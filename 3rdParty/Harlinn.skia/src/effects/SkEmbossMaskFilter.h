/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkEmbossMaskFilter_DEFINED
#define SkEmbossMaskFilter_DEFINED

#include "src/core/SkMaskFilterBase.h"

/** \class SkEmbossMaskFilter

    This mask filter creates a 3D emboss look, by specifying a light and blur amount.
*/
class SkEmbossMaskFilter : public SkMaskFilterBase {
public:
    struct Light {
        SkScalar    fDirection[3];  // x,y,z
        uint16_t    fPad;
        uint8_t     fAmbient;
        uint8_t     fSpecular;      // exponent, 4.4 right now
    };

    SK_API static sk_sp<SkMaskFilter> Make(SkScalar blurSigma, const Light& light);

    // overrides from SkMaskFilter
    //  This method is not exported to java.
    SK_API SkMask::Format getFormat() const override;
    //  This method is not exported to java.
    SK_API bool filterMask(SkMask* dst, const SkMask& src, const SkMatrix&,
                    SkIPoint* margin) const override;

protected:
    SK_API SkEmbossMaskFilter(SkScalar blurSigma, const Light& light);
    SK_API void flatten(SkWriteBuffer&) const override;

private:
    SK_FLATTENABLE_HOOKS(SkEmbossMaskFilter)

    Light       fLight;
    SkScalar    fBlurSigma;

    using INHERITED = SkMaskFilter;
};

#endif
