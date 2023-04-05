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

BOOST_FIXTURE_TEST_SUITE( SlimReaderWriterLockTests, LocalFixture )

// --run_test=SlimReaderWriterLockTests/AcquireExclusiveTest1
BOOST_AUTO_TEST_CASE( AcquireExclusiveTest1 )
{
    static_assert( std::is_copy_assignable_v<SlimReaderWriterLock> == false );
    static_assert( std::is_copy_constructible_v<SlimReaderWriterLock> == false );
    static_assert( std::is_move_assignable_v<SlimReaderWriterLock> == false );
    static_assert( std::is_move_constructible_v<SlimReaderWriterLock> == false );

    SlimReaderWriterLock slimReaderWriterLock;
    slimReaderWriterLock.AcquireExclusive( );
    EventWaitHandle event( true );
    bool success = false;

    Thread thread( [&slimReaderWriterLock, &event,&success]( )
    {
        slimReaderWriterLock.AcquireExclusive();
        success = true;
        event.Signal( );
        slimReaderWriterLock.ReleaseExclusive( );
    } );
    slimReaderWriterLock.ReleaseExclusive( );
    BOOST_CHECK( event.Wait( ) );
    slimReaderWriterLock.AcquireExclusive( );
    BOOST_CHECK( success );
    BOOST_CHECK( thread.Wait( ) );
}

// --run_test=SlimReaderWriterLockTests/TryAcquireExclusiveTest1
BOOST_AUTO_TEST_CASE( TryAcquireExclusiveTest1 )
{
    SlimReaderWriterLock slimReaderWriterLock;
    slimReaderWriterLock.AcquireExclusive( );
    EventWaitHandle event( true );
    bool success = false;

    Thread thread( [&slimReaderWriterLock, &event, &success]( )
    {
        while ( !slimReaderWriterLock.TryAcquireExclusive( ) )
        {
            
        }
        success = true;
        event.Signal( );
        slimReaderWriterLock.ReleaseExclusive( );
    } );
    slimReaderWriterLock.ReleaseExclusive( );
    BOOST_CHECK( event.Wait( ) );
    slimReaderWriterLock.AcquireExclusive( );
    BOOST_CHECK( success );
    BOOST_CHECK( thread.Wait( ) );
}



// --run_test=SlimReaderWriterLockTests/AcquireSharedTest1
BOOST_AUTO_TEST_CASE( AcquireSharedTest1 )
{
    SlimReaderWriterLock slimReaderWriterLock;
    slimReaderWriterLock.AcquireExclusive( );
    EventWaitHandle event( true );
    bool success = false;

    Thread thread( [&slimReaderWriterLock, &event, &success]( )
    {
        slimReaderWriterLock.AcquireShared( );
        success = true;
        event.Signal( );
        slimReaderWriterLock.ReleaseShared( );
    } );
    slimReaderWriterLock.ReleaseExclusive( );
    BOOST_CHECK( event.Wait( ) );
    slimReaderWriterLock.AcquireExclusive( );
    BOOST_CHECK( success );
    BOOST_CHECK( thread.Wait( ) );
}


// --run_test=SlimReaderWriterLockTests/TryAcquireSharedTest1
BOOST_AUTO_TEST_CASE( TryAcquireSharedTest1 )
{
    SlimReaderWriterLock slimReaderWriterLock;
    slimReaderWriterLock.AcquireExclusive( );
    EventWaitHandle event( true );
    bool success = false;

    Thread thread( [&slimReaderWriterLock, &event, &success]( )
    {
        while ( !slimReaderWriterLock.TryAcquireShared( ) )
        {
        }
        success = true;
        event.Signal( );
        slimReaderWriterLock.ReleaseShared( );
    } );
    slimReaderWriterLock.ReleaseExclusive( );
    BOOST_CHECK( event.Wait( ) );
    slimReaderWriterLock.AcquireExclusive( );
    BOOST_CHECK( success );
    BOOST_CHECK( thread.Wait( ) );
}



BOOST_AUTO_TEST_SUITE_END( )