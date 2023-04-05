/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkMiniRecorder_DEFINED
#define SkMiniRecorder_DEFINED

#include <skia/core/SkScalar.h>
#include <skia/core/SkTypes.h>
#include <skia/private/SkNoncopyable.h>
#include "src/core/SkRecords.h"
class SkCanvas;

// Records small pictures, but only a limited subset of the canvas API, and may fail.
class SkMiniRecorder : SkNoncopyable {
public:
    SK_API SkMiniRecorder();
    SK_API ~SkMiniRecorder();

    // Try to record an op.  Returns false on failure.
    SK_API bool drawPath(const SkPath&, const SkPaint&);
    SK_API bool drawRect(const SkRect&, const SkPaint&);
    SK_API bool drawTextBlob(const SkTextBlob*, SkScalar x, SkScalar y, const SkPaint&);

    // Detach anything we've recorded as a picture, resetting this SkMiniRecorder.
    // If cull is nullptr we'll calculate it.
    SK_API sk_sp<SkPicture> detachAsPicture(const SkRect* cull);

    // Flush anything we've recorded to the canvas, resetting this SkMiniRecorder.
    // This is logically the same as but rather more efficient than:
    //    sk_sp<SkPicture> pic(this->detachAsPicture(nullptr));
    //    pic->playback(canvas);
    SK_API void flushAndReset(SkCanvas*);

private:
    enum class State {
        kEmpty,
        kDrawPath,
        kDrawRect,
        kDrawTextBlob,
    };

    State fState;

    template <size_t A, size_t B>
    struct Max { static const size_t val = A > B ? A : B; };

    static const size_t kInlineStorage =
        Max<sizeof(SkRecords::DrawPath),
        Max<sizeof(SkRecords::DrawRect),
            sizeof(SkRecords::DrawTextBlob)>::val>::val;
    alignas(void*) alignas(double) char fBuffer[kInlineStorage];
};

#endif//SkMiniRecorder_DEFINED
