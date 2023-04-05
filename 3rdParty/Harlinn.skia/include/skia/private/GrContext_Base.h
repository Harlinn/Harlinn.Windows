#pragma once
/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrContext_Base_DEFINED
#define GrContext_Base_DEFINED

#include <skia/core/SkRefCnt.h>
#include <skia/gpu/GrBackendSurface.h>
#include <skia/gpu/GrContextOptions.h>
#include <skia/gpu/GrTypes.h>

class GrBaseContextPriv;
class GrCaps;
class GrContextThreadSafeProxy;
class GrDirectContext;
class GrImageContext;
class GrRecordingContext;

class GrContext_Base : public SkRefCnt {
public:
    SK_API ~GrContext_Base() override;

    /*
     * Safely downcast to a GrDirectContext.
     */
    virtual GrDirectContext* asDirectContext() { return nullptr; }

    /*
     * The 3D API backing this context
     */
    SK_API GrBackendApi backend() const;

    /*
     * Retrieve the default GrBackendFormat for a given SkColorType and renderability.
     * It is guaranteed that this backend format will be the one used by the GrContext
     * SkColorType and SkSurfaceCharacterization-based createBackendTexture methods.
     *
     * The caller should check that the returned format is valid.
     */
    SK_API GrBackendFormat defaultBackendFormat(SkColorType, GrRenderable) const;

    SK_API GrBackendFormat compressedBackendFormat(SkImage::CompressionType) const;

    // TODO: When the public version is gone, rename to refThreadSafeProxy and add raw ptr ver.
    SK_API sk_sp<GrContextThreadSafeProxy> threadSafeProxy();

    // Provides access to functions that aren't part of the public API.
    SK_API GrBaseContextPriv priv();
    SK_API const GrBaseContextPriv priv() const;  // NOLINT(readability-const-return-type)

protected:
    friend class GrBaseContextPriv; // for hidden functions

    SK_API GrContext_Base(sk_sp<GrContextThreadSafeProxy>);

    SK_API virtual bool init();

    /**
     * An identifier for this context. The id is used by all compatible contexts. For example,
     * if SkImages are created on one thread using an image creation context, then fed into a
     * DDL Recorder on second thread (which has a recording context) and finally replayed on
     * a third thread with a direct context, then all three contexts will report the same id.
     * It is an error for an image to be used with contexts that report different ids.
     */
    SK_API uint32_t contextID() const;

    bool matches(GrContext_Base* candidate) const {
        return candidate && candidate->contextID() == this->contextID();
    }

    /*
     * The options in effect for this context
     */
    SK_API const GrContextOptions& options() const;

    SK_API const GrCaps* caps() const;
    SK_API sk_sp<const GrCaps> refCaps() const;

    virtual GrImageContext* asImageContext() { return nullptr; }
    virtual GrRecordingContext* asRecordingContext() { return nullptr; }

    sk_sp<GrContextThreadSafeProxy>         fThreadSafeProxy;

private:
    using INHERITED = SkRefCnt;
};

#endif
