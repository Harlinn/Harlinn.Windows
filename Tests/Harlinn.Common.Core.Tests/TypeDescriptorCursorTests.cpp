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




    class TimeseriesPoint
    {
        DateTime timestamp_;
        UInt64 flags_;
        double value_;
    public:
        // TypeList *must* contain a parameter pack that can be used
        // to instantiate a Tuple<...> that must be binary compatible
        // with TimeseriesPoint.
        using TypeList = Core::TypeList<DateTime, UInt64, double>;
        constexpr TimeseriesPoint( ) noexcept
            : flags_( 0 ), value_( 0 )
        {
        }

        constexpr TimeseriesPoint( DateTime timestamp, double value ) noexcept
            : timestamp_( timestamp ), flags_( 0 ), value_( value )
        {
        }
        constexpr TimeseriesPoint( DateTime timestamp, UInt64 flags, double value ) noexcept
            : timestamp_( timestamp ), flags_( flags ), value_( value )
        {
        }

        constexpr void Assign( DateTime timestamp, double value ) noexcept
        {
            timestamp_ = timestamp;
            flags_ = 0;
            value_ = value;
        }
        constexpr void Assign( DateTime timestamp, UInt64 flags, double value ) noexcept
        {
            timestamp_ = timestamp;
            flags_ = flags;
            value_ = value;
        }

        constexpr DateTime Timestamp( ) const noexcept
        {
            return timestamp_;
        }
        constexpr UInt64 Flags( ) const noexcept
        {
            return flags_;
        }
        constexpr double Value( ) const noexcept
        {
            return value_;
        }

        auto operator<=>( const TimeseriesPoint& ) const = default;
    };
}


BOOST_FIXTURE_TEST_SUITE( TypeDescriptorCursorTests, LocalFixture )


// --run_test=TypeDescriptorCursorTests/EmptyTest1
BOOST_AUTO_TEST_CASE( EmptyTest1 )
{

    constexpr auto descriptor = Persistent::Descriptor( );

    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorSize = rootDescriptorCursor.Size( );
    BOOST_CHECK( rootDescriptorCursorSize == 1 );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );

    auto typelistCursorSize = typelistCursor.Size( );
    BOOST_CHECK( typelistCursorSize == 0 );
    auto typelistCursorIsValid = typelistCursor.IsValid( );
    BOOST_CHECK( typelistCursorIsValid == false );
}


// --run_test=TypeDescriptorCursorTests/BasicTypeTest1
BOOST_AUTO_TEST_CASE( BasicTypeTest1 )
{
    using ArgType1 = bool;
    constexpr Types::BasicTypeId expectedTypeId = Types::BasicTypeId::Boolean;
    constexpr ArgType1 arg1 = true;

    constexpr auto descriptor = Persistent::Descriptor( arg1 );

    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    bool rootDescriptorCursorIsTypeList = rootDescriptorCursor.IsTypeListType( );
    BOOST_CHECK( rootDescriptorCursorIsTypeList == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );
    bool isBasicType = typelistCursor.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto typeId = typelistCursor.BasicTypeId( );
    BOOST_CHECK( typeId == expectedTypeId );
}


// --run_test=TypeDescriptorCursorTests/BasicTupleTypeTest1
BOOST_AUTO_TEST_CASE( BasicTupleTypeTest1 )
{
    using ArgType1 = Tuple<>;
    constexpr ArgType1 arg1;

    constexpr auto descriptor = Persistent::Descriptor( arg1 );

    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    bool rootDescriptorCursorIsTypeList = rootDescriptorCursor.IsTypeListType( );
    BOOST_CHECK( rootDescriptorCursorIsTypeList == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );
    bool isTupleType = typelistCursor.IsTupleType( );
    BOOST_CHECK( isTupleType == true );
    auto typeId = typelistCursor.TupleTypeId( );
    BOOST_CHECK( typeId == Types::TupleTypeId::Tuple );

    auto tupleType = typelistCursor.ReadTupleType( );
    auto tupleTypeCursor = tupleType.Cursor( );
    auto tupleTypeCursorSize = tupleTypeCursor.Size( );
    BOOST_CHECK( tupleTypeCursorSize == 0 );

    auto tupleTypeCursorIsValid = tupleTypeCursor.IsValid( );
    BOOST_CHECK( tupleTypeCursorIsValid == false );
}

