#include "pch.h"
#include <HCCCurrency.h>
#include <HCCLogging.h>
#include <HCCString.h>

namespace Harlinn::Common::Core
{
    HCC_EXPORT std::wstring Currency::ToWideString( ) const
    {
        CY cy;
        cy.int64 = value_;
        BSTR bstr = nullptr;
        auto hr = VarBstrFromCy( cy, GetSystemDefaultLCID( ), LOCALE_NOUSEROVERRIDE, &bstr );
        CheckHRESULT( hr );
        if ( bstr )
        {
            size_t length = static_cast<size_t>( SysStringLen( bstr ) );
            std::wstring result( bstr, length );
            SysFreeString( bstr );
            return result;
        }
        else
        {
            return std::wstring( );
        }
    }

    std::string Currency::ToAnsiString( ) const
    {
        return Core::ToAnsiString( ToWideString( ) );
    }

    bool Currency::TryParse( const wchar_t* text, Currency& result )
    {
        CY cy{};
        auto hr = VarCyFromStr( text, GetSystemDefaultLCID( ), LOCALE_NOUSEROVERRIDE, &cy );
        if ( hr == S_OK )
        {
            result = cy;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Currency::TryParse( const char* text, Currency& result )
    {
        auto s = Core::ToWideString( text );
        return TryParse( s.c_str( ), result );
    }
    Currency Currency::Parse( const wchar_t* text )
    {
        Currency currency;
        if ( TryParse( text, currency ) )
        {
            return currency;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid currency" );
        }
    }
    Currency Currency::Parse( const char* text )
    {
        Currency currency;
        if ( TryParse( text, currency ) )
        {
            return currency;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid currency" );
        }
    }


}