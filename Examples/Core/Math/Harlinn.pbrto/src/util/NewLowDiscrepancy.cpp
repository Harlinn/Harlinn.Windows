#include "pch.h"

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

#include <pbrto/util/NewLowDiscrepancy.h>

#include <pbrto/util/NewMath.h>
#include <pbrto/util/NewPrimes.h>

namespace pbrto
{

    std::string DigitPermutation::ToString( ) const
    {
        std::string s = StringPrintf(
            "[ DigitPermitation base: %d nDigits: %d permutations: ", base, nDigits );
        for ( int digitIndex = 0; digitIndex < nDigits; ++digitIndex )
        {
            s += StringPrintf( "[%d] ( ", digitIndex );
            for ( int digitValue = 0; digitValue < base; ++digitValue )
            {
                s += StringPrintf( "%d", permutations[ digitIndex * base + digitValue ] );
                if ( digitValue != base - 1 )
                    s += ", ";
            }
            s += ") ";
        }

        return s + " ]";
    }

    std::string ToString( RandomizeStrategy r )
    {
        switch ( r )
        {
            case RandomizeStrategy::None:
                return "None";
            case RandomizeStrategy::PermuteDigits:
                return "PermuteDigits";
            case RandomizeStrategy::FastOwen:
                return "FastOwen";
            case RandomizeStrategy::Owen:
                return "Owen";
            default:
                NLOG_FATAL( "Unhandled RandomizeStrategy" );
                return "";
        }
    }

    // Low Discrepancy Function Definitions
    pstdo::vector<DigitPermutation>* ComputeRadicalInversePermutations( uint32_t seed,
        Allocator alloc )
    {
        pstdo::vector<DigitPermutation>* perms =
            alloc.new_object<pstdo::vector<DigitPermutation>>( alloc );
        perms->resize( PrimeTableSize );
        for ( int i = 0; i < PrimeTableSize; ++i )
            ( *perms )[ i ] = DigitPermutation( Primes[ i ], seed, alloc );
        return perms;
    }

}