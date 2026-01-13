#pragma once
#ifndef HARLINN_COMMON_CORE_HCCBITVECTOR_H_
#define HARLINN_COMMON_CORE_HCCBITVECTOR_H_
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

#include <HCCLib.h>

namespace Harlinn::Common::Core
{

    /// <summary>
    /// Extracts the value of a bit at a bit index from an integer value.
    /// </summary>
    /// <typeparam name="BitsT">
    /// A signed or unsigned integer type.
    /// </typeparam>
    /// <param name="bits">
    /// The integer value
    /// </param>
    /// <param name="startIndex">
    /// 0 based index of the bit to extract, where 0 is the index of the least significant bit.
    /// </param>
    /// <returns>true if the bit was set, otherwise false.</returns>
    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr bool BitsToBool( const BitsT bits, const UInt32 startIndex )
    {
        using UnsignedType = std::make_unsigned_t<BitsT>;
        if constexpr ( sizeof( BitsT ) <= 4 )
        {
            return static_cast< bool >( ExtractBits32( static_cast< UInt32 >( std::bit_cast< UnsignedType >( bits ) ), startIndex, 1 ) );
        }
        else
        {
            return static_cast< bool >( ExtractBits64( static_cast< UInt64 >( std::bit_cast< UnsignedType >( bits ) ), startIndex, 1 ) );
        }

    }

    template<typename ResultT, typename BitsT>
        requires ( std::is_integral_v<BitsT> && std::is_enum_v<ResultT> )
    inline constexpr ResultT BitsToEnum( const BitsT bits, const UInt32 startIndex, const UInt32 bitCount )
    {
        using UnsignedType = std::make_unsigned_t<BitsT>;
        if constexpr ( sizeof( BitsT ) <= 4 )
        {
            return static_cast< ResultT >( ExtractBits32( static_cast< UInt32 >( std::bit_cast< UnsignedType >( bits ) ), startIndex, bitCount ) );
        }
        else
        {
            return static_cast< ResultT >( ExtractBits64( static_cast< UInt64 >( std::bit_cast< UnsignedType >( bits ) ), startIndex, bitCount ) );
        }
    }


    template<typename ResultT, typename BitsT>
        requires ( std::is_integral_v<BitsT>&& std::is_integral_v<ResultT>&& std::is_unsigned_v<ResultT> )
    inline constexpr ResultT BitsToUnsigned( const BitsT bits, const UInt32 startIndex, const UInt32 bitCount )
    {
        using UnsignedType = std::make_unsigned_t<BitsT>;
        if constexpr ( sizeof( BitsT ) <= 4 )
        {
            return static_cast< ResultT >( ExtractBits32( static_cast< UInt32 >( std::bit_cast< UnsignedType >( bits ) ), startIndex, bitCount ) );
        }
        else
        {
            return static_cast< ResultT >( ExtractBits64( static_cast< UInt64 >( std::bit_cast< UnsignedType >( bits ) ), startIndex, bitCount ) );
        }
    }

    template<typename ResultT, typename BitsT>
        requires ( std::is_integral_v<BitsT>&& std::is_integral_v<ResultT>&& std::is_signed_v<ResultT> )
    inline constexpr ResultT BitsToSigned( const BitsT bits, const UInt32 startIndex, const UInt32 bitCount )
    {
        using UnsignedType = std::make_unsigned_t<ResultT>;
        auto value = static_cast< ResultT >(BitsToUnsigned<UnsignedType>( bits, startIndex, bitCount ));
        if ( bitCount > 1 )
        {
            auto signMask = static_cast< ResultT >( static_cast< UnsignedType >(1U) << ( bitCount - 1 ) );
            if ( value & signMask )
            {
                value = -( value & ~signMask );
            }
        }
        return value;
    }

    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr Byte BitsToByte( const BitsT bits, UInt32 startIndex, UInt32 bitCount )
    {
        return BitsToUnsigned<Byte>( bits, startIndex, bitCount );
    }
    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr SByte BitsToSByte( const BitsT bits, UInt32 startIndex, UInt32 bitCount )
    {
        return BitsToSigned<SByte>( bits, startIndex, bitCount );
        
    }
    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr UInt16 BitsToUInt16( const BitsT bits, UInt32 startIndex, UInt32 bitCount )
    {
        return BitsToUnsigned<UInt16>( bits, startIndex, bitCount );
    }
    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr Int16 BitsToInt16( const BitsT bits, UInt32 startIndex, UInt32 bitCount )
    {
        return BitsToSigned<Int16>( bits, startIndex, bitCount );
    }
    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr UInt32 BitsToUInt32( const BitsT bits, UInt32 startIndex, UInt32 bitCount )
    {
        return BitsToUnsigned<UInt32>( bits, startIndex, bitCount );
    }
    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr Int32 BitsToInt32( const BitsT bits, UInt32 startIndex, UInt32 bitCount )
    {
        return BitsToSigned<Int32>( bits, startIndex, bitCount );
    }
    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr UInt64 BitsToUInt64( const BitsT bits, UInt32 startIndex, UInt32 bitCount )
    {
        return BitsToUnsigned<UInt64>( bits, startIndex, bitCount );
    }
    template<typename BitsT>
        requires std::is_integral_v<BitsT>
    inline constexpr Int64 BitsToInt64( const BitsT bits, UInt32 startIndex, UInt32 bitCount )
    {
        return BitsToSigned<Int64>( bits, startIndex, bitCount );
    }

    template<typename T>
        requires (std::is_integral_v<T> && std::is_unsigned_v<T>)
    inline constexpr T GrayEncode( T value )
    {
        return value ^ ( value >> 1 );
    }

    template<typename T>
        requires ( std::is_integral_v<T>&& std::is_signed_v<T> )
    inline constexpr T GrayEncode( T value )
    {
        using UnsignedType = std::make_unsigned_t<T>;
        return std::bit_cast<T>( GrayEncode( std::bit_cast< UnsignedType >( value ) ) );
    }


    template<typename T>
        requires ( std::is_integral_v<T>&& std::is_unsigned_v<T> )
    inline constexpr T GrayDecode( T value )
    {
        constexpr auto InitialShift = (sizeof( T ) * CHAR_BIT) - 1; 
        for ( T bit = static_cast<T>(1U) << InitialShift; bit > 1; bit >>= 1 )
        {
            if ( value & bit )
            {
                value ^= bit >> 1;
            }
        }
        return value;
    }

    template<typename T>
        requires ( std::is_integral_v<T>&& std::is_signed_v<T> )
    inline constexpr T GrayDecode( T value )
    {
        using UnsignedType = std::make_unsigned_t<T>;
        return std::bit_cast< T >( GrayDecode( std::bit_cast< UnsignedType >( value ) ) );
    }

    /// <summary>
    /// A type that holds a fixed number of bits
    /// </summary>
    /// <remarks>
    /// This template was intentionally designed for a little-endian architecture.
    /// </remarks>
    template<size_t bitCount>
    class Bits
    {
        static_assert( bitCount <= 64, "bitCount > 64 is not supported." );
    public:
        static constexpr size_t Size = bitCount;
        using word_type = typename BitMask<Size>::type;
        static constexpr word_type Mask = BitMask<Size>::value;
        using value_type = bool;
        static constexpr size_t BytesPerWord = sizeof( word_type );
        static constexpr size_t BitsPerByte = CHAR_BIT;
        static constexpr size_t BitsPerWord = sizeof( word_type ) * BitsPerByte;
        static constexpr size_t UnusedBits = BitsPerWord - Size;
        static constexpr word_type One = static_cast<word_type>( 1 );
    private:
        word_type value_ = 0;
    public:
        constexpr Bits( ) noexcept = default;
        constexpr explicit Bits( word_type value ) noexcept
            : value_( value & Mask )
        { }

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }
        class reference
        {
            Bits& bits_;
            word_type mask_;
        public:
            constexpr reference( Bits& bits, size_t index ) noexcept
                : bits_( bits ), mask_( static_cast<word_type>(One << index) )
            {
            }

            reference( ) = delete;
            reference( const reference& ) = default;

            template<size_t N>
            constexpr reference& operator=( const typename Bits<N>::reference& other ) noexcept
            {
                if ( other.bits_.value_ & other.mask_ )
                {
                    bits_.value_ |= mask_;
                }
                else
                {
                    bits_.value_ &= ~mask_;
                }
                return *this;
            }

