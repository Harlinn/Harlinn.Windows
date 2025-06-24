#pragma once
#ifndef HARLINN_MATH_SIMD_H_
#define HARLINN_MATH_SIMD_H_

/*
   Copyright 2024-2025 Espen Harlinn

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


    template<size_t N>
    struct Traits<char, N> : public Traits8Bit<char, N>
    {
    };

    template<size_t N>
    struct Traits<SByte, N> : public Traits8Bit<SByte, N>
    {
    };

    template<size_t N>
    struct Traits<Byte, N> : public Traits8Bit<Byte, N>
    {
    };


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

    template<size_t N>
    struct Traits<Int16, N> : public Traits16Bit<Int16, N>
    {
    };

    template<size_t N>
    struct Traits<UInt16, N> : public Traits16Bit<UInt16, N>
    {
    };


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
        static constexpr size_t SIMDTypeSize = DataTypeTraits::Size;
        static constexpr size_t SIMDTypeCapacity = UseShortSIMDType ? 4 : 8;
        static constexpr size_t Capacity = UseShortSIMDType ? 4 : ( ( N + 7 ) & static_cast< Int64 >( -8 ) );
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
                return _mm_set1_epi32( std::bit_cast< int >( value ) );
            }
            else
            {
                return _mm256_set1_epi32( std::bit_cast< int >( value ) );
            }
        }

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
                    return _mm_add_epi32( _mm_shuffle_epi32( v, 0b01'00'01'00 ), _mm_permute_epi32( v, v, 0b00'01'00'01 ) );
                }
                else if constexpr ( N == 3 )
                {
                    return _mm_add_epi32( _mm_shuffle_epi32( v, v, _MM_SHUFFLE( 0, 2, 1, 0 ) ), _mm_add_epi32( _mm_shuffle_epi32( v, v, _MM_SHUFFLE( 1, 1, 0, 2 ) ), _mm_shuffle_epi32( v, v, _MM_SHUFFLE( 2, 0, 2, 1 ) ) ) );
                }
                else
                {
                    return _mm_add_epi32( _mm_add_epi32( v, _mm_shuffle_epi32( v, v, 0b10'01'00'11 ) ),
                        _mm_add_epi32( _mm_shuffle_epi32( v, v, 0b01'00'11'10 ), _mm_shuffle_epi32( v, v, 0b00'11'10'01 ) ) );
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

        static SIMDType Mul( Type lhs, SIMDType rhs ) noexcept
        {
            return Mul( Fill( lhs ), rhs );
        }

        static SIMDType Mul( SIMDType lhs, Type rhs ) noexcept
        {
            return Mul( lhs, Fill( rhs ) );
        }

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

    template<size_t N>
    struct Traits<Int32, N> : public Traits32Bit<Int32, N>
    {
    };

    template<size_t N>
    struct Traits<UInt32, N> : public Traits32Bit<UInt32, N>
    {
    };


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
                return _mm_set1_epi64x( std::bit_cast< long long >( value ) );
            }
            else
            {
                return _mm256_set1_epi64x( std::bit_cast< long long >( value ) );
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
    struct Traits<Int64, N> : public Traits64Bit<Int64, N>
    {
    };

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
        /// Returns a mask suitable for extracting
        /// the <c>Size</c> lowest elements from
        /// the <c>SIMDType</c> using the <c>And</c> function.
        /// </summary>
        /// <returns></returns>
        static SIMDType Mask( ) noexcept
        {
            return Mask( 0xFFFFFFFF );
        }

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

        static SIMDType Set( Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 4 )
        {
            return _mm256_set_ps( 0.f, 0.f, 0.f, value5, value4, value3, value2, value1 );
        }

        static SIMDType Set( Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 5 )
        {
            return _mm256_set_ps( 0.f, 0.f, value6, value5, value4, value3, value2, value1 );
        }

        static SIMDType Set( Type value7, Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 6 )
        {
            return _mm256_set_ps( 0.f, value7, value6, value5, value4, value3, value2, value1 );
        }

        static SIMDType Set( Type value8, Type value7, Type value6, Type value5, Type value4, Type value3, Type value2, Type value1 ) noexcept requires ( N > 7 )
        {
            return _mm256_set_ps( value8, value7, value6, value5, value4, value3, value2, value1 );
        }

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
                    __m128 low = _mm_castpd_ps( _mm_load_sd( reinterpret_cast< const double* >( src ) ) );
                    __m128 high = _mm_load_ss( reinterpret_cast< const float* >( src + 2 ) );
                    return _mm_insert_ps( low, high, 0x20 );
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
                return _mm_cvtss_f32( src );
            }
            else
            {
                return _mm256_cvtss_f32( src );
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
        /// Compute the bitwise AND of packed single-precision (32-bit) 
        /// floating-point elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
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
        /// Compute the bitwise NOT of packed single-precision (32-bit) floating-point 
        /// elements in <c>lhs</c> and then AND with <c>rhs</c>, returning the results.
        /// </summary>
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
        /// Compute the bitwise OR of packed single-precision (32-bit) 
        /// floating-point elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
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
        /// Compute the bitwise XOR of packed single-precision (32-bit) 
        /// floating-point elements in <c>lhs</c> and <c>rhs</c>, returning the results.
        /// </summary>
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
                if constexpr ( N == 1 )
                {
                    return v;
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


        static Type Avg( SIMDType v ) noexcept
        {
            return First( HSum( v ) ) / static_cast< Type >( N );
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

        static SIMDType HProd( SIMDType v ) noexcept
        {
            if constexpr ( UseShortSIMDType )
            {
                if constexpr ( N == 1 )
                {
                    return v;
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
        /// Divides one float32 vector by another.
        /// </summary>
        /// <param name="lhs">float32 vector used for the left-hand side of the operation</param>
        /// <param name="rhs">float32 vector used for the right-hand side of the operation</param>
        /// <remarks>
        /// Divides the packed single-precision floating-point elements (float32 elements) 
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

        static SIMDType Div( SIMDType lhs, Type rhs ) noexcept
        {
            return Div( lhs, Fill( rhs ) );
        }

        template<typename ... Args>
        static SIMDType Permute( Args&& ... args )
        {
            static_assert( false, "No matching overload" );
        }

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
        

        template<UInt32 shuffle>
        static SIMDType Swizzle( SIMDType v ) noexcept requires( UseShortSIMDType )
        {
            return _mm_permute_ps( v, shuffle );
        }

        
        static SIMDType Swizzle( SIMDType v, UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1 ) noexcept
            requires( UseShortSIMDType )
        {
            alignas( AlignAs ) std::array<UInt32, 4> selection{ selection1, selection2, selection3, selection4 };
            __m128i selectionControl = _mm_load_si128( reinterpret_cast< const __m128i* >( selection[ 0 ].data( ) ) );
            return _mm_permutevar_ps( v, selectionControl );
        }

        static SIMDType Swizzle( SIMDType v, UInt32 selection8, UInt32 selection7, UInt32 selection6, UInt32 selection5, UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1 ) noexcept
            requires( UseShortSIMDType == false )
        {
            alignas( AlignAs ) std::array<UInt32, 8> selection{ selection1, selection2, selection3, selection4, selection5, selection6, selection7, selection8 };
            __m128i selectionControl = _mm256_load_si256( reinterpret_cast< const __m256i* >( selection[ 0 ].data( ) ) );
            return _mm256_permutevar8x32_ps( v, selectionControl );
        }
        


        template<typename ... Args>
        static SIMDType Shuffle( Args&& ... args )
        {
            static_assert( false, "No matching overload" );
        }

        template<UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1>
        static SIMDType Shuffle( SIMDType v1, SIMDType v2 ) noexcept requires( UseShortSIMDType )
        {
            return _mm_shuffle_ps( v1, v2, _MM_SHUFFLE( selection4, selection3, selection2, selection1 ) );
        }

        template<UInt32 selection4, UInt32 selection3, UInt32 selection2, UInt32 selection1>
        static SIMDType Shuffle( SIMDType v1 ) noexcept requires( UseShortSIMDType )
        {
            return _mm_shuffle_ps( v1, v1, _MM_SHUFFLE( selection4, selection3, selection2, selection1 ) );
        }





        /// <summary>
        /// Set each bit of the result based on the most significant bit of 
        /// the corresponding packed single-precision (32-bit) floating-point 
        /// element in v.
        /// </summary>
        /// <param name="v">Elements to test</param>
        /// <returns>
        /// Bit mask based on the most significant bit of 
        /// the corresponding packed single-precision (32-bit) floating-point 
        /// element in v.
        /// </returns>
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
        /// Set each bit of the result based on the most significant bit of 
        /// the corresponding packed single-precision (32-bit) floating-point 
        /// element in v.
        /// </summary>
        /// <param name="v">Elements to test</param>
        /// <returns>
        /// Bit mask based on the most significant bit of 
        /// the corresponding packed single-precision (32-bit) floating-point 
        /// element in v.
        /// </returns>
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
        // Handles permutes that cannot be performed using a single _mm_shuffle_ps.
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

        // Handles permutes that only read from the first vector.
        template<UInt32 shuffle>
        struct PermuteImpl<shuffle, false, false, false, false>
        {
            static SIMDType Permute( SIMDType v1, SIMDType ) noexcept
            {
                return _mm_shuffle_ps( v1, v1, shuffle );
            }
        };

        // Handles permutes that only read from the second vector.
        template<UInt32 shuffle>
        struct PermuteImpl<shuffle, true, true, true, true>
        {
            static SIMDType Permute( SIMDType, SIMDType  v2 ) noexcept
            {
                return _mm_shuffle_ps( v2, v2, shuffle );
            }
        };

        // Handles permutes that read XY from the first vector, ZW from the second.
        template<UInt32 shuffle>
        struct PermuteImpl<shuffle, false, false, true, true>
        {
            static SIMDType Permute( SIMDType v1, SIMDType v2 ) noexcept
            {
                return _mm_shuffle_ps( v1, v2, shuffle );
            }
        };

        // Handles permutes that read XY from the second vector, ZW from the first.
        template<UInt32 shuffle>
        struct PermuteImpl<shuffle, true, true, false, false>
        {
            static SIMDType Permute( SIMDType v1, SIMDType v2 ) noexcept
            {
                return _mm_shuffle_ps( v2, v1, shuffle );
            }
        };
    public:
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
        template<>
        static inline constexpr SIMDType Permute<0, 1, 2, 3>( SIMDType v1, SIMDType ) noexcept
        {
            return v1;
        }
        template<>
        static inline constexpr SIMDType Permute<4, 5, 6, 7>( SIMDType, SIMDType v2 ) noexcept
        {
            return v2;
        }


        template<>
        static inline SIMDType Permute<0, 1, 4, 5>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_movelh_ps( v1, v2 );
        }
        template<>
        static inline SIMDType Permute<6, 7, 2, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_movehl_ps( v1, v2 );
        }
        template<>
        static inline SIMDType Permute<0, 4, 1, 5>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_unpacklo_ps( v1, v2 );
        }
        template<>
        static inline SIMDType Permute<2, 6, 3, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_unpackhi_ps( v1, v2 );
        }
        template<>
        static inline SIMDType Permute<2, 3, 6, 7>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_castpd_ps( _mm_unpackhi_pd( _mm_castps_pd( v1 ), _mm_castps_pd( v2 ) ) );
        }

        template<>
        static inline SIMDType Permute<4, 1, 2, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x1 );
        }
        template<>
        static inline SIMDType Permute<0, 5, 2, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x2 );
        }
        template<>
        static inline SIMDType Permute<4, 5, 2, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x3 );
        }
        template<>
        static inline SIMDType Permute<0, 1, 6, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x4 );
        }
        template<>
        static inline SIMDType Permute<4, 1, 6, 3>( SIMDType v1, SIMDType v2 ) noexcept
        {
            return _mm_blend_ps( v1, v2, 0x5 );
        }
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


        static SIMDType IsInf( SIMDType v ) noexcept
        {
            auto tmp = And( v, Constants::AbsMask );
            return Equal( tmp, Constants::Infinity );
        }

        static SIMDType IsNegativeInf( SIMDType v ) noexcept
        {
            return Equal( v, Fill( Constants::NegativeInfinityValue ) );
        }

        static SIMDType IsNegativeInfOrNaN( SIMDType v ) noexcept
        {
            auto isNegativeInf = IsNegativeInf( v );
            auto isNaN = IsNaN( v );
            return Or( isNegativeInf, isNaN );
        }

        static SIMDType IsPositiveInf( SIMDType v ) noexcept
        {
            return Equal( v, Fill( Constants::InfinityValue ) );
        }

        static SIMDType IsPositiveInfOrNaN( SIMDType v ) noexcept
        {
            auto isPositiveInf = IsPositiveInf( v );
            auto isNaN = IsNaN( v );
            return Or( isPositiveInf, isNaN );
        }

        static SIMDType IsZero( SIMDType v ) noexcept
        {
            return Equal( v, _mm_setzero_ps( ) );
        }


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

        static SIMDType FastAbs( SIMDType v ) noexcept
        {
            return And( v, Fill( Constants::AbsMaskValue ) );
        }


        static SIMDType Abs( SIMDType v ) noexcept
        {
            return Max( Sub( Zero( ), v ), v );
        }

        static SIMDType AbsX( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select1222 );
        }
        static SIMDType AbsY( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select2122 );
        }
        static SIMDType AbsZ( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select2212 );
        }
        static SIMDType AbsW( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select2221 );
        }

        static SIMDType AbsXY( SIMDType v ) noexcept
        {
            return Select( Abs( v ), v, Constants::Select1122 );
        }



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

        static SIMDType NegateX( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select1222 );
        }
        static SIMDType NegateY( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select2122 );
        }
        static SIMDType NegateZ( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select2212 );
        }
        static SIMDType NegateW( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select2221 );
        }

        static SIMDType NegateXY( SIMDType v ) noexcept
        {
            return Select( Negate( v ), v, Constants::Select1122 );
        }


        static SIMDType ModAngles( SIMDType v ) noexcept
        {
            constexpr Type Inv2PiValue = static_cast< Type >( 0.15915494309189533577 );
            constexpr Type PiTimes2Value = static_cast< Type >( 2. * M_PI );
            constexpr SIMDType Inv2Pi = { {Inv2PiValue,Inv2PiValue,Inv2PiValue,Inv2PiValue} };
            constexpr SIMDType PiTimes2 = { {PiTimes2Value,PiTimes2Value,PiTimes2Value,PiTimes2Value} };

            auto result = Round( Mul( v, Inv2Pi ) );
            return FNMAdd( result, PiTimes2, v );
        }


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

        static bool AllLess( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = Less( v1, v2 );
            return AllTrue( result );
        }

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

        static bool AllLessOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = LessOrEqual( v1, v2 );
            return AllTrue( result );
        }

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

        static bool AllEqual( SIMDType v1, SIMDType v2, SIMDType epsilon ) noexcept
        {
            auto v = Abs( Sub( v1, v2 ) );
            auto rmm1 = LessOrEqual( v, epsilon );
            return AllTrue( rmm1 );
        }

        static bool AnyEqual( SIMDType v1, SIMDType v2, SIMDType epsilon ) noexcept
        {
            auto v = Abs( Sub( v1, v2 ) );
            auto rmm1 = LessOrEqual( v, epsilon );
            return AnyTrue( rmm1 );
        }

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

        static bool AllNotEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = NotEqual( v1, v2 );
            return AllTrue( result );
        }

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

        static bool AllNearEqual( SIMDType v1, SIMDType v2, SIMDType epsilon ) noexcept
        {
            auto result = NearEqual( v1, v2, epsilon );
            return AllTrue( result );
        }

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

        static bool AllGreaterOrEqual( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = GreaterOrEqual( v1, v2 );
            return AllTrue( result );
        }

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

        static bool AllGreater( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = Greater( v1, v2 );
            return AllTrue( result );
        }

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

        static bool AllSameValue( SIMDType v1, SIMDType v2 ) noexcept
        {
            auto result = SameValue( v1, v2 );
            return AllTrue( result );
        }

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
        /// Square Root of Single-Precision Floating-Point Values
        /// </summary>
        /// <param name="v"></param>
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
        /// Reciprocal square Root of Single-Precision Floating-Point Values
        /// </summary>
        /// <param name="v"></param>
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
        /// Cube Root of Single-Precision Floating-Point Values
        /// </summary>
        /// <param name="v"></param>
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
        /// Reciprocal of Single-Precision Floating-Point Values
        /// </summary>
        /// <param name="v"></param>
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
        /// Computes a vector perpendicular to the argument vector.
        /// </summary>
        /// <param name="v">
        /// The argument vector.
        /// </param>
        /// <returns>
        /// The vector orthogonal to <c>v</c>.
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
        static SIMDType TransformPoint( SIMDType p, SIMDType mr1, SIMDType mr2, SIMDType mr3 )
        {
            auto y = At<1>( p );
            auto result = FMAdd( y, mr2, mr3 );

            auto x = At<0>( p );
            result = FMAdd( x, mr1, result );

            auto w = At<2>( result );
            return Div( result, w );
        }

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


        static SIMDType TransformNormal( SIMDType n, SIMDType matrix )
        {
            // Y
            auto result = At<1>( n );
            result = Mul( result, Swizzle<3, 2, 3, 2>( matrix ) );
            // X
            auto temp = At<0>( n );
            return FMAdd( temp, Swizzle<1, 0, 1, 0>( matrix ), result );
        }

        static SIMDType TransformNormal( SIMDType n, SIMDType mr1, SIMDType mr2 )
        {
            // Y
            auto result = At<1>( n );
            result = Mul( result, mr2 );
            // X
            auto temp = At<0>( n );
            return FMAdd( temp, mr1, result );
        }

        static SIMDType TransformNormal( SIMDType n, SIMDType mr1, SIMDType mr2, SIMDType mr3 )
        {
            auto z = At<2>( n );
            auto result = Mul( z, mr3 );
            auto y = At<1>( n );
            result = FMAdd( y, mr2, result );
            auto x = At<0>( n );
            return FMAdd( x, mr1, result );
        }

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