// --run_test=TypeDescriptorCursorTests/BasicTupleTypeTest2
BOOST_AUTO_TEST_CASE( BasicTupleTypeTest2 )
{
    using ArgType1 = Tuple<Tuple<>,Tuple<>>;
    constexpr ArgType1 arg1;

    constexpr auto descriptor = Persistent::Descriptor( arg1 );

    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    bool rootDescriptorCursorIsTypeList = rootDescriptorCursor.IsTypeListType( );
    BOOST_CHECK( rootDescriptorCursorIsTypeList == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );
    bool isTupleType = typelistCursor.IsTupleType( );
    BOOST_CHECK( isTupleType == true );
    auto typeId = typelistCursor.TupleTypeId( );
    BOOST_CHECK( typeId == Types::TupleTypeId::Tuple );

    auto tupleType = typelistCursor.ReadTupleType( );
    auto tupleTypeCursor = tupleType.Cursor( );
    auto tupleTypeCursorSize = tupleTypeCursor.Size( );
    BOOST_CHECK( tupleTypeCursorSize == 2 );

    auto tupleTypeCursorIsValid = tupleTypeCursor.IsValid( );
    BOOST_CHECK( tupleTypeCursorIsValid == true );

    auto nestedTupleType1 = tupleTypeCursor.ReadTupleType( );
    auto nestedTupleType1Cursor = nestedTupleType1.Cursor( );
    auto nestedTupleType1CursorSize = nestedTupleType1Cursor.Size( );
    BOOST_CHECK( nestedTupleType1CursorSize == 0 );

    auto nestedTupleType1CursorIsValid = nestedTupleType1Cursor.IsValid( );
    BOOST_CHECK( nestedTupleType1CursorIsValid == false );

    auto nestedTupleType2 = tupleTypeCursor.ReadTupleType( );
    auto nestedTupleType2Cursor = nestedTupleType2.Cursor( );
    auto nestedTupleType2CursorSize = nestedTupleType2Cursor.Size( );
    BOOST_CHECK( nestedTupleType2CursorSize == 0 );

    auto nestedTupleType2CursorIsValid = nestedTupleType2Cursor.IsValid( );
    BOOST_CHECK( nestedTupleType2CursorIsValid == false );




}



// --run_test=TypeDescriptorCursorTests/TimeseriesPointAdaptedTest1
BOOST_AUTO_TEST_CASE( TimeseriesPointAdaptedTest1 )
{
    using ArgType1 = TimeseriesPoint;
    constexpr ArgType1 arg1;

    using FormatTraits = Persistent::Internal::FormatTraits<ArgType1>;
    using FormatType = FormatTraits::FormatType;
    constexpr auto format = FormatTraits::Format;
    constexpr bool isFixedSize = Types::IsFixedSize<ArgType1>::value;

    constexpr auto descriptor = Persistent::Descriptor( arg1 );

    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    bool rootDescriptorCursorIsTypeList = rootDescriptorCursor.IsTypeListType( );
    BOOST_CHECK( rootDescriptorCursorIsTypeList == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );
    bool isAdapted = typelistCursor.IsAdaptedType( );
    BOOST_CHECK( isAdapted == true );

    auto adaptedType = typelistCursor.ReadAdaptedType( );
    auto adaptedCursor = adaptedType.Cursor( );
    auto adaptedCursorSize = adaptedCursor.Size( );
    BOOST_CHECK( adaptedCursorSize == 3 );
    auto isBasicType = adaptedCursor.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::DateTime );
    basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::UInt64 );
    basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::Double );
}

// --run_test=TypeDescriptorCursorTests/ArrayTest1
BOOST_AUTO_TEST_CASE( ArrayTest1 )
{
    using ArgType1 = std::array<bool,4>;
    constexpr ArgType1 arg1{};

    constexpr auto descriptor = Persistent::Descriptor( arg1 );

    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    bool rootDescriptorCursorIsTypeList = rootDescriptorCursor.IsTypeListType( );
    BOOST_CHECK( rootDescriptorCursorIsTypeList == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );

    auto isBasicType = typelistCursor.IsFixedSizeBasicArrayType( );
    BOOST_CHECK( isBasicType == true );
    auto isArray = IsSet( typelistCursor.Modifiers( ), Persistent::ModifierFlags::Array );
    BOOST_CHECK( isArray == true );
    auto isFixedSize = IsSet( typelistCursor.Modifiers( ), Persistent::ModifierFlags::Fixed );
    BOOST_CHECK( isFixedSize == true );

    auto basicArrayType = typelistCursor.ReadFixedSizeBasicArrayType( );
    auto elementType = basicArrayType.BasicTypeId( );
    BOOST_CHECK( elementType == Types::BasicTypeId::Boolean );
    auto arraySize = basicArrayType.ArraySize( );
    BOOST_CHECK( arraySize == 4 );
}

