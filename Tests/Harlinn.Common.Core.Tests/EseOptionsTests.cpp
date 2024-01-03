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
#include "HCCEseOptions.h"
using namespace Harlinn::Common::Core;

// EseOptionsTests.cpp
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        {
            CoInitializeEx( nullptr, COINIT_MULTITHREADED );
        }
        ~LocalFixture( )
        {
            CoUninitialize( );
        }
    };
}

BOOST_FIXTURE_TEST_SUITE( EseOptionsTests, LocalFixture )

// --run_test=EseOptionsTests/LoadOptionsTest
BOOST_AUTO_TEST_CASE( LoadOptionsTest )
{
    auto options = Ese::Options::LoadFromFile( L"EseOptionsTests.xml" );
    bool loaded = options != nullptr;
    BOOST_TEST( loaded );
}


BOOST_AUTO_TEST_SUITE_END( )