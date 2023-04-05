/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrVkGpu_DEFINED
#define GrVkGpu_DEFINED

#include <skia/gpu/vk/GrVkBackendContext.h>
#include <skia/gpu/vk/GrVkTypes.h>
#include "src/gpu/GrGpu.h"
#include "src/gpu/GrStagingBufferManager.h"
#include "src/gpu/vk/GrVkCaps.h"
#include "src/gpu/vk/GrVkMSAALoadManager.h"
#include "src/gpu/vk/GrVkMemory.h"
#include "src/gpu/vk/GrVkResourceProvider.h"
#include "src/gpu/vk/GrVkSemaphore.h"
#include "src/gpu/vk/GrVkUtil.h"

class GrDirectContext;
class GrPipeline;

class GrVkBuffer;
class GrVkCommandPool;
class GrVkFramebuffer;
class GrVkMemoryAllocator;
class GrVkPipeline;
class GrVkPipelineState;
class GrVkPrimaryCommandBuffer;
class GrVkOpsRenderPass;
class GrVkRenderPass;
class GrVkSecondaryCommandBuffer;
class GrVkTexture;
struct GrVkInterface;

class GrVkGpu : public GrGpu {
public:
    SK_API static sk_sp<GrGpu> Make(const GrVkBackendContext&, const GrContextOptions&, GrDirectContext*);

    SK_API ~GrVkGpu() override;

    SK_API void disconnect(DisconnectType) override;
    bool disconnected() const { return fDisconnected; }

    void releaseUnlockedBackendObjects() override {
        fResourceProvider.releaseUnlockedBackendObjects();
    }

    SK_API GrThreadSafePipelineBuilder* pipelineBuilder() override;
    SK_API sk_sp<GrThreadSafePipelineBuilder> refPipelineBuilder() override;

    const GrVkInterface* vkInterface() const { return fInterface.get(); }
    const GrVkCaps& vkCaps() const { return *fVkCaps; }

    GrStagingBufferManager* stagingBufferManager() override { return &fStagingBufferManager; }
    SK_API void takeOwnershipOfBuffer(sk_sp<GrGpuBuffer>) override;

    bool isDeviceLost() const override { return fDeviceIsLost; }

    GrVkMemoryAllocator* memoryAllocator() const { return fMemoryAllocator.get(); }

    VkPhysicalDevice physicalDevice() const { return fPhysicalDevice; }
    VkDevice device() const { return fDevice; }
    VkQueue  queue() const { return fQueue; }
    uint32_t  queueIndex() const { return fQueueIndex; }
    GrVkCommandPool* cmdPool() const { return fMainCmdPool; }
    const VkPhysicalDeviceProperties& physicalDeviceProperties() const {
        return fPhysDevProps;
    }
    const VkPhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties() const {
        return fPhysDevMemProps;
    }
    bool protectedContext() const { return fProtectedContext == GrProtected::kYes; }

    GrVkResourceProvider& resourceProvider() { return fResourceProvider; }

    GrVkPrimaryCommandBuffer* currentCommandBuffer() const { return fMainCmdBuffer; }

    SK_API void xferBarrier(GrRenderTarget*, GrXferBarrierType) override;

    SK_API bool setBackendTextureState(const GrBackendTexture&,
                                const GrBackendSurfaceMutableState&,
                                GrBackendSurfaceMutableState* previousState,
                                sk_sp<GrRefCntedCallback> finishedCallback) override;

    SK_API bool setBackendRenderTargetState(const GrBackendRenderTarget&,
                                     const GrBackendSurfaceMutableState&,
                                     GrBackendSurfaceMutableState* previousState,
                                     sk_sp<GrRefCntedCallback> finishedCallback) override;

    SK_API void deleteBackendTexture(const GrBackendTexture&) override;

    SK_API bool compile(const GrProgramDesc&, const GrProgramInfo&) override;

#if GR_TEST_UTILS
    SK_API bool isTestingOnlyBackendTexture(const GrBackendTexture&) const override;

    SK_API GrBackendRenderTarget createTestingOnlyBackendRenderTarget(SkISize dimensions,
                                                               GrColorType,
                                                               int sampleCnt,
                                                               GrProtected) override;
    SK_API void deleteTestingOnlyBackendRenderTarget(const GrBackendRenderTarget&) override;

    void resetShaderCacheForTesting() const override {
        fResourceProvider.resetShaderCacheForTesting();
    }
#endif

    SK_API sk_sp<GrAttachment> makeStencilAttachment(const GrBackendFormat& /*colorFormat*/,
                                              SkISize dimensions, int numStencilSamples) override;

