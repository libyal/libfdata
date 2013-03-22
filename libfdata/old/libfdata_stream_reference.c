/*
 * Stream data reference functions
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

#include "libfdata_definitions.h"
#include "libfdata_libcerror.h"
#include "libfdata_libfcache.h"
#include "libfdata_reference.h"
#include "libfdata_stream.h"
#include "libfdata_stream_reference.h"
#include "libfdata_types.h"

/* Initializes the stream reference and its values
 * Returns 1 if successful or -1 on error
 */
int libfdata_stream_reference_initialize(
     libfdata_reference_t **reference,
     libfdata_stream_t *stream,
     uint8_t flags,
     libcerror_error_t **error )
{
	static char *function = "libfdata_stream_reference_initialize";

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
	if( libfdata_reference_initialize(
	     reference,
	     (intptr_t *) stream,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_stream_free,
	     (int (*)(intptr_t **, intptr_t *, libcerror_error_t **)) &libfdata_stream_clone,
	     (int (*)(intptr_t *, int *, libcerror_error_t **)) &libfdata_stream_get_number_of_segments,
	     (int (*)(intptr_t *, size64_t *, libcerror_error_t **)) &libfdata_stream_get_data_size,
	     (int (*)(intptr_t *, intptr_t *, libfcache_cache_t *, uint8_t **, size_t *, libcerror_error_t **)) &libfdata_stream_get_data,
	     (int (*)(intptr_t *, intptr_t *, libfcache_cache_t *, int, uint8_t **, size_t *, uint8_t, libcerror_error_t **)) &libfdata_stream_get_segment_data,
	     (int (*)(intptr_t *, intptr_t *, libfcache_cache_t *, off64_t, uint8_t **, size_t *, uint8_t, libcerror_error_t **)) &libfdata_stream_get_segment_data_at_offset,
	     (int (*)(intptr_t *, intptr_t *, libfcache_cache_t *, int, size_t, uint8_t **, size_t *, uint8_t, libcerror_error_t **)) &libfdata_stream_get_segment_data_at_value_index,
	     (ssize_t (*)(intptr_t *, intptr_t *, libfcache_cache_t *, uint8_t *, size_t, libcerror_error_t **)) &libfdata_stream_read_buffer,
	     (off64_t (*)(intptr_t *, off64_t, int, libcerror_error_t **)) &libfdata_stream_seek_offset,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create reference.",
		 function );

		return( -1 );
	}
	return( 1 );
}

