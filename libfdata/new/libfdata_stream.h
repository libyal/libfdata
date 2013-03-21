/*
 * The stream functions
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

#if !defined( _LIBFDATA_INTERNAL_STREAM_H )
#define _LIBFDATA_INTERNAL_STREAM_H

#include <common.h>
#include <types.h>

#include "libfdata_extern.h"
#include "libfdata_libcerror.h"
#include "libfdata_libfcache.h"
#include "libfdata_range.h"
#include "libfdata_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfdata_internal_stream libfdata_internal_stream_t;

struct libfdata_internal_stream
{
	/* The data offset
	 */
	off64_t data_offset;

	/* The data size
	 */
	size64_t data_size;

	/* The maximum segment size
	 */
	size64_t maximum_segment_size;

	/* The current segment index
	 */
	int segment_index;

	/* The segment data offset
	 */
	size_t segment_data_offset;

	/* The segments array 
	 */
	libcdata_array_t *segments_array;

	/* The mapped ranges array 
	 */
	libcdata_array_t *mapped_ranges_array;

	/* The time stamp
	 */
	time_t timestamp;

	/* The flags
	 */
	uint8_t flags;

	/* The data handle
	 */
	intptr_t *data_handle;

	/* The free data handle function
	 */
	int (*free_data_handle)(
	       intptr_t **data_handle,
	       libcerror_error_t **error );

	/* The clone (duplicate) data handle function
	 */
	int (*clone_data_handle)(
	       intptr_t **destination_data_handle,
	       intptr_t *source_data_handle,
	       libcerror_error_t **error );

	/* The read segment data function
	 */
	ssize_t (*read_segment_data)(
	           intptr_t *data_handle,
	           intptr_t *file_io_handle,
	           libfdata_stream_t *stream,
                   int segment_index,
                   int segment_file_index,
	           uint8_t *segment_data,
	           size_t segment_data_size,
                   uint8_t read_flags,
	           libcerror_error_t **error );

	/* The write segment data function
	 */
	ssize_t (*write_segment_data)(
	           intptr_t *data_handle,
	           intptr_t *file_io_handle,
	           libfdata_stream_t *stream,
	           int segment_index,
	           int segment_file_index,
	           const uint8_t *segment_data,
	           size_t segment_data_size,
                   uint8_t write_flags,
	           libcerror_error_t **error );

	/* The seek segment offset function
	 */
	off64_t (*seek_segment_offset)(
	           intptr_t *data_handle,
	           intptr_t *file_io_handle,
	           libfdata_stream_t *stream,
	           int segment_index,
	           int segment_file_index,
	           off64_t segment_offset,
	           int whence,
	           libcerror_error_t **error );
};

