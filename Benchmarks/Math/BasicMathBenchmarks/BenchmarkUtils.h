#pragma once
#ifndef BENCHMARKUTILS_H_
#define BENCHMARKUTILS_H_

/*
   Copyright 2024 Espen Harlinn

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

#include <HCCMath.h>
#include <HCCVectorMath.h>
#include <pbrto/util/math.h>
#include <benchmark/benchmark.h>
#include <random>

//#define RUN_BASIC_MATH_BENCHMARKS
#define RUN_VECTOR2FLOAT_BENCHMARKS

using namespace Harlinn::Common::Core;

template<typename FloatT, size_t N >
struct RandomGenerator
{
    using FloatType = FloatT;
    std::array<FloatType, N> Values;
    size_t Counter = 0;
    RandomGenerator( FloatT lowerBound = -10000, FloatT upperBound = 10000 )
    {
        std::uniform_real_distribution<FloatType> unif( lowerBound, upperBound );
        std::default_random_engine re;
        for ( size_t i = 0; i < N; i++ )
        {
            Values[ i ] = unif( re );
        }
    }
    __forceinline FloatType operator( )( )
    {
        return Values[ Counter++ % N ];
    }
    void Reset( )
    {
        Counter = 0;
    }
};

constexpr size_t SampleCount = 64;



#endif
