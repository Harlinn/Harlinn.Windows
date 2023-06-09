/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkLatticeIter_DEFINED
#define SkLatticeIter_DEFINED

#include <skia/core/SkCanvas.h>
#include <skia/core/SkScalar.h>
#include <skia/private/SkTArray.h>

struct SkIRect;
struct SkRect;

/**
 *  Disect a lattice request into an sequence of src-rect / dst-rect pairs
 */
class SkLatticeIter {
public:

    SK_SPI static bool Valid(int imageWidth, int imageHeight, const SkCanvas::Lattice& lattice);

    SK_SPI SkLatticeIter(const SkCanvas::Lattice& lattice, const SkRect& dst);

    SK_SPI static bool Valid(int imageWidth, int imageHeight, const SkIRect& center);

    SK_SPI SkLatticeIter(int imageWidth, int imageHeight, const SkIRect& center, const SkRect& dst);

    /**
     *  While it returns true, use src/dst to draw the image/bitmap. Optional parameters
     *  isFixedColor and fixedColor specify if the rectangle is filled with a fixed color.
     *  If (*isFixedColor) is true, then (*fixedColor) contains the rectangle color.
     */
    SK_SPI bool next(SkIRect* src, SkRect* dst, bool* isFixedColor = nullptr,
              SkColor* fixedColor = nullptr);

    /** Version of above that converts the integer src rect to a scalar rect. */
    bool next(SkRect* src, SkRect* dst, bool* isFixedColor = nullptr,
              SkColor* fixedColor = nullptr) {
        SkIRect isrcR;
        if (this->next(&isrcR, dst, isFixedColor, fixedColor)) {
            *src = SkRect::Make(isrcR);
            return true;
        }
        return false;
    }

    /**
     *  Apply a matrix to the dst points.
     */
    SK_SPI void mapDstScaleTranslate(const SkMatrix& matrix);

    /**
     *  Returns the number of rects that will actually be drawn.
     */
    int numRectsToDraw() const {
        return fNumRectsToDraw;
    }

private:
    SkTArray<int> fSrcX;
    SkTArray<int> fSrcY;
    SkTArray<SkScalar> fDstX;
    SkTArray<SkScalar> fDstY;
    SkTArray<SkCanvas::Lattice::RectType> fRectTypes;
    SkTArray<SkColor> fColors;

    int  fCurrX;
    int  fCurrY;
    int  fNumRectsInLattice;
    int  fNumRectsToDraw;
};

#endif
