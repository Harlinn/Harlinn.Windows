/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/core/SkRefCnt.h"
#include "skia/gpu/GrDirectContext.h"
//#include "skia/gpu/gl/GrGLFunctions.h"
//#include "skia/gpu/gl/GrGLInterface.h"
//#include "skia/tools/gpu/gl/GLTestContext.h"

#include "skia/tools/gpu/d3d/D3DTestContext.h"

sk_sp<GrDirectContext> create_direct_context(
    std::ostringstream& driverinfo,
    std::unique_ptr<sk_gpu_test::D3DTestContext>* d3dContext )
{
    d3dContext->reset( sk_gpu_test::CreatePlatformD3DTestContext( d3dContext->get() ) );
    if ( !d3dContext )
    {
        return nullptr;
    }
    ( *d3dContext )->makeCurrent( );
    sk_sp<GrDirectContext> result = ( *d3dContext )->makeContext( GrContextOptions( ) );
    if ( !result )
    {
        d3dContext->reset( );
        return nullptr;
    }

    return result;
}


 /*
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <sstream>

// create_direct_context implementation for EGL.
sk_sp<GrDirectContext> create_direct_context(
        std::ostringstream& driverinfo,
        std::unique_ptr<sk_gpu_test::GLTestContext>* glContext) {
    glContext->reset(sk_gpu_test::CreatePlatformGLTestContext(kGLES_GrGLStandard));
    if (!glContext) {
        return nullptr;
    }
    (*glContext)->makeCurrent();
    sk_sp<GrDirectContext> result = (*glContext)->makeContext(GrContextOptions());
    if (!result) {
        glContext->reset();
        return nullptr;
    }

    driverinfo << "GL Version: " << glGetString(GL_VERSION) << "\n";
    driverinfo << "GL Vendor: " << glGetString(GL_VENDOR) << "\n";
    driverinfo << "GL Renderer: " << glGetString(GL_RENDERER) << "\n";
    driverinfo << "GL Extensions: " << glGetString(GL_EXTENSIONS) << "\n";

    return result;
}
*/
