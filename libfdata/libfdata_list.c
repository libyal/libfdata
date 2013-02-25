/*
 * The list functions
 *
 * Copyright (c) 2010-2013, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libfdata_definitions.h"
#include "libfdata_libcdata.h"
#include "libfdata_libcerror.h"
#include "libfdata_libcnotify.h"
#include "libfdata_libfcache.h"
#include "libfdata_list.h"
#include "libfdata_list_element.h"
#include "libfdata_types.h"

#define libfdata_list_calculate_cache_entry_index( element_index, number_of_cache_entries ) \
	element_index % number_of_cache_entries

/* Initializes the list
 *
 * If the flag LIBFDATA_FLAG_DATA_HANDLE_MANAGED is set the list
 * takes over management of the data handle and the data handle is freed when
 * no longer needed
 *
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_initialize(
     libfdata_list_t **list,
     intptr_t *data_handle,
     int (*free_data_handle)(
            intptr_t **data_handle,
            libcerror_error_t **error ),
     int (*clone_data_handle)(
            intptr_t **destination_data_handle,
            intptr_t *source_data_handle,
            libcerror_error_t **error ),
     int (*read_element_data)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfdata_list_element_t *list_element,
            libfcache_cache_t *cache,
            int data_range_file_index,
            off64_t data_range_offset,
            size64_t data_range_size,
            uint32_t data_range_flags,
            uint8_t read_flags,
            libcerror_error_t **error ),
     int (*write_element_data)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfdata_list_element_t *list_element,
            libfcache_cache_t *cache,
            int data_range_file_index,
            off64_t data_range_offset,
            size64_t data_range_size,
            uint32_t data_range_flags,
            uint8_t write_flags,
            libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_initialize";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	if( *list != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid list value already set.",
		 function );

		return( -1 );
	}
	internal_list = memory_allocate_structure(
	                 libfdata_internal_list_t );

	if( internal_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create list.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_list,
	     0,
	     sizeof( libfdata_internal_list_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear list.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_list->elements ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create elements array.",
		 function );

		goto on_error;
	}
	internal_list->flags             |= flags;
	internal_list->data_handle        = data_handle;
	internal_list->free_data_handle   = free_data_handle;
	internal_list->clone_data_handle  = clone_data_handle;
	internal_list->read_element_data  = read_element_data;
	internal_list->write_element_data = write_element_data;

	*list = (libfdata_list_t *) internal_list;

	return( 1 );

on_error:
	if( internal_list != NULL )
	{
		memory_free(
		 internal_list );
	}
	return( -1 );
}

/* Frees the list
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_free(
     libfdata_list_t **list,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_free";
	int result                              = 1;

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	if( *list != NULL )
	{
		internal_list = (libfdata_internal_list_t *) *list;
		*list         = NULL;

		if( libcdata_array_free(
		     &( internal_list->elements ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_list_element_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the elements array.",
			 function );

			result = -1;
		}
		if( ( internal_list->flags & LIBFDATA_FLAG_DATA_HANDLE_MANAGED ) != 0 )
		{
			if( internal_list->data_handle != NULL )
			{
				if( internal_list->free_data_handle == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: invalid list - missing free data handle function.",
					 function );

					result = -1;
				}
				else if( internal_list->free_data_handle(
				          &( internal_list->data_handle ),
				          error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free data handle.",
					 function );

					result = -1;
				}
			}
		}
		memory_free(
		 internal_list );
	}
	return( result );
}

/* Clones (duplicates) the list
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_clone(
     libfdata_list_t **destination_list,
     libfdata_list_t *source_list,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_source_list = NULL;
	intptr_t *destination_data_handle              = NULL;
	static char *function                          = "libfdata_list_clone";

	if( destination_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination list.",
		 function );

		return( -1 );
	}
	if( *destination_list != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination list value already set.",
		 function );

		return( -1 );
	}
	if( source_list == NULL )
	{
		*destination_list = NULL;

		return( 1 );
	}
	internal_source_list = (libfdata_internal_list_t *) source_list;

	if( internal_source_list->data_handle != NULL )
	{
		if( internal_source_list->free_data_handle == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid source list - missing free data handle function.",
			 function );

			goto on_error;
		}
		if( internal_source_list->clone_data_handle == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid source list - missing clone data handle function.",
			 function );

			goto on_error;
		}
		if( internal_source_list->clone_data_handle(
		     &destination_data_handle,
		     internal_source_list->data_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to clone data handle.",
			 function );

			goto on_error;
		}
	}
	if( libfdata_list_initialize(
	     destination_list,
	     destination_data_handle,
	     internal_source_list->free_data_handle,
	     internal_source_list->clone_data_handle,
	     internal_source_list->read_element_data,
	     internal_source_list->write_element_data,
	     LIBFDATA_FLAG_DATA_HANDLE_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create destination list.",
		 function );

		goto on_error;
	}
	if( *destination_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing destination list.",
		 function );

		return( -1 );
	}
	destination_data_handle = NULL;

	if( libfdata_list_clone_elements(
	     *destination_list,
	     source_list,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy list elements.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *destination_list != NULL )
	{
		libfdata_list_free(
		 destination_list,
		 NULL );
	}
	if( destination_data_handle != NULL )
	{
		internal_source_list->free_data_handle(
		 &destination_data_handle,
		 NULL );
	}
	return( -1 );
}

/* Clones (duplicates) the elements of the list
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_clone_elements(
     libfdata_list_t *destination_list,
     libfdata_list_t *source_list,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_destination_list = NULL;
	libfdata_internal_list_t *internal_source_list      = NULL;
	libfdata_list_element_t *destination_list_element   = NULL;
	libfdata_list_element_t *source_list_element        = NULL;
	static char *function                               = "libfdata_list_clone_elements";
	int element_index                                   = 0;
	int number_of_elements                              = 0;

	if( destination_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination list.",
		 function );

		return( -1 );
	}
	internal_destination_list = (libfdata_internal_list_t *) destination_list;

	if( source_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source list.",
		 function );

		return( -1 );
	}
	internal_source_list = (libfdata_internal_list_t *) source_list;

	if( libcdata_array_get_number_of_entries(
	     internal_source_list->elements,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from source elements array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_empty(
	     internal_destination_list->elements,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_list_element_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty destination elements array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_resize(
	     internal_destination_list->elements,
	     number_of_elements,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_list_element_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize destination elements array.",
		 function );

		goto on_error;
	}
	for( element_index = 0;
	     element_index < number_of_elements;
	     element_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_source_list->elements,
		     element_index,
		     (intptr_t **) &source_list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve list element: %d from source elements array.",
			 function,
			 element_index );

			goto on_error;
		}
		if( source_list_element == NULL )
		{
			continue;
		}
		if( libfdata_list_element_clone(
		     &destination_list_element,
		     source_list_element,
		     destination_list,
		     element_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create destination list element: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		if( libcdata_array_set_entry_by_index(
		     internal_destination_list->elements,
		     element_index,
		     (intptr_t *) destination_list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set list element: %d in destination elements array.",
			 function,
			 element_index );

			goto on_error;
		}
		destination_list_element = NULL;
	}
	internal_destination_list->data_size = internal_source_list->data_size;

	return( 1 );

on_error:
	if( destination_list_element != NULL )
	{
		libfdata_list_element_free(
		 &destination_list_element,
		 NULL );
	}
	return( -1 );
}

/* Empties the elements
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_empty(
     libfdata_list_t *list,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_empty";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_empty(
	     internal_list->elements,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_list_element_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to emtpy elements array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Resizes the elements
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_resize(
     libfdata_list_t *list,
     int number_of_elements,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_resize";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_resize(
	     internal_list->elements,
	     number_of_elements,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_list_element_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize elements array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of elements of the list
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_number_of_elements(
     libfdata_list_t *list,
     int *number_of_elements,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_get_number_of_elements";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_get_number_of_entries(
	     internal_list->elements,
	     number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from elements array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Calculates the value offsets
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_calculate_value_offsets(
     libfdata_internal_list_t *internal_list,
     libcerror_error_t **error )
{
	libfdata_list_element_t *list_element = NULL;
	static char *function                 = "libfdata_list_calculate_value_offsets";
	off64_t calculated_value_offset       = 0;
	off64_t data_range_offset             = 0;
	size64_t data_range_size              = 0;
	uint32_t data_range_flags             = 0;
	int data_range_file_index             = -1;
	int element_index                     = -1;
	int number_of_elements                = 0;

	if( internal_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal list.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_list->elements,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from elements array.",
		 function );

		return( -1 );
	}
	for( element_index = 0;
	     element_index < number_of_elements;
	     element_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_list->elements,
		     element_index,
		     (intptr_t **) &list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve list element: %d from elements array.",
			 function,
			 element_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     list_element,
		     &data_range_file_index,
		     &data_range_offset,
		     &data_range_size,
		     &data_range_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data range of list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( libfdata_list_element_set_value_offset(
		     list_element,
		     calculated_value_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set data offset of list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		calculated_value_offset += (off64_t) data_range_size;
	}
	internal_list->flags &= ~( LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES );

	return( 1 );
}

/* Retrieves a specific element
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_element_by_index(
     libfdata_list_t *list,
     int element_index,
     libfdata_list_element_t **element,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_get_element_by_index";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_get_entry_by_index(
	     internal_list->elements,
	     element_index,
	     (intptr_t **) element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element: %d from elements array.",
		 function,
		 element_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves an element for the specified offset
 * Returns 1 if successful, 0 if no matching element was found or -1 on error
 */
