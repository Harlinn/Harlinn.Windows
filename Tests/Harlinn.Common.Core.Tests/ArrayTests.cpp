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

// --run_test=ArrayTests/ByteArrayConcatTest1
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest1 )
{
    constexpr ByteArray a1( static_cast<Byte>( 1 ) );
    constexpr ByteArray a2( static_cast<Byte>( 2 ) );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = a3[0];
    constexpr auto v2 = a3[1];

    constexpr auto rv1 = a3.Read<Byte>( a3.begin( ) );
    constexpr auto rv2 = a3.Read<Byte>( a3.begin( ) + 1 );
    constexpr auto orv1 = a3.Read<Byte>( 0 );
    constexpr auto orv2 = a3.Read<Byte>( 1 );

    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    BOOST_CHECK( rv1 == 1 );
    BOOST_CHECK( rv2 == 2 );
    BOOST_CHECK( orv1 == 1 );
    BOOST_CHECK( orv2 == 2 );

    constexpr auto a4 = a3 + static_cast<Byte>( 3 );
    constexpr auto v3 = a4[2];
    BOOST_CHECK( v3 == 3 );
}

// --run_test=ArrayTests/ByteArrayConcatTest2
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest2 )
{
    constexpr ByteArray a1( static_cast<Int16>( 1 ) );
    constexpr ByteArray a2( static_cast<Int16>( 2 ) );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = a3[0];
    constexpr auto v2 = a3[2];
    constexpr auto a3Size = a3.size( );

    constexpr auto rv1 = a3.Read<Int16>( a3.begin( ) );
    constexpr auto rv2 = a3.Read<Int16>( a3.begin( ) + 2 );
    constexpr auto orv1 = a3.Read<Int16>( 0 );
    constexpr auto orv2 = a3.Read<Int16>( 2 );

    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    BOOST_CHECK( rv1 == 1 );
    BOOST_CHECK( rv2 == 2 );
    BOOST_CHECK( orv1 == 1 );
    BOOST_CHECK( orv2 == 2 );
    BOOST_CHECK( a3Size == 4 );

    auto int16_1 = *(Int16*)a3.data( );
    auto int16_2 = *(Int16*)(a3.data( ) + 2 );

    BOOST_CHECK( int16_1 == 1 );
    BOOST_CHECK( int16_2 == 2 );

    constexpr auto a4 = a3 + static_cast<Int16>( 3 );
    constexpr auto v3 = a4[4];
    BOOST_CHECK( v3 == 3 );

}

// --run_test=ArrayTests/ByteArrayConcatTest3
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest3 )
{
    constexpr ByteArray a1( static_cast<Int32>( 1 ) );
    constexpr ByteArray a2( static_cast<Int32>( 2 ) );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = a3[0];
    constexpr auto v2 = a3[4];
    constexpr auto a3Size = a3.size( );

    constexpr auto rv1 = a3.Read<Int32>( a3.begin( ) );
    constexpr auto rv2 = a3.Read<Int32>( a3.begin( ) + 4 );
    constexpr auto orv1 = a3.Read<Int32>( 0 );
    constexpr auto orv2 = a3.Read<Int32>( 4 );


    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    BOOST_CHECK( rv1 == 1 );
    BOOST_CHECK( rv2 == 2 );
    BOOST_CHECK( orv1 == 1 );
    BOOST_CHECK( orv2 == 2 );
    BOOST_CHECK( a3Size == 8 );

    auto int32_1 = *(Int32*)a3.data( );
    auto int32_2 = *(Int32*)( a3.data( ) + 4 );

    BOOST_CHECK( int32_1 == 1 );
    BOOST_CHECK( int32_2 == 2 );

    constexpr auto a4 = a3 + static_cast<Int32>( 3 );
    constexpr auto v3 = a4[8];
    BOOST_CHECK( v3 == 3 );

}

