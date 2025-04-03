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

#include <pbrto/NewLightSamplers.h>

#include <pbrto/NewInteraction.h>
#include <pbrto/NewLights.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewError.h>
#include <pbrto/util/NewHash.h>
#include <pbrto/util/NewLowDiscrepancy.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewMemory.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewSpectrum.h>

#include <atomic>
#include <cstdint>
#include <numeric>
#include <vector>

namespace pbrto
{

    std::string SampledLight::ToString( ) const
    {
        return std::format( "[ SampledLight light: {} p: {} ]",
            light ? light.ToString( ).c_str( ) : "(nullptr)", p );
    }

    std::string CompactLightBounds::ToString( ) const
    {
        return std::format(
            "[ CompactLightBounds qb: [ [ {} {} {} ] [ {} {} {} ] ] w: {} ({}) phi: {} "
            "qCosTheta_o: {} ({}) qCosTheta_e: {} ({}) twoSided: {} ]",
            qb[ 0 ][ 0 ], qb[ 0 ][ 1 ], qb[ 0 ][ 2 ], qb[ 1 ][ 0 ], qb[ 1 ][ 1 ], qb[ 1 ][ 2 ], w, Vector3f( w ), phi,
            qCosTheta_o, CosTheta_o( ), qCosTheta_e, CosTheta_e( ), twoSided );
    }

    std::string CompactLightBounds::ToString( const Bounds3f& allBounds ) const
    {
        return std::format(
            "[ CompactLightBounds b: {} qb: [ [ {} {} {} ] [ {} {} {} ] ] w: {} ({}) phi: {} "
            "qCosTheta_o: {} ({}) qCosTheta_e: {} ({}) twoSided: {} ]",
            Bounds( allBounds ), qb[ 0 ][ 0 ], qb[ 0 ][ 1 ], qb[ 0 ][ 2 ], qb[ 1 ][ 0 ], qb[ 1 ][ 1 ], qb[ 1 ][ 2 ], w,
            Vector3f( w ), phi, qCosTheta_o, CosTheta_o( ), qCosTheta_e, CosTheta_e( ), twoSided );
    }

    LightSampler LightSampler::Create( const std::string& name, pstdo::span<const Light> lights,
        Allocator alloc )
    {
        if ( name == "uniform" )
            return alloc.new_object<UniformLightSampler>( lights, alloc );
        else if ( name == "power" )
            return alloc.new_object<PowerLightSampler>( lights, alloc );
        else if ( name == "bvh" )
            return alloc.new_object<BVHLightSampler>( lights, alloc );
        else if ( name == "exhaustive" )
            return alloc.new_object<ExhaustiveLightSampler>( lights, alloc );
        else
        {
            Error( R"(Light sample distribution type "{}" unknown. Using "bvh".)",
                name.c_str( ) );
            return alloc.new_object<BVHLightSampler>( lights, alloc );
        }
    }

    std::string LightSampler::ToString( ) const
    {
        if ( !ptr( ) )
            return "(nullptr)";

        auto ts = [ & ]( auto ptr ) { return ptr->ToString( ); };
        return DispatchCPU( ts );
    }

    ///////////////////////////////////////////////////////////////////////////
    // PowerLightSampler

    // PowerLightSampler Method Definitions
    PowerLightSampler::PowerLightSampler( pstdo::span<const Light> lights, Allocator alloc )
        : lights( lights.begin( ), lights.end( ), alloc ),
        lightToIndex( alloc ),
        aliasTable( alloc )
    {
        if ( lights.empty( ) )
            return;
        // Initialize _lightToIndex_ hash table
        for ( size_t i = 0; i < lights.size( ); ++i )
            lightToIndex.Insert( lights[ i ], i );

        // Compute lights' power and initialize alias table
        pstdo::vector<Float> lightPower;
        SampledWavelengths lambda = SampledWavelengths::SampleVisible( 0.5f );
        for ( const auto& light : lights )
        {
            SampledSpectrum phi = SafeDiv( light.Phi( lambda ), lambda.PDF( ) );
            lightPower.push_back( phi.Average( ) );
        }
        if ( std::accumulate( lightPower.begin( ), lightPower.end( ), 0.f ) == 0.f )
            std::fill( lightPower.begin( ), lightPower.end( ), 1.f );
        aliasTable = AliasTable( lightPower, alloc );
    }

    std::string PowerLightSampler::ToString( ) const
    {
        return std::format( "[ PowerLightSampler aliasTable: {} ]", aliasTable );
    }

    ///////////////////////////////////////////////////////////////////////////
    // BVHLightSampler

    NSTAT_MEMORY_COUNTER( "Memory/Light BVH", lightBVHBytes );
    NSTAT_INT_DISTRIBUTION( "Integrator/Lights sampled per lookup", nLightsSampled );