    GrBackendFormat getPreferredStencilFormat(const GrBackendFormat&) override {
        return GrBackendFormat::MakeVk(this->vkCaps().preferredStencilFormat());
    }

    SK_API sk_sp<GrAttachment> makeMSAAAttachment(SkISize dimensions,
                                           const GrBackendFormat& format,
                                           int numSamples,
                                           GrProtected isProtected,
                                           GrMemoryless isMemoryless) override;

    SK_API void addBufferMemoryBarrier(const GrManagedResource*,
                                VkPipelineStageFlags srcStageMask,
                                VkPipelineStageFlags dstStageMask,
                                bool byRegion,
                                VkBufferMemoryBarrier* barrier) const;
    SK_API void addBufferMemoryBarrier(VkPipelineStageFlags srcStageMask,
                                VkPipelineStageFlags dstStageMask,
                                bool byRegion,
                                VkBufferMemoryBarrier* barrier) const;
    SK_API void addImageMemoryBarrier(const GrManagedResource*,
                               VkPipelineStageFlags srcStageMask,
                               VkPipelineStageFlags dstStageMask,
                               bool byRegion,
                               VkImageMemoryBarrier* barrier) const;

    SK_API bool loadMSAAFromResolve(GrVkCommandBuffer* commandBuffer,
                             const GrVkRenderPass& renderPass,
                             GrAttachment* dst,
                             GrVkImage* src,
                             const SkIRect& srcRect);

    SK_API bool onRegenerateMipMapLevels(GrTexture* tex) override;

    SK_API void onResolveRenderTarget(GrRenderTarget* target, const SkIRect& resolveRect) override;

    SK_API void submitSecondaryCommandBuffer(std::unique_ptr<GrVkSecondaryCommandBuffer>);

    SK_API void submit(GrOpsRenderPass*) override;

    SK_API GrFence SK_WARN_UNUSED_RESULT insertFence() override;
    SK_API bool waitFence(GrFence) override;
    SK_API void deleteFence(GrFence) const override;

    SK_API std::unique_ptr<GrSemaphore> SK_WARN_UNUSED_RESULT makeSemaphore(bool isOwned) override;
    SK_API std::unique_ptr<GrSemaphore> wrapBackendSemaphore(const GrBackendSemaphore&,
                                                      GrSemaphoreWrapType,
                                                      GrWrapOwnership) override;
    SK_API void insertSemaphore(GrSemaphore* semaphore) override;
    SK_API void waitSemaphore(GrSemaphore* semaphore) override;

    // These match the definitions in SkDrawable, from whence they came
    typedef void* SubmitContext;
    typedef void (*SubmitProc)(SubmitContext submitContext);

    // Adds an SkDrawable::GpuDrawHandler that we will delete the next time we submit the primary
    // command buffer to the gpu.
    SK_API void addDrawable(std::unique_ptr<SkDrawable::GpuDrawHandler> drawable);

    void checkFinishProcs() override { fResourceProvider.checkCommandBuffers(); }
    SK_API void finishOutstandingGpuWork() override;

    SK_API std::unique_ptr<GrSemaphore> prepareTextureForCrossContextUsage(GrTexture*) override;

    SK_API void copyBuffer(sk_sp<GrGpuBuffer> srcBuffer, sk_sp<GrGpuBuffer> dstBuffer,
                    VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size);
    SK_API bool updateBuffer(sk_sp<GrVkBuffer> buffer, const void* src, VkDeviceSize offset,
                      VkDeviceSize size);

    enum PersistentCacheKeyType : uint32_t {
        kShader_PersistentCacheKeyType = 0,
        kPipelineCache_PersistentCacheKeyType = 1,
    };

    SK_API void storeVkPipelineCacheData() override;

    SK_API bool beginRenderPass(const GrVkRenderPass*,
                         sk_sp<const GrVkFramebuffer>,
                         const VkClearValue* colorClear,
                         const GrSurface*,
                         const SkIRect& renderPassBounds,
                         bool forSecondaryCB);
    SK_API void endRenderPass(GrRenderTarget* target, GrSurfaceOrigin origin, const SkIRect& bounds);

    // Returns true if VkResult indicates success and also checks for device lost or OOM. Every
    // Vulkan call (and GrVkMemoryAllocator call that returns VkResult) made on behalf of the
    // GrVkGpu should be processed by this function so that we respond to OOMs and lost devices.
    SK_API bool checkVkResult(VkResult);

private:
    enum SyncQueue {
        kForce_SyncQueue,
        kSkip_SyncQueue
    };

    SK_API GrVkGpu(GrDirectContext*, const GrVkBackendContext&, const sk_sp<GrVkCaps> caps,
            sk_sp<const GrVkInterface>, uint32_t instanceVersion, uint32_t physicalDeviceVersion,
            sk_sp<GrVkMemoryAllocator>);

