#pragma once
#ifndef __HCCMATRIX_H__
#define __HCCMATRIX_H__
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

#include <HCCMath.h>
#include <HCCSIMD.h>
#include <HCCString.h>

namespace Harlinn::Common::Core::Math
{
    namespace Internal
    {
        namespace SIMD
        {
            template<typename ValueT, size_t N>
            struct Traits : public Core::SIMD::Traits<ValueT, N>
            {

            };
        }
    }



    template<typename ValueT, size_t N>
    class alignas( Math::Internal::SIMD::Traits<ValueT,N>::AlignAs ) Vector
    {
    public:
        using Indices = std::make_index_sequence<N>;
        static constexpr size_t Size = N;
        using ValueType = std::remove_cvref_t<ValueT>;
        using UIntType = MakeUnsigned<ValueType>;
        using Traits = Math::Internal::SIMD::Traits<ValueType, N>;
    protected:
        static constexpr size_t Capacity = Traits::Capacity;
        static constexpr size_t SIMDIterations = Traits::SIMDIterations;
        static constexpr size_t SIMDValuesPerIteration = Traits::SIMDTypeSize / sizeof( ValueType );
        using SIMDType = typename Traits::SIMDType;

        ValueType values_[Capacity] = { };
    public:
        constexpr Vector( ) noexcept
        {
            
        }


        template<typename T>
            requires (N > 1)
        constexpr Vector( T x ) noexcept
        {
            std::fill_n( values_, N, x );
        }

        template<typename...Args>
            requires std::conjunction_v<std::is_same<ValueType, std::remove_cvref_t<Args>>...> && (sizeof...( Args ) == N)
        constexpr Vector( Args ...args )
            : values_{ args... } 
        {
        }

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }
        constexpr size_t capacity( ) const noexcept
        {
            return Capacity;
        }

        constexpr ValueType& operator[]( size_t index ) noexcept
        {
            return values_[index];
        }
        constexpr const ValueType& operator[]( size_t index ) const noexcept
        {
            return values_[index];
        }

    private:
        
        template <size_t S, size_t... I>
        [[nodiscard]] constexpr Vector NegImpl( std::index_sequence<I...> )  const
        {
            if constexpr ( IsSignedInteger<ValueType> || IsFloatingPoint<ValueType> )
            {
                return { ( -values_[I] )... };
            }
            else
            {
                return *this;
            }
        }

        [[nodiscard]] Vector NegImpl( )  const
        {
            if constexpr ( IsSignedInteger<ValueType> || IsFloatingPoint<ValueType> )
            {
                Vector result;

                auto simdValue = Traits::Fill( static_cast<ValueType>(0) );

                const ValueType* p1 = values_;
                ValueType* pR = result.values_;
                for ( size_t i = 0; i < SIMDIterations; ++i )
                {
                    Traits::Store( pR, Traits::Sub( simdValue, Traits::Load( p1 ) ) );
                    p1 += SIMDValuesPerIteration;
                    pR += SIMDValuesPerIteration;
                }
                return result;
            }
            else
            {
                return *this;
            }
        }



        template <size_t S, size_t... I>
        [[nodiscard]] constexpr Vector AddImpl( const ValueType( &other )[S], std::index_sequence<I...> )  const
        {
            return { ( values_[I] + other[I] )... };
        }


