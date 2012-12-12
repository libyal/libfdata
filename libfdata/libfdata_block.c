/*
 * The block functions
 *
 * Copyright (c) 2010-2012, Joachim Metz <joachim.metz@gmail.com>
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

#include "libfdata_block.h"
#include "libfdata_buffer.h"
#include "libfdata_definitions.h"
#include "libfdata_libcerror.h"
#include "libfdata_libcnotify.h"
#include "libfdata_libfcache.h"
#include "libfdata_mapped_range.h"
#include "libfdata_range.h"
#include "libfdata_types.h"
#include "libfdata_unused.h"

#define libfdata_block_calculate_cache_entry_index( segment_index, number_of_cache_entries ) \
	segment_index % number_of_cache_entries

/* Initializes the block
 *
 * If the flag LIBFDATA_FLAG_DATA_HANDLE_MANAGED is set the block
 * takes over management of the data handle and the data handle is freed when
 * no longer needed
 *
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_initialize(
     libfdata_block_t **block,
     intptr_t *data_handle,
     int (*free_data_handle)(
            intptr_t **data_handle,
            libcerror_error_t **error ),
     int (*clone_data_handle)(
            intptr_t **destination_data_handle,
            intptr_t *source_data_handle,
            libcerror_error_t **error ),
     ssize_t (*read_segment_data)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                int segment_file_index,
                uint8_t *segment_data,
                size_t segment_data_size,
                uint8_t read_flags,
                libcerror_error_t **error ),
     ssize_t (*write_segment_data)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                int segment_file_index,
                const uint8_t *segment_data,
                size_t segment_data_size,
                uint8_t write_flags,
                libcerror_error_t **error ),
     off64_t (*seek_segment_offset)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                int segment_file_index,
                off64_t segment_offset,
                int whence,
                libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_initialize";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block value already set.",
		 function );

		return( -1 );
	}
	internal_block = memory_allocate_structure(
	                  libfdata_internal_block_t );

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_block,
	     0,
	     sizeof( libfdata_internal_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block.",
		 function );

		memory_free(
		 internal_block );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_block->segments_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create segments array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_block->mapped_ranges_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create mapped ranges array.",
		 function );

		goto on_error;
	}
	internal_block->timestamp           = libfcache_date_time_get_timestamp();
	internal_block->flags              |= flags;
	internal_block->data_handle         = data_handle;
	internal_block->free_data_handle    = free_data_handle;
	internal_block->clone_data_handle   = clone_data_handle;
	internal_block->read_segment_data   = read_segment_data;
	internal_block->write_segment_data  = write_segment_data;
	internal_block->seek_segment_offset = seek_segment_offset;

	*block = (libfdata_block_t *) internal_block;

	return( 1 );

on_error:
	if( internal_block != NULL )
	{
		if( internal_block->segments_array != NULL )
		{
			libcdata_array_free(
			 &( internal_block->segments_array ),
			 NULL );
		}
		memory_free(
		 internal_block );
	}
	return( -1 );
}

/* Frees the block
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_free(
     libfdata_block_t **block,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_free";
	int result                                = 1;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		internal_block = (libfdata_internal_block_t *) *block;
		*block         = NULL;

		if( libcdata_array_free(
		     &( internal_block->mapped_ranges_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_mapped_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the mapped ranges array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_block->segments_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the segments array.",
			 function );

			result = -1;
		}
		if( ( internal_block->flags & LIBFDATA_FLAG_DATA_HANDLE_MANAGED ) != 0 )
		{
			if( internal_block->data_handle != NULL )
			{
				if( internal_block->free_data_handle != NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: invalid list - missing free data handle function.",
					 function );

					result = -1;
				}
				else if( internal_block->free_data_handle(
					  &( internal_block->data_handle ),
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
		 internal_block );
	}
	return( result );
}

/* Clones (duplicates) the block
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_clone(
     libfdata_block_t **destination_block,
     libfdata_block_t *source_block,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_source_block = NULL;
	intptr_t *destination_data_handle                = NULL;
	static char *function                            = "libfdata_block_clone";

	if( destination_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination block.",
		 function );

		return( -1 );
	}
	if( *destination_block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination block value already set.",
		 function );

		return( -1 );
	}
	if( source_block == NULL )
	{
		*destination_block = NULL;

		return( 1 );
	}
	internal_source_block = (libfdata_internal_block_t *) source_block;

	if( internal_source_block->data_handle != NULL )
	{
		if( internal_source_block->free_data_handle == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid source block - missing free data handle function.",
			 function );

			goto on_error;
		}
		if( internal_source_block->clone_data_handle == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid source block - missing clone data handle function.",
			 function );

			goto on_error;
		}
		if( internal_source_block->clone_data_handle(
		     &destination_data_handle,
		     internal_source_block->data_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create destination data handle.",
			 function );

			goto on_error;
		}
	}
	if( libfdata_block_initialize(
	     destination_block,
	     destination_data_handle,
	     internal_source_block->free_data_handle,
	     internal_source_block->clone_data_handle,
	     internal_source_block->read_segment_data,
	     internal_source_block->write_segment_data,
	     internal_source_block->seek_segment_offset,
	     LIBFDATA_FLAG_DATA_HANDLE_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create destination block.",
		 function );

		goto on_error;
	}
	if( *destination_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing destination block.",
		 function );

		goto on_error;
	}
	destination_data_handle = NULL;

/* TODO clone data ranges */
	return( 1 );

