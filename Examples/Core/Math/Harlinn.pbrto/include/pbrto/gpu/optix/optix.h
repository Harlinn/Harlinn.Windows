// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_GPU_OPTIX_OPTIX_H
#define PBRT_GPU_OPTIX_OPTIX_H

#include <pbrto/pbrt.h>

#include <pbrto/base/light.h>
#include <pbrto/base/material.h>
#include <pbrto/base/medium.h>
#include <pbrto/base/shape.h>
#include <pbrto/base/texture.h>
#include <pbrto/util/pstd.h>
#include <pbrto/wavefront/workitems.h>
#include <pbrto/wavefront/workqueue.h>

#include <optix.h>

namespace pbrt {

class TriangleMesh;
class BilinearPatchMesh;

struct TriangleMeshRecord {
    const TriangleMesh *mesh;
    Material material;
    FloatTexture alphaTexture;
    pstd::span<Light> areaLights;
    MediumInterface *mediumInterface;
};

struct BilinearMeshRecord {
    const BilinearPatchMesh *mesh;
    Material material;
    FloatTexture alphaTexture;
    pstd::span<Light> areaLights;
    MediumInterface *mediumInterface;
};

struct QuadricRecord {
    Shape shape;
    Material material;
    FloatTexture alphaTexture;
    Light areaLight;
    MediumInterface *mediumInterface;
};

struct RayIntersectParameters {
    OptixTraversableHandle traversable;

    const RayQueue *rayQueue;

    // closest hit
    RayQueue *nextRayQueue;
    EscapedRayQueue *escapedRayQueue;
    HitAreaLightQueue *hitAreaLightQueue;
    MaterialEvalQueue *basicEvalMaterialQueue, *universalEvalMaterialQueue;
    MediumSampleQueue *mediumSampleQueue;

    // shadow rays
    ShadowRayQueue *shadowRayQueue;
    SOA<PixelSampleState> pixelSampleState;

    // Subsurface scattering...
    SubsurfaceScatterQueue *subsurfaceScatterQueue;
};

}  // namespace pbrt

#endif  // PBRT_GPU_OPTIX_OPTIX_H
