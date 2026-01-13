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
        LocalFixture( )
        {
        }
        ~LocalFixture( )
        {
        }
    };
}

BOOST_FIXTURE_TEST_SUITE( BitsTests, LocalFixture )

// --run_test=BitsTests/Bits1Test1
BOOST_AUTO_TEST_CASE( Bits1Test1 )
{
    using BitsType = Bits<1>;
    BitsType bits1( 0 );
    BOOST_CHECK( bits1[0] == false );
    bits1[0] = true;
    BOOST_CHECK( bits1[0] == true );

    BitsType bits2( 0 );

    BitsType bits3 = bits1 & bits2;
    BOOST_CHECK( bits3[0] == false );

    BitsType bits4 = bits1 | bits2;
    BOOST_CHECK( bits4[0] == true );

    BitsType bits5 = bits1 ^ bits2;
    BOOST_CHECK( bits5[0] == true );

    BitsType bits6( 0 );
    BitsType bits7 = bits6 & bits2;
    BOOST_CHECK( bits7[0] == false );

    BitsType bits8 = bits6 | bits2;
    BOOST_CHECK( bits8[0] == false );

    BitsType bits9 = bits6 ^ bits2;
    BOOST_CHECK( bits9[0] == false );
}

// --run_test=BitsTests/Bits2Test1
BOOST_AUTO_TEST_CASE( Bits2Test1 )
{
    constexpr size_t Size = 2;
    using BitsType = Bits<2>;
    constexpr BitsType::word_type Off = 0;
    constexpr BitsType::word_type OneOn = 0b01;
    constexpr BitsType::word_type OneOnReversed = 0b10;
    constexpr BitsType::word_type On = 0b11;
    constexpr BitsType::word_type OffOn = 0b01;
    constexpr BitsType::word_type OnOff = 0b10;
    constexpr BitsType bitsOff( Off );
    constexpr BitsType bitsOneOn( OneOn );
    constexpr BitsType bitsOneOnReversed( OneOnReversed );
    constexpr BitsType bitsOn( On );
    constexpr BitsType bitsOffOn( OffOn );
    constexpr BitsType bitsOnOff( OnOff );

    constexpr auto count1a = bitsOff.count( );
    BOOST_CHECK( count1a == 0 );
    auto count1b = bitsOff.count( );
    BOOST_CHECK( count1b == 0 );

    constexpr auto count2a = bitsOneOn.count( );
    BOOST_CHECK( count2a == 1 );
    auto count2b = bitsOneOn.count( );
    BOOST_CHECK( count2b == 1 );

    constexpr auto count3a = bitsOneOnReversed.count( );
    BOOST_CHECK( count3a == 1 );
    auto count3b = bitsOneOnReversed.count( );
    BOOST_CHECK( count3b == 1 );

    constexpr auto count4a = bitsOn.count( );
    BOOST_CHECK( count4a == Size );
    auto count4b = bitsOn.count( );
    BOOST_CHECK( count4b == Size );

    BitsType bits1( 0 );
    BOOST_CHECK( bits1 == bitsOff );
    
    bits1[0] = true;
    BOOST_CHECK( bits1 == bitsOffOn );

    constexpr auto bits2 = bitsOff & bitsOff;
    BOOST_CHECK( bits2 == bitsOff );

    constexpr auto bits3 = bitsOff & bitsOn;
    BOOST_CHECK( bits3 == bitsOff );

    constexpr auto bits4 = bitsOffOn & bitsOnOff;
    BOOST_CHECK( bits4 == bitsOff );

    constexpr auto bits5 = bitsOffOn & bitsOffOn;
    BOOST_CHECK( bits5 == bitsOffOn );

    constexpr auto bits6 = bitsOn & bitsOn;
    BOOST_CHECK( bits6 == bitsOn );

    constexpr auto bits7 = bitsOffOn.reversed( );
    BOOST_CHECK( bits7 == bitsOnOff );

    constexpr auto bits8 = bitsOff | bitsOff;
    BOOST_CHECK( bits8 == bitsOff );

    constexpr auto bits9 = bitsOff | bitsOn;
    BOOST_CHECK( bits9 == bitsOn );

    constexpr auto bits10 = bitsOffOn | bitsOnOff;
    BOOST_CHECK( bits10 == bitsOn );

    constexpr auto bits11 = bitsOffOn | bitsOffOn;
    BOOST_CHECK( bits11 == bitsOffOn );

    constexpr auto bits12 = bitsOn | bitsOn;
    BOOST_CHECK( bits12 == bitsOn );

    constexpr auto bits13 = bitsOff ^ bitsOff;
    BOOST_CHECK( bits13 == bitsOff );

    constexpr auto bits14 = bitsOff ^ bitsOn;
    BOOST_CHECK( bits14 == bitsOn );

    constexpr auto bits15 = bitsOffOn ^ bitsOnOff;
    BOOST_CHECK( bits15 == bitsOn );

    constexpr auto bits16 = bitsOffOn ^ bitsOffOn;
    BOOST_CHECK( bits16 == bitsOff );

    constexpr auto bits17 = bitsOn ^ bitsOn;
    BOOST_CHECK( bits17 == bitsOff );
}

