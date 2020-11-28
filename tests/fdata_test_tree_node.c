/*
 * Library tree_node type test program
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fdata_test_libcerror.h"
#include "fdata_test_libfdata.h"
#include "fdata_test_macros.h"
#include "fdata_test_memory.h"
#include "fdata_test_unused.h"

#include "../libfdata/libfdata_tree_node.h"

int fdata_test_tree_node_value_free_function_return_value = 1;

/* Test node value free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_tree_node_value_free_function(
     intptr_t **node_value,
     libcerror_error_t **error )
{
	static char *function = "fdata_test_tree_node_value_free_function";

	if( node_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node value.",
		 function );

		return( -1 );
	}
	if( *node_value != NULL )
	{
		memory_free(
		 *node_value );

		*node_value = NULL;
	}
	return( fdata_test_tree_node_value_free_function_return_value );
}

/* Test value compare function
 * Returns LIBFDATA_COMPARE_LESS, LIBFDATA_COMPARE_EQUAL, LIBFDATA_COMPARE_GREATER if successful or -1 on error
 */
int fdata_test_tree_node_value_compare_function(
     intptr_t *first_value,
     intptr_t *second_value,
     libfdata_error_t **error )
{
	static char *function = "fdata_test_tree_node_value_compare_function";

	if( first_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first value.",
		 function );

		return( -1 );
	}
	if( second_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second value.",
		 function );

		return( -1 );
	}
	if( *first_value > *second_value )
	{
		return( LIBFDATA_COMPARE_LESS );
	}
	else if( *first_value < *second_value )
	{
		return( LIBFDATA_COMPARE_GREATER );
	}
	return( LIBFDATA_COMPARE_EQUAL );
}

/* Reads a node
 * Callback function for the tree
 * Returns 1 if successful or -1 on error
 */
