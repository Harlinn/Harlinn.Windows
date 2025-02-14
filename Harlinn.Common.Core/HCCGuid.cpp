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
#include <HCCGuid.h>
#include <HCCString.h>
#include <HCCLogging.h>

namespace Harlinn::Common::Core
{
    Guid::Guid( const char* uuid )
        : data_( )
    {
        auto s = Core::ToWideString( uuid );
        auto hr = IIDFromString( s.c_str( ), (LPIID)&data_ );
        if ( hr != S_OK )
        {
            CheckHRESULT( hr );
        }
    }

    Guid::Guid( const wchar_t* uuid )
        : data_( )
    {
        auto hr = IIDFromString( uuid, (LPIID)&data_ );
        if ( hr != S_OK )
        {
            CheckHRESULT( hr );
        }
    }

    Guid::Guid( const AnsiString& uuid )
        : data_( )
    {
        auto s = Core::ToWideString( uuid );
        auto hr = IIDFromString( s.c_str( ), (LPIID)&data_ );
        if ( hr != S_OK )
        {
            CheckHRESULT( hr );
        }
    }
    Guid::Guid( const WideString& uuid )
        : data_( )
    {
        auto hr = IIDFromString( uuid.c_str(), (LPIID)&data_ );
        if ( hr != S_OK )
        {
            CheckHRESULT( hr );
        }
    }

    bool Guid::TryParse( const char* uuid, Guid& result )
    {
        auto s = Core::ToWideString( uuid );
        auto hr = IIDFromString( s.c_str(), (LPIID)&result.data_ );
        if ( hr != S_OK )
        {
            result = GUID{ 0, };
            return false;
        }
        return true;
    }
    bool Guid::TryParse( const wchar_t* uuid, Guid& result ) noexcept
    {
        auto hr = IIDFromString( uuid, (LPIID)&result.data_ );
        if ( hr != S_OK )
        {
            result = GUID{ 0, };
            return false;
        }
        return true;
    }
    bool Guid::TryParse( const AnsiString& uuid, Guid& result )
    {
        auto s = Core::ToWideString( uuid );
        auto hr = IIDFromString( s.c_str( ), (LPIID)&result.data_ );
        if ( hr != S_OK )
        {
            result = GUID{ 0, };
            return false;
        }
        return true;
    }
    bool Guid::TryParse( const WideString& uuid, Guid& result ) noexcept
    {
        auto hr = IIDFromString( uuid.c_str(), (LPIID)&result.data_ );
        if ( hr != S_OK )
        {
            result = GUID{ 0, };
            return false;
        }
        return true;
    }

    Guid Guid::Parse( const char* uuid )
    {
        Guid guid;
        if ( TryParse( uuid, guid ) )
        {
            return guid;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid GUID" );
        }
    }
    Guid Guid::Parse( const wchar_t* uuid )
    {
        Guid guid;
        if ( TryParse( uuid, guid ) )
        {
            return guid;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid GUID" );
        }
    }
    Guid Guid::Parse( const AnsiString& uuid )
    {
        Guid guid;
        if ( TryParse( uuid, guid ) )
        {
            return guid;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid GUID" );
        }
    }
    Guid Guid::Parse( const WideString& uuid )
    {
        Guid guid;
        if ( TryParse( uuid, guid ) )
        {
            return guid;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid GUID" );
        }
    }


    WideString Guid::ToWideString( ) const
    {
        LPOLESTR ptr = nullptr;
        auto hr = StringFromIID( *this, &ptr );
        if ( SUCCEEDED( hr ) )
        {
            WideString result( ptr );
            CoTaskMemFree( ptr );
            return result;
        }
        else
        {
            CheckHRESULT( hr );
            return {};
        }
    }

    AnsiString Guid::ToAnsiString( ) const
    {
        return Core::ToAnsiString( ToWideString( ) );
    }

    namespace
    {
        bool IsHexadecimal( wchar_t value )
        {
            if ( value >= L'0' && value <= L'9' )
            {
                return true;
            }
            if ( value >= L'A' && value <= L'F' )
            {
                return true;
            }
            if ( value >= L'a' && value <= L'f' )
            {
                return true;
            }
            return false;
        }
        bool IsGuidImpl( const wchar_t* ptr )
        {
            // 8        4    4    4    12
            //"97AF57A2-4079-4C9A-8033-8A254E021C12"
            return IsHexadecimal( ptr[ 0 ] ) && IsHexadecimal( ptr[ 1 ] ) && IsHexadecimal( ptr[ 2 ] ) && IsHexadecimal( ptr[ 3 ] ) &&
                IsHexadecimal( ptr[ 4 ] ) && IsHexadecimal( ptr[ 5 ] ) && IsHexadecimal( ptr[ 6 ] ) && IsHexadecimal( ptr[ 7 ] ) &&
                ptr[ 8 ] == L'-' &&
                IsHexadecimal( ptr[ 9 ] ) && IsHexadecimal( ptr[ 10 ] ) && IsHexadecimal( ptr[ 11 ] ) && IsHexadecimal( ptr[ 12 ] ) &&
                ptr[ 13 ] == L'-' &&
                IsHexadecimal( ptr[ 14 ] ) && IsHexadecimal( ptr[ 15 ] ) && IsHexadecimal( ptr[ 16 ] ) && IsHexadecimal( ptr[ 17 ] ) &&
                ptr[ 18 ] == L'-' &&
                IsHexadecimal( ptr[ 19 ] ) && IsHexadecimal( ptr[ 20 ] ) && IsHexadecimal( ptr[ 21 ] ) && IsHexadecimal( ptr[ 22 ] ) &&
                ptr[ 23 ] == L'-' &&
                IsHexadecimal( ptr[ 24 ] ) && IsHexadecimal( ptr[ 25 ] ) && IsHexadecimal( ptr[ 26 ] ) && IsHexadecimal( ptr[ 27 ] ) &&
                IsHexadecimal( ptr[ 28 ] ) && IsHexadecimal( ptr[ 29 ] ) && IsHexadecimal( ptr[ 30 ] ) && IsHexadecimal( ptr[ 31 ] ) &&
                IsHexadecimal( ptr[ 32 ] ) && IsHexadecimal( ptr[ 33 ] ) && IsHexadecimal( ptr[ 34 ] ) && IsHexadecimal( ptr[ 35 ] );
        }
    }
    bool Guid::IsGuid( const WideString& uuid )
    {
        //"{97AF57A2-4079-4C9A-8033-8A254E021C12}"
        auto length = uuid.Length( );
        auto ptr = uuid.c_str( );
        if ( length == 38 && ptr[ 0 ] == L'{' && ptr[ 37 ] == L'}' )
        {
            return IsGuidImpl( ptr + 1 );
        }
        else if ( length == 36 )
        {
            return IsGuidImpl( ptr );
        }
        return false;

    }


    Guid Guid::NewGuid( )
    {
        Guid result;
        auto hr = CoCreateGuid( (GUID*)&result );
        CheckHRESULT( hr );
        return result;
    }

    HCC_EXPORT std::ostream& operator << ( std::ostream& stream, const Guid& guid )
    {
        auto str = guid.ToAnsiString( );
        stream << str;
        return stream;
    }

}