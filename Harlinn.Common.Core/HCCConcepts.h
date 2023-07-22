#pragma once
#ifndef HCCCONCEPTS_H_
#define HCCCONCEPTS_H_

#include "HCCDef.h"

namespace Harlinn::Common::Core
{
    template<typename T>
    concept SimpleSpanLike = requires ( T t1 )
    {
        { t1[ 0 ] } ->std::convertible_to<typename T::value_type>;
        { t1.begin( ) } ->std::same_as<typename T::iterator>;
        { t1.end( ) } ->std::same_as<typename T::iterator>;
        { t1.size( ) } ->std::same_as<typename T::size_type>;
        { t1.data( ) } ->std::same_as<typename T::pointer>;
    };


    template<typename T>
    concept SpanLike = SimpleSpanLike<T> && requires ( T t1 )
    {
        { t1[ 0 ] } ->std::same_as<typename T::reference>;
        { t1.rbegin( ) } ->std::same_as<typename T::reverse_iterator>;
        { t1.rend( ) } ->std::same_as<typename T::reverse_iterator>;
        { t1.front() } ->std::same_as<typename T::reference>;
        { t1.back( ) } ->std::same_as<typename T::reference>;
    };

    template<typename T>
    concept SimpleStringLike = requires ( T t1 )
    {
        { t1[ 0 ] } ->std::convertible_to<typename T::value_type>;
        { t1.begin( ) } ->std::same_as<typename T::iterator>;
        { t1.end( ) } ->std::same_as<typename T::iterator>;
        { t1.size( ) } ->std::same_as<typename T::size_type>;
        { t1.c_str( ) } ->std::same_as<typename T::const_pointer>;
        { t1.data( ) } ->std::same_as<typename T::pointer>;
    };

    template<typename T>
    concept SimpleWideStringLike = SimpleStringLike<T> && std::is_same_v<typename T::value_type, wchar_t>;

    template<typename T>
    concept SimpleAnsiStringLike = SimpleStringLike<T> && std::is_same_v<typename T::value_type, char>;


    template<typename T>
    concept StringLike = SimpleStringLike<T> && requires ( T t1, const T t2, typename T::size_type sz )
    {
        { t1[ 0 ] } ->std::same_as<typename T::reference>;
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

    template<typename T>
    concept WideStringLike = StringLike<T> && std::is_same_v<typename T::value_type, wchar_t>;

    template<typename T>
    concept AnsiStringLike = StringLike<T> && std::is_same_v<typename T::value_type, char>;

    static_assert( AnsiStringLike< std::string > );
    static_assert( WideStringLike< std::wstring > );

    

    

}


#endif
