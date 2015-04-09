/*
 * Library btree type testing program
 *
 * Copyright (C) 2010-2015, Joachim Metz <joachim.metz@gmail.com>
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

#define LEAF_VALUE_DATA_SIZE			512
#define NODE_DATA_SIZE				512
#define MAXIMUM_NUMBER_OF_LEAF_VALUES		8
#define MAXIMUM_NUMBER_OF_NODE_LEVELS		3
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

/* Frees the key value data
 * Returns 1 if successful or -1 on error
 */
int fdata_test_btree_key_value_data_free(
     uint8_t **key_value_data,
     libcerror_error_t **error )
{
	static char *function = "fdata_test_btree_key_value_data_free";

	if( key_value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid key value data.",
		 function );

		return( -1 );
	}
	if( *key_value_data != NULL )
	{
		memory_free(
		 *key_value_data );

		*key_value_data = NULL;
	}
	return( 1 );
}

/* Print the key value
 */
void fdata_test_key_value_fprint(
      FILE *stream,
      uint8_t *key_value )
{
	int key_value_index = 0;

	fprintf(
	 stream,
	 "key_value: " );

	if( key_value == NULL )
	{
		fprintf(
		 stream,
		 "NULL" );
	}
	else
	{
		for( key_value_index = 0;
		     key_value_index < ( key_value[ 0 ] + 1 );
		     key_value_index++ )
		{
			fprintf(
			 stream,
			 "%02" PRIx8 " ",
			 key_value[ key_value_index ] );
		}
	}
	fprintf(
	 stream,
	 "\n" );
}

/* Key value compare function
 * Returns return LIBFDATA_COMPARE_LESS, LIBFDATA_COMPARE_EQUAL, LIBFDATA_COMPARE_GREATER if successful or -1 on error
 */
int fdata_test_key_value_compare(
     uint8_t *first_key_value,
     uint8_t *second_key_value,
     libcerror_error_t **error )
{
	static char *function   = "fdata_test_key_value_compare";
	ssize_t key_value_index = 0;
	ssize_t key_value_size  = 0;

	if( ( first_key_value == NULL )
	 && ( second_key_value == NULL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first and second key value.",
		 function );

		return( -1 );
	}
	if( first_key_value == NULL )
	{
		return( LIBFDATA_COMPARE_LESS );
	}
	if( second_key_value == NULL )
	{
		return( LIBFDATA_COMPARE_GREATER );
	}
	if( first_key_value[ 0 ] <= second_key_value[ 0 ] )
	{
		key_value_size = first_key_value[ 0 ];
	}
	else
	{
		key_value_size = second_key_value[ 0 ];
	}
	key_value_size += 1;

	for( key_value_index = 1;
	     key_value_index < key_value_size;
	     key_value_index++ )
	{
		if( first_key_value[ key_value_index ] < second_key_value[ key_value_index ] )
		{
			return( LIBFDATA_COMPARE_LESS );
		}
		else if( first_key_value[ key_value_index ] > second_key_value[ key_value_index ] )
		{
			return( LIBFDATA_COMPARE_GREATER );
		}
	}
	return( LIBFDATA_COMPARE_EQUAL );
}

/* Frees the leaf value data
 * Returns 1 if successful or -1 on error
 */
