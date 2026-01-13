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
#include "HCCBitConverter.h"

using namespace Harlinn::Common;
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

BOOST_FIXTURE_TEST_SUITE( BitConverterTests, LocalFixture )

// --run_test=BitConverterTests/BooleanTests1
BOOST_AUTO_TEST_CASE( BooleanTests1 )
{
    auto trueBytes1 = BitConverter::GetBytes( true );
    constexpr auto trueBytes2 = BitConverter::GetArray( true );
    auto equal1 = std::ranges::equal( trueBytes1, trueBytes2 );
    BOOST_CHECK( equal1 );

    auto falseBytes1 = BitConverter::GetBytes( false );
    constexpr auto falseBytes2 = BitConverter::GetArray( false );
    auto equal2 = std::ranges::equal( falseBytes1, falseBytes2 );
    BOOST_CHECK( equal2 );

    auto trueValue1 = BitConverter::ToBoolean( trueBytes1 );
    auto trueValue2 = BitConverter::ToBoolean( trueBytes2 );

    BOOST_CHECK( trueValue1 );
    BOOST_CHECK( trueValue2 );

    auto falseValue1 = BitConverter::ToBoolean( falseBytes1 );
    auto falseValue2 = BitConverter::ToBoolean( falseBytes2 );

    BOOST_CHECK( falseValue1 == false );
    BOOST_CHECK( falseValue2 == false );
}

