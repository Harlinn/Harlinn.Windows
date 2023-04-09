#pragma once

/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkUserConfig_DEFINED
#define SkUserConfig_DEFINED

/*  SkTypes.h, the root of the public header files, includes this file
    SkUserConfig.h after first initializing certain Skia defines, letting
    this file change or augment those flags.

    Below are optional defines that add, subtract, or change default behavior
    in Skia. Your port can locally edit this file to enable/disable flags as
    you choose, or these can be delared on your command line (i.e. -Dfoo).

    By default, this include file will always default to having all of the flags
    commented out, so including it will have no effect.
*/

///////////////////////////////////////////////////////////////////////////////

/*  Skia has lots of debug-only code. Often this is just null checks or other
    parameter checking, but sometimes it can be quite intrusive (e.g. check that
    each 32bit pixel is in premultiplied form). This code can be very useful
    during development, but will slow things down in a shipping product.

    By default, these mutually exclusive flags are defined in SkTypes.h,
    based on the presence or absence of NDEBUG, but that decision can be changed
    here.
 */
//#define SK_DEBUG
//#define SK_RELEASE

/*  To write debug messages to a console, skia will call SkDebugf(...) following
    printf conventions (e.g. const char* format, ...). If you want to redirect
    this to something other than printf, define yours here
 */
//#define SkDebugf(...)  MyFunction(__VA_ARGS__)

/*
 *  To specify a different default font cache limit, define this. If this is
 *  undefined, skia will use a built-in value.
 */
//#define SK_DEFAULT_FONT_CACHE_LIMIT   (1024 * 1024)

/*
 *  To specify the default size of the image cache, undefine this and set it to
 *  the desired value (in bytes). SkGraphics.h as a runtime API to set this
 *  value as well. If this is undefined, a built-in value will be used.
 */
//#define SK_DEFAULT_IMAGE_CACHE_LIMIT (1024 * 1024)

/*  Define this to set the upper limit for text to support LCD. Values that
    are very large increase the cost in the font cache and draw slower, without
    improving readability. If this is undefined, Skia will use its default
    value (e.g. 48)
 */
//#define SK_MAX_SIZE_FOR_LCDTEXT     48

/*  Change the kN32_SkColorType ordering to BGRA to work in X windows.
 */
//#define SK_R32_SHIFT    16


/* Determines whether to build code that supports the GPU backend. Some classes
   that are not GPU-specific, such as SkShader subclasses, have optional code
   that is used allows them to interact with the GPU backend. If you'd like to
   omit this code set SK_SUPPORT_GPU to 0. This also allows you to omit the gpu
   directories from your include search path when you're not building the GPU
   backend. Defaults to 1 (build the GPU code).
 */
#define SK_SUPPORT_GPU 1

/* Skia makes use of histogram logging macros to trace the frequency of
 * events. By default, Skia provides no-op versions of these macros.
 * Skia consumers can provide their own definitions of these macros to
 * integrate with their histogram collection backend.
 */
//#define SK_HISTOGRAM_BOOLEAN(name, sample)
//#define SK_HISTOGRAM_ENUMERATION(name, sample, enum_size)
//#define SK_HISTOGRAM_EXACT_LINEAR(name, sample, value_max)
//#define SK_HISTOGRAM_MEMORY_KB(name, sample)


#ifndef SK_HAS_HEIF_LIBRARY
#define SK_HAS_HEIF_LIBRARY 1
#endif

#ifndef SK_CODEC_DECODES_PNG
#define SK_CODEC_DECODES_PNG 1
#endif

#ifndef SK_GL
#define SK_GL 1
#endif

#ifndef SK_DIRECT3D
#define SK_DIRECT3D 1
#endif
#ifndef GR_TEST_UTILS
#define GR_TEST_UTILS 1
#endif

#ifndef SK_ENABLE_DISCRETE_GPU
#define SK_ENABLE_DISCRETE_GPU 1
#endif

#ifndef SK_ANGLE
//#define SK_ANGLE 1
#endif

#ifndef SK_VULKAN
#define SK_VULKAN 1
#endif

#ifndef SK_USE_VMA
#define SK_USE_VMA 1
#endif


#ifndef SK_USE_DISCARDABLE_SCALEDIMAGECACHE
#define SK_USE_DISCARDABLE_SCALEDIMAGECACHE 1
#endif

#ifndef SK_USE_WIC_ENCODER
#define SK_USE_WIC_ENCODER 1
#endif


#ifndef SK_HAS_WUFFS_LIBRARY
#define SK_HAS_WUFFS_LIBRARY 1
#endif

#ifndef SK_USE_LIBGIFCODEC
#define SK_USE_LIBGIFCODEC 1
#endif

#ifndef SK_CODEC_DECODES_JPEG
#define SK_CODEC_DECODES_JPEG 1
#endif

#ifndef SK_CODEC_DECODES_WEBP
#define SK_CODEC_DECODES_WEBP 1
#endif

#ifndef SK_CODEC_DECODES_RAW
#define SK_CODEC_DECODES_RAW 1
#endif

#ifndef SK_ENCODE_JPEG
#define SK_ENCODE_JPEG 1
#endif

#ifndef SK_ENCODE_PNG
#define SK_ENCODE_PNG 1
#endif

#ifndef SK_ENCODE_WEBP
#define SK_ENCODE_WEBP 1
#endif

#ifndef SK_ENABLE_SPIRV_VALIDATION
#define SK_ENABLE_SPIRV_VALIDATION 1
#endif

#ifndef SK_USING_THIRD_PARTY_ICU
//#define SK_USING_THIRD_PARTY_ICU 1
#endif

#ifndef SK_SHAPER_HARFBUZZ_AVAILABLE
#define SK_SHAPER_HARFBUZZ_AVAILABLE 1
#endif

#ifndef SK_UNICODE_AVAILABLE
#define SK_UNICODE_AVAILABLE 1
#endif

#endif
