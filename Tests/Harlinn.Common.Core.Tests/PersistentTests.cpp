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





BOOST_FIXTURE_TEST_SUITE( PersistentTests, LocalFixture )

// --run_test=PersistentTests/SevenBitEncodingSizeTest1
BOOST_AUTO_TEST_CASE( SevenBitEncodingSizeTest1 )
{

    constexpr size_t sizeZero = SizeOf7BitEncodedValue( 0 );
    constexpr auto bytesZero = Write7BitEncodedValue<sizeZero>( static_cast< UInt64>( 0 ) );
    constexpr auto resultZero = Read7BitEncodedValue( bytesZero );
    BOOST_CHECK( resultZero == 0 );

    constexpr auto maxValue = std::numeric_limits<UInt64>::max( );
    constexpr size_t sizeMaxValue = SizeOf7BitEncodedValue( maxValue );
    constexpr auto bytesMaxValue = Write7BitEncodedValue<sizeMaxValue>( maxValue );
    constexpr auto resultMaxValue = Read7BitEncodedValue( bytesMaxValue );
    BOOST_CHECK( maxValue == resultMaxValue );

    constexpr auto maxValueM1 = maxValue - 1;
    constexpr size_t sizeMaxValueM1 = SizeOf7BitEncodedValue( maxValueM1 );
    constexpr auto bytesMaxValueM1 = Write7BitEncodedValue<sizeMaxValueM1>( maxValueM1 );
    constexpr auto resultMaxValueM1 = Read7BitEncodedValue( bytesMaxValueM1 );
    BOOST_CHECK( maxValueM1 == resultMaxValueM1 );


    
    constexpr UInt64 transitionValue1 = std::numeric_limits<UInt64>::max( ) >> 8;
    constexpr UInt64 transitionValue1P1 = transitionValue1 + 1;

    constexpr size_t sizeValueTransition1P1 = SizeOf7BitEncodedValue( transitionValue1P1 );
    constexpr auto bytesValueTransition1P1 = Write7BitEncodedValue<sizeValueTransition1P1>( transitionValue1P1 );
    constexpr auto resultValueTransition1P1 = Read7BitEncodedValue( bytesValueTransition1P1 );
    BOOST_CHECK( transitionValue1P1 == resultValueTransition1P1 );

    constexpr size_t sizeValueTransition1 = SizeOf7BitEncodedValue( transitionValue1 );
    constexpr auto bytesValueTransition1 = Write7BitEncodedValue<sizeValueTransition1>( transitionValue1 );
    constexpr auto resultValueTransition1 = Read7BitEncodedValue( bytesValueTransition1 );
    BOOST_CHECK( transitionValue1 == resultValueTransition1 );


    constexpr UInt64 transitionValue2 = std::numeric_limits<UInt64>::max( ) >> ( 8 + 7 );
    constexpr UInt64 transitionValue2P1 = transitionValue2 + 1;

    constexpr size_t sizeValueTransition2P1 = SizeOf7BitEncodedValue( transitionValue2P1 );
    constexpr auto bytesValueTransition2P1 = Write7BitEncodedValue<sizeValueTransition2P1>( transitionValue2P1 );
    constexpr auto resultValueTransition2P1 = Read7BitEncodedValue( bytesValueTransition2P1 );
    BOOST_CHECK( transitionValue2P1 == resultValueTransition2P1 );

    constexpr size_t sizeValueTransition2 = SizeOf7BitEncodedValue( transitionValue2 );
    constexpr auto bytesValueTransition2 = Write7BitEncodedValue<sizeValueTransition2>( transitionValue2 );
    constexpr auto resultValueTransition2 = Read7BitEncodedValue( bytesValueTransition2 );
    BOOST_CHECK( transitionValue2 == resultValueTransition2 );

    constexpr UInt64 transitionValue3 = std::numeric_limits<UInt64>::max( ) >> ( 8 + 7 + 7 );
    constexpr UInt64 transitionValue3P1 = transitionValue3 + 1;

    constexpr size_t sizeValueTransition3P1 = SizeOf7BitEncodedValue( transitionValue3P1 );
    constexpr auto bytesValueTransition3P1 = Write7BitEncodedValue<sizeValueTransition3P1>( transitionValue3P1 );
    constexpr auto resultValueTransition3P1 = Read7BitEncodedValue( bytesValueTransition3P1 );
    BOOST_CHECK( transitionValue3P1 == resultValueTransition3P1 );

    constexpr size_t sizeValueTransition3 = SizeOf7BitEncodedValue( transitionValue3 );
    constexpr auto bytesValueTransition3 = Write7BitEncodedValue<sizeValueTransition3>( transitionValue3 );
    constexpr auto resultValueTransition3 = Read7BitEncodedValue( bytesValueTransition3 );
    BOOST_CHECK( transitionValue3 == resultValueTransition3 );


    constexpr UInt64 transitionValue4 = std::numeric_limits<UInt64>::max( ) >> ( 8 + 7 + 7 + 7 );
    constexpr UInt64 transitionValue4P1 = transitionValue4 + 1;

    constexpr size_t sizeValueTransition4P1 = SizeOf7BitEncodedValue( transitionValue4P1 );
    constexpr auto bytesValueTransition4P1 = Write7BitEncodedValue<sizeValueTransition4P1>( transitionValue4P1 );
    constexpr auto resultValueTransition4P1 = Read7BitEncodedValue( bytesValueTransition4P1 );
    BOOST_CHECK( transitionValue4P1 == resultValueTransition4P1 );

    constexpr size_t sizeValueTransition4 = SizeOf7BitEncodedValue( transitionValue4 );
    constexpr auto bytesValueTransition4 = Write7BitEncodedValue<sizeValueTransition4>( transitionValue4 );
    constexpr auto resultValueTransition4 = Read7BitEncodedValue( bytesValueTransition4 );
    BOOST_CHECK( transitionValue4 == resultValueTransition4 );

    constexpr UInt64 transitionValue5 = std::numeric_limits<UInt64>::max( ) >> ( 8 + 7 + 7 + 7 + 7 );
    constexpr UInt64 transitionValue5P1 = transitionValue5 + 1;

    constexpr size_t sizeValueTransition5P1 = SizeOf7BitEncodedValue( transitionValue5P1 );
    constexpr auto bytesValueTransition5P1 = Write7BitEncodedValue<sizeValueTransition5P1>( transitionValue5P1 );
    constexpr auto resultValueTransition5P1 = Read7BitEncodedValue( bytesValueTransition5P1 );
    BOOST_CHECK( transitionValue5P1 == resultValueTransition5P1 );

    constexpr size_t sizeValueTransition5 = SizeOf7BitEncodedValue( transitionValue5 );
    constexpr auto bytesValueTransition5 = Write7BitEncodedValue<sizeValueTransition5>( transitionValue5 );
    constexpr auto resultValueTransition5 = Read7BitEncodedValue( bytesValueTransition5 );
    BOOST_CHECK( transitionValue5 == resultValueTransition5 );

    constexpr UInt64 transitionValue6 = std::numeric_limits<UInt64>::max( ) >> ( 8 + 7 + 7 + 7 + 7 + 7 );
    constexpr UInt64 transitionValue6P1 = transitionValue6 + 1;

    constexpr size_t sizeValueTransition6P1 = SizeOf7BitEncodedValue( transitionValue6P1 );
    constexpr auto bytesValueTransition6P1 = Write7BitEncodedValue<sizeValueTransition6P1>( transitionValue6P1 );
    constexpr auto resultValueTransition6P1 = Read7BitEncodedValue( bytesValueTransition6P1 );
    BOOST_CHECK( transitionValue6P1 == resultValueTransition6P1 );

    constexpr size_t sizeValueTransition6 = SizeOf7BitEncodedValue( transitionValue6 );
    constexpr auto bytesValueTransition6 = Write7BitEncodedValue<sizeValueTransition6>( transitionValue6 );
    constexpr auto resultValueTransition6 = Read7BitEncodedValue( bytesValueTransition6 );
    BOOST_CHECK( transitionValue6 == resultValueTransition6 );

    constexpr UInt64 transitionValue7 = std::numeric_limits<UInt64>::max( ) >> ( 8 + 7 + 7 + 7 + 7 + 7 + 7 );
    constexpr UInt64 transitionValue7P1 = transitionValue7 + 1;

    constexpr size_t sizeValueTransition7P1 = SizeOf7BitEncodedValue( transitionValue7P1 );
    constexpr auto bytesValueTransition7P1 = Write7BitEncodedValue<sizeValueTransition7P1>( transitionValue7P1 );
    constexpr auto resultValueTransition7P1 = Read7BitEncodedValue( bytesValueTransition7P1 );
    BOOST_CHECK( transitionValue7P1 == resultValueTransition7P1 );

    constexpr size_t sizeValueTransition7 = SizeOf7BitEncodedValue( transitionValue7 );
    constexpr auto bytesValueTransition7 = Write7BitEncodedValue<sizeValueTransition7>( transitionValue7 );
    constexpr auto resultValueTransition7 = Read7BitEncodedValue( bytesValueTransition7 );
    BOOST_CHECK( transitionValue7 == resultValueTransition7 );

    constexpr UInt64 transitionValue8 = std::numeric_limits<UInt64>::max( ) >> ( 8 + 7 + 7 + 7 + 7 + 7 + 7 + 7 );
    constexpr UInt64 transitionValue8P1 = transitionValue8 + 1;

    constexpr size_t sizeValueTransition8P1 = SizeOf7BitEncodedValue( transitionValue8P1 );
    constexpr auto bytesValueTransition8P1 = Write7BitEncodedValue<sizeValueTransition8P1>( transitionValue8P1 );
    constexpr auto resultValueTransition8P1 = Read7BitEncodedValue( bytesValueTransition8P1 );
    BOOST_CHECK( transitionValue8P1 == resultValueTransition8P1 );

    constexpr size_t sizeValueTransition8 = SizeOf7BitEncodedValue( transitionValue8 );
    constexpr auto bytesValueTransition8 = Write7BitEncodedValue<sizeValueTransition8>( transitionValue8 );
    constexpr auto resultValueTransition8 = Read7BitEncodedValue( bytesValueTransition8 );
    BOOST_CHECK( transitionValue8 == resultValueTransition8 );
}

