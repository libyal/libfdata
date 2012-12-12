/*
 * The list functions
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

#if !defined( _LIBFDATA_INTERNAL_LIST_H )
#define _LIBFDATA_INTERNAL_LIST_H

#include <common.h>
#include <types.h>

#include "libfdata_extern.h"
#include "libfdata_libcdata.h"
#include "libfdata_libcerror.h"
#include "libfdata_libfcache.h"
#include "libfdata_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdata_internal_list libfdata_internal_list_t;

struct libfdata_internal_list
{
	/* The data size
	 */
	size64_t data_size;

	/* The (list) elements (array)
	 */
	libcdata_array_t *elements;

	/* The flags
	 */
	uint8_t flags;

	/* The data handle
	 */
	intptr_t *data_handle;

	/* The free data handle function
	 */
	int (*free_data_handle)(
	       intptr_t **data_handle,
	       libcerror_error_t **error );

	/* The clone (duplicate) data handle function
	 */
	int (*clone_data_handle)(
	       intptr_t **destination_data_handle,
	       intptr_t *source_data_handle,
	       libcerror_error_t **error );

	/* The read element data function
	 */
	int (*read_element_data)(
	       intptr_t *data_handle,
	       intptr_t *file_io_handle,
	       libfdata_list_element_t *list_element,
	       libfcache_cache_t *cache,
	       int data_range_file_index,
	       off64_t data_range_offset,
	       size64_t data_range_size,
	       uint32_t data_range_flags,
               uint8_t read_flags,
	       libcerror_error_t **error );

	/* The write element data function
	 */
	int (*write_element_data)(
	       intptr_t *data_handle,
	       intptr_t *file_io_handle,
	       libfdata_list_element_t *list_element,
	       libfcache_cache_t *cache,
	       int data_range_file_index,
	       off64_t data_range_offset,
	       size64_t data_range_size,
	       uint32_t data_range_flags,
               uint8_t write_flags,
	       libcerror_error_t **error );
};

LIBFDATA_EXTERN \
int libfdata_list_initialize(
     libfdata_list_t **list,
     intptr_t *data_handle,
     int (*free_data_handle)(
            intptr_t **data_handle,
            libcerror_error_t **error ),
     int (*clone_data_handle)(
            intptr_t **destination_data_handle,
            intptr_t *source_data_handle,
            libcerror_error_t **error ),
     int (*read_element_data)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfdata_list_element_t *list_element,
            libfcache_cache_t *cache,
            int data_range_file_index,
            off64_t data_range_offset,
            size64_t data_range_size,
            uint32_t data_range_flags,
            uint8_t read_flags,
            libcerror_error_t **error ),
     int (*write_element_data)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfdata_list_element_t *list_element,
            libfcache_cache_t *cache,
            int data_range_file_index,
            off64_t data_range_offset,
            size64_t data_range_size,
            uint32_t data_range_flags,
            uint8_t write_flags,
            libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_free(
     libfdata_list_t **list,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_clone(
     libfdata_list_t **destination_list,
     libfdata_list_t *source_list,
     libcerror_error_t **error );

int libfdata_list_clone_elements(
     libfdata_list_t *destination_list,
     libfdata_list_t *source_list,
     libcerror_error_t **error );

/* List element functions
 */
LIBFDATA_EXTERN \
int libfdata_list_empty(
     libfdata_list_t *list,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_resize(
     libfdata_list_t *list,
     int number_of_elements,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_get_number_of_elements(
     libfdata_list_t *list,
     int *number_of_elements,
     libcerror_error_t **error );

int libfdata_list_calculate_value_offsets(
     libfdata_internal_list_t *internal_list,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_get_element_by_index(
     libfdata_list_t *list,
     int element_index,
     libfdata_list_element_t **element,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_get_element_by_offset(
     libfdata_list_t *list,
     off64_t element_data_offset,
     int *element_index,
     libfdata_list_element_t **element,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_set_element_by_index(
     libfdata_list_t *list,
     int element_index,
     int file_index,
     off64_t offset,
     size64_t size,
     uint32_t flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_append_element(
     libfdata_list_t *list,
     int *element_index,
     int file_index,
     off64_t offset,
     size64_t size,
     uint32_t flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_is_element_set(
     libfdata_list_t *list,
     int element_index,
     libcerror_error_t **error );

/* Data range functions
 */
LIBFDATA_EXTERN \
int libfdata_list_get_data_range_by_index(
     libfdata_list_t *list,
     int element_index,
     int *file_index,
     off64_t *offset,
     size64_t *size,
     uint32_t *flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_set_data_range_by_index(
     libfdata_list_t *list,
     int element_index,
     int file_index,
     off64_t offset,
     size64_t size,
     uint32_t flags,
     libcerror_error_t **error );

/* List element value functions
 */
int libfdata_list_get_element_index_at_value_offset(
     libfdata_list_t *list,
     off64_t value_offset,
     int *element_index,
     size_t *element_offset,
     libcerror_error_t **error );

int libfdata_list_get_element_index_at_value_index(
     libfdata_list_t *list,
     int value_index,
     size_t value_size,
     int *element_index,
     size_t *element_offset,
     libcerror_error_t **error );

int libfdata_list_get_element_value(
     libfdata_list_t *list,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     libfdata_list_element_t *element,
     intptr_t **element_value,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_get_element_value_by_index(
     libfdata_list_t *list,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int element_index,
     intptr_t **element_value,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_get_element_value_at_offset(
     libfdata_list_t *list,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     off64_t value_offset,
     intptr_t **element_value,
     uint8_t read_flags,
     libcerror_error_t **error );

int libfdata_list_set_element_value(
     libfdata_list_t *list,
     libfcache_cache_t *cache,
     libfdata_list_element_t *element,
     intptr_t *element_value,
     int (*free_element_value)(
            intptr_t **element_value,
            libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_set_element_value_by_index(
     libfdata_list_t *list,
     libfcache_cache_t *cache,
     int element_index,
     intptr_t *element_value,
     int (*free_element_value)(
            intptr_t **element_value,
            libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_list_get_data_size(
     libfdata_list_t *list,
     size64_t *data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