        [[nodiscard]] Vector AddImpl( const Vector& other )  const
        {
            Vector result;

            const ValueType* p1 = values_;
            const ValueType* p2 = other.values_;
            ValueType* pR = result.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( pR, Traits::Add( Traits::Load( p1 ), Traits::Load( p2 ) ) );
                p1 += SIMDValuesPerIteration;
                p2 += SIMDValuesPerIteration;
                pR += SIMDValuesPerIteration;
            }
            return result;
        }
        template <size_t... I>
        [[nodiscard]] constexpr Vector AddImpl( ValueType value, std::index_sequence<I...> )  const
        {
            return { ( values_[I] + value )... };
        }


        [[nodiscard]] Vector AddImpl( ValueType value )  const
        {
            Vector result;
            auto simdValue = Traits::Fill( value );
            const ValueType* p1 = values_;
            ValueType* pR = result.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( pR, Traits::Add( Traits::Load( p1 ), simdValue ) );
                p1 += SIMDValuesPerIteration;
                pR += SIMDValuesPerIteration;
            }
            return result;
        }

        template <size_t S, size_t... I>
        [[nodiscard]] constexpr Vector SubImpl( const ValueType( &other )[S], std::index_sequence<I...> )  const
        {
            return { ( values_[I] - other[I] )... };
        }

        [[nodiscard]] Vector SubImpl( const Vector& other )  const
        {
            Vector result;

            const ValueType* p1 = values_;
            const ValueType* p2 = other.values_;
            ValueType* pR = result.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( pR, Traits::Sub( Traits::Load( p1 ), Traits::Load( p2 ) ) );
                p1 += SIMDValuesPerIteration;
                p2 += SIMDValuesPerIteration;
                pR += SIMDValuesPerIteration;
            }
            return result;
        }

        template <size_t... I>
        [[nodiscard]] constexpr Vector SubImpl( ValueType value, std::index_sequence<I...> )  const
        {
            return { ( values_[I] - value )... };
        }

        [[nodiscard]] Vector SubImpl( ValueType value )  const
        {
            Vector result;
            auto simdValue = Traits::Fill( value );
            const ValueType* p1 = values_;
            ValueType* pR = result.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( pR, Traits::Sub( Traits::Load( p1 ), simdValue ) );
                p1 += SIMDValuesPerIteration;
                pR += SIMDValuesPerIteration;
            }
            return result;
        }


        template <size_t... I>
        [[nodiscard]] constexpr Vector MulImpl( ValueType value, std::index_sequence<I...> )  const
        {
            return { ( values_[I] * value )... };
        }

        [[nodiscard]] Vector MulImpl( ValueType value )  const
        {
            Vector result;
            auto simdValue = Traits::Fill( value );
            const ValueType* p1 = values_;
            ValueType* pR = result.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( pR, Traits::Mul( Traits::Load( p1 ), simdValue ) );
                p1 += SIMDValuesPerIteration;
                pR += SIMDValuesPerIteration;
            }
            return result;
        }

        template <size_t... I>
        [[nodiscard]] constexpr Vector DivImpl( ValueType value, std::index_sequence<I...> )  const
        {
            return { ( values_[I] / value )... };
        }

        [[nodiscard]] Vector DivImpl( ValueType value )  const
        {
            Vector result;
            auto simdValue = Traits::Fill( value );
            const ValueType* p1 = values_;
            ValueType* pR = result.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( pR, Traits::Div( Traits::Load( p1 ), simdValue ) );
                p1 += SIMDValuesPerIteration;
                pR += SIMDValuesPerIteration;
            }
            return result;
        }


        template <size_t... I>
        [[nodiscard]] constexpr ValueType MagnitudeImpl( std::index_sequence<I...> ) const
        {
            return Math::Sqrt( ( ( values_[I] * values_[I] ) + ... ) );
        }

        template <size_t... I>
        [[nodiscard]] constexpr bool EqualsImpl( const ValueType( &other )[N], std::index_sequence<I...> ) const
        {
            return ( ( values_[I] == other[I] ) && ... );
        }

        [[nodiscard]] constexpr bool EqualsImpl( const Vector& other ) const
        {
            ValueType* p1 = values_;
            const ValueType* p2 = other.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                if constexpr ( std::is_same_v<ValueType, float> )
                {
                    __m256i pcmp = _mm256_cmpeq_pd( _mm256_load_pd( p1 ), _mm256_load_pd( p2 ) );
                    unsigned bitmask = _mm256_movemask_epi8( pcmp );
                    return ( bitmask == 0xffffffffU );
                }
                else
                {
                    __m256i pcmp = _mm256_cmpeq_pd( _mm256_load_pd( p1 ), _mm256_load_pd( p2 ) );
                    unsigned bitmask = _mm256_movemask_epi8( pcmp );
                    return ( bitmask == 0xffffffffU );
                }
                p1 += SIMDValuesPerIteration;
                p2 += SIMDValuesPerIteration;
            }
        }




        template <size_t S,size_t... I>
        constexpr void AddAssignImpl( const ValueType( &other )[S], std::index_sequence<I...> )
        {
            ( ( values_[I] += other[I] ), ... );
        }


        constexpr void AddAssignImpl( const Vector& other )
        {
            ValueType* p1 = values_;
            const ValueType* p2 = other.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( p1, Traits::Add( Traits::Load( p1 ), Traits::Load( p2 ) ) );
                p1 += SIMDValuesPerIteration;
                p2 += SIMDValuesPerIteration;
            }
        }
        template <size_t S, size_t... I>
        constexpr void SubAssignImpl( const ValueType( &other )[N], std::index_sequence<I...> )
        {
            ( ( values_[I] -= other[I] ), ... );
        }
        constexpr void SubAssignImpl( const Vector& other )
        {
            ValueType* p1 = values_;
            const ValueType* p2 = other.values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( p1, Traits::Sub( Traits::Load( p1 ), Traits::Load( p2 ) ) );
                p1 += SIMDValuesPerIteration;
                p2 += SIMDValuesPerIteration;
            }
        }


        template <size_t... I>
        constexpr void AddAssignImpl( ValueType value, std::index_sequence<I...> )
        {
            ( ( values_[I] += value ), ... );
        }


        constexpr void AddAssignImpl( ValueType value )
        {
            auto simdValue = Traits::Fill( value );
            ValueType* p1 = values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( p1, Traits::Add( Traits::Load( p1 ), simdValue ) );
                p1 += SIMDValuesPerIteration;
            }
        }
        template <size_t... I>
        constexpr void SubAssignImpl( ValueType value, std::index_sequence<I...> )
        {
            ( ( values_[I] -= value ), ... );
        }

        constexpr void SubAssignImpl( ValueType value )
        {
            auto simdValue = Traits::Fill( value );
            ValueType* p1 = values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( p1, Traits::Sub( Traits::Load( p1 ), simdValue ) );
                p1 += SIMDValuesPerIteration;
            }
        }


        template <size_t... I>
        constexpr void MulAssignImpl( ValueType value, std::index_sequence<I...> )
        {
            ( ( values_[I] *= value ), ... );
        }


        constexpr void MulAssignImpl( ValueType value )
        {
            auto simdValue = Traits::Fill( value );
            ValueType* p1 = values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( p1, Traits::Mul( Traits::Load( p1 ), simdValue ) );
                p1 += SIMDValuesPerIteration;
            }
        }


        template <size_t... I>
        constexpr void DivAssignImpl( ValueType value, std::index_sequence<I...> )
        {
            ( ( values_[I] /= value ), ... );
        }

        constexpr void DivAssignImpl( ValueType value )
        {
            auto simdValue = Traits::Fill( value );
            ValueType* p1 = values_;
            for ( size_t i = 0; i < SIMDIterations; ++i )
            {
                Traits::Store( p1, Traits::Div( Traits::Load( p1 ), simdValue ) );
                p1 += SIMDValuesPerIteration;
            }
        }


    public:
        [[nodiscard]] constexpr Vector operator-( ) const
        {
            if ( std::is_constant_evaluated( ) )
            {
                return NegImpl<Capacity>( Indices{} );
            }
            else
            {
                return NegImpl( );
            }
        }


        [[nodiscard]] constexpr Vector operator+( const Vector& other ) const
        { 
            if ( std::is_constant_evaluated( ) )
            {
                return AddImpl( other.values_, Indices{} );
            }
            else
            {
                return AddImpl( other );
            }
        }


        [[nodiscard]] constexpr Vector operator-( const Vector& other ) const
        { 
            if ( std::is_constant_evaluated( ) )
            {
                return SubImpl( other.values_, Indices{} );
            }
            else
            {
                return SubImpl( other );
            }
        }
        
        [[nodiscard]] constexpr Vector operator+( const ValueType( &other )[N] ) const
        { 
            return AddImpl( other, Indices{} );
        }
        [[nodiscard]] constexpr Vector operator-( const ValueType( &other )[N] ) const
        { 
            return SubImpl( other, Indices{} );
        }

        [[nodiscard]] constexpr Vector operator+( const ValueType value ) const
        { 
            if ( std::is_constant_evaluated( ) )
            {
                return AddImpl( value, Indices{} );
            }
            else
            {
                return AddImpl( value );
            }
        }
        [[nodiscard]] constexpr Vector operator-( const ValueType value ) const
        { 
            if ( std::is_constant_evaluated( ) )
            {
                return SubImpl( value, Indices{} );
            }
            else
            {
                return SubImpl( value );
            }
        }
        [[nodiscard]] constexpr Vector operator*( const ValueType value ) const
        { 
            if ( std::is_constant_evaluated( ) )
            {
                return MulImpl( value, Indices{} );
            }
            else
            {
                return MulImpl( value );
            }
        }
        [[nodiscard]] constexpr Vector operator/( const ValueType value ) const
        { 
            if ( std::is_constant_evaluated( ) )
            {
                return DivImpl( value, Indices{} );
            }
            else
            {
                return DivImpl( value );
            }
        }

        
        constexpr Vector& operator+=( const Vector& other )
        {
            if ( std::is_constant_evaluated( ) )
            {
                AddAssignImpl( other.values_, Indices{} );
            }
            else
            {
                AddAssignImpl( other );
            }
            return *this;
        }
        constexpr Vector& operator-=( const Vector& other )
        {
            if ( std::is_constant_evaluated( ) )
            {
                SubAssignImpl( other.values_, Indices{} );
            }
            else
            {
                SubAssignImpl( other );
            }
            return *this;
        }

        constexpr Vector& operator+=( ValueType value )
        {
            if ( std::is_constant_evaluated( ) )
            {
                AddAssignImpl( value, Indices{} );
            }
            else
            {
                AddAssignImpl( value );
            }
            return *this;
        }
        constexpr Vector& operator-=( ValueType value )
        {
            if ( std::is_constant_evaluated( ) )
            {
                SubAssignImpl( value, Indices{} );
            }
            else
            {
                SubAssignImpl( value );
            }
            return *this;
        }

        constexpr Vector& operator*=( ValueType value )
        {
            if ( std::is_constant_evaluated( ) )
            {
                MulAssignImpl( value, Indices{} );
            }
            else
            {
                MulAssignImpl( value );
            }
            return *this;
        }
        constexpr Vector& operator/=( ValueType value )
        {
            if ( std::is_constant_evaluated( ) )
            {
                DivAssignImpl( value, Indices{} );
            }
            else
            {
                DivAssignImpl( value );
            }
            return *this;
        }




        [[nodiscard]] AnsiString ToString( ) const
        {
            if ( Size )
            {
                AnsiString result( "[" );
                for ( size_t i = 0; i < Size; ++i )
                {
                    if ( ( i + 1 ) != Size )
                    {
                        result += Format( "{},", values_[i] );
                    }
                    else
                    {
                        result += Format( "{}", values_[i] );
                    }
                }
                result += "]";
                return result;
            }
            else
            {
                return AnsiString("[]");
            }
        }

    };

    namespace Internal
    {
        [[nodiscard]] inline static __m128 cross_productf( __m128 const& vec0, __m128 const& vec1 )
        {
            __m128 tmp0 = _mm_shuffle_ps( vec0, vec0, _MM_SHUFFLE( 3, 0, 2, 1 ) );
            __m128 tmp1 = _mm_shuffle_ps( vec1, vec1, _MM_SHUFFLE( 3, 1, 0, 2 ) );
            __m128 tmp2 = _mm_mul_ps( tmp0, vec1 );
            __m128 tmp3 = _mm_mul_ps( tmp0, tmp1 );
            __m128 tmp4 = _mm_shuffle_ps( tmp2, tmp2, _MM_SHUFFLE( 3, 0, 2, 1 ) );
            return _mm_sub_ps( tmp3, tmp4 );
        }

        [[nodiscard]] inline static __m128 cross_productf2( __m128 const& vec0, __m128 const& vec1 )
        {
            return _mm_permute_ps(
                _mm_sub_ps(
                    _mm_mul_ps( vec0, _mm_permute_ps( vec1, _MM_SHUFFLE( 3, 0, 2, 1 ) ) ),
                    _mm_mul_ps( vec1, _mm_permute_ps( vec0, _MM_SHUFFLE( 3, 0, 2, 1 ) ) )
                ), _MM_SHUFFLE( 3, 0, 2, 1 ) );
        }


        [[nodiscard]] inline static __m256d cross_product( __m256d vec0, __m256d vec1 )
        {
            return _mm256_permute4x64_pd(
                _mm256_sub_pd(
                    _mm256_mul_pd( vec0, _mm256_permute4x64_pd( vec1, _MM_SHUFFLE( 3, 0, 2, 1 ) ) ),
                    _mm256_mul_pd( vec1, _mm256_permute4x64_pd( vec0, _MM_SHUFFLE( 3, 0, 2, 1 ) ) )
                ), _MM_SHUFFLE( 3, 0, 2, 1 ));
        }

        template<typename FloatT>
        [[nodiscard]] inline Vector<FloatT, 3> CrossProduct1( Vector<FloatT, 3>& v1, Vector<FloatT, 3>& v2 )
        {
            return {
                v1[1] * v2[2] - v1[2] * v2[1],
                v1[2] * v2[0] - v1[0] * v2[2],
                v1[0] * v2[1] - v1[1] * v2[0]
            };
        }

        template<typename FloatT>
        [[nodiscard]] inline Vector<FloatT, 3> CrossProduct2( Vector<FloatT, 3>& v1, Vector<FloatT, 3>& v2 )
        {
            return {
                v1[1] * v2[2] - v1[2] * v2[1],
                v1[2] * v2[0] - v1[0] * v2[2],
                v1[0] * v2[1] - v1[1] * v2[0]
            };
        }


    }


    template<typename FloatT>
    [[nodiscard]] inline Vector<FloatT, 3> Cross( Vector<FloatT, 3>& v1, Vector<FloatT, 3>& v2 )
    {

    }

     /*
    template<typename FloatT, size_t N>
    FloatT Dot( Vector<FloatT, N>& v1, Vector<FloatT, N>& v2 )
    {

        static_assert( accumulators > 1 && accumulators <= 4 );
        constexpr int valuesPerLoop = accumulators * 8;
        assert( 0 == count % valuesPerLoop );
        const float* const p1End = p1 + count;

        // These independent accumulators.
        // Depending on the accumulators template argument, 
        // some are unused, "unreferenced local variable" warning is OK.
        __m256 dot0, dot1, dot2, dot3;

        // For the first few values we don't have anything to add yet, just multiplying
        {
            __m256 a = _mm256_loadu_ps( p1 );
            __m256 b = _mm256_loadu_ps( p2 );
            dot0 = _mm256_mul_ps( a, b );
            if constexpr ( accumulators > 1 )
            {
                a = _mm256_loadu_ps( p1 + 8 );
                b = _mm256_loadu_ps( p2 + 8 );
                dot1 = _mm256_mul_ps( a, b );
            }
            if constexpr ( accumulators > 2 )
            {
                a = _mm256_loadu_ps( p1 + 16 );
                b = _mm256_loadu_ps( p2 + 16 );
                dot2 = _mm256_mul_ps( a, b );
            }
            if constexpr ( accumulators > 3 )
            {
                a = _mm256_loadu_ps( p1 + 24 );
                b = _mm256_loadu_ps( p2 + 24 );
                dot3 = _mm256_mul_ps( a, b );
            }
            p1 += valuesPerLoop;
            p2 += valuesPerLoop;
        }

        for ( ; p1 < p1End; p1 += valuesPerLoop, p2 += valuesPerLoop )
        {
            __m256 a = _mm256_loadu_ps( p1 );
            __m256 b = _mm256_loadu_ps( p2 );
            dot0 = fmadd_ps<fma>( a, b, dot0 );
            if constexpr ( accumulators > 1 )
            {
                a = _mm256_loadu_ps( p1 + 8 );
                b = _mm256_loadu_ps( p2 + 8 );
                dot1 = fmadd_ps<fma>( a, b, dot1 );
            }
            if constexpr ( accumulators > 2 )
            {
                a = _mm256_loadu_ps( p1 + 16 );
                b = _mm256_loadu_ps( p2 + 16 );
                dot2 = fmadd_ps<fma>( a, b, dot2 );
            }
            if constexpr ( accumulators > 3 )
            {
                a = _mm256_loadu_ps( p1 + 24 );
                b = _mm256_loadu_ps( p2 + 24 );
                dot3 = fmadd_ps<fma>( a, b, dot3 );
            }
        }

        // Add the accumulators together into dot0. Using pairwise approach for slightly better precision, with 4 accumulators we compute ( d0 + d1 ) + ( d2 + d3 ).
        if constexpr ( accumulators > 1 )
            dot0 = _mm256_add_ps( dot0, dot1 );
        if constexpr ( accumulators > 3 )
            dot2 = _mm256_add_ps( dot2, dot3 );
        if constexpr ( accumulators > 2 )
            dot0 = _mm256_add_ps( dot0, dot2 );
        // Return horizontal sum of all 8 lanes of dot0
        return hadd_ps( dot0 );
    }
    */





    template<typename FloatT, size_t rows, size_t columns>
    class MatrixBase
    {
    public:
        using ValueType = FloatT;
        static constexpr size_t Rows = rows;
        static constexpr size_t Columns = columns;
        static constexpr size_t Size = Rows * Columns;
    protected:
        ValueType values_[Size];
    public:

    };

    template<typename FloatT, size_t rows, size_t columns>
    class Matrix : public MatrixBase<FloatT, rows, columns>
    {
    public:
        using Base = MatrixBase<FloatT, rows, columns>;
        using ValueType = Base::ValueType;
        using UIntType = Base::UIntType;

    };


    template<typename FloatT>
    class Matrix<FloatT, 2, 2> : public MatrixBase<FloatT, 2, 2>
    {
    public:
        using Base = MatrixBase<FloatT, 2, 2>;
        using ValueType = Base::ValueType;
        using UIntType = Base::UIntType;

    };

    template<typename FloatT>
    class Matrix<FloatT, 3, 3> : public MatrixBase<FloatT, 3,3>
    {
    public:
        using Base = MatrixBase<FloatT, 3, 3>;
        using ValueType = Base::ValueType;
        using UIntType = Base::UIntType;

    };

    template<typename FloatT>
    class Matrix<FloatT, 4, 4> : public MatrixBase<FloatT, 4, 4>
    {
    public:
        using Base = MatrixBase<FloatT, 4, 4>;
        using ValueType = Base::ValueType;
        using UIntType = Base::UIntType;

    };


}


#endif
