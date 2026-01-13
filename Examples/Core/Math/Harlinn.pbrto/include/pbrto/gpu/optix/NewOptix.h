/*
    Copyright 2024-2026 Espen Harlinn
 
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

#ifndef PBRT_GPU_OPTIX_OPTIX_H
#define PBRT_GPU_OPTIX_OPTIX_H

#include <pbrto/NewPbrt.h>

#include <pbrto/base/NewLight.h>
#include <pbrto/base/NewMaterial.h>
#include <pbrto/base/NewMedium.h>
#include <pbrto/base/NewShape.h>
#include <pbrto/base/NewTexture.h>
#include <pbrto/util/NewPstd.h>
#include <pbrto/wavefront/NewWorkitems.h>
#include <pbrto/wavefront/NewWorkqueue.h>

#include <optix.h>

namespace pbrto
{

    class TriangleMesh;
    class BilinearPatchMesh;

    struct TriangleMeshRecord
    {
        const TriangleMesh* mesh;
        Material material;
        FloatTexture alphaTexture;
        pstdo::span<Light> areaLights;
        MediumInterface* mediumInterface;
    };

    struct BilinearMeshRecord
    {
        const BilinearPatchMesh* mesh;
        Material material;
        FloatTexture alphaTexture;
        pstdo::span<Light> areaLights;
        MediumInterface* mediumInterface;
    };

    struct QuadricRecord
    {
        Shape shape;
        Material material;
        FloatTexture alphaTexture;
        Light areaLight;
        MediumInterface* mediumInterface;
    };

    struct RayIntersectParameters
    {
        OptixTraversableHandle traversable;

        const RayQueue* rayQueue;

        // closest hit
        RayQueue* nextRayQueue;
        EscapedRayQueue* escapedRayQueue;
        HitAreaLightQueue* hitAreaLightQueue;
        MaterialEvalQueue* basicEvalMaterialQueue, * universalEvalMaterialQueue;
        MediumSampleQueue* mediumSampleQueue;

        // shadow rays
        ShadowRayQueue* shadowRayQueue;
        SOA<PixelSampleState> pixelSampleState;

        // Subsurface scattering...
        SubsurfaceScatterQueue* subsurfaceScatterQueue;
    };

}  // namespace pbrt

#endif  // PBRT_GPU_OPTIX_OPTIX_H
