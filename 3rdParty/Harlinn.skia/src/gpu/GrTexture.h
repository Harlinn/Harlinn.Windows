
/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrTexture_DEFINED
#define GrTexture_DEFINED

#include <skia/core/SkImage.h>
#include <skia/core/SkPoint.h>
#include <skia/core/SkRefCnt.h>
#include <skia/gpu/GrBackendSurface.h>
#include <skia/private/GrTypesPriv.h>
#include "src/gpu/GrSurface.h"

class GrTexture : virtual public GrSurface {
public:
    GrTexture* asTexture() override { return this; }
    const GrTexture* asTexture() const override { return this; }

    virtual GrBackendTexture getBackendTexture() const = 0;

    /**
     * This function indicates that the texture parameters (wrap mode, filtering, ...) have been
     * changed externally to Skia.
     */
    virtual void textureParamsModified() = 0;

    /**
     * This function steals the backend texture from a uniquely owned GrTexture with no pending
     * IO, passing it out to the caller. The GrTexture is deleted in the process.
     *
     * Note that if the GrTexture is not uniquely owned (no other refs), or has pending IO, this
     * function will fail.
     */
    SK_API static bool StealBackendTexture(sk_sp<GrTexture>,
                                    GrBackendTexture*,
                                    SkImage::BackendTextureReleaseProc*);

    GrTextureType textureType() const { return fTextureType; }
    bool hasRestrictedSampling() const {
        return GrTextureTypeHasRestrictedSampling(this->textureType());
    }

    SK_API void markMipmapsDirty();
    SK_API void markMipmapsClean();
    GrMipmapped mipmapped() const {
        return GrMipmapped(fMipmapStatus != GrMipmapStatus::kNotAllocated);
    }
    bool mipmapsAreDirty() const { return fMipmapStatus != GrMipmapStatus::kValid; }
    GrMipmapStatus mipmapStatus() const { return fMipmapStatus; }
    int maxMipmapLevel() const { return fMaxMipmapLevel; }

    SK_API static void ComputeScratchKey(const GrCaps& caps,
                                  const GrBackendFormat& format,
                                  SkISize dimensions,
                                  GrRenderable,
                                  int sampleCnt,
                                  GrMipmapped,
                                  GrProtected,
                                  GrScratchKey* key);

protected:
    SK_API GrTexture(GrGpu*, const SkISize&, GrProtected, GrTextureType, GrMipmapStatus);

    virtual bool onStealBackendTexture(GrBackendTexture*, SkImage::BackendTextureReleaseProc*) = 0;

    SK_API void computeScratchKey(GrScratchKey*) const override;

private:
    SK_API size_t onGpuMemorySize() const override;

    GrTextureType                 fTextureType;
    GrMipmapStatus                fMipmapStatus;
    int                           fMaxMipmapLevel;
    friend class GrTextureResource;

    using INHERITED = GrSurface;
};

#endif
