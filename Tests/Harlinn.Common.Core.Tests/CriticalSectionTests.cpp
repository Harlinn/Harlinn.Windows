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

BOOST_FIXTURE_TEST_SUITE( CriticalSectionTests, LocalFixture )

// --run_test=CriticalSectionTests/DefaultConstructorTest1
BOOST_AUTO_TEST_CASE( DefaultConstructorTest1 )
{
    static_assert( std::is_copy_assignable_v<CriticalSection> == false );
    static_assert( std::is_copy_constructible_v<CriticalSection> == false );
    static_assert( std::is_move_assignable_v<CriticalSection> == false );
    static_assert( std::is_move_constructible_v<CriticalSection> == false );
    CriticalSection criticalSection1;
    BOOST_CHECK( criticalSection1.TryEnter() );
}

// --run_test=CriticalSectionTests/EnterTest1
BOOST_AUTO_TEST_CASE( EnterTest1 )
{
    CriticalSection criticalSection;
    criticalSection.Enter( );
    EventWaitHandle event( true );

    Thread thread( [&criticalSection, &event]( )
    {
        criticalSection.Enter( );
        event.Signal( );
        criticalSection.Leave( );
    } );
    criticalSection.Leave( );
    BOOST_CHECK( event.Wait( ) );
    criticalSection.Enter();
    BOOST_CHECK( thread.Wait( ) );
}

// --run_test=CriticalSectionTests/TryEnterTest1
BOOST_AUTO_TEST_CASE( TryEnterTest1 )
{
    CriticalSection criticalSection;
    criticalSection.Enter( );
    EventWaitHandle event( true );
    std::atomic<bool> enteredCriticalSection = false;
    Thread thread( [&criticalSection, &event,&enteredCriticalSection]( )
    {
        if ( criticalSection.TryEnter( ) )
        {
            enteredCriticalSection = true;
            event.Signal( );
            criticalSection.Leave( );
        }
        else
        {
            event.Signal( );
        }
    } );
    criticalSection.Leave( );
    BOOST_CHECK( event.Wait( ) );
    criticalSection.Enter( );
    BOOST_CHECK( enteredCriticalSection.load() == true );
    BOOST_CHECK( thread.Wait( ) );
}




BOOST_AUTO_TEST_SUITE_END( )