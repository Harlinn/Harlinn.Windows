/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkOpCoincidence_DEFINED
#define SkOpCoincidence_DEFINED

#include <skia/private/SkTDArray.h>
#include "src/core/SkArenaAlloc.h"
#include "src/pathops/SkOpSpan.h"
#include "src/pathops/SkPathOpsTypes.h"

class SkOpPtT;
class SkOpSpanBase;

class SkCoincidentSpans {
public:
    SK_API const SkOpPtT* coinPtTEnd() const;
    SK_API const SkOpPtT* coinPtTStart() const;

    // These return non-const pointers so that, as copies, they can be added
    // to a new span pair
    SkOpPtT* coinPtTEndWritable() const { return const_cast<SkOpPtT*>(fCoinPtTEnd); }
    SkOpPtT* coinPtTStartWritable() const { return const_cast<SkOpPtT*>(fCoinPtTStart); }

    SK_API bool collapsed(const SkOpPtT* ) const;
    SK_API bool contains(const SkOpPtT* s, const SkOpPtT* e) const;
    SK_API void correctEnds();
    SK_API void correctOneEnd(const SkOpPtT* (SkCoincidentSpans::* getEnd)() const,
                       void (SkCoincidentSpans::* setEnd)(const SkOpPtT* ptT) );

#if DEBUG_COIN
    SK_API void debugCorrectEnds(SkPathOpsDebug::GlitchLog* log) const;
    SK_API void debugCorrectOneEnd(SkPathOpsDebug::GlitchLog* log,
                            const SkOpPtT* (SkCoincidentSpans::* getEnd)() const,
                            void (SkCoincidentSpans::* setEnd)(const SkOpPtT* ptT) const) const;
    SK_API bool debugExpand(SkPathOpsDebug::GlitchLog* log) const;
#endif

    const char* debugID() const {
#if DEBUG_COIN
        return fGlobalState->debugCoinDictEntry().fFunctionName;
#else
        return nullptr;
#endif
    }

    SK_API void debugShow() const;
#ifdef SK_DEBUG
    SK_API void debugStartCheck(const SkOpSpanBase* outer, const SkOpSpanBase* over,
            const SkOpGlobalState* debugState) const;
#endif
    SK_API void dump() const;
    SK_API bool expand();
    SK_API bool extend(const SkOpPtT* coinPtTStart, const SkOpPtT* coinPtTEnd,
                const SkOpPtT* oppPtTStart, const SkOpPtT* oppPtTEnd);
    bool flipped() const { return fOppPtTStart->fT > fOppPtTEnd->fT; }
    SkDEBUGCODE(SkOpGlobalState* globalState() { return fGlobalState; })

    void init(SkDEBUGCODE(SkOpGlobalState* globalState)) {
        sk_bzero(this, sizeof(*this));
        SkDEBUGCODE(fGlobalState = globalState);
    }

    SkCoincidentSpans* next() { return fNext; }
    const SkCoincidentSpans* next() const { return fNext; }
    SkCoincidentSpans** nextPtr() { return &fNext; }
    SK_API const SkOpPtT* oppPtTStart() const;
    SK_API const SkOpPtT* oppPtTEnd() const;
    // These return non-const pointers so that, as copies, they can be added
    // to a new span pair
    SkOpPtT* oppPtTStartWritable() const { return const_cast<SkOpPtT*>(fOppPtTStart); }
    SkOpPtT* oppPtTEndWritable() const { return const_cast<SkOpPtT*>(fOppPtTEnd); }
    SK_API bool ordered(bool* result) const;

    SK_API void set(SkCoincidentSpans* next, const SkOpPtT* coinPtTStart, const SkOpPtT* coinPtTEnd,
            const SkOpPtT* oppPtTStart, const SkOpPtT* oppPtTEnd);