on_error:
	if( *destination_block != NULL )
	{
		libfdata_block_free(
		 destination_block,
		 NULL );
	}
	if( destination_data_handle != NULL )
	{
		internal_source_block->free_data_handle(
		 &destination_data_handle,
		 NULL );
	}
	return( -1 );
}

/* Segment functions
 */

/* Empties the segments
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_empty_segments(
     libfdata_block_t *block,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_empty_segments";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libcdata_array_empty(
	     internal_block->mapped_ranges_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_mapped_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty mapped ranges array.",
		 function );

		return( -1 );
	}
	if( libcdata_array_empty(
	     internal_block->segments_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty segments array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Resizes the segments
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_resize_segments(
     libfdata_block_t *block,
     int number_of_segments,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_resize_segments";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libcdata_array_resize(
	     internal_block->segments_array,
	     number_of_segments,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize segments array.",
		 function );

		return( -1 );
	}
	if( libcdata_array_resize(
	     internal_block->mapped_ranges_array,
	     number_of_segments,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_mapped_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize mapped ranges array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of segments of the block
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_number_of_segments(
     libfdata_block_t *block,
     int *number_of_segments,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_get_number_of_segments";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libcdata_array_get_number_of_entries(
	     internal_block->segments_array,
	     number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from segments array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the offset and size of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_segment_by_index(
     libfdata_block_t *block,
     int segment_index,
     int *segment_file_index,
     off64_t *segment_offset,
     size64_t *segment_size,
     uint32_t *segment_flags,
     libcerror_error_t **error )
{
	libfdata_range_t *segment_data_range      = NULL;
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_get_segment_by_index";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libcdata_array_get_entry_by_index(
	     internal_block->segments_array,
	     segment_index,
	     (intptr_t **) &segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from segments array.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( libfdata_range_get(
	     segment_data_range,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment: %d data range values.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Sets the offset and size of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_set_segment_by_index(
     libfdata_block_t *block,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libcerror_error_t **error )
{
	libfdata_mapped_range_t *mapped_range     = NULL;
	libfdata_range_t *segment_data_range      = NULL;
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_set_segment_by_index";
	off64_t previous_segment_offset           = 0;
	size64_t previous_segment_size            = 0;
	uint32_t previous_segment_flags           = 0;
	int previous_segment_file_index           = 0;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libcdata_array_get_entry_by_index(
	     internal_block->segments_array,
	     segment_index,
	     (intptr_t **) &segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from segments array.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( segment_data_range == NULL )
	{
		if( libfdata_range_initialize(
		     &segment_data_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create segment data range.",
			 function );

			return( -1 );
		}
		if( libfdata_mapped_range_initialize(
		     &mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create mapped range.",
			 function );

			libfdata_range_free(
			 &segment_data_range,
			 NULL );

			return( -1 );
		}
		if( libcdata_array_set_entry_by_index(
		     internal_block->segments_array,
		     segment_index,
		     (intptr_t *) segment_data_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set entry: %d in segments array.",
			 function,
			 segment_index );

			libfdata_mapped_range_free(
			 &mapped_range,
			 NULL );
			libfdata_range_free(
			 &segment_data_range,
			 NULL );

			return( -1 );
		}
		if( libcdata_array_set_entry_by_index(
		     internal_block->mapped_ranges_array,
		     segment_index,
		     (intptr_t *) mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set entry: %d in mapped ranges array.",
			 function,
			 segment_index );

			libcdata_array_set_entry_by_index(
			 internal_block->segments_array,
			 segment_index,
			 NULL,
			 NULL );
			libfdata_mapped_range_free(
			 &mapped_range,
			 NULL );
			libfdata_range_free(
			 &segment_data_range,
			 NULL );

			return( -1 );
		}
	}
	else
	{
		if( libcdata_array_get_entry_by_index(
		     internal_block->mapped_ranges_array,
		     segment_index,
		     (intptr_t **) &mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from mapped ranges array.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( mapped_range == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing mapped range: %d\n",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_range_get(
		     segment_data_range,
		     &previous_segment_file_index,
		     &previous_segment_offset,
		     &previous_segment_size,
		     &previous_segment_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d data range values.",
			 function,
			 segment_index );

			return( -1 );
		}
		internal_block->data_size -= previous_segment_size;
	}
	if( libfdata_range_set(
	     segment_data_range,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set segment data range values.",
		 function );

		return( -1 );
	}
	internal_block->data_size += segment_size;
	internal_block->flags     |= LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES;

	return( 1 );
}

/* Appends a segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_append_segment(
     libfdata_block_t *block,
     int *segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	libfdata_mapped_range_t *mapped_range     = NULL;
	libfdata_range_t *segment_data_range      = NULL;
	static char *function                     = "libfdata_block_append_segment";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libfdata_range_initialize(
	     &segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create segment data range.",
		 function );

		goto on_error;
	}
	if( libfdata_mapped_range_initialize(
	     &mapped_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create mapped range.",
		 function );

		goto on_error;
	}
	if( libfdata_range_set(
	     segment_data_range,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set segment data range values.",
		 function );

		goto on_error;
	}
	if( libfdata_mapped_range_set(
	     mapped_range,
	     (off64_t) internal_block->data_size,
	     segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set mapped range values.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_block->segments_array,
	     segment_index,
	     (intptr_t *) segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append data range to segments array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_block->mapped_ranges_array,
	     segment_index,
	     (intptr_t *) mapped_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append mapped range to array.",
		 function );

		libcdata_array_set_entry_by_index(
		 internal_block->segments_array,
		 segment_index,
		 NULL,
		 NULL );

		goto on_error;
	}
	internal_block->data_size += segment_size;

	return( 1 );

on_error:
	if( mapped_range != NULL )
	{
		libfdata_mapped_range_free(
		 &mapped_range,
		 NULL );
	}
	if( segment_data_range != NULL )
	{
		libfdata_range_free(
		 &segment_data_range,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the maximum segment size
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_maximum_segment_size(
     libfdata_block_t *block,
     size64_t *maximum_segment_size,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_get_maximum_segment_size";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( maximum_segment_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid maximum segment size.",
		 function );

		return( -1 );
	}
	*maximum_segment_size = internal_block->maximum_segment_size;

	return( 1 );
}

/* Sets the maximum segment size
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_set_maximum_segment_size(
     libfdata_block_t *block,
     size64_t maximum_segment_size,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_set_maximum_segment_size";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( maximum_segment_size > (size64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid maximum segment size value exceeds maximum.",
		 function );

		return( -1 );
	}
	internal_block->maximum_segment_size = maximum_segment_size;

	return( 1 );
}

/* Mapped range functions
 */

