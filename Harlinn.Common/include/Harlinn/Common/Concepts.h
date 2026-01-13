#pragma once
#ifndef HARLINN_COMMON_CONCEPTS_H_
#define HARLINN_COMMON_CONCEPTS_H_

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
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif

#include <iterator>
#include <ranges>
#include "BasicTypes.h"

namespace Harlinn::Common
{
    template<typename T>
    concept CharType = std::is_same_v<T, char> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char8_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;

    template<typename T>
    concept ApiCharType = std::is_same_v<T, char> || std::is_same_v<T, wchar_t>;

    /// <summary>
    /// Constrains types that satisfy the `std::ranges::input_range` concept,
    /// i.e. ranges that can be iterated over using an input iterator (single-pass
    /// iteration). Use this when only single-pass traversal is required.
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as an input-iterable range.
    /// </typeparam>
    template<typename T>
    concept InputRange = std::ranges::input_range<T>;

    /// <summary>
    /// Constrains range types that satisfy `std::ranges::output_range` for element type `T`,
    /// i.e. ranges that can be written-to through an output iterator accepting values of type `T`.
    /// </summary>
    /// <typeparam name="RangeT">
    /// Range type to be checked as an output range.
    /// </typeparam>
    /// <typeparam name="T">
    /// Element type that can be assigned to the range via an output iterator.
    /// </typeparam>
    template<typename RangeT, typename T>
    concept OutputRange = std::ranges::output_range<RangeT,T>;

    /// <summary>
    /// Constrains types that satisfy the `std::ranges::forward_range` concept,
    /// i.e. ranges that are iterable using a forward iterator (single-pass or multi-pass
    /// forward iteration is supported).
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a forward-iterable range.
    /// </typeparam>
    template<typename T>
    concept ForwardRange = std::ranges::forward_range<T>;


    /// <summary>
    /// Constrains types that satisfy the `std::ranges::bidirectional_range` concept,
    /// i.e. ranges whose iterators support both forward and backward traversal.
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a bidirectional range.
    /// </typeparam>
    template<typename T>
    concept BidirectionalRange = std::ranges::bidirectional_range<T>;

    
    /// <summary>
    /// Constrains types that satisfy the `std::ranges::random_access_range` concept,
    /// i.e. ranges whose iterators support constant-time random access (iterator
    /// arithmetic, indexing and full ordering).
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a random-access range.
    /// </typeparam>
    template<typename T>
    concept RandomAccessRange = std::ranges::random_access_range<T>;


    /// <summary>
    /// Constrains types that satisfy the `std::ranges::contiguous_range` concept,
    /// i.e. ranges whose elements are stored contiguously in memory and can be
    /// accessed via pointers or contiguous iterators.
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a contiguous range.
    /// </typeparam>
    template<typename T>
    concept ContiguousRange = std::ranges::contiguous_range<T>;


    /// <summary>
    /// Constrains types that satisfy the `std::ranges::range` concept,
    /// i.e. types that provide `begin()`/`end()` (are iterable as a range).
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a range.
    /// </typeparam>
    template<typename T>
    concept Range = std::ranges::range<T>;

    /// <summary>
    /// Constrains types that satisfy the `std::ranges::borrowed_range` concept,
    /// i.e. ranges whose iterators may remain valid even if the range object is a temporary.
    /// Commonly true for views and other types that allow borrowing.
    /// </summary>
    /// <typeparam name="T">Type to be checked as a borrowed range.</typeparam>
    template<typename T>
    concept BorrowedRange = std::ranges::borrowed_range<T>;

    /// <summary>
    /// Constrains types that satisfy the `std::ranges::sized_range` concept,
    /// i.e. ranges that provide a `size()` and where the size can be determined
    /// in constant time without iterating the range.
    /// </summary>
    /// <typeparam name="T">Type to be checked as a sized range.</typeparam>
    template<typename T>
    concept SizedRange = std::ranges::sized_range<T>;