int libfdata_list_get_element_by_offset(
     libfdata_list_t *list,
     off64_t value_offset,
     int *element_index,
     libfdata_list_element_t **element,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_get_element_by_offset";
	off64_t data_range_offset               = 0;
	size64_t data_range_size                = 0;
        uint32_t data_range_flags               = 0;
	int data_range_file_index               = -1;
	int number_of_elements                  = 0;

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( element_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element index.",
		 function );

		return( -1 );
	}
	if( element == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_list->elements,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from elements array.",
		 function );

		return( -1 );
	}
	for( *element_index = 0;
	     *element_index < number_of_elements;
	     *element_index += 1 )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_list->elements,
		     *element_index,
		     (intptr_t **) element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve list element: %d from elements array.",
			 function,
			 *element_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     *element,
		     &data_range_file_index,
		     &data_range_offset,
		     &data_range_size,
		     &data_range_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data range of list element: %d.",
			 function,
			 *element_index );

			return( -1 );
		}
		if( ( value_offset >= data_range_offset )
		 && ( value_offset < (off64_t) ( data_range_offset + data_range_size ) ) )
		{
			return( 1 );
		}
	}
	*element = NULL;

	return( 0 );
}

/* Sets the data offset and size of a specific element
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_set_element_by_index(
     libfdata_list_t *list,
     int element_index,
     int file_index,
     off64_t offset,
     size64_t size,
     uint32_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *list_element   = NULL;
	static char *function                   = "libfdata_list_set_element_by_index";
	off64_t previous_offset                 = 0;
	size64_t previous_size                  = 0;
	uint32_t previous_flags                 = 0;
	int previous_file_index                 = 0;

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_get_entry_by_index(
	     internal_list->elements,
	     element_index,
	     (intptr_t **) &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element: %d from elements array.",
		 function,
		 element_index );

		return( -1 );
	}
	if( list_element == NULL )
	{
		if( libfdata_list_element_initialize(
		     &list_element,
		     list,
		     element_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create list element.",
			 function );

			return( -1 );
		}
		if( libcdata_array_set_entry_by_index(
		     internal_list->elements,
		     element_index,
		     (intptr_t *) list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set list element: %d in elements array.",
			 function,
			 element_index );

			libfdata_list_element_free(
			 &list_element,
			 NULL );

			return( -1 );
		}
	}
	else
	{
		if( libfdata_list_element_get_data_range(
		     list_element,
		     &previous_file_index,
		     &previous_offset,
		     &previous_size,
		     &previous_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data range of list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		internal_list->data_size -= previous_size;
	}
	if( libfdata_list_element_set_data_range(
	     list_element,
	     file_index,
	     offset,
	     size,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data range of list element: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	internal_list->data_size += size;
	internal_list->flags     |= LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES;

	return( 1 );
}

/* Appends an element data offset and size
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_append_element(
     libfdata_list_t *list,
     int *element_index,
     int file_index,
     off64_t offset,
     size64_t size,
     uint32_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *list_element   = NULL;
	static char *function                   = "libfdata_list_append_element";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libfdata_list_element_initialize(
	     &list_element,
	     list,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create list element.",
		 function );

		goto on_error;
	}
	if( libfdata_list_element_set_data_range(
	     list_element,
	     file_index,
	     offset,
	     size,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data range of list element.",
		 function );

		goto on_error;
	}
	if( libfdata_list_element_set_value_offset(
	     list_element,
	     internal_list->data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set list element data offset.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_list->elements,
	     element_index,
	     (intptr_t *) list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append list element to elements array.",
		 function );

		goto on_error;
	}
	if( libfdata_list_element_set_element_index(
	     list_element,
	     *element_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set list element index.",
		 function );

		list_element = NULL;

		goto on_error;
	}
	internal_list->data_size += size;

	return( 1 );

on_error:
	if( list_element != NULL )
	{
		libfdata_list_element_free(
		 &list_element,
		 NULL );
	}
	return( -1 );
}

/* Determines if a specific element is set
 * Returns 1 if element is set, 0 if not or -1 on error
 */
