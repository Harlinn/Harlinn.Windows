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

BOOST_FIXTURE_TEST_SUITE( MutexTests, LocalFixture )

// --run_test=MutexTests/WaitTest1
BOOST_AUTO_TEST_CASE( WaitTest1 )
{
    Mutex mutex( true );
    EventWaitHandle event(true);

    Thread thread( [&mutex,&event]( )
    {
        mutex.Wait();
        event.Signal( );
        mutex.Release( );
    } );
    mutex.Release( );
    BOOST_CHECK( event.Wait( ) );
    BOOST_CHECK( mutex.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}

// --run_test=MutexTests/OpenTest1
BOOST_AUTO_TEST_CASE( OpenTest1 )
{
    std::wstring mutexName( L"OpenTest1MutexName" );
    Mutex mutex( mutexName, true );
    EventWaitHandle event(true);

    Thread thread( [&mutexName, &event]( )
    {
        auto mutex = Mutex::OpenExisting( mutexName );
        mutex.Wait( );
        event.Signal( );
        mutex.Release( );
    } );
    mutex.Release( );
    BOOST_CHECK( event.Wait( ) );
    BOOST_CHECK( mutex.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}

// --run_test=MutexTests/TryOpenTest1
BOOST_AUTO_TEST_CASE( TryOpenTest1 )
{
    std::wstring mutexName( L"OpenTest1MutexName" );
    Mutex mutex( mutexName, true );
    EventWaitHandle event( true );

    Thread thread( [&mutexName, &event]( )
    {
        auto mutex = Mutex::TryOpenExisting( mutexName );
        mutex.Wait( );
        event.Signal( );
        mutex.Release( );
    } );
    mutex.Release( );
    BOOST_CHECK( event.Wait( ) );
    BOOST_CHECK( mutex.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}
BOOST_AUTO_TEST_SUITE_END( )
