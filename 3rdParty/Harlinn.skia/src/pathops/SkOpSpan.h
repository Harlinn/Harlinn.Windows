/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkOpSpan_DEFINED
#define SkOpSpan_DEFINED

#include <skia/core/SkPoint.h>
#include "src/pathops/SkPathOpsDebug.h"
#include "src/pathops/SkPathOpsTypes.h"

class SkArenaAlloc;
class SkOpAngle;
class SkOpContour;
class SkOpGlobalState;
class SkOpSegment;
class SkOpSpanBase;
class SkOpSpan;
struct SkPathOpsBounds;

// subset of op span used by terminal span (when t is equal to one)
class SkOpPtT {
public:
    enum {
        kIsAlias = 1,
        kIsDuplicate = 1
    };

    const SkOpPtT* active() const;

    // please keep in sync with debugAddOpp()
    void addOpp(SkOpPtT* opp, SkOpPtT* oppPrev) {
        SkOpPtT* oldNext = this->fNext;
        SkASSERT(this != opp);
        this->fNext = opp;
        SkASSERT(oppPrev != oldNext);
        oppPrev->fNext = oldNext;
    }

    SK_API bool alias() const;
    SK_API bool coincident() const { return fCoincident; }
    SK_API bool contains(const SkOpPtT* ) const;
    SK_API bool contains(const SkOpSegment*, const SkPoint& ) const;
    SK_API bool contains(const SkOpSegment*, double t) const;
    SK_API const SkOpPtT* contains(const SkOpSegment* ) const;
    SK_API SkOpContour* contour() const;

    int debugID() const {
        return SkDEBUGRELEASE(fID, -1);
    }

    SK_API void debugAddOpp(const SkOpPtT* opp, const SkOpPtT* oppPrev) const;
    SK_API const SkOpAngle* debugAngle(int id) const;
    SK_API const SkOpCoincidence* debugCoincidence() const;
    SK_API bool debugContains(const SkOpPtT* ) const;
    SK_API const SkOpPtT* debugContains(const SkOpSegment* check) const;
    SK_API SkOpContour* debugContour(int id) const;
    SK_API const SkOpPtT* debugEnder(const SkOpPtT* end) const;
    SK_API int debugLoopLimit(bool report) const;
    SK_API bool debugMatchID(int id) const;
    SK_API const SkOpPtT* debugOppPrev(const SkOpPtT* opp) const;
    SK_API const SkOpPtT* debugPtT(int id) const;
    SK_API void debugResetCoinT() const;
    SK_API const SkOpSegment* debugSegment(int id) const;
    SK_API void debugSetCoinT(int ) const;
    SK_API const SkOpSpanBase* debugSpan(int id) const;
    SK_API void debugValidate() const;

    bool deleted() const {
        return fDeleted;
    }

    bool duplicate() const {
        return fDuplicatePt;
    }

    SK_API void dump() const;  // available to testing only
    SK_API void dumpAll() const;
    SK_API void dumpBase() const;

    SK_API const SkOpPtT* find(const SkOpSegment* ) const;
    SK_API SkOpGlobalState* globalState() const;
    SK_API void init(SkOpSpanBase* , double t, const SkPoint& , bool dup);

    void insert(SkOpPtT* span) {
        SkASSERT(span != this);
        span->fNext = fNext;
        fNext = span;
    }

    const SkOpPtT* next() const {
        return fNext;
    }

    SkOpPtT* next() {
        return fNext;
    }

    SK_API bool onEnd() const;

    // returns nullptr if this is already in the opp ptT loop
    SkOpPtT* oppPrev(const SkOpPtT* opp) const {
        // find the fOpp ptr to opp
        SkOpPtT* oppPrev = opp->fNext;
        if (oppPrev == this) {
            return nullptr;
        }
        while (oppPrev->fNext != opp) {
            oppPrev = oppPrev->fNext;
            if (oppPrev == this) {
                return nullptr;
            }
        }
        return oppPrev;
    }

