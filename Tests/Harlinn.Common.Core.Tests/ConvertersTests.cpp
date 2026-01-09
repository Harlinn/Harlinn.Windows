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

using namespace Harlinn::Common;
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

BOOST_FIXTURE_TEST_SUITE( ConvertersTests, LocalFixture )

// --run_test=ConvertersTests/SByteMinMaxTest1
BOOST_AUTO_TEST_CASE( SByteMinMaxTest1 )
{
    using Type = SByte;
    constexpr Type minValue = std::numeric_limits<Type>::lowest( );
    constexpr Type maxValue = std::numeric_limits<Type>::max( );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Byte>( minValue ); }, ArgumentOutOfRangeException
    );
    BOOST_CHECK_THROW(
        { 
            auto result = ConvertTo<UInt16>( minValue ); 
        }, ArgumentOutOfRangeException
    );

    auto byteValue = ConvertTo<Byte>( maxValue );
    BOOST_CHECK( byteValue == static_cast<Byte>( maxValue ) );

    auto uint16Value = ConvertTo<UInt16>( maxValue );
    BOOST_CHECK( uint16Value == static_cast<UInt16>( maxValue ) );

    auto int16Value = ConvertTo<Int16>( maxValue );
    BOOST_CHECK( int16Value == static_cast<Int16>( maxValue ) );


    auto boolValue = ConvertTo<bool>( minValue );
    BOOST_CHECK( boolValue == true );
    boolValue = ConvertTo<bool>( maxValue );
    BOOST_CHECK( boolValue == true );
}

// --run_test=ConvertersTests/ByteMinMaxTest1
BOOST_AUTO_TEST_CASE( ByteMinMaxTest1 )
{
    using Type = Byte;
    constexpr Type minValue = std::numeric_limits<Type>::lowest( );
    constexpr Type maxValue = std::numeric_limits<Type>::max( );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<SByte>( maxValue ); }, ArgumentOutOfRangeException
    );

    auto byteValue = ConvertTo<SByte>( minValue );
    BOOST_CHECK( byteValue == static_cast<SByte>( minValue ) );

    auto boolValue = ConvertTo<bool>( minValue );
    BOOST_CHECK( boolValue == false );
    boolValue = ConvertTo<bool>( maxValue );
    BOOST_CHECK( boolValue == true );
}


// --run_test=ConvertersTests/Int16MinMaxTest1
BOOST_AUTO_TEST_CASE( Int16MinMaxTest1 )
{
    using Type = Int16;
    constexpr Type minValue = std::numeric_limits<Type>::lowest( );
    constexpr Type maxValue = std::numeric_limits<Type>::max( );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<SByte>( minValue ); }, ArgumentOutOfRangeException
    );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<SByte>( maxValue ); }, ArgumentOutOfRangeException
    );

    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Byte>( minValue ); }, ArgumentOutOfRangeException
    );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Byte>( maxValue ); }, ArgumentOutOfRangeException
    );


    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt16>( minValue ); }, ArgumentOutOfRangeException
    );

    auto uint16Value = ConvertTo<UInt16>( maxValue );
    BOOST_CHECK( uint16Value == static_cast<UInt16>( maxValue ) );

    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt32>( minValue ); }, ArgumentOutOfRangeException
    );

    auto uint32Value = ConvertTo<UInt32>( maxValue );
    BOOST_CHECK( uint32Value == static_cast<UInt32>( maxValue ) );

    auto int32Value = ConvertTo<Int32>( minValue );
    BOOST_CHECK( int32Value == static_cast<Int32>( minValue ) );

    int32Value = ConvertTo<Int32>( maxValue );
    BOOST_CHECK( int32Value == static_cast<Int32>( maxValue ) );


    auto boolValue = ConvertTo<bool>( minValue );
    BOOST_CHECK( boolValue == true );
    boolValue = ConvertTo<bool>( maxValue );
    BOOST_CHECK( boolValue == true );
}


