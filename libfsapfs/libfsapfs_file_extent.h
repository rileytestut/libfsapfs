/*
 * File extent functions
 *
 * Copyright (C) 2018, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSAPFS_FILE_EXTENT_H )
#define _LIBFSAPFS_FILE_EXTENT_H

#include <common.h>
#include <types.h>

#include "libfsapfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsapfs_file_extent libfsapfs_file_extent_t;

struct libfsapfs_file_extent
{
	/* Block number
	 */
	uint64_t block_number;

	/* Data size
	 */
	uint64_t data_size;
};

int libfsapfs_file_extent_initialize(
     libfsapfs_file_extent_t **file_extent,
     libcerror_error_t **error );

int libfsapfs_file_extent_free(
     libfsapfs_file_extent_t **file_extent,
     libcerror_error_t **error );

int libfsapfs_file_extent_read_key_data(
     libfsapfs_file_extent_t *file_extent,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsapfs_file_extent_read_value_data(
     libfsapfs_file_extent_t *file_extent,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSAPFS_FILE_EXTENT_H ) */