int fdata_test_btree_leaf_value_data_free(
     uint8_t **leaf_value_data,
     libcerror_error_t **error )
{
	static char *function = "fdata_test_btree_leaf_value_data_free";

	if( leaf_value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leaf value data.",
		 function );

		return( -1 );
	}
	if( *leaf_value_data != NULL )
	{
		memory_free(
		 *leaf_value_data );

		*leaf_value_data = NULL;
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
     int node_data_file_index FDATA_TEST_ATTRIBUTE_UNUSED,
     off64_t node_data_offset,
     size64_t node_data_size FDATA_TEST_ATTRIBUTE_UNUSED,
     uint32_t node_data_flags FDATA_TEST_ATTRIBUTE_UNUSED,
     uint8_t *key_value,
     uint8_t read_flags FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	uint8_t *key_value_data    = NULL;
	static char *function      = "fdata_test_btree_read_node";
	off64_t element_offset     = 0;
	size_t key_value_data_size = 0;
	int element_index          = 0;
	int leaf_value_index       = 0;
	int level                  = 0;
	int sub_node_index         = 0;

	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle );
	FDATA_TEST_UNREFERENCED_PARAMETER( node_data_file_index );
	FDATA_TEST_UNREFERENCED_PARAMETER( node_data_size );
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

		goto on_error;
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

		goto on_error;
	}
	key_value_data_size = sizeof( uint8_t ) * ( level + 2 );

	if( ( level + 1 ) < MAXIMUM_NUMBER_OF_NODE_LEVELS )
	{
		element_offset  = node_data_offset & 0xffffffffUL;
		element_offset *= MAXIMUM_NUMBER_OF_SUB_NODES;
		element_offset += (off64_t) ( level + 1 ) << 32;

		for( sub_node_index = 0;
		     sub_node_index < MAXIMUM_NUMBER_OF_SUB_NODES;
		     sub_node_index++ )
		{
			key_value_data = (uint8_t *) memory_allocate(
			                              (size_t) key_value_data_size );

			if( key_value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create key value data.",
				 function );

				goto on_error;
			}
			if( key_value != NULL )
			{
				if( memory_copy(
				     key_value_data,
				     key_value,
				     key_value_data_size - 1 ) == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
					 "%s: unable to copy key value data.",
					 function );

					goto on_error;
				}
			}
			key_value_data[ 0 ]                       = (uint8_t) key_value_data_size - 1;
			key_value_data[ key_value_data_size - 1 ] = sub_node_index;

			if( libfdata_btree_node_append_sub_node(
			     node,
			     &element_index,
			     0,
			     element_offset,
			     NODE_DATA_SIZE,
			     0,
			     (intptr_t *) key_value_data,
			     (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_key_value_data_free,
			     0,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append sub node.",
				 function );

				goto on_error;
			}
			key_value_data = NULL;

			element_offset += NODE_DATA_SIZE;
		}
	}
	else
	{
		element_offset  = node_data_offset & 0xffffffffUL;
		element_offset *= MAXIMUM_NUMBER_OF_LEAF_VALUES;
		element_offset += (off64_t) ( level + 1 ) << 32;

		for( leaf_value_index = 0;
		     leaf_value_index < MAXIMUM_NUMBER_OF_LEAF_VALUES;
		     leaf_value_index++ )
		{
			key_value_data = (uint8_t *) memory_allocate(
			                              (size_t) key_value_data_size );

			if( key_value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create key value data.",
				 function );

				goto on_error;
			}
			if( key_value != NULL )
			{
				if( memory_copy(
				     key_value_data,
				     key_value,
				     key_value_data_size - 1 ) == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
					 "%s: unable to copy key value data.",
					 function );

					goto on_error;
				}
			}
			key_value_data[ 0 ]                       = (uint8_t) key_value_data_size - 1;
			key_value_data[ key_value_data_size - 1 ] = leaf_value_index;

			if( libfdata_btree_node_append_leaf_value(
			     node,
			     &element_index,
			     0,
			     element_offset,
			     LEAF_VALUE_DATA_SIZE,
			     0,
			     (intptr_t *) key_value_data,
			     (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_key_value_data_free,
			     0,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append leaf value.",
				 function );

				goto on_error;
			}
			key_value_data = NULL;

			element_offset += NODE_DATA_SIZE;
		}
	}
	return( 1 );

on_error:
	if( key_value_data != NULL )
	{
		memory_free(
		 key_value_data );
	}
	return( 1 );
}

/* Reads a leaf value
 * Callback function for the btree
 * Returns 1 if successful or -1 on error
 */
