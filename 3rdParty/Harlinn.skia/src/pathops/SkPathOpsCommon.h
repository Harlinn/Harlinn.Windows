/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkPathOpsCommon_DEFINED
#define SkPathOpsCommon_DEFINED

#include <skia/private/SkTDArray.h>
#include "src/pathops/SkOpAngle.h"

class SkOpCoincidence;
class SkOpContour;
class SkPathWriter;

SK_API const SkOpAngle* AngleWinding(SkOpSpanBase* start, SkOpSpanBase* end, int* windingPtr,
                              bool* sortable);
SK_API SkOpSegment* FindChase(SkTDArray<SkOpSpanBase*>* chase, SkOpSpanBase** startPtr,
                       SkOpSpanBase** endPtr);
SK_API SkOpSpan* FindSortableTop(SkOpContourHead* );
SK_API SkOpSpan* FindUndone(SkOpContourHead* );
SK_API bool FixWinding(SkPath* path);
SK_API bool SortContourList(SkOpContourHead** , bool evenOdd, bool oppEvenOdd);
SK_API bool HandleCoincidence(SkOpContourHead* , SkOpCoincidence* );
SK_API bool OpDebug(const SkPath& one, const SkPath& two, SkPathOp op, SkPath* result
             SkDEBUGPARAMS(bool skipAssert)
             SkDEBUGPARAMS(const char* testName));

#endif
