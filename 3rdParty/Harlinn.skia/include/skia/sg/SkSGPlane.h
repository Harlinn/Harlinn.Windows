/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGPlane_DEFINED
#define SkSGPlane_DEFINED

#include "SkSGGeometryNode.h"

class SkCanvas;
class SkPaint;

namespace sksg {

/**
 * Concrete Geometry node, representing the whole canvas.
 */
class Plane final : public GeometryNode {
public:
    static sk_sp<Plane> Make() { return sk_sp<Plane>(new Plane()); }

protected:
    SK_API void onClip(SkCanvas*, bool antiAlias) const override;
    SK_API void onDraw(SkCanvas*, const SkPaint&) const override;
    SK_API bool onContains(const SkPoint&)        const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;
    SK_API SkPath onAsPath() const override;

private:
    Plane();

    using INHERITED = GeometryNode;
};

} // namespace sksg

#endif // SkSGPlane_DEFINED
