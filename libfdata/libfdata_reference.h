/*
 * Data reference functions
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

#if !defined( _LIBFDATA_INTERNAL_REFERENCE_H )
#define _LIBFDATA_INTERNAL_REFERENCE_H

#include <common.h>
#include <types.h>

#include "libfdata_extern.h"
#include "libfdata_libcerror.h"
#include "libfdata_libfcache.h"
#include "libfdata_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdata_internal_reference libfdata_internal_reference_t;

struct libfdata_internal_reference
{
	/* The data handle
	 */
	intptr_t *data_handle;

	/* The flags
	 */
	uint8_t flags;

	/* Function to free the data handle
	 */
	int (*free_data_handle)(
	     intptr_t **data_handle,
	     libcerror_error_t **error );

	/* Function to clone the data handle
	 */
	int (*clone_data_handle)(
	     intptr_t **destination_data_handle,
	     intptr_t *source_data_handle,
	     libcerror_error_t **error );

	/* Function to retrieve the number of segments
	 */
	int (*get_number_of_segments)(
	       intptr_t *data_handle,
	       int *number_of_segments,
	       libcerror_error_t **error );

	/* Function to retrieve the size
	 */
	int (*get_size)(
	       intptr_t *data_handle,
	       size64_t *size,
	       libcerror_error_t **error );

	/* Function to retrieve the data
	 */
	int (*get_data)(
	       intptr_t *data_handle,
	       intptr_t *file_io_handle,
	       libfcache_cache_t *cache,
	       uint8_t **data,
	       size_t *data_size,
	       libcerror_error_t **error );

	/* Function to retrieve the segment data
	 */
	int (*get_segment_data)(
	       intptr_t *data_handle,
	       intptr_t *file_io_handle,
	       libfcache_cache_t *cache,
	       int segment_index,
	       uint8_t **data,
	       size_t *data_size,
	       uint8_t read_flags,
	       libcerror_error_t **error );

	/* Function to retrieve the segment data at a specific offset
	 */
	int (*get_segment_data_at_offset)(
	       intptr_t *data_handle,
	       intptr_t *file_io_handle,
	       libfcache_cache_t *cache,
	       off64_t data_offset,
	       uint8_t **data,
	       size_t *data_size,
	       uint8_t read_flags,
	       libcerror_error_t **error );

	/* Function to retrieve the segment data at a specific value index
	 */
	int (*get_segment_data_at_value_index)(
	       intptr_t *data_handle,
	       intptr_t *file_io_handle,
	       libfcache_cache_t *cache,
	       int value_index,
	       size_t value_size,
	       uint8_t **data,
	       size_t *data_size,
	       uint8_t read_flags,
	       libcerror_error_t **error );

	/* Function to read a buffer
	 */
	ssize_t (*read_buffer)(
	           intptr_t *data_handle,
	           intptr_t *file_io_handle,
	           libfcache_cache_t *cache,
	           uint8_t *buffer,
	           size_t buffer_size,
	           libcerror_error_t **error );

	/* Function to seek an offset
	 */
	off64_t (*seek_offset)(
	           intptr_t *data_handle,
	           off64_t offset,
	           int whence,
	           libcerror_error_t **error );
};

LIBFDATA_EXTERN \
int libfdata_reference_initialize(
     libfdata_reference_t **reference,
     intptr_t *data_handle,
     int (*free_data_handle)(
            intptr_t **data_handle,
            libcerror_error_t **error ),
     int (*clone_data_handle)(
            intptr_t **destination_data_handle,
            intptr_t *source_data_handle,
            libcerror_error_t **error ),
     int (*get_number_of_segments)(
            intptr_t *data_handle,
            int *number_of_segments,
            libcerror_error_t **error ),
     int (*get_size)(
            intptr_t *data_handle,
            size64_t *size,
            libcerror_error_t **error ),
     int (*get_data)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfcache_cache_t *cache,
            uint8_t **data,
            size_t *data_size,
            libcerror_error_t **error ),
     int (*get_segment_data)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfcache_cache_t *cache,
            int segment_index,
            uint8_t **data,
            size_t *data_size,
            uint8_t read_flags,
            libcerror_error_t **error ),
     int (*get_segment_data_at_offset)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfcache_cache_t *cache,
            off64_t data_offset,
            uint8_t **data,
            size_t *data_size,
            uint8_t read_flags,
            libcerror_error_t **error ),
     int (*get_segment_data_at_value_index)(
            intptr_t *data_handle,
            intptr_t *file_io_handle,
            libfcache_cache_t *cache,
            int value_index,
            size_t value_size,
            uint8_t **data,
            size_t *data_size,
            uint8_t read_flags,
            libcerror_error_t **error ),
     ssize_t (*read_buffer)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                libfcache_cache_t *cache,
                uint8_t *buffer,
                size_t buffer_size,
                libcerror_error_t **error ),
     off64_t (*seek_offset)(
                intptr_t *data_handle,
                off64_t offset,
                int whence,
                libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_reference_free(
     libfdata_reference_t **reference,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_reference_clone(
     libfdata_reference_t **destination_reference,
     libfdata_reference_t *source_reference,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_reference_get_data_handle(
     libfdata_reference_t *reference,
     intptr_t **data_handle,
     libcerror_error_t **error );

/* Segment functions
 */
LIBFDATA_EXTERN \
int libfdata_reference_get_number_of_segments(
     libfdata_reference_t *reference,
     int *number_of_segments,
     libcerror_error_t **error );

/* Data functions
 */
LIBFDATA_EXTERN \
int libfdata_reference_get_size(
     libfdata_reference_t *reference,
     size64_t *size,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_reference_get_data(
     libfdata_reference_t *reference,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_reference_get_segment_data(
     libfdata_reference_t *reference,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_reference_get_segment_data_at_offset(
     libfdata_reference_t *reference,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     off64_t data_offset,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_reference_get_segment_data_at_value_index(
     libfdata_reference_t *reference,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int value_index,
     size_t value_size,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error );

/* IO functions
 */
LIBFDATA_EXTERN \
ssize_t libfdata_reference_read_buffer(
         libfdata_reference_t *reference,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBFDATA_EXTERN \
off64_t libfdata_reference_seek_offset(
         libfdata_reference_t *reference,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

