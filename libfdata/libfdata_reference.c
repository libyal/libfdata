/*
 * Data reference functions
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

#include "libfdata_buffer.h"
#include "libfdata_definitions.h"
#include "libfdata_libcerror.h"
#include "libfdata_libfcache.h"
#include "libfdata_reference.h"
#include "libfdata_types.h"

/* Initializes the reference and its values
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_initialize(
     libfdata_reference_t **reference,
     intptr_t *data_handle,
     int (*free_data_handle)(
            intptr_t **data_handle,
            libcerror_error_t **error ),
     int (*clone_data_handle)(
            intptr_t **destination_data_handle,
            intptr_t *source_data_handle,
            libcerror_error_t **error ),
     int (*get_number_of_segments)(
            intptr_t *data_handle,
            int *number_of_segments,
            libcerror_error_t **error ),
     int (*get_size)(
            intptr_t *data_handle,
            size64_t *size,
            libcerror_error_t **error ),
     int (*get_data)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfcache_cache_t *cache,
            uint8_t **data,
            size_t *data_size,
            libcerror_error_t **error ),
     int (*get_segment_data)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfcache_cache_t *cache,
            int segment_index,
            uint8_t **data,
            size_t *data_size,
            uint8_t read_flags,
            libcerror_error_t **error ),
     int (*get_segment_data_at_offset)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfcache_cache_t *cache,
            off64_t data_offset,
            uint8_t **data,
            size_t *data_size,
            uint8_t read_flags,
            libcerror_error_t **error ),
     int (*get_segment_data_at_value_index)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfcache_cache_t *cache,
            int value_index,
            size_t value_size,
            uint8_t **data,
            size_t *data_size,
            uint8_t read_flags,
            libcerror_error_t **error ),
     ssize_t (*read_buffer)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                libfcache_cache_t *cache,
                uint8_t *buffer,
                size_t buffer_size,
                libcerror_error_t **error ),
     off64_t (*seek_offset)(
                intptr_t *data_handle,
                off64_t offset,
                int whence,
                libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_initialize";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	if( *reference != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid reference value already set.",
		 function );

		return( -1 );
	}
	if( free_data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid free data handle function.",
		 function );

		return( -1 );
	}
	internal_reference = memory_allocate_structure(
	                      libfdata_internal_reference_t );

	if( internal_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create reference.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_reference,
	     0,
	     sizeof( libfdata_internal_reference_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear reference.",
		 function );

		goto on_error;
	}
	internal_reference->data_handle                     = data_handle;
	internal_reference->free_data_handle                = free_data_handle;
	internal_reference->clone_data_handle               = clone_data_handle;
	internal_reference->get_number_of_segments          = get_number_of_segments;
	internal_reference->get_size                        = get_size;
	internal_reference->get_data                        = get_data;
	internal_reference->get_segment_data                = get_segment_data;
	internal_reference->get_segment_data_at_offset      = get_segment_data_at_offset;
	internal_reference->get_segment_data_at_value_index = get_segment_data_at_value_index;
	internal_reference->read_buffer                     = read_buffer;
	internal_reference->seek_offset                     = seek_offset;
	internal_reference->flags                           = flags;

	*reference = (libfdata_reference_t *) internal_reference;

	return( 1 );

on_error:
	if( internal_reference != NULL )
	{
		memory_free(
		 internal_reference );
	}
	return( -1 );
}

/* Frees the reference and its values
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_free(
     libfdata_reference_t **reference,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_free";
	int result                                        = 1;

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	if( *reference != NULL )
	{
		internal_reference = (libfdata_internal_reference_t *) *reference;
		*reference         = NULL;

		if( internal_reference->data_handle != NULL )
		{
			if( internal_reference->free_data_handle == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid reference - missing free data handle function.",
				 function );

				result = -1;
			}
			else if( internal_reference->free_data_handle(
			          &( internal_reference->data_handle ),
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
		memory_free(
		 internal_reference );
	}
	return( result );
}

/* Clones the source reference to the destination
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_clone(
     libfdata_reference_t **destination_reference,
     libfdata_reference_t *source_reference,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_source_reference = NULL;
	intptr_t *destination_data_handle                        = NULL;
	static char *function                                    = "libfdata_reference_clone";

	if( destination_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination reference.",
		 function );

		return( -1 );
	}
	if( *destination_reference != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination reference value already set.",
		 function );

		return( -1 );
	}
	if( source_reference == NULL )
	{
		*destination_reference = NULL;

		return( 1 );
	}
	internal_source_reference = (libfdata_internal_reference_t *) source_reference;

	if( internal_source_reference->free_data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid source reference - missing free data handle function.",
		 function );

		goto on_error;
	}
	if( internal_source_reference->clone_data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid source reference - missing clone data handle function.",
		 function );

		goto on_error;
	}
	if( internal_source_reference->clone_data_handle(
	     &destination_data_handle,
	     internal_source_reference->data_handle,
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
	if( libfdata_reference_initialize(
	     destination_reference,
	     destination_data_handle,
	     internal_source_reference->free_data_handle,
	     internal_source_reference->clone_data_handle,
	     internal_source_reference->get_number_of_segments,
	     internal_source_reference->get_size,
	     internal_source_reference->get_data,
	     internal_source_reference->get_segment_data,
	     internal_source_reference->get_segment_data_at_offset,
	     internal_source_reference->get_segment_data_at_value_index,
	     internal_source_reference->read_buffer,
	     internal_source_reference->seek_offset,
	     LIBFDATA_REFERENCE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create destination reference.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( destination_data_handle != NULL )
	{
		internal_source_reference->free_data_handle(
		 &destination_data_handle,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the data handle
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_get_data_handle(
     libfdata_reference_t *reference,
     intptr_t **data_handle,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_get_data_handle";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	*data_handle = internal_reference->data_handle;

	return( 1 );
}

/* Segment functions
 */

