#pragma once
#ifndef PBRTO_UTIL_NEWCOLOR_H_
#define PBRTO_UTIL_NEWCOLOR_H_

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

#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewTaggedPtr.h>
#include <pbrto/util/NewVecMath.h>


// A special present from windgi.h on Windows...
#ifdef RGB
#undef RGB
#endif  // RGB

namespace pbrto
{

    // RGB Definition
    class RGB
    {
    public:
        // RGB Public Methods
        RGB( ) = default;
        PBRT_CPU_GPU
            RGB( Float r, Float g, Float b ) : r( r ), g( g ), b( b ) {}

        PBRT_CPU_GPU
            RGB& operator+=( RGB s )
        {
            r += s.r;
            g += s.g;
            b += s.b;
            return *this;
        }
        PBRT_CPU_GPU
            RGB operator+( RGB s ) const
        {
            RGB ret = *this;
            return ret += s;
        }

        PBRT_CPU_GPU
            RGB& operator-=( RGB s )
        {
            r -= s.r;
            g -= s.g;
            b -= s.b;
            return *this;
        }
        PBRT_CPU_GPU
            RGB operator-( RGB s ) const
        {
            RGB ret = *this;
            return ret -= s;
        }
        PBRT_CPU_GPU
            friend RGB operator-( Float a, RGB s ) { return { a - s.r, a - s.g, a - s.b }; }

        PBRT_CPU_GPU
            RGB& operator*=( RGB s )
        {
            r *= s.r;
            g *= s.g;
            b *= s.b;
            return *this;
        }
        PBRT_CPU_GPU
            RGB operator*( RGB s ) const
        {
            RGB ret = *this;
            return ret *= s;
        }
        PBRT_CPU_GPU
            RGB operator*( Float a ) const
        {
            NDCHECK( !IsNaN( a ) );
            return { a * r, a * g, a * b };
        }
        PBRT_CPU_GPU
            RGB& operator*=( Float a )
        {
            NDCHECK( !IsNaN( a ) );
            r *= a;
            g *= a;
            b *= a;
            return *this;
        }
        PBRT_CPU_GPU
            friend RGB operator*( Float a, RGB s ) { return s * a; }

        PBRT_CPU_GPU
            RGB& operator/=( RGB s )
        {
            r /= s.r;
            g /= s.g;
            b /= s.b;
            return *this;
        }
        PBRT_CPU_GPU
            RGB operator/( RGB s ) const
        {
            RGB ret = *this;
            return ret /= s;
        }
        PBRT_CPU_GPU
            RGB& operator/=( Float a )
        {
            NDCHECK( !IsNaN( a ) );
            NDCHECK_NE( a, 0 );
            r /= a;
            g /= a;
            b /= a;
            return *this;
        }
        PBRT_CPU_GPU
            RGB operator/( Float a ) const
        {
            RGB ret = *this;
            return ret /= a;
        }

        PBRT_CPU_GPU
            RGB operator-( ) const { return { -r, -g, -b }; }

        PBRT_CPU_GPU
            Float Average( ) const { return ( r + g + b ) / 3; }

        PBRT_CPU_GPU
            bool operator==( RGB s ) const { return r == s.r && g == s.g && b == s.b; }
        PBRT_CPU_GPU
            bool operator!=( RGB s ) const { return r != s.r || g != s.g || b != s.b; }
        PBRT_CPU_GPU
            Float operator[]( int c ) const
        {
            NDCHECK( c >= 0 && c < 3 );
            if ( c == 0 )
                return r;
            else if ( c == 1 )
                return g;
            return b;
        }
        PBRT_CPU_GPU
            Float& operator[]( int c )
        {
            NDCHECK( c >= 0 && c < 3 );
            if ( c == 0 )
                return r;
            else if ( c == 1 )
                return g;
            return b;
        }

        std::string ToString( ) const;

        // RGB Public Members
        Float r = 0, g = 0, b = 0;
    };

