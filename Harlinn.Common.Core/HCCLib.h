#pragma once
#ifndef __HCCLIB_H__
#define __HCCLIB_H__

#include <HCCDef.h>
#include <HCCTraits.h>
#include <HCCConcepts.h>

#define HCCLIB_IMPLEMENTS_ROUND 1
#define HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP 1
#define HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC 1

namespace Harlinn::Common::Core
{
#pragma pack(push,1)
    struct Bits8
    {
        Byte Value;
    };
    union Bits16
    {
        struct
        {
            Byte Low;
            Byte High;
        };
        UInt16 Value;
    };

    union Bits32
    {
        struct
        {
            Bits16 Low;
            Bits16 High;
        };
        UInt32 Value;
        Int32 Int32Value;
        Single SingleValue;
    };

    union Bits64
    {
        struct
        {
            Bits32 Low;
            Bits32 High;
        };
        UInt64 Value;
        Int64 Int64Value;
        Double DoubleValue;
    };

#pragma pack(pop)


    namespace Internal
    {
        template<typename T, std::size_t... N>
        inline constexpr T ByteSwapImpl( T value, std::index_sequence<N...> )
        {
            return ( ( ( ( value >> ( N * CHAR_BIT ) ) & (T)(unsigned char)( -1 ) )  << ( ( sizeof( T ) - 1 - N ) * CHAR_BIT ) ) | ... );
        };
    }
    template<typename T>
        requires IsInteger<std::remove_cvref_t<T>>
    inline constexpr T ByteSwap( T value )
    {
        if ( std::is_constant_evaluated( ) )
        {
            return std::bit_cast<T>( Internal::ByteSwapImpl(std::bit_cast<std::make_unsigned_t<T>>( value ),  std::make_index_sequence<sizeof( T )>( ) ) );
        }
        else
        {
            if constexpr ( sizeof( std::remove_cvref_t<T> ) == 1 )
            {
                return value;
            }
            else if constexpr ( sizeof( std::remove_cvref_t<T> ) == 2 )
            {
                return std::bit_cast<std::remove_cvref_t<T>>( 
                    _byteswap_ushort( std::bit_cast<UInt16>( value ) ) );
            }
            else if constexpr ( sizeof( std::remove_cvref_t<T> ) == 4 )
            {
                return std::bit_cast<std::remove_cvref_t<T>>( 
                    _byteswap_ulong( std::bit_cast<UInt32>( value ) ) );
            }
            else
            {
                return std::bit_cast<std::remove_cvref_t<T>>(
                    _byteswap_uint64( std::bit_cast<UInt64>( value ) ));
            }
        }
    }

    
    template<size_t N>
    struct BitMask
    {
        static_assert( N <= 64 && N > 0, "Unsupported bit-mask width" );
        using type = std::conditional_t
            <
            N <= 8, Byte,
            std::conditional_t
                <
                N <= 16, UInt16,
                std::conditional_t
                    <
                    N <= 32, UInt32,
                    UInt64
                    >    
                >
            >;
        static constexpr type value = (( static_cast<type>( 1 ) << ( N - 1 ) ) - 1) ^ ( static_cast<type>( 1 ) << ( N - 1 ) );
    };

    template<size_t N>
    inline constexpr auto BitMask_v = BitMask<N>::value;
    template<size_t N>
    using BitMask_t = typename BitMask<N>::type;

    /// <summary>
    /// Reverses the order of the bits of a byte.
    /// </summary>
    inline constexpr Byte ReverseBits( Byte b ) noexcept
    {
        /*
         * From: https://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64BitsDiv
         */
        b = static_cast<Byte>( ( static_cast<UInt64>(b) * 0x0202020202ULL & 0x010884422010ULL ) % 1023 );
        return b;
    }

    inline constexpr SByte ReverseBits( SByte b ) noexcept
    {
        return std::bit_cast<SByte>( ReverseBits( std::bit_cast<Byte>(b) ) );
    }
    inline constexpr char ReverseBits( char b ) noexcept
    {
        return std::bit_cast<char>( ReverseBits( std::bit_cast<Byte>( b ) ) );
    }

