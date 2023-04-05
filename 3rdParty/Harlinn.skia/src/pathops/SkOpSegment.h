/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkOpSegment_DEFINE
#define SkOpSegment_DEFINE

#include "src/core/SkArenaAlloc.h"
#include "src/pathops/SkOpAngle.h"
#include "src/pathops/SkOpSpan.h"
#include "src/pathops/SkPathOpsBounds.h"
#include "src/pathops/SkPathOpsCubic.h"
#include "src/pathops/SkPathOpsCurve.h"

struct SkDCurve;
class SkOpCoincidence;
class SkOpContour;
enum class SkOpRayDir;
struct SkOpRayHit;
class SkPathWriter;

class SkOpSegment {
public:
    bool operator<(const SkOpSegment& rh) const {
        return fBounds.fTop < rh.fBounds.fTop;
    }

    SK_API SkOpAngle* activeAngle(SkOpSpanBase* start, SkOpSpanBase** startPtr, SkOpSpanBase** endPtr,
                            bool* done);
    SK_API SkOpAngle* activeAngleInner(SkOpSpanBase* start, SkOpSpanBase** startPtr,
                                       SkOpSpanBase** endPtr, bool* done);
    SK_API SkOpAngle* activeAngleOther(SkOpSpanBase* start, SkOpSpanBase** startPtr,
                                       SkOpSpanBase** endPtr, bool* done);
    SK_API bool activeOp(SkOpSpanBase* start, SkOpSpanBase* end, int xorMiMask, int xorSuMask,
                  SkPathOp op);
    SK_API bool activeOp(int xorMiMask, int xorSuMask, SkOpSpanBase* start, SkOpSpanBase* end, SkPathOp op,
                  int* sumMiWinding, int* sumSuWinding);

    SK_API bool activeWinding(SkOpSpanBase* start, SkOpSpanBase* end);
    SK_API bool activeWinding(SkOpSpanBase* start, SkOpSpanBase* end, int* sumWinding);

    SkOpSegment* addConic(SkPoint pts[3], SkScalar weight, SkOpContour* parent) {
        init(pts, weight, parent, SkPath::kConic_Verb);
        SkDCurve curve;
        curve.fConic.set(pts, weight);
        curve.setConicBounds(pts, weight, 0, 1, &fBounds);
        return this;
    }

    SkOpSegment* addCubic(SkPoint pts[4], SkOpContour* parent) {
        init(pts, 1, parent, SkPath::kCubic_Verb);
        SkDCurve curve;
        curve.fCubic.set(pts);
        curve.setCubicBounds(pts, 1, 0, 1, &fBounds);
        return this;
    }

    SK_API bool addCurveTo(const SkOpSpanBase* start, const SkOpSpanBase* end, SkPathWriter* path) const;

    SkOpAngle* addEndSpan() {
        SkOpAngle* angle = this->globalState()->allocator()->make<SkOpAngle>();
        angle->set(&fTail, fTail.prev());
        fTail.setFromAngle(angle);
        return angle;
    }

    SK_API bool addExpanded(double newT, const SkOpSpanBase* test, bool* startOver);

    SkOpSegment* addLine(SkPoint pts[2], SkOpContour* parent) {
        SkASSERT(pts[0] != pts[1]);
        init(pts, 1, parent, SkPath::kLine_Verb);
        fBounds.setBounds(pts, 2);
        return this;
    }

    SK_API SkOpPtT* addMissing(double t, SkOpSegment* opp, bool* allExist);

    SkOpAngle* addStartSpan() {
        SkOpAngle* angle = this->globalState()->allocator()->make<SkOpAngle>();
        angle->set(&fHead, fHead.next());
        fHead.setToAngle(angle);
        return angle;
    }

    SK_API SkOpSegment* addQuad(SkPoint pts[3], SkOpContour* parent) {
        init(pts, 1, parent, SkPath::kQuad_Verb);
        SkDCurve curve;
        curve.fQuad.set(pts);
        curve.setQuadBounds(pts, 1, 0, 1, &fBounds);
        return this;
    }

    SK_API SkOpPtT* addT(double t);
    SK_API SkOpPtT* addT(double t, const SkPoint& pt);

    const SkPathOpsBounds& bounds() const {
        return fBounds;
    }

    void bumpCount() {
        ++fCount;
    }

    SK_API void calcAngles();
    SK_API SkOpSpanBase::Collapsed collapsed(double startT, double endT) const;
    SK_API static bool ComputeOneSum(const SkOpAngle* baseAngle, SkOpAngle* nextAngle,
                              SkOpAngle::IncludeType );
    SK_API static bool ComputeOneSumReverse(SkOpAngle* baseAngle, SkOpAngle* nextAngle,
                                     SkOpAngle::IncludeType );
    SK_API int computeSum(SkOpSpanBase* start, SkOpSpanBase* end, SkOpAngle::IncludeType includeType);

