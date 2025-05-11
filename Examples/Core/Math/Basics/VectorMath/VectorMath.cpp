#include <HCCVectorMath.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Math;

namespace Basics
{
    using Quaternion = Math::Quaternion<float>;


    // The Shortest Arc Quaternion as described by Sam Melax in Game Programming Gems

    Quaternion ShortestArc( const Vector3f& fromDir, const Vector3f& toDir ) noexcept
    {
        using Traits = Vector3f::Traits;
        using Constants = Traits::Constants::Base;

        Vector3f fromDirNormalized = Normalize( fromDir );
        Vector3f toDirNormalized = Normalize( toDir );

        const auto dot = ScalarDot( fromDirNormalized, toDirNormalized );
        if ( dot >= 1.f )
        {
            return Quaternion::Identity( );
        }
        else if ( dot <= -1.f )
        {
            auto axis = Math::Cross( fromDirNormalized, Vector3f::Right( ) );
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
}


int main( int argc, char* argv[ ] )
{
    Vector3f fromVector( 2.f, 2.f, 1.f );
    Vector3f toVector( 2.f, 1.f, 2.f );

    Quaternion<float> q1 = Basics::ShortestArc( fromVector, toVector );
    Quaternion<float> q2 = ShortestArc( fromVector, toVector );

    if ( q1 != q2 )
    {
        PrintLn( "Oops!{} != {}", q1, q2 );
    }
    else
    {
        PrintLn( "Cool!" );
    }

}

