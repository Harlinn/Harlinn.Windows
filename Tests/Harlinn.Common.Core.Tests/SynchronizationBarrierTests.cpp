/*
   Copyright 2024-2025 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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