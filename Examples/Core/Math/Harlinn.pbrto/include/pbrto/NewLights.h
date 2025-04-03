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
    std::string ToString( LightType type );
}

namespace std
{
    template<typename CharT>
    struct formatter<pbrto::LightType, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( pbrto::LightType value, FormatContext& ctx ) const
        {
            return std::format_to( ctx.out( ), "{}", pbrto::ToString( value ) );
        }
    };
}

namespace pbrto
{


    // Light Inline Functions
    PBRT_CPU_GPU inline bool IsDeltaLight( LightType type )
    {
        return ( type == LightType::DeltaPosition || type == LightType::DeltaDirection );
    }

    // LightLiSample Definition
    struct LightLiSample
    {
        SampledSpectrum L;
        Vector3f wi;
        Float pdf;
        Interaction pLight;

        // LightLiSample Public Methods
        LightLiSample( ) = default;

        PBRT_CPU_GPU
            LightLiSample( const SampledSpectrum& L, Vector3f wi, Float pdf, const Interaction& pLight )
            : L( L ), wi( wi ), pdf( pdf ), pLight( pLight )
        {
        }
        std::string ToString( ) const;


    };

    // LightLeSample Definition
    struct LightLeSample
    {
        // LightLeSample Public Members
        SampledSpectrum L;
        Ray ray;
        pstdo::optional<Interaction> intr;
        Float pdfPos = 0;
        Float pdfDir = 0;

        // LightLeSample Public Methods
        LightLeSample( ) = default;

        LightLeSample( const SampledSpectrum& L, const Ray& ray, Float pdfPos, Float pdfDir )
            : L( L ), ray( ray ), pdfPos( pdfPos ), pdfDir( pdfDir )
        {
        }

        LightLeSample( const SampledSpectrum& L, const Ray& ray, const Interaction& intr, Float pdfPos, Float pdfDir )
            : L( L ), ray( ray ), intr( intr ), pdfPos( pdfPos ), pdfDir( pdfDir )
        {
            NCHECK( this->intr->n != Normal3f( 0, 0, 0 ) );
        }
        std::string ToString( ) const;

        Float AbsCosTheta( Vector3f w ) const { return intr ? ScalarAbsDot( w, intr->n ) : 1.f; }


    };

    // LightSampleContext Definition
    class LightSampleContext
    {
    public:
        // LightSampleContext Public Methods
        LightSampleContext( ) = default;
        PBRT_CPU_GPU
            LightSampleContext( const SurfaceInteraction& si )
            : pi( si.pi ), n( si.n ), ns( si.shading.n )
        {
        }
        PBRT_CPU_GPU
            LightSampleContext( const Interaction& intr ) : pi( intr.pi ) {}
        PBRT_CPU_GPU
            LightSampleContext( Point3fi pi, Normal3f n, Normal3f ns ) : pi( pi ), n( n ), ns( ns ) {}

        PBRT_CPU_GPU
            Point3f p( ) const { return Point3f( pi ); }

        // LightSampleContext Public Members
        Point3fi pi;
        Normal3f n, ns;
    };

    // LightBounds Definition
    class LightBounds
    {
    public:
        // LightBounds Public Methods
        LightBounds( ) = default;
        LightBounds( const Bounds3f& b, Vector3f w, Float phi, Float cosTheta_o,
            Float cosTheta_e, bool twoSided );

        PBRT_CPU_GPU
            Point3f Centroid( ) const { return ( bounds.pMin + bounds.pMax ) / 2; }

        PBRT_CPU_GPU
            Float Importance( Point3f p, Normal3f n ) const;

        std::string ToString( ) const;

        // LightBounds Public Members
        Bounds3f bounds;
        Float phi = 0;
        Vector3f w;
        Float cosTheta_o, cosTheta_e;
        bool twoSided;
    };

    // LightBounds Inline Methods
    inline LightBounds::LightBounds( const Bounds3f& b, Vector3f w, Float phi,
        Float cosTheta_o, Float cosTheta_e, bool twoSided )
        : bounds( b ),
        w( Normalize( w ) ),
        phi( phi ),
        cosTheta_o( cosTheta_o ),
        cosTheta_e( cosTheta_e ),
        twoSided( twoSided )
    {
    }

