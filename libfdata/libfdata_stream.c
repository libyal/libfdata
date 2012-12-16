/*
 * The stream functions
 *
 * Copyright (c) 2010-2012, Joachim Metz <joachim.metz@gmail.com>
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
#include "libfdata_mapped_range.h"
#include "libfdata_range.h"
#include "libfdata_types.h"
#include "libfdata_unused.h"

#define libfdata_stream_calculate_cache_entry_index( segment_index, number_of_cache_entries ) \
	segment_index % number_of_cache_entries

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
                int segment_file_index,
                uint8_t *segment_data,
                size_t segment_data_size,
                uint8_t read_flags,
                libcerror_error_t **error ),
     ssize_t (*write_segment_data)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                int segment_file_index,
                const uint8_t *segment_data,
                size_t segment_data_size,
                uint8_t write_flags,
                libcerror_error_t **error ),
     off64_t (*seek_segment_offset)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                int segment_file_index,
                off64_t segment_offset,
                int whence,
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

		memory_free(
		 internal_stream );

		return( -1 );
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
	if( libcdata_array_initialize(
	     &( internal_stream->mapped_ranges_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create mapped ranges array.",
		 function );

		goto on_error;
	}
	internal_stream->timestamp           = libfcache_date_time_get_timestamp();
	internal_stream->flags              |= flags;
	internal_stream->data_handle         = data_handle;
	internal_stream->free_data_handle    = free_data_handle;
	internal_stream->clone_data_handle   = clone_data_handle;
	internal_stream->read_segment_data   = read_segment_data;
	internal_stream->write_segment_data  = write_segment_data;
	internal_stream->seek_segment_offset = seek_segment_offset;

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
		     &( internal_stream->mapped_ranges_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_mapped_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the mapped ranges array.",
			 function );

			result = -1;
		}
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
				if( internal_stream->free_data_handle != NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: invalid stream - missing free data handle function.",
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
		 "%s: invalid destination stream value already set.",
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
	     internal_source_stream->write_segment_data,
	     internal_source_stream->seek_segment_offset,
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
	     internal_stream->mapped_ranges_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_mapped_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty mapped ranges array.",
		 function );

		return( -1 );
	}
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
	if( libcdata_array_resize(
	     internal_stream->mapped_ranges_array,
	     number_of_segments,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_mapped_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize mapped ranges array.",
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
	libfdata_range_t *segment_data_range        = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
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
	if( libfdata_range_get(
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
	libfdata_mapped_range_t *mapped_range       = NULL;
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
		if( libfdata_mapped_range_initialize(
		     &mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create mapped range.",
			 function );

			libfdata_range_free(
			 &segment_data_range,
			 NULL );

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

			libfdata_mapped_range_free(
			 &mapped_range,
			 NULL );
			libfdata_range_free(
			 &segment_data_range,
			 NULL );

			return( -1 );
		}
		if( libcdata_array_set_entry_by_index(
		     internal_stream->mapped_ranges_array,
		     segment_index,
		     (intptr_t *) mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set entry: %d in mapped ranges array.",
			 function,
			 segment_index );

			libcdata_array_set_entry_by_index(
			 internal_stream->segments_array,
			 segment_index,
			 NULL,
			 NULL );
			libfdata_mapped_range_free(
			 &mapped_range,
			 NULL );
			libfdata_range_free(
			 &segment_data_range,
			 NULL );

			return( -1 );
		}
	}
	else
	{
		if( libcdata_array_get_entry_by_index(
		     internal_stream->mapped_ranges_array,
		     segment_index,
		     (intptr_t **) &mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from mapped ranges array.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( mapped_range == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing mapped range: %d\n",
			 function,
			 segment_index );

			return( -1 );
		}
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

/* Appends a segment
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
	libfdata_mapped_range_t *mapped_range       = NULL;
	libfdata_range_t *segment_data_range        = NULL;
	static char *function                       = "libfdata_stream_append_segment";
	int mapped_range_index                      = 0;

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
	if( libfdata_mapped_range_initialize(
	     &mapped_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create mapped range.",
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
	if( libfdata_mapped_range_set(
	     mapped_range,
	     (off64_t) internal_stream->data_size,
	     segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set mapped range values.",
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
	if( libcdata_array_append_entry(
	     internal_stream->mapped_ranges_array,
	     &mapped_range_index,
	     (intptr_t *) mapped_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append mapped range to array.",
		 function );

		libcdata_array_set_entry_by_index(
		 internal_stream->segments_array,
		 *segment_index,
		 NULL,
		 NULL );

		goto on_error;
	}
	internal_stream->data_size += segment_size;

	return( 1 );

on_error:
	if( mapped_range != NULL )
	{
		libfdata_mapped_range_free(
		 &mapped_range,
		 NULL );
	}
	if( segment_data_range != NULL )
	{
		libfdata_range_free(
		 &segment_data_range,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the maximum segment size
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_maximum_segment_size(
     libfdata_stream_t *stream,
     size64_t *maximum_segment_size,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_get_maximum_segment_size";

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

	if( maximum_segment_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid maximum segment size.",
		 function );

		return( -1 );
	}
	*maximum_segment_size = internal_stream->maximum_segment_size;

	return( 1 );
}

/* Sets the maximum segment size
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_set_maximum_segment_size(
     libfdata_stream_t *stream,
     size64_t maximum_segment_size,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_set_maximum_segment_size";

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

	if( maximum_segment_size > (size64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid maximum segment size value exceeds maximum.",
		 function );

		return( -1 );
	}
	internal_stream->maximum_segment_size = maximum_segment_size;

	return( 1 );
}

/* Mapped range functions
 */