int libfdata_list_is_element_set(
     libfdata_list_t *list,
     int element_index,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *element        = NULL;
	static char *function                   = "libfdata_list_is_element_set";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_get_entry_by_index(
	     internal_list->elements,
	     element_index,
	     (intptr_t **) &element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element: %d from elements array.",
		 function,
		 element_index );

		return( -1 );
	}
	if( element == NULL )
	{
		return( 0 );
	}
	return( 1 );
}

/* Retrieves the element index for a specific value offset
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_element_index_at_value_offset(
     libfdata_list_t *list,
     off64_t value_offset,
     int *element_index,
     size_t *element_offset,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *list_element   = NULL;
	static char *function                   = "libfdata_list_get_element_index_at_value_offset";
	off64_t calculated_value_offset         = 0;
	off64_t data_range_offset               = 0;
	size64_t data_range_size                = 0;
	uint32_t data_range_flags               = 0;
	int calculated_element_index            = -1;
	int data_range_file_index               = -1;
	int initial_element_index               = -1;
	int number_of_elements                  = 0;

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( internal_list->data_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid list - data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( value_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid value offset value less than zero.",
		 function );

		return( -1 );
	}
	if( element_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element index.",
		 function );

		return( -1 );
	}
	if( element_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element offset.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_list->elements,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from elements array.",
		 function );

		return( -1 );
	}
	if( ( internal_list->flags & LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES ) != 0 )
	{
		if( libfdata_list_calculate_value_offsets(
		     internal_list,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to calculate value offsets.",
			 function );

			return( -1 );
		}
	}
	/* This assumes a fairly even distribution of the sizes of the list elements
	 */
	initial_element_index = (int) ( ( number_of_elements * value_offset ) / internal_list->data_size );

	/* Look for the corresponding list element upwards in the list
	 */
	for( calculated_element_index = initial_element_index;
	     calculated_element_index < number_of_elements;
	     calculated_element_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_list->elements,
		     calculated_element_index,
		     (intptr_t **) &list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve list element: %d from elements array.",
			 function,
			 calculated_element_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     list_element,
		     &data_range_file_index,
		     &data_range_offset,
		     &data_range_size,
		     &data_range_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data range of list element: %d.",
			 function,
			 calculated_element_index );

			return( -1 );
		}
		if( libfdata_list_element_get_value_offset(
		     list_element,
		     &calculated_value_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to retrieve data offset of list element: %d.",
			 function,
			 calculated_element_index );

			return( -1 );
		}
		/* Check if the data offset is in the list element
		 */
		if( ( value_offset >= calculated_value_offset )
		 && ( value_offset < ( calculated_value_offset + (off64_t) data_range_size ) ) )
		{
			value_offset -= calculated_value_offset;

			break;
		}
		/* Check if the data offset is out of bounds
		 */
		if( value_offset < calculated_value_offset )
		{
			calculated_element_index = number_of_elements;

			break;
		}
	}
	if( calculated_element_index >= number_of_elements )
	{
		/* Look for the corresponding list element downwards in the list
		 */
		for( calculated_element_index = initial_element_index;
		     calculated_element_index >= 0;
		     calculated_element_index-- )
		{
			if( libcdata_array_get_entry_by_index(
			     internal_list->elements,
			     calculated_element_index,
			     (intptr_t **) &list_element,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve list element: %d from elements array.",
				 function,
				 calculated_element_index );

				return( -1 );
			}
			if( libfdata_list_element_get_data_range(
			     list_element,
			     &data_range_file_index,
			     &data_range_offset,
			     &data_range_size,
			     &data_range_flags,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve data range of list element: %d.",
				 function,
				 calculated_element_index );

				return( -1 );
			}
			if( libfdata_list_element_get_value_offset(
			     list_element,
			     &calculated_value_offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to retrieve data offset of list element: %d.",
				 function,
				 calculated_element_index );

				return( -1 );
			}
			/* Check if the data offset is in the list element
			 */
			if( ( value_offset >= calculated_value_offset )
			 && ( value_offset < ( calculated_value_offset + (off64_t) data_range_size ) ) )
			{
				value_offset -= calculated_value_offset;

				break;
			}
			/* Check if the data offset is out of bounds
			 */
			if( value_offset > calculated_value_offset )
			{
				calculated_element_index = -1;

				break;
			}
		}
	}
	if( calculated_element_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element index value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( value_offset < 0 )
	 || ( value_offset > (off64_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element offset value out of bounds.",
		 function );

		return( -1 );
	}
	*element_index  = calculated_element_index;
	*element_offset = (size_t) value_offset;

	return( 1 );
}

