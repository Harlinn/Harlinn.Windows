/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrAHardwareBufferImageGenerator_DEFINED
#define GrAHardwareBufferImageGenerator_DEFINED

#include <skia/core/SkImageGenerator.h>

#include <skia/private/GrTypesPriv.h>

class GrGpuResource;
class GrSurfaceProxyView;

extern "C" {
    typedef struct AHardwareBuffer AHardwareBuffer;
}

/**
 *  GrAHardwareBufferImageGenerator allows to create an SkImage attached to
 *  an existing android native hardware buffer. A hardware buffer has to be
 *  created with AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE usage, because it is
 *  bound to an external texture using an EGLImage. The image generator will
 *  keep a reference to the hardware buffer for its lifetime. A hardware buffer
 *  can be shared between processes and same buffer can be used in multiple GPU
 *  contexts.
 *  To implement certain features like tiling, Skia may copy the texture to
 *  avoid OpenGL API limitations.
 */
class GrAHardwareBufferImageGenerator : public SkImageGenerator {
public:
    SK_API static std::unique_ptr<SkImageGenerator> Make(AHardwareBuffer*, SkAlphaType,
                                                  sk_sp<SkColorSpace>, GrSurfaceOrigin);

    SK_API ~GrAHardwareBufferImageGenerator() override;

    SK_API static void DeleteGLTexture(void* ctx);

protected:

    SK_API bool onIsValid(GrRecordingContext*) const override;

    SK_API GrSurfaceProxyView onGenerateTexture(GrRecordingContext*, const SkImageInfo&, const SkIPoint&,
                                         GrMipmapped, GrImageTexGenPolicy) override;

private:
    SK_API GrAHardwareBufferImageGenerator(const SkImageInfo&, AHardwareBuffer*, SkAlphaType,
                                    bool isProtectedContent, uint32_t bufferFormat,
                                    GrSurfaceOrigin surfaceOrigin);
    SK_API GrSurfaceProxyView makeView(GrRecordingContext* context);

    SK_API void releaseTextureRef();

    SK_API static void ReleaseRefHelper_TextureReleaseProc(void* ctx);

    AHardwareBuffer* fHardwareBuffer;
    uint32_t         fBufferFormat;
    const bool       fIsProtectedContent;
    GrSurfaceOrigin  fSurfaceOrigin;

    using INHERITED = SkImageGenerator;
};
#endif  // GrAHardwareBufferImageGenerator_DEFINED
