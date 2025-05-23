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

#include <pbrto/NewCameras.h>

#include <pbrto/base/NewMedium.h>
#include <pbrto/NewBsdf.h>
#include <pbrto/NewFilm.h>
#include <pbrto/NewFilters.h>
#include <pbrto/NewOptions.h>
#include <pbrto/NewParamDict.h>
#include <pbrto/util/NewError.h>
#include <pbrto/util/NewFile.h>
#include <pbrto/util/NewImage.h>
#include <pbrto/util/NewLowDiscrepancy.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewStats.h>

#include <algorithm>

namespace pbrto
{

    // CameraTransform Method Definitions
    CameraTransform::CameraTransform( const AnimatedTransform& worldFromCamera )
    {
        switch ( Options->renderingSpace )
        {
            case RenderingCoordinateSystem::Camera:
            {
                // Compute _worldFromRender_ for camera-space rendering
                Float tMid = ( worldFromCamera.startTime + worldFromCamera.endTime ) / 2;
                worldFromRender = worldFromCamera.Interpolate( tMid );
                break;
            }
            case RenderingCoordinateSystem::CameraWorld:
            {
                // Compute _worldFromRender_ for camera-world space rendering
                Float tMid = ( worldFromCamera.startTime + worldFromCamera.endTime ) / 2;
                Point3f pCamera = worldFromCamera( Point3f( 0, 0, 0 ), tMid );
                worldFromRender = Translate( Vector3f( pCamera ) );
                break;
            }
            case RenderingCoordinateSystem::World:
            {
                // Compute _worldFromRender_ for world-space rendering
                worldFromRender = Transform( );
                break;
            }
            default:
                NLOG_FATAL( "Unhandled rendering coordinate space" );
        }
        NLOG_VERBOSE( "World-space position: %s", worldFromRender( Point3f::Simd( 0, 0, 0 ) ) );
        // Compute _renderFromCamera_ transformation
        Transform renderFromWorld = Inverse( worldFromRender );
        Transform rfc[ 2 ] = { renderFromWorld * worldFromCamera.startTransform,
                            renderFromWorld * worldFromCamera.endTransform };
        renderFromCamera = AnimatedTransform( rfc[ 0 ], worldFromCamera.startTime, rfc[ 1 ],
            worldFromCamera.endTime );
    }

    std::string CameraTransform::ToString( ) const
    {
        return StringPrintf( "[ CameraTransform renderFromCamera: %s worldFromRender: %s ]",
            renderFromCamera, worldFromRender );
    }

    // Camera Method Definitions
    PBRT_CPU_GPU pstdo::optional<CameraRayDifferential> Camera::GenerateRayDifferential( const CameraSample& sample, SampledWavelengths& lambda ) const
    {
        auto gen = [ & ]( auto ptr ) { return ptr->GenerateRayDifferential( sample, lambda ); };
        return Dispatch( gen );
    }

    PBRT_CPU_GPU SampledSpectrum Camera::We( const Ray& ray, SampledWavelengths& lambda,
        Point2f* pRaster2 ) const
    {
        auto we = [ & ]( auto ptr ) { return ptr->We( ray, lambda, pRaster2 ); };
        return Dispatch( we );
    }

    PBRT_CPU_GPU void Camera::PDF_We( const Ray& ray, Float* pdfPos, Float* pdfDir ) const
    {
        auto pdf = [ & ]( auto ptr ) { return ptr->PDF_We( ray, pdfPos, pdfDir ); };
        return Dispatch( pdf );
    }

    PBRT_CPU_GPU pstdo::optional<CameraWiSample> Camera::SampleWi( const Interaction& ref, Point2f u,
        SampledWavelengths& lambda ) const
    {
        auto sample = [ & ]( auto ptr ) { return ptr->SampleWi( ref, u, lambda ); };
        return Dispatch( sample );
    }

    void Camera::InitMetadata( ImageMetadata* metadata ) const
    {
        auto init = [ & ]( auto ptr ) { return ptr->InitMetadata( metadata ); };
        return DispatchCPU( init );
    }

    std::string Camera::ToString( ) const
    {
        if ( !ptr( ) )
            return "(nullptr)";

        auto ts = [ & ]( auto ptr ) { return ptr->ToString( ); };
        return DispatchCPU( ts );
    }

    // CameraBase Method Definitions
    CameraBase::CameraBase( CameraBaseParameters p )
        : cameraTransform( p.cameraTransform ),
        shutterOpen( p.shutterOpen ),
        shutterClose( p.shutterClose ),
        film( p.film ),
        medium( p.medium )
    {
        if ( cameraTransform.CameraFromRenderHasScale( ) )
            Warning( "Scaling detected in rendering space to camera space transformation!\n"
                "The system has numerous assumptions, implicit and explicit,\n"
                "that this transform will have no scale factors in it.\n"
                "Proceed at your own risk; your image may have errors or\n"
                "the system may crash as a result of this." );
    }

    PBRT_CPU_GPU pstdo::optional<CameraRayDifferential> CameraBase::GenerateRayDifferential(
        Camera camera, CameraSample sample, SampledWavelengths& lambda )
    {
        // Generate regular camera ray _cr_ for ray differential
        pstdo::optional<CameraRay> cr = camera.GenerateRay( sample, lambda );
        if ( !cr )
            return {};
        RayDifferential rd( cr->ray );

        // Find camera ray after shifting one pixel in the $x$ direction
        pstdo::optional<CameraRay> rx;
        for ( Float eps : {.05f, -.05f} )
        {
            CameraSample sshift = sample;
            sshift.pFilm.x += eps;
            // Try to generate ray with _sshift_ and compute $x$ differential
            if ( rx = camera.GenerateRay( sshift, lambda ); rx )
            {
                rd.rxOrigin = rd.o + ( rx->ray.o - rd.o ) / eps;
                rd.rxDirection = rd.d + ( rx->ray.d - rd.d ) / eps;
                break;
            }
        }

        // Find camera ray after shifting one pixel in the $y$ direction
        pstdo::optional<CameraRay> ry;
        for ( Float eps : {.05f, -.05f} )
        {
            CameraSample sshift = sample;
            sshift.pFilm.y += eps;
            if ( ry = camera.GenerateRay( sshift, lambda ); ry )
            {
                rd.ryOrigin = rd.o + ( ry->ray.o - rd.o ) / eps;
                rd.ryDirection = rd.d + ( ry->ray.d - rd.d ) / eps;
                break;
            }
        }

        // Return approximate ray differential and weight
        rd.hasDifferentials = rx && ry;
        return CameraRayDifferential{ rd, cr->weight };
    }

    void CameraBase::FindMinimumDifferentials( Camera camera )
    {
        minPosDifferentialX = minPosDifferentialY = minDirDifferentialX =
            minDirDifferentialY = Vector3f( Infinity, Infinity, Infinity );

        CameraSample sample;
        sample.pLens = Point2f( 0.5, 0.5 );
        sample.time = 0.5;
        SampledWavelengths lambda = SampledWavelengths::SampleVisible( 0.5 );

        int n = 512;
        for ( int i = 0; i < n; ++i )
        {
            sample.pFilm.x = Float( i ) / ( n - 1 ) * film.FullResolution( ).x;
            sample.pFilm.y = Float( i ) / ( n - 1 ) * film.FullResolution( ).y;

            pstdo::optional<CameraRayDifferential> crd =
                camera.GenerateRayDifferential( sample, lambda );
            if ( !crd )
                continue;

            RayDifferential& ray = crd->ray;
            Vector3f dox = CameraFromRender( ray.rxOrigin - ray.o, ray.time );
            if ( ScalarLength( dox ) < ScalarLength( minPosDifferentialX ) )
                minPosDifferentialX = dox;
            Vector3f doy = CameraFromRender( ray.ryOrigin - ray.o, ray.time );
            if ( ScalarLength( doy ) < ScalarLength( minPosDifferentialY ) )
                minPosDifferentialY = doy;

            ray.d = Normalize( ray.d );
            ray.rxDirection = Normalize( ray.rxDirection );
            ray.ryDirection = Normalize( ray.ryDirection );

            Frame f = Frame::FromZ( ray.d );
            Vector3f df = f.ToLocal( ray.d );  // should be (0, 0, 1);
            Vector3f dxf = Normalize( f.ToLocal( ray.rxDirection ) );
            Vector3f dyf = Normalize( f.ToLocal( ray.ryDirection ) );

            if ( ScalarLength( dxf - df ) < ScalarLength( minDirDifferentialX ) )
                minDirDifferentialX = dxf - df;
            if ( ScalarLength( dyf - df ) < ScalarLength( minDirDifferentialY ) )
                minDirDifferentialY = dyf - df;
        }

        NLOG_VERBOSE( "Camera min pos differentials: %s, %s", minPosDifferentialX,
            minPosDifferentialY );
        NLOG_VERBOSE( "Camera min dir differentials: %s, %s", minDirDifferentialX,
            minDirDifferentialY );
    }

