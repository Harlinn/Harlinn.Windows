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

#include <pbrto/util/rng.h>
#include <pbrto/util/sampling.h>
#include <pbrto/util/NewSampling.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Util::Test;

static pbrt::Transform RandomTransform( pbrt::RNG& rng )
{
    pbrt::Transform t;
    auto r = [ &rng ]( ) { return -10. + 20. * rng.Uniform<float>( ); };
    for ( int i = 0; i < 10; ++i )
    {
        switch ( rng.Uniform<uint32_t>( 3 ) )
        {
            case 0:
                t = t * pbrt::Scale( std::abs( r( ) ), std::abs( r( ) ), std::abs( r( ) ) );
                break;
            case 1:
                t = t * pbrt::Translate( pbrt::Vector3f( r( ), r( ), r( ) ) );
                break;
            case 2:
                t = t * pbrt::Rotate( r( ) * 20., pbrt::SampleUniformSphere( pbrt::Point2f( rng.Uniform<float>( ),
                    rng.Uniform<float>( ) ) ) );
                break;
        }
    }
    return t;
}

inline pbrto::Transform ConvertTransform( const pbrt::Transform& transform )
{
    pbrt::SquareMatrix<4> pm = transform.GetMatrix( );
    pbrto::SquareMatrix<4> m(
        pm[ 0 ][ 0 ], pm[ 0 ][ 1 ], pm[ 0 ][ 2 ], pm[ 0 ][ 3 ],
        pm[ 1 ][ 0 ], pm[ 1 ][ 1 ], pm[ 1 ][ 2 ], pm[ 1 ][ 3 ],
        pm[ 2 ][ 0 ], pm[ 2 ][ 1 ], pm[ 2 ][ 2 ], pm[ 2 ][ 3 ],
        pm[ 3 ][ 0 ], pm[ 3 ][ 1 ], pm[ 3 ][ 2 ], pm[ 3 ][ 3 ] );
    return pbrto::Transform( m );
}

inline pbrt::Transform ConvertTransform( const pbrto::Transform& transform )
{
    pbrto::SquareMatrix<4> pm = transform.GetMatrix( );
    pbrt::SquareMatrix<4> m(
        pm[ 0 ][ 0 ], pm[ 0 ][ 1 ], pm[ 0 ][ 2 ], pm[ 0 ][ 3 ],
        pm[ 1 ][ 0 ], pm[ 1 ][ 1 ], pm[ 1 ][ 2 ], pm[ 1 ][ 3 ],
        pm[ 2 ][ 0 ], pm[ 2 ][ 1 ], pm[ 2 ][ 2 ], pm[ 2 ][ 3 ],
        pm[ 3 ][ 0 ], pm[ 3 ][ 1 ], pm[ 3 ][ 2 ], pm[ 3 ][ 3 ] );
    return pbrt::Transform( m );
}



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

