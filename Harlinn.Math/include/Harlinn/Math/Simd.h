#pragma once
#ifndef HARLINN_MATH_SIMD_H_
#define HARLINN_MATH_SIMD_H_

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

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif

#include <Harlinn/Common/Utils.h>

#include <cmath>
#include <cfenv>
#include <immintrin.h>
#include <array>

namespace Harlinn::Math
{
    using namespace Harlinn::Common;
}

namespace Harlinn::Math::SIMD
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
    struct DataTypeTraits : public std::false_type
    {
    };

    template<>
    struct DataTypeTraits<DataType::m64> : public std::true_type
    {
        static constexpr DataType Id = DataType::m64;
        static constexpr size_t AlignAs = 8;
        static constexpr size_t Size = 8;
        using Type = __m64;
    };

    template<>
    struct DataTypeTraits<DataType::m128> : public std::true_type
    {
        static constexpr DataType Id = DataType::m128;
        static constexpr size_t AlignAs = 16;
        static constexpr size_t Size = 16;
        using Type = __m128;
        using IntegerType = __m128i;
    };
    template<>
    struct DataTypeTraits<DataType::m128i> : public std::true_type
    {
        static constexpr DataType Id = DataType::m128i;
        static constexpr size_t AlignAs = 16;
        static constexpr size_t Size = 16;
        using Type = __m128i;
    };
    template<>
    struct DataTypeTraits<DataType::m128d> : public std::true_type
    {
        static constexpr DataType Id = DataType::m128d;
        static constexpr size_t AlignAs = 16;
        static constexpr size_t Size = 16;
        using Type = __m128d;
        using IntegerType = __m128i;
    };

    template<>
    struct DataTypeTraits<DataType::m256> : public std::true_type
    {
        static constexpr DataType Id = DataType::m256;
        static constexpr size_t AlignAs = 32;
        static constexpr size_t Size = 32;
        using Type = __m256;
        using IntegerType = __m256i;
    };
    template<>
    struct DataTypeTraits<DataType::m256i> : public std::true_type
    {
        static constexpr DataType Id = DataType::m256i;
        static constexpr size_t AlignAs = 32;
        static constexpr size_t Size = 32;
        using Type = __m256i;
    };
    template<>
    struct DataTypeTraits<DataType::m256d> : public std::true_type
    {
        static constexpr DataType Id = DataType::m256d;
        static constexpr size_t AlignAs = 32;
        static constexpr size_t Size = 32;
        using Type = __m256d;
        using IntegerType = __m256i;
    };
    template<>
    struct DataTypeTraits<DataType::m512> : public std::true_type
    {
        static constexpr DataType Id = DataType::m512;
        static constexpr size_t AlignAs = 64;
        static constexpr size_t Size = 64;
        using Type = __m512;
        using IntegerType = __m512i;
    };
    template<>
    struct DataTypeTraits<DataType::m512i> : public std::true_type
    {
        static constexpr DataType Id = DataType::m512i;
        static constexpr size_t AlignAs = 64;
        static constexpr size_t Size = 64;
        using Type = __m512i;
    };
    template<>
    struct DataTypeTraits<DataType::m512d> : public std::true_type
    {
        static constexpr DataType Id = DataType::m512d;
        static constexpr size_t AlignAs = 64;
        static constexpr size_t Size = 64;
        using Type = __m512d;
        using IntegerType = __m512i;
    };

    template<typename T>
    struct TraitLimits : public std::false_type
    {
    };

    namespace Internal
    {
        template<typename ElementT, typename SIMDT>
        struct TraitLimitsImpl : public std::true_type
        {
            using ElementType = ElementT;
            using SIMDType = SIMDT;
            static constexpr size_t Size = sizeof( SIMDType ) / sizeof( ElementType );
        };

        struct TraitsBase : public std::true_type
        {
        };
    }
    template<>
    struct TraitLimits<char> : public Internal::TraitLimitsImpl<char, __m256i>
    {
    };
    template<>
    struct TraitLimits<Byte> : public Internal::TraitLimitsImpl<Byte, __m256i>
    {
    };
    template<>
    struct TraitLimits<SByte> : public Internal::TraitLimitsImpl<SByte, __m256i>
    {
    };
    template<>
    struct TraitLimits<Int16> : public Internal::TraitLimitsImpl<Int16, __m256i>
    {
    };
    template<>
    struct TraitLimits<UInt16> : public Internal::TraitLimitsImpl<UInt16, __m256i>
    {
    };
    template<>
    struct TraitLimits<Int32> : public Internal::TraitLimitsImpl<Int32, __m256i>
    {
    };
    template<>
    struct TraitLimits<UInt32> : public Internal::TraitLimitsImpl<UInt32, __m256i>
    {
    };
    template<>
    struct TraitLimits<Int64> : public Internal::TraitLimitsImpl<Int64, __m256i>
    {
    };
    template<>
    struct TraitLimits<UInt64> : public Internal::TraitLimitsImpl<UInt64, __m256i>
    {
    };
    template<>
    struct TraitLimits<float> : public Internal::TraitLimitsImpl<float, __m256>
    {
    };
    template<>
    struct TraitLimits<double> : public Internal::TraitLimitsImpl<double, __m256>
    {
    };


    namespace Internal
    {

        template<UInt32 Arg>
        constexpr UInt32 ShuffleImpl()
        {
            return Arg & 3;
        };

        template<UInt32 Arg1, UInt32 Arg2, UInt32 ...Remaining>
        constexpr UInt32 ShuffleImpl( )
        {
            UInt32 Count = sizeof...( Remaining ) + 1;
            UInt32 Shift = Count * 2;
            return (( Arg1 & 3 ) << Shift) + ShuffleImpl<Arg2, Remaining...>( );
        };
    }

    template<UInt32 ...Args>
    constexpr UInt32 Shuffle_v = Internal::ShuffleImpl<Args...>( );

    template<typename T, size_t N>
    struct Traits : public std::false_type
    {
        using Type = std::remove_cvref_t<T>;
    };

    /// <summary>
    /// Traits structure for 8-bit types that provides SIMD-optimized operations and type information for fixed-size arrays.
    /// </summary>
    /// <typeparam name="T">The 8-bit element type to be stored and manipulated.</typeparam>
    /// <typeparam name="N">The number of elements in the fixed-size array.</typeparam>
    template<typename T, size_t N>
    struct Traits8Bit : public Internal::TraitsBase
    {
        using Type = T;
        using UIntType = Byte;
        static constexpr size_t Size = N;
    private:
        static constexpr bool UseShortSIMDType = N <= 16;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        using ArrayType = std::array<Type, N>;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t SIMDTypeCapacity = UseShortSIMDType ? 16 : 32;
        static constexpr size_t Capacity = UseShortSIMDType ? 16 : ( ( N + 31 ) & static_cast< Int64 >( -32 ) );
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
                return _mm_set1_epi8( std::bit_cast< char >( value ) );
            }
            else
            {
                return _mm256_set1_epi8( std::bit_cast< char >( value ) );
            }
        }

        static SIMDType Mask( UIntType value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Size == 1 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, value );
                }
                else if constexpr ( Size == 2 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, value, value );
                }
                else if constexpr ( Size == 3 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, value, value, value );
                }
                else if constexpr ( Size == 4 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        value, value, value, value );
                }
                else if constexpr ( Size == 5 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 6 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 7 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 8 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 9 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 10 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 11 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 12 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 13 )
                {
                    return _mm_set_epi8( 0x00, 0x00, 0x00, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 14 )
                {
                    return _mm_set_epi8( 0x00, 0x00, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 15 )
                {
                    return _mm_set_epi8( 0x00, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else
                {
                    return _mm_set_epi8( value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
            }
            else
            {
                if constexpr ( Size == 17 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 18 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 19 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 20 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 21 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 22 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 23 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        0x00, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 24 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 25 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 26 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 27 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        0x00, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 28 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 29 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, 0x00, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 30 )
                {
                    return _mm256_set_epi8( 0x00, 0x00, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else if constexpr ( Size == 31 )
                {
                    return _mm256_set_epi8( 0x00, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }
                else
                {
                    return _mm256_set_epi8( value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value,
                        value, value, value, value );
                }

            }
        }


        static SIMDType Set( Type value1 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value2, Type value1 ) noexcept
            requires ( Size > 1 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 2 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 3 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 4 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 5 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value7, Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 6 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 7 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value9, Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 8 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }

        static SIMDType Set( Type value10, Type value9, Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 9 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }
        static SIMDType Set( Type value11, Type value10, Type value9, Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 10 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }
        static SIMDType Set( Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 11 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }
        static SIMDType Set( Type value13, Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 12 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, 0x00, std::bit_cast< char >( value13 ),
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, std::bit_cast< char >( value13 ),
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }
        static SIMDType Set( Type value14, Type value13, Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 13 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, 0x00, std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }
        static SIMDType Set( Type value15, Type value14, Type value13, Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 14 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( 0x00, std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }
        static SIMDType Set( Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 15 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi8( std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
            else
            {
                return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                    std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                    std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                    std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
            }
        }
        static SIMDType Set( Type value17, Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 16 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value18, Type value17, Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 17 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value19, Type value18, Type value17, Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 18 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 19 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value21, Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 20 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value22, Type value21, Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 21 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value23, Type value22, Type value21, Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 22 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 23 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value25, Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 24 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, std::bit_cast< char >( value25 ),
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value26, Type value25, Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 25 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, std::bit_cast< char >( value26 ), std::bit_cast< char >( value25 ),
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value27, Type value26, Type value25, Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 26 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                0x00, std::bit_cast< char >( value27 ), std::bit_cast< char >( value26 ), std::bit_cast< char >( value25 ),
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value28, Type value27, Type value26, Type value25,
            Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 27 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, 0x00,
                std::bit_cast< char >( value28 ), std::bit_cast< char >( value27 ), std::bit_cast< char >( value26 ), std::bit_cast< char >( value25 ),
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value29, Type value28, Type value27, Type value26, Type value25,
            Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 28 )
        {
            return _mm256_set_epi8( 0x00, 0x00, 0x00, std::bit_cast< char >( value29 ),
                std::bit_cast< char >( value28 ), std::bit_cast< char >( value27 ), std::bit_cast< char >( value26 ), std::bit_cast< char >( value25 ),
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value30, Type value29, Type value28, Type value27, Type value26, Type value25,
            Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 29 )
        {
            return _mm256_set_epi8( 0x00, 0x00, std::bit_cast< char >( value30 ), std::bit_cast< char >( value29 ),
                std::bit_cast< char >( value28 ), std::bit_cast< char >( value27 ), std::bit_cast< char >( value26 ), std::bit_cast< char >( value25 ),
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value31, Type value30, Type value29, Type value28, Type value27, Type value26, Type value25,
            Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 30 )
        {
            return _mm256_set_epi8( 0x00, std::bit_cast< char >( value31 ), std::bit_cast< char >( value30 ), std::bit_cast< char >( value29 ),
                std::bit_cast< char >( value28 ), std::bit_cast< char >( value27 ), std::bit_cast< char >( value26 ), std::bit_cast< char >( value25 ),
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }
        static SIMDType Set( Type value32, Type value31, Type value30, Type value29,
            Type value28, Type value27, Type value26, Type value25,
            Type value24, Type value23, Type value22, Type value21,
            Type value20, Type value19, Type value18, Type value17,
            Type value16, Type value15, Type value14, Type value13,
            Type value12, Type value11, Type value10, Type value9,
            Type value8, Type value7, Type value6, Type value5,
            Type value4, Type value3, Type value2, Type value1 ) noexcept
            requires ( Size > 31 )
        {
            return _mm256_set_epi8( std::bit_cast< char >( value32 ), std::bit_cast< char >( value31 ), std::bit_cast< char >( value30 ), std::bit_cast< char >( value29 ),
                std::bit_cast< char >( value28 ), std::bit_cast< char >( value27 ), std::bit_cast< char >( value26 ), std::bit_cast< char >( value25 ),
                std::bit_cast< char >( value24 ), std::bit_cast< char >( value23 ), std::bit_cast< char >( value22 ), std::bit_cast< char >( value21 ),
                std::bit_cast< char >( value20 ), std::bit_cast< char >( value19 ), std::bit_cast< char >( value18 ), std::bit_cast< char >( value17 ),
                std::bit_cast< char >( value16 ), std::bit_cast< char >( value15 ), std::bit_cast< char >( value14 ), std::bit_cast< char >( value13 ),
                std::bit_cast< char >( value12 ), std::bit_cast< char >( value11 ), std::bit_cast< char >( value10 ), std::bit_cast< char >( value9 ),
                std::bit_cast< char >( value8 ), std::bit_cast< char >( value7 ), std::bit_cast< char >( value6 ), std::bit_cast< char >( value5 ),
                std::bit_cast< char >( value4 ), std::bit_cast< char >( value3 ), std::bit_cast< char >( value2 ), std::bit_cast< char >( value1 ) );
        }








        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {

                if constexpr ( Size == 1 )
                {
                    return _mm_cvtsi32_si128( static_cast< int >( src[ 0 ] ) );
                }
                else if constexpr ( Size == 2 )
                {
                    return _mm_cvtsi32_si128( static_cast< int >( reinterpret_cast< const UInt16* >( src )[ 0 ] ) );
                }
                else if constexpr ( Size == 3 )
                {
                    return _mm_cvtsi32_si128( static_cast< int >( reinterpret_cast< const UInt16* >( src )[ 0 ] ) | ( static_cast< int >( src[ 2 ] ) << 16 ) );
                }
                else if constexpr ( Size == 4 )
                {
                    return _mm_cvtsi32_si128( *reinterpret_cast< const Int32* >( src ) );
                }
                else if constexpr ( Size == 5 )
                {
                    UInt64 tmp = static_cast< UInt64 >( *reinterpret_cast< const UInt32* >( src ) ) |
                        ( static_cast< UInt64 >( src[ 4 ] ) << 32 );
                    return _mm_castpd_si128( _mm_load_sd( reinterpret_cast< const double* >( &tmp ) ) );
                }
                else if constexpr ( Size == 6 )
                {
                    UInt64 tmp = static_cast< UInt64 >( *reinterpret_cast< const UInt32* >( src ) ) |
                        ( static_cast< UInt64 >( reinterpret_cast< const UInt16* >( src )[ 2 ] ) << 32 );
                    return _mm_castpd_si128( _mm_load_sd( reinterpret_cast< const double* >( &tmp ) ) );
                }
                else if constexpr ( Size == 7 )
                {
                    UInt64 tmp = static_cast< UInt64 >( *reinterpret_cast< const UInt32* >( src ) ) |
                        ( static_cast< UInt64 >( reinterpret_cast< const UInt16* >( src )[ 2 ] ) << 32 ) |
                        ( static_cast< UInt64 >( src[ 6 ] ) << 48 );
                    return _mm_castpd_si128( _mm_load_sd( reinterpret_cast< const double* >( &tmp ) ) );
                }
                else if constexpr ( Size == 8 )
                {
                    return _mm_castpd_si128( _mm_load_sd( reinterpret_cast< const double* >( src ) ) );
                }
                else if constexpr ( Size == 16 )
                {
                    return _mm_load_si128( reinterpret_cast< const __m128i* >( src ) );
                }
                else
                {
                    alignas( AlignAs ) std::array<Type, 16> values;
                    [&values, src] <std::size_t... I>
                        ( std::index_sequence<I...> )
                    {
                        ( ( values[ I ] = src[ I ] ), ... );
                    }( std::make_index_sequence<Size>( ) );
                    [&values] <std::size_t... I>
                        ( std::index_sequence<I...> )
                    {
                        ( ( values[ Size + I ] = static_cast< Type >( 0 ) ), ... );
                    }( std::make_index_sequence<16 - Size>( ) );
                    return _mm_load_si128( reinterpret_cast< const __m128i* >( values.data( ) ) );
                }
            }
            else
            {
                alignas( AlignAs ) std::array<Type, 32> values;
                [&values, src] <std::size_t... I>
                    ( std::index_sequence<I...> )
                {
                    ( ( values[ I ] = src[ I ] ), ... );
                }( std::make_index_sequence<Size>( ) );
                [&values] <std::size_t... I>
                    ( std::index_sequence<I...> )
                {
                    ( ( values[ Size + I ] = static_cast< Type >( 0 ) ), ... );
                }( std::make_index_sequence<32 - Size>( ) );
                return _mm256_load_si256( reinterpret_cast< const __m256i* >( values.data( ) ) );
            }
        }

        static SIMDType Load( const ArrayType& src )
        {
            return Load( src.data( ) );
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast< const __m256i* >( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Size == 1 )
                {
                    *dest = static_cast< Type >( std::bit_cast< UInt32 >( _mm_cvtsi128_si32( src ) ) );
                }
                else if constexpr ( Size == 2 )
                {
                    *reinterpret_cast< UInt16* >( dest ) = static_cast< UInt16 >( std::bit_cast< UInt32 >( _mm_cvtsi128_si32( src ) ) );
                }
                else if constexpr ( Size == 3 )
                {
                    auto tmp = std::bit_cast< UInt32 >( _mm_cvtsi128_si32( src ) );
                    *reinterpret_cast< UInt16* >( dest ) = static_cast< UInt16 >( tmp );
                    dest[ 2 ] = static_cast< Type >( tmp >> 16 );
                }
                else if constexpr ( Size == 4 )
                {
                    *reinterpret_cast< UInt32* >( dest ) = std::bit_cast< UInt32 >( _mm_cvtsi128_si32( src ) );
                }
                else if constexpr ( Size == 5 )
                {
                    auto tmp = std::bit_cast< UInt64 >( _mm_cvtsi128_si64( src ) );
                    *reinterpret_cast< UInt32* >( dest ) = static_cast< UInt32 >( tmp );
                    dest[ 4 ] = static_cast< Type >( tmp >> 32 );
                }
                else if constexpr ( Size == 6 )
                {
                    auto tmp = std::bit_cast< UInt64 >( _mm_cvtsi128_si64( src ) );
                    *reinterpret_cast< UInt32* >( dest ) = static_cast< UInt32 >( tmp );
                    reinterpret_cast< UInt16* >( dest )[ 2 ] = static_cast< UInt16 >( tmp >> 32 );
                }
                else if constexpr ( Size == 7 )
                {
                    auto tmp = std::bit_cast< UInt64 >( _mm_cvtsi128_si64( src ) );
                    *reinterpret_cast< UInt32* >( dest ) = static_cast< UInt32 >( tmp );
                    reinterpret_cast< UInt16* >( dest )[ 2 ] = static_cast< UInt16 >( tmp >> 32 );
                    dest[ 6 ] = static_cast< Type >( tmp >> 48 );
                }
                else if constexpr ( Size == 8 )
                {
                    *reinterpret_cast< UInt64* >( dest ) = std::bit_cast< UInt64 >( _mm_cvtsi128_si64( src ) );
                }
                else if constexpr ( Size == 16 )
                {
                    _mm_store_si128( reinterpret_cast< __m128i* >( dest ), src );
                }
                else
                {
                    alignas( AlignAs ) std::array<Type, 16> values;
                    _mm_store_si128( reinterpret_cast< __m128i* >( values.data( ) ), src );
                    [&values, dest] <std::size_t... I>
                        ( std::index_sequence<I...> )
                    {
                        ( ( dest[ I ] = values[ I ] ), ... );
                    }( std::make_index_sequence<Size>( ) );
                }
            }
            else
            {
                if constexpr ( Size == 32 )
                {
                    _mm256_store_si256( reinterpret_cast< __m256i* >( dest ), src );
                }
                else
                {
                    alignas( AlignAs ) std::array<Type, 32> values;
                    _mm256_store_si256( reinterpret_cast< __m256i* >( values.data( ) ), src );
                    [&values, dest] <std::size_t... I>
                        ( std::index_sequence<I...> )
                    {
                        ( ( dest[ I ] = values[ I ] ), ... );
                    }( std::make_index_sequence<Size>( ) );
                }
            }
        }




        static void UnalignedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast< __m128i* >( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast< __m128i* >( dest ), src );
            }
        }


        static ArrayType ToArray( SIMDType src )
        {
            ArrayType result;
            Store( result.data( ) );
            return result;
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

    /// <summary>
    /// Specialization of the Traits struct for character arrays of a specific size.
    /// </summary>
    /// <typeparam name="N">The size of the character array.</typeparam>
    template<size_t N>
    struct Traits<char, N> : public Traits8Bit<char, N>
    {
    };

    /// <summary>
    /// Specialization of the Traits template for signed byte types with a specific size.
    /// </summary>
    /// <typeparam name="N">The size or dimension parameter for the traits specialization.</typeparam>
    template<size_t N>
    struct Traits<SByte, N> : public Traits8Bit<SByte, N>
    {
    };

    /// <summary>
    /// Template specialization that defines traits for a Byte type with a specified size.
    /// </summary>
    /// <typeparam name="N">The size parameter, typically representing the number of bytes or elements.</typeparam>
    template<size_t N>
    struct Traits<Byte, N> : public Traits8Bit<Byte, N>
    {
    };


    /// <summary>
    /// A traits structure that provides SIMD operations and type 
    /// information for 16-bit integer types, automatically selecting 
    /// between 128-bit (SSE) and 256-bit (AVX2) SIMD instruction 
    /// sets based on the number of elements.
    /// </summary>
    /// <typeparam name="T">The 16-bit integer type (e.g., int16_t, uint16_t, short).</typeparam>
    /// <typeparam name="N">The number of elements in the vector.</typeparam>
    template<typename T, size_t N>
    struct Traits16Bit : public Internal::TraitsBase
    {
        using Type = T;
        static constexpr size_t Size = N;
    private:
        static constexpr bool UseShortSIMDType = N <= 8;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        using ArrayType = std::array<Type, N>;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t SIMDTypeCapacity = UseShortSIMDType ? 8 : 16;
        static constexpr size_t Capacity = UseShortSIMDType ? 8 : ( ( N + 15 ) & static_cast< Int64 >( -16 ) );
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
                return _mm_set1_epi16( std::bit_cast< short >( value ) );
            }
            else
            {
                return _mm256_set1_epi16( std::bit_cast< short >( value ) );
            }
        }

        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast< const __m128i* >( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast< const __m256i* >( src ) );
            }
        }

        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast< const __m256i* >( src ) );
            }
        }

        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast< __m128i* >( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast< __m128i* >( dest ), src );
            }
        }

        static void UnalignedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast< __m128i* >( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast< __m128i* >( dest ), src );
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

    /// <summary>
    /// Specialization of the Traits template for Int16 types with a specified size, inheriting from Traits16Bit.
    /// </summary>
    /// <typeparam name="N">The size parameter for the traits specialization.</typeparam>
    template<size_t N>
    struct Traits<Int16, N> : public Traits16Bit<Int16, N>
    {
    };

    /// <summary>
    /// Specialization of the Traits template for 16-bit unsigned integer types.
    /// </summary>
    /// <typeparam name="N">The size parameter for the traits specialization.</typeparam>
    template<size_t N>
    struct Traits<UInt16, N> : public Traits16Bit<UInt16, N>
    {
    };


    /// <summary>
    /// A traits structure providing SIMD operations and type information for 
    /// 32-bit integer types, automatically selecting between 128-bit and 
    /// 256-bit SIMD implementations based on vector size.
    /// </summary>
    /// <typeparam name="T">The 32-bit element type (e.g., int32_t, uint32_t, float).</typeparam>
    /// <typeparam name="N">The number of elements in the vector.</typeparam>
    template<typename T, size_t N>
    struct Traits32Bit : public Internal::TraitsBase
    {
        using Type = T;
        static constexpr size_t Size = N;
    private:
        static constexpr bool UseShortSIMDType = N <= 4;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        using ArrayType = std::array<Type, N>;
        using UIntType = std::make_unsigned_t<Type>;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t SIMDTypeCapacity = UseShortSIMDType ? 4 : 8;
        static constexpr size_t Capacity = UseShortSIMDType ? 4 : ( ( N + 7 ) & static_cast< Int64 >( -8 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        /// <summary>
        /// Creates a SIMD vector with all elements set to zero.
        /// </summary>
        /// <returns>A SIMD vector (either 128-bit or 256-bit depending on UseShortSIMDType) with all bits set to zero.</returns>
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
        /// <summary>
        /// Fills a SIMD vector with a single value replicated across all elements.
        /// </summary>
        /// <param name="value">The value to replicate across all elements of the SIMD vector.</param>
        /// <returns>
        /// A SIMD vector with all elements set to the specified value, using 
        /// either 128-bit (SSE) or 256-bit (AVX) instructions depending on 
        /// the UseShortSIMDType configuration.
        /// </returns>
        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi32( std::bit_cast< int >( value ) );
            }
            else
            {
                return _mm256_set1_epi32( std::bit_cast< int >( value ) );
            }
        }

        /// <summary>
        /// Creates a SIMD vector filled with a divisor value for the first Num elements and 1 for the remaining elements.
        /// </summary>
        /// <typeparam name="Num">The number of elements to fill with the divisor value. Must be greater than 0 and less than or equal to SIMDTypeCapacity.</typeparam>
        /// <param name="value">The divisor value to fill into the first Num elements of the SIMD vector.</param>
        /// <returns>A SIMD vector (either 128-bit or 256-bit) with the divisor value in the first Num positions and 1 in the remaining positions.</returns>
        template<size_t Num>
        static SIMDType FillDivisor( Type value ) noexcept requires ( Num > 0 && Num <= SIMDTypeCapacity )
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Num == 1 )
                {
                    return _mm_set_epi32( 1.f, 1.f, 1.f, value );
                }
                else if constexpr ( Num == 2 )
                {
                    return _mm_set_epi32( 1.f, 1.f, value, value );
                }
                else if constexpr ( Num == 3 )
                {
                    return _mm_set_epi32( 1.f, value, value, value );
                }
                else
                {
                    return _mm_set1_epi32( value );
                }
            }
            else
            {
                if constexpr ( Num == 5 )
                {
                    return _mm256_set_epi32( 1.f, 1.f, 1.f, value, value, value, value, value );
                }
                else if constexpr ( Num == 6 )
                {
                    return _mm256_set_epi32( 1.f, 1.f, value, value, value, value, value, value );
                }
                else if constexpr ( Num == 7 )
                {
                    return _mm256_set_epi32( 1.f, value, value, value, value, value, value, value );
                }
                else
                {
                    return _mm256_set1_epi32( value );
                }
            }
        }

        /// <summary>
        /// Trims a SIMD vector to the specified size by masking out unused elements.
        /// </summary>
        /// <param name="v">The SIMD vector to trim.</param>
        /// <returns>
        /// The trimmed SIMD vector. If Size equals SIMDTypeCapacity, returns the 
        /// input vector unchanged; otherwise, returns the vector masked to 
        /// include only the first Size elements.
        /// </returns>
        static SIMDType Trim( SIMDType v ) noexcept
        {
            if constexpr ( Size == SIMDTypeCapacity )
            {
                return v;
            }
            else
            {
                return And( v, Mask( ) );
            }
        }

        /// <summary>
        /// Creates a SIMD mask vector by setting specific lanes to a given value based on the compile-time Size parameter.
        /// </summary>
        /// <param name="value">The unsigned integer value to use for populating the active lanes of the mask.</param>
        /// <returns>A SIMD vector (either __m128i or __m256i) with the rightmost Size lanes set to value and remaining lanes set to 0x00000000.</returns>
        static SIMDType Mask( UIntType value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Size == 1 )
                {
                    return _mm_set_epi32( 0x00000000, 0x00000000, 0x00000000, value );
                }
                else if constexpr ( Size == 2 )
                {
                    return _mm_set_epi32( 0x00000000, 0x00000000, value, value );
                }
                else if constexpr ( Size == 3 )
                {
                    return _mm_set_epi32( 0x00000000, value, value, value );
                }
                else
                {
                    return _mm_set_epi32( value, value, value, value );
                }
            }
            else
            {
                if constexpr ( Size == 5 )
                {
                    return _mm256_set_epi32( 0x00000000, 0x00000000, 0x00000000, value, value, value, value, value );
                }
                else if constexpr ( Size == 6 )
                {
                    return _mm256_set_epi32( 0x00000000, 0x00000000, value, value, value, value, value, value );
                }
                else if constexpr ( Size == 7 )
                {
                    return _mm256_set_epi32( 0x00000000, value, value, value, value, value, value, value );
                }
                else
                {
                    return _mm256_set_epi32( value, value, value, value, value, value, value, value );
                }
            }
        }

        /// <summary>
        /// Returns a mask suitable for extracting
        /// the <c>Size</c> lowest elements from
        /// the <c>SIMDType</c> using the <c>And</c> function.
        /// </summary>
        /// <returns></returns>
        static SIMDType Mask( ) noexcept
        {
            return Mask( 0xFFFFFFFF );
        }

        /// <summary>
        /// Creates a SIMD vector with a single value in the lowest position and zeros in all other positions.
        /// </summary>
        /// <param name="value1">The value to place in the lowest element of the SIMD vector.</param>
        /// <returns>
        /// A SIMD vector containing the specified value in the lowest position and zeros elsewhere. 
        /// Returns either a 128-bit (_mm) or 256-bit (_mm256) vector depending on the 
        /// UseShortSIMDType compile-time constant.
        /// </returns>
        static SIMDType Set( Type value1 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi32(0, 0, 0, value1 );
            }
            else
            {
                return _mm256_set_epi32( 0, 0, 0, 0, 0, 0, 0, value1 );
            }
        }

        /// <summary>
        /// Creates a SIMD vector by setting two integer values in the lowest positions.
        /// </summary>
        /// <param name="value2">The integer value to place in the second position.</param>
        /// <param name="value1">The integer value to place in the first (lowest) position.</param>
        /// <returns>A SIMD vector containing the two specified values in the lowest positions, with remaining positions zeroed.</returns>
        static SIMDType Set( Type value2, Type value1 ) noexcept requires ( N > 1 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi32( 0, 0, value2, value1 );
            }
            else
            {
                return _mm256_set_epi32( 0, 0, 0, 0, 0, 0, value2, value1 );
            }
        }

        /// <summary>
        /// Creates a SIMD vector by setting three values in the lower elements, with remaining elements zeroed.
        /// </summary>
        /// <param name="value3">The value to place in the third element (index 2).</param>
        /// <param name="value2">The value to place in the second element (index 1).</param>
        /// <param name="value1">The value to place in the first element (index 0).</param>
        /// <returns>
        /// A SIMD vector containing the three specified values in the lower elements, 
        /// with upper elements set to zero. Returns a 128-bit SIMD type 
        /// if UseShortSIMDType is true, otherwise a 256-bit SIMD type.
        /// </returns>
        static SIMDType Set( Type value3, Type value2, Type value1 ) noexcept requires ( N > 2 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi32( 0, value3, value2, value1 );
            }
            else
            {
                return _mm256_set_epi32( 0, 0, 0, 0, 0, value3, value2, value1 );
            }
        }

        /// <summary>
        /// Creates a SIMD vector by setting four integer values in reverse order.
        /// </summary>
        /// <param name="value4">The value to place in the fourth position (highest order element).</param>
        /// <param name="value3">The value to place in the third position.</param>
        /// <param name="value2">The value to place in the second position.</param>
        /// <param name="value1">The value to place in the first position (lowest order element).</param>
        /// <returns>A SIMD vector containing the four specified values, with the remaining elements (if any) set to zero.</returns>
        static SIMDType Set( Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 3 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_epi32( value4, value3, value2, value1 );
            }
            else
            {
                return _mm256_set_epi32( 0, 0, 0, 0, value4, value3, value2, value1 );
            }
        }

        /// <summary>
        /// Creates a SIMD vector by setting individual values in reverse order, with the remaining elements zeroed.
        /// </summary>
        /// <param name="value5">The value to set in the 5th position (index 4).</param>
        /// <param name="value4">The value to set in the 4th position (index 3).</param>
        /// <param name="value3">The value to set in the 3rd position (index 2).</param>
        /// <param name="value2">The value to set in the 2nd position (index 1).</param>
        /// <param name="value1">The value to set in the 1st position (index 0).</param>
        /// <returns>A SIMD vector containing the specified values in the lower 5 positions, with the upper 3 positions set to zero.</returns>
        static SIMDType Set( Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 4 )
        {
            return _mm256_set_epi32( 0, 0, 0, value5, value4, value3, value2, value1 );
        }

        /// <summary>
        /// Creates a SIMD vector by setting six values in reverse order, with the remaining elements set to zero.
        /// </summary>
        /// <param name="value6">The value to set in the sixth position.</param>
        /// <param name="value5">The value to set in the fifth position.</param>
        /// <param name="value4">The value to set in the fourth position.</param>
        /// <param name="value3">The value to set in the third position.</param>
        /// <param name="value2">The value to set in the second position.</param>
        /// <param name="value1">The value to set in the first position.</param>
        /// <returns>A SIMD vector containing the specified values in reverse order, with leading elements set to zero.</returns>
        static SIMDType Set( Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 5 )
        {
            return _mm256_set_epi32( 0, 0, value6, value5, value4, value3, value2, value1 );
        }

        /// <summary>
        /// Creates a SIMD vector by setting individual elements with the provided values.
        /// </summary>
        /// <param name="value7">The value for the seventh element of the vector.</param>
        /// <param name="value6">The value for the sixth element of the vector.</param>
        /// <param name="value5">The value for the fifth element of the vector.</param>
        /// <param name="value4">The value for the fourth element of the vector.</param>
        /// <param name="value3">The value for the third element of the vector.</param>
        /// <param name="value2">The value for the second element of the vector.</param>
        /// <param name="value1">The value for the first element of the vector.</param>
        /// <returns>A SIMD vector with elements set to the specified values, with the eighth element initialized to zero.</returns>
        static SIMDType Set( Type value7, Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 6 )
        {
            return _mm256_set_epi32( 0, value7, value6, value5, value4, value3, value2, value1 );
        }

        /// <summary>
        /// Creates a SIMD vector by setting eight 32-bit integer values in reverse order.
        /// </summary>
        /// <param name="value8">The value for the highest-order (8th) element.</param>
        /// <param name="value7">The value for the 7th element.</param>
        /// <param name="value6">The value for the 6th element.</param>
        /// <param name="value5">The value for the 5th element.</param>
        /// <param name="value4">The value for the 4th element.</param>
        /// <param name="value3">The value for the 3rd element.</param>
        /// <param name="value2">The value for the 2nd element.</param>
        /// <param name="value1">The value for the lowest-order (1st) element.</param>
        /// <returns>A SIMD vector containing the eight specified values.</returns>
        static SIMDType Set( Type value8, Type value7, Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 7 )
        {
            return _mm256_set_epi32( value8, value7, value6, value5, value4, value3, value2, value1 );
        }

        /// <summary>
        /// Sets the X component (first element) of a SIMD vector to a specified value.
        /// </summary>
        /// <param name="v">The SIMD vector whose X component will be replaced.</param>
        /// <param name="value">The value to set in the X component.</param>
        /// <returns>A new SIMD vector with the X component set to the specified value and all other components unchanged from the input vector.</returns>
        static SIMDType SetX( SIMDType v, Type value )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_blend_epi32( v, _mm_set1_epi32( value ), 0b0001 );
            }
            else
            {
                return _mm256_blend_epi32( v, _mm256_set1_epi32( value ), 0b0001 );
            }
        }

        /// <summary>
        /// Sets the Y component of a SIMD vector to a specified value.
        /// </summary>
        /// <param name="v">The SIMD vector whose Y component will be modified.</param>
        /// <param name="value">The value to set for the Y component.</param>
        /// <returns>A new SIMD vector with the Y component set to the specified value and all other components unchanged from the input vector.</returns>
        static SIMDType SetY( SIMDType v, Type value )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_blend_epi32( v, _mm_set1_epi32( value ), 0b0010 );
            }
            else
            {
                return _mm256_blend_epi32( v, _mm256_set1_epi32( value ), 0b0010 );
            }
        }

        /// <summary>
        /// Sets the Z component of a SIMD vector to a specified value.
        /// </summary>
        /// <param name="v">The SIMD vector whose Z component will be modified.</param>
        /// <param name="value">The value to set in the Z component.</param>
        /// <returns>A new SIMD vector with the Z component set to the specified value and other components copied from the input vector.</returns>
        static SIMDType SetZ( SIMDType v, Type value )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_blend_epi32( v, _mm_set1_epi32( value ), 0b0100 );
            }
            else
            {
                return _mm256_blend_epi32( v, _mm256_set1_epi32( value ), 0b0100 );
            }
        }

        /// <summary>
        /// Sets the W component (fourth element) of a SIMD vector to a specified value.
        /// </summary>
        /// <param name="v">The source SIMD vector whose W component will be replaced.</param>
        /// <param name="value">The value to set in the W component.</param>
        /// <returns>A new SIMD vector with the W component set to the specified value and other components unchanged from the source vector.</returns>
        static SIMDType SetW( SIMDType v, Type value )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_blend_epi32( v, _mm_set1_epi32( value ), 0b1000 );
            }
            else
            {
                return _mm256_blend_epi32( v, _mm256_set1_epi32( value ), 0b1000 );
            }
        }

        /// <summary>
        /// Loads N elements from memory into a SIMD register with optimized paths for different element counts.
        /// </summary>
        /// <param name="src">Pointer to the source memory location containing the elements to load.</param>
        /// <returns>A SIMD register (SIMDType) containing the loaded elements. Returns __m128i for N≤4 or __m256i for N>4, depending on UseShortSIMDType.</returns>
        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_castps_si128( _mm_load_ss( reinterpret_cast< const float* >( src ) ) );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_castpd_si128( _mm_load_sd( reinterpret_cast< const double* >( src ) ) );
                }
                else if constexpr ( N == 3 )
                {
                    __m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src ) ) );
                    __m128 high = _mm_load_ss( reinterpret_cast< const float* >( src + 2 ) );
                    return _mm_castps_si128( _mm_movelh_ps( low, high ) );
                }
                else
                {
                    return _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) );
                }
            }
            else
            {
                if constexpr ( N == 5 )
                {
                    return _mm256_castps_si256( _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_load_ps( src ) ), _mm_load_ss( src + 4 ), 1 ) );
                }
                else if constexpr ( N == 6 )
                {
                    return _mm256_castps_si256( _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_load_ps( src ) ), _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src + 4 ) ) ), 1 ) );
                }
                else if constexpr ( N == 7 )
                {
                    auto rmm1 = _mm_load_ps( src );
                    __m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src + 4 ) ) );
                    __m128 high = _mm_load_ss( reinterpret_cast< const float* >( src + 6 ) );
                    auto rmm2 = _mm_insert_ps( low, high, 0x20 );
                    return _mm256_castps_si256( _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm2, 1 ) );
                }
                else
                {
                    return _mm256_loadu_si256( reinterpret_cast< const __m256i* >( src ) );
                }
            }
        }

        /// <summary>
        /// Loads SIMD data from a std::array into a SIMD type.
        /// </summary>
        /// <typeparam name="NA">The size of the source array, which must be greater than or equal to N.</typeparam>
        /// <param name="src">The source array containing the data to load.</param>
        /// <returns>A SIMD type populated with data from the source array.</returns>
        template<size_t NA>
            requires ( NA >= N )
        static SIMDType Load( const std::array<Type, NA>& src ) noexcept
        {
            return Load( src.data( ) );
        }


        /// <summary>
        /// Loads SIMD data from an unaligned memory location.
        /// </summary>
        /// <param name="src">Pointer to the source memory location from which to load data. The memory does not need to be aligned.</param>
        /// <returns>A SIMD vector containing the loaded data. Returns a 128-bit vector (__m128i) if UseShortSIMDType is true, otherwise returns a 256-bit vector (__m256i).</returns>
        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast< const __m256i* >( src ) );
            }
        }

        /// <summary>
        /// Stores a SIMD vector to an aligned memory location.
        /// </summary>
        /// <param name="dest">Pointer to the aligned destination memory address where the SIMD vector will be stored.</param>
        /// <param name="src">The SIMD vector to store.</param>
        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast< __m128i* >( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast< __m256i* >( dest ), src );
            }
        }

        /// <summary>
        /// Stores a SIMD register value to an unaligned memory location.
        /// </summary>
        /// <param name="dest">Pointer to the destination memory location where the SIMD data will be stored. Does not need to be aligned.</param>
        /// <param name="src">The SIMD register value to store to memory.</param>
        static void UnalignedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast< __m128i* >( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast< __m128i* >( dest ), src );
            }
        }

        /// <summary>
        /// Returns the first element of <c>src</<>. The first
        /// element is the element at the lowest position of <c>src</<>.
        /// </summary>
        /// <param name="src">SIMDType to extract the first value from.</param>
        /// <returns>
        /// The first element of <c>src</<>.
        /// </returns>
        static Type First( SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cvtsi128_si32( src );
            }
            else
            {
                return _mm256_cvtsi256_si32( src );
            }
        }

        /// <summary>
        /// Returns an array containing the lower <c>N</c> elements
        /// of <c>v</c>.
        /// </summary>
        /// <param name="src">
        /// The SIMDType holding the values to return
        /// </param>
        /// <returns>
        /// An array containing the lower <c>N</c> elements
        /// of <c>v</c>.
        /// </returns>
        static ArrayType ToArray( SIMDType src ) noexcept
        {
            if constexpr ( N == SIMDTypeCapacity )
            {
                alignas( AlignAs ) ArrayType result;
                Store( result.data( ), src );
                return result;
            }
            else if constexpr ( N == 1 )
            {
                ArrayType result;
                result[ 0 ] = _mm_cvtsi128_si32( src );
                return result;
            }
            else if constexpr ( N == 2 )
            {
                alignas( AlignAs ) ArrayType result;
                _mm_store_sd( reinterpret_cast< double* >( result.data( ) ), _mm_castsi128_pd( src ) );
                return result;
            }
            else if constexpr ( N == 3 )
            {
                alignas( AlignAs ) ArrayType result;
                auto srcd = _mm_castsi128_pd( src );
                _mm_store_sd( reinterpret_cast< double* >( result.data( ) ), srcd );
                result[ 2 ] = std::bit_cast< Type >( _mm_extract_epi32( src, 2 ) );
                return result;
            }
            else if constexpr ( N == 4 )
            {
                alignas( AlignAs ) ArrayType result;
                _mm_store_si128( reinterpret_cast< __m128i* >( result.data( ) ), src );
                return result;
            }
            else if constexpr ( N == 8 )
            {
                alignas( AlignAs ) ArrayType result;
                Store( result.data( ), src );
                return result;
            }
            else
            {
                alignas( AlignAs ) std::array<Type, SIMDTypeCapacity> tmp;
                Store( tmp.data( ), src );
                return[ &tmp ] <std::size_t... I>
                    ( std::index_sequence<I...> )
                {
                    ArrayType result;
                    ( ( result[ I ] = tmp[ I ] ), ... );
                    return result;
                }( std::make_index_sequence<N>( ) );
            }
        }

        /// <summary>
        /// Returns a SIMDType with all elements set to the
        /// value of <c>v[index]</c>.
        /// </summary>
        /// <typeparam name="index">
        /// The index of the value, in <c>v</c> to assign to ell the elements
        /// of the result, 
        /// </typeparam>
        /// <param name="v">
        /// The SIMDType type containing the the source value.
        /// </param>
        /// <returns>
        /// A SIMDType with all elements set to the
        /// value of <c>v[index]</c>.
        /// </returns>
        template<size_t index>
            requires ( index < Size )
        static SIMDType At( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( index == 0 )
                {
                    return _mm_shuffle_epi32( v, _MM_SHUFFLE( 0, 0, 0, 0 ) );
                }
                else if constexpr ( index == 1 )
                {
                    return _mm_shuffle_epi32( v, _MM_SHUFFLE( 1, 1, 1, 1 ) );
                }
                else if constexpr ( index == 2 )
                {
                    return _mm_shuffle_epi32( v, _MM_SHUFFLE( 2, 2, 2, 2 ) );
                }
                else
                {
                    return _mm_shuffle_epi32( v, _MM_SHUFFLE( 3, 3, 3, 3 ) );
                }
            }
            else
            {
                if constexpr ( index < 4 )
                {
                    auto low = _mm256_castsi256_si128( v );
                    if constexpr ( index == 0 )
                    {
                        return _mm256_broadcastd_epi32( low );
                    }
                    else if constexpr ( index == 1 )
                    {
                        return _mm256_broadcastd_epi32( _mm_shuffle_epi32( low, _MM_SHUFFLE( 1, 1, 1, 1 ) ) );
                    }
                    else if constexpr ( index == 2 )
                    {
                        return _mm256_broadcastd_epi32( _mm_shuffle_epi32( low, _MM_SHUFFLE( 2, 2, 2, 2 ) ) );
                    }
                    else
                    {
                        return _mm256_broadcastd_epi32( _mm_shuffle_epi32( low, _MM_SHUFFLE( 3, 3, 3, 3 ) ) );
                    }
                }
                else
                {
                    auto high = _mm256_extractf128_si256( v, 1 );
                    if constexpr ( index == 4 )
                    {
                        return _mm256_broadcastd_epi32( high );
                    }
                    else if constexpr ( index == 5 )
                    {
                        return _mm256_broadcastd_epi32( _mm_shuffle_epi32( high, _MM_SHUFFLE( 1, 1, 1, 1 ) ) );
                    }
                    else if constexpr ( index == 6 )
                    {
                        return _mm256_broadcastd_epi32( _mm_shuffle_epi32( high, _MM_SHUFFLE( 2, 2, 2, 2 ) ) );
                    }
                    else
                    {
                        return _mm256_broadcastd_epi32( _mm_shuffle_epi32( high, _MM_SHUFFLE( 3, 3, 3, 3 ) ) );
                    }
                }
            }
        }

        /// <summary>
        /// Returns the value of <c>v[index]</c>.
        /// </summary>
        /// <typeparam name="index">
        /// The index of the value, in <c>v</c>.
        /// </typeparam>
        /// <param name="v">
        /// The SIMDType type containing the the source value.
        /// </param>
        /// <returns>
        /// The value of <c>v[index]</c>.
        /// </returns>
        template<size_t index>
            requires ( index < Size )
        static Type Extract( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( index == 0 )
                {
                    return _mm_cvtsi128_si32( v );
                }
                else if constexpr ( index == 1 )
                {
                    return _mm_extract_epi32( v, 1 );
                }
                else if constexpr ( index == 2 )
                {
                    return _mm_extract_epi32( v, 2 );
                }
                else
                {
                    return _mm_extract_epi32( v, 3 );
                }
            }
            else
            {
                if constexpr ( index < 4 )
                {
                    auto low = _mm256_castsi256_si128( v );
                    if constexpr ( index == 0 )
                    {
                        return _mm_cvtsi128_si32( low );
                    }
                    else if constexpr ( index == 1 )
                    {
                        return _mm_extract_epi32( low, 1 );
                    }
                    else if constexpr ( index == 2 )
                    {
                        return _mm_extract_epi32( low, 2 );
                    }
                    else
                    {
                        return _mm_extract_epi32( low, 3 );
                    }
                }
                else
                {
                    auto high = _mm256_extractf128_si256( v, 1 );
                    if constexpr ( index == 4 )
                    {
                        return _mm_cvtsi128_si32( high );
                    }
                    else if constexpr ( index == 5 )
                    {
                        return _mm_extract_epi32( high, 1 );
                    }
                    else if constexpr ( index == 6 )
                    {
                        return _mm_extract_epi32( high, 2 );
                    }
                    else
                    {
                        return _mm_extract_epi32( high, 3 );
                    }
                }
            }
        }

        /// <summary>
        /// Checks whether a SIMD value contains any NaN (Not-a-Number) elements.
        /// </summary>
        /// <param name="v">The SIMD value to check for NaN elements.</param>
        /// <returns>
        /// Always returns false, indicating no NaN elements are present 
        /// since integer types cannot represent NaN.
        /// </returns>
        static constexpr bool HasNaN( SIMDType v ) noexcept
        {
            return false;
        }

        /// <summary>
        /// Compute the bitwise AND of packed 32-bit integer 
        /// elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        static SIMDType And( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_and_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_and_epi32( lhs, rhs );
            }
        }

        /// <summary>
        /// Compute the bitwise NOT of packed 32-bit integer 
        /// elements in <c>lhs</c> and then AND with <c>rhs</c>, returning the results.
        /// </summary>
        static SIMDType AndNot( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_andnot_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_andnot_epi32( lhs, rhs );
            }
        }

        /// <summary>
        /// Compute the bitwise OR of packed 32-bit integer 
        /// elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        static SIMDType Or( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_or_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_or_epi32( lhs, rhs );
            }
        }

        /// <summary>
        /// Compute the bitwise XOR of packed 32-bit integer 
        /// elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        static SIMDType Xor( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_xor_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_xor_epi32( lhs, rhs );
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
        /// Add Horizontal 32 bit integer values
        /// </summary>
        /// <param name="lhs">32 bit integer vector used for the left-hand side of the operation</param>
        /// <param name="rhs">32 bit integer vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Adds pairs of adjacent 32 bit integer values from the first 
        /// source operand, lhs, and the second source operand, rhs.
        /// </remarks>
        /// <returns>Result of the addition operation</returns>
        static SIMDType HAdd( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_hadd_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_hadd_epi32( lhs, rhs );
            }
        }

        /// <summary>
        /// Computes the horizontal sum of all elements in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector whose elements will be summed.</param>
        /// <returns>A SIMD vector with all lanes containing the sum of all elements from the input vector.</returns>
        static SIMDType HSum( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return v;
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_add_epi32( _mm_shuffle_epi32( v, 0b01'00'01'00 ), _mm_shuffle_epi32( v, 0b00'01'00'01 ) );
                }
                else if constexpr ( N == 3 )
                {
                    return _mm_add_epi32( _mm_shuffle_epi32( v, _MM_SHUFFLE( 0, 2, 1, 0 ) ), _mm_add_epi32( _mm_shuffle_epi32( v, _MM_SHUFFLE( 1, 1, 0, 2 ) ), _mm_shuffle_epi32( v, _MM_SHUFFLE( 2, 0, 2, 1 ) ) ) );
                }
                else
                {
                    return _mm_add_epi32( _mm_add_epi32( v, _mm_shuffle_epi32( v, 0b10'01'00'11 ) ),
                        _mm_add_epi32( _mm_shuffle_epi32( v, 0b01'00'11'10 ), _mm_shuffle_epi32( v, 0b00'11'10'01 ) ) );
                }
            }
            else
            {
                __m128i low = _mm256_castsi256_si128( v );
                __m128i high = _mm256_extractf128_si256( v, 1 );
                __m128i r1 = _mm_add_epi32( low, high );
                __m128i r2 = _mm_add_epi32( r1, _mm_castps_si128( _mm_movehl_ps( _mm_castsi128_ps( r1 ), _mm_castsi128_ps( r1 ) ) ) );
                return _mm256_broadcastd_epi32( _mm_add_epi32( r2, _mm_castps_si128( _mm_movehdup_ps( _mm_castsi128_ps( r2 ) ) ) ) );
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

        /// <summary>
        /// Multiplies corresponding 32-bit integer elements from two SIMD vectors and returns 64-bit results.
        /// </summary>
        /// <param name="lhs">The left-hand side SIMD vector containing 32-bit integer elements.</param>
        /// <param name="rhs">The right-hand side SIMD vector containing 32-bit integer elements.</param>
        /// <returns>A SIMD vector containing the 64-bit products of the multiplied elements. Uses either 128-bit (_mm_mul_epi32) or 256-bit (_mm256_mul_epi32) SIMD instructions based on the UseShortSIMDType compile-time condition.</returns>
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

        /// <summary>
        /// Multiplies a scalar value with a SIMD vector by broadcasting the scalar to all vector lanes.
        /// </summary>
        /// <param name="lhs">The scalar value to multiply.</param>
        /// <param name="rhs">The SIMD vector to multiply with.</param>
        /// <returns>A SIMD vector containing the element-wise product of the broadcasted scalar and the input vector.</returns>
        static SIMDType Mul( Type lhs, SIMDType rhs ) noexcept
        {
            return Mul( Fill( lhs ), rhs );
        }

        /// <summary>
        /// Multiplies a SIMD vector by a scalar value.
        /// </summary>
        /// <param name="lhs">The SIMD vector (left-hand side operand).</param>
        /// <param name="rhs">The scalar value (right-hand side operand) to multiply with each element of the vector.</param>
        /// <returns>A SIMD vector containing the result of multiplying each element of the input vector by the scalar value.</returns>
        static SIMDType Mul( SIMDType lhs, Type rhs ) noexcept
        {
            return Mul( lhs, Fill( rhs ) );
        }

        /// <summary>
        /// Computes the element-wise minimum of two SIMD vectors containing 32-bit signed integers.
        /// </summary>
        /// <param name="lhs">The first SIMD vector.</param>
        /// <param name="rhs">The second SIMD vector.</param>
        /// <returns>A SIMD vector where each element is the minimum of the corresponding elements from lhs and rhs.</returns>
        static SIMDType Min( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_min_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_min_epi32( lhs, rhs );
            }
        }

        /// <summary>
        /// Computes the element-wise maximum of two SIMD vectors containing 32-bit signed integers.
        /// </summary>
        /// <param name="lhs">The first SIMD vector to compare.</param>
        /// <param name="rhs">The second SIMD vector to compare.</param>
        /// <returns>A SIMD vector containing the maximum values from each corresponding element pair.</returns>
        static SIMDType Max( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_max_epi32( lhs, rhs );
            }
            else
            {
                return _mm256_max_epi32( lhs, rhs );
            }
        }

        /// <summary>
        /// Clamps a SIMD vector of integers to a specified range by restricting each element to be within the lower and upper bounds.
        /// </summary>
        /// <param name="v">The SIMD vector to clamp.</param>
        /// <param name="lowerBounds">The SIMD vector containing the minimum allowed values for each element.</param>
        /// <param name="upperBounds">The SIMD vector containing the maximum allowed values for each element.</param>
        /// <returns>A SIMD vector where each element of v is clamped to be within the corresponding elements of lowerBounds and upperBounds.</returns>
        static SIMDType Clamp( SIMDType v, SIMDType lowerBounds, SIMDType upperBounds ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_min_epi32( upperBounds, _mm_max_epi32( lowerBounds, v ) );
            }
            else
            {
                return _mm256_min_epi32( upperBounds, _mm256_max_epi32( lowerBounds, v ) );
            }
        }


    };

    /// <summary>
    /// Specialization of Traits for Int32 types with a compile-time size parameter.
    /// </summary>
    /// <typeparam name="N">The compile-time size parameter for the Int32 traits specialization.</typeparam>
    template<size_t N>
    struct Traits<Int32, N> : public Traits32Bit<Int32, N>
    {
    };

    /// <summary>
    /// Specialization of Traits for UInt32 types with a specified size, inheriting from Traits32Bit.
    /// </summary>
    /// <typeparam name="N">The size parameter for the traits specialization.</typeparam>
    template<size_t N>
    struct Traits<UInt32, N> : public Traits32Bit<UInt32, N>
    {
    };


    /// <summary>
    /// Provides SIMD traits and operations for 64-bit integer types, optimizing for either SSE (128-bit) or AVX2 (256-bit) instruction sets based on vector size.
    /// </summary>
    /// <typeparam name="T">The 64-bit element type (e.g., int64_t, uint64_t).</typeparam>
    /// <typeparam name="N">The number of elements in the vector.</typeparam>
    template<typename T, size_t N>
    struct Traits64Bit : public Internal::TraitsBase
    {
        using Type = T;
        static constexpr size_t Size = N;
    private:
        static constexpr bool UseShortSIMDType = N <= 2;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128i>, SIMD::DataTypeTraits<DataType::m256i> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        using ArrayType = std::array<Type, N>;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t SIMDTypeCapacity = UseShortSIMDType ? 2 : 4;
        static constexpr size_t Capacity = UseShortSIMDType ? 2 : ( ( N + 3 ) & static_cast< Int64 >( -4 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

        /// <summary>
        /// Returns a SIMD vector with all elements set to zero.
        /// </summary>
        /// <returns>A SIMD vector of type SIMDType with all bits set to zero. Returns a 128-bit vector if UseShortSIMDType is true, otherwise returns a 256-bit vector.</returns>
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

        /// <summary>
        /// Fills a SIMD vector with a single value replicated across all elements.
        /// </summary>
        /// <param name="value">The value to replicate across all elements of the SIMD vector.</param>
        /// <returns>A SIMD vector with the specified value replicated in all lanes. Returns either a 128-bit (__m128i) or 256-bit (__m256i) SIMD type depending on the UseShortSIMDType constant.</returns>
        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set1_epi64x( std::bit_cast< long long >( value ) );
            }
            else
            {
                return _mm256_set1_epi64x( std::bit_cast< long long >( value ) );
            }
        }

        /// <summary>
        /// Loads SIMD data from an aligned memory address.
        /// </summary>
        /// <param name="src">Pointer to the aligned memory location from which to load data. Must be aligned to 16 bytes for SSE (_mm_load_si128) or 32 bytes for AVX (_mm256_load_si256).</param>
        /// <returns>A SIMD vector containing the loaded data. Returns a 128-bit vector (__m128i) if UseShortSIMDType is true, otherwise returns a 256-bit vector (__m256i).</returns>
        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_load_si128( reinterpret_cast< const __m128i* >( src ) );
            }
            else
            {
                return _mm256_load_si256( reinterpret_cast< const __m256i* >( src ) );
            }
        }

        /// <summary>
        /// Loads SIMD data from an unaligned memory address.
        /// </summary>
        /// <param name="src">Pointer to the source memory location from which to load data. The memory does not need to be aligned.</param>
        /// <returns>A SIMD vector containing the loaded data. Returns a 128-bit vector (__m128i) if UseShortSIMDType is true, otherwise returns a 256-bit vector (__m256i).</returns>
        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) );
            }
            else
            {
                return _mm256_loadu_si256( reinterpret_cast< const __m256i* >( src ) );
            }
        }

        /// <summary>
        /// Stores a SIMD vector to an aligned memory location.
        /// </summary>
        /// <param name="dest">Pointer to the destination memory location where the SIMD data will be stored. Must be properly aligned (16-byte for SSE, 32-byte for AVX).</param>
        /// <param name="src">The SIMD vector to store.</param>
        static void Store( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_store_si128( reinterpret_cast< __m128i* >( dest ), src );
            }
            else
            {
                _mm256_store_si256( reinterpret_cast< __m128i* >( dest ), src );
            }
        }

        /// <summary>
        /// Stores a SIMD vector to an unaligned memory location.
        /// </summary>
        /// <param name="dest">Pointer to the destination memory location where the SIMD vector will be stored. Does not need to be aligned.</param>
        /// <param name="src">The SIMD vector to store.</param>
        static void UnalignedStore( Type* dest, SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                _mm_storeu_si128( reinterpret_cast< __m128i* >( dest ), src );
            }
            else
            {
                _mm256_storeu_si256( reinterpret_cast< __m128i* >( dest ), src );
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

        /// <summary>
        /// Multiplies two SIMD vectors containing 64-bit unsigned integers.
        /// </summary>
        /// <param name="a">The first SIMD vector containing 64-bit values to multiply.</param>
        /// <param name="b">The second SIMD vector containing 64-bit values to multiply.</param>
        /// <returns>A SIMD vector containing the product of the corresponding 64-bit elements from the input vectors.</returns>
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

    /// <summary>
    /// Specialization of Traits for Int64 types with a specified size.
    /// </summary>
    /// <typeparam name="N">The size parameter for the traits specialization.</typeparam>
    template<size_t N>
    struct Traits<Int64, N> : public Traits64Bit<Int64, N>
    {
    };

    /// <summary>
    /// Specialization of the Traits template for UInt64 types with a specified size parameter.
    /// </summary>
    /// <typeparam name="N">The size parameter for the UInt64 traits specialization.</typeparam>
    template<size_t N>
    struct Traits<UInt64, N> : public Traits64Bit<UInt64, N>
    {
    };

    namespace Internal
    {
        struct Constants
        {
            using ValueType = float;
            static constexpr ValueType MinusOne = -1.f;
            static constexpr ValueType MinusZero = -0.f;
            static constexpr ValueType EpsilonValue = 1.192092896e-7f;

            static constexpr ValueType Zero = 0.f;
            static constexpr ValueType One = 1.f;
            static constexpr ValueType Two = 2.f;
            static constexpr ValueType Three = 3.f;

            static constexpr ValueType BitsSet = std::bit_cast< ValueType >( 0xFFFFFFFFU );
            static constexpr ValueType BitsClear = std::bit_cast< ValueType >( 0U );
            static constexpr ValueType SignMaskValue = std::bit_cast< ValueType >( 0x80000000U );

            static constexpr ValueType InfinityValue = std::bit_cast< ValueType >( 0x7F800000U );
            static constexpr ValueType NegativeInfinityValue = std::bit_cast< ValueType >( 0xFF800000U );
            static constexpr ValueType QNaNValue = std::bit_cast< ValueType >( 0x7FC00000U );
            static constexpr ValueType QNaNTestValue = std::bit_cast< ValueType >( 0x007FFFFFU );
            static constexpr ValueType AbsMaskValue = std::bit_cast< ValueType >( 0x7FFFFFFF );
            static constexpr ValueType FltMinValue = std::bit_cast< ValueType >( 0x00800000 );
            static constexpr ValueType FltMaxValue = std::bit_cast< ValueType >( 0x7F7FFFFF );
            static constexpr ValueType NegOneMaskValue = std::bit_cast< ValueType >( 0xFFFFFFFF );

            static constexpr ValueType Pi = static_cast< ValueType >( 3.14159265358979323846 );
            static constexpr ValueType NegativePi = -Pi;
            static constexpr ValueType PiTimes2 = static_cast< ValueType >( 2. * Pi );
            static constexpr ValueType InvPi = static_cast< ValueType >( 0.31830988618379067154 );
            static constexpr ValueType Inv2Pi = static_cast< ValueType >( 0.15915494309189533577 );
            static constexpr ValueType Inv4Pi = static_cast< ValueType >( 0.07957747154594766788 );
            static constexpr ValueType PiOver2 = static_cast< ValueType >( 1.57079632679489661923 );
            static constexpr ValueType PiOver4 = static_cast< ValueType >( 0.78539816339744830961 );
            static constexpr ValueType Sqrt2 = static_cast< ValueType >( 1.41421356237309504880 );
            static constexpr ValueType TwoOverPi = static_cast< ValueType >( 2. / Pi );
            static constexpr ValueType ThreePiOver4 = static_cast< ValueType >( ( 3. * Pi ) / 4. );

        };
        struct m128Constants : Constants
        {
            using Base = Constants;
            using SIMDType = __m128;
            static constexpr SIMDType SinCoefficient1 = { {-2.3889859e-08f,-2.3889859e-08f,-2.3889859e-08f,-2.3889859e-08f} };
            static constexpr SIMDType SinCoefficient2 = { { +2.7525562e-06f, +2.7525562e-06f, +2.7525562e-06f, +2.7525562e-06f } };
            static constexpr SIMDType SinCoefficient3 = { {-0.00019840874f,-0.00019840874f,-0.00019840874f,-0.00019840874f} };
            static constexpr SIMDType SinCoefficient4 = { {+0.0083333310f,+0.0083333310f,+0.0083333310f,+0.0083333310f} };
            static constexpr SIMDType SinCoefficient5 = { {-0.16666667f,-0.16666667f,-0.16666667f,-0.16666667f} };

            static constexpr SIMDType CosCoefficient1 = { {-2.6051615e-07f,-2.6051615e-07f,-2.6051615e-07f,-2.6051615e-07f} };
            static constexpr SIMDType CosCoefficient2 = { {+2.4760495e-05f,+2.4760495e-05f,+2.4760495e-05f,+2.4760495e-05f} };
            static constexpr SIMDType CosCoefficient3 = { {-0.0013888378f,-0.0013888378f,-0.0013888378f,-0.0013888378f} };
            static constexpr SIMDType CosCoefficient4 = { {+0.041666638f,+0.041666638f,+0.041666638f,+0.041666638f} };
            static constexpr SIMDType CosCoefficient5 = { { -0.5f,-0.5f,-0.5f,-0.5f } };

            static constexpr __m256 SinCosCoefficient1 = { {-2.3889859e-08f,-2.3889859e-08f,-2.3889859e-08f,-2.3889859e-08f ,-2.6051615e-07f,-2.6051615e-07f,-2.6051615e-07f,-2.6051615e-07f} };
            static constexpr __m256 SinCosCoefficient2 = { {+2.7525562e-06f, +2.7525562e-06f, +2.7525562e-06f, +2.7525562e-06f, +2.4760495e-05f,+2.4760495e-05f,+2.4760495e-05f,+2.4760495e-05f} };
            static constexpr __m256 SinCosCoefficient3 = { {-0.00019840874f,-0.00019840874f,-0.00019840874f,-0.00019840874f, -0.0013888378f,-0.0013888378f,-0.0013888378f,-0.0013888378f} };
            static constexpr __m256 SinCosCoefficient4 = { {+0.0083333310f,+0.0083333310f,+0.0083333310f,+0.0083333310f, +0.041666638f,+0.041666638f,+0.041666638f,+0.041666638f} };
            static constexpr __m256 SinCosCoefficient5 = { {-0.16666667f,-0.16666667f,-0.16666667f,-0.16666667f, -0.5f,-0.5f,-0.5f,-0.5f } };
            static constexpr __m256 One8 = { { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f } };

            static constexpr SIMDType TanCoefficient1 = { {1.0f,1.0f,1.0f,1.0f} };
            static constexpr SIMDType TanCoefficient2 = { {-4.667168334e-1f,-4.667168334e-1f,-4.667168334e-1f,-4.667168334e-1f} };
            static constexpr SIMDType TanCoefficient3 = { {2.566383229e-2f,2.566383229e-2f,2.566383229e-2f,2.566383229e-2f} };
            static constexpr SIMDType TanCoefficient4 = { {-3.118153191e-4f,-3.118153191e-4f,-3.118153191e-4f,-3.118153191e-4f} };
            static constexpr SIMDType TanCoefficient5 = { {4.981943399e-7f,4.981943399e-7f,4.981943399e-7f,4.981943399e-7f} };
            static constexpr SIMDType TanCoefficient6 = { {-1.333835001e-1f,-1.333835001e-1f,-1.333835001e-1f,-1.333835001e-1f} };
            static constexpr SIMDType TanCoefficient7 = { {3.424887824e-3f,3.424887824e-3f,3.424887824e-3f,3.424887824e-3f} };
            static constexpr SIMDType TanCoefficient8 = { {-1.786170734e-5f,-1.786170734e-5f,-1.786170734e-5f,-1.786170734e-5f} };
            static constexpr SIMDType TanCoefficient9 = { {6.077100628e-11f, 6.077100628e-11f, 6.077100628e-11f, 6.077100628e-11f } };
            static constexpr SIMDType TanNearZero = { { 0.000244140625f,0.000244140625f,0.000244140625f,0.000244140625f } };

            static constexpr SIMDType ATanCoefficient1 = { {-0.3333314528f,-0.3333314528f,-0.3333314528f,-0.3333314528f} };
            static constexpr SIMDType ATanCoefficient2 = { {+0.1999355085f,+0.1999355085f,+0.1999355085f,+0.1999355085f} };
            static constexpr SIMDType ATanCoefficient3 = { {-0.1420889944f,-0.1420889944f,-0.1420889944f,-0.1420889944f} };
            static constexpr SIMDType ATanCoefficient4 = { {+0.1065626393f,+0.1065626393f,+0.1065626393f,+0.1065626393f} };
            static constexpr SIMDType ATanCoefficient5 = { {-0.0752896400f,-0.0752896400f,-0.0752896400f,-0.0752896400f} };
            static constexpr SIMDType ATanCoefficient6 = { {+0.0429096138f,+0.0429096138f,+0.0429096138f,+0.0429096138f} };
            static constexpr SIMDType ATanCoefficient7 = { {-0.0161657367f,-0.0161657367f,-0.0161657367f,-0.0161657367f} };
            static constexpr SIMDType ATanCoefficient8 = { {+0.0028662257f,+0.0028662257f,+0.0028662257f,+0.0028662257f} };


            static constexpr SIMDType ArcCoefficients0 = { { +1.5707963050f, -0.2145988016f, +0.0889789874f, -0.0501743046f } };
            static constexpr SIMDType ArcCoefficients1 = { { +0.0308918810f, -0.0170881256f, +0.0066700901f, -0.0012624911f } };
            static constexpr SIMDType PiConstants0 = { { Pi, PiTimes2, InvPi, Inv2Pi } };
            static constexpr SIMDType IdentityR1 = { { 1.0f, 0.0f, 0.0f, 0.0f } };
            static constexpr SIMDType IdentityR2 = { { 0.0f, 1.0f, 0.0f, 0.0f } };
            static constexpr SIMDType IdentityR3 = { { 0.0f, 0.0f, 1.0f, 0.0f } };
            static constexpr SIMDType IdentityR4 = { { 0.0f, 0.0f, 0.0f, 1.0f } };
            static constexpr SIMDType NegIdentityR1 = { { -1.0f, 0.0f, 0.0f, 0.0f } };
            static constexpr SIMDType NegIdentityR2 = { { 0.0f, -1.0f, 0.0f, 0.0f } };
            static constexpr SIMDType NegIdentityR3 = { { 0.0f, 0.0f, -1.0f, 0.0f } };
            static constexpr SIMDType NegIdentityR4 = { { 0.0f, 0.0f, 0.0f, -1.0f } };
            static constexpr SIMDType NegativeZero = { { MinusZero, MinusZero, MinusZero, MinusZero } };
            static constexpr SIMDType Negate3 = { { SignMaskValue, SignMaskValue, SignMaskValue, 0x00000000 } };
            static constexpr SIMDType MaskXY = { { BitsSet, BitsSet, 0x00000000, 0x00000000 } };
            static constexpr SIMDType Mask3 = { { BitsSet, BitsSet, BitsSet, 0x00000000 } };
            static constexpr SIMDType MaskX = { { BitsSet, 0x00000000, 0x00000000, 0x00000000 } };
            static constexpr SIMDType MaskY = { { 0x00000000, BitsSet, 0x00000000, 0x00000000 } };
            static constexpr SIMDType MaskZ = { { 0x00000000, 0x00000000, BitsSet, 0x00000000 } };
            static constexpr SIMDType MaskW = { { 0x00000000, 0x00000000, 0x00000000, BitsSet } };
            static constexpr SIMDType NegateX = { { -1.0f, 1.0f, 1.0f, 1.0f } };
            static constexpr SIMDType NegateY = { { 1.0f, -1.0f, 1.0f, 1.0f } };
            static constexpr SIMDType NegateZ = { { 1.0f, 1.0f, -1.0f, 1.0f } };
            static constexpr SIMDType NegateW = { { 1.0f, 1.0f, 1.0f, -1.0f } };
            static constexpr SIMDType One = { { 1.0f, 1.0f, 1.0f, 1.0f } };
            static constexpr SIMDType One3 = { { 1.0f, 1.0f, 1.0f, 0.0f } };
            static constexpr SIMDType Zero = { { 0.0f, 0.0f, 0.0f, 0.0f } };
            static constexpr SIMDType Two = { { 2.f, 2.f, 2.f, 2.f } };
            static constexpr SIMDType Four = { { 4.f, 4.f, 4.f, 4.f } };
            static constexpr SIMDType Six = { { 6.f, 6.f, 6.f, 6.f } };
            static constexpr SIMDType NegativeOne = { { -1.0f, -1.0f, -1.0f, -1.0f } };
            static constexpr SIMDType OneHalf = { { 0.5f, 0.5f, 0.5f, 0.5f } };
            static constexpr SIMDType NegativeOneHalf = { { -0.5f, -0.5f, -0.5f, -0.5f } };
            static constexpr SIMDType NegativeTwoPi = { { -Base::PiTimes2, -Base::PiTimes2, -Base::PiTimes2, -Base::PiTimes2 } };
            static constexpr SIMDType NegativePi = { { Base::NegativePi, Base::NegativePi, Base::NegativePi, Base::NegativePi } };
            static constexpr SIMDType HalfPi = { { Base::PiOver2, Base::PiOver2, Base::PiOver2, Base::PiOver2 } };
            static constexpr SIMDType Pi = { { Base::Pi, Base::Pi, Base::Pi, Base::Pi } };
            static constexpr SIMDType ReciprocalPi = { { Base::InvPi, Base::InvPi, Base::InvPi, Base::InvPi } };
            static constexpr SIMDType TwoPi = { { Base::PiTimes2, Base::PiTimes2, Base::PiTimes2, Base::PiTimes2 } };
            static constexpr SIMDType TwoOverPi = { { Base::TwoOverPi, Base::TwoOverPi, Base::TwoOverPi, Base::TwoOverPi } };
            static constexpr SIMDType ReciprocalTwoPi = { { Base::Inv2Pi, Base::Inv2Pi, Base::Inv2Pi, Base::Inv2Pi} };
            static constexpr SIMDType PiOver4 = { {Base::PiOver4,Base::PiOver4,Base::PiOver4,Base::PiOver4} };
            static constexpr SIMDType ThreePiOver4 = { {Base::ThreePiOver4,Base::ThreePiOver4,Base::ThreePiOver4,Base::ThreePiOver4} };
            static constexpr SIMDType Epsilon = { { 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f } };
            static constexpr SIMDType Infinity = { { Base::InfinityValue, Base::InfinityValue, Base::InfinityValue, Base::InfinityValue } };
            static constexpr SIMDType NegativeInfinity = { { Base::NegativeInfinityValue, Base::NegativeInfinityValue, Base::NegativeInfinityValue, Base::NegativeInfinityValue } };
            static constexpr SIMDType QNaN = { { Base::QNaNValue, Base::QNaNValue, Base::QNaNValue, Base::QNaNValue } };
            static constexpr SIMDType QNaNTest = { { Base::QNaNTestValue, Base::QNaNTestValue, Base::QNaNTestValue, Base::QNaNTestValue } };
            static constexpr SIMDType AbsMask = { { Base::AbsMaskValue, Base::AbsMaskValue, Base::AbsMaskValue, Base::AbsMaskValue } };
            static constexpr SIMDType AbsXMask = { { Base::AbsMaskValue, Base::BitsSet, Base::BitsSet, Base::BitsSet } };
            static constexpr SIMDType AbsYMask = { { Base::BitsSet, Base::AbsMaskValue, Base::BitsSet, Base::BitsSet } };
            static constexpr SIMDType AbsZMask = { { Base::BitsSet, Base::BitsSet, Base::AbsMaskValue, Base::BitsSet } };
            static constexpr SIMDType AbsWMask = { { Base::BitsSet, Base::BitsSet, Base::BitsSet, Base::AbsMaskValue } };
            static constexpr SIMDType FltMin = { { Base::FltMinValue, Base::FltMinValue, Base::FltMinValue, Base::FltMinValue } };
            static constexpr SIMDType FltMax = { { Base::FltMaxValue, Base::FltMaxValue, Base::FltMaxValue, Base::FltMaxValue } };
            static constexpr SIMDType NegOneMask = { { Base::NegOneMaskValue, Base::NegOneMaskValue, Base::NegOneMaskValue, Base::NegOneMaskValue } };

            //static constexpr SIMDType Select1111 = { { BitsClear, BitsClear, BitsClear, BitsClear } };

            static constexpr SIMDType Select2111 = { { Base::BitsSet, Base::BitsClear, Base::BitsClear, Base::BitsClear } };
            static constexpr SIMDType Select1211 = { { Base::BitsClear, Base::BitsSet, Base::BitsClear, Base::BitsClear } };
            static constexpr SIMDType Select2211 = { { Base::BitsSet, Base::BitsSet, Base::BitsClear, Base::BitsClear } };
            static constexpr SIMDType Select1121 = { { Base::BitsClear, Base::BitsClear, Base::BitsSet, Base::BitsClear } };
            static constexpr SIMDType Select2121 = { { Base::BitsSet, Base::BitsClear, Base::BitsSet, Base::BitsClear } };
            static constexpr SIMDType Select1221 = { { Base::BitsClear, Base::BitsSet, Base::BitsSet, Base::BitsClear } };
            static constexpr SIMDType Select2221 = { { Base::BitsSet, Base::BitsSet, Base::BitsSet, Base::BitsClear } };
            static constexpr SIMDType Select1112 = { { Base::BitsClear, Base::BitsClear, Base::BitsClear, Base::BitsSet } };

            static constexpr SIMDType Select2112 = { { Base::BitsSet, Base::BitsClear, Base::BitsClear, Base::BitsSet } };
            static constexpr SIMDType Select1212 = { { Base::BitsClear, Base::BitsSet, Base::BitsClear, Base::BitsSet } };
            static constexpr SIMDType Select2212 = { { Base::BitsSet, Base::BitsSet, Base::BitsClear, Base::BitsSet } };
            static constexpr SIMDType Select1122 = { { Base::BitsClear, Base::BitsClear, Base::BitsSet, Base::BitsSet } };
            static constexpr SIMDType Select2122 = { { Base::BitsSet, Base::BitsClear, Base::BitsSet, Base::BitsSet } };
            static constexpr SIMDType Select1222 = { { Base::BitsClear, Base::BitsSet, Base::BitsSet, Base::BitsSet } };

            //static constexpr SIMDType Select2222 = { { BitsSet, BitsSet, BitsSet, BitsSet } };

            static constexpr SIMDType True = { { Base::BitsSet, Base::BitsSet, Base::BitsSet, Base::BitsSet } };

        };
        struct m256Constants : Constants
        {
            using Base = Constants;
            using SIMDType = __m256;
        };
    }

    /// <summary>
	/// Specialization of the Traits template for float types with a specified size parameter.
    /// </summary>
    /// <typeparam name="N"></typeparam>
    template<size_t N>
    struct Traits<float, N> : public Internal::TraitsBase
    {
        using Type = float;
        using UIntType = UInt32;
        static constexpr size_t Size = N;
    private:
        static constexpr bool UseShortSIMDType = N <= 4;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128>, SIMD::DataTypeTraits<DataType::m256> >;
    public:
        using Constants = std::conditional_t<UseShortSIMDType, Internal::m128Constants, Internal::m256Constants>;
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        using SIMDIntegerType = typename DataTypeTraits::IntegerType;
        using ArrayType = std::array<Type, N>;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t SIMDTypeCapacity = UseShortSIMDType ? 4 : 8;
        static constexpr size_t Capacity = UseShortSIMDType ? 4 : ( ( N + 7 ) & static_cast< Int64 >( -8 ) );
        static constexpr size_t SIMDIterations = ( Capacity * sizeof( Type ) ) / SIMDTypeSize;

    private:
        /// <summary>
        /// Provides constant indices for selecting components from 128-bit SIMD vectors.
        /// </summary>
        struct m128Select
        {
            static constexpr UInt32 X = 0;
            static constexpr UInt32 Y = 1;
            static constexpr UInt32 Z = 2;
            static constexpr UInt32 W = 3;

            static constexpr UInt32 V0 = 0;
            static constexpr UInt32 V1 = 1;
            static constexpr UInt32 V2 = 2;
            static constexpr UInt32 V3 = 3;
        };

        /// <summary>
        /// Provides constants for selecting components from 256-bit SIMD vectors.
        /// </summary>
        struct m256Select
        {
            static constexpr UInt32 X0 = 0;
            static constexpr UInt32 Y0 = 1;
            static constexpr UInt32 Z0 = 2;
            static constexpr UInt32 W0 = 3;
            static constexpr UInt32 X1 = 4;
            static constexpr UInt32 Y1 = 5;
            static constexpr UInt32 Z1 = 6;
            static constexpr UInt32 W1 = 7;

            static constexpr UInt32 V0 = 0;
            static constexpr UInt32 V1 = 1;
            static constexpr UInt32 V2 = 2;
            static constexpr UInt32 V3 = 3;
            static constexpr UInt32 V4 = 4;
            static constexpr UInt32 V5 = 5;
            static constexpr UInt32 V6 = 6;
            static constexpr UInt32 V7 = 7;
        };

        /// <summary>
        /// Defines constants for permuting elements in 128-bit SIMD vectors.
        /// </summary>
        struct m128Permute
        {
            static constexpr UInt32 X1 = 0;
            static constexpr UInt32 Y1 = 1;
            static constexpr UInt32 Z1 = 2;
            static constexpr UInt32 W1 = 3;
            static constexpr UInt32 X2 = 4;
            static constexpr UInt32 Y2 = 5;
            static constexpr UInt32 Z2 = 6;
            static constexpr UInt32 W2 = 7;

            static constexpr UInt32 V11 = 0;
            static constexpr UInt32 V12 = 1;
            static constexpr UInt32 V13 = 2;
            static constexpr UInt32 V14 = 3;
            static constexpr UInt32 V21 = 4;
            static constexpr UInt32 V22 = 5;
            static constexpr UInt32 V23 = 6;
            static constexpr UInt32 V24 = 7;
        };

    public:
        using SelectType = std::conditional_t<UseShortSIMDType, m128Select, m256Select>;
        using PermuteType = m128Permute;


        /// <summary>
        /// Returns a SIMD register with all elements set to zero.
        /// </summary>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), returns a static __m128 register initialized to zero using _mm_setzero_ps.
        /// For N &gt; 4 (long SIMD type), returns a static __m256 register initialized to zero using _mm256_setzero_ps.
        /// The static variable ensures the zeroed register is only initialized once, improving performance.
        /// </remarks>
        /// <returns>
        /// A SIMDType with all elements set to zero.
        /// </returns>
        static SIMDType Zero( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                static auto result = _mm_setzero_ps( );
                return result;
            }
            else
            {
                static auto result = _mm256_setzero_ps( );
                return result;
            }
        }

        /// <summary>
        /// Broadcasts a single value to all elements of the SIMD register.
        /// </summary>
        /// <param name="value">
        /// The value to broadcast to all elements of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with all elements set to <c>value</c>.
        /// </returns>
        static SIMDType Fill( Type value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_ps1( value );
            }
            else
            {
                return _mm256_broadcast_ss( &value );
            }
        }
        
        /// <summary>
        /// Fills a SIMD vector with a specified number of elements, all set to the same value.
        /// </summary>
        /// <typeparam name="Num">The number of elements to fill in the SIMD vector. Must be greater than 0 and not exceed Size.</typeparam>
        /// <param name="value">The value to replicate across the SIMD vector elements.</param>
        /// <returns>A SIMD vector with the first Num elements set to the specified value.</returns>
        template<size_t Num>
        static SIMDType Fill( Type value ) noexcept requires ( Num > 0 && Num <= Size )
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Num == 1 )
                {
                    return Set( value );
                }
                else if constexpr ( Num == 2 )
                {
                    return Set( value, value );
                }
                else if constexpr ( Num == 3 )
                {
                    return Set( value, value, value );
                }
                else
                {
                    return _mm_set_ps1( value );
                }
            }
            else
            {
                if constexpr ( Num == 5 )
                {
                    return Set( value, value, value, value, value );
                }
                else if constexpr ( Num == 6 )
                {
                    return Set( value, value, value, value, value, value );
                }
                else if constexpr ( Num == 7 )
                {
                    return Set( value, value, value, value, value, value, value );
                }
                else
                {
                    return _mm256_broadcast_ss( &value );
                }
            }
        }

        /// <summary>
        /// Creates a SIMD vector for division operations by filling the first Num elements with a divisor value and padding remaining elements with 1.0f.
        /// </summary>
        /// <typeparam name="Num">The number of elements to fill with the divisor value. Must be greater than 0 and not exceed SIMDTypeCapacity.</typeparam>
        /// <param name="value">The divisor value to fill into the SIMD vector.</param>
        /// <returns>
        /// A SIMD vector (either __m128 or __m256) with the first Num elements set to 
        /// the divisor value and remaining elements set to 1.0f (identity for division).
        /// </returns>
        template<size_t Num>
        static SIMDType FillDivisor( Type value ) noexcept requires ( Num > 0 && Num <= SIMDTypeCapacity )
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Num == 1 )
                {
                    return _mm_set_ps( 1.f, 1.f, 1.f, value );
                }
                else if constexpr ( Num == 2 )
                {
                    return _mm_set_ps( 1.f, 1.f, value, value );
                }
                else if constexpr ( Num == 3 )
                {
                    return _mm_set_ps( 1.f, value, value, value );
                }
                else
                {
                    return _mm_set_ps1( value );
                }
            }
            else
            {
                if constexpr ( Num == 5 )
                {
                    return _mm256_set_ps( 1.f, 1.f, 1.f, value, value, value, value, value );
                }
                else if constexpr ( Num == 6 )
                {
                    return _mm256_set_ps( 1.f, 1.f, value, value, value, value, value, value );
                }
                else if constexpr ( Num == 7 )
                {
                    return _mm256_set_ps( 1.f, value, value, value, value, value, value, value );
                }
                else
                {
                    return _mm256_broadcast_ss( &value );
                }
            }
        }

        /// <summary>
        /// Returns a SIMD register with only the valid elements for the current vector size.
        /// 
        /// If the vector size (<c>Size</c>) matches the SIMD register capacity (<c>SIMDTypeCapacity</c>),
        /// the input vector <c>v</c> is returned unchanged.
        /// Otherwise, the function applies a mask to zero out any unused elements, ensuring that only
        /// the lowest <c>Size</c> elements are preserved and the rest are set to zero.
        /// 
        /// This is useful for operations where the SIMD register may contain extra elements that should
        /// not participate in further calculations, such as when working with vectors smaller than the
        /// full SIMD width.
        /// </summary>
        /// <param name="v">The SIMD register to trim.</param>
        /// <returns>
        /// A SIMD register with only the valid elements for the current vector size.
        /// </returns>
        static SIMDType Trim( SIMDType v ) noexcept
        {
            if constexpr ( Size == SIMDTypeCapacity )
            {
                return v;
            }
            else
            {
                return And( v, Mask( ) );
            }
        }


        /// <summary>
        /// Creates a SIMD mask by replicating an unsigned integer value across SIMD lanes.
        /// </summary>
        /// <param name="value">The unsigned integer value to replicate as a mask pattern across the SIMD vector lanes.</param>
        /// <returns>
        /// A SIMD vector (128-bit or 256-bit) with the mask value replicated in 
        /// the appropriate number of lanes based on the Size template parameter, 
        /// with remaining lanes set to zero.
        /// </returns>
        static SIMDType Mask( UIntType value ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Size == 1 )
                {
                    return _mm_castsi128_ps( _mm_set_epi32( 0x00000000, 0x00000000, 0x00000000, value ) );
                }
                else if constexpr ( Size == 2 )
                {
                    return _mm_castsi128_ps( _mm_set_epi32( 0x00000000, 0x00000000, value, value ) );
                }
                else if constexpr ( Size == 3 )
                {
                    return _mm_castsi128_ps( _mm_set_epi32( 0x00000000, value, value, value ) );
                }
                else
                {
                    return _mm_castsi128_ps( _mm_set_epi32( value, value, value, value ) );
                }
            }
            else
            {
                if constexpr ( Size == 5 )
                {
                    return _mm256_castsi256_ps( _mm256_set_epi32( 0x00000000, 0x00000000, 0x00000000, value, value, value, value, value ) );
                }
                else if constexpr ( Size == 6 )
                {
                    return _mm256_castsi256_ps( _mm256_set_epi32( 0x00000000, 0x00000000, value, value, value, value, value, value ) );
                }
                else if constexpr ( Size == 7 )
                {
                    return _mm256_castsi256_ps( _mm256_set_epi32( 0x00000000, value, value, value, value, value, value, value ) );
                }
                else
                {
                    return _mm256_castsi256_ps( _mm256_set_epi32( value, value, value, value, value, value, value, value ) );
                }
            }
        }

        /// <summary>
        /// Returns a mask suitable for extracting the <c>Size</c> lowest elements from
        /// the <c>SIMDType</c> using the <c>And</c> function.
        /// 
        /// This overload sets all bits of the mask to 0xFFFFFFFF, which is commonly used
        /// to select all elements in a SIMD register. For partial selection, use the overload
        /// that accepts a value parameter.
        /// </summary>
        /// <returns>
        /// A SIMDType mask with all bits set to 0xFFFFFFFF.
        /// </returns>
        static SIMDType Mask( ) noexcept
        {
            return Mask( 0xFFFFFFFF );
        }

        /// <summary>
        /// Sets the SIMD register with a single value in the lowest element, zeroing all other elements.
        /// </summary>
        /// <param name="value1">
        /// The value to set in the lowest element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the lowest element set to <c>value1</c> and all other elements set to zero.
        /// </returns>
        static SIMDType Set( Type value1 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_ss( value1 );
            }
            else
            {
                return _mm256_set_ps( 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, value1 );
            }
        }

        /// <summary>
        /// Sets the SIMD register with two values in the lowest elements, zeroing all other elements.
        /// </summary>
        /// <param name="value2">
        /// The value to set in the second-lowest element of the SIMD register.
        /// </param>
        /// <param name="value1">
        /// The value to set in the lowest element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the lowest two elements set to <c>value2</c> and <c>value1</c>, and all other elements set to zero.
        /// </returns>
        static SIMDType Set( Type value2, Type value1 ) noexcept requires ( N > 1 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_ps( 0.f, 0.f, value2, value1 );
            }
            else
            {
                return _mm256_set_ps( 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, value2, value1 );
            }
        }

        /// <summary>
        /// Sets the SIMD register with three values in the lowest elements, zeroing all other elements.
        /// </summary>
        /// <param name="value3">
        /// The value to set in the third-lowest element of the SIMD register.
        /// </param>
        /// <param name="value2">
        /// The value to set in the second-lowest element of the SIMD register.
        /// </param>
        /// <param name="value1">
        /// The value to set in the lowest element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the lowest three elements set to <c>value3</c>, <c>value2</c>, and <c>value1</c>, and all other elements set to zero.
        /// </returns>
        static SIMDType Set( Type value3, Type value2, Type value1 ) noexcept requires ( N > 2 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_ps( 0.f, value3, value2, value1 );
            }
            else
            {
                return _mm256_set_ps( 0.f, 0.f, 0.f, 0.f, 0.f, value3, value2, value1 );
            }
        }

        /// <summary>
        /// Sets the SIMD register with four values in the lowest elements, zeroing all other elements.
        /// </summary>
        /// <param name="value4">
        /// The value to set in the fourth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value3">
        /// The value to set in the third-lowest element of the SIMD register.
        /// </param>
        /// <param name="value2">
        /// The value to set in the second-lowest element of the SIMD register.
        /// </param>
        /// <param name="value1">
        /// The value to set in the lowest element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the lowest four elements set to <c>value4</c>, <c>value3</c>, <c>value2</c>, and <c>value1</c>, and all other elements set to zero.
        /// </returns>
        static SIMDType Set( Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 3 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_ps( value4, value3, value2, value1 );
            }
            else
            {
                return _mm256_set_ps( 0.f, 0.f, 0.f, 0.f, value4, value3, value2, value1 );
            }
        }

        /// <summary>
        /// Sets the SIMD register with five values in the lowest elements, zeroing all other elements.
        /// </summary>
        /// <param name="value5">
        /// The value to set in the fifth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value4">
        /// The value to set in the fourth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value3">
        /// The value to set in the third-lowest element of the SIMD register.
        /// </param>
        /// <param name="value2">
        /// The value to set in the second-lowest element of the SIMD register.
        /// </param>
        /// <param name="value1">
        /// The value to set in the lowest element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the lowest five elements set to <c>value5</c>, <c>value4</c>, <c>value3</c>, <c>value2</c>, and <c>value1</c>, and all other elements set to zero.
        /// </returns>
        static SIMDType Set( Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 4 )
        {
            return _mm256_set_ps( 0.f, 0.f, 0.f, value5, value4, value3, value2, value1 );
        }

        /// <summary>
        /// Sets the SIMD register with six values in the lowest elements, zeroing all other elements.
        /// </summary>
        /// <param name="value6">
        /// The value to set in the sixth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value5">
        /// The value to set in the fifth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value4">
        /// The value to set in the fourth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value3">
        /// The value to set in the third-lowest element of the SIMD register.
        /// </param>
        /// <param name="value2">
        /// The value to set in the second-lowest element of the SIMD register.
        /// </param>
        /// <param name="value1">
        /// The value to set in the lowest element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the lowest six elements set to <c>value6</c>, <c>value5</c>, <c>value4</c>, <c>value3</c>, <c>value2</c>, and <c>value1</c>, and all other elements set to zero.
        /// </returns>
        static SIMDType Set( Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 5 )
        {
            return _mm256_set_ps( 0.f, 0.f, value6, value5, value4, value3, value2, value1 );
        }

        /// <summary>
        /// Sets the SIMD register with seven values in the lowest elements, zeroing all other elements.
        /// </summary>
        /// <param name="value7">
        /// The value to set in the seventh-lowest element of the SIMD register.
        /// </param>
        /// <param name="value6">
        /// The value to set in the sixth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value5">
        /// The value to set in the fifth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value4">
        /// The value to set in the fourth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value3">
        /// The value to set in the third-lowest element of the SIMD register.
        /// </param>
        /// <param name="value2">
        /// The value to set in the second-lowest element of the SIMD register.
        /// </param>
        /// <param name="value1">
        /// The value to set in the lowest element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the lowest seven elements set to <c>value7</c>, <c>value6</c>, <c>value5</c>, <c>value4</c>, <c>value3</c>, <c>value2</c>, and <c>value1</c>, and all other elements set to zero.
        /// </returns>
        static SIMDType Set( Type value7, Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 6 )
        {
            return _mm256_set_ps( 0.f, value7, value6, value5, value4, value3, value2, value1 );
        }

        /// <summary>
        /// Sets the SIMD register with eight values in the lowest elements, zeroing all other elements.
        /// </summary>
        /// <param name="value8">
        /// The value to set in the eighth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value7">
        /// The value to set in the seventh-lowest element of the SIMD register.
        /// </param>
        /// <param name="value6">
        /// The value to set in the sixth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value5">
        /// The value to set in the fifth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value4">
        /// The value to set in the fourth-lowest element of the SIMD register.
        /// </param>
        /// <param name="value3">
        /// The value to set in the third-lowest element of the SIMD register.
        /// </param>
        /// <param name="value2">
        /// The value to set in the second-lowest element of the SIMD register.
        /// </param>
        /// <param name="value1">
        /// The value to set in the lowest element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the lowest eight elements set to <c>value8</c>, <c>value7</c>, <c>value6</c>, <c>value5</c>, <c>value4</c>, <c>value3</c>, <c>value2</c>, and <c>value1</c>, and all other elements set to zero.
        /// </returns>
        static SIMDType Set( Type value8, Type value7, Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 7 )
        {
            return _mm256_set_ps( value8, value7, value6, value5, value4, value3, value2, value1 );
        }


        /// <summary>
        /// Sets the X (lowest) element of the SIMD register to the specified value.
        /// </summary>
        /// <param name="v">
        /// The SIMD register whose X element will be set.
        /// </param>
        /// <param name="value">
        /// The value to set in the X element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the X element set to <c>value</c>, and all other elements unchanged.
        /// </returns>
        static SIMDType SetX( SIMDType v, Type value )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_blend_ps( v, _mm_set_ps1( value ), 0b0001 );
            }
            else
            {
                return _mm256_blend_ps( v, _mm256_set1_ps( value ), 0b0001 );
            }
        }

        /// <summary>
        /// Sets the Y (second-lowest) element of the SIMD register to the specified value.
        /// </summary>
        /// <param name="v">
        /// The SIMD register whose Y element will be set.
        /// </param>
        /// <param name="value">
        /// The value to set in the Y element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the Y element set to <c>value</c>, and all other elements unchanged.
        /// </returns>
        static SIMDType SetY( SIMDType v, Type value )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_blend_ps( v, _mm_set_ps1( value ), 0b0010 );
            }
            else
            {
                return _mm256_blend_ps( v, _mm256_set1_ps( value ), 0b0010 );
            }
        }

        /// <summary>
        /// Sets the Z (third-lowest) element of the SIMD register to the specified value.
        /// </summary>
        /// <param name="v">
        /// The SIMD register whose Z element will be set.
        /// </param>
        /// <param name="value">
        /// The value to set in the Z element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the Z element set to <c>value</c>, and all other elements unchanged.
        /// </returns>
        static SIMDType SetZ( SIMDType v, Type value )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_blend_ps( v, _mm_set_ps1( value ), 0b0100 );
            }
            else
            {
                return _mm256_blend_ps( v, _mm256_set1_ps( value ), 0b0100 );
            }
        }

        /// <summary>
        /// Sets the W (fourth) element of the SIMD register to the specified value.
        /// </summary>
        /// <param name="v">
        /// The SIMD register whose W element will be set.
        /// </param>
        /// <param name="value">
        /// The value to set in the W element of the SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with the W element set to <c>value</c>, and all other elements unchanged.
        /// </returns>
        static SIMDType SetW( SIMDType v, Type value )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_blend_ps( v, _mm_set_ps1( value ), 0b1000 );
            }
            else
            {
                return _mm256_blend_ps( v, _mm256_set1_ps( value ), 0b1000 );
            }
        }


        /**
         * @brief Loads N float values from memory into a SIMD register.
         *
         * This function loads N elements of type float from the memory location pointed to by src
         * into a SIMD register. The loading strategy depends on the value of N and whether a short
         * SIMD type (128-bit) or a long SIMD type (256-bit) is used.
         *
         * - For N == 1: Loads a single float using _mm_load_ss.
         * - For N == 2: Loads two floats as a double using _mm_load_sd and casts to __m128.
         * - For N == 3: Loads three floats using the Set function, which fills the SIMD register
         *   with the provided values.
         * - For N >= 4 (short SIMD): Loads four floats using _mm_load_ps.
         * - For N == 5, 6, 7 (long SIMD): Loads the first four floats using _mm_load_ps, then
         *   inserts additional values using _mm256_insertf128_ps and appropriate intrinsics.
         * - For N == 8 (long SIMD): Loads eight floats using _mm256_load_ps.
         *
         * @param src Pointer to the source array of floats to load.
         * @return SIMDType The loaded SIMD register containing the N float values.
         */

        /// <summary>
        /// Loads N floating-point values from memory into a SIMD register.
        /// </summary>
        /// <param name="src">Pointer to the source memory location containing the floating-point values to load.</param>
        /// <returns>
        /// A SIMD register containing the loaded values. For counts less 
        /// than the register capacity, the remaining elements are undefined 
        /// or zero-initialized depending on the intrinsic used.</returns>
        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_load_ss( src );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src ) ) );
                }
                else if constexpr ( N == 3 )
                {
                    //__m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src ) ) );
                    //__m128 high = _mm_load_ss( reinterpret_cast< const float* >( src + 2 ) );
                    //return _mm_insert_ps( low, high, 0x20 );
                    
                    return Set( src[ 2 ], src[ 1 ], src[ 0 ] );
                }
                else
                {
                    return _mm_load_ps( src );
                }
            }
            else
            {
                if constexpr ( N == 5 )
                {
                    // Loads first 4 floats, inserts the 5th as a scalar in the upper lane.
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_load_ps( src ) ), _mm_load_ss( src + 4 ), 1 );
                }
                else if constexpr ( N == 6 )
                {
                    // Loads first 4 floats, inserts the next two as a double in the upper lane.
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_load_ps( src ) ), _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src + 4 ) ) ), 1 );
                }
                else if constexpr ( N == 7 )
                {
                    // Loads first 4 floats, inserts next two as a double and the 7th as a scalar.
                    auto rmm1 = _mm_load_ps( src );
                    __m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src + 4 ) ) );
                    __m128 high = _mm_load_ss( reinterpret_cast<const float*>( src + 6 ) );
                    auto rmm2 = _mm_insert_ps( low, high, 0x20 );
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm2, 1 );
                }
                else
                {
                    return _mm256_load_ps( src );
                }
            }
        }
        /*
        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_load_ss( src );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src ) ) );
                }
                else if constexpr ( N == 3 )
                {
                    
                    //__m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src ) ) );
                    //__m128 high = _mm_load_ss( reinterpret_cast< const float* >( src + 2 ) );
                    //return _mm_insert_ps( low, high, 0x20 );
                    
                    return Set( src[ 2 ], src[ 1 ], src[0] );
                }
                else
                {
                    return _mm_load_ps( src );
                }
            }
            else
            {
                if constexpr ( N == 5 )
                {
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_load_ps( src ) ), _mm_load_ss( src + 4 ), 1 );
                }
                else if constexpr ( N == 6 )
                {
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_load_ps( src ) ), _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src + 4 ) ) ), 1 );
                }
                else if constexpr ( N == 7 )
                {
                    auto rmm1 = _mm_load_ps( src );
                    __m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src + 4 ) ) );
                    __m128 high = _mm_load_ss( reinterpret_cast< const float* >( src + 6 ) );
                    auto rmm2 = _mm_insert_ps( low, high, 0x20 );
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm2, 1 );
                }
                else
                {
                    return _mm256_load_ps( src );
                }
            }
        }
        */
        /*
        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_load_ss( src );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src ) ) );
                }
                else if constexpr ( N == 3 )
                {
                    __m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src ) ) );
                    __m128 high = _mm_load_ss( reinterpret_cast<const float*>( src + 2 ) );
                    return _mm_insert_ps( low, high, 0x20 );
                }
                else
                {
                    return _mm_loadu_ps( src );
                }
            }
            else
            {
                if constexpr ( N == 5 )
                {
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_loadu_ps( src ) ), _mm_load_ss( src + 4 ), 1 );
                }
                else if constexpr ( N == 6 )
                {
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_loadu_ps( src ) ), _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src + 4 ) ) ), 1 );
                }
                else if constexpr ( N == 7 )
                {
                    auto rmm1 = _mm_loadu_ps( src );
                    __m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src + 4 ) ) );
                    __m128 high = _mm_load_ss( reinterpret_cast<const float*>( src + 6 ) );
                    auto rmm2 = _mm_insert_ps( low, high, 0x20 );
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm2, 1 );
                }
                else
                {
                    return _mm256_loadu_ps( src );
                }
            }
        }
        */

        /*
        struct alignas( AlignAs ) Loadable
        {
            std::array<Type, 4> data;

            Loadable( const std::array<Type, 1>& d )
                : data{ d[ 0 ],{},{},{} }
            { }
            Loadable( const std::array<Type, 2>& d )
                : data{ d[ 0 ],d[ 1 ],{},{} }
            {
            }
            Loadable( const std::array<Type, 3>& d )
                : data{ d[ 0 ],d[ 1 ],d[ 2 ],{} }
            { }
            Loadable( const std::array<Type, 4>& d )
                : data{ d[ 0 ],d[ 1 ],d[ 2 ],d[ 3 ] }
            { }

        };



        static SIMDType Load( const Loadable src ) noexcept
        {
            return _mm_load_ps( src.data.data() );
        }
        */

        /// <summary>
        /// Loads SIMDType from a std::array of elements.
        /// </summary>
        /// <typeparam name="NA">
        /// The number of elements in the source array. Must be greater than or equal to N.
        /// </typeparam>
        /// <param name="src">
        /// Reference to the source std::array containing the elements to load.
        /// </param>
        /// <returns>
        /// A SIMDType containing the loaded elements from the array.
        /// </returns>
        template<size_t NA>
            requires ( NA >= N )
        static SIMDType Load( const std::array<Type, NA>& src ) noexcept
        {
            return Load( src.data( ) );
        }


        /// <summary>
        /// Loads SIMD data from an unaligned memory location.
        /// </summary>
        /// <param name="src">Pointer to the source memory location containing the data to load. The memory does not need to be aligned to SIMD boundaries.</param>
        /// <returns>A SIMD vector containing the loaded data. The specific SIMD type (128-bit or 256-bit) and loading strategy depend on the compile-time value of N and the UseShortSIMDType flag.</returns>
        static SIMDType UnalignedLoad( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_load_ss( src );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src ) ) );
                }
                else if constexpr ( N == 3 )
                {
                    return Set( src[ 2 ], src[ 1 ], src[ 0 ] );
                }
                else
                {
                    return _mm_loadu_ps( src );
                }
            }
            else
            {
                if constexpr ( N == 5 )
                {
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_loadu_ps( src ) ), _mm_load_ss( src + 4 ), 1 );
                }
                else if constexpr ( N == 6 )
                {
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( _mm_loadu_ps( src ) ), _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src + 4 ) ) ), 1 );
                }
                else if constexpr ( N == 7 )
                {
                    auto rmm1 = _mm_loadu_ps( src );
                    __m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast<const double*>( src + 4 ) ) );
                    __m128 high = _mm_load_ss( reinterpret_cast<const float*>( src + 6 ) );
                    auto rmm2 = _mm_insert_ps( low, high, 0x20 );
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm2, 1 );
                }
                else
                {
                    return _mm256_loadu_ps( src );
                }
            }
        }

        /// <summary>
        /// Stores the contents of a SIMD register to a memory location.
        /// </summary>
        /// <param name="dest">
        /// Pointer to the destination memory where the SIMD register contents will be stored.
        /// The memory must be properly aligned for SIMD operations.
        /// </param>
        /// <param name="src">
        /// The SIMD register whose contents will be stored to memory.
        /// </param>
        /// <remarks>
        /// For short SIMD types (N &lt;= 4), uses _mm_store_ps to store 128-bit data.
        /// For long SIMD types (N &gt; 4), uses _mm256_store_ps to store 256-bit data.
        /// The function does not perform bounds or alignment checks; the caller is responsible
        /// for ensuring the destination pointer is valid and properly aligned.
        /// </remarks>
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

        /// <summary>
        /// Stores a SIMD register value to an unaligned memory location.
        /// </summary>
        /// <param name="dest">Pointer to the destination memory location where the SIMD data will be stored. Does not need to be aligned.</param>
        /// <param name="src">The SIMD register value to store.</param>
        static void UnalignedStore( Type* dest, SIMDType src ) noexcept
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
        /// Returns the first element of the SIMD register.
        /// </summary>
        /// <param name="src">
        /// The SIMDType register from which to extract the first value.
        /// </param>
        /// <returns>
        /// The value of the lowest element in <c>src</c>.
        /// </returns>
        static Type First( SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cvtss_f32( src );
            }
            else
            {
                return _mm256_cvtss_f32( src );
            }
        }

        /// <summary>
        /// Converts a SIMD register to a std::array containing the lower <c>N</c> elements.
        /// </summary>
        /// <param name="src">
        /// The SIMDType register to convert.
        /// </param>
        /// <returns>
        /// An ArrayType containing the lower <c>N</c> elements of <c>src</c>.
        /// </returns>
        static ArrayType ToArray( SIMDType src ) noexcept
        {
            if constexpr ( N == 1 )
            {
                ArrayType result;
                result[ 0 ] = _mm_cvtss_f32( src );
                return result;
            }
            else if constexpr ( N == 2 )
            {
                ArrayType result;
                _mm_store_sd( reinterpret_cast< double* >( result.data( ) ), _mm_castps_pd( src ) );

                return result;
            }
            else if constexpr ( N == 3 )
            {
                ArrayType result;
                _mm_store_sd( reinterpret_cast< double* >( result.data( ) ), _mm_castps_pd( src ) );
                result[ 2 ] = std::bit_cast< Type >( _mm_extract_ps( src, 2 ) );
                return result;

            }
            else if constexpr ( N == 4 )
            {
                ArrayType result;
                _mm_storeu_ps( result.data( ), src );
                return result;
            }
            else if constexpr ( N == 8 )
            {
                ArrayType result;
                _mm256_storeu_ps( result.data( ), src );
                return result;
            }
            else
            {
                alignas( AlignAs ) std::array<Type, SIMDTypeCapacity> tmp;
                Store( tmp.data( ), src );
                return[ &tmp ] <std::size_t... I>
                    ( std::index_sequence<I...> )
                {
                    ArrayType result;
                    ( ( result[ I ] = tmp[ I ] ), ... );
                    return result;
                }( std::make_index_sequence<N>( ) );
            }
        }

        /// <summary>
        /// Returns a SIMDType with all elements set to the value of <c>v[index]</c>.
        /// </summary>
        /// <typeparam name="index">
        /// The index of the value in <c>v</c> to assign to all the elements of the result.
        /// </typeparam>
        /// <param name="v">
        /// The SIMDType containing the source value.
        /// </param>
        /// <returns>
        /// A SIMDType with all elements set to the value of <c>v[index]</c>.
        /// </returns>
        template<size_t index>
            requires ( index < Size )
        static SIMDType At( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( index == 0 )
                {
                    return _mm_shuffle_ps( v, v, _MM_SHUFFLE( 0, 0, 0, 0 ) );
                }
                else if constexpr ( index == 1 )
                {
                    return _mm_shuffle_ps( v, v, _MM_SHUFFLE( 1, 1, 1, 1 ) );
                }
                else if constexpr ( index == 2 )
                {
                    return _mm_shuffle_ps( v, v, _MM_SHUFFLE( 2, 2, 2, 2 ) );
                }
                else
                {
                    return _mm_shuffle_ps( v, v, _MM_SHUFFLE( 3, 3, 3, 3 ) );
                }
            }
            else
            {
                if constexpr ( index < 4 )
                {
                    auto low = _mm256_castps256_ps128( v );
                    if constexpr ( index == 0 )
                    {
                        return _mm256_broadcastss_ps( low );
                    }
                    else if constexpr ( index == 1 )
                    {
                        return _mm256_broadcastss_ps( _mm_shuffle_ps( low, low, _MM_SHUFFLE( 1, 1, 1, 1 ) ) );
                    }
                    else if constexpr ( index == 2 )
                    {
                        return _mm256_broadcastss_ps( _mm_shuffle_ps( low, low, _MM_SHUFFLE( 2, 2, 2, 2 ) ) );
                    }
                    else
                    {
                        return _mm256_broadcastss_ps( _mm_shuffle_ps( low, low, _MM_SHUFFLE( 3, 3, 3, 3 ) ) );
                    }
                }
                else
                {
                    auto high = _mm256_extractf128_ps( v, 1 );
                    if constexpr ( index == 4 )
                    {
                        return _mm256_broadcastss_ps( high );
                    }
                    else if constexpr ( index == 5 )
                    {
                        return _mm256_broadcastss_ps( _mm_shuffle_ps( high, high, _MM_SHUFFLE( 1, 1, 1, 1 ) ) );
                    }
                    else if constexpr ( index == 6 )
                    {
                        return _mm256_broadcastss_ps( _mm_shuffle_ps( high, high, _MM_SHUFFLE( 2, 2, 2, 2 ) ) );
                    }
                    else
                    {
                        return _mm256_broadcastss_ps( _mm_shuffle_ps( high, high, _MM_SHUFFLE( 3, 3, 3, 3 ) ) );
                    }
                }
            }
        }


        /// <summary>
        /// Extracts the value of the element at the specified index from a SIMD register.
        /// </summary>
        /// <typeparam name="index">
        /// The index of the element to extract. Must be less than <c>Size</c>.
        /// </typeparam>
        /// <param name="v">
        /// The SIMDType register from which to extract the value.
        /// </param>
        /// <returns>
        /// The value of the element at the specified index in <c>v</c>.
        /// </returns>
        /// <remarks>
        /// For short SIMD types (N &lt;= 4), uses <c>_mm_cvtss_f32</c> for index 0 and <c>_mm_extract_ps</c> for other indices.
        /// For long SIMD types (N &gt; 4), extracts from the lower or upper 128-bit lane as appropriate.
        /// </remarks>
        template<size_t index>
            requires ( index < Size )
        static Type Extract( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( index == 0 )
                {
                    return _mm_cvtss_f32( v );
                }
                else if constexpr ( index == 1 )
                {
                    return std::bit_cast< Type >( _mm_extract_ps( v, 1 ) );
                }
                else if constexpr ( index == 2 )
                {
                    return std::bit_cast< Type >( _mm_extract_ps( v, 2 ) );
                }
                else
                {
                    return std::bit_cast< Type >( _mm_extract_ps( v, 3 ) );
                }
            }
            else
            {
                if constexpr ( index < 4 )
                {
                    auto low = _mm256_castps256_ps128( v );
                    if constexpr ( index == 0 )
                    {
                        return _mm_cvtss_f32( low );
                    }
                    else if constexpr ( index == 1 )
                    {
                        return std::bit_cast< Type >( _mm_extract_ps( low, 1 ) );
                    }
                    else if constexpr ( index == 2 )
                    {
                        return std::bit_cast< Type >( _mm_extract_ps( low, 2 ) );
                    }
                    else
                    {
                        return std::bit_cast< Type >( _mm_extract_ps( low, 3 ) );
                    }
                }
                else
                {
                    auto high = _mm256_extractf128_ps( v, 1 );
                    if constexpr ( index == 4 )
                    {
                        return _mm_cvtss_f32( high );
                    }
                    else if constexpr ( index == 5 )
                    {
                        return std::bit_cast< Type >( _mm_extract_ps( high, 1 ) );
                    }
                    else if constexpr ( index == 6 )
                    {
                        return std::bit_cast< Type >( _mm_extract_ps( high, 2 ) );
                    }
                    else
                    {
                        return std::bit_cast< Type >( _mm_extract_ps( high, 3 ) );
                    }
                }
            }
        }

        /// <summary>
        /// Computes the bitwise AND of packed single-precision (32-bit) floating-point elements
        /// in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        /// <param name="lhs">SIMDType containing the left-hand side values.</param>
        /// <param name="rhs">SIMDType containing the right-hand side values.</param>
        /// <returns>
        /// SIMDType containing the result of the bitwise AND operation for each element.
        /// </returns>
        static SIMDType And( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_and_ps( lhs, rhs );
            }
            else
            {
                return _mm256_and_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Computes the bitwise NOT of packed single-precision (32-bit) floating-point 
        /// elements in <c>lhs</c> and then ANDs with <c>rhs</c>, returning the results.
        /// </summary>
        /// <param name="lhs">
        /// SIMDType containing the left-hand side values. Each element is bitwise NOT-ed before AND.
        /// </param>
        /// <param name="rhs">
        /// SIMDType containing the right-hand side values. Each element is AND-ed with the NOT of the corresponding element in <c>lhs</c>.
        /// </param>
        /// <returns>
        /// SIMDType containing the result of the bitwise AND NOT operation for each element.
        /// </returns>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), uses _mm_andnot_ps.
        /// For N &gt; 4 (long SIMD type), uses _mm256_andnot_ps.
        /// </remarks>
        static SIMDType AndNot( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_andnot_ps( lhs, rhs );
            }
            else
            {
                return _mm256_andnot_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Computes the bitwise OR of packed single-precision (32-bit) floating-point elements
        /// in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        /// <param name="lhs">SIMDType containing the left-hand side values.</param>
        /// <param name="rhs">SIMDType containing the right-hand side values.</param>
        /// <returns>
        /// SIMDType containing the result of the bitwise OR operation for each element.
        /// </returns>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), uses _mm_or_ps.
        /// For N &gt; 4 (long SIMD type), uses _mm256_or_ps.
        /// </remarks>
        static SIMDType Or( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_or_ps( lhs, rhs );
            }
            else
            {
                return _mm256_or_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Computes the bitwise XOR of packed single-precision (32-bit) floating-point elements
        /// in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        /// <param name="lhs">SIMDType containing the left-hand side values.</param>
        /// <param name="rhs">SIMDType containing the right-hand side values.</param>
        /// <returns>
        /// SIMDType containing the result of the bitwise XOR operation for each element.
        /// </returns>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), uses _mm_xor_ps.
        /// For N &gt; 4 (long SIMD type), uses _mm256_xor_ps.
        /// </remarks>
        static SIMDType Xor( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_xor_ps( lhs, rhs );
            }
            else
            {
                return _mm256_xor_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Adds two float32 SIMD vectors element-wise.
        /// </summary>
        /// <param name="lhs">
        /// The left-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <param name="rhs">
        /// The right-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <returns>
        /// A SIMD vector containing the element-wise sum of <c>lhs</c> and <c>rhs</c>.
        /// </returns>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), uses <c>_mm_add_ps</c> to add 128-bit vectors.
        /// For N &gt; 4 (long SIMD type), uses <c>_mm256_add_ps</c> to add 256-bit vectors.
        /// </remarks>
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
        /// Performs horizontal addition of two SIMD vectors containing single-precision floating-point values.
        /// </summary>
        /// <param name="lhs">
        /// The left-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <param name="rhs">
        /// The right-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <returns>
        /// A SIMD vector containing the horizontally added results of <c>lhs</c> and <c>rhs</c>.
        /// </returns>
        /// <remarks>
        /// Adds pairs of adjacent single-precision floating-point values from the first 
        /// source operand, lhs, and the second source operand, rhs.
        /// 
        /// For N &lt;= 4 (short SIMD type), uses <c>_mm_hadd_ps</c> to add 128-bit vectors horizontally.
        /// For N &gt; 4 (long SIMD type), uses <c>_mm256_hadd_ps</c> to add 256-bit vectors horizontally.
        /// </remarks>
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

        /// <summary>
        /// Computes the horizontal sum of the lower N SIMD vector elements and broadcasts the result across all lanes.
        /// </summary>
        /// <param name="v">The SIMD vector whose elements will be summed.</param>
        /// <returns>A SIMD vector with the sum of all input elements broadcast to every lane.</returns>
        static SIMDType HSum( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_broadcastss_ps( v );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_add_ps( _mm_permute_ps( v, 0b01'00'01'00 ), _mm_permute_ps( v, 0b00'01'00'01 ) );
                }
                else if constexpr ( N == 3 )
                {
                    return _mm_add_ps( _mm_permute_ps( v, _MM_SHUFFLE( 0, 2, 1, 0 ) ), _mm_add_ps( _mm_permute_ps( v, _MM_SHUFFLE( 1, 1, 0, 2 ) ), _mm_permute_ps( v, _MM_SHUFFLE( 2, 0, 2, 1 ) ) ) );
                }
                else
                {
                    return _mm_add_ps( _mm_add_ps( v, _mm_permute_ps( v, 0b10'01'00'11 ) ),
                        _mm_add_ps( _mm_permute_ps( v, 0b01'00'11'10 ), _mm_permute_ps( v, 0b00'11'10'01 ) ) );
                }
            }
            else
            {
                __m128 low = _mm256_castps256_ps128( v );
                __m128 high = _mm256_extractf128_ps( v, 1 );
                __m128 r1 = _mm_add_ps( low, high );
                __m128 r2 = _mm_add_ps( r1, _mm_movehl_ps( r1, r1 ) );
                return _mm256_broadcastss_ps( _mm_add_ss( r2, _mm_movehdup_ps( r2 ) ) );
            }
        }

        /// <summary>
        /// Computes the average value of the elements in a SIMD vector.
        /// </summary>
        /// <param name="v">
        /// The SIMDType vector whose elements will be averaged.
        /// </param>
        /// <returns>
        /// The average value of the elements in <c>v</c>.
        /// </returns>
        /// <remarks>
        /// This function first computes the horizontal sum of all elements in the SIMD vector <c>v</c>
        /// using <c>HSum</c>, then extracts the first element of the result using <c>First</c>, and
        /// divides by the number of elements <c>N</c> to obtain the average.
        /// </remarks>
        static Type Avg( SIMDType v ) noexcept
        {
            return First( HSum( v ) ) / static_cast< Type >( N );
        }



        /// <summary>
        /// Subtracts two SIMD vectors containing packed single-precision floating-point elements.
        /// </summary>
        /// <param name="lhs">
        /// The left-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <param name="rhs">
        /// The right-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <returns>
        /// A SIMD vector containing the element-wise difference of <c>lhs</c> and <c>rhs</c>.
        /// </returns>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), uses <c>_mm_sub_ps</c> to subtract 128-bit vectors.
        /// For N &gt; 4 (long SIMD type), uses <c>_mm256_sub_ps</c> to subtract 256-bit vectors.
        /// </remarks>
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
        /// Adds odd-numbered single-precision floating-point values of the first
        /// source operand, <paramref name="lhs"/>, with the corresponding single-precision
        /// floating-point values from the second source operand, <paramref name="rhs"/>;
        /// stores the result in the odd-numbered values of the result. Subtracts the
        /// even-numbered single-precision floating-point values from the second source
        /// operand, <paramref name="rhs"/>, from the corresponding single-precision
        /// floating values in the first source operand, <paramref name="lhs"/>;
        /// stores the result into the even-numbered values of the result.
        /// </summary>
        /// <param name="lhs">float32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), uses <c>_mm_addsub_ps</c> to add/subtract 128-bit vectors.
        /// For N &gt; 4 (long SIMD type), uses <c>_mm256_addsub_ps</c> to add/subtract 256-bit vectors.
        /// </remarks>
        /// <returns>
        /// Result of the operation is stored in the result vector, which is returned by the intrinsic.
        /// </returns>
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
        /// Multiplies two float32 SIMD vectors element-wise.
        /// </summary>
        /// <param name="lhs">
        /// The left-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <param name="rhs">
        /// The right-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <returns>
        /// A SIMD vector containing the element-wise product of <c>lhs</c> and <c>rhs</c>.
        /// </returns>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), uses <c>_mm_mul_ps</c> to multiply 128-bit vectors.
        /// For N &gt; 4 (long SIMD type), uses <c>_mm256_mul_ps</c> to multiply 256-bit vectors.
        /// </remarks>
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
        /// Multiplies a SIMD vector by a scalar value.
        /// </summary>
        /// <param name="lhs">
        /// The scalar value to multiply each element of the SIMD vector by.
        /// </param>
        /// <param name="rhs">
        /// The SIMD vector whose elements will be multiplied by the scalar value.
        /// </param>
        /// <returns>
        /// A SIMD vector containing the result of multiplying each element of <c>rhs</c> by <c>lhs</c>.
        /// </returns>
        /// <remarks>
        /// This function broadcasts the scalar <c>lhs</c> to all elements of a SIMD register using <c>Fill(lhs)</c>,
        /// then performs an element-wise multiplication with <c>rhs</c> using the <c>Mul</c> function.
        /// </remarks>
        static SIMDType Mul( Type lhs, SIMDType rhs ) noexcept
        {
            return Mul( Fill( lhs ), rhs );
        }

        /// <summary>
        /// Multiplies a SIMD vector by a scalar value.
        /// </summary>
        /// <param name="lhs">
        /// The SIMD vector whose elements will be multiplied by the scalar value.
        /// </param>
        /// <param name="rhs">
        /// The scalar value to multiply each element of the SIMD vector by.
        /// </param>
        /// <returns>
        /// A SIMD vector containing the result of multiplying each element of <c>lhs</c> by <c>rhs</c>.
        /// </returns>
        /// <remarks>
        /// This function broadcasts the scalar <c>rhs</c> to all elements of a SIMD register using <c>Fill(rhs)</c>,
        /// then performs an element-wise multiplication with <c>lhs</c> using the <c>Mul</c> function.
        /// </remarks>
        static SIMDType Mul( SIMDType lhs, Type rhs ) noexcept
        {
            return Mul( lhs, Fill( rhs ) );
        }


        /// <summary>
        /// Multiplies two quaternions using SIMD operations.
        /// </summary>
        /// <param name="q1">The first quaternion to multiply.</param>
        /// <param name="q2">The second quaternion to multiply.</param>
        /// <returns>The resulting quaternion from the multiplication of q1 and q2.</returns>
        inline static SIMDType QuaternionMultiply( SIMDType q1, SIMDType q2 ) noexcept
            requires ( Size == 4 )
        {
            constexpr Type One = 1.f;
            constexpr Type MinusOne = -1.f;

            constexpr SIMDType controlWZYX = { { One, MinusOne, One, MinusOne } };
            constexpr SIMDType controlZWXY = { { One, One, MinusOne, MinusOne } };
            constexpr SIMDType controlYXWZ = { { MinusOne, One, One, MinusOne } };

            auto q2X = At<0>( q2 );
            auto q2Y = At<1>( q2 );
            auto q2Z = At<2>( q2 );
            auto result = At<3>( q2 );

            result = Mul( result, q1 );

            auto q1Swizzle = Shuffle<0, 1, 2, 3>( q1 );

            q2X = Mul( q2X, q1Swizzle );
            q1Swizzle = Shuffle<2, 3, 0, 1>( q1Swizzle );

            result = FMAdd( q2X, controlWZYX, result );

            q2Y = Mul( q2Y, q1Swizzle );
            q1Swizzle = Shuffle<0, 1, 2, 3>( q1Swizzle );

            q2Y = Mul( q2Y, controlZWXY );

            q2Z = Mul( q2Z, q1Swizzle );

            q2Y = FMAdd( q2Z, controlYXWZ, q2Y );
            result = Add( result, q2Y );
            return result;
        }

        /// <summary>
        /// Computes the horizontal product of the elements in a SIMD vector.
        /// </summary>
        /// <param name="v">
        /// The SIMD vector whose elements will be multiplied horizontally.
        /// </param>
        /// <returns>
        /// A SIMD vector where all elements are set to the product of the input vector's elements.
        /// For N == 1, returns the input vector unchanged.
        /// For N == 2, multiplies the two elements and returns the result in both positions.
        /// For N == 3, multiplies all three elements and returns the result in all positions.
        /// For N == 4, multiplies all four elements and returns the result in all positions.
        /// For N > 4, splits the vector into low and high 128-bit lanes, multiplies their elements,
        /// and combines the results as appropriate for the vector size.
        /// </returns>
        /// <remarks>
        /// This function uses SIMD intrinsics to efficiently compute the product of all elements
        /// in the vector, broadcasting the result to all elements of the returned SIMD vector.
        /// </remarks>
        static SIMDType HProd( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_broadcastss_ps( v );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_mul_ps( v, _mm_permute_ps( v, 0b11'10'00'01 ) );
                }
                else if constexpr ( N == 3 )
                {
                    return _mm_mul_ps( v, _mm_mul_ps( _mm_permute_ps( v, _MM_SHUFFLE( 3, 1, 0, 2 ) ), _mm_permute_ps( v, _MM_SHUFFLE( 3, 0, 2, 1 ) ) ) );
                }
                else
                {
                    return _mm_mul_ps( _mm_mul_ps( v, _mm_permute_ps( v, 0b10'01'00'11 ) ),
                        _mm_mul_ps( _mm_permute_ps( v, 0b01'00'11'10 ), _mm_permute_ps( v, 0b00'11'10'01 ) ) );
                }
            }
            else
            {
                __m128 low = _mm256_castps256_ps128( v );
                __m128 high = _mm256_extractf128_ps( v, 1 );
                auto rmm1 = _mm_mul_ps( _mm_mul_ps( low, _mm_permute_ps( low, 0b10'01'00'11 ) ),
                    _mm_mul_ps( _mm_permute_ps( low, 0b01'00'11'10 ), _mm_permute_ps( low, 0b00'11'10'01 ) ) );

                if constexpr ( N == 5 )
                {
                    auto rmm2 = _mm_broadcastss_ps( high );
                    rmm1 = _mm_mul_ps( rmm2, rmm1 );
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm1, 1 );
                }
                else if constexpr ( N == 6 )
                {
                    auto rmm2 = _mm_mul_ps( _mm_permute_ps( high, 0b01'00'01'00 ), _mm_permute_ps( high, 0b00'01'00'01 ) );
                    rmm1 = _mm_mul_ps( rmm2, rmm1 );
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm1, 1 );
                }
                else if constexpr ( N == 7 )
                {
                    high = _mm_permute_ps( _mm_move_ss( _mm_permute_ps( high, _MM_SHUFFLE( 0, 2, 1, 3 ) ), _mm_set1_ps( 1.0f ) ), _MM_SHUFFLE( 0, 2, 1, 3 ) );

                    auto rmm2 = _mm_mul_ps( _mm_mul_ps( high, _mm_permute_ps( high, 0b10'01'00'11 ) ),
                        _mm_mul_ps( _mm_permute_ps( high, 0b01'00'11'10 ), _mm_permute_ps( high, 0b00'11'10'01 ) ) );
                    rmm1 = _mm_mul_ps( rmm2, rmm1 );
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm1, 1 );
                }
                else
                {
                    auto rmm2 = _mm_mul_ps( _mm_mul_ps( high, _mm_permute_ps( high, 0b10'01'00'11 ) ),
                        _mm_mul_ps( _mm_permute_ps( high, 0b01'00'11'10 ), _mm_permute_ps( high, 0b00'11'10'01 ) ) );
                    rmm1 = _mm_mul_ps( rmm2, rmm1 );
                    return _mm256_insertf128_ps( _mm256_castps128_ps256( rmm1 ), rmm1, 1 );
                }
            }
        }


        /// <summary>
        /// Divides two SIMD vectors containing packed single-precision floating-point elements.
        /// </summary>
        /// <param name="lhs">
        /// The left-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <param name="rhs">
        /// The right-hand side SIMD vector containing packed single-precision floating-point elements.
        /// </param>
        /// <returns>
        /// A SIMD vector containing the element-wise division of <c>lhs</c> by <c>rhs</c>.
        /// </returns>
        /// <remarks>
        /// For N &lt;= 4 (short SIMD type), uses <c>_mm_div_ps</c> to divide 128-bit vectors.
        /// For N &gt; 4 (long SIMD type), uses <c>_mm256_div_ps</c> to divide 256-bit vectors.
        /// </remarks>
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
        /// Divides each element of the SIMD vector <c>lhs</c> by the scalar value <c>rhs</c>.
        /// </summary>
        /// <param name="lhs">
        /// The left-hand side SIMD vector containing packed elements to be divided.
        /// </param>
        /// <param name="rhs">
        /// The scalar value to divide each element of the SIMD vector <c>lhs</c> by.
        /// </param>
        /// <returns>
        /// A SIMD vector containing the result of element-wise division of <c>lhs</c> by <c>rhs</c>.
        /// </returns>
        /// <remarks>
        /// This function broadcasts the scalar <c>rhs</c> to all elements of a SIMD register using <c>Fill(rhs)</c>,
        /// then performs an element-wise division with <c>lhs</c> using the <c>Div</c> function.
        /// </remarks>
        static SIMDType Div( SIMDType lhs, Type rhs ) noexcept
        {
            return Div( lhs, Fill( rhs ) );
        }

        /**
         * @brief Permutes elements of a SIMD register according to a specified pattern.
         *
         * This is a variadic template placeholder for SIMD permutation operations.
         * No matching overload is provided; attempting to use this function will result in a static assertion failure.
         *
         * @tparam Args Variadic template arguments specifying permutation parameters.
         * @param args Permutation arguments.
         * @note This function is intentionally not implemented and will always trigger a static assertion.
         */

        template<typename ... Args>
        static SIMDType Permute( Args&& ... args )
        {
            static_assert( false, "No matching overload" );
        }

        /// <summary>
        /// Permutes the elements of a SIMD register according to the specified shuffle mask.
        /// </summary>
        /// <param name="v">The SIMD register whose elements will be permuted.</param>
        /// <param name="shuffleMask">
        /// The mask that determines the permutation pattern. Each element in the result is selected
        /// from the input register according to the mask.
        /// </param>
        /// <returns>
        /// A SIMD register with elements permuted as specified by <paramref name="shuffleMask"/>.
        /// </returns>
        /// <remarks>
        /// For short SIMD types (128-bit), uses <c>_mm_permute_ps</c>.
        /// For long SIMD types (256-bit), uses <c>_mm256_permute_ps</c>.
        /// </remarks>
        template<int shuffleMask>
        static SIMDType Permute( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_permute_ps( v, shuffleMask );
            }
            else
            {
                return _mm256_permute_ps( v, shuffleMask );
            }
        }
        

        /// <summary>
        /// Permutes the elements of a SIMD register according to the specified shuffle mask.
        /// </summary>
        /// <typeparam name="shuffle">
        /// The shuffle mask to use for permuting the elements. Each element in the result is selected
        /// from the input register according to the mask.
        /// </typeparam>
        /// <param name="v">
        /// The SIMD register whose elements will be permuted.
        /// </param>
        /// <returns>
        /// A SIMDType with elements permuted as specified by <paramref name="shuffle"/>.
        /// </returns>
        /// <remarks>
        /// For short SIMD types (128-bit), uses <c>_mm_permute_ps</c>.
        /// </remarks>
        template<UInt32 shuffle>
        static SIMDType Swizzle( SIMDType v ) noexcept requires( UseShortSIMDType )
        {
            return _mm_permute_ps( v, shuffle );
        }

        
        /// <summary>
        /// Rearranges the elements of a SIMD vector based on the specified selection indices.
        /// </summary>
        /// <param name="v">The SIMD vector to swizzle.</param>
        /// <param name="selection4">The index selecting which element to place in the fourth position (0-3).</param>
        /// <param name="selection3">The index selecting which element to place in the third position (0-3).</param>
        /// <param name="selection2">The index selecting which element to place in the second position (0-3).</param>
        /// <param name="selection1">The index selecting which element to place in the first position (0-3).</param>
        /// <returns>A new SIMD vector with elements rearranged according to the selection indices.</returns>
        static SIMDType Swizzle( SIMDType v, UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1 ) noexcept
            requires( UseShortSIMDType )
        {
            alignas( AlignAs ) std::array<UInt32, 4> selection{ selection1, selection2, selection3, selection4 };
            __m128i selectionControl = _mm_load_si128( reinterpret_cast< const __m128i* >( selection[ 0 ].data( ) ) );
            return _mm_permutevar_ps( v, selectionControl );
        }


        /// <summary>
        /// Permutes the elements of a 256-bit SIMD register according to the specified selection indices.
        /// </summary>
        /// <param name="v">
        /// The SIMD register whose elements will be permuted.
        /// </param>
        /// <param name="selection8">
        /// The index for the highest element in the result.
        /// </param>
        /// <param name="selection7">
        /// The index for the next-highest element in the result.
        /// </param>
        /// <param name="selection6">
        /// The index for the next element in the result.
        /// </param>
        /// <param name="selection5">
        /// The index for the next element in the result.
        /// </param>
        /// <param name="selection4">
        /// The index for the next element in the result.
        /// </param>
        /// <param name="selection3">
        /// The index for the next element in the result.
        /// </param>
        /// <param name="selection2">
        /// The index for the next element in the result.
        /// </param>
        /// <param name="selection1">
        /// The index for the lowest element in the result.
        /// </param>
        /// <returns>
        /// A SIMDType with elements permuted as specified by the selection indices.
        /// </returns>
        /// <remarks>
        /// This function constructs a control vector from the provided selection indices and uses
        /// the _mm256_permutevar8x32_ps intrinsic to permute the elements of the input SIMD register.
        /// The selection indices should be in the range [0, 7] for a 256-bit SIMD register.
        /// </remarks>
        static SIMDType Swizzle( SIMDType v, UInt32 selection8, UInt32 selection7, UInt32 selection6, UInt32 selection5, UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1 ) noexcept
            requires( UseShortSIMDType == false )
        {
            alignas( AlignAs ) std::array<UInt32, 8> selection{ selection1, selection2, selection3, selection4, selection5, selection6, selection7, selection8 };
            __m128i selectionControl = _mm256_load_si256( reinterpret_cast< const __m256i* >( selection[ 0 ].data( ) ) );
            return _mm256_permutevar8x32_ps( v, selectionControl );
        }
        

        /// <summary>
        /// Variadic template placeholder for SIMD shuffle operations.
        /// <para>
        /// This function serves as a catch-all for unsupported or unimplemented shuffle overloads.
        /// Attempting to use this function will result in a static assertion failure.
        /// </para>
        /// <typeparam name="...Args"></typeparam>
        /// <param name="...args"></param>
        /// <returns></returns>
        template<typename ... Args>
        static SIMDType Shuffle( Args&& ... args )
        {
            static_assert( false, "No matching overload" );
        }

        /// <summary>
        /// Permutes the elements of two 128-bit SIMD registers according to the specified selection indices.
        /// </summary>
        /// <param name="v1">
        /// The first SIMD register whose elements will be permuted.
        /// </param>
        /// <param name="v2">
        /// The second SIMD register whose elements will be permuted.
        /// </param>
        /// <param name="selection4">
        /// The index for the highest element in the result.
        /// </param>
        /// <param name="selection3">
        /// The index for the next-highest element in the result.
        /// </param>
        /// <param name="selection2">
        /// The index for the next-lowest element in the result.
        /// </param>
        /// <param name="selection1">
        /// The index for the lowest element in the result.
        /// </param>
        /// <returns>
        /// A SIMDType with elements permuted as specified by the selection indices.
        /// </returns>
        /// <remarks>
        /// This function uses the _mm_shuffle_ps intrinsic to permute the elements of the input SIMD registers.
        /// The selection indices should be in the range [0, 3] for a 128-bit SIMD register.
        /// </remarks>
        template<UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1>
        static SIMDType Shuffle( SIMDType v1, SIMDType v2 ) noexcept requires( UseShortSIMDType )
        {
            return _mm_shuffle_ps( v1, v2, _MM_SHUFFLE( selection4, selection3, selection2, selection1 ) );
        }

        /// <summary>
        /// Permutes the elements of a 128-bit SIMD register according to the specified selection indices.
        /// </summary>
        /// <typeparam name="selection4">The index for the highest element in the result.</typeparam>
        /// <typeparam name="selection3">The index for the next-highest element in the result.</typeparam>
        /// <typeparam name="selection2">The index for the next-lowest element in the result.</typeparam>
        /// <typeparam name="selection1">The index for the lowest element in the result.</typeparam>
        /// <param name="v1">The SIMD register whose elements will be permuted.</param>
        /// <returns>
        /// A SIMDType with elements permuted as specified by the selection indices.
        /// </returns>
        /// <remarks>
        /// This function uses the _mm_shuffle_ps intrinsic to permute the elements of the input SIMD register.
        /// The selection indices should be in the range [0, 3] for a 128-bit SIMD register.
        /// </remarks>

        template<UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1>
        static SIMDType Shuffle( SIMDType v1 ) noexcept requires( UseShortSIMDType )
        {
            return _mm_shuffle_ps( v1, v1, _MM_SHUFFLE( selection4, selection3, selection2, selection1 ) );
        }


        /// <summary>
        /// Creates a bitmask from the most significant bits of each packed single-precision (32-bit) 
        /// floating-point element in the SIMD register <paramref name="v"/>.
        /// </summary>
        /// <param name="v">
        /// SIMD register containing packed single-precision floating-point elements.
        /// </param>
        /// <returns>
        /// An integer bitmask where each bit corresponds to the most significant bit of each element in <paramref name="v"/>.
        /// For 128-bit SIMD, returns a 4-bit mask; for 256-bit SIMD, returns an 8-bit mask.
        /// </returns>
        /// <remarks>
        /// - For short SIMD types (128-bit), uses <c>_mm_movemask_ps</c>.
        /// - For long SIMD types (256-bit), uses <c>_mm256_movemask_ps</c>.
        /// This is typically used for quick checks of sign bits or for conditional operations.
        /// </remarks>
        static int MoveMask( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_movemask_ps( v );
            }
            else
            {
                return _mm256_movemask_ps( v );
            }
        }

        /// <summary>
        /// Creates a bitmask from the most significant bits of each packed single-precision (32-bit)
        /// floating-point element in the SIMD integer register <paramref name="v"/>.
        /// </summary>
        /// <param name="v">
        /// SIMD integer register containing packed 32-bit integer elements.
        /// </param>
        /// <returns>
        /// An integer bitmask where each bit corresponds to the most significant bit of each element in <paramref name="v"/>.
        /// For 128-bit SIMD, returns a 4-bit mask; for 256-bit SIMD, returns an 8-bit mask.
        /// </returns>
        /// <remarks>
        /// - For short SIMD types (128-bit), uses <c>_mm_movemask_ps</c> after casting to <c>__m128</c>.
        /// - For long SIMD types (256-bit), uses <c>_mm256_movemask_ps</c> after casting to <c>__m256</c>.
        /// This is typically used for quick checks of sign bits or for conditional operations.
        /// </remarks>
        static int MoveMask( SIMDIntegerType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_movemask_ps( _mm_castsi128_ps( v ) );
            }
            else
            {
                return _mm256_movemask_ps( _mm256_castsi256_ps( v ) );
            }
        }

    private:
        /// <summary>
        /// Permute implementation for shuffle masks that select elements from both input vectors.
        ///
        /// This generic implementation of <c>PermuteImpl</c> allows for flexible permutation of elements
        /// from two SIMD registers (<c>v1</c> and <c>v2</c>) based on the shuffle mask and selection flags.
        /// The <c>shuffle</c> parameter specifies the permutation pattern, while the <c>v2x</c>, <c>v2y</c>,
        /// <c>v2z</c>, and <c>v2w</c> flags indicate whether each corresponding element in the result should
        /// be selected from <c>v2</c> (<c>true</c>) or <c>v1</c> (<c>false</c>).
        ///
        /// The function creates a selection mask, permutes both input vectors, and blends the results
        /// according to the mask, returning the final permuted SIMD register.
        ///
        /// <typeparam name="shuffle">The shuffle mask to use for permuting the elements.</typeparam>
        /// <typeparam name="v2x">If true, select the X element from v2; otherwise from v1.</typeparam>
        /// <typeparam name="v2y">If true, select the Y element from v2; otherwise from v1.</typeparam>
        /// <typeparam name="v2z">If true, select the Z element from v2; otherwise from v1.</typeparam>
        /// <typeparam name="v2w">If true, select the W element from v2; otherwise from v1.</typeparam>
        /// <param name="v1">The first SIMD register.</param>
        /// <param name="v2">The second SIMD register.</param>
        /// <returns>
        /// A SIMDType with elements permuted and selected from <c>v1</c> and <c>v2</c> as specified.
        /// </returns>
        /// <remarks>
        /// Uses <c>_mm_shuffle_ps</c> to permute both input vectors, then blends the results using
        /// bitwise operations and the selection mask.
        /// </remarks>
        template<UInt32 shuffle, bool v2x, bool v2y, bool v2z, bool v2w>
        struct PermuteImpl
        {
            static SIMDType Permute( SIMDType v1, SIMDType v2 ) noexcept
            {
                constexpr SIMDType selectMask =
                { {
                        v2x ? std::bit_cast< Type >( 0xFFFFFFFF ) : static_cast< Type >( 0 ),
                        v2y ? std::bit_cast< Type >( 0xFFFFFFFF ) : static_cast< Type >( 0 ),
                        v2z ? std::bit_cast< Type >( 0xFFFFFFFF ) : static_cast< Type >( 0 ),
                        v2w ? std::bit_cast< Type >( 0xFFFFFFFF ) : static_cast< Type >( 0 )
                } };

                auto shuffled1 = _mm_shuffle_ps( v1, v1, shuffle );
                auto shuffled2 = _mm_shuffle_ps( v2, v2, shuffle );

                auto masked1 = _mm_andnot_ps( selectMask, shuffled1 );
                auto masked2 = _mm_and_ps( selectMask, shuffled2 );

                return _mm_or_ps( masked1, masked2 );
            }
        };

        /// <summary>
        /// Permute implementation for shuffle masks that only read from the first vector.
        /// 
        /// This specialization of <c>PermuteImpl</c> is used when all elements of the result
        /// are selected from the first input SIMD vector (<c>v1</c>). The shuffle mask
        /// determines the permutation pattern, and the second input vector is ignored.
        /// 
        /// <typeparam name="shuffle">
        /// The shuffle mask to use for permuting the elements.
        /// </typeparam>
        /// <param name="v1">
        /// The SIMD register whose elements will be permuted.
        /// </param>
        /// <param name="">
        /// Unused second SIMD register.
        /// </param>
        /// <returns>
        /// A SIMDType with elements permuted as specified by the shuffle mask.
        /// </returns>
        /// <remarks>
        /// Uses <c>_mm_shuffle_ps</c> to permute the elements of <c>v1</c>.
        /// </remarks>
        template<UInt32 shuffle>
        struct PermuteImpl<shuffle, false, false, false, false>
        {
            static SIMDType Permute( SIMDType v1, SIMDType ) noexcept
            {
                return _mm_shuffle_ps( v1, v1, shuffle );
            }
        };

        /// <summary>
        /// Permute implementation for shuffle masks that only read from the second vector.
        /// 
        /// This specialization of <c>PermuteImpl</c> is used when all elements of the result
        /// are selected from the second input SIMD vector (<c>v2</c>). The shuffle mask
        /// determines the permutation pattern, and the first input vector is ignored.
        /// 
        /// <typeparam name="shuffle">
        /// The shuffle mask to use for permuting the elements.
        /// </typeparam>
        /// <param name="">
        /// Unused first SIMD register.
        /// </param>
        /// <param name="v2">
        /// The SIMD register whose elements will be permuted.
        /// </param>
        /// <returns>
        /// A SIMDType with elements permuted as specified by the shuffle mask.
        /// </returns>
        /// <remarks>
        /// Uses <c>_mm_shuffle_ps</c> to permute the elements of <c>v2</c>.
        /// </remarks>
        template<UInt32 shuffle>
        struct PermuteImpl<shuffle, true, true, true, true>
        {
            static SIMDType Permute( SIMDType, SIMDType  v2 ) noexcept
            {
                return _mm_shuffle_ps( v2, v2, shuffle );
            }
        };

        /// <summary>
        /// Permute implementation for shuffle masks that read the first two elements from the first vector
        /// and the last two elements from the second vector.
        /// 
        /// This specialization of <c>PermuteImpl</c> is used when the result vector's first two elements
        /// are selected from the first input SIMD vector (<c>v1</c>), and the last two elements are selected
        /// from the second input SIMD vector (<c>v2</c>). The shuffle mask determines the permutation pattern.
        /// 
        /// <typeparam name="shuffle">
        /// The shuffle mask to use for permuting the elements.
        /// </typeparam>
        /// <param name="v1">
        /// The SIMD register whose first two elements will be used in the result.
        /// </param>
        /// <param name="v2">
        /// The SIMD register whose last two elements will be used in the result.
        /// </param>
        /// <returns>
        /// A SIMDType with elements permuted as specified by the shuffle mask.
        /// </returns>
        /// <remarks>
        /// Uses <c>_mm_shuffle_ps</c> to permute the elements of <c>v1</c> and <c>v2</c>.
        /// </remarks>
        template<UInt32 shuffle>
        struct PermuteImpl<shuffle, false, false, true, true>
        {
            static SIMDType Permute( SIMDType v1, SIMDType v2 ) noexcept
            {
                return _mm_shuffle_ps( v1, v2, shuffle );
            }
        };

        /// <summary>
        /// Permute implementation for shuffle masks that read XY from the second vector and ZW from the first.
        /// 
        /// This specialization of <c>PermuteImpl</c> is used when the result vector's first two elements
        /// are selected from the second input SIMD vector (<c>v2</c>), and the last two elements are selected
        /// from the first input SIMD vector (<c>v1</c>). The shuffle mask determines the permutation pattern.
        /// 
        /// <typeparam name="shuffle">
        /// The shuffle mask to use for permuting the elements.
        /// </typeparam>
        /// <param name="v1">
        /// The SIMD register whose last two elements will be used in the result.
        /// </param>
        /// <param name="v2">
        /// The SIMD register whose first two elements will be used in the result.
        /// </param>
        /// <returns>
        /// A SIMDType with elements permuted as specified by the shuffle mask.
        /// </returns>
        /// <remarks>
        /// Uses <c>_mm_shuffle_ps</c> to permute the elements of <c>v2</c> and <c>v1</c>.
        /// </remarks>
        template<UInt32 shuffle>
        struct PermuteImpl<shuffle, true, true, false, false>
        {
            static SIMDType Permute( SIMDType v1, SIMDType v2 ) noexcept
            {
                return _mm_shuffle_ps( v2, v1, shuffle );
            }
        };
    public:

         /// <summary>
         /// Permutes and blends elements from two SIMD vectors according to the compile-time indices.
         /// </summary>
         /// <typeparam name="X">Index for the lowest element in the result (0..7). If &gt;=4 selects from v2.</typeparam>
         /// <typeparam name="Y">Index for the next element in the result (0..7). If &gt;=4 selects from v2.</typeparam>
         /// <typeparam name="Z">Index for the next element in the result (0..7). If &gt;=4 selects from v2.</typeparam>
         /// <typeparam name="W">Index for the highest element in the result (0..7). If &gt;=4 selects from v2.</typeparam>
         /// <param name="v1">First input SIMD vector. Elements with indices 0..3 are taken from this vector when index &lt; 4.</param>
         /// <param name="v2">Second input SIMD vector. Elements with indices 4..7 are taken from this vector when index &gt;= 4.</param>
         /// <returns>
         /// A SIMDType containing elements selected and arranged according to template indices X, Y, Z and W.
         /// Elements are chosen from v1 when the corresponding index is in range [0,3], otherwise from v2
         /// (index values are masked to their low two bits when forming the shuffle control).
         /// </returns>
         /// <remarks>
         /// The implementation computes a 4-lane shuffle mask using _MM_SHUFFLE applied to the low two
         /// bits of each index. It then determines, for each lane, whether the element should be selected
         /// from v2 (index > 3). Finally, the function dispatches to an appropriate PermuteImpl specialization
         /// selected by the computed shuffle and per-lane source flags (v2x/v2y/v2z/v2w).
         /// This provides a compile-time optimized permutation/blend that avoids runtime branching.
         /// </remarks>
        template<UInt32 X, UInt32 Y, UInt32 Z, UInt32 W>
        static inline SIMDType Permute( SIMDType v1, SIMDType v2 ) noexcept
        {
            constexpr UInt32 shuffle = _MM_SHUFFLE( W & 3, Z & 3, Y & 3, X & 3 );

            constexpr bool v2x = X > 3;
            constexpr bool v2y = Y > 3;
            constexpr bool v2z = Z > 3;
            constexpr bool v2w = W > 3;

            return PermuteImpl<shuffle, v2x, v2y, v2z, v2w>::Permute( v1, v2 );
        }

        // Special-case permute templates
        
        /// <summary>
        /// Specialization of the compile-time Permute template for the identity permutation.
        /// </summary>
        /// <remarks>
        /// This overload corresponds to the compile-time indices &lt;0,1,2,3&gt; which represent
        /// the identity shuffle for a 4-lane 128-bit SIMD register (or the corresponding lower
        /// 4 lanes of a wider register). Because the requested permutation selects each element
        /// from the same position it occupies in the input, the function simply returns the
        /// first input operand unchanged.
        /// 
        /// The second SIMD operand is intentionally unused in this specialization and is present
        /// only to match the general Permute signature that accepts two inputs. The function is
        /// constexpr and noexcept, enabling use in compile-time contexts and guaranteeing no
        /// side-effects.
        /// </remarks>
        /// <param name="v1">The input SIMD value whose elements are returned unchanged.</param>
        /// <param name="">Unused second SIMD operand (ignored).</param>
        /// <returns>Returns <paramref name="v1"/> unchanged.</returns>
        template<>
        static inline constexpr SIMDType Permute<0, 1, 2, 3>( SIMDType v1, SIMDType ) noexcept
        {
            return v1;
        }

        /// <summary>
        /// Permutes SIMD vector elements by selecting elements 4, 5, 6, 7, which returns the second vector unchanged.
        /// </summary>
        /// <param name="">The first SIMD vector (unused in this permutation).</param>
        /// <param name="v2">The second SIMD vector to return.</param>
        /// <returns>The second SIMD vector, as indices 4-7 correspond to all elements of v2.</returns>
        template<>
        static inline constexpr SIMDType Permute<4, 5, 6, 7>( SIMDType, SIMDType v2 ) noexcept
        {
            return v2;
        }

        /// <summary>
        /// Permute specialization that builds a 4-element result by taking the lower two element
        /// from the first operand <c>v1</c> and the lower two element from the second operand <c>v2</c>.
        /// </summary>
        /// <remarks>
        /// This is a compile-time specialization of the generic <c>Permute</c> template for the
        /// indices &lt;0,1,4,5&gt;. It produces the result vector:
        /// result[0] = v1[0], result[1] = v1[1], result[2] = v2[0], result[3] = v2[1].
        ///
        /// The implementation uses the SSE intrinsic <c>_mm_movelh_ps</c> which moves the low
        /// 64 bits (two floats) from the second source into the high 64 bits of the result and
        /// keeps the low 64 bits from the first source. This provides an efficient hardware
        /// instruction for this particular lane combination.
        ///
        /// Constraints:
        /// - This specialization is valid for the "short" SIMD type (128-bit, __m128).
        /// - The function is noexcept and constexpr-eligible via compile-time template selection.
        /// </remarks>
        /// <param name="v1">The first input SIMD register (source for lanes 0 and 1).</param>
        /// <param name="v2">The second input SIMD register (source for lanes 2 and 3).</param>
        /// <returns>
        /// A SIMDType containing lanes { v1[0], v1[1], v2[0], v2[1] } in that order.
        /// </returns>

        template<>
        static inline SIMDType Permute<0, 1, 4, 5>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_movelh_ps( v1, v2 );
        }

        /// <summary>
        /// Permutes elements from two SIMD vectors by selecting specific indexed elements to create a new vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector, source for elements at positions 0 and 1 of the result.</param>
        /// <param name="v2">The second SIMD vector, source for elements at positions 2 and 3 of the result.</param>
        /// <returns>A SIMD vector containing the high elements of v2 in the low positions and the high elements of v1 in the high positions.</returns>
        template<>
        static inline SIMDType Permute<6, 7, 2, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_movehl_ps( v1, v2 );
        }

        /// <summary>
        /// Permutes elements from two SIMD vectors by interleaving the lower elements.
        /// </summary>
        /// <param name="v1">The first SIMD vector providing elements at positions 0 and 1.</param>
        /// <param name="v2">The second SIMD vector providing elements at positions 4 and 5.</param>
        /// <returns>A SIMD vector containing the interleaved lower elements in the order [v1[0], v2[0], v1[1], v2[1]].</returns>
        template<>
        static inline SIMDType Permute<0, 4, 1, 5>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_unpacklo_ps( v1, v2 );
        }
        
        /// <summary>
        /// Permute specialization that interleaves the high 64-bit halves of two 128-bit float vectors.
        /// </summary>
        /// <remarks>
        /// This specialization implements the compile-time permutation indices &lt;2, 6, 3, 7&gt;.
        /// Indices are interpreted as follows: values 0..3 select lanes from the first input operand
        /// <c>v1</c>, and values 4..7 select lanes from the second input operand <c>v2</c> (index - 4).
        ///
        /// The implementation uses the SSE intrinsic <c>_mm_unpackhi_ps</c> which takes the high
        /// 64-bit halves (elements 2 and 3) of each source and interleaves them. The resulting element
        /// mapping (lowest to highest element) is:
        /// 
        /// result[0] = v1[2]
        /// result[1] = v2[2]
        /// result[2] = v1[3]
        /// result[3] = v2[3]
        ///
        /// This specialization provides an efficient hardware mapping for the requested element selection
        /// by directly leveraging the unpack high intrinsic without additional shuffles or blends.
        /// </remarks>
        /// <param name="v1">First input SIMD vector (source for indices 0..3).</param>
        /// <param name="v2">Second input SIMD vector (source for indices 4..7).</param>
        /// <returns>
        /// A <c>SIMDType</c> containing lanes { v1[2], v2[2], v1[3], v2[3] } in that order.
        /// </returns>
        template<>
        static inline SIMDType Permute<2, 6, 3, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_unpackhi_ps( v1, v2 );
        }

        /// <summary>
        /// Permute specialization that builds a 4-element result by selecting
        /// the high 64-bit lanes from two 128-bit float vectors.
        /// </summary>
        /// <remarks>
        /// This specialization corresponds to the compile-time permutation indices
        /// &lt;2, 3, 6, 7&gt; where indices in the range [0,3] select lanes from the
        /// first operand (<c>v1</c>) and indices in the range [4,7] select lanes
        /// from the second operand (<c>v2</c>) (an index &gt;= 4 selects from <c>v2</c>
        /// using index-4). The resulting element mapping (lowest to highest element) is:
        /// 
        /// result[0] = v1[2]
        /// result[1] = v1[3]
        /// result[2] = v2[2]
        /// result[3] = v2[3]
        ///
        /// The implementation uses an efficient 64-bit-lane unpack of the high halves:
        /// it reinterprets the input <c>__m128</c> values as <c>__m128d</c> (two 64-bit
        /// lanes), performs <c>_mm_unpackhi_pd</c> to assemble the desired high-lane
        /// elements and then reinterprets the result back to <c>__m128</c>.
        /// </remarks>
        /// <param name="v1">First input SIMD vector (source for indices 0..3).</param>
        /// <param name="v2">Second input SIMD vector (source for indices 4..7).</param>
        /// <returns>
        /// A <c>SIMDType</c> containing elements selected and arranged according
        /// to the compile-time indices &lt;2,3,6,7&gt;.
        /// </returns>
        template<>
        static inline SIMDType Permute<2, 3, 6, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_castpd_ps( _mm_unpackhi_pd( _mm_castps_pd( v1 ), _mm_castps_pd( v2 ) ) );
        }

        /// <summary>
        /// Permute specialization that selects lane mapping &lt;4,1,2,3&gt; from two 4-element float vectors.
        /// </summary>
        /// <remarks>
        /// This specialization produces a 4-element result where:
        /// result[0] is taken from the second input operand <paramref name="v2"/> (index 4 maps to v2[0]),
        /// result[1]..result[3] are taken from the first input operand <paramref name="v1"/> (indices 1,2,3).
        /// The resulting element mapping (lowest to highest element) is:
        /// 
        /// result[0] = v2[0]
        /// result[1] = v1[1]
        /// result[2] = v1[2]
        /// result[3] = v1[3]
        /// 
        /// Implementation details:
        /// - Uses the SSE intrinsic <c>_mm_blend_ps</c> with an 8-bit immediate mask of <c>0x1</c>.
        ///   The mask bit layout for <c>_mm_blend_ps</c> sets which lanes come from the second operand;
        ///   mask bit 0 corresponds to the lowest lane. Therefore <c>0x1</c> selects only the lowest
        ///   lane from <paramref name="v2"/>, leaving the remaining lanes from <paramref name="v1"/>.
        /// - The function is noexcept and has no side effects.
        /// </remarks>
        /// 
        /// <param name="v1">First input SIMD register (provides elements 1..3 in the result).</param>
        /// <param name="v2">Second input SIMD register (provides element 0 in the result).</param>
        ///
        /// <returns>
        /// A <c>SIMDType</c> (typically <c>__m128</c>) containing lanes { v2[0], v1[1], v1[2], v1[3] }.
        /// </returns>
        template<>
        static inline SIMDType Permute<4, 1, 2, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x1 );
        }

        /// <summary>
        /// Permutes elements from two SIMD vectors by selecting specific indices from each vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to permute from.</param>
        /// <param name="v2">The second SIMD vector to permute from.</param>
        /// <returns>A SIMD vector containing the permuted elements according to the specified indices.</returns>
        template<>
        static inline SIMDType Permute<0, 5, 2, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x2 );
        }
        /// <summary>
        /// Permutes elements from two SIMD vectors by selecting specific indexed elements from each input vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector providing elements at indices 4 and 5.</param>
        /// <param name="v2">The second SIMD vector providing elements at indices 2 and 3.</param>
        /// <returns>A SIMD vector containing the permuted elements in the order specified by the template arguments <4, 5, 2, 3>.</returns>
        template<>
        static inline SIMDType Permute<4, 5, 2, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x3 );
        }
        /// <summary>
        /// Permutes elements from two SIMD vectors by selecting specific indices from each vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to select elements from.</param>
        /// <param name="v2">The second SIMD vector to select elements from.</param>
        /// <returns>A SIMD vector containing the permuted elements: {v1[0], v1[1], v2[2], v1[3]}.</returns>
        template<>
        static inline SIMDType Permute<0, 1, 6, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x4 );
        }
        /// <summary>
		/// Permutes elements from two SIMD vectors by selecting specific indices from each vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to select elements from.</param>
        /// <param name="v2">The second SIMD vector to select elements from.</param>
        /// <returns>A SIMD vector containing the permuted elements: {v1[0], v1[1], v2[2], v1[3]}.</returns>
        template<>
        static inline SIMDType Permute<4, 1, 6, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x5 );
        }
        /// <summary>
        /// Permutes elements from two SIMD vectors by selecting elements at indices 0, 5, 6, and 3.
        /// </summary>
        /// <param name="v1">The first SIMD vector to permute from.</param>
        /// <param name="v2">The second SIMD vector to permute from.</param>
        /// <returns>A SIMD vector containing elements selected according to the permutation pattern: element 0 from v1, element 1 (5-4) from v2, element 2 (6-4) from v2, and element 3 from v1.</returns>
        template<>
        static inline SIMDType Permute<0, 5, 6, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x6 );
        }
        template<>
        static inline SIMDType Permute<4, 5, 6, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x7 );
        }
        template<>
        static inline SIMDType Permute<0, 1, 2, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x8 );
        }
        template<>
        static inline SIMDType Permute<4, 1, 2, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x9 );
        }
        template<>
        static inline SIMDType Permute<0, 5, 2, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0xA );
        }
        template<>
        static inline SIMDType Permute<4, 5, 2, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0xB );
        }
        template<>
        static inline SIMDType Permute<0, 1, 6, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0xC );
        }
        template<>
        static inline SIMDType Permute<4, 1, 6, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0xD );
        }
        template<>
        static inline SIMDType Permute<0, 5, 6, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0xE );
        }

        /// <summary>
        /// Defines a control vector for use with Select.
        /// </summary>
        /// <param name="index0">
        /// Determines the source of the first element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index1">
        /// Determines the source of the second element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index2">
        /// Determines the source of the third element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index3">
        /// Determines the source of the fourth element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        static SIMDType SelectControl( UInt32 index0 = 0, UInt32 index1 = 0, UInt32 index2 = 0, UInt32 index3 = 0 ) noexcept
            requires( UseShortSIMDType )
        {
            auto tmp = _mm_set_epi32( static_cast< int >( index3 ), static_cast< int >( index2 ), static_cast< int >( index1 ), static_cast< int >( index0 ) );
            tmp = _mm_cmpgt_epi32( tmp, { {0,0,0,0} } );
            return _mm_castsi128_ps( tmp );
        }

        /// <summary>
        /// Defines a control vector for use with Select.
        /// </summary>
        /// <param name="index0">
        /// Determines the source of the first element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index1">
        /// Determines the source of the second element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index2">
        /// Determines the source of the third element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index3">
        /// Determines the source of the fourth element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index4">
        /// Determines the source of the fifth element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index5">
        /// Determines the source of the sixth element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index6">
        /// Determines the source of the seventh element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        /// <param name="index7">
        /// Determines the source of the eight element of the
        /// result of the Select. If 0 the select will choose the 
        /// corresponding element from the first vector, otherwise 
        /// the corresponding element from the second vector will 
        /// be selected.
        /// </param>
        static SIMDType SelectControl( UInt32 index0 = 0, UInt32 index1 = 0, UInt32 index2 = 0, UInt32 index3 = 0, UInt32 index4 = 0, UInt32 index5 = 0, UInt32 index6 = 0, UInt32 index7 = 0 ) noexcept
            requires( UseShortSIMDType == false )
        {
            auto tmp = _mm256_set_epi32( static_cast< int >( index7 ), static_cast< int >( index6 ), static_cast< int >( index5 ), static_cast< int >( index4 ), static_cast< int >( index3 ), static_cast< int >( index2 ), static_cast< int >( index1 ), static_cast< int >( index0 ) );
            tmp = _mm256_cmpgt_epi32( tmp, { {0,0,0,0,0,0,0,0} } );
            return _mm256_castsi256_ps( tmp );
        }

        /// <summary>
        /// Performs a per-component selection between two input vectors and returns the resulting vector.
        /// </summary>
        /// <param name="v1">
        /// The first source to select elements from.
        /// </param>
        /// <param name="v2">
        /// The second source to select elements from.
        /// </param>
        /// <param name="control">
        /// Mask used to select an element from either v1 or v2. If an element in control is zero, 
        /// the returned SIMDType corresponding element will be from v1, if an element control is 
        /// 0xFFFFFFFF, the returned SIMDType corresponding element will be from v2.
        /// </param>
        static SIMDType Select( SIMDType v1, SIMDType v2, SIMDType control ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                auto rmm1 = _mm_castsi128_ps( _mm_andnot_epi32( _mm_castps_si128( control ), _mm_castps_si128( v1 ) ) );
                //auto rmm1 = _mm_andnot_ps( control, v1 );
                auto rmm2 = _mm_and_ps( v2, control );
                return  _mm_castsi128_ps( _mm_or_epi32( _mm_castps_si128( rmm1 ), _mm_castps_si128( rmm2 ) ) );
                //return  _mm_or_ps( rmm1, rmm2 );
            }
            else
            {
                auto rmm1 = _mm256_andnot_ps( control, v1 );
                auto rmm2 = _mm256_and_ps( v2, control );
                return _mm256_or_ps( rmm1, rmm2 );
            }
        }

        /// <summary>
        /// Performs a per-component selection between two input vectors and returns the resulting vector.
        /// </summary>
        /// <param name="v1">
        /// The first source to select elements from.
        /// </param>
        /// <param name="v2">
        /// The second source to select elements from.
        /// </param>
        /// <param name="control">
        /// Mask used to select an element from either v1 or v2. If an element in control is zero, 
        /// the returned SIMDType corresponding element will be from v1, if an element control is 
        /// 0xFFFFFFFF, the returned SIMDType corresponding element will be from v2.
        /// </param>
        static SIMDType Select( SIMDType v1, SIMDType v2, SIMDIntegerType control ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                auto rmm1 = _mm_andnot_ps( _mm_castsi128_ps( control ), v1 );
                auto rmm2 = _mm_and_ps( v2, _mm_castsi128_ps( control ) );
                return _mm_or_ps( rmm1, rmm2 );
            }
            else
            {
                auto rmm1 = _mm256_andnot_ps( _mm256_castsi256_ps( control ), v1 );
                auto rmm2 = _mm256_and_ps( v2, _mm256_castsi256_ps( control ) );
                return _mm256_or_ps( rmm1, rmm2 );
            }
        }

        static SIMDIntegerType Select( SIMDIntegerType v1, SIMDIntegerType v2, SIMDIntegerType control ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                auto rmm1 = _mm_andnot_epi32( control, v1 );
                auto rmm2 = _mm_and_epi32( v2, control );
                return _mm_or_epi32( rmm1, rmm2 );
            }
            else
            {
                auto rmm1 = _mm256_andnot_epi32( control, v1 );
                auto rmm2 = _mm256_and_epi32( v2, control );
                return _mm256_or_epi32( rmm1, rmm2 );
            }
        }

        static SIMDIntegerType Select( SIMDIntegerType v1, SIMDIntegerType v2, SIMDType control ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                auto rmm1 = _mm_andnot_epi32( _mm_castps_si128( control ), v1 );
                auto rmm2 = _mm_and_epi32( v2, _mm_castps_si128( control ) );
                return _mm_or_epi32( rmm1, rmm2 );
            }
            else
            {
                auto rmm1 = _mm256_andnot_epi32( _mm256_castps_si256( control ), v1 );
                auto rmm2 = _mm256_and_epi32( v2, _mm256_castps_si256( control ) );
                return _mm256_or_epi32( rmm1, rmm2 );
            }
        }




        /// <summary>
        /// Unpack and interleave single-precision (32-bit) floating-point elements 
        /// from the high half v1 and v2, returning the results.
        /// </summary>
        static SIMDType UnpackHigh( SIMDType v1, SIMDType v2 ) noexcept requires( UseShortSIMDType )
        {
            return _mm_unpackhi_ps( v1, v2 );
        }

        /// <summary>
        /// Unpack and interleave single-precision (32-bit) floating-point elements 
        /// from the high half of each 128-bit lane in v1 and v2, returning the results.
        /// </summary>
        static SIMDType UnpackHigh( SIMDType v1, SIMDType v2 ) noexcept requires( UseShortSIMDType == false )
        {
            return _mm256_unpackhi_ps( v1, v2 );
        }

        /// <summary>
        /// Unpack and interleave single-precision (32-bit) floating-point elements 
        /// from the low half of v1 and v2, returning the results.
        /// </summary>
        static SIMDType UnpackLow( SIMDType v1, SIMDType v2 ) noexcept requires( UseShortSIMDType )
        {
            return _mm_unpacklo_ps( v1, v2 );
        }

        /// <summary>
        /// Unpack and interleave single-precision (32-bit) floating-point elements 
        /// from the low half of each 128-bit lane in v1 and v2, returning the results. 
        /// </summary>
        static SIMDType UnpackLow( SIMDType v1, SIMDType v2 ) noexcept requires( UseShortSIMDType == false )
        {
            return _mm256_unpacklo_ps( v1, v2 );
        }

        /// <summary>
        /// Combines the two upper single-precision (32-bit) floating-point elements from v1,
        /// and the two lower single-precision (32-bit) floating-point elements from v2, returning the results.
        /// </summary>
        static SIMDType High2Low2( SIMDType v1, SIMDType v2 ) noexcept requires( UseShortSIMDType )
        {
            return _mm_castpd_ps( _mm_move_sd( _mm_castps_pd( v1 ), _mm_castps_pd( v2 ) ) );
        }

        /// <summary>
        /// Combines the three upper single-precision (32-bit) floating-point elements from v1,
        /// and the lower single-precision (32-bit) floating-point elements from v2, returning the results.
        /// </summary>
        static SIMDType High3Low1( SIMDType v1, SIMDType v2 ) noexcept requires( UseShortSIMDType )
        {
            return _mm_move_ss( v1, v2 );
        }

        /// <summary>
        /// Checks if each element in a SIMD vector is infinite (positive or negative infinity).
        /// </summary>
        /// <param name="v">The SIMD vector to check for infinity values.</param>
        /// <returns>
        /// A SIMD vector with elements set to indicate whether the corresponding element 
        /// in the input is infinite. Uses all bits set (true) for infinite values 
        /// and all bits clear (false) for finite values.</returns>
        static SIMDType IsInf( SIMDType v ) noexcept
        {
            auto tmp = And( v, Constants::AbsMask );
            return Equal( tmp, Constants::Infinity );
        }

        /// <summary>
        /// Checks if each element in a SIMD vector is negative infinity.
        /// </summary>
        /// <param name="v">The SIMD vector to test.</param>
        /// <returns>A SIMD vector where each element is set to indicate whether the corresponding element in the input is negative infinity.</returns>
        static SIMDType IsNegativeInf( SIMDType v ) noexcept
        {
            return Equal( v, Fill( Constants::NegativeInfinityValue ) );
        }

        /// <summary>
        /// Checks if a SIMD value is negative infinity or NaN (Not a Number).
        /// </summary>
        /// <param name="v">The SIMD value to check.</param>
        /// <returns>A SIMD value with elements set to indicate whether the corresponding element in the input is negative infinity or NaN.</returns>
        static SIMDType IsNegativeInfOrNaN( SIMDType v ) noexcept
        {
            auto isNegativeInf = IsNegativeInf( v );
            auto isNaN = IsNaN( v );
            return Or( isNegativeInf, isNaN );
        }

        /// <summary>
        /// Checks if each element in a SIMD vector is positive infinity.
        /// </summary>
        /// <param name="v">The SIMD vector to test for positive infinity values.</param>
        /// <returns>A SIMD vector with each element set to indicate whether the corresponding element in the input is positive infinity.</returns>
        static SIMDType IsPositiveInf( SIMDType v ) noexcept
        {
            return Equal( v, Fill( Constants::InfinityValue ) );
        }

        /// <summary>
        /// Determines whether each element in a SIMD vector is positive infinity or NaN (Not a Number).
        /// </summary>
        /// <param name="v">The SIMD vector to test.</param>
        /// <returns>A SIMD vector where each element is set to indicate whether the corresponding element in the input is positive infinity or NaN.</returns>
        static SIMDType IsPositiveInfOrNaN( SIMDType v ) noexcept
        {
            auto isPositiveInf = IsPositiveInf( v );
            auto isNaN = IsNaN( v );
            return Or( isPositiveInf, isNaN );
        }

        /// <summary>
        /// Checks if all components of a SIMD vector are zero.
        /// </summary>
        /// <param name="v">The SIMD vector to test.</param>
        /// <returns>A SIMD vector containing the result of the zero comparison for each component.</returns>
        static SIMDType IsZero( SIMDType v ) noexcept
        {
            return Equal( v, _mm_setzero_ps( ) );
        }

        /// <summary>
        /// Checks if a SIMD vector contains NaN (Not-a-Number) values.
        /// </summary>
        /// <param name="v">The SIMD vector to check for NaN values.</param>
        /// <returns>A SIMD vector where each element is the result of the NaN check for the corresponding element in the input vector. Elements that are NaN will have a truthy value, while non-NaN elements will have a falsy value.</returns>
        static SIMDType IsNaN( SIMDType v ) noexcept
        {
            return NotEqual( v, v );
        }

        /// <summary>
        /// Returns true if at least one of the values in <c>v</c> is NaN,
        /// otherwise false.
        /// </summary>
        /// <param name="v">
        /// A SIMDType holding the values to test.
        /// </param>
        /// <returns>
        /// Returns true if at least one of the values in <c>v</c> is NaN,
        /// otherwise false.
        /// </returns>

        static bool HasNaN( SIMDType v ) noexcept
        {
            auto tmp = IsNaN( v );
            return AnyTrue( tmp );
        }

        /// <summary>
        /// Computes the absolute value of a SIMD vector using a fast bitwise operation.
        /// </summary>
        /// <param name="v">The SIMD vector for which to compute the absolute value.</param>
        /// <returns>A SIMD vector containing the absolute values of the input vector's elements.</returns>
        static SIMDType FastAbs( SIMDType v ) noexcept
        {
            return And( v, Fill( Constants::AbsMaskValue ) );
        }

        /// <summary>
        /// Computes the absolute value of a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector for which to compute the absolute value.</param>
        /// <returns>A SIMD vector containing the absolute values of the elements in the input vector.</returns>
        static SIMDType Abs( SIMDType v ) noexcept
        {
            return Max( Sub( Zero( ), v ), v );
        }

        /// <summary>
        /// Computes the absolute value of the X component while preserving the Y, Z, and W components.
        /// </summary>
        /// <param name="v">The SIMD vector whose X component will have its absolute value computed.</param>
        /// <returns>A SIMD vector with the absolute value of the X component and unchanged Y, Z, and W components.</returns>
        static SIMDType AbsX( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select1222 );
        }

        /// <summary>
        /// Computes the absolute value of the Y component while preserving other components of a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector whose Y component will have its absolute value computed.</param>
        /// <returns>A SIMD vector with the absolute value applied to the Y component and other components unchanged.</returns>
        static SIMDType AbsY( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select2122 );
        }

        /// <summary>
        /// Computes the absolute value of the Z component while preserving other components.
        /// </summary>
        /// <param name="v">The SIMD vector whose Z component will have its absolute value computed.</param>
        /// <returns>A SIMD vector with the absolute value applied to the Z component and other components unchanged.</returns>
        static SIMDType AbsZ( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select2212 );
        }

        /// <summary>
        /// Computes the absolute value of the W component while preserving other components.
        /// </summary>
        /// <param name="v">The SIMD vector whose W component will have its absolute value computed.</param>
        /// <returns>A SIMD vector with the absolute value applied to the W component and other components unchanged.</returns>
        static SIMDType AbsW( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select2221 );
        }

        /// <summary>
        /// Computes the absolute value of the X and Y components of a SIMD vector, leaving Z and W unchanged.
        /// </summary>
        /// <param name="v">The SIMD vector whose X and Y components will have their absolute values computed.</param>
        /// <returns>A SIMD vector with the absolute values of the X and Y components from the input vector, and the original Z and W components.</returns>
        static SIMDType AbsXY( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select1122 );
        }


        /// <summary>
        /// Computes the element-wise minimum of two SIMD vectors.
        /// </summary>
        /// <param name="lhs">The first SIMD vector to compare.</param>
        /// <param name="rhs">The second SIMD vector to compare.</param>
        /// <returns>A SIMD vector containing the minimum values from each corresponding element pair.</returns>
        static SIMDType Min( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_min_ps( lhs, rhs );
            }
            else
            {
                return _mm256_min_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Computes the element-wise maximum of two SIMD vectors.
        /// </summary>
        /// <param name="lhs">The first SIMD vector to compare.</param>
        /// <param name="rhs">The second SIMD vector to compare.</param>
        /// <returns>A SIMD vector containing the maximum values from each corresponding element pair.</returns>
        static SIMDType Max( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_max_ps( lhs, rhs );
            }
            else
            {
                return _mm256_max_ps( lhs, rhs );
            }
        }

        /// <summary>
        /// Computes the minimum value across all elements in a SIMD vector (horizontal minimum reduction).
        /// </summary>
        /// <param name="v">The SIMD vector containing the values to reduce.</param>
        /// <returns>The minimum value found across all elements in the vector.</returns>
        static Type HorizontalMin( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_cvtss_f32( v );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_cvtss_f32( _mm_min_ps( v, _mm_permute_ps( v, 1 ) ) );
                }
                else if constexpr ( N == 3 )
                {
                    return _mm_cvtss_f32( _mm_min_ps( v, _mm_min_ps( _mm_permute_ps( v, 0b11'01'00'10 ), _mm_permute_ps( v, 0b11'00'10'01 ) ) ) );
                }
                else // N == 4
                {
                    return _mm_cvtss_f32( _mm_min_ps( _mm_min_ps( v, _mm_permute_ps( v, 0b10'01'00'11 ) ),
                        _mm_min_ps( _mm_permute_ps( v, 0b01'00'11'10 ), _mm_permute_ps( v, 0b00'11'10'01 ) ) ) );
                }
            }
            else
            {
                __m128 low = _mm256_castps256_ps128( v );
                __m128 high = _mm256_extractf128_ps( v, 1 );
                auto rmm1 = _mm_min_ps( _mm_min_ps( low, _mm_permute_ps( low, 0b10'01'00'11 ) ),
                    _mm_min_ps( _mm_permute_ps( low, 0b01'00'11'10 ), _mm_permute_ps( low, 0b00'11'10'01 ) ) );
                if constexpr ( N == 5 )
                {
                    auto rmm2 = _mm_min_ps( high, rmm1 );
                    return _mm_cvtss_f32( rmm2 );
                }
                else if constexpr ( N == 6 )
                {
                    auto rmm2 = _mm_min_ps( _mm_min_ps( high, _mm_permute_ps( high, 1 ) ), rmm1 );
                    return _mm_cvtss_f32( rmm2 );
                }
                else if constexpr ( N == 7 )
                {
                    auto rmm2 = _mm_min_ps( _mm_min_ps( high, _mm_min_ps( _mm_permute_ps( high, 0b11'01'00'10 ), _mm_permute_ps( high, 0b11'00'10'01 ) ) ), rmm1 );
                    return _mm_cvtss_f32( rmm2 );
                }
                else // N == 8 
                {
                    auto rmm2 = _mm_min_ps( _mm_min_ps( _mm_min_ps( high, _mm_permute_ps( high, 0b10'01'00'11 ) ),
                        _mm_min_ps( _mm_permute_ps( high, 0b01'00'11'10 ), _mm_permute_ps( high, 0b00'11'10'01 ) ) ), rmm1 );
                    return _mm_cvtss_f32( rmm2 );
                }
            }
        }

        /// <summary>
        /// Computes the maximum value across all elements in a SIMD vector by performing horizontal max operations.
        /// </summary>
        /// <param name="v">The SIMD vector containing the values to find the maximum from.</param>
        /// <returns>The maximum value found across all elements in the SIMD vector.</returns>
        static Type HorizontalMax( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_cvtss_f32( v );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_cvtss_f32( _mm_max_ps( v, _mm_permute_ps( v, 1 ) ) );
                }
                else if constexpr ( N == 3 )
                {
                    return _mm_cvtss_f32( _mm_max_ps( v, _mm_max_ps( _mm_permute_ps( v, 0b11'01'00'10 ), _mm_permute_ps( v, 0b11'00'10'01 ) ) ) );
                }
                else // N == 4
                {
                    return _mm_cvtss_f32( _mm_max_ps( _mm_max_ps( v, _mm_permute_ps( v, 0b10'01'00'11 ) ),
                        _mm_max_ps( _mm_permute_ps( v, 0b01'00'11'10 ), _mm_permute_ps( v, 0b00'11'10'01 ) ) ) );
                }
            }
            else
            {
                __m128 low = _mm256_castps256_ps128( v );
                __m128 high = _mm256_extractf128_ps( v, 1 );
                auto rmm1 = _mm_max_ps( _mm_max_ps( low, _mm_permute_ps( low, 0b10'01'00'11 ) ),
                    _mm_max_ps( _mm_permute_ps( low, 0b01'00'11'10 ), _mm_permute_ps( low, 0b00'11'10'01 ) ) );
                if constexpr ( N == 5 )
                {
                    auto rmm2 = _mm_max_ps( high, rmm1 );
                    return _mm_cvtss_f32( rmm2 );
                }
                else if constexpr ( N == 6 )
                {
                    auto rmm2 = _mm_max_ps( _mm_max_ps( high, _mm_permute_ps( high, 1 ) ), rmm1 );
                    return _mm_cvtss_f32( rmm2 );
                }
                else if constexpr ( N == 7 )
                {
                    auto rmm2 = _mm_max_ps( _mm_max_ps( high, _mm_max_ps( _mm_permute_ps( high, 0b11'01'00'10 ), _mm_permute_ps( high, 0b11'00'10'01 ) ) ), rmm1 );
                    return _mm_cvtss_f32( rmm2 );
                }
                else // N == 8 
                {
                    auto rmm2 = _mm_max_ps( _mm_max_ps( _mm_max_ps( high, _mm_permute_ps( high, 0b10'01'00'11 ) ),
                        _mm_max_ps( _mm_permute_ps( high, 0b01'00'11'10 ), _mm_permute_ps( high, 0b00'11'10'01 ) ) ), rmm1 );
                    return _mm_cvtss_f32( rmm2 );
                }
            }
        }


        /// <summary>
        /// Rounds each element of a SIMD vector to the nearest integer value.
        /// </summary>
        /// <param name="v">The SIMD vector containing floating-point values to round.</param>
        /// <returns>A SIMD vector with each element rounded to the nearest integer value.</returns>
        static SIMDType Round( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_round_ps( v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC );
            }
            else
            {
                return _mm256_round_ps( v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC );
            }
        }

        /// <summary>
        /// Truncates the floating-point values in a SIMD vector toward zero, removing the fractional part.
        /// </summary>
        /// <param name="v">The SIMD vector containing floating-point values to truncate.</param>
        /// <returns>A SIMD vector containing the truncated floating-point values.</returns>
        static SIMDType Truncate( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_round_ps( v, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC );
            }
            else
            {
                return _mm256_round_ps( v, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC );
            }
        }

        /// <summary>
        /// Computes the floor of each element in a SIMD vector, rounding toward negative infinity.
        /// </summary>
        /// <param name="v">The SIMD vector containing the values to floor.</param>
        /// <returns>A SIMD vector with each element rounded down to the nearest integer value.</returns>
        static SIMDType Floor( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_round_ps( v, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC );
            }
            else
            {
                return _mm256_round_ps( v, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC );
            }
        }

        /// <summary>
        /// Computes the ceiling of each element in a SIMD vector, rounding each value up to the nearest integer.
        /// </summary>
        /// <param name="v">The SIMD vector containing the values to round up.</param>
        /// <returns>A SIMD vector with each element rounded up to the nearest integer.</returns>
        static SIMDType Ceil( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_round_ps( v, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC );
            }
            else
            {
                return _mm256_round_ps( v, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC );
            }
        }

        /// <summary>
        /// Clamps SIMD vector values to be within specified lower and upper bounds.
        /// </summary>
        /// <param name="v">The SIMD vector to clamp.</param>
        /// <param name="lowerBounds">The SIMD vector containing the minimum allowed values.</param>
        /// <param name="upperBounds">The SIMD vector containing the maximum allowed values.</param>
        /// <returns>A SIMD vector with each element clamped between the corresponding elements in lowerBounds and upperBounds.</returns>
        static SIMDType Clamp( SIMDType v, SIMDType lowerBounds, SIMDType upperBounds ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_min_ps( upperBounds, _mm_max_ps( lowerBounds, v ) );
            }
            else
            {
                return _mm256_min_ps( upperBounds, _mm256_max_ps( lowerBounds, v ) );
            }
        }

        /// <summary>
        /// Checks if a value is within the symmetric bounds defined by another value.
        /// </summary>
        /// <param name="v">The value to check against the bounds.</param>
        /// <param name="bounds">The positive bound value. The actual bounds are [-bounds, bounds].</param>
        /// <returns>A SIMD vector where each element is set to indicate whether the corresponding element in 'v' is within the range [-bounds, bounds].</returns>
        static SIMDType InBounds( SIMDType v, SIMDType bounds ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                SIMDType minusOne = Constants::NegativeOne;
                auto temp1 = LessOrEqual( v, bounds );
                auto temp2 = Mul( bounds, minusOne );
                temp2 = LessOrEqual( temp2, v );
                return And( temp1, temp2 );
            }
            else
            {
                SIMDType minusOne = { { -1.f, -1.f, -1.f, -1.f, -1.f,-1.f,-1.f,-1.f} };
                auto temp1 = LessOrEqual( v, bounds );
                auto temp2 = Mul( bounds, minusOne );
                temp2 = LessOrEqual( temp2, v );
                return And( temp1, temp2 );
            }
        }



        /// <summary>
        /// Performs linear interpolation between two SIMD vectors.
        /// </summary>
        /// <param name="v1">The starting SIMD vector.</param>
        /// <param name="v2">The ending SIMD vector.</param>
        /// <param name="t">The interpolation factor, typically in the range [0, 1].</param>
        /// <returns>A SIMD vector containing the result of the linear interpolation: v1 * (1 - t) + v2 * t.</returns>
        static SIMDType Lerp( SIMDType v1, SIMDType v2, Type t ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_ps( Fill<Size>( t ), v2, _mm_mul_ps( Fill<Size>( 1.f - t ), v1 ) );
            }
            else
            {
                return _mm256_fmadd_ps( Fill<Size>( t ), v2, _mm256_mul_ps( Fill<Size>( 1.f - t ), v1 ) );
            }
        }

        /// <summary>
        /// Performs linear interpolation between two SIMD vectors.
        /// </summary>
        /// <param name="v1">The starting SIMD vector value.</param>
        /// <param name="v2">The ending SIMD vector value.</param>
        /// <param name="t">The interpolation factor SIMD vector, typically in the range [0, 1].</param>
        /// <returns>A SIMD vector containing the interpolated values computed as v1 * (1 - t) + v2 * t.</returns>
        static SIMDType Lerp( SIMDType v1, SIMDType v2, SIMDType t ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_ps( t, v2, _mm_mul_ps( _mm_sub_ps( Fill<Size>( 1.f ), t ), v1 ) );
            }
            else
            {
                return _mm256_fmadd_ps( t, v2, _mm256_mul_ps( _mm256_sub_ps( Fill<Size>( 1.f ), t ), v1 ) );
            }
        }
        /// <summary>
        /// Performs linear interpolation between two SIMD vectors using fused multiply-add operations.
        /// </summary>
        /// <param name="v1">The starting SIMD vector value.</param>
        /// <param name="v2">The ending SIMD vector value.</param>
        /// <param name="t">The interpolation factor, typically in the range [0, 1].</param>
        /// <returns>A SIMD vector containing the interpolated values, computed as (1-t)*v1 + t*v2.</returns>
        static SIMDType Lerp2( SIMDType v1, SIMDType v2, Type t ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_ps( Fill<Size>( t ), v2, _mm_mul_ps( Fill<Size>( 1.f - t ), v1 ) );
            }
            else
            {
                return _mm256_fmadd_ps( Fill<Size>( t ), v2, _mm256_mul_ps( Fill<Size>( 1.f - t ), v1 ) );
            }
        }

        /// <summary>
        /// Performs linear interpolation between two SIMD vectors using the formula: (1-t)*v1 + t*v2.
        /// </summary>
        /// <param name="v1">The start vector (result when t=0).</param>
        /// <param name="v2">The end vector (result when t=1).</param>
        /// <param name="t">The interpolation factor, typically in the range [0, 1].</param>
        /// <returns>The interpolated SIMD vector.</returns>
        static SIMDType Lerp2( SIMDType v1, SIMDType v2, SIMDType t ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_ps( t, v2, _mm_mul_ps( _mm_sub_ps( Fill<Size>( 1.f ), t ), v1 ) );
            }
            else
            {
                return _mm256_fmadd_ps( t, v2, _mm256_mul_ps( _mm256_sub_ps( Fill<Size>( 1.f ), t ), v1 ) );
            }
        }

        /// <summary>
        /// Clamps all components of a SIMD vector to the range [0.0, 1.0].
        /// </summary>
        /// <param name="v">The SIMD vector to saturate.</param>
        /// <returns>A SIMD vector with all components clamped between 0.0 and 1.0.</returns>
        static SIMDType Saturate( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_min_ps( _mm_max_ps( v, { { 0.0f, 0.0f, 0.0f, 0.0f } } ), { { 1.0f, 1.0f, 1.0f, 1.0f } } );
            }
            else
            {
                return _mm256_min_ps( _mm256_max_ps( v, { { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f } } ), { { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f } } );
            }
        }

        /// <summary>
        /// Negates all elements of a SIMD vector by subtracting them from zero.
        /// </summary>
        /// <param name="v">The SIMD vector to negate.</param>
        /// <returns>A SIMD vector containing the negated values of the input vector.</returns>
        static SIMDType Negate( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_ps( _mm_setzero_ps( ), v );
            }
            else
            {
                return _mm256_sub_ps( _mm256_setzero_ps( ), v );
            }
        }

        /// <summary>
        /// Negates only the X component of a SIMD vector while preserving other components.
        /// </summary>
        /// <param name="v">The SIMD vector whose X component will be negated.</param>
        /// <returns>A SIMD vector with the X component negated and all other components unchanged.</returns>
        static SIMDType NegateX( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select1222 );
        }

        /// <summary>
        /// Negates only the Y component of a SIMD vector while preserving other components.
        /// </summary>
        /// <param name="v">The SIMD vector whose Y component will be negated.</param>
        /// <returns>A SIMD vector with the Y component negated and all other components unchanged.</returns>
        static SIMDType NegateY( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select2122 );
        }

        /// <summary>
        /// Negates the Z component of a SIMD vector while preserving other components.
        /// </summary>
        /// <param name="v">The SIMD vector whose Z component will be negated.</param>
        /// <returns>A SIMD vector with the Z component negated and all other components unchanged.</returns>
        static SIMDType NegateZ( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select2212 );
        }

        /// <summary>
        /// Negates only the W component of a SIMD vector while preserving the X, Y, and Z components.
        /// </summary>
        /// <param name="v">The SIMD vector whose W component will be negated.</param>
        /// <returns>A SIMD vector with the W component negated and X, Y, Z components unchanged.</returns>
        static SIMDType NegateW( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select2221 );
        }

        /// <summary>
        /// Negates the X and Y components of a SIMD vector while preserving the Z and W components.
        /// </summary>
        /// <param name="v">The SIMD vector whose X and Y components will be negated.</param>
        /// <returns>A SIMD vector with negated X and Y components and unchanged Z and W components.</returns>
        static SIMDType NegateXY( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select1122 );
        }


        /// <summary>
        /// Reduces angles to the range [-π, π] by wrapping them modulo 2π.
        /// </summary>
        /// <param name="v">A SIMD vector containing angle values (in radians) to be normalized.</param>
        /// <returns>A SIMD vector with the input angles reduced to the principal range by subtracting multiples of 2π.</returns>
        static SIMDType ModAngles( SIMDType v ) noexcept
        {
            constexpr Type Inv2PiValue = static_cast< Type >( 0.15915494309189533577 );
            constexpr Type PiTimes2Value = static_cast< Type >( 2. * M_PI );
            constexpr SIMDType Inv2Pi = { {Inv2PiValue,Inv2PiValue,Inv2PiValue,Inv2PiValue} };
            constexpr SIMDType PiTimes2 = { {PiTimes2Value,PiTimes2Value,PiTimes2Value,PiTimes2Value} };

            auto result = Round( Mul( v, Inv2Pi ) );
            return FNMAdd( result, PiTimes2, v );
        }

        /// <summary>
        /// Computes the sine and cosine of a SIMD vector of angles simultaneously using polynomial approximation.
        /// </summary>
        /// <param name="v">A SIMD vector containing the input angles in radians.</param>
        /// <param name="cosines">Pointer to a SIMD vector that will receive the computed cosine values.</param>
        /// <returns>A SIMD vector containing the computed sine values corresponding to the input angles.</returns>
        static SIMDType FastSinCos( SIMDType v, SIMDType* cosines ) noexcept
        {
            auto x = ModAngles( v );

            auto sign = And( x, Constants::NegativeZero );
            auto c = Or( Constants::Pi, sign );
            auto absx = AndNot( sign, x );
            auto rflx = Sub( c, x );
            auto comp = LessOrEqual( absx, Constants::HalfPi );
            auto select0 = And( comp, x );
            auto select1 = AndNot( comp, rflx );
            x = Or( select0, select1 );
            select0 = And( comp, Constants::One );
            select1 = AndNot( comp, Constants::NegativeOne );
            sign = Or( select0, select1 );

            auto x2 = Mul( x, x );

            // Cosine
            SIMDType vConstantsB = Constants::CosCoefficient1;
            SIMDType vConstants = Constants::CosCoefficient2;
            auto Result = FMAdd( vConstantsB, x2, vConstants );

            vConstants = Constants::CosCoefficient3;
            Result = FMAdd( Result, x2, vConstants );

            vConstants = Constants::CosCoefficient4;
            Result = FMAdd( Result, x2, vConstants );

            vConstants = Constants::CosCoefficient5;
            Result = FMAdd( Result, x2, vConstants );

            Result = FMAdd( Result, x2, Constants::One );
            Result = Mul( Result, sign );

            *cosines = Result;


            // Sine
            vConstantsB = Constants::SinCoefficient1;
            vConstants = Constants::SinCoefficient2;
            Result = FMAdd( vConstantsB, x2, vConstants );

            vConstants = Constants::SinCoefficient3;
            Result = FMAdd( Result, x2, vConstants );

            vConstants = Constants::SinCoefficient4;
            Result = FMAdd( Result, x2, vConstants );

            vConstants = Constants::SinCoefficient5;
            Result = FMAdd( Result, x2, vConstants );

            Result = FMAdd( Result, x2, Constants::One );
            return Mul( Result, x );

        }

        /// <summary>
        /// Computes the sine of an angle using a fast SIMD approximation with polynomial evaluation.
        /// </summary>
        /// <param name="v">The input angle(s) in radians to compute the sine of.</param>
        /// <returns>The sine of the input angle(s), computed using a polynomial approximation.</returns>
        static SIMDType FastSin( SIMDType v ) noexcept
        {
            auto x = ModAngles( v );

            auto sign = And( x, Constants::NegativeZero );
            auto c = Or( Constants::Pi, sign );
            auto absx = AndNot( sign, x );
            auto rflx = Sub( c, x );
            auto comp = LessOrEqual( absx, Constants::HalfPi );
            auto select0 = And( comp, x );
            auto select1 = AndNot( comp, rflx );
            x = Or( select0, select1 );

            auto x2 = Mul( x, x );

            auto result = FMAdd( Constants::SinCoefficient1, x2, Constants::SinCoefficient2 );
            result = FMAdd( result, x2, Constants::SinCoefficient3 );
            result = FMAdd( result, x2, Constants::SinCoefficient4 );
            result = FMAdd( result, x2, Constants::SinCoefficient5 );

            result = FMAdd( result, x2, Constants::One );
            return Mul( result, x );

        }

        /// <summary>
        /// Computes the cosine of each component in a SIMD vector using a fast polynomial approximation.
        /// </summary>
        /// <param name="v">The input SIMD vector containing angle values in radians.</param>
        /// <returns>A SIMD vector containing the cosine of each input angle component.</returns>
        static SIMDType FastCos( SIMDType v ) noexcept
        {
            auto x = ModAngles( v );

            auto sign = And( x, Constants::NegativeZero );
            auto c = Or( Constants::Pi, sign );
            auto absx = AndNot( sign, x );
            auto rflx = Sub( c, x );
            auto comp = LessOrEqual( absx, Constants::HalfPi );
            auto select0 = And( comp, x );
            auto select1 = AndNot( comp, rflx );
            x = Or( select0, select1 );
            select0 = And( comp, Constants::One );
            select1 = AndNot( comp, Constants::NegativeOne );
            sign = Or( select0, select1 );

            auto x2 = Mul( x, x );

            auto result = FMAdd( Constants::CosCoefficient1, x2, Constants::CosCoefficient2 );

            result = FMAdd( result, x2, Constants::CosCoefficient3 );

            result = FMAdd( result, x2, Constants::CosCoefficient4 );

            result = FMAdd( result, x2, Constants::CosCoefficient5 );

            result = FMAdd( result, x2, Constants::One );
            return Mul( result, sign );
        }

        /// <summary>
        /// Computes an approximation of the tangent function for SIMD vector values using a polynomial approximation.
        /// </summary>
        /// <param name="v">The input SIMD vector containing angle values in radians for which to compute the tangent.</param>
        /// <returns>A SIMD vector containing the approximated tangent values corresponding to the input angles.</returns>
        static SIMDType FastTan( SIMDType v ) noexcept
        {
            constexpr SIMDType Mask = { { 0x1, 0x1, 0x1, 0x1 } };

            auto va = Mul( v, Constants::TwoOverPi );
            va = Round( va );

            auto vc = FNMSub( va, Constants::HalfPi, v );
            vc = FNMSub( va, Constants::TanCoefficient9, vc );

            auto vb = Abs( va );
            vb = _mm_blend_ps( vb, Constants::Zero, 1 );

            auto vc2 = Mul( vc, vc );

            auto vbIsEven = And( vb, Mask );
            vbIsEven = SameValue( vbIsEven, Constants::Zero );

            auto n = FMAdd( vc2, Constants::TanCoefficient8, Constants::TanCoefficient7 );
            auto d = FMAdd( vc2, Constants::TanCoefficient5, Constants::TanCoefficient4 );
            n = FMAdd( vc2, n, Constants::TanCoefficient6 );
            d = FMAdd( vc2, d, Constants::TanCoefficient3 );
            n = Mul( vc2, n );
            d = FMAdd( vc2, d, Constants::TanCoefficient2 );
            n = FMAdd( vc, n, vc );
            auto vcNearZero = InBounds( vc, Constants::TanNearZero );
            d = FMAdd( vc2, d, Constants::TanCoefficient1 );

            n = Select( n, vc, vcNearZero );
            d = Select( d, Constants::One, vcNearZero );

            auto r0 = Negate( n );
            auto r1 = Div( n, d );
            r0 = Div( d, r0 );

            auto isZero = Equal( v, Constants::Zero );

            auto result = Select( r0, r1, vbIsEven );

            return Select( result, Constants::Zero, isZero );
        }

        /// <summary>
        /// Computes the arctangent (inverse tangent) of a SIMD vector using a fast polynomial approximation.
        /// </summary>
        /// <param name="v">The input SIMD vector containing values for which to compute the arctangent.</param>
        /// <returns>A SIMD vector containing the arctangent of the input values in radians.</returns>
        static SIMDType FastATan( SIMDType v ) noexcept
        {
            auto absV = Abs( v );
            auto invV = Div( Constants::One, v );
            auto comp = Greater( v, Constants::One );
            auto select0 = And( comp, Constants::One );
            auto select1 = AndNot( comp, Constants::NegativeOne );
            auto sign = Or( select0, select1 );
            comp = LessOrEqual( absV, Constants::One );
            select0 = And( comp, Constants::Zero );
            select1 = AndNot( comp, sign );
            sign = Or( select0, select1 );
            select0 = And( comp, v );
            select1 = AndNot( comp, invV );
            auto x = Or( select0, select1 );

            auto x2 = Mul( x, x );

            // Compute polynomial approximation

            auto vConstantsB = Constants::ATanCoefficient8;
            auto vConstants = Constants::ATanCoefficient7;
            auto Result = FMAdd( vConstantsB, x2, vConstants );

            vConstants = Constants::ATanCoefficient6;
            Result = FMAdd( Result, x2, vConstants );

            vConstants = Constants::ATanCoefficient5;
            Result = FMAdd( Result, x2, vConstants );


            vConstants = Constants::ATanCoefficient4;
            Result = FMAdd( Result, x2, vConstants );

            vConstants = Constants::ATanCoefficient3;
            Result = FMAdd( Result, x2, vConstants );

            vConstants = Constants::ATanCoefficient2;
            Result = FMAdd( Result, x2, vConstants );

            vConstants = Constants::ATanCoefficient1;
            Result = FMAdd( Result, x2, vConstants );

            Result = FMAdd( Result, x2, Constants::One );

            Result = Mul( Result, x );
            auto result1 = Mul( sign, Constants::HalfPi );
            result1 = Sub( result1, Result );

            comp = Equal( sign, Constants::Zero );
            select0 = And( comp, Result );
            select1 = AndNot( comp, result1 );
            return Or( select0, select1 );
        }

        /// <summary>
        /// Computes the fast approximate arctangent of x/y (atan2) using SIMD operations.
        /// </summary>
        /// <param name="x">The x-coordinate (numerator) SIMD vector.</param>
        /// <param name="y">The y-coordinate (denominator) SIMD vector.</param>
        /// <returns>A SIMD vector containing the angle in radians between the positive x-axis and the point (y, x), handling special cases for zero and infinity values.</returns>
        static SIMDType FastATan2( SIMDType x, SIMDType y ) noexcept
        {
            auto xEqualsZero = Equal( x, Constants::Zero );
            auto yEqualsZero = Equal( y, Constants::Zero );
            auto yIsPositive = And( y, Constants::NegativeZero );
            yIsPositive = SameValue( yIsPositive, Constants::Zero );
            auto xEqualsInfinity = IsInf( x );
            auto yEqualsInfinity = IsInf( y );

            auto xSign = And( x, Constants::NegativeZero );
            auto Pi = Or( Constants::Pi, xSign );
            auto PiOverTwo = Or( Constants::HalfPi, xSign );
            auto PiOverFour = Or( Constants::PiOver4, xSign );
            auto ThreePiOverFour = Or( Constants::ThreePiOver4, xSign );

            auto R1 = Select( Pi, xSign, yIsPositive );

            auto R2 = Select( Constants::True, PiOverTwo, yEqualsZero );
            auto R3 = Select( R2, R1, xEqualsZero );
            auto R4 = Select( ThreePiOverFour, PiOverFour, yIsPositive );
            auto R5 = Select( PiOverTwo, R4, yEqualsInfinity );
            auto Result = Select( R3, R5, xEqualsInfinity );
            auto atanValid = SameValue( Result, Constants::True );

            auto V = Div( x, y );

            auto R0 = FastATan( V );

            R1 = Select( Pi, Constants::NegativeZero, yIsPositive );
            R2 = Add( R0, R1 );

            return Select( Result, R2, atanValid );
        }


        /// <summary>
        /// Computes the sine of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing input values in radians.</param>
        /// <returns>A SIMD vector containing the sine of each corresponding element in the input vector.</returns>
        static SIMDType Sin( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sin_ps( v );
            }
            else
            {
                return _mm256_sin_ps( v );
            }
        }

        /// <summary>
        /// Computes the cosine of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing input values in radians.</param>
        /// <returns>A SIMD vector containing the cosine of each corresponding element in the input vector.</returns>
        static SIMDType Cos( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cos_ps( v );
            }
            else
            {
                return _mm256_cos_ps( v );
            }
        }

        /// <summary>
        /// Computes the sine and cosine of each element in a SIMD vector simultaneously.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input angles in radians.</param>
        /// <param name="cosines">Pointer to a SIMD vector where the cosine values will be stored.</param>
        /// <returns>A SIMD vector containing the sine values corresponding to the input angles.</returns>
        static SIMDType SinCos( SIMDType v, SIMDType* cosines ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sincos_ps( cosines, v );
            }
            else
            {
                return _mm256_sincos_ps( cosines, v );
            }
        }

        /// <summary>
        /// Computes the tangent of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing input values in radians.</param>
        /// <returns>A SIMD vector containing the tangent of each corresponding element in the input vector.</returns>
        static SIMDType Tan( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_tan_ps( v );
            }
            else
            {
                return _mm256_tan_ps( v );
            }
        }

        /// <summary>
        /// Computes the arcsine (inverse sine) of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values for which to compute the arcsine.</param>
        /// <returns>A SIMD vector containing the arcsine of each element in the input vector.</returns>
        static SIMDType ASin( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_asin_ps( v );
            }
            else
            {
                return _mm256_asin_ps( v );
            }
        }

        /// <summary>
        /// Computes the arccosine (inverse cosine) of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing input values for which to compute the arccosine.</param>
        /// <returns>A SIMD vector containing the arccosine of each element in the input vector, with results in radians.</returns>
        static SIMDType ACos( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_acos_ps( v );
            }
            else
            {
                return _mm256_acos_ps( v );
            }
        }

        /// <summary>
        /// Computes the arctangent (inverse tangent) of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the values for which to compute the arctangent.</param>
        /// <returns>A SIMD vector containing the arctangent of each corresponding element in the input vector.</returns>
        static SIMDType ATan( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_atan_ps( v );
            }
            else
            {
                return _mm256_atan_ps( v );
            }
        }

        /// <summary>
        /// Computes the four-quadrant arctangent of y/x for SIMD vectors.
        /// </summary>
        /// <param name="x">A SIMD vector containing the x-coordinates.</param>
        /// <param name="y">A SIMD vector containing the y-coordinates.</param>
        /// <returns>A SIMD vector containing the arctangent of y/x in radians, with values in the range [-π, π].</returns>
        static SIMDType ATan2( SIMDType x, SIMDType y ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_atan2_ps( x, y );
            }
            else
            {
                return _mm256_atan2_ps( x, y );
            }
        }

        /// <summary>
        /// Computes the hyperbolic sine of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the hyperbolic sine of each corresponding element in the input vector.</returns>
        static SIMDType SinH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sinh_ps( v );
            }
            else
            {
                return _mm256_sinh_ps( v );
            }
        }

        /// <summary>
        /// Computes the hyperbolic cosine of a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing values for which to compute the hyperbolic cosine.</param>
        /// <returns>A SIMD vector containing the hyperbolic cosine of each element in the input vector.</returns>
        static SIMDType CosH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cosh_ps( v );
            }
            else
            {
                return _mm256_cosh_ps( v );
            }
        }

        /// <summary>
        /// Computes the hyperbolic tangent of a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the hyperbolic tangent of each element in the input vector.</returns>
        static SIMDType TanH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_tanh_ps( v );
            }
            else
            {
                return _mm256_tanh_ps( v );
            }
        }

        /// <summary>
        /// Computes the inverse hyperbolic sine (asinh) of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the inverse hyperbolic sine of each corresponding element in the input vector.</returns>
        static SIMDType ASinH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_asinh_ps( v );
            }
            else
            {
                return _mm256_asinh_ps( v );
            }
        }

        /// <summary>
        /// Computes the inverse hyperbolic cosine (arcosh) of SIMD vector elements.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the inverse hyperbolic cosine of each element in the input vector.</returns>
        static SIMDType ACosH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_acosh_ps( v );
            }
            else
            {
                return _mm256_acosh_ps( v );
            }
        }

        /// <summary>
        /// Computes the hyperbolic arctangent of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the hyperbolic arctangent of each element from the input vector.</returns>
        static SIMDType ATanH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_atanh_ps( v );
            }
            else
            {
                return _mm256_atanh_ps( v );
            }
        }

        /// <summary>
        /// Computes the natural logarithm of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the natural logarithm of each corresponding element in the input vector.</returns>
        static SIMDType Log( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_log_ps( v );
            }
            else
            {
                return _mm256_log_ps( v );
            }
        }

        /// <summary>
        /// Computes the natural logarithm of 1 plus the input value (log(1 + v)) for each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the natural logarithm of 1 plus each input element.</returns>
        static SIMDType Log1P( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_log1p_ps( v );
            }
            else
            {
                return _mm256_log1p_ps( v );
            }
        }

        /// <summary>
        /// Computes the base-10 logarithm of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the base-10 logarithm of each element from the input vector.</returns>
        static SIMDType Log10( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_log10_ps( v );
            }
            else
            {
                return _mm256_log10_ps( v );
            }
        }

        /// <summary>
        /// Computes the base-2 logarithm of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the values for which to compute the logarithm.</param>
        /// <returns>A SIMD vector containing the base-2 logarithm of each element in the input vector.</returns>
        static SIMDType Log2( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_log2_ps( v );
            }
            else
            {
                return _mm256_log2_ps( v );
            }
        }

        /// <summary>
        /// Computes the exponential function (e raised to the power of each element) for a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the exponent values.</param>
        /// <returns>A SIMD vector where each element is e raised to the power of the corresponding element in the input vector.</returns>
        static SIMDType Exp( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_exp_ps( v );
            }
            else
            {
                return _mm256_exp_ps( v );
            }
        }

        /// <summary>
        /// Computes the base-10 exponential (10^x) of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the exponent values.</param>
        /// <returns>A SIMD vector where each element is 10 raised to the power of the corresponding element in the input vector.</returns>
        static SIMDType Exp10( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_exp10_ps( v );
            }
            else
            {
                return _mm256_exp10_ps( v );
            }
        }

        /// <summary>
        /// Computes the base-2 exponential (2^x) of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the exponent values.</param>
        /// <returns>A SIMD vector containing the base-2 exponential of each corresponding element in the input vector.</returns>
        static SIMDType Exp2( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_exp2_ps( v );
            }
            else
            {
                return _mm256_exp2_ps( v );
            }
        }

        /// <summary>
        /// Computes the exponential minus one (e^x - 1) for each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the input values.</param>
        /// <returns>A SIMD vector containing the result of e^x - 1 for each corresponding element in the input vector.</returns>
        static SIMDType ExpM1( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_expm1_ps( v );
            }
            else
            {
                return _mm256_expm1_ps( v );
            }
        }

        /// <summary>
        /// Computes the power of base raised to the exponent for SIMD vector elements.
        /// </summary>
        /// <param name="base">The base values as a SIMD vector.</param>
        /// <param name="exponent">The exponent values as a SIMD vector.</param>
        /// <returns>A SIMD vector containing the result of raising each base element to its corresponding exponent element.</returns>
        static SIMDType Pow( SIMDType base, SIMDType exponent ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_pow_ps( base, exponent );
            }
            else
            {
                return _mm256_pow_ps( base, exponent );
            }
        }

        /// <summary>
        /// Computes the floating-point remainder of x divided by y for SIMD vectors.
        /// </summary>
        /// <param name="x">The dividend SIMD vector.</param>
        /// <param name="y">The divisor SIMD vector.</param>
        /// <returns>A SIMD vector containing the floating-point remainder of x/y for each element.</returns>
        static SIMDType FMod( SIMDType x, SIMDType y ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmod_ps( x, y );
            }
            else
            {
                return _mm256_fmod_ps( x, y );
            }
        }

        /// <summary>
        /// Computes the Euclidean distance (hypotenuse) from the origin for pairs of x and y coordinates using SIMD operations.
        /// </summary>
        /// <param name="x">A SIMD vector containing x-coordinates.</param>
        /// <param name="y">A SIMD vector containing y-coordinates.</param>
        /// <returns>A SIMD vector containing the hypotenuse values (sqrt(x² + y²)) for each pair of coordinates.</returns>
        static SIMDType Hypot( SIMDType x, SIMDType y ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_hypot_ps( x, y );
            }
            else
            {
                return _mm256_hypot_ps( x, y );
            }
        }

        /// <summary>
        /// Checks if all of the first <c>Size</c> number of elements 
        /// are equal to 0xFFFFFFFF.
        /// </summary>
        /// <param name="v"></param>
        /// <returns>
        /// <c>true</c> if all of the first <c>Size</c> number of elements 
        /// are equal to 0xFFFFFFFF, otherwise <c>false</c>.
        /// </returns>
        static bool AllTrue( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return ( _mm_movemask_ps( v ) & 1 ) == 1;
                }
                else if constexpr ( N == 2 )
                {
                    return ( _mm_movemask_ps( v ) & 3 ) == 3;
                }
                else if constexpr ( N == 3 )
                {
                    return ( _mm_movemask_ps( v ) & 7 ) == 7;
                }
                else
                {
                    return ( _mm_movemask_ps( v ) & 15 ) == 15;
                }
            }
            else
            {
                if constexpr ( N == 5 )
                {
                    return ( _mm256_movemask_ps( v ) & 31 ) == 31;
                }
                else if constexpr ( N == 6 )
                {
                    return ( _mm256_movemask_ps( v ) & 63 ) == 63;
                }
                else if constexpr ( N == 7 )
                {
                    return ( _mm256_movemask_ps( v ) & 127 ) == 127;
                }
                else
                {
                    return ( _mm256_movemask_ps( v ) & 255 ) == 255;
                }
            }
        }

        /// <summary>
        /// Checks if any of the first <c>Size</c> number of elements 
        /// are equal to 0xFFFFFFFF.
        /// </summary>
        /// <param name="v"></param>
        /// <returns>
        /// <c>true</c> if any of the first <c>Size</c> number of elements 
        /// are equal to 0xFFFFFFFF, otherwise <c>false</c>.
        /// </returns>
        static bool AnyTrue( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return ( _mm_movemask_ps( v ) & 1 ) != 0;
                }
                else if constexpr ( N == 2 )
                {
                    return ( _mm_movemask_ps( v ) & 3 ) != 0;
                }
                else if constexpr ( N == 3 )
                {
                    return ( _mm_movemask_ps( v ) & 7 ) != 0;
                }
                else
                {
                    return ( _mm_movemask_ps( v ) & 15 ) != 0;
                }
            }
            else
            {
                if constexpr ( N == 5 )
                {
                    return ( _mm256_movemask_ps( v ) & 31 ) != 0;
                }
                else if constexpr ( N == 6 )
                {
                    return ( _mm256_movemask_ps( v ) & 63 ) != 0;
                }
                else if constexpr ( N == 7 )
                {
                    return ( _mm256_movemask_ps( v ) & 127 ) != 0;
                }
                else
                {
                    return ( _mm256_movemask_ps( v ) & 255 ) != 0;
                }
            }
        }





        /// <summary>
        /// Determines whether the elements of v1 are less than 
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is less than the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType Less( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmplt_ps( v1, v2 );
            }
            else
            {
                // LT_OQ => 0x11
                return _mm256_cmp_ps( v1, v2, _CMP_LT_OQ );
            }
        }

        /// <summary>
        /// Checks if all elements in the first SIMD vector are less than the corresponding elements in the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if all elements in v1 are less than the corresponding elements in v2; otherwise, false.</returns>
        static bool AllLess( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = Less( v1, v2 );
            return AllTrue( result );
        }

        /// <summary>
        /// Determines if any element in the first SIMD vector is less than the corresponding element in the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if any element in v1 is less than the corresponding element in v2; otherwise, false.</returns>
        static bool AnyLess( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = Less( v1, v2 );
            return AnyTrue( result );
        }


        /// <summary>
        /// Determines whether the elements of v1 are less than or equal to
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is less than or equal to the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType LessOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmple_ps( v1, v2 );
            }
            else
            {
                // _CMP_LE_OQ => 18
                return _mm256_cmp_ps( v1, v2, _CMP_LE_OQ );
            }
        }

        /// <summary>
        /// Determines whether all corresponding elements in the first SIMD vector are less than or equal to those in the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if all elements in v1 are less than or equal to the corresponding elements in v2; otherwise, false.</returns>
        static bool AllLessOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = LessOrEqual( v1, v2 );
            return AllTrue( result );
        }

        /// <summary>
        /// Determines whether any element in the first SIMD vector is less than or equal to the corresponding element in the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if any element in v1 is less than or equal to the corresponding element in v2; otherwise, false.</returns>
        static bool AnyLessOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = LessOrEqual( v1, v2 );
            return AnyTrue( result );
        }

        /// <summary>
        /// Determines whether the elements of v1 are equal to
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is equal to the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType Equal( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_ps( v1, v2 );
            }
            else
            {
                return _mm256_cmp_ps( v1, v2, _CMP_EQ_OQ );
            }
        }

        /// <summary>
        /// Compares <c>Size</c> elements of v1 and v2,
        /// returning true if all are equal.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// Returns <c>true</c> if the lower <c>Size</c> elements of v1 and v2
        /// are equal.
        /// </returns>
        static bool AllEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = Equal( v1, v2 );
            return AllTrue( result );
        }

        /// <summary>
        /// Determines whether all corresponding elements of two SIMD vectors are equal within a specified tolerance.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <param name="epsilon">The maximum allowed absolute difference between corresponding elements for them to be considered equal.</param>
        /// <returns>True if all corresponding elements differ by at most epsilon; otherwise, false.</returns>
        static bool AllEqual( SIMDType v1, SIMDType v2, SIMDType epsilon ) noexcept
        {
            auto v = Abs( Sub( v1, v2 ) );
            auto rmm1 = LessOrEqual( v, epsilon );
            return AllTrue( rmm1 );
        }

        /// <summary>
        /// Checks if any corresponding elements of two SIMD vectors are equal within a specified epsilon tolerance.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <param name="epsilon">The tolerance value for comparing floating-point equality.</param>
        /// <returns>True if any pair of corresponding elements are equal within epsilon; false otherwise.</returns>
        static bool AnyEqual( SIMDType v1, SIMDType v2, SIMDType epsilon ) noexcept
        {
            auto v = Abs( Sub( v1, v2 ) );
            auto rmm1 = LessOrEqual( v, epsilon );
            return AnyTrue( rmm1 );
        }

        /// <summary>
        /// Determines whether any corresponding elements in two SIMD vectors are equal.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if any corresponding pair of elements are equal; otherwise, false.</returns>
        static bool AnyEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = Equal( v1, v2 );
            return AnyTrue( result );
        }

        /// <summary>
        /// Determines whether the elements of v1 are not equal to
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is not equal to the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType NotEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpneq_ps( v1, v2 );
            }
            else
            {
                return _mm256_cmp_ps( v1, v2, _CMP_NEQ_UQ );
            }
        }

        /// <summary>
        /// Checks if all corresponding elements in two SIMD vectors are not equal.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if all corresponding elements are not equal, false otherwise.</returns>
        static bool AllNotEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = NotEqual( v1, v2 );
            return AllTrue( result );
        }

        /// <summary>
        /// Determines if any elements are not equal between two SIMD vectors.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if any corresponding elements in the two vectors are not equal; otherwise, false.</returns>
        static bool AnyNotEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = NotEqual( v1, v2 );
            return AnyTrue( result );
        }


        /// <summary>
        /// Determines whether the elements of v1 are nearly equal to
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is nearly equal to the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType NearEqual( SIMDType v1, SIMDType v2, SIMDType epsilon ) noexcept
        {
            auto delta = Sub( v1, v2 );
            auto temp = Zero( );
            temp = Sub( temp, delta );
            temp = Max( temp, delta );
            return LessOrEqual( temp, epsilon );
        }

        /// <summary>
        /// Determines whether all corresponding components of two SIMD vectors are approximately equal within a specified tolerance.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <param name="epsilon">The tolerance value used for the approximate equality comparison.</param>
        /// <returns>True if all corresponding components of the two vectors are within epsilon of each other; otherwise, false.</returns>
        static bool AllNearEqual( SIMDType v1, SIMDType v2, SIMDType epsilon ) noexcept
        {
            auto result = NearEqual( v1, v2, epsilon );
            return AllTrue( result );
        }

        /// <summary>
        /// Determines whether any corresponding elements of two SIMD vectors are approximately equal within a specified tolerance.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <param name="epsilon">The SIMD vector containing tolerance values for the comparison.</param>
        /// <returns>True if any pair of corresponding elements are approximately equal within the epsilon tolerance; otherwise, false.</returns>
        static bool AnyNearEqual( SIMDType v1, SIMDType v2, SIMDType epsilon ) noexcept
        {
            auto result = NearEqual( v1, v2, epsilon );
            return AnyTrue( result );
        }


        /// <summary>
        /// Determines whether the elements of v1 are greater than
        /// or equal to the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is greater than or equal to the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType GreaterOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpge_ps( v1, v2 );
            }
            else
            {
                return _mm256_cmp_ps( v1, v2, _CMP_GE_OQ );
            }
        }

        /// <summary>
        /// Determines whether all components of the first SIMD vector are greater than or equal to the corresponding components of the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if all components of v1 are greater than or equal to the corresponding components of v2; otherwise, false.</returns>
        static bool AllGreaterOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = GreaterOrEqual( v1, v2 );
            return AllTrue( result );
        }

        /// <summary>
        /// Determines if any element in the first SIMD vector is greater than or equal to the corresponding element in the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if any element in v1 is greater than or equal to the corresponding element in v2; otherwise, false.</returns>
        static bool AnyGreaterOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = GreaterOrEqual( v1, v2 );
            return AnyTrue( result );
        }


        /// <summary>
        /// Determines whether the elements of v1 are greater than
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is greater than the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType Greater( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpgt_ps( v1, v2 );
            }
            else
            {
                return _mm256_cmp_ps( v1, v2, _CMP_GT_OQ );
            }
        }

        /// <summary>
        /// Determines whether all elements in the first SIMD vector are greater than the corresponding elements in the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if all elements in v1 are greater than the corresponding elements in v2; otherwise, false.</returns>
        static bool AllGreater( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = Greater( v1, v2 );
            return AllTrue( result );
        }

        /// <summary>
        /// Checks if any element in the first SIMD vector is greater than the corresponding element in the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if at least one element in v1 is greater than the corresponding element in v2; otherwise, false.</returns>
        static bool AnyGreater( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = Greater( v1, v2 );
            return AnyTrue( result );
        }



        /// <summary>
        /// Performs binary, element wise comparision of v1 and v2. 
        /// </summary>
        /// <param name="v1">v1</param>
        /// <param name="v2">v2</param>
        /// <returns>
        /// The results of the element wise comparision. An element is
        /// set to 0xFFFFFFFF if the corresponding elements in v1 and v2
        /// have the same binary value, otherwise the element is 0.
        /// </returns>
        static SIMDType SameValue( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_castsi128_ps( _mm_cmpeq_epi32( _mm_castps_si128( v1 ), _mm_castps_si128( v2 ) ) );
            }
            else
            {
                return _mm_castsi256_ps( _mm256_cmpeq_epi32( _mm256_castps_si256( v1 ), _mm256_castps_si256( v2 ) ) );
            }
        }

        /// <summary>
        /// Checks if all corresponding elements in two SIMD vectors have the same value.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if all corresponding elements are equal, false otherwise.</returns>
        static bool AllSameValue( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            return AllTrue( result );
        }

        /// <summary>
        /// Checks if any corresponding elements in two SIMD vectors have the same value.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if at least one pair of corresponding elements are equal; otherwise, false.</returns>
        static bool AnySameValue( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            return AnyTrue( result );
        }

        /// <summary>
        /// Performs binary, element wise comparision of v1 and v2. 
        /// </summary>
        /// <param name="v1">v1</param>
        /// <param name="v2">v2</param>
        /// <returns>
        /// The results of the element wise comparision. An element is
        /// set to 0xFFFFFFFF if the corresponding elements in v1 and v2
        /// have the same binary value, otherwise the element is 0.
        /// </returns>
        static SIMDIntegerType SameValue( SIMDType v1, SIMDIntegerType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_epi32( _mm_castps_si128( v1 ), v2 );
            }
            else
            {
                return _mm256_cmpeq_epi32( _mm256_castps_si256( v1 ), v2 );
            }
        }

        /// <summary>
        /// Checks if all elements in a SIMD vector have the same value when compared to a corresponding SIMD integer vector.
        /// </summary>
        /// <param name="v1">The SIMD vector containing values to compare.</param>
        /// <param name="v2">The SIMD integer vector containing values to compare against.</param>
        /// <returns>True if all element-wise comparisons indicate the same value; otherwise, false.</returns>
        static bool AllSameValue( SIMDType v1, SIMDIntegerType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            if constexpr ( UseShortSIMDType )
            {
                return AllTrue( _mm_castsi128_ps( result ) );
            }
            else
            {
                return AllTrue( _mm_castsi256_ps( result ) );
            }
        }

        /// <summary>
        /// Checks if any element in the first SIMD vector has the same value as the corresponding element in the second SIMD vector.
        /// </summary>
        /// <param name="v1">The first SIMD vector to compare.</param>
        /// <param name="v2">The second SIMD integer vector to compare.</param>
        /// <returns>True if at least one pair of corresponding elements have the same value; otherwise, false.</returns>
        static bool AnySameValue( SIMDType v1, SIMDIntegerType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            if constexpr ( UseShortSIMDType )
            {
                return AnyTrue( _mm_castsi128_ps( result ) );
            }
            else
            {
                return AnyTrue( _mm_castsi256_ps( result ) );
            }
        }


        /// <summary>
        /// Performs binary, element wise comparision of v1 and v2. 
        /// </summary>
        /// <param name="v1">v1</param>
        /// <param name="v2">v2</param>
        /// <returns>
        /// The results of the element wise comparision. An element is
        /// set to 0xFFFFFFFF if the corresponding elements in v1 and v2
        /// have the same binary value, otherwise the element is 0.
        /// </returns>
        static SIMDIntegerType SameValue( SIMDIntegerType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_epi32( v1, _mm_castps_si128( v2 ) );
            }
            else
            {
                return _mm256_cmpeq_epi32( v1, _mm256_castps_si256( v2 ) );
            }
        }

        /// <summary>
        /// Checks if all elements in two SIMD vectors have the same value at corresponding positions.
        /// </summary>
        /// <param name="v1">The first SIMD integer vector to compare.</param>
        /// <param name="v2">The second SIMD vector to compare.</param>
        /// <returns>True if all corresponding elements in both vectors have the same value; otherwise, false.</returns>
        static bool AllSameValue( SIMDIntegerType v1, SIMDType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            if constexpr ( UseShortSIMDType )
            {
                return AllTrue( _mm_castsi128_ps( result ) );
            }
            else
            {
                return AllTrue( _mm_castsi256_ps( result ) );
            }
        }

        /// <summary>
        /// Determines if any element in an integer SIMD vector has the same value as any element in another SIMD vector.
        /// </summary>
        /// <param name="v1">The integer SIMD vector to compare.</param>
        /// <param name="v2">The SIMD vector to compare against.</param>
        /// <returns>True if any element comparison yields a match, false otherwise.</returns>
        static bool AnySameValue( SIMDIntegerType v1, SIMDType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            if constexpr ( UseShortSIMDType )
            {
                return AnyTrue( _mm_castsi128_ps( result ) );
            }
            else
            {
                return AnyTrue( _mm_castsi256_ps( result ) );
            }
        }

        /// <summary>
        /// Performs binary, element wise comparision of v1 and v2. 
        /// </summary>
        /// <param name="v1">v1</param>
        /// <param name="v2">v2</param>
        /// <returns>
        /// The results of the element wise comparision. An element is
        /// set to 0xFFFFFFFF if the corresponding elements in v1 and v2
        /// have the same binary value, otherwise the element is 0.
        /// </returns>
        static SIMDIntegerType SameValue( SIMDIntegerType v1, SIMDIntegerType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_epi32( v1, v2 );
            }
            else
            {
                return _mm256_cmpeq_epi32( v1, v2 );
            }
        }

        /// <summary>
        /// Checks if all corresponding elements in two SIMD integer vectors have the same value.
        /// </summary>
        /// <param name="v1">The first SIMD integer vector to compare.</param>
        /// <param name="v2">The second SIMD integer vector to compare.</param>
        /// <returns>True if all corresponding elements in the two vectors are equal, false otherwise.</returns>
        static bool AllSameValue( SIMDIntegerType v1, SIMDIntegerType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            if constexpr ( UseShortSIMDType )
            {
                return AllTrue( _mm_castsi128_ps( result ) );
            }
            else
            {
                return AllTrue( _mm_castsi256_ps( result ) );
            }
        }

        /// <summary>
        /// Determines if any corresponding elements in two SIMD integer vectors have the same value.
        /// </summary>
        /// <param name="v1">The first SIMD integer vector to compare.</param>
        /// <param name="v2">The second SIMD integer vector to compare.</param>
        /// <returns>True if at least one pair of corresponding elements are equal, false otherwise.</returns>
        static bool AnySameValue( SIMDIntegerType v1, SIMDIntegerType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            if constexpr ( UseShortSIMDType )
            {
                return AnyTrue( _mm_castsi128_ps( result ) );
            }
            else
            {
                return AnyTrue( _mm_castsi256_ps( result ) );
            }
        }


        /// <summary>
        /// Computes the square root of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the values to compute square roots for.</param>
        /// <returns>A SIMD vector containing the square root of each corresponding element in the input vector.</returns>
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
        /// Computes the approximate reciprocal square root of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the values for which to compute the reciprocal square root.</param>
        /// <returns>A SIMD vector containing the approximate reciprocal square root (1/√x) of each element in the input vector.</returns>
        static SIMDType ReciprocalSqrt( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_rsqrt_ps( v );
            }
            else
            {
                return _mm256_rsqrt_ps( v );
            }
        }


        /// <summary>
        /// Computes the cube root of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing the values for which to compute cube roots.</param>
        /// <returns>A SIMD vector containing the cube root of each element from the input vector.</returns>
        static SIMDType Cbrt( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cbrt_ps( v );
            }
            else
            {
                return _mm256_cbrt_ps( v );
            }
        }


        /// <summary>
        /// Computes the approximate reciprocal of each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector whose elements will have their reciprocals computed.</param>
        /// <returns>A SIMD vector containing the approximate reciprocal (1/x) of each element from the input vector.</returns>
        static SIMDType Reciprocal( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_rcp_ps( v );
            }
            else
            {
                return _mm256_rcp_ps( v );
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

        /// <summary>
        /// Computes the dot product of two SIMD vectors.
        /// </summary>
        /// <param name="a">The first SIMD vector.</param>
        /// <param name="b">The second SIMD vector.</param>
        /// <returns>A SIMD type containing the dot product result, with the value broadcast across elements.</returns>
        static SIMDType Dot( SIMDType a, SIMDType b ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Size == 2 )
                {
                    return _mm_dp_ps( a, b, 0b00110011 );
                }
                else if constexpr ( Size == 3 )
                {
                    return _mm_dp_ps( a, b, 0b01110111 );
                }
                else
                {
                    return _mm_dp_ps( a, b, 0xff );
                }
            }
            else
            {
                __m256 rmm1 = _mm256_dp_ps( a, b, 0xff );
                __m256 rmm2 = _mm256_permute2f128_ps( rmm1, rmm1, 1 );
                return _mm256_add_ps( rmm1, rmm2 );
            }
        }

        /// <summary>
        /// Computes the dot product of two SIMD vectors using a mask to select components.
        /// </summary>
        /// <typeparam name="mask">A compile-time constant mask that controls which components are multiplied and where the result is stored. The upper 4 bits specify which elements to multiply, and the lower 4 bits specify which elements of the result to write to.</typeparam>
        /// <param name="a">The first SIMD vector.</param>
        /// <param name="b">The second SIMD vector.</param>
        /// <returns>A SIMD vector containing the dot product result, with placement determined by the mask.</returns>
        template<int mask>
        static SIMDType Dot( SIMDType a, SIMDType b ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_dp_ps( a, b, mask );
            }
            else
            {
                __m256 rmm1 = _mm256_dp_ps( a, b, mask );
                __m256 rmm2 = _mm256_permute2f128_ps( rmm1, rmm1, 1 );
                return _mm256_add_ps( rmm1, rmm2 );
            }
        }

        /// <summary>
        /// Computes the outer product of two 2D vectors represented in SIMD registers.
        /// </summary>
        /// <param name="a">The first 2D vector in SIMD format.</param>
        /// <param name="b">The second 2D vector in SIMD format.</param>
        /// <returns>A SIMD vector containing the four components of the 2x2 outer product: [a1*b1, a1*b2, a2*b1, a2*b2].</returns>
        static SIMDType OuterProduct2x2( SIMDType a, SIMDType b ) noexcept
        {
            // a1*b1  a1*b2 a2*b1  a2*b2
            //
            // a: 1 1 0 0
            // b: 1 0 1 0

            auto rmm1 = Swizzle< Shuffle_v<1, 1, 0, 0>>( a );
            auto rmm2 = Swizzle< Shuffle_v<1, 0, 1, 0>>( b );

            return Mul( rmm1, rmm2 );
        }

        /// <summary>
        /// Computes the outer product of two 3D vectors represented as SIMD types, producing a 3x3 matrix.
        /// </summary>
        /// <param name="a">The first 3D vector in SIMD format (elements at indices 0, 1, 2).</param>
        /// <param name="b">The second 3D vector in SIMD format (elements at indices 0, 1, 2).</param>
        /// <returns>An array of three SIMD vectors representing the rows of the resulting 3x3 outer product matrix.</returns>
        static std::array<SIMDType, 3> OuterProduct3x3( SIMDType a, SIMDType b ) noexcept
        {
            // a1*b1 a1*b2 a1*b3
            // a2*b1 a2*b2 a2*b3
            // a3*b1 a3*b2 a3*b3

            auto an = At<0>( a );
            auto r1 = Mul( an, b );
            an = At<1>( a );
            auto r2 = Mul( an, b );
            an = At<2>( a );
            auto r3 = Mul( an, b );

            return std::array<SIMDType, 3>{ r1, r2, r3 };
        }

        /// <summary>
        /// Computes the 4x4 outer product of two SIMD vectors.
        /// </summary>
        /// <param name="a">The first SIMD vector containing 4 elements.</param>
        /// <param name="b">The second SIMD vector containing 4 elements.</param>
        /// <returns>An array of 4 SIMD vectors representing the 4x4 outer product matrix, where each row is the result of multiplying one element from 'a' by all elements of 'b'.</returns>
        static std::array<SIMDType, 4> OuterProduct4x4( SIMDType a, SIMDType b ) noexcept
        {
            // a1*b1 a1*b2 a1*b3 a1*b4
            // a2*b1 a2*b2 a2*b3 a2*b4
            // a3*b1 a3*b2 a3*b3 a3*b4
            // a4*b1 a4*b2 a4*b4 a4*b4

            auto an = At<0>( a );
            auto r1 = Mul( an, b );
            an = At<1>( a );
            auto r2 = Mul( an, b );
            an = At<2>( a );
            auto r3 = Mul( an, b );
            an = At<3>( a );
            auto r4 = Mul( an, b );

            return std::array<SIMDType, 4>{ r1, r2, r3, r4 };
        }
        

        /// <summary>
        /// Computes the cross product of two SIMD vectors.
        /// </summary>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>
        /// A SIMD vector containing the cross product of vectors a and b. 
        /// For 2D vectors, returns a scalar value replicated across all 
        /// components. For 3D and 4D vectors, returns the standard cross 
        /// product.
        /// </returns>
        static SIMDType Cross( SIMDType a, SIMDType b ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 2 )
                {
                    auto rmm1 = _mm_permute_ps( b, _MM_SHUFFLE( 0, 1, 0, 1 ) );
                    rmm1 = _mm_mul_ps( rmm1, a );
                    auto rmm2 = _mm_permute_ps( rmm1, _MM_SHUFFLE( 1, 1, 1, 1 ) );
                    rmm1 = _mm_sub_ss( rmm1, rmm2 );
                    return _mm_permute_ps( rmm1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
                }
                else if constexpr ( N == 3 )
                {
                    auto rmm1 = _mm_shuffle_ps( a, a, _MM_SHUFFLE( 3, 0, 2, 1 ) );
                    auto rmm2 = _mm_shuffle_ps( b, b, _MM_SHUFFLE( 3, 1, 0, 2 ) );
                    auto rmm3 = _mm_mul_ps( rmm1, b );
                    rmm3 = _mm_shuffle_ps( rmm3, rmm3, _MM_SHUFFLE( 3, 0, 2, 1 ) );
                    rmm1 = _mm_mul_ps( rmm1, rmm2 );
                    return _mm_sub_ps( rmm1, rmm3 );
                }
                else if constexpr ( N == 4 )
                {
                    auto rmm1 = _mm_shuffle_ps( a, a, _MM_SHUFFLE( 3, 0, 2, 1 ) );
                    auto rmm2 = _mm_shuffle_ps( b, b, _MM_SHUFFLE( 3, 1, 0, 2 ) );
                    rmm1 = _mm_mul_ps( rmm1, rmm2 );

                    rmm2 = _mm_shuffle_ps( a, a, _MM_SHUFFLE( 3, 1, 0, 2 ) );
                    auto rmm3 = _mm_shuffle_ps( b, b, _MM_SHUFFLE( 3, 0, 2, 1 ) );
                    rmm2 = _mm_mul_ps( rmm2, rmm3 );

                    return _mm_sub_ps( rmm1, rmm2 );
                }
            }
        }

        /// <summary>
        /// Computes an orthogonal (perpendicular) vector to the input vector.
        /// </summary>
        /// <param name="v">The input SIMD vector for which to compute an orthogonal vector.</param>
        /// <returns>
        /// A SIMD vector that is orthogonal (perpendicular) to the input vector. 
        /// For 2D vectors, returns the perpendicular vector rotated 90 degrees. 
        /// For 3D vectors, computes an orthogonal vector using a robust algorithm. 
        /// For 4D vectors, swaps and flips components to produce an orthogonal result.
        /// </returns>
        static inline SIMDType Orthogonal( const SIMDType v ) noexcept
        {
            using FloatT = Type;

            if constexpr ( Size == 2 )
            {
                constexpr SIMDType flipX = { { static_cast< FloatT >( -1.0 ), static_cast< FloatT >( 1.0 ), static_cast< FloatT >( 1.0 ), static_cast< FloatT >( 1.0 ) } };
                auto result = Shuffle<3, 2, 0, 1>( v, v );
                return Mul( result, flipX );
            }
            else if constexpr ( Size == 3 )
            {
                constexpr SIMDType zero = { { static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. )} };

                auto z = At<2>( v );
                auto yzyy = Swizzle<SelectType::Y, SelectType::Z, SelectType::Y, SelectType::Y>( v );

                auto negativeV = Sub( zero, v );

                auto zIsNegative = Less( z, zero );
                auto yzyyIsNegative = Less( yzyy, zero );

                auto s = Add( yzyy, z );
                auto d = Sub( yzyy, z );

                auto select = SameValue( zIsNegative, yzyyIsNegative );

                auto r0 = Permute<PermuteType::X1, PermuteType::X0, PermuteType::X0, PermuteType::X0>( negativeV, s );
                auto r1 = Permute<PermuteType::X1, PermuteType::X0, PermuteType::X0, PermuteType::X0>( v, d );

                return Select( r1, r0, select );
            }
            else if constexpr ( Size == 4 )
            {
                constexpr SIMDType flipZW = { { { static_cast< FloatT >( 1.0 ), static_cast< FloatT >( 1.0 ), static_cast< FloatT >( -1.0 ), static_cast< FloatT >( -1.0 ) } } };
                auto result = Shuffle<1, 0, 3, 2>( v, v );
                return Simd( Mul( result, flipZW ) );
            }
        }

        /// <summary>
        /// Performs spherical linear interpolation (slerp) between two quaternions.
        /// </summary>
        /// <param name="q1">The first quaternion.</param>
        /// <param name="q2">The second quaternion.</param>
        /// <param name="t">The interpolation parameter, typically in the range [0, 1].</param>
        /// <returns>The interpolated quaternion between q1 and q2.</returns>
        static SIMDType Slerp( SIMDType q1, SIMDType q2, SIMDType t ) noexcept
        {
            using FloatT = Type;
            constexpr SIMDType One = { { static_cast< FloatT >( 1.0 ), static_cast< FloatT >( 1.0 ), static_cast< FloatT >( 1.0 ), static_cast< FloatT >( 1.0 ) } };
            constexpr SIMDType OneX = { { static_cast< FloatT >( 1.0 ), static_cast< FloatT >( 0.0 ), static_cast< FloatT >( 0.0 ), static_cast< FloatT >( 0.0 ) } };
            constexpr SIMDType MinusOne = { { static_cast< FloatT >( -1.0 ), static_cast< FloatT >( -1.0 ), static_cast< FloatT >( -1.0 ), static_cast< FloatT >( -1.0 ) } };
            constexpr SIMDType OneMinusEpsilon = { { static_cast< FloatT >( 1.0 - 0.00001 ), static_cast< FloatT >( 1.0 - 0.00001 ), static_cast< FloatT >( 1.0 - 0.00001 ), static_cast< FloatT >( 1.0 - 0.00001 ) } };
            constexpr SIMDType SignMask2 = { { std::bit_cast< FloatT >( 0x80000000 ), 0, 0, 0 } };
            constexpr SIMDType Zero = { { 0, 0, 0, 0 } };
            constexpr SIMDType MaskXY = { { std::bit_cast< FloatT >( 0xFFFFFFFF ), std::bit_cast< FloatT >( 0xFFFFFFFF ), 0, 0 } };

            auto cosOmega = Dot( q1, q2 );

            auto control = Less( cosOmega, Zero );
            auto sign = Select( One, MinusOne, control );

            cosOmega = Mul( cosOmega, sign );

            control = Less( cosOmega, OneMinusEpsilon );

            auto sinOmega = FNMSub( cosOmega, cosOmega, One );

            sinOmega = Sqrt( sinOmega );

            auto omega = FastATan2( sinOmega, cosOmega );

            auto v01 = And( t, MaskXY );
            v01 = Xor( v01, SignMask2 );
            v01 = Add( OneX, v01 );

            auto s0 = Mul( v01, omega );
            s0 = FastSin( s0 );
            s0 = Div( s0, sinOmega );

            s0 = Select( v01, s0, control );

            auto s1 = At<1>( s0 );
            s0 = At<0>( s0 );

            s1 = Mul( s1, sign );
            auto result = Mul( q1, s0 );
            s1 = Mul( s1, q2 );
            return Add( result, s1 );
        }

        /// <summary>
        /// Transforms a 2D vector by a matrix represented as separate row vectors.
        /// </summary>
        /// <param name="v">The vector to transform.</param>
        /// <param name="mr1">The first row of the transformation matrix.</param>
        /// <param name="mr2">The second row of the transformation matrix.</param>
        /// <param name="mr3">The third row of the transformation matrix (typically the translation component).</param>
        /// <returns>The transformed vector.</returns>
        static SIMDType TransformVector( SIMDType v, SIMDType mr1, SIMDType mr2, SIMDType mr3 )
        {
            if constexpr ( Size == 2 )
            {
                auto result = At<1>( v );
                result = FMAdd( result, mr2, mr3 );
                auto temp = At<0>( v );
                return FMAdd( temp, mr1, result );
            }
        }

        /// <summary>
        /// Transforms a vector by a matrix represented as four row vectors using SIMD operations.
        /// </summary>
        /// <param name="v">The input vector to transform.</param>
        /// <param name="mr1">The first row of the transformation matrix.</param>
        /// <param name="mr2">The second row of the transformation matrix.</param>
        /// <param name="mr3">The third row of the transformation matrix.</param>
        /// <param name="mr4">The fourth row of the transformation matrix.</param>
        /// <returns>The transformed vector resulting from the matrix-vector multiplication.</returns>
        static SIMDType TransformVector( SIMDType v, SIMDType mr1, SIMDType mr2, SIMDType mr3, SIMDType mr4 )
        {
            if constexpr ( Size == 3 )
            {
                // Z
                auto result = At<2>( v );
                result = FMAdd( result, mr3, mr4 );
                // Y
                auto temp = At<1>( v );
                result = FMAdd( temp, mr2, result );
                // X
                temp = At<0>( v );
                return FMAdd( temp, mr1, result );
            }
            else if constexpr ( Size == 4 )
            {
                // W
                auto result = At<3>( v );
                result = Mul( result, mr4 );
                // Z
                auto temp = At<2>( v );
                result = FMAdd( temp, mr3, result );
                // Y
                temp = At<1>( v );
                result = FMAdd( temp, mr2, result );
                // X
                temp = At<0>( v );
                result = FMAdd( temp, mr1, result );
                return result;
            }
        }

        // 2D
        
        /// <summary>
        /// Transforms a 2D point by a 3x3 matrix and performs perspective division.
        /// </summary>
        /// <param name="p">The point to transform, with x-coordinate at index 0 and y-coordinate at index 1.</param>
        /// <param name="mr1">The first row of the transformation matrix.</param>
        /// <param name="mr2">The second row of the transformation matrix.</param>
        /// <param name="mr3">The third row of the transformation matrix.</param>
        /// <returns>The transformed point after perspective division by its w-coordinate (index 2).</returns>
        static SIMDType TransformPoint( SIMDType p, SIMDType mr1, SIMDType mr2, SIMDType mr3 )
        {
            auto y = At<1>( p );
            auto result = FMAdd( y, mr2, mr3 );

            auto x = At<0>( p );
            result = FMAdd( x, mr1, result );

            auto w = At<2>( result );
            return Div( result, w );
        }

        /// <summary>
        /// Transforms a point by a 4x4 matrix (represented as four row vectors) and performs perspective division.
        /// </summary>
        /// <param name="p">The point to transform, represented as a SIMD vector.</param>
        /// <param name="mr1">The first row of the transformation matrix.</param>
        /// <param name="mr2">The second row of the transformation matrix.</param>
        /// <param name="mr3">The third row of the transformation matrix.</param>
        /// <param name="mr4">The fourth row of the transformation matrix.</param>
        /// <returns>The transformed point after perspective division (division by the w component).</returns>
        static SIMDType TransformPoint( SIMDType p, SIMDType mr1, SIMDType mr2, SIMDType mr3, SIMDType mr4 )
        {
            auto z = At<2>( p );
            auto result = FMAdd( z, mr3, mr4 );

            auto y = At<1>( p );
            result = FMAdd( y, mr2, result );

            auto x = At<0>( p );
            result = FMAdd( x, mr1, result );

            auto w = At<3>( result );
            return Div( result, w );
        }

        /// <summary>
        /// Transforms a 2D normal vector by a 2x2 transformation matrix stored in SIMD format.
        /// </summary>
        /// <param name="n">The normal vector to transform, with X component at index 0 and Y component at index 1.</param>
        /// <param name="matrix">A 2x2 transformation matrix stored in SIMD format with elements arranged as [m00, m01, m10, m11].</param>
        /// <returns>The transformed normal vector as a SIMD type, computed as (n.x * matrix[0,1], n.y * matrix[2,3]).</returns>
        static SIMDType TransformNormal( SIMDType n, SIMDType matrix )
        {
            // Y
            auto result = At<1>( n );
            result = Mul( result, Swizzle<3, 2, 3, 2>( matrix ) );
            // X
            auto temp = At<0>( n );
            return FMAdd( temp, Swizzle<1, 0, 1, 0>( matrix ), result );
        }

        /// <summary>
        /// Transforms a 2D normal vector using two matrix rows.
        /// </summary>
        /// <param name="n">The normal vector to transform.</param>
        /// <param name="mr1">The first matrix row used for transformation.</param>
        /// <param name="mr2">The second matrix row used for transformation.</param>
        /// <returns>The transformed normal vector as a SIMD type.</returns>
        static SIMDType TransformNormal( SIMDType n, SIMDType mr1, SIMDType mr2 )
        {
            // Y
            auto result = At<1>( n );
            result = Mul( result, mr2 );
            // X
            auto temp = At<0>( n );
            return FMAdd( temp, mr1, result );
        }

        /// <summary>
        /// Transforms a normal vector by a 3x3 matrix represented as three row vectors.
        /// </summary>
        /// <param name="n">The normal vector to transform.</param>
        /// <param name="mr1">The first row of the transformation matrix.</param>
        /// <param name="mr2">The second row of the transformation matrix.</param>
        /// <param name="mr3">The third row of the transformation matrix.</param>
        /// <returns>The transformed normal vector.</returns>
        static SIMDType TransformNormal( SIMDType n, SIMDType mr1, SIMDType mr2, SIMDType mr3 )
        {
            auto z = At<2>( n );
            auto result = Mul( z, mr3 );
            auto y = At<1>( n );
            result = FMAdd( y, mr2, result );
            auto x = At<0>( n );
            return FMAdd( x, mr1, result );
        }

        /// <summary>
        /// Computes the next representable floating-point value greater than the input for each SIMD lane.
        /// </summary>
        /// <param name="v">The SIMD vector of floating-point values to increment to their next representable value.</param>
        /// <returns>A SIMD vector where each lane contains the smallest floating-point value greater than the corresponding input value. Positive infinity and NaN values are returned unchanged, and negative zero is treated as positive zero.</returns>
        static SIMDType NextUp( SIMDType v )
        {
            /*
            if ( IsInf( v ) && v > 0.f )
                return v;
            if ( v == -0.f )
                v = 0.f;

            uint32_t ui = FloatToBits( v );
            if ( v >= 0 )
                ++ui;
            else
                --ui;
            return BitsToFloat( ui );
            */

            auto OneI = Traits<UInt32, 4>::Fill( 0x00000001 );

            auto v1 = Select( v, _mm_setzero_ps( ), IsZero( v ) );

            auto v1i = _mm_castps_si128( v1 );
            auto v1iPositive = _mm_add_epi32( v1i, OneI );
            v1i = _mm_sub_epi32( v1i, OneI );

            auto r1i = Select( v1i, v1iPositive, GreaterOrEqual( v, _mm_setzero_ps( ) ) );
            auto r1 = _mm_castsi128_ps( r1i );

            r1 = Select( r1, v, IsPositiveInfOrNaN( v ) );
            return r1;


        }

        /// <summary>
        /// Computes the next representable floating-point value in the downward direction for each element in a SIMD vector.
        /// </summary>
        /// <param name="v">The SIMD vector containing floating-point values to decrement to their next lower representable values.</param>
        /// <returns>A SIMD vector where each element is the next representable floating-point value below the corresponding input element. Returns the input value unchanged for negative infinity and NaN.</returns>
        static SIMDType NextDown( SIMDType v )
        {
            /*
            if ( IsInf( v ) && v < 0. )
                return v;
            if ( v == 0.f )
                v = -0.f;
            uint32_t ui = FloatToBits( v );
            if ( v > 0 )
                --ui;
            else
                ++ui;
            return BitsToFloat( ui );

            */

            auto OneI = Traits<UInt32, 4>::Fill( 0x00000001 );

            auto v1 = Select( v, Fill( -0.f ), IsZero( v ) );

            auto v1i = _mm_castps_si128( v1 );
            auto v1iPositive = _mm_sub_epi32( v1i, OneI );
            v1i = _mm_add_epi32( v1i, OneI );

            auto r1i = Select( v1i, v1iPositive, Greater( v, _mm_setzero_ps( ) ) );
            auto r1 = _mm_castsi128_ps( r1i );

            r1 = Select( r1, v, IsNegativeInfOrNaN( v ) );
            return r1;
        }



    };



    template<size_t N>
    struct Traits<double, N> : public Internal::TraitsBase
    {
        using Type = double;
        static constexpr size_t Size = N;
    private:
        static constexpr bool UseShortSIMDType = N <= 2;
        using DataTypeTraits = std::conditional_t<UseShortSIMDType, SIMD::DataTypeTraits<DataType::m128d>, SIMD::DataTypeTraits<DataType::m256d> >;
    public:
        static constexpr DataType Id = DataTypeTraits::Id;
        static constexpr size_t AlignAs = DataTypeTraits::AlignAs;
        using SIMDType = typename DataTypeTraits::Type;
        using SIMDIntegerType = typename DataTypeTraits::IntegerType;
        using ArrayType = std::array<Type, N>;
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t SIMDTypeCapacity = UseShortSIMDType ? 2 : 4;
        static constexpr size_t Capacity = UseShortSIMDType ? 2 : ( ( N + 3 ) & static_cast< Int64 >( -4 ) );
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

        template<size_t Num>
        static SIMDType Fill( Type value ) noexcept requires ( Num > 0 && Num <= Size )
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Num == 1 )
                {
                    return Set( value );
                }
                else
                {
                    return _mm_set1_pd( value );
                }
            }
            else
            {
                if constexpr ( Num == 3 )
                {
                    return Set( value, value, value );
                }
                else
                {
                    return _mm256_set1_pd( value );
                }
            }
        }


        template<size_t Num>
        static SIMDType FillDivisor( Type value ) noexcept requires ( Num > 0 && Num <= SIMDTypeCapacity )
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Num == 1 )
                {
                    return _mm_set_pd( 1.f, value );
                }
                else
                {
                    return _mm_set1_pd( value );
                }
            }
            else
            {
                if constexpr ( Num == 3 )
                {
                    return _mm256_set_pd( 1.f, value, value, value );
                }
                else
                {
                    return _mm256_set1_pd( value );
                }
            }
        }


        static SIMDType Trim( SIMDType v ) noexcept
        {
            if constexpr ( Size == SIMDTypeCapacity )
            {
                return v;
            }
            else
            {
                return And( v, Mask( ) );
            }
        }


        /// <summary>
        /// Returns a mask suitable for extracting
        /// the <c>Size</c> lowest elements from
        /// the <c>SIMDType</c> using the <c>And</c> function.
        /// </summary>
        /// <returns></returns>
        static SIMDType Mask( ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( Size == 1 )
                {
                    return _mm_castsi128_pd( _mm_set_epi64x( 0x0000000000000000, 0xFFFFFFFFFFFFFFFF ) );
                }
                else
                {
                    return _mm_castsi128_pd( _mm_set_epi64x( 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF ) );
                }
            }
            else
            {
                if constexpr ( Size == 3 )
                {
                    return _mm256_castsi256_pd( _mm256_set_epi64x( 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF ) );
                }
                else
                {
                    return _mm256_castsi256_pd( _mm256_set_epi64x( 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF ) );
                }
            }
        }


        static SIMDType Set( Type value1 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_pd( 0.f, value1 );
            }
            else
            {
                return _mm256_set_pd( 0.f, 0.f, 0.f, value1 );
            }
        }

        static SIMDType Set( Type value2, Type value1 ) noexcept requires ( N > 1 )
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_set_pd( value2, value1 );
            }
            else
            {
                return _mm256_set_pd( 0.f, 0.f, value2, value1 );
            }
        }

        static SIMDType Set( Type value3, Type value2, Type value1 ) noexcept requires ( N > 2 )
        {
            return _mm256_set_pd( 0.f, value3, value2, value1 );
        }

        static SIMDType Set( Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 3 )
        {
            return _mm256_set_pd( value4, value3, value2, value1 );
        }


        static SIMDType Load( const Type* src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_load_sd( src );
                }
                else
                {
                    return _mm_load_pd( src );
                }
            }
            else
            {
                if constexpr ( N == 3 )
                {
                    return _mm256_insertf128_pd( _mm256_castpd128_pd256( _mm_load_pd( src ) ), _mm_load_pd( src + 2 ), 1 );
                }
                else
                {
                    return _mm256_load_pd( src );
                }
            }
        }

        template<size_t NA>
            requires ( NA >= N )
        static SIMDType Load( const std::array<Type, NA>& src ) noexcept
        {
            return Load( src.data( ) );
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
        /// Returns the first element of <c>src</<>. The first
        /// element is the element at the lowest position of <c>src</<>.
        /// </summary>
        /// <param name="src">SIMDType to extract the first value from.</param>
        /// <returns>
        /// The first element of <c>src</<>.
        /// </returns>
        static Type First( SIMDType src ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cvtsd_f64( src );
            }
            else
            {
                return _mm256_cvtsd_f64( src );
            }
        }

        /// <summary>
        /// Returns an array containing the lower <c>N</c> elements
        /// of <c>v</c>.
        /// </summary>
        /// <param name="src">
        /// The SIMDType holding the values to return
        /// </param>
        /// <returns>
        /// An array containing the lower <c>N</c> elements
        /// of <c>v</c>.
        /// </returns>
        static ArrayType ToArray( SIMDType src ) noexcept
        {
            if constexpr ( N == SIMDTypeCapacity )  // N == 2 || N == 4
            {
                alignas( AlignAs ) ArrayType result;
                Store( result.data( ), src );
                return result;
            }
            else if constexpr ( N == 1 )
            {
                alignas( AlignAs ) ArrayType result;
                _mm_store_sd( result.data( ), src );
                return result;
            }
            else // N == 3
            {
                alignas( AlignAs ) std::array<Type, SIMDTypeCapacity> tmp;
                Store( tmp.data( ), src );
                return[ &tmp ] <std::size_t... I>
                    ( std::index_sequence<I...> )
                {
                    ArrayType result;
                    ( ( result[ I ] = tmp[ I ] ), ... );
                    return result;
                }( std::make_index_sequence<N>( ) );
            }
        }

        /// <summary>
        /// Returns a SIMDType with all elements set to the
        /// value of <c>v[index]</c>.
        /// </summary>
        /// <typeparam name="index">
        /// The index of the value, in <c>v</c> to assign to ell the elements
        /// of the result, 
        /// </typeparam>
        /// <param name="v">
        /// The SIMDType type containing the the source value.
        /// </param>
        /// <returns>
        /// A SIMDType with all elements set to the
        /// value of <c>v[index]</c>.
        /// </returns>
        template<size_t index>
            requires ( index < Size )
        static SIMDType At( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( index == 0 )
                {
                    return _mm_permute_pd( v, _MM_SHUFFLE2( 0, 0 ) );
                }
                else
                {
                    return _mm_permute_pd( v, _MM_SHUFFLE2( 1, 1 ) );
                }

            }
            else
            {
                if constexpr ( index == 0 )
                {
                    return _mm256_permute4x64_pd( v, _MM_SHUFFLE( 0, 0, 0, 0 ) );
                }
                else if constexpr ( index == 1 )
                {
                    return _mm256_permute4x64_pd( v, _MM_SHUFFLE( 1, 1, 1, 1 ) );
                }
                else if constexpr ( index == 2 )
                {
                    return _mm256_permute4x64_pd( v, _MM_SHUFFLE( 2, 2, 2, 2 ) );
                }
                else
                {
                    return _mm256_permute4x64_pd( v, _MM_SHUFFLE( 3, 3, 3, 3 ) );
                }
            }
        }

        /// <summary>
        /// Returns the value of <c>v[index]</c>.
        /// </summary>
        /// <typeparam name="index">
        /// The index of the value, in <c>v</c>.
        /// </typeparam>
        /// <param name="v">
        /// The SIMDType type containing the the source value.
        /// </param>
        /// <returns>
        /// The value of <c>v[index]</c>.
        /// </returns>
        template<size_t index>
            requires ( index < Size )
        static Type Extract( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( index == 0 )
                {
                    return _mm_cvtsd_f64( v );
                }
                else
                {
                    return _mm_cvtsd_f64( _mm_permute_pd( v, _MM_SHUFFLE2( 1, 1 ) ) );
                }

            }
            else
            {
                if constexpr ( index == 0 )
                {
                    return _mm256_cvtsd_f64( v );
                }
                else if constexpr ( index == 1 )
                {
                    return _mm256_cvtsd_f64( _mm256_permute4x64_pd( v, _MM_SHUFFLE( 1, 1, 1, 1 ) ) );
                }
                else if constexpr ( index == 2 )
                {
                    return _mm256_cvtsd_f64( _mm256_permute4x64_pd( v, _MM_SHUFFLE( 2, 2, 2, 2 ) ) );
                }
                else
                {
                    return _mm256_cvtsd_f64( _mm256_permute4x64_pd( v, _MM_SHUFFLE( 3, 3, 3, 3 ) ) );
                }
            }
        }



        /// <summary>
        /// Returns true if at least one of the values in <c>v</c> is NaN,
        /// otherwise false.
        /// </summary>
        /// <param name="v">
        /// A SIMDType holding the values to test.
        /// </param>
        /// <returns>
        /// Returns true if at least one of the values in <c>v</c> is NaN,
        /// otherwise false.
        /// </returns>
        static bool HasNaN( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                auto rmm1 = _mm_cmpneq_pd( v, v );
                if constexpr ( N == 1 )
                {
                    return ( _mm_movemask_pd( rmm1 ) & 1 ) != 0;
                }
                else
                {
                    return ( _mm_movemask_pd( rmm1 ) & 3 ) != 0;
                }
            }
            else
            {
                __m128d low = _mm256_castpd256_pd128( v );
                auto rmm1 = _mm_cmpneq_pd( low, low );
                if ( ( _mm_movemask_pd( rmm1 ) & 3 ) != 0 )
                {
                    return true;
                }
                else
                {
                    __m128d high = _mm256_extractf128_pd( v, 1 );
                    auto rmm2 = _mm_cmpneq_pd( high, high );
                    if constexpr ( N == 3 )
                    {
                        return ( _mm_movemask_pd( rmm2 ) & 1 ) != 0;
                    }
                    else
                    {
                        return ( _mm_movemask_pd( rmm2 ) & 3 ) != 0;
                    }
                }
            }
        }


        /// <summary>
        /// Compute the bitwise AND of packed double-precision (64-bit) 
        /// floating-point elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        static SIMDType And( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_and_pd( lhs, rhs );
            }
            else
            {
                return _mm256_and_pd( lhs, rhs );
            }
        }

        /// <summary>
        /// Compute the bitwise NOT of packed double-precision (64-bit) floating-point 
        /// elements in <c>lhs</c> and then AND with <c>rhs</c>, returning the results.
        /// </summary>
        static SIMDType AndNot( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_andnot_pd( lhs, rhs );
            }
            else
            {
                return _mm256_andnot_pd( lhs, rhs );
            }
        }

        /// <summary>
        /// Compute the bitwise OR of packed double-precision (64-bit) 
        /// floating-point elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        static SIMDType Or( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_or_pd( lhs, rhs );
            }
            else
            {
                return _mm256_or_pd( lhs, rhs );
            }
        }

        /// <summary>
        /// Compute the bitwise XOR of packed double-precision (64-bit) 
        /// floating-point elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
        static SIMDType Xor( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_xor_pd( lhs, rhs );
            }
            else
            {
                return _mm256_xor_pd( lhs, rhs );
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


        static SIMDType HSum( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return v;
                }
                else
                {
                    return _mm_add_pd( v, _mm_permute_pd( v, 1 ) );
                }
            }
            else
            {
                auto low = _mm256_castpd256_pd128( v );
                auto high = _mm256_extractf128_pd( v, 1 );
                if constexpr ( N == 3 )
                {
                    auto r1 = _mm_permute_pd( high, 0b00'00 );
                    auto r2 = _mm_add_pd( _mm_add_pd( low, _mm_permute_pd( low, 1 ) ), r1 );
                    return _mm256_broadcastsd_pd( r2 );
                }
                else
                {
                    auto r2 = _mm_add_pd( _mm_add_pd( low, _mm_permute_pd( low, 1 ) ), _mm_add_pd( high, _mm_permute_pd( high, 1 ) ) );
                    return _mm256_broadcastsd_pd( r2 );
                }
                /*
                auto rmm1 = _mm256_add_pd( v, _mm256_permute_pd( v, 0b0101 ) );
                auto low = _mm256_castpd256_pd128( rmm1 );
                auto high = _mm256_extractf128_pd( rmm1, 1 );
                return _mm256_broadcastsd_pd( _mm_add_pd( low, high ) );
                */
            }
        }


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

        static SIMDType Mul( Type lhs, SIMDType rhs ) noexcept
        {
            return Mul( Fill( lhs ), rhs );
        }

        static SIMDType Mul( SIMDType lhs, Type rhs ) noexcept
        {
            return Mul( lhs, Fill( rhs ) );
        }

        inline static SIMDType QuaternionMultiply( SIMDType q1, SIMDType q2 ) noexcept
            requires ( Size == 4 )
        {
            constexpr Type One = 1.;
            constexpr Type MinusOne = -1.;

            constexpr SIMDType controlWZYX = { { One, MinusOne, One, MinusOne } };
            constexpr SIMDType controlZWXY = { { One, One, MinusOne, MinusOne } };
            constexpr SIMDType controlYXWZ = { { MinusOne, One, One, MinusOne } };

            auto q2X = At<0>( q2 );
            auto q2Y = At<1>( q2 );
            auto q2Z = At<2>( q2 );
            auto result = At<3>( q2 );

            result = Mul( result, q1 );

            auto q1Swizzle = Swizzle<0, 1, 2, 3>( q1 );

            q2X = Mul( q2X, q1Swizzle );
            q1Swizzle = Swizzle<2, 3, 0, 1>( q1Swizzle );

            result = FMAdd( q2X, controlWZYX, result );

            q2Y = Mul( q2Y, q1Swizzle );
            q1Swizzle = Swizzle<0, 1, 2, 3>( q1Swizzle );

            q2Y = Mul( q2Y, controlZWXY );

            q2Z = Mul( q2Z, q1Swizzle );

            q2Y = FMAdd( q2Z, controlYXWZ, q2Y );
            result = Add( result, q2Y );
            return result;
        }

        static SIMDType HProd( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return v;
                }
                else
                {
                    return _mm_mul_pd( v, _mm_permute_pd( v, 1 ) );
                }
            }
            else
            {
                auto low = _mm256_castpd256_pd128( v );
                auto high = _mm256_extractf128_pd( v, 1 );
                if constexpr ( N == 3 )
                {
                    auto r1 = _mm_permute_pd( high, 0b00'00 );
                    auto r2 = _mm_mul_pd( _mm_mul_pd( low, _mm_permute_pd( low, 1 ) ), r1 );
                    return _mm256_broadcastsd_pd( r2 );
                }
                else
                {
                    auto r2 = _mm_mul_pd( _mm_mul_pd( low, _mm_permute_pd( low, 1 ) ), _mm_mul_pd( high, _mm_permute_pd( high, 1 ) ) );
                    return _mm256_broadcastsd_pd( r2 );
                }
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

        static SIMDType Div( SIMDType lhs, Type rhs ) noexcept
        {
            return Div( lhs, Fill( rhs ) );
        }

        template<int shuffleMask>
        static SIMDType Permute( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_permute_pd( v, shuffleMask );
            }
            else
            {
                return _mm256_permute_pd( v, shuffleMask );
            }
        }

        template< UInt32 selection2, UInt32 selection1>
        static SIMDType Swizzle( SIMDType v ) noexcept requires( UseShortSIMDType )
        {
            return _mm_permute_pd( v, _MM_SHUFFLE2( selection2, selection1 ) );
        }

        template<UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1>
        static SIMDType Swizzle( SIMDType v ) noexcept requires( UseShortSIMDType == false )
        {
            return _mm256_permute4x64_pd( v, _MM_SHUFFLE( selection4, selection3, selection2, selection1 ) );
        }


        static SIMDType Abs( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_max_pd( _mm_sub_pd( _mm_setzero_pd( ), v ), v );
            }
            else
            {
                return _mm256_max_pd( _mm256_sub_pd( _mm256_setzero_pd( ), v ), v );
            }
        }

        static SIMDType Min( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_min_pd( lhs, rhs );
            }
            else
            {
                return _mm256_min_pd( lhs, rhs );
            }
        }

        static SIMDType Max( SIMDType lhs, SIMDType rhs ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_max_pd( lhs, rhs );
            }
            else
            {
                return _mm256_max_pd( lhs, rhs );
            }
        }

        static Type HorizontalMin( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_cvtsd_f64( v );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_cvtsd_f64( _mm_min_pd( v, _mm_permute_pd( v, _MM_SHUFFLE2( 0, 1 ) ) ) );
                }
            }
            else
            {
                __m128d low = _mm256_castpd256_pd128( v );
                __m128d high = _mm256_extractf128_pd( v, 1 );
                auto rmm1 = _mm_min_pd( low, _mm_permute_pd( low, _MM_SHUFFLE2( 0, 1 ) ) );
                if constexpr ( N == 3 )
                {
                    auto rmm2 = _mm_min_pd( high, rmm1 );
                    return _mm_cvtsd_f64( rmm2 );
                }
                else // N == 4
                {
                    auto rmm2 = _mm_min_pd( _mm_min_pd( high, _mm_permute_pd( high, 1 ) ), rmm1 );
                    return _mm_cvtsd_f64( rmm2 );
                }

            }
        }

        static Type HorizontalMax( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return _mm_cvtsd_f64( v );
                }
                else if constexpr ( N == 2 )
                {
                    return _mm_cvtsd_f64( _mm_max_pd( v, _mm_permute_pd( v, _MM_SHUFFLE2( 0, 1 ) ) ) );
                }
            }
            else
            {
                __m128d low = _mm256_castpd256_pd128( v );
                __m128d high = _mm256_extractf128_pd( v, 1 );
                auto rmm1 = _mm_max_pd( low, _mm_permute_pd( low, _MM_SHUFFLE2( 0, 1 ) ) );
                if constexpr ( N == 3 )
                {
                    auto rmm2 = _mm_max_pd( high, rmm1 );
                    return _mm_cvtsd_f64( rmm2 );
                }
                else // N == 4
                {
                    auto rmm2 = _mm_max_pd( _mm_max_pd( high, _mm_permute_pd( high, 1 ) ), rmm1 );
                    return _mm_cvtsd_f64( rmm2 );
                }

            }
        }

        static SIMDType Round( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_round_pd( v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC );
            }
            else
            {
                return _mm256_round_pd( v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC );
            }
        }

        static SIMDType Truncate( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_round_pd( v, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC );
            }
            else
            {
                return _mm256_round_pd( v, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC );
            }
        }

        static SIMDType Floor( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_round_pd( v, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC );
            }
            else
            {
                return _mm256_round_pd( v, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC );
            }
        }

        static SIMDType Ceil( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_round_pd( v, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC );
            }
            else
            {
                return _mm256_round_pd( v, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC );
            }
        }

        static SIMDType Clamp( SIMDType v, SIMDType lowerBounds, SIMDType upperBounds ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_min_pd( upperBounds, _mm_max_pd( lowerBounds, v ) );
            }
            else
            {
                return _mm256_min_pd( upperBounds, _mm256_max_pd( lowerBounds, v ) );
            }
        }

        static SIMDType Lerp( SIMDType v1, SIMDType v2, Type t ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_pd( Fill<Size>( t ), v2, _mm_mul_pd( Fill<Size>( 1.f - t ), v1 ) );

                //return _mm_fmadd_pd( v2, v1, _mm_mul_pd( _mm_sub_ps( _mm_set_pd1( 1.f ), v2 ), _mm_set_pd1( t ) ) );
            }
            else
            {
                return _mm256_fmadd_pd( Fill<Size>( t ), v2, _mm256_mul_pd( Fill<Size>( 1.f - t ), v1 ) );

                //return _mm256_fmadd_pd( v2, v1, _mm256_mul_pd( _mm256_sub_pd( _mm256_set1_pd( 1.f ), v2 ), _mm256_set1_pd( t ) ) );
            }
        }

        static SIMDType Lerp( SIMDType v1, SIMDType v2, SIMDType t ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmadd_pd( t, v2, _mm_mul_pd( _mm_sub_pd( Fill<Size>( 1.f ), t ), v1 ) );
            }
            else
            {
                return _mm256_fmadd_pd( t, v2, _mm256_mul_pd( _mm256_sub_pd( Fill<Size>( 1.f ), t ), v1 ) );
            }
        }


        static SIMDType Saturate( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_min_pd( _mm_max_pd( v, { { { 0.0, 0.0 } } } ), { { { 1.0, 1.0 } } } );
            }
            else
            {
                return _mm256_min_pd( _mm256_max_pd( v, { { { 0.0, 0.0, 0.0, 0.0 } } } ), { { { 1.0, 1.0, 1.0, 1.0 } } } );
            }
        }

        static SIMDType Negate( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sub_pd( _mm_setzero_pd( ), v );
            }
            else
            {
                return _mm256_sub_pd( _mm256_setzero_pd( ), v );
            }
        }



        static SIMDType Sin( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sin_pd( v );
            }
            else
            {
                return _mm256_sin_pd( v );
            }
        }

        static SIMDType Cos( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cos_pd( v );
            }
            else
            {
                return _mm256_cos_pd( v );
            }
        }

        static SIMDType SinCos( SIMDType v, SIMDType* cosines ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sincos_pd( cosines, v );
            }
            else
            {
                return _mm256_sincos_pd( cosines, v );
            }
        }

        static SIMDType Tan( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_tan_pd( v );
            }
            else
            {
                return _mm256_tan_pd( v );
            }
        }

        static SIMDType ASin( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_asin_pd( v );
            }
            else
            {
                return _mm256_asin_pd( v );
            }
        }

        static SIMDType ACos( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_acos_pd( v );
            }
            else
            {
                return _mm256_acos_pd( v );
            }
        }

        static SIMDType ATan( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_atan_pd( v );
            }
            else
            {
                return _mm256_atan_pd( v );
            }
        }

        static SIMDType ATan2( SIMDType x, SIMDType y ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_atan2_pd( x, y );
            }
            else
            {
                return _mm256_atan2_pd( x, y );
            }
        }

        static SIMDType SinH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_sinh_pd( v );
            }
            else
            {
                return _mm256_sinh_pd( v );
            }
        }

        static SIMDType CosH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cosh_pd( v );
            }
            else
            {
                return _mm256_cosh_pd( v );
            }
        }

        static SIMDType TanH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_tanh_pd( v );
            }
            else
            {
                return _mm256_tanh_pd( v );
            }
        }

        static SIMDType ASinH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_asinh_pd( v );
            }
            else
            {
                return _mm256_asinh_pd( v );
            }
        }

        static SIMDType ACosH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_acosh_pd( v );
            }
            else
            {
                return _mm256_acosh_pd( v );
            }
        }

        static SIMDType ATanH( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_atanh_pd( v );
            }
            else
            {
                return _mm256_atanh_pd( v );
            }
        }

        static SIMDType Log( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_log_pd( v );
            }
            else
            {
                return _mm256_log_pd( v );
            }
        }

        static SIMDType Log1P( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_log1p_pd( v );
            }
            else
            {
                return _mm256_log1p_pd( v );
            }
        }

        static SIMDType Log10( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_log10_pd( v );
            }
            else
            {
                return _mm256_log10_pd( v );
            }
        }

        static SIMDType Log2( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_log2_pd( v );
            }
            else
            {
                return _mm256_log2_pd( v );
            }
        }

        static SIMDType Exp( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_exp_pd( v );
            }
            else
            {
                return _mm256_exp_pd( v );
            }
        }

        static SIMDType Exp10( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_exp10_pd( v );
            }
            else
            {
                return _mm256_exp10_pd( v );
            }
        }

        static SIMDType Exp2( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_exp2_pd( v );
            }
            else
            {
                return _mm256_exp2_pd( v );
            }
        }

        static SIMDType ExpM1( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_expm1_pd( v );
            }
            else
            {
                return _mm256_expm1_pd( v );
            }
        }

        static SIMDType Pow( SIMDType base, SIMDType exponent ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_pow_pd( base, exponent );
            }
            else
            {
                return _mm256_pow_pd( base, exponent );
            }
        }

        static SIMDType FMod( SIMDType x, SIMDType y ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_fmod_pd( x, y );
            }
            else
            {
                return _mm256_fmod_pd( x, y );
            }
        }

        static SIMDType Hypot( SIMDType x, SIMDType y ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_hypot_pd( x, y );
            }
            else
            {
                return _mm256_hypot_pd( x, y );
            }
        }

        /// <summary>
        /// Determines whether the elements of v1 are less than 
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is less than the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType Less( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmplt_pd( v1, v2 );
            }
            else
            {
                // LT_OQ => 0x11
                return _mm256_cmp_pd( v1, v2, _CMP_LT_OQ );
            }
        }

        /// <summary>
        /// Determines whether the elements of v1 are less than or equal to
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is less than or equal to the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType LessOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmple_pd( v1, v2 );
            }
            else
            {
                // _CMP_LE_OQ => 18
                return _mm256_cmp_pd( v1, v2, _CMP_LE_OQ );
            }
        }

        /// <summary>
        /// Determines whether the elements of v1 are equal to
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is equal to the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType Equal( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_pd( v1, v2 );
            }
            else
            {
                return _mm256_cmp_pd( v1, v2, _CMP_EQ_OQ );
            }
        }


        /// <summary>
        /// Determines whether the elements of v1 are greater than
        /// or equal to the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is greater than or equal to the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType GreaterOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpge_pd( v1, v2 );
            }
            else
            {
                return _mm256_cmp_pd( v1, v2, _CMP_GE_OQ );
            }
        }

        /// <summary>
        /// Determines whether the elements of v1 are greater than
        /// the corresponding elements of v2.
        /// </summary>
        /// <param name="v1">
        /// The first source of values for the comparison.
        /// </param>
        /// <param name="v2">
        /// The second source of values for the comparison.
        /// </param>
        /// <returns>
        /// If an element of v1 is greater than the corresponding element of v2,
        /// the corresponding element in the result will be set to 0xFFFFFFFF,
        /// otherwise the corresponding element in the result will be set to 0.
        /// </returns>
        static SIMDType Greater( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpgt_pd( v1, v2 );
            }
            else
            {
                return _mm256_cmp_pd( v1, v2, _CMP_GT_OQ );
            }
        }



        static bool AllEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    auto rmm1 = _mm_cmpeq_pd( v1, v2 );
                    return ( _mm_movemask_pd( rmm1 ) & 1 ) == 1;
                }
                else // N == 2
                {
                    auto rmm1 = _mm_cmpeq_pd( v1, v2 );
                    return ( _mm_movemask_pd( rmm1 ) & 3 ) == 3;
                }
            }
            else
            {
                if constexpr ( N == 3 )
                {
                    auto rmm1 = _mm256_cmpeq_epi64( _mm256_castpd_si256( v1 ), _mm256_castpd_si256( v2 ) );
                    return ( _mm256_movemask_epi8( rmm1 ) & 7 ) == 7;
                }
                else // N == 4
                {
                    auto rmm1 = _mm256_cmpeq_epi64( _mm256_castpd_si256( v1 ), _mm256_castpd_si256( v2 ) );
                    return ( _mm256_movemask_epi8( rmm1 ) & 15 ) == 15;
                }
            }
        }


        /// <summary>
        /// Performs binary, element wise comparision of v1 and v2. 
        /// </summary>
        /// <param name="v1">v1</param>
        /// <param name="v2">v2</param>
        /// <returns>
        /// The results of the element wise comparision. An element is
        /// set to 0xFFFFFFFFFFFFFFFF if the corresponding elements in v1 and v2
        /// have the same binary value, otherwise the element is 0.
        /// </returns>
        static SIMDIntegerType SameValue( SIMDType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_epi64( _mm_castpd_si128( v1 ), _mm_castpd_si128( v2 ) );
            }
            else
            {
                return _mm256_cmpeq_epi64( _mm256_castpd_si256( v1 ), _mm256_castpd_si256( v2 ) );
            }
        }

        /// <summary>
        /// Performs binary, element wise comparision of v1 and v2. 
        /// </summary>
        /// <param name="v1">v1</param>
        /// <param name="v2">v2</param>
        /// <returns>
        /// The results of the element wise comparision. An element is
        /// set to 0xFFFFFFFFFFFFFFFF if the corresponding elements in v1 and v2
        /// have the same binary value, otherwise the element is 0.
        /// </returns>
        static SIMDIntegerType SameValue( SIMDType v1, SIMDIntegerType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_epi64( _mm_castpd_si128( v1 ), v2 );
            }
            else
            {
                return _mm256_cmpeq_epi64( _mm256_castpd_si256( v1 ), v2 );
            }
        }

        /// <summary>
        /// Performs binary, element wise comparision of v1 and v2. 
        /// </summary>
        /// <param name="v1">v1</param>
        /// <param name="v2">v2</param>
        /// <returns>
        /// The results of the element wise comparision. An element is
        /// set to 0xFFFFFFFFFFFFFFFF if the corresponding elements in v1 and v2
        /// have the same binary value, otherwise the element is 0.
        /// </returns>
        static SIMDIntegerType SameValue( SIMDIntegerType v1, SIMDType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_epi64( v1, _mm_castpd_si128( v2 ) );
            }
            else
            {
                return _mm256_cmpeq_epi64( v1, _mm256_castpd_si256( v2 ) );
            }
        }

        /// <summary>
        /// Performs binary, element wise comparision of v1 and v2. 
        /// </summary>
        /// <param name="v1">v1</param>
        /// <param name="v2">v2</param>
        /// <returns>
        /// The results of the element wise comparision. An element is
        /// set to 0xFFFFFFFFFFFFFFFF if the corresponding elements in v1 and v2
        /// have the same binary value, otherwise the element is 0.
        /// </returns>
        static SIMDIntegerType SameValue( SIMDIntegerType v1, SIMDIntegerType v2 ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cmpeq_epi64( v1, v2 );
            }
            else
            {
                return _mm256_cmpeq_epi64( v1, v2 );
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
        /// Cube Root of float64 vector
        /// </summary>
        /// <param name="v"></param>
        static SIMDType Cbrt( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                return _mm_cbrt_pd( v );
            }
            else
            {
                return _mm256_cbrt_pd( v );
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

    template<typename T>
    constexpr bool IsSIMDType = Traits<T, 4>::value;
}


#endif

