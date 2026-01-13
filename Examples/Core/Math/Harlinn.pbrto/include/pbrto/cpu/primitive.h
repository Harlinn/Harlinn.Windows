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

#ifndef PBRT_CPU_PRIMITIVE_H
#define PBRT_CPU_PRIMITIVE_H

#include <pbrto/pbrt.h>

#include <pbrto/base/light.h>
#include <pbrto/base/material.h>
#include <pbrto/base/medium.h>
#include <pbrto/base/shape.h>
#include <pbrto/base/texture.h>
#include <pbrto/util/stats.h>
#include <pbrto/util/taggedptr.h>
#include <pbrto/util/transform.h>

#include <memory>

namespace pbrt {

STAT_MEMORY_COUNTER("Memory/Primitives", primitiveMemory);

class SimplePrimitive;
class GeometricPrimitive;
class TransformedPrimitive;
class AnimatedPrimitive;
class BVHAggregate;
class KdTreeAggregate;

// Primitive Definition
class Primitive
    : public TaggedPointer<SimplePrimitive, GeometricPrimitive, TransformedPrimitive,
                           AnimatedPrimitive, BVHAggregate, KdTreeAggregate> {
  public:
    // Primitive Interface
    using TaggedPointer::TaggedPointer;

    Bounds3f Bounds() const;

    pstd::optional<ShapeIntersection> Intersect(const Ray &r,
                                                Float tMax = Infinity) const;
    bool IntersectP(const Ray &r, Float tMax = Infinity) const;
};

// GeometricPrimitive Definition
class GeometricPrimitive {
  public:
    // GeometricPrimitive Public Methods
    GeometricPrimitive(Shape shape, Material material, Light areaLight,
                       const MediumInterface &mediumInterface,
                       FloatTexture alpha = nullptr);
    Bounds3f Bounds() const;
    pstd::optional<ShapeIntersection> Intersect(const Ray &r, Float tMax) const;
    bool IntersectP(const Ray &r, Float tMax) const;

  private:
    // GeometricPrimitive Private Members
    Shape shape;
    Material material;
    Light areaLight;
    MediumInterface mediumInterface;
    FloatTexture alpha;
};

// SimplePrimitive Definition
class SimplePrimitive {
  public:
    // SimplePrimitive Public Methods
    Bounds3f Bounds() const;
    pstd::optional<ShapeIntersection> Intersect(const Ray &r, Float tMax) const;
    bool IntersectP(const Ray &r, Float tMax) const;
    SimplePrimitive(Shape shape, Material material);

  private:
    // SimplePrimitive Private Members
    Shape shape;
    Material material;
};

// TransformedPrimitive Definition
class TransformedPrimitive {
  public:
    // TransformedPrimitive Public Methods
    TransformedPrimitive(Primitive primitive, const Transform *renderFromPrimitive)
        : primitive(primitive), renderFromPrimitive(renderFromPrimitive) {
        primitiveMemory += sizeof(*this);
    }

    pstd::optional<ShapeIntersection> Intersect(const Ray &r, Float tMax) const;
    bool IntersectP(const Ray &r, Float tMax) const;

    Bounds3f Bounds() const { return (*renderFromPrimitive)(primitive.Bounds()); }

  private:
    // TransformedPrimitive Private Members
    Primitive primitive;
    const Transform *renderFromPrimitive;
};

// AnimatedPrimitive Definition
class AnimatedPrimitive {
  public:
    // AnimatedPrimitive Public Methods
    Bounds3f Bounds() const {
        return renderFromPrimitive.MotionBounds(primitive.Bounds());
    }

    AnimatedPrimitive(Primitive primitive, const AnimatedTransform &renderFromPrimitive);
    pstd::optional<ShapeIntersection> Intersect(const Ray &r, Float tMax) const;
    bool IntersectP(const Ray &r, Float tMax) const;

  private:
    // AnimatedPrimitive Private Members
    Primitive primitive;
    AnimatedTransform renderFromPrimitive;
};

}  // namespace pbrt

#endif  // PBRT_CPU_PRIMITIVE_H