/* Calculates the mapped ranges
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_calculate_mapped_ranges(
     libfdata_internal_stream_t *internal_stream,
     libcerror_error_t **error )
{
	libfdata_mapped_range_t *mapped_range = NULL;
	libfdata_range_t *segment_data_range  = NULL;
	static char *function                 = "libfdata_stream_calculate_mapped_ranges";
	off64_t mapped_range_offset           = 0;
	off64_t segment_offset                = 0;
	size64_t segment_size                 = 0;
	uint32_t segment_flags                = 0;
	int number_of_segments                = 0;
	int segment_file_index                = 0;
	int segment_index                     = 0;

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream ",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_stream->segments_array,
	     &number_of_segments,
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
	for( segment_index = 0;
	     segment_index < number_of_segments;
	     segment_index++ )
	{
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
		if( libcdata_array_get_entry_by_index(
		     internal_stream->mapped_ranges_array,
		     segment_index,
		     (intptr_t **) &mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from mapped ranges array.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_range_get(
		     segment_data_range,
		     &segment_file_index,
		     &segment_offset,
		     &segment_size,
		     &segment_flags,
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
		if( libfdata_mapped_range_set(
		     mapped_range,
		     mapped_range_offset,
		     segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set mapped range: %d values.",
			 function,
			 segment_index );

			return( -1 );
		}
		mapped_range_offset += (off64_t) segment_size;
	}
	internal_stream->timestamp = libfcache_date_time_get_timestamp();
	internal_stream->flags    &= ~( LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES );

	return( 1 );
}

/* Data functions
 */

/* Retrieves the data offset
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_data_offset(
     libfdata_stream_t *stream,
     off64_t *data_offset,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_get_data_offset";

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

	if( data_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data offset.",
		 function );

		return( -1 );
	}
	*data_offset = internal_stream->data_offset;

	return( 1 );
}

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_data_size(
     libfdata_stream_t *stream,
     size64_t *data_size,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_get_data_size";

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

	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	*data_size = internal_stream->data_size;

	return( 1 );
}

/* Check if the data has been cached as a single cache value
 * The data_buffer value is set if successful
 * Returns 1 if successful, 0 if not or -1 on error
 */
