/*
 * The container object map functions
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

#if !defined( _LIBFSAPFS_CONTAINER_OBJECT_MAP_H )
#define _LIBFSAPFS_CONTAINER_OBJECT_MAP_H

#include <common.h>
#include <types.h>

#include "libfsapfs_libbfio.h"
#include "libfsapfs_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsapfs_container_object_map libfsapfs_container_object_map_t;

struct libfsapfs_container_object_map
{
	/* The object map btree block number
	 */
	uint64_t object_map_btree_block_number;
};

int libfsapfs_container_object_map_initialize(
     libfsapfs_container_object_map_t **container_object_map,
     libcerror_error_t **error );

int libfsapfs_container_object_map_free(
     libfsapfs_container_object_map_t **container_object_map,
     libcerror_error_t **error );

int libfsapfs_container_object_map_read_file_io_handle(
     libfsapfs_container_object_map_t *container_object_map,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libfsapfs_container_object_map_read_data(
     libfsapfs_container_object_map_t *container_object_map,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSAPFS_CONTAINER_OBJECT_MAP_H ) */

