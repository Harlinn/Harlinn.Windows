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

BOOST_FIXTURE_TEST_SUITE( ArrayTests, LocalFixture )

BOOST_AUTO_TEST_CASE( StdArraySupportsConstexprConcatTest1 )
{
    std::array<Byte, 1> a1{};
    std::array<Byte, 2> a2{};
    auto a3 = a1 + a2;

    constexpr signed char buffer1[] = { 1,2,3 };
    constexpr unsigned char buffer2[] = { 1,2,3 };
    constexpr char buffer3[] = "hello";
    constexpr int buffer4[] = { 1,2,3 };
    constexpr auto length1 = LengthOf( buffer1 );
    constexpr auto length2 = LengthOf( buffer2 );
    constexpr auto length3 = LengthOf( buffer3 );
    constexpr auto length4 = LengthOf( buffer4 );
}

// --run_test=ArrayTests/ArrayConcatTest1
BOOST_AUTO_TEST_CASE( ArrayConcatTest1 )
{
    constexpr std::array a1{ 1 };
    constexpr std::array a2{ 2 };
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = a3[0];
    constexpr auto v2 = a3[1];

    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    
}

BOOST_AUTO_TEST_SUITE_END( )
