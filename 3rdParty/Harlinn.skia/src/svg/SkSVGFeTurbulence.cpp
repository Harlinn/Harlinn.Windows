/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/effects/SkImageFilters.h"
#include "skia/effects/SkPerlinNoiseShader.h"
#include "skia/svg/SkSVGAttributeParser.h"
#include "skia/svg/SkSVGFeTurbulence.h"
#include "skia/svg/SkSVGFilterContext.h"
#include "skia/svg/SkSVGRenderContext.h"
#include "skia/svg/SkSVGValue.h"

bool SkSVGFeTurbulence::parseAndSetAttribute(const char* name, const char* value) {
    return INHERITED::parseAndSetAttribute(name, value) ||
           this->setNumOctaves(
                   SkSVGAttributeParser::parse<SkSVGIntegerType>("numOctaves", name, value)) ||
           this->setSeed(SkSVGAttributeParser::parse<SkSVGNumberType>("seed", name, value)) ||
           this->setBaseFrequency(SkSVGAttributeParser::parse<SkSVGFeTurbulenceBaseFrequency>(
                   "baseFrequency", name, value)) ||
           this->setTurbulenceType(SkSVGAttributeParser::parse<SkSVGFeTurbulenceType>(
                   "type", name, value));
}

template <>
bool SkSVGAttributeParser::parse<SkSVGFeTurbulenceBaseFrequency>(
        SkSVGFeTurbulenceBaseFrequency* freq) {
    SkSVGNumberType freqX;
    if (!this->parse(&freqX)) {
        return false;
    }

    SkSVGNumberType freqY;
    this->parseCommaWspToken();
    if (this->parse(&freqY)) {
        *freq = SkSVGFeTurbulenceBaseFrequency(freqX, freqY);
    } else {
        *freq = SkSVGFeTurbulenceBaseFrequency(freqX, freqX);
    }

    return this->parseEOSToken();
}

template <>
bool SkSVGAttributeParser::parse<SkSVGFeTurbulenceType>(SkSVGFeTurbulenceType* type) {
    bool parsedValue = false;

    if (this->parseExpectedStringToken("fractalNoise")) {
        *type = SkSVGFeTurbulenceType(SkSVGFeTurbulenceType::kFractalNoise);
        parsedValue = true;
    } else if (this->parseExpectedStringToken("turbulence")) {
        *type = SkSVGFeTurbulenceType(SkSVGFeTurbulenceType::kTurbulence);
        parsedValue = true;
    }

    return parsedValue && this->parseEOSToken();
}

sk_sp<SkImageFilter> SkSVGFeTurbulence::onMakeImageFilter(const SkSVGRenderContext& ctx,
                                                          const SkSVGFilterContext& fctx) const {
    const SkISize* tileSize = nullptr;  // TODO: needs filter element subregion properties

    sk_sp<SkShader> shader;
    switch (fTurbulenceType.fType) {
        case SkSVGFeTurbulenceType::Type::kTurbulence:
            shader = SkPerlinNoiseShader::MakeTurbulence(
                    fBaseFrequency.freqX(), fBaseFrequency.freqY(), fNumOctaves, fSeed, tileSize);
            break;
        case SkSVGFeTurbulenceType::Type::kFractalNoise:
            shader = SkPerlinNoiseShader::MakeFractalNoise(
                    fBaseFrequency.freqX(), fBaseFrequency.freqY(), fNumOctaves, fSeed, tileSize);
            break;
    }

    return SkImageFilters::Shader(shader, this->resolveFilterSubregion(ctx, fctx));
}
