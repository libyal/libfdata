/*
 * Library btree type testing program
 *
 * Copyright (c) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "fdata_test_libcerror.h"
#include "fdata_test_libcstring.h"
#include "fdata_test_libfcache.h"
#include "fdata_test_libfdata.h"
#include "fdata_test_unused.h"

#define LEAF_VALUE_DATA_SIZE			512
#define NODE_DATA_SIZE				512
#define MAXIMUM_NUMBER_OF_LEAF_VALUES		8
#define MAXIMUM_NUMBER_OF_NODE_LEVELS		4
#define MAXIMUM_NUMBER_OF_SUB_NODES		8

/* Tests initializing the btree
 * Make sure the value btree is referencing, is set to NULL
 * Returns 1 if successful, 0 if not or -1 on error
 */
int fdata_test_btree_initialize(
     libfdata_btree_t **btree,
     int expected_result )
{
	libcerror_error_t *error = NULL;
	static char *function    = "fdata_test_btree_initialize";
	int result               = 0;

	fprintf(
	 stdout,
	 "Testing initialize\t" );

	result = libfdata_btree_initialize(
	          btree,
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
		 "%s: unable to create btree.",
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
		if( libfdata_btree_free(
		     btree,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free btree.",
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
int fdata_test_btree_element_data_free(
     uint8_t **element_data,
     libcerror_error_t **error )
{
	static char *function = "fdata_test_btree_element_data_free";

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

/* Reads a node
 * Callback function for the btree
 * Returns 1 if successful or -1 on error
 */
int fdata_test_btree_read_node(
     intptr_t *data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *file_io_handle,
     libfdata_btree_node_t *node,
     libfcache_cache_t *cache,
     int node_data_file_index FDATA_TEST_ATTRIBUTE_UNUSED,
     off64_t node_data_offset,
     size64_t node_data_size,
     uint32_t node_data_flags FDATA_TEST_ATTRIBUTE_UNUSED,
     uint8_t read_flags FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	static char *function  = "fdata_test_btree_read_node";
	off64_t element_offset = 0;
	int element_index      = 0;
	int leaf_value_index   = 0;
	int level              = 0;
	int sub_node_index     = 0;

	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle );
	FDATA_TEST_UNREFERENCED_PARAMETER( node_data_file_index );
	FDATA_TEST_UNREFERENCED_PARAMETER( node_data_flags );
	FDATA_TEST_UNREFERENCED_PARAMETER( read_flags );

	if( libfdata_btree_node_get_level(
	     node,
	     &level,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve level from node.",
		 function );

		return( -1 );
	}
	if( ( level < 0 )
	 || ( level >= MAXIMUM_NUMBER_OF_NODE_LEVELS ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid level value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( level + 1 ) < MAXIMUM_NUMBER_OF_NODE_LEVELS )
	{
		for( sub_node_index = 0;
		     sub_node_index < MAXIMUM_NUMBER_OF_SUB_NODES;
		     sub_node_index++ )
		{
			element_offset = ( ( level * MAXIMUM_NUMBER_OF_SUB_NODES ) + sub_node_index + 1 ) * NODE_DATA_SIZE;

			if( libfdata_btree_node_append_sub_node(
			     node,
			     &element_index,
			     0,
			     element_offset,
			     NODE_DATA_SIZE,
			     0,
			     NULL,
			     NULL,
			     0,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append sub node.",
				 function );

				return( -1 );
			}
		}
	}
	else
	{
		for( leaf_value_index = 0;
		     leaf_value_index < MAXIMUM_NUMBER_OF_LEAF_VALUES;
		     leaf_value_index++ )
		{
/* TODO make sure leaf nodes have unique offset */
			element_offset = ( ( level * MAXIMUM_NUMBER_OF_SUB_NODES ) + leaf_value_index + 1 ) * NODE_DATA_SIZE;

			if( libfdata_btree_node_append_leaf_value(
			     node,
			     &element_index,
			     0,
			     element_offset,
			     LEAF_VALUE_DATA_SIZE,
			     0,
			     NULL,
			     NULL,
			     0,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append leaf value.",
				 function );

				return( -1 );
			}
		}
	}
	return( 1 );
}

/* Tests reading the btree
 * Returns 1 if successful, 0 if not or -1 on error
 */
int fdata_test_btree_read(
    void )
{
	libfcache_cache_t *cache         = NULL;
	libfdata_btree_t *btree          = NULL;
	libcerror_error_t *error         = NULL;
	uint8_t *element_data            = NULL;
	static char *function            = "fdata_test_btree_read";
	uint32_t test_element_index      = 0;
	int element_index                = 0;
	int number_of_leaf_values        = 0;
	int level                        = 0;
	int result                       = 0;
	int result_number_of_leaf_values = 0;
	int segment_index                = 0;

	fprintf(
	 stdout,
	 "Testing initialize\t" );

	if( libfdata_btree_initialize(
	     &btree,
	     NULL,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_btree_node_t *, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &fdata_test_btree_read_node,
	     NULL,
	     0,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create btree.",
		 function );

		goto on_error;
	}
	if( libfdata_btree_set_root_node(
	     btree,
	     0,
	     0,
	     NODE_DATA_SIZE,
	     0,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set root node in btree.",
		 function );

		goto on_error;
	}
	if( libfcache_cache_initialize(
	     &cache,
	     128,
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
	if( libfdata_btree_get_number_of_leaf_values(
	     btree,
	     NULL,
	     cache,
	     &number_of_leaf_values,
	     0,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of leaf values in btree.",
		 function );

		goto on_error;
	}
	result_number_of_leaf_values = 1;

	for( level = 1;
	     level < ( MAXIMUM_NUMBER_OF_NODE_LEVELS - 1 );
	     level++ )
	{
		result_number_of_leaf_values *= MAXIMUM_NUMBER_OF_SUB_NODES;
	}
	result_number_of_leaf_values *= MAXIMUM_NUMBER_OF_LEAF_VALUES;

	if( number_of_leaf_values != result_number_of_leaf_values )
	{
		result = 0;
	}
	else
	{
		result = 1;
	}
	fprintf(
	 stdout,
	 "Testing _get_number_of_leaf_values\t" );

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

	if( libfcache_cache_free(
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
	if( libfdata_btree_free(
	     &btree,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free btree.",
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
		libfcache_cache_free(
		 &cache,
		 NULL );
	}
	if( btree != NULL )
	{
		libfdata_btree_free(
		 &btree,
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
	libfdata_btree_t *btree = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "Unsupported number of arguments.\n" );

		return( EXIT_FAILURE );
	}
	btree = NULL;

	if( fdata_test_btree_initialize(
	     &btree,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	btree = (libfdata_btree_t *) 0x12345678UL;

	if( fdata_test_btree_initialize(
	     &btree,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	if( fdata_test_btree_initialize(
	     NULL,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	/* Test: read nodes
	 */
	if( fdata_test_btree_read() != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

