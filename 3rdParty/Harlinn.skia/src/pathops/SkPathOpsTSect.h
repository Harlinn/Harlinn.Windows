/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkPathOpsTSect_DEFINED
#define SkPathOpsTSect_DEFINED

#include <skia/private/SkMacros.h>
#include "src/core/SkArenaAlloc.h"
#include "src/pathops/SkIntersections.h"
#include "src/pathops/SkPathOpsBounds.h"
#include "src/pathops/SkPathOpsRect.h"
#include "src/pathops/SkPathOpsTCurve.h"

#include <utility>

#ifdef SK_DEBUG
typedef uint8_t SkOpDebugBool;
#else
typedef bool SkOpDebugBool;
#endif

static inline bool SkDoubleIsNaN(double x) {
    return x != x;
}

class SkTCoincident {
public:
    SkTCoincident() {
        this->init();
    }

    void debugInit() {
#ifdef SK_DEBUG
        this->fPerpPt.fX = this->fPerpPt.fY = SK_ScalarNaN;
        this->fPerpT = SK_ScalarNaN;
        this->fMatch = 0xFF;
#endif
    }

    SK_API char dumpIsCoincidentStr() const;
    SK_API void dump() const;

    bool isMatch() const {
        SkASSERT(!!fMatch == fMatch);
        return SkToBool(fMatch);
    }

    void init() {
        fPerpT = -1;
        fMatch = false;
        fPerpPt.fX = fPerpPt.fY = SK_ScalarNaN;
    }

    void markCoincident() {
        if (!fMatch) {
            fPerpT = -1;
        }
        fMatch = true;
    }

    const SkDPoint& perpPt() const {
        return fPerpPt;
    }

    double perpT() const {
        return fPerpT;
    }

    SK_API void setPerp(const SkTCurve& c1, double t, const SkDPoint& cPt, const SkTCurve& );

private:
    SkDPoint fPerpPt;
    double fPerpT;  // perpendicular intersection on opposite curve
    SkOpDebugBool fMatch;
};

class SkTSect;
class SkTSpan;

struct SkTSpanBounded {
    SkTSpan* fBounded;
    SkTSpanBounded* fNext;
};

class SkTSpan {
public:
    SkTSpan(const SkTCurve& curve, SkArenaAlloc& heap) {
        fPart = curve.make(heap);
    }

    SK_API void addBounded(SkTSpan* , SkArenaAlloc* );
    SK_API double closestBoundedT(const SkDPoint& pt) const;
    SK_API bool contains(double t) const;

    void debugInit(const SkTCurve& curve, SkArenaAlloc& heap) {
#ifdef SK_DEBUG
        SkTCurve* fake = curve.make(heap);
        fake->debugInit();
        init(*fake);
        initBounds(*fake);
        fCoinStart.init();
        fCoinEnd.init();
#endif
    }

    SK_API const SkTSect* debugOpp() const;

#ifdef SK_DEBUG
    void debugSetGlobalState(SkOpGlobalState* state) {
        fDebugGlobalState = state;
    }

    SK_API const SkTSpan* debugSpan(int ) const;
    SK_API const SkTSpan* debugT(double t) const;
    SK_API bool debugIsBefore(const SkTSpan* span) const;
#endif
    SK_API void dump() const;
    SK_API void dumpAll() const;
    SK_API void dumpBounded(int id) const;
    SK_API void dumpBounds() const;
    SK_API void dumpCoin() const;

    double endT() const {
        return fEndT;
    }

    SK_API SkTSpan* findOppSpan(const SkTSpan* opp) const;

    SkTSpan* findOppT(double t) const {
        SkTSpan* result = oppT(t);
        SkOPASSERT(result);
        return result;
    }

    SK_API SkDEBUGCODE(SkOpGlobalState* globalState() const { return fDebugGlobalState; })

    bool hasOppT(double t) const {
        return SkToBool(oppT(t));
    }

    SK_API int hullsIntersect(SkTSpan* span, bool* start, bool* oppStart);
    SK_API void init(const SkTCurve& );
    SK_API bool initBounds(const SkTCurve& );

    bool isBounded() const {
        return fBounded != nullptr;
    }

    SK_API bool linearsIntersect(SkTSpan* span);
    SK_API double linearT(const SkDPoint& ) const;