/* Retrieves the number of segments
 * The number of segments is 0 when there is no data
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_get_number_of_segments(
     libfdata_reference_t *reference,
     int *number_of_segments,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_get_number_of_segments";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( internal_reference->data_handle == NULL )
	{
		if( number_of_segments == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid number of segments.",
			 function );

			return( -1 );
		}
		*number_of_segments = 0;
	}
	else
	{
		if( internal_reference->get_number_of_segments == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid reference - missing get number of segments function.",
			 function );

			return( -1 );
		}
		if( internal_reference->get_number_of_segments(
		     internal_reference->data_handle,
		     number_of_segments,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of segments.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Data functions
 */

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_get_size(
     libfdata_reference_t *reference,
     size64_t *size,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_get_size";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( internal_reference->get_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid reference - missing get size function.",
		 function );

		return( -1 );
	}
	if( internal_reference->get_size(
	     internal_reference->data_handle,
	     size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_get_data(
     libfdata_reference_t *reference,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_get_data";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( internal_reference->get_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid reference - missing get data function.",
		 function );

		return( -1 );
	}
	if( internal_reference->get_data(
	     internal_reference->data_handle,
	     file_io_handle,
	     cache,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the segment data of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_get_segment_data(
     libfdata_reference_t *reference,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_get_segment_data";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( internal_reference->get_segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid reference - missing get segment data function.",
		 function );

		return( -1 );
	}
	if( internal_reference->get_segment_data(
	     internal_reference->data_handle,
	     file_io_handle,
	     cache,
	     segment_index,
	     data,
	     data_size,
	     read_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data of segment: %d.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the segment data at a certain offset
 * The data size set to the remaining size in the corresponding segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_get_segment_data_at_offset(
     libfdata_reference_t *reference,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     off64_t data_offset,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_get_segment_data_at_offset";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( internal_reference->get_segment_data_at_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid reference - missing get segment data at offset function.",
		 function );

		return( -1 );
	}
	if( internal_reference->get_segment_data_at_offset(
	     internal_reference->data_handle,
	     file_io_handle,
	     cache,
	     data_offset,
	     data,
	     data_size,
	     read_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment data at offset %" PRIi64 ".",
		 function,
		 data_offset );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the segment data at a value index
 * The data size set to the remaining size in the corresponding segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_reference_get_segment_data_at_value_index(
     libfdata_reference_t *reference,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int value_index,
     size_t value_size,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_get_segment_data_at_value_index";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( internal_reference->get_segment_data_at_value_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid reference - missing get segment data at value index function.",
		 function );

		return( -1 );
	}
	if( internal_reference->get_segment_data_at_value_index(
	     internal_reference->data_handle,
	     file_io_handle,
	     cache,
	     value_index,
	     value_size,
	     data,
	     data_size,
	     read_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment data at value index.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* IO functions
 */

/* Reads data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfdata_reference_read_buffer(
         libfdata_reference_t *reference,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_read_buffer";
	ssize_t read_count                                = 0;

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( internal_reference->read_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid reference - missing read buffer function.",
		 function );

		return( -1 );
	}
	read_count = internal_reference->read_buffer(
		      internal_reference->data_handle,
		      file_io_handle,
		      cache,
		      buffer,
		      buffer_size,
		      error );

	if( read_count != (ssize_t) buffer_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libfdata_reference_seek_offset(
         libfdata_reference_t *reference,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libfdata_internal_reference_t *internal_reference = NULL;
	static char *function                             = "libfdata_reference_seek_offset";

	if( reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reference.",
		 function );

		return( -1 );
	}
	internal_reference = (libfdata_internal_reference_t *) reference;

	if( internal_reference->seek_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid reference - missing seek offset function.",
		 function );

		return( -1 );
	}
	offset = internal_reference->seek_offset(
		  internal_reference->data_handle,
		  offset,
		  whence,
		  error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	return( offset );
}

