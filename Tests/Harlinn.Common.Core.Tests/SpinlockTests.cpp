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

BOOST_FIXTURE_TEST_SUITE( SpinlockTests, LocalFixture )

// --run_test=SpinlockTests/LockTest1
BOOST_AUTO_TEST_CASE( LockTest1 )
{
    Spinlock spinlock( true );
    EventWaitHandle event( true );

    Thread thread( [&spinlock, &event]( )
    {
        spinlock.lock();
        event.Signal( );
        spinlock.unlock( );
    } );
    spinlock.unlock( );
    BOOST_CHECK( event.Wait( ) );
    spinlock.lock( );
    BOOST_CHECK( thread.Wait( ) );
}

// --run_test=SpinlockTests/TryLockTest1
BOOST_AUTO_TEST_CASE( TryLockTest1 )
{
    Spinlock spinlock( true );
    EventWaitHandle event( true );

    Thread thread( [&spinlock, &event]( )
    {
        while ( !spinlock.try_lock( ) )
        {
        }
        event.Signal( );
        spinlock.unlock( );
    } );
    spinlock.unlock( );
    BOOST_CHECK( event.Wait( ) );
    spinlock.lock( );
    BOOST_CHECK( thread.Wait( ) );
}


BOOST_AUTO_TEST_SUITE_END( )
