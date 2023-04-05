/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkPathWriter_DEFINED
#define SkPathWriter_DEFINED

#include <skia/core/SkPath.h>
#include <skia/private/SkTArray.h>
#include <skia/private/SkTDArray.h>

class SkOpPtT;

// Construct the path one contour at a time.
// If the contour is closed, copy it to the final output.
// Otherwise, keep the partial contour for later assembly.

class SkPathWriter {
public:
    SK_API SkPathWriter(SkPath& path);
    SK_API void assemble();
    SK_API void conicTo(const SkPoint& pt1, const SkOpPtT* pt2, SkScalar weight);
    SK_API void cubicTo(const SkPoint& pt1, const SkPoint& pt2, const SkOpPtT* pt3);
    SK_API bool deferredLine(const SkOpPtT* pt);
    SK_API void deferredMove(const SkOpPtT* pt);
    SK_API void finishContour();
    bool hasMove() const { return !fFirstPtT; }
    SK_API void init();
    SK_API bool isClosed() const;
    const SkPath* nativePath() const { return fPathPtr; }
    SK_API void quadTo(const SkPoint& pt1, const SkOpPtT* pt2);

private:
    SK_API bool changedSlopes(const SkOpPtT* pt) const;
    SK_API void close();
    const SkTDArray<const SkOpPtT*>& endPtTs() const { return fEndPtTs; }
    SK_API void lineTo();
    SK_API bool matchedLast(const SkOpPtT*) const;
    SK_API void moveTo();
    const SkTArray<SkPath>& partials() const { return fPartials; }
    SK_API bool someAssemblyRequired();
    SK_API SkPoint update(const SkOpPtT* pt);

    SkPath fCurrent;  // contour under construction
    SkTArray<SkPath> fPartials;   // contours with mismatched starts and ends
    SkTDArray<const SkOpPtT*> fEndPtTs;  // possible pt values for partial starts and ends
    SkPath* fPathPtr;  // closed contours are written here
    const SkOpPtT* fDefer[2];  // [0] deferred move, [1] deferred line
    const SkOpPtT* fFirstPtT;  // first in current contour
};

#endif /* defined(__PathOps__SkPathWriter__) */
