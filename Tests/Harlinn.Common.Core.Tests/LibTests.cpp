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

BOOST_FIXTURE_TEST_SUITE( LibTests, LocalFixture )


// --run_test=LibTests/CharStrCompareTest
BOOST_AUTO_TEST_CASE( CharStrCompareTest )
{
    constexpr auto result1 = Compare( "A", "B" );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( nullptr, "B" );
    BOOST_CHECK( result2 < 0 );

    constexpr auto result3 = Compare( "B", nullptr );
    BOOST_CHECK( result3 > 0 );

    constexpr auto result4 = Compare( nullptr, nullptr );
    BOOST_CHECK( result4 == 0 );

    int result5 = Compare( "B", "A" );
    BOOST_CHECK( result5 > 0 );

    constexpr auto result6 = Compare( "AA", "B" );
    BOOST_CHECK( result6 < 0 );

    constexpr auto result7 = Compare( "AA", "A" );
    BOOST_CHECK( result7 > 0 );

    constexpr auto result8 = Compare( "", nullptr );
    BOOST_CHECK( result8 == 0 );

    constexpr auto result9 = Compare( nullptr, "" );
    BOOST_CHECK( result9 == 0 );
}

// --run_test=LibTests/WideCharStrCompareTest
BOOST_AUTO_TEST_CASE( WideCharStrCompareTest )
{
    constexpr auto result1 = Compare( L"A", L"B" );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( nullptr, L"B" );
    BOOST_CHECK( result2 < 0 );

    constexpr auto result3 = Compare( L"B", nullptr );
    BOOST_CHECK( result3 > 0 );

    constexpr auto result4 = Compare( nullptr, nullptr );
    BOOST_CHECK( result4 == 0 );

    int result5 = Compare( L"B", L"A" );
    BOOST_CHECK( result5 > 0 );

    constexpr auto result6 = Compare( L"AA", L"B" );
    BOOST_CHECK( result6 < 0 );

    constexpr auto result7 = Compare( L"AA", L"A" );
    BOOST_CHECK( result7 > 0 );

    constexpr auto result8 = Compare( L"", nullptr );
    BOOST_CHECK( result8 == 0 );

    constexpr auto result9 = Compare( nullptr, L"" );
    BOOST_CHECK( result9 == 0 );
}

// --run_test=LibTests/BooleanCompareTest
BOOST_AUTO_TEST_CASE( BooleanCompareTest )
{
    constexpr auto result1 = Compare( false, true );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( false, false );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( true, true );
    BOOST_CHECK( result3 == 0 );

    constexpr auto result4 = Compare( true, false );
    BOOST_CHECK( result4 > 0 );
}

// --run_test=LibTests/SByteCompareTest
BOOST_AUTO_TEST_CASE( SByteCompareTest )
{
    constexpr auto result1 = Compare( static_cast<SByte>( 1 ), static_cast<SByte>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<SByte>( 1 ), static_cast<SByte>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<SByte>( 2 ), static_cast<SByte>( 1 ) );
    BOOST_CHECK( result3 > 0 );

    constexpr auto result4 = Compare( static_cast<SByte>( -2 ), static_cast<SByte>( -1 ) );
    BOOST_CHECK( result4 < 0 );

    constexpr auto result5 = Compare( static_cast<SByte>( -1 ), static_cast<SByte>( -1 ) );
    BOOST_CHECK( result5 == 0 );

    constexpr auto result6 = Compare( static_cast<SByte>( -1 ), static_cast<SByte>( -2 ) );
    BOOST_CHECK( result6 > 0 );
}

// --run_test=LibTests/ByteCompareTest
BOOST_AUTO_TEST_CASE( ByteCompareTest )
{
    constexpr auto result1 = Compare( static_cast<Byte>( 1 ), static_cast<Byte>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<Byte>( 1 ), static_cast<Byte>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<Byte>( 2 ), static_cast<Byte>( 1 ) );
    BOOST_CHECK( result3 > 0 );
}

// --run_test=LibTests/Int16CompareTest
BOOST_AUTO_TEST_CASE( Int16CompareTest )
{
    constexpr auto result1 = Compare( static_cast<Int16>( 1 ), static_cast<Int16>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<Int16>( 1 ), static_cast<Int16>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<Int16>( 2 ), static_cast<Int16>( 1 ) );
    BOOST_CHECK( result3 > 0 );

    constexpr auto result4 = Compare( static_cast<Int16>( -2 ), static_cast<Int16>( -1 ) );
    BOOST_CHECK( result4 < 0 );

    constexpr auto result5 = Compare( static_cast<Int16>( -1 ), static_cast<Int16>( -1 ) );
    BOOST_CHECK( result5 == 0 );

    constexpr auto result6 = Compare( static_cast<Int16>( -1 ), static_cast<Int16>( -2 ) );
    BOOST_CHECK( result6 > 0 );
}

// --run_test=LibTests/UInt16CompareTest
BOOST_AUTO_TEST_CASE( UInt16CompareTest )
{
    constexpr auto result1 = Compare( static_cast<UInt16>( 1 ), static_cast<UInt16>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<UInt16>( 1 ), static_cast<UInt16>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<UInt16>( 2 ), static_cast<UInt16>( 1 ) );
    BOOST_CHECK( result3 > 0 );
}

// --run_test=LibTests/Int32CompareTest
BOOST_AUTO_TEST_CASE( Int32CompareTest )
{
    constexpr auto result1 = Compare( static_cast<Int32>( 1 ), static_cast<Int32>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<Int32>( 1 ), static_cast<Int32>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<Int32>( 2 ), static_cast<Int32>( 1 ) );
    BOOST_CHECK( result3 > 0 );

    constexpr auto result4 = Compare( static_cast<Int32>( -2 ), static_cast<Int32>( -1 ) );
    BOOST_CHECK( result4 < 0 );

    constexpr auto result5 = Compare( static_cast<Int32>( -1 ), static_cast<Int32>( -1 ) );
    BOOST_CHECK( result5 == 0 );

    constexpr auto result6 = Compare( static_cast<Int32>( -1 ), static_cast<Int32>( -2 ) );
    BOOST_CHECK( result6 > 0 );
}

