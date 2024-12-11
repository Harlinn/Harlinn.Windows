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

/*
for ( auto _ : state )
{
    Vector v1( 1.0f, 2.0f, 3.f, 1.0f );
    Vector v2( 1.0f, 2.0f, 3.f, 1.0f );
    Vector v3 = ( v1 + v2 ) + ( v1 + v2 ) + ( v1 + v2 );
    DebugBreak( );
    benchmark::DoNotOptimize( v3 );
}
*/

static void BenchmarkVector2MultipleAdds( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = Math::Vector<float, 4>;
    using VectorSimd = typename Vector::Simd;
    using Traits = typename Vector::Traits;
    FloatGenerator.Reset( );
    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        VectorSimd l1 = Traits::Load( v1.values.data() );
        VectorSimd l2 = Traits::Load( v2.values.data( ) );
        benchmark::DoNotOptimize( (( l1 + l2 ) + l1 ) + (( l2 + l1 ) + l2 ) );
    }
}
BENCHMARK( BenchmarkVector2MultipleAdds );


static void BenchmarkVector2MultipleXMVectorAdd( benchmark::State& state )
{
    using namespace DirectX;
    using Vector = XMFLOAT4A;
    FloatGenerator.Reset( );
    
    for ( auto _ : state )
    {
        Vector v1( { FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) } );
        Vector v2( { FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) } );
        auto v1Loaded = XMLoadFloat4A( &v1 );
        auto v2Loaded = XMLoadFloat4A( &v2 );
        benchmark::DoNotOptimize( 
            XMVectorAdd(
                XMVectorAdd( 
                    XMVectorAdd( 
                        v1Loaded,
                        v2Loaded ),
                    v1Loaded ),
                XMVectorAdd( 
                    XMVectorAdd( 
                        v2Loaded,
                        v1Loaded ),
                    v2Loaded ) ) );
    }
}
BENCHMARK( BenchmarkVector2MultipleXMVectorAdd );


static void BenchmarkVector2MultipleOperations( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = Math::Vector<float, 3>;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Dot( Abs( Max( Ceil( -v1 ), Floor( v2 ) ) ), v2 ) );
    }
}
BENCHMARK( BenchmarkVector2MultipleOperations );

static void BenchmarkPBRTVector2fMultipleOperations( benchmark::State& state )
{
    using namespace pbrt;
    using Vector = pbrt::Vector3f;
    FloatGenerator.Reset( );


    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Dot( Abs( Max( Ceil( -v1 ), Floor( v2 ) ) ), v2 ) );
    }
}
BENCHMARK( BenchmarkPBRTVector2fMultipleOperations );

static void BenchmarkMathFMA1( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        auto a = FloatGenerator( );
        auto b = FloatGenerator( );
        auto c = FloatGenerator( );
        benchmark::DoNotOptimize( Math::FMA( a, b, c ) );
    }
}
BENCHMARK( BenchmarkMathFMA1 );

static void BenchmarkPbrtFMA1( benchmark::State& state )
{
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        auto a = FloatGenerator( );
        auto b = FloatGenerator( );
        auto c = FloatGenerator( );
        benchmark::DoNotOptimize( pbrt::FMA( a, b, c ) );
    }
}
BENCHMARK( BenchmarkPbrtFMA1 );

static void BenchmarkMathFMA2( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = Math::Vector<float, 2>;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        auto a = FloatGenerator( );
        Vector b( FloatGenerator( ), FloatGenerator( ) );
        Vector c( FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::FMA( a, b, c ) );
    }
}
BENCHMARK( BenchmarkMathFMA2 );

static void BenchmarkPbrtFMA2( benchmark::State& state )
{
    using Vector = pbrt::Vector2f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        auto a = FloatGenerator( );
        Vector b( FloatGenerator( ), FloatGenerator( ) );
        Vector c( FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize(pbrt::FMA( a, b, c ) );
    }
}
BENCHMARK( BenchmarkPbrtFMA2 );