    void markCoincident() {
        fCoinStart.markCoincident();
        fCoinEnd.markCoincident();
    }

    const SkTSpan* next() const {
        return fNext;
    }

    bool onlyEndPointsInCommon(const SkTSpan* opp, bool* start,
            bool* oppStart, bool* ptsInCommon);

    const SkTCurve& part() const {
        return *fPart;
    }

    int pointCount() const {
        return fPart->pointCount();
    }

    const SkDPoint& pointFirst() const {
        return (*fPart)[0];
    }

    const SkDPoint& pointLast() const {
        return (*fPart)[fPart->pointLast()];
    }

    SK_API bool removeAllBounded();
    SK_API bool removeBounded(const SkTSpan* opp);

    void reset() {
        fBounded = nullptr;
    }

    void resetBounds(const SkTCurve& curve) {
        fIsLinear = fIsLine = false;
        initBounds(curve);
    }

    bool split(SkTSpan* work, SkArenaAlloc* heap) {
        return splitAt(work, (work->fStartT + work->fEndT) * 0.5, heap);
    }

    SK_API bool splitAt(SkTSpan* work, double t, SkArenaAlloc* heap);

    double startT() const {
        return fStartT;
    }

private:

    // implementation is for testing only
    int debugID() const {
        return PATH_OPS_DEBUG_T_SECT_RELEASE(fID, -1);
    }

    SK_API void dumpID() const;

    SK_API int hullCheck(const SkTSpan* opp, bool* start, bool* oppStart);
    SK_API int linearIntersects(const SkTCurve& ) const;
    SK_API SkTSpan* oppT(double t) const;

    SK_API void validate() const;
    SK_API void validateBounded() const;
    SK_API void validatePerpT(double oppT) const;
    SK_API void validatePerpPt(double t, const SkDPoint& ) const;

    SkTCurve* fPart;
    SkTCoincident fCoinStart;
    SkTCoincident fCoinEnd;
    SkTSpanBounded* fBounded;
    SkTSpan* fPrev;
    SkTSpan* fNext;
    SkDRect fBounds;
    double fStartT;
    double fEndT;
    double fBoundsMax;
    SkOpDebugBool fCollapsed;
    SkOpDebugBool fHasPerp;
    SkOpDebugBool fIsLinear;
    SkOpDebugBool fIsLine;
    SkOpDebugBool fDeleted;
    SkDEBUGCODE(SkOpGlobalState* fDebugGlobalState);
    SkDEBUGCODE(SkTSect* fDebugSect);
    PATH_OPS_DEBUG_T_SECT_CODE(int fID);
    friend class SkTSect;
};

class SkTSect {
public:
    SkTSect(const SkTCurve& c
                             SkDEBUGPARAMS(SkOpGlobalState* ) PATH_OPS_DEBUG_T_SECT_PARAMS(int id));
    SK_API static void BinarySearch(SkTSect* sect1, SkTSect* sect2,
            SkIntersections* intersections);

    SkDEBUGCODE(SkOpGlobalState* globalState() { return fDebugGlobalState; })
        SK_API bool hasBounded(const SkTSpan* ) const;

    const SkTSect* debugOpp() const {
        return SkDEBUGRELEASE(fOppSect, nullptr);
    }

#ifdef SK_DEBUG
    SK_API const SkTSpan* debugSpan(int id) const;
    SK_API const SkTSpan* debugT(double t) const;
#endif
    SK_API void dump() const;
    SK_API void dumpBoth(SkTSect* ) const;
    SK_API void dumpBounded(int id) const;
    SK_API void dumpBounds() const;
    SK_API void dumpCoin() const;
    SK_API void dumpCoinCurves() const;
    SK_API void dumpCurves() const;

private:
    enum {
        kZeroS1Set = 1,
        kOneS1Set = 2,
        kZeroS2Set = 4,
        kOneS2Set = 8
    };

    SK_API SkTSpan* addFollowing(SkTSpan* prior);
    SK_API void addForPerp(SkTSpan* span, double t);
    SK_API SkTSpan* addOne();

    SkTSpan* addSplitAt(SkTSpan* span, double t) {
        SkTSpan* result = this->addOne();
        SkDEBUGCODE(result->debugSetGlobalState(this->globalState()));
        result->splitAt(span, t, &fHeap);
        result->initBounds(fCurve);
        span->initBounds(fCurve);
        return result;
    }