// --run_test=BitConverterTests/SByteTests1
BOOST_AUTO_TEST_CASE( SByteTests1 )
{
    constexpr SByte value1 = -128;
    constexpr SByte value2 = 1;
    constexpr SByte value3 = 127;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToSByte( value1Bytes1 );
    auto value1Value2 = BitConverter::ToSByte( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToSByte( value2Bytes1 );
    auto value2Value2 = BitConverter::ToSByte( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToSByte( value3Bytes1 );
    auto value3Value2 = BitConverter::ToSByte( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/ByteTests1
BOOST_AUTO_TEST_CASE( ByteTests1 )
{
    constexpr Byte value1 = 0;
    constexpr Byte value2 = 1;
    constexpr Byte value3 = 255;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToByte( value1Bytes1 );
    auto value1Value2 = BitConverter::ToByte( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToByte( value2Bytes1 );
    auto value2Value2 = BitConverter::ToByte( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToByte( value3Bytes1 );
    auto value3Value2 = BitConverter::ToByte( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/CharTests1
BOOST_AUTO_TEST_CASE( CharTests1 )
{
    constexpr char value1 = -128;
    constexpr char value2 = 1;
    constexpr char value3 = 127;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToChar( value1Bytes1 );
    auto value1Value2 = BitConverter::ToChar( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToChar( value2Bytes1 );
    auto value2Value2 = BitConverter::ToChar( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToChar( value3Bytes1 );
    auto value3Value2 = BitConverter::ToChar( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/WideCharTests1
BOOST_AUTO_TEST_CASE( WideCharTests1 )
{
    constexpr wchar_t value1 = 0;
    constexpr wchar_t value2 = 1;
    constexpr wchar_t value3 = 0xFFFEU;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToWideChar( value1Bytes1 );
    auto value1Value2 = BitConverter::ToWideChar( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToWideChar( value2Bytes1 );
    auto value2Value2 = BitConverter::ToWideChar( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToWideChar( value3Bytes1 );
    auto value3Value2 = BitConverter::ToWideChar( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}


// --run_test=BitConverterTests/Int16Tests1
BOOST_AUTO_TEST_CASE( Int16Tests1 )
{
    using ValueType = Int16;
    constexpr ValueType value1 = std::numeric_limits<ValueType>::lowest( ) + 1;
    constexpr ValueType value2 = 1;
    constexpr ValueType value3 = std::numeric_limits<ValueType>::max( ) - 1;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToInt16( value1Bytes1 );
    auto value1Value2 = BitConverter::ToInt16( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToInt16( value2Bytes1 );
    auto value2Value2 = BitConverter::ToInt16( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToInt16( value3Bytes1 );
    auto value3Value2 = BitConverter::ToInt16( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}


// --run_test=BitConverterTests/UInt16Tests1
BOOST_AUTO_TEST_CASE( UInt16Tests1 )
{
    using ValueType = UInt16;
    constexpr ValueType value1 = std::numeric_limits<ValueType>::lowest( ) + 1;
    constexpr ValueType value2 = 0x1FF;
    constexpr ValueType value3 = std::numeric_limits<ValueType>::max( ) - 1;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToUInt16( value1Bytes1 );
    auto value1Value2 = BitConverter::ToUInt16( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToUInt16( value2Bytes1 );
    auto value2Value2 = BitConverter::ToUInt16( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToUInt16( value3Bytes1 );
    auto value3Value2 = BitConverter::ToUInt16( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/Int32Tests1
BOOST_AUTO_TEST_CASE( Int32Tests1 )
{
    using ValueType = Int32;
    constexpr ValueType value1 = std::numeric_limits<ValueType>::lowest( ) + 1;
    constexpr ValueType value2 = 1;
    constexpr ValueType value3 = std::numeric_limits<ValueType>::max( ) - 1;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToInt32( value1Bytes1 );
    auto value1Value2 = BitConverter::ToInt32( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToInt32( value2Bytes1 );
    auto value2Value2 = BitConverter::ToInt32( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToInt32( value3Bytes1 );
    auto value3Value2 = BitConverter::ToInt32( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}


// --run_test=BitConverterTests/UInt32Tests1
BOOST_AUTO_TEST_CASE( UInt32Tests1 )
{
    using ValueType = UInt32;
    constexpr ValueType value1 = std::numeric_limits<ValueType>::lowest( ) + 1;
    constexpr ValueType value2 = 0x1FFFF;
    constexpr ValueType value3 = std::numeric_limits<ValueType>::max( ) - 1;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToUInt32( value1Bytes1 );
    auto value1Value2 = BitConverter::ToUInt32( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToUInt32( value2Bytes1 );
    auto value2Value2 = BitConverter::ToUInt32( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToUInt32( value3Bytes1 );
    auto value3Value2 = BitConverter::ToUInt32( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}


// --run_test=BitConverterTests/Int64Tests1
BOOST_AUTO_TEST_CASE( Int64Tests1 )
{
    using ValueType = Int64;
    constexpr ValueType value1 = std::numeric_limits<ValueType>::lowest( ) + 1;
    constexpr ValueType value2 = 1;
    constexpr ValueType value3 = std::numeric_limits<ValueType>::max( ) - 1;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToInt64( value1Bytes1 );
    auto value1Value2 = BitConverter::ToInt64( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToInt64( value2Bytes1 );
    auto value2Value2 = BitConverter::ToInt64( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToInt64( value3Bytes1 );
    auto value3Value2 = BitConverter::ToInt64( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}


// --run_test=BitConverterTests/UInt64Tests1
BOOST_AUTO_TEST_CASE( UInt64Tests1 )
{
    using ValueType = UInt64;
    constexpr ValueType value1 = std::numeric_limits<ValueType>::lowest( ) + 1;
    constexpr ValueType value2 = 0x1FFFF;
    constexpr ValueType value3 = std::numeric_limits<ValueType>::max( ) - 1;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToUInt64( value1Bytes1 );
    auto value1Value2 = BitConverter::ToUInt64( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToUInt64( value2Bytes1 );
    auto value2Value2 = BitConverter::ToUInt64( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToUInt64( value3Bytes1 );
    auto value3Value2 = BitConverter::ToUInt64( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/SingleTests1
BOOST_AUTO_TEST_CASE( SingleTests1 )
{
    using ValueType = float;
    constexpr ValueType value1 = std::numeric_limits<ValueType>::lowest( ) + 1;
    constexpr ValueType value2 = 1;
    constexpr ValueType value3 = std::numeric_limits<ValueType>::max( ) - 1;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToSingle( value1Bytes1 );
    auto value1Value2 = BitConverter::ToSingle( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToSingle( value2Bytes1 );
    auto value2Value2 = BitConverter::ToSingle( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToSingle( value3Bytes1 );
    auto value3Value2 = BitConverter::ToSingle( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/DoubleTests1
BOOST_AUTO_TEST_CASE( DoubleTests1 )
{
    using ValueType = double;
    constexpr ValueType value1 = std::numeric_limits<ValueType>::lowest( ) + 1;
    constexpr ValueType value2 = 1;
    constexpr ValueType value3 = std::numeric_limits<ValueType>::max( ) - 1;

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToDouble( value1Bytes1 );
    auto value1Value2 = BitConverter::ToDouble( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToDouble( value2Bytes1 );
    auto value2Value2 = BitConverter::ToDouble( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToDouble( value3Bytes1 );
    auto value3Value2 = BitConverter::ToDouble( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/DateTimeTests1
BOOST_AUTO_TEST_CASE( DateTimeTests1 )
{
    using ValueType = DateTime;
    constexpr ValueType value1 = ValueType( DateTime::MinValue( ) );
    constexpr ValueType value2 = ValueType( DateTime::UnixEpoch );
    constexpr ValueType value3 = ValueType( DateTime::MaxValue( ) );

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToDateTime( value1Bytes1 );
    auto value1Value2 = BitConverter::ToDateTime( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToDateTime( value2Bytes1 );
    auto value2Value2 = BitConverter::ToDateTime( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToDateTime( value3Bytes1 );
    auto value3Value2 = BitConverter::ToDateTime( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/TimeSpanTests1
BOOST_AUTO_TEST_CASE( TimeSpanTests1 )
{
    using ValueType = TimeSpan;
    constexpr ValueType value1 = ValueType( TimeSpan::MinValue( ) );
    constexpr ValueType value2 = ValueType( TimeSpan::TicksPerDay );
    constexpr ValueType value3 = ValueType( TimeSpan::MaxValue( ) );

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToTimeSpan( value1Bytes1 );
    auto value1Value2 = BitConverter::ToTimeSpan( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToTimeSpan( value2Bytes1 );
    auto value2Value2 = BitConverter::ToTimeSpan( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToTimeSpan( value3Bytes1 );
    auto value3Value2 = BitConverter::ToTimeSpan( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/CurrencyTests1
BOOST_AUTO_TEST_CASE( CurrencyTests1 )
{
    using ValueType = Currency;
    constexpr ValueType value1 = ValueType( -1.74 );
    constexpr ValueType value2 = ValueType( 0.1 );
    constexpr ValueType value3 = ValueType( 1.74 );

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    constexpr auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToCurrency( value1Bytes1 );
    auto value1Value2 = BitConverter::ToCurrency( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    constexpr auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToCurrency( value2Bytes1 );
    auto value2Value2 = BitConverter::ToCurrency( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    constexpr auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToCurrency( value3Bytes1 );
    auto value3Value2 = BitConverter::ToCurrency( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}

// --run_test=BitConverterTests/GuidTests1
BOOST_AUTO_TEST_CASE( GuidTests1 )
{
    using ValueType = Guid;
    ValueType value1 = ValueType::New( );
    ValueType value2 = ValueType::New( );
    ValueType value3 = ValueType::New( );

    auto value1Bytes1 = BitConverter::GetBytes( value1 );
    auto value1Bytes2 = BitConverter::GetArray( value1 );
    auto equal1 = std::ranges::equal( value1Bytes1, value1Bytes2 );
    BOOST_CHECK( equal1 );

    auto value1Value1 = BitConverter::ToGuid( value1Bytes1 );
    auto value1Value2 = BitConverter::ToGuid( value1Bytes2 );

    BOOST_CHECK( value1Value1 == value1 );
    BOOST_CHECK( value1Value2 == value1 );

    auto value2Bytes1 = BitConverter::GetBytes( value2 );
    auto value2Bytes2 = BitConverter::GetArray( value2 );
    auto equal2 = std::ranges::equal( value2Bytes1, value2Bytes2 );
    BOOST_CHECK( equal2 );

    auto value2Value1 = BitConverter::ToGuid( value2Bytes1 );
    auto value2Value2 = BitConverter::ToGuid( value2Bytes2 );

    BOOST_CHECK( value2Value1 == value2 );
    BOOST_CHECK( value2Value2 == value2 );


    auto value3Bytes1 = BitConverter::GetBytes( value3 );
    auto value3Bytes2 = BitConverter::GetArray( value3 );
    auto equal3 = std::ranges::equal( value3Bytes1, value3Bytes2 );
    BOOST_CHECK( equal3 );

    auto value3Value1 = BitConverter::ToGuid( value3Bytes1 );
    auto value3Value2 = BitConverter::ToGuid( value3Bytes2 );

    BOOST_CHECK( value3Value1 == value3 );
    BOOST_CHECK( value3Value2 == value3 );
}








BOOST_AUTO_TEST_SUITE_END( )