    static bool Overlaps(const SkOpPtT* s1, const SkOpPtT* e1, const SkOpPtT* s2,
            const SkOpPtT* e2, const SkOpPtT** sOut, const SkOpPtT** eOut) {
        const SkOpPtT* start1 = s1->fT < e1->fT ? s1 : e1;
        const SkOpPtT* start2 = s2->fT < e2->fT ? s2 : e2;
        *sOut = between(s1->fT, start2->fT, e1->fT) ? start2
                : between(s2->fT, start1->fT, e2->fT) ? start1 : nullptr;
        const SkOpPtT* end1 = s1->fT < e1->fT ? e1 : s1;
        const SkOpPtT* end2 = s2->fT < e2->fT ? e2 : s2;
        *eOut = between(s1->fT, end2->fT, e1->fT) ? end2
                : between(s2->fT, end1->fT, e2->fT) ? end1 : nullptr;
        if (*sOut == *eOut) {
            SkOPOBJASSERT(s1, start1->fT >= end2->fT || start2->fT >= end1->fT);
            return false;
        }
        SkASSERT(!*sOut || *sOut != *eOut);
        return *sOut && *eOut;
    }

    SK_API bool ptAlreadySeen(const SkOpPtT* head) const;
    SK_API SkOpPtT* prev();

    SK_API const SkOpSegment* segment() const;
    SK_API SkOpSegment* segment();

    void setCoincident() const {
        SkOPASSERT(!fDeleted);
        fCoincident = true;
    }

    SK_API void setDeleted();

    void setSpan(const SkOpSpanBase* span) {
        fSpan = const_cast<SkOpSpanBase*>(span);
    }

    const SkOpSpanBase* span() const {
        return fSpan;
    }

    SkOpSpanBase* span() {
        return fSpan;
    }

    const SkOpPtT* starter(const SkOpPtT* end) const {
        return fT < end->fT ? this : end;
    }

    double fT;
    SkPoint fPt;   // cache of point value at this t
protected:
    SkOpSpanBase* fSpan;  // contains winding data
    SkOpPtT* fNext;  // intersection on opposite curve or alias on this curve
    bool fDeleted;  // set if removed from span list
    bool fDuplicatePt;  // set if identical pt is somewhere in the next loop
    // below mutable since referrer is otherwise always const
    mutable bool fCoincident;  // set if at some point a coincident span pointed here
    SkDEBUGCODE(int fID);
};

class SkOpSpanBase {
public:
    enum class Collapsed {
        kNo,
        kYes,
        kError,
    };

    SK_API bool addOpp(SkOpSpanBase* opp);

    void bumpSpanAdds() {
        ++fSpanAdds;
    }

    bool chased() const {
        return fChased;
    }

    SK_API void checkForCollapsedCoincidence();

    const SkOpSpanBase* coinEnd() const {
        return fCoinEnd;
    }

    SK_API Collapsed collapsed(double s, double e) const;
    SK_API bool contains(const SkOpSpanBase* ) const;
    SK_API const SkOpPtT* contains(const SkOpSegment* ) const;

    bool containsCoinEnd(const SkOpSpanBase* coin) const {
        SkASSERT(this != coin);
        const SkOpSpanBase* next = this;
        while ((next = next->fCoinEnd) != this) {
            if (next == coin) {
                return true;
            }
        }
        return false;
    }

    SK_API bool containsCoinEnd(const SkOpSegment* ) const;
    SK_API SkOpContour* contour() const;

    int debugBumpCount() {
        return SkDEBUGRELEASE(++fCount, -1);
    }

    int debugID() const {
        return SkDEBUGRELEASE(fID, -1);
    }

#if DEBUG_COIN
    SK_API void debugAddOpp(SkPathOpsDebug::GlitchLog* , const SkOpSpanBase* opp) const;
#endif
    SK_API bool debugAlignedEnd(double t, const SkPoint& pt) const;
    SK_API bool debugAlignedInner() const;
    SK_API const SkOpAngle* debugAngle(int id) const;
#if DEBUG_COIN
    void debugCheckForCollapsedCoincidence(SkPathOpsDebug::GlitchLog* ) const;
#endif
    SK_API const SkOpCoincidence* debugCoincidence() const;
    SK_API bool debugCoinEndLoopCheck() const;
    SK_API SkOpContour* debugContour(int id) const;
#ifdef SK_DEBUG
    bool debugDeleted() const { return fDebugDeleted; }
#endif
#if DEBUG_COIN
    SK_API void debugInsertCoinEnd(SkPathOpsDebug::GlitchLog* ,
                            const SkOpSpanBase* ) const;
    SK_API void debugMergeMatches(SkPathOpsDebug::GlitchLog* log,
                           const SkOpSpanBase* opp) const;
#endif
    SK_API const SkOpPtT* debugPtT(int id) const;
    SK_API void debugResetCoinT() const;
    SK_API const SkOpSegment* debugSegment(int id) const;
    SK_API void debugSetCoinT(int ) const;
#ifdef SK_DEBUG
    SK_API void debugSetDeleted() { fDebugDeleted = true; }
#endif
    SK_API const SkOpSpanBase* debugSpan(int id) const;
    SK_API const SkOpSpan* debugStarter(SkOpSpanBase const** endPtr) const;
    SK_API SkOpGlobalState* globalState() const;
    SK_API void debugValidate() const;

