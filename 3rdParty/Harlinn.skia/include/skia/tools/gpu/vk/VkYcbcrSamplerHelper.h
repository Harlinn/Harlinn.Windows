/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef VkYcbcrSamplerHelper_DEFINED
#define VkYcbcrSamplerHelper_DEFINED

#include "skia/core/SkTypes.h"

#ifdef SK_VULKAN

#include "skia/gpu/GrBackendSurface.h"

class GrContext;
class GrVkGpu;

// This helper will create and hold data for a Vulkan YCbCr backend texture. This format is
// particularly interesting because its sampler is immutable.
class VkYcbcrSamplerHelper {
public:
    SK_API VkYcbcrSamplerHelper(GrDirectContext*);
    SK_API ~VkYcbcrSamplerHelper();

    SK_API bool isYCbCrSupported();

    SK_API bool createBackendTexture(uint32_t width, uint32_t height);

    const GrBackendTexture& backendTexture() const { return fTexture; }

    SK_API static int GetExpectedY(int x, int y, int width, int height);
    SK_API static std::pair<int, int> GetExpectedUV(int x, int y, int width, int height);

private:
    SK_API GrVkGpu* vkGpu();

    GrDirectContext* fDContext;

    VkImage fImage = VK_NULL_HANDLE;
    VkDeviceMemory fImageMemory = VK_NULL_HANDLE;
    GrBackendTexture fTexture;
};

#endif // SK_VULKAN

#endif // VkYcbcrSamplerHelper_DEFINED
