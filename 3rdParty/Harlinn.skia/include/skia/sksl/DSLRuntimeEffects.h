#pragma once
/*
 * Copyright 2021 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_DSL_RUNTIME_EFFECTS
#define SKSL_DSL_RUNTIME_EFFECTS

#include <skia/effects/SkRuntimeEffect.h>
#include <skia/sksl/DSL.h>

namespace SkSL {

class Compiler;

namespace dsl {

#ifndef SKSL_STANDALONE

SK_API void StartRuntimeShader(SkSL::Compiler* compiler);

SK_API sk_sp<SkRuntimeEffect> EndRuntimeShader(SkRuntimeEffect::Options options = {});

#endif

} // namespace dsl

} // namespace SkSL

#endif