// --run_test=ConvertersTests/UInt16MinMaxTest1
BOOST_AUTO_TEST_CASE( UInt16MinMaxTest1 )
{
    using Type = UInt16;
    constexpr Type minValue = std::numeric_limits<Type>::lowest( );
    constexpr Type maxValue = std::numeric_limits<Type>::max( );

    auto sbyteValue = ConvertTo<SByte>( minValue );
    BOOST_CHECK( sbyteValue == static_cast<SByte>( minValue ) );

    
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<SByte>( maxValue ); }, ArgumentOutOfRangeException
    );

    auto byteValue = ConvertTo<Byte>( minValue );
    BOOST_CHECK( byteValue == static_cast<Byte>( minValue ) );

    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Byte>( maxValue ); }, ArgumentOutOfRangeException
    );


    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int16>( maxValue ); }, ArgumentOutOfRangeException
    );

    auto uint32Value = ConvertTo<UInt32>( minValue );
    BOOST_CHECK( uint32Value == static_cast<UInt32>( minValue ) );

    uint32Value = ConvertTo<UInt32>( maxValue );
    BOOST_CHECK( uint32Value == static_cast<UInt32>( maxValue ) );

    auto int32Value = ConvertTo<Int32>( minValue );
    BOOST_CHECK( int32Value == static_cast<Int32>( minValue ) );

    int32Value = ConvertTo<Int32>( maxValue );
    BOOST_CHECK( int32Value == static_cast<Int32>( maxValue ) );


    auto boolValue = ConvertTo<bool>( minValue );
    BOOST_CHECK( boolValue == false );
    boolValue = ConvertTo<bool>( maxValue );
    BOOST_CHECK( boolValue == true );
}


// --run_test=ConvertersTests/Int32MinMaxTest1
BOOST_AUTO_TEST_CASE( Int32MinMaxTest1 )
{
    using Type = Int32;
    constexpr Type minValue = std::numeric_limits<Type>::lowest( );
    constexpr Type maxValue = std::numeric_limits<Type>::max( );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int16>( minValue ); }, ArgumentOutOfRangeException
    );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int16>( maxValue ); }, ArgumentOutOfRangeException
    );

    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt16>( minValue ); }, ArgumentOutOfRangeException
    );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt16>( maxValue ); }, ArgumentOutOfRangeException
    );


    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt32>( minValue ); }, ArgumentOutOfRangeException
    );

    auto uint32Value = ConvertTo<UInt32>( maxValue );
    BOOST_CHECK( uint32Value == static_cast<UInt32>( maxValue ) );

    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt64>( minValue ); }, ArgumentOutOfRangeException
    );

    auto uint64Value = ConvertTo<UInt64>( maxValue );
    BOOST_CHECK( uint64Value == static_cast<UInt64>( maxValue ) );

    auto int64Value = ConvertTo<Int64>( minValue );
    BOOST_CHECK( int64Value == static_cast<Int64>( minValue ) );

    int64Value = ConvertTo<Int64>( maxValue );
    BOOST_CHECK( int64Value == static_cast<Int64>( maxValue ) );


    auto boolValue = ConvertTo<bool>( minValue );
    BOOST_CHECK( boolValue == true );
    boolValue = ConvertTo<bool>( maxValue );
    BOOST_CHECK( boolValue == true );
}


