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

BOOST_FIXTURE_TEST_SUITE( TimerQueueTests, LocalFixture )

// --run_test=TimerQueueTests/WaitTest1
BOOST_AUTO_TEST_CASE( WaitTest1 )
{
    size_t counter = 0;
    EventWaitHandle event( true );

    TimerQueue timerQueue;
    auto timer = timerQueue.CreateTimer( 100, 100, TimerQueueTimerFlags::Default, [&counter,&event]( )
    {
        counter++;
        if ( counter == 5 )
        {
            event.Signal( );
        }
    } );

    BOOST_CHECK( event.Wait( ) );
    timer.Close( );
    timerQueue.Close( );
}




BOOST_AUTO_TEST_SUITE_END( )
