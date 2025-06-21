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

using namespace Harlinn::Common;
struct TimeseriesPointA
{
    DateTime timestamp_;
    UInt64 flags_;
    double value_;

    using TypeList = Core::TypeList<DateTime, UInt64, double>;
};

struct TimeseriesPointB
{
    DateTime timestamp_;
    UInt64 flags_;
    double value_;
};

struct TimeseriesPointC
{
    DateTime timestamp_;
    UInt64 flags_;
    double value_;
};


namespace Harlinn::Common::Core::Types::Adapters
{
    template<>
    struct TypeAdapter<TimeseriesPointC> : std::true_type
    {
        using type = Core::TypeList<DateTime, UInt64, double>;
    };
}

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    struct TypeListTest
    {
        template<typename ...Args>
        constexpr static size_t IsSupported( Args&& ...args ) noexcept
        {
            using Type = TypeList<Args...>;
            return Types::IsSupportedType<Type>::value;
        }

        template<typename ...Args> 
        constexpr static bool IsFixedSize( Args&& ...args ) noexcept
        {
            using Type = TypeList<Args...>;
            return Types::IsFixedSize<Type>::value;
        }

        template<typename ...Args>
        constexpr static size_t PackedSizeOf( Args&& ...args ) noexcept
        {
            using Type = TypeList<Args...>;
            return Types::PackedSizeOf<Type>::value;
        }
    };

}







BOOST_FIXTURE_TEST_SUITE( TraitsTests, LocalFixture )

// --run_test=TraitsTests/IsPointerTest1
BOOST_AUTO_TEST_CASE( IsPointerTest1 )
{
    constexpr bool typeIsPointer_1 = IsPointer<char*>;
    BOOST_CHECK( typeIsPointer_1 == true );
    constexpr bool typeIsPointer_2 = IsPointer<const char*>;
    BOOST_CHECK( typeIsPointer_2 == true );
    constexpr bool typeIsPointer_3 = IsPointer<const volatile char*>;
    BOOST_CHECK( typeIsPointer_3 == true );
    constexpr bool typeIsPointer_4 = IsPointer<char*&>;
    BOOST_CHECK( typeIsPointer_4 == true );
    constexpr bool typeIsPointer_5 = IsPointer<const char*&>;
    BOOST_CHECK( typeIsPointer_5 == true );
    constexpr bool typeIsPointer_6 = IsPointer<const volatile char*&>;
    BOOST_CHECK( typeIsPointer_6 == true );

    constexpr bool typeIsPointer_7 = std::is_pointer_v<char*>;
    BOOST_CHECK( typeIsPointer_7 == true );
    constexpr bool typeIsPointer_8 = std::is_pointer_v<const char*>;
    BOOST_CHECK( typeIsPointer_8 == true );
    constexpr bool typeIsPointer_9 = std::is_pointer_v<const volatile char*>;
    BOOST_CHECK( typeIsPointer_9 == true );
    constexpr bool typeIsPointer_10 = std::is_pointer_v<char*&>;
    BOOST_CHECK( typeIsPointer_10 == false );
    constexpr bool typeIsPointer_11 = std::is_pointer_v<const char*&>;
    BOOST_CHECK( typeIsPointer_11 == false );
    constexpr bool typeIsPointer_12 = std::is_pointer_v<const volatile char*&>;
    BOOST_CHECK( typeIsPointer_12 == false );

}


// --run_test=TraitsTests/IsConstTest1
BOOST_AUTO_TEST_CASE( IsConstTest1 )
{
    constexpr bool typeIsConst_1 = IsConst<const char>;
    BOOST_CHECK( typeIsConst_1 == true );
    constexpr bool typeIsConst_2 = IsConst<const char&>;
    BOOST_CHECK( typeIsConst_2 == true );
    constexpr bool typeIsConst_3 = IsConst<const volatile char&>;
    BOOST_CHECK( typeIsConst_3 == true );

    constexpr bool typeIsConst_4 = IsConst<char>;
    BOOST_CHECK( typeIsConst_4 == false );
    constexpr bool typeIsConst_5 = IsConst<char&>;
    BOOST_CHECK( typeIsConst_5 == false );
    constexpr bool typeIsConst_6 = IsConst<volatile char&>;
    BOOST_CHECK( typeIsConst_6 == false );
}

// --run_test=TraitsTests/IsVolatileTest1
BOOST_AUTO_TEST_CASE( IsVolatileTest1 )
{
    constexpr bool typeIsVolatile_1 = IsVolatile<volatile char>;
    BOOST_CHECK( typeIsVolatile_1 == true );
    constexpr bool typeIsVolatile_2 = IsVolatile<volatile char&>;
    BOOST_CHECK( typeIsVolatile_2 == true );
    constexpr bool typeIsVolatile_3 = IsVolatile<volatile const char&>;
    BOOST_CHECK( typeIsVolatile_3 == true );

    constexpr bool typeIsVolatile_4 = IsVolatile<char>;
    BOOST_CHECK( typeIsVolatile_4 == false );
    constexpr bool typeIsVolatile_5 = IsVolatile<char&>;
    BOOST_CHECK( typeIsVolatile_5 == false );
    constexpr bool typeIsVolatile_6 = IsVolatile<const char&>;
    BOOST_CHECK( typeIsVolatile_6 == false );
}

// --run_test=TraitsTests/IsReferenceTest1
BOOST_AUTO_TEST_CASE( IsReferenceTest1 )
{
    constexpr bool typeIsReference_1 = IsReference<char&>;
    BOOST_CHECK( typeIsReference_1 == true );
    constexpr bool typeIsReference_2 = IsReference<const char&>;
    BOOST_CHECK( typeIsReference_2 == true );
    constexpr bool typeIsReference_3 = IsReference<const volatile char&>;
    BOOST_CHECK( typeIsReference_3 == true );

    constexpr bool typeIsReference_4 = IsReference<char>;
    BOOST_CHECK( typeIsReference_4 == false );
    constexpr bool typeIsReference_5 = IsReference<const char>;
    BOOST_CHECK( typeIsReference_5 == false );
    constexpr bool typeIsReference_6 = IsReference<const volatile char>;
    BOOST_CHECK( typeIsReference_6 == false );
}

// --run_test=TraitsTests/IsReferenceTest2
BOOST_AUTO_TEST_CASE( IsReferenceTest2 )
{
    constexpr bool typeIsReference_1 = IsReference<char*&>;
    BOOST_CHECK( typeIsReference_1 == true );
    constexpr bool typeIsReference_2 = IsReference<const char*&>;
    BOOST_CHECK( typeIsReference_2 == true );
    constexpr bool typeIsReference_3 = IsReference<const volatile char*&>;
    BOOST_CHECK( typeIsReference_3 == true );

    constexpr bool typeIsReference_4 = IsReference<char*>;
    BOOST_CHECK( typeIsReference_4 == false );
    constexpr bool typeIsReference_5 = IsReference<const char*>;
    BOOST_CHECK( typeIsReference_5 == false );
    constexpr bool typeIsReference_6 = IsReference<const volatile char*>;
    BOOST_CHECK( typeIsReference_6 == false );
}




// --run_test=TraitsTests/IsBasicTypeTest1
BOOST_AUTO_TEST_CASE( IsBasicTypeTest1 )
{
    constexpr bool boolIsBasicType = IsBasicType<bool>;
    BOOST_CHECK( boolIsBasicType == true );
    constexpr bool charIsBasicType = IsBasicType<char>;
    BOOST_CHECK( charIsBasicType == true );
    constexpr bool sbyteIsBasicType = IsBasicType<SByte>;
    BOOST_CHECK( sbyteIsBasicType == true );
    constexpr bool byteIsBasicType = IsBasicType<Byte>;
    BOOST_CHECK( byteIsBasicType == true );
    constexpr bool wchar_tIsBasicType = IsBasicType<wchar_t>;
    BOOST_CHECK( wchar_tIsBasicType == true );
    constexpr bool int16IsBasicType = IsBasicType<Int16>;
    BOOST_CHECK( int16IsBasicType == true );
    constexpr bool uint16IsBasicType = IsBasicType<UInt16>;
    BOOST_CHECK( uint16IsBasicType == true );
    constexpr bool int32IsBasicType = IsBasicType<Int32>;
    BOOST_CHECK( int32IsBasicType == true );
    constexpr bool uint32IsBasicType = IsBasicType<UInt32>;
    BOOST_CHECK( uint32IsBasicType == true );
    constexpr bool longIsBasicType = IsBasicType<long>;
    BOOST_CHECK( longIsBasicType == true );
    constexpr bool ulongIsBasicType = IsBasicType<unsigned long>;
    BOOST_CHECK( ulongIsBasicType == true );
    constexpr bool int64IsBasicType = IsBasicType<Int64>;
    BOOST_CHECK( int64IsBasicType == true );
    constexpr bool uint64IsBasicType = IsBasicType<UInt64>;
    BOOST_CHECK( uint64IsBasicType == true );
    constexpr bool floatIsBasicType = IsBasicType<float>;
    BOOST_CHECK( floatIsBasicType == true );
    constexpr bool doubleIsBasicType = IsBasicType<double>;
    BOOST_CHECK( doubleIsBasicType == true );
    constexpr bool timeSpanIsBasicType = IsBasicType<TimeSpan>;
    BOOST_CHECK( timeSpanIsBasicType == true );
    constexpr bool dateTimeIsBasicType = IsBasicType<DateTime>;
    BOOST_CHECK( dateTimeIsBasicType == true );
    constexpr bool currencyIsBasicType = IsBasicType<Currency>;
    BOOST_CHECK( currencyIsBasicType == true );
    constexpr bool guidIsBasicType = IsBasicType<Guid>;
    BOOST_CHECK( guidIsBasicType == true );

    constexpr bool stringIsBasicType = IsBasicType<std::string>;
    BOOST_CHECK( stringIsBasicType == false );
}

