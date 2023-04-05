/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkPathOpsLine_DEFINED
#define SkPathOpsLine_DEFINED

#include "src/pathops/SkPathOpsPoint.h"

struct SkDLine {
    SkDPoint fPts[2];

    const SkDPoint& operator[](int n) const { SkASSERT(n >= 0 && n < 2); return fPts[n]; }
    SkDPoint& operator[](int n) { SkASSERT(n >= 0 && n < 2); return fPts[n]; }

    const SkDLine& set(const SkPoint pts[2]) {
        fPts[0] = pts[0];
        fPts[1] = pts[1];
        return *this;
    }

    SK_API double exactPoint(const SkDPoint& xy) const;
    SK_API static double ExactPointH(const SkDPoint& xy, double left, double right, double y);
    SK_API static double ExactPointV(const SkDPoint& xy, double top, double bottom, double x);

    SK_API double nearPoint(const SkDPoint& xy, bool* unequal) const;
    SK_API bool nearRay(const SkDPoint& xy) const;
    SK_API static double NearPointH(const SkDPoint& xy, double left, double right, double y);
    SK_API static double NearPointV(const SkDPoint& xy, double top, double bottom, double x);
    SK_API SkDPoint ptAtT(double t) const;

    void dump() const;
    void dumpID(int ) const;
    void dumpInner() const;
};

#endif
