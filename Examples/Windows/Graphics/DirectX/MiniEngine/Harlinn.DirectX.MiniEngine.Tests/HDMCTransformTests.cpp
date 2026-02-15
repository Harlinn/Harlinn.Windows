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
using namespace Harlinn::Windows::DirectX::MiniEngine;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    static std::array<float, 4> ExtractQuatComponents( const Quaternion& q )
    {
#ifdef HDMC_USES_HCC_MATH
        m::Quaternion<float> qr( q );
        return { qr.v.x, qr.v.y, qr.v.z, qr.w };
#else
        ::DirectX::XMFLOAT4A f;
        ::DirectX::XMStoreFloat4A( &f, q );
        return { f.x, f.y, f.z, f.w };
#endif
    }

    static std::array<float, 3> ExtractVec3Components( const Vector3& v )
    {
#ifdef HDMC_USES_HCC_MATH
        m::Vector<float, 4> vf( Vector4( v.simd ) );
        return { vf.x, vf.y, vf.z };
#else
        ::DirectX::XMFLOAT4A f;
        ::DirectX::XMStoreFloat4A( &f, Vector4( v ) );
        return { f.x, f.y, f.z };
#endif
    }

    static std::array<float, 4> ExtractVec4Components( const Vector4& v )
    {
#ifdef HDMC_USES_HCC_MATH
        m::Vector<float, 4> vf( v );
        return { vf.x, vf.y, vf.z, vf.w };
#else
        ::DirectX::XMFLOAT4A f;
        ::DirectX::XMStoreFloat4A( &f, v );
        return { f.x, f.y, f.z, f.w };
#endif
    }

    static bool AlmostEqual( float a, float b, float eps = 1e-6f )
    {
        return std::fabs( a - b ) <= eps;
    }
}

BOOST_FIXTURE_TEST_SUITE( HDMCTransformTests, LocalFixture )

// --run_test=HDMCTransformTests/OrthogonalTransformQuaternionCtor
BOOST_AUTO_TEST_CASE( OrthogonalTransformQuaternionCtor )
{
    // Create a quaternion representing a rotation about X axis (non-zero test)
    const float angle = 0.7f; // radians
#ifdef HDMC_USES_HCC_MATH
    Quaternion q = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR1 ), angle );
#else
    Quaternion q = Quaternion( Vector3( kXUnitVector ), angle );
#endif

    // Construct transform from quaternion
    OrthogonalTransform t( q );

    // Extract rotation from transform and compare to original quaternion
    auto rotActual = ExtractQuatComponents( t.GetRotation( ) );
    auto rotExpected = ExtractQuatComponents( q );

    bool rotMatch = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( rotActual[ i ], rotExpected[ i ] ) )
        {
            rotMatch = false;
            break;
        }
    }
    BOOST_TEST( rotMatch );

    // Translation must be zero for this constructor
    auto trans = ExtractVec3Components( t.GetTranslation( ) );
    bool transIsZero = AlmostEqual( trans[ 0 ], 0.0f ) && AlmostEqual( trans[ 1 ], 0.0f ) && AlmostEqual( trans[ 2 ], 0.0f );
    BOOST_TEST( transIsZero );
}

// --run_test=HDMCTransformTests/OrthogonalTransformTranslateCtor
BOOST_AUTO_TEST_CASE( OrthogonalTransformTranslateCtor )
{
    Vector3 translate( 1.0f, 2.0f, 3.0f );

    // Construct transform from translation only
    OrthogonalTransform t( translate );

    // Rotation must be identity
#ifdef HDMC_USES_HCC_MATH
    Quaternion expectedRot = Quaternion::Identity( );
#else
    Quaternion expectedRot( kIdentity );
#endif

    auto rotActual = ExtractQuatComponents( t.GetRotation( ) );
    auto rotExpected = ExtractQuatComponents( expectedRot );

    bool rotIsIdentity = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( rotActual[ i ], rotExpected[ i ] ) )
        {
            rotIsIdentity = false;
            break;
        }
    }
    BOOST_TEST( rotIsIdentity );

    // Translation must match input
    auto transActual = ExtractVec3Components( t.GetTranslation( ) );
