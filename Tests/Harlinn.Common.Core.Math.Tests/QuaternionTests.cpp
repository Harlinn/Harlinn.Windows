#include "pch.h"

using namespace Harlinn::Common::Core;

using Constants = Math::Constants<float>;
using Quaternion = Math::Quaternion<float>;
using Q = Quaternion;

namespace
{
    

    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    inline bool Equal( const Quaternion& q1, const Quaternion& q2, float epsilon = 0.0001f )
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

    template<Math::Internal::TupleType T, Math::Internal::TupleType U>
    inline bool Equal( const T& q1, const U& q2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < T::Size; i++ )
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

    Math::Vector<float, 4> result = Dot( q1, q2 );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/LengthSquaredTest1
BOOST_AUTO_TEST_CASE( LengthSquaredTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 30.f, 30.f, 30.f, 30.f );

    Math::Vector<float, 4> result = LengthSquared( q1 );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}


// --run_test=QuaternionTests/LengthTest1
BOOST_AUTO_TEST_CASE( LengthTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 5.47722578f, 5.47722578f, 5.47722578f, 5.47722578f );

    Math::Vector<float, 4> result = Length( q1 );

    auto equal = Equal( result, expected );

    BOOST_CHECK( equal );
}

// --run_test=QuaternionTests/ReciprocalLengthTest1
BOOST_AUTO_TEST_CASE( ReciprocalLengthTest1 )
{
    Q q1( 2.f, 3.f, 4.f, 1.f );

    Math::Vector<float, 4> expected( 0.182574183f, 0.182574183f, 0.182574183f, 0.182574183f );

    Math::Vector<float, 4> result = ReciprocalLength( q1 );

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

BOOST_AUTO_TEST_SUITE_END( )