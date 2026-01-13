#pragma once
#ifndef __HCCCONVERTERS_H__
#define __HCCCONVERTERS_H__
/*
   Copyright 2024-2026 Espen Harlinn

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

#include <HCCLogging.h>
#include <HCCString.h>
#include <HCCDateTime.h>
#include <HCCGuid.h>
#include <HCCCurrency.h>
#include <HCCVariant.h>
#include <HCCTraits.h>


namespace Harlinn::Common::Core
{
    /// <summary>
    /// A ConvertTo template that performs no conversion
    /// since ResultType must be the same as ArgumentType.
    /// </summary>
    /// <typeparam name="ResultType">
    /// The type to convert to.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// The type to convert from, must be of the same type as ResultType
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, ArgumentType> 
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg;
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// float to double.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be double, the type to convert to.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be float, the type to convert from.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, double>&&
            std::is_same_v<ArgumentType, float> )
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// double to float. Throws an ArgumentOutOfRangeException
    /// if the argument cannot safely be converted to a float.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be float, the type to convert to.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be double, the type to convert from.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
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

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// any type for which there exists an overload of 
    /// ToWideString, except for Variant and Currency,
    /// to WideString. 
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be WideString.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a type for which there exists an overload of 
    /// ToWideString, except for Variant and Currency.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires (requires( ArgumentType a )
        {
            { ToWideString( a ) } -> std::same_as<WideString>;
            
	    }&& IsWideString<ResultType>&& (std::is_same_v<ResultType, ArgumentType> == false) &&
            std::is_same_v<Variant, ArgumentType> == false && std::is_same_v<Currency, ArgumentType> == false )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToWideString( arg );
    }
    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// any type for which there exists an overload of 
    /// ToAnsiString, except for Variant and Currency,
    /// to AnsiString. 
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be WideString.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a type for which there exists an overload of 
    /// ToAnsiString, except for Variant and Currency.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( requires( ArgumentType a )
        {
            { ToAnsiString( a ) } -> std::same_as<AnsiString>;
            
        } && IsAnsiString<ResultType> && 
            std::is_same_v<Variant, ArgumentType> == false && std::is_same_v<Currency, ArgumentType> == false )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ToAnsiString( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// an integer or floating point type, but not bool,
    /// to a bool.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be bool.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be an integer or floating point type, but not bool.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            std::is_arithmetic_v<ArgumentType> && 
            IsNotBoolean<ArgumentType> )
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<bool>( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a bool to an integer or floating point type, but not 
    /// a bool type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be an integer or floating point type, but not bool.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be bool.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ArgumentType, bool> &&
            std::is_arithmetic_v<ResultType> &&
            IsNotBoolean<ResultType> )
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg ? 1 : 0 );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a DateTime or TimeSpan to a bool.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be bool.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be DateTime or TimeSpan.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            ( std::is_same_v<DateTime, ArgumentType> || std::is_same_v<TimeSpan, ArgumentType> ) )
    constexpr inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<bool>( arg.Ticks() );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a type that satisfies the SimpleStringLike concept to a 
    /// type for which there exist a Parse&lt;&gt; specialization
    /// that accepts the argument type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// A type for which there exist a Parse&lt;&gt; specialization
    /// that accepts the argument type.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// A type that satisfies the SimpleStringLike concept.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, SimpleStringLike ArgumentType>
        requires requires( const ArgumentType& a )
        {
            { Parse<ResultType>( a ) }->std::same_as<ResultType>;
        }
    inline ResultType ConvertTo( const ArgumentType& arg )
    {
        return Parse<ResultType>( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a Guid to a bool.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be bool.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be Guid.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            std::is_same_v<Guid, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg.IsEmpty() == false;
    }
    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a Currency to a bool.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be bool.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be Currency.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<ResultType, bool> &&
            std::is_same_v<Currency, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg.Value() != 0;
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a Variant to a type for Which there exist a specialization
    /// of Variant::As&lt;ResultType&gt;.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must not be a Variant, and it must be 
    /// a type for Which there exist a specialization
    /// of Variant::As&lt;ResultType&gt;.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be Variant.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( std::is_same_v<Variant, ArgumentType> && std::is_same_v <Variant,ResultType> == false ) &&
            requires ( Variant v )
            {
                { v.As<ResultType>( ) }->std::same_as<ResultType>;
            }
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg.As<ResultType>( );
    }

    /// <summary>
    /// A ConvertTo template that performs a narrowing conversion from
    /// an integer type to another.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be a smaller integer type than ArgumentType.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a wider integer type than ResultType.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
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

    /// <summary>
    /// A ConvertTo template that performs a widening conversion from
    /// an integer type to another integer type with the same signedness.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be an integer type that is wider or equally sized to 
    /// ArgumentType with the same signedness..
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be an integer type that is narrower or equally sized to 
    /// ArgumentType with the same signedness.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( ((IsSignedInteger<ResultType> && IsSignedInteger<ArgumentType>) ||
            ( IsUnsignedInteger<ResultType> && IsUnsignedInteger<ArgumentType> ) ) &&
            size_is_greater_or_equal< ResultType, ArgumentType> && std::is_same_v<ResultType, ArgumentType> == false )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs a narrowing conversion from
    /// an unsigned integer type to a signed integer type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be a signed integer type that is narrower or equally sized to 
    /// ArgumentType.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a unsigned integer type that is wider or equally sized to 
    /// ResultType.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
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

    /// <summary>
    /// A ConvertTo template that performs a widening conversion from
    /// an unsigned integer type to a signed integer type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be a signed integer type that is wider than 
    /// ArgumentType.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be an unsigned integer type that is narrower than 
    /// ResultType.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires ( IsSignedInteger<ResultType> && IsUnsignedInteger<ArgumentType> &&
            size_is_greater< ResultType, ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs a narrowing conversion from
    /// a signed integer type to an unsigned integer type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be an unsigned integer type that is narrower than 
    /// ArgumentType.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a signed integer type that is wider than 
    /// ResultType.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
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

    /// <summary>
    /// A ConvertTo template that performs a widening conversion from
    /// a signed integer type to an unsigned integer type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be an unsigned integer type that is wider or equally sized to 
    /// ArgumentType.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a signed integer type that is narrower or equally sized to 
    /// ResultType.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
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


    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a floating point type to an integer type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be an integer.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a floating point type.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
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

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a Currency value to an integer, floating point, AnsiString
    /// or WideString type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be an integer, floating point, AnsiString
    /// or WideString type.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be Currency.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires (IsInteger<ResultType> || IsFloatingPoint<ResultType> || IsAnsiString<ResultType> || IsWideString<ResultType> ) && 
            std::is_same_v<ArgumentType,Currency>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return arg.As<ResultType>( );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a DateTime or TimeSpan value to an integer type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be an integer type.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must DateTime or TimeSpan.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
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

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a c style zero terminated string value to a TimeSpan.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be TimeSpan.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be convertible to <c>const char*</c> or <c>const wchar_t*</c>.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan> && 
            (std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> || 
                std::is_nothrow_convertible_v< ArgumentType, const char*>)
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan::Parse( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a type that matches the SimpleStringLike concept to a TimeSpan.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be TimeSpan.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a type that matches the SimpleStringLike concept.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, SimpleStringLike ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan::Parse( arg.c_str() );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a TimeSpan to a floating point type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be a floating point type.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be TimeSpan.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value in number of days.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan> && IsFloatingPoint<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan::FromDays( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a Currency value to a TimeSpan value.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be TimeSpan.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be Currency.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert in number of days.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan> && std::is_same_v<ArgumentType,Currency>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan::FromDays( arg.As<double>() );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// an integer type to a DateTime value.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be DateTime.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be an integer type.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert in ticks.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, DateTime>&& IsInteger<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return DateTime( ConvertTo<Int64>(arg) );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// an integer type to a TimeSpan value.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be TimeSpan.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be an integer type.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert in ticks.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, TimeSpan>&& IsInteger<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return TimeSpan( ConvertTo<Int64>(arg) );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a c style zero terminated string value to a DateTime.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be DateTime.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be convertible to <c>const char*</c> or <c>const wchar_t*</c>.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, DateTime> && 
            (std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> || 
                std::is_nothrow_convertible_v< ArgumentType, const char*>)
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return DateTime::Parse( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a type that matches the SimpleStringLike concept to a DateTime.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be DateTime.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a type that matches the SimpleStringLike concept.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, SimpleStringLike ArgumentType>
        requires std::is_same_v<ResultType, DateTime>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return DateTime::Parse( arg.c_str() );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a floating point type to a DateTime value.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be DateTime.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be a floating point type.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert in number of days before or after midnight, 30 December 1899.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, DateTime> && IsFloatingPoint<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return DateTime::FromOADate( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a DateTime value to a floating point type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be a floating point type.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be DateTime.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value in number of days before or after midnight, 30 December 1899.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires IsFloatingPoint<ResultType> && std::is_same_v<ArgumentType, DateTime>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg.ToOADate( ) );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a TimeSpan value to a floating point type.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be a floating point type.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be TimeSpan.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value in number of days.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires IsFloatingPoint<ResultType> && std::is_same_v<ArgumentType, TimeSpan>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg.TotalDays( ) );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a TimeSpan value to DataTime value, or a conversion
    /// from a DataTime value to TimeSpan value.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be TimeSpan if ArgumentType is DataTime, or
    /// DataTime if ArgumentType is TimeSpan.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be TimeSpan if ResultType is DataTime, or
    /// DataTime if ResultType is TimeSpan.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires (std::is_same_v<ResultType, TimeSpan>&& std::is_same_v<ArgumentType, DateTime>) ||
           ( std::is_same_v<ResultType, DateTime> && std::is_same_v<ArgumentType, TimeSpan> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return ResultType( arg.Ticks() );
    }


    

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// a c style zero terminated string value, or a type that matches
    /// the SimpleStringLike concept, to a Guid.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be Guid.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be convertible to <c>const char*</c> or <c>const wchar_t*</c>,
    /// or a type that matches the SimpleStringLike concept.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires std::is_same_v<ResultType, Guid> && 
            (std::is_nothrow_convertible_v< ArgumentType, const wchar_t*> || 
                std::is_nothrow_convertible_v< ArgumentType, const char*> ||
                SimpleStringLike<ArgumentType> )
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return Guid::Parse( arg );
    }

    /// <summary>
    /// A ConvertTo template that performs conversion from
    /// an integer to a floating point value.
    /// </summary>
    /// <typeparam name="ResultType">
    /// Must be floating point type.
    /// </typeparam>
    /// <typeparam name="ArgumentType">
    /// Must be an integer type.
    /// </typeparam>
    /// <param name="arg">
    /// The value to convert.
    /// </param>
    /// <returns>
    /// The converted value.
    /// </returns>
    template <typename ResultType, typename ArgumentType>
        requires IsFloatingPoint<ResultType> && IsInteger<ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
    {
        return static_cast<ResultType>( arg );
    }



}

#endif
