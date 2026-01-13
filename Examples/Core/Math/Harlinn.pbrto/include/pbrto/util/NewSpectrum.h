#pragma once
#ifndef PBRTO_UTIL_NEWSPECTRUM_H_
#define PBRTO_UTIL_NEWSPECTRUM_H_

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

//#define USE_MODIFIED_SAMPLEDSPECTRUM
#define USE_MODIFIED_SAMPLEDSPECTRUM_TEST
    // Spectrum Constants
    constexpr Float Lambda_min = 360, Lambda_max = 830;

    // Must be a multiple of 4
    static constexpr int NSpectrumSamples = 4;
    static_assert( ( NSpectrumSamples & 3 ) == 0 );

    constexpr bool SampledSpectrumUsesLargeTraits = ( NSpectrumSamples & 7 ) == 0;
    constexpr size_t SampledSpectrumTraitsSize = SampledSpectrumUsesLargeTraits ? 8 : 4;
    constexpr size_t SampledSpectrumAlignAs = SampledSpectrumUsesLargeTraits ? 32 : 16;
    constexpr size_t SampledSpectrumIterationCount = NSpectrumSamples / SampledSpectrumTraitsSize;

    static constexpr Float CIE_Y_integral = 106.856895;



    // SampledSpectrum Definition
    class alignas( SampledSpectrumAlignAs ) SampledSpectrum
    {
    public:
        
        using Traits = SIMD::Traits<Float, SampledSpectrumTraitsSize>;
        using VectorType = std::array<Float, NSpectrumSamples>;
        static constexpr size_t IterationCount = SampledSpectrumIterationCount;
        static constexpr size_t TraitsSize = SampledSpectrumTraitsSize;
    private:
        friend struct SOA<SampledSpectrum>;
        
    public:
        VectorType values{};
        SampledSpectrum( ) = default;
        
        explicit SampledSpectrum( Float c ) 
        { 
            values.fill( c ); 
        }

        SampledSpectrum( const VectorType& v )
            : values( v )
        { }

        /*
        SampledSpectrum( std::span<const Float> v )
            : values( v.begin(), v.end() )
        {
            NDCHECK_EQ( NSpectrumSamples, v.size( ) );
            for ( int i = 0; i < NSpectrumSamples; ++i )
                values[ i ] = v[ i ];
        }
        */
        Float operator[]( int i ) const
        {
            NDCHECK( i >= 0 && i < NSpectrumSamples );
            return values[ i ];
        }
        Float& operator[]( int i )
        {
            NDCHECK( i >= 0 && i < NSpectrumSamples );
            return values[ i ];
        }

    //private:
        Traits::SIMDType Load( size_t i ) const
        {
            size_t offset = i * TraitsSize;
            return Traits::Load( values.data( ) + offset );
        }
        void Store( size_t i, Traits::SIMDType v )
        {
            size_t offset = i * TraitsSize;
            Traits::Store( values.data( ) + offset, v );
        }
    public:

        explicit operator bool( ) const
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            for ( int i = 0; i < NSpectrumSamples; ++i )
                if ( values[ i ] != 0 )
                    return true;
            return false;
#else            
            auto zero = Traits::Zero( );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v = Load( i );
                if ( Traits::AllEqual( v, zero ) == false )
                {
                    return true;
                }
            }
            return false;
#endif
        }

        // SampledSpectrum Public Methods
        SampledSpectrum operator+( const SampledSpectrum& s ) const
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            SampledSpectrum ret = *this;
            return ret += s;
#else            
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v2 = s.Load( i );
                result.Store( i, Traits::Add( v1, v2 ) );
            }
            return result;
#endif
        }

        SampledSpectrum& operator+=( const SampledSpectrum& s )
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            for ( int i = 0; i < NSpectrumSamples; ++i )
                values[ i ] += s.values[ i ];
#else            
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v2 = s.Load( i );
                Store( i, Traits::Add( v1, v2 ) );
            }
#endif
            return *this;
        }

        SampledSpectrum operator-( const SampledSpectrum& s ) const
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            SampledSpectrum ret = *this;
            return ret -= s;