    /// <summary>
    /// Constrains types that satisfy the `std::ranges::view` concept,
    /// i.e. lightweight (possibly non-owning) range adapters whose iterators
    /// may remain valid even when the view object is a temporary.
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a view (e.g., range view or adaptor type).
    /// </typeparam>
    template<typename T>
    concept View = std::ranges::view<T>;

    
    /// <summary>
    /// Constrains types that satisfy the `std::ranges::common_range` concept,
    /// i.e. ranges whose `begin()` and `end()` return the same iterator type
    /// (a "common" end), making them suitable for algorithms that require
    /// comparable begin/end iterators.
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a common range.
    /// </typeparam>
    template<typename T>
    concept CommonRange = std::ranges::common_range<T>;


    /// <summary>
    /// Constrains types that satisfy the `std::ranges::viewable_range` concept,
    /// i.e. ranges that can be used with range-view adaptors (either a view type
    /// or a range that can be bound-to a view).
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a viewable range.
    /// </typeparam>
    template<typename T>
    concept ViewableRange = std::ranges::viewable_range<T>;

    /// <summary>
    /// Constrains types that satisfy the `std::ranges::constant_range` concept,
    /// i.e. ranges whose elements are accessed as constant values (cannot be
    /// modified through the range's iterator).
    /// </summary>
    /// <typeparam name="T">
    /// Type to be checked as a constant range.
    /// </typeparam>
    template<typename T>
    concept ConstantRange = std::ranges::constant_range<T>;




    /// <summary>
    /// Matches contiguous containers that expose `size()` and `data()` and provide
    /// random-access element access (operator[]) such as std::array, std::vector,
    /// std::span and std::basic_string.
    /// </summary>
    template<typename T>
    concept ContiguousContainerLike = requires ( const T & t )
    {
        typename T::value_type;
        typename T::size_type;
        { t.size( ) } -> std::same_as<typename T::size_type>;
        { t.data( ) } -> std::convertible_to<const typename T::value_type*>;
        { t[ 0 ] } -> std::convertible_to<typename T::const_reference>;
    };


    
    /// <summary>
    /// Constrains types that declare a nested `value_type`.
    /// </summary>
    /// <typeparam name="T">
    /// Type that must declare a nested `value_type` (e.g., container or span-like type).
    /// </typeparam>
    template<typename T>
    concept HasValueType = requires { typename T::value_type; };

    /// <summary>
    /// Constrains types that declare a nested `value_type` and where that nested
    /// `value_type`, after removing cv-qualifiers and references, is the same as
    /// `ValueType`.
    /// </summary>
    /// <typeparam name="T">
    /// Type that must declare a nested `value_type` (e.g. container or span-like type).
    /// </typeparam>
    /// <typeparam name="ExpectedValueType">
    /// Expected element/value type to compare against `T::value_type`.
    /// </typeparam>
    template<typename T, typename ExpectedValueType>
    concept ValueTypeIs = requires { typename T::value_type; } && std::same_as<std::remove_cvref_t<typename T::value_type>, ExpectedValueType>;


    /// <summary>
    /// Constrains types that declare a nested `key_type`.
    /// </summary>
    /// <typeparam name="T">
    /// Type that must declare a nested `key_type` (e.g., associative container type).
    /// </typeparam>
    template<typename T>
    concept HasKeyType = requires { typename T::key_type; };

    
    /// <summary>
    /// Constrains types that declare a nested `key_type` and where that nested
    /// `key_type`, after removing cv-qualifiers and references, is the same as
    /// `ExpectedKeyType`.
    /// </summary>
    /// <typeparam name="T">
    /// Type that must declare a nested `key_type` (e.g., associative container type).
    /// </typeparam>
    /// <typeparam name="ExpectedKeyType">
    /// Expected key type to compare against `T::key_type`.
    /// </typeparam>
    template<typename T, typename ExpectedKeyType>
    concept KeyTypeIs = requires { typename T::key_type; }&& std::same_as<std::remove_cvref_t<typename T::key_type>, ExpectedKeyType>;

