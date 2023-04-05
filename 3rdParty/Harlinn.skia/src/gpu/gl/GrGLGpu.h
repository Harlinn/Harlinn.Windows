/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrGLGpu_DEFINED
#define GrGLGpu_DEFINED

#include <skia/core/SkTypes.h>
#include <skia/private/SkTArray.h>
#include "src/core/SkLRUCache.h"
#include "src/gpu/GrFinishCallbacks.h"
#include "src/gpu/GrGpu.h"
#include "src/gpu/GrNativeRect.h"
#include "src/gpu/GrProgramDesc.h"
#include "src/gpu/GrThreadSafePipelineBuilder.h"
#include "src/gpu/GrWindowRectsState.h"
#include "src/gpu/GrXferProcessor.h"
#include "src/gpu/gl/GrGLAttachment.h"
#include "src/gpu/gl/GrGLContext.h"
#include "src/gpu/gl/GrGLProgram.h"
#include "src/gpu/gl/GrGLRenderTarget.h"
#include "src/gpu/gl/GrGLTexture.h"
#include "src/gpu/gl/GrGLVertexArray.h"

class GrGLBuffer;
class GrGLOpsRenderPass;
class GrPipeline;
class GrSwizzle;

class GrGLGpu final : public GrGpu {
public:
    SK_API static sk_sp<GrGpu> Make(sk_sp<const GrGLInterface>, const GrContextOptions&, GrDirectContext*);
    SK_API ~GrGLGpu() override;

    SK_API void disconnect(DisconnectType) override;

    SK_API GrThreadSafePipelineBuilder* pipelineBuilder() override;
    SK_API sk_sp<GrThreadSafePipelineBuilder> refPipelineBuilder() override;

    const GrGLContext& glContext() const { return *fGLContext; }

    const GrGLInterface* glInterface() const { return fGLContext->glInterface(); }
    const GrGLContextInfo& ctxInfo() const { return *fGLContext; }
    GrGLStandard glStandard() const { return fGLContext->standard(); }
    GrGLVersion glVersion() const { return fGLContext->version(); }
    GrGLSLGeneration glslGeneration() const { return fGLContext->glslGeneration(); }
    const GrGLCaps& glCaps() const { return *fGLContext->caps(); }

    // Used by GrGLProgram to configure OpenGL state.
    SK_API void bindTexture(int unitIdx, GrSamplerState samplerState, const GrSwizzle&, GrGLTexture*);

    // These functions should be used to bind GL objects. They track the GL state and skip redundant
    // bindings. Making the equivalent glBind calls directly will confuse the state tracking.
    void bindVertexArray(GrGLuint id) {
        fHWVertexArrayState.setVertexArrayID(this, id);
    }

    // These callbacks update state tracking when GL objects are deleted. They are called from
    // GrGLResource onRelease functions.
    void notifyVertexArrayDelete(GrGLuint id) {
        fHWVertexArrayState.notifyVertexArrayDelete(id);
    }

    // Binds a buffer to the GL target corresponding to 'type', updates internal state tracking, and
    // returns the GL target the buffer was bound to.
    // When 'type' is kIndex_GrBufferType, this function will also implicitly bind the default VAO.
    // If the caller wishes to bind an index buffer to a specific VAO, it can call glBind directly.
    SK_API GrGLenum bindBuffer(GrGpuBufferType type, const GrBuffer*);

    // Flushes state from GrProgramInfo to GL. Returns false if the state couldn't be set.
    SK_API bool flushGLState(GrRenderTarget*, bool useMultisampleFBO, const GrProgramInfo&);
    SK_API void flushScissorRect(const SkIRect& scissor, int rtHeight, GrSurfaceOrigin);

    // The flushRenderTarget methods will all set the initial viewport to the full extent of the
    // backing render target.
    SK_API void flushViewport(const SkIRect& viewport, int rtHeight, GrSurfaceOrigin);

    // Returns the last program bound by flushGLState(), or nullptr if a different program has since
    // been put into use via some other method (e.g., resetContext, copySurfaceAsDraw).
    // The returned GrGLProgram can be used for binding textures and vertex attributes.
    GrGLProgram* currentProgram() {
        this->handleDirtyContext();
        return fHWProgram.get();
    }

