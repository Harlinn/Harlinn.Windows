#pragma once
#ifndef CODESTREAM_H_
#define CODESTREAM_H_

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

#include <HCCIO.h>
#include <HCCBlocks.h>

namespace Harlinn::ODBC
{
    using namespace Harlinn::Common::Core;
}

namespace Harlinn::ODBC::Tool
{
    class CodeStream
    {
        WideString filename_;
        Blocks::Stream stream_;
    public:
        CodeStream( const WideString& filename )
            : filename_( filename )
        {
            auto parentDirectory = IO::Path::GetParentDirectory( filename );
            if ( parentDirectory )
            {
                if ( IO::Directory::Exist( parentDirectory ) == false )
                {
                    IO::Directory::Create( parentDirectory );
                }
            }
        }

        const WideString& Filename( ) const
        {
            return filename_;
        }


        void Write( const wchar_t* wstr )
        {
            if ( wstr )
            {
                auto str = AnsiString::From( wstr );
                stream_.Write( str.c_str( ), str.Length( ) );
            }
        }

        void Write( const char* str )
        {
            if ( str )
            {
                auto strLen = LengthOf( str );
                stream_.Write( str, strLen );
            }
        }

        void WriteLine( const wchar_t* wstr )
        {
            Write( wstr );
            WriteLine( );
        }

        void WriteLine( const char* str )
        {
            Write( str );
            WriteLine( );
        }

        void Write( const WideString& wstr )
        {
            if ( wstr )
            {
                auto str = AnsiString::From( wstr );
                stream_.Write( str.c_str( ), str.Length( ) );
            }
        }

        void Write( const AnsiString& str )
        {
            if ( str )
            {
                stream_.Write( str.c_str( ), str.Length( ) );
            }
        }

        void WriteLine( const WideString& wstr )
        {
            Write( wstr );
            WriteLine( );
        }

        void WriteLine( const AnsiString& str )
        {
            Write( str );
            WriteLine( );
        }



        template <class... Types>
        void Write( const std::wformat_string<Types...> fmt, Types&&... args )
        {
            auto wstr = FormatV( fmt.get( ), std::make_wformat_args( args... ) );
            if ( wstr )
            {
                auto str = AnsiString::From( wstr );
                stream_.Write( str.c_str( ), str.Length( ) );
            }
        }
        template <class... Types>
        void WriteLine( const std::wformat_string<Types...> fmt, Types&&... args )
        {
            auto wstr = FormatV( fmt.get( ), std::make_wformat_args( args... ) );
            if ( wstr )
            {
                auto str = AnsiString::From( wstr );
                stream_.Write( str.c_str( ), str.Length( ) );
            }
            stream_.Write( "\r\n", 2 );
        }

        template <class... Types>
        void Write( const std::format_string<Types...> fmt, Types&&... args )
        {
            auto str = FormatV( fmt.get( ), std::make_format_args( args... ) );
            if ( str )
            {
                stream_.Write( str.c_str( ), str.Length( ) );
            }
        }

        template <class... Types>
        void WriteLine( const std::format_string<Types...> fmt, Types&&... args )
        {
            auto str = FormatV( fmt.get( ), std::make_format_args( args... ) );
            if ( str )
            {
                stream_.Write( str.c_str( ), str.Length( ) );
            }
            stream_.Write( "\r\n", 2 );
        }
        
        void WriteLine( )
        {
            stream_.Write( "\r\n", 2 );
        }

        std::vector<Byte> ToBytes( ) const
        {
            return stream_.ToBytes( );
        }

        void Flush( )
        {
            auto bytes = ToBytes( );
            if ( IO::File::Exist( filename_ ) )
            {
                auto fileBytes = IO::File::ReadAllBytes( filename_ );
                if ( fileBytes == bytes )
                {
                    return;
                }
            }
            IO::File::WriteAllBytes( filename_, bytes );
        }



    };
}


#endif
