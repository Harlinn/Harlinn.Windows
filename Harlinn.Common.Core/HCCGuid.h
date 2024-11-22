#pragma once
#ifndef __HCCGUID_H__
#define __HCCGUID_H__
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

#include <HCCLib.h>

namespace Harlinn::Common::Core
{
    class Guid;
    template<typename T>
    concept GuidType = std::is_same_v<GUID, T> || std::is_same_v<Guid, T> || std::is_same_v<boost::uuids::uuid, T>;
    /// <summary>
    /// Represents a globally unique identifier (GUID).
    /// </summary>
    /// <remarks>
    /// A GUID is a 128-bit integer (16 bytes) that can be used across all computers and networks wherever 
    /// a unique identifier is required. Such an identifier has a very low probability of being duplicated.
    /// </remarks>
    class Guid
    {
    public:
        using Bytes = std::array<Byte, 16>;
    private:
        struct DataT : GUID
        {
            using Base = GUID;
            constexpr DataT( ) noexcept
                : Base{}
            {
            }

            constexpr DataT( const GUID& g ) noexcept
                : Base( g )
            {
            }

            constexpr DataT( const boost::uuids::uuid& g ) noexcept
                : Base( std::bit_cast<GUID>(g) )
            {
            }

            constexpr DataT( uint64_t lo, uint64_t hi ) noexcept
                : Base{ lo & 0XFFFFFFFF, ( ( lo >> 32 ) & 0XFFFF ), ( ( lo >> 48 ) & 0XFFFF ), 
                    {( hi & 0xFF ), 
                    ( ( hi >> 8 ) & 0xFF ), 
                    ( ( hi >> 16 ) & 0xFF ), 
                    ( ( hi >> 24 ) & 0xFF ), 
                    ( ( hi >> 32 ) & 0xFF ), 
                    ( ( hi >> 40 ) & 0xFF ), 
                    ( ( hi >> 48 ) & 0xFF ), 
                    ( ( hi >> 56 ) & 0xFF )} }
            {
            }

            constexpr DataT( const uint64_t values[ 2 ] ) noexcept
                : DataT( values[ 0 ], values[ 1 ] )
            { }

            constexpr DataT( UInt32 d1, UInt16 d2, UInt16 d3, Byte d4, Byte d5, Byte d6, Byte d7, Byte d8, Byte d9, Byte d10, Byte d11 ) noexcept
                : Base{ d1, d2, d3, {d4, d5, d6, d7, d8, d9, d10, d11 } }
            {
            }

            constexpr DataT( const Bytes& bytes ) noexcept
                : Base{ std::bit_cast<GUID>( bytes )}
            {
            }

            constexpr DataT( Byte b1, Byte b2, Byte b3, Byte b4, Byte b5, Byte b6, Byte b7, Byte b8, Byte b9, Byte b10, Byte b11, Byte b12, Byte b13, Byte b14, Byte b15, Byte b16 ) noexcept
                : DataT{ Bytes{b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16} }
            {
            }

            constexpr DataT( const Byte values[ 16 ] ) noexcept
                : DataT( values[ 0 ], values[ 1 ], values[ 2 ], values[ 3 ], values[ 4 ], values[ 5 ], values[ 6 ], values[ 7 ], values[ 8 ], values[ 9 ], values[ 10 ], values[ 11 ], values[ 12 ], values[ 13 ], values[ 14 ], values[ 15 ] )
            {
            }



            constexpr UInt64 Lo( ) const
            {
                return static_cast< UInt64 >( Base::Data1 ) | ( static_cast< UInt64 >( Base::Data2 ) << 32 ) | ( static_cast< UInt64 >( Base::Data3 ) << 48 );
            }

            constexpr UInt64 Hi( ) const
            {
                return std::bit_cast< UInt64 >( Base::Data4 );
            }
        };
        
        DataT data_;
    public:
        constexpr Guid() noexcept
            : data_()
        { }

        constexpr Guid( const GUID& other ) noexcept
            : data_( other )
        {
        }

        constexpr Guid( const std::array<Byte,16>& other ) noexcept
            : data_( other )
        {
        }

        constexpr Guid( const boost::uuids::uuid& other ) noexcept
            : data_( other )
        {
        }

        constexpr Guid( uint64_t lo, uint64_t hi ) noexcept
            : data_( lo, hi )
        {
        }

        constexpr Guid( const uint64_t values[ 2 ] ) noexcept
            : data_( values )
        {
        }



        constexpr Guid( UInt32 d1, UInt16 d2, UInt16 d3, Byte d4, Byte d5, Byte d6, Byte d7, Byte d8, Byte d9, Byte d10, Byte d11 ) noexcept
            : data_( d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11 )
        {
            
        }

