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
    RandomGenerator<float, SampleCount> FloatM10To100Generator( -10.0f, 100.0f );
    RandomGenerator<float, SampleCount> Float0To10Generator( 0.0f, 10.0f );
    RandomGenerator<float, SampleCount> Float1To10Generator( 1.0f, 10.0f );
    RandomGenerator<float, SampleCount> Float1To100Generator( 1.0f, 100.0f );


}
#ifdef RUN_TRANSFORM_BENCHMARKS

static void BenchmarkPointRotation( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        auto transformation = Math::Rotation( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f p1Rotated = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( p1Rotated.z );
    }
}
BENCHMARK( BenchmarkPointRotation );

static void BenchmarkPointXMMatrixRotationRollPitchYaw( benchmark::State& state )
{
    using namespace DirectX;
    
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        auto transformation = XMMatrixRotationRollPitchYaw( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        XMFLOAT3A p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3A( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3A p1Stored;
        XMStoreFloat3A( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixRotationRollPitchYaw );


static void BenchmarkPointRotationAxis( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    Math::Vector3f axis( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
    
    for ( auto _ : state )
    {
        auto transformation = Math::RotationAxis( axis, FloatAngleInRadiansGenerator() );
        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f p1Rotated = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( p1Rotated.z );
    }
}
BENCHMARK( BenchmarkPointRotationAxis );

static void BenchmarkPointXMMatrixRotationAxis( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    XMFLOAT3A axis( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
    
    for ( auto _ : state )
    {
        auto axisLoaded = XMLoadFloat3A( &axis );
        auto transformation = XMMatrixRotationAxis( axisLoaded, FloatAngleInRadiansGenerator( ) );
        XMFLOAT3A p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3A( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3A p1Stored;
        XMStoreFloat3A( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixRotationAxis );

static void BenchmarkVectorRotationAxis( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    Math::Vector3f axis( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
    
    for ( auto _ : state )
    {
        auto transformation = Math::RotationAxis( axis, FloatAngleInRadiansGenerator( ) );
        Math::Vector3f v1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f v1Rotated = Math::Transform( v1, transformation );
        benchmark::DoNotOptimize( v1Rotated.z );
    }
}
BENCHMARK( BenchmarkVectorRotationAxis );

static void BenchmarkVectorXMMatrixRotationAxis( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    XMFLOAT3A axis( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
    
    for ( auto _ : state )
    {
        auto axisLoaded = XMLoadFloat3A( &axis );
        auto transformation = XMMatrixRotationAxis( axisLoaded, FloatAngleInRadiansGenerator( ) );
        XMFLOAT3A p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3A( &p1 );
        auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3A p1Stored;
        XMStoreFloat3A( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixRotationAxis );

static void BenchmarkNormalRotationAxis( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    Math::Vector3f axis( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
    
    for ( auto _ : state )
    {
        auto transformation = Math::RotationAxis( axis, FloatAngleInRadiansGenerator( ) );
        Math::Normal3f n1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f n1Rotated = Math::Transform( n1, transformation );
        benchmark::DoNotOptimize( n1Rotated.z );
    }
}
BENCHMARK( BenchmarkNormalRotationAxis );

static void BenchmarkNormalXMMatrixRotationAxis( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    XMFLOAT3A axis( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
    
    for ( auto _ : state )
    {
        auto axisLoaded = XMLoadFloat3A( &axis );
        auto transformation = XMMatrixRotationAxis( axisLoaded, FloatAngleInRadiansGenerator( ) );
        XMFLOAT3A p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3A( &p1 );
        auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3A p1Stored;
        XMStoreFloat3A( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixRotationAxis );




static void BenchmarkPointTranslation( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float offsetX = FloatAngleInRadiansGenerator( );
        float offsetY = FloatAngleInRadiansGenerator( );
        float offsetZ = FloatAngleInRadiansGenerator( );
        auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkPointTranslation );

static void BenchmarkPointXMMatrixTranslation( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float offsetX = FloatAngleInRadiansGenerator( );
        float offsetY = FloatAngleInRadiansGenerator( );
        float offsetZ = FloatAngleInRadiansGenerator( );
        auto transformation = XMMatrixTranslation( offsetX, offsetY, offsetZ );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto result = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 resultStored;
        XMStoreFloat3( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixTranslation );

static void BenchmarkVectorTranslation( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float offsetX = FloatAngleInRadiansGenerator( );
        float offsetY = FloatAngleInRadiansGenerator( );
        float offsetZ = FloatAngleInRadiansGenerator( );
        auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
        Math::Vector3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorTranslation );

static void BenchmarkVectorXMMatrixTranslation( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float offsetX = FloatAngleInRadiansGenerator( );
        float offsetY = FloatAngleInRadiansGenerator( );
        float offsetZ = FloatAngleInRadiansGenerator( );
        auto transformation = XMMatrixTranslation( offsetX, offsetY, offsetZ );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto result = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3 resultStored;
        XMStoreFloat3( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixTranslation );

static void BenchmarkNormalTranslation( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float offsetX = FloatAngleInRadiansGenerator( );
        float offsetY = FloatAngleInRadiansGenerator( );
        float offsetZ = FloatAngleInRadiansGenerator( );
        auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
        Math::Normal3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkNormalTranslation );

static void BenchmarkNormalXMMatrixTranslation( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float offsetX = FloatAngleInRadiansGenerator( );
        float offsetY = FloatAngleInRadiansGenerator( );
        float offsetZ = FloatAngleInRadiansGenerator( );
        auto transformation = XMMatrixTranslation( offsetX, offsetY, offsetZ );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto result = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3 resultStored;
        XMStoreFloat3( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixTranslation );



static void BenchmarkPointScaling( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float scalingX = FloatAngleInRadiansGenerator( );
        float scalingY = FloatAngleInRadiansGenerator( );
        float scalingZ = FloatAngleInRadiansGenerator( );
        auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkPointScaling );


static void BenchmarkPointXMMatrixScaling( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float scalingX = FloatAngleInRadiansGenerator( );
        float scalingY = FloatAngleInRadiansGenerator( );
        float scalingZ = FloatAngleInRadiansGenerator( );
        auto transformation = XMMatrixScaling( scalingX, scalingY, scalingZ );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto result = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 resultStored;
        XMStoreFloat3( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixScaling );

static void BenchmarkVectorScaling( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float scalingX = FloatAngleInRadiansGenerator( );
        float scalingY = FloatAngleInRadiansGenerator( );
        float scalingZ = FloatAngleInRadiansGenerator( );
        auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
        Math::Vector3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorScaling );


static void BenchmarkVectorXMMatrixScaling( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float scalingX = FloatAngleInRadiansGenerator( );
        float scalingY = FloatAngleInRadiansGenerator( );
        float scalingZ = FloatAngleInRadiansGenerator( );
        auto transformation = XMMatrixScaling( scalingX, scalingY, scalingZ );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto result = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3 resultStored;
        XMStoreFloat3( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixScaling );


static void BenchmarkNormalScaling( benchmark::State& state )
{
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float scalingX = FloatAngleInRadiansGenerator( );
        float scalingY = FloatAngleInRadiansGenerator( );
        float scalingZ = FloatAngleInRadiansGenerator( );
        auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
        Math::Normal3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkNormalScaling );

static void BenchmarkNormalXMMatrixScaling( benchmark::State& state )
{
    using namespace DirectX;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float scalingX = FloatAngleInRadiansGenerator( );
        float scalingY = FloatAngleInRadiansGenerator( );
        float scalingZ = FloatAngleInRadiansGenerator( );
        auto transformation = XMMatrixScaling( scalingX, scalingY, scalingZ );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto result = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3 resultStored;
        XMStoreFloat3( &resultStored, result );

        benchmark::DoNotOptimize( resultStored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixScaling );




static void BenchmarkPointTransformationMatrix( benchmark::State& state )
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
BENCHMARK( BenchmarkPointTransformationMatrix );

static void BenchmarkPointXMMatrixTransformation( benchmark::State& state )
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
BENCHMARK( BenchmarkPointXMMatrixTransformation );


static void BenchmarkVectorTransformationMatrix( benchmark::State& state )
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
        Math::Vector3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorTransformationMatrix );

static void BenchmarkVectorXMMatrixTransformation( benchmark::State& state )
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
        auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3A p1TransformedStored;
        XMStoreFloat3A( &p1TransformedStored, p1Transformed );

        benchmark::DoNotOptimize( p1TransformedStored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixTransformation );


static void BenchmarkNormalTransformationMatrix( benchmark::State& state )
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
        Math::Normal3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f result = Math::Transform( p1, transformation );
        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkNormalTransformationMatrix );

static void BenchmarkNormalXMMatrixTransformation( benchmark::State& state )
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
        auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3A p1TransformedStored;
        XMStoreFloat3A( &p1TransformedStored, p1Transformed );

        benchmark::DoNotOptimize( p1TransformedStored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixTransformation );


static void BenchmarkPointAffineTransformationMatrix( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
        const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
        const QuaternionSimd<Quaternion<float>> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
        const Math::Vector3f translation( 4.f, 4.f, 4.f );

        auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkPointAffineTransformationMatrix );

static void BenchmarkPointXMMatrixAffineTransformation( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        const XMFLOAT3A scalingUnloaded( 1.5f, 2.5f, 1.f );
        auto scaling = XMLoadFloat3A( &scalingUnloaded );
        const XMFLOAT3A rotationOriginUnloaded( 5.f, 5.f, 5.f );
        auto rotationOrigin = XMLoadFloat3A( &rotationOriginUnloaded );
        const auto rotationQuaternion = XMQuaternionRotationRollPitchYaw( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
        const XMFLOAT3A translationUnloaded( 4.f, 4.f, 4.f );
        auto translation = XMLoadFloat3A( &translationUnloaded );

        auto transformation = XMMatrixAffineTransformation( scaling, rotationOrigin, rotationQuaternion, translation );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixAffineTransformation );

static void BenchmarkVectorAffineTransformationMatrix( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
        const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
        const QuaternionSimd<Quaternion<float>> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
        const Math::Vector3f translation( 4.f, 4.f, 4.f );

        auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
        Math::Vector3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorAffineTransformationMatrix );

static void BenchmarkVectorXMMatrixAffineTransformation( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        const XMFLOAT3A scalingUnloaded( 1.5f, 2.5f, 1.f );
        auto scaling = XMLoadFloat3A( &scalingUnloaded );
        const XMFLOAT3A rotationOriginUnloaded( 5.f, 5.f, 5.f );
        auto rotationOrigin = XMLoadFloat3A( &rotationOriginUnloaded );
        const auto rotationQuaternion = XMQuaternionRotationRollPitchYaw( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
        const XMFLOAT3A translationUnloaded( 4.f, 4.f, 4.f );
        auto translation = XMLoadFloat3A( &translationUnloaded );

        auto transformation = XMMatrixAffineTransformation( scaling, rotationOrigin, rotationQuaternion, translation );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixAffineTransformation );

static void BenchmarkNormalAffineTransformationMatrix( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
        const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
        const QuaternionSimd<Quaternion<float>> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
        const Math::Vector3f translation( 4.f, 4.f, 4.f );

        auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
        Math::Normal3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkNormalAffineTransformationMatrix );


static void BenchmarkNormalXMMatrixAffineTransformation( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        const XMFLOAT3A scalingUnloaded( 1.5f, 2.5f, 1.f );
        auto scaling = XMLoadFloat3A( &scalingUnloaded );
        const XMFLOAT3A rotationOriginUnloaded( 5.f, 5.f, 5.f );
        auto rotationOrigin = XMLoadFloat3A( &rotationOriginUnloaded );
        const auto rotationQuaternion = XMQuaternionRotationRollPitchYaw( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
        const XMFLOAT3A translationUnloaded( 4.f, 4.f, 4.f );
        auto translation = XMLoadFloat3A( &translationUnloaded );

        auto transformation = XMMatrixAffineTransformation( scaling, rotationOrigin, rotationQuaternion, translation );
        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixAffineTransformation );

static void BenchmarkPointLookTo( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        Point3f cameraPosition( -2.f, 1.f, -3.f );
        Vector3f cameraDirection( 1.5f, 1.5f, 1.5f );
        Vector3f upDirection( 0.f, 1.f, 0.f );

        auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );

        
        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkPointLookTo );

static void BenchmarkPointXMMatrixLookToLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
        XMFLOAT3A cameraDirectionUnloaded( 1.5f, 1.5f, 1.5f );
        XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

        auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
        auto cameraDirection = XMLoadFloat3A( &cameraDirectionUnloaded );
        auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

        auto transformation = XMMatrixLookToLH( cameraPosition, cameraDirection, upDirection );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixLookToLH );

static void BenchmarkVectorLookTo( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        Point3f cameraPosition( -2.f, 1.f, -3.f );
        Vector3f cameraDirection( 1.5f, 1.5f, 1.5f );
        Vector3f upDirection( 0.f, 1.f, 0.f );

        auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );


        Math::Vector3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorLookTo );

static void BenchmarkVectorXMMatrixLookToLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
        XMFLOAT3A cameraDirectionUnloaded( 1.5f, 1.5f, 1.5f );
        XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

        auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
        auto cameraDirection = XMLoadFloat3A( &cameraDirectionUnloaded );
        auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

        auto transformation = XMMatrixLookToLH( cameraPosition, cameraDirection, upDirection );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixLookToLH );

static void BenchmarkNormalLookTo( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        Point3f cameraPosition( -2.f, 1.f, -3.f );
        Vector3f cameraDirection( 1.5f, 1.5f, 1.5f );
        Vector3f upDirection( 0.f, 1.f, 0.f );

        auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );


        Math::Normal3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkNormalLookTo );

static void BenchmarkNormalXMMatrixLookToLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
        XMFLOAT3A cameraDirectionUnloaded( 1.5f, 1.5f, 1.5f );
        XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

        auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
        auto cameraDirection = XMLoadFloat3A( &cameraDirectionUnloaded );
        auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

        auto transformation = XMMatrixLookToLH( cameraPosition, cameraDirection, upDirection );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixLookToLH );

static void BenchmarkPointLookAt( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        Point3f cameraPosition( -2.f, 1.f, -3.f );
        Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
        Vector3f upDirection( 0.f, 1.f, 0.f );

        auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );


        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkPointLookAt );

static void BenchmarkPointXMMatrixLookAtLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
        XMFLOAT3A focusPointUnloaded( 1.5f, 1.5f, 1.5f );
        XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

        auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
        auto focusPoint = XMLoadFloat3A( &focusPointUnloaded );
        auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

        auto transformation = XMMatrixLookAtLH( cameraPosition, focusPoint, upDirection );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixLookAtLH );


static void BenchmarkVectorLookAt( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        Point3f cameraPosition( -2.f, 1.f, -3.f );
        Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
        Vector3f upDirection( 0.f, 1.f, 0.f );

        auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );


        Math::Vector3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorLookAt );

static void BenchmarkVectorXMMatrixLookAtLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
        XMFLOAT3A focusPointUnloaded( 1.5f, 1.5f, 1.5f );
        XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

        auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
        auto focusPoint = XMLoadFloat3A( &focusPointUnloaded );
        auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

        auto transformation = XMMatrixLookAtLH( cameraPosition, focusPoint, upDirection );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixLookAtLH );

static void BenchmarkNormalLookAt( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        Point3f cameraPosition( -2.f, 1.f, -3.f );
        Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
        Vector3f upDirection( 0.f, 1.f, 0.f );

        auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );


        Math::Normal3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkNormalLookAt );

static void BenchmarkNormalXMMatrixLookAtLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
        XMFLOAT3A focusPointUnloaded( 1.5f, 1.5f, 1.5f );
        XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

        auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
        auto focusPoint = XMLoadFloat3A( &focusPointUnloaded );
        auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

        auto transformation = XMMatrixLookAtLH( cameraPosition, focusPoint, upDirection );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixLookAtLH );

static void BenchmarkPointPerspectiveProjection( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        float viewWidth = 1024;
        float viewHeight = 768;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );


        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkPointPerspectiveProjection );

static void BenchmarkPointXMMatrixPerspectiveLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float viewWidth = 1024;
        float viewHeight = 768;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = XMMatrixPerspectiveLH( viewWidth, viewHeight, nearZ, farZ );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixPerspectiveLH );

static void BenchmarkVectorPerspectiveProjection( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        float viewWidth = 1024;
        float viewHeight = 768;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );


        Math::Vector3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorPerspectiveProjection );

static void BenchmarkVectorXMMatrixPerspectiveLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float viewWidth = 1024;
        float viewHeight = 768;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = XMMatrixPerspectiveLH( viewWidth, viewHeight, nearZ, farZ );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixPerspectiveLH );

static void BenchmarkNormalPerspectiveProjection( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        float viewWidth = 1024;
        float viewHeight = 768;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );


        Math::Normal3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorPerspectiveProjection );

static void BenchmarkNormalXMMatrixPerspectiveLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float viewWidth = 1024;
        float viewHeight = 768;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = XMMatrixPerspectiveLH( viewWidth, viewHeight, nearZ, farZ );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixPerspectiveLH );

static void BenchmarkPointPerspectiveFovProjection( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        float fovAngleY = Constants::PiOver4;
        float aspectRatio = 1.4f;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );


        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkPointPerspectiveFovProjection );

static void BenchmarkPointXMMatrixPerspectiveFovLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float fovAngleY = Constants::PiOver4;
        float aspectRatio = 1.4f;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = XMMatrixPerspectiveFovLH( fovAngleY, aspectRatio, nearZ, farZ );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkPointXMMatrixPerspectiveFovLH );

static void BenchmarkVectorPerspectiveFovProjection( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        float fovAngleY = Constants::PiOver4;
        float aspectRatio = 1.4f;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );


        Math::Vector3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Vector3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkVectorPerspectiveFovProjection );

static void BenchmarkVectorXMMatrixPerspectiveFovLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float fovAngleY = Constants::PiOver4;
        float aspectRatio = 1.4f;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = XMMatrixPerspectiveFovLH( fovAngleY, aspectRatio, nearZ, farZ );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkVectorXMMatrixPerspectiveFovLH );

static void BenchmarkNormalPerspectiveFovProjection( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        float fovAngleY = Constants::PiOver4;
        float aspectRatio = 1.4f;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );


        Math::Normal3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Normal3f result = Math::Transform( p1, transformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkNormalPerspectiveFovProjection );

static void BenchmarkNormalXMMatrixPerspectiveFovLH( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float fovAngleY = Constants::PiOver4;
        float aspectRatio = 1.4f;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto transformation = XMMatrixPerspectiveFovLH( fovAngleY, aspectRatio, nearZ, farZ );

        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );
        auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkNormalXMMatrixPerspectiveFovLH );

