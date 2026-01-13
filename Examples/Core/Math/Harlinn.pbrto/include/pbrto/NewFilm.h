#pragma once
#ifndef PBRTO_NEWFILM_H_
#define PBRTO_NEWFILM_H_

/*
   Copyright 2024-2026 Espen Harlinn

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

#include <pbrto/base/NewBxdf.h>
#include <pbrto/base/NewCamera.h>
#include <pbrto/base/NewFilm.h>
#include <pbrto/NewBsdf.h>
#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewColorspace.h>
#include <pbrto/util/NewParallel.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewSpectrum.h>
#include <pbrto/util/NewTransform.h>
#include <pbrto/util/NewVecMath.h>

#include <atomic>
#include <map>
#include <string>
#include <thread>
#include <vector>

namespace pbrto
{

    // PixelSensor Definition
    class PixelSensor
    {
        // PixelSensor Private Members
        DenselySampledSpectrum r_bar, g_bar, b_bar;
        Float imagingRatio;
        static constexpr int nSwatchReflectances = 24;
        static Spectrum swatchReflectances[ nSwatchReflectances ];
    public:
        // PixelSensor Public Methods
        static PixelSensor* Create( const ParameterDictionary& parameters,
            const RGBColorSpace* colorSpace, Float exposureTime,
            const FileLoc* loc, Allocator alloc );

        static PixelSensor* CreateDefault( Allocator alloc = {} );

        PixelSensor( Spectrum r, Spectrum g, Spectrum b, const RGBColorSpace* outputColorSpace, Spectrum sensorIllum, Float imagingRatio, Allocator alloc )
            : r_bar( r, alloc ), g_bar( g, alloc ), b_bar( b, alloc ), imagingRatio( imagingRatio )
        {
            // Compute XYZ from camera RGB matrix
            // Compute _rgbCamera_ values for training swatches
            Float rgbCamera[ nSwatchReflectances ][ 3 ];
            for ( int i = 0; i < nSwatchReflectances; ++i )
            {
                RGB rgb = ProjectReflectance<RGB>( swatchReflectances[ i ], sensorIllum, &r_bar, &g_bar, &b_bar );
                for ( int c = 0; c < 3; ++c )
                    rgbCamera[ i ][ c ] = rgb[ c ];
            }

            // Compute _xyzOutput_ values for training swatches
            Float xyzOutput[ 24 ][ 3 ];
            Float sensorWhiteG = InnerProduct( sensorIllum, &g_bar );
            Float sensorWhiteY = InnerProduct( sensorIllum, &Spectra::Y( ) );
            for ( size_t i = 0; i < nSwatchReflectances; ++i )
            {
                Spectrum s = swatchReflectances[ i ];
                XYZ xyz =
                    ProjectReflectance<XYZ>( s, &outputColorSpace->illuminant, &Spectra::X( ), &Spectra::Y( ), &Spectra::Z( ) ) *
                    ( sensorWhiteY / sensorWhiteG );
                for ( int c = 0; c < 3; ++c )
                    xyzOutput[ i ][ c ] = xyz[ c ];
            }

            // Initialize _XYZFromSensorRGB_ using linear least squares
            pstdo::optional<SquareMatrix<3>> m =
                LinearLeastSquares( rgbCamera, xyzOutput, nSwatchReflectances );
            if ( !m )
                ErrorExit( "Sensor XYZ from RGB matrix could not be solved." );
            XYZFromSensorRGB = *m;
        }

        PixelSensor( const RGBColorSpace* outputColorSpace, Spectrum sensorIllum,
            Float imagingRatio, Allocator alloc )
            : r_bar( &Spectra::X( ), alloc ),
            g_bar( &Spectra::Y( ), alloc ),
            b_bar( &Spectra::Z( ), alloc ),
            imagingRatio( imagingRatio )
        {
            // Compute white balancing matrix for XYZ _PixelSensor_
            if ( sensorIllum )
            {
                Point2f sourceWhite = SpectrumToXYZ( sensorIllum ).xy( );
                Point2f targetWhite = outputColorSpace->w;
                XYZFromSensorRGB = WhiteBalance( sourceWhite, targetWhite );
            }
        }

        RGB ToSensorRGB( const SampledSpectrum& LIn, const SampledWavelengths& lambda ) const
        {
            auto L = SafeDiv( LIn, lambda.PDF( ) );
            return imagingRatio * RGB( ScalarAvg( r_bar.Sample( lambda ) * L ),
                ScalarAvg( g_bar.Sample( lambda ) * L ),
                ScalarAvg( b_bar.Sample( lambda ) * L ) );
        }

        // PixelSensor Public Members
        SquareMatrix<3> XYZFromSensorRGB;

    private:
        // PixelSensor Private Methods
        template <typename Triplet>
        static Triplet ProjectReflectance( Spectrum r, Spectrum illum, Spectrum b1,
            Spectrum b2, Spectrum b3 );

        
    };

    // PixelSensor Inline Methods
    template <typename Triplet>
    inline Triplet PixelSensor::ProjectReflectance( Spectrum refl, Spectrum illum, Spectrum b1, Spectrum b2, Spectrum b3 )
    {
        Triplet result;
        Float g_integral = 0;
        for ( Float lambda = Lambda_min; lambda <= Lambda_max; ++lambda )
        {
            g_integral += b2( lambda ) * illum( lambda );
            result[ 0 ] += b1( lambda ) * refl( lambda ) * illum( lambda );
            result[ 1 ] += b2( lambda ) * refl( lambda ) * illum( lambda );
            result[ 2 ] += b3( lambda ) * refl( lambda ) * illum( lambda );
        }
        return result / g_integral;
    }

    // VisibleSurface Definition
    class VisibleSurface
    {
    public:
        // VisibleSurface Public Members
        Point3f::Simd p;
        Normal3f::Simd n, ns;
        Vector3f::Simd dpdx, dpdy;
        SampledSpectrum albedo;
        Point2f uv;
        Float time = 0;
        bool set = false;

        // VisibleSurface Public Methods
        VisibleSurface( const SurfaceInteraction& si, const SampledSpectrum& albedo, const SampledWavelengths& lambda );

        operator bool( ) const { return set; }

        VisibleSurface( ) = default;

        std::string ToString( ) const;

        
    };

    // FilmBaseParameters Definition
    struct FilmBaseParameters
    {
        Point2i fullResolution;
        Bounds2i pixelBounds;
        Filter filter;
        Float diagonal;
        const PixelSensor* sensor;
        std::string filename;

        FilmBaseParameters( const ParameterDictionary& parameters, Filter filter, const PixelSensor* sensor, const FileLoc* loc );
        FilmBaseParameters( Point2i fullResolution, Bounds2i pixelBounds, Filter filter, Float diagonal, const PixelSensor* sensor, std::string filename )
            : fullResolution( fullResolution ),
              pixelBounds( pixelBounds ),
              filter( filter ),
              diagonal( diagonal ),
              sensor( sensor ),
              filename( filename )
        {
        }

        
    };

    // FilmBase Definition
    class FilmBase
    {
    protected:
        // FilmBase Protected Members
        Point2i fullResolution;
        Bounds2i pixelBounds;
        Filter filter;
        Float diagonal;
        const PixelSensor* sensor;
        std::string filename;
    public:
        // FilmBase Public Methods
        FilmBase( FilmBaseParameters p )
            : fullResolution( p.fullResolution ),
              pixelBounds( p.pixelBounds ),
              filter( p.filter ),
              diagonal( p.diagonal * .001f ),
              sensor( p.sensor ),
              filename( p.filename )
        {
            NCHECK( !pixelBounds.IsEmpty( ) );
            NCHECK_GE( pixelBounds.pMin.x, 0 );
            NCHECK_LE( pixelBounds.pMax.x, fullResolution.x );
            NCHECK_GE( pixelBounds.pMin.y, 0 );
            NCHECK_LE( pixelBounds.pMax.y, fullResolution.y );
            NLOG_VERBOSE( "Created film with full resolution %s, pixelBounds %s",
                fullResolution, pixelBounds );
        }

        Point2i FullResolution( ) const { return fullResolution; }
        Bounds2i PixelBounds( ) const { return pixelBounds; }
        Float Diagonal( ) const { return diagonal; }
        Filter GetFilter( ) const { return filter; }
        const PixelSensor* GetPixelSensor( ) const { return sensor; }
        std::string GetFilename( ) const { return filename; }

        SampledWavelengths SampleWavelengths( Float u ) const
        {
            return SampledWavelengths::SampleVisible( u );
        }

        Bounds2f SampleBounds( ) const;

        std::string BaseToString( ) const;

    
    };

    // RGBFilm Definition
    class RGBFilm : public FilmBase
    {
        // RGBFilm::Pixel Definition
        struct Pixel
        {
            Pixel( ) = default;
            double rgbSum[ 3 ] = { 0., 0., 0. };
            double weightSum = 0.;
            AtomicDouble rgbSplat[ 3 ];
        };

        // RGBFilm Private Members
        const RGBColorSpace* colorSpace;
        Float maxComponentValue;
        bool writeFP16;
        Float filterIntegral;
        SquareMatrix<3> outputRGBFromSensorRGB;
        Array2D<Pixel> pixels;
    public:
        // RGBFilm Public Methods
        bool UsesVisibleSurface( ) const { return false; }

        void AddSample( Point2i pFilm, const SampledSpectrum& L, const SampledWavelengths& lambda, const VisibleSurface*, Float weight )
        {
            // Convert sample radiance to _PixelSensor_ RGB
            RGB rgb = sensor->ToSensorRGB( L, lambda );

            // Optionally clamp sensor RGB value
            Float m = Math::Max( rgb.x, rgb.y, rgb.z );
            if ( m > maxComponentValue )
                rgb *= maxComponentValue / m;

            NDCHECK( InsideExclusive( pFilm, pixelBounds ) );
            // Update pixel values with filtered sample contribution
            Pixel& pixel = pixels[ pFilm ];
            for ( int c = 0; c < 3; ++c )
                pixel.rgbSum[ c ] += weight * rgb[ c ];
            pixel.weightSum += weight;
        }

        RGB GetPixelRGB( Point2i p, Float splatScale = 1 ) const
        {
            const Pixel& pixel = pixels[ p ];
            RGB rgb( pixel.rgbSum[ 0 ], pixel.rgbSum[ 1 ], pixel.rgbSum[ 2 ] );
            // Normalize _rgb_ with weight sum
            Float weightSum = pixel.weightSum;
            if ( weightSum != 0 )
                rgb /= weightSum;

            // Add splat value at pixel
            for ( int c = 0; c < 3; ++c )
                rgb[ c ] += splatScale * pixel.rgbSplat[ c ] / filterIntegral;

            // Convert _rgb_ to output RGB color space
            rgb = outputRGBFromSensorRGB * rgb;

            return rgb;
        }

        RGBFilm( FilmBaseParameters p, const RGBColorSpace* colorSpace,
            Float maxComponentValue = Infinity, bool writeFP16 = true,
            Allocator alloc = {} );

        static RGBFilm* Create( const ParameterDictionary& parameters, Float exposureTime,
            Filter filter, const RGBColorSpace* colorSpace,
            const FileLoc* loc, Allocator alloc );

        void AddSplat( Point2f p, const SampledSpectrum& v, const SampledWavelengths& lambda );

        void WriteImage( ImageMetadata metadata, Float splatScale = 1 );
        Image GetImage( ImageMetadata* metadata, Float splatScale = 1 );

        std::string ToString( ) const;

        RGB ToOutputRGB( const SampledSpectrum& L, const SampledWavelengths& lambda ) const
        {
            RGB sensorRGB = sensor->ToSensorRGB( L, lambda );
            return outputRGBFromSensorRGB * sensorRGB;
        }

        PBRT_CPU_GPU void ResetPixel( Point2i p ) { memset( &pixels[ p ], 0, sizeof( Pixel ) ); }

    private:
        
    };

    // GBufferFilm Definition
    class GBufferFilm : public FilmBase
    {
        // GBufferFilm::Pixel Definition
        struct Pixel
        {
            
            double rgbSum[ 3 ] = { 0., 0., 0. };
            double weightSum = 0., gBufferWeightSum = 0.;
            AtomicDouble rgbSplat[ 3 ];
            Point3f pSum;
            Float dzdxSum = 0, dzdySum = 0;
            Normal3f nSum, nsSum;
            Point2f uvSum;
            double rgbAlbedoSum[ 3 ] = { 0., 0., 0. };
            VarianceEstimator<Float> rgbVariance[ 3 ];

            Pixel( ) = default;
        };

        // GBufferFilm Private Members
        AnimatedTransform outputFromRender;
        bool applyInverse;
        Array2D<Pixel> pixels;
        const RGBColorSpace* colorSpace;
        Float maxComponentValue;
        bool writeFP16;
        Float filterIntegral;
        SquareMatrix<3> outputRGBFromSensorRGB;
    public:
        // GBufferFilm Public Methods
        GBufferFilm( FilmBaseParameters p, const AnimatedTransform& outputFromRender,
            bool applyInverse, const RGBColorSpace* colorSpace,
            Float maxComponentValue = Infinity, bool writeFP16 = true,
            Allocator alloc = {} );

        static GBufferFilm* Create( const ParameterDictionary& parameters, Float exposureTime,
            const CameraTransform& cameraTransform, Filter filter,
            const RGBColorSpace* colorSpace, const FileLoc* loc,
            Allocator alloc );

        void AddSample( Point2i pFilm, const SampledSpectrum& L, const SampledWavelengths& lambda, const VisibleSurface* visibleSurface, Float weight );

        void AddSplat( Point2f p, const SampledSpectrum& v, const SampledWavelengths& lambda );

        RGB ToOutputRGB( const SampledSpectrum& L, const SampledWavelengths& lambda ) const
        {
            RGB cameraRGB = sensor->ToSensorRGB( L, lambda );
            return outputRGBFromSensorRGB * cameraRGB;
        }

        bool UsesVisibleSurface( ) const { return true; }

        RGB GetPixelRGB( Point2i p, Float splatScale = 1 ) const
        {
            const Pixel& pixel = pixels[ p ];
            RGB rgb( pixel.rgbSum[ 0 ], pixel.rgbSum[ 1 ], pixel.rgbSum[ 2 ] );

            // Normalize pixel with weight sum
            Float weightSum = pixel.weightSum;
            if ( weightSum != 0 )
                rgb /= weightSum;

            // Add splat value at pixel
            for ( int c = 0; c < 3; ++c )
                rgb[ c ] += splatScale * pixel.rgbSplat[ c ] / filterIntegral;

            rgb = outputRGBFromSensorRGB * rgb;

            return rgb;
        }

        void WriteImage( ImageMetadata metadata, Float splatScale = 1 );
        Image GetImage( ImageMetadata* metadata, Float splatScale = 1 );

        std::string ToString( ) const;

        void ResetPixel( Point2i p ) { memset( &pixels[ p ], 0, sizeof( Pixel ) ); }

    private:
        
    };

    // SpectralFilm Definition
    class SpectralFilm : public FilmBase
    {
        // SpectralFilm::Pixel Definition
        struct Pixel
        {
            Pixel( ) = default;
            // Continue to store RGB, both to include in the final image as
            // well as for previews during rendering.
            double rgbSum[ 3 ] = { 0., 0., 0. };
            double rgbWeightSum = 0.;
            AtomicDouble rgbSplat[ 3 ];
            // The following will all have nBuckets entries.
            double* bucketSums, * weightSums;
            AtomicDouble* bucketSplats;
        };

        // SpectralFilm Private Members
        const RGBColorSpace* colorSpace;
        Float lambdaMin, lambdaMax;
        int nBuckets;
        Float maxComponentValue;
        bool writeFP16;
        Float filterIntegral;
        Array2D<Pixel> pixels;
        SquareMatrix<3> outputRGBFromSensorRGB;
    public:
        // SpectralFilm Public Methods
        bool UsesVisibleSurface( ) const { return false; }

        SampledWavelengths SampleWavelengths( Float u ) const
        {
            return SampledWavelengths::SampleUniform( u, lambdaMin, lambdaMax );
        }

        void AddSample( Point2i pFilm, const SampledSpectrum& LIn, const SampledWavelengths& lambda, const VisibleSurface*, Float weight )
        {
            auto L = LIn;
            // Start by doing more or less what RGBFilm::AddSample() does so
            // that we can maintain accurate RGB values.

            // Convert sample radiance to _PixelSensor_ RGB
            RGB rgb = sensor->ToSensorRGB( L, lambda );

            // Optionally clamp sensor RGB value
            Float m = Math::Max( rgb.x, rgb.y, rgb.z );
            if ( m > maxComponentValue )
                rgb *= maxComponentValue / m;

            NDCHECK( InsideExclusive( pFilm, pixelBounds ) );
            // Update RGB fields in Pixel structure.
            Pixel& pixel = pixels[ pFilm ];
            for ( int c = 0; c < 3; ++c )
                pixel.rgbSum[ c ] += weight * rgb[ c ];
            pixel.rgbWeightSum += weight;

            // Spectral processing starts here.
            // Optionally clamp spectral value. (TODO: for spectral should we
            // just clamp channels individually?)
            Float lm = L.MaxComponentValue( );
            if ( lm > maxComponentValue )
                L *= maxComponentValue / lm;

            // The CIE_Y_integral factor effectively cancels out the effect of
            // the conversion of light sources to use photometric units for
            // specification.  We then do *not* divide by the PDF in |lambda|
            // but take advantage of the fact that we know that it is uniform
            // in SampleWavelengths(), the fact that the buckets all have the
            // same extend, and can then just average radiance in buckets
            // below.
            L *= weight * CIE_Y_integral;

            // Accumulate contributions in spectral buckets.
            for ( int i = 0; i < NSpectrumSamples; ++i )
            {
                int b = LambdaToBucket( lambda[ i ] );
                pixel.bucketSums[ b ] += L[ i ];
                pixel.weightSums[ b ] += weight;
            }
        }

        RGB GetPixelRGB( Point2i p, Float splatScale = 1 ) const;

        SpectralFilm( FilmBaseParameters p, Float lambdaMin, Float lambdaMax, int nBuckets,
            const RGBColorSpace* colorSpace, Float maxComponentValue = Infinity,
            bool writeFP16 = true, Allocator alloc = {} );

        static SpectralFilm* Create( const ParameterDictionary& parameters, Float exposureTime,
            Filter filter, const RGBColorSpace* colorSpace,
            const FileLoc* loc, Allocator alloc );

        void AddSplat( Point2f p, const SampledSpectrum& v, const SampledWavelengths& lambda );

        void WriteImage( ImageMetadata metadata, Float splatScale = 1 );

        // Returns an image with both RGB and spectral components, following
        // the layout proposed in "An OpenEXR Layout for Sepctral Images" by
        // Fichet et al., https://jcgt.org/published/0010/03/01/.
        Image GetImage( ImageMetadata* metadata, Float splatScale = 1 );

        std::string ToString( ) const;

        RGB ToOutputRGB( const SampledSpectrum& L, const SampledWavelengths& lambda ) const
        {
            NLOG_FATAL( "ToOutputRGB() is unimplemented. But that's ok since it's only used "
                "in the SPPM integrator, which is inherently very much based on "
                "RGB output." );
            return {};
        }

        void ResetPixel( Point2i p )
        {
            Pixel& pix = pixels[ p ];
            pix.rgbSum[ 0 ] = pix.rgbSum[ 1 ] = pix.rgbSum[ 2 ] = 0.;
            pix.rgbWeightSum = 0.;
            pix.rgbSplat[ 0 ] = pix.rgbSplat[ 1 ] = pix.rgbSplat[ 2 ] = 0.;
            memset( pix.bucketSums, 0, nBuckets * sizeof( double ) );
            memset( pix.weightSums, 0, nBuckets * sizeof( double ) );
            memset( pix.bucketSplats, 0, nBuckets * sizeof( AtomicDouble ) );
        }

    private:
        int LambdaToBucket( Float lambda ) const
        {
            NDCHECK_RARE( 1e6f, lambda < lambdaMin || lambda > lambdaMax );
            int bucket = nBuckets * ( lambda - lambdaMin ) / ( lambdaMax - lambdaMin );
            return Clamp( bucket, 0, nBuckets - 1 );
        }

        
    };

    inline SampledWavelengths Film::SampleWavelengths( Float u ) const
    {
        auto sample = [ & ]( auto ptr ) { return ptr->SampleWavelengths( u ); };
        return Dispatch( sample );
    }

    inline Bounds2f Film::SampleBounds( ) const
    {
        auto sb = [ & ]( auto ptr ) { return ptr->SampleBounds( ); };
        return Dispatch( sb );
    }

    inline Bounds2i Film::PixelBounds( ) const
    {
        auto pb = [ & ]( auto ptr ) { return ptr->PixelBounds( ); };
        return Dispatch( pb );
    }

    inline Point2i Film::FullResolution( ) const
    {
        auto fr = [ & ]( auto ptr ) { return ptr->FullResolution( ); };
        return Dispatch( fr );
    }

    inline Float Film::Diagonal( ) const
    {
        auto diag = [ & ]( auto ptr ) { return ptr->Diagonal( ); };
        return Dispatch( diag );
    }

    inline Filter Film::GetFilter( ) const
    {
        auto filter = [ & ]( auto ptr ) { return ptr->GetFilter( ); };
        return Dispatch( filter );
    }

    inline bool Film::UsesVisibleSurface( ) const
    {
        auto uses = [ & ]( auto ptr ) { return ptr->UsesVisibleSurface( ); };
        return Dispatch( uses );
    }

    inline RGB Film::GetPixelRGB( Point2i p, Float splatScale ) const
    {
        auto get = [ & ]( auto ptr ) { return ptr->GetPixelRGB( p, splatScale ); };
        return Dispatch( get );
    }

    inline RGB Film::ToOutputRGB( const SampledSpectrum& L, const SampledWavelengths& lambda ) const
    {
        auto out = [ & ]( auto ptr ) { return ptr->ToOutputRGB( L, lambda ); };
        return Dispatch( out );
    }

    inline void Film::AddSample( Point2i pFilm, const SampledSpectrum& L, const SampledWavelengths& lambda, const VisibleSurface* visibleSurface, Float weight )
    {
        auto add = [ & ]( auto ptr ) {
            return ptr->AddSample( pFilm, L, lambda, visibleSurface, weight );
            };
        return Dispatch( add );
    }

    inline const PixelSensor* Film::GetPixelSensor( ) const
    {
        auto filter = [ & ]( auto ptr ) { return ptr->GetPixelSensor( ); };
        return Dispatch( filter );
    }

    inline void Film::ResetPixel( Point2i p )
    {
        auto rp = [ & ]( auto ptr ) { ptr->ResetPixel( p ); };
        return Dispatch( rp );
    }

}

#endif