// --run_test=ConvertersTests/UInt32MinMaxTest1
BOOST_AUTO_TEST_CASE( UInt32MinMaxTest1 )
{
    using Type = UInt32;
    constexpr Type minValue = std::numeric_limits<Type>::lowest( );
    constexpr Type maxValue = std::numeric_limits<Type>::max( );

    auto int16Value = ConvertTo<Int16>( minValue );
    BOOST_CHECK( int16Value == static_cast<Int16>( minValue ) );


    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int16>( maxValue ); }, ArgumentOutOfRangeException
    );

    auto uint16Value = ConvertTo<UInt16>( minValue );
    BOOST_CHECK( uint16Value == static_cast<UInt16>( minValue ) );

    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt16>( maxValue ); }, ArgumentOutOfRangeException
    );


    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int32>( maxValue ); }, ArgumentOutOfRangeException
    );

    auto uint64Value = ConvertTo<UInt64>( minValue );
    BOOST_CHECK( uint64Value == static_cast<UInt64>( minValue ) );

    uint64Value = ConvertTo<UInt64>( maxValue );
    BOOST_CHECK( uint64Value == static_cast<UInt64>( maxValue ) );

    auto int64Value = ConvertTo<Int64>( minValue );
    BOOST_CHECK( int64Value == static_cast<Int64>( minValue ) );

    int64Value = ConvertTo<Int64>( maxValue );
    BOOST_CHECK( int64Value == static_cast<Int64>( maxValue ) );


    auto boolValue = ConvertTo<bool>( minValue );
    BOOST_CHECK( boolValue == false );
    boolValue = ConvertTo<bool>( maxValue );
    BOOST_CHECK( boolValue == true );
}


// --run_test=ConvertersTests/Int64MinMaxTest1
BOOST_AUTO_TEST_CASE( Int64MinMaxTest1 )
{
    using Type = Int64;
    constexpr Type minValue = std::numeric_limits<Type>::lowest( );
    constexpr Type maxValue = std::numeric_limits<Type>::max( );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int32>( minValue ); }, ArgumentOutOfRangeException
    );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int32>( maxValue ); }, ArgumentOutOfRangeException
    );

    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt32>( minValue ); }, ArgumentOutOfRangeException
    );
    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt32>( maxValue ); }, ArgumentOutOfRangeException
    );


    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt64>( minValue ); }, ArgumentOutOfRangeException
    );

    auto uint64Value = ConvertTo<UInt64>( maxValue );
    BOOST_CHECK( uint64Value == static_cast<UInt64>( maxValue ) );


    auto boolValue = ConvertTo<bool>( minValue );
    BOOST_CHECK( boolValue == true );
    boolValue = ConvertTo<bool>( maxValue );
    BOOST_CHECK( boolValue == true );
}


// --run_test=ConvertersTests/UInt64MinMaxTest1
BOOST_AUTO_TEST_CASE( UInt64MinMaxTest1 )
{
    using Type = UInt64;
    constexpr Type minValue = std::numeric_limits<Type>::lowest( );
    constexpr Type maxValue = std::numeric_limits<Type>::max( );

    auto int32Value = ConvertTo<Int32>( minValue );
    BOOST_CHECK( int32Value == static_cast<Int32>( minValue ) );


    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int32>( maxValue ); }, ArgumentOutOfRangeException
    );

    auto uint32Value = ConvertTo<UInt32>( minValue );
    BOOST_CHECK( uint32Value == static_cast<UInt32>( minValue ) );

    BOOST_CHECK_THROW(
        { auto result = ConvertTo<UInt32>( maxValue ); }, ArgumentOutOfRangeException
    );


    BOOST_CHECK_THROW(
        { auto result = ConvertTo<Int64>( maxValue ); }, ArgumentOutOfRangeException
    );


    auto boolValue = ConvertTo<bool>( minValue );
    BOOST_CHECK( boolValue == false );
    boolValue = ConvertTo<bool>( maxValue );
    BOOST_CHECK( boolValue == true );
}




