#pragma once
#ifndef __HCCTRAITS_H__
#define __HCCTRAITS_H__
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

#include <HCCDef.h>
#include <HCCMeta.h>

namespace Harlinn::Common::Core
{
    static_assert( sizeof( bool ) == 1, "Some of the code expects bool to have a size of 1" );

    template<typename ...Types_>
    class Tuple;

    template<typename T>
    class Vector;

    template <typename ...Types>
    using TypeList = Meta::List<Types...>;


    // true if and only if Type is a specialization of Template
    template <class Type, template <class...> class Template>
    constexpr bool IsSpecializationOf_v = false;
    template <template <class...> class Template, class... Types>
    constexpr bool IsSpecializationOf_v<Template<Types...>, Template> = true;

    template <class Type, template <class...> class Template>
    struct IsSpecializationOf : std::bool_constant<IsSpecializationOf_v<Type, Template>>
    { };
    
    template<typename Type, typename... TypeList>
    using IsAnyOf = std::disjunction<std::is_same<Type, TypeList>...>;

    template<typename Type, typename... TypeList>
    inline constexpr bool IsAnyOf_v = IsAnyOf<Type, TypeList...>::value;


    template<typename T>
    constexpr bool IsPointer = std::is_same_v< std::remove_const_t<std::remove_reference_t<std::remove_volatile_t<T>>>, std::remove_pointer_t<std::remove_const_t<std::remove_reference_t<std::remove_volatile_t<T>>>>> == false;


    template<typename T>
    constexpr bool IsConst = std::is_same_v<std::remove_reference_t<std::remove_volatile_t<T>>, std::remove_const_t<std::remove_reference_t<std::remove_volatile_t<T>>>> == false;

    template<typename T>
    constexpr bool IsVolatile = std::is_same_v<std::remove_reference_t<std::remove_const_t<T>>, std::remove_volatile_t<std::remove_reference_t<std::remove_const_t<T>>>> == false;

    template<typename T>
    inline constexpr bool IsReference = std::is_same_v< std::remove_volatile_t<std::remove_const_t<T>> , std::remove_reference_t<std::remove_volatile_t<std::remove_const_t<T>>>> == false;

    template<typename T>
    constexpr bool IsArray = std::is_array_v<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdArrayImpl = false;

