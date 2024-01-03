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

BOOST_FIXTURE_TEST_SUITE( VariantTests, LocalFixture )

// --run_test=VariantTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    Variant variant;
    BOOST_CHECK( variant.IsEmpty( ) );
}

// --run_test=VariantTests/BooleanConstructorTest1
BOOST_AUTO_TEST_CASE( BooleanConstructorTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type() == VariantType::Bool );
    BOOST_CHECK( variant.As<bool>( ) == variantValue );
}

// --run_test=VariantTests/SByteConstructorTest1
BOOST_AUTO_TEST_CASE( SByteConstructorTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    BOOST_CHECK( variant.As<SByte>( ) == variantValue );
}

// --run_test=VariantTests/ByteConstructorTest1
BOOST_AUTO_TEST_CASE( ByteConstructorTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    BOOST_CHECK( variant.As<Byte>( ) == variantValue );
}

// --run_test=VariantTests/Int16ConstructorTest1
BOOST_AUTO_TEST_CASE( Int16ConstructorTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    BOOST_CHECK( variant.As<Int16>( ) == variantValue );
}

// --run_test=VariantTests/UInt16ConstructorTest1
BOOST_AUTO_TEST_CASE( UInt16ConstructorTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    BOOST_CHECK( variant.As<UInt16>( ) == variantValue );
}

// --run_test=VariantTests/Int32ConstructorTest1
BOOST_AUTO_TEST_CASE( Int32ConstructorTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    BOOST_CHECK( variant.As<Int32>( ) == variantValue );
}

// --run_test=VariantTests/UInt32ConstructorTest1
BOOST_AUTO_TEST_CASE( UInt32ConstructorTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    BOOST_CHECK( variant.As<UInt32>( ) == variantValue );
}

// --run_test=VariantTests/Int64ConstructorTest1
BOOST_AUTO_TEST_CASE( Int64ConstructorTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    BOOST_CHECK( variant.As<Int64>( ) == variantValue );
}

// --run_test=VariantTests/UInt64ConstructorTest1
BOOST_AUTO_TEST_CASE( UInt64ConstructorTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    BOOST_CHECK( variant.As<UInt64>( ) == variantValue );
}


// --run_test=VariantTests/SingleConstructorTest1
BOOST_AUTO_TEST_CASE( SingleConstructorTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    BOOST_CHECK( variant.As<float>( ) == variantValue );
}

// --run_test=VariantTests/DoubleConstructorTest1
BOOST_AUTO_TEST_CASE( DoubleConstructorTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    BOOST_CHECK( variant.As<Double>( ) == variantValue );
}

// --run_test=VariantTests/DateTimeConstructorTest1
BOOST_AUTO_TEST_CASE( DateTimeConstructorTest1 )
{
    DateTime variantValue(2020,1,1);
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    BOOST_CHECK( variant.As<DateTime>( ) == variantValue );
}

// --run_test=VariantTests/CurrencyConstructorTest1
BOOST_AUTO_TEST_CASE( CurrencyConstructorTest1 )
{
    Currency variantValue(10000);
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Currency );
    BOOST_CHECK( variant.As<Currency>( ) == variantValue );
}

// --run_test=VariantTests/SysStringConstructorTest1
BOOST_AUTO_TEST_CASE( SysStringConstructorTest1 )
{
    SysString variantValue( L"Test" );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::BStr );
    BOOST_CHECK( variantValue == variant.As<SysString>( )  );
}

// --run_test=VariantTests/wstringConstructorTest1
BOOST_AUTO_TEST_CASE( wstringConstructorTest1 )
{
    WideString variantValue( L"Test" );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::BStr );
    BOOST_CHECK( variantValue == variant.As<WideString>( ) );
}

// --run_test=VariantTests/BooleanToSByteConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToSByteConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToByteConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToByteConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToInt16ConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToUInt16ConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToInt32ConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToUInt32ConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToInt64ConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToUInt64ConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToSingleConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToSingleConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToDoubleConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/BooleanToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToDateTimeConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime(1899,12,29) );
}