        constexpr Guid( Byte b1, Byte b2, Byte b3, Byte b4, Byte b5, Byte b6, Byte b7, Byte b8, Byte b9, Byte b10, Byte b11, Byte b12, Byte b13, Byte b14, Byte b15, Byte b16 ) noexcept
            : data_( b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16 )
        {

        }

        constexpr Guid( const Byte values[ 16 ] ) noexcept
            : data_( values )
        {
        }


        /// <summary>
        /// <para>
        /// Creates a new Guid by treating the current value as a
        /// 128-bit unsigned integer that gets incremented by 1.
        /// </para>
        /// <para>
        /// This can be useful when writing tests that are easier 
        /// to implement with predictable values for the Guids.
        /// </para>
        /// </summary>
        /// <returns>
        /// The 'next' Guid value.
        /// </returns>
        constexpr Guid Next( ) const noexcept
        {
            if ( data_.Hi() != MAXUINT64 )
            {
                return Guid( data_.Lo( ), data_.Hi( ) + 1 );
            }
            else
            {
                return Guid( data_.Lo( ) + 1, 0 );
            }
        }

        /// <summary>
        /// Compares this Guid with another Guid.
        /// </summary>
        /// <param name="other">
        /// 
        /// </param>
        /// <returns>
        /// <list>
        ///   <item><c>result &gt; 0</c> when this Guid is greater than the other Guid</item>
        ///   <item><c>result == 0</c> when this Guid is equal to the other Guid</item>
        ///   <item><c>result &lt; 0</c> when this Guid is less than the other Guid</item>
        /// </list>
        /// </returns>
        constexpr int CompareTo( const Guid& other ) const noexcept
        {
            if ( std::is_constant_evaluated( ) )
            {
                auto self = std::bit_cast<std::array<Byte, 16>, GUID>( data_ );
                auto othr = std::bit_cast<std::array<Byte, 16>, GUID>( other.data_ );
                size_t i = 0;
                while ( i < self.size() )
                {
                    if ( self[i] != othr[i] )
                    {
                        return static_cast<int>(self[i]) - static_cast<int>( othr[i] );
                    }
                    ++i;
                }
                return 0;
            }
            else
            {
                __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
                __m128i othr = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &other ) );

                const __m128i signsMask = _mm_xor_si128( self, othr );

                __m128i compareResult = _mm_cmpgt_epi8( othr, self );
                __m128i reverseCompareResult = _mm_cmpgt_epi8( self, othr );

                // Flip sign-bits
                compareResult = _mm_xor_si128( signsMask, compareResult );
                reverseCompareResult = _mm_xor_si128( signsMask, reverseCompareResult );

                UInt32 cmp = static_cast<UInt32>( _mm_movemask_epi8( compareResult ) );
                UInt32 rcmp = static_cast<UInt32>( _mm_movemask_epi8( reverseCompareResult ) );

                cmp = ( cmp - 1u ) ^ cmp;
                rcmp = ( rcmp - 1u ) ^ rcmp;