    bool deleted() const {
        return fPtT.deleted();
    }

    SK_API void dump() const;  // available to testing only
    SK_API void dumpCoin() const;
    SK_API void dumpAll() const;
    SK_API void dumpBase() const;
    SK_API void dumpHead() const;

    bool final() const {
        return fPtT.fT == 1;
    }

    SkOpAngle* fromAngle() const {
        return fFromAngle;
    }

    SK_API void initBase(SkOpSegment* parent, SkOpSpan* prev, double t, const SkPoint& pt);

    // Please keep this in sync with debugInsertCoinEnd()
    void insertCoinEnd(SkOpSpanBase* coin) {
        if (containsCoinEnd(coin)) {
            SkASSERT(coin->containsCoinEnd(this));
            return;
        }
        debugValidate();
        SkASSERT(this != coin);
        SkOpSpanBase* coinNext = coin->fCoinEnd;
        coin->fCoinEnd = this->fCoinEnd;
        this->fCoinEnd = coinNext;
        debugValidate();
    }

    SK_API void merge(SkOpSpan* span);
    SK_API bool mergeMatches(SkOpSpanBase* opp);

    const SkOpSpan* prev() const {
        return fPrev;
    }

    SkOpSpan* prev() {
        return fPrev;
    }

    const SkPoint& pt() const {
        return fPtT.fPt;
    }

    const SkOpPtT* ptT() const {
        return &fPtT;
    }

    SkOpPtT* ptT() {
        return &fPtT;
    }

    SkOpSegment* segment() const {
        return fSegment;
    }

    void setAligned() {
        fAligned = true;
    }

    void setChased(bool chased) {
        fChased = chased;
    }

    void setFromAngle(SkOpAngle* angle) {
        fFromAngle = angle;
    }

    void setPrev(SkOpSpan* prev) {
        fPrev = prev;
    }

    bool simple() const {
        fPtT.debugValidate();
        return fPtT.next()->next() == &fPtT;
    }

    int spanAddsCount() const {
        return fSpanAdds;
    }

    const SkOpSpan* starter(const SkOpSpanBase* end) const {
        const SkOpSpanBase* result = t() < end->t() ? this : end;
        return result->upCast();
    }

    SkOpSpan* starter(SkOpSpanBase* end) {
        SkASSERT(this->segment() == end->segment());
        SkOpSpanBase* result = t() < end->t() ? this : end;
        return result->upCast();
    }

    SkOpSpan* starter(SkOpSpanBase** endPtr) {
        SkOpSpanBase* end = *endPtr;
        SkASSERT(this->segment() == end->segment());
        SkOpSpanBase* result;
        if (t() < end->t()) {
            result = this;
        } else {
            result = end;
            *endPtr = this;
        }
        return result->upCast();
    }

    int step(const SkOpSpanBase* end) const {
        return t() < end->t() ? 1 : -1;
    }

    double t() const {
        return fPtT.fT;
    }

    void unaligned() {
        fAligned = false;
    }

    SkOpSpan* upCast() {
        SkASSERT(!final());
        return (SkOpSpan*) this;
    }

    const SkOpSpan* upCast() const {
        SkOPASSERT(!final());
        return (const SkOpSpan*) this;
    }

    SkOpSpan* upCastable() {
        return final() ? nullptr : upCast();
    }

    const SkOpSpan* upCastable() const {
        return final() ? nullptr : upCast();
    }

private:
    SK_API void alignInner();

protected:  // no direct access to internals to avoid treating a span base as a span
    SkOpPtT fPtT;  // list of points and t values associated with the start of this span
    SkOpSegment* fSegment;  // segment that contains this span
    SkOpSpanBase* fCoinEnd;  // linked list of coincident spans that end here (may point to itself)
    SkOpAngle* fFromAngle;  // points to next angle from span start to end
    SkOpSpan* fPrev;  // previous intersection point
    int fSpanAdds;  // number of times intersections have been added to span
    bool fAligned;
    bool fChased;  // set after span has been added to chase array
    SkDEBUGCODE(int fCount);  // number of pt/t pairs added
    SkDEBUGCODE(int fID);
    SkDEBUGCODE(bool fDebugDeleted);  // set when span was merged with another span
};

