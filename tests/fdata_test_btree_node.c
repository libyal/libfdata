/*
 * Library btree_node type test program
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fdata_test_libcerror.h"
#include "fdata_test_libfdata.h"
#include "fdata_test_macros.h"
#include "fdata_test_memory.h"
#include "fdata_test_unused.h"

#include "../libfdata/libfdata_btree_node.h"
#include "../libfdata/libfdata_definitions.h"

int fdata_test_btree_node_key_value_free_function_return_value = 1;

/* Test key value free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_btree_node_key_value_free_function(
     intptr_t **key_value FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( key_value )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_btree_node_key_value_free_function_return_value );
}

/* Test key_value compare function
 * Returns LIBFDATA_COMPARE_LESS, LIBFDATA_COMPARE_EQUAL, LIBFDATA_COMPARE_GREATER if successful or -1 on error
 */
int fdata_test_btree_node_key_value_compare_function(
     intptr_t *first_key_value,
     intptr_t *second_key_value,
     libfdata_error_t **error )
{
	static char *function = "fdata_test_btree_node_key_value_compare_function";

	if( first_key_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first key_value.",
		 function );

		return( -1 );
	}
	if( second_key_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second key_value.",
		 function );

		return( -1 );
	}
/* TODO implement */
	return( LIBFDATA_COMPARE_EQUAL );
}

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