    SK_API bool binarySearchCoin(SkTSect* , double tStart, double tStep, double* t,
                          double* oppT, SkTSpan** oppFirst);
    SK_API SkTSpan* boundsMax();
    SK_API bool coincidentCheck(SkTSect* sect2);
    SK_API void coincidentForce(SkTSect* sect2, double start1s, double start1e);
    SK_API bool coincidentHasT(double t);
    SK_API int collapsed() const;
    SK_API void computePerpendiculars(SkTSect* sect2, SkTSpan* first,
                               SkTSpan* last);
    SK_API int countConsecutiveSpans(SkTSpan* first,
                              SkTSpan** last) const;

    int debugID() const {
        return PATH_OPS_DEBUG_T_SECT_RELEASE(fID, -1);
    }

    SK_API bool deleteEmptySpans();
    SK_API void dumpCommon(const SkTSpan* ) const;
    SK_API void dumpCommonCurves(const SkTSpan* ) const;
    SK_API static int EndsEqual(const SkTSect* sect1, const SkTSect* sect2,
                         SkIntersections* );
    SK_API bool extractCoincident(SkTSect* sect2, SkTSpan* first,
                           SkTSpan* last, SkTSpan** result);
    SK_API SkTSpan* findCoincidentRun(SkTSpan* first, SkTSpan** lastPtr);
    SK_API int intersects(SkTSpan* span, SkTSect* opp,
                   SkTSpan* oppSpan, int* oppResult);
    SK_API bool isParallel(const SkDLine& thisLine, const SkTSect* opp) const;
    SK_API int linesIntersect(SkTSpan* span, SkTSect* opp,
                       SkTSpan* oppSpan, SkIntersections* );
    SK_API bool markSpanGone(SkTSpan* span);
    SK_API bool matchedDirection(double t, const SkTSect* sect2, double t2) const;
    SK_API void matchedDirCheck(double t, const SkTSect* sect2, double t2,
                         bool* calcMatched, bool* oppMatched) const;
    SK_API void mergeCoincidence(SkTSect* sect2);

    const SkDPoint& pointLast() const {
        return fCurve[fCurve.pointLast()];
    }

    SK_API SkTSpan* prev(SkTSpan* ) const;
    SK_API bool removeByPerpendicular(SkTSect* opp);
    SK_API void recoverCollapsed();
    SK_API bool removeCoincident(SkTSpan* span, bool isBetween);
    SK_API void removeAllBut(const SkTSpan* keep, SkTSpan* span,
                      SkTSect* opp);
    SK_API bool removeSpan(SkTSpan* span);
    SK_API void removeSpanRange(SkTSpan* first, SkTSpan* last);
    SK_API bool removeSpans(SkTSpan* span, SkTSect* opp);
    SK_API void removedEndCheck(SkTSpan* span);

    void resetRemovedEnds() {
        fRemovedStartT = fRemovedEndT = false;
    }

    SK_API SkTSpan* spanAtT(double t, SkTSpan** priorSpan);
    SK_API SkTSpan* tail();
    SK_API bool trim(SkTSpan* span, SkTSect* opp);
    SK_API bool unlinkSpan(SkTSpan* span);
    SK_API bool updateBounded(SkTSpan* first, SkTSpan* last,
                       SkTSpan* oppFirst);
    SK_API void validate() const;
    SK_API void validateBounded() const;

    const SkTCurve& fCurve;
    SkSTArenaAlloc<1024> fHeap;
    SkTSpan* fHead;
    SkTSpan* fCoincident;
    SkTSpan* fDeleted;
    int fActiveCount;
    bool fRemovedStartT;
    bool fRemovedEndT;
    bool fHung;
    SkDEBUGCODE(SkOpGlobalState* fDebugGlobalState);
    SkDEBUGCODE(SkTSect* fOppSect);
    PATH_OPS_DEBUG_T_SECT_CODE(int fID);
    PATH_OPS_DEBUG_T_SECT_CODE(int fDebugCount);
#if DEBUG_T_SECT
    int fDebugAllocatedCount;
#endif
    friend class SkTSpan;
};

#endif