    void setCoinPtTEnd(const SkOpPtT* ptT) {
        SkOPASSERT(ptT == ptT->span()->ptT());
        SkOPASSERT(!fCoinPtTStart || ptT->fT != fCoinPtTStart->fT);
        SkASSERT(!fCoinPtTStart || fCoinPtTStart->segment() == ptT->segment());
        fCoinPtTEnd = ptT;
        ptT->setCoincident();
    }

    void setCoinPtTStart(const SkOpPtT* ptT) {
        SkOPASSERT(ptT == ptT->span()->ptT());
        SkOPASSERT(!fCoinPtTEnd || ptT->fT != fCoinPtTEnd->fT);
        SkASSERT(!fCoinPtTEnd || fCoinPtTEnd->segment() == ptT->segment());
        fCoinPtTStart = ptT;
        ptT->setCoincident();
    }

    void setEnds(const SkOpPtT* coinPtTEnd, const SkOpPtT* oppPtTEnd) {
        this->setCoinPtTEnd(coinPtTEnd);
        this->setOppPtTEnd(oppPtTEnd);
    }

    void setOppPtTEnd(const SkOpPtT* ptT) {
        SkOPASSERT(ptT == ptT->span()->ptT());
        SkOPASSERT(!fOppPtTStart || ptT->fT != fOppPtTStart->fT);
        SkASSERT(!fOppPtTStart || fOppPtTStart->segment() == ptT->segment());
        fOppPtTEnd = ptT;
        ptT->setCoincident();
    }

    void setOppPtTStart(const SkOpPtT* ptT) {
        SkOPASSERT(ptT == ptT->span()->ptT());
        SkOPASSERT(!fOppPtTEnd || ptT->fT != fOppPtTEnd->fT);
        SkASSERT(!fOppPtTEnd || fOppPtTEnd->segment() == ptT->segment());
        fOppPtTStart = ptT;
        ptT->setCoincident();
    }

    void setStarts(const SkOpPtT* coinPtTStart, const SkOpPtT* oppPtTStart) {
        this->setCoinPtTStart(coinPtTStart);
        this->setOppPtTStart(oppPtTStart);
    }

    void setNext(SkCoincidentSpans* next) { fNext = next; }

private:
    SkCoincidentSpans* fNext;
    const SkOpPtT* fCoinPtTStart;
    const SkOpPtT* fCoinPtTEnd;
    const SkOpPtT* fOppPtTStart;
    const SkOpPtT* fOppPtTEnd;
    SkDEBUGCODE(SkOpGlobalState* fGlobalState);
};

class SkOpCoincidence {
public:
    SkOpCoincidence(SkOpGlobalState* globalState)
        : fHead(nullptr)
        , fTop(nullptr)
        , fGlobalState(globalState)
        , fContinue(false)
        , fSpanDeleted(false)
        , fPtAllocated(false)
        , fCoinExtended(false)
        , fSpanMerged(false) {
        globalState->setCoincidence(this);
    }

    SK_API void add(SkOpPtT* coinPtTStart, SkOpPtT* coinPtTEnd, SkOpPtT* oppPtTStart,
             SkOpPtT* oppPtTEnd);
    SK_API bool addEndMovedSpans(DEBUG_COIN_DECLARE_ONLY_PARAMS());
    SK_API bool addExpanded(DEBUG_COIN_DECLARE_ONLY_PARAMS());
    SK_API bool addMissing(bool* added  DEBUG_COIN_DECLARE_PARAMS());
    SK_API bool apply(DEBUG_COIN_DECLARE_ONLY_PARAMS());
    SK_API bool contains(const SkOpPtT* coinPtTStart, const SkOpPtT* coinPtTEnd,
                  const SkOpPtT* oppPtTStart, const SkOpPtT* oppPtTEnd) const;
    SK_API void correctEnds(DEBUG_COIN_DECLARE_ONLY_PARAMS());

#if DEBUG_COIN
    SK_API void debugAddEndMovedSpans(SkPathOpsDebug::GlitchLog* log) const;
    SK_API void debugAddExpanded(SkPathOpsDebug::GlitchLog* ) const;
    SK_API void debugAddMissing(SkPathOpsDebug::GlitchLog* , bool* added) const;
    SK_API void debugAddOrOverlap(SkPathOpsDebug::GlitchLog* log,
                           const SkOpSegment* coinSeg, const SkOpSegment* oppSeg,
                           double coinTs, double coinTe, double oppTs, double oppTe,
                           bool* added) const;
#endif

