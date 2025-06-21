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
#include <Harlinn/Math/Transformations.h>
#include <pbrto/util/transform.h>
#include <pbrto/util/NewTransform.h>

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

static void BenchmarkMathAffineTransformationPoint3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );
    
    Math::Point3f mathCameraPosition( 1.f, -1.5f, 2.f );
    Math::Point3f mathFocusPosition( 20.f, 20.f, 20.f );
    Math::Vector3f mathUpDirection( 0.f, 1.f, 0.f );

    Math::AffineTransformation affineTransformation = Math::AffineTransformation::LookAt( mathCameraPosition, mathFocusPosition, mathUpDirection );

    for ( auto _ : state )
    {
        Math::Point3f p1( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        Math::Point3f p1Transformed = affineTransformation( p1 );
        benchmark::DoNotOptimize( p1Transformed.z );
    }
}
BENCHMARK( BenchmarkMathAffineTransformationPoint3f );

static void BenchmarkPbrtTransformPoint3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    pbrt::Point3f pbrtCameraPosition( 1.f, -1.5f, 2.f );
    pbrt::Point3f pbrtFocusPosition( 20.f, 20.f, 20.f );
    pbrt::Vector3f pbrtUpDirection( 0.f, 1.f, 0.f );

    pbrt::Transform pbrtTransform = pbrt::LookAt( pbrtCameraPosition, pbrtFocusPosition, pbrtUpDirection );

    for ( auto _ : state )
    {
        pbrt::Point3f p1( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        pbrt::Point3f p1Transformed = pbrtTransform( p1 );
        benchmark::DoNotOptimize( p1Transformed.z );
    }
}
BENCHMARK( BenchmarkPbrtTransformPoint3f );

static void BenchmarkMathAffineTransformationNormal3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    Math::Point3f mathCameraPosition( 1.f, -1.5f, 2.f );
    Math::Point3f mathFocusPosition( 20.f, 20.f, 20.f );
    Math::Vector3f mathUpDirection( 0.f, 1.f, 0.f );

    Math::AffineTransformation affineTransformation = Math::AffineTransformation::LookAt( mathCameraPosition, mathFocusPosition, mathUpDirection );

    for ( auto _ : state )
    {
        Math::Normal3f p1( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        Math::Normal3f p1Transformed = affineTransformation( p1 );
        benchmark::DoNotOptimize( p1Transformed.z );
    }
}
BENCHMARK( BenchmarkMathAffineTransformationNormal3f );

static void BenchmarkPbrtTransformNormal3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    pbrt::Point3f pbrtCameraPosition( 1.f, -1.5f, 2.f );
    pbrt::Point3f pbrtFocusPosition( 20.f, 20.f, 20.f );
    pbrt::Vector3f pbrtUpDirection( 0.f, 1.f, 0.f );

    pbrt::Transform pbrtTransform = pbrt::LookAt( pbrtCameraPosition, pbrtFocusPosition, pbrtUpDirection );

    for ( auto _ : state )
    {
        pbrt::Normal3f p1( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        pbrt::Normal3f p1Transformed = pbrtTransform( p1 );
        benchmark::DoNotOptimize( p1Transformed.z );
    }
}
BENCHMARK( BenchmarkPbrtTransformNormal3f );

static void BenchmarkMathAffineTransformationVector3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    Math::Point3f mathCameraPosition( 1.f, -1.5f, 2.f );
    Math::Point3f mathFocusPosition( 20.f, 20.f, 20.f );
    Math::Vector3f mathUpDirection( 0.f, 1.f, 0.f );

    Math::AffineTransformation affineTransformation = Math::AffineTransformation::LookAt( mathCameraPosition, mathFocusPosition, mathUpDirection );

    for ( auto _ : state )
    {
        Math::Vector3f p1( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        Math::Vector3f p1Transformed = affineTransformation( p1 );
        benchmark::DoNotOptimize( p1Transformed.z );
    }
}
BENCHMARK( BenchmarkMathAffineTransformationVector3f );

static void BenchmarkPbrtTransformVector3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    pbrt::Point3f pbrtCameraPosition( 1.f, -1.5f, 2.f );
    pbrt::Point3f pbrtFocusPosition( 20.f, 20.f, 20.f );
    pbrt::Vector3f pbrtUpDirection( 0.f, 1.f, 0.f );

    pbrt::Transform pbrtTransform = pbrt::LookAt( pbrtCameraPosition, pbrtFocusPosition, pbrtUpDirection );

    for ( auto _ : state )
    {
        pbrt::Vector3f p1( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        pbrt::Vector3f p1Transformed = pbrtTransform( p1 );
        benchmark::DoNotOptimize( p1Transformed.z );
    }
}
BENCHMARK( BenchmarkPbrtTransformVector3f );


static void BenchmarkPbrtoRotateFromToVector3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    pbrto::Vector3f::Simd fromVector( 0.f, 1.f, 0.f );

    for ( auto _ : state )
    {
        pbrto::Vector3f::Simd toVector( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        pbrto::Transform transform( pbrto::RotateFromTo( fromVector, toVector ) );
        benchmark::DoNotOptimize( transform );
    }
}
BENCHMARK( BenchmarkPbrtoRotateFromToVector3f );

static void BenchmarkPbrtoRotateFromToOVector3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    pbrto::Vector3f fromVector( 0.f, 1.f, 0.f );

    for ( auto _ : state )
    {
        pbrto::Vector3f toVector( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        pbrto::Transform transform( pbrto::RotateFromToO( fromVector, toVector ) );
        benchmark::DoNotOptimize( transform );
    }
}
BENCHMARK( BenchmarkPbrtoRotateFromToOVector3f );


static void BenchmarkPbrtRotateFromToVector3f( benchmark::State& state )
{
    FloatM10To100Generator.Reset( );

    pbrt::Vector3f fromVector( 0.f, 1.f, 0.f );

    for ( auto _ : state )
    {
        pbrt::Vector3f toVector( FloatM10To100Generator( ), FloatM10To100Generator( ), FloatM10To100Generator( ) );
        pbrt::Transform transform( pbrt::RotateFromTo( fromVector, toVector ) );
        benchmark::DoNotOptimize( transform );
    }
}
BENCHMARK( BenchmarkPbrtRotateFromToVector3f );


#endif