// --run_test=TraitsTests/CArrayTypeTraitsTest1
BOOST_AUTO_TEST_CASE( CArrayTypeTraitsTest1 )
{
    constexpr Byte byteArray[] = { '1','2' };
    using ByteArrayTypeTraits = Types::Internal::ArrayTypeTraits<decltype( byteArray ), decltype( byteArray )>;

    constexpr bool isArray = ByteArrayTypeTraits::IsArray;
    BOOST_CHECK( isArray == true );

    constexpr size_t rank = ByteArrayTypeTraits::Rank;
    BOOST_CHECK( rank == 1 );

    constexpr size_t extent = ByteArrayTypeTraits::Extent;
    BOOST_CHECK( extent == 2 );

    using ElementTraitsOfByteArrayTypeTraits = Types::TypeTraits<ByteArrayTypeTraits::ElementType>;
    constexpr bool isByte = ElementTraitsOfByteArrayTypeTraits::TypeId == Types::BasicTypeId::Byte;
    BOOST_CHECK( isByte == true );

}

// --run_test=TraitsTests/IsContainerTest1
BOOST_AUTO_TEST_CASE( IsContainerTest1 )
{
    constexpr bool stdarrayIsContainer = IsContainer<std::array<Byte, 1>>;
    BOOST_CHECK( stdarrayIsContainer == true );


    constexpr bool vectorIsContainer = IsContainer<std::vector<Byte>>;
    BOOST_CHECK( vectorIsContainer == true );
    constexpr bool VectorIsContainer = IsContainer<Vector<Byte>>;
    BOOST_CHECK( VectorIsContainer == true );
    constexpr bool unorderedMapIsContainer = IsContainer<std::unordered_map<Byte, long>>;
    BOOST_CHECK( unorderedMapIsContainer == true );

    constexpr bool stdstringIsContainer = IsContainer<AnsiString>;
    BOOST_CHECK( stdstringIsContainer == true );

    constexpr bool stdwstringIsContainer = IsContainer<WideString>;
    BOOST_CHECK( stdwstringIsContainer == true );

    constexpr bool stdstring_viewIsContainer = IsContainer<AnsiStringView>;
    BOOST_CHECK( stdstring_viewIsContainer == true );

    constexpr bool stdwstring_viewIsContainer = IsContainer<WideStringView>;
    BOOST_CHECK( stdwstring_viewIsContainer == true );

    constexpr bool stdspanIsContainer = IsContainer<std::span<Byte>>;
    BOOST_CHECK( stdspanIsContainer == true );


}

// --run_test=TraitsTests/IsTupleTest1
BOOST_AUTO_TEST_CASE( IsTupleTest1 )
{
    constexpr bool stdtupleIsTuple = IsStdTuple< std::tuple<> >;
    BOOST_CHECK( stdtupleIsTuple == true );
    constexpr bool tupleIsTuple = IsCoreTuple< Tuple<> >;
    BOOST_CHECK( tupleIsTuple == true );
}

// --run_test=TraitsTests/TupleTraitsCountTest1
BOOST_AUTO_TEST_CASE( TupleTraitsCountTest1 )
{
    using TupleTraits1 = Types::Internal::TupleTypeTraits<Tuple<>, Tuple<> >;
    constexpr auto countOfTupleTraits1 = TupleTraits1::Count;
    BOOST_CHECK( countOfTupleTraits1 == 0 );

    using TupleTraits2 = Types::Internal::TupleTypeTraits< Tuple<Int32, double>, Tuple<Int32, double> >;
    constexpr auto countOfTupleTraits2 = TupleTraits2::Count;
    BOOST_CHECK( countOfTupleTraits2 == 2 );
}

// --run_test=TraitsTests/TupleTraitsTypeAtTest1
BOOST_AUTO_TEST_CASE( TupleTraitsTypeAtTest1 )
{
    using TupleTraits = Types::Internal::TupleTypeTraits<Tuple<Int32, double>, Tuple<Int32, double> >;
    using TypeAtTupleTraits0 = Meta::At<TupleTraits::Types,0>;
    constexpr bool isTypeAtTupleTraits0Int32 = std::is_same_v<TypeAtTupleTraits0, Int32>;
    BOOST_CHECK( isTypeAtTupleTraits0Int32 == true );

    using TypeAtTupleTraits1 = Meta::At<TupleTraits::Types, 1>;
    constexpr bool isTypeAtTupleTraits1Double = std::is_same_v<TypeAtTupleTraits1, double>;
    BOOST_CHECK( isTypeAtTupleTraits1Double == true );

}

// --run_test=TraitsTests/TupleTraitsTypeTraitsAtTest1
BOOST_AUTO_TEST_CASE( TupleTraitsTypeTraitsAtTest1 )
{
    using TupleTraits = Types::Internal::TupleTypeTraits<Tuple<Int32, double>, Tuple<Int32, double> >;
    using TypeAtTupleTraits0 = Types::TypeTraits< Meta::At<TupleTraits::Types,0> >;
    constexpr bool isTypeAtTupleTraits0Int32 = TypeAtTupleTraits0::TypeId == Types::BasicTypeId::Int32;
    BOOST_CHECK( isTypeAtTupleTraits0Int32 == true );

    using TypeAtTupleTraits1 = Types::TypeTraits< Meta::At<TupleTraits::Types, 1> >;
    constexpr bool isTypeAtTupleTraits1Double = TypeAtTupleTraits1::TypeId == Types::BasicTypeId::Double;
    BOOST_CHECK( isTypeAtTupleTraits1Double == true );

}