/* Calculates the mapped ranges
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_calculate_mapped_ranges(
     libfdata_internal_block_t *internal_block,
     libcerror_error_t **error )
{
	libfdata_mapped_range_t *mapped_range = NULL;
	libfdata_range_t *segment_data_range  = NULL;
	static char *function                 = "libfdata_block_calculate_mapped_ranges";
	off64_t mapped_range_offset           = 0;
	off64_t segment_offset                = 0;
	size64_t segment_size                 = 0;
	uint32_t segment_flags                = 0;
	int number_of_segments                = 0;
	int segment_file_index                = 0;
	int segment_index                     = 0;

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block ",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_block->segments_array,
	     &number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from segments array.",
		 function );

		return( -1 );
	}
	for( segment_index = 0;
	     segment_index < number_of_segments;
	     segment_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_block->segments_array,
		     segment_index,
		     (intptr_t **) &segment_data_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from segments array.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libcdata_array_get_entry_by_index(
		     internal_block->mapped_ranges_array,
		     segment_index,
		     (intptr_t **) &mapped_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from mapped ranges array.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_range_get(
		     segment_data_range,
		     segment_file_index,
		     segment_offset,
		     segment_size,
		     segment_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d data range values.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_mapped_range_set(
		     mapped_range,
		     mapped_range_offset,
		     segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set mapped range: %d values.",
			 function,
			 segment_index );

			return( -1 );
		}
		mapped_range_offset += (off64_t) segment_size;
	}
	internal_block->timestamp = libfcache_date_time_get_timestamp();
	internal_block->flags    &= ~( LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES );

	return( 1 );
}

/* Data functions
 */

/* Retrieves the data offset
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_data_offset(
     libfdata_block_t *block,
     off64_t *data_offset,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_get_data_offset";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( data_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data offset.",
		 function );

		return( -1 );
	}
	*data_offset = internal_block->data_offset;

	return( 1 );
}

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_data_size(
     libfdata_block_t *block,
     size64_t *data_size,
     libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_get_data_size";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

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
	*data_size = internal_block->data_size;

	return( 1 );
}

/* Check if the data has been cached as a single cache value
 * The data_buffer value is set if successful
 * Returns 1 if successful, 0 if not or -1 on error
 */
int libfdata_block_get_cached_data_buffer(
     libfdata_internal_block_t *interal_block,
     libfcache_cache_value_t *cache_value,
     libfdata_buffer_t **data_buffer,
     libcerror_error_t **error )
{
	static char *function        = "libfdata_block_get_cached_data_buffer";
        off64_t cache_value_offset   = (off64_t) -1;
	size_t data_size             = 0;
	time_t cache_value_timestamp = 0;
        int cache_value_file_index   = -1;
	int number_of_cache_values   = 0;

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( data_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data buffer.",
		 function );

		return( -1 );
	}
	*data_buffer = NULL;

	if( cache_value == NULL )
	{
		return( 0 );
	}
	if( libfcache_cache_get_number_of_cache_values(
	     cache,
	     &number_of_cache_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of cache values.",
		 function );

		goto on_error;
	}
	if( number_of_cache_values != 1 )
	{
		return( 0 );
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
	if( ( cache_value_file_index != 0 )
	 || ( cache_value_offset != 0 )
	 || ( cache_value_timestamp != internal_block->timestamp ) )
	{
		return( 0 );
	}
	if( libfcache_cache_value_get_value(
	     cache_value,
	     (intptr_t **) data_buffer,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data buffer from cache value: 0.",
		 function );

		goto on_error;
	}
	if( data_buffer == NULL )
	{
		return( 0 );
	}
	if( libfdata_buffer_get_data_size(
	     data_buffer,
	     &data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data size.",
		 function );

		goto on_error;
	}
	if( internal_block->data_size != (size64_t) data_size )
	{
		*data_buffer = NULL;

		return( 0 );
	}
	return( 1 );

on_error:
	*data_buffer = NULL;

	return( -1 );
}