    inline LightBounds Union( const LightBounds& a, const LightBounds& b )
    {
        // If one _LightBounds_ has zero power, return the other
        if ( a.phi == 0 )
            return b;
        if ( b.phi == 0 )
            return a;

        // Find average direction and updated angles for _LightBounds_
        DirectionCone cone =
            Union( DirectionCone( a.w, a.cosTheta_o ), DirectionCone( b.w, b.cosTheta_o ) );
        Float cosTheta_o = cone.cosTheta;
        Float cosTheta_e = std::min( a.cosTheta_e, b.cosTheta_e );

        // Return final _LightBounds_ union
        return LightBounds( Union( a.bounds, b.bounds ), cone.w, a.phi + b.phi, cosTheta_o,
            cosTheta_e, a.twoSided | b.twoSided );
    }

    // LightBase Definition
    class LightBase
    {
    public:
        // LightBase Public Methods
        LightBase( LightType type, const Transform& renderFromLight,
            const MediumInterface& mediumInterface );

        PBRT_CPU_GPU
            LightType Type( ) const { return type; }

        PBRT_CPU_GPU
            SampledSpectrum L( Point3f p, Normal3f n, Point2f uv, Vector3f w,
                const SampledWavelengths& lambda ) const
        {
            return SampledSpectrum( 0.f );
        }

        PBRT_CPU_GPU
            SampledSpectrum Le( const Ray&, const SampledWavelengths& ) const
        {
            return SampledSpectrum( 0.f );
        }

    protected:
        // LightBase Protected Methods
        static const DenselySampledSpectrum* LookupSpectrum( Spectrum s );

        std::string BaseToString( ) const;
        // LightBase Protected Members
        LightType type;
        Transform renderFromLight;
        MediumInterface mediumInterface;
        static InternCache<DenselySampledSpectrum>* spectrumCache;
    };

    // PointLight Definition
    class PointLight : public LightBase
    {
    public:
        // PointLight Public Methods
        PointLight( Transform renderFromLight, MediumInterface mediumInterface, Spectrum I,
            Float scale )
            : LightBase( LightType::DeltaPosition, renderFromLight, mediumInterface ),
            I( LookupSpectrum( I ) ),
            scale( scale )
        {
        }

        static PointLight* Create( const Transform& renderFromLight, Medium medium,
            const ParameterDictionary& parameters,
            const RGBColorSpace* colorSpace, const FileLoc* loc,
            Allocator alloc );
        SampledSpectrum Phi( SampledWavelengths lambda ) const;
        void Preprocess( const Bounds3f& sceneBounds ) {}

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const;

        std::string ToString( ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const
        {
            Point3f p = renderFromLight( Point3f( 0, 0, 0 ) );
            Vector3f wi = Normalize( p - ctx.p( ) );
            SampledSpectrum Li = scale * I->Sample( lambda ) / ScalarDistanceSquared( p, ctx.p( ) );

            return LightLiSample( Li, wi, 1, Interaction( p, &mediumInterface ) );
        }

        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext, Vector3f, bool allowIncompletePDF ) const
        {
            return 0;
        }

    private:
        // PointLight Private Members
        const DenselySampledSpectrum* I;
        Float scale;
    };

    // DistantLight Definition
    class DistantLight : public LightBase
    {
    public:
        // DistantLight Public Methods
        DistantLight( const Transform& renderFromLight, Spectrum Lemit, Float scale )
            : LightBase( LightType::DeltaDirection, renderFromLight, {} ),
            Lemit( LookupSpectrum( Lemit ) ),
            scale( scale )
        {
        }

        static DistantLight* Create( const Transform& renderFromLight,
            const ParameterDictionary& parameters,
            const RGBColorSpace* colorSpace, const FileLoc* loc,
            Allocator alloc );

