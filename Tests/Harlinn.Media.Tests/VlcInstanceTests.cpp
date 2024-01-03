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

#include <HWMVlc.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Windows;
using namespace Harlinn::Media;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( VlcInstanceTests, LocalFixture )

// --run_test=VlcInstanceTests/VersionTest1
BOOST_AUTO_TEST_CASE( VersionTest1 )
{
    auto version = Vlc::Instance::Version( );
    BOOST_CHECK( version != nullptr );

}

// --run_test=VlcInstanceTests/InstanceCreateTest1
BOOST_AUTO_TEST_CASE( InstanceCreateTest1 )
{
    auto instance = Vlc::Instance::Create( );
    BOOST_CHECK( instance != nullptr );

}

// --run_test=VlcInstanceTests/AudioFiltersTest1
BOOST_AUTO_TEST_CASE( AudioFiltersTest1 )
{
    auto instance = Vlc::Instance::Create( );
    BOOST_CHECK( instance != nullptr );
    auto filters = instance.AudioFilters( );
    BOOST_CHECK( filters.size( ) > 0 );
}

// --run_test=VlcInstanceTests/VideoFiltersTest1
BOOST_AUTO_TEST_CASE( VideoFiltersTest1 )
{
    auto instance = Vlc::Instance::Create( );
    BOOST_CHECK( instance != nullptr );
    auto filters = instance.VideoFilters( );
    BOOST_CHECK( filters.size( ) > 0 );
}


BOOST_AUTO_TEST_SUITE_END( )
