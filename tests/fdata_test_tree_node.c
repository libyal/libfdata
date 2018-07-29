/*
 * Library tree_node type test program
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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
     intptr_t **node_value FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( node_value )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_tree_node_value_free_function_return_value );
}

/* Reads a node
 * Callback function for the tree
 * Returns 1 if successful or -1 on error
 */
int fdata_test_tree_read_node(
     intptr_t *data_handle,
     intptr_t *file_io_handle,
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
     intptr_t *file_io_handle,
     libfdata_tree_node_t *tree_node,
     libfdata_cache_t *cache,
     int sub_nodes_file_index,
     off64_t sub_nodes_offset,
     size64_t sub_nodes_size,
     uint32_t sub_nodes_flags,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	static char *function = "fdata_test_tree_read_sub_nodes";

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

	/* TODO: add tests for libfdata_tree_node_free_single */

	/* TODO: add tests for libfdata_tree_node_set_parent_node */

	/* TODO: add tests for libfdata_tree_node_is_root */

	/* TODO: add tests for libfdata_tree_node_get_data_range */

	/* TODO: add tests for libfdata_tree_node_set_data_range */

	/* TODO: add tests for libfdata_tree_node_sub_nodes_data_range_is_set */

	/* TODO: add tests for libfdata_tree_node_get_sub_nodes_data_range */

	/* TODO: add tests for libfdata_tree_node_set_sub_nodes_data_range */

	/* TODO: add tests for libfdata_tree_node_get_timestamp */

	/* TODO: add tests for libfdata_tree_node_get_first_leaf_node_index */

	/* TODO: add tests for libfdata_tree_node_set_first_leaf_node_index */

	/* TODO: add tests for libfdata_tree_node_get_node_value */

	/* TODO: add tests for libfdata_tree_node_set_node_value */

	/* TODO: add tests for libfdata_tree_node_resize_sub_nodes */

	/* TODO: add tests for libfdata_tree_node_get_number_of_sub_nodes */

	/* TODO: add tests for libfdata_tree_node_get_sub_node_by_index */

	/* TODO: add tests for libfdata_tree_node_set_sub_node_by_index */

	/* TODO: add tests for libfdata_tree_node_append_sub_node */

	/* TODO: add tests for libfdata_tree_node_insert_sub_node */

	/* TODO: add tests for libfdata_tree_node_split_sub_nodes */

	/* TODO: add tests for libfdata_tree_node_is_deleted */

	/* TODO: add tests for libfdata_tree_node_set_deleted */

	/* TODO: add tests for libfdata_tree_node_set_deleted_sub_node */

	/* TODO: add tests for libfdata_tree_node_set_calculate_leaf_node_values */

	/* TODO: add tests for libfdata_tree_node_read_leaf_node_values */

	/* TODO: add tests for libfdata_tree_node_is_leaf */

	/* TODO: add tests for libfdata_tree_node_set_leaf */

	/* TODO: add tests for libfdata_tree_node_set_leaf_sub_node */

	/* TODO: add tests for libfdata_tree_node_get_number_of_leaf_nodes */

	/* TODO: add tests for libfdata_tree_node_get_leaf_node_by_index */

	/* TODO: add tests for libfdata_tree_node_get_number_of_deleted_leaf_nodes */

	/* TODO: add tests for libfdata_tree_node_get_deleted_leaf_node_by_index */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