    void CameraBase::InitMetadata( ImageMetadata* metadata ) const
    {
        metadata->cameraFromWorld = cameraTransform.CameraFromWorld( shutterOpen ).GetMatrix( );
    }

    std::string CameraBase::ToString( ) const
    {
        return StringPrintf( "cameraTransform: %s shutterOpen: %f shutterClose: %f film: %s "
            "medium: %s minPosDifferentialX: %s minPosDifferentialY: %s "
            "minDirDifferentialX: %s minDirDifferentialY: %s ",
            cameraTransform, shutterOpen, shutterClose, film,
            medium ? medium.ToString( ).c_str( ) : "(nullptr)",
            minPosDifferentialX, minPosDifferentialY, minDirDifferentialX,
            minDirDifferentialY );
    }

    std::string CameraSample::ToString( ) const
    {
        return StringPrintf( "[ CameraSample pFilm: %s pLens: %s time: %f filterWeight: %f ]",
            pFilm, pLens, time, filterWeight );
    }

    // ProjectiveCamera Method Definitions
    void ProjectiveCamera::InitMetadata( ImageMetadata* metadata ) const
    {
        metadata->cameraFromWorld = cameraTransform.CameraFromWorld( shutterOpen ).GetMatrix( );

        // TODO: double check this
        Transform NDCFromWorld = Translate( Vector3f( 0.5, 0.5, 0.5 ) ) * Scale( 0.5, 0.5, 0.5 ) *
            screenFromCamera * *metadata->cameraFromWorld;
        metadata->NDCFromWorld = NDCFromWorld.GetMatrix( );

        CameraBase::InitMetadata( metadata );
    }

    std::string ProjectiveCamera::BaseToString( ) const
    {
        return CameraBase::ToString( ) +
            StringPrintf( "screenFromCamera: %s cameraFromRaster: %s "
                "rasterFromScreen: %s screenFromRaster: %s "
                "lensRadius: %f focalDistance: %f",
                screenFromCamera, cameraFromRaster, rasterFromScreen,
                screenFromRaster, lensRadius, focalDistance );
    }

    Camera Camera::Create( const std::string& name, const ParameterDictionary& parameters,
        Medium medium, const CameraTransform& cameraTransform, Film film,
        const FileLoc* loc, Allocator alloc )
    {
        Camera camera;
        if ( name == "perspective" )
            camera = PerspectiveCamera::Create( parameters, cameraTransform, film, medium, loc,
                alloc );
        else if ( name == "orthographic" )
            camera = OrthographicCamera::Create( parameters, cameraTransform, film, medium,
                loc, alloc );
        else if ( name == "realistic" )
            camera = RealisticCamera::Create( parameters, cameraTransform, film, medium, loc,
                alloc );
        else if ( name == "spherical" )
            camera = SphericalCamera::Create( parameters, cameraTransform, film, medium, loc,
                alloc );
        else
            ErrorExit( loc, "%s: camera type unknown.", name );

        if ( !camera )
            ErrorExit( loc, "%s: unable to create camera.", name );

        parameters.ReportUnused( );
        return camera;
    }

    // CameraBaseParameters Method Definitions
    CameraBaseParameters::CameraBaseParameters( const CameraTransform& cameraTransform,
        Film film, Medium medium,
        const ParameterDictionary& parameters,
        const FileLoc* loc )
        : cameraTransform( cameraTransform ), film( film ), medium( medium )
    {
        shutterOpen = parameters.GetOneFloat( "shutteropen", 0.f );
        shutterClose = parameters.GetOneFloat( "shutterclose", 1.f );
        if ( shutterClose < shutterOpen )
        {
            Warning( loc, "Shutter close time %f < shutter open %f.  Swapping them.",
                shutterClose, shutterOpen );
            pstdo::swap( shutterClose, shutterOpen );
        }
    }

    // OrthographicCamera Method Definitions
    pstdo::optional<CameraRay> OrthographicCamera::GenerateRay( const CameraSample& sample, SampledWavelengths& lambda ) const
    {
        // Compute raster and camera sample positions
        Point3f::Simd pFilm = Point3f( sample.pFilm.x, sample.pFilm.y, 0 );
        Point3f pCamera = cameraFromRaster( pFilm );

        Ray ray( pCamera, Vector3f( 0, 0, 1 ), SampleTime( sample.time ), medium );
        // Modify ray for depth of field
        if ( lensRadius > 0 )
        {
            // Sample point on lens
            Point2f pLens = lensRadius * SampleUniformDiskConcentric( sample.pLens );

            // Compute point on plane of focus
            Float ft = focalDistance / ray.d.z( );
            Point3f pFocus = ray( ft );

            // Update ray for effect of lens
            ray.o = Point3f( pLens.x, pLens.y, 0 );
            ray.d = Normalize( pFocus - ray.o );
        }

        return CameraRay{ RenderFromCamera( ray ) };
    }

    pstdo::optional<CameraRayDifferential> OrthographicCamera::GenerateRayDifferential( const CameraSample& sample, SampledWavelengths& lambda ) const
    {
        // Compute main orthographic viewing ray
        // Compute raster and camera sample positions
        Point3f::Simd pFilm = Point3f( sample.pFilm.x, sample.pFilm.y, 0 );
        Point3f pCamera = cameraFromRaster( pFilm );

        RayDifferential ray( pCamera, Vector3f( 0, 0, 1 ), SampleTime( sample.time ), medium );
        // Modify ray for depth of field
        if ( lensRadius > 0 )
        {
            // Sample point on lens
            Point2f pLens = lensRadius * SampleUniformDiskConcentric( sample.pLens );

            // Compute point on plane of focus
            Float ft = focalDistance / ray.d.z( );
            Point3f pFocus = ray( ft );

            // Update ray for effect of lens
            ray.o = Point3f( pLens.x, pLens.y, 0 );
            ray.d = Normalize( pFocus - ray.o );
        }

        // Compute ray differentials for _OrthographicCamera_
        if ( lensRadius > 0 )
        {
            // Compute _OrthographicCamera_ ray differentials accounting for lens
            // Sample point on lens
            Point2f pLens = lensRadius * SampleUniformDiskConcentric( sample.pLens );

            Float ft = focalDistance / ray.d.z( );
            Point3f pFocus = pCamera + dxCamera + ( ft * Vector3f( 0, 0, 1 ) );
            ray.rxOrigin = Point3f( pLens.x, pLens.y, 0 );
            ray.rxDirection = Normalize( pFocus - ray.rxOrigin );

            pFocus = pCamera + dyCamera + ( ft * Vector3f( 0, 0, 1 ) );
            ray.ryOrigin = Point3f( pLens.x, pLens.y, 0 );
            ray.ryDirection = Normalize( pFocus - ray.ryOrigin );

        }
        else
        {
            ray.rxOrigin = ray.o + dxCamera;
            ray.ryOrigin = ray.o + dyCamera;
            ray.rxDirection = ray.ryDirection = ray.d;
        }

        ray.hasDifferentials = true;
        return CameraRayDifferential{ RenderFromCamera( ray ) };
    }

    std::string OrthographicCamera::ToString( ) const
    {
        return StringPrintf( "[ OrthographicCamera %s dxCamera: %s dyCamera: %s ]",
            BaseToString( ), dxCamera, dyCamera );
    }

    OrthographicCamera* OrthographicCamera::Create( const ParameterDictionary& parameters,
        const CameraTransform& cameraTransform,
        Film film, Medium medium,
        const FileLoc* loc, Allocator alloc )
    {
        CameraBaseParameters cameraBaseParameters( cameraTransform, film, medium, parameters,
            loc );

        Float lensradius = parameters.GetOneFloat( "lensradius", 0.f );
        Float focaldistance = parameters.GetOneFloat( "focaldistance", 1e6f );
        Float frame =
            parameters.GetOneFloat( "frameaspectratio", Float( film.FullResolution( ).x ) /
                Float( film.FullResolution( ).y ) );
        Bounds2f screen;
        if ( frame > 1.f )
        {
            screen.pMin.x = -frame;
            screen.pMax.x = frame;
            screen.pMin.y = -1.f;
            screen.pMax.y = 1.f;
        }
        else
        {
            screen.pMin.x = -1.f;
            screen.pMax.x = 1.f;
            screen.pMin.y = -1.f / frame;
            screen.pMax.y = 1.f / frame;
        }
        std::vector<Float> sw = parameters.GetFloatArray( "screenwindow" );
        if ( !sw.empty( ) )
        {
            if ( Options->fullscreen )
            {
                Warning( "\"screenwindow\" is ignored in fullscreen mode" );
            }
            else
            {
                if ( sw.size( ) == 4 )
                {
                    screen.pMin.x = sw[ 0 ];
                    screen.pMax.x = sw[ 1 ];
                    screen.pMin.y = sw[ 2 ];
                    screen.pMax.y = sw[ 3 ];
                }
                else
                {
                    Error( "\"screenwindow\" should have four values" );
                }
            }
        }
        return alloc.new_object<OrthographicCamera>( cameraBaseParameters, screen, lensradius,
            focaldistance );
    }

