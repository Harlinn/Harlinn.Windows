#pragma once
#ifndef PBRTO_NEWCAMERAS_H_
#define PBRTO_NEWCAMERAS_H_

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
#include <pbrto/base/NewFilm.h>
#include <pbrto/NewFilm.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/NewRay.h>
#include <pbrto/NewSamplers.h>
#include <pbrto/util/NewImage.h>
#include <pbrto/util/NewScattering.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace pbrto
{

    // CameraTransform Definition
    class CameraTransform
    {
        // CameraTransform Private Members
        AnimatedTransform renderFromCamera;
        Transform worldFromRender;
    public:
        // CameraTransform Public Methods
        CameraTransform( ) = default;
        explicit CameraTransform( const AnimatedTransform& worldFromCamera );

        PBRT_CPU_GPU
            Point3f RenderFromCamera( Point3f p, Float time ) const
        {
            return renderFromCamera( p, time );
        }
        PBRT_CPU_GPU
            Point3f CameraFromRender( Point3f p, Float time ) const
        {
            return renderFromCamera.ApplyInverse( p, time );
        }
        PBRT_CPU_GPU
            Point3f RenderFromWorld( Point3f p ) const
        {
            return worldFromRender.ApplyInverse( p );
        }

        PBRT_CPU_GPU
            Transform RenderFromWorld( ) const
        {
            return Inverse( worldFromRender );
        }
        PBRT_CPU_GPU
            Transform CameraFromRender( Float time ) const
        {
            return Inverse( renderFromCamera.Interpolate( time ) );
        }
        PBRT_CPU_GPU
            Transform CameraFromWorld( Float time ) const
        {
            return Inverse( worldFromRender * renderFromCamera.Interpolate( time ) );
        }

        PBRT_CPU_GPU
            bool CameraFromRenderHasScale( ) const
        {
            return renderFromCamera.HasScale( );
        }

        PBRT_CPU_GPU
            Vector3f RenderFromCamera( Vector3f v, Float time ) const
        {
            return renderFromCamera( v, time );
        }

        PBRT_CPU_GPU
            Normal3f RenderFromCamera( Normal3f n, Float time ) const
        {
            return renderFromCamera( n, time );
        }

        PBRT_CPU_GPU
            Ray RenderFromCamera( const Ray& r ) const
        {
            return renderFromCamera( r );
        }

        PBRT_CPU_GPU
            RayDifferential RenderFromCamera( const RayDifferential& r ) const
        {
            return renderFromCamera( r );
        }

        PBRT_CPU_GPU
            Vector3f CameraFromRender( Vector3f v, Float time ) const
        {
            return renderFromCamera.ApplyInverse( v, time );
        }

        PBRT_CPU_GPU
            Normal3f CameraFromRender( Normal3f v, Float time ) const
        {
            return renderFromCamera.ApplyInverse( v, time );
        }

        PBRT_CPU_GPU
            const AnimatedTransform& RenderFromCamera( ) const
        {
            return renderFromCamera;
        }

        PBRT_CPU_GPU
            const Transform& WorldFromRender( ) const
        {
            return worldFromRender;
        }

        std::string ToString( ) const;
    };

    // CameraWiSample Definition
    struct CameraWiSample
    {
        SampledSpectrum Wi;
        Vector3f wi;
        Float pdf;
        Point2f pRaster;
        Interaction pRef;
        Interaction pLens;

        // CameraWiSample Public Methods
        CameraWiSample( ) = default;
        PBRT_CPU_GPU
            CameraWiSample( const SampledSpectrum& Wi, const Vector3f& wi, Float pdf, Point2f pRaster, const Interaction& pRef, const Interaction& pLens )
            : Wi( Wi ), wi( wi ), pdf( pdf ), pRaster( pRaster ), pRef( pRef ), pLens( pLens )
        {
        }
    };

    // CameraRay Definition
    struct CameraRay
    {
        Ray ray;
        SampledSpectrum weight = SampledSpectrum( 1 );
    };

    // CameraRayDifferential Definition
    struct CameraRayDifferential
    {
        RayDifferential ray;
        SampledSpectrum weight = SampledSpectrum( 1 );
    };

    // CameraBaseParameters Definition
    struct CameraBaseParameters
    {
        CameraTransform cameraTransform;
        Float shutterOpen = 0, shutterClose = 1;
        Film film;
        Medium medium;

        CameraBaseParameters( ) = default;
        CameraBaseParameters( const CameraTransform& cameraTransform, Film film, Medium medium, const ParameterDictionary& parameters, const FileLoc* loc );
    };

    // CameraBase Definition
    class CameraBase
    {
    protected:
        // CameraBase Protected Members
        CameraTransform cameraTransform;
        Float shutterOpen;
        Float shutterClose;
        Film film;
        Medium medium;
        Vector3f minPosDifferentialX;
        Vector3f minPosDifferentialY;
        Vector3f minDirDifferentialX;
        Vector3f minDirDifferentialY;
    public:
        // CameraBase Public Methods
        PBRT_CPU_GPU
            Film GetFilm( ) const
        {
            return film;
        }
        PBRT_CPU_GPU
            const CameraTransform& GetCameraTransform( ) const { return cameraTransform; }

        PBRT_CPU_GPU
            Float SampleTime( Float u ) const
        {
            return Lerp( u, shutterOpen, shutterClose );
        }

        void InitMetadata( ImageMetadata* metadata ) const;
        std::string ToString( ) const;

        PBRT_CPU_GPU
            void Approximate_dp_dxy( Point3f p, Normal3f n, Float time, int samplesPerPixel, Vector3f* dpdx, Vector3f* dpdy ) const
        {
            // Compute tangent plane equation for ray differential intersections
            Point3f pCamera = CameraFromRender( p, time );
            Transform DownZFromCamera = RotateFromTo( Normalize( Vector3f( pCamera ) ), Vector3f( 0, 0, 1 ) );
            Point3f pDownZ = DownZFromCamera( pCamera );
            Normal3f nDownZ = DownZFromCamera( CameraFromRender( n, time ) );
            Float d = nDownZ.z * pDownZ.z;

            // Find intersection points for approximated camera differential rays
            Ray xRay( Point3f( 0, 0, 0 ) + minPosDifferentialX, Vector3f( 0, 0, 1 ) + minDirDifferentialX );
            Float tx = -( ScalarDot( nDownZ, Vector3f( xRay.o ) ) - d ) / ScalarDot( nDownZ, xRay.d );
            Ray yRay( Point3f( 0, 0, 0 ) + minPosDifferentialY, Vector3f( 0, 0, 1 ) + minDirDifferentialY );
            Float ty = -( ScalarDot( nDownZ, Vector3f( yRay.o ) ) - d ) / ScalarDot( nDownZ, yRay.d );
            Point3f px = xRay( tx ), py = yRay( ty );

            // Estimate $\dpdx$ and $\dpdy$ in tangent plane at intersection point
            Float sppScale =
                GetOptions( ).disablePixelJitter
                ? 1
                : std::max<Float>( .125, 1 / Math::Sqrt( ( Float )samplesPerPixel ) );


            Point3f pxAdjusted = px - pDownZ;
            Point3f pyAdjusted = py - pDownZ;

            *dpdx = sppScale * RenderFromCamera( ToPoint3f( DownZFromCamera.ApplyInverse( pxAdjusted ) ), time );
            *dpdy = sppScale * RenderFromCamera( ToPoint3f( DownZFromCamera.ApplyInverse( pyAdjusted ) ), time );

        }

    protected:


        // CameraBase Protected Methods
        CameraBase( ) = default;
        CameraBase( CameraBaseParameters p );

        PBRT_CPU_GPU
            static pstdo::optional<CameraRayDifferential> GenerateRayDifferential( Camera camera, CameraSample sample, SampledWavelengths& lambda );

        PBRT_CPU_GPU
            Ray RenderFromCamera( const Ray& r ) const
        {
            return cameraTransform.RenderFromCamera( r );
        }

        PBRT_CPU_GPU
            RayDifferential RenderFromCamera( const RayDifferential& r ) const
        {
            return cameraTransform.RenderFromCamera( r );
        }

        PBRT_CPU_GPU
            Vector3f RenderFromCamera( Vector3f v, Float time ) const
        {
            return cameraTransform.RenderFromCamera( v, time );
        }

        PBRT_CPU_GPU
            Normal3f RenderFromCamera( Normal3f v, Float time ) const
        {
            return cameraTransform.RenderFromCamera( v, time );
        }

        PBRT_CPU_GPU
            Point3f RenderFromCamera( Point3f p, Float time ) const
        {
            return cameraTransform.RenderFromCamera( p, time );
        }

        PBRT_CPU_GPU
            Vector3f CameraFromRender( Vector3f v, Float time ) const
        {
            return cameraTransform.CameraFromRender( v, time );
        }

        PBRT_CPU_GPU
            Normal3f CameraFromRender( Normal3f v, Float time ) const
        {
            return cameraTransform.CameraFromRender( v, time );
        }

        PBRT_CPU_GPU
            Point3f CameraFromRender( Point3f p, Float time ) const
        {
            return cameraTransform.CameraFromRender( p, time );
        }

        void FindMinimumDifferentials( Camera camera );
    };

    // ProjectiveCamera Definition
    class ProjectiveCamera : public CameraBase
    {
    protected:
        // ProjectiveCamera Protected Members
        Transform screenFromCamera;
        Transform cameraFromRaster;
        Transform rasterFromScreen;
        Transform screenFromRaster;
        Float lensRadius;
        Float  focalDistance;
    public:
        // ProjectiveCamera Public Methods
        ProjectiveCamera( ) = default;
        void InitMetadata( ImageMetadata* metadata ) const;

        std::string BaseToString( ) const;

        ProjectiveCamera( CameraBaseParameters baseParameters, const Transform& screenFromCamera, Bounds2f screenWindow, Float lensRadius, Float focalDistance )
            : CameraBase( baseParameters ), screenFromCamera( screenFromCamera ), lensRadius( lensRadius ), focalDistance( focalDistance )
        {
            // Compute projective camera transformations
            // Compute projective camera screen transformations
            Transform NDCFromScreen = Scale( 1 / ( screenWindow.pMax.x - screenWindow.pMin.x ), 1 / ( screenWindow.pMax.y - screenWindow.pMin.y ), 1 ) *
                Translate( Vector3f( -screenWindow.pMin.x, -screenWindow.pMax.y, 0 ) );

            Transform rasterFromNDC = Scale( film.FullResolution( ).x, -film.FullResolution( ).y, 1 );

            rasterFromScreen = rasterFromNDC * NDCFromScreen;
            screenFromRaster = Inverse( rasterFromScreen );
            cameraFromRaster = Inverse( screenFromCamera ) * screenFromRaster;
        }


    };

    // OrthographicCamera Definition
    class OrthographicCamera : public ProjectiveCamera
    {
        // OrthographicCamera Private Members
        Vector3f dxCamera;
        Vector3f dyCamera;
    public:
        // OrthographicCamera Public Methods
        OrthographicCamera( CameraBaseParameters baseParameters, Bounds2f screenWindow, Float lensRadius, Float focalDist )
            : ProjectiveCamera( baseParameters, Orthographic( 0, 1 ), screenWindow, lensRadius, focalDist )
        {
            // Compute differential changes in origin for orthographic camera rays
            dxCamera = cameraFromRaster( Vector3f( 1, 0, 0 ) );
            dyCamera = cameraFromRaster( Vector3f( 0, 1, 0 ) );

            // Compute minimum differentials for orthographic camera
            minDirDifferentialX = minDirDifferentialY = Vector3f( 0, 0, 0 );
            minPosDifferentialX = dxCamera;
            minPosDifferentialY = dyCamera;
        }

        PBRT_CPU_GPU
            pstdo::optional<CameraRay> GenerateRay( CameraSample sample, SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU
            pstdo::optional<CameraRayDifferential> GenerateRayDifferential( CameraSample sample, SampledWavelengths& lambda ) const;

        static OrthographicCamera* Create( const ParameterDictionary& parameters, const CameraTransform& cameraTransform, Film film, Medium medium, const FileLoc* loc, Allocator alloc = {} );

        SampledSpectrum We( const Ray& ray, SampledWavelengths& lambda, Point2f* pRaster2 = nullptr ) const
        {
            NLOG_FATAL( "We() unimplemented for OrthographicCamera" );
            return {};
        }

        void PDF_We( const Ray& ray, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "PDF_We() unimplemented for OrthographicCamera" );
        }

        pstdo::optional<CameraWiSample> SampleWi( const Interaction& ref, Point2f u, SampledWavelengths& lambda ) const
        {
            NLOG_FATAL( "SampleWi() unimplemented for OrthographicCamera" );
            return {};
        }
        std::string ToString( ) const;
    };

    // PerspectiveCamera Definition
    class PerspectiveCamera : public ProjectiveCamera
    {
        // PerspectiveCamera Private Members
        Vector3f dxCamera;
        Vector3f dyCamera;
        Float cosTotalWidth;
        Float A;
    public:
        // PerspectiveCamera Public Methods
        PerspectiveCamera( CameraBaseParameters baseParameters, Float fov, Bounds2f screenWindow, Float lensRadius, Float focalDist )
            : ProjectiveCamera( baseParameters, Perspective( fov, 1e-2f, 1000.f ), screenWindow, lensRadius, focalDist )
        {
            // Compute differential changes in origin for perspective camera rays
            dxCamera = cameraFromRaster( Point3f( 1, 0, 0 ) ) - cameraFromRaster( Point3f( 0, 0, 0 ) );
            dyCamera = cameraFromRaster( Point3f( 0, 1, 0 ) ) - cameraFromRaster( Point3f( 0, 0, 0 ) );

            // Compute _cosTotalWidth_ for perspective camera
            Point2f radius = Point2f( film.GetFilter( ).Radius( ) );
            Point3f pCorner( -radius.x, -radius.y, 0.f );
            Vector3f wCornerCamera = Normalize( Vector3f( cameraFromRaster( pCorner ) ) );
            cosTotalWidth = wCornerCamera.z;

            NDCHECK_LT( .9999 * cosTotalWidth, Math::Cos( Deg2Rad( fov / 2 ) ) );


            // Compute image plane area at $z=1$ for _PerspectiveCamera_
            Point2i res = film.FullResolution( );
            Point3f pMin = cameraFromRaster( Point3f( 0, 0, 0 ) );
            Point3f pMax = cameraFromRaster( Point3f( res.x, res.y, 0 ) );
            pMin /= pMin.z;
            pMax /= pMax.z;
            A = std::abs( ( pMax.x - pMin.x ) * ( pMax.y - pMin.y ) );

            // Compute minimum differentials for _PerspectiveCamera_
            FindMinimumDifferentials( this );
        }

        PerspectiveCamera( ) = default;

        static PerspectiveCamera* Create( const ParameterDictionary& parameters, const CameraTransform& cameraTransform, Film film, Medium medium, const FileLoc* loc, Allocator alloc = {} );

        PBRT_CPU_GPU
            pstdo::optional<CameraRay> GenerateRay( CameraSample sample, SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU
            pstdo::optional<CameraRayDifferential> GenerateRayDifferential( CameraSample sample, SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU
            SampledSpectrum We( const Ray& ray, SampledWavelengths& lambda, Point2f* pRaster2 = nullptr ) const;

        PBRT_CPU_GPU
            void PDF_We( const Ray& ray, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            pstdo::optional<CameraWiSample> SampleWi( const Interaction& ref, Point2f u, SampledWavelengths& lambda ) const;

        std::string ToString( ) const;
    };

    // SphericalCamera Definition
    class SphericalCamera : public CameraBase
    {
    public:
        // SphericalCamera::Mapping Definition
        enum Mapping { EquiRectangular, EqualArea };
    private:
        // SphericalCamera Private Members
        Mapping mapping;
    public:
        // SphericalCamera Public Methods
        SphericalCamera( CameraBaseParameters baseParameters, Mapping mapping )
            : CameraBase( baseParameters ), mapping( mapping )
        {
            // Compute minimum differentials for _SphericalCamera_
            FindMinimumDifferentials( this );
        }

        static SphericalCamera* Create( const ParameterDictionary& parameters, const CameraTransform& cameraTransform, Film film, Medium medium, const FileLoc* loc, Allocator alloc = {} );

        PBRT_CPU_GPU
            pstdo::optional<CameraRay> GenerateRay( CameraSample sample, SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU
            pstdo::optional<CameraRayDifferential> GenerateRayDifferential( CameraSample sample, SampledWavelengths& lambda ) const
        {
            return CameraBase::GenerateRayDifferential( this, sample, lambda );
        }

        PBRT_CPU_GPU
            SampledSpectrum We( const Ray& ray, SampledWavelengths& lambda, Point2f* pRaster2 = nullptr ) const
        {
            NLOG_FATAL( "We() unimplemented for SphericalCamera" );
            return {};
        }

        PBRT_CPU_GPU
            void PDF_We( const Ray& ray, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "PDF_We() unimplemented for SphericalCamera" );
        }

        PBRT_CPU_GPU
            pstdo::optional<CameraWiSample> SampleWi( const Interaction& ref, Point2f u, SampledWavelengths& lambda ) const
        {
            NLOG_FATAL( "SampleWi() unimplemented for SphericalCamera" );
            return {};
        }

        std::string ToString( ) const;
    };

    // ExitPupilSample Definition
    struct ExitPupilSample
    {
        Point3f pPupil;
        Float pdf;
    };

    // RealisticCamera Definition
    class RealisticCamera : public CameraBase
    {
        // RealisticCamera Private Declarations
        struct LensElementInterface
        {
            Float curvatureRadius;
            Float thickness;
            Float eta;
            Float apertureRadius;
            std::string ToString( ) const;
        };

        // RealisticCamera Private Members
        Bounds2f physicalExtent;
        pstdo::vector<LensElementInterface> elementInterfaces;
        Image apertureImage;
        pstdo::vector<Bounds2f> exitPupilBounds;
    public:
        // RealisticCamera Public Methods
        RealisticCamera( CameraBaseParameters baseParameters, std::vector<Float>& lensParameters, Float focusDistance, Float apertureDiameter, Image apertureImage, Allocator alloc );

        static RealisticCamera* Create( const ParameterDictionary& parameters, const CameraTransform& cameraTransform, Film film, Medium medium, const FileLoc* loc, Allocator alloc = {} );

        PBRT_CPU_GPU
            pstdo::optional<CameraRay> GenerateRay( CameraSample sample, SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU
            pstdo::optional<CameraRayDifferential> GenerateRayDifferential( CameraSample sample, SampledWavelengths& lambda ) const
        {
            return CameraBase::GenerateRayDifferential( this, sample, lambda );
        }

        PBRT_CPU_GPU
            SampledSpectrum We( const Ray& ray, SampledWavelengths& lambda, Point2f* pRaster2 = nullptr ) const
        {
            NLOG_FATAL( "We() unimplemented for RealisticCamera" );
            return {};
        }

        PBRT_CPU_GPU
            void PDF_We( const Ray& ray, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "PDF_We() unimplemented for RealisticCamera" );
        }

        PBRT_CPU_GPU
            pstdo::optional<CameraWiSample> SampleWi( const Interaction& ref, Point2f u, SampledWavelengths& lambda ) const
        {
            NLOG_FATAL( "SampleWi() unimplemented for RealisticCamera" );
            return {};
        }

        std::string ToString( ) const;

    private:
        // RealisticCamera Private Methods
        PBRT_CPU_GPU
            Float LensRearZ( ) const
        {
            return elementInterfaces.back( ).thickness;
        }

        PBRT_CPU_GPU
            Float LensFrontZ( ) const
        {
            Float zSum = 0;
            for ( const LensElementInterface& element : elementInterfaces )
            {
                zSum += element.thickness;
            }
            return zSum;
        }

        PBRT_CPU_GPU
            Float RearElementRadius( ) const
        {
            return elementInterfaces.back( ).apertureRadius;
        }

        PBRT_CPU_GPU
            Float TraceLensesFromFilm( const Ray& rCamera, Ray* rOut ) const;

        PBRT_CPU_GPU
            static bool IntersectSphericalElement( Float radius, Float zCenter, const Ray& ray, Float* t, Normal3f* n )
        {
            // Compute _t0_ and _t1_ for ray--element intersection
            Point3f o = ray.o - Vector3f( 0, 0, zCenter );
            Float A = ray.d.x * ray.d.x + ray.d.y * ray.d.y + ray.d.z * ray.d.z;
            Float B = 2 * ( ray.d.x * o.x + ray.d.y * o.y + ray.d.z * o.z );
            Float C = o.x * o.x + o.y * o.y + o.z * o.z - radius * radius;
            Float t0, t1;
            if ( !Quadratic( A, B, C, &t0, &t1 ) )
            {
                return false;
            }
            // Select intersection $t$ based on ray direction and element curvature
            bool useCloserT = ( ray.d.z > 0 ) ^ ( radius < 0 );
            *t = useCloserT ? std::min( t0, t1 ) : std::max( t0, t1 );
            if ( *t < 0 )
            {
                return false;
            }
            // Compute surface normal of element at ray intersection point
            *n = Normal3f( Vector3f( o + *t * ray.d ) );

            * n = FaceForward( Normal3f( Normalize( *n ) ), Vector3f( -ray.d ) );


            return true;
        }

        PBRT_CPU_GPU
            Float TraceLensesFromScene( const Ray& rCamera, Ray* rOut ) const;

        void DrawLensSystem( ) const;
        void DrawRayPathFromFilm( const Ray& r, bool arrow, bool toOpticalIntercept ) const;
        void DrawRayPathFromScene( const Ray& r, bool arrow, bool toOpticalIntercept ) const;

        static void ComputeCardinalPoints( Ray rIn, Ray rOut, Float* p, Float* f );
        void ComputeThickLensApproximation( Float pz[ 2 ], Float f[ 2 ] ) const;
        Float FocusThickLens( Float focusDistance );
        Bounds2f BoundExitPupil( Float filmX0, Float filmX1 ) const;
        void RenderExitPupil( Float sx, Float sy, const char* filename ) const;

        PBRT_CPU_GPU
            pstdo::optional<ExitPupilSample> SampleExitPupil( Point2f pFilm, Point2f uLens ) const;

        void TestExitPupilBounds( ) const;


    };

    PBRT_CPU_GPU
        inline pstdo::optional<CameraRay> Camera::GenerateRay( CameraSample sample, SampledWavelengths& lambda ) const
    {
        auto generate = [ & ]( auto ptr )
            {
                return ptr->GenerateRay( sample, lambda );
            };
        return Dispatch( generate );
    }

    PBRT_CPU_GPU
        inline Film Camera::GetFilm( ) const
    {
        auto getfilm = [ & ]( auto ptr ) { return ptr->GetFilm( ); };
        return Dispatch( getfilm );
    }

    PBRT_CPU_GPU inline Float Camera::SampleTime( Float u ) const
    {
        auto sample = [ & ]( auto ptr ) { return ptr->SampleTime( u ); };
        return Dispatch( sample );
    }

    PBRT_CPU_GPU inline const CameraTransform& Camera::GetCameraTransform( ) const
    {
        auto gtc = [ & ]( auto ptr ) -> const CameraTransform& {
            return ptr->GetCameraTransform( );
            };
        return Dispatch( gtc );
    }

    PBRT_CPU_GPU inline void Camera::Approximate_dp_dxy( Point3f p, Normal3f n, Float time, int samplesPerPixel, Vector3f* dpdx, Vector3f* dpdy ) const
    {
        if constexpr ( AllInheritFrom<CameraBase>( Camera::Types( ) ) )
        {
            return ( ( const CameraBase* )ptr( ) )->Approximate_dp_dxy( p, n, time, samplesPerPixel, dpdx, dpdy );
        }
        else
        {
            auto approx = [ & ]( auto ptr )
                {
                    return ptr->Approximate_dp_dxy( p, n, time, samplesPerPixel, dpdx, dpdy );
                };
            return Dispatch( approx );
        }
    }

}

#endif
