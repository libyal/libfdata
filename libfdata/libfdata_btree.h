/*
 * The balanced tree functions
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

#if !defined( _LIBFDATA_INTERNAL_BTREE_H )
#define _LIBFDATA_INTERNAL_BTREE_H

#include <common.h>
#include <types.h>

#include "libfdata_btree_node.h"
#include "libfdata_btree_range.h"
#include "libfdata_extern.h"
#include "libfdata_libcerror.h"
#include "libfdata_libfcache.h"
#include "libfdata_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdata_internal_btree libfdata_internal_btree_t;

struct libfdata_internal_btree
{
	/* The root node data range
	 */
	libfdata_btree_range_t *root_node_data_range;

	/* The time stamp
	 */
	time_t timestamp;

	/* The flags
	 */
	uint8_t flags;

	/* The calculate cache entry index value
	 */
	int (*calculate_cache_entry_index)(
	       int node_index,
	       int node_data_file_index,
	       off64_t node_data_offset,
	       size64_t node_data_size,
	       uint32_t node_data_flags,
               int number_of_cache_entries );

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

	/* The read node function
	 */
	int (*read_node)(
	       intptr_t *data_handle,
	       intptr_t *file_io_handle,
	       libfdata_btree_node_t *node,
	       int node_data_file_index,
	       off64_t node_data_offset,
	       size64_t node_data_size,
	       uint32_t node_data_flags,
               uint8_t read_flags,
	       libcerror_error_t **error );

	/* The write node function
	 */
	int (*write_node)(
	       intptr_t *data_handle,
	       intptr_t *file_io_handle,
	       libfdata_btree_node_t *node,
	       int node_data_file_index,
	       off64_t node_data_offset,
	       size64_t node_data_size,
	       uint32_t node_data_flags,
               uint8_t write_flags,
	       libcerror_error_t **error );
};

LIBFDATA_EXTERN \
int libfdata_btree_initialize(
     libfdata_btree_t **tree,
     intptr_t *data_handle,
     int (*free_data_handle)(
            intptr_t **data_handle,
            libcerror_error_t **error ),
     int (*clone_data_handle)(
            intptr_t **destination_data_handle,
            intptr_t *source_data_handle,
            libcerror_error_t **error ),
     int (*read_node)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfdata_btree_node_t *node,
            int node_data_file_index,
            off64_t node_data_offset,
            size64_t node_data_size,
            uint32_t node_data_flags,
            uint8_t read_flags,
            libcerror_error_t **error ),
     int (*write_node)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfdata_btree_node_t *node,
            int node_data_file_index,
            off64_t node_data_offset,
            size64_t node_data_size,
            uint32_t node_data_flags,
            uint8_t write_flags,
            libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_free(
     libfdata_btree_t **tree,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_clone(
     libfdata_btree_t **destination_tree,
     libfdata_btree_t *source_tree,
     libcerror_error_t **error );

/* Root node functions
 */
LIBFDATA_EXTERN \
int libfdata_btree_get_root_node(
     libfdata_btree_t *tree,
     int *node_data_file_index,
     off64_t *node_data_offset,
     size64_t *node_data_size,
     uint32_t *node_data_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_set_root_node(
     libfdata_btree_t *tree,
     int node_data_file_index,
     off64_t node_data_offset,
     size64_t node_data_size,
     uint32_t node_data_flags,
     libcerror_error_t **error );

/* Leaf value functions
 */
int libfdata_btree_read_node(
     libfdata_internal_btree_t *internal_tree,
     libfdata_btree_range_t *node_data_range,
     int level,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     libfdata_btree_node_t **node,
     uint8_t read_flags,
     libcerror_error_t **error );

int libfdata_btree_read_sub_tree(
     libfdata_internal_btree_t *internal_tree,
     libfdata_btree_range_t *node_data_range,
     int level,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     libfdata_btree_node_t **node,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_get_number_of_leaf_values(
     libfdata_btree_t *tree,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int *number_of_values,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_get_leaf_value_by_index(
     libfdata_btree_t *tree,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int value_index,
     intptr_t **value,
     uint8_t read_flags,
     libcerror_error_t **error );

/* TODO add get leaf value by key function */

#if defined( __cplusplus )
}
#endif

#endif

