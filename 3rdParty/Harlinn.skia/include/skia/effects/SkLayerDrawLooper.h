#pragma once
/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkLayerDrawLooper_DEFINED
#define SkLayerDrawLooper_DEFINED

#include <skia/core/SkBlendMode.h>
#include <skia/core/SkDrawLooper.h>
#include <skia/core/SkPaint.h>
#include <skia/core/SkPoint.h>

#ifndef SK_SUPPORT_LEGACY_DRAWLOOPER
#error "SkDrawLooper is unsupported"
#endif

/**
 *  DEPRECATED: No longer supported by Skia.
 */
class SkLayerDrawLooper : public SkDrawLooper {
public:
    SK_API ~SkLayerDrawLooper() override;

    /**
     *  Bits specifies which aspects of the layer's paint should replace the
     *  corresponding aspects on the draw's paint.
     *  kEntirePaint_Bits means use the layer's paint completely.
     *  0 means ignore the layer's paint... except for fColorMode, which is
     *  always applied.
     */
    enum Bits {
        kStyle_Bit      = 1 << 0,   //!< use this layer's Style/stroke settings
        kPathEffect_Bit = 1 << 2,   //!< use this layer's patheffect
        kMaskFilter_Bit = 1 << 3,   //!< use this layer's maskfilter
        kShader_Bit     = 1 << 4,   //!< use this layer's shader
        kColorFilter_Bit = 1 << 5,  //!< use this layer's colorfilter
        kXfermode_Bit   = 1 << 6,   //!< use this layer's xfermode

        // unsupported kTextSkewX_Bit  = 1 << 1,

        /**
         *  Use the layer's paint entirely, with these exceptions:
         *  - We never override the draw's paint's text_encoding, since that is
         *    used to interpret the text/len parameters in draw[Pos]Text.
         *  - Color is always computed using the LayerInfo's fColorMode.
         */
        kEntirePaint_Bits = -1

    };
    typedef int32_t BitFlags;

    /**
     *  Info for how to apply the layer's paint and offset.
     *
     *  fColorMode controls how we compute the final color for the layer:
     *      The layer's paint's color is treated as the SRC
     *      The draw's paint's color is treated as the DST
     *      final-color = Mode(layers-color, draws-color);
     *  Any SkBlendMode will work. Two common choices are:
     *      kSrc: to use the layer's color, ignoring the draw's
     *      kDst: to just keep the draw's color, ignoring the layer's
     */
    struct LayerInfo {
        BitFlags    fPaintBits;
        SkBlendMode fColorMode;
        SkVector    fOffset;
        bool        fPostTranslate; //!< applies to fOffset

        /**
         *  Initial the LayerInfo. Defaults to settings that will draw the
         *  layer with no changes: e.g.
         *      fPaintBits == 0
         *      fColorMode == kDst_Mode
         *      fOffset == (0, 0)
         */
        SK_API LayerInfo();
    };

    SK_API SkDrawLooper::Context* makeContext(SkArenaAlloc*) const override;

    SK_API bool asABlurShadow(BlurShadowRec* rec) const override;

protected:
    SK_API SkLayerDrawLooper();

    SK_API void flatten(SkWriteBuffer&) const override;

private:
    SK_FLATTENABLE_HOOKS(SkLayerDrawLooper)

    struct Rec {
        Rec*    fNext;
        SkPaint fPaint;
        LayerInfo fInfo;
    };
    Rec*    fRecs;
    int     fCount;

    // state-machine during the init/next cycle
    class LayerDrawLooperContext : public SkDrawLooper::Context {
    public:
        SK_API explicit LayerDrawLooperContext(const SkLayerDrawLooper* looper);

    protected:
        SK_API bool next(Info*, SkPaint* paint) override;

    private:
        Rec* fCurrRec;

        SK_API static void ApplyInfo(SkPaint* dst, const SkPaint& src, const LayerInfo&);
    };

    using INHERITED = SkDrawLooper;

public:
    class Builder {
    public:
        SK_API Builder();

        SK_API ~Builder();

        /**
         *  Call for each layer you want to add (from top to bottom).
         *  This returns a paint you can modify, but that ptr is only valid until
         *  the next call made to addLayer().
         */
        SK_API SkPaint* addLayer(const LayerInfo&);

        /**
         *  This layer will draw with the original paint, at the specified offset
         */
        SK_API void addLayer(SkScalar dx, SkScalar dy);

        /**
         *  This layer will with the original paint and no offset.
         */
        void addLayer() { this->addLayer(0, 0); }

        /// Similar to addLayer, but adds a layer to the top.
        SK_API SkPaint* addLayerOnTop(const LayerInfo&);

        /**
          * Pass list of layers on to newly built looper and return it. This will
          * also reset the builder, so it can be used to build another looper.
          */
        SK_API sk_sp<SkDrawLooper> detach();

    private:
        Builder(const Builder&) = delete;
        Builder& operator=(const Builder&) = delete;

        Rec* fRecs;
        Rec* fTopRec;
        int  fCount;
    };
};

#endif