// --run_test=LibTests/UInt32CompareTest
BOOST_AUTO_TEST_CASE( UInt32CompareTest )
{
    constexpr auto result1 = Compare( static_cast<UInt32>( 1 ), static_cast<UInt32>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<UInt32>( 1 ), static_cast<UInt32>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<UInt32>( 2 ), static_cast<UInt32>( 1 ) );
    BOOST_CHECK( result3 > 0 );
}

// --run_test=LibTests/Int64CompareTest
BOOST_AUTO_TEST_CASE( Int64CompareTest )
{
    constexpr auto result1 = Compare( static_cast<Int64>( 1 ), static_cast<Int64>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<Int64>( 1 ), static_cast<Int64>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<Int64>( 2 ), static_cast<Int64>( 1 ) );
    BOOST_CHECK( result3 > 0 );

    constexpr auto result4 = Compare( static_cast<Int64>( -2 ), static_cast<Int64>( -1 ) );
    BOOST_CHECK( result4 < 0 );

    constexpr auto result5 = Compare( static_cast<Int64>( -1 ), static_cast<Int64>( -1 ) );
    BOOST_CHECK( result5 == 0 );

    constexpr auto result6 = Compare( static_cast<Int64>( -1 ), static_cast<Int64>( -2 ) );
    BOOST_CHECK( result6 > 0 );
}

// --run_test=LibTests/UInt64CompareTest
BOOST_AUTO_TEST_CASE( UInt64CompareTest )
{
    constexpr auto result1 = Compare( static_cast<UInt64>( 1 ), static_cast<UInt64>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<UInt64>( 1 ), static_cast<UInt64>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<UInt64>( 2 ), static_cast<UInt64>( 1 ) );
    BOOST_CHECK( result3 > 0 );
}

// --run_test=LibTests/SingleCompareTest
BOOST_AUTO_TEST_CASE( SingleCompareTest )
{
    constexpr auto result1 = Compare( static_cast<float>( 1 ), static_cast<float>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<float>( 1 ), static_cast<float>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<float>( 2 ), static_cast<float>( 1 ) );
    BOOST_CHECK( result3 > 0 );

    constexpr auto result4 = Compare( static_cast<float>( -2 ), static_cast<float>( -1 ) );
    BOOST_CHECK( result4 < 0 );

    constexpr auto result5 = Compare( static_cast<float>( -1 ), static_cast<float>( -1 ) );
    BOOST_CHECK( result5 == 0 );

    constexpr auto result6 = Compare( static_cast<float>( -1 ), static_cast<float>( -2 ) );
    BOOST_CHECK( result6 > 0 );
}

// --run_test=LibTests/DoubleCompareTest
BOOST_AUTO_TEST_CASE( DoubleCompareTest )
{
    constexpr auto result1 = Compare( static_cast<Double>( 1 ), static_cast<Double>( 2 ) );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( static_cast<Double>( 1 ), static_cast<Double>( 1 ) );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( static_cast<Double>( 2 ), static_cast<Double>( 1 ) );
    BOOST_CHECK( result3 > 0 );

    constexpr auto result4 = Compare( static_cast<Double>( -2 ), static_cast<Double>( -1 ) );
    BOOST_CHECK( result4 < 0 );

    constexpr auto result5 = Compare( static_cast<Double>( -1 ), static_cast<Double>( -1 ) );
    BOOST_CHECK( result5 == 0 );

    constexpr auto result6 = Compare( static_cast<Double>( -1 ), static_cast<Double>( -2 ) );
    BOOST_CHECK( result6 > 0 );
}

// --run_test=LibTests/GuidCompareTest
BOOST_AUTO_TEST_CASE( GuidCompareTest )
{
    // {555193B3-EF83-4FAB-A951-8E495D2DE506}
    constexpr Guid guid1( 0x555193b3, 0xef83, 0x4fab, 0xa9, 0x51, 0x8e, 0x49, 0x5d, 0x2d, 0xe5, 0x6 );
    // {CF68FF1D-6AD2-4C0E-828E-BAFC15E685AE}
    constexpr Guid guid2(0xcf68ff1d, 0x6ad2, 0x4c0e, 0x82, 0x8e, 0xba, 0xfc, 0x15, 0xe6, 0x85, 0xae );

    Guid guid3 = guid1;
    Guid guid4 = guid2;
    

    constexpr auto result1 = Compare( guid1, guid2 );
    BOOST_CHECK( result1 > 0 );

    constexpr auto result2 = Compare( guid1, guid1 );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( guid2, guid1 );
    BOOST_CHECK( result3 < 0 );

    auto result4 = Compare( guid3, guid4 );
    BOOST_CHECK( result1 > 0 );

    auto result5 = Compare( guid3, guid3 );
    BOOST_CHECK( result2 == 0 );

    auto result6 = Compare( guid4, guid2 );
    BOOST_CHECK( result3 < 0 );

}

// --run_test=LibTests/DateTimeCompareTest
BOOST_AUTO_TEST_CASE( DateTimeCompareTest )
{
    constexpr DateTime dateTime1( 1LL );
    constexpr DateTime dateTime2( 2LL );

    constexpr auto result1 = Compare( dateTime1, dateTime2 );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( dateTime1, dateTime1 );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( dateTime2, dateTime1 );
    BOOST_CHECK( result3 > 0 );
}

// --run_test=LibTests/TimeSpanCompareTest
BOOST_AUTO_TEST_CASE( TimeSpanCompareTest )
{
    constexpr TimeSpan timeSpan1( 1LL );
    constexpr TimeSpan timeSpan2( 2LL );

    constexpr auto result1 = Compare( timeSpan1, timeSpan2 );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( timeSpan1, timeSpan1 );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( timeSpan2, timeSpan1 );
    BOOST_CHECK( result3 > 0 );
}

