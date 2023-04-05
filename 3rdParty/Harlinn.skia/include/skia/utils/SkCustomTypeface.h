#pragma once
/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkCustomTypeface_DEFINED
#define SkCustomTypeface_DEFINED

#include <skia/core/SkFontMetrics.h>
#include <skia/core/SkFontStyle.h>
#include <skia/core/SkImage.h>
#include <skia/core/SkPaint.h>
#include <skia/core/SkPath.h>
#include <skia/core/SkPicture.h>
#include <skia/core/SkTypeface.h>

#include <vector>

class SkStream;

class SkCustomTypefaceBuilder {
public:
    SK_API SkCustomTypefaceBuilder();

    SK_API void setGlyph(SkGlyphID, float advance, const SkPath&);
    SK_API void setGlyph(SkGlyphID, float advance, const SkPath&, const SkPaint&);
    SK_API void setGlyph(SkGlyphID, float advance, sk_sp<SkImage>, float scale);
    SK_API void setGlyph(SkGlyphID, float advance, sk_sp<SkPicture>);

    SK_API void setMetrics(const SkFontMetrics& fm, float scale = 1);
    SK_API void setFontStyle(SkFontStyle);

    SK_API sk_sp<SkTypeface> detach();

private:
    std::vector<SkPath> fPaths;
    std::vector<float>  fAdvances;
    SkFontMetrics       fMetrics;
    SkFontStyle         fStyle;

    SK_API static sk_sp<SkTypeface> Deserialize(SkStream*);

    friend class SkTypeface;
};

#endif
