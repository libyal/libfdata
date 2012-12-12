/*
 * Buffer functions
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

#if !defined( _LIBFDATA_INTERNAL_BUFFER_H )
#define _LIBFDATA_INTERNAL_BUFFER_H

#include <common.h>
#include <types.h>

#include "libfdata_extern.h"
#include "libfdata_libcerror.h"
#include "libfdata_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdata_internal_buffer libfdata_internal_buffer_t;

struct libfdata_internal_buffer
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;

	/* The flags
	 */
	uint8_t flags;
};

LIBFDATA_EXTERN \
int libfdata_buffer_initialize(
     libfdata_buffer_t **buffer,
     size_t size,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_buffer_free(
     libfdata_buffer_t **buffer,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_buffer_clone(
     libfdata_buffer_t **destination_buffer,
     libfdata_buffer_t *source_buffer,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_buffer_resize(
     libfdata_buffer_t *buffer,
     size_t size,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_buffer_get_data_size(
     libfdata_buffer_t *buffer,
     size_t *data_size,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_buffer_get_data(
     libfdata_buffer_t *buffer,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_buffer_get_data_at_offset(
     libfdata_buffer_t *buffer,
     size_t data_offset,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_buffer_set_data(
     libfdata_buffer_t *buffer,
     const uint8_t *data,
     size_t data_size,
     uint8_t flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

