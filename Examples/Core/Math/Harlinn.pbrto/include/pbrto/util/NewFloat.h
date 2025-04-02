#pragma once
#ifndef PBRT_UTIL_NEWFLOAT_H_
#define PBRT_UTIL_NEWFLOAT_H_

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
#include <pbrto/util/NewPStd.h>
#include <HCCMath.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <string>

namespace pbrto
{
    using namespace Harlinn::Common::Core;
    using namespace Harlinn::Common::Core::Math;

    // Floating-point Constants
    static constexpr Float Infinity = std::numeric_limits<Float>::infinity( );

    static constexpr Float MachineEpsilon = std::numeric_limits<Float>::epsilon( ) * 0.5f;

    static constexpr double DoubleOneMinusEpsilon = 0x1.fffffffffffffp-1;
    static constexpr float FloatOneMinusEpsilon = 0x1.fffffep-1;
#ifdef PBRT_FLOAT_AS_DOUBLE
    static constexpr double OneMinusEpsilon = DoubleOneMinusEpsilon;
#else
    static constexpr float OneMinusEpsilon = FloatOneMinusEpsilon;
#endif
    


    inline constexpr uint32_t FloatToBits( float f )
    {
        return std::bit_cast< uint32_t >( f );
    }

    inline constexpr float BitsToFloat( uint32_t ui )
    {
        return std::bit_cast< float >( ui );
    }

    inline constexpr int Exponent( float v )
    {
        return ( FloatToBits( v ) >> 23 ) - 127;
    }

    inline constexpr int Significand( float v )
    {
        return FloatToBits( v ) & ( ( 1 << 23 ) - 1 );
    }

    inline constexpr uint32_t SignBit( float v )
    {
        return FloatToBits( v ) & 0x80000000;
    }

    inline constexpr uint64_t FloatToBits( double f )
    {
        return std::bit_cast< uint64_t >( f );
    }

    inline constexpr double BitsToFloat( uint64_t ui )
    {
        return std::bit_cast< double >( ui );
    }

    inline constexpr float NextFloatUp( float v )
    {
        return Math::NextUp( v );
    }

    inline constexpr float NextFloatDown( float v )
    {
        return Math::NextDown( v );
    }

    inline constexpr Float gamma( int n )
    {
        return ( n * MachineEpsilon ) / ( 1 - n * MachineEpsilon );
    }

    inline constexpr Float AddRoundUp( Float a, Float b )
    {
        return Math::AddAdjustUp( a, b );
    }
    inline constexpr Float AddRoundDown( Float a, Float b )
    {
        return Math::AddAdjustDown( a, b );
    }

    inline constexpr Float SubRoundUp( Float a, Float b )
    {
        return Math::SubAdjustUp( a, b );
    }
    inline constexpr Float SubRoundDown( Float a, Float b )
    {
        return Math::SubAdjustDown( a, b );
    }

    inline constexpr Float MulRoundUp( Float a, Float b )
    {
        return Math::MulAdjustUp( a, b );
    }

    inline constexpr Float MulRoundDown( Float a, Float b )
    {
        return Math::MulAdjustDown( a, b );
    }

    inline constexpr Float DivRoundUp( Float a, Float b )
    {
        return Math::DivAdjustUp( a, b );
    }

    inline constexpr Float DivRoundDown( Float a, Float b )
    {
        return Math::DivAdjustDown( a, b );
    }

    inline constexpr Float SqrtRoundUp( Float a )
    {
        return Math::SqrtAdjustUp( a );
    }

    inline constexpr Float SqrtRoundDown( Float a )
    {
        return Math::SqrtAdjustDown( a );
    }

    inline constexpr Float FMARoundUp( Float a, Float b, Float c )
    {
        return Math::FMAAdjustUp( a, b, c );
    }

    inline constexpr Float FMARoundDown( Float a, Float b, Float c )
    {
        return Math::FMAAdjustDown( a, b, c );
    }

    inline constexpr double NextFloatUp( double v )
    {
        return Math::NextUp( v );
    }

    inline constexpr double NextFloatDown( double v )
    {
        return Math::NextDown( v );
    }

    inline constexpr int Exponent( double d )
    {
        return ( FloatToBits( d ) >> 52 ) - 1023;
    }

    inline constexpr uint64_t Significand( double d )
    {
        return FloatToBits( d ) & ( ( 1ull << 52 ) - 1 );
    }

    inline constexpr uint64_t SignBit( double v )
    {
        return FloatToBits( v ) & 0x8000000000000000;
    }

    inline constexpr double FlipSign( double a, double b )
    {
        return BitsToFloat( FloatToBits( a ) ^ SignBit( b ) );
    }

    

}  // namespace pbrto

#endif
