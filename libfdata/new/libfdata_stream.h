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
	/* The time stamp
	 */
	time_t timestamp;
};

/* Data functions
 */
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

#if defined( __cplusplus )
}
#endif

#endif

