#include <HCCVectorMath.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Math;

namespace Basics
{

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
                axis = Cross( fromDirNormalized, Vector3f::Up() );
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
            Quaternion result( cp, s[0] * 0.5f );
            return result;
        }
    }
}

#if 1
int main( int argc, char* argv[ ] )
{
    Vector3f fromVector( 2.f, 2.f, 1.f );
    Vector3f toVector( 2.f, 1.f, 2.f );

    Quaternion<float> q1 = Basics::ShortestArc1( fromVector, toVector );
    Quaternion<float> q2 = Basics::ShortestArc2( fromVector.ToSimd( ), toVector.ToSimd( ) );
    Quaternion<float> qm = ShortestArc( fromVector, toVector );

    if ( q1 != qm )
    {
        PrintLn( "Oops!{} != {}", q1, qm );
    }
    if ( q2 != qm )
    {
        PrintLn( "Oops!{} != {}", q2, qm );
    }
    else
    {
        PrintLn( "Cool!" );
    }

}
#else
int main( )
{
    Vector3f::Simd v1( 1.f, 2.f, 3.f );
    auto v2 = Sqrt( v1 );
    auto v3 = v2.Values( );
    static_assert( std::is_same_v<decltype( v3 ), Vector3f> );
    PrintLn( "x:{}, y:{}, z:{}", v3.x, v3.y, v3.z );
}
#endif