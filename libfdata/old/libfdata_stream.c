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
#include "libfdata_libbfio.h"
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
	if( libfdata_list_initialize(
	     &( internal_stream->segments_list ),
	     (intptr_t *) internal_stream,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_list_element_t *, libfcache_cache_t *, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libfdata_stream_read_element_data,
	     NULL,
	     LIBFDATA_FLAG_DATA_HANDLE_NON_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create segments list.",
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

		if( libfdata_list_free(
		     &( internal_stream->segments_list ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the segments list.",
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

	if( libfdata_list_clone_elements(
	     ( (libfdata_internal_stream_t *) *destination_stream )->segments_list,
	     internal_source_stream->segments_list,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy stream segment list elements.",
		 function );

		goto on_error;
	}
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

	if( libfdata_list_resize(
	     internal_stream->segments_list,
	     number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize segments list.",
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

	if( libfdata_list_get_number_of_elements(
	     internal_stream->segments_list,
	     number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from segments list.",
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

	if( libfdata_list_get_element_by_index(
	     internal_stream->segments_list,
	     segment_index,
	     &segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element: %d from segments list.",
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
		 "%s: unable to retrieve segment: %d.",
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
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_set_segment_by_index";

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

	if( libfdata_list_set_element_by_index(
	     internal_stream->segments_list,
	     segment_index,
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
		 "%s: unable to set element: %d in segments list.",
		 function,
		 segment_index );

		return( -1 );
	}
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

	if( libfdata_list_append_element(
	     internal_stream->segments_list,
	     segment_index,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append element to segments list.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the offset and size of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_set_segment_value_size(
     libfdata_stream_t *stream,
     int segment_index,
     size64_t value_size,
     libcerror_error_t **error )
{
	libfdata_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libfdata_stream_set_segment_value_size";

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

/*TODO
	if( libfdata_list_set_element_value_size(
	     internal_stream->segments_list,
	     segment_index,
	     value_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set element: %d value size.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( 1 );
*/
	return( -1 );
}

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_data_size(
     libfdata_stream_t *stream,
     size64_t *size,
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

	if( libfdata_list_get_data_size(
	     internal_stream->segments_list,
	     size,
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
	return( 1 );
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
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer              = NULL;
	libfcache_cache_value_t *cache_value        = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	libfdata_list_element_t *segment            = NULL;
	uint8_t *data_buffer_data                   = NULL;
	static char *function                       = "libfdata_stream_get_data";
	off64_t segment_offset                      = 0;
	size64_t data_stream_size                   = 0;
	size64_t segment_size                       = 0;
	size_t data_buffer_size                     = 0;
	size_t data_offset                          = 0;
	ssize_t read_count                          = 0;
	uint32_t segment_flags                      = 0;
	int number_of_cache_values                  = 0;
	int number_of_segments                      = 0;
	int segment_index                           = 0;
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
	/* Check if all data has been cached in a single cache value
	 */
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

		return( -1 );
	}
	if( number_of_cache_values == 1 )
	{
		if( libfcache_cache_get_value_by_index(
		     cache,
		     0,
		     &cache_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( cache_value != NULL )
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
			 "%s: unable to retrieve data buffer from cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( data_buffer != NULL )
	{
		if( libfdata_buffer_get_data_size(
		     data_buffer,
		     &data_buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data buffer size.",
			 function );

			return( -1 );
		}
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
	/* Read all the data in a single cache value
	 */
	if( ( number_of_cache_values != 1 )
	 || ( cache_value == NULL )
	 || ( data_buffer == NULL )
	 || ( data_stream_size != (size64_t) data_buffer_size ) )
	{
		if( data_stream_size > (size64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid data stream size value exceeds maximum.",
			 function );

			return( -1 );
		}
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

		if( libfdata_buffer_initialize(
		     &data_buffer,
		     (size_t) data_stream_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create data buffer.",
			 function );

			return( -1 );
		}
		if( libfdata_buffer_get_data(
		     data_buffer,
		     &data_buffer_data,
		     &data_buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer.",
			 function );

			libfdata_buffer_free(
			 &data_buffer,
			 NULL );

			return( -1 );
		}
		if( data_buffer_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing data buffer data.",
			 function );

			libfdata_buffer_free(
			 &data_buffer,
			 NULL );

			return( -1 );
		}
		if( libfdata_list_get_number_of_elements(
		     internal_stream->segments_list,
		     &number_of_segments,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements from segments list.",
			 function );

			libfdata_buffer_free(
			 &data_buffer,
			 NULL );

			return( -1 );
		}
		/* Read all the segment data into the data buffer
		 */
		for( segment_index = 0;
		     segment_index < number_of_segments;
		     segment_index++ )
		{
			if( libfdata_list_get_element_by_index(
			     internal_stream->segments_list,
			     segment_index,
			     &segment,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve element: %d from segments list.",
				 function,
				 segment_index );

				libfdata_buffer_free(
				 &data_buffer,
				 NULL );

				return( -1 );
			}
			if( libfdata_list_element_get_data_range(
			     segment,
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
				 "%s: unable to retrieve segment: %d.",
				 function,
				 segment_index );

				libfdata_buffer_free(
				 &data_buffer,
				 NULL );

				return( -1 );
			}
			if( libbfio_handle_seek_offset(
			     (libbfio_handle_t *) file_io_handle,
			     segment_offset,
			     SEEK_SET,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_SEEK_FAILED,
				 "%s: unable to seek segment offset: %" PRIi64 ".",
				 function,
				 segment_offset );

				libfdata_buffer_free(
				 &data_buffer,
				 NULL );

				return( -1 );
			}
			read_count = internal_stream->read_segment_data(
				      internal_stream->data_handle,
				      file_io_handle,
				      segment_index,
				      &( data_buffer_data[ data_offset ] ),
				      (size_t) segment_size,
				      0,
				      error );

			if( read_count != (ssize_t) segment_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read segment data: %d.",
				 function,
				 segment_index );

				libfdata_buffer_free(
				 &data_buffer,
				 NULL );

				return( -1 );
			}
			data_offset += (size_t) read_count;
		}
		if( libfcache_cache_set_value_by_index(
		     cache,
		     0,
		     0,
		     0,
		     libfcache_date_time_get_timestamp(),
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

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the segment data and size of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_segment_data(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer              = NULL;
	libfcache_cache_value_t *cache_value        = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	libfdata_list_element_t *segment            = NULL;
	static char *function                       = "libfdata_stream_get_segment_data";
	off64_t segment_offset                      = 0;
	off64_t segment_value_offset                = 0;
	size64_t data_stream_size                   = 0;
	size64_t segment_size                       = 0;
	size_t data_buffer_size                     = 0;
	uint32_t segment_flags                      = 0;
	int number_of_cache_values                  = 0;
	int segment_file_index                     = 0;

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

	/* Check if all data has been cached in a single cache value
	 */
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

		return( -1 );
	}
	if( number_of_cache_values == 1 )
	{
		if( libfcache_cache_get_value_by_index(
		     cache,
		     0,
		     &cache_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( cache_value != NULL )
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
			 "%s: unable to retrieve data buffer from cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( data_buffer != NULL )
	{
		if( libfdata_buffer_get_data_size(
		     data_buffer,
		     &data_buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data buffer size.",
			 function );

			return( -1 );
		}
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
	if( ( ( (libfdata_internal_list_t *) internal_stream->segments_list )->flags & LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES ) != 0 )
	{
		if( libfdata_list_calculate_value_offsets(
		     (libfdata_internal_list_t *) internal_stream->segments_list,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to calculate value offsets.",
			 function );

			return( -1 );
		}
	}
	/* All the data has been cached in a single cache value
	 */
	if( data_stream_size == (size64_t) data_buffer_size )
	{
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
		if( libfdata_list_get_element_by_index(
		     internal_stream->segments_list,
		     segment_index,
		     &segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     segment,
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
			 "%s: unable to retrieve segment: %d.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_get_value_offset(
		     segment,
		     &segment_value_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d data offset.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( segment_value_offset > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid segment value offset value exceeds maximum.",
			 function );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     (size_t) segment_value_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIi64 ".",
			 function,
			 segment_value_offset );

			return( -1 );
		}
		if( segment_size > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid segment size value exceeds maximum.",
			 function );

			return( -1 );
		}
		*data_size = (size_t) segment_size;
	}
	else
	{
		if( libfdata_list_get_element_value_by_index(
		     internal_stream->segments_list,
		     (intptr_t *) file_io_handle,
		     cache,
		     segment_index,
		     (intptr_t **) &data_buffer,
		     read_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element value: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
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

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the segment data and size at a certain offset
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_segment_data_at_offset(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     off64_t data_offset,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer              = NULL;
	libfcache_cache_value_t *cache_value        = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	libfdata_list_element_t *segment            = NULL;
	static char *function                       = "libfdata_stream_get_segment_data_at_offset";
	off64_t segment_offset                      = 0;
	size64_t data_stream_size                   = 0;
	size64_t segment_size                       = 0;
	size_t data_buffer_size                     = 0;
	size_t segment_data_offset                  = 0;
	uint32_t segment_flags                      = 0;
	int number_of_cache_values                  = 0;
	int segment_index                           = 0;
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

	if( libfdata_list_get_element_index_at_value_offset(
	     internal_stream->segments_list,
	     data_offset,
	     &segment_index,
	     &segment_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index at offset: %" PRIi64 ".",
		 function,
		 data_offset );

		return( -1 );
	}
	/* Check if all data has been cached in a single cache value
	 */
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

		return( -1 );
	}
	if( number_of_cache_values == 1 )
	{
		if( libfcache_cache_get_value_by_index(
		     cache,
		     0,
		     &cache_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( cache_value != NULL )
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
			 "%s: unable to retrieve data buffer from cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( data_buffer != NULL )
	{
		if( libfdata_buffer_get_data_size(
		     data_buffer,
		     &data_buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data buffer size.",
			 function );

			return( -1 );
		}
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
	/* All the data has been cached in a single cache value
	 */
	if( data_stream_size == (size64_t) data_buffer_size )
	{
		if( data_offset > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid data offset value exceeds maximum.",
			 function );

			return( -1 );
		}
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
		if( libfdata_list_get_element_by_index(
		     internal_stream->segments_list,
		     segment_index,
		     &segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     segment,
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
			 "%s: unable to retrieve segment: %d.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     (size_t) data_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIi64 ".",
			 function,
			 data_offset );

			return( -1 );
		}
		if( segment_data_offset > segment_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: segment data offset value exceeds segment size.",
			 function );

			return( -1 );
		}
		if( ( segment_size - segment_data_offset ) > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid data size value exceeds maximum.",
			 function );

			return( -1 );
		}
		*data_size = (size_t) ( segment_size - segment_data_offset );
	}
	else
	{
		if( libfdata_list_get_element_value_by_index(
		     internal_stream->segments_list,
		     (intptr_t *) file_io_handle,
		     cache,
		     segment_index,
		     (intptr_t **) &data_buffer,
		     read_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element value: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     segment_data_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIzd ".",
			 function,
			 segment_data_offset );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the segment data and size at a specific value index
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_get_segment_data_at_value_index(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int value_index,
     size_t value_size,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer              = NULL;
	libfcache_cache_value_t *cache_value        = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	libfdata_list_element_t *segment            = NULL;
	static char *function                       = "libfdata_stream_get_segment_data_at_value_index";
	off64_t segment_offset                      = 0;
	off64_t segment_value_offset                = 0;
	size64_t data_stream_size                   = 0;
	size64_t segment_size                       = 0;
	size_t data_buffer_size                     = 0;
	size_t segment_data_offset                  = 0;
	uint32_t segment_flags                      = 0;
	int number_of_cache_values                  = 0;
	int segment_index                           = 0;
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

	if( libfdata_list_get_element_index_at_value_index(
	     internal_stream->segments_list,
	     value_index,
	     value_size,
	     &segment_index,
	     &segment_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index at value index: %d for value size: %" PRIzd ".",
		 function,
		 value_index,
		 value_size );

		return( -1 );
	}
	/* Check if all data has been cached in a single cache value
	 */
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

		return( -1 );
	}
	if( number_of_cache_values == 1 )
	{
		if( libfcache_cache_get_value_by_index(
		     cache,
		     0,
		     &cache_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( cache_value != NULL )
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
			 "%s: unable to retrieve data buffer from cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( data_buffer != NULL )
	{
		if( libfdata_buffer_get_data_size(
		     data_buffer,
		     &data_buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data buffer size.",
			 function );

			return( -1 );
		}
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
	/* All the data has been cached in a single cache value
	 */
	if( data_stream_size == (size64_t) data_buffer_size )
	{
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
		if( libfdata_list_get_element_by_index(
		     internal_stream->segments_list,
		     segment_index,
		     &segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     segment,
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
			 "%s: unable to retrieve segment: %d.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_get_value_offset(
		     segment,
		     &segment_value_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d data offset.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( segment_value_offset > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid segment value offset value exceeds maximum.",
			 function );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     (size_t) segment_value_offset + segment_data_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIi64 ".",
			 function,
			 segment_value_offset + segment_data_offset );

			return( -1 );
		}
		if( segment_data_offset > segment_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: segment data offset value exceeds segment size.",
			 function );

			return( -1 );
		}
		if( ( segment_size - segment_data_offset ) > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid data size value exceeds maximum.",
			 function );

			return( -1 );
		}
		*data_size = (size_t) ( segment_size - segment_data_offset );
	}
	else
	{
		if( libfdata_list_get_element_value_by_index(
		     internal_stream->segments_list,
		     (intptr_t *) file_io_handle,
		     cache,
		     segment_index,
		     (intptr_t **) &data_buffer,
		     read_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element value: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     segment_data_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIzd ".",
			 function,
			 segment_data_offset );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the reference and size of the data of a specific segment
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
     uint8_t *data,
     size_t data_size,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer              = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	libfdata_list_element_t *segment            = NULL;
	static char *function                       = "libfdata_stream_set_segment_data";
	off64_t segment_offset                      = 0;
	size64_t segment_size                       = 0;
	uint32_t segment_flags                      = 0;
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

	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfdata_list_get_element_by_index(
	     internal_stream->segments_list,
	     segment_index,
	     &segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element: %d from segments list.",
		 function,
		 segment_index );

		goto on_error;
	}
	if( libfdata_list_element_get_data_range(
	     segment,
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
		 "%s: unable to retrieve segment: %d.",
		 function,
		 segment_index );

		goto on_error;
	}
	if( data_size != (size_t) segment_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: mismatch between data size and segment size.",
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
	     data,
	     data_size,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data buffer data.",
		 function );

		goto on_error;
	}
	if( libfdata_list_set_element_value_by_index(
	     internal_stream->segments_list,
	     cache,
	     segment_index,
	     (intptr_t *) data_buffer,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_buffer_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set element value: %d in segments list.",
		 function,
		 segment_index );

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

/* Reads the element data into a data buffer
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_read_element_data(
     intptr_t *data_handle,
     intptr_t *file_io_handle,
     libfdata_list_element_t *list_element,
     libfcache_cache_t *cache,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags LIBFDATA_ATTRIBUTE_UNUSED,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer              = NULL;
	libfdata_internal_stream_t *internal_stream = NULL;
	uint8_t *data_buffer_data                   = NULL;
	static char *function                       = "libfdata_stream_read_element_data";
	size_t data_buffer_size                     = 0;
	ssize_t read_count                          = 0;
	int segment_index                           = 0;

	LIBFDATA_UNREFERENCED_PARAMETER( element_data_flags )

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data stream data handle.",
		 function );

		return( -1 );
	}
	internal_stream = (libfdata_internal_stream_t *) data_handle;

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
	if( element_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfdata_list_element_get_element_index(
	     list_element,
	     &segment_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index from list element.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_initialize(
	     &data_buffer,
	     (size_t) element_data_size,
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
	     data_buffer,
	     &data_buffer_data,
	     &data_buffer_size,
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
	if( libbfio_handle_seek_offset(
	     (libbfio_handle_t *) file_io_handle,
	     element_data_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek element data offset: %" PRIi64 ".",
		 function,
		 element_data_offset );

		goto on_error;
	}
	read_count = internal_stream->read_segment_data(
		      internal_stream->data_handle,
		      file_io_handle,
		      segment_index,
		      data_buffer_data,
		      (size_t) element_data_size,
		      read_flags,
		      error );

	if( read_count != (ssize_t) element_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read element data: %d.",
		 function,
		 segment_index );

		goto on_error;
	}
	if( libfdata_list_element_set_element_value(
	     list_element,
	     cache,
	     (intptr_t *) data_buffer,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_buffer_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set element value in list element.",
		 function );

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

/* Reads the segment data into the buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfdata_stream_read_segment_data(
         intptr_t *data_handle LIBFDATA_ATTRIBUTE_UNUSED,
         intptr_t *file_io_handle,
         int segment_index LIBFDATA_ATTRIBUTE_UNUSED,
         uint8_t *data,
         size_t data_size,
         uint8_t read_flags LIBFDATA_ATTRIBUTE_UNUSED,
         libcerror_error_t **error )
{
	static char *function = "libfdata_stream_read_segment_data";
	ssize_t read_count    = 0;

	LIBFDATA_UNREFERENCED_PARAMETER( data_handle )
	LIBFDATA_UNREFERENCED_PARAMETER( segment_index )
	LIBFDATA_UNREFERENCED_PARAMETER( read_flags )

	read_count = libbfio_handle_read_buffer(
		      (libbfio_handle_t *) file_io_handle,
		      data,
		      data_size,
		      error );

	if( read_count != (ssize_t) data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment data.",
		 function );

		return( -1 );
	}
	return( read_count );
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

