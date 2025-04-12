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

#include <pbrto/cpu/NewRender.h>

#include <pbrto/NewCameras.h>
#include <pbrto/cpu/NewAggregates.h>
#include <pbrto/cpu/NewIntegrators.h>
#include <pbrto/NewFilm.h>
#include <pbrto/NewFilters.h>
#include <pbrto/NewLights.h>
#include <pbrto/NewMaterials.h>
#include <pbrto/NewMedia.h>
#include <pbrto/NewSamplers.h>
#include <pbrto/NewScene.h>
#include <pbrto/NewShapes.h>
#include <pbrto/NewTextures.h>
#include <pbrto/util/NewColorSpace.h>
#include <pbrto/util/NewParallel.h>

namespace pbrto
{

    PBRTO_EXPORT
        void RenderCPU( BasicScene& parsedScene )
    {
        Allocator alloc;
        ThreadLocal<Allocator> threadAllocators( []( ) { return Allocator( ); } );

        // Create media first (so have them for the camera...)
        std::map<std::string, Medium> media = parsedScene.CreateMedia( );

        // Textures
        NLOG_VERBOSE( "Starting textures" );
        NamedTextures textures = parsedScene.CreateTextures( );
        NLOG_VERBOSE( "Finished textures" );

        // Lights
        std::map<int, pstdo::vector<Light>*> shapeIndexToAreaLights;
        std::vector<Light> lights =
            parsedScene.CreateLights( textures, &shapeIndexToAreaLights );

        NLOG_VERBOSE( "Starting materials" );
        std::map<std::string, pbrto::Material> namedMaterials;
        std::vector<pbrto::Material> materials;
        parsedScene.CreateMaterials( textures, &namedMaterials, &materials );
        NLOG_VERBOSE( "Finished materials" );

        Primitive accel = parsedScene.CreateAggregate( textures, shapeIndexToAreaLights, media,
            namedMaterials, materials );

        Camera camera = parsedScene.GetCamera( );
        Film film = camera.GetFilm( );
        Sampler sampler = parsedScene.GetSampler( );

        // Integrator
        NLOG_VERBOSE( "Starting to create integrator" );
        std::unique_ptr<Integrator> integrator(
            parsedScene.CreateIntegrator( camera, sampler, accel, lights ) );
        NLOG_VERBOSE( "Finished creating integrator" );

        // Helpful warnings
        bool haveScatteringMedia = false;
        for ( const auto& sh : parsedScene.shapes )
            if ( !sh.insideMedium.empty( ) || !sh.outsideMedium.empty( ) )
                haveScatteringMedia = true;
        for ( const auto& sh : parsedScene.animatedShapes )
            if ( !sh.insideMedium.empty( ) || !sh.outsideMedium.empty( ) )
                haveScatteringMedia = true;

        if ( haveScatteringMedia && parsedScene.integrator.name != "volpath" &&
            parsedScene.integrator.name != "simplevolpath" &&
            parsedScene.integrator.name != "bdpt" && parsedScene.integrator.name != "mlt" )
            Warning( "Scene has scattering media but \"%s\" integrator doesn't support "
                "volume scattering. Consider using \"volpath\", \"simplevolpath\", "
                "\"bdpt\", or \"mlt\".",
                parsedScene.integrator.name );

        bool haveLights = !lights.empty( );
        for ( const auto& m : media )
            haveLights |= m.second.IsEmissive( );

        if ( !haveLights && parsedScene.integrator.name != "ambientocclusion" &&
            parsedScene.integrator.name != "aov" )
            Warning( "No light sources defined in scene; rendering a black image." );

        if ( film.Is<GBufferFilm>( ) && !( parsedScene.integrator.name == "path" ||
            parsedScene.integrator.name == "volpath" ) )
            Warning( "GBufferFilm is not supported by the \"%s\" integrator. The channels "
                "other than R, G, B will be zero.",
                parsedScene.integrator.name );

        bool haveSubsurface = false;
        for ( pbrto::Material mtl : materials )
            haveSubsurface |= mtl && mtl.HasSubsurfaceScattering( );
        for ( const auto& namedMtl : namedMaterials )
            haveSubsurface |= namedMtl.second && namedMtl.second.HasSubsurfaceScattering( );

        if ( haveSubsurface && parsedScene.integrator.name != "volpath" )
            Warning( "Some objects in the scene have subsurface scattering, which is "
                "not supported by the %s integrator. Use the \"volpath\" integrator "
                "to render them correctly.",
                parsedScene.integrator.name );

        NLOG_VERBOSE( "Memory used after scene creation: %d", GetCurrentRSS( ) );

        if ( Options->pixelMaterial )
        {
            SampledWavelengths lambda = SampledWavelengths::SampleUniform( 0.5f );

            CameraSample cs;
            cs.pFilm = Point2f( *Options->pixelMaterial ) + Vector2f( 0.5f, 0.5f );
            cs.time = 0.5f;
            cs.pLens = Point2f( 0.5f, 0.5f );
            cs.filterWeight = 1;
            pstdo::optional<CameraRay> cr = camera.GenerateRay( cs, lambda );
            if ( !cr )
                ErrorExit( "Unable to generate camera ray for specified pixel." );

            int depth = 1;
            Ray ray = cr->ray;
            while ( true )
            {
                pstdo::optional<ShapeIntersection> isect = accel.Intersect( ray, Infinity );
                if ( !isect )
                {
                    if ( depth == 1 )
                        ErrorExit( "No geometry visible at specified pixel." );
                    else
                        break;
                }

                const SurfaceInteraction& intr = isect->intr;
                if ( !intr.material )
                    Warning( "Ignoring \"interface\" material at intersection." );
                else
                {
                    Transform worldFromRender = camera.GetCameraTransform( ).WorldFromRender( );
                    Printf( "Intersection depth %d\n", depth );
                    Printf( "World-space p: %s\n", worldFromRender( intr.p( ) ) );
                    Printf( "World-space n: %s\n", worldFromRender( intr.n ) );
                    Printf( "World-space ns: %s\n", worldFromRender( intr.shading.n ) );
                    Printf( "Distance from camera: %f\n", ScalarDistance( intr.p( ), cr->ray.o ) );

                    bool isNamed = false;
                    for ( const auto& mtl : namedMaterials )
                        if ( mtl.second == intr.material )
                        {
                            Printf( "Named material: %s\n\n", mtl.first );
                            isNamed = true;
                            break;
                        }
                    if ( !isNamed )
                        // If we didn't find a named material, dump out the whole thing.
                        Printf( "%s\n\n", intr.material.ToString( ) );

                    ++depth;
                    ray = intr.SpawnRay( ray.d );
                }
            }

            return;
        }

        // Render!
        integrator->Render( );

        NLOG_VERBOSE( "Memory used after rendering: %s", GetCurrentRSS( ) );

        PtexTextureBase::ReportStats( );
        ImageTextureBase::ClearCache( );
    }

}