static void BenchmarkPointProject( benchmark::State& state )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    FloatAngleInRadiansGenerator.Reset( );

    for ( auto _ : state )
    {
        float viewPortX = 0;
        float viewPortY = 0;
        float viewportWidth = 1024;
        float viewportHeight = 768;
        float viewportMinZ = 0.f;
        float viewportMaxZ = 1.f;

        SquareMatrix<float, 4> viewTransformation;

        Point3f cameraPosition( -2.f, 1.f, -3.f );
        Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
        Vector3f upDirection( 0.f, 1.f, 0.f );

        auto worldTransformation = Math::LookAt( cameraPosition, focusPoint, upDirection );

        float fovAngleY = Constants::PiOver4;
        float aspectRatio = 1.4f;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto projection = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );


        Math::Point3f p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        Math::Point3f result = Math::Project( p1.ToSimd( ), viewPortX, viewPortY, viewportWidth, viewportHeight, viewportMinZ, viewportMaxZ, projection, viewTransformation.ToSimd( ), worldTransformation );

        benchmark::DoNotOptimize( result.z );
    }
}
BENCHMARK( BenchmarkPointProject );

static void BenchmarkPointXMVector3Project( benchmark::State& state )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    FloatAngleInRadiansGenerator.Reset( );
    for ( auto _ : state )
    {
        float viewPortX = 0;
        float viewPortY = 0;
        float viewportWidth = 1024;
        float viewportHeight = 768;
        float viewportMinZ = 0.f;
        float viewportMaxZ = 1.f;

        auto viewTransformation = XMMatrixIdentity( );

        XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
        XMFLOAT3A focusPointUnloaded( 1.5f, 1.5f, 1.5f );
        XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

        auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
        auto focusPoint = XMLoadFloat3A( &focusPointUnloaded );
        auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

        auto worldTransformation = XMMatrixLookAtLH( cameraPosition, focusPoint, upDirection );

        float fovAngleY = Constants::PiOver4;
        float aspectRatio = 1.4f;
        float nearZ = Constants::MachineEpsilon;
        float farZ = 1000;

        auto projection = XMMatrixPerspectiveFovLH( fovAngleY, aspectRatio, nearZ, farZ );


        XMFLOAT3 p1( FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ), FloatAngleInRadiansGenerator( ) );
        auto p1Loaded = XMLoadFloat3( &p1 );

        auto p1Transformed = XMVector3Project( p1Loaded, viewPortX, viewPortY, viewportWidth, viewportHeight, viewportMinZ, viewportMaxZ, projection, viewTransformation, worldTransformation );
        XMFLOAT3 p1Stored;
        XMStoreFloat3( &p1Stored, p1Transformed );

        benchmark::DoNotOptimize( p1Stored.z );
    }
}
BENCHMARK( BenchmarkPointXMVector3Project );



#endif