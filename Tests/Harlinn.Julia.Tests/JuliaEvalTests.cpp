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

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <JuliaTestFixture.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Julia;

BOOST_FIXTURE_TEST_SUITE( JuliaEvalTests, LocalFixture )

// --run_test=JuliaEvalTests/AsTest1
BOOST_AUTO_TEST_CASE( RunTest1 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<bool>( );
    BOOST_CHECK( resultValue == true );
}

// --run_test=JuliaEvalTests/AsTest2
BOOST_AUTO_TEST_CASE( RunTest2 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<SByte>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest3
BOOST_AUTO_TEST_CASE( RunTest3 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<Byte>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest4
BOOST_AUTO_TEST_CASE( RunTest4 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<Int16>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest5
BOOST_AUTO_TEST_CASE( AsTest5 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<UInt16>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest6
BOOST_AUTO_TEST_CASE( AsTest6 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<Int32>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest7
BOOST_AUTO_TEST_CASE( AsTest7 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<UInt32>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest8
BOOST_AUTO_TEST_CASE( AsTest8 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<Int64>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest9
BOOST_AUTO_TEST_CASE( AsTest9 )
{
    const char* juliaScript = "1";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<UInt64>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest10
BOOST_AUTO_TEST_CASE( AsTest10 )
{
    const char* juliaScript = "Float32(1.0)";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<float>( );
    BOOST_CHECK( resultValue == 1 );
}

// --run_test=JuliaEvalTests/AsTest11
BOOST_AUTO_TEST_CASE( AsTest11 )
{
    const char* juliaScript = "1.0";
    auto result = Eval( juliaScript );
    auto resultValue = result.As<double>( );
    BOOST_CHECK( resultValue == 1 );
}


BOOST_AUTO_TEST_SUITE_END( )