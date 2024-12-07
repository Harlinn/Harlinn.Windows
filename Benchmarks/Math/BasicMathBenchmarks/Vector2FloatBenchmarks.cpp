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

#include "BenchmarkUtils.h"
#include <pbrto/util/vecmath.h>

#ifdef RUN_VECTOR2FLOAT_BENCHMARKS
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

static void BenchmarkVector2Add( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = Math::Vector<float, 3>;
    DoubleGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Dot( Abs( Max( Ceil( -v1 ), Floor( v2 ) ) ), v2 ) );
    }
}
BENCHMARK( BenchmarkVector2Add );

static void BenchmarkPBRTVector2fAdd( benchmark::State& state )
{
    using namespace pbrt;
    using Vector = pbrt::Vector3f;
    DoubleGenerator.Reset( );


    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Dot( Abs( Max( Ceil( -v1 ), Floor( v2 ) ) ), v2 ) );
    }
}
BENCHMARK( BenchmarkPBRTVector2fAdd );

#endif
