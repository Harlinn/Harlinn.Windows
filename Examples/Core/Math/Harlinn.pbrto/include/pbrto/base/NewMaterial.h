#pragma once
#ifndef PBRTO_BASE_NEWMATERIAL_H_
#define PBRTO_BASE_NEWMATERIAL_H_

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

#include <pbrto/base/NewBssrdf.h>
#include <pbrto/base/NewTexture.h>
#include <pbrto/util/NewTaggedPtr.h>

#include <map>
#include <string>

namespace pbrto
{

    struct MaterialEvalContext;

    // Material Declarations
    class CoatedDiffuseMaterial;
    class CoatedConductorMaterial;
    class ConductorMaterial;
    class DielectricMaterial;
    class DiffuseMaterial;
    class DiffuseTransmissionMaterial;
    class HairMaterial;
    class MeasuredMaterial;
    class SubsurfaceMaterial;
    class ThinDielectricMaterial;
    class MixMaterial;

    // Material Definition
    class Material
        : public TaggedPointer<  // Material Types
        CoatedDiffuseMaterial, CoatedConductorMaterial, ConductorMaterial,
        DielectricMaterial, DiffuseMaterial, DiffuseTransmissionMaterial, HairMaterial,
        MeasuredMaterial, SubsurfaceMaterial, ThinDielectricMaterial, MixMaterial

        >
    {
    public:
        // Material Interface
        using TaggedPointer::TaggedPointer;

        static Material Create( const std::string& name,
            const TextureParameterDictionary& parameters, Image* normalMap,
            /*const */ std::map<std::string, Material>& namedMaterials,
            const FileLoc* loc, Allocator alloc );

        std::string ToString( ) const;

        template <typename TextureEvaluator>
        inline BSDF GetBSDF( TextureEvaluator texEval, MaterialEvalContext ctx,
            SampledWavelengths& lambda, ScratchBuffer& buf ) const;

        template <typename TextureEvaluator>
        inline BSSRDF GetBSSRDF( TextureEvaluator texEval, MaterialEvalContext ctx,
            SampledWavelengths& lambda, ScratchBuffer& buf ) const;

        template <typename TextureEvaluator>
        PBRT_CPU_GPU inline bool CanEvaluateTextures( TextureEvaluator texEval ) const;

        PBRT_CPU_GPU inline const Image* GetNormalMap( ) const;

        PBRT_CPU_GPU inline FloatTexture GetDisplacement( ) const;

        PBRT_CPU_GPU inline bool HasSubsurfaceScattering( ) const;
    };

}

#endif
