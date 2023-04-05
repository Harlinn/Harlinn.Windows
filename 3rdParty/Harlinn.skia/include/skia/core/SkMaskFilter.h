#pragma once
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkMaskFilter_DEFINED
#define SkMaskFilter_DEFINED

#include <skia/core/SkBlurTypes.h>
#include <skia/core/SkCoverageMode.h>
#include <skia/core/SkFlattenable.h>
#include <skia/core/SkScalar.h>

class SkMatrix;
struct SkRect;

/** \class SkMaskFilter

    SkMaskFilter is the base class for object that perform transformations on
    the mask before drawing it. An example subclass is Blur.
*/
class SkMaskFilter : public SkFlattenable {
public:
    /** Create a blur maskfilter.
     *  @param style      The SkBlurStyle to use
     *  @param sigma      Standard deviation of the Gaussian blur to apply. Must be > 0.
     *  @param respectCTM if true the blur's sigma is modified by the CTM.
     *  @return The new blur maskfilter
     */
    SK_API static sk_sp<SkMaskFilter> MakeBlur(SkBlurStyle style, SkScalar sigma,
                                        bool respectCTM = true);

    /**
     *  Returns the approximate bounds that would result from filtering the src rect.
     *  The actual result may be different, but it should be contained within the
     *  returned bounds.
     */
    SK_API SkRect approximateFilteredBounds(const SkRect& src) const;

    SK_API static sk_sp<SkMaskFilter> Deserialize(const void* data, size_t size,
                                           const SkDeserialProcs* procs = nullptr);

private:
    SK_API static void RegisterFlattenables();
    friend class SkFlattenable;
};

#endif