// --run_test=ArrayTests/ByteArrayConcatTest4
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest4 )
{
    constexpr ByteArray a1( static_cast<Int64>( 1 ) );
    constexpr ByteArray a2( static_cast<Int64>( 2 ) );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = a3[0];
    constexpr auto v2 = a3[8];
    constexpr auto a3Size = a3.size( );

    constexpr auto rv1 = a3.Read<Int64>( a3.begin( ) );
    constexpr auto rv2 = a3.Read<Int64>( a3.begin( ) + 8 );
    constexpr auto orv1 = a3.Read<Int64>( 0 );
    constexpr auto orv2 = a3.Read<Int64>( 8 );

    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    BOOST_CHECK( rv1 == 1 );
    BOOST_CHECK( rv2 == 2 );
    BOOST_CHECK( orv1 == 1 );
    BOOST_CHECK( orv2 == 2 );
    BOOST_CHECK( a3Size == 16 );

    auto int64_1 = *(Int64*)a3.data( );
    auto int64_2 = *(Int64*)( a3.data( ) + 8 );

    BOOST_CHECK( int64_1 == 1 );
    BOOST_CHECK( int64_2 == 2 );

    constexpr auto a4 = a3 + static_cast<Int64>( 3 );
    constexpr auto v3 = a4[16];
    BOOST_CHECK( v3 == 3 );

}

// --run_test=ArrayTests/ByteArrayConcatTest5
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest5 )
{
    constexpr ByteArray a1( 1.0f );
    constexpr ByteArray a2( 2.0f );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = static_cast<UInt32>( a3[3]);
    constexpr auto v2 = static_cast<UInt32>( a3[7]);
    constexpr auto a3Size = a3.size( );

    constexpr auto rv1 = a3.Read<float>( a3.begin( ) );
    constexpr auto rv2 = a3.Read<float>( a3.begin( ) + 4 );
    constexpr auto orv1 = a3.Read<float>( 0 );
    constexpr auto orv2 = a3.Read<float>( 4 );


    BOOST_CHECK( v1 == 63 );
    BOOST_CHECK( v2 == 64 );

    BOOST_CHECK( rv1 == 1.0f );
    BOOST_CHECK( rv2 == 2.0f );
    BOOST_CHECK( orv1 == 1.0f );
    BOOST_CHECK( orv2 == 2.0f );

    BOOST_CHECK( a3Size == 8 );

    auto float_1 = *(float*)a3.data( );
    auto float_2 = *(float*)( a3.data( ) + 4 );

    BOOST_CHECK( float_1 == 1.0f );
    BOOST_CHECK( float_2 == 2.0f );

    constexpr auto a4 = a3 + static_cast<float>( 3.0f );
    constexpr auto v3 = a4.Read<float>(8);
    BOOST_CHECK( v3 == 3.0f );


}

