#pragma once
#ifndef PBRTO_BASE_NEWTEXTURE_H_
#define PBRTO_BASE_NEWTEXTURE_H_

/*
   Copyright 2024-2025 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>


#include <string>

namespace pbrto
{

    struct TextureEvalContext;

    class FloatConstantTexture;
    class FloatBilerpTexture;
    class FloatCheckerboardTexture;
    class FloatDotsTexture;
    class FBmTexture;
    class GPUFloatImageTexture;
    class FloatImageTexture;
    class FloatMixTexture;
    class FloatDirectionMixTexture;
    class FloatPtexTexture;
    class GPUFloatPtexTexture;
    class FloatScaledTexture;
    class WindyTexture;
    class WrinkledTexture;

    // FloatTexture Definition
    class FloatTexture : public TaggedPointer< FloatImageTexture, GPUFloatImageTexture, FloatMixTexture, FloatDirectionMixTexture, FloatScaledTexture, FloatConstantTexture, FloatBilerpTexture, FloatCheckerboardTexture, FloatDotsTexture, FBmTexture, FloatPtexTexture, GPUFloatPtexTexture, WindyTexture, WrinkledTexture >
    {
    public:
        // FloatTexture Interface
        using TaggedPointer::TaggedPointer;

        static FloatTexture Create( const std::string& name, const Transform& renderFromTexture, const TextureParameterDictionary& parameters, const FileLoc* loc, Allocator alloc, bool gpu );

        std::string ToString( ) const;

        PBRT_CPU_GPU
            inline Float Evaluate( TextureEvalContext ctx ) const;
    };

    class RGBConstantTexture;
    class RGBReflectanceConstantTexture;
    class SpectrumConstantTexture;
    class SpectrumBilerpTexture;
    class SpectrumCheckerboardTexture;
    class SpectrumImageTexture;
    class GPUSpectrumImageTexture;
    class MarbleTexture;
    class SpectrumMixTexture;
    class SpectrumDirectionMixTexture;
    class SpectrumDotsTexture;
    class SpectrumPtexTexture;
    class GPUSpectrumPtexTexture;
    class SpectrumScaledTexture;

    // SpectrumTexture Definition
    class SpectrumTexture : public TaggedPointer< SpectrumImageTexture, GPUSpectrumImageTexture, SpectrumMixTexture, SpectrumDirectionMixTexture, SpectrumScaledTexture, SpectrumConstantTexture, SpectrumBilerpTexture, SpectrumCheckerboardTexture, MarbleTexture, SpectrumDotsTexture, SpectrumPtexTexture, GPUSpectrumPtexTexture >
    {
    public:
        // SpectrumTexture Interface
        using TaggedPointer::TaggedPointer;

        static SpectrumTexture Create( const std::string& name, const Transform& renderFromTexture, const TextureParameterDictionary& parameters, SpectrumType spectrumType, const FileLoc* loc, Allocator alloc, bool gpu );

        std::string ToString( ) const;

        PBRT_CPU_GPU
            inline SampledSpectrum Evaluate( TextureEvalContext ctx, SampledWavelengths lambda ) const;
    };

}

#endif

