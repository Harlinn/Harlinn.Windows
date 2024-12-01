#pragma once
#ifndef __HCCSIMD_H__
#define __HCCSIMD_H__
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

//#include <HCCMath.h>
#include <HCCLib.h>
#include <zmmintrin.h>

namespace Harlinn::Common::Core::SIMD
{

    enum class BaseType
    {
        SByte,
        Byte,
        Int16,
        UInt16,
        Int32,
        UInt32,
        Int64,
        UInt64,
        Half,
        Single,
        Double
    };

    enum class DataType
    {
        // __m64, alignas(8)
        m64,
        // __m128, alignas(16)
        m128,
        // __m128i, alignas(16)
        m128i,
        // __m128d, alignas(16)
        m128d,
        // __m256, alignas(32)
        m256,
        // __m256i, alignas(32)
        m256i,
        // __m256d, alignas(32)
        m256d,
        // __m512, alignas(64)
        m512,
        // __m512i, alignas(64)
        m512i,
        // __m512d, alignas(64)
        m512d
    };

    template<DataType dt>
    struct DataTypeTraits;

    template<>
    struct DataTypeTraits<DataType::m64>
    {
        static constexpr DataType Id = DataType::m64;
        static constexpr size_t AlignAs = 8;
        static constexpr size_t Size = 8;
        using Type = __m64;
    };

    template<>
    struct DataTypeTraits<DataType::m128>
    {
        static constexpr DataType Id = DataType::m128;
        static constexpr size_t AlignAs = 16;
        static constexpr size_t Size = 16;
        using Type = __m128;
    };
    template<>
    struct DataTypeTraits<DataType::m128i>
    {
        static constexpr DataType Id = DataType::m128i;
        static constexpr size_t AlignAs = 16;
        static constexpr size_t Size = 16;
        using Type = __m128i;
    };
    template<>
    struct DataTypeTraits<DataType::m128d>
    {
        static constexpr DataType Id = DataType::m128d;
        static constexpr size_t AlignAs = 16;
        static constexpr size_t Size = 16;
        using Type = __m128d;
    };

    template<>
    struct DataTypeTraits<DataType::m256>
    {
        static constexpr DataType Id = DataType::m256;
        static constexpr size_t AlignAs = 32;
        static constexpr size_t Size = 32;
        using Type = __m256;
    };
    template<>
    struct DataTypeTraits<DataType::m256i>
    {
        static constexpr DataType Id = DataType::m256i;
        static constexpr size_t AlignAs = 32;
        static constexpr size_t Size = 32;
        using Type = __m256i;
    };
    template<>
    struct DataTypeTraits<DataType::m256d>
    {
        static constexpr DataType Id = DataType::m256d;
        static constexpr size_t AlignAs = 32;
        static constexpr size_t Size = 32;
        using Type = __m256d;
    };
    template<>
    struct DataTypeTraits<DataType::m512>
    {
        static constexpr DataType Id = DataType::m512;
        static constexpr size_t AlignAs = 64;
        static constexpr size_t Size = 64;
        using Type = __m512;
    };
    template<>
    struct DataTypeTraits<DataType::m512i>
    {
        static constexpr DataType Id = DataType::m512i;
        static constexpr size_t AlignAs = 64;
        static constexpr size_t Size = 64;
        using Type = __m512i;
    };
    template<>
    struct DataTypeTraits<DataType::m512d>
    {
        static constexpr DataType Id = DataType::m512d;
        static constexpr size_t AlignAs = 64;
        static constexpr size_t Size = 64;
        using Type = __m512d;
    };



    template<typename T, size_t N>
    struct Traits
    {
        using Type = std::remove_cvref_t<T>;
    };


