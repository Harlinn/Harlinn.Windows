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


static void BenchmarkDoubleIsSameValue( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsSameValue( DoubleGenerator( ), 1.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleIsSameValue );

static void BenchmarkFloatIsSameValue( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsSameValue( FloatGenerator( ), 1.0f ) );
    }
}
BENCHMARK( BenchmarkFloatIsSameValue );

static void BenchmarkDoubleIsZero( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsZero( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleIsZero );

static void BenchmarkFloatIsZero( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsZero( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatIsZero );

static void BenchmarkDoubleIsNaN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleIsNaN );

static void BenchmarkDoubleOpenLibMIsNaN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::isnan( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMIsNaN );

static void BenchmarkDoubleStdIsNaN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::isnan( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdIsNaN );

static void BenchmarkDoublePbrtoIsNaN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::IsNaN( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoublePbrtoIsNaN );


static void BenchmarkFloatIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsNaN( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatIsNaN );

static void BenchmarkFloatOpenLibMIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::__isnanf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMIsNaN );

static void BenchmarkFloatStdIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::isnan( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdIsNaN );

static void BenchmarkFloatPbrtoIsNaN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::IsNaN( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtoIsNaN );


static void BenchmarkDoubleSignum( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::signum( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleSignum );

static void BenchmarkDoubleOpenLibMSignbit( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::signbit( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMSignbit );

template <typename T> int NaiveSignum( T val )
{
    return ( T( 0 ) < val ) - ( val < T( 0 ) );
}

static void BenchmarkDoubleNaiveSignum( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( NaiveSignum( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleNaiveSignum );

static void BenchmarkFloatSignum( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::signum( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSignum );

static void BenchmarkFloatOpenLibMSignbit( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::__signbitf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMSignbit );

static void BenchmarkFloatNaiveSignum( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( NaiveSignum( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatNaiveSignum );

static void BenchmarkDoubleDeg2Rad( benchmark::State& state )
{
    DoubleAngleInDegreesGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Deg2Rad( DoubleAngleInDegreesGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleDeg2Rad );

static void BenchmarkDoublePbrtRadians( benchmark::State& state )
{
    DoubleAngleInDegreesGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Radians( DoubleAngleInDegreesGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoublePbrtRadians );


static void BenchmarkFloatDeg2Rad( benchmark::State& state )
{
    FloatAngleInDegreesGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Deg2Rad( FloatAngleInDegreesGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatDeg2Rad );

static void BenchmarkFloatPbrtRadians( benchmark::State& state )
{
    FloatAngleInDegreesGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Radians( FloatAngleInDegreesGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtRadians );


static void BenchmarkDoubleRad2Deg( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Rad2Deg( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleRad2Deg );

static void BenchmarkDoublePbrtDegrees( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Degrees( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoublePbrtDegrees );


static void BenchmarkFloatRad2Deg( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Rad2Deg( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatRad2Deg );

static void BenchmarkFloatPbrtDegrees( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Degrees( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtDegrees );


static void BenchmarkDoubleNextAfter( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextAfter( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleNextAfter );

static void BenchmarkDoubleOpenLibMNextAfter( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::nextafter( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMNextAfter );

static void BenchmarkDoubleStdNextAfter( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdNextAfter );

static void BenchmarkFloatNextAfter( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextAfter( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkFloatNextAfter );


static void BenchmarkFloatOpenLibMNextAfter( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::nextafterf( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMNextAfter );

static void BenchmarkFloatStdNextAfter( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( FloatGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkFloatStdNextAfter );


static void BenchmarkDoubleInternalOpenLibMSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::sqrt( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalOpenLibMSqrt );

static void BenchmarkDoubleSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleSqrt );

static void BenchmarkDoubleStdSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sqrt( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdSqrt );

static void BenchmarkDoublePbrtSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::sqrt( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoublePbrtSqrt );

static void BenchmarkFloatInternalOpenLibMSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::sqrtf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalOpenLibMSqrt );

static void BenchmarkFloatSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSqrt );

static void BenchmarkFloatStdSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sqrt( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdSqrt );

static void BenchmarkFloatPbrtSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::sqrt( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtSqrt );


static void BenchmarkDoubleNextDown( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleNextDown );

static void BenchmarkDoubleStdNextDown( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( DoubleGenerator( ), -std::numeric_limits<double>::infinity( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdNextDown );

static void BenchmarkFloatNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatNextDown );

static void BenchmarkFloatStdNextDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( FloatGenerator( ), -std::numeric_limits<float>::infinity( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdNextDown );

static void BenchmarkFloatPbrtNextFloatDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::NextFloatDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtNextFloatDown );


static void BenchmarkDoubleNextUp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleNextUp );

static void BenchmarkDoubleStdNextUp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( DoubleGenerator( ), std::numeric_limits<double>::infinity( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdNextUp );


static void BenchmarkFloatNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatNextUp );

static void BenchmarkFloatStdNextUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( FloatGenerator( ), std::numeric_limits<float>::infinity( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdNextUp );

static void BenchmarkFloatPbrtNextFloatUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::NextFloatUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtNextFloatUp );


static void BenchmarkDoubleIsInf( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleIsInf );

static void BenchmarkDoubleOpenLibMIsInf( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::isinf( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMIsInf );

static void BenchmarkDoubleStdIsInf( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::isinf( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdIsInf );

static void BenchmarkFloatIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::IsInf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatIsInf );

static void BenchmarkFloatOpenLibMIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::__isinff( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMIsInf );

static void BenchmarkFloatStdIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::isinf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdIsInf );

static void BenchmarkFloatPbrtIsInf( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::IsInf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtIsInf );


static void BenchmarkDoubleInternalAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::AbsImpl( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalAbs );

static void BenchmarkDoubleAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleAbs );

static void BenchmarkDoubleOpenLibMAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fabs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMAbs );

static void BenchmarkDoubleStdAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::abs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdAbs );

static void BenchmarkDoublePbrtAbs( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::abs( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoublePbrtAbs );


static void BenchmarkFloatInternalAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::AbsImpl( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalAbs );


static void BenchmarkFloatAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Abs( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatAbs );

static void BenchmarkFloatOpenLibMAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fabsf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMAbs );


static void BenchmarkFloatStdAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::abs( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdAbs );

static void BenchmarkFloatPbrtAbs( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::abs( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtAbs );


static void BenchmarkDoubleSignBit( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SignBit( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleSignBit );

static void BenchmarkDoubleOpenLibMSignBit( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::signbit( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMSignBit );

static void BenchmarkDoubleStdSignBit( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::signbit( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdSignBit );

static void BenchmarkFloatSignBit( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SignBit( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSignBit );

static void BenchmarkFloatOpenLibMSignBit( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::signbit( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMSignBit );

static void BenchmarkFloatStdSignBit( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::signbit( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdSignBit );

static void BenchmarkDoubleFRExp( benchmark::State& state )
{
    int exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FRExp( DoubleGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkDoubleFRExp );

static void BenchmarkDoubleOpenLibMFRExp( benchmark::State& state )
{
    int exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::frexp( DoubleGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMFRExp );

static void BenchmarkDoubleStdFRExp( benchmark::State& state )
{
    int exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::frexp( DoubleGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkDoubleStdFRExp );

static void BenchmarkFloatFRExp( benchmark::State& state )
{
    int exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FRExp( FloatGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkFloatFRExp );

static void BenchmarkFloatOpenLibMFRExp( benchmark::State& state )
{
    int exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::frexpf( FloatGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMFRExp );

static void BenchmarkFloatStdFRExp( benchmark::State& state )
{
    int exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::frexp( FloatGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkFloatStdFRExp );

static void BenchmarkDoubleModF( benchmark::State& state )
{
    double exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ModF( DoubleGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkDoubleModF );

static void BenchmarkDoubleOpenLibMModF( benchmark::State& state )
{
    double exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::modf( DoubleGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMModF );

static void BenchmarkDoubleStdModF( benchmark::State& state )
{
    double exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::modf( DoubleGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkDoubleStdModF );

static void BenchmarkFloatingPointDoubleModF( benchmark::State& state )
{
    double exp;
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<double>::ModF( DoubleGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkFloatingPointDoubleModF );


static void BenchmarkFloatModF( benchmark::State& state )
{
    float exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ModF( FloatGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkFloatModF );

static void BenchmarkFloatOpenLibMModF( benchmark::State& state )
{
    float exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::modff( FloatGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMModF );

static void BenchmarkFloatingPointFloatModF( benchmark::State& state )
{
    float exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<float>::ModF( FloatGenerator( ), exp ) );
    }
}
BENCHMARK( BenchmarkFloatingPointFloatModF );


static void BenchmarkFloatStdModF( benchmark::State& state )
{
    float exp;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::modf( FloatGenerator( ), &exp ) );
    }
}
BENCHMARK( BenchmarkFloatStdModF );

static void BenchmarkDoubleMin( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleMin );

static void BenchmarkDoubleOpenLibMMin( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmin( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMMin );

static void BenchmarkDoubleStdMin( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::min( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdMin );

static void BenchmarkFloatMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Min( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkFloatMin );

static void BenchmarkFloatOpenLibMMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fminf( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMMin );

static void BenchmarkFloatStdMin( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::min( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkFloatStdMin );

static void BenchmarkDoubleMax( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleMax );

static void BenchmarkDoubleOpenLibMMax( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmax( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMMax );

static void BenchmarkDoubleStdMax( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::max( DoubleGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdMax );

static void BenchmarkFloatMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Max( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkFloatMax );

static void BenchmarkFloatOpenLibMMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmaxf( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMMax );

static void BenchmarkFloatStdMax( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::max( FloatGenerator( ), 0.0f ) );
    }
}
BENCHMARK( BenchmarkFloatStdMax );


static void BenchmarkDoubleTrunc( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleTrunc );

static void BenchmarkDoubleOpenLibMTrunc( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::trunc( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMTrunc );

static void BenchmarkFloatingPointDoubleTrunc( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::FloatingPoint<double> fp( DoubleGenerator( ) );
        benchmark::DoNotOptimize( fp.Trunc(  ) );
    }
}
BENCHMARK( BenchmarkFloatingPointDoubleTrunc );


static void BenchmarkDoubleStdTrunc( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::trunc( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdTrunc );

static void BenchmarkFloatTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Trunc( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatTrunc );

static void BenchmarkFloatOpenLibMTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::truncf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMTrunc );

static void BenchmarkFloatingPointFloatTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Math::FloatingPoint<float> fp( FloatGenerator( ) );
        benchmark::DoNotOptimize( fp.Trunc( ) );
    }
}
BENCHMARK( BenchmarkFloatingPointFloatTrunc );


static void BenchmarkFloatStdTrunc( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::trunc( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdTrunc );

static void BenchmarkDoubleFloor( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleFloor );

static void BenchmarkDoubleOpenLibMFloor( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::floor( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMFloor );

static void BenchmarkFloatingPointDoubleFloor( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<double>::Floor( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatingPointDoubleFloor );


static void BenchmarkDoubleStdFloor( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::floor( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdFloor );

static void BenchmarkFloatFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Floor( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatFloor );

static void BenchmarkFloatOpenLibMFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::floorf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMFloor );

static void BenchmarkFloatingPointFloatFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<float>::Floor( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatingPointFloatFloor );


static void BenchmarkFloatStdFloor( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::floor( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdFloor );


static void BenchmarkDoubleCeil( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleCeil );

static void BenchmarkDoubleOpenLibMCeil( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::ceil( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMCeil );

static void BenchmarkFloatingPointDoubleCeil( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<double>::Ceil( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatingPointDoubleCeil );


static void BenchmarkDoubleStdCeil( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::ceil( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdCeil );

static void BenchmarkFloatCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Ceil( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatCeil );

static void BenchmarkFloatOpenLibMCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::ceilf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMCeil );

static void BenchmarkFloatingPointFloatCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<float>::Ceil( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatingPointFloatCeil );

static void BenchmarkFloatStdCeil( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::ceil( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdCeil );

static void BenchmarkDoubleRound( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleRound );

static void BenchmarkDoubleOpenLibMRound( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::round( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMRound );

static void BenchmarkFloatingPointDoubleRound( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<double>::Round( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatingPointDoubleRound );


static void BenchmarkDoubleStdRound( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::round( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdRound );

static void BenchmarkFloatRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Round( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatRound );

static void BenchmarkFloatOpenLibMRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::roundf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMRound );


static void BenchmarkFloatingPointFloatRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FloatingPoint<float>::Round( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatingPointFloatRound );


static void BenchmarkFloatStdRound( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::round( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdRound );

static void BenchmarkDoubleClamp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( DoubleGenerator( ), -1000.0, 1000.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleClamp );

static void BenchmarkDoubleStdClamp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::clamp( DoubleGenerator( ), -1000.0, 1000.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdClamp );

static void BenchmarkFloatClamp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Clamp( FloatGenerator( ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkFloatClamp );

static void BenchmarkFloatStdClamp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::clamp( FloatGenerator( ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkFloatStdClamp );

static void BenchmarkFloatPbrtClamp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Clamp( FloatGenerator( ), -1000.0f, 1000.0f ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtClamp );

static void BenchmarkDoubleInternalLerpImpl( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::LerpImpl( 5.0, 10.0, DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalLerpImpl );


static void BenchmarkDoubleLerp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0, 10.0, DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleLerp );

static void BenchmarkDoubleStdLerp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::lerp( 5.0, 10.0, DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdLerp );

static void BenchmarkFloatLerp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Lerp( 5.0f, 10.0f, FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatLerp );


static void BenchmarkFloatInternalLerpImpl( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::LerpImpl( 5.0f, 10.0f, FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalLerpImpl );

static void BenchmarkFloatStdLerp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::lerp( 5.0f, 10.0f, FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdLerp );

static void BenchmarkFloatPbrtLerp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Lerp( 5.0f, 10.0f, FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtLerp );



static void BenchmarkDoubleCopySign( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::CopySign( DoubleGenerator( ), -1.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleCopySign );

static void BenchmarkDoubleOpenLibMCopySign( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::copysign( DoubleGenerator( ), -1.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMCopySign );

static void BenchmarkDoubleStdCopySign( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::copysign( DoubleGenerator( ), -1.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdCopySign );

static void BenchmarkDoublePbrtCopySign( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::copysign( DoubleGenerator( ), -1.0 ) );
    }
}
BENCHMARK( BenchmarkDoublePbrtCopySign );


static void BenchmarkFloatCopySign( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::CopySign( FloatGenerator( ), -1.0f ) );
    }
}
BENCHMARK( BenchmarkFloatCopySign );

static void BenchmarkFloatOpenLibMCopySign( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::copysignf( FloatGenerator( ), -1.0f ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMCopySign );

static void BenchmarkFloatStdCopySign( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::copysign( FloatGenerator( ), -1.0f ) );
    }
}
BENCHMARK( BenchmarkFloatStdCopySign );

static void BenchmarkFloatPbrtCopySign( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::copysign( FloatGenerator( ), -1.0f ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtCopySign );


static void BenchmarkDoubleScaleByN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ScaleByN( DoubleGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkDoubleScaleByN );

static void BenchmarkDoubleOpenLibMScaleByN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::scalbn( DoubleGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMScaleByN );

static void BenchmarkDoubleStdScaleByN( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::scalbn( DoubleGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdScaleByN );

static void BenchmarkFloatScaleByN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ScaleByN( FloatGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkFloatScaleByN );

static void BenchmarkFloatOpenLibMScaleByN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::scalbnf( FloatGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMScaleByN );

static void BenchmarkFloatStdScaleByN( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::scalbn( FloatGenerator( ), 42 ) );
    }
}
BENCHMARK( BenchmarkFloatStdScaleByN );

static void BenchmarkDoubleFMod( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( DoubleGenerator( ), M_PI ) );
    }
}
BENCHMARK( BenchmarkDoubleFMod );

static void BenchmarkDoubleOpenLibMFMod( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmod( DoubleGenerator( ), M_PI ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMFMod );

static void BenchmarkDoubleStdFMod( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::fmod( DoubleGenerator( ), M_PI ) );
    }
}
BENCHMARK( BenchmarkDoubleStdFMod );

static void BenchmarkFloatFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMod( FloatGenerator( ), static_cast<float>(M_PI) ) );
    }
}
BENCHMARK( BenchmarkFloatFMod );

static void BenchmarkFloatOpenLibMFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::fmodf( FloatGenerator( ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMFMod );

static void BenchmarkFloatStdFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::fmod( FloatGenerator( ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdFMod );

static void BenchmarkFloatPbrtFMod( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pstd::fmod( FloatGenerator( ), static_cast< float >( M_PI ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtFMod );



static void BenchmarkDoubleExp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Exp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleExp );

static void BenchmarkDoubleOpenLibMExp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::exp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMExp );

static void BenchmarkDoubleStdExp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::exp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdExp );

static void BenchmarkFloatExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Exp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatExp );

static void BenchmarkFloatOpenLibMExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::expf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMExp );

static void BenchmarkFloatStdExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::exp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdExp );

static void BenchmarkFloatPbrtFastExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FastExp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtFastExp );



static void BenchmarkDoubleHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleHypot );

static void BenchmarkDoubleOpenLibMHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::hypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMHypot );

static void BenchmarkDoubleOpenLibMFastHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastHypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMFastHypot );

static void BenchmarkDoubleStdHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdHypot );


static void BenchmarkFloatHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkFloatHypot );

static void BenchmarkFloatOpenLibMHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::hypotf( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMHypot );

static void BenchmarkFloatOpenLibMFastHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastHypot( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMFastHypot );


static void BenchmarkFloatStdHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkFloatStdHypot );

static void BenchmarkDoubleHypot3( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( DoubleGenerator( ), 16.0, 42.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleHypot3 );

static void BenchmarkDoubleStdHypot3( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( DoubleGenerator( ), 16.0, 42.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdHypot3 );

static void BenchmarkFloatHypot3( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( FloatGenerator( ), 16.0f, 42.0f ) );
    }
}
BENCHMARK( BenchmarkFloatHypot3 );

static void BenchmarkFloatStdHypot3( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( FloatGenerator( ), 16.0f, 42.0f ) );
    }
}
BENCHMARK( BenchmarkFloatStdHypot3 );


static void BenchmarkDoubleInternalLog( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::LogImpl( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalLog );

static void BenchmarkDoubleLog( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleLog );

static void BenchmarkDoubleOpenLibMLog( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMLog );

static void BenchmarkDoubleStdLog( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdLog );

static void BenchmarkFloatInternalLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::LogImpl( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalLog );

static void BenchmarkFloatLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatLog );

static void BenchmarkFloatOpenLibMLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::logf( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMLog );

static void BenchmarkFloatStdLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdLog );


static void BenchmarkDoubleLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleLog2 );


static void BenchmarkDoubleOpenLibMLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMLog2 );

static void BenchmarkDoubleStdLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdLog2 );


static void BenchmarkFloatLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatLog2 );

static void BenchmarkFloatOpenLibMLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log2f( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMLog2 );

static void BenchmarkFloatStdLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdLog2 );


static void BenchmarkDoubleLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleLog10 );

static void BenchmarkDoubleOpenLibMLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log10( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMLog10 );

static void BenchmarkDoubleStdLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdLog10 );


static void BenchmarkFloatLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatLog10 );

static void BenchmarkFloatOpenLibMLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::log10f( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMLog10 );

static void BenchmarkFloatStdLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdLog10 );

static void BenchmarkDoubleOpenLibMSin( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::sin( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMSin );

static void BenchmarkDoubleSin( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sin( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleSin );

static void BenchmarkDoubleStdSin( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sin( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdSin );

static void BenchmarkFloatOpenLibMSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::sinf( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMSin );

static void BenchmarkFloatSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sin( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSin );

static void BenchmarkFloatStdSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sin( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdSin );


static void BenchmarkDoubleOpenLibMCos( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::cos( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMCos );

static void BenchmarkDoubleCos( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Cos( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleCos );

static void BenchmarkDoubleStdCos( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::cos( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdCos );

static void BenchmarkFloatOpenLibMCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::OpenLibM::cosf( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMCos );

static void BenchmarkFloatCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Cos( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatCos );

static void BenchmarkFloatStdCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::cos( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdCos );

static void BenchmarkDoubleOpenLibMSinCos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        double sine, cosine;
        OpenLibM::sincos( DoubleMinusOneToOneGenerator( ), &sine, &cosine );
        benchmark::DoNotOptimize( cosine );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMSinCos );


static void BenchmarkFloatOpenLibMSinCos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        float sine, cosine;
        OpenLibM::sincosf( FloatMinusOneToOneGenerator( ), &sine, &cosine );
        benchmark::DoNotOptimize( cosine );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMSinCos );

static void BenchmarkFloatDirectXSinCos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        float sine, cosine;
        DirectX::XMScalarSinCos( &sine, &cosine, FloatMinusOneToOneGenerator( ) );
        benchmark::DoNotOptimize( cosine );
    }
}
BENCHMARK( BenchmarkFloatDirectXSinCos );


static void BenchmarkDoubleTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Tan( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleTan );

static void BenchmarkDoubleOpenLibMTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::tan( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMTan );

static void BenchmarkDoubleStdTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::tan( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdTan );

static void BenchmarkFloatTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Tan( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatTan );

static void BenchmarkFloatOpenLibMTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::tanf( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMTan );

static void BenchmarkFloatStdTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::tan( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdTan );

static void BenchmarkDoubleATan( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleATan );


static void BenchmarkDoubleOpenLibMATan( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMATan );


static void BenchmarkDoubleStdATan( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdATan );

static void BenchmarkFloatATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatATan );

static void BenchmarkFloatOpenLibMATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atanf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMATan );

static void BenchmarkFloatStdATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdATan );

static void BenchmarkDoubleASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ASin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleASin );


static void BenchmarkDoubleOpenLibMASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::asin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMASin );

static void BenchmarkDoubleOpenLibMFastASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastASin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMFastASin );


static void BenchmarkDoubleStdASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::asin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdASin );

static void BenchmarkFloatASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatASin );

static void BenchmarkFloatOpenLibMASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::asinf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMASin );

static void BenchmarkFloatOpenLibMFastASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMFastASin );

static void BenchmarkFloatStdASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::asin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdASin );


static void BenchmarkDoubleACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleACos );

static void BenchmarkDoubleOpenLibMACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::acos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMACos );

static void BenchmarkDoubleOpenLibMFastACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastACos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMFastACos );


static void BenchmarkDoubleStdACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::acos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdACos );

static void BenchmarkFloatACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatACos );

static void BenchmarkFloatOpenLibMACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::acosf( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMACos );

static void BenchmarkFloatOpenLibMFastACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::FastACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMFastACos );


static void BenchmarkFloatStdACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::acos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdACos );

static void BenchmarkDoubleATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan2( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkDoubleATan2 );

static void BenchmarkDoubleOpenLibMATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atan2( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkDoubleOpenLibMATan2 );

static void BenchmarkDoubleStdATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan2( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdATan2 );

static void BenchmarkFloatATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan2( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkFloatATan2 );

static void BenchmarkFloatOpenLibMATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::atan2f( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMATan2 );

static void BenchmarkFloatStdATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan2( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkFloatStdATan2 );

static void BenchmarkFloatFMA( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMA( FloatMinusOneToOneGenerator( ), 0.5f, 2.5f ) );
    }
}
BENCHMARK( BenchmarkFloatFMA );

static void BenchmarkPbrtFloatFMA( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FMA( FloatMinusOneToOneGenerator( ), 0.5f, 2.5f ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatFMA );

static void BenchmarkFloatSinXOverX( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SinXOverX( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSinXOverX );

static void BenchmarkPbrtFloatSinXOverX( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SinXOverX( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSinXOverX );


static void BenchmarkFloatExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ExpM1( FloatM10To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatExpM1 );

static void BenchmarkFloatOpenLibMExpM1( benchmark::State& state )
{

    FloatM10To100Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( OpenLibM::expm1f( FloatM10To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatOpenLibMExpM1 );


static void BenchmarkFloatSinc( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sinc( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSinc );

static void BenchmarkPbrtFloatSinc( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Sinc( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSinc );


static void BenchmarkFloatMod( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Mod( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMod );

static void BenchmarkPbrtFloatMod( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Mod( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatMod );

static void BenchmarkFloatSmoothStep( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SmoothStep( FloatGenerator( ), FloatGenerator.LowerBound, FloatGenerator.UpperBound ) );
    }
}
BENCHMARK( BenchmarkFloatSmoothStep );

static void BenchmarkPbrtFloatSmoothStep( benchmark::State& state )
{

    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SmoothStep( FloatGenerator( ), FloatGenerator.LowerBound, FloatGenerator.UpperBound ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSmoothStep );


static void BenchmarkFloatSafeSqrt( benchmark::State& state )
{
    FloatPositiveGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SafeSqrt( FloatPositiveGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSafeSqrt );

static void BenchmarkPbrtFloatSafeSqrt( benchmark::State& state )
{
    FloatPositiveGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SafeSqrt( FloatPositiveGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSafeSqrt );

static void BenchmarkFloatSqr( benchmark::State& state )
{
    FloatPositiveGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqr( FloatPositiveGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSqr );

static void BenchmarkPbrtFloatSqr( benchmark::State& state )
{
    FloatPositiveGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Sqr( FloatPositiveGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSqr );

static void BenchmarkFloatSafeASin( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SafeASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSafeASin );

static void BenchmarkPbrtFloatSafeASin( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SafeASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSafeASin );

static void BenchmarkFloatSafeACos( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SafeACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSafeACos );

static void BenchmarkPbrtFloatSafeACos( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SafeACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSafeACos );

static void BenchmarkFloatNextFloatUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextFloatUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatNextFloatUp );

static void BenchmarkPbrtFloatNextFloatUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::NextFloatUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatNextFloatUp );

static void BenchmarkFloatNextFloatDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::NextFloatDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatNextFloatDown );

static void BenchmarkPbrtFloatNextFloatDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::NextFloatDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatNextFloatDown );

static void BenchmarkFloatAddRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::AddRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatAddRoundUp );

static void BenchmarkPbrtFloatAddRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::AddRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatAddRoundUp );


static void BenchmarkFloatAddRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::AddRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatAddRoundDown );

static void BenchmarkPbrtFloatAddRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::AddRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatAddRoundDown );

static void BenchmarkFloatSubRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SubRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSubRoundUp );

static void BenchmarkPbrtFloatSubRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SubRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSubRoundUp );


static void BenchmarkFloatSubRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SubRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSubRoundDown );

static void BenchmarkPbrtFloatSubRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SubRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSubRoundDown );


static void BenchmarkFloatMulRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::MulRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMulRoundUp );

static void BenchmarkPbrtFloatMulRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::MulRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatMulRoundUp );


static void BenchmarkFloatMulRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::MulRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatMulRoundDown );

static void BenchmarkPbrtFloatMulRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::MulRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatMulRoundDown );

static void BenchmarkFloatDivRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::DivRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatDivRoundUp );

static void BenchmarkPbrtFloatDivRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::DivRoundUp( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatDivRoundUp );


static void BenchmarkFloatDivRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::DivRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatDivRoundDown );

static void BenchmarkPbrtFloatDivRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::DivRoundDown( FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatDivRoundDown );

static void BenchmarkFloatSqrtRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SqrtRoundUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSqrtRoundUp );

static void BenchmarkPbrtFloatSqrtRoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SqrtRoundUp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSqrtRoundUp );


static void BenchmarkFloatSqrtRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SqrtRoundDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSqrtRoundDown );

static void BenchmarkPbrtFloatSqrtRoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SqrtRoundDown( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSqrtRoundDown );

static void BenchmarkFloatFMARoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMARoundUp( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatFMARoundUp );


static void BenchmarkPbrtFloatFMARoundUp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FMARoundUp( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatFMARoundUp );

static void BenchmarkFloatFMARoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMARoundDown( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatFMARoundDown );

static void BenchmarkPbrtFloatFMARoundDown( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::FMARoundDown( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatFMARoundDown );


static void BenchmarkFloatFastLog2( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FastLog2( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatFastLog2 );

static void BenchmarkPbrtFloatLog2( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Log2( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatLog2 );


static void BenchmarkFloatLog2Int( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2Int( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatLog2Int );

static void BenchmarkPbrtFloatLog2Int( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Log2Int( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatLog2Int );

static void BenchmarkFloatGaussian( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Gaussian( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatGaussian );

static void BenchmarkPbrtFloatGaussian( benchmark::State& state )
{
    FloatZeroToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Gaussian( FloatZeroToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatGaussian );

static void BenchmarkFloatLogistic( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Logistic( Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatLogistic );

static void BenchmarkPbrtFloatLogistic( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Logistic( Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatLogistic );

static void BenchmarkFloatDifferenceOfProducts( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::DifferenceOfProducts( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatDifferenceOfProducts );

static void BenchmarkPbrtFloatDifferenceOfProducts( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::DifferenceOfProducts( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatDifferenceOfProducts );

static void BenchmarkFloatSumOfProducts( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SumOfProducts( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatSumOfProducts );

static void BenchmarkPbrtFloatSumOfProducts( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::SumOfProducts( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ) ) );
    }
}
BENCHMARK( BenchmarkPbrtFloatSumOfProducts );

static void BenchmarkFloatQuadratic( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    float t1, t2;
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Quadratic( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), &t1, &t2 ) );
    }
}
BENCHMARK( BenchmarkFloatQuadratic );

static void BenchmarkFloatPbrtQuadratic( benchmark::State& state )
{
    Float0To10Generator.Reset( );
    float t1, t2;
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( pbrt::Quadratic( Float0To10Generator( ), Float0To10Generator( ), Float0To10Generator( ), &t1, &t2 ) );
    }
}
BENCHMARK( BenchmarkFloatPbrtQuadratic );

static void BenchmarkFloatIntervalMultiply( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) * Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalMultiply );

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

static void BenchmarkFloatIntervalDivide( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) / Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalDivide );

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

static void BenchmarkFloatIntervalScalarMultiply( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) * Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalScalarMultiply );

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

static void BenchmarkFloatIntervalScalarDivision( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) / Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalScalarDivision );

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

static void BenchmarkFloatIntervalAddition( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) + Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalAddition );

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

