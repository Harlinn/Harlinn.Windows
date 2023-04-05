#pragma once
/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/gpu/gl/GrGLAssembleInterface.h>

SK_API void GrGetEGLQueryAndDisplay(GrEGLQueryStringFn** queryString, GrEGLDisplay* display,
                             void* ctx, GrGLGetProc get);