#else
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v2 = s.Load( i );
                result.Store( i, Traits::Sub( v1, v2 ) );
            }
            return result;
#endif
        }

        SampledSpectrum& operator-=( const SampledSpectrum& s )
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            for ( int i = 0; i < NSpectrumSamples; ++i )
                values[ i ] -= s.values[ i ];
#else
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v2 = s.Load( i );
                Store( i, Traits::Sub( v1, v2 ) );
            }
#endif
            return *this;
        }
        
        friend SampledSpectrum operator-( Float a, const SampledSpectrum& s )
        {
            NDCHECK( !IsNaN( a ) );
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            SampledSpectrum ret;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                ret.values[ i ] = a - s.values[ i ];
            return ret;
#else
            SampledSpectrum result;
            auto v1 = Traits::Fill( a );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                
                auto v2 = s.Load( i );
                result.Store( i, Traits::Sub( v1, v2 ) );
            }
            return result;
#endif
        }

        SampledSpectrum operator*( const SampledSpectrum& s ) const
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            SampledSpectrum ret = *this;
            return ret *= s;
#else            
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v2 = s.Load( i );
                result.Store( i, Traits::Mul( v1, v2 ) );
            }
            return result;
#endif
        }

        SampledSpectrum& operator*=( const SampledSpectrum& s )
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            for ( int i = 0; i < NSpectrumSamples; ++i )
                values[ i ] *= s.values[ i ];
#else            
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v2 = s.Load( i );
                Store( i, Traits::Mul( v1, v2 ) );
            }
#endif
            return *this;
        }
        
        SampledSpectrum operator*( Float a ) const
        {
            NDCHECK( !IsNaN( a ) );
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            SampledSpectrum ret = *this;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                ret.values[ i ] *= a;
            return ret;
#else
            SampledSpectrum result;
            auto v2 = Traits::Fill( a );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                result.Store( i, Traits::Mul( v1, v2 ) );
            }
            return result;
#endif
        }
        SampledSpectrum& operator*=( Float a )
        {
            NDCHECK( !IsNaN( a ) );
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            for ( int i = 0; i < NSpectrumSamples; ++i )
                values[ i ] *= a;
#else            
            SampledSpectrum result;
            auto v2 = Traits::Fill( a );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                Store( i, Traits::Mul( v1, v2 ) );
            }
#endif
            return *this;
        }
        friend SampledSpectrum operator*( Float a, const SampledSpectrum& s ) 
        { 
            return s * a; 
        }

        SampledSpectrum operator/( const SampledSpectrum& s ) const
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            SampledSpectrum ret = *this;
            return ret /= s;
#else            
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v2 = s.Load( i );
                result.Store( i, Traits::Div( v1, v2 ) );
            }
            return result;
#endif
            
        }

        SampledSpectrum& operator/=( const SampledSpectrum& s )
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            for ( int i = 0; i < NSpectrumSamples; ++i )
            {
                NDCHECK_NE( 0, s.values[ i ] );
                values[ i ] /= s.values[ i ];
            }
#else
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v2 = s.Load( i );
                Store( i, Traits::Div( v1, v2 ) );
            }
#endif
            return *this;
        }
        
        SampledSpectrum operator/( Float a ) const
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            SampledSpectrum ret = *this;
            return ret /= a;
#else
            SampledSpectrum result;
            auto v2 = Traits::Fill( a );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                result.Store( i, Traits::Div( v1, v2 ) );
            }
            return result;
#endif
        }

        SampledSpectrum& operator/=( Float a )
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            NDCHECK_NE( a, 0 );
            NDCHECK( !IsNaN( a ) );
            for ( int i = 0; i < NSpectrumSamples; ++i )
                values[ i ] /= a;
#else
            auto v2 = Traits::Fill( a );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                Store( i, Traits::Div( v1, v2 ) );
            }
#endif
            return *this;
        }
        

        SampledSpectrum operator-( ) const
        {
#ifndef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            SampledSpectrum ret;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                ret.values[ i ] = -values[ i ];
            return ret;
#else
            SampledSpectrum result;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                result.Store( i, Traits::Negate( v1 ) );
            }
            return result;
