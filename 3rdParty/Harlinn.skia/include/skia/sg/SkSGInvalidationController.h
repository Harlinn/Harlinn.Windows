/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGInvalidationController_DEFINED
#define SkSGInvalidationController_DEFINED

#include "skia/core/SkMatrix.h"
#include "skia/core/SkTypes.h"

#include <vector>

struct SkRect;

namespace sksg {

/**
 * Receiver for invalidation events.
 *
 * Tracks dirty regions for repaint.
 */
class InvalidationController {
public:
    SK_API InvalidationController();
    InvalidationController(const InvalidationController&) = delete;
    InvalidationController& operator=(const InvalidationController&) = delete;

    SK_API void inval(const SkRect&, const SkMatrix& ctm = SkMatrix::I());

    const SkRect& bounds() const { return fBounds; }

    auto begin() const { return fRects.cbegin(); }
    auto   end() const { return fRects.cend();   }

    SK_API void reset();

private:
    std::vector<SkRect> fRects;
    SkRect              fBounds;
};

} // namespace sksg

#endif // SkSGInvalidationController_DEFINED
