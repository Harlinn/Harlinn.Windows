/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFilterContext_DEFINED
#define SkSVGFilterContext_DEFINED

#include "skia/core/SkRect.h"
#include "skia/core/SkRefCnt.h"
#include "skia/core/SkString.h"
#include "skia/private/SkTHash.h"
#include "skia/svg/SkSVGTypes.h"

class SkImageFilter;
class SkSVGFeInputType;
class SkSVGRenderContext;

class SkSVGFilterContext {
public:
    SkSVGFilterContext(const SkRect& filterEffectsRegion,
                       const SkSVGObjectBoundingBoxUnits& primitiveUnits)
            : fFilterEffectsRegion(filterEffectsRegion)
            , fPrimitiveUnits(primitiveUnits)
            , fPreviousResult({nullptr, filterEffectsRegion, SkSVGColorspace::kSRGB}) {}

    const SkRect& filterEffectsRegion() const { return fFilterEffectsRegion; }

    SK_API const SkRect& filterPrimitiveSubregion(const SkSVGFeInputType&) const;

    const SkSVGObjectBoundingBoxUnits& primitiveUnits() const { return fPrimitiveUnits; }

    SK_API void registerResult(const SkSVGStringType&, const sk_sp<SkImageFilter>&, const SkRect&, SkSVGColorspace);

    SK_API void setPreviousResult(const sk_sp<SkImageFilter>&, const SkRect&, SkSVGColorspace);

    SK_API bool previousResultIsSourceGraphic() const;

    SK_API SkSVGColorspace resolveInputColorspace(const SkSVGRenderContext&,
                                           const SkSVGFeInputType&) const;

    SK_API sk_sp<SkImageFilter> resolveInput(const SkSVGRenderContext&, const SkSVGFeInputType&) const;
    
    SK_API sk_sp<SkImageFilter> resolveInput(const SkSVGRenderContext&, const SkSVGFeInputType&, SkSVGColorspace) const;

private:
    struct Result {
        sk_sp<SkImageFilter> fImageFilter;
        SkRect fFilterSubregion;
        SkSVGColorspace fColorspace;
    };

    SK_API const Result* findResultById(const SkSVGStringType&) const;

    SK_API std::tuple<sk_sp<SkImageFilter>, SkSVGColorspace> getInput(const SkSVGRenderContext&,
                                                               const SkSVGFeInputType&) const;

    SkRect fFilterEffectsRegion;

    SkSVGObjectBoundingBoxUnits fPrimitiveUnits;

    SkTHashMap<SkSVGStringType, Result> fResults;

    Result fPreviousResult;
};

#endif  // SkSVGFilterContext_DEFINED
