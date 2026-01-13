#pragma once
#ifndef __HCCBITCONVERTER_H__
#define __HCCBITCONVERTER_H__
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

#include <HCCException.h>
#include <HCCString.h>
#include <HCCDateTime.h>
#include <HCCCurrency.h>
#include <HCCGuid.h>


/// <summary>
/// The BitConverter namespace contains methods for 
/// converting a SimpleByteSpanLike container to one of the base data
/// types, as well as for converting a base data type to a 
/// vector of bytes. 
/// </summary>
namespace Harlinn::Common::Core::BitConverter
{
    
    // This value indicates the "endianess" of the architecture.
    // The value is set to true if the architecture is 
    // little endian; false if it is big endian.
#if BIGENDIAN 
    constexpr bool IsLittleEndian = false;
    constexpr bool IsBigEndian = true;
#else
    constexpr bool IsLittleEndian = true;
    constexpr bool IsBigEndian = false;
#endif

    // Converts a bool into a vector of bytes with length one.
    inline std::vector<byte> GetBytes( bool value )
    {
        std::vector<byte> result( 1, value ? static_cast< Byte >( 1U ) : static_cast< Byte >( 0U ) );
        return result;
    }

    // Converts a bool into a std::array<Byte,1>.
    constexpr inline std::array<Byte,1> GetArray( bool value )
    {
        std::array<Byte, 1> result{ value ? static_cast<Byte>( 1U ) : static_cast< Byte >( 0U ) };
        return result;
    }


    // Converts a char into a vector of bytes with length one. 
    inline std::vector<byte> GetBytes( char value )
    {
        std::vector<byte> result( 1, std::bit_cast< Byte >( value ) );
        return result;
    }

    // Converts a char into a std::array<Byte,1>.
    constexpr inline std::array<Byte, 1> GetArray( char value )
    {
        std::array<Byte, 1> result{ std::bit_cast< Byte >( value ) };
        return result;
    }

    // Converts a SByte into a vector of bytes with length one. 
    inline std::vector<byte> GetBytes( SByte value )
    {
        std::vector<byte> result( 1, std::bit_cast< Byte >( value ) );
        return result;
    }

    // Converts a SByte into a std::array<Byte,1>.
    constexpr inline std::array<Byte, 1> GetArray( SByte value )
    {
        std::array<Byte, 1> result{ std::bit_cast< Byte >( value ) };
        return result;
    }

    // Converts a Byte into a vector of bytes with length one. 
    inline std::vector<byte> GetBytes( Byte value )
    {
        std::vector<byte> result( 1, value );
        return result;
    }

    // Converts a Byte into a std::array<Byte,1>.
    constexpr inline std::array<Byte, 1> GetArray( Byte value )
    {
        std::array<Byte, 1> result{ value };
        return result;
    }

