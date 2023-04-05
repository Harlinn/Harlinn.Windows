/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef ProxyUtils_DEFINED
#define ProxyUtils_DEFINED

#include "skia/private/GrTypesPriv.h"
#include "src/gpu/GrImageInfo.h"
#include "src/gpu/GrPipeline.h"
#include "src/gpu/GrTextureProxy.h"

class GrGeometryProcessor;
class GrDirectContext;
class GrProgramInfo;
class GrCPixmap;

namespace sk_gpu_test {

/** Returns the proxy backing an image if it is texture backed, otherwise nullptr. */
SK_API GrTextureProxy* GetTextureImageProxy(SkImage*, GrRecordingContext*);

/** Makes a texture proxy containing the passed in color data. */
SK_API GrSurfaceProxyView MakeTextureProxyViewFromData(GrDirectContext*,
                                                GrRenderable,
                                                GrSurfaceOrigin,
                                                GrCPixmap pixmap);

#if SK_GPU_V1
SK_API GrProgramInfo* CreateProgramInfo(const GrCaps*,
                                 SkArenaAlloc*,
                                 const GrSurfaceProxyView& writeView,
                                 bool usesMSAASurface,
                                 GrAppliedClip&&,
                                 const GrDstProxyView&,
                                 GrGeometryProcessor*,
                                 SkBlendMode,
                                 GrPrimitiveType,
                                 GrXferBarrierFlags renderPassXferBarriers,
                                 GrLoadOp colorLoadOp,
                                 GrPipeline::InputFlags flags = GrPipeline::InputFlags::kNone,
                                 const GrUserStencilSettings* stencil =
                                                                &GrUserStencilSettings::kUnused);
#endif

}  // namespace sk_gpu_test

#endif
