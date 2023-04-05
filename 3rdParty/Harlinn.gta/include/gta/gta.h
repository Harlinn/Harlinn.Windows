/*
 * gta.h
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


/**
 * \file gta.h
 * \brief The libgta C interface.
 *
 * This document describes the C language interface of libgta.
 */


/**
 * \mainpage libgta Reference
 *
 * \section file_format The Generic Tagged Array (GTA) File Format
 *
 * The GTA file format has the following features:\n
 * - GTAs can store any kind of data in multidimensional arrays\n
 * - GTAs can optionally use simple tags to store rich metadata\n
 * - GTAs are streamable, which allows direct reading from and writing to pipes, network sockets, and other non-seekable media\n
 * - Uncompressed GTA files allow easy out-of-core data access for very large arrays
 *
 * See the <a href="https://marlam.de/gta/specification.pdf">GTA file format specification</a> for details.
 *
 * \section lib The libgta Library
 *
 * The library works with three basic entities: GTA headers, GTA tag lists, and the array data.\n
 * A GTA header stores all the information about the array data: array dimensions, array element components,
 * and tag lists. There is one global tag list for the whole array, one tag list for each dimension, and one
 * tag list for each element component.\n
 *
 * The array data can be read and written in one of three ways:
 * - completely in memory (for arrays that are not too big),
 * - stream-based (for streamable tasks),
 * - or block-based (for random access to the array data).
 *
 * The library provides interfaces for C and C++. See the <a href="files.html">Files</a> section.
 *
 * \section examples Examples
 *
 * Examples written in C:
 * - <a href="example-basic_8c.html">Introductory example</a>
 * - <a href="example-tags_8c.html">Using tags</a>
 * - <a href="example-stream-io_8c.html">Stream-based input/output</a>
 * - <a href="example-block-io_8c.html">Block-based input/output</a>
 *
 * Examples written in C++:
 * - <a href="example-basic_8cpp.html">Introductory example</a>
 * - <a href="example-tags_8cpp.html">Using tags</a>
 * - <a href="example-stream-io_8cpp.html">Stream-based input/output</a>
 * - <a href="example-block-io_8cpp.html">Block-based input/output</a>
 *
 * \page example-basic.c Examples written in C: Introductory example
 * \include example-basic.c
 * \page example-tags.c Examples written in C: Using tags
 * \include example-tags.c
 * \page example-stream-io.c Examples written in C: Stream-based input/output
 * \include example-stream-io.c
 * \page example-block-io.c Examples written in C: Block-based input/output
 * \include example-block-io.c
 *
 * \page example-basic.cpp Examples written in C++: Introductory example
 * \include example-basic.cpp
 * \page example-tags.cpp Examples written in C++: Using tags
 * \include example-tags.cpp
 * \page example-stream-io.cpp Examples written in C++: Stream-based input/output
 * \include example-stream-io.cpp
 * \page example-block-io.cpp Examples written in C++: Block-based input/output
 * \include example-block-io.cpp
 */


#ifndef GTA_H
#define GTA_H

#include <stdio.h>

#if defined _MSC_VER && _MSC_VER < 1600
/* MSVC versions older than Visual Studio 2010 lack the C99 header <stdint.h> */
typedef signed __int64 intmax_t;
typedef unsigned __int64 uintmax_t;
#   ifdef _WIN64
typedef signed __int64 intptr_t;
#   else
typedef signed int intptr_t;
#   endif
#else
/* Everyone else has it */
#   include <stdint.h>
#endif


/* GTA_EXPORT: Declare functions as part of the library API.
 * (You only need to define GTA_STATIC for a static GTA library
 * if you use Microsoft compilers). */

#if 0
#if (defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__
#   ifdef GTA_BUILD
#       ifdef DLL_EXPORT
#           define GTA_EXPORT __declspec(dllexport)
#       else
#           define GTA_EXPORT
#       endif
#   else
#       if defined _MSC_VER && !defined GTA_STATIC
#           define GTA_EXPORT __declspec(dllimport)
#       else
#           define GTA_EXPORT
#       endif
#   endif
#else
#   define GTA_EXPORT
#endif
#endif

#ifdef BUILDING_HARLINN_GTA
 #define GTA_EXPORT __declspec(dllexport)
#else
 #define GTA_EXPORT __declspec(dllimport)
 #pragma comment(lib,"Harlinn.gta.lib")
#endif


/* Several attributes that may help the compiler to optimize the code or to
 * produce better warnings.
 * See http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
 * and http://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html
 */
#ifdef __GNUC__
#   define GTA_ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#   define GTA_ATTR_NONNULL_ALL __attribute__((nonnull))
#   define GTA_ATTR_NONNULL1(a) __attribute__((nonnull(a)))
#   define GTA_ATTR_NONNULL2(a, b) __attribute__((nonnull(a, b)))
#   define GTA_ATTR_NONNULL3(a, b, c) __attribute__((nonnull(a, b, c)))
#   define GTA_ATTR_CONST __attribute__((const))
#   define GTA_ATTR_PURE __attribute__((pure))
#   define GTA_ATTR_NOTHROW __attribute__((nothrow))
#   define GTA_ATTR_UNUSED __attribute__((unused))
#else
#   define GTA_ATTR_WARN_UNUSED_RESULT
#   define GTA_ATTR_NONNULL_ALL
#   define GTA_ATTR_NONNULL1(a)
#   define GTA_ATTR_NONNULL2(a, b)
#   define GTA_ATTR_NONNULL3(a, b, c)
#   define GTA_ATTR_CONST
#   define GTA_ATTR_PURE
#   define GTA_ATTR_NOTHROW
#   define GTA_ATTR_UNUSED
#endif

