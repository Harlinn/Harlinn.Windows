#pragma once
#ifndef __HCCGUID_H__
#define __HCCGUID_H__

#include <HCCLib.h>

namespace Harlinn::Common::Core
{
    class Guid;
    template<typename T>
    concept GuidType = std::is_same_v<GUID, T> || std::is_same_v<Guid, T> || std::is_same_v<boost::uuids::uuid, T>;

    class Guid
    {
        union DataT
        {
            GUID g_;
            struct
            {
                uint64_t hi_;
                uint64_t lo_;
            };
            constexpr DataT( ) noexcept
                : hi_(0), lo_( 0 )
            {
            }

            constexpr DataT( const GUID& g ) noexcept
                : g_( g )
            {
            }

            DataT( const boost::uuids::uuid& g ) noexcept
                : g_( *reinterpret_cast<const GUID*>(&g) )
            {
            }

            constexpr DataT( uint64_t hi, uint64_t lo ) noexcept
                : hi_( hi ), lo_( lo )
            { }
            constexpr DataT( UInt32 d1, UInt16 d2, UInt16 d3, Byte d4, Byte d5, Byte d6, Byte d7, Byte d8, Byte d9, Byte d10, Byte d11 ) noexcept
                : g_{ d1, d2, d3, {d4, d5, d6, d7, d8, d9, d10, d11 } }
            {
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
            : data_( reinterpret_cast<const GUID&>(other) )
        {
        }

        Guid( const boost::uuids::uuid& other ) noexcept
            : data_( other )
        {
        }

        constexpr Guid( uint64_t hi, uint64_t lo ) noexcept
            : data_( hi, lo )
        {
        }

        constexpr Guid( UInt32 d1, UInt16 d2, UInt16 d3, Byte d4, Byte d5, Byte d6, Byte d7, Byte d8, Byte d9, Byte d10, Byte d11 ) noexcept
            : data_( d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11 )
        {
            
        }

        Guid Next( ) const noexcept
        {
            if ( data_.lo_ != MAXUINT64 )
            {
                return Guid( data_.hi_, data_.lo_ + 1 );
            }
            else
            {
                return Guid( data_.hi_ + 1, 0 );
            }
        }


        constexpr int CompareTo( const Guid& other ) const noexcept
        {
            if ( std::is_constant_evaluated( ) )
            {
                auto self = std::bit_cast<std::array<Byte, 16>, GUID>( data_.g_ );
                auto othr = std::bit_cast<std::array<Byte, 16>, GUID>( other.data_.g_ );
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

        bool empty( ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            return _mm_test_all_zeros( self, self ) != 0;
        }

        bool IsEmpty( ) const noexcept
        {
            return empty( );
        }

        explicit operator bool( ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            return _mm_test_all_zeros( self, self ) == 0;
        }

        HCC_EXPORT explicit Guid( const char* uuid );
        HCC_EXPORT explicit Guid( const wchar_t* uuid );
        HCC_EXPORT explicit Guid( const std::string& uuid );
        HCC_EXPORT explicit Guid( const std::wstring& uuid );

        HCC_EXPORT static bool TryParse( const char* uuid, Guid& result );
        HCC_EXPORT static bool TryParse( const wchar_t* uuid, Guid& result );
        HCC_EXPORT static bool TryParse( const std::string& uuid, Guid& result );
        HCC_EXPORT static bool TryParse( const std::wstring& uuid, Guid& result );

        HCC_EXPORT static Guid Parse( const char* uuid );
        HCC_EXPORT static Guid Parse( const wchar_t* uuid );
        HCC_EXPORT static Guid Parse( const std::string& uuid );
        HCC_EXPORT static Guid Parse( const std::wstring& uuid );

        HCC_EXPORT std::wstring ToString( ) const;
        HCC_EXPORT std::string ToAnsiString( ) const;

        HCC_EXPORT const GUID& AsGuid( ) const
        {
            return data_.g_;
        }


        friend std::ostream& operator << ( std::ostream& stream, const Guid& guid )
        {
            auto str = guid.ToAnsiString( );
            stream << str;
            return stream;
        }


        HCC_EXPORT static Guid NewGuid( );

        static Guid New( )
        {
            return NewGuid( );
        }


        constexpr uint64_t Hi( ) const noexcept
        {
            return data_.hi_;
        }
        constexpr uint64_t Lo( ) const noexcept
        {
            return data_.lo_;
        }

        const std::array<Byte, 16>& ToArray( ) const
        {
            return reinterpret_cast<const std::array<Byte, 16>&>( data_ );
        }
        const std::array<Byte, 16>& ToBytes( ) const
        {
            return ToArray( );
        }


        constexpr operator const GUID& ( ) const noexcept
        {
            return data_.g_;
        }

        constexpr const GUID& Value( ) const noexcept
        {
            return data_.g_;
        }
        constexpr GUID& Value( ) noexcept
        {
            return data_.g_;
        }


        template<GuidType T>
        bool operator == ( const T& other ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            __m128i othr = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &other ) );
            __m128i mask = _mm_xor_si128( self, othr );
            return _mm_test_all_zeros( mask, mask ) != 0;
        }

        template<GuidType T>
        bool operator != ( const T& other ) const noexcept
        {
            __m128i self = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &data_ ) );
            __m128i othr = _mm_lddqu_si128( reinterpret_cast<const __m128i*>( &other ) );
            __m128i mask = _mm_xor_si128( self, othr );
            return _mm_test_all_zeros( mask, mask ) == 0;
        }

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
    template<> struct hash<Harlinn::Common::Core::Guid>
    {
        constexpr std::size_t operator()( const Harlinn::Common::Core::Guid& guid ) const noexcept
        {
            return guid.Lo( );
        }
    };
}


#endif