    // BVHLightSampler Method Definitions
    BVHLightSampler::BVHLightSampler( pstdo::span<const Light> lights, Allocator alloc )
        : lights( lights.begin( ), lights.end( ), alloc ),
        infiniteLights( alloc ),
        nodes( alloc ),
        lightToBitTrail( alloc )
    {
        // Initialize _infiniteLights_ array and light BVH
        std::vector<std::pair<int, LightBounds>> bvhLights;
        for ( size_t i = 0; i < lights.size( ); ++i )
        {
            // Store $i$th light in either _infiniteLights_ or _bvhLights_
            Light light = lights[ i ];
            pstdo::optional<LightBounds> lightBounds = light.Bounds( );
            if ( !lightBounds )
                infiniteLights.push_back( light );
            else if ( lightBounds->phi > 0 )
            {
                bvhLights.push_back( std::make_pair( i, *lightBounds ) );
                allLightBounds = Union( allLightBounds, lightBounds->bounds );
            }
        }
        if ( !bvhLights.empty( ) )
            buildBVH( bvhLights, 0, bvhLights.size( ), 0, 0 );
        lightBVHBytes += nodes.size( ) * sizeof( LightBVHNode ) +
            lightToBitTrail.capacity( ) * sizeof( uint32_t ) +
            lights.size( ) * sizeof( Light ) +
            infiniteLights.size( ) * sizeof( Light );
    }

    std::pair<int, LightBounds> BVHLightSampler::buildBVH(
        std::vector<std::pair<int, LightBounds>>& bvhLights, int start, int end,
        uint32_t bitTrail, int depth )
    {
        NDCHECK_LT( start, end );
        // Initialize leaf node if only a single light remains
        if ( end - start == 1 )
        {
            int nodeIndex = nodes.size( );
            CompactLightBounds cb( bvhLights[ start ].second, allLightBounds );
            int lightIndex = bvhLights[ start ].first;
            nodes.push_back( LightBVHNode::MakeLeaf( lightIndex, cb ) );
            lightToBitTrail.Insert( lights[ lightIndex ], bitTrail );
            return { nodeIndex, bvhLights[ start ].second };
        }

        // Choose split dimension and position using modified SAH
        // Compute bounds and centroid bounds for lights
        Bounds3f bounds, centroidBounds;
        for ( int i = start; i < end; ++i )
        {
            const LightBounds& lb = bvhLights[ i ].second;
            bounds = Union( bounds, lb.bounds );
            centroidBounds = Union( centroidBounds, lb.Centroid( ) );
        }

        Float minCost = Infinity;
        int minCostSplitBucket = -1, minCostSplitDim = -1;
        constexpr int nBuckets = 12;
        for ( int dim = 0; dim < 3; ++dim )
        {
            // Compute minimum cost bucket for splitting along dimension _dim_
            if ( centroidBounds.pMax[ dim ] == centroidBounds.pMin[ dim ] )
                continue;
            // Compute _LightBounds_ for each bucket
            LightBounds bucketLightBounds[ nBuckets ];
            for ( int i = start; i < end; ++i )
            {
                Point3f pc = bvhLights[ i ].second.Centroid( );
                int b = nBuckets * centroidBounds.Offset( pc )[ dim ];
                if ( b == nBuckets )
                    b = nBuckets - 1;
                NDCHECK_GE( b, 0 );
                NDCHECK_LT( b, nBuckets );
                bucketLightBounds[ b ] = Union( bucketLightBounds[ b ], bvhLights[ i ].second );
            }

            // Compute costs for splitting lights after each bucket
            Float cost[ nBuckets - 1 ];
            for ( int i = 0; i < nBuckets - 1; ++i )
            {
                // Find _LightBounds_ for lights below and above bucket split
                LightBounds b0, b1;
                for ( int j = 0; j <= i; ++j )
                    b0 = Union( b0, bucketLightBounds[ j ] );
                for ( int j = i + 1; j < nBuckets; ++j )
                    b1 = Union( b1, bucketLightBounds[ j ] );

                // Compute final light split cost for bucket
                cost[ i ] = EvaluateCost( b0, bounds, dim ) + EvaluateCost( b1, bounds, dim );
            }

            // Find light split that minimizes SAH metric
            for ( int i = 1; i < nBuckets - 1; ++i )
            {
                if ( cost[ i ] > 0 && cost[ i ] < minCost )
                {
                    minCost = cost[ i ];
                    minCostSplitBucket = i;
                    minCostSplitDim = dim;
                }
            }
        }

        // Partition lights according to chosen split
        int mid;
        if ( minCostSplitDim == -1 )
            mid = ( start + end ) / 2;
        else
        {
            const auto* pmid = std::partition(
                &bvhLights[ start ], &bvhLights[ end - 1 ] + 1,
                [ = ]( const std::pair<int, LightBounds>& l ) {
                    int b = nBuckets *
                        centroidBounds.Offset( l.second.Centroid( ) )[ minCostSplitDim ];
                    if ( b == nBuckets )
                        b = nBuckets - 1;
                    NDCHECK_GE( b, 0 );
                    NDCHECK_LT( b, nBuckets );
                    return b <= minCostSplitBucket;
                } );
            mid = pmid - &bvhLights[ 0 ];
            if ( mid == start || mid == end )
                mid = ( start + end ) / 2;
            NDCHECK( mid > start && mid < end );
        }

        // Allocate interior _LightBVHNode_ and recursively initialize children
        int nodeIndex = nodes.size( );
        nodes.push_back( LightBVHNode( ) );
        NCHECK_LT( depth, 64 );
        std::pair<int, LightBounds> child0 =
            buildBVH( bvhLights, start, mid, bitTrail, depth + 1 );
        NDCHECK_EQ( nodeIndex + 1, child0.first );
        std::pair<int, LightBounds> child1 =
            buildBVH( bvhLights, mid, end, bitTrail | ( 1u << depth ), depth + 1 );

        // Initialize interior node and return node index and bounds
        LightBounds lb = Union( child0.second, child1.second );
        CompactLightBounds cb( lb, allLightBounds );
        nodes[ nodeIndex ] = LightBVHNode::MakeInterior( child1.first, cb );
        return { nodeIndex, lb };
    }