/* The C99 'restrict' keyword. */
#if __STDC_VERSION__ >= 199901L
#   define GTA_RESTRICT restrict
#else
#   define GTA_RESTRICT
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
 *
 * Version information
 *
 */

#include <gta/gta_version.h>


/*
 *
 * Types
 *
 */


/**
 * \brief      The GTA header type
 */
typedef struct gta_internal_header_struct gta_header_t;

/**
 * \brief       The GTA tag list type
 *
 * A tag consists of a name and a value. A tag list stores these name/value pairs.\n
 * Tag names are non-empty UTF-8 strings that must not contain '='.\n
 * Tag values are UTF-8 strings.\n
 * If you do not want to deal with conversions between the local character set and UTF-8,
 * you must restrict names and values to ASCII.
 */
typedef struct gta_internal_taglist_struct gta_taglist_t;

/**
 * \brief       GTA result type
 *
 * The return value of most GTA functions is of this type, to indicate failures
 * and their causes.
 */
typedef enum
{
    GTA_OK = 0,
    /**<
     * \brief   Success / no error
     */
    GTA_OVERFLOW = 1,
    /**<
     * \brief   Size overflow
     */
    GTA_UNSUPPORTED_DATA = 2,
    /**<
     * \brief   Unsupported data
     *
     * The input seems to require features that are not available in this version
     * of the library.
     */
    GTA_UNEXPECTED_EOF = 3,
    /**<
     * \brief   Unexpected end of file
     *
     * The GTA library intended to read more data, but the input did not provide it.
     */
    GTA_INVALID_DATA = 4,
    /**<
     * \brief   Invalid data
     *
     * Some data was invalid. For example, an input file is not in GTA format.
     */
    GTA_SYSTEM_ERROR = 5
    /**<
     * \brief   System error
     *
     * A system error occured. More information is available in errno.
     * Examples: memory allocation failure (errno == ENOMEM), input/output
     * errors (errno == EIO), no space left on device (errno == ENOSPC).
     */
} gta_result_t;

/**
 * \brief       GTA data types
 *
 * Data types supported by GTA.
 *
 * All integer types contain the exact number of bits indicated by their name
 * and use the common two's complement representation.\n
 * All floating point types contain the exact number of bits indicated by their
 * name and conform to the binary representation defined by IEEE 754.\n
 * The complex types (GTA_CFLOAT*) consist of two floating point values with the
 * number of bits indicated by the name, as defined above. The first value is
 * the real part, the second value is the imaginary part. For example,
 * \a GTA_CFLOAT32 consists of two \a GTA_FLOAT32 values.\n
 * The name \a GTA_BLOB can be used for data types that are not defined in this
 * list. In this case, the size of the data type must be given, and the data type
 * must be independent of endianness.
 */
typedef enum
{
    GTA_INT8      = 1,  /**< \brief int8_t */
    GTA_UINT8     = 2,  /**< \brief uint8_t */
    GTA_INT16     = 3,  /**< \brief int16_t */
    GTA_UINT16    = 4,  /**< \brief uint16_t */
    GTA_INT32     = 5,  /**< \brief int32_t */
    GTA_UINT32    = 6,  /**< \brief uint32_t */
    GTA_INT64     = 7,  /**< \brief int64_t */
    GTA_UINT64    = 8,  /**< \brief uint64_t */
    GTA_INT128    = 9,  /**< \brief int128_t (unavailable on many platforms) */
    GTA_UINT128   = 10, /**< \brief uint128_t (unavailable on many platforms) */
    GTA_FLOAT32   = 11, /**< \brief IEEE 754 single precision floating point (on many platforms: float) */
    GTA_FLOAT64   = 12, /**< \brief IEEE 754 double precision floating point (on many platforms: double) */
    GTA_FLOAT128  = 13, /**< \brief IEEE 754 quadrupel precision floating point (unavailable on many platforms, even if long double exists) */
    GTA_CFLOAT32  = 14, /**< \brief complex (re,im) based on two \a GTA_FLOAT32 */
    GTA_CFLOAT64  = 15, /**< \brief complex (re,im) based on two \a GTA_FLOAT64 */
    GTA_CFLOAT128 = 16, /**< \brief complex (re,im) based on two \a GTA_FLOAT128 */
    GTA_BLOB      = 0   /**< \brief Data blob; must be endianness-independent; user must specify the size */
} gta_type_t;

/**
 * \brief       GTA compression algorithms
 *
 * These are deprecated. Do not use them anymore, they will be removed in a future version.
 */
typedef enum
{
    GTA_NONE  = 0,      /**< \brief No compression */
    GTA_ZLIB  = 1,      /**< \brief ZLIB compression with default level (fast, moderate compression rate) */
    GTA_ZLIB1 = 4,      /**< \brief ZLIB compression with level 1 */
    GTA_ZLIB2 = 5,      /**< \brief ZLIB compression with level 2 */
    GTA_ZLIB3 = 6,      /**< \brief ZLIB compression with level 3 */
    GTA_ZLIB4 = 7,      /**< \brief ZLIB compression with level 4 */
    GTA_ZLIB5 = 8,      /**< \brief ZLIB compression with level 5 */
    GTA_ZLIB6 = 9,      /**< \brief ZLIB compression with level 6 */
    GTA_ZLIB7 = 10,     /**< \brief ZLIB compression with level 7 */
    GTA_ZLIB8 = 11,     /**< \brief ZLIB compression with level 8 */
    GTA_ZLIB9 = 12,     /**< \brief ZLIB compression with level 9 */
    GTA_BZIP2 = 2,      /**< \brief BZIP2 compression (moderate speed, good compression rates) */
    GTA_XZ    = 3       /**< \brief XZ compression (low/moderate speed, good/very good compression rates) */
} gta_compression_t;

