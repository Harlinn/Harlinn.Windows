#include "pch.h"

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

#include <pbrto/cpu/NewPrimitive.h>

#include <pbrto/cpu/NewAggregates.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/NewMaterials.h>
#include <pbrto/NewShapes.h>
#include <pbrto/NewTextures.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewLog.h>
#include <pbrto/util/NewTaggedPtr.h>
#include <pbrto/util/NewVecMath.h>

namespace pbrto
{

    Bounds3f Primitive::Bounds( ) const
    {
        auto bounds = [ & ]( auto ptr ) { return ptr->Bounds( ); };
        return DispatchCPU( bounds );
    }

    pstdo::optional<ShapeIntersection> Primitive::Intersect( const Ray& r, Float tMax ) const
    {
        auto isect = [ & ]( auto ptr ) { return ptr->Intersect( r, tMax ); };
        return DispatchCPU( isect );
    }

    bool Primitive::IntersectP( const Ray& r, Float tMax ) const
    {
        auto isectp = [ & ]( auto ptr ) { return ptr->IntersectP( r, tMax ); };
        return DispatchCPU( isectp );
    }

    // GeometricPrimitive Method Definitions
    GeometricPrimitive::GeometricPrimitive( Shape shape, Material material, Light areaLight,
        const MediumInterface& mediumInterface,
        FloatTexture alpha )
        : shape( shape ),
        material( material ),
        areaLight( areaLight ),
        mediumInterface( mediumInterface ),
        alpha( alpha )
    {
        primitiveMemory += sizeof( *this );
    }

    Bounds3f GeometricPrimitive::Bounds( ) const
    {
        return shape.Bounds( );
    }

    pstdo::optional<ShapeIntersection> GeometricPrimitive::Intersect( const Ray& r,
        Float tMax ) const
    {
        pstdo::optional<ShapeIntersection> si = shape.Intersect( r, tMax );
        if ( !si )
            return {};
        NCHECK_LT( si->tHit, 1.001 * tMax );
        // Test intersection against alpha texture, if present
        if ( alpha )
        {
            if ( Float a = alpha.Evaluate( si->intr ); a < 1 )
            {
                // Possibly ignore intersection based on stochastic alpha test
                Float u = ( a <= 0 ) ? 1.f : HashFloat( r.o, r.d );
                if ( u > a )
                {
                    // Ignore this intersection and trace a new ray
                    Ray rNext = si->intr.SpawnRay( r.d );
                    pstdo::optional<ShapeIntersection> siNext =
                        Intersect( rNext, tMax - si->tHit );
                    if ( siNext )
                        siNext->tHit += si->tHit;
                    return siNext;
                }
            }
        }

        // Initialize _SurfaceInteraction_ after _Shape_ intersection
        si->intr.SetIntersectionProperties( material, areaLight, &mediumInterface, r.medium );

        return si;
    }

    bool GeometricPrimitive::IntersectP( const Ray& r, Float tMax ) const
    {
        if ( alpha )
            return Intersect( r, tMax ).has_value( );
        else
            return shape.IntersectP( r, tMax );
    }

    // SimplePrimitive Method Definitions
    SimplePrimitive::SimplePrimitive( Shape shape, Material material )
        : shape( shape ), material( material )
    {
        primitiveMemory += sizeof( *this );
    }

    Bounds3f SimplePrimitive::Bounds( ) const
    {
        return shape.Bounds( );
    }

    bool SimplePrimitive::IntersectP( const Ray& r, Float tMax ) const
    {
        return shape.IntersectP( r, tMax );
    }

    pstdo::optional<ShapeIntersection> SimplePrimitive::Intersect( const Ray& r,
        Float tMax ) const
    {
        pstdo::optional<ShapeIntersection> si = shape.Intersect( r, tMax );
        if ( !si )
            return {};

        si->intr.SetIntersectionProperties( material, nullptr, nullptr, r.medium );

        return si;
    }

    // TransformedPrimitive Method Definitions
    pstdo::optional<ShapeIntersection> TransformedPrimitive::Intersect( const Ray& r,
        Float tMax ) const
    {
        // Transform ray to primitive-space and intersect with primitive
        Ray ray = renderFromPrimitive->ApplyInverse( r, &tMax );
        pstdo::optional<ShapeIntersection> si = primitive.Intersect( ray, tMax );
        if ( !si )
            return {};
        NCHECK_LT( si->tHit, 1.001 * tMax );

        // Return transformed instance's intersection information
        si->intr = ( *renderFromPrimitive )( si->intr );
        NCHECK_GE( ScalarDot( si->intr.n, si->intr.shading.n ), 0 );
        return si;
    }

    bool TransformedPrimitive::IntersectP( const Ray& r, Float tMax ) const
    {
        Ray ray = renderFromPrimitive->ApplyInverse( r, &tMax );
        return primitive.IntersectP( ray, tMax );
    }

    // AnimatedPrimitive Method Definitions
    AnimatedPrimitive::AnimatedPrimitive( Primitive p,
        const AnimatedTransform& renderFromPrimitive )
        : primitive( p ), renderFromPrimitive( renderFromPrimitive )
    {
        primitiveMemory += sizeof( *this );
        NCHECK( renderFromPrimitive.IsAnimated( ) );
    }

    pstdo::optional<ShapeIntersection> AnimatedPrimitive::Intersect( const Ray& r,
        Float tMax ) const
    {
        // Compute _ray_ after transformation by _renderFromPrimitive_
        Transform interpRenderFromPrimitive = renderFromPrimitive.Interpolate( r.time );
        Ray ray = interpRenderFromPrimitive.ApplyInverse( r, &tMax );
        pstdo::optional<ShapeIntersection> si = primitive.Intersect( ray, tMax );
        if ( !si )
            return {};

        // Transform instance's intersection data to rendering space
        si->intr = interpRenderFromPrimitive( si->intr );
        NCHECK_GE( ScalarDot( si->intr.n, si->intr.shading.n ), 0 );
        return si;
    }

    bool AnimatedPrimitive::IntersectP( const Ray& r, Float tMax ) const
    {
        Ray ray = renderFromPrimitive.ApplyInverse( r, &tMax );
        return primitive.IntersectP( ray, tMax );
    }

}
