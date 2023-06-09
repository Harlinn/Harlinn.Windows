/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkEffectPriv_DEFINED
#define SkEffectPriv_DEFINED

#include <skia/core/SkImageInfo.h>
#include <skia/core/SkMatrix.h>

class SkArenaAlloc;
class SkColorSpace;
class SkMatrixProvider;
class SkPaint;
class SkRasterPipeline;

// Passed to effects that will add stages to rasterpipeline
struct SkStageRec {
    SkRasterPipeline*       fPipeline;
    SkArenaAlloc*           fAlloc;
    SkColorType             fDstColorType;
    SkColorSpace*           fDstCS;         // may be nullptr
    const SkPaint&          fPaint;
    const SkMatrix*         fLocalM;        // may be nullptr
    const SkMatrixProvider& fMatrixProvider;
};

#endif // SkEffectPriv_DEFINED
