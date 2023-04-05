#include "pch.h"
#include <HCCGuid.h>
#include <HCCString.h>
#include <HCCLogging.h>

namespace Harlinn::Common::Core
{
    Guid::Guid( const char* uuid )
        : data_( )
    {
        auto s = ToWideString( uuid );
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

    Guid::Guid( const std::string& uuid )
        : data_( )
    {
        auto s = ToWideString( uuid );
        auto hr = IIDFromString( s.c_str( ), (LPIID)&data_ );
        if ( hr != S_OK )
        {
            CheckHRESULT( hr );
        }
    }
    Guid::Guid( const std::wstring& uuid )
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
        auto s = ToWideString( uuid );
        auto hr = IIDFromString( s.c_str(), (LPIID)&result.data_ );
        if ( hr != S_OK )
        {
            result = GUID{ 0, };
            return false;
        }
        return true;
    }
    bool Guid::TryParse( const wchar_t* uuid, Guid& result )
    {
        auto hr = IIDFromString( uuid, (LPIID)&result.data_ );
        if ( hr != S_OK )
        {
            result = GUID{ 0, };
            return false;
        }
        return true;
    }
    bool Guid::TryParse( const std::string& uuid, Guid& result )
    {
        auto s = ToWideString( uuid );
        auto hr = IIDFromString( s.c_str( ), (LPIID)&result.data_ );
        if ( hr != S_OK )
        {
            result = GUID{ 0, };
            return false;
        }
        return true;
    }
    bool Guid::TryParse( const std::wstring& uuid, Guid& result )
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
    Guid Guid::Parse( const std::string& uuid )
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
    Guid Guid::Parse( const std::wstring& uuid )
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


    std::wstring Guid::ToString( ) const
    {
        LPOLESTR ptr = nullptr;
        auto hr = StringFromIID( *this, &ptr );
        if ( SUCCEEDED( hr ) )
        {
            std::wstring result( ptr );
            CoTaskMemFree( ptr );
            return result;
        }
        else
        {
            CheckHRESULT( hr );
            return std::wstring( );
        }
    }

    std::string Guid::ToAnsiString( ) const
    {
        return Core::ToAnsiString( ToString( ) );
    }


    Guid Guid::NewGuid( )
    {
        Guid result;
        auto hr = CoCreateGuid( (GUID*)&result );
        CheckHRESULT( hr );
        return result;
    }



}