    SK_API void clearAll();
    SK_API void clearOne(SkOpSpan* span);
    SK_API static void ClearVisited(SkOpSpanBase* span);
    SK_API bool contains(double t) const;

    SkOpContour* contour() const {
        return fContour;
    }

    int count() const {
        return fCount;
    }

    SK_API void debugAddAngle(double startT, double endT);
#if DEBUG_COIN
    SK_API const SkOpPtT* debugAddT(double t, SkPathOpsDebug::GlitchLog* ) const;
#endif
    SK_API const SkOpAngle* debugAngle(int id) const;
#if DEBUG_ANGLE
    SK_API void debugCheckAngleCoin() const;
#endif
#if DEBUG_COIN
    SK_API void debugCheckHealth(SkPathOpsDebug::GlitchLog* ) const;
    SK_API void debugClearAll(SkPathOpsDebug::GlitchLog* glitches) const;
    SK_API void debugClearOne(const SkOpSpan* span, SkPathOpsDebug::GlitchLog* glitches) const;
#endif
    SK_API const SkOpCoincidence* debugCoincidence() const;
    SK_API SkOpContour* debugContour(int id) const;

    int debugID() const {
        return SkDEBUGRELEASE(fID, -1);
    }

    SK_API SkOpAngle* debugLastAngle();
#if DEBUG_COIN
    SK_API void debugMissingCoincidence(SkPathOpsDebug::GlitchLog* glitches) const;
    SK_API void debugMoveMultiples(SkPathOpsDebug::GlitchLog* glitches) const;
    SK_API void debugMoveNearby(SkPathOpsDebug::GlitchLog* glitches) const;
#endif
    SK_API const SkOpPtT* debugPtT(int id) const;
    SK_API void debugReset();
    SK_API const SkOpSegment* debugSegment(int id) const;

#if DEBUG_ACTIVE_SPANS
    SK_API void debugShowActiveSpans(SkString* str) const;
#endif
#if DEBUG_MARK_DONE
    SK_API void debugShowNewWinding(const char* fun, const SkOpSpan* span, int winding);
    SK_API void debugShowNewWinding(const char* fun, const SkOpSpan* span, int winding, int oppWinding);
#endif

    SK_API const SkOpSpanBase* debugSpan(int id) const;
    SK_API void debugValidate() const;

#if DEBUG_COINCIDENCE_ORDER
    SK_API void debugResetCoinT() const;
    SK_API void debugSetCoinT(int, SkScalar ) const;
#endif

#if DEBUG_COIN
    static void DebugClearVisited(const SkOpSpanBase* span);

    bool debugVisited() const {
        if (!fDebugVisited) {
            fDebugVisited = true;
            return false;
        }
        return true;
    }
#endif

#if DEBUG_ANGLE
    SK_API double distSq(double t, const SkOpAngle* opp) const;
#endif

    bool done() const {
        SkOPASSERT(fDoneCount <= fCount);
        return fDoneCount == fCount;
    }

    bool done(const SkOpAngle* angle) const {
        return angle->start()->starter(angle->end())->done();
    }

    SkDPoint dPtAtT(double mid) const {
        return (*CurveDPointAtT[fVerb])(fPts, fWeight, mid);
    }

    SkDVector dSlopeAtT(double mid) const {
        return (*CurveDSlopeAtT[fVerb])(fPts, fWeight, mid);
    }

    SK_API void dump() const;
    SK_API void dumpAll() const;
    SK_API void dumpAngles() const;
    SK_API void dumpCoin() const;
    SK_API void dumpPts(const char* prefix = "seg") const;
    SK_API void dumpPtsInner(const char* prefix = "seg") const;

    SK_API const SkOpPtT* existing(double t, const SkOpSegment* opp) const;
    SK_API SkOpSegment* findNextOp(SkTDArray<SkOpSpanBase*>* chase, SkOpSpanBase** nextStart,
                             SkOpSpanBase** nextEnd, bool* unsortable, bool* simple,
                             SkPathOp op, int xorMiMask, int xorSuMask);
    SK_API SkOpSegment* findNextWinding(SkTDArray<SkOpSpanBase*>* chase, SkOpSpanBase** nextStart,
                                  SkOpSpanBase** nextEnd, bool* unsortable);
    SK_API SkOpSegment* findNextXor(SkOpSpanBase** nextStart, SkOpSpanBase** nextEnd, bool* unsortable);
    SK_API SkOpSpan* findSortableTop(SkOpContour* );
    SK_API SkOpGlobalState* globalState() const;

