/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file
 */

#ifndef SkSpecialSurface_DEFINED
#define SkSpecialSurface_DEFINED

#include <skia/core/SkImageInfo.h>
#include <skia/core/SkRefCnt.h>
#include <skia/core/SkSurfaceProps.h>

#if SK_SUPPORT_GPU
#include <skia/private/GrTypesPriv.h>
#endif

class GrBackendFormat;
class GrRecordingContext;
class SkBitmap;
class SkCanvas;
class SkSpecialImage;

/**
 * SkSpecialSurface is a restricted form of SkSurface solely for internal use. It differs
 * from SkSurface in that:
 *     - it can be backed by GrTextures larger than [ fWidth, fHeight ]
 *     - it can't be used for tiling
 *     - it becomes inactive once a snapshot of it is taken (i.e., no copy-on-write)
 *     - it has no generation ID
 */
class SkSpecialSurface : public SkRefCnt {
public:
    const SkSurfaceProps& props() const { return fProps; }

    int width() const { return fSubset.width(); }
    int height() const { return fSubset.height(); }

    /**
    *  Return a canvas that will draw into this surface. This will always
    *  return the same canvas for a given surface, and is managed/owned by the
    *  surface.
    *
    *  The canvas will be invalid after 'newImageSnapshot' is called.
    */
    SK_API SkCanvas* getCanvas();

    /**
    *  Returns an image of the current state of the surface pixels up to this
    *  point. The canvas returned by 'getCanvas' becomes invalidated by this
    *  call and no more drawing to this surface is allowed.
    *
    *  Note: the caller inherits a ref from this call that must be balanced
    */
    SK_API sk_sp<SkSpecialImage> makeImageSnapshot();

#if SK_SUPPORT_GPU
    /**
     *  Allocate a new GPU-backed SkSpecialSurface. If the requested surface cannot
     *  be created, nullptr will be returned.
     */
    SK_API static sk_sp<SkSpecialSurface> MakeRenderTarget(GrRecordingContext*,
                                                    const SkImageInfo&,
                                                    const SkSurfaceProps&);
#endif

    /**
     * Use and existing SkBitmap as the backing store.
     */
    SK_API static sk_sp<SkSpecialSurface> MakeFromBitmap(const SkIRect& subset, SkBitmap& bm,
                                                  const SkSurfaceProps&);

    /**
     *  Return a new CPU-backed surface, with the memory for the pixels automatically
     *  allocated.
     *
     *  If the requested surface cannot be created, or the request is not a
     *  supported configuration, nullptr will be returned.
     */
    SK_API static sk_sp<SkSpecialSurface> MakeRaster(const SkImageInfo&,
                                              const SkSurfaceProps&);

protected:
    SK_API SkSpecialSurface(const SkIRect& subset, const SkSurfaceProps&);

    // For testing only
    friend class TestingSpecialSurfaceAccess;
    const SkIRect& subset() const { return fSubset; }

private:
    const SkSurfaceProps fProps;
    const SkIRect        fSubset;

    using INHERITED = SkRefCnt;
};

#endif