/* Tests the libfdata_btree_node_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_btree_node_t *btree_node = NULL;
	int result                        = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_btree_node_initialize(
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

	btree_node = (libfdata_btree_node_t *) 0x12345678UL;

	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	btree_node = NULL;

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

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_btree_node_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_btree_node_initialize(
		          &btree_node,
		          0,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( btree_node != NULL )
			{
				libfdata_btree_node_free(
				 &btree_node,
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
			 "btree_node",
			 btree_node );

			FDATA_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_btree_node_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_btree_node_initialize(
		          &btree_node,
		          0,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( btree_node != NULL )
			{
				libfdata_btree_node_free(
				 &btree_node,
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
			 "btree_node",
			 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_btree_node_free(
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

/* Tests the libfdata_btree_node_get_level function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_get_level(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_btree_node_t *btree_node = NULL;
	int level                         = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_node_get_level(
	          btree_node,
	          &level,
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
	result = libfdata_btree_node_get_level(
	          NULL,
	          &level,
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

	result = libfdata_btree_node_get_level(
	          btree_node,
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
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_is_branch function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_is_branch(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_btree_node_t *btree_node = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_node_is_branch(
	          btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libfdata_internal_btree_node_t *) btree_node )->flags = LIBFDATA_BTREE_NODE_FLAG_IS_BRANCH;

	result = libfdata_btree_node_is_branch(
	          btree_node,
	          &error );

	( (libfdata_internal_btree_node_t *) btree_node )->flags = 0;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_btree_node_is_branch(
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
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_is_leaf function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_is_leaf(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_btree_node_t *btree_node = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_node_is_leaf(
	          btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libfdata_internal_btree_node_t *) btree_node )->flags = LIBFDATA_BTREE_NODE_FLAG_IS_LEAF;

	result = libfdata_btree_node_is_leaf(
	          btree_node,
	          &error );

	( (libfdata_internal_btree_node_t *) btree_node )->flags = 0;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_btree_node_is_leaf(
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
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_is_root function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_is_root(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_btree_node_t *btree_node = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	( (libfdata_internal_btree_node_t *) btree_node )->level = 1;

	result = libfdata_btree_node_is_root(
	          btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libfdata_internal_btree_node_t *) btree_node )->level = 0;

	result = libfdata_btree_node_is_root(
	          btree_node,
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
	( (libfdata_internal_btree_node_t *) btree_node )->level = 0;

	result = libfdata_btree_node_is_root(
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
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_get_number_of_sub_nodes function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_get_number_of_sub_nodes(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_btree_node_t *btree_node = NULL;
	int number_of_sub_nodes           = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_node_get_number_of_sub_nodes(
	          btree_node,
	          &number_of_sub_nodes,
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
	result = libfdata_btree_node_get_number_of_sub_nodes(
	          NULL,
	          &number_of_sub_nodes,
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

	result = libfdata_btree_node_get_number_of_sub_nodes(
	          btree_node,
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
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_get_sub_node_data_range_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_get_sub_node_data_range_by_index(
     void )
{
	libcerror_error_t *error                    = NULL;
	libfdata_btree_node_t *btree_node           = NULL;
	libfdata_btree_range_t *sub_node_data_range = 0;
	char *key_value                             = "key";
	int result                                  = 0;
	int sub_node_index                          = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_node_append_sub_node(
	          btree_node,
	          &sub_node_index,
	          1,
	          1024,
	          2048,
	          0,
	          (intptr_t *) key_value,
	          (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_node_key_value_free_function,
	          LIBFDATA_KEY_VALUE_FLAG_MANAGED,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	sub_node_data_range = NULL;

	result = libfdata_btree_node_get_sub_node_data_range_by_index(
	          btree_node,
	          0,
	          &sub_node_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "sub_node_data_range",
	 sub_node_data_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	sub_node_data_range = NULL;

	result = libfdata_btree_node_get_sub_node_data_range_by_index(
	          NULL,
	          0,
	          &sub_node_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "sub_node_data_range",
	 sub_node_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_btree_node_get_sub_node_data_range_by_index(
	          btree_node,
	          -1,
	          &sub_node_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "sub_node_data_range",
	 sub_node_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_btree_node_get_sub_node_data_range_by_index(
	          btree_node,
	          0,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "sub_node_data_range",
	 sub_node_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_get_sub_node_data_range_by_mapped_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_get_sub_node_data_range_by_mapped_index(
     void )
{
	libcerror_error_t *error                    = NULL;
	libfdata_btree_node_t *btree_node           = NULL;
	libfdata_btree_range_t *sub_node_data_range = 0;
	char *key_value                             = "key";
	int result                                  = 0;
	int sub_node_index                          = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_node_append_sub_node(
	          btree_node,
	          &sub_node_index,
	          1,
	          1024,
	          2048,
	          0,
	          (intptr_t *) key_value,
	          (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_node_key_value_free_function,
	          LIBFDATA_KEY_VALUE_FLAG_MANAGED,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	sub_node_data_range = NULL;

#ifdef TODO
/* TODO fix test */
	result = libfdata_btree_node_get_sub_node_data_range_by_mapped_index(
	          btree_node,
	          0,
	          &sub_node_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "sub_node_data_range",
	 sub_node_data_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	sub_node_data_range = NULL;

	result = libfdata_btree_node_get_sub_node_data_range_by_mapped_index(
	          NULL,
	          0,
	          &sub_node_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "sub_node_data_range",
	 sub_node_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_btree_node_get_sub_node_data_range_by_mapped_index(
	          btree_node,
	          -1,
	          &sub_node_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "sub_node_data_range",
	 sub_node_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_btree_node_get_sub_node_data_range_by_mapped_index(
	          btree_node,
	          0,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "sub_node_data_range",
	 sub_node_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_get_number_of_leaf_values_in_branch function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_get_number_of_leaf_values_in_branch(
     void )
{
	libcerror_error_t *error            = NULL;
	libfdata_btree_node_t *btree_node   = NULL;
	int number_of_leaf_values_in_branch = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_node_get_number_of_leaf_values_in_branch(
	          btree_node,
	          &number_of_leaf_values_in_branch,
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
	result = libfdata_btree_node_get_number_of_leaf_values_in_branch(
	          NULL,
	          &number_of_leaf_values_in_branch,
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

	result = libfdata_btree_node_get_number_of_leaf_values_in_branch(
		  btree_node,
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
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_get_number_of_leaf_values function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_get_number_of_leaf_values(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_btree_node_t *btree_node = NULL;
	int number_of_leaf_values         = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_node_get_number_of_leaf_values(
	          btree_node,
	          &number_of_leaf_values,
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
	result = libfdata_btree_node_get_number_of_leaf_values(
	          NULL,
	          &number_of_leaf_values,
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

	result = libfdata_btree_node_get_number_of_leaf_values(
	          btree_node,
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
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_get_leaf_value_data_range_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_get_leaf_value_data_range_by_index(
     void )
{
	libcerror_error_t *error                      = NULL;
	libfdata_btree_node_t *btree_node             = NULL;
	libfdata_btree_range_t *leaf_value_data_range = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_btree_node_get_leaf_value_data_range_by_index(
	          btree_node,
	          0,
	          &leaf_value_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "leaf_value_data_range",
	 leaf_value_data_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_btree_node_get_leaf_value_data_range_by_index(
	          NULL,
	          0,
	          &leaf_value_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "leaf_value_data_range",
	 leaf_value_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_btree_node_get_leaf_value_data_range_by_index(
	          btree_node,
	          -1,
	          &leaf_value_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "leaf_value_data_range",
	 leaf_value_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_btree_node_get_leaf_value_data_range_by_index(
	          btree_node,
	          0,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "leaf_value_data_range",
	 leaf_value_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_node_get_leaf_value_data_range_by_mapped_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_node_get_leaf_value_data_range_by_mapped_index(
     void )
{
	libcerror_error_t *error                      = NULL;
	libfdata_btree_node_t *btree_node             = NULL;
	libfdata_btree_range_t *leaf_value_data_range = 0;
	int result                                    = 0;

	/* Initialize test
	 */

	result = libfdata_btree_node_initialize(
	          &btree_node,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_node",
	 btree_node );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_btree_node_get_leaf_value_data_range_by_mapped_index(
	          btree_node,
	          0,
	          &leaf_value_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "leaf_value_data_range",
	 leaf_value_data_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_btree_node_get_leaf_value_data_range_by_mapped_index(
	          NULL,
	          0,
	          &leaf_value_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "leaf_value_data_range",
	 leaf_value_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_btree_node_get_leaf_value_data_range_by_mapped_index(
	          btree_node,
	          -1,
	          &leaf_value_data_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "leaf_value_data_range",
	 leaf_value_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_btree_node_get_leaf_value_data_range_by_mapped_index(
	          btree_node,
	          0,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "leaf_value_data_range",
	 leaf_value_data_range );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_btree_node_free(
	          &btree_node,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_node",
	 btree_node );

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
	if( btree_node != NULL )
	{
		libfdata_btree_node_free(
		 &btree_node,
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
	 "libfdata_btree_node_initialize",
	 fdata_test_btree_node_initialize );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_free",
	 fdata_test_btree_node_free );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_get_level",
	 fdata_test_btree_node_get_level );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_is_branch",
	 fdata_test_btree_node_is_branch );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_is_leaf",
	 fdata_test_btree_node_is_leaf );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_is_root",
	 fdata_test_btree_node_is_root );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_get_number_of_sub_nodes",
	 fdata_test_btree_node_get_number_of_sub_nodes );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_get_sub_node_data_range_by_index",
	 fdata_test_btree_node_get_sub_node_data_range_by_index );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_get_sub_node_data_range_by_mapped_index",
	 fdata_test_btree_node_get_sub_node_data_range_by_mapped_index );

	/* TODO: add tests for libfdata_btree_node_get_sub_node_data_range_by_key */

	/* TODO: add tests for libfdata_btree_node_get_sub_node_by_index */

	/* TODO: add tests for libfdata_btree_node_set_sub_node_by_index */

	/* TODO: add tests for libfdata_btree_node_append_sub_node */

	FDATA_TEST_RUN(
	 "libfdata_btree_node_get_number_of_leaf_values_in_branch",
	 fdata_test_btree_node_get_number_of_leaf_values_in_branch );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_get_number_of_leaf_values",
	 fdata_test_btree_node_get_number_of_leaf_values );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_get_leaf_value_data_range_by_index",
	 fdata_test_btree_node_get_leaf_value_data_range_by_index );

	FDATA_TEST_RUN(
	 "libfdata_btree_node_get_leaf_value_data_range_by_mapped_index",
	 fdata_test_btree_node_get_leaf_value_data_range_by_mapped_index );

	/* TODO: add tests for libfdata_btree_node_get_leaf_value_data_range_by_key */

	/* TODO: add tests for libfdata_btree_node_get_leaf_value_by_index */

	/* TODO: add tests for libfdata_btree_node_get_leaf_value_by_key */

	/* TODO: add tests for libfdata_btree_node_set_leaf_value_by_index */

	/* TODO: add tests for libfdata_btree_node_append_leaf_value */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

