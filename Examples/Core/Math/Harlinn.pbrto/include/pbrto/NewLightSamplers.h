#pragma once
#ifndef PBRTO_NEWLIGHTSAMPLERS_H_
#define PBRTO_NEWLIGHTSAMPLERS_H_

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

#include <pbrto/base/NewLight.h>
#include <pbrto/base/NewLightSampler.h>
#include <pbrto/NewLights.h>  // LightBounds. Should that live elsewhere?
#include <pbrto/util/NewContainers.h>
#include <pbrto/util/NewHash.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewVecMath.h>

#include <algorithm>
#include <cstdint>
#include <string>

namespace pbrto
{

    // UniformLightSampler Definition
    class UniformLightSampler
    {
    public:
        // UniformLightSampler Public Methods
        UniformLightSampler( pstdo::span<const Light> lights, Allocator alloc )
            : lights( lights.begin( ), lights.end( ), alloc )
        {
        }

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( Float u ) const
        {
            if ( lights.empty( ) )
                return {};
            int lightIndex = std::min<int>( u * lights.size( ), lights.size( ) - 1 );
            return SampledLight{ lights[ lightIndex ], 1.f / lights.size( ) };
        }

        PBRT_CPU_GPU
            Float PMF( Light light ) const
        {
            if ( lights.empty( ) )
                return 0;
            return 1.f / lights.size( );
        }

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( const LightSampleContext& ctx, Float u ) const
        {
            return Sample( u );
        }

        PBRT_CPU_GPU
            Float PMF( const LightSampleContext& ctx, Light light ) const { return PMF( light ); }

        std::string ToString( ) const { return "UniformLightSampler"; }

    private:
        // UniformLightSampler Private Members
        pstdo::vector<Light> lights;
    };

    // PowerLightSampler Definition
    class PowerLightSampler
    {
    public:
        // PowerLightSampler Public Methods
        PowerLightSampler( pstdo::span<const Light> lights, Allocator alloc );

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( Float u ) const
        {
            if ( !aliasTable.size( ) )
                return {};
            Float pmf;
            int lightIndex = aliasTable.Sample( u, &pmf );
            return SampledLight{ lights[ lightIndex ], pmf };
        }

        PBRT_CPU_GPU
            Float PMF( Light light ) const
        {
            if ( !aliasTable.size( ) )
                return 0;
            return aliasTable.PMF( lightToIndex[ light ] );
        }

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( const LightSampleContext& ctx, Float u ) const
        {
            return Sample( u );
        }

        PBRT_CPU_GPU
            Float PMF( const LightSampleContext& ctx, Light light ) const { return PMF( light ); }

        std::string ToString( ) const;

    private:
        // PowerLightSampler Private Members
        pstdo::vector<Light> lights;
        HashMap<Light, size_t> lightToIndex;
        AliasTable aliasTable;
    };

    // CompactLightBounds Definition
    class CompactLightBounds
    {
    public:
        // CompactLightBounds Public Methods
        CompactLightBounds( ) = default;

        PBRT_CPU_GPU
            CompactLightBounds( const LightBounds& lb, const Bounds3f& allb )
            : w( Normalize( lb.w ) ),
            phi( lb.phi ),
            qCosTheta_o( QuantizeCos( lb.cosTheta_o ) ),
            qCosTheta_e( QuantizeCos( lb.cosTheta_e ) ),
            twoSided( lb.twoSided )
        {
            // Quantize bounding box into _qb_
            for ( int c = 0; c < 3; ++c )
            {
                qb[ 0 ][ c ] =
                    pstdo::floor( QuantizeBounds( lb.bounds[ 0 ][ c ], allb.pMin[ c ], allb.pMax[ c ] ) );
                qb[ 1 ][ c ] =
                    pstdo::ceil( QuantizeBounds( lb.bounds[ 1 ][ c ], allb.pMin[ c ], allb.pMax[ c ] ) );
            }
        }

