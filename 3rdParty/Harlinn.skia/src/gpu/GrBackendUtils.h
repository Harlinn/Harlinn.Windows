/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrBackendUtils_DEFINED
#define GrBackendUtils_DEFINED

#include <skia/core/SkImage.h>

#include <skia/gpu/GrBackendSurface.h>

SK_API SkImage::CompressionType GrBackendFormatToCompressionType(const GrBackendFormat& format);

// Returns the number of bytes per texel block for the given format. All non compressed formats
// are treated as having a block size of 1x1, so this is equivalent to bytesPerPixel.
SK_API size_t GrBackendFormatBytesPerBlock(const GrBackendFormat& format);

// Returns the number of bytes per pixel for the given format. All compressed formats will return 0.
SK_API size_t GrBackendFormatBytesPerPixel(const GrBackendFormat& format);

SK_API int GrBackendFormatStencilBits(const GrBackendFormat& format);

#endif