    SK_API void destroyResources();

    SK_API GrBackendTexture onCreateBackendTexture(SkISize dimensions,
                                            const GrBackendFormat&,
                                            GrRenderable,
                                            GrMipmapped,
                                            GrProtected) override;
    SK_API GrBackendTexture onCreateCompressedBackendTexture(SkISize dimensions,
                                                      const GrBackendFormat&,
                                                      GrMipmapped,
                                                      GrProtected) override;

    SK_API bool onClearBackendTexture(const GrBackendTexture&,
                               sk_sp<GrRefCntedCallback> finishedCallback,
                               std::array<float, 4> color) override;

    SK_API bool onUpdateCompressedBackendTexture(const GrBackendTexture&,
                                          sk_sp<GrRefCntedCallback> finishedCallback,
                                          const void* data,
                                          size_t length) override;

    SK_API bool setBackendSurfaceState(GrVkImageInfo info,
                                sk_sp<GrBackendSurfaceMutableStateImpl> currentState,
                                SkISize dimensions,
                                const GrVkSharedImageInfo& newInfo,
                                GrBackendSurfaceMutableState* previousState,
                                sk_sp<GrRefCntedCallback> finishedCallback);

    SK_API sk_sp<GrTexture> onCreateTexture(SkISize,
                                     const GrBackendFormat&,
                                     GrRenderable,
                                     int renderTargetSampleCnt,
                                     SkBudgeted,
                                     GrProtected,
                                     int mipLevelCount,
                                     uint32_t levelClearMask) override;
    SK_API sk_sp<GrTexture> onCreateCompressedTexture(SkISize dimensions,
                                               const GrBackendFormat&,
                                               SkBudgeted,
                                               GrMipmapped,
                                               GrProtected,
                                               const void* data, size_t dataSize) override;

    SK_API sk_sp<GrTexture> onWrapBackendTexture(const GrBackendTexture&,
                                          GrWrapOwnership,
                                          GrWrapCacheable,
                                          GrIOType) override;
    SK_API sk_sp<GrTexture> onWrapCompressedBackendTexture(const GrBackendTexture&,
                                                    GrWrapOwnership,
                                                    GrWrapCacheable) override;
    SK_API sk_sp<GrTexture> onWrapRenderableBackendTexture(const GrBackendTexture&,
                                                    int sampleCnt,
                                                    GrWrapOwnership,
                                                    GrWrapCacheable) override;
    SK_API sk_sp<GrRenderTarget> onWrapBackendRenderTarget(const GrBackendRenderTarget&) override;

    SK_API sk_sp<GrRenderTarget> onWrapVulkanSecondaryCBAsRenderTarget(const SkImageInfo&,
                                                                const GrVkDrawableInfo&) override;

    SK_API sk_sp<GrGpuBuffer> onCreateBuffer(size_t size, GrGpuBufferType type, GrAccessPattern,
                                      const void* data) override;

    SK_API bool onReadPixels(GrSurface*,
                      SkIRect,
                      GrColorType surfaceColorType,
                      GrColorType dstColorType,
                      void* buffer,
                      size_t rowBytes) override;

    SK_API bool onWritePixels(GrSurface*,
                       SkIRect,
                       GrColorType surfaceColorType,
                       GrColorType srcColorType,
                       const GrMipLevel[],
                       int mipLevelCount,
                       bool prepForTexSampling) override;

    SK_API bool onTransferPixelsTo(GrTexture*,
                            SkIRect,
                            GrColorType textureColorType,
                            GrColorType bufferColorType,
                            sk_sp<GrGpuBuffer>,
                            size_t offset,
                            size_t rowBytes) override;

    SK_API bool onTransferPixelsFrom(GrSurface*,
                              SkIRect,
                              GrColorType surfaceColorType,
                              GrColorType bufferColorType,
                              sk_sp<GrGpuBuffer>,
                              size_t offset) override;

    SK_API bool onCopySurface(GrSurface* dst, GrSurface* src, const SkIRect& srcRect,
                       const SkIPoint& dstPoint) override;

    SK_API void addFinishedProc(GrGpuFinishedProc finishedProc,
                         GrGpuFinishedContext finishedContext) override;

    SK_API void addFinishedCallback(sk_sp<GrRefCntedCallback> finishedCallback);

    SK_API GrOpsRenderPass* onGetOpsRenderPass(GrRenderTarget*,
                                        bool useMSAASurface,
                                        GrAttachment* stencil,
                                        GrSurfaceOrigin,
                                        const SkIRect&,
                                        const GrOpsRenderPass::LoadAndStoreInfo&,
                                        const GrOpsRenderPass::StencilLoadAndStoreInfo&,
                                        const SkTArray<GrSurfaceProxy*, true>& sampledProxies,
                                        GrXferBarrierFlags renderPassXferBarriers) override;