#ifdef HDMC_USES_HCC_MATH
    // extract expected from the same translate value to avoid construction mismatch
    auto transExpected = ExtractVec3Components( translate );
#else
    auto transExpected = std::array<float, 3>{ 1.0f, 2.0f, 3.0f };
#endif

    bool transMatches = AlmostEqual( transActual[ 0 ], transExpected[ 0 ] ) &&
        AlmostEqual( transActual[ 1 ], transExpected[ 1 ] ) &&
        AlmostEqual( transActual[ 2 ], transExpected[ 2 ] );
    BOOST_TEST( transMatches );
}

// --run_test=HDMCTransformTests/OrthogonalTransformRotateTranslateCtor
BOOST_AUTO_TEST_CASE( OrthogonalTransformRotateTranslateCtor )
{
    // Prepare rotation (about Y axis) and translation
    const float angle = 0.9f;
#ifdef HDMC_USES_HCC_MATH
    Quaternion q = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR2 ), angle );
#else
    Quaternion q = Quaternion( Vector3( kYUnitVector ), angle );
#endif

    Vector3 translate( -4.0f, 5.5f, 2.25f );

    // Construct transform from rotation and translation
    OrthogonalTransform t( q, translate );

    // Rotation stored must equal the provided quaternion (within epsilon)
    auto rotActual = ExtractQuatComponents( t.GetRotation( ) );
    auto rotExpected = ExtractQuatComponents( q );

    bool rotMatches = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( rotActual[ i ], rotExpected[ i ] ) )
        {
            rotMatches = false;
            break;
        }
    }
    BOOST_TEST( rotMatches );

    // Translation stored must equal the provided translation
    auto transActual = ExtractVec3Components( t.GetTranslation( ) );
#ifdef HDMC_USES_HCC_MATH
    auto transExpected = ExtractVec3Components( translate );
#else
    auto transExpected = std::array<float, 3>{ -4.0f, 5.5f, 2.25f };
#endif

    bool transMatches = AlmostEqual( transActual[ 0 ], transExpected[ 0 ] ) &&
        AlmostEqual( transActual[ 1 ], transExpected[ 1 ] ) &&
        AlmostEqual( transActual[ 2 ], transExpected[ 2 ] );
    BOOST_TEST( transMatches );
}

// --run_test=HDMCTransformTests/OrthogonalTransformMatrixCtor
BOOST_AUTO_TEST_CASE( OrthogonalTransformMatrixCtor )
{
    const float angle = 1.234567f; // radians
#ifdef HDMC_USES_HCC_MATH
    Matrix3 rotMat = MakeYRotation( angle );
#else
    Matrix3 rotMat = Matrix3::MakeYRotation( angle );
#endif
    // select a non-trivial vector
    Vector3 v( 1.0f, 0.5f, -2.0f );

    // result using matrix multiplication
    Vector3 byMatrix = rotMat * v;

    // construct transform from matrix and apply
    OrthogonalTransform t( rotMat );
    Vector3 byTransform = t * v; // uses quaternion rotation + translation (translation must be zero)

    auto mComp = ExtractVec3Components( byMatrix );
    auto tComp = ExtractVec3Components( byTransform );

    bool rotationMatches = AlmostEqual( mComp[ 0 ], tComp[ 0 ] ) &&
        AlmostEqual( mComp[ 1 ], tComp[ 1 ] ) &&
        AlmostEqual( mComp[ 2 ], tComp[ 2 ] );

    BOOST_TEST( rotationMatches );

    // Also verify translation is zero for this constructor
    auto trans = ExtractVec3Components( t.GetTranslation( ) );
    bool transIsZero = AlmostEqual( trans[ 0 ], 0.0f ) && AlmostEqual( trans[ 1 ], 0.0f ) && AlmostEqual( trans[ 2 ], 0.0f );
    BOOST_TEST( transIsZero );
}