    // PerspectiveCamera Method Definitions
    pstdo::optional<CameraRay> PerspectiveCamera::GenerateRay( const CameraSample& sample, SampledWavelengths& lambda ) const
    {
        // Compute raster and camera sample positions
        Point3f::Simd pFilm = Point3f::Simd( sample.pFilm.x, sample.pFilm.y, 0 );
        Point3f::Simd pCamera = cameraFromRaster( pFilm );

        Ray ray( Point3f::Simd( 0, 0, 0 ), Normalize( Vector3f::Simd( pCamera ) ), SampleTime( sample.time ), medium );
        // Modify ray for depth of field
        if ( lensRadius > 0 )
        {
            // Sample point on lens
            Point2f pLens = lensRadius * SampleUniformDiskConcentric( sample.pLens );

            // Compute point on plane of focus
            Float ft = focalDistance / ray.d.z( );
            Point3f::Simd pFocus = ray( ft );

            // Update ray for effect of lens
            ray.o = Point3f::Simd( pLens.x, pLens.y, 0 );
            ray.d = Normalize( pFocus - ray.o );
        }

        return CameraRay{ RenderFromCamera( ray ) };
    }

    pstdo::optional<CameraRayDifferential> PerspectiveCamera::GenerateRayDifferential( const CameraSample& sample, SampledWavelengths& lambda ) const
    {
        // Compute raster and camera sample positions
        Point3f::Simd pFilm = Point3f::Simd( sample.pFilm.x, sample.pFilm.y, 0 );
        Point3f::Simd pCamera = cameraFromRaster( pFilm );
        Vector3f::Simd dir = Normalize( Vector3f::Simd( pCamera ) );
        RayDifferential ray( Point3f::Simd( 0, 0, 0 ), dir, SampleTime( sample.time ), medium );
        // Modify ray for depth of field
        if ( lensRadius > 0 )
        {
            // Sample point on lens
            Point2f pLens = lensRadius * SampleUniformDiskConcentric( sample.pLens );

            // Compute point on plane of focus
            Float ft = focalDistance / ray.d.z( );
            Point3f::Simd pFocus = ray( ft );

            // Update ray for effect of lens
            ray.o = Point3f::Simd( pLens.x, pLens.y, 0 );
            ray.d = Normalize( pFocus - ray.o );
        }

        // Compute offset rays for _PerspectiveCamera_ ray differentials
        if ( lensRadius > 0 )
        {
            // Compute _PerspectiveCamera_ ray differentials accounting for lens
            // Sample point on lens
            Point2f pLens = lensRadius * SampleUniformDiskConcentric( sample.pLens );

            // Compute $x$ ray differential for _PerspectiveCamera_ with lens
            Vector3f::Simd dx = Normalize( Vector3f::Simd( pCamera + dxCamera ) );
            Float ft = focalDistance / dx.z( );
            Point3f::Simd pFocus = Point3f::Simd( ft * dx );
            ray.rxOrigin = Point3f::Simd( pLens.x, pLens.y, 0 );
            ray.rxDirection = Normalize( pFocus - ray.rxOrigin );

            // Compute $y$ ray differential for _PerspectiveCamera_ with lens
            Vector3f::Simd dy = Normalize( Vector3f::Simd( pCamera + dyCamera ) );
            ft = focalDistance / dy.z( );
            pFocus = Point3f::Simd( ft * dy );
            ray.ryOrigin = Point3f::Simd( pLens.x, pLens.y, 0 );
            ray.ryDirection = Normalize( pFocus - ray.ryOrigin );

        }
        else
        {
            ray.rxOrigin = ray.ryOrigin = ray.o;
            ray.rxDirection = Normalize( Vector3f::Simd( pCamera ) + dxCamera );
            ray.ryDirection = Normalize( Vector3f::Simd( pCamera ) + dyCamera );
        }

        ray.hasDifferentials = true;
        return CameraRayDifferential{ RenderFromCamera( ray ) };
    }

    std::string PerspectiveCamera::ToString( ) const
    {
        return StringPrintf( "[ PerspectiveCamera %s dxCamera: %s dyCamera: %s A: "
            "%f cosTotalWidth: %f ]",
            BaseToString( ), dxCamera, dyCamera, A, cosTotalWidth );
    }

    PerspectiveCamera* PerspectiveCamera::Create( const ParameterDictionary& parameters,
        const CameraTransform& cameraTransform,
        Film film, Medium medium, const FileLoc* loc,
        Allocator alloc )
    {
        CameraBaseParameters cameraBaseParameters( cameraTransform, film, medium, parameters,
            loc );

        Float lensradius = parameters.GetOneFloat( "lensradius", 0.f );
        Float focaldistance = parameters.GetOneFloat( "focaldistance", 1e6 );
        Float frame =
            parameters.GetOneFloat( "frameaspectratio", Float( film.FullResolution( ).x ) /
                Float( film.FullResolution( ).y ) );
        Bounds2f screen;
        if ( frame > 1.f )
        {
            screen.pMin.x = -frame;
            screen.pMax.x = frame;
            screen.pMin.y = -1.f;
            screen.pMax.y = 1.f;
        }
        else
        {
            screen.pMin.x = -1.f;
            screen.pMax.x = 1.f;
            screen.pMin.y = -1.f / frame;
            screen.pMax.y = 1.f / frame;
        }
        std::vector<Float> sw = parameters.GetFloatArray( "screenwindow" );
        if ( !sw.empty( ) )
        {
            if ( Options->fullscreen )
            {
                Warning( "\"screenwindow\" is ignored in fullscreen mode" );
            }
            else
            {
                if ( sw.size( ) == 4 )
                {
                    screen.pMin.x = sw[ 0 ];
                    screen.pMax.x = sw[ 1 ];
                    screen.pMin.y = sw[ 2 ];
                    screen.pMax.y = sw[ 3 ];
                }
                else
                {
                    Error( loc, "\"screenwindow\" should have four values" );
                }
            }
        }
        Float fov = parameters.GetOneFloat( "fov", 90. );
        return alloc.new_object<PerspectiveCamera>( cameraBaseParameters, fov, screen,
            lensradius, focaldistance );
    }

    PBRT_CPU_GPU SampledSpectrum PerspectiveCamera::We( const Ray& ray, SampledWavelengths& lambda,
        Point2f* pRasterOut ) const
    {
        // Check if ray is forward-facing with respect to the camera
        Float cosTheta = ScalarDot( ray.d, RenderFromCamera( Vector3f::Simd( 0, 0, 1 ), ray.time ) );
        if ( cosTheta <= cosTotalWidth )
            return SampledSpectrum( 0. );

        // Map ray $(\p{}, \w{})$ onto the raster grid
        Point3f::Simd pFocus = ray( ( lensRadius > 0 ? focalDistance : 1 ) / cosTheta );
        Point3f::Simd pCamera = CameraFromRender( pFocus, ray.time );
        Point3f pRaster = cameraFromRaster.ApplyInverse( pCamera );

        // Return raster position if requested
        if ( pRasterOut )
            *pRasterOut = Point2f( pRaster.x, pRaster.y );

        // Return zero importance for out of bounds points
        Bounds2f sampleBounds = film.SampleBounds( );
        if ( !Inside( Point2f( pRaster.x, pRaster.y ), sampleBounds ) )
            return SampledSpectrum( 0. );

        // Compute lens area of perspective camera
        Float lensArea = lensRadius != 0 ? ( Pi * Sqr( lensRadius ) ) : 1;

        // Return importance for point on image plane
        return SampledSpectrum( 1 / ( A * lensArea * FastPow<4>( cosTheta ) ) );
    }

