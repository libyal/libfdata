/*
 * Library list_element type test program
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

#include "../libfdata/libfdata_list_element.h"

int fdata_test_list_element_element_value_free_function_return_value = 1;

/* Test element value free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_list_element_element_value_free_function(
     intptr_t **element_value FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( element_value )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_list_element_element_value_free_function_return_value );
}

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

/* Tests the libfdata_list_element_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_initialize(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	int result                            = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests       = 2;
	int number_of_memset_fail_tests       = 1;
	int test_number                       = 0;
#endif

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_element_initialize(
	          NULL,
	          list,
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

	list_element = (libfdata_list_element_t *) 0x12345678UL;

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	list_element = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_list_element_initialize(
	          &list_element,
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

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
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

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 * 2 fail in memory_allocate of libfdata_range_initialize
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_list_element_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_list_element_initialize(
		          &list_element,
		          list,
		          0,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( list_element != NULL )
			{
				libfdata_list_element_free(
				 &list_element,
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
			 "list_element",
			 list_element );

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
		/* Test libfdata_list_element_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_list_element_initialize(
		          &list_element,
		          list,
		          0,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( list_element != NULL )
			{
				libfdata_list_element_free(
				 &list_element,
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
			 "list_element",
			 list_element );

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
	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_list_element_free(
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

/* Tests the libfdata_list_element_clone function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_clone(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfdata_list_t *list                             = NULL;
	libfdata_list_element_t *destination_list_element = NULL;
	libfdata_list_element_t *source_list_element      = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &source_list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "source_list_element",
	 source_list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_list_element_clone with initialized list_element
	 */
	result = libfdata_list_element_clone(
	          &destination_list_element,
	          source_list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "destination_list_element",
	 destination_list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_free(
	          &destination_list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_list_element",
	 destination_list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_list_element_clone with non-initialized list_element
	 */
	result = libfdata_list_element_clone(
	          &destination_list_element,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_list_element",
	 destination_list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_element_clone(
	          NULL,
	          source_list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_list_element",
	 destination_list_element );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	destination_list_element = (libfdata_list_element_t *) 0x12345678UL;

	result = libfdata_list_element_clone(
	          &destination_list_element,
	          source_list_element,
	          &error );

	destination_list_element = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_list_element",
	 destination_list_element );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* Test libfdata_list_element_clone with malloc failing
	 */
	fdata_test_malloc_attempts_before_fail = 0;

	result = libfdata_list_element_clone(
	          &destination_list_element,
	          source_list_element,
	          &error );

	if( fdata_test_malloc_attempts_before_fail != -1 )
	{
		fdata_test_malloc_attempts_before_fail = -1;

		if( destination_list_element != NULL )
		{
			libfdata_list_element_free(
			 &destination_list_element,
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
		 "destination_list_element",
		 destination_list_element );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfdata_list_element_clone with memset failing
	 */
	fdata_test_memset_attempts_before_fail = 0;

	result = libfdata_list_element_clone(
	          &destination_list_element,
	          source_list_element,
	          &error );

	if( fdata_test_memset_attempts_before_fail != -1 )
	{
		fdata_test_memset_attempts_before_fail = -1;

		if( destination_list_element != NULL )
		{
			libfdata_list_element_free(
			 &destination_list_element,
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
		 "destination_list_element",
		 destination_list_element );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FDATA_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfdata_list_element_free(
	          &source_list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "source_list_element",
	 source_list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( source_list_element != NULL )
	{
		libfdata_list_element_free(
		 &source_list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_get_element_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_get_element_index(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	int element_index                     = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_list_element_get_element_index(
	          list_element,
	          &element_index,
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
	result = libfdata_list_element_get_element_index(
	          NULL,
	          &element_index,
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

	result = libfdata_list_element_get_element_index(
	          list_element,
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
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_set_element_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_set_element_index(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_list_element_set_element_index(
	          list_element,
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
	result = libfdata_list_element_set_element_index(
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

	result = libfdata_list_element_set_element_index(
	          list_element,
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
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_get_timestamp function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_get_timestamp(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	int64_t timestamp                     = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_list_element_get_timestamp(
	          list_element,
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
	result = libfdata_list_element_get_timestamp(
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

	result = libfdata_list_element_get_timestamp(
	          list_element,
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
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_get_data_range function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_get_data_range(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	size64_t size                         = 0;
	off64_t offset                        = 0;
	uint32_t flags                        = 0;
	int file_index                        = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_list_element_get_data_range(
	          list_element,
	          &file_index,
	          &offset,
	          &size,
	          &flags,
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
	result = libfdata_list_element_get_data_range(
	          NULL,
	          &file_index,
	          &offset,
	          &size,
	          &flags,
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

	result = libfdata_list_element_get_data_range(
	          list_element,
	          NULL,
	          &offset,
	          &size,
	          &flags,
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

	result = libfdata_list_element_get_data_range(
	          list_element,
	          &file_index,
	          NULL,
	          &size,
	          &flags,
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

	result = libfdata_list_element_get_data_range(
	          list_element,
	          &file_index,
	          &offset,
	          NULL,
	          &flags,
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

	result = libfdata_list_element_get_data_range(
	          list_element,
	          &file_index,
	          &offset,
	          &size,
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
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_set_data_range function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_set_data_range(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_list_element_set_data_range(
	          list_element,
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
	result = libfdata_list_element_set_data_range(
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

	result = libfdata_list_element_set_data_range(
	          list_element,
	          -1,
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

	result = libfdata_list_element_set_data_range(
	          list_element,
	          1,
	          -1,
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

	result = libfdata_list_element_set_data_range(
	          list_element,
	          1,
	          1024,
	          (size64_t) INT64_MAX + 1,
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
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_get_mapped_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_get_mapped_size(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	size64_t mapped_size                  = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_list_element_get_mapped_size(
	          list_element,
	          &mapped_size,
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
	result = libfdata_list_element_set_mapped_size(
	          list_element,
	          512,
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
	result = libfdata_list_element_get_mapped_size(
	          list_element,
	          &mapped_size,
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
	result = libfdata_list_element_get_mapped_size(
	          NULL,
	          &mapped_size,
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

	result = libfdata_list_element_get_mapped_size(
	          list_element,
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
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_set_mapped_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_set_mapped_size(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_list_element_set_mapped_size(
	          list_element,
	          512,
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
	result = libfdata_list_element_set_mapped_size(
	          NULL,
	          512,
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
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_get_element_value function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_get_element_value(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	intptr_t *element_value               = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
/* TODO implement */

	/* Test error cases
	 */
	result = libfdata_list_element_get_element_value(
	          NULL,
	          NULL,
	          NULL,
	          &element_value,
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
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_element_set_element_value function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_element_set_element_value(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
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
	 "list",
	 list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_element_initialize(
	          &list_element,
	          list,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
/* TODO implement */

	/* Test error cases
	 */
	result = libfdata_list_element_set_element_value(
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
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfdata_list_element_free(
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "list",
	 list );

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
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
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
	 "libfdata_list_element_initialize",
	 fdata_test_list_element_initialize );

	FDATA_TEST_RUN(
	 "libfdata_list_element_free",
	 fdata_test_list_element_free );

	FDATA_TEST_RUN(
	 "libfdata_list_element_clone",
	 fdata_test_list_element_clone );

	FDATA_TEST_RUN(
	 "libfdata_list_element_get_element_index",
	 fdata_test_list_element_get_element_index );

	FDATA_TEST_RUN(
	 "libfdata_list_element_set_element_index",
	 fdata_test_list_element_set_element_index );

	FDATA_TEST_RUN(
	 "libfdata_list_element_get_timestamp",
	 fdata_test_list_element_get_timestamp );

	FDATA_TEST_RUN(
	 "libfdata_list_element_get_data_range",
	 fdata_test_list_element_get_data_range );

	FDATA_TEST_RUN(
	 "libfdata_list_element_set_data_range",
	 fdata_test_list_element_set_data_range );

	FDATA_TEST_RUN(
	 "libfdata_list_element_get_mapped_size",
	 fdata_test_list_element_get_mapped_size );

	FDATA_TEST_RUN(
	 "libfdata_list_element_set_mapped_size",
	 fdata_test_list_element_set_mapped_size );

	FDATA_TEST_RUN(
	 "libfdata_list_element_get_element_value",
	 fdata_test_list_element_get_element_value );

	FDATA_TEST_RUN(
	 "libfdata_list_element_set_element_value",
	 fdata_test_list_element_set_element_value );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

