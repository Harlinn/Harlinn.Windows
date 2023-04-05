/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkOpAngle_DEFINED
#define SkOpAngle_DEFINED

#include "src/pathops/SkLineParameters.h"
#include "src/pathops/SkPathOpsCurve.h"
#if DEBUG_ANGLE
#include <skia/core/SkString.h>
#endif

class SkOpContour;
class SkOpPtT;
class SkOpSegment;
class SkOpSpanBase;
class SkOpSpan;

class SkOpAngle {
public:
    enum IncludeType {
        kUnaryWinding,
        kUnaryXor,
        kBinarySingle,
        kBinaryOpp,
    };

    SK_API const SkOpAngle* debugAngle(int id) const;
    SK_API const SkOpCoincidence* debugCoincidence() const;
    SK_API SkOpContour* debugContour(int id) const;

    int debugID() const {
        return SkDEBUGRELEASE(fID, -1);
    }

#if DEBUG_SORT
    SK_API void debugLoop() const;
#endif

#if DEBUG_ANGLE
    SK_API bool debugCheckCoincidence() const { return fCheckCoincidence; }
    SK_API void debugCheckNearCoincidence() const;
    SK_API SkString debugPart() const;
#endif
    SK_API const SkOpPtT* debugPtT(int id) const;
    SK_API const SkOpSegment* debugSegment(int id) const;
    SK_API int debugSign() const;
    SK_API const SkOpSpanBase* debugSpan(int id) const;
    SK_API void debugValidate() const;
    SK_API void debugValidateNext() const;  // in debug builds, verify that angle loop is uncorrupted
    SK_API double distEndRatio(double dist) const;
    // available to testing only
    SK_API void dump() const;
    SK_API void dumpCurves() const;
    SK_API void dumpLoop() const;
    SK_API void dumpOne(bool functionHeader) const;
    SK_API void dumpTo(const SkOpSegment* fromSeg, const SkOpAngle* ) const;
    SK_API void dumpTest() const;

    SkOpSpanBase* end() const {
        return fEnd;
    }

    SK_API bool insert(SkOpAngle* );
    SK_API SkOpSpanBase* lastMarked() const;
    SK_API bool loopContains(const SkOpAngle* ) const;
    SK_API int loopCount() const;

    SkOpAngle* next() const {
        return fNext;
    }

    SK_API SkOpAngle* previous() const;
    SK_API SkOpSegment* segment() const;
    SK_API void set(SkOpSpanBase* start, SkOpSpanBase* end);

    void setLastMarked(SkOpSpanBase* marked) {
        fLastMarked = marked;
    }

    SkOpSpanBase* start() const {
        return fStart;
    }

    SK_API SkOpSpan* starter();

    bool tangentsAmbiguous() const {
        return fTangentsAmbiguous;
    }

    bool unorderable() const {
        return fUnorderable;
    }

private:
    SK_API bool after(SkOpAngle* test);
    SK_API void alignmentSameSide(const SkOpAngle* test, int* order) const;
    SK_API bool checkCrossesZero() const;
    SK_API bool checkParallel(SkOpAngle* );
    SK_API bool computeSector();
    SK_API int convexHullOverlaps(const SkOpAngle* );
    SK_API bool endToSide(const SkOpAngle* rh, bool* inside) const;
    SK_API bool endsIntersect(SkOpAngle* );
    SK_API int findSector(SkPath::Verb verb, double x, double y) const;
    SK_API SkOpGlobalState* globalState() const;
    SK_API int lineOnOneSide(const SkDPoint& origin, const SkDVector& line, const SkOpAngle* test,
                      bool useOriginal) const;
    SK_API int lineOnOneSide(const SkOpAngle* test, bool useOriginal);
    SK_API int linesOnOriginalSide(const SkOpAngle* test);
    SK_API bool merge(SkOpAngle* );
    SK_API double midT() const;
    SK_API bool midToSide(const SkOpAngle* rh, bool* inside) const;
    SK_API bool oppositePlanes(const SkOpAngle* rh) const;
    SK_API int orderable(SkOpAngle* rh);  // false == this < rh ; true == this > rh; -1 == unorderable
    SK_API void setSector();
    SK_API void setSpans();
    SK_API bool tangentsDiverge(const SkOpAngle* rh, double s0xt0);

    SkDCurve fOriginalCurvePart;  // the curve from start to end
    SkDCurveSweep fPart;  // the curve from start to end offset as needed
    double fSide;
    SkLineParameters fTangentHalf;  // used only to sort a pair of lines or line-like sections
    SkOpAngle* fNext;
    SkOpSpanBase* fLastMarked;
    SkOpSpanBase* fStart;
    SkOpSpanBase* fEnd;
    SkOpSpanBase* fComputedEnd;
    int fSectorMask;
    int8_t fSectorStart;  // in 32nds of a circle
    int8_t fSectorEnd;
    bool fUnorderable;
    bool fComputeSector;
    bool fComputedSector;
    bool fCheckCoincidence;
    bool fTangentsAmbiguous;
    SkDEBUGCODE(int fID);

    friend class PathOpsAngleTester;
};



#endif