        std::string ToString( ) const;
        std::string ToString( const Bounds3f& allBounds ) const;

        PBRT_CPU_GPU
            bool TwoSided( ) const { return twoSided; }
        PBRT_CPU_GPU
            Float CosTheta_o( ) const { return 2 * ( qCosTheta_o / 32767.f ) - 1; }
        PBRT_CPU_GPU
            Float CosTheta_e( ) const { return 2 * ( qCosTheta_e / 32767.f ) - 1; }

        PBRT_CPU_GPU
            Bounds3f Bounds( const Bounds3f& allb ) const
        {
            return { Point3f( Lerp2( qb[ 0 ][ 0 ] / 65535.f, allb.pMin.x, allb.pMax.x ),
                            Lerp2( qb[ 0 ][ 1 ] / 65535.f, allb.pMin.y, allb.pMax.y ),
                            Lerp2( qb[ 0 ][ 2 ] / 65535.f, allb.pMin.z, allb.pMax.z ) ),
                    Point3f( Lerp2( qb[ 1 ][ 0 ] / 65535.f, allb.pMin.x, allb.pMax.x ),
                            Lerp2( qb[ 1 ][ 1 ] / 65535.f, allb.pMin.y, allb.pMax.y ),
                            Lerp2( qb[ 1 ][ 2 ] / 65535.f, allb.pMin.z, allb.pMax.z ) ) };
        }

        PBRT_CPU_GPU
            Float Importance( Point3f p, Normal3f n, const Bounds3f& allb ) const
        {
            Bounds3f bounds = Bounds( allb );
            Float cosTheta_o = CosTheta_o( ), cosTheta_e = CosTheta_e( );
            // Return importance for light bounds at reference point
            // Compute clamped squared distance to reference point
            Point3f pc = ( bounds.pMin + bounds.pMax ) / 2;
            Float d2 = ScalarDistanceSquared( p, pc );
            d2 = std::max( d2, ScalarLength( bounds.Diagonal( ) ) / 2 );

            // Define cosine and sine clamped subtraction lambdas
            auto cosSubClamped = []( Float sinTheta_a, Float cosTheta_a, Float sinTheta_b,
                Float cosTheta_b ) -> Float {
                    if ( cosTheta_a > cosTheta_b )
                        return 1;
                    return cosTheta_a * cosTheta_b + sinTheta_a * sinTheta_b;
                };

            auto sinSubClamped = []( Float sinTheta_a, Float cosTheta_a, Float sinTheta_b,
                Float cosTheta_b ) -> Float {
                    if ( cosTheta_a > cosTheta_b )
                        return 0;
                    return sinTheta_a * cosTheta_b - cosTheta_a * sinTheta_b;
                };

            // Compute sine and cosine of angle to vector _w_, $\theta_\roman{w}$
            Vector3f wi = Normalize( p - pc );
            Float cosTheta_w = ScalarDot( Vector3f( w ), wi );
            if ( twoSided )
                cosTheta_w = Math::FastAbs( cosTheta_w );
            Float sinTheta_w = SafeSqrt( 1 - Sqr( cosTheta_w ) );

            // Compute $\cos\,\theta_\roman{\+b}$ for reference point
            Float cosTheta_b = BoundSubtendedDirections( bounds, p ).cosTheta;
            Float sinTheta_b = SafeSqrt( 1 - Sqr( cosTheta_b ) );

            // Compute $\cos\,\theta'$ and test against $\cos\,\theta_\roman{e}$
            Float sinTheta_o = SafeSqrt( 1 - Sqr( cosTheta_o ) );
            Float cosTheta_x = cosSubClamped( sinTheta_w, cosTheta_w, sinTheta_o, cosTheta_o );
            Float sinTheta_x = sinSubClamped( sinTheta_w, cosTheta_w, sinTheta_o, cosTheta_o );
            Float cosThetap = cosSubClamped( sinTheta_x, cosTheta_x, sinTheta_b, cosTheta_b );
            if ( cosThetap <= cosTheta_e )
                return 0;

            // Return final importance at reference point
            Float importance = phi * cosThetap / d2;
            NDCHECK_GE( importance, -1e-3 );
            // Account for $\cos\theta_\roman{i}$ in importance at surfaces
            if ( n != Normal3f( 0, 0, 0 ) )
            {
                Float cosTheta_i = ScalarAbsDot( wi, n );
                Float sinTheta_i = SafeSqrt( 1 - Sqr( cosTheta_i ) );
                Float cosThetap_i =
                    cosSubClamped( sinTheta_i, cosTheta_i, sinTheta_b, cosTheta_b );
                importance *= cosThetap_i;
            }

            importance = std::max<Float>( importance, 0 );
            return importance;
        }