/* Reads the data into a single data buffer
 * This function cannot handle data of a size > SSIZE_MAX
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_read_data_buffer(
     libfdata_internal_block_t *interal_block,
     libfdata_buffer_t **data_buffer,
     libcerror_error_t **error )
{
	libfdata_range_t *segment_data_range = NULL;
	uint8_t *data                        = NULL;
	static char *function                = "libfdata_block_read_data_buffer";
	off64_t segment_offset               = 0;
	size64_t segment_size                = 0;
	size_t data_offset                   = 0;
	size_t data_size                     = 0;
	ssize_t read_count                   = 0;
	uint32_t segment_flags               = 0;
	int number_of_segments               = 0;
	int segment_file_index               = 0;
	int segment_index                    = 0;

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( internal_block->read_segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block - missing read segment data function.",
		 function );

		return( -1 );
	}
	if( internal_block->seek_segment_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block - missing seek segment offset function.",
		 function );

		return( -1 );
	}
	if( internal_block->data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data block size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data buffer.",
		 function );

		return( -1 );
	}
	if( *data_buffer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data buffer value already set.",
		 function );

		return( -1 );
	}
	if( libfdata_buffer_initialize(
	     data_buffer,
	     (size_t) internal_block->data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data buffer.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_get_data(
	     data_buffer,
	     &data,
	     &data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data from data buffer.",
		 function );

		goto on_error;
	}
	if( data_buffer_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing data buffer data.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     internal_block->segments_array,
	     number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from segments array.",
		 function );

		goto on_error;
	}
	/* Read all the segment data into the data buffer
	 */
	for( segment_index = 0;
	     segment_index < number_of_segments;
	     segment_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_block->segments_array,
		     segment_index,
		     (intptr_t **) &segment_data_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from segments array.",
			 function,
			 segment_index );

			goto on_error;
		}
		if( libfdata_range_get(
		     segment_data_range,
		     &segment_file_index,
		     &segment_offset,
		     &segment_size,
		     &segment_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d data range values.",
			 function,
			 segment_index );

			goto on_error;
		}
/* TODO check if segment size is in bounds
		if( data_size != (size_t) segment_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data size value out of bounds.",
			 function );

			goto on_error;
		}
*/
		if( internal_block->seek_segment_offset(
		     internal_block->data_handle,
		     file_io_handle,
		     segment_file_index,
		     segment_offset,
		     SEEK_SET,
		     error ) != segment_offset )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek segment offset: %" PRIi64 " in segment file: %d.",
			 function,
			 segment_offset,
			 segment_file_index );

			goto on_error;
		}
		read_count = internal_block->read_segment_data(
			      internal_block->data_handle,
			      file_io_handle,
			      segment_file_index,
			      &( data[ data_offset ] ),
			      (size_t) segment_size,
			      0,
			      error );

		if( read_count != (ssize_t) segment_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read segment data: %d from segment file: %d.",
			 function,
			 segment_index,
			 segment_file_index );

			goto on_error;
		}
		data_offset += (size_t) read_count;
	}
	return( 1 );