            constexpr reference& operator=( bool value ) noexcept
            {
                /*
#pragma warning(push)
#pragma warning(disable:4804)
                bits_.value_ = ( bits_.value_ & ~mask_ ) | ( -value & mask_ );
#pragma warning(pop)
                */
                
                if ( value )
                {
                    bits_.value_ |= mask_;
                }
                else
                {
                    bits_.value_ &= ~mask_;
                }
                
                return *this;
            }

            constexpr __forceinline operator bool( ) const noexcept
            {
                return bits_.value_ & mask_;
            }
        };


        constexpr word_type Value( ) const noexcept
        {
            return value_;
        }


        // Indexing.
        constexpr reference operator[]( size_t index ) noexcept
        {
            return reference( *this, index );
        }

        constexpr bool __forceinline operator[]( size_t index ) const noexcept
        {
            return value_ & ( static_cast<word_type>(One << index) );
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return any( );
        }

        constexpr auto operator <=> ( const Bits& other ) const noexcept = default;

        constexpr Bits operator~( ) const noexcept
        {
            return Bits( ~value_ );
        }

        constexpr Bits& operator|=( const Bits& other ) noexcept
        {
            value_ |= other.value_;
            return *this;
        }
        constexpr Bits& operator&=( const Bits& other ) noexcept
        {
            value_ &= other.value_;
            return *this;
        }
        constexpr Bits& operator^=( const Bits& other ) noexcept
        {
            value_ ^= other.value_;
            return *this;
        }
        template<typename T>
            requires std::is_integral_v<T>
        constexpr Bits& operator<<=( const T& val ) noexcept
        {
            value_ = (value_ << val) & Mask;
            return *this;
        }
        template<typename T>
            requires std::is_integral_v<T>
        constexpr Bits& operator>>=( const T& val ) noexcept
        {
            value_ >>= val;
            return *this;
        }



        constexpr void reverse( ) noexcept
        {
            value_ <<= ( BitsPerWord - Size );
            if constexpr ( BytesPerWord == 8 )
            {
                const auto* srcBytes = reinterpret_cast<Byte*>( &value_ );
                word_type dest;
                auto* destBytes = reinterpret_cast<Byte*>( &dest );
                destBytes[0] = ReverseBits( srcBytes[7] );
                destBytes[1] = ReverseBits( srcBytes[6] );
                destBytes[2] = ReverseBits( srcBytes[5] );
                destBytes[3] = ReverseBits( srcBytes[4] );
                destBytes[4] = ReverseBits( srcBytes[3] );
                destBytes[5] = ReverseBits( srcBytes[2] );
                destBytes[6] = ReverseBits( srcBytes[1] );
                destBytes[7] = ReverseBits( srcBytes[0] );
                value_ = dest;
            }
            else if constexpr ( BytesPerWord == 4 )
            {
                const auto* srcBytes = reinterpret_cast<Byte*>( &value_ );
                word_type dest;
                auto* destBytes = reinterpret_cast<Byte*>( &dest );
                destBytes[0] = ReverseBits( srcBytes[3] );
                destBytes[1] = ReverseBits( srcBytes[2] );
                destBytes[2] = ReverseBits( srcBytes[1] );
                destBytes[3] = ReverseBits( srcBytes[0] );
                value_ = dest;
            }
            else if constexpr ( BytesPerWord == 2 )
            {
                const auto* srcBytes = reinterpret_cast<Byte*>( &value_ );
                word_type dest;
                auto* destBytes = reinterpret_cast<Byte*>( &dest );
                destBytes[0] = ReverseBits( srcBytes[1] );
                destBytes[1] = ReverseBits( srcBytes[0] );
                value_ = dest;
            }
            else
            {
                value_ = ReverseBits( value_ );
            }
        }
        constexpr Bits reversed( ) const noexcept
        {
            Bits bits( value_ );
            bits.reverse( );
            return bits;
        }

        constexpr void flip( ) noexcept
        {
            value_ = ( ~value_ ) & Mask;
        }
        constexpr Bits flipped( ) const noexcept
        {
            return Bits( ~value_ );
        }


        constexpr bool all( ) const noexcept
        {
            return value_ == Mask;
        }
        constexpr bool any( ) const noexcept
        {
            return (value_ & Mask) != 0;
        }
        constexpr bool none( ) const noexcept
        {
            return value_ == 0;
        }

        constexpr bool test( size_t index ) const noexcept
        {
            return value_ & ( One << index );
        }

        template<size_t N>
        constexpr bool test( ) const noexcept
        {
            static_assert( N < Size, "N must be less than the bitCount template parameter for this Bits<bitCount> type" );
            constexpr word_type mask = static_cast<word_type>( One << N );
            return value_ & mask;
        }


        constexpr size_t count( ) const noexcept
        {
            if ( std::is_constant_evaluated( ) )
            {
                size_t result = 0;
                for ( size_t i = 0; i < Size; ++i )
                {
                    if ( value_ & ( 1 << i ) )
                    {
                        result++;
                    }
                }
                return result;
            }
            else
            {
                if constexpr ( sizeof( value_type ) == 8 )
                {
                    return static_cast<size_t>( _mm_popcnt_u64( value_ ) );
                }
                else
                {
                    return static_cast<size_t>( _mm_popcnt_u32( value_ ) );
                }
            }
        }

        constexpr void set( ) noexcept
        {
            value_ = Mask;
        }

        constexpr void set( size_t index ) noexcept
        {
            value_ |= One << index;
        }

        constexpr void set( size_t index, bool val ) noexcept
        {
            if ( val )
            {
                value_ |= One << index;
            }
            else
            {
                value_ &= ~( One << index );
            }
        }
        constexpr void reset( ) noexcept
        {
            value_ = 0;
        }
        constexpr void reset( size_t index ) noexcept
        {
            value_ &= ~( One << index );
        }

