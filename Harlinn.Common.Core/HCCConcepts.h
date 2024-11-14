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

    template<typename T>
    concept SimpleCharSpanLike = SimpleSpanLike<T> && ( std::is_same_v<typename T::value_type, char> || std::is_same_v<typename T::value_type, wchar_t> );

    template<typename T>
    concept SimpleAnsiCharSpanLike = SimpleSpanLike<T> && std::is_same_v<typename T::value_type, char>;

    template<typename T>
    concept SimpleWideCharSpanLike = SimpleSpanLike<T> && std::is_same_v<typename T::value_type, wchar_t>;


    template<typename T>
    concept SpanLike = SimpleSpanLike<T> && requires ( T t1 )
    {
        { t1.rbegin( ) } ->std::same_as<typename T::reverse_iterator>;
        { t1.rend( ) } ->std::same_as<typename T::reverse_iterator>;
        { t1.front() } ->std::same_as<typename T::reference>;
        { t1.back( ) } ->std::same_as<typename T::reference>;
    };

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

    template<typename T>
    concept SimpleStringLike = Internal::SimpleStringLikeImpl<T> && (std::is_same_v<typename T::value_type, wchar_t> || std::is_same_v<typename T::value_type, char> );

    template<typename T>
    concept SimpleWideStringLike = Internal::SimpleStringLikeImpl<T> && std::is_same_v<typename T::value_type, wchar_t>;

    template<typename T>
    concept SimpleAnsiStringLike = Internal::SimpleStringLikeImpl<T> && std::is_same_v<typename T::value_type, char>;

    namespace Internal
    {
        template<typename T>
        concept StringLikeImpl = SimpleStringLikeImpl<T> && requires ( T t1, const T t2, typename T::size_type sz )
        {
            { t1.rbegin( ) } ->std::same_as<typename T::reverse_iterator>;
            { t1.rend( ) } ->std::same_as<typename T::reverse_iterator>;
            { t1.front( ) } ->std::convertible_to<typename T::value_type>;
            { t1.back( ) } ->std::convertible_to<typename T::value_type>;
            { t1.resize( sz ) };


            { t2[ 0 ] } ->std::same_as<typename T::const_reference>;
            { t2.begin( ) } ->std::same_as<typename T::const_iterator>;
            { t2.end( ) } ->std::same_as<typename T::const_iterator>;
            { t2.rbegin( ) } ->std::same_as<typename T::const_reverse_iterator>;
            { t2.rend( ) } ->std::same_as<typename T::const_reverse_iterator>;
            { t2.front( ) } ->std::convertible_to<typename T::value_type>;
            { t2.back( ) } ->std::convertible_to<typename T::value_type>;
            { t2.data( ) } ->std::same_as<typename T::const_pointer>;
        };
    }

    template<typename T>
    concept StringLike = Internal::StringLikeImpl<T> && ( std::is_same_v<typename T::value_type, wchar_t> || std::is_same_v<typename T::value_type, char> );

    template<typename T>
    concept WideStringLike = Internal::StringLikeImpl<T> && std::is_same_v<typename T::value_type, wchar_t>;

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