    std::string BVHLightSampler::ToString( ) const
    {
        return std::format( "[ BVHLightSampler nodes: {} ]", nodes );
    }

    std::string LightBVHNode::ToString( ) const
    {
        return std::format(
            "[ LightBVHNode lightBounds: {} childOrLightIndex: {} isLeaf: {} ]", lightBounds,
            childOrLightIndex, isLeaf );
    }

    // ExhaustiveLightSampler Method Definitions
    ExhaustiveLightSampler::ExhaustiveLightSampler( pstdo::span<const Light> lights,
        Allocator alloc )
        : lights( lights.begin( ), lights.end( ), alloc ),
        boundedLights( alloc ),
        infiniteLights( alloc ),
        lightBounds( alloc ),
        lightToBoundedIndex( alloc )
    {
        for ( const auto& light : lights )
        {
            if ( pstdo::optional<LightBounds> lb = light.Bounds( ); lb )
            {
                lightToBoundedIndex.Insert( light, boundedLights.size( ) );
                lightBounds.push_back( *lb );
                boundedLights.push_back( light );
            }
            else
                infiniteLights.push_back( light );
        }
    }

    PBRT_CPU_GPU pstdo::optional<SampledLight> ExhaustiveLightSampler::Sample( const LightSampleContext& ctx,
        Float u ) const
    {
        Float pInfinite = Float( infiniteLights.size( ) ) /
            Float( infiniteLights.size( ) + ( !lightBounds.empty( ) ? 1 : 0 ) );

        // Note: shared with BVH light sampler...
        if ( u < pInfinite )
        {
            u /= pInfinite;
            int index = std::min<int>( u * infiniteLights.size( ), infiniteLights.size( ) - 1 );
            Float pdf = pInfinite * 1.f / infiniteLights.size( );
            return SampledLight{ infiniteLights[ index ], pdf };
        }
        else
        {
            u = std::min<Float>( ( u - pInfinite ) / ( 1 - pInfinite ), OneMinusEpsilon );

            uint64_t seed = MixBits( FloatToBits( u ) );
            WeightedReservoirSampler<Light> wrs( seed );

            for ( size_t i = 0; i < boundedLights.size( ); ++i )
                wrs.Add( boundedLights[ i ], lightBounds[ i ].Importance( ctx.p( ), ctx.n ) );

            if ( !wrs.HasSample( ) )
                return {};

            Float pdf = ( 1.f - pInfinite ) * wrs.SampleProbability( );
            return SampledLight{ wrs.GetSample( ), pdf };
        }
    }

    PBRT_CPU_GPU Float ExhaustiveLightSampler::PMF( const LightSampleContext& ctx, Light light ) const
    {
        if ( !lightToBoundedIndex.HasKey( light ) )
            return 1.f / ( infiniteLights.size( ) + ( !lightBounds.empty( ) ? 1 : 0 ) );

        Float importanceSum = 0;
        Float lightImportance = 0;
        for ( size_t i = 0; i < boundedLights.size( ); ++i )
        {
            Float importance = lightBounds[ i ].Importance( ctx.p( ), ctx.n );
            importanceSum += importance;
            if ( light == boundedLights[ i ] )
                lightImportance = importance;
        }
        Float pInfinite = Float( infiniteLights.size( ) ) /
            Float( infiniteLights.size( ) + ( !lightBounds.empty( ) ? 1 : 0 ) );
        Float pdf = lightImportance / importanceSum * ( 1. - pInfinite );
        return pdf;
    }

    std::string ExhaustiveLightSampler::ToString( ) const
    {
        return std::format( "[ ExhaustiveLightSampler lightBounds: {}]", lightBounds );
    }

}