int libfdata_stream_get_cached_data_buffer(
     libfdata_internal_stream_t *internal_stream,
     libfcache_cache_t *cache,
     libfcache_cache_value_t *cache_value,
     libfdata_buffer_t **data_buffer,
     libcerror_error_t **error )
{
	static char *function        = "libfdata_stream_get_cached_data_buffer";
        off64_t cache_value_offset   = (off64_t) -1;
	size_t data_size             = 0;
	time_t cache_value_timestamp = 0;
        int cache_value_file_index   = -1;
	int number_of_cache_values   = 0;

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( data_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data buffer.",
		 function );

		return( -1 );
	}
	*data_buffer = NULL;

	if( cache_value == NULL )
	{
		return( 0 );
	}
	if( libfcache_cache_get_number_of_cache_values(
	     cache,
	     &number_of_cache_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of cache values.",
		 function );

		goto on_error;
	}
	if( number_of_cache_values != 1 )
	{
		return( 0 );
	}
	if( libfcache_cache_value_get_identifier(
	     cache_value,
	     &cache_value_file_index,
	     &cache_value_offset,
	     &cache_value_timestamp,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve cache value identifier.",
		 function );

		return( -1 );
	}
	if( ( cache_value_file_index != 0 )
	 || ( cache_value_offset != 0 )
	 || ( cache_value_timestamp != internal_stream->timestamp ) )
	{
		return( 0 );
	}
	if( libfcache_cache_value_get_value(
	     cache_value,
	     (intptr_t **) data_buffer,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data buffer from cache value: 0.",
		 function );

		goto on_error;
	}
	if( data_buffer == NULL )
	{
		return( 0 );
	}
	if( libfdata_buffer_get_data_size(
	     *data_buffer,
	     &data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data size.",
		 function );

		goto on_error;
	}
	if( internal_stream->data_size != (size64_t) data_size )
	{
		*data_buffer = NULL;

		return( 0 );
	}
	return( 1 );

on_error:
	*data_buffer = NULL;

	return( -1 );
}

/* Reads the data into a single data buffer
 * This function cannot handle data of a size > SSIZE_MAX
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_read_data_buffer(
     libfdata_internal_stream_t *internal_stream,
     intptr_t *file_io_handle,
     libfdata_buffer_t **data_buffer,
     libcerror_error_t **error )
{
	libfdata_range_t *segment_data_range = NULL;
	uint8_t *data                        = NULL;
	static char *function                = "libfdata_stream_read_data_buffer";
	off64_t segment_offset               = 0;
	size64_t segment_size                = 0;
	size_t data_offset                   = 0;
	size_t data_size                     = 0;
	ssize_t read_count                   = 0;
	uint32_t segment_flags               = 0;
	int number_of_segments               = 0;
	int segment_file_index               = 0;
	int segment_index                    = 0;

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( internal_stream->read_segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing read segment data function.",
		 function );

		return( -1 );
	}
	if( internal_stream->seek_segment_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing seek segment offset function.",
		 function );

		return( -1 );
	}
	if( internal_stream->data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data buffer.",
		 function );

		return( -1 );
	}
	if( *data_buffer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data buffer value already set.",
		 function );

		return( -1 );
	}
	if( libfdata_buffer_initialize(
	     data_buffer,
	     (size_t) internal_stream->data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data buffer.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_get_data(
	     *data_buffer,
	     &data,
	     &data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data from data buffer.",
		 function );

		goto on_error;
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing data.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     internal_stream->segments_array,
	     &number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from segments array.",
		 function );

		goto on_error;
	}
	/* Read all the segment data into the data buffer
	 */
	for( segment_index = 0;
	     segment_index < number_of_segments;
	     segment_index++ )
	{
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

			goto on_error;
		}
		if( libfdata_range_get(
		     segment_data_range,
		     &segment_file_index,
		     &segment_offset,
		     &segment_size,
		     &segment_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d data range values.",
			 function,
			 segment_index );

			goto on_error;
		}
