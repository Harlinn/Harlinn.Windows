/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrGLBuffer_DEFINED
#define GrGLBuffer_DEFINED

#include <skia/gpu/gl/GrGLTypes.h>
#include "src/gpu/GrGpuBuffer.h"

class GrGLGpu;
class GrGLCaps;

class GrGLBuffer : public GrGpuBuffer {
public:
    SK_API static sk_sp<GrGLBuffer> Make(GrGLGpu*, size_t size, GrGpuBufferType intendedType,
                                  GrAccessPattern, const void* data = nullptr);

    ~GrGLBuffer() override {
        // either release or abandon should have been called by the owner of this object.
        SkASSERT(0 == fBufferID);
    }

    GrGLuint bufferID() const { return fBufferID; }

    /**
     * Returns the actual size of the underlying GL buffer object. In certain cases we may make this
     * smaller than the size reported by GrGpuBuffer.
     */
    size_t glSizeInBytes() const { return fGLSizeInBytes; }

    void setHasAttachedToTexture() { fHasAttachedToTexture = true; }
    bool hasAttachedToTexture() const { return fHasAttachedToTexture; }

protected:
    SK_API GrGLBuffer(GrGLGpu*, size_t size, GrGpuBufferType intendedType, GrAccessPattern,
               const void* data);

    SK_API void onAbandon() override;
    SK_API void onRelease() override;
    SK_API void setMemoryBacking(SkTraceMemoryDump* traceMemoryDump,
                          const SkString& dumpName) const override;

private:
    SK_API GrGLGpu* glGpu() const;
    SK_API const GrGLCaps& glCaps() const;

    SK_API void onMap() override;
    SK_API void onUnmap() override;
    SK_API bool onUpdateData(const void* src, size_t srcSizeInBytes) override;

#ifdef SK_DEBUG
    SK_API void validate() const;
#endif

    GrGpuBufferType fIntendedType;
    GrGLuint        fBufferID;
    GrGLenum        fUsage;
    size_t          fGLSizeInBytes;
    bool            fHasAttachedToTexture;

    using INHERITED = GrGpuBuffer;
};

#endif
