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
}


BOOST_FIXTURE_TEST_SUITE( IntervalTests, LocalFixture )

// --run_test=IntervalTests/IntersectsTest
BOOST_AUTO_TEST_CASE( IntersectsTest )
{
    Interval firstInterval( DateTime( 11LL ), DateTime( 12LL ) );
    Interval secondInterval( DateTime( 12LL ), DateTime( 13LL ) );
    bool intersects1 = firstInterval.Intersects( secondInterval );
    BOOST_CHECK( intersects1 );
    bool intersects2 = secondInterval.Intersects( firstInterval );
    BOOST_CHECK( intersects2 );

    Interval thirdInterval( DateTime( 13LL ), DateTime( 14LL ) );
    bool intersects3 = firstInterval.Intersects( thirdInterval );
    BOOST_CHECK( intersects3 == false );
    bool intersects4 = thirdInterval.Intersects( firstInterval );
    BOOST_CHECK( intersects4 == false );

    Interval fourthInterval( DateTime( 10LL ), DateTime( 13LL ) );
    bool intersects5 = firstInterval.Intersects( fourthInterval );
    BOOST_CHECK( intersects5 );
    bool intersects6 = fourthInterval.Intersects( firstInterval );
    BOOST_CHECK( intersects6 );


}

BOOST_AUTO_TEST_SUITE_END( )