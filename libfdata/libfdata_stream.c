/*
 * The stream functions
 *
 * Copyright (c) 2010-2013, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfdata_stream.h"
#include "libfdata_buffer.h"
#include "libfdata_definitions.h"
#include "libfdata_libcerror.h"
#include "libfdata_libcnotify.h"
#include "libfdata_libfcache.h"
#include "libfdata_list.h"
#include "libfdata_list_element.h"
#include "libfdata_types.h"
#include "libfdata_unused.h"

/* Initializes the stream
 *
 * If the flag LIBFDATA_FLAG_DATA_HANDLE_MANAGED is set the stream
 * takes over management of the data handle and the data handle is freed when
 * no longer needed
 *
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_initialize(
     libfdata_stream_t **stream,
     intptr_t *data_handle,
     int (*free_data_handle)(
            intptr_t **data_handle,
            libcerror_error_t **error ),
     int (*clone_data_handle)(
            intptr_t **destination_data_handle,
            intptr_t *source_data_handle,
            libcerror_error_t **error ),
     ssize_t (*read_segment_data)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                int segment_index,
                uint8_t *data,
                size_t data_size,
                uint8_t read_flags,
                libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_initialize";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stream value already set.",
		 function );

		return( -1 );
	}
	if( read_segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid read segment data function.",
		 function );

		return( -1 );
	}
	internal_stream = memory_allocate_structure(
	                   libfdata_internal_stream_t );

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create stream.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_stream,
	     0,
	     sizeof( libfdata_internal_stream_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear stream.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_stream->segments_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create segments array.",
		 function );

		goto on_error;
	}
	internal_stream->flags            |= flags;
	internal_stream->data_handle       = data_handle;
	internal_stream->free_data_handle  = free_data_handle;
	internal_stream->clone_data_handle = clone_data_handle;
	internal_stream->read_segment_data = read_segment_data;

	*stream = (libfdata_stream_t *) internal_stream;

	return( 1 );

on_error:
	if( internal_stream != NULL )
	{
		if( internal_stream->segments_array != NULL )
		{
			libcdata_array_free(
			 &( internal_stream->segments_array ),
			 (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_range_free,
			 NULL );
		}
		memory_free(
		 internal_stream );
	}
	return( -1 );
}

/* Frees the stream
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_free(
     libfdata_stream_t **stream,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_free";
	int result                                  = 1;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		internal_stream = (libfdata_internal_stream_t *) *stream;
		*stream         = NULL;

		if( libcdata_array_free(
		     &( internal_stream->segments_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the segments array.",
			 function );

			result = -1;
		}
		if( ( internal_stream->flags & LIBFDATA_FLAG_DATA_HANDLE_MANAGED ) != 0 )
		{
			if( internal_stream->data_handle != NULL )
			{
				if( internal_stream->free_data_handle == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: invalid source stream - missing free data handle function.",
					 function );

					result = -1;
				}
				else if( internal_stream->free_data_handle(
				          &( internal_stream->data_handle ),
				          error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free data handle.",
					 function );

					result = -1;
				}
			}
		}
		memory_free(
		 internal_stream );
	}
	return( result );
}

/* Clones (duplicates) the stream
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_clone(
     libfdata_stream_t **destination_stream,
     libfdata_stream_t *source_stream,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_source_stream = NULL;
	intptr_t *destination_data_handle                  = NULL;
	static char *function                              = "libfdata_stream_clone";

	if( destination_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination stream.",
		 function );

		return( -1 );
	}
	if( *destination_stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: destination stream already set.",
		 function );

		return( -1 );
	}
	if( source_stream == NULL )
	{
		*destination_stream = NULL;

		return( 1 );
	}
	internal_source_stream = (libfdata_internal_stream_t *) source_stream;

	if( internal_source_stream->data_handle != NULL )
	{
		if( internal_source_stream->free_data_handle == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid source stream - missing free data handle function.",
			 function );

			goto on_error;
		}
		if( internal_source_stream->clone_data_handle == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid source stream - missing clone data handle function.",
			 function );

			goto on_error;
		}
		if( internal_source_stream->clone_data_handle(
		     &destination_data_handle,
		     internal_source_stream->data_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create destination data handle.",
			 function );

			goto on_error;
		}
	}
	if( libfdata_stream_initialize(
	     destination_stream,
	     destination_data_handle,
	     internal_source_stream->free_data_handle,
	     internal_source_stream->clone_data_handle,
	     internal_source_stream->read_segment_data,
	     LIBFDATA_FLAG_DATA_HANDLE_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create destination stream.",
		 function );

		goto on_error;
	}
	if( *destination_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing destination stream.",
		 function );

		goto on_error;
	}
	destination_data_handle = NULL;

/* TODO clone data ranges */
	return( 1 );

