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



namespace Basics
{

    using namespace Harlinn::Common::Core;
    using namespace Harlinn::Common::Core::Math;

    using Quaternion = Math::Quaternion<float>;


    // The Shortest Arc Quaternion as described by Sam Melax in Game Programming Gems

    Quaternion ShortestArc1( const Vector3f& fromDir, const Vector3f& toDir ) noexcept
    {
        using Constants = Vector3f::Traits::Constants::Base;

        Vector3f fromDirNormalized = Normalize( fromDir );
        Vector3f toDirNormalized = Normalize( toDir );

        const float dot = ScalarDot( fromDirNormalized, toDirNormalized );
        if ( dot >= 1.f )
        {
            return Quaternion::Identity( );
        }
        else if ( dot <= -1.f )
        {
            Vector3f axis = Cross( fromDirNormalized, Vector3f::Right( ) );
            if ( AreNearlyEqual( ScalarLengthSquared( axis ), 0.f, Constants::EpsilonValue ) )
            {
                axis = Cross( fromDirNormalized, Vector3f::Up( ) );
            }

            return Quaternion::FromAxisAndAngle( axis, Constants::Pi );
        }
        else
        {
            const float s = Sqrt( ( 1.f + dot ) * 2.f );
            Vector3f cp = Cross( fromDirNormalized, toDirNormalized ) / s;
            Quaternion result( cp, s * 0.5f );
            return result;
        }
    }


    Quaternion ShortestArc2( const Vector3f::Simd& fromDir, const Vector3f::Simd& toDir ) noexcept
    {
        using Constants = Vector3f::Traits::Constants::Base;

        auto fromDirNormalized = Normalize( fromDir );
        auto toDirNormalized = Normalize( toDir );

        const auto dot = Dot( fromDirNormalized, toDirNormalized );
        const auto dotf = dot[ 0 ];
        if ( dotf >= 1.f )
        {
            return Quaternion::Identity( );
        }
        else if ( dotf <= -1.f )
        {
            auto axis = Cross( fromDirNormalized, Vector3f::Right( ) );
            if ( AreNearlyEqual( ScalarLengthSquared( axis ), 0.f, Constants::EpsilonValue ) )
            {
                axis = Cross( fromDirNormalized, Vector3f::Up( ) );
            }

            return Quaternion::FromAxisAndAngle( axis, Constants::Pi );
        }
        else
        {
            const auto s = Sqrt( ( 1.f + dot ) * 2.f );
            auto cp = Cross( fromDirNormalized, toDirNormalized ) / s;
            Quaternion result( cp, s.x() * 0.5f );
            return result;
        }
    }
}

static void BenchmarkShortestArc1( benchmark::State& state )
{
    using namespace Math;

    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Math::Vector3f v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Math::Vector3f v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

        Q result = Basics::ShortestArc1( v1, v2 );

        benchmark::DoNotOptimize( result.w );
    }
}
BENCHMARK( BenchmarkShortestArc1 );

static void BenchmarkShortestArc2( benchmark::State& state )
{
    using namespace Math;

    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Math::Vector3f::Simd v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Math::Vector3f::Simd v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

        Q result = Basics::ShortestArc2( v1, v2 );

        benchmark::DoNotOptimize( result.w );
    }
}
BENCHMARK( BenchmarkShortestArc2 );


static void BenchmarkDirectXTK12QuaternionFromToRotation( benchmark::State& state )
{
    using namespace DirectX::SimpleMath;

    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Vector3 v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Vector3 v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

        auto result = DirectX::SimpleMath::Quaternion::FromToRotation( v1, v2 );

        benchmark::DoNotOptimize( result.w );
    }
}
BENCHMARK( BenchmarkDirectXTK12QuaternionFromToRotation );


static void BenchmarkShortestArc( benchmark::State& state )
{
    using namespace Math;

    FloatGenerator.Reset( );

    for ( auto _ : state )
    {
        Math::Vector3f::Simd v1( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );
        Math::Vector3f::Simd v2( FloatGenerator( ), FloatGenerator( ), FloatGenerator( ) );

        Q result = Math::ShortestArc( v1, v2 );

        benchmark::DoNotOptimize( result.w );
    }
}
BENCHMARK( BenchmarkShortestArc );

#endif
