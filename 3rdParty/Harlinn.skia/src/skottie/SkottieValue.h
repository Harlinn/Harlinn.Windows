/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkottieValue_DEFINED
#define SkottieValue_DEFINED

#include "skia/core/SkColor.h"
#include "skia/core/SkM44.h"
#include "skia/core/SkPath.h"

#include <initializer_list>
#include <vector>

namespace skjson { class Value; }

namespace skottie {

using ScalarValue = SkScalar;
using   Vec2Value = SkV2;

class VectorValue final : public std::vector<float> {
public:
    VectorValue() = default;

    VectorValue(std::initializer_list<float> l) : INHERITED(l) {}

    operator SkV3()      const;
    operator SkColor()   const;
    operator SkColor4f() const;

private:
    using INHERITED = std::vector<float>;
};

class ShapeValue final : public std::vector<float> {
public:
    operator SkPath() const;
};

} // namespace skottie

#endif // SkottieValue_DEFINED