    PBRT_CPU_GPU void PerspectiveCamera::PDF_We( const Ray& ray, Float* pdfPos, Float* pdfDir ) const
    {
        // Return zero PDF values if ray direction is not front-facing
        Float cosTheta = ScalarDot( ray.d, RenderFromCamera( Vector3f::Simd( 0, 0, 1 ), ray.time ) );
        if ( cosTheta <= cosTotalWidth )
        {
            *pdfPos = *pdfDir = 0;
            return;
        }

        // Map ray $(\p{}, \w{})$ onto the raster grid
        Point3f::Simd pFocus = ray( ( lensRadius > 0 ? focalDistance : 1 ) / cosTheta );
        Point3f::Simd pCamera = CameraFromRender( pFocus, ray.time );
        Point3f pRaster = cameraFromRaster.ApplyInverse( pCamera );

        // Return zero probability for out of bounds points
        Bounds2f sampleBounds = film.SampleBounds( );
        if ( !Inside( Point2f( pRaster.x, pRaster.y ), sampleBounds ) )
        {
            *pdfPos = *pdfDir = 0;
            return;
        }

        // Compute lens area  and return perspective camera probabilities
        Float lensArea = lensRadius != 0 ? ( Pi * Sqr( lensRadius ) ) : 1;
        *pdfPos = 1 / lensArea;
        *pdfDir = 1 / ( A * FastPow<3>( cosTheta ) );
    }

    PBRT_CPU_GPU pstdo::optional<CameraWiSample> PerspectiveCamera::SampleWi( const Interaction& ref, Point2f u, SampledWavelengths& lambda ) const
    {
        // Uniformly sample a lens interaction _lensIntr_
        Point2f pLens = lensRadius * SampleUniformDiskConcentric( u );
        Point3f::Simd pLensRender = RenderFromCamera( Point3f::Simd( pLens.x, pLens.y, 0 ), ref.time );
        Normal3f::Simd n = Normal3f::Simd( RenderFromCamera( Vector3f::Simd( 0, 0, 1 ), ref.time ) );
        Interaction lensIntr( pLensRender, n, ref.time, medium );

        // Find incident direction to camera _wi_ at _ref_
        Vector3f::Simd wi = lensIntr.p( ) - ref.p( );
        Float dist = ScalarLength( wi );
        wi /= dist;

        // Compute PDF for importance arriving at _ref_
        Float lensArea = lensRadius != 0 ? ( Pi * Sqr( lensRadius ) ) : 1;
        Float pdf = Sqr( dist ) / ( ScalarAbsDot( lensIntr.n, wi ) * lensArea );

        // Compute importance and return _CameraWiSample_
        Point2f pRaster;
        SampledSpectrum Wi = We( lensIntr.SpawnRay( -wi ), lambda, &pRaster );
        if ( !Wi )
            return {};
        return CameraWiSample( Wi, wi, pdf, pRaster, ref, lensIntr );
    }

    // SphericalCamera Method Definitions
    pstdo::optional<CameraRay> SphericalCamera::GenerateRay( const CameraSample& sample, SampledWavelengths& lambda ) const
    {
        // Compute spherical camera ray direction
        Point2f uv( sample.pFilm.x / film.FullResolution( ).x,
            sample.pFilm.y / film.FullResolution( ).y );
        Vector3f dir;
        if ( mapping == EquiRectangular )
        {
            // Compute ray direction using equirectangular mapping
            Float theta = Pi * uv[ 1 ], phi = 2 * Pi * uv[ 0 ];
            Float sinTheta;
            Float cosTheta;
            SinCos( theta, &sinTheta, &cosTheta );
            dir = SphericalDirection( sinTheta, cosTheta, phi );

        }
        else
        {
            // Compute ray direction using equal area mapping
            uv = WrapEqualAreaSquare( uv );
            dir = EqualAreaSquareToSphere( uv );
        }
        pstdo::swap( dir.y, dir.z );

        Ray ray( Point3f( 0, 0, 0 ), dir, SampleTime( sample.time ), medium );
        return CameraRay{ RenderFromCamera( ray ) };
    }

    SphericalCamera* SphericalCamera::Create( const ParameterDictionary& parameters,
        const CameraTransform& cameraTransform,
        Film film, Medium medium, const FileLoc* loc,
        Allocator alloc )
    {
        CameraBaseParameters cameraBaseParameters( cameraTransform, film, medium, parameters,
            loc );

        Float lensradius = parameters.GetOneFloat( "lensradius", 0.f );
        Float focaldistance = parameters.GetOneFloat( "focaldistance", 1e30f );
        Float frame =
            parameters.GetOneFloat( "frameaspectratio", Float( film.FullResolution( ).x ) /
                Float( film.FullResolution( ).y ) );
        Bounds2f screen;
        if ( frame > 1.f )
        {
            screen.pMin.x = -frame;
            screen.pMax.x = frame;
            screen.pMin.y = -1.f;
            screen.pMax.y = 1.f;
        }
        else
        {
            screen.pMin.x = -1.f;
            screen.pMax.x = 1.f;
            screen.pMin.y = -1.f / frame;
            screen.pMax.y = 1.f / frame;
        }
        std::vector<Float> sw = parameters.GetFloatArray( "screenwindow" );
        if ( !sw.empty( ) )
        {
            if ( Options->fullscreen )
            {
                Warning( "\"screenwindow\" is ignored in fullscreen mode" );
            }
            else
            {
                if ( sw.size( ) == 4 )
                {
                    screen.pMin.x = sw[ 0 ];
                    screen.pMax.x = sw[ 1 ];
                    screen.pMin.y = sw[ 2 ];
                    screen.pMax.y = sw[ 3 ];
                }
                else
                {
                    Error( loc, "\"screenwindow\" should have four values" );
                }
            }
        }
        ( void )lensradius;     // don't need this
        ( void )focaldistance;  // don't need this

        std::string m = parameters.GetOneString( "mapping", "equalarea" );
        Mapping mapping;
        if ( m == "equalarea" )
            mapping = EqualArea;
        else if ( m == "equirectangular" )
            mapping = EquiRectangular;
        else
            ErrorExit( loc,
                "%s: unknown mapping for spherical camera. (Must be "
                "\"equalarea\" or \"equirectangular\".)",
                m );

        return alloc.new_object<SphericalCamera>( cameraBaseParameters, mapping );
    }

    std::string SphericalCamera::ToString( ) const
    {
        return StringPrintf( "[ SphericalCamera %s mapping: %s ]", CameraBase::ToString( ),
            mapping == EquiRectangular ? "EquiRectangular" : "EqualArea" );
    }

    // RealisticCamera Method Definitions
    RealisticCamera::RealisticCamera( CameraBaseParameters baseParameters,
        std::vector<Float>& lensParameters, Float focusDistance,
        Float setApertureDiameter, Image apertureImage,
        Allocator alloc )
        : CameraBase( baseParameters ),
        elementInterfaces( alloc ),
        exitPupilBounds( alloc ),
        apertureImage( std::move( apertureImage ) )
    {
        // Compute film's physical extent
        Float aspect = ( Float )film.FullResolution( ).y / ( Float )film.FullResolution( ).x;
        Float diagonal = film.Diagonal( );
        Float x = Math::Sqrt( Sqr( diagonal ) / ( 1 + Sqr( aspect ) ) );
        Float y = aspect * x;
        physicalExtent = Bounds2f( Point2f( -x / 2, -y / 2 ), Point2f( x / 2, y / 2 ) );

        // Initialize _elementInterfaces_ for camera
        for ( size_t i = 0; i < lensParameters.size( ); i += 4 )
        {
            // Extract lens element configuration from _lensParameters_
            Float curvatureRadius = lensParameters[ i ] / 1000;
            Float thickness = lensParameters[ i + 1 ] / 1000;
            Float eta = lensParameters[ i + 2 ];
            Float apertureDiameter = lensParameters[ i + 3 ] / 1000;

            if ( curvatureRadius == 0 )
            {
                // Set aperture stop diameter
                setApertureDiameter /= 1000;
                if ( setApertureDiameter > apertureDiameter )
                    Warning( "Aperture diameter %f is greater than maximum possible %f. "
                        "Clamping it.",
                        setApertureDiameter, apertureDiameter );
                else
                    apertureDiameter = setApertureDiameter;
            }
            // Add element interface to end of _elementInterfaces_
            elementInterfaces.push_back(
                { curvatureRadius, thickness, eta, apertureDiameter / 2 } );
        }

        // Compute lens--film distance for given focus distance
        elementInterfaces.back( ).thickness = FocusThickLens( focusDistance );

        // Compute exit pupil bounds at sampled points on the film
        int nSamples = 64;
        exitPupilBounds.resize( nSamples );
        ParallelFor( 0, nSamples, [ & ]( int i ) {
            Float r0 = ( Float )i / nSamples * film.Diagonal( ) / 2;
            Float r1 = ( Float )( i + 1 ) / nSamples * film.Diagonal( ) / 2;
            exitPupilBounds[ i ] = BoundExitPupil( r0, r1 );
            } );

        // Compute minimum differentials for _RealisticCamera_
        FindMinimumDifferentials( this );
    }

