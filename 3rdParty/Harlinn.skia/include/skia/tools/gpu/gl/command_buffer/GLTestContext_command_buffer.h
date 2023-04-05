
/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GLTestContext_command_buffer_DEFINED
#define GLTestContext_command_buffer_DEFINED

#include "skia/tools/gpu/gl/GLTestContext.h"

namespace sk_gpu_test {
class CommandBufferGLTestContext : public GLTestContext {
public:
    SK_API ~CommandBufferGLTestContext() override;

    static CommandBufferGLTestContext *Create(int version, GLTestContext* shareContext) {
        CommandBufferGLTestContext* cbShareContext =
                reinterpret_cast<CommandBufferGLTestContext*>(shareContext);
        CommandBufferGLTestContext *ctx = new CommandBufferGLTestContext(version, cbShareContext);
        if (!ctx->isValid()) {
            delete ctx;
            return nullptr;
        }
        return ctx;
    }

    SK_API void presentCommandBuffer();

    SK_API bool makeCurrent();

    SK_API int getStencilBits();

    SK_API int getSampleCount();

private:
    SK_API CommandBufferGLTestContext(int version, CommandBufferGLTestContext* shareContext);

    SK_API void destroyGLContext();

    SK_API void onPlatformMakeNotCurrent() const override;
    SK_API void onPlatformMakeCurrent() const override;

    SK_API std::function<void()> onPlatformGetAutoContextRestore() const override;

    SK_API GrGLFuncPtr onPlatformGetProcAddress(const char *name) const override;

    void *fContext;
    void *fDisplay;
    void *fSurface;
    void *fConfig;
};
}   // namespace sk_gpu_test

#endif
