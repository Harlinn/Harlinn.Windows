#pragma once
#ifndef PBRTO_WAVEFRONT_NEWAGGREGATE_H_
#define PBRTO_WAVEFRONT_NEWAGGREGATE_H_

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

#include <pbrto/cpu/NewPrimitive.h>
#include <pbrto/NewLights.h>
#include <pbrto/NewMaterials.h>
#include <pbrto/NewScene.h>
#include <pbrto/util/NewContainers.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewSoa.h>
#include <pbrto/wavefront/NewIntegrator.h>
#include <pbrto/wavefront/NewWorkitems.h>

#include <map>
#include <string>

namespace pbrto
{

    class CPUAggregate : public WavefrontAggregate
    {
    public:
        CPUAggregate( BasicScene& scene, NamedTextures& textures,
            const std::map<int, pstdo::vector<Light>*>& shapeIndexToAreaLights,
            const std::map<std::string, Medium>& media,
            const std::map<std::string, pbrto::Material>& namedMaterials,
            const std::vector<pbrto::Material>& materials );

        Bounds3f Bounds( ) const { return aggregate ? aggregate.Bounds( ) : Bounds3f( ); }

        void IntersectClosest( int maxRays, const RayQueue* rayQueue,
            EscapedRayQueue* escapedRayQueue,
            HitAreaLightQueue* hitAreaLightQueue,
            MaterialEvalQueue* basicEvalMaterialQueue,
            MaterialEvalQueue* universalEvalMaterialQueue,
            MediumSampleQueue* mediumSampleQueue,
            RayQueue* nextRayQueue ) const;

        void IntersectShadow( int maxRays, ShadowRayQueue* shadowRayQueue,
            SOA<PixelSampleState>* pixelSampleState ) const;

        void IntersectShadowTr( int maxRays, ShadowRayQueue* shadowRayQueue,
            SOA<PixelSampleState>* pixelSampleState ) const;

        void IntersectOneRandom( int maxRays,
            SubsurfaceScatterQueue* subsurfaceScatterQueue ) const;

    private:
        Primitive aggregate;
    };

}

#endif
