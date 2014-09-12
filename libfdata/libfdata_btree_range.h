/*
 * The balanced tree range functions
 *
 * Copyright (c) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFDATA_BTREE_RANGE_H )
#define _LIBFDATA_BTREE_RANGE_H

#include <common.h>
#include <types.h>

#include "libfdata_extern.h"
#include "libfdata_libcerror.h"
#include "libfdata_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdata_btree_range libfdata_btree_range_t;

struct libfdata_btree_range
{
	/* The file index
	 */
	int file_index;

	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;

	/* The flags
	 */
	uint32_t flags;

	/* The key value
	 */
	intptr_t *key_value;

	/* The free key value function
	 */
	int (*free_key_value)(
	       intptr_t **key_value,
	       libcerror_error_t **error );

	/* The key value flags
	 */
	uint8_t key_value_flags;
};

int libfdata_btree_range_initialize(
     libfdata_btree_range_t **range,
     libcerror_error_t **error );

int libfdata_btree_range_free(
     libfdata_btree_range_t **range,
     libcerror_error_t **error );

/* TODO add libfdata_btree_range_clone */

int libfdata_btree_range_get(
     libfdata_btree_range_t *range,
     int *file_index,
     off64_t *offset,
     size64_t *size,
     uint32_t *flags,
     intptr_t **key_value,
     libcerror_error_t **error );

int libfdata_btree_range_set(
     libfdata_btree_range_t *range,
     int file_index,
     off64_t offset,
     size64_t size,
     uint32_t flags,
     intptr_t *key_value,
     int (*free_key_value)(
            intptr_t **key_value,
            libcerror_error_t **error ),
     uint8_t key_value_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