    /// <summary>
    /// Constrains types that declare a nested `mapped_type`.
    /// </summary>
    /// <typeparam name="T">
    /// Type that must declare a nested `mapped_type` (e.g., associative 
    /// container type such as `std::map` or `std::unordered_map`).
    /// </typeparam>
    template<typename T>
    concept HasMappedType = requires { typename T::mapped_type; };
    
    /// <summary>
    /// Constrains types that declare a nested `mapped_type` and where that nested
    /// `mapped_type`, after removing cv-qualifiers and references, is the same as
    /// `ExpectedMappedType`.
    /// </summary>
    /// <typeparam name="T">
    /// Type that must declare a nested `mapped_type` (e.g., associative container 
    /// type such as `std::map` or `std::unordered_map`).
    /// </typeparam>
    /// <typeparam name="ExpectedMappedType">
    /// Expected mapped type to compare against `T::mapped_type`.
    /// </typeparam>
    template<typename T, typename ExpectedMappedType>
    concept MappedTypeIs = requires { typename T::mapped_type; }&& std::same_as<std::remove_cvref_t<typename T::mapped_type>, ExpectedMappedType>;


    /// <summary>
    /// Matches most containers with sequential memory layout.
    /// </summary>
    template<typename T>
    concept SimpleSpanLike = std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<typename T::const_iterator>::iterator_category>&& requires ( T t1 )
    {
        { t1[ 0 ] } ->std::convertible_to<typename T::const_reference>;
        { t1.begin( ) } ->std::convertible_to<typename T::const_iterator>;
        { t1.end( ) } ->std::convertible_to<typename T::const_iterator>;
        { t1.size( ) } ->std::same_as<typename T::size_type>;
        { t1.data( ) } ->std::convertible_to<typename T::const_pointer>;
    };

    /// <summary>
    /// Matches most common string classes with sequential memory layout. 
    /// Do not assume that they are zero terminated
    /// </summary>
    template<typename T>
    concept SimpleCharSpanLike = SimpleSpanLike<T> && ( std::is_same_v<typename T::value_type, char> || std::is_same_v<typename T::value_type, wchar_t> );

    /// <summary>
    /// Matches most common char string classes with sequential memory layout. 
    /// Do not assume that they are zero terminated
    /// </summary>
    template<typename T>
    concept SimpleAnsiCharSpanLike = SimpleSpanLike<T> && std::is_same_v<typename T::value_type, char>;

    /// <summary>
    /// Matches most common wchar_t string classes with sequential memory layout. 
    /// Do not assume that they are zero terminated
    /// </summary>
    template<typename T>
    concept SimpleWideCharSpanLike = SimpleSpanLike<T> && std::is_same_v<typename T::value_type, wchar_t>;

    /// <summary>
    /// Matches most common container classes with sequential memory layout. 
    /// </summary>
    template<typename T>
    concept SimpleByteSpanLike = SimpleSpanLike<T> && std::is_same_v<typename T::value_type, Byte>;


    template<typename T>
    concept SpanLike = SimpleSpanLike<T> && requires ( T t1 )
    {
        { t1.rbegin( ) } ->std::same_as<typename T::reverse_iterator>;
        { t1.rend( ) } ->std::same_as<typename T::reverse_iterator>;
        { t1.front( ) } ->std::convertible_to<const typename T::value_type>;
        { t1.back( ) } ->std::convertible_to<const typename T::value_type>;
    };

    /// <summary>
    /// Matches most common string classes with sequential memory layout. 
    /// Do not assume that they are zero terminated
    /// </summary>
    template<typename T>
    concept CharSpanLike = SpanLike<T> && ( std::is_same_v<typename T::value_type, char> || std::is_same_v<typename T::value_type, wchar_t> );

