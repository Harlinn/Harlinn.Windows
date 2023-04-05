/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkAAClip_DEFINED
#define SkAAClip_DEFINED

#include <skia/core/SkClipOp.h>
#include <skia/core/SkRect.h>
#include "src/core/SkAutoMalloc.h"
#include "src/core/SkBlitter.h"

class SkPath;
class SkRegion;

class SkAAClip {
public:
    SK_API SkAAClip();
    SK_API SkAAClip(const SkAAClip&);
    SK_API ~SkAAClip();

    SK_API SkAAClip& operator=(const SkAAClip&);

    bool isEmpty() const { return nullptr == fRunHead; }
    const SkIRect& getBounds() const { return fBounds; }

    // Returns true iff the clip is not empty, and is just a hard-edged rect (no partial alpha).
    // If true, getBounds() can be used in place of this clip.
    SK_API bool isRect() const;

    SK_API bool setEmpty();
    SK_API bool setRect(const SkIRect&);
    SK_API bool setPath(const SkPath&, const SkIRect& bounds, bool doAA = true);
    SK_API bool setRegion(const SkRegion&);

    SK_API bool op(const SkIRect&, SkClipOp);
    SK_API bool op(const SkRect&, SkClipOp, bool doAA);
    SK_API bool op(const SkAAClip&, SkClipOp);

    SK_API bool translate(int dx, int dy, SkAAClip* dst) const;

    /**
     *  Allocates a mask the size of the aaclip, and expands its data into
     *  the mask, using kA8_Format. Used for tests and visualization purposes.
     */
    SK_API void copyToMask(SkMask*) const;

    bool quickContains(const SkIRect& r) const {
        return this->quickContains(r.fLeft, r.fTop, r.fRight, r.fBottom);
    }

#ifdef SK_DEBUG
    SK_API void validate() const;
    SK_API void debug(bool compress_y=false) const;
#else
    void validate() const {}
    void debug(bool compress_y=false) const {}
#endif

private:
    class Builder;
    struct RunHead;
    friend class SkAAClipBlitter;

    SkIRect  fBounds;
    RunHead* fRunHead;

    SK_API void freeRuns();

    SK_API bool quickContains(int left, int top, int right, int bottom) const;

    SK_API bool trimBounds();
    SK_API bool trimTopBottom();
    SK_API bool trimLeftRight();

    // For SkAAClipBlitter and quickContains
    SK_API const uint8_t* findRow(int y, int* lastYForRow = nullptr) const;
    SK_API const uint8_t* findX(const uint8_t data[], int x, int* initialCount = nullptr) const;
};

///////////////////////////////////////////////////////////////////////////////

class SkAAClipBlitter : public SkBlitter {
public:
    SkAAClipBlitter() : fScanlineScratch(nullptr) {}
    SK_API ~SkAAClipBlitter() override;

    void init(SkBlitter* blitter, const SkAAClip* aaclip) {
        SkASSERT(aaclip && !aaclip->isEmpty());
        fBlitter = blitter;
        fAAClip = aaclip;
        fAAClipBounds = aaclip->getBounds();
    }

    SK_API void blitH(int x, int y, int width) override;
    SK_API void blitAntiH(int x, int y, const SkAlpha[], const int16_t runs[]) override;
    SK_API void blitV(int x, int y, int height, SkAlpha alpha) override;
    SK_API void blitRect(int x, int y, int width, int height) override;
    SK_API void blitMask(const SkMask&, const SkIRect& clip) override;
    SK_API const SkPixmap* justAnOpaqueColor(uint32_t* value) override;

private:
    SkBlitter*      fBlitter;
    const SkAAClip* fAAClip;
    SkIRect         fAAClipBounds;

    // point into fScanlineScratch
    int16_t*        fRuns;
    SkAlpha*        fAA;

    enum {
        kSize = 32 * 32
    };
    SkAutoSMalloc<kSize> fGrayMaskScratch;  // used for blitMask
    void* fScanlineScratch;  // enough for a mask at 32bit, or runs+aa

    SK_API void ensureRunsAndAA();
};

#endif
