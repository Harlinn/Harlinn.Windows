/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGPath_DEFINED
#define SkSVGPath_DEFINED

#include "skia/core/SkPath.h"
#include "skia/svg/SkSVGShape.h"

class SkSVGPath final : public SkSVGShape {
public:
    static sk_sp<SkSVGPath> Make() { return sk_sp<SkSVGPath>(new SkSVGPath()); }

    SVG_ATTR(Path, SkPath, SkPath())

protected:
    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    SK_API void onDraw(SkCanvas*, const SkSVGLengthContext&, const SkPaint&,
                SkPathFillType) const override;

    SK_API SkPath onAsPath(const SkSVGRenderContext&) const override;

    SK_API SkRect onObjectBoundingBox(const SkSVGRenderContext&) const override;

private:
    SK_API SkSVGPath();

    using INHERITED = SkSVGShape;
};

#endif // SkSVGPath_DEFINED
