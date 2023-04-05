/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGClipPath_DEFINED
#define SkSVGClipPath_DEFINED

#include "skia/svg/SkSVGHiddenContainer.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGClipPath final : public SkSVGHiddenContainer {
public:
    static sk_sp<SkSVGClipPath> Make() {
        return sk_sp<SkSVGClipPath>(new SkSVGClipPath());
    }

    SVG_ATTR(ClipPathUnits, SkSVGObjectBoundingBoxUnits,
             SkSVGObjectBoundingBoxUnits(SkSVGObjectBoundingBoxUnits::Type::kUserSpaceOnUse))

private:
    friend class SkSVGRenderContext;

    SK_API SkSVGClipPath();

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    SK_API SkPath resolveClip(const SkSVGRenderContext&) const;

    using INHERITED = SkSVGHiddenContainer;
};

#endif // SkSVGClipPath_DEFINED
