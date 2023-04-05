#pragma once
#ifndef HARLINN_WINDOWS_BISON_CONFIG_H_
#define HARLINN_WINDOWS_BISON_CONFIG_H_ 1

#define _GL_INLINE_HEADER_BEGIN 
#ifndef GL_LIST_INLINE
#define GL_LIST_INLINE static inline
#endif

#ifndef _GL_EXTERN_INLINE
#define _GL_EXTERN_INLINE static inline
#endif

#include <io.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define ssize_t ptrdiff_t

#define _GL_INLINE_HEADER_BEGIN
#define _GL_INLINE_HEADER_END
#define _GL_ATTRIBUTE_PURE
#define _GL_ATTRIBUTE_CONST
#define _GL_UNUSED
#define _GL_ATTRIBUTE_NODISCARD
#define _GL_ATTRIBUTE_MAYBE_UNUSED
#define HAVE_LONG_LONG_INT 1
# define _GL_ATTRIBUTE_FORMAT(spec) /* empty */
#define HAVE_DECL_STRERROR_R 1
#define HAVE_DECL___ARGV 1
#define _GL_ARG_NONNULL(a)
#define _GL_ATTRIBUTE_FORMAT_PRINTF(a, b)
#define _GL_ATTRIBUTE_DEPRECATED
#define _GL_ATTRIBUTE_FALLTHROUGH
#define GNULIB_XALLOC 1
#define _GL_ATTRIBUTE_MALLOC
#define _GL_ATTRIBUTE_ALLOC_SIZE(a)
#define GNULIB_XALLOC_DIE 1
#define _GL_HAVE__STATIC_ASSERT
#define _Static_assert(a, b)
#define __PGI

#define MIN min
#define _GL_CMP(a, b) (a) == (b)

#define __getopt_argv_const
#define _Noreturn

#ifndef _GL_INLINE
#define _GL_INLINE inline
#endif

#ifndef FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE
#define FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE 1
#endif

#define PACKAGE_BUGREPORT "https://github.com/harlinn"
#define VERSION "3.7.6"
#define PACKAGE_COPYRIGHT_YEAR 2021
#define LOCALEDIR ""
#define PACKAGE_STRING "bison"
#define PACKAGE_URL "https://github.com/harlinn"
#define PACKAGE ""
#define PACKAGE_VERSION "3.7.6"
#define PACKAGE_NAME "bison"
#define PKGDATADIR "data"
#define RENAME_OPEN_FILE_WORKS 1


#endif
