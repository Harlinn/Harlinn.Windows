/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkOpEdgeBuilder_DEFINED
#define SkOpEdgeBuilder_DEFINED

#include "src/pathops/SkOpContour.h"
#include "src/pathops/SkPathWriter.h"

class SkOpEdgeBuilder {
public:
    SkOpEdgeBuilder(const SkPathWriter& path, SkOpContourHead* contours2,
            SkOpGlobalState* globalState)
        : fGlobalState(globalState)
        , fPath(path.nativePath())
        , fContourBuilder(contours2)
        , fContoursHead(contours2)
        , fAllowOpenContours(true) {
        init();
    }

    SkOpEdgeBuilder(const SkPath& path, SkOpContourHead* contours2, SkOpGlobalState* globalState)
        : fGlobalState(globalState)
        , fPath(&path)
        , fContourBuilder(contours2)
        , fContoursHead(contours2)
        , fAllowOpenContours(false) {
        init();
    }

    SK_API void addOperand(const SkPath& path);

    void complete() {
        fContourBuilder.flush();
        SkOpContour* contour = fContourBuilder.contour();
        if (contour && contour->count()) {
            contour->complete();
            fContourBuilder.setContour(nullptr);
        }
    }

    SK_API bool finish();

    const SkOpContour* head() const {
        return fContoursHead;
    }

    SK_API void init();
    bool unparseable() const { return fUnparseable; }
    SkPathOpsMask xorMask() const { return fXorMask[fOperand]; }

private:
    SK_API void closeContour(const SkPoint& curveEnd, const SkPoint& curveStart);
    SK_API bool close();
    SK_API int preFetch();
    SK_API bool walk();

    SkOpGlobalState* fGlobalState;
    const SkPath* fPath;
    SkTDArray<SkPoint> fPathPts;
    SkTDArray<SkScalar> fWeights;
    SkTDArray<uint8_t> fPathVerbs;
    SkOpContourBuilder fContourBuilder;
    SkOpContourHead* fContoursHead;
    SkPathOpsMask fXorMask[2];
    int fSecondHalf;
    bool fOperand;
    bool fAllowOpenContours;
    bool fUnparseable;
};

#endif
