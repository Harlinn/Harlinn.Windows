/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGImage_DEFINED
#define SkSGImage_DEFINED

#include "SkSGRenderNode.h"

#include "skia/core/SkSamplingOptions.h"

class SkImage;

namespace sksg {

/**
 * Concrete rendering node, wrapping an SkImage.
 *
 */
class Image final : public RenderNode {
public:
    static sk_sp<Image> Make(sk_sp<SkImage> image) {
        return sk_sp<Image>(new Image(std::move(image)));
    }

    SG_ATTRIBUTE(Image          , sk_sp<SkImage>   , fImage          )
    SG_ATTRIBUTE(SamplingOptions, SkSamplingOptions, fSamplingOptions)
    SG_ATTRIBUTE(AntiAlias      , bool             , fAntiAlias      )

protected:
    SK_API explicit Image(sk_sp<SkImage>);

    SK_API void onRender(SkCanvas*, const RenderContext*) const override;
    SK_API const RenderNode* onNodeAt(const SkPoint&)     const override;

    SK_API SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;

private:
    SkSamplingOptions fSamplingOptions;
    sk_sp<SkImage>    fImage;
    bool              fAntiAlias = true;

    using INHERITED = RenderNode;
};

} // namespace sksg

#endif // SkSGImage_DEFINED