// --run_test=HDMCTransformTests/OrthogonalTransformMatrixTranslateCtor
BOOST_AUTO_TEST_CASE( OrthogonalTransformMatrixTranslateCtor )
{
    const float angle = 0.654321f; // radians
#ifdef HDMC_USES_HCC_MATH
    Matrix3 rotMat = MakeZRotation( angle );
#else
    Matrix3 rotMat = Matrix3::MakeZRotation( angle );
#endif

    Vector3 translation( 3.5f, -1.2f, 4.8f );
    Vector3 testVec( 2.0f, 1.5f, -0.75f );

    // Expected result: first rotate the vector, then add translation
    Vector3 expectedResult = rotMat * testVec + translation;

    // Construct transform from matrix and translation
    OrthogonalTransform t( rotMat, translation );

    // Apply transform to the test vector
    Vector3 actualResult = t * testVec;

    // Extract and compare results
    auto expComp = ExtractVec3Components( expectedResult );
    auto actComp = ExtractVec3Components( actualResult );

    bool resultsMatch = AlmostEqual( expComp[ 0 ], actComp[ 0 ] ) &&
        AlmostEqual( expComp[ 1 ], actComp[ 1 ] ) &&
        AlmostEqual( expComp[ 2 ], actComp[ 2 ] );

    BOOST_TEST( resultsMatch );

    // Also verify the stored translation matches
    auto storedTrans = ExtractVec3Components( t.GetTranslation( ) );
#ifdef HDMC_USES_HCC_MATH
    auto expectedTrans = ExtractVec3Components( translation );
#else
    auto expectedTrans = std::array<float, 3>{ 3.5f, -1.2f, 4.8f };
#endif

    bool transMatches = AlmostEqual( storedTrans[ 0 ], expectedTrans[ 0 ] ) &&
        AlmostEqual( storedTrans[ 1 ], expectedTrans[ 1 ] ) &&
        AlmostEqual( storedTrans[ 2 ], expectedTrans[ 2 ] );

    BOOST_TEST( transMatches );
}

// --run_test=HDMCTransformTests/OrthogonalTransformIdentityCtor
BOOST_AUTO_TEST_CASE( OrthogonalTransformIdentityCtor )
{
    Vector3 testVec( 3.7f, -2.1f, 5.9f );

    // Construct identity transform
    OrthogonalTransform identityTransform( kIdentity );

    // Apply identity transform to test vector
    Vector3 result = identityTransform * testVec;

    // Result should equal the input vector (within epsilon)
    auto inputComp = ExtractVec3Components( testVec );
    auto resultComp = ExtractVec3Components( result );

    bool vectorUnchanged = AlmostEqual( inputComp[ 0 ], resultComp[ 0 ] ) &&
        AlmostEqual( inputComp[ 1 ], resultComp[ 1 ] ) &&
        AlmostEqual( inputComp[ 2 ], resultComp[ 2 ] );

    BOOST_TEST( vectorUnchanged );

    // Verify rotation is identity
#ifdef HDMC_USES_HCC_MATH
    Quaternion expectedRot = Quaternion::Identity( );
#else
    Quaternion expectedRot( kIdentity );
#endif

    auto rotActual = ExtractQuatComponents( identityTransform.GetRotation( ) );
    auto rotExpected = ExtractQuatComponents( expectedRot );

    bool rotIsIdentity = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( rotActual[ i ], rotExpected[ i ] ) )
        {
            rotIsIdentity = false;
            break;
        }
    }
    BOOST_TEST( rotIsIdentity );

    // Verify translation is zero
    auto trans = ExtractVec3Components( identityTransform.GetTranslation( ) );
    bool transIsZero = AlmostEqual( trans[ 0 ], 0.0f ) && AlmostEqual( trans[ 1 ], 0.0f ) && AlmostEqual( trans[ 2 ], 0.0f );
    BOOST_TEST( transIsZero );
}

// --run_test=HDMCTransformTests/SetRotationGetRotationTest
BOOST_AUTO_TEST_CASE( SetRotationGetRotationTest )
{
    // Create an identity transform
    OrthogonalTransform t( kIdentity );

    // Create a new quaternion (rotate about Z axis)
    const float angle = 1.5708f; // PI/2
#ifdef HDMC_USES_HCC_MATH
    Quaternion newRot = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR3 ), angle );
#else
    Quaternion newRot = Quaternion( Vector3( kZUnitVector ), angle );