    // Binds the vertex array that should be used for internal draws, enables 'numAttribs' vertex
    // arrays, and flushes the desired primitive restart settings. If an index buffer is provided,
    // it will be bound to the vertex array. Otherwise the index buffer binding will be left
    // unchanged.
    //
    // NOTE: This binds the default VAO (ID=zero) unless we are on a core profile, in which case we
    // use a placeholder array instead.
    GrGLAttribArrayState* bindInternalVertexArray(const GrBuffer* indexBuffer, int numAttribs,
                                                  GrPrimitiveRestart primitiveRestart) {
        auto* attribState = fHWVertexArrayState.bindInternalVertexArray(this, indexBuffer);
        attribState->enableVertexArrays(this, numAttribs, primitiveRestart);
        return attribState;
    }

    // Applies any necessary workarounds and returns the GL primitive type to use in draw calls.
    SK_API GrGLenum prepareToDraw(GrPrimitiveType primitiveType);

    using ResolveDirection = GrGLRenderTarget::ResolveDirection;

    // Resolves the render target's single sample FBO into the MSAA, or vice versa.
    // If glCaps.framebufferResolvesMustBeFullSize() is true, resolveRect must be equal the render
    // target's bounds rect.
    // If blitting single to MSAA, glCaps.canResolveSingleToMSAA() must be true.
    SK_API void resolveRenderFBOs(GrGLRenderTarget*, const SkIRect& resolveRect, ResolveDirection,
                           bool invalidateReadBufferAfterBlit = false);

    // For loading a dynamic MSAA framebuffer when glCaps.canResolveSingleToMSAA() is false.
    // NOTE: If glCaps.framebufferResolvesMustBeFullSize() is also true, the drawBounds should be
    // equal to the proxy bounds. This is because the render pass will have to do a full size
    // resolve back into the single sample FBO when rendering is complete.
    void drawSingleIntoMSAAFBO(GrGLRenderTarget* rt, const SkIRect& drawBounds) {
        this->copySurfaceAsDraw(rt, true/*drawToMultisampleFBO*/, rt, drawBounds,
                                drawBounds.topLeft());
    }

    // The GrGLOpsRenderPass does not buffer up draws before submitting them to the gpu.
    // Thus this is the implementation of the clear call for the corresponding passthrough function
    // on GrGLOpsRenderPass.
    SK_API void clear(const GrScissorState&, std::array<float, 4> color, GrRenderTarget*,
               bool useMultisampleFBO, GrSurfaceOrigin);

    // The GrGLOpsRenderPass does not buffer up draws before submitting them to the gpu.
    // Thus this is the implementation of the clearStencil call for the corresponding passthrough
    // function on GrGLOpsrenderPass.
    SK_API void clearStencilClip(const GrScissorState&, bool insideStencilMask,
                          GrRenderTarget*, bool useMultisampleFBO, GrSurfaceOrigin);

    SK_API void beginCommandBuffer(GrGLRenderTarget*, bool useMultisampleFBO,
                            const SkIRect& bounds, GrSurfaceOrigin,
                            const GrOpsRenderPass::LoadAndStoreInfo& colorLoadStore,
                            const GrOpsRenderPass::StencilLoadAndStoreInfo& stencilLoadStore);

    SK_API void endCommandBuffer(GrGLRenderTarget*, bool useMultisampleFBO,
                          const GrOpsRenderPass::LoadAndStoreInfo& colorLoadStore,
                          const GrOpsRenderPass::StencilLoadAndStoreInfo& stencilLoadStore);

    void invalidateBoundRenderTarget() {
        fHWBoundRenderTargetUniqueID.makeInvalid();
    }

    sk_sp<GrAttachment> makeStencilAttachment(const GrBackendFormat& colorFormat,
                                              SkISize dimensions, int numStencilSamples) override;

