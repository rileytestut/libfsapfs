/*
 * The container physical map functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfsapfs_container_physical_map.h"
#include "libfsapfs_container_physical_map_entry.h"
#include "libfsapfs_libbfio.h"
#include "libfsapfs_libcdata.h"
#include "libfsapfs_libcerror.h"
#include "libfsapfs_libcnotify.h"

#include "fsapfs_container_physical_map.h"

/* Creates a container physical map
 * Make sure the value container_physical_map is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsapfs_container_physical_map_initialize(
     libfsapfs_container_physical_map_t **container_physical_map,
     libcerror_error_t **error )
{
	static char *function = "libfsapfs_container_physical_map_initialize";

	if( container_physical_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container physical map.",
		 function );

		return( -1 );
	}
	if( *container_physical_map != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid container physical map value already set.",
		 function );

		return( -1 );
	}
	*container_physical_map = memory_allocate_structure(
	                           libfsapfs_container_physical_map_t );

	if( *container_physical_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create container physical map.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *container_physical_map,
	     0,
	     sizeof( libfsapfs_container_physical_map_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear container physical map.",
		 function );

		memory_free(
		 *container_physical_map );

		*container_physical_map = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *container_physical_map )->entries_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *container_physical_map != NULL )
	{
		memory_free(
		 *container_physical_map );

		*container_physical_map = NULL;
	}
	return( -1 );
}

/* Frees a container physical map
 * Returns 1 if successful or -1 on error
 */
int libfsapfs_container_physical_map_free(
     libfsapfs_container_physical_map_t **container_physical_map,
     libcerror_error_t **error )
{
	static char *function = "libfsapfs_container_physical_map_free";
	int result            = 1;

	if( container_physical_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container physical map.",
		 function );

		return( -1 );
	}
	if( *container_physical_map != NULL )
	{
		if( libcdata_array_free(
		     &( ( *container_physical_map )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsapfs_container_physical_map_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free entries array.",
			 function );

			result = -1;
		}
		memory_free(
		 *container_physical_map );

		*container_physical_map = NULL;
	}
	return( result );
}

/* Reads the container physical map
 * Returns 1 if successful or -1 on error
 */
int libfsapfs_container_physical_map_read_file_io_handle(
     libfsapfs_container_physical_map_t *container_physical_map,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	fsapfs_container_physical_map_t container_physical_map_data;

	static char *function = "libfsapfs_container_physical_map_read_file_io_handle";
	ssize_t read_count    = 0;

	if( container_physical_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container physical map.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading container physical map at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek container physical map offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &container_physical_map_data,
	              sizeof( fsapfs_container_physical_map_t ),
	              error );

	if( read_count != (ssize_t) sizeof( fsapfs_container_physical_map_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read container physical map data.",
		 function );

		return( -1 );
	}
	if( libfsapfs_container_physical_map_read_data(
	     container_physical_map,
	     (uint8_t *) &container_physical_map_data,
	     sizeof( fsapfs_container_physical_map_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read container physical map data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the container physical map
 * Returns 1 if successful or -1 on error
 */
int libfsapfs_container_physical_map_read_data(
     libfsapfs_container_physical_map_t *container_physical_map,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfsapfs_container_physical_map_entry_t *map_entry = NULL;
	static char *function                               = "libfsapfs_container_physical_map_read_data";
	size_t data_offset                                  = 0;
	uint32_t map_entry_index                            = 0;
	uint32_t number_of_map_entries                      = 0;
	uint32_t object_type                                = 0;
	int entry_index                                     = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                                = 0;
	uint32_t value_32bit                                = 0;
#endif

	if( container_physical_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container physical map.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( fsapfs_container_physical_map_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: container physical map data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( fsapfs_container_physical_map_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsapfs_container_physical_map_t *) data )->object_type,
	 object_type );

	if( object_type != 0x4000000cUL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid object type: 0x%08" PRIx32 ".",
		 function,
		 object_type );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsapfs_container_physical_map_t *) data )->number_of_entries,
	 number_of_map_entries );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 ( (fsapfs_container_physical_map_t *) data )->object_checksum,
		 value_64bit );
		libcnotify_printf(
		 "%s: object checksum\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (fsapfs_container_physical_map_t *) data )->object_identifier,
		 value_64bit );
		libcnotify_printf(
		 "%s: object identifier\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (fsapfs_container_physical_map_t *) data )->object_version,
		 value_64bit );
		libcnotify_printf(
		 "%s: object version\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: object type\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 object_type );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsapfs_container_physical_map_t *) data )->object_subtype,
		 value_32bit );
		libcnotify_printf(
		 "%s: object subtype\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsapfs_container_physical_map_t *) data )->flags,
		 value_32bit );
		libcnotify_printf(
		 "%s: flags\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of entries\t\t: %" PRIu32 "\n",
		 function,
		 number_of_map_entries );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset = 40;

	if( number_of_map_entries > 101 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of map entries value out of bounds.",
		 function );

		goto on_error;
	}
	for( map_entry_index = 0;
	     map_entry_index < number_of_map_entries;
	     map_entry_index++ )
	{
		if( libfsapfs_container_physical_map_entry_initialize(
		     &map_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create container physical map entry.",
			 function );

			goto on_error;
		}
		if( libfsapfs_container_physical_map_entry_read_data(
		     map_entry,
		     &( data[ data_offset ] ),
		     data_size - data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read container physical map entry: %" PRIu32 ".",
			 function,
			 map_entry_index );

			goto on_error;
		}
		data_offset += sizeof( fsapfs_container_physical_map_entry_t );

		if( libcdata_array_append_entry(
		     container_physical_map->entries_array,
		     &entry_index,
		     (intptr_t *) map_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append map entry: %" PRIu32 " to array.",
			 function,
			 map_entry_index );

			goto on_error;
		}
		map_entry = NULL;
	}
	return( 1 );

on_error:
	if( map_entry != NULL )
	{
		libfsapfs_container_physical_map_entry_free(
		 &map_entry,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the physical address of a specific object identifier
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
int libfsapfs_container_physical_map_get_physical_address_by_object_identifier(
     libfsapfs_container_physical_map_t *container_physical_map,
     uint64_t object_identifier,
     uint64_t *physical_address,
     libcerror_error_t **error )
{
	libfsapfs_container_physical_map_entry_t *map_entry = NULL;
	static char *function                               = "libfsapfs_container_physical_map_get_physical_address_by_object_identifier";
	int entry_index                                     = 0;
	int number_of_entries                               = 0;

	if( container_physical_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid container physical map.",
		 function );

		return( -1 );
	}
	if( physical_address == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid physical address.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     container_physical_map->entries_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from array.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     container_physical_map->entries_array,
		     entry_index,
		     (intptr_t **) &map_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d from array.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( map_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( object_identifier == map_entry->object_identifier )
		{
			*physical_address = map_entry->physical_address;

			return( 1 );
		}
		map_entry = NULL;
	}
	return( 0 );
}