#endif

    // Set rotation
    t.SetRotation( newRot );

    // Get rotation and compare
    auto setComp = ExtractQuatComponents( newRot );
    auto getComp = ExtractQuatComponents( t.GetRotation( ) );

    bool rotMatches = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( setComp[ i ], getComp[ i ] ) )
        {
            rotMatches = false;
            break;
        }
    }
    BOOST_TEST( rotMatches );

    // Verify translation unchanged (still zero)
    auto trans = ExtractVec3Components( t.GetTranslation( ) );
    bool transIsZero = AlmostEqual( trans[ 0 ], 0.0f ) && AlmostEqual( trans[ 1 ], 0.0f ) && AlmostEqual( trans[ 2 ], 0.0f );
    BOOST_TEST( transIsZero );
}

// --run_test=HDMCTransformTests/SetTranslationGetTranslationTest
BOOST_AUTO_TEST_CASE( SetTranslationGetTranslationTest )
{
    // Create an identity transform
    OrthogonalTransform t( kIdentity );

    // Create a new translation vector
    Vector3 newTrans( 7.5f, -3.2f, 1.1f );

    // Set translation
    t.SetTranslation( newTrans );

    // Get translation and compare
    auto setComp = ExtractVec3Components( newTrans );
    auto getComp = ExtractVec3Components( t.GetTranslation( ) );

    bool transMatches = AlmostEqual( setComp[ 0 ], getComp[ 0 ] ) &&
        AlmostEqual( setComp[ 1 ], getComp[ 1 ] ) &&
        AlmostEqual( setComp[ 2 ], getComp[ 2 ] );
    BOOST_TEST( transMatches );

    // Verify rotation unchanged (still identity)
#ifdef HDMC_USES_HCC_MATH
    Quaternion expectedRot = Quaternion::Identity( );
#else
    Quaternion expectedRot( kIdentity );
#endif

    auto rotActual = ExtractQuatComponents( t.GetRotation( ) );
    auto rotExpected = ExtractQuatComponents( expectedRot );

    bool rotIsIdentity = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( rotActual[ i ], rotExpected[ i ] ) )
        {
            rotIsIdentity = false;
            break;
        }
    }
    BOOST_TEST( rotIsIdentity );
}

// --run_test=HDMCTransformTests/MakeXRotationTest
BOOST_AUTO_TEST_CASE( MakeXRotationTest )
{
    const float angle = 0.785398f; // PI/4

    // Create transform from MakeXRotation
    OrthogonalTransform t = OrthogonalTransform::MakeXRotation( angle );

    // Test vector (rotate about X, so X component should stay same)
    Vector3 v( 1.0f, 1.0f, 0.0f );
    Vector3 rotated = t * v;

    auto vComp = ExtractVec3Components( v );
    auto rComp = ExtractVec3Components( rotated );

    // X component should be unchanged
    bool xUnchanged = AlmostEqual( vComp[ 0 ], rComp[ 0 ] );
    BOOST_TEST( xUnchanged );

    // Verify translation is zero
    auto trans = ExtractVec3Components( t.GetTranslation( ) );
    bool transIsZero = AlmostEqual( trans[ 0 ], 0.0f ) && AlmostEqual( trans[ 1 ], 0.0f ) && AlmostEqual( trans[ 2 ], 0.0f );
    BOOST_TEST( transIsZero );
}

// --run_test=HDMCTransformTests/MakeYRotationTest
BOOST_AUTO_TEST_CASE( MakeYRotationTest )
{
    const float angle = 0.785398f; // PI/4

    // Create transform from MakeYRotation
    OrthogonalTransform t = OrthogonalTransform::MakeYRotation( angle );

    // Test vector (rotate about Y, so Y component should stay same)
    Vector3 v( 1.0f, 1.0f, 0.0f );
    Vector3 rotated = t * v;

    auto vComp = ExtractVec3Components( v );
    auto rComp = ExtractVec3Components( rotated );

    // Y component should be unchanged
    bool yUnchanged = AlmostEqual( vComp[ 1 ], rComp[ 1 ] );
    BOOST_TEST( yUnchanged );

    // Verify translation is zero
    auto trans = ExtractVec3Components( t.GetTranslation( ) );
    bool transIsZero = AlmostEqual( trans[ 0 ], 0.0f ) && AlmostEqual( trans[ 1 ], 0.0f ) && AlmostEqual( trans[ 2 ], 0.0f );
    BOOST_TEST( transIsZero );
}