// --run_test=PersistentTests/ReaderCanReadTest1
BOOST_AUTO_TEST_CASE( ReaderCanReadTest1 )
{
    using ReaderT = IO::BinaryReader<IO::MemoryStream>;
    constexpr auto canReadVector = Persistent::Internal::ReaderCanRead< ReaderT, Vector<SByte> >;
    BOOST_CHECK( canReadVector == true );
    constexpr auto canReadSpan = Persistent::Internal::ReaderCanRead< ReaderT, std::span<SByte> >;
    BOOST_CHECK( canReadSpan == false );
}

// --run_test=PersistentTests/WriterCanWriteTest1
BOOST_AUTO_TEST_CASE( WriterCanWriteTest1 )
{
    using WriterT = IO::BinaryWriter<IO::MemoryStream>;
    constexpr auto canWriteVector = Persistent::Internal::WriterCanWrite< WriterT, Vector<SByte> >;
    BOOST_CHECK( canWriteVector == true );
    constexpr auto canWriteSpan = Persistent::Internal::WriterCanWrite< WriterT, std::span<SByte> >;
    BOOST_CHECK( canWriteSpan == true );
}



// --run_test=PersistentTests/FormatTraitsTest1
BOOST_AUTO_TEST_CASE( FormatTraitsTest1 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Boolean;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<bool>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );
    
    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers();
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest2
BOOST_AUTO_TEST_CASE( FormatTraitsTest2 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Char;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<char>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest3
BOOST_AUTO_TEST_CASE( FormatTraitsTest3 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::SByte;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<SByte>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest4
BOOST_AUTO_TEST_CASE( FormatTraitsTest4 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Byte;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<Byte>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest5
BOOST_AUTO_TEST_CASE( FormatTraitsTest5 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::WChar;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<wchar_t>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest6
BOOST_AUTO_TEST_CASE( FormatTraitsTest6 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Int16;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<Int16>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest7
BOOST_AUTO_TEST_CASE( FormatTraitsTest7 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::UInt16;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<UInt16>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest8
BOOST_AUTO_TEST_CASE( FormatTraitsTest8 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Int32;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<Int32>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest9
BOOST_AUTO_TEST_CASE( FormatTraitsTest9 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::UInt32;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<UInt32>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest10
BOOST_AUTO_TEST_CASE( FormatTraitsTest10 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Int64;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<Int64>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest11
BOOST_AUTO_TEST_CASE( FormatTraitsTest11 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::UInt64;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<UInt64>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest12
BOOST_AUTO_TEST_CASE( FormatTraitsTest12 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Single;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<float>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest13
BOOST_AUTO_TEST_CASE( FormatTraitsTest13 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Double;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<double>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest14
BOOST_AUTO_TEST_CASE( FormatTraitsTest14 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::TimeSpan;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<TimeSpan>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest15
BOOST_AUTO_TEST_CASE( FormatTraitsTest15 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::DateTime;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<DateTime>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest16
BOOST_AUTO_TEST_CASE( FormatTraitsTest16 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Currency;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<Currency>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest17
BOOST_AUTO_TEST_CASE( FormatTraitsTest17 )
{
    constexpr auto expectedTypeId = Types::BasicTypeId::Guid;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::None;
    using FormatTraits = Persistent::Internal::FormatTraits<Guid>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 2 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
}

// --run_test=PersistentTests/FormatTraitsTest18
BOOST_AUTO_TEST_CASE( FormatTraitsTest18 )
{
    constexpr size_t ArraySize = 100;
    constexpr auto expectedTypeId = Types::BasicTypeId::Boolean;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<bool[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 100 uses 1 byte
    BOOST_CHECK( byteSize == 3 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest19
BOOST_AUTO_TEST_CASE( FormatTraitsTest19 )
{
    constexpr size_t ArraySize = 128;
    constexpr auto expectedTypeId = Types::BasicTypeId::Boolean;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<bool[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 128 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest20
BOOST_AUTO_TEST_CASE( FormatTraitsTest20 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Char;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<char[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest21
BOOST_AUTO_TEST_CASE( FormatTraitsTest21 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::SByte;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<SByte[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest22
BOOST_AUTO_TEST_CASE( FormatTraitsTest22 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Byte;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<Byte[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest23
BOOST_AUTO_TEST_CASE( FormatTraitsTest23 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::WChar;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<wchar_t[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest24
BOOST_AUTO_TEST_CASE( FormatTraitsTest24 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Int16;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<Int16[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest25
BOOST_AUTO_TEST_CASE( FormatTraitsTest25 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::UInt16;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<UInt16[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest26
BOOST_AUTO_TEST_CASE( FormatTraitsTest26 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Int32;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<Int32[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest27
BOOST_AUTO_TEST_CASE( FormatTraitsTest27 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::UInt32;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<UInt32[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest28
BOOST_AUTO_TEST_CASE( FormatTraitsTest28 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Int64;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<Int64[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest29
BOOST_AUTO_TEST_CASE( FormatTraitsTest29 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::UInt64;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<UInt64[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest30
BOOST_AUTO_TEST_CASE( FormatTraitsTest30 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Single;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<float[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest31
BOOST_AUTO_TEST_CASE( FormatTraitsTest31 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Double;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<double[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest32
BOOST_AUTO_TEST_CASE( FormatTraitsTest32 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::TimeSpan;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<TimeSpan[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest33
BOOST_AUTO_TEST_CASE( FormatTraitsTest33 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::DateTime;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<DateTime[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest34
BOOST_AUTO_TEST_CASE( FormatTraitsTest34 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Currency;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<Currency[ArraySize]>;

    auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}

// --run_test=PersistentTests/FormatTraitsTest35
BOOST_AUTO_TEST_CASE( FormatTraitsTest35 )
{
    constexpr size_t ArraySize = 2048;
    constexpr auto expectedTypeId = Types::BasicTypeId::Guid;
    constexpr auto expectedModifiers = Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed;
    using FormatTraits = Persistent::Internal::FormatTraits<Guid[ArraySize]>;

    constexpr auto descriptor = FormatTraits::Descriptor;

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );
    // The header uses two bytes, and the 7-bit encoding of 2048 uses 2 bytes
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );
    auto header = cursor.CurrentType( );
    auto isBasicType = header.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = header.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
    auto modifiers = header.Modifiers( );
    BOOST_CHECK( modifiers == expectedModifiers );
    auto arrayOfBasicType = cursor.ReadFixedSizeBasicArrayType( );
    auto fixedSize = arrayOfBasicType.ArraySize( );
    BOOST_CHECK( fixedSize == ArraySize );
}


// --run_test=PersistentTests/FormatTraitsTest36
BOOST_AUTO_TEST_CASE( FormatTraitsTest36 )
{
    using FormatTraits = Persistent::Internal::FormatTraits< Tuple<int,double> >;
    auto descriptor = FormatTraits::Descriptor;
    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );
    
    auto byteSize = cursor.ByteSize( );
    // Expected layout
    //  0 : bytesize of descriptor
    //  1 : number of descriptor elements
    //  2 : TypeId of descriptor element (Tuple)
    //  3 : modifier flags of descritor element (ModifierFlags::None)
    //  4 : bytesize of tuple descriptor
    //  5 : number of descriptor elements of tuple descriptor
    //  6 : TypeId of descriptor element (BasicTypeId::Int32)
    //  7 : modifier flags of descritor element (ModifierFlags::None)
    //  8 : TypeId of descriptor element (BasicTypeId::Double)
    //  9 : modifier flags of descritor element (ModifierFlags::None)
    //
    // Byte size does not include itself or the number of 
    // descriptor elements, so the expected value is 8


    BOOST_CHECK( byteSize == 8 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );

    auto header = cursor.CurrentType( );
    auto isTupleType = header.IsTupleType( );
    BOOST_CHECK( isTupleType == true );

    auto tupleType = cursor.ReadTupleType( );
    auto tupleTypeMemberCount = tupleType.MemberCount( );
    BOOST_CHECK( tupleTypeMemberCount == 2 );

    auto tupleTypeCursor = tupleType.Cursor( );
    auto basicType_0 = tupleTypeCursor.ReadBasicType( );
    auto basicType_0_TypeId = basicType_0.BasicTypeId( );
    BOOST_CHECK( basicType_0_TypeId == Types::BasicTypeId::Int32 );

    auto basicType_1 = tupleTypeCursor.ReadBasicType( );
    auto basicType_1_TypeId = basicType_1.BasicTypeId( );
    BOOST_CHECK( basicType_1_TypeId == Types::BasicTypeId::Double );
}


// --run_test=PersistentTests/FormatTraitsTest37
BOOST_AUTO_TEST_CASE( FormatTraitsTest37 )
{
    using FormatTraits = Persistent::Internal::FormatTraits< Tuple<Tuple<Int32, double>, Tuple<bool, Int64>> >;
    auto descriptor = FormatTraits::Descriptor;
    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );

    auto byteSize = cursor.ByteSize( );


    BOOST_CHECK( byteSize == 20 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );

    auto header = cursor.CurrentType( );
    auto isTupleType = header.IsTupleType( );
    BOOST_CHECK( isTupleType == true );

    auto tupleType = cursor.ReadTupleType( );
    auto tupleTypeMemberCount = tupleType.MemberCount( );
    BOOST_CHECK( tupleTypeMemberCount == 2 );

    auto tupleTypeCursor = tupleType.Cursor( );

    auto tupleType_0 = tupleTypeCursor.ReadTupleType( );
    auto tupleType_0_TypeId = tupleType_0.TupleTypeId( );
    BOOST_CHECK( tupleType_0_TypeId == Types::TupleTypeId::Tuple );
    auto tupleType_0Cursor = tupleType_0.Cursor( );
    auto tupleType_0_BasicType_0 = tupleType_0Cursor.ReadBasicType( );
    BOOST_CHECK( tupleType_0_BasicType_0.IsBasicType( ) );
    BOOST_CHECK( tupleType_0_BasicType_0.BasicTypeId( ) == Types::BasicTypeId::Int32 );

    auto tupleType_0_BasicType_1 = tupleType_0Cursor.ReadBasicType( );
    BOOST_CHECK( tupleType_0_BasicType_1.IsBasicType( ) );
    BOOST_CHECK( tupleType_0_BasicType_1.BasicTypeId( ) == Types::BasicTypeId::Double );

    auto tupleType_1 = tupleTypeCursor.ReadTupleType( );
    auto tupleType_1_TypeId = tupleType_0.TupleTypeId( );
    BOOST_CHECK( tupleType_1_TypeId == Types::TupleTypeId::Tuple );
    auto tupleType_1Cursor = tupleType_1.Cursor( );

    auto tupleType_1_BasicType_0 = tupleType_1Cursor.ReadBasicType( );
    BOOST_CHECK( tupleType_1_BasicType_0.IsBasicType( ) );
    BOOST_CHECK( tupleType_1_BasicType_0.BasicTypeId( ) == Types::BasicTypeId::Boolean );

    auto tupleType_1_BasicType_1 = tupleType_1Cursor.ReadBasicType( );
    BOOST_CHECK( tupleType_1_BasicType_1.IsBasicType( ) );
    BOOST_CHECK( tupleType_1_BasicType_1.BasicTypeId( ) == Types::BasicTypeId::Int64 );

}

// --run_test=PersistentTests/DescriptorTest1
BOOST_AUTO_TEST_CASE( DescriptorTest1 )
{
    auto descriptor = Persistent::Descriptor( );
    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );
    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 4 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );

    auto typeList = cursor.ReadTypeListType( );
    auto typeListCursor = typeList.Cursor( );
    auto typeListCursorCount = typeListCursor.Size( );
    BOOST_CHECK( typeListCursorCount == 0 );


}

// --run_test=PersistentTests/DescriptorTest2
BOOST_AUTO_TEST_CASE( DescriptorTest2 )
{
    constexpr bool boolValue = true;
    auto descriptor = Persistent::Descriptor( boolValue );
    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );
    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 6 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );

    auto typeList = cursor.ReadTypeListType( );
    auto typeListCursor = typeList.Cursor( );
    auto typeListCursorCount = typeListCursor.Size( );
    BOOST_CHECK( typeListCursorCount == 1 );
    auto typeListCursor_Type0 = typeListCursor.ReadBasicType( );
    BOOST_CHECK( typeListCursor_Type0.IsBasicType( ) );
    BOOST_CHECK( typeListCursor_Type0.BasicTypeId( ) == Types::BasicTypeId::Boolean );
}

// --run_test=PersistentTests/DescriptorTest3
BOOST_AUTO_TEST_CASE( DescriptorTest3 )
{
    bool boolValue = true;
    double doubleValue = 1.0;
    auto descriptor = Persistent::Descriptor( boolValue, doubleValue );
    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );
    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 8 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );

    auto typeList = cursor.ReadTypeListType( );
    auto typeListCursor = typeList.Cursor( );
    auto typeListCursorCount = typeListCursor.Size( );
    BOOST_CHECK( typeListCursorCount == 2 );

    BOOST_CHECK( typeListCursor.IsBasicType( ) && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto typeListCursor_Type0 = typeListCursor.ReadBasicType( );
    BOOST_CHECK( typeListCursor_Type0.IsBasicType( ) );
    BOOST_CHECK( typeListCursor_Type0.BasicTypeId( ) == Types::BasicTypeId::Boolean );

    BOOST_CHECK( typeListCursor.IsBasicType( ) && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto typeListCursor_Type1 = typeListCursor.ReadBasicType( );
    BOOST_CHECK( typeListCursor_Type1.IsBasicType( ) );
    BOOST_CHECK( typeListCursor_Type1.BasicTypeId( ) == Types::BasicTypeId::Double );

}


// --run_test=PersistentTests/DescriptorTest4
BOOST_AUTO_TEST_CASE( DescriptorTest4 )
{
    bool boolValue = true;
    double doubleValue = 1.0;
    Tuple tuple( static_cast<Int16>(2), static_cast<Int64>( 3 ) );

    auto descriptor = Persistent::Descriptor( boolValue, doubleValue, tuple );
    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );
    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 16 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );

    auto typeList = cursor.ReadTypeListType( );
    auto typeListCursor = typeList.Cursor( );
    auto typeListCursorCount = typeListCursor.Size( );
    BOOST_CHECK( typeListCursorCount == 3 );

    BOOST_CHECK( typeListCursor.IsBasicType( ) && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto typeListCursor_Type0 = typeListCursor.ReadBasicType( );
    BOOST_CHECK( typeListCursor_Type0.IsBasicType( ) );
    BOOST_CHECK( typeListCursor_Type0.BasicTypeId( ) == Types::BasicTypeId::Boolean );

    BOOST_CHECK( typeListCursor.IsBasicType( ) && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto typeListCursor_Type1 = typeListCursor.ReadBasicType( );
    BOOST_CHECK( typeListCursor_Type1.IsBasicType( ) );
    BOOST_CHECK( typeListCursor_Type1.BasicTypeId( ) == Types::BasicTypeId::Double );

    BOOST_CHECK( typeListCursor.IsTupleType( ) && typeListCursor.TupleTypeId( ) == Types::TupleTypeId::Tuple && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto tupleType = typeListCursor.ReadTupleType( );
    auto tupleTypeCursor = tupleType.Cursor( );

    auto tupleTypeCursorIsBasicType = tupleTypeCursor.IsBasicType( );

    BOOST_CHECK( tupleTypeCursor.IsBasicType() && IsNotSet( tupleTypeCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto tupleTypeCursor_Type0 = tupleTypeCursor.ReadBasicType( );
    BOOST_CHECK( tupleTypeCursor_Type0.BasicTypeId( ) == Types::BasicTypeId::Int16 );

    auto tupleTypeCursor_Type1 = tupleTypeCursor.ReadBasicType( );
    BOOST_CHECK( tupleTypeCursor_Type1.BasicTypeId( ) == Types::BasicTypeId::Int64 );
}

// --run_test=PersistentTests/DescriptorTest5
BOOST_AUTO_TEST_CASE( DescriptorTest5 )
{
    bool boolValue = true;
    double doubleValue = 1.0;
    Tuple tuple( static_cast<Int16>( 2 ), static_cast<Int64>( 3 ) );
    DateTime dateTimeValue = DateTime::Now();

    constexpr auto descriptor = Persistent::Descriptor( boolValue, doubleValue, tuple, dateTimeValue );

    Persistent::TypeDescriptorCursor cursor( (const Byte*)&descriptor );
    auto byteSize = cursor.ByteSize( );
    BOOST_CHECK( byteSize == 18 );
    auto size = cursor.Size( );
    BOOST_CHECK( size == 1 );

    auto typeList = cursor.ReadTypeListType( );
    auto typeListCursor = typeList.Cursor( );
    auto typeListCursorCount = typeListCursor.Size( );
    BOOST_CHECK( typeListCursorCount == 4 );

    BOOST_CHECK( typeListCursor.IsBasicType( ) && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto typeListCursor_Type0 = typeListCursor.ReadBasicType( );
    BOOST_CHECK( typeListCursor_Type0.IsBasicType( ) );
    BOOST_CHECK( typeListCursor_Type0.BasicTypeId( ) == Types::BasicTypeId::Boolean );

    BOOST_CHECK( typeListCursor.IsBasicType( ) && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto typeListCursor_Type1 = typeListCursor.ReadBasicType( );
    BOOST_CHECK( typeListCursor_Type1.IsBasicType( ) );
    BOOST_CHECK( typeListCursor_Type1.BasicTypeId( ) == Types::BasicTypeId::Double );

    BOOST_CHECK( typeListCursor.IsTupleType( ) && typeListCursor.TupleTypeId( ) == Types::TupleTypeId::Tuple && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto tupleType = typeListCursor.ReadTupleType( );
    auto tupleTypeCursor = tupleType.Cursor( );

    BOOST_CHECK( tupleTypeCursor.IsBasicType( ) && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto tupleTypeCursor_Type0 = tupleTypeCursor.ReadBasicType( );
    BOOST_CHECK( tupleTypeCursor_Type0.BasicTypeId( ) == Types::BasicTypeId::Int16 );

    auto tupleTypeCursor_Type1 = tupleTypeCursor.ReadBasicType( );
    BOOST_CHECK( tupleTypeCursor_Type1.BasicTypeId( ) == Types::BasicTypeId::Int64 );

    BOOST_CHECK( typeListCursor.IsBasicType( ) && IsNotSet( typeListCursor.Modifiers( ), Persistent::ModifierFlags::Array ) );
    auto typeListCursor_Type4 = typeListCursor.ReadBasicType( );
    BOOST_CHECK( typeListCursor_Type4.BasicTypeId( ) == Types::BasicTypeId::DateTime );

}

// --run_test=PersistentTests/WriteTest1
BOOST_AUTO_TEST_CASE( WriteTest1 )
{
    bool boolValue = true;
    constexpr auto descriptor = Persistent::Descriptor( boolValue );
    constexpr auto isFixedSize = Persistent::IsFixedSize( boolValue );
    constexpr auto bufferSize = Persistent::BufferSize( boolValue );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayReader( &buffer );
    Persistent::Write( arrayReader, boolValue );
    auto bufferValue = buffer.Read<bool>( 0 );
    BOOST_CHECK( bufferValue == boolValue );
}

// --run_test=PersistentTests/WriteTest2
BOOST_AUTO_TEST_CASE( WriteTest2 )
{
    bool arg_1 = true;
    Int16 arg_2 = 10;
    Int64 arg_3 = 20;
    Int32 arg_4 = 30;
    constexpr auto descriptor = Persistent::Descriptor( arg_1, arg_2, arg_3, arg_4 );
    constexpr auto isFixedSize = Persistent::IsFixedSize( arg_1, arg_2, arg_3, arg_4 );
    constexpr auto bufferSize = Persistent::BufferSize( arg_1, arg_2, arg_3, arg_4 );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayReader( &buffer );
    Persistent::Write( arrayReader, arg_1, arg_2, arg_3, arg_4 );
    
    auto bufferValue_1 = buffer.Read<bool>( 0 );
    BOOST_CHECK( bufferValue_1 == arg_1 );
    
    auto bufferValue_2 = buffer.Read<Int16>( 1 );
    BOOST_CHECK( bufferValue_2 == arg_2 );

    auto bufferValue_3 = buffer.Read<Int64>( 3 );
    BOOST_CHECK( bufferValue_3 == arg_3 );

    auto bufferValue_4 = buffer.Read<Int32>( 11 );
    BOOST_CHECK( bufferValue_4 == arg_4 );

}

// --run_test=PersistentTests/ReadTest1
BOOST_AUTO_TEST_CASE( ReadTest1 )
{
    bool boolValue = true;
    constexpr auto descriptor = Persistent::Descriptor( boolValue );
    constexpr auto isFixedSize = Persistent::IsFixedSize( boolValue );
    constexpr auto bufferSize = Persistent::BufferSize( boolValue );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, boolValue );

    bool bufferValue = false;
    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, bufferValue );

    BOOST_CHECK( bufferValue == boolValue );
}


// --run_test=PersistentTests/ReadTest2
BOOST_AUTO_TEST_CASE( ReadTest2 )
{
    bool arg_1 = true;
    Int16 arg_2 = 10;
    Int64 arg_3 = 20;
    Int32 arg_4 = 30;
    constexpr auto descriptor = Persistent::Descriptor( arg_1, arg_2, arg_3, arg_4 );
    constexpr auto isFixedSize = Persistent::IsFixedSize( arg_1, arg_2, arg_3, arg_4 );
    constexpr auto bufferSize = Persistent::BufferSize( arg_1, arg_2, arg_3, arg_4 );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg_1, arg_2, arg_3, arg_4 );


    bool value_1 = false;
    Int16 value_2 = 0;
    Int64 value_3 = 0;
    Int32 value_4 = 0;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value_1, value_2, value_3, value_4 );

    BOOST_CHECK( value_1 == arg_1 );
    BOOST_CHECK( value_2 == arg_2 );
    BOOST_CHECK( value_3 == arg_3 );
    BOOST_CHECK( value_4 == arg_4 );

}


// --run_test=PersistentTests/ReadTest3
BOOST_AUTO_TEST_CASE( ReadTest3 )
{
    using Type = char;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest4
BOOST_AUTO_TEST_CASE( ReadTest4 )
{
    using Type = SByte;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest5
BOOST_AUTO_TEST_CASE( ReadTest5 )
{
    using Type = Byte;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest6
BOOST_AUTO_TEST_CASE( ReadTest6 )
{
    using Type = wchar_t;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest7
BOOST_AUTO_TEST_CASE( ReadTest7 )
{
    using Type = Int16;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest8
BOOST_AUTO_TEST_CASE( ReadTest8 )
{
    using Type = UInt16;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest9
BOOST_AUTO_TEST_CASE( ReadTest9 )
{
    using Type = Int32;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest10
BOOST_AUTO_TEST_CASE( ReadTest10 )
{
    using Type = UInt32;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest11
BOOST_AUTO_TEST_CASE( ReadTest11 )
{
    using Type = long;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest12
BOOST_AUTO_TEST_CASE( ReadTest12 )
{
    using Type = unsigned long;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest13
BOOST_AUTO_TEST_CASE( ReadTest13 )
{
    using Type = Int64;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest14
BOOST_AUTO_TEST_CASE( ReadTest14 )
{
    using Type = UInt64;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest15
BOOST_AUTO_TEST_CASE( ReadTest15 )
{
    using Type = float;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest16
BOOST_AUTO_TEST_CASE( ReadTest16 )
{
    using Type = double;
    constexpr Type expectedValue = 10;
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest17
BOOST_AUTO_TEST_CASE( ReadTest17 )
{
    using Type = TimeSpan;
    constexpr Type expectedValue( 10 );
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest18
BOOST_AUTO_TEST_CASE( ReadTest18 )
{
    using Type = DateTime;
    constexpr Type expectedValue( 10LL );
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest19
BOOST_AUTO_TEST_CASE( ReadTest19 )
{
    using Type = Currency;
    constexpr Type expectedValue( 10LL );
    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest20
BOOST_AUTO_TEST_CASE( ReadTest20 )
{
    using Type = Guid;
    // {DD1B292C-DE26-4FB2-BA25-132EB2FE488E}
    constexpr Type expectedValue( 0xdd1b292c, 0xde26, 0x4fb2, 0xba, 0x25, 0x13, 0x2e, 0xb2, 0xfe, 0x48, 0x8e );

    Type arg = expectedValue;

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value{};

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    BOOST_CHECK( value == arg );
}

// --run_test=PersistentTests/ReadTest21
BOOST_AUTO_TEST_CASE( ReadTest21 )
{
    using Type = bool;
    constexpr size_t ItemCount = 2;
    
    constexpr Type expectedValue[ItemCount] = { true , false };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );
    

    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest22
BOOST_AUTO_TEST_CASE( ReadTest22 )
{
    using Type = char;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest23
BOOST_AUTO_TEST_CASE( ReadTest23 )
{
    using Type = SByte;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest24
BOOST_AUTO_TEST_CASE( ReadTest24 )
{
    using Type = Byte;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest25
BOOST_AUTO_TEST_CASE( ReadTest25 )
{
    using Type = wchar_t;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest26
BOOST_AUTO_TEST_CASE( ReadTest26 )
{
    using Type = Int16;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest27
BOOST_AUTO_TEST_CASE( ReadTest27 )
{
    using Type = UInt16;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest28
BOOST_AUTO_TEST_CASE( ReadTest28 )
{
    using Type = Int32;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest29
BOOST_AUTO_TEST_CASE( ReadTest29 )
{
    using Type = UInt32;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest30
BOOST_AUTO_TEST_CASE( ReadTest30 )
{
    using Type = long;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest31
BOOST_AUTO_TEST_CASE( ReadTest31 )
{
    using Type = unsigned long;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest32
BOOST_AUTO_TEST_CASE( ReadTest32 )
{
    using Type = Int64;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest33
BOOST_AUTO_TEST_CASE( ReadTest33 )
{
    using Type = UInt64;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest34
BOOST_AUTO_TEST_CASE( ReadTest34 )
{
    using Type = float;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest35
BOOST_AUTO_TEST_CASE( ReadTest35 )
{
    using Type = double;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue[ItemCount] = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest36
BOOST_AUTO_TEST_CASE( ReadTest36 )
{
    using Type = TimeSpan;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue_1( 10 );
    constexpr Type expectedValue_2( 20 );

    constexpr Type expectedValue[ItemCount] = { expectedValue_1,expectedValue_2 };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest37
BOOST_AUTO_TEST_CASE( ReadTest37 )
{
    using Type = DateTime;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue_1( 10LL );
    constexpr Type expectedValue_2( 20LL );

    constexpr Type expectedValue[ItemCount] = { expectedValue_1,expectedValue_2 };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest38
BOOST_AUTO_TEST_CASE( ReadTest38 )
{
    using Type = Currency;
    constexpr size_t ItemCount = 2;

    constexpr Type expectedValue_1( 10 );
    constexpr Type expectedValue_2( 20 );

    constexpr Type expectedValue[ItemCount] = { expectedValue_1,expectedValue_2 };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest39
BOOST_AUTO_TEST_CASE( ReadTest39 )
{
    using Type = Guid;
    constexpr size_t ItemCount = 2;

    // {DD1B292C-DE26-4FB2-BA25-132EB2FE488E}
    constexpr Type expectedValue_1( 0xdd1b292c, 0xde26, 0x4fb2, 0xba, 0x25, 0x13, 0x2e, 0xb2, 0xfe, 0x48, 0x8e );
    // {7B719B96-2332-437C-9822-B0495539B23E}
    constexpr Type expectedValue_2( 0x7b719b96, 0x2332, 0x437c, 0x98, 0x22, 0xb0, 0x49, 0x55, 0x39, 0xb2, 0x3e );

    constexpr Type expectedValue[ItemCount] = { expectedValue_1,expectedValue_2 };

    Type arg[ItemCount];
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    Type value[ItemCount];

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest40
BOOST_AUTO_TEST_CASE( ReadTest40 )
{
    using Type_1 = Byte;
    constexpr Type_1 expectedValue_1 = static_cast<Type_1>(10);

    using Type_2 = Guid;
    constexpr size_t ItemCount = 2;

    // {DD1B292C-DE26-4FB2-BA25-132EB2FE488E}
    constexpr Type_2 expectedValue_2_1( 0xdd1b292c, 0xde26, 0x4fb2, 0xba, 0x25, 0x13, 0x2e, 0xb2, 0xfe, 0x48, 0x8e );
    // {7B719B96-2332-437C-9822-B0495539B23E}
    constexpr Type_2 expectedValue_2_2( 0x7b719b96, 0x2332, 0x437c, 0x98, 0x22, 0xb0, 0x49, 0x55, 0x39, 0xb2, 0x3e );
    constexpr Type_2 expectedValue_2[ItemCount] = { expectedValue_2_1,expectedValue_2_2 };

    using Type_3 = float;
    constexpr Type_3 expectedValue_3 = static_cast<Type_1>( 20 );

    Type_1 arg_1 = expectedValue_1;

    Type_2 arg_2[ItemCount];
    std::copy( std::begin( expectedValue_2 ), std::end( expectedValue_2 ), std::begin( arg_2 ) );

    Type_3 arg_3 = expectedValue_3;


    constexpr auto bufferSize = Persistent::BufferSize( arg_1, arg_2, arg_3 );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg_1, arg_2, arg_3 );

    Type_1 value_1 = static_cast<Type_1>( 0 );

    Type_2 value_2[ItemCount];

    Type_3 value_3 = static_cast<Type_3>( 0 );


    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value_1, value_2, value_3 );

    BOOST_CHECK( value_1 == expectedValue_1 );

    bool asExpected = std::equal( std::begin( expectedValue_2 ), std::end( expectedValue_2 ), std::begin( value_2 ) );
    BOOST_CHECK( asExpected );

    BOOST_CHECK( value_3 == expectedValue_3 );

}


// --run_test=PersistentTests/ReadTest41
BOOST_AUTO_TEST_CASE( ReadTest41 )
{
    using Type = bool;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { true, false };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest42
BOOST_AUTO_TEST_CASE( ReadTest42 )
{
    using Type = char;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest43
BOOST_AUTO_TEST_CASE( ReadTest43 )
{
    using Type = SByte;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest44
BOOST_AUTO_TEST_CASE( ReadTest44 )
{
    using Type = Byte;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest45
BOOST_AUTO_TEST_CASE( ReadTest45 )
{
    using Type = wchar_t;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest46
BOOST_AUTO_TEST_CASE( ReadTest46 )
{
    using Type = Int16;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest47
BOOST_AUTO_TEST_CASE( ReadTest47 )
{
    using Type = UInt16;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest48
BOOST_AUTO_TEST_CASE( ReadTest48 )
{
    using Type = Int32;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest49
BOOST_AUTO_TEST_CASE( ReadTest49 )
{
    using Type = UInt32;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest50
BOOST_AUTO_TEST_CASE( ReadTest50 )
{
    using Type = long;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest51
BOOST_AUTO_TEST_CASE( ReadTest51 )
{
    using Type = unsigned long;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest52
BOOST_AUTO_TEST_CASE( ReadTest52 )
{
    using Type = Int64;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest53
BOOST_AUTO_TEST_CASE( ReadTest53 )
{
    using Type = UInt64;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest54
BOOST_AUTO_TEST_CASE( ReadTest54 )
{
    using Type = float;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest55
BOOST_AUTO_TEST_CASE( ReadTest55 )
{
    using Type = double;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest56
BOOST_AUTO_TEST_CASE( ReadTest56 )
{
    using Type = TimeSpan;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { Type( 10 ), Type( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest57
BOOST_AUTO_TEST_CASE( ReadTest57 )
{
    using Type = DateTime;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { Type( 10LL ), Type( 20LL ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest58
BOOST_AUTO_TEST_CASE( ReadTest58 )
{
    using Type = Currency;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    constexpr ArrayType expectedValue = { Type( 10 ), Type( 20 ) };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest59
BOOST_AUTO_TEST_CASE( ReadTest59 )
{
    using Type = Guid;
    constexpr size_t ItemCount = 2;
    using ArrayType = std::array<Type, ItemCount>;

    // {DD1B292C-DE26-4FB2-BA25-132EB2FE488E}
    constexpr Type expectedValue_1( 0xdd1b292c, 0xde26, 0x4fb2, 0xba, 0x25, 0x13, 0x2e, 0xb2, 0xfe, 0x48, 0x8e );
    // {7B719B96-2332-437C-9822-B0495539B23E}
    constexpr Type expectedValue_2( 0x7b719b96, 0x2332, 0x437c, 0x98, 0x22, 0xb0, 0x49, 0x55, 0x39, 0xb2, 0x3e );

    constexpr ArrayType expectedValue = { expectedValue_1, expectedValue_1 };

    ArrayType arg;
    std::copy( std::begin( expectedValue ), std::end( expectedValue ), std::begin( arg ) );


    constexpr auto bufferSize = Persistent::BufferSize( arg );
    ByteArray<bufferSize> buffer;
    ArrayWriter<bufferSize> arrayWriter( &buffer );
    Persistent::Write( arrayWriter, arg );

    ArrayType value;

    ArrayReader<bufferSize> arrayReader( &buffer );
    Persistent::Read( arrayReader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest60
BOOST_AUTO_TEST_CASE( ReadTest60 )
{
    using Type = char;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest61
BOOST_AUTO_TEST_CASE( ReadTest61 )
{
    using Type = SByte;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest62
BOOST_AUTO_TEST_CASE( ReadTest62 )
{
    using Type = Byte;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest63
BOOST_AUTO_TEST_CASE( ReadTest63 )
{
    using Type = wchar_t;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest64
BOOST_AUTO_TEST_CASE( ReadTest64 )
{
    using Type = Int16;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest65
BOOST_AUTO_TEST_CASE( ReadTest65 )
{
    using Type = UInt16;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest66
BOOST_AUTO_TEST_CASE( ReadTest66 )
{
    using Type = Int32;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest67
BOOST_AUTO_TEST_CASE( ReadTest67 )
{
    using Type = UInt32;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest68
BOOST_AUTO_TEST_CASE( ReadTest68 )
{
    using Type = long;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest69
BOOST_AUTO_TEST_CASE( ReadTest69 )
{
    using Type = unsigned long;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest70
BOOST_AUTO_TEST_CASE( ReadTest70 )
{
    using Type = Int64;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest71
BOOST_AUTO_TEST_CASE( ReadTest71 )
{
    using Type = UInt64;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest72
BOOST_AUTO_TEST_CASE( ReadTest72 )
{
    using Type = float;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest73
BOOST_AUTO_TEST_CASE( ReadTest73 )
{
    using Type = double;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;

    VectorType expectedValue = { static_cast<Type>( 10 ),static_cast<Type>( 20 ) };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest74
BOOST_AUTO_TEST_CASE( ReadTest74 )
{
    using Type = TimeSpan;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;
    Type expectedValue_1( 10 );
    Type expectedValue_2( 20 );


    VectorType expectedValue = { expectedValue_1,expectedValue_2 };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest75
BOOST_AUTO_TEST_CASE( ReadTest75 )
{
    using Type = DateTime;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;
    Type expectedValue_1( 10LL );
    Type expectedValue_2( 20LL );


    VectorType expectedValue = { expectedValue_1,expectedValue_2 };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest76
BOOST_AUTO_TEST_CASE( ReadTest76 )
{
    using Type = Currency;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;
    Type expectedValue_1( 10 );
    Type expectedValue_2( 20 );


    VectorType expectedValue = { expectedValue_1,expectedValue_2 };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest77
BOOST_AUTO_TEST_CASE( ReadTest77 )
{
    using Type = Guid;
    constexpr size_t ItemCount = 2;
    using VectorType = std::vector<Type>;
    // {DD1B292C-DE26-4FB2-BA25-132EB2FE488E}
    constexpr Type expectedValue_1( 0xdd1b292c, 0xde26, 0x4fb2, 0xba, 0x25, 0x13, 0x2e, 0xb2, 0xfe, 0x48, 0x8e );
    // {7B719B96-2332-437C-9822-B0495539B23E}
    constexpr Type expectedValue_2( 0x7b719b96, 0x2332, 0x437c, 0x98, 0x22, 0xb0, 0x49, 0x55, 0x39, 0xb2, 0x3e );


    VectorType expectedValue = { expectedValue_1,expectedValue_2 };
    VectorType arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    VectorType value;

    Persistent::Read( reader, value );

    bool asExpected = std::equal( std::begin( expectedValue ), std::end( expectedValue ), std::begin( value ) );

    BOOST_CHECK( asExpected );
}


// --run_test=PersistentTests/ReadTest78
BOOST_AUTO_TEST_CASE( ReadTest78 )
{
    using Type = Tuple<bool>;

    Type expectedValue( true );
    Type arg( true );

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    Type value( false );

    Persistent::Read( reader, value );

    bool asExpected = get<0>( expectedValue ) == get<0>( value );

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest79
BOOST_AUTO_TEST_CASE( ReadTest79 )
{
    using Type = std::pair<Byte,double>;

    Type expectedValue( 10, 20.0 );
    Type arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    Type value( 0, 0.0 );

    Persistent::Read( reader, value );

    bool asExpected = expectedValue == value;

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest80
BOOST_AUTO_TEST_CASE( ReadTest80 )
{
    using Type = std::tuple<Byte, double>;

    Type expectedValue( 10, 20.0 );
    Type arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    Type value( 0, 0.0 );

    Persistent::Read( reader, value );

    bool asExpected = expectedValue == value;

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest81
BOOST_AUTO_TEST_CASE( ReadTest81 )
{
    using Type = std::string;

    Type expectedValue( "Hello" );
    Type arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    Type value;

    Persistent::Read( reader, value );

    bool asExpected = expectedValue == value;

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest82
BOOST_AUTO_TEST_CASE( ReadTest82 )
{
    using Type = std::wstring;

    Type expectedValue( L"Hello" );
    Type arg = expectedValue;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    Type value;

    Persistent::Read( reader, value );

    bool asExpected = expectedValue == value;

    BOOST_CHECK( asExpected );
}

// --run_test=PersistentTests/ReadTest83
BOOST_AUTO_TEST_CASE( ReadTest83 )
{
    using Type_1 = std::string;
    using Type_2 = std::tuple<Byte, double>;

    Type_1 expectedValue_1( "Hello" );
    Type_1 arg_1 = expectedValue_1;

    Type_2 expectedValue_2( 10, 20.0 );
    Type_2 arg_2 = expectedValue_2;


    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg_1, arg_2 );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    Type_1 value_1;
    Type_2 value_2( 0, 0.0 );

    Persistent::Read( reader, value_1, value_2 );

    bool asExpected_1 = expectedValue_1 == value_1;
    bool asExpected_2 = expectedValue_2 == value_2;

    BOOST_CHECK( asExpected_1 );
    BOOST_CHECK( asExpected_2 );
}

// --run_test=PersistentTests/ReadTest84
BOOST_AUTO_TEST_CASE( ReadTest84 )
{
    using Type_1 = std::string;
    using Type_2 = std::tuple<Byte, double>;
    using Type_3 = std::vector<std::tuple<DateTime, UInt32, double>>;

    Type_1 expectedValue_1( "Hello" );
    Type_1 arg_1 = expectedValue_1;

    Type_2 expectedValue_2( 10, 20.0 );
    Type_2 arg_2 = expectedValue_2;

    Type_3 expectedValue_3;
    expectedValue_3.emplace_back( DateTime( 1LL ), 0, 1.0 );
    expectedValue_3.emplace_back( DateTime( 2LL ), 0, 2.0 );
    expectedValue_3.emplace_back( DateTime( 3LL ), 0, 3.0 );
    Type_3 arg_3 = expectedValue_3;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg_1, arg_2, arg_3 );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    Type_1 value_1;
    Type_2 value_2( 0, 0.0 );
    Type_3 value_3;

    Persistent::Read( reader, value_1, value_2, value_3 );

    bool asExpected_1 = expectedValue_1 == value_1;
    bool asExpected_2 = expectedValue_2 == value_2;
    bool asExpected_3 = expectedValue_3 == value_3;

    BOOST_CHECK( asExpected_1 );
    BOOST_CHECK( asExpected_2 );
    BOOST_CHECK( asExpected_3 );
}

// --run_test=PersistentTests/ReadTest85
BOOST_AUTO_TEST_CASE( ReadTest85 )
{
    using Type_1 = std::string;
    using Type_2 = std::tuple<Byte, double>;
    using Type_3 = std::vector<std::tuple<DateTime, UInt32, double>>;

    Type_1 expectedValue_1( "Hello" );
    Type_1 arg_1 = expectedValue_1;

    Type_2 expectedValue_2( 10, 20.0 );
    Type_2 arg_2 = expectedValue_2;

    Type_3 expectedValue_3;
    expectedValue_3.emplace_back( DateTime( 1LL ), 0, 1.0 );
    expectedValue_3.emplace_back( DateTime( 2LL ), 0, 2.0 );
    expectedValue_3.emplace_back( DateTime( 3LL ), 0, 3.0 );
    Type_3 arg_3 = expectedValue_3;

    IO::MemoryStream stream;
    IO::BinaryWriter writer( stream );
    Persistent::Write( writer, arg_1, arg_2, arg_3 );

    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    Type_1 value_1;
    Type_2 value_2( 0, 0.0 );
    Type_3 value_3;

    Persistent::Read( reader, value_1, value_2, value_3 );

    bool asExpected_1 = expectedValue_1 == value_1;
    bool asExpected_2 = expectedValue_2 == value_2;
    bool asExpected_3 = expectedValue_3 == value_3;

    BOOST_CHECK( asExpected_1 );
    BOOST_CHECK( asExpected_2 );
    BOOST_CHECK( asExpected_3 );
}

// --run_test=PersistentTests/FormatTupleTest1
BOOST_AUTO_TEST_CASE( FormatTupleTest1 )
{
    using Int32FormatType = Tuple<Types::BasicTypeId, Persistent::ModifierFlags>;
    using DoubleFormatType = Tuple<Types::BasicTypeId, Persistent::ModifierFlags>;

    constexpr auto sizeofInt32FormatType = sizeof( Int32FormatType );
    BOOST_CHECK( sizeofInt32FormatType == 2 );

    constexpr auto sizeofDoubleFormatType = sizeof( DoubleFormatType );
    BOOST_CHECK( sizeofInt32FormatType == 2 );

    Int32FormatType int32Format( Types::BasicTypeId::Int32, Persistent::ModifierFlags::None );
    DoubleFormatType doubleFormat( Types::BasicTypeId::Double, Persistent::ModifierFlags::None );

    auto valuesFormat = TupleCat( int32Format, doubleFormat );
    using ValuesFormatType = decltype( valuesFormat );
    constexpr auto sizeofValuesFormatType = sizeof( ValuesFormatType );
    BOOST_CHECK( sizeofValuesFormatType == 4 );

    auto tupleFormatHeaderByteSizeAndCount = MakeTuple( Types::TupleTypeId::Tuple, Persistent::ModifierFlags::None, Persistent::Internal::SevenBitEncodedValue<sizeofValuesFormatType>::value, Persistent::Internal::SevenBitEncodedValue<2>::value );
    using TupleFormatHeaderByteSizeAndCountType = decltype( tupleFormatHeaderByteSizeAndCount );
    constexpr auto sizeofTupleFormatHeaderByteSizeAndCountType = sizeof( TupleFormatHeaderByteSizeAndCountType );
    BOOST_CHECK( sizeofTupleFormatHeaderByteSizeAndCountType == 4 );
}

// --run_test=PersistentTests/FormatTupleTest2
BOOST_AUTO_TEST_CASE( FormatTupleTest2 )
{
    using TraitsType = Persistent::Internal::FormatTraits< Tuple<> >;
    constexpr auto format = TraitsType::Format;
}






BOOST_AUTO_TEST_SUITE_END( )