    PBRT_CPU_GPU
    inline RGB max( RGB a, RGB b )
    {
        return RGB( std::max( a.r, b.r ), std::max( a.g, b.g ), std::max( a.b, b.b ) );
    }

    PBRT_CPU_GPU
    inline RGB Lerp( Float t, RGB s1, RGB s2 )
    {
        return ( 1 - t ) * s1 + t * s2;
    }

    // RGB Inline Functions
    template <typename U, typename V>
    PBRT_CPU_GPU inline RGB Clamp( RGB rgb, U min, V max )
    {
        return RGB( Math::Clamp( rgb.r, min, max ), Math::Clamp( rgb.g, min, max ), Math::Clamp( rgb.b, min, max ) );
    }
    PBRT_CPU_GPU inline RGB ClampZero( RGB rgb )
    {
        return RGB( std::max<Float>( 0, rgb.r ), std::max<Float>( 0, rgb.g ),
            std::max<Float>( 0, rgb.b ) );
    }

    // XYZ Definition
    class XYZ
    {
    public:
        // XYZ Public Methods
        XYZ( ) = default;
        PBRT_CPU_GPU
            XYZ( Float X, Float Y, Float Z ) : X( X ), Y( Y ), Z( Z ) {}

        PBRT_CPU_GPU
            Float Average( ) const { return ( X + Y + Z ) / 3; }

        PBRT_CPU_GPU
            Point2f xy( ) const { return Point2f( X / ( X + Y + Z ), Y / ( X + Y + Z ) ); }

        PBRT_CPU_GPU
            static XYZ FromxyY( Point2f xy, Float Y = 1 )
        {
            if ( xy.y == 0 )
                return XYZ( 0, 0, 0 );
            return XYZ( xy.x * Y / xy.y, Y, ( 1 - xy.x - xy.y ) * Y / xy.y );
        }

        PBRT_CPU_GPU
            XYZ& operator+=( const XYZ& s )
        {
            X += s.X;
            Y += s.Y;
            Z += s.Z;
            return *this;
        }
        PBRT_CPU_GPU
            XYZ operator+( const XYZ& s ) const
        {
            XYZ ret = *this;
            return ret += s;
        }

        PBRT_CPU_GPU
            XYZ& operator-=( const XYZ& s )
        {
            X -= s.X;
            Y -= s.Y;
            Z -= s.Z;
            return *this;
        }
        PBRT_CPU_GPU
            XYZ operator-( const XYZ& s ) const
        {
            XYZ ret = *this;
            return ret -= s;
        }
        PBRT_CPU_GPU
            friend XYZ operator-( Float a, const XYZ& s ) { return { a - s.X, a - s.Y, a - s.Z }; }

        PBRT_CPU_GPU
            XYZ& operator*=( const XYZ& s )
        {
            X *= s.X;
            Y *= s.Y;
            Z *= s.Z;
            return *this;
        }
        PBRT_CPU_GPU
            XYZ operator*( const XYZ& s ) const
        {
            XYZ ret = *this;
            return ret *= s;
        }
        PBRT_CPU_GPU
            XYZ operator*( Float a ) const
        {
            NDCHECK( !IsNaN( a ) );
            return { a * X, a * Y, a * Z };
        }
        PBRT_CPU_GPU
            XYZ& operator*=( Float a )
        {
            NDCHECK( !IsNaN( a ) );
            X *= a;
            Y *= a;
            Z *= a;
            return *this;
        }

        PBRT_CPU_GPU
            XYZ& operator/=( const XYZ& s )
        {
            X /= s.X;
            Y /= s.Y;
            Z /= s.Z;
            return *this;
        }
        PBRT_CPU_GPU
            XYZ operator/( const XYZ& s ) const
        {
            XYZ ret = *this;
            return ret /= s;
        }
        PBRT_CPU_GPU
            XYZ& operator/=( Float a )
        {
            NDCHECK( !IsNaN( a ) );
            NDCHECK_NE( a, 0 );
            X /= a;
            Y /= a;
            Z /= a;
            return *this;
        }
        PBRT_CPU_GPU
            XYZ operator/( Float a ) const
        {
            XYZ ret = *this;
            return ret /= a;
        }

