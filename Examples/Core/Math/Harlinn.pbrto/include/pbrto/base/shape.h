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

#ifndef PBRT_BASE_SHAPE_H
#define PBRT_BASE_SHAPE_H

#include <pbrto/pbrt.h>

#include <pbrto/base/texture.h>
#include <pbrto/util/taggedptr.h>
#include <pbrto/util/vecmath.h>

#include <map>
#include <string>

namespace pbrt {

// Shape Declarations
class Triangle;
class BilinearPatch;
class Curve;
class Sphere;
class Cylinder;
class Disk;

struct ShapeSample;
struct ShapeIntersection;
struct ShapeSampleContext;

// Shape Definition
class Shape
    : public TaggedPointer<Sphere, Cylinder, Disk, Triangle, BilinearPatch, Curve> {
  public:
    // Shape Interface
    using TaggedPointer::TaggedPointer;

    static pstd::vector<Shape> Create(
        const std::string &name, const Transform *renderFromObject,
        const Transform *objectFromRender, bool reverseOrientation,
        const ParameterDictionary &parameters,
        const std::map<std::string, FloatTexture> &floatTextures, const FileLoc *loc,
        Allocator alloc);
    std::string ToString() const;

    PBRT_CPU_GPU inline Bounds3f Bounds() const;

    PBRT_CPU_GPU inline DirectionCone NormalBounds() const;

    PBRT_CPU_GPU inline pstd::optional<ShapeIntersection> Intersect(
        const Ray &ray, Float tMax = Infinity) const;

    PBRT_CPU_GPU inline bool IntersectP(const Ray &ray, Float tMax = Infinity) const;

    PBRT_CPU_GPU inline Float Area() const;

    PBRT_CPU_GPU inline pstd::optional<ShapeSample> Sample(Point2f u) const;

    PBRT_CPU_GPU inline Float PDF(const Interaction &) const;

    PBRT_CPU_GPU inline pstd::optional<ShapeSample> Sample(const ShapeSampleContext &ctx,
                                                           Point2f u) const;

    PBRT_CPU_GPU inline Float PDF(const ShapeSampleContext &ctx, Vector3f wi) const;
};

}  // namespace pbrt

#endif  // PBRT_BASE_SHAPE_H
