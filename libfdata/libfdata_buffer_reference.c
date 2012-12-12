/*
 * Buffer data reference functions
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

#include "libfdata_buffer.h"
#include "libfdata_buffer_reference.h"
#include "libfdata_definitions.h"
#include "libfdata_libcerror.h"
#include "libfdata_libcnotify.h"
#include "libfdata_libfcache.h"
#include "libfdata_reference.h"
#include "libfdata_types.h"
#include "libfdata_unused.h"

/* Initializes the buffer reference and its values
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_initialize(
     libfdata_reference_t **reference,
     const uint8_t *buffer,
     size_t buffer_size,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_buffer_reference_t *buffer_reference = NULL;
	static char *function                         = "libfdata_buffer_reference_initialize";

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
	if( *reference == NULL )
	{
		buffer_reference = memory_allocate_structure(
		                    libfdata_buffer_reference_t );

		if( buffer_reference == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create buffer reference.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     buffer_reference,
		     0,
		     sizeof( libfdata_buffer_reference_t ) ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear buffer reference.",
			 function );

			memory_free(
			 buffer_reference );

			return( -1 );
		}
		if( ( flags & LIBFDATA_BUFFER_DATA_FLAG_MANAGED ) != 0 )
		{
			buffer_reference->data = (uint8_t *) buffer;
		}
		else if( buffer == NULL )
		{
			buffer_reference->data = NULL;
		}
		else if( buffer_size > 0 )
		{
			buffer_reference->data = (uint8_t *) memory_allocate(
			                                      sizeof( uint8_t ) * buffer_size );

			if( buffer_reference->data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create data.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     buffer_reference->data,
			     buffer,
			     buffer_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy data.",
				 function );

				goto on_error;
			}
			buffer_reference->flags |= LIBFDATA_BUFFER_DATA_FLAG_MANAGED;
		}
		buffer_reference->data_size = buffer_size;
		buffer_reference->flags    |= flags;

		if( libfdata_reference_initialize(
		     reference,
		     (intptr_t *) buffer_reference,
		     (int (*)(intptr_t **, libcerror_error_t **))
		          libfdata_buffer_reference_free,
		     (int (*)(intptr_t **, intptr_t *, libcerror_error_t **))
		          libfdata_buffer_reference_clone,
		     (int (*)(intptr_t *, int *, libcerror_error_t **))
		          libfdata_buffer_reference_get_number_of_segments,
		     (int (*)(intptr_t *, size64_t *, libcerror_error_t **))
		          libfdata_buffer_reference_get_size,
		     (int (*)(intptr_t *, intptr_t *, libfcache_cache_t *, uint8_t **, size_t *, libcerror_error_t **))
		          libfdata_buffer_reference_get_data,
		     (int (*)(intptr_t *, intptr_t *, libfcache_cache_t *, int, uint8_t **, size_t *, uint8_t, libcerror_error_t **))
		          libfdata_buffer_reference_get_segment_data,
		     (int (*)(intptr_t *, intptr_t *, libfcache_cache_t *, off64_t, uint8_t **, size_t *, uint8_t, libcerror_error_t **))
		          libfdata_buffer_reference_get_segment_data_at_offset,
		     (int (*)(intptr_t *, intptr_t *, libfcache_cache_t *, int, size_t, uint8_t **, size_t *, uint8_t, libcerror_error_t **))
		          libfdata_buffer_reference_get_segment_data_at_value_index,
		     (ssize_t (*)(intptr_t *, intptr_t *, libfcache_cache_t *, uint8_t *, size_t, libcerror_error_t **))
		          libfdata_buffer_reference_read_buffer,
		     (off64_t (*)(intptr_t *, off64_t, int, libcerror_error_t **))
		          libfdata_buffer_reference_seek_offset,
		     LIBFDATA_REFERENCE_FLAG_MANAGED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create reference.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( buffer_reference != NULL )
	{
		if( ( flags & LIBFDATA_BUFFER_DATA_FLAG_MANAGED ) == 0 )
		{
			if( buffer_reference->data != NULL )
			{
				memory_free(
				 buffer_reference->data );
			}
		}
		memory_free(
		 buffer_reference );
	}
	return( -1 );
}

/* Frees the buffer reference and its values
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_free(
     libfdata_buffer_reference_t **buffer_reference,
     libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_free";

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
		 function );

		return( -1 );
	}
	if( *buffer_reference != NULL )
	{
		if( ( ( *buffer_reference )->flags & LIBFDATA_BUFFER_DATA_FLAG_MANAGED ) != 0 )
		{
			if( ( *buffer_reference )->data != NULL )
			{
				memory_free(
				 ( *buffer_reference )->data );
			}
		}
		memory_free(
		 *buffer_reference );

		*buffer_reference = NULL;
	}
	return( 1 );
}

/* Clones the source buffer_reference to the destination
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_clone(
     libfdata_buffer_reference_t **destination_buffer_reference,
     libfdata_buffer_reference_t *source_buffer_reference,
     libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_clone";

	if( destination_buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination buffer reference.",
		 function );

		return( -1 );
	}
	if( *destination_buffer_reference != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination buffer reference value already set.",
		 function );

		return( -1 );
	}
	if( source_buffer_reference == NULL )
	{
		*destination_buffer_reference = NULL;

		return( 1 );
	}
	*destination_buffer_reference = memory_allocate_structure(
	                                 libfdata_buffer_reference_t );

	if( *destination_buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination buffer reference.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *destination_buffer_reference,
	     0,
	     sizeof( libfdata_buffer_reference_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear destinatino buffer reference.",
		 function );

		memory_free(
		 *destination_buffer_reference );

		*destination_buffer_reference = NULL;

		return( -1 );
	}
	if( source_buffer_reference->data_size > 0 )
	{
		( *destination_buffer_reference )->data = (uint8_t *) memory_allocate(
		                                                       sizeof( uint8_t ) * source_buffer_reference->data_size );

		if( ( *destination_buffer_reference )->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     ( *destination_buffer_reference )->data,
		     source_buffer_reference->data,
		     source_buffer_reference->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy data.",
			 function );

			goto on_error;
		}
		( *destination_buffer_reference )->flags |= LIBFDATA_BUFFER_DATA_FLAG_MANAGED;
	}
	( *destination_buffer_reference )->data_size = source_buffer_reference->data_size;
	( *destination_buffer_reference )->flags    |= source_buffer_reference->flags;

	return( 1 );

on_error:
	if( *destination_buffer_reference != NULL )
	{
		if( ( *destination_buffer_reference )->data != NULL )
		{
			memory_free(
			 ( *destination_buffer_reference )->data );
		}
		memory_free(
		 *destination_buffer_reference );

		*destination_buffer_reference = NULL;
	}
	return( -1 );
}

/* Segment functions
 */

