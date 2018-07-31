/*
 * Library list type test program
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

#include "../libfdata/libfdata_list.h"

int fdata_test_list_data_handle_free_function_return_value   = 1;
int fdata_test_list_data_handle_clone_function_return_value  = 1;
int fdata_test_list_element_value_free_function_return_value = 1;

/* Test data handle free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_list_data_handle_free_function(
     intptr_t **data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_list_data_handle_free_function_return_value );
}

/* Test data handle clone function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_list_data_handle_clone_function(
     intptr_t **destination_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *source_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( destination_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( source_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_list_data_handle_clone_function_return_value );
}

/* Test element value free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_list_element_value_free_function(
     intptr_t **element_value FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( element_value )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_list_element_value_free_function_return_value );
}

/* Reads element data
 * Callback function for the list
 * Returns 1 if successful or -1 on error
 */
int fdata_test_list_read_element_data(
     intptr_t *data_handle,
     intptr_t *file_io_handle,
     libfdata_list_element_t *list_element,
     libfdata_cache_t *cache,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	uint8_t *element_value = NULL;
	static char *function  = "fdata_test_list_read_element_data";
	uint32_t element_index = 0;

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
	if( element_data_file_index != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data file index value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( element_data_offset < 1024 )
	 || ( element_data_offset >= ( 1024 + 128 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( element_data_size != 128 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( element_data_flags != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data flags value out of bounds.",
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
	element_value = (uint8_t *) memory_allocate(
	                             sizeof( uint32_t ) );

	if( element_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create element value.",
		 function );

		goto on_error;
	}
	element_index = (uint32_t) ( ( element_data_offset - 1024 ) / element_data_size );

	byte_stream_copy_from_uint32_little_endian(
	 element_value,
	 element_index );

	if( libfdata_list_element_set_element_value(
	     list_element,
	     file_io_handle,
	     cache,
	     (intptr_t *) element_value,
	     (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_list_element_value_free_function,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set list element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( element_value != NULL )
	{
		memory_free(
		 element_value );
	}
	return( -1 );
}

/* Tests the libfdata_list_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_list_t *list           = NULL;
	int result                      = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests = 3;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	/* Test error cases
	 */
	result = libfdata_list_initialize(
	          NULL,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	list = (libfdata_list_t *) 0x12345678UL;

	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
	          NULL,
	          0,
	          &error );

	list = NULL;

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
	 * 2 fail in memory_allocate of libfdata_list_initialize of elements_array
	 * 3 fail in memory_allocate of libfdata_list_initialize of mapped_ranges_array
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_list_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_list_initialize(
		          &list,
		          NULL,
		          &fdata_test_list_data_handle_free_function,
		          &fdata_test_list_data_handle_clone_function,
		          &fdata_test_list_read_element_data,
		          NULL,
		          0,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( list != NULL )
			{
				libfdata_list_free(
				 &list,
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
			 "list",
			 list );

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
		/* Test libfdata_list_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_list_initialize(
		          &list,
		          NULL,
		          &fdata_test_list_data_handle_free_function,
		          &fdata_test_list_data_handle_clone_function,
		          &fdata_test_list_read_element_data,
		          NULL,
		          0,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( list != NULL )
			{
				libfdata_list_free(
				 &list,
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
			 "list",
			 list );

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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_list_free(
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

/* Tests the libfdata_list_clone function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_clone(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_list_t *destination_list = NULL;
	libfdata_list_t *source_list      = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &source_list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "source_list",
	 source_list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_list_clone with intialized list
	 */
	result = libfdata_list_clone(
	          &destination_list,
	          source_list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "destination_list",
	 destination_list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_list_free(
	          &destination_list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_list",
	 destination_list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_list_clone with non-intialized list
	 */
	result = libfdata_list_clone(
	          &destination_list,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_list",
	 destination_list );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_clone(
	          NULL,
	          source_list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_list",
	 destination_list );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	destination_list = (libfdata_list_t *) 0x12345678UL;

	result = libfdata_list_clone(
	          &destination_list,
	          source_list,
	          &error );

	destination_list = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_list",
	 destination_list );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* Test libfdata_list_clone with malloc failing
	 */
	fdata_test_malloc_attempts_before_fail = 0;

	result = libfdata_list_clone(
	          &destination_list,
	          source_list,
	          &error );

	if( fdata_test_malloc_attempts_before_fail != -1 )
	{
		fdata_test_malloc_attempts_before_fail = -1;

		if( destination_list != NULL )
		{
			libfdata_list_free(
			 &destination_list,
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
		 "destination_list",
		 destination_list );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfdata_list_clone with memset failing
	 */
	fdata_test_memset_attempts_before_fail = 0;

	result = libfdata_list_clone(
	          &destination_list,
	          source_list,
	          &error );

	if( fdata_test_memset_attempts_before_fail != -1 )
	{
		fdata_test_memset_attempts_before_fail = -1;

		if( destination_list != NULL )
		{
			libfdata_list_free(
			 &destination_list,
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
		 "destination_list",
		 destination_list );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FDATA_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfdata_list_free(
	          &source_list,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "source_list",
	 source_list );

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
	if( source_list != NULL )
	{
		libfdata_list_free(
		 &source_list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_empty function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_empty(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
	result = libfdata_list_empty(
	          list,
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
	result = libfdata_list_empty(
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_resize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_resize(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
	result = libfdata_list_resize(
	          list,
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
	result = libfdata_list_resize(
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

	result = libfdata_list_resize(
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_number_of_elements function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_number_of_elements(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int element_index        = 0;
	int number_of_elements   = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
	result = libfdata_list_get_number_of_elements(
	          list,
	          &number_of_elements,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_elements",
	 number_of_elements,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_get_number_of_elements(
	          list,
	          &number_of_elements,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_elements",
	 number_of_elements,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_get_number_of_elements(
	          NULL,
	          &number_of_elements,
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

	result = libfdata_list_get_number_of_elements(
	          list,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_element_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_element_by_index(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	size64_t element_size    = 0;
	off64_t element_offset   = 0;
	uint32_t element_flags   = 0;
	int element_file_index   = 0;
	int element_index        = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_get_element_by_index(
	          list,
	          0,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "element_file_index",
	 element_file_index,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "element_offset",
	 (int64_t) element_offset,
	 (int64_t) 1024 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "element_size",
	 (uint64_t) element_size,
	 (uint64_t) 128 );

	FDATA_TEST_ASSERT_EQUAL_UINT32(
	 "element_flags",
	 (uint32_t) element_flags,
	 (uint32_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_get_element_by_index(
	          NULL,
	          0,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
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

	result = libfdata_list_get_element_by_index(
	          list,
	          -1,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_set_element_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_set_element_by_index(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_resize(
	          list,
	          1,
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
	result = libfdata_list_set_element_by_index(
	          list,
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

	/* Test error cases
	 */
	result = libfdata_list_set_element_by_index(
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

	result = libfdata_list_set_element_by_index(
	          list,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_prepend_element function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_prepend_element(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
	result = libfdata_list_prepend_element(
	          list,
	          0,
	          0,
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
	result = libfdata_list_prepend_element(
	          NULL,
	          0,
	          0,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_append_element function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_append_element(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int element_index        = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_append_element(
	          NULL,
	          &element_index,
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

	result = libfdata_list_append_element(
	          list,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_mapped_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_mapped_offset(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	off64_t mapped_offset    = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
	mapped_offset = -1;

	result = libfdata_list_get_mapped_offset(
	          list,
	          &mapped_offset,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "mapped_offset",
	 (int64_t) mapped_offset,
	 (int64_t) -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfdata_list_set_mapped_offset(
	          list,
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
	mapped_offset = 0;

	result = libfdata_list_get_mapped_offset(
	          list,
	          &mapped_offset,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "mapped_offset",
	 (int64_t) mapped_offset,
	 (int64_t) 512 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	mapped_offset = 0;

	result = libfdata_list_get_mapped_offset(
	          NULL,
	          &mapped_offset,
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

	result = libfdata_list_get_mapped_offset(
	          list,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_set_mapped_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_set_mapped_offset(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
	result = libfdata_list_set_mapped_offset(
	          list,
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
	result = libfdata_list_set_mapped_offset(
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

	result = libfdata_list_set_mapped_offset(
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_mapped_size_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_mapped_size_by_index(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	size64_t mapped_size     = 0;
	int element_index        = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_get_mapped_size_by_index(
	          list,
	          0,
	          &mapped_size,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "mapped_size",
	 (uint64_t) mapped_size,
	 (uint64_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfdata_list_set_mapped_size_by_index(
	          list,
	          0,
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
	result = libfdata_list_get_mapped_size_by_index(
	          list,
	          0,
	          &mapped_size,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "mapped_size",
	 (uint64_t) mapped_size,
	 (uint64_t) 512 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_get_mapped_size_by_index(
	          NULL,
	          0,
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

	result = libfdata_list_get_mapped_size_by_index(
	          list,
	          -1,
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

	result = libfdata_list_get_mapped_size_by_index(
	          list,
	          0,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_set_mapped_size_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_set_mapped_size_by_index(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int element_index        = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_set_mapped_size_by_index(
	          list,
	          0,
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
	result = libfdata_list_set_mapped_size_by_index(
	          NULL,
	          0,
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

	result = libfdata_list_set_mapped_size_by_index(
	          list,
	          -1,
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

	result = libfdata_list_set_mapped_size_by_index(
	          list,
	          0,
	          (size64_t) INT64_MAX + 1,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_element_by_index_with_mapped_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_element_by_index_with_mapped_size(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	size64_t element_size    = 0;
	size64_t mapped_size     = 0;
	off64_t element_offset   = 0;
	uint32_t element_flags   = 0;
	int element_file_index   = 0;
	int element_index        = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_get_element_by_index_with_mapped_size(
	          list,
	          0,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
	          &mapped_size,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "element_file_index",
	 element_file_index,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "element_offset",
	 (int64_t) element_offset,
	 (int64_t) 1024 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "element_size",
	 (uint64_t) element_size,
	 (uint64_t) 128 );

	FDATA_TEST_ASSERT_EQUAL_UINT32(
	 "element_flags",
	 (uint32_t) element_flags,
	 (uint32_t) 0 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "mapped_size",
	 (uint64_t) mapped_size,
	 (uint64_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfdata_list_set_mapped_size_by_index(
	          list,
	          0,
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
	result = libfdata_list_get_element_by_index_with_mapped_size(
	          list,
	          0,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
	          &mapped_size,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "element_file_index",
	 element_file_index,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "element_offset",
	 (int64_t) element_offset,
	 (int64_t) 1024 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "element_size",
	 (uint64_t) element_size,
	 (uint64_t) 128 );

	FDATA_TEST_ASSERT_EQUAL_UINT32(
	 "element_flags",
	 (uint32_t) element_flags,
	 (uint32_t) 0 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "mapped_size",
	 (uint64_t) mapped_size,
	 (uint64_t) 512 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_get_element_by_index_with_mapped_size(
	          NULL,
	          0,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
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

	result = libfdata_list_get_element_by_index_with_mapped_size(
	          list,
	          -1,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_set_element_by_index_with_mapped_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_set_element_by_index_with_mapped_size(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_resize(
	          list,
	          1,
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
	result = libfdata_list_set_element_by_index_with_mapped_size(
	          list,
	          0,
	          1,
	          1024,
	          128,
	          0,
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
	result = libfdata_list_set_element_by_index_with_mapped_size(
	          NULL,
	          0,
	          1,
	          1024,
	          128,
	          0,
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

	result = libfdata_list_set_element_by_index_with_mapped_size(
	          list,
	          -1,
	          1,
	          1024,
	          128,
	          0,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_append_element_with_mapped_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_append_element_with_mapped_size(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int element_index        = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
	result = libfdata_list_append_element_with_mapped_size(
	          list,
	          &element_index,
	          1,
	          1024,
	          128,
	          0,
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
	result = libfdata_list_append_element_with_mapped_size(
	          NULL,
	          &element_index,
	          1,
	          1024,
	          128,
	          0,
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

	result = libfdata_list_append_element_with_mapped_size(
	          list,
	          NULL,
	          1,
	          1024,
	          128,
	          0,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_element_index_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_element_index_at_offset(
     void )
{
	libcerror_error_t *error    = NULL;
	libfdata_list_t *list       = NULL;
	off64_t element_data_offset = 0;
	int element_index           = 0;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_get_element_index_at_offset(
	          list,
	          0,
	          &element_index,
	          &element_data_offset,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "element_index",
	 element_index,
	 0 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "element_data_offset",
	 (int64_t) element_data_offset,
	 (int64_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_get_element_index_at_offset(
	          NULL,
	          0,
	          &element_index,
	          &element_data_offset,
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

	result = libfdata_list_get_element_index_at_offset(
	          list,
	          -1,
	          &element_index,
	          &element_data_offset,
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

	result = libfdata_list_get_element_index_at_offset(
	          list,
	          0,
	          NULL,
	          &element_data_offset,
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

	result = libfdata_list_get_element_index_at_offset(
	          list,
	          0,
	          &element_index,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_list_element_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_list_element_at_offset(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_list_t *list                 = NULL;
	libfdata_list_element_t *list_element = NULL;
	off64_t element_data_offset           = 0;
	int element_index                     = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	list_element = NULL;

	result = libfdata_list_get_list_element_at_offset(
	          list,
	          0,
	          &element_index,
	          &element_data_offset,
	          &list_element,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "element_index",
	 element_index,
	 0 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "element_data_offset",
	 (int64_t) element_data_offset,
	 (int64_t) 0 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "list_element",
	 list_element );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	list_element = NULL;

	result = libfdata_list_get_list_element_at_offset(
	          NULL,
	          0,
	          &element_index,
	          &element_data_offset,
	          &list_element,
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

	result = libfdata_list_get_list_element_at_offset(
	          list,
	          -1,
	          &element_index,
	          &element_data_offset,
	          &list_element,
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

	result = libfdata_list_get_list_element_at_offset(
	          list,
	          0,
	          NULL,
	          &element_data_offset,
	          &list_element,
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

	result = libfdata_list_get_list_element_at_offset(
	          list,
	          0,
	          &element_index,
	          NULL,
	          &list_element,
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

	result = libfdata_list_get_list_element_at_offset(
	          list,
	          0,
	          &element_index,
	          &element_data_offset,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_element_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_element_at_offset(
     void )
{
	libcerror_error_t *error    = NULL;
	libfdata_list_t *list       = NULL;
	size64_t element_size       = 0;
	off64_t element_data_offset = 0;
	off64_t element_offset      = 0;
	uint32_t element_flags      = 0;
	int element_file_index      = 0;
	int element_index           = 0;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_get_element_at_offset(
	          list,
	          0,
	          &element_index,
	          &element_data_offset,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "element_index",
	 element_index,
	 0 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "element_data_offset",
	 (int64_t) element_data_offset,
	 (int64_t) 0 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "element_file_index",
	 element_file_index,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "element_offset",
	 (int64_t) element_offset,
	 (int64_t) 1024 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "element_size",
	 (uint64_t) element_size,
	 (uint64_t) 128 );

	FDATA_TEST_ASSERT_EQUAL_UINT32(
	 "element_flags",
	 (uint32_t) element_flags,
	 (uint32_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_get_element_at_offset(
	          NULL,
	          0,
	          &element_index,
	          &element_data_offset,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
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

	result = libfdata_list_get_element_at_offset(
	          list,
	          -1,
	          &element_index,
	          &element_data_offset,
	          &element_file_index,
	          &element_offset,
	          &element_size,
	          &element_flags,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_element_value_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_element_value_by_index(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_cache_t *cache  = NULL;
	libfdata_list_t *list    = NULL;
	intptr_t *element_value  = NULL;
	int element_index        = 0;
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

	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_get_element_value_by_index(
	          list,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &element_value,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "element_value",
	 element_value );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	memory_free(
	 element_value );

	element_value = NULL;

	/* Test error cases
	 */
	result = libfdata_list_get_element_value_by_index(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
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

/* Tests the libfdata_list_get_element_value_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_element_value_at_offset(
     void )
{
	libcerror_error_t *error    = NULL;
	libfdata_cache_t *cache     = NULL;
	libfdata_list_t *list       = NULL;
	intptr_t *element_value     = NULL;
	off64_t element_data_offset = 0;
	int element_index           = 0;
	int result                  = 0;

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

	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	element_value = NULL;

	result = libfdata_list_get_element_value_at_offset(
	          list,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &element_index,
	          &element_data_offset,
	          &element_value,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "element_value",
	 element_value );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	memory_free(
	 element_value );

	element_value = NULL;

	result = libfdata_list_get_element_value_at_offset(
	          list,
	          NULL,
	          (libfdata_cache_t *) cache,
	          4096,
	          &element_index,
	          &element_data_offset,
	          &element_value,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "element_value",
	 element_value );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	element_value = NULL;

	result = libfdata_list_get_element_value_at_offset(
	          NULL,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &element_index,
	          &element_data_offset,
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

	result = libfdata_list_get_element_value_at_offset(
	          list,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          NULL,
	          &element_data_offset,
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

	result = libfdata_list_get_element_value_at_offset(
	          list,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
	          &element_index,
	          &element_data_offset,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
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

/* Tests the libfdata_list_set_element_value_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_set_element_value_by_index(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int result               = 0;
	int value1               = 1;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
/* TODO implement */

	/* Test error cases
	 */
	result = libfdata_list_set_element_value_by_index(
	          NULL,
	          NULL,
	          NULL,
	          0,
	          (intptr_t *) &value1,
	          &fdata_test_list_element_value_free_function,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_set_element_value_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_set_element_value_at_offset(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	int result               = 0;
	int value1               = 1;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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
/* TODO implement */

	/* Test error cases
	 */
	result = libfdata_list_set_element_value_at_offset(
	          NULL,
	          NULL,
	          NULL,
	          0,
	          (intptr_t *) &value1,
	          &fdata_test_list_element_value_free_function,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_list_get_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_list_get_size(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_list_t *list    = NULL;
	size64_t size            = 0;
	int element_index        = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_list_initialize(
	          &list,
	          NULL,
	          &fdata_test_list_data_handle_free_function,
	          &fdata_test_list_data_handle_clone_function,
	          &fdata_test_list_read_element_data,
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

	result = libfdata_list_append_element(
	          list,
	          &element_index,
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
	result = libfdata_list_get_size(
	          list,
	          &size,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "size",
	 (uint64_t) size,
	 (uint64_t) 128 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_list_get_size(
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

	result = libfdata_list_get_size(
	          list,
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
	if( list != NULL )
	{
		libfdata_list_free(
		 &list,
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
	 "libfdata_list_initialize",
	 fdata_test_list_initialize );

	FDATA_TEST_RUN(
	 "libfdata_list_free",
	 fdata_test_list_free );

	FDATA_TEST_RUN(
	 "libfdata_list_clone",
	 fdata_test_list_clone );

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

	/* TODO: add tests for libfdata_list_set_calculate_mapped_ranges_flag */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	FDATA_TEST_RUN(
	 "libfdata_list_empty",
	 fdata_test_list_empty );

	FDATA_TEST_RUN(
	 "libfdata_list_resize",
	 fdata_test_list_resize );

	/* TODO: add tests for libfdata_list_reverse */

	FDATA_TEST_RUN(
	 "libfdata_list_get_number_of_elements",
	 fdata_test_list_get_number_of_elements );

	/* TODO: add tests for libfdata_list_get_list_element_by_index */

	FDATA_TEST_RUN(
	 "libfdata_list_get_element_by_index",
	 fdata_test_list_get_element_by_index );

	FDATA_TEST_RUN(
	 "libfdata_list_set_element_by_index",
	 fdata_test_list_set_element_by_index );

	FDATA_TEST_RUN(
	 "libfdata_list_prepend_element",
	 fdata_test_list_prepend_element );

	FDATA_TEST_RUN(
	 "libfdata_list_append_element",
	 fdata_test_list_append_element );

	/* TODO: add tests for libfdata_list_append_list */

	/* TODO: add tests for libfdata_list_is_element_set */

	FDATA_TEST_RUN(
	 "libfdata_list_get_mapped_offset",
	 fdata_test_list_get_mapped_offset );

	FDATA_TEST_RUN(
	 "libfdata_list_set_mapped_offset",
	 fdata_test_list_set_mapped_offset );

	FDATA_TEST_RUN(
	 "libfdata_list_get_mapped_size_by_index",
	 fdata_test_list_get_mapped_size_by_index );

	FDATA_TEST_RUN(
	 "libfdata_list_set_mapped_size_by_index",
	 fdata_test_list_set_mapped_size_by_index );

	FDATA_TEST_RUN(
	 "libfdata_list_get_element_by_index_with_mapped_size",
	 fdata_test_list_get_element_by_index_with_mapped_size );

	FDATA_TEST_RUN(
	 "libfdata_list_set_element_by_index_with_mapped_size",
	 fdata_test_list_set_element_by_index_with_mapped_size );

	FDATA_TEST_RUN(
	 "libfdata_list_append_element_with_mapped_size",
	 fdata_test_list_append_element_with_mapped_size );

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

	/* TODO: add tests for libfdata_list_calculate_mapped_ranges */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	FDATA_TEST_RUN(
	 "libfdata_list_get_element_index_at_offset",
	 fdata_test_list_get_element_index_at_offset );

	FDATA_TEST_RUN(
	 "libfdata_list_get_list_element_at_offset",
	 fdata_test_list_get_list_element_at_offset );

	FDATA_TEST_RUN(
	 "libfdata_list_get_element_at_offset",
	 fdata_test_list_get_element_at_offset );

	/* TODO: add tests for libfdata_list_cache_element_value */

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

	/* TODO: add tests for libfdata_list_get_element_value */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	FDATA_TEST_RUN(
	 "libfdata_list_get_element_value_by_index",
	 fdata_test_list_get_element_value_by_index );

	FDATA_TEST_RUN(
	 "libfdata_list_get_element_value_at_offset",
	 fdata_test_list_get_element_value_at_offset );

#if defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT )

	/* TODO: add tests for libfdata_list_set_element_value */

#endif /* defined( __GNUC__ ) && !defined( LIBFDATA_DLL_IMPORT ) */

	FDATA_TEST_RUN(
	 "libfdata_list_set_element_value_by_index",
	 fdata_test_list_set_element_value_by_index );

	FDATA_TEST_RUN(
	 "libfdata_list_set_element_value_at_offset",
	 fdata_test_list_set_element_value_at_offset );

	FDATA_TEST_RUN(
	 "libfdata_list_get_size",
	 fdata_test_list_get_size );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