        template<typename T, size_t N>
        constexpr bool IsStdArrayImpl<std::array<T, N>> = true;
    }
    template<typename T>
    constexpr bool IsStdArray = Core::Internal::IsStdArrayImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdVectorImpl = false;

        template<typename T, typename A>
        constexpr bool IsStdVectorImpl<std::vector<T, A>> = true;
    }
    template<typename T>
    constexpr bool IsStdVector = Core::Internal::IsStdVectorImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdVectorBoolImpl = false;

        template<typename T, typename A>
        constexpr bool IsStdVectorBoolImpl<std::vector<T, A>> = std::is_same_v<T,bool>;
    }
    template<typename T>
    constexpr bool IsStdVectorBool = Core::Internal::IsStdVectorBoolImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdDequeImpl = false;

        template<typename T, typename A>
        constexpr bool IsStdDequeImpl<std::deque<T, A>> = true;
    }
    template<typename T>
    constexpr bool IsStdDeque = Core::Internal::IsStdDequeImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdForwardListImpl = false;

        template<typename T, typename A>
        constexpr bool IsStdForwardListImpl<std::forward_list<T, A>> = true;
    }
    template<typename T>
    constexpr bool IsStdForwardList = Core::Internal::IsStdForwardListImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdListImpl = false;

        template<typename T, typename A>
        constexpr bool IsStdListImpl<std::list<T, A>> = true;
    }
    template<typename T>
    constexpr bool IsStdList = Core::Internal::IsStdListImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdSetImpl = false;

        template<typename Key, typename Compare, typename Allocator>
        constexpr bool IsStdSetImpl<std::set<Key, Compare, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdSet = Core::Internal::IsStdSetImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdMapImpl = false;

        template<typename Key, typename Value, typename Compare, typename Allocator>
        constexpr bool IsStdMapImpl<std::map<Key, Value, Compare, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdMap = Core::Internal::IsStdMapImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdMultisetImpl = false;

        template<typename Key, typename Compare, typename Allocator>
        constexpr bool IsStdMultisetImpl<std::multiset<Key, Compare, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdMultiset = Core::Internal::IsStdMultisetImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdMultimapImpl = false;

        template<typename Key, typename Value, typename Compare, typename Allocator>
        constexpr bool IsStdMultimapImpl<std::multimap<Key, Value, Compare, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdMultimap = Core::Internal::IsStdMultimapImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdUnorderedSetImpl = false;

        template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
        constexpr bool IsStdUnorderedSetImpl<std::unordered_set<Key, Hash, KeyEqual, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdUnorderedSet = Core::Internal::IsStdUnorderedSetImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdUnorderedMapImpl = false;

        template<typename Key, typename Value, typename Hash, typename KeyEqual, typename Allocator>
        constexpr bool IsStdUnorderedMapImpl<std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdUnorderedMap = Core::Internal::IsStdUnorderedMapImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdUnorderedMultisetImpl = false;

        template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
        constexpr bool IsStdUnorderedMultisetImpl<std::unordered_multiset<Key, Hash, KeyEqual, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdUnorderedMultiset = Core::Internal::IsStdUnorderedMultisetImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdUnorderedMultimapImpl = false;

        template<typename Key, typename Value, typename Hash, typename KeyEqual, typename Allocator>
        constexpr bool IsStdUnorderedMultimapImpl<std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdUnorderedMultimap = Core::Internal::IsStdUnorderedMultimapImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdStackImpl = false;

        template<typename T, typename Container>
        constexpr bool IsStdStackImpl<std::stack<T, Container>> = true;
    }
    template<typename T>
    constexpr bool IsStdStack = Core::Internal::IsStdStackImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdQueueImpl = false;

        template<typename T, typename Container>
        constexpr bool IsStdQueueImpl<std::queue<T, Container>> = true;
    }
    template<typename T>
    constexpr bool IsStdQueue = Core::Internal::IsStdQueueImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdPriorityQueueImpl = false;

        template<typename T, typename Container, typename Compare>
        constexpr bool IsStdPriorityQueueImpl<std::priority_queue<T, Container, Compare>> = true;
    }
    template<typename T>
    constexpr bool IsStdPriorityQueue = Core::Internal::IsStdPriorityQueueImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdSpanImpl = false;

        template<typename T, size_t N>
        constexpr bool IsStdSpanImpl<std::span<T, N>> = true;
    }
    template<typename T>
    constexpr bool IsStdSpan = Core::Internal::IsStdSpanImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdBasicStringImpl = false;

        template<typename CharT, typename Traits, typename Allocator>
        constexpr bool IsStdBasicStringImpl<std::basic_string<CharT, Traits, Allocator>> = true;
    }
    template<typename T>
    constexpr bool IsStdBasicString = Core::Internal::IsStdBasicStringImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsBasicStringImpl = false;

        template<typename CharT>
        constexpr bool IsBasicStringImpl<BasicString<CharT>> = true;
    }
    template<typename T>
    constexpr bool IsBasicString = Core::Internal::IsBasicStringImpl<std::remove_cvref_t<T>>;



    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdBasicStringViewImpl = false;

        template<typename CharT, typename Traits>
        constexpr bool IsStdBasicStringViewImpl<std::basic_string_view<CharT, Traits>> = true;
    }
    template<typename T>
    constexpr bool IsStdBasicStringView = Core::Internal::IsStdBasicStringViewImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsBasicStringViewImpl = false;

        template<typename CharT>
        constexpr bool IsBasicStringViewImpl<BasicStringView<CharT>> = true;
    }
    template<typename T>
    constexpr bool IsBasicStringView = Core::Internal::IsBasicStringViewImpl<std::remove_cvref_t<T>>;

    template <class T>
    constexpr bool IsInitializerList = IsSpecializationOf_v<std::remove_cvref_t<T>, std::initializer_list>;
    

    namespace Internal
    {
        template<typename T>
        constexpr bool IsCoreVectorImpl = false;

        template<typename T>
        constexpr bool IsCoreVectorImpl<Vector<T>> = true;
    }
    template<typename T>
    constexpr bool IsCoreVector = Core::Internal::IsCoreVectorImpl<std::remove_cvref_t<T>>;

    template<typename T>
    constexpr bool IsContainer = IsStdArray<T> ||
                                IsStdVector<T> ||
                                IsStdDeque<T> ||
                                IsStdForwardList<T> ||
                                IsStdList<T> ||
                                IsStdSet<T> ||
                                IsStdMap<T> ||
                                IsStdMultiset<T> ||
                                IsStdMultimap<T> ||
                                IsStdUnorderedSet<T> ||
                                IsStdUnorderedMap<T> ||
                                IsStdUnorderedMultiset<T> ||
                                IsStdUnorderedMultimap<T> ||
                                IsStdStack<T> ||
                                IsStdQueue<T> ||
                                IsStdPriorityQueue<T> ||
                                IsStdSpan<T> ||
                                IsStdBasicString<T> ||
                                IsStdBasicStringView<T> ||
                                IsBasicString<T> ||
                                IsBasicStringView<T> ||
                                IsCoreVector<T>;


    template<typename T>
    constexpr bool IsArrayContainer = IsStdArray<T>;

    template<typename T>
    constexpr bool IsVectorContainer = IsStdVector<T> || IsCoreVector<T>;



    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdOptionalImpl = false;

        template<typename T>
        constexpr bool IsStdOptionalImpl<std::optional<T>> = true;
    }
    template<typename T>
    constexpr bool IsStdOptional = Core::Internal::IsStdOptionalImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdAnyImpl = false;

        template<>
        constexpr bool IsStdAnyImpl<std::any> = true;
    }
    template<typename T>
    constexpr bool IsStdAny = Core::Internal::IsStdAnyImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdSharedPtrImpl = false;

        template<typename T>
        constexpr bool IsStdSharedPtrImpl<std::shared_ptr<T>> = true;
    }
    template<typename T>
    constexpr bool IsStdSharedPtr = Core::Internal::IsStdSharedPtrImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdUniquePtrImpl = false;

        template<typename T, typename Deleter>
        constexpr bool IsStdUniquePtrImpl<std::unique_ptr<T, Deleter>> = true;
    }
    template<typename T>
    constexpr bool IsStdUniquePtr = Core::Internal::IsStdUniquePtrImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdPairImpl = false;

        template<typename T1, typename T2 >
        constexpr bool IsStdPairImpl<std::pair<T1,T2> > = true;
    }
    template<typename T>
    constexpr bool IsStdPair = Core::Internal::IsStdPairImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdTupleImpl = false;

        template<typename ...Types>
        constexpr bool IsStdTupleImpl<std::tuple<Types...>> = true;
    }
    template<typename T>
    constexpr bool IsStdTuple = Core::Internal::IsStdTupleImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdVariantImpl = false;

        template<typename ...Types>
        constexpr bool IsStdVariantImpl<std::variant<Types...>> = true;
    }
    template<typename T>
    constexpr bool IsStdVariant = Core::Internal::IsStdVariantImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsCoreTupleImpl = false;

        template<typename ...Types>
        constexpr bool IsCoreTupleImpl<Tuple<Types...>> = true;
    }
    template<typename T>
    constexpr bool IsCoreTuple = Core::Internal::IsCoreTupleImpl<std::remove_cvref_t<T>>;

    template<typename T>
    constexpr bool IsTupleType = IsStdPair<T> || IsStdTuple<T> || IsCoreTuple<T>;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsBasicTypeImpl = IsAnyOf_v<T, bool, char, SByte, Byte, wchar_t, Int16, UInt16, Int32, long, UInt32, unsigned long, Int64, UInt64, float, double, TimeSpan, DateTime, Currency, Guid> || std::is_enum_v<T>;
    }

    template<typename T>
    constexpr bool IsBasicType = Core::Internal::IsBasicTypeImpl<std::remove_cvref_t<T>>;


    template<typename T>
    constexpr bool IsString = std::is_pointer_v<T> && ( std::is_same_v<char, std::remove_cvref_t< std::remove_pointer_t<T>>> || std::is_same_v<wchar_t, std::remove_cvref_t< std::remove_pointer_t<T>>> );

    template<typename T>
    constexpr bool IsCharString = std::is_pointer_v<T> && std::is_same_v<char, std::remove_cvref_t< std::remove_pointer_t<T>>>;
    template<typename T>
    constexpr bool IsWideCharString = std::is_pointer_v<T> && std::is_same_v<wchar_t, std::remove_cvref_t< std::remove_pointer_t<T>>>;



    namespace Internal
    {
        template<typename T>
        constexpr bool IsTypeListImpl = false;

        template<typename ...Types>
        constexpr bool IsTypeListImpl<TypeList<Types...>> = true;
    }
    template<typename T>
    constexpr bool IsTypeList = Core::Internal::IsTypeListImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template <class T>
        struct ToReferenceIfReferenceWrapper
        { 
            using type = T;
        };

        template <class T>
        struct ToReferenceIfReferenceWrapper<std::reference_wrapper<T>>
        { 
            using type = T&;
        };

        // Make a reference to wrapped type
        template <class T>
        using ToReferenceIfReferenceWrapper_t = typename ToReferenceIfReferenceWrapper<std::decay_t<T>>::type;

    }


    template<typename T>
    inline constexpr bool IsComplex = std::is_same_v<std::remove_cvref_t<T>, std::complex<float>> || std::is_same_v<std::remove_cvref_t<T>, std::complex<double>>;

    namespace Internal
    {
        template<typename ...Args>
        struct MakeFloatingPointImpl
        {
            using type = double;
        };

        template<>
        struct MakeFloatingPointImpl<float,float>
        {
            using type = float;
        };
    }

    template<typename S, typename T>
        requires IsArithmetic<S> && IsArithmetic<T>
    using MakeFloatingPoint = typename Internal::MakeFloatingPointImpl< std::remove_cvref_t<S>, std::remove_cvref_t<T> >::type;



    template<typename T>
    inline constexpr std::remove_cvref_t<T> SignMask = 
        std::numeric_limits< std::make_unsigned_t<std::remove_cvref_t<T>> >::max( ) 
        - std::bit_cast<std::make_unsigned_t<std::remove_cvref_t<T>>>( 
            std::numeric_limits< std::make_signed_t< std::remove_cvref_t<T> > >::max( ) );

    template<>
    inline constexpr UInt32 SignMask<float> = 0x80000000UL;

    template<>
    inline constexpr UInt64 SignMask<double> = 0x8000000000000000ULL;

    template<typename T>
    inline constexpr T ValueMask = ~SignMask<T>;

    template<>
    inline constexpr UInt32 ValueMask<float> = 0x7FFFFFFFUL;

    template<>
    inline constexpr UInt64 ValueMask<double> = 0x7FFFFFFFFFFFFFFFULL;


    namespace Internal
    {
        template<typename T>
        constexpr bool IsStdComplexImpl = false;

        template<typename T>
        constexpr bool IsStdComplexImpl<std::complex<T>> = true;
    }
    template<typename T>
    constexpr bool IsStdComplex = Core::Internal::IsStdComplexImpl<std::remove_cvref_t<T>>;

    namespace Internal
    {
        template <size_t>
        struct MakeUnsignedHelper;

        template <>
        struct MakeUnsignedHelper<1>
        {
            using Type = Byte;
        };

        template <>
        struct MakeUnsignedHelper<2>
        {
            using Type = UInt16;
        };

        template <>
        struct MakeUnsignedHelper<4>
        {
            using Type = UInt32;
        };

        template <>
        struct MakeUnsignedHelper<8>
        {
            using Type = UInt64;
        };
    }


    template<typename T>
    using MakeUnsigned = typename Internal::MakeUnsignedHelper< sizeof(T) >::Type;


    template<typename T, typename U = MakeUnsigned< std::remove_cvref_t<T> > >
    inline constexpr U FractionMask = std::numeric_limits<std::remove_cvref_t<T>>::max( );

    template<typename T, typename U = MakeUnsigned< std::remove_cvref_t<T> > >
    inline constexpr U ExponentMask = 0;

    template<>
    inline constexpr UInt32 FractionMask<float, UInt32> = std::bit_cast<UInt32>( 0b00000000011111111111111111111111 );
    template<>
    inline constexpr UInt32 ExponentMask<float, UInt32> = std::bit_cast<UInt32>( 0b01111111100000000000000000000000 );

    template<>
    inline constexpr UInt64 FractionMask<double, UInt64> = std::bit_cast<UInt64>( 0b0000000000001111111111111111111111111111111111111111111111111111 );
    template<>
    inline constexpr UInt64 ExponentMask<double, UInt64> = std::bit_cast<UInt64>( 0b0111111111110000000000000000000000000000000000000000000000000000 );


    template <typename ty1, typename ty2>
    inline constexpr bool size_is_greater_or_equal = sizeof( ty1 ) >= sizeof( ty2 ) ? true : false;


    template <typename ty1, typename ty2>
    inline constexpr bool size_is_greater = sizeof( ty1 ) > sizeof( ty2 ) ? true : false;

    template <typename ty1, typename ty2>
    inline constexpr bool size_is_less = sizeof( ty1 ) < sizeof( ty2 ) ? true : false;

    template <typename ty1, typename ty2>
    inline constexpr bool size_is_less_or_equal = sizeof( ty1 ) <= sizeof( ty2 ) ? true : false;

    template <typename T>
    inline constexpr bool IsAnsiString = std::is_base_of_v<AnsiString,T>;

    template <typename T>
    inline constexpr bool IsWideString = std::is_base_of_v<WideString, T>;

    template <typename T>
    inline constexpr bool IsAnsiStringView = std::is_base_of_v<AnsiStringView, T>;

    template <typename T>
    inline constexpr bool IsWideStringView = std::is_base_of_v<WideStringView, T>;


    template <typename T>
    inline constexpr bool IsNotString = IsAnsiString<T> == false && IsWideString<T> == false;

    template<typename T>
    using ElementTypeOf = std::remove_reference_t<decltype( *std::begin( std::declval<T&>( ) ) )>;

    template<typename T>
    concept WideStringType = requires( T t )
    {
        {
            t.c_str( )
        } -> std::convertible_to<const wchar_t*>;
    };


    
    template <class It>
    using IteratorValue_t = std::iter_value_t<It>;

    template <class It>
    using IteratorCategory_t = typename std::iterator_traits<It>::iterator_category;

    template <class It, class = void>
    inline constexpr bool IsIterator_v = false;

    template <class It>
    inline constexpr bool IsIterator_v<It, std::void_t<IteratorCategory_t<It>>> = true;

    template <class It>
    inline constexpr bool IsInputIterator_v = std::is_convertible_v<IteratorCategory_t<It>, std::input_iterator_tag>;

    template <class It>
    inline constexpr bool IsForwardIterator_v = std::is_convertible_v<IteratorCategory_t<It>, std::forward_iterator_tag>;

    template <class It>
    inline constexpr bool IsBidirectionalIterator_v = std::is_convertible_v<IteratorCategory_t<It>, std::bidirectional_iterator_tag>;

    template <class It>
    inline constexpr bool IsRandomAccessIterator_v = std::is_convertible_v<IteratorCategory_t<It>, std::random_access_iterator_tag>;

    template <class It>
    inline constexpr bool IsContiguousIterator_v = std::is_convertible_v<IteratorCategory_t<It>, std::contiguous_iterator_tag>;

    template <typename...> 
    struct AlwaysFalse : std::false_type
    {
    };
    


    namespace Types
    {
        /// <summary>
        /// Identifies the C/C++ types and C++ classes that forms the
        /// basis for the type vocabulary.
        /// </summary>
        enum class BasicTypeId : Byte
        {
            Unknown,
            /// <summary>
            /// identifies bool
            /// </summary>
            Boolean,
            /// <summary>
            /// identifies char
            /// </summary>
            Char,
            /// <summary>
            /// identifies signed char
            /// </summary>
            SByte,
            /// <summary>
            /// identifies unsigned char
            /// </summary>
            Byte,
            /// <summary>
            /// identifies wchar_t
            /// </summary>
            WChar,
            /// <summary>
            /// identifies short
            /// </summary>
            Int16,
            /// <summary>
            /// identifies unsigned short
            /// </summary>
            UInt16,
            /// <summary>
            /// identifies int or long
            /// </summary>
            Int32,
            /// <summary>
            /// identifies unsigned int or unsigned long
            /// </summary>
            UInt32,
            /// <summary>
            /// identifies long long
            /// </summary>
            Int64,
            /// <summary>
            /// identifies unsigned long long
            /// </summary>
            UInt64,
            /// <summary>
            /// identifies float
            /// </summary>
            Single,
            /// <summary>
            /// identifies double
            /// </summary>
            Double,
            /// <summary>
            /// identifies TimeSpan
            /// </summary>
            TimeSpan,
            /// <summary>
            /// identifies DateTime
            /// </summary>
            DateTime,
            /// <summary>
            /// identifies Currency
            /// </summary>
            Currency,
            /// <summary>
            /// identifies Guid
            /// </summary>
            Guid
        };

        #define HCC_MAP_BASICTYPEID_ENUM_VALUES( enumBaseType ) \
            Unknown = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Unknown), \
            Boolean = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Boolean), \
            Char = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Char), \
            SByte = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::SByte), \
            Byte = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Byte), \
            WChar = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::WChar), \
            Int16 = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Int16), \
            UInt16 = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::UInt16), \
            Int32 = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Int32), \
            UInt32 = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::UInt32), \
            Int64 = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Int64), \
            UInt64 = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::UInt64), \
            Single = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Single), \
            Double = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Double), \
            TimeSpan = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::TimeSpan), \
            DateTime = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::DateTime), \
            Currency = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Currency), \
            Guid = static_cast<enumBaseType>(Harlinn::Common::Core::Types::BasicTypeId::Guid)


        // Includes BasicTypeId::Unknown
        constexpr size_t BasicTypeIdCount = static_cast<size_t>( BasicTypeId::Guid ) + 1;
        // Excludes BasicTypeId::Unknown
        constexpr size_t BasicTypeCount = BasicTypeIdCount - 1;
        constexpr size_t BasicTypeIdMin = static_cast<size_t>( BasicTypeId::Boolean );
        constexpr size_t BasicTypeIdMax = static_cast<size_t>( BasicTypeId::Guid );

        template<typename T>
        struct TypeTraits;

        template<typename T>
        concept BasicType = IsBasicType<T>;

        template<typename T>
        concept ArrayType = IsArray<T>;

        template<typename T>
        concept PointerType = IsPointer<T>;

        template<typename T>
        concept ContainerType = IsContainer<T>;

        template<typename T>
        concept ArrayContainerType = IsArrayContainer<T>;

        template<typename T>
        concept VectorContainerType = IsVectorContainer<T>;


        template<typename T>
        concept TupleType = IsTupleType<T>;

        template<typename T>
        concept StdOptionalType = IsStdOptional<T>;

        template<typename T>
        concept StdSharedPtrType = IsStdSharedPtr<T>;

        template<typename T>
        concept StdUniquePtrType = IsStdUniquePtr<T>;

        template<typename T>
        concept SmartPtrType = IsStdUniquePtr<T> || IsStdSharedPtr<T>;

        template<typename T>
        concept StdVariantType = IsStdVariant<T>;

        template<typename T>
        concept VariadicTemplateType = IsTypeList<T> || IsTupleType<T> || IsStdVariant<T>;

        template<typename T>
        concept VariadicStructureType = IsTypeList<T> || IsTupleType<T>;

        template<typename T>
        concept WithElementTypeType = IsArray<T> || IsContainer<T> || IsStdOptional<T> || IsStdSharedPtr<T> || IsStdUniquePtr<T> || std::is_pointer_v< std::remove_cvref_t<T> >;

        template<typename T>
        struct IsFixedSize;

        template<typename T>
        struct PackedSizeOf;

        namespace Internal
        {
            
            template<typename T, typename RT >
            struct TypeTraitsBase
            {
                using Type = T;
                using RawType = RT;
                static constexpr bool IsSupported = false;
                static constexpr bool IsConst = Core::IsConst<RT>;
                static constexpr bool IsVolatile = Core::IsVolatile<RT>;
                static constexpr bool IsReference = Core::IsReference<RT>;
                static constexpr bool IsBasic = false;
                static constexpr bool IsArray = false;
                static constexpr bool IsPointer = false;
                static constexpr bool IsContainer = false;
                static constexpr bool IsOptional = false;
                static constexpr bool IsSharedPtr = false;
                static constexpr bool IsUniquePtr = false;
                static constexpr bool IsTuple = false;
                static constexpr bool IsVariant = false;
                static constexpr bool IsTypeList = false;
                static constexpr bool IsAdapted = false;
                static constexpr bool IsFixedSize = false;

                static constexpr size_t SizeOf( const T& object ) noexcept
                {
                    return sizeof( T );
                }

            };


            template<typename T, typename RT>
            struct UnsupportedTypeTraits : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
            };


            template<typename T, typename RT>
            struct BasicTypeTraits;

            template<typename T, BasicTypeId typeId_, typename RT>
            struct BasicTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                static constexpr BasicTypeId TypeId = typeId_;
                static constexpr bool IsSupported = true;
                static constexpr bool IsBasic = true;
                static constexpr bool IsFixedSize = true;
                static constexpr bool IsEnum = std::is_enum_v<T>;
            };

            template<typename RT>
            struct BasicTypeTraits<bool, RT> : public BasicTypeTraitsBase<bool, BasicTypeId::Boolean, RT>
            {
                using Base = BasicTypeTraitsBase<bool, BasicTypeId::Boolean, RT>;
            };
            template<typename RT>
            struct BasicTypeTraits<char, RT> : public BasicTypeTraitsBase<char, BasicTypeId::Char, RT>
            {
                using Base = BasicTypeTraitsBase<char, BasicTypeId::Char, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<Byte, RT> : public BasicTypeTraitsBase<Byte, BasicTypeId::Byte, RT>
            {
                using Base = BasicTypeTraitsBase<Byte, BasicTypeId::Byte, RT>;
            };
            template<typename RT>
            struct BasicTypeTraits<SByte, RT> : public BasicTypeTraitsBase<SByte, BasicTypeId::SByte, RT>
            {
                using Base = BasicTypeTraitsBase<SByte, BasicTypeId::SByte, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<wchar_t, RT> : public BasicTypeTraitsBase<wchar_t, BasicTypeId::WChar, RT>
            {
                using Base = BasicTypeTraitsBase<wchar_t, BasicTypeId::WChar, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<Int16, RT> : public BasicTypeTraitsBase<Int16, BasicTypeId::Int16, RT>
            {
                using Base = BasicTypeTraitsBase<Int16, BasicTypeId::Int16, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<UInt16, RT> : public BasicTypeTraitsBase<UInt16, BasicTypeId::UInt16, RT>
            {
                using Base = BasicTypeTraitsBase<UInt16, BasicTypeId::UInt16, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<Int32, RT> : public BasicTypeTraitsBase<Int32, BasicTypeId::Int32, RT>
            {
                using Base = BasicTypeTraitsBase<Int32, BasicTypeId::Int32, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<long, RT> : public BasicTypeTraitsBase<long, BasicTypeId::Int32, RT>
            {
                using Base = BasicTypeTraitsBase<long, BasicTypeId::Int32, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<UInt32, RT> : public BasicTypeTraitsBase<UInt32, BasicTypeId::UInt32, RT>
            {
                using Base = BasicTypeTraitsBase<UInt32, BasicTypeId::UInt32, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<unsigned long, RT> : public BasicTypeTraitsBase<unsigned long, BasicTypeId::UInt32, RT>
            {
                using Base = BasicTypeTraitsBase<unsigned long, BasicTypeId::UInt32, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<Int64, RT> : public BasicTypeTraitsBase<Int64, BasicTypeId::Int64, RT>
            {
                using Base = BasicTypeTraitsBase<Int64, BasicTypeId::Int64, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<UInt64, RT> : public BasicTypeTraitsBase<UInt64, BasicTypeId::UInt64, RT>
            {
                using Base = BasicTypeTraitsBase<UInt64, BasicTypeId::UInt64, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<float, RT> : public BasicTypeTraitsBase<float, BasicTypeId::Single, RT>
            {
                using Base = BasicTypeTraitsBase<float, BasicTypeId::Single, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<double, RT> : public BasicTypeTraitsBase<double, BasicTypeId::Double, RT>
            {
                using Base = BasicTypeTraitsBase<double, BasicTypeId::Double, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<DateTime, RT> : public BasicTypeTraitsBase<DateTime, BasicTypeId::DateTime, RT>
            {
                using Base = BasicTypeTraitsBase<DateTime, BasicTypeId::DateTime, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<TimeSpan, RT> : public BasicTypeTraitsBase<TimeSpan, BasicTypeId::TimeSpan, RT>
            {
                using Base = BasicTypeTraitsBase<TimeSpan, BasicTypeId::TimeSpan, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<Currency, RT> : public BasicTypeTraitsBase<Currency, BasicTypeId::Currency, RT>
            {
                using Base = BasicTypeTraitsBase<Currency, BasicTypeId::Currency, RT>;
            };

            template<typename RT>
            struct BasicTypeTraits<Guid, RT> : public BasicTypeTraitsBase<Guid, BasicTypeId::Guid, RT>
            {
                using Base = BasicTypeTraitsBase<Guid, BasicTypeId::Guid, RT>;
            };
        }

        static_assert( BasicTypeIdMax < 128 );

        enum class ContainerTypeId : Byte
        {
            // Same value as BasicTypeId::Unknown
            Unknown,
            StdArray = 128,
            StdVector,
            StdVectorBool,
            StdDeque,
            StdForwardList,
            StdList,
            StdSet,
            StdMap,
            StdMultiset,
            StdMultimap,
            StdUnorderedSet,
            StdUnorderedMap,
            StdUnorderedMultiset,
            StdUnorderedMultimap,
            StdStack,
            StdQueue,
            StdPriorityQueue,
            StdSpan,
            StdBasicString,
            StdBasicStringView,
            BasicString,
            BasicStringView,
            Vector
        };

        // Includes ContainerTypeId::Unknown
        constexpr size_t ContainerTypeIdCount = static_cast<size_t>( ContainerTypeId::Vector ) - static_cast<size_t>( ContainerTypeId::StdArray ) + 2;
        // Excludes ContainerTypeId::Unknown
        constexpr size_t ContainerTypeCount = ContainerTypeIdCount - 1;
        constexpr size_t ContainerTypeIdMin = static_cast<size_t>( ContainerTypeId::StdArray );
        constexpr size_t ContainerTypeIdMax = static_cast<size_t>( ContainerTypeId::Vector );

        static_assert( ContainerTypeIdMax < 200 );

        enum class TupleTypeId : Byte
        {
            // Same value as BasicTypeId::Unknown
            Unknown,
            StdPair = 200,
            StdTuple,
            Tuple
        };

        // Includes TupleTypeId::Unknown
        constexpr size_t TupleTypeIdCount = static_cast<size_t>( TupleTypeId::Tuple ) - static_cast<size_t>( TupleTypeId::StdPair ) + 2;
        // Excludes TupleTypeId::Unknown
        constexpr size_t TupleTypeCount = TupleTypeIdCount - 1;
        // Excludes TupleTypeId::Unknown
        constexpr size_t TupleTypeIdMin = static_cast<size_t>( TupleTypeId::StdPair );
        constexpr size_t TupleTypeIdMax = static_cast<size_t>( TupleTypeId::Tuple );

        
        static_assert( ContainerTypeIdMax < 210 );

        enum class UtilityTypeId : Byte
        {
            // Same value as BasicTypeId::Unknown
            Unknown,
            Pointer = 210,
            Array,
            StdSharedPtr,
            StdUniquePtr,
            StdVariant,
            StdOptional,
            StdAny,
            TypeList,
            Adapted
        };
        // Includes UtilityTypeId::Unknown
        constexpr size_t UtilityTypeIdCount = static_cast<size_t>( UtilityTypeId::TypeList ) - static_cast<size_t>( UtilityTypeId::Pointer ) + 2;
        // Excludes UtilityTypeId::Unknown
        constexpr size_t UtilityTypeCount = UtilityTypeIdCount - 1;
        // Excludes UtilityTypeId::Unknown
        constexpr size_t UtilityTypeIdMin = static_cast<size_t>( UtilityTypeId::Pointer );
        constexpr size_t UtilityTypeIdMax = static_cast<size_t>( UtilityTypeId::TypeList );


        template<typename T>
        concept HasTypeList = IsTypeList<typename T::TypeList>;

        namespace Adapters
        {
            template<typename T>
            struct TypeAdapter : std::false_type
            {
            };
        }
        template<typename T>
        inline constexpr bool HasTypeAdapter = Types::Adapters::TypeAdapter<T>::value;

        template<typename T>
        concept IsAdapted = HasTypeList<std::remove_cvref_t<T>> || HasTypeAdapter<std::remove_cvref_t<T>>;


        namespace Internal
        {
            template<typename T, typename RT>
            struct ArrayTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using ElementType = std::remove_extent_t<T>;
                static constexpr size_t Rank = std::rank_v<T>;
                static constexpr size_t Extent = std::extent_v<T>;
                static constexpr size_t Count = Extent;
                static constexpr bool IsSupported = true;
                static constexpr bool IsArray = true;
                static constexpr UtilityTypeId TypeId = UtilityTypeId::Array;

                static constexpr size_t SizeOf( const T& object ) noexcept
                {
                    static_assert( !std::is_unbounded_array_v<Base::Type>, "Unable to calculate the size of an unbounded array." );

                    if constexpr ( IsFixedSize<ElementType>::value )
                    {
                        return Count * PackedSizeOf<ElementType>::value;
                    }
                    else
                    {
                        using ElementTypeTraits = TypeTraits<ElementType>;
                        size_t result = 0;
                        for ( size_t i = 0; i < Count; ++i )
                        {
                            const auto& item = object[i];
                            result += ElementTypeTraits::SizeOf( item );
                        }
                        return result;
                    }
                }

            };

            template<typename T, typename RT>
            struct ArrayTypeTraits : ArrayTypeTraitsBase<T, RT>
            {
                using Base = ArrayTypeTraitsBase<T, RT>;
            };

            template<typename T, typename RT>
            struct PointerTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using ElementType = std::remove_pointer_t<T>;
                static constexpr bool IsSupported = true;
                static constexpr bool IsPointer = true;
                static constexpr UtilityTypeId TypeId = UtilityTypeId::Pointer;

                static constexpr size_t SizeOf( const ElementType* object ) noexcept
                {
                    static_assert( object == nullptr, "Unable to calculate the size of an unbounded array." );
                    return 0;
                }

            };

            template<typename T, typename RT>
            struct PointerTypeTraits : PointerTypeTraitsBase<T, RT>
            {
                using Base = PointerTypeTraitsBase<T, RT>;
            };

            template<typename RT, typename ...T>
            struct ContainerTypeTraits;

            template<typename T, typename RT >
            struct ContainerTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using ElementType = typename T::value_type;
                static constexpr bool IsSupported = true;
                static constexpr bool IsContainer = true;

                static constexpr size_t Count = 0;
                static constexpr bool IsView = false;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::Unknown;
            };

            template<typename RT, typename T>
            struct ContainerTypeTraits<RT, Vector<T>> : ContainerTypeTraitsBase<Vector<T>, RT>
            {
                using Base = ContainerTypeTraitsBase<Vector<T>, RT>;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::Vector;

                static constexpr size_t SizeOf( const Vector<T>& object ) noexcept
                {
                    if constexpr ( IsFixedSize<Base::ElementType>::value )
                    {
                        return object.size( ) * PackedSizeOf<Base::ElementType>::value;
                    }
                    else
                    {
                        using ElementTypeTraits = TypeTraits<Base::ElementType>;
                        size_t result = 0;
                        auto end = object.end( );
                        for ( auto it = object.begin( ); it != end; ++it )
                        {
                            const auto& item = *it;
                            result += ElementTypeTraits::SizeOf( item );
                        }
                        return result;
                    }
                }

            };

            template<typename RT, typename T, size_t N>
            struct ContainerTypeTraits<RT, std::array<T, N>> : ContainerTypeTraitsBase<std::array<T, N>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::array<T, N>, RT>;
                static constexpr bool IsFixedSize = true;
                static constexpr size_t Count = N;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdArray;
            };

            template<typename RT, typename T, typename A>
            struct ContainerTypeTraits<RT, std::vector<T, A>> : ContainerTypeTraitsBase<std::vector<T, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::vector<T, A>, RT>;
                static constexpr ContainerTypeId TypeId = std::is_same_v<T,bool>? ContainerTypeId::StdVectorBool : ContainerTypeId::StdVector;

                static constexpr size_t SizeOf( const std::vector<T, A>& object ) noexcept
                {
                    if constexpr ( IsFixedSize<Base::ElementType>::value )
                    {
                        return object.size( ) * PackedSizeOf<Base::ElementType>::value;
                    }
                    else
                    {
                        using ElementTypeTraits = TypeTraits<Base::ElementType>;
                        size_t result = 0;
                        auto end = object.end( );
                        for ( auto it = object.begin( ); it != end; ++it )
                        {
                            const auto& item = *it;
                            result += ElementTypeTraits::SizeOf( item );
                        }
                        return result;
                    }
                }
            };

            template<typename RT, typename T, typename A>
            struct ContainerTypeTraits<RT, std::deque<T, A>> : ContainerTypeTraitsBase<std::deque<T, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::deque<T, A>, RT>;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdDeque;
            };

            template<typename RT, typename T, typename A>
            struct ContainerTypeTraits<RT, std::forward_list<T, A>> : ContainerTypeTraitsBase<std::forward_list<T, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::forward_list<T, A>, RT>;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdForwardList;
            };

            template<typename RT, typename T, typename A>
            struct ContainerTypeTraits<RT, std::list<T, A>> : ContainerTypeTraitsBase<std::list<T, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::list<T, A>, RT>;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdList;
            };

            template<typename RT, typename T, typename C, typename A>
            struct ContainerTypeTraits<RT, std::set<T, C, A>> : ContainerTypeTraitsBase<std::set<T, C, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::set<T, C, A>, RT>;
                using ComparerType = C;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdSet;
            };

            template<typename RT, typename K, typename V, typename C, typename A>
            struct ContainerTypeTraits<RT, std::map<K, V, C, A>> : ContainerTypeTraitsBase<std::map<K, V, C, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::map<K, V, C, A>, RT>;
                using KeyType = K;
                using ValueType = V;
                using ComparerType = C;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdMap;
            };

            template<typename RT, typename T, typename C, typename A>
            struct ContainerTypeTraits<RT, std::multiset<T, C, A>> : ContainerTypeTraitsBase<std::multiset<T, C, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::multiset<T, C, A>, RT>;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdMultiset;
            };

            template<typename RT, typename K, typename V, typename C, typename A>
            struct ContainerTypeTraits<RT, std::multimap<K, V, C, A>> : ContainerTypeTraitsBase<std::multimap<K, V, C, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::multimap<K, V, C, A>, RT>;
                using KeyType = K;
                using ValueType = V;
                using ComparerType = C;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdMultimap;
            };


            template<typename RT, typename K, typename H, typename C, typename A>
            struct ContainerTypeTraits<RT, std::unordered_set<K, H, C, A> > : ContainerTypeTraitsBase<std::unordered_set<K, H, C, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::unordered_set<K, H, C, A>, RT>;
                using HashFunctionType = H;
                using ComparerType = C;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdUnorderedSet;
            };

            template<typename RT, typename K, typename V, typename H, typename C, typename A>
            struct ContainerTypeTraits<RT, std::unordered_map<K, V, H, C, A> > : ContainerTypeTraitsBase<std::unordered_map<K, V, H, C, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::unordered_map<K, V, H, C, A>, RT>;
                using KeyType = K;
                using ValueType = V;
                using HashFunctionType = H;
                using ComparerType = C;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdUnorderedMap;
            };

            template<typename RT, typename K, typename H, typename C, typename A>
            struct ContainerTypeTraits<RT, std::unordered_multiset<K, H, C, A> > : ContainerTypeTraitsBase<std::unordered_multiset<K, H, C, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::unordered_multiset<K, H, C, A>, RT>;
                using HashFunctionType = H;
                using ComparerType = C;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdUnorderedMultiset;
            };

            template<typename RT, typename K, typename V, typename H, typename C, typename A>
            struct ContainerTypeTraits<RT, std::unordered_multimap<K, V, H, C, A> > : ContainerTypeTraitsBase<std::unordered_multimap<K, V, H, C, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::unordered_multimap<K, V, H, C, A>, RT>;
                using KeyType = K;
                using ValueType = V;
                using HashFunctionType = H;
                using ComparerType = C;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdUnorderedMultimap;
            };

            template<typename RT, typename T, typename Cnr>
            struct ContainerTypeTraits<RT, std::stack<T, Cnr>> : ContainerTypeTraitsBase<std::stack<T, Cnr>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::stack<T, Cnr>, RT>;
                using AdaptedContainerType = Cnr;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdStack;
            };

            template<typename RT, typename T, typename Cnr>
            struct ContainerTypeTraits<RT, std::queue<T, Cnr>> : ContainerTypeTraitsBase<std::queue<T, Cnr>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::queue<T, Cnr>, RT>;
                using AdaptedContainerType = Cnr;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdQueue;
            };
            template<typename RT, typename T, typename Cnr, typename Cmp>
            struct ContainerTypeTraits<RT, std::priority_queue<T, Cnr, Cmp>> : ContainerTypeTraitsBase<std::priority_queue<T, Cnr, Cmp>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::priority_queue<T, Cnr, Cmp>, RT>;
                using AdaptedContainerType = Cnr;
                using ComparerType = Cmp;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdPriorityQueue;
            };



            template<typename RT, typename T, typename TR, typename A>
            struct ContainerTypeTraits<RT, std::basic_string<T, TR, A>> : ContainerTypeTraitsBase<std::basic_string<T, TR, A>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::basic_string<T, TR, A>, RT>;
                using CharTraits = TR;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdBasicString;
            };

            template<typename RT, typename T, typename TR>
            struct ContainerTypeTraits<RT, std::basic_string_view<T, TR>> : ContainerTypeTraitsBase<std::basic_string_view<T, TR>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::basic_string_view<T, TR>, RT>;
                using CharTraits = TR;
                static constexpr bool IsView = true;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdBasicStringView;
            };

            template<typename RT, typename T >
            struct ContainerTypeTraits<RT, BasicString<T>> : ContainerTypeTraitsBase<BasicString<T>, RT>
            {
                using Base = ContainerTypeTraitsBase<BasicString<T>, RT>;
                using CharTraits = typename std::basic_string<T>::traits_type;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::BasicString;
            };

            template<typename RT, typename T>
            struct ContainerTypeTraits<RT, BasicStringView<T>> : ContainerTypeTraitsBase<BasicStringView<T>, RT>
            {
                using Base = ContainerTypeTraitsBase<BasicStringView<T>, RT>;
                using CharTraits = typename std::basic_string_view<T>::traits_type;
                static constexpr bool IsView = true;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::BasicStringView;
            };



            template<typename RT, typename T, size_t N>
            struct ContainerTypeTraits<RT, std::span<T, N>> : ContainerTypeTraitsBase<std::span<T, N>, RT>
            {
                using Base = ContainerTypeTraitsBase<std::span<T, N>, RT>;
                static constexpr bool IsFixedSize = std::span<T, N>::extent == std::dynamic_extent;
                static constexpr bool IsView = true;
                static constexpr ContainerTypeId TypeId = ContainerTypeId::StdSpan;
            };

            template<typename RT, typename ...T>
            struct TupleTypeTraits;

            template<typename RT, typename T, typename ...TupleTypes_>
            struct TupleTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using Types = TypeList<TupleTypes_...>;
                static constexpr size_t Count = sizeof...( TupleTypes_ );
                static constexpr bool IsSupported = true;
                static constexpr bool IsTuple = true;

                static constexpr TupleTypeId TypeId = TupleTypeId::Unknown;

                static constexpr size_t SizeOf( const T& object ) noexcept
                {
                    if constexpr ( Count > 0 )
                    {
                        if constexpr ( IsFixedSize<T>::value )
                        {
                            return PackedSizeOf<T>::value;
                        }
                        else
                        {
                            if constexpr ( IsStdTuple<T> || IsStdPair<T> )
                            {
                                size_t result = std::apply( []( auto&... v )
                                {
                                    return ( TypeTraits<decltype( v )>::SizeOf( v ) + ... );
                                }, object );
                            }
                            else if constexpr ( IsCoreTuple<T> )
                            {
                                size_t result = Apply( []( auto&... v )
                                {
                                    return ( TypeTraits<decltype( v )>::SizeOf( v ) + ... );
                                }, object );
                            }
                            else
                            {
                                static constexpr bool isKnownTupleType = IsStdTuple<T> || IsStdPair<T> || IsCoreTuple<T>;
                                static_assert( isKnownTupleType, "Unknown tuple type" );
                            }
                        }
                    }
                    else
                    {
                        return 0;
                    }
                }

            };

            template<typename RT, typename ...T>
            struct TupleTypeTraits<RT, std::tuple<T...>> : TupleTypeTraitsBase<RT, std::tuple<T...>, T...>
            {
                using Base = TupleTypeTraitsBase<RT, std::tuple<T...>, T...>;
                static constexpr TupleTypeId TypeId = TupleTypeId::StdTuple;
            };

            template<typename RT, typename ...T>
            struct TupleTypeTraits<RT, std::pair<T...>> : TupleTypeTraitsBase<RT, std::pair<T...>, T...>
            {
                using Base = TupleTypeTraitsBase<RT, std::pair<T...>, T...>;
                static constexpr TupleTypeId TypeId = TupleTypeId::StdPair;
            };


            template<typename RT, typename ...T>
            struct TupleTypeTraits<RT, Tuple<T...>> : TupleTypeTraitsBase<RT, Tuple<T...>, T...>
            {
                using Base = TupleTypeTraitsBase<RT, Tuple<T...>, T...>;
                static constexpr TupleTypeId TypeId = TupleTypeId::Tuple;
            };

            template<typename RT, typename ...T>
            struct VariantTypeTraits;

            template<typename RT, typename T, typename ...VariantTypes_>
            struct VariantTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using Types = TypeList<VariantTypes_...>;
                static constexpr size_t Count = sizeof...( VariantTypes_ );
                static constexpr bool IsSupported = true;
                static constexpr bool IsVariant = true;
                static constexpr UtilityTypeId TypeId = UtilityTypeId::StdVariant;

            };

            template<typename RT, typename ...T>
            struct VariantTypeTraits<RT, std::variant<T...>> : VariantTypeTraitsBase<RT, std::variant<T...>, T...>
            {
                using Base = VariantTypeTraitsBase<RT, std::variant<T...>, T...>;
            };


            template<typename RT, typename ...T>
            struct TypeListTypeTraits;

            template<typename RT, typename T, typename ...TypeListTypes_>
            struct TypeListTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using Types = TypeList<TypeListTypes_...>;
                static constexpr size_t Count = sizeof...( TypeListTypes_ );
                static constexpr bool IsSupported = true;
                static constexpr bool IsTypeList = true;
                static constexpr UtilityTypeId TypeId = UtilityTypeId::TypeList;
            };

            template<typename RT, typename ...T>
            struct TypeListTypeTraits<RT, TypeList<T...>> : TypeListTypeTraitsBase<RT, TypeList<T...>, T...>
            {
                using Base = TypeListTypeTraitsBase<RT, TypeList<T...>, T...>;
            };


            template<typename T, typename RT>
            struct AdaptedTypeTraits;

            template<typename T, typename RT, typename TL>
            struct AdaptedTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using Types = TL;
                static constexpr size_t Count = Meta::SizeOf_v<Types>;
                static constexpr bool IsSupported = true;
                static constexpr bool IsAdapted = true;
                static constexpr UtilityTypeId TypeId = UtilityTypeId::Adapted;
                using TupleType = typename Meta::Assign<Tuple<>, Types>;
                static constexpr bool IsFixedSize = Core::Types::IsFixedSize<TupleType>::value;

                static constexpr size_t SizeOf( const T& object ) noexcept
                {
                    if constexpr ( Count > 0 )
                    {
                        if constexpr ( Core::Types::IsFixedSize<TupleType>::value )
                        {
                            return PackedSizeOf<TupleType>::value;
                        }
                        else
                        {
                            size_t result = Apply( []( auto&... v )
                            {
                                return ( TypeTraits<decltype( v )>::SizeOf( v ) + ... );
                            }, reinterpret_cast<const TupleType&>(object) );
                            return result;
                        }
                    }
                    else
                    {
                        return 0;
                    }
                }

            };

            template<typename T>
            struct TypeListOf
            {
            private:
                static constexpr auto Eval( ) noexcept
                {
                    if constexpr ( HasTypeList<T> )
                    {
                        return (typename T::TypeList*)nullptr;
                    }
                    else
                    {
                        return (void*)nullptr;
                    }
                }
            public:
                using type = std::remove_pointer_t<decltype( Eval( ) )>;
            };

            template<typename T, typename RT>
            struct AdaptedTypeTraits : AdaptedTypeTraitsBase<T, RT, std::conditional_t<HasTypeList<T>, typename TypeListOf<T>::type, typename Types::Adapters::TypeAdapter<T>::type> >
            {
                
            };



            template<typename T, typename RT>
            struct OptionalTypeTraits;

            template<typename T, typename RT>
            struct OptionalTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using ElementType = typename T::value_type;
                
                static constexpr bool IsSupported = true;
                static constexpr bool IsOptional = true;
                static constexpr UtilityTypeId TypeId = UtilityTypeId::StdOptional;
            };

            template<typename T, typename RT>
            struct OptionalTypeTraits<std::optional<T>, RT> : OptionalTypeTraitsBase<std::optional<T>, RT>
            {
                using Base = OptionalTypeTraitsBase<std::optional<T>, RT>;
            };


            template<typename T, typename RT>
            struct SharedPtrTypeTraits;

            template<typename T, typename RT>
            struct SharedPtrTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using ElementType = typename T::element_type;

                static constexpr bool IsSupported = true;
                static constexpr bool IsSharedPtr = true;
                static constexpr UtilityTypeId TypeId = UtilityTypeId::StdSharedPtr;
            };

            template<typename T, typename RT>
            struct SharedPtrTypeTraits<std::shared_ptr<T>, RT> : SharedPtrTypeTraitsBase< std::shared_ptr<T>, RT>
            {
                using Base = SharedPtrTypeTraitsBase< std::shared_ptr<T>, RT>;
            };

            template<typename T, typename RT>
            struct UniquePtrTypeTraits;

            template<typename T, typename RT>
            struct UniquePtrTypeTraitsBase : TypeTraitsBase<T, RT>
            {
                using Base = TypeTraitsBase<T, RT>;
                using ElementType = typename T::element_type;

                static constexpr bool IsSupported = true;
                static constexpr bool IsUniquePtr = true;
                static constexpr UtilityTypeId TypeId = UtilityTypeId::StdUniquePtr;
            };

            template<typename T, typename RT>
            struct UniquePtrTypeTraits<std::unique_ptr<T>, RT> : UniquePtrTypeTraitsBase< std::unique_ptr<T>, RT>
            {
                using Base = UniquePtrTypeTraitsBase< std::unique_ptr<T>, RT>;
            };



        }

        
        template<typename T>
        struct TypeTraits : 
            std::conditional_t
              <
                IsBasicType<T>, Types::Internal::BasicTypeTraits<std::remove_cvref_t<T>, T>,
                  std::conditional_t
                  <
                    IsArray<T>, Types::Internal::ArrayTypeTraits<std::remove_cvref_t<T>, T>,
                    std::conditional_t
                      <  
                        IsPointer<T>, Types::Internal::PointerTypeTraits<std::remove_cvref_t<T>, T>,
                        std::conditional_t
                        <
                          IsContainer<T>, Types::Internal::ContainerTypeTraits<T, std::remove_cvref_t<T>>,
                          std::conditional_t
                          < 
                            IsTupleType<T>, Types::Internal::TupleTypeTraits<T, std::remove_cvref_t<T>>,
                            std::conditional_t
                            < 
                              IsStdOptional<T>, Types::Internal::OptionalTypeTraits<std::remove_cvref_t<T>, T >,
                              std::conditional_t
                              <
                                IsStdUniquePtr<T>, Types::Internal::UniquePtrTypeTraits<std::remove_cvref_t<T>, T >,
                                std::conditional_t
                                <
                                  IsStdSharedPtr<T>, Types::Internal::SharedPtrTypeTraits<std::remove_cvref_t<T>, T >,
                                  std::conditional_t
                                  <
                                    IsStdVariant<T>, Types::Internal::VariantTypeTraits<T, std::remove_cvref_t<T>>,
                                    std::conditional_t
                                    <
                                      IsTypeList<T>, Types::Internal::TypeListTypeTraits<T, std::remove_cvref_t<T>>,
                                      std::conditional_t
                                      < 
                                        IsAdapted<T>, Types::Internal::AdaptedTypeTraits<std::remove_cvref_t<T>,T>,
                                        Types::Internal::UnsupportedTypeTraits<std::remove_cvref_t<T>, T> 
                                      >
                                    >
                                  >
                                >
                              >
                            >
                          >
                        >
                      >
                  > 
              >
        { };
        




        template<typename T>
        struct PackedSizeOf
        {
            static constexpr size_t value = 0;
        };

        template<Types::BasicType T>
        struct PackedSizeOf<T>
        {
            using TypeTraits = Types::TypeTraits<T>;
            static constexpr size_t value = sizeof( TypeTraits::Type );
        };

        namespace Internal
        {
            template<size_t i, typename T>
            struct VariadicStructureTypePackedSizeOf
            {
                using TypeTraits = typename Types::TypeTraits<T>;
                using ElementType = Meta::At< typename TypeTraits::Types, i>;
                static constexpr size_t value = PackedSizeOf<ElementType>::value + VariadicStructureTypePackedSizeOf<i - 1, T>::value;
            };

            template<typename T>
            struct VariadicStructureTypePackedSizeOf<0, T >
            {
                using TypeTraits = typename Types::TypeTraits<T>;
                using ElementType = Meta::At< typename TypeTraits::Types, 0>;

                static constexpr size_t value = PackedSizeOf<ElementType>::value;
            };
        }


        template<Types::VariadicStructureType T>
        struct PackedSizeOf<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr size_t value = std::conditional_t<(IsFixedSize<T>::value && TypeTraits::Count != 0), Types::Internal::VariadicStructureTypePackedSizeOf<TypeTraits::Count - 1, T>, std::integral_constant<size_t,0> >::value;
        };

        template<Types::ArrayType T>
        struct PackedSizeOf<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr size_t value = TypeTraits::Count != 0 ? TypeTraits::Count * PackedSizeOf<typename TypeTraits::ElementType>::value : 0;
        };

        template<Types::ContainerType T>
        struct PackedSizeOf<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr size_t value = TypeTraits::IsFixedSize ? TypeTraits::Count * PackedSizeOf<typename TypeTraits::ElementType>::value : 0;
        };


        template<Types::StdOptionalType T>
        struct PackedSizeOf<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr size_t value = IsFixedSize<T>::value? (sizeof( bool ) + PackedSizeOf<typename TypeTraits::ElementType>::value) : 0;
        };


        template<typename T>
        struct IsFixedSize
        {
            static constexpr bool value = false;
        };

        template<Types::BasicType T>
        struct IsFixedSize<T>
        {
            using TypeTraits = Types::TypeTraits<T>;
            static constexpr bool value = TypeTraits::IsFixedSize;
        };

        template<Types::ArrayType T>
        struct IsFixedSize<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr bool value = TypeTraits::Count == 0 ? true : IsFixedSize<typename TypeTraits::ElementType>::value;
        };

        template<Types::ContainerType T>
        struct IsFixedSize<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr bool value = TypeTraits::IsFixedSize ? ( TypeTraits::Count != 0 ? IsFixedSize<typename TypeTraits::ElementType>::value : true ) : false;
        };

        template<Types::StdOptionalType T>
        struct IsFixedSize<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr bool value = IsFixedSize<typename TypeTraits::ElementType>::value;
        };

        namespace Internal
        {
            template<size_t i, typename T>
            struct VariadicStructureTypeIsFixedSize
            {
                using TypeTraits = typename Types::TypeTraits<T>;
                using ElementType = Meta::At< typename TypeTraits::Types, i>;
                static constexpr bool value = IsFixedSize<ElementType>::value ? VariadicStructureTypeIsFixedSize<i - 1, T>::value : false;
            };

            template<typename T>
            struct VariadicStructureTypeIsFixedSize<0, T >
            {
                using TypeTraits = typename Types::TypeTraits<T>;
                using ElementType = Meta::At< typename TypeTraits::Types, 0>;

                static constexpr bool value = IsFixedSize<ElementType>::value;
            };
        }

        template<Types::VariadicStructureType T>
        struct IsFixedSize<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr bool value = std::conditional_t< TypeTraits::Count == 0, std::true_type, Types::Internal::VariadicStructureTypeIsFixedSize<TypeTraits::Count - 1, T> >::value;
        };



        template<typename T>
        struct IsSupportedType
        {
            static constexpr bool value = false;
        };
        template<Types::BasicType T>
        struct IsSupportedType<T>
        {
            using TypeTraits = Types::TypeTraits<T>;
            static constexpr bool value = TypeTraits::IsSupported;
        };
        template<Types::WithElementTypeType T>
        struct IsSupportedType<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr bool value = IsSupportedType<typename TypeTraits::ElementType>::value;
        };

        namespace Internal
        {
            template<size_t i, typename T>
            struct VariadicTemplateTypeIsSupportedType
            {
                using TypeTraits = typename Types::TypeTraits<T>;
                using ElementType = Meta::At< typename TypeTraits::Types, i>;
                static constexpr bool value = IsSupportedType<ElementType>::value ? VariadicTemplateTypeIsSupportedType<i - 1, T>::value : false;
            };

            template<typename T>
            struct VariadicTemplateTypeIsSupportedType<0, T >
            {
                using TypeTraits = typename Types::TypeTraits<T>;
                using ElementType = Meta::At< typename TypeTraits::Types, 0>;

                static constexpr bool value = IsSupportedType<ElementType>::value;
            };
        }

        template<Types::VariadicTemplateType T>
        struct IsSupportedType<T>
        {
            using TypeTraits = typename Types::TypeTraits<T>;
            static constexpr bool value = std::conditional_t<TypeTraits::Count == 0, std::true_type, Types::Internal::VariadicTemplateTypeIsSupportedType<TypeTraits::Count - 1, T>>::value;
        };

        template<typename ...Args>
        constexpr size_t SizeOf( const Args& ... args ) noexcept
        {
            return ( TypeTraits<decltype( args )>::SizeOf( args ) + ... );
        }


    }

}


#endif