                return cmp < rcmp ? -1 : cmp == rcmp ? 0 : 1;
            }
        }

        /// <summary>
        /// Test if this Guid is empty, meaning every byte of the Guid is 0.
        /// </summary>
        /// <returns>
        /// true if the Guid is empty.
        /// </returns>
        bool empty( ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            return _mm_test_all_zeros( self, self ) != 0;
        }

        /// <summary>
        /// Test if this Guid is empty, meaning every byte of the Guid is 0.
        /// </summary>
        /// <returns>
        /// true if the Guid is empty.
        /// </returns>
        bool IsEmpty( ) const noexcept
        {
            return empty( );
        }

        /// <summary>
        /// Test if the Guid is not empty.
        /// </summary>
        explicit operator bool( ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            return _mm_test_all_zeros( self, self ) == 0;
        }
        /// <summary>
        /// Constructs a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A zero terminated c-style character string.
        /// </param>
        HCC_EXPORT explicit Guid( const char* uuid );
        /// <summary>
        /// Constructs a Guid from its string representation.
        /// The string representation must match L"{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A zero terminated c-style wide character string.
        /// </param>
        HCC_EXPORT explicit Guid( const wchar_t* uuid );
        /// <summary>
        /// Constructs a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A const reference to an AnsiString.
        /// </param>
        HCC_EXPORT explicit Guid( const AnsiString& uuid );
        /// <summary>
        /// Constructs a Guid from its string representation.
        /// The string representation must match L"{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A const reference to a WideString.
        /// </param>
        HCC_EXPORT explicit Guid( const WideString& uuid );

        /// <summary>
        /// Tries to parse a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A zero terminated c-style character string.
        /// </param>
        /// <returns>
        /// true if the successfully parsed a Guid, otherwise false.
        /// </returns>
        HCC_EXPORT static bool TryParse( const char* uuid, Guid& result );
        /// <summary>
        /// Tries to parse a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A zero terminated c-style wide character string.
        /// </param>
        /// <returns>
        /// true if the successfully parsed a Guid, otherwise false.
        /// </returns>
        HCC_EXPORT static bool TryParse( const wchar_t* uuid, Guid& result ) noexcept;
        /// <summary>
        /// Tries to parse a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A const reference to an AnsiString.
        /// </param>
        /// <returns>
        /// true if the successfully parsed a Guid, otherwise false.
        /// </returns>
        HCC_EXPORT static bool TryParse( const AnsiString& uuid, Guid& result );
        /// <summary>
        /// Tries to parse a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A const reference to a WideString.
        /// </param>
        /// <returns>
        /// true if the successfully parsed a Guid, otherwise false.
        /// </returns>
        HCC_EXPORT static bool TryParse( const WideString& uuid, Guid& result ) noexcept;

        /// <summary>
        /// Parse a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A zero terminated c-style character string.
        /// </param>
        /// <returns>
        /// The parsed Guid.
        /// </returns>
        HCC_EXPORT static Guid Parse( const char* uuid );
        /// <summary>
        /// Parse a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A zero terminated c-style wide character string.
        /// </param>
        /// <returns>
        /// The parsed Guid.
        /// </returns>
        HCC_EXPORT static Guid Parse( const wchar_t* uuid );
        /// <summary>
        /// Parse a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A const reference to an AnsiString.
        /// </param>
        /// <returns>
        /// The parsed Guid.
        /// </returns>
        HCC_EXPORT static Guid Parse( const AnsiString& uuid );
        /// <summary>
        /// Parse a Guid from its string representation.
        /// The string representation must match "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}"
        /// </summary>
        /// <param name="uuid">
        /// A const reference to a WideString.
        /// </param>
        /// <returns>
        /// The parsed Guid.
        /// </returns>
        HCC_EXPORT static Guid Parse( const WideString& uuid );

        template<SimpleStringLike StringT>
            requires ( std::is_same_v<StringT,AnsiString> == false && std::is_same_v<StringT, WideString> == false )
        static Guid Parse( const StringT& uuid )
        {
            return Parse( uuid.c_str( ) );
        }

        HCC_EXPORT WideString ToWideString( ) const;
        HCC_EXPORT AnsiString ToAnsiString( ) const;

        HCC_EXPORT const GUID& AsGuid( ) const
        {
            return data_;
        }

        HCC_EXPORT static bool IsGuid( const WideString& uuid );

        HCC_EXPORT friend std::ostream& operator << ( std::ostream& stream, const Guid& guid );

        /// <summary>
        /// Creates a new Guid value.
        /// </summary>
        /// <returns>
        /// The Guid containing the new Guid value.
        /// </returns>
        HCC_EXPORT static Guid NewGuid( );

        /// <summary>
        /// Creates a new Guid value.
        /// </summary>
        /// <returns>
        /// The Guid containing the new Guid value.
        /// </returns>
        static Guid New( )
        {
            return NewGuid( );
        }

        /// <summary>
        /// Retrieves the 64 most significant bits of this Guid as an unsigned 64-bit integer.
        /// </summary>
        /// <returns>
        /// the 64 most significant bits of this Guid.
        /// </returns>
        constexpr uint64_t Hi( ) const noexcept
        {
            return data_.Hi( );
        }
        /// <summary>
        /// Retrieves the 64 least significant bits of this Guid as an unsigned 64-bit integer.
        /// </summary>
        /// <returns>
        /// the 64 least significant bits of this Guid.
        /// </returns>

        constexpr uint64_t Lo( ) const noexcept
        {
            return data_.Lo( );
        }

        /// <summary>
        /// Retrieves a const reference to the data of this Guid as a std::array&lt;Byte, 16&gt;.
        /// </summary>
        /// <returns>
        /// A const reference to the data of this Guid as a std::array&lt;Byte, 16&gt;.
        /// </returns>
        const std::array<Byte, 16>& ToArray( ) const
        {
            return reinterpret_cast<const std::array<Byte, 16>&>( data_ );
        }
        
        /// <summary>
        /// Retrieves a const reference to the data of this Guid as a std::array&lt;Byte, 16&gt;.
        /// </summary>
        /// <returns>
        /// A const reference to the data of this Guid as a std::array&lt;Byte, 16&gt;.
        /// </returns>
        const std::array<Byte, 16>& ToBytes( ) const
        {
            return ToArray( );
        }

        /// <summary>
        /// Retrieves a const reference to the data of this Guid as a GUID.
        /// </summary>
        constexpr operator const GUID& ( ) const noexcept
        {
            return data_;
        }

        /// <summary>
        /// Retrieves a const reference to the data of this Guid as a GUID.
        /// </summary>
        /// <returns>
        /// A const reference to the data of this Guid as a GUID.
        /// </returns>
        constexpr const GUID& Value( ) const noexcept
        {
            return data_;
        }
        /// <summary>
        /// Retrieves a reference to the data of this Guid as a GUID.
        /// </summary>
        /// <returns>
        /// A reference to the data of this Guid as a GUID.
        /// </returns>
        constexpr GUID& Value( ) noexcept
        {
            return data_;
        }

        /// <summary>
        /// Tests if this Guid is equal to another Guid, GUID or boost::uuids::uuid.
        /// </summary>
        /// <typeparam name="T">
        /// Must be Guid, GUID or boost::uuids::uuid.
        /// </typeparam>
        /// <param name="other">
        /// The other guid. 
        /// </param>
        /// <returns>
        /// true if this Guid is equal to other, otherwise false.
        /// </returns>
        template<GuidType T>
        bool operator == ( const T& other ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast< const __m128i* >( &data_ ) );
            __m128i othr = _mm_lddqu_si128( reinterpret_cast< const __m128i* >( &other ) );
            __m128i mask = _mm_xor_si128( self, othr );
            return _mm_test_all_zeros( mask, mask ) != 0;
        }

        /// <summary>
        /// Tests if this Guid is not equal to another Guid, GUID or boost::uuids::uuid.
        /// </summary>
        /// <typeparam name="T">
        /// Must be Guid, GUID or boost::uuids::uuid.
        /// </typeparam>
        /// <param name="other">
        /// The other guid. 
        /// </param>
        /// <returns>
        /// true if this Guid is not equal to other, otherwise false.
        /// </returns>
        template<GuidType T>
        bool operator != ( const T& other ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            __m128i othr = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &other ) );
            __m128i mask = _mm_xor_si128( self, othr );
            return _mm_test_all_zeros( mask, mask ) == 0;
        }

        /// <summary>
        /// Tests if this Guid is less or equal to another Guid, GUID or boost::uuids::uuid.
        /// </summary>
        /// <typeparam name="T">
        /// Must be Guid, GUID or boost::uuids::uuid.
        /// </typeparam>
        /// <param name="other">
        /// The other guid. 
        /// </param>
        /// <returns>
        /// true if this Guid is less or equal to other, otherwise false.
        /// </returns>
        template<GuidType T>
        constexpr bool operator <= ( const T& other ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            __m128i othr = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &other ) );

            const __m128i signsMask = _mm_xor_si128( self, othr );

            __m128i compareResult = _mm_cmpgt_epi8( othr, self );
            __m128i reverseCompareResult = _mm_cmpgt_epi8( self, othr );

            // Flip sign-bits
            compareResult = _mm_xor_si128( signsMask, compareResult );
            reverseCompareResult = _mm_xor_si128( signsMask, reverseCompareResult );

            UInt32 cmp = static_cast<UInt32>( _mm_movemask_epi8( compareResult ) );
            UInt32 rcmp = static_cast<UInt32>( _mm_movemask_epi8( reverseCompareResult ) );

            cmp = ( cmp - 1u ) ^ cmp;
            rcmp = ( rcmp - 1u ) ^ rcmp;

            return cmp <= rcmp;
        }

        /// <summary>
        /// Tests if this Guid is less than another Guid, GUID or boost::uuids::uuid.
        /// </summary>
        /// <typeparam name="T">
        /// Must be Guid, GUID or boost::uuids::uuid.
        /// </typeparam>
        /// <param name="other">
        /// The other guid. 
        /// </param>
        /// <returns>
        /// true if this Guid is less than other, otherwise false.
        /// </returns>
        template<GuidType T>
        bool operator < ( const T& other ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            __m128i othr = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &other ) );

            const __m128i signsMask = _mm_xor_si128( self, othr );

            __m128i compareResult = _mm_cmpgt_epi8( othr, self );
            __m128i reverseCompareResult = _mm_cmpgt_epi8( self, othr );

            // Flip sign-bits
            compareResult = _mm_xor_si128( signsMask, compareResult );
            reverseCompareResult = _mm_xor_si128( signsMask, reverseCompareResult );

            UInt32 cmp = static_cast<UInt32>( _mm_movemask_epi8( compareResult ) );
            UInt32 rcmp = static_cast<UInt32>( _mm_movemask_epi8( reverseCompareResult ) );

            cmp = ( cmp - 1u ) ^ cmp;
            rcmp = ( rcmp - 1u ) ^ rcmp;

            return cmp < rcmp;

        }

        /// <summary>
        /// Tests if this Guid is greater or equal to another Guid, GUID or boost::uuids::uuid.
        /// </summary>
        /// <typeparam name="T">
        /// Must be Guid, GUID or boost::uuids::uuid.
        /// </typeparam>
        /// <param name="other">
        /// The other guid. 
        /// </param>
        /// <returns>
        /// true if this Guid is greater or equal to other, otherwise false.
        /// </returns>
        template<GuidType T>
        constexpr bool operator >= ( const T& other ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            __m128i othr = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &other ) );

            const __m128i signsMask = _mm_xor_si128( self, othr );

            __m128i compareResult = _mm_cmpgt_epi8( othr, self );
            __m128i reverseCompareResult = _mm_cmpgt_epi8( self, othr );

            // Flip sign-bits
            compareResult = _mm_xor_si128( signsMask, compareResult );
            reverseCompareResult = _mm_xor_si128( signsMask, reverseCompareResult );

            UInt32 cmp = static_cast<UInt32>( _mm_movemask_epi8( compareResult ) );
            UInt32 rcmp = static_cast<UInt32>( _mm_movemask_epi8( reverseCompareResult ) );

            cmp = ( cmp - 1u ) ^ cmp;
            rcmp = ( rcmp - 1u ) ^ rcmp;

            return cmp >= rcmp;
        }

        /// <summary>
        /// Tests if this Guid is grater than another Guid, GUID or boost::uuids::uuid.
        /// </summary>
        /// <typeparam name="T">
        /// Must be Guid, GUID or boost::uuids::uuid.
        /// </typeparam>
        /// <param name="other">
        /// The other guid. 
        /// </param>
        /// <returns>
        /// true if this Guid is grater than other, otherwise false.
        /// </returns>
        template<GuidType T>
        constexpr bool operator > ( const T& other ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            __m128i othr = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &other ) );

            const __m128i signsMask = _mm_xor_si128( self, othr );

            __m128i compareResult = _mm_cmpgt_epi8( othr, self );
            __m128i reverseCompareResult = _mm_cmpgt_epi8( self, othr );

            // Flip sign-bits
            compareResult = _mm_xor_si128( signsMask, compareResult );
            reverseCompareResult = _mm_xor_si128( signsMask, reverseCompareResult );

            UInt32 cmp = static_cast<UInt32>( _mm_movemask_epi8( compareResult ) );
            UInt32 rcmp = static_cast<UInt32>( _mm_movemask_epi8( reverseCompareResult ) );

            cmp = ( cmp - 1u ) ^ cmp;
            rcmp = ( rcmp - 1u ) ^ rcmp;

            return cmp > rcmp;
        }
    };

    namespace Test
    {
        HCC_EXPORT extern GUID Ids[10000];
    }

    template<typename T>
    inline constexpr bool IsGuid = std::is_same_v<std::remove_cv_t<T>, Guid>;

    /// <summary>
    /// Implements ByteSwap for a Guid.
    /// </summary>
    /// <typeparam name="T">
    /// Must be Guid.
    /// </typeparam>
    /// <param name="guid">
    /// The Guid value.
    /// </param>
    /// <returns>
    /// A Guid with the bytes swapped for the Data1, Data2 and Data3 fields.
    /// </returns>
    template<typename T>
        requires IsGuid<T>
    inline constexpr T ByteSwap( const T& guid ) noexcept
    {
        const GUID& src = guid.Value( );
        return Guid( ByteSwap( src.Data1 ), ByteSwap( src.Data2 ), ByteSwap( src.Data3 ), src.Data4[0], src.Data4[1], src.Data4[2], src.Data4[3], src.Data4[4], src.Data4[5], src.Data4[6], src.Data4[7] );
    }


}

namespace std
{
    /// <summary>
    /// This specialization of std::hash for Harlinn::Common::Core::Guid
    /// assumes that the distribution of values for the 8 last bytes of the
    /// Guid is random enough to be used as a hash value.
    /// </summary>
    template<> struct hash<Harlinn::Common::Core::Guid>
    {
        constexpr std::size_t operator()( const Harlinn::Common::Core::Guid& guid ) const noexcept
        {
            return guid.Lo( );
        }
    };
}


#endif