        PBRT_CPU_GPU
            XYZ operator-( ) const { return { -X, -Y, -Z }; }

        PBRT_CPU_GPU
            bool operator==( const XYZ& s ) const { return X == s.X && Y == s.Y && Z == s.Z; }
        PBRT_CPU_GPU
            bool operator!=( const XYZ& s ) const { return X != s.X || Y != s.Y || Z != s.Z; }
        PBRT_CPU_GPU
            Float operator[]( int c ) const
        {
            NDCHECK( c >= 0 && c < 3 );
            if ( c == 0 )
                return X;
            else if ( c == 1 )
                return Y;
            return Z;
        }
        PBRT_CPU_GPU
            Float& operator[]( int c )
        {
            NDCHECK( c >= 0 && c < 3 );
            if ( c == 0 )
                return X;
            else if ( c == 1 )
                return Y;
            return Z;
        }

        std::string ToString( ) const;

        // XYZ Public Members
        Float X = 0, Y = 0, Z = 0;
    };

    PBRT_CPU_GPU
        inline XYZ operator*( Float a, const XYZ& s )
    {
        return s * a;
    }


    template <typename U, typename V>
    PBRT_CPU_GPU inline XYZ Clamp( const XYZ& xyz, U min, V max )
    {
        return XYZ( Math::Clamp( xyz.X, min, max ), Math::Clamp( xyz.Y, min, max ), Math::Clamp( xyz.Z, min, max ) );
    }

    PBRT_CPU_GPU
    inline XYZ ClampZero( const XYZ& xyz )
    {
        return XYZ( std::max<Float>( 0, xyz.X ), std::max<Float>( 0, xyz.Y ),
            std::max<Float>( 0, xyz.Z ) );
    }

    PBRT_CPU_GPU
    inline XYZ Lerp( Float t, const XYZ& s1, const XYZ& s2 )
    {
        return ( 1 - t ) * s1 + t * s2;
    }

    // RGBSigmoidPolynomial Definition
    class RGBSigmoidPolynomial
    {
    public:
        // RGBSigmoidPolynomial Public Methods
        RGBSigmoidPolynomial( ) = default;
        PBRT_CPU_GPU
            RGBSigmoidPolynomial( Float c0, Float c1, Float c2 ) : c0( c0 ), c1( c1 ), c2( c2 ) {}
        std::string ToString( ) const;

        PBRT_CPU_GPU
            Float operator()( Float lambda ) const
        {
            return s( EvaluatePolynomial( lambda, c2, c1, c0 ) );
        }

        PBRT_CPU_GPU
            Float MaxValue( ) const
        {
            Float result = std::max( ( *this )( 360 ), ( *this )( 830 ) );
            Float lambda = -c1 / ( 2 * c0 );
            if ( lambda >= 360 && lambda <= 830 )
                result = std::max( result, ( *this )( lambda ) );
            return result;
        }

    private:
        // RGBSigmoidPolynomial Private Methods
        PBRT_CPU_GPU
            static Float s( Float x )
        {
            if ( IsInf( x ) )
                return x > static_cast< Float >( 0 ) ? static_cast< Float >( 1 ) : static_cast< Float >( 0 );
            return static_cast< Float >( .5 ) + x / ( static_cast< Float >( 2 ) * Math::Sqrt( static_cast< Float >( 1 ) + Sqr( x ) ) );
        };

        // RGBSigmoidPolynomial Private Members
        Float c0, c1, c2;
    };

    // RGBToSpectrumTable Definition
    class RGBToSpectrumTable
    {
    public:
        // RGBToSpectrumTable Public Constants
        static constexpr int res = 64;

        using CoefficientArray = float[ 3 ][ res ][ res ][ res ][ 3 ];

        // RGBToSpectrumTable Public Methods
        RGBToSpectrumTable( const float* zNodes, const CoefficientArray* coeffs )
            : zNodes( zNodes ), coeffs( coeffs )
        {
        }

