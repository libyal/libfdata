/*
 * Library mapped_range type test program
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libfdata/libfdata_mapped_range.h"

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

/* Tests the libfdata_mapped_range_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_mapped_range_initialize(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_mapped_range_t *mapped_range = NULL;
	int result                            = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests       = 1;
	int number_of_memset_fail_tests       = 1;
	int test_number                       = 0;
#endif

	/* Test regular cases
	 */
	result = libfdata_mapped_range_initialize(
	          &mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "mapped_range",
	 mapped_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_mapped_range_free(
	          &mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "mapped_range",
	 mapped_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_mapped_range_initialize(
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

	mapped_range = (libfdata_mapped_range_t *) 0x12345678UL;

	result = libfdata_mapped_range_initialize(
	          &mapped_range,
	          &error );

	mapped_range = NULL;

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
		/* Test libfdata_mapped_range_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_mapped_range_initialize(
		          &mapped_range,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( mapped_range != NULL )
			{
				libfdata_mapped_range_free(
				 &mapped_range,
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
			 "mapped_range",
			 mapped_range );

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
		/* Test libfdata_mapped_range_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_mapped_range_initialize(
		          &mapped_range,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( mapped_range != NULL )
			{
				libfdata_mapped_range_free(
				 &mapped_range,
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
			 "mapped_range",
			 mapped_range );

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
	if( mapped_range != NULL )
	{
		libfdata_mapped_range_free(
		 &mapped_range,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_mapped_range_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_mapped_range_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_mapped_range_free(
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

/* Tests the libfdata_mapped_range_clone function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_mapped_range_clone(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfdata_mapped_range_t *destination_mapped_range = NULL;
	libfdata_mapped_range_t *source_mapped_range      = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfdata_mapped_range_initialize(
	          &source_mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "source_mapped_range",
	 source_mapped_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_mapped_range_clone(
	          &destination_mapped_range,
	          source_mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "destination_mapped_range",
	 destination_mapped_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_mapped_range_free(
	          &destination_mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_mapped_range",
	 destination_mapped_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_mapped_range_clone(
	          &destination_mapped_range,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_mapped_range",
	 destination_mapped_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_mapped_range_clone(
	          NULL,
	          source_mapped_range,
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
	result = libfdata_mapped_range_free(
	          &source_mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "source_mapped_range",
	 source_mapped_range );

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
	if( destination_mapped_range != NULL )
	{
		libfdata_mapped_range_free(
		 &destination_mapped_range,
		 NULL );
	}
	if( source_mapped_range != NULL )
	{
		libfdata_mapped_range_free(
		 &source_mapped_range,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_mapped_range_get function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_mapped_range_get(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_mapped_range_t *mapped_range = NULL;
	size64_t size                         = 0;
	off64_t offset                        = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_mapped_range_initialize(
	          &mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "mapped_range",
	 mapped_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_mapped_range_get(
	          mapped_range,
	          &offset,
	          &size,
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
	result = libfdata_mapped_range_get(
	          NULL,
	          &offset,
	          &size,
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

	result = libfdata_mapped_range_get(
	          mapped_range,
	          NULL,
	          &size,
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

	result = libfdata_mapped_range_get(
	          mapped_range,
	          &offset,
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
	result = libfdata_mapped_range_free(
	          &mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "mapped_range",
	 mapped_range );

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
	if( mapped_range != NULL )
	{
		libfdata_mapped_range_free(
		 &mapped_range,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_mapped_range_set function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_mapped_range_set(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_mapped_range_t *mapped_range = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_mapped_range_initialize(
	          &mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "mapped_range",
	 mapped_range );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_mapped_range_set(
	          mapped_range,
	          1024,
	          2048,
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
	result = libfdata_mapped_range_set(
	          NULL,
	          1024,
	          2048,
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
	result = libfdata_mapped_range_free(
	          &mapped_range,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "mapped_range",
	 mapped_range );

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
	if( mapped_range != NULL )
	{
		libfdata_mapped_range_free(
		 &mapped_range,
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
	 "libfdata_mapped_range_initialize",
	 fdata_test_mapped_range_initialize );

	FDATA_TEST_RUN(
	 "libfdata_mapped_range_free",
	 fdata_test_mapped_range_free );

	FDATA_TEST_RUN(
	 "libfdata_mapped_range_clone",
	 fdata_test_mapped_range_clone );

	FDATA_TEST_RUN(
	 "libfdata_mapped_range_get",
	 fdata_test_mapped_range_get );

	FDATA_TEST_RUN(
	 "libfdata_mapped_range_set",
	 fdata_test_mapped_range_set );

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

