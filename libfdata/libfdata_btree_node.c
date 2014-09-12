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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfdata_btree_node.h"
#include "libfdata_btree_range.h"
#include "libfdata_definitions.h"
#include "libfdata_libcdata.h"
#include "libfdata_libcerror.h"
#include "libfdata_types.h"

/* Creates a node
 * Make sure the value node is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_initialize(
     libfdata_btree_node_t **node,
     int level,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_initialize";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	if( *node != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid node value already set.",
		 function );

		return( -1 );
	}
	if( level < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid level value less than zero.",
		 function );

		return( -1 );
	}
	internal_tree_node = memory_allocate_structure(
	                      libfdata_internal_btree_node_t );

	if( internal_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create node.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_tree_node,
	     0,
	     sizeof( libfdata_internal_btree_node_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear node.",
		 function );

		memory_free(
		 internal_tree_node );

		return( -1 );
	}
	internal_tree_node->level = level;
	internal_tree_node->flags = LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES;

	*node = (libfdata_btree_node_t *) internal_tree_node;

	return( 1 );

on_error:
	if( internal_tree_node != NULL )
	{
		memory_free(
		 internal_tree_node );
	}
	return( -1 );
}

/* Frees a node
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_free(
     libfdata_btree_node_t **node,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_free";
	int result                                         = 1;

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	if( *node != NULL )
	{
		internal_tree_node = (libfdata_internal_btree_node_t *) *node;
		*node              = NULL;

		if( internal_tree_node->value != NULL )
		{
			if( ( internal_tree_node->value_flags & LIBFDATA_BTREE_NODE_VALUE_FLAG_MANAGED ) != 0 )
			{
				if( internal_tree_node->free_value == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: invalid node - missing free value function.",
					 function );

					result = -1;
				}
				else if( internal_tree_node->free_value(
					  &( internal_tree_node->value ),
					  error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free value.",
					 function );

					result = -1;
				}
			}
		}
		if( internal_tree_node->sub_node_ranges_array != NULL )
		{
			if( libcdata_array_free(
			     &( internal_tree_node->sub_node_ranges_array ),
			     (int (*)(intptr_t **, libcerror_error_t **error)) &libfdata_btree_range_free,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free the sub node ranges array.",
				 function );

				result = -1;
			}
		}
		if( internal_tree_node->leaf_value_ranges_array != NULL )
		{
			if( libcdata_array_free(
			     &( internal_tree_node->leaf_value_ranges_array ),
			     (int (*)(intptr_t **, libcerror_error_t **error)) &libfdata_btree_range_free,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free the leaf value ranges array.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 internal_tree_node );
	}
	return( result );
}

/* Node functions
 */

/* Retrieves the level
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_get_level(
     libfdata_btree_node_t *node,
     int *level,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_get_level";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( level == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid level.",
		 function );

		return( -1 );
	}
	*level = internal_tree_node->level;

	return( 1 );
}

/* Determines if the node is a branch node
 * Returns 1 if a branch node, 0 if not or -1 on error
 */
int libfdata_btree_node_is_branch(
     libfdata_btree_node_t *node,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_is_branch";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( ( internal_tree_node->flags & LIBFDATA_BTREE_NODE_FLAG_IS_BRANCH ) != 0 )
	{
		return( 1 );
	}
	return( 0 );
}

/* Determines if the node is a leaf node
 * Returns 1 if a leaf node, 0 if not or -1 on error
 */
int libfdata_btree_node_is_leaf(
     libfdata_btree_node_t *node,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_is_leaf";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( ( internal_tree_node->flags & LIBFDATA_BTREE_NODE_FLAG_IS_LEAF ) != 0 )
	{
		return( 1 );
	}
	return( 0 );
}

/* Determines if the node is a root node
 * Returns 1 if a root node, 0 if not or -1 on error
 */
int libfdata_btree_node_is_root(
     libfdata_btree_node_t *node,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_is_root";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( internal_tree_node->level == 0 )
	{
		return( 1 );
	}
	return( 0 );
}

/* Node value functions
 */

/* Retrieves the node value
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_get_value(
     libfdata_btree_node_t *node,
     intptr_t **value,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_get_value";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	*value = internal_tree_node->value;

	return( 1 );
}

/* Sets the node value
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_set_value(
     libfdata_btree_node_t *node,
     intptr_t *value,
     int (*free_value)(
            intptr_t **value,
            libcerror_error_t **error ),
     uint8_t value_flags,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_set_value";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( free_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid free value function.",
		 function );

		return( -1 );
	}
	if( ( internal_tree_node->value_flags & LIBFDATA_BTREE_NODE_VALUE_FLAG_MANAGED ) != 0 )
	{
		if( internal_tree_node->value != NULL )
		{
			if( internal_tree_node->free_value == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid node - missing free value function.",
				 function );

				return( -1 );
			}
			if( internal_tree_node->free_value(
			     &( internal_tree_node->value ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free value.",
				 function );

				return( -1 );
			}
		}
		internal_tree_node->value_flags &= ~( LIBFDATA_BTREE_NODE_VALUE_FLAG_MANAGED );
	}
	internal_tree_node->value        = value;
	internal_tree_node->free_value   = free_value;
	internal_tree_node->value_flags |= value_flags;

	return( 1 );
}

/* Sub node data range functions
 */

