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

BOOST_FIXTURE_TEST_SUITE( FixedStringTests, LocalFixture )

// --run_test=FixedStringTests/BasicCompiletimeTest1
BOOST_AUTO_TEST_CASE( BasicCompiletimeTest1 )
{
    using FixedString = FixedWideZString<UInt16, 128>;
    static_assert( FixedString::ArraySize == 129 );
    constexpr size_t alignment = std::alignment_of_v<FixedString>;
    static_assert( alignment == 1 );
    constexpr size_t sizeofFixedString = sizeof( FixedString );
    constexpr size_t expectedSizeofFixedString = sizeof( UInt16 ) + ( ( 128 + 1 ) * sizeof( wchar_t ) );
    static_assert( sizeofFixedString == expectedSizeofFixedString );
}
// --run_test=FixedStringTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    using FixedString = FixedWideZString<UInt16, 128>;
    FixedString str;
    BOOST_CHECK( str.length() == 0 );
}

// --run_test=FixedStringTests/ConstructorTest2
BOOST_AUTO_TEST_CASE( ConstructorTest2 )
{
    using FixedString = FixedWideZString<UInt16, 128>;
    FixedString str1(L"");
    constexpr bool val1 = IsSpecializationOf<std::string_view, std::basic_string_view>;
    constexpr bool val2 = IsSpecializationOf<std::string, std::basic_string>;

    BOOST_CHECK( str1.length( ) == 0 );
    FixedString str2( L"2" );
    BOOST_CHECK( str2.length( ) == 1 );
    FixedString str3( str2 );
    BOOST_CHECK( str3.length( ) == 1 );
}




BOOST_AUTO_TEST_SUITE_END( )