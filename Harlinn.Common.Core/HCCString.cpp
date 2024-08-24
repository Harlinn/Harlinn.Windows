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

#include <pch.h>
#include <HCCString.h>
#include <HCCDateTime.h>
#include <HCCCurrency.h>
#include <HCCVariant.h>
#include <HCCException.h>
#include <HCCMemory.h>

namespace Harlinn::Common::Core
{
    namespace
    {
        _locale_t GetInvariantNumericLocale( )
        {
            static _locale_t invariantLocale = _wcreate_locale( LC_NUMERIC, L"C" );
            return invariantLocale;
        }

    }

#ifdef HCC_WITH_BASIC_STRING
    namespace Internal
    {
        WideString From( const char* text, size_t textLength, unsigned codePage, unsigned flags )
        {
            auto byteCount = static_cast<int>( textLength );
            if ( byteCount )
            {
                auto wideCharCount = MultiByteToWideChar( codePage, flags, text, byteCount, nullptr, 0 );
                if ( !wideCharCount )
                {
                    ThrowLastOSError( );
                }
                WideString result;
                result.SetLength( wideCharCount );
                auto rc = MultiByteToWideChar( codePage, flags, text, byteCount, result.data( ), wideCharCount );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                return result;
            }
            return WideString( );
        }

        AnsiString From( const wchar_t* text, size_t textLength, unsigned codePage, unsigned flags )
        {
            auto wideCharCount = static_cast<int>( textLength );
            if ( wideCharCount )
            {
                auto byteCount = WideCharToMultiByte( codePage, flags, text, wideCharCount, nullptr, 0, nullptr, nullptr );
                if ( !byteCount )
                {
                    ThrowLastOSError( );
                }
                AnsiString result;
                result.SetLength( byteCount );
                auto rc = WideCharToMultiByte( codePage, flags, text, wideCharCount, result.data( ), byteCount, nullptr, nullptr );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
                return result;
            }
            return AnsiString( );
        }

    }
#endif

    namespace Internal
    {
        void ThrowFixedStringArgumentToLong( size_t size, size_t maxSize )
        {
            auto message = Format( L"Argument string is to long:{}, maximum length is {}.", size, maxSize );
            Exception exc( message );
            throw exc;
        }
    }

