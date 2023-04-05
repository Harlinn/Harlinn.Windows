/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkFlattenable.h>

#if defined(SK_DISABLE_EFFECT_DESERIALIZATION)

    void SkFlattenable::PrivateInitializer::InitEffects() {}
    void SkFlattenable::PrivateInitializer::InitImageFilters() {}

#else

    #include <skia/core/SkBBHFactory.h>
    #include <skia/core/SkColorFilter.h>
    #include <skia/core/SkPathEffect.h>
    #include <skia/effects/Sk1DPathEffect.h>
    #include <skia/effects/Sk2DPathEffect.h>
    #include <skia/effects/SkCornerPathEffect.h>
    #include <skia/effects/SkDiscretePathEffect.h>
    #include <skia/effects/SkGradientShader.h>
    #include <skia/effects/SkOverdrawColorFilter.h>
    #include <skia/effects/SkPerlinNoiseShader.h>
    #include <skia/effects/SkShaderMaskFilter.h>
    #include <skia/effects/SkTableColorFilter.h>
    #include "src/core/SkBlendModeBlender.h"
    #include "src/core/SkColorFilter_Matrix.h"
    #include "src/core/SkImageFilter_Base.h"
    #include "src/core/SkRecordedDrawable.h"
    #include "src/effects/SkDashImpl.h"
    #include "src/effects/SkEmbossMaskFilter.h"
    #include "src/effects/SkOpPE.h"
    #include "src/effects/SkTrimPE.h"
    #include "src/shaders/SkBitmapProcShader.h"
    #include "src/shaders/SkColorFilterShader.h"
    #include "src/shaders/SkColorShader.h"
    #include "src/shaders/SkComposeShader.h"
    #include "src/shaders/SkEmptyShader.h"
    #include "src/shaders/SkImageShader.h"
    #include "src/shaders/SkLocalMatrixShader.h"
    #include "src/shaders/SkPictureShader.h"
    #include "src/shaders/SkShaderBase.h"

    #include <skia/effects/SkImageFilters.h>
    #include "src/core/SkLocalMatrixImageFilter.h"
    #include "src/core/SkMatrixImageFilter.h"

#ifdef SK_ENABLE_SKSL
    #include <skia/effects/SkRuntimeEffect.h>
#endif

#ifdef SK_SUPPORT_LEGACY_DRAWLOOPER
    #include <skia/effects/SkLayerDrawLooper.h>
#endif

    /**
     *  Register most effects for deserialization.
     *
     *  None of these are strictly required for Skia to operate, so if you're
     *  not using deserialization yourself, you can define
     *  SK_DISABLE_EFFECT_SERIALIZATION, or modify/replace this file as needed.
     */
    void SkFlattenable::PrivateInitializer::InitEffects() {
        // Shaders.
        SK_REGISTER_FLATTENABLE(SkColor4Shader);
        SK_REGISTER_FLATTENABLE(SkColorFilterShader);
        SK_REGISTER_FLATTENABLE(SkColorShader);
        SK_REGISTER_FLATTENABLE(SkShader_Blend);
        SK_REGISTER_FLATTENABLE(SkEmptyShader);
        SK_REGISTER_FLATTENABLE(SkLocalMatrixShader);
        SK_REGISTER_FLATTENABLE(SkPictureShader);
        SkGradientShader::RegisterFlattenables();
        SkPerlinNoiseShader::RegisterFlattenables();
        SkShaderBase::RegisterFlattenables();

        // Color filters.
        SkColorFilter_Matrix::RegisterFlattenables();
        SkColorFilterBase::RegisterFlattenables();
        SkTableColorFilter::RegisterFlattenables();

        // Blenders.
        SK_REGISTER_FLATTENABLE(SkBlendModeBlender);

#ifdef SK_ENABLE_SKSL
        // Runtime shaders, color filters, and blenders.
        SkRuntimeEffect::RegisterFlattenables();
#endif

        // Mask filters.
        SK_REGISTER_FLATTENABLE(SkEmbossMaskFilter);
        SkMaskFilter::RegisterFlattenables();
        SkShaderMaskFilter::RegisterFlattenables();

        // Path effects.
        SkCornerPathEffect::RegisterFlattenables();
        SK_REGISTER_FLATTENABLE(SkDashImpl);
        SkDiscretePathEffect::RegisterFlattenables();
        SkLine2DPathEffect::RegisterFlattenables();
        SkPath2DPathEffect::RegisterFlattenables();
        SK_REGISTER_FLATTENABLE(SkMatrixPE);
        SK_REGISTER_FLATTENABLE(SkOpPE);
        SkPath1DPathEffect::RegisterFlattenables();
        SK_REGISTER_FLATTENABLE(SkStrokePE);
        SK_REGISTER_FLATTENABLE(SkStrokeAndFillPE);
        SK_REGISTER_FLATTENABLE(SkTrimPE);
        SkPathEffectBase::RegisterFlattenables();

        // Misc.
#ifdef SK_SUPPORT_LEGACY_DRAWLOOPER
        SK_REGISTER_FLATTENABLE(SkLayerDrawLooper);
#endif
        SK_REGISTER_FLATTENABLE(SkRecordedDrawable);
    }

    /*
     *  Register SkImageFilters for deserialization.
     *
     *  None of these are strictly required for Skia to operate, so if you're
     *  not using deserialization yourself, you can define
     *  SK_DISABLE_EFFECT_SERIALIZATION, or modify/replace this file as needed.
     */
    void SkFlattenable::PrivateInitializer::InitImageFilters() {
        SkRegisterAlphaThresholdImageFilterFlattenable();
        SkRegisterArithmeticImageFilterFlattenable();
        SkRegisterBlendImageFilterFlattenable();
        SkRegisterBlurImageFilterFlattenable();
        SkRegisterColorFilterImageFilterFlattenable();
        SkRegisterComposeImageFilterFlattenable();
        SkRegisterCropImageFilterFlattenable();
        SkRegisterDisplacementMapImageFilterFlattenable();
        SkRegisterDropShadowImageFilterFlattenable();
        SkRegisterImageImageFilterFlattenable();
        SkRegisterLightingImageFilterFlattenables();
        SkRegisterMagnifierImageFilterFlattenable();
        SkRegisterMatrixConvolutionImageFilterFlattenable();
        SkRegisterMergeImageFilterFlattenable();
        SkRegisterMorphologyImageFilterFlattenables();
        SkRegisterOffsetImageFilterFlattenable();
        SkRegisterPictureImageFilterFlattenable();
#ifdef SK_ENABLE_SKSL
        SkRegisterRuntimeImageFilterFlattenable();
#endif
        SkRegisterShaderImageFilterFlattenable();
        SkRegisterTileImageFilterFlattenable();
        SK_REGISTER_FLATTENABLE(SkLocalMatrixImageFilter);
        SK_REGISTER_FLATTENABLE(SkMatrixImageFilter);
    }

#endif
