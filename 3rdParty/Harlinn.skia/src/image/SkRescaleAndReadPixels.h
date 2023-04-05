/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkBitmap.h>
#include <skia/core/SkImage.h>
#include <skia/core/SkSamplingOptions.h>

struct SkImageInfo;
struct SkIRect;

/** Generic/synchronous implementation for SkImage:: and SkSurface::asyncRescaleAndReadPixels. */
void SkRescaleAndReadPixels(SkBitmap src,
                            const SkImageInfo& resultInfo,
                            const SkIRect& srcRect,
                            SkImage::RescaleGamma,
                            SkImage::RescaleMode,
                            SkImage::ReadPixelsCallback,
                            SkImage::ReadPixelsContext);
