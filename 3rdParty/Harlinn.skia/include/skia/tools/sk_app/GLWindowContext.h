
/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GLWindowContext_DEFINED
#define GLWindowContext_DEFINED


#include "skia/gpu/gl/GrGLInterface.h"

#include "skia/core/SkRefCnt.h"
#include "skia/core/SkSurface.h"

#include "skia/tools/sk_app/WindowContext.h"

namespace sk_app {

class GLWindowContext : public WindowContext {
public:
    SK_API sk_sp<SkSurface> getBackbufferSurface() override;

    bool isValid() override { return SkToBool(fBackendContext.get()); }

    SK_API void resize(int w, int h) override;
    SK_API void swapBuffers() override;

    SK_API void setDisplayParams(const DisplayParams& params) override;

protected:
    SK_API GLWindowContext(const DisplayParams&);
    // This should be called by subclass constructor. It is also called when window/display
    // parameters change. This will in turn call onInitializeContext().
    SK_API void initializeContext();
    virtual sk_sp<const GrGLInterface> onInitializeContext() = 0;

    // This should be called by subclass destructor. It is also called when window/display
    // parameters change prior to initializing a new GL context. This will in turn call
    // onDestroyContext().
    SK_API void destroyContext();
    virtual void onDestroyContext() = 0;

    virtual void onSwapBuffers() = 0;

    sk_sp<const GrGLInterface> fBackendContext;
    sk_sp<SkSurface>           fSurface;
};

}   // namespace sk_app

#endif