    private:
        // CompactLightBounds Private Methods
        PBRT_CPU_GPU
            static unsigned int QuantizeCos( Float c )
        {
            NCHECK( c >= -1 && c <= 1 );
            return pstdo::floor( 32767.f * ( ( c + 1 ) / 2 ) );
        }

        PBRT_CPU_GPU
            static Float QuantizeBounds( Float c, Float min, Float max )
        {
            NCHECK( c >= min && c <= max );
            if ( min == max )
                return 0;
            return 65535.f * Clamp( ( c - min ) / ( max - min ), 0, 1 );
        }

        // CompactLightBounds Private Members
        OctahedralVector w;
        Float phi = 0;
        struct
        {
            unsigned int qCosTheta_o : 15;
            unsigned int qCosTheta_e : 15;
            unsigned int twoSided : 1;
        };
        uint16_t qb[ 2 ][ 3 ];
    };

    // LightBVHNode Definition
    struct alignas( 32 ) LightBVHNode
    {
        // LightBVHNode Public Methods
        LightBVHNode( ) = default;

        LightBVHNode( const CompactLightBounds& cb, unsigned int index, bool isLightIndex )
            : lightBounds( cb ), childOrLightIndex( index ), isLeaf( isLightIndex ? 1 : 0 )
        {
        }

        PBRT_CPU_GPU
            static LightBVHNode MakeLeaf( unsigned int lightIndex, const CompactLightBounds& cb )
        {
            return LightBVHNode( cb, lightIndex, true );
        }

        PBRT_CPU_GPU
            static LightBVHNode MakeInterior( unsigned int child1Index,
                const CompactLightBounds& cb )
        {
            return LightBVHNode( cb, child1Index, false );
        }

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( const LightSampleContext& ctx, Float u ) const;

        std::string ToString( ) const;

        // LightBVHNode Public Members
        CompactLightBounds lightBounds;
        struct
        {
            unsigned int childOrLightIndex : 31;
            unsigned int isLeaf : 1;
        };
    };

