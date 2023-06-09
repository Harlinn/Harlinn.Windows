/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/tools/sk_app/WindowContext.h>

#include <skia/gpu/GrDirectContext.h>
#ifdef SK_GRAPHITE_ENABLED
#include "experimental/graphite/include/Context.h"
#endif

namespace sk_app {

WindowContext::WindowContext(const DisplayParams& params)
        : fDisplayParams(params) {}

WindowContext::~WindowContext() {}

}   //namespace sk_app