/* Retrieves the element index for a specific value index
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_element_index_at_value_index(
     libfdata_list_t *list,
     int value_index,
     size_t value_size,
     int *element_index,
     size_t *element_offset,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *list_element   = NULL;
	static char *function                   = "libfdata_list_get_element_index_at_value_index";
	off64_t data_range_offset               = 0;
	size64_t data_range_size                = 0;
	uint64_t number_of_values               = 0;
	uint32_t data_range_flags               = 0;
	int calculated_element_index            = -1;
	int data_range_file_index               = -1;
	int number_of_elements                  = 0;

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( value_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid value index value less than zero.",
		 function );

		return( -1 );
	}
	if( value_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid value size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( element_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element index.",
		 function );

		return( -1 );
	}
	if( element_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element offset.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_list->elements,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from elements array.",
		 function );

		return( -1 );
	}
	for( calculated_element_index = 0;
	     calculated_element_index < number_of_elements;
	     calculated_element_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_list->elements,
		     *element_index,
		     (intptr_t **) &list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d from elements array.",
			 function,
			 calculated_element_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     list_element,
		     &data_range_file_index,
		     &data_range_offset,
		     &data_range_size,
		     &data_range_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data range of list element: %d.",
			 function,
			 calculated_element_index );

			return( -1 );
		}
		number_of_values = data_range_size / value_size;

		if( number_of_values > (uint64_t) INT_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid number of values value exceeds maximum.",
			 function );

			return( -1 );
		}
		if( value_index < (int) number_of_values )
		{
			break;
		}
		value_index -= (int) number_of_values;
	}
	if( calculated_element_index >= number_of_elements )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element index value out of bounds.",
		 function );

		return( -1 );
	}
	if( value_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid value index value out of bounds.",
		 function );

		return( -1 );
	}
	*element_index  = calculated_element_index;
	*element_offset = value_size * value_index;

	return( 1 );
}

/* Data range functions
 */