    inline constexpr UInt16 ReverseBits( UInt16 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt16 hi = static_cast<UInt16>( ReverseBits( static_cast<Byte>( val & 0x00FF ) ) )<< 8;
            UInt16 lo = static_cast<UInt16>( ReverseBits( static_cast<Byte>( val >> 8 ) ) );
            UInt16 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast<Byte*>( &val );
            UInt16 result;
            Byte* resultPtr = reinterpret_cast<Byte*>( &result );

            resultPtr[0] = ReverseBits( srcPtr[1] );
            resultPtr[1] = ReverseBits( srcPtr[0] );
            return result;
        }
    }
    inline constexpr Int16 ReverseBits( Int16 val ) noexcept
    {
        return std::bit_cast<Int16>( ReverseBits( std::bit_cast<UInt16>( val ) ) );
    }
    inline constexpr wchar_t ReverseBits( wchar_t val ) noexcept
    {
        return std::bit_cast<wchar_t>( ReverseBits( std::bit_cast<UInt16>( val ) ) );
    }


    inline constexpr UInt32 ReverseBits( UInt32 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt32 hi = static_cast<UInt32>( ReverseBits( static_cast<UInt16>( val & 0xFFFF ) ) ) << 16;
            UInt32 lo = static_cast<UInt32>( ReverseBits( static_cast<UInt16>( val >> 16 ) ) );
            UInt32 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast<Byte*>( &val );
            UInt32 result;
            Byte* resultPtr = reinterpret_cast<Byte*>( &result );

            resultPtr[0] = ReverseBits( srcPtr[3] );
            resultPtr[1] = ReverseBits( srcPtr[2] );
            resultPtr[2] = ReverseBits( srcPtr[1] );
            resultPtr[3] = ReverseBits( srcPtr[0] );
            return result;
        }
    }
    inline constexpr Int32 ReverseBits( Int32 val ) noexcept
    {
        return std::bit_cast<Int32>( ReverseBits( std::bit_cast<UInt32>( val ) ) );
    }
    inline constexpr long ReverseBits( long val ) noexcept
    {
        return std::bit_cast<long>( ReverseBits( std::bit_cast<UInt32>( val ) ) );
    }
    inline constexpr unsigned long ReverseBits( unsigned long val ) noexcept
    {
        return std::bit_cast<unsigned long>( ReverseBits( std::bit_cast<UInt32>( val ) ) );
    }


    inline constexpr UInt64 ReverseBits( UInt64 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt64 hi = static_cast<UInt64>( ReverseBits( static_cast<UInt32>( val & 0xFFFFFFFF ) ) ) << 32;
            UInt64 lo = static_cast<UInt64>( ReverseBits( static_cast<UInt32>( val >> 32 ) ) );
            UInt64 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast<Byte*>( &val );
            UInt64 result;
            Byte* resultPtr = reinterpret_cast<Byte*>( &result );

            resultPtr[0] = ReverseBits( srcPtr[7] );
            resultPtr[1] = ReverseBits( srcPtr[6] );
            resultPtr[2] = ReverseBits( srcPtr[5] );
            resultPtr[3] = ReverseBits( srcPtr[4] );
            resultPtr[4] = ReverseBits( srcPtr[3] );
            resultPtr[5] = ReverseBits( srcPtr[2] );
            resultPtr[6] = ReverseBits( srcPtr[1] );
            resultPtr[7] = ReverseBits( srcPtr[0] );
            return result;
        }
    }
    inline constexpr Int64 ReverseBits( Int64 val ) noexcept
    {
        return std::bit_cast<Int64>( ReverseBits( std::bit_cast<UInt64>( val ) ) );
    }
    inline constexpr Single ReverseBits( Single val ) noexcept
    {
        return std::bit_cast<Single>( ReverseBits( std::bit_cast<UInt32>( val ) ) );
    }
    inline constexpr Double ReverseBits( Double val ) noexcept
    {
        return std::bit_cast<Double>( ReverseBits( std::bit_cast<UInt64>( val ) ) );
    }

    

    /// <summary>
    /// Creates a bit-mask
    /// </summary>
    /// <param name="bitIndex">
    /// The number of bits to set.
    /// The value of numberOfBitsToSet must be in the range [1,64]
    /// </param>
    /// <returns>The generated bit-mask</returns>
    inline constexpr UInt64 CreateBitMask64( unsigned numberOfBitsToSet ) noexcept
    {
        assert( numberOfBitsToSet <= 64 && numberOfBitsToSet > 0 && "The value of numberOfBitsToSet must be in the range [1,64]" );
        UInt64 mostSignificantBit = 1ULL << (numberOfBitsToSet - 1);
        if ( std::is_constant_evaluated( ) )
        {
            return ( mostSignificantBit - 1 ) ^ mostSignificantBit;
        }
        else
        {
            return _blsmsk_u64( mostSignificantBit );
        }
    }
    
    /// <summary>
    /// Creates a bit-mask with all the bits -
    /// up to, and including, the bit at bitIndex
    /// - set.
    /// </summary>
    /// <param name="bitIndex">
    /// The number of bits to set.
    /// The value of numberOfBitsToSet must be in the range [1,32]
    /// </param>
    /// <returns>The generated bit-mask</returns>
    inline constexpr UInt32 CreateBitMask32( unsigned numberOfBitsToSet ) noexcept
    {
        assert( numberOfBitsToSet <= 32 && numberOfBitsToSet > 0 && "The value of numberOfBitsToSet must be in the range [1,32]" );
        UInt32 mostSignificantBit = 1ULL << ( numberOfBitsToSet - 1 );
        if ( std::is_constant_evaluated( ) )
        {
            return ( mostSignificantBit - 1 ) ^ mostSignificantBit;
        }
        else
        {
            return _blsmsk_u32( mostSignificantBit );
        }
    }

    /// <summary>
    /// Extracts contiguous bits from value
    /// </summary>
    /// <param name="value"></param>
    /// <param name="start">
    /// 0 based index of the least significant bit to extract.
    /// </param>
    /// <param name="len">
    /// Number of bits to extract,
    /// </param>
    /// <returns>
    /// the extracted bits, with the first extracted bit at
    /// position 0, the least significant bit in the
    /// returned value.
    /// </returns>
    inline constexpr UInt64 ExtractBits64( UInt64 value, UInt32 start, UInt32 len ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt64 mask = CreateBitMask64( len );
            return ( value >> start ) & mask;
        }
        else
        {
            return _bextr_u64( value, start, len );
        }
    }
    /// <summary>
    /// Extracts contiguous bits from value
    /// </summary>
    /// <param name="value"></param>
    /// <param name="start">
    /// 0 based index of the least significant bit to extract.
    /// </param>
    /// <param name="len">
    /// Number of bits to extract,
    /// </param>
    /// <returns>
    /// the extracted bits, with the first extracted bit at
    /// position 0, the least significant bit in the
    /// returned value.
    /// </returns>
    inline constexpr UInt32 ExtractBits32( UInt32 value, UInt32 start, UInt32 len ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt32 mask = CreateBitMask32( len );
            return ( value >> start ) & mask;
        }
        else
        {
            return _bextr_u32(value, start, len );
        }
    }

    
    template<size_t N>
    inline const void* AlignTo( const void* address )
    {
        return reinterpret_cast<const void*>(( reinterpret_cast<size_t>(address) + N ) & ~static_cast<size_t>( N ));
    }
    template<size_t N>
    inline void* AlignTo( void* address )
    {
        return reinterpret_cast<void*>( ( reinterpret_cast<size_t>( address ) + N ) & ~static_cast<size_t>( N ) );
    }
    template<size_t N>
    inline size_t AlignedPaddingFor( const void* address )
    {
        return (( reinterpret_cast<size_t>( address ) + N ) & ~static_cast<size_t>( N )) - reinterpret_cast<size_t>( address );
    }



    template<typename T>
    inline constexpr bool IsGUID = std::is_same_v<std::remove_cv_t<T>, GUID>;

    template<typename T>
        requires IsGUID<T>
    inline constexpr T ByteSwap( const T& guid ) noexcept
    {
        return GUID{ ByteSwap( guid.Data1 ), ByteSwap( guid.Data2 ), ByteSwap( guid.Data3 ), { guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] } };
    }


    template<typename T>
        requires (IsFloatingPoint<std::remove_cvref_t<T>> || std::is_enum_v<std::remove_cvref_t<T>> )
    inline constexpr T ByteSwap( const T value ) noexcept
    {
        using Type = std::remove_cvref_t<T>;
        using UIntType = MakeUnsigned<Type>;
        std::bit_cast<Type>( ByteSwap( std::bit_cast<UIntType>( value ) ) );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
        {
            { std::bit_cast<UInt64>( t2 ) }->std::convertible_to<UInt64>;
        }
    inline constexpr T1 GetHigh32Bits( T2 val ) noexcept
    {
        auto value = std::bit_cast<UInt64>( val );
        return static_cast<T1>( value >> 32 );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
        {
            { std::bit_cast<UInt64>( t2 ) }->std::convertible_to<UInt64>;
        }
    inline constexpr T2 SetHigh32Bits( T2 x, T1 value ) noexcept
    {
        return std::bit_cast<T2>( (std::bit_cast<UInt64>( x ) & 0x00000000FFFFFFFFULL) + (static_cast<UInt64>(std::bit_cast<UInt32>( value )) << 32) );
    }

    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
        {
            { std::bit_cast<UInt64>( t2 ) }->std::convertible_to<UInt64>;
        }
    inline constexpr T1 GetLow32Bits( T2 val ) noexcept
    {
        auto value = std::bit_cast<UInt64>( val );
        return static_cast<T1>( value );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
        {
            { std::bit_cast<UInt64>( t2 ) }->std::convertible_to<UInt64>;
        }
    inline constexpr T2 SetLow32Bits( T2 x, T1 value ) noexcept
    {
        return std::bit_cast<T2>( ( std::bit_cast<UInt64>( x ) & 0xFFFFFFFF00000000ULL ) + static_cast<UInt64>( std::bit_cast<UInt32>( value ) ) );
    }

    template<typename T1, typename T2, typename T3>
        requires ( sizeof( T1 ) == 8 ) && ( std::is_same_v<Int32, T2> || std::is_same_v<UInt32, T2> ) && ( std::is_same_v<Int32, T3> || std::is_same_v<UInt32, T3> ) && requires( UInt64 v1 )
        {
            { std::bit_cast<T1>( v1 ) }->std::same_as<T1>;
        }
    inline constexpr T1 From32BitsTo64Bits( T2 high32Bits, T3 low32Bits ) noexcept
    {
        return std::bit_cast<T1>(  (static_cast<UInt64>( high32Bits ) << 32) + static_cast<UInt64>( low32Bits ) );
    }





    template<typename T, size_t N>
        requires ( std::is_same_v<char,std::remove_cv_t<T>> == false && std::is_same_v<wchar_t, std::remove_cv_t<T>> == false )
    inline constexpr size_t LengthOf( T ( &array )[N] ) noexcept
    {
        return N;
    }

    template<typename T>
        requires requires( T container )
        {
            { container.size( ) } -> std::convertible_to<size_t>;
        }
    inline constexpr size_t LengthOf( const T& container ) noexcept
    {
        return container.size( );
    }

    namespace Internal
    {
        inline constexpr size_t LengthOf( const char* s ) noexcept
        {
            if ( std::is_constant_evaluated( ) )
            {
                return s && s[0] ? std::string_view( s ).size( ) : 0;
            }
            else
            {
                return s && s[0] ? strlen( s ) : 0;
            }
        }
        inline constexpr size_t LengthOf( const wchar_t* s ) noexcept
        {
            if ( std::is_constant_evaluated( ) )
            {
                return s && s[0] ? std::wstring_view( s ).size( ) : 0;
            }
            else
            {
                return s && s[0] ? wcslen( s ) : 0;
            }
        }
    }

    template<typename T>
        requires ( std::is_pointer_v<T> && ( std::is_same_v<char, std::remove_const_t< std::remove_pointer_t<T> > > || std::is_same_v<wchar_t, std::remove_const_t< std::remove_pointer_t<T> > > ) )
    inline constexpr size_t LengthOf( T str ) noexcept
    {
        return Core::Internal::LengthOf( str );
    }


    inline void Copy( char* dest, const char* source, size_t length ) noexcept
    {
        memcpy( dest, source, length );
    }
    inline void Copy( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
    {
        wmemcpy( dest, source, length );
    }

    inline constexpr int Compare( nullptr_t s1, nullptr_t s2 ) noexcept
    {
        return 0;
    }

    inline constexpr int Compare( nullptr_t s1, const char* s2 ) noexcept
    {
        return s2 && s2[0]?-1:0;
    }

    inline constexpr int Compare( const char* s1, nullptr_t s2 ) noexcept
    {
        return s1 && s1[0]?1:0;
    }

    inline constexpr int Compare( const char* s1, const char* s2 ) noexcept
    {   
        if ( std::is_constant_evaluated() )
        {
            if ( s1 && s1[0] )
            {
                if ( s2 && s2[0] )
                {
                    return std::string_view( s1 ).compare( s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[0] )
            {
                return -1;
            }
            return 0;
        }
        else
        {
            if ( s1 && s1[0] )
            {
                if ( s2 && s2[0] )
                {
                    return strcmp( s1, s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[0] )
            {
                return -1;
            }
            return 0;
        }
    }

    inline constexpr int Compare( nullptr_t s1, const wchar_t* s2 ) noexcept
    {
        return s2 && s2[0] ? -1 : 0;
    }

    inline constexpr int Compare( const wchar_t* s1, nullptr_t s2 ) noexcept
    {
        return s1 && s1[0] ? 1 : 0;
    }

    inline constexpr int Compare( const wchar_t* s1, const wchar_t* s2 ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            if ( s1 && s1[0] )
            {
                if ( s2 && s2[0] )
                {
                    return std::wstring_view( s1 ).compare( s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[0] )
            {
                return -1;
            }
            return 0;
        }
        else
        {
            if ( s1 && s1[0] )
            {
                if ( s2 && s2[0] )
                {
                    return wcscmp( s1, s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[0] )
            {
                return -1;
            }
            return 0;
        }
    }

    template<typename T>
        requires std::is_integral_v<T> || std::is_floating_point_v<T> 
    constexpr inline int Compare( T v1, T v2 ) noexcept
    {
        return v1 > v2 ? 1 : v1 < v2 ? -1 : 0;
    }


    template<typename T>
        requires std::is_same_v<DateTime, std::remove_cvref_t<T>> || 
            std::is_same_v<TimeSpan, std::remove_cvref_t<T>> || 
            std::is_same_v<Currency, std::remove_cvref_t<T>>
    constexpr inline int Compare( T v1, T v2 ) noexcept
    {
        return v1.CompareTo( v2 );
    }


    template<typename T1, typename T2>
        requires ((std::is_same_v<Guid, std::remove_cvref_t<T1>> || std::is_same_v<GUID, std::remove_cvref_t<T1>> ) &&
                ( std::is_same_v<Guid, std::remove_cvref_t<T2>> || std::is_same_v<GUID, std::remove_cvref_t<T2>> ) )
    constexpr inline int Compare( const T1& v1, const T2& v2 ) noexcept
    {
        return reinterpret_cast<const Guid&>(v1).CompareTo( reinterpret_cast< const Guid& >( v2 ) );
    }


    template<typename T1, typename T2 >
        requires requires( const T1& t1, const T2& t2 )
        {
            { t1.compare( t2 ) } ->std::convertible_to<int>;
        }
    inline int Compare( const T1& v1, const T2& v2 ) noexcept
    {
        return v1.compare( v2 );
    }

    template<typename FirstT, typename SecondT >
        requires requires( FirstT f, SecondT s )
        { 
            { Compare( f, s ) } ->std::convertible_to<int>;
        }
    inline int Compare( const FirstT* first, size_t firstLength, const SecondT* second, size_t secondLength )
    {
        auto compareSize = std::min( firstLength, secondLength );
        for ( size_t i = 0; i < compareSize; i++ )
        {
            auto result = Compare(first[i], second[i] );
            if ( result )
            {
                return result;
            }
        }
        if ( firstLength == secondLength )
        {
            return 0;
        }
        else if ( firstLength < secondLength )
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    template<typename FirstT, typename SecondT, typename ConversionFunc >
        requires requires( FirstT f, SecondT s, ConversionFunc func )
        {
            { Compare( f, s ) } ->std::convertible_to<int>;
            { func(s) } ->std::convertible_to<FirstT>;
        }
    inline int Compare( const FirstT* first, size_t firstLength, const SecondT* second, size_t secondLength, ConversionFunc converter )
    {
        auto compareSize = std::min( firstLength, secondLength );
        for ( size_t i = 0; i < compareSize; i++ )
        {
            auto result = Compare( first[ i ], converter( second[ i ] ) );
            if ( result )
            {
                return result;
            }
        }
        if ( firstLength == secondLength )
        {
            return 0;
        }
        else if ( firstLength < secondLength )
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    template<typename FirstT, typename SecondT, typename CompareFunc >
        requires requires( FirstT f, SecondT s, CompareFunc func )
    {
        { func( f, s ) } ->std::convertible_to<int>;
    }
    inline int CompareEx( const FirstT* first, size_t firstLength, const SecondT* second, size_t secondLength, CompareFunc compare )
    {
        auto compareSize = std::min( firstLength, secondLength );
        for ( size_t i = 0; i < compareSize; i++ )
        {
            auto result = compare( first[ i ], second[ i ] );
            if ( result )
            {
                return result;
            }
        }
        if ( firstLength == secondLength )
        {
            return 0;
        }
        else if ( firstLength < secondLength )
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }





    template<SimpleSpanLike T1, SimpleSpanLike T2, typename ConversionFunc >
    inline int Compare( const T1& first, const T2& second, ConversionFunc converter )
    {
        return Compare( first.data( ), first.size( ), second.data( ), second.size( ), converter );
    }

    template<SimpleSpanLike T1, SimpleSpanLike T2 >
    inline int Compare( const T1& first, const T2& second )
    {
        return Compare( first.data( ), first.size( ), second.data( ), second.size( ) );
    }



    template<typename T>
        requires std::is_floating_point_v<T>
    constexpr bool AreNearlyEqual( T a, T b, T smallNumber = static_cast<T>( 0.0001 ) ) noexcept
    {
        if ( a <= b )
        {
            return ( b - a ) <= smallNumber;
        }
        else
        {
            return ( a - b ) <= smallNumber;
        }
    }




    class XXH64Hasher
    {
    public:
        using HashType = XXH64_hash_t;
        using StateType = XXH64_state_t;
        using CanonicalType = XXH64_canonical_t;
        using ErrorCode = XXH_errorcode;
    private:
        StateType* state_;
    public:
        XXH64Hasher( HashType seed = 0)
            : state_( XXH64_createState( ) )
        {
            Reset( seed );
        }

        XXH64Hasher( const XXH64Hasher& other ) = delete;
        XXH64Hasher( XXH64Hasher&& other ) = delete;

        ~XXH64Hasher( )
        {
            if ( state_ )
            {
                XXH64_freeState( state_ );
            }
        }

        XXH64Hasher& operator =( const XXH64Hasher& other ) = delete;
        XXH64Hasher& operator =( XXH64Hasher&& other ) = delete;

        ErrorCode Reset( HashType seed = 0 )
        {
            return XXH64_reset( state_, seed );
        }

        HashType Digest( )
        {
            return XXH64_digest( state_ );
        }

        void Update( const void* input, size_t length )
        {
            XXH64_update( state_, input, length );
        }

        template<typename T>
            requires std::is_same_v<T,bool>
                void Add( T value )
        {
                
            Byte v = value ? 1 : 0;
            Update( &v, 1 );
        }
        template<typename T>
            requires (std::is_integral_v<T> && ( std::is_same_v<T, bool> == false ) ) || std::is_floating_point_v<T>
        void Add( T value )
        {
            Update( &value, sizeof(T) );
        }
        template<typename T>
            requires std::is_same_v<DateTime, std::remove_cvref_t<T>> ||
                std::is_same_v<TimeSpan, std::remove_cvref_t<T>> ||
                std::is_same_v<Currency, std::remove_cvref_t<T>> ||
                std::is_same_v<Guid, std::remove_cvref_t<T>>
        void Add( T value )
        {
            Update( &value, sizeof( std::remove_cvref_t<T> ) );
        }

        template<typename T>
            requires std::is_same_v<char,T> || std::is_same_v<wchar_t, T>
        void Add( const T* value, size_t size )
        {
            if ( size )
            {
                Update( value, size * sizeof( T ) );
            }
        }

        void Add( const Byte* value, size_t size )
        {
            if ( size )
            {
                Update( value, size );
            }
        }

        template<typename T>
            requires std::is_same_v<char,T> || std::is_same_v<wchar_t, T>
        void Add( const T* value )
        {
            if ( value )
            {
                auto size = LengthOf( value );
                Update( value, size * sizeof( T ) );
            }
        }

        template<typename T>
            requires IsSpecializationOf<T, std::basic_string> || IsSpecializationOf<T, std::basic_string_view>
        void Add( const T& str )
        { 
            Add( str.data(), str.size() );
        }
    };


    // Bit manipulation
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsPowerOfTwo( T v ) noexcept
    {
        return v != 0 && ( v & ( v - 1 ) ) == 0;
    }

    template<typename T>
        requires std::is_enum_v<std::remove_cvref_t<T>>
    constexpr inline bool IsPowerOfTwo( T v ) noexcept
    {
        auto val = std::bit_cast<std::underlying_type_t<std::remove_cvref_t<T>>>( v );
        return val != 0 && ( val & ( val - 1 ) ) == 0;
    }

    
    constexpr inline Byte NextPowerOfTwo( Byte v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v++;
        return v;
    }
    constexpr inline SByte NextPowerOfTwo( SByte v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v++;
        return v;
    }


    constexpr inline Int16 NextPowerOfTwo( Int16 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v++;
        return v;
    }
    constexpr inline UInt16 NextPowerOfTwo( UInt16 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v++;
        return v;
    }
    

    constexpr inline Int32 NextPowerOfTwo( Int32 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }
    constexpr inline UInt32 NextPowerOfTwo( UInt32 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }

    constexpr inline Int64 NextPowerOfTwo( Int64 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v |= v >> 32;
        v++;
        return v;
    }
    constexpr inline UInt64 NextPowerOfTwo( UInt64 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v |= v >> 32;
        v++;
        return v;
    }

    template<typename CharType>
    bool HexToBinary( CharType c, Byte& result )
    {
        if ( c >= static_cast<CharType>( '0' ) && c <= static_cast<CharType>( '9' ) )
        {
            result = static_cast<Byte>( c ) - static_cast<Byte>( '0' );
            return true;
        }
        else if ( c >= static_cast<CharType>( 'a' ) && c <= static_cast<CharType>( 'f' ) )
        {
            result = (static_cast<Byte>( c ) - static_cast<Byte>( 'a' )) + 10;
            return true;
        }
        else if ( c >= static_cast<CharType>( 'A' ) && c <= static_cast<CharType>( 'F' ) )
        {
            result = ( static_cast<Byte>( c ) - static_cast<Byte>( 'A' ) ) + 10;
            return true;
        }
        else
        {
            return false;
        }

    }
    
    template<typename CharType>
    inline bool HexToBinary( const CharType* text, size_t textLength, std::vector<Byte>& result )
    {
        if ( ( textLength % 2 ) == 0 )
        {
            const CharType* textEnd = text + textLength;
            size_t binaryLength = textLength / 2;
            result.clear( );
            result.resize( binaryLength );
            size_t i = 0;
            while ( text < textEnd )
            {
                Byte msn;
                if ( HexToBinary( *text, msn ) )
                {
                    text++;
                    Byte lsn;
                    if ( HexToBinary( *text, lsn ) )
                    {
                        text++;
                        result[i] = ( msn << 4 ) | lsn;
                        i++;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }





    

}

#endif