// --run_test=TransformTests/PbrtTransformPoint3fiTest1
BOOST_AUTO_TEST_CASE( PbrtTransformPoint3fiTest1 )
{
    pbrt::SquareMatrix<4> m( 
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 1.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 1.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrt::Point3fi p( 
        pbrt::Interval( -30.2945175f, -30.2945175f ),
        pbrt::Interval( -154.808182f, -154.808182f ),
        pbrt::Interval( -931.506165f, -931.506165f ) );

    pbrt::Point3fi expected(
        pbrt::Interval( -30.2945251f, -30.2945099f ),
        pbrt::Interval( -154.808228f, -154.808136f ),
        pbrt::Interval( -931.506409f, -931.505920f ) );

    pbrt::Transform t( m );
    auto hasScale = t.HasScale( );
    BOOST_CHECK_NE(true, hasScale );

    pbrt::Point3fi result = t( p );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTransformPoint3fiTest1
BOOST_AUTO_TEST_CASE( PbrtoTransformPoint3fiTest1 )
{
    pbrto::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 1.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 1.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrto::Point3fi p(
        pbrto::Interval( -30.2945175f, -30.2945175f ),
        pbrto::Interval( -154.808182f, -154.808182f ),
        pbrto::Interval( -931.506165f, -931.506165f ) );

    pbrto::Point3fi expected(
        pbrto::Interval( -30.2945251f, -30.2945099f ),
        pbrto::Interval( -154.808228f, -154.808136f ),
        pbrto::Interval( -931.506409f, -931.505920f ) );

    pbrto::Transform t( m );
    auto hasScale = t.HasScale( );
    BOOST_CHECK_NE( true, hasScale );

    pbrto::Point3fi result = t( p );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtTransformPoint3fiTest2
BOOST_AUTO_TEST_CASE( PbrtTransformPoint3fiTest2 )
{
    pbrt::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.998598754f, -0.0529195182f, 0.00000000f,
        0.00000000f, -0.0529195182f, -0.998598754f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrt::Point3fi p(
        pbrt::Interval( -30.2945175f, -30.2945175f ),
        pbrt::Interval( -154.808182f, -154.808182f ),
        pbrt::Interval( -931.506165f, -931.506165f ) );

    pbrt::Point3fi expected(
        pbrt::Interval( -30.2945251f, -30.2945099f ),
        pbrt::Interval( -105.296448f, -105.296356f ),
        pbrt::Interval( 938.393005f, 938.393494f ) );

    pbrt::Transform t( m );
    auto hasScale = t.HasScale( );
    BOOST_CHECK_NE( true, hasScale );

    pbrt::Point3fi result = t( p );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTransformPoint3fiTest2
BOOST_AUTO_TEST_CASE( PbrtoTransformPoint3fiTest2 )
{
    pbrto::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.998598754f, -0.0529195182f, 0.00000000f,
        0.00000000f, -0.0529195182f, -0.998598754f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrto::Point3fi p(
        pbrto::Interval( -30.2945175f, -30.2945175f ),
        pbrto::Interval( -154.808182f, -154.808182f ),
        pbrto::Interval( -931.506165f, -931.506165f ) );

    pbrto::Point3fi expected(
        pbrto::Interval( -30.2945251f, -30.2945099f ),
        pbrto::Interval( -105.296448f, -105.296356f ),
        pbrto::Interval( 938.393005f, 938.393494f ) );

    pbrto::Transform t( m );
    auto hasScale = t.HasScale( );
    BOOST_CHECK_NE( true, hasScale );

    pbrto::Point3fi result = t( p );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}


// --run_test=TransformTests/PbrtTransformApplyInversePoint3fiTest1
BOOST_AUTO_TEST_CASE( PbrtTransformApplyInversePoint3fiTest1 )
{
    pbrt::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 1.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 1.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrt::Point3fi p(
        pbrt::Interval( -30.2945175f, -30.2945175f ),
        pbrt::Interval( -154.808182f, -154.808182f ),
        pbrt::Interval( -931.506165f, -931.506165f ) );

    pbrt::Point3fi expected(
        pbrt::Interval( -30.2945251f, -30.2945099f ),
        pbrt::Interval( -154.808228f, -154.808136f ),
        pbrt::Interval( -931.506409f, -931.505920f ) );

    pbrt::Transform t( m );

    pbrt::Point3fi result = t.ApplyInverse( p );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTransformApplyInversePoint3fiTest1
BOOST_AUTO_TEST_CASE( PbrtoTransformApplyInversePoint3fiTest1 )
{
    pbrto::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 1.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 1.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrto::Point3fi p(
        pbrto::Interval( -30.2945175f, -30.2945175f ),
        pbrto::Interval( -154.808182f, -154.808182f ),
        pbrto::Interval( -931.506165f, -931.506165f ) );

    pbrto::Point3fi expected(
        pbrto::Interval( -30.2945251f, -30.2945099f ),
        pbrto::Interval( -154.808228f, -154.808136f ),
        pbrto::Interval( -931.506409f, -931.505920f ) );

    pbrto::Transform t( m );

    pbrto::Point3fi result = t.ApplyInverse( p );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtTransformApplyInversePoint3fiTest2
BOOST_AUTO_TEST_CASE( PbrtTransformApplyInversePoint3fiTest2 )
{
    pbrt::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.998598754f, -0.0529195182f, 0.00000000f,
        0.00000000f, -0.0529195182f, -0.998598754f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrt::Point3fi p(
        pbrt::Interval( -30.2945175f, -30.2945175f ),
        pbrt::Interval( -154.808182f, -154.808182f ),
        pbrt::Interval( -931.506165f, -931.506165f ) );

    pbrt::Point3fi expected(
        pbrt::Interval( -30.2945251f, -30.2945099f ),
        pbrt::Interval( -105.296463f, -105.296371f ),
        pbrt::Interval( 938.393127f, 938.393616f ) );

    pbrt::Transform t( m );

    pbrt::Point3fi result = t.ApplyInverse( p );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTransformApplyInversePoint3fiTest2
BOOST_AUTO_TEST_CASE( PbrtoTransformApplyInversePoint3fiTest2 )
{
    pbrto::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.998598754f, -0.0529195182f, 0.00000000f,
        0.00000000f, -0.0529195182f, -0.998598754f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrto::Point3fi p(
        pbrto::Interval( -30.2945175f, -30.2945175f ),
        pbrto::Interval( -154.808182f, -154.808182f ),
        pbrto::Interval( -931.506165f, -931.506165f ) );

    pbrto::Point3fi expected(
        pbrto::Interval( -30.2945251f, -30.2945099f ),
        pbrto::Interval( -105.296463f, -105.296371f ),
        pbrto::Interval( 938.393127f, 938.393616f ) );

    pbrto::Transform t( m );

    pbrto::Point3fi result = t.ApplyInverse( p );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtTransformVector3fiTest1
BOOST_AUTO_TEST_CASE( PbrtTransformVector3fiTest1 )
{
    pbrt::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 1.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 1.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrt::Vector3fi v(
        pbrt::Interval( -30.2945175f, -30.2945175f ),
        pbrt::Interval( -154.808182f, -154.808182f ),
        pbrt::Interval( -931.506165f, -931.506165f ) );

    pbrt::Vector3fi expected(
        pbrt::Interval( -30.2945251f, -30.2945099f ),
        pbrt::Interval( -154.808228f, -154.808136f ),
        pbrt::Interval( -931.506409f, -931.505920f ) );

    pbrt::Transform t( m );

    pbrt::Vector3fi result = t( v );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTransformVector3fiTest1
BOOST_AUTO_TEST_CASE( PbrtoTransformVector3fiTest1 )
{
    pbrto::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 1.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 1.00000000f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrto::Vector3fi v(
        pbrto::Interval( -30.2945175f, -30.2945175f ),
        pbrto::Interval( -154.808182f, -154.808182f ),
        pbrto::Interval( -931.506165f, -931.506165f ) );

    pbrto::Vector3fi expected(
        pbrto::Interval( -30.2945251f, -30.2945099f ),
        pbrto::Interval( -154.808228f, -154.808136f ),
        pbrto::Interval( -931.506409f, -931.505920f ) );

    pbrto::Transform t( m );

    pbrto::Vector3fi result = t( v );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}



// --run_test=TransformTests/PbrtTransformVector3fiTest2
BOOST_AUTO_TEST_CASE( PbrtTransformVector3fiTest2 )
{
    pbrt::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.998598754f, -0.0529195182f, 0.00000000f,
        0.00000000f, -0.0529195182f, -0.998598754f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrt::Vector3fi v(
        pbrt::Interval( -30.2945175f, -30.2945175f ),
        pbrt::Interval( -154.808182f, -154.808182f ),
        pbrt::Interval( -931.506165f, -931.506165f ) );

    pbrt::Vector3fi expected(
        pbrt::Interval( -30.2945251f, -30.2945099f ),
        pbrt::Interval( -105.296448f, -105.296356f ),
        pbrt::Interval( 938.393005f, 938.393494f ) );

    pbrt::Transform t( m );

    pbrt::Vector3fi result = t( v );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/PbrtoTransformVector3fiTest2
BOOST_AUTO_TEST_CASE( PbrtoTransformVector3fiTest2 )
{
    pbrto::SquareMatrix<4> m(
        1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
        0.00000000f, 0.998598754f, -0.0529195182f, 0.00000000f,
        0.00000000f, -0.0529195182f, -0.998598754f, 0.00000000f,
        0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f );

    pbrto::Vector3fi v(
        pbrto::Interval( -30.2945175f, -30.2945175f ),
        pbrto::Interval( -154.808182f, -154.808182f ),
        pbrto::Interval( -931.506165f, -931.506165f ) );

    pbrto::Vector3fi expected(
        pbrto::Interval( -30.2945251f, -30.2945099f ),
        pbrto::Interval( -105.296448f, -105.296356f ),
        pbrto::Interval( 938.393005f, 938.393494f ) );

    pbrto::Transform t( m );

    pbrto::Vector3fi result = t( v );

    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}

// --run_test=TransformTests/TransformRandomTest1
BOOST_AUTO_TEST_CASE( TransformRandomTest1 )
{
    pbrt::RNG rng;
    auto r = [ &rng ]( ) { return -10.f + 20.f * rng.Uniform<float>( ); };

    pbrt::Transform t1;
    pbrto::Transform t2;
    
    for ( int i = 0; i < 10; ++i )
    {
        auto v1 = r( );
        auto v2 = r( );
        auto v3 = r( );

        switch ( i % 3 )
        {
            case 0:
            {
                t1 = t1 * pbrt::Scale( std::abs( v1 ), std::abs( v2 ), std::abs( v3 ) );
                t2 = t2 * pbrto::Scale( std::abs( v1 ), std::abs( v2 ), std::abs( v3 ) );

                auto equal = Equal( t1, t2 );
                if ( !equal )
                {
                    PrintLn( "Itration {}", i );
                }
                BOOST_CHECK( equal );
                break;
            }
            case 1:
            {
                t1 = t1 * pbrt::Translate( pbrt::Vector3f( v1, v2, v3 ) );
                t2 = t2 * pbrto::Translate( pbrto::Vector3f( v1, v2, v3 ) );
                auto equal = Equal( t1, t2 );
                if ( !equal )
                {
                    PrintLn( "Itration {}", i );
                }
                BOOST_CHECK( equal );

            }
            break;
            case 2:
            {
                t1 = t1 * pbrt::Rotate( v1 * 20.f, pbrt::SampleUniformSphere( pbrt::Point2f( v2, v3 ) ) );
                t2 = t2 * pbrto::Rotate( v1 * 20.f, pbrto::SampleUniformSphere( pbrto::Point2f( v2, v3 ) ) );
                auto equal = Equal( t1, t2 );
                if ( !equal )
                {
                    PrintLn( "Itration {}", i );
                }
                BOOST_CHECK( equal );
            }
            break;
        }
    }
    


}





BOOST_AUTO_TEST_SUITE_END( )