        PBRT_CPU_GPU
            RGBSigmoidPolynomial operator()( RGB rgb ) const;

        static void Init( Allocator alloc );

        static const RGBToSpectrumTable* sRGB;
        static const RGBToSpectrumTable* DCI_P3;
        static const RGBToSpectrumTable* Rec2020;
        static const RGBToSpectrumTable* ACES2065_1;

        std::string ToString( ) const;

    private:
        // RGBToSpectrumTable Private Members
        const float* zNodes;
        const CoefficientArray* coeffs;
    };

    // ColorEncoding Definitions
    class LinearColorEncoding;
    class sRGBColorEncoding;
    class GammaColorEncoding;

    


    class ColorEncoding : public TaggedPointer<LinearColorEncoding, sRGBColorEncoding, GammaColorEncoding>
    {
    public:
        using TaggedPointer::TaggedPointer;
        
        // ColorEncoding Interface
        void ToLinear( const std::span<const uint8_t>& vin, const std::span<Float>& vout ) const;
        void FromLinear( const std::span<const Float>& vin, const std::span<uint8_t>& vout ) const;

        Float ToFloatLinear( Float v ) const;

        std::string ToString( ) const;

        static const ColorEncoding Get( const std::string& name, Allocator alloc );

        static ColorEncoding Linear;
        static ColorEncoding sRGB;

        static void Init( Allocator alloc );
    };

    class LinearColorEncoding
    {
    public:
        void ToLinear( const std::span<const uint8_t>& vin, const std::span<Float>& vout ) const
        {
            NDCHECK_EQ( vin.size( ), vout.size( ) );
            for ( size_t i = 0; i < vin.size( ); ++i )
            {
                vout[ i ] = vin[ i ] / 255.f;
            }
        }

        void FromLinear( const std::span<const Float>& vin, const std::span<uint8_t>& vout ) const
        {
            NDCHECK_EQ( vin.size( ), vout.size( ) );
            for ( size_t i = 0; i < vin.size( ); ++i )
            {
                vout[ i ] = uint8_t( Math::Clamp( vin[ i ] * 255.f + 0.5f, 0.f, 255.f ) );
            }
        }

        Float ToFloatLinear( Float v ) const 
        { 
            return v; 
        }

        

        std::string ToString( ) const { return "[ LinearColorEncoding ]"; }
    };

    class sRGBColorEncoding
    {
    public:
        // sRGBColorEncoding Public Methods
        void ToLinear( const std::span<const uint8_t>& vin, const std::span<Float>& vout ) const;
        Float ToFloatLinear( Float v ) const;
        void FromLinear( const std::span<const Float>& vin, const std::span<uint8_t>& vout ) const;

        std::string ToString( ) const { return "[ sRGBColorEncoding ]"; }
    };

    class GammaColorEncoding
    {
    public:
        GammaColorEncoding( Float gamma );

        void ToLinear( const std::span<const uint8_t>& vin, const std::span<Float>& vout ) const;
        Float ToFloatLinear( Float v ) const;
        void FromLinear( const std::span<const Float>& vin, const std::span<uint8_t>& vout ) const;

        std::string ToString( ) const;

    private:
        Float gamma;
        pstdo::array<Float, 256> applyLUT;
        pstdo::array<Float, 1024> inverseLUT;
    };

    inline void ColorEncoding::ToLinear( const std::span<const uint8_t>& vin, const std::span<Float>& vout ) const
    {
        auto tolin = [ & ]( auto ptr ) { return ptr->ToLinear( vin, vout ); };
        Dispatch( tolin );
    }

    inline Float ColorEncoding::ToFloatLinear( Float v ) const
    {
        auto tfl = [ & ]( auto ptr ) { return ptr->ToFloatLinear( v ); };
        return Dispatch( tfl );
    }

