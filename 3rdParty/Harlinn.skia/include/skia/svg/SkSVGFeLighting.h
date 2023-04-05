/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGFeLighting_DEFINED
#define SkSVGFeLighting_DEFINED

#include "skia/svg/SkSVGFe.h"
#include "skia/svg/SkSVGTypes.h"

class SkSVGFeDistantLight;
class SkSVGFePointLight;
class SkSVGFeSpotLight;

class SkSVGFeLighting : public SkSVGFe {
public:
    struct KernelUnitLength {
        SkSVGNumberType fDx;
        SkSVGNumberType fDy;
    };

    SVG_ATTR(SurfaceScale, SkSVGNumberType, 1)
    SVG_OPTIONAL_ATTR(KernelUnitLength, KernelUnitLength)

protected:
    explicit SkSVGFeLighting(SkSVGTag t) : INHERITED(t) {}

    std::vector<SkSVGFeInputType> getInputs() const final { return {this->getIn()}; }

    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    SK_API sk_sp<SkImageFilter> onMakeImageFilter(const SkSVGRenderContext&,
                                           const SkSVGFilterContext&) const final;

    virtual sk_sp<SkImageFilter> makeDistantLight(const SkSVGRenderContext&,
                                                  const SkSVGFilterContext&,
                                                  const SkSVGFeDistantLight*) const = 0;

    virtual sk_sp<SkImageFilter> makePointLight(const SkSVGRenderContext&,
                                                const SkSVGFilterContext&,
                                                const SkSVGFePointLight*) const = 0;

    virtual sk_sp<SkImageFilter> makeSpotLight(const SkSVGRenderContext&,
                                               const SkSVGFilterContext&,
                                               const SkSVGFeSpotLight*) const = 0;

    SK_API SkColor resolveLightingColor(const SkSVGRenderContext&) const;

    SK_API SkPoint3 resolveXYZ(const SkSVGRenderContext&,
                        const SkSVGFilterContext&,
                        SkSVGNumberType,
                        SkSVGNumberType,
                        SkSVGNumberType) const;

private:
    using INHERITED = SkSVGFe;
};

class SkSVGFeSpecularLighting final : public SkSVGFeLighting {
public:
    static sk_sp<SkSVGFeSpecularLighting> Make() {
        return sk_sp<SkSVGFeSpecularLighting>(new SkSVGFeSpecularLighting());
    }

    SVG_ATTR(SpecularConstant, SkSVGNumberType, 1)
    SVG_ATTR(SpecularExponent, SkSVGNumberType, 1)

protected:
    bool parseAndSetAttribute(const char*, const char*) override;

    SK_API sk_sp<SkImageFilter> makeDistantLight(const SkSVGRenderContext&,
                                          const SkSVGFilterContext&,
                                          const SkSVGFeDistantLight*) const final;

    SK_API sk_sp<SkImageFilter> makePointLight(const SkSVGRenderContext&,
                                        const SkSVGFilterContext&,
                                        const SkSVGFePointLight*) const final;

    SK_API sk_sp<SkImageFilter> makeSpotLight(const SkSVGRenderContext&,
                                       const SkSVGFilterContext&,
                                       const SkSVGFeSpotLight*) const final;

private:
    SkSVGFeSpecularLighting() : INHERITED(SkSVGTag::kFeSpecularLighting) {}

    using INHERITED = SkSVGFeLighting;
};

class SkSVGFeDiffuseLighting final : public SkSVGFeLighting {
public:
    static sk_sp<SkSVGFeDiffuseLighting> Make() {
        return sk_sp<SkSVGFeDiffuseLighting>(new SkSVGFeDiffuseLighting());
    }

    SVG_ATTR(DiffuseConstant, SkSVGNumberType, 1)

protected:
    SK_API bool parseAndSetAttribute(const char*, const char*) override;

    SK_API sk_sp<SkImageFilter> makeDistantLight(const SkSVGRenderContext&,
                                          const SkSVGFilterContext&,
                                          const SkSVGFeDistantLight*) const final;

    SK_API sk_sp<SkImageFilter> makePointLight(const SkSVGRenderContext&,
                                        const SkSVGFilterContext&,
                                        const SkSVGFePointLight*) const final;

    SK_API sk_sp<SkImageFilter> makeSpotLight(const SkSVGRenderContext&,
                                       const SkSVGFilterContext&,
                                       const SkSVGFeSpotLight*) const final;

private:
    SkSVGFeDiffuseLighting() : INHERITED(SkSVGTag::kFeDiffuseLighting) {}

    using INHERITED = SkSVGFeLighting;
};

#endif  // SkSVGFeLighting_DEFINED
