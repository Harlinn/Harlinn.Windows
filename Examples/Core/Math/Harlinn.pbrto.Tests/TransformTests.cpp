#include "pch.h"
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

using namespace Harlinn::Common::Core;
using namespace Harlinn::Util::Test;

BOOST_FIXTURE_TEST_SUITE( TransformTests, LocalFixture )


// --run_test=TransformTests/PbrtTranslateTransformPointTest1
BOOST_AUTO_TEST_CASE( PbrtTranslateTransformPointTest1 )
{
    pbrt::Vector3f translation( 2.f, 3.f, 4.f );
    auto transformation = pbrt::Translate( translation );
    pbrt::Point3f p1( 2.f, 2.f, 2.f );
    pbrt::Point3f expected( 4.f, 5.f, 6.f );
    pbrt::Point3f result = transformation( p1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTranslateTransformPointTest1
BOOST_AUTO_TEST_CASE( PbrtoTranslateTransformPointTest1 )
{
    pbrto::Vector3f translation( 2.f, 3.f, 4.f );
    auto transformation = pbrto::Translate( translation );
    pbrto::Point3f p1( 2.f, 2.f, 2.f );
    pbrto::Point3f expected( 4.f, 5.f, 6.f );
    pbrto::Point3f result = transformation( p1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtTranslateTransformVectorTest1
BOOST_AUTO_TEST_CASE( PbrtTranslateTransformVectorTest1 )
{
    pbrt::Vector3f translation( 2.f, 3.f, 4.f );
    auto transformation = pbrt::Translate( translation );
    pbrt::Vector3f v1( 2.f, 2.f, 2.f );
    pbrt::Vector3f expected( 2.f, 2.f, 2.f );
    pbrt::Vector3f result = transformation( v1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTranslateTransformVectorTest1
BOOST_AUTO_TEST_CASE( PbrtoTranslateTransformVectorTest1 )
{
    pbrto::Vector3f translation( 2.f, 3.f, 4.f );
    auto transformation = pbrto::Translate( translation );
    pbrto::Vector3f v1( 2.f, 2.f, 2.f );
    pbrto::Vector3f expected( 2.f, 2.f, 2.f );
    pbrto::Vector3f result = transformation( v1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtTranslateTransformNormalTest1
BOOST_AUTO_TEST_CASE( PbrtTranslateTransformNormalTest1 )
{
    pbrt::Vector3f translation( 2.f, 3.f, 4.f );
    auto transformation = pbrt::Translate( translation );
    pbrt::Normal3f n1( 2.f, 2.f, 2.f );
    pbrt::Normal3f expected( 2.f, 2.f, 2.f );
    pbrt::Normal3f result = transformation( n1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTranslateTransformNormalTest1
BOOST_AUTO_TEST_CASE( PbrtoTranslateTransformNormalTest1 )
{
    pbrto::Vector3f translation( 2.f, 3.f, 4.f );
    auto transformation = pbrto::Translate( translation );
    pbrto::Normal3f n1( 2.f, 2.f, 2.f );
    pbrto::Normal3f expected( 2.f, 2.f, 2.f );
    pbrto::Normal3f result = transformation( n1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}



////

// --run_test=TransformTests/PbrtRotateTransformPointTest1
BOOST_AUTO_TEST_CASE( PbrtRotateTransformPointTest1 )
{
    pbrt::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = 45.f;
    auto transformation = pbrt::Rotate( angle, axis  );
    pbrt::Point3f p1( 2.f, 2.f, 2.f );
    pbrt::Point3f expected( 2.82842708f, 2.f, 0.f );
    pbrt::Point3f result = transformation( p1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoRotateTransformPointTest1
BOOST_AUTO_TEST_CASE( PbrtoRotateTransformPointTest1 )
{
    pbrto::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = 45.f;
    auto transformation = pbrto::Rotate( angle, axis );
    pbrto::Point3f p1( 2.f, 2.f, 2.f );
    pbrto::Point3f expected( 2.82842708f, 2.f, 0.f );
    pbrto::Point3f result = transformation( p1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtRotateTransformVectorTest1
BOOST_AUTO_TEST_CASE( PbrtRotateTransformVectorTest1 )
{
    pbrt::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = 45.f;
    auto transformation = pbrt::Rotate( angle, axis );
    pbrt::Vector3f v1( 2.f, 2.f, 2.f );
    pbrt::Vector3f expected( 2.82842708f, 2.f, 0.f );
    pbrt::Vector3f result = transformation( v1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoRotateTransformVectorTest1
BOOST_AUTO_TEST_CASE( PbrtoRotateTransformVectorTest1 )
{
    pbrto::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = 45.f;
    auto transformation = pbrto::Rotate( angle, axis );
    pbrto::Vector3f v1( 2.f, 2.f, 2.f );
    pbrto::Vector3f expected( 2.82842708f, 2.f, 0.f );
    pbrto::Vector3f result = transformation( v1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtRotateTransformNormalTest1
BOOST_AUTO_TEST_CASE( PbrtRotateTransformNormalTest1 )
{
    pbrt::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = 45.f;
    auto transformation = pbrt::Rotate( angle, axis );
    pbrt::Normal3f n1( 2.f, 2.f, 2.f );
    pbrt::Normal3f expected( 2.82842708f, 2.f, 0.f );
    pbrt::Normal3f result = transformation( n1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoRotateTransformNormalTest1
BOOST_AUTO_TEST_CASE( PbrtoRotateTransformNormalTest1 )
{
    pbrto::Vector3f axis( 0.f, 1.f, 0.f );
    float angle = 45.f;
    auto transformation = pbrto::Rotate( angle, axis );
    pbrto::Normal3f n1( 2.f, 2.f, 2.f );
    pbrto::Normal3f expected( 2.82842708f, 2.f, 0.f );
    pbrto::Normal3f result = transformation( n1 );
    auto equal = Equal( expected, result );

    BOOST_CHECK( equal );
}


////

// --run_test=TransformTests/PbrtScaleTransformPointTest1
BOOST_AUTO_TEST_CASE( PbrtScaleTransformPointTest1 )
{
    auto transformation = pbrt::Scale( 1.2f, 1.3f, 1.25f );
    pbrt::Point3f p1( 2.f, 2.f, 2.f );
    pbrt::Point3f expected( 2.40000010f, 2.59999990f, 2.50000000f );
    pbrt::Point3f result = transformation( p1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoScaleTransformPointTest1
BOOST_AUTO_TEST_CASE( PbrtoScaleTransformPointTest1 )
{
    auto transformation = pbrto::Scale( 1.2f, 1.3f, 1.25f );
    pbrto::Point3f p1( 2.f, 2.f, 2.f );
    pbrto::Point3f expected( 2.40000010f, 2.59999990f, 2.50000000f );
    pbrto::Point3f result = transformation( p1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtScaleTransformVectorTest1
BOOST_AUTO_TEST_CASE( PbrtScaleTransformVectorTest1 )
{
    auto transformation = pbrt::Scale( 1.2f, 1.3f, 1.25f );
    pbrt::Vector3f v1( 2.f, 2.f, 2.f );
    pbrt::Vector3f expected( 2.40000010f, 2.59999990f, 2.50000000f );
    pbrt::Vector3f result = transformation( v1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoScaleTransformVectorTest1
BOOST_AUTO_TEST_CASE( PbrtoScaleTransformVectorTest1 )
{
    auto transformation = pbrto::Scale( 1.2f, 1.3f, 1.25f );
    pbrto::Vector3f v1( 2.f, 2.f, 2.f );
    pbrto::Vector3f expected( 2.40000010f, 2.59999990f, 2.50000000f );
    pbrto::Vector3f result = transformation( v1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtScaleTransformNormalTest1
BOOST_AUTO_TEST_CASE( PbrtScaleTransformNormalTest1 )
{
    auto transformation = pbrt::Scale( 1.2f, 1.3f, 1.25f );
    pbrt::Normal3f n1( 2.f, 2.f, 2.f );
    pbrt::Normal3f expected( 1.66666663f, 1.53846157f, 1.60000002f );
    pbrt::Normal3f result = transformation( n1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoScaleTransformNormalTest1
BOOST_AUTO_TEST_CASE( PbrtoScaleTransformNormalTest1 )
{
    auto transformation = pbrto::Scale( 1.2f, 1.3f, 1.25f );
    pbrto::Normal3f n1( 2.f, 2.f, 2.f );
    pbrto::Normal3f expected( 1.66666663f, 1.53846157f, 1.60000002f );
    pbrto::Normal3f result = transformation( n1 );
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}



BOOST_AUTO_TEST_SUITE_END( )