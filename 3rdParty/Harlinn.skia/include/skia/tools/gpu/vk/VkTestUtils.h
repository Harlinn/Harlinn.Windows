/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef VkTestUtils_DEFINED
#define VkTestUtils_DEFINED

#include "skia/core/SkTypes.h"

#ifdef SK_VULKAN

#include "skia/gpu/vk/GrVkBackendContext.h"
#include "skia/gpu/vk/GrVkTypes.h"
#include "skia/tools/gpu/vk/GrVulkanDefines.h"
#include <functional>

class GrVkExtensions;
struct GrVkBackendContext;

namespace sk_gpu_test {
    SK_API bool LoadVkLibraryAndGetProcAddrFuncs(PFN_vkGetInstanceProcAddr*, PFN_vkGetDeviceProcAddr*);

    using CanPresentFn = std::function<bool(VkInstance, VkPhysicalDevice,
                                            uint32_t queueFamilyIndex)>;

    SK_API bool CreateVkBackendContext(GrVkGetProc getProc,
                                GrVkBackendContext* ctx,
                                GrVkExtensions*,
                                VkPhysicalDeviceFeatures2*,
                                VkDebugReportCallbackEXT* debugCallback,
                                uint32_t* presentQueueIndexPtr = nullptr,
                                CanPresentFn canPresent = CanPresentFn(),
                                bool isProtected = false);

    SK_API void FreeVulkanFeaturesStructs(const VkPhysicalDeviceFeatures2*);
}  // namespace sk_gpu_test

#endif
#endif

