/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGGeometryEffect_DEFINED
#define SkSGGeometryEffect_DEFINED

#include "SkSGGeometryNode.h"

#include "skia/core/SkPaint.h"
#include "skia/core/SkPath.h"
#include "skia/effects/SkTrimPathEffect.h"
#include "SkSGTransform.h"

namespace sksg {

/**
 * Base class for geometry effects.
 */
class GeometryEffect : public GeometryNode {
protected:
    SK_API explicit GeometryEffect(sk_sp<GeometryNode>);
    SK_API ~GeometryEffect() override;

    SK_API void onClip(SkCanvas*, bool antiAlias) const final;
    SK_API void onDraw(SkCanvas*, const SkPaint&) const final;
    SK_API bool onContains(const SkPoint&)        const final;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) final;
    SK_API SkPath onAsPath() const final;

    SK_API virtual SkPath onRevalidateEffect(const sk_sp<GeometryNode>&) = 0;

private:
    const sk_sp<GeometryNode> fChild;
    SkPath                    fPath; // transformed child cache.

    using INHERITED = GeometryNode;
};

/**
 * Apply a trim effect to the child geometry.
 */
class TrimEffect final : public GeometryEffect {
public:
    static sk_sp<TrimEffect> Make(sk_sp<GeometryNode> child) {
        return child ? sk_sp<TrimEffect>(new TrimEffect(std::move(child))) : nullptr;
    }

    SG_ATTRIBUTE(Start , SkScalar              , fStart )
    SG_ATTRIBUTE(Stop  , SkScalar              , fStop  )
    SG_ATTRIBUTE(Mode  , SkTrimPathEffect::Mode, fMode  )

private:
    SK_API explicit TrimEffect(sk_sp<GeometryNode> child) : INHERITED(std::move(child)) {}

    SK_API SkPath onRevalidateEffect(const sk_sp<GeometryNode>&) override;

    SkScalar               fStart = 0,
                           fStop  = 1;
    SkTrimPathEffect::Mode fMode  = SkTrimPathEffect::Mode::kNormal;

    using INHERITED = GeometryEffect;
};

/**
 * Apply a transform to a GeometryNode.
 */
class GeometryTransform final : public GeometryEffect {
public:
    static sk_sp<GeometryTransform> Make(sk_sp<GeometryNode> child, sk_sp<Transform> transform) {
        return child && transform
            ? sk_sp<GeometryTransform>(new GeometryTransform(std::move(child),
                                                             std::move(transform)))
            : nullptr;
    }

    SK_API ~GeometryTransform() override;

    const sk_sp<Transform>& getTransform() const { return fTransform; }

private:
    SK_API GeometryTransform(sk_sp<GeometryNode>, sk_sp<Transform>);

    SK_API SkPath onRevalidateEffect(const sk_sp<GeometryNode>&) override;

    const sk_sp<Transform> fTransform;

    using INHERITED = GeometryEffect;
};

/**
 * Apply a dash effect to the child geometry.
 *
 * Follows the same semantics as SkDashPathEffect, with one minor tweak: when the number of
 * intervals is odd, they are repeated once more to attain an even sequence (same as SVG
 * stroke-dasharray: https://www.w3.org/TR/SVG11/painting.html#StrokeDasharrayProperty).
 */
class DashEffect final : public GeometryEffect {
public:
    static sk_sp<DashEffect> Make(sk_sp<GeometryNode> child) {
        return child ? sk_sp<DashEffect>(new DashEffect(std::move(child))) : nullptr;
    }

    SG_ATTRIBUTE(Intervals, std::vector<float>, fIntervals)
    SG_ATTRIBUTE(Phase,                 float , fPhase    )

private:
    SK_API explicit DashEffect(sk_sp<GeometryNode> child) : INHERITED(std::move(child)) {}

    SK_API SkPath onRevalidateEffect(const sk_sp<GeometryNode>&) override;

    std::vector<float> fIntervals;
    float              fPhase = 0;

    using INHERITED = GeometryEffect;
};

/**
 * Apply a rounded-corner effect to the child geometry.
 */
class RoundEffect final : public GeometryEffect {
public:
    static sk_sp<RoundEffect> Make(sk_sp<GeometryNode> child) {
        return child ? sk_sp<RoundEffect>(new RoundEffect(std::move(child))) : nullptr;
    }

    SG_ATTRIBUTE(Radius, SkScalar, fRadius)

private:
    SK_API explicit RoundEffect(sk_sp<GeometryNode> child) : INHERITED(std::move(child)) {}

    SK_API SkPath onRevalidateEffect(const sk_sp<GeometryNode>&) override;

    SkScalar fRadius = 0;

    using INHERITED = GeometryEffect;
};

/**
 * Apply an offset effect to the child geometry.
 */
class OffsetEffect final : public GeometryEffect {
public:
    static sk_sp<OffsetEffect> Make(sk_sp<GeometryNode> child) {
        return child ? sk_sp<OffsetEffect>(new OffsetEffect(std::move(child))) : nullptr;
    }

    SG_ATTRIBUTE(Offset     , SkScalar     , fOffset    )
    SG_ATTRIBUTE(MiterLimit , SkScalar     , fMiterLimit)
    SG_ATTRIBUTE(Join       , SkPaint::Join, fJoin      )

private:
    SK_API explicit OffsetEffect(sk_sp<GeometryNode> child) : INHERITED(std::move(child)) {}

    SK_API SkPath onRevalidateEffect(const sk_sp<GeometryNode>&) override;

    SkScalar fOffset     = 0,
             fMiterLimit = 4;
    SkPaint::Join  fJoin = SkPaint::kMiter_Join;

    using INHERITED = GeometryEffect;
};

} // namespace sksg

#endif // SkSGGeometryEffect_DEFINED