        SampledSpectrum Phi( SampledWavelengths lambda ) const;

        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext, Vector3f, bool allowIncompletePDF ) const
        {
            return 0;
        }

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const { return {}; }

        std::string ToString( ) const;

        void Preprocess( const Bounds3f& sceneBounds )
        {
            sceneBounds.BoundingSphere( &sceneCenter, &sceneRadius );
        }

        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const
        {
            Vector3f wi = Normalize( renderFromLight( Vector3f( 0, 0, 1 ) ) );
            Point3f pOutside = ctx.p( ) + wi * ( 2 * sceneRadius );
            return LightLiSample( scale * Lemit->Sample( lambda ), wi, 1,
                Interaction( pOutside, nullptr ) );
        }

    private:
        // DistantLight Private Members
        const DenselySampledSpectrum* Lemit;
        Float scale;
        Point3f sceneCenter;
        Float sceneRadius;
    };

    // ProjectionLight Definition
    class ProjectionLight : public LightBase
    {
    public:
        // ProjectionLight Public Methods
        ProjectionLight( Transform renderFromLight, MediumInterface medium, Image image,
            const RGBColorSpace* colorSpace, Float scale, Float fov,
            Allocator alloc );

        static ProjectionLight* Create( const Transform& renderFromLight, Medium medium,
            const ParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds ) {}

        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const;
        PBRT_CPU_GPU
            SampledSpectrum I( Vector3f w, const SampledWavelengths& lambda ) const;

        SampledSpectrum Phi( SampledWavelengths lambda ) const;

        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext, Vector3f, bool allowIncompletePDF ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const;

        std::string ToString( ) const;

    private:
        // ProjectionLight Private Members
        Image image;
        const RGBColorSpace* imageColorSpace;
        Float scale;
        Bounds2f screenBounds;
        Float hither = 1e-3f;
        Transform screenFromLight, lightFromScreen;
        Float A;
        PiecewiseConstant2D distrib;
    };

    // GoniometricLight Definition
    class GoniometricLight : public LightBase
    {
    public:
        // GoniometricLight Public Methods
        GoniometricLight( const Transform& renderFromLight,
            const MediumInterface& mediumInterface, Spectrum I, Float scale,
            Image image, Allocator alloc );

        static GoniometricLight* Create( const Transform& renderFromLight, Medium medium,
            const ParameterDictionary& parameters,
            const RGBColorSpace* colorSpace, const FileLoc* loc,
            Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds ) {}

        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const;

        SampledSpectrum Phi( SampledWavelengths lambda ) const;

        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext, Vector3f, bool allowIncompletePDF ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const;

        std::string ToString( ) const;

        PBRT_CPU_GPU
            SampledSpectrum I( Vector3f w, const SampledWavelengths& lambda ) const
        {
            Point2f uv = EqualAreaSphereToSquare( w );
            return scale * Iemit->Sample( lambda ) * image.LookupNearestChannel( uv, 0 );
        }

    private:
        // GoniometricLight Private Members
        const DenselySampledSpectrum* Iemit;
        Float scale;
        Image image;
        PiecewiseConstant2D distrib;
    };

    // DiffuseAreaLight Definition
    class DiffuseAreaLight : public LightBase
    {
    public:
        // DiffuseAreaLight Public Methods
        DiffuseAreaLight( const Transform& renderFromLight,
            const MediumInterface& mediumInterface, Spectrum Le, Float scale,
            const Shape shape, FloatTexture alpha, Image image,
            const RGBColorSpace* imageColorSpace, bool twoSided );

        static DiffuseAreaLight* Create( const Transform& renderFromLight, Medium medium,
            const ParameterDictionary& parameters,
            const RGBColorSpace* colorSpace, const FileLoc* loc,
            Allocator alloc, const Shape shape,
            FloatTexture alpha );

        void Preprocess( const Bounds3f& sceneBounds ) {}

        SampledSpectrum Phi( SampledWavelengths lambda ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const;

        pstdo::optional<LightBounds> Bounds( ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for area lights" );
        }

        std::string ToString( ) const;

        PBRT_CPU_GPU
            SampledSpectrum L( Point3f p, Normal3f n, Point2f uv, Vector3f w,
                const SampledWavelengths& lambda ) const
        {
            // Check for zero emitted radiance from point on area light
            if ( !twoSided && ScalarDot( n, w ) < 0 )
                return SampledSpectrum( 0.f );
            if ( AlphaMasked( Interaction( p, uv ) ) )
                return SampledSpectrum( 0.f );

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

        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const;

        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext ctx, Vector3f wi, bool allowIncompletePDF ) const;

    private:
        // DiffuseAreaLight Private Members
        Shape shape;
        FloatTexture alpha;
        Float area;
        bool twoSided;
        const DenselySampledSpectrum* Lemit;
        Float scale;
        Image image;
        const RGBColorSpace* imageColorSpace;

        // DiffuseAreaLight Private Methods
        PBRT_CPU_GPU
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
    public:
        // UniformInfiniteLight Public Methods
        UniformInfiniteLight( const Transform& renderFromLight, Spectrum Lemit, Float scale );

        void Preprocess( const Bounds3f& sceneBounds )
        {
            sceneBounds.BoundingSphere( &sceneCenter, &sceneRadius );
        }

        SampledSpectrum Phi( SampledWavelengths lambda ) const;

        PBRT_CPU_GPU
            SampledSpectrum Le( const Ray& ray, const SampledWavelengths& lambda ) const;
        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const;
        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext, Vector3f, bool allowIncompletePDF ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const { return {}; }

        std::string ToString( ) const;

    private:
        // UniformInfiniteLight Private Members
        const DenselySampledSpectrum* Lemit;
        Float scale;
        Point3f sceneCenter;
        Float sceneRadius;
    };

    // ImageInfiniteLight Definition
    class ImageInfiniteLight : public LightBase
    {
    public:
        // ImageInfiniteLight Public Methods
        ImageInfiniteLight( Transform renderFromLight, Image image,
            const RGBColorSpace* imageColorSpace, Float scale,
            std::string filename, Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds )
        {
            sceneBounds.BoundingSphere( &sceneCenter, &sceneRadius );
        }

        SampledSpectrum Phi( SampledWavelengths lambda ) const;

        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext, Vector3f, bool allowIncompletePDF ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        std::string ToString( ) const;

        PBRT_CPU_GPU
            SampledSpectrum Le( const Ray& ray, const SampledWavelengths& lambda ) const
        {
            Vector3f wLight = Normalize( renderFromLight.ApplyInverse( ray.d ) );
            Point2f uv = EqualAreaSphereToSquare( wLight );
            return ImageLe( uv, lambda );
        }

        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const
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
            Vector3f wLight = EqualAreaSquareToSphere( uv );
            Vector3f wi = renderFromLight( wLight );

            // Compute PDF for sampled infinite light direction
            Float pdf = mapPDF / ( 4 * Pi );

            // Return radiance value for infinite light direction
            return LightLiSample(
                ImageLe( uv, lambda ), wi, pdf,
                Interaction( ctx.p( ) + wi * ( 2 * sceneRadius ), &mediumInterface ) );
        }

        pstdo::optional<LightBounds> Bounds( ) const { return {}; }

    private:
        // ImageInfiniteLight Private Methods
        PBRT_CPU_GPU
            SampledSpectrum ImageLe( Point2f uv, const SampledWavelengths& lambda ) const
        {
            RGB rgb;
            for ( int c = 0; c < 3; ++c )
                rgb[ c ] = image.LookupNearestChannel( uv, c, WrapMode::OctahedralSphere );
            RGBIlluminantSpectrum spec( *imageColorSpace, ClampZero( rgb ) );
            return scale * spec.Sample( lambda );
        }

        // ImageInfiniteLight Private Members
        Image image;
        const RGBColorSpace* imageColorSpace;
        Float scale;
        Point3f sceneCenter;
        Float sceneRadius;
        PiecewiseConstant2D distribution;
        PiecewiseConstant2D compensatedDistribution;
    };

    // PortalImageInfiniteLight Definition
    class PortalImageInfiniteLight : public LightBase
    {
    public:
        // PortalImageInfiniteLight Public Methods
        PortalImageInfiniteLight( const Transform& renderFromLight, Image image,
            const RGBColorSpace* imageColorSpace, Float scale,
            const std::string& filename, std::vector<Point3f> portal,
            Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds )
        {
            sceneBounds.BoundingSphere( &sceneCenter, &sceneRadius );
        }

        SampledSpectrum Phi( SampledWavelengths lambda ) const;

        PBRT_CPU_GPU
            SampledSpectrum Le( const Ray& ray, const SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const;

        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext, Vector3f, bool allowIncompletePDF ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const { return {}; }

        std::string ToString( ) const;

    private:
        // PortalImageInfiniteLight Private Methods
        PBRT_CPU_GPU
            SampledSpectrum ImageLookup( Point2f uv, const SampledWavelengths& lambda ) const;

        PBRT_CPU_GPU
            pstdo::optional<Point2f> ImageFromRender( Vector3f wRender,
                Float* duv_dw = nullptr ) const
        {
            Vector3f w = portalFrame.ToLocal( wRender );
            if ( w.z <= 0 )
                return {};
            // Compute Jacobian determinant of mapping $\roman{d}(u,v)/\roman{d}\omega$ if
            // needed
            if ( duv_dw )
                *duv_dw = Sqr( Pi ) * ( 1 - Sqr( w.x ) ) * ( 1 - Sqr( w.y ) ) / w.z;

            Float alpha = std::atan2( w.x, w.z ), beta = std::atan2( w.y, w.z );
            NDCHECK( !IsNaN( alpha + beta ) );
            return Point2f( Clamp( ( alpha + Pi / 2 ) / Pi, 0, 1 ),
                Clamp( ( beta + Pi / 2 ) / Pi, 0, 1 ) );
        }

        PBRT_CPU_GPU
            Vector3f RenderFromImage( Point2f uv, Float* duv_dw = nullptr ) const
        {
            Float alpha = -Pi / 2 + uv[ 0 ] * Pi, beta = -Pi / 2 + uv[ 1 ] * Pi;
            Float x = std::tan( alpha ), y = std::tan( beta );
            NDCHECK( !IsInf( x ) && !IsInf( y ) );
            Vector3f w = Normalize( Vector3f( x, y, 1 ) );
            // Compute Jacobian determinant of mapping $\roman{d}(u,v)/\roman{d}\omega$ if
            // needed
            if ( duv_dw )
                *duv_dw = Sqr( Pi ) * ( 1 - Sqr( w.x ) ) * ( 1 - Sqr( w.y ) ) / w.z;

            return portalFrame.FromLocal( w );
        }

        PBRT_CPU_GPU
            pstdo::optional<Bounds2f> ImageBounds( Point3f p ) const
        {
            pstdo::optional<Point2f> p0 = ImageFromRender( Normalize( portal[ 0 ] - p ) );
            pstdo::optional<Point2f> p1 = ImageFromRender( Normalize( portal[ 2 ] - p ) );
            if ( !p0 || !p1 )
                return {};
            return Bounds2f( *p0, *p1 );
        }

        PBRT_CPU_GPU
            Float Area( ) const
        {
            return ScalarLength( portal[ 1 ] - portal[ 0 ] ) * ScalarLength( portal[ 3 ] - portal[ 0 ] );
        }

        // PortalImageInfiniteLight Private Members
        pstdo::array<Point3f, 4> portal;
        Frame portalFrame;
        Image image;
        WindowedPiecewiseConstant2D distribution;
        const RGBColorSpace* imageColorSpace;
        Float scale;
        Float sceneRadius;
        std::string filename;
        Point3f sceneCenter;
    };

    // SpotLight Definition
    class SpotLight : public LightBase
    {
    public:
        // SpotLight Public Methods
        SpotLight( const Transform& renderFromLight, const MediumInterface& m, Spectrum I,
            Float scale, Float totalWidth, Float falloffStart );

        static SpotLight* Create( const Transform& renderFromLight, Medium medium,
            const ParameterDictionary& parameters,
            const RGBColorSpace* colorSpace, const FileLoc* loc,
            Allocator alloc );

        void Preprocess( const Bounds3f& sceneBounds ) {}

        PBRT_CPU_GPU
            SampledSpectrum I( Vector3f w, SampledWavelengths ) const;

        SampledSpectrum Phi( SampledWavelengths lambda ) const;

        PBRT_CPU_GPU
            Float PDF_Li( LightSampleContext, Vector3f, bool allowIncompletePDF ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLeSample> SampleLe( Point2f u1, Point2f u2,
                SampledWavelengths& lambda, Float time ) const;
        PBRT_CPU_GPU
            void PDF_Le( const Ray&, Float* pdfPos, Float* pdfDir ) const;

        PBRT_CPU_GPU
            void PDF_Le( const Interaction&, Vector3f w, Float* pdfPos, Float* pdfDir ) const
        {
            NLOG_FATAL( "Shouldn't be called for non-area lights" );
        }

        pstdo::optional<LightBounds> Bounds( ) const;

        std::string ToString( ) const;

        PBRT_CPU_GPU
            pstdo::optional<LightLiSample> SampleLi( LightSampleContext ctx, Point2f u,
                SampledWavelengths lambda,
                bool allowIncompletePDF ) const
        {
            Point3f p = renderFromLight( Point3f( 0, 0, 0 ) );
            Vector3f wi = Normalize( p - ctx.p( ) );
            // Compute incident radiance _Li_ for _SpotLight_
            Vector3f wLight = Normalize( renderFromLight.ApplyInverse( Vector3f( -wi ) ) );

            SampledSpectrum Li = I( wLight, lambda ) / ScalarDistanceSquared( p, ctx.p( ) );


            if ( !Li )
                return {};
            return LightLiSample( Li, wi, 1, Interaction( p, &mediumInterface ) );
        }

    private:
        // SpotLight Private Members
        const DenselySampledSpectrum* Iemit;
        Float scale, cosFalloffStart, cosFalloffEnd;
    };

    PBRT_CPU_GPU inline pstdo::optional<LightLiSample> Light::SampleLi( LightSampleContext ctx, Point2f u,
        SampledWavelengths lambda,
        bool allowIncompletePDF ) const
    {
        auto sample = [ & ]( auto ptr ) {
            return ptr->SampleLi( ctx, u, lambda, allowIncompletePDF );
            };
        return Dispatch( sample );
    }

    PBRT_CPU_GPU inline Float Light::PDF_Li( LightSampleContext ctx, Vector3f wi,
        bool allowIncompletePDF ) const
    {
        auto pdf = [ & ]( auto ptr ) { return ptr->PDF_Li( ctx, wi, allowIncompletePDF ); };
        return Dispatch( pdf );
    }

    PBRT_CPU_GPU inline SampledSpectrum Light::L( Point3f p, Normal3f n, Point2f uv, Vector3f w,
        const SampledWavelengths& lambda ) const
    {
        NCHECK( Type( ) == LightType::Area );
        auto l = [ & ]( auto ptr ) { return ptr->L( p, n, uv, w, lambda ); };
        return Dispatch( l );
    }

    PBRT_CPU_GPU inline SampledSpectrum Light::Le( const Ray& ray,
        const SampledWavelengths& lambda ) const
    {
        auto le = [ & ]( auto ptr ) { return ptr->Le( ray, lambda ); };
        return Dispatch( le );
    }

    PBRT_CPU_GPU inline LightType Light::Type( ) const
    {
        auto t = [ & ]( auto ptr ) { return ptr->Type( ); };
        return Dispatch( t );
    }

}  // namespace pbrt

namespace std
{

    template <>
    struct hash<pbrto::Light>
    {
        size_t operator()( pbrto::Light light ) const noexcept
        {
            return pbrto::Hash( light.ptr( ) );
        }
    };

}

#endif
