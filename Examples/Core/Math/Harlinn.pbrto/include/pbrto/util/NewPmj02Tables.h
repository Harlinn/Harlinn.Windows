#pragma once
#ifndef PBRTO_UTIL_NEWPMJ02TABLES_H_
#define PBRTO_UTIL_NEWPMJ02TABLES_H_

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
#include <pbrto/util/NewVecMath.h>

#include <cstdint>

namespace pbrto
{

    // PMJ02BN Table Declarations
    constexpr int nPMJ02bnSets = 5;
    constexpr int nPMJ02bnSamples = 65536;
    extern PBRT_CONST uint32_t pmj02bnSamples[ nPMJ02bnSets ][ nPMJ02bnSamples ][ 2 ];

    // PMJ02BN Table Inline Functions
    PBRT_CPU_GPU inline Point2f GetPMJ02BNSample( int setIndex, int sampleIndex );

    PBRT_CPU_GPU
        inline Point2f GetPMJ02BNSample( int setIndex, int sampleIndex )
    {
        setIndex %= nPMJ02bnSets;
        NDCHECK_LT( sampleIndex, nPMJ02bnSamples );
        sampleIndex %= nPMJ02bnSamples;

        // Convert from fixed-point.
#ifdef PBRT_IS_GPU_CODE
        return Point2f( pmj02bnSamples[ setIndex ][ sampleIndex ][ 0 ] * 0x1p-32f,
            pmj02bnSamples[ setIndex ][ sampleIndex ][ 1 ] * 0x1p-32f );
#else
    // Double precision is key here for the pixel sample sorting, but not
    // necessary otherwise.
        return Point2f( pmj02bnSamples[ setIndex ][ sampleIndex ][ 0 ] * 0x1p-32f,
            pmj02bnSamples[ setIndex ][ sampleIndex ][ 1 ] * 0x1p-32f );
#endif
    }

}

#endif
