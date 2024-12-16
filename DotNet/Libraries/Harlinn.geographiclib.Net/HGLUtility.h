#pragma once
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

#pragma managed(push)
#include <GeographicLib/Constants.hpp>
#pragma managed(pop)

using namespace System;

namespace Harlinn::GeographicLib::Net
{
    inline std::string ToUtf8( System::String^ string )
    {
        if ( string )
        {
            array<Byte>^ bytes = System::Text::Encoding::UTF8->GetBytes( string );
            std::string str;
            str.resize( bytes->Length );
            System::Runtime::InteropServices::Marshal::Copy( bytes, 0, IntPtr( str.data( ) ), bytes->Length );
            return str;
        }
        return "";
    }

    inline System::String^ FromUtf8( const std::string& string )
    {
        array<Byte>^ bytes = gcnew array<Byte>( static_cast< int >( string.size( ) ) );
        System::Runtime::InteropServices::Marshal::Copy( IntPtr( const_cast< char* >( string.data( ) ) ), bytes, 0, static_cast< int >( string.size( ) ) );
        return System::Text::Encoding::UTF8->GetString( bytes );
    }

    inline System::String^ FromUtf8( const char* string )
    {
        if ( string )
        {
            auto size = strlen( string );
            array<Byte>^ bytes = gcnew array<Byte>( static_cast< int >( size ) );
            System::Runtime::InteropServices::Marshal::Copy( IntPtr( const_cast< char* >( string ) ), bytes, 0, static_cast< int >( size ) );
            return System::Text::Encoding::UTF8->GetString( bytes );
        }
        return nullptr;
    }


    public ref class GeographicErr : public System::Exception
    {
    public:
        using Base = System::Exception;

        GeographicErr( String^ message )
            : Base( message )
        {
        }

    };

    inline void __declspec( noreturn ) ThrowGeographicErr( const ::GeographicLib::GeographicErr& geographicErr )
    {
        auto message = FromUtf8( geographicErr.what( ) );
        auto exception = gcnew GeographicErr( message );
        throw exception;
    }
}