// --run_test=VariantTests/BooleanToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToCurrencyConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 1 ) );
}


// --run_test=VariantTests/BooleanToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( BooleanToSysStringConversionTest1 )
{
    constexpr bool variantValue = true;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Bool );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"-1" );
}

// --run_test=VariantTests/SByteToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( SByteToBooleanConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/SByteToByteConversionTest1
BOOST_AUTO_TEST_CASE( SByteToByteConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( SByteToInt16ConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( SByteToUInt16ConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( SByteToInt32ConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( SByteToUInt32ConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( SByteToInt64ConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( SByteToUInt64ConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToSingleConversionTest1
BOOST_AUTO_TEST_CASE( SByteToSingleConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( SByteToDoubleConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SByteToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( SByteToDateTimeConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime(1900,1,9) );
}

// --run_test=VariantTests/SByteToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( SByteToCurrencyConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/SByteToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( SByteToSysStringConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/SByteTowstringConversionTest1
BOOST_AUTO_TEST_CASE( SByteTowstringConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/SByteTostringConversionTest1
BOOST_AUTO_TEST_CASE( SByteTostringConversionTest1 )
{
    constexpr SByte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::SByte );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}

// --run_test=VariantTests/ByteToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( ByteToBooleanConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/ByteToSByteConversionTest1
BOOST_AUTO_TEST_CASE( ByteToSByteConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( ByteToInt16ConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( ByteToUInt16ConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( ByteToInt32ConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( ByteToUInt32ConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( ByteToInt64ConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( ByteToUInt64ConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToSingleConversionTest1
BOOST_AUTO_TEST_CASE( ByteToSingleConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( ByteToDoubleConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/ByteToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( ByteToDateTimeConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/ByteToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( ByteToCurrencyConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/ByteToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( ByteToSysStringConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/ByteTowstringConversionTest1
BOOST_AUTO_TEST_CASE( ByteTowstringConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/ByteTostringConversionTest1
BOOST_AUTO_TEST_CASE( ByteTostringConversionTest1 )
{
    constexpr Byte variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Byte );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}

// --run_test=VariantTests/Int16ToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToBooleanConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/Int16ToSByteConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToSByteConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}


// --run_test=VariantTests/Int16ToByteConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToByteConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}


// --run_test=VariantTests/Int16ToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToUInt16ConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int16ToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToInt32ConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int16ToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToUInt32ConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int16ToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToInt64ConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int16ToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToUInt64ConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int16ToSingleConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToSingleConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int16ToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToDoubleConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int16ToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToDateTimeConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/Int16ToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToCurrencyConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/Int16ToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( Int16ToSysStringConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/Int16TowstringConversionTest1
BOOST_AUTO_TEST_CASE( Int16TowstringConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/Int16TostringConversionTest1
BOOST_AUTO_TEST_CASE( Int16TostringConversionTest1 )
{
    constexpr Int16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int16 );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}


// --run_test=VariantTests/UInt16ToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToBooleanConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/UInt16ToSByteConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToSByteConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}


// --run_test=VariantTests/UInt16ToByteConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToByteConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt16ToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToInt16ConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}


// --run_test=VariantTests/UInt16ToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToInt32ConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt16ToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToUInt32ConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt16ToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToInt64ConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt16ToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToUInt64ConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt16ToSingleConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToSingleConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt16ToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToDoubleConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt16ToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToDateTimeConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/UInt16ToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToCurrencyConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/UInt16ToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( UInt16ToSysStringConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/UInt16TowstringConversionTest1
BOOST_AUTO_TEST_CASE( UInt16TowstringConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/UInt16TostringConversionTest1
BOOST_AUTO_TEST_CASE( UInt16TostringConversionTest1 )
{
    constexpr UInt16 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt16 );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}

// --run_test=VariantTests/Int32ToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToBooleanConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/Int32ToSByteConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToSByteConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}


// --run_test=VariantTests/Int32ToByteConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToByteConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int32ToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToInt16ConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int32ToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToUInt16ConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}


// --run_test=VariantTests/Int32ToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToUInt32ConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int32ToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToInt64ConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int32ToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToUInt64ConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int32ToSingleConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToSingleConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int32ToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToDoubleConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int32ToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToDateTimeConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/Int32ToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToCurrencyConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/Int32ToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( Int32ToSysStringConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/Int32TowstringConversionTest1
BOOST_AUTO_TEST_CASE( Int32TowstringConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/Int32TostringConversionTest1
BOOST_AUTO_TEST_CASE( Int32TostringConversionTest1 )
{
    constexpr Int32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}

// --run_test=VariantTests/UInt32ToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToBooleanConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/UInt32ToSByteConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToSByteConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}



// --run_test=VariantTests/UInt32ToByteConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToByteConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt32ToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToInt16ConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt32ToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToUInt16ConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt32ToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToInt32ConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt32ToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToInt64ConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt32ToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToUInt64ConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt32ToSingleConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToSingleConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt32ToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToDoubleConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt32ToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToDateTimeConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/UInt32ToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToCurrencyConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/UInt32ToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( UInt32ToSysStringConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/UInt32TowstringConversionTest1
BOOST_AUTO_TEST_CASE( UInt32TowstringConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/UInt32TostringConversionTest1
BOOST_AUTO_TEST_CASE( UInt32TostringConversionTest1 )
{
    constexpr UInt32 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt32 );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}

// --run_test=VariantTests/Int64ToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToBooleanConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/Int64ToSByteConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToSByteConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}



// --run_test=VariantTests/Int64ToByteConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToByteConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int64ToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToInt16ConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int64ToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToUInt16ConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int64ToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToInt32ConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int64ToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToUInt32ConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int64ToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToUInt64ConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int64ToSingleConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToSingleConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int64ToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToDoubleConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/Int64ToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToDateTimeConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/Int64ToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToCurrencyConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/Int64ToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( Int64ToSysStringConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/Int64TowstringConversionTest1
BOOST_AUTO_TEST_CASE( Int64TowstringConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/Int64TostringConversionTest1
BOOST_AUTO_TEST_CASE( Int64TostringConversionTest1 )
{
    constexpr Int64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int64 );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}

// --run_test=VariantTests/UInt64ToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToBooleanConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/UInt64ToSByteConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToSByteConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToByteConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToByteConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToInt16ConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToUInt16ConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToInt32ConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToUInt32ConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToInt64ConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToSingleConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToSingleConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToDoubleConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/UInt64ToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToDateTimeConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/UInt64ToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToCurrencyConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/UInt64ToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( UInt64ToSysStringConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/UInt64TowstringConversionTest1
BOOST_AUTO_TEST_CASE( UInt64TowstringConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/UInt64TostringConversionTest1
BOOST_AUTO_TEST_CASE( UInt64TostringConversionTest1 )
{
    constexpr UInt64 variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::UInt64 );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}


// --run_test=VariantTests/SingleToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( SingleToBooleanConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/SingleToSByteConversionTest1
BOOST_AUTO_TEST_CASE( SingleToSByteConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}



// --run_test=VariantTests/SingleToByteConversionTest1
BOOST_AUTO_TEST_CASE( SingleToByteConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SingleToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( SingleToInt16ConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SingleToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( SingleToUInt16ConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SingleToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( SingleToInt32ConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SingleToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( SingleToUInt32ConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SingleToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( SingleToInt64ConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SingleToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( SingleToUInt64ConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SingleToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( SingleToDoubleConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/SingleToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( SingleToDateTimeConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/SingleToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( SingleToCurrencyConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/SingleToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( SingleToSysStringConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/SingleTowstringConversionTest1
BOOST_AUTO_TEST_CASE( SingleTowstringConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/SingleTostringConversionTest1
BOOST_AUTO_TEST_CASE( SingleTostringConversionTest1 )
{
    constexpr float variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Single );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}

// --run_test=VariantTests/DoubleToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToBooleanConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/DoubleToSByteConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToSByteConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToByteConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToByteConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToInt16ConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToUInt16ConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToInt32ConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToUInt32ConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToInt64ConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToUInt64ConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToSingleConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToSingleConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DoubleToDateTimeConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToDateTimeConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<DateTime>( );
    BOOST_CHECK( converted == DateTime( 1900, 1, 9 ) );
}

// --run_test=VariantTests/DoubleToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToCurrencyConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/DoubleToSysStringConversionTest1
BOOST_AUTO_TEST_CASE( DoubleToSysStringConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<SysString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/DoubleTowstringConversionTest1
BOOST_AUTO_TEST_CASE( DoubleTowstringConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<WideString>( );
    BOOST_CHECK( converted == L"10" );
}

// --run_test=VariantTests/DoubleTostringConversionTest1
BOOST_AUTO_TEST_CASE( DoubleTostringConversionTest1 )
{
    constexpr Double variantValue = 10;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto converted = variant.As<AnsiString>( );
    BOOST_CHECK( converted == "10" );
}

// --run_test=VariantTests/DateTimeToBooleanConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToBooleanConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<bool>( );
    BOOST_CHECK( converted == true );
}

// --run_test=VariantTests/DateTimeToSByteConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToSByteConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<SByte>( );
    BOOST_CHECK( converted == 10 );
}


// --run_test=VariantTests/DateTimeToByteConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToByteConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<Byte>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DateTimeToInt16ConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToInt16ConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<Int16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DateTimeToUInt16ConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToUInt16ConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<UInt16>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DateTimeToInt32ConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToInt32ConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<Int32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DateTimeToUInt32ConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToUInt32ConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<UInt32>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DateTimeToInt64ConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToInt64ConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<Int64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DateTimeToUInt64ConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToUInt64ConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<UInt64>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DateTimeToSingleConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToSingleConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<float>( );
    BOOST_CHECK( converted == 10 );
}

// --run_test=VariantTests/DateTimeToDoubleConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToDoubleConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<Double>( );
    BOOST_CHECK( converted == 10 );
}


// --run_test=VariantTests/DateTimeToCurrencyConversionTest1
BOOST_AUTO_TEST_CASE( DateTimeToCurrencyConversionTest1 )
{
    DateTime variantValue( 1900, 1, 9 );
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::DateTime );
    auto converted = variant.As<Currency>( );
    BOOST_CHECK( converted == Currency( 10 ) );
}

// --run_test=VariantTests/AbsTest1
BOOST_AUTO_TEST_CASE( AbsTest1 )
{
    constexpr double variantValue = -1;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto result = variant.Abs();
    BOOST_CHECK( result.Type( ) == VariantType::Double );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/AddTest1
BOOST_AUTO_TEST_CASE( AddTest1 )
{
    constexpr double variantValue1 = 1;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 1;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1.Add( variant2 );
    BOOST_CHECK( result.Type( ) == VariantType::Double );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 2 );
}

// --run_test=VariantTests/AddTest2
BOOST_AUTO_TEST_CASE( AddTest2 )
{
    constexpr double variantValue1 = 1;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 1;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1 + variant2;
    BOOST_CHECK( result.Type( ) == VariantType::Double );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 2 );
}

// --run_test=VariantTests/AndTest1
BOOST_AUTO_TEST_CASE( AndTest1 )
{
    constexpr UInt32 variantValue1 = 1;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::UInt32 );

    constexpr UInt32 variantValue2 = 3;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::UInt32 );

    auto result = variant1.And( variant2 );
    BOOST_CHECK( result.Type( ) == VariantType::Int32 );
    auto converted = result.As<Int32>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/AndTest2
BOOST_AUTO_TEST_CASE( AndTest2 )
{
    constexpr UInt32 variantValue1 = 1;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::UInt32 );

    constexpr UInt32 variantValue2 = 3;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::UInt32 );

    auto result = variant1 & variant2;
    BOOST_CHECK( result.Type( ) == VariantType::Int32 );
    auto converted = result.As<Int32>( );
    BOOST_CHECK( converted == 1 );
}


// --run_test=VariantTests/ConcatenateTest1
BOOST_AUTO_TEST_CASE( ConcatenateTest1 )
{
    constexpr UInt32 variantValue1 = 1;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::UInt32 );

    constexpr UInt32 variantValue2 = 3;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::UInt32 );

    auto result = variant1.Concatenate( variant2 );
    BOOST_CHECK( result.Type( ) == VariantType::BStr );
    auto converted = result.As<SysString>( );
    BOOST_CHECK( converted == L"13" );
}

// --run_test=VariantTests/DivTest1
BOOST_AUTO_TEST_CASE( DivTest1 )
{
    constexpr double variantValue1 = 6;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1.Div( variant2 );
    BOOST_CHECK( result.Type( ) == VariantType::Double );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 3 );
}


// --run_test=VariantTests/DivTest2
BOOST_AUTO_TEST_CASE( DivTest2 )
{
    constexpr double variantValue1 = 6;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1 / variant2;
    BOOST_CHECK( result.Type( ) == VariantType::Double );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 3 );
}

// --run_test=VariantTests/IDivTest1
BOOST_AUTO_TEST_CASE( IDivTest1 )
{
    constexpr double variantValue1 = 7;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1.IDiv( variant2 );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 3 );
}


// --run_test=VariantTests/TruncTest1
BOOST_AUTO_TEST_CASE( TruncTest1 )
{
    constexpr double variantValue = 1.74;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto result = variant.Trunc( );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/ModTest1
BOOST_AUTO_TEST_CASE( ModTest1 )
{
    constexpr double variantValue1 = 7;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1.Mod( variant2 );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/ModTest2
BOOST_AUTO_TEST_CASE( ModTest2 )
{
    constexpr double variantValue1 = 7;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1 % variant2;
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 1 );
}

// --run_test=VariantTests/MulTest1
BOOST_AUTO_TEST_CASE( MulTest1 )
{
    constexpr double variantValue1 = 7;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1.Mul( variant2 );
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 14 );
}

// --run_test=VariantTests/MulTest2
BOOST_AUTO_TEST_CASE( MulTest2 )
{
    constexpr double variantValue1 = 7;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    auto result = variant1 * variant2;
    auto converted = result.As<Double>( );
    BOOST_CHECK( converted == 14 );
}

// --run_test=VariantTests/NegTest1
BOOST_AUTO_TEST_CASE( NegTest1 )
{
    constexpr Int32 variantValue = -5;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto result = variant.Neg( );
    auto converted = result.As<Int32>( );
    BOOST_CHECK( converted == 5 );
}


// --run_test=VariantTests/NotTest1
BOOST_AUTO_TEST_CASE( NotTest1 )
{
    constexpr Int32 variantValue = 5;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );
    auto result = variant.Not( );
    auto converted = result.As<Int32>( );
    BOOST_CHECK( converted == 0xFFFFFFFA );
}

// --run_test=VariantTests/NotTest2
BOOST_AUTO_TEST_CASE( NotTest2 )
{
    constexpr Int32 variantValue = 5;
    constexpr Int32 expectedVariantValue = ~variantValue;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Int32 );

    auto result = ~variant;
    auto converted = result.As<Int32>( );
    BOOST_CHECK( converted == expectedVariantValue );
}


// --run_test=VariantTests/OrTest1
BOOST_AUTO_TEST_CASE( OrTest1 )
{
    constexpr UInt32 variantValue1 = 1;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::UInt32 );

    constexpr UInt32 variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::UInt32 );

    constexpr UInt32 expectedValue = variantValue1 | variantValue2;

    auto result = variant1.Or( variant2 );
    auto converted = result.As<UInt32>( );
    BOOST_CHECK( converted == expectedValue );
}

// --run_test=VariantTests/OrTest2
BOOST_AUTO_TEST_CASE( OrTest2 )
{
    constexpr UInt32 variantValue1 = 1;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::UInt32 );

    constexpr UInt32 variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::UInt32 );

    constexpr UInt32 expectedValue = variantValue1 | variantValue2;

    auto result = variant1 | variant2;
    auto converted = result.As<UInt32>( );
    BOOST_CHECK( converted == expectedValue );
}

// --run_test=VariantTests/SubTest1
BOOST_AUTO_TEST_CASE( SubTest1 )
{
    constexpr double variantValue1 = 2;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 1;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    constexpr double expectedValue = variantValue1 - variantValue2;

    auto result = variant1.Sub( variant2 );
    auto converted = result.As<double>( );
    BOOST_CHECK( converted == expectedValue );
}

// --run_test=VariantTests/SubTest2
BOOST_AUTO_TEST_CASE( SubTest2 )
{
    constexpr double variantValue1 = 2;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 1;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    constexpr double expectedValue = variantValue1 - variantValue2;

    auto result = variant1 - variant2;
    auto converted = result.As<double>( );
    BOOST_CHECK( converted == expectedValue );
}

// --run_test=VariantTests/PowTest1
BOOST_AUTO_TEST_CASE( PowTest1 )
{
    constexpr double variantValue1 = 2;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Double );

    constexpr double variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Double );

    double expectedValue = std::pow( variantValue1 , variantValue2 );

    auto result = variant1.Pow( variant2 );
    auto converted = result.As<double>( );
    BOOST_CHECK( converted == expectedValue );
}

// --run_test=VariantTests/EqvTest1
BOOST_AUTO_TEST_CASE( EqvTest1 )
{
    constexpr Int32 variantValue1 = 2;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Int32 );

    constexpr Int32 variantValue2 = 2;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Int32 );

    bool expectedValue = true;

    auto result = variant1.Eqv( variant2 );
    auto converted = result.As<bool>( );
    BOOST_CHECK( converted == expectedValue );
}

// --run_test=VariantTests/EqvTest2
BOOST_AUTO_TEST_CASE( EqvTest2 )
{
    constexpr Int32 variantValue1 = 2;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Int32 );

    constexpr Int32 variantValue2 = ~variantValue1;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Int32 );

    bool expectedValue = false;

    auto result = variant1.Eqv( variant2 );
    auto converted = result.As<bool>( );
    BOOST_CHECK( converted == expectedValue );
}


// --run_test=VariantTests/FixTest1
BOOST_AUTO_TEST_CASE( FixTest1 )
{
    constexpr double variantValue = -5.5;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto result = variant.Fix( );
    auto converted = result.As<double>( );
    BOOST_CHECK( converted == -5 );
}

// --run_test=VariantTests/FixTest2
BOOST_AUTO_TEST_CASE( FixTest2 )
{
    constexpr double variantValue = 5.5;
    Variant variant( variantValue );
    BOOST_CHECK( variant.Type( ) == VariantType::Double );
    auto result = variant.Fix( );
    auto converted = result.As<double>( );
    BOOST_CHECK( converted == 5 );
}

// --run_test=VariantTests/ImpTest1
BOOST_AUTO_TEST_CASE( ImpTest1 )
{
    constexpr Int32 variantValue1 = 2;
    Variant variant1( variantValue1 );
    BOOST_CHECK( variant1.Type( ) == VariantType::Int32 );

    constexpr Int32 variantValue2 = 1;
    Variant variant2( variantValue2 );
    BOOST_CHECK( variant2.Type( ) == VariantType::Int32 );

    Int32 expectedValue = 0xFFFFFFFD;

    auto result = variant1.Imp( variant2 );
    auto converted = result.As<Int32>( );
    BOOST_CHECK( converted == expectedValue );
}




BOOST_AUTO_TEST_SUITE_END( )
