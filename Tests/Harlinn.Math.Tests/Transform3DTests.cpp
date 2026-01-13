/*
    Copyright 2024-2026 Espen Harlinn
 
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
#include "pch.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Util::Test;

BOOST_FIXTURE_TEST_SUITE( Transform3DTests, LocalFixture )

// --run_test=Transform3DTests/PointRotationAxisTest1
BOOST_AUTO_TEST_CASE( PointRotationAxisTest1 )
{
    using Constants = Math::Constants<float>;
    Math::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = Constants::PiOver2;
    auto transformation = Math::RotationAxis( axis, angle );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 2.f, 2.f, -2.f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorRotationAxisTest1
BOOST_AUTO_TEST_CASE( VectorRotationAxisTest1 )
{
    using Constants = Math::Constants<float>;
    Math::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = Constants::PiOver2;
    auto transformation = Math::RotationAxis( axis, angle );
    Math::Vector<float,3> v1( 2.f, 2.f, 2.f );
    Math::Vector<float, 3> expected( 2.f, 2.f, -2.f );
    Math::Vector<float, 3> result = Math::Transform( v1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorXMMatrixRotationAxisTest1
BOOST_AUTO_TEST_CASE( VectorXMMatrixRotationAxisTest1 )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    const XMFLOAT3A axisUnloaded( 0.f, 1.f, 0.f );
    auto axis = XMLoadFloat3A( &axisUnloaded );
    float angle = Constants::PiOver2;
    auto transformation = XMMatrixRotationAxis( axis, angle );
    XMFLOAT3A v1Unloaded( 2.f, 2.f, 2.f );
    auto v1 = XMLoadFloat3A( &v1Unloaded );
    XMFLOAT3A expected( 2.f, 2.f, -2.f );
    auto resultLoaded = XMVector3Transform( v1, transformation );
    XMFLOAT3A result;
    XMStoreFloat3( &result, resultLoaded );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}



// --run_test=Transform3DTests/NormalRotationAxisTest1
BOOST_AUTO_TEST_CASE( NormalRotationAxisTest1 )
{
    using Constants = Math::Constants<float>;
    Math::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = Constants::PiOver2;
    auto transformation = Math::RotationAxis( axis, angle );
    Math::Normal3f n1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 2.f, 2.f, -2.f );
    Math::Normal3f result = Math::Transform( n1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}


// --run_test=Transform3DTests/NormalXMMatrixRotationAxisTest1
BOOST_AUTO_TEST_CASE( NormalXMMatrixRotationAxisTest1 )
{
    using namespace DirectX;
    using Constants = Math::Constants<float>;
    const XMFLOAT3A axisUnloaded( 0.f, 1.f, 0.f );
    auto axis = XMLoadFloat3A( &axisUnloaded );
    float angle = Constants::PiOver2;
    auto transformation = XMMatrixRotationAxis( axis, angle );
    XMFLOAT3A v1Unloaded( 2.f, 2.f, 2.f );
    auto v1 = XMLoadFloat3A( &v1Unloaded );
    XMFLOAT3A expected( 2.f, 2.f, -2.f );
    auto resultLoaded = XMVector3TransformNormal( v1, transformation );
    XMFLOAT3A result;
    XMStoreFloat3( &result, resultLoaded );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}


// --run_test=Transform3DTests/PointTranslationTest1
BOOST_AUTO_TEST_CASE( PointTranslationTest1 )
{
    using Constants = Math::Constants<float>;
    
    float offsetX = 3.f;
    float offsetY = 2.f;
    float offsetZ = 1.f;
    auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 5.f, 4.f, 3.f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorTranslationTest1
BOOST_AUTO_TEST_CASE( VectorTranslationTest1 )
{
    using Constants = Math::Constants<float>;

    float offsetX = 3.f;
    float offsetY = 2.f;
    float offsetZ = 1.f;
    auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
    Math::Vector3f v1( 2.f, 2.f, 2.f );
    Math::Vector3f expected( 5.f, 4.f, 3.f );
    Math::Vector3f result = Math::Transform( v1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorXMMatrixTranslationTest1
BOOST_AUTO_TEST_CASE( VectorXMMatrixTranslationTest1 )
{
    using namespace DirectX;
    float offsetX = 3.f;
    float offsetY = 2.f;
    float offsetZ = 1.f;
    auto transformation = XMMatrixTranslation( offsetX, offsetY, offsetZ );
    XMFLOAT3A v1Unloaded( 2.f, 2.f, 2.f );
    auto v1 = XMLoadFloat3A( &v1Unloaded );
    XMFLOAT3A expected( 5.f, 4.f, 3.f );
    auto resultLoaded = XMVector3Transform( v1, transformation );
    XMFLOAT3A result;
    XMStoreFloat3( &result, resultLoaded );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalTranslationTest1
BOOST_AUTO_TEST_CASE( NormalTranslationTest1 )
{
    using Constants = Math::Constants<float>;

    float offsetX = 3.f;
    float offsetY = 2.f;
    float offsetZ = 1.f;
    auto transformation = Math::Translation( offsetX, offsetY, offsetZ );
    Math::Normal3f n1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 2.f, 2.f, 2.f );
    Math::Normal3f result = Math::Transform( n1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}


// --run_test=Transform3DTests/NormalXMMatrixTranslationTest1
BOOST_AUTO_TEST_CASE( NormalXMMatrixTranslationTest1 )
{
    using namespace DirectX;
    float offsetX = 3.f;
    float offsetY = 2.f;
    float offsetZ = 1.f;
    auto transformation = XMMatrixTranslation( offsetX, offsetY, offsetZ );
    XMFLOAT3A n1Unloaded( 2.f, 2.f, 2.f );
    auto n1 = XMLoadFloat3A( &n1Unloaded );
    XMFLOAT3A expected( 2.f, 2.f, 2.f );
    auto resultLoaded = XMVector3TransformNormal( n1, transformation );
    XMFLOAT3A result;
    XMStoreFloat3( &result, resultLoaded );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}




// --run_test=Transform3DTests/PointScalingTest1
BOOST_AUTO_TEST_CASE( PointScalingTest1 )
{
    using Constants = Math::Constants<float>;

    float scalingX = 3.f;
    float scalingY = 2.f;
    float scalingZ = 1.f;
    auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 6.f, 4.f, 2.f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorScalingTest1
BOOST_AUTO_TEST_CASE( VectorScalingTest1 )
{
    using Constants = Math::Constants<float>;

    float scalingX = 3.f;
    float scalingY = 2.f;
    float scalingZ = 1.f;
    auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
    Math::Vector3f v1( 2.f, 2.f, 2.f );
    Math::Vector3f expected( 6.f, 4.f, 2.f );
    Math::Vector3f result = Math::Transform( v1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorXMMatrixScalingTest1
BOOST_AUTO_TEST_CASE( VectorXMMatrixScalingTest1 )
{
    using namespace DirectX;
    float scalingX = 3.f;
    float scalingY = 2.f;
    float scalingZ = 1.f;
    auto transformation = XMMatrixScaling( scalingX, scalingY, scalingZ );
    XMFLOAT3A v1Unloaded( 2.f, 2.f, 2.f );
    auto v1 = XMLoadFloat3A( &v1Unloaded );
    XMFLOAT3A expected( 6.f, 4.f, 2.f );
    auto resultLoaded = XMVector3Transform( v1, transformation );
    XMFLOAT3A result;
    XMStoreFloat3( &result, resultLoaded );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}


// --run_test=Transform3DTests/NormalScalingTest1
BOOST_AUTO_TEST_CASE( NormalScalingTest1 )
{
    using Constants = Math::Constants<float>;

    float scalingX = 3.f;
    float scalingY = 2.f;
    float scalingZ = 1.f;
    auto transformation = Math::Scaling( scalingX, scalingY, scalingZ );
    Math::Normal3f n1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 6.f, 4.f, 2.f );
    Math::Normal3f result = Math::Transform( n1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalXMMatrixScalingTest1
BOOST_AUTO_TEST_CASE( NormalXMMatrixScalingTest1 )
{
    using namespace DirectX;
    float scalingX = 3.f;
    float scalingY = 2.f;
    float scalingZ = 1.f;
    auto transformation = XMMatrixScaling( scalingX, scalingY, scalingZ );
    XMFLOAT3A v1Unloaded( 2.f, 2.f, 2.f );
    auto v1 = XMLoadFloat3A( &v1Unloaded );
    XMFLOAT3A expected( 6.f, 4.f, 2.f );
    auto resultLoaded = XMVector3TransformNormal( v1, transformation );
    XMFLOAT3A result;
    XMStoreFloat3( &result, resultLoaded );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}



// --run_test=Transform3DTests/PointTransformationMatrixTest1
BOOST_AUTO_TEST_CASE( PointTransformationMatrixTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    const Point3f scalingOrigin( 10.f, 10.f, 10.f );
    const Quaternion<float> scalingOrientationQuaternion( Constants::Pi * 0.6f, Constants::Pi * 0.6f, Constants::Pi * 0.6f );
    const Math::Vector<float, 3> scaling(.8f, .8f, .8f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector<float, 3> translation( 4.f, 4.f, 4.f );

    auto transformation = Math::TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 7.23640394f, 8.98319530f, 7.33583355f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = AllEqual( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointXMMatrixTransformationTest2
BOOST_AUTO_TEST_CASE( PointXMMatrixTransformationTest2 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

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
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );
    XMFLOAT3 expected( 7.23640394f, 8.98319530f, 7.33583355f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );

}



// --run_test=Transform3DTests/VectorTransformationMatrixTest1
BOOST_AUTO_TEST_CASE( VectorTransformationMatrixTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    const Point3f scalingOrigin( 10.f, 10.f, 10.f );
    const Quaternion<float> scalingOrientationQuaternion( Constants::Pi * 0.6f, Constants::Pi * 0.6f, Constants::Pi * 0.6f );
    const Math::Vector<float, 3> scaling( .8f, .8f, .8f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector<float, 3> translation( 4.f, 4.f, 4.f );

    auto transformation = Math::TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Vector3f v1( 2.f, 2.f, 2.f );
    Math::Vector3f expected( 7.23640394f, 8.98319530f, 7.33583355f );
    Math::Vector3f result = Math::Transform( v1, transformation );
    auto equal = AllEqual( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorXMMatrixTransformationTest2
BOOST_AUTO_TEST_CASE( VectorXMMatrixTransformationTest2 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

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
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );
    XMFLOAT3 expected( 7.23640394f, 8.98319530f, 7.33583355f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );

}

// --run_test=Transform3DTests/NormalTransformationMatrixTest1
BOOST_AUTO_TEST_CASE( NormalTransformationMatrixTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    const Point3f scalingOrigin( 10.f, 10.f, 10.f );
    const Quaternion<float> scalingOrientationQuaternion( Constants::Pi * 0.6f, Constants::Pi * 0.6f, Constants::Pi * 0.6f );
    const Math::Vector<float, 3> scaling( .8f, .8f, .8f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector<float, 3> translation( 4.f, 4.f, 4.f );

    auto transformation = Math::TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Normal3f n1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 2.01553679f, 0.0192041993f, 1.90190506f );
    Math::Normal3f result = Math::Transform( n1, transformation );
    auto equal = AllEqual( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalXMMatrixTransformationTest2
BOOST_AUTO_TEST_CASE( NormalXMMatrixTransformationTest2 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

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
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );
    XMFLOAT3 expected( 2.01553679f, 0.0192041993f, 1.90190506f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );

}


// --run_test=Transform3DTests/PointAffineTransformationMatrixTest1
BOOST_AUTO_TEST_CASE( PointAffineTransformationMatrixTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;


    const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector3f translation( 4.f, 4.f, 4.f );

    auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f expected( 5.82341528f, 10.4759951f, 8.14516068f );
    Math::Point3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointXMMatrixAffineTransformationTest1
BOOST_AUTO_TEST_CASE( PointXMMatrixAffineTransformationTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    
    const XMFLOAT3A scalingUnloaded( 1.5f, 2.5f, 1.f );
    auto scaling = XMLoadFloat3A( &scalingUnloaded );
    const XMFLOAT3A rotationOriginUnloaded( 5.f, 5.f, 5.f );
    auto rotationOrigin = XMLoadFloat3A( &rotationOriginUnloaded );
    const auto rotationQuaternion = XMQuaternionRotationRollPitchYaw( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const XMFLOAT3A translationUnloaded( 4.f, 4.f, 4.f );
    auto translation = XMLoadFloat3A( &translationUnloaded );

    auto transformation = XMMatrixAffineTransformation( scaling, rotationOrigin, rotationQuaternion, translation );
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );
    XMFLOAT3 expected( 5.82341528f, 10.4759951f, 8.14516068f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorAffineTransformationMatrixTest1
BOOST_AUTO_TEST_CASE( VectorAffineTransformationMatrixTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;


    const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector3f translation( 4.f, 4.f, 4.f );

    auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Vector3f p1( 2.f, 2.f, 2.f );
    Math::Vector3f expected( 5.82341528f, 10.4759951f, 8.14516068f );
    Math::Vector3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}


// --run_test=Transform3DTests/VectorXMMatrixAffineTransformationTest1
BOOST_AUTO_TEST_CASE( VectorXMMatrixAffineTransformationTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;


    const XMFLOAT3A scalingUnloaded( 1.5f, 2.5f, 1.f );
    auto scaling = XMLoadFloat3A( &scalingUnloaded );
    const XMFLOAT3A rotationOriginUnloaded( 5.f, 5.f, 5.f );
    auto rotationOrigin = XMLoadFloat3A( &rotationOriginUnloaded );
    const auto rotationQuaternion = XMQuaternionRotationRollPitchYaw( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const XMFLOAT3A translationUnloaded( 4.f, 4.f, 4.f );
    auto translation = XMLoadFloat3A( &translationUnloaded );

    auto transformation = XMMatrixAffineTransformation( scaling, rotationOrigin, rotationQuaternion, translation );
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );
    XMFLOAT3 expected( 5.82341528f, 10.4759951f, 8.14516068f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalAffineTransformationMatrixTest1
BOOST_AUTO_TEST_CASE( NormalAffineTransformationMatrixTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;


    const Math::Vector3f scaling( 1.5f, 2.5f, 1.f );
    const Math::Point3f rotationOrigin( 5.f, 5.f, 5.f );
    const Quaternion<float> rotationQuaternion( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const Math::Vector3f translation( 4.f, 4.f, 4.f );

    auto transformation = Math::AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation );
    Math::Normal3f p1( 2.f, 2.f, 2.f );
    Math::Normal3f expected( 3.12196779f, 1.53600752f, 5.08861494f );
    Math::Normal3f result = Math::Transform( p1, transformation );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalXMMatrixAffineTransformationTest1
BOOST_AUTO_TEST_CASE( NormalXMMatrixAffineTransformationTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    const XMFLOAT3A scalingUnloaded( 1.5f, 2.5f, 1.f );
    auto scaling = XMLoadFloat3A( &scalingUnloaded );
    const XMFLOAT3A rotationOriginUnloaded( 5.f, 5.f, 5.f );
    auto rotationOrigin = XMLoadFloat3A( &rotationOriginUnloaded );
    const auto rotationQuaternion = XMQuaternionRotationRollPitchYaw( Constants::Pi * 0.3f, Constants::Pi * 0.3f, Constants::Pi * 0.3f );
    const XMFLOAT3A translationUnloaded( 4.f, 4.f, 4.f );
    auto translation = XMLoadFloat3A( &translationUnloaded );

    auto transformation = XMMatrixAffineTransformation( scaling, rotationOrigin, rotationQuaternion, translation );
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );
    XMFLOAT3 expected( 3.12196779f, 1.53600752f, 5.08861494f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}


// --run_test=Transform3DTests/PointLookToTest1
BOOST_AUTO_TEST_CASE( PointLookToTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition(-2.f, 1.f, -3.f);
    Vector3f cameraDirection(1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );
    

    auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f result = Math::Transform( p1, transformation );

    Math::Point3f expected( -0.707106709f, -2.85773802f, 5.77350330f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointXMMatrixLookToLHTest1
BOOST_AUTO_TEST_CASE( PointXMMatrixLookToLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
    XMFLOAT3A cameraDirectionUnloaded( 1.5f, 1.5f, 1.5f );
    XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

    auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
    auto cameraDirection = XMLoadFloat3A( &cameraDirectionUnloaded );
    auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

    auto transformation = XMMatrixLookToLH( cameraPosition, cameraDirection, upDirection );
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( -0.707106709f, -2.85773802f, 5.77350330f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorLookToTest1
BOOST_AUTO_TEST_CASE( VectorLookToTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f cameraDirection( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );
    Math::Vector3f p1( 2.f, 2.f, 2.f );
    Math::Vector3f result = Math::Transform( p1, transformation );

    Math::Vector3f expected( -0.707106709f, -2.85773802f, 5.77350330f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorXMMatrixLookToLHTest1
BOOST_AUTO_TEST_CASE( VectorXMMatrixLookToLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
    XMFLOAT3A cameraDirectionUnloaded( 1.5f, 1.5f, 1.5f );
    XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

    auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
    auto cameraDirection = XMLoadFloat3A( &cameraDirectionUnloaded );
    auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

    auto transformation = XMMatrixLookToLH( cameraPosition, cameraDirection, upDirection );
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( -0.707106709f, -2.85773802f, 5.77350330f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalLookToTest1
BOOST_AUTO_TEST_CASE( NormalLookToTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f cameraDirection( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookTo( cameraPosition, cameraDirection, upDirection );
    Math::Normal3f p1( 10.f, 10.f, 10.f );
    Math::Normal3f result = Math::Transform( p1, transformation );

    Math::Normal3f expected( -1.19209290e-07f, -2.38418579e-07f, 17.3205090f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalXMMatrixLookToLHTest1
BOOST_AUTO_TEST_CASE( NormalXMMatrixLookToLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
    XMFLOAT3A cameraDirectionUnloaded( 1.5f, 1.5f, 1.5f );
    XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

    auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
    auto cameraDirection = XMLoadFloat3A( &cameraDirectionUnloaded );
    auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

    auto transformation = XMMatrixLookToLH( cameraPosition, cameraDirection, upDirection );
    XMFLOAT3 p1( 10.f, 10.f, 10.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( -1.19209290e-07f, -2.38418579e-07f, 17.3205090f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointLookAtTest1
BOOST_AUTO_TEST_CASE( PointLookAtTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );
    Math::Point3f p1( 2.f, 2.f, 2.f );
    Math::Point3f result = Math::Transform( p1, transformation );

    Math::Point3f expected( 0.0877057314f, 0.436784744f, 6.46540976f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointXMMatrixLookAtLHTest1
BOOST_AUTO_TEST_CASE( PointXMMatrixLookAtLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
    XMFLOAT3A focusPointUnloaded( 1.5f, 1.5f, 1.5f );
    XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

    auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
    auto focusPoint = XMLoadFloat3A( &focusPointUnloaded );
    auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

    auto transformation = XMMatrixLookAtLH( cameraPosition, focusPoint, upDirection );
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 0.0877057314f, 0.436784744f, 6.46540976f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorLookAtTest1
BOOST_AUTO_TEST_CASE( VectorLookAtTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );
    Math::Vector3f p1( 2.f, 2.f, 2.f );
    Math::Vector3f result = Math::Transform( p1, transformation );

    Math::Vector3f expected( 0.0877057314f, 0.436784744f, 6.46540976f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorXMMatrixLookAtLHTest1
BOOST_AUTO_TEST_CASE( VectorXMMatrixLookAtLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
    XMFLOAT3A focusPointUnloaded( 1.5f, 1.5f, 1.5f );
    XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

    auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
    auto focusPoint = XMLoadFloat3A( &focusPointUnloaded );
    auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

    auto transformation = XMMatrixLookAtLH( cameraPosition, focusPoint, upDirection );
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 0.0877057314f, 0.436784744f, 6.46540976f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalLookAtTest1
BOOST_AUTO_TEST_CASE( NormalLookAtTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    Point3f cameraPosition( -2.f, 1.f, -3.f );
    Vector3f focusPoint( 1.5f, 1.5f, 1.5f );
    Vector3f upDirection( 0.f, 1.f, 0.f );


    auto transformation = Math::LookAt( cameraPosition, focusPoint, upDirection );
    Math::Normal3f p1( 2.f, 2.f, 2.f );
    Math::Normal3f result = Math::Transform( p1, transformation );

    Math::Normal3f expected( 0.350823164f, 1.74713910f, 2.97059369f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalXMMatrixLookAtLHTest1
BOOST_AUTO_TEST_CASE( NormalXMMatrixLookAtLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    XMFLOAT3A cameraPositionUnloaded( -2.f, 1.f, -3.f );
    XMFLOAT3A focusPointUnloaded( 1.5f, 1.5f, 1.5f );
    XMFLOAT3A upDirectionUnloaded( 0.f, 1.f, 0.f );

    auto cameraPosition = XMLoadFloat3A( &cameraPositionUnloaded );
    auto focusPoint = XMLoadFloat3A( &focusPointUnloaded );
    auto upDirection = XMLoadFloat3A( &upDirectionUnloaded );

    auto transformation = XMMatrixLookAtLH( cameraPosition, focusPoint, upDirection );
    XMFLOAT3 p1( 2.f, 2.f, 2.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 0.350823164f, 1.74713910f, 2.97059369f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointPerspectiveProjectionTest1
BOOST_AUTO_TEST_CASE( PointPerspectiveProjectionTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float viewWidth = 1024; 
    float viewHeight = 768; 
    float nearZ = Constants::MachineEpsilon; 
    float farZ = 1000;

    auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );
    Math::Point3f p1( 200.f, 300.f, 300.f );
    Math::Point3f result = Math::Transform( p1, transformation );

    Math::Point3f expected( 7.76102169e-11f, 1.55220434e-10f, 1.00000000f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointXMMatrixPerspectiveLHTest1
BOOST_AUTO_TEST_CASE( PointXMMatrixPerspectiveLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    float viewWidth = 1024;
    float viewHeight = 768;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = XMMatrixPerspectiveLH( viewWidth, viewHeight, nearZ, farZ );
    XMFLOAT3 p1( 200.f, 300.f, 300.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 7.76102169e-11f, 1.55220434e-10f, 1.00000000f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorPerspectiveProjectionTest1
BOOST_AUTO_TEST_CASE( VectorPerspectiveProjectionTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float viewWidth = 1024;
    float viewHeight = 768;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );
    Math::Vector3f p1( 200.f, 300.f, 300.f );
    Math::Vector3f result = Math::Transform( p1, transformation );

    Math::Vector3f expected( 2.32830644e-08f, 4.65661287e-08f, 300.000000f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorXMMatrixPerspectiveLHTest1
BOOST_AUTO_TEST_CASE( VectorXMMatrixPerspectiveLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    float viewWidth = 1024;
    float viewHeight = 768;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = XMMatrixPerspectiveLH( viewWidth, viewHeight, nearZ, farZ );
    XMFLOAT3 p1( 200.f, 300.f, 300.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 2.32830644e-08f, 4.65661287e-08f, 300.000000f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalPerspectiveProjectionTest1
BOOST_AUTO_TEST_CASE( NormalPerspectiveProjectionTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float viewWidth = 1024;
    float viewHeight = 768;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveProjection( viewWidth, viewHeight, nearZ, farZ );
    Math::Normal3f p1( 200.f, 300.f, 300.f );
    Math::Normal3f result = Math::Transform( p1, transformation );

    Math::Normal3f expected( 2.32830644e-08f, 4.65661287e-08f, 300.000000f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalXMMatrixPerspectiveLHTest1
BOOST_AUTO_TEST_CASE( NormalXMMatrixPerspectiveLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    float viewWidth = 1024;
    float viewHeight = 768;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = XMMatrixPerspectiveLH( viewWidth, viewHeight, nearZ, farZ );
    XMFLOAT3 p1( 200.f, 300.f, 300.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 2.32830644e-08f, 4.65661287e-08f, 300.000000f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointPerspectiveProjectionFovTest1
BOOST_AUTO_TEST_CASE( PointPerspectiveProjectionFovTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );
    Math::Point3f p1( 200.f, 300.f, 300.f );
    Math::Point3f result = Math::Transform( p1, transformation );

    Math::Point3f expected( 1.14962542f, 2.41421342f, 1.00000000f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/PointXMMatrixPerspectiveFovLHTest1
BOOST_AUTO_TEST_CASE( PointXMMatrixPerspectiveFovLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = XMMatrixPerspectiveFovLH( fovAngleY, aspectRatio, nearZ, farZ );
    XMFLOAT3 p1( 200.f, 300.f, 300.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformCoord( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 1.14962542f, 2.41421342f, 1.00000000f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorPerspectiveProjectionFovTest1
BOOST_AUTO_TEST_CASE( VectorPerspectiveProjectionFovTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );
    Math::Vector3f p1( 200.f, 300.f, 300.f );
    Math::Vector3f result = Math::Transform( p1, transformation );

    Math::Vector3f expected( 344.887634f, 724.264038f, 300.f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/VectorXMMatrixPerspectiveFovLHTest1
BOOST_AUTO_TEST_CASE( VectorXMMatrixPerspectiveFovLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = XMMatrixPerspectiveFovLH( fovAngleY, aspectRatio, nearZ, farZ );
    XMFLOAT3 p1( 200.f, 300.f, 300.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3Transform( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 344.887634f, 724.264038f, 300.f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}


// --run_test=Transform3DTests/NormalPerspectiveProjectionFovTest1
BOOST_AUTO_TEST_CASE( NormalPerspectiveProjectionFovTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = Math::PerspectiveFovProjection( fovAngleY, aspectRatio, nearZ, farZ );
    Math::Normal3f p1( 200.f, 300.f, 300.f );
    Math::Normal3f result = Math::Transform( p1, transformation );

    Math::Normal3f expected( 344.887634f, 724.264038f, 300.f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=Transform3DTests/NormalXMMatrixPerspectiveFovLHTest1
BOOST_AUTO_TEST_CASE( NormalXMMatrixPerspectiveFovLHTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

    float fovAngleY = Constants::PiOver4;
    float aspectRatio = 1.4f;
    float nearZ = Constants::MachineEpsilon;
    float farZ = 1000;

    auto transformation = XMMatrixPerspectiveFovLH( fovAngleY, aspectRatio, nearZ, farZ );
    XMFLOAT3 p1( 200.f, 300.f, 300.f );
    auto p1Loaded = XMLoadFloat3( &p1 );
    auto p1Transformed = XMVector3TransformNormal( p1Loaded, transformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 344.887634f, 724.264038f, 300.f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}


// --run_test=Transform3DTests/PointProjectTest1
BOOST_AUTO_TEST_CASE( PointProjectTest1 )
{
    using namespace Math;
    using Constants = Math::Constants<float>;

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


    Math::Point3f p1( 200.f, 300.f, 300.f );
    Math::Point3f result = Math::Project( p1.ToSimd(), viewPortX, viewPortY, viewportWidth, viewportHeight, viewportMinZ, viewportMaxZ, projection, viewTransformation.ToSimd( ), worldTransformation );

    Math::Point3f expected( 451.515869f, -251.981598f, 1.f );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}




// --run_test=Transform3DTests/PointXMVector3ProjectLHTest1
BOOST_AUTO_TEST_CASE( PointXMVector3ProjectTest1 )
{
    using Constants = Math::Constants<float>;
    using namespace DirectX;

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


    XMFLOAT3 p1( 200.f, 300.f, 300.f );
    auto p1Loaded = XMLoadFloat3( &p1 );

    auto p1Transformed = XMVector3Project( p1Loaded, viewPortX, viewPortY, viewportWidth, viewportHeight, viewportMinZ, viewportMaxZ, projection, viewTransformation, worldTransformation );
    XMFLOAT3 p1Stored;
    XMStoreFloat3( &p1Stored, p1Transformed );

    XMFLOAT3 expected( 451.515869f, -251.981598f, 1.f );
    auto equal = Equal( expected, p1Stored );
    BOOST_CHECK( equal );
}





BOOST_AUTO_TEST_SUITE_END( )