static void BenchmarkMathFMA3( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = Math::Vector<float, 3>;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        auto a = FloatGenerator( );
        Vector b( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector c( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Math::FMA( a, b, c ) );
    }
}
BENCHMARK( BenchmarkMathFMA3 );

static void BenchmarkPbrtFMA3( benchmark::State& state )
{
    using Vector = pbrt::Vector3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        auto a = FloatGenerator( );
        Vector b( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector c( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( pbrt::FMA( a, b, c ) );
    }
}
BENCHMARK( BenchmarkPbrtFMA3 );


static void BenchmarkMathQuaternionAdd( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Quaternion = Math::Quaternion<float>;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Quaternion q1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Quaternion q2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( q1 + q2 );
    }
}
BENCHMARK( BenchmarkMathQuaternionAdd );

static void BenchmarkPbrtQuaternionAdd( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Quaternion = pbrt::Quaternion;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Quaternion q1( { FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) }, FloatGenerator( ) );
        Quaternion q2( { FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) }, FloatGenerator( ) );
        benchmark::DoNotOptimize( q1 + q2 );
    }
}
BENCHMARK( BenchmarkPbrtQuaternionAdd );

static void BenchmarkMathPoint3Distance( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Point = Math::Point3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Point p1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Point p2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Distance(p1, p2) );
    }
}
BENCHMARK( BenchmarkMathPoint3Distance );

static void BenchmarkPbrtPoint3Distance( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Point = pbrt::Point3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Point p1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Point p2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( pbrt::Distance( p1, p2 ) );
    }
}
BENCHMARK( BenchmarkPbrtPoint3Distance );

static void BenchmarkMathPoint3DistanceSquared( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Point = Math::Point3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Point p1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Point p2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( DistanceSquared( p1, p2 ) );
    }
}
BENCHMARK( BenchmarkMathPoint3DistanceSquared );

static void BenchmarkPbrtPoint3DistanceSquared( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Point = pbrt::Point3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Point p1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Point p2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( pbrt::DistanceSquared( p1, p2 ) );
    }
}
BENCHMARK( BenchmarkPbrtPoint3DistanceSquared );

static void BenchmarkMathVector3Cross( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = Math::Vector3f;
    using Normal = Math::Normal3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Cross( v1, v2 ) );
    }
}
BENCHMARK( BenchmarkMathVector3Cross );

static void BenchmarkMathPbrtVector3Cross( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = pbrt::Vector3f;
    using Normal = pbrt::Normal3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Normal v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( pbrt::Cross( v1, v2 ) );
    }
}
BENCHMARK( BenchmarkMathVector3Cross );


static void BenchmarkMathVector3Dot( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = Math::Vector3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( Dot( v1, v2 ) );
    }
}
BENCHMARK( BenchmarkMathVector3Dot );

static void BenchmarkPbrtVector3Dot( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = pbrt::Vector3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( pbrt::Dot( v1, v2 ) );
    }
}
BENCHMARK( BenchmarkPbrtVector3Dot );


static void BenchmarkMathVector3AngleBetween( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = Math::Vector3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( AngleBetween( v1, v2 ) );
        //DebugBreak( );
    }
}
BENCHMARK( BenchmarkMathVector3AngleBetween );

static void BenchmarkPbrtVector3AngleBetween( benchmark::State& state )
{
    using namespace Harlinn::Common::Core::Math;
    using Vector = pbrt::Vector3f;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        benchmark::DoNotOptimize( pbrt::AngleBetween( v1, v2 ) );
    }
}
BENCHMARK( BenchmarkPbrtVector3AngleBetween );

// XMVector3AngleBetweenVectors

static void BenchmarkXMVector3AngleBetweenVectors( benchmark::State& state )
{
    using namespace DirectX;
    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        XMFLOAT3A v1( { FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) } );
        XMFLOAT3A v2( { FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) } );
        benchmark::DoNotOptimize( XMVector3AngleBetweenVectors( XMLoadFloat3A(&v1 ), XMLoadFloat3A( &v2 ) ) );
    }
}
BENCHMARK( BenchmarkXMVector3AngleBetweenVectors );



#endif
