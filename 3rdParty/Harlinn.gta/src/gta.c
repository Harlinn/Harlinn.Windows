/*
 * gta.c
 *
 * This file is part of libgta, a library that implements the Generic Tagged
 * Array (GTA) file format.
 *
 * Copyright (C) 2010, 2011, 2012, 2014, 2019
 * Martin Lambers <marlam@marlam.de>
 *
 * Libgta is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * Libgta is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Libgta. If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#ifndef _MSC_VER
#   include <unistd.h>
#endif

#if WITH_COMPRESSION
#   include <zlib.h>
#   if (defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__ && defined DLL_EXPORT
#      define BZ_IMPORT
#   endif
#   include <bzlib.h>
#   if (defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__ && !defined DLL_EXPORT
#      define LZMA_API_STATIC
#   endif
#   include <lzma.h>
#endif

#define GTA_BUILD
#include "gta/gta.h"

/* Work around Windows deficiencies.  */
#ifdef _MSC_VER
#   pragma warning(disable : 4244 4996)
#   define ssize_t intptr_t
#   define inline
#endif
#if (defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__
#   ifndef EOVERFLOW
#       define EOVERFLOW EFBIG
#   endif
#   undef off_t
#   define off_t intmax_t
#   undef fseeko
#   undef ftello
#   if defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR)
#       define fseeko(stream, offset, whence) _fseeki64(stream, offset, whence)
#       define ftello(stream) _ftelli64(stream)
#   else
#       define fseeko(stream, offset, whence) fseeko64(stream, offset, whence)
#       define ftello(stream) ftello64(stream)
#   endif
#   undef lseek
#   define lseek(fd, offset, whence) _lseeki64(fd, offset, whence)
#   ifndef SSIZE_MAX
#       define SSIZE_MAX (sizeof(ssize_t) == sizeof(long long) ? LLONG_MAX \
                : sizeof(ssize_t) == sizeof(long) ? LONG_MAX : INT_MAX)
#   endif
#endif

/* Define OFF_MAX (maximum value in off_t). */
#ifndef OFF_MAX
#   define OFF_MAX (sizeof(off_t) == sizeof(long long) ? LLONG_MAX \
        : sizeof(off_t) == sizeof(long) ? LONG_MAX : INT_MAX)
#endif

/*
 *
 * Configuration
 *
 */

/* The maximum size of a chunk. Changing this will break compatibility! */
static const size_t gta_max_chunk_size = 16 * 1024 * 1024;
/* The buffer size increment when filling buffers with an unknown number of elements. */
static const size_t gta_bufsize_inc = 256;


/*
 *
 * Sanity checks
 *
 */


#if !(SIZEOF_INT8_T == 1) || !(SIZEOF_INT >= 4) || !(UINTMAX_MAX >= UINT64_MAX)
#   error "This library makes assumptions that are not true on this platform."
#endif

static GTA_ATTR_CONST GTA_ATTR_NOTHROW
bool
gta_size_overflow(size_t a, size_t b)
{
    return !(b == 0 || !(SIZE_MAX / b < a));
}

static GTA_ATTR_CONST GTA_ATTR_NOTHROW
bool
gta_uintmax_overflow(uintmax_t a, uintmax_t b)
{
    return !(b == 0 || !(UINTMAX_MAX / b < a));
}


/*
 *
 * Internal Types
 *
 */


struct gta_internal_taglist_struct
{
    /* A tag list is both an unsorted list, with new entries appended to its
     * end, and a sorted list according to strcmp(), with sorted[0] giving the
     * index of the first entry, sorted[1] of the second and so on.
     * This means that tags are stored in the GTA in the order in which they
     * were set (which is not strictly necessary, but nice), and that a tag list
     * can be searched for specific entries via fast binary search nevertheless.
     * We keep track of the total size that the tag list requires when written
     * to a GTA file in the encoded_size value. */
    ssize_t entries;
    size_t size;
    char **names;
    char **values;
    ssize_t *sorted;
    size_t encoded_size;
};

struct gta_internal_header_struct
{
    bool host_endianness;
    gta_compression_t compression;

    gta_taglist_t *global_taglist;

    size_t components;
    uint8_t *component_types;
    uintmax_t *component_blob_sizes;
    gta_taglist_t **component_taglists;
    uintmax_t element_size;

    size_t dimensions;
    uintmax_t *dimension_sizes;
    gta_taglist_t **dimension_taglists;
};

struct gta_internal_io_state_struct
{
    int io_type;                // 0 = undecided, 1 = input, 2 = output
    bool failure;               // Failure flag. When set, no further actions are performed.
    uintmax_t counter;          // Number of elements that were already read or written.
    void *chunk;                // The current chunk (if GTA is compressed) of buffer (if uncompressed)
    size_t chunk_size;          // Size of the chunk
    size_t chunk_index;         // Current index inside the chunk
    uintmax_t already_read;     // Only for input of uncompressed GTA: number of bytes that were already read
};


/*
 *
 * Version information
 *
 */


const char *
gta_version(int *GTA_RESTRICT major, int *GTA_RESTRICT minor, int *GTA_RESTRICT patch)
{
    if (major)
    {
        *major = GTA_VERSION_MAJOR;
    }
    if (minor)
    {
        *minor = GTA_VERSION_MINOR;
    }
    if (patch)
    {
        *patch = GTA_VERSION_PATCH;
    }
    return GTA_VERSION;
}


/*
 *
 * Custom input/output functions for files and file descriptors.
 *
 */


static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NOTHROW
size_t
gta_read_stream(intptr_t userdata, void *GTA_RESTRICT buffer, size_t size, int *GTA_RESTRICT error)
{
    errno = 0;
    FILE *f = (FILE *)userdata;
    size_t r = fread(buffer, 1, size, f);
    if (r < size && ferror(f))
    {
        if (errno == 0)
        {
            errno = EIO;
        }
        *error = true;
    }
    return r;
}

static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NOTHROW
size_t
gta_write_stream(intptr_t userdata, const void *GTA_RESTRICT buffer, size_t size, int *GTA_RESTRICT error)
{
    errno = 0;
    FILE *f = (FILE *)userdata;
    size_t r = fwrite(buffer, 1, size, f);
    if (r < size)
    {
        if (errno == 0)
        {
            errno = EIO;
        }
        *error = true;
    }
    return r;
}

static GTA_ATTR_NOTHROW
void gta_seek_stream(intptr_t userdata, intmax_t offset, int whence, int *GTA_RESTRICT error)
{
    FILE *f = (FILE *)userdata;
    int r;
    if (offset > OFF_MAX)
    {
        errno = EOVERFLOW;
        *error = true;
        return;
    }
    errno = 0;
    r = fseeko(f, offset, whence);
    if (r != 0)
    {
        if (errno == 0)
        {
            errno = EIO;
        }
        *error = true;
    }
    return;
}

static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NOTHROW
size_t
gta_read_fd(intptr_t userdata, void *GTA_RESTRICT buffer, size_t size, int *GTA_RESTRICT error)
{
    int fd = (int)userdata;
    char *ptr = buffer;
    size_t bytes_read = 0;
    ssize_t r;
    while (bytes_read < size)
    {
        size_t remaining_size = size - bytes_read;
        ssize_t chunk_size = (remaining_size <= SSIZE_MAX ? remaining_size : SSIZE_MAX);
        r = read(fd, ptr, chunk_size);
        if (r < 0)
        {
            *error = true;
            break;
        }
        bytes_read += r;
        if (r < chunk_size)
        {
            break;
        }
        ptr += chunk_size;
    }
    return bytes_read;
}

static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NOTHROW
size_t
gta_write_fd(intptr_t userdata, const void *GTA_RESTRICT buffer, size_t size, int *GTA_RESTRICT error)
{
    int fd = (int)userdata;
    const char *ptr = buffer;
    size_t bytes_written = 0;
    ssize_t r;
    while (bytes_written < size)
    {
        size_t remaining_size = size - bytes_written;
        ssize_t chunk_size = (remaining_size <= SSIZE_MAX ? remaining_size : SSIZE_MAX);
        r = write(fd, ptr, chunk_size);
        if (r < 0)
        {
            *error = true;
            break;
        }
        bytes_written += r;
        if (r < chunk_size)
        {
            break;
        }
        ptr += chunk_size;
    }
    return bytes_written;
}

static GTA_ATTR_NOTHROW
void gta_seek_fd(intptr_t userdata, intmax_t offset, int whence, int *GTA_RESTRICT error)
{
    int fd = (int)userdata;
    int r;
    if (offset > OFF_MAX)
    {
        errno = EOVERFLOW;
        *error = true;
        return;
    }
    r = lseek(fd, offset, whence);
    if (r == -1)
    {
        *error = true;
    }
    return;
}

static GTA_ATTR_NOTHROW
gta_result_t gta_readskip(gta_read_t read_fn, intptr_t userdata, uintmax_t s)
{
    gta_result_t retval = GTA_OK;
    void *trash = malloc(s < gta_max_chunk_size ? s : gta_max_chunk_size);
    if (!trash)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    while (s > 0)
    {
        int error = false;
        size_t x = (s > gta_max_chunk_size ? gta_max_chunk_size : s);
        size_t r = read_fn(userdata, trash, x, &error);
        if (error)
        {
            retval = GTA_SYSTEM_ERROR;
            goto exit;
        }
        if (r < x)
        {
            retval = GTA_UNEXPECTED_EOF;
            goto exit;
        }
        s -= x;
    }
exit:
    free(trash);
    return retval;
}


/*
 *
 * Compression and Decompression
 *
 */


