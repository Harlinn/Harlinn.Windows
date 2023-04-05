/*
 * Copyright 2009 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkEdgeClipper_DEFINED
#define SkEdgeClipper_DEFINED

#include <skia/core/SkPath.h>

/** This is basically an iterator. It is initialized with an edge and a clip,
    and then next() is called until it returns kDone_Verb.
 */
class SkEdgeClipper {
public:
    SkEdgeClipper(bool canCullToTheRight) : fCanCullToTheRight(canCullToTheRight) {}

    SK_API bool clipLine(SkPoint p0, SkPoint p1, const SkRect& clip);
    SK_API bool clipQuad(const SkPoint pts[3], const SkRect& clip);
    SK_API bool clipCubic(const SkPoint pts[4], const SkRect& clip);

    SK_API SkPath::Verb next(SkPoint pts[]);

    bool canCullToTheRight() const { return fCanCullToTheRight; }

    /**
     *  Clips each segment from the path, and passes the result (in a clipper) to the
     *  consume proc.
     */
    SK_API static void ClipPath(const SkPath& path, const SkRect& clip, bool canCullToTheRight,
                         void (*consume)(SkEdgeClipper*, bool newCtr, void* ctx), void* ctx);

private:
    SkPoint*        fCurrPoint;
    SkPath::Verb*   fCurrVerb;
    const bool      fCanCullToTheRight;

    enum {
        kMaxVerbs = 18,  // max curvature in X and Y split cubic into 9 pieces, * (line + cubic)
        kMaxPoints = 54  // 2 lines + 1 cubic require 6 points; times 9 pieces
    };
    SkPoint         fPoints[kMaxPoints];
    SkPath::Verb    fVerbs[kMaxVerbs];

    SK_API void clipMonoQuad(const SkPoint srcPts[3], const SkRect& clip);
    SK_API void clipMonoCubic(const SkPoint srcPts[4], const SkRect& clip);
    SK_API void appendLine(SkPoint p0, SkPoint p1);
    SK_API void appendVLine(SkScalar x, SkScalar y0, SkScalar y1, bool reverse);
    SK_API void appendQuad(const SkPoint pts[3], bool reverse);
    SK_API void appendCubic(const SkPoint pts[4], bool reverse);
};

#ifdef SK_DEBUG
    SK_API void sk_assert_monotonic_x(const SkPoint pts[], int count);
    SK_API void sk_assert_monotonic_y(const SkPoint pts[], int count);
#else
    #define sk_assert_monotonic_x(pts, count)
    #define sk_assert_monotonic_y(pts, count)
#endif

#endif
