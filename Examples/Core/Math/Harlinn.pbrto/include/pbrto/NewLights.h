#pragma once
#ifndef PBRTO_NEWLIGHTS_H_
#define PBRTO_NEWLIGHTS_H_

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

// PhysLight code contributed by Anders Langlands and Luca Fascione
// Copyright (c) 2020, Weta Digital, Ltd.
// SPDX-License-Identifier: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <pbrto/base/NewLight.h>
#include <pbrto/base/NewMedium.h>
#include <pbrto/base/NewTexture.h>
#include <pbrto/NewInteraction.h>
#include <pbrto/NewShapes.h>
#include <pbrto/NewTextures.h>
#include <pbrto/util/NewImage.h>
#include <pbrto/util/NewLog.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTransform.h>
#include <pbrto/util/NewVecMath.h>

#include <functional>
#include <memory>
#include <string>

namespace pbrto
{

    PBRTO_EXPORT std::string ToString( LightType type );

    // Light Inline Functions
    PBRT_CPU_GPU inline bool IsDeltaLight( LightType type )
    {
        return ( type == LightType::DeltaPosition || type == LightType::DeltaDirection );
    }

    // LightLiSample Definition
    struct LightLiSample
    {
        Vector3f::Simd wi;
        SampledSpectrum::Simd L;
        Float pdf;
        Interaction pLight;

        // LightLiSample Public Methods
        LightLiSample( ) = default;
        LightLiSample( const SampledSpectrum& l, Vector3f wi, Float pdf, const Interaction& pLight )
            : L( l ), wi( wi ), pdf( pdf ), pLight( pLight )
        { }

        LightLiSample( const SampledSpectrum::Simd& l, Vector3f::Simd wi, Float pdf, const Interaction& pLight )
            : L( l ), wi( wi ), pdf( pdf ), pLight( pLight )
        { }

        PBRTO_EXPORT std::string ToString( ) const;

        
    };

    // LightLeSample Definition
    struct LightLeSample
    {
        // LightLeSample Public Members
        Ray ray;
        SampledSpectrum::Simd L;
        pstdo::optional<Interaction> intr;
        Float pdfPos = 0, pdfDir = 0;

        // LightLeSample Public Methods
        LightLeSample( ) = default;
        LightLeSample( SampledSpectrum l, const Ray& ray, Float pdfPos, Float pdfDir )
            : L( l ), ray( ray ), pdfPos( pdfPos ), pdfDir( pdfDir )
        { }
        LightLeSample( SampledSpectrum::Simd l, const Ray& ray, Float pdfPos, Float pdfDir )
            : L( l ), ray( ray ), pdfPos( pdfPos ), pdfDir( pdfDir )
        { }
        LightLeSample( SampledSpectrum l, const Ray& ray, const Interaction& intr, Float pdfPos, Float pdfDir )
            : L( l ), ray( ray ), intr( intr ), pdfPos( pdfPos ), pdfDir( pdfDir )
        {
            NCHECK( this->intr->n != Normal3f( 0, 0, 0 ) );
        }
        LightLeSample( const SampledSpectrum::Simd l, const Ray& ray, const Interaction& intr, Float pdfPos, Float pdfDir )
            : L( l ), ray( ray ), intr( intr ), pdfPos( pdfPos ), pdfDir( pdfDir )
        {
            NCHECK( this->intr->n != Normal3f( 0, 0, 0 ) );
        }
        PBRTO_EXPORT std::string ToString( ) const;

        Float AbsCosTheta( Vector3f w ) const 
        { 
            return intr ? ScalarAbsDot( w, intr->n ) : 1.f; 
        }
        Float AbsCosTheta( Vector3f::Simd w ) const
        {
            return intr ? ScalarAbsDot( w, intr->n ) : 1.f;
        }

        
    };

    // LightSampleContext Definition
    class LightSampleContext
    {
    public:
        // LightSampleContext Public Members
        Point3fi pi;
        Normal3f::Simd n; 
        Normal3f::Simd ns;