/* Retrieves the number of sub nodes
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_get_number_of_sub_nodes(
     libfdata_btree_node_t *node,
     int *number_of_sub_nodes,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_get_number_of_sub_nodes";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( internal_tree_node->sub_node_ranges_array == NULL )
	{
		if( number_of_sub_nodes == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid number of sub nodes.",
			 function );

			return( -1 );
		}
		*number_of_sub_nodes = 0;
	}
	else
	{
		if( libcdata_array_get_number_of_entries(
		     internal_tree_node->sub_node_ranges_array,
		     number_of_sub_nodes,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of entries from sub node ranges array.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves a specific sub node data range
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_get_sub_node_data_range_by_index(
     libfdata_btree_node_t *node,
     int sub_node_index,
     libfdata_btree_range_t **sub_node_data_range,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_get_sub_node_data_range_by_index";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( libcdata_array_get_entry_by_index(
	     internal_tree_node->sub_node_ranges_array,
	     sub_node_index,
	     (intptr_t **) sub_node_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from sub node ranges array.",
		 function,
		 sub_node_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific sub node
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_get_sub_node_by_index(
     libfdata_btree_node_t *node,
     int sub_node_index,
     int *sub_node_file_index,
     off64_t *sub_node_offset,
     size64_t *sub_node_size,
     uint32_t *sub_node_flags,
     intptr_t **key_value,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	libfdata_btree_range_t *data_range                 = NULL;
	static char *function                              = "libfdata_btree_node_get_sub_node_by_index";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( internal_tree_node->sub_node_ranges_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sub node index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_tree_node->sub_node_ranges_array,
	     sub_node_index,
	     (intptr_t **) &data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from sub node ranges array.",
		 function,
		 sub_node_index );

		return( -1 );
	}
	if( libfdata_btree_range_get(
	     data_range,
	     sub_node_file_index,
	     sub_node_offset,
	     sub_node_size,
	     sub_node_flags,
	     key_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub node: %d data range.",
		 function,
		 sub_node_index );

		return( -1 );
	}
	return( 1 );
}

/* Sets the offset and size of a specific sub node
 * Returns 1 if successful or -1 on error
 */
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
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	libfdata_btree_range_t *data_range                 = NULL;
	static char *function                              = "libfdata_btree_node_set_sub_node_by_index";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( internal_tree_node->sub_node_ranges_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sub node index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_tree_node->sub_node_ranges_array,
	     sub_node_index,
	     (intptr_t **) &data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from sub node ranges array.",
		 function,
		 sub_node_index );

		return( -1 );
	}
	if( libfdata_btree_range_set(
	     data_range,
	     sub_node_file_index,
	     sub_node_offset,
	     sub_node_size,
	     sub_node_flags,
	     key_value,
	     free_key_value,
	     key_value_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set sub node: %d data range.",
		 function,
		 sub_node_index );

		return( -1 );
	}
	return( 1 );
}

/* Appends a sub node offset and size
 * Returns 1 if successful or -1 on error
 */
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
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	libfdata_btree_range_t *data_range                 = NULL;
	static char *function                              = "libfdata_btree_node_append_sub_node";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( ( internal_tree_node->flags & LIBFDATA_BTREE_NODE_FLAG_IS_LEAF ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid node - unsupported flags is leaf is set.",
		 function );

		return( -1 );
	}
	if( internal_tree_node->sub_node_ranges_array == NULL )
	{
		if( libcdata_array_initialize(
		     &( internal_tree_node->sub_node_ranges_array ),
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create sub node ranges array.",
			 function );

			goto on_error;
		}
	}
	if( libfdata_btree_range_initialize(
	     &data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data range.",
		 function );

		goto on_error;
	}
	if( libfdata_btree_range_set(
	     data_range,
	     sub_node_file_index,
	     sub_node_offset,
	     sub_node_size,
	     sub_node_flags,
	     key_value,
	     free_key_value,
	     key_value_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data range.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_tree_node->sub_node_ranges_array,
	     sub_node_index,
	     (intptr_t *) data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append data range to sub node ranges array.",
		 function );

		goto on_error;
	}
	internal_tree_node->flags |= LIBFDATA_BTREE_NODE_FLAG_IS_BRANCH;

	return( 1 );

on_error:
	if( data_range != NULL )
	{
		libfdata_btree_range_free(
		 &data_range,
		 NULL );
	}
	return( -1 );
}

/* Branch leaf values functions
 */

