#pragma once
#ifndef __HCCBITCONVERTER_H__
#define __HCCBITCONVERTER_H__

#include <HCCException.h>
#include <HCCString.h>


// The BitConverter namespace contains methods for 
// converting a vector of bytes to one of the base data
// types, as well as for converting a base data type to a 
// vector of bytes. 
//
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

    // Converts a byte into a vector of bytes with length one.
    static std::vector<byte> GetBytes( bool value )
    {
        std::vector<byte> result( 1, value ? 1 : 0 );
        return result;
    }

    // Converts a char into a vector of bytes with length one. 
    static std::vector<byte> GetBytes( char value )
    {
        std::vector<byte> result( 1, value );
        return result;
    }

    // Converts a wchar_t into a vector of bytes with length two. 
    static std::vector<byte> GetBytes( wchar_t value )
    {
        std::vector<byte> result( 2 );
        wchar_t* ptr = reinterpret_cast<wchar_t*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a short into a vector of bytes with length two.
    static std::vector<byte> GetBytes( short value )
    {
        std::vector<byte> result( 2 );
        short* ptr = reinterpret_cast<short*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts an int into a vector of bytes with length four.
    static std::vector<byte> GetBytes( int value )
    {
        std::vector<byte> result( 4 );
        int* ptr = reinterpret_cast<int*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a long into a vector of bytes with length eight. 
    static std::vector<byte> GetBytes( long long value )
    {
        std::vector<byte> result( 8 );
        long long* ptr = reinterpret_cast<long long*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts an ushort into a vector of bytes with length two.
    static std::vector<byte> GetBytes( unsigned short value )
    {
        std::vector<byte> result( 2 );
        unsigned short* ptr = reinterpret_cast<unsigned short*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts an uint into a vector of bytes with length four.
    static std::vector<byte> GetBytes( unsigned int value )
    {
        std::vector<byte> result( 4 );
        unsigned int* ptr = reinterpret_cast<unsigned int*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts an unsigned long into a vector of bytes with length eight. 
    static std::vector<byte> GetBytes( unsigned long long value )
    {
        std::vector<byte> result( 8 );
        unsigned long long* ptr = reinterpret_cast<unsigned long long*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a float into a vector of bytes with length four.
    static std::vector<byte> GetBytes( float value )
    {
        std::vector<byte> result( 4 );
        float* ptr = reinterpret_cast<float*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a double into a vector of bytes with length eight. 
    static std::vector<byte> GetBytes( double value )
    {
        std::vector<byte> result( 8 );
        double* ptr = reinterpret_cast<double*>( result.data( ) );
        *ptr = value;
        return result;
    }

    // Converts a vector of bytes into a wchar_t.
    static wchar_t ToWideChar( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 2 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 2 == 0 )
        {
            // data is aligned
            return *( (wchar_t*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            return (wchar_t)( ( *pbyte << 8 ) | ( *( pbyte + 1 ) ) );
#else
            return (wchar_t)( ( *pbyte ) | ( *( pbyte + 1 ) << 8 ) );
#endif
        }

    }

    // Converts a vector of bytes into a short. 
    static short ToInt16( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 2 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 2 == 0 )
        {
            // data is aligned
            return *( (short*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            return (short)( ( *pbyte << 8 ) | ( *( pbyte + 1 ) ) );
#else
            return (short)( ( *pbyte ) | ( *( pbyte + 1 ) << 8 ) );
#endif
        }

    }

    // Converts a vector of bytes into an unsigned short. 
    static unsigned short ToUInt16( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 2 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 2 == 0 )
        {
            // data is aligned
            return *( (unsigned short*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            return (unsigned short)( ( *pbyte << 8 ) | ( *( pbyte + 1 ) ) );
#else
            return (unsigned short)( ( *pbyte ) | ( *( pbyte + 1 ) << 8 ) );
#endif
        }

    }

    // Converts a vector of bytes into a 32-bit integer. 
    static int ToInt32( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 4 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 4 == 0 )
        {
            // data is aligned
            return *( (int*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            return (int)( *pbyte << 24 ) | ( *( pbyte + 1 ) << 16 ) | ( *( pbyte + 2 ) << 8 ) | ( *( pbyte + 3 ) );
#else
            return (int)( *pbyte ) | ( *( pbyte + 1 ) << 8 ) | ( *( pbyte + 2 ) << 16 ) | ( *( pbyte + 3 ) << 24 );
#endif
        }

    }

    // Converts a vector of bytes into a 32-bit unsigned integer. 
    static unsigned int ToUInt32( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 4 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 4 == 0 )
        {
            // data is aligned
            return *( (unsigned int*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            return (unsigned int)( *pbyte << 24 ) | ( *( pbyte + 1 ) << 16 ) | ( *( pbyte + 2 ) << 8 ) | ( *( pbyte + 3 ) );
#else
            return (unsigned int)( *pbyte ) | ( *( pbyte + 1 ) << 8 ) | ( *( pbyte + 2 ) << 16 ) | ( *( pbyte + 3 ) << 24 );
#endif
        }

    }


    // Converts a vector of bytes into a 64-bit integer. 
    static long long ToInt64( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 8 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 8 == 0 )
        {
            // data is aligned
            return *( (long long*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            int i1 = ( *pbyte << 24 ) | ( *( pbyte + 1 ) << 16 ) | ( *( pbyte + 2 ) << 8 ) | ( *( pbyte + 3 ) );
            uint i2 = ( *( pbyte + 4 ) << 24 ) | ( *( pbyte + 5 ) << 16 ) | ( *( pbyte + 6 ) << 8 ) | ( *( pbyte + 7 ) );
            return ( (long long)i1 << 32 ) | i2;
#else
            uint i1 = ( *pbyte ) | ( *( pbyte + 1 ) << 8 ) | ( *( pbyte + 2 ) << 16 ) | ( *( pbyte + 3 ) << 24 );
            int i2 = ( *( pbyte + 4 ) ) | ( *( pbyte + 5 ) << 8 ) | ( *( pbyte + 6 ) << 16 ) | ( *( pbyte + 7 ) << 24 );
            return ( (long long)i2 << 32 ) | i1;
#endif
        }

    }


    // Converts a vector of bytes into a 64-bit unsigned integer. 
    static unsigned long long ToUInt64( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 8 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 8 == 0 )
        {
            // data is aligned
            return *( (long long*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            uint i1 = ( *pbyte << 24 ) | ( *( pbyte + 1 ) << 16 ) | ( *( pbyte + 2 ) << 8 ) | ( *( pbyte + 3 ) );
            uint i2 = ( *( pbyte + 4 ) << 24 ) | ( *( pbyte + 5 ) << 16 ) | ( *( pbyte + 6 ) << 8 ) | ( *( pbyte + 7 ) );
            return ( ( unsigned long long ) i1 << 32 ) | i2;
#else
            uint i1 = ( *pbyte ) | ( *( pbyte + 1 ) << 8 ) | ( *( pbyte + 2 ) << 16 ) | ( *( pbyte + 3 ) << 24 );
            uint i2 = ( *( pbyte + 4 ) ) | ( *( pbyte + 5 ) << 8 ) | ( *( pbyte + 6 ) << 16 ) | ( *( pbyte + 7 ) << 24 );
            return ( ( unsigned long long ) i2 << 32 ) | i1;
#endif
        }

    }


    // Converts a vector of bytes into a float.
    static float ToSingle( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 4 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 4 == 0 )
        {
            // data is aligned
            return *( (float*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            auto i = (int)( *pbyte << 24 ) | ( *( pbyte + 1 ) << 16 ) | ( *( pbyte + 2 ) << 8 ) | ( *( pbyte + 3 ) );
#else
            auto i = (int)( *pbyte ) | ( *( pbyte + 1 ) << 8 ) | ( *( pbyte + 2 ) << 16 ) | ( *( pbyte + 3 ) << 24 );
#endif
            return *(float*)&i;
        }

    }

    // Converts a vector of bytes into a double.
    static double ToDouble( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }

        if ( startIndex > value.size( ) - 8 )
        {
            throw ArgumentException( L"Remaining buffer is to small" );
        }


        const byte* pbyte = value.data( ) + startIndex;
        if ( size_t( pbyte ) % 8 == 0 )
        {
            // data is aligned
            return *( (double*)pbyte );
        }
        else
        {
#if BIGENDIAN 
            int i1 = ( *pbyte << 24 ) | ( *( pbyte + 1 ) << 16 ) | ( *( pbyte + 2 ) << 8 ) | ( *( pbyte + 3 ) );
            uint i2 = ( *( pbyte + 4 ) << 24 ) | ( *( pbyte + 5 ) << 16 ) | ( *( pbyte + 6 ) << 8 ) | ( *( pbyte + 7 ) );
            auto i = ( (long long)i1 << 32 ) | i2;
#else
            uint i1 = ( *pbyte ) | ( *( pbyte + 1 ) << 8 ) | ( *( pbyte + 2 ) << 16 ) | ( *( pbyte + 3 ) << 24 );
            int i2 = ( *( pbyte + 4 ) ) | ( *( pbyte + 5 ) << 8 ) | ( *( pbyte + 6 ) << 16 ) | ( *( pbyte + 7 ) << 24 );
            auto i = ( (long long)i2 << 32 ) | i1;
#endif
            return *(double*)&i;
        }

    }


    static WideString::value_type GetHexValue( int i )
    {
        if ( i < 10 )
        {
            return ( WideString::value_type ) ( i + '0' );
        }
        return ( WideString::value_type ) ( i - 10 + 'A' );
    }


    // Converts a vector of bytes into a String.
    static WideString ToString( const std::vector<byte>& value, size_t startIndex, size_t length )
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
            return {};
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

    // Converts a vector of bytes into a String. 
    static WideString ToString( const std::vector<byte>& value )
    {
        return ToString( value, 0, value.size( ) );
    }

    // Converts a vector of bytes into a String. 
    static WideString ToString( const std::vector<byte>& value, size_t startIndex )
    {
        return ToString( value, startIndex, value.size( ) - startIndex );
    }

    // Converts a vector of bytes into a boolean. 
    static bool ToBoolean( const std::vector<byte>& value, size_t startIndex )
    {
        if ( startIndex >= value.size( ) )
        {
            throw ArgumentOutOfRangeException( L"startIndex" );
        }
        return ( value[startIndex] == 0 ) ? false : true;
    }

}


#endif
