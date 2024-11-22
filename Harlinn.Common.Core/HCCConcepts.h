#pragma once
#ifndef HCCCONCEPTS_H_
#define HCCCONCEPTS_H_
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

#include "HCCDef.h"

namespace Harlinn::Common::Core
{
    /// <summary>
    /// Matches most containers with sequential memory layout.
    /// </summary>
    template<typename T>
    concept SimpleSpanLike = std::is_base_of_v<std::random_access_iterator_tag,typename std::iterator_traits<typename T::const_iterator>::iterator_category> && requires ( T t1 )
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
        { t1.front() } ->std::convertible_to<const typename T::value_type>;
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
        concept SimpleStringLikeImpl = std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<typename T::const_iterator>::iterator_category> && requires ( T t1 )
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
    concept SimpleStringLike = Internal::SimpleStringLikeImpl<T> && (std::is_same_v<typename T::value_type, wchar_t> || std::is_same_v<typename T::value_type, char> );

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

    static_assert( AnsiStringLike< std::string > );
    static_assert( WideStringLike< std::wstring > );

    template<typename ValueT>
    concept SimpleComLike = requires( ValueT v )
    {
        { v.AddRef( ) } ->std::convertible_to<UInt32>;
        { v.Release( ) } ->std::convertible_to<UInt32>;
    };

}


#endif