int fdata_test_btree_read_leaf_value(
     intptr_t *data_handle FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *file_io_handle,
     libfdata_btree_t *tree,
     libfdata_cache_t *cache,
     int leaf_value_index,
     int leaf_value_data_file_index FDATA_TEST_ATTRIBUTE_UNUSED,
     off64_t leaf_value_data_offset,
     size64_t leaf_value_data_size,
     uint32_t leaf_value_data_flags FDATA_TEST_ATTRIBUTE_UNUSED,
     intptr_t *key_value FDATA_TEST_ATTRIBUTE_UNUSED,
     uint8_t read_flags FDATA_TEST_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	uint8_t *leaf_value_data       = NULL;
	static char *function          = "fdata_test_btree_read_leaf_value";
	uint32_t test_leaf_value_index = 0;

	FDATA_TEST_UNREFERENCED_PARAMETER( data_handle );
	FDATA_TEST_UNREFERENCED_PARAMETER( leaf_value_data_file_index );
	FDATA_TEST_UNREFERENCED_PARAMETER( leaf_value_data_offset );
	FDATA_TEST_UNREFERENCED_PARAMETER( leaf_value_data_flags );
	FDATA_TEST_UNREFERENCED_PARAMETER( key_value );
	FDATA_TEST_UNREFERENCED_PARAMETER( read_flags );

	leaf_value_data_size = sizeof( uint8_t ) * LEAF_VALUE_DATA_SIZE;

	leaf_value_data = (uint8_t *) memory_allocate(
	                               (size_t) leaf_value_data_size );

	if( leaf_value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create leaf value data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     leaf_value_data,
	     0,
	     (size_t) leaf_value_data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear leaf value data.",
		 function );

		goto on_error;
	}
	test_leaf_value_index = (uint32_t) ( ( leaf_value_data_offset & 0xffffffffUL ) / LEAF_VALUE_DATA_SIZE );

	byte_stream_copy_from_uint32_little_endian(
	 leaf_value_data,
	 test_leaf_value_index );

	if( libfdata_btree_set_leaf_value_by_index(
	     tree,
	     file_io_handle,
	     cache,
	     leaf_value_index,
	     (intptr_t *) leaf_value_data,
	     (int (*)(intptr_t **, libcerror_error_t **)) &fdata_test_btree_leaf_value_data_free,
	     LIBFDATA_BTREE_LEAF_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set leaf value data as leaf value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( leaf_value_data != NULL )
	{
		memory_free(
		 leaf_value_data );
	}
	return( -1 );
}

/* Tests reading the btree
 * Returns 1 if successful, 0 if not or -1 on error
 */
int fdata_test_btree_read(
    void )
{
	uint8_t key_value[ 8 ];

	libcerror_error_t *error         = NULL;
	libfdata_btree_t *btree          = NULL;
	libfdata_cache_t *cache          = NULL;
	uint8_t *leaf_value_data         = NULL;
	static char *function            = "fdata_test_btree_read";
	uint32_t test_leaf_value_index   = 0;
	int leaf_value_index             = 0;
	int number_of_leaf_values        = 0;
	int level                        = 0;
	int result                       = 0;
	int result_number_of_leaf_values = 0;

	if( libfdata_btree_initialize(
	     &btree,
	     NULL,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_btree_node_t *, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &fdata_test_btree_read_node,
	     (int (*)(intptr_t *, intptr_t *, libfdata_btree_t *, libfdata_cache_t *, int, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &fdata_test_btree_read_leaf_value,
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
	if( libfdata_cache_initialize(
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
	     level < MAXIMUM_NUMBER_OF_NODE_LEVELS;
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

	if( result != 0 )
	{
		for( leaf_value_index = 0;
		     leaf_value_index < number_of_leaf_values;
		     leaf_value_index++ )
		{
			if( libfdata_btree_get_leaf_value_by_index(
			     btree,
			     NULL,
			     cache,
			     leaf_value_index,
			     (intptr_t **) &leaf_value_data,
			     0,
			     &error ) != 1 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to retrieve leaf value: %d.",
				 function,
				 leaf_value_index );

				goto on_error;
			}
			result = 0;

			if( leaf_value_data != NULL )
			{
				byte_stream_copy_to_uint32_little_endian(
				 leaf_value_data,
				 test_leaf_value_index );

				if( test_leaf_value_index == (uint32_t) leaf_value_index )
				{
					result = 1;
				}
			}
			if( result == 0 )
			{
				break;
			}
		}
		fprintf(
		 stdout,
		 "Testing get_leaf_value_by_index\t" );

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
	}
	if( result != 0 )
	{
/* TODO add support for different maximum number of node levels
 */
#if MAXIMUM_NUMBER_OF_NODE_LEVELS != 3
#error unsupported maximum number of node levels
#endif
		key_value[ 0 ] = 0x03;
		key_value[ 1 ] = 0x04;
		key_value[ 2 ] = 0x07;
		key_value[ 3 ] = 0x05;
		key_value[ 4 ] = 0x00;
		key_value[ 5 ] = 0x00;
		key_value[ 6 ] = 0x00;
		key_value[ 7 ] = 0x00;

		leaf_value_index = 317;

		result = libfdata_btree_get_leaf_value_by_key(
		          btree,
		          NULL,
		          cache,
		          (intptr_t *) key_value,
		          (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &fdata_test_key_value_compare,
		          0,
		          (intptr_t **) &leaf_value_data,
		          0,
		          &error );

		if( result == -1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to retrieve leaf value by key.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			result = 0;

			if( leaf_value_data != NULL )
			{
				byte_stream_copy_to_uint32_little_endian(
				 leaf_value_data,
				 test_leaf_value_index );

				if( test_leaf_value_index == (uint32_t) leaf_value_index )
				{
					result = 1;
				}
			}
		}
		if( result != 0 )
		{
			/* See if the function fails gracefully without a compare function
			 */
			result = libfdata_btree_get_leaf_value_by_key(
			          btree,
			          NULL,
			          cache,
			          (intptr_t *) key_value,
			          NULL,
			          0,
			          (intptr_t **) &leaf_value_data,
			          0,
			          &error );

			if( result == -1 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to retrieve leaf value by key.",
				 function );

				goto on_error;
			}
			else if( result != 0 )
			{
				result = 0;
			}
			else
			{
				result = 1;
			}
		}
		if( result != 0 )
		{
			/* See if the function fails gracefully with a non existing key
			 */
			key_value[ 0 ] = 0x03;
			key_value[ 1 ] = 0xff;
			key_value[ 2 ] = 0xfe;
			key_value[ 3 ] = 0xfd;
			key_value[ 4 ] = 0x00;
			key_value[ 5 ] = 0x00;
			key_value[ 6 ] = 0x00;
			key_value[ 7 ] = 0x00;

			result = libfdata_btree_get_leaf_value_by_key(
			          btree,
			          NULL,
			          cache,
			          (intptr_t *) key_value,
			          (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &fdata_test_key_value_compare,
			          0,
			          (intptr_t **) &leaf_value_data,
			          0,
			          &error );

			if( result == -1 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to retrieve leaf value by key.",
				 function );

				goto on_error;
			}
			else if( result != 0 )
			{
				result = 0;
			}
			else
			{
				result = 1;
			}
		}
		fprintf(
		 stdout,
		 "Testing get_leaf_value_by_key\t" );

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
	}
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
		libfdata_cache_free(
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

