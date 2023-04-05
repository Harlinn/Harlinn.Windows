/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrBackendSemaphore_DEFINED
#define GrBackendSemaphore_DEFINED

#include <skia/gpu/GrTypes.h>

#include <skia/gpu/gl/GrGLTypes.h>

#ifdef SK_METAL
#include <skia/gpu/mtl/GrMtlTypes.h>
#endif

#ifdef SK_VULKAN
#include <skia/gpu/vk/GrVkTypes.h>
#endif

#ifdef SK_DIRECT3D
#include <skia/private/GrD3DTypesMinimal.h>
#endif

/**
 * Wrapper class for passing into and receiving data from Ganesh about a backend semaphore object.
 */
class GrBackendSemaphore {
public:
    // For convenience we just set the backend here to OpenGL. The GrBackendSemaphore cannot be used
    // until either init* is called, which will set the appropriate GrBackend.
    GrBackendSemaphore()
            : fBackend(GrBackendApi::kOpenGL), fGLSync(nullptr), fIsInitialized(false) {}

#ifdef SK_DIRECT3D
    // We only need to specify these if Direct3D is enabled, because it requires special copy
    // characteristics.
    SK_API ~GrBackendSemaphore();
    SK_API GrBackendSemaphore(const GrBackendSemaphore&);
    SK_API GrBackendSemaphore& operator=(const GrBackendSemaphore&);
#endif

    void initGL(GrGLsync sync) {
        fBackend = GrBackendApi::kOpenGL;
        fGLSync = sync;
        fIsInitialized = true;
    }

#ifdef SK_VULKAN
    void initVulkan(VkSemaphore semaphore) {
        fBackend = GrBackendApi::kVulkan;
        fVkSemaphore = semaphore;

        fIsInitialized = true;
    }

    VkSemaphore vkSemaphore() const {
        if (!fIsInitialized || GrBackendApi::kVulkan != fBackend) {
            return VK_NULL_HANDLE;
        }
        return fVkSemaphore;
    }
#endif

#ifdef SK_METAL
    // It is the creator's responsibility to ref the MTLEvent passed in here, via __bridge_retained.
    // The other end will wrap this BackendSemaphore and take the ref, via __bridge_transfer.
    void initMetal(GrMTLHandle event, uint64_t value) {
        fBackend = GrBackendApi::kMetal;
        fMtlEvent = event;
        fMtlValue = value;

        fIsInitialized = true;
    }

    GrMTLHandle mtlSemaphore() const {
        if (!fIsInitialized || GrBackendApi::kMetal != fBackend) {
            return nullptr;
        }
        return fMtlEvent;
    }

    uint64_t mtlValue() const {
        if (!fIsInitialized || GrBackendApi::kMetal != fBackend) {
            return 0;
        }
        return fMtlValue;
    }

#endif

#ifdef SK_DIRECT3D
    void initDirect3D(const GrD3DFenceInfo& info) {
        fBackend = GrBackendApi::kDirect3D;
        this->assignD3DFenceInfo(info);
        fIsInitialized = true;
    }
#endif

    bool isInitialized() const { return fIsInitialized; }

    GrGLsync glSync() const {
        if (!fIsInitialized || GrBackendApi::kOpenGL != fBackend) {
            return nullptr;
        }
        return fGLSync;
    }


#ifdef SK_DIRECT3D
    SK_API bool getD3DFenceInfo(GrD3DFenceInfo* outInfo) const;
#endif

private:
#ifdef SK_DIRECT3D
    SK_API void assignD3DFenceInfo(const GrD3DFenceInfo& info);
#endif

    GrBackendApi fBackend;
    union {
        GrGLsync    fGLSync;
#ifdef SK_VULKAN
        VkSemaphore fVkSemaphore;
#endif
#ifdef SK_METAL
        GrMTLHandle fMtlEvent;    // Expected to be an id<MTLEvent>
#endif
#ifdef SK_DIRECT3D
        GrD3DFenceInfo* fD3DFenceInfo;
#endif
    };
#ifdef SK_METAL
    uint64_t fMtlValue;
#endif
    bool fIsInitialized;
};

#endif