/* TODO check if segment size is in bounds
		if( data_size != (size_t) segment_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data size value out of bounds.",
			 function );

			goto on_error;
		}
*/
		if( internal_stream->seek_segment_offset(
		     internal_stream->data_handle,
		     file_io_handle,
		     segment_file_index,
		     segment_offset,
		     SEEK_SET,
		     error ) != segment_offset )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek segment offset: %" PRIi64 " in segment file: %d.",
			 function,
			 segment_offset,
			 segment_file_index );

			goto on_error;
		}
		read_count = internal_stream->read_segment_data(
			      internal_stream->data_handle,
			      file_io_handle,
			      segment_file_index,
			      &( data[ data_offset ] ),
			      (size_t) segment_size,
			      0,
			      error );

		if( read_count != (ssize_t) segment_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read segment data: %d from segment file: %d.",
			 function,
			 segment_index,
			 segment_file_index );

			goto on_error;
		}
		data_offset += (size_t) read_count;
	}
	return( 1 );

on_error:
	if( *data_buffer != NULL )
	{
		libfdata_buffer_free(
		 data_buffer,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the data of the stream
 * The function caches all the data segments of the stream into a single buffer
 * This function cannot handle data of a size > SSIZE_MAX
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_data(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfcache_cache_value_t *cache_value        = NULL;
	libfdata_buffer_t *data_buffer              = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_get_data";
	int result                                  = 0;

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

	if( ( read_flags & LIBFDATA_READ_FLAG_IGNORE_CACHE ) != 0 )
	{
		result = libfdata_stream_get_cached_segment_data(
			  internal_stream,
			  cache,
			  0,
		          0,
		          0,
		          internal_stream->data_size,
		          0,
			  &cache_value,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cached segment data.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			/* Check if all data has been cached in a single cache value
			 */
			result = libfdata_stream_get_cached_data_buffer(
				  internal_stream,
				  cache,
				  cache_value,
				  &data_buffer,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve cached single data buffer.",
				 function );

				return( -1 );
			}
		}
	}
	/* Read all the data in a single cache value
	 */
	if( result == 0 )
	{
		if( libfcache_cache_clear(
		     cache,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to clear cache.",
			 function );

			return( -1 );
		}
		data_buffer = NULL;

		if( libfdata_stream_read_data_buffer(
		     internal_stream,
		     file_io_handle,
		     &data_buffer,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data as single data buffer.",
			 function );

			return( -1 );
		}
		if( libfcache_cache_set_value_by_index(
		     cache,
		     0,
		     0,
		     0,
		     internal_stream->timestamp,
		     (intptr_t *) data_buffer,
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_buffer_free,
		     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set value in cache entry: 0.",
			 function );

			libfdata_buffer_free(
			 &data_buffer,
			 NULL );

			return( -1 );
		}
	}
	if( libfdata_buffer_get_data(
	     data_buffer,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data from data buffer.",
		 function );

		data_buffer = NULL;

		return( -1 );
	}
	return( 1 );
}

/* Segment data functions
 */

/* Retrieves the segment index for a specific data offset
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_segment_index_at_data_offset(
     libfdata_internal_stream_t *internal_stream,
     off64_t data_offset,
     int *segment_index,
     off64_t *segment_data_offset,
     libcerror_error_t **error )
{
	libfdata_mapped_range_t *mapped_range = NULL;
	static char *function                 = "libfdata_stream_get_segment_index_at_data_offset";
	off64_t mapped_range_offset           = 0;
	size64_t mapped_range_size            = 0;
	int initial_segment_index             = 0;
	int number_of_segments                = 0;

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( internal_stream->data_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid stream - data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( data_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid data offset value less than zero.",
		 function );

		return( -1 );
	}
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
	if( segment_data_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment data offset.",
		 function );

		return( -1 );
	}
	if( ( internal_stream->flags & LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES ) != 0 )
	{
		if( libfdata_stream_calculate_mapped_ranges(
		     internal_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to calculate mapped ranges.",
			 function );

			return( -1 );
		}
	}
	if( libcdata_array_get_number_of_entries(
	     internal_stream->segments_array,
	     &number_of_segments,
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
	/* This assumes a fairly even distribution of the sizes of the segments
	 */
	initial_segment_index = (int) ( ( number_of_segments * data_offset ) / internal_stream->data_size );

	/* Look for the corresponding segment upwards in the array
	 */
	for( *segment_index = initial_segment_index;
	     *segment_index < number_of_segments;
	     *segment_index += 1 )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_stream->segments_array,
		     *segment_index,
		     (intptr_t **) &mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from mapped ranges array.",
			 function,
			 *segment_index );

			return( -1 );
		}
		if( libfdata_mapped_range_get(
		     mapped_range,
		     &mapped_range_offset,
		     &mapped_range_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to retrieve values from mapped range: %d.",
			 function,
			 *segment_index );

			return( -1 );
		}
		/* Check if the data offset is in the mapped range
		 */
		if( ( data_offset >= mapped_range_offset )
		 && ( data_offset < ( mapped_range_offset + (off64_t) mapped_range_size ) ) )
		{
			data_offset -= mapped_range_offset;

			break;
		}
		/* Check if the data offset is out of bounds
		 */
		if( data_offset < mapped_range_offset )
		{
			*segment_index = number_of_segments;

			break;
		}
	}
	if( *segment_index >= number_of_segments )
	{
		/* Look for the corresponding segment downwards in the array
		 */
		for( *segment_index = initial_segment_index;
		     *segment_index >= 0;
		     *segment_index -= 1 )
		{
			if( libcdata_array_get_entry_by_index(
			     internal_stream->segments_array,
			     *segment_index,
			     (intptr_t **) &mapped_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve entry: %d from mapped ranges array.",
				 function,
				 *segment_index );

				return( -1 );
			}
			if( libfdata_mapped_range_get(
			     mapped_range,
			     &mapped_range_offset,
			     &mapped_range_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to retrieve values from mapped range: %d.",
				 function,
				 *segment_index );

				return( -1 );
			}
			/* Check if the data offset is in the mapped range
			 */
			if( ( data_offset >= mapped_range_offset )
			 && ( data_offset < ( mapped_range_offset + (off64_t) mapped_range_size ) ) )
			{
				data_offset -= mapped_range_offset;

				break;
			}
			/* Check if the data offset is out of bounds
			 */
			if( data_offset > mapped_range_offset )
			{
				*segment_index = -1;

				break;
			}
		}
	}
	if( *segment_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment index value out of bounds.",
		 function );

		return( -1 );
	}
	if( data_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	*segment_data_offset = data_offset;

	return( 1 );
}