        // LightSampleContext Public Methods
        LightSampleContext( ) = default;
        LightSampleContext( const SurfaceInteraction& si )
            : pi( si.pi ), n( si.n ), ns( si.shading.n )
        {
        }
        LightSampleContext( const Interaction& intr ) 
            : pi( intr.pi ) 
        { }
        LightSampleContext( Point3fi pi, Normal3f n, Normal3f ns ) 
            : pi( pi ), n( n ), ns( ns ) 
        { }

        LightSampleContext( Point3fi pi, Normal3f::Simd n, Normal3f::Simd ns )
            : pi( pi ), n( n ), ns( ns )
        { }

        Point3f p( ) const 
        { 
            return Point3f( pi ); 
        }

        
    };

    // LightBounds Definition
    class LightBounds
    {
    public:
        // LightBounds Public Members
        Vector3f::Simd w;
        Bounds3f bounds;
        Float phi = 0;
        Float cosTheta_o, cosTheta_e;
        bool twoSided;

        // LightBounds Public Methods
        LightBounds( ) = default;
        LightBounds( const Bounds3f& b, Vector3f w, Float phi, Float cosTheta_o, Float cosTheta_e, bool twoSided )
            : bounds( b ),
              w( Normalize( w ) ),
              phi( phi ),
              cosTheta_o( cosTheta_o ),
              cosTheta_e( cosTheta_e ),
              twoSided( twoSided )
        { }
        LightBounds( const Bounds3f& b, Vector3f::Simd w, Float phi, Float cosTheta_o, Float cosTheta_e, bool twoSided )
            : bounds( b ),
              w( Normalize( w ) ),
              phi( phi ),
              cosTheta_o( cosTheta_o ),
              cosTheta_e( cosTheta_e ),
              twoSided( twoSided )
        { }

        Point3f Centroid( ) const 
        { 
            return ( bounds.pMin + bounds.pMax ) / 2.f; 
        }

        PBRTO_EXPORT Float Importance( Point3f p, Normal3f n ) const;

        PBRTO_EXPORT std::string ToString( ) const;

        
    };


    inline LightBounds Union( const LightBounds& a, const LightBounds& b )
    {
        // If one _LightBounds_ has zero power, return the other
        if ( a.phi == 0 )
            return b;
        if ( b.phi == 0 )
            return a;

        // Find average direction and updated angles for _LightBounds_
        DirectionCone cone = Union( DirectionCone( a.w, a.cosTheta_o ), DirectionCone( b.w, b.cosTheta_o ) );
        Float cosTheta_o = cone.cosTheta;
        Float cosTheta_e = std::min( a.cosTheta_e, b.cosTheta_e );

        // Return final _LightBounds_ union
        return LightBounds( Union( a.bounds, b.bounds ), cone.w, a.phi + b.phi, cosTheta_o, cosTheta_e, a.twoSided | b.twoSided );
    }

    // LightBase Definition
    class LightBase
    {
    protected:
        // LightBase Protected Members
        LightType type;
        Transform renderFromLight;
        MediumInterface mediumInterface;
        static InternCache<DenselySampledSpectrum>* spectrumCache;
    public:
        // LightBase Public Methods
        PBRTO_EXPORT LightBase( LightType type, const Transform& renderFromLight, const MediumInterface& mediumInterface );

        LightType Type( ) const 
        { 
            return type; 
        }

        SampledSpectrum::Simd L( Point3f::Simd p, Normal3f::Simd n, Point2f uv, Vector3f::Simd w, const SampledWavelengths& lambda ) const
        {
            return SampledSpectrum::Simd( 0.f );
        }

        SampledSpectrum::Simd Le( const Ray&, const SampledWavelengths& ) const
        {
            return SampledSpectrum::Simd( 0.f );
        }

    protected:
        // LightBase Protected Methods
        PBRTO_EXPORT static const DenselySampledSpectrum* LookupSpectrum( Spectrum s );

        PBRTO_EXPORT std::string BaseToString( ) const;
        
    };

    // PointLight Definition
    class PointLight : public LightBase
    {
    private:
        // PointLight Private Members
        const DenselySampledSpectrum* I;
        Float scale;
    public:
        // PointLight Public Methods
        PointLight( Transform renderFromLight, MediumInterface mediumInterface, Spectrum I,
            Float scale )
            : LightBase( LightType::DeltaPosition, renderFromLight, mediumInterface ),
             I( LookupSpectrum( I ) ),
             scale( scale )
        { }

