/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrDataUtils_DEFINED
#define GrDataUtils_DEFINED

#include <skia/core/SkColor.h>
#include <skia/private/GrTypesPriv.h>
#include <skia/private/SkTArray.h>

class GrImageInfo;
class GrCPixmap;
class GrPixmap;
class SkPixmap;

SK_API size_t GrNumBlocks(SkImage::CompressionType, SkISize baseDimensions);

// Returns a value that can be used to set rowBytes for a transfer function.
SK_API size_t GrCompressedRowBytes(SkImage::CompressionType, int w);

// Return the pixel dimensions of a compressed texture. The topmost levels
// of a compressed mipmapped texture (i.e., 1x1 or 2x2) still occupy a full
// block and thus objectively take up more pixels (e.g., 4x4 pixels for ETC1).
SK_API SkISize GrCompressedDimensions(SkImage::CompressionType, SkISize baseDimensions);

// Compute the size of the buffer required to hold all the mipLevels of the specified type
// of data when all rowBytes are tight.
// Note there may still be padding between the mipLevels to meet alignment requirements.
SK_API size_t GrComputeTightCombinedBufferSize(size_t bytesPerPixel, SkISize baseDimensions,
                                        SkTArray<size_t>* individualMipOffsets, int mipLevelCount);

SK_API void GrFillInCompressedData(SkImage::CompressionType, SkISize dimensions, GrMipmapped, char* dest,
                            const SkColor4f& color);

SK_API bool GrConvertPixels(const GrPixmap& dst, const GrCPixmap& src, bool flipY = false);

/** Clears the dst image to a constant color. */
SK_API bool GrClearImage(const GrImageInfo& dstInfo, void* dst, size_t dstRB, std::array<float, 4> color);

#if GR_TEST_UTILS
/**
 * BC1 compress an image that contains only either opaque black or transparent black and one
 * other color.
 *   opaque pixmaps      -> kBC1_RGB8_UNORM
 *   transparent pixmaps -> kBC1_RGBA8_UNORM
 */
SK_API void GrTwoColorBC1Compress(const SkPixmap& pixmap, SkColor otherColor, char* dstPixels);
#endif

#endif