// --run_test=TypeDescriptorCursorTests/ArrayTest2
BOOST_AUTO_TEST_CASE( ArrayTest2 )
{
    using ArgType1 = std::array<TimeseriesPoint, 4>;
    constexpr ArgType1 arg1{};
    using ArgType2 = SByte;
    constexpr ArgType2 arg2 = 2;

    constexpr auto descriptor = Persistent::Descriptor( arg1, arg2 );

    using FormatTraits = Persistent::Internal::FormatTraits<TimeseriesPoint>;
    constexpr auto format = FormatTraits::Format;


    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    bool rootDescriptorCursorIsTypeList = rootDescriptorCursor.IsTypeListType( );
    BOOST_CHECK( rootDescriptorCursorIsTypeList == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );

    // arg1
    auto isFixedSizeArrayType = typelistCursor.IsFixedSizeArrayType( );
    BOOST_CHECK( isFixedSizeArrayType == true );
    auto fixedSizeArrayType = typelistCursor.ReadFixedSizeArrayType( );
    auto arraySize = fixedSizeArrayType.ArraySize( );
    BOOST_CHECK( arraySize == 4 );
    auto fixedSizeArrayTypeCursor = fixedSizeArrayType.Cursor( );
    auto isAdaptedType = fixedSizeArrayTypeCursor.IsAdaptedType( );
    BOOST_CHECK( isAdaptedType == true );

    auto adaptedType = fixedSizeArrayTypeCursor.ReadAdaptedType( );
    auto adaptedCursor = adaptedType.Cursor( );
    auto adaptedCursorSize = adaptedCursor.Size( );
    BOOST_CHECK( adaptedCursorSize == 3 );
    auto isBasicType = adaptedCursor.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::DateTime );
    basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::UInt64 );
    basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::Double );

    // arg2
    isBasicType = typelistCursor.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    basicType = typelistCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::SByte );

}



// --run_test=TypeDescriptorCursorTests/VectorTest1
BOOST_AUTO_TEST_CASE( VectorTest1 )
{
    using ArgType1 = Vector<bool>;
    ArgType1 arg1;

    constexpr auto descriptor = Persistent::Descriptor( arg1 );

    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    bool rootDescriptorCursorIsTypeList = rootDescriptorCursor.IsTypeListType( );
    BOOST_CHECK( rootDescriptorCursorIsTypeList == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );

    auto isBasicArrayType = typelistCursor.IsBasicArrayType( );
    BOOST_CHECK( isBasicArrayType == true );
    auto isArray = IsSet( typelistCursor.Modifiers( ), Persistent::ModifierFlags::Array );
    BOOST_CHECK( isArray == true );
    auto isFixedSize = IsSet( typelistCursor.Modifiers( ), Persistent::ModifierFlags::Fixed );
    BOOST_CHECK( isFixedSize == false );

    auto basicArrayType = typelistCursor.ReadBasicArrayType( );
    auto elementType = basicArrayType.BasicTypeId( );
    BOOST_CHECK( elementType == Types::BasicTypeId::Boolean );
    

}

// --run_test=TypeDescriptorCursorTests/VectorTest2
BOOST_AUTO_TEST_CASE( VectorTest2 )
{
    using ArgType1 = Vector<TimeseriesPoint>;
    ArgType1 arg1;

    using ArgType2 = SByte;
    constexpr ArgType2 arg2 = 2;

    constexpr auto descriptor = Persistent::Descriptor( arg1, arg2 );
    constexpr auto descriptorSize = sizeof( descriptor );

    Persistent::TypeDescriptorCursor rootDescriptorCursor( descriptor );
    auto rootDescriptorCursorIsValid = rootDescriptorCursor.IsValid( );
    BOOST_CHECK( rootDescriptorCursorIsValid == true );

    bool rootDescriptorCursorIsTypeList = rootDescriptorCursor.IsTypeListType( );
    BOOST_CHECK( rootDescriptorCursorIsTypeList == true );

    auto typelist = rootDescriptorCursor.ReadTypeListType( );
    auto typelistCursor = typelist.Cursor( );

    auto typeId = typelistCursor.TypeId( );
    auto isArrayType = typelistCursor.IsArrayType( );
    BOOST_CHECK( isArrayType == true );


    auto arrayType = typelistCursor.ReadArrayType( );
    auto arrayTypeCursor = arrayType.Cursor( );
    auto arrayTypeCursorSize = arrayTypeCursor.Size( );
    BOOST_CHECK( arrayTypeCursorSize == 1 );

    auto isAdaptedType = arrayTypeCursor.IsAdaptedType( );
    BOOST_CHECK( isAdaptedType == true );

    auto adaptedType = arrayTypeCursor.ReadAdaptedType( );
    auto adaptedCursor = adaptedType.Cursor( );
    auto adaptedCursorSize = adaptedCursor.Size( );
    BOOST_CHECK( adaptedCursorSize == 3 );
    auto isBasicType = adaptedCursor.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    auto basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::DateTime );
    basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::UInt64 );
    basicType = adaptedCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::Double );

    // arg2
    isBasicType = typelistCursor.IsBasicType( );
    BOOST_CHECK( isBasicType == true );
    basicType = typelistCursor.ReadBasicType( );
    BOOST_CHECK( basicType.BasicTypeId( ) == Types::BasicTypeId::SByte );

}





BOOST_AUTO_TEST_SUITE_END( )
