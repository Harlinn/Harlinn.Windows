/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef GrGLTexture_DEFINED
#define GrGLTexture_DEFINED

#include <skia/private/GrGLTypesPriv.h>
#include "src/gpu/GrGpu.h"
#include "src/gpu/GrTexture.h"
#include "src/gpu/gl/GrGLUtil.h"

class GrGLGpu;

class GrGLTexture : public GrTexture {
public:
    struct Desc {
        SkISize fSize                       = {-1, -1};
        GrGLenum fTarget                    = 0;
        GrGLuint fID                        = 0;
        GrGLFormat fFormat                  = GrGLFormat::kUnknown;
        GrBackendObjectOwnership fOwnership = GrBackendObjectOwnership::kOwned;
    };

    SK_API static GrTextureType TextureTypeFromTarget(GrGLenum textureTarget);

    SK_API GrGLTexture(GrGLGpu*, SkBudgeted, const Desc&, GrMipmapStatus);

    ~GrGLTexture() override {}

    SK_API GrBackendTexture getBackendTexture() const override;

    SK_API GrBackendFormat backendFormat() const override;

    // TODO: Remove once clients are no longer calling this.
    void textureParamsModified() override { fParameters->invalidate(); }

    GrGLTextureParameters* parameters() { return fParameters.get(); }

    GrGLuint textureID() const { return fID; }

    SK_API GrGLenum target() const;

    GrGLFormat format() const { return fFormat; }

    bool hasBaseLevelBeenBoundToFBO() const { return fBaseLevelHasBeenBoundToFBO; }
    void baseLevelWasBoundToFBO() { fBaseLevelHasBeenBoundToFBO = true; }

    SK_API static sk_sp<GrGLTexture> MakeWrapped(GrGLGpu*,
                                          GrMipmapStatus,
                                          const Desc&,
                                          sk_sp<GrGLTextureParameters>,
                                          GrWrapCacheable, GrIOType);

    SK_API void dumpMemoryStatistics(SkTraceMemoryDump* traceMemoryDump) const override;

protected:
    // Constructor for subclasses.
    SK_API GrGLTexture(GrGLGpu*, const Desc&, sk_sp<GrGLTextureParameters>, GrMipmapStatus);

    // Constructor for instances wrapping backend objects.
    SK_API GrGLTexture(GrGLGpu*,
                const Desc&,
                GrMipmapStatus,
                sk_sp<GrGLTextureParameters>,
                GrWrapCacheable,
                GrIOType);

    SK_API void init(const Desc&);

    SK_API void onAbandon() override;
    SK_API void onRelease() override;

    SK_API bool onStealBackendTexture(GrBackendTexture*, SkImage::BackendTextureReleaseProc*) override;

private:
    sk_sp<GrGLTextureParameters> fParameters;
    GrGLuint fID;
    GrGLFormat fFormat;
    GrBackendObjectOwnership fTextureIDOwnership;
    bool fBaseLevelHasBeenBoundToFBO = false;

    using INHERITED = GrTexture;
};

#endif
