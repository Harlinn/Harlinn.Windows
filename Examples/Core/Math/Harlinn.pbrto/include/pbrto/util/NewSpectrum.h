#pragma once
#ifndef PBRTO_UTIL_NEWSPECTRUM_H_
#define PBRTO_UTIL_NEWSPECTRUM_H_

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

#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewColor.h>
#include <pbrto/util/NewFloat.h>
#include <pbrto/util/NewHash.h>
#include <pbrto/util/NewVecMath.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/util/NewTaggedPtr.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace pbrto
{

    // Spectrum Constants
    constexpr Float Lambda_min = 360, Lambda_max = 830;

    static constexpr int NSpectrumSamples = 4;

    static constexpr Float CIE_Y_integral = 106.856895;

    // Spectrum Definition
    class BlackbodySpectrum;
    class ConstantSpectrum;
    class PiecewiseLinearSpectrum;
    class DenselySampledSpectrum;
    class RGBAlbedoSpectrum;
    class RGBUnboundedSpectrum;
    class RGBIlluminantSpectrum;

    class Spectrum : public TaggedPointer<ConstantSpectrum, DenselySampledSpectrum,
        PiecewiseLinearSpectrum, RGBAlbedoSpectrum,
        RGBUnboundedSpectrum, RGBIlluminantSpectrum,
        BlackbodySpectrum>
    {
    public:
        // Spectrum Interface
        using TaggedPointer::TaggedPointer;
        PBRTO_EXPORT std::string ToString( ) const;

        Float operator()( Float lambda ) const;

        Float MaxValue( ) const;

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const;
    };

    // Spectrum Function Declarations
    inline Float Blackbody( Float lambda, Float T )
    {
        if ( T <= 0 )
            return 0;
        const Float c = 299792458.f;
        const Float h = 6.62606957e-34f;
        const Float kb = 1.3806488e-23f;
        // Return emitted radiance for blackbody at wavelength _lambda_
        Float l = lambda * 1e-9f;
        Float Le = ( 2 * h * c * c ) / ( FastPow<5>( l ) * ( FastExp( ( h * c ) / ( l * kb * T ) ) - 1 ) );
        NCHECK( !IsNaN( Le ) );
        return Le;
    }

    namespace Spectra
    {
        PBRTO_EXPORT DenselySampledSpectrum D( Float T, Allocator alloc );
    }  // namespace Spectra

    PBRTO_EXPORT Float SpectrumToPhotometric( Spectrum s );

    PBRTO_EXPORT XYZ SpectrumToXYZ( Spectrum s );

    // SampledSpectrum Definition
    class SampledSpectrum : public Math::Tuple4<SampledSpectrum, Float>
    {
    public:
        using Base = Math::Tuple4<SampledSpectrum, Float>;
    private:
        friend struct SOA<SampledSpectrum>;
    public:
        // SampledSpectrum Public Methods

        using Traits = Base::Traits;
        using value_type = Base::value_type;

        SampledSpectrum( ) noexcept = default;
        explicit SampledSpectrum( float v ) noexcept
            : Base( v, v, v, v )
        {
        }
        SampledSpectrum( float v1, float v2, float v3, float v4 ) noexcept
            : Base( v1, v2, v3, v4 )
        { }

        SampledSpectrum( const ArrayType& values ) noexcept
            : Base( values )
        { }

        SampledSpectrum( const float( &v )[ NSpectrumSamples ] )
            : Base( v[ 0 ],v[ 1 ],v[ 2 ],v[ 3 ] )
        { }

        template<Math::Internal::TupleType T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        SampledSpectrum( const T& other ) noexcept
            : Base( other.x, other.y, other.z, other.w )
        { }

        template<Math::Internal::SimdType T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        SampledSpectrum( const T& other ) noexcept
            : SampledSpectrum( Traits::ToArray( other.simd ) )
        { }


        PBRTO_EXPORT std::string ToString( ) const;

        bool HasNaNs( ) const
        {
            return Base::HasNaN( );
        }

        PBRTO_EXPORT XYZ ToXYZ( const SampledWavelengths& lambda ) const;
        PBRTO_EXPORT RGB ToRGB( const SampledWavelengths& lambda, const RGBColorSpace& cs ) const;
        PBRTO_EXPORT Float Y( const SampledWavelengths& lambda ) const;

        explicit operator bool( ) const
        {
            return Base::x != 0.f || Base::y != 0.f || Base::z != 0.f || Base::w != 0.f;
        }

        

        Float MinComponentValue( ) const
        {
            return Math::MinComponentValue( *this );
        }
        Float MaxComponentValue( ) const
        {
            return Math::MaxComponentValue( *this );
        }
        Float Average( ) const
        {
            return ScalarAvg( *this );
        }

    
    };

    // SampledWavelengths Definitions
    class SampledWavelengths
    {
    public:
        using VectorType = Math::Vector<Float, NSpectrumSamples>;
    private:
        // SampledWavelengths Private Members
        friend struct SOA<SampledWavelengths>;
        VectorType lambda; 
        VectorType pdf;
    public:
        // SampledWavelengths Public Methods
        bool operator==( const SampledWavelengths& swl ) const
        {
            return lambda == swl.lambda && pdf == swl.pdf;
        }
        bool operator!=( const SampledWavelengths& swl ) const
        {
            return lambda != swl.lambda || pdf != swl.pdf;
        }

        PBRTO_EXPORT std::string ToString( ) const;

        static SampledWavelengths SampleUniform( Float u, Float lambda_min = Lambda_min, Float lambda_max = Lambda_max )
        {
            SampledWavelengths swl;
            // Sample first wavelength using _u_
            auto first = Lerp2( u, lambda_min, lambda_max );
            swl.lambda.x = first;

            // Initialize _lambda_ for remaining wavelengths
            Float delta = ( lambda_max - lambda_min ) / NSpectrumSamples;

            for ( int i = 1; i < NSpectrumSamples; ++i )
            {
                swl.lambda[ i ] = swl.lambda[ i - 1 ] + delta;
                if ( swl.lambda[ i ] > lambda_max )
                {
                    swl.lambda[ i ] = lambda_min + ( swl.lambda[ i ] - lambda_max );
                }
            }
            
            // Compute PDF for sampled wavelengths
            swl.pdf = VectorType( 1.f / ( lambda_max - lambda_min ) );

            return swl;
        }

        Float operator[]( int i ) const 
        { 
            return lambda[ i ]; 
        }
        Float& operator[]( int i ) 
        { 
            return lambda[ i ]; 
        }
        SampledSpectrum PDF( ) const 
        { 
            return SampledSpectrum( pdf ); 
        }

        void TerminateSecondary( )
        {
            if ( SecondaryTerminated( ) )
            {
                return;
            }
            // Update wavelength probabilities for termination
            pdf.x /= NSpectrumSamples;
            pdf.y = 0.f;
            pdf.z = 0.f;
            pdf.w = 0.f;
        }

        bool SecondaryTerminated( ) const
        {
            return pdf.y != 0 || pdf.z != 0 || pdf.w != 0;
        }

        static SampledWavelengths SampleVisible( Float u )
        {
            SampledWavelengths swl;
            for ( int i = 0; i < NSpectrumSamples; ++i )
            {
                // Compute _up_ for $i$th wavelength sample
                Float up = u + Float( i ) / NSpectrumSamples;
                if ( up > 1 )
                    up -= 1;

                swl.lambda[ i ] = SampleVisibleWavelengths( up );
                swl.pdf[ i ] = VisibleWavelengthsPDF( swl.lambda[ i ] );
            }
            return swl;
        }
    };

    // Spectrum Definitions
    class ConstantSpectrum
    {
        Float c;
    public:
        ConstantSpectrum( Float c ) 
            : c( c ) 
        { }

        Float operator()( Float lambda ) const 
        { 
            return c; 
        }
        // ConstantSpectrum Public Methods
        PBRTO_EXPORT SampledSpectrum Sample( const SampledWavelengths& ) const;

        Float MaxValue( ) const 
        { 
            return c; 
        }

        PBRTO_EXPORT std::string ToString( ) const;
    };

    class DenselySampledSpectrum
    {
    private:
        friend struct std::hash<pbrto::DenselySampledSpectrum>;
        // DenselySampledSpectrum Private Members
        int lambda_min, lambda_max;
        pstdo::vector<Float> values;
    public:
        // DenselySampledSpectrum Public Methods
        DenselySampledSpectrum( int lambda_min = Lambda_min, int lambda_max = Lambda_max,
            Allocator alloc = {} )
            : lambda_min( lambda_min ),
              lambda_max( lambda_max ),
              values( lambda_max - lambda_min + 1, alloc )
        {
        }
        DenselySampledSpectrum( Spectrum s, Allocator alloc )
            : DenselySampledSpectrum( s, Lambda_min, Lambda_max, alloc )
        {
        }
        DenselySampledSpectrum( const DenselySampledSpectrum& s, Allocator alloc )
            : lambda_min( s.lambda_min ),
              lambda_max( s.lambda_max ),
              values( s.values.begin( ), s.values.end( ), alloc )
        {
        }

        DenselySampledSpectrum( Spectrum spec, int lambda_min = Lambda_min,
            int lambda_max = Lambda_max, Allocator alloc = {} )
            : lambda_min( lambda_min ),
              lambda_max( lambda_max ),
              values( lambda_max - lambda_min + 1, alloc )
        {
            NCHECK_GE( lambda_max, lambda_min );
            if ( spec )
                for ( int lambda = lambda_min; lambda <= lambda_max; ++lambda )
                    values[ lambda - lambda_min ] = spec( lambda );
        }
        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
            {
                int offset = std::lround( lambda[ i ] ) - lambda_min;
                if ( offset < 0 || offset >= values.size( ) )
                    s[ i ] = 0;
                else
                    s[ i ] = values[ offset ];
            }
            return s;
        }

        void Scale( Float s )
        {
            for ( Float& v : values )
                v *= s;
        }

        Float MaxValue( ) const 
        { 
            return *std::max_element( values.begin( ), values.end( ) ); 
        }

        PBRTO_EXPORT std::string ToString( ) const;

        

        template <typename F>
        static DenselySampledSpectrum SampleFunction( F func, int lambda_min = Lambda_min,
            int lambda_max = Lambda_max,
            Allocator alloc = {} )
        {
            DenselySampledSpectrum s( lambda_min, lambda_max, alloc );
            for ( int lambda = lambda_min; lambda <= lambda_max; ++lambda )
                s.values[ lambda - lambda_min ] = func( lambda );
            return s;
        }

        Float operator()( Float lambda ) const
        {
            NDCHECK_GT( lambda, 0 );
            int offset = std::lround( lambda ) - lambda_min;
            if ( offset < 0 || offset >= values.size( ) )
                return 0;
            return values[ offset ];
        }

        bool operator==( const DenselySampledSpectrum& d ) const
        {
            if ( lambda_min != d.lambda_min || lambda_max != d.lambda_max ||
                values.size( ) != d.values.size( ) )
                return false;
            for ( size_t i = 0; i < values.size( ); ++i )
                if ( values[ i ] != d.values[ i ] )
                    return false;
            return true;
        }

    
    };

    class PiecewiseLinearSpectrum
    {
    public:
        // PiecewiseLinearSpectrum Public Methods
        PiecewiseLinearSpectrum( ) = default;

        PBRTO_EXPORT PiecewiseLinearSpectrum( pstdo::span<const Float> lambdas, pstdo::span<const Float> values, Allocator alloc = {} );

        void Scale( Float s )
        {
            for ( Float& v : values )
                v *= s;
        }

        PBRTO_EXPORT Float MaxValue( ) const;

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                s[ i ] = ( *this )( lambda[ i ] );
            return s;
        }
        PBRTO_EXPORT Float operator()( Float lambda ) const;

        PBRTO_EXPORT std::string ToString( ) const;

        

        PBRTO_EXPORT static pstdo::optional<Spectrum> Read( const std::string& filename, Allocator alloc );

        PBRTO_EXPORT static PiecewiseLinearSpectrum* FromInterleaved( pstdo::span<const Float> samples, bool normalize, Allocator alloc );

    private:
        // PiecewiseLinearSpectrum Private Members
        pstdo::vector<Float> lambdas, values;
    };

    class BlackbodySpectrum
    {
    public:
        // BlackbodySpectrum Public Methods
        BlackbodySpectrum( Float T ) : T( T )
        {
            // Compute blackbody normalization constant for given temperature
            Float lambdaMax = 2.8977721e-3f / T;
            normalizationFactor = 1 / Blackbody( lambdaMax * 1e9f, T );
        }

        Float operator()( Float lambda ) const
        {
            return Blackbody( lambda, T ) * normalizationFactor;
        }

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                s[ i ] = Blackbody( lambda[ i ], T ) * normalizationFactor;
            return s;
        }

        Float MaxValue( ) const 
        { 
            return 1.f; 
        }

        PBRTO_EXPORT std::string ToString( ) const;

    private:
        // BlackbodySpectrum Private Members
        Float T;
        Float normalizationFactor;
    };

    class RGBAlbedoSpectrum
    {
    public:
        // RGBAlbedoSpectrum Public Methods
        PBRTO_EXPORT RGBAlbedoSpectrum( const RGBColorSpace& cs, RGB rgb );

        Float operator()( Float lambda ) const { return rsp( lambda ); }
        Float MaxValue( ) const { return rsp.MaxValue( ); }

        

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                s[ i ] = rsp( lambda[ i ] );
            return s;
        }

        PBRTO_EXPORT std::string ToString( ) const;

    private:
        // RGBAlbedoSpectrum Private Members
        RGBSigmoidPolynomial rsp;
    };

    class RGBUnboundedSpectrum
    {
    public:
        PBRTO_EXPORT RGBUnboundedSpectrum( const RGBColorSpace& cs, RGB rgb );

        RGBUnboundedSpectrum( ) 
            : rsp( 0, 0, 0 ), scale( 0 ) 
        { }

        // RGBUnboundedSpectrum Public Methods
        Float operator()( Float lambda ) const { return scale * rsp( lambda ); }
        Float MaxValue( ) const { return scale * rsp.MaxValue( ); }

        

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                s[ i ] = scale * rsp( lambda[ i ] );
            return s;
        }

        PBRTO_EXPORT std::string ToString( ) const;

    private:
        // RGBUnboundedSpectrum Private Members
        Float scale = 1;
        RGBSigmoidPolynomial rsp;
    };

    class RGBIlluminantSpectrum
    {
    public:
        // RGBIlluminantSpectrum Public Methods
        RGBIlluminantSpectrum( ) = default;
        PBRTO_EXPORT RGBIlluminantSpectrum( const RGBColorSpace& cs, RGB rgb );

        Float operator()( Float lambda ) const
        {
            if ( !illuminant )
                return 0;
            return scale * rsp( lambda ) * ( *illuminant )( lambda );
        }

        Float MaxValue( ) const
        {
            if ( !illuminant )
                return 0;
            return scale * rsp.MaxValue( ) * illuminant->MaxValue( );
        }

        const DenselySampledSpectrum* Illuminant( ) const 
        { 
            return illuminant; 
        }

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            if ( !illuminant )
                return SampledSpectrum( 0 );
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                s[ i ] = scale * rsp( lambda[ i ] );
            return s * illuminant->Sample( lambda );
        }

        PBRTO_EXPORT std::string ToString( ) const;

    private:
        // RGBIlluminantSpectrum Private Members
        Float scale;
        RGBSigmoidPolynomial rsp;
        const DenselySampledSpectrum* illuminant;
    };

    // SampledSpectrum Inline Functions
    inline SampledSpectrum SafeDiv( SampledSpectrum a, SampledSpectrum b )
    {
        using Traits = SampledSpectrum::Traits;
        auto result = a / b;
        auto nans = Traits::IsNaN( result.simd );
        auto zeros = Traits::Zero( );
        result.simd = Traits::Select( result.simd, zeros, nans );
        return SampledSpectrum( result );
    }


    inline SampledSpectrum Bilerp( pstdo::array<Float, 2> p, pstdo::span<const SampledSpectrum> v )
    {
        return ( 
            ( 1 - p[ 0 ] ) * 
            ( 1 - p[ 1 ] ) * v[ 0 ] + p[ 0 ] * 
            ( 1 - p[ 1 ] ) * v[ 1 ] +
            ( 1 - p[ 0 ] ) * p[ 1 ] * v[ 2 ] + p[ 0 ] * p[ 1 ] * v[ 3 ] );
    }

    // Spectral Data Declarations
    namespace Spectra
    {

        void Init( Allocator alloc );

        PBRT_CPU_GPU
            inline const DenselySampledSpectrum& X( )
        {
#ifdef PBRT_IS_GPU_CODE
            extern PBRT_GPU DenselySampledSpectrum* xGPU;
            return *xGPU;
#else
            PBRTO_EXPORT extern DenselySampledSpectrum* x;
            return *x;
#endif
        }

        PBRT_CPU_GPU
            inline const DenselySampledSpectrum& Y( )
        {
#ifdef PBRT_IS_GPU_CODE
            extern PBRT_GPU DenselySampledSpectrum* yGPU;
            return *yGPU;
#else
            PBRTO_EXPORT extern DenselySampledSpectrum* y;
            return *y;
#endif
        }

        PBRT_CPU_GPU
            inline const DenselySampledSpectrum& Z( )
        {
#ifdef PBRT_IS_GPU_CODE
            extern PBRT_GPU DenselySampledSpectrum* zGPU;
            return *zGPU;
#else
            PBRTO_EXPORT extern DenselySampledSpectrum* z;
            return *z;
#endif
        }

    }  // namespace Spectra

    // Spectral Function Declarations
    PBRTO_EXPORT Spectrum GetNamedSpectrum( std::string name );

    PBRTO_EXPORT std::string FindMatchingNamedSpectrum( Spectrum s );

    namespace Spectra
    {
        PBRT_CPU_GPU inline const DenselySampledSpectrum& X( );
        PBRT_CPU_GPU inline const DenselySampledSpectrum& Y( );
        PBRT_CPU_GPU inline const DenselySampledSpectrum& Z( );
    }  // namespace Spectra

    // Spectrum Inline Functions
    PBRT_CPU_GPU inline Float InnerProduct( Spectrum f, Spectrum g )
    {
        Float integral = 0;
        for ( Float lambda = Lambda_min; lambda <= Lambda_max; ++lambda )
            integral += f( lambda ) * g( lambda );
        return integral;
    }

    // Spectrum Inline Method Definitions
    PBRT_CPU_GPU inline Float Spectrum::operator()( Float lambda ) const
    {
        auto op = [ & ]( auto ptr ) { return ( *ptr )( lambda ); };
        return Dispatch( op );
    }

    PBRT_CPU_GPU inline SampledSpectrum Spectrum::Sample( const SampledWavelengths& lambda ) const
    {
        auto samp = [ & ]( auto ptr ) { return ptr->Sample( lambda ); };
        return Dispatch( samp );
    }

    PBRT_CPU_GPU inline Float Spectrum::MaxValue( ) const
    {
        auto max = [ & ]( auto ptr ) { return ptr->MaxValue( ); };
        return Dispatch( max );
    }

}  // namespace pbrt

namespace std
{

    template <>
    struct hash<pbrto::DenselySampledSpectrum>
    {
        size_t operator()( const pbrto::DenselySampledSpectrum& s ) const
        {
            return pbrto::HashBuffer( s.values.data( ), s.values.size( ) );
        }
    };

}


#endif