// --run_test=BitsTests/Bits3Test1
BOOST_AUTO_TEST_CASE( Bits3Test1 )
{
    constexpr size_t Size = 3;
    using BitsType = Bits<3>;
    constexpr BitsType::word_type Off = 0;
    constexpr BitsType::word_type OneOn = 0b001;
    constexpr BitsType::word_type OneOnReversed = 0b100;
    constexpr BitsType::word_type On = 0b111;
    constexpr BitsType::word_type OffOn = 0b101;
    constexpr BitsType::word_type OffOnReversed = 0b101;
    constexpr BitsType::word_type OnOff = 0b010;
    constexpr BitsType bitsOff( Off );
    constexpr BitsType bitsOneOn( OneOn );
    constexpr BitsType bitsOneOnReversed( OneOnReversed );
    constexpr BitsType bitsOn( On );
    constexpr BitsType bitsOffOn( OffOn );
    constexpr BitsType bitsOffOnReversed( OffOnReversed );
    constexpr BitsType bitsOnOff( OnOff );

    constexpr auto count1a = bitsOff.count( );
    BOOST_CHECK( count1a == 0 );
    auto count1b = bitsOff.count( );
    BOOST_CHECK( count1b == 0 );

    constexpr auto count2a = bitsOneOn.count( );
    BOOST_CHECK( count2a == 1 );
    auto count2b = bitsOneOn.count( );
    BOOST_CHECK( count2b == 1 );

    constexpr auto count3a = bitsOneOnReversed.count( );
    BOOST_CHECK( count3a == 1 );
    auto count3b = bitsOneOnReversed.count( );
    BOOST_CHECK( count3b == 1 );

    constexpr auto count4a = bitsOn.count( );
    BOOST_CHECK( count4a == Size );
    auto count4b = bitsOn.count( );
    BOOST_CHECK( count4b == Size );


    BitsType bits1( 0 );
    BOOST_CHECK( bits1 == bitsOff );

    bits1[0] = true;
    BOOST_CHECK( bits1 == bitsOneOn );

    constexpr auto bits2 = bitsOff & bitsOff;
    BOOST_CHECK( bits2 == bitsOff );

    constexpr auto bits3 = bitsOff & bitsOn;
    BOOST_CHECK( bits3 == bitsOff );

    constexpr auto bits4 = bitsOffOn & bitsOnOff;
    BOOST_CHECK( bits4 == bitsOff );

    constexpr auto bits5 = bitsOffOn & bitsOffOn;
    BOOST_CHECK( bits5 == bitsOffOn );

    constexpr auto bits6 = bitsOn & bitsOn;
    BOOST_CHECK( bits6 == bitsOn );

    constexpr auto bits7a = bitsOffOn.reversed( );
    BOOST_CHECK( bits7a == bitsOffOnReversed );

    constexpr auto bits7b = bitsOneOn.reversed( );
    BOOST_CHECK( bits7b == bitsOneOnReversed );

    constexpr auto bits8 = bitsOff | bitsOff;
    BOOST_CHECK( bits8 == bitsOff );

    constexpr auto bits9 = bitsOff | bitsOn;
    BOOST_CHECK( bits9 == bitsOn );

    constexpr auto bits10 = bitsOffOn | bitsOnOff;
    BOOST_CHECK( bits10 == bitsOn );

    constexpr auto bits11 = bitsOffOn | bitsOffOn;
    BOOST_CHECK( bits11 == bitsOffOn );

    constexpr auto bits12 = bitsOn | bitsOn;
    BOOST_CHECK( bits12 == bitsOn );

    constexpr auto bits13 = bitsOff ^ bitsOff;
    BOOST_CHECK( bits13 == bitsOff );

    constexpr auto bits14 = bitsOff ^ bitsOn;
    BOOST_CHECK( bits14 == bitsOn );

    constexpr auto bits15 = bitsOffOn ^ bitsOnOff;
    BOOST_CHECK( bits15 == bitsOn );

    constexpr auto bits16 = bitsOffOn ^ bitsOffOn;
    BOOST_CHECK( bits16 == bitsOff );

    constexpr auto bits17 = bitsOn ^ bitsOn;
    BOOST_CHECK( bits17 == bitsOff );
}

