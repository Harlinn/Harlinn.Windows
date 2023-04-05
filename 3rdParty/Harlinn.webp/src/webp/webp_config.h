#pragma once
#ifndef HAVE_WEBP_CONFIG_H
#define HAVE_WEBP_CONFIG_H 1

/* Adapted from the autotools src/webp/config.h.in.  */



/* Define if building universal (internal helper macro) */
/* TODO: handle properly in CMake */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Set to 1 if __builtin_bswap16 is available */
/* #undef HAVE_BUILTIN_BSWAP16 */

/* Set to 1 if __builtin_bswap32 is available */
/* #undef HAVE_BUILTIN_BSWAP32 */

/* Set to 1 if __builtin_bswap64 is available */
/* #undef HAVE_BUILTIN_BSWAP64 */

/* Define to 1 if you have the <cpu-features.h> header file. */
/* #undef HAVE_CPU_FEATURES_H */

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if you have the <GLUT/glut.h> header file. */
/* #undef HAVE_GLUT_GLUT_H */

/* Define to 1 if you have the <GL/glut.h> header file. */
/* #undef HAVE_GL_GLUT_H */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <OpenGL/glut.h> header file. */
/* #undef HAVE_OPENGL_GLUT_H */

/* Have PTHREAD_PRIO_INHERIT. */
/* #undef HAVE_PTHREAD_PRIO_INHERIT */

/* Define to 1 if you have the <shlwapi.h> header file. */
#define HAVE_SHLWAPI_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */

/* Define to 1 if you have the <wincodec.h> header file. */
#define HAVE_WINCODEC_H 1

/* Define to 1 if you have the <windows.h> header file. */
#define HAVE_WINDOWS_H 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
/* TODO: handle properly in CMake */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "WebP"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://bugs.chromium.org/p/webp"

/* Define to the full name of this package. */
#define PACKAGE_NAME "WebP"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "WebP 1.2.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "WebP"

/* Define to the home page for this package. */
#define PACKAGE_URL "http://developers.google.com/speed/webp"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.2.1"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "1.2.1"

/* Set to 1 if GIF library is installed */
#define WEBP_HAVE_GIF 1

/* Set to 1 if OpenGL is supported */
#define WEBP_HAVE_GL 1

/* Set to 1 if JPEG library is installed */
#define WEBP_HAVE_JPEG 1

/* Set to 1 if NEON is supported */
/* #undef WEBP_HAVE_NEON */

/* Set to 1 if runtime detection of NEON is enabled */
/* TODO: handle properly in CMake */
/* #undef WEBP_HAVE_NEON_RTCD */

/* Set to 1 if PNG library is installed */
#define WEBP_HAVE_PNG 1

/* Set to 1 if SDL library is installed */
// #define WEBP_HAVE_SDL 1

/* Set to 1 if SSE2 is supported */
#define WEBP_HAVE_SSE2 1

/* Set to 1 if SSE4.1 is supported */
#define WEBP_HAVE_SSE41 1

/* Set to 1 if TIFF library is installed */
#define WEBP_HAVE_TIFF 1

/* Enable near lossless encoding */
#define WEBP_NEAR_LOSSLESS 1

/* Undefine this to disable thread support. */
#define WEBP_USE_THREAD 1

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif
#endif