// --run_test=LibTests/CurrencyCompareTest
BOOST_AUTO_TEST_CASE( CurrencyCompareTest )
{
    constexpr Currency currency1( 1LL );
    constexpr Currency currency2( 2LL );

    constexpr auto result1 = Compare( currency1, currency2 );
    BOOST_CHECK( result1 < 0 );

    constexpr auto result2 = Compare( currency1, currency1 );
    BOOST_CHECK( result2 == 0 );

    constexpr auto result3 = Compare( currency2, currency1 );
    BOOST_CHECK( result3 > 0 );
}

// --run_test=LibTests/SByteByteSwapTest
BOOST_AUTO_TEST_CASE( SByteByteSwapTest )
{
    using ValueType = SByte;
    constexpr ValueType valueMin = std::numeric_limits<ValueType>::min( );
    constexpr ValueType valueM1 = static_cast<ValueType>( -1 );
    constexpr ValueType value0 = static_cast<ValueType>( 0 );
    constexpr ValueType valueP1 = static_cast<ValueType>( 1 );
    constexpr ValueType valueMax = std::numeric_limits<ValueType>::max( );

    constexpr ValueType valueMinResult = ByteSwap( valueMin );
    constexpr ValueType valueM1Result = ByteSwap( valueM1 );
    constexpr ValueType value0Result = ByteSwap( value0 );
    constexpr ValueType valueP1Result = ByteSwap( valueP1 );
    constexpr ValueType valueMaxResult = ByteSwap( valueMax );

    BOOST_CHECK( valueMinResult == valueMin );
    BOOST_CHECK( valueM1Result == valueM1 );
    BOOST_CHECK( value0Result == value0 );
    BOOST_CHECK( valueP1Result == valueP1 );
    BOOST_CHECK( valueMaxResult == valueMax );
}

// --run_test=LibTests/ByteByteSwapTest
BOOST_AUTO_TEST_CASE( ByteByteSwapTest )
{
    using ValueType = Byte;
    constexpr ValueType valueMin = std::numeric_limits<ValueType>::min( );
    constexpr ValueType valueM1 = static_cast<ValueType>( -1 );
    constexpr ValueType value0 = static_cast<ValueType>( 0 );
    constexpr ValueType valueP1 = static_cast<ValueType>( 1 );
    constexpr ValueType valueMax = std::numeric_limits<ValueType>::max( );

    constexpr ValueType valueMinResult = ByteSwap( valueMin );
    constexpr ValueType valueM1Result = ByteSwap( valueM1 );
    constexpr ValueType value0Result = ByteSwap( value0 );
    constexpr ValueType valueP1Result = ByteSwap( valueP1 );
    constexpr ValueType valueMaxResult = ByteSwap( valueMax );

    BOOST_CHECK( valueMinResult == valueMin );
    BOOST_CHECK( valueM1Result == valueM1 );
    BOOST_CHECK( value0Result == value0 );
    BOOST_CHECK( valueP1Result == valueP1 );
    BOOST_CHECK( valueMaxResult == valueMax );
}


// --run_test=LibTests/Int16ByteSwapTest
BOOST_AUTO_TEST_CASE( Int16ByteSwapTest )
{
    using ValueType = Int16;
    constexpr ValueType valueMin = std::numeric_limits<ValueType>::min( );
    constexpr ValueType valueM1 = static_cast<ValueType>( -1 );
    constexpr ValueType value0 = static_cast<ValueType>( 0 );
    constexpr ValueType valueP1 = static_cast<ValueType>( 1 );
    constexpr ValueType valueMax = std::numeric_limits<ValueType>::max( );

    constexpr ValueType valueMinResult1 = ByteSwap( valueMin );
    constexpr ValueType valueM1Result1 = ByteSwap( valueM1 );
    constexpr ValueType value0Result1 = ByteSwap( value0 );
    constexpr ValueType valueP1Result1 = ByteSwap( valueP1 );
    constexpr ValueType valueMaxResult1 = ByteSwap( valueMax );

    ValueType valueMinResult1r = _byteswap_ushort( valueMin );
    ValueType valueM1Result1r = _byteswap_ushort( valueM1 );
    ValueType value0Result1r = _byteswap_ushort( value0 );
    ValueType valueP1Result1r = _byteswap_ushort( valueP1 );
    ValueType valueMaxResult1r = _byteswap_ushort( valueMax );

    constexpr ValueType valueMinResult2 = ByteSwap( valueMinResult1 );
    constexpr ValueType valueM1Result2 = ByteSwap( valueM1Result1 );
    constexpr ValueType value0Result2 = ByteSwap( value0Result1 );
    constexpr ValueType valueP1Result2 = ByteSwap( valueP1Result1 );
    constexpr ValueType valueMaxResult2 = ByteSwap( valueMaxResult1 );

    BOOST_CHECK( valueMinResult2 == valueMin );
    BOOST_CHECK( valueM1Result2 == valueM1 );
    BOOST_CHECK( value0Result2 == value0 );
    BOOST_CHECK( valueP1Result2 == valueP1 );
    BOOST_CHECK( valueMaxResult2 == valueMax );

    BOOST_CHECK( valueMinResult1 == valueMinResult1r );
    BOOST_CHECK( valueM1Result1 == valueM1Result1r );
    BOOST_CHECK( value0Result1 == value0Result1r );
    BOOST_CHECK( valueP1Result1 == valueP1Result1r );
    BOOST_CHECK( valueMaxResult1 == valueMaxResult1r );
}

