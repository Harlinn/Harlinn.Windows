/*
 * Copyright 2021 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/core/SkBlendMode.h"
#include "skia/core/SkRefCnt.h"
#include "skia/effects/SkRuntimeEffect.h"
#include "skia/tools/RuntimeBlendUtils.h"

sk_sp<SkBlender> GetRuntimeBlendForBlendMode(SkBlendMode mode) {
    static auto result = SkRuntimeEffect::MakeForBlender(SkString(R"(
        uniform blender b;
        half4 main(half4 src, half4 dst) {
            return b.eval(src, dst);
        }
    )"));

    SkASSERTF(result.effect, "%s", result.errorText.c_str());

    SkRuntimeBlendBuilder builder(result.effect);
    builder.child("b") = SkBlender::Mode(mode);
    return builder.makeBlender();
}