#endif
        }
        bool operator==( const SampledSpectrum& s ) const { return values == s.values; }
        bool operator!=( const SampledSpectrum& s ) const { return values != s.values; }

        std::string ToString( ) const;

        bool HasNaNs( ) const
        {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            auto zero = Traits::Zero( );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v = Load( i );
                if ( Traits::HasNaN( v ) )
                {
                    return true;
                }
            }
            return false;
            
#else
            for ( int i = 0; i < NSpectrumSamples; ++i )
                if ( IsNaN( values[ i ] ) )
                    return true;
            return false;
#endif
        }

        PBRTO_EXPORT XYZ ToXYZ( const SampledWavelengths& lambda ) const;
        PBRTO_EXPORT RGB ToRGB( const SampledWavelengths& lambda, const RGBColorSpace& cs ) const;
        PBRTO_EXPORT Float Y( const SampledWavelengths& lambda ) const;
        PBRTO_EXPORT static Float Y( const SampledSpectrum& s, const SampledWavelengths& lambda );

        

        

        Float MinComponentValue( ) const
        {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            Float result = std::numeric_limits<Float>::max( );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v = Traits::HorizontalMin( v1 );
                result = Math::Min( result, v );
            }
            return result;
#else
            
            Float m = values[ 0 ];
            for ( int i = 1; i < NSpectrumSamples; ++i )
                m = std::min( m, values[ i ] );
            return m;
#endif
            
        }
        Float MaxComponentValue( ) const
        {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            Float result = std::numeric_limits<Float>::lowest( );
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                auto v = Traits::HorizontalMax( v1 );
                result = Math::Max( result, v );
            }
            return result;
#else
            Float m = values[ 0 ];
            for ( int i = 1; i < NSpectrumSamples; ++i )
                m = std::max( m, values[ i ] );
            return m;
#endif            
        }
        Float Average( ) const
        {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
            Float result = 0,f;
            for ( size_t i = 0; i < IterationCount; i++ )
            {
                auto v1 = Load( i );
                result += Traits::Avg( v1 );
            }
            return result / IterationCount;
#else
            
            Float sum = values[ 0 ];
            for ( int i = 1; i < NSpectrumSamples; ++i )
                sum += values[ i ];
            return sum / NSpectrumSamples;
#endif            
        }

    private:
        
    };

    inline SampledSpectrum Sqr( const SampledSpectrum& sampledSpectrum )
    {
        return sampledSpectrum * sampledSpectrum;
    }

    inline SampledSpectrum SafeDiv( const SampledSpectrum& a, const SampledSpectrum& b )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;

        auto zeros = Traits::Zero( );

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v1 = a.Load( i );
            auto v2 = b.Load( i );
            auto r = Traits::Div( v1, v2 );
            auto isZero = Traits::Equal( v2, zeros );

            r = Traits::Select( r, zeros, isZero );
            result.Store( i, r );
        }

        return result;
#else
        SampledSpectrum r;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            r[ i ] = ( b[ i ] != 0 ) ? a[ i ] / b[ i ] : 0.;
        return r;
#endif
    }

    template <typename U, typename V>
    inline SampledSpectrum Clamp( const SampledSpectrum& s, U low, V high )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;
        auto l = Traits::Fill( static_cast< Traits::Type >( low ) );
        auto h = Traits::Fill( static_cast< Traits::Type >( high ) );

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v = s.Load( i );

            auto r = Traits::Clamp( v, l, h );
            result.Store( i, r );
        }

        return result;

#else
        SampledSpectrum ret;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            ret[ i ] = Math::Clamp( s[ i ], low, high );
        NDCHECK( !ret.HasNaNs( ) );
        return ret;
#endif
    }

    inline SampledSpectrum ClampZero( const SampledSpectrum& s )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;
        auto zeros = Traits::Zero( );

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v = s.Load( i );

            auto r = Traits::Max( zeros, v );
            result.Store( i, r );
        }

        return result;

#else
        SampledSpectrum ret;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            ret[ i ] = Math::Max<Float>( 0, s[ i ] );
        NDCHECK( !ret.HasNaNs( ) );
        return ret;
