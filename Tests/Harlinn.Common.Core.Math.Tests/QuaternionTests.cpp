#include "pch.h"

using namespace Harlinn::Common::Core;

using Constants = Math::Constants<float>;
using Quaternion = Math::Quaternion<float>;
using Q = Math::Quaternion<float>;

namespace
{
    

    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    inline bool Equal( const Q& q1, const Q& q2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            auto v1 = q1[ i ];
            float v2 = q2[ i ];
            auto delta = v1 - v2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }


    inline bool Equal( const DirectX::XMFLOAT4A& q1, const DirectX::XMFLOAT4A& q2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            auto v1 =  ( &q1.x )[ i ];
            float v2 = ( &q2.x )[ i ];
            auto delta = v1 - v2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const DirectX::XMFLOAT3A& q1, const DirectX::XMFLOAT3A& q2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto v1 = ( &q1.x )[ i ];
            float v2 = ( &q2.x )[ i ];
            auto delta = v1 - v2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }
}

BOOST_FIXTURE_TEST_SUITE( QuaternionTests, LocalFixture )

// --run_test=QuaternionTests/AddTest1
BOOST_AUTO_TEST_CASE( AddTest1 )
{
    Q q1( 3.f, 3.f, 3.f, 3.f );
    Q q2( 2.f, 2.f, 2.f, 2.f );
    Q expected( 5.f, 5.f, 5.f, 5.f );

    Q result = q1 + q2;

    auto equal = Equal( result, expected );
    
    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/SubtractTest1
BOOST_AUTO_TEST_CASE( SubtractTest1 )
{
    Q q1( 3.f, 3.f, 3.f, 3.f );
    Q q2( 2.f, 2.f, 2.f, 2.f );
    Q expected( 1.f, 1.f, 1.f, 1.f );

    Q result = q1 - q2;

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );

}

