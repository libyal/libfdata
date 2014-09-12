/*
 * The balanced tree node functions
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

#if !defined( _LIBFDATA_INTERNAL_BTREE_NODE_H )
#define _LIBFDATA_INTERNAL_BTREE_NODE_H

#include <common.h>
#include <types.h>

#include "libfdata_btree_range.h"
#include "libfdata_extern.h"
#include "libfdata_libcdata.h"
#include "libfdata_libcerror.h"
#include "libfdata_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdata_internal_btree_node libfdata_internal_btree_node_t;

struct libfdata_internal_btree_node
{
	/* The (node) level
	 */
	int level;

	/* The value
	 */
	intptr_t *value;

	/* The free value function
	 */
	int (*free_value)(
	       intptr_t **value,
	       libcerror_error_t **error );

	/* The value flags
	 */
	uint8_t value_flags;

	/* The sub node (data) ranges array
	 */
	libcdata_array_t *sub_node_ranges_array;

	/* The number of leaf values in the branch
	 */
	int branch_number_of_leaf_values;

	/* The relative first leaf value index in the branch
	 */
	int branch_first_leaf_value_index;

	/* The leaf value (data) ranges array
	 */
	libcdata_array_t *leaf_value_ranges_array;

	/* The flags
	 */
	uint8_t flags;
};

int libfdata_btree_node_initialize(
     libfdata_btree_node_t **node,
     int level,
     libcerror_error_t **error );

int libfdata_btree_node_free(
     libfdata_btree_node_t **node,
     libcerror_error_t **error );

/* Node functions
 */

LIBFDATA_EXTERN \
int libfdata_btree_node_get_level(
     libfdata_btree_node_t *node,
     int *level,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_is_branch(
     libfdata_btree_node_t *node,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_is_leaf(
     libfdata_btree_node_t *node,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_is_root(
     libfdata_btree_node_t *node,
     libcerror_error_t **error );

/* Node value functions
 */

LIBFDATA_EXTERN \
int libfdata_btree_node_get_value(
     libfdata_btree_node_t *node,
     intptr_t **value,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_set_value(
     libfdata_btree_node_t *node,
     intptr_t *value,
     int (*free_value)(
            intptr_t **value,
            libcerror_error_t **error ),
     uint8_t value_flags,
     libcerror_error_t **error );

/* Sub node data range functions
 */

LIBFDATA_EXTERN \
int libfdata_btree_node_get_number_of_sub_nodes(
     libfdata_btree_node_t *node,
     int *number_of_sub_nodes,
     libcerror_error_t **error );

int libfdata_btree_node_get_sub_node_data_range_by_index(
     libfdata_btree_node_t *node,
     int sub_node_index,
     libfdata_btree_range_t **sub_node_data_range,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_get_sub_node_by_index(
     libfdata_btree_node_t *node,
     int sub_node_index,
     int *sub_node_file_index,
     off64_t *sub_node_offset,
     size64_t *sub_node_size,
     uint32_t *sub_node_flags,
     intptr_t **key_value,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_set_sub_node_by_index(
     libfdata_btree_node_t *node,
     int sub_node_index,
     int sub_node_file_index,
     off64_t sub_node_offset,
     size64_t sub_node_size,
     uint32_t sub_node_flags,
     intptr_t *key_value,
     int (*free_key_value)(
            intptr_t **key_value,
            libcerror_error_t **error ),
     uint8_t key_value_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_append_sub_node(
     libfdata_btree_node_t *node,
     int *sub_node_index,
     int sub_node_file_index,
     off64_t sub_node_offset,
     size64_t sub_node_size,
     uint32_t sub_node_flags,
     intptr_t *key_value,
     int (*free_key_value)(
            intptr_t **key_value,
            libcerror_error_t **error ),
     uint8_t key_value_flags,
     libcerror_error_t **error );

/* Branch leaf values functions
 */

int libfdata_btree_node_get_branch_leaf_values(
     libfdata_btree_node_t *node,
     int *number_of_leaf_values,
     int *first_leaf_value_index,
     libcerror_error_t **error );

/* Leaf value data range functions
 */

LIBFDATA_EXTERN \
int libfdata_btree_node_get_number_of_leaf_values(
     libfdata_btree_node_t *node,
     int *number_of_leaf_values,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_get_leaf_value_by_index(
     libfdata_btree_node_t *node,
     int leaf_value_index,
     int *leaf_value_file_index,
     off64_t *leaf_value_offset,
     size64_t *leaf_value_size,
     uint32_t *leaf_value_flags,
     intptr_t **key_value,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_set_leaf_value_by_index(
     libfdata_btree_node_t *node,
     int leaf_value_index,
     int leaf_value_file_index,
     off64_t leaf_value_offset,
     size64_t leaf_value_size,
     uint32_t leaf_value_flags,
     intptr_t *key_value,
     int (*free_key_value)(
            intptr_t **key_value,
            libcerror_error_t **error ),
     uint8_t key_value_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_btree_node_append_leaf_value(
     libfdata_btree_node_t *node,
     int *leaf_value_index,
     int leaf_value_file_index,
     off64_t leaf_value_offset,
     size64_t leaf_value_size,
     uint32_t leaf_value_flags,
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