    // BVHLightSampler Definition
    class BVHLightSampler
    {
    public:
        // BVHLightSampler Public Methods
        PBRTO_EXPORT BVHLightSampler( pstdo::span<const Light> lights, Allocator alloc );

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( const LightSampleContext& ctx, Float u ) const
        {
            // Compute infinite light sampling probability _pInfinite_
            Float pInfinite = Float( infiniteLights.size( ) ) /
                Float( infiniteLights.size( ) + ( nodes.empty( ) ? 0 : 1 ) );

            if ( u < pInfinite )
            {
                // Sample infinite lights with uniform probability
                u /= pInfinite;
                int index =
                    std::min<int>( u * infiniteLights.size( ), infiniteLights.size( ) - 1 );
                Float pmf = pInfinite / infiniteLights.size( );
                return SampledLight{ infiniteLights[ index ], pmf };

            }
            else
            {
                // Traverse light BVH to sample light
                if ( nodes.empty( ) )
                    return {};
                // Declare common variables for light BVH traversal
                Point3f p = ctx.p( );
                Normal3f n = ctx.ns;
                u = std::min<Float>( ( u - pInfinite ) / ( 1 - pInfinite ), OneMinusEpsilon );
                int nodeIndex = 0;
                Float pmf = 1 - pInfinite;

                while ( true )
                {
                    // Process light BVH node for light sampling
                    LightBVHNode node = nodes[ nodeIndex ];
                    if ( !node.isLeaf )
                    {
                        // Compute light BVH child node importances
                        const LightBVHNode* children[ 2 ] = { &nodes[ nodeIndex + 1 ],
                                                           &nodes[ node.childOrLightIndex ] };
                        std::array < Float, 2> ci = {
                            children[ 0 ]->lightBounds.Importance( p, n, allLightBounds ),
                            children[ 1 ]->lightBounds.Importance( p, n, allLightBounds ) };
                        if ( ci[ 0 ] == 0 && ci[ 1 ] == 0 )
                            return {};

                        // Randomly sample light BVH child node
                        Float nodePMF;
                        int child = SampleDiscrete( ci, u, &nodePMF, &u );
                        pmf *= nodePMF;
                        nodeIndex = ( child == 0 ) ? ( nodeIndex + 1 ) : node.childOrLightIndex;

                    }
                    else
                    {
                        // Confirm light has nonzero importance before returning light sample
                        if ( nodeIndex > 0 )
                            NDCHECK_GT( node.lightBounds.Importance( p, n, allLightBounds ), 0 );
                        if ( nodeIndex > 0 ||
                            node.lightBounds.Importance( p, n, allLightBounds ) > 0 )
                            return SampledLight{ lights[ node.childOrLightIndex ], pmf };
                        return {};
                    }
                }
            }
        }

        PBRT_CPU_GPU
            Float PMF( const LightSampleContext& ctx, Light light ) const
        {
            // Handle infinite _light_ PMF computation
            if ( !lightToBitTrail.HasKey( light ) )
                return 1.f / ( infiniteLights.size( ) + ( nodes.empty( ) ? 0 : 1 ) );

            // Initialize local variables for BVH traversal for PMF computation
            uint32_t bitTrail = lightToBitTrail[ light ];
            Point3f p = ctx.p( );
            Normal3f n = ctx.ns;
            // Compute infinite light sampling probability _pInfinite_
            Float pInfinite = Float( infiniteLights.size( ) ) /
                Float( infiniteLights.size( ) + ( nodes.empty( ) ? 0 : 1 ) );

            Float pmf = 1 - pInfinite;
            int nodeIndex = 0;

            // Compute light's PMF by walking down tree nodes to the light
            while ( true )
            {
                const LightBVHNode* node = &nodes[ nodeIndex ];
                if ( node->isLeaf )
                {
                    NDCHECK_EQ( light, lights[ node->childOrLightIndex ] );
                    return pmf;
                }
                // Compute child importances and update PMF for current node
                const LightBVHNode* child0 = &nodes[ nodeIndex + 1 ];
                const LightBVHNode* child1 = &nodes[ node->childOrLightIndex ];
                Float ci[ 2 ] = { child0->lightBounds.Importance( p, n, allLightBounds ),
                               child1->lightBounds.Importance( p, n, allLightBounds ) };
                NDCHECK_GT( ci[ bitTrail & 1 ], 0 );
                pmf *= ci[ bitTrail & 1 ] / ( ci[ 0 ] + ci[ 1 ] );

                // Use _bitTrail_ to find next node index and update its value
                nodeIndex = ( bitTrail & 1 ) ? node->childOrLightIndex : ( nodeIndex + 1 );
                bitTrail >>= 1;
            }
        }

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( Float u ) const
        {
            if ( lights.empty( ) )
                return {};
            int lightIndex = std::min<int>( u * lights.size( ), lights.size( ) - 1 );
            return SampledLight{ lights[ lightIndex ], 1.f / lights.size( ) };
        }

