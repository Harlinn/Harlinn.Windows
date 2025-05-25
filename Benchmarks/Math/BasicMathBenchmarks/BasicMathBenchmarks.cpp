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
    RandomGenerator<float, SampleCount> DoubleM10To100Generator( -10.0f, 100.0f );
    RandomGenerator<float, SampleCount> FloatM10To100Generator( -10.0f, 100.0f );
    RandomGenerator<float, SampleCount> Float0To10Generator( 0.0f, 10.0f );
    RandomGenerator<float, SampleCount> Float1To10Generator( 1.0f, 10.0f );
    RandomGenerator<float, SampleCount> Float1To100Generator( 1.0f, 100.0f );
    

}

#ifdef RUN_BASIC_MATH_BENCHMARKS
static void BenchmarkDoubleGenerator( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( DoubleGenerator() );
    }
}
BENCHMARK( BenchmarkDoubleGenerator );

static void BenchmarkFloatGenerator( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( FloatGenerator( ) );
    }
}
BENCHMARK( BenchmarkFloatGenerator );


static void BenchmarkMathDoubleIsSameValue( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsSameValue( DoubleGenerator( ), 1.0 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleIsSameValue );

static void BenchmarkMathFloatIsSameValue( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsSameValue( FloatGenerator( ), 1.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatIsSameValue );


static void BenchmarkMathDoubleIsZero( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsZero( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleIsZero );

static void BenchmarkMathFloatIsZero( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsZero( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIsZero );

static void BenchmarkMathDoubleIsNaN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleIsNaN );

static void BenchmarkOpenLibMDoubleIsNaN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::isnan( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleIsNaN );

static void BenchmarkStdDoubleIsNaN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::isnan( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleIsNaN );

static void BenchmarkPbrtDoubleIsNaN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::IsNaN( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtDoubleIsNaN );


static void BenchmarkMathFloatIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIsNaN );

static void BenchmarkMathVector2fIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fIsNaN );

static void BenchmarkMathVector2fSimdIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdIsNaN );


static void BenchmarkMathVector3fIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fIsNaN );

static void BenchmarkMathVector3fSimdIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdIsNaN );


static void BenchmarkMathVector4fIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fIsNaN );

static void BenchmarkMathVector4fSimdIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdIsNaN );



static void BenchmarkOpenLibMFloatIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::__isnanf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatIsNaN );

static void BenchmarkStdFloatIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::isnan( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatIsNaN );

static void BenchmarkPbrtFloatIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::IsNaN( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIsNaN );


static void BenchmarkMathDoubleSignum( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::signum( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleSignum );

template <typename T> int NaiveSignum( T val )
{
    return ( T( 0 ) < val ) - ( val < T( 0 ) );
}

static void BenchmarkNaiveDoubleSignum( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( NaiveSignum( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkNaiveDoubleSignum );

static void BenchmarkMathFloatSignum( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::signum( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSignum );

static void BenchmarkNaiveFloatSignum( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( NaiveSignum( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkNaiveFloatSignum );

static void BenchmarkMathDoubleDeg2Rad( benchmark::State& state )
{
    DoubleAngleInDegreesGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Deg2Rad( DoubleAngleInDegreesGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleDeg2Rad );

static void BenchmarkPbrtDoubleRadians( benchmark::State& state )
{
    DoubleAngleInDegreesGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Radians( DoubleAngleInDegreesGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtDoubleRadians );


static void BenchmarkMathFloatDeg2Rad( benchmark::State& state )
{
    FloatAngleInDegreesGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Deg2Rad( FloatAngleInDegreesGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatDeg2Rad );

static void BenchmarkPbrtFloatRadians( benchmark::State& state )
{
    FloatAngleInDegreesGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Radians( FloatAngleInDegreesGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatRadians );


static void BenchmarkMathDoubleRad2Deg( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Rad2Deg( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleRad2Deg );

static void BenchmarkPbrtDoubleDegrees( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Degrees( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtDoubleDegrees );


static void BenchmarkMathFloatRad2Deg( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Rad2Deg( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatRad2Deg );

static void BenchmarkPbrtFloatDegrees( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Degrees( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatDegrees );


static void BenchmarkMathDoubleNextAfter( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextAfter( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleNextAfter );

static void BenchmarkOpenLibMDoubleNextAfter( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::nextafter( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleNextAfter );

static void BenchmarkStdDoubleNextAfter( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleNextAfter );

static void BenchmarkMathFloatNextAfter( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextAfter( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatNextAfter );


static void BenchmarkOpenLibMFloatNextAfter( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::nextafterf( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatNextAfter );

static void BenchmarkStdFloatNextAfter( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( FloatGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkStdFloatNextAfter );


static void BenchmarkMathDoubleSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleSqrt );


static void BenchmarkOpenLibMDoubleSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::sqrt( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleSqrt );


static void BenchmarkStdDoubleSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sqrt( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleSqrt );

static void BenchmarkPbrtDoubleSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::sqrt( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtDoubleSqrt );

static void BenchmarkMathFloatSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSqrt );

static void BenchmarkMathVector2fSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSqrt );

static void BenchmarkMathVector2fSimdSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdSqrt );


static void BenchmarkMathVector3fSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSqrt );

static void BenchmarkMathVector3fSimdSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdSqrt );


static void BenchmarkMathVector4fSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSqrt );

static void BenchmarkMathVector4fSimdSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdSqrt );



static void BenchmarkOpenLibMFloatSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::sqrtf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatSqrt );


static void BenchmarkStdFloatSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sqrt( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatSqrt );

static void BenchmarkPbrtFloatSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::sqrt( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSqrt );


static void BenchmarkMathDoubleNextDown( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleNextDown );

static void BenchmarkStdDoubleNextDown( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( DoubleGenerator( ), -std::numeric_limits<double>::infinity( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleNextDown );

static void BenchmarkMathFloatNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatNextDown );

static void BenchmarkMathVector2fNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fNextDown );

static void BenchmarkMathVector2fSimdNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdNextDown );


static void BenchmarkMathVector3fNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fNextDown );

static void BenchmarkMathVector3fSimdNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdNextDown );

static void BenchmarkMathVector4fNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fNextDown );

static void BenchmarkMathVector4fSimdNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdNextDown );



static void BenchmarkStdFloatNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( FloatGenerator( ), -std::numeric_limits<float>::infinity( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatNextDown );

static void BenchmarkPbrtFloatNextFloatDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::NextFloatDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatNextFloatDown );


static void BenchmarkMathDoubleNextUp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleNextUp );

static void BenchmarkStdDoubleNextUp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( DoubleGenerator( ), std::numeric_limits<double>::infinity( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleNextUp );


static void BenchmarkMathFloatNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatNextUp );

static void BenchmarkMathVector2fNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fNextUp );

static void BenchmarkMathVector2fSimdNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdNextUp );


static void BenchmarkMathVector3fNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fNextUp );

static void BenchmarkMathVector3fSimdNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdNextUp );

static void BenchmarkMathVector4fNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fNextUp );

static void BenchmarkMathVector4fSimdNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdNextUp );




static void BenchmarkStdFloatNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( FloatGenerator( ), std::numeric_limits<float>::infinity( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatNextUp );

static void BenchmarkPbrtFloatNextFloatUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::NextFloatUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatNextFloatUp );


static void BenchmarkMathDoubleIsInf( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleIsInf );

static void BenchmarkOpenLibMDoubleIsInf( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::isinf( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleIsInf );

static void BenchmarkStdDoubleIsInf( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::isinf( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleIsInf );

static void BenchmarkMathFloatIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIsInf );

static void BenchmarkMathVector2fIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fIsInf );


static void BenchmarkMathVector2fSimdIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdIsInf );


static void BenchmarkMathVector3fIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fIsInf );


static void BenchmarkMathVector3fSimdIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdIsInf );

static void BenchmarkMathVector4fIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fIsInf );


static void BenchmarkMathVector4fSimdIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdIsInf );



static void BenchmarkOpenLibMFloatIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::__isinff( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatIsInf );

static void BenchmarkStdFloatIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::isinf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatIsInf );

static void BenchmarkPbrtFloatIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::IsInf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIsInf );

static void BenchmarkMathDoubleAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleAbs );

static void BenchmarkMathDoubleFastAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastAbs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleFastAbs );

static void BenchmarkMathInternalDoubleAbsImpl( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::AbsImpl( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathInternalDoubleAbsImpl );


static void BenchmarkOpenLibMDoubleAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fabs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleAbs );

static void BenchmarkStdDoubleAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::abs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleAbs );

static void BenchmarkPbrtDoubleAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::abs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtDoubleAbs );


static void BenchmarkMathFloatAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatAbs );

static void BenchmarkMathVector2fAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fAbs );

static void BenchmarkMathVector2fSimdAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdAbs );


static void BenchmarkMathVector3fAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fAbs );

static void BenchmarkMathVector3fSimdAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdAbs );

static void BenchmarkMathVector4fAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fAbs );

static void BenchmarkMathVector4fSimdAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdAbs );




static void BenchmarkMathFloatFastAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastAbs( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatFastAbs );

static void BenchmarkMathVector2fFastAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastAbs( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fFastAbs );

static void BenchmarkMathVector2fSimdFastAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastAbs( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdFastAbs );


static void BenchmarkMathVector3fFastAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastAbs( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fFastAbs );

static void BenchmarkMathVector3fSimdFastAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastAbs( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdFastAbs );

static void BenchmarkMathVector4fFastAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastAbs( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fFastAbs );

static void BenchmarkMathVector4fSimdFastAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastAbs( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdFastAbs );


static void BenchmarkMathInternalFloatAbsImpl( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::AbsImpl( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathInternalFloatAbsImpl );

static void BenchmarkOpenLibMFloatAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fabsf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatAbs );


static void BenchmarkStdFloatAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::abs( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatAbs );

static void BenchmarkPbrtFloatAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::abs( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatAbs );


static void BenchmarkMathDoubleSignBit( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SignBit( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleSignBit );

static void BenchmarkOpenLibMDoubleSignBit( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::signbit( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleSignBit );

static void BenchmarkStdDoubleSignBit( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::signbit( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleSignBit );

static void BenchmarkMathFloatSignBit( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SignBit( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSignBit );

static void BenchmarkOpenLibMFloatSignBit( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::signbit( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatSignBit );

static void BenchmarkStdFloatSignBit( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::signbit( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatSignBit );

static void BenchmarkMathDoubleFRExp( benchmark::State& state )
{
    int exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FRExp( DoubleGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkMathDoubleFRExp );

static void BenchmarkOpenLibMDoubleFRExp( benchmark::State& state )
{
    int exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::frexp( DoubleGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleFRExp );

static void BenchmarkStdDoubleFRExp( benchmark::State& state )
{
    int exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::frexp( DoubleGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkStdDoubleFRExp );

static void BenchmarkMathFloatFRExp( benchmark::State& state )
{
    int exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FRExp( FloatGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkMathFloatFRExp );


static void BenchmarkOpenLibMFloatFRExp( benchmark::State& state )
{
    int exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::frexpf( FloatGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatFRExp );

static void BenchmarkStdFloatFRExp( benchmark::State& state )
{
    int exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::frexp( FloatGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkStdFloatFRExp );

static void BenchmarkMathDoubleModF( benchmark::State& state )
{
    double exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ModF( DoubleGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkMathDoubleModF );

static void BenchmarkOpenLibMDoubleModF( benchmark::State& state )
{
    double exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::modf( DoubleGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleModF );

static void BenchmarkStdDoubleModF( benchmark::State& state )
{
    double exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::modf( DoubleGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkStdDoubleModF );

static void BenchmarkMathFloatingPointDoubleModF( benchmark::State& state )
{
    double exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<double>::ModF( DoubleGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointDoubleModF );


static void BenchmarkMathFloatModF( benchmark::State& state )
{
    float exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ModF( FloatGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkMathFloatModF );



static void BenchmarkOpenLibMFloatModF( benchmark::State& state )
{
    float exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::modff( FloatGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatModF );

static void BenchmarkMathFloatingPointFloatModF( benchmark::State& state )
{
    float exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<float>::ModF( FloatGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointFloatModF );


static void BenchmarkStdFloatModF( benchmark::State& state )
{
    float exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::modf( FloatGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkStdFloatModF );

static void BenchmarkMathDoubleMin( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleMin );

static void BenchmarkOpenLibMDoubleMin( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmin( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleMin );

static void BenchmarkStdDoubleMin( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::min( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleMin );

static void BenchmarkMathFloatMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatMin );

static void BenchmarkMathVector2fMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( Math::Vector2f( FloatGenerator( ) ), Math::Vector2f( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fMin );

static void BenchmarkMathVector2fSimdMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( Math::Vector2f::Simd( FloatGenerator( ) ), Math::Vector2f::Simd( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdMin );

static void BenchmarkMathVector3fMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( Math::Vector3f(FloatGenerator( )), Math::Vector3f( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fMin );

static void BenchmarkMathVector3fSimdMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( Math::Vector3f::Simd( FloatGenerator( ) ), Math::Vector3f::Simd( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdMin );

static void BenchmarkMathVector4fMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( Math::Vector4f( FloatGenerator( ) ), Math::Vector4f( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fMin );

static void BenchmarkMathVector4fSimdMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( Math::Vector4f::Simd( FloatGenerator( ) ), Math::Vector4f::Simd( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdMin );



static void BenchmarkOpenLibMFloatMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fminf( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatMin );

static void BenchmarkStdFloatMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::min( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkStdFloatMin );

static void BenchmarkMathDoubleMax( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleMax );

static void BenchmarkOpenLibMDoubleMax( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmax( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleMax );

static void BenchmarkStdDoubleMax( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::max( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleMax );

static void BenchmarkMathFloatMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatMax );

static void BenchmarkMathVector2fMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( Math::Vector2f( FloatGenerator( ) ), Math::Vector2f( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fMax );

static void BenchmarkMathVector2fSimdMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( Math::Vector2f::Simd( FloatGenerator( ) ), Math::Vector2f::Simd( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdMax );


static void BenchmarkMathVector3fMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( Math::Vector3f( FloatGenerator( ) ), Math::Vector3f( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fMax );

static void BenchmarkMathVector3fSimdMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( Math::Vector3f::Simd( FloatGenerator( ) ), Math::Vector3f::Simd( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdMax );

static void BenchmarkMathVector4fMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( Math::Vector4f( FloatGenerator( ) ), Math::Vector4f( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fMax );

static void BenchmarkMathVector4fSimdMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( Math::Vector4f::Simd( FloatGenerator( ) ), Math::Vector4f::Simd( 0.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdMax );


static void BenchmarkOpenLibMFloatMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmaxf( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatMax );

static void BenchmarkStdFloatMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::max( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkStdFloatMax );


static void BenchmarkMathDoubleTrunc( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleTrunc );

static void BenchmarkOpenLibMDoubleTrunc( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::trunc( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleTrunc );

static void BenchmarkMathFloatingPointDoubleTrunc( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::FloatingPoint<double> fp( DoubleGenerator( ) );
        benchmark::DoNotOptimize( fp.Trunc(  ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointDoubleTrunc );


static void BenchmarkStdDoubleTrunc( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::trunc( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleTrunc );

static void BenchmarkMathFloatTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatTrunc );

static void BenchmarkMathVector2fTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fTrunc );

static void BenchmarkMathVector2fSimdTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdTrunc );


static void BenchmarkMathVector3fTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fTrunc );

static void BenchmarkMathVector3fSimdTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdTrunc );

static void BenchmarkMathVector4fTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fTrunc );

static void BenchmarkMathVector4fSimdTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdTrunc );


static void BenchmarkOpenLibMFloatTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::truncf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatTrunc );

static void BenchmarkMathFloatingPointFloatTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::FloatingPoint<float> fp( FloatGenerator( ) );
        benchmark::DoNotOptimize( fp.Trunc( ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointFloatTrunc );


static void BenchmarkStdFloatTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::trunc( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatTrunc );

static void BenchmarkMathDoubleFloor( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleFloor );

static void BenchmarkOpenLibMDoubleFloor( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::floor( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleFloor );

static void BenchmarkMathFloatingPointDoubleFloor( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<double>::Floor( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointDoubleFloor );


static void BenchmarkStdDoubleFloor( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::floor( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleFloor );

static void BenchmarkMathFloatFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatFloor );

static void BenchmarkMathVector2fFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fFloor );

static void BenchmarkMathVector2fSimdFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdFloor );


static void BenchmarkMathVector3fFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fFloor );

static void BenchmarkMathVector3fSimdFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdFloor );

static void BenchmarkMathVector4fFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fFloor );

static void BenchmarkMathVector4fSimdFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdFloor );



static void BenchmarkOpenLibMFloatFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::floorf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatFloor );

static void BenchmarkMathFloatingPointFloatFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<float>::Floor( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointFloatFloor );


static void BenchmarkStdFloatFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::floor( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatFloor );


static void BenchmarkMathDoubleCeil( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleCeil );

static void BenchmarkOpenLibMDoubleCeil( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::ceil( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleCeil );

static void BenchmarkMathFloatingPointDoubleCeil( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<double>::Ceil( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointDoubleCeil );


static void BenchmarkStdDoubleCeil( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::ceil( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleCeil );

static void BenchmarkMathFloatCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatCeil );

static void BenchmarkMathVector2fCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fCeil );

static void BenchmarkMathVector2fSimdCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdCeil );


static void BenchmarkMathVector3fCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fCeil );

static void BenchmarkMathVector3fSimdCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdCeil );

static void BenchmarkMathVector4fCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fCeil );

static void BenchmarkMathVector4fSimdCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdCeil );



static void BenchmarkOpenLibMFloatCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::ceilf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatCeil );

static void BenchmarkMathFloatingPointFloatCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<float>::Ceil( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointFloatCeil );

static void BenchmarkStdFloatCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::ceil( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatCeil );

static void BenchmarkMathDoubleRound( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleRound );

static void BenchmarkOpenLibMDoubleRound( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::round( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleRound );

static void BenchmarkMathFloatingPointDoubleRound( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<double>::Round( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointDoubleRound );


static void BenchmarkStdDoubleRound( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::round( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleRound );

static void BenchmarkMathFloatRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatRound );

static void BenchmarkMathVector2fRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fRound );

static void BenchmarkMathVector2fSimdRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdRound );


static void BenchmarkMathVector3fRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fRound );

static void BenchmarkMathVector3fSimdRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdRound );

static void BenchmarkMathVector4fRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fRound );

static void BenchmarkMathVector4fSimdRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdRound );



static void BenchmarkOpenLibMFloatRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::roundf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatRound );


static void BenchmarkMathFloatingPointFloatRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<float>::Round( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatingPointFloatRound );


static void BenchmarkStdFloatRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::round( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatRound );

static void BenchmarkMathDoubleClamp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( DoubleGenerator( ), -1000.0, 1000.0 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleClamp );

static void BenchmarkStdDoubleClamp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::clamp( DoubleGenerator( ), -1000.0, 1000.0 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleClamp );

static void BenchmarkMathFloatClamp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( FloatGenerator( ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatClamp );

static void BenchmarkMathVector2fClamp1( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector2f( FloatGenerator( ) ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector2fClamp1 );

static void BenchmarkMathVector2fSimdClamp1( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector2f::Simd( FloatGenerator( ) ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdClamp1 );


static void BenchmarkMathVector2fClamp2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector2f( FloatGenerator( ) ), Math::Vector2f( -1000.0f ), Math::Vector2f( 1000.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fClamp2 );

static void BenchmarkMathVector2fSimdClamp2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector2f::Simd( FloatGenerator( ) ), Math::Vector2f::Simd( -1000.0f ), Math::Vector2f::Simd( 1000.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdClamp2 );



//
static void BenchmarkMathVector3fClamp1( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector3f( FloatGenerator( ) ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector3fClamp1 );

static void BenchmarkMathVector3fSimdClamp1( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector3f::Simd( FloatGenerator( ) ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdClamp1 );


static void BenchmarkMathVector3fClamp2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector3f( FloatGenerator( ) ), Math::Vector3f( -1000.0f ), Math::Vector3f( 1000.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fClamp2 );

static void BenchmarkMathVector3fSimdClamp2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector3f::Simd( FloatGenerator( ) ), Math::Vector3f::Simd( -1000.0f ), Math::Vector3f::Simd( 1000.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdClamp2 );

//
static void BenchmarkMathVector4fClamp1( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector4f( FloatGenerator( ) ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector4fClamp1 );

static void BenchmarkMathVector4fSimdClamp1( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector4f::Simd( FloatGenerator( ) ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdClamp1 );


static void BenchmarkMathVector4fClamp2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector4f( FloatGenerator( ) ), Math::Vector4f( -1000.0f ), Math::Vector4f( 1000.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fClamp2 );

static void BenchmarkMathVector4fSimdClamp2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( Math::Vector4f::Simd( FloatGenerator( ) ), Math::Vector4f::Simd( -1000.0f ), Math::Vector4f::Simd( 1000.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdClamp2 );

static void BenchmarkStdFloatClamp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::clamp( FloatGenerator( ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkStdFloatClamp );

static void BenchmarkPbrtFloatClamp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Clamp( FloatGenerator( ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatClamp );

static void BenchmarkMathDoubleLerp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0, 10.0, DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleLerp );


static void BenchmarkMathInternalDoubleLerpImpl( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::LerpImpl( 5.0, 10.0, DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathInternalDoubleLerpImpl );


static void BenchmarkStdDoubleLerp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::lerp( 5.0, 10.0, DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleLerp );

static void BenchmarkMathFloatLerp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0f, 10.0f, FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatLerp );

static void BenchmarkMathVector2fLerp11( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0f, 10.0f, Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fLerp11 );

static void BenchmarkMathVector2fSimdLerp11( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0f, 10.0f, Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdLerp11 );


static void BenchmarkMathVector3fLerp11( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0f, 10.0f, Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fLerp11 );

static void BenchmarkMathVector3fSimdLerp11( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0f, 10.0f, Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdLerp11 );

static void BenchmarkMathVector4fLerp11( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0f, 10.0f, Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fLerp11 );

static void BenchmarkMathVector4fSimdLerp11( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0f, 10.0f, Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdLerp11 );


static void BenchmarkMathFloatLerp2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp2( FloatGenerator( ), 5.0f, 10.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatLerp2 );


static void BenchmarkMathVector2fLerp21( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp2( Math::Vector2f( FloatGenerator( ) ), 5.0f, 10.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector2fLerp21 );

static void BenchmarkMathVector2fSimdLerp21( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp2( Math::Vector2f::Simd( FloatGenerator( ) ), 5.0f, 10.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdLerp21 );

static void BenchmarkMathVector3fLerp21( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp2( Math::Vector3f( FloatGenerator( ) ), 5.0f, 10.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector3fLerp21 );

static void BenchmarkMathVector3fSimdLerp21( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp2( Math::Vector3f::Simd( FloatGenerator( ) ), 5.0f, 10.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdLerp21 );

static void BenchmarkMathVector4fLerp21( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp2( Math::Vector4f( FloatGenerator( ) ), 5.0f, 10.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector4fLerp21 );

static void BenchmarkMathVector4fSimdLerp21( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp2( Math::Vector4f::Simd( FloatGenerator( ) ), 5.0f, 10.0f ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdLerp21 );

static void BenchmarkMathVector2fLerp22( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector2f vec1( v1 );
    Math::Vector2f vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );

        benchmark::DoNotOptimize( Math::Lerp2( v3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector2fLerp22 );

static void BenchmarkMathVector2fSimdLerp22( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );

    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector2f::Simd vec1( v1 );
    Math::Vector2f::Simd vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );

        benchmark::DoNotOptimize( Math::Lerp2( v3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdLerp22 );


static void BenchmarkMathVector3fLerp22( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector3f vec1( v1 );
    Math::Vector3f vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        
        benchmark::DoNotOptimize( Math::Lerp2( v3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector3fLerp22 );

static void BenchmarkMathVector3fSimdLerp22( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );

    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector3f::Simd vec1( v1 );
    Math::Vector3f::Simd vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        
        benchmark::DoNotOptimize( Math::Lerp2( v3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdLerp22 );



static void BenchmarkPbrtVector3fLerp22( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    pbrt::Vector3f vec1( v1, v1, v1 );
    pbrt::Vector3f vec2( v2, v2, v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        
        benchmark::DoNotOptimize( pbrt::Lerp( v3, vec1, vec2 ) );

    }
}
BENCHMARK( BenchmarkPbrtVector3fLerp22 );

static void BenchmarkMathVector4fLerp22( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector4f vec1( v1 );
    Math::Vector4f vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );

        benchmark::DoNotOptimize( Math::Lerp2( v3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector4fLerp22 );

static void BenchmarkMathVector4fSimdLerp22( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );

    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector4f::Simd vec1( v1 );
    Math::Vector4f::Simd vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );

        benchmark::DoNotOptimize( Math::Lerp2( v3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdLerp22 );


static void BenchmarkMathVector2fLerp23( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector2f vec1( v1 );
    Math::Vector2f vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        Math::Vector2f vec3( v3 );

        benchmark::DoNotOptimize( Math::Lerp2( vec3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector2fLerp23 );

static void BenchmarkMathVector2fSimdLerp23( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector2f::Simd vec1( v1 );
    Math::Vector2f::Simd vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        Math::Vector2f::Simd vec3( v3 );

        benchmark::DoNotOptimize( Math::Lerp2( vec3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdLerp23 );



static void BenchmarkMathVector3fLerp23( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector3f vec1( v1 );
    Math::Vector3f vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        Math::Vector3f vec3( v3 );

        benchmark::DoNotOptimize( Math::Lerp2( vec3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector3fLerp23 );

static void BenchmarkMathVector3fSimdLerp23( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector3f::Simd vec1( v1 );
    Math::Vector3f::Simd vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        Math::Vector3f::Simd vec3( v3 );

        benchmark::DoNotOptimize( Math::Lerp2( vec3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdLerp23 );


static void BenchmarkMathVector4fLerp23( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector4f vec1( v1 );
    Math::Vector4f vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        Math::Vector4f vec3( v3 );

        benchmark::DoNotOptimize( Math::Lerp2( vec3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector4fLerp23 );

static void BenchmarkMathVector4fSimdLerp23( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    Math::Vector4f::Simd vec1( v1 );
    Math::Vector4f::Simd vec2( v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );
        Math::Vector4f::Simd vec3( v3 );

        benchmark::DoNotOptimize( Math::Lerp2( vec3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdLerp23 );


static void BenchmarkPbrtVector2fLerp22( benchmark::State& state )
{
    FloatGenerator.Reset( );
    auto v1 = FloatGenerator( );
    auto v2 = FloatGenerator( );
    if ( v1 > v2 )
    {
        std::swap( v1, v2 );
    }
    pbrt::Vector2f vec1( v1, v1 );
    pbrt::Vector2f vec2( v2, v2 );

    for ( auto _ : state )
    {
        auto v3 = FloatGenerator( );

        benchmark::DoNotOptimize( pbrt::Lerp( v3, vec1, vec2 ) );
    }
}
BENCHMARK( BenchmarkPbrtVector2fLerp22 );




static void BenchmarkMathInternalFloatLerpImpl( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::LerpImpl( 5.0f, 10.0f, FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathInternalFloatLerpImpl );

static void BenchmarkStdFloatLerp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::lerp( 5.0f, 10.0f, FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatLerp );

static void BenchmarkPbrtFloatLerp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Lerp( 5.0f, 10.0f, FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatLerp );


static void BenchmarkMathDoubleCopySign( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::CopySign( DoubleGenerator( ), -1.0 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleCopySign );

static void BenchmarkOpenLibMDoubleCopySign( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::copysign( DoubleGenerator( ), -1.0 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleCopySign );

static void BenchmarkStdDoubleCopySign( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::copysign( DoubleGenerator( ), -1.0 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleCopySign );

static void BenchmarkPbrtDoubleCopySign( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::copysign( DoubleGenerator( ), -1.0 ) );
    }
}
BENCHMARK( BenchmarkPbrtDoubleCopySign );


static void BenchmarkMathFloatCopySign( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::CopySign( FloatGenerator( ), -1.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatCopySign );

static void BenchmarkOpenLibMFloatCopySign( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::copysignf( FloatGenerator( ), -1.0f ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatCopySign );

static void BenchmarkStdFloatCopySign( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::copysign( FloatGenerator( ), -1.0f ) );
    }
}
BENCHMARK( BenchmarkStdFloatCopySign );

static void BenchmarkPbrtFloatCopySign( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::copysign( FloatGenerator( ), -1.0f ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatCopySign );


static void BenchmarkMathDoubleScaleByN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ScaleByN( DoubleGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleScaleByN );

static void BenchmarkOpenLibMDoubleScaleByN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::scalbn( DoubleGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleScaleByN );

static void BenchmarkStdDoubleScaleByN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::scalbn( DoubleGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleScaleByN );

static void BenchmarkMathFloatScaleByN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ScaleByN( FloatGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkMathFloatScaleByN );

static void BenchmarkOpenLibMFloatScaleByN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::scalbnf( FloatGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatScaleByN );

static void BenchmarkStdFloatScaleByN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::scalbn( FloatGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkStdFloatScaleByN );

static void BenchmarkMathDoubleFMod( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( DoubleGenerator( ), M_PI ) );
    }
}
BENCHMARK( BenchmarkMathDoubleFMod );

static void BenchmarkOpenLibMDoubleFMod( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmod( DoubleGenerator( ), M_PI ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleFMod );

static void BenchmarkStdDoubleFMod( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::fmod( DoubleGenerator( ), M_PI ) );
    }
}
BENCHMARK( BenchmarkStdDoubleFMod );

static void BenchmarkMathFloatFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( FloatGenerator( ), static_cast<float>(M_PI) ) );
    }
}
BENCHMARK( BenchmarkMathFloatFMod );

static void BenchmarkMathVector2fFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( Math::Vector2f( FloatGenerator( ) ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fFMod );

static void BenchmarkMathVector2fSimdFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( Math::Vector2f::Simd( FloatGenerator( ) ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdFMod );

static void BenchmarkMathVector3fFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( Math::Vector3f( FloatGenerator( ) ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fFMod );

static void BenchmarkMathVector3fSimdFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( Math::Vector3f::Simd( FloatGenerator( ) ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdFMod );


static void BenchmarkMathVector4fFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( Math::Vector4f( FloatGenerator( ) ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fFMod );

static void BenchmarkMathVector4fSimdFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( Math::Vector4f::Simd( FloatGenerator( ) ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdFMod );


static void BenchmarkOpenLibMFloatFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmodf( FloatGenerator( ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatFMod );

static void BenchmarkStdFloatFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::fmod( FloatGenerator( ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatFMod );

static void BenchmarkPbrtFloatFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::fmod( FloatGenerator( ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatFMod );

static void BenchmarkMathDoubleExp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Exp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleExp );

static void BenchmarkOpenLibMDoubleExp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::exp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleExp );

static void BenchmarkStdDoubleExp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::exp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleExp );

static void BenchmarkMathFloatExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Exp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatExp );

static void BenchmarkMathVector2fExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Exp( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fExp );

static void BenchmarkMathVector2fSimdExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f::Simd v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Exp( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdExp );

static void BenchmarkMathVector3fExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Exp( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fExp );

static void BenchmarkMathVector3fSimdExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f::Simd v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Exp( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdExp );

static void BenchmarkMathVector4fExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Exp( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fExp );

static void BenchmarkMathVector4fSimdExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f::Simd v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Exp( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdExp );



static void BenchmarkMathFloatFastExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastExp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatFastExp );


static void BenchmarkOpenLibMFloatExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::expf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatExp );

static void BenchmarkStdFloatExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::exp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatExp );

static void BenchmarkPbrtFloatFastExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FastExp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatFastExp );


static void BenchmarkMathDoubleExpM1( benchmark::State& state )
{

    DoubleM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( DoubleM10To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleExpM1 );

static void BenchmarkOpenLibMDoubleExpM1( benchmark::State& state )
{

    DoubleM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::expm1( DoubleM10To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleExpM1 );

static void BenchmarkStdDoubleExpM1( benchmark::State& state )
{

    DoubleM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::expm1( DoubleM10To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleExpM1 );




static void BenchmarkMathFloatExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( FloatM10To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatExpM1 );

static void BenchmarkMathVector2fExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( Math::Vector2f(FloatM10To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fExpM1 );

static void BenchmarkMathVector2fSimdExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( Math::Vector2f::Simd( FloatM10To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdExpM1 );

static void BenchmarkMathVector3fExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( Math::Vector3f( FloatM10To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fExpM1 );

static void BenchmarkMathVector3fSimdExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( Math::Vector3f::Simd( FloatM10To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdExpM1 );


static void BenchmarkMathVector4fExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( Math::Vector4f( FloatM10To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fExpM1 );

static void BenchmarkMathVector4fSimdExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( Math::Vector4f::Simd( FloatM10To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdExpM1 );



static void BenchmarkOpenLibMFloatExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::expm1f( FloatM10To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatExpM1 );

static void BenchmarkStdFloatExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::expm1f( FloatM10To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatExpM1 );




static void BenchmarkMathDoubleHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleHypot );

static void BenchmarkOpenLibMDoubleHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::hypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleHypot );

static void BenchmarkOpenLibMDoubleFastHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastHypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleFastHypot );

static void BenchmarkStdDoubleHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleHypot );


static void BenchmarkMathFloatHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatHypot );

static void BenchmarkMathVector2fHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( Math::Vector2f( FloatGenerator( ) ), Math::Vector2f( 16.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fHypot );

static void BenchmarkMathVector2SimdfHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( Math::Vector2f::Simd( FloatGenerator( ) ), Math::Vector2f::Simd( 16.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2SimdfHypot );

static void BenchmarkMathVector3fHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( Math::Vector3f( FloatGenerator( ) ), Math::Vector3f( 16.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fHypot );

static void BenchmarkMathVector3SimdfHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( Math::Vector3f::Simd( FloatGenerator( ) ), Math::Vector3f::Simd( 16.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3SimdfHypot );

static void BenchmarkMathVector4fHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( Math::Vector4f( FloatGenerator( ) ), Math::Vector4f( 16.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fHypot );

static void BenchmarkMathVector4SimdfHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( Math::Vector4f::Simd( FloatGenerator( ) ), Math::Vector4f::Simd( 16.0f ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4SimdfHypot );


static void BenchmarkOpenLibMFloatHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::hypotf( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatHypot );

static void BenchmarkOpenLibMFloatFastHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastHypot( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatFastHypot );


static void BenchmarkStdFloatHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkStdFloatHypot );

static void BenchmarkMathDoubleHypot3( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( DoubleGenerator( ), 16.0, 42.0 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleHypot3 );

static void BenchmarkStdDoubleHypot3( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( DoubleGenerator( ), 16.0, 42.0 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleHypot3 );

static void BenchmarkMathFloatHypot3( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( FloatGenerator( ), 16.0f, 42.0f ) );
    }
}
BENCHMARK( BenchmarkMathFloatHypot3 );

static void BenchmarkStdFloatHypot3( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( FloatGenerator( ), 16.0f, 42.0f ) );
    }
}
BENCHMARK( BenchmarkStdFloatHypot3 );

static void BenchmarkMathDoubleLog( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleLog );

static void BenchmarkOpenLibMDoubleLog( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleLog );

static void BenchmarkStdDoubleLog( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleLog );

static void BenchmarkMathFloatLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatLog );

static void BenchmarkMathVector2fLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Log( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fLog );

static void BenchmarkMathVector2fSimdLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f::Simd v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Log( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdLog );

static void BenchmarkMathVector3fLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Log( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fLog );

static void BenchmarkMathVector3fSimdLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f::Simd v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Log( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdLog );

static void BenchmarkMathVector4fLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Log( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fLog );

static void BenchmarkMathVector4fSimdLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f::Simd v( FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::Log( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdLog );



static void BenchmarkOpenLibMFloatLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::logf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatLog );

static void BenchmarkStdFloatLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatLog );

static void BenchmarkMathDoubleLog1P( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log1P( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleLog1P );


static void BenchmarkOpenLibMDoubleLog1P( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log1p( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleLog1P );

static void BenchmarkStdDoubleLog1P( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log1p( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleLog1P );

static void BenchmarkMathFloatLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log1P( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatLog1P );

static void BenchmarkMathVector2fLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log1P( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fLog1P );

static void BenchmarkMathVector2fSimdLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log1P( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdLog1P );

static void BenchmarkMathVector3fLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log1P( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fLog1P );

static void BenchmarkMathVector3fSimdLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log1P( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdLog1P );

static void BenchmarkMathVector4fLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log1P( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fLog1P );

static void BenchmarkMathVector4fSimdLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log1P( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdLog1P );




static void BenchmarkOpenLibMFloatLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log1pf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatLog1P );

static void BenchmarkStdFloatLog1P( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log1pf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatLog1P );


static void BenchmarkMathDoubleLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleLog2 );



static void BenchmarkOpenLibMDoubleLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleLog2 );

static void BenchmarkStdDoubleLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleLog2 );


static void BenchmarkMathFloatLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatLog2 );

static void BenchmarkMathVector2fLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fLog2 );

static void BenchmarkMathVector2fSimdLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdLog2 );

static void BenchmarkMathVector3fLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fLog2 );

static void BenchmarkMathVector3fSimdLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdLog2 );

static void BenchmarkMathVector4fLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fLog2 );

static void BenchmarkMathVector4fSimdLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdLog2 );


static void BenchmarkOpenLibMFloatLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log2f( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatLog2 );

static void BenchmarkStdFloatLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatLog2 );


static void BenchmarkMathDoubleLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleLog10 );

static void BenchmarkOpenLibMDoubleLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log10( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleLog10 );

static void BenchmarkStdDoubleLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleLog10 );


static void BenchmarkMathFloatLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatLog10 );

//
static void BenchmarkMathVector2fLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fLog10 );

static void BenchmarkMathVector2fSimdLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdLog10 );

static void BenchmarkMathVector3fLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fLog10 );

static void BenchmarkMathVector3fSimdLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdLog10 );

static void BenchmarkMathVector4fLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fLog10 );

static void BenchmarkMathVector4fSimdLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdLog10 );

static void BenchmarkOpenLibMFloatLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log10f( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatLog10 );

static void BenchmarkStdFloatLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatLog10 );

static void BenchmarkMathDoublePow( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Pow( DoubleGenerator( ), DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoublePow );

static void BenchmarkOpenLibMDoublePow( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::pow( DoubleGenerator( ), DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoublePow );

static void BenchmarkStdDoublePow( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::pow( DoubleGenerator( ), DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoublePow );

static void BenchmarkMathFloatPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Pow( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatPow );

static void BenchmarkMathVector2fPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Pow( Math::Vector2f( FloatGenerator( ) ), Math::Vector2f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fPow );

static void BenchmarkMathVector2fSimdPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Pow( Math::Vector2f::Simd( FloatGenerator( ) ), Math::Vector2f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdPow );

static void BenchmarkMathVector3fPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Pow( Math::Vector3f( FloatGenerator( ) ), Math::Vector3f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fPow );

static void BenchmarkMathVector3fSimdPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Pow( Math::Vector3f::Simd( FloatGenerator( ) ), Math::Vector3f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdPow );

static void BenchmarkMathVector4fPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Pow( Math::Vector4f( FloatGenerator( ) ), Math::Vector4f( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fPow );

static void BenchmarkMathVector4fSimdPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Pow( Math::Vector4f::Simd( FloatGenerator( ) ), Math::Vector4f::Simd( FloatGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdPow );


static void BenchmarkOpenLibMFloatPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::pow( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatPow );

static void BenchmarkStdFloatPow( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::pow( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatPow );




static void BenchmarkMathDoubleSin( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sin( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleSin );


static void BenchmarkOpenLibMDoubleSin( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::sin( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleSin );


static void BenchmarkStdDoubleSin( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sin( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleSin );

static void BenchmarkMathFloatSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sin( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSin );

static void BenchmarkMathVector2fSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Sin( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSin );

static void BenchmarkMathVector2fSimdSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Sin( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdSin );

static void BenchmarkMathVector3fSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Sin( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSin );

static void BenchmarkMathVector3fSimdSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Sin( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdSin );

static void BenchmarkMathVector4fSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Sin( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSin );

static void BenchmarkMathVector4fSimdSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Sin( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdSin );

static void BenchmarkOpenLibMFloatSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::sinf( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatSin );

static void BenchmarkStdFloatSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sin( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatSin );

static void BenchmarkMathDoubleCos( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Cos( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleCos );

static void BenchmarkOpenLibMDoubleCos( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::cos( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleCos );


static void BenchmarkStdDoubleCos( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::cos( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleCos );

static void BenchmarkMathFloatCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Cos( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatCos );

static void BenchmarkMathVector2fCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Cos( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fCos );

static void BenchmarkMathVector2fSimdCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Cos( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdCos );

static void BenchmarkMathVector3fCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Cos( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fCos );

static void BenchmarkMathVector3fSimdCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Cos( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdCos );

static void BenchmarkMathVector4fCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Cos( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fCos );

static void BenchmarkMathVector4fSimdCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Cos( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdCos );



static void BenchmarkOpenLibMFloatCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::cosf( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatCos );

static void BenchmarkStdFloatCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::cos( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatCos );


static void BenchmarkMathDoubleSinCos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        double sine, cosine;
        Math::SinCos( DoubleMinusOneToOneGenerator( ), &sine, &cosine );
        benchmark::DoNotOptimize( cosine );
    }
}
BENCHMARK( BenchmarkMathDoubleSinCos );


static void BenchmarkOpenLibMDoubleSinCos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        double sine, cosine;
        OpenLibM::sincos( DoubleMinusOneToOneGenerator( ), &sine, &cosine );
        benchmark::DoNotOptimize( cosine );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleSinCos );


static void BenchmarkMathFloatSinCos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        float sine, cosine;
        Math::SinCos( FloatMinusOneToOneGenerator( ), &sine, &cosine );
        benchmark::DoNotOptimize( cosine );
    }
}
BENCHMARK( BenchmarkMathFloatSinCos );


static void BenchmarkOpenLibMFloatSinCos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        float sine, cosine;
        OpenLibM::sincosf( FloatMinusOneToOneGenerator( ), &sine, &cosine );
        benchmark::DoNotOptimize( cosine );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatSinCos );

static void BenchmarkDirectXMathFloatSinCos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        float sine, cosine;
        DirectX::XMScalarSinCos( &sine, &cosine, FloatMinusOneToOneGenerator( ) );
        benchmark::DoNotOptimize( cosine );
    }
}
BENCHMARK( BenchmarkDirectXMathFloatSinCos );


static void BenchmarkMathDoubleTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Tan( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleTan );

static void BenchmarkOpenLibMDoubleTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::tan( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleTan );

static void BenchmarkStdDoubleTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::tan( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleTan );

static void BenchmarkMathFloatTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Tan( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatTan );

static void BenchmarkMathVector2fTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Tan( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fTan );

static void BenchmarkMathVector2fSimdTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector2f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Tan( v ) );
    }
}
BENCHMARK( BenchmarkMathVector2fSimdTan );

static void BenchmarkMathVector3fTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Tan( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fTan );

static void BenchmarkMathVector3fSimdTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector3f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Tan( v ) );
    }
}
BENCHMARK( BenchmarkMathVector3fSimdTan );

static void BenchmarkMathVector4fTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Tan( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fTan );

static void BenchmarkMathVector4fSimdTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::Vector4f::Simd v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        benchmark::DoNotOptimize( Math::Tan( v ) );
    }
}
BENCHMARK( BenchmarkMathVector4fSimdTan );


static void BenchmarkOpenLibMFloatTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::tanf( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatTan );

static void BenchmarkStdFloatTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::tan( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatTan );

static void BenchmarkMathDoubleATan( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleATan );


static void BenchmarkOpenLibMDoubleATan( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleATan );


static void BenchmarkStdDoubleATan( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleATan );

static void BenchmarkMathFloatATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatATan );

static void BenchmarkOpenLibMFloatATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atanf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatATan );

static void BenchmarkStdFloatATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatATan );

static void BenchmarkMathDoubleASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ASin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleASin );


static void BenchmarkOpenLibMDoubleASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::asin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleASin );

static void BenchmarkOpenLibMDoubleFastASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastASin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleFastASin );


static void BenchmarkStdDoubleASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::asin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleASin );

static void BenchmarkMathFloatASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatASin );

static void BenchmarkOpenLibMFloatASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::asinf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatASin );

static void BenchmarkOpenLibMFloatFastASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatFastASin );

static void BenchmarkStdFloatASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::asin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatASin );


static void BenchmarkMathDoubleACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleACos );

static void BenchmarkOpenLibMDoubleACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::acos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleACos );

static void BenchmarkOpenLibMDoubleFastACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastACos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleFastACos );


static void BenchmarkStdDoubleACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::acos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleACos );

static void BenchmarkMathFloatACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatACos );

static void BenchmarkOpenLibMFloatACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::acosf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatACos );

static void BenchmarkOpenLibMFloatFastACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatFastACos );


static void BenchmarkStdFloatACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::acos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatACos );

static void BenchmarkMathDoubleATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan2( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkMathDoubleATan2 );

static void BenchmarkOpenLibMDoubleATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atan2( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleATan2 );

static void BenchmarkStdDoubleATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan2( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkStdDoubleATan2 );

static void BenchmarkMathFloatATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan2( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkMathFloatATan2 );

static void BenchmarkOpenLibMFloatATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atan2f( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkOpenLibMFloatATan2 );

static void BenchmarkStdFloatATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan2( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkStdFloatATan2 );




static void BenchmarkMathFloatFMA( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMA( FloatMinusOneToOneGenerator( ), 0.5f, 2.5f ) );
    }
}
BENCHMARK( BenchmarkMathFloatFMA );


static void BenchmarkPbrtFloatFMA( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FMA( FloatMinusOneToOneGenerator( ), 0.5f, 2.5f ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatFMA );

static void BenchmarkMathFloatSinXOverX( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SinXOverX( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSinXOverX );


static void BenchmarkPbrtFloatSinXOverX( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SinXOverX( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSinXOverX );




static void BenchmarkMathFloatSinc( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sinc( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSinc );


static void BenchmarkPbrtFloatSinc( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Sinc( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSinc );


static void BenchmarkMathFloatMod( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Mod( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatMod );


static void BenchmarkPbrtFloatMod( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Mod( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatMod );


static void BenchmarkMathFloatSmoothStep( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SmoothStep( FloatGenerator( ), FloatGenerator.LowerBound, FloatGenerator.UpperBound ) );
    }
}
BENCHMARK( BenchmarkMathFloatSmoothStep );


static void BenchmarkPbrtFloatSmoothStep( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SmoothStep( FloatGenerator( ), FloatGenerator.LowerBound, FloatGenerator.UpperBound ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSmoothStep );


static void BenchmarkMathFloatSafeSqrt( benchmark::State& state )
{
    FloatPositiveGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SafeSqrt( FloatPositiveGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSafeSqrt );


static void BenchmarkPbrtFloatSafeSqrt( benchmark::State& state )
{
    FloatPositiveGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SafeSqrt( FloatPositiveGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSafeSqrt );


static void BenchmarkMathFloatSqr( benchmark::State& state )
{
    FloatPositiveGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqr( FloatPositiveGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSqr );


static void BenchmarkPbrtFloatSqr( benchmark::State& state )
{
    FloatPositiveGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Sqr( FloatPositiveGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSqr );


static void BenchmarkMathFloatSafeASin( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SafeASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSafeASin );


static void BenchmarkPbrtFloatSafeASin( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SafeASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSafeASin );


static void BenchmarkMathFloatSafeACos( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SafeACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSafeACos );


static void BenchmarkPbrtFloatSafeACos( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SafeACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSafeACos );


static void BenchmarkMathFloatAddAdjustUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::AddAdjustUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatAddAdjustUp );


static void BenchmarkPbrtFloatAddRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::AddRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatAddRoundUp );



static void BenchmarkMathFloatAddAdjustDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::AddAdjustDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatAddAdjustDown );


static void BenchmarkPbrtFloatAddRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::AddRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatAddRoundDown );


static void BenchmarkMathFloatSubAdjustUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SubAdjustUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSubAdjustUp );


static void BenchmarkPbrtFloatSubRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SubRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSubRoundUp );



static void BenchmarkMathFloatSubAdjustDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SubAdjustDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSubAdjustDown );


static void BenchmarkPbrtFloatSubRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SubRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSubRoundDown );



static void BenchmarkMathFloatMulAdjustUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::MulAdjustUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatMulAdjustUp );


static void BenchmarkPbrtFloatMulRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::MulRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatMulRoundUp );



static void BenchmarkMathFloatMulAdjustDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::MulAdjustDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatMulAdjustDown );


static void BenchmarkPbrtFloatMulRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::MulRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatMulRoundDown );


static void BenchmarkMathFloatDivAdjustUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::DivAdjustUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatDivAdjustUp );


static void BenchmarkPbrtFloatDivRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::DivRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatDivRoundUp );



static void BenchmarkMathFloatDivAdjustDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::DivAdjustDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatDivAdjustDown );


static void BenchmarkPbrtFloatDivRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::DivRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatDivRoundDown );


static void BenchmarkMathFloatSqrtAdjustUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SqrtAdjustUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSqrtAdjustUp );


static void BenchmarkPbrtFloatSqrtRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SqrtRoundUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSqrtRoundUp );


static void BenchmarkMathFloatSqrtAdjustDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SqrtAdjustDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSqrtAdjustDown );


static void BenchmarkPbrtFloatSqrtRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SqrtRoundDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSqrtRoundDown );


static void BenchmarkMathFloatFMAAdjustUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMAAdjustUp( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatFMAAdjustUp );



static void BenchmarkPbrtFloatFMARoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FMARoundUp( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatFMARoundUp );


static void BenchmarkMathFloatFMAAdjustDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMAAdjustDown( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatFMAAdjustDown );


static void BenchmarkPbrtFloatFMARoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FMARoundDown( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatFMARoundDown );



static void BenchmarkMathFloatFastLog2( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastLog2( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatFastLog2 );


static void BenchmarkPbrtFloatLog2( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Log2( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatLog2 );



static void BenchmarkMathFloatLog2Int( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2Int( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatLog2Int );


static void BenchmarkPbrtFloatLog2Int( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Log2Int( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatLog2Int );


static void BenchmarkMathFloatGaussian( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Gaussian( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatGaussian );


static void BenchmarkPbrtFloatGaussian( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Gaussian( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatGaussian );


static void BenchmarkMathFloatLogistic( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Logistic( Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatLogistic );


static void BenchmarkPbrtFloatLogistic( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Logistic( Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatLogistic );


static void BenchmarkMathFloatDifferenceOfProducts( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::DifferenceOfProducts( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatDifferenceOfProducts );


static void BenchmarkPbrtFloatDifferenceOfProducts( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::DifferenceOfProducts( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatDifferenceOfProducts );


static void BenchmarkMathFloatSumOfProducts( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SumOfProducts( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatSumOfProducts );


static void BenchmarkPbrtFloatSumOfProducts( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SumOfProducts( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSumOfProducts );


static void BenchmarkMathFloatQuadratic( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    float t1, t2;
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Quadratic( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), &t1, &t2 ) );
    }
}
BENCHMARK( BenchmarkMathFloatQuadratic );

static void BenchmarkPbrtFloatQuadratic( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    float t1, t2;
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Quadratic( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), &t1, &t2 ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatQuadratic );

static void BenchmarkMathFloatIntervalMultiply( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) * Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalMultiply );


static void BenchmarkPbrtFloatIntervalMultiply( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) * Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalMultiply );


static void BenchmarkMathFloatIntervalDivide( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) / Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalDivide );


static void BenchmarkPbrtFloatIntervalDivide( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) / Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalDivide );


static void BenchmarkMathFloatIntervalScalarMultiply( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) * Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalScalarMultiply );


static void BenchmarkPbrtFloatIntervalScalarMultiply( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) * Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalScalarMultiply );


static void BenchmarkMathFloatIntervalScalarDivision( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) / Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalScalarDivision );


static void BenchmarkPbrtFloatIntervalScalarDivision( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) / Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalScalarDivision );


static void BenchmarkMathFloatIntervalAddition( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) + Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalAddition );


static void BenchmarkPbrtFloatIntervalAddition( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) + Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalAddition );


static void BenchmarkMathFloatIntervalSubtraction( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) - Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalSubtraction );


static void BenchmarkPbrtFloatIntervalSubtraction( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) - Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalSubtraction );


static void BenchmarkMathFloatIntervalScalarAddition( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) + Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalScalarAddition );


static void BenchmarkPbrtFloatIntervalScalarAddition( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) + Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalScalarAddition );


static void BenchmarkMathFloatIntervalScalarSubtraction( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) - Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalScalarSubtraction );


static void BenchmarkPbrtFloatIntervalScalarSubtraction( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) - Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalScalarSubtraction );


static void BenchmarkMathFloatIntervalSqrt( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalSqrt );


static void BenchmarkPbrtFloatIntervalSqrt( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Sqrt( Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalSqrt );


static void BenchmarkMathFloatIntervalFMA( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMA( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalFMA );


static void BenchmarkPbrtFloatIntervalFMA( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FMA( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalFMA );


static void BenchmarkMathFloatIntervalDifferenceOfProducts( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::DifferenceOfProducts( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalDifferenceOfProducts );


static void BenchmarkPbrtFloatIntervalDifferenceOfProducts( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::DifferenceOfProducts( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalDifferenceOfProducts );


static void BenchmarkMathFloatIntervalSumOfProducts( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SumOfProducts( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalSumOfProducts );

static void BenchmarkPbrtFloatIntervalSumOfProducts( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SumOfProducts( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalSumOfProducts );

static void BenchmarkMathFloatIntervalQuadratic( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    Interval t0, t1;

    for ( auto _ : state )
    {
        Math::Quadratic( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), &t0, &t1 );
        benchmark::DoNotOptimize( t0 );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalQuadratic );


static void BenchmarkPbrtFloatIntervalQuadratic( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = pbrt::Interval;

    Interval t0, t1;

    for ( auto _ : state )
    {
        pbrt::Quadratic( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), &t0, &t1 );
        benchmark::DoNotOptimize( t0 );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalQuadratic );


static void BenchmarkMathFloatIntervalACos( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACos( Interval( FloatMinusOneToOneGenerator( ), FloatMinusOneToOneGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalACos );


static void BenchmarkPbrtFloatIntervalACos( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::ACos( Interval( FloatMinusOneToOneGenerator( ), FloatMinusOneToOneGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalACos );


static void BenchmarkMathFloatIntervalCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Cos( Interval( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalCos );


static void BenchmarkPbrtFloatIntervalCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Cos( Interval( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalCos );


static void BenchmarkMathFloatIntervalSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sin( Interval( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatIntervalSin );


static void BenchmarkPbrtFloatIntervalSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    using Interval = pbrt::Interval;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Sin( Interval( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatIntervalSin );



static void BenchmarkOpenLibMDoubleSinH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::sinh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkOpenLibMDoubleSinH );

static void BenchmarkDoubleMathSinH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SinH( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleMathSinH );


static void BenchmarkDoubleStdSinH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sinh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdSinH );



static void BenchmarkFloatOpenLibMSinH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::sinhf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMSinH );

static void BenchmarkFloatMathSinH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SinH( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMathSinH );


static void BenchmarkFloatStdSinH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sinh( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdSinH );


static void BenchmarkDoubleOpenLibMASinH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::asinh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMASinH );

static void BenchmarkDoubleMathASinH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ASinH( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleMathASinH );


static void BenchmarkDoubleStdASinH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::asinh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdASinH );

static void BenchmarkFloatOpenLibMASinH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::asinhf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMASinH );

static void BenchmarkFloatMathASinH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ASinH( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMathASinH );


static void BenchmarkFloatStdASinH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::asinh( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdASinH );

//
static void BenchmarkDoubleOpenLibMCosH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::cosh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMCosH );

static void BenchmarkDoubleMathCosH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::CosH( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleMathCosH );


static void BenchmarkDoubleStdCosH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::cosh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdCosH );



static void BenchmarkFloatOpenLibMCosH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::coshf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMCosH );

static void BenchmarkFloatMathCosH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::CosH( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMathCosH );


static void BenchmarkFloatStdCosH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::cosh( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdCosH );


static void BenchmarkDoubleOpenLibMACosH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::acosh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMACosH );

static void BenchmarkDoubleMathACosH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACosH( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleMathACosH );


static void BenchmarkDoubleStdACosH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::acosh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdACosH );

static void BenchmarkFloatOpenLibMACosH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::acoshf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMACosH );

static void BenchmarkFloatMathACosH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACosH( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMathACosH );


static void BenchmarkFloatStdACosH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::acosh( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdACosH );

///

static void BenchmarkDoubleOpenLibMTanH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::tanh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMTanH );

static void BenchmarkDoubleMathTanH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::TanH( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleMathTanH );


static void BenchmarkDoubleStdTanH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::tanh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdTanH );



static void BenchmarkFloatOpenLibMTanH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::tanhf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMTanH );

static void BenchmarkFloatMathTanH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::TanH( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMathTanH );


static void BenchmarkFloatStdTanH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::tanh( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdTanH );


static void BenchmarkDoubleOpenLibMATanH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atanh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMATanH );

static void BenchmarkDoubleMathATanH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATanH( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleMathATanH );


static void BenchmarkDoubleStdATanH( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atanh( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdATanH );

static void BenchmarkFloatOpenLibMATanH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atanhf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMATanH );

static void BenchmarkFloatMathATanH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATanH( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMathATanH );


static void BenchmarkFloatStdATanH( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atanh( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdATanH );


static void BenchmarkMathDoubleErf( benchmark::State& state )
{

    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Erf( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathDoubleErf );

static void BenchmarkStdDoubleErf( benchmark::State& state )
{

    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::erf( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdDoubleErf );

static void BenchmarkMathFloatErf( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Erf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkMathFloatErf );


static void BenchmarkStdFloatErf( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::erf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkStdFloatErf );


#endif


BENCHMARK_MAIN( );
