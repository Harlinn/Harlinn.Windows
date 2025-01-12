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
#ifdef RUN_TRANSFORM_BENCHMARKS

static void BenchmarkRotationAxis( benchmark::State& state )
{
    Math::Vector3f axis( 0.f, 1.f, 0.f );
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        auto transformation = Math::RotationAxis( axis, FloatAngleInRadiansGenerator() );
        Math::Point3f p1( 2.f, 2.f, 2.f );
        Math::Point3f p1Rotated = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( p1Rotated.z );
    }
}
BENCHMARK( BenchmarkRotationAxis );

static void BenchmarkXMMatrixRotationAxis( benchmark::State& state )
{
    using namespace DirectX;
    XMFLOAT3A axis( 0.f, 1.f, 0.f );
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        auto axisLoaded = XMLoadFloat3A( &axis );
        auto transformation = XMMatrixRotationAxis( axisLoaded, FloatAngleInRadiansGenerator( ) );
        XMFLOAT3A p1( 2.f, 2.f, 2.f );
        auto p1Loaded = XMLoadFloat3A( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3A p1Stored;
        XMStoreFloat3A( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkXMMatrixRotationAxis );

static void BenchmarkTranslation( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float offsetX = FloatAngleInRadiansGenerator( );
        float offsetY = FloatAngleInRadiansGenerator( );
        float offsetZ = FloatAngleInRadiansGenerator( );
        auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
        Math::Point3f p1( 2.f, 2.f, 2.f );
        Math::Point3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkTranslation );

static void BenchmarkXMMatrixTranslation( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float offsetX = FloatAngleInRadiansGenerator( );
        float offsetY = FloatAngleInRadiansGenerator( );
        float offsetZ = FloatAngleInRadiansGenerator( );
        auto transformation = XMMatrixTranslation( offsetX, offsetY, offsetZ );
        XMFLOAT3 p1( 2.f, 2.f, 2.f );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto result = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 resultStored;
        XMStoreFloat3( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.z );
    }
}
BENCHMARK( BenchmarkXMMatrixTranslation );


static void BenchmarkScaling( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float scalingX = FloatAngleInRadiansGenerator( );
        float scalingY = FloatAngleInRadiansGenerator( );
        float scalingZ = FloatAngleInRadiansGenerator( );
        auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
        Math::Point3f p1( 2.f, 2.f, 2.f );
        Math::Point3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkScaling );


static void BenchmarkXMMatrixScaling( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float scalingX = FloatAngleInRadiansGenerator( );
        float scalingY = FloatAngleInRadiansGenerator( );
        float scalingZ = FloatAngleInRadiansGenerator( );
        auto transformation = XMMatrixScaling( scalingX, scalingY, scalingZ );
        XMFLOAT3 p1( 2.f, 2.f, 2.f );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto result = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 resultStored;
        XMStoreFloat3( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.z );
    }
}
BENCHMARK( BenchmarkXMMatrixTranslation );


static void BenchmarkTransformationMatrix( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    const Point3f scalingOrigin( 10.f, 10.f, 10.f );
    const Quaternion<float> scalingOrientationQuaternion( Constants::Pi * 0.6f, Constants::Pi * 0.6f, Constants::Pi * 0.6f );
    const Math::Vector<float, 3> scaling( .8f, .8f, .8f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector<float, 3> translation( 4.f, 4.f, 4.f );

    auto transformation = Math::TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );

    for ( auto _ : state )
    {
        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkTransformationMatrix );

static void BenchmarkXMMatrixTransformation( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );

    const XMFLOAT3A scalingOriginUnloaded( 10.f, 10.f, 10.f );
    auto scalingOrigin = XMLoadFloat3A( &scalingOriginUnloaded );
    const auto scalingOrientationQuaternion = XMQuaternionRotationRollPitchYaw( Constants::Pi * 0.6f, Constants::Pi * 0.6f, Constants::Pi * 0.6f );
    const XMFLOAT3A scalingUnloaded( .8f, .8f, .8f );
    auto scaling = XMLoadFloat3A( &scalingUnloaded );
    const XMFLOAT3A rotationOriginUnloaded( 5.f, 5.f, 5.f );
    auto rotationOrigin = XMLoadFloat3A( &rotationOriginUnloaded );
    const auto rotationQuaternion = XMQuaternionRotationRollPitchYaw( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const XMFLOAT3A translationUnloaded( 4.f, 4.f, 4.f );
    auto translation = XMLoadFloat3A( &translationUnloaded );

    auto transformation = XMMatrixTransformation( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );


    for ( auto _ : state )
    {
        XMFLOAT3A p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3A( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3A p1TransformedStored;
        XMStoreFloat3A( &p1TransformedStored, p1Transformed );

        benchmark::DoNotOptimize( p1TransformedStored.z );
    }
}
BENCHMARK( BenchmarkXMMatrixTransformation );


#endif