// --run_test=QuaternionTests/AddScalarTest1
BOOST_AUTO_TEST_CASE( AddScalarTest1 )
{
    Q q1( 1.f, 2.f, 3.f, 4.f );
    float v1 = 2.f;
    float v2 = 3.f;
    Q expected1( 1.f, 2.f, 3.f, 6.f );
    Q expected2( 1.f, 2.f, 3.f, 7.f );

    Q result1 = q1 + v1;
    Q result2 = v2 + q1;

    auto equal = Equal( result1, expected1 );

    BOOST_CHECK( equal );

    equal = Equal( result2, expected2 );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/SubtractScalarTest1
BOOST_AUTO_TEST_CASE( SubtractScalarTest1 )
{
    Q q1( 1.f, 2.f, 3.f, 4.f );
    float v1 = 2.f;
    float v2 = 3.f;
    Q expected1( 1.f, 2.f, 3.f, 2.f );
    Q expected2( 1.f, 2.f, 3.f, -1.f );

    Q result1 = q1 - v1;
    Q result2 = v2 - q1;

    auto equal = Equal( result1, expected1 );

    BOOST_CHECK( equal );

    equal = Equal( result2, expected2 );

    BOOST_CHECK( equal );
}


// --run_test=QuaternionTests/MultiplyTest1
BOOST_AUTO_TEST_CASE( MultiplyTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );
    Q q2( 8.f, 7.f, 6.f, 9.f );
    Q expected( 36.f, 14.f, 52.f, -52.f );

    Q result = q1 * q2;

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/MultiplyTest2
BOOST_AUTO_TEST_CASE( MultiplyTest2 )
{
    Q q1( -22.1869278f, -22.1869278f, -49.2577934f, 0.f );
    Q q2( 0.0632871166f, -0.303319544f, -0.0201944206f, 0.950570464f );
    Q expected( -6.59743977f, -17.5248032f, -54.9568787f, -6.32031488f );

    Q result = q1 * q2;

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/XMQuaternionMultiplyTest2
BOOST_AUTO_TEST_CASE( XMQuaternionMultiplyTest2 )
{
    using namespace DirectX;

    XMFLOAT4A q1Unloaded( -22.1869278f, -22.1869278f, -49.2577934f, 0.f );
    auto q1 = XMLoadFloat4A( &q1Unloaded );

    XMFLOAT4A q2Unloaded( 0.0632871166f, -0.303319544f, -0.0201944206f, 0.950570464f );
    auto q2 = XMLoadFloat4A( &q2Unloaded );

    XMFLOAT4A expected( -6.59743977f, -17.5248032f, -54.9568787f, -6.32031488f );

    auto result = XMQuaternionMultiply( q1, q2 );

    XMFLOAT4A resultStored;
    XMStoreFloat4A( &resultStored, result );

    auto equal = Equal( resultStored, expected );

    BOOST_CHECK( equal );
}



// --run_test=QuaternionTests/MultiplyScalarTest1
BOOST_AUTO_TEST_CASE( MultiplyScalarTest1 )
{
    Q q1( 1.f, 2.f, 3.f, 4.f );
    float v1 = 2.f;
    float v2 = 3.f;
    Q expected1( 2.f, 4.f, 6.f, 8.f );
    Q expected2( 3.f, 6.f, 9.f, 12.f );

    Q result1 = q1 * v1;
    Q result2 = v2 * q1;

    auto equal = Equal( result1, expected1 );

    BOOST_CHECK( equal );

    equal = Equal( result2, expected2 );

    BOOST_CHECK( equal );
}


// --run_test=QuaternionTests/DivisionScalarTest1
BOOST_AUTO_TEST_CASE( DivisionScalarTest1 )
{
    Q q1( 1.f, 2.f, 3.f, 4.f );
    float v1 = 2.f;
    float v2 = 3.f;
    Q expected1( 1.f / 2.f, 2.f / 2.f, 3.f / 2.f, 4.f / 2.f );
    Q expected2( 3.f / 1.f, 3.f / 2.f, 3.f / 3.f, 3.f / 4.f );

    Q result1 = q1 / v1;
    Q result2 = v2 / q1;

    auto equal = Equal( result1, expected1 );

    BOOST_CHECK( equal );

    equal = Equal( result2, expected2 );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/DotTest1
BOOST_AUTO_TEST_CASE( DotTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );
    Q q2( 8.f, 7.f, 6.f, 9.f );

    Math::Vector<float, 4> expected( 70.f, 70.f, 70.f, 70.f );

    Math::Vector<float, 4> result = Math::Vector<float, 4>::Simd(Dot( q1, q2 ).simd);

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/LengthSquaredTest1
BOOST_AUTO_TEST_CASE( LengthSquaredTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 30.f, 30.f, 30.f, 30.f );

    Math::Vector<float, 4> result = Math::Vector<float, 4>::Simd( LengthSquared( q1 ).simd);

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}


// --run_test=QuaternionTests/LengthTest1
BOOST_AUTO_TEST_CASE( LengthTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 5.47722578f, 5.47722578f, 5.47722578f, 5.47722578f );

    Math::Vector<float, 4> result = Math::Vector<float, 4>::Simd( Length( q1 ).simd );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/ReciprocalLengthTest1
BOOST_AUTO_TEST_CASE( ReciprocalLengthTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 0.182574183f, 0.182574183f, 0.182574183f, 0.182574183f );

    Math::Vector<float, 4> result = Math::Vector<float, 4>::Simd( ReciprocalLength( q1 ).simd );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/NormalizeTest1
BOOST_AUTO_TEST_CASE( NormalizeTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Q expected( 0.365148365f, 0.547722518f, 0.730296731f, 0.182574183f );

    Q result = Normalize( q1 );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/ConjugateTest1
BOOST_AUTO_TEST_CASE( ConjugateTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Q expected( -2.f, -3.f, -4.f, 1.f );

    Q result = Conjugate( q1 );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/InverseTest1
BOOST_AUTO_TEST_CASE( InverseTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Q expected( -0.0666666701f, -0.100000001f, -0.133333340f, 0.0333333351f );

    Q result = Inverse( q1 );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/SlerpTest1
BOOST_AUTO_TEST_CASE( SlerpTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );
    Q q2( 8.f, 7.f, 6.f, 9.f );

    Q expected( 0.429141968f, 0.539775491f, 0.650409102f, 0.318508387f );

    auto q1n = Normalize( q1 );
    auto q2n = Normalize( q2 );

    Q result = Slerp( q1n, q2n, 0.3f );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/XMQuaternionRotateTest1
BOOST_AUTO_TEST_CASE( XMQuaternionRotateTest1 )
{
    Math::Vector<float, 3> vec( -22.186928, -22.186928, -49.257793 );
    Q rotation( -0.06328712, 0.30331954, 0.02019442, 0.95057046 );
    Math::Vector<float, 3> expected( -44.661453, -28.521133, -24.550959 );

    Math::Vector<float, 3> result = Math::Rotate( vec, rotation );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );

}

// --run_test=QuaternionTests/XMVector3RotateTest1
BOOST_AUTO_TEST_CASE( XMVector3RotateTest1 )
{
    using namespace DirectX;

    XMFLOAT3A vecUnloaded( -22.186928, -22.186928, -49.257793 );
    auto vec = XMLoadFloat3A( &vecUnloaded );

    XMFLOAT4A rotationUnloaded( -0.06328712, 0.30331954, 0.02019442, 0.95057046 );
    auto rotation = XMLoadFloat4A( &rotationUnloaded );

    XMFLOAT3A expected( -44.661453, -28.521133, -24.550959 );

    auto result = XMVector3Rotate( vec, rotation );

    XMFLOAT3A resultStored;
    XMStoreFloat3A( &resultStored, result );

    auto equal = Equal( resultStored, expected );

    BOOST_CHECK( equal );
}



/*

// --run_test=QuaternionTests/XMQuaternionDotTest1
BOOST_AUTO_TEST_CASE( XMQuaternionDotTest1 )
{
    using namespace DirectX;
    XMFLOAT4A q1Unloaded( 2.f, 3.f, 4.f, 1.f );
    auto q1 = XMLoadFloat4A( &q1Unloaded );
    XMFLOAT4A q2Unloaded( 8.f, 7.f, 6.f, 9.f );
    auto q2 = XMLoadFloat4A( &q2Unloaded );

    XMFLOAT4A expected( 0.429141968f, 0.539775491f, 0.650409102f, 0.318508387f );

    auto q1n = XMQuaternionNormalize( q1 );
    auto q2n = XMQuaternionNormalize( q2 );

    auto result = XMQuaternionSlerp(q1n,q2n,0.3f);

    XMFLOAT4A resultStored;
    XMStoreFloat4A( &resultStored, result );

    auto equal = Equal( resultStored, expected );

    BOOST_CHECK( equal );
}
*/


BOOST_AUTO_TEST_SUITE_END( )