class SkOpSpan : public SkOpSpanBase {
public:
    bool alreadyAdded() const {
        if (fAlreadyAdded) {
            return true;
        }
        return false;
    }

    bool clearCoincident() {
        SkASSERT(!final());
        if (fCoincident == this) {
            return false;
        }
        fCoincident = this;
        return true;
    }

    SK_API int computeWindSum();
    SK_API bool containsCoincidence(const SkOpSegment* ) const;

    bool containsCoincidence(const SkOpSpan* coin) const {
        SkASSERT(this != coin);
        const SkOpSpan* next = this;
        while ((next = next->fCoincident) != this) {
            if (next == coin) {
                return true;
            }
        }
        return false;
    }

    SK_API bool debugCoinLoopCheck() const;
#if DEBUG_COIN
    SK_API void debugInsertCoincidence(SkPathOpsDebug::GlitchLog* , const SkOpSpan* ) const;
    SK_API void debugInsertCoincidence(SkPathOpsDebug::GlitchLog* ,
                                const SkOpSegment* , bool flipped, bool ordered) const;
#endif
    SK_API void dumpCoin() const;
    SK_API bool dumpSpan() const;

    bool done() const {
        SkASSERT(!final());
        return fDone;
    }

    SK_API void init(SkOpSegment* parent, SkOpSpan* prev, double t, const SkPoint& pt);
    SK_API bool insertCoincidence(const SkOpSegment* , bool flipped, bool ordered);

    // Please keep this in sync with debugInsertCoincidence()
    void insertCoincidence(SkOpSpan* coin) {
        if (containsCoincidence(coin)) {
            SkASSERT(coin->containsCoincidence(this));
            return;
        }
        debugValidate();
        SkASSERT(this != coin);
        SkOpSpan* coinNext = coin->fCoincident;
        coin->fCoincident = this->fCoincident;
        this->fCoincident = coinNext;
        debugValidate();
    }

    bool isCanceled() const {
        SkASSERT(!final());
        return fWindValue == 0 && fOppValue == 0;
    }

    bool isCoincident() const {
        SkASSERT(!final());
        return fCoincident != this;
    }

    void markAdded() {
        fAlreadyAdded = true;
    }

    SkOpSpanBase* next() const {
        SkASSERT(!final());
        return fNext;
    }

    int oppSum() const {
        SkASSERT(!final());
        return fOppSum;
    }

    int oppValue() const {
        SkASSERT(!final());
        return fOppValue;
    }

    SK_API void release(const SkOpPtT* );

    SK_API SkOpPtT* setCoinStart(SkOpSpan* oldCoinStart, SkOpSegment* oppSegment);

    void setDone(bool done) {
        SkASSERT(!final());
        fDone = done;
    }

    void setNext(SkOpSpanBase* nextT) {
        SkASSERT(!final());
        fNext = nextT;
    }

    SK_API void setOppSum(int oppSum);

    void setOppValue(int oppValue) {
        SkASSERT(!final());
        SkASSERT(fOppSum == SK_MinS32);
        SkOPASSERT(!oppValue || !fDone);
        fOppValue = oppValue;
    }

    void setToAngle(SkOpAngle* angle) {
        SkASSERT(!final());
        fToAngle = angle;
    }

    SK_API void setWindSum(int windSum);

    void setWindValue(int windValue) {
        SkASSERT(!final());
        SkASSERT(windValue >= 0);
        SkASSERT(fWindSum == SK_MinS32);
        SkOPASSERT(!windValue || !fDone);
        fWindValue = windValue;
    }

    SK_API bool sortableTop(SkOpContour* );

    SkOpAngle* toAngle() const {
        SkASSERT(!final());
        return fToAngle;
    }

    int windSum() const {
        SkASSERT(!final());
        return fWindSum;
    }

    int windValue() const {
        SkOPASSERT(!final());
        return fWindValue;
    }

private:  // no direct access to internals to avoid treating a span base as a span
    SkOpSpan* fCoincident;  // linked list of spans coincident with this one (may point to itself)
    SkOpAngle* fToAngle;  // points to next angle from span start to end
    SkOpSpanBase* fNext;  // next intersection point
    int fWindSum;  // accumulated from contours surrounding this one.
    int fOppSum;  // for binary operators: the opposite winding sum
    int fWindValue;  // 0 == canceled; 1 == normal; >1 == coincident
    int fOppValue;  // normally 0 -- when binary coincident edges combine, opp value goes here
    int fTopTTry; // specifies direction and t value to try next
    bool fDone;  // if set, this span to next higher T has been processed
    bool fAlreadyAdded;
};

#endif
