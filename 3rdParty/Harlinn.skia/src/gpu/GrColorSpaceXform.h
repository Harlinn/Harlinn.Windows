/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrColorSpaceXform_DEFINED
#define GrColorSpaceXform_DEFINED

#include <skia/core/SkRefCnt.h>
#include "src/core/SkColorSpacePriv.h"
#include "src/core/SkColorSpaceXformSteps.h"
#include "src/gpu/GrFragmentProcessor.h"

class GrColorInfo;
class SkColorSpace;

 /**
  * Represents a color space transformation
  */
class GrColorSpaceXform : public SkRefCnt {
public:
    GrColorSpaceXform(const SkColorSpaceXformSteps& steps) : fSteps(steps) {}

    SK_API static sk_sp<GrColorSpaceXform> Make(SkColorSpace* src, SkAlphaType srcAT,
                                         SkColorSpace* dst, SkAlphaType dstAT);

    SK_API static sk_sp<GrColorSpaceXform> Make(const GrColorInfo& srcInfo, const GrColorInfo& dstInfo);

    const SkColorSpaceXformSteps& steps() const { return fSteps; }

    /**
     * GrFragmentProcessor::addToKey() must call this and include the returned value in its
     * computed key.
     */
    static uint32_t XformKey(const GrColorSpaceXform* xform) {
        // Code generation depends on which steps we apply,
        // and the kinds of transfer functions (if we're applying those).
        if (!xform) { return 0; }

        const SkColorSpaceXformSteps& steps(xform->fSteps);
        uint32_t key = steps.flags.mask();
        if (steps.flags.linearize) {
            key |= classify_transfer_fn(steps.srcTF)    << 8;
        }
        if (steps.flags.encode) {
            key |= classify_transfer_fn(steps.dstTFInv) << 16;
        }
        return key;
    }

    SK_API static bool Equals(const GrColorSpaceXform* a, const GrColorSpaceXform* b);

    SK_API SkColor4f apply(const SkColor4f& srcColor);

private:
    friend class GrGLSLColorSpaceXformHelper;

    SkColorSpaceXformSteps fSteps;
};

class GrColorSpaceXformEffect : public GrFragmentProcessor {
public:
    /**
     *  Returns a fragment processor that calls the passed in fragment processor, and then converts
     *  the color space of the output from src to dst. If the child is null, fInputColor is used.
     */
    SK_API static std::unique_ptr<GrFragmentProcessor> Make(std::unique_ptr<GrFragmentProcessor> child,
                                                     SkColorSpace* src, SkAlphaType srcAT,
                                                     SkColorSpace* dst, SkAlphaType dstAT);
    SK_API static std::unique_ptr<GrFragmentProcessor> Make(std::unique_ptr<GrFragmentProcessor> child,
                                                     const GrColorInfo& srcInfo,
                                                     const GrColorInfo& dstInfo);

    /**
     * Returns a fragment processor that calls the passed in FP and then converts it with the given
     * color xform. If the child is null, fInputColor is used. Returns child as-is if the xform is
     * null (i.e. a no-op).
     */
    SK_API static std::unique_ptr<GrFragmentProcessor> Make(std::unique_ptr<GrFragmentProcessor> child,
                                                     sk_sp<GrColorSpaceXform> colorXform);

    const char* name() const override { return "ColorSpaceXform"; }
    SK_API std::unique_ptr<GrFragmentProcessor> clone() const override;

    const GrColorSpaceXform* colorXform() const { return fColorXform.get(); }

private:
    SK_API GrColorSpaceXformEffect(std::unique_ptr<GrFragmentProcessor> child,
                            sk_sp<GrColorSpaceXform> colorXform);

    SK_API GrColorSpaceXformEffect(const GrColorSpaceXformEffect& that);

    SK_API static OptimizationFlags OptFlags(const GrFragmentProcessor* child);
    SK_API SkPMColor4f constantOutputForConstantInput(const SkPMColor4f& input) const override;

    SK_API std::unique_ptr<ProgramImpl> onMakeProgramImpl() const override;
    SK_API void onAddToKey(const GrShaderCaps&, GrProcessorKeyBuilder*) const override;
    SK_API bool onIsEqual(const GrFragmentProcessor&) const override;

    sk_sp<GrColorSpaceXform> fColorXform;

    using INHERITED = GrFragmentProcessor;
};

#endif