    /// <summary>
    /// Matches most common char string classes with sequential memory layout. 
    /// Do not assume that they are zero terminated
    /// </summary>
    template<typename T>
    concept AnsiCharSpanLike = SpanLike<T> && std::is_same_v<typename T::value_type, char>;

    /// <summary>
    /// Matches most common wchar_t string classes with sequential memory layout. 
    /// Do not assume that they are zero terminated
    /// </summary>
    template<typename T>
    concept WideCharSpanLike = SpanLike<T> && std::is_same_v<typename T::value_type, wchar_t>;



    namespace Internal
    {
        template<typename T>
        concept SimpleStringLikeImpl = std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<typename T::const_iterator>::iterator_category>&& requires ( T t1 )
        {
            { t1[ 0 ] } ->std::convertible_to<typename T::const_reference>;
            { t1.begin( ) } ->std::convertible_to<typename T::const_iterator>;
            { t1.end( ) } ->std::convertible_to<typename T::const_iterator>;
            { t1.size( ) } ->std::same_as<typename T::size_type>;
            { t1.c_str( ) } ->std::same_as<typename T::const_pointer>;
            { t1.data( ) } ->std::convertible_to<typename T::const_pointer>;
        };
    }

    /// <summary>
    /// Matches most common zero terminated C++ string classes with sequential memory layout. 
    /// </summary>
    template<typename T>
    concept SimpleStringLike = Internal::SimpleStringLikeImpl<T> && ( std::is_same_v<typename T::value_type, wchar_t> || std::is_same_v<typename T::value_type, char> );

    /// <summary>
    /// Matches most common zero terminated C++ wchar_t string classes with sequential memory layout. 
    /// </summary>
    template<typename T>
    concept SimpleWideStringLike = Internal::SimpleStringLikeImpl<T> && std::is_same_v<typename T::value_type, wchar_t>;

    /// <summary>
    /// Matches most common zero terminated C++ char string classes with sequential memory layout. 
    /// </summary>
    template<typename T>
    concept SimpleAnsiStringLike = Internal::SimpleStringLikeImpl<T> && std::is_same_v<typename T::value_type, char>;

    namespace Internal
    {
        template<typename T>
        concept StringLikeImpl = SimpleStringLikeImpl<T> &&
            std::is_constructible_v<T> &&
            std::is_constructible_v<T, const typename T::value_type*>&&
            std::is_constructible_v<T, const typename T::value_type*, typename T::size_type>&&
            requires ( T t1, const T t2, typename T::size_type sz, typename T::size_type pos, typename T::size_type count, const typename T::value_type* ptr, typename T::value_type value )
        {
            { t1.rbegin( ) } ->std::same_as<typename T::reverse_iterator>;
            { t1.rend( ) } ->std::same_as<typename T::reverse_iterator>;
            { t1.front( ) } ->std::convertible_to<typename T::value_type>;
            { t1.back( ) } ->std::convertible_to<typename T::value_type>;
            { t1.resize( sz ) };
            { t1.reserve( sz ) };
            { t1.append( ptr, sz ) };
            { t1.append( ptr ) };
            { t1.append( sz, value ) };


            { t2[ 0 ] } ->std::same_as<typename T::const_reference>;
            { t2.begin( ) } ->std::same_as<typename T::const_iterator>;
            { t2.end( ) } ->std::same_as<typename T::const_iterator>;
            { t2.rbegin( ) } ->std::same_as<typename T::const_reverse_iterator>;
            { t2.rend( ) } ->std::same_as<typename T::const_reverse_iterator>;
            { t2.front( ) } ->std::convertible_to<typename T::value_type>;
            { t2.back( ) } ->std::convertible_to<typename T::value_type>;
            { t2.data( ) } ->std::same_as<typename T::const_pointer>;
            { t2.empty( ) } ->std::same_as<bool>;
            { t2.find( ptr ) } ->std::same_as<typename T::size_type>;
            { t2.find( ptr, pos ) } ->std::same_as<typename T::size_type>;
            { t2.find( ptr, pos, sz ) } ->std::same_as<typename T::size_type>;
            { t2.find( value, pos ) } ->std::same_as<typename T::size_type>;
            { t2.find_first_of( ptr ) } ->std::same_as<typename T::size_type>;
            { t2.find_first_of( ptr, pos ) } ->std::same_as<typename T::size_type>;
            { t2.find_first_of( ptr, pos, sz ) } ->std::same_as<typename T::size_type>;
            { t2.find_last_of( ptr ) } ->std::same_as<typename T::size_type>;
            { t2.find_last_of( ptr, pos ) } ->std::same_as<typename T::size_type>;
            { t2.find_last_of( ptr, pos, sz ) } ->std::same_as<typename T::size_type>;
            { t2.substr( pos, count ) } ->std::same_as<T>;
        };
    }