LIBFDATA_EXTERN \
int libfdata_stream_initialize(
     libfdata_stream_t **stream,
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
                libfdata_stream_t *stream,
                int segment_index,
                int segment_file_index,
                uint8_t *segment_data,
                size_t segment_data_size,
                uint8_t read_flags,
                libcerror_error_t **error ),
     ssize_t (*write_segment_data)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                libfdata_stream_t *stream,
                int segment_index,
                int segment_file_index,
                const uint8_t *segment_data,
                size_t segment_data_size,
                uint8_t write_flags,
                libcerror_error_t **error ),
     off64_t (*seek_segment_offset)(
                intptr_t *data_handle,
                intptr_t *file_io_handle,
                libfdata_stream_t *stream,
                int segment_index,
                int segment_file_index,
                off64_t segment_offset,
                int whence,
                libcerror_error_t **error ),
     uint8_t flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_free(
     libfdata_stream_t **stream,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_clone(
     libfdata_stream_t **destination_stream,
     libfdata_stream_t *source_stream,
     libcerror_error_t **error );

/* Segment functions
 */
LIBFDATA_EXTERN \
int libfdata_stream_empty_segments(
     libfdata_stream_t *stream,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_resize_segments(
     libfdata_stream_t *stream,
     int number_of_segments,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_get_number_of_segments(
     libfdata_stream_t *stream,
     int *number_of_segments,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_get_segment_by_index(
     libfdata_stream_t *stream,
     int segment_index,
     int *segment_file_index,
     off64_t *segment_offset,
     size64_t *segment_size,
     uint32_t *segment_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_set_segment_by_index(
     libfdata_stream_t *stream,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_append_segment(
     libfdata_stream_t *stream,
     int *segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_get_maximum_segment_size(
     libfdata_stream_t *stream,
     size64_t *maximum_segment_size,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_set_maximum_segment_size(
     libfdata_stream_t *stream,
     size64_t maximum_segment_size,
     libcerror_error_t **error );

/* Mapped range functions
 */
int libfdata_stream_calculate_mapped_ranges(
     libfdata_internal_stream_t *internal_stream,
     libcerror_error_t **error );

/* Data functions
 */
LIBFDATA_EXTERN \
int libfdata_stream_get_data_offset(
     libfdata_stream_t *stream,
     off64_t *data_offset,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_get_data_size(
     libfdata_stream_t *stream,
     size64_t *data_size,
     libcerror_error_t **error );

int libfdata_stream_get_cached_data_buffer(
     libfdata_internal_stream_t *internal_stream,
     libfcache_cache_t *cache,
     libfcache_cache_value_t *cache_value,
     libfdata_buffer_t **data_buffer,
     libcerror_error_t **error );

int libfdata_stream_read_data_buffer(
     libfdata_internal_stream_t *internal_stream,
     intptr_t *file_io_handle,
     libfdata_buffer_t **data_buffer,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_get_data(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     uint8_t **data,
     size_t *data_size,
     uint8_t read_flags,
     libcerror_error_t **error );

/* Segment data functions
 */
int libfdata_stream_get_segment_index_at_data_offset(
     libfdata_internal_stream_t *internal_stream,
     off64_t data_offset,
     int *segment_index,
     off64_t *segment_data_offset,
     libcerror_error_t **error );

int libfdata_stream_get_cached_segment_data(
     libfdata_internal_stream_t *internal_stream,
     libfcache_cache_t *cache,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libfcache_cache_value_t **cache_value,
     libcerror_error_t **error );

int libfdata_stream_read_segment_data(
     libfdata_internal_stream_t *internal_stream,
     intptr_t *file_io_handle,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     uint8_t *segment_data,
     size_t segment_data_size,
     uint8_t read_flags,
     libcerror_error_t **error );

int libfdata_stream_read_segment_data_buffer(
     libfdata_internal_stream_t *internal_stream,
     intptr_t *file_io_handle,
     int segment_index,
     int segment_file_index,
     off64_t segment_offset,
     size64_t segment_size,
     uint32_t segment_flags,
     libfdata_buffer_t **data_buffer,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_get_segment_data(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t **segment_data,
     size_t *segment_data_size,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_get_segment_data_at_offset(
     libfdata_stream_t *stream,
     intptr_t *file_io_handle,
     libfcache_cache_t *cache,
     off64_t data_offset,
     uint8_t **segment_data,
     size_t *segment_data_size,
     uint8_t read_flags,
     libcerror_error_t **error );

LIBFDATA_EXTERN \
int libfdata_stream_set_segment_data(
     libfdata_stream_t *stream,
     libfcache_cache_t *cache,
     int segment_index,
     uint8_t *segment_data,
     size_t segment_data_size,
     uint8_t flags,
     libcerror_error_t **error );

/* IO functions
 */
LIBFDATA_EXTERN \
ssize_t libfdata_stream_read_buffer(
         libfdata_stream_t *stream,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         uint8_t *buffer,
         size_t buffer_size,
         uint8_t read_flags,
         libcerror_error_t **error );

LIBFDATA_EXTERN \
ssize_t libfdata_stream_write_buffer(
         libfdata_stream_t *stream,
         intptr_t *file_io_handle,
         libfcache_cache_t *cache,
         const uint8_t *buffer,
         size_t buffer_size,
         uint8_t write_flags,
         libcerror_error_t **error );

LIBFDATA_EXTERN \
off64_t libfdata_stream_seek_offset(
         libfdata_stream_t *stream,
         intptr_t *file_io_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

