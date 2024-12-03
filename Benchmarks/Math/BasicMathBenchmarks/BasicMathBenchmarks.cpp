// BasicMathBenchmarks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HCCMath.h>
#include <pbrto/util/math.h>
#include <benchmark/benchmark.h>
#include <random>

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
        return Values[ Counter++%N ];
    }
    void Reset()
    {
        Counter = 0;
    }
};

constexpr size_t SampleCount = 64;

RandomGenerator<double, SampleCount> DoubleGenerator;
RandomGenerator<float, SampleCount> FloatGenerator;
RandomGenerator<double, SampleCount> DoubleAngleInDegreesGenerator(0.0,360.0);
RandomGenerator<float, SampleCount> FloatAngleInDegreesGenerator( 0.0f, 360.0f );
RandomGenerator<double, SampleCount> DoubleAngleInRadiansGenerator( 0.0, M_PI * 2 );
RandomGenerator<float, SampleCount> FloatAngleInRadiansGenerator( 0.0f, (float) M_PI * 2 );

RandomGenerator<double, SampleCount> DoubleZeroToOneGenerator( 0.0, 1.0 );
RandomGenerator<float, SampleCount> FloatZeroToOneGenerator( 0.0f, 1.0f );

RandomGenerator<double, SampleCount> DoubleMinusOneToOneGenerator( -1.0, 1.0 );
RandomGenerator<float, SampleCount> FloatMinusOneToOneGenerator( -1.0f, 1.0f );


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

static void BenchmarkFloatStdNextAfter( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::nextafter( FloatGenerator( ), 0.0 ) );
    }
}
BENCHMARK( BenchmarkFloatStdNextAfter );

static void BenchmarkDoubleInternalSqrt( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::SqrtImpl( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalSqrt );

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


static void BenchmarkFloatInternalSqrt( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::SqrtImpl( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalSqrt );

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


static void BenchmarkDoubleInternalExpImpl( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ExpImpl( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalExpImpl );

static void BenchmarkDoubleExp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Exp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleExp );

static void BenchmarkDoubleStdExp( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::exp( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdExp );

static void BenchmarkFloatInternalExpImpl( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ExpImpl( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalExpImpl );

static void BenchmarkFloatExp( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Exp( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatExp );

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


static void BenchmarkDoubleInternalHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::HypotImpl( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalHypot );

static void BenchmarkDoubleHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleHypot );

static void BenchmarkDoubleStdHypot( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( DoubleGenerator( ), 16.0 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdHypot );

static void BenchmarkFloatInternalHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::HypotImpl( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkFloatInternalHypot );

static void BenchmarkFloatHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Hypot( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkFloatHypot );

static void BenchmarkFloatStdHypot( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::hypot( FloatGenerator( ), 16.0f ) );
    }
}
BENCHMARK( BenchmarkFloatStdHypot );


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

static void BenchmarkFloatStdLog( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdLog );

static void BenchmarkDoubleInternalLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::Log2Impl( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalLog2 );

static void BenchmarkDoubleLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleLog2 );

static void BenchmarkDoubleStdLog2( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdLog2 );

static void BenchmarkFloatInternalLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::Log2Impl( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalLog2 );

static void BenchmarkFloatLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatLog2 );

static void BenchmarkFloatStdLog2( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdLog2 );

static void BenchmarkDoubleInternalLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::Log10Impl( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalLog10 );

static void BenchmarkDoubleLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleLog10 );

static void BenchmarkDoubleStdLog10( benchmark::State& state )
{
    DoubleGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( DoubleGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdLog10 );

static void BenchmarkFloatInternalLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::Log10Impl( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalLog10 );

static void BenchmarkFloatLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Log10( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatLog10 );

static void BenchmarkFloatStdLog10( benchmark::State& state )
{
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::log2( FloatGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdLog10 );

static void BenchmarkDoubleInternalSin( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::SinImpl( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalSin );

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

static void BenchmarkFloatInternalSin( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::SinImpl( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalSin );

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

static void BenchmarkDoubleInternalCos( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::CosImpl( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalCos );

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
        benchmark::DoNotOptimize( std::sin( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdCos );

static void BenchmarkFloatInternalCos( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::CosImpl( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalCos );

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
        benchmark::DoNotOptimize( std::sin( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdCos );


static void BenchmarkDoubleInternalTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::TanImpl( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalTan );

static void BenchmarkDoubleTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Tan( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleTan );

static void BenchmarkDoubleStdTan( benchmark::State& state )
{
    DoubleAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sin( DoubleAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdTan );

static void BenchmarkFloatInternalTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::TanImpl( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalTan );

static void BenchmarkFloatTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Tan( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatTan );

static void BenchmarkFloatStdTan( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::sin( FloatAngleInRadiansGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdTan );

static void BenchmarkDoubleInternalATan( benchmark::State& state )
{
    
    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ATanImpl( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalATan );

static void BenchmarkDoubleATan( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleATan );

static void BenchmarkDoubleStdATan( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdATan );

static void BenchmarkFloatInternalATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ATanImpl( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalATan );

static void BenchmarkFloatATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatATan );

static void BenchmarkFloatStdATan( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdATan );

static void BenchmarkDoubleInternalASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ASinImpl( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalASin );

static void BenchmarkDoubleASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ASin( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleASin );

static void BenchmarkDoubleStdASin( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdASin );

static void BenchmarkFloatInternalASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ASinImpl( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalASin );

static void BenchmarkFloatASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ASin( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatASin );

static void BenchmarkFloatStdASin( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdASin );

static void BenchmarkDoubleInternalACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ACosImpl( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalACos );

static void BenchmarkDoubleACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACos( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleACos );

static void BenchmarkDoubleStdACos( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( DoubleMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkDoubleStdACos );

static void BenchmarkFloatInternalACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ACosImpl( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatInternalACos );

static void BenchmarkFloatACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ACos( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatACos );

static void BenchmarkFloatStdACos( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan( FloatMinusOneToOneGenerator( ) ) );
    }
}
BENCHMARK( BenchmarkFloatStdACos );

static void BenchmarkDoubleInternalATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ATan2Impl( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkDoubleInternalATan2 );

static void BenchmarkDoubleATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan2( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkDoubleATan2 );

static void BenchmarkDoubleStdATan2( benchmark::State& state )
{

    DoubleMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan2( DoubleMinusOneToOneGenerator( ), 0.5 ) );
    }
}
BENCHMARK( BenchmarkDoubleStdATan2 );

static void BenchmarkFloatInternalATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::Internal::ATan2Impl( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkFloatInternalATan2 );

static void BenchmarkFloatATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( Math::ATan2( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkFloatATan2 );

static void BenchmarkFloatStdATan2( benchmark::State& state )
{

    FloatMinusOneToOneGenerator.Reset( );
    for ( auto _ : state )
    {
        benchmark::DoNotOptimize( std::atan2( FloatMinusOneToOneGenerator( ), 0.5f ) );
    }
}
BENCHMARK( BenchmarkFloatStdATan2 );


BENCHMARK_MAIN( );