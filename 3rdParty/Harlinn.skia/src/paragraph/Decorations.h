// Copyright 2020 Google LLC.
#ifndef Decorations_DEFINED
#define Decorations_DEFINED

#include "skia/core/SkCanvas.h"
#include "skia/core/SkPath.h"
#include "skia/paragraph/TextStyle.h"
#include "src/paragraph/TextLine.h"

namespace skia {
namespace textlayout {

class Decorations {
    public:
    void paint(SkCanvas* canvas, const TextStyle& textStyle, const TextLine::ClipContext& context, SkScalar baseline);

    private:

    void calculateThickness(TextStyle textStyle, sk_sp<SkTypeface> typeface);
    void calculatePosition(TextDecoration decoration, SkScalar ascent);
    void calculatePaint(const TextStyle& textStyle);
    void calculateWaves(const TextStyle& textStyle, SkRect clip);
    void calculateGaps(const TextLine::ClipContext& context, const SkRect& rect, SkScalar baseline, SkScalar halo);

    SkScalar fThickness;
    SkScalar fPosition;

    SkFontMetrics fFontMetrics;
    SkPaint fPaint;
    SkPath fPath;
};
}  // namespace textlayout
}  // namespace skia
#endif