        PBRTO_EXPORT static PointLight* Create( const Transform& renderFromLight, Medium medium, const ParameterDictionary& parameters, const RGBColorSpace* colorSpace, const FileLoc* loc, Allocator alloc );
        PBRTO_EXPORT SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const;
        void Preprocess( const Bounds3f& sceneBounds ) 
        { }

        PBRTO_EXPORT pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        PBRTO_EXPORT void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        PBRTO_EXPORT pstdo::optional<LightBounds> Bounds( ) const;

        PBRTO_EXPORT std::string ToString( ) const;

        pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const
        {
            Point3f::Simd p = renderFromLight( Point3f( 0, 0, 0 ) );
            Point3f::Simd ctxP = ctx.p( );
            Vector3f::Simd wi = Normalize( p - ctxP );
            SampledSpectrum::Simd Li = scale * I->Sample( lambda ) / ScalarDistanceSquared( p, ctxP );
            return LightLiSample( Li, wi, 1, Interaction( p, &mediumInterface ) );
        }

        Float PDF_Li( LightSampleContext, Vector3f::Simd, bool allowIncompletePDF ) const
        {
            return 0;
        }

    
    };

    // DistantLight Definition
    class DistantLight : public LightBase
    {
        // DistantLight Private Members
        const DenselySampledSpectrum* Lemit;
        Float scale;
        Point3f sceneCenter;
        Float sceneRadius;
    public:
        // DistantLight Public Methods
        DistantLight( const Transform& renderFromLight, Spectrum Lemit, Float scale )
            : LightBase( LightType::DeltaDirection, renderFromLight, {} ),
              Lemit( LookupSpectrum( Lemit ) ),
              scale( scale )
        {
        }

        PBRTO_EXPORT static DistantLight* Create( const Transform& renderFromLight, const ParameterDictionary& parameters, const RGBColorSpace* colorSpace, const FileLoc* loc, Allocator alloc );

        PBRTO_EXPORT SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const;

        Float PDF_Li( LightSampleContext, Vector3f::Simd, bool allowIncompletePDF ) const
        {
            return 0;
        }

        PBRTO_EXPORT pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        PBRTO_EXPORT void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const 
        { 
            return {}; 
        }

        PBRTO_EXPORT std::string ToString( ) const;

        void Preprocess( const Bounds3f& sceneBounds )
        {
            sceneBounds.BoundingSphere( &sceneCenter, &sceneRadius );
        }

        pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const
        {
            Vector3f::Simd wi = Normalize( renderFromLight( Vector3f::Simd( 0, 0, 1 ) ) );
            Point3f::Simd pOutside = ctx.p( ) + wi * ( 2 * sceneRadius );
            return LightLiSample( scale * Lemit->Sample( lambda ), wi, 1, Interaction( pOutside, nullptr ) );
        }

    private:
        
    };

    // ProjectionLight Definition
    class ProjectionLight : public LightBase
    {
        // ProjectionLight Private Members
        Image image;
        const RGBColorSpace* imageColorSpace;
        Float scale;
        Bounds2f screenBounds;
        Float hither = 1e-3f;
        Transform screenFromLight; 
        Transform lightFromScreen;
        Float A;
        PiecewiseConstant2D distrib;
    public:
        // ProjectionLight Public Methods
        PBRTO_EXPORT ProjectionLight( Transform renderFromLight, MediumInterface medium, Image image, const RGBColorSpace* colorSpace, Float scale, Float fov, Allocator alloc );

        static ProjectionLight* Create( const Transform& renderFromLight, Medium medium, const ParameterDictionary& parameters, const FileLoc* loc, Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds ) {}

        PBRTO_EXPORT pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const;
        PBRTO_EXPORT SampledSpectrum::Simd I( Vector3f::Simd w, const SampledWavelengths& lambda ) const;

        PBRTO_EXPORT SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const;

        Float PDF_Li( LightSampleContext, Vector3f::Simd, bool allowIncompletePDF ) const
        {
            return 0.f;
        }

        pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        PBRTO_EXPORT pstdo::optional<LightBounds> Bounds( ) const;

