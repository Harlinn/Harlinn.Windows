#pragma once
/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkStrokeRec_DEFINED
#define SkStrokeRec_DEFINED

#include <skia/core/SkPaint.h>
#include <skia/private/SkMacros.h>

class SkPath;

SK_BEGIN_REQUIRE_DENSE
class SkStrokeRec {
public:
    enum InitStyle {
        kHairline_InitStyle,
        kFill_InitStyle
    };
    SK_API SkStrokeRec(InitStyle style);
    SK_API SkStrokeRec(const SkPaint&, SkPaint::Style, SkScalar resScale = 1);
    SK_API explicit SkStrokeRec(const SkPaint&, SkScalar resScale = 1);

    enum Style {
        kHairline_Style,
        kFill_Style,
        kStroke_Style,
        kStrokeAndFill_Style
    };

    static constexpr int kStyleCount = kStrokeAndFill_Style + 1;

    SK_API Style getStyle() const;
    SkScalar getWidth() const { return fWidth; }
    SkScalar getMiter() const { return fMiterLimit; }
    SkPaint::Cap getCap() const { return (SkPaint::Cap)fCap; }
    SkPaint::Join getJoin() const { return (SkPaint::Join)fJoin; }

    bool isHairlineStyle() const {
        return kHairline_Style == this->getStyle();
    }

    bool isFillStyle() const {
        return kFill_Style == this->getStyle();
    }

    SK_API void setFillStyle();
    SK_API void setHairlineStyle();
    /**
     *  Specify the strokewidth, and optionally if you want stroke + fill.
     *  Note, if width==0, then this request is taken to mean:
     *      strokeAndFill==true -> new style will be Fill
     *      strokeAndFill==false -> new style will be Hairline
     */
    SK_API void setStrokeStyle(SkScalar width, bool strokeAndFill = false);

    void setStrokeParams(SkPaint::Cap cap, SkPaint::Join join, SkScalar miterLimit) {
        fCap = cap;
        fJoin = join;
        fMiterLimit = miterLimit;
    }

    SkScalar getResScale() const {
        return fResScale;
    }

    void setResScale(SkScalar rs) {
        SkASSERT(rs > 0 && SkScalarIsFinite(rs));
        fResScale = rs;
    }

    /**
     *  Returns true if this specifes any thick stroking, i.e. applyToPath()
     *  will return true.
     */
    bool needToApply() const {
        Style style = this->getStyle();
        return (kStroke_Style == style) || (kStrokeAndFill_Style == style);
    }

    /**
     *  Apply these stroke parameters to the src path, returning the result
     *  in dst.
     *
     *  If there was no change (i.e. style == hairline or fill) this returns
     *  false and dst is unchanged. Otherwise returns true and the result is
     *  stored in dst.
     *
     *  src and dst may be the same path.
     */
    SK_API bool applyToPath(SkPath* dst, const SkPath& src) const;

    /**
     *  Apply these stroke parameters to a paint.
     */
    SK_API void applyToPaint(SkPaint* paint) const;

    /**
     * Gives a conservative value for the outset that should applied to a
     * geometries bounds to account for any inflation due to applying this
     * strokeRec to the geometry.
     */
    SK_API SkScalar getInflationRadius() const;

    /**
     * Equivalent to:
     *   SkStrokeRec rec(paint, style);
     *   rec.getInflationRadius();
     * This does not account for other effects on the paint (i.e. path
     * effect).
     */
    SK_API static SkScalar GetInflationRadius(const SkPaint&, SkPaint::Style);

    SK_API static SkScalar GetInflationRadius(SkPaint::Join, SkScalar miterLimit, SkPaint::Cap,
                                       SkScalar strokeWidth);

    /**
     * Compare if two SkStrokeRecs have an equal effect on a path.
     * Equal SkStrokeRecs produce equal paths. Equality of produced
     * paths does not take the ResScale parameter into account.
     */
    bool hasEqualEffect(const SkStrokeRec& other) const {
        if (!this->needToApply()) {
            return this->getStyle() == other.getStyle();
        }
        return fWidth == other.fWidth &&
               (fJoin != SkPaint::kMiter_Join || fMiterLimit == other.fMiterLimit) &&
               fCap == other.fCap &&
               fJoin == other.fJoin &&
               fStrokeAndFill == other.fStrokeAndFill;
    }

private:
    SK_API void init(const SkPaint&, SkPaint::Style, SkScalar resScale);

    SkScalar        fResScale;
    SkScalar        fWidth;
    SkScalar        fMiterLimit;
    // The following three members are packed together into a single u32.
    // This is to avoid unnecessary padding and ensure binary equality for
    // hashing (because the padded areas might contain garbage values).
    //
    // fCap and fJoin are larger than needed to avoid having to initialize
    // any pad values
    uint32_t        fCap : 16;             // SkPaint::Cap
    uint32_t        fJoin : 15;            // SkPaint::Join
    uint32_t        fStrokeAndFill : 1;    // bool
};
SK_END_REQUIRE_DENSE

#endif