    SK_API sk_sp<GrAttachment> makeMSAAAttachment(SkISize dimensions,
                                           const GrBackendFormat& format,
                                           int numSamples,
                                           GrProtected isProtected,
                                           GrMemoryless) override;

    SK_API void deleteBackendTexture(const GrBackendTexture&) override;

    SK_API bool compile(const GrProgramDesc&, const GrProgramInfo&) override;

    bool precompileShader(const SkData& key, const SkData& data) override {
        return fProgramCache->precompileShader(this->getContext(), key, data);
    }

#if GR_TEST_UTILS
    SK_API bool isTestingOnlyBackendTexture(const GrBackendTexture&) const override;

    SK_API GrBackendRenderTarget createTestingOnlyBackendRenderTarget(SkISize dimensions,
                                                               GrColorType,
                                                               int sampleCnt,
                                                               GrProtected) override;
    SK_API void deleteTestingOnlyBackendRenderTarget(const GrBackendRenderTarget&) override;

    const GrGLContext* glContextForTesting() const override { return &this->glContext(); }

    void resetShaderCacheForTesting() const override { fProgramCache->reset(); }
#endif

    SK_API void submit(GrOpsRenderPass* renderPass) override;

    SK_API GrFence SK_WARN_UNUSED_RESULT insertFence() override;
    SK_API bool waitFence(GrFence) override;
    SK_API void deleteFence(GrFence) const override;

    SK_API std::unique_ptr<GrSemaphore> SK_WARN_UNUSED_RESULT makeSemaphore(bool isOwned) override;
    SK_API std::unique_ptr<GrSemaphore> wrapBackendSemaphore(const GrBackendSemaphore&,
                                                      GrSemaphoreWrapType,
                                                      GrWrapOwnership) override;
    SK_API void insertSemaphore(GrSemaphore* semaphore) override;
    SK_API void waitSemaphore(GrSemaphore* semaphore) override;

    SK_API void checkFinishProcs() override;
    SK_API void finishOutstandingGpuWork() override;

    // Calls glGetError() until no errors are reported. Also looks for OOMs.
    SK_API void clearErrorsAndCheckForOOM();
    // Calls glGetError() once and returns the result. Also looks for an OOM.
    SK_API GrGLenum getErrorAndCheckForOOM();

    SK_API std::unique_ptr<GrSemaphore> prepareTextureForCrossContextUsage(GrTexture*) override;

    SK_API void deleteSync(GrGLsync) const;

    SK_API void bindFramebuffer(GrGLenum fboTarget, GrGLuint fboid);
    SK_API void deleteFramebuffer(GrGLuint fboid);

    SK_API void insertManualFramebufferBarrier() override;

    SK_API void flushProgram(sk_sp<GrGLProgram>);

    // Version for programs that aren't GrGLProgram.
    SK_API void flushProgram(GrGLuint);

private:
    SK_API GrGLGpu(std::unique_ptr<GrGLContext>, GrDirectContext*);

    // GrGpu overrides
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

    SK_API void onResetContext(uint32_t resetBits) override;

    SK_API void onResetTextureBindings() override;

    SK_API void xferBarrier(GrRenderTarget*, GrXferBarrierType) override;