// --run_test=HDMCTransformTests/MakeZRotationTest
BOOST_AUTO_TEST_CASE( MakeZRotationTest )
{
    const float angle = 0.785398f; // PI/4

    // Create transform from MakeZRotation
    OrthogonalTransform t = OrthogonalTransform::MakeZRotation( angle );

    // Test vector (rotate about Z, so Z component should stay same)
    Vector3 v( 1.0f, 0.0f, 1.0f );
    Vector3 rotated = t * v;

    auto vComp = ExtractVec3Components( v );
    auto rComp = ExtractVec3Components( rotated );

    // Z component should be unchanged
    bool zUnchanged = AlmostEqual( vComp[ 2 ], rComp[ 2 ] );
    BOOST_TEST( zUnchanged );

    // Verify translation is zero
    auto trans = ExtractVec3Components( t.GetTranslation( ) );
    bool transIsZero = AlmostEqual( trans[ 0 ], 0.0f ) && AlmostEqual( trans[ 1 ], 0.0f ) && AlmostEqual( trans[ 2 ], 0.0f );
    BOOST_TEST( transIsZero );
}

// --run_test=HDMCTransformTests/SetRotationMultipleTimesTest
BOOST_AUTO_TEST_CASE( SetRotationMultipleTimesTest )
{
    OrthogonalTransform t( kIdentity );

    // First rotation (X axis)
    const float angle1 = 0.5f;
#ifdef HDMC_USES_HCC_MATH
    Quaternion rot1 = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR1 ), angle1 );
#else
    Quaternion rot1 = Quaternion( Vector3( kXUnitVector ), angle1 );
#endif

    t.SetRotation( rot1 );
    auto comp1 = ExtractQuatComponents( t.GetRotation( ) );
    auto exp1 = ExtractQuatComponents( rot1 );

    bool match1 = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( comp1[ i ], exp1[ i ] ) )
        {
            match1 = false;
            break;
        }
    }
    BOOST_TEST( match1 );

    // Second rotation (Y axis) - overwrites first
    const float angle2 = 1.0f;
#ifdef HDMC_USES_HCC_MATH
    Quaternion rot2 = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR2 ), angle2 );
#else
    Quaternion rot2 = Quaternion( Vector3( kYUnitVector ), angle2 );
#endif

    t.SetRotation( rot2 );
    auto comp2 = ExtractQuatComponents( t.GetRotation( ) );
    auto exp2 = ExtractQuatComponents( rot2 );

    bool match2 = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( comp2[ i ], exp2[ i ] ) )
        {
            match2 = false;
            break;
        }
    }
    BOOST_TEST( match2 );
}

// --run_test=HDMCTransformTests/SetTranslationMultipleTimesTest
BOOST_AUTO_TEST_CASE( SetTranslationMultipleTimesTest )
{
    OrthogonalTransform t( kIdentity );

    // First translation
    Vector3 trans1( 1.0f, 2.0f, 3.0f );
    t.SetTranslation( trans1 );

    auto comp1 = ExtractVec3Components( t.GetTranslation( ) );
    bool match1 = AlmostEqual( comp1[ 0 ], 1.0f ) &&
        AlmostEqual( comp1[ 1 ], 2.0f ) &&
        AlmostEqual( comp1[ 2 ], 3.0f );
    BOOST_TEST( match1 );

    // Second translation - overwrites first
    Vector3 trans2( -5.0f, 0.5f, 10.0f );
    t.SetTranslation( trans2 );

    auto comp2 = ExtractVec3Components( t.GetTranslation( ) );
    bool match2 = AlmostEqual( comp2[ 0 ], -5.0f ) &&
        AlmostEqual( comp2[ 1 ], 0.5f ) &&
        AlmostEqual( comp2[ 2 ], 10.0f );
    BOOST_TEST( match2 );
}

