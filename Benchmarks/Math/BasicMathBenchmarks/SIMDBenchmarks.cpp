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

#include "BenchmarkUtils.h"
#include <pbrto/util/vecmath.h>

using namespace Harlinn::Math;

namespace
{
    RandomGenerator<double, SampleCount> DoubleGenerator;
    RandomGenerator<float, SampleCount> FloatGenerator;
    RandomGenerator<double, SampleCount> DoubleAngleInDegreesGenerator( 0.0, 360.0 );
    RandomGenerator<float, SampleCount> FloatAngleInDegreesGenerator( 0.0f, 360.0f );
    RandomGenerator<double, SampleCount> DoubleAngleInRadiansGenerator( 0.0, M_PI * 2 );
    RandomGenerator<float, SampleCount> FloatAngleInRadiansGenerator( 0.0f, ( float )M_PI * 2 );

    RandomGenerator<double, SampleCount> DoubleZeroToOneGenerator( 0.0, 1.0 );
    RandomGenerator<float, SampleCount> FloatZeroToOneGenerator( 0.0f, 1.0f );

    RandomGenerator<double, SampleCount> DoubleMinusOneToOneGenerator( -1.0, 1.0 );
    RandomGenerator<float, SampleCount> FloatMinusOneToOneGenerator( -1.0f, 1.0f );
}

#ifdef RUN_SIMD_BENCHMARKS

static void BenchmarkFloatNextDown3A( benchmark::State& state )
{
    using Traits = SIMD::Traits<float, 3>;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f::Simd p( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        p.simd = Traits::NextDown( p.simd );
        benchmark::DoNotOptimize( p );
    }
}
BENCHMARK( BenchmarkFloatNextDown3A );

static void BenchmarkFloatNextDown3B( benchmark::State& state )
{
    using Traits = SIMD::Traits<float, 3>;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f::Simd p1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Math::Vector3f p2( p1 );
        
        p2.x = pbrt::NextFloatDown( p2.x );
        p2.y = pbrt::NextFloatDown( p2.y );
        p2.z = pbrt::NextFloatDown( p2.z );

        benchmark::DoNotOptimize( p2 );
    }
}
BENCHMARK( BenchmarkFloatNextDown3B );


static void BenchmarkPbrtFloatNextDown3( benchmark::State& state )
{
    using Traits = SIMD::Traits<float, 3>;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        pbrt::Point3f p( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        p.x = pbrt::NextFloatDown( p.x );
        p.y = pbrt::NextFloatDown( p.y );
        p.z = pbrt::NextFloatDown( p.z );
        benchmark::DoNotOptimize( p );
    }
}
BENCHMARK( BenchmarkPbrtFloatNextDown3 );



#endif

