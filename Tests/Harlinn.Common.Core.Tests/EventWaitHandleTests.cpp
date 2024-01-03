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

BOOST_FIXTURE_TEST_SUITE( EventWaitHandleTests, LocalFixture )

// --run_test=EventWaitHandleTests/DefaultConstructorTest1
BOOST_AUTO_TEST_CASE( DefaultConstructorTest1 )
{
    EventWaitHandle event1;
    BOOST_CHECK( event1.GetHandle() == 0 );
}


// --run_test=EventWaitHandleTests/MoveTest1
BOOST_AUTO_TEST_CASE( MoveTest1 )
{
    EventWaitHandle event1;
    BOOST_CHECK( event1.GetHandle( ) == 0 );
    EventWaitHandle event2( true );
    BOOST_CHECK( event2.GetHandle( ) != 0 );
    event1 = std::move( event2 );
    BOOST_CHECK( event1.GetHandle( ) != 0 );
    BOOST_CHECK( event2.GetHandle( ) == 0 );

    Thread thread( [&event1]( )
    {
        event1.Signal( );
    } );

    BOOST_CHECK( event1.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}



// --run_test=EventWaitHandleTests/WaitTest1
BOOST_AUTO_TEST_CASE( WaitTest1 )
{
    EventWaitHandle event1( true );

    Thread thread( [&event1]( )
    {
        event1.Signal( );
    } );

    BOOST_CHECK( event1.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}


// --run_test=EventWaitHandleTests/WaitWithTimeoutTest1
BOOST_AUTO_TEST_CASE( WaitWithTimeoutTest1 )
{
    EventWaitHandle event1( true );
    EventWaitHandle event2( true );

    Thread thread( [&event1,&event2]( )
    {
        event1.Wait( );
        event2.Signal( );
    } );

    BOOST_CHECK( event2.Wait( 500 ) == false );
    event1.Signal( );
    BOOST_CHECK( event2.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}


// --run_test=EventWaitHandleTests/OpenTest1
BOOST_AUTO_TEST_CASE( OpenTest1 )
{
    WideString eventName(L"OpenTest1EventName" );
    EventWaitHandle event1( eventName, true );

    Thread thread( [&eventName]( )
    {
        try
        {
            auto event = EventWaitHandle::OpenExisting( eventName );
            event.Signal( );
        }
        catch ( std::exception& exc )
        {
            printf("Exception:%s\n", exc.what( ));
        }
    } );

    BOOST_CHECK( event1.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}


// --run_test=EventWaitHandleTests/TryOpenTest1
BOOST_AUTO_TEST_CASE( TryOpenTest1 )
{
    WideString eventName( L"TryOpenTest1EventName" );
    EventWaitHandle event1( eventName, true );

    Thread thread( [&eventName]( )
    {
        try
        {
            auto event = EventWaitHandle::TryOpenExisting( eventName );
            event.Signal( );
        }
        catch ( std::exception& exc )
        {
            printf( "Exception:%s\n", exc.what( ) );
        }
    } );

    BOOST_CHECK( event1.Wait( ) );
    BOOST_CHECK( thread.Wait( ) );
}






BOOST_AUTO_TEST_SUITE_END( )