// --run_test=BitsTests/Bits7Test1
BOOST_AUTO_TEST_CASE( Bits7Test1 )
{
    constexpr size_t Size = 7;
    using BitsType = Bits<Size>;
    constexpr BitsType::word_type Off = 0;
    constexpr BitsType::word_type OneOn = 0b0000001;
    constexpr BitsType::word_type OneOnReversed = 0b1000000;
    constexpr BitsType::word_type On = 0b1111111;
    constexpr BitsType::word_type OffOn = 0b1010101;
    constexpr BitsType::word_type OffOnReversed = 0b1010101;
    constexpr BitsType::word_type OnOff = 0b0101010;
    constexpr BitsType bitsOff( Off );
    constexpr BitsType bitsOneOn( OneOn );
    constexpr BitsType bitsOneOnReversed( OneOnReversed );
    constexpr BitsType bitsOn( On );
    constexpr BitsType bitsOffOn( OffOn );
    constexpr BitsType bitsOffOnReversed( OffOnReversed );
    constexpr BitsType bitsOnOff( OnOff );

    constexpr auto count1a = bitsOff.count( );
    BOOST_CHECK( count1a == 0 );
    auto count1b = bitsOff.count( );
    BOOST_CHECK( count1b == 0 );

    constexpr auto count2a = bitsOneOn.count( );
    BOOST_CHECK( count2a == 1 );
    auto count2b = bitsOneOn.count( );
    BOOST_CHECK( count2b == 1 );

    constexpr auto count3a = bitsOneOnReversed.count( );
    BOOST_CHECK( count3a == 1 );
    auto count3b = bitsOneOnReversed.count( );
    BOOST_CHECK( count3b == 1 );

    constexpr auto count4a = bitsOn.count( );
    BOOST_CHECK( count4a == Size );
    auto count4b = bitsOn.count( );
    BOOST_CHECK( count4b == Size );


    BitsType bits1( 0 );
    BOOST_CHECK( bits1 == bitsOff );

    bits1[0] = true;
    BOOST_CHECK( bits1 == bitsOneOn );

    constexpr auto bits2 = bitsOff & bitsOff;
    BOOST_CHECK( bits2 == bitsOff );

    constexpr auto bits3 = bitsOff & bitsOn;
    BOOST_CHECK( bits3 == bitsOff );

    constexpr auto bits4 = bitsOffOn & bitsOnOff;
    BOOST_CHECK( bits4 == bitsOff );

    constexpr auto bits5 = bitsOffOn & bitsOffOn;
    BOOST_CHECK( bits5 == bitsOffOn );

    constexpr auto bits6 = bitsOn & bitsOn;
    BOOST_CHECK( bits6 == bitsOn );

    constexpr auto bits7a = bitsOffOn.reversed( );
    BOOST_CHECK( bits7a == bitsOffOnReversed );

    constexpr auto bits7b = bitsOneOn.reversed( );
    BOOST_CHECK( bits7b == bitsOneOnReversed );

    constexpr auto bits8 = bitsOff | bitsOff;
    BOOST_CHECK( bits8 == bitsOff );

    constexpr auto bits9 = bitsOff | bitsOn;
    BOOST_CHECK( bits9 == bitsOn );

    constexpr auto bits10 = bitsOffOn | bitsOnOff;
    BOOST_CHECK( bits10 == bitsOn );

    constexpr auto bits11 = bitsOffOn | bitsOffOn;
    BOOST_CHECK( bits11 == bitsOffOn );

    constexpr auto bits12 = bitsOn | bitsOn;
    BOOST_CHECK( bits12 == bitsOn );

    constexpr auto bits13 = bitsOff ^ bitsOff;
    BOOST_CHECK( bits13 == bitsOff );

    constexpr auto bits14 = bitsOff ^ bitsOn;
    BOOST_CHECK( bits14 == bitsOn );

    constexpr auto bits15 = bitsOffOn ^ bitsOnOff;
    BOOST_CHECK( bits15 == bitsOn );

    constexpr auto bits16 = bitsOffOn ^ bitsOffOn;
    BOOST_CHECK( bits16 == bitsOff );

    constexpr auto bits17 = bitsOn ^ bitsOn;
    BOOST_CHECK( bits17 == bitsOff );
}

