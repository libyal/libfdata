/*
 * Library area type testing program
 *
 * Copyright (C) 2010-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "fdata_test_libcerror.h"
#include "fdata_test_libcstring.h"
#include "fdata_test_libfdata.h"
#include "fdata_test_unused.h"

#define ELEMENT_DATA_SIZE		512
#define MAXIMUM_NUMBER_OF_ELEMENTS	1024

/* Tests initializing the area
 * Make sure the value area is referencing, is set to NULL
 * Returns 1 if successful, 0 if not or -1 on error
 */
int fdata_test_area_initialize(
     libfdata_area_t **area,
     int expected_result )
{
	libcerror_error_t *error = NULL;
	static char *function    = "fdata_test_area_initialize";
	int result               = 0;

	fprintf(
	 stdout,
	 "Testing initialize\t" );

	result = libfdata_area_initialize(
	          area,
	          ELEMENT_DATA_SIZE,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
	          &error );

	if( result != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create area.",
		 function );
	}
	if( result != expected_result )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( result == -1 )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stdout );

		libcerror_error_free(
		 &error );
	}
	if( result == 1 )
	{
		if( libfdata_area_free(
		     area,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free area.",
			 function );

			libcerror_error_backtrace_fprint(
			 error,
			 stdout );

			libcerror_error_free(
			 &error );

			return( -1 );
		}
	}
	if( result != expected_result )
	{
		return( 0 );
	}
	return( 1 );
}

/* Frees the element data
 * Returns 1 if successful or -1 on error
 */
int fdata_test_area_element_data_free(
     uint8_t **element_data,
     libcerror_error_t **error )
{
	static char *function = "fdata_test_area_element_data_free";

	if( element_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element data.",
		 function );

		return( -1 );
	}
	if( *element_data != NULL )
	{
		memory_free(
		 *element_data );

		*element_data = NULL;
	}
	return( 1 );
}

/* Reads element data
 * Callback function for the area
 * Returns 1 if successful or -1 on error
 */
int fdata_test_area_read_element_data(
     intptr_t *data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *file_io_handle,
     libfdata_area_t *area,
     libfdata_cache_t *cache,
     off64_t element_value_offset,
     int element_data_file_index FDATA_TEST_ATTRIBUTE_UNUSED,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags FDATA_TEST_ATTRIBUTE_UNUSED,
     uint8_t read_flags FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	uint8_t *element_data       = NULL;
	static char *function       = "fdata_test_area_read_element_data";
	uint32_t test_element_index = 0;

	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle );
	FDATA_TEST_UNREFERENCED_PARAMETER( element_data_file_index );
	FDATA_TEST_UNREFERENCED_PARAMETER( element_data_flags );
	FDATA_TEST_UNREFERENCED_PARAMETER( read_flags );

	element_data_size = sizeof( uint8_t ) * ELEMENT_DATA_SIZE;

	element_data = (uint8_t *) memory_allocate(
	                            (size_t) element_data_size );

	if( element_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create element data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     element_data,
	     0,
	     (size_t) element_data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear element data.",
		 function );

		goto on_error;
	}
	test_element_index = (uint32_t) ( element_data_offset / ELEMENT_DATA_SIZE );

	byte_stream_copy_from_uint32_little_endian(
	 element_data,
	 test_element_index );

	if( libfdata_area_set_element_value_at_offset(
	     area,
	     file_io_handle,
	     cache,
	     element_value_offset,
	     (intptr_t *) element_data,
	     (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_area_element_data_free,
	     LIBFDATA_AREA_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set element data as element value at offset: 0x%08" PRIx64 ".",
		 function,
		 element_value_offset );

		goto on_error;
	}
	return( 1 );

on_error:
	if( element_data != NULL )
	{
		memory_free(
		 element_data );
	}
	return( -1 );
}

/* Tests reading the area
 * Returns 1 if successful, 0 if not or -1 on error
 */
int fdata_test_area_read(
    void )
{
	libcerror_error_t *error    = NULL;
	libfdata_area_t *area       = NULL;
	libfdata_cache_t *cache     = NULL;
	uint8_t *element_data       = NULL;
	static char *function       = "fdata_test_area_read";
	off64_t element_offset      = 0;
	uint32_t test_element_index = 0;
	int element_index           = 0;
	int result                  = 0;
	int segment_index           = 0;

	fprintf(
	 stdout,
	 "Testing initialize\t" );

	if( libfdata_area_initialize(
	     &area,
	     ELEMENT_DATA_SIZE,
	     NULL,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_area_t *, libfdata_cache_t *, off64_t, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &fdata_test_area_read_element_data,
	     NULL,
	     0,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create area.",
		 function );

		goto on_error;
	}
	if( libfdata_area_append_segment(
	     area,
	     &segment_index,
	     0,
	     0,
	     MAXIMUM_NUMBER_OF_ELEMENTS * ELEMENT_DATA_SIZE,
	     0,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append segment to area.",
		 function );

		goto on_error;
	}
	if( libfdata_cache_initialize(
	     &cache,
	     4,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create cache.",
		 function );

		goto on_error;
	}
	for( element_index = 0;
	     element_index < MAXIMUM_NUMBER_OF_ELEMENTS;
	     element_index++ )
	{
		if( libfdata_area_get_element_value_at_offset(
		     area,
		     NULL,
		     cache,
		     element_offset,
		     (intptr_t **) &element_data,
		     0,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to retrieve element: %d value.",
			 function,
			 element_index );

			goto on_error;
		}
		result = 0;

		if( element_data != NULL )
		{
			byte_stream_copy_to_uint32_little_endian(
			 element_data,
			 test_element_index );

			if( test_element_index == (uint32_t) element_index )
			{
				result = 1;
			}
		}
		if( result == 0 )
		{
			break;
		}
		element_offset += ELEMENT_DATA_SIZE;
	}
	fprintf(
	 stdout,
	 "Testing get_element_value_at_offset\t" );

	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( libfdata_cache_free(
	     &cache,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free cache.",
		 function );

		goto on_error;
	}
	if( libfdata_area_free(
	     &area,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free area.",
		 function );

		goto on_error;
	}
	return( result );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stdout );

		libcerror_error_free(
		 &error );
	}
	if( cache != NULL )
	{
		libfdata_cache_free(
		 &cache,
		 NULL );
	}
	if( area != NULL )
	{
		libfdata_area_free(
		 &area,
		 NULL );
	}
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libfdata_area_t *area = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "Unsupported number of arguments.\n" );

		return( EXIT_FAILURE );
	}
	area = NULL;

	if( fdata_test_area_initialize(
	     &area,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	area = (libfdata_area_t *) 0x12345678UL;

	if( fdata_test_area_initialize(
	     &area,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	if( fdata_test_area_initialize(
	     NULL,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	/* Test: read elements
	 */
	if( fdata_test_area_read() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

