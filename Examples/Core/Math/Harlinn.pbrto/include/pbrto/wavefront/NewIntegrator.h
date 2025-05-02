#pragma once
#ifndef PBRTO_WAVEFRONT_NEWINTEGRATOR_H_
#define PBRTO_WAVEFRONT_NEWINTEGRATOR_H_

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

#include <pbrto/base/NewBxdf.h>
#include <pbrto/base/NewCamera.h>
#include <pbrto/base/NewFilm.h>
#include <pbrto/base/NewFilter.h>
#include <pbrto/base/NewLight.h>
#include <pbrto/base/NewLightSampler.h>
#include <pbrto/base/NewSampler.h>
#ifdef PBRT_BUILD_GPU_RENDERER
#include <pbrto/gpu/NewUtil.h>
#endif  // PBRT_BUILD_GPU_RENDERER
#include <pbrto/NewOptions.h>
#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/wavefront/NewWorkitems.h>
#include <pbrto/wavefront/NewWorkqueue.h>

namespace pbrto
{

    class BasicScene;
    class GUI;

    // WavefrontAggregate Definition
    class WavefrontAggregate
    {
    public:
        // WavefrontAggregate Interface
        virtual ~WavefrontAggregate( ) = default;

        virtual Bounds3f Bounds( ) const = 0;

        virtual void IntersectClosest( int maxRays, const RayQueue* rayQ,
            EscapedRayQueue* escapedRayQ,
            HitAreaLightQueue* hitAreaLightQ,
            MaterialEvalQueue* basicMtlQ,
            MaterialEvalQueue* universalMtlQ,
            MediumSampleQueue* mediumSampleQ,
            RayQueue* nextRayQ ) const = 0;

        virtual void IntersectShadow( int maxRays, ShadowRayQueue* shadowRayQueue,
            SOA<PixelSampleState>* pixelSampleState ) const = 0;
        virtual void IntersectShadowTr( int maxRays, ShadowRayQueue* shadowRayQueue,
            SOA<PixelSampleState>* pixelSampleState ) const = 0;

        virtual void IntersectOneRandom(
            int maxRays, SubsurfaceScatterQueue* subsurfaceScatterQueue ) const = 0;
    };

    // WavefrontPathIntegrator Definition
    class WavefrontPathIntegrator
    {
    public:
        // WavefrontPathIntegrator Public Methods
        Float Render( );

        void GenerateCameraRays( int y0, Transform movingFromcamera, int sampleIndex );
        template <typename Sampler>
        void GenerateCameraRays( int y0, Transform movingFromCamera, int sampleIndex );

        void GenerateRaySamples( int wavefrontDepth, int sampleIndex );
        template <typename Sampler>
        void GenerateRaySamples( int wavefrontDepth, int sampleIndex );

        void TraceShadowRays( int wavefrontDepth );
        void SampleMediumInteraction( int wavefrontDepth );
        template <typename PhaseFunction>
        void SampleMediumScattering( int wavefrontDepth );
        void SampleSubsurface( int wavefrontDepth );

        void HandleEscapedRays( );
        void HandleEmissiveIntersection( );

        void EvaluateMaterialsAndBSDFs( int wavefrontDepth, Transform movingFromCamera );
        template <typename ConcreteMaterial>
        void EvaluateMaterialAndBSDF( int wavefrontDepth, Transform movingFromCamera );
        template <typename ConcreteMaterial, typename TextureEvaluator>
        void EvaluateMaterialAndBSDF( MaterialEvalQueue* evalQueue, Transform movingFromCamera,
            int wavefrontDepth );

        void UpdateFilm( );

        WavefrontPathIntegrator( pstdo::pmr::memory_resource* memoryResource,
            BasicScene& scene );

        template <typename F>
        void ParallelFor( const char* description, int nItems, F&& func )
        {
            if ( Options->useGPU )
#ifdef PBRT_BUILD_GPU_RENDERER
                GPUParallelFor( description, nItems, func );
#else
                NLOG_FATAL( "Options->useGPU was set without PBRT_BUILD_GPU_RENDERER enabled" );
#endif
            else
                pbrto::ParallelFor( 0, nItems, func );
        }

        template <typename F>
        void Do( const char* description, F&& func )
        {
            if ( Options->useGPU )
#ifdef PBRT_BUILD_GPU_RENDERER
                GPUParallelFor( description, 1, [ = ] PBRT_GPU( int ) mutable { func( ); } );
#else
                NLOG_FATAL( "Options->useGPU was set without PBRT_BUILD_GPU_RENDERER enabled" );
#endif
            else
                func( );
        }

        RayQueue* CurrentRayQueue( int wavefrontDepth )
        {
            return rayQueues[ wavefrontDepth & 1 ];
        }
        RayQueue* NextRayQueue( int wavefrontDepth )
        {
            return rayQueues[ ( wavefrontDepth + 1 ) & 1 ];
        }

#ifdef PBRT_BUILD_GPU_RENDERER
        void PrefetchGPUAllocations( );
#endif  // PBRT_BUILD_GPU_RENDERER

        // --display-server methods
        void StartDisplayThread( );
        void UpdateDisplayRGBFromFilm( Bounds2i pixelBounds );
        void StopDisplayThread( );

        // --interactive support
        void UpdateFramebufferFromFilm( Bounds2i pixelBounds, Float exposure, RGB* rgb );

        // WavefrontPathIntegrator Member Variables
        bool initializeVisibleSurface;
        bool haveSubsurface;
        bool haveMedia;
        pstdo::array<bool, Material::NumTags( )> haveBasicEvalMaterial;
        pstdo::array<bool, Material::NumTags( )> haveUniversalEvalMaterial;

        struct Stats
        {
            Stats( int maxDepth, Allocator alloc );

            std::string Print( ) const;

            // Note: not atomics: tid 0 always updates them for everyone...
            uint64_t cameraRays = 0;
            pstdo::vector<uint64_t> indirectRays, shadowRays;
        };
        Stats* stats;

        pstdo::pmr::memory_resource* memoryResource;

        Filter filter;
        Film film;
        Sampler sampler;
        Camera camera;
        pstdo::vector<Light>* infiniteLights;
        LightSampler lightSampler;

        int maxDepth, samplesPerPixel;
        bool regularize;

        int scanlinesPerPass, maxQueueSize;

        SOA<PixelSampleState> pixelSampleState;

        RayQueue* rayQueues[ 2 ];

        WavefrontAggregate* aggregate = nullptr;

        MediumSampleQueue* mediumSampleQueue = nullptr;
        MediumScatterQueue* mediumScatterQueue = nullptr;

        EscapedRayQueue* escapedRayQueue = nullptr;

        HitAreaLightQueue* hitAreaLightQueue = nullptr;

        MaterialEvalQueue* basicEvalMaterialQueue = nullptr;
        MaterialEvalQueue* universalEvalMaterialQueue = nullptr;

        ShadowRayQueue* shadowRayQueue = nullptr;

        GetBSSRDFAndProbeRayQueue* bssrdfEvalQueue = nullptr;
        SubsurfaceScatterQueue* subsurfaceScatterQueue = nullptr;

        RGB* displayRGB = nullptr, * displayRGBHost = nullptr;
        std::atomic<bool>* exitCopyThread;
        std::thread* copyThread;
    };

}

#endif