/* Check if the segment data has been cached
 * Returns 1 if successful, 0 if not or -1 on error
 */
int libfdata_stream_get_cached_segment_data(
     libfdata_internal_stream_t *internal_stream,
     libfcache_cache_t *cache,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libfcache_cache_value_t **cache_value,
     libcerror_error_t **error )
{
	static char *function        = "libfdata_stream_get_cached_segment_data";
        off64_t cache_value_offset   = (off64_t) -1;
	time_t cache_value_timestamp = 0;
	int cache_entry_index        = -1;
        int cache_value_file_index   = -1;
	int number_of_cache_entries  = 0;

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( segment_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment index value out of bounds.",
		 function );

		return( -1 );
	}
	if( cache_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache value.",
		 function );

		return( -1 );
	}
	if( libfcache_cache_get_number_of_entries(
	     cache,
	     &number_of_cache_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of cache entries.",
		 function );

		return( -1 );
	}
	if( number_of_cache_entries <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of cache entries value out of bounds.",
		 function );

		return( -1 );
	}
	cache_entry_index = libfdata_stream_calculate_cache_entry_index(
	                     segment_index,
	                     number_of_cache_entries );

	if( libfcache_cache_get_value_by_index(
	     cache,
	     cache_entry_index,
	     cache_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve cache entry: %d from cache.",
		 function,
		 cache_entry_index );

		return( -1 );
	}
	if( *cache_value == NULL )
	{
		return( 0 );
	}
	if( libfcache_cache_value_get_identifier(
	     *cache_value,
	     &cache_value_file_index,
	     &cache_value_offset,
	     &cache_value_timestamp,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve cache value identifier.",
		 function );

		return( -1 );
	}
	if( ( cache_value_file_index != segment_file_index )
	 || ( cache_value_offset != segment_offset )
	 || ( cache_value_timestamp != internal_stream->timestamp ) )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: cache: 0x%08" PRIjx " miss (%d out of %d)\n",
			 function,
			 (intptr_t) cache,
			 cache_entry_index,
			 number_of_cache_entries );
		}