    inline void ColorEncoding::FromLinear( const std::span<const Float>& vin, const std::span<uint8_t>& vout ) const
    {
        auto fl = [ & ]( auto ptr ) { return ptr->FromLinear( vin, vout ); };
        Dispatch( fl );
    }

    constexpr inline Float LinearToSRGB( Float value )
    {
        if ( value <= 0.0031308f )
            return 12.92f * value;
        // Minimax polynomial approximation from enoki's color.h.
        float sqrtValue = Math::SafeSqrt( value );
        float p = Math::EvaluatePolynomial( sqrtValue, -0.0016829072605308378f, 0.03453868659826638f,
            0.7642611304733891f, 2.0041169284241644f,
            0.7551545191665577f, -0.016202083165206348f );
        float q = Math::EvaluatePolynomial( sqrtValue, 4.178892964897981e-7f,
            -0.00004375359692957097f, 0.03467195408529984f,
            0.6085338522168684f, 1.8970238036421054f, 1.f );
        return p / q * value;
    }

    constexpr inline uint8_t LinearToSRGB8( Float value, Float dither = 0.f )
    {
        if ( value <= 0.f )
            return 0;
        if ( value >= 1.f )
            return 255;
        return static_cast< uint8_t >( Math::Clamp( Math::Round( 255.f * LinearToSRGB( value ) + dither ), 0.f, 255.f ) );
    }

    constexpr inline Float SRGBToLinear( float value )
    {
        if ( value <= 0.04045f )
            return value * ( 1 / 12.92f );
        // Minimax polynomial approximation from enoki's color.h.
        float p = EvaluatePolynomial( value, -0.0163933279112946f, -0.7386328024653209f,
            -11.199318357635072f, -47.46726633009393f,
            -36.04572663838034f );
        float q = EvaluatePolynomial( value, -0.004261480793199332f, -19.140923959601675f,
            -59.096406619244426f, -18.225745396846637f, 1.f );
        return p / q * value;
    }

    extern PBRT_CONST Float SRGBToLinearLUT[ 256 ];

    inline Float SRGB8ToLinear( uint8_t value )
    {
        return SRGBToLinearLUT[ value ];
    }

    // White Balance Definitions
    // clang-format off
    // These are the Bradford transformation matrices.
    const SquareMatrix<3> LMSFromXYZ(
        static_cast< Float >( 0.8951 ), static_cast< Float >( 0.2664 ), static_cast< Float >( -0.1614 ),
        static_cast< Float >( -0.7502 ), static_cast< Float >( 1.7135 ), static_cast< Float >( 0.0367 ),
        static_cast< Float >( 0.0389 ), static_cast< Float >( -0.0685 ), static_cast< Float >( 1.0296 ) );
    const SquareMatrix<3> XYZFromLMS(
        static_cast< Float >( 0.986993 ), static_cast< Float >( -0.147054 ), static_cast< Float >( 0.159963 ),
        static_cast< Float >( 0.432305 ), static_cast< Float >( 0.51836 ), static_cast< Float >( 0.0492912 ),
        static_cast< Float >( -0.00852866 ), static_cast< Float >( 0.0400428 ), static_cast< Float >( 0.968487 ) );
    // clang-format on

    inline SquareMatrix<3> WhiteBalance( const Point2f& srcWhite, const Point2f& targetWhite )
    {
        // Find LMS coefficients for source and target white
        XYZ srcXYZ = XYZ::FromxyY( srcWhite ); 
        XYZ dstXYZ = XYZ::FromxyY( targetWhite );
        auto srcLMS = LMSFromXYZ * srcXYZ;
        auto dstLMS = LMSFromXYZ * dstXYZ;

        // Return white balancing matrix for source and target white
        SquareMatrix<3> LMScorrect = SquareMatrix<3>::Diag(
            dstLMS[ 0 ] / srcLMS[ 0 ], dstLMS[ 1 ] / srcLMS[ 1 ], dstLMS[ 2 ] / srcLMS[ 2 ] );
        return XYZFromLMS * LMScorrect * LMSFromXYZ;
    }

}

#endif