// --run_test=LibTests/UInt16ByteSwapTest
BOOST_AUTO_TEST_CASE( UInt16ByteSwapTest )
{
    using ValueType = UInt16;
    constexpr ValueType valueMin = std::numeric_limits<ValueType>::min( );
    constexpr ValueType valueM1 = static_cast<ValueType>( -1 );
    constexpr ValueType value0 = static_cast<ValueType>( 0 );
    constexpr ValueType valueP1 = static_cast<ValueType>( 1 );
    constexpr ValueType valueMax = std::numeric_limits<ValueType>::max( );

    constexpr ValueType valueMinResult1 = ByteSwap( valueMin );
    constexpr ValueType valueM1Result1 = ByteSwap( valueM1 );
    constexpr ValueType value0Result1 = ByteSwap( value0 );
    constexpr ValueType valueP1Result1 = ByteSwap( valueP1 );
    constexpr ValueType valueMaxResult1 = ByteSwap( valueMax );

    ValueType valueMinResult1r = _byteswap_ushort( valueMin );
    ValueType valueM1Result1r = _byteswap_ushort( valueM1 );
    ValueType value0Result1r = _byteswap_ushort( value0 );
    ValueType valueP1Result1r = _byteswap_ushort( valueP1 );
    ValueType valueMaxResult1r = _byteswap_ushort( valueMax );

    constexpr ValueType valueMinResult2 = ByteSwap( valueMinResult1 );
    constexpr ValueType valueM1Result2 = ByteSwap( valueM1Result1 );
    constexpr ValueType value0Result2 = ByteSwap( value0Result1 );
    constexpr ValueType valueP1Result2 = ByteSwap( valueP1Result1 );
    constexpr ValueType valueMaxResult2 = ByteSwap( valueMaxResult1 );

    BOOST_CHECK( valueMinResult2 == valueMin );
    BOOST_CHECK( valueM1Result2 == valueM1 );
    BOOST_CHECK( value0Result2 == value0 );
    BOOST_CHECK( valueP1Result2 == valueP1 );
    BOOST_CHECK( valueMaxResult2 == valueMax );

    BOOST_CHECK( valueMinResult1 == valueMinResult1r );
    BOOST_CHECK( valueM1Result1 == valueM1Result1r );
    BOOST_CHECK( value0Result1 == value0Result1r );
    BOOST_CHECK( valueP1Result1 == valueP1Result1r );
    BOOST_CHECK( valueMaxResult1 == valueMaxResult1r );
}

// --run_test=LibTests/Int32ByteSwapTest
BOOST_AUTO_TEST_CASE( Int32ByteSwapTest )
{
    using ValueType = Int32;
    constexpr ValueType valueMin = std::numeric_limits<ValueType>::min( );
    constexpr ValueType valueM1 = static_cast<ValueType>( -1 );
    constexpr ValueType value0 = static_cast<ValueType>( 0 );
    constexpr ValueType valueP1 = static_cast<ValueType>( 1 );
    constexpr ValueType valueMax = std::numeric_limits<ValueType>::max( );

    constexpr ValueType valueMinResult1 = ByteSwap( valueMin );
    constexpr ValueType valueM1Result1 = ByteSwap( valueM1 );
    constexpr ValueType value0Result1 = ByteSwap( value0 );
    constexpr ValueType valueP1Result1 = ByteSwap( valueP1 );
    constexpr ValueType valueMaxResult1 = ByteSwap( valueMax );

    ValueType valueMinResult1r = _byteswap_ulong( valueMin );
    ValueType valueM1Result1r = _byteswap_ulong( valueM1 );
    ValueType value0Result1r = _byteswap_ulong( value0 );
    ValueType valueP1Result1r = _byteswap_ulong( valueP1 );
    ValueType valueMaxResult1r = _byteswap_ulong( valueMax );

    constexpr ValueType valueMinResult2 = ByteSwap( valueMinResult1 );
    constexpr ValueType valueM1Result2 = ByteSwap( valueM1Result1 );
    constexpr ValueType value0Result2 = ByteSwap( value0Result1 );
    constexpr ValueType valueP1Result2 = ByteSwap( valueP1Result1 );
    constexpr ValueType valueMaxResult2 = ByteSwap( valueMaxResult1 );

    BOOST_CHECK( valueMinResult2 == valueMin );
    BOOST_CHECK( valueM1Result2 == valueM1 );
    BOOST_CHECK( value0Result2 == value0 );
    BOOST_CHECK( valueP1Result2 == valueP1 );
    BOOST_CHECK( valueMaxResult2 == valueMax );

    BOOST_CHECK( valueMinResult1 == valueMinResult1r );
    BOOST_CHECK( valueM1Result1 == valueM1Result1r );
    BOOST_CHECK( value0Result1 == value0Result1r );
    BOOST_CHECK( valueP1Result1 == valueP1Result1r );
    BOOST_CHECK( valueMaxResult1 == valueMaxResult1r );
}

// --run_test=LibTests/UInt32ByteSwapTest
BOOST_AUTO_TEST_CASE( UInt32ByteSwapTest )
{
    using ValueType = UInt32;
    constexpr ValueType valueMin = std::numeric_limits<ValueType>::min( );
    constexpr ValueType valueM1 = static_cast<ValueType>( -1 );
    constexpr ValueType value0 = static_cast<ValueType>( 0 );
    constexpr ValueType valueP1 = static_cast<ValueType>( 1 );
    constexpr ValueType valueMax = std::numeric_limits<ValueType>::max( );

    constexpr ValueType valueMinResult1 = ByteSwap( valueMin );
    constexpr ValueType valueM1Result1 = ByteSwap( valueM1 );
    constexpr ValueType value0Result1 = ByteSwap( value0 );
    constexpr ValueType valueP1Result1 = ByteSwap( valueP1 );
    constexpr ValueType valueMaxResult1 = ByteSwap( valueMax );

    ValueType valueMinResult1r = _byteswap_ulong( valueMin );
    ValueType valueM1Result1r = _byteswap_ulong( valueM1 );
    ValueType value0Result1r = _byteswap_ulong( value0 );
    ValueType valueP1Result1r = _byteswap_ulong( valueP1 );
    ValueType valueMaxResult1r = _byteswap_ulong( valueMax );

    constexpr ValueType valueMinResult2 = ByteSwap( valueMinResult1 );
    constexpr ValueType valueM1Result2 = ByteSwap( valueM1Result1 );
    constexpr ValueType value0Result2 = ByteSwap( value0Result1 );
    constexpr ValueType valueP1Result2 = ByteSwap( valueP1Result1 );
    constexpr ValueType valueMaxResult2 = ByteSwap( valueMaxResult1 );

    BOOST_CHECK( valueMinResult2 == valueMin );
    BOOST_CHECK( valueM1Result2 == valueM1 );
    BOOST_CHECK( value0Result2 == value0 );
    BOOST_CHECK( valueP1Result2 == valueP1 );
    BOOST_CHECK( valueMaxResult2 == valueMax );

    BOOST_CHECK( valueMinResult1 == valueMinResult1r );
    BOOST_CHECK( valueM1Result1 == valueM1Result1r );
    BOOST_CHECK( value0Result1 == value0Result1r );
    BOOST_CHECK( valueP1Result1 == valueP1Result1r );
    BOOST_CHECK( valueMaxResult1 == valueMaxResult1r );

}

