/*
 * Library tree type test program
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

#include "../libfdata/libfdata_tree.h"

/* TODO remove once tree and tree node have been added to the library include file */
#include "../libfdata/libfdata_tree_node.h"

int fdata_test_tree_data_handle_free_function_return_value  = 1;
int fdata_test_tree_data_handle_clone_function_return_value = 1;
int fdata_test_tree_node_value_free_function_return_value   = 1;

/* Test data handle free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_tree_data_handle_free_function(
     intptr_t **data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_tree_data_handle_free_function_return_value );
}

/* Test data handle clone function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_tree_data_handle_clone_function(
     intptr_t **destination_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *source_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( destination_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( source_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_tree_data_handle_clone_function_return_value );
}

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

/* Tests the libfdata_tree_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	int result                      = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
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

	/* Test error cases
	 */
	result = libfdata_tree_initialize(
	          NULL,
	          NULL,
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
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

	tree = (libfdata_tree_t *) 0x12345678UL;

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	tree = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
	          NULL,
	          &fdata_test_tree_read_sub_nodes,
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

	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
	          &fdata_test_tree_read_node,
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

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_tree_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_tree_initialize(
		          &tree,
		          NULL,
		          &fdata_test_tree_data_handle_free_function,
		          &fdata_test_tree_data_handle_clone_function,
		          &fdata_test_tree_read_node,
		          &fdata_test_tree_read_sub_nodes,
		          0,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( tree != NULL )
			{
				libfdata_tree_free(
				 &tree,
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
			 "tree",
			 tree );

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
		/* Test libfdata_tree_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_tree_initialize(
		          &tree,
		          NULL,
		          &fdata_test_tree_data_handle_free_function,
		          &fdata_test_tree_data_handle_clone_function,
		          &fdata_test_tree_read_node,
		          &fdata_test_tree_read_sub_nodes,
		          0,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( tree != NULL )
			{
				libfdata_tree_free(
				 &tree,
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
			 "tree",
			 tree );

			FDATA_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FDATA_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_tree_free(
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

/* Tests the libfdata_tree_clone function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_clone(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_tree_t *destination_tree = NULL;
	libfdata_tree_t *source_tree      = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &source_tree,
	          NULL,
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
	          &fdata_test_tree_read_node,
	          &fdata_test_tree_read_sub_nodes,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "source_tree",
	 source_tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_tree_clone with initialized tree
	 */
	result = libfdata_tree_clone(
	          &destination_tree,
	          source_tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "destination_tree",
	 destination_tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_tree_free(
	          &destination_tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_tree",
	 destination_tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_tree_clone with non-initialized tree
	 */
	result = libfdata_tree_clone(
	          &destination_tree,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_tree",
	 destination_tree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_tree_clone(
	          NULL,
	          source_tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_tree",
	 destination_tree );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	destination_tree = (libfdata_tree_t *) 0x12345678UL;

	result = libfdata_tree_clone(
	          &destination_tree,
	          source_tree,
	          &error );

	destination_tree = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_tree",
	 destination_tree );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* Test libfdata_tree_clone with malloc failing
	 */
	fdata_test_malloc_attempts_before_fail = 0;

	result = libfdata_tree_clone(
	          &destination_tree,
	          source_tree,
	          &error );

	if( fdata_test_malloc_attempts_before_fail != -1 )
	{
		fdata_test_malloc_attempts_before_fail = -1;

		if( destination_tree != NULL )
		{
			libfdata_tree_free(
			 &destination_tree,
			 &error );
		}
	}
	else
	{
		FDATA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FDATA_TEST_ASSERT_IS_NULL(
		 "destination_tree",
		 destination_tree );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfdata_tree_clone with memset failing
	 */
	fdata_test_memset_attempts_before_fail = 0;

	result = libfdata_tree_clone(
	          &destination_tree,
	          source_tree,
	          &error );

	if( fdata_test_memset_attempts_before_fail != -1 )
	{
		fdata_test_memset_attempts_before_fail = -1;

		if( destination_tree != NULL )
		{
			libfdata_tree_free(
			 &destination_tree,
			 &error );
		}
	}
	else
	{
		FDATA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FDATA_TEST_ASSERT_IS_NULL(
		 "destination_tree",
		 destination_tree );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FDATA_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfdata_tree_free(
	          &source_tree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "source_tree",
	 source_tree );

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
	if( source_tree != NULL )
	{
		libfdata_tree_free(
		 &source_tree,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

/* Tests the libfdata_tree_get_node_value function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_get_node_value(
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
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
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
	/* Test libfdata_tree_get_node_value with failing libfcache_cache_get_value_by_index
	 */
	result = libfdata_tree_get_node_value(
	          NULL,
	          NULL,
	          cache,
	          tree_node,
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

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_get_node_value(
	          tree,
	          NULL,
	          cache,
	          tree_node,
	          &node_value,
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
	result = libfdata_tree_get_node_value(
	          NULL,
	          NULL,
	          cache,
	          tree_node,
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

	/* Test libfdata_tree_get_node_value with failing libfcache_cache_get_number_of_entries
	 */
	result = libfdata_tree_get_node_value(
	          tree,
	          NULL,
	          NULL,
	          tree_node,
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

	/* Test libfdata_tree_get_node_value with failing libfdata_tree_node_get_data_range
	 */
	result = libfdata_tree_get_node_value(
	          tree,
	          NULL,
	          cache,
	          NULL,
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

	result = libfdata_tree_get_node_value(
	          tree,
	          NULL,
	          cache,
	          tree_node,
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

/* Tests the libfdata_tree_set_node_value function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_set_node_value(
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
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
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
	/* Test libfdata_tree_set_node_value with failing libfcache_cache_get_value_by_index
	 */
	result = libfdata_tree_set_node_value(
	          NULL,
	          cache,
	          tree_node,
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

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_set_node_value(
	          tree,
	          cache,
	          tree_node,
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
#endif

	/* Test error cases
	 */
	result = libfdata_tree_set_node_value(
	          NULL,
	          cache,
	          tree_node,
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

	/* Test libfdata_tree_set_node_value with failing libfcache_cache_get_number_of_entries
	 */
	result = libfdata_tree_set_node_value(
	          tree,
	          NULL,
	          tree_node,
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

	/* Test libfdata_tree_set_node_value with failing libfdata_tree_node_get_data_range
	 */
	result = libfdata_tree_set_node_value(
	          tree,
	          cache,
	          NULL,
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

	result = libfdata_tree_set_node_value(
	          tree,
	          cache,
	          tree_node,
	          NULL,
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

	result = libfdata_tree_set_node_value(
	          tree,
	          cache,
	          tree_node,
	          NULL,
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
	/* TODO: add tests for libfdata_tree_read_sub_nodes */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

/* Tests the libfdata_tree_get_root_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_get_root_node(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *root_node = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
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

	result = libfdata_tree_set_root_node(
	          tree,
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
	root_node = NULL;

	result = libfdata_tree_get_root_node(
	          tree,
	          &root_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "root_node",
	 root_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	root_node = NULL;

	result = libfdata_tree_get_root_node(
	          NULL,
	          &root_node,
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

	result = libfdata_tree_get_root_node(
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
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_set_root_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_set_root_node(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_tree_t *tree    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_tree_initialize(
	          &tree,
	          NULL,
	          &fdata_test_tree_data_handle_free_function,
	          &fdata_test_tree_data_handle_clone_function,
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
	result = libfdata_tree_set_root_node(
	          tree,
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
	result = libfdata_tree_set_root_node(
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
	if( tree != NULL )
	{
		libfdata_tree_free(
		 &tree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_tree_get_number_of_leaf_nodes function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_get_number_of_leaf_nodes(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_cache_t *cache  = NULL;
	libfdata_tree_t *tree    = NULL;
	int number_of_leaf_nodes = 0;
	int result               = 0;

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

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_get_number_of_leaf_nodes(
	          tree,
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

	/* Test error cases
	 */
	result = libfdata_tree_get_number_of_leaf_nodes(
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

	result = libfdata_tree_get_number_of_leaf_nodes(
	          tree,
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

/* Tests the libfdata_tree_get_leaf_node_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_get_leaf_node_by_index(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_cache_t *cache         = NULL;
	libfdata_tree_t *tree           = NULL;
	libfdata_tree_node_t *leaf_node = NULL;
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

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	leaf_node = NULL;

	result = libfdata_tree_get_leaf_node_by_index(
	          tree,
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

	result = libfdata_tree_get_leaf_node_by_index(
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

/* Tests the libfdata_tree_get_number_of_deleted_leaf_nodes function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_get_number_of_deleted_leaf_nodes(
     void )
{
	libcerror_error_t *error         = NULL;
	libfdata_cache_t *cache          = NULL;
	libfdata_tree_t *tree            = NULL;
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

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_tree_get_number_of_deleted_leaf_nodes(
	          tree,
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

	/* Test error cases
	 */
	result = libfdata_tree_get_number_of_deleted_leaf_nodes(
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

	result = libfdata_tree_get_number_of_deleted_leaf_nodes(
	          tree,
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

/* Tests the libfdata_tree_get_deleted_leaf_node_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_tree_get_deleted_leaf_node_by_index(
     void )
{
	libcerror_error_t *error                = NULL;
	libfdata_cache_t *cache                 = NULL;
	libfdata_tree_t *tree                   = NULL;
	libfdata_tree_node_t *deleted_leaf_node = NULL;
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

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	deleted_leaf_node = NULL;

	result = libfdata_tree_get_deleted_leaf_node_by_index(
	          tree,
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

	result = libfdata_tree_get_deleted_leaf_node_by_index(
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

	FDATA_TEST_RUN(
	 "libfdata_tree_initialize",
	 fdata_test_tree_initialize );

	FDATA_TEST_RUN(
	 "libfdata_tree_free",
	 fdata_test_tree_free );

#ifdef TODO
/* TODO fix clone function */
	FDATA_TEST_RUN(
	 "libfdata_tree_clone",
	 fdata_test_tree_clone );
#endif

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

	FDATA_TEST_RUN(
	 "libfdata_tree_get_node_value",
	 fdata_test_tree_get_node_value );

	FDATA_TEST_RUN(
	 "libfdata_tree_set_node_value",
	 fdata_test_tree_set_node_value );

	/* TODO: add tests for libfdata_tree_read_sub_nodes */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	FDATA_TEST_RUN(
	 "libfdata_tree_get_root_node",
	 fdata_test_tree_get_root_node );

	FDATA_TEST_RUN(
	 "libfdata_tree_set_root_node",
	 fdata_test_tree_set_root_node );

	FDATA_TEST_RUN(
	 "libfdata_tree_get_number_of_leaf_nodes",
	 fdata_test_tree_get_number_of_leaf_nodes );

	FDATA_TEST_RUN(
	 "libfdata_tree_get_leaf_node_by_index",
	 fdata_test_tree_get_leaf_node_by_index );

	FDATA_TEST_RUN(
	 "libfdata_tree_get_number_of_deleted_leaf_nodes",
	 fdata_test_tree_get_number_of_deleted_leaf_nodes );

	FDATA_TEST_RUN(
	 "libfdata_tree_get_deleted_leaf_node_by_index",
	 fdata_test_tree_get_deleted_leaf_node_by_index );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