template<typename T, Types::BasicTypeId TypeId>
void TypeTraitsTest( )
{
    using Type = T;
    constexpr Types::BasicTypeId expectedTypeId = TypeId;

    using TypeTraits_1 = Types::TypeTraits<Type>;
    constexpr bool hasExpectedTypeId_1 = TypeTraits_1::TypeId == expectedTypeId;
    BOOST_CHECK( hasExpectedTypeId_1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool hasExpectedTypeId_2 = TypeTraits_2::TypeId == expectedTypeId;
    BOOST_CHECK( hasExpectedTypeId_2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );

    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool hasExpectedTypeId_3 = TypeTraits_3::TypeId == expectedTypeId;
    BOOST_CHECK( hasExpectedTypeId_3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool hasExpectedTypeId_4 = TypeTraits_4::TypeId == expectedTypeId;
    BOOST_CHECK( hasExpectedTypeId_4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );


    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool hasExpectedTypeId_5 = TypeTraits_5::TypeId == expectedTypeId;
    BOOST_CHECK( hasExpectedTypeId_5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool hasExpectedTypeId_6 = TypeTraits_6::TypeId == expectedTypeId;
    BOOST_CHECK( hasExpectedTypeId_6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool hasExpectedTypeId_7 = TypeTraits_7::TypeId == expectedTypeId;
    BOOST_CHECK( hasExpectedTypeId_7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool hasExpectedTypeId_8 = TypeTraits_8::TypeId == expectedTypeId;
    BOOST_CHECK( hasExpectedTypeId_8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}
// --run_test=TraitsTests/TypeTraitsTest1
BOOST_AUTO_TEST_CASE( TypeTraitsTest1 )
{
    TypeTraitsTest<bool, Types::BasicTypeId::Boolean>( );
    TypeTraitsTest<char, Types::BasicTypeId::Char>( );
    TypeTraitsTest<SByte, Types::BasicTypeId::SByte>( );
    TypeTraitsTest<Byte, Types::BasicTypeId::Byte>( );
    TypeTraitsTest<wchar_t, Types::BasicTypeId::WChar>( );
    TypeTraitsTest<Int16, Types::BasicTypeId::Int16>( );
    TypeTraitsTest<UInt16, Types::BasicTypeId::UInt16>( );
    TypeTraitsTest<Int32, Types::BasicTypeId::Int32>( );
    TypeTraitsTest<long, Types::BasicTypeId::Int32>( );
    TypeTraitsTest<UInt32, Types::BasicTypeId::UInt32>( );
    TypeTraitsTest<unsigned long, Types::BasicTypeId::UInt32>( );
    TypeTraitsTest<Int64, Types::BasicTypeId::Int64>( );
    TypeTraitsTest<UInt64, Types::BasicTypeId::UInt64>( );
    TypeTraitsTest<float, Types::BasicTypeId::Single>( );
    TypeTraitsTest<double, Types::BasicTypeId::Double>( );
    TypeTraitsTest<TimeSpan, Types::BasicTypeId::TimeSpan>( );
    TypeTraitsTest<DateTime, Types::BasicTypeId::DateTime>( );
    TypeTraitsTest<Currency, Types::BasicTypeId::Currency>( );
    TypeTraitsTest<Guid, Types::BasicTypeId::Guid>( );

}


template<typename T>
void CArrayTypeTraitsTest( )
{
    using Type = T[ 10 ];

    using TypeTraits_1 = Types::TypeTraits<Type>;
    constexpr bool isArray_1 = TypeTraits_1::IsArray;
    BOOST_CHECK( isArray_1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isArray_2 = TypeTraits_2::IsArray;
    BOOST_CHECK( isArray_2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    constexpr bool expectedIsArray_3 = std::is_array_v<std::remove_cvref_t<Type&>>;
    constexpr bool expectedIsVolatile_3 = IsVolatile<Type&>;
    constexpr bool expectedIsReference_3 = IsReference<Type&>;
    constexpr bool expectedIsConst_3 = IsConst<Type&>;



    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isArray_3 = TypeTraits_3::IsArray;
    BOOST_CHECK( isArray_3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );

    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isArray_4 = TypeTraits_4::IsArray;
    BOOST_CHECK( isArray_4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );


    constexpr bool expectedIsVolatile_5 = IsVolatile<const Type&>;
    constexpr bool expectedIsReference_5 = IsReference<const Type&>;
    constexpr bool expectedIsConst_5 = IsConst<const Type&>;

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isArray_5 = TypeTraits_5::IsArray;
    BOOST_CHECK( isArray_5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    constexpr bool expectedIsVolatile_6 = IsVolatile<volatile Type&>;
    constexpr bool expectedIsReference_6 = IsReference<volatile Type&>;
    constexpr bool expectedIsConst_6 = IsConst<volatile Type&>;

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isArray_6 = TypeTraits_6::IsArray;
    BOOST_CHECK( isArray_6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isArray_7 = TypeTraits_7::IsArray;
    BOOST_CHECK( isArray_7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    constexpr bool expectedIsVolatile_8 = IsVolatile<const volatile Type&>;
    constexpr bool expectedIsReference_8 = IsReference<const volatile Type&>;
    constexpr bool expectedIsConst_8 = IsConst<const volatile Type&>;

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isArray_8 = TypeTraits_8::IsArray;
    BOOST_CHECK( isArray_8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}

// --run_test=TraitsTests/CArrayTypeTraitsTest2
BOOST_AUTO_TEST_CASE( CArrayTypeTraitsTest2 )
{
    CArrayTypeTraitsTest<bool>( );
    CArrayTypeTraitsTest<char>( );
    CArrayTypeTraitsTest<SByte>( );
    CArrayTypeTraitsTest<Byte>( );
    CArrayTypeTraitsTest<wchar_t>( );
    CArrayTypeTraitsTest<Int16>( );
    CArrayTypeTraitsTest<UInt16>( );
    CArrayTypeTraitsTest<Int32>( );
    CArrayTypeTraitsTest<long>( );
    CArrayTypeTraitsTest<UInt32>( );
    CArrayTypeTraitsTest<unsigned long>( );
    CArrayTypeTraitsTest<Int64>( );
    CArrayTypeTraitsTest<UInt64>( );
    CArrayTypeTraitsTest<float>( );
    CArrayTypeTraitsTest<double>( );
    CArrayTypeTraitsTest<TimeSpan>( );
    CArrayTypeTraitsTest<DateTime>( );
    CArrayTypeTraitsTest<Currency>( );
    CArrayTypeTraitsTest<Guid>( );
}


template<typename T>
void CPointerTypeTraitsTest( )
{
    using Type = T*;

    using TypeTraits_1 = Types::TypeTraits<Type>;
    constexpr bool isPointer1 = TypeTraits_1::IsPointer;
    BOOST_CHECK( isPointer1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isPointer2 = TypeTraits_2::IsPointer;
    BOOST_CHECK( isPointer2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isPointer3 = TypeTraits_3::IsPointer;
    BOOST_CHECK( isPointer3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isPointer4 = TypeTraits_4::IsPointer;
    BOOST_CHECK( isPointer4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isPointer5 = TypeTraits_5::IsPointer;
    BOOST_CHECK( isPointer5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isPointer6 = TypeTraits_6::IsPointer;
    BOOST_CHECK( isPointer6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isPointer7 = TypeTraits_7::IsPointer;
    BOOST_CHECK( isPointer7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isPointer8 = TypeTraits_8::IsPointer;
    BOOST_CHECK( isPointer8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}

// --run_test=TraitsTests/CPointerTypeTraitsTest1
BOOST_AUTO_TEST_CASE( CPointerTypeTraitsTest1 )
{
    CPointerTypeTraitsTest<bool>( );
    CPointerTypeTraitsTest<char>( );
    CPointerTypeTraitsTest<SByte>( );
    CPointerTypeTraitsTest<Byte>( );
    CPointerTypeTraitsTest<wchar_t>( );
    CPointerTypeTraitsTest<Int16>( );
    CPointerTypeTraitsTest<UInt16>( );
    CPointerTypeTraitsTest<Int32>( );
    CPointerTypeTraitsTest<long>( );
    CPointerTypeTraitsTest<UInt32>( );
    CPointerTypeTraitsTest<unsigned long>( );
    CPointerTypeTraitsTest<Int64>( );
    CPointerTypeTraitsTest<UInt64>( );
    CPointerTypeTraitsTest<float>( );
    CPointerTypeTraitsTest<double>( );
    CPointerTypeTraitsTest<TimeSpan>( );
    CPointerTypeTraitsTest<DateTime>( );
    CPointerTypeTraitsTest<Currency>( );
    CPointerTypeTraitsTest<Guid>( );

}

template<typename ... T>
void StdTupleTypeTraitsTest( )
{
    using Type = std::tuple<T...>;

    using TypeTraits_1 = Types::TypeTraits<Type>;
    constexpr bool isTuple1 = TypeTraits_1::IsTuple;
    BOOST_CHECK( isTuple1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isTuple2 = TypeTraits_2::IsTuple;
    BOOST_CHECK( isTuple2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isTuple3 = TypeTraits_3::IsTuple;
    BOOST_CHECK( isTuple3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isTuple4 = TypeTraits_4::IsTuple;
    BOOST_CHECK( isTuple4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isTuple5 = TypeTraits_5::IsTuple;
    BOOST_CHECK( isTuple5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isTuple6 = TypeTraits_6::IsTuple;
    BOOST_CHECK( isTuple6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isTuple7 = TypeTraits_7::IsTuple;
    BOOST_CHECK( isTuple7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isTuple8 = TypeTraits_8::IsTuple;
    BOOST_CHECK( isTuple8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}

// --run_test=TraitsTests/StdTupleTypeTraitsTest1
BOOST_AUTO_TEST_CASE( StdTupleTypeTraitsTest1 )
{
    StdTupleTypeTraitsTest<>( );
    StdTupleTypeTraitsTest<Int32, double>( );
    StdTupleTypeTraitsTest<double, Int32, DateTime >( );
}

template<typename ... T>
void CoreTupleTypeTraitsTest( )
{
    using Type = Tuple<T...>;

    using TypeTraits_1 = Types::TypeTraits<Type>;
    constexpr bool isTuple1 = TypeTraits_1::IsTuple;
    BOOST_CHECK( isTuple1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isTuple2 = TypeTraits_2::IsTuple;
    BOOST_CHECK( isTuple2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isTuple3 = TypeTraits_3::IsTuple;
    BOOST_CHECK( isTuple3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isTuple4 = TypeTraits_4::IsTuple;
    BOOST_CHECK( isTuple4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isTuple5 = TypeTraits_5::IsTuple;
    BOOST_CHECK( isTuple5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isTuple6 = TypeTraits_6::IsTuple;
    BOOST_CHECK( isTuple6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isTuple7 = TypeTraits_7::IsTuple;
    BOOST_CHECK( isTuple7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isTuple8 = TypeTraits_8::IsTuple;
    BOOST_CHECK( isTuple8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}


// --run_test=TraitsTests/CoreTupleTypeTraitsTest1
BOOST_AUTO_TEST_CASE( CoreTupleTypeTraitsTest1 )
{
    CoreTupleTypeTraitsTest<>( );
    CoreTupleTypeTraitsTest<Int32, double>( );
    CoreTupleTypeTraitsTest<double, Int32, DateTime >( );
}

template<typename T, Types::ContainerTypeId TypeId>
void ContainerTypeTraitsTest( )
{
    using Type = T;

    using TypeTraits_1 = Types::TypeTraits<Type>;

    constexpr bool isExpectedContainerType = TypeTraits_1::TypeId == TypeId;
    BOOST_CHECK( isExpectedContainerType == true );

    constexpr bool isContainer1 = TypeTraits_1::IsContainer;
    BOOST_CHECK( isContainer1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isContainer2 = TypeTraits_2::IsContainer;
    BOOST_CHECK( isContainer2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isContainer3 = TypeTraits_3::IsContainer;
    BOOST_CHECK( isContainer3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isContainer4 = TypeTraits_4::IsContainer;
    BOOST_CHECK( isContainer4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isContainer5 = TypeTraits_5::IsContainer;
    BOOST_CHECK( isContainer5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isContainer6 = TypeTraits_6::IsContainer;
    BOOST_CHECK( isContainer6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isContainer7 = TypeTraits_7::IsContainer;
    BOOST_CHECK( isContainer7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isContainer8 = TypeTraits_8::IsContainer;
    BOOST_CHECK( isContainer8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}


// --run_test=TraitsTests/ContainerTypeTraitsTest1
BOOST_AUTO_TEST_CASE( ContainerTypeTraitsTest1 )
{
    ContainerTypeTraitsTest<std::array<Int32, 4>, Types::ContainerTypeId::StdArray>( );
    ContainerTypeTraitsTest<std::vector<Byte>, Types::ContainerTypeId::StdVector>( );
    ContainerTypeTraitsTest<std::unordered_map<int, double>, Types::ContainerTypeId::StdUnorderedMap>( );
    ContainerTypeTraitsTest<AnsiString, Types::ContainerTypeId::BasicString>( );
    ContainerTypeTraitsTest<WideString, Types::ContainerTypeId::BasicString>( );
    ContainerTypeTraitsTest<std::string_view, Types::ContainerTypeId::StdBasicStringView>( );
    ContainerTypeTraitsTest<std::wstring_view, Types::ContainerTypeId::StdBasicStringView>( );
    ContainerTypeTraitsTest<std::span<Byte, 12>, Types::ContainerTypeId::StdSpan>( );
    ContainerTypeTraitsTest<std::vector<bool>, Types::ContainerTypeId::StdVectorBool>( );
    ContainerTypeTraitsTest<std::deque<Currency>, Types::ContainerTypeId::StdDeque>( );
    ContainerTypeTraitsTest<std::forward_list<Currency>, Types::ContainerTypeId::StdForwardList>( );
    ContainerTypeTraitsTest<std::list<Currency>, Types::ContainerTypeId::StdList>( );
    ContainerTypeTraitsTest<std::set<Currency>, Types::ContainerTypeId::StdSet>( );
    ContainerTypeTraitsTest<std::map<Currency, std::string>, Types::ContainerTypeId::StdMap>( );
    ContainerTypeTraitsTest<std::multiset<Currency>, Types::ContainerTypeId::StdMultiset>( );
    ContainerTypeTraitsTest<std::multimap<Currency, std::string>, Types::ContainerTypeId::StdMultimap>( );
    ContainerTypeTraitsTest<std::unordered_set<Currency>, Types::ContainerTypeId::StdUnorderedSet>( );
    ContainerTypeTraitsTest<std::unordered_multiset<Currency>, Types::ContainerTypeId::StdUnorderedMultiset>( );
    ContainerTypeTraitsTest<std::unordered_multimap<Currency, std::string>, Types::ContainerTypeId::StdUnorderedMultimap>( );
    ContainerTypeTraitsTest<std::stack<Currency>, Types::ContainerTypeId::StdStack>( );
    ContainerTypeTraitsTest<std::queue<Currency>, Types::ContainerTypeId::StdQueue>( );
    ContainerTypeTraitsTest<std::priority_queue<Currency>, Types::ContainerTypeId::StdPriorityQueue>( );
    ContainerTypeTraitsTest<std::priority_queue<Currency>, Types::ContainerTypeId::StdPriorityQueue>( );
}


// --run_test=TraitsTests/TypeTraitsTest47
BOOST_AUTO_TEST_CASE( TypeTraitsTest47 )
{
    using Type = std::optional<Currency>;

    using TypeTraits_1 = Types::TypeTraits<Type>;
    
    constexpr bool isOptional1 = TypeTraits_1::IsOptional;
    BOOST_CHECK( isOptional1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isOptional2 = TypeTraits_2::IsOptional;
    BOOST_CHECK( isOptional2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isOptional3 = TypeTraits_3::IsOptional;
    BOOST_CHECK( isOptional3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isOptional4 = TypeTraits_4::IsOptional;
    BOOST_CHECK( isOptional4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isOptional5 = TypeTraits_5::IsOptional;
    BOOST_CHECK( isOptional5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isOptional6 = TypeTraits_6::IsOptional;
    BOOST_CHECK( isOptional6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isOptional7 = TypeTraits_7::IsOptional;
    BOOST_CHECK( isOptional7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isOptional8 = TypeTraits_8::IsOptional;
    BOOST_CHECK( isOptional8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}

// --run_test=TraitsTests/TypeTraitsTest48
BOOST_AUTO_TEST_CASE( TypeTraitsTest48 )
{
    using Type = std::shared_ptr<Currency>;

    using TypeTraits_1 = Types::TypeTraits<Type>;

    constexpr bool isSharedPtr1 = TypeTraits_1::IsSharedPtr;
    BOOST_CHECK( isSharedPtr1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isSharedPtr2 = TypeTraits_2::IsSharedPtr;
    BOOST_CHECK( isSharedPtr2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isSharedPtr3 = TypeTraits_3::IsSharedPtr;
    BOOST_CHECK( isSharedPtr3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isSharedPtr4 = TypeTraits_4::IsSharedPtr;
    BOOST_CHECK( isSharedPtr4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isSharedPtr5 = TypeTraits_5::IsSharedPtr;
    BOOST_CHECK( isSharedPtr5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isSharedPtr6 = TypeTraits_6::IsSharedPtr;
    BOOST_CHECK( isSharedPtr6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isSharedPtr7 = TypeTraits_7::IsSharedPtr;
    BOOST_CHECK( isSharedPtr7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isSharedPtr8 = TypeTraits_8::IsSharedPtr;
    BOOST_CHECK( isSharedPtr8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}

// --run_test=TraitsTests/TypeTraitsTest49
BOOST_AUTO_TEST_CASE( TypeTraitsTest49 )
{
    using Type = std::unique_ptr<Currency>;

    using TypeTraits_1 = Types::TypeTraits<Type>;

    constexpr bool isUniquePtr1 = TypeTraits_1::IsUniquePtr;
    BOOST_CHECK( isUniquePtr1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isUniquePtr2 = TypeTraits_2::IsUniquePtr;
    BOOST_CHECK( isUniquePtr2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isUniquePtr3 = TypeTraits_3::IsUniquePtr;
    BOOST_CHECK( isUniquePtr3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isUniquePtr4 = TypeTraits_4::IsUniquePtr;
    BOOST_CHECK( isUniquePtr4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isUniquePtr5 = TypeTraits_5::IsUniquePtr;
    BOOST_CHECK( isUniquePtr5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isUniquePtr6 = TypeTraits_6::IsUniquePtr;
    BOOST_CHECK( isUniquePtr6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isUniquePtr7 = TypeTraits_7::IsUniquePtr;
    BOOST_CHECK( isUniquePtr7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isUniquePtr8 = TypeTraits_8::IsUniquePtr;
    BOOST_CHECK( isUniquePtr8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}


// --run_test=TraitsTests/TypeTraitsTest50
BOOST_AUTO_TEST_CASE( TypeTraitsTest50 )
{
    using Type = std::pair<Currency,std::string>;

    using TypeTraits_1 = Types::TypeTraits<Type>;

    constexpr bool isTuple1 = TypeTraits_1::IsTuple;
    BOOST_CHECK( isTuple1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isTuple2 = TypeTraits_2::IsTuple;
    BOOST_CHECK( isTuple2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isTuple3 = TypeTraits_3::IsTuple;
    BOOST_CHECK( isTuple3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isTuple4 = TypeTraits_4::IsTuple;
    BOOST_CHECK( isTuple4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isTuple5 = TypeTraits_5::IsTuple;
    BOOST_CHECK( isTuple5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isTuple6 = TypeTraits_6::IsTuple;
    BOOST_CHECK( isTuple6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isTuple7 = TypeTraits_7::IsTuple;
    BOOST_CHECK( isTuple7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isTuple8 = TypeTraits_8::IsTuple;
    BOOST_CHECK( isTuple8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}

// --run_test=TraitsTests/TypeTraitsTest51
BOOST_AUTO_TEST_CASE( TypeTraitsTest51 )
{
    using Type = std::variant<Currency, std::string>;

    using TypeTraits_1 = Types::TypeTraits<Type>;

    constexpr bool isVariant1 = TypeTraits_1::IsVariant;
    BOOST_CHECK( isVariant1 == true );
    constexpr bool isConst_1 = TypeTraits_1::IsConst;
    BOOST_CHECK( isConst_1 == false );
    constexpr bool isVolatile_1 = TypeTraits_1::IsVolatile;
    BOOST_CHECK( isVolatile_1 == false );
    constexpr bool isReference_1 = TypeTraits_1::IsReference;
    BOOST_CHECK( isReference_1 == false );

    using TypeTraits_2 = Types::TypeTraits<const Type>;
    constexpr bool isVariant2 = TypeTraits_2::IsVariant;
    BOOST_CHECK( isVariant2 == true );
    constexpr bool isConst_2 = TypeTraits_2::IsConst;
    BOOST_CHECK( isConst_2 == true );
    constexpr bool isVolatile_2 = TypeTraits_2::IsVolatile;
    BOOST_CHECK( isVolatile_2 == false );
    constexpr bool isReference_2 = TypeTraits_2::IsReference;
    BOOST_CHECK( isReference_2 == false );


    using TypeTraits_3 = Types::TypeTraits<Type&>;
    constexpr bool isVariant3 = TypeTraits_3::IsVariant;
    BOOST_CHECK( isVariant3 == true );
    constexpr bool isConst_3 = TypeTraits_3::IsConst;
    BOOST_CHECK( isConst_3 == false );
    constexpr bool isVolatile_3 = TypeTraits_3::IsVolatile;
    BOOST_CHECK( isVolatile_3 == false );
    constexpr bool isReference_3 = TypeTraits_3::IsReference;
    BOOST_CHECK( isReference_3 == true );


    using TypeTraits_4 = Types::TypeTraits<volatile Type>;
    constexpr bool isVariant4 = TypeTraits_4::IsVariant;
    BOOST_CHECK( isVariant4 == true );
    constexpr bool isConst_4 = TypeTraits_4::IsConst;
    BOOST_CHECK( isConst_4 == false );
    constexpr bool isVolatile_4 = TypeTraits_4::IsVolatile;
    BOOST_CHECK( isVolatile_4 == true );
    constexpr bool isReference_4 = TypeTraits_4::IsReference;
    BOOST_CHECK( isReference_4 == false );

    using TypeTraits_5 = Types::TypeTraits<const Type&>;
    constexpr bool isVariant5 = TypeTraits_5::IsVariant;
    BOOST_CHECK( isVariant5 == true );
    constexpr bool isConst_5 = TypeTraits_5::IsConst;
    BOOST_CHECK( isConst_5 == true );
    constexpr bool isVolatile_5 = TypeTraits_5::IsVolatile;
    BOOST_CHECK( isVolatile_5 == false );
    constexpr bool isReference_5 = TypeTraits_5::IsReference;
    BOOST_CHECK( isReference_5 == true );

    using TypeTraits_6 = Types::TypeTraits<volatile Type&>;
    constexpr bool isVariant6 = TypeTraits_6::IsVariant;
    BOOST_CHECK( isVariant6 == true );
    constexpr bool isConst_6 = TypeTraits_6::IsConst;
    BOOST_CHECK( isConst_6 == false );
    constexpr bool isVolatile_6 = TypeTraits_6::IsVolatile;
    BOOST_CHECK( isVolatile_6 == true );
    constexpr bool isReference_6 = TypeTraits_6::IsReference;
    BOOST_CHECK( isReference_6 == true );

    using TypeTraits_7 = Types::TypeTraits<const volatile Type>;
    constexpr bool isVariant7 = TypeTraits_7::IsVariant;
    BOOST_CHECK( isVariant7 == true );
    constexpr bool isConst_7 = TypeTraits_7::IsConst;
    BOOST_CHECK( isConst_7 == true );
    constexpr bool isVolatile_7 = TypeTraits_7::IsVolatile;
    BOOST_CHECK( isVolatile_7 == true );
    constexpr bool isReference_7 = TypeTraits_7::IsReference;
    BOOST_CHECK( isReference_7 == false );

    using TypeTraits_8 = Types::TypeTraits<const volatile Type&>;
    constexpr bool isVariant8 = TypeTraits_8::IsVariant;
    BOOST_CHECK( isVariant8 == true );
    constexpr bool isConst_8 = TypeTraits_8::IsConst;
    BOOST_CHECK( isConst_8 == true );
    constexpr bool isVolatile_8 = TypeTraits_8::IsVolatile;
    BOOST_CHECK( isVolatile_8 == true );
    constexpr bool isReference_8 = TypeTraits_8::IsReference;
    BOOST_CHECK( isReference_8 == true );
}

// --run_test=TraitsTests/TypeTraitsTest52
BOOST_AUTO_TEST_CASE( TypeTraitsTest52 )
{
    using Type = std::variant<Currency, std::string>;
    using TypeTraits = Types::TypeTraits<Type>;

    using CurrencyTypeTraits = Types::TypeTraits< Meta::At<TypeTraits::Types, 0> >;
    constexpr bool isCurrency = CurrencyTypeTraits::TypeId == Types::BasicTypeId::Currency;
    BOOST_CHECK( isCurrency == true );

    using StdStringTypeTraits = Types::TypeTraits< Meta::At<TypeTraits::Types, 1> >;
    constexpr bool isStdBasicString = StdStringTypeTraits::TypeId == Types::ContainerTypeId::StdBasicString;
    BOOST_CHECK( isStdBasicString == true );
}

// --run_test=TraitsTests/TypeTraitsTest53
BOOST_AUTO_TEST_CASE( TypeTraitsTest53 )
{
    using Type = std::variant<std::tuple<Currency>, std::pair<std::string,bool&>>;
    using TypeTraits = Types::TypeTraits<Type>;

    using FirstTypeTraits = Types::TypeTraits< Meta::At<TypeTraits::Types, 0> >;
    using SecondTypeTraits = Types::TypeTraits< Meta::At<TypeTraits::Types, 1> >;
    
    BOOST_CHECK( FirstTypeTraits::IsTuple == true );
    BOOST_CHECK( SecondTypeTraits::IsTuple == true );
    BOOST_CHECK( FirstTypeTraits::TypeId == Types::TupleTypeId::StdTuple );
    BOOST_CHECK( FirstTypeTraits::Count == 1 );
    BOOST_CHECK( SecondTypeTraits::Count == 2 );

    using CurrencyTypeTraits = Types::TypeTraits< Meta::At<FirstTypeTraits::Types, 0> >;
    constexpr bool isCurrency = CurrencyTypeTraits::TypeId == Types::BasicTypeId::Currency;
    BOOST_CHECK( isCurrency == true );

    using StdStringTypeTraits = Types::TypeTraits< Meta::At<SecondTypeTraits::Types, 0> >;
    constexpr bool isStdBasicString = StdStringTypeTraits::TypeId == Types::ContainerTypeId::StdBasicString;
    BOOST_CHECK( isStdBasicString == true );

    using boolTypeTraits = Types::TypeTraits< Meta::At<SecondTypeTraits::Types, 1> >;
    constexpr bool isBoolean = boolTypeTraits::TypeId == Types::BasicTypeId::Boolean;
    BOOST_CHECK( isBoolean == true );
    BOOST_CHECK( boolTypeTraits::IsReference );

}


// --run_test=TraitsTests/TypeTraitsTest54
BOOST_AUTO_TEST_CASE( TypeTraitsTest54 )
{
    using Type = Byte[2];
    constexpr auto isArray_1 = IsArray<Type>;
    BOOST_CHECK( isArray_1 == true );
    constexpr auto isArray_1b = std::is_array_v<Type>;
    BOOST_CHECK( isArray_1b == true );

    constexpr auto isArray_2 = IsArray<Type&>;
    BOOST_CHECK( isArray_2 == true );
    constexpr auto isArray_2b = std::is_array_v<Type&>;
    BOOST_CHECK( isArray_2b == false );

    constexpr auto isArray_3 = IsArray<Type&&>;
    BOOST_CHECK( isArray_3 == true );
    constexpr auto isArray_3b = std::is_array_v<Type&&>;
    BOOST_CHECK( isArray_3b == false );
}


// --run_test=TraitsTests/TypeTraitsTest55
BOOST_AUTO_TEST_CASE( TypeTraitsTest55 )
{
    using Type = std::array<Byte,2>;
    constexpr auto isStdArray_1 = IsStdArray<Type>;
    BOOST_CHECK( isStdArray_1 == true );
    constexpr auto isStdArray_1b = Core::Internal::IsStdArrayImpl<Type>;
    BOOST_CHECK( isStdArray_1b == true );

    constexpr auto isStdArray_2 = IsStdArray<Type&>;
    BOOST_CHECK( isStdArray_2 == true );
    constexpr auto isStdArray_2b = Core::Internal::IsStdArrayImpl<Type&>;
    BOOST_CHECK( isStdArray_2b == false );

    constexpr auto isStdArray_3 = IsStdArray<Type&&>;
    BOOST_CHECK( isStdArray_3 == true );
    constexpr auto isStdArray_3b = Core::Internal::IsStdArrayImpl<Type&&>;
    BOOST_CHECK( isStdArray_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest56
BOOST_AUTO_TEST_CASE( TypeTraitsTest56 )
{
    using Type = std::vector<Byte>;
    constexpr auto isStdVector_1 = IsStdVector<Type>;
    BOOST_CHECK( isStdVector_1 == true );
    constexpr auto isStdVector_1b = Core::Internal::IsStdVectorImpl<Type>;
    BOOST_CHECK( isStdVector_1b == true );

    constexpr auto isStdVector_2 = IsStdVector<Type&>;
    BOOST_CHECK( isStdVector_2 == true );
    constexpr auto isStdVector_2b = Core::Internal::IsStdVectorImpl<Type&>;
    BOOST_CHECK( isStdVector_2b == false );

    constexpr auto isStdVector_3 = IsStdVector<Type&&>;
    BOOST_CHECK( isStdVector_3 == true );
    constexpr auto isStdVector_3b = Core::Internal::IsStdVectorImpl<Type&&>;
    BOOST_CHECK( isStdVector_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest57
BOOST_AUTO_TEST_CASE( TypeTraitsTest57 )
{
    using Type = std::vector<bool>;
    constexpr auto isStdVectorBool_1 = IsStdVectorBool<Type>;
    BOOST_CHECK( isStdVectorBool_1 == true );
    constexpr auto isStdVectorBool_1b = Core::Internal::IsStdVectorBoolImpl<Type>;
    BOOST_CHECK( isStdVectorBool_1b == true );

    constexpr auto isStdVectorBool_2 = IsStdVectorBool<Type&>;
    BOOST_CHECK( isStdVectorBool_2 == true );
    constexpr auto isStdVectorBool_2b = Core::Internal::IsStdVectorBoolImpl<Type&>;
    BOOST_CHECK( isStdVectorBool_2b == false );

    constexpr auto isStdVectorBool_3 = IsStdVectorBool<Type&&>;
    BOOST_CHECK( isStdVectorBool_3 == true );
    constexpr auto isStdVectorBool_3b = Core::Internal::IsStdVectorBoolImpl<Type&&>;
    BOOST_CHECK( isStdVectorBool_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest58
BOOST_AUTO_TEST_CASE( TypeTraitsTest58 )
{
    using Type = std::deque<Byte>;
    constexpr auto isStdDeque_1 = IsStdDeque<Type>;
    BOOST_CHECK( isStdDeque_1 == true );
    constexpr auto isStdDeque_1b = Core::Internal::IsStdDequeImpl<Type>;
    BOOST_CHECK( isStdDeque_1b == true );

    constexpr auto isStdDeque_2 = IsStdDeque<Type&>;
    BOOST_CHECK( isStdDeque_2 == true );
    constexpr auto isStdDeque_2b = Core::Internal::IsStdDequeImpl<Type&>;
    BOOST_CHECK( isStdDeque_2b == false );

    constexpr auto isStdDeque_3 = IsStdDeque<Type&&>;
    BOOST_CHECK( isStdDeque_3 == true );
    constexpr auto isStdDeque_3b = Core::Internal::IsStdDequeImpl<Type&&>;
    BOOST_CHECK( isStdDeque_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest59
BOOST_AUTO_TEST_CASE( TypeTraitsTest59 )
{
    using Type = std::forward_list<Byte>;
    constexpr auto isStdForwardList_1 = IsStdForwardList<Type>;
    BOOST_CHECK( isStdForwardList_1 == true );
    constexpr auto isStdForwardList_1b = Core::Internal::IsStdForwardListImpl<Type>;
    BOOST_CHECK( isStdForwardList_1b == true );

    constexpr auto isStdForwardList_2 = IsStdForwardList<Type&>;
    BOOST_CHECK( isStdForwardList_2 == true );
    constexpr auto isStdForwardList_2b = Core::Internal::IsStdForwardListImpl<Type&>;
    BOOST_CHECK( isStdForwardList_2b == false );

    constexpr auto isStdForwardList_3 = IsStdForwardList<Type&&>;
    BOOST_CHECK( isStdForwardList_3 == true );
    constexpr auto isStdForwardList_3b = Core::Internal::IsStdForwardListImpl<Type&&>;
    BOOST_CHECK( isStdForwardList_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest60
BOOST_AUTO_TEST_CASE( TypeTraitsTest60 )
{
    using Type = std::list<Byte>;
    constexpr auto isStdList_1 = IsStdList<Type>;
    BOOST_CHECK( isStdList_1 == true );
    constexpr auto isStdList_1b = Core::Internal::IsStdListImpl<Type>;
    BOOST_CHECK( isStdList_1b == true );

    constexpr auto isStdList_2 = IsStdList<Type&>;
    BOOST_CHECK( isStdList_2 == true );
    constexpr auto isStdList_2b = Core::Internal::IsStdListImpl<Type&>;
    BOOST_CHECK( isStdList_2b == false );

    constexpr auto isStdList_3 = IsStdList<Type&&>;
    BOOST_CHECK( isStdList_3 == true );
    constexpr auto isStdList_3b = Core::Internal::IsStdListImpl<Type&&>;
    BOOST_CHECK( isStdList_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest61
BOOST_AUTO_TEST_CASE( TypeTraitsTest61 )
{
    using Type = std::set<Byte>;
    constexpr auto isStdSet_1 = IsStdSet<Type>;
    BOOST_CHECK( isStdSet_1 == true );
    constexpr auto isStdSet_1b = Core::Internal::IsStdSetImpl<Type>;
    BOOST_CHECK( isStdSet_1b == true );

    constexpr auto isStdSet_2 = IsStdSet<Type&>;
    BOOST_CHECK( isStdSet_2 == true );
    constexpr auto isStdSet_2b = Core::Internal::IsStdSetImpl<Type&>;
    BOOST_CHECK( isStdSet_2b == false );

    constexpr auto isStdSet_3 = IsStdSet<Type&&>;
    BOOST_CHECK( isStdSet_3 == true );
    constexpr auto isStdSet_3b = Core::Internal::IsStdSetImpl<Type&&>;
    BOOST_CHECK( isStdSet_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest62
BOOST_AUTO_TEST_CASE( TypeTraitsTest62 )
{
    using Type = std::map<Byte,std::string>;
    constexpr auto isStdMap_1 = IsStdMap<Type>;
    BOOST_CHECK( isStdMap_1 == true );
    constexpr auto isStdMap_1b = Core::Internal::IsStdMapImpl<Type>;
    BOOST_CHECK( isStdMap_1b == true );

    constexpr auto isStdMap_2 = IsStdMap<Type&>;
    BOOST_CHECK( isStdMap_2 == true );
    constexpr auto isStdMap_2b = Core::Internal::IsStdMapImpl<Type&>;
    BOOST_CHECK( isStdMap_2b == false );

    constexpr auto isStdMap_3 = IsStdMap<Type&&>;
    BOOST_CHECK( isStdMap_3 == true );
    constexpr auto isStdMap_3b = Core::Internal::IsStdMapImpl<Type&&>;
    BOOST_CHECK( isStdMap_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest63
BOOST_AUTO_TEST_CASE( TypeTraitsTest63 )
{
    using Type = std::multiset<Byte>;
    constexpr auto isStdMultiset_1 = IsStdMultiset<Type>;
    BOOST_CHECK( isStdMultiset_1 == true );
    constexpr auto isStdMultiset_1b = Core::Internal::IsStdMultisetImpl<Type>;
    BOOST_CHECK( isStdMultiset_1b == true );

    constexpr auto isStdMultiset_2 = IsStdMultiset<Type&>;
    BOOST_CHECK( isStdMultiset_2 == true );
    constexpr auto isStdMultiset_2b = Core::Internal::IsStdMultisetImpl<Type&>;
    BOOST_CHECK( isStdMultiset_2b == false );

    constexpr auto isStdMultiset_3 = IsStdMultiset<Type&&>;
    BOOST_CHECK( isStdMultiset_3 == true );
    constexpr auto isStdMultiset_3b = Core::Internal::IsStdMultisetImpl<Type&&>;
    BOOST_CHECK( isStdMultiset_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest64
BOOST_AUTO_TEST_CASE( TypeTraitsTest64 )
{
    using Type = std::multimap<Byte, std::string>;
    constexpr auto isStdMultimap_1 = IsStdMultimap<Type>;
    BOOST_CHECK( isStdMultimap_1 == true );
    constexpr auto isStdMultimap_1b = Core::Internal::IsStdMultimapImpl<Type>;
    BOOST_CHECK( isStdMultimap_1b == true );

    constexpr auto isStdMultimap_2 = IsStdMultimap<Type&>;
    BOOST_CHECK( isStdMultimap_2 == true );
    constexpr auto isStdMultimap_2b = Core::Internal::IsStdMultimapImpl<Type&>;
    BOOST_CHECK( isStdMultimap_2b == false );

    constexpr auto isStdMultimap_3 = IsStdMultimap<Type&&>;
    BOOST_CHECK( isStdMultimap_3 == true );
    constexpr auto isStdMultimap_3b = Core::Internal::IsStdMultimapImpl<Type&&>;
    BOOST_CHECK( isStdMultimap_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest65
BOOST_AUTO_TEST_CASE( TypeTraitsTest65 )
{
    using Type = std::stack<Byte>;
    constexpr auto isStdStack_1 = IsStdStack<Type>;
    BOOST_CHECK( isStdStack_1 == true );
    constexpr auto isStdStack_1b = Core::Internal::IsStdStackImpl<Type>;
    BOOST_CHECK( isStdStack_1b == true );

    constexpr auto isStdStack_2 = IsStdStack<Type&>;
    BOOST_CHECK( isStdStack_2 == true );
    constexpr auto isStdStack_2b = Core::Internal::IsStdStackImpl<Type&>;
    BOOST_CHECK( isStdStack_2b == false );

    constexpr auto isStdStack_3 = IsStdStack<Type&&>;
    BOOST_CHECK( isStdStack_3 == true );
    constexpr auto isStdStack_3b = Core::Internal::IsStdStackImpl<Type&&>;
    BOOST_CHECK( isStdStack_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest66
BOOST_AUTO_TEST_CASE( TypeTraitsTest66 )
{
    using Type = std::queue<Byte>;
    constexpr auto isStdQueue_1 = IsStdQueue<Type>;
    BOOST_CHECK( isStdQueue_1 == true );
    constexpr auto isStdQueue_1b = Core::Internal::IsStdQueueImpl<Type>;
    BOOST_CHECK( isStdQueue_1b == true );

    constexpr auto isStdQueue_2 = IsStdQueue<Type&>;
    BOOST_CHECK( isStdQueue_2 == true );
    constexpr auto isStdQueue_2b = Core::Internal::IsStdQueueImpl<Type&>;
    BOOST_CHECK( isStdQueue_2b == false );

    constexpr auto isStdQueue_3 = IsStdQueue<Type&&>;
    BOOST_CHECK( isStdQueue_3 == true );
    constexpr auto isStdQueue_3b = Core::Internal::IsStdQueueImpl<Type&&>;
    BOOST_CHECK( isStdQueue_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest67
BOOST_AUTO_TEST_CASE( TypeTraitsTest67 )
{
    using Type = std::priority_queue<Byte>;
    constexpr auto isStdPriorityQueue_1 = IsStdPriorityQueue<Type>;
    BOOST_CHECK( isStdPriorityQueue_1 == true );
    constexpr auto isStdPriorityQueue_1b = Core::Internal::IsStdPriorityQueueImpl<Type>;
    BOOST_CHECK( isStdPriorityQueue_1b == true );

    constexpr auto isStdPriorityQueue_2 = IsStdPriorityQueue<Type&>;
    BOOST_CHECK( isStdPriorityQueue_2 == true );
    constexpr auto isStdPriorityQueue_2b = Core::Internal::IsStdPriorityQueueImpl<Type&>;
    BOOST_CHECK( isStdPriorityQueue_2b == false );

    constexpr auto isStdPriorityQueue_3 = IsStdPriorityQueue<Type&&>;
    BOOST_CHECK( isStdPriorityQueue_3 == true );
    constexpr auto isStdPriorityQueue_3b = Core::Internal::IsStdPriorityQueueImpl<Type&&>;
    BOOST_CHECK( isStdPriorityQueue_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest68
BOOST_AUTO_TEST_CASE( TypeTraitsTest68 )
{
    using Type = std::span<Byte>;
    constexpr auto isStdSpan_1 = IsStdSpan<Type>;
    BOOST_CHECK( isStdSpan_1 == true );
    constexpr auto isStdSpan_1b = Core::Internal::IsStdSpanImpl<Type>;
    BOOST_CHECK( isStdSpan_1b == true );

    constexpr auto isStdSpan_2 = IsStdSpan<Type&>;
    BOOST_CHECK( isStdSpan_2 == true );
    constexpr auto isStdSpan_2b = Core::Internal::IsStdSpanImpl<Type&>;
    BOOST_CHECK( isStdSpan_2b == false );

    constexpr auto isStdSpan_3 = IsStdSpan<Type&&>;
    BOOST_CHECK( isStdSpan_3 == true );
    constexpr auto isStdSpan_3b = Core::Internal::IsStdSpanImpl<Type&&>;
    BOOST_CHECK( isStdSpan_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest69
BOOST_AUTO_TEST_CASE( TypeTraitsTest69 )
{
    using Type = std::string;
    constexpr auto isStdBasicString_1 = IsStdBasicString<Type>;
    BOOST_CHECK( isStdBasicString_1 == true );
    constexpr auto isStdBasicString_1b = Core::Internal::IsStdBasicStringImpl<Type>;
    BOOST_CHECK( isStdBasicString_1b == true );

    constexpr auto isStdBasicString_2 = IsStdBasicString<Type&>;
    BOOST_CHECK( isStdBasicString_2 == true );
    constexpr auto isStdBasicString_2b = Core::Internal::IsStdBasicStringImpl<Type&>;
    BOOST_CHECK( isStdBasicString_2b == false );

    constexpr auto isStdBasicString_3 = IsStdBasicString<Type&&>;
    BOOST_CHECK( isStdBasicString_3 == true );
    constexpr auto isStdBasicString_3b = Core::Internal::IsStdBasicStringImpl<Type&&>;
    BOOST_CHECK( isStdBasicString_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest70
BOOST_AUTO_TEST_CASE( TypeTraitsTest70 )
{
    using Type = std::string_view;
    constexpr auto isStdBasicStringView_1 = IsStdBasicStringView<Type>;
    BOOST_CHECK( isStdBasicStringView_1 == true );
    constexpr auto isStdBasicStringView_1b = Core::Internal::IsStdBasicStringViewImpl<Type>;
    BOOST_CHECK( isStdBasicStringView_1b == true );

    constexpr auto isStdBasicStringView_2 = IsStdBasicStringView<Type&>;
    BOOST_CHECK( isStdBasicStringView_2 == true );
    constexpr auto isStdBasicStringView_2b = Core::Internal::IsStdBasicStringViewImpl<Type&>;
    BOOST_CHECK( isStdBasicStringView_2b == false );

    constexpr auto isStdBasicStringView_3 = IsStdBasicStringView<Type&&>;
    BOOST_CHECK( isStdBasicStringView_3 == true );
    constexpr auto isStdBasicStringView_3b = Core::Internal::IsStdBasicStringViewImpl<Type&&>;
    BOOST_CHECK( isStdBasicStringView_3b == false );
}


// --run_test=TraitsTests/TypeTraitsTest72
BOOST_AUTO_TEST_CASE( TypeTraitsTest72 )
{
    using Type = Vector<Byte>;
    constexpr auto isCoreVector_1 = IsCoreVector<Type>;
    BOOST_CHECK( isCoreVector_1 == true );
    constexpr auto isCoreVector_1b = Core::Internal::IsCoreVectorImpl<Type>;
    BOOST_CHECK( isCoreVector_1b == true );

    constexpr auto isCoreVector_2 = IsCoreVector<Type&>;
    BOOST_CHECK( isCoreVector_2 == true );
    constexpr auto isCoreVector_2b = Core::Internal::IsCoreVectorImpl<Type&>;
    BOOST_CHECK( isCoreVector_2b == false );

    constexpr auto isCoreVector_3 = IsCoreVector<Type&&>;
    BOOST_CHECK( isCoreVector_3 == true );
    constexpr auto isCoreVector_3b = Core::Internal::IsCoreVectorImpl<Type&&>;
    BOOST_CHECK( isCoreVector_3b == false );
}

// --run_test=TraitsTests/TypeTraitsTest75
BOOST_AUTO_TEST_CASE( TypeTraitsTest75 )
{
    using Type_1 = std::array<Byte,2>;
    constexpr auto isContainer_1 = IsContainer<Type_1>;
    BOOST_CHECK( isContainer_1 == true );

    using Type_2 = std::vector<Byte>;
    constexpr auto isContainer_2 = IsContainer<Type_2>;
    BOOST_CHECK( isContainer_2 == true );

    using Type_3 = std::vector<bool>;
    constexpr auto isContainer_3 = IsContainer<Type_3>;
    BOOST_CHECK( isContainer_3 == true );

    using Type_4 = std::deque<Byte>;
    constexpr auto isContainer_4 = IsContainer<Type_4>;
    BOOST_CHECK( isContainer_4 == true );

    using Type_5 = Vector<Byte>;
    constexpr auto isContainer_5 = IsContainer<Type_5>;
    BOOST_CHECK( isContainer_5 == true );


}

// --run_test=TraitsTests/TypeTraitsTest76
BOOST_AUTO_TEST_CASE( TypeTraitsTest76 )
{
    using Type = std::optional<Byte>;
    constexpr auto result = IsStdOptional<Type>;
    BOOST_CHECK( result == true );
}

// --run_test=TraitsTests/TypeTraitsTest77
BOOST_AUTO_TEST_CASE( TypeTraitsTest77 )
{
    using Type = std::any;
    constexpr auto result = IsStdAny<Type>;
    BOOST_CHECK( result == true );
}
// --run_test=TraitsTests/TypeTraitsTest78
BOOST_AUTO_TEST_CASE( TypeTraitsTest78 )
{
    using Type = std::shared_ptr<Byte>;
    constexpr auto result = IsStdSharedPtr<Type>;
    BOOST_CHECK( result == true );
}

// --run_test=TraitsTests/TypeTraitsTest79
BOOST_AUTO_TEST_CASE( TypeTraitsTest79 )
{
    using Type = std::unique_ptr<Byte>;
    constexpr auto result = IsStdUniquePtr<Type>;
    BOOST_CHECK( result == true );
}

// --run_test=TraitsTests/TypeTraitsTest80
BOOST_AUTO_TEST_CASE( TypeTraitsTest80 )
{
    using Type = std::pair<Byte,bool>;
    constexpr auto result = IsStdPair<Type>;
    BOOST_CHECK( result == true );
}

// --run_test=TraitsTests/TypeTraitsTest81
BOOST_AUTO_TEST_CASE( TypeTraitsTest81 )
{
    using Type = std::tuple<Byte, bool>;
    constexpr auto result = IsStdTuple<Type>;
    BOOST_CHECK( result == true );
}

// --run_test=TraitsTests/TypeTraitsTest82
BOOST_AUTO_TEST_CASE( TypeTraitsTest82 )
{
    using Type = std::variant<Byte, bool>;
    constexpr auto result = IsStdVariant<Type>;
    BOOST_CHECK( result == true );
}

// --run_test=TraitsTests/TypeTraitsTest83
BOOST_AUTO_TEST_CASE( TypeTraitsTest83 )
{
    using Type = Tuple<Byte, bool>;
    constexpr auto result = IsCoreTuple<Type>;
    BOOST_CHECK( result == true );
}

// --run_test=TraitsTests/TypeTraitsTest84
BOOST_AUTO_TEST_CASE( TypeTraitsTest84 )
{
    using Type = Tuple<Byte, bool>;
    constexpr auto result = IsTupleType<Type>;
    BOOST_CHECK( result == true );
}

// --run_test=TraitsTests/TypeTraitsTest85
BOOST_AUTO_TEST_CASE( TypeTraitsTest85 )
{
    BOOST_CHECK( IsBasicType<bool> );
    BOOST_CHECK( IsBasicType<bool&> );
    BOOST_CHECK( IsBasicType<const bool&> );
    BOOST_CHECK( IsBasicType<const volatile bool&> );
    BOOST_CHECK( IsBasicType<volatile const bool&& > );

    BOOST_CHECK( IsBasicType<Guid> );
    BOOST_CHECK( IsBasicType<Guid&> );
    BOOST_CHECK( IsBasicType<const Guid&> );
    BOOST_CHECK( IsBasicType<const volatile Guid&> );
    BOOST_CHECK( IsBasicType<volatile const Guid&& > );

}

// --run_test=TraitsTests/TypeTraitsTest86
BOOST_AUTO_TEST_CASE( TypeTraitsTest86 )
{
    using Type = std::complex<double>;
    constexpr auto result = IsStdComplex<Type>;
    BOOST_CHECK( result == true );
}


// --run_test=TraitsTests/TypeTraitsTest87
BOOST_AUTO_TEST_CASE( TypeTraitsTest87 )
{
    using Type = std::tuple<char, Int32>;
    constexpr auto isFixedSize = Types::IsFixedSize<Type>::value;
    BOOST_CHECK( isFixedSize == true );
    constexpr auto byteSize = Types::PackedSizeOf<Type>::value;
    BOOST_CHECK( byteSize == 5 );
}

// --run_test=TraitsTests/TypeTraitsTest88
BOOST_AUTO_TEST_CASE( TypeTraitsTest88 )
{
    using Type = std::tuple<char, std::vector<Byte>>;
    constexpr auto isFixedSize = Types::IsFixedSize<Type>::value;
    BOOST_CHECK( isFixedSize == false );
}

// --run_test=TraitsTests/TypeTraitsTest89
BOOST_AUTO_TEST_CASE( TypeTraitsTest89 )
{
    using Type = std::tuple<char, std::array<Byte, 2>>;
    constexpr auto isFixedSize = Types::IsFixedSize<Type>::value;
    BOOST_CHECK( isFixedSize == true );
    constexpr auto byteSize = Types::PackedSizeOf<Type>::value;
    BOOST_CHECK( byteSize == 3 );
}


// --run_test=TraitsTests/TypeTraitsTest90
BOOST_AUTO_TEST_CASE( TypeTraitsTest90 )
{
    using Type = std::vector<Byte>;
    constexpr auto isFixedSize = Types::IsFixedSize<Type>::value;
    BOOST_CHECK( isFixedSize == false );
}

// --run_test=TraitsTests/TypeTraitsTest91
BOOST_AUTO_TEST_CASE( TypeTraitsTest91 )
{
    using Type = std::optional<std::vector<Byte>>;
    constexpr auto isFixedSize = Types::IsFixedSize<Type>::value;
    BOOST_CHECK( isFixedSize == false );
    constexpr auto byteSize = Types::PackedSizeOf<Type>::value;
    BOOST_CHECK( byteSize == 0 );
}

// --run_test=TraitsTests/TypeTraitsTest92
BOOST_AUTO_TEST_CASE( TypeTraitsTest92 )
{
    using Type = std::tuple<char, std::array<std::optional<std::vector<Byte>>, 2>>;
    constexpr auto isFixedSize = Types::IsFixedSize<Type>::value;
    BOOST_CHECK( isFixedSize == false );
    constexpr auto byteSize = Types::PackedSizeOf<Type>::value;
    BOOST_CHECK( byteSize == 0 );
}

// --run_test=TraitsTests/TypeTraitsTest93
BOOST_AUTO_TEST_CASE( TypeTraitsTest93 )
{
    using Type_2 = Tuple<char, std::array<std::optional<std::array<Byte, 5>>, 2>>;
    constexpr size_t expectedSize = sizeof( Type_2 );
    constexpr size_t sizeOfBool = sizeof( bool );

    using Type = std::tuple<char, std::array<std::optional<std::array<Byte, 5>>, 2>>;
    constexpr auto isFixedSize = Types::IsFixedSize<Type>::value;
    BOOST_CHECK( isFixedSize == true );
    constexpr auto byteSize = Types::PackedSizeOf<Type>::value;
    BOOST_CHECK( byteSize == expectedSize );
}

// --run_test=TraitsTests/TypeTraitsTest94
BOOST_AUTO_TEST_CASE( TypeTraitsTest94 )
{
    using Type = std::tuple<char, std::array<std::optional<std::array<Byte, 5>>, 2>>;
    constexpr auto isSupportedType = Types::IsSupportedType<Type>::value;
    BOOST_CHECK( isSupportedType == true );
}

// --run_test=TraitsTests/TypeTraitsTest95
BOOST_AUTO_TEST_CASE( TypeTraitsTest95 )
{
    using Type = std::tuple<char, std::array<std::optional<std::array<FILETIME, 5>>, 2>>;
    constexpr auto isSupportedType = Types::IsSupportedType<Type>::value;
    BOOST_CHECK( isSupportedType == false );
}

// --run_test=TraitsTests/TypeTraitsTest96
BOOST_AUTO_TEST_CASE( TypeTraitsTest96 )
{
    using Type = std::tuple<char, std::array<std::optional<std::array<Byte, 5>>, 2>>;
    constexpr auto isSupportedType = Types::IsSupportedType<Type>::value;
    BOOST_CHECK( isSupportedType == true );
}

// --run_test=TraitsTests/TypeTraitsTest97
BOOST_AUTO_TEST_CASE( TypeTraitsTest97 )
{
    constexpr bool isSupported = TypeListTest::IsSupported( );
    BOOST_CHECK( isSupported == true );

    constexpr bool isFixedSize = TypeListTest::IsFixedSize( );
    BOOST_CHECK( isFixedSize == true );

    constexpr size_t packedSize = TypeListTest::PackedSizeOf( );
    BOOST_CHECK( packedSize == 0 );
}

// --run_test=TraitsTests/TypeTraitsTest98
BOOST_AUTO_TEST_CASE( TypeTraitsTest98 )
{
    constexpr char charArrayArg[4] = {};

    constexpr bool isSupported = TypeListTest::IsSupported( charArrayArg );
    BOOST_CHECK( isSupported == true );

    constexpr bool isFixedSize = TypeListTest::IsFixedSize( charArrayArg );
    BOOST_CHECK( isFixedSize == true );

    constexpr size_t packedSize = TypeListTest::PackedSizeOf( charArrayArg );
    BOOST_CHECK( packedSize == 4 );
}

// --run_test=TraitsTests/TypeTraitsTest99
BOOST_AUTO_TEST_CASE( TypeTraitsTest99 )
{
    constexpr char charArg = {};

    constexpr bool isSupported = TypeListTest::IsSupported( charArg );
    BOOST_CHECK( isSupported == true );

    constexpr bool isFixedSize = TypeListTest::IsFixedSize( charArg );
    BOOST_CHECK( isFixedSize == true );

    constexpr size_t packedSize = TypeListTest::PackedSizeOf( charArg );
    BOOST_CHECK( packedSize == 1 );
}

// --run_test=TraitsTests/TypeTraitsTest100
BOOST_AUTO_TEST_CASE( TypeTraitsTest100 )
{
    constexpr char charArg = {};
    constexpr double doubleArg = 1.0;

    constexpr bool isSupported = TypeListTest::IsSupported( charArg, doubleArg );
    BOOST_CHECK( isSupported == true );

    constexpr bool isFixedSize = TypeListTest::IsFixedSize( charArg, doubleArg );
    BOOST_CHECK( isFixedSize == true );

    constexpr size_t packedSize = TypeListTest::PackedSizeOf( charArg, doubleArg );
    BOOST_CHECK( packedSize == 9 );
}

// --run_test=TraitsTests/TypeTraitsTest101
BOOST_AUTO_TEST_CASE( TypeTraitsTest101 )
{
    constexpr char charArg = {};
    constexpr double doubleArg = 1.0;

    constexpr bool isSupported = TypeListTest::IsSupported( charArg, doubleArg, "Hello" );
    BOOST_CHECK( isSupported == true );

    constexpr bool isFixedSize = TypeListTest::IsFixedSize( charArg, doubleArg, "Hello" );
    BOOST_CHECK( isFixedSize == true );

    constexpr size_t packedSize = TypeListTest::PackedSizeOf( charArg, doubleArg, "Hello" );
    BOOST_CHECK( packedSize == 15 );
}



// --run_test=TraitsTests/TypeTraitsTest105
BOOST_AUTO_TEST_CASE( TypeTraitsTest105 )
{
    bool arg1; 
    char arg2; 
    SByte arg3; 
    Byte arg4; 
    wchar_t arg5; 
    Int16 arg6; 
    UInt16 arg7; 
    Int32 arg8; 
    long arg9;
    UInt32 arg10; 
    unsigned long arg11; 
    Int64 arg12; 
    UInt64 arg13; 
    float arg14; 
    double arg15; 
    TimeSpan arg16; 
    DateTime arg17; 
    Currency arg18; 
    Guid arg19;

    constexpr bool isSupported = TypeListTest::IsSupported( arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19 );
    BOOST_CHECK( isSupported == true );

    constexpr bool isFixedSize = TypeListTest::IsFixedSize( arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19 );
    BOOST_CHECK( isFixedSize == true );

    constexpr size_t packedSize = TypeListTest::PackedSizeOf( arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19 );
    BOOST_CHECK( packedSize == 94 );
}

// --run_test=TraitsTests/TypeTraitsTest106
BOOST_AUTO_TEST_CASE( TypeTraitsTest106 )
{
    bool arg1 = 1;
    char arg2 = 2;
    SByte arg3 = 3;
    Byte arg4 = 4;
    wchar_t arg5 = 5;
    Int16 arg6 = 6;
    UInt16 arg7 = 7;
    Int32 arg8 = 8;
    long arg9 = 9;
    UInt32 arg10 = 10;
    unsigned long arg11 = 11;
    Int64 arg12 = 12;
    UInt64 arg13 = 13;
    float arg14 = 14;
    double arg15 = 15;
    TimeSpan arg16(16LL);
    DateTime arg17(17LL);
    Currency arg18(18);
    Guid arg19;

    constexpr auto byteSize = Types::SizeOf( arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19 );
    BOOST_CHECK( byteSize == 94 );
}


// --run_test=TraitsTests/TypeTraitsTest107
BOOST_AUTO_TEST_CASE( TypeTraitsTest107 )
{
    using Type = Tuple<Int32, Int32>;
    Vector<Type> elements;
    elements.emplace_back( 1, 1 );
    elements.emplace_back( 2, 2 );
    elements.emplace_back( 3, 3 );

    auto byteSize = Types::SizeOf( elements );
    BOOST_CHECK( byteSize == 24 );

}

// --run_test=TraitsTests/TypeTraitsTest108
BOOST_AUTO_TEST_CASE( TypeTraitsTest108 )
{
    using Type = std::tuple<Int32, Int32>;
    using VectorT1 = std::vector<Type>;
    using VectorT2 = std::vector<VectorT1>;

    VectorT1 vectorT1_1;
    vectorT1_1.emplace_back( 1, 1 );
    vectorT1_1.emplace_back( 2, 2 );
    vectorT1_1.emplace_back( 3, 3 );
    VectorT1 vectorT1_2;
    vectorT1_2.emplace_back( 1, 1 );
    vectorT1_2.emplace_back( 2, 2 );
    vectorT1_2.emplace_back( 3, 3 );
    VectorT1 vectorT1_3;
    vectorT1_3.emplace_back( 1, 1 );
    vectorT1_3.emplace_back( 2, 2 );
    vectorT1_3.emplace_back( 3, 3 );

    VectorT2 elements;
    elements.emplace_back( std::move( vectorT1_1 ) );
    elements.emplace_back( std::move( vectorT1_2 ) );
    elements.emplace_back( std::move( vectorT1_3 ) );

    auto byteSize = Types::SizeOf( elements );
    BOOST_CHECK( byteSize == 72 );

}






// --run_test=TraitsTests/HasTypeListTest1
BOOST_AUTO_TEST_CASE( HasTypeListTest1 )
{
    constexpr bool aHasTypeList = Types::HasTypeList<TimeseriesPointA>;
    BOOST_CHECK( aHasTypeList );
    constexpr bool bHasTypeList = Types::HasTypeList<TimeseriesPointB>;
    BOOST_CHECK( bHasTypeList == false );
}

// --run_test=TraitsTests/HasTypeAdapterTest1
BOOST_AUTO_TEST_CASE( HasTypeAdapterTest1 )
{
    constexpr bool aHasTypeAdapter = Types::HasTypeAdapter<TimeseriesPointA>;
    BOOST_CHECK( aHasTypeAdapter == false );
    constexpr bool bHasTypeAdapter = Types::HasTypeAdapter<TimeseriesPointB>;
    BOOST_CHECK( bHasTypeAdapter == false );

    constexpr bool cHasTypeAdapter = Types::HasTypeAdapter<TimeseriesPointC>;
    BOOST_CHECK( cHasTypeAdapter == true );

}

// --run_test=TraitsTests/AdaptedTypeTraitsTest1
BOOST_AUTO_TEST_CASE( AdaptedTypeTraitsTest1 )
{
    using TimeseriesPointATraits = Types::TypeTraits<TimeseriesPointA>;
    BOOST_CHECK( TimeseriesPointATraits::IsAdapted );
    BOOST_CHECK( TimeseriesPointATraits::Count == 3 );

    using TimeseriesPointBTraits = Types::TypeTraits<TimeseriesPointB>;
    BOOST_CHECK( TimeseriesPointBTraits::IsAdapted == false );

    using TimeseriesPointCTraits = Types::TypeTraits<TimeseriesPointC>;
    BOOST_CHECK( TimeseriesPointCTraits::IsAdapted );
    BOOST_CHECK( TimeseriesPointCTraits::Count == 3 );
}

// --run_test=TraitsTests/WideStringTypeTest1
BOOST_AUTO_TEST_CASE( WideStringTypeTest1 )
{
    constexpr bool wstringIsWideStringType = WideStringType<WideString>;
    constexpr bool SysStringIsWideStringType = WideStringType<SysString>;
    constexpr bool ComStringIsWideStringType = WideStringType<ComString>;

    BOOST_CHECK( wstringIsWideStringType );
    BOOST_CHECK( SysStringIsWideStringType );
    BOOST_CHECK( ComStringIsWideStringType );

}




BOOST_AUTO_TEST_SUITE_END( )