/* Retrieves the data range of a specific element
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_data_range_by_index(
     libfdata_list_t *list,
     int element_index,
     int *file_index,
     off64_t *offset,
     size64_t *size,
     uint32_t *flags,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *list_element   = NULL;
	static char *function                   = "libfdata_list_get_data_range_by_index";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_get_entry_by_index(
	     internal_list->elements,
	     element_index,
	     (intptr_t **) &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element: %d from elements array.",
		 function,
		 element_index );

		return( -1 );
	}
	if( libfdata_list_element_get_data_range(
	     list_element,
	     file_index,
	     offset,
	     size,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data range from list element: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	return( 1 );
}

/* Sets the data range of a specific element
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_set_data_range_by_index(
     libfdata_list_t *list,
     int element_index,
     int file_index,
     off64_t offset,
     size64_t size,
     uint32_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *list_element   = NULL;
	static char *function                   = "libfdata_list_set_data_range_by_index";
	off64_t previous_offset                 = 0;
	size64_t previous_size                  = 0;
	uint32_t previous_flags                 = 0;
	int previous_file_index                 = 0;

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_get_entry_by_index(
	     internal_list->elements,
	     element_index,
	     (intptr_t **) &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element: %d from elements array.",
		 function,
		 element_index );

		return( -1 );
	}
	if( libfdata_list_element_get_data_range(
	     list_element,
	     &previous_file_index,
	     &previous_offset,
	     &previous_size,
	     &previous_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data range of list element: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	internal_list->data_size -= previous_size;

	if( libfdata_list_element_set_data_range(
	     list_element,
	     file_index,
	     offset,
	     size,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data range of list element: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	internal_list->data_size += size;
	internal_list->flags     |= LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES;

	return( 1 );
}

/* List element value functions
 */

