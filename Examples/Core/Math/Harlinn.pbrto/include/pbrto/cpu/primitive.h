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

namespace pbrt
{

    STAT_MEMORY_COUNTER( "Memory/Primitives", primitiveMemory );

    class SimplePrimitive;
    class GeometricPrimitive;
    class TransformedPrimitive;
    class AnimatedPrimitive;
    class BVHAggregate;
    class KdTreeAggregate;

    // Primitive Definition
    class Primitive : public TaggedPointer<SimplePrimitive, GeometricPrimitive, TransformedPrimitive, AnimatedPrimitive, BVHAggregate, KdTreeAggregate>
    {
    public:
        // Primitive Interface
        using TaggedPointer::TaggedPointer;

        Bounds3f Bounds( ) const;

        pstd::optional<ShapeIntersection> Intersect( const Ray& r, Float tMax = Infinity ) const;
        bool IntersectP( const Ray& r, Float tMax = Infinity ) const;
    };

    // GeometricPrimitive Definition
    class GeometricPrimitive
    {
        // GeometricPrimitive Private Members
        Shape shape;
        Material material;
        Light areaLight;
        MediumInterface mediumInterface;
        FloatTexture alpha;
    public:
        // GeometricPrimitive Public Methods
        GeometricPrimitive( Shape shape, Material material, Light areaLight, const MediumInterface& mediumInterface, FloatTexture alpha = nullptr );
        Bounds3f Bounds( ) const;
        pstd::optional<ShapeIntersection> Intersect( const Ray& r, Float tMax ) const;
        bool IntersectP( const Ray& r, Float tMax ) const;
    };

    // SimplePrimitive Definition
    class SimplePrimitive
    {
        // SimplePrimitive Private Members
        Shape shape;
        Material material;
    public:
        // SimplePrimitive Public Methods

        SimplePrimitive( Shape shape, Material material );

        Bounds3f Bounds( ) const;
        pstd::optional<ShapeIntersection> Intersect( const Ray& r, Float tMax ) const;
        bool IntersectP( const Ray& r, Float tMax ) const;
        
    };

    // TransformedPrimitive Definition
    class TransformedPrimitive
    {
        // TransformedPrimitive Private Members
        Primitive primitive;
        const Transform* renderFromPrimitive;
    public:
        // TransformedPrimitive Public Methods
        TransformedPrimitive( Primitive primitive, const Transform* renderFromPrimitive )
            : primitive( primitive ), renderFromPrimitive( renderFromPrimitive )
        {
            primitiveMemory += sizeof( *this );
        }

        pstd::optional<ShapeIntersection> Intersect( const Ray& r, Float tMax ) const;
        bool IntersectP( const Ray& r, Float tMax ) const;

        Bounds3f Bounds( ) const 
        { 
            return ( *renderFromPrimitive )( primitive.Bounds( ) ); 
        }
    };

    // AnimatedPrimitive Definition
    class AnimatedPrimitive
    {
        // AnimatedPrimitive Private Members
        Primitive primitive;
        AnimatedTransform renderFromPrimitive;
    public:
        // AnimatedPrimitive Public Methods
        AnimatedPrimitive( Primitive primitive, const AnimatedTransform& renderFromPrimitive );

        Bounds3f Bounds( ) const
        {
            return renderFromPrimitive.MotionBounds( primitive.Bounds( ) );
        }

        
        pstd::optional<ShapeIntersection> Intersect( const Ray& r, Float tMax ) const;
        bool IntersectP( const Ray& r, Float tMax ) const;
    };

}  // namespace pbrt

#endif  // PBRT_CPU_PRIMITIVE_H
