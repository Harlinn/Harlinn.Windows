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

BOOST_FIXTURE_TEST_SUITE( SynchronizationBarrierTests, LocalFixture )

// --run_test=SynchronizationBarrierTests/EnterTest1
BOOST_AUTO_TEST_CASE( EnterTest1 )
{
    static_assert( std::is_copy_assignable_v<SynchronizationBarrier> == false );
    static_assert( std::is_copy_constructible_v<SynchronizationBarrier> == false );
    static_assert( std::is_move_assignable_v<SynchronizationBarrier> == false );
    static_assert( std::is_move_constructible_v<SynchronizationBarrier> == false );

    constexpr UInt32 ThreadCount = 10;
    SynchronizationBarrier barrier( ThreadCount );
    std::atomic<UInt32> threadsEntered;
    ThreadGroup threadGroup;
    for ( UInt32 i = 0; i < ThreadCount; ++i )
    {
        threadGroup.Add( [&barrier,&threadsEntered]( )
        {
            barrier.Enter( );
            threadsEntered++;
        } );
    }
    threadGroup.join( );
    BOOST_CHECK( threadsEntered.load( ) == ThreadCount );
    
}


BOOST_AUTO_TEST_SUITE_END( )