    const SkOpAngle* debugAngle(int id) const {
        return SkDEBUGRELEASE(fGlobalState->debugAngle(id), nullptr);
    }

    SK_API void debugCheckBetween() const;

#if DEBUG_COIN
    SK_API void debugCheckValid(SkPathOpsDebug::GlitchLog* log) const;
#endif

    SkOpContour* debugContour(int id) const {
        return SkDEBUGRELEASE(fGlobalState->debugContour(id), nullptr);
    }

#if DEBUG_COIN
    SK_API void debugCorrectEnds(SkPathOpsDebug::GlitchLog* log) const;
    SK_API bool debugExpand(SkPathOpsDebug::GlitchLog* ) const;
    SK_API void debugMark(SkPathOpsDebug::GlitchLog* ) const;
    SK_API void debugMarkCollapsed(SkPathOpsDebug::GlitchLog* ,
                            const SkCoincidentSpans* coin, const SkOpPtT* test) const;
    SK_API void debugMarkCollapsed(SkPathOpsDebug::GlitchLog* , const SkOpPtT* test) const;
#endif

    const SkOpPtT* debugPtT(int id) const {
        return SkDEBUGRELEASE(fGlobalState->debugPtT(id), nullptr);
    }

    const SkOpSegment* debugSegment(int id) const {
        return SkDEBUGRELEASE(fGlobalState->debugSegment(id), nullptr);
    }

#if DEBUG_COIN
    SK_API void debugRelease(SkPathOpsDebug::GlitchLog* , const SkCoincidentSpans* ,
                      const SkCoincidentSpans* ) const;
    SK_API void debugRelease(SkPathOpsDebug::GlitchLog* , const SkOpSegment* ) const;
#endif
    SK_API void debugShowCoincidence() const;

    const SkOpSpanBase* debugSpan(int id) const {
        return SkDEBUGRELEASE(fGlobalState->debugSpan(id), nullptr);
    }

    SK_API void debugValidate() const;
    SK_API void dump() const;
    SK_API bool expand(DEBUG_COIN_DECLARE_ONLY_PARAMS());
    SK_API bool extend(const SkOpPtT* coinPtTStart, const SkOpPtT* coinPtTEnd, const SkOpPtT* oppPtTStart,
                const SkOpPtT* oppPtTEnd);
    SK_API bool findOverlaps(SkOpCoincidence*  DEBUG_COIN_DECLARE_PARAMS()) const;
    SK_API void fixUp(SkOpPtT* deleted, const SkOpPtT* kept);

    SkOpGlobalState* globalState() {
        return fGlobalState;
    }

    const SkOpGlobalState* globalState() const {
        return fGlobalState;
    }

    bool isEmpty() const {
        return !fHead && !fTop;
    }

    SK_API bool mark(DEBUG_COIN_DECLARE_ONLY_PARAMS());
    SK_API void markCollapsed(SkOpPtT* );

    static bool Ordered(const SkOpPtT* coinPtTStart, const SkOpPtT* oppPtTStart) {
      return Ordered(coinPtTStart->segment(), oppPtTStart->segment());
    }

    SK_API static bool Ordered(const SkOpSegment* coin, const SkOpSegment* opp);
    SK_API void release(const SkOpSegment* );
    SK_API void releaseDeleted();

private:
    void add(const SkOpPtT* coinPtTStart, const SkOpPtT* coinPtTEnd, const SkOpPtT* oppPtTStart,
             const SkOpPtT* oppPtTEnd) {
        this->add(const_cast<SkOpPtT*>(coinPtTStart), const_cast<SkOpPtT*>(coinPtTEnd),
            const_cast<SkOpPtT*>(oppPtTStart), const_cast<SkOpPtT*>(oppPtTEnd));
    }

