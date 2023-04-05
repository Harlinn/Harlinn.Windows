/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGMerge_DEFINED
#define SkSGMerge_DEFINED

#include "SkSGGeometryNode.h"

#include "skia/core/SkPath.h"

#include <vector>

class SkCanvas;
class SkPaint;

namespace sksg {

/**
 * Concrete Geometry node, combining other geometries based on Mode.
 */
class Merge final : public GeometryNode {
public:
    enum class Mode {
        // Append path mode.
        kMerge,

        // SkPathOp ops.
        kUnion,
        kIntersect,
        kDifference,
        kReverseDifference,
        kXOR,
    };

    struct Rec {
        sk_sp<GeometryNode> fGeo;
        Mode                fMode;
    };

    static sk_sp<Merge> Make(std::vector<Rec>&& recs) {
        return sk_sp<Merge>(new Merge(std::move(recs)));
    }

    SK_API ~Merge() override;

protected:
    SK_API void onClip(SkCanvas*, bool antiAlias) const override;
    SK_API void onDraw(SkCanvas*, const SkPaint&) const override;
    SK_API bool onContains(const SkPoint&)        const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;
    SK_API SkPath onAsPath() const override;

private:
    SK_API Merge(std::vector<Rec>&& recs);

    const std::vector<Rec> fRecs;
    SkPath                 fMerged;

    using INHERITED = GeometryNode;
};

} // namespace sksg

#endif // SkSGMerge_DEFINED
