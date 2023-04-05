/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkBigPicture_DEFINED
#define SkBigPicture_DEFINED

#include <skia/core/SkM44.h>
#include <skia/core/SkPicture.h>
#include <skia/core/SkRect.h>
#include <skia/private/SkNoncopyable.h>
#include <skia/private/SkOnce.h>
#include <skia/private/SkTemplates.h>

class SkBBoxHierarchy;
class SkMatrix;
class SkRecord;

// An implementation of SkPicture supporting an arbitrary number of drawing commands.
class SkBigPicture final : public SkPicture {
public:
    // An array of refcounted const SkPicture pointers.
    class SnapshotArray : ::SkNoncopyable {
    public:
        SnapshotArray(const SkPicture* pics[], int count) : fPics(pics), fCount(count) {}
        ~SnapshotArray() { for (int i = 0; i < fCount; i++) { fPics[i]->unref(); } }

        const SkPicture* const* begin() const { return fPics; }
        int count() const { return fCount; }
    private:
        SkAutoTMalloc<const SkPicture*> fPics;
        int fCount;
    };

    SK_API SkBigPicture(const SkRect& cull,
                 sk_sp<SkRecord>,
                 std::unique_ptr<SnapshotArray>,
                 sk_sp<SkBBoxHierarchy>,
                 size_t approxBytesUsedBySubPictures);


// SkPicture overrides
    SK_API void playback(SkCanvas*, AbortCallback*) const override;
    SK_API SkRect cullRect() const override;
    SK_API int approximateOpCount(bool nested) const override;
    SK_API size_t approximateBytesUsed() const override;
    const SkBigPicture* asSkBigPicture() const override { return this; }

// Used by GrLayerHoister
    SK_API void partialPlayback(SkCanvas*,
                         int start,
                         int stop,
                         const SkM44& initialCTM) const;
// Used by GrRecordReplaceDraw
    const SkBBoxHierarchy* bbh() const { return fBBH.get(); }
    const SkRecord*     record() const { return fRecord.get(); }

private:
    int drawableCount() const;
    SK_API SkPicture const* const* drawablePicts() const;

    const SkRect                         fCullRect;
    const size_t                         fApproxBytesUsedBySubPictures;
    sk_sp<const SkRecord>                fRecord;
    std::unique_ptr<const SnapshotArray> fDrawablePicts;
    sk_sp<const SkBBoxHierarchy>         fBBH;
};

#endif//SkBigPicture_DEFINED