    SK_API bool addEndMovedSpans(const SkOpSpan* base, const SkOpSpanBase* testSpan);
    SK_API bool addEndMovedSpans(const SkOpPtT* ptT);

    SK_API bool addIfMissing(const SkOpPtT* over1s, const SkOpPtT* over2s,
                      double tStart, double tEnd, SkOpSegment* coinSeg, SkOpSegment* oppSeg,
                      bool* added
                      SkDEBUGPARAMS(const SkOpPtT* over1e) SkDEBUGPARAMS(const SkOpPtT* over2e));
    SK_API bool addOrOverlap(SkOpSegment* coinSeg, SkOpSegment* oppSeg,
                      double coinTs, double coinTe, double oppTs, double oppTe, bool* added);
    SK_API bool addOverlap(const SkOpSegment* seg1, const SkOpSegment* seg1o,
                    const SkOpSegment* seg2, const SkOpSegment* seg2o,
                    const SkOpPtT* overS, const SkOpPtT* overE);
    SK_API bool checkOverlap(SkCoincidentSpans* check,
                      const SkOpSegment* coinSeg, const SkOpSegment* oppSeg,
                      double coinTs, double coinTe, double oppTs, double oppTe,
                      SkTDArray<SkCoincidentSpans*>* overlaps) const;
    SK_API bool contains(const SkOpSegment* seg, const SkOpSegment* opp, double oppT) const;
    SK_API bool contains(const SkCoincidentSpans* coin, const SkOpSegment* seg,
                  const SkOpSegment* opp, double oppT) const;
#if DEBUG_COIN
    SK_API void debugAddIfMissing(SkPathOpsDebug::GlitchLog* ,
                           const SkCoincidentSpans* outer, const SkOpPtT* over1s,
                           const SkOpPtT* over1e) const;
    SK_API void debugAddIfMissing(SkPathOpsDebug::GlitchLog* ,
                           const SkOpPtT* over1s, const SkOpPtT* over2s,
                           double tStart, double tEnd,
                           const SkOpSegment* coinSeg, const SkOpSegment* oppSeg, bool* added,
                           const SkOpPtT* over1e, const SkOpPtT* over2e) const;
    SK_API void debugAddEndMovedSpans(SkPathOpsDebug::GlitchLog* ,
                               const SkOpSpan* base, const SkOpSpanBase* testSpan) const;
    SK_API void debugAddEndMovedSpans(SkPathOpsDebug::GlitchLog* ,
                               const SkOpPtT* ptT) const;
#endif
    SK_API void fixUp(SkCoincidentSpans* coin, SkOpPtT* deleted, const SkOpPtT* kept);
    SK_API void markCollapsed(SkCoincidentSpans* head, SkOpPtT* test);
    SK_API bool overlap(const SkOpPtT* coinStart1, const SkOpPtT* coinEnd1,
                 const SkOpPtT* coinStart2, const SkOpPtT* coinEnd2,
                 double* overS, double* overE) const;
    SK_API bool release(SkCoincidentSpans* coin, SkCoincidentSpans* );
    SK_API void releaseDeleted(SkCoincidentSpans* );
    SK_API void restoreHead();
    // return coinPtT->segment()->t mapped from overS->fT <= t <= overE->fT
    SK_API static double TRange(const SkOpPtT* overS, double t, const SkOpSegment* coinPtT
                         SkDEBUGPARAMS(const SkOpPtT* overE));

    SkCoincidentSpans* fHead;
    SkCoincidentSpans* fTop;
    SkOpGlobalState* fGlobalState;
    bool fContinue;
    bool fSpanDeleted;
    bool fPtAllocated;
    bool fCoinExtended;
    bool fSpanMerged;
};

#endif
