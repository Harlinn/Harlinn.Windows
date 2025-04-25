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
    class RGB : public Math::Tuple3<RGB, Float>
    {
    public:
        using Base = Math::Tuple3<RGB, Float>;
        using Base::Base;
        // RGB Public Methods
        RGB( ) = default;

        Float Average( ) const
        {
            return ( x + y + z ) / 3;
        }

        std::string ToString( ) const;

        Float r( ) const
        {
            return x;
        }
        Float g( ) const
        {
            return y;
        }
        Float b( ) const
        {
            return z;
        }
    };

    // XYZ Definition
    class XYZ : public Math::Tuple3<XYZ,Float>
    {
    public:
        using Base = Math::Tuple3<XYZ, Float>;
        using Base::Base;
        
        // XYZ Public Methods
        XYZ( ) = default;

        Float Average( ) const 
        { 
            return ( x + y + z ) / 3; 
        }

        Point2f xy( ) const 
        { 
            return Point2f( x / ( x + y + z ), y / ( x + y + z ) ); 
        }

        static XYZ FromxyY( Point2f xy, Float Y = 1 )
        {
            if ( xy.y == 0 )
                return XYZ( 0, 0, 0 );
            return XYZ( xy.x * Y / xy.y, Y, ( 1 - xy.x - xy.y ) * Y / xy.y );
        }
        std::string ToString( ) const;

        
    };

    // RGBSigmoidPolynomial Definition
    class RGBSigmoidPolynomial
    {
        // RGBSigmoidPolynomial Private Members
        Float c0, c1, c2;
    public:
        // RGBSigmoidPolynomial Public Methods
        RGBSigmoidPolynomial( ) = default;
        RGBSigmoidPolynomial( Float c0, Float c1, Float c2 ) 
            : c0( c0 ), c1( c1 ), c2( c2 ) 
        { }
        std::string ToString( ) const;

        Float operator()( Float lambda ) const
        {
            return s( EvaluatePolynomial( lambda, c2, c1, c0 ) );
        }

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
        static Float s( Float x )
        {
            if ( IsInf( x ) )
                return x > 0 ? 1 : 0;
            return .5f + x / ( 2 * Math::Sqrt( 1 + Sqr( x ) ) );
        };

        
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

    class ColorEncoding
        : public TaggedPointer<LinearColorEncoding, sRGBColorEncoding, GammaColorEncoding>
    {
    public:
        using TaggedPointer::TaggedPointer;
        // ColorEncoding Interface
        inline void ToLinear( pstdo::span<const uint8_t> vin, pstdo::span<Float> vout ) const;
        inline void FromLinear( pstdo::span<const Float> vin, pstdo::span<uint8_t> vout ) const;

        inline Float ToFloatLinear( Float v ) const;

        std::string ToString( ) const;

        static const ColorEncoding Get( const std::string& name, Allocator alloc );

        static ColorEncoding Linear;
        static ColorEncoding sRGB;

        static void Init( Allocator alloc );
    };

    class LinearColorEncoding
    {
    public:
        void ToLinear( pstdo::span<const uint8_t> vin, pstdo::span<Float> vout ) const
        {
            NDCHECK_EQ( vin.size( ), vout.size( ) );
            for ( size_t i = 0; i < vin.size( ); ++i )
                vout[ i ] = vin[ i ] / 255.f;
        }

        Float ToFloatLinear( Float v ) const 
        { 
            return v; 
        }

        void FromLinear( pstdo::span<const Float> vin, pstdo::span<uint8_t> vout ) const
        {
            NDCHECK_EQ( vin.size( ), vout.size( ) );
            for ( size_t i = 0; i < vin.size( ); ++i )
                vout[ i ] = uint8_t( Clamp( vin[ i ] * 255.f + 0.5f, 0, 255 ) );
        }

        std::string ToString( ) const 
        { 
            return "[ LinearColorEncoding ]"; 
        }
    };

    class sRGBColorEncoding
    {
    public:
        // sRGBColorEncoding Public Methods
        PBRTO_EXPORT void ToLinear( pstdo::span<const uint8_t> vin, pstdo::span<Float> vout ) const;
        PBRTO_EXPORT Float ToFloatLinear( Float v ) const;
        PBRTO_EXPORT void FromLinear( pstdo::span<const Float> vin, pstdo::span<uint8_t> vout ) const;

        std::string ToString( ) const { return "[ sRGBColorEncoding ]"; }
    };

    class GammaColorEncoding
    {
        Float gamma;
        pstdo::array<Float, 256> applyLUT;
        pstdo::array<Float, 1024> inverseLUT;
    public:
        PBRTO_EXPORT GammaColorEncoding( Float gamma );

        PBRTO_EXPORT void ToLinear( pstdo::span<const uint8_t> vin, pstdo::span<Float> vout ) const;
        PBRTO_EXPORT Float ToFloatLinear( Float v ) const;
        PBRTO_EXPORT void FromLinear( pstdo::span<const Float> vin, pstdo::span<uint8_t> vout ) const;

        PBRTO_EXPORT std::string ToString( ) const;

    private:
        
    };

    inline void ColorEncoding::ToLinear( pstdo::span<const uint8_t> vin, pstdo::span<Float> vout ) const
    {
        auto tolin = [ & ]( auto ptr ) { return ptr->ToLinear( vin, vout ); };
        Dispatch( tolin );
    }

    inline Float ColorEncoding::ToFloatLinear( Float v ) const
    {
        auto tfl = [ & ]( auto ptr ) { return ptr->ToFloatLinear( v ); };
        return Dispatch( tfl );
    }

    inline void ColorEncoding::FromLinear( pstdo::span<const Float> vin, pstdo::span<uint8_t> vout ) const
    {
        auto fl = [ & ]( auto ptr ) { return ptr->FromLinear( vin, vout ); };
        Dispatch( fl );
    }

    inline Float LinearToSRGB( Float value )
    {
        if ( value <= 0.0031308f )
            return 12.92f * value;
        // Minimax polynomial approximation from enoki's color.h.
        float sqrtValue = SafeSqrt( value );
        float p = EvaluatePolynomial( sqrtValue, -0.0016829072605308378f, 0.03453868659826638f,
            0.7642611304733891f, 2.0041169284241644f,
            0.7551545191665577f, -0.016202083165206348f );
        float q = EvaluatePolynomial( sqrtValue, 4.178892964897981e-7f,
            -0.00004375359692957097f, 0.03467195408529984f,
            0.6085338522168684f, 1.8970238036421054f, 1.f );
        return p / q * value;
    }

    inline uint8_t LinearToSRGB8( Float value, Float dither = 0 )
    {
        if ( value <= 0 )
            return 0;
        if ( value >= 1 )
            return 255;
        return Clamp( pstdo::round( 255.f * LinearToSRGB( value ) + dither ), 0, 255 );
    }

    inline Float SRGBToLinear( float value )
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

    PBRTO_EXPORT extern PBRT_CONST Float SRGBToLinearLUT[ 256 ];

    inline Float SRGB8ToLinear( uint8_t value )
    {
        return SRGBToLinearLUT[ value ];
    }

    // White Balance Definitions
    // clang-format off
    // These are the Bradford transformation matrices.
    const SquareMatrix<3> LMSFromXYZ( 0.8951, 0.2664, -0.1614,
        -0.7502, 1.7135, 0.0367,
        0.0389, -0.0685, 1.0296 );
    const SquareMatrix<3> XYZFromLMS( 0.986993, -0.147054, 0.159963,
        0.432305, 0.51836, 0.0492912,
        -0.00852866, 0.0400428, 0.968487 );
    // clang-format on

    inline SquareMatrix<3> WhiteBalance( Point2f srcWhite, Point2f targetWhite )
    {
        // Find LMS coefficients for source and target white
        XYZ srcXYZ = XYZ::FromxyY( srcWhite ), dstXYZ = XYZ::FromxyY( targetWhite );
        auto srcLMS = LMSFromXYZ * srcXYZ, dstLMS = LMSFromXYZ * dstXYZ;

        // Return white balancing matrix for source and target white
        SquareMatrix<3> LMScorrect = SquareMatrix<3>::Diag(
            dstLMS[ 0 ] / srcLMS[ 0 ], dstLMS[ 1 ] / srcLMS[ 1 ], dstLMS[ 2 ] / srcLMS[ 2 ] );
        return XYZFromLMS * LMScorrect * LMSFromXYZ;
    }

}

#endif