    /// <summary>
    /// Matches zero terminated C++ string classes with sequential memory layout 
    /// that implements an API similar to std::basic_string instantiated for either 
    /// char or wchar_t. 
    /// </summary>
    template<typename T>
    concept StringLike = Internal::StringLikeImpl<T> && ( std::is_same_v<typename T::value_type, wchar_t> || std::is_same_v<typename T::value_type, char> );

    /// <summary>
    /// Matches zero terminated C++ string classes with sequential memory layout 
    /// that implements an API similar to std::basic_string instantiated for wchar_t. 
    /// </summary>
    template<typename T>
    concept WideStringLike = Internal::StringLikeImpl<T> && std::is_same_v<typename T::value_type, wchar_t>;

    /// <summary>
    /// Matches zero terminated C++ string classes with sequential memory layout 
    /// that implements an API similar to std::basic_string instantiated for char. 
    /// </summary>
    template<typename T>
    concept AnsiStringLike = Internal::StringLikeImpl<T> && std::is_same_v<typename T::value_type, char>;

    template<typename ValueT>
    concept SimpleComLike = requires( ValueT v )
    {
        { v.AddRef( ) } ->std::convertible_to<UInt32>;
        { v.Release( ) } ->std::convertible_to<UInt32>;
    };

    template<typename BinaryT>
    concept BinaryLike = std::is_same_v<Byte, typename BinaryT::value_type >&&
        std::is_constructible_v<BinaryT>&&
        std::is_constructible_v<BinaryT, typename BinaryT::size_type>&&
        requires( BinaryT t1, const BinaryT& t2, typename BinaryT::size_type sz )
    {
        { t1[ sz ] }->std::same_as<typename BinaryT::reference>;
        { t2[ sz ] }->std::same_as<typename BinaryT::const_reference>;
        { t1.begin( ) }->std::same_as<typename BinaryT::iterator>;
        { t2.begin( ) }->std::same_as<typename BinaryT::const_iterator>;
        { t1.end( ) }->std::same_as<typename BinaryT::iterator>;
        { t2.end( ) }->std::same_as<typename BinaryT::const_iterator>;
        { t2.size( ) }->std::same_as<typename BinaryT::size_type>;
        { t1.data( ) }->std::same_as<typename BinaryT::pointer>;
        { t2.data( ) }->std::same_as<typename BinaryT::const_pointer>;
        { t1.resize( sz ) };
    };


    template<typename T>
    concept BooleanType = std::is_same_v<T, bool>;

    template<typename T>
    concept FloatingPointType = std::is_floating_point_v<T>;

    template<typename T>
    concept IntegerType = std::is_integral_v<T> && ( std::is_same_v<T, bool> == false );

    template<typename T>
    concept SignedIntegerType = IntegerType<T> && std::is_signed_v<T>;

    template<typename T>
    concept UnsignedIntegerType = IntegerType<T> && ( std::is_signed_v<T> == false );

    template<typename T>
    concept UnsignedIntegerOrBooleanType = UnsignedIntegerType<T> || BooleanType<T>;


    template<typename T>
    concept ArithmeticType = IntegerType<T> || FloatingPointType<T>;


}


#endif