on_error:
	if( data_buffer != NULL )
	{
		libfdata_buffer_free(
		 &data_buffer,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the data of the block
 * The function caches all the data segments of the block into a single buffer
 * This function cannot handle data of a size > SSIZE_MAX
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_data(
     libfdata_block_t *block,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfcache_cache_value_t *cache_value      = NULL;
	libfdata_buffer_t *data_buffer            = NULL;
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_get_data";
	off64_t segment_offset                    = 0;
	size64_t segment_size                     = 0;
	size_t data_buffer_size                   = 0;
	uint32_t segment_flags                    = 0;
	int number_of_cache_values                = 0;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libfdata_range_get(
	     segment_data_range,
	     &segment_file_index,
	     &segment_offset,
	     &segment_size,
	     &segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment: %d data range values.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( ( read_flags & LIBFDATA_READ_FLAG_IGNORE_CACHE ) != 0 )
	{
		result = libfdata_block_get_cached_segment_data(
			  internal_block,
			  segment_index,
		          segment_file_index,
		          segment_offset,
		          segment_size,
		          segment_flags,
			  &cache_value,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cached segment data.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			/* Check if all data has been cached in a single cache value
			 */
			result = libfdata_block_get_cached_data_buffer(
				  internal_block,
				  cache_value,
				  &data_buffer,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve cached single data buffer.",
				 function );

				return( -1 );
			}
		}
	}
	/* Read all the data in a single cache value
	 */
	if( result == 0 )
	{
		if( libfcache_cache_clear(
		     cache,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to clear cache.",
			 function );

			return( -1 );
		}
		data_buffer = NULL;

		if( libfdata_block_read_data_buffer(
		     internal_block,
		     &data_buffer,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data as single data buffer.",
			 function );

			return( -1 );
		}
		if( libfcache_cache_set_value_by_index(
		     cache,
		     0,
		     0,
		     0,
		     internal_block->timestamp,
		     (intptr_t *) data_buffer,
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_buffer_free,
		     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set value in cache entry: 0.",
			 function );

			libfdata_buffer_free(
			 &data_buffer,
			 NULL );

			return( -1 );
		}
	}
	if( libfdata_buffer_get_data(
	     data_buffer,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data from data buffer.",
		 function );

		data_buffer = NULL;

		return( -1 );
	}
	return( 1 );
}

/* Segment data functions
 */

/* Check if the segment data has been cached
 * Returns 1 if successful, 0 if not or -1 on error
 */
int libfdata_block_get_cached_segment_data(
     libfdata_internal_block_t *interal_block,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libfcache_cache_value_t **cache_value,
     libcerror_error_t **error )
{
	libfcache_cache_value_t *cache_value = NULL;
	static char *function                = "libfdata_block_get_cached_segment_data";
        off64_t cache_value_offset           = (off64_t) -1;
	time_t cache_value_timestamp         = 0;
	int cache_entry_index                = -1;
        int cache_value_file_index           = -1;
	int number_of_cache_entries          = 0;
	int segment_file_index               = 0;

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( cache_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache value.",
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
	cache_entry_index = libfdata_block_calculate_cache_entry_index(
	                     segment_index,
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
	if( cache_value == NULL )
	{
		return( 0 );
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
	if( ( cache_value_file_index != segment_file_index )
	 || ( cache_value_offset != segment_offset )
	 || ( cache_value_timestamp != internal_block->timestamp ) )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: cache: 0x%08" PRIjx " miss (%d out of %d)\n",
			 function,
			 (intptr_t) cache,
			 cache_entry_index,
			 number_of_cache_entries );
		}
#endif
		*cache_value = NULL;

		return( 0 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: cache: 0x%08" PRIjx " hit (%d out of %d)\n",
		 function,
		 (intptr_t) cache,
		 cache_entry_index,
		 number_of_cache_entries );
	}
#endif
	return( 1 );
}

/* Reads the segment data into a buffer
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_read_segment_data(
     libfdata_internal_block_t *interal_block,
     intptr_t *file_io_handle,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     uint8_t *segment_data,
     size_t segment_data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	static char *function = "libfdata_block_read_segment_data";

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal block.",
		 function );

		return( -1 );
	}
	if( internal_block->read_segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block - missing read segment data function.",
		 function );

		return( -1 );
	}
	if( internal_block->seek_segment_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block - missing seek segment offset function.",
		 function );

		return( -1 );
	}
	if( (size64_t) segment_data_size != segment_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading segment data at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIu64 "\n",
		 function,
		 segment_offset,
		 segment_offset,
		 segment_size );
	}
#endif
	if( internal_block->seek_segment_offset(
	     internal_block->data_handle,
	     file_io_handle,
	     segment_file_index,
	     segment_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset: %" PRIi64 " in segment: %d.",
		 function,
		 segment_offset,
		 segment_index );

		return( -1 );
	}
	read_count = internal_block->read_segment_data(
		      internal_block->data_handle,
		      file_io_handle,
		      segment_file_index,
		      segment_data,
		      segment_data_size,
		      read_flags,
		      error );

	if( read_count != (ssize_t) segment_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data from segment: %d.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Reads the segment data into a data buffer
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_read_segment_data_buffer(
     libfdata_internal_block_t *interal_block,
     intptr_t *file_io_handle,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libfdata_block_read_segment_data_buffer";
	size_t data_size      = 0;

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal block.",
		 function );

		return( -1 );
	}
	if( segment_size > (size64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid segment size value exceeds maximum.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_initialize(
	     &data_buffer,
	     (size_t) segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data buffer.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_get_data(
	     data_buffer,
	     &data,
	     &data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data from data buffer.",
		 function );

		goto on_error;
	}
	if( libfdata_block_read_segment_data(
	     internal_block->data_handle,
	     file_io_handle,
	     segment_file_index,
	     segment_file_index,
	     segment_offset,
	     segment_size,
	     segment_flags,
	     data,
	     data_size,
	     read_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment: %d data.",
		 function,
		 segment_index );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_buffer != NULL )
	{
		libfdata_buffer_free(
		 &data_buffer,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the segment data and size of a specific segment
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_segment_data(
     libfdata_block_t *block,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t **segment_data,
     size_t *segment_data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfcache_cache_value_t *cache_value      = NULL;
	libfdata_buffer_t *data_buffer            = NULL;
	libfdata_mapped_range_t *mapped_range     = NULL;
	libfdata_range_t *segment_data_range      = NULL;
	libfcache_cache_value_t *cache_value      = NULL;
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_get_segment_data";
	off64_t mapped_range_offset               = 0;
	off64_t segment_offset                    = 0;
	size64_t mapped_range_size                = 0;
	size64_t segment_size                     = 0;
	size_t data_buffer_size                   = 0;
	uint32_t segment_flags                    = 0;
	int number_of_cache_values                = 0;
	int segment_file_index                    = 0;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment data.",
		 function );

		return( -1 );
	}
	if( segment_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment data size.",
		 function );

		return( -1 );
	}
	if( ( internal_block->flags & LIBFDATA_FLAG_CALCULATE_MAPPED_RANGES ) != 0 )
	{
		if( libfdata_block_calculate_mapped_ranges(
		     internal_block,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to calculate mapped ranges.",
			 function );

			return( -1 );
		}
	}
	if( libcdata_array_get_entry_by_index(
	     internal_block->segments_array,
	     segment_index,
	     (intptr_t **) &segment_data_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from segments array.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( libfdata_range_get(
	     segment_data_range,
	     &segment_file_index,
	     &segment_offset,
	     &segment_size,
	     &segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment: %d data range values.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( ( read_flags & LIBFDATA_READ_FLAG_IGNORE_CACHE ) != 0 )
	{
		result = libfdata_block_get_cached_segment_data(
			  internal_block,
			  segment_index,
		          segment_file_index,
		          segment_offset,
		          segment_size,
		          segment_flags,
			  &cache_value,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cached segment data.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			/* Check if all data has been cached in a single cache value
			 */
			result = libfdata_block_get_cached_data_buffer(
				  internal_block,
				  cache_value,
				  &data_buffer,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve cached single data buffer.",
				 function );

				return( -1 );
			}
			else if( result != 0 )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_block->mapped_ranges_array,
				     segment_index,
				     (intptr_t **) &mapped_range,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve entry: %d from mapped ranges array.",
					 function,
					 segment_index );

					return( -1 );
				}
				if( libfdata_mapped_range_get(
				     mapped_range,
				     &mapped_range_offset,
				     &mapped_range_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve mapped range: %d values.",
					 function,
					 segment_index );

					return( -1 );
				}
				if( mapped_range_offset > (off64_t) SSIZE_MAX )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid mapped range offset value exceeds maximum.",
					 function );

					return( -1 );
				}
				if( libfdata_buffer_get_data_at_offset(
				     data_buffer,
				     (size_t) mapped_range_offset,
				     data,
				     data_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve data from data buffer at offset: %" PRIi64 ".",
					 function,
					 mapped_range_offset );

					return( -1 );
				}
				if( mapped_range_size > (off64_t) SSIZE_MAX )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid mapped range size value exceeds maximum.",
					 function );

					return( -1 );
				}
				*segment_data_size = (size_t) mapped_range_offset;
			}
			else
			{
				if( libfcache_cache_value_get_value(
				     cache_value,
				     (intptr_t **) &data_buffer,
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
				if( libfdata_buffer_get_data(
				     data_buffer,
				     data,
				     data_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve data from data buffer.",
					 function );

					return( -1 );
				}
				result = 1;
			}
		}
	}
	if( result == 0 )
	{
		if( libfdata_block_read_segment_data_buffer(
		     internal_block,
		     segment_index,
		     segment_file_index,
		     segment_offset,
		     segment_size,
		     segment_flags,
		     &data_buffer,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to retrieve read segment: %d data buffer.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_set_element_value(
		     segment,
		     cache,
		     (intptr_t *) data_buffer,
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_buffer_free,
		     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set element value in list element.",
			 function );

			libfdata_buffer_free(
			 &data_buffer,
			 NULL );

			return( -1 );
		}
		if( libfdata_buffer_get_data(
		     data_buffer,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* TODO */

#include "libfdata_list.h"
#include "libfdata_list_element.h"

/* Retrieves the segment data and size at a certain offset
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_segment_data_at_offset(
     libfdata_block_t *block,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     off64_t data_offset,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer            = NULL;
	libfcache_cache_value_t *cache_value       = NULL;
	libfdata_internal_block_t *internal_block = NULL;
	libfdata_list_element_t *segment          = NULL;
	static char *function                     = "libfdata_block_get_segment_data_at_offset";
	off64_t segment_offset                    = 0;
	size64_t segment_size                     = 0;
	size_t data_buffer_size                   = 0;
	size_t segment_data_offset                = 0;
	uint32_t segment_flags                    = 0;
	int number_of_cache_values                = 0;
	int segment_file_index                    = 0;
	int segment_index                         = 0;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libfdata_list_get_element_index_at_value_offset(
	     internal_block->segments_list,
	     data_offset,
	     &segment_index,
	     &segment_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index at offset: %" PRIi64 ".",
		 function,
		 data_offset );

		return( -1 );
	}
	/* Check if all data has been cached in a single cache value
	 */
	if( libfcache_cache_get_number_of_cache_values(
	     cache,
	     &number_of_cache_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of cache values.",
		 function );

		return( -1 );
	}
	if( number_of_cache_values == 1 )
	{
		if( libfcache_cache_get_value_by_index(
		     cache,
		     0,
		     &cache_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( cache_value != NULL )
	{
		if( libfcache_cache_value_get_value(
		     cache_value,
		     (intptr_t **) &data_buffer,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data buffer from cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( data_buffer != NULL )
	{
		if( libfdata_buffer_get_data_size(
		     data_buffer,
		     &data_buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data buffer size.",
			 function );

			return( -1 );
		}
	}
	/* Check if all the data has been cached in a single cache value
	 */
	if( internal_block->data_size == (size64_t) data_buffer_size )
	{
		if( data_offset > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid data offset value exceeds maximum.",
			 function );

			return( -1 );
		}
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
		if( libfdata_list_get_element_by_index(
		     internal_block->segments_list,
		     segment_index,
		     &segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     segment,
		     &segment_file_index,
		     &segment_offset,
		     &segment_size,
		     &segment_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     (size_t) data_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIi64 ".",
			 function,
			 data_offset );

			return( -1 );
		}
		if( segment_data_offset > segment_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: segment data offset value out of bounds.",
			 function );

			return( -1 );
		}
		if( ( segment_size - segment_data_offset ) > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid segment size value out of bounds.",
			 function );

			return( -1 );
		}
		*data_size = (size_t) ( segment_size - segment_data_offset );
	}
	else
	{
		if( libfdata_list_get_element_value_by_index(
		     internal_block->segments_list,
		     file_io_handle,
		     cache,
		     segment_index,
		     (intptr_t **) &data_buffer,
		     read_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element value: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     segment_data_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIzd ".",
			 function,
			 segment_data_offset );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the segment data and size at a specific value index
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_get_segment_data_at_value_index(
     libfdata_block_t *block,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int value_index,
     size_t value_size,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfcache_cache_value_t *cache_value      = NULL;
	libfdata_buffer_t *data_buffer            = NULL;
	libfdata_internal_block_t *internal_block = NULL;
	libfdata_list_element_t *segment          = NULL;
	static char *function                     = "libfdata_block_get_segment_data_at_value_index";
	off64_t segment_offset                    = 0;
	off64_t segment_value_offset              = 0;
	size64_t segment_size                     = 0;
	size_t data_buffer_size                   = 0;
	size_t segment_data_offset                = 0;
	uint32_t segment_flags                    = 0;
	int number_of_cache_values                = 0;
	int segment_file_index                    = 0;
	int segment_index                         = 0;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( libfdata_list_get_element_index_at_value_index(
	     internal_block->segments_list,
	     value_index,
	     value_size,
	     &segment_index,
	     &segment_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index at value index: %d for value size: %" PRIzd ".",
		 function,
		 value_index,
		 value_size );

		return( -1 );
	}
	/* Check if all data has been cached in a single cache value
	 */
	if( libfcache_cache_get_number_of_cache_values(
	     cache,
	     &number_of_cache_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of cache values.",
		 function );

		return( -1 );
	}
	if( number_of_cache_values == 1 )
	{
		if( libfcache_cache_get_value_by_index(
		     cache,
		     0,
		     &cache_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( cache_value != NULL )
	{
		if( libfcache_cache_value_get_value(
		     cache_value,
		     (intptr_t **) &data_buffer,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data buffer from cache value: 0.",
			 function );

			return( -1 );
		}
	}
	if( data_buffer != NULL )
	{
		if( libfdata_buffer_get_data_size(
		     data_buffer,
		     &data_buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data buffer size.",
			 function );

			return( -1 );
		}
	}
	/* Check if all the data has been cached in a single cache value
	 */
	if( internal_block->data_size == (size64_t) data_buffer_size )
	{
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
		if( libfdata_list_get_element_by_index(
		     internal_block->segments_list,
		     segment_index,
		     &segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_get_data_range(
		     segment,
		     &segment_file_index,
		     &segment_offset,
		     &segment_size,
		     &segment_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_list_element_get_value_offset(
		     segment,
		     &segment_value_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d data offset.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( segment_value_offset > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid segment value offset value exceeds maximum.",
			 function );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     (size_t) segment_value_offset + segment_data_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIi64 ".",
			 function,
			 segment_value_offset + segment_data_offset );

			return( -1 );
		}
		if( segment_data_offset > segment_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: segment data offset value out of bounds.",
			 function );

			return( -1 );
		}
		if( ( segment_size - segment_data_offset ) > (off64_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid segment size value out of bounds.",
			 function );

			return( -1 );
		}
		*data_size = (size_t) ( segment_size - segment_data_offset );
	}
	else
	{
		if( libfdata_list_get_element_value_by_index(
		     internal_block->segments_list,
		     file_io_handle,
		     cache,
		     segment_index,
		     (intptr_t **) &data_buffer,
		     read_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element value: %d from segments list.",
			 function,
			 segment_index );

			return( -1 );
		}
		if( libfdata_buffer_get_data_at_offset(
		     data_buffer,
		     segment_data_offset,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data from data buffer at offset: %" PRIzd ".",
			 function,
			 segment_data_offset );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the reference and size of the data of a specific segment
 *
 * If the flag LIBFDATA_SEGMENT_DATA_FLAG_MANAGED is set the block
 * takes over management of the data and the data is freed when
 * no longer needed. If the flag is not set the block makes a copy of the data.
 *
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_set_segment_data(
     libfdata_block_t *block,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t *data,
     size_t data_size,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer            = NULL;
	libfdata_internal_block_t *internal_block = NULL;
	libfdata_list_element_t *segment          = NULL;
	static char *function                     = "libfdata_block_set_segment_data";
	off64_t segment_offset                    = 0;
	size64_t segment_size                     = 0;
	uint32_t segment_flags                    = 0;
	int segment_file_index                    = 0;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfdata_list_get_element_by_index(
	     internal_block->segments_list,
	     segment_index,
	     &segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element: %d from segments list.",
		 function,
		 segment_index );

		goto on_error;
	}
	if( libfdata_list_element_get_data_range(
	     segment,
	     &segment_file_index,
	     &segment_offset,
	     &segment_size,
	     &segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment: %d.",
		 function,
		 segment_index );

		goto on_error;
	}
	if( data_size != (size_t) segment_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_initialize(
	     &data_buffer,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data buffer.",
		 function );

		goto on_error;
	}
	if( libfdata_buffer_set_data(
	     data_buffer,
	     data,
	     data_size,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data buffer data.",
		 function );

		goto on_error;
	}
	if( libfdata_list_set_element_value_by_index(
	     internal_block->segments_list,
	     cache,
	     segment_index,
	     (intptr_t *) data_buffer,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfdata_buffer_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set element value: %d in segments list.",
		 function,
		 segment_index );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_buffer != NULL )
	{
		libfdata_buffer_free(
		 &data_buffer,
		 NULL );
	}
	return( -1 );
}

#ifdef TODO

/* Reads the element data into a data buffer
 * Returns 1 if successful or -1 on error
 */
int libfdata_block_read_element_data(
     libfdata_internal_block_t *internal_block,
     intptr_t *file_io_handle,
     libfdata_list_element_t *segment,
     libfcache_cache_t *cache,
     int data_range_file_index,
     off64_t data_range_offset,
     size64_t data_range_size,
     uint32_t data_range_flags,
     uint8_t read_flags,
     libcerror_error_t **error )
{
	libfdata_buffer_t *data_buffer = NULL;
	uint8_t *data_buffer_data      = NULL;
	static char *function          = "libfdata_block_read_element_data";
	size_t data_buffer_size        = 0;
	ssize_t read_count             = 0;
	int segment_index              = 0;

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal block.",
		 function );

		return( -1 );
	}
	if( data_range_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid segment size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfdata_list_element_get_element_index(
	     segment,
	     &segment_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element index from list element.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_buffer != NULL )
	{
		libfdata_buffer_free(
		 &data_buffer,
		 NULL );
	}
	return( -1 );
}

#endif

/* Reads data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfdata_block_read_buffer(
         libfdata_block_t *block,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         uint8_t *buffer,
         size_t buffer_size,
         uint8_t read_flags,
         libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	uint8_t *segment_data                     = NULL;
	static char *function                     = "libfdata_block_read_buffer";
	size_t buffer_offset                      = 0;
	size_t read_size                          = 0;
	size_t segment_data_size                  = 0;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_block->data_offset < 0 )
	 || ( internal_block->data_offset >= (off64_t) internal_block->data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block - data offset: %" PRIi64 " value out of bounds: 0 - %" PRIu64 ".",
		 function,
		 internal_block->data_offset,
		 internal_block->data_size );

		return( -1 );
	}
	if( (off64_t) ( internal_block->data_offset + buffer_size ) > (off64_t) internal_block->data_size )
	{
		buffer_size = (size_t) ( internal_block->data_size - internal_block->data_offset );
	}
	while( buffer_size > 0 )
	{
		if( libfdata_block_get_segment_data(
		     block,
		     file_io_handle,
		     cache,
		     internal_block->segment_index,
		     &segment_data,
		     &segment_data_size,
		     read_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment data at offset: %" PRIi64 ".",
			 function,
			 internal_block->data_offset );

			return( -1 );
		}
		if( segment_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing segment data.",
			 function );

			return( -1 );
		}
		read_size = segment_data_size - internal_block->segment_data_offset;

		if( read_size > buffer_size )
		{
			read_size = buffer_size;
		}
		if( memory_copy(
		     &( buffer[ buffer_offset ] ),
		     &( segment_data[ internal_block->segment_data_offset ] ),
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy segment data to buffer.",
			 function );

			return( -1 );
		}
		internal_block->data_offset += read_size;

		if( ( internal_block->segment_data_offset + read_size ) == segment_data_size )
		{
			internal_block->segment_index      += 1;
			internal_block->segment_data_offset = 0;
		}
		else
		{
			internal_block->segment_data_offset += read_size;
		}
		buffer_size   -= read_size;
		buffer_offset += read_size;
	}
	return( (size_t) buffer_offset );
}

/* Writes data in the buffer to the current offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfdata_block_write_buffer(
         libfdata_block_t *block,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         const uint8_t *buffer,
         size_t buffer_size,
         uint8_t write_flags,
         libcerror_error_t **error )
{
/* TODO implement */
	return( -1 );
}

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libfdata_block_seek_offset(
         libfdata_block_t *block,
         intptr_t *file_io_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libfdata_internal_block_t *internal_block = NULL;
	static char *function                     = "libfdata_block_seek_offset";
	size_t segment_data_offset                = 0;
	int segment_index                         = 0;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libfdata_internal_block_t *) block;

	if( internal_block->data_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block - data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_block->data_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) internal_block->data_size;
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: seeking offset: %" PRIi64 ".\n",
		 function,
		 offset );
	}
#endif
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( offset < (off64_t) internal_block->data_size )
	{
		if( libfdata_list_get_element_index_at_value_offset(
		     internal_block->segments_list,
		     offset,
		     &segment_index,
		     &segment_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element index at offset %" PRIi64 ".",
			 function,
			 offset );

			return( -1 );
		}
		internal_block->segment_index       = segment_index;
		internal_block->segment_data_offset = segment_data_offset;
	}
	internal_block->data_offset = offset;

	return( offset );
}

