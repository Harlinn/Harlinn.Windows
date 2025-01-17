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

using Constants = Math::Constants<float>;
using Quaternion = Math::Quaternion<float>;
using Q = Math::Quaternion<float>;

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

#ifdef RUN_QUATERNION_BENCHMARKS

static void BenchmarkXMQuaternionSlerp( benchmark::State& state )
{
    using namespace DirectX;


    FloatAngleInRadiansGenerator.Reset( );
    FloatZeroToOneGenerator.Reset( );

    for ( auto _ : state )
    {
        XMFLOAT4 q1Unloaded( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto q1 = XMLoadFloat4( &q1Unloaded );
        XMFLOAT4 q2Unloaded( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto q2 = XMLoadFloat4( &q2Unloaded );

        auto q1n = XMQuaternionNormalize( q1 );
        auto q2n = XMQuaternionNormalize( q2 );

        auto result = XMQuaternionSlerp( q1n, q2n, FloatZeroToOneGenerator( ) );

        XMFLOAT4 resultStored;
        XMStoreFloat4( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.w );
    }
}
BENCHMARK( BenchmarkXMQuaternionSlerp );


static void BenchmarkQuaternionSlerp( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );
    FloatZeroToOneGenerator.Reset( );

    for ( auto _ : state )
    {
        Q q1( FloatAngleInRadiansGenerator(), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Q q2( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );

        auto q1n = Normalize( q1 );
        auto q2n = Normalize( q2 );

        Q result = Slerp( q1n, q2n, FloatZeroToOneGenerator( ) );

        benchmark::DoNotOptimize( result.w );
    }
}
BENCHMARK( BenchmarkQuaternionSlerp );

#ifndef PBRT_USES_HCCMATH
static void BenchmarkPbrtQuaternionSlerp( benchmark::State& state )
{
    
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );
    FloatZeroToOneGenerator.Reset( );

    for ( auto _ : state )
    {
        pbrt::Quaternion q1( pbrt::Vector3f(FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( )), FloatAngleInRadiansGenerator( ) );
        pbrt::Quaternion q2( pbrt::Vector3f( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( )), FloatAngleInRadiansGenerator( ) );

        pbrt::Quaternion q1n = pbrt::Normalize( q1 );
        pbrt::Quaternion q2n = pbrt::Normalize( q2 );

        pbrt::Quaternion result = pbrt::Slerp( FloatZeroToOneGenerator( ), q1n, q2n );

        benchmark::DoNotOptimize( result.w );
    }
}
BENCHMARK( BenchmarkPbrtQuaternionSlerp );
#endif

static void BenchmarkXMQuaternionMultiply( benchmark::State& state )
{
    using namespace DirectX;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        XMFLOAT4 q1Unloaded( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto q1 = XMLoadFloat4( &q1Unloaded );
        XMFLOAT4 q2Unloaded( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto q2 = XMLoadFloat4( &q2Unloaded );


        auto result = XMQuaternionMultiply( q1, q2 );

        XMFLOAT4 resultStored;
        XMStoreFloat4( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.w );
    }
}
BENCHMARK( BenchmarkXMQuaternionMultiply );


static void BenchmarkQuaternionMultiply( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        Q q1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Q q2( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );

        Q result = q1 * q2;

        benchmark::DoNotOptimize( result.w );
    }
}
BENCHMARK( BenchmarkQuaternionMultiply );

static void BenchmarkXMQuaternionRotationNormal( benchmark::State& state )
{
    using namespace DirectX;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        XMFLOAT3 vUnloaded( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto v = XMLoadFloat3( &vUnloaded );

        auto result = XMQuaternionRotationNormal( v, FloatAngleInRadiansGenerator( ) );

        XMFLOAT4 resultStored;
        XMStoreFloat4( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.w );
    }
}
BENCHMARK( BenchmarkXMQuaternionRotationNormal );


static void BenchmarkQuaternionFromNormalizedAxisAndAngle( benchmark::State& state )
{
    using namespace Math;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector3f v( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );

        Q result = Math::Quaternion<float>::FromNormalizedAxisAndAngle(v, FloatAngleInRadiansGenerator( ) );

        benchmark::DoNotOptimize( result.w );
    }
}
BENCHMARK( BenchmarkQuaternionFromNormalizedAxisAndAngle );





#endif