// --run_test=LibTests/Int64ByteSwapTest
BOOST_AUTO_TEST_CASE( Int64ByteSwapTest )
{
    using ValueType = Int64;
    constexpr ValueType valueMin = std::numeric_limits<ValueType>::min( );
    constexpr ValueType valueM1 = static_cast<ValueType>( -1 );
    constexpr ValueType value0 = static_cast<ValueType>( 0 );
    constexpr ValueType valueP1 = static_cast<ValueType>( 1 );
    constexpr ValueType valueMax = std::numeric_limits<ValueType>::max( );

    constexpr ValueType valueMinResult1 = ByteSwap( valueMin );
    constexpr ValueType valueM1Result1 = ByteSwap( valueM1 );
    constexpr ValueType value0Result1 = ByteSwap( value0 );
    constexpr ValueType valueP1Result1 = ByteSwap( valueP1 );
    constexpr ValueType valueMaxResult1 = ByteSwap( valueMax );

    ValueType valueMinResult1r = _byteswap_uint64( valueMin );
    ValueType valueM1Result1r = _byteswap_uint64( valueM1 );
    ValueType value0Result1r = _byteswap_uint64( value0 );
    ValueType valueP1Result1r = _byteswap_uint64( valueP1 );
    ValueType valueMaxResult1r = _byteswap_uint64( valueMax );


    constexpr ValueType valueMinResult2 = ByteSwap( valueMinResult1 );
    constexpr ValueType valueM1Result2 = ByteSwap( valueM1Result1 );
    constexpr ValueType value0Result2 = ByteSwap( value0Result1 );
    constexpr ValueType valueP1Result2 = ByteSwap( valueP1Result1 );
    constexpr ValueType valueMaxResult2 = ByteSwap( valueMaxResult1 );

    BOOST_CHECK( valueMinResult2 == valueMin );
    BOOST_CHECK( valueM1Result2 == valueM1 );
    BOOST_CHECK( value0Result2 == value0 );
    BOOST_CHECK( valueP1Result2 == valueP1 );
    BOOST_CHECK( valueMaxResult2 == valueMax );

    BOOST_CHECK( valueMinResult1 == valueMinResult1r );
    BOOST_CHECK( valueM1Result1 == valueM1Result1r );
    BOOST_CHECK( value0Result1 == value0Result1r );
    BOOST_CHECK( valueP1Result1 == valueP1Result1r );
    BOOST_CHECK( valueMaxResult1 == valueMaxResult1r );

}

// --run_test=LibTests/UInt64ByteSwapTest
BOOST_AUTO_TEST_CASE( UInt64ByteSwapTest )
{
    using ValueType = UInt64;
    constexpr ValueType valueMin = std::numeric_limits<ValueType>::min( );
    constexpr ValueType valueM1 = static_cast<ValueType>( -1 );
    constexpr ValueType value0 = static_cast<ValueType>( 0 );
    constexpr ValueType valueP1 = static_cast<ValueType>( 1 );
    constexpr ValueType valueMax = std::numeric_limits<ValueType>::max( );

    constexpr ValueType valueMinResult1 = ByteSwap( valueMin );
    constexpr ValueType valueM1Result1 = ByteSwap( valueM1 );
    constexpr ValueType value0Result1 = ByteSwap( value0 );
    constexpr ValueType valueP1Result1 = ByteSwap( valueP1 );
    constexpr ValueType valueMaxResult1 = ByteSwap( valueMax );

    ValueType valueMinResult1r = _byteswap_uint64( valueMin );
    ValueType valueM1Result1r = _byteswap_uint64( valueM1 );
    ValueType value0Result1r = _byteswap_uint64( value0 );
    ValueType valueP1Result1r = _byteswap_uint64( valueP1 );
    ValueType valueMaxResult1r = _byteswap_uint64( valueMax );

    constexpr ValueType valueMinResult2 = ByteSwap( valueMinResult1 );
    constexpr ValueType valueM1Result2 = ByteSwap( valueM1Result1 );
    constexpr ValueType value0Result2 = ByteSwap( value0Result1 );
    constexpr ValueType valueP1Result2 = ByteSwap( valueP1Result1 );
    constexpr ValueType valueMaxResult2 = ByteSwap( valueMaxResult1 );

    BOOST_CHECK( valueMinResult2 == valueMin );
    BOOST_CHECK( valueM1Result2 == valueM1 );
    BOOST_CHECK( value0Result2 == value0 );
    BOOST_CHECK( valueP1Result2 == valueP1 );
    BOOST_CHECK( valueMaxResult2 == valueMax );

    BOOST_CHECK( valueMinResult1 == valueMinResult1r );
    BOOST_CHECK( valueM1Result1 == valueM1Result1r );
    BOOST_CHECK( value0Result1 == value0Result1r );
    BOOST_CHECK( valueP1Result1 == valueP1Result1r );
    BOOST_CHECK( valueMaxResult1 == valueMaxResult1r );
}

// --run_test=LibTests/ByteSwapAndNetworkByteorderTest
BOOST_AUTO_TEST_CASE( ByteSwapAndNetworkByteorderTest )
{
    UInt32 initialValue = 0x04030201;
    UInt32 expectedValue = 0x01020304;
    auto htonlResult = htonl( initialValue );
    BOOST_CHECK( htonlResult == expectedValue );
    auto byteSwapUInt32Result = ByteSwap<UInt32>( initialValue );
    BOOST_CHECK( byteSwapUInt32Result == expectedValue );
    BOOST_CHECK( htonlResult == byteSwapUInt32Result );
}


