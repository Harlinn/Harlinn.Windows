#pragma once
#ifndef __HCCCONVERTERS_H__
#define __HCCCONVERTERS_H__

#include <HCCLogging.h>
#include <HCCString.h>
#include <HCCDateTime.h>
#include <HCCGuid.h>
#include <HCCCurrency.h>
#include <HCCVariant.h>
#include <HCCTraits.h>


namespace Harlinn::Common::Core
{
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, ArgumentType> 
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg;
    }

    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, double>&&
            std::is_same_v<ArgumentType, float> )
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, float>&&
            std::is_same_v<ArgumentType, double> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        if ( std::isnormal( arg ) )
        {
            if ( arg < static_cast<double>( std::numeric_limits<float>::lowest( ) ) ||
                arg > static_cast<double>( std::numeric_limits<float>::max( ) ) )
            {
                HCC_THROW( ArgumentOutOfRangeException );
            }
        }
        return static_cast<ResultType>( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires (requires( ArgumentType a )
        {
            { ToWideString( a ) } -> std::same_as<WideString>;
            
        } && IsWideString<ResultType> && 
            std::is_same_v<Variant, ArgumentType> == false && std::is_same_v<Currency, ArgumentType> == false )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToWideString( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires ( requires( ArgumentType a )
        {
            { ToAnsiString( a ) } -> std::same_as<std::string>;
            
        } && IsAnsiString<ResultType> && 
            std::is_same_v<Variant, ArgumentType> == false && std::is_same_v<Currency, ArgumentType> == false )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToAnsiString( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            std::is_arithmetic_v<ArgumentType> && 
            IsNotBoolean<ArgumentType> )
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<bool>( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ArgumentType, bool> &&
            std::is_arithmetic_v<ResultType> &&
            IsNotBoolean<ResultType> )
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg ? 1 : 0 );
    }

    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            ( std::is_same_v<DateTime, ArgumentType> || std::is_same_v<TimeSpan, ArgumentType> ) )
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<bool>( arg.Ticks() );
    }


    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            ( std::is_same_v<WideString, ArgumentType> || std::is_same_v<std::string, ArgumentType> ) )
    inline ResultType ConvertTo( const ArgumentType& arg )
    {
        return ToBoolean( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            std::is_same_v<Guid, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg.IsEmpty() == false;
    }
    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            std::is_same_v<Currency, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg.Value() != 0;
    }

    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<Variant, ArgumentType> &&
            std::is_same_v <Variant,ResultType> == false )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg.As<ResultType>( );
    }

    template <typename ResultType, typename ArgumentType>
        requires ( ((IsSignedInteger<ResultType> && IsSignedInteger<ArgumentType>) ||
            ( IsUnsignedInteger<ResultType> && IsUnsignedInteger<ArgumentType> ) ) &&
            size_is_less< ResultType, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        if ( arg < static_cast<ArgumentType>( std::numeric_limits<ResultType>::lowest( ) ) ||
                arg > static_cast<ArgumentType>( std::numeric_limits<ResultType>::max( ) ) )
        {
            HCC_THROW( ArgumentOutOfRangeException );
        }
        return static_cast<ResultType>( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires ( ((IsSignedInteger<ResultType> && IsSignedInteger<ArgumentType>) ||
            ( IsUnsignedInteger<ResultType> && IsUnsignedInteger<ArgumentType> ) ) &&
            size_is_greater_or_equal< ResultType, ArgumentType> && std::is_same_v<ResultType, ArgumentType> == false )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg );
    }


    template <typename ResultType, typename ArgumentType>
        requires ( IsSignedInteger<ResultType> && IsUnsignedInteger<ArgumentType> &&
            size_is_less_or_equal< ResultType, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        if ( arg > static_cast<ArgumentType>( std::numeric_limits<ResultType>::max( ) ) )
        {
            HCC_THROW( ArgumentOutOfRangeException );
        }
        return static_cast<ResultType>( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires ( IsSignedInteger<ResultType> && IsUnsignedInteger<ArgumentType> &&
            size_is_greater< ResultType, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg );
    }


    template <typename ResultType, typename ArgumentType>
        requires ( IsUnsignedInteger<ResultType> && IsSignedInteger<ArgumentType> &&
            size_is_less< ResultType, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        if ( arg < 0  ||  
            arg > static_cast<ArgumentType>( std::numeric_limits<ResultType>::max( ) ) )
        {
            HCC_THROW( ArgumentOutOfRangeException );
        }
        return static_cast<ResultType>( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires ( IsUnsignedInteger<ResultType> && IsSignedInteger<ArgumentType> &&
            size_is_greater_or_equal< ResultType, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        if ( arg < 0 )
        {
            HCC_THROW( ArgumentOutOfRangeException );
        }
        return static_cast<ResultType>( arg );
    }



    template <typename ResultType, typename ArgumentType>
        requires IsInteger<ResultType> && IsFloatingPoint<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        if ( arg < static_cast<ArgumentType>( std::numeric_limits<ResultType>::lowest( ) ) ||
            arg > static_cast<ArgumentType>( std::numeric_limits<ResultType>::max( ) ) )
        {
            HCC_THROW( ArgumentOutOfRangeException );
        }
        return static_cast<ResultType>( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires (IsInteger<ResultType> || IsFloatingPoint<ResultType> || IsAnsiString<ResultType> || IsWideString<ResultType> ) && 
            std::is_same_v<ArgumentType,Currency>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg.As<ResultType>( );
    }


    template <typename ResultType, typename ArgumentType>
        requires IsInteger<ResultType> && IsAnyOf_v<ArgumentType,DateTime, TimeSpan>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        if ( arg.Ticks( ) < static_cast<Int64>( std::numeric_limits<ResultType>::lowest( ) ) ||
            arg.Ticks( ) > static_cast<Int64>( std::numeric_limits<ResultType>::max( ) ) )
        {
            HCC_THROW( ArgumentOutOfRangeException );
        }
        return static_cast<ResultType>( arg.Ticks( ) );
    }

    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,SByte> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToSByte( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,Byte> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToByte( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,Int16> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToInt16( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,UInt16> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToUInt16( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,Int32> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToInt32( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,UInt32> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToUInt32( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,Int64> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToInt64( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,UInt64> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToUInt64( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,Single> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToSingle( arg );
    }
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType,Double> && 
            ( IsWideString<ArgumentType> || 
                std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> ||
                IsAnsiString<ArgumentType> ||
                std::is_nothrow_convertible_v< ArgumentType, const char*> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToDouble( arg );
    }


    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan> && 
            (std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> || 
                std::is_nothrow_convertible_v< ArgumentType, const char*>)
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan::Parse( arg );
    }


    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan> && 
            ( IsWideString<ArgumentType> || IsAnsiString<ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan::Parse( arg.c_str() );
    }

    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan> && IsFloatingPoint<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan::FromDays( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan> && std::is_same_v<ArgumentType,Currency>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan::FromDays( arg.As<double>() );
    }

    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, DateTime>&& IsInteger<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return DateTime( ConvertTo<Int64>(arg) );
    }


    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan>&& IsInteger<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan( ConvertTo<Int64>(arg) );
    }


    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, DateTime> && 
            (std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> || 
                std::is_nothrow_convertible_v< ArgumentType, const char*>)
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return DateTime::Parse( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, DateTime> &&
            ( IsWideString<ArgumentType> || IsAnsiString<ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return DateTime::Parse( arg.c_str() );
    }

    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, DateTime> && IsFloatingPoint<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return DateTime::FromOADate( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires IsFloatingPoint<ResultType> && std::is_same_v<ArgumentType, DateTime>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg.ToOADate( ) );
    }

    template <typename ResultType, typename ArgumentType>
        requires IsFloatingPoint<ResultType> && std::is_same_v<ArgumentType, TimeSpan>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg.TotalDays( ) );
    }

    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan>&& std::is_same_v<ArgumentType, DateTime>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ResultType( arg.Ticks() );
    }

    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, DateTime>&& std::is_same_v<ArgumentType, TimeSpan>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ResultType( arg.Ticks() );
    }

    


    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, Guid> && 
            (std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> || 
                std::is_nothrow_convertible_v< ArgumentType, const char*> ||
                IsWideString<ArgumentType> || IsAnsiString<ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return Guid::Parse( arg );
    }

    template <typename ResultType, typename ArgumentType>
        requires IsFloatingPoint<ResultType> && IsInteger<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg );
    }



}

#endif
