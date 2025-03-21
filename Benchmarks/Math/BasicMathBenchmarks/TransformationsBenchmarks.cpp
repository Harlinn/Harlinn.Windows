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

#include "BenchmarkUtils.h"
#include <HCCTransformations.h>
#include <pbrto/util/transform.h>

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

    RandomGenerator<float, SampleCount> FloatPositiveGenerator( 0.0f );
    RandomGenerator<float, SampleCount> FloatM10To100Generator( -10.0f, 100.0f );
    RandomGenerator<float, SampleCount> Float0To10Generator( 0.0f, 10.0f );
    RandomGenerator<float, SampleCount> Float1To10Generator( 1.0f, 10.0f );
    RandomGenerator<float, SampleCount> Float1To100Generator( 1.0f, 100.0f );


}

#ifdef RUN_TRANSFORMATIONS_BENCHMARKS

static void BenchmarkMathAffineTransformation( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );
    
    Math::AffineTransformation affineTransformation = Math::AffineTransformation::Scale( 1.5f, 2.5f, 3.f );

    for ( auto _ : state )
    {
        Math::Point3f p1( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        Math::Point3f p1Transformed = affineTransformation( p1 );
        benchmark::DoNotOptimize( p1Transformed.z );
    }
}
BENCHMARK( BenchmarkMathAffineTransformation );

static void BenchmarkPbrtTransform( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    pbrt::Transform pbrtTransform = pbrt::Scale( 1.5f, 2.5f, 3.f );

    for ( auto _ : state )
    {
        pbrt::Point3f p1( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        pbrt::Point3f p1Transformed = pbrtTransform( p1 );
        benchmark::DoNotOptimize( p1Transformed.z );
    }
}
BENCHMARK( BenchmarkPbrtTransform );



#endif

