/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
 */

#ifndef SkStrike_DEFINED
#define SkStrike_DEFINED

#include <skia/core/SkFontMetrics.h>
#include <skia/core/SkFontTypes.h>
#include <skia/private/SkMutex.h>
#include <skia/private/SkTHash.h>
#include <skia/private/SkTemplates.h>
#include "src/core/SkArenaAlloc.h"
#include "src/core/SkDescriptor.h"
#include "src/core/SkGlyph.h"
#include "src/core/SkGlyphRunPainter.h"
#include "src/core/SkStrikeForGPU.h"
#include <memory>

class SkScalerContext;

// The value stored in fDigestForPackedGlyphID.
// index() is the index into fGlyphForIndex.
class SkGlyphDigest {
public:
    // Default ctor is only needed for the hash table.
    SkGlyphDigest() = default;
    SkGlyphDigest(size_t i, const SkGlyph& glyph)
        : fIndex{SkTo<uint32_t>(i)}
        , fIsEmpty(glyph.isEmpty())
        , fIsColor(glyph.isColor())
        , fCanDrawAsMask{SkStrikeForGPU::CanDrawAsMask(glyph)}
        , fCanDrawAsSDFT{SkStrikeForGPU::CanDrawAsSDFT(glyph)} {}
    int index()          const {return fIndex;        }
    bool isEmpty()       const {return fIsEmpty;      }
    bool isColor()       const {return fIsColor;      }
    bool canDrawAsMask() const {return fCanDrawAsMask;}
    bool canDrawAsSDFT() const {return fCanDrawAsSDFT;}

private:
    static_assert(SkPackedGlyphID::kEndData == 20);
    uint32_t fIndex : SkPackedGlyphID::kEndData;
    uint32_t fIsEmpty       : 1;
    uint32_t fIsColor       : 1;
    uint32_t fCanDrawAsMask : 1;
    uint32_t fCanDrawAsSDFT : 1;
};

// This class represents a strike: a specific combination of typeface, size, matrix, etc., and
// holds the glyphs for that strike.
class SkScalerCache {
public:
    SK_API SkScalerCache(std::unique_ptr<SkScalerContext> scaler,
                  const SkFontMetrics* metrics = nullptr);

    // Lookup (or create if needed) the toGlyph using toID. If that glyph is not initialized with
    // an image, then use the information in from to initialize the width, height top, left,
    // format and image of the toGlyph. This is mainly used preserving the glyph if it was
    // created by a search of desperation.
    SK_API std::tuple<SkGlyph*, size_t> mergeGlyphAndImage(
            SkPackedGlyphID toID, const SkGlyph& from) SK_EXCLUDES(fMu);

    // If the path has never been set, then add a path to glyph.
    SK_API std::tuple<const SkPath*, size_t> mergePath(
            SkGlyph* glyph, const SkPath* path) SK_EXCLUDES(fMu);

    /** Return the number of glyphs currently cached. */
    SK_API int countCachedGlyphs() const SK_EXCLUDES(fMu);

    /** If the advance axis intersects the glyph's path, append the positions scaled and offset
        to the array (if non-null), and set the count to the updated array length.
    */
    SK_API void findIntercepts(const SkScalar bounds[2], SkScalar scale, SkScalar xPos,
                        SkGlyph* , SkScalar* array, int* count) SK_EXCLUDES(fMu);

    const SkFontMetrics& getFontMetrics() const {
        return fFontMetrics;
    }

    SK_API std::tuple<SkSpan<const SkGlyph*>, size_t> metrics(
            SkSpan<const SkGlyphID> glyphIDs, const SkGlyph* results[]) SK_EXCLUDES(fMu);

    SK_API std::tuple<SkSpan<const SkGlyph*>, size_t> preparePaths(
            SkSpan<const SkGlyphID> glyphIDs, const SkGlyph* results[]) SK_EXCLUDES(fMu);

