/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef TestSurface_DEFINED
#define TestSurface_DEFINED

#include "skia/core/SkImageInfo.h"
#include "skia/core/SkSize.h"
#include "skia/gpu/GrTypes.h"
#include "skia/private/SkColorData.h"

class GrDirectContext;
class SkSurface;
class SkSurfaceProps;

namespace sk_gpu_test {

SK_API sk_sp<SkSurface> MakeBackendTextureSurface(GrDirectContext*,
                                           const SkImageInfo&,
                                           GrSurfaceOrigin,
                                           int sampleCnt,
                                           GrMipmapped = GrMipmapped::kNo,
                                           GrProtected = GrProtected::kNo,
                                           const SkSurfaceProps* = nullptr);

SK_API sk_sp<SkSurface> MakeBackendTextureSurface(GrDirectContext*,
                                           SkISize,
                                           GrSurfaceOrigin,
                                           int sampleCnt,
                                           SkColorType,
                                           sk_sp<SkColorSpace> = nullptr,
                                           GrMipmapped = GrMipmapped::kNo,
                                           GrProtected = GrProtected::kNo,
                                           const SkSurfaceProps* = nullptr);

/** Creates an SkSurface backed by a non-textureable render target. */
SK_API sk_sp<SkSurface> MakeBackendRenderTargetSurface(GrDirectContext*,
                                                const SkImageInfo&,
                                                GrSurfaceOrigin,
                                                int sampleCnt,
                                                GrProtected = GrProtected::kNo,
                                                const SkSurfaceProps* = nullptr);

SK_API sk_sp<SkSurface> MakeBackendRenderTargetSurface(GrDirectContext*,
                                                SkISize,
                                                GrSurfaceOrigin,
                                                int sampleCnt,
                                                SkColorType,
                                                sk_sp<SkColorSpace> = nullptr,
                                                GrProtected = GrProtected::kNo,
                                                const SkSurfaceProps* = nullptr);
}  // namespace sk_gpu_test

#endif
