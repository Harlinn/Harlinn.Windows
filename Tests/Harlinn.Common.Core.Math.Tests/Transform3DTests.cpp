#include "pch.h"

using namespace Harlinn::Common::Core;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
    inline bool Equal( const Math::SquareMatrix<float, 4>& m1, const Math::SquareMatrix<float, 4>& m2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }

    template<Math::Internal::TupleType T, Math::Internal::TupleType U>
    inline bool Equal( const T& v1, const U& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }
    template<Math::Internal::TupleType T>
    inline bool Equal( const DirectX::XMFLOAT3& v1, const T& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = (&v1.x)[ i ];
            float value2 = v2[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    template<Math::Internal::TupleType T>
    inline bool Equal( const T& v1, const DirectX::XMFLOAT3& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = v1[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }

    inline bool Equal( const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2, float epsilon = 0.0001f )
    {
        for ( size_t i = 0; i < 3; i++ )
        {
            auto value1 = ( &v1.x )[ i ];
            float value2 = ( &v2.x )[ i ];
            auto delta = value1 - value2;
            if ( std::abs( delta ) > epsilon )
            {
                return false;
            }
        }
        return true;
    }


    inline bool Equal( const pbrt::SquareMatrix<4>& m1, const pbrt::SquareMatrix<4>& m2, float epsilon = 0.0001f )
    {
        for ( int i = 0; i < 4; i++ )
        {
            for ( int j = 0; j < 4; j++ )
            {
                auto v1 = m1[ i ][ j ];
                float v2 = m2[ i ][ j ];
                auto delta = v1 - v2;
                if ( std::abs( delta ) > epsilon )
                {
                    return false;
                }
            }
        }
        return true;
    }

}

BOOST_FIXTURE_TEST_SUITE( Transform3DTests, LocalFixture )

// --run_test=Transform3DTests/RotateTest1
BOOST_AUTO_TEST_CASE( RotateTest1 )
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

// --run_test=Transform3DTests/TranslationTest1
BOOST_AUTO_TEST_CASE( TranslationTest1 )
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

// --run_test=Transform3DTests/ScalingTest1
BOOST_AUTO_TEST_CASE( ScalingTest1 )
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

// --run_test=Transform3DTests/TransformationMatrixTest1
BOOST_AUTO_TEST_CASE( TransformationMatrixTest1 )
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
    auto equal = Equal( expected, result );
    BOOST_CHECK( equal );
}




// --run_test=Transform3DTests/RotateTest2
BOOST_AUTO_TEST_CASE( RotateTest2 )
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


BOOST_AUTO_TEST_SUITE_END( )