    template<size_t N>
    struct Traits<char, N>
    {
        using Type = char;
    private:
        static constexpr bool UseShortSIMDType = N <= 16;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 16 : ( ( N + 31 ) & static_cast<Int64>( -32 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi8( std::bit_cast<char>( value ) );
            }
            else
            {
                return _mm256_set1_epi8( std::bit_cast<char>( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }


        /// <summary>
        /// Adds two int8 vectors.
        /// </summary>
        /// <param name="lhs">int8 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int8 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Adds packed signed 8-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 8 bits (overflow), the result is wrapped around and 
        /// the low 8 bits are written to the destination vector (that is, the carry is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi8( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi8( lhs, rhs );
            }
        }


        /// <summary>
        /// Subtracts int8 vectors.
        /// </summary>
        /// <param name="lhs">int8 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int8 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed signed 8-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 8 (overflow), the result is wrapped around 
        /// and the low 8 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi8( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi8( lhs, rhs );
            }
        }


    };
    template<size_t N>
    struct Traits<SByte, N>
    {
        using Type = SByte;
    private:
        static constexpr bool UseShortSIMDType = N <= 16;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 16 : ( ( N + 31 ) & static_cast<Int64>( -32 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi8( std::bit_cast<char>( value ) );
            }
            else
            {
                return _mm256_set1_epi8( std::bit_cast<char>( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        /// <summary>
        /// Adds two int8 vectors.
        /// </summary>
        /// <param name="lhs">int8 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int8 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds packed signed 8-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 8 bits (overflow), the result is wrapped around and 
        /// the low 8 bits are written to the destination vector (that is, the carry is ignored).
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi8( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi8( lhs, rhs );
            }
        }

        /// <summary>
        /// Subtracts int8 vectors.
        /// </summary>
        /// <param name="lhs">int8 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int8 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed signed 8-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 8 bits (overflow), the result is wrapped around 
        /// and the low 8 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi8( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi8( lhs, rhs );
            }
        }

    };
    template<size_t N>
    struct Traits<Byte, N>
    {
        using Type = Byte;
    private:
        static constexpr bool UseShortSIMDType = N <= 16;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 16 : ( ( N + 31 ) & static_cast<Int64>( -32 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi8( std::bit_cast<char>( value ) );
            }
            else
            {
                return _mm256_set1_epi8( std::bit_cast<char>( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        /// <summary>
        /// Adds two uint8 vectors.
        /// </summary>
        /// <param name="lhs">uint8 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">uint8 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds packed unsigned 8-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 8 bits (overflow), the result is wrapped around and 
        /// the low 8 bits are written to the destination vector (that is, the carry is ignored).
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi8( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi8( lhs, rhs );
            }
        }

        /// <summary>
        /// Subtracts uint8 vectors.
        /// </summary>
        /// <param name="lhs">uint8 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">uint8 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed unsigned 8-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 8 bits (overflow), the result is wrapped around 
        /// and the low 8 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi8( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi8( lhs, rhs );
            }
        }


    };
    template<size_t N>
    struct Traits<Int16, N>
    {
        using Type = Int16;
    private:
        static constexpr bool UseShortSIMDType = N <= 8;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 8 : ( ( N + 15 ) & static_cast<Int64>( -16 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi16( std::bit_cast<short>( value ) );
            }
            else
            {
                return _mm256_set1_epi16( std::bit_cast<short>( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        /// <summary>
        /// Adds two int16 vectors.
        /// </summary>
        /// <param name="lhs">int16 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int16 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds packed signed 16-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 16 bits (overflow), the result is wrapped around and 
        /// the low 16 bits are written to the destination vector (that is, the carry is ignored).
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi16( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi16( lhs, rhs );
            }
        }

        /// <summary>
        /// Subtracts int16 vectors.
        /// </summary>
        /// <param name="lhs">int16 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int16 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed signed 16-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 16 bits (overflow), the result is wrapped around 
        /// and the low 16 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi16( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi16( lhs, rhs );
            }
        }


    };
    template<size_t N>
    struct Traits<UInt16, N>
    {
        using Type = UInt16;
    private:
        static constexpr bool UseShortSIMDType = N <= 8;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 8 : ( ( N + 15 ) & static_cast<Int64>( -16 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi16( std::bit_cast<short>( value ) );
            }
            else
            {
                return _mm256_set1_epi16( std::bit_cast<short>( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        /// <summary>
        /// Adds two uint16 vectors.
        /// </summary>
        /// <param name="lhs">uint16 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">uint16 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds packed unsigned 16-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 16 bits (overflow), the result is wrapped around and 
        /// the low 16 bits are written to the destination vector (that is, the carry is ignored).
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi16( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi16( lhs, rhs );
            }
        }

        /// <summary>
        /// Subtracts uint16 vectors.
        /// </summary>
        /// <param name="lhs">uint16 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">uint16 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed unsigned 16-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 16 bits (overflow), the result is wrapped around 
        /// and the low 16 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi16( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi16( lhs, rhs );
            }
        }


        static SIMDType Mul( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_mulhrs_epi16( lhs, rhs );
            }
            else
            {
                return _mm256_mulhrs_epi16( lhs, rhs );
            }
        }


    };
    template<size_t N>
    struct Traits<Int32, N>
    {
        using Type = Int32;
    private:
        static constexpr bool UseShortSIMDType = N <= 4;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 4 : ( ( N + 7 ) & static_cast<Int64>( -8 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi32( std::bit_cast<int>( value ) );
            }
            else
            {
                return _mm256_set1_epi32( std::bit_cast<int>( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        /// <summary>
        /// Adds two int32 vectors.
        /// </summary>
        /// <param name="lhs">int32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds packed signed 32-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 32 bits (overflow), the result is wrapped around and 
        /// the low 32 bits are written to the destination vector (that is, the carry is ignored).
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi32( lhs, rhs );
            }
        }

        /// <summary>
        /// Subtracts int32 vectors.
        /// </summary>
        /// <param name="lhs">int32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed signed 32-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 32 bits (overflow), the result is wrapped around 
        /// and the low 32 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi32( lhs, rhs );
            }
        }

        static SIMDType Mul( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_mul_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_mul_epi32( lhs, rhs );
            }
        }


    };
    template<size_t N>
    struct Traits<UInt32, N>
    {
        using Type = UInt32;
    private:
        static constexpr bool UseShortSIMDType = N <= 4;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 4 : ( ( N + 7 ) & static_cast<Int64>( -8 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi32( std::bit_cast<int>( value ) );
            }
            else
            {
                return _mm256_set1_epi32( std::bit_cast<int>( value ) );
            }
        }


        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        /// <summary>
        /// Adds two uint32 vectors.
        /// </summary>
        /// <param name="lhs">uint32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">uint32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds packed unsigned 32-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 32 bits (overflow), the result is wrapped around and 
        /// the low 32 bits are written to the destination vector (that is, the carry is ignored).
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi32( lhs, rhs );
            }
        }

        /// <summary>
        /// Subtracts uint32 vectors.
        /// </summary>
        /// <param name="lhs">uint32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">uint32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed unsigned 32-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 32 bits (overflow), the result is wrapped around 
        /// and the low 32 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi32( lhs, rhs );
            }
        }


        static SIMDType Mul( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_mul_epu32( lhs, rhs );
            }
            else
            {
                return _mm256_mul_epu32( lhs, rhs );
            }
        }



    };
    template<size_t N>
    struct Traits<Int64, N>
    {
        using Type = Int64;
    private:
        static constexpr bool UseShortSIMDType = N <= 2;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 2 : ( ( N + 3 ) & static_cast<Int64>( -4 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi64x( std::bit_cast<long long>( value ) );
            }
            else
            {
                return _mm256_set1_epi64x( std::bit_cast<long long>( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        /// <summary>
        /// Adds two int64 vectors.
        /// </summary>
        /// <param name="lhs">int64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds packed signed 64-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 64 bits (overflow), the result is wrapped around and 
        /// the low 64 bits are written to the destination vector (that is, the carry is ignored).
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi64( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi64( lhs, rhs );
            }
        }

        /// <summary>
        /// Subtracts int64 vectors.
        /// </summary>
        /// <param name="lhs">int64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">int64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed signed 64-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 64 bits (overflow), the result is wrapped around 
        /// and the low 64 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi64( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi64( lhs, rhs );
            }
        }

        SIMDType Mul( SIMDType a, SIMDType b )
        {
            if constexpr ( UseShortSIMDType )
            {
                SIMDType bswap = _mm_shuffle_epi32( b, 0xB1 );
                SIMDType prodlh = _mm_mullo_epi32( a, bswap );

                SIMDType prodlh2 = _mm_srli_epi64( prodlh, 32 );
                SIMDType prodlh3 = _mm_add_epi32( prodlh2, prodlh );
                SIMDType prodlh4 = _mm_and_si128( prodlh3, _mm_set1_epi64x( 0x00000000FFFFFFFF ) );

                SIMDType prodll = _mm_mul_epu32( a, b );
                SIMDType prod = _mm_add_epi64( prodll, prodlh4 );
                return  prod;
            }
            else
            {
                SIMDType bswap = _mm256_shuffle_epi32( b, 0xB1 );
                SIMDType prodlh = _mm256_mullo_epi32( a, bswap );

                SIMDType prodlh2 = _mm256_srli_epi64( prodlh, 32 );
                SIMDType prodlh3 = _mm256_add_epi32( prodlh2, prodlh );
                SIMDType prodlh4 = _mm256_and_si256( prodlh3, _mm256_set1_epi64x( 0x00000000FFFFFFFF ) );

                SIMDType prodll = _mm256_mul_epu32( a, b );
                SIMDType prod = _mm256_add_epi64( prodll, prodlh4 );
                return  prod;
            }
        }

    };
    template<size_t N>
    struct Traits<UInt64, N>
    {
        using Type = UInt64;
    private:
        static constexpr bool UseShortSIMDType = N <= 2;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 2 : ( ( N + 3 ) & static_cast<Int64>( -4 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_si128( );
            }
            else
            {
                return _mm256_setzero_si256( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi64x( std::bit_cast<long long>( value ) );
            }
            else
            {
                return _mm256_set1_epi64x( std::bit_cast<long long>( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast<const __m128i*>( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast<const __m256i*>( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast<__m128i*>( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast<__m128i*>( dest ), src );
            }
        }

        /// <summary>
        /// Adds two uint64 vectors.
        /// </summary>
        /// <param name="lhs">uint64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">uint64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds packed unsigned 64-bit integers from source vector lhs and corresponding bits of source 
        /// vector rhs and stores the packed integer result in the destination vector. When an individual 
        /// result is too large to be represented in 64 bits (overflow), the result is wrapped around and 
        /// the low 64 bits are written to the destination vector (that is, the carry is ignored).
        /// You must control the range of values operated upon to prevent undetected overflow conditions.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_epi64( lhs, rhs );
            }
            else
            {
                return _mm256_add_epi64( lhs, rhs );
            }
        }

        /// <summary>
        /// Subtracts uint64 vectors.
        /// </summary>
        /// <param name="lhs">uint64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">uint64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// <p>
        /// Subtracts packed unsigned 64-bit integers of the second source vector rhs from 
        /// corresponding bits of the first source vector lhs. When an individual result 
        /// is too large to be represented in 64 bits (overflow), the result is wrapped around 
        /// and the low 64 bits are written to the destination vector (that is, the carry 
        /// is ignored).
        /// </p>
        /// <p>
        /// You must control the range of values operated upon to prevent undetected 
        /// overflow conditions.
        /// </p>
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_epi64( lhs, rhs );
            }
            else
            {
                return _mm256_sub_epi64( lhs, rhs );
            }
        }


        SIMDType Mul( SIMDType a, SIMDType b )
        {
            if constexpr ( UseShortSIMDType )
            {
                SIMDType bswap = _mm_shuffle_epi32( b, 0xB1 );
                SIMDType prodlh = _mm_mullo_epi32( a, bswap );

                SIMDType prodlh2 = _mm_srli_epi64( prodlh, 32 );
                SIMDType prodlh3 = _mm_add_epi32( prodlh2, prodlh );
                SIMDType prodlh4 = _mm_and_si128( prodlh3, _mm_set1_epi64x( 0x00000000FFFFFFFF ) );

                SIMDType prodll = _mm_mul_epu32( a, b );
                SIMDType prod = _mm_add_epi64( prodll, prodlh4 );
                return  prod;
            }
            else
            {
                SIMDType bswap = _mm256_shuffle_epi32( b, 0xB1 );
                SIMDType prodlh = _mm256_mullo_epi32( a, bswap );

                SIMDType prodlh2 = _mm256_srli_epi64( prodlh, 32 );
                SIMDType prodlh3 = _mm256_add_epi32( prodlh2, prodlh );
                SIMDType prodlh4 = _mm256_and_si256( prodlh3, _mm256_set1_epi64x( 0x00000000FFFFFFFF ) );

                SIMDType prodll = _mm256_mul_epu32( a, b );
                SIMDType prod = _mm256_add_epi64( prodll, prodlh4 );
                return  prod;
            }
        }



    };
    template<size_t N>
    struct Traits<float, N>
    {
        using Type = float;
    private:
        static constexpr bool UseShortSIMDType = N <= 4;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128>, SIMD::DataTypeTraits<DataType::m256> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t Capacity = UseShortSIMDType ? 4 : ( ( N + 7 ) & static_cast<Int64>( -8 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_ps( );
            }
            else
            {
                return _mm256_setzero_ps( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_ps( value );
            }
            else
            {
                return _mm256_set1_ps( value );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_ps( src );
            }
            else
            {
                return _mm256_load_ps( src );
            }
        }
        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_ps( src );
            }
            else
            {
                return _mm256_loadu_ps( src );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_ps( dest, src );
            }
            else
            {
                _mm256_store_ps( dest, src );
            }
        }
        static void UnaligedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_ps( dest, src );
            }
            else
            {
                _mm256_storeu_ps( dest, src );
            }
        }

        /// <summary>
        /// Adds two float32 vectors.
        /// </summary>
        /// <param name="lhs">float32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Performs an addition of the packed single-precision floating-point elements (float32 elements) 
        /// in the first source vector, lhs, with the float32 elements in the second source vector, rhs.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_ps( lhs, rhs );
            }
            else
            {
                return _mm256_add_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Add Horizontal single-precision floating-point Values
        /// </summary>
        /// <param name="lhs">float32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds pairs of adjacent single-precision floating-point values from the first 
        /// source operand, lhs, and the second source operand, rhs.
        /// </remarks>
        /// <returns>Result of the addition operation</returns>
        static SIMDType HAdd( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_hadd_ps( lhs, rhs );
            }
            else
            {
                return _mm256_hadd_ps( lhs, rhs );
            }
        }


        static SIMDType HSum( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                __m128 r1 = _mm_add_ps( v, _mm_movehl_ps( v, v ) );
                return _mm_add_ss( r1, _mm_movehdup_ps( r1 ) );
            }
            else
            {
                __m128 low = _mm256_castps256_ps128( v );
                __m128 high = _mm256_extractf128_ps( v, 1 );
                __m128 r1 = _mm_add_ps( low, high );
                __m128 r2 = _mm_add_ps( r1, _mm_movehl_ps( r1, r1 ) );
                return _mm_add_ss( r2, _mm_movehdup_ps( r2 ) );
            }
        }



        /// <summary>
        /// Subtracts float32 vectors.
        /// </summary>
        /// <param name="lhs">float32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Subtracts the packed single-precision floating-point elements (float32 elements) of the second source vector, rhs, from the first source vector, lhs.
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_ps( lhs, rhs );
            }
            else
            {
                return _mm256_sub_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Add/Subtract single-precision floating-point (float32) Values
        /// </summary>
        /// <param name="lhs">float32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds odd-numbered single-precision floating-point values of the first
        /// source operand, lhs, with the corresponding single-precision floating-point
        /// values from the second source operand, rhs; stores the result in the odd-numbered
        /// values of the result. Subtracts the even-numbered single-precision
        /// floating-point values from the second source operand, rhs, from the corresponding
        /// single-precision floating values in the first source operand, lhs; stores the
        /// result into the even-numbered values of the result.
        /// </remarks>
        /// <returns>Result of the operation is stored in the result vector, which is returned by the intrinsic.</returns>
        static SIMDType AddSub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_addsub_ps( lhs, rhs );
            }
            else
            {
                return _mm256_addsub_ps( lhs, rhs );
            }
        }


        /// <summary>
        /// Multiplies two float32 vectors.
        /// </summary>
        /// <param name="lhs">float32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Multiplies the packed single-precision floating-point elements (float32 elements) 
        /// in the first source vector, lhs, with the corresponding float32 elements in the second source vector, rhs.
        /// </remarks>
        /// <returns>Result of the multiplication operation.</returns>
        static SIMDType Mul( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_mul_ps( lhs, rhs );
            }
            else
            {
                return _mm256_mul_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Devides one float32 vector by another.
        /// </summary>
        /// <param name="lhs">float32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Devides the packed single-precision floating-point elements (float32 elements) 
        /// in the first source vector, lhs, by the corresponding float32 elements in the second source vector, rhs.
        /// </remarks>
        /// <returns>Result of the division operation</returns>
        static SIMDType Div( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_div_ps( lhs, rhs );
            }
            else
            {
                return _mm256_div_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Square Root of Single-Precision Floating-Point Values
        /// </summary>
        /// <param name="v"></param>
        /// <returns></returns>
        static SIMDType Sqrt( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sqrt_ps( v );
            }
            else
            {
                return _mm256_sqrt_ps( v );
            }
        }
        


        /// <summary>
        /// Multiply-adds packed single-precision floating-point values using three float32 vectors
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD multiply-add computation on packed single-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, 
        /// a and b, are multiplied and the infinite precision intermediate results are added to 
        /// corresponding values in the third operand, after which the final results are rounded to the 
        /// nearest float32 values.
        /// </remarks>
        /// <returns>Result of the multiply-add operation</returns>
        static SIMDType FMAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_ps( a, b, c );
            }
            else
            {
                return _mm256_fmadd_ps( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-adds scalar single-precision floating-point values using three float32vectors.
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of scalar SIMD multiply-add computation on scalar single-precision floating-point 
        /// values in the low 32-bits of three source operands, a, b, and c. The float32 values in two operands, 
        /// a and b, are multiplied and the infinite precision intermediate result is obtained. The float32 
        /// value in the third operand, c, is added to the infinite precision intermediate result. 
        /// The final result is rounded to the nearest float32 value.
        /// </remarks>
        /// <returns>Result of the multiply-add operation</returns>
        static SIMDType ScalarFMAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_ss( a, b, c );
            }
            else
            {
                return  _mm256_castps128_ps256( _mm_fmadd_ss( _mm256_castps256_ps128( a ), _mm256_castps256_ps128( b ), _mm256_castps256_ps128( c ) ) );
            }
        }


        /// <summary>
        /// Multiply-subtracts packed single-precision floating-point values using three float32 vectors
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD multiply-subtract computation on packed single-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, 
        /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
        /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
        /// The final results are rounded to the nearest float32 values.
        /// </remarks>
        /// <returns>Result of the multiply-subtract operation</returns>
        static SIMDType FMSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmsub_ps( a, b, c );
            }
            else
            {
                return _mm256_fmsub_ps( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-adds and subtracts packed single-precision floating-point values using three float32 vectors.
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD multiply-add-subtract computation on packed single-precision floating-point values 
        /// using three source vectors/operands, a, b, and c. Corresponding values in two operands, a and b, are 
        /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
        /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
        /// are rounded to the nearest float32 values.
        /// </remarks>
        /// <returns>Result of the multiply-add-subtract operation</returns>
        static SIMDType FMAddSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmaddsub_ps( a, b, c );
            }
            else
            {
                return _mm256_fmaddsub_ps( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-subtracts scalar single-precision floating-point values using three float32 vectors.
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of scalar SIMD multiply-subtract computation on scalar single-precision floating-point 
        /// values in the low 32-bits of three source operands, a, b, and c. The float32 values in two operands, 
        /// a and b, are multiplied and the infinite precision intermediate result is obtained. From the infinite 
        /// precision intermediate result, the float32 value in the third operand, c, is subtracted. The final 
        /// result is rounded to the nearest float32 value.
        /// </remarks>
        /// <returns>Result of the multiply-subtract operation</returns>
        static SIMDType ScalarFMSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmsub_ss( a, b, c );
            }
            else
            {
                return  _mm256_castps128_ps256( _mm_fmsub_ss( _mm256_castps256_ps128( a ), _mm256_castps256_ps128( b ), _mm256_castps256_ps128( c ) ) );
            }
        }

        /// <summary>
        /// Multiply-subtracts and adds packed single-precision floating-point values using three float32 vectors.
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD multiply-subtract-add computation on packed single-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, a and b, 
        /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
        /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
        /// The final results are rounded to the nearest float32 values.
        /// </remarks>
        /// <returns>Result of the multiply-subtract-add operation</returns>
        static SIMDType FMSubAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmsubadd_ps( a, b, c );
            }
            else
            {
                return _mm256_fmsubadd_ps( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-adds negated packed single-precision floating-point values of three float32 vectors
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD negated multiply-add computation on packed single-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, 
        /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
        /// the values in the third operand, c, after which the final results are rounded to the nearest 
        /// float32 values.
        /// </remarks>
        /// <returns>Result of the negated multiply-add operation.</returns>
        static SIMDType FNMAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fnmadd_ps( a, b, c );
            }
            else
            {
                return _mm256_fnmadd_ps( a, b, c );
            }
        }


        /// <summary>
        /// Multiply-adds negated scalar single-precision floating-point values of three float32 vectors.
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of scalar SIMD negated multiply-add computation on scalar single-precision 
        /// floating-point values in the low 32-bits of three source operands, a, b, and c. The float32 
        /// values in two operands, a and b, are multiplied and the negated infinite precision intermediate 
        /// result obtained is added to the float32 value in the third operand, c. The final result is 
        /// rounded to the nearest float32 value.
        /// </remarks>
        /// <returns>Result of the negated multiply-add operation.</returns>
        static SIMDType ScalarFNMAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fnmadd_ss( a, b, c );
            }
            else
            {

                return  _mm256_castps128_ps256( _mm_fnmadd_ss( _mm256_castps256_ps128( a ), _mm256_castps256_ps128( b ), _mm256_castps256_ps128( c ) ) );
            }
        }

        /// <summary>
        /// Multiply-subtracts negated packed single-precision floating-point values of three float32 vectors.
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD negated multiply-subtract computation on packed single-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, a and b, 
        /// are multiplied and the negated infinite precision intermediate result is obtained. From this 
        /// intermediate result the value in the third operand, c, is subtracted, after which the final results 
        /// are rounded to the nearest float32 values.
        /// </remarks>
        /// <returns>Result of the negated multiply-subtract operation.</returns>
        static SIMDType FNMSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fnmsub_ps( a, b, c );
            }
            else
            {
                return _mm256_fnmsub_ps( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-subtracts negated scalar single-precision floating-point values of three float32 vectors.
        /// </summary>
        /// <param name="a">float32 vector used for the operation</param>
        /// <param name="b">float32 vector used for the operation</param>
        /// <param name="c">float32 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of scalar SIMD negated multiply-subtract computation on scalar single-precision floating-point 
        /// values in the low 32-bits of three source operands, a, b, and c. The float32 values in two operands, a and b, 
        /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
        /// intermediate result, the float32 value in the third operand, c, is subtracted. The final result is rounded 
        /// to the nearest float32 value.
        /// </remarks>
        /// <returns>Result of the negated multiply-subtract operation.</returns>
        static SIMDType ScalarFNMSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fnmsub_ss( a, b, c );
            }
            else
            {

                return  _mm256_castps128_ps256( _mm_fnmsub_ss( _mm256_castps256_ps128( a ), _mm256_castps256_ps128( b ), _mm256_castps256_ps128( c ) ) );
            }
        }



    };
    template<size_t N>
    struct Traits<double, N>
    {
        using Type = double;
    private:
        static constexpr bool UseShortSIMDType = N <= 2;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128d>, SIMD::DataTypeTraits<DataType::m256d> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;

        static constexpr size_t Capacity = UseShortSIMDType ? 2 : ( ( N + 3 ) & static_cast<Int64>( -4 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_setzero_pd( );
            }
            else
            {
                return _mm256_setzero_pd( );
            }
        }

        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_pd( value );
            }
            else
            {
                return _mm256_set1_pd( value );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_pd( src );
            }
            else
            {
                return _mm256_load_pd( src );
            }
        }
        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_pd( src );
            }
            else
            {
                return _mm256_loadu_pd( src );
            }
        }


        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_pd( dest, src );
            }
            else
            {
                _mm256_store_pd( dest, src );
            }
        }
        static void UnalignedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_pd( dest, src );
            }
            else
            {
                _mm256_storeu_pd( dest, src );
            }
        }

        /// <summary>
        /// Adds two float64 vectors.
        /// </summary>
        /// <param name="lhs">float64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Performs an addition of the packed double-precision floating-point elements (float64 elements) 
        /// in the first source vector, lhs, with the float64 elements in the second source vector, rhs.
        /// </remarks>
        /// <returns>Result of the addition operation.</returns>
        static SIMDType Add( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_add_pd( lhs, rhs );
            }
            else
            {
                return _mm256_add_pd( lhs, rhs );
            }
        }

        /// <summary>
        /// Add Horizontal double-precision floating-point Values
        /// </summary>
        /// <param name="lhs">float64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds pairs of adjacent double-precision floating-point values from the first 
        /// source operand, lhs, and second source operand, rhs.
        /// </remarks>
        /// <returns>Result of the addition operation</returns>
        static SIMDType HAdd( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_hadd_pd( lhs, rhs );
            }
            else
            {
                return _mm256_hadd_pd( lhs, rhs );
            }
        }

        /*
        static SIMDType HSum( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                __m128d r1 = _mm_add_pd( v, _mm_movehl_pd( v, v ) );
                return _mm_add_sd( r1, _mm_movehdup_pd( r1 ) );
            }
            else
            {
                __m128d low = _mm256_castpd256_pd128( v );
                __m128d high = _mm256_extractf128_pd( v, 1 );
                __m128d r1 = _mm_add_pd( low, high );
                __m128d r2 = _mm_add_pd( r1, _mm_movehl_pd( r1, r1 ) );
                return _mm_add_sd( r2, _mm_movehdup_pd( r2 ) );
            }
        }
        */

        /// <summary>
        /// Subtracts float64 vectors.
        /// </summary>
        /// <param name="lhs">float64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Subtracts the packed double-precision floating-point elements (float64 elements) of the second 
        /// source vector, rhs, from the corresponding values in first source vector, lhs.
        /// </remarks>
        /// <returns>Returns the result of the subtraction operation.</returns>
        static SIMDType Sub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_pd( lhs, rhs );
            }
            else
            {
                return _mm256_sub_pd( lhs, rhs );
            }
        }


        /// <summary>
        /// Add/Subtract double-precision Floating-Point (float64) Values
        /// </summary>
        /// <param name="lhs">float64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds odd-numbered double-precision floating-point values of the first
        /// source operand, lhs, with the corresponding double-precision floating-point
        /// values from the second source operand, rhs; stores the result in the odd-numbered
        /// values of the result. Subtracts the even-numbered double-precision
        /// floating-point values from the second source operand, rhs, from the corresponding
        /// double-precision floating values in the first source operand, lhs; stores the
        /// result into the even-numbered values of the result.
        /// </remarks>
        /// <returns>Result of the operation is stored in the result vector, which is returned by the intrinsic.</returns>
        static SIMDType AddSub( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_addsub_pd( lhs, rhs );
            }
            else
            {
                return _mm256_addsub_pd( lhs, rhs );
            }
        }



        /// <summary>
        /// Multiplies two float64 vectors.
        /// </summary>
        /// <param name="lhs">float64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Multiplies the packed double-precision floating-point elements (float64 elements) 
        /// in the first source vector, lhs, with the corresponding float64 elements in the second source vector, rhs.
        /// </remarks>
        /// <returns>Result of the multiplication operation.</returns>
        static SIMDType Mul( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_mul_pd( lhs, rhs );
            }
            else
            {
                return _mm256_mul_pd( lhs, rhs );
            }
        }

        /// <summary>
        /// Devides one float64 vector by another.
        /// </summary>
        /// <param name="lhs">float64 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float64 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Devides the packed double-precision floating-point elements (float64 elements) 
        /// in the first source vector, lhs, by the corresponding float64 elements in the second source vector, rhs.
        /// </remarks>
        /// <returns>Result of the division operation</returns>
        static SIMDType Div( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_div_pd( lhs, rhs );
            }
            else
            {
                return _mm256_div_pd( lhs, rhs );
            }
        }

        /// <summary>
        /// Square Root of float64 vector
        /// </summary>
        /// <param name="v"></param>
        /// <returns></returns>
        static SIMDType Sqrt( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sqrt_pd( v );
            }
            else
            {
                return _mm256_sqrt_pd( v );
            }
        }

        /// <summary>
        /// Multiply-adds packed double-precision floating-point values using three float64 vectors
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD multiply-add computation on packed double-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, 
        /// a and b, are multiplied and the infinite precision intermediate results are added to 
        /// corresponding values in the third operand, after which the final results are rounded to 
        /// the nearest float64 values.
        /// </remarks>
        /// <returns>Result of the multiply-add operation</returns>
        static SIMDType FMAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_pd( a, b, c );
            }
            else
            {
                return _mm256_fmadd_pd( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-adds scalar double-precision floating-point values using three float64 vectors.
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of scalar SIMD multiply-add computation on scalar double-precision 
        /// floating-point values in the low 32-bits of three source operands, a, b, and c. 
        /// The float64 values in two operands, a and b, are multiplied and the infinite precision 
        /// intermediate result is obtained. The float64 value in the third operand, c, is added 
        /// to the infinite precision intermediate result. The final result is rounded to the 
        /// nearest float64 value.
        /// </remarks>
        /// <returns>Result of the multiply-add operation</returns>
        static SIMDType ScalarFMAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_sd( a, b, c );
            }
            else
            {

                return  _mm256_castpd128_pd256( _mm_fmadd_sd( _mm256_castpd256_pd128( a ), _mm256_castpd256_pd128( b ), _mm256_castpd256_pd128( c ) ) );
            }
        }



        /// <summary>
        /// Multiply-subtracts packed double-precision floating-point values using three float64 vectors
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD multiply-subtract computation on packed double-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, 
        /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
        /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
        /// The final results are rounded to the nearest float64 values.
        /// </remarks>
        /// <returns>Result of the multiply-subtract operation</returns>
        static SIMDType FMSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmsub_pd( a, b, c );
            }
            else
            {
                return _mm256_fmsub_pd( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-adds and subtracts packed double-precision floating-point values using three float64 vectors.
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD multiply-add-subtract computation on packed double-precision floating-point values 
        /// using three source vectors/operands, a, b, and c. Corresponding values in two operands, a and b, are 
        /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
        /// c, are added to the intermediate results while the even values are subtracted from them. The final 
        /// results are rounded to the nearest float64 values.
        /// </remarks>
        /// <returns>Result of the multiply-add-subtract operation</returns>
        static SIMDType FMAddSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmaddsub_pd( a, b, c );
            }
            else
            {
                return _mm256_fmaddsub_pd( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-subtracts scalar double-precision floating-point values using three float64 vectors.
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of scalar SIMD multiply-subtract computation on scalar double-precision floating-point 
        /// values in the low 64-bits of three source operands, a, b, and c. The float64 values in two operands, 
        /// a and b, are multiplied and the infinite precision intermediate result is obtained. From the infinite 
        /// precision intermediate result, the float64 value in the third operand, c, is subtracted. The final 
        /// result is rounded to the nearest float64 value.
        /// </remarks>
        /// <returns>Result of the multiply-subtract operation.</returns>
        static SIMDType ScalarFMSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmsub_sd( a, b, c );
            }
            else
            {

                return  _mm256_castpd128_pd256( _mm_fmsub_sd( _mm256_castpd256_pd128( a ), _mm256_castpd256_pd128( b ), _mm256_castpd256_pd128( c ) ) );
            }
        }

        /// <summary>
        /// Multiply-subtracts and adds packed double-precision floating-point values using three float64 vectors.
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD multiply-subtract-add computation on packed double-precision floating-point values 
        /// using three source vectors/operands, a, b, and c. Corresponding values in two operands, a and b, are 
        /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
        /// c, are subtracted from the intermediate results while the even values are added to them. The final 
        /// results are rounded to the nearest float64 values.
        /// </remarks>
        /// <returns>Result of the multiply-subtract-add operation</returns>
        static SIMDType FMSubAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmsubadd_pd( a, b, c );
            }
            else
            {
                return _mm256_fmsubadd_pd( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-adds negated packed double-precision floating-point values of three float64 vectors.
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD negated multiply-add computation on packed double-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, 
        /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
        /// the values in the third operand, c, after which the final results are rounded to the nearest 
        /// float64 values.
        /// </remarks>
        /// <returns>Result of the negated multiply-add operation.</returns>
        static SIMDType FMNAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fnmadd_pd( a, b, c );
            }
            else
            {
                return _mm256_fnmadd_pd( a, b, c );
            }
        }

        /// <summary>
        /// Multiply-adds negated scalar double-precision floating-point values of three float64 vectors.
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of scalar SIMD negated multiply-add computation on scalar double-precision floating-point 
        /// values in the low 64-bits of three source operands, a, b, and c. The float64 values in two operands, 
        /// a and b, are multiplied and the negated infinite precision intermediate result obtained is added to 
        /// the float64 value in the third operand, c. The final result is rounded to the nearest float64 value.
        /// </remarks>
        /// <returns>Result of the negated multiply-add operation</returns>
        static SIMDType ScalarFNMAdd( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fnmadd_sd( a, b, c );
            }
            else
            {

                return  _mm256_castpd128_pd256( _mm_fnmadd_sd( _mm256_castpd256_pd128( a ), _mm256_castpd256_pd128( b ), _mm256_castpd256_pd128( c ) ) );
            }
        }


        /// <summary>
        /// Multiply-subtracts negated packed double-precision floating-point values of three float64 vectors.
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of SIMD negated multiply-subtract computation on packed double-precision floating-point 
        /// values using three source vectors/operands, a, b, and c. Corresponding values in two operands, a and b, 
        /// are multiplied and the negated infinite precision intermediate result is obtained. From this intermediate 
        /// result the value in the third operand, c, is subtracted, after which the final results are rounded to the 
        /// nearest float64 values.
        /// </remarks>
        /// <returns>Result of the negated multiply-subtract operation.</returns>
        static SIMDType FMNSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fnmsub_pd( a, b, c );
            }
            else
            {
                return _mm256_fnmsub_pd( a, b, c );
            }
        }


        /// <summary>
        /// Multiply-subtracts negated scalar double-precision floating-point values of three float64 vectors.
        /// </summary>
        /// <param name="a">float64 vector used for the operation</param>
        /// <param name="b">float64 vector used for the operation</param>
        /// <param name="c">float64 vector used for the operation</param>
        /// <remarks>
        /// Performs a set of scalar SIMD negated multiply-subtract computation on scalar double-precision 
        /// floating-point values in the low 64-bits of three source operands, a, b, and c. The float64 values in 
        /// two operands, a and b, are multiplied and the negated infinite precision intermediate result is obtained. 
        /// From this negated intermediate result, the float64 value in the third operand, c, is subtracted. 
        /// The final result is rounded to the nearest float64 value.
        /// </remarks>
        /// <returns>Result of the negated multiply-subtract operation.</returns>
        static SIMDType ScalarFNMSub( SIMDType a, SIMDType b, SIMDType c ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fnmsub_sd( a, b, c );
            }
            else
            {

                return  _mm256_castpd128_pd256( _mm_fnmsub_sd( _mm256_castpd256_pd128( a ), _mm256_castpd256_pd128( b ), _mm256_castpd256_pd128( c ) ) );
            }
        }



    };


}

#endif
