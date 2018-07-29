/*
 * Library area type test program
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

#include "../libfdata/libfdata_area.h"

int fdata_test_area_data_handle_free_function_return_value   = 1;
int fdata_test_area_data_handle_clone_function_return_value  = 1;
int fdata_test_area_element_value_free_function_return_value = 1;

/* Test data handle free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_area_data_handle_free_function(
     intptr_t **data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_area_data_handle_free_function_return_value );
}

/* Test data handle clone function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_area_data_handle_clone_function(
     intptr_t **destination_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *source_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( destination_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( source_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_area_data_handle_clone_function_return_value );
}

/* Test element value free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_area_element_value_free_function(
     intptr_t **element_value FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( element_value )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_area_element_value_free_function_return_value );
}

/* Reads element data
 * Callback function for the area
 * Returns 1 if successful or -1 on error
 */
int fdata_test_area_read_element_data(
     intptr_t *data_handle,
     intptr_t *file_io_handle,
     libfdata_area_t *area,
     libfdata_cache_t *cache,
     off64_t element_value_offset,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	uint8_t *element_value = NULL;
	static char *function  = "fdata_test_area_read_element_data";
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
	 || ( element_data_offset >= ( 1024 + 2048 ) ) )
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

	if( libfdata_area_set_element_value_at_offset(
	     area,
	     file_io_handle,
	     cache,
	     element_value_offset,
	     (intptr_t *) element_value,
	     (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_area_element_value_free_function,
	     LIBFDATA_AREA_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set element value at offset: 0x%08" PRIx64 ".",
		 function,
		 element_value_offset );

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

/* Tests the libfdata_area_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_area_t *area           = NULL;
	int result                      = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests = 3;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_area_initialize(
	          NULL,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
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

	area = (libfdata_area_t *) 0x12345678UL;

	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	area = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfdata_area_initialize(
	          &area,
	          0,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
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
	 * 2 fail in memory_allocate of libfdata_area_initialize of segments_array
	 * 3 fail in memory_allocate of libfdata_area_initialize of mapped_ranges_array
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_area_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_area_initialize(
		          &area,
		          128,
		          NULL,
		          &fdata_test_area_data_handle_free_function,
		          &fdata_test_area_data_handle_clone_function,
		          &fdata_test_area_read_element_data,
		          NULL,
		          0,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( area != NULL )
			{
				libfdata_area_free(
				 &area,
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
			 "area",
			 area );

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
		/* Test libfdata_area_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_area_initialize(
		          &area,
		          128,
		          NULL,
		          &fdata_test_area_data_handle_free_function,
		          &fdata_test_area_data_handle_clone_function,
		          &fdata_test_area_read_element_data,
		          NULL,
		          0,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( area != NULL )
			{
				libfdata_area_free(
				 &area,
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
			 "area",
			 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_area_free(
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

/* Tests the libfdata_area_clone function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_clone(
     void )
{
	libcerror_error_t *error          = NULL;
	libfdata_area_t *destination_area = NULL;
	libfdata_area_t *source_area      = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &source_area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "source_area",
	 source_area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_area_clone with intialized area
	 */
	result = libfdata_area_clone(
	          &destination_area,
	          source_area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "destination_area",
	 destination_area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_area_free(
	          &destination_area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_area",
	 destination_area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_area_clone with non-intialized area
	 */
	result = libfdata_area_clone(
	          &destination_area,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_area",
	 destination_area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_area_clone(
	          NULL,
	          source_area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_area",
	 destination_area );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	destination_area = (libfdata_area_t *) 0x12345678UL;

	result = libfdata_area_clone(
	          &destination_area,
	          source_area,
	          &error );

	destination_area = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_area",
	 destination_area );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* Test libfdata_area_clone with malloc failing
	 */
	fdata_test_malloc_attempts_before_fail = 0;

	result = libfdata_area_clone(
	          &destination_area,
	          source_area,
	          &error );

	if( fdata_test_malloc_attempts_before_fail != -1 )
	{
		fdata_test_malloc_attempts_before_fail = -1;

		if( destination_area != NULL )
		{
			libfdata_area_free(
			 &destination_area,
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
		 "destination_area",
		 destination_area );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfdata_area_clone with memset failing
	 */
	fdata_test_memset_attempts_before_fail = 0;

	result = libfdata_area_clone(
	          &destination_area,
	          source_area,
	          &error );

	if( fdata_test_memset_attempts_before_fail != -1 )
	{
		fdata_test_memset_attempts_before_fail = -1;

		if( destination_area != NULL )
		{
			libfdata_area_free(
			 &destination_area,
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
		 "destination_area",
		 destination_area );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FDATA_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfdata_area_free(
	          &source_area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "source_area",
	 source_area );

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
	if( source_area != NULL )
	{
		libfdata_area_free(
		 &source_area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_empty function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_empty(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_area_empty(
	          area,
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
	result = libfdata_area_empty(
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_resize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_resize(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_area_resize(
	          area,
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
	result = libfdata_area_resize(
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

	result = libfdata_area_resize(
	          area,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_get_number_of_segments function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_get_number_of_segments(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	int number_of_segments   = 0;
	int result               = 0;
	int segment_index        = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_area_get_number_of_segments(
	          area,
	          &number_of_segments,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_segments",
	 number_of_segments,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfdata_area_append_segment(
	          area,
	          &segment_index,
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
	result = libfdata_area_get_number_of_segments(
	          area,
	          &number_of_segments,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "number_of_segments",
	 number_of_segments,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_area_get_number_of_segments(
	          NULL,
	          &number_of_segments,
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

	result = libfdata_area_get_number_of_segments(
	          area,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_get_segment_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_get_segment_by_index(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	size64_t segment_size    = 0;
	off64_t segment_offset   = 0;
	uint32_t segment_flags   = 0;
	int result               = 0;
	int segment_file_index   = 0;
	int segment_index        = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_area_append_segment(
	          area,
	          &segment_index,
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
	result = libfdata_area_get_segment_by_index(
	          area,
	          0,
	          &segment_file_index,
	          &segment_offset,
	          &segment_size,
	          &segment_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "segment_file_index",
	 segment_file_index,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "segment_offset",
	 (int64_t) segment_offset,
	 (int64_t) 1024 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "segment_size",
	 (uint64_t) segment_size,
	 (uint64_t) 2048 );

	FDATA_TEST_ASSERT_EQUAL_UINT32(
	 "segment_flags",
	 (uint32_t) segment_flags,
	 (uint32_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_area_get_segment_by_index(
	          NULL,
	          0,
	          &segment_file_index,
	          &segment_offset,
	          &segment_size,
	          &segment_flags,
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

	result = libfdata_area_get_segment_by_index(
	          area,
	          -1,
	          &segment_file_index,
	          &segment_offset,
	          &segment_size,
	          &segment_flags,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_set_segment_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_set_segment_by_index(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_area_resize(
	          area,
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
	result = libfdata_area_set_segment_by_index(
	          area,
	          0,
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
	result = libfdata_area_set_segment_by_index(
	          NULL,
	          0,
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

	result = libfdata_area_set_segment_by_index(
	          area,
	          -1,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_prepend_segment function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_prepend_segment(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_area_prepend_segment(
	          area,
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
	result = libfdata_area_prepend_segment(
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_append_segment function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_append_segment(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	int result               = 0;
	int segment_index        = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_area_append_segment(
	          area,
	          &segment_index,
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
	result = libfdata_area_append_segment(
	          NULL,
	          &segment_index,
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

	result = libfdata_area_append_segment(
	          area,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_get_element_data_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_get_element_data_size(
     void )
{
	libcerror_error_t *error   = NULL;
	libfdata_area_t *area      = NULL;
	size64_t element_data_size = 0;
	int result                 = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_area_get_element_data_size(
	          area,
	          &element_data_size,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "element_data_size",
	 (uint64_t) element_data_size,
	 (uint64_t) 128 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_area_get_element_data_size(
	          NULL,
	          &element_data_size,
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

	result = libfdata_area_get_element_data_size(
	          area,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_get_element_value_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_get_element_value_at_offset(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	libfdata_cache_t *cache  = NULL;
	intptr_t *element_value  = NULL;
	int result               = 0;
	int segment_index        = 0;

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

	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_area_append_segment(
	          area,
	          &segment_index,
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
	element_value = NULL;

	result = libfdata_area_get_element_value_at_offset(
	          area,
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
	result = libfdata_area_get_element_value_at_offset(
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

	result = libfdata_area_get_element_value_at_offset(
	          area,
	          NULL,
	          (libfdata_cache_t *) cache,
	          0,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
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

/* Tests the libfdata_area_set_element_value_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_set_element_value_at_offset(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	int result               = 0;
	int value1               = 1;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
/* TODO implement */

	/* Test error cases
	 */
	result = libfdata_area_set_element_value_at_offset(
	          NULL,
	          NULL,
	          NULL,
	          0,
	          (intptr_t *) &value1,
	          &fdata_test_area_element_value_free_function,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_area_get_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_area_get_size(
     void )
{
	libcerror_error_t *error = NULL;
	libfdata_area_t *area    = NULL;
	size64_t size            = 0;
	int result               = 0;
	int segment_index        = 0;

	/* Initialize test
	 */
	result = libfdata_area_initialize(
	          &area,
	          128,
	          NULL,
	          &fdata_test_area_data_handle_free_function,
	          &fdata_test_area_data_handle_clone_function,
	          &fdata_test_area_read_element_data,
	          NULL,
	          0,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "area",
	 area );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_area_append_segment(
	          area,
	          &segment_index,
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
	result = libfdata_area_get_size(
	          area,
	          &size,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "size",
	 (uint64_t) size,
	 (uint64_t) 2048 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_area_get_size(
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

	result = libfdata_area_get_size(
	          area,
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
	result = libfdata_area_free(
	          &area,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "area",
	 area );

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
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
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
	 "libfdata_area_initialize",
	 fdata_test_area_initialize );

	FDATA_TEST_RUN(
	 "libfdata_area_free",
	 fdata_test_area_free );

	FDATA_TEST_RUN(
	 "libfdata_area_clone",
	 fdata_test_area_clone );

	FDATA_TEST_RUN(
	 "libfdata_area_empty",
	 fdata_test_area_empty );

	FDATA_TEST_RUN(
	 "libfdata_area_resize",
	 fdata_test_area_resize );

	FDATA_TEST_RUN(
	 "libfdata_area_get_number_of_segments",
	 fdata_test_area_get_number_of_segments );

	FDATA_TEST_RUN(
	 "libfdata_area_get_segment_by_index",
	 fdata_test_area_get_segment_by_index );

	FDATA_TEST_RUN(
	 "libfdata_area_set_segment_by_index",
	 fdata_test_area_set_segment_by_index );

	FDATA_TEST_RUN(
	 "libfdata_area_prepend_segment",
	 fdata_test_area_prepend_segment );

	FDATA_TEST_RUN(
	 "libfdata_area_append_segment",
	 fdata_test_area_append_segment );

	FDATA_TEST_RUN(
	 "libfdata_area_get_element_data_size",
	 fdata_test_area_get_element_data_size );

	FDATA_TEST_RUN(
	 "libfdata_area_get_element_value_at_offset",
	 fdata_test_area_get_element_value_at_offset );

	FDATA_TEST_RUN(
	 "libfdata_area_set_element_value_at_offset",
	 fdata_test_area_set_element_value_at_offset );

	FDATA_TEST_RUN(
	 "libfdata_area_get_size",
	 fdata_test_area_get_size );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

