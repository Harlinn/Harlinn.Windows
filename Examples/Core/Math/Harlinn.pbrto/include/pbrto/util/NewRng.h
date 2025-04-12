#pragma once
#ifndef PBRTO_UTIL_NEWRNG_H_
#define PBRTO_UTIL_NEWRNG_H_

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
#include <pbrto/util/NewFloat.h>
#include <pbrto/util/NewHash.h>
#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewPStd.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include <type_traits>

namespace pbrto
{

    // Random Number Declarations
    constexpr uint64_t PCG32_DEFAULT_STATE = 0x853c49e6748fea9bULL;
    constexpr uint64_t PCG32_DEFAULT_STREAM = 0xda3e39cb94b95bdbULL;
    constexpr uint64_t PCG32_MULT = 0x5851f42d4c957f2dULL;

// RNG Definition
    class RNG
    {
    public:
        // RNG Public Methods
        PBRT_CPU_GPU
            RNG( ) : state( PCG32_DEFAULT_STATE ), inc( PCG32_DEFAULT_STREAM ) {}
        PBRT_CPU_GPU
            RNG( uint64_t seqIndex, uint64_t offset ) { SetSequence( seqIndex, offset ); }
        PBRT_CPU_GPU
            RNG( uint64_t seqIndex ) { SetSequence( seqIndex ); }

        PBRT_CPU_GPU
            void SetSequence( uint64_t sequenceIndex, uint64_t offset );
        PBRT_CPU_GPU
            void SetSequence( uint64_t sequenceIndex )
        {
            SetSequence( sequenceIndex, MixBits( sequenceIndex ) );
        }

        template <typename T>
        PBRT_CPU_GPU T Uniform( );

        template <typename T>
        PBRT_CPU_GPU typename std::enable_if_t<std::is_integral_v<T>, T> Uniform( T b )
        {
            T threshold = ( ~b + 1u ) % b;
            while ( true )
            {
                T r = Uniform<T>( );
                if ( r >= threshold )
                    return r % b;
            }
        }

        PBRT_CPU_GPU
            void Advance( int64_t idelta );
        PBRT_CPU_GPU
            int64_t operator-( const RNG& other ) const;

        std::string ToString( ) const;

    private:
        // RNG Private Members
        uint64_t state, inc;
    };

    // RNG Inline Method Definitions
    template <typename T>
    PBRT_CPU_GPU inline T RNG::Uniform( )
    {
        return T::unimplemented;
    }

    template <>
    PBRT_CPU_GPU inline uint32_t RNG::Uniform<uint32_t>( );

    template <>
    PBRT_CPU_GPU inline uint32_t RNG::Uniform<uint32_t>( )
    {
        uint64_t oldstate = state;
        state = oldstate * PCG32_MULT + inc;
        uint32_t xorshifted = ( uint32_t )( ( ( oldstate >> 18u ) ^ oldstate ) >> 27u );
        uint32_t rot = ( uint32_t )( oldstate >> 59u );
        return ( xorshifted >> rot ) | ( xorshifted << ( ( ~rot + 1u ) & 31 ) );
    }

    template <>
    PBRT_CPU_GPU inline uint64_t RNG::Uniform<uint64_t>( )
    {
        uint64_t v0 = Uniform<uint32_t>( ), v1 = Uniform<uint32_t>( );
        return ( v0 << 32 ) | v1;
    }

    template <>
    PBRT_CPU_GPU inline int32_t RNG::Uniform<int32_t>( )
    {
        // https://stackoverflow.com/a/13208789
        uint32_t v = Uniform<uint32_t>( );
        if ( v <= ( uint32_t )std::numeric_limits<int32_t>::max( ) )
            return int32_t( v );
        NDCHECK_GE( v, ( uint32_t )std::numeric_limits<int32_t>::min( ) );
        return int32_t( v - std::numeric_limits<int32_t>::min( ) ) +
            std::numeric_limits<int32_t>::min( );
    }

    template <>
    PBRT_CPU_GPU inline int64_t RNG::Uniform<int64_t>( )
    {
        // https://stackoverflow.com/a/13208789
        uint64_t v = Uniform<uint64_t>( );
        if ( v <= ( uint64_t )std::numeric_limits<int64_t>::max( ) )
            // Safe to type convert directly.
            return int64_t( v );
        NDCHECK_GE( v, ( uint64_t )std::numeric_limits<int64_t>::min( ) );
        return int64_t( v - std::numeric_limits<int64_t>::min( ) ) +
            std::numeric_limits<int64_t>::min( );
    }

    PBRT_CPU_GPU inline void RNG::SetSequence( uint64_t sequenceIndex, uint64_t seed )
    {
        state = 0u;
        inc = ( sequenceIndex << 1u ) | 1u;
        Uniform<uint32_t>( );
        state += seed;
        Uniform<uint32_t>( );
    }

    template <>
    PBRT_CPU_GPU inline float RNG::Uniform<float>( )
    {
        return std::min<float>( OneMinusEpsilon, Uniform<uint32_t>( ) * 0x1p-32f );
    }

    template <>
    PBRT_CPU_GPU inline double RNG::Uniform<double>( )
    {
        return std::min<double>( OneMinusEpsilon, Uniform<uint64_t>( ) * 0x1p-64 );
    }

    PBRT_CPU_GPU inline void RNG::Advance( int64_t idelta )
    {
        uint64_t curMult = PCG32_MULT, curPlus = inc, accMult = 1u;
        uint64_t accPlus = 0u, delta = ( uint64_t )idelta;
        while ( delta > 0 )
        {
            if ( delta & 1 )
            {
                accMult *= curMult;
                accPlus = accPlus * curMult + curPlus;
            }
            curPlus = ( curMult + 1 ) * curPlus;
            curMult *= curMult;
            delta /= 2;
        }
        state = accMult * state + accPlus;
    }

    PBRT_CPU_GPU
        inline int64_t RNG::operator-( const RNG& other ) const
    {
        NCHECK_EQ( inc, other.inc );
        uint64_t curMult = PCG32_MULT, curPlus = inc, curState = other.state;
        uint64_t theBit = 1u, distance = 0u;
        while ( state != curState )
        {
            if ( ( state & theBit ) != ( curState & theBit ) )
            {
                curState = curState * curMult + curPlus;
                distance |= theBit;
            }
            NCHECK_EQ( state & theBit, curState & theBit );
            theBit <<= 1;
            curPlus = ( curMult + 1ULL ) * curPlus;
            curMult *= curMult;
        }
        return ( int64_t )distance;
    }

}

#endif
