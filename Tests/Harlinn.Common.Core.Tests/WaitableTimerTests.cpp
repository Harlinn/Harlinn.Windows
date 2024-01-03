/*
   Copyright 2024 Espen Harlinn

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

BOOST_FIXTURE_TEST_SUITE( WaitableTimerTests, LocalFixture )

// --run_test=WaitableTimerTests/WaitTest1
BOOST_AUTO_TEST_CASE( WaitTest1 )
{
    WaitableTimer waitableTimer( true );
    EventWaitHandle event( true );

    Thread thread( [&waitableTimer, &event]( )
    {
        waitableTimer.Wait( );
        waitableTimer.SetTimer( TimeSpan::FromSeconds( 0.5 ) );
        event.Signal( );
        
    } );
    waitableTimer.SetTimer( TimeSpan::FromSeconds( 0.5 ) );
    BOOST_CHECK( event.Wait( ) );
    BOOST_CHECK( waitableTimer.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}

// --run_test=WaitableTimerTests/OpenTest1
BOOST_AUTO_TEST_CASE( OpenTest1 )
{
    WideString waitableTimerName( L"OpenTest1WaitableTimerName" );
    WaitableTimer waitableTimer( waitableTimerName, true );
    EventWaitHandle event( true );

    Thread thread( [&waitableTimerName, &event]( )
    {
        auto waitableTimer = WaitableTimer::OpenExisting( waitableTimerName );
        waitableTimer.Wait( );
        waitableTimer.SetTimer( TimeSpan::FromSeconds( 0.5 ) );
        event.Signal( );

    } );
    waitableTimer.SetTimer( TimeSpan::FromSeconds( 0.5 ) );
    BOOST_CHECK( event.Wait( ) );
    BOOST_CHECK( waitableTimer.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}

// --run_test=WaitableTimerTests/TryOpenTest1
BOOST_AUTO_TEST_CASE( TryOpenTest1 )
{
    WideString waitableTimerName( L"OpenTest1WaitableTimerName" );
    WaitableTimer waitableTimer( waitableTimerName, true );
    EventWaitHandle event( true );

    Thread thread( [&waitableTimerName, &event]( )
    {
        auto waitableTimer = WaitableTimer::TryOpenExisting( waitableTimerName );
        waitableTimer.Wait( );
        waitableTimer.SetTimer( TimeSpan::FromSeconds( 0.5 ) );
        event.Signal( );

    } );
    waitableTimer.SetTimer( TimeSpan::FromSeconds( 0.5 ) );
    BOOST_CHECK( event.Wait( ) );
    BOOST_CHECK( waitableTimer.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}



BOOST_AUTO_TEST_SUITE_END( )