        //word_type extract( size_t index )

    };

    template<size_t N>
    constexpr Bits<N> operator | ( const Bits<N>& lhs, const Bits<N>& rhs ) noexcept
    {
        return Bits<N>( lhs.Value() | rhs.Value() );
    }
    template<size_t N>
    constexpr Bits<N> operator & ( const Bits<N>& lhs, const Bits<N>& rhs ) noexcept
    {
        return Bits<N>( lhs.Value( ) & rhs.Value( ) );
    }
    template<size_t N>
    constexpr Bits<N> operator ^ ( const Bits<N>& lhs, const Bits<N>& rhs ) noexcept
    {
        return Bits<N>( lhs.Value( ) ^ rhs.Value( ) );
    }
    template<typename T, size_t N>
        requires std::is_integral_v<T>
    constexpr Bits<N> operator << ( const Bits<N>& lhs, const T& rhs ) noexcept
    {
        return Bits<N>( lhs.Value( ) << rhs );
    }
    template<typename T, size_t N>
        requires std::is_integral_v<T>
    constexpr Bits<N> operator >> ( const Bits<N>& lhs, const T& rhs ) noexcept
    {
        return Bits<N>( lhs.Value( ) >> rhs );
    }

    namespace Internal
    {
        template<typename BitVectorT, typename BitVectorU>
        struct BitVectorLogicalResult
        {
            using type = std::conditional_t<sizeof( typename BitVectorT::word_type ) >= sizeof( typename BitVectorU::word_type ), BitVectorT, BitVectorU>;
        };
    }

    /// <summary>
    /// A resizeable bit-vector
    /// </summary>
    /// <typeparam name="VectorT">
    /// A std::vector like type that will be used as storage 
    /// for the bits
    /// </typeparam>
    /// <remarks>
    /// This template was intentionally designed for a little-endian architecture.
    /// </remarks>
    template<typename VectorT>
        requires requires( VectorT vec )
    {
        {
            vec.size( )
        } ->std::convertible_to<size_t>;
        {
            vec.data( )
        } ->std::convertible_to<typename VectorT::value_type*>;
        {
            vec[0]
        } ->std::convertible_to<typename VectorT::value_type>;
        {
            vec[0] = static_cast<typename VectorT::value_type>( 0 )
        };
        {
            vec.emplace_back( static_cast<typename VectorT::value_type>( 0 ) )
        };
        {
            vec.resize( static_cast<typename VectorT::size_type>( 0 ) )
        };
    } && IsInteger<typename VectorT::value_type>
    class BitVector
    {
    public:
        using VectorType = VectorT;
        using size_type = typename VectorType::size_type;
        using word_type = typename VectorType::value_type;
        static_assert( std::is_integral_v<word_type>, "Template argument must be a vector like type of an integral type." );

        static constexpr size_t BytesPerWord = sizeof( word_type );
        static constexpr size_t BitsPerByte = CHAR_BIT;
        static constexpr size_t BitsPerWord = sizeof( word_type ) * BitsPerByte;
        static constexpr word_type One = static_cast<word_type>( 1 );
    private:
        /// <summary>
        /// Number of bits in the bit-vector
        /// </summary>
        size_t size_ = 0;
        VectorType data_;
    public:
        BitVector( ) = default;

        explicit BitVector( bool value )
        {
            emplace_back( value );
        }

        template<typename T>
            requires std::is_integral_v<T>
        explicit BitVector( const T bits, size_t bitCount )
        {
            emplace_back( bits, bitCount );
        }

        template<typename T>
            requires std::is_integral_v<T>
        explicit BitVector( const T* bits, size_t bitCount )
            : size_( bitCount ), data_( reinterpret_cast<const word_type*>( bits ), reinterpret_cast<const word_type*>( bits ) + (bitCount % BitsPerWord ? (bitCount / BitsPerWord) + 1 : bitCount / BitsPerWord) )
        {
            size_t remainingBits = bitCount % BitsPerWord;
            if ( remainingBits )
            {
                word_type mask = CreateMask( remainingBits );
                data_[bitCount / BitsPerWord] &= mask;
            }
        }

        explicit BitVector( const VectorType& bits, size_t bitCount )
            : size_( bitCount ), data_( bits )
        {
            size_t remainingBits = bitCount % BitsPerWord;
            if ( remainingBits )
            {
                word_type mask = CreateMask( remainingBits );
                data_[bitCount / BitsPerWord] &= mask;
            }
        }


        class reference
        {
            word_type& word_;
            word_type mask_;
        public:

            reference( BitVector& bitVector, size_t index )  noexcept
                : word_( bitVector.data_[index / BitsPerWord] ), mask_( static_cast<word_type>( One << (index% BitsPerWord) ) )
            {
            }

            reference( ) = delete;
            reference( const reference& ) noexcept = default;

            reference& operator=( reference other ) noexcept
            {
                if ( other.word_ & other.mask_ )
                {
                    word_ |= mask_;
                }
                else
                {
                    word_ &= ~mask_;
                }
                return *this;
            }

            reference& operator=( bool value ) noexcept
            {
                if ( value )
                {
                    word_ |= mask_;
                }
                else
                {
                    word_ &= ~mask_;
                }
                return *this;
            }

            operator bool( ) const noexcept
            {
                return word_ & mask_;
            }
        };


        explicit operator bool( ) const noexcept
        {
            return any( );
        }

        constexpr bool empty( ) const noexcept
        {
            return size_ == 0;
        }

        // Indexing.
        reference operator[]( size_t index ) noexcept
        {
            return reference( *this, index );
        }

        bool operator[]( size_t index ) const noexcept
        {
            return ( data_[index / BitsPerWord] & ( One << ( index % BitsPerWord ) ) );
        }

        

        template<typename VectorU>
        bool EqualTo( const BitVector<VectorU>& other ) const noexcept
        {
            if ( size_ == other.size( ) )
            {
                size_t fullByteSize = size_ / BitsPerByte;
                if ( fullByteSize )
                {
                    if ( memcmp( data_.data( ), other.Vector( ).data( ), fullByteSize ) != 0 )
                    {
                        return false;
                    }
                }
                size_t remainingBitCount = size_ % BitsPerByte;
                if ( remainingBitCount != 0 )
                {
                    const Byte* thisPtr = reinterpret_cast<const Byte*>( data_.data( ) );
                    const Byte* otherPtr = reinterpret_cast<const Byte*>( other.Vector( ).data( ) );
                    Byte thisByte = thisPtr[fullByteSize];
                    Byte otherByte = otherPtr[fullByteSize];
                    Byte bitsMask = static_cast<Byte>( CreateMask( remainingBitCount ) );
                    return ( thisByte & bitsMask ) == ( otherByte & bitsMask );
                }
                return true;
            }
            else
            {
                return false;
            }
        }

        template<typename VectorU>
        bool operator == ( const BitVector<VectorU>& other ) const noexcept
        {
            return EqualTo( other );
        }
        template<typename VectorU>
        bool operator != ( const BitVector<VectorU>& other ) const noexcept
        {
            return EqualTo( other ) == false;
        }

        const VectorType& Vector( ) const noexcept
        {
            return data_;
        }

        word_type* data( ) noexcept
        {
            return data_.data( );
        }
        const word_type* data( ) const noexcept
        {
            return data_.data( );
        }

        constexpr size_t size( ) const noexcept
        {
            return size_;
        }

        constexpr size_t DataSize( ) const noexcept
        {
            return data_.size();
        }


        bool test( size_t index ) const noexcept
        {
            return ( data_[index / BitsPerWord] & ( One << ( index % BitsPerWord ) ) );
        }

        constexpr size_t count( ) const noexcept
        {
            const size_t fullByteCount = size_ / BitsPerByte;
            const size_t fullByteOverflowBitCount = size_ % BitsPerByte;
            const size_t fullUInt64Count = fullByteCount / sizeof( UInt64 );
            const size_t fullUInt64OverflowByteCount = fullByteCount % sizeof( UInt64 );
            const UInt64* uint64Ptr = reinterpret_cast<const UInt64*>( data( ) );
            const UInt64* uint64EndPtr = uint64Ptr + fullUInt64Count;
            size_t result = 0;
            while ( uint64Ptr < uint64EndPtr )
            {
                result += static_cast<size_t>( _mm_popcnt_u64( *uint64Ptr ) );
                uint64Ptr++;
            }
            if ( fullUInt64OverflowByteCount )
            {
                UInt64 value = 0;
                if ( fullByteOverflowBitCount )
                {
                    memcpy( &value, uint64Ptr, fullUInt64OverflowByteCount + 1 );
                    Byte* bytePtr = reinterpret_cast<Byte*>( &value );
                    const Byte byteMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( fullByteOverflowBitCount ) ) );
                    bytePtr[fullUInt64OverflowByteCount] &= byteMask;
                }
                else
                {
                    memcpy( &value, uint64Ptr, fullUInt64OverflowByteCount );
                }
                result += static_cast<size_t>( _mm_popcnt_u64( value ) );
            }
            else if ( fullByteOverflowBitCount )
            {
                const Byte* bytePtr = reinterpret_cast<const Byte*>( uint64Ptr );
                const Byte byteMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( fullByteOverflowBitCount ) ) );
                Byte byteValue = *bytePtr & byteMask;
                result += static_cast<size_t>( _mm_popcnt_u32( byteValue ) );
            }
            return result;
        }


    private:
        static constexpr word_type CreateMask( size_t size ) noexcept
        {
            if constexpr ( sizeof( word_type ) == 8 )
            {
                return static_cast<word_type>( CreateBitMask64( static_cast<UInt32>( size ) ) );
            }
            else
            {
                return static_cast<word_type>( CreateBitMask32( static_cast<UInt32>( size ) ) );
            }
        }
    public:
        

        bool all( ) const noexcept
        {
            if ( size_ )
            {
                size_t fullWordSize = size_ / BitsPerWord;
                if ( fullWordSize == 0 )
                {
                    word_type bitsMask = CreateMask( size_ );
                    return ( *data_.data( ) & bitsMask ) == bitsMask;
                }
                else
                {
                    size_t remainingBitsInLastWord = size_ % BitsPerWord;
                    size_t fullUInt64Size = fullWordSize / (sizeof( UInt64 )/sizeof(word_type) );
                    
                    if ( fullUInt64Size == 0 )
                    {
                        constexpr word_type wordMask = ~word_type( 0 );
                        const word_type* words = data_.data( );
                        const word_type* fullWordsEnd = words + fullWordSize;
                        while ( words < fullWordsEnd )
                        {
                            if ( *words != wordMask )
                            {
                                return false;
                            }
                            words++;
                        }
                        if ( remainingBitsInLastWord )
                        {
                            word_type bitsMask = CreateMask( remainingBitsInLastWord );
                            return ( *words & bitsMask ) == bitsMask;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else
                    {
                        size_t remainingWords = fullWordSize % ( sizeof( UInt64 ) / sizeof( word_type ) );

                        constexpr UInt64 uint64Mask = ~UInt64( 0 );
                        const UInt64* uint64s = reinterpret_cast<const UInt64*>(data_.data( ));
                        const UInt64* uint64sEnd = uint64s + fullUInt64Size;
                        while ( uint64s < uint64sEnd )
                        {
                            if ( *uint64s != uint64Mask )
                            {
                                return false;
                            }
                            uint64s++;
                        }
                        if ( remainingWords )
                        {
                            constexpr word_type wordMask = ~word_type( 0 );
                            const word_type* words = reinterpret_cast<const word_type*>( uint64s );
                            const word_type* wordsEnd = words + remainingWords;
                            while ( words < wordsEnd )
                            {
                                if ( *words != wordMask )
                                {
                                    return false;
                                }
                                words++;
                            }
                            if ( remainingBitsInLastWord )
                            {
                                word_type bitsMask = CreateMask( remainingBitsInLastWord );
                                return ( *words & bitsMask ) == bitsMask;
                            }
                            else
                            {
                                return true;
                            }
                        }
                        if ( remainingBitsInLastWord )
                        {
                            const word_type* words = reinterpret_cast<const word_type*>( uint64s );
                            word_type bitsMask = CreateMask( remainingBitsInLastWord );
                            return ( *words & bitsMask ) == bitsMask;
                        }
                        else
                        {
                            return true;
                        }
                    }
                }
            }
            else
            {
                return true;
            }
        }
        bool none( ) const noexcept
        {
            if ( size_ )
            {
                size_t fullWordSize = size_ / BitsPerWord;
                if ( fullWordSize == 0 )
                {
                    word_type bitsMask = CreateMask( size_ );
                    return ( *data_.data( ) & bitsMask ) == 0;
                }
                else
                {
                    size_t remainingBitsInLastWord = size_ % BitsPerWord;
                    size_t fullUInt64Size = fullWordSize / ( sizeof( UInt64 ) / sizeof( word_type ) );

                    if ( fullUInt64Size == 0 )
                    {
                        const word_type* words = data_.data( );
                        const word_type* fullWordsEnd = words + fullWordSize;
                        while ( words < fullWordsEnd )
                        {
                            if ( *words != static_cast<word_type>( 0 ) )
                            {
                                return false;
                            }
                            words++;
                        }
                        if ( remainingBitsInLastWord )
                        {
                            word_type bitsMask = CreateMask( remainingBitsInLastWord );
                            return ( *words & bitsMask ) == 0;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else
                    {
                        size_t remainingWords = fullWordSize % ( sizeof( UInt64 ) / sizeof( word_type ) );

                        const UInt64* uint64s = reinterpret_cast<const UInt64*>( data_.data( ) );
                        const UInt64* uint64sEnd = uint64s + fullUInt64Size;
                        while ( uint64s < uint64sEnd )
                        {
                            if ( *uint64s != 0 )
                            {
                                return false;
                            }
                            uint64s++;
                        }
                        if ( remainingWords )
                        {
                            const word_type* words = reinterpret_cast<const word_type*>( uint64s );
                            const word_type* wordsEnd = words + remainingWords;
                            while ( words < wordsEnd )
                            {
                                if ( *words != 0 )
                                {
                                    return false;
                                }
                                words++;
                            }
                            if ( remainingBitsInLastWord )
                            {
                                word_type bitsMask = CreateMask( remainingBitsInLastWord );
                                return ( *words & bitsMask ) == 0;
                            }
                            else
                            {
                                return true;
                            }
                        }
                        if ( remainingBitsInLastWord )
                        {
                            const word_type* words = reinterpret_cast<const word_type*>( uint64s );
                            word_type bitsMask = CreateMask( remainingBitsInLastWord );
                            return ( *words & bitsMask ) == 0;
                        }
                        else
                        {
                            return true;
                        }
                    }
                }
            }
            else
            {
                return true;
            }
        }

        bool any( ) const
        {
            return none( ) == false;
        }

    private:
        
    public:
        constexpr size_t capacity( ) const noexcept
        {
            return data_.capacity( ) * BitsPerWord;
        }
        void reserve( size_t numberOfBits )
        {
            size_t fullWordSize = numberOfBits / BitsPerWord;
            size_t remainder = numberOfBits % BitsPerWord;
            data_.reserve( remainder ? fullWordSize + 1 : fullWordSize );
        }
    public:
        void clear( )
        {
            data_.clear( );
            size_ = 0;
        }

        void swap( BitVector& other ) noexcept
        {
            data_.swap( other.data_ );
            std::swap( size_, other.size_ );
        }

        void resize( size_t newSize, bool value = false )
        {
            if ( newSize > size_ )
            {
                size_t newFullWordSize = newSize / BitsPerWord;
                size_t newRemainingBits = newSize % BitsPerWord;
                size_t currentFullWordSize = size_ / BitsPerWord;
                size_t currentRemainingBits = size_ % BitsPerWord;
                data_.resize( newRemainingBits ? newFullWordSize + 1 : newFullWordSize, value ? ~word_type( 0 ) : word_type( 0 ) );
                word_type* dataPtr = data_.data( );
                if ( value )
                {
                    if ( currentRemainingBits )
                    {
                        auto mask = CreateMask( currentRemainingBits );
                        dataPtr[currentFullWordSize] &= mask;
                    }
                    if ( newRemainingBits )
                    {
                        auto mask = CreateMask( newRemainingBits );
                        dataPtr[newFullWordSize] |= mask;
                    }
                }
                else
                {
                    if ( currentRemainingBits )
                    {
                        auto mask = CreateMask( currentRemainingBits );
                        dataPtr[currentFullWordSize] &= mask;
                    }
                }
                size_ = newSize;
            }
            else if ( newSize < size_ )
            {
                if ( newSize )
                {
                    size_t newFullWordSize = newSize / BitsPerWord;
                    size_t newRemainingBits = newSize % BitsPerWord;
                    if ( newRemainingBits )
                    {
                        data_.resize( newFullWordSize + 1 );
                        word_type mask = CreateMask( newRemainingBits );
                        data_[newFullWordSize] = data_[newFullWordSize] & mask;
                    }
                    else
                    {
                        data_.resize( newFullWordSize );
                    }
                    size_ = newSize;
                }
                else
                {
                    data_.clear( );
                    size_ = 0;
                }
            }
        }
        void emplace_back( bool value )
        {
            if ( size_ < data_.size( ) * BitsPerWord )
            {
                word_type bitMask = One << ( size_ % BitsPerWord );
                if ( value )
                {
                    data_[size_ / BitsPerWord] |= bitMask;
                }
                else
                {
                    data_[size_ / BitsPerWord] &= ~bitMask;
                }
            }
            else
            {
                data_.emplace_back( value ? 1 : 0 );
            }
            size_++;
        }
        void push_back( bool value )
        {
            emplace_back( value );
        }

        
        template<size_t N>
        void append( const Bits<N> values )
        {
            append( values.Value(), Bits<N>::Size );
        }

        template<typename T>
            requires std::is_integral_v<T>
        void append( const T value, size_t bitCount = sizeof(T) * BitsPerByte )
        {
            assert( bitCount <= (sizeof( T ) * BitsPerByte) && "bitCount must be less than, or equal, to the number of bits of the value type." );
            if constexpr ( sizeof( T ) >= sizeof( word_type ) )
            {
                if ( (bitCount == sizeof( T ) * BitsPerByte) && ( size( ) == data_.size( ) * BitsPerWord ) )
                {
                
                    constexpr auto wordsPerValue = sizeof( T ) / sizeof( word_type );
                    const word_type* words = reinterpret_cast<const word_type*>( &value );
                    for ( size_t i = 0; i < wordsPerValue; i++ )
                    {
                        data_.emplace_back( words[i] );
                    }
                    size_ += sizeof( T ) * BitsPerByte;
                    return;
                }
            }
            for ( size_t i = 0; i < bitCount; i++ )
            {
                T valueMask = static_cast<T>( 1 ) << i;
                bool valueHasBitOn = ( value & valueMask ) != 0;
                push_back( valueHasBitOn );
            }
        }

        /*
        template<typename T>
            requires std::is_integral_v<T>
        void append( const T* bits, size_t bitCount )
        {
            assert( ( bits || bitCount == 0 ) );
            if ( bitCount )
            {
                const size_t size = size_;
                const size_t newSize = size + bitCount;
                resize( newSize );
                const size_t currentFullByteCount = size / BitsPerByte;
                const size_t currentFullByteOverflowBitCount = size % BitsPerByte;
                if ( currentFullByteOverflowBitCount )
                {
                    const size_t bitsFullByteCount = bitCount / BitsPerByte;
                    const size_t bitsFullByteOverflowBitCount = bitCount % BitsPerByte;
                    const size_t srcUInt64Count = bitsFullByteCount / sizeof( UInt64 );
                    const size_t srcUInt64ByteOverflowCount = bitsFullByteCount % sizeof( UInt64 );
                    
                    word_type* wordDestPtr = data( ) + (currentFullByteCount/sizeof( word_type ));
                    UInt64* destUInt64Ptr = reinterpret_cast< UInt64* >( wordDestPtr );
                    const UInt64* srcUInt64Ptr = reinterpret_cast< const UInt64* >( bits );
                    const UInt64* srcUInt64EndPtr = srcUInt64Ptr + srcUInt64Count;
                    
                    
                    const UInt64 mask = CreateBitMask64( static_cast< UInt32 >( currentFullByteOverflowBitCount ) );
                    word_type overflowWordValue = *wordDestPtr;
                    UInt64 overflowValue = static_cast<UInt64>( overflowWordValue ) & mask;
                    const UInt64 overflowValueUInt64RightShift = 64ULL - currentFullByteOverflowBitCount;
                    while ( srcUInt64Ptr < srcUInt64EndPtr )
                    {
                        const UInt64 value = *srcUInt64Ptr;
                        *destUInt64Ptr = overflowValue | ( value << currentFullByteOverflowBitCount );
                        overflowValue = value >> overflowValueUInt64RightShift;
                        destUInt64Ptr++;
                        srcUInt64Ptr++;
                    }
                    
                    const Byte* srcPtr = reinterpret_cast<const Byte*>( srcUInt64Ptr );
                    Byte* destPtr = reinterpret_cast<Byte*>( destUInt64Ptr );
                    Byte overflowByteValue = static_cast<Byte>( overflowValue );
                    const UInt64 overflowValueByteRightShift = 8ULL - currentFullByteOverflowBitCount;
                    if ( srcUInt64ByteOverflowCount )
                    {
                        const Byte* srcEndPtr = srcPtr + srcUInt64ByteOverflowCount;
                        while ( srcPtr < srcEndPtr )
                        {
                            const Byte value = *srcPtr;
                            *destPtr = overflowByteValue | ( value << currentFullByteOverflowBitCount );
                            overflowByteValue = value >> overflowValueByteRightShift;
                            destPtr++;
                            srcPtr++;
                        }
                    }
                    if ( bitsFullByteOverflowBitCount )
                    {
                        const Byte srcMask = static_cast<Byte>(CreateBitMask32( static_cast<UInt32>( bitsFullByteOverflowBitCount ) ));
                        const Byte value = ( *srcPtr ) & srcMask;
                        if ( ( bitsFullByteOverflowBitCount + currentFullByteOverflowBitCount ) <= BitsPerByte )
                        {
                            *destPtr = overflowByteValue | ( value << currentFullByteOverflowBitCount );
                        }
                        else
                        {
                            *destPtr = overflowByteValue | ( value << currentFullByteOverflowBitCount );
                            destPtr++;
                            *destPtr = value >> overflowValueByteRightShift;
                        }
                    }
                    else
                    {
                        *destPtr = overflowByteValue;
                    }
                }
                else
                {
                    // The trivial case 
                    Byte* destPtr = reinterpret_cast<Byte*>( data( ) ) + currentFullByteCount;
                    const size_t bitsFullByteCount = bitCount / BitsPerByte;
                    const size_t bitsFullByteOwerflowBitCount = bitCount % BitsPerByte;
                    memcpy( destPtr, bits, bitsFullByteOwerflowBitCount ? bitsFullByteCount + 1 : bitsFullByteCount );
                    if ( bitsFullByteOwerflowBitCount )
                    {
                        const Byte mask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( bitsFullByteOwerflowBitCount ) ) );
                        destPtr[bitsFullByteCount] &= mask;
                    }
                }
            }
        }
        */

        template<typename T>
            requires std::is_integral_v<T>
        void append( const T* bits, size_t bitCount )
        {
            assert( ( bits || bitCount == 0 ) );
            if ( bitCount )
            {
                const size_t size = size_;
                const size_t newSize = size + bitCount;
                resize( newSize );

                const size_t destinationFullByteCount = size / BitsPerByte;
                const size_t destinationOverflowBitCount = size % BitsPerByte;

                const size_t sourceFullByteCount = bitCount / BitsPerByte;
                const size_t sourceFullByteOverflowBitCount = bitCount % BitsPerByte;

                if ( destinationOverflowBitCount )
                {
                    const Byte destinationMask = static_cast<Byte>(CreateMask( destinationOverflowBitCount ));

                    const Byte* sourcePtr = reinterpret_cast< const Byte* >( bits );
                    Byte* destPtr = reinterpret_cast< Byte* >( data() ) + destinationFullByteCount;
                    Byte overflowByteValue = (*destPtr) & destinationMask;
                    const size_t overflowValueByteRightShift = 8ULL - destinationOverflowBitCount;

                    const Byte* sourceEndPtr = sourcePtr + sourceFullByteCount;
                    while ( sourcePtr < sourceEndPtr )
                    {
                        const Byte value = *sourcePtr;
                        *destPtr = overflowByteValue | ( value << destinationOverflowBitCount );
                        overflowByteValue = value >> overflowValueByteRightShift;
                        destPtr++;
                        sourcePtr++;
                    }
                    
                    if ( sourceFullByteOverflowBitCount )
                    {
                        const Byte sourceMask = static_cast< Byte >( CreateBitMask32( static_cast< UInt32 >( sourceFullByteOverflowBitCount ) ) );
                        const Byte value = ( *sourcePtr ) & sourceMask;
                        if ( ( sourceFullByteOverflowBitCount + destinationOverflowBitCount ) <= BitsPerByte )
                        {
                            *destPtr = overflowByteValue | ( value << destinationOverflowBitCount );
                        }
                        else
                        {
                            *destPtr = overflowByteValue | ( value << destinationOverflowBitCount );
                            destPtr++;
                            *destPtr = value >> overflowValueByteRightShift;
                        }
                    }
                    else
                    {
                        *destPtr = overflowByteValue;
                    }


                }
                else
                {
                    // The trivial case 
                    Byte* destPtr = reinterpret_cast< Byte* >( data( ) ) + destinationFullByteCount;
                    
                    memcpy( destPtr, bits, sourceFullByteOverflowBitCount ? sourceFullByteCount + 1 : sourceFullByteCount );
                    if ( sourceFullByteOverflowBitCount )
                    {
                        const Byte mask = static_cast< Byte >( CreateMask( static_cast< UInt32 >( sourceFullByteOverflowBitCount ) ) );
                        destPtr[ sourceFullByteCount ] &= mask;
                    }
                }
            }
        }


        template<typename VectorU>
        void append( const BitVector<VectorU>& other )
        {
            append( other.data( ), other.size( ) );
        }
        void append( bool value )
        {
            emplace_back( value );
        }


        void flip( ) noexcept
        {
            Byte* bytePtr = reinterpret_cast<Byte*>( data_.data( ) );
            size_t bytesUntil64BitBoundary = AlignedPaddingFor<sizeof( UInt64 )>( data_.data( ) );
            size_t fullByteSize = size_ / BitsPerByte;
            if ( fullByteSize <= bytesUntil64BitBoundary )
            {
                Byte* byteEndPtr = bytePtr + fullByteSize;
                while ( bytePtr < byteEndPtr )
                {
                    *bytePtr = ~( *bytePtr );
                    bytePtr++;
                }
                auto remainingBits = size_ % BitsPerByte;
                if ( remainingBits )
                {
                    Byte mask = static_cast<Byte>( CreateMask( remainingBits ) );
                    *bytePtr = mask & ~( *bytePtr );
                }
            }
            else
            {
                Byte* byteEndPtr = bytePtr + bytesUntil64BitBoundary;
                while ( bytePtr < byteEndPtr )
                {
                    *bytePtr = ~( *bytePtr );
                    bytePtr++;
                }
                size_t remainingByteSize = fullByteSize - bytesUntil64BitBoundary;
                size_t fullUInt64Size = remainingByteSize / sizeof( UInt64 );
                UInt64* uint64Ptr = reinterpret_cast<UInt64*>( bytePtr );
                const UInt64* uint64EndPtr = uint64Ptr + fullUInt64Size;
                while ( uint64Ptr < uint64EndPtr )
                {
                    *uint64Ptr = ~( *uint64Ptr );
                    uint64Ptr++;
                }
                bytePtr = reinterpret_cast<Byte*>( uint64Ptr );
                remainingByteSize %= sizeof( UInt64 );
                if ( remainingByteSize )
                {
                    Byte* byteEndPtr = bytePtr + remainingByteSize;
                    while ( bytePtr < byteEndPtr )
                    {
                        *bytePtr = ~( *bytePtr );
                        bytePtr++;
                    }
                }
                auto remainingBits = size_ % BitsPerByte;
                if ( remainingBits )
                {
                    Byte mask = static_cast<Byte>( CreateMask( remainingBits ) );
                    *bytePtr = mask & ~( *bytePtr );
                }
            }
        }

        BitVector flipped( ) const
        {
            BitVector result(*this);
            result.flip();
            return result;
        }
        BitVector operator~( ) const
        {
            return flipped( );
        }

        template<typename VectorU>
        void And( const BitVector<VectorU>& other )
        {
            size_t otherSize = other.size( );
            
            const UInt64* otherUInt64Ptr = reinterpret_cast<const UInt64*>( other.data( ) );

            if ( otherSize > size_ )
            {
                size_t thisSize = size_;
                resize( otherSize );
                UInt64* thisUInt64Ptr = reinterpret_cast<UInt64*>( data( ) );
                size_t thisFullByteSize = thisSize / BitsPerByte;
                size_t thisRemainingBits = thisSize % BitsPerByte;
                size_t thisFullUInt64Size = thisFullByteSize / sizeof(UInt64);
                size_t thisRemainingBytes = thisFullByteSize % sizeof( UInt64 );
                const UInt64* thisUInt64EndPtr = thisUInt64Ptr + thisFullUInt64Size;
                while ( thisUInt64Ptr < thisUInt64EndPtr )
                {
                    *thisUInt64Ptr &= *otherUInt64Ptr;
                    thisUInt64Ptr++;
                    otherUInt64Ptr++;
                }
                Byte* thisPtr = reinterpret_cast<Byte*>( thisUInt64Ptr );
                const Byte* otherPtr = reinterpret_cast<const Byte*>( otherUInt64Ptr );

                if ( thisRemainingBytes )
                {
                    const Byte* thisEndPtr = thisPtr + thisRemainingBytes;
                    while ( thisPtr < thisEndPtr )
                    {
                        *thisPtr &= *otherPtr;
                        thisPtr++;
                        otherPtr++;
                    }
                }
                if ( thisRemainingBits )
                {
                    Byte mask = static_cast<Byte>( CreateBitMask32(static_cast<UInt32>( thisRemainingBits )) );
                    *thisPtr &= ( *otherPtr ) & mask;
                }
            }
            else
            {
                UInt64* thisUInt64Ptr = reinterpret_cast<UInt64*>( data( ) );
                size_t thisFullByteSize = size_ / BitsPerByte;
                size_t thisRemainingBits = size_ % BitsPerByte;
                size_t otherFullByteSize = otherSize / BitsPerByte;
                size_t otherRemainingBits = otherSize % BitsPerByte;
                size_t otherFullUInt64Size = otherFullByteSize / sizeof( UInt64 );
                size_t otherRemainingBytes = otherFullByteSize % sizeof( UInt64 );
                const UInt64* otherUInt64EndPtr = otherUInt64Ptr + otherFullUInt64Size;

                while ( otherUInt64Ptr < otherUInt64EndPtr )
                {
                    *thisUInt64Ptr &= *otherUInt64Ptr;
                    thisUInt64Ptr++;
                    otherUInt64Ptr++;
                }
                Byte* thisPtr = reinterpret_cast<Byte*>( thisUInt64Ptr );
                const Byte* otherPtr = reinterpret_cast<const Byte*>( otherUInt64Ptr );

                if ( otherRemainingBytes )
                {
                    const Byte* otherEndPtr = otherPtr + otherRemainingBytes;
                    while ( otherPtr < otherEndPtr )
                    {
                        *thisPtr &= *otherPtr;
                        thisPtr++;
                        otherPtr++;
                    }
                }
                if ( otherRemainingBits )
                {
                    Byte mask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( otherRemainingBits ) ) );
                    *thisPtr &= ( *otherPtr ) & mask;
                    thisPtr++;
                    otherPtr++;
                }

                Byte* thisEndPtr = reinterpret_cast<Byte*>( data_.data( ) ) + (sizeof( word_type ) * data_.size( ));
                if ( thisPtr < thisEndPtr )
                {
                    size_t remaining = thisEndPtr - thisPtr;
                    memset( thisPtr, 0, remaining );
                    thisPtr += remaining;
                }
            }
        }

        template<typename VectorU>
        BitVector& operator &= ( const BitVector<VectorU>& other )
        {
            And( other );
            return *this;
        }

        template<typename VectorU>
        void Or( const BitVector<VectorU>& other )
        {
            size_t otherSize = other.size( );

            const UInt64* otherUInt64Ptr = reinterpret_cast<const UInt64*>( other.data( ) );

            if ( otherSize > size_ )
            {
                size_t thisSize = size_;
                resize( otherSize );
                UInt64* thisUInt64Ptr = reinterpret_cast<UInt64*>( data( ) );
                size_t thisFullByteSize = thisSize / BitsPerByte;
                size_t thisRemainingBits = thisSize % BitsPerByte;
                size_t thisFullUInt64Size = thisFullByteSize / sizeof( UInt64 );
                size_t thisRemainingBytes = thisFullByteSize % sizeof( UInt64 );
                const UInt64* thisUInt64EndPtr = thisUInt64Ptr + thisFullUInt64Size;
                size_t otherFullByteSize = otherSize / BitsPerByte;
                size_t otherRemainingBits = otherSize % BitsPerByte;

                while ( thisUInt64Ptr < thisUInt64EndPtr )
                {
                    *thisUInt64Ptr |= *otherUInt64Ptr;
                    thisUInt64Ptr++;
                    otherUInt64Ptr++;
                }
                Byte* thisPtr = reinterpret_cast<Byte*>( thisUInt64Ptr );
                const Byte* otherPtr = reinterpret_cast<const Byte*>( otherUInt64Ptr );

                if ( thisRemainingBytes )
                {
                    const Byte* thisEndPtr = thisPtr + thisRemainingBytes;
                    while ( thisPtr < thisEndPtr )
                    {
                        *thisPtr |= *otherPtr;
                        thisPtr++;
                        otherPtr++;
                    }
                }

                const Byte* otherEndPtr = reinterpret_cast<const Byte*>( other.data( ) ) + ( sizeof( BitVector<VectorU>::word_type ) * other.DataSize( ) );
                if ( thisRemainingBits )
                {
                    Byte thisMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( thisRemainingBits ) ) );
                    if ( thisFullByteSize == otherFullByteSize )
                    {
                        Byte otherMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( otherRemainingBits ) ) );
                        *thisPtr = ( ( *thisPtr ) & thisMask ) | (( *otherPtr ) & otherMask );
                        thisPtr++;
                        otherPtr++;
                    }
                    else
                    {
                        *thisPtr = ( ( *thisPtr ) & thisMask ) | *otherPtr;
                        thisPtr++;
                        otherPtr++;
                    }
                }
                if ( otherPtr < otherEndPtr )
                {
                    size_t remaining = otherEndPtr - otherPtr;
                    memcpy( thisPtr, otherPtr, remaining );
                }
            }
            else
            {
                UInt64* thisUInt64Ptr = reinterpret_cast<UInt64*>( data( ) );
                size_t thisFullByteSize = size_ / BitsPerByte;
                size_t thisRemainingBits = size_ % BitsPerByte;
                size_t otherFullByteSize = otherSize / BitsPerByte;
                size_t otherRemainingBits = otherSize % BitsPerByte;
                size_t otherFullUInt64Size = otherFullByteSize / sizeof( UInt64 );
                size_t otherRemainingBytes = otherFullByteSize % sizeof( UInt64 );
                const UInt64* otherUInt64EndPtr = otherUInt64Ptr + otherFullUInt64Size;

                while ( otherUInt64Ptr < otherUInt64EndPtr )
                {
                    *thisUInt64Ptr |= *otherUInt64Ptr;
                    thisUInt64Ptr++;
                    otherUInt64Ptr++;
                }
                Byte* thisPtr = reinterpret_cast<Byte*>( thisUInt64Ptr );
                const Byte* otherPtr = reinterpret_cast<const Byte*>( otherUInt64Ptr );

                if ( otherRemainingBytes )
                {
                    const Byte* otherEndPtr = otherPtr + otherRemainingBytes;
                    while ( otherPtr < otherEndPtr )
                    {
                        *thisPtr |= *otherPtr;
                        thisPtr++;
                        otherPtr++;
                    }
                }
                if ( otherRemainingBits )
                {
                    Byte mask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( otherRemainingBits ) ) );
                    *thisPtr |= ( *otherPtr ) & mask;
                    thisPtr++;
                    otherPtr++;
                }
            }
        }

        template<typename VectorU>
        BitVector& operator |= ( const BitVector<VectorU>& other )
        {
            Or( other );
            return *this;
        }

        template<typename VectorU>
        void Xor( const BitVector<VectorU>& other )
        {
            size_t otherSize = other.size( );

            const UInt64* otherUInt64Ptr = reinterpret_cast<const UInt64*>( other.data( ) );

            if ( otherSize > size_ )
            {
                size_t thisSize = size_;
                resize( otherSize );
                UInt64* thisUInt64Ptr = reinterpret_cast<UInt64*>( data( ) );
                size_t thisFullByteSize = thisSize / BitsPerByte;
                size_t thisRemainingBits = thisSize % BitsPerByte;
                size_t thisFullUInt64Size = thisFullByteSize / sizeof( UInt64 );
                size_t thisRemainingBytes = thisFullByteSize % sizeof( UInt64 );
                const UInt64* thisUInt64EndPtr = thisUInt64Ptr + thisFullUInt64Size;
                size_t otherFullByteSize = otherSize / BitsPerByte;
                size_t otherRemainingBits = otherSize % BitsPerByte;

                while ( thisUInt64Ptr < thisUInt64EndPtr )
                {
                    *thisUInt64Ptr ^= *otherUInt64Ptr;
                    thisUInt64Ptr++;
                    otherUInt64Ptr++;
                }
                Byte* thisPtr = reinterpret_cast<Byte*>( thisUInt64Ptr );
                const Byte* otherPtr = reinterpret_cast<const Byte*>( otherUInt64Ptr );

                if ( thisRemainingBytes )
                {
                    const Byte* thisEndPtr = thisPtr + thisRemainingBytes;
                    while ( thisPtr < thisEndPtr )
                    {
                        *thisPtr ^= *otherPtr;
                        thisPtr++;
                        otherPtr++;
                    }
                }

                const Byte* otherEndPtr = reinterpret_cast<const Byte*>( other.data( ) ) + ( sizeof( BitVector<VectorU>::word_type ) * other.DataSize( ) );
                if ( thisRemainingBits )
                {
                    Byte thisMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( thisRemainingBits ) ) );
                    if ( thisFullByteSize == otherFullByteSize )
                    {
                        Byte otherMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( otherRemainingBits ) ) );
                        *thisPtr = ( ( *thisPtr ) & thisMask ) ^ ( ( *otherPtr ) & otherMask );
                        thisPtr++;
                        otherPtr++;
                    }
                    else
                    {
                        *thisPtr = ( ( *thisPtr ) & thisMask ) ^ *otherPtr;
                        thisPtr++;
                        otherPtr++;
                    }
                }
                if ( otherPtr < otherEndPtr )
                {
                    size_t remaining = otherEndPtr - otherPtr;
                    memcpy( thisPtr, otherPtr, remaining );
                }
            }
            else
            {
                UInt64* thisUInt64Ptr = reinterpret_cast<UInt64*>( data( ) );
                size_t thisFullByteSize = size_ / BitsPerByte;
                size_t thisRemainingBits = size_ % BitsPerByte;
                size_t otherFullByteSize = otherSize / BitsPerByte;
                size_t otherRemainingBits = otherSize % BitsPerByte;
                size_t otherFullUInt64Size = otherFullByteSize / sizeof( UInt64 );
                size_t otherRemainingBytes = otherFullByteSize % sizeof( UInt64 );
                const UInt64* otherUInt64EndPtr = otherUInt64Ptr + otherFullUInt64Size;

                while ( otherUInt64Ptr < otherUInt64EndPtr )
                {
                    *thisUInt64Ptr ^= *otherUInt64Ptr;
                    thisUInt64Ptr++;
                    otherUInt64Ptr++;
                }
                Byte* thisPtr = reinterpret_cast<Byte*>( thisUInt64Ptr );
                const Byte* otherPtr = reinterpret_cast<const Byte*>( otherUInt64Ptr );

                if ( otherRemainingBytes )
                {
                    const Byte* otherEndPtr = otherPtr + otherRemainingBytes;
                    while ( otherPtr < otherEndPtr )
                    {
                        *thisPtr ^= *otherPtr;
                        thisPtr++;
                        otherPtr++;
                    }
                }
                if ( otherRemainingBits )
                {
                    Byte mask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( otherRemainingBits ) ) );
                    *thisPtr ^= ( *otherPtr ) & mask;
                    thisPtr++;
                    otherPtr++;
                }
            }
        }

        template<typename VectorU>
        BitVector& operator ^= ( const BitVector<VectorU>& other )
        {
            Xor( other );
            return *this;
        }

    };



    template<typename VectorT, typename VectorU>
    inline typename Core::Internal::BitVectorLogicalResult<BitVector<VectorT>, BitVector<VectorU>>::type operator & ( const BitVector<VectorT>& lhs, const BitVector<VectorU>& rhs )
    {
        using ResultType = typename Core::Internal::BitVectorLogicalResult<BitVector<VectorT>, BitVector<VectorU>>::type;
        size_t lhsSize = lhs.size( );
        size_t rhsSize = rhs.size( );
        size_t maxSize = std::max( lhsSize, rhsSize );
        size_t minSize = std::min( lhsSize, rhsSize );
        const Byte* minDataPtr = lhsSize <= rhsSize ? reinterpret_cast<const Byte*>( lhs.data( ) ) : reinterpret_cast<const Byte*>( rhs.data( ) );
        const Byte* maxDataPtr = lhsSize > rhsSize ? reinterpret_cast<const Byte*>( lhs.data( ) ) : reinterpret_cast<const Byte*>( rhs.data( ) );
        ResultType result;
        result.resize( maxSize );
        Byte* resultDataPtr = reinterpret_cast<Byte*>( result.data( ) );
        size_t minByteSize = minSize / CHAR_BIT;
        size_t remainingMinBits = minSize % CHAR_BIT;
        size_t minUInt64Size = minByteSize / sizeof( UInt64 );
        size_t remainingMinBytes = minByteSize % sizeof( UInt64 );

        const UInt64* minUInt64DataPtr = reinterpret_cast<const UInt64*>( minDataPtr );
        const UInt64* minUInt64DataEndPtr = minUInt64DataPtr + minUInt64Size;
        const UInt64* maxUInt64DataPtr = reinterpret_cast<const UInt64*>( maxDataPtr );
        UInt64* resultUInt64DataPtr = reinterpret_cast<UInt64*>( resultDataPtr );
        while ( minUInt64DataPtr < minUInt64DataEndPtr )
        {
            *resultUInt64DataPtr = *minUInt64DataPtr & *maxUInt64DataPtr;
            minUInt64DataPtr++;
            maxUInt64DataPtr++;
            resultUInt64DataPtr++;
        }
        minDataPtr = reinterpret_cast<const Byte*>( minUInt64DataPtr );
        maxDataPtr = reinterpret_cast<const Byte*>( maxUInt64DataPtr );
        resultDataPtr = reinterpret_cast<Byte*>( resultUInt64DataPtr );
        const Byte* minDataEndPtr = minDataPtr + remainingMinBytes;
        while ( minDataPtr < minDataEndPtr )
        {
            *resultDataPtr = *minDataPtr & *maxDataPtr;
            minDataPtr++;
            maxDataPtr++;
            resultDataPtr++;
        }
        if ( remainingMinBits )
        {
            auto mask = static_cast<Byte>(CreateBitMask32( static_cast<UInt32>( remainingMinBits ) ));
            *resultDataPtr = ( *minDataPtr & *maxDataPtr ) & mask;
        }
        return result;
    }

    template<typename VectorT, typename VectorU>
    inline typename Core::Internal::BitVectorLogicalResult<BitVector<VectorT>, BitVector<VectorU>>::type operator | ( const BitVector<VectorT>& lhs, const BitVector<VectorU>& rhs )
    {
        using ResultType = typename Core::Internal::BitVectorLogicalResult<BitVector<VectorT>, BitVector<VectorU>>::type;
        size_t lhsSize = lhs.size( );
        size_t rhsSize = rhs.size( );
        size_t maxSize = std::max( lhsSize, rhsSize );
        size_t minSize = std::min( lhsSize, rhsSize );
        const Byte* minDataPtr = lhsSize <= rhsSize ? reinterpret_cast<const Byte*>( lhs.data( ) ) : reinterpret_cast<const Byte*>( rhs.data( ) );
        const Byte* maxDataPtr = lhsSize > rhsSize ? reinterpret_cast<const Byte*>( lhs.data( ) ) : reinterpret_cast<const Byte*>( rhs.data( ) );
        ResultType result;
        result.resize( maxSize );
        Byte* resultDataPtr = reinterpret_cast<Byte*>( result.data( ) );
        size_t minByteSize = minSize / CHAR_BIT;
        size_t remainingMinBits = minSize % CHAR_BIT;
        size_t minUInt64Size = minByteSize / sizeof( UInt64 );
        size_t remainingMinBytes = minByteSize % sizeof( UInt64 );

        size_t maxByteSize = maxSize / CHAR_BIT;
        size_t remainingMaxBits = maxSize % CHAR_BIT;
        const Byte* maxDataEndPtr = maxDataPtr + maxByteSize;

        const UInt64* minUInt64DataPtr = reinterpret_cast<const UInt64*>( minDataPtr );
        const UInt64* minUInt64DataEndPtr = minUInt64DataPtr + minUInt64Size;
        const UInt64* maxUInt64DataPtr = reinterpret_cast<const UInt64*>( maxDataPtr );
        UInt64* resultUInt64DataPtr = reinterpret_cast<UInt64*>( resultDataPtr );
        while ( minUInt64DataPtr < minUInt64DataEndPtr )
        {
            *resultUInt64DataPtr = *minUInt64DataPtr | *maxUInt64DataPtr;
            minUInt64DataPtr++;
            maxUInt64DataPtr++;
            resultUInt64DataPtr++;
        }
        minDataPtr = reinterpret_cast<const Byte*>( minUInt64DataPtr );
        maxDataPtr = reinterpret_cast<const Byte*>( maxUInt64DataPtr );
        resultDataPtr = reinterpret_cast<Byte*>( resultUInt64DataPtr );
        const Byte* minDataEndPtr = minDataPtr + remainingMinBytes;
        while ( minDataPtr < minDataEndPtr )
        {
            *resultDataPtr = *minDataPtr | *maxDataPtr;
            minDataPtr++;
            maxDataPtr++;
            resultDataPtr++;
        }
        if ( remainingMinBits )
        {
            if ( maxByteSize != minByteSize )
            {
                auto minMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( remainingMinBits ) ) );
                *resultDataPtr = ( ( *minDataPtr & minMask ) | *maxDataPtr );
                maxDataPtr++;
                resultDataPtr++;
            }
            else
            {
                auto minMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( remainingMinBits ) ) );
                auto maxMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( remainingMaxBits ) ) );
                *resultDataPtr = ( (* minDataPtr & minMask ) | ( * maxDataPtr & maxMask ) );
                maxDataPtr++;
                resultDataPtr++;
            }
        }
        memcpy( resultDataPtr, maxDataPtr, remainingMaxBits ? ( maxDataEndPtr - maxDataPtr ) + 1 : maxDataEndPtr - maxDataPtr );

        return result;
    }


    template<typename VectorT, typename VectorU>
    inline typename Core::Internal::BitVectorLogicalResult<BitVector<VectorT>, BitVector<VectorU>>::type operator ^ ( const BitVector<VectorT>& lhs, const BitVector<VectorU>& rhs )
    {
        using ResultType = typename Core::Internal::BitVectorLogicalResult<BitVector<VectorT>, BitVector<VectorU>>::type;
        size_t lhsSize = lhs.size( );
        size_t rhsSize = rhs.size( );
        size_t maxSize = std::max( lhsSize, rhsSize );
        size_t minSize = std::min( lhsSize, rhsSize );
        const Byte* minDataPtr = lhsSize <= rhsSize ? reinterpret_cast<const Byte*>( lhs.data( ) ) : reinterpret_cast<const Byte*>( rhs.data( ) );
        const Byte* maxDataPtr = lhsSize > rhsSize ? reinterpret_cast<const Byte*>( lhs.data( ) ) : reinterpret_cast<const Byte*>( rhs.data( ) );
        ResultType result;
        result.resize( maxSize );
        Byte* resultDataPtr = reinterpret_cast<Byte*>( result.data( ) );
        size_t minByteSize = minSize / CHAR_BIT;
        size_t remainingMinBits = minSize % CHAR_BIT;
        size_t minUInt64Size = minByteSize / sizeof( UInt64 );
        size_t remainingMinBytes = minByteSize % sizeof( UInt64 );

        size_t maxByteSize = maxSize / CHAR_BIT;
        size_t remainingMaxBits = maxSize % CHAR_BIT;
        const Byte* maxDataEndPtr = maxDataPtr + maxByteSize;

        const UInt64* minUInt64DataPtr = reinterpret_cast<const UInt64*>( minDataPtr );
        const UInt64* minUInt64DataEndPtr = minUInt64DataPtr + minUInt64Size;
        const UInt64* maxUInt64DataPtr = reinterpret_cast<const UInt64*>( maxDataPtr );
        UInt64* resultUInt64DataPtr = reinterpret_cast<UInt64*>( resultDataPtr );
        while ( minUInt64DataPtr < minUInt64DataEndPtr )
        {
            *resultUInt64DataPtr = *minUInt64DataPtr ^ *maxUInt64DataPtr;
            minUInt64DataPtr++;
            maxUInt64DataPtr++;
            resultUInt64DataPtr++;
        }
        minDataPtr = reinterpret_cast<const Byte*>( minUInt64DataPtr );
        maxDataPtr = reinterpret_cast<const Byte*>( maxUInt64DataPtr );
        resultDataPtr = reinterpret_cast<Byte*>( resultUInt64DataPtr );
        const Byte* minDataEndPtr = minDataPtr + remainingMinBytes;
        while ( minDataPtr < minDataEndPtr )
        {
            *resultDataPtr = *minDataPtr ^ *maxDataPtr;
            minDataPtr++;
            maxDataPtr++;
            resultDataPtr++;
        }
        if ( remainingMinBits )
        {
            if ( maxByteSize != minByteSize )
            {
                auto minMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( remainingMinBits ) ) );
                *resultDataPtr = ( ( *minDataPtr & minMask ) ^ *maxDataPtr );
                maxDataPtr++;
                resultDataPtr++;
            }
            else
            {
                auto minMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( remainingMinBits ) ) );
                auto maxMask = static_cast<Byte>( CreateBitMask32( static_cast<UInt32>( remainingMaxBits ) ) );
                *resultDataPtr = ( ( *minDataPtr & minMask ) ^ ( *maxDataPtr & maxMask ) );
                maxDataPtr++;
                resultDataPtr++;
            }
        }
        memcpy( resultDataPtr, maxDataPtr, remainingMaxBits ? ( maxDataEndPtr - maxDataPtr ) + 1 : maxDataEndPtr - maxDataPtr );

        return result;
    }
    


}


#endif
