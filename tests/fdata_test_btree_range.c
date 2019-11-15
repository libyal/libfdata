/*
 * Library btree_range type test program
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libfdata/libfdata_btree_range.h"

int fdata_test_btree_range_key_value_free_function_return_value = 1;

/* Test key value free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_btree_range_key_value_free_function(
     intptr_t **key_value FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( key_value )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_btree_range_key_value_free_function_return_value );
}

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

/* Tests the libfdata_btree_range_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_range_initialize(
     void )
{
	libcerror_error_t *error            = NULL;
	libfdata_btree_range_t *btree_range = NULL;
	int result                          = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests     = 1;
	int number_of_memset_fail_tests     = 1;
	int test_number                     = 0;
#endif

	/* Test regular cases
	 */
	result = libfdata_btree_range_initialize(
	          &btree_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "btree_range",
	 btree_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_range_free(
	          &btree_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "btree_range",
	 btree_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_btree_range_initialize(
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

	btree_range = (libfdata_btree_range_t *) 0x12345678UL;

	result = libfdata_btree_range_initialize(
	          &btree_range,
	          &error );

	btree_range = NULL;

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
		/* Test libfdata_btree_range_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_btree_range_initialize(
		          &btree_range,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( btree_range != NULL )
			{
				libfdata_btree_range_free(
				 &btree_range,
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
			 "btree_range",
			 btree_range );

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
		/* Test libfdata_btree_range_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_btree_range_initialize(
		          &btree_range,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( btree_range != NULL )
			{
				libfdata_btree_range_free(
				 &btree_range,
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
			 "btree_range",
			 btree_range );

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
	if( btree_range != NULL )
	{
		libfdata_btree_range_free(
		 &btree_range,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_range_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_range_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_btree_range_free(
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

/* Tests the libfdata_btree_range_clone function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_range_clone(
     void )
{
	libcerror_error_t *error                        = NULL;
	libfdata_btree_range_t *destination_btree_range = NULL;
	libfdata_btree_range_t *source_btree_range      = NULL;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libfdata_btree_range_initialize(
	          &source_btree_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "source_btree_range",
	 source_btree_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_range_clone(
	          &destination_btree_range,
	          source_btree_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "destination_btree_range",
	 destination_btree_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_range_free(
	          &destination_btree_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_btree_range",
	 destination_btree_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_range_clone(
	          &destination_btree_range,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_btree_range",
	 destination_btree_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_btree_range_clone(
	          NULL,
	          source_btree_range,
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
	result = libfdata_btree_range_free(
	          &source_btree_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "source_btree_range",
	 source_btree_range );

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
	if( destination_btree_range != NULL )
	{
		libfdata_btree_range_free(
		 &destination_btree_range,
		 NULL );
	}
	if( source_btree_range != NULL )
	{
		libfdata_btree_range_free(
		 &source_btree_range,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_range_get function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_range_get(
     void )
{
	libcerror_error_t *error      = NULL;
	libfdata_btree_range_t *range = NULL;
	intptr_t *key_value           = 0;
	size64_t data_size            = 0;
	off64_t data_offset           = 0;
	uint32_t data_flags           = 0;
	int data_file_index           = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfdata_btree_range_initialize(
	          &range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "range",
	 range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	key_value = NULL;

	result = libfdata_btree_range_get(
	          range,
	          &data_file_index,
	          &data_offset,
	          &data_size,
	          &data_flags,
	          &key_value,
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
	key_value = NULL;

	result = libfdata_btree_range_get(
	          NULL,
	          &data_file_index,
	          &data_offset,
	          &data_size,
	          &data_flags,
	          &key_value,
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

	result = libfdata_btree_range_get(
	          range,
	          NULL,
	          &data_offset,
	          &data_size,
	          &data_flags,
	          &key_value,
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

	result = libfdata_btree_range_get(
	          range,
	          &data_file_index,
	          NULL,
	          &data_size,
	          &data_flags,
	          &key_value,
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

	result = libfdata_btree_range_get(
	          range,
	          &data_file_index,
	          &data_offset,
	          NULL,
	          &data_flags,
	          &key_value,
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

	result = libfdata_btree_range_get(
	          range,
	          &data_file_index,
	          &data_offset,
	          &data_size,
	          NULL,
	          &key_value,
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

	result = libfdata_btree_range_get(
	          range,
	          &data_file_index,
	          &data_offset,
	          &data_size,
	          &data_flags,
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
	result = libfdata_btree_range_free(
	          &range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "range",
	 range );

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
	if( range != NULL )
	{
		libfdata_btree_range_free(
		 &range,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_btree_range_set function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_btree_range_set(
     void )
{
	libcerror_error_t *error      = NULL;
	libfdata_btree_range_t *range = NULL;
	char *key_value               = "key";
	int result                    = 0;

	/* Initialize test
	 */
	result = libfdata_btree_range_initialize(
	          &range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "range",
	 range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_btree_range_set(
	          range,
	          1,
	          1024,
	          2048,
	          0,
	          (intptr_t *) key_value,
	          (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_range_key_value_free_function,
	          LIBFDATA_KEY_VALUE_FLAG_MANAGED,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_btree_range_set(
	          range,
	          1,
	          1024,
	          2048,
	          0,
	          (intptr_t *) key_value,
	          (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_range_key_value_free_function,
	          LIBFDATA_KEY_VALUE_FLAG_MANAGED,
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
	result = libfdata_btree_range_set(
	          NULL,
	          1,
	          1024,
	          2048,
	          0,
	          (intptr_t *) key_value,
	          (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_range_key_value_free_function,
	          LIBFDATA_KEY_VALUE_FLAG_MANAGED,
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

	/* Test libfdata_btree_range_set with free_key_value function failing
	 */
	fdata_test_btree_range_key_value_free_function_return_value = -1;

	result = libfdata_btree_range_set(
	          range,
	          1,
	          1024,
	          2048,
	          0,
	          (intptr_t *) key_value,
	          (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_range_key_value_free_function,
	          LIBFDATA_KEY_VALUE_FLAG_MANAGED,
	          &error );

	fdata_test_btree_range_key_value_free_function_return_value = 1;

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
	result = libfdata_btree_range_free(
	          &range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "range",
	 range );

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
	if( range != NULL )
	{
		libfdata_btree_range_free(
		 &range,
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
	 "libfdata_btree_range_initialize",
	 fdata_test_btree_range_initialize );

	FDATA_TEST_RUN(
	 "libfdata_btree_range_free",
	 fdata_test_btree_range_free );

	FDATA_TEST_RUN(
	 "libfdata_btree_range_clone",
	 fdata_test_btree_range_clone );

	FDATA_TEST_RUN(
	 "libfdata_btree_range_get",
	 fdata_test_btree_range_get );

	FDATA_TEST_RUN(
	 "libfdata_btree_range_set",
	 fdata_test_btree_range_set );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

