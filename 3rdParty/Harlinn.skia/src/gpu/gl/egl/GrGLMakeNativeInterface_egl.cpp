/*
 * Copyright 2021 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/gpu/gl/GrGLInterface.h>
#include <skia/gpu/gl/egl/GrGLMakeEGLInterface.h>

sk_sp<const GrGLInterface> GrGLMakeNativeInterface() { return GrGLMakeEGLInterface(); }

const GrGLInterface* GrGLCreateNativeInterface() { return GrGLMakeNativeInterface().release(); }