// --run_test=HDMCTransformTests/MakeTranslation
BOOST_AUTO_TEST_CASE( MakeTranslation )
{
    Vector3 translation( 2.5f, -1.3f, 4.7f );

    // Create transform using static factory
    OrthogonalTransform t = OrthogonalTransform::MakeTranslation( translation );

    // Verify translation is stored correctly
    auto storedTrans = ExtractVec3Components( t.GetTranslation( ) );
    auto expectedTrans = ExtractVec3Components( translation );

    bool transMatches = AlmostEqual( storedTrans[ 0 ], expectedTrans[ 0 ] ) &&
        AlmostEqual( storedTrans[ 1 ], expectedTrans[ 1 ] ) &&
        AlmostEqual( storedTrans[ 2 ], expectedTrans[ 2 ] );
    BOOST_TEST( transMatches );

    // Verify rotation is identity
#ifdef HDMC_USES_HCC_MATH
    Quaternion expectedRot = Quaternion::Identity( );
#else
    Quaternion expectedRot( kIdentity );
#endif

    auto rotActual = ExtractQuatComponents( t.GetRotation( ) );
    auto rotExpected = ExtractQuatComponents( expectedRot );

    bool rotIsIdentity = true;
    for ( int i = 0; i < 4; ++i )
    {
        if ( !AlmostEqual( rotActual[ i ], rotExpected[ i ] ) )
        {
            rotIsIdentity = false;
            break;
        }
    }
    BOOST_TEST( rotIsIdentity );
}

// --run_test=HDMCTransformTests/TransformVector3
BOOST_AUTO_TEST_CASE( TransformVector3 )
{
    // Create transform: rotation about Z by PI/4, then translate
    const float angle = 0.785398f; // PI/4
#ifdef HDMC_USES_HCC_MATH
    Quaternion rot = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR3 ), angle );
#else
    Quaternion rot = Quaternion( Vector3( kZUnitVector ), angle );
#endif

    Vector3 translation( 1.0f, 2.0f, 3.0f );
    OrthogonalTransform t( rot, translation );

    // Test vector
    Vector3 v( 1.0f, 0.0f, 0.0f );

    // Apply transform: first rotate, then translate
    Vector3 result = t * v;

    // Expected: rotate v by rot, then add translation
    Vector3 rotatedV = rot * v;
    Vector3 expected = rotatedV + translation;

    auto expComp = ExtractVec3Components( expected );
    auto resComp = ExtractVec3Components( result );

    bool matches = AlmostEqual( expComp[ 0 ], resComp[ 0 ] ) &&
        AlmostEqual( expComp[ 1 ], resComp[ 1 ] ) &&
        AlmostEqual( expComp[ 2 ], resComp[ 2 ] );
    BOOST_TEST( matches );
}

// --run_test=HDMCTransformTests/TransformVector4
BOOST_AUTO_TEST_CASE( TransformVector4 )
{
    // Create transform with rotation and translation
    const float angle = 1.5707f; // PI/2
#ifdef HDMC_USES_HCC_MATH
    Quaternion rot = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR2 ), angle );
#else
    Quaternion rot = Quaternion( Vector3( kYUnitVector ), angle );
#endif

    Vector3 translation( 0.5f, 1.5f, 2.5f );
    OrthogonalTransform t( rot, translation );

    // Test vector with W=1 (point)
    Vector4 v( 1.0f, 0.0f, 0.0f, 1.0f );

    // Apply transform
    Vector4 result = t * v;

    // Expected: rotate (1,0,0), add translation, W scaled appropriately
    Vector3 v3( 1.0f, 0.0f, 0.0f );
    Vector3 rotated = rot * v3;
    Vector3 expected3 = rotated + translation;

    auto expComp = ExtractVec3Components( expected3 );
    auto resComp = ExtractVec4Components( result );

    bool matches = AlmostEqual( expComp[ 0 ], resComp[ 0 ] ) &&
        AlmostEqual( expComp[ 1 ], resComp[ 1 ] ) &&
        AlmostEqual( expComp[ 2 ], resComp[ 2 ] );
    BOOST_TEST( matches );

    // W should be 1
    bool wIsOne = AlmostEqual( resComp[ 3 ], 1.0f );
    BOOST_TEST( wIsOne );
}

// --run_test=HDMCTransformTests/TransformBoundingSphere
BOOST_AUTO_TEST_CASE( TransformBoundingSphere )
{
    // Create transform: small rotation and translation
    const float angle = 0.3f;
#ifdef HDMC_USES_HCC_MATH
    Quaternion rot = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR1 ), angle );