    SK_API sk_sp<GrTexture> onCreateTexture(SkISize dimensions,
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

    SK_API sk_sp<GrGpuBuffer> onCreateBuffer(size_t size, GrGpuBufferType intendedType, GrAccessPattern,
                                      const void* data) override;

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

    // Given a GL format return the index into the stencil format array on GrGLCaps to a
    // compatible stencil format, or negative if there is no compatible stencil format.
    SK_API int getCompatibleStencilIndex(GrGLFormat format);

    GrBackendFormat getPreferredStencilFormat(const GrBackendFormat& format) override {
        int idx = this->getCompatibleStencilIndex(format.asGLFormat());
        if (idx < 0) {
            return {};
        }
        return GrBackendFormat::MakeGL(GrGLFormatToEnum(this->glCaps().stencilFormats()[idx]),
                                       GR_GL_TEXTURE_NONE);
    }

    SK_API void onFBOChanged();

    // Returns whether the texture is successfully created. On success, a non-zero texture ID is
    // returned. On failure, zero is returned.
    // The texture is populated with |texels|, if it is non-null.
    // The texture parameters are cached in |initialTexParams|.
    SK_API GrGLuint createTexture(SkISize dimensions,
                           GrGLFormat,
                           GrGLenum target,
                           GrRenderable,
                           GrGLTextureParameters::SamplerOverriddenState*,
                           int mipLevelCount);

    SK_API GrGLuint createCompressedTexture2D(SkISize dimensions,
                                       SkImage::CompressionType compression,
                                       GrGLFormat,
                                       GrMipmapped,
                                       GrGLTextureParameters::SamplerOverriddenState*);

    SK_API bool onReadPixels(GrSurface*,
                      SkIRect,
                      GrColorType surfaceColorType,
                      GrColorType dstColorType,
                      void*,
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

    SK_API bool readOrTransferPixelsFrom(GrSurface*,
                                  SkIRect rect,
                                  GrColorType surfaceColorType,
                                  GrColorType dstColorType,
                                  void* offsetOrPtr,
                                  int rowWidthInPixels);

    // Unbinds xfer buffers from GL for operations that don't need them.
    // Before calling any variation of TexImage, TexSubImage, etc..., call this with
    // GrGpuBufferType::kXferCpuToGpu to ensure that the PIXEL_UNPACK_BUFFER is unbound.
    // Before calling ReadPixels and reading back into cpu memory call this with
    // GrGpuBufferType::kXferGpuToCpu to ensure that the PIXEL_PACK_BUFFER is unbound.
    SK_API void unbindXferBuffer(GrGpuBufferType type);

    SK_API void onResolveRenderTarget(GrRenderTarget* target, const SkIRect& resolveRect) override;

    SK_API bool onRegenerateMipMapLevels(GrTexture*) override;

    SK_API bool onCopySurface(GrSurface* dst, GrSurface* src, const SkIRect& srcRect,
                       const SkIPoint& dstPoint) override;

    // binds texture unit in GL
    SK_API void setTextureUnit(int unitIdx);

    SK_API void flushBlendAndColorWrite(const GrXferProcessor::BlendInfo& blendInfo, const GrSwizzle&);

    SK_API void addFinishedProc(GrGpuFinishedProc finishedProc,
                         GrGpuFinishedContext finishedContext) override;

    SK_API GrOpsRenderPass* onGetOpsRenderPass(GrRenderTarget*,
                                        bool useMultisampleFBO,
                                        GrAttachment*,
                                        GrSurfaceOrigin,
                                        const SkIRect&,
                                        const GrOpsRenderPass::LoadAndStoreInfo&,
                                        const GrOpsRenderPass::StencilLoadAndStoreInfo&,
                                        const SkTArray<GrSurfaceProxy*, true>& sampledProxies,
                                        GrXferBarrierFlags renderPassXferBarriers) override;

    SK_API bool onSubmitToGpu(bool syncCpu) override;

    SK_API bool waitSync(GrGLsync, uint64_t timeout, bool flush);

    SK_API bool copySurfaceAsDraw(GrSurface* dst, bool drawToMultisampleFBO, GrSurface* src,
                           const SkIRect& srcRect, const SkIPoint& dstPoint);
    SK_API void copySurfaceAsCopyTexSubImage(GrSurface* dst, GrSurface* src, const SkIRect& srcRect,
                                      const SkIPoint& dstPoint);
    SK_API bool copySurfaceAsBlitFramebuffer(GrSurface* dst, GrSurface* src, const SkIRect& srcRect,
                                      const SkIPoint& dstPoint);

    class ProgramCache : public GrThreadSafePipelineBuilder {
    public:
        SK_API ProgramCache(int runtimeProgramCacheSize);
        SK_API ~ProgramCache() override;

        SK_API void abandon();
        SK_API void reset();
        SK_API sk_sp<GrGLProgram> findOrCreateProgram(GrDirectContext*,
                                               const GrProgramInfo&);
        SK_API sk_sp<GrGLProgram> findOrCreateProgram(GrDirectContext*,
                                               const GrProgramDesc&,
                                               const GrProgramInfo&,
                                               Stats::ProgramCacheResult*);
        SK_API bool precompileShader(GrDirectContext*, const SkData& key, const SkData& data);

    private:
        struct Entry;

        SK_API sk_sp<GrGLProgram> findOrCreateProgramImpl(GrDirectContext*,
                                                   const GrProgramDesc&,
                                                   const GrProgramInfo&,
                                                   Stats::ProgramCacheResult*);

        struct DescHash {
            uint32_t operator()(const GrProgramDesc& desc) const {
                return SkOpts::hash_fn(desc.asKey(), desc.keyLength(), 0);
            }
        };

        SkLRUCache<GrProgramDesc, std::unique_ptr<Entry>, DescHash> fMap;
    };

    SK_API void flushPatchVertexCount(uint8_t count);

    SK_API void flushColorWrite(bool writeColor);
    SK_API void flushClearColor(std::array<float, 4>);

    // flushes the scissor. see the note on flushBoundTextureAndParams about
    // flushing the scissor after that function is called.
    void flushScissor(const GrScissorState& scissorState, int rtHeight, GrSurfaceOrigin rtOrigin) {
        this->flushScissorTest(GrScissorTest(scissorState.enabled()));
        if (scissorState.enabled()) {
            this->flushScissorRect(scissorState.rect(), rtHeight, rtOrigin);
        }
    }
    SK_API void flushScissorTest(GrScissorTest);

    SK_API void flushWindowRectangles(const GrWindowRectsState&, const GrGLRenderTarget*, GrSurfaceOrigin);
    SK_API void disableWindowRectangles();

    int numTextureUnits() const { return this->caps()->shaderCaps()->maxFragmentSamplers(); }

    // Binds a texture to a target on the "scratch" texture unit to use for texture operations
    // other than usual draw flow (i.e. a GrGLProgram derived from a GrPipeline used to draw). It
    // ensures that such operations don't negatively interact with draws. The active texture unit
    // and the binding for 'target' will change.
    SK_API void bindTextureToScratchUnit(GrGLenum target, GrGLint textureID);

    // The passed bounds contains the render target's color values that will subsequently be
    // written.
    SK_API void flushRenderTarget(GrGLRenderTarget*, bool useMultisampleFBO, GrSurfaceOrigin,
                           const SkIRect& bounds);
    // This version has an implicit bounds of the entire render target.
    SK_API void flushRenderTarget(GrGLRenderTarget*, bool useMultisampleFBO);
    // This version can be used when the render target's colors will not be written.
    SK_API void flushRenderTargetNoColorWrites(GrGLRenderTarget*, bool useMultisampleFBO);

    SK_API void flushStencil(const GrStencilSettings&, GrSurfaceOrigin);
    SK_API void disableStencil();

    SK_API void flushConservativeRasterState(bool enable);

    SK_API void flushWireframeState(bool enable);

    SK_API void flushFramebufferSRGB(bool enable);

    // Uploads src data of a color type to the currently bound texture on the active texture unit.
    // The caller specifies color type that the texture is being used with, which may be different
    // than the src color type. This fails if the combination of texture format, texture color type,
    // and src data color type are not valid. No conversion is performed on the data before passing
    // it to GL. 'dstRect' must be the texture bounds if mipLevelCount is greater than 1.
    SK_API bool uploadColorTypeTexData(GrGLFormat textureFormat,
                                GrColorType textureColorType,
                                SkISize texDims,
                                GrGLenum target,
                                SkIRect dstRect,
                                GrColorType srcColorType,
                                const GrMipLevel texels[],
                                int mipLevelCount);

    // Uploads a constant color to a texture using the "default" format and color type. Overwrites
    // entire levels. Bit n in 'levelMask' indicates whether level n should be written. This
    // function doesn't know if MIP levels have been allocated, thus levelMask should not have bits
    // beyond the low bit set if the texture is not MIP mapped.
    SK_API bool uploadColorToTex(GrGLFormat textureFormat,
                          SkISize texDims,
                          GrGLenum target,
                          std::array<float, 4> color,
                          uint32_t levelMask);

    // Pushes data to the currently bound texture to the currently active unit. 'dstRect' must be
    // the texture bounds if mipLevelCount is greater than 1.
    SK_API void uploadTexData(SkISize dimensions,
                       GrGLenum target,
                       SkIRect dstRect,
                       GrGLenum externalFormat,
                       GrGLenum externalType,
                       size_t bpp,
                       const GrMipLevel texels[],
                       int mipLevelCount);

    // Helper for onCreateCompressedTexture. Compressed textures are read-only so we only use this
    // to populate a new texture. Returns false if we failed to create and upload the texture.
    SK_API bool uploadCompressedTexData(SkImage::CompressionType compressionType,
                                 GrGLFormat,
                                 SkISize dimensions,
                                 GrMipmapped,
                                 GrGLenum target,
                                 const void* data, size_t dataSize);

    // Calls one of various versions of renderBufferStorageMultisample.
    SK_API bool renderbufferStorageMSAA(const GrGLContext& ctx, int sampleCount, GrGLenum format,
                                 int width, int height);

    SK_API bool createRenderTargetObjects(const GrGLTexture::Desc&,
                                   int sampleCount,
                                   GrGLRenderTarget::IDs*);
    enum TempFBOTarget {
        kSrc_TempFBOTarget,
        kDst_TempFBOTarget
    };

    // Binds a surface as a FBO for copying, reading, or clearing. If the surface already owns an
    // FBO ID then that ID is bound. If not the surface is temporarily bound to a FBO and that FBO
    // is bound. This must be paired with a call to unbindSurfaceFBOForPixelOps().
    SK_API void bindSurfaceFBOForPixelOps(GrSurface* surface, int mipLevel, GrGLenum fboTarget,
                                   TempFBOTarget tempFBOTarget);

    // Must be called if bindSurfaceFBOForPixelOps was used to bind a surface for copying.
    SK_API void unbindSurfaceFBOForPixelOps(GrSurface* surface, int mipLevel, GrGLenum fboTarget);

#ifdef SK_ENABLE_DUMP_GPU
    void onDumpJSON(SkJSONWriter*) const override;
#endif

    SK_API bool createCopyProgram(GrTexture* srcTexture);
    SK_API bool createMipmapProgram(int progIdx);

    std::unique_ptr<GrGLContext> fGLContext;

    // GL program-related state
    sk_sp<ProgramCache>         fProgramCache;

    ///////////////////////////////////////////////////////////////////////////
    ///@name Caching of GL State
    ///@{
    int                         fHWActiveTextureUnitIdx;

    GrGLuint                    fHWProgramID;
    sk_sp<GrGLProgram>          fHWProgram;

    enum TriState {
        kNo_TriState,
        kYes_TriState,
        kUnknown_TriState
    };

    GrGLuint                    fTempSrcFBOID;
    GrGLuint                    fTempDstFBOID;

    GrGLuint                    fStencilClearFBOID;

    // last scissor / viewport scissor state seen by the GL.
    struct {
        TriState fEnabled;
        GrNativeRect fRect;
        void invalidate() {
            fEnabled = kUnknown_TriState;
            fRect.invalidate();
        }
    } fHWScissorSettings;

    class {
    public:
        bool valid() const { return kInvalidSurfaceOrigin != fRTOrigin; }
        void invalidate() { fRTOrigin = kInvalidSurfaceOrigin; }
        bool knownDisabled() const { return this->valid() && !fWindowState.enabled(); }
        void setDisabled() {
            fRTOrigin = kTopLeft_GrSurfaceOrigin;
            fWindowState.setDisabled();
        }

        void set(GrSurfaceOrigin rtOrigin, int width, int height,
                 const GrWindowRectsState& windowState) {
            fRTOrigin = rtOrigin;
            fWidth = width;
            fHeight = height;
            fWindowState = windowState;
        }

        bool knownEqualTo(GrSurfaceOrigin rtOrigin, int width, int height,
                          const GrWindowRectsState& windowState) const {
            if (!this->valid()) {
                return false;
            }
            if (fWindowState.numWindows() &&
                (fRTOrigin != rtOrigin || fWidth != width || fHeight != height)) {
                return false;
            }
            return fWindowState == windowState;
        }

    private:
        enum { kInvalidSurfaceOrigin = -1 };

        int                  fRTOrigin;
        int                  fWidth;
        int                  fHeight;
        GrWindowRectsState   fWindowState;
    } fHWWindowRectsState;

    GrNativeRect fHWViewport;

    /**
     * Tracks vertex attrib array state.
     */
    class HWVertexArrayState {
    public:
        HWVertexArrayState() : fCoreProfileVertexArray(nullptr) { this->invalidate(); }

        ~HWVertexArrayState() { delete fCoreProfileVertexArray; }

        void invalidate() {
            fBoundVertexArrayIDIsValid = false;
            fDefaultVertexArrayAttribState.invalidate();
            if (fCoreProfileVertexArray) {
                fCoreProfileVertexArray->invalidateCachedState();
            }
        }

        void notifyVertexArrayDelete(GrGLuint id) {
            if (fBoundVertexArrayIDIsValid && fBoundVertexArrayID == id) {
                // Does implicit bind to 0
                fBoundVertexArrayID = 0;
            }
        }

        void setVertexArrayID(GrGLGpu* gpu, GrGLuint arrayID) {
            if (!gpu->glCaps().vertexArrayObjectSupport()) {
                SkASSERT(0 == arrayID);
                return;
            }
            if (!fBoundVertexArrayIDIsValid || arrayID != fBoundVertexArrayID) {
                GR_GL_CALL(gpu->glInterface(), BindVertexArray(arrayID));
                fBoundVertexArrayIDIsValid = true;
                fBoundVertexArrayID = arrayID;
            }
        }

        /**
         * Binds the vertex array that should be used for internal draws, and returns its attrib
         * state. This binds the default VAO (ID=zero) unless we are on a core profile, in which
         * case we use a placeholder array instead.
         *
         * If an index buffer is provided, it will be bound to the vertex array. Otherwise the
         * index buffer binding will be left unchanged.
         *
         * The returned GrGLAttribArrayState should be used to set vertex attribute arrays.
         */
        SK_API GrGLAttribArrayState* bindInternalVertexArray(GrGLGpu*, const GrBuffer* ibuff = nullptr);

    private:
        GrGLuint             fBoundVertexArrayID;
        bool                 fBoundVertexArrayIDIsValid;

        // We return a non-const pointer to this from bindArrayAndBuffersToDraw when vertex array 0
        // is bound. However, this class is internal to GrGLGpu and this object never leaks out of
        // GrGLGpu.
        GrGLAttribArrayState fDefaultVertexArrayAttribState;

        // This is used when we're using a core profile.
        GrGLVertexArray*     fCoreProfileVertexArray;
    } fHWVertexArrayState;

    uint8_t fHWPatchVertexCount;

    struct {
        GrGLenum                fGLTarget;
        GrGpuResource::UniqueID fBoundBufferUniqueID;
        bool                    fBufferZeroKnownBound;

        void invalidate() {
            fBoundBufferUniqueID.makeInvalid();
            fBufferZeroKnownBound = false;
        }
    }                                       fHWBufferState[kGrGpuBufferTypeCount];

    auto* hwBufferState(GrGpuBufferType type) {
        unsigned typeAsUInt = static_cast<unsigned>(type);
        SkASSERT(typeAsUInt < SK_ARRAY_COUNT(fHWBufferState));
        SkASSERT(type != GrGpuBufferType::kUniform);
        return &fHWBufferState[typeAsUInt];
    }

    enum class FlushType {
        kIfRequired,
        kForce,
    };

    // This calls glFlush if it is required for previous operations or kForce is passed.
    SK_API void flush(FlushType flushType = FlushType::kIfRequired);

    void setNeedsFlush() { fNeedsGLFlush = true; }

    struct {
        GrBlendEquation fEquation;
        GrBlendCoeff    fSrcCoeff;
        GrBlendCoeff    fDstCoeff;
        SkPMColor4f     fConstColor;
        bool            fConstColorValid;
        TriState        fEnabled;

        void invalidate() {
            fEquation = kIllegal_GrBlendEquation;
            fSrcCoeff = kIllegal_GrBlendCoeff;
            fDstCoeff = kIllegal_GrBlendCoeff;
            fConstColorValid = false;
            fEnabled = kUnknown_TriState;
        }
    }                                       fHWBlendState;

    TriState                                fHWConservativeRasterEnabled;

    TriState                                fHWWireframeEnabled;

    GrStencilSettings                       fHWStencilSettings;
    GrSurfaceOrigin                         fHWStencilOrigin;
    TriState                                fHWStencilTestEnabled;

    TriState                                fHWWriteToColor;
    GrGpuResource::UniqueID                 fHWBoundRenderTargetUniqueID;
    bool                                    fHWBoundFramebufferIsMSAA;
    TriState                                fHWSRGBFramebuffer;

    class TextureUnitBindings {
    public:
        TextureUnitBindings() = default;
        TextureUnitBindings(const TextureUnitBindings&) = delete;
        TextureUnitBindings& operator=(const TextureUnitBindings&) = delete;

        SK_API GrGpuResource::UniqueID boundID(GrGLenum target) const;
        SK_API bool hasBeenModified(GrGLenum target) const;
        SK_API void setBoundID(GrGLenum target, GrGpuResource::UniqueID);
        SK_API void invalidateForScratchUse(GrGLenum target);
        SK_API void invalidateAllTargets(bool markUnmodified);

    private:
        struct TargetBinding {
            GrGpuResource::UniqueID fBoundResourceID;
            bool fHasBeenModified = false;
        };
        TargetBinding fTargetBindings[3];
    };
    SkAutoTArray<TextureUnitBindings> fHWTextureUnitBindings;

    GrGLfloat fHWClearColor[4];

    GrGLuint fBoundDrawFramebuffer = 0;

    /** IDs for copy surface program. (3 sampler types) */
    struct {
        GrGLuint    fProgram = 0;
        GrGLint     fTextureUniform = 0;
        GrGLint     fTexCoordXformUniform = 0;
        GrGLint     fPosXformUniform = 0;
    }                                       fCopyPrograms[3];
    sk_sp<GrGLBuffer>                       fCopyProgramArrayBuffer;

    /** IDs for texture mipmap program. (4 filter configurations) */
    struct {
        GrGLuint    fProgram = 0;
        GrGLint     fTextureUniform = 0;
        GrGLint     fTexCoordXformUniform = 0;
    }                                       fMipmapPrograms[4];
    sk_sp<GrGLBuffer>                       fMipmapProgramArrayBuffer;

    SK_API static int TextureToCopyProgramIdx(GrTexture* texture);

    static int TextureSizeToMipmapProgramIdx(int width, int height) {
        const bool wide = (width > 1) && SkToBool(width & 0x1);
        const bool tall = (height > 1) && SkToBool(height & 0x1);
        return (wide ? 0x2 : 0x0) | (tall ? 0x1 : 0x0);
    }

    GrPrimitiveType fLastPrimitiveType;

    GrGLTextureParameters::ResetTimestamp fResetTimestampForTextureParameters = 0;

    class SamplerObjectCache;
    std::unique_ptr<SamplerObjectCache> fSamplerObjectCache;

    std::unique_ptr<GrGLOpsRenderPass> fCachedOpsRenderPass;
    GrFinishCallbacks fFinishCallbacks;

    // If we've called a command that requires us to call glFlush than this will be set to true
    // since we defer calling flush until submit time. When we call submitToGpu if this is true then
    // we call glFlush and reset this to false.
    bool fNeedsGLFlush = false;

    SkDEBUGCODE(bool fIsExecutingCommandBuffer_DebugOnly = false);

    friend class GrGLPathRendering; // For accessing setTextureUnit.

    using INHERITED = GrGpu;
};

#endif