/* Retrieves the leaf values of the branch
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_get_branch_leaf_values(
     libfdata_btree_node_t *node,
     int *number_of_leaf_values,
     int *first_leaf_value_index,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_get_branch_leaf_values";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( number_of_leaf_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of leaf values.",
		 function );

		return( -1 );
	}
	if( first_leaf_value_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first leaf value index.",
		 function );

		return( -1 );
	}
	*number_of_leaf_values  = internal_tree_node->branch_number_of_leaf_values;
	*first_leaf_value_index = internal_tree_node->branch_first_leaf_value_index;

	return( 1 );
}

/* Leaf value data range functions
 */

/* Retrieves the number of leaf values
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_get_number_of_leaf_values(
     libfdata_btree_node_t *node,
     int *number_of_leaf_values,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	static char *function                              = "libfdata_btree_node_get_number_of_leaf_values";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( internal_tree_node->leaf_value_ranges_array == NULL )
	{
		if( number_of_leaf_values == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid number of leaf values.",
			 function );

			return( -1 );
		}
		*number_of_leaf_values = 0;
	}
	else
	{
		if( libcdata_array_get_number_of_entries(
		     internal_tree_node->leaf_value_ranges_array,
		     number_of_leaf_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of entries from leaf value ranges array.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves a specific leaf value
 * Returns 1 if successful or -1 on error
 */
int libfdata_btree_node_get_leaf_value_by_index(
     libfdata_btree_node_t *node,
     int leaf_value_index,
     int *leaf_value_file_index,
     off64_t *leaf_value_offset,
     size64_t *leaf_value_size,
     uint32_t *leaf_value_flags,
     intptr_t **key_value,
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	libfdata_btree_range_t *data_range                 = NULL;
	static char *function                              = "libfdata_btree_node_get_leaf_value_by_index";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( internal_tree_node->leaf_value_ranges_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid leaf value index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_tree_node->leaf_value_ranges_array,
	     leaf_value_index,
	     (intptr_t **) &data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from leaf value ranges array.",
		 function,
		 leaf_value_index );

		return( -1 );
	}
	if( libfdata_btree_range_get(
	     data_range,
	     leaf_value_file_index,
	     leaf_value_offset,
	     leaf_value_size,
	     leaf_value_flags,
	     key_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve leaf value: %d data range.",
		 function,
		 leaf_value_index );

		return( -1 );
	}
	return( 1 );
}

/* Sets the offset and size of a specific leaf value
 * Returns 1 if successful or -1 on error
 */
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
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	libfdata_btree_range_t *data_range                 = NULL;
	static char *function                              = "libfdata_btree_node_set_leaf_value_by_index";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( internal_tree_node->leaf_value_ranges_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid leaf value index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_tree_node->leaf_value_ranges_array,
	     leaf_value_index,
	     (intptr_t **) &data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from leaf value ranges array.",
		 function,
		 leaf_value_index );

		return( -1 );
	}
	if( libfdata_btree_range_set(
	     data_range,
	     leaf_value_file_index,
	     leaf_value_offset,
	     leaf_value_size,
	     leaf_value_flags,
	     key_value,
	     free_key_value,
	     key_value_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set leaf value: %d data range.",
		 function,
		 leaf_value_index );

		return( -1 );
	}
	return( 1 );
}

/* Appends a leaf value offset and size
 * Returns 1 if successful or -1 on error
 */
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
     libcerror_error_t **error )
{
	libfdata_internal_btree_node_t *internal_tree_node = NULL;
	libfdata_btree_range_t *data_range                 = NULL;
	static char *function                              = "libfdata_btree_node_append_leaf_value";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_tree_node = (libfdata_internal_btree_node_t *) node;

	if( ( internal_tree_node->flags & LIBFDATA_BTREE_NODE_FLAG_IS_BRANCH ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid node - unsupported flags is branch is set.",
		 function );

		return( -1 );
	}
	if( internal_tree_node->leaf_value_ranges_array == NULL )
	{
		if( libcdata_array_initialize(
		     &( internal_tree_node->leaf_value_ranges_array ),
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create leaf value ranges array.",
			 function );

			goto on_error;
		}
	}
	if( libfdata_btree_range_initialize(
	     &data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data range.",
		 function );

		goto on_error;
	}
	if( libfdata_btree_range_set(
	     data_range,
	     leaf_value_file_index,
	     leaf_value_offset,
	     leaf_value_size,
	     leaf_value_flags,
	     key_value,
	     free_key_value,
	     key_value_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data range.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_tree_node->leaf_value_ranges_array,
	     leaf_value_index,
	     (intptr_t *) data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append data range to leaf value ranges array.",
		 function );

		goto on_error;
	}
	internal_tree_node->flags |= LIBFDATA_BTREE_NODE_FLAG_IS_LEAF;

	return( 1 );

on_error:
	if( data_range != NULL )
	{
		libfdata_btree_range_free(
		 &data_range,
		 NULL );
	}
	return( -1 );
}

