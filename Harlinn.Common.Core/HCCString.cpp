#include <pch.h>
#include <HCCString.h>
#include <HCCDateTime.h>
#include <HCCCurrency.h>
#include <HCCVariant.h>
#include <HCCException.h>
#include <HCCMemory.h>

namespace Harlinn::Common::Core
{
#ifdef HCC_WITH_BASIC_STRING
    namespace Internal
    {
        namespace
        {
            constexpr size_t MemoryManagerBlockSize = AnsiString::AllocationGranularity;
            FixedSizeMemoryManager<MemoryManagerBlockSize, 20480> fixedSizeMemoryManager;
        }

        HCC_EXPORT char* AllocateBytes( size_t count )
        {
            if ( count <= MemoryManagerBlockSize )
            {
                return (char*)fixedSizeMemoryManager.Malloc( );
            }
            else
            {
                return (char*)malloc( count );
            }
        }
        HCC_EXPORT void FreeBytes( char* bytes, size_t size )
        {
            if ( size <= MemoryManagerBlockSize )
            {
                fixedSizeMemoryManager.Free( bytes );
            }
            else
            {
                free( bytes );
            }
        }

        HCC_EXPORT void ResetStringFixedSizeMemoryManager( )
        {
            fixedSizeMemoryManager.Reset( );
        }

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

    void ToWideString( const char* source, size_t length, unsigned codePage, unsigned flags, WideString& dest )
    {
        auto byteCount = static_cast<int>( length );
        if ( byteCount )
        {
            auto wideCharCount = MultiByteToWideChar( codePage, flags, source, byteCount, nullptr, 0 );
            if ( !wideCharCount )
            {
                ThrowLastOSError( );
            }
            dest.resize( wideCharCount );
            auto rc = MultiByteToWideChar( codePage, flags, source, byteCount, dest.data( ), wideCharCount );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
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

    WideString ToWideString( Single value, int width, int precission )
    {
        return Format( L"{:0{}.{}f}", value, width, precission );
    }
    WideString ToWideString( Single value, const std::locale& locale )
    {
        return Format( locale, L"{:0f}", value );
    }
    WideString ToWideString( Single value, int width, int precission, const std::locale& locale )
    {
        return Format( locale, L"{:0{}.{}f}", value, width, precission );
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


    void ToAnsiString( const wchar_t* source, size_t length, unsigned codePage, unsigned flags, AnsiString& dest )
    {
        auto wideCharCount = static_cast<int>( length );
        if ( wideCharCount )
        {
            auto byteCount = WideCharToMultiByte( codePage, flags, source, wideCharCount, nullptr, 0, nullptr, nullptr );
            if ( !byteCount )
            {
                ThrowLastOSError( );
            }
            dest.resize( byteCount );
            auto rc = WideCharToMultiByte( codePage, flags, source, wideCharCount, dest.data( ), byteCount, nullptr, nullptr );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
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

    AnsiString ToAnsiString( Single value, int width, int precission )
    {
        return Format( "{:0{}.{}f}", value, width, precission );
    }
    AnsiString ToAnsiString( Single value, const std::locale& locale )
    {
        return Format( locale, "{:0f}", value );
    }
    AnsiString ToAnsiString( Single value, int width, int precission, const std::locale& locale )
    {
        return Format( locale, "{:{}.{}f}", value, width, precission );
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



    bool ToBoolean( const wchar_t* str ) noexcept
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

    bool ToBoolean( const char* str ) noexcept
    {
        auto wstr = ToWideString( str );
        return ToBoolean( wstr );
    }



    Byte ToByte( const wchar_t* str, int radix )
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
    Byte ToByte( const char* str, int radix )
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

    SByte ToSByte( const wchar_t* str, int radix )
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
    SByte ToSByte( const char* str, int radix )
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

    Int16 ToInt16( const wchar_t* str, int radix )
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
    Int16 ToInt16( const char* str, int radix )
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

    UInt16 ToUInt16( const wchar_t* str, int radix )
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
    UInt16 ToUInt16( const char* str, int radix )
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

    Int32 ToInt32( const wchar_t* str, int radix )
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

            return 0xFFFFFFFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    Int32 ToInt32( const char* str, int radix )
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

            return 0xFFFFFFFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    UInt32 ToUInt32( const wchar_t* str, int radix )
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

            return 0xFFFFFFFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }
    UInt32 ToUInt32( const char* str, int radix )
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

            return 0xFFFFFFFF & result;
        }
        else
        {
            throw ArgumentException( L"Not a number", "str" );
        }
    }

    Int64 ToInt64( const wchar_t* str, int radix )
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
    Int64 ToInt64( const char* str, int radix )
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

    UInt64 ToUInt64( const wchar_t* str, int radix )
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
    UInt64 ToUInt64( const char* str, int radix )
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

    Single ToSingle( const wchar_t* str )
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
    Single ToSingle( const char* str )
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

    Double ToDouble( const wchar_t* str )
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
    Double ToDouble( const char* str )
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

}