// --run_test=ConvertersTests/SameTest1
BOOST_AUTO_TEST_CASE( SameTest1 )
{
    using Type = bool;
    Type value = true;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest2
BOOST_AUTO_TEST_CASE( SameTest2 )
{
    using Type = SByte;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest3
BOOST_AUTO_TEST_CASE( SameTest3 )
{
    using Type = Byte;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest4
BOOST_AUTO_TEST_CASE( SameTest4 )
{
    using Type = Int16;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest5
BOOST_AUTO_TEST_CASE( SameTest5 )
{
    using Type = UInt16;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest6
BOOST_AUTO_TEST_CASE( SameTest6 )
{
    using Type = Int32;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest7
BOOST_AUTO_TEST_CASE( SameTest7 )
{
    using Type = UInt32;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest8
BOOST_AUTO_TEST_CASE( SameTest8 )
{
    using Type = Int64;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest9
BOOST_AUTO_TEST_CASE( SameTest9 )
{
    using Type = UInt64;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest10
BOOST_AUTO_TEST_CASE( SameTest10 )
{
    using Type = float;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest11
BOOST_AUTO_TEST_CASE( SameTest11 )
{
    using Type = double;
    Type value = 1;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest12
BOOST_AUTO_TEST_CASE( SameTest12 )
{
    using Type = DateTime;
    Type value(1LL);
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest13
BOOST_AUTO_TEST_CASE( SameTest13 )
{
    using Type = TimeSpan;
    Type value( 1LL );
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest14
BOOST_AUTO_TEST_CASE( SameTest14 )
{
    using Type = AnsiString;
    Type value( "Hi" );
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest15
BOOST_AUTO_TEST_CASE( SameTest15 )
{
    using Type = WideString;
    Type value( L"Hi" );
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest16
BOOST_AUTO_TEST_CASE( SameTest16 )
{
    using Type = Guid;
    Type value( L"{260E6DDD-7AFF-471C-A530-3E60766364E0}" );
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest17
BOOST_AUTO_TEST_CASE( SameTest17 )
{
    using Type = Currency;
    Type value = 1000;
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}

// --run_test=ConvertersTests/SameTest18
BOOST_AUTO_TEST_CASE( SameTest18 )
{
    using Type = Variant;
    Type value(1);
    auto result = ConvertTo<Type>( value );
    BOOST_CHECK( value == result );
}


// --run_test=ConvertersTests/ToWideStringTest1
BOOST_AUTO_TEST_CASE( ToWideStringTest1 )
{
    using Type = bool;
    Type value = true;
    WideString expectedResult{ L"True" };
    auto result = ConvertTo<WideString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToWideStringTest2
BOOST_AUTO_TEST_CASE( ToWideStringTest2 )
{
    using Type = SByte;
    Type value = 1;
    WideString expectedResult{ L"1" };
    auto result = ConvertTo<WideString>( value );
	bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest3
BOOST_AUTO_TEST_CASE( ToWideStringTest3 )
{
    using Type = Byte;
    Type value = 1;
    WideString expectedResult{ L"1" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest4
BOOST_AUTO_TEST_CASE( ToWideStringTest4 )
{
    using Type = Int16;
    Type value = 1;
    WideString expectedResult{ L"1" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest5
BOOST_AUTO_TEST_CASE( ToWideStringTest5 )
{
    using Type = UInt16;
    Type value = 1;
    WideString expectedResult{ L"1" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest6
BOOST_AUTO_TEST_CASE( ToWideStringTest6 )
{
    using Type = Int32;
    Type value = 1;
    WideString expectedResult{ L"1" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest7
BOOST_AUTO_TEST_CASE( ToWideStringTest7 )
{
    using Type = UInt32;
    Type value = 1;
    WideString expectedResult{ L"1" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest8
BOOST_AUTO_TEST_CASE( ToWideStringTest8 )
{
    using Type = Int64;
    Type value = 1;
    WideString expectedResult{ L"1" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest9
BOOST_AUTO_TEST_CASE( ToWideStringTest9 )
{
    using Type = UInt64;
    Type value = 1;
    WideString expectedResult{ L"1" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest10
BOOST_AUTO_TEST_CASE( ToWideStringTest10 )
{
    using Type = float;
    Type value = 1;
    WideString expectedResult{ L"1.000000" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest11
BOOST_AUTO_TEST_CASE( ToWideStringTest11 )
{
    using Type = Double;
    Type value = 1;
    WideString expectedResult{ L"1.000000" };
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest12
BOOST_AUTO_TEST_CASE( ToWideStringTest12 )
{
    using Type = DateTime;
    Type value(2020,1,1);
    WideString expectedResult = value.ToString();
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest13
BOOST_AUTO_TEST_CASE( ToWideStringTest13 )
{
    using Type = TimeSpan;
    Type value = Type::FromDays(1);
    WideString expectedResult = value.ToString( );
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}


// --run_test=ConvertersTests/ToWideStringTest14
BOOST_AUTO_TEST_CASE( ToWideStringTest14 )
{
    using Type = Guid;
    Type value("{39978367-04DD-415F-8633-F079EA432700}");
    WideString expectedResult = value.ToWideString( );
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest15
BOOST_AUTO_TEST_CASE( ToWideStringTest15 )
{
    using Type = Currency;
    Type value( 10000 );
    WideString expectedResult = value.ToWideString( );
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest16
BOOST_AUTO_TEST_CASE( ToWideStringTest16 )
{
    using Type = Variant;
    Type value( 1 );
    WideString expectedResult = value.AsWideString();
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest17
BOOST_AUTO_TEST_CASE( ToWideStringTest17 )
{
    using Type = WideString;
    Type value( L"Hi" );
    auto result = ConvertTo<WideString>( value );
    bool asExpected = value == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToWideStringTest18
BOOST_AUTO_TEST_CASE( ToWideStringTest18 )
{
    using Type = AnsiString;
    Type value( "Hi" );
    WideString expectedResult = ToWideString( value );
    auto result = ConvertTo<WideString>( value );
    bool asExpected = expectedResult == result;
    BOOST_CHECK( asExpected );
}

// --run_test=ConvertersTests/ToAnsiStringTest1
BOOST_AUTO_TEST_CASE( ToAnsiStringTest1 )
{
    using Type = bool;
    Type value = true;
    AnsiString expectedResult{ "True" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest2
BOOST_AUTO_TEST_CASE( ToAnsiStringTest2 )
{
    using Type = SByte;
    Type value = 1;
    AnsiString expectedResult{ "1" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest3
BOOST_AUTO_TEST_CASE( ToAnsiStringTest3 )
{
    using Type = Byte;
    Type value = 1;
    AnsiString expectedResult{ "1" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest4
BOOST_AUTO_TEST_CASE( ToAnsiStringTest4 )
{
    using Type = Int16;
    Type value = 1;
    AnsiString expectedResult{ "1" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest5
BOOST_AUTO_TEST_CASE( ToAnsiStringTest5 )
{
    using Type = UInt16;
    Type value = 1;
    AnsiString expectedResult{ "1" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest6
BOOST_AUTO_TEST_CASE( ToAnsiStringTest6 )
{
    using Type = Int32;
    Type value = 1;
    AnsiString expectedResult{ "1" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest7
BOOST_AUTO_TEST_CASE( ToAnsiStringTest7 )
{
    using Type = UInt32;
    Type value = 1;
    AnsiString expectedResult{ "1" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest8
BOOST_AUTO_TEST_CASE( ToAnsiStringTest8 )
{
    using Type = Int64;
    Type value = 1;
    AnsiString expectedResult{ "1" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest9
BOOST_AUTO_TEST_CASE( ToAnsiStringTest9 )
{
    using Type = UInt64;
    Type value = 1;
    AnsiString expectedResult{ "1" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest10
BOOST_AUTO_TEST_CASE( ToAnsiStringTest10 )
{
    using Type = float;
    Type value = 1;
    AnsiString expectedResult{ "1.000000" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest11
BOOST_AUTO_TEST_CASE( ToAnsiStringTest11 )
{
    using Type = Double;
    Type value = 1;
    AnsiString expectedResult{ "1.000000" };
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest12
BOOST_AUTO_TEST_CASE( ToAnsiStringTest12 )
{
    using Type = DateTime;
    Type value( 2020, 1, 1 );
    AnsiString expectedResult = value.ToAnsiString( );
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest13
BOOST_AUTO_TEST_CASE( ToAnsiStringTest13 )
{
    using Type = TimeSpan;
    Type value = Type::FromDays( 1 );
    AnsiString expectedResult = value.ToAnsiString( );
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}


// --run_test=ConvertersTests/ToAnsiStringTest14
BOOST_AUTO_TEST_CASE( ToAnsiStringTest14 )
{
    using Type = Guid;
    Type value( "{39978367-04DD-415F-8633-F079EA432700}" );
    AnsiString expectedResult = value.ToAnsiString( );
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest15
BOOST_AUTO_TEST_CASE( ToAnsiStringTest15 )
{
    using Type = Currency;
    Type value( 10000 );
    AnsiString expectedResult = value.ToAnsiString( );
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest16
BOOST_AUTO_TEST_CASE( ToAnsiStringTest16 )
{
    using Type = Variant;
    Type value( 1 );
    AnsiString expectedResult = value.As<AnsiString>( );
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest17
BOOST_AUTO_TEST_CASE( ToAnsiStringTest17 )
{
    using Type = WideString;
    Type value( L"Hi" );
    AnsiString expectedResult = ToAnsiString( value );
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToAnsiStringTest18
BOOST_AUTO_TEST_CASE( ToAnsiStringTest18 )
{
    using Type = AnsiString;
    Type value( "Hi" );
    AnsiString expectedResult = value;
    auto result = ConvertTo<AnsiString>( value );
    BOOST_CHECK( expectedResult == result );
}


// --run_test=ConvertersTests/ToBooleanTest1
BOOST_AUTO_TEST_CASE( ToBooleanTest1 )
{
    using Type = bool;
    Type value = true;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest2
BOOST_AUTO_TEST_CASE( ToBooleanTest2 )
{
    using Type = SByte;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest3
BOOST_AUTO_TEST_CASE( ToBooleanTest3 )
{
    using Type = Byte;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest4
BOOST_AUTO_TEST_CASE( ToBooleanTest4 )
{
    using Type = Int16;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest5
BOOST_AUTO_TEST_CASE( ToBooleanTest5 )
{
    using Type = UInt16;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest6
BOOST_AUTO_TEST_CASE( ToBooleanTest6 )
{
    using Type = Int32;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest7
BOOST_AUTO_TEST_CASE( ToBooleanTest7 )
{
    using Type = UInt32;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest8
BOOST_AUTO_TEST_CASE( ToBooleanTest8 )
{
    using Type = Int64;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest9
BOOST_AUTO_TEST_CASE( ToBooleanTest9 )
{
    using Type = UInt64;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest10
BOOST_AUTO_TEST_CASE( ToBooleanTest10 )
{
    using Type = float;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest11
BOOST_AUTO_TEST_CASE( ToBooleanTest11 )
{
    using Type = Double;
    Type value = 1;
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest12
BOOST_AUTO_TEST_CASE( ToBooleanTest12 )
{
    using Type = DateTime;
    Type value( 2020, 1, 1 );
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest13
BOOST_AUTO_TEST_CASE( ToBooleanTest13 )
{
    using Type = TimeSpan;
    Type value = Type::FromDays( 1 );
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}


// --run_test=ConvertersTests/ToBooleanTest14
BOOST_AUTO_TEST_CASE( ToBooleanTest14 )
{
    using Type = Guid;
    Type value( "{39978367-04DD-415F-8633-F079EA432700}" );
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest15
BOOST_AUTO_TEST_CASE( ToBooleanTest15 )
{
    using Type = Currency;
    Type value( 10000 );
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest16
BOOST_AUTO_TEST_CASE( ToBooleanTest16 )
{
    using Type = Variant;
    Type value( 1 );
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest17
BOOST_AUTO_TEST_CASE( ToBooleanTest17 )
{
    using Type = WideString;
    Type value( L"Hi" );
    bool expectedResult = false;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest17a
BOOST_AUTO_TEST_CASE( ToBooleanTest17a )
{
    using Type = WideString;
    Type value( L"true" );
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest17b
BOOST_AUTO_TEST_CASE( ToBooleanTest17b )
{
    using Type = WideString;
    Type value( L"yes" );
    bool expectedResult = false;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest17c
BOOST_AUTO_TEST_CASE( ToBooleanTest17c )
{
    using Type = WideString;
    Type value( L"1" );
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToBooleanTest17d
BOOST_AUTO_TEST_CASE( ToBooleanTest17d )
{
    using Type = WideString;
    Type value( L"10" );
    bool expectedResult = true;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}





// --run_test=ConvertersTests/ToBooleanTest18
BOOST_AUTO_TEST_CASE( ToBooleanTest18 )
{
    using Type = AnsiString;
    Type value( "Hi" );
    bool expectedResult = false;
    auto result = ConvertTo<bool>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest1
BOOST_AUTO_TEST_CASE( ToSByteTest1 )
{
    using Type = bool;
    Type value = true;
    SByte expectedResult = 1;
    
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest2
BOOST_AUTO_TEST_CASE( ToSByteTest2 )
{
    using Type = SByte;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest3
BOOST_AUTO_TEST_CASE( ToSByteTest3 )
{
    using Type = Byte;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest4
BOOST_AUTO_TEST_CASE( ToSByteTest4 )
{
    using Type = Int16;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest5
BOOST_AUTO_TEST_CASE( ToSByteTest5 )
{
    using Type = UInt16;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest6
BOOST_AUTO_TEST_CASE( ToSByteTest6 )
{
    using Type = Int32;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest7
BOOST_AUTO_TEST_CASE( ToSByteTest7 )
{
    using Type = UInt32;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest8
BOOST_AUTO_TEST_CASE( ToSByteTest8 )
{
    using Type = Int64;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest9
BOOST_AUTO_TEST_CASE( ToSByteTest9 )
{
    using Type = UInt64;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest10
BOOST_AUTO_TEST_CASE( ToSByteTest10 )
{
    using Type = float;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest11
BOOST_AUTO_TEST_CASE( ToSByteTest11 )
{
    using Type = Double;
    Type value = 1;
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest12
BOOST_AUTO_TEST_CASE( ToSByteTest12 )
{
    using Type = DateTime;
    Type value( 2020, 1, 1 );
    SByte expectedResult = 1;
    BOOST_CHECK_THROW( { auto result = ConvertTo<SByte>( value ); }, ArgumentOutOfRangeException );
}

// --run_test=ConvertersTests/ToSByteTest13
BOOST_AUTO_TEST_CASE( ToSByteTest13 )
{
    using Type = TimeSpan;
    Type value = Type::FromDays( 1 );
    SByte expectedResult = 1;
    BOOST_CHECK_THROW( { auto result = ConvertTo<SByte>( value ); }, ArgumentOutOfRangeException );
}

// --run_test=ConvertersTests/ToSByteTest13a
BOOST_AUTO_TEST_CASE( ToSByteTest13a )
{
    using Type = TimeSpan;
    Type value( std::numeric_limits<SByte>::max( ) );
    constexpr SByte expectedResult = std::numeric_limits<SByte>::max();
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}


// --run_test=ConvertersTests/ToSByteTest15
BOOST_AUTO_TEST_CASE( ToSByteTest15 )
{
    using Type = Currency;
    Type value( 1 );
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest16
BOOST_AUTO_TEST_CASE( ToSByteTest16 )
{
    using Type = Variant;
    Type value( 1 );
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest17
BOOST_AUTO_TEST_CASE( ToSByteTest17 )
{
    using Type = WideString;
    Type value( L"1" );
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}

// --run_test=ConvertersTests/ToSByteTest18
BOOST_AUTO_TEST_CASE( ToSByteTest18 )
{
    using Type = AnsiString;
    Type value( "1" );
    SByte expectedResult = 1;
    auto result = ConvertTo<SByte>( value );
    BOOST_CHECK( expectedResult == result );
}


BOOST_AUTO_TEST_SUITE_END( )