    const SkOpSpan* head() const {
        return &fHead;
    }

    SkOpSpan* head() {
        return &fHead;
    }

    SK_API void init(SkPoint pts[], SkScalar weight, SkOpContour* parent, SkPath::Verb verb);

    SkOpSpan* insert(SkOpSpan* prev) {
        SkOpGlobalState* globalState = this->globalState();
        globalState->setAllocatedOpSpan();
        SkOpSpan* result = globalState->allocator()->make<SkOpSpan>();
        SkOpSpanBase* next = prev->next();
        result->setPrev(prev);
        prev->setNext(result);
        SkDEBUGCODE(result->ptT()->fT = 0);
        result->setNext(next);
        if (next) {
            next->setPrev(result);
        }
        return result;
    }

    SK_API bool isClose(double t, const SkOpSegment* opp) const;

    bool isHorizontal() const {
        return fBounds.fTop == fBounds.fBottom;
    }

    SkOpSegment* isSimple(SkOpSpanBase** end, int* step) const {
        return nextChase(end, step, nullptr, nullptr);
    }

    bool isVertical() const {
        return fBounds.fLeft == fBounds.fRight;
    }

    bool isVertical(SkOpSpanBase* start, SkOpSpanBase* end) const {
        return (*CurveIsVertical[fVerb])(fPts, fWeight, start->t(), end->t());
    }

    SK_API bool isXor() const;

    void joinEnds(SkOpSegment* start) {
        fTail.ptT()->addOpp(start->fHead.ptT(), start->fHead.ptT());
    }

    const SkPoint& lastPt() const {
        return fPts[SkPathOpsVerbToPoints(fVerb)];
    }

    SK_API void markAllDone();
    SK_API bool markAndChaseDone(SkOpSpanBase* start, SkOpSpanBase* end, SkOpSpanBase** found);
    SK_API bool markAndChaseWinding(SkOpSpanBase* start, SkOpSpanBase* end, int winding,
            SkOpSpanBase** lastPtr);
    SK_API bool markAndChaseWinding(SkOpSpanBase* start, SkOpSpanBase* end, int winding,
            int oppWinding, SkOpSpanBase** lastPtr);
    SK_API bool markAngle(int maxWinding, int sumWinding, const SkOpAngle* angle, SkOpSpanBase** result);
    SK_API bool markAngle(int maxWinding, int sumWinding, int oppMaxWinding, int oppSumWinding,
                         const SkOpAngle* angle, SkOpSpanBase** result);
    SK_API void markDone(SkOpSpan* );
    SK_API bool markWinding(SkOpSpan* , int winding);
    SK_API bool markWinding(SkOpSpan* , int winding, int oppWinding);
    SK_API bool match(const SkOpPtT* span, const SkOpSegment* parent, double t, const SkPoint& pt) const;
    SK_API bool missingCoincidence();
    SK_API bool moveMultiples();
    SK_API bool moveNearby();

    SkOpSegment* next() const {
        return fNext;
    }

    SK_API SkOpSegment* nextChase(SkOpSpanBase** , int* step, SkOpSpan** , SkOpSpanBase** last) const;
    SK_API bool operand() const;

    static int OppSign(const SkOpSpanBase* start, const SkOpSpanBase* end) {
        int result = start->t() < end->t() ? -start->upCast()->oppValue()
                : end->upCast()->oppValue();
        return result;
    }

    SK_API bool oppXor() const;

    const SkOpSegment* prev() const {
        return fPrev;
    }

    SkPoint ptAtT(double mid) const {
        return (*CurvePointAtT[fVerb])(fPts, fWeight, mid);
    }

    const SkPoint* pts() const {
        return fPts;
    }

    bool ptsDisjoint(const SkOpPtT& span, const SkOpPtT& test) const {
        SkASSERT(this == span.segment());
        SkASSERT(this == test.segment());
        return ptsDisjoint(span.fT, span.fPt, test.fT, test.fPt);
    }

    bool ptsDisjoint(const SkOpPtT& span, double t, const SkPoint& pt) const {
        SkASSERT(this == span.segment());
        return ptsDisjoint(span.fT, span.fPt, t, pt);
    }

    SK_API bool ptsDisjoint(double t1, const SkPoint& pt1, double t2, const SkPoint& pt2) const;

    SK_API void rayCheck(const SkOpRayHit& base, SkOpRayDir dir, SkOpRayHit** hits, SkArenaAlloc*);
    SK_API void release(const SkOpSpan* );

#if DEBUG_COIN
    void resetDebugVisited() const {
        fDebugVisited = false;
    }
#endif