/**
 * \brief       Custom input function
 *
 * You can specify your own input function to read from your own custom sources.\n
 * It must read the given number of bytes into the given buffer.\n
 * Its return value must be the number of bytes successfully read.\n
 * If an error occured, the error flag must be set to true (1).
 * The function must set errno to indicate the type of error. If the
 * error type is unknown, errno should be set to EIO.
 */
typedef size_t (*gta_read_t)(intptr_t userdata, void *buffer, size_t size, int *error);

/**
 * \brief       Custom output function
 *
 * You can specify your own output function to write to your own custum destinations.\n
 * It must write the given number of bytes from the given buffer.\n
 * Its return value must be the number of bytes successfully written.\n
 * If an error occured, the error flag must be set to true (1).
 * The function must set errno to indicate the type of error. If the
 * error type is unknown, errno should be set to EIO.
 */
typedef size_t (*gta_write_t)(intptr_t userdata, const void *buffer, size_t size, int *error);

/**
 * \brief       Custom seek function
 *
 * You can specify your own seek function to seek in your own custum media.\n
 * It must change its file position indicator as indicated by the parameters \a
 * offset and \a whence, just like fseeko() and lseek() do. The parameter \a whence
 * can be SEEK_SET or SEEK_CUR (SEEK_END is never used).\n
 * If an error occured, the error flag must be set to true (1).
 * The function must set errno to indicate the type of error. If the
 * error type is unknown, errno should be set to EIO.
 */
typedef void (*gta_seek_t)(intptr_t userdata, intmax_t offset, int whence, int *error);

/**
 * \brief       State for element-based input/output
 *
 * See gta_read_elements() and gta_write_elements().
 */
typedef struct gta_internal_io_state_struct gta_io_state_t;


/**
 *
 * \name Version information
 *
 */

/*@{*/

/**
 * \brief       Get the libgta version.
 * \param major Buffer for the major version number, or NULL.
 * \param minor Buffer for the minor version number, or NULL.
 * \param patch Buffer for the patch version number, or NULL.
 * \return      The libgta version string.
 *
 * This function returns the version string "MAJOR.MINOR.PATCH".
 * If the pointers \a major, \a minor, \a patch are not NULL,
 * the requested version number will be stored there.
 */
extern GTA_EXPORT const char *
gta_version(int *GTA_RESTRICT major, int *GTA_RESTRICT minor, int *GTA_RESTRICT patch)
GTA_ATTR_NOTHROW;

/*@}*/

/**
 *
 * \name Create and destroy GTA Headers
 *
 */

/*@{*/

/**
 * \brief               Create a new GTA header structure and initialize it.
 * \param header        The header.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Creates a new GTA header and initializes it.
 * The GTA will initially be empty (zero element components, zero dimensions)
 * and contain no tags.
 */
extern GTA_EXPORT gta_result_t
gta_create_header(gta_header_t *GTA_RESTRICT *GTA_RESTRICT header)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Clone a GTA header structure.
 * \param dst_header    The destination header.
 * \param src_header    The source header.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Clones \a src_header into \a dst_header.
 */
extern GTA_EXPORT gta_result_t
gta_clone_header(gta_header_t *GTA_RESTRICT dst_header,
        const gta_header_t *GTA_RESTRICT src_header)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Destroy a GTA header structure and free its resources.
 * \param header        The header.
 *
 * Destroys a GTA header structure and fress all of its resources.
 */
extern GTA_EXPORT void
gta_destroy_header(gta_header_t *GTA_RESTRICT header)
GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/*@}*/


/**
 *
 * \name Read and Write GTA Headers
 *
 */

/*@{*/

/**
 * \brief               Read a GTA header.
 * \param header        The header.
 * \param read_fn       The custom input function.
 * \param userdata      A parameter to the custom input function.
 * \return              \a GTA_OK, \a GTA_OVERFLOW, \a GTA_INVALID_DATA, or \a GTA_SYSTEM_ERROR.
 */