int fdata_test_tree_read_node(
     intptr_t *data_handle,
     intptr_t *file_io_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libfdata_tree_node_t *tree_node,
     libfdata_cache_t *cache,
     int node_file_index,
     off64_t node_offset,
     size64_t node_size,
     uint32_t node_flags,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	uint8_t *node_value   = NULL;
	static char *function = "fdata_test_tree_read_node";
	uint32_t node_index   = 0;

	FDATA_TEST_UNREFERENCED_PARAMETER( file_io_handle )

	if( data_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( node_file_index != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid node file index value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( node_offset < 1024 )
	 || ( node_offset >= ( 1024 + 128 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid node offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( node_size != 128 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid node size value out of bounds.",
		 function );

		return( -1 );
	}
	if( node_flags != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid node flags value out of bounds.",
		 function );

		return( -1 );
	}
	if( read_flags != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid read flags value out of bounds.",
		 function );

		return( -1 );
	}
	node_value = (uint8_t *) memory_allocate(
	                          sizeof( uint32_t ) );

	if( node_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create node value.",
		 function );

		goto on_error;
	}
	node_index = (uint32_t) ( ( node_offset - 1024 ) / node_size );

	byte_stream_copy_from_uint32_little_endian(
	 node_value,
	 node_index );

	if( libfdata_tree_node_set_node_value(
	     tree_node,
	     cache,
	     (intptr_t *) node_value,
	     (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_tree_node_value_free_function,
	     LIBFDATA_TREE_NODE_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set tree node value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( node_value != NULL )
	{
		memory_free(
		 node_value );
	}
	return( -1 );
}

/* Reads sub nodes
 * Callback function for the tree
 * Returns 1 if successful or -1 on error
 */
int fdata_test_tree_read_sub_nodes(
     intptr_t *data_handle,
     intptr_t *file_io_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libfdata_tree_node_t *tree_node FDATA_TEST_ATTRIBUTE_UNUSED,
     libfdata_cache_t *cache FDATA_TEST_ATTRIBUTE_UNUSED,
     int sub_nodes_file_index,
     off64_t sub_nodes_offset,
     size64_t sub_nodes_size,
     uint32_t sub_nodes_flags,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	static char *function = "fdata_test_tree_read_sub_nodes";

	FDATA_TEST_UNREFERENCED_PARAMETER( file_io_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( tree_node )
	FDATA_TEST_UNREFERENCED_PARAMETER( cache )

	if( data_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( sub_nodes_file_index != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sub nodes file index value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( sub_nodes_offset < 1024 )
	 || ( sub_nodes_offset >= ( 1024 + 128 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sub nodes offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( sub_nodes_size != 128 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sub nodes size value out of bounds.",
		 function );

		return( -1 );
	}
	if( sub_nodes_flags != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sub nodes flags value out of bounds.",
		 function );

		return( -1 );
	}
	if( read_flags != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid read flags value out of bounds.",
		 function );

		return( -1 );
	}
/* TODO implement */

	return( -1 );
}

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

/* Tests the libfdata_tree_node_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests = 4;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_initialize(
	          NULL,
	          tree,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	tree_node = (libfdata_tree_node_t *) 0x12345678UL;

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          NULL,
	          &error );

	tree_node = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          NULL,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 * 2 fail in memory_allocate of libfdata_range_initialize of node_data_range
	 * 3 fail in memory_allocate of libfdata_range_initialize of sub_nodes_data_range
	 * 4 fail in memory_allocate of libcdata_array_initialize
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_tree_node_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_tree_node_initialize(
		          &tree_node,
		          tree,
		          NULL,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( tree_node != NULL )
			{
				libfdata_tree_node_free(
				 &tree_node,
				 NULL );
			}
		}
		else
		{
			FDATA_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FDATA_TEST_ASSERT_IS_NULL(
			 "tree_node",
			 tree_node );

			FDATA_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	/* 1 fail in memset after memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_tree_node_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_tree_node_initialize(
		          &tree_node,
		          tree,
		          NULL,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( tree_node != NULL )
			{
				libfdata_tree_node_free(
				 &tree_node,
				 NULL );
			}
		}
		else
		{
			FDATA_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FDATA_TEST_ASSERT_IS_NULL(
			 "tree_node",
			 tree_node );

			FDATA_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FDATA_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_tree_node_free(
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_free_single function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_free_single(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_tree_node_free_single(
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_parent_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_parent_node(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int element_index               = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_parent_node(
	          tree_node,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "element_index",
	 element_index,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_parent_node(
	          NULL,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_is_root function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_is_root(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_is_root(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_is_root(
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_data_range function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_data_range(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	size64_t node_size              = 0;
	off64_t node_offset             = 0;
	uint32_t node_flags             = 0;
	int node_file_index             = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_get_data_range(
	          tree_node,
	          &node_file_index,
	          &node_offset,
	          &node_size,
	          &node_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_get_data_range(
	          NULL,
	          &node_file_index,
	          &node_offset,
	          &node_size,
	          &node_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_data_range(
	          tree_node,
	          NULL,
	          &node_offset,
	          &node_size,
	          &node_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_data_range(
	          tree_node,
	          &node_file_index,
	          NULL,
	          &node_size,
	          &node_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_data_range(
	          tree_node,
	          &node_file_index,
	          &node_offset,
	          NULL,
	          &node_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_data_range(
	          tree_node,
	          &node_file_index,
	          &node_offset,
	          &node_size,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_data_range function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_data_range(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_data_range(
	          tree_node,
	          1,
	          1024,
	          2048,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_data_range(
	          NULL,
	          1,
	          1024,
	          2048,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_sub_nodes_data_range_is_set function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_sub_nodes_data_range_is_set(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_sub_nodes_data_range_is_set(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfdata_tree_node_set_sub_nodes_data_range(
	          tree_node,
	          1,
	          1024,
	          2048,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_sub_nodes_data_range_is_set(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_sub_nodes_data_range_is_set(
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_sub_nodes_data_range function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_sub_nodes_data_range(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	size64_t sub_nodes_size         = 0;
	off64_t sub_nodes_offset        = 0;
	uint32_t sub_nodes_flags        = 0;
	int result                      = 0;
	int sub_nodes_file_index        = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_get_sub_nodes_data_range(
	          tree_node,
	          &sub_nodes_file_index,
	          &sub_nodes_offset,
	          &sub_nodes_size,
	          &sub_nodes_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
	result = libfdata_tree_node_set_sub_nodes_data_range(
	          tree_node,
	          1,
	          1024,
	          2048,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_get_sub_nodes_data_range(
	          tree_node,
	          &sub_nodes_file_index,
	          &sub_nodes_offset,
	          &sub_nodes_size,
	          &sub_nodes_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_get_sub_nodes_data_range(
	          NULL,
	          &sub_nodes_file_index,
	          &sub_nodes_offset,
	          &sub_nodes_size,
	          &sub_nodes_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_sub_nodes_data_range(
	          tree_node,
	          NULL,
	          &sub_nodes_offset,
	          &sub_nodes_size,
	          &sub_nodes_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_sub_nodes_data_range(
	          tree_node,
	          &sub_nodes_file_index,
	          NULL,
	          &sub_nodes_size,
	          &sub_nodes_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_sub_nodes_data_range(
	          tree_node,
	          &sub_nodes_file_index,
	          &sub_nodes_offset,
	          NULL,
	          &sub_nodes_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_sub_nodes_data_range(
	          tree_node,
	          &sub_nodes_file_index,
	          &sub_nodes_offset,
	          &sub_nodes_size,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_sub_nodes_data_range function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_sub_nodes_data_range(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_sub_nodes_data_range(
	          tree_node,
	          1,
	          1024,
	          2048,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_sub_nodes_data_range(
	          NULL,
	          1,
	          1024,
	          2048,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_timestamp function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_timestamp(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int64_t timestamp               = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_get_timestamp(
	          tree_node,
	          &timestamp,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_NOT_EQUAL_INT64(
	 "timestamp",
	 timestamp,
	 (int64_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_get_timestamp(
	          NULL,
	          &timestamp,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_timestamp(
	          tree_node,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_first_leaf_node_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_first_leaf_node_index(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_tree_t *tree             = NULL;
	libfdata_tree_node_t *tree_node   = NULL;
	int deleted_first_leaf_node_index = 0;
	int first_leaf_node_index         = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_get_first_leaf_node_index(
	          tree_node,
	          &first_leaf_node_index,
	          &deleted_first_leaf_node_index,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_get_first_leaf_node_index(
	          NULL,
	          &first_leaf_node_index,
	          &deleted_first_leaf_node_index,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_first_leaf_node_index(
	          tree_node,
	          NULL,
	          &deleted_first_leaf_node_index,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_first_leaf_node_index(
	          tree_node,
	          &first_leaf_node_index,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_first_leaf_node_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_first_leaf_node_index(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_first_leaf_node_index(
	          tree_node,
	          5,
	          7,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_first_leaf_node_index(
	          NULL,
	          5,
	          7,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_set_first_leaf_node_index(
	          NULL,
	          -1,
	          7,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_set_first_leaf_node_index(
	          NULL,
	          5,
	          -1,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_node_value function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_node_value(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	intptr_t *node_value            = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_set_data_range(
	          tree_node,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	node_value = NULL;

	result = libfdata_tree_node_get_node_value(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &node_value,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "node_value",
	 node_value );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* node_value is managed by the cache and does not need to be explicitly freed
	 */

	/* Test error cases
	 */
	node_value = NULL;

	result = libfdata_tree_node_get_node_value(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &node_value,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_node_value function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_node_value(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;
	int value1                      = 1;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_set_data_range(
	          tree_node,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_node_value(
	          tree_node,
	          (libfdata_cache_t *) cache,
	          (intptr_t *) &value1,
	          (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_tree_node_value_free_function,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_node_value(
	          NULL,
	          (libfdata_cache_t *) cache,
	          (intptr_t *) &value1,
	          (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_tree_node_value_free_function,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_resize_sub_nodes function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_resize_sub_nodes(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_resize_sub_nodes(
	          tree_node,
	          10,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_resize_sub_nodes(
	          NULL,
	          10,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_resize_sub_nodes(
	          tree_node,
	          -1,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_number_of_sub_nodes function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_number_of_sub_nodes(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int number_of_sub_nodes         = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	/* Test libfdata_tree_node_get_number_of_sub_nodes failing in libfdata_tree_get_node_value
	 */
	result = libfdata_tree_node_get_number_of_sub_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_node_get_number_of_sub_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_sub_nodes",
	 number_of_sub_nodes,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Initialize test
	 */
/* TODO */

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_node_get_number_of_sub_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_sub_nodes",
	 number_of_sub_nodes,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_tree_node_get_number_of_sub_nodes(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_number_of_sub_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_sub_node_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_sub_node_by_index(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *sub_node  = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_tree_node_get_sub_node_by_index failing in libfdata_tree_get_node_value
	 */
	sub_node = NULL;

	result = libfdata_tree_node_get_sub_node_by_index(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &sub_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
/* TODO */

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	sub_node = NULL;

	result = libfdata_tree_node_get_sub_node_by_index(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &sub_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "sub_node",
	 sub_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	sub_node = NULL;

	result = libfdata_tree_node_get_sub_node_by_index(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &sub_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_sub_node_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_sub_node_by_index(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_node_set_sub_node_by_index(
	          tree_node,
	          0,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_tree_node_set_sub_node_by_index(
	          NULL,
	          0,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_set_sub_node_by_index(
	          tree_node,
	          -1,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_append_sub_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_append_sub_node(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;
	int sub_node_index              = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_append_sub_node(
	          tree_node,
	          &sub_node_index,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_append_sub_node(
	          NULL,
	          &sub_node_index,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_append_sub_node(
	          tree_node,
	          NULL,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_insert_sub_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_insert_sub_node(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;
	int sub_node_index              = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_insert_sub_node(
	          tree_node,
	          NULL,
	          cache,
	          &sub_node_index,
	          1,
	          1024,
	          128,
	          0,
	          &fdata_test_tree_node_value_compare_function,
	          0,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_insert_sub_node(
	          NULL,
	          NULL,
	          cache,
	          &sub_node_index,
	          1,
	          1024,
	          128,
	          0,
	          &fdata_test_tree_node_value_compare_function,
	          0,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_insert_sub_node(
	          tree_node,
	          NULL,
	          cache,
	          NULL,
	          1,
	          1024,
	          128,
	          0,
	          &fdata_test_tree_node_value_compare_function,
	          0,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_insert_sub_node(
	          tree_node,
	          NULL,
	          cache,
	          &sub_node_index,
	          1,
	          1024,
	          128,
	          0,
	          NULL,
	          0,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_insert_sub_node(
	          tree_node,
	          NULL,
	          cache,
	          &sub_node_index,
	          1,
	          1024,
	          128,
	          0,
	          &fdata_test_tree_node_value_compare_function,
	          0xff,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_is_deleted function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_is_deleted(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_set_data_range(
	          tree_node,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_is_deleted(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfdata_tree_node_set_deleted(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_is_deleted(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_is_deleted(
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_deleted function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_deleted(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_deleted(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_deleted(
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_deleted_sub_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_deleted_sub_node(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;
	int sub_node_index              = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_append_sub_node(
	          tree_node,
	          &sub_node_index,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_deleted_sub_node(
	          tree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_deleted_sub_node(
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_set_deleted_sub_node(
	          tree_node,
	          -1,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_is_leaf function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_is_leaf(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_set_data_range(
	          tree_node,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_is_leaf(
	          tree_node,
	          NULL,
	          cache,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfdata_tree_node_set_leaf(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_is_leaf(
	          tree_node,
	          NULL,
	          cache,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_is_leaf(
	          NULL,
	          NULL,
	          cache,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_leaf function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_leaf(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_leaf(
	          tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_leaf(
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_set_leaf_sub_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_set_leaf_sub_node(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;
	int sub_node_index              = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_append_sub_node(
	          tree_node,
	          &sub_node_index,
	          1,
	          1024,
	          128,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_tree_node_set_leaf_sub_node(
	          tree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_node_set_leaf_sub_node(
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_set_leaf_sub_node(
	          tree_node,
	          -1,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_number_of_leaf_nodes function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_number_of_leaf_nodes(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int number_of_leaf_nodes        = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	/* Test libfdata_tree_node_get_number_of_leaf_nodes failing in libfdata_tree_get_node_value
	 */
	result = libfdata_tree_node_get_number_of_leaf_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_leaf_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_node_get_number_of_leaf_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_leaf_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_leaf_nodes",
	 number_of_leaf_nodes,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Initialize test
	 */
/* TODO */

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_node_get_number_of_leaf_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_leaf_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_leaf_nodes",
	 number_of_leaf_nodes,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_tree_node_get_number_of_leaf_nodes(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_leaf_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_number_of_leaf_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_leaf_node_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_leaf_node_by_index(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *leaf_node = NULL;
	libfdata_tree_node_t *tree_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_tree_node_get_leaf_node_by_index failing in libfdata_tree_get_node_value
	 */
	leaf_node = NULL;

	result = libfdata_tree_node_get_leaf_node_by_index(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &leaf_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
/* TODO */

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	leaf_node = NULL;

	result = libfdata_tree_node_get_leaf_node_by_index(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &leaf_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "leaf_node",
	 leaf_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	leaf_node = NULL;

	result = libfdata_tree_node_get_leaf_node_by_index(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &leaf_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_number_of_deleted_leaf_nodes function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_number_of_deleted_leaf_nodes(
     void )
{
	libcerror_error_t *error         = NULL;
	libfdata_cache_t *cache          = NULL;
	libfdata_tree_t *tree            = NULL;
	libfdata_tree_node_t *tree_node  = NULL;
	int number_of_deleted_leaf_nodes = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	/* Test libfdata_tree_node_get_number_of_deleted_leaf_nodes failing in libfdata_tree_get_node_value
	 */
	result = libfdata_tree_node_get_number_of_deleted_leaf_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_deleted_leaf_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_node_get_number_of_deleted_leaf_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_deleted_leaf_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_deleted_leaf_nodes",
	 number_of_deleted_leaf_nodes,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Initialize test
	 */
/* TODO */

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_node_get_number_of_deleted_leaf_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_deleted_leaf_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_deleted_leaf_nodes",
	 number_of_deleted_leaf_nodes,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_tree_node_get_number_of_deleted_leaf_nodes(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_deleted_leaf_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_node_get_number_of_deleted_leaf_nodes(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_node_get_deleted_leaf_node_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_node_get_deleted_leaf_node_by_index(
     void )
{
	libcerror_error_t *error                = NULL;
	libfdata_cache_t *cache                 = NULL;
	libfdata_tree_t *tree                   = NULL;
	libfdata_tree_node_t *deleted_leaf_node = NULL;
	libfdata_tree_node_t *tree_node         = NULL;
	int result                              = 0;

	/* Initialize test
	 */
	result = libfdata_cache_initialize(
	          &cache,
	          16,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          NULL,
	          NULL,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_node_initialize(
	          &tree_node,
	          tree,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_tree_node_get_deleted_leaf_node_by_index failing in libfdata_tree_get_node_value
	 */
	deleted_leaf_node = NULL;

	result = libfdata_tree_node_get_deleted_leaf_node_by_index(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &deleted_leaf_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
/* TODO */

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	deleted_leaf_node = NULL;

	result = libfdata_tree_node_get_deleted_leaf_node_by_index(
	          tree_node,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &deleted_leaf_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "deleted_leaf_node",
	 deleted_leaf_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	deleted_leaf_node = NULL;

	result = libfdata_tree_node_get_deleted_leaf_node_by_index(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &deleted_leaf_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_tree_node_free(
	          &tree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree_node",
	 tree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "tree",
	 tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_cache_free(
	          &cache,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "cache",
	 cache );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree_node != NULL )
	{
		libfdata_tree_node_free(
		 &tree_node,
		 NULL );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FDATA_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FDATA_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FDATA_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FDATA_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FDATA_TEST_UNREFERENCED_PARAMETER( argc )
	FDATA_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

	FDATA_TEST_RUN(
	 "libfdata_tree_node_initialize",
	 fdata_test_tree_node_initialize );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_free",
	 fdata_test_tree_node_free );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_free_single",
	 fdata_test_tree_node_free_single );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_parent_node",
	 fdata_test_tree_node_set_parent_node );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_is_root",
	 fdata_test_tree_node_is_root );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_data_range",
	 fdata_test_tree_node_get_data_range );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_data_range",
	 fdata_test_tree_node_set_data_range );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_sub_nodes_data_range_is_set",
	 fdata_test_tree_node_sub_nodes_data_range_is_set );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_sub_nodes_data_range",
	 fdata_test_tree_node_get_sub_nodes_data_range );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_sub_nodes_data_range",
	 fdata_test_tree_node_set_sub_nodes_data_range );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_timestamp",
	 fdata_test_tree_node_get_timestamp );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_first_leaf_node_index",
	 fdata_test_tree_node_get_first_leaf_node_index );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_first_leaf_node_index",
	 fdata_test_tree_node_set_first_leaf_node_index );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_node_value",
	 fdata_test_tree_node_get_node_value );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_node_value",
	 fdata_test_tree_node_set_node_value );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_resize_sub_nodes",
	 fdata_test_tree_node_resize_sub_nodes );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_number_of_sub_nodes",
	 fdata_test_tree_node_get_number_of_sub_nodes );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_sub_node_by_index",
	 fdata_test_tree_node_get_sub_node_by_index );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_sub_node_by_index",
	 fdata_test_tree_node_set_sub_node_by_index );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_append_sub_node",
	 fdata_test_tree_node_append_sub_node );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_insert_sub_node",
	 fdata_test_tree_node_insert_sub_node );

	/* TODO: add tests for libfdata_tree_node_split_sub_nodes */

	FDATA_TEST_RUN(
	 "libfdata_tree_node_is_deleted",
	 fdata_test_tree_node_is_deleted );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_deleted",
	 fdata_test_tree_node_set_deleted );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_deleted_sub_node",
	 fdata_test_tree_node_set_deleted_sub_node );

	/* TODO: add tests for libfdata_tree_node_set_calculate_leaf_node_values */

	/* TODO: add tests for libfdata_tree_node_read_leaf_node_values */

	FDATA_TEST_RUN(
	 "libfdata_tree_node_is_leaf",
	 fdata_test_tree_node_is_leaf );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_leaf",
	 fdata_test_tree_node_set_leaf );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_set_leaf_sub_node",
	 fdata_test_tree_node_set_leaf_sub_node );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_number_of_leaf_nodes",
	 fdata_test_tree_node_get_number_of_leaf_nodes );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_leaf_node_by_index",
	 fdata_test_tree_node_get_leaf_node_by_index );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_number_of_deleted_leaf_nodes",
	 fdata_test_tree_node_get_number_of_deleted_leaf_nodes );

	FDATA_TEST_RUN(
	 "libfdata_tree_node_get_deleted_leaf_node_by_index",
	 fdata_test_tree_node_get_deleted_leaf_node_by_index );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