    WideString ToWideString( bool value )
    {
        BSTR bstr = nullptr;
        auto hr = VarBstrFromBool( value?VARIANT_TRUE:VARIANT_FALSE, GetSystemDefaultLCID( ), LOCALE_NOUSEROVERRIDE, &bstr );
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
    WideString ToWideString( SByte value, int base )
    {
        wchar_t buffer[33];
        _itow_s( value, buffer, base );
        return WideString( buffer );
    }
    WideString ToWideString( Byte value, int base )
    {
        wchar_t buffer[33];
        _ultow_s( value, buffer, base );
        return WideString( buffer );
    }
    WideString ToWideString( Int16 value, int base )
    {
        wchar_t buffer[33];
        _itow_s( value, buffer, base );
        return WideString( buffer );
    }
    WideString ToWideString( UInt16 value, int base )
    {
        wchar_t buffer[33];
        _ultow_s( value, buffer, base );
        return WideString( buffer );
    }
    WideString ToWideString( Int32 value, int base )
    {
        wchar_t buffer[33];
        _itow_s( value, buffer, base );
        return WideString( buffer );
    }
    WideString ToWideString( UInt32 value, int base )
    {
        wchar_t buffer[33];
        _ultow_s( value, buffer, base );
        return WideString( buffer );
    }
    WideString ToWideString( Int64 value, int base )
    {
        wchar_t buffer[66];
        _i64tow_s( value, buffer, ARRAYSIZE( buffer ), base );
        return WideString( buffer );
    }
    WideString ToWideString( UInt64 value, int base )
    {
        wchar_t buffer[66];
        _ui64tow_s( value, buffer, ARRAYSIZE( buffer ), base );
        return WideString( buffer );
    }

    WideString ToWideStringInvariant( Single value, int width, int precision )
    {
        return ToWideString( value, width, precision, std::locale::classic( ) );
    }
    WideString ToWideStringInvariant( Single value )
    {
        return ToWideString( value, std::locale::classic( ) );
    }

    WideString ToWideString( Single value )
    {
#ifdef HCC_WITH_BASIC_STRING
        const auto length = static_cast< size_t >( _scwprintf( L"%f", value ) );
        WideString str( length, L'\0' );
        swprintf_s( str.data(), length + 1, L"%f", value );
        return str;
#else
        return std::to_wstring( value );
#endif
    }

    WideString ToWideString( Single value, int width, int precision )
    {
        return Format( L"{:0{}.{}f}", value, width, precision );
    }
    WideString ToWideString( Single value, const std::locale& locale )
    {
        return Format( locale, L"{:0f}", value );
    }
    WideString ToWideString( Single value, int width, int precision, const std::locale& locale )
    {
        return Format( locale, L"{:0{}.{}f}", value, width, precision );
    }

    


    WideString ToWideString( Double value )
    {
#ifdef HCC_WITH_BASIC_STRING
        const auto length = static_cast< size_t >( _scwprintf( L"%f", value ) );
        WideString str( length, L'\0' );
        swprintf_s( str.data( ), length + 1, L"%f", value );
        return str;
#else
        return std::to_wstring( value );
#endif
    }
    WideString ToWideString( const DateTime& value )
    {
        return value.ToString( );
    }
    WideString ToWideString( const TimeSpan& value )
    {
        return value.ToString( );
    }
    WideString ToWideString( const Guid& value )
    {
        return value.ToString( );
    }
    WideString ToWideString( const Currency& value )
    {
        return value.ToWideString( );
    }
    WideString ToWideString( const Variant& value )
    {
        return value.AsWideString( );
    }

    [[nodiscard]] WideString ToWideString( const FixedSizeMemoryManagerStatistics& statistics )
    {
        return Format( L"Free count={}, Malloc calls={}, Free calls={}, Aligned Malloc calls={}, Aligned Free calls={}", statistics.FreeCount, statistics.MallocCalls, statistics.FreeCalls, statistics.AlignedMallocCalls, statistics.AlignedFreeCalls );
    }


    

    AnsiString ToAnsiString( bool value )
    {
        return ToAnsiString( ToWideString( value ) );
    }

    AnsiString ToAnsiString( SByte value, int base )
    {
        char buffer[33];
        _itoa_s( value, buffer, base );
        return AnsiString( buffer );
    }
    AnsiString ToAnsiString( Byte value, int base )
    {
        char buffer[33];
        _ultoa_s( value, buffer, base );
        return AnsiString( buffer );
    }
    AnsiString ToAnsiString( Int16 value, int base )
    {
        char buffer[33];
        _itoa_s( value, buffer, base );
        return AnsiString( buffer );
    }
    AnsiString ToAnsiString( UInt16 value, int base )
    {
        char buffer[33];
        _ultoa_s( value, buffer, base );
        return AnsiString( buffer );
    }
    AnsiString ToAnsiString( Int32 value, int base )
    {
        char buffer[33];
        _itoa_s( value, buffer, base );
        return AnsiString( buffer );
    }
    AnsiString ToAnsiString( UInt32 value, int base )
    {
        char buffer[33];
        _ultoa_s( value, buffer, base );
        return AnsiString( buffer );
    }
    AnsiString ToAnsiString( Int64 value, int base )
    {
        char buffer[66];
        _i64toa_s( value, buffer, ARRAYSIZE( buffer ), base );
        return AnsiString( buffer );
    }
    AnsiString ToAnsiString( UInt64 value, int base )
    {
        char buffer[66];
        _ui64toa_s( value, buffer, ARRAYSIZE( buffer ), base );
        return AnsiString( buffer );
    }
    AnsiString ToAnsiString( Single value )
    {
#ifdef HCC_WITH_BASIC_STRING
        const auto length = static_cast< size_t >( _scprintf( "%f", value ) );
        AnsiString str( length, '\0' );
        sprintf_s( str.data( ), length + 1, "%f", value );
        return str;
#else
        return std::to_string( value );
#endif
    }

    AnsiString ToAnsiStringInvariant( Single value, int width, int precision )
    {
        return ToAnsiString( value, width, precision, std::locale::classic() );
    }

    AnsiString ToAnsiStringInvariant( Single value )
    {
        return ToAnsiString( value, std::locale::classic( ) );
    }


    AnsiString ToAnsiString( Single value, int width, int precision )
    {
        return Format( "{:0{}.{}f}", value, width, precision );
    }
    AnsiString ToAnsiString( Single value, const std::locale& locale )
    {
        return Format( locale, "{:0f}", value );
    }
    AnsiString ToAnsiString( Single value, int width, int precision, const std::locale& locale )
    {
        return Format( locale, "{:0{}.{}f}", value, width, precision );
    }

    AnsiString ToAnsiStringInvariant( Double value, int width, int precision )
    {
        return ToAnsiString( value, width, precision, std::locale::classic( ) );
    }
    AnsiString ToAnsiStringInvariant( Double value )
    {
        return ToAnsiString( value, std::locale::classic( ) );
    }

    AnsiString ToAnsiString( Double value )
    {
#ifdef HCC_WITH_BASIC_STRING
        const auto length = static_cast< size_t >( _scprintf( "%f", value ) );
        AnsiString str( length, '\0' );
        sprintf_s( str.data( ), length + 1, "%f", value );
        return str;
#else
        return std::to_string( value );
#endif
    }

    AnsiString ToAnsiString( Double value, const std::locale& locale )
    {
        return Format( locale, "{:0f}", value );
    }
    AnsiString ToAnsiString( Double value, int width, int precision )
    {
        return Format( "{:0{}.{}f}", value, width, precision );
    }
    AnsiString ToAnsiString( Double value, int width, int precision, const std::locale& locale )
    {
        return Format( locale, "{:0{}.{}f}", value, width, precision );
    }

    AnsiString ToAnsiString( const DateTime& value )
    {
        return ToAnsiString(value.ToString( ));
    }
    AnsiString ToAnsiString( const TimeSpan& value )
    {
        return ToAnsiString( value.ToString( ) );
    }
    AnsiString ToAnsiString( const Guid& value )
    {
        return ToAnsiString( value.ToString( ) );
    }
    AnsiString ToAnsiString( const Currency& value )
    {
        return ToAnsiString( value.ToWideString( ) );
    }
    AnsiString ToAnsiString( const Variant& value )
    {
        return ToAnsiString( value.AsWideString( ) );
    }

    [[nodiscard]] AnsiString ToAnsiString( const FixedSizeMemoryManagerStatistics& statistics )
    {
        return Format( "Free count={}, Malloc calls={}, Free calls={}, Aligned Malloc calls={}, Aligned Free calls={}", statistics.FreeCount, statistics.MallocCalls, statistics.FreeCalls, statistics.AlignedMallocCalls, statistics.AlignedFreeCalls );
    }



    bool ParseBoolean( const wchar_t* str ) noexcept
    {
        if ( str != nullptr && str[0] )
        {
            VARIANT_BOOL result = VARIANT_FALSE;
            auto hr = VarBoolFromStr( str, LOCALE_USER_DEFAULT /*GetUserDefaultLCID()*/, VAR_LOCALBOOL, &result );
            if ( hr == S_OK && result == VARIANT_TRUE )
            {
                return true;
            }
            if ( hr != S_OK )
            {
                hr = VarBoolFromStr( str, MAKELCID( LANG_INVARIANT, SUBLANG_NEUTRAL ), LOCALE_NOUSEROVERRIDE, &result );
                if ( hr == S_OK && result == VARIANT_TRUE )
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool ParseBoolean( const char* str ) noexcept
    {
        auto wstr = ToWideString( str );
        return ParseBoolean( wstr );
    }

    bool TryParseBoolean( const wchar_t* str, bool& value ) noexcept
    {
        if ( str != nullptr && str[ 0 ] )
        {
            VARIANT_BOOL result = VARIANT_FALSE;
            auto hr = VarBoolFromStr( str, LOCALE_USER_DEFAULT, VAR_LOCALBOOL, &result );
            if ( hr == S_OK )
            {
                value = result == VARIANT_TRUE;
                return true;
            }
            else
            {
                hr = VarBoolFromStr( str, MAKELCID( LANG_INVARIANT, SUBLANG_NEUTRAL ), LOCALE_NOUSEROVERRIDE, &result );
                if ( hr == S_OK )
                {
                    value = result == VARIANT_TRUE;
                    return true;
                }
            }
        }
        return false;
    }

    bool TryParseBoolean( const char* str, bool& value ) noexcept
    {
        auto wstr = ToWideString( str );
        return TryParseBoolean( wstr.c_str(), value );
    }



    Byte ParseByte( const wchar_t* str, int radix )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT8_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return 0xFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    Byte ParseByte( const char* str, int radix )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT8_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return 0xFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseByte( const wchar_t* str,Byte& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT8_MAX )
            {
                return false;
            }

            value = 0xFF & result;
            return true;
        }
        return false;
    }
    bool TryParseByte( const char* str, Byte& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT8_MAX )
            {
                return false;
            }

            value = 0xFF & result;
            return true;
        }
        return false;
    }