extern GTA_EXPORT gta_result_t
gta_read_header(gta_header_t *GTA_RESTRICT header, gta_read_t read_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief              Read a GTA header from a stream.
 * \param header       The header.
 * \param f            The stream.
 * \return             \a GTA_OK, \a GTA_OVERFLOW, \a GTA_INVALID_DATA, or \a GTA_SYSTEM_ERROR.
 *
 * Reads a GTA header from a stream.\n
 * The file position indicator will be positioned after the GTA header, on the
 * first data byte.
 */
extern GTA_EXPORT gta_result_t
gta_read_header_from_stream(gta_header_t *GTA_RESTRICT header, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief              Read a GTA header from a file descriptor.
 * \param header       The header.
 * \param fd           The file descriptor.
 * \return             \a GTA_OK, \a GTA_OVERFLOW, \a GTA_INVALID_DATA, or \a GTA_SYSTEM_ERROR.
 *
 * Reads a GTA header from a file descriptor.\n
 * The file position indicator will be positioned after the GTA header, on the
 * first data byte.
 */
extern GTA_EXPORT gta_result_t
gta_read_header_from_fd(gta_header_t *GTA_RESTRICT header, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;


/**
 * \brief               Write a GTA header.
 * \param header        The header.
 * \param write_fn      The custom output function.
 * \param userdata      A parameter to the custom output function.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 */
extern GTA_EXPORT gta_result_t
gta_write_header(const gta_header_t *GTA_RESTRICT header, gta_write_t write_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief               Write a GTA header to a stream.
 * \param header        The header.
 * \param f             The stream.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 */
extern GTA_EXPORT gta_result_t
gta_write_header_to_stream(const gta_header_t *GTA_RESTRICT header, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Write a GTA header to a file descriptor.
 * \param header        The header.
 * \param fd            The file descriptor.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 */
extern GTA_EXPORT gta_result_t
gta_write_header_to_fd(const gta_header_t *GTA_RESTRICT header, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/*@}*/


/**
 *
 * \name Access GTA Headers
 *
 */

/*@{*/

/**
 * \brief               Get the global tag list (non-modifiable).
 * \param header        The header.
 * \return              The global tag list (non-modifiable).
 */
extern GTA_EXPORT const gta_taglist_t *
gta_get_global_taglist_const(const gta_header_t *GTA_RESTRICT header)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the global tag list (modifiable).
 * \param header        The header.
 * \return              The global tag list (modifiable).
 */
extern GTA_EXPORT gta_taglist_t *
gta_get_global_taglist(gta_header_t *GTA_RESTRICT header)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Return the size of an array element.
 * \param header        The header.
 * \return              The size of an array element, which is the sum of the component sizes.
 */
extern GTA_EXPORT uintmax_t
gta_get_element_size(const gta_header_t *GTA_RESTRICT header)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the number of components.
 * \param header        The header.
 * \return              The number of components in an array element.
 */
extern GTA_EXPORT uintmax_t
gta_get_components(const gta_header_t *GTA_RESTRICT header)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the type of a component.
 * \param header        The header.
 * \param i             The component index.
 * \return              The type of the element component.
 */
extern GTA_EXPORT gta_type_t
gta_get_component_type(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the size of a component.
 * \param header        The header.
 * \param i             The component index.
 * \return              The size (in bytes) of the element component.
 */
extern GTA_EXPORT uintmax_t
gta_get_component_size(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the tag list of a component (non-modifiable).
 * \param header        The header.
 * \param i             The component index.
 * \return              The tag list of the element component (non-modifiable).
 */
extern GTA_EXPORT const gta_taglist_t *
gta_get_component_taglist_const(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the tag list of a component (modifiable).
 * \param header        The header.
 * \param i             The component index.
 * \return              The tag list of the element component (modifiable).
 */
extern GTA_EXPORT gta_taglist_t *
gta_get_component_taglist(gta_header_t *GTA_RESTRICT header, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the number of dimensions.
 * \param header        The header.
 * \return              The number of dimensions of the array data.
 */
extern GTA_EXPORT uintmax_t
gta_get_dimensions(const gta_header_t *GTA_RESTRICT header)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the size in a dimension.
 * \param header        The header.
 * \param i             The dimension index.
 * \return              The size of the array in the given dimension.
 */
extern GTA_EXPORT uintmax_t
gta_get_dimension_size(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the tag list of a dimension (non-modifiable).
 * \param header        The header.
 * \param i             The dimension index.
 * \return              The tag list of the dimension (non-modifiable).
 */
extern GTA_EXPORT const gta_taglist_t *
gta_get_dimension_taglist_const(const gta_header_t *GTA_RESTRICT header, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the tag list of a dimension (modifiable).
 * \param header        The header.
 * \param i             The dimension index.
 * \return              The tag list of the dimension (modifiable).
 */
extern GTA_EXPORT gta_taglist_t *
gta_get_dimension_taglist(gta_header_t *GTA_RESTRICT header, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the total number of elements in the array.
 * \param header        The header.
 * \return              The total number of elements in the array.
 */
extern GTA_EXPORT uintmax_t
gta_get_elements(const gta_header_t *GTA_RESTRICT header)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the total size of the array data.
 * \param header        The header.
 * \return              The total size (in bytes) of the array data.
 */
extern GTA_EXPORT uintmax_t
gta_get_data_size(const gta_header_t *GTA_RESTRICT header)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the compression.
 * \param header        The header.
 * \return              The compression type.
 *
 * Gets the compression type for the header and data. Compression
 * is deprecated so the return value should always be GTA_NONE, unless
 * you read legacy files.
 * This function will be removed in a future version.
 */
extern GTA_EXPORT gta_compression_t
gta_get_compression(const gta_header_t *GTA_RESTRICT header)
GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Set the compression.
 * \param header        The header.
 * \param compression   The compression type.
 *
 * Sets the compression type for writing the header and data.
 * Compression is deprecated and this function actually does nothing.
 * This function will be removed in a future version.
 */
extern GTA_EXPORT void
gta_set_compression(gta_header_t *GTA_RESTRICT header, gta_compression_t compression)
GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/*@}*/


/**
 *
 * \name Define an Array
 *
 */


/*@{*/

/**
 * \brief               Set the components of an array element.
 * \param header        The header.
 * \param n             The number of components.
 * \param types         The types of the \a n components.
 * \param sizes         NULL, or the sizes of the components that have type \a GTA_BLOB.
 * \return              \a GTA_OK, \a GTA_OVERFLOW, \a GTA_UNSUPPORTED_DATA, or \a GTA_SYSTEM_ERROR.
 *
 * Set the components of the array elements.\n
 * The \a sizes parameter can be NULL if no components have the type \a GTA_BLOB.
 * Otherwise, it must point to a list that contains the sizes of these components (and only
 * these components). For example, if there are five components, but only two have the type
 * \a GTA_BLOB, then the \a sizes list must contain two size values.\n
 * All components will initially have an empty tag list.\n
 */
extern GTA_EXPORT gta_result_t
gta_set_components(gta_header_t *GTA_RESTRICT header, uintmax_t n, const gta_type_t *GTA_RESTRICT types, const uintmax_t *GTA_RESTRICT sizes)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL1(1) GTA_ATTR_NOTHROW;

/**
 * \brief               Set the dimensions.
 * \param header        The header.
 * \param n             The number of dimensions.
 * \param sizes         The array sizes in each of the \n dimensions.
 * \return              \a GTA_OK, \a GTA_OVERFLOW, \a GTA_INVALID_DATA, or \a GTA_SYSTEM_ERROR.
 *
 * Sets the array dimensions.\n
 * All dimensions will initially have an empty tag list.
 */
extern GTA_EXPORT gta_result_t
gta_set_dimensions(gta_header_t *GTA_RESTRICT header, uintmax_t n, const uintmax_t *GTA_RESTRICT sizes)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL1(1) GTA_ATTR_NOTHROW;

/*@}*/


/**
 *
 * \name Access Tag Lists
 *
 */

/*@{*/

/**
 * \brief               Get the number of tags in a tag list.
 * \param taglist       The tag list.
 * \return              The number of tags in the list.
 */
extern GTA_EXPORT uintmax_t
gta_get_tags(const gta_taglist_t *GTA_RESTRICT taglist)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the tag name with the given index.
 * \param taglist       The tag list.
 * \param i             The tag index.
 * \return              The name of the tag.
 */
extern GTA_EXPORT const char *
gta_get_tag_name(const gta_taglist_t *GTA_RESTRICT taglist, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the tag value with the given index.
 * \param taglist       The tag list.
 * \param i             The tag index.
 * \return              The value of the tag.
 */
extern GTA_EXPORT const char *
gta_get_tag_value(const gta_taglist_t *GTA_RESTRICT taglist, uintmax_t i)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get a tag value by its name.
 * \param taglist       The tag list.
 * \param name          The tag name.
 * \return              The tag value, or NULL if the tag name is not found.
 */
extern GTA_EXPORT const char *
gta_get_tag(const gta_taglist_t *GTA_RESTRICT taglist, const char *GTA_RESTRICT name)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Set a tag.
 * \param taglist       The tag list.
 * \param name          The name.
 * \param value         The value.
 * \return              \a GTA_OK, \a GTA_INVALID_DATA, \a GTA_OVERFLOW, or \a GTA_SYSTEM_ERROR.
 *
 * Sets the given tag, possibly overwriting an existing tag with the same name.
 * The name and value must be valid UTF-8 strings without control characters.
 * Additionally, the name must not contain the equal sign and must not be empty.
 */
extern GTA_EXPORT gta_result_t
gta_set_tag(gta_taglist_t *GTA_RESTRICT taglist, const char *GTA_RESTRICT name, const char *GTA_RESTRICT value)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Unset a tag.
 * \param taglist       The tag list.
 * \param name          The tag name.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Removes the tag with the given name, if it exists.
 */
extern GTA_EXPORT gta_result_t
gta_unset_tag(gta_taglist_t *GTA_RESTRICT taglist, const char *GTA_RESTRICT name)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Unset all tags.
 * \param taglist       The tag list.
 *
 * Removes all tags from the tag list.
 */
extern GTA_EXPORT void
gta_unset_all_tags(gta_taglist_t *GTA_RESTRICT taglist)
GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Clone a tag list.
 * \param dst_taglist   The destination tag list.
 * \param src_taglist   The source tag list.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Copies \a src_taglist to \a dst_taglist.
 */
extern GTA_EXPORT gta_result_t
gta_clone_taglist(gta_taglist_t *GTA_RESTRICT dst_taglist,
        const gta_taglist_t *GTA_RESTRICT src_taglist)
GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/*@}*/


/**
 *
 * \name Read and Write Complete Arrays
 *
 * These functions are intended to be used by applications that know that all the data will fit into memory.
 */

/*@{*/

/**
 * \brief               Read the complete data.
 * \param header        The header.
 * \param data          The data buffer.
 * \param read_fn       The custom input function.
 * \param userdata      A parameter to the custom input function.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the complete data into the given buffer. The buffer must be large enough.
 */
extern GTA_EXPORT gta_result_t
gta_read_data(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, gta_read_t read_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief               Read the complete data from a stream.
 * \param header        The header.
 * \param data          The data buffer.
 * \param f             The stream.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the complete data into the given buffer. The buffer must be large enough.
 */
extern GTA_EXPORT gta_result_t
gta_read_data_from_stream(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Read the complete data from a file descriptor.
 * \param header        The header.
 * \param data          The data buffer.
 * \param fd            The file descriptor.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the complete data into the given buffer. The buffer must be large enough.
 */
extern GTA_EXPORT gta_result_t
gta_read_data_from_fd(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Skip the complete data.
 * \param header        The header.
 * \param read_fn       The custom input function.
 * \param seek_fn       The custom seek function, or NULL for non-seekable input.
 * \param userdata      A parameter to the custom input and seek functions.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Skips the complete data, so that the next GTA header can be read.
 */
extern GTA_EXPORT gta_result_t
gta_skip_data(const gta_header_t *GTA_RESTRICT header, gta_read_t read_fn, gta_seek_t seek_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL2(1, 2);

/**
 * \brief               Skip the complete data from a stream.
 * \param header        The header.
 * \param f             The stream.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Skips the complete data, so that the next GTA header can be read.
 */
extern GTA_EXPORT gta_result_t
gta_skip_data_from_stream(const gta_header_t *GTA_RESTRICT header, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Skip the complete data from a file descriptor.
 * \param header        The header.
 * \param fd            The file descriptor.
 * \return              \a GTA_OK, \a GTA_UNSUPPORTED_DATA, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Skips the complete data, so that the next GTA header can be read.
 */
extern GTA_EXPORT gta_result_t
gta_skip_data_from_fd(const gta_header_t *GTA_RESTRICT header, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Write the complete data.
 * \param header        The header.
 * \param data          The data buffer.
 * \param write_fn      The custom output function.
 * \param userdata      A parameter to the custom output function.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Writes the complete data.
 */
extern GTA_EXPORT gta_result_t
gta_write_data(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, gta_write_t write_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL2(1, 3);

/**
 * \brief               Write the complete data to a stream.
 * \param header        The header.
 * \param data          The data buffer.
 * \param f             The stream.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Writes the complete data.
 */
extern GTA_EXPORT gta_result_t
gta_write_data_to_stream(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL2(1, 3) GTA_ATTR_NOTHROW;

/**
 * \brief               Write the complete data to a file descriptor.
 * \param header        The header.
 * \param data          The data buffer.
 * \param fd            The file descriptor.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Writes the complete data.
 */
extern GTA_EXPORT gta_result_t
gta_write_data_to_fd(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL1(1) GTA_ATTR_NOTHROW;

/**
 * \brief               Copy the complete data.
 * \param read_header   The input header.
 * \param read_fn       The custom input function.
 * \param read_userdata A parameter to the custom input function.
 * \param write_header  The ourput header.
 * \param write_fn      The custom output function.
 * \param write_userdata A parameter to the custom output function.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Copies the complete data.
 * The data encoding is altered as necessary (endianness correction).
 * Note that the data encoding may change even if \a read_header and \a write_header
 * point to the same header!
 */
extern GTA_EXPORT gta_result_t
gta_copy_data(
        const gta_header_t *GTA_RESTRICT read_header, gta_read_t read_fn, intptr_t read_userdata,
        const gta_header_t *GTA_RESTRICT write_header, gta_write_t write_fn, intptr_t write_userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief               Copy the complete data between streams.
 * \param read_header   The input header.
 * \param read_f        The input stream.
 * \param write_header  The output header.
 * \param write_f       The output stream.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Copies the complete data.
 * The data encoding is altered as necessary (endianness correction).
 * Note that the data encoding may change even if \a read_header and \a write_header
 * point to the same header!
 */
extern GTA_EXPORT gta_result_t
gta_copy_data_stream(
        const gta_header_t *GTA_RESTRICT read_header, FILE *GTA_RESTRICT read_f,
        const gta_header_t *GTA_RESTRICT write_header, FILE *GTA_RESTRICT write_f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Copy the complete data between file descriptors.
 * \param read_header   The input header.
 * \param read_fd       The input file descriptor.
 * \param write_header  The output header.
 * \param write_fd      The output file descriptor.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Copies the complete data.
 * The data encoding is altered as necessary (endianness correction).
 * Note that the data encoding may change even if \a read_header and \a write_header
 * point to the same header!
 */
extern GTA_EXPORT gta_result_t
gta_copy_data_fd(
        const gta_header_t *GTA_RESTRICT read_header, int read_fd,
        const gta_header_t *GTA_RESTRICT write_header, int write_fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/*@}*/


/**
 *
 * \name In-Memory Data Access
 *
 */

/*@{*/

/**
 * \brief               Transform a linear index to array indices.
 * \param header        The header.
 * \param index         The linear index.
 * \param indices       The array indices.
 */
extern GTA_EXPORT void
gta_linear_index_to_indices(const gta_header_t *GTA_RESTRICT header, uintmax_t index, uintmax_t *GTA_RESTRICT indices)
GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Transform array indices to a linear index.
 * \param header        The header.
 * \param indices       The array indices.
 * \return              The linear index.
 */
extern GTA_EXPORT uintmax_t
gta_indices_to_linear_index(const gta_header_t *GTA_RESTRICT header, const uintmax_t *GTA_RESTRICT indices)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the address of an array element (non-modifiable).
 * \param header        The header.
 * \param data          The data.
 * \param indices       The indices for each dimension of the array.
 * \return              A pointer to the element.
 */
extern GTA_EXPORT const void *
gta_get_element_const(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, const uintmax_t *GTA_RESTRICT indices)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the address of an array element (modifiable).
 * \param header        The header.
 * \param data          The data.
 * \param indices       The indices for each dimension of the array.
 * \return              A pointer to the element.
 */
extern GTA_EXPORT void *
gta_get_element(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, const uintmax_t *GTA_RESTRICT indices)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the address of an array element (non-modifiable).
 * \param header        The header.
 * \param data          The data.
 * \param index         The linear index of the element.
 * \return              A pointer to the element.
 */
extern GTA_EXPORT const void *
gta_get_element_linear_const(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT data, uintmax_t index)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the address of an array element (modifiable).
 * \param header        The header.
 * \param data          The data.
 * \param index         The linear index of the element.
 * \return              A pointer to the element.
 */
extern GTA_EXPORT void *
gta_get_element_linear(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT data, uintmax_t index)
GTA_ATTR_NONNULL_ALL GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the address of a component of an array element (non-modifiable).
 * \param header        The header.
 * \param element       The element.
 * \param i             The component index.
 * \return              A pointer to the component.
 */
extern GTA_EXPORT const void *
gta_get_component_const(const gta_header_t *GTA_RESTRICT header, const void *GTA_RESTRICT element, uintmax_t i)
GTA_ATTR_NONNULL1(1) GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/**
 * \brief               Get the address of a component of an array element (modifiable).
 * \param header        The header.
 * \param element       The element.
 * \param i             The component index.
 * \return              A pointer to the component.
 */
extern GTA_EXPORT void *
gta_get_component(const gta_header_t *GTA_RESTRICT header, void *GTA_RESTRICT element, uintmax_t i)
GTA_ATTR_NONNULL1(1) GTA_ATTR_PURE GTA_ATTR_NOTHROW;

/*@}*/


/**
 *
 * \name Read and Write Array Elements
 *
 * These functions are intended to be used for filtering a complete array on a per-element basis.
 * They read or write a given number of elements, and it is expected that they are used
 * repeatedly until all elements of an array have been read or written.
 * Theses function work for all GTAs, an the input and output streams
 * do not need to be seekable.
 *
 * Element-based input/output needs a state structure. This structure must be allocated with
 * gta_create_io_state() before the first element is read or written, and freed with
 * gta_destroy_io_state() after the last element was read or written, or after an error occured.
 */

/*@{*/

/**
 * \brief               Create and initialize a new input/output state.
 * \param io_state      The input/output state.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Creates and initializes a state structure for element-based input/output.
 */
extern GTA_EXPORT gta_result_t
gta_create_io_state(gta_io_state_t *GTA_RESTRICT *GTA_RESTRICT io_state)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Clone an input/output state.
 * \param dst_io_state  The destination state.
 * \param src_io_state  The source state.
 * \return              \a GTA_OK or \a GTA_SYSTEM_ERROR.
 *
 * Clones \a src_io_state into \a dst_io_state.
 */
extern GTA_EXPORT gta_result_t
gta_clone_io_state(gta_io_state_t *GTA_RESTRICT dst_io_state,
        const gta_io_state_t *GTA_RESTRICT src_io_state)
GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Destroy input/output state and free its resources.
 * \param io_state      The input/output state.
 *
 * Destroys a state structure for element-based input/output and frees its resources.
 */
extern GTA_EXPORT void
gta_destroy_io_state(gta_io_state_t *GTA_RESTRICT io_state)
GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief               Read array elements.
 * \param header        The header.
 * \param io_state      The input/output state.
 * \param n             The number of elements to read.
 * \param buf           The buffer for the elements.
 * \param read_fn       The custom input function.
 * \param userdata      A parameter to the custom input function.
 * \return              \a GTA_OK, \a GTA_OVERFLOW, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the given number of elements into the given buffer, which must be large enough.
 */
extern GTA_EXPORT gta_result_t
gta_read_elements(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, void *GTA_RESTRICT buf, gta_read_t read_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief               Read array elements.
 * \param header        The header.
 * \param io_state      The input/output state.
 * \param n             The number of elements to read.
 * \param buf           The buffer for the elements.
 * \param f             The stream.
 * \return              \a GTA_OK, \a GTA_INVALID_DATA, \a GTA_OVERFLOW, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the given number of elements into the given buffer, which must be large enough.
 */
extern GTA_EXPORT gta_result_t
gta_read_elements_from_stream(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, void *GTA_RESTRICT buf, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief               Read array elements.
 * \param header        The header.
 * \param io_state      The input/output state.
 * \param n             The number of elements to read.
 * \param buf           The buffer for the elements.
 * \param fd            The file descriptor.
 * \return              \a GTA_OK, \a GTA_INVALID_DATA, \a GTA_OVERFLOW, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the given number of elements into the given buffer, which must be large enough.
 */
extern GTA_EXPORT gta_result_t
gta_read_elements_from_fd(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, void *GTA_RESTRICT buf, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief               Write array elements.
 * \param header        The header.
 * \param io_state      The input/output state.
 * \param n             The number of elements to write.
 * \param buf           The buffer for the elements.
 * \param write_fn      The custom output function.
 * \param userdata      A parameter to the custom output function.
 * \return              \a GTA_OK, \a GTA_INVALID_DATA, \a GTA_OVERFLOW, or \a GTA_SYSTEM_ERROR.
 *
 * Writes the given number of elements from the given buffer.
 */
extern GTA_EXPORT gta_result_t
gta_write_elements(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, const void *GTA_RESTRICT buf, gta_write_t write_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief               Write array elements.
 * \param header        The header.
 * \param io_state      The input/output state.
 * \param n             The number of elements to write.
 * \param buf           The buffer for the elements.
 * \param f             The stream.
 * \return              \a GTA_OK, \a GTA_INVALID_DATA, \a GTA_OVERFLOW, or \a GTA_SYSTEM_ERROR.
 *
 * Writes the given number of elements from the given buffer.
 */
extern GTA_EXPORT gta_result_t
gta_write_elements_to_stream(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, const void *GTA_RESTRICT buf, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief               Write array elements.
 * \param header        The header.
 * \param io_state      The input/output state.
 * \param n             The number of elements to write.
 * \param buf           The buffer for the elements.
 * \param fd            The file descriptor.
 * \return              \a GTA_OK, \a GTA_INVALID_DATA, \a GTA_OVERFLOW, or \a GTA_SYSTEM_ERROR.
 *
 * Writes the given number of elements from the given buffer.
 */
extern GTA_EXPORT gta_result_t
gta_write_elements_to_fd(const gta_header_t *GTA_RESTRICT header, gta_io_state_t *GTA_RESTRICT io_state,
        uintmax_t n, const void *GTA_RESTRICT buf, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;


/*@}*/


/**
 *
 * \name Read and Write Array Blocks
 *
 * These functions can only be used if the input/output is seekable.\n
 * They are suitable for applications that do not want to store the complete array data in
 * memory.\n
 * A block is given by the lowest and highest element coordinates in each dimension.
 * For example, for a 2D array from which we want a rectangle of 20x10 elements starting at
 * element (5,3), we would store the values (5,3) in \a lower_coordinates and (24, 12) in
 * \a higher_coordinates.
 */

/*@{*/

/**
 * \brief                       Read an array block.
 * \param header                The header.
 * \param data_offset           Offset of the first data byte.
 * \param lower_coordinates     Coordinates of the lower corner element of the block.
 * \param higher_coordinates    Coordinates of the higher corner element of the block.
 * \param block                 The block buffer.
 * \param read_fn               The custom input function.
 * \param seek_fn               The custom seek function.
 * \param userdata              A parameter to the custom input function.
 * \return                      \a GTA_OK, \a GTA_UNSUPPORTED_DATA (if the data is compressed), \a GTA_OVERFLOW, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the given array block and copies it to the given block buffer, which must be large enough.\n
 * This function modifies the file position indicator of the input.
 */
extern GTA_EXPORT gta_result_t
gta_read_block(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        void *GTA_RESTRICT block, gta_read_t read_fn, gta_seek_t seek_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief                       Read an array block from a stream.
 * \param header                The header.
 * \param data_offset           Offset of the first data byte.
 * \param lower_coordinates     Coordinates of the lower corner element of the block.
 * \param higher_coordinates    Coordinates of the higher corner element of the block.
 * \param block                 The block buffer.
 * \param f                     The stream.
 * \return                      \a GTA_OK, \a GTA_UNSUPPORTED_DATA (if the data is compressed), \a GTA_OVERFLOW, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the given array block and copies it to the given block buffer, which must be large enough.\n
 * This function modifies the file position indicator of the input.
 */
extern GTA_EXPORT gta_result_t
gta_read_block_from_stream(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        void *GTA_RESTRICT block, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief                       Read an array block from a file descriptor.
 * \param header                The header.
 * \param data_offset           Offset of the first data byte.
 * \param lower_coordinates     Coordinates of the lower corner element of the block.
 * \param higher_coordinates    Coordinates of the higher corner element of the block.
 * \param block                 The block buffer.
 * \param fd                    The file descriptor.
 * \return                      \a GTA_OK, \a GTA_UNSUPPORTED_DATA (if the data is compressed), \a GTA_OVERFLOW, \a GTA_UNEXPECTED_EOF, or \a GTA_SYSTEM_ERROR.
 *
 * Reads the given array block and copies it to the given block buffer, which must be large enough.\n
 * This function modifies the file position indicator of the input.
 */
extern GTA_EXPORT gta_result_t
gta_read_block_from_fd(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        void *GTA_RESTRICT block, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief                       Write an array block.
 * \param header                The header.
 * \param data_offset           Offset of the first data byte.
 * \param lower_coordinates     Coordinates of the lower corner element of the block.
 * \param higher_coordinates    Coordinates of the higher corner element of the block.
 * \param block                 The block buffer.
 * \param write_fn              The custom output function.
 * \param seek_fn               The custom seek function.
 * \param userdata              A parameter to the custom output function.
 * \return                      \a GTA_OK, \a GTA_UNSUPPORTED_DATA (if the data is compressed), \a GTA_OVERFLOW, or \a GTA_SYSTEM_ERROR.
 *
 * This function modifies the file position indicator of the output.
 */
extern GTA_EXPORT gta_result_t
gta_write_block(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        const void *GTA_RESTRICT block, gta_write_t write_fn, gta_seek_t seek_fn, intptr_t userdata)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL;

/**
 * \brief                       Write an array block to a stream.
 * \param header                The header.
 * \param data_offset           Offset of the first data byte.
 * \param lower_coordinates     Coordinates of the lower corner element of the block.
 * \param higher_coordinates    Coordinates of the higher corner element of the block.
 * \param block                 The block buffer.
 * \param f                     The stream.
 * \return                      \a GTA_OK, \a GTA_UNSUPPORTED_DATA (if the data is compressed), \a GTA_OVERFLOW, or \a GTA_SYSTEM_ERROR.
 *
 * This function modifies the file position indicator of the output.
 */
extern GTA_EXPORT gta_result_t
gta_write_block_to_stream(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        const void *GTA_RESTRICT block, FILE *GTA_RESTRICT f)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/**
 * \brief                       Write an array block to a file descriptor.
 * \param header                The header.
 * \param data_offset           Offset of the first data byte.
 * \param lower_coordinates     Coordinates of the lower corner element of the block.
 * \param higher_coordinates    Coordinates of the higher corner element of the block.
 * \param block                 The block buffer.
 * \param fd                    The file descriptor.
 * \return                      \a GTA_OK, \a GTA_UNSUPPORTED_DATA (if the data is compressed), \a GTA_OVERFLOW, \a GTA_SYSTEM_ERROR.
 *
 * This function modifies the file position indicator of the output.
 */
extern GTA_EXPORT gta_result_t
gta_write_block_to_fd(const gta_header_t *GTA_RESTRICT header, intmax_t data_offset,
        const uintmax_t *GTA_RESTRICT lower_coordinates, const uintmax_t *GTA_RESTRICT higher_coordinates,
        const void *GTA_RESTRICT block, int fd)
GTA_ATTR_WARN_UNUSED_RESULT GTA_ATTR_NONNULL_ALL GTA_ATTR_NOTHROW;

/*@}*/


#ifdef __cplusplus
}
#endif

#endif
