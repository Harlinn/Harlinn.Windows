// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0
#include "pch.h"

#include <pbrto/wavefront/aggregate.h>

#include <pbrto/cpu/aggregates.h>
#include <pbrto/lights.h>
#include <pbrto/materials.h>
#include <pbrto/scene.h>
#include <pbrto/textures.h>
#include <pbrto/util/error.h>
#include <pbrto/util/file.h>
#include <pbrto/util/log.h>
#include <pbrto/util/mesh.h>
#include <pbrto/util/parallel.h>
#include <pbrto/util/pstd.h>
#include <pbrto/util/stats.h>
#include <pbrto/wavefront/intersect.h>

namespace pbrt
{

    CPUAggregate::CPUAggregate(
        BasicScene& scene, NamedTextures& textures,
        const std::map<int, pstd::vector<Light>*>& shapeIndexToAreaLights,
        const std::map<std::string, Medium>& media,
        const std::map<std::string, pbrt::Material>& namedMaterials,
        const std::vector<pbrt::Material>& materials )
    {
        aggregate = scene.CreateAggregate( textures, shapeIndexToAreaLights, media,
            namedMaterials, materials );
    }

    // CPUAggregate Method Definitions
    void CPUAggregate::IntersectClosest( int maxRays, const RayQueue* rayQueue,
        EscapedRayQueue* escapedRayQueue,
        HitAreaLightQueue* hitAreaLightQueue,
        MaterialEvalQueue* basicEvalMaterialQueue,
        MaterialEvalQueue* universalEvalMaterialQueue,
        MediumSampleQueue* mediumSampleQueue,
        RayQueue* nextRayQueue ) const
    {
        // _CPUAggregate::IntersectClosest()_ method implementation
        ParallelFor( 0, rayQueue->Size( ), [ = ]( int index ) {
            const RayWorkItem r = ( *rayQueue )[ index ];
            // Intersect _r_'s ray with the scene and enqueue resulting work
            if ( !aggregate )
            {
                EnqueueWorkAfterMiss( r, mediumSampleQueue, escapedRayQueue );
                return;
            }
            pstd::optional<ShapeIntersection> si = aggregate.Intersect( r.ray );
            if ( !si )
                EnqueueWorkAfterMiss( r, mediumSampleQueue, escapedRayQueue );
            else
                // FIXME? Second arg r.ray.medium doesn't match OptiX path
                EnqueueWorkAfterIntersection(
                    r, r.ray.medium, si->tHit, si->intr, mediumSampleQueue, nextRayQueue,
                    hitAreaLightQueue, basicEvalMaterialQueue, universalEvalMaterialQueue );
            } );
    }

    void CPUAggregate::IntersectShadow( int maxRays, ShadowRayQueue* shadowRayQueue,
        SOA<PixelSampleState>* pixelSampleState ) const
    {
        // Intersect shadow rays from _shadowRayQueue_ in parallel
        ParallelFor( 0, shadowRayQueue->Size( ), [ = ]( int index ) {
            const ShadowRayWorkItem w = ( *shadowRayQueue )[ index ];
            bool hit = aggregate.IntersectP( w.ray, w.tMax );
            RecordShadowRayResult( w, pixelSampleState, hit );
            } );
    }

    void CPUAggregate::IntersectShadowTr( int maxRays, ShadowRayQueue* shadowRayQueue,
        SOA<PixelSampleState>* pixelSampleState ) const
    {
        ParallelFor( 0, shadowRayQueue->Size( ), [ = ]( int index ) {
            const ShadowRayWorkItem w = ( *shadowRayQueue )[ index ];
            pstd::optional<ShapeIntersection> si;
            TraceTransmittance(
                w, pixelSampleState,
                [ & ]( Ray ray, Float tMax ) -> TransmittanceTraceResult {
                    si = aggregate.Intersect( ray, tMax );

                    if ( !si )
                        return TransmittanceTraceResult{ false, Point3f( ), Material( ) };
                    else
                        return TransmittanceTraceResult{ true, si->intr.p( ),
                                                        si->intr.material };
                },
                [ & ]( Point3f p ) -> Ray { return si->intr.SpawnRayTo( p ); } );
            } );
    }

    void CPUAggregate::IntersectOneRandom(
        int maxRays, SubsurfaceScatterQueue* subsurfaceScatterQueue ) const
    {
        ParallelFor( 0, subsurfaceScatterQueue->Size( ), [ = ]( int index ) {
            const SubsurfaceScatterWorkItem& w = ( *subsurfaceScatterQueue )[ index ];
            uint64_t seed = Hash( w.p0, w.p1 );

            WeightedReservoirSampler<SubsurfaceInteraction> wrs( seed );
            Interaction base( w.p0, 0.f /* FIXME time */, Medium( ) );
            while ( true )
            {
                Ray r = base.SpawnRayTo( w.p1 );
                if ( r.d == Vector3f( 0, 0, 0 ) )
                    break;
                pstd::optional<ShapeIntersection> si = aggregate.Intersect( r, 1 );
                if ( !si )
                    break;
                base = si->intr;
                if ( si->intr.material == w.material )
                    wrs.Add( SubsurfaceInteraction( si->intr ), 1.f );
            }

            if ( wrs.HasSample( ) )
            {
                subsurfaceScatterQueue->reservoirPDF[ index ] = wrs.SampleProbability( );
                subsurfaceScatterQueue->ssi[ index ] = wrs.GetSample( );
            }
            else
                subsurfaceScatterQueue->reservoirPDF[ index ] = 0;
            } );
    }

}  // namespace pbrt