    // Converts a wchar_t into a vector of bytes with length two. 
    inline std::vector<byte> GetBytes( wchar_t value )
    {
        std::vector<byte> result( 2 );
        wchar_t* ptr = reinterpret_cast<wchar_t*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a Byte into a std::array<Byte,2>.
    constexpr inline std::array<Byte, 2> GetArray( wchar_t value )
    {
        std::array<Byte, 2> result{ static_cast< Byte >( value ), static_cast< Byte >( value >> 8 ) };
        return result;
    }

    // Converts a short into a vector of bytes with length two.
    inline std::vector<byte> GetBytes( short value )
    {
        std::vector<byte> result( 2 );
        short* ptr = reinterpret_cast< short* >( result.data( ) );
        *ptr = value;
        return result;
    }


    // Converts a short into a std::array<Byte,2>.
    constexpr inline std::array<Byte, 2> GetArray( short value )
    {
        std::array<Byte, 2> result{ static_cast< Byte >( value ), static_cast< Byte >( value >> 8 ) };
        return result;
    }

    // Converts a short into a vector of bytes with length two.
    inline std::vector<byte> GetBytes( unsigned short value )
    {
        std::vector<byte> result( 2 );
        short* ptr = reinterpret_cast< short* >( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts an unsigned short into a std::array<Byte,2>.
    constexpr inline std::array<Byte, 2> GetArray( unsigned short value )
    {
        std::array<Byte, 2> result{ static_cast< Byte >( value ), static_cast< Byte >( value >> 8 ) };
        return result;
    }


    

    // Converts an int into a vector of bytes with length four.
    inline std::vector<byte> GetBytes( int value )
    {
        std::vector<byte> result( 4 );
        int* ptr = reinterpret_cast<int*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts an int into a std::array<Byte,4>.
    constexpr inline std::array<Byte, 4> GetArray( int value )
    {
        std::array<Byte, 4> result{ static_cast< Byte >( value ), static_cast< Byte >( value >> 8 ), static_cast< Byte >( value >> 16 ), static_cast< Byte >( value >> 24 ) };
        return result;
    }

    // Converts a long long into a vector of bytes with length eight. 
    inline std::vector<byte> GetBytes( long long value )
    {
        std::vector<byte> result( 8 );
        long long* ptr = reinterpret_cast<long long*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a long long into a std::array<Byte,8>.
    constexpr inline std::array<Byte, 8> GetArray( long long value )
    {
        std::array<Byte, 8> result{ static_cast< Byte >( value ), static_cast< Byte >( value >> 8 ), static_cast< Byte >( value >> 16 ), static_cast< Byte >( value >> 24 ),
        static_cast< Byte >( value >> 32 ), static_cast< Byte >( value >> 40 ), static_cast< Byte >( value >> 48 ), static_cast< Byte >( value >> 56 ) };
        return result;
    }

    // Converts an uint into a vector of bytes with length four.
    inline std::vector<byte> GetBytes( unsigned int value )
    {
        std::vector<byte> result( 4 );
        unsigned int* ptr = reinterpret_cast<unsigned int*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts an unsigned int into a std::array<Byte,4>.
    constexpr inline std::array<Byte, 4> GetArray( unsigned int value )
    {
        std::array<Byte, 4> result{ static_cast< Byte >( value ), static_cast< Byte >( value >> 8 ), static_cast< Byte >( value >> 16 ), static_cast< Byte >( value >> 24 ) };
        return result;
    }

    // Converts an unsigned long into a vector of bytes with length eight. 
    inline std::vector<byte> GetBytes( unsigned long long value )
    {
        std::vector<byte> result( 8 );
        unsigned long long* ptr = reinterpret_cast<unsigned long long*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts an unsigned long long into a std::array<Byte,8>.
    constexpr inline std::array<Byte, 8> GetArray( unsigned long long value )
    {
        std::array<Byte, 8> result{ static_cast< Byte >( value ), static_cast< Byte >( value >> 8 ), static_cast< Byte >( value >> 16 ), static_cast< Byte >( value >> 24 ),
        static_cast< Byte >( value >> 32 ), static_cast< Byte >( value >> 40 ), static_cast< Byte >( value >> 48 ), static_cast< Byte >( value >> 56 ) };
        return result;
    }

    // Converts a float into a vector of bytes with length four.
    inline std::vector<byte> GetBytes( float value )
    {
        std::vector<byte> result( 4 );
        float* ptr = reinterpret_cast<float*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a float into a std::array<Byte,4>.
    constexpr inline std::array<Byte, 4> GetArray( float value )
    {
        return GetArray( std::bit_cast<UInt32>( value ) );
    }


    // Converts a double into a vector of bytes with length eight. 
    inline std::vector<byte> GetBytes( double value )
    {
        std::vector<byte> result( 8 );
        double* ptr = reinterpret_cast<double*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a double into a std::array<Byte,8>.
    constexpr inline std::array<Byte, 8> GetArray( double value )
    {
        return GetArray( std::bit_cast< UInt64 >( value ) );
    }


    // Converts a DateTime into a vector of bytes with length eight. 
    inline std::vector<byte> GetBytes( const DateTime& value )
    {
        return GetBytes( value.Ticks( ) );
    }

    // Converts a DateTime into a std::array<Byte,8>.
    constexpr inline std::array<Byte, 8> GetArray( const DateTime& value )
    {
        return GetArray( value.Ticks( ) );
    }

    // Converts a TimeSpan into a vector of bytes with length eight. 
    inline std::vector<byte> GetBytes( const TimeSpan& value )
    {
        return GetBytes( value.Ticks( ) );
    }

    // Converts a TimeSpan into a std::array<Byte,8>.
    constexpr inline std::array<Byte, 8> GetArray( const TimeSpan& value )
    {
        return GetArray( value.Ticks( ) );
    }

    // Converts a Currency into a vector of bytes with length eight. 
    inline std::vector<byte> GetBytes( const Currency& value )
    {
        return GetBytes( value.Value( ) );
    }

    // Converts a Currency into a std::array<Byte,8>.
    constexpr inline std::array<Byte, 8> GetArray( const Currency& value )
    {
        return GetArray( value.Value( ) );
    }

    // Converts a Guid into a vector of bytes with length 16. 
    inline std::vector<byte> GetBytes( const Guid& value )
    {
        std::vector<byte> result( 16 );
        Guid* ptr = reinterpret_cast< Guid* >( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a Guid into a std::array<Byte,16>.
    constexpr inline std::array<Byte, 16> GetArray( const Guid& value )
    {
        return value.ToArray( );
    }




    namespace Internal
    {
        template<typename T, SimpleByteSpanLike SpanT>
        void RangeCheck( const SpanT& value, size_t startIndex )
        {
            if ( startIndex >= value.size( ) )
            {
                throw ArgumentException( L"startIndex" );
            }

            if ( startIndex + sizeof(T) > value.size( ) )
            {
                throw ArgumentException( L"Remaining buffer is too small" );
            }
        }
    }

    // Converts a SimpleByteSpanLike container into a boolean. 
    template<SimpleSpanLike SpanT>
    inline bool ToBoolean( const SpanT& value, size_t startIndex = 0U )
    {
        Internal::RangeCheck<Byte>( value, startIndex );
        return ( value[ startIndex ] == 0 ) ? false : true;
    }

    // Converts a SimpleByteSpanLike container into a SByte
    template<SimpleByteSpanLike SpanT>
    inline SByte ToSByte( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = SByte;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* pbyte = value.data( ) + startIndex;
        return std::bit_cast< ResultType >( *pbyte );
    }


    // Converts a SimpleByteSpanLike container into a Byte
    template<SimpleByteSpanLike SpanT>
    inline Byte ToByte( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = Byte;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* pbyte = value.data( ) + startIndex;
        return *pbyte;
    }

    // Converts a SimpleByteSpanLike container into a char
    template<SimpleByteSpanLike SpanT>
    inline char ToChar( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = char;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* pbyte = value.data( ) + startIndex;
        return std::bit_cast< ResultType >( *pbyte );
    }



    // Converts a SimpleByteSpanLike container into a wchar_t.
    template<SimpleByteSpanLike SpanT>
    inline wchar_t ToWideChar( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = wchar_t;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast<const wchar_t*>( ptr );
    }


    


    // Converts a SimpleByteSpanLike container into a short. 
    template<SimpleByteSpanLike SpanT>
    inline Int16 ToInt16( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = Int16;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }

    // Converts a SimpleByteSpanLike container into an unsigned short. 
    template<SimpleByteSpanLike SpanT>
    inline UInt16 ToUInt16( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = UInt16;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }

    // Converts a SimpleByteSpanLike container into a 32-bit integer. 
    template<SimpleByteSpanLike SpanT>
    inline Int32 ToInt32( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = Int32;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }

    // Converts a SimpleByteSpanLike container into a 32-bit unsigned integer. 
    template<SimpleByteSpanLike SpanT>
    inline UInt32 ToUInt32( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = UInt32;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }


    // Converts a SimpleByteSpanLike container into a 64-bit integer. 
    template<SimpleByteSpanLike SpanT>
    inline Int64 ToInt64( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = Int64;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }


    // Converts a SimpleByteSpanLike container into a 64-bit unsigned integer. 
    template<SimpleByteSpanLike SpanT>
    inline UInt64 ToUInt64( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = UInt64;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }


    // Converts a SimpleByteSpanLike container into a float.
    template<SimpleByteSpanLike SpanT>
    inline float ToSingle( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = float;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }

    // Converts a SimpleByteSpanLike container into a double.
    template<SimpleByteSpanLike SpanT>
    inline double ToDouble( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = double;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }

    // Converts a SimpleByteSpanLike container into a DateTime.
    template<SimpleByteSpanLike SpanT>
    inline DateTime ToDateTime( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = DateTime;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }

    // Converts a SimpleByteSpanLike container into a TimeSpan.
    template<SimpleByteSpanLike SpanT>
    inline TimeSpan ToTimeSpan( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = TimeSpan;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }

    // Converts a SimpleByteSpanLike container into a Currency object.
    template<SimpleByteSpanLike SpanT>
    inline Currency ToCurrency( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = Currency;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }

    // Converts a SimpleByteSpanLike container into a Guid object.
    template<SimpleByteSpanLike SpanT>
    inline Guid ToGuid( const SpanT& value, size_t startIndex = 0U )
    {
        using ResultType = Guid;
        Internal::RangeCheck<ResultType>( value, startIndex );

        const Byte* ptr = value.data( ) + startIndex;
        return *reinterpret_cast< const ResultType* >( ptr );
    }





    inline WideString::value_type GetHexValue( int i )
    {
        if ( i < 10 )
        {
            return ( WideString::value_type ) ( i + '0' );
        }
        return ( WideString::value_type ) ( i - 10 + 'A' );
    }


    // Converts a SimpleByteSpanLike container into a String.
    template<SimpleByteSpanLike SpanT>
    inline WideString ToString( const SpanT& value, size_t startIndex, size_t length )
    {
        if ( startIndex >= value.size( ) && startIndex > 0 )
        {
            // Don't throw for a 0 length vector.
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - length )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }

        if ( length == 0 )
        {
            return WideString();
        }

        if ( length > ( MaxInt32 / 3 ) )
        {
            // (MaxInt32 / 3) == 715,827,882 Bytes == 699 MB
            throw ArgumentOutOfRangeException( L"length" );
        }

        size_t stringLength = size_t( length ) * 3 - 1;
        WideString result;
        result.resize( stringLength );
        WideString::value_type* buffer = result.data( );
        size_t i = 0;
        size_t index = startIndex;
        for ( i = 0; i < stringLength; i += 3 )
        {
            byte b = value[index++];
            buffer[i] = GetHexValue( b / 16 );
            buffer[i + 1] = GetHexValue( b % 16 );
            buffer[i + 2] = '-';
        }
        buffer[i + 2] = '\x0';
        return result;
    }

    // Converts a SimpleByteSpanLike container into a String. 
    template<SimpleByteSpanLike SpanT>
    inline WideString ToString( const SpanT& value )
    {
        return ToString( value, 0, value.size( ) );
    }

    // Converts a SimpleByteSpanLike container into a String. 
    template<SimpleByteSpanLike SpanT>
    inline WideString ToString( const SpanT& value, size_t startIndex )
    {
        return ToString( value, startIndex, value.size( ) - startIndex );
    }

    

}


#endif