/* Retrieves the value the element
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_element_value(
     libfdata_list_t *list,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     libfdata_list_element_t *element,
     intptr_t **element_value,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfcache_cache_value_t *cache_value    = NULL;
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_get_element_value";
        off64_t cache_value_offset              = (off64_t) -1;
	off64_t data_range_offset               = 0;
	size64_t data_range_size                = 0;
	time_t cache_value_timestamp            = 0;
	time_t element_timestamp                = 0;
	uint32_t data_range_flags               = 0;
	int cache_entry_index                   = -1;
	int cache_value_file_index              = -1;
	int data_range_file_index               = -1;
	int element_index                       = -1;
	int number_of_cache_entries             = 0;
	int result                              = 0;

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( internal_list->read_element_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid list - missing read element data function.",
		 function );

		return( -1 );
	}
	if( libfdata_list_element_get_data_range(
	     element,
	     &data_range_file_index,
	     &data_range_offset,
	     &data_range_size,
	     &data_range_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data range from list element.",
		 function );

		return( -1 );
	}
	if( libfcache_cache_get_number_of_entries(
	     cache,
	     &number_of_cache_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of cache entries.",
		 function );

		return( -1 );
	}
	if( libfdata_list_element_get_element_index(
	     element,
	     &element_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index from list element.",
		 function );

		return( -1 );
	}
	if( number_of_cache_entries <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of cache entries value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( read_flags & LIBFDATA_READ_FLAG_IGNORE_CACHE ) == 0 )
	{
		cache_entry_index = libfdata_list_calculate_cache_entry_index(
		                     element_index,
		                     number_of_cache_entries );

		if( libfcache_cache_get_value_by_index(
		     cache,
		     cache_entry_index,
		     &cache_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache entry: %d from cache.",
			 function,
			 cache_entry_index );

			return( -1 );
		}
		if( cache_value != NULL )
		{
			if( libfdata_list_element_get_timestamp(
			     element,
			     &element_timestamp,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve time stamp from list element.",
				 function );

				return( -1 );
			}
			if( libfcache_cache_value_get_identifier(
			     cache_value,
			     &cache_value_file_index,
			     &cache_value_offset,
			     &cache_value_timestamp,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve cache value identifier.",
				 function );

				return( -1 );
			}
		}
		if( ( data_range_offset == cache_value_offset )
		 && ( element_timestamp == cache_value_timestamp ) )
		{
			result = 1;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( result == 0 )
			{
				libcnotify_printf(
				 "%s: cache: 0x%08" PRIjx " miss (%d out of %d)\n",
				 function,
				 (intptr_t) cache,
				 cache_entry_index,
				 number_of_cache_entries );
			}
			else
			{
				libcnotify_printf(
				 "%s: cache: 0x%08" PRIjx " hit (%d out of %d)\n",
				 function,
				 (intptr_t) cache,
				 cache_entry_index,
				 number_of_cache_entries );
			}
		}
#endif
	}
	if( result == 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading element data at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIu64 "\n",
			 function,
			 data_range_offset,
			 data_range_offset,
			 data_range_size );
		}
#endif
		if( internal_list->read_element_data(
		     internal_list->data_handle,
		     file_io_handle,
		     element,
		     cache,
		     data_range_file_index,
		     data_range_offset,
		     data_range_size,
		     data_range_flags,
		     read_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read element data at offset: %" PRIi64 ".",
			 function,
			 data_range_offset );

			return( -1 );
		}
		cache_entry_index = libfdata_list_calculate_cache_entry_index(
		                     element_index,
		                     number_of_cache_entries );

		if( libfcache_cache_get_value_by_index(
		     cache,
		     cache_entry_index,
		     &cache_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache entry: %d from cache.",
			 function,
			 cache_entry_index );

			return( -1 );
		}
		if( cache_value != NULL )
		{
			if( libfdata_list_element_get_timestamp(
			     element,
			     &element_timestamp,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve time stamp from list element.",
				 function );

				return( -1 );
			}
			if( libfcache_cache_value_get_identifier(
			     cache_value,
			     &cache_value_file_index,
			     &cache_value_offset,
			     &cache_value_timestamp,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve cache value identifier.",
				 function );

				return( -1 );
			}
		}
		if( ( data_range_offset != cache_value_offset )
		 || ( element_timestamp != cache_value_timestamp ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing cache value.",
			 function );

			return( -1 );
		}
	}
	if( libfcache_cache_value_get_value(
	     cache_value,
	     element_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the value of a specific element
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_element_value_by_index(
     libfdata_list_t *list,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int element_index,
     intptr_t **element_value,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *list_element   = NULL;
	static char *function                   = "libfdata_list_get_element_value_by_index";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_get_entry_by_index(
	     internal_list->elements,
	     element_index,
	     (intptr_t **) &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element: %d from elements array.",
		 function,
		 element_index );

		return( -1 );
	}
	if( libfdata_list_get_element_value(
	     list,
	     file_io_handle,
	     cache,
	     list_element,
	     element_value,
	     read_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the value an element at a specific offset
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_element_value_at_offset(
     libfdata_list_t *list,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     off64_t value_offset,
     intptr_t **element_value,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	static char *function = "libfdata_list_get_element_value_at_offset";
	size_t element_offset = 0;
	int element_index     = 0;

	if( libfdata_list_get_element_index_at_value_offset(
	     list,
	     value_offset,
	     &element_index,
	     &element_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index at offset: %" PRIi64 ".",
		 function,
		 value_offset );

		return( -1 );
	}
	if( libfdata_list_get_element_value_by_index(
	     list,
	     file_io_handle,
	     cache,
	     element_index,
	     element_value,
	     read_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element: %d value.",
		 function,
		 element_index );

		return( -1 );
	}
	return( 1 );
}

/* Sets the value of a specific element
 *
 * If the flag LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED is set the list
 * takes over management of the value and the value is freed when
 * no longer needed.
 *
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_set_element_value(
     libfdata_list_t *list,
     libfcache_cache_t *cache,
     libfdata_list_element_t *element,
     intptr_t *element_value,
     int (*free_element_value)(
            intptr_t **element_value,
            libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error )
{
	static char *function       = "libfdata_list_set_element_value";
	off64_t data_range_offset   = 0;
	size64_t data_range_size    = 0;
	time_t element_timestamp    = 0;
	uint32_t data_range_flags   = 0;
	int cache_entry_index       = -1;
	int data_range_file_index   = -1;
	int element_index           = -1;
	int number_of_cache_entries = 0;

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	if( libfdata_list_element_get_data_range(
	     element,
	     &data_range_file_index,
	     &data_range_offset,
	     &data_range_size,
	     &data_range_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data range from list element.",
		 function );

		return( -1 );
	}
	if( libfdata_list_element_get_timestamp(
	     element,
	     &element_timestamp,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve time stamp from list element.",
		 function );

		return( -1 );
	}
	if( libfcache_cache_get_number_of_entries(
	     cache,
	     &number_of_cache_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of cache entries.",
		 function );

		return( -1 );
	}
	if( libfdata_list_element_get_element_index(
	     element,
	     &element_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index from list element.",
		 function );

		return( -1 );
	}
	if( number_of_cache_entries <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of cache entries value out of bounds.",
		 function );

		return( -1 );
	}
	cache_entry_index = libfdata_list_calculate_cache_entry_index(
	                     element_index,
	                     number_of_cache_entries );

	if( libfcache_cache_set_value_by_index(
	     cache,
	     cache_entry_index,
	     0,
	     data_range_offset,
	     element_timestamp,
	     element_value,
	     free_element_value,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value in cache entry: %d.",
		 function,
		 cache_entry_index );

		return( -1 );
	}
	return( 1 );
}

/* Sets the value of a specific element
 *
 * If the flag LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED is set the list
 * takes over management of the value and the value is freed when
 * no longer needed.
 *
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_set_element_value_by_index(
     libfdata_list_t *list,
     libfcache_cache_t *cache,
     int element_index,
     intptr_t *element_value,
     int (*free_element_value)(
            intptr_t **element_value,
            libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	libfdata_list_element_t *list_element   = NULL;
	static char *function                   = "libfdata_list_set_element_value_by_index";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( libcdata_array_get_entry_by_index(
	     internal_list->elements,
	     element_index,
	     (intptr_t **) &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element: %d from elements array.",
		 function,
		 element_index );

		return( -1 );
	}
	if( libfdata_list_set_element_value(
	     list,
	     cache,
	     list_element,
	     element_value,
	     free_element_value,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set element value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data size of the list
 * Returns 1 if successful or -1 on error
 */
int libfdata_list_get_data_size(
     libfdata_list_t *list,
     size64_t *data_size,
     libcerror_error_t **error )
{
	libfdata_internal_list_t *internal_list = NULL;
	static char *function                   = "libfdata_list_get_data_size";

	if( list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list.",
		 function );

		return( -1 );
	}
	internal_list = (libfdata_internal_list_t *) list;

	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	*data_size = internal_list->data_size;

	return( 1 );
}

