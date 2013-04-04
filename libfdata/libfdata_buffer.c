/*
 * Buffer functions
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

/* Creates a buffer
 * Make sure the value buffer is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_initialize(
     libfdata_buffer_t **buffer,
     size_t size,
     libcerror_error_t **error )
{
	libfdata_internal_buffer_t *internal_buffer = NULL;
	static char *function                       = "libfdata_buffer_initialize";

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
	if( *buffer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid buffer value already set.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	internal_buffer = memory_allocate_structure(
	                   libfdata_internal_buffer_t );

	if( internal_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create buffer.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_buffer,
	     0,
	     sizeof( libfdata_internal_buffer_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear buffer.",
		 function );

		goto on_error;
	}
	if( size > 0 )
	{
		internal_buffer->data = (uint8_t *) memory_allocate(
						     sizeof( uint8_t ) * size );

		if( internal_buffer->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create buffer data.",
			 function );

			goto on_error;
		}
		internal_buffer->data_size = size;
		internal_buffer->flags     = LIBFDATA_BUFFER_DATA_FLAG_MANAGED;
	}
	*buffer = (libfdata_buffer_t *) internal_buffer;

	return( 1 );

on_error:
	if( internal_buffer != NULL )
	{
		memory_free(
		 internal_buffer );
	}
	return( -1 );
}

/* Frees a buffer
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_free(
     libfdata_buffer_t **buffer,
     libcerror_error_t **error )
{
	libfdata_internal_buffer_t *internal_buffer = NULL;
	static char *function                       = "libfdata_buffer_free";

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
	if( *buffer != NULL )
	{
		internal_buffer = (libfdata_internal_buffer_t *) *buffer;
		*buffer         = NULL;

		if( ( internal_buffer->flags & LIBFDATA_BUFFER_DATA_FLAG_MANAGED ) != 0 )
		{
			if( internal_buffer->data != NULL )
			{
				memory_free(
				 internal_buffer->data );
			}
		}
		memory_free(
		 internal_buffer );
	}
	return( 1 );
}

/* Clones the source buffer to the destination
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_clone(
     libfdata_buffer_t **destination_buffer,
     libfdata_buffer_t *source_buffer,
     libcerror_error_t **error )
{
	libfdata_internal_buffer_t *internal_source_buffer = NULL;
	static char *function                              = "libfdata_buffer_clone";

	if( destination_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination buffer.",
		 function );

		return( -1 );
	}
	if( *destination_buffer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination buffer value already set.",
		 function );

		return( -1 );
	}
	if( source_buffer == NULL )
	{
		*destination_buffer = NULL;

		return( 1 );
	}
	internal_source_buffer = (libfdata_internal_buffer_t *) source_buffer;

	if( libfdata_buffer_initialize(
	     destination_buffer,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create destination buffer.",
		 function );

		return( -1 );
	}
	if( libfdata_buffer_set_data(
	     *destination_buffer,
	     internal_source_buffer->data,
	     internal_source_buffer->data_size,
	     LIBFDATA_BUFFER_DATA_FLAG_NON_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data.",
		 function );

		libfdata_buffer_free(
		 destination_buffer,
		 NULL );

		return( -1 );
	}
	return( 1 );
}

/* Resizes a buffer
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_resize(
     libfdata_buffer_t *buffer,
     size_t size,
     libcerror_error_t **error )
{
	libfdata_internal_buffer_t *internal_buffer = NULL;
	void *reallocation                          = NULL;
	static char *function                       = "libfdata_buffer_resize";

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
	internal_buffer = (libfdata_internal_buffer_t *) buffer;

	if( size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( size > internal_buffer->data_size )
	{
		reallocation = memory_reallocate(
		                internal_buffer->data,
		                size );

		if( reallocation == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to resize buffer data.",
			 function );

			return( -1 );
		}
		if( internal_buffer->data == NULL )
		{
			internal_buffer->flags = LIBFDATA_BUFFER_DATA_FLAG_MANAGED;
		}
		internal_buffer->data      = (uint8_t *) reallocation;
		internal_buffer->data_size = size;
	}
	return( 1 );
}

/* Retrieves the buffer data size
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_get_data_size(
     libfdata_buffer_t *buffer,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfdata_internal_buffer_t *internal_buffer = NULL;
	static char *function                       = "libfdata_buffer_get_data_size";

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
	internal_buffer = (libfdata_internal_buffer_t *) buffer;

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
	*data_size = internal_buffer->data_size;

	return( 1 );
}

/* Retrieves the buffer data
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_get_data(
     libfdata_buffer_t *buffer,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfdata_internal_buffer_t *internal_buffer = NULL;
	static char *function                       = "libfdata_buffer_get_data";

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
	internal_buffer = (libfdata_internal_buffer_t *) buffer;

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
	*data      = internal_buffer->data;
	*data_size = internal_buffer->data_size;

	return( 1 );
}

/* Retrieves the buffer data at a specific offset
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_get_data_at_offset(
     libfdata_buffer_t *buffer,
     size_t data_offset,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfdata_internal_buffer_t *internal_buffer = NULL;
	static char *function                       = "libfdata_buffer_get_data_at_offset";

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
	internal_buffer = (libfdata_internal_buffer_t *) buffer;

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
	if( internal_buffer->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid buffer - missing data.",
		 function );

		return( -1 );
	}
	if( data_offset > internal_buffer->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value exceeds data size.",
		 function );

		return( -1 );
	}
	*data      = &( internal_buffer->data[ data_offset ] );
	*data_size = internal_buffer->data_size - data_offset;

	return( 1 );
}

/* Sets the buffer data
 *
 * If the flag LIBFDATA_BUFFER_DATA_FLAG_MANAGED is set the buffer
 * takes over management of the data and the data is freed when
 * no longer needed. If the flag is not set the buffer makes a copy of the data.
 *
 * Returns 1 if successful or -1 on error
 */
int libfdata_buffer_set_data(
     libfdata_buffer_t *buffer,
     const uint8_t *data,
     size_t data_size,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_buffer_t *internal_buffer = NULL;
	static char *function                       = "libfdata_buffer_set_data";

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
	internal_buffer = (libfdata_internal_buffer_t *) buffer;

	if( ( flags & ~( LIBFDATA_BUFFER_DATA_FLAG_MANAGED ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	if( internal_buffer->data != data )
	{
		if( ( internal_buffer->flags & LIBFDATA_BUFFER_DATA_FLAG_MANAGED ) != 0 )
		{
			if( internal_buffer->data != NULL )
			{
				memory_free(
				 internal_buffer->data );
			}
			internal_buffer->flags &= ~( LIBFDATA_BUFFER_DATA_FLAG_MANAGED );
		}
		if( ( flags & LIBFDATA_BUFFER_DATA_FLAG_MANAGED ) != 0 )
		{
			internal_buffer->data = (uint8_t *) data;
		}
		else if( data == NULL )
		{
			internal_buffer->data = NULL;
		}
		else if( data_size > 0 )
		{
			internal_buffer->data = (uint8_t *) memory_allocate(
							     sizeof( uint8_t ) * data_size );

			if( internal_buffer->data == NULL )
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
			     internal_buffer->data,
			     data,
			     data_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy data.",
				 function );

				goto on_error;
			}
			internal_buffer->flags |= LIBFDATA_BUFFER_DATA_FLAG_MANAGED;
		}
	}
	internal_buffer->data_size = data_size;
	internal_buffer->flags    |= flags;

	return( 1 );

on_error:
	if( internal_buffer->data != NULL )
	{
		memory_free(
		 internal_buffer->data );

		internal_buffer->data = NULL;
	}
	return( -1 );
}