        PBRT_CPU_GPU
            Float PMF( Light light ) const
        {
            if ( lights.empty( ) )
                return 0;
            return 1.f / lights.size( );
        }

        std::string ToString( ) const;

    private:
        // BVHLightSampler Private Methods
        std::pair<int, LightBounds> buildBVH(
            std::vector<std::pair<int, LightBounds>>& bvhLights, int start, int end,
            uint32_t bitTrail, int depth );

        Float EvaluateCost( const LightBounds& b, const Bounds3f& bounds, int dim ) const
        {
            // Evaluate direction bounds measure for _LightBounds_
            Float theta_o = Math::ACos( b.cosTheta_o ), theta_e = Math::ACos( b.cosTheta_e );
            Float theta_w = std::min( theta_o + theta_e, Pi );
            Float sinTheta_o = SafeSqrt( 1 - Sqr( b.cosTheta_o ) );

            Float M_omega = 2 * Pi * ( 1 - b.cosTheta_o ) +
                Pi / 2 *
                ( 2 * theta_w * sinTheta_o - Math::Cos( theta_o - 2 * theta_w ) -
                    2 * theta_o * sinTheta_o + b.cosTheta_o );

            // Return complete cost estimate for _LightBounds_
            Float Kr = MaxComponentValue( bounds.Diagonal( ) ) / bounds.Diagonal( )[ dim ];
            return b.phi * M_omega * Kr * b.bounds.SurfaceArea( );
        }

        // BVHLightSampler Private Members
        pstdo::vector<Light> lights;
        pstdo::vector<Light> infiniteLights;
        Bounds3f allLightBounds;
        pstdo::vector<LightBVHNode> nodes;
        HashMap<Light, uint32_t> lightToBitTrail;
    };

    // ExhaustiveLightSampler Definition
    class ExhaustiveLightSampler
    {
    public:
        ExhaustiveLightSampler( pstdo::span<const Light> lights, Allocator alloc );

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( const LightSampleContext& ctx, Float u ) const;

        PBRT_CPU_GPU
            Float PMF( const LightSampleContext& ctx, Light light ) const;

        PBRT_CPU_GPU
            pstdo::optional<SampledLight> Sample( Float u ) const
        {
            if ( lights.empty( ) )
                return {};

            int lightIndex = std::min<int>( u * lights.size( ), lights.size( ) - 1 );
            return SampledLight{ lights[ lightIndex ], 1.f / lights.size( ) };
        }

        PBRT_CPU_GPU
            Float PMF( Light light ) const
        {
            if ( lights.empty( ) )
                return 0;
            return 1.f / lights.size( );
        }

        std::string ToString( ) const;

    private:
        pstdo::vector<Light> lights, boundedLights, infiniteLights;
        pstdo::vector<LightBounds> lightBounds;
        HashMap<Light, size_t> lightToBoundedIndex;
    };

    PBRT_CPU_GPU inline pstdo::optional<SampledLight> LightSampler::Sample( const LightSampleContext& ctx,
        Float u ) const
    {
        auto s = [ & ]( auto ptr ) { return ptr->Sample( ctx, u ); };
        return Dispatch( s );
    }

    PBRT_CPU_GPU inline Float LightSampler::PMF( const LightSampleContext& ctx, Light light ) const
    {
        auto pdf = [ & ]( auto ptr ) { return ptr->PMF( ctx, light ); };
        return Dispatch( pdf );
    }

    PBRT_CPU_GPU inline pstdo::optional<SampledLight> LightSampler::Sample( Float u ) const
    {
        auto sample = [ & ]( auto ptr ) { return ptr->Sample( u ); };
        return Dispatch( sample );
    }

    PBRT_CPU_GPU inline Float LightSampler::PMF( Light light ) const
    {
        auto pdf = [ & ]( auto ptr ) { return ptr->PMF( light ); };
        return Dispatch( pdf );
    }

}

#endif
