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
        LocalFixture( )
        {
        }
        ~LocalFixture( )
        {
        }
    };

    



}

BOOST_FIXTURE_TEST_SUITE( BitsConversionTests, LocalFixture )

// --run_test=BitsConversionTests/CreateBitMask32Tests1
BOOST_AUTO_TEST_CASE( CreateBitMask32Tests1 )
{
    constexpr auto mask = CreateBitMask32( 3 );
    BOOST_CHECK( mask == 7 );
}

// --run_test=BitsConversionTests/ExtractBits32Tests1
BOOST_AUTO_TEST_CASE( ExtractBits32Tests1 )
{
    constexpr auto mask = CreateBitMask32( 3 ) << 1;
    auto value = ExtractBits32( mask, 1,4 );
    BOOST_CHECK( value == 7 );
}



// --run_test=BitsConversionTests/ExtractBits32Tests2
BOOST_AUTO_TEST_CASE( ExtractBits32Tests2 )
{
    constexpr UInt32 source1 = 0b10000000'00000000'00000000'00000000;
    constexpr auto value1a = ExtractBits32( source1,31,1 );
    BOOST_CHECK( value1a == 1 );
    auto value1b = ExtractBits32( source1, 31, 1 );
    BOOST_CHECK( value1b == 1 );

    constexpr UInt32 source2 = 0b00000000'00000000'00000000'00000101;
    constexpr auto value2a = ExtractBits32( source2, 0, 3 );
    BOOST_CHECK( value2a == 5 );
    auto value2b = ExtractBits32( source2, 0, 3 );
    BOOST_CHECK( value2b == 5 );
}

// --run_test=BitsConversionTests/BitsToByteTests1
BOOST_AUTO_TEST_CASE( BitsToByteTests1 )
{
    constexpr Byte byteSource1 = 0b10011001;
    constexpr SByte sbyteSource1 = std::bit_cast< SByte >(static_cast<Byte>(0b10011001));
    constexpr UInt16 uint16Source1 = 0b1001100110011001;
    constexpr Int16 int16Source1 = std::bit_cast<Int16>( static_cast< UInt16 >( 0b1001100110011001 ));
    constexpr UInt32 uint32Source1 = 0b10011001100110011001100110011001;
    constexpr Int32 int32Source1 = 0b10011001100110011001100110011001;
    constexpr UInt64 uint64Source1 = 0b10011001100110011001100110011001;
    constexpr Int64 int64Source1 = 0b10011001100110011001100110011001;

    {
        constexpr auto value1a = BitsToByte( byteSource1, 0, 0 );
        BOOST_CHECK( value1a == 0 );

        auto value1b = BitsToByte( byteSource1, 0, 0 );
        BOOST_CHECK( value1b == 0 );

        constexpr auto value2a = BitsToByte( byteSource1, 0, 1 );
        BOOST_CHECK( value2a == 1 );

        auto value2b = BitsToByte( byteSource1, 0, 1 );
        BOOST_CHECK( value2b == 1 );

        constexpr auto value3a = BitsToByte( byteSource1, 7, 1 );
        BOOST_CHECK( value3a == 1 );

        auto value3b = BitsToByte( byteSource1, 7, 1 );
        BOOST_CHECK( value3b == 1 );

        constexpr auto value4a = BitsToByte( byteSource1, 6, 1 );
        BOOST_CHECK( value4a == 0 );

        auto value4b = BitsToByte( byteSource1, 6, 1 );
        BOOST_CHECK( value4b == 0 );

        constexpr auto value5a = BitsToByte( byteSource1, 12, 1 );
        BOOST_CHECK( value5a == 0 );

        auto value5b = BitsToByte( byteSource1, 12, 1 );
        BOOST_CHECK( value5b == 0 );

        constexpr auto value6a = BitsToByte( byteSource1, 12, 64 );
        BOOST_CHECK( value6a == 0 );

        auto value6b = BitsToByte( byteSource1, 12, 64 );
        BOOST_CHECK( value6b == 0 );
    }
    {
        constexpr auto value1a = BitsToByte( sbyteSource1, 0, 0 );
        BOOST_CHECK( value1a == 0 );

        auto value1b = BitsToByte( sbyteSource1, 0, 0 );
        BOOST_CHECK( value1b == 0 );

        constexpr auto value2a = BitsToByte( sbyteSource1, 0, 1 );
        BOOST_CHECK( value2a == 1 );

        auto value2b = BitsToByte( sbyteSource1, 0, 1 );
        BOOST_CHECK( value2b == 1 );

        constexpr auto value3a = BitsToByte( sbyteSource1, 7, 1 );
        BOOST_CHECK( value3a == 1 );

        auto value3b = BitsToByte( sbyteSource1, 7, 1 );
        BOOST_CHECK( value3b == 1 );

        constexpr auto value4a = BitsToByte( sbyteSource1, 6, 1 );
        BOOST_CHECK( value4a == 0 );

        auto value4b = BitsToByte( sbyteSource1, 6, 1 );
        BOOST_CHECK( value4b == 0 );

        constexpr auto value5a = BitsToByte( sbyteSource1, 12, 1 );
        BOOST_CHECK( value5a == 0 );

        auto value5b = BitsToByte( sbyteSource1, 12, 1 );
        BOOST_CHECK( value5b == 0 );

        constexpr auto value6a = BitsToByte( sbyteSource1, 12, 64 );
        BOOST_CHECK( value6a == 0 );

        auto value6b = BitsToByte( sbyteSource1, 12, 64 );
        BOOST_CHECK( value6b == 0 );
    }
}

// --run_test=BitsConversionTests/BitsToSByteTests1
BOOST_AUTO_TEST_CASE( BitsToSByteTests1 )
{
    constexpr Byte byteSource1 = 0b10011001;
    //constexpr Byte value1a = BitsToByte( byteSource1, 1, 1 );
    constexpr SByte value1a = BitsToSByte( byteSource1, 0, 1 );
    BOOST_CHECK( value1a == 1 );
    constexpr SByte value1b = BitsToSByte( byteSource1, 3, 2 );
    BOOST_CHECK( value1b == -1 );
    constexpr SByte value1c = BitsToSByte( byteSource1, 0, 0 );
    BOOST_CHECK( value1c == 0 );

}




BOOST_AUTO_TEST_SUITE_END( )