static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NOTHROW
gta_result_t
gta_compress(void **dst, size_t *dst_size, const void *src, size_t src_size, gta_compression_t compression)
{
    void* tmp_ptr;
    gta_result_t retval = GTA_OK;

    switch (compression)
    {
    case GTA_NONE:
        {
            *dst = malloc(src_size);
            if (!*dst)
            {
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            memcpy(*dst, src, src_size);
            *dst_size = src_size;
        }
        break;

#if WITH_COMPRESSION
    case GTA_ZLIB:
    case GTA_ZLIB1:
    case GTA_ZLIB2:
    case GTA_ZLIB3:
    case GTA_ZLIB4:
    case GTA_ZLIB5:
    case GTA_ZLIB6:
    case GTA_ZLIB7:
    case GTA_ZLIB8:
    case GTA_ZLIB9:
        {
            int zlib_level = (
                      compression == GTA_ZLIB1 ? 1
                    : compression == GTA_ZLIB2 ? 2
                    : compression == GTA_ZLIB3 ? 3
                    : compression == GTA_ZLIB4 ? 4
                    : compression == GTA_ZLIB5 ? 5
                    : compression == GTA_ZLIB6 ? 6
                    : compression == GTA_ZLIB7 ? 7
                    : compression == GTA_ZLIB8 ? 8
                    : compression == GTA_ZLIB9 ? 9
                    : Z_DEFAULT_COMPRESSION);
            int zlib_r;
            uLong zlib_uncompressed_size = src_size;
            uLongf zlib_compressed_size;

            size_t max_compression_overhead = src_size / 10 + 12;
            if (src_size > SIZE_MAX - max_compression_overhead)
            {
                retval = GTA_OVERFLOW;
                break;
            }
            zlib_compressed_size = src_size + max_compression_overhead;
            if (zlib_uncompressed_size != src_size || zlib_compressed_size != src_size + max_compression_overhead)
            {
                // Data type overflow
                retval = GTA_OVERFLOW;
                break;
            }
            *dst = malloc(zlib_compressed_size);
            if (!*dst)
            {
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            zlib_r = compress2(*dst, &zlib_compressed_size, src, zlib_uncompressed_size, zlib_level);
            if (zlib_r != Z_OK)
            {
                free(*dst);
                // of the possible errors Z_MEM_ERROR, Z_BUF_ERROR, Z_STREAM_ERROR,
                // only Z_MEM_ERROR can happen here
                errno = ENOMEM;
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            *dst_size = zlib_compressed_size;
            tmp_ptr = realloc(*dst, *dst_size);
            if (!tmp_ptr)
            {
                free(*dst);
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            *dst = tmp_ptr;
        }
        break;

    case GTA_BZIP2:
        {
            size_t max_compression_overhead = src_size / 100 + 600;
            if (src_size > SIZE_MAX - max_compression_overhead)
            {
                retval = GTA_OVERFLOW;
                break;
            }
            unsigned int bz2_uncompressed_size = src_size;
            unsigned int bz2_compressed_size = src_size + max_compression_overhead;
            if (bz2_uncompressed_size != src_size || bz2_compressed_size != src_size + max_compression_overhead)
            {
                // Data type overflow
                retval = GTA_OVERFLOW;
                break;
            }
            *dst = malloc(bz2_compressed_size);
            if (!*dst)
            {
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            int r = BZ2_bzBuffToBuffCompress(
                    *dst, &bz2_compressed_size,
                    (char *)src, bz2_uncompressed_size,
                    9, 0, 0);
            if (r != BZ_OK)
            {
                // of the possible errors BZ_CONFIG_ERROR, BZ_PARAM_ERROR,
                // BZ_MEM_ERROR, BZ_OUTBUFF_FULL, only BZ_MEM_ERROR can happen here.
                errno = ENOMEM;
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            *dst_size = bz2_compressed_size;
            tmp_ptr = realloc(*dst, *dst_size);
            if (!tmp_ptr)
            {
                free(*dst);
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            *dst = tmp_ptr;
        }
        break;

    case GTA_XZ:
        {
            lzma_stream strm = LZMA_STREAM_INIT;
            void *buf;
            size_t buf_size;
            lzma_ret r;

            buf_size = lzma_stream_buffer_bound(src_size);
            if (buf_size == 0)
            {
                retval = GTA_OVERFLOW;
                break;
            }
            buf = malloc(buf_size);
            if (!buf)
            {
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            strm.next_in = src;
            strm.avail_in = src_size;
            strm.next_out = buf;
            strm.avail_out = buf_size;
            r = lzma_easy_encoder(&strm, LZMA_PRESET_DEFAULT, LZMA_CHECK_NONE);
            if (r != LZMA_OK)
            {
                errno = EINVAL;
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            r = lzma_code(&strm, LZMA_RUN);
            if (r != LZMA_OK)
            {
                lzma_end(&strm);
                errno = EINVAL;
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            r = lzma_code(&strm, LZMA_FINISH);
            if (r != LZMA_STREAM_END)
            {
                lzma_end(&strm);
                errno = EINVAL;
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            *dst_size = strm.total_out;
            *dst = realloc(buf, *dst_size);
            if (!*dst)
            {
                free(buf);
                lzma_end(&strm);
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            lzma_end(&strm);
        }
        break;
#endif
    }

    return retval;
}

static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NOTHROW
gta_result_t
gta_uncompress(void *dst, size_t dst_size, const void *src, size_t src_size, gta_compression_t compression)
{
    gta_result_t retval = GTA_OK;

    switch (compression)
    {
    case GTA_NONE:
        {
            if (dst_size < src_size)
            {
                retval = GTA_OVERFLOW;
                break;
            }
            memcpy(dst, src, src_size);
        }
        break;

#if WITH_COMPRESSION
    case GTA_ZLIB:
    case GTA_ZLIB1:
    case GTA_ZLIB2:
    case GTA_ZLIB3:
    case GTA_ZLIB4:
    case GTA_ZLIB5:
    case GTA_ZLIB6:
    case GTA_ZLIB7:
    case GTA_ZLIB8:
    case GTA_ZLIB9:
        {
            int zlib_r;
            uLong zlib_compressed_size = src_size;
            uLongf zlib_uncompressed_size = dst_size;

            if (zlib_compressed_size != src_size || zlib_uncompressed_size != dst_size)
            {
                // Data type overflow
                retval = GTA_OVERFLOW;
                break;
            }
            zlib_r = uncompress(dst, &zlib_uncompressed_size, src, zlib_compressed_size);
            if (zlib_r != Z_OK)
            {
                if (zlib_r == Z_MEM_ERROR)
                {
                    errno = ENOMEM;
                    retval = GTA_SYSTEM_ERROR;
                    break;
                }
                else if (zlib_r == Z_BUF_ERROR)
                {
                    retval = GTA_OVERFLOW;
                    break;
                }
                else // zlib_r == Z_DATA_ERROR or unknown error
                {
                    retval = GTA_INVALID_DATA;
                    break;
                }
            }
            if (zlib_uncompressed_size != dst_size)
            {
                retval = GTA_INVALID_DATA;
                break;
            }
        }
        break;

    case GTA_BZIP2:
        {
            unsigned int bz2_compressed_size = src_size;
            unsigned int bz2_uncompressed_size = dst_size;
            int r;

            if (bz2_compressed_size != src_size || bz2_uncompressed_size != dst_size)
            {
                // Data type overflow
                retval = GTA_OVERFLOW;
                break;
            }
            r = BZ2_bzBuffToBuffDecompress(dst, &bz2_uncompressed_size, (char *)src, bz2_compressed_size, 0, 0);
            if (r != BZ_OK)
            {
                if (r == BZ_MEM_ERROR)
                {
                    errno = ENOMEM;
                    retval = GTA_SYSTEM_ERROR;
                    break;
                }
                else
                {
                    retval = GTA_INVALID_DATA;
                    break;
                }
            }
            if (bz2_uncompressed_size != dst_size)
            {
                retval = GTA_INVALID_DATA;
                break;
            }
        }
        break;

    case GTA_XZ:
        {
            lzma_stream strm = LZMA_STREAM_INIT;
            lzma_ret r;

            strm.next_in = src;
            strm.avail_in = src_size;
            strm.next_out = dst;
            strm.avail_out = dst_size;
            r = lzma_stream_decoder(&strm, gta_max_chunk_size, 0);
            if (r != LZMA_OK)
            {
                errno = (r == LZMA_MEM_ERROR ? ENOMEM : EINVAL);
                retval = GTA_SYSTEM_ERROR;
                break;
            }
            r = lzma_code(&strm, LZMA_RUN);
            if (r != LZMA_STREAM_END)
            {
                lzma_end(&strm);
                retval = GTA_INVALID_DATA;
                break;
            }
            if (strm.total_out != dst_size)
            {
                lzma_end(&strm);
                retval = GTA_INVALID_DATA;
                break;
            }
            lzma_end(&strm);
        }
        break;
#endif
    }

    return retval;
}


/*
 *
 * Endianness Functions
 *
 */


/**
 * \brief               Find out if the data needs endianness swapping.
 * \param header        The header.
 * \return              Whether the data needs endianness swapping.
 */
static inline GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW
bool
gta_data_needs_endianness_swapping(const gta_header_t *header)
{
    return !(header->host_endianness);
}

/**
 * \brief               Swap the endianness of a 16 bit value.
 * \param ptr           The value.
 */
static inline GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
void
gta_swap_endianness_16(void *GTA_RESTRICT ptr)
{
    uint16_t x;
    memcpy(&x, ptr, sizeof(uint16_t));
    x = (x << UINT16_C(8)) | (x >> UINT16_C(8));
    memcpy(ptr, &x, sizeof(uint16_t));
}

/**
 * \brief               Swap the endianness of a 32 bit value.
 * \param ptr           The value.
 */
static inline GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
void
gta_swap_endianness_32(void *GTA_RESTRICT ptr)
{
    uint32_t x;
    memcpy(&x, ptr, sizeof(uint32_t));
    x =   ((x                       ) << UINT32_C(24))
        | ((x & UINT32_C(0x0000ff00)) << UINT32_C(8))
        | ((x & UINT32_C(0x00ff0000)) >> UINT32_C(8))
        | ((x                       ) >> UINT32_C(24));
    memcpy(ptr, &x, sizeof(uint32_t));
}

/**
 * \brief               Swap the endianness of a 64 bit value.
 * \param ptr           The value.
 */
static inline GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
void
gta_swap_endianness_64(void *GTA_RESTRICT ptr)
{
    uint64_t x;
    memcpy(&x, ptr, sizeof(uint64_t));
    x =   ((x                               ) << UINT64_C(56))
        | ((x & UINT64_C(0x000000000000ff00)) << UINT64_C(40))
        | ((x & UINT64_C(0x0000000000ff0000)) << UINT64_C(24))
        | ((x & UINT64_C(0x00000000ff000000)) << UINT64_C(8))
        | ((x & UINT64_C(0x000000ff00000000)) >> UINT64_C(8))
        | ((x & UINT64_C(0x0000ff0000000000)) >> UINT64_C(24))
        | ((x & UINT64_C(0x00ff000000000000)) >> UINT64_C(40))
        | ((x                               ) >> UINT64_C(56));
    memcpy(ptr, &x, sizeof(uint64_t));
}

/**
 * \brief               Swap the endianness of a 128 bit value.
 * \param ptr           The value.
 */
static inline GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
void
gta_swap_endianness_128(void *GTA_RESTRICT ptr)
{
    /* We cannot expect uint128_t to be available. */
    uint64_t x[2];
    memcpy(x, ptr, 2 * sizeof(uint64_t));
    gta_swap_endianness_64(x + 0);
    gta_swap_endianness_64(x + 1);
    uint64_t tmp = x[0];
    x[0] = x[1];
    x[1] = tmp;
    memcpy(ptr, x, 2 * sizeof(uint64_t));
}

/**
 * \brief               Swap the endianness of a component.
 * \param header        The header.
 * \param i             The component index.
 * \param component     The component.
 *
 * Swaps the endianness of a the given component.\n
 * Components of type \a GTA_BLOB are assumed to be independent of endianness,
 * and are therefore not altered.
 */
static inline GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
void
gta_swap_component_endianness(const gta_header_t *header, uintmax_t i, void *GTA_RESTRICT component)
{
    switch (header->component_types[i])
    {
    case GTA_BLOB:
    case GTA_INT8:
    case GTA_UINT8:
        break;
    case GTA_INT16:
    case GTA_UINT16:
        gta_swap_endianness_16(component);
        break;
    case GTA_INT32:
    case GTA_UINT32:
    case GTA_FLOAT32:
        gta_swap_endianness_32(component);
        break;
    case GTA_INT64:
    case GTA_UINT64:
    case GTA_FLOAT64:
        gta_swap_endianness_64(component);
        break;
    case GTA_INT128:
    case GTA_UINT128:
    case GTA_FLOAT128:
        gta_swap_endianness_128(component);
        break;
    case GTA_CFLOAT32:
        gta_swap_endianness_32(component);
        gta_swap_endianness_32((char *)component + 4);
        break;
    case GTA_CFLOAT64:
        gta_swap_endianness_64(component);
        gta_swap_endianness_64((char *)component + 8);
        break;
    case GTA_CFLOAT128:
        gta_swap_endianness_128(component);
        gta_swap_endianness_128((char *)component + 16);
        break;
    }
}

/**
 * \brief               Swap the endianness of an array element.
 * \param header        The header.
 * \param element       The array element.
 *
 * This function corrects the endianness for all components of the given array element.\n
 * Components of type \a GTA_BLOB are assumed to be independent of endianness,
 * and are therefore not altered.
 */
static inline GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
void
gta_swap_element_endianness(const gta_header_t *header, void *GTA_RESTRICT element)
{
    char *ptr = element;
    size_t blob_size_index = 0;
    for (uintmax_t i = 0; i < header->components; i++)
    {
        gta_swap_component_endianness(header, i, ptr);
        switch (header->component_types[i])
        {
        case GTA_BLOB:
            ptr += header->component_blob_sizes[blob_size_index++];
            break;
        case GTA_INT8:
        case GTA_UINT8:
            ptr += 1;
            break;
        case GTA_INT16:
        case GTA_UINT16:
            ptr += 2;
            break;
        case GTA_INT32:
        case GTA_UINT32:
        case GTA_FLOAT32:
            ptr += 4;
            break;
        case GTA_INT64:
        case GTA_UINT64:
        case GTA_FLOAT64:
        case GTA_CFLOAT32:
            ptr += 8;
            break;
        case GTA_INT128:
        case GTA_UINT128:
        case GTA_FLOAT128:
        case GTA_CFLOAT64:
            ptr += 16;
            break;
        case GTA_CFLOAT128:
            ptr += 32;
            break;
        }
    }
}


/*
 *
 * Read and Write Chunks
 *
 */


/**
 * \brief               Read a data chunk.
 * \param header        The header.
 * \param chunk         The buffer for the chunk (will be allocated).
 * \param chunk_size    The size of the chunk.
 * \param read_fn       The custom input function.
 * \param userdata      A parameter to the custom input function.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 */
static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL
gta_result_t
gta_read_chunk(const gta_header_t *GTA_RESTRICT header,
        void *GTA_RESTRICT *chunk, size_t *chunk_size,
        gta_read_t read_fn, intptr_t userdata)
{
    int error = false;
    uint64_t size_uncompressed;
    uint8_t compression;
    uint64_t size_compressed;
    void *chunk_compressed = NULL;
    gta_result_t retval = GTA_OK;
    size_t r;

    *chunk = NULL;
    *chunk_size = 0;
    r = read_fn(userdata, &size_uncompressed, sizeof(uint64_t), &error);
    if (error)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    if (r < sizeof(uint64_t))
    {
        retval = GTA_UNEXPECTED_EOF;
        goto exit;
    }
    if (gta_data_needs_endianness_swapping(header))
    {
        gta_swap_endianness_64(&size_uncompressed);
    }
    if (size_uncompressed > gta_max_chunk_size)
    {
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
    }
    if (size_uncompressed == 0)
    {
        // the last, empty chunk
        retval = GTA_OK;
        goto exit;
    }
    *chunk_size = size_uncompressed;
    *chunk = malloc(*chunk_size);
    if (!*chunk)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    r = read_fn(userdata, &compression, sizeof(uint8_t), &error);
    if (error)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    if (r < sizeof(uint8_t))
    {
        retval = GTA_UNEXPECTED_EOF;
        goto exit;
    }
    if (compression != GTA_NONE
            && compression != GTA_ZLIB
            && compression != GTA_ZLIB1
            && compression != GTA_ZLIB2
            && compression != GTA_ZLIB3
            && compression != GTA_ZLIB4
            && compression != GTA_ZLIB5
            && compression != GTA_ZLIB6
            && compression != GTA_ZLIB7
            && compression != GTA_ZLIB8
            && compression != GTA_ZLIB9
            && compression != GTA_BZIP2
            && compression != GTA_XZ)
    {
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
    }
    if (compression == GTA_NONE)
    {
        r = read_fn(userdata, *chunk, *chunk_size, &error);
        if (error)
        {
            retval = GTA_SYSTEM_ERROR;
            goto exit;
        }
        if (r < *chunk_size)
        {
            retval = GTA_UNEXPECTED_EOF;
            goto exit;
        }
    }
    else
    {
#if WITH_COMPRESSION
        r = read_fn(userdata, &size_compressed, sizeof(uint64_t), &error);
        if (error)
        {
            retval = GTA_SYSTEM_ERROR;
            goto exit;
        }
        if (r < sizeof(uint64_t))
        {
            retval = GTA_UNEXPECTED_EOF;
            goto exit;
        }
        if (gta_data_needs_endianness_swapping(header))
        {
            gta_swap_endianness_64(&size_compressed);
        }
        if (size_compressed > size_uncompressed)
        {
            // A compressed chunk is always smaller than an uncompressed chunk,
            // or else it would not have been compressed! See specification.
            retval = GTA_INVALID_DATA;
            goto exit;
        }
        if (size_compressed == 0)
        {
            retval = GTA_INVALID_DATA;
            goto exit;
        }
        chunk_compressed = malloc(size_compressed);
        if (!chunk_compressed)
        {
            retval = GTA_SYSTEM_ERROR;
            goto exit;
        }
        r = read_fn(userdata, chunk_compressed, size_compressed, &error);
        if (error)
        {
            retval = GTA_SYSTEM_ERROR;
            goto exit;
        }
        if (r < size_compressed)
        {
            retval = GTA_UNEXPECTED_EOF;
            goto exit;
        }
        retval = gta_uncompress(*chunk, *chunk_size,
                chunk_compressed, size_compressed, compression);
        if (retval != GTA_OK)
        {
            goto exit;
        }
        free(chunk_compressed);
        chunk_compressed = NULL;
#else
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
#endif
    }

exit:
    free(chunk_compressed);
    if (retval != GTA_OK)
    {
        free(*chunk);
        *chunk = NULL;
        *chunk_size = 0;
    }
    return retval;
}

/**
 * \brief               Skip a data chunk.
 * \param header        The header.
 * \param chunk_size    The size of the skipped chunk.
 * \param read_fn       The custom input function.
 * \param seek_fn       The custom seek function, or NULL for non-seekable input.
 * \param userdata      A parameter to the custom input/seek functions.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 */
static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL3(1, 2, 3)
gta_result_t
gta_skip_chunk(const gta_header_t *GTA_RESTRICT header, size_t *chunk_size,
        gta_read_t read_fn, gta_seek_t seek_fn, intptr_t userdata)
{
    int error = false;
    uint64_t size_uncompressed;
    uint8_t compression;
    uint64_t size_compressed;
    void *trash = NULL;
    gta_result_t retval = GTA_OK;
    size_t r;

    r = read_fn(userdata, &size_uncompressed, sizeof(uint64_t), &error);
    if (error)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    if (r < sizeof(uint64_t))
    {
        retval = GTA_UNEXPECTED_EOF;
        goto exit;
    }
    if (gta_data_needs_endianness_swapping(header))
    {
        gta_swap_endianness_64(&size_uncompressed);
    }
    if (size_uncompressed > gta_max_chunk_size)
    {
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
    }
    if (size_uncompressed == 0)
    {
        // the last, empty chunk
        *chunk_size = 0;
        retval = GTA_OK;
        goto exit;
    }
    *chunk_size = size_uncompressed;
    r = read_fn(userdata, &compression, sizeof(uint8_t), &error);
    if (error)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    if (r < sizeof(uint8_t))
    {
        retval = GTA_UNEXPECTED_EOF;
        goto exit;
    }
    if (compression != GTA_NONE
            && compression != GTA_ZLIB
            && compression != GTA_ZLIB1
            && compression != GTA_ZLIB2
            && compression != GTA_ZLIB3
            && compression != GTA_ZLIB4
            && compression != GTA_ZLIB5
            && compression != GTA_ZLIB6
            && compression != GTA_ZLIB7
            && compression != GTA_ZLIB8
            && compression != GTA_ZLIB9
            && compression != GTA_BZIP2
            && compression != GTA_XZ)
    {
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
    }
    if (compression == GTA_NONE)
    {
        if (seek_fn)
        {
            seek_fn(userdata, *chunk_size, SEEK_CUR, &error);
            if (error)
            {
                retval = GTA_SYSTEM_ERROR;
                goto exit;
            }
        }
        else
        {
            retval = gta_readskip(read_fn, userdata, *chunk_size);
            if (retval != GTA_OK)
            {
                goto exit;
            }
        }
    }
    else
    {
#if WITH_COMPRESSION
        r = read_fn(userdata, &size_compressed, sizeof(uint64_t), &error);
        if (error)
        {
            retval = GTA_SYSTEM_ERROR;
            goto exit;
        }
        if (r < sizeof(uint64_t))
        {
            retval = GTA_UNEXPECTED_EOF;
            goto exit;
        }
        if (gta_data_needs_endianness_swapping(header))
        {
            gta_swap_endianness_64(&size_compressed);
        }
        if (size_compressed > size_uncompressed)
        {
            // A compressed chunk is always smaller than an uncompressed chunk,
            // or else it would not have been compressed! See specification.
            retval = GTA_INVALID_DATA;
            goto exit;
        }
        if (size_compressed == 0)
        {
            retval = GTA_INVALID_DATA;
            goto exit;
        }
        if (seek_fn)
        {
            seek_fn(userdata, size_compressed, SEEK_CUR, &error);
            if (error)
            {
                retval = GTA_SYSTEM_ERROR;
                goto exit;
            }
        }
        else
        {
            retval = gta_readskip(read_fn, userdata, size_compressed);
            if (retval != GTA_OK)
            {
                goto exit;
            }
        }
#else
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
#endif
    }

exit:
    free(trash);
    if (retval != GTA_OK)
    {
        *chunk_size = 0;
    }
    return retval;
}

/**
 * \brief               Write a data chunk.
 * \param header        The header.
 * \param chunk         The chunk buffer.
 * \param chunk_size    The size of the chunk.
 * \param write_fn      The custom output function.
 * \param userdata      A parameter to the custom output function.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA (if the chunk size larger than the limit), or \a GTA_SYSTEM_ERROR.
 */
static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL1(1)
gta_result_t
gta_write_chunk(const gta_header_t *GTA_RESTRICT header,
        const void *GTA_RESTRICT chunk, size_t chunk_size,
        gta_write_t write_fn, intptr_t userdata)
{
    int error = false;
    uint64_t size_uncompressed = chunk_size;
    uint8_t output_compression;
    gta_result_t retval = GTA_OK;
    size_t r;

    if (chunk_size > gta_max_chunk_size)
    {
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
    }
    errno = 0;
    r = write_fn(userdata, &size_uncompressed, sizeof(uint64_t), &error);
    if (error || r < sizeof(uint64_t))
    {
        if (errno == 0)
        {
            errno = EIO;
        }
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    if (chunk_size == 0)
    {
        retval = GTA_OK;
        goto exit;
    }
    output_compression = GTA_NONE;
    errno = 0;
    r = write_fn(userdata, &output_compression, sizeof(uint8_t), &error);
    if (error || r < sizeof(uint8_t))
    {
        if (errno == 0)
        {
            errno = EIO;
        }
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    errno = 0;
    r = write_fn(userdata, chunk, chunk_size, &error);
    if (error || r < chunk_size)
    {
        if (errno == 0)
        {
            errno = EIO;
        }
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }

exit:
    return retval;
}


/*
 *
 * Initialize and Deinitialize Tag Lists
 *
 */


static GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
void
gta_create_taglist(gta_taglist_t *GTA_RESTRICT taglist)
{
    taglist->entries = 0;
    taglist->size = 0;
    taglist->names = NULL;
    taglist->values = NULL;
    taglist->sorted = NULL;
    taglist->encoded_size = 1;
}

static GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
void
gta_destroy_taglist(gta_taglist_t *GTA_RESTRICT taglist)
{
    for (ssize_t i = 0; i < taglist->entries; i++)
    {
        free(taglist->names[i]);
        free(taglist->values[i]);
    }
    free(taglist->names);
    free(taglist->values);
    free(taglist->sorted);
}


/*
 *
 * Access Tag Lists
 *
 */

/**
 * \brief                               Check if a string is valid UTF-8 and fulfills some given requirements.
 * \param s                             The string.
 * \param allow_control_characters      Whether the string is allowed to contain control characters.
 * \param allow_equal_sign              Whether the string is allowed to contain the equal sign '='.
 * \param allow_empty_string            Whether the string is allowed to be empty.
 * \return                              True if the string is valid UTF-8 and fulfills the given requirements, false otherwise.
 */
static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL
bool
gta_check_utf8(const char *s, bool allow_control_characters, bool allow_equal_sign, bool allow_empty_string)
{
    const unsigned char *data = (const unsigned char *)s;
    size_t i = 0;
    int multibyte_case = 0;
    int continuation_bytes = 0;
    unsigned int multibyte_val = 0;
    bool error = false;

    for (;;)
    {
        unsigned char c = data[i++];
        if (c < 0x80)
        {
            if (continuation_bytes > 0)
            {
                error = true;
                break;
            }
            else if (c == 0x00)
            {
                if (i == 1 && !allow_empty_string)
                {
                    error = true;
                }
                break;
            }
            else
            {
                if ((c < 0x20 || c == 0x7f) && !allow_control_characters)
                {
                    error = true;
                    break;
                }
                if (c == '=' && !allow_equal_sign)
                {
                    error = true;
                    break;
                }
            }
        }
        else if (c < 0xc0)
        {
            if (continuation_bytes > 0)
            {
                multibyte_val = (multibyte_val << 6u) | (c & 0x3f);
                continuation_bytes--;
                if (continuation_bytes == 0)
                {
                    if ((multibyte_case == 2 && multibyte_val < 0x80)
                            || (multibyte_case == 3 && multibyte_val < 0x800)
                            || (multibyte_case == 4 && multibyte_val < 0x10000)
                            || multibyte_val > 0x10ffff)
                    {
                        error = true;
                        break;
                    }
                }
            }
            else
            {
                error = true;
                break;
            }
        }
        else if (c < 0xc2)
        {
            error = true;
            break;
        }
        else if (c < 0xe0)
        {
            if (continuation_bytes == 0)
            {
                multibyte_case = 2;
                multibyte_val = (c & 0x1f);
                continuation_bytes = 1;
            }
            else
            {
                error = true;
                break;
            }
        }
        else if (c < 0xf0)
        {
            if (continuation_bytes == 0)
            {
                multibyte_case = 3;
                multibyte_val = (c & 0x0f);
                continuation_bytes = 2;
            }
            else
            {
                error = true;
                break;
            }
        }
        else if (c < 0xf5)
        {
            if (continuation_bytes == 0)
            {
                multibyte_case = 4;
                multibyte_val = (c & 0x07);
                continuation_bytes = 3;
            }
            else
            {
                error = true;
                break;
            }
        }
        else // (c <= 0xff)
        {
            error = true;
            break;
        }
    }

    return !error;
}

/**
 * \brief Check if a string is a valid tag name.
 * \param name  The string.
 * \return      True if the string is a valid tag name, false otherwise.
 */
static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL
bool
gta_check_tag_name(const char *name)
{
    return gta_check_utf8(name, false, false, false);
}

/**
 * \brief Check if a string is a valid tag value.
 * \param value The string.
 * \return      True if the string is a valid tag value, false otherwise.
 */
static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL
bool
gta_check_tag_value(const char *value)
{
    return gta_check_utf8(value, false, true, true);
}

uintmax_t
gta_get_tags(const gta_taglist_t *GTA_RESTRICT taglist)
{
    return taglist->entries;
}

const char *
gta_get_tag_name(const gta_taglist_t *GTA_RESTRICT taglist, uintmax_t i)
{
    return taglist->names[i];
}

const char *
gta_get_tag_value(const gta_taglist_t *GTA_RESTRICT taglist, uintmax_t i)
{
    return taglist->values[i];
}

const char *
gta_get_tag(const gta_taglist_t *GTA_RESTRICT taglist, const char *GTA_RESTRICT name)
{
    ssize_t a = 0;
    ssize_t b = taglist->entries - 1;

    while (b >= a)
    {
        ssize_t c = (a + b) / 2;
        ssize_t d = taglist->sorted[c];
        int cmp = strcmp(taglist->names[d], name);
        if (cmp < 0)
        {
            a = c + 1;
        }
        else if (cmp > 0)
        {
            b = c - 1;
        }
        else
        {
            return taglist->values[d];
        }
    }
    return NULL;
}

gta_result_t
gta_set_tag(gta_taglist_t *GTA_RESTRICT taglist, const char *GTA_RESTRICT name, const char *GTA_RESTRICT value)
{
    if (!gta_check_tag_name(name) || !gta_check_tag_value(value))
    {
        return GTA_INVALID_DATA;
    }
    size_t newnam_size = strlen(name) + 1;
    size_t newval_size = strlen(value) + 1;

    ssize_t a = 0;
    ssize_t b = taglist->entries - 1;

    while (b >= a)
    {
        ssize_t c = (a + b) / 2;
        ssize_t d = taglist->sorted[c];
        int cmp = strcmp(taglist->names[d], name);
        if (cmp < 0)
        {
            a = c + 1;
        }
        else if (cmp > 0)
        {
            b = c - 1;
        }
        else
        {
            size_t oldval_size = strlen(taglist->values[d]) + 1;
            char *newval = malloc(newval_size);
            if (!newval)
            {
                return GTA_SYSTEM_ERROR;
            }
            memcpy(newval, value, newval_size);
            free(taglist->values[d]);
            taglist->values[d] = newval;
            taglist->encoded_size = taglist->encoded_size - oldval_size + newval_size;
            return GTA_OK;
        }
    }

    if ((size_t)taglist->entries == taglist->size)
    {
        if (taglist->entries == SSIZE_MAX
                || taglist->size > SIZE_MAX - gta_bufsize_inc
                || gta_size_overflow(taglist->size + gta_bufsize_inc, sizeof(char *))
                || gta_size_overflow(taglist->size + gta_bufsize_inc, sizeof(ssize_t)))
        {
            return GTA_OVERFLOW;
        }
        taglist->size += gta_bufsize_inc;
        char **old_names = taglist->names;
        char **old_values = taglist->values;
        ssize_t *old_sorted = taglist->sorted;
        taglist->names = malloc((size_t)taglist->size * sizeof(char *));
        taglist->values = malloc((size_t)taglist->size * sizeof(char *));
        taglist->sorted = malloc((size_t)taglist->size * sizeof(ssize_t));
        if (!taglist->names || !taglist->values || !taglist->sorted)
        {
            free(taglist->names);
            free(taglist->values);
            free(taglist->sorted);
            taglist->names = old_names;
            taglist->values = old_values;
            taglist->sorted = old_sorted;
            return GTA_SYSTEM_ERROR;
        }
        if (old_names)
        {
            memcpy(taglist->names, old_names, (size_t)(taglist->size - gta_bufsize_inc) * sizeof(char *));
            free(old_names);
        }
        if (old_values)
        {
            memcpy(taglist->values, old_values, (size_t)(taglist->size - gta_bufsize_inc) * sizeof(char *));
            free(old_values);
        }
        if (old_sorted)
        {
            memcpy(taglist->sorted, old_sorted, (size_t)(taglist->size - gta_bufsize_inc) * sizeof(ssize_t));
            free(old_sorted);
        }
    }

    char *newnam = malloc(newnam_size);
    char *newval = malloc(newval_size);
    if (!newnam || !newval)
    {
        free(newnam);
        free(newval);
        return GTA_SYSTEM_ERROR;
    }
    memcpy(newnam, name, newnam_size);
    memcpy(newval, value, newval_size);

    taglist->names[taglist->entries] = newnam;
    taglist->values[taglist->entries] = newval;
    taglist->encoded_size += newnam_size + newval_size;
    taglist->entries++;
    for (ssize_t i = taglist->entries - 1; i > a; i--)
    {
        taglist->sorted[i] = taglist->sorted[i - 1];
    }
    taglist->sorted[a] = taglist->entries - 1;
    return GTA_OK;
}

gta_result_t
gta_unset_tag(gta_taglist_t *GTA_RESTRICT taglist, const char *GTA_RESTRICT name)
{
    ssize_t a = 0;
    ssize_t b = taglist->entries - 1;

    while (b >= a)
    {
        ssize_t c = (a + b) / 2;
        ssize_t d = taglist->sorted[c];
        int cmp = strcmp(taglist->names[d], name);
        if (cmp < 0)
        {
            a = c + 1;
        }
        else if (cmp > 0)
        {
            b = c - 1;
        }
        else
        {
            size_t oldnam_size = strlen(taglist->names[d]) + 1;
            size_t oldval_size = strlen(taglist->values[d]) + 1;
            free(taglist->names[d]);
            free(taglist->values[d]);
            for (ssize_t i = d; i < taglist->entries - 1; i++)
            {
                taglist->names[i] = taglist->names[i + 1];
                taglist->values[i] = taglist->values[i + 1];
            }
            bool d_seen = false;
            for (ssize_t i = 0; i < taglist->entries - 1; i++)
            {
                ssize_t e = taglist->sorted[d_seen ? i + 1 : i];
                if (!d_seen && e == d)
                {
                    d_seen = true;
                    e = taglist->sorted[i + 1];
                }
                taglist->sorted[i] = (e > d ? e - 1 : e);
            }
            taglist->encoded_size -= oldnam_size + oldval_size;
            // TODO: Shrink the array if there are too many unused entries?
            taglist->entries--;
            return GTA_OK;
        }
    }
    return GTA_OK;
}

void
gta_unset_all_tags(gta_taglist_t *GTA_RESTRICT taglist)
{
    gta_destroy_taglist(taglist);
    gta_create_taglist(taglist);
}

gta_result_t
gta_clone_taglist(gta_taglist_t *GTA_RESTRICT dst_taglist,
        const gta_taglist_t *GTA_RESTRICT src_taglist)
{
    gta_taglist_t tmp_taglist;
    gta_create_taglist(&tmp_taglist);
    for (uintmax_t i = 0; i < gta_get_tags(src_taglist); i++)
    {
        gta_result_t r = gta_set_tag(&tmp_taglist,
                gta_get_tag_name(src_taglist, i),
                gta_get_tag_value(src_taglist, i));
        if (r != GTA_OK)
        {
            gta_destroy_taglist(&tmp_taglist);
            return r;
        }
    }
    gta_destroy_taglist(dst_taglist);
    memcpy(dst_taglist, &tmp_taglist, sizeof(gta_taglist_t));
    return GTA_OK;
}


/*
 *
 * Initialization and Deinitialization of Headers
 *
 */


gta_result_t
gta_create_header(gta_header_t *GTA_RESTRICT *GTA_RESTRICT header)
{
    *header = malloc(sizeof(gta_header_t));
    if (!*header)
    {
        return GTA_SYSTEM_ERROR;
    }
    gta_header_t *GTA_RESTRICT hdr = *header;
    hdr->host_endianness = true;
    hdr->compression = GTA_NONE;
    hdr->global_taglist = malloc(sizeof(gta_taglist_t));
    if (!hdr->global_taglist)
    {
        free(hdr);
        return GTA_SYSTEM_ERROR;
    }
    gta_create_taglist(hdr->global_taglist);
    hdr->components = 0;
    hdr->component_types = NULL;
    hdr->component_blob_sizes = NULL;
    hdr->component_taglists = NULL;
    hdr->element_size = 0;
    hdr->dimensions = 0;
    hdr->dimension_sizes = NULL;
    hdr->dimension_taglists = NULL;
    return GTA_OK;
}

gta_result_t
gta_clone_header(gta_header_t *GTA_RESTRICT dst_header,
        const gta_header_t *GTA_RESTRICT src_header)
{
    gta_result_t retval;
    gta_header_t *temp_header;

    retval = gta_create_header(&temp_header);
    if (retval != GTA_OK)
    {
        return retval;
    }

    temp_header->host_endianness = src_header->host_endianness;
    temp_header->compression = src_header->compression;
    for (uintmax_t i = 0; i < gta_get_tags(src_header->global_taglist); i++)
    {
        retval = gta_set_tag(temp_header->global_taglist,
                gta_get_tag_name(src_header->global_taglist, i),
                gta_get_tag_value(src_header->global_taglist, i));
        if (retval != GTA_OK)
        {
            goto exit;
        }
    }
    gta_type_t *types = malloc(src_header->components * sizeof(gta_type_t));
    if (!types)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    for (uintmax_t i = 0; i < src_header->components; i++)
    {
        types[i] = src_header->component_types[i];
    }
    retval = gta_set_components(temp_header, src_header->components,
            types, src_header->component_blob_sizes);
    free(types);
    if (retval != GTA_OK)
    {
        goto exit;
    }
    for (uintmax_t i = 0; i < src_header->components; i++)
    {
        for (uintmax_t j = 0; j < gta_get_tags(src_header->component_taglists[i]); j++)
        {
            retval = gta_set_tag(temp_header->component_taglists[i],
                    gta_get_tag_name(src_header->component_taglists[i], j),
                    gta_get_tag_value(src_header->component_taglists[i], j));
            if (retval != GTA_OK)
            {
                goto exit;
            }
        }
    }
    retval = gta_set_dimensions(temp_header, src_header->dimensions, src_header->dimension_sizes);
    if (retval != GTA_OK)
    {
        goto exit;
    }
    for (uintmax_t i = 0; i < src_header->dimensions; i++)
    {
        for (uintmax_t j = 0; j < gta_get_tags(src_header->dimension_taglists[i]); j++)
        {
            retval = gta_set_tag(temp_header->dimension_taglists[i],
                    gta_get_tag_name(src_header->dimension_taglists[i], j),
                    gta_get_tag_value(src_header->dimension_taglists[i], j));
            if (retval != GTA_OK)
            {
                goto exit;
            }
        }
    }

exit:
    if (retval == GTA_OK)
    {
        gta_destroy_taglist(dst_header->global_taglist);
        free(dst_header->global_taglist);
        free(dst_header->component_types);
        free(dst_header->component_blob_sizes);
        for (uintmax_t i = 0; i < dst_header->components; i++)
        {
            gta_destroy_taglist(dst_header->component_taglists[i]);
            free(dst_header->component_taglists[i]);
        }
        free(dst_header->component_taglists);
        free(dst_header->dimension_sizes);
        for (uintmax_t i = 0; i < dst_header->dimensions; i++)
        {
            gta_destroy_taglist(dst_header->dimension_taglists[i]);
            free(dst_header->dimension_taglists[i]);
        }
        free(dst_header->dimension_taglists);
        memcpy(dst_header, temp_header, sizeof(gta_header_t));
    }
    else
    {
        if (temp_header->global_taglist)
        {
            gta_destroy_taglist(temp_header->global_taglist);
            free(temp_header->global_taglist);
        }
        free(temp_header->component_types);
        free(temp_header->component_blob_sizes);
        if (temp_header->component_taglists)
        {
            for (uintmax_t i = 0; i < temp_header->components; i++)
            {
                gta_destroy_taglist(temp_header->component_taglists[i]);
                free(temp_header->component_taglists[i]);
            }
        }
        free(temp_header->component_taglists);
        free(temp_header->dimension_sizes);
        if (temp_header->dimension_taglists)
        {
            for (uintmax_t i = 0; i < temp_header->dimensions; i++)
            {
                gta_destroy_taglist(temp_header->dimension_taglists[i]);
                free(temp_header->dimension_taglists[i]);
            }
            free(temp_header->dimension_taglists);
        }
    }
    free(temp_header);
    return retval;
}

void
gta_destroy_header(gta_header_t *GTA_RESTRICT header)
{
    gta_destroy_taglist(header->global_taglist);
    free(header->global_taglist);
    free(header->component_types);
    free(header->component_blob_sizes);
    for (uintmax_t i = 0; i < header->components; i++)
    {
        gta_destroy_taglist(header->component_taglists[i]);
        free(header->component_taglists[i]);
    }
    free(header->component_taglists);
    free(header->dimension_sizes);
    for (uintmax_t i = 0; i < header->dimensions; i++)
    {
        gta_destroy_taglist(header->dimension_taglists[i]);
        free(header->dimension_taglists[i]);
    }
    free(header->dimension_taglists);
    free(header);
}


/*
 *
 * Read and Write Headers
 *
 */


static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW
gta_result_t
gta_append_element_to_array(
        void **array, size_t *array_size, size_t *array_elements,
        const void *element, size_t element_size)
{
    if (*array_elements == *array_size)
    {
        void *tmp_ptr;
        if (*array_size > SIZE_MAX - gta_bufsize_inc
                || gta_size_overflow(*array_size + gta_bufsize_inc, element_size))
        {
            return GTA_OVERFLOW;
        }
        *array_size += gta_bufsize_inc;
        tmp_ptr = realloc(*array, *array_size * element_size);
        if (!tmp_ptr)
        {
            free(*array);
            return GTA_SYSTEM_ERROR;
        }
        *array = tmp_ptr;
    }
    void *dst = (char *)(*array) + *array_elements * element_size;
    memcpy(dst, element, element_size);
    (*array_elements)++;
    return GTA_OK;
}

static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL
gta_result_t
gta_read_blob_from_chunk(const gta_header_t *GTA_RESTRICT header, gta_read_t read_fn, intptr_t userdata,
        void **chunk, size_t *chunk_size, size_t *chunk_index,
        void *blob, size_t blob_size)
{
    gta_result_t retval = GTA_OK;
    char *cblob = blob;
    char *cchunk = *chunk;
    for (size_t i = 0; i < blob_size; i++)
    {
        if (*chunk_index == *chunk_size)
        {
            free(*chunk);
            *chunk = NULL;
            retval = gta_read_chunk(header, chunk, chunk_size, read_fn, userdata);
            if (retval != GTA_OK)
            {
                return retval;
            }
            if (*chunk_size == 0)
            {
                return GTA_INVALID_DATA;
            }
            *chunk_index = 0;
            cchunk = *chunk;
        }
        cblob[i] = cchunk[(*chunk_index)++];
    }
    return retval;
}

static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL
gta_result_t
gta_read_taglist_from_chunk(const gta_header_t *GTA_RESTRICT header, gta_read_t read_fn, intptr_t userdata,
        void **chunk, size_t *chunk_size, size_t *chunk_index,
        gta_taglist_t **taglist)
{
    void *name = NULL;
    size_t name_len = 0;
    size_t name_size = 0;
    void *value = NULL;
    size_t value_len = 0;
    size_t value_size = 0;
    bool in_name = true;
    gta_result_t retval = GTA_OK;

    *taglist = malloc(sizeof(gta_taglist_t));
    if (!*taglist)
    {
        return GTA_SYSTEM_ERROR;
    }
    gta_create_taglist(*taglist);
    for (;;)
    {
        char c;
        retval = gta_read_blob_from_chunk(header, read_fn, userdata,
                chunk, chunk_size, chunk_index, &c, sizeof(char));
        if (retval != GTA_OK)
        {
            goto exit;
        }
        if (in_name && name_len == 0 && c == '\0')
        {
            break;
        }
        if (in_name)
        {
            retval = gta_append_element_to_array(&name, &name_size, &name_len, &c, sizeof(char));
            if (retval != GTA_OK)
            {
                goto exit;
            }
            if (c == '\0')
            {
                in_name = false;
            }
        }
        else
        {
            retval = gta_append_element_to_array(&value, &value_size, &value_len, &c, sizeof(char));
            if (retval != GTA_OK)
            {
                goto exit;
            }
            if (c == '\0')
            {
                retval = gta_set_tag(*taglist, name, value);
                if (retval != GTA_OK)
                {
                    goto exit;
                }
                name_len = 0;
                value_len = 0;
                in_name = true;
            }
        }
    }

exit:
    free(name);
    free(value);
    if (retval != GTA_OK)
    {
        gta_destroy_taglist(*taglist);
        free(*taglist);
        *taglist = NULL;
    }
    return retval;
}

gta_result_t
gta_read_header(gta_header_t *GTA_RESTRICT header, gta_read_t read_fn, intptr_t userdata)
{
    uint8_t firstblock[6];
    int input_error = false;
    gta_result_t retval = GTA_OK;
    size_t r;

    /* Use a temp header to avoid changing the given header unless we read everything successfully */
    gta_header_t *temp_header = NULL;
    retval = gta_create_header(&temp_header);
    if (retval != GTA_OK)
    {
        return retval;
    }

    /* Read first block */
    r = read_fn(userdata, firstblock, 6, &input_error);
    if (input_error)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }
    if (r < 6)
    {
        retval = GTA_UNEXPECTED_EOF;
        goto exit;
    }
    if (strncmp((char *)firstblock, "GTA", 3) != 0)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }
    if (firstblock[3] != 1)
    {
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
    }
    if (firstblock[4] & 0xfc)
    {
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
    }
    bool big_endian = (firstblock[4] & 0x01);
#if WORDS_BIGENDIAN
    temp_header->host_endianness = big_endian;
#else
    temp_header->host_endianness = !big_endian;
#endif
    if (firstblock[5] != GTA_NONE
            && firstblock[5] != GTA_ZLIB
            && firstblock[5] != GTA_ZLIB1
            && firstblock[5] != GTA_ZLIB2
            && firstblock[5] != GTA_ZLIB3
            && firstblock[5] != GTA_ZLIB4
            && firstblock[5] != GTA_ZLIB5
            && firstblock[5] != GTA_ZLIB6
            && firstblock[5] != GTA_ZLIB7
            && firstblock[5] != GTA_ZLIB8
            && firstblock[5] != GTA_ZLIB9
            && firstblock[5] != GTA_BZIP2
            && firstblock[5] != GTA_XZ)
    {
        retval = GTA_UNSUPPORTED_DATA;
        goto exit;
    }
    temp_header->compression = firstblock[5];

    /* Read rest of header from chunk list */

    void *chunk = NULL;
    size_t chunk_size = 0;
    size_t chunk_index = 0;

    // Read component list
    {
        void *comp_array = NULL;
        size_t comp_array_size = 0;
        size_t comp_array_elements = 0;
        void *bs_array = NULL;
        size_t bs_array_size = 0;
        size_t bs_array_elements = 0;
        size_t element_size = 0;
        for (;;)
        {
            uint8_t type;
            retval = gta_read_blob_from_chunk(temp_header, read_fn, userdata,
                    &chunk, &chunk_size, &chunk_index,
                    &type, sizeof(uint8_t));
            if (retval != GTA_OK)
            {
                free(comp_array);
                free(bs_array);
                goto exit;
            }
            if (type == 0xff)
            {
                break;
            }
            uint64_t size;
            switch (type)
            {
            case GTA_BLOB:
                break;
            case GTA_INT8:
            case GTA_UINT8:
                size = 1;
                break;
            case GTA_INT16:
            case GTA_UINT16:
                size = 2;
                break;
            case GTA_INT32:
            case GTA_UINT32:
            case GTA_FLOAT32:
                size = 4;
                break;
            case GTA_INT64:
            case GTA_UINT64:
            case GTA_FLOAT64:
            case GTA_CFLOAT32:
                size = 8;
                break;
            case GTA_INT128:
            case GTA_UINT128:
            case GTA_FLOAT128:
            case GTA_CFLOAT64:
                size = 16;
                break;
            case GTA_CFLOAT128:
                size = 32;
                break;
            default:
                retval = GTA_INVALID_DATA;
                free(comp_array);
                free(bs_array);
                goto exit;
                break;
            }
            if (type == GTA_BLOB)
            {
                retval = gta_read_blob_from_chunk(temp_header, read_fn, userdata,
                        &chunk, &chunk_size, &chunk_index,
                        &size, sizeof(uint64_t));
                if (retval != GTA_OK)
                {
                    free(comp_array);
                    free(bs_array);
                    goto exit;
                }
                if (gta_data_needs_endianness_swapping(temp_header))
                {
                    gta_swap_endianness_64(&size);
                }
                if (size == 0)
                {
                    retval = GTA_INVALID_DATA;
                    free(comp_array);
                    free(bs_array);
                    goto exit;
                }
                uintmax_t bigsize = size;
                retval = gta_append_element_to_array(
                        &bs_array, &bs_array_size, &bs_array_elements,
                        &bigsize, sizeof(uintmax_t));
                if (retval != GTA_OK)
                {
                    free(comp_array);
                    free(bs_array);
                    goto exit;
                }
            }
            if (element_size > UINTMAX_MAX - size)
            {
                retval = GTA_OVERFLOW;
                free(comp_array);
                free(bs_array);
                goto exit;
            }
            element_size += size;
            retval = gta_append_element_to_array(
                    &comp_array, &comp_array_size, &comp_array_elements,
                    &type, sizeof(uint8_t));
            if (retval != GTA_OK)
            {
                free(comp_array);
                free(bs_array);
                goto exit;
            }
        }
        temp_header->components = comp_array_elements;
        temp_header->element_size = element_size;
        if (comp_array_elements > 0)
        {
            temp_header->component_types = realloc(comp_array, comp_array_elements * sizeof(uint8_t));
            if (!temp_header->component_types)
            {
                free(comp_array);
                retval = GTA_SYSTEM_ERROR;
                goto exit;
            }
        }
        if (bs_array_elements > 0)
        {
            temp_header->component_blob_sizes = realloc(bs_array, bs_array_elements * sizeof(uintmax_t));
            if (!temp_header->component_blob_sizes)
            {
                free(bs_array);
                retval = GTA_SYSTEM_ERROR;
                goto exit;
            }
        }
    }

    // Read dimension list
    {
        void *dim_array = NULL;
        size_t dim_array_size = 0;
        size_t dim_array_elements = 0;
        uintmax_t data_size = temp_header->element_size;
        for (;;)
        {
            uint64_t size;
            retval = gta_read_blob_from_chunk(temp_header, read_fn, userdata,
                    &chunk, &chunk_size, &chunk_index,
                    &size, sizeof(uint64_t));
            if (retval != GTA_OK)
            {
                free(dim_array);
                goto exit;
            }
            if (gta_data_needs_endianness_swapping(temp_header))
            {
                gta_swap_endianness_64(&size);
            }
            if (size == 0)
            {
                break;
            }
            if (gta_uintmax_overflow(data_size, size))
            {
                retval = GTA_OVERFLOW;
                free(dim_array);
                goto exit;
            }
            data_size *= size;
            uintmax_t bigsize = size;
            retval = gta_append_element_to_array(
                    &dim_array, &dim_array_size, &dim_array_elements,
                    &bigsize, sizeof(uintmax_t));
            if (retval != GTA_OK)
            {
                free(dim_array);
                goto exit;
            }
        }
        temp_header->dimensions = dim_array_elements;
        if (dim_array_elements > 0)
        {
            temp_header->dimension_sizes = realloc(dim_array, dim_array_elements * sizeof(uintmax_t));
            if (!temp_header->dimension_sizes)
            {
                free(dim_array);
                retval = GTA_SYSTEM_ERROR;
                goto exit;
            }
        }
    }

    // Read tag lists
    {
        gta_taglist_t *taglist;
        retval = gta_read_taglist_from_chunk(header, read_fn, userdata,
                &chunk, &chunk_size, &chunk_index, &taglist);
        if (retval != GTA_OK)
        {
            goto exit;
        }
        gta_destroy_taglist(temp_header->global_taglist);
        free(temp_header->global_taglist);
        temp_header->global_taglist = taglist;
        void *tl_array = NULL;
        size_t tl_array_size = 0;
        size_t tl_array_elements = 0;
        for (size_t i = 0; i < temp_header->components; i++)
        {
            taglist = NULL;
            if ((retval = gta_read_taglist_from_chunk(header, read_fn, userdata,
                            &chunk, &chunk_size, &chunk_index, &taglist)) != GTA_OK
                    || (retval = gta_append_element_to_array(
                            &tl_array, &tl_array_size, &tl_array_elements,
                            &taglist, sizeof(gta_taglist_t *))) != GTA_OK)
            {
                if (taglist)
                {
                    gta_destroy_taglist(taglist);
                }
                for (size_t j = 0; j < i; j++)
                {
                    gta_taglist_t *tl = ((gta_taglist_t **)tl_array)[j];
                    gta_destroy_taglist(tl);
                    free(tl);
                }
                free(tl_array);
                goto exit;
            }
        }
        if (tl_array_elements > 0)
        {
            temp_header->component_taglists = realloc(tl_array, tl_array_elements * sizeof(gta_taglist_t *));
            if (!temp_header->component_taglists)
            {
                free(tl_array);
                retval = GTA_SYSTEM_ERROR;
                goto exit;
            }
        }
        tl_array = NULL;
        tl_array_size = 0;
        tl_array_elements = 0;
        for (size_t i = 0; i < temp_header->dimensions; i++)
        {
            taglist = NULL;
            if ((retval = gta_read_taglist_from_chunk(header, read_fn, userdata,
                            &chunk, &chunk_size, &chunk_index, &taglist)) != GTA_OK
                    || (retval = gta_append_element_to_array(
                            &tl_array, &tl_array_size, &tl_array_elements,
                            &taglist, sizeof(gta_taglist_t *))) != GTA_OK)
            {
                if (taglist)
                {
                    gta_destroy_taglist(taglist);
                }
                for (size_t j = 0; j < i; j++)
                {
                    gta_taglist_t *tl = ((gta_taglist_t **)tl_array)[j];
                    gta_destroy_taglist(tl);
                    free(tl);
                }
                free(tl_array);
                goto exit;
            }
        }
        if (tl_array_elements > 0)
        {
            temp_header->dimension_taglists = realloc(tl_array, tl_array_elements * sizeof(gta_taglist_t *));
            if (!temp_header->dimension_taglists)
            {
                free(tl_array);
                retval = GTA_SYSTEM_ERROR;
                goto exit;
            }
        }
    }

    // Make sure that the chunk is now empty
    if (chunk_index != chunk_size)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }

    // Read an empty chunk that marks the end of the chunk list
    free(chunk);
    chunk = NULL;
    retval = gta_read_chunk(header, &chunk, &chunk_size, read_fn, userdata);
    if (retval != GTA_OK)
    {
        goto exit;
    }
    if (chunk_size != 0)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }

exit:
    if (retval == GTA_OK)
    {
        gta_destroy_taglist(header->global_taglist);
        free(header->global_taglist);
        free(header->component_types);
        free(header->component_blob_sizes);
        for (size_t i = 0; i < header->components; i++)
        {
            gta_destroy_taglist(header->component_taglists[i]);
            free(header->component_taglists[i]);
        }
        free(header->component_taglists);
        free(header->dimension_sizes);
        for (size_t i = 0; i < header->dimensions; i++)
        {
            gta_destroy_taglist(header->dimension_taglists[i]);
            free(header->dimension_taglists[i]);
        }
        free(header->dimension_taglists);
        memcpy(header, temp_header, sizeof(gta_header_t));
    }
    else
    {
        gta_destroy_taglist(temp_header->global_taglist);
        free(temp_header->global_taglist);
        free(temp_header->component_types);
        free(temp_header->component_blob_sizes);
        if (temp_header->component_taglists)
        {
            for (size_t i = 0; i < temp_header->components; i++)
            {
                gta_destroy_taglist(temp_header->component_taglists[i]);
                free(temp_header->component_taglists[i]);
            }
            free(temp_header->component_taglists);
        }
        free(temp_header->dimension_sizes);
        if (temp_header->dimension_taglists)
        {
            for (size_t i = 0; i < temp_header->dimensions; i++)
            {
                gta_destroy_taglist(temp_header->dimension_taglists[i]);
                free(temp_header->dimension_taglists[i]);
            }
            free(temp_header->dimension_taglists);
        }
    }
    free(temp_header);
    return retval;
}

gta_result_t
gta_read_header_from_stream(gta_header_t *GTA_RESTRICT header, FILE *GTA_RESTRICT f)
{
    return gta_read_header(header, gta_read_stream, (intptr_t)f);
}

gta_result_t
gta_read_header_from_fd(gta_header_t *GTA_RESTRICT header, int fd)
{
    return gta_read_header(header, gta_read_fd, fd);
}

static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL
gta_result_t
gta_write_blob_to_chunk(const gta_header_t *GTA_RESTRICT header, gta_write_t write_fn, intptr_t userdata,
        void *chunk, size_t chunk_size, size_t *chunk_index,
        const void *blob, size_t blob_size)
{
    gta_result_t retval = GTA_OK;
    const char *cblob = blob;
    char *cchunk = chunk;
    for (size_t i = 0; i < blob_size; i++)
    {
        cchunk[(*chunk_index)++] = cblob[i];
        if (*chunk_index == chunk_size)
        {
            retval = gta_write_chunk(header, chunk, *chunk_index, write_fn, userdata);
            if (retval != GTA_OK)
            {
                return retval;
            }
            *chunk_index = 0;
        }
    }
    return retval;
}

static GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL
gta_result_t
gta_write_taglist_to_chunk(const gta_header_t *GTA_RESTRICT header, gta_write_t write_fn, intptr_t userdata,
        void *chunk, size_t chunk_size, size_t *chunk_index, const gta_taglist_t *GTA_RESTRICT taglist)
{
    gta_result_t retval = GTA_OK;
    for (uintmax_t i = 0; i < gta_get_tags(taglist); i++)
    {
        const char *name = gta_get_tag_name(taglist, i);
        retval = gta_write_blob_to_chunk(header, write_fn, userdata, chunk, chunk_size, chunk_index,
                name, strlen(name) + 1);
        if (retval != GTA_OK)
        {
            return retval;
        }
        const char *value = gta_get_tag_value(taglist, i);
        retval = gta_write_blob_to_chunk(header, write_fn, userdata, chunk, chunk_size, chunk_index,
                value, strlen(value) + 1);
        if (retval != GTA_OK)
        {
            return retval;
        }
    }
    char taglist_end = '\0';
    retval = gta_write_blob_to_chunk(header, write_fn, userdata, chunk, chunk_size, chunk_index,
            &taglist_end, sizeof(char));
    return retval;
}

gta_result_t
gta_write_header(const gta_header_t *GTA_RESTRICT header, gta_write_t write_fn, intptr_t userdata)
{
    uint8_t firstblock[6];
    int output_error = false;
    gta_result_t retval = GTA_OK;
    size_t r;

    /* Write first block */
    firstblock[0] = 'G';
    firstblock[1] = 'T';
    firstblock[2] = 'A';
    firstblock[3] = 1;
    firstblock[4] = 0;
#if WORDS_BIGENDIAN
    firstblock[4] |= 0x01;
#endif
    firstblock[5] = GTA_NONE;
    errno = 0;
    r = write_fn(userdata, firstblock, 6, &output_error);
    if (output_error || r < 6)
    {
        if (errno == 0)
        {
            errno = EIO;
        }
        return GTA_SYSTEM_ERROR;
    }

    /* Write rest of header in chunklist */

    // Compute required space for header
    size_t required_size = 6;
    required_size += header->components * sizeof(uint8_t);
    required_size += 1 * sizeof(uint8_t);
    for (size_t i = 0; i < header->components; i++)
    {
        required_size += header->component_taglists[i]->encoded_size;
        if (header->component_types[i] == GTA_BLOB)
        {
            required_size += sizeof(uint64_t);
        }
    }
    required_size += header->dimensions * sizeof(uint64_t);
    required_size += 1 * sizeof(uint64_t);
    for (size_t i = 0; i < header->dimensions; i++)
    {
        required_size += header->dimension_taglists[i]->encoded_size;
    }
    required_size += header->global_taglist->encoded_size;
    // Allocate a chunk
    void *chunk = NULL;
    size_t chunk_size = 0;
    size_t chunk_index = 0;
    chunk_size = (required_size < gta_max_chunk_size ? required_size : gta_max_chunk_size);
    chunk = malloc(chunk_size);
    if (!chunk)
    {
        retval = GTA_SYSTEM_ERROR;
        goto exit;
    }

    // Write component list
    size_t blob_size_index = 0;
    for (size_t i = 0; i < header->components; i++)
    {
        uint8_t type = header->component_types[i];
        retval = gta_write_blob_to_chunk(header, write_fn, userdata, chunk, chunk_size, &chunk_index,
                &type, sizeof(uint8_t));
        if (retval != GTA_OK)
        {
            goto exit;
        }
        if (type == GTA_BLOB)
        {
            uint64_t blob_size = header->component_blob_sizes[blob_size_index];
            retval = gta_write_blob_to_chunk(header, write_fn, userdata, chunk, chunk_size, &chunk_index,
                    &blob_size, sizeof(uint64_t));
            if (retval != GTA_OK)
            {
                goto exit;
            }
            blob_size_index++;
        }
    }
    uint8_t componentlist_end = 0xff;
    retval = gta_write_blob_to_chunk(header, write_fn, userdata, chunk, chunk_size, &chunk_index,
            &componentlist_end, sizeof(uint8_t));
    if (retval != GTA_OK)
    {
        goto exit;
    }

    // Write dimension list
    for (size_t i = 0; i < header->dimensions; i++)
    {
        uint64_t dimension_size = header->dimension_sizes[i];
        retval = gta_write_blob_to_chunk(header, write_fn, userdata, chunk, chunk_size, &chunk_index,
                &dimension_size, sizeof(uint64_t));
        if (retval != GTA_OK)
        {
            goto exit;
        }
    }
    uint64_t dimensionlist_end = 0;
    retval = gta_write_blob_to_chunk(header, write_fn, userdata, chunk, chunk_size, &chunk_index,
            &dimensionlist_end, sizeof(uint64_t));
    if (retval != GTA_OK)
    {
        goto exit;
    }

    // Write tag lists
    retval = gta_write_taglist_to_chunk(header, write_fn, userdata, chunk, chunk_size, &chunk_index,
            header->global_taglist);
    if (retval != GTA_OK)
    {
        goto exit;
    }
    for (size_t i = 0; i < header->components; i++)
    {
        retval = gta_write_taglist_to_chunk(header, write_fn, userdata, chunk, chunk_size, &chunk_index,
                header->component_taglists[i]);
        if (retval != GTA_OK)
        {
            goto exit;
        }
    }
    for (size_t i = 0; i < header->dimensions; i++)
    {
        retval = gta_write_taglist_to_chunk(header, write_fn, userdata, chunk, chunk_size, &chunk_index,
                header->dimension_taglists[i]);
        if (retval != GTA_OK)
        {
            goto exit;
        }
    }

    // Flush the chunk
    if (chunk_index > 0)
    {
        retval = gta_write_chunk(header, chunk, chunk_index, write_fn, userdata);
        if (retval != GTA_OK)
        {
            goto exit;
        }
    }

    // An empty chunk marks the end
    retval = gta_write_chunk(header, NULL, 0, write_fn, userdata);
    if (retval != GTA_OK)
    {
        goto exit;
    }

exit:
    free(chunk);
    return retval;
}

gta_result_t
gta_write_header_to_stream(const gta_header_t *GTA_RESTRICT header, FILE *GTA_RESTRICT f)
{
    return gta_write_header(header, gta_write_stream, (intptr_t)f);
}

gta_result_t
gta_write_header_to_fd(const gta_header_t *GTA_RESTRICT header, int fd)
{
    return gta_write_header(header, gta_write_fd, fd);
}


/*
 *
 * Access Headers
 *
 */


const gta_taglist_t *
gta_get_global_taglist_const(const gta_header_t *GTA_RESTRICT header)
{
    return header->global_taglist;
}

gta_taglist_t *
gta_get_global_taglist(gta_header_t *GTA_RESTRICT header)
{
    return header->global_taglist;
}

uintmax_t
gta_get_element_size(const gta_header_t *GTA_RESTRICT header)
{
    return header->element_size;
}

uintmax_t
gta_get_components(const gta_header_t *GTA_RESTRICT header)
{
    return header->components;
}

gta_type_t
gta_get_component_type(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
{
    return header->component_types[i];
}

uintmax_t
gta_get_component_size(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
{
    gta_type_t type = header->component_types[i];
    uintmax_t size = 0;
    switch (type)
    {
    case GTA_INT8:
    case GTA_UINT8:
        size = 1;
        break;
    case GTA_INT16:
    case GTA_UINT16:
        size = 2;
        break;
    case GTA_INT32:
    case GTA_UINT32:
    case GTA_FLOAT32:
        size = 4;
        break;
    case GTA_INT64:
    case GTA_UINT64:
    case GTA_FLOAT64:
    case GTA_CFLOAT32:
        size = 8;
        break;
    case GTA_INT128:
    case GTA_UINT128:
    case GTA_FLOAT128:
    case GTA_CFLOAT64:
        size = 16;
        break;
    case GTA_CFLOAT128:
        size = 32;
        break;
    case GTA_BLOB:
        {
            size_t blob_size_index = 0;
            for (size_t j = 0; j < i; j++)
            {
                if (header->component_types[j] == GTA_BLOB)
                {
                    blob_size_index++;
                }
            }
            size = header->component_blob_sizes[blob_size_index];
        }
        break;
    }
    return size;
}

const gta_taglist_t *
gta_get_component_taglist_const(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
{
    return header->component_taglists[i];
}

gta_taglist_t *
gta_get_component_taglist(gta_header_t *GTA_RESTRICT header, uintmax_t i)
{
    return header->component_taglists[i];
}

gta_result_t
gta_set_components(gta_header_t *GTA_RESTRICT header, uintmax_t n,
        const gta_type_t *GTA_RESTRICT types, const uintmax_t *GTA_RESTRICT sizes)
{
    if (n > UINT64_MAX || n > SIZE_MAX
            || gta_size_overflow(n, sizeof(uint8_t))
            || gta_size_overflow(n, sizeof(gta_taglist_t *)))
    {
        return GTA_OVERFLOW;
    }

    uintmax_t element_size = 0;
    uintmax_t data_size = 0;
    size_t blobs = 0;

    for (size_t i = 0; i < n; i++)
    {
        uintmax_t size = 0;
        switch (types[i])
        {
        case GTA_BLOB:
            size = sizes[blobs++];
            if (size < 1 || size > UINT64_MAX)
            {
                return GTA_OVERFLOW;
            }
            break;
        case GTA_INT8:
        case GTA_UINT8:
            size = 1;
            break;
        case GTA_INT16:
        case GTA_UINT16:
            size = 2;
            break;
        case GTA_INT32:
        case GTA_UINT32:
        case GTA_FLOAT32:
            size = 4;
            break;
        case GTA_INT64:
        case GTA_UINT64:
        case GTA_FLOAT64:
        case GTA_CFLOAT32:
            size = 8;
            break;
        case GTA_INT128:
        case GTA_UINT128:
        case GTA_FLOAT128:
        case GTA_CFLOAT64:
            size = 16;
            break;
        case GTA_CFLOAT128:
            size = 32;
            break;
        default:
            return GTA_UNSUPPORTED_DATA;
            break;
        }
        if (element_size > UINTMAX_MAX - size)
        {
            return GTA_OVERFLOW;
        }
        element_size += size;
    }
    data_size = element_size;
    for (size_t i = 0; i < header->dimensions; i++)
    {
        if (gta_uintmax_overflow(data_size, header->dimension_sizes[i]))
        {
            return GTA_OVERFLOW;
        }
        data_size *= header->dimension_sizes[i];
    }

    uint8_t *my_types = NULL;
    uintmax_t *my_blob_sizes = NULL;
    gta_taglist_t **my_taglists = NULL;
    if (n > 0)
    {
        my_types = malloc(n * sizeof(uint8_t));
        if (blobs > 0)
        {
            my_blob_sizes = malloc(blobs * sizeof(uintmax_t));
        }
        my_taglists = malloc(n * sizeof(gta_taglist_t *));
        if (!my_types || (blobs > 0 && !my_blob_sizes) || !my_taglists)
        {
            free(my_types);
            free(my_blob_sizes);
            free(my_taglists);
            return GTA_SYSTEM_ERROR;
        }
        for (size_t i = 0; i < n; i++)
        {
            my_types[i] = types[i];
        }
        if (blobs > 0)
        {
            memcpy(my_blob_sizes, sizes, blobs * sizeof(uintmax_t));
        }
        for (size_t i = 0; i < n; i++)
        {
            my_taglists[i] = malloc(sizeof(gta_taglist_t));
            if (!my_taglists[i])
            {
                for (size_t j = 0; j < i; j++)
                {
                    gta_destroy_taglist(my_taglists[j]);
                    free(my_taglists[j]);
                }
                free(my_types);
                free(my_blob_sizes);
                free(my_taglists);
                return GTA_SYSTEM_ERROR;
            }
            gta_create_taglist(my_taglists[i]);
        }
    }

    for (size_t i = 0; i < header->components; i++)
    {
        gta_destroy_taglist(header->component_taglists[i]);
        free(header->component_taglists[i]);
    }
    free(header->component_types);
    free(header->component_blob_sizes);
    free(header->component_taglists);

    header->components = n;
    header->component_types = my_types;
    header->component_blob_sizes = my_blob_sizes;
    header->component_taglists = my_taglists;
    header->element_size = element_size;

    return GTA_OK;
}

uintmax_t
gta_get_dimensions(const gta_header_t *GTA_RESTRICT header)
{
    return header->dimensions;
}

uintmax_t
gta_get_dimension_size(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
{
    return header->dimension_sizes[i];
}

const gta_taglist_t *
gta_get_dimension_taglist_const(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
{
    return header->dimension_taglists[i];
}

gta_taglist_t *
gta_get_dimension_taglist(gta_header_t *GTA_RESTRICT header, uintmax_t i)
{
    return header->dimension_taglists[i];
}

gta_result_t
gta_set_dimensions(gta_header_t *GTA_RESTRICT header, uintmax_t n, const uintmax_t *GTA_RESTRICT sizes)
{
    uintmax_t data_size = header->element_size;

    if (n > UINT64_MAX || n > SIZE_MAX
            || gta_size_overflow(n, sizeof(gta_taglist_t *))
            || gta_size_overflow(n, sizeof(uintmax_t)))
    {
        return GTA_OVERFLOW;
    }
    for (size_t i = 0; i < n; i++)
    {
        if (sizes[i] < 1)
        {
            return GTA_INVALID_DATA;
        }
        if (sizes[i] > UINT64_MAX)
        {
            return GTA_OVERFLOW;
        }
        if (gta_uintmax_overflow(data_size, sizes[i]))
        {
            return GTA_OVERFLOW;
        }
        data_size *= sizes[i];
    }

    uintmax_t *my_sizes = NULL;
    gta_taglist_t **my_taglists = NULL;
    if (n > 0)
    {
        my_sizes = malloc(n * sizeof(uintmax_t));
        my_taglists = malloc(n * sizeof(gta_taglist_t *));
        if (!my_sizes || !my_taglists)
        {
            free(my_sizes);
            free(my_taglists);
            return GTA_SYSTEM_ERROR;
        }
        memcpy(my_sizes, sizes, n * sizeof(uintmax_t));
        for (size_t i = 0; i < n; i++)
        {
            my_taglists[i] = malloc(sizeof(gta_taglist_t));
            if (!my_taglists[i])
            {
                for (size_t j = 0; j < i; j++)
                {
                    gta_destroy_taglist(my_taglists[j]);
                    free(my_taglists[j]);
                }
                free(my_sizes);
                free(my_taglists);
                return GTA_SYSTEM_ERROR;
            }
            gta_create_taglist(my_taglists[i]);
        }
    }

    for (size_t i = 0; i < header->dimensions; i++)
    {
        gta_destroy_taglist(header->dimension_taglists[i]);
        free(header->dimension_taglists[i]);
    }
    free(header->dimension_sizes);
    free(header->dimension_taglists);

    header->dimensions = n;
    header->dimension_sizes = my_sizes;
    header->dimension_taglists = my_taglists;

    return GTA_OK;
}

uintmax_t
gta_get_elements(const gta_header_t *GTA_RESTRICT header)
{
    if (header->dimensions == 0)
    {
        return 0;
    }
    else
    {
        uintmax_t elements = header->dimension_sizes[0];
        for (uintmax_t i = 1; i < header->dimensions; i++)
        {
            elements *= header->dimension_sizes[i];
        }
        return elements;
    }
}

uintmax_t
gta_get_data_size(const gta_header_t *GTA_RESTRICT header)
{
    return gta_get_element_size(header) * gta_get_elements(header);
}

gta_compression_t
gta_get_compression(const gta_header_t *GTA_RESTRICT header)
{
    /* We do not support compression anymore. This function will be removed in
     * a future version. */
    return header->compression;
}

void
gta_set_compression(gta_header_t *GTA_RESTRICT header, gta_compression_t compression)
{
    /* We do not support compression anymore. This function does nothing and
     * will be removed in a future version. */
    (void)header;
    (void)compression;
}


/*
 *
 * In-Memory Data Access
 *
 */


void
gta_linear_index_to_indices(const gta_header_t *GTA_RESTRICT header, uintmax_t index, uintmax_t *indices)
{
    uintmax_t multiplied_dim_sizes = gta_get_elements(header);
    for (uintmax_t i = 0; i < gta_get_dimensions(header); i++)
    {
        uintmax_t j = gta_get_dimensions(header) - 1 - i;
        multiplied_dim_sizes /= gta_get_dimension_size(header, j);
        indices[j] = index / multiplied_dim_sizes;
        index -= indices[j] * multiplied_dim_sizes;
    }
}

uintmax_t
gta_indices_to_linear_index(const gta_header_t *GTA_RESTRICT header, const uintmax_t *indices)
{
    uintmax_t dim_product = 1;
    uintmax_t index = indices[0];
    for (uintmax_t i = 1; i < gta_get_dimensions(header); i++)
    {
        dim_product *= gta_get_dimension_size(header, i - 1);
        index += indices[i] * dim_product;
    }
    return index;
}

const void *
gta_get_element_const(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, const uintmax_t *GTA_RESTRICT indices)
{
    // We know that size_t does not overflow because all the data is in a buffer
    size_t index = gta_indices_to_linear_index(header, indices);
    const char *ptr = data;
    return ptr + index * gta_get_element_size(header);
}

void *
gta_get_element(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, const uintmax_t *GTA_RESTRICT indices)
{
    return (void *)gta_get_element_const(header, data, indices);
}

const void *
gta_get_element_linear_const(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, uintmax_t index)
{
    return ((const char *)data) + index * gta_get_element_size(header);
}

void *
gta_get_element_linear(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, uintmax_t index)
{
    return (void *)gta_get_element_linear_const(header, data, index);
}

const void *
gta_get_component_const(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT element, uintmax_t i)
{
    // We know that size_t does not overflow because all the data is in a buffer
    const char *c = element;
    size_t blob_size_index = 0;
    for (uintmax_t j = 0; j < i; j++)
    {
        switch (header->component_types[j])
        {
        case GTA_BLOB:
            c += header->component_blob_sizes[blob_size_index++];
            break;
        case GTA_INT8:
        case GTA_UINT8:
            c += 1;
            break;
        case GTA_INT16:
        case GTA_UINT16:
            c += 2;
            break;
        case GTA_INT32:
        case GTA_UINT32:
        case GTA_FLOAT32:
            c += 4;
            break;
        case GTA_INT64:
        case GTA_UINT64:
        case GTA_FLOAT64:
        case GTA_CFLOAT32:
            c += 8;
            break;
        case GTA_INT128:
        case GTA_UINT128:
        case GTA_FLOAT128:
        case GTA_CFLOAT64:
            c += 16;
            break;
        case GTA_CFLOAT128:
            c += 32;
            break;
        }
    }
    return c;
}

void *
gta_get_component(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT element, uintmax_t i)
{
    return (void *)gta_get_component_const(header, element, i);
}


/*
 *
 * Read and Write Complete Arrays
 *
 */


gta_result_t
gta_read_data(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, gta_read_t read_fn, intptr_t userdata)
{
    // We know that the data size fits into size_t, because the caller already allocated a buffer for all the data.
    if (gta_get_compression(header) != GTA_NONE)
    {
#if WITH_COMPRESSION
        char *data_ptr = data;
        size_t remaining_size = gta_get_data_size(header);
        void *chunk;
        size_t chunk_size;
        gta_result_t retval;

        for (;;)
        {
            retval = gta_read_chunk(header, &chunk, &chunk_size, read_fn, userdata);
            if (retval != GTA_OK)
            {
                return retval;
            }
            if (chunk_size == 0)
            {
                if (remaining_size == 0)
                {
                    break;
                }
                else
                {
                    return GTA_INVALID_DATA;
                }
            }
            if (chunk_size > remaining_size)
            {
                free(chunk);
                return GTA_INVALID_DATA;
            }
            memcpy(data_ptr, chunk, chunk_size);
            free(chunk);
            remaining_size -= chunk_size;
            data_ptr += chunk_size;
        }
#else
        return GTA_UNSUPPORTED_DATA;
#endif
    }
    else
    {
        int input_error = false;
        size_t r = read_fn(userdata, data, gta_get_data_size(header), &input_error);
        if (input_error)
        {
            return GTA_SYSTEM_ERROR;
        }
        if (r < gta_get_data_size(header))
        {
            return GTA_UNEXPECTED_EOF;
        }
    }
    if (gta_data_needs_endianness_swapping(header))
    {
        for (uintmax_t i = 0; i < gta_get_elements(header); i++)
        {
            void *e = gta_get_element_linear(header, data, i);
            gta_swap_element_endianness(header, e);
        }
    }
    return GTA_OK;
}

gta_result_t
gta_read_data_from_stream(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, FILE *GTA_RESTRICT f)
{
    return gta_read_data(header, data, gta_read_stream, (intptr_t)f);
}

gta_result_t
gta_read_data_from_fd(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, int fd)
{
    return gta_read_data(header, data, gta_read_fd, fd);
}

gta_result_t
gta_skip_data(const gta_header_t *GTA_RESTRICT header, gta_read_t read_fn, gta_seek_t seek_fn, intptr_t userdata)
{
    gta_result_t retval;

    if (gta_get_compression(header) != GTA_NONE)
    {
#if WITH_COMPRESSION
        uintmax_t s = gta_get_data_size(header);
        size_t chunk_size;
        while (s > 0)
        {
            retval = gta_skip_chunk(header, &chunk_size, read_fn, seek_fn, userdata);
            if (retval != GTA_OK)
            {
                return retval;
            }
            if (chunk_size > s)
            {
                return GTA_INVALID_DATA;
            }
            s -= chunk_size;
            if (chunk_size == 0 && s > 0)
            {
                return GTA_INVALID_DATA;
            }
        }
        retval = gta_skip_chunk(header, &chunk_size, read_fn, seek_fn, userdata);
        if (retval != GTA_OK)
        {
            return retval;
        }
        if (chunk_size != 0)
        {
            return GTA_INVALID_DATA;
        }
#else
        return GTA_UNSUPPORTED_DATA;
#endif
    }
    else
    {
        if (seek_fn)
        {
            if (gta_get_data_size(header) > (uintmax_t)(INTMAX_MAX))
            {
                return GTA_OVERFLOW;
            }
            int error = false;
            seek_fn(userdata, gta_get_data_size(header), SEEK_CUR, &error);
            if (error)
            {
                return GTA_SYSTEM_ERROR;
            }
        }
        else
        {
            retval = gta_readskip(read_fn, userdata, gta_get_data_size(header));
            if (retval != GTA_OK)
            {
                return retval;
            }
        }
    }
    return GTA_OK;
}

gta_result_t
gta_skip_data_from_stream(const gta_header_t *GTA_RESTRICT header, FILE *GTA_RESTRICT f)
{
    return gta_skip_data(header, gta_read_stream,
            (ftello(f) == -1 ? NULL : gta_seek_stream), (intptr_t)f);
}

gta_result_t
gta_skip_data_from_fd(const gta_header_t *GTA_RESTRICT header, int fd)
{
    return gta_skip_data(header, gta_read_fd,
            (lseek(fd, 0, SEEK_CUR) == -1 ? NULL : gta_seek_fd), fd);
}

gta_result_t
gta_write_data(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, gta_write_t write_fn, intptr_t userdata)
{
    // We know that the data size fits into size_t, because the caller already allocated a buffer for all the data.
    int output_error = false;
    errno = 0;
    size_t r = write_fn(userdata, data, gta_get_data_size(header), &output_error);
    if (output_error || r < gta_get_data_size(header))
    {
        if (errno == 0)
        {
            errno = EIO;
        }
        return GTA_SYSTEM_ERROR;
    }
    return GTA_OK;
}

gta_result_t
gta_write_data_to_stream(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, FILE *GTA_RESTRICT f)
{
    return gta_write_data(header, data, gta_write_stream, (intptr_t)f);
}

gta_result_t
gta_write_data_to_fd(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, int fd)
{
    return gta_write_data(header, data, gta_write_fd, fd);
}

gta_result_t
gta_copy_data(const gta_header_t *GTA_RESTRICT read_header, gta_read_t read_fn, intptr_t read_userdata,
        const gta_header_t *GTA_RESTRICT write_header, gta_write_t write_fn, intptr_t write_userdata)
{
    if (gta_get_dimensions(read_header) != gta_get_dimensions(write_header)
            || gta_get_components(read_header) != gta_get_components(write_header))
    {
        return GTA_INVALID_DATA;
    }
    for (uintmax_t i = 0; i < gta_get_dimensions(read_header); i++)
    {
        if (gta_get_dimension_size(read_header, i) != gta_get_dimension_size(write_header, i))
        {
            return GTA_INVALID_DATA;
        }
    }
    for (uintmax_t i = 0; i < gta_get_components(read_header); i++)
    {
        if (gta_get_component_type(read_header, i) != gta_get_component_type(write_header, i))
        {
            return GTA_INVALID_DATA;
        }
        if (gta_get_component_type(read_header, i) == GTA_BLOB
                && gta_get_component_size(read_header, i) != gta_get_component_size(write_header, i))
        {
            return GTA_INVALID_DATA;
        }
    }

    uintmax_t size = gta_get_data_size(read_header);
    gta_result_t retval = GTA_OK;

    if (gta_get_compression(read_header) != GTA_NONE)
    {
#if WITH_COMPRESSION
        void *chunk = NULL;
        size_t chunk_size = 0;
        do
        {
            retval = gta_read_chunk(read_header, &chunk, &chunk_size, read_fn, read_userdata);
            if (retval != GTA_OK)
            {
                free(chunk);
                return retval;
            }
            if (chunk_size > size)
            {
                free(chunk);
                return GTA_INVALID_DATA;
            }
            int error = false;
            errno = 0;
            size_t r = write_fn(write_userdata, chunk, chunk_size, &error);
            if (error || r < chunk_size)
            {
                if (errno == 0)
                {
                    errno = EIO;
                }
                retval = GTA_SYSTEM_ERROR;
            }
            free(chunk);
            if (retval != GTA_OK)
            {
                return retval;
            }
            size -= chunk_size;
        }
        while (chunk_size > 0);
        if (size > 0)
        {
            return GTA_UNEXPECTED_EOF;
        }
#else
        return GTA_UNSUPPORTED_DATA;
#endif
    }
    else
    {
        void *chunk = NULL;
        size_t chunk_size = 0;
        size_t chunk_index = 0;
        void *buffer = malloc(size < gta_max_chunk_size ? size : gta_max_chunk_size);

        if (!buffer)
        {
            return GTA_SYSTEM_ERROR;
        }
        while (size > 0)
        {
            int error = false;
            size_t x = (size > gta_max_chunk_size ? gta_max_chunk_size : size);
            size_t r = read_fn(read_userdata, buffer, x, &error);
            if (error)
            {
                free(buffer);
                free(chunk);
                return GTA_SYSTEM_ERROR;
            }
            if (r < x)
            {
                free(buffer);
                free(chunk);
                return GTA_UNEXPECTED_EOF;
            }
            error = false;
            errno = 0;
            r = write_fn(write_userdata, buffer, x, &error);
            if (error || r < x)
            {
                if (errno == 0)
                {
                    errno = EIO;
                }
                free(buffer);
                free(chunk);
                return GTA_SYSTEM_ERROR;
            }
            size -= x;
        }
        free(buffer);
    }
    return GTA_OK;
}

gta_result_t
gta_copy_data_stream(
        const gta_header_t *GTA_RESTRICT read_header, FILE *GTA_RESTRICT read_f,
        const gta_header_t *GTA_RESTRICT write_header, FILE *GTA_RESTRICT write_f)
{
    return gta_copy_data(
            read_header, gta_read_stream, (intptr_t)read_f,
            write_header, gta_write_stream, (intptr_t)write_f);
}

gta_result_t
gta_copy_data_fd(
        const gta_header_t *GTA_RESTRICT read_header, int read_fd,
        const gta_header_t *GTA_RESTRICT write_header, int write_fd)
{
    return gta_copy_data(
            read_header, gta_read_fd, read_fd,
            write_header, gta_write_fd, write_fd);
}


/*
 *
 * Read and Write Array Elements
 *
 */

gta_result_t
gta_create_io_state(gta_io_state_t *GTA_RESTRICT *GTA_RESTRICT io_state)
{
    *io_state = malloc(sizeof(gta_io_state_t));
    if (!*io_state)
    {
        return GTA_SYSTEM_ERROR;
    }
    (*io_state)->io_type = 0;
    (*io_state)->failure = false;
    (*io_state)->counter = 0;
    (*io_state)->chunk = NULL;
    (*io_state)->chunk_size = 0;
    (*io_state)->chunk_index = 0;
    (*io_state)->already_read = 0;
    return GTA_OK;
}

void
gta_destroy_io_state(gta_io_state_t *GTA_RESTRICT io_state)
{
    free(io_state->chunk);
    free(io_state);
}

gta_result_t
gta_clone_io_state(gta_io_state_t *GTA_RESTRICT dst_io_state,
        const gta_io_state_t *GTA_RESTRICT src_io_state)
{
    void *chunk = NULL;

    if (src_io_state->chunk)
    {
        chunk = malloc(src_io_state->chunk_size);
        if (!chunk)
        {
            return GTA_SYSTEM_ERROR;
        }
        memcpy(chunk, src_io_state->chunk, src_io_state->chunk_size);
    }
    free(dst_io_state->chunk);
    dst_io_state->io_type = src_io_state->io_type;
    dst_io_state->failure = src_io_state->failure;
    dst_io_state->counter = src_io_state->counter;
    dst_io_state->chunk = chunk;
    dst_io_state->chunk_size = src_io_state->chunk_size;
    dst_io_state->chunk_index = src_io_state->chunk_index;
    dst_io_state->already_read = src_io_state->already_read;
    return GTA_OK;
}

gta_result_t
gta_read_elements(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, void *GTA_RESTRICT buf, gta_read_t read_fn, intptr_t userdata)
{
    gta_result_t retval = GTA_OK;

    if (io_state->io_type == 0)
    {
        io_state->io_type = 1;
    }
    if (io_state->io_type != 1)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }
    if (io_state->failure)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }
    if (n > gta_get_elements(header) || io_state->counter > gta_get_elements(header) - n)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }
    uintmax_t s = gta_get_element_size(header);
    if (s == 0)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }
    if (s > SIZE_MAX || n > SIZE_MAX || gta_size_overflow(n, s))
    {
        retval = GTA_OVERFLOW;
        goto exit;
    }
    size_t size = n * s;
    size_t i = 0;
    while (i < size)
    {
        if (io_state->chunk_index == io_state->chunk_size)
        {
            if (gta_get_compression(header) != GTA_NONE)
            {
#if WITH_COMPRESSION
                free(io_state->chunk);
                io_state->chunk = NULL;
                gta_result_t retval = gta_read_chunk(header, &(io_state->chunk),
                        &(io_state->chunk_size), read_fn, userdata);
#else
                gta_result_t retval = GTA_UNSUPPORTED_DATA;

#endif
                if (retval != GTA_OK)
                {
                    goto exit;
                }
            }
            else
            {
                size_t chunk_size = gta_max_chunk_size;
                if (!io_state->chunk)
                {
                    if (gta_get_data_size(header) < chunk_size)
                    {
                        chunk_size = gta_get_data_size(header);
                    }
                    io_state->chunk = malloc(chunk_size);
                    if (!io_state->chunk)
                    {
                        retval = GTA_SYSTEM_ERROR;
                        goto exit;
                    }
                }
                uintmax_t read_size = gta_get_data_size(header) - io_state->already_read;
                if (read_size > chunk_size)
                {
                    read_size = chunk_size;
                }
                int error = false;
                size_t r = read_fn(userdata, io_state->chunk, read_size, &error);
                if (error)
                {
                    retval = GTA_SYSTEM_ERROR;
                    goto exit;
                }
                if (r < read_size)
                {
                    retval = GTA_UNEXPECTED_EOF;
                    goto exit;
                }
                io_state->chunk_size = read_size;
                io_state->already_read += read_size;
            }
            io_state->chunk_index = 0;
        }
        size_t l = size - i;
        if (l > io_state->chunk_size - io_state->chunk_index)
        {
            l = io_state->chunk_size - io_state->chunk_index;
        }
        memcpy((char *)buf + i, (char *)(io_state->chunk) + io_state->chunk_index, l);
        i += l;
        io_state->chunk_index += l;
    }
    io_state->counter += n;
    if (io_state->counter == gta_get_elements(header))
    {
        if (gta_get_compression(header) != GTA_NONE)
        {
#if WITH_COMPRESSION
            if (io_state->chunk_index != io_state->chunk_size)
            {
                retval = GTA_INVALID_DATA;
                goto exit;
            }
            // read the last, empty chunk
            free(io_state->chunk);
            io_state->chunk = NULL;
            retval = gta_read_chunk(header, &(io_state->chunk),
                    &(io_state->chunk_size), read_fn, userdata);
            if (retval != GTA_OK)
            {
                goto exit;
            }
            if (io_state->chunk_size != 0)
            {
                retval = GTA_INVALID_DATA;
                goto exit;
            }
#else
            retval = GTA_UNSUPPORTED_DATA;
            goto exit;
#endif
        }
        else
        {
            // free the chunk; it will not be needed anymore
            free(io_state->chunk);
            io_state->chunk = NULL;
        }
    }
    if (gta_data_needs_endianness_swapping(header))
    {
        for (uintmax_t i = 0; i < n; i++)
        {
            gta_swap_element_endianness(header, (char *)buf + i * s);
        }
    }
exit:
    if (retval != GTA_OK)
    {
        io_state->failure = true;
        free(io_state->chunk);
        io_state->chunk = NULL;
    }
    return retval;
}

gta_result_t
gta_read_elements_from_stream(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, void *GTA_RESTRICT buf, FILE *GTA_RESTRICT f)
{
    return gta_read_elements(header, io_state, n, buf, gta_read_stream, (intptr_t)f);
}

gta_result_t
gta_read_elements_from_fd(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, void *GTA_RESTRICT buf, int fd)
{
    return gta_read_elements(header, io_state, n, buf, gta_read_fd, fd);
}

gta_result_t
gta_write_elements(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, const void *GTA_RESTRICT buf, gta_write_t write_fn, intptr_t userdata)
{
    gta_result_t retval = GTA_OK;

    if (io_state->io_type == 0)
    {
        io_state->io_type = 2;
    }
    if (io_state->io_type != 2)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }
    if (io_state->failure)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }
    if (n > gta_get_elements(header) || io_state->counter > gta_get_elements(header) - n)
    {
        retval = GTA_INVALID_DATA;
        goto exit;
    }
    uintmax_t s = gta_get_element_size(header);
    if (s > SIZE_MAX || n > SIZE_MAX || gta_size_overflow(n, s))
    {
        retval = GTA_OVERFLOW;
        goto exit;
    }
    size_t size = n * s;
    size_t i = 0;
    while (i < size)
    {
        if (io_state->chunk_index == io_state->chunk_size)
        {
            if (!io_state->chunk)
            {
                size_t chunk_size = gta_max_chunk_size;
                if (gta_get_data_size(header) < chunk_size)
                {
                    chunk_size = gta_get_data_size(header);
                }
                io_state->chunk = malloc(chunk_size);
                if (!io_state->chunk)
                {
                    retval = GTA_SYSTEM_ERROR;
                    goto exit;
                }
                io_state->chunk_size = chunk_size;
            }
            if (io_state->chunk_index > 0)
            {
                int error = false;
                errno = 0;
                size_t r = write_fn(userdata, io_state->chunk, io_state->chunk_size, &error);
                if (error || r < io_state->chunk_size)
                {
                    if (errno == 0)
                    {
                        errno = EIO;
                    }
                    retval = GTA_SYSTEM_ERROR;
                    goto exit;
                }
            }
            io_state->chunk_index = 0;
        }
        size_t l = size - i;
        if (l > io_state->chunk_size - io_state->chunk_index)
        {
            l = io_state->chunk_size - io_state->chunk_index;
        }
        memcpy((char *)(io_state->chunk) + io_state->chunk_index, (char *)buf + i, l);
        i += l;
        io_state->chunk_index += l;
    }
    io_state->counter += n;
    if (io_state->counter == gta_get_elements(header))
    {
        // flush
        if (io_state->chunk_index > 0)
        {
            int error = false;
            errno = 0;
            size_t r = write_fn(userdata, io_state->chunk, io_state->chunk_index, &error);
            if (error || r < io_state->chunk_index)
            {
                if (errno == 0)
                {
                    errno = EIO;
                }
                retval = GTA_SYSTEM_ERROR;
                goto exit;
            }
        }
        // free the chunk; it will not be needed anymore
        free(io_state->chunk);
        io_state->chunk = NULL;
    }
exit:
    if (retval != GTA_OK)
    {
        io_state->failure = true;
        free(io_state->chunk);
        io_state->chunk = NULL;
    }
    return retval;
}

gta_result_t
gta_write_elements_to_stream(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, const void *GTA_RESTRICT buf, FILE *GTA_RESTRICT f)
{
    return gta_write_elements(header, io_state, n, buf, gta_write_stream, (intptr_t)f);
}

gta_result_t
gta_write_elements_to_fd(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, const void *GTA_RESTRICT buf, int fd)
{
    return gta_write_elements(header, io_state, n, buf, gta_write_fd, fd);
}


/*
 *
 * Read and Write Array Blocks
 *
 */


/**
 * \brief               Get the offset of an array element.
 * \param header        The header.
 * \param indices       The indices for each dimension of the array.
 * \return              The offset of the element, relative to the start of the data.
 */
static GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW
intmax_t
gta_get_element_offset(const gta_header_t *GTA_RESTRICT header, const uintmax_t *GTA_RESTRICT indices)
{
    uintmax_t index = 0;
    uintmax_t dim_product = 1;
    for (uintmax_t i = 0; i < gta_get_dimensions(header); i++)
    {
        if (i > 0)
        {
            dim_product *= gta_get_dimension_size(header, i - 1);
        }
        index += indices[i] * dim_product;
    }
    return index * gta_get_element_size(header);
}

gta_result_t
gta_read_block(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        void *GTA_RESTRICT block, gta_read_t read_fn, gta_seek_t seek_fn, intptr_t userdata)
{
    if (gta_get_compression(header) != GTA_NONE || gta_get_dimensions(header) == 0)
    {
        return GTA_UNSUPPORTED_DATA;
    }
    if (data_offset > INTMAX_MAX - gta_get_element_offset(header, higher_coordinates)
            || gta_get_element_size(header) > (uintmax_t)(INTMAX_MAX)
            || data_offset + gta_get_element_offset(header, higher_coordinates) > INTMAX_MAX - (intmax_t)gta_get_element_size(header))
    {
        return GTA_OVERFLOW;
    }

    uintmax_t *coords = malloc(gta_get_dimensions(header) * sizeof(uintmax_t));
    if (!coords)
    {
        return GTA_SYSTEM_ERROR;
    }

    memcpy(coords, lower_coordinates, gta_get_dimensions(header) * sizeof(uintmax_t));
    uintmax_t dim0_len = higher_coordinates[0] - lower_coordinates[0] + 1;
    uintmax_t dim0_datalen = dim0_len * gta_get_element_size(header);
    char *block_ptr = block;
    gta_result_t retval = GTA_OK;

    for (;;)
    {
        intmax_t o = gta_get_element_offset(header, coords);
        // Read data
        int error = false;
        seek_fn(userdata, data_offset + o, SEEK_SET, &error);
        if (error)
        {
            retval = GTA_SYSTEM_ERROR;
            break;
        }
        size_t r = read_fn(userdata, block_ptr, dim0_datalen, &error);
        if (error)
        {
            retval = GTA_SYSTEM_ERROR;
            break;
        }
        if (r < dim0_datalen)
        {
            retval = GTA_UNEXPECTED_EOF;
            break;
        }
        // Fix endianness
        if (gta_data_needs_endianness_swapping(header))
        {
            for (uintmax_t i = 0; i < dim0_len; i++)
            {
                void *e = block_ptr + i * gta_get_element_size(header);
                gta_swap_element_endianness(header, e);
            }
        }
        // Increase block index and coordinates
        block_ptr += dim0_datalen;
        uintmax_t d;
        for (d = 1; d < gta_get_dimensions(header); d++)
        {
            if (coords[d] < higher_coordinates[d])
            {
                coords[d]++;
                break;
            }
            else
            {
                coords[d] = lower_coordinates[d];
            }
        }
        if (d == gta_get_dimensions(header))
        {
            break;
        }
    }
    free(coords);
    return retval;
}

gta_result_t
gta_read_block_from_stream(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        void *GTA_RESTRICT block, FILE *GTA_RESTRICT f)
{
    return gta_read_block(header, data_offset, lower_coordinates, higher_coordinates, block,
            gta_read_stream, gta_seek_stream, (intptr_t)f);
}

gta_result_t
gta_read_block_from_fd(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        void *GTA_RESTRICT block, int fd)
{
    return gta_read_block(header, data_offset, lower_coordinates, higher_coordinates, block,
            gta_read_fd, gta_seek_fd, fd);
}

gta_result_t
gta_write_block(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        const void *GTA_RESTRICT block, gta_write_t write_fn, gta_seek_t seek_fn, intptr_t userdata)
{
    if (gta_get_compression(header) != GTA_NONE || gta_get_dimensions(header) == 0)
    {
        return GTA_UNSUPPORTED_DATA;
    }
    if (data_offset > INTMAX_MAX - gta_get_element_offset(header, higher_coordinates)
            || gta_get_element_size(header) > (uintmax_t)(INTMAX_MAX)
            || data_offset + gta_get_element_offset(header, higher_coordinates) > INTMAX_MAX - (intmax_t)gta_get_element_size(header))
    {
        return GTA_OVERFLOW;
    }

    uintmax_t *coords = malloc(gta_get_dimensions(header) * sizeof(uintmax_t));
    if (!coords)
    {
        return GTA_SYSTEM_ERROR;
    }

    memcpy(coords, lower_coordinates, gta_get_dimensions(header) * sizeof(uintmax_t));
    uintmax_t dim0_len = higher_coordinates[0] - lower_coordinates[0] + 1;
    uintmax_t dim0_datalen = dim0_len * gta_get_element_size(header);
    void *temp_block = NULL;
    if (gta_data_needs_endianness_swapping(header))
    {
        temp_block = malloc(dim0_datalen);
        if (!temp_block)
        {
            free(coords);
            return GTA_OVERFLOW;
        }
    }
    const char *block_ptr = block;
    gta_result_t retval = GTA_OK;

    for (;;)
    {
        intmax_t o = gta_get_element_offset(header, coords);
        // Fix endianness (we must not change endianness of an existing file)
        if (gta_data_needs_endianness_swapping(header))
        {
            memcpy(temp_block, block_ptr, dim0_datalen);
            for (uintmax_t i = 0; i < dim0_len; i++)
            {
                void *e = (char *)temp_block + i * gta_get_element_size(header);
                gta_swap_element_endianness(header, e);
            }
        }
        // Write data
        int error = false;
        seek_fn(userdata, data_offset + o, SEEK_SET, &error);
        if (error)
        {
            retval = GTA_SYSTEM_ERROR;
            break;
        }
        errno = 0;
        size_t r = write_fn(userdata,
                gta_data_needs_endianness_swapping(header) ? temp_block : block_ptr,
                dim0_datalen, &error);
        if (error || r < dim0_datalen)
        {
            if (errno == 0)
            {
                errno = EIO;
            }
            retval = GTA_SYSTEM_ERROR;
            break;
        }
        // Increase block index and coordinates
        block_ptr += dim0_datalen;
        uintmax_t d;
        for (d = 1; d < gta_get_dimensions(header); d++)
        {
            if (coords[d] < higher_coordinates[d])
            {
                coords[d]++;
                break;
            }
            else
            {
                coords[d] = lower_coordinates[d];
            }
        }
        if (d == gta_get_dimensions(header))
        {
            break;
        }
    }
    free(temp_block);
    free(coords);
    return retval;
}

gta_result_t
gta_write_block_to_stream(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        const void *GTA_RESTRICT block, FILE *GTA_RESTRICT f)
{
    return gta_write_block(header, data_offset, lower_coordinates, higher_coordinates, block,
            gta_write_stream, gta_seek_stream, (intptr_t)f);
}

gta_result_t
gta_write_block_to_fd(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        const void *GTA_RESTRICT block, int fd)
{
    return gta_write_block(header, data_offset, lower_coordinates, higher_coordinates, block,
            gta_write_fd, gta_seek_fd, fd);
}