// --run_test=LibTests/SignMaskTest
BOOST_AUTO_TEST_CASE( SignMaskTest )
{
    constexpr SByte signMaskSByte = SignMask<SByte>;
    constexpr SByte valueMaskSByte = ValueMask<SByte>;
    constexpr SByte expectedSignMaskSByte = static_cast<SByte>( 0x80 );
    constexpr SByte expectedValueMaskSByte = static_cast<SByte>( 0x7F );

    BOOST_CHECK( signMaskSByte == expectedSignMaskSByte );
    BOOST_CHECK( valueMaskSByte == expectedValueMaskSByte );

    constexpr Byte signMaskByte = SignMask<Byte>;
    constexpr Byte valueMaskByte = ValueMask<Byte>;
    constexpr Byte expectedSignMaskByte = static_cast<Byte>( 0x80 );
    constexpr Byte expectedValueMaskByte = static_cast<Byte>( 0x7F );

    BOOST_CHECK( signMaskByte == expectedSignMaskByte );
    BOOST_CHECK( valueMaskByte == expectedValueMaskByte );

    constexpr Int16 signMaskInt16 = SignMask<Int16>;
    constexpr Int16 valueMaskInt16 = ValueMask<Int16>;
    constexpr Int16 expectedSignMaskInt16 = static_cast<Int16>( 0x8000 );
    constexpr Int16 expectedValueMaskInt16 = static_cast<Int16>( 0x7FFF );

    BOOST_CHECK( signMaskInt16 == expectedSignMaskInt16 );
    BOOST_CHECK( valueMaskInt16 == expectedValueMaskInt16 );

    constexpr UInt16 signMaskUInt16 = SignMask<UInt16>;
    constexpr UInt16 valueMaskUInt16 = ValueMask<UInt16>;
    constexpr UInt16 expectedSignMaskUInt16 = static_cast<UInt16>( 0x8000 );
    constexpr UInt16 expectedValueMaskUInt16 = static_cast<UInt16>( 0x7FFF );

    BOOST_CHECK( signMaskUInt16 == expectedSignMaskUInt16 );
    BOOST_CHECK( valueMaskUInt16 == expectedValueMaskUInt16 );

    constexpr Int32 signMaskInt32 = SignMask<Int32>;
    constexpr Int32 valueMaskInt32 = ValueMask<Int32>;
    constexpr Int32 expectedSignMaskInt32 = static_cast<Int32>( 0x80000000 );
    constexpr Int32 expectedValueMaskInt32 = static_cast<Int32>( 0x7FFFFFFF );

    BOOST_CHECK( signMaskInt32 == expectedSignMaskInt32 );
    BOOST_CHECK( valueMaskInt32 == expectedValueMaskInt32 );

    constexpr UInt32 signMaskUInt32 = SignMask<UInt32>;
    constexpr UInt32 valueMaskUInt32 = ValueMask<UInt32>;
    constexpr UInt32 expectedSignMaskUInt32 = static_cast<UInt32>( 0x80000000 );
    constexpr UInt32 expectedValueMaskUInt32 = static_cast<UInt32>( 0x7FFFFFFF );

    BOOST_CHECK( signMaskUInt32 == expectedSignMaskUInt32 );
    BOOST_CHECK( valueMaskUInt32 == expectedValueMaskUInt32 );

    constexpr Int64 signMaskInt64 = SignMask<Int64>;
    constexpr Int64 valueMaskInt64 = ValueMask<Int64>;
    constexpr Int64 expectedSignMaskInt64 = static_cast<Int64>( 0x8000000000000000ULL );
    constexpr Int64 expectedValueMaskInt64 = static_cast<Int64>( 0x7FFFFFFFFFFFFFFFULL );

    BOOST_CHECK( signMaskInt64 == expectedSignMaskInt64 );
    BOOST_CHECK( valueMaskInt64 == expectedValueMaskInt64 );

    constexpr UInt64 signMaskUInt64 = SignMask<UInt64>;
    constexpr UInt64 valueMaskUInt64 = ValueMask<UInt64>;
    constexpr UInt64 expectedSignMaskUInt64 = static_cast<UInt64>( 0x8000000000000000ULL );
    constexpr UInt64 expectedValueMaskUInt64 = static_cast<UInt64>( 0x7FFFFFFFFFFFFFFFULL );

    BOOST_CHECK( signMaskUInt64 == expectedSignMaskUInt64 );
    BOOST_CHECK( valueMaskUInt64 == expectedValueMaskUInt64 );

    constexpr UInt32 signMaskSingle = SignMask<float>;
    constexpr UInt32 valueMaskSingle = ValueMask<float>;
    constexpr UInt32 expectedSignMaskSingle = static_cast<UInt32>( 0x80000000 );
    constexpr UInt32 expectedValueMaskSingle = static_cast<UInt32>( 0x7FFFFFFF );

    BOOST_CHECK( signMaskSingle == expectedSignMaskSingle );
    BOOST_CHECK( valueMaskSingle == expectedValueMaskSingle );

    constexpr UInt64 signMaskDouble = SignMask<Double>;
    constexpr UInt64 valueMaskDouble = ValueMask<Double>;
    constexpr UInt64 expectedSignMaskDouble = static_cast<UInt64>( 0x8000000000000000ULL );
    constexpr UInt64 expectedValueMaskDouble = static_cast<UInt64>( 0x7FFFFFFFFFFFFFFFULL );

    BOOST_CHECK( signMaskDouble == expectedSignMaskDouble );
    BOOST_CHECK( valueMaskDouble == expectedValueMaskDouble );
}

