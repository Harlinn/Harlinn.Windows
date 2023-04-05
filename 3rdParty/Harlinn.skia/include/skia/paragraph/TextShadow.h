// Copyright 2019 Google LLC.
#ifndef TextShadow_DEFINED
#define TextShadow_DEFINED

#include "skia/core/SkColor.h"
#include "skia/core/SkPoint.h"

namespace skia {
namespace textlayout {

class TextShadow {
public:
    SkColor fColor = SK_ColorBLACK;
    SkPoint fOffset;
    double fBlurSigma = 0.0;

    SK_API TextShadow();

    SK_API TextShadow(SkColor color, SkPoint offset, double blurSigma);

    SK_API bool operator==(const TextShadow& other) const;

    SK_API bool operator!=(const TextShadow& other) const;

    SK_API bool hasShadow() const;
};
}  // namespace textlayout
}  // namespace skia

#endif  // TextShadow_DEFINED
