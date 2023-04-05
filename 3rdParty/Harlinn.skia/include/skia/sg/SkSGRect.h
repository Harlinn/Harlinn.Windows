/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGRect_DEFINED
#define SkSGRect_DEFINED

#include "SkSGGeometryNode.h"

#include "skia/core/SkPath.h"
#include "skia/core/SkRRect.h"
#include "skia/core/SkRect.h"

class SkCanvas;
class SkPaint;

namespace sksg {

/**
 * Concrete Geometry node, wrapping an SkRect.
 */
class Rect final : public GeometryNode {
public:
    static sk_sp<Rect> Make()                { return sk_sp<Rect>(new Rect(SkRect::MakeEmpty())); }
    static sk_sp<Rect> Make(const SkRect& r) { return sk_sp<Rect>(new Rect(r)); }

    SG_ATTRIBUTE(L, SkScalar, fRect.fLeft  )
    SG_ATTRIBUTE(T, SkScalar, fRect.fTop   )
    SG_ATTRIBUTE(R, SkScalar, fRect.fRight )
    SG_ATTRIBUTE(B, SkScalar, fRect.fBottom)

    SG_MAPPED_ATTRIBUTE(Direction        , SkPathDirection, fAttrContaier)
    SG_MAPPED_ATTRIBUTE(InitialPointIndex, uint8_t        , fAttrContaier)

protected:
    SK_API void onClip(SkCanvas*, bool antiAlias) const override;
    SK_API void onDraw(SkCanvas*, const SkPaint&) const override;
    SK_API bool onContains(const SkPoint&)        const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;
    SK_API SkPath onAsPath() const override;

private:
    SK_API explicit Rect(const SkRect&);

    SkRect   fRect;

    struct AttrContainer {
        uint8_t fDirection         : 1;
        uint8_t fInitialPointIndex : 2;

        SkPathDirection getDirection() const {
            return static_cast<SkPathDirection>(fDirection);
        }
        void setDirection(SkPathDirection dir) { fDirection = SkTo<uint8_t>(dir); }

        uint8_t getInitialPointIndex() const { return fInitialPointIndex; }
        void setInitialPointIndex(uint8_t idx) { fInitialPointIndex = idx; }
    };
    AttrContainer fAttrContaier = { (int)SkPathDirection::kCW, 0 };

    using INHERITED = GeometryNode;
};

/**
 * Concrete Geometry node, wrapping an SkRRect.
 */
class RRect final : public GeometryNode {
public:
    static sk_sp<RRect> Make()                  { return sk_sp<RRect>(new RRect(SkRRect())); }
    static sk_sp<RRect> Make(const SkRRect& rr) { return sk_sp<RRect>(new RRect(rr)); }

    SG_ATTRIBUTE(RRect, SkRRect, fRRect)

    SG_MAPPED_ATTRIBUTE(Direction        , SkPathDirection, fAttrContaier)
    SG_MAPPED_ATTRIBUTE(InitialPointIndex, uint8_t          , fAttrContaier)

protected:
    SK_API void onClip(SkCanvas*, bool antiAlias) const override;
    SK_API void onDraw(SkCanvas*, const SkPaint&) const override;
    SK_API bool onContains(const SkPoint&)        const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;
    SK_API SkPath onAsPath() const override;

private:
    SK_API explicit RRect(const SkRRect&);

    SkRRect fRRect;

    struct AttrContainer {
        uint8_t fDirection         : 1;
        uint8_t fInitialPointIndex : 2;

        SkPathDirection getDirection() const {
            return static_cast<SkPathDirection>(fDirection);
        }
        void setDirection(SkPathDirection dir) { fDirection = SkTo<uint8_t>(dir); }

        uint8_t getInitialPointIndex() const { return fInitialPointIndex; }
        void setInitialPointIndex(uint8_t idx) { fInitialPointIndex = idx; }
    };
    AttrContainer fAttrContaier = { (int)SkPathDirection::kCW, 0 };

    using INHERITED = GeometryNode;
};

} // namespace sksg

#endif // SkSGRect_DEFINED
