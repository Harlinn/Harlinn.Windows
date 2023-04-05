/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrSDFTControl_DEFINED
#define GrSDFTControl_DEFINED

#include <skia/core/SkFont.h>
#include <skia/core/SkScalar.h>

class SkMatrix;
class SkSurfaceProps;

class GrSDFTControl {
public:
    SK_API GrSDFTControl(bool ableToUseSDFT, bool useSDFTForSmallText, SkScalar min, SkScalar max);

    enum DrawingType : uint8_t {
        kDirect = 1,
        kSDFT = 2,
        kPath = 4
    };

    SK_API DrawingType drawingType(
            const SkFont& font, const SkPaint& paint, const SkMatrix& viewMatrix) const;

    SK_API SkFont getSDFFont(const SkFont& font,
                      const SkMatrix& viewMatrix,
                      SkScalar* textRatio) const;
    SK_API std::pair<SkScalar, SkScalar> computeSDFMinMaxScale(
            SkScalar textSize, const SkMatrix& viewMatrix) const;
private:
    SK_API static SkScalar MinSDFTRange(bool useSDFTForSmallText, SkScalar min);

    // Below this size (in device space) distance field text will not be used.
    const SkScalar fMinDistanceFieldFontSize;

    // Above this size (in device space) distance field text will not be used and glyphs will
    // be rendered from outline as individual paths.
    const SkScalar fMaxDistanceFieldFontSize;

    const bool fAbleToUseSDFT;
};

#endif  // GrSDFTControl_DEFINED
