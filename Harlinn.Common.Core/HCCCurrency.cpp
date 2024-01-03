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

#include "pch.h"
#include <HCCCurrency.h>
#include <HCCLogging.h>
#include <HCCString.h>

namespace Harlinn::Common::Core
{
    HCC_EXPORT WideString Currency::ToWideString( ) const
    {
        CY cy;
        cy.int64 = value_;
        BSTR bstr = nullptr;
        auto hr = VarBstrFromCy( cy, GetSystemDefaultLCID( ), LOCALE_NOUSEROVERRIDE, &bstr );
        CheckHRESULT( hr );
        if ( bstr )
        {
            size_t length = static_cast<size_t>( SysStringLen( bstr ) );
            WideString result( bstr, length );
            SysFreeString( bstr );
            return result;
        }
        else
        {
            return {};
        }
    }

    AnsiString Currency::ToAnsiString( ) const
    {
        return Core::ToAnsiString( ToWideString( ) );
    }

    template<>
    WideString Currency::As<WideString>( ) const
    {
        return ToWideString( );
    }
    template<>
    AnsiString Currency::As<AnsiString>( ) const
    {
        return ToAnsiString( );
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