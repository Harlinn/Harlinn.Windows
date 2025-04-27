#pragma once
#ifndef PBRTO_CPU_NEWINTEGRATORS_H_
#define PBRTO_CPU_NEWINTEGRATORS_H_

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

#include <pbrto/base/NewCamera.h>
#include <pbrto/base/NewSampler.h>
#include <pbrto/NewBsdf.h>
#include <pbrto/NewCameras.h>
#include <pbrto/cpu/NewPrimitive.h>
#include <pbrto/NewFilm.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/NewLights.h>
#include <pbrto/NewLightSamplers.h>
#include <pbrto/util/NewLowDiscrepancy.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewRng.h>
#include <pbrto/util/NewSampling.h>

#include <functional>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace pbrto
{

    // Integrator Definition
    class Integrator
    {
    public:
        // Integrator Public Members
        Primitive aggregate;
        std::vector<Light> lights;
        std::vector<Light> infiniteLights;

        // Integrator Public Methods
        virtual ~Integrator( );

        static std::unique_ptr<Integrator> Create(
            const std::string& name, const ParameterDictionary& parameters, Camera camera,
            Sampler sampler, Primitive aggregate, std::vector<Light> lights,
            const RGBColorSpace* colorSpace, const FileLoc* loc );

        virtual std::string ToString( ) const = 0;

        virtual void Render( ) = 0;

        pstdo::optional<ShapeIntersection> Intersect( const Ray& ray, Float tMax = Infinity ) const;
        bool IntersectP( const Ray& ray, Float tMax = Infinity ) const;

        bool Unoccluded( const Interaction& p0, const Interaction& p1 ) const
        {
            return !IntersectP( p0.SpawnRayTo( p1 ), 1 - ShadowEpsilon );
        }

        SampledSpectrum::Simd Tr( const Interaction& p0, const Interaction& p1, const SampledWavelengths& lambda ) const;

        

    protected:
        // Integrator Protected Methods
        Integrator( Primitive aggregate, std::vector<Light> lights )
            : aggregate( aggregate ), lights( lights )
        {
            // Integrator constructor implementation
            Bounds3f sceneBounds = aggregate ? aggregate.Bounds( ) : Bounds3f( );
            NLOG_VERBOSE( "Scene bounds %s", sceneBounds );
            for ( auto& light : lights )
            {
                light.Preprocess( sceneBounds );
                if ( light.Type( ) == LightType::Infinite )
                {
                    infiniteLights.push_back( light );
                }
            }
        }
    };

    // ImageTileIntegrator Definition
    class ImageTileIntegrator : public Integrator
    {
    protected:
        // ImageTileIntegrator Protected Members
        Camera camera;
        Sampler samplerPrototype;
    public:
        // ImageTileIntegrator Public Methods
        ImageTileIntegrator( Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights )
            : Integrator( aggregate, lights ), camera( camera ), samplerPrototype( sampler )
        {
        }

        void Render( );

        virtual void EvaluatePixelSample( Point2i pPixel, int sampleIndex, Sampler sampler, ScratchBuffer& scratchBuffer ) = 0;

    
    };

    // RayIntegrator Definition
    class RayIntegrator : public ImageTileIntegrator
    {
    public:
        // RayIntegrator Public Methods
        RayIntegrator( Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights )
            : ImageTileIntegrator( camera, sampler, aggregate, lights )
        {
        }

        void EvaluatePixelSample( Point2i pPixel, int sampleIndex, Sampler sampler, ScratchBuffer& scratchBuffer ) final;

        virtual SampledSpectrum::Simd Li( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, VisibleSurface* visibleSurface ) const = 0;
    };

    // RandomWalkIntegrator Definition
    class RandomWalkIntegrator : public RayIntegrator
    {
        // RandomWalkIntegrator Private Members
        int maxDepth;
    public:
        // RandomWalkIntegrator Public Methods
        RandomWalkIntegrator( int maxDepth, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights )
            : RayIntegrator( camera, sampler, aggregate, lights ), maxDepth( maxDepth )
        {
        }

        static std::unique_ptr<RandomWalkIntegrator> Create(
            const ParameterDictionary& parameters, Camera camera, Sampler sampler,
            Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

        SampledSpectrum::Simd Li( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, VisibleSurface* visibleSurface ) const override
        {
            return LiRandomWalk( ray, lambda, sampler, scratchBuffer, 0 );
        }

    private:
        // RandomWalkIntegrator Private Methods
        SampledSpectrum::Simd LiRandomWalk( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, int depth ) const
        {
            // Intersect ray with scene and return if no intersection
            pstdo::optional<ShapeIntersection> si = Intersect( ray );
            if ( !si )
            {
                // Return emitted light from infinite light sources
                SampledSpectrum::Simd Le( 0.f );
                for ( Light light : infiniteLights )
                    Le += light.Le( ray, lambda );
                return Le;
            }
            SurfaceInteraction& isect = si->intr;

            // Get emitted radiance at surface intersection
            Vector3f::Simd wo = -ray.d;
            SampledSpectrum::Simd Le = isect.Le( wo, lambda );

            // Terminate random walk if maximum depth has been reached
            if ( depth == maxDepth )
                return Le;

            // Compute BSDF at random walk intersection point
            BSDF bsdf = isect.GetBSDF( ray, lambda, camera, scratchBuffer, sampler );
            if ( !bsdf )
                return Le;

            // Randomly sample direction leaving surface for random walk
            Point2f u = sampler.Get2D( );
            Vector3f::Simd wp = SampleUniformSphere( u );

            // Evaluate BSDF at surface for sampled direction
            SampledSpectrum::Simd fcos = bsdf.f( wo, wp ) * ScalarAbsDot( wp, isect.shading.n );
            if ( !fcos )
                return Le;

            // Recursively trace ray to estimate incident radiance at surface
            ray = isect.SpawnRay( wp );
            return Le + fcos * LiRandomWalk( ray, lambda, sampler, scratchBuffer, depth + 1 ) / ( 1 / ( 4 * Pi ) );
        }

        
    };

    // SimplePathIntegrator Definition
    class SimplePathIntegrator : public RayIntegrator
    {
        // SimplePathIntegrator Private Members
        int maxDepth;
        bool sampleLights, sampleBSDF;
        UniformLightSampler lightSampler;
    public:
        // SimplePathIntegrator Public Methods
        SimplePathIntegrator( int maxDepth, bool sampleLights, bool sampleBSDF, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights );

        SampledSpectrum::Simd Li( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, VisibleSurface* visibleSurface ) const override;

        static std::unique_ptr<SimplePathIntegrator> Create( const ParameterDictionary& parameters, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

    private:
        
    };

    // PathIntegrator Definition
    class PathIntegrator : public RayIntegrator
    {
        // PathIntegrator Private Members
        int maxDepth;
        LightSampler lightSampler;
        bool regularize;
    public:
        // PathIntegrator Public Methods
        PathIntegrator( int maxDepth, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const std::string& lightSampleStrategy = "bvh", bool regularize = false );

        SampledSpectrum::Simd Li( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, VisibleSurface* visibleSurface ) const;

        static std::unique_ptr<PathIntegrator> Create( const ParameterDictionary& parameters, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

    private:
        // PathIntegrator Private Methods
        SampledSpectrum::Simd SampleLd( const SurfaceInteraction& intr, const BSDF* bsdf, SampledWavelengths& lambda, Sampler sampler ) const;

        
    };

    // SimpleVolPathIntegrator Definition
    class SimpleVolPathIntegrator : public RayIntegrator
    {
        // SimpleVolPathIntegrator Private Members
        int maxDepth;
    public:
        // SimpleVolPathIntegrator Public Methods
        SimpleVolPathIntegrator( int maxDepth, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights );

        SampledSpectrum::Simd Li( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, VisibleSurface* visibleSurface ) const override;

        static std::unique_ptr<SimpleVolPathIntegrator> Create( const ParameterDictionary& parameters, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

    private:
        
    };

    // VolPathIntegrator Definition
    class VolPathIntegrator : public RayIntegrator
    {
        // VolPathIntegrator Private Members
        int maxDepth;
        LightSampler lightSampler;
        bool regularize;
    public:
        // VolPathIntegrator Public Methods
        VolPathIntegrator( int maxDepth, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const std::string& lightSampleStrategy = "bvh", bool regularize = false )
            : RayIntegrator( camera, sampler, aggregate, lights ),
              maxDepth( maxDepth ),
              lightSampler( LightSampler::Create( lightSampleStrategy, lights, Allocator( ) ) ),
              regularize( regularize )
        {
        }

        SampledSpectrum::Simd Li( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, VisibleSurface* visibleSurface ) const override;

        static std::unique_ptr<VolPathIntegrator> Create( const ParameterDictionary& parameters, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

    private:
        // VolPathIntegrator Private Methods
        SampledSpectrum::Simd SampleLd( const Interaction& intr, const BSDF* bsdf, SampledWavelengths& lambda, Sampler sampler, SampledSpectrum::Simd beta, SampledSpectrum::Simd inv_w_u ) const;

        
    };

    // AOIntegrator Definition
    class AOIntegrator : public RayIntegrator
    {
        bool cosSample;
        Float maxDist;
        Spectrum illuminant;
        Float illumScale;
    public:
        // AOIntegrator Public Methods
        AOIntegrator( bool cosSample, Float maxDist, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, Spectrum illuminant );

        SampledSpectrum::Simd Li( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, VisibleSurface* visibleSurface ) const override;

        static std::unique_ptr<AOIntegrator> Create( const ParameterDictionary& parameters, Spectrum illuminant, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

    private:
        
    };

    // LightPathIntegrator Definition
    class LightPathIntegrator : public ImageTileIntegrator
    {
        // LightPathIntegrator Private Members
        int maxDepth;
        PowerLightSampler lightSampler;
    public:
        // LightPathIntegrator Public Methods
        LightPathIntegrator( int maxDepth, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights );

        void EvaluatePixelSample( Point2i pPixel, int sampleIndex, Sampler sampler, ScratchBuffer& scratchBuffer ) override;

        static std::unique_ptr<LightPathIntegrator> Create( const ParameterDictionary& parameters, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

    private:
        
    };

    // BDPTIntegrator Definition
    struct Vertex;
    class BDPTIntegrator : public RayIntegrator
    {
        // BDPTIntegrator Private Members
        int maxDepth;
        bool regularize;
        LightSampler lightSampler;
        bool visualizeStrategies, visualizeWeights;
        mutable std::vector<Film> weightFilms;
    public:
        // BDPTIntegrator Public Methods
        BDPTIntegrator( Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, int maxDepth, bool visualizeStrategies, bool visualizeWeights, bool regularize = false )
            : RayIntegrator( camera, sampler, aggregate, lights ),
              maxDepth( maxDepth ),
              regularize( regularize ),
              lightSampler( new PowerLightSampler( lights, Allocator( ) ) ),
              visualizeStrategies( visualizeStrategies ),
              visualizeWeights( visualizeWeights )
        {
        }

        SampledSpectrum::Simd Li( RayDifferential ray, SampledWavelengths& lambda, Sampler sampler, ScratchBuffer& scratchBuffer, VisibleSurface* visibleSurface ) const override;

        static std::unique_ptr<BDPTIntegrator> Create( const ParameterDictionary& parameters, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

        void Render( ) override;

    private:
        
    };

    // MLTIntegrator Definition
    class MLTSampler;

    class MLTIntegrator : public Integrator
    {
        // MLTIntegrator Constants
        static constexpr int cameraStreamIndex = 0;
        static constexpr int lightStreamIndex = 1;
        static constexpr int connectionStreamIndex = 2;
        static constexpr int nSampleStreams = 3;

        // MLTIntegrator Private Members
        Camera camera;
        bool regularize;
        LightSampler lightSampler;
        int maxDepth, nBootstrap;
        int mutationsPerPixel;
        Float sigma, largeStepProbability;
        int nChains;
    public:
        // MLTIntegrator Public Methods
        MLTIntegrator( Camera camera, Primitive aggregate, std::vector<Light> lights, int maxDepth, int nBootstrap, int nChains, int mutationsPerPixel, Float sigma, Float largeStepProbability, bool regularize )
            : Integrator( aggregate, lights ),
            lightSampler( new PowerLightSampler( lights, Allocator( ) ) ),
            camera( camera ),
            maxDepth( maxDepth ),
            nBootstrap( nBootstrap ),
            nChains( nChains ),
            mutationsPerPixel( mutationsPerPixel ),
            sigma( sigma ),
            largeStepProbability( largeStepProbability ),
            regularize( regularize )
        {
        }

        void Render( ) override;

        static std::unique_ptr<MLTIntegrator> Create( const ParameterDictionary& parameters, Camera camera, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

    private:
        // MLTIntegrator Private Methods
        SampledSpectrum::Simd L( ScratchBuffer& scratchBuffer, MLTSampler& sampler, int k, Point2f* pRaster, SampledWavelengths* lambda );

        static Float c( const SampledSpectrum& L, const SampledWavelengths& lambda )
        {
            return L.Y( lambda );
        }

        
    };

    // SPPMIntegrator Definition
    class SPPMIntegrator : public Integrator
    {
        // SPPMIntegrator Private Members
        Camera camera;
        Float initialSearchRadius;
        Sampler samplerPrototype;
        int digitPermutationsSeed;
        int maxDepth;
        int photonsPerIteration;
        const RGBColorSpace* colorSpace;
    public:
        // SPPMIntegrator Public Methods
        SPPMIntegrator( Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, int photonsPerIteration, int maxDepth, Float initialSearchRadius, int seed, const RGBColorSpace* colorSpace )
            : Integrator( aggregate, lights ),
              camera( camera ),
              samplerPrototype( sampler ),
              initialSearchRadius( initialSearchRadius ),
              maxDepth( maxDepth ),
              photonsPerIteration( photonsPerIteration > 0
                ? photonsPerIteration
                : camera.GetFilm( ).PixelBounds( ).Area( ) ),
              colorSpace( colorSpace ),
              digitPermutationsSeed( seed )
        { }

        static std::unique_ptr<SPPMIntegrator> Create( const ParameterDictionary& parameters, const RGBColorSpace* colorSpace, Camera camera, Sampler sampler, Primitive aggregate, std::vector<Light> lights, const FileLoc* loc );

        std::string ToString( ) const;

        void Render( ) override;

    private:
        // SPPMIntegrator Private Methods
        SampledSpectrum::Simd SampleLd( const SurfaceInteraction& intr, const BSDF& bsdf, SampledWavelengths& lambda, Sampler sampler, LightSampler lightSampler ) const;

        
    };

    // FunctionIntegrator Definition
    class FunctionIntegrator : public Integrator
    {
        std::function<double( Point2f )> func;
        std::string outputFilename;
        Camera camera;
        Sampler baseSampler;
        bool skipBad;
        std::string imageFilename;
    public:
        FunctionIntegrator( std::function<double( Point2f )> func, const std::string& outputFilename, Camera camera, Sampler sampler, bool skipBad, std::string imageFilename );

        static std::unique_ptr<FunctionIntegrator> Create( const ParameterDictionary& parameters, Camera camera, Sampler sampler, const FileLoc* loc );

        void Render( ) override;

        std::string ToString( ) const;

    private:
        
    };

}

#endif