// --run_test=LibTests/LengthOfTest1
BOOST_AUTO_TEST_CASE( LengthOfTest1 )
{
    constexpr size_t lengthOfCString = LengthOf( "Hi" );
    BOOST_CHECK( lengthOfCString == 2 );
    constexpr size_t lengthOfWideCString = LengthOf( L"Hi" );
    BOOST_CHECK( lengthOfCString == 2 );

    constexpr bool boolArray[2]{true,true};
    constexpr size_t lengthOfBoolArray = LengthOf( boolArray );
    BOOST_CHECK( lengthOfBoolArray == 2 );

    constexpr std::array<bool,2> boolArray2{ true,true };
    constexpr size_t lengthOfBoolArray2 = LengthOf( boolArray2 );
    BOOST_CHECK( lengthOfBoolArray2 == 2 );


    constexpr SByte sbyteArray[2]{'H','i'};
    constexpr size_t lengthOfSbyteArray = LengthOf( sbyteArray );
    BOOST_CHECK( lengthOfSbyteArray == 2 );

    constexpr std::array<SByte, 2> sbyteArray2{ 'H','i' };
    constexpr size_t lengthOfSbyteArray2 = LengthOf( sbyteArray2 );
    BOOST_CHECK( lengthOfSbyteArray2 == 2 );


    constexpr Byte byteArray[2]{ 'H','i' };
    constexpr size_t lengthOfByteArray = LengthOf( byteArray );
    BOOST_CHECK( lengthOfByteArray == 2 );

    constexpr std::string_view strView("Hi");
    constexpr size_t lengthOfStrView = LengthOf( strView );
    BOOST_CHECK( lengthOfStrView == 2 );


    Int16 Int16Array[2]{ 10,20 };
    constexpr size_t lengthOfInt16Array = LengthOf( Int16Array );
    BOOST_CHECK( lengthOfInt16Array == 2 );
}