    SK_API std::tuple<SkSpan<const SkGlyph*>, size_t> prepareImages(
            SkSpan<const SkPackedGlyphID> glyphIDs, const SkGlyph* results[]) SK_EXCLUDES(fMu);

    SK_API size_t prepareForDrawingMasksCPU(SkDrawableGlyphBuffer* drawables) SK_EXCLUDES(fMu);

    // SkStrikeForGPU APIs
    const SkGlyphPositionRoundingSpec& roundingSpec() const {
        return fRoundingSpec;
    }

    SK_API size_t prepareForMaskDrawing(
            SkDrawableGlyphBuffer* drawables, SkSourceGlyphBuffer* rejects) SK_EXCLUDES(fMu);

    SK_API size_t prepareForSDFTDrawing(
            SkDrawableGlyphBuffer* drawables, SkSourceGlyphBuffer* rejects) SK_EXCLUDES(fMu);

    SK_API size_t prepareForPathDrawing(
            SkDrawableGlyphBuffer* drawables, SkSourceGlyphBuffer* rejects) SK_EXCLUDES(fMu);

    void dump() const SK_EXCLUDES(fMu);

    SkScalerContext* getScalerContext() const { return fScalerContext.get(); }

private:
    template <typename Fn>
    size_t commonFilterLoop(SkDrawableGlyphBuffer* drawables, Fn&& fn) SK_REQUIRES(fMu);

    // Return a glyph. Create it if it doesn't exist, and initialize the glyph with metrics and
    // advances using a scaler.
    SK_API std::tuple<SkGlyph*, size_t> glyph(SkPackedGlyphID) SK_REQUIRES(fMu);

    SK_API std::tuple<SkGlyphDigest, size_t> digest(SkPackedGlyphID) SK_REQUIRES(fMu);

    // Generate the glyph digest information and update structures to add the glyph.
    SK_API SkGlyphDigest addGlyph(SkGlyph* glyph) SK_REQUIRES(fMu);

    SK_API std::tuple<const void*, size_t> prepareImage(SkGlyph* glyph) SK_REQUIRES(fMu);

    // If the path has never been set, then use the scaler context to add the glyph.
    SK_API std::tuple<const SkPath*, size_t> preparePath(SkGlyph*) SK_REQUIRES(fMu);

    enum PathDetail {
        kMetricsOnly,
        kMetricsAndPath
    };

    // internalPrepare will only be called with a mutex already held.
    SK_API std::tuple<SkSpan<const SkGlyph*>, size_t> internalPrepare(
            SkSpan<const SkGlyphID> glyphIDs,
            PathDetail pathDetail,
            const SkGlyph** results) SK_REQUIRES(fMu);

    const std::unique_ptr<SkScalerContext> fScalerContext;
    const SkFontMetrics                    fFontMetrics;
    const SkGlyphPositionRoundingSpec      fRoundingSpec;

    mutable SkMutex fMu;

    // Map from a combined GlyphID and sub-pixel position to a SkGlyphDigest. The actual glyph is
    // stored in the fAlloc. The pointer to the glyph is stored fGlyphForIndex. The
    // SkGlyphDigest's fIndex field stores the index. This pointer provides an unchanging
    // reference to the SkGlyph as long as the strike is alive, and fGlyphForIndex
    // provides a dense index for glyphs.
    SkTHashMap<SkPackedGlyphID, SkGlyphDigest> fDigestForPackedGlyphID SK_GUARDED_BY(fMu);
    std::vector<SkGlyph*> fGlyphForIndex SK_GUARDED_BY(fMu);

    // so we don't grow our arrays a lot
    inline static constexpr size_t kMinGlyphCount = 8;
    inline static constexpr size_t kMinGlyphImageSize = 16 /* height */ * 8 /* width */;
    inline static constexpr size_t kMinAllocAmount = kMinGlyphImageSize * kMinGlyphCount;

    SkArenaAlloc            fAlloc SK_GUARDED_BY(fMu) {kMinAllocAmount};
};

#endif  // SkStrike_DEFINED
