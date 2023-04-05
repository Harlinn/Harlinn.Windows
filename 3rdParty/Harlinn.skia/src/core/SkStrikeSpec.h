/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkStrikeSpec_DEFINED
#define SkStrikeSpec_DEFINED

#include <skia/core/SkMaskFilter.h>
#include <skia/core/SkPathEffect.h>
#include "src/core/SkDescriptor.h"
#include "src/core/SkStrikeForGPU.h"

#include <tuple>

#if SK_SUPPORT_GPU
#include "src/gpu/text/GrSDFTControl.h"
class GrStrikeCache;
class GrTextStrike;
#endif

class SkFont;
class SkPaint;
class SkStrikeCache;
class SkSurfaceProps;

class SkStrikeSpec {
public:
    SK_API SkStrikeSpec(const SkDescriptor& descriptor, sk_sp<SkTypeface> typeface);
    SK_API SkStrikeSpec(const SkStrikeSpec&);
    SkStrikeSpec& operator=(const SkStrikeSpec&) = delete;

    SK_API SkStrikeSpec(SkStrikeSpec&&);
    SkStrikeSpec& operator=(SkStrikeSpec&&) = delete;

    SK_API ~SkStrikeSpec();

    // Create a strike spec for mask style cache entries.
    SK_API static SkStrikeSpec MakeMask(
            const SkFont& font,
            const SkPaint& paint,
            const SkSurfaceProps& surfaceProps,
            SkScalerContextFlags scalerContextFlags,
            const SkMatrix& deviceMatrix);

    // Create a strike spec for path style cache entries.
    SK_API static std::tuple<SkStrikeSpec, SkScalar> MakePath(
            const SkFont& font,
            const SkPaint& paint,
            const SkSurfaceProps& surfaceProps,
            SkScalerContextFlags scalerContextFlags);

    SK_API static std::tuple<SkStrikeSpec, SkScalar> MakeSourceFallback(
            const SkFont& font,
            const SkPaint& paint,
            const SkSurfaceProps& surfaceProps,
            SkScalerContextFlags scalerContextFlags,
            SkScalar maxSourceGlyphDimension);

    // Create a canonical strike spec for device-less measurements.
    SK_API static std::tuple<SkStrikeSpec, SkScalar> MakeCanonicalized(
            const SkFont& font, const SkPaint* paint = nullptr);

    // Create a strike spec without a device, and does not switch over to path for large sizes.
    SK_API static SkStrikeSpec MakeWithNoDevice(const SkFont& font, const SkPaint* paint = nullptr);

    // Make a strike spec for PDF Vector strikes
    SK_API static SkStrikeSpec MakePDFVector(const SkTypeface& typeface, int* size);

#if SK_SUPPORT_GPU
    // Create a strike spec for scaled distance field text.
    SK_API static std::tuple<SkStrikeSpec, SkScalar, SkScalar, SkScalar> MakeSDFT(
            const SkFont& font,
            const SkPaint& paint,
            const SkSurfaceProps& surfaceProps,
            const SkMatrix& deviceMatrix,
            const GrSDFTControl& control);

    SK_API sk_sp<GrTextStrike> findOrCreateGrStrike(GrStrikeCache* cache) const;
#endif

    SK_API SkScopedStrikeForGPU findOrCreateScopedStrike(SkStrikeForGPUCacheInterface* cache) const;

    SK_API sk_sp<SkStrike> findOrCreateStrike() const;

    SK_API sk_sp<SkStrike> findOrCreateStrike(SkStrikeCache* cache) const;

    std::unique_ptr<SkScalerContext> createScalerContext() const {
        SkScalerContextEffects effects{fPathEffect.get(), fMaskFilter.get()};
        return fTypeface->createScalerContext(effects, fAutoDescriptor.getDesc());
    }

    const SkDescriptor& descriptor() const { return *fAutoDescriptor.getDesc(); }
    const SkTypeface& typeface() const { return *fTypeface; }
    SK_API static bool ShouldDrawAsPath(const SkPaint& paint, const SkFont& font, const SkMatrix& matrix);
    SK_API SkString dump() const;

private:
    SK_API SkStrikeSpec(
            const SkFont& font,
            const SkPaint& paint,
            const SkSurfaceProps& surfaceProps,
            SkScalerContextFlags scalerContextFlags,
            const SkMatrix& deviceMatrix);

    SkAutoDescriptor fAutoDescriptor;
    sk_sp<SkMaskFilter> fMaskFilter{nullptr};
    sk_sp<SkPathEffect> fPathEffect{nullptr};
    sk_sp<SkTypeface> fTypeface;
};

class SkBulkGlyphMetrics {
public:
    SK_API explicit SkBulkGlyphMetrics(const SkStrikeSpec& spec);
    SK_API SkSpan<const SkGlyph*> glyphs(SkSpan<const SkGlyphID> glyphIDs);
    SK_API const SkGlyph* glyph(SkGlyphID glyphID);

private:
    inline static constexpr int kTypicalGlyphCount = 20;
    SkAutoSTArray<kTypicalGlyphCount, const SkGlyph*> fGlyphs;
    sk_sp<SkStrike> fStrike;
};

class SkBulkGlyphMetricsAndPaths {
public:
    SK_API explicit SkBulkGlyphMetricsAndPaths(const SkStrikeSpec& spec);
    SK_API explicit SkBulkGlyphMetricsAndPaths(sk_sp<SkStrike>&& strike);
    SK_API ~SkBulkGlyphMetricsAndPaths();
    SK_API SkSpan<const SkGlyph*> glyphs(SkSpan<const SkGlyphID> glyphIDs);
    SK_API const SkGlyph* glyph(SkGlyphID glyphID);
    SK_API void findIntercepts(const SkScalar bounds[2], SkScalar scale, SkScalar xPos,
                        const SkGlyph* glyph, SkScalar* array, int* count);

private:
    inline static constexpr int kTypicalGlyphCount = 20;
    SkAutoSTArray<kTypicalGlyphCount, const SkGlyph*> fGlyphs;
    sk_sp<SkStrike> fStrike;
};

class SkBulkGlyphMetricsAndImages {
public:
    SK_API explicit SkBulkGlyphMetricsAndImages(const SkStrikeSpec& spec);
    SK_API explicit SkBulkGlyphMetricsAndImages(sk_sp<SkStrike>&& strike);
    SK_API ~SkBulkGlyphMetricsAndImages();
    SK_API SkSpan<const SkGlyph*> glyphs(SkSpan<const SkPackedGlyphID> packedIDs);
    SK_API const SkGlyph* glyph(SkPackedGlyphID packedID);
    SK_API const SkDescriptor& descriptor() const;

private:
    inline static constexpr int kTypicalGlyphCount = 64;
    SkAutoSTArray<kTypicalGlyphCount, const SkGlyph*> fGlyphs;
    sk_sp<SkStrike> fStrike;
};

#endif  // SkStrikeSpec_DEFINED