    void resetVisited() {
        fVisited = false;
    }

    void setContour(SkOpContour* contour) {
        fContour = contour;
    }

    void setNext(SkOpSegment* next) {
        fNext = next;
    }

    void setPrev(SkOpSegment* prev) {
        fPrev = prev;
    }

    void setUpWinding(SkOpSpanBase* start, SkOpSpanBase* end, int* maxWinding, int* sumWinding) {
        int deltaSum = SpanSign(start, end);
        *maxWinding = *sumWinding;
        if (*sumWinding == SK_MinS32) {
          return;
        }
        *sumWinding -= deltaSum;
    }

    SK_API void setUpWindings(SkOpSpanBase* start, SkOpSpanBase* end, int* sumMiWinding,
                       int* maxWinding, int* sumWinding);
    SK_API void setUpWindings(SkOpSpanBase* start, SkOpSpanBase* end, int* sumMiWinding, int* sumSuWinding,
                       int* maxWinding, int* sumWinding, int* oppMaxWinding, int* oppSumWinding);
    SK_API bool sortAngles();
    SK_API bool spansNearby(const SkOpSpanBase* ref, const SkOpSpanBase* check, bool* found) const;

    static int SpanSign(const SkOpSpanBase* start, const SkOpSpanBase* end) {
        int result = start->t() < end->t() ? -start->upCast()->windValue()
                : end->upCast()->windValue();
        return result;
    }

    SkOpAngle* spanToAngle(SkOpSpanBase* start, SkOpSpanBase* end) {
        SkASSERT(start != end);
        return start->t() < end->t() ? start->upCast()->toAngle() : start->fromAngle();
    }

    SK_API bool subDivide(const SkOpSpanBase* start, const SkOpSpanBase* end, SkDCurve* result) const;

    const SkOpSpanBase* tail() const {
        return &fTail;
    }

    SkOpSpanBase* tail() {
        return &fTail;
    }

    SK_API bool testForCoincidence(const SkOpPtT* priorPtT, const SkOpPtT* ptT, const SkOpSpanBase* prior,
            const SkOpSpanBase* spanBase, const SkOpSegment* opp) const;

    SK_API SkOpSpan* undoneSpan();
    SK_API int updateOppWinding(const SkOpSpanBase* start, const SkOpSpanBase* end) const;
    SK_API int updateOppWinding(const SkOpAngle* angle) const;
    SK_API int updateOppWindingReverse(const SkOpAngle* angle) const;
    SK_API int updateWinding(SkOpSpanBase* start, SkOpSpanBase* end);
    SK_API int updateWinding(SkOpAngle* angle);
    SK_API int updateWindingReverse(const SkOpAngle* angle);

    SK_API static bool UseInnerWinding(int outerWinding, int innerWinding);

    SkPath::Verb verb() const {
        return fVerb;
    }

    // look for two different spans that point to the same opposite segment
    bool visited() {
        if (!fVisited) {
            fVisited = true;
            return false;
        }
        return true;
    }

    SkScalar weight() const {
        return fWeight;
    }

    SK_API SkOpSpan* windingSpanAtT(double tHit);
    SK_API int windSum(const SkOpAngle* angle) const;

private:
    SkOpSpan fHead;  // the head span always has its t set to zero
    SkOpSpanBase fTail;  // the tail span always has its t set to one
    SkOpContour* fContour;
    SkOpSegment* fNext;  // forward-only linked list used by contour to walk the segments
    const SkOpSegment* fPrev;
    SkPoint* fPts;  // pointer into array of points owned by edge builder that may be tweaked
    SkPathOpsBounds fBounds;  // tight bounds
    SkScalar fWeight;
    int fCount;  // number of spans (one for a non-intersecting segment)
    int fDoneCount;  // number of processed spans (zero initially)
    SkPath::Verb fVerb;
    bool fVisited;  // used by missing coincidence check
#if DEBUG_COIN
    mutable bool fDebugVisited;  // used by debug missing coincidence check
#endif
#if DEBUG_COINCIDENCE_ORDER
    mutable int fDebugBaseIndex;
    mutable SkScalar fDebugBaseMin;  // if > 0, the 1st t value in this seg vis-a-vis the ref seg
    mutable SkScalar fDebugBaseMax;
    mutable int fDebugLastIndex;
    mutable SkScalar fDebugLastMin;  // if > 0, the last t -- next t val - base has same sign
    mutable SkScalar fDebugLastMax;
#endif
    SkDEBUGCODE(int fID);
};

#endif