#endif
		*cache_value = NULL;

		return( 0 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: cache: 0x%08" PRIjx " hit (%d out of %d)\n",
		 function,
		 (intptr_t) cache,
		 cache_entry_index,
		 number_of_cache_entries );
	}
#endif
	return( 1 );
}

/* Reads the segment data into a buffer
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_read_segment_data(
     libfdata_internal_stream_t *internal_stream,
     intptr_t *file_io_handle,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     uint8_t *segment_data,
     size_t segment_data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	static char *function = "libfdata_stream_read_segment_data";
	ssize_t read_count    = 0;

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal stream.",
		 function );

		return( -1 );
	}
	if( internal_stream->read_segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing read segment data function.",
		 function );

		return( -1 );
	}
	if( internal_stream->seek_segment_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing seek segment offset function.",
		 function );

		return( -1 );
	}
	if( (size64_t) segment_data_size != segment_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading segment data at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIu64 "\n",
		 function,
		 segment_offset,
		 segment_offset,
		 segment_size );
	}
#endif
	if( internal_stream->seek_segment_offset(
	     internal_stream->data_handle,
	     file_io_handle,
	     segment_file_index,
	     segment_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset: %" PRIi64 " in segment: %d.",
		 function,
		 segment_offset,
		 segment_index );

		return( -1 );
	}
	read_count = internal_stream->read_segment_data(
		      internal_stream->data_handle,
		      file_io_handle,
		      segment_file_index,
		      segment_data,
		      segment_data_size,
		      read_flags,
		      error );

	if( read_count != (ssize_t) segment_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data from segment: %d.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Reads the segment data into a data buffer
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_read_segment_data_buffer(
     libfdata_internal_stream_t *internal_stream,
     intptr_t *file_io_handle,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libfdata_buffer_t **data_buffer,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libfdata_stream_read_segment_data_buffer";
	size_t data_size      = 0;

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal stream.",
		 function );

		return( -1 );
	}
	if( segment_size > (size64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid segment size value exceeds maximum.",
		 function );

		goto on_error;
	}
	if( data_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data buffer.",
		 function );

		return( -1 );
	}
	if( *data_buffer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data buffer value already set.",
		 function );

		return( -1 );
	}
	if( libfdata_buffer_initialize(
	     data_buffer,
	     (size_t) segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data buffer.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_get_data(
	     *data_buffer,
	     &data,
	     &data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data from data buffer.",
		 function );

		goto on_error;
	}
	if( libfdata_stream_read_segment_data(
	     internal_stream,
	     file_io_handle,
	     segment_file_index,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     data,
	     data_size,
	     read_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment: %d data.",
		 function,
		 segment_index );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *data_buffer != NULL )
	{
		libfdata_buffer_free(
		 data_buffer,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the segment data and size of a specific segment
 * This function requires a cache 
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_segment_data(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t **segment_data,
     size_t *segment_data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfcache_cache_value_t *cache_value        = NULL;
	libfdata_buffer_t *data_buffer              = NULL;
	libfdata_mapped_range_t *mapped_range       = NULL;
	libfdata_range_t *segment_data_range        = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_get_segment_data";
	off64_t mapped_range_offset                 = 0;
	off64_t segment_offset                      = 0;
	size64_t mapped_range_size                  = 0;
	size64_t segment_size                       = 0;
	uint32_t segment_flags                      = 0;
	int cache_entry_index                       = 0;
	int number_of_cache_entries                 = 0;
	int result                                  = 0;
	int segment_file_index                      = 0;

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

	if( cache == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache.",
		 function );

		return( -1 );
	}
	if( segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment data.",
		 function );

		return( -1 );
	}
	if( segment_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment data size.",
		 function );

		return( -1 );
	}
	if( ( internal_stream->flags & LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES ) != 0 )
	{
		if( libfdata_stream_calculate_mapped_ranges(
		     internal_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to calculate mapped ranges.",
			 function );

			return( -1 );
		}
	}
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
	if( libfdata_range_get(
	     segment_data_range,
	     &segment_file_index,
	     &segment_offset,
	     &segment_size,
	     &segment_flags,
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
	if( ( read_flags & LIBFDATA_READ_FLAG_IGNORE_CACHE ) != 0 )
	{
		result = libfdata_stream_get_cached_segment_data(
			  internal_stream,
			  cache,
			  segment_index,
		          segment_file_index,
		          segment_offset,
		          segment_size,
		          segment_flags,
			  &cache_value,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cached segment data.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			/* Check if all data has been cached in a single cache value
			 */
			result = libfdata_stream_get_cached_data_buffer(
				  internal_stream,
				  cache,
				  cache_value,
				  &data_buffer,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve cached single data buffer.",
				 function );

				return( -1 );
			}
			else if( result != 0 )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_stream->mapped_ranges_array,
				     segment_index,
				     (intptr_t **) &mapped_range,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve entry: %d from mapped ranges array.",
					 function,
					 segment_index );

					return( -1 );
				}
				if( libfdata_mapped_range_get(
				     mapped_range,
				     &mapped_range_offset,
				     &mapped_range_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve mapped range: %d values.",
					 function,
					 segment_index );

					return( -1 );
				}
				if( mapped_range_offset > (off64_t) SSIZE_MAX )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid mapped range offset value exceeds maximum.",
					 function );

					return( -1 );
				}
				if( mapped_range_size > (off64_t) SSIZE_MAX )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid mapped range size value exceeds maximum.",
					 function );

					return( -1 );
				}
				if( libfdata_buffer_get_data_at_offset(
				     data_buffer,
				     (size_t) mapped_range_offset,
				     segment_data,
				     segment_data_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve data from data buffer at offset: %" PRIi64 ".",
					 function,
					 mapped_range_offset );

					return( -1 );
				}
			}
			else
			{
				if( libfcache_cache_value_get_value(
				     cache_value,
				     (intptr_t **) &data_buffer,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve element value.",
					 function );

					return( -1 );
				}
				if( libfdata_buffer_get_data(
				     data_buffer,
				     segment_data,
				     segment_data_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve data from data buffer.",
					 function );

					return( -1 );
				}
				result = 1;
			}
		}
	}
	if( result == 0 )
	{
		if( libfcache_cache_get_number_of_entries(
		     cache,
		     &number_of_cache_entries,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of cache entries.",
			 function );

			return( -1 );
		}
		if( libfdata_stream_read_segment_data_buffer(
		     internal_stream,
		     file_io_handle,
		     segment_index,
		     segment_file_index,
		     segment_offset,
		     segment_size,
		     segment_flags,
		     &data_buffer,
		     read_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to retrieve read segment: %d data buffer.",
			 function,
			 segment_index );

			return( -1 );
		}
		cache_entry_index = libfdata_stream_calculate_cache_entry_index(
		                     segment_index,
		                     number_of_cache_entries );

		if( libfcache_cache_set_value_by_index(
		     cache,
		     cache_entry_index,
		     segment_file_index,
		     segment_offset,
		     internal_stream->timestamp,
		     (intptr_t *) data_buffer,
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_buffer_free,
		     LIBFCACHE_CACHE_VALUE_FLAG_MANAGED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set value in cache entry: %d.",
			 function,
			 cache_entry_index );

			libfdata_buffer_free(
			 &data_buffer,
			 NULL );

			return( -1 );
		}
		if( libfdata_buffer_get_data(
		     data_buffer,
		     segment_data,
		     segment_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the segment data and size at a certain offset
 * This function requires a cache 
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_segment_data_at_offset(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     off64_t data_offset,
     uint8_t **segment_data,
     size_t *segment_data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_get_segment_data_at_offset";
	off64_t segment_data_offset                 = 0;
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

	if( libfdata_stream_get_segment_index_at_data_offset(
	     internal_stream,
	     data_offset,
	     &segment_index,
	     &segment_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment index at offset: %" PRIi64 ".",
		 function,
		 data_offset );

		return( -1 );
	}
	if( libfdata_stream_get_segment_data(
             stream,
             file_io_handle,
             cache,
             segment_index,
             segment_data,
             segment_data_size,
             read_flags,
             error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment: %d data.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Sets the data and size of a specific segment
 *
 * If the flag LIBFDATA_SEGMENT_DATA_FLAG_MANAGED is set the stream
 * takes over management of the data and the data is freed when
 * no longer needed. If the flag is not set the stream makes a copy of the data.
 *
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_set_segment_data(
     libfdata_stream_t *stream,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t *segment_data,
     size_t segment_data_size,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer              = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	libfdata_range_t *segment_data_range        = NULL;
	static char *function                       = "libfdata_stream_set_segment_data";
	off64_t segment_offset                      = 0;
	size64_t segment_size                       = 0;
	uint32_t segment_flags                      = 0;
	int cache_entry_index                       = 0;
	int number_of_cache_entries                 = 0;
	int segment_file_index                      = 0;

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

	if( segment_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid segment data size value exceeds maximum.",
		 function );

		return( -1 );
	}
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
	if( libfdata_range_get(
	     segment_data_range,
	     &segment_file_index,
	     &segment_offset,
	     &segment_size,
	     &segment_flags,
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
	if( segment_data_size != (size_t) segment_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment data size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_initialize(
	     &data_buffer,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data buffer.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_set_data(
	     data_buffer,
	     segment_data,
	     segment_data_size,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set segment data in data buffer.",
		 function );

		goto on_error;
	}
	if( libfcache_cache_get_number_of_entries(
	     cache,
	     &number_of_cache_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of cache entries.",
		 function );

		goto on_error;
	}
	if( number_of_cache_entries <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of cache entries value out of bounds.",
		 function );

		goto on_error;
	}
	cache_entry_index = libfdata_stream_calculate_cache_entry_index(
	                     segment_index,
	                     number_of_cache_entries );

	if( libfcache_cache_set_value_by_index(
	     cache,
	     cache_entry_index,
	     segment_file_index,
	     segment_offset,
	     internal_stream->timestamp,
	     (intptr_t *) data_buffer,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_buffer_free,
	     LIBFCACHE_CACHE_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value in cache entry: %d.",
		 function,
		 cache_entry_index );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_buffer != NULL )
	{
		libfdata_buffer_free(
		 &data_buffer,
		 NULL );
	}
	return( -1 );
}

/* Reads data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfdata_stream_read_buffer(
         libfdata_stream_t *stream,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         uint8_t *buffer,
         size_t buffer_size,
         uint8_t read_flags,
         libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	uint8_t *segment_data                       = NULL;
	static char *function                       = "libfdata_stream_read_buffer";
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
	if( ( internal_stream->data_offset < 0 )
	 || ( internal_stream->data_offset >= (off64_t) internal_stream->data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid stream - data offset: %" PRIi64 " value out of bounds: 0 - %" PRIu64 ".",
		 function,
		 internal_stream->data_offset,
		 internal_stream->data_size );

		return( -1 );
	}
	if( (off64_t) ( internal_stream->data_offset + buffer_size ) > (off64_t) internal_stream->data_size )
	{
		buffer_size = (size_t) ( internal_stream->data_size - internal_stream->data_offset );
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
		     read_flags,
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

/* Writes data in the buffer to the current offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfdata_stream_write_buffer(
         libfdata_stream_t *stream,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         const uint8_t *buffer,
         size_t buffer_size,
         uint8_t write_flags,
         libcerror_error_t **error )
{
/* TODO implement */
	return( -1 );
}

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libfdata_stream_seek_offset(
         libfdata_stream_t *stream,
         intptr_t *file_io_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_seek_offset";
	off64_t segment_data_offset                 = 0;
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
	if( whence == SEEK_CUR )
	{
		offset += internal_stream->data_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) internal_stream->data_size;
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
	if( offset < (off64_t) internal_stream->data_size )
	{
		if( libfdata_stream_get_segment_index_at_data_offset(
		     internal_stream,
		     offset,
		     &segment_index,
		     &segment_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment index at offset %" PRIi64 ".",
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

