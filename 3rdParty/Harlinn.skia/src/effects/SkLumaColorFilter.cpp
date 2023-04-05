/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkString.h>
#include <skia/effects/SkLumaColorFilter.h>
#include <skia/effects/SkRuntimeEffect.h>
#include "src/core/SkRuntimeEffectPriv.h"

sk_sp<SkColorFilter> SkLumaColorFilter::Make() {
#ifdef SK_ENABLE_SKSL
    const char* code =
        "half4 main(half4 inColor) {"
            "return saturate(dot(half3(0.2126, 0.7152, 0.0722), inColor.rgb)).000r;"
        "}";
    sk_sp<SkRuntimeEffect> effect = SkMakeCachedRuntimeEffect(SkRuntimeEffect::MakeForColorFilter,
                                                              code);
    SkASSERT(effect);

    return effect->makeColorFilter(SkData::MakeEmpty());
#else
    // TODO(skia:12197)
    return nullptr;
#endif
}
