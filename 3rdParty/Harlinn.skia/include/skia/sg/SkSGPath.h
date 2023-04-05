/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGPath_DEFINED
#define SkSGPath_DEFINED

#include "SkSGGeometryNode.h"

#include "skia/core/SkPath.h"

class SkCanvas;
class SkPaint;

namespace sksg {

/**
 * Concrete Geometry node, wrapping an SkPath.
 */
class Path : public GeometryNode {
public:
    static sk_sp<Path> Make()                { return sk_sp<Path>(new Path(SkPath())); }
    static sk_sp<Path> Make(const SkPath& r) { return sk_sp<Path>(new Path(r)); }

    SG_ATTRIBUTE(Path, SkPath, fPath)

    // Temporarily inlined for SkPathFillType staging
    // SG_MAPPED_ATTRIBUTE(FillType, SkPathFillType, fPath)

    SkPathFillType getFillType() const {
        return fPath.getFillType();
    }

    void setFillType(SkPathFillType fillType) {
        if (fillType != fPath.getFillType()) {
            fPath.setFillType(fillType);
            this->invalidate();
        }
    }

protected:
    SK_API void onClip(SkCanvas*, bool antiAlias) const override;
    SK_API void onDraw(SkCanvas*, const SkPaint&) const override;
    SK_API bool onContains(const SkPoint&)        const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;
    SK_API SkPath onAsPath() const override;

private:
    SK_API explicit Path(const SkPath&);

    SkPath fPath;

    using INHERITED = GeometryNode;
};

} // namespace sksg

#endif // SkSGPath_DEFINED