// --run_test=ArrayTests/ByteArrayConcatTest6
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest6 )
{
    constexpr ByteArray a1( 1.0 );
    constexpr ByteArray a2( 2.0 );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = static_cast<UInt32>( a3[7] );
    constexpr auto v2 = static_cast<UInt32>( a3[15] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( v1 == 63 );
    BOOST_CHECK( v2 == 64 );
    BOOST_CHECK( a3Size == 16 );

    auto double_1 = *(double*)a3.data( );
    auto double_2 = *(double*)( a3.data( ) + 8 );

    BOOST_CHECK( double_1 == 1.0f );
    BOOST_CHECK( double_2 == 2.0f );

    constexpr auto a4 = a3 + 3.0;
    constexpr auto v3 = a4.Read<double>( 16 );
    BOOST_CHECK( v3 == 3.0f );

}

// --run_test=ArrayTests/ByteArrayConcatTest7
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest7 )
{
    constexpr ByteArray a1( false );
    constexpr ByteArray a2( true );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = static_cast<UInt32>( a3[0] );
    constexpr auto v2 = static_cast<UInt32>( a3[1] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( v1 == 0 );
    BOOST_CHECK( v2 == 1 );
    BOOST_CHECK( a3Size == 2 );

    auto byte_1 = *(Byte*)a3.data( );
    auto byte_2 = *(Byte*)( a3.data( ) + 1 );

    BOOST_CHECK( byte_1 == 0 );
    BOOST_CHECK( byte_2 == 1 );

    constexpr auto a4 = a3 + false;
    constexpr auto v3 = a4.Read<bool>( 2 );
    BOOST_CHECK( v3 == false );

}

// --run_test=ArrayTests/ByteArrayConcatTest8
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest8 )
{
    constexpr ByteArray a1( static_cast<SByte>( 1 ) );
    constexpr ByteArray a2( static_cast<SByte>( 2 ) );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = static_cast<UInt32>( a3[0] );
    constexpr auto v2 = static_cast<UInt32>( a3[1] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    BOOST_CHECK( a3Size == 2 );

    auto sbyte_1 = *(SByte*)a3.data( );
    auto sbyte_2 = *(SByte*)( a3.data( ) + 1 );

    BOOST_CHECK( sbyte_1 == 1 );
    BOOST_CHECK( sbyte_2 == 2 );

    constexpr auto a4 = a3 + static_cast<SByte>( 3 );
    constexpr auto v3 = a4.Read<SByte>( 2 );
    BOOST_CHECK( v3 == 3 );

}

// --run_test=ArrayTests/ByteArrayConcatTest9
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest9 )
{
    constexpr ByteArray a1( static_cast<UInt16>( 1 ) );
    constexpr ByteArray a2( static_cast<UInt16>( 2 ) );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = static_cast<UInt32>( a3[0] );
    constexpr auto v2 = static_cast<UInt32>( a3[2] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    BOOST_CHECK( a3Size == 4 );

    auto uint16_1 = *(UInt16*)a3.data( );
    auto uint16_2 = *(UInt16*)( a3.data( ) + 2 );

    BOOST_CHECK( uint16_1 == 1 );
    BOOST_CHECK( uint16_2 == 2 );

    constexpr auto a4 = a3 + static_cast<UInt16>( 3 );
    constexpr auto v3 = a4.Read<UInt16>( 4 );
    BOOST_CHECK( v3 == 3 );
}

// --run_test=ArrayTests/ByteArrayConcatTest10
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest10 )
{
    constexpr ByteArray a1( static_cast<UInt32>( 1 ) );
    constexpr ByteArray a2( static_cast<UInt32>( 2 ) );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = static_cast<UInt32>( a3[0] );
    constexpr auto v2 = static_cast<UInt32>( a3[4] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    BOOST_CHECK( a3Size == 8 );

    auto uint32_1 = *(UInt32*)a3.data( );
    auto uint32_2 = *(UInt32*)( a3.data( ) + 4 );

    BOOST_CHECK( uint32_1 == 1 );
    BOOST_CHECK( uint32_2 == 2 );

    constexpr auto a4 = a3 + static_cast<UInt32>( 3 );
    constexpr auto v3 = a4.Read<UInt32>( 8 );
    BOOST_CHECK( v3 == 3 );
}

// --run_test=ArrayTests/ByteArrayConcatTest11
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest11 )
{
    constexpr ByteArray a1( static_cast<UInt64>( 1 ) );
    constexpr ByteArray a2( static_cast<UInt64>( 2 ) );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = static_cast<UInt32>( a3[0] );
    constexpr auto v2 = static_cast<UInt32>( a3[8] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( v1 == 1 );
    BOOST_CHECK( v2 == 2 );
    BOOST_CHECK( a3Size == 16 );

    auto uint64_1 = *(UInt64*)a3.data( );
    auto uint64_2 = *(UInt64*)( a3.data( ) + 8 );

    BOOST_CHECK( uint64_1 == 1 );
    BOOST_CHECK( uint64_2 == 2 );

    constexpr auto a4 = a3 + static_cast<UInt64>( 3 );
    constexpr auto v3 = a4.Read<UInt64>( 16 );
    BOOST_CHECK( v3 == 3 );
}


// --run_test=ArrayTests/ByteArrayConcatTest12
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest12 )
{
    constexpr TimeSpan v1( 1LL );
    constexpr TimeSpan v2( 2LL );
    constexpr TimeSpan v3( 3LL );

    constexpr ByteArray a1( v1 );
    constexpr ByteArray a2( v2 );
    constexpr auto a3 = a1 + a2;
    constexpr auto bv1 = static_cast<UInt32>( a3[0] );
    constexpr auto bv2 = static_cast<UInt32>( a3[8] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( bv1 == 1 );
    BOOST_CHECK( bv2 == 2 );
    BOOST_CHECK( a3Size == 16 );

    auto timeSpan_1 = *(TimeSpan*)a3.data( );
    auto timeSpan_2 = *(TimeSpan*)( a3.data( ) + 8 );

    BOOST_CHECK( timeSpan_1 == v1 );
    BOOST_CHECK( timeSpan_2 == v2 );

    constexpr auto a4 = a3 + v3;
    constexpr auto timeSpan_3 = a4.Read<TimeSpan>( 16 );
    BOOST_CHECK( timeSpan_3 == v3 );
}

// --run_test=ArrayTests/ByteArrayConcatTest13
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest13 )
{
    constexpr DateTime v1( 1LL );
    constexpr DateTime v2( 2LL );
    constexpr DateTime v3( 3LL );

    constexpr ByteArray a1( v1 );
    constexpr ByteArray a2( v2 );
    constexpr auto a3 = a1 + a2;
    constexpr auto bv1 = static_cast<UInt32>( a3[0] );
    constexpr auto bv2 = static_cast<UInt32>( a3[8] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( bv1 == 1 );
    BOOST_CHECK( bv2 == 2 );
    BOOST_CHECK( a3Size == 16 );

    auto dateTime_1 = *(DateTime*)a3.data( );
    auto dateTime_2 = *(DateTime*)( a3.data( ) + 8 );

    BOOST_CHECK( dateTime_1 == v1 );
    BOOST_CHECK( dateTime_2 == v2 );

    constexpr auto a4 = a3 + v3;
    constexpr auto dateTime_3 = a4.Read<DateTime>( 16 );
    BOOST_CHECK( dateTime_3 == v3 );
}

// --run_test=ArrayTests/ByteArrayConcatTest14
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest14 )
{
    constexpr Currency v1( 1LL );
    constexpr Currency v2( 2LL );
    constexpr Currency v3( 3LL );

    constexpr ByteArray a1( v1 );
    constexpr ByteArray a2( v2 );
    constexpr auto a3 = a1 + a2;
    constexpr auto bv1 = static_cast<UInt32>( a3[0] );
    constexpr auto bv2 = static_cast<UInt32>( a3[8] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( bv1 == 16 );
    BOOST_CHECK( bv2 == 32 );
    BOOST_CHECK( a3Size == 16 );

    auto currency_1 = *(Currency*)a3.data( );
    auto currency_2 = *(Currency*)( a3.data( ) + 8 );

    BOOST_CHECK( currency_1 == v1 );
    BOOST_CHECK( currency_2 == v2 );

    constexpr auto a4 = a3 + v3;
    constexpr auto currency_3 = a4.Read<Currency>( 16 );
    BOOST_CHECK( currency_3 == v3 );
}

// --run_test=ArrayTests/ByteArrayConcatTest15
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest15 )
{
    // {9593FFC6-E842-49A0-A1B8-5247B78F89CB}
    constexpr GUID v1 =
    { 0x9593ffc6, 0xe842, 0x49a0, { 0xa1, 0xb8, 0x52, 0x47, 0xb7, 0x8f, 0x89, 0xcb } };

    // {9A31D67A-2DBF-46F4-85D4-EB67E12A1372}
    constexpr GUID v2 =
    { 0x9a31d67a, 0x2dbf, 0x46f4, { 0x85, 0xd4, 0xeb, 0x67, 0xe1, 0x2a, 0x13, 0x72 } };

    // {0FBBB7F3-9EAB-4B44-8C3C-B4E872D1CE12}
    constexpr GUID v3 =
    { 0xfbbb7f3, 0x9eab, 0x4b44, { 0x8c, 0x3c, 0xb4, 0xe8, 0x72, 0xd1, 0xce, 0x12 } };


    constexpr ByteArray a1( v1 );
    constexpr ByteArray a2( v2 );
    constexpr auto a3 = a1 + a2;
    constexpr auto bv1 = static_cast<UInt32>( a3[0] );
    constexpr auto bv2 = static_cast<UInt32>( a3[16] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( bv1 == 198 );
    BOOST_CHECK( bv2 == 122 );
    BOOST_CHECK( a3Size == 32 );

    auto guid_1 = *(GUID*)a3.data( );
    auto guid_2 = *(GUID*)( a3.data( ) + 16 );

    BOOST_CHECK( guid_1 == v1 );
    BOOST_CHECK( guid_2 == v2 );

    constexpr auto a4 = a3 + v3;
    constexpr auto guid_3 = a4.Read<GUID>( 32 );
    BOOST_CHECK( guid_3 == v3 );
}

// --run_test=ArrayTests/ByteArrayConcatTest16
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest16 )
{
    // {9593FFC6-E842-49A0-A1B8-5247B78F89CB}
    constexpr Guid v1( 0x9593ffc6, 0xe842, 0x49a0, 0xa1, 0xb8, 0x52, 0x47, 0xb7, 0x8f, 0x89, 0xcb );

    // {9A31D67A-2DBF-46F4-85D4-EB67E12A1372}
    constexpr Guid v2( 0x9a31d67a, 0x2dbf, 0x46f4, 0x85, 0xd4, 0xeb, 0x67, 0xe1, 0x2a, 0x13, 0x72 );

    // {0FBBB7F3-9EAB-4B44-8C3C-B4E872D1CE12}
    constexpr Guid v3( 0xfbbb7f3, 0x9eab, 0x4b44, 0x8c, 0x3c, 0xb4, 0xe8, 0x72, 0xd1, 0xce, 0x12 );

    constexpr ByteArray a1( v1 );
    constexpr ByteArray a2( v2 );
    constexpr auto a3 = a1 + a2;
    constexpr auto bv1 = static_cast<UInt32>( a3[0] );
    constexpr auto bv2 = static_cast<UInt32>( a3[16] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( bv1 == 198 );
    BOOST_CHECK( bv2 == 122 );
    BOOST_CHECK( a3Size == 32 );

    auto guid_1 = *(Guid*)a3.data( );
    auto guid_2 = *(Guid*)( a3.data( ) + 16 );

    BOOST_CHECK( guid_1 == v1 );
    BOOST_CHECK( guid_2 == v2 );

    constexpr auto a4 = a3 + v3;
    constexpr auto guid_3 = a4.Read<Guid>( 32 );
    BOOST_CHECK( guid_3 == v3 );
}

enum class EnumTest17 : UInt16
{
    Zero = 0,
    One = 1,
    Two = 2
};

// --run_test=ArrayTests/ByteArrayConcatTest17
BOOST_AUTO_TEST_CASE( ByteArrayConcatTest17 )
{
    constexpr ByteArray a1( EnumTest17::Zero );
    constexpr ByteArray a2( EnumTest17::One );
    constexpr auto a3 = a1 + a2;
    constexpr auto v1 = static_cast<UInt32>( a3[0] );
    constexpr auto v2 = static_cast<UInt32>( a3[2] );
    constexpr auto a3Size = a3.size( );

    BOOST_CHECK( v1 == 0 );
    BOOST_CHECK( v2 == 1 );
    BOOST_CHECK( a3Size == 4 );

    auto enumTest17_1 = *(EnumTest17*)a3.data( );
    auto enumTest17_2 = *(EnumTest17*)( a3.data( ) + 2 );

    BOOST_CHECK( enumTest17_1 == EnumTest17::Zero );
    BOOST_CHECK( enumTest17_2 == EnumTest17::One );

    constexpr auto a4 = a3 + EnumTest17::Two;
    constexpr auto v3 = a4.Read<EnumTest17>( 4 );
    BOOST_CHECK( v3 == EnumTest17::Two );

}




// --run_test=ArrayTests/ByteOffsetOfTest1
BOOST_AUTO_TEST_CASE( ByteOffsetOfTest1 )
{
    constexpr size_t byteOffsetOf1 = Internal::ByteOffsetOf_v<5,UInt32,Byte,std::array<Byte,5>,Byte[4],float,double>;
    BOOST_CHECK( byteOffsetOf1 == 18 );
    constexpr size_t byteSizeOf1 = Internal::_ByteSizeOf_v<UInt32, Byte, std::array<Byte, 5>, Byte[4], float, double>;
    BOOST_CHECK( byteSizeOf1 == 26 );

}

// --run_test=ArrayTests/ByteArrayConstructorTest1
BOOST_AUTO_TEST_CASE( ByteArrayConstructorTest1 )
{
    constexpr ByteArray a1( 1.0f, 4 );
    constexpr size_t a1Size = a1.size( );
    BOOST_CHECK( a1Size == 8 );

    constexpr auto floatValue = a1.Read<float>( 0 );
    constexpr auto int32Value = a1.Read<Int32>( 4 );
    BOOST_CHECK( floatValue == 1.0f );
    BOOST_CHECK( int32Value == 4 );


}


// --run_test=ArrayTests/ByteArrayConstructorTest2
BOOST_AUTO_TEST_CASE( ByteArrayConstructorTest2 )
{
    constexpr ByteArray a1( false, 
        static_cast<SByte>( 1 ),
        static_cast<Byte>( 2 ),
        static_cast<Int16>( 3 ),
        static_cast<UInt16>( 4 ),
        static_cast<Int32>( 5 ),
        static_cast<UInt32>( 6 ),
        static_cast<Int64>( 7 ),
        static_cast<UInt64>( 8 ),
        static_cast<float>( 9 ),
        static_cast<double>( 10 ) );
    constexpr size_t a1Size = a1.size( );
    BOOST_CHECK( a1Size == 43 );

    constexpr auto boolValue = a1.Read<bool>( 0 );
    constexpr auto sbyteValue = a1.Read<SByte>( 1 );
    constexpr auto byteValue = a1.Read<Byte>( 2 );
    constexpr auto int16Value = a1.Read<Int16>( 3 );
    constexpr auto uint16Value = a1.Read<UInt16>( 5 );
    constexpr auto int32Value = a1.Read<Int32>( 7 );
    constexpr auto uint32Value = a1.Read<UInt32>( 11 );
    constexpr auto int64Value = a1.Read<Int64>( 15 );
    constexpr auto uint64Value = a1.Read<UInt64>( 23 );
    constexpr auto floatValue = a1.Read<float>( 31 );
    constexpr auto doubleValue = a1.Read<double>( 35 );


    BOOST_CHECK( boolValue == false );
    BOOST_CHECK( sbyteValue == 1 );
    BOOST_CHECK( byteValue == 2 );
    BOOST_CHECK( int16Value == 3 );
    BOOST_CHECK( uint16Value == 4 );
    BOOST_CHECK( int32Value == 5 );
    BOOST_CHECK( uint32Value == 6 );
    BOOST_CHECK( int64Value == 7 );
    BOOST_CHECK( uint64Value == 8 );
    BOOST_CHECK( floatValue == 9.0f );
    BOOST_CHECK( doubleValue == 10.0 );
}

// --run_test=ArrayTests/ByteArrayConstructorTest3
BOOST_AUTO_TEST_CASE( ByteArrayConstructorTest3 )
{
    constexpr std::array<double, 2> dblArray{};
    constexpr ByteArray a1( dblArray );
    constexpr size_t a1Size = a1.size( );
    BOOST_CHECK( a1Size == 16 );

}

// --run_test=ArrayTests/ByteArrayConstructorTest4
BOOST_AUTO_TEST_CASE( ByteArrayConstructorTest4 )
{
    // {83272B5E-DDF8-4C3E-912C-68070A31E89B}
    constexpr GUID guidValue1 =
    { 0x83272b5e, 0xddf8, 0x4c3e, { 0x91, 0x2c, 0x68, 0x7, 0xa, 0x31, 0xe8, 0x9b } };
    constexpr Guid guidValue2( 0x83272b5e, 0xddf8, 0x4c3e, 0x91, 0x2c, 0x68, 0x7, 0xa, 0x31, 0xe8, 0x9b );


    constexpr ByteArray a1( guidValue1 );
    constexpr ByteArray a2( guidValue2 );

    constexpr bool areEqual = a1 == a2;

    BOOST_CHECK( areEqual );

}





BOOST_AUTO_TEST_SUITE_END( )