static void BenchmarkFloatIntervalSubtraction( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) - Interval( Float1To100Generator( ), Float1To100Generator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalSubtraction );

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

static void BenchmarkFloatIntervalScalarAddition( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) + Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalScalarAddition );

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

static void BenchmarkFloatIntervalScalarSubtraction( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Interval( Float1To100Generator( ), Float1To100Generator( ) ) - Float1To100Generator( ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalScalarSubtraction );

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

static void BenchmarkFloatIntervalSqrt( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sqrt( Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalSqrt );

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

static void BenchmarkFloatIntervalFMA( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::FMA( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalFMA );

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

static void BenchmarkFloatIntervalDifferenceOfProducts( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::DifferenceOfProducts( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalDifferenceOfProducts );

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

static void BenchmarkFloatIntervalSumOfProducts( benchmark::State& state )
{
    Float1To100Generator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::SumOfProducts( Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ), Interval( Float1To100Generator( ), Float1To100Generator( ) ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalSumOfProducts );

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

static void BenchmarkFloatIntervalQuadratic( benchmark::State& state )
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
BENCHMARK( BenchmarkFloatIntervalQuadratic );

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

static void BenchmarkFloatIntervalACos( benchmark::State& state )
{
    FloatMinusOneToOneGenerator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACos( Interval( FloatMinusOneToOneGenerator( ), FloatMinusOneToOneGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalACos );

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

static void BenchmarkFloatIntervalCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Cos( Interval( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalCos );

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


static void BenchmarkFloatIntervalSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    using Interval = Math::Interval<float>;

    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Sin( Interval( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) ) ) );
    }
}
BENCHMARK( BenchmarkFloatIntervalSin );

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


#endif












BENCHMARK_MAIN( );
