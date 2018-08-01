/*
 * Library btree type test program
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libfdata/libfdata_btree.h"

int fdata_test_btree_data_handle_free_function_return_value  = 1;
int fdata_test_btree_data_handle_clone_function_return_value = 1;

/* Test data handle free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_btree_data_handle_free_function(
     intptr_t **data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_btree_data_handle_free_function_return_value );
}

/* Test data handle clone function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_btree_data_handle_clone_function(
     intptr_t **destination_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *source_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( destination_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( source_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_btree_data_handle_clone_function_return_value );
}

/* Test key_value compare function
 * Returns LIBCDATA_COMPARE_LESS, LIBCDATA_COMPARE_EQUAL, LIBCDATA_COMPARE_GREATER if successful or -1 on error
 */
int fdata_test_btree_key_value_compare_function(
     intptr_t *first_key_value,
     intptr_t *second_key_value,
     libfdata_error_t **error )
{
	static char *function = "fdata_test_btree_key_value_compare_function";

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
	return( LIBCDATA_COMPARE_EQUAL );
}

/* Tests the libfdata_btree_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_btree_t *btree         = NULL;
	int result                      = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfdata_btree_initialize(
	          &btree,
	          NULL,
	          &fdata_test_btree_data_handle_free_function,
	          &fdata_test_btree_data_handle_clone_function,
	          NULL,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree",
	 btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_free(
	          &btree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree",
	 btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_btree_initialize(
	          NULL,
	          NULL,
	          &fdata_test_btree_data_handle_free_function,
	          &fdata_test_btree_data_handle_clone_function,
	          NULL,
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

	btree = (libfdata_btree_t *) 0x12345678UL;

	result = libfdata_btree_initialize(
	          &btree,
	          NULL,
	          &fdata_test_btree_data_handle_free_function,
	          &fdata_test_btree_data_handle_clone_function,
	          NULL,
	          NULL,
	          0,
	          &error );

	btree = NULL;

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
	 * 2 fail in memory_allocate of libfdata_btree_initialize of elements_array
	 * 3 fail in memory_allocate of libfdata_btree_initialize of mapped_ranges_array
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_btree_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_btree_initialize(
		          &btree,
		          NULL,
		          &fdata_test_btree_data_handle_free_function,
		          &fdata_test_btree_data_handle_clone_function,
		          NULL,
		          NULL,
		          0,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( btree != NULL )
			{
				libfdata_btree_free(
				 &btree,
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
			 "btree",
			 btree );

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
		/* Test libfdata_btree_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_btree_initialize(
		          &btree,
		          NULL,
		          &fdata_test_btree_data_handle_free_function,
		          &fdata_test_btree_data_handle_clone_function,
		          NULL,
		          NULL,
		          0,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( btree != NULL )
			{
				libfdata_btree_free(
				 &btree,
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
			 "btree",
			 btree );

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
	if( btree != NULL )
	{
		libfdata_btree_free(
		 &btree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_btree_free(
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

/* Tests the libfdata_btree_clone function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_clone(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_btree_t *destination_btree = NULL;
	libfdata_btree_t *source_btree      = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_btree_initialize(
	          &source_btree,
	          NULL,
	          &fdata_test_btree_data_handle_free_function,
	          &fdata_test_btree_data_handle_clone_function,
	          NULL,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "source_btree",
	 source_btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_btree_clone with intialized btree
	 */
	result = libfdata_btree_clone(
	          &destination_btree,
	          source_btree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "destination_btree",
	 destination_btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_free(
	          &destination_btree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_btree",
	 destination_btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_btree_clone with non-intialized btree
	 */
	result = libfdata_btree_clone(
	          &destination_btree,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_btree",
	 destination_btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_btree_clone(
	          NULL,
	          source_btree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_btree",
	 destination_btree );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	destination_btree = (libfdata_btree_t *) 0x12345678UL;

	result = libfdata_btree_clone(
	          &destination_btree,
	          source_btree,
	          &error );

	destination_btree = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_btree",
	 destination_btree );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* Test libfdata_btree_clone with malloc failing
	 */
	fdata_test_malloc_attempts_before_fail = 0;

	result = libfdata_btree_clone(
	          &destination_btree,
	          source_btree,
	          &error );

	if( fdata_test_malloc_attempts_before_fail != -1 )
	{
		fdata_test_malloc_attempts_before_fail = -1;

		if( destination_btree != NULL )
		{
			libfdata_btree_free(
			 &destination_btree,
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
		 "destination_btree",
		 destination_btree );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfdata_btree_clone with memset failing
	 */
	fdata_test_memset_attempts_before_fail = 0;

	result = libfdata_btree_clone(
	          &destination_btree,
	          source_btree,
	          &error );

	if( fdata_test_memset_attempts_before_fail != -1 )
	{
		fdata_test_memset_attempts_before_fail = -1;

		if( destination_btree != NULL )
		{
			libfdata_btree_free(
			 &destination_btree,
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
		 "destination_btree",
		 destination_btree );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FDATA_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfdata_btree_free(
	          &source_btree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "source_btree",
	 source_btree );

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
	if( source_btree != NULL )
	{
		libfdata_btree_free(
		 &source_btree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_get_root_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_get_root_node(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_btree_t *btree  = NULL;
	size64_t node_data_size  = 0;
	off64_t node_data_offset = 0;
	uint32_t node_data_flags = 0;
	int node_data_file_index = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_btree_initialize(
	          &btree,
	          NULL,
	          &fdata_test_btree_data_handle_free_function,
	          &fdata_test_btree_data_handle_clone_function,
	          NULL,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree",
	 btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_set_root_node(
	          btree,
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
	result = libfdata_btree_get_root_node(
	          btree,
	          &node_data_file_index,
	          &node_data_offset,
	          &node_data_size,
	          &node_data_flags,
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
	result = libfdata_btree_get_root_node(
	          NULL,
	          &node_data_file_index,
	          &node_data_offset,
	          &node_data_size,
	          &node_data_flags,
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

	result = libfdata_btree_get_root_node(
	          btree,
	          NULL,
	          &node_data_offset,
	          &node_data_size,
	          &node_data_flags,
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

	result = libfdata_btree_get_root_node(
	          btree,
	          &node_data_file_index,
	          NULL,
	          &node_data_size,
	          &node_data_flags,
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

	result = libfdata_btree_get_root_node(
	          btree,
	          &node_data_file_index,
	          &node_data_offset,
	          NULL,
	          &node_data_flags,
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

	result = libfdata_btree_get_root_node(
	          btree,
	          &node_data_file_index,
	          &node_data_offset,
	          &node_data_size,
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
	result = libfdata_btree_free(
	          &btree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree",
	 btree );

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
	if( btree != NULL )
	{
		libfdata_btree_free(
		 &btree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_set_root_node function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_set_root_node(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_btree_t *btree  = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_btree_initialize(
	          &btree,
	          NULL,
	          &fdata_test_btree_data_handle_free_function,
	          &fdata_test_btree_data_handle_clone_function,
	          NULL,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree",
	 btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_set_root_node(
	          btree,
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
	result = libfdata_btree_set_root_node(
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
	result = libfdata_btree_free(
	          &btree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree",
	 btree );

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
	if( btree != NULL )
	{
		libfdata_btree_free(
		 &btree,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_get_number_of_leaf_values function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_get_number_of_leaf_values(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_btree_t *btree   = NULL;
	libfdata_cache_t *cache   = NULL;
	int number_of_leaf_values = 0;
	int result                = 0;

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

	result = libfdata_btree_initialize(
	          &btree,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree",
	 btree );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
#ifdef TODO
/* TODO fix test */
	result = libfdata_btree_get_number_of_leaf_values(
	          btree,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_leaf_values,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_leaf_values",
	 number_of_leaf_values,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_btree_get_number_of_leaf_values(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          &number_of_leaf_values,
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

	result = libfdata_btree_get_number_of_leaf_values(
	          btree,
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

	result = libfdata_btree_free(
	          &btree,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree",
	 btree );

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
	if( btree != NULL )
	{
		libfdata_btree_free(
		 &btree,
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
	 "libfdata_btree_initialize",
	 fdata_test_btree_initialize );

	FDATA_TEST_RUN(
	 "libfdata_btree_free",
	 fdata_test_btree_free );

	FDATA_TEST_RUN(
	 "libfdata_btree_clone",
	 fdata_test_btree_clone );

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

	/* TODO: add tests for libfdata_btree_calculate_node_cache_entry_index */

	/* TODO: add tests for libfdata_btree_calculate_leaf_value_cache_entry_index */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	FDATA_TEST_RUN(
	 "libfdata_btree_get_root_node",
	 fdata_test_btree_get_root_node );

	FDATA_TEST_RUN(
	 "libfdata_btree_set_root_node",
	 fdata_test_btree_set_root_node );

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

	/* TODO: add tests for libfdata_btree_read_leaf_value */

	/* TODO: add tests for libfdata_btree_read_node */

	/* TODO: add tests for libfdata_btree_read_sub_tree */

	/* TODO: add tests for libfdata_btree_get_leaf_node_by_index */

	/* TODO: add tests for libfdata_btree_get_leaf_node_by_key */

	/* TODO: add tests for libfdata_btree_get_next_leaf_node_by_key */

	/* TODO: add tests for libfdata_btree_get_previous_leaf_node_by_key */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	/* TODO: add tests for libfdata_btree_get_number_of_leaf_values */

	/* TODO: add tests for libfdata_btree_get_leaf_value_by_index */

	/* TODO: add tests for libfdata_btree_set_leaf_value_by_index */

	/* TODO: add tests for libfdata_btree_get_leaf_value_by_key */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