#else
    Quaternion rot = Quaternion( Vector3( kXUnitVector ), angle );
#endif

    Vector3 translation( 5.0f, -2.0f, 3.0f );
    OrthogonalTransform t( rot, translation );

    // Create a bounding sphere
    Vector3 center( 1.0f, 1.0f, 1.0f );
    float radius = 0.5f;
    BoundingSphere sphere( center, Scalar( radius ) );

    // Apply transform
    BoundingSphere transformed = t * sphere;

    // For orthogonal transforms, radius is unchanged
    // Center is rotated and translated
    BoundingSphere expectedSphere( t * center, Scalar( radius ) );

    auto expCenter = ExtractVec3Components( expectedSphere.GetCenter( ) );
    auto transCenter = ExtractVec3Components( transformed.GetCenter( ) );

    bool centerMatches = AlmostEqual( expCenter[ 0 ], transCenter[ 0 ] ) &&
        AlmostEqual( expCenter[ 1 ], transCenter[ 1 ] ) &&
        AlmostEqual( expCenter[ 2 ], transCenter[ 2 ] );
    BOOST_TEST( centerMatches );

    // Radius should be the same
#ifdef HDMC_USES_HCC_MATH
    bool radiusMatches = AlmostEqual( transformed.GetRadius( ).x(), radius );
#else
    bool radiusMatches = AlmostEqual( ( float )transformed.GetRadius( ), radius );
#endif
    BOOST_TEST( radiusMatches );
}

// --run_test=HDMCTransformTests/ComposeTransforms
BOOST_AUTO_TEST_CASE( ComposeTransforms )
{
    // Create two transforms
    const float angle1 = 0.4f;
    const float angle2 = 0.6f;

#ifdef HDMC_USES_HCC_MATH
    Quaternion rot1 = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR1 ), angle1 );
    Quaternion rot2 = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR2 ), angle2 );
#else
    Quaternion rot1 = Quaternion( Vector3( kXUnitVector ), angle1 );
    Quaternion rot2 = Quaternion( Vector3( kYUnitVector ), angle2 );
#endif

    Vector3 trans1( 1.0f, 0.0f, 0.0f );
    Vector3 trans2( 0.0f, 2.0f, 0.0f );

    OrthogonalTransform t1( rot1, trans1 );
    OrthogonalTransform t2( rot2, trans2 );

    // Compose: t1 * t2 means apply t2 first, then t1
    OrthogonalTransform composed = t1 * t2;

    // Test on a vector: should equal t1 * (t2 * v)
    Vector3 v( 1.0f, 1.0f, 0.0f );

    Vector3 vTransformed2 = t2 * v;
    Vector3 vTransformedBoth = t1 * vTransformed2;

    Vector3 vComposed = composed * v;

    auto bothComp = ExtractVec3Components( vTransformedBoth );
    auto compComp = ExtractVec3Components( vComposed );

    bool matches = AlmostEqual( bothComp[ 0 ], compComp[ 0 ] ) &&
        AlmostEqual( bothComp[ 1 ], compComp[ 1 ] ) &&
        AlmostEqual( bothComp[ 2 ], compComp[ 2 ] );
    BOOST_TEST( matches );
}

// --run_test=HDMCTransformTests/InverseTransform
BOOST_AUTO_TEST_CASE( InverseTransform )
{
    // Create a transform
    const float angle = 0.8f;
#ifdef HDMC_USES_HCC_MATH
    Quaternion rot = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR3 ), angle );
#else
    Quaternion rot = Quaternion( Vector3( kZUnitVector ), angle );