        PBRTO_EXPORT std::string ToString( ) const;
    };

    // GoniometricLight Definition
    class GoniometricLight : public LightBase
    {
        // GoniometricLight Private Members
        const DenselySampledSpectrum* Iemit;
        Float scale;
        Image image;
        PiecewiseConstant2D distrib;
    public:
        // GoniometricLight Public Methods
        PBRTO_EXPORT GoniometricLight( const Transform& renderFromLight, const MediumInterface& mediumInterface, Spectrum I, Float scale, Image image, Allocator alloc );

        PBRTO_EXPORT static GoniometricLight* Create( const Transform& renderFromLight, Medium medium, const ParameterDictionary& parameters, const RGBColorSpace* colorSpace, const FileLoc* loc, Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds ) {}

        PBRTO_EXPORT pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const;

        PBRTO_EXPORT SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const;

        Float PDF_Li( LightSampleContext, Vector3f::Simd, bool allowIncompletePDF ) const
        {
            return 0.f;
        }

        PBRTO_EXPORT pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        PBRTO_EXPORT void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        PBRTO_EXPORT pstdo::optional<LightBounds> Bounds( ) const;

        PBRTO_EXPORT std::string ToString( ) const;

        SampledSpectrum I( Vector3f::Simd w, const SampledWavelengths& lambda ) const
        {
            Point2f uv = EqualAreaSphereToSquare( w );
            return scale * Iemit->Sample( lambda ) * image.LookupNearestChannel( uv, 0 );
        }
    };

    // DiffuseAreaLight Definition
    class DiffuseAreaLight : public LightBase
    {
        // DiffuseAreaLight Private Members
        Shape shape;
        FloatTexture alpha;
        Float area;
        bool twoSided;
        const DenselySampledSpectrum* Lemit;
        Float scale;
        Image image;
        const RGBColorSpace* imageColorSpace;
    public:
        // DiffuseAreaLight Public Methods
        PBRTO_EXPORT DiffuseAreaLight( const Transform& renderFromLight, const MediumInterface& mediumInterface, Spectrum Le, Float scale, const Shape shape, FloatTexture alpha, Image image, const RGBColorSpace* imageColorSpace, bool twoSided );

        PBRTO_EXPORT static DiffuseAreaLight* Create( const Transform& renderFromLight, Medium medium, const ParameterDictionary& parameters, const RGBColorSpace* colorSpace, const FileLoc* loc, Allocator alloc, const Shape shape, FloatTexture alpha );

        void Preprocess( const Bounds3f& sceneBounds ) {}

        PBRTO_EXPORT SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const;

        PBRTO_EXPORT pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        PBRTO_EXPORT void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const;

        PBRTO_EXPORT pstdo::optional<LightBounds> Bounds( ) const;

        void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for area lights" );
        }

        PBRTO_EXPORT std::string ToString( ) const;

        SampledSpectrum::Simd L( Point3f::Simd p, Normal3f::Simd n, Point2f uv, Vector3f::Simd w, const SampledWavelengths& lambda ) const
        {
            // Check for zero emitted radiance from point on area light
            if ( !twoSided && ScalarDot( n, w ) < 0 )
                return SampledSpectrum::Simd( 0.f );
            if ( AlphaMasked( Interaction( p, uv ) ) )
                return SampledSpectrum::Simd( 0.f );

            if ( image )
            {
                // Return _DiffuseAreaLight_ emission using image
                RGB rgb;
                uv[ 1 ] = 1 - uv[ 1 ];
                for ( int c = 0; c < 3; ++c )
                    rgb[ c ] = image.BilerpChannel( uv, c );
                RGBIlluminantSpectrum spec( *imageColorSpace, ClampZero( rgb ) );
                return scale * spec.Sample( lambda );

            }
            else
                return scale * Lemit->Sample( lambda );
        }

        PBRTO_EXPORT pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const;

        PBRTO_EXPORT Float PDF_Li( LightSampleContext ctx, Vector3f::Simd wi, bool allowIncompletePDF ) const;

    private:
        