#endif
    }

    inline SampledSpectrum Sqrt( const SampledSpectrum& s )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v = s.Load( i );
            auto r = Traits::Sqrt( v );
            result.Store( i, r );
        }

        return result;

#else
        SampledSpectrum ret;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            ret[ i ] = Math::Sqrt( s[ i ] );
        NDCHECK( !ret.HasNaNs( ) );
        return ret;
#endif
    }

    inline SampledSpectrum SafeSqrt( const SampledSpectrum& s )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;
        auto zeros = Traits::Zero( );

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v = s.Load( i );
            v = Traits::Max( zeros, v );
            auto r = Traits::Sqrt( v );
            result.Store( i, r );
        }

        return result;

#else
        SampledSpectrum ret;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            ret[ i ] = SafeSqrt( s[ i ] );
        NDCHECK( !ret.HasNaNs( ) );
        return ret;
#endif
    }

    inline SampledSpectrum Pow( const SampledSpectrum& s, Float e )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;
        auto exponent = Traits::Fill( e );

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v = s.Load( i );
            auto r = Traits::Pow( v, exponent );
            result.Store( i, r );
        }

        return result;

#else
        SampledSpectrum ret;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            ret[ i ] = Math::Pow( s[ i ], e );
        return ret;
#endif
    }

    inline SampledSpectrum Exp( const SampledSpectrum& s )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST_
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v = s.Load( i );
            auto r = Traits::Exp( v );
            result.Store( i, r );
        }

        return result;

#else
        SampledSpectrum ret;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            ret[ i ] = Math::FastExp( s[ i ] );
        NDCHECK( !ret.HasNaNs( ) );
        return ret;
#endif
    }

    inline SampledSpectrum FastExp( const SampledSpectrum& s )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST_
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v = s.Load( i );
            auto r = Traits::Exp( v );
            result.Store( i, r );
        }

        return result;

#else
        SampledSpectrum ret;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            ret[ i ] = FastExp( s[ i ] );
        NDCHECK( !ret.HasNaNs( ) );
        return ret;
