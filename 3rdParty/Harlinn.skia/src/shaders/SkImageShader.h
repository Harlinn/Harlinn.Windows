/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkImageShader_DEFINED
#define SkImageShader_DEFINED

#include <skia/core/SkImage.h>
#include "src/shaders/SkBitmapProcShader.h"
#include "src/shaders/SkShaderBase.h"

class SkImageShader : public SkShaderBase {
public:
    SK_API static sk_sp<SkShader> Make(sk_sp<SkImage>,
                                SkTileMode tmx,
                                SkTileMode tmy,
                                const SkSamplingOptions&,
                                const SkMatrix* localMatrix,
                                bool clampAsIfUnpremul = false);

    SK_API bool isOpaque() const override;

#if SK_SUPPORT_GPU
    SK_API std::unique_ptr<GrFragmentProcessor> asFragmentProcessor(const GrFPArgs&) const override;
#endif

    SK_API static SkM44 CubicResamplerMatrix(float B, float C);

private:
    SK_FLATTENABLE_HOOKS(SkImageShader)

    SK_API SkImageShader(sk_sp<SkImage>,
                  SkTileMode tmx,
                  SkTileMode tmy,
                  const SkSamplingOptions&,
                  const SkMatrix* localMatrix,
                  bool clampAsIfUnpremul = false);

    SK_API void flatten(SkWriteBuffer&) const override;
#ifdef SK_ENABLE_LEGACY_SHADERCONTEXT
    SK_API Context* onMakeContext(const ContextRec&, SkArenaAlloc* storage) const override;
#endif
    SK_API SkImage* onIsAImage(SkMatrix*, SkTileMode*) const override;

    SK_API bool onAppendStages(const SkStageRec&) const override;
    SK_API SkStageUpdater* onAppendUpdatableStages(const SkStageRec&) const override;

    SK_API SkUpdatableShader* onUpdatableShader(SkArenaAlloc* alloc) const override;

    SK_API skvm::Color onProgram(skvm::Builder*, skvm::Coord device, skvm::Coord local, skvm::Color paint,
                          const SkMatrixProvider&, const SkMatrix* localM, const SkColorInfo& dst,
                          skvm::Uniforms* uniforms, SkArenaAlloc*) const override;

    class TransformShader;
    SK_API skvm::Color makeProgram(
            skvm::Builder*, skvm::Coord device, skvm::Coord local, skvm::Color paint,
            const SkMatrixProvider&, const SkMatrix* localM, const SkColorInfo& dst,
            skvm::Uniforms* uniforms, const TransformShader* coordShader, SkArenaAlloc*) const;

    SK_API bool doStages(const SkStageRec&, TransformShader* = nullptr) const;

    sk_sp<SkImage>          fImage;
    const SkSamplingOptions fSampling;
    const SkTileMode        fTileModeX;
    const SkTileMode        fTileModeY;
    const bool              fClampAsIfUnpremul;

    friend class SkShaderBase;
    using INHERITED = SkShaderBase;
};

#endif