/* Retrieves the number of segments
 * The number of segments is 0 when there is no data
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_get_number_of_segments(
     libfdata_buffer_reference_t *buffer_reference,
     int *number_of_segments,
     libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_get_number_of_segments";

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
		 function );

		return( -1 );
	}
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
	if( buffer_reference->data != NULL )
	{
		*number_of_segments = 1;
	}
	else
	{
		*number_of_segments = 0;
	}
	return( 1 );
}

/* Data functions
 */

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_get_size(
     libfdata_buffer_reference_t *buffer_reference,
     size64_t *size,
     libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_get_size";

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = (size64_t) buffer_reference->data_size;

	return( 1 );
}

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_get_data(
     libfdata_buffer_reference_t *buffer_reference,
     intptr_t *file_io_handle LIBFDATA_ATTRIBUTE_UNUSED,
     libfcache_cache_t *cache LIBFDATA_ATTRIBUTE_UNUSED,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_get_data";

	LIBFDATA_UNREFERENCED_PARAMETER( file_io_handle )
	LIBFDATA_UNREFERENCED_PARAMETER( cache )

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
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
	*data      = buffer_reference->data;
	*data_size = buffer_reference->data_size;

	return( 1 );
}

/* Retrieves the segment data of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_get_segment_data(
     libfdata_buffer_reference_t *buffer_reference,
     intptr_t *file_io_handle LIBFDATA_ATTRIBUTE_UNUSED,
     libfcache_cache_t *cache LIBFDATA_ATTRIBUTE_UNUSED,
     int segment_index,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags LIBFDATA_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_get_segment_data";

	LIBFDATA_UNREFERENCED_PARAMETER( file_io_handle )
	LIBFDATA_UNREFERENCED_PARAMETER( cache )
	LIBFDATA_UNREFERENCED_PARAMETER( read_flags )

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
		 function );

		return( -1 );
	}
	if( segment_index != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment value out of bounds.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
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
	*data      = buffer_reference->data;
	*data_size = buffer_reference->data_size;

	return( 1 );
}

/* Retrieves the segment data at a certain offset
 * The data size set to the remaining size in the corresponding segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_get_segment_data_at_offset(
     libfdata_buffer_reference_t *buffer_reference,
     intptr_t *file_io_handle LIBFDATA_ATTRIBUTE_UNUSED,
     libfcache_cache_t *cache LIBFDATA_ATTRIBUTE_UNUSED,
     off64_t data_offset,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags LIBFDATA_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_get_segment_data_at_offset";

	LIBFDATA_UNREFERENCED_PARAMETER( file_io_handle )
	LIBFDATA_UNREFERENCED_PARAMETER( cache )
	LIBFDATA_UNREFERENCED_PARAMETER( read_flags )

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
		 function );

		return( -1 );
	}
	if( buffer_reference->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid buffer reference - missing data.",
		 function );

		return( -1 );
	}
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
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
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
	if( data_offset >= (off64_t) buffer_reference->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value exceeds segment data size.",
		 function );

		return( -1 );
	}
	*data      = &( ( buffer_reference->data )[ data_offset ] );
	*data_size = buffer_reference->data_size - (size_t) data_offset;

	return( 1 );
}

/* Retrieves the segment data at a value index
 * The data size set to the remaining size in the corresponding segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_reference_get_segment_data_at_value_index(
     libfdata_buffer_reference_t *buffer_reference,
     intptr_t *file_io_handle LIBFDATA_ATTRIBUTE_UNUSED,
     libfcache_cache_t *cache LIBFDATA_ATTRIBUTE_UNUSED,
     int value_index,
     size_t value_size,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags LIBFDATA_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	static char *function      = "libfdata_buffer_reference_get_segment_data_at_value_index";
	size_t segment_data_offset = 0;

	LIBFDATA_UNREFERENCED_PARAMETER( file_io_handle )
	LIBFDATA_UNREFERENCED_PARAMETER( cache )
	LIBFDATA_UNREFERENCED_PARAMETER( read_flags )

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
		 function );

		return( -1 );
	}
	if( buffer_reference->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid buffer reference - missing data.",
		 function );

		return( -1 );
	}
	if( value_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid value index value out of bounds.",
		 function );

		return( -1 );
	}
	if( value_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid value size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
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
	segment_data_offset = value_size * (size_t) value_index;

	if( segment_data_offset >= buffer_reference->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment data offset value exceeds segment data size.",
		 function );

		return( -1 );
	}
	*data      = &( ( buffer_reference->data )[ segment_data_offset ] );
	*data_size = buffer_reference->data_size - segment_data_offset;

	return( 1 );
}

/* IO functions
 */

