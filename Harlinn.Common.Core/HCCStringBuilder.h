#pragma once
#ifndef HCCSTRINGBUILDER_H_
#define HCCSTRINGBUILDER_H_

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

#include "HCCBlocks.h"
#include "HCCString.h"

namespace Harlinn::Common::Core
{
    template<typename T>
        requires std::is_same_v<T,char> || std::is_same_v<T, wchar_t>
    class StringBuilder
    {
        Blocks::Stream stream_;
        static constexpr bool isWide = std::is_same_v<T, wchar_t>;
    public:
        using value_type = T;
        using string_type = std::conditional_t<std::is_same_v<T, wchar_t>, WideString, AnsiString>;

        StringBuilder( ) = default;

        string_type ToString( ) const
        {
            if constexpr ( isWide )
            {
                return stream_.ToWideString();
            }
            else
            {
                return stream_.ToAnsiString( );
            }
        }


        void AppendLine( )
        {
            if constexpr ( isWide )
            {
                stream_.Write( L"\r\n", 2 * sizeof( wchar_t ) );
            }
            else
            {
                stream_.Write( "\r\n", 2 );
            }
        }

        template <class... Types>
        void Append( const std::wformat_string<Types...> fmt, Types&&... args )
        {
            auto wstr = FormatV( fmt.get( ), std::make_wformat_args( args... ) );
            if ( wstr )
            {
                if constexpr ( isWide )
                {
                    stream_.Write( wstr.c_str( ), wstr.Length( )*sizeof(wchar_t) );
                }
                else
                {
                    auto str = AnsiString::From( wstr );
                    stream_.Write( str.c_str( ), str.Length( ) );
                }
            }
        }
        template <class... Types>
        void AppendLine( const std::wformat_string<Types...> fmt, Types&&... args )
        {
            auto wstr = FormatV( fmt.get( ), std::make_wformat_args( args... ) );
            if ( wstr )
            {
                if constexpr ( isWide )
                {
                    stream_.Write( wstr.c_str( ), wstr.Length( ) * sizeof( wchar_t ) );
                }
                else
                {
                    auto str = AnsiString::From( wstr );
                    stream_.Write( str.c_str( ), str.Length( ) );
                }
            }
            AppendLine( );
        }

        template <class... Types>
        void Append( const std::format_string<Types...> fmt, Types&&... args )
        {
            auto str = FormatV( fmt.get( ), std::make_format_args( args... ) );
            if ( str )
            {
                if constexpr ( isWide )
                {
                    auto wstr = WideString::From( str );
                    stream_.Write( wstr.c_str( ), wstr.Length( ) * sizeof( wchar_t ) );
                }
                else
                {
                    stream_.Write( str.c_str( ), str.Length( ) );
                }
            }
        }

        template <class... Types>
        void AppendLine( const std::format_string<Types...> fmt, Types&&... args )
        {
            auto str = FormatV( fmt.get( ), std::make_format_args( args... ) );
            if ( str )
            {
                if constexpr ( isWide )
                {
                    auto wstr = WideString::From( str );
                    stream_.Write( wstr.c_str( ), wstr.Length( ) * sizeof( wchar_t ) );
                }
                else
                {
                    stream_.Write( str.c_str( ), str.Length( ) );
                }
            }
            AppendLine( );
        }

        void Append( const char* str )
        {
            if ( str )
            {
                if constexpr ( isWide )
                {
                    auto wstr = WideString::From( str );
                    stream_.Write( wstr.c_str( ), wstr.Length( ) * sizeof( wchar_t ) );
                }
                else
                {
                    auto strLength = LengthOf( str );
                    stream_.Write( str, strLength );
                }
            }
        }
        void Append( const wchar_t* wstr )
        {
            if ( wstr )
            {
                if constexpr ( isWide )
                {
                    auto strLength = LengthOf( wstr );
                    stream_.Write( wstr, strLength * sizeof( wchar_t ) );
                }
                else
                {
                    auto str = AnsiString::From( wstr );
                    stream_.Write( str, str.Length() );
                }
            }
        }

        void AppendLine( const char* str )
        {
            Append( str );
            AppendLine( );
        }
        void AppendLine( const wchar_t* wstr )
        {
            Append( wstr );
            AppendLine( );
        }

        void Append( const AnsiString& str )
        {
            if ( str )
            {
                if constexpr ( isWide )
                {
                    auto wstr = WideString::From( str );
                    stream_.Write( wstr.c_str( ), wstr.Length( ) * sizeof( wchar_t ) );
                }
                else
                {
                    stream_.Write( str.c_str(), str.Length() );
                }
            }
        }
        void Append( const WideString& wstr )
        {
            if ( wstr )
            {
                if constexpr ( isWide )
                {
                    stream_.Write( wstr.c_str( ), wstr.Length() * sizeof( wchar_t ) );
                }
                else
                {
                    auto str = AnsiString::From( wstr );
                    stream_.Write( str, str.Length( ) );
                }
            }
        }

        void AppendLine( const AnsiString& str )
        {
            Append( str );
            AppendLine( );
        }
        void AppendLine( const WideString& wstr )
        {
            Append( wstr );
            AppendLine( );
        }


    };
}


#endif