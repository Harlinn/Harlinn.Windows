/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef RandomScalerContext_DEFINED
#define RandomScalerContext_DEFINED

#include <skia/core/SkTypeface.h>
#include "src/core/SkScalerContext.h"

/*
 * This scaler context is for debug only purposes.  It will 'randomly' but deterministically return
 * LCD / A8 / BW / RBGA masks based off of the Glyph ID
 */

class SkRandomTypeface : public SkTypeface {
public:
    SK_API SkRandomTypeface(sk_sp<SkTypeface> proxy, const SkPaint&, bool fakeit);

    SkTypeface* proxy() const { return fProxy.get(); }
    const SkPaint& paint() const { return fPaint; }

protected:
    SK_API std::unique_ptr<SkScalerContext> onCreateScalerContext(const SkScalerContextEffects&,
                                                           const SkDescriptor*) const override;
    SK_API void onFilterRec(SkScalerContextRec*) const override;
    SK_API void getGlyphToUnicodeMap(SkUnichar*) const override;
    SK_API std::unique_ptr<SkAdvancedTypefaceMetrics> onGetAdvancedMetrics() const override;
    SK_API std::unique_ptr<SkStreamAsset> onOpenStream(int* ttcIndex) const override;
    SK_API sk_sp<SkTypeface> onMakeClone(const SkFontArguments& args) const override;
    SK_API void onGetFontDescriptor(SkFontDescriptor*, bool* isLocal) const override;

    SK_API void onCharsToGlyphs(const SkUnichar* chars, int count, SkGlyphID glyphs[]) const override;
    SK_API int onCountGlyphs() const override;
    SK_API int onGetUPEM() const override;

    SK_API void onGetFamilyName(SkString* familyName) const override;
    SK_API bool onGetPostScriptName(SkString*) const override;
    SK_API SkTypeface::LocalizedStrings* onCreateFamilyNameIterator() const override;

    SK_API void getPostScriptGlyphNames(SkString*) const override;

    SK_API bool onGlyphMaskNeedsCurrentColor() const override { return false; }
    SK_API int onGetVariationDesignPosition(SkFontArguments::VariationPosition::Coordinate coordinates[],
                                     int coordinateCount) const override;
    SK_API int onGetVariationDesignParameters(SkFontParameters::Variation::Axis parameters[],
                                       int parameterCount) const override;
    SK_API int onGetTableTags(SkFontTableTag tags[]) const override;
    SK_API size_t onGetTableData(SkFontTableTag, size_t offset, size_t length, void* data) const override;

private:
    sk_sp<SkTypeface> fProxy;
    SkPaint           fPaint;
    bool              fFakeIt;
};

#endif
