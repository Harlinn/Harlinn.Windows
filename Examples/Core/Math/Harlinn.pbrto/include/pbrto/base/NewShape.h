#pragma once
#ifndef PBRTO_BASE_NEWSHAPE_H_
#define PBRTO_BASE_NEWSHAPE_H_

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

#include <pbrto/NewPbrt.h>

#include <pbrto/base/NewTexture.h>
#include <pbrto/util/NewVecmath.h>

#include <map>
#include <string>

namespace pbrto
{

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
        : public TaggedPointer<Sphere, Cylinder, Disk, Triangle, BilinearPatch, Curve>
    {
    public:
        // Shape Interface
        using TaggedPointer::TaggedPointer;

        static pstdo::vector<Shape> Create(
            const std::string& name, const Transform* renderFromObject,
            const Transform* objectFromRender, bool reverseOrientation,
            const ParameterDictionary& parameters,
            const std::map<std::string, FloatTexture>& floatTextures, const FileLoc* loc,
            Allocator alloc );
        std::string ToString( ) const;

        inline Bounds3f Bounds( ) const;

        inline DirectionCone NormalBounds( ) const;

        inline pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax = Infinity ) const;

        inline bool IntersectP( const Ray& ray, Float tMax = Infinity ) const;

        inline Float Area( ) const;

        inline pstdo::optional<ShapeSample> Sample( Point2f u ) const;

        inline Float PDF( const Interaction& ) const;

        inline pstdo::optional<ShapeSample> Sample( const ShapeSampleContext& ctx, Point2f u ) const;

        inline Float PDF( const ShapeSampleContext& ctx, Vector3f::Simd wi ) const;
    };

}

#endif
