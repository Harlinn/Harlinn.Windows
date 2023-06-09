/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/core/SkCanvas.h"
#include "skia/svg/SkSVGPoly.h"
#include "skia/svg/SkSVGRenderContext.h"
#include "skia/svg/SkSVGValue.h"
#include "src/core/SkTLazy.h"

SkSVGPoly::SkSVGPoly(SkSVGTag t) : INHERITED(t) {}

bool SkSVGPoly::parseAndSetAttribute(const char* n, const char* v) {
    if (INHERITED::parseAndSetAttribute(n, v)) {
        return true;
    }

    if (this->setPoints(SkSVGAttributeParser::parse<SkSVGPointsType>("points", n, v))) {
        // TODO: we can likely just keep the points array and create the SkPath when needed.
        fPath = SkPath::Polygon(
                fPoints.begin(), fPoints.count(),
                this->tag() == SkSVGTag::kPolygon);  // only polygons are auto-closed
    }

    // No other attributes on this node
    return false;
}

void SkSVGPoly::onDraw(SkCanvas* canvas, const SkSVGLengthContext&, const SkPaint& paint,
                       SkPathFillType fillType) const {
    // the passed fillType follows inheritance rules and needs to be applied at draw time.
    fPath.setFillType(fillType);
    canvas->drawPath(fPath, paint);
}

SkPath SkSVGPoly::onAsPath(const SkSVGRenderContext& ctx) const {
    SkPath path = fPath;

    // clip-rule can be inherited and needs to be applied at clip time.
    path.setFillType(ctx.presentationContext().fInherited.fClipRule->asFillType());

    this->mapToParent(&path);
    return path;
}

SkRect SkSVGPoly::onObjectBoundingBox(const SkSVGRenderContext& ctx) const {
    return fPath.getBounds();
}