/* Reads data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfdata_buffer_reference_read_buffer(
         libfdata_buffer_reference_t *buffer_reference,
         intptr_t *file_io_handle LIBFDATA_ATTRIBUTE_UNUSED,
         libfcache_cache_t *cache LIBFDATA_ATTRIBUTE_UNUSED,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_read_buffer";

	LIBFDATA_UNREFERENCED_PARAMETER( file_io_handle )
	LIBFDATA_UNREFERENCED_PARAMETER( cache )

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
		 function );

		return( -1 );
	}
	if( ( buffer_reference->data_offset < 0 )
	 || ( buffer_reference->data_offset >= (off64_t) buffer_reference->data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( (off64_t) ( buffer_reference->data_offset + buffer_size ) > (off64_t) buffer_reference->data_size )
	{
		buffer_size = buffer_reference->data_size - (size_t) buffer_reference->data_offset;
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
	if( memory_copy(
	     buffer,
	     buffer_reference->data,
	     buffer_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data to buffer.",
		 function );

		return( -1 );
	}
	buffer_reference->data_offset += buffer_size;

	return( (ssize_t) buffer_size );
}

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libfdata_buffer_reference_seek_offset(
         libfdata_buffer_reference_t *buffer_reference,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	static char *function = "libfdata_buffer_reference_seek_offset";

	if( buffer_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer reference.",
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
		offset += buffer_reference->data_offset;
	}
	else if( whence == SEEK_END )
	{	
		offset += (off64_t) buffer_reference->data_size;
	}
#if defined( HAVE_DEBUG_OUTPUT )
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
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	buffer_reference->data_offset = offset;

	return( offset );
}