// --run_test=LibTests/NextPowerOfTwoTest1
BOOST_AUTO_TEST_CASE( NextPowerOfTwoTest1 )
{
    constexpr Byte val0 = 0;
    constexpr UInt32 result0 = NextPowerOfTwo( val0 );
    BOOST_CHECK( result0 == 0 );


    constexpr Byte val1 = 1 << 0;
    constexpr UInt32 result1 = NextPowerOfTwo( val1 );
    constexpr bool result1IsPowerOfTwo = IsPowerOfTwo( result1 );
    BOOST_CHECK( result1IsPowerOfTwo );

    constexpr Byte val2 = 1 << 1;
    constexpr UInt32 result2 = NextPowerOfTwo( val2 );

    constexpr bool result2IsPowerOfTwo = IsPowerOfTwo( result2 );
    BOOST_CHECK( result2IsPowerOfTwo );

    constexpr Byte val2p1 = val2 + val1;
    constexpr UInt32 result2p1 = NextPowerOfTwo( val2p1 );

    constexpr bool result2p1IsPowerOfTwo = IsPowerOfTwo( result2p1 );
    BOOST_CHECK( result2p1IsPowerOfTwo );

    constexpr Byte val3 = 1 << 2;
    constexpr UInt32 result3 = NextPowerOfTwo( val3 );

    constexpr bool result3IsPowerOfTwo = IsPowerOfTwo( result3 );
    BOOST_CHECK( result3IsPowerOfTwo );

    constexpr Byte val3p2 = val3 + val2;
    constexpr UInt32 result3p2 = NextPowerOfTwo( val3p2 );
    constexpr bool result3p2IsPowerOfTwo = IsPowerOfTwo( result3p2 );
    BOOST_CHECK( result3p2IsPowerOfTwo );


    constexpr Byte val4 = 1 << 3;
    constexpr UInt32 result4 = NextPowerOfTwo( val4 );
    constexpr bool result4IsPowerOfTwo = IsPowerOfTwo( result4 );
    BOOST_CHECK( result4IsPowerOfTwo );
    constexpr Byte val4p3 = val4 + val3;
    constexpr UInt32 result4p3 = NextPowerOfTwo( val4p3 );
    constexpr bool result4p3IsPowerOfTwo = IsPowerOfTwo( result4p3 );
    BOOST_CHECK( result4p3IsPowerOfTwo );

    constexpr Byte val5 = 1 << 4;
    constexpr UInt32 result5 = NextPowerOfTwo( val5 );
    constexpr bool result5IsPowerOfTwo = IsPowerOfTwo( result5 );
    BOOST_CHECK( result5IsPowerOfTwo );
    constexpr Byte val5p4 = val5 + val4;
    constexpr UInt32 result5p4 = NextPowerOfTwo( val5p4 );
    constexpr bool result5p4IsPowerOfTwo = IsPowerOfTwo( result5p4 );
    BOOST_CHECK( result5p4IsPowerOfTwo );

    constexpr Byte val6 = 1 << 5;
    constexpr UInt32 result6 = NextPowerOfTwo( val6 );
    constexpr bool result6IsPowerOfTwo = IsPowerOfTwo( result6 );
    BOOST_CHECK( result6IsPowerOfTwo );

    constexpr Byte val6p5 = val6 + val5;
    constexpr UInt32 result6p4 = NextPowerOfTwo( val6p5 );
    constexpr bool result6p4IsPowerOfTwo = IsPowerOfTwo( result6p4 );
    BOOST_CHECK( result6p4IsPowerOfTwo );

    constexpr Byte val7 = 1 << 6;
    constexpr UInt32 result7 = NextPowerOfTwo( val7 );
    constexpr bool result7IsPowerOfTwo = IsPowerOfTwo( result7 );
    BOOST_CHECK( result7IsPowerOfTwo );

    constexpr Byte val7p6 = val7 + val6;
    constexpr UInt32 result7p4 = NextPowerOfTwo( val7p6 );
    constexpr bool result7p4IsPowerOfTwo = IsPowerOfTwo( result7p4 );
    BOOST_CHECK( result7p4IsPowerOfTwo );

    constexpr Byte val8 = 1 << 7;
    constexpr UInt32 result8 = NextPowerOfTwo( val8 );
    constexpr bool result8IsPowerOfTwo = IsPowerOfTwo( result8 );
    BOOST_CHECK( result8IsPowerOfTwo );

    constexpr Byte val8p7 = val8 + val7;
    constexpr UInt32 result8p4 = NextPowerOfTwo( val8p7 );
    constexpr bool result8p4IsPowerOfTwo = IsPowerOfTwo( result8p4 );
    BOOST_CHECK( result8p4IsPowerOfTwo == false );

    constexpr UInt16 val9 = 1 << 8;
    constexpr UInt32 result9 = NextPowerOfTwo( val9 );
    constexpr bool result9IsPowerOfTwo = IsPowerOfTwo( result9 );
    BOOST_CHECK( result9IsPowerOfTwo );

    constexpr UInt16 val9p8 = val9 + val8;
    constexpr UInt32 result9p8 = NextPowerOfTwo( val9p8 );
    constexpr bool result9p8IsPowerOfTwo = IsPowerOfTwo( result9p8 );
    BOOST_CHECK( result9p8IsPowerOfTwo );

    constexpr UInt16 val15 = 1 << 14;
    constexpr UInt32 result15 = NextPowerOfTwo( val15 );
    constexpr bool result15IsPowerOfTwo = IsPowerOfTwo( result15 );
    BOOST_CHECK( result15IsPowerOfTwo );

    constexpr UInt16 val15p8 = val15 + val8;
    constexpr UInt32 result15p8 = NextPowerOfTwo( val15p8 );
    constexpr bool result15p8IsPowerOfTwo = IsPowerOfTwo( result15p8 );
    BOOST_CHECK( result15p8IsPowerOfTwo );

    constexpr UInt16 val16 = 1 << 15;
    constexpr UInt32 result16 = NextPowerOfTwo( val16 );
    constexpr bool result16IsPowerOfTwo = IsPowerOfTwo( result16 );
    BOOST_CHECK( result16IsPowerOfTwo );

    constexpr UInt16 val16p8 = val16 + val8;
    constexpr UInt32 result16p8 = NextPowerOfTwo( val16p8 );
    constexpr bool result16p8IsPowerOfTwo = IsPowerOfTwo( result16p8 );
    BOOST_CHECK( result16p8IsPowerOfTwo == false );


    constexpr UInt32 val17 = 1 << 16;
    constexpr UInt64 result17 = NextPowerOfTwo( val17 );
    constexpr bool result17IsPowerOfTwo = IsPowerOfTwo( result17 );
    BOOST_CHECK( result17IsPowerOfTwo );
    constexpr UInt32 val17p8 = val17 + val8;
    constexpr UInt64 result17p8 = NextPowerOfTwo( val17p8 );
    constexpr bool result17p8IsPowerOfTwo = IsPowerOfTwo( result17p8 );
    BOOST_CHECK( result17p8IsPowerOfTwo );

    constexpr UInt32 val18 = 1U << 30U;
    constexpr UInt64 result18 = NextPowerOfTwo( val18 );
    constexpr bool result18IsPowerOfTwo = IsPowerOfTwo( result18 );
    BOOST_CHECK( result18IsPowerOfTwo );
    constexpr UInt32 val18p8 = val18 + val8;
    constexpr UInt64 result18p8 = NextPowerOfTwo( val18p8 );
    constexpr bool result18p8IsPowerOfTwo = IsPowerOfTwo( result18p8 );
    BOOST_CHECK( result18p8IsPowerOfTwo );


    constexpr UInt32 val19 = 1U << 31U;
    constexpr UInt64 result19 = NextPowerOfTwo( val19 );
    constexpr bool result19IsPowerOfTwo = IsPowerOfTwo( result19 );
    BOOST_CHECK( result19IsPowerOfTwo );
    constexpr UInt32 val19p8 = val19 + val8;
    constexpr UInt64 result19p8 = NextPowerOfTwo( val19p8 );
    constexpr bool result19p8IsPowerOfTwo = IsPowerOfTwo( result19p8 );
    BOOST_CHECK( result19p8IsPowerOfTwo == false );

    constexpr UInt64 val20 = 1ULL << 31U;
    constexpr UInt64 result20 = NextPowerOfTwo( val20 );
    constexpr bool result20IsPowerOfTwo = IsPowerOfTwo( result20 );
    BOOST_CHECK( result20IsPowerOfTwo );
    constexpr UInt64 val20p8 = val20 + val8;
    constexpr UInt64 result20p8 = NextPowerOfTwo( val20p8 );
    constexpr bool result20p8IsPowerOfTwo = IsPowerOfTwo( result20p8 );
    BOOST_CHECK( result20p8IsPowerOfTwo );

    constexpr UInt64 val21 = 1ULL << 62U;
    constexpr UInt64 result21 = NextPowerOfTwo( val21 );
    constexpr bool result21IsPowerOfTwo = IsPowerOfTwo( result21 );
    BOOST_CHECK( result21IsPowerOfTwo );
    constexpr UInt64 val21p8 = val21 + val8;
    constexpr UInt64 result21p8 = NextPowerOfTwo( val21p8 );
    constexpr bool result21p8IsPowerOfTwo = IsPowerOfTwo( result21p8 );
    BOOST_CHECK( result21p8IsPowerOfTwo );

    constexpr UInt64 val22 = 1ULL << 63U;
    constexpr UInt64 result22 = NextPowerOfTwo( val22 );
    constexpr bool result22IsPowerOfTwo = IsPowerOfTwo( result22 );
    BOOST_CHECK( result22IsPowerOfTwo );
    constexpr UInt64 val22p8 = val22 + val8;
    constexpr UInt64 result22p8 = NextPowerOfTwo( val22p8 );
    constexpr bool result22p8IsPowerOfTwo = IsPowerOfTwo( result22p8 );
    BOOST_CHECK( result22p8IsPowerOfTwo == false );

}

// --run_test=LibTests/MaskBitsTest1
BOOST_AUTO_TEST_CASE( MaskBitsTest1 )
{
    constexpr auto mask1 = CreateBitMask32( 4 );
    constexpr auto mask2 = BitMask<4>::value;
    BOOST_CHECK( mask1 == mask2 );
}

// --run_test=LibTests/ExtractBitsTest1
BOOST_AUTO_TEST_CASE( ExtractBitsTest1 )
{
    constexpr auto extracted1 = ExtractBits32( 0b1011010, 3, 2 );
    auto extracted2 = ExtractBits32( 0b0011000, 3, 2 );
    BOOST_CHECK( extracted1 == extracted2 );
}



BOOST_AUTO_TEST_SUITE_END( )

