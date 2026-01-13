/*
   Copyright 2024-2026 Espen Harlinn

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