    SK_API void prepareSurfacesForBackendAccessAndStateUpdates(
            SkSpan<GrSurfaceProxy*> proxies,
            SkSurface::BackendSurfaceAccess access,
            const GrBackendSurfaceMutableState* newState) override;

    SK_API bool onSubmitToGpu(bool syncCpu) override;

    SK_API void onReportSubmitHistograms() override;

    // Ends and submits the current command buffer to the queue and then creates a new command
    // buffer and begins it. If sync is set to kForce_SyncQueue, the function will wait for all
    // work in the queue to finish before returning. If this GrVkGpu object has any semaphores in
    // fSemaphoreToSignal, we will add those signal semaphores to the submission of this command
    // buffer. If this GrVkGpu object has any semaphores in fSemaphoresToWaitOn, we will add those
    // wait semaphores to the submission of this command buffer.
    SK_API bool submitCommandBuffer(SyncQueue sync);

    SK_API void copySurfaceAsCopyImage(GrSurface* dst,
                                GrSurface* src,
                                GrVkImage* dstImage,
                                GrVkImage* srcImage,
                                const SkIRect& srcRect,
                                const SkIPoint& dstPoint);

    SK_API void copySurfaceAsBlit(GrSurface* dst,
                           GrSurface* src,
                           GrVkImage* dstImage,
                           GrVkImage* srcImage,
                           const SkIRect& srcRect,
                           const SkIPoint& dstPoint);

    SK_API void copySurfaceAsResolve(GrSurface* dst, GrSurface* src, const SkIRect& srcRect,
                              const SkIPoint& dstPoint);

    // helpers for onCreateTexture and writeTexturePixels
    SK_API bool uploadTexDataLinear(GrVkImage* tex,
                             SkIRect rect,
                             GrColorType colorType,
                             const void* data,
                             size_t rowBytes);
    SK_API bool uploadTexDataOptimal(GrVkImage* tex,
                              SkIRect rect,
                              GrColorType colorType,
                              const GrMipLevel texels[],
                              int mipLevelCount);
    SK_API bool uploadTexDataCompressed(GrVkImage* tex, SkImage::CompressionType compression,
                                 VkFormat vkFormat, SkISize dimensions, GrMipmapped mipMapped,
                                 const void* data, size_t dataSize);
    SK_API void resolveImage(GrSurface* dst, GrVkRenderTarget* src, const SkIRect& srcRect,
                      const SkIPoint& dstPoint);

    SK_API bool createVkImageForBackendSurface(VkFormat,
                                        SkISize dimensions,
                                        int sampleCnt,
                                        GrTexturable,
                                        GrRenderable,
                                        GrMipmapped,
                                        GrVkImageInfo*,
                                        GrProtected);

    sk_sp<const GrVkInterface>                            fInterface;
    sk_sp<GrVkMemoryAllocator>                            fMemoryAllocator;
    sk_sp<GrVkCaps>                                       fVkCaps;
    bool                                                  fDeviceIsLost = false;

    VkPhysicalDevice                                      fPhysicalDevice;
    VkDevice                                              fDevice;
    VkQueue                                               fQueue;    // Must be Graphics queue
    uint32_t                                              fQueueIndex;

    // Created by GrVkGpu
    GrVkResourceProvider                                  fResourceProvider;
    GrStagingBufferManager                                fStagingBufferManager;

    GrVkMSAALoadManager                                   fMSAALoadManager;

    GrVkCommandPool*                                      fMainCmdPool;
    // just a raw pointer; object's lifespan is managed by fCmdPool
    GrVkPrimaryCommandBuffer*                             fMainCmdBuffer;

    SkSTArray<1, GrVkSemaphore::Resource*>                fSemaphoresToWaitOn;
    SkSTArray<1, GrVkSemaphore::Resource*>                fSemaphoresToSignal;

    SkTArray<std::unique_ptr<SkDrawable::GpuDrawHandler>> fDrawables;

    VkPhysicalDeviceProperties                            fPhysDevProps;
    VkPhysicalDeviceMemoryProperties                      fPhysDevMemProps;

    // We need a bool to track whether or not we've already disconnected all the gpu resources from
    // vulkan context.
    bool                                                  fDisconnected;

    GrProtected                                           fProtectedContext;

    std::unique_ptr<GrVkOpsRenderPass>                    fCachedOpsRenderPass;

    using INHERITED = GrGpu;
};

#endif
