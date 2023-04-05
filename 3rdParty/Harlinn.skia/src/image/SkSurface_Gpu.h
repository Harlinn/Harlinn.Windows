/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSurface_Gpu_DEFINED
#define SkSurface_Gpu_DEFINED

#include <skia/private/GrTypesPriv.h>
#include "src/image/SkSurface_Base.h"

#if SK_SUPPORT_GPU

class GrBackendFormat;
namespace skgpu { class BaseDevice; }

class SkSurface_Gpu : public SkSurface_Base {
public:
    SK_API SkSurface_Gpu(sk_sp<skgpu::BaseDevice>);
    SK_API ~SkSurface_Gpu() override;

    SK_API GrRecordingContext* onGetRecordingContext() override;

    SK_API GrBackendTexture onGetBackendTexture(BackendHandleAccess) override;
    SK_API GrBackendRenderTarget onGetBackendRenderTarget(BackendHandleAccess) override;
    SK_API bool onReplaceBackendTexture(const GrBackendTexture&, GrSurfaceOrigin, ContentChangeMode, TextureReleaseProc,
                                 ReleaseContext) override;

    SK_API SkCanvas* onNewCanvas() override;
    SK_API sk_sp<SkSurface> onNewSurface(const SkImageInfo&) override;
    SK_API sk_sp<SkImage> onNewImageSnapshot(const SkIRect* subset) override;
    SK_API void onWritePixels(const SkPixmap&, int x, int y) override;
    SK_API void onAsyncRescaleAndReadPixels(const SkImageInfo& info, const SkIRect& srcRect,
                                     RescaleGamma rescaleGamma, RescaleMode,
                                     ReadPixelsCallback callback,
                                     ReadPixelsContext context) override;
    SK_API void onAsyncRescaleAndReadPixelsYUV420(SkYUVColorSpace yuvColorSpace,
                                           sk_sp<SkColorSpace> dstColorSpace,
                                           const SkIRect& srcRect,
                                           const SkISize& dstSize,
                                           RescaleGamma rescaleGamma,
                                           RescaleMode,
                                           ReadPixelsCallback callback,
                                           ReadPixelsContext context) override;
    SK_API bool onCopyOnWrite(ContentChangeMode) override;
    SK_API void onDiscard() override;
    SK_API GrSemaphoresSubmitted onFlush(BackendSurfaceAccess access, const GrFlushInfo& info,
                                  const GrBackendSurfaceMutableState*) override;
    SK_API bool onWait(int numSemaphores, const GrBackendSemaphore* waitSemaphores,
                 bool deleteSemaphoresAfterWait) override;
    SK_API bool onCharacterize(SkSurfaceCharacterization*) const override;
    SK_API bool onIsCompatible(const SkSurfaceCharacterization&) const override;
    SK_API void onDraw(SkCanvas* canvas, SkScalar x, SkScalar y, const SkSamplingOptions&,
                const SkPaint* paint) override;
    SK_API bool onDraw(sk_sp<const SkDeferredDisplayList>, SkIPoint offset) override;

    SK_API skgpu::BaseDevice* getDevice();

private:
    sk_sp<skgpu::BaseDevice> fDevice;

    using INHERITED = SkSurface_Base;
};

#endif // SK_SUPPORT_GPU

#endif // SkSurface_Gpu_DEFINED