// --run_test=BitsTests/Bits8Test1
BOOST_AUTO_TEST_CASE( Bits8Test1 )
{
    constexpr size_t Size = 8;
    using BitsType = Bits<Size>;
    constexpr BitsType::word_type Off = 0;
    constexpr BitsType::word_type OneOn = 0b00000001;
    constexpr BitsType::word_type OneOnReversed = 0b10000000;
    constexpr BitsType::word_type On = 0b11111111;
    constexpr BitsType::word_type OffOn = 0b01010101;
    constexpr BitsType::word_type OffOnReversed = 0b10101010;
    constexpr BitsType::word_type OnOff = 0b10101010;
    constexpr BitsType bitsOff( Off );
    constexpr BitsType bitsOneOn( OneOn );
    constexpr BitsType bitsOneOnReversed( OneOnReversed );
    constexpr BitsType bitsOn( On );
    constexpr BitsType bitsOffOn( OffOn );
    constexpr BitsType bitsOffOnReversed( OffOnReversed );
    constexpr BitsType bitsOnOff( OnOff );

    constexpr auto count1a = bitsOff.count( );
    BOOST_CHECK( count1a == 0 );
    auto count1b = bitsOff.count( );
    BOOST_CHECK( count1b == 0 );

    constexpr auto count2a = bitsOneOn.count( );
    BOOST_CHECK( count2a == 1 );
    auto count2b = bitsOneOn.count( );
    BOOST_CHECK( count2b == 1 );

    constexpr auto count3a = bitsOneOnReversed.count( );
    BOOST_CHECK( count3a == 1 );
    auto count3b = bitsOneOnReversed.count( );
    BOOST_CHECK( count3b == 1 );

    constexpr auto count4a = bitsOn.count( );
    BOOST_CHECK( count4a == Size );
    auto count4b = bitsOn.count( );
    BOOST_CHECK( count4b == Size );



    BitsType bits1( 0 );
    BOOST_CHECK( bits1 == bitsOff );

    bits1[0] = true;
    BOOST_CHECK( bits1 == bitsOneOn );

    constexpr auto bits2 = bitsOff & bitsOff;
    BOOST_CHECK( bits2 == bitsOff );

    constexpr auto bits3 = bitsOff & bitsOn;
    BOOST_CHECK( bits3 == bitsOff );

    constexpr auto bits4 = bitsOffOn & bitsOnOff;
    BOOST_CHECK( bits4 == bitsOff );

    constexpr auto bits5 = bitsOffOn & bitsOffOn;
    BOOST_CHECK( bits5 == bitsOffOn );

    constexpr auto bits6 = bitsOn & bitsOn;
    BOOST_CHECK( bits6 == bitsOn );

    constexpr auto bits7a = bitsOffOn.reversed( );
    BOOST_CHECK( bits7a == bitsOffOnReversed );

    constexpr auto bits7b = bitsOneOn.reversed( );
    BOOST_CHECK( bits7b == bitsOneOnReversed );

    constexpr auto bits8 = bitsOff | bitsOff;
    BOOST_CHECK( bits8 == bitsOff );

    constexpr auto bits9 = bitsOff | bitsOn;
    BOOST_CHECK( bits9 == bitsOn );

    constexpr auto bits10 = bitsOffOn | bitsOnOff;
    BOOST_CHECK( bits10 == bitsOn );

    constexpr auto bits11 = bitsOffOn | bitsOffOn;
    BOOST_CHECK( bits11 == bitsOffOn );

    constexpr auto bits12 = bitsOn | bitsOn;
    BOOST_CHECK( bits12 == bitsOn );

    constexpr auto bits13 = bitsOff ^ bitsOff;
    BOOST_CHECK( bits13 == bitsOff );

    constexpr auto bits14 = bitsOff ^ bitsOn;
    BOOST_CHECK( bits14 == bitsOn );

    constexpr auto bits15 = bitsOffOn ^ bitsOnOff;
    BOOST_CHECK( bits15 == bitsOn );

    constexpr auto bits16 = bitsOffOn ^ bitsOffOn;
    BOOST_CHECK( bits16 == bitsOff );

    constexpr auto bits17 = bitsOn ^ bitsOn;
    BOOST_CHECK( bits17 == bitsOff );
}


BOOST_AUTO_TEST_SUITE_END( )