    SByte ParseSByte( const wchar_t* str, int radix )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == LONG_MAX || result == LONG_MIN ) && errno == ERANGE ) ||
                result < INT8_MIN || result > INT8_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return 0xFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    SByte ParseSByte( const char* str, int radix )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == LONG_MAX || result == LONG_MIN ) && errno == ERANGE ) ||
                result < INT8_MIN || result > INT8_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return 0xFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseSByte( const wchar_t* str, SByte& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result < INT8_MIN || result > INT8_MAX )
            {
                return false;
            }

            value = 0xFF & result;
            return true;
        }
        return false;
    }
    bool TryParseSByte( const char* str, SByte& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result < INT8_MIN || result > INT8_MAX )
            {
                return false;
            }

            value = 0xFF & result;
            return true;
        }
        return false;
    }


    Int16 ParseInt16( const wchar_t* str, int radix )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == LONG_MAX || result == LONG_MIN ) && errno == ERANGE ) ||
                result < INT16_MIN || result > INT16_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return 0xFFFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    Int16 ParseInt16( const char* str, int radix )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == LONG_MAX || result == LONG_MIN ) && errno == ERANGE ) ||
                result < INT16_MIN || result > INT16_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return 0xFFFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseInt16( const wchar_t* str, Int16& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result < INT16_MIN || result > INT16_MAX )
            {
                return false;
            }

            value = 0xFFFF & result;
            return true;
        }
        return false;
    }
    bool TryParseInt16( const char* str, Int16& value, int radix  ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result < INT16_MIN || result > INT16_MAX )
            {
                return false;
            }

            value = 0xFFFF & result;
            return true;
        }
        return false;
    }

    UInt16 ParseUInt16( const wchar_t* str, int radix )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT16_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return 0xFFFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    UInt16 ParseUInt16( const char* str, int radix )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT16_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return 0xFFFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseUInt16( const wchar_t* str, UInt16& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT16_MAX )
            {
                return false;
            }

            value = 0xFFFF & result;
            return true;
        }
        return false;
    }
    bool TryParseUInt16( const char* str, UInt16& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT16_MAX )
            {
                return false;
            }

            value = 0xFFFF & result;
            return true;
        }
        return false;
    }


    Int32 ParseInt32( const wchar_t* str, int radix )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == LONG_MAX || result == LONG_MIN ) && errno == ERANGE ) ||
                result < INT32_MIN || result > INT32_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    Int32 ParseInt32( const char* str, int radix )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == LONG_MAX || result == LONG_MIN ) && errno == ERANGE ) ||
                result < INT32_MIN || result > INT32_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseInt32( const wchar_t* str, Int32& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result < INT32_MIN || result > INT32_MAX )
            {
                return false;
            }

            value = result;
            return true;
        }
        return false;
    }
    bool TryParseInt32( const char* str, Int32& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtol( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result < INT32_MIN || result > INT32_MAX )
            {
                return false;
            }

            value = result;
            return true;
        }
        return false;
    }


    UInt32 ParseUInt32( const wchar_t* str, int radix )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT32_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    UInt32 ParseUInt32( const char* str, int radix )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT32_MAX )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }

            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseUInt32( const wchar_t* str, UInt32& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT32_MAX )
            {
                return false;
            }

            value = result;
            return true;
        }
        return false;
    }
    bool TryParseUInt32( const char* str, UInt32& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtoul( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT32_MAX )
            {
                return false;
            }

            value = result;
            return true;
        }
        return false;
    }

    Int64 ParseInt64( const wchar_t* str, int radix )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoll( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == LLONG_MAX || result == LLONG_MIN ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    Int64 ParseInt64( const char* str, int radix )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtoll( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == LLONG_MAX || result == LLONG_MIN ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseInt64( const wchar_t* str, Int64& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoll( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result < INT32_MIN || result > INT32_MAX )
            {
                return false;
            }

            value = result;
            return true;
        }
        return false;
    }
    bool TryParseInt64( const char* str, Int64& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtoll( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result < INT32_MIN || result > INT32_MAX )
            {
                return false;
            }

            value = result;
            return true;
        }
        return false;
    }



    UInt64 ParseUInt64( const wchar_t* str, int radix )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoull( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( result == ULLONG_MAX && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    UInt64 ParseUInt64( const char* str, int radix )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtoull( str, &end, radix );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( result == ULLONG_MAX && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseUInt64( const wchar_t* str, UInt64& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstoull( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT32_MAX )
            {
                return false;
            }

            value = result;
            return true;
        }
        return false;
    }
    bool TryParseUInt64( const char* str, UInt64& value, int radix ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtoull( str, &end, radix );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( ( result == ULONG_MAX ) && errno == ERANGE ) ||
                result > UINT32_MAX )
            {
                return false;
            }

            value = result;
            return true;
        }
        return false;
    }



    Single ParseSingle( const wchar_t* str )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstof( str, &end );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == HUGE_VALF || result == -HUGE_VALF ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    Single ParseSingle( const char* str )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtof( str, &end );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == HUGE_VALF || result == -HUGE_VALF ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseSingle( const wchar_t* str, float& value ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstof( str, &end );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( result == HUGE_VALF || result == -HUGE_VALF ) && errno == ERANGE )
            {
                return false;
            }
            value = result;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool TryParseSingle( const char* str, float& value ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtof( str, &end );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( result == HUGE_VALF || result == -HUGE_VALF ) && errno == ERANGE )
            {
                return false;
            }
            value = result;
            return true;
        }
        else
        {
            return false;
        }
    }



    


    Single ParseSingleInvariant( const wchar_t* str )
    {
        if ( str && str[ 0 ] )
        {
            static _locale_t invariantLocale = GetInvariantNumericLocale( );
            wchar_t* end = nullptr;
            auto result = _wcstof_l( str, &end, invariantLocale );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == HUGE_VALF || result == -HUGE_VALF ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    Single ParseSingleInvariant( const char* str )
    {
        if ( str && str[ 0 ] )
        {
            static _locale_t invariantLocale = GetInvariantNumericLocale( );
            char* end = nullptr;
            auto result = _strtof_l( str, &end, invariantLocale );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == HUGE_VALF || result == -HUGE_VALF ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseSingleInvariant( const wchar_t* str, float& value ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            static _locale_t invariantLocale = GetInvariantNumericLocale( );
            wchar_t* end = nullptr;
            auto result = _wcstof_l( str, &end, invariantLocale );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( result == HUGE_VALF || result == -HUGE_VALF ) && errno == ERANGE )
            {
                return false;
            }
            value = result;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool TryParseSingleInvariant( const char* str, float& value ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            static _locale_t invariantLocale = GetInvariantNumericLocale( );
            char* end = nullptr;
            auto result = _strtof_l( str, &end, invariantLocale );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( result == HUGE_VALF || result == -HUGE_VALF ) && errno == ERANGE )
            {
                return false;
            }
            value = result;
            return true;
        }
        else
        {
            return false;
        }
    }


    Double ParseDouble( const wchar_t* str )
    {
        if ( str && str[0] )
        {
            wchar_t* end = nullptr;
            auto result = wcstod( str, &end );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == HUGE_VAL || result == -HUGE_VAL ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    Double ParseDouble( const char* str )
    {
        if ( str && str[0] )
        {
            char* end = nullptr;
            auto result = strtod( str, &end );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == HUGE_VAL || result == -HUGE_VAL ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseDouble( const wchar_t* str, double& value ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            wchar_t* end = nullptr;
            auto result = wcstod( str, &end );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( result == HUGE_VAL || result == -HUGE_VAL ) && errno == ERANGE )
            {
                return false;
            }
            value = result;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool TryParseDouble( const char* str, double& value ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            char* end = nullptr;
            auto result = strtod( str, &end );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( result == HUGE_VAL || result == -HUGE_VAL ) && errno == ERANGE )
            {
                return false;
            }
            value = result;
            return true;
        }
        else
        {
            return false;
        }
    }


    double ParseDoubleInvariant( const wchar_t* str )
    {
        if ( str && str[ 0 ] )
        {
            static _locale_t invariantLocale = GetInvariantNumericLocale( );
            wchar_t* end = nullptr;
            auto result = _wcstod_l( str, &end, invariantLocale );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == HUGE_VAL || result == -HUGE_VAL ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    double ParseDoubleInvariant( const char* str )
    {
        if ( str && str[ 0 ] )
        {
            static _locale_t invariantLocale = GetInvariantNumericLocale( );
            char* end = nullptr;
            auto result = _strtod_l( str, &end, invariantLocale );
            if ( result == 0 && str == end )
            {
                throw ArgumentException( L"Not a number", "str" );
            }
            if ( ( result == HUGE_VAL || result == -HUGE_VAL ) && errno == ERANGE )
            {
                throw ArgumentException( L"Value out of range", "str" );
            }
            return result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    bool TryParseDoubleInvariant( const wchar_t* str, double& value ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            static _locale_t invariantLocale = GetInvariantNumericLocale( );
            wchar_t* end = nullptr;
            auto result = _wcstod_l( str, &end, invariantLocale );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( result == HUGE_VAL || result == -HUGE_VAL ) && errno == ERANGE )
            {
                return false;
            }
            value = result;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool TryParseDoubleInvariant( const char* str, double& value ) noexcept
    {
        if ( str && str[ 0 ] )
        {
            static _locale_t invariantLocale = GetInvariantNumericLocale( );
            char* end = nullptr;
            auto result = _strtod_l( str, &end, invariantLocale );
            if ( result == 0 && str == end )
            {
                return false;
            }
            if ( ( result == HUGE_VAL || result == -HUGE_VAL ) && errno == ERANGE )
            {
                return false;
            }
            value = result;
            return true;
        }
        else
        {
            return false;
        }
    }



}