on_error:
	if( *destination_stream != NULL )
	{
		libfdata_stream_free(
		 destination_stream,
		 NULL );
	}
	if( destination_data_handle != NULL )
	{
		internal_source_stream->free_data_handle(
		 &destination_data_handle,
		 NULL );
	}
	return( -1 );
}

/* Segment functions
 */

/* Empties the segments
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_empty_segments(
     libfdata_stream_t *stream,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_empty_segments";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) stream;

	if( libcdata_array_empty(
	     internal_stream->segments_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty segments array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Resizes the segments
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_resize_segments(
     libfdata_stream_t *stream,
     int number_of_segments,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_resize_segments";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) stream;

	if( libcdata_array_resize(
	     internal_stream->segments_array,
	     number_of_segments,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize segments array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of segments of the stream
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_number_of_segments(
     libfdata_stream_t *stream,
     int *number_of_segments,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_get_number_of_segments";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) stream;

	if( libcdata_array_get_number_of_entries(
	     internal_stream->segments_array,
	     number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from segments array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the offset and size of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_segment_by_index(
     libfdata_stream_t *stream,
     int segment_index,
     int *segment_file_index,
     off64_t *segment_offset,
     size64_t *segment_size,
     uint32_t *segment_flags,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	libfdata_list_element_t *segment            = NULL;
	static char *function                       = "libfdata_stream_get_segment_by_index";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) stream;

	if( libcdata_array_get_entry_by_index(
	     internal_stream->segments_array,
	     segment_index,
	     (intptr_t **) &segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from segments array.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( libfdata_list_element_get_data_range(
	     segment,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment: %d data range values.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Sets the offset and size of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_set_segment_by_index(
     libfdata_stream_t *stream,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libcerror_error_t **error )
{
	libfdata_range_t *segment_data_range        = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_set_segment_by_index";
	off64_t previous_segment_offset             = 0;
	size64_t previous_segment_size              = 0;
	uint32_t previous_segment_flags             = 0;
	int previous_segment_file_index             = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) stream;

	if( libcdata_array_get_entry_by_index(
	     internal_stream->segments_array,
	     segment_index,
	     (intptr_t **) &segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from segments array.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( segment_data_range == NULL )
	{
		if( libfdata_range_initialize(
		     &segment_data_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create segment data range.",
			 function );

			return( -1 );
		}
		if( libcdata_array_set_entry_by_index(
		     internal_stream->segments_array,
		     segment_index,
		     (intptr_t *) segment_data_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set entry: %d in segments array.",
			 function,
			 segment_index );

			libfdata_range_free(
			 &segment_data_range,
			 NULL );

			return( -1 );
		}
	}
	else
	{
		if( libfdata_range_get(
		     segment_data_range,
		     &previous_segment_file_index,
		     &previous_segment_offset,
		     &previous_segment_size,
		     &previous_segment_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d data range values.",
			 function,
			 segment_index );

			return( -1 );
		}
		internal_stream->data_size -= previous_segment_size;
	}
	if( libfdata_range_set(
	     segment_data_range,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set segment data range values.",
		 function );

		return( -1 );
	}
	internal_stream->data_size += segment_size;
	internal_stream->flags     |= LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES;

	return( 1 );
}

/* Appends a segment offset and size
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_append_segment(
     libfdata_stream_t *stream,
     int *segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	libfdata_range_t *segment_data_range        = NULL;
	static char *function                       = "libfdata_stream_append_segment";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) stream;

	if( segment_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment index.",
		 function );

		return( -1 );
	}
	if( libfdata_range_initialize(
	     &segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create segment data range.",
		 function );

		goto on_error;
	}
	if( libfdata_range_set(
	     segment_data_range,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set segment data range values.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_stream->segments_array,
	     segment_index,
	     (intptr_t *) segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append data range to segments array.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: segment: %03d\tfile index: %03d offset: 0x%08" PRIx64 " - 0x%08" PRIx64 " (size: %" PRIu64 ")\n",
		 function,
		 *segment_index,
		 segment_file_index,
		 segment_offset,
		 segment_offset + segment_size,
		 segment_size );
	}
#endif
	internal_stream->data_size += segment_size;

	return( 1 );

on_error:
	if( segment_data_range != NULL )
	{
		libfdata_range_free(
		 &segment_data_range,
		 NULL );
	}
	return( -1 );
}

/* IO functions
 */

/* Reads data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfdata_stream_read_buffer(
         libfdata_stream_t *stream,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	uint8_t *segment_data                       = NULL;
	static char *function                       = "libfdata_stream_read_buffer";
	size64_t data_stream_size                   = 0;
	size_t buffer_offset                        = 0;
	size_t read_size                            = 0;
	size_t segment_data_size                    = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) stream;

	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfdata_list_get_data_size(
	     internal_stream->segments_list,
	     &data_stream_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segments list data size.",
		 function );

		return( -1 );
	}
	if( ( internal_stream->data_offset < 0 )
	 || ( internal_stream->data_offset >= (off64_t) data_stream_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid stream - data offset: %" PRIi64 " value out of bounds: 0 - %" PRIu64 ".",
		 function,
		 internal_stream->data_offset,
		 data_stream_size );

		return( -1 );
	}
	if( (off64_t) ( internal_stream->data_offset + buffer_size ) > (off64_t) data_stream_size )
	{
		buffer_size = (size_t) ( data_stream_size - internal_stream->data_offset );
	}
	while( buffer_size > 0 )
	{
		if( libfdata_stream_get_segment_data(
		     stream,
		     file_io_handle,
		     cache,
		     internal_stream->segment_index,
		     &segment_data,
		     &segment_data_size,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment data at offset: %" PRIi64 ".",
			 function,
			 internal_stream->data_offset );

			return( -1 );
		}
		if( segment_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing segment data.",
			 function );

			return( -1 );
		}
		read_size = segment_data_size - internal_stream->segment_data_offset;

		if( read_size > buffer_size )
		{
			read_size = buffer_size;
		}
		if( memory_copy(
		     &( buffer[ buffer_offset ] ),
		     &( segment_data[ internal_stream->segment_data_offset ] ),
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy segment data to buffer.",
			 function );

			return( -1 );
		}
		internal_stream->data_offset += read_size;

		if( ( internal_stream->segment_data_offset + read_size ) == segment_data_size )
		{
			internal_stream->segment_index      += 1;
			internal_stream->segment_data_offset = 0;
		}
		else
		{
			internal_stream->segment_data_offset += read_size;
		}
		buffer_size   -= read_size;
		buffer_offset += read_size;
	}
	return( (size_t) buffer_offset );
}

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libfdata_stream_seek_offset(
         libfdata_stream_t *stream,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_seek_offset";
	size64_t data_stream_size                   = 0;
	size_t segment_data_offset                  = 0;
	int segment_index                           = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) stream;

	if( internal_stream->data_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid stream - data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( libfdata_list_get_data_size(
	     internal_stream->segments_list,
	     &data_stream_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segments list data size.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_stream->data_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) data_stream_size;
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: seeking offset: %" PRIi64 ".\n",
		 function,
		 offset );
	}
#endif
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( offset < (off64_t) data_stream_size )
	{
		if( libfdata_list_get_element_index_at_value_offset(
		     internal_stream->segments_list,
		     offset,
		     &segment_index,
		     &segment_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element index at offset %" PRIi64 ".",
			 function,
			 offset );

			return( -1 );
		}
		internal_stream->segment_index       = segment_index;
		internal_stream->segment_data_offset = segment_data_offset;
	}
	internal_stream->data_offset = offset;

	return( offset );
}