#endif
    }

    inline SampledSpectrum Log( const SampledSpectrum& s )
    {
#ifdef USE_MODIFIED_SAMPLEDSPECTRUM_TEST_
        using Traits = SampledSpectrum::Traits;
        SampledSpectrum result;

        for ( size_t i = 0; i < SampledSpectrum::IterationCount; i++ )
        {
            auto v = s.Load( i );
            auto r = Traits::Log( v );
            result.Store( i, r );
        }

        return result;

#else
        SampledSpectrum ret;
        for ( int i = 0; i < NSpectrumSamples; ++i )
            ret[ i ] = Math::Log( s[ i ] );
        NDCHECK( !ret.HasNaNs( ) );
        return ret;
#endif
    }

    inline Float ScalarAvg( const SampledSpectrum& s )
    {
        return s.Average( );
    }

    inline Float MaxComponentValue( const SampledSpectrum& s )
    {
        return s.MaxComponentValue( );
    }

    inline Float MinComponentValue( const SampledSpectrum& s )
    {
        return s.MinComponentValue( );
    }


    inline SampledSpectrum Bilerp( pstdo::array<Float, 2> p, pstdo::span<const SampledSpectrum> v )
    {
        return ( 
            (( 1 - p[ 0 ] ) * ( 1 - p[ 1 ] )) * v[ 0 ] + 
            (p[ 0 ] * ( 1 - p[ 1 ] )) * v[ 1 ] +
            (( 1 - p[ 0 ] ) * p[ 1 ]) * v[ 2 ] + 
            (p[ 0 ] * p[ 1 ]) * v[ 3 ] );

        //return ( ( 1 - p[ 0 ] ) * ( 1 - p[ 1 ] ) * v[ 0 ] + p[ 0 ] * ( 1 - p[ 1 ] ) * v[ 1 ] +
        //    ( 1 - p[ 0 ] ) * p[ 1 ] * v[ 2 ] + p[ 0 ] * p[ 1 ] * v[ 3 ] );
    }

    inline SampledSpectrum Lerp2( Float t, const SampledSpectrum& s1, const SampledSpectrum& s2 )
    {
        return ( 1 - t ) * s1 + t * s2;
    }



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
        std::string ToString( ) const;

        Float operator()( Float lambda ) const;

        Float MaxValue( ) const;

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const;
    };

    // Spectrum Function Declarations
    PBRT_CPU_GPU inline Float Blackbody( Float lambda, Float T )
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

    

    


    // SampledWavelengths Definitions
    class alignas( SampledSpectrumAlignAs ) SampledWavelengths
    {
    public:
        using VectorType = SampledSpectrum::VectorType;
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
            swl.lambda[ 0 ] = Lerp2( u, lambda_min, lambda_max );

            // Initialize _lambda_ for remaining wavelengths
            Float delta = ( lambda_max - lambda_min ) / NSpectrumSamples;
            for ( int i = 1; i < NSpectrumSamples; ++i )
            {
                swl.lambda[ i ] = swl.lambda[ i - 1 ] + delta;
                if ( swl.lambda[ i ] > lambda_max )
                    swl.lambda[ i ] = lambda_min + ( swl.lambda[ i ] - lambda_max );
            }

            // Compute PDF for sampled wavelengths
            //for ( int i = 0; i < NSpectrumSamples; ++i )
            //    swl.pdf[ i ] = 1 / ( lambda_max - lambda_min );

            swl.pdf.fill( 1.f / ( lambda_max - lambda_min ) );

            return swl;
        }

        const VectorType& Lambda( ) const
        {
            return lambda;
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
                return;
            // Update wavelength probabilities for termination
            for ( int i = 1; i < NSpectrumSamples; ++i )
            {
                pdf[ i ] = 0;
            }
            pdf[ 0 ] /= NSpectrumSamples;
            
        }

        bool SecondaryTerminated( ) const
        {
            for ( int i = 1; i < NSpectrumSamples; ++i )
                if ( pdf[ i ] != 0 )
                    return false;
            return true;
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

                auto sample = SampleVisibleWavelengths( up );
                swl.lambda[ i ] = sample;
                swl.pdf[ i ] = VisibleWavelengthsPDF( sample );
            }
            return swl;
        }

    private:
        
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
        SampledSpectrum Sample( const SampledWavelengths& ) const
        {
            return SampledSpectrum( c );
        }

        Float MaxValue( ) const 
        { 
            return c; 
        }

        PBRTO_EXPORT std::string ToString( ) const;
        
    };

    class DenselySampledSpectrum
    {
        friend struct std::hash<pbrto::DenselySampledSpectrum>;
        // DenselySampledSpectrum Private Members
        int lambda_min, lambda_max;
        pstdo::vector<Float> values;
    public:
        // DenselySampledSpectrum Public Methods
        DenselySampledSpectrum( int lambda_min = Lambda_min, int lambda_max = Lambda_max, Allocator alloc = {} )
            : lambda_min( lambda_min ), lambda_max( lambda_max ), values( lambda_max - lambda_min + 1, alloc )
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

        std::string ToString( ) const;

        DenselySampledSpectrum( Spectrum spec, int lambda_min = Lambda_min, int lambda_max = Lambda_max, Allocator alloc = {} )
            : lambda_min( lambda_min ),
              lambda_max( lambda_max ),
              values( lambda_max - lambda_min + 1, alloc )
        {
            NCHECK_GE( lambda_max, lambda_min );
            if ( spec )
                for ( int lambda = lambda_min; lambda <= lambda_max; ++lambda )
                    values[ lambda - lambda_min ] = spec( lambda );
        }

        template <typename F>
        static DenselySampledSpectrum SampleFunction( F func, int lambda_min = Lambda_min, int lambda_max = Lambda_max, Allocator alloc = {} )
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

    private:
        
    };

    class PiecewiseLinearSpectrum
    {
        // PiecewiseLinearSpectrum Private Members
        pstdo::vector<Float> lambdas, values;
    public:
        // PiecewiseLinearSpectrum Public Methods
        PiecewiseLinearSpectrum( ) = default;

        void Scale( Float s )
        {
            for ( Float& v : values )
                v *= s;
        }

        Float MaxValue( ) const
        {
            if ( values.empty( ) )
                return 0;
            return *std::max_element( values.begin( ), values.end( ) );
        }

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                s[ i ] = ( *this )( lambda[ i ] );
            return s;
        }
        Float operator()( Float lambda ) const
        {
            // Handle _PiecewiseLinearSpectrum_ corner cases
            if ( lambdas.empty( ) || lambda < lambdas.front( ) || lambda > lambdas.back( ) )
                return 0;

            // Find offset to largest _lambdas_ below _lambda_ and interpolate
            int o = FindInterval( lambdas.size( ), [ & ]( int i ) { return lambdas[ i ] <= lambda; } );
            NDCHECK( lambda >= lambdas[ o ] && lambda <= lambdas[ o + 1 ] );
            Float t = ( lambda - lambdas[ o ] ) / ( lambdas[ o + 1 ] - lambdas[ o ] );
            return Lerp2( t, values[ o ], values[ o + 1 ] );
        }

        PBRTO_EXPORT std::string ToString( ) const;

        PBRTO_EXPORT PiecewiseLinearSpectrum( pstdo::span<const Float> lambdas, pstdo::span<const Float> values, Allocator alloc = {} );

        PBRTO_EXPORT static pstdo::optional<Spectrum> Read( const std::string& filename, Allocator alloc );

        PBRTO_EXPORT static PiecewiseLinearSpectrum* FromInterleaved( pstdo::span<const Float> samples, bool normalize, Allocator alloc );

    private:
        
    };

    class BlackbodySpectrum
    {
        // BlackbodySpectrum Private Members
        Float T;
        Float normalizationFactor;
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

        Float MaxValue( ) const { return 1.f; }

        PBRTO_EXPORT std::string ToString( ) const;
    };

    class RGBAlbedoSpectrum
    {
        // RGBAlbedoSpectrum Private Members
        RGBSigmoidPolynomial rsp;
    public:
        // RGBAlbedoSpectrum Public Methods
        Float operator()( Float lambda ) const 
        { 
            return rsp( lambda ); 
        }
        Float MaxValue( ) const 
        { 
            return rsp.MaxValue( ); 
        }

        PBRTO_EXPORT RGBAlbedoSpectrum( const RGBColorSpace& cs, RGB rgb );

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                s[ i ] = rsp( lambda[ i ] );
            return s;
        }

        PBRTO_EXPORT std::string ToString( ) const;

    };

    class RGBUnboundedSpectrum
    {
        // RGBUnboundedSpectrum Private Members
        Float scale = 1;
        RGBSigmoidPolynomial rsp;
    public:
        // RGBUnboundedSpectrum Public Methods
        Float operator()( Float lambda ) const 
        { 
            return scale * rsp( lambda ); 
        }
        Float MaxValue( ) const 
        { 
            return scale * rsp.MaxValue( ); 
        }

        PBRTO_EXPORT RGBUnboundedSpectrum( const RGBColorSpace& cs, RGB rgb );

        RGBUnboundedSpectrum( ) 
            : rsp( 0, 0, 0 ), scale( 0 ) 
        { }

        SampledSpectrum Sample( const SampledWavelengths& lambda ) const
        {
            SampledSpectrum s;
            for ( int i = 0; i < NSpectrumSamples; ++i )
                s[ i ] = scale * rsp( lambda[ i ] );
            return s;
        }

        PBRTO_EXPORT std::string ToString( ) const;
    };

    class RGBIlluminantSpectrum
    {
        // RGBIlluminantSpectrum Private Members
        Float scale;
        RGBSigmoidPolynomial rsp;
        const DenselySampledSpectrum* illuminant;
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
    };


    

    // Spectral Data Declarations
    namespace Spectra
    {

        void Init( Allocator alloc );

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
        auto samp = [ & ]( auto ptr ) 
            { 
                return ptr->Sample( lambda ); 
            };
        return Dispatch( samp );
    }

    PBRT_CPU_GPU inline Float Spectrum::MaxValue( ) const
    {
        auto max = [ & ]( auto ptr ) { return ptr->MaxValue( ); };
        return Dispatch( max );
    }

} 

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
