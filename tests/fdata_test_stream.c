/*
 * Library stream type test program
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

#include "../libfdata/libfdata_stream.h"

int fdata_test_stream_data_handle_free_function_return_value   = 1;
int fdata_test_stream_data_handle_clone_function_return_value  = 1;
int fdata_test_stream_element_value_free_function_return_value = 1;

/* Test data handle free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_stream_data_handle_free_function(
     intptr_t **data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_stream_data_handle_free_function_return_value );
}

/* Test data handle clone function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_stream_data_handle_clone_function(
     intptr_t **destination_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *source_data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( destination_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( source_data_handle )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_stream_data_handle_clone_function_return_value );
}

/* Test element value free function
 * Returns 1 if successful or -1 on error
 */
int fdata_test_stream_element_value_free_function(
     intptr_t **element_value FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error FDATA_TEST_ATTRIBUTE_UNUSED )
{
	FDATA_TEST_UNREFERENCED_PARAMETER( element_value )
	FDATA_TEST_UNREFERENCED_PARAMETER( error )

	return( fdata_test_stream_element_value_free_function_return_value );
}

/* Tests the libfdata_stream_initialize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_stream_t *stream       = NULL;
	int result                      = 0;

#if defined( HAVE_FDATA_TEST_MEMORY )
	int number_of_malloc_fail_tests = 3;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_stream_initialize(
	          NULL,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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

	stream = (libfdata_stream_t *) 0x12345678UL;

	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
	          &error );

	stream = NULL;

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
	 * 2 fail in memory_allocate of libfdata_stream_initialize of segments_array
	 * 3 fail in memory_allocate of libfdata_stream_initialize of mapped_ranges_array
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfdata_stream_initialize with malloc failing
		 */
		fdata_test_malloc_attempts_before_fail = test_number;

		result = libfdata_stream_initialize(
		          &stream,
		          NULL,
		          &fdata_test_stream_data_handle_free_function,
		          &fdata_test_stream_data_handle_clone_function,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          0,
		          &error );

		if( fdata_test_malloc_attempts_before_fail != -1 )
		{
			fdata_test_malloc_attempts_before_fail = -1;

			if( stream != NULL )
			{
				libfdata_stream_free(
				 &stream,
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
			 "stream",
			 stream );

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
		/* Test libfdata_stream_initialize with memset failing
		 */
		fdata_test_memset_attempts_before_fail = test_number;

		result = libfdata_stream_initialize(
		          &stream,
		          NULL,
		          &fdata_test_stream_data_handle_free_function,
		          &fdata_test_stream_data_handle_clone_function,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          0,
		          &error );

		if( fdata_test_memset_attempts_before_fail != -1 )
		{
			fdata_test_memset_attempts_before_fail = -1;

			if( stream != NULL )
			{
				libfdata_stream_free(
				 &stream,
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
			 "stream",
			 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_free function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfdata_stream_free(
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

/* Tests the libfdata_stream_clone function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_clone(
     void )
{
	libcerror_error_t *error              = NULL;
	libfdata_stream_t *destination_stream = NULL;
	libfdata_stream_t *source_stream      = NULL;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &source_stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "source_stream",
	 source_stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_stream_clone with initialized stream
	 */
	result = libfdata_stream_clone(
	          &destination_stream,
	          source_stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "destination_stream",
	 destination_stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_free(
	          &destination_stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_stream",
	 destination_stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libfdata_stream_clone with non-initialized stream
	 */
	result = libfdata_stream_clone(
	          &destination_stream,
	          NULL,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_stream",
	 destination_stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_stream_clone(
	          NULL,
	          source_stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_stream",
	 destination_stream );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	destination_stream = (libfdata_stream_t *) 0x12345678UL;

	result = libfdata_stream_clone(
	          &destination_stream,
	          source_stream,
	          &error );

	destination_stream = NULL;

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "destination_stream",
	 destination_stream );

	FDATA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FDATA_TEST_MEMORY )

	/* Test libfdata_stream_clone with malloc failing
	 */
	fdata_test_malloc_attempts_before_fail = 0;

	result = libfdata_stream_clone(
	          &destination_stream,
	          source_stream,
	          &error );

	if( fdata_test_malloc_attempts_before_fail != -1 )
	{
		fdata_test_malloc_attempts_before_fail = -1;

		if( destination_stream != NULL )
		{
			libfdata_stream_free(
			 &destination_stream,
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
		 "destination_stream",
		 destination_stream );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfdata_stream_clone with memset failing
	 */
	fdata_test_memset_attempts_before_fail = 0;

	result = libfdata_stream_clone(
	          &destination_stream,
	          source_stream,
	          &error );

	if( fdata_test_memset_attempts_before_fail != -1 )
	{
		fdata_test_memset_attempts_before_fail = -1;

		if( destination_stream != NULL )
		{
			libfdata_stream_free(
			 &destination_stream,
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
		 "destination_stream",
		 destination_stream );

		FDATA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FDATA_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfdata_stream_free(
	          &source_stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "source_stream",
	 source_stream );

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
	if( source_stream != NULL )
	{
		libfdata_stream_free(
		 &source_stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_empty function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_empty(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_stream_empty(
	          stream,
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
	result = libfdata_stream_empty(
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_resize function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_resize(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_stream_resize(
	          stream,
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
	result = libfdata_stream_resize(
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

	result = libfdata_stream_resize(
	          stream,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_get_number_of_segments function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_get_number_of_segments(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int number_of_segments    = 0;
	int result                = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_stream_get_number_of_segments(
	          stream,
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
	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_get_number_of_segments(
	          stream,
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
	result = libfdata_stream_get_number_of_segments(
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

	result = libfdata_stream_get_number_of_segments(
	          stream,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_get_segment_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_get_segment_by_index(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	size64_t segment_size     = 0;
	off64_t segment_offset    = 0;
	uint32_t segment_flags    = 0;
	int result                = 0;
	int segment_file_index    = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_get_segment_by_index(
	          stream,
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
	result = libfdata_stream_get_segment_by_index(
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

	result = libfdata_stream_get_segment_by_index(
	          stream,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_set_segment_by_index function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_set_segment_by_index(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_resize(
	          stream,
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
	result = libfdata_stream_set_segment_by_index(
	          stream,
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
	result = libfdata_stream_set_segment_by_index(
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

	result = libfdata_stream_set_segment_by_index(
	          stream,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_prepend_segment function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_prepend_segment(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_stream_prepend_segment(
	          stream,
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
	result = libfdata_stream_prepend_segment(
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_append_segment function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_append_segment(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_append_segment(
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

	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_set_mapped_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_set_mapped_size(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_set_mapped_size(
	          stream,
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
	result = libfdata_stream_set_mapped_size(
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

	result = libfdata_stream_set_mapped_size(
	          stream,
	          4096,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_get_segment_mapped_range function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_get_segment_mapped_range(
     void )
{
	libcerror_error_t *error    = NULL;
	libfdata_stream_t *stream   = NULL;
	size64_t mapped_range_size  = 0;
	off64_t mapped_range_offset = 0;
	int result                  = 0;
	int segment_index           = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_get_segment_mapped_range(
	          stream,
	          0,
	          &mapped_range_offset,
	          &mapped_range_size,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "mapped_range_offset",
	 (int64_t) mapped_range_offset,
	 (int64_t) 0 );

	FDATA_TEST_ASSERT_EQUAL_UINT64(
	 "mapped_range_size",
	 (uint64_t) mapped_range_size,
	 (uint64_t) 2048 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_stream_get_segment_mapped_range(
	          NULL,
	          0,
	          &mapped_range_offset,
	          &mapped_range_size,
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

	result = libfdata_stream_get_segment_mapped_range(
	          stream,
	          -1,
	          &mapped_range_offset,
	          &mapped_range_size,
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

	result = libfdata_stream_get_segment_mapped_range(
	          stream,
	          0,
	          NULL,
	          &mapped_range_size,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_get_segment_index_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_get_segment_index_at_offset(
     void )
{
	libcerror_error_t *error    = NULL;
	libfdata_stream_t *stream   = NULL;
	off64_t segment_data_offset = 0;
	int result                  = 0;
	int segment_index           = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_get_segment_index_at_offset(
	          stream,
	          0,
	          &segment_index,
	          &segment_data_offset,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "segment_index",
	 segment_index,
	 0 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "segment_data_offset",
	 (int64_t) segment_data_offset,
	 (int64_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#ifdef TODO
/* TODO fix libfdata_stream_get_segment_index_at_offset
 * libcdata_array_get_entry_by_index: invalid entry index value out of bounds.
 */
	result = libfdata_stream_get_segment_index_at_offset(
	          stream,
	          4096,
	          &segment_index,
	          &segment_data_offset,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_stream_get_segment_index_at_offset(
	          NULL,
	          0,
	          &segment_index,
	          &segment_data_offset,
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

	result = libfdata_stream_get_segment_index_at_offset(
	          stream,
	          -1,
	          &segment_index,
	          &segment_data_offset,
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

	result = libfdata_stream_get_segment_index_at_offset(
	          stream,
	          0,
	          NULL,
	          &segment_data_offset,
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

	result = libfdata_stream_get_segment_index_at_offset(
	          stream,
	          0,
	          &segment_index,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_get_segment_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_get_segment_at_offset(
     void )
{
	libcerror_error_t *error    = NULL;
	libfdata_stream_t *stream   = NULL;
	size64_t segment_size       = 0;
	off64_t segment_data_offset = 0;
	off64_t segment_offset      = 0;
	uint32_t segment_flags      = 0;
	int result                  = 0;
	int segment_file_index      = 0;
	int segment_index           = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_get_segment_at_offset(
	          stream,
	          0,
	          &segment_index,
	          &segment_data_offset,
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
	 "segment_index",
	 segment_index,
	 0 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "segment_data_offset",
	 (int64_t) segment_data_offset,
	 (int64_t) 0 );

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

#ifdef TODO
/* TODO fix libfdata_stream_get_segment_at_offset
 * libcdata_array_get_entry_by_index: invalid entry index value out of bounds.
 */
	result = libfdata_stream_get_segment_at_offset(
	          stream,
	          4096,
	          &segment_index,
	          &segment_data_offset,
	          &segment_file_index,
	          &segment_offset,
	          &segment_size,
	          &segment_flags,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );
#endif

	/* Test error cases
	 */
	result = libfdata_stream_get_segment_at_offset(
	          NULL,
	          0,
	          &segment_index,
	          &segment_data_offset,
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

	result = libfdata_stream_get_segment_at_offset(
	          stream,
	          -1,
	          &segment_index,
	          &segment_data_offset,
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

	result = libfdata_stream_get_segment_at_offset(
	          stream,
	          0,
	          NULL,
	          &segment_data_offset,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_read_buffer(
     void )
{
	uint8_t data[ 32 ];

	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
/* TODO implement */

	/* Test error cases
	 */
	result = libfdata_stream_read_buffer(
	          NULL,
	          NULL,
	          data,
	          32,
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

	result = libfdata_stream_read_buffer(
	          stream,
	          NULL,
	          NULL,
	          32,
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

	result = libfdata_stream_read_buffer(
	          stream,
	          NULL,
	          data,
	          (size_t) SSIZE_MAX + 1,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_read_buffer_at_offset(
     void )
{
	uint8_t data[ 32 ];

	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
/* TODO implement */

	/* Test error cases
	 */
	result = libfdata_stream_read_buffer_at_offset(
	          NULL,
	          NULL,
	          data,
	          32,
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

	result = libfdata_stream_read_buffer_at_offset(
	          stream,
	          NULL,
	          NULL,
	          32,
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

	result = libfdata_stream_read_buffer_at_offset(
	          stream,
	          NULL,
	          data,
	          (size_t) SSIZE_MAX + 1,
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

	result = libfdata_stream_read_buffer_at_offset(
	          stream,
	          NULL,
	          data,
	          32,
	          -1,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_seek_offset(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	int result                = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
/* TODO implement */

	/* Test error cases
	 */
	result = libfdata_stream_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
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

	result = libfdata_stream_seek_offset(
	          stream,
	          -1,
	          SEEK_SET,
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

	result = libfdata_stream_seek_offset(
	          stream,
	          0,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_get_offset function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_get_offset(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	off64_t offset            = 0;
	int result                = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_get_offset(
	          stream,
	          &offset,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 0 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfdata_stream_get_offset(
	          NULL,
	          &offset,
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

	result = libfdata_stream_get_offset(
	          stream,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfdata_stream_get_size function
 * Returns 1 if successful or 0 if not
 */
int fdata_test_stream_get_size(
     void )
{
	libcerror_error_t *error  = NULL;
	libfdata_stream_t *stream = NULL;
	size64_t size             = 0;
	int result                = 0;
	int segment_index         = 0;

	/* Initialize test
	 */
	result = libfdata_stream_initialize(
	          &stream,
	          NULL,
	          &fdata_test_stream_data_handle_free_function,
	          &fdata_test_stream_data_handle_clone_function,
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
	 "stream",
	 stream );

	FDATA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          stream,
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
	result = libfdata_stream_get_size(
	          stream,
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
	result = libfdata_stream_get_size(
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

	result = libfdata_stream_get_size(
	          stream,
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
	result = libfdata_stream_free(
	          &stream,
	          &error );

	FDATA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FDATA_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libfdata_stream_free(
		 &stream,
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
	 "libfdata_stream_initialize",
	 fdata_test_stream_initialize );

	FDATA_TEST_RUN(
	 "libfdata_stream_free",
	 fdata_test_stream_free );

	FDATA_TEST_RUN(
	 "libfdata_stream_clone",
	 fdata_test_stream_clone );

	FDATA_TEST_RUN(
	 "libfdata_stream_empty",
	 fdata_test_stream_empty );

	FDATA_TEST_RUN(
	 "libfdata_stream_resize",
	 fdata_test_stream_resize );

	/* TODO: add tests for libfdata_stream_reverse */

	FDATA_TEST_RUN(
	 "libfdata_stream_get_number_of_segments",
	 fdata_test_stream_get_number_of_segments );

	FDATA_TEST_RUN(
	 "libfdata_stream_get_segment_by_index",
	 fdata_test_stream_get_segment_by_index );

	FDATA_TEST_RUN(
	 "libfdata_stream_set_segment_by_index",
	 fdata_test_stream_set_segment_by_index );

	FDATA_TEST_RUN(
	 "libfdata_stream_prepend_segment",
	 fdata_test_stream_prepend_segment );

	FDATA_TEST_RUN(
	 "libfdata_stream_append_segment",
	 fdata_test_stream_append_segment );

	FDATA_TEST_RUN(
	 "libfdata_stream_set_mapped_size",
	 fdata_test_stream_set_mapped_size );

	FDATA_TEST_RUN(
	 "libfdata_stream_get_segment_mapped_range",
	 fdata_test_stream_get_segment_mapped_range );

	FDATA_TEST_RUN(
	 "libfdata_stream_get_segment_index_at_offset",
	 fdata_test_stream_get_segment_index_at_offset );

	FDATA_TEST_RUN(
	 "libfdata_stream_get_segment_at_offset",
	 fdata_test_stream_get_segment_at_offset );

	FDATA_TEST_RUN(
	 "libfdata_stream_read_buffer",
	 fdata_test_stream_read_buffer );

	FDATA_TEST_RUN(
	 "libfdata_stream_read_buffer_at_offset",
	 fdata_test_stream_read_buffer_at_offset );

	/* TODO: add tests for libfdata_stream_write_buffer */

	FDATA_TEST_RUN(
	 "libfdata_stream_seek_offset",
	 fdata_test_stream_seek_offset );

	FDATA_TEST_RUN(
	 "libfdata_stream_get_offset",
	 fdata_test_stream_get_offset );

	FDATA_TEST_RUN(
	 "libfdata_stream_get_size",
	 fdata_test_stream_get_size );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