        // DiffuseAreaLight Private Methods
        bool AlphaMasked( const Interaction& intr ) const
        {
            if ( !alpha )
                return false;
#ifdef PBRT_IS_GPU_CODE
            Float a = BasicTextureEvaluator( )( alpha, intr );
#else
            Float a = UniversalTextureEvaluator( )( alpha, intr );
#endif  // PBRT_IS_GPU_CODE
            if ( a >= 1 )
                return false;
            if ( a <= 0 )
                return true;
            return HashFloat( intr.p( ) ) > a;
        }
    };

    // UniformInfiniteLight Definition
    class UniformInfiniteLight : public LightBase
    {
        // UniformInfiniteLight Private Members
        const DenselySampledSpectrum* Lemit;
        Float scale;
        Point3f sceneCenter;
        Float sceneRadius;
    public:
        // UniformInfiniteLight Public Methods
        PBRTO_EXPORT UniformInfiniteLight( const Transform& renderFromLight, Spectrum Lemit, Float scale );

        void Preprocess( const Bounds3f& sceneBounds )
        {
            sceneBounds.BoundingSphere( &sceneCenter, &sceneRadius );
        }

        PBRTO_EXPORT SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const;

        PBRTO_EXPORT SampledSpectrum::Simd Le( const Ray& ray, const SampledWavelengths& lambda ) const;
        PBRTO_EXPORT pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const;
        PBRTO_EXPORT Float PDF_Li( LightSampleContext, Vector3f::Simd, bool allowIncompletePDF ) const;

        PBRTO_EXPORT pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        PBRTO_EXPORT void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const 
        { 
            return {}; 
        }

        PBRTO_EXPORT std::string ToString( ) const;
    };

    // ImageInfiniteLight Definition
    class ImageInfiniteLight : public LightBase
    {
        // ImageInfiniteLight Private Members
        Image image;
        const RGBColorSpace* imageColorSpace;
        Float scale;
        Point3f sceneCenter;
        Float sceneRadius;
        PiecewiseConstant2D distribution;
        PiecewiseConstant2D compensatedDistribution;
    public:
        // ImageInfiniteLight Public Methods
        PBRTO_EXPORT ImageInfiniteLight( Transform renderFromLight, Image image, const RGBColorSpace* imageColorSpace, Float scale, std::string filename, Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds )
        {
            sceneBounds.BoundingSphere( &sceneCenter, &sceneRadius );
        }

        PBRTO_EXPORT SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const;

        PBRTO_EXPORT Float PDF_Li( LightSampleContext, Vector3f::Simd, bool allowIncompletePDF ) const;

        PBRTO_EXPORT pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        PBRTO_EXPORT void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        PBRTO_EXPORT std::string ToString( ) const;

        SampledSpectrum::Simd Le( const Ray& ray, const SampledWavelengths& lambda ) const
        {
            Vector3f::Simd wLight = Normalize( renderFromLight.ApplyInverse( ray.d ) );
            Point2f uv = EqualAreaSphereToSquare( wLight );
            return ImageLe( uv, lambda );
        }

        pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const
        {
            // Find $(u,v)$ sample coordinates in infinite light texture
            Float mapPDF = 0;
            Point2f uv;
            if ( allowIncompletePDF )
                uv = compensatedDistribution.Sample( u, &mapPDF );
            else
                uv = distribution.Sample( u, &mapPDF );
            if ( mapPDF == 0 )
                return {};

            // Convert infinite light sample point to direction
            Vector3f::Simd wLight = EqualAreaSquareToSphere( uv );
            Vector3f::Simd wi = renderFromLight( wLight );

            // Compute PDF for sampled infinite light direction
            Float pdf = mapPDF / ( 4 * Pi );

            // Return radiance value for infinite light direction
            return LightLiSample(
                ImageLe( uv, lambda ), wi, pdf,
                Interaction( ctx.p( ) + wi * ( 2 * sceneRadius ), &mediumInterface ) );
        }

        pstdo::optional<LightBounds> Bounds( ) const 
        { 
            return {}; 
        }

    private:
        // ImageInfiniteLight Private Methods
        SampledSpectrum::Simd ImageLe( Point2f uv, const SampledWavelengths& lambda ) const
        {
            RGB rgb;
            for ( int c = 0; c < 3; ++c )
                rgb[ c ] = image.LookupNearestChannel( uv, c, WrapMode::OctahedralSphere );
            RGBIlluminantSpectrum spec( *imageColorSpace, ClampZero( rgb ) );
            return scale * spec.Sample( lambda );
        }

        
    };

    // PortalImageInfiniteLight Definition
    class PortalImageInfiniteLight : public LightBase
    {
        // PortalImageInfiniteLight Private Members
        pstdo::array<Point3f::Simd, 4> portal;
        Point3f::Simd sceneCenter;
        Frame portalFrame;
        Image image;
        WindowedPiecewiseConstant2D distribution;
        const RGBColorSpace* imageColorSpace;
        Float scale;
        Float sceneRadius;
        std::string filename;
        
    public:
        // PortalImageInfiniteLight Public Methods
        PBRTO_EXPORT PortalImageInfiniteLight( const Transform& renderFromLight, Image image, const RGBColorSpace* imageColorSpace, Float scale, const std::string& filename, std::vector<Point3f> portal, Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds )
        {
            sceneBounds.BoundingSphere( &sceneCenter, &sceneRadius );
        }

        PBRTO_EXPORT SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const;

        PBRTO_EXPORT SampledSpectrum::Simd Le( const Ray& ray, const SampledWavelengths& lambda ) const;

        PBRTO_EXPORT pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const;

        PBRTO_EXPORT Float PDF_Li( LightSampleContext, Vector3f::Simd, bool allowIncompletePDF ) const;

        PBRTO_EXPORT pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        PBRTO_EXPORT void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const 
        { 
            return {}; 
        }

        PBRTO_EXPORT std::string ToString( ) const;

    private:
        // PortalImageInfiniteLight Private Methods
        PBRTO_EXPORT SampledSpectrum::Simd ImageLookup( Point2f uv, const SampledWavelengths& lambda ) const;

        pstdo::optional<Point2f> ImageFromRender( Vector3f wRender, Float* duv_dw = nullptr ) const
        {
            Vector3f w = portalFrame.ToLocal( wRender );
            if ( w.z <= 0 )
                return {};
            // Compute Jacobian determinant of mapping $\roman{d}(u,v)/\roman{d}\omega$ if
            // needed
            if ( duv_dw )
                *duv_dw = Sqr( Pi ) * ( 1 - Sqr( w.x ) ) * ( 1 - Sqr( w.y ) ) / w.z;

            Float alpha = Math::ATan2( w.x, w.z ), beta = Math::ATan2( w.y, w.z );
            NDCHECK( !IsNaN( alpha + beta ) );
            return Point2f( Clamp( ( alpha + Pi / 2 ) / Pi, 0, 1 ),
                Clamp( ( beta + Pi / 2 ) / Pi, 0, 1 ) );
        }

        Vector3f RenderFromImage( Point2f uv, Float* duv_dw = nullptr ) const
        {
            Float alpha = -Pi / 2 + uv[ 0 ] * Pi, beta = -Pi / 2 + uv[ 1 ] * Pi;
            Float x = Math::Tan( alpha ), y = Math::Tan( beta );
            NDCHECK( !IsInf( x ) && !IsInf( y ) );
            Vector3f w = Normalize( Vector3f( x, y, 1 ) );
            // Compute Jacobian determinant of mapping $\roman{d}(u,v)/\roman{d}\omega$ if
            // needed
            if ( duv_dw )
                *duv_dw = Sqr( Pi ) * ( 1 - Sqr( w.x ) ) * ( 1 - Sqr( w.y ) ) / w.z;

            return portalFrame.FromLocal( w );
        }

        pstdo::optional<Bounds2f> ImageBounds( Point3f p ) const
        {
            pstdo::optional<Point2f> p0 = ImageFromRender( Normalize( portal[ 0 ] - p ) );
            pstdo::optional<Point2f> p1 = ImageFromRender( Normalize( portal[ 2 ] - p ) );
            if ( !p0 || !p1 )
                return {};
            return Bounds2f( *p0, *p1 );
        }

        Float Area( ) const
        {
            return ScalarLength( portal[ 1 ] - portal[ 0 ] ) * ScalarLength( portal[ 3 ] - portal[ 0 ] );
        }

        
    };

    // SpotLight Definition
    class SpotLight : public LightBase
    {
        // SpotLight Private Members
        const DenselySampledSpectrum* Iemit;
        Float scale, cosFalloffStart, cosFalloffEnd;
    public:
        // SpotLight Public Methods
        PBRTO_EXPORT SpotLight( const Transform& renderFromLight, const MediumInterface& m, Spectrum I, Float scale, Float totalWidth, Float falloffStart );

        PBRTO_EXPORT static SpotLight* Create( const Transform& renderFromLight, Medium medium, const ParameterDictionary& parameters, const RGBColorSpace* colorSpace, const FileLoc* loc, Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds ) 
        {
        }

        SampledSpectrum::Simd I( Vector3f::Simd w, SampledWavelengths lambda ) const
        {
            return SmoothStep( CosTheta( w ), cosFalloffEnd, cosFalloffStart ) * scale * Iemit->Sample( lambda );
        }

        SampledSpectrum::Simd Phi( SampledWavelengths lambda ) const
        {
            return scale * Iemit->Sample( lambda ) * 2 * Pi * ( ( 1 - cosFalloffStart ) + ( cosFalloffStart - cosFalloffEnd ) / 2 );
        }

        Float PDF_Li( LightSampleContext, Vector3f::Simd, bool allowIncompletePDF ) const
        {
            return 0.f;
        }

        PBRTO_EXPORT pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2, SampledWavelengths& lambda, Float time ) const;
        PBRTO_EXPORT void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        void PDF_Le( const Interaction&, Vector3f::Simd w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        PBRTO_EXPORT pstdo::optional<LightBounds> Bounds( ) const;

        PBRTO_EXPORT std::string ToString( ) const;

        pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const
        {
            Point3f::Simd p = renderFromLight( Point3f::Simd( 0, 0, 0 ) );
            Point3f::Simd ctxP = ctx.p( );
            Vector3f::Simd wi = Normalize( p - ctxP );
            // Compute incident radiance _Li_ for _SpotLight_
            Vector3f::Simd wLight = Normalize( renderFromLight.ApplyInverse( -wi ) );
            SampledSpectrum::Simd Li = I( wLight, lambda ) / ScalarDistanceSquared( p, ctxP );

            if ( !Li )
                return {};
            return LightLiSample( Li, wi, 1, Interaction( p, &mediumInterface ) );
        }
    };

    inline pstdo::optional<LightLiSample> Light::SampleLi( LightSampleContext ctx, Point2f u, SampledWavelengths lambda, bool allowIncompletePDF ) const
    {
        auto sample = [ & ]( auto ptr ) 
            {
                return ptr->SampleLi( ctx, u, lambda, allowIncompletePDF );
            };
        return Dispatch( sample );
    }

    inline Float Light::PDF_Li( LightSampleContext ctx, Vector3f::Simd wi, bool allowIncompletePDF ) const
    {
        auto pdf = [ & ]( auto ptr ) 
            { 
                return ptr->PDF_Li( ctx, wi, allowIncompletePDF ); 
            };
        return Dispatch( pdf );
    }

    inline SampledSpectrum::Simd Light::L( Point3f::Simd p, Normal3f::Simd n, Point2f uv, Vector3f::Simd w, const SampledWavelengths& lambda ) const
    {
        NCHECK( Type( ) == LightType::Area );
        auto l = [ & ]( auto ptr ) 
            { 
                return ptr->L( p, n, uv, w, lambda ); 
            };
        return Dispatch( l );
    }

    inline SampledSpectrum::Simd Light::Le( const Ray& ray, const SampledWavelengths& lambda ) const
    {
        auto le = [ & ]( auto ptr ) { return ptr->Le( ray, lambda ); };
        return Dispatch( le );
    }

    inline LightType Light::Type( ) const
    {
        auto t = [ & ]( auto ptr ) { return ptr->Type( ); };
        return Dispatch( t );
    }

}

namespace std
{

    template <>
    struct hash<pbrto::Light>
    {
        PBRT_CPU_GPU
            size_t operator()( pbrto::Light light ) const noexcept
        {
            return pbrto::Hash( light.ptr( ) );
        }
    };

}

#endif
