/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/core/SkCanvas.h"
#include "skia/core/SkPaint.h"
#include "skia/utils/SkParsePath.h"
#include "skia/svg/SkSVGPath.h"
#include "skia/svg/SkSVGRenderContext.h"
#include "skia/svg/SkSVGValue.h"

SkSVGPath::SkSVGPath() : INHERITED(SkSVGTag::kPath) { }

bool SkSVGPath::parseAndSetAttribute(const char* n, const char* v) {
    return INHERITED::parseAndSetAttribute(n, v) ||
           this->setPath(SkSVGAttributeParser::parse<SkPath>("d", n, v));
}

template <>
bool SkSVGAttributeParser::parse<SkPath>(SkPath* path) {
    return SkParsePath::FromSVGString(fCurPos, path);
}

void SkSVGPath::onDraw(SkCanvas* canvas, const SkSVGLengthContext&, const SkPaint& paint,
                       SkPathFillType fillType) const {
    // the passed fillType follows inheritance rules and needs to be applied at draw time.
    SkPath path = fPath;  // Note: point and verb data are CoW
    path.setFillType(fillType);
    canvas->drawPath(path, paint);
}

SkPath SkSVGPath::onAsPath(const SkSVGRenderContext& ctx) const {
    SkPath path = fPath;
    // clip-rule can be inherited and needs to be applied at clip time.
    path.setFillType(ctx.presentationContext().fInherited.fClipRule->asFillType());
    this->mapToParent(&path);
    return path;
}

SkRect SkSVGPath::onObjectBoundingBox(const SkSVGRenderContext& ctx) const {
    return fPath.computeTightBounds();
}