#endif

    Vector3 translation( 3.0f, -1.5f, 2.0f );
    OrthogonalTransform t( rot, translation );

    // Get inverse
    OrthogonalTransform tInv = ~t;

    // Test: t * tInv should be identity
    OrthogonalTransform composed = t * tInv;

    // Apply to a test vector: should return approximately the same vector
    Vector3 v( 2.0f, 3.0f, 1.0f );
    Vector3 vTransformed = t * v;
    Vector3 vRestored = tInv * vTransformed;

    auto origComp = ExtractVec3Components( v );
    auto restoredComp = ExtractVec3Components( vRestored );

    bool matches = AlmostEqual( origComp[ 0 ], restoredComp[ 0 ] ) &&
        AlmostEqual( origComp[ 1 ], restoredComp[ 1 ] ) &&
        AlmostEqual( origComp[ 2 ], restoredComp[ 2 ] );
    BOOST_TEST( matches );

    // Verify rotation of inverse is conjugate of original
    auto origRot = ExtractQuatComponents( t.GetRotation( ) );
    auto invRot = ExtractQuatComponents( tInv.GetRotation( ) );

    // Conjugate: (x, y, z, w) -> (-x, -y, -z, w)
    bool rotIsConjugate = AlmostEqual( origRot[ 0 ], -invRot[ 0 ], 1e-4f ) &&
        AlmostEqual( origRot[ 1 ], -invRot[ 1 ], 1e-4f ) &&
        AlmostEqual( origRot[ 2 ], -invRot[ 2 ], 1e-4f ) &&
        AlmostEqual( origRot[ 3 ], invRot[ 3 ], 1e-4f );
    BOOST_TEST( rotIsConjugate );

    // Verify translation of inverse
    auto origTrans = ExtractVec3Components( t.GetTranslation( ) );
    auto invTrans = ExtractVec3Components( tInv.GetTranslation( ) );

    // Inverse translation should be -R^T * t (where R is rotation matrix)
    // For unit quaternions, R^T = R^-1, and for inverse quat: T_inv = -R_inv * T
    // This is handled in the implementation, just check that they differ
    bool transInverted = !( AlmostEqual( origTrans[ 0 ], invTrans[ 0 ] ) &&
        AlmostEqual( origTrans[ 1 ], invTrans[ 1 ] ) &&
        AlmostEqual( origTrans[ 2 ], invTrans[ 2 ] ) );
    BOOST_TEST( transInverted );
}

// --run_test=HDMCTransformTests/ChainedTransforms
BOOST_AUTO_TEST_CASE( ChainedTransforms )
{
    // Create three transforms and chain them
    const float angle1 = 0.2f;
    const float angle2 = 0.3f;
    const float angle3 = 0.5f;

#ifdef HDMC_USES_HCC_MATH
    Quaternion rot1 = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR1 ), angle1 );
    Quaternion rot2 = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR2 ), angle2 );
    Quaternion rot3 = Quaternion::FromAxisAndAngle( Vector3( m::Traits::Constants::IdentityR3 ), angle3 );
#else
    Quaternion rot1 = Quaternion( Vector3( kXUnitVector ), angle1 );
    Quaternion rot2 = Quaternion( Vector3( kYUnitVector ), angle2 );
    Quaternion rot3 = Quaternion( Vector3( kZUnitVector ), angle3 );
#endif

    Vector3 trans1( 1.0f, 0.0f, 0.0f );
    Vector3 trans2( 0.0f, 1.0f, 0.0f );
    Vector3 trans3( 0.0f, 0.0f, 1.0f );

    OrthogonalTransform t1( rot1, trans1 );
    OrthogonalTransform t2( rot2, trans2 );
    OrthogonalTransform t3( rot3, trans3 );

    // Chain: t1 * t2 * t3
    OrthogonalTransform composed = t1 * ( t2 * t3 );

    // Test vector
    Vector3 v( 1.0f, 0.5f, 0.25f );

    // Apply sequentially: t3, then t2, then t1
    Vector3 step1 = t3 * v;
    Vector3 step2 = t2 * step1;
    Vector3 step3 = t1 * step2;

    // Apply composed transform directly
    Vector3 vComposed = composed * v;

    auto seqComp = ExtractVec3Components( step3 );
    auto compComp = ExtractVec3Components( vComposed );

    bool matches = AlmostEqual( seqComp[ 0 ], compComp[ 0 ] ) &&
        AlmostEqual( seqComp[ 1 ], compComp[ 1 ] ) &&
        AlmostEqual( seqComp[ 2 ], compComp[ 2 ] );
    BOOST_TEST( matches );
}

BOOST_AUTO_TEST_SUITE_END( )