    PBRT_CPU_GPU Float RealisticCamera::TraceLensesFromFilm( const Ray& rCamera, Ray* rOut ) const
    {
        Float elementZ = 0, weight = 1;
        // Transform _rCamera_ from camera to lens system space
        Ray rLens( rCamera.o.WithNegatedZ( ),
            rCamera.d.WithNegatedZ( ), rCamera.time );
        Point3f rLensO( rLens.o );
        Vector3f rLensD( rLens.d );
        for ( int i = elementInterfaces.size( ) - 1; i >= 0; --i )
        {
            const LensElementInterface& element = elementInterfaces[ i ];
            // Update ray from film accounting for interaction with _element_
            elementZ -= element.thickness;
            // Compute intersection of ray with lens element
            Float t;
            Normal3f n;
            bool isStop = ( element.curvatureRadius == 0 );
            if ( isStop )
            {
                // Compute _t_ at plane of aperture stop
                t = ( elementZ - rLensO.z ) / rLensD.z;
                if ( t < 0 )
                    return 0;

            }
            else
            {
                // Intersect ray with element to compute _t_ and _n_
                Float radius = element.curvatureRadius;
                Float zCenter = elementZ + element.curvatureRadius;
                if ( !IntersectSphericalElement( radius, zCenter, rLens, &t, &n ) )
                    return 0;
            }
            NDCHECK_GE( t, 0 );

            // Test intersection point against element aperture
            Point3f pHit = rLens( t );
            if ( isStop && apertureImage )
            {
                // Check intersection point against _apertureImage_
                Point2f uv( ( pHit.x / element.apertureRadius + 1 ) / 2,
                    ( pHit.y / element.apertureRadius + 1 ) / 2 );
                weight = apertureImage.BilerpChannel( uv, 0, WrapMode::Black );
                if ( weight == 0 )
                    return 0;

            }
            else
            {
                // Check intersection point against spherical aperture
                if ( Sqr( pHit.x ) + Sqr( pHit.y ) > Sqr( element.apertureRadius ) )
                    return 0;
            }
            rLens.o = pHit;
            rLensO = rLens.o;

            // Update ray path for element interface interaction
            if ( !isStop )
            {
                Vector3f::Simd w;
                Float eta_i = element.eta;
                Float eta_t = ( i > 0 && elementInterfaces[ i - 1 ].eta != 0 )
                    ? elementInterfaces[ i - 1 ].eta
                    : 1;
                if ( !Refract( Normalize( -rLens.d ), n, eta_t / eta_i, nullptr, &w ) )
                    return 0;
                /*
                w = Math::Refract( Normalize( -rLens.d ), n, eta_t / eta_i );
                if ( w == 0 )
                {
                    return 0;
                }
                */
                rLens.d = w;
            }
        }
        // Transform lens system space ray back to camera space
        if ( rOut )
            *rOut = Ray( rLens.o.WithNegatedZ( ),
                rLens.d.WithNegatedZ( ), rLens.time );

        return weight;
    }

    void RealisticCamera::ComputeCardinalPoints( Ray rIn, Ray rOut, Float* pz, Float* fz )
    {
        Point3f rInO( rIn.o );
        Point3f rOutO( rOut.o );
        auto rOutDX = rOut.d.x( );

        Float tf = -rOutO.x / rOutDX;
        *fz = -rOut( tf ).z( );
        Float tp = ( rInO.x - rOutO.x ) / rOutDX;
        *pz = -rOut( tp ).z( );
    }

    void RealisticCamera::ComputeThickLensApproximation( Float pz[ 2 ], Float fz[ 2 ] ) const
    {
        // Find height $x$ from optical axis for parallel rays
        Float x = .001f * film.Diagonal( );

        // Compute cardinal points for film side of lens system
        Ray rScene( Point3f( x, 0, LensFrontZ( ) + 1 ), Vector3f( 0, 0, -1 ) );
        Ray rFilm;
        if ( !TraceLensesFromScene( rScene, &rFilm ) )
            ErrorExit( "Unable to trace ray from scene to film for thick lens "
                "approximation. Is aperture stop extremely small?" );
        ComputeCardinalPoints( rScene, rFilm, &pz[ 0 ], &fz[ 0 ] );

        // Compute cardinal points for scene side of lens system
        rFilm = Ray( Point3f( x, 0, LensRearZ( ) - 1 ), Vector3f( 0, 0, 1 ) );
        if ( TraceLensesFromFilm( rFilm, &rScene ) == 0 )
            ErrorExit( "Unable to trace ray from film to scene for thick lens "
                "approximation. Is aperture stop extremely small?" );
        ComputeCardinalPoints( rFilm, rScene, &pz[ 1 ], &fz[ 1 ] );
    }

    Float RealisticCamera::FocusThickLens( Float focusDistance )
    {
        Float pz[ 2 ], fz[ 2 ];
        ComputeThickLensApproximation( pz, fz );
        NLOG_VERBOSE( "Cardinal points: p' = %f f' = %f, p = %f f = %f.\n", pz[ 0 ], fz[ 0 ], pz[ 1 ],
            fz[ 1 ] );
        NLOG_VERBOSE( "Effective focal length %f\n", fz[ 0 ] - pz[ 0 ] );
        // Compute translation of lens, _delta_, to focus at _focusDistance_
        Float f = fz[ 0 ] - pz[ 0 ];
        Float z = -focusDistance;
        Float c = ( pz[ 1 ] - z - pz[ 0 ] ) * ( pz[ 1 ] - z - 4 * f - pz[ 0 ] );
        if ( c <= 0 )
            ErrorExit( "Coefficient must be positive. It looks focusDistance %f "
                " is too short for a given lenses configuration",
                focusDistance );
        Float delta = ( pz[ 1 ] - z + pz[ 0 ] - Math::Sqrt( c ) ) / 2;

        return elementInterfaces.back( ).thickness + delta;
    }

    Bounds2f RealisticCamera::BoundExitPupil( Float filmX0, Float filmX1 ) const
    {
        Bounds2f pupilBounds;
        // Sample a collection of points on the rear lens to find exit pupil
        const int nSamples = 1024 * 1024;
        // Compute bounding box of projection of rear element on sampling plane
        Float rearRadius = RearElementRadius( );
        Bounds2f projRearBounds( Point2f( -1.5f * rearRadius, -1.5f * rearRadius ),
            Point2f( 1.5f * rearRadius, 1.5f * rearRadius ) );

        for ( int i = 0; i < nSamples; ++i )
        {
            // Find location of sample points on $x$ segment and rear lens element
            Point3f pFilm( Lerp2( ( i + 0.5f ) / nSamples, filmX0, filmX1 ), 0, 0 );
            Float u[ 2 ] = { RadicalInverse( 0, i ), RadicalInverse( 1, i ) };
            Point3f pRear( Lerp2( u[ 0 ], projRearBounds.pMin.x, projRearBounds.pMax.x ),
                Lerp2( u[ 1 ], projRearBounds.pMin.y, projRearBounds.pMax.y ),
                LensRearZ( ) );

            // Expand pupil bounds if ray makes it through the lens system
            if ( !Inside( Point2f( pRear.x, pRear.y ), pupilBounds ) &&
                TraceLensesFromFilm( Ray( pFilm, pRear - pFilm ), nullptr ) )
                pupilBounds = Union( pupilBounds, Point2f( pRear.x, pRear.y ) );
        }

        // Return degenerate bounds if no rays made it through the lens system
        if ( pupilBounds.IsDegenerate( ) )
        {
            NLOG_VERBOSE( "Unable to find exit pupil in x = [%f,%f] on film.", filmX0, filmX1 );
            return pupilBounds;
        }

        // Expand bounds to account for sample spacing
        pupilBounds =
            Expand( pupilBounds, 2 * ScalarLength( projRearBounds.Diagonal( ) ) / Math::Sqrt( static_cast<float>( nSamples ) ) );

        return pupilBounds;
    }

    PBRT_CPU_GPU pstdo::optional<ExitPupilSample> RealisticCamera::SampleExitPupil( Point2f pFilm,
        Point2f uLens ) const
    {
        // Find exit pupil bound for sample distance from film center
        Float rFilm = Math::Hypot( pFilm.x, pFilm.y );
        int rIndex = rFilm / ( film.Diagonal( ) / 2 ) * exitPupilBounds.size( );
        rIndex = std::min<int>( exitPupilBounds.size( ) - 1, rIndex );
        Bounds2f pupilBounds = exitPupilBounds[ rIndex ];
        if ( pupilBounds.IsDegenerate( ) )
            return {};

        // Generate sample point inside exit pupil bound
        Point2f pLens = pupilBounds.Lerp2( uLens );
        Float pdf = 1 / pupilBounds.Area( );

        // Return sample point rotated by angle of _pFilm_ with $+x$ axis
        Float sinTheta = ( rFilm != 0 ) ? pFilm.y / rFilm : 0;
        Float cosTheta = ( rFilm != 0 ) ? pFilm.x / rFilm : 1;
        Point3f pPupil( cosTheta * pLens.x - sinTheta * pLens.y,
            sinTheta * pLens.x + cosTheta * pLens.y, LensRearZ( ) );
        return ExitPupilSample{ pPupil, pdf };
    }

    pstdo::optional<CameraRay> RealisticCamera::GenerateRay( const CameraSample& sample, SampledWavelengths& lambda ) const
    {
        // Find point on film, _pFilm_, corresponding to _sample.pFilm_
        Point2f s( sample.pFilm.x / film.FullResolution( ).x,
            sample.pFilm.y / film.FullResolution( ).y );
        Point2f pFilm2 = physicalExtent.Lerp2( s );
        Point3f pFilm( -pFilm2.x, pFilm2.y, 0 );

        // Trace ray from _pFilm_ through lens system
        pstdo::optional<ExitPupilSample> eps =
            SampleExitPupil( Point2f( pFilm.x, pFilm.y ), sample.pLens );
        if ( !eps )
            return {};
        Ray rFilm( pFilm, eps->pPupil - pFilm );
        Ray ray;
        Float weight = TraceLensesFromFilm( rFilm, &ray );
        if ( weight == 0 )
            return {};

        // Finish initialization of _RealisticCamera_ ray
        ray.time = SampleTime( sample.time );
        ray.medium = medium;
        ray = RenderFromCamera( ray );
        ray.d = Normalize( ray.d );

        // Compute weighting for _RealisticCamera_ ray
        Float cosTheta = Normalize( rFilm.d ).z( );
        weight *= FastPow<4>( cosTheta ) / ( eps->pdf * Sqr( LensRearZ( ) ) );

        return CameraRay{ ray, SampledSpectrum( weight ) };
    }

    NSTAT_PERCENT( "Camera/Rays vignetted by lens system", vignettedRays, totalRays );

    std::string RealisticCamera::LensElementInterface::ToString( ) const
    {
        return StringPrintf( "[ LensElementInterface curvatureRadius: %f thickness: %f "
            "eta: %f apertureRadius: %f ]",
            curvatureRadius, thickness, eta, apertureRadius );
    }

    PBRT_CPU_GPU Float RealisticCamera::TraceLensesFromScene( const Ray& rCamera, Ray* rOut ) const
    {
        Float elementZ = -LensFrontZ( );
        // Transform _rCamera_ from camera to lens system space
        const Transform LensFromCamera = Scale( 1, 1, -1 );
        Ray rLens = LensFromCamera( rCamera );
        Point3f rLensO( rLens.o );
        Vector3f rLensD( rLens.d );
        for ( size_t i = 0; i < elementInterfaces.size( ); ++i )
        {
            const LensElementInterface& element = elementInterfaces[ i ];
            // Compute intersection of ray with lens element
            Float t;
            Normal3f n;
            bool isStop = ( element.curvatureRadius == 0 );
            if ( isStop )
            {
                t = ( elementZ - rLensO.z ) / rLensD.z;
                if ( t < 0 )
                    return 0;
            }
            else
            {
                Float radius = element.curvatureRadius;
                Float zCenter = elementZ + element.curvatureRadius;
                if ( !IntersectSphericalElement( radius, zCenter, rLens, &t, &n ) )
                    return 0;
            }

            // Test intersection point against element aperture
            // Don't worry about the aperture image here.
            Point3f pHit = rLens( t );
            Float r2 = pHit.x * pHit.x + pHit.y * pHit.y;
            if ( r2 > element.apertureRadius * element.apertureRadius )
                return 0;
            rLens.o = pHit;
            rLensO = rLens.o;

            // Update ray path for from-scene element interface interaction
            if ( !isStop )
            {
                Vector3f::Simd wt;
                Float eta_i = ( i == 0 || elementInterfaces[ i - 1 ].eta == 0 )
                    ? 1
                    : elementInterfaces[ i - 1 ].eta;
                Float eta_t = ( elementInterfaces[ i ].eta != 0 ) ? elementInterfaces[ i ].eta : 1;
                if ( !Refract( Normalize( -rLens.d ), n, eta_t / eta_i, nullptr, &wt ) )
                    return 0;
                //wt = Math::Refract( Normalize( -rLens.d ), n, eta_t / eta_i );
                //if ( wt == 0 )
                //{
                //    return 0;
                //}
                rLens.d = wt;
            }
            elementZ += element.thickness;
        }
        // Transform _rLens_ from lens system space back to camera space
        if ( rOut )
            *rOut = Ray( rLens.o.WithNegatedZ( ),
                rLens.d.WithNegatedZ( ), rLens.time );
        return 1;
    }

    void RealisticCamera::DrawLensSystem( ) const
    {
        Float sumz = -LensFrontZ( );
        Float z = sumz;
        for ( size_t i = 0; i < elementInterfaces.size( ); ++i )
        {
            const LensElementInterface& element = elementInterfaces[ i ];
            Float r = element.curvatureRadius;
            if ( r == 0 )
            {
                // stop
                printf( "{Thick, Line[{{%f, %f}, {%f, %f}}], ", z, element.apertureRadius, z,
                    2 * element.apertureRadius );
                printf( "Line[{{%f, %f}, {%f, %f}}]}, ", z, -element.apertureRadius, z,
                    -2 * element.apertureRadius );
            }
            else
            {
                Float theta = Math::FastAbs( SafeASin( element.apertureRadius / r ) );
                if ( r > 0 )
                {
                    // convex as seen from front of lens
                    Float t0 = Pi - theta;
                    Float t1 = Pi + theta;
                    printf( "Circle[{%f, 0}, %f, {%f, %f}], ", z + r, r, t0, t1 );
                }
                else
                {
                    // concave as seen from front of lens
                    Float t0 = -theta;
                    Float t1 = theta;
                    printf( "Circle[{%f, 0}, %f, {%f, %f}], ", z + r, -r, t0, t1 );
                }
                if ( element.eta != 0 && element.eta != 1 )
                {
                    // connect top/bottom to next element
                    NCHECK_LT( i + 1, elementInterfaces.size( ) );
                    Float nextApertureRadius = elementInterfaces[ i + 1 ].apertureRadius;
                    Float h = std::max( element.apertureRadius, nextApertureRadius );
                    Float hlow = std::min( element.apertureRadius, nextApertureRadius );

                    Float zp0, zp1;
                    if ( r > 0 )
                    {
                        zp0 = z + element.curvatureRadius -
                            element.apertureRadius / Math::Tan( theta );
                    }
                    else
                    {
                        zp0 = z + element.curvatureRadius +
                            element.apertureRadius / Math::Tan( theta );
                    }

                    Float nextCurvatureRadius = elementInterfaces[ i + 1 ].curvatureRadius;
                    Float nextTheta =
                        Math::FastAbs( SafeASin( nextApertureRadius / nextCurvatureRadius ) );
                    if ( nextCurvatureRadius > 0 )
                    {
                        zp1 = z + element.thickness + nextCurvatureRadius -
                            nextApertureRadius / Math::Tan( nextTheta );
                    }
                    else
                    {
                        zp1 = z + element.thickness + nextCurvatureRadius +
                            nextApertureRadius / Math::Tan( nextTheta );
                    }

                    // Connect tops
                    printf( "Line[{{%f, %f}, {%f, %f}}], ", zp0, h, zp1, h );
                    printf( "Line[{{%f, %f}, {%f, %f}}], ", zp0, -h, zp1, -h );

                    // vertical lines when needed to close up the element profile
                    if ( element.apertureRadius < nextApertureRadius )
                    {
                        printf( "Line[{{%f, %f}, {%f, %f}}], ", zp0, h, zp0, hlow );
                        printf( "Line[{{%f, %f}, {%f, %f}}], ", zp0, -h, zp0, -hlow );
                    }
                    else if ( element.apertureRadius > nextApertureRadius )
                    {
                        printf( "Line[{{%f, %f}, {%f, %f}}], ", zp1, h, zp1, hlow );
                        printf( "Line[{{%f, %f}, {%f, %f}}], ", zp1, -h, zp1, -hlow );
                    }
                }
            }
            z += element.thickness;
        }

        // 24mm height for 35mm film
        printf( "Line[{{0, -.012}, {0, .012}}], " );
        // optical axis
        printf( "Line[{{0, 0}, {%f, 0}}] ", 1.2f * sumz );
    }

    void RealisticCamera::DrawRayPathFromFilm( const Ray& r, bool arrow,
        bool toOpticalIntercept ) const
    {
        Float elementZ = 0;
        // Transform _ray_ from camera to lens system space
        static const Transform LensFromCamera = Scale( 1, 1, -1 );
        Ray ray = LensFromCamera( r );
        printf( "{ " );
        if ( TraceLensesFromFilm( r, nullptr ) == 0 )
        {
            printf( "Dashed, RGBColor[.8, .5, .5]" );
        }
        else
            printf( "RGBColor[.5, .5, .8]" );

        Point3f rayO( ray.o );
        Vector3f rayD( ray.d );
        for ( int i = elementInterfaces.size( ) - 1; i >= 0; --i )
        {
            const LensElementInterface& element = elementInterfaces[ i ];
            elementZ -= element.thickness;
            bool isStop = ( element.curvatureRadius == 0 );
            // Compute intersection of ray with lens element
            Float t;
            Normal3f n;
            if ( isStop )
                t = -( rayO.z - elementZ ) / rayD.z;
            else
            {
                Float radius = element.curvatureRadius;
                Float zCenter = elementZ + element.curvatureRadius;
                if ( !IntersectSphericalElement( radius, zCenter, ray, &t, &n ) )
                    goto done;
            }
            NCHECK_GE( t, 0 );

            printf( ", Line[{{%f, %f}, {%f, %f}}]", rayO.z, rayO.x, ray( t ).z( ), ray( t ).x( ) );

            // Test intersection point against element aperture
            Point3f pHit = ray( t );
            Float r2 = pHit.x * pHit.x + pHit.y * pHit.y;
            Float apertureRadius2 = element.apertureRadius * element.apertureRadius;
            if ( r2 > apertureRadius2 )
                goto done;
            ray.o = pHit;
            rayO = ray.o;

            // Update ray path for element interface interaction
            if ( !isStop )
            {
                Vector3f::Simd wt;
                Float eta_i = element.eta;
                Float eta_t = ( i > 0 && elementInterfaces[ i - 1 ].eta != 0 )
                    ? elementInterfaces[ i - 1 ].eta
                    : 1;
                if ( !Refract( Normalize( -ray.d ), n, eta_t / eta_i, nullptr, &wt ) )
                    goto done;
                //wt = Math::Refract( Normalize( -ray.d ), n, eta_t / eta_i );
                //if ( wt == 0 )
                //{
                //    goto done;
                //}
                ray.d = wt;
                rayD = ray.d;
            }
        }

        ray.d = Normalize( ray.d );
        rayD = ray.d;
        {
            Float ta = Math::FastAbs( elementZ / 4 );
            if ( toOpticalIntercept )
            {
                ta = -rayO.x / rayD.x;
                printf( ", Point[{%f, %f}]", ray( ta ).z( ), ray( ta ).x( ) );
            }
            printf( ", %s[{{%f, %f}, {%f, %f}}]", arrow ? "Arrow" : "Line", ray.o.z( ), ray.o.x( ),
                ray( ta ).z( ), ray( ta ).x( ) );

            // overdraw the optical axis if needed...
            if ( toOpticalIntercept )
                printf( ", Line[{{%f, 0}, {%f, 0}}]", ray.o.z( ), ray( ta ).z( ) * 1.05f );
        }

    done:
        printf( "}" );
    }

    void RealisticCamera::DrawRayPathFromScene( const Ray& r, bool arrow,
        bool toOpticalIntercept ) const
    {
        Float elementZ = LensFrontZ( ) * -1;

        // Transform _ray_ from camera to lens system space
        static const Transform LensFromCamera = Scale( 1, 1, -1 );
        Ray ray = LensFromCamera( r );
        Point3f rayO( ray.o );
        Vector3f rayD( ray.d );
        for ( size_t i = 0; i < elementInterfaces.size( ); ++i )
        {
            const LensElementInterface& element = elementInterfaces[ i ];
            bool isStop = ( element.curvatureRadius == 0 );
            // Compute intersection of ray with lens element
            Float t;
            Normal3f n;
            if ( isStop )
                t = -( rayO.z - elementZ ) / rayD.z;
            else
            {
                Float radius = element.curvatureRadius;
                Float zCenter = elementZ + element.curvatureRadius;
                if ( !IntersectSphericalElement( radius, zCenter, ray, &t, &n ) )
                    return;
            }
            NCHECK_GE( t, 0.f );

            printf( "Line[{{%f, %f}, {%f, %f}}],", rayO.z, rayO.x, ray( t ).z( ), ray( t ).x( ) );

            // Test intersection point against element aperture
            Point3f pHit = ray( t );
            Float r2 = pHit.x * pHit.x + pHit.y * pHit.y;
            Float apertureRadius2 = element.apertureRadius * element.apertureRadius;
            if ( r2 > apertureRadius2 )
                return;
            ray.o = pHit;
            rayO = ray.o;

            // Update ray path for from-scene element interface interaction
            if ( !isStop )
            {
                Vector3f::Simd wt;
                Float eta_i = ( i == 0 || elementInterfaces[ i - 1 ].eta == 0.f )
                    ? 1.f
                    : elementInterfaces[ i - 1 ].eta;
                Float eta_t =
                    ( elementInterfaces[ i ].eta != 0.f ) ? elementInterfaces[ i ].eta : 1.f;
                if ( !Refract( Normalize( -ray.d ), n, eta_t / eta_i, nullptr, &wt ) )
                    return;
                //wt = Math::Refract( Normalize( -ray.d ), n, eta_t / eta_i );
                //if ( wt == 0 )
                //{
                //    return;
                //}
                ray.d = wt;
                rayD = ray.d;
            }
            elementZ += element.thickness;
        }

        // go to the film plane by default
        {
            Float ta = -rayO.z / rayD.z;
            if ( toOpticalIntercept )
            {
                ta = -rayO.x / rayD.x;
                printf( "Point[{%f, %f}], ", ray( ta ).z( ), ray( ta ).x() );
            }
            printf( "%s[{{%f, %f}, {%f, %f}}]", arrow ? "Arrow" : "Line", rayO.z, rayO.x,
                ray( ta ).z( ), ray( ta ).x( ) );
        }
    }

    void RealisticCamera::RenderExitPupil( Float sx, Float sy, const char* filename ) const
    {
        Point3f pFilm( sx, sy, 0 );

        const int nSamples = 2048;
        Image image( PixelFormat::Float, { nSamples, nSamples }, { "Y" } );

        for ( int y = 0; y < nSamples; ++y )
        {
            Float fy = ( Float )y / ( Float )( nSamples - 1 );
            Float ly = Lerp2( fy, -RearElementRadius( ), RearElementRadius( ) );
            for ( int x = 0; x < nSamples; ++x )
            {
                Float fx = ( Float )x / ( Float )( nSamples - 1 );
                Float lx = Lerp2( fx, -RearElementRadius( ), RearElementRadius( ) );

                Point3f pRear( lx, ly, LensRearZ( ) );

                if ( lx * lx + ly * ly > RearElementRadius( ) * RearElementRadius( ) )
                    image.SetChannel( { x, y }, 0, 1. );
                else if ( TraceLensesFromFilm( Ray( pFilm, pRear - pFilm ), nullptr ) )
                    image.SetChannel( { x, y }, 0, 0.5 );
                else
                    image.SetChannel( { x, y }, 0, 0. );
            }
        }

        image.Write( filename );
    }

    void RealisticCamera::TestExitPupilBounds( ) const
    {
        Float filmDiagonal = film.Diagonal( );

        static RNG rng;

        Float u = rng.Uniform<Float>( );
        Point3f pFilm( u * filmDiagonal / 2, 0, 0 );

        Float r = pFilm.x / ( filmDiagonal / 2 );
        int pupilIndex = std::min<int>( exitPupilBounds.size( ) - 1,
            pstdo::floor( r * ( exitPupilBounds.size( ) - 1 ) ) );
        Bounds2f pupilBounds = exitPupilBounds[ pupilIndex ];
        if ( pupilIndex + 1 < ( int )exitPupilBounds.size( ) )
            pupilBounds = Union( pupilBounds, exitPupilBounds[ pupilIndex + 1 ] );

        // Now, randomly pick points on the aperture and see if any are outside
        // of pupil bounds...
        for ( int i = 0; i < 1000; ++i )
        {
            Point2f u2{ rng.Uniform<Float>( ), rng.Uniform<Float>( ) };
            Point2f pd = SampleUniformDiskConcentric( u2 );
            pd *= RearElementRadius( );

            Ray testRay( pFilm, Point3f( pd.x, pd.y, 0.f ) - pFilm );
            Ray testOut;
            if ( !TraceLensesFromFilm( testRay, &testOut ) )
                continue;

            if ( !Inside( pd, pupilBounds ) )
            {
                fprintf( stderr,
                    "Aha! (%f,%f) went through, but outside bounds (%f,%f) - "
                    "(%f,%f)\n",
                    pd.x, pd.y, pupilBounds.pMin[ 0 ], pupilBounds.pMin[ 1 ],
                    pupilBounds.pMax[ 0 ], pupilBounds.pMax[ 1 ] );
                RenderExitPupil(
                    ( Float )pupilIndex / exitPupilBounds.size( ) * filmDiagonal / 2.f, 0.f,
                    "low.exr" );
                RenderExitPupil(
                    ( Float )( pupilIndex + 1 ) / exitPupilBounds.size( ) * filmDiagonal / 2.f,
                    0.f, "high.exr" );
                RenderExitPupil( pFilm.x, 0.f, "mid.exr" );
                exit( 0 );
            }
        }
        fprintf( stderr, "." );
    }

    std::string RealisticCamera::ToString( ) const
    {
        return StringPrintf(
            "[ RealisticCamera %s elementInterfaces: %s exitPupilBounds: %s ]",
            CameraBase::ToString( ), elementInterfaces, exitPupilBounds );
    }

    RealisticCamera* RealisticCamera::Create( const ParameterDictionary& parameters,
        const CameraTransform& cameraTransform,
        Film film, Medium medium, const FileLoc* loc,
        Allocator alloc )
    {
        CameraBaseParameters cameraBaseParameters( cameraTransform, film, medium, parameters,
            loc );

        // Realistic camera-specific parameters
        std::string lensFile = ResolveFilename( parameters.GetOneString( "lensfile", "" ) );
        Float apertureDiameter = parameters.GetOneFloat( "aperturediameter", 1.0 );
        Float focusDistance = parameters.GetOneFloat( "focusdistance", 10.0 );

        if ( lensFile.empty( ) )
        {
            Error( loc, "No lens description file supplied!" );
            return nullptr;
        }
        // Load element data from lens description file
        std::vector<Float> lensParameters = ReadFloatFile( lensFile );
        if ( lensParameters.empty( ) )
        {
            Error( loc, "Error reading lens specification file \"%s\".", lensFile );
            return nullptr;
        }
        if ( lensParameters.size( ) % 4 != 0 )
        {
            Error( loc,
                "%s: excess values in lens specification file; "
                "must be multiple-of-four values, read %d.",
                lensFile, ( int )lensParameters.size( ) );
            return nullptr;
        }

        int builtinRes = 256;
        auto rasterize = [ & ]( pstdo::span<const Point2f> vert ) {
            Image image( PixelFormat::Float, { builtinRes, builtinRes }, { "Y" }, nullptr, alloc );

            for ( int y = 0; y < image.Resolution( ).y; ++y )
                for ( int x = 0; x < image.Resolution( ).x; ++x )
                {
                    Point2f p( -1 + 2 * ( x + 0.5f ) / image.Resolution( ).x,
                        -1 + 2 * ( y + 0.5f ) / image.Resolution( ).y );
                    int windingNumber = 0;
                    // Test against edges
                    for ( int i = 0; i < vert.size( ); ++i )
                    {
                        int i1 = ( i + 1 ) % vert.size( );
                        Float e = ( p[ 0 ] - vert[ i ][ 0 ] ) * ( vert[ i1 ][ 1 ] - vert[ i ][ 1 ] ) -
                            ( p[ 1 ] - vert[ i ][ 1 ] ) * ( vert[ i1 ][ 0 ] - vert[ i ][ 0 ] );
                        if ( vert[ i ].y <= p.y )
                        {
                            if ( vert[ i1 ].y > p.y && e > 0 )
                                ++windingNumber;
                        }
                        else if ( vert[ i1 ].y <= p.y && e < 0 )
                            --windingNumber;
                    }

                    image.SetChannel( { x, y }, 0, windingNumber == 0 ? 0.f : 1.f );
                }

            return image;
            };

        std::string apertureName = parameters.GetOneString( "aperture", "" );
        Image apertureImage( alloc );
        if ( !apertureName.empty( ) )
        {
            // built-in diaphragm shapes
            if ( apertureName == "gaussian" )
            {
                apertureImage = Image( PixelFormat::Float, { builtinRes, builtinRes }, { "Y" },
                    nullptr, alloc );
                for ( int y = 0; y < apertureImage.Resolution( ).y; ++y )
                    for ( int x = 0; x < apertureImage.Resolution( ).x; ++x )
                    {
                        Point2f uv( -1 + 2 * ( x + 0.5f ) / apertureImage.Resolution( ).x,
                            -1 + 2 * ( y + 0.5f ) / apertureImage.Resolution( ).y );
                        Float r2 = Sqr( uv.x ) + Sqr( uv.y );
                        Float sigma2 = 1;
                        Float v = std::max<Float>(
                            0, Math::Exp( -r2 / sigma2 ) - Math::Exp( -1 / sigma2 ) );
                        apertureImage.SetChannel( { x, y }, 0, v );
                    }
            }
            else if ( apertureName == "square" )
            {
                apertureImage = Image( PixelFormat::Float, { builtinRes, builtinRes }, { "Y" },
                    nullptr, alloc );
                for ( int y = .25 * builtinRes; y < .75 * builtinRes; ++y )
                    for ( int x = .25 * builtinRes; x < .75 * builtinRes; ++x )
                        apertureImage.SetChannel( { x, y }, 0, 4.f );
            }
            else if ( apertureName == "pentagon" )
            {
                // https://mathworld.wolfram.com/RegularPentagon.html
                constexpr Float c1 = ( Math::Sqrt( 5.f ) - 1 ) / 4;
                constexpr Float c2 = ( Math::Sqrt( 5.f ) + 1 ) / 4;
                constexpr Float s1 = Math::Sqrt( 10.f + 2.f * Math::Sqrt( 5.f ) ) / 4;
                constexpr Float s2 = Math::Sqrt( 10.f - 2.f * Math::Sqrt( 5.f ) ) / 4;
                // Vertices in CW order.
                Point2f vert[ 5 ] = { Point2f( 0, 1 ), {s1, c1}, {s2, -c2}, {-s2, -c2}, {-s1, c1} };
                // Scale down slightly
                for ( int i = 0; i < 5; ++i )
                    vert[ i ] *= .8f;
                apertureImage = rasterize( vert );
            }
            else if ( apertureName == "star" )
            {
                // 5-sided. Vertices are two pentagons--inner and outer radius
                pstdo::array<Point2f, 10> vert;
                for ( int i = 0; i < 10; ++i )
                {
                    // inner radius: https://math.stackexchange.com/a/2136996
                    constexpr Float r1 = ( Math::Cos( Deg2Rad( 72.f ) ) / Math::Cos( Deg2Rad( 36.f ) ) );
                    Float r = ( i & 1 ) ? 1.f : r1;
                    Float phi = Pi * i / 5.f;
                    Float sinPhi;
                    Float cosPhi;
                    SinCos( phi, &sinPhi, &cosPhi );
                    vert[ i ] = Point2f( r * cosPhi, r * sinPhi );
                }
                std::reverse( vert.begin( ), vert.end( ) );
                apertureImage = rasterize( vert );
            }
            else
            {
                ImageAndMetadata im = Image::Read( ResolveFilename( apertureName ), alloc );
                apertureImage = std::move( im.image );
                if ( apertureImage.NChannels( ) > 1 )
                {
                    ImageChannelDesc rgbDesc = apertureImage.GetChannelDesc( { "R", "G", "B" } );
                    if ( !rgbDesc )
                        ErrorExit( "%s: didn't find R, G, B channels to average for "
                            "aperture image.",
                            apertureName );

                    Image mono( PixelFormat::Float, apertureImage.Resolution( ), { "Y" }, nullptr,
                        alloc );
                    for ( int y = 0; y < mono.Resolution( ).y; ++y )
                        for ( int x = 0; x < mono.Resolution( ).x; ++x )
                        {
                            Float avg = apertureImage.GetChannels( { x, y }, rgbDesc ).Average( );
                            mono.SetChannel( { x, y }, 0, avg );
                        }

                    apertureImage = std::move( mono );
                }
            }

            if ( apertureImage )
            {
                apertureImage.FlipY( );

                // Normalize it so that brightness matches a circular aperture
                Float sum = 0;
                for ( int y = 0; y < apertureImage.Resolution( ).y; ++y )
                    for ( int x = 0; x < apertureImage.Resolution( ).x; ++x )
                        sum += apertureImage.GetChannel( { x, y }, 0 );
                Float avg =
                    sum / ( apertureImage.Resolution( ).x * apertureImage.Resolution( ).y );

                Float scale = ( Pi / 4 ) / avg;
                for ( int y = 0; y < apertureImage.Resolution( ).y; ++y )
                    for ( int x = 0; x < apertureImage.Resolution( ).x; ++x )
                        apertureImage.SetChannel( { x, y }, 0,
                            apertureImage.GetChannel( { x, y }, 0 ) * scale );
            }
        }

        return alloc.new_object<RealisticCamera>( cameraBaseParameters, lensParameters,
            focusDistance, apertureDiameter,
            std::move( apertureImage ), alloc );
    }

}