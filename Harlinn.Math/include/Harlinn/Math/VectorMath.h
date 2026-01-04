#pragma once
#ifndef HARLINN_MATH_VECTORMATH_H_
#define HARLINN_MATH_VECTORMATH_H_

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

#include "Math.h"

namespace Harlinn::Math
{
    template<typename MatrixT, typename size_t N>
    struct SquareMatrixSimd;


    template<ArithmeticType T, size_t N>
    class SquareMatrix;

    namespace Internal
    {
        /// <summary>
		/// Base class for vector types. This is used to identify vector types at compile time.
        /// </summary>
        struct VectorBase
        {
        };

        struct ScalarBase
        {
        };
    }

    /// <summary>
	/// This concept constrains a type to be a Vector type.
    /// </summary>
    template<typename T>
    concept VectorType = std::is_base_of_v<Internal::VectorBase, T>;

    /// <summary>
	/// This concept constrains a type to be a Vector SIMD type.
    /// </summary>
    template<typename T>
    concept VectorSimdType = std::is_base_of_v<Internal::VectorBase, typename T::TupleType>;

    /// <summary>
	/// This concept constrains a type to be either a Vector type or a Vector SIMD type.
    /// </summary>
    template<typename T>
    concept VectorOrVectorSimdType = VectorType<T> || VectorSimdType<T>;

    /// <summary>
	/// This concept constrains a type to be a Scalar type.
    /// </summary>
    template<typename T>
    concept ScalarType = std::is_base_of_v<Internal::ScalarBase, T>;

    /// <summary>
	/// This concept constrains a type to be a Scalar SIMD type.
    /// </summary>
    template<typename T>
    concept ScalarSimdType = std::is_base_of_v<Internal::ScalarBase, typename T::TupleType>;

    /// <summary>
	/// This concept constrains a type to be either a Scalar type or a Scalar SIMD type.
    /// </summary>
    template<typename T>
    concept ScalarOrScalarSimdType = ScalarType<T> || ScalarSimdType<T>;



    /// <summary>
    /// <para>
    /// Vector is specialized for:
    /// </para>
    /// <list type="bullet">
    /// <item>
    /// Vector&lt;float,2&gt;
    /// </item>
    /// <item>
    /// Vector&lt;float,3&gt;
    /// </item>
    /// <item>
    /// Vector&lt;float,4&gt;
    /// </item>
    /// </list>
    /// <para>
    /// The specializations are crafted for use
    /// in graphic apps.
    /// </para>
    /// </summary>
    /// <typeparam name="ValueT">
    /// 
    /// </typeparam>
    /// <typeparam name="N">
    /// The size of the Vector
    /// </typeparam>
    template<ArithmeticType ValueT, size_t N>
    class alignas( SIMD::Traits<ValueT, N>::AlignAs ) Vector : public Internal::VectorBase
    {
    public:
        using Indices = std::make_index_sequence<N>;
        static constexpr size_t Size = N;
        using ValueType = std::remove_cvref_t<ValueT>;
        using UIntType = MakeUnsigned<ValueType>;
        using Traits = SIMD::Traits<ValueType, N>;
    protected:
        static constexpr size_t Capacity = Traits::Capacity;
        static constexpr size_t SIMDIterations = Traits::SIMDIterations;
        static constexpr size_t SIMDValuesPerIteration = Traits::SIMDTypeSize / sizeof( ValueType );
        using SIMDType = typename Traits::SIMDType;

        ValueType values_[ Capacity ] = { };
    public:
        constexpr Vector( ) noexcept
        {

        }


        template<typename T>
            requires ( N > 1 )
        constexpr Vector( T x ) noexcept
        {
            std::fill_n( values_, N, x );
        }

        template<typename...Args>
            requires std::conjunction_v<std::is_same<ValueType, std::remove_cvref_t<Args>>...> && ( sizeof...( Args ) == N )
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
            return values_[ index ];
        }
        constexpr const ValueType& operator[]( size_t index ) const noexcept
        {
            return values_[ index ];
        }

    private:

        template <size_t S, size_t... I>
        [[nodiscard]] constexpr Vector NegImpl( std::index_sequence<I...> )  const
        {
            if constexpr ( IsSignedInteger<ValueType> || IsFloatingPoint<ValueType> )
            {
                return { ( -values_[ I ] )... };
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

                auto simdValue = Traits::Fill( static_cast< ValueType >( 0 ) );

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
        [[nodiscard]] constexpr Vector AddImpl( const ValueType( &other )[ S ], std::index_sequence<I...> )  const
        {
            return { ( values_[ I ] + other[ I ] )... };
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
            return { ( values_[ I ] + value )... };
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
        [[nodiscard]] constexpr Vector SubImpl( const ValueType( &other )[ S ], std::index_sequence<I...> )  const
        {
            return { ( values_[ I ] - other[ I ] )... };
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
            return { ( values_[ I ] - value )... };
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
            return { ( values_[ I ] * value )... };
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
            return { ( values_[ I ] / value )... };
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
            return Math::Sqrt( ( ( values_[ I ] * values_[ I ] ) + ... ) );
        }

        template <size_t... I>
        [[nodiscard]] constexpr bool EqualsImpl( const ValueType( &other )[ N ], std::index_sequence<I...> ) const
        {
            return ( ( values_[ I ] == other[ I ] ) && ... );
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




        template <size_t S, size_t... I>
        constexpr void AddAssignImpl( const ValueType( &other )[ S ], std::index_sequence<I...> )
        {
            ( ( values_[ I ] += other[ I ] ), ... );
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
        constexpr void SubAssignImpl( const ValueType( &other )[ N ], std::index_sequence<I...> )
        {
            ( ( values_[ I ] -= other[ I ] ), ... );
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
            ( ( values_[ I ] += value ), ... );
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
            ( ( values_[ I ] -= value ), ... );
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
            ( ( values_[ I ] *= value ), ... );
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
            ( ( values_[ I ] /= value ), ... );
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

        [[nodiscard]] constexpr Vector operator+( const ValueType( &other )[ N ] ) const
        {
            return AddImpl( other, Indices{} );
        }
        [[nodiscard]] constexpr Vector operator-( const ValueType( &other )[ N ] ) const
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




        [[nodiscard]] std::string ToString( ) const
        {
            if ( Size )
            {
                std::string result( "[" );
                for ( size_t i = 0; i < Size; ++i )
                {
                    if ( ( i + 1 ) != Size )
                    {
                        result += std::format( "{},", values_[ i ] );
                    }
                    else
                    {
                        result += std::format( "{}", values_[ i ] );
                    }
                }
                result += "]";
                return result;
            }
            else
            {
                return std::string( "[]" );
            }
        }

    };

    namespace Internal
    {
        struct TupleBase
        {
        };

        struct TupleSimdBase
        {
        };



        template<typename T>
        struct DistanceType
        {
            using type = float;
        };

        template<>
        struct DistanceType<double>
        {
            using type = double;
        };

        template<>
        struct DistanceType<Int64>
        {
            using type = double;
        };

        template<>
        struct DistanceType<UInt64>
        {
            using type = double;
        };
    }

    /// <summary>
	/// This concept constrains a type to be a Tuple2, Tuple3 or Tuple4 SIMD type.
    /// </summary>
    template<typename T>
    concept SimdType = std::is_base_of_v<Internal::TupleSimdBase, T>;

    /// <summary>
	/// This concept constrains a type to be a Tuple2, Tuple3 or Tuple4 type.
    /// </summary>
    template<typename T>
    concept TupleType = std::is_base_of_v<Internal::TupleBase, T>;

    template<typename T>
    concept SimdOrTupleType = SimdType<T> || TupleType<T>;

    /// <summary>
	/// This concept constrains a type to be either a SIMD type, a Tuple type, or an arithmetic type.
    /// </summary>
    template<typename T>
    concept SimdTupleOrArithmeticType = SimdType<T> || TupleType<T> || ArithmeticType<T>;

    /// <summary>
	/// Determines if the provided Tuple2, Tuple3 or Tuple4 types are compatible,
    /// </summary>
    /// <typeparam name="T">
    /// The first type to compare.
    /// </typeparam>
    /// <typeparam name="...Other">
    /// The other types to compare.
    /// </typeparam>
    template<typename T, typename ... Other>
    constexpr bool IsCompatible = ( std::is_same_v<typename T::Traits, typename Other::Traits> && ... );

    namespace Internal
    {

        /// <summary>
		/// Determines if any of the provided types is a Tuple2, Tuple3 or Tuple4 SIMD type.
        /// </summary>
        /// <typeparam name="...Args">
        /// The types to compare.
        /// </typeparam>
        template<typename ...Args>
        constexpr bool HasSimdType = ( SimdType<Args> || ... );

        /// <summary>
		/// Determines if all of the provided types are Tuple2, Tuple3 or Tuple4 SIMD types.
        /// </summary>
        /// <typeparam name="...Args">
        /// The types to compare.
        /// </typeparam>
        template<typename ...Args>
        constexpr bool AllAreSimdType = ( SimdType<Args> && ... );

        /// <summary>
		/// Determines if any of the provided types is a Tuple2, Tuple3 or Tuple4 type.
        /// </summary>
        /// <typeparam name="...Args">
        /// The types to compare.
        /// </typeparam>
        template<typename ...Args>
        constexpr bool HasTupleType = ( TupleType<Args> || ... );

        /// <summary>
		/// Determines if all of the provided types are Tuple2, Tuple3 or Tuple4 types.
        /// </summary>
        /// <typeparam name="...Args">
        /// The types to compare.
        /// </typeparam>
        template<typename ...Args>
        constexpr bool AllAreTupleType = ( TupleType<Args> && ... );

        /// <summary>
		/// Determines if any of the provided types is either a Tuple2, Tuple3 or Tuple4 SIMD type, or a Tuple2, Tuple3 or Tuple4 type.
        /// </summary>
        /// <typeparam name="...Args">
        /// The types to compare.
        /// </typeparam>
        template<typename ...Args>
        constexpr bool HasSimdOrTupleType = ( SimdOrTupleType<Args> || ... );

        /// <summary>
		/// Determines if all of the provided types are either Tuple2, Tuple3 or Tuple4 SIMD types, or Tuple2, Tuple3 or Tuple4 types.
        /// </summary>
        /// <typeparam name="...Args"></typeparam>
        template<typename ...Args>
        constexpr bool AllAreSimdOrTupleType = ( SimdOrTupleType<Args> && ... );
    }

    namespace Internal
    {

        /// <summary>
        /// Converts a SIMD wrapper type to its underlying SIMD register type.
        /// </summary>
        /// <typeparam name="T">A type satisfying the SimdType concept, which wraps a SIMD register.</typeparam>
        /// <param name="v">The SIMD wrapper object to convert.</param>
        /// <returns>The underlying SIMD register contained within the wrapper object.</returns>
        template<SimdType T>
        constexpr typename T::SIMDType ToSimd( const T& v ) noexcept
        {
            return v.simd;
        }


        /*
        template<SimdType T>
        constexpr const typename T::SIMDType& ToSimd( const T& v ) noexcept
        {
            return v.simd;
        }
        */

        /// <summary>
        /// Converts a tuple-type object to its SIMD representation by loading its values.
        /// </summary>
        /// <typeparam name="T">A tuple-type that must provide a SIMDType member type and a Traits type with a Load function.</typeparam>
        /// <param name="v">The tuple-type object to convert to SIMD format.</param>
        /// <returns>A SIMD representation of the tuple's values.</returns>
        template<TupleType T>
        typename T::SIMDType ToSimd( const T& v ) noexcept
        {
            using Traits = typename T::Traits;
            return Traits::Load( v.values );
        }

        /// <summary>
        /// Returns a reference to the given SIMD type value without modification.
        /// </summary>
        /// <typeparam name="T">A type that satisfies the SimdType concept.</typeparam>
        /// <param name="v">The SIMD type value to return.</param>
        /// <returns>A constant reference to the input value.</returns>
        template<SimdType T>
        constexpr const T& ToSimdType( const T& v ) noexcept
        {
            return v;
        }

        /// <summary>
        /// Converts a tuple type to its corresponding SIMD type.
        /// </summary>
        /// <typeparam name="T">The tuple type to convert. Must have nested Simd and Traits types, and a values member.</typeparam>
        /// <param name="v">The tuple value to convert to SIMD type.</param>
        /// <returns>A SIMD type instance constructed from the tuple's values.</returns>
        template<TupleType T>
        typename T::Simd ToSimdType( const T& v ) noexcept
        {
            using Traits = typename T::Traits;
            return typename T::Simd( Traits::Load( v.values ) );
        }

        /// <summary>
        /// Defines a type alias that determines the appropriate result type for SIMD operations based on whether the input is a SIMD type or a tuple type.
        /// </summary>
        /// <typeparam name="T">A type that satisfies the SimdOrTupleType concept, which can be either a SIMD type or a tuple type.</typeparam>
        template<SimdOrTupleType T>
        using MakeResultType = std::conditional_t< SimdType<T>, T, typename T::Simd >;

    }


    /// <summary>
    /// Holds the SIMD value for a `Tuple2`, `Tuple3`, or `Tuple4`-derived type and provides
    /// high-performance, per-component math operations implemented on top of the underlying
    /// SIMD register type.
    /// </summary>
    /// <typeparam name="TupleT">
    /// A tuple type derived from `Tuple2`, `Tuple3`, or `Tuple4`. The type must define:
    /// - `Traits`: SIMD traits exposing `Type`, `SIMDType`, `AlignAs`, `SIMDTypeCapacity`, and math ops.
    /// - `ArrayType`: contiguous storage compatible with `Traits::Load/Store`.
    /// - `Size`: the component count (2, 3, 4, or extended up to 8 for specific value packs).
    /// - `Simd`: the corresponding `TupleSimd<TupleT>` specialization.
    /// </typeparam>
    /// <remarks>
    /// Design notes:
    /// - TupleSimd is a thin wrapper around the SIMD register (`simd`) and is intended
    ///   to be passed by reference for best performance. Benchmarks showed that passing
    ///   `TupleSimd` objects by value can degrade performance (≈10% in pbrto workloads).
    /// - The class maintains no additional state beyond the single SIMD register and
    ///   relies solely on `TupleT::Traits` for all math operations.
    /// - Construction supports zero-initialization, loading from a tuple or array,
    ///   and initializing from scalars with arity checks (Size == 2, 3, 4, 8).
    ///
    /// Interop and conversions:
    /// - Use `Values()` to materialize a `TupleT` (the structural tuple) from this SIMD form.
    /// - Use free functions `Internal::ToSimd`, `Internal::ToSimdType`, and `Internal::MakeResultType`
    ///   when composing algorithms that operate across Tuple and SIMD forms.
    ///
    /// Performance & correctness:
    /// - All arithmetic and comparison operations are implemented via `Traits` functions
    ///   to guarantee consistent behavior and optimal instruction selection.
    /// - For mixed-dimension operations, the type system restricts usage via `requires` clauses.
    /// - Many accessor utilities (`X()`, `WithAbsXY()`, `SetW(..)`, etc.) rely on
    ///   `Traits::Permute` / `Traits::Extract` and are branchless.
    ///
    /// Safety:
    /// - `HasNaN()` provides a fast detection for invalid floating point inputs.
    /// - Boolean conversion (`operator bool`) checks if any component is non-zero.
    ///
    /// Typical use:
    /// - Compose `TupleSimd` in math kernels to avoid repeated load/store of `TupleT::values`.
    /// - Convert back to `TupleT` only at API boundaries or for serialization/logging.
    /// </remarks>
    template<typename TupleT>
    class alignas( TupleT::Traits::AlignAs ) TupleSimd : public Internal::TupleSimdBase
    {
    public:
        using TupleType = TupleT;
        using Traits = typename TupleType::Traits;
        using ArrayType = typename TupleType::ArrayType;
        using value_type = typename Traits::Type;
        using size_type = size_t;
        using Simd = typename TupleType::Simd;

        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Size = TupleType::Size;
        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;

        SIMDType simd;

        /// <summary>
        /// Default constructor that initializes the SIMD tuple to zero.
        /// </summary>
        TupleSimd( ) noexcept
            : simd( Traits::Zero( ) )
        {
        }

        /// <summary>
        /// Constructs a TupleSimd from SIMD values.
        /// </summary>
        /// <param name="values">The SIMD values to initialize the tuple with.</param>
        TupleSimd( SIMDType values ) noexcept
            : simd( values )
        {
        }

        /// <summary>
        /// Assigns the elements of <c>other.simd</c> to <c>simd</c>.
        /// </summary>
        

        /// <summary>
        /// Constructs a TupleSimd from another SIMD type with compatible traits.
        /// </summary>
        /// <typeparam name="S">
        /// The source SIMD type, which must have either identical Traits or 
        /// the same underlying Type with a smaller or equal Size.
        /// </typeparam>
        /// <param name="other">
        /// The source SIMD object to copy from.
        /// </param>
        template<SimdType S>
            requires std::is_same_v<Traits, typename S::Traits> ||
        ( std::is_same_v<typename Traits::Type, typename S::Traits::Type> && ( Size > S::Size ) )
            TupleSimd( const S & other ) noexcept
            : simd( other.simd )
        {
        }

        /// <summary>
        /// Constructs a TupleSimd from a larger SIMD vector, truncating 
        /// unused components and zeroing them out.
        /// </summary>
        /// <typeparam name="S">
        /// The type of the source SIMD vector. Must have the same underlying 
        /// element type and a size greater than this TupleSimd's size.
        /// </typeparam>
        /// <param name="other">
        /// The source SIMD vector to copy from, which must have a larger size 
        /// than this TupleSimd.
        /// </param>
        template<SimdType S>
            requires std::is_same_v<typename Traits::Type, typename S::Traits::Type> && ( Size < S::Size )
        TupleSimd( const S& other ) noexcept
            : simd( other.simd )
        {
            if constexpr ( Size < 4 )
            {
                simd = Traits::SetW( simd, 0 );
            }
            if constexpr ( Size < 3 )
            {
                simd = Traits::SetZ( simd, 0 );
            }
        }


        /// <summary>
        /// Constructs a TupleSimd from a TupleType by loading its values 
        /// into SIMD registers.
        /// </summary>
        /// <param name="other">
        /// The tuple containing values to load into the SIMD representation.
        /// </param>
        TupleSimd( const TupleType& other ) noexcept
            : simd( Traits::Load( other.values ) )
        {
        }

        /// <summary>
        /// Constructs a TupleSimd by loading values from an array.
        /// </summary>
        /// <param name="values">
        /// The array containing values to load into the SIMD register.
        /// </param>
        TupleSimd( const ArrayType& values ) noexcept
            : simd( Traits::Load( values ) )
        {
        }

        /// <summary>
        /// Assigns <c>x</c> to the first element, and <c>y</c> to the second element, of <c>simd</c>&semi; 
        /// while initializing the remaining elements to zero.
        /// </summary>
        /// <remarks>
        /// Can only be called for a <c>TupleSimd</c> type instantiated for a <c>Tuple2</c> derived type.
        /// </remarks>
        TupleSimd( value_type x, value_type y ) noexcept requires ( Size == 2 )
            : simd( Traits::Set( y, x ) )
        {
        }

        /// <summary>
        /// Assigns <c>x</c> to the first element, <c>y</c> to the second element, and <c>z</c> to the third element, of <c>simd</c>; 
        /// while initializing the remaining elements to zero.
        /// </summary>
        /// <remarks>
        /// Can only be called for a <c>TupleSimd</c> type instantiated for a <c>Tuple3</c> derived type.
        /// </remarks>
        TupleSimd( value_type x, value_type y, value_type z ) noexcept requires ( Size == 3 )
            : simd( Traits::Set( z, y, x ) )
        {
        }

        /// <summary>
        /// Assigns <c>x</c> to the first element, <c>y</c> to the second element, <c>z</c> to the third element, and <c>w</c> to the fourth element, of <c>simd</c>;
        /// while initializing the remaining elements to zero.
        /// </summary>
        /// <remarks>
        /// Can only be called for a <c>TupleSimd</c> type instantiated for a <c>Tuple4</c> derived type.
        /// </remarks>
        TupleSimd( value_type x, value_type y, value_type z, value_type w ) noexcept requires ( Size == 4 )
            : simd( Traits::Set( w, z, y, x ) )
        {
        }

        /// <summary>
        /// Assigns <c>x</c> to the first two elements of <c>simd</c>.
        /// </summary>
        explicit TupleSimd( value_type x ) noexcept requires ( Size == 2 )
            : simd( Traits::Set( x, x ) )
        {
        }


        /// <summary>
        /// Assigns <c>x</c> to the first three elements of <c>simd</c>.
        /// </summary>
        explicit TupleSimd( value_type x ) noexcept requires ( Size == 3 )
            : simd( Traits::Set( x, x, x ) )
        {
        }

        /// <summary>
        /// Assigns <c>x</c> to the first four elements of <c>simd</c>.
        /// </summary>
        explicit TupleSimd( value_type x ) noexcept requires ( Size == 4 )
            : simd( Traits::Set( x, x, x, x ) )
        {
        }


        /// <summary>
        /// Assigns <c>x</c> to the first eight elements of <c>simd</c>.
        /// </summary>
        explicit TupleSimd( value_type x ) noexcept requires ( Size == 8 )
            : simd( Traits::Set( x, x, x, x, x, x, x, x ) )
        {
        }


        /// <summary>
        /// Returns an instance of the <c>Tuple2</c>, <c>Tuple3</c> or <c>Tuple4</c>
        /// derived type initialized using the <c>Size</c> first elements of <c>simd</c>.
        /// </summary>
        TupleType Values( ) const noexcept
        {
            return TupleType( *this );
        }


        /// <summary>
        /// Returns a <c>TupleSimd</c> with each element of <c>simd</c> negated.
        /// </summary>
        TupleSimd operator - ( ) const noexcept
        {
            return Traits::Negate( simd );
        }

        /// <summary>
        /// Returns <c>true</c> if each element of <c>simd</c> is equal to the corresponding element of <c>other.simd</c>, otherwise <c>false</c>.
        /// </summary>
        bool operator == ( const TupleSimd& other ) const noexcept
        {
            return Traits::AllEqual( simd, other.simd );
        }

        /// <summary>
        /// Returns <c>true</c> if any element of <c>simd</c> is not equal to the corresponding element of <c>other.simd</c>, otherwise <c>false</c>.
        /// </summary>
        bool operator != ( const TupleSimd& other ) const noexcept
        {
            return Traits::AnyNotEqual( simd, other.simd );
        }


        /// <summary>
        /// Returns <c>true</c> if each element of <c>simd</c> is equal to <c>value</c>, otherwise <c>false</c>.
        /// </summary>
        bool operator == ( const value_type value ) const noexcept
        {
            return Traits::AllEqual( simd, Traits::Fill( value ) );
        }

        /// <summary>
        /// Returns <c>true</c> if any element of <c>simd</c> is not equal to <c>value</c>, otherwise <c>false</c>.
        /// </summary>
        bool operator != ( const value_type value ) const noexcept
        {
            return Traits::AnyNotEqual( simd, Traits::Fill( value ) );
        }

        /// <summary>
        /// Returns <c>true</c> if each element of <c>simd</c> is equal to the corresponding element of <c>other.values</c>, otherwise <c>false</c>.
        /// </summary>
        template<Math::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        bool operator == ( const T& other ) const noexcept
        {
            return Traits::AllEqual( simd, Traits::Load( other.values ) );
        }

        /// <summary>
        /// Returns <c>true</c> if any element of <c>simd</c> is not equal to the corresponding element of <c>other.values</c>, otherwise <c>false</c>.
        /// </summary>
        template<Math::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        bool operator != ( const T& other ) const noexcept
        {
            return Traits::AllEqual( simd, Traits::Load( other.values ) ) == false;
        }


        /// <summary>
        /// Returns <c>true</c> if any element of <c>simd</c> is equal to <c>value</c>, otherwise <c>false</c>.
        /// </summary>
        bool AnyEqual( const value_type value ) const noexcept
        {
            return Traits::AnyEqual( simd, Traits::Fill( value ) );
        }

        /// <summary>
        /// Returns <c>true</c> if any element of <c>simd</c> is not equal to <c>value</c>, otherwise <c>false</c>.
        /// </summary>
        bool AnyNotEqual( const value_type value ) const noexcept
        {
            return Traits::AnyNotEqual( simd, Traits::Fill( value ) );
        }

        /// <summary>
        /// Returns <c>true</c> if any element of <c>simd</c> is not equal to zero, otherwise <c>false</c>.
        /// </summary>
        explicit operator bool( ) const noexcept
        {
            return Traits::AnyNotEqual( simd, Traits::Zero( ) );
        }




        /// <summary>
        /// Adds each element of <c>other.values</c> to the corresponding element of <c>simd</c>.
        /// </summary>
        template<Math::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        TupleSimd& operator += ( const T& other ) noexcept
        {
            simd = Traits::Add( simd, Traits::Load( other.values ) );
            return *this;
        }

        /// <summary>
        /// Adds each element of <c>other.simd</c> to the corresponding element of <c>simd</c>.
        /// </summary>
        TupleSimd& operator += ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }

        /// <summary>
        /// Adds <c>value</c> to each element of <c>simd</c>.
        /// </summary>
        TupleSimd& operator += ( const value_type value ) noexcept
        {
            simd = Traits::Add( simd, Traits::Fill<Size>( value ) );
            return *this;
        }

        /// <summary>
        /// Subtracts each element of <c>other.values</c> from the corresponding element of <c>simd</c>.
        /// </summary>
        template<Math::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        TupleSimd& operator -= ( const T& other ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Load( other.values ) );
            return *this;
        }

        /// <summary>
        /// Subtracts each element of <c>other.simd</c> from the corresponding element of <c>simd</c>.
        /// </summary>
        TupleSimd& operator -= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        /// <summary>
        /// Subtracts <c>value</c> from each element of <c>simd</c>.
        /// </summary>
        TupleSimd& operator -= ( const value_type value ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Fill<Size>( value ) );
            return *this;
        }

        /// <summary>
        /// Multiplies each element of <c>simd</c> with the corresponding element of <c>other.values</c>.
        /// </summary>
        template<Math::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        TupleSimd& operator *= ( const T& other ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Load( other.values ) );
            return *this;
        }

        /// <summary>
        /// Multiplies each element of <c>simd</c> with the corresponding element of <c>other.simd</c>.
        /// </summary>
        TupleSimd& operator *= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        /// <summary>
        /// Multiplies each element of <c>simd</c> with <c>value</c>.
        /// </summary>
        TupleSimd& operator *= ( const value_type value ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Fill<Size>( value ) );
            return *this;
        }

        /// <summary>
        /// Multiplies each element of <c>simd</c> with the corresponding element of <c>other.values</c>.
        /// </summary>
        template<Math::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        TupleSimd& operator /= ( const T& other ) noexcept
        {
            simd = Traits::Div( simd, Traits::Load( other.values ) );
            return *this;
        }

        /// <summary>
        /// Divides each element of <c>simd</c> by the corresponding element of <c>other.simd</c>.
        /// </summary>
        TupleSimd& operator /= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }

        /// <summary>
        /// Divides each element of <c>simd</c> by <c>value</c>.
        /// </summary>
        TupleSimd& operator /= ( const value_type value ) noexcept
        {
            simd = Traits::Div( simd, Traits::FillDivisor<Size>( value ) );
            return *this;
        }

        /// <summary>
        /// Assigns each element of <c>other.simd</c> to the corresponding element of <c>simd</c>.
        /// </summary>
        /// <param name="other"></param>
        void Assign( const TupleSimd& other ) noexcept
        {
            simd = other.simd;
        }

        /// <summary>
        /// Assigns <c>value</c> to the first <c>Size</c> elements of <c>simd</c>.
        /// </summary>
        void Assign( const value_type value ) noexcept
        {
            simd = Traits::Fill<Size>( value );
        }

        /// <summary>
        /// Assigns each element of <c>other.values</c> to the corresponding element of <c>simd</c>.
        /// </summary>
        template<Math::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        void Assign( const T& other ) noexcept
        {
            simd = Traits::Load( other.values );
        }

        /// <summary>
        /// Assigns each element of <c>values</c> to the corresponding element of <c>simd</c>.
        /// </summary>
        void Assign( SIMDType values ) noexcept
        {
            simd = values;
        }

        /// <summary>
        /// Returns <c>true</c> if at least one of the elements of <c>simd</c>` is NaN, otherwise <c>false</c>.
        /// </summary>
        bool HasNaN( ) const noexcept
        {
            return Traits::HasNaN( simd );
        }

        /// <summary>
        /// Replicates the first element of `simd` to all the elements of the result.
        /// </summary>
        TupleSimd X( ) const
        {
            return Traits::Trim( Traits::At<0>( simd ) );
        }
        /// <summary>
        /// Extracts the first element of `simd`.
        /// </summary>
        value_type x( ) const
        {
            return Traits::Extract<0>( simd );
        }
        /// <summary>
        /// Assigns the first element of `src` to the first element of `simd`.
        /// </summary>
        void SetX( SIMDType src )
        {
            simd = Traits::Permute<4, 1, 2, 3>( simd, src );
        }
        /// <summary>
        /// Assigns the first element of `src.simd` to the first element of `simd`.
        /// </summary>
        void SetX( const TupleSimd& src )
        {
            SetX( src.simd );
        }
        /// <summary>
        /// Assigns `value` to the first element of `simd`.
        /// </summary>
        void SetX( const value_type value )
        {
            SetX( Traits::Fill<Size>( value ) );
        }
        /// <summary>
        /// Sets the first element of `simd` to its absolute value.
        /// </summary>
        void AbsX( )
        {
            simd = Traits::AbsX( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the first element to its absolute value.
        /// </summary>
        TupleSimd WithAbsX( ) const
        {
            return Traits::AbsX( simd );
        }
        /// <summary>
        /// Sets the first element of `simd` to its negated value.
        /// </summary>
        void NegateX( )
        {
            simd = Traits::NegateX( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the first element to its negated value.
        /// </summary>
        TupleSimd WithNegatedX( ) const
        {
            return Traits::NegateX( simd );
        }


        /// <summary>
        /// Replicates the second element of `simd` to all the elements of the result.
        /// </summary>
        TupleSimd Y( ) const
        {
            return Traits::Trim( Traits::At<1>( simd ) );
        }
        /// <summary>
        /// Extracts the second element of `simd`.
        /// </summary>
        value_type y( ) const
        {
            return Traits::Extract<1>( simd );
        }
        /// <summary>
        /// Assigns the second element of `src` to the second element of `simd`.
        /// </summary>
        void SetY( SIMDType src )
        {
            simd = Traits::Permute<0, 5, 2, 3>( simd, src );
        }
        /// <summary>
        /// Assigns the second element of `src.simd` to the second element of `simd`.
        /// </summary>
        void SetY( const TupleSimd& src )
        {
            SetY( src.simd );
        }
        /// <summary>
        /// Assigns `value` to the second element of `simd`.
        /// </summary>
        void SetY( const value_type value )
        {
            SetY( Traits::Fill<Size>( value ) );
        }
        /// <summary>
        /// Sets the second element of `simd` to its absolute value.
        /// </summary>
        void AbsY( )
        {
            simd = Traits::AbsY( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the second element to its absolute value.
        /// </summary>
        TupleSimd WithAbsY( ) const noexcept
        {
            return Traits::AbsY( simd );
        }
        /// <summary>
        /// Sets the second element of `simd` to its negated value.
        /// </summary>
        void NegateY( )
        {
            simd = Traits::NegateY( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the second element to its negated value.
        /// </summary>
        TupleSimd WithNegatedY( ) const
        {
            return Traits::NegateY( simd );
        }

        /// <summary>
        /// Sets the first and second elements of `simd` to their absolute values.
        /// </summary>
        void AbsXY( )
        {
            simd = Traits::AbsXY( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the first and second elements to their absolute values.
        /// </summary>
        TupleSimd WithAbsXY( ) const noexcept
        {
            return Traits::AbsXY( simd );
        }
        /// <summary>
        /// Sets the first and second elements of `simd` to their negated values.
        /// </summary>
        void NegateXY( )
        {
            simd = Traits::NegateXY( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the first and second elements to their negated values.
        /// </summary>
        TupleSimd WithNegatedXY( ) const
        {
            return Traits::NegateXY( simd );
        }

        /// <summary>
        /// Replicates the third element of `simd` to all the elements of the result.
        /// </summary>
        TupleSimd Z( ) const requires ( Size > 2 )
        {
            return Traits::Trim( Traits::At<2>( simd ) );
        }
        /// <summary>
        /// Extracts the third element of `simd`.
        /// </summary>
        value_type z( ) const requires ( Size > 2 )
        {
            return Traits::Extract<2>( simd );
        }
        /// <summary>
        /// Assigns the third element of `src` to the third element of `simd`.
        /// </summary>
        void SetZ( SIMDType src ) requires ( Size > 2 )
        {
            simd = Traits::Permute<0, 1, 6, 3>( simd, src );
        }
        /// <summary>
        /// Assigns the third element of `src.simd` to the third element of `simd`.
        /// </summary>
        void SetZ( const TupleSimd& src ) requires ( Size > 2 )
        {
            SetZ( src.simd );
        }
        /// <summary>
        /// Assigns `value` to the third element of `simd`.
        /// </summary>
        void SetZ( const value_type value ) requires ( Size > 2 )
        {
            SetZ( Traits::Fill<Size>( value ) );
        }
        /// <summary>
        /// Sets the third element of `simd` to its absolute value.
        /// </summary>
        void AbsZ( ) requires ( Size > 2 )
        {
            simd = Traits::AbsZ( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the third element to its absolute value.
        /// </summary>
        TupleSimd WithAbsZ( ) const noexcept requires ( Size > 2 )
        {
            return Traits::AbsZ( simd );
        }
        /// <summary>
        /// Sets the third element of `simd` to its negated value.
        /// </summary>
        void NegateZ( ) requires ( Size > 2 )
        {
            simd = Traits::NegateZ( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the third element to its negated value.
        /// </summary>
        TupleSimd WithNegatedZ( ) const requires ( Size > 2 )
        {
            return Traits::NegateZ( simd );
        }

        /// <summary>
        /// Assigns the first, second and third elements of `src` to the first, second and third elements of `simd`.
        /// </summary>
        void SetXYZ( SIMDType src ) requires ( Size > 2 )
        {
            simd = Traits::Permute<0, 1, 2, 7>( src, simd );
        }
        /// <summary>
        /// Assigns the first, second and third elements of `src.simd` to the first, second and third elements of `simd`.
        /// </summary>
        void SetXYZ( const TupleSimd& src )
        {
            SetXYZ( src.simd );
        }

        /// <summary>
        /// Assigns `x` to the first element of `simd`, `y` to the second element of `simd`, and `z` to the third element of `simd`.
        /// </summary>
        void SetXYZ( const value_type x, const value_type y, const value_type z )
        {
            SetXYZ( Traits::Set( z, y, x ) );
        }

        /// <summary>
        /// Replicates the fourth element of `simd` to all the elements of the result.
        /// </summary>
        TupleSimd W( ) const requires ( Size > 3 )
        {
            return Traits::Trim( Traits::At<3>( simd ) );
        }
        /// <summary>
        /// Extracts the fourth element of `simd`.
        /// </summary>
        value_type w( ) const requires ( Size > 3 )
        {
            return Traits::Extract<3>( simd );
        }

        /// <summary>
        /// Assigns the fourth element of `src` to the fourth element of `simd`.
        /// </summary>
        void SetW( SIMDType src ) requires ( Size > 3 )
        {
            simd = Traits::Permute<0, 1, 2, 7>( simd, src );
        }
        /// <summary>
        /// Assigns the fourth element of `src.simd` to the fourth element of `simd`.
        /// </summary>
        void SetW( const TupleSimd& src ) requires ( Size > 3 )
        {
            SetW( src.simd );
        }
        /// <summary>
        /// Assigns `value` to the fourth element of `simd`.
        /// </summary>
        void SetW( const value_type value ) requires ( Size > 3 )
        {
            SetW( Traits::Fill<Size>( value ) );
        }

        /// <summary>
        /// Sets the fourth element of `simd` to its absolute value.
        /// </summary>
        void AbsW( ) requires ( Size > 3 )
        {
            simd = Traits::AbsW( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the fourth element to its absolute value.
        /// </summary>
        TupleSimd WithAbsW( ) const noexcept requires ( Size > 3 )
        {
            return Traits::AbsW( simd );
        }
        /// <summary>
        /// Sets the fourth element of `simd` to its negated value.
        /// </summary>
        void NegateW( ) requires ( Size > 3 )
        {
            simd = Traits::NegateW( simd );
        }
        /// <summary>
        /// Copies the `TupleSimd` setting the fourth element to its negated value.
        /// </summary>
        TupleSimd WithNegatedW( ) const requires ( Size > 3 )
        {
            return Traits::NegateW( simd );
        }

        /// <summary>
        /// Returns the element at index `idx` in `simd`.
        /// </summary>
        value_type operator[]( size_t idx ) const
        {
            if constexpr ( Size == 1 )
            {
                return Traits::Extract<0>( simd );
            }
            else if constexpr ( Size == 2 )
            {
                switch ( idx )
                {
                    case 0:
                        return Traits::Extract<0>( simd );
                    case 1:
                        return Traits::Extract<1>( simd );
                }
            }
            else if constexpr ( Size == 3 )
            {
                switch ( idx )
                {
                    case 0:
                        return Traits::Extract<0>( simd );
                    case 1:
                        return Traits::Extract<1>( simd );
                    case 2:
                        return Traits::Extract<2>( simd );
                }
            }
            else if constexpr ( Size == 4 )
            {
                switch ( idx )
                {
                    case 0:
                        return Traits::Extract<0>( simd );
                    case 1:
                        return Traits::Extract<1>( simd );
                    case 2:
                        return Traits::Extract<2>( simd );
                    case 3:
                        return Traits::Extract<3>( simd );
                }
            }
            else if constexpr ( Size == 5 )
            {
                switch ( idx )
                {
                    case 0:
                        return Traits::Extract<0>( simd );
                    case 1:
                        return Traits::Extract<1>( simd );
                    case 2:
                        return Traits::Extract<2>( simd );
                    case 3:
                        return Traits::Extract<3>( simd );
                    case 4:
                        return Traits::Extract<4>( simd );
                }
            }
            else if constexpr ( Size == 6 )
            {
                switch ( idx )
                {
                    case 0:
                        return Traits::Extract<0>( simd );
                    case 1:
                        return Traits::Extract<1>( simd );
                    case 2:
                        return Traits::Extract<2>( simd );
                    case 3:
                        return Traits::Extract<3>( simd );
                    case 4:
                        return Traits::Extract<4>( simd );
                    case 5:
                        return Traits::Extract<5>( simd );
                }
            }
            else if constexpr ( Size == 7 )
            {
                switch ( idx )
                {
                    case 0:
                        return Traits::Extract<0>( simd );
                    case 1:
                        return Traits::Extract<1>( simd );
                    case 2:
                        return Traits::Extract<2>( simd );
                    case 3:
                        return Traits::Extract<3>( simd );
                    case 4:
                        return Traits::Extract<4>( simd );
                    case 5:
                        return Traits::Extract<5>( simd );
                    case 6:
                        return Traits::Extract<6>( simd );
                }
            }
            else if constexpr ( Size == 8 )
            {
                switch ( idx )
                {
                    case 0:
                        return Traits::Extract<0>( simd );
                    case 1:
                        return Traits::Extract<1>( simd );
                    case 2:
                        return Traits::Extract<2>( simd );
                    case 3:
                        return Traits::Extract<3>( simd );
                    case 4:
                        return Traits::Extract<4>( simd );
                    case 5:
                        return Traits::Extract<5>( simd );
                    case 6:
                        return Traits::Extract<6>( simd );
                    case 7:
                        return Traits::Extract<7>( simd );
                }
            }
            return operator[]( idx% Size );
        }

        /// <summary>
        /// Returns a `TupleSimd` with all elements set to zero.
        /// </summary>
        static TupleSimd Zero( ) noexcept
        {
            return TupleSimd( Traits::Zero( ) );
        }
        /// <summary>
        /// Returns a `TupleSimd` with all elements set to one.
        /// </summary>
        static TupleSimd One( ) noexcept
        {
            return TupleSimd( Traits::Fill<Size>( static_cast< value_type >( 1 ) ) );
        }

        /// <summary>
        /// Returns a `TupleSimd` the first element set to 1, and the other elements set to 0.
        /// </summary>
        static TupleSimd UnitX( ) noexcept
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( 1 ) ) );
        }
        /// <summary>
        /// Returns a `TupleSimd` the second element set to 1, and the other elements set to 0.
        /// </summary>
        static TupleSimd UnitY( ) noexcept
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ) ) );
        }

        /// <summary>
        /// Returns a `TupleSimd` the third element set to 1, and the other elements set to 0.
        /// </summary>
        static TupleSimd UnitZ( ) noexcept requires ( Size >= 3 )
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) ) );
        }

        /// <summary>
        /// Returns a `TupleSimd` the fourth element set to 1, and the other elements set to 0.
        /// </summary>
        static TupleSimd UnitW( ) noexcept requires ( Size >= 4 )
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) ) );
        }

        /// <summary>
        /// Returns a `TupleSimd` containing the unit vector for the up direction.
        /// </summary>
        static TupleSimd Up( ) noexcept requires ( Size >= 3 )
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ) ) );
        }
        /// <summary>
        /// Returns a `TupleSimd` containing the unit vector for the down direction.
        /// </summary>
        static TupleSimd Down( ) noexcept requires ( Size >= 3 )
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( -1 ), static_cast< value_type >( 0 ) ) );
        }
        /// <summary>
        /// Returns a `TupleSimd` containing the unit vector for the right direction.
        /// </summary>
        static TupleSimd Right( ) noexcept requires ( Size >= 3 )
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( 1 ) ) );
        }

        /// <summary>
        /// Returns a `TupleSimd` containing the unit vector for the left direction.
        /// </summary>
        static TupleSimd Left( ) noexcept requires ( Size >= 3 )
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( -1 ) ) );
        }

        /// <summary>
        /// Returns a `TupleSimd` containing the unit vector for the forward direction.
        /// </summary>
        static TupleSimd Forward( ) noexcept requires ( Size >= 3 )
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( -1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) ) );
        }

        /// <summary>
        /// Returns a `TupleSimd` containing the unit vector for the backward direction.
        /// </summary>
        static TupleSimd Backward( ) noexcept requires ( Size >= 3 )
        {
            return TupleSimd( Traits::Set( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) ) );
        }

        std::string ToString( ) const
        {
            if constexpr ( Size == 2 )
            {
                return std::format( "[{}, {}]", Traits::First( X( ).simd ), Traits::First( Y( ).simd ) );
            }
            else if constexpr ( Size == 3 )
            {
                return std::format( "[{}, {}, {}]", Traits::First( X( ).simd ), Traits::First( Y( ).simd ), Traits::First( Z( ).simd ) );
            }
            else
            {
                return std::format( "[{}, {}, {}, {}]", Traits::First( X( ).simd ), Traits::First( Y( ).simd ), Traits::First( Z( ).simd ), Traits::First( W( ).simd ) );
            }
        }

        friend std::ostream& operator << ( std::ostream& stream, const TupleSimd& t )
        {
            stream << t.ToString( );
            return stream;
        }
    };


    /// <summary>
    /// A tuple holding two numbers.
    /// </summary>
    /// <typeparam name="DerivedT">
    /// A concrete type derived from this template.
    /// </typeparam>
    /// <typeparam name="T">
    /// The type of the values.
    /// </typeparam>
    /// <remarks>
    /// This implementation passes Tuple2 derived objects by reference,
    /// since passing the Tuple2 derived objects by value did not make 
    /// a noticeable difference on the performance of pbrto. This is also
    /// true for Tuple3 derived objects. Passing Tuple4 derived by
    /// value degraded the performance of pbrto by approximately 5 %.
    /// </remarks>
    template<class DerivedT, ArithmeticType T>
    class Tuple2 : public Internal::TupleBase
    {
    public:
        using DerivedType = DerivedT;
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 2;

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
        using ArrayType = typename Traits::ArrayType;

        using reference = typename ArrayType::reference;
        using const_reference = typename ArrayType::const_reference;
        using pointer = typename ArrayType::pointer;
        using const_pointer = typename ArrayType::const_pointer;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
        using reverse_iterator = typename ArrayType::reverse_iterator;
        using const_reverse_iterator = typename ArrayType::const_reverse_iterator;


        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.
        /// </summary>
        using Simd = TupleSimd<DerivedType>;

        union
        {
            //! \unnamed{union}
            ArrayType values;
            struct
            {
                //! \unnamed{union/struct:1}
                value_type x; 
                //! \unnamed{union/struct:2}
                value_type y;
            };
        };

        Tuple2( ) noexcept
            : x( static_cast< value_type >( 0 ) ), y( static_cast< value_type >( 0 ) )
        {
        }

        explicit Tuple2( value_type v ) noexcept
            : x( v ), y( v )
        {
        }

        Tuple2( value_type xv, value_type yv ) noexcept
            : x( xv ), y( yv )
        {
        }

        Tuple2( const ArrayType a ) noexcept
            : values( a )
        {
        }

        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple2( const U& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        {
        }

        template<TupleType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple2( const U& other ) noexcept
            : values( other.values )
        {
        }

        template<TupleType U>
            requires ( std::is_same_v<Traits, typename U::Traits> == false )
        explicit Tuple2( const U& other ) noexcept
            : x( static_cast< value_type >( other.x ) ), y( static_cast< value_type >( other.y ) )
        {
        }


        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        DerivedType& operator = ( const U& other ) noexcept
        {
            values = Traits::ToArray( other.simd );
            return static_cast< DerivedType& >( *this );
        }



        Simd ToSimd( ) const noexcept
        {
            return Simd( Traits::Load( values ) );
        }

        operator Simd( ) const noexcept
        {
            return ToSimd( );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        constexpr bool operator == ( const U& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y );
        }
        template<TupleType U>
            requires ( U::Size == Size )
        constexpr bool operator != ( const U& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y );
        }

        constexpr bool operator == ( value_type value ) const noexcept
        {
            return IsSameValue( x, value ) && IsSameValue( y, value );
        }
        constexpr bool operator != ( value_type value ) const noexcept
        {
            return !IsSameValue( x, value ) || !IsSameValue( y, value );
        }


        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator == ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values ), other.simd );
        }

        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator != ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values ), other.simd ) == false;
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values ) );
        }

        DerivedType& operator += ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Add( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator += ( const U& other ) noexcept
        {
            x += other.x;
            y += other.y;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator += ( const value_type value ) noexcept
        {
            x += value;
            y += value;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Sub( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator -= ( const U& other ) noexcept
        {
            x -= other.x;
            y -= other.y;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const value_type value ) noexcept
        {
            x -= value;
            y -= value;
            return static_cast< DerivedType& >( *this );
        }


        DerivedType& operator *= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Mul( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator *= ( const U& other ) noexcept
        {
            x *= other.x;
            y *= other.y;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator *= ( const value_type value ) noexcept
        {
            x *= value;
            y *= value;
            return static_cast< DerivedType& >( *this );
        }


        DerivedType& operator /= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Div( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator /= ( const U& other ) noexcept
        {
            x /= other.x;
            y /= other.y;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator /= ( const value_type value ) noexcept
        {
            x /= value;
            y /= value;
            return static_cast< DerivedType& >( *this );
        }


        static DerivedType Zero( )
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType One( )
        {
            return DerivedType( static_cast< value_type >( 1 ), static_cast< value_type >( 1 ) );
        }
        static DerivedType UnitX( )
        {
            return DerivedType( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType UnitY( )
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 1 ) );
        }


        const_reference operator[]( size_t index ) const noexcept
        {
            return values[ index ];
        }

        reference operator[]( size_t index ) noexcept
        {
            return values[ index ];
        }

        const_pointer data( ) const noexcept
        {
            return values.data( );
        }
        pointer data( ) noexcept
        {
            return values.data( );
        }

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }

        const_reference front( ) const noexcept
        {
            return values.front( );
        }
        reference front( ) noexcept
        {
            return values.front( );
        }

        const_reference back( ) const noexcept
        {
            return values.back( );
        }
        reference back( ) noexcept
        {
            return values.back( );
        }

        const_iterator begin( ) const noexcept
        {
            return values.begin( );
        }
        const_iterator cbegin( ) const noexcept
        {
            return values.cbegin( );
        }
        iterator begin( ) noexcept
        {
            return values.begin( );
        }
        const_iterator end( ) const noexcept
        {
            return values.end( );
        }
        const_iterator cend( ) const noexcept
        {
            return values.cend( );
        }
        iterator end( ) noexcept
        {
            return values.end( );
        }
        const_reverse_iterator rbegin( ) const noexcept
        {
            return values.rbegin( );
        }
        reverse_iterator rbegin( ) noexcept
        {
            return values.rbegin( );
        }
        const_reverse_iterator rend( ) const noexcept
        {
            return values.rend( );
        }
        reverse_iterator rend( ) noexcept
        {
            return values.rend( );
        }




        void Assign( value_type xv, value_type yv ) noexcept
        {
            x = xv;
            y = yv;
        }
        void Assign( const ArrayType& src ) noexcept
        {
            values = src;
        }
        void Assign( SIMDType src ) noexcept
        {
            values = Traits::ToArray( src );
        }

        bool HasNaN( ) const noexcept
        {
            return std::isnan( x ) || std::isnan( y );
        }

        bool IsFinite( ) const noexcept
        {
            return std::isfinite( x ) && std::isfinite( y );
        }

        bool IsInfinite( ) const noexcept
        {
            return std::isinf( x ) || std::isinf( y );
        }


        std::string ToString( ) const
        {
            return std::format( "[{}, {}]", x, y );
        }


    };

    template<typename DerivedT, ArithmeticType T>
    class Tuple3 : public Internal::TupleBase
    {
    public:
        using DerivedType = DerivedT;
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 3;

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
        using ArrayType = typename Traits::ArrayType;

        using reference = typename ArrayType::reference;
        using const_reference = typename ArrayType::const_reference;
        using pointer = typename ArrayType::pointer;
        using const_pointer = typename ArrayType::const_pointer;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
        using reverse_iterator = typename ArrayType::reverse_iterator;
        using const_reverse_iterator = typename ArrayType::const_reverse_iterator;

        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using Simd = TupleSimd<DerivedType>;

        union
        {
            //! \unnamed{union}
            ArrayType values;
            struct
            {
                //! \unnamed{union/struct:1}
                value_type x; 
                //! \unnamed{union/struct:2}
                value_type y; 
                //! \unnamed{union/struct:3}
                value_type z;
            };
        };

        Tuple3( ) noexcept
            : x{}, y{}, z{}
        {
        }

        explicit Tuple3( value_type v ) noexcept
            : x( v ), y( v ), z( v )
        {
        }

        Tuple3( value_type xv, value_type yv, value_type zv ) noexcept
            : x( xv ), y( yv ), z( zv )
        {
        }

        Tuple3( const ArrayType a ) noexcept
            : values( a )
        {
        }


        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple3( const U& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        {
        }




        template<TupleType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple3( const U& other ) noexcept
            : values( other.values )
        {
        }

        template<TupleType U>
            requires ( std::is_same_v<Traits, typename U::Traits> == false )
        explicit Tuple3( const U& other ) noexcept
            : x( static_cast< value_type >( other.x ) ), y( static_cast< value_type >( other.y ) ), z( static_cast< value_type >( other.z ) )
        {
        }


        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        DerivedType& operator = ( const U& other ) noexcept
        {
            values = Traits::ToArray( other.simd );
            return static_cast< DerivedType& >( *this );
        }




        Simd ToSimd( ) const noexcept
        {
            return Simd( Traits::Load( values ) );
        }

        operator Simd( ) const noexcept
        {
            return ToSimd( );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        constexpr bool operator == ( const U& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z );
        }
        template<TupleType U>
            requires ( U::Size == Size )
        constexpr bool operator != ( const U& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y ) || !IsSameValue( z, other.z );
        }

        constexpr bool operator == ( value_type value ) const noexcept
        {
            return IsSameValue( x, value ) && IsSameValue( y, value ) && IsSameValue( z, value );
        }
        constexpr bool operator != ( value_type value ) const noexcept
        {
            return !IsSameValue( x, value ) || !IsSameValue( y, value ) || !IsSameValue( z, value );
        }

        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator == ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values ), other.simd );
        }

        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator != ( const U& other ) const noexcept
        {
            return Traits::AnyNotEqual( Traits::Load( values ), other.simd );
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values ) );
        }

        DerivedType& operator += ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Add( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator += ( const U& other ) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator += ( const value_type value ) noexcept
        {
            x += value;
            y += value;
            z += value;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Sub( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator -= ( const U& other ) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const value_type value ) noexcept
        {
            x -= value;
            y -= value;
            z -= value;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator *= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Mul( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator *= ( const U& other ) noexcept
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator *= ( const value_type value ) noexcept
        {
            x *= value;
            y *= value;
            z *= value;
            return static_cast< DerivedType& >( *this );
        }


        DerivedType& operator /= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Div( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator /= ( const U& other ) noexcept
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator /= ( const value_type value ) noexcept
        {
            x /= value;
            y /= value;
            z /= value;
            return static_cast< DerivedType& >( *this );
        }

        const_reference operator[]( size_t index ) const noexcept
        {
            return values[ index ];
        }

        reference operator[]( size_t index ) noexcept
        {
            return values[ index ];
        }


        static DerivedType Zero( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType One( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 1 ), static_cast< value_type >( 1 ), static_cast< value_type >( 1 ) );
        }

        static DerivedType UnitX( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType UnitY( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 1 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType UnitZ( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 1 ) );
        }
        static DerivedType Up( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 1 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType Down( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( -1 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType Right( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType Left( ) noexcept
        {
            return DerivedType( static_cast< value_type >( -1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType Forward( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( -1 ) );
        }
        static DerivedType Backward( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 1 ) );
        }


        const_pointer data( ) const noexcept
        {
            return values.data( );
        }
        pointer data( ) noexcept
        {
            return values.data( );
        }

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }

        const_reference front( ) const noexcept
        {
            return values.front( );
        }
        reference front( ) noexcept
        {
            return values.front( );
        }

        const_reference back( ) const noexcept
        {
            return values.back( );
        }
        reference back( ) noexcept
        {
            return values.back( );
        }

        const_iterator begin( ) const noexcept
        {
            return values.begin( );
        }
        const_iterator cbegin( ) const noexcept
        {
            return values.cbegin( );
        }
        iterator begin( ) noexcept
        {
            return values.begin( );
        }
        const_iterator end( ) const noexcept
        {
            return values.end( );
        }
        const_iterator cend( ) const noexcept
        {
            return values.cend( );
        }
        iterator end( ) noexcept
        {
            return values.end( );
        }
        const_reverse_iterator rbegin( ) const noexcept
        {
            return values.rbegin( );
        }
        reverse_iterator rbegin( ) noexcept
        {
            return values.rbegin( );
        }
        const_reverse_iterator rend( ) const noexcept
        {
            return values.rend( );
        }
        reverse_iterator rend( ) noexcept
        {
            return values.rend( );
        }

        void Assign( value_type xv, value_type yv, value_type zv ) noexcept
        {
            x = xv;
            y = yv;
            z = zv;
        }
        void Assign( const ArrayType& src ) noexcept
        {
            values = src;
        }
        void Assign( SIMDType src ) noexcept
        {
            values = Traits::ToArray( src );
        }

        bool HasNaN( ) const noexcept
        {
            return std::isnan( x ) || std::isnan( y ) || std::isnan( z );
        }

        bool IsFinite( ) const noexcept
        {
            return std::isfinite( x ) && std::isfinite( y ) && std::isfinite( z );
        }

        bool IsInfinite( ) const noexcept
        {
            return std::isinf( x ) || std::isinf( y ) || std::isinf( z );
        }

        std::string ToString( ) const
        {
            return std::format( "[{}, {}, {}]", x, y, z );
        }
    };

    template<typename DerivedT, ArithmeticType T>
    class Tuple4 : public Internal::TupleBase
    {
    public:
        using DerivedType = DerivedT;
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 4;

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
        using ArrayType = typename Traits::ArrayType;

        using reference = typename ArrayType::reference;
        using const_reference = typename ArrayType::const_reference;
        using pointer = typename ArrayType::pointer;
        using const_pointer = typename ArrayType::const_pointer;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
        using reverse_iterator = typename ArrayType::reverse_iterator;
        using const_reverse_iterator = typename ArrayType::const_reverse_iterator;

        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using Simd = TupleSimd<DerivedType>;

        union
        {
            //! \unnamed{union}
            ArrayType values;
            struct
            {
                //! \unnamed{union/struct:1}
                value_type x;
                //! \unnamed{union/struct:2}
                value_type y; 
                //! \unnamed{union/struct:3}
                value_type z; 
                //! \unnamed{union/struct:4}
                value_type w;
            };
        };

        Tuple4( ) noexcept
            : x( static_cast< value_type >( 0 ) ), y( static_cast< value_type >( 0 ) ), z( static_cast< value_type >( 0 ) ), w( static_cast< value_type >( 0 ) )
        {
        }

        Tuple4( value_type value ) noexcept
            : x( value ), y( value ), z( value ), w( value )
        {
        }

        Tuple4( value_type xv, value_type yv, value_type zv, value_type wv ) noexcept
            : x( xv ), y( yv ), z( zv ), w( wv )
        {
        }

        Tuple4( const ArrayType& a ) noexcept
            : values( a )
        {
        }

        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple4( const U& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        {
        }

        template<TupleType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple4( const U& other ) noexcept
            : values( other.values )
        {
        }

        template<TupleType U>
            requires ( std::is_same_v<Traits, typename U::Traits> == false )
        explicit Tuple4( const U& other ) noexcept
            : x( static_cast< value_type >( other.x ) ), y( static_cast< value_type >( other.y ) ), z( static_cast< value_type >( other.z ) ), w( static_cast< value_type >( other.w ) )
        {
        }

        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        DerivedType& operator = ( const U& other ) noexcept
        {
            values = Traits::ToArray( other.simd );
            return static_cast< DerivedType& >( *this );
        }

        Simd ToSimd( ) const noexcept
        {
            return Simd( Traits::Load( values ) );
        }

        explicit operator Simd( ) const noexcept
        {
            return ToSimd( );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        constexpr bool operator == ( const U& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z ) && IsSameValue( w, other.w );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        constexpr bool operator != ( const U& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y ) || !IsSameValue( z, other.z ) || !IsSameValue( w, other.w );
        }

        constexpr bool operator == ( value_type value ) const noexcept
        {
            return IsSameValue( x, value ) && IsSameValue( y, value ) && IsSameValue( z, value ) && IsSameValue( w, value );
        }
        constexpr bool operator != ( value_type value ) const noexcept
        {
            return !IsSameValue( x, value ) || !IsSameValue( y, value ) || !IsSameValue( z, value ) || !IsSameValue( w, value );
        }

        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator == ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values ), other.simd );
        }

        template<SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator != ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values ), other.simd ) == false;
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values ) );
        }

        DerivedType& operator += ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Add( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator += ( const U& other ) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator += ( const value_type value ) noexcept
        {
            x += value;
            y += value;
            z += value;
            w += value;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Sub( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator -= ( const U& other ) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const value_type value ) noexcept
        {
            x -= value;
            y -= value;
            z -= value;
            w -= value;
            return static_cast< DerivedType& >( *this );
        }


        DerivedType& operator *= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Mul( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator *= ( const U& other ) noexcept
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator *= ( const value_type value ) noexcept
        {
            x *= value;
            y *= value;
            z *= value;
            w *= value;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator /= ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Div( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<TupleType U>
            requires ( U::Size == Size )
        DerivedType& operator /= ( const U& other ) noexcept
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator /= ( const value_type value ) noexcept
        {
            x /= value;
            y /= value;
            z /= value;
            w /= value;
            return static_cast< DerivedType& >( *this );
        }

        const_reference operator[]( size_t index ) const noexcept
        {
            return values[ index ];
        }

        reference operator[]( size_t index ) noexcept
        {
            return values[ index ];
        }

        static DerivedType Zero( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType One( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 1 ), static_cast< value_type >( 1 ), static_cast< value_type >( 1 ), static_cast< value_type >( 1 ) );
        }

        static DerivedType UnitX( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType UnitY( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 1 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType UnitZ( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 1 ), static_cast< value_type >( 0 ) );
        }
        static DerivedType UnitW( ) noexcept
        {
            return DerivedType( static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 0 ), static_cast< value_type >( 1 ) );
        }

        const_pointer data( ) const noexcept
        {
            return values.data( );
        }
        pointer data( ) noexcept
        {
            return values.data( );
        }

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }

        const_reference front( ) const noexcept
        {
            return values.front( );
        }
        reference front( ) noexcept
        {
            return values.front( );
        }

        const_reference back( ) const noexcept
        {
            return values.back( );
        }
        reference back( ) noexcept
        {
            return values.back( );
        }

        const_iterator begin( ) const noexcept
        {
            return values.begin( );
        }
        const_iterator cbegin( ) const noexcept
        {
            return values.cbegin( );
        }
        iterator begin( ) noexcept
        {
            return values.begin( );
        }
        const_iterator end( ) const noexcept
        {
            return values.end( );
        }
        const_iterator cend( ) const noexcept
        {
            return values.cend( );
        }
        iterator end( ) noexcept
        {
            return values.end( );
        }
        const_reverse_iterator rbegin( ) const noexcept
        {
            return values.rbegin( );
        }
        reverse_iterator rbegin( ) noexcept
        {
            return values.rbegin( );
        }
        const_reverse_iterator rend( ) const noexcept
        {
            return values.rend( );
        }
        reverse_iterator rend( ) noexcept
        {
            return values.rend( );
        }

        void Assign( value_type xv, value_type yv, value_type zv, value_type wv ) noexcept
        {
            x = xv;
            y = yv;
            z = zv;
            w = wv;
        }
        void Assign( const ArrayType& src ) noexcept
        {
            values = src;
        }
        void Assign( SIMDType src ) noexcept
        {
            values = Traits::ToArray( src );
        }

        bool HasNaN( ) const noexcept
        {
            return std::isnan( x ) || std::isnan( y ) || std::isnan( z ) || std::isnan( w );
        }

        bool IsFinite( ) const noexcept
        {
            return std::isfinite( x ) && std::isfinite( y ) && std::isfinite( z ) && std::isfinite( w );
        }

        bool IsInfinite( ) const noexcept
        {
            return std::isinf( x ) || std::isinf( y ) || std::isinf( z ) || std::isinf( w );
        }

        std::string ToString( ) const
        {
            return std::format( "[{}, {}, {}, {}]", x, y, z, w );
        }

    };


    // Addition
    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto operator + ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::Add( lhs.simd, rhs.simd ) );
    }


    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasTupleType<T, U>
    inline auto operator + ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( Internal::AllAreTupleType<T, U> && T::Size < 3 )
        {
            return T( lhs.x + rhs.x, lhs.y + rhs.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Add( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ) ) );
        }
    }

    template<ArithmeticType T, SimdType U>
    inline auto operator + ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Add( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), rhs.simd ) );
    }

    template<SimdType T, ArithmeticType U>
    inline auto operator + ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Add( lhs.simd, Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) ) );
    }

    template<ArithmeticType T, TupleType U>
    inline auto operator + ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        if constexpr ( U::Size < 3 )
        {
            return U( lhs + rhs.x, lhs + rhs.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<U>;
            return ResultType( Traits::Add( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), Traits::Load( rhs.values ) ) );
        }
    }

    template<TupleType T, ArithmeticType U>
    inline auto operator + ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( T::Size < 3 )
        {
            return T( lhs.x + rhs, lhs.y + rhs );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Add( Traits::Load( lhs.values ), Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) ) );
        }
    }

    // Subtraction
    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto operator - ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::Sub( lhs.simd, rhs.simd ) );
    }


    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasTupleType<T, U>
    inline auto operator - ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( Internal::AllAreTupleType<T, U> && T::Size < 3 )
        {
            return T( lhs.x - rhs.x, lhs.y - rhs.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Sub( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ) ) );
        }
    }

    template<ArithmeticType T, SimdType U>
    inline auto operator - ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Sub( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), rhs.simd ) );
    }

    template<SimdType T, ArithmeticType U>
    inline auto operator - ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Sub( lhs.simd, Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) ) );
    }

    template<ArithmeticType T, TupleType U>
    inline auto operator - ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        if constexpr ( U::Size < 3 )
        {
            return U( lhs - rhs.x, lhs - rhs.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<U>;
            return ResultType( Traits::Sub( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), Traits::Load( rhs.values ) ) );
        }
    }

    template<TupleType T, ArithmeticType U>
    inline auto operator - ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( T::Size < 3 )
        {
            return T( lhs.x - rhs, lhs.y - rhs );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Sub( Traits::Load( lhs.values ), Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) ) );
        }
    }


    // Multiplication
    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto operator * ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::Mul( lhs.simd, rhs.simd ) );
    }

    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasTupleType<T, U>
    inline auto operator * ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( Internal::AllAreTupleType<T, U> && T::Size < 3 )
        {
            return T( lhs.x * rhs.x, lhs.y * rhs.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Mul( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ) ) );
        }
    }

    template<ArithmeticType T, SimdType U>
    inline auto operator * ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        using ResultType = U;
        return ResultType( Traits::Mul( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), rhs.simd ) );
    }

    template<SimdType T, ArithmeticType U>
    inline auto operator * ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::Mul( lhs.simd, Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) ) );
    }

    template<ArithmeticType T, TupleType U>
    inline auto operator * ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        if constexpr ( U::Size < 3 )
        {
            return U( lhs * rhs.x, lhs * rhs.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<U>;
            return ResultType( Traits::Mul( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), Traits::Load( rhs.values ) ) );
        }
    }

    template<TupleType T, ArithmeticType U>
    inline auto operator * ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( T::Size < 3 )
        {
            return T( lhs.x * rhs, lhs.y * rhs );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Mul( Traits::Load( lhs.values ), Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) ) );
        }
    }


    // Division
    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto operator / ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::Div( lhs.simd, rhs.simd ) );
    }


    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasTupleType<T, U>
    inline auto operator / ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( Internal::AllAreTupleType<T, U> && T::Size < 3 )
        {
            return T( lhs.x / rhs.x, lhs.y / rhs.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Div( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ) ) );
        }
    }

    template<ArithmeticType T, SimdType U>
    inline auto operator / ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Div( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), rhs.simd ) );
    }

    template<SimdType T, ArithmeticType U>
    inline auto operator / ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Div( lhs.simd, Traits::FillDivisor<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) ) );
    }

    template<ArithmeticType T, TupleType U>
    inline auto operator / ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        if constexpr ( U::Size < 3 )
        {
            return U( lhs / rhs.x, lhs / rhs.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<U>;
            return ResultType( Traits::Div( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), Traits::Load( rhs.values ) ) );
        }
    }

    template<TupleType T, ArithmeticType U>
    inline auto operator / ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( T::Size < 3 )
        {
            return T( lhs.x / rhs, lhs.y / rhs );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Div( Traits::Load( lhs.values ), Traits::FillDivisor<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) ) );
        }
    }

    // Operations

    /// <summary>
    /// Retrieves the lowest element of v 
    /// </summary>
    template<SimdType T>
    inline auto First( const T& v )
    {
        using Traits = typename T::Traits;
        return Traits::First( v.simd );
    }
    /// <summary>
    /// Retrieves the lowest element of v 
    /// </summary>
    template<TupleType T>
    inline auto First( const T& v )
    {
        return v.x;
    }


    /// <summary>
    /// Calculates the horizontal sum of the elements in the vector.
    /// </summary>
    template<SimdType T>
    inline T HSum( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HSum( t.simd );
    }

    /// <summary>
    /// Calculates the horizontal sum of the elements in the vector.
    /// </summary>
    template<SimdType T>
    inline typename T::value_type ScalarHSum( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Traits::HSum( t.simd ) );
    }

    /// <summary>
    /// Calculates the horizontal sum of the elements in the vector.
    /// </summary>
    template<TupleType T>
    inline typename T::value_type ScalarHSum( const T& t ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return t.x + t.y;
        }
        else if constexpr ( T::Size == 3 )
        {
            return t.x + t.y + t.z;
        }
        else if constexpr ( T::Size == 4 )
        {
            return t.x + t.y + t.z + t.w;
        }
        else
        {
            typename T::value_type result{};
            for ( size_t i = 0; i < T::Size; i++ )
            {
                result += t.values[ i ];
            }
            return result;
        }
    }
    /// <summary>
    /// Calculates the horizontal sum of the elements in the vector.
    /// </summary>
    template<TupleType T>
    inline typename T::Simd HSum( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill<Traits::Size>( ScalarHSum( t ) );
    }

    // Avg
    template<SimdType T>
    inline auto Avg( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Div( Traits::HSum( t.simd ), Traits::FillDivisor<Traits::Size>( static_cast< typename Traits::Type >( Traits::Size ) ) ) );
    }
    template<TupleType T>
    inline auto Avg( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Div( Traits::HSum( Traits::Load( t.values ) ), Traits::FillDivisor<Traits::Size>( static_cast< typename Traits::Type >( Traits::Size ) ) ) );
    }


    /// <summary>
    /// Calculates the average value of the elements in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline typename T::value_type ScalarAvg( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return ScalarHSum( t ) / static_cast< typename Traits::Type >( Traits::Size );
    }

    /// <summary>
    /// Calculates the horizontal product of the elements in the vector.
    /// </summary>
    template<SimdType T>
    inline T HProd( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HProd( t.simd );
    }

    template<SimdType T>
    inline auto ScalarHProd( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::HProd( t ).simd );
    }

    /// <summary>
    /// Calculates the horizontal product of the elements in the vector.
    /// </summary>
    template<TupleType T, typename ResultT = typename T::value_type>
    inline ResultT ScalarHProd( const T& t ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return t.x * t.y;
        }
        else if constexpr ( T::Size == 3 )
        {
            return t.x * t.y * t.z;
        }
        else if constexpr ( T::Size == 4 )
        {
            return t.x * t.y * t.z * t.w;
        }
        else
        {
            ResultT result = static_cast< ResultT >( 1 );
            for ( size_t i = 0; i < T::Size; i++ )
            {
                result *= t.values[ i ];
            }
            return result;
        }
    }
    /// <summary>
    /// Calculates the horizontal product of the elements in the vector.
    /// </summary>
    template<TupleType T>
    inline typename T::Simd HProd( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill<Traits::Size>( ScalarHProd( t ) );
    }


    // AllTrue

    /// <summary>
    /// Returns true if all the elements of the argument have all their bits set to 1 
    /// </summary>
    template<SimdOrTupleType T>
    inline bool AllTrue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllTrue( Internal::ToSimd( v ) );
    }

    // AnyTrue

    /// <summary>
    /// Returns true if any of the elements of the argument have all their bits set to 1 
    /// </summary>
    template<SimdOrTupleType T>
    inline bool AnyTrue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllTrue( Internal::ToSimd( v ) );
    }

    // Less

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
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Less( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Less( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// If an element of v1 is less than value, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto Less( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Less( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) ) );
    }

    /// <summary>
    /// Determines whether value is less than the elements of v2.
    /// </summary>
    /// <returns>
    /// If value is less than an element of v2, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto Less( T value, const U& v2 ) noexcept
    {
        using Traits = typename U::Traits;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Less( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are less than 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if all the elements of v1 is less than their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AllLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// true if all the elements of v1 is less than value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AllLess( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is less than all of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is less than any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AllLess( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }


    /// <summary>
    /// Determines whether any of the elements of v1 are less than 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if any of the elements of v1 is less than their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AnyLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether any of the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// true if any of the elements of v1 is less than value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AnyLess( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is less than any of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is less than any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AnyLess( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }

    // LessOrEqual

    /// <summary>
    /// Determines whether the elements of v1 are less than, or equal to, 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// If an element of v1 is less than, or equal to, the corresponding element of v2,
    /// the corresponding element in the result will be set to 0xFFFFFFFF,
    /// otherwise the corresponding element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto LessOrEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::LessOrEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether the elements of v1 are less than, or equal to, value.
    /// </summary>
    /// <returns>
    /// If an element of v1 is less than, or equal to, value, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto LessOrEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::LessOrEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) ) );
    }

    /// <summary>
    /// Determines whether value is less than, or equal to, the elements of v2.
    /// </summary>
    /// <returns>
    /// If value is less than, or equal to, an element of v2, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto LessOrEqual( const T value, const U& v2 ) noexcept
    {
        using Traits = typename U::Traits;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::LessOrEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are less than, or equal to, 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if all the elements of v1 is less than, or equal to, their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AllLessOrEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLessOrEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are less than, or equal to, value.
    /// </summary>
    /// <returns>
    /// true if all the elements of v1 is less than, or equal to, value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AllLessOrEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLessOrEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is less than, or equal to, all of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is less than, or equal to, any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AllLessOrEqual( const T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLessOrEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }


    /// <summary>
    /// Determines whether any of the elements of v1 are less than, or equal to, 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if any of the elements of v1 is less than, or equal to, their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AnyLessOrEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLessOrEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether any of the elements of v1 are less than, or equal to, value.
    /// </summary>
    /// <returns>
    /// true if any of the elements of v1 is less than, or equal to, value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AnyLessOrEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLessOrEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is less than, or equal to, any of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is less than, or equal to, any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AnyLessOrEqual( const T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLessOrEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }


    // Equal

    /// <summary>
    /// Determines whether the elements of lhs and the corresponding elements of rhs are 
    /// less or equally apart than the corresponding element of epsilon.
    /// </summary>
    /// <param name="lhs">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="rhs">
    /// The second source of values for the comparison.
    /// </param>
    /// <param name="epsilon">
    /// The source of the maximum difference between the
    /// corresponding elements from lhs and rhs.
    /// </param>
    /// <returns>
    /// If an element of lhs and the corresponding elements of rhs are less
    /// or equally apart than the corresponding element of epsilon,
    /// the corresponding element in the result will be set to 0xFFFFFFFF,
    /// otherwise the corresponding element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline auto Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Equal( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ), Internal::ToSimd( epsilon ) ) );
    }


    /// <summary>
    /// Determines whether the elements of lhs and the corresponding elements of rhs are 
    /// less or equally apart than the value of epsilon.
    /// </summary>
    /// <param name="lhs">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="rhs">
    /// The second source of values for the comparison.
    /// </param>
    /// <param name="epsilon">
    /// The maximum difference between the elements from lhs and rhs.
    /// </param>
    /// <returns>
    /// If an element of lhs and the corresponding elements of rhs are less
    /// or equally apart than the value of epsilon, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline auto Equal( const S& lhs, const T& rhs, U epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Equal( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( epsilon ) ) ) );
    }


    // AllEqual

    /// <summary>
    /// Determines whether all the elements of lhs and their corresponding element of rhs are 
    /// less or equally apart than the corresponding element of epsilon.
    /// </summary>
    /// <param name="lhs">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="rhs">
    /// The second source of values for the comparison.
    /// </param>
    /// <param name="epsilon">
    /// The source of the maximum difference between the
    /// corresponding elements from lhs and rhs.
    /// </param>
    /// <returns>
    /// true if all the elements of lhs and the corresponding elements of rhs are less
    /// or equally apart than the corresponding element of epsilon, otherwise false.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline bool AllEqual( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ), Internal::ToSimd( epsilon ) );
    }

    /// <summary>
    /// Determines whether all the elements of lhs and their corresponding element of rhs are 
    /// less or equally apart than the value of epsilon.
    /// </summary>
    /// <param name="lhs">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="rhs">
    /// The second source of values for the comparison.
    /// </param>
    /// <param name="epsilon">
    /// The maximum difference between the elements from lhs and rhs.
    /// </param>
    /// <returns>
    /// true if all the elements of lhs and the corresponding elements of rhs are less
    /// or equally apart than the value of epsilon, otherwise false. 
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline bool AllEqual( const S& lhs, const T& rhs, const U epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( epsilon ) ) );
    }

    ///
    // AnyEqual

    /// <summary>
    /// Determines whether any of the elements of lhs and their corresponding element of rhs are 
    /// less or equally apart than the corresponding element of epsilon.
    /// </summary>
    /// <param name="lhs">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="rhs">
    /// The second source of values for the comparison.
    /// </param>
    /// <param name="epsilon">
    /// The source of the maximum difference between the
    /// corresponding elements from lhs and rhs.
    /// </param>
    /// <returns>
    /// true if any of the elements of lhs and the corresponding elements of rhs are less
    /// or equally apart than the corresponding element of epsilon, otherwise false.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline bool AnyEqual( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AnyEqual( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ), Internal::ToSimd( epsilon ) );
    }

    /// <summary>
    /// Determines whether any of the elements of lhs and their corresponding element of rhs are 
    /// less or equally apart than the value of epsilon.
    /// </summary>
    /// <param name="lhs">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="rhs">
    /// The second source of values for the comparison.
    /// </param>
    /// <param name="epsilon">
    /// The maximum difference between the elements from lhs and rhs.
    /// </param>
    /// <returns>
    /// true if any of the elements of lhs and the corresponding elements of rhs are less
    /// or equally apart than the value of epsilon, otherwise false. 
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline bool AnyEqual( const S& lhs, const T& rhs, U epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AnyEqual( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( epsilon ) ) );
    }


    // Equal

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
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Equal( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Equal( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether the elements of v1 are equal to value.
    /// </summary>
    /// <returns>
    /// If an element of v1 is equal to value, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto Equal( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Equal( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) ) );
    }

    /// <summary>
    /// Determines whether value is equal to the elements of v2.
    /// </summary>
    /// <returns>
    /// If value is equal to an element of v2, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto Equal( const T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Equal( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) ) );
    }


    /// <summary>
    /// Determines whether all the elements of v1 are equal to 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if all the elements of v1 is equal to their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AllEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are equal to value.
    /// </summary>
    /// <returns>
    /// true if all the elements of v1 is equal to value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AllEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is equal to all the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is equal to all the elements of v2, otherwise false.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline bool AllEqual( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }

    // AnyEqual

    /// <summary>
    /// Determines whether any of the elements of v1 are equal to 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if any of the elements of v1 is equal to their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AnyEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether any of the elements of v1 are equal to value.
    /// </summary>
    /// <returns>
    /// true if any of the elements of v1 is equal to value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AnyEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is equal to any of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is equal to any of the elements of v2, otherwise false.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline bool AnyEqual( const T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }

    // NotEqual

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
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto NotEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::NotEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether the elements of v1 are not equal to value.
    /// </summary>
    /// <returns>
    /// If an element of v1 is not equal to value, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto NotEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::NotEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) ) );
    }

    /// <summary>
    /// Determines whether value is not equal to the elements of v2.
    /// </summary>
    /// <returns>
    /// If value is not equal to an element of v2, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto NotEqual( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::NotEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are not equal to 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if all the elements of v1 is not equal to their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AllNotEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllNotEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are not equal to value.
    /// </summary>
    /// <returns>
    /// true if all the elements of v1 is not equal to value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AllNotEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllNotEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is not equal to all the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is not equal to all the elements of v2, otherwise false.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline bool AllNotEqual( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllNotEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }

    // AnyNotEqual

    /// <summary>
    /// Determines whether any of the elements of v1 are not equal to 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if any of the elements of v1 is not equal to their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AnyNotEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyNotEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether any of the elements of v1 are not equal to value.
    /// </summary>
    /// <returns>
    /// true if any of the elements of v1 is not equal to value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AnyNotEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyNotEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is not equal to any of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is not equal to any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AnyNotEqual( const T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyNotEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }




    // GreaterOrEqual

    /// <summary>
    /// Determines whether the elements of v1 are greater than, or equal to, 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// If an element of v1 is greater than, or equal to, the corresponding element of v2,
    /// the corresponding element in the result will be set to 0xFFFFFFFF,
    /// otherwise the corresponding element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto GreaterOrEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::GreaterOrEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether the elements of v1 are greater than, or equal to, value.
    /// </summary>
    /// <returns>
    /// If an element of v1 is greater than, or equal to, value, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto GreaterOrEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::GreaterOrEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) ) );
    }

    /// <summary>
    /// Determines whether value is greater than, or equal to, the elements of v2.
    /// </summary>
    /// <returns>
    /// If value is greater than, or equal to, an element of v2, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto GreaterOrEqual( const T value, const U& v2 ) noexcept
    {
        using Traits = typename U::Traits;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::GreaterOrEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are greater than, or equal to, 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if all the elements of v1 is greater than, or equal to, their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AllGreaterOrEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllGreaterOrEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are greater than, or equal to, value.
    /// </summary>
    /// <returns>
    /// true if all the elements of v1 is greater than, or equal to, value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AllGreaterOrEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllGreaterOrEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is greater than, or equal to, all of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is greater than, or equal to, any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AllGreaterOrEqual( const T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllGreaterOrEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }


    /// <summary>
    /// Determines whether any of the elements of v1 are greater than, or equal to, 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if any of the elements of v1 is greater than, or equal to, their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AnyGreaterOrEqual( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyGreaterOrEqual( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether any of the elements of v1 are greater than, or equal to, value.
    /// </summary>
    /// <returns>
    /// true if any of the elements of v1 is greater than, or equal to, value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AnyGreaterOrEqual( const T& v1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyGreaterOrEqual( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is greater than, or equal to, any of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is greater than, or equal to, any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AnyGreaterOrEqual( const T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyGreaterOrEqual( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }



    // Greater

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
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Greater( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Greater( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether the elements of v1 are greater than value.
    /// </summary>
    /// <returns>
    /// If an element of v1 is greater than value, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto Greater( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Greater( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) ) );
    }

    /// <summary>
    /// Determines whether value is greater than the elements of v2.
    /// </summary>
    /// <returns>
    /// If value is greater than an element of v2, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto Greater( T value, const U& v2 ) noexcept
    {
        using Traits = typename U::Traits;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Greater( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are greater than 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if all the elements of v1 is greater than their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AllGreater( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllGreater( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are greater than value.
    /// </summary>
    /// <returns>
    /// true if all the elements of v1 is greater than value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AllGreater( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllGreater( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is greater than all of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is greater than any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AllGreater( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllGreater( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }


    /// <summary>
    /// Determines whether any of the elements of v1 are greater than 
    /// the corresponding elements of v2.
    /// </summary>
    /// <param name="v1">
    /// The first source of values for the comparison.
    /// </param>
    /// <param name="v2">
    /// The second source of values for the comparison.
    /// </param>
    /// <returns>
    /// true if any of the elements of v1 is greater than their corresponding 
    /// element in v2, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline bool AnyGreater( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyGreater( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) );
    }

    /// <summary>
    /// Determines whether any of the elements of v1 are greater than value.
    /// </summary>
    /// <returns>
    /// true if any of the elements of v1 is greater than value, otherwise false.
    /// </returns>
    template<SimdOrTupleType T, ArithmeticType U>
    inline bool AnyGreater( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyGreater( Internal::ToSimd( v1 ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ) );
    }

    /// <summary>
    /// Determines whether value is greater than any of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is greater than any of the elements of v2, otherwise false.
    /// </returns>
    template< ArithmeticType T, SimdOrTupleType U>
    inline bool AnyGreater( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyGreater( Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( value ) ), Internal::ToSimd( v2 ) );
    }


    // Select

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
    /// the corresponding element in the result will be from v1, if an element control is 
    /// 0xFFFFFFFF, the corresponding element in the result will be from v2.
    /// </param>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline S Select( const S& v1, const T& v2, const U& control ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Select( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ), Internal::ToSimd( control ) ) );
    }


    /// <summary>
    /// Determines which of the elements of t are NaN. 
    /// </summary>
    /// <param name="t">
    /// The source of the values for the test.
    /// </param>
    /// <returns>
    /// If an element of t is NaN, the corresponding element in the 
    /// result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T>
    inline auto IsNaN( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::IsNaN( Internal::ToSimd( t ) ) );
    }

    /// <summary>
    /// Determines which of the elements of t are Inf. 
    /// </summary>
    /// <param name="t">
    /// The source of the values for the test.
    /// </param>
    /// <returns>
    /// If an element of t is Inf, the corresponding element in the 
    /// result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<SimdOrTupleType T>
    inline auto IsInf( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::IsInf( Internal::ToSimd( t ) ) );
    }


    // Abs

    /// <summary>
    /// Computes the absolute value of each element held by the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Abs( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            return T( Abs( t.x ), Abs( t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Abs( Internal::ToSimd( t ) ) );
        }
    }

    // FastAbs

    /// <summary>
    /// Computes the absolute value of each element held by the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto FastAbs( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            return T( FastAbs( t.x ), FastAbs( t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::FastAbs( Internal::ToSimd( t ) ) );
        }
    }


    // Min

    /// <summary>
    /// Makes a comparison between the elements held by the two arguments, and 
    /// returns a TupleSimd derived object containing the smallest elements.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Min( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && TupleType<U> && T::Size < 3 )
        {
            return T( Min( lhs.x, rhs.x ), Min( lhs.y, rhs.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Min( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ) ) );
        }
    }

    // Max

    /// <summary>
    /// Makes a comparison between the elements held by the two arguments, and 
    /// returns a TupleSimd containing the largest elements.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Max( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && TupleType<U> && T::Size < 3 )
        {
            return T( Max( lhs.x, rhs.x ), Max( lhs.y, rhs.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Max( Internal::ToSimd( lhs ), Internal::ToSimd( rhs ) ) );
        }
    }

    // Sqr

    /// <summary>
    /// Computes the square value of each element held by the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Sqr( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            return T( Sqr( t.x ), Sqr( t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            if constexpr ( SimdType<T> )
            {
                const auto& simd = Internal::ToSimd( t );
                return ResultType( Traits::Mul( simd, simd ) );

            }
            else
            {
                const auto simd = Internal::ToSimd( t );
                return ResultType( Traits::Mul( simd, simd ) );
            }
        }
    }

    // Ceil


    /// <summary>
    /// Computes the ceiling of each element held by the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Ceil( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            return T( Ceil( t.x ), Ceil( t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Ceil( Internal::ToSimd( t ) ) );
        }
    }

    // Floor

    /// <summary>
    /// Computes the floor of each element held by the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Floor( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            return T( Floor( t.x ), Floor( t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Floor( Internal::ToSimd( t ) ) );
        }
    }


    // Round

    /// <summary>
    /// Rounds each element held by the argument towards the nearest even integer.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Round( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            return T( Round( t.x ), Round( t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Round( Internal::ToSimd( t ) ) );
        }
    }

    // Trunc


    /// <summary>
    /// Rounds each element held by the argument to the nearest integer in the direction of zero.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Trunc( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            return T( Trunc( t.x ), Trunc( t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Truncate( Internal::ToSimd( t ) ) );
        }
    }

    // Lerp

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<SimdType T, SimdType U, ArithmeticType NumberT>
        requires IsCompatible<T, U>
    inline auto Lerp( const T& a, const U& b, NumberT t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Trim( Traits::Lerp( a.simd, b.simd, static_cast< Type >( t ) ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U, ArithmeticType NumberT>
        requires IsCompatible<T, U>&& Internal::HasTupleType<T, U>
    inline auto Lerp( const T& a, const U& b, NumberT t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        if constexpr ( TupleType<T> && TupleType<U> && T::Size < 3 )
        {
            return T( Lerp( a.x, b.x, static_cast< Type >( t ) ),
                Lerp( a.y, b.y, static_cast< Type >( t ) ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Trim( Traits::Lerp( Internal::ToSimd( a ), Internal::ToSimd( b ), static_cast< Type >( t ) ) ) );
        }
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<SimdType S, SimdType T, SimdType U>
        requires IsCompatible<S, T, U>
    inline auto Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::Trim( Traits::Lerp( a.simd, b.simd, t.simd ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>&& Internal::HasTupleType<S, T, U>
    inline auto Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && TupleType<U> && T::Size < 3 )
        {
            return T( Lerp( a.x, b.x, t.x ),
                Lerp( a.y, b.y, t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<S>;
            return ResultType( Traits::Trim( Traits::Lerp( Internal::ToSimd( a ), Internal::ToSimd( b ), Internal::ToSimd( t ) ) ) );
        }
    }



    /// <summary>
    /// Calculates the linear interpolation between a and b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<ArithmeticType NumberT1, ArithmeticType NumberT2, SimdOrTupleType T>
    inline auto Lerp( const NumberT1 a, const NumberT2 b, const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Trim( Traits::Lerp( Traits::Fill<T::Size>( static_cast< Type >( a ) ), Traits::Fill<T::Size>( static_cast< Type >( b ) ), Internal::ToSimd( t ) ) ) );
    }

    // Lerp2


    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<ArithmeticType S, SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto Lerp2( const S t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Trim( Traits::Lerp2( a.simd, b.simd, static_cast< Type >( t ) ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasTupleType<T, U>
    inline auto Lerp2( const S t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;

        if constexpr ( TupleType<T> && TupleType<U> && T::Size < 3 )
        {
            return T( Lerp2( static_cast< Type >( t ), a.x, b.x ),
                Lerp2( static_cast< Type >( t ), a.y, b.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Trim( Traits::Lerp2( Internal::ToSimd( a ), Internal::ToSimd( b ), static_cast< Type >( t ) ) ) );
        }
    }


    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<SimdType S, SimdType T, SimdType U>
        requires IsCompatible<S, T, U>
    inline auto Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::Trim( Traits::Lerp2( a.simd, b.simd, t.simd ) ) );
    }


    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>&& Internal::HasTupleType<S, T, U>
    inline auto Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        if constexpr ( TupleType<S> && TupleType<T> && S::Size < 3 )
        {
            return S( Lerp( a.x, b.x, t.x ),
                Lerp( a.y, b.y, t.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<S>;
            return ResultType( Traits::Trim( Traits::Lerp2( Internal::ToSimd( a ), Internal::ToSimd( b ), Internal::ToSimd( t ) ) ) );
        }
    }


    /// <summary>
    /// Calculates the linear interpolation between a and b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<SimdType S, ArithmeticType T, ArithmeticType U>
    inline auto Lerp2( const S& t, const T a, const U b ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::Trim( Traits::Lerp2( Traits::Fill<S::Size>( static_cast< Type >( a ) ), Traits::Fill<S::Size>( static_cast< Type >( b ) ), t.simd ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between a and b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<TupleType S, ArithmeticType T, ArithmeticType U>
    inline auto Lerp2( const S& t, const T a, const U b ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;

        if constexpr ( S::Size == 2 )
        {
            return S(
                Lerp2( t.x, static_cast< Type >( a ), static_cast< Type >( b ) ),
                Lerp2( t.y, static_cast< Type >( a ), static_cast< Type >( b ) ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<S>;
            return ResultType( Traits::Trim( Traits::Lerp2( Traits::Fill<S::Size>( static_cast< Type >( a ) ), Traits::Fill<S::Size>( static_cast< Type >( b ) ), Internal::ToSimd( t ) ) ) );
        }
    }

    // Permute

    template<int shuffleMask, SimdOrTupleType T>
    inline T Permute( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Permute<shuffleMask>( Internal::ToSimd( t ) ) );
    }

    // Clamp

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified by the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<SimdType S, SimdType T, SimdType U>
        requires IsCompatible<S, T, U>
    inline auto Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename S::Traits;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd ) );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified by the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>&& Internal::HasTupleType<S, T, U>
    inline auto Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename S::Traits;
        if constexpr ( TupleType<S> && TupleType<T> && TupleType<U> && S::Size < 3 )
        {
            return S( Clamp( v.x, lowerBounds.x, upperBounds.x ),
                Clamp( v.y, lowerBounds.y, upperBounds.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<S>;
            return ResultType( Traits::Clamp( Internal::ToSimd( v ), Internal::ToSimd( lowerBounds ), Internal::ToSimd( upperBounds ) ) );
        }
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified by lowerBounds and upperBounds, 
    /// otherwise the value of nearest boundary is returned.
    /// </summary>
    template<SimdType S, ArithmeticType T, ArithmeticType U>
    inline auto Clamp( const S& v, const T lowerBounds, const U upperBounds ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::Clamp( v.simd, Traits::Fill<S::Size>( static_cast< Type >( lowerBounds ) ), Traits::Fill<S::Size>( static_cast< Type >( upperBounds ) ) ) );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified by lowerBounds and upperBounds, 
    /// otherwise the value of nearest boundary is returned.
    /// </summary>
    template<TupleType S, ArithmeticType T, ArithmeticType U>
    inline auto Clamp( const S& v, const T lowerBounds, const U upperBounds ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = typename Traits::Type;
        if constexpr ( TupleType<S> && S::Size < 3 )
        {
            return S( Clamp( v.x, static_cast< Type >( lowerBounds ), static_cast< Type >( upperBounds ) ),
                Clamp( v.y, static_cast< Type >( lowerBounds ), static_cast< Type >( upperBounds ) ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<S>;
            return ResultType( Traits::Clamp( Traits::Load( v.values ), Traits::Fill<S::Size>( static_cast< Type >( lowerBounds ) ), Traits::Fill<S::Size>( static_cast< Type >( upperBounds ) ) ) );
        }
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified by the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Clamp( const S v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        if constexpr ( TupleType<T> && TupleType<U> && T::Size < 3 )
        {
            return S( Clamp( static_cast< Type >( v ), lowerBounds.x, upperBounds.x ),
                Clamp( static_cast< Type >( v ), lowerBounds.y, upperBounds.y ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Clamp( Traits::Fill<T::Size>( static_cast< Type >( v ) ), Internal::ToSimd( lowerBounds ), Internal::ToSimd( upperBounds ) ) );
        }
    }


    template<SimdOrTupleType S>
    inline auto ClampZero( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::Max( Traits::Zero( ), Internal::ToSimd( v ) ) );
    }


    /// <summary>
    /// Detects if the elements of a vector are within bounds.
    /// </summary>
    /// <param name="v">
    /// The elements to test against the bounds.
    /// </param>
    /// <param name="bounds">
    /// The bounds
    /// </param>
    /// <returns>
    /// An element in the result will have all bits set if
    /// the corresponding element of v are greater or
    /// equal to the corresponding negated value from bounds,
    /// and less or equal to the corresponding value from bounds,
    /// otherwise the element will be set to 0.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T>
        requires IsCompatible<S, T>
    inline auto InBounds( const S& v, const T& bounds ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::InBounds( Internal::ToSimd( v ), Internal::ToSimd( bounds ) ) );
    }


    // ClampLength

    namespace Internal
    {
        template<SimdType S, SimdType T, SimdType U>
            requires IsCompatible<S, T, U>
        inline S ClampLengthImpl( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
        {
            using Traits = typename S::Traits;
            using Simd = S;

            auto lengthSquared = LengthSquared( v );

            const auto zero = Traits::Zero( );
            typename Traits::SIMDType infinity = { { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } };

            auto reciprocalLength = ReciprocalSqrt( lengthSquared );

            auto infiniteLength = Traits::SameValue( lengthSquared.simd, infinity );
            auto zeroLength = Traits::Equal( lengthSquared.simd, zero );

            auto normal = Traits::Mul( v.simd, reciprocalLength.simd );

            auto length = Traits::Mul( lengthSquared.simd, reciprocalLength.simd );

            auto select = Traits::SameValue( infiniteLength, zeroLength );
            length = Traits::Select( lengthSquared.simd, length, select );
            normal = Traits::Select( lengthSquared.simd, normal, select );

            auto controlMax = Traits::Greater( length, lengthMax.simd );
            auto controlMin = Traits::Less( length, lengthMin.simd );

            auto clampLength = Traits::Select( length, lengthMax.simd, controlMax );
            clampLength = Traits::Select( clampLength, lengthMin.simd, controlMin );

            auto result = Traits::Mul( normal, clampLength );


            select = Traits::SameValue( controlMax, controlMin );
            return Simd( Traits::Trim( Traits::Select( result, v.simd, select ) ) );
        }
    }

    /// <summary>
    /// Clamps the length of a vector to a given range.
    /// </summary>
    /// <param name="v">
    /// vector to clamp.
    /// </param>
    /// <param name="lengthMin">
    /// A vector whose elements are equal to the minimum clamp length. 
    /// The elements must be greater-than-or-equal to zero.
    /// </param>
    /// <param name="lengthMax">
    /// A vector whose elements are equal to the maximum clamp length. 
    /// The elements must be greater-than-or-equal to zero.
    /// </param>
    /// <returns>
    /// Returns a vector whose length is clamped to the specified 
    /// minimum and maximum.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline auto ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
    {
        return Internal::ClampLengthImpl( Internal::ToSimdType( v ), Internal::ToSimdType( lengthMin ), Internal::ToSimdType( lengthMax ) );
    }
    /// <summary>
    /// Clamps the length of a vector to a given range.
    /// </summary>
    /// <param name="v">
    /// vector to clamp.
    /// </param>
    /// <param name="lengthMin">
    /// Minimum clamp length.
    /// </param>
    /// <param name="lengthMax">
    /// Maximum clamp length.
    /// </param>
    /// <returns>
    /// Returns a vector whose length is clamped to the specified 
    /// minimum and maximum.
    /// </returns>
    template<SimdOrTupleType S, ArithmeticType T, ArithmeticType U>
    inline auto ClampLength( const S& v, const T lengthMin, const U lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = typename Traits::Type;
        using Simd = typename S::Simd;

        return Internal::ClampLengthImpl( Internal::ToSimdType( v ), Simd( Traits::Fill<Traits::Size>( static_cast< Type >( lengthMin ) ) ), Simd( Traits::Fill<Traits::Size>( static_cast< Type >( lengthMax ) ) ) );
    }

    namespace Internal
    {
        /// <summary>
        /// Reflects an incident vector across a normal vector.
        /// </summary>
        /// <param name="incident">
        /// Incident vector to reflect.
        /// </param>
        /// <param name="normal">
        /// Normal vector to reflect the incident vector across.
        /// </param>
        /// <returns>
        /// The reflected incident angle.
        /// </returns>
        template<SimdType S, SimdType T>
            requires IsCompatible<S, T>
        inline S ReflectImpl( const S& incident, const T& normal ) noexcept
        {
            using Traits = typename S::Traits;
            using Simd = S;

            auto result = Traits::Dot( incident.simd, normal.simd );
            result = Traits::Add( result, result );
            return Simd( Traits::FNMSub( result, normal.simd, incident.simd ) );
        }
    }
    /// <summary>
    /// Reflects an incident vector across a normal vector.
    /// </summary>
    /// <param name="incident">
    /// Incident vector to reflect.
    /// </param>
    /// <param name="normal">
    /// Normal vector to reflect the incident vector across.
    /// </param>
    /// <returns>
    /// The reflected incident angle.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T>
        requires IsCompatible<S, T>
    inline auto Reflect( const S& incident, const T& normal ) noexcept
    {
        return Internal::ReflectImpl( Internal::ToSimdType( incident ), Internal::ToSimdType( normal ) );
    }

    namespace Internal
    {
        /// <summary>
        /// Refracts an incident vector across a normal vector.
        /// </summary>
        /// <param name="incident">
        /// The incident vector to refract.
        /// </param>
        /// <param name="normal">
        /// The normal vector to refract the incident vector through.
        /// </param>
        /// <param name="refractionIndex">
        /// A vector whose elements are equal to the index of refraction.
        /// </param>
        /// <returns>
        /// Returns the refracted incident vector. If the refraction index 
        /// and the angle between the incident vector and the normal are such 
        /// that the result is a total internal reflection, the function will 
        /// return a vector with all elements set to zero.
        /// </returns>
        template<SimdType S, SimdType T, SimdType U>
            requires IsCompatible<S, T, U>
        inline S RefractImpl( const S& incident, const T& normal, const U& refractionIndex ) noexcept
        {
            using Traits = typename S::Traits;
            using FloatT = typename Traits::Type;
            using SIMDType = typename Traits::SIMDType;
            using Simd = S;

            constexpr SIMDType zero = { {static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. )} };
            constexpr SIMDType one = { {static_cast< FloatT >( 1. ),static_cast< FloatT >( 1. ),static_cast< FloatT >( 1. ),static_cast< FloatT >( 1. )} };

            auto rmm1 = Traits::Dot( incident.simd, normal.simd );

            auto rmm2 = Traits::FNMAdd( rmm1, rmm1, one );
            auto rmm3 = Traits::Mul( refractionIndex.simd, refractionIndex.simd );
            rmm2 = Traits::FNMAdd( rmm2, rmm3, one );

            auto zeroSelect = Traits::LessOrEqual( rmm2, zero );

            rmm2 = Traits::Sqrt( rmm2 );
            rmm2 = Traits::FMAdd( refractionIndex.simd, rmm1, rmm2 );

            auto result = Traits::Mul( refractionIndex.simd, incident.simd );
            result = Traits::FNMAdd( rmm2, normal.simd, result );
            return Simd( Traits::Select( result, zero, zeroSelect ) );
        }
    }

    /// <summary>
    /// Refracts an incident vector across a normal vector.
    /// </summary>
    /// <param name="incident">
    /// The incident vector to refract.
    /// </param>
    /// <param name="normal">
    /// The normal vector to refract the incident vector through.
    /// </param>
    /// <param name="refractionIndex">
    /// A vector whose elements are equal to the index of refraction.
    /// </param>
    /// <returns>
    /// Returns the refracted incident vector. If the refraction index 
    /// and the angle between the incident vector and the normal are such 
    /// that the result is a total internal reflection, the function will 
    /// return a vector with all elements set to zero.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline auto Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
    {
        return Internal::RefractImpl( Internal::ToSimdType( incident ), Internal::ToSimdType( normal ), Internal::ToSimdType( refractionIndex ) );
    }

    /// <summary>
    /// Refracts an incident vector across a normal vector.
    /// </summary>
    /// <param name="incident">
    /// The incident vector to refract.
    /// </param>
    /// <param name="normal">
    /// The normal vector to refract the incident vector through.
    /// </param>
    /// <param name="refractionIndex">
    /// The index of refraction.
    /// </param>
    /// <returns>
    /// Returns the refracted incident vector. If the refraction index 
    /// and the angle between the incident vector and the normal are such 
    /// that the result is a total internal reflection, the function will 
    /// return a vector with all elements set to zero.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline auto Refract( const S& incident, const T& normal, const U refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = typename Traits::Type;
        using Simd = typename S::Simd;

        return Internal::RefractImpl( Internal::ToSimdType( incident ), Internal::ToSimdType( normal ), Simd( static_cast< Type >( refractionIndex ) ) );
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
    template<SimdOrTupleType S>
    inline auto Orthogonal( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        using ResultType = Internal::MakeResultType<S>;

        return ResultType( Traits::Orthogonal( Internal::ToSimd( v ) ) );
    }

    // Saturate

    /// <summary>
    /// Saturates the elements of v to the range 0.0 to 1.0.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Saturate( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Saturate( Internal::ToSimd( v ) ) );
    }

    // Sqrt

    /// <summary>
    /// Calculates the square root of each element in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Sqrt( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            using ResultType = T;
            return ResultType( Traits::ToArray( Traits::Sqrt( Internal::ToSimd( v ) ) ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Sqrt( Internal::ToSimd( v ) ) );
        }
    }

    // Cbrt

    /// <summary>
    /// Calculates the cube root of each element in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Cbrt( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            using ResultType = T;
            return ResultType( Traits::ToArray( Traits::Cbrt( Internal::ToSimd( v ) ) ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Cbrt( Internal::ToSimd( v ) ) );
        }
    }


    // SafeSqrt

    /// <summary>
    /// Calculates the square root of each element greater or 
    /// equal to 0.f in the argument. For elements less than 
    /// 0.f, the result is 0.f.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto SafeSqrt( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            using ResultType = T;
            return ResultType( Traits::ToArray( Traits::Sqrt( Traits::Max( Traits::Zero( ), Internal::ToSimd( v ) ) ) ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Sqrt( Traits::Max( Traits::Zero( ), Internal::ToSimd( v ) ) ) );
        }
    }

    // ReciprocalSqrt


    /// <summary>
    /// Calculates the reciprocal square root of each element in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ReciprocalSqrt( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            using ResultType = T;
            return ResultType( Traits::ToArray( Traits::Div( Traits::Fill<Traits::Size>( Constants<Type>::One ), Traits::Sqrt( Internal::ToSimd( v ) ) ) ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Div( Traits::Fill<Traits::Size>( Constants<Type>::One ), Traits::Sqrt( Internal::ToSimd( v ) ) ) );
        }
    }

    // Reciprocal

    /// <summary>
    /// Calculates the reciprocal of each element in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Reciprocal( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        if constexpr ( TupleType<T> && T::Size < 3 )
        {
            using ResultType = T;
            return ResultType( static_cast< Type >( 1 ) / t.x, static_cast< Type >( 1 ) / t.y );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Div( Traits::Fill<Traits::Size>( Constants<Type>::One ), Internal::ToSimd( t ) ) );
        }
    }

    // FMA

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, SimdType T, SimdType U>
        requires IsCompatible<S, T, U>
    inline auto FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAdd( a.simd, b.simd, c.simd ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>&& Internal::HasTupleType<S, T, U>
    inline auto FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAdd( Internal::ToSimd( a ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline auto FMA( const S& a, const T& b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAdd( Internal::ToSimd( a ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, SimdOrTupleType U>
        requires IsCompatible<S, U>
    inline auto FMA( const S& a, const T b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAdd( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );

    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, ArithmeticType U>
    inline auto FMA( const S& a, const T b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAdd( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto FMA( const S a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, ArithmeticType U>
    inline auto FMA( const S a, const T& b, const U c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<ArithmeticType S, ArithmeticType T, SimdOrTupleType U>
    inline auto FMA( const S a, const T b, const U& c ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::FMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Evaluates the provided polynomial using Horner’s method
    /// </summary>

    template <SimdType T, typename C>
        requires IsArithmetic<C>
    constexpr inline T EvaluatePolynomial( const T& t, C c )
    {
        using Traits = typename T::Traits;
        return Traits::Fill<Traits::Size>( c );
    }
    template <SimdType T, SimdType C>
        requires IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, C c )
    {
        return c;
    }

    template <SimdType T, typename C, typename... Args>
        requires IsArithmetic<C>
    constexpr inline T EvaluatePolynomial( const T& t, C c, Args... remaining );

    template <TupleType T, typename C, typename... Args>
        requires IsArithmetic<C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, C c, Args... remaining );

    template <SimdType T, SimdType C, typename... Args>
        requires IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, const C& c, Args... remaining );

    template <TupleType T, SimdType C, typename... Args>
        requires IsCompatible<T, C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, const C& c, Args... remaining );

    template <SimdType T, TupleType C, typename... Args>
        requires IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, const C& c, Args... remaining );

    template <TupleType T, TupleType C, typename... Args>
        requires IsCompatible<T, C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, const C& c, Args... remaining );


    template <SimdType T, typename C, typename... Args>
        requires IsArithmetic<C>
    constexpr inline T EvaluatePolynomial( const T& t, C c, Args... remaining )
    {
        using Traits = typename T::Traits;
        return FMA( t, EvaluatePolynomial( t, remaining... ), T( Traits::Fill<Traits::Size>( c ) ) );
    }

    template <TupleType T, typename C, typename... Args>
        requires IsArithmetic<C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, C c, Args... remaining )
    {
        using Traits = typename T::Traits;
        using SimdType = typename T::Simd;
        SimdType tSimd( t );
        return FMA( tSimd, EvaluatePolynomial( tSimd, remaining... ), SimdType( Traits::Fill<Traits::Size>( c ) ) );
    }

    template <SimdType T, SimdType C, typename... Args>
        requires IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, const C& c, Args... remaining )
    {
        using Traits = typename T::Traits;
        return FMA( t, EvaluatePolynomial( t, remaining... ), c );
    }

    template <TupleType T, SimdType C, typename... Args>
        requires IsCompatible<T, C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, const C& c, Args... remaining )
    {
        using Traits = typename T::Traits;
        using SimdType = typename T::Simd;
        SimdType tSimd( t );
        return FMA( tSimd, EvaluatePolynomial( tSimd, remaining... ), c );
    }

    template <SimdType T, TupleType C, typename... Args>
        requires IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, const C& c, Args... remaining )
    {
        using Traits = typename T::Traits;
        using SimdType = typename C::Simd;
        SimdType cSimd( c );
        return FMA( t, EvaluatePolynomial( t, remaining... ), cSimd );
    }
    template <TupleType T, TupleType C, typename... Args>
        requires IsCompatible<T, C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, const C& c, Args... remaining )
    {
        using Traits = typename T::Traits;
        using TSimdType = typename T::Simd;
        using CSimdType = typename C::Simd;
        TSimdType tSimd( t );
        CSimdType cSimd( c );
        return FMA( tSimd, EvaluatePolynomial( tSimd, remaining... ), cSimd );
    }



    // FMSub

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline auto FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMSub( Internal::ToSimd( a ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline auto FMSub( const S& a, const T& b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMSub( Internal::ToSimd( a ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, SimdOrTupleType U>
        requires IsCompatible<S, U>
    inline auto FMSub( const S& a, const T b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMSub( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, ArithmeticType U>
    inline auto FMSub( const S& a, const T b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMSub( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto FMSub( const S a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, ArithmeticType U>
    inline auto FMSub( const S a, const T& b, const U c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, ArithmeticType T, SimdOrTupleType U>
    inline auto FMSub( const S a, const T b, const U& c ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::FMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }


    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline auto FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAddSub( Internal::ToSimd( a ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline auto FMAddSub( const S& a, const T& b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAddSub( Internal::ToSimd( a ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, SimdOrTupleType U>
        requires IsCompatible<S, U>
    inline auto FMAddSub( const S& a, const T b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAddSub( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, ArithmeticType U>
    inline auto FMAddSub( const S& a, const T b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMAddSub( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto FMAddSub( const S a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMAddSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, ArithmeticType U>
    inline auto FMAddSub( const S a, const T& b, const U c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMAddSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, ArithmeticType T, SimdOrTupleType U>
    inline auto FMAddSub( const S a, const T b, const U& c ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::FMAddSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }


    // FMSubAdd

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline auto FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMSubAdd( Internal::ToSimd( a ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline auto FMSubAdd( const S& a, const T& b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMSubAdd( Internal::ToSimd( a ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, SimdOrTupleType U>
        requires IsCompatible<S, U>
    inline auto FMSubAdd( const S& a, const T b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMSubAdd( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, ArithmeticType U>
    inline auto FMSubAdd( const S& a, const T b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FMSubAdd( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto FMSubAdd( const S a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMSubAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, ArithmeticType U>
    inline auto FMSubAdd( const S a, const T& b, const U c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMSubAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<ArithmeticType S, ArithmeticType T, SimdOrTupleType U>
    inline auto FMSubAdd( const S a, const T b, const U& c ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::FMSubAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }

    // FNMAdd

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline auto FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FNMAdd( Internal::ToSimd( a ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline auto FNMAdd( const S& a, const T& b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FNMAdd( Internal::ToSimd( a ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, SimdOrTupleType U>
        requires IsCompatible<S, U>
    inline auto FNMAdd( const S& a, const T b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FNMAdd( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, ArithmeticType U>
    inline auto FNMAdd( const S& a, const T b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FNMAdd( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto FNMAdd( const S a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FNMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, ArithmeticType U>
    inline auto FNMAdd( const S a, const T& b, const U c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FNMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<ArithmeticType S, ArithmeticType T, SimdOrTupleType U>
    inline auto FNMAdd( const S a, const T b, const U& c ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::FNMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }

    // FNMSub

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U>
    inline auto FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FNMSub( Internal::ToSimd( a ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<SimdOrTupleType S, SimdOrTupleType T, ArithmeticType U>
        requires IsCompatible<S, T>
    inline auto FNMSub( const S& a, const T& b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FNMSub( Internal::ToSimd( a ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, SimdOrTupleType U>
        requires IsCompatible<S, U>
    inline auto FNMSub( const S& a, const T b, const U& c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FNMSub( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<SimdOrTupleType S, ArithmeticType T, ArithmeticType U>
    inline auto FNMSub( const S& a, const T b, const U c ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<S>;
        return ResultType( Traits::FNMSub( Internal::ToSimd( a ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto FNMSub( const S a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FNMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Internal::ToSimd( c ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<ArithmeticType S, SimdOrTupleType T, ArithmeticType U>
    inline auto FNMSub( const S a, const T& b, const U c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FNMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Internal::ToSimd( b ), Traits::Fill<Traits::Size>( static_cast< Type >( c ) ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<ArithmeticType S, ArithmeticType T, SimdOrTupleType U>
    inline auto FNMSub( const S a, const T b, const U& c ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::FNMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Internal::ToSimd( c ) ) );
    }


    // Sin

    /// <summary>
    /// Calculates the sine of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Sin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Sin( Internal::ToSimd( v ) ) );
    }

    // FastSin

    /// <summary>
    /// Calculates the sine of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto FastSin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FastSin( Internal::ToSimd( v ) ) );
    }

    // Cos

    /// <summary>
    /// Calculates the cosine of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Cos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Cos( Internal::ToSimd( v ) ) );
    }

    // FastCos

    /// <summary>
    /// Calculates the cosine of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto FastCos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FastCos( Internal::ToSimd( v ) ) );
    }

    // SinCos

    /// <summary>
    /// Calculates the sine and cosine of each element in the argument expressed in radians.
    /// </summary>
    template<SimdType T>
    inline T SinCos( const T& v, T* cosines ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::SinCos( v.simd, &cosines->simd );
    }

    /// <summary>
    /// Calculates the sine and cosine of each element in the argument expressed in radians.
    /// </summary>
    template<TupleType T>
    inline typename T::Simd SinCos( const T& v, typename T::Simd* cosines ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::SinCos( Traits::Load( v.values ), &cosines->simd );
    }

    // FastSinCos

    /// <summary>
    /// Calculates the sine and cosine of each element in the argument expressed in radians.
    /// </summary>
    template<SimdType T>
    inline T FastSinCos( const T& v, T* cosines ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastSinCos( v.simd, &cosines->simd );
    }

    /// <summary>
    /// Calculates the sine and cosine of each element in the argument expressed in radians.
    /// </summary>
    template<TupleType T>
    inline typename T::Simd FastSinCos( const T& v, typename T::Simd* cosines ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastSinCos( Traits::Load( v.values ), &cosines->simd );
    }

    // Tan

    /// <summary>
    /// Calculates the tangent of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Tan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Tan( Internal::ToSimd( v ) ) );
    }

    // FastTan

    /// <summary>
    /// Calculates the tangent of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto FastTan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FastTan( Internal::ToSimd( v ) ) );
    }

    // ASin

    /// <summary>
    /// Calculates the inverse sine of each element in the argument, in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ASin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::ASin( Internal::ToSimd( v ) ) );
    }

    // ACos

    /// <summary>
    /// Calculates the inverse cosine of each element in the argument, in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ACos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::ACos( Internal::ToSimd( v ) ) );
    }

    // ATan

    /// <summary>
    /// Calculates the inverse tangent of each element in the argument, in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ATan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::ATan( Internal::ToSimd( v ) ) );
    }

    // FastATan

    /// <summary>
    /// Calculates the inverse tangent of each element in the argument, in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto FastATan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FastATan( Internal::ToSimd( v ) ) );
    }

    // ATan2

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto ATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::ATan2( Internal::ToSimd( x ), Internal::ToSimd( y ) ) );
    }

    // FastATan2

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto FastATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FastATan2( Internal::ToSimd( x ), Internal::ToSimd( y ) ) );
    }


    namespace Internal
    {
        /// <summary>
        /// Calculates the angle modulo 2PI.
        /// </summary>
        /// <typeparam name="T">
        /// A TupleN SimdType 
        /// </typeparam>
        /// <param name="angles">
        /// The angles in radians
        /// </param>
        /// <returns>
        /// Returns a SimdType holding the angles modulo 2PI.
        /// </returns>
        template<SimdType T>
        inline T ModAnglesImpl( const T& angles )
        {
            using Traits = typename T::Traits;
            using FloatT = typename Traits::Type;

            auto result = Traits::Round( Traits::Mul( angles.simd, Traits::Fill<Traits::Size>( Constants<FloatT>::Inv2Pi ) ) );
            return Traits::FNMAdd( result, Traits::Fill<Traits::Size>( Constants<FloatT>::PiTimes2 ), angles.simd );
        }
    }
    /// <summary>
    /// Calculates the angle modulo 2PI.
    /// </summary>
    /// <typeparam name="T">
    /// A TupleN SimdType 
    /// </typeparam>
    /// <param name="angles">
    /// The angles in radians
    /// </param>
    /// <returns>
    /// Returns a SimdType holding the angles modulo 2PI.
    /// </returns>
    template<SimdOrTupleType T>
    inline auto ModAngles( const T& angles )
    {
        return Internal::ModAnglesImpl( Internal::ToSimdType( angles ) );
    }

    // AddAngles

    namespace Internal
    {
        /// <summary>
        /// Adds the angles in the corresponding elements of v1 and v2.
        /// The argument angles must be in the range [-PI,PI), and the
        /// computed angles will be in the range [-PI,PI) 
        /// </summary>
        template<SimdType T, SimdType U>
            requires IsCompatible<T, U>
        inline T AddAnglesImpl( const T& v1, const U& v2 ) noexcept
        {
            using Traits = typename T::Traits;
            using FloatT = typename Traits::Type;
            // Adjust the angles
            auto result = Traits::Add( v1.simd, v2.simd );
            // Less than Pi?
            auto offset = Traits::Less( result, Traits::Fill( Constants<FloatT>::NegativePi ) );
            offset = Traits::And( offset, Traits::Fill( Constants<FloatT>::PiTimes2 ) );
            // Add 2Pi to all entries less than -Pi
            result = Traits::Add( result, offset );
            // Greater than or equal to Pi?
            offset = Traits::GreaterOrEqual( result, Traits::Fill( Constants<FloatT>::Pi ) );
            offset = Traits::And( offset, Traits::Fill( Constants<FloatT>::PiTimes2 ) );
            // Sub 2Pi to all entries greater than Pi
            return Traits::Trim( Traits::Sub( result, offset ) );
        }
    }
    /// <summary>
    /// Adds the angles in the corresponding elements of v1 and v2.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto AddAngles( const T& v1, const U& v2 ) noexcept
    {
        return Internal::AddAnglesImpl( Internal::ToSimdType( v1 ), Internal::ToSimdType( v2 ) );
    }

    // SubtractAngles

    namespace Internal
    {
        /// <summary>
        /// Subtracts the angles in v2 from the corresponding elements of v1.
        /// The argument angles must be in the range [-PI,PI), and the
        /// computed angles will be in the range [-PI,PI) 
        /// </summary>
        template<SimdType T, SimdType U>
            requires IsCompatible<T, U>
        inline T SubtractAnglesImpl( const T& v1, const U& v2 ) noexcept
        {
            using Traits = typename T::Traits;
            using FloatT = typename Traits::Type;
            // Adjust the angles
            auto result = Traits::Sub( v1.simd, v2.simd );
            // Less than Pi?
            auto offset = Traits::Less( result, Traits::Fill( Constants<FloatT>::NegativePi ) );
            offset = Traits::And( offset, Traits::Fill( Constants<FloatT>::PiTimes2 ) );
            // Add 2Pi to all entries less than -Pi
            result = Traits::Add( result, offset );
            // Greater than or equal to Pi?
            offset = Traits::GreaterOrEqual( result, Traits::Fill( Constants<FloatT>::Pi ) );
            offset = Traits::And( offset, Traits::Fill( Constants<FloatT>::PiTimes2 ) );
            // Sub 2Pi to all entries greater than Pi
            return Traits::Trim( Traits::Sub( result, offset ) );
        }
    }
    /// <summary>
    /// Subtracts the angles in v2 from the corresponding elements of v1.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto SubtractAngles( const T& v1, const U& v2 ) noexcept
    {
        return Internal::SubtractAnglesImpl( Internal::ToSimdType( v1 ), Internal::ToSimdType( v2 ) );
    }


    // SinH

    /// <summary>
    /// Calculates the hyperbolic sine of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto SinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::SinH( Internal::ToSimd( v ) ) );
    }

    // CosH

    /// <summary>
    /// Calculates the hyperbolic cosine of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto CosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::CosH( Internal::ToSimd( v ) ) );
    }

    // TanH

    /// <summary>
    /// Calculates the hyperbolic tangent of each element in the argument expressed in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto TanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::TanH( Internal::ToSimd( v ) ) );
    }

    // ASinH

    /// <summary>
    /// Calculates the inverse hyperbolic sine of each element in the argument, in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ASinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::ASinH( Internal::ToSimd( v ) ) );
    }

    // ACosH

    /// <summary>
    /// Calculates the inverse hyperbolic cosine of each element in the argument, in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ACosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::ACosH( Internal::ToSimd( v ) ) );
    }

    // ATanH

    /// <summary>
    /// Calculates the inverse hyperbolic tangent of each element in the argument, in radians.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ATanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::ATanH( Internal::ToSimd( v ) ) );
    }

    // Log

    /// <summary>
    /// Calculates the natural logarithm of each element in the argument.
    /// </summary>
    template<SimdType T>
    inline auto Log( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Log( Internal::ToSimd( v ) ) );
    }

    /// <summary>
    /// Calculates the natural logarithm of each element in the argument.
    /// </summary>
    template<TupleType T>
    inline auto Log( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( T::Size == 2 )
        {
            return T( Log( v.x ), Log( v.y ) );
        }
        else if constexpr ( T::Size == 3 )
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Log( v.x ), Log( v.y ), Log( v.z ) );
        }
        else if constexpr ( T::Size == 4 )
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Log( v.x ), Log( v.y ), Log( v.z ), Log( v.w ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Log( Internal::ToSimd( v ) ) );
        }
    }


    // Log1P


    /// <summary>
    /// Calculates the natural logarithm of 1 + each element in the argument.
    /// </summary>
    template<SimdType T>
    inline auto Log1P( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Log1P( Internal::ToSimd( v ) ) );
    }

    /// <summary>
    /// Calculates the natural logarithm of 1 + each element in the argument.
    /// </summary>
    template<TupleType T>
    inline auto Log1P( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( T::Size == 2 )
        {
            return T( Log1P( v.x ), Log1P( v.y ) );
        }
        else if constexpr ( T::Size == 3 )
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Log1P( v.x ), Log1P( v.y ), Log1P( v.z ) );
        }
        else if constexpr ( T::Size == 4 )
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Log1P( v.x ), Log1P( v.y ), Log1P( v.z ), Log1P( v.w ) );
        }
        else
        {
            using ResultType = Internal::MakeResultType<T>;
            return ResultType( Traits::Log1P( Internal::ToSimd( v ) ) );
        }
    }


    // Log10

    /// <summary>
    /// Calculates the base-10 logarithm of each element in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Log10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Log10( Internal::ToSimd( v ) ) );
    }

    // Log2

    /// <summary>
    /// Calculates the base-2 logarithm, $$log_{2}_$$, of each element in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Log2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Log2( Internal::ToSimd( v ) ) );
    }

    // Exp

    /// <summary>
    /// Calculates  $$e$$ (Euler's number, 2.7182818...), raised to the power of each element in the argument.
    /// </summary>
    template<SimdType T>
    inline auto Exp( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        /*
        using Tuple = typename T::TupleType;
        if constexpr ( T::Size == 2 )
        {
            Tuple t( v );
            return ResultType( Exp( t.x ), Exp( t.y ) );
        }
        else if constexpr ( T::Size == 3 )
        {
            Tuple t( v );
            return ResultType( Exp( t.x ), Exp( t.y ), Exp( t.z ) );
        }
        else if constexpr ( T::Size == 4 )
        {
            Tuple t( v );
            return ResultType( Exp( t.x ), Exp( t.y ), Exp( t.z ), Exp( t.w ) );
        }
        else
        {
            return ResultType( Traits::Exp( v.simd ) );
        }
        */
        return ResultType( Traits::Exp( v.simd ) );
    }

    /// <summary>
    /// Calculates  $$e$$ (Euler's number, 2.7182818...), raised to the power of each element in the argument.
    /// </summary>
    template<TupleType T>
    inline auto Exp( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        if constexpr ( T::Size == 2 )
        {
            return T( Exp( v.x ), Exp( v.y ) );
        }
        else if constexpr ( T::Size == 3 )
        {
            return ResultType( Exp( v.x ), Exp( v.y ), Exp( v.z ) );
        }
        else if constexpr ( T::Size == 4 )
        {
            return ResultType( Exp( v.x ), Exp( v.y ), Exp( v.z ), Exp( v.w ) );
        }
        else
        {
            return ResultType( Traits::Exp( Internal::ToSimd( v ) ) );
        }
    }

    // Exp10

    /// <summary>
    /// Calculates the base-10 exponential of each element in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Exp10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Exp10( Internal::ToSimd( v ) ) );
    }

    // Exp2

    /// <summary>
    /// Calculates the base-2 exponential of each element in the argument.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Exp2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Exp2( Internal::ToSimd( v ) ) );
    }

    // ExpM1

    /// <summary>
    /// Calculates  $$e$$ (Euler's number, 2.7182818...), raised to the power of each element in the argument, $$-1.0$$.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ExpM1( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::ExpM1( Internal::ToSimd( v ) ) );
    }

    // Pow

    /// <summary>
    /// Calculates the elements in base raised to the corresponding element in exponent.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Pow( const T& base, const U& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Pow( Internal::ToSimd( base ), Internal::ToSimd( exponent ) ) );
    }

    /// <summary>
    /// Calculates the elements in base raised to the value of exponent.
    /// </summary>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto Pow( const T& base, const U exponent ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Pow( Internal::ToSimd( base ), Traits::Fill<Traits::Size>( static_cast< Type >( exponent ) ) ) );
    }

    /// <summary>
    /// Returns the value of base raised to the corresponding elements in exponent.
    /// </summary>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto Pow( const T& base, const U& exponent ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Pow( Traits::Fill<Traits::Size>( static_cast< Type >( base ) ), Internal::ToSimd( exponent ) ) );
    }

    namespace Internal
    {
        template<SimdType T>
        struct SimdFastPowImpl
        {
            using Traits = typename T::Traits;
            using ValueType = Traits::Type;
            template<int n>
            static constexpr inline T Pow( const T& v )
            {
                if constexpr ( n < 0 )
                {
                    return Traits::Div( Traits::Fill<Traits::Size>( Constants<ValueType>::One ), Pow<-n>( v ).simd );
                }
                auto n2 = Pow<n / 2>( v );
                return n2 * n2 * Pow<n & 1>( v );
            }

            template<>
            static constexpr inline T Pow<1>( const T& v )
            {
                return v;
            }
            template<>
            static constexpr inline T Pow<0>( const T& v )
            {
                return Traits::Fill<Traits::Size>( Constants<ValueType>::One );
            }
        };
    }

    template<int n, SimdType T>
    inline T FastPow( const T& v )
    {
        return Internal::SimdFastPowImpl<T>::Pow<n>( v );
    }

    template<int n, TupleType T>
    inline typename T::Simd FastPow( const T& v )
    {
        return Internal::SimdFastPowImpl<typename T::Simd>::Pow<n>( v );
    }



    // FMod

    /// <summary>
    /// Computes the floating-point remainder of the division operation $x/y$.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto FMod( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMod( Internal::ToSimd( x ), Internal::ToSimd( y ) ) );
    }

    /// <summary>
    /// Computes the floating-point remainder of the division operation $x/y$.
    /// </summary>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto FMod( const T& x, const U y ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::FMod( Internal::ToSimd( x ), Traits::FillDivisor<Traits::Size>( static_cast< Type >( y ) ) ) );
    }

    /// <summary>
    /// Computes the floating-point remainder of the division operation $x/y$.
    /// </summary>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto FMod( const T x, const U& y ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::FMod( Traits::Fill<Traits::Size>( static_cast< Type >( x ) ), Internal::ToSimd( y ) ) );
    }

    // Hypot

    /// <summary>
    /// Calculates the square root of the sum of the squares of each corresponding 
    /// element in x and y, without undue overflow or underflow at intermediate 
    /// stages of the computation.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Hypot( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Hypot( Internal::ToSimd( x ), Internal::ToSimd( y ) ) );
    }

    /// <summary>
    /// Calculates the square root of the sum of the squares of each corresponding 
    /// element in x and y, without undue overflow or underflow at intermediate 
    /// stages of the computation.
    /// </summary>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto Hypot( const T& x, const U y ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Hypot( Internal::ToSimd( x ), Traits::FillDivisor<Traits::Size>( static_cast< Type >( y ) ) ) );
    }

    /// <summary>
    /// Calculates the square root of the sum of the squares of each corresponding 
    /// element in x and y, without undue overflow or underflow at intermediate 
    /// stages of the computation.
    /// </summary>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto Hypot( const T x, const U& y ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Hypot( Traits::Fill<Traits::Size>( static_cast< Type >( x ) ), Internal::ToSimd( y ) ) );
    }

    // Hermite

    namespace Internal
    {
        /// <summary>
        /// Calculates the Hermite spline interpolation, using the specified arguments.
        /// </summary>
        template<SimdType T, SimdType U, SimdType V, SimdType W>
            requires IsCompatible<T, U, V, W>
        inline T HermiteImpl( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
        {
            using Traits = typename T::Traits;
            using FloatT = typename T::value_type;
            auto t2 = t * t;
            auto t3 = t * t2;

            auto p0 = Traits::Fill( static_cast< FloatT >( 2.0 ) * t3 - static_cast< FloatT >( 3.0 ) * t2 + static_cast< FloatT >( 1.0 ) );
            auto t0 = Traits::Fill( t3 - static_cast< FloatT >( 2.0 ) * t2 + t );
            auto p1 = Traits::Fill( static_cast< FloatT >( -2.0 ) * t3 + static_cast< FloatT >( 3.0 ) * t2 );
            auto t1 = Traits::Fill( t3 - t2 );

            auto result = Traits::Mul( p0, firstPosition.simd );
            result = Traits::FMAdd( firstTangent.simd, t0, result );
            result = Traits::FMAdd( secondPosition.simd, p1, result );
            return Traits::Trim( Traits::FMAdd( secondTangent.simd, t1, result ) );
        }
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U, SimdOrTupleType V, SimdOrTupleType W, ArithmeticType X>
        requires IsCompatible<T, U, V, W>
    inline auto Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, const X t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Internal::HermiteImpl( Internal::ToSimdType( firstPosition ), Internal::ToSimdType( firstTangent ), Internal::ToSimdType( secondPosition ), Internal::ToSimdType( secondTangent ), static_cast< Type >( t ) );
    }

    // Dot

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::Dot( v1.simd, v2.simd ) );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasSimdType<T, U>&& Internal::HasTupleType<T, U>
    inline auto Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Dot( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<SimdOrTupleType T, ArithmeticType U>
    inline auto Dot( const T& v1, const U v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Dot( Internal::ToSimd( v1 ), Traits::FillDivisor<Traits::Size>( static_cast< Type >( v2 ) ) ) );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<ArithmeticType T, SimdOrTupleType U>
    inline auto Dot( const T v1, const U& v2 ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Dot( Traits::Fill<Traits::Size>( static_cast< Type >( v1 ) ), Internal::ToSimd( v2 ) ) );
    }

    template<TupleType T, TupleType U>
        requires IsCompatible<T, U>
    constexpr inline typename T::Simd Dot( const T& v1, const U& v2 ) noexcept
    {
        using ResultType = typename T::Simd;
        if constexpr ( T::Size == 2 )
        {
            return ResultType( v1.x * v2.x + v1.y * v2.y );
        }
        else if constexpr ( T::Size == 3 )
        {
            return ResultType( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z );
        }
        else if constexpr ( T::Size == 4 )
        {
            return ResultType( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w );
        }
    }


    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<int mask, SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::Dot<mask>( v1.simd, v2.simd ) );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<int mask, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasSimdType<T, U>&& Internal::HasTupleType<T, U>
    inline auto Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Dot<mask>( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<int mask, SimdOrTupleType T, ArithmeticType U>
    inline auto Dot( const T& v1, const U v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Dot<mask>( Internal::ToSimd( v1 ), Traits::FillDivisor<Traits::Size>( static_cast< Type >( v2 ) ) ) );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<int mask, ArithmeticType T, SimdOrTupleType U>
    inline auto Dot( const T v1, const U& v2 ) noexcept
    {
        using Traits = typename U::Traits;
        using Type = typename Traits::Type;
        using ResultType = Internal::MakeResultType<U>;
        return ResultType( Traits::Dot<mask>( Traits::Fill<Traits::Size>( static_cast< Type >( v1 ) ), Internal::ToSimd( v2 ) ) );
    }

    // ScalarDot

    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Dot( v1, v2 ).simd );
    }

    template<TupleType T, SimdType U>
        requires IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Dot( v1, v2 ).simd );
    }

    template<SimdType T, TupleType U>
        requires IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Dot( v1, v2 ).simd );
    }

    template<TupleType T, TupleType U>
        requires IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return v1.x * v2.x + v1.y * v2.y;
        }
        else if constexpr ( T::Size == 3 )
        {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        }
        else if constexpr ( T::Size == 4 )
        {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
        }
    }


    // AbsDot

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto AbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Abs( Math::Dot( v1, v2 ).simd ) );
    }

    // ScalarAbsDot

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto ScalarAbsDot( const T& v1, const U& v2 ) noexcept
    {
        return Math::FastAbs( ScalarDot( v1, v2 ) );
    }

    // Cross

    /// <summary>
    /// Calculates the cross product between v1 and v2.
    /// </summary>
    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto Cross( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::Cross( v1.simd, v2.simd ) );
    }

    /// <summary>
    /// Calculates the cross product between v1 and v2.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasTupleType<T, U>
    inline auto Cross( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Cross( Internal::ToSimd( v1 ), Internal::ToSimd( v2 ) ) );
    }

    /// <summary>
    /// Calculates the normalized cross product between v1 and v2.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto UnitCross( const T& v1, const U& v2 ) noexcept
    {
        return Normalize( Cross( v1, v2 ) );
    }


    // LengthSquared

    /// <summary>
    /// Calculates the squared length of v.
    /// </summary>
    template<SimdType T>
    inline auto LengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = T;
        return ResultType( Traits::HSum( Traits::Mul( v.simd, v.simd ) ) );
    }

    /// <summary>
    /// Calculates the squared length of v.
    /// </summary>
    template<TupleType T>
    inline auto LengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;

        if constexpr ( T::Size == 2 )
        {
            return ResultType( v.x * v.x + v.y * v.y );
        }
        else if constexpr ( T::Size == 3 )
        {
            return ResultType( v.x * v.x + v.y * v.y + v.z * v.z );
        }
        else if constexpr ( T::Size == 4 )
        {
            return ResultType( v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w );
        }
    }


    // ScalarLengthSquared

    template<SimdType T>
    inline auto ScalarLengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::LengthSquared( v ).simd );
    }

    template<TupleType T>
    inline auto ScalarLengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        if constexpr ( T::Size == 2 )
        {
            return v.x * v.x + v.y * v.y;
        }
        else if constexpr ( T::Size == 3 )
        {
            return v.x * v.x + v.y * v.y + v.z * v.z;
        }
        else if constexpr ( T::Size == 4 )
        {
            return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
        }
    }


    // Length

    /// <summary>
    /// Calculates the length of v.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Length( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Sqrt( Math::LengthSquared( v ).simd ) );
    }

    // ScalarLength

    /// <summary>
    /// Calculates the length of v.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ScalarLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Length( v ).simd );
    }

    // Normalize

    /// <summary>
    /// Normalizes v.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto Normalize( const T& v ) noexcept
    {
        return v / Length( v );
    }


    // ReciprocalLength

    /// <summary>
    /// Calculates the reciprocal length of v.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ReciprocalLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        auto length = Length( v );
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Div( Traits::Fill<Traits::Size>( static_cast< Type >( 1. ) ), length.simd ) );
    }

    // ScalarReciprocalLength

    /// <summary>
    /// Calculates the reciprocal length of v.
    /// </summary>
    template<SimdOrTupleType T>
    inline auto ScalarReciprocalLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        auto length = ScalarLength( v );
        return static_cast< Type >( 1. ) / length;
    }

    // DistanceSquared

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    inline auto DistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( p1.simd, p2.simd );
        using ResultType = T;
        return ResultType( Traits::HSum( Traits::Mul( diff, diff ) ) );
    }

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasTupleType<T, U>
    inline auto DistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( Internal::ToSimd( p2 ), Internal::ToSimd( p1 ) );
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::HSum( Traits::Mul( diff, diff ) ) );
    }

    // ScalarDistanceSquared

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>&& Internal::HasSimdType<T, U>
    inline auto ScalarDistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( DistanceSquared( p1, p2 ).simd );
    }

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<TupleType T, TupleType U>
        requires IsCompatible<T, U>
    constexpr inline auto ScalarDistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Traits = typename T::Traits;
        if constexpr ( T::Size == 2 )
        {
            auto x = p2.x - p1.x;
            auto y = p2.y - p1.y;
            return x * x + y * y;
        }
        else if constexpr ( T::Size == 3 )
        {
            auto x = p2.x - p1.x;
            auto y = p2.y - p1.y;
            auto z = p2.z - p1.z;
            return x * x + y * y + z * z;
        }
        else if constexpr ( T::Size == 4 )
        {
            auto x = p2.x - p1.x;
            auto y = p2.y - p1.y;
            auto z = p2.z - p1.z;
            auto w = p2.w - p1.w;
            return x * x + y * y + z * z + w * w;
        }
    }


    // Distance

    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto Distance( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::Sqrt( DistanceSquared( p1, p2 ).simd ) );
    }

    // ScalarDistance

    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U>
    inline auto ScalarDistance( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Distance( p1, p2 ).simd );
    }

    // DifferenceOfProducts

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<SimdTupleOrArithmeticType S, SimdOrTupleType T, SimdTupleOrArithmeticType U, SimdTupleOrArithmeticType V>
    //requires IsCompatible<S, T>&& IsCompatible<S, U>&& IsCompatible<S, V>
    inline auto DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        auto v34 = v3 * v4;
        return FMA( v1, v2, -v34 );
    }

    // SumOfProducts

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<SimdTupleOrArithmeticType S, SimdOrTupleType T, SimdTupleOrArithmeticType U, SimdTupleOrArithmeticType V>
    //requires IsCompatible<S, T> && IsCompatible<S, U> && IsCompatible<S, V>
    inline auto SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        auto v34 = v3 * v4;
        return FMA( v1, v2, v34 );
    }

    // BaryCentric

    namespace Internal
    {
        /// <summary>
        /// Calculates a point in Barycentric coordinates, using the specified triangle.
        /// https://en.wikipedia.org/wiki/Barycentric_coordinate_system
        /// </summary>
        /// <param name="p1">
        /// The first position.
        /// </param>
        /// <param name="p2">
        /// The second position.
        /// </param>
        /// <param name="p3">
        /// The third position.
        /// </param>
        /// <param name="f">
        /// Weighting factor.
        /// </param>
        /// <param name="g">
        /// Weighting factor.
        /// </param>
        template<SimdType S, SimdType T, SimdType U, SimdType V, SimdType W>
            requires IsCompatible<S, T, U, V, W>
        inline S BaryCentricImpl( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
        {
            using Traits = typename S::Traits;
            using Simd = S;

            auto rmm1 = Traits::Sub( p2.simd, p1.simd );
            auto rmm2 = Traits::Sub( p3.simd, p1.simd );
            rmm1 = Traits::FMAdd( rmm1.simd, f.simd, p1.simd );
            return Simd( Traits::FMAdd( rmm2.simd, g.simd, rmm1.simd ) );
        }
    }

    /// <summary>
    /// Calculates a point in Barycentric coordinates, using the specified triangle.
    /// https://en.wikipedia.org/wiki/Barycentric_coordinate_system
    /// </summary>
    /// <param name="p1">
    /// The first position.
    /// </param>
    /// <param name="p2">
    /// The second position.
    /// </param>
    /// <param name="p3">
    /// The third position.
    /// </param>
    /// <param name="f">
    /// Weighting factor.
    /// </param>
    /// <param name="g">
    /// Weighting factor.
    /// </param>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U, SimdOrTupleType V, SimdOrTupleType W>
        requires IsCompatible<S, T>&& IsCompatible<S, U>&& IsCompatible<S, V>&& IsCompatible<S, W>
    inline auto BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        return Internal::BaryCentricImpl( Internal::ToSimdType( p1 ), Internal::ToSimdType( p2 ), Internal::ToSimdType( p3 ), Internal::ToSimdType( f ), Internal::ToSimdType( g ) );
    }

    /// <summary>
    /// Calculates a point in Barycentric coordinates, using the specified triangle.
    /// https://en.wikipedia.org/wiki/Barycentric_coordinate_system
    /// </summary>
    /// <param name="p1">
    /// The first position.
    /// </param>
    /// <param name="p2">
    /// The second position.
    /// </param>
    /// <param name="p3">
    /// The third position.
    /// </param>
    /// <param name="f">
    /// Weighting factor.
    /// </param>
    /// <param name="g">
    /// Weighting factor.
    /// </param>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U, ArithmeticType V, ArithmeticType W>
        requires IsCompatible<S, T, U>
    inline auto BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = typename Traits::Type;
        using Simd = typename S::Simd;

        return Internal::BaryCentricImpl( Internal::ToSimdType( p1 ), Internal::ToSimdType( p2 ), Internal::ToSimdType( p3 ), Simd( Traits::Fill<Traits::Size>( static_cast< Type >( f ) ) ), Simd( Traits::Fill<Traits::Size>( static_cast< Type >( g ) ) ) );
    }

    // CatmullRom

    namespace Internal
    {
        /// <summary>
        /// Calculates the Catmull-Rom interpolation, using the specified positions.
        /// </summary>
        /// <param name="p1">
        /// The first position.
        /// </param>
        /// <param name="p2">
        /// The second position.
        /// </param>
        /// <param name="p3">
        /// The third position.
        /// </param>
        /// <param name="p4">
        /// The fourth position.
        /// </param>
        /// <param name="t">
        /// The interpolation control factors.
        /// </param>
        template<SimdType S, SimdType T, SimdType U, SimdType V, SimdType W>
            requires IsCompatible<S, T, U, V, W>
        inline S CatmullRomImpl( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
        {
            using Traits = typename S::Traits;
            using FloatT = typename Traits::Type;
            using Simd = S;

            static constexpr Traits::SIMDType catmul2 = { { static_cast< FloatT >( 2.0 ), static_cast< FloatT >( 2.0 ), static_cast< FloatT >( 2.0 ), static_cast< FloatT >( 2.0 ) } };
            static constexpr Traits::SIMDType catmul3 = { { static_cast< FloatT >( 3.0 ), static_cast< FloatT >( 3.0 ), static_cast< FloatT >( 3.0 ), static_cast< FloatT >( 3.0 ) } };
            static constexpr Traits::SIMDType catmul4 = { { static_cast< FloatT >( 4.0 ), static_cast< FloatT >( 4.0 ), static_cast< FloatT >( 4.0 ), static_cast< FloatT >( 4.0 ) } };
            static constexpr Traits::SIMDType catmul5 = { { static_cast< FloatT >( 5.0 ), static_cast< FloatT >( 5.0 ), static_cast< FloatT >( 5.0 ), static_cast< FloatT >( 5.0 ) } };
            static constexpr Traits::SIMDType oneHalf = { { static_cast< FloatT >( 0.5 ), static_cast< FloatT >( 0.5 ), static_cast< FloatT >( 0.5 ), static_cast< FloatT >( 0.5 ) } };

            auto t2 = Traits::Mul( t.simd, t.simd );
            auto t3 = Traits::Mul( t.simd, t2 );
            // For p1:
            auto result = Traits::Add( t2, t2 );
            result = Traits::Sub( result, t.simd );
            result = Traits::Sub( result, t3 );
            result = Traits::Mul( result, p1.simd );
            // For p2:
            auto temp = Traits::Mul( t3, catmul3 );
            temp = Traits::FNMAdd( t2, catmul5, temp );
            temp = Traits::Add( temp, catmul2 );
            result = Traits::FMAdd( temp, p2.simd, result );
            // For p3:
            temp = Traits::Mul( t2, catmul4 );
            temp = Traits::FNMAdd( t3, catmul3, temp );
            temp = Traits::Add( temp, t.simd );
            result = Traits::FMAdd( temp, p3.simd, result );
            // For p4:
            t3 = Traits::Sub( t3, t2 );
            result = Traits::FMAdd( t3, p4.simd, result );
            // Divide by 2 
            return Simd( Traits::Mul( result, oneHalf ) );
        }
    }

    /// <summary>
    /// Calculates the Catmull-Rom interpolation, using the specified positions.
    /// </summary>
    /// <param name="p1">
    /// The first position.
    /// </param>
    /// <param name="p2">
    /// The second position.
    /// </param>
    /// <param name="p3">
    /// The third position.
    /// </param>
    /// <param name="p4">
    /// The fourth position.
    /// </param>
    /// <param name="t">
    /// The interpolation control factors.
    /// </param>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U, SimdOrTupleType V, SimdOrTupleType W>
        requires IsCompatible<S, T, U, V, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        return Internal::CatmullRomImpl( Internal::ToSimdType( p1 ), Internal::ToSimdType( p2 ), Internal::ToSimdType( p3 ), Internal::ToSimdType( p4 ), Internal::ToSimdType( t ) );
    }

    namespace Internal
    {
        /// <summary>
        /// Calculates the Catmull-Rom interpolation, using the specified positions.
        /// </summary>
        /// <param name="p1">
        /// The first position.
        /// </param>
        /// <param name="p2">
        /// The second position.
        /// </param>
        /// <param name="p3">
        /// The third position.
        /// </param>
        /// <param name="p4">
        /// The fourth position.
        /// </param>
        /// <param name="t">
        /// The interpolation control factors.
        /// </param>
        template<SimdType S, SimdType T, SimdType U, SimdType V>
            requires IsCompatible<S, T, U, V>
        inline S CatmullRomImpl( const S& p1, const T& p2, const U& p3, const V& p4, const typename S::value_type t ) noexcept
        {
            using Traits = typename S::Traits;
            using FloatT = typename Traits::Type;
            using Simd = S;

            FloatT t2 = t * t;
            FloatT t3 = t * t2;

            auto P1 = Traits::Fill( ( -t3 + static_cast< FloatT >( 2.0 ) * t2 - t ) * static_cast< FloatT >( 0.5 ) );
            auto P2 = Traits::Fill( ( static_cast< FloatT >( 3.0 ) * t3 - static_cast< FloatT >( 5.0 ) * t2 + static_cast< FloatT >( 2.0 ) ) * static_cast< FloatT >( 0.5 ) );
            auto P3 = Traits::Fill( ( static_cast< FloatT >( -3.0 ) * t3 + static_cast< FloatT >( 4.0 ) * t2 + t ) * static_cast< FloatT >( 0.5 ) );
            auto P4 = Traits::Fill( ( t3 - t2 ) * static_cast< FloatT >( 0.5 ) );

            P2 = Traits::Mul( p2.simd, P2 );
            P1 = Traits::FMAdd( p1.simd, P1, P2 );
            P4 = Traits::Mul( p4.simd, P4 );
            P3 = Traits::FMAdd( p3.simd, P3, P4 );
            return Simd( Traits::Trim( Traits::Add( P1, P3 ) ) );
        }
    }

    /// <summary>
    /// Calculates the Catmull-Rom interpolation, using the specified positions.
    /// </summary>
    /// <param name="p1">
    /// The first position.
    /// </param>
    /// <param name="p2">
    /// The second position.
    /// </param>
    /// <param name="p3">
    /// The third position.
    /// </param>
    /// <param name="p4">
    /// The fourth position.
    /// </param>
    /// <param name="t">
    /// The interpolation control factors.
    /// </param>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U, SimdOrTupleType V, ArithmeticType W>
        requires IsCompatible<S, T, U, V>
    inline auto CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Type = typename Traits::Type;
        using SimdType = Internal::MakeResultType<T>;
        return Internal::CatmullRomImpl( Internal::ToSimdType( p1 ), Internal::ToSimdType( p2 ), Internal::ToSimdType( p3 ), Internal::ToSimdType( p4 ), SimdType( Traits::Fill<Traits::Size>( static_cast< Type >( t ) ) ) );
    }


    /// <summary>
    /// Retrieves the lowest value held by the 
    /// argument.
    /// </summary>
    /// <param name="v">
    /// The argument.
    /// </param>
    /// <returns>
    /// The lowest value held by the argument.
    /// </returns>
    template<SimdType T>
    inline auto MinComponentValue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HorizontalMin( v.simd );
    }
    /// <summary>
    /// Retrieves the lowest value held by the 
    /// argument.
    /// </summary>
    /// <param name="v">
    /// The argument.
    /// </param>
    /// <returns>
    /// The lowest value held by the argument.
    /// </returns>
    template<TupleType T>
    constexpr inline auto MinComponentValue( const T& v ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return Min( v.x, v.y );
        }
        else if constexpr ( T::Size == 3 )
        {
            return Min( v.x, v.y, v.z );
        }
        else if constexpr ( T::Size == 4 )
        {
            return Min( v.x, v.y, v.z, v.w );
        }
        else
        {
            return *std::min_element( v.values.begin( ), v.values.end( ) );
        }
    }

    /// <summary>
    /// Retrieves the highest value held by the 
    /// argument.
    /// </summary>
    /// <param name="v">
    /// The argument.
    /// </param>
    /// <returns>
    /// The highest value held by the argument.
    /// </returns>
    template<SimdType T>
    inline auto MaxComponentValue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HorizontalMax( v.simd );
    }

    /// <summary>
    /// Retrieves the highest value held by the 
    /// argument.
    /// </summary>
    /// <param name="v">
    /// The argument.
    /// </param>
    /// <returns>
    /// The highest value held by the argument.
    /// </returns>
    template<TupleType T>
    constexpr inline auto MaxComponentValue( const T& v ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return Max( v.x, v.y );
        }
        else if constexpr ( T::Size == 3 )
        {
            return Max( v.x, v.y, v.z );
        }
        else if constexpr ( T::Size == 4 )
        {
            return Max( v.x, v.y, v.z, v.w );
        }
        else
        {
            return *std::max_element( v.values.begin( ), v.values.end( ) );
        }
    }

    namespace Internal
    {
        template<typename FloatT, size_t N>
        constexpr size_t MinIndex( const std::array<FloatT, N>& values, size_t first, size_t second )
        {
            return values[ first ] <= values[ second ] ? first : second;
        }
        template<typename FloatT, size_t N>
        constexpr size_t MaxIndex( const std::array<FloatT, N>& values, size_t first, size_t second )
        {
            return values[ first ] >= values[ second ] ? first : second;
        }
    }


    /// <summary>
    /// Retrieves the offset of the highest value held by the argument.
    /// </summary>
    /// <param name="v">
    /// The argument.
    /// </param>
    /// <returns>
    /// The offset of the highest value held by the argument.
    /// </returns>
    template<TupleType T>
    constexpr inline size_t MaxComponentIndex( const T& v ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return Internal::MaxIndex( v.values, 0, 1 );
        }
        else if constexpr ( T::Size == 3 )
        {
            return Internal::MaxIndex( v.values, Internal::MaxIndex( v.values, 0, 1 ), 2 );
        }
        else
        {
            return Internal::MaxIndex( v.values, Internal::MaxIndex( v.values, 0, 1 ), Internal::MaxIndex( v.values, 2, 3 ) );
        }
    }

    /// <summary>
    /// Retrieves the offset of the highest value held by the argument.
    /// </summary>
    /// <param name="v">
    /// The argument.
    /// </param>
    /// <returns>
    /// The offset of the highest value held by the argument.
    /// </returns>
    template<SimdType T>
    constexpr inline size_t MaxComponentIndex( const T& v ) noexcept
    {
        using TupleT = T::TupleType;
        TupleT tmp( v );
        return MaxComponentIndex( tmp );
    }

    /// <summary>
    /// Retrieves the offset of the lowest value held by the argument.
    /// </summary>
    /// <param name="v">
    /// The argument.
    /// </param>
    /// <returns>
    /// The offset of the lowest value held by the argument.
    /// </returns>
    template<TupleType T>
    constexpr inline size_t MinComponentIndex( const T& v ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return Internal::MinIndex( v.values, 0, 1 );
        }
        else if constexpr ( T::Size == 3 )
        {
            return Internal::MinIndex( v.values, Internal::MinIndex( v.values, 0, 1 ), 2 );
        }
        else
        {
            return Internal::MinIndex( v.values, Internal::MinIndex( v.values, 0, 1 ), Internal::MinIndex( v.values, 2, 3 ) );
        }
    }

    /// <summary>
    /// Retrieves the offset of the lowest value held by the argument.
    /// </summary>
    /// <param name="v">
    /// The argument.
    /// </param>
    /// <returns>
    /// The offset of the lowest value held by the argument.
    /// </returns>
    template<SimdType T, typename ResultT = typename T::value_type >
    constexpr inline size_t MinComponentIndex( const T& v ) noexcept
    {
        using TupleT = T::TupleType;
        TupleT tmp( v );
        return MinComponentIndex( tmp );
    }

    // NextUp

    template<SimdOrTupleType T>
    inline auto NextUp( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::NextUp( Internal::ToSimd( t ) ) );
    }


    // NextDown

    template<SimdOrTupleType T>
    inline auto NextDown( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = Internal::MakeResultType<T>;
        return ResultType( Traits::NextDown( Internal::ToSimd( t ) ) );
    }


    // AddAdjustUp

    template<SimdType S, SimdType T >
        requires IsCompatible<S, T>
    inline S AddAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Add( a.simd, b.simd ) ) );
    }

    template<SimdType S, TupleType T >
        requires IsCompatible<S, T>
    inline S AddAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Add( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<TupleType S, SimdType T >
        requires IsCompatible<S, T>
    inline T AddAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Add( Traits::Load( a.values ), b.simd ) ) );
    }

    template<TupleType S, TupleType T >
        requires IsCompatible<S, T>
    inline typename S::Simd AddAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Add( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }




    // AddAdjustDown

    template<SimdType S, SimdType T >
        requires IsCompatible<S, T>
    inline S AddAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Add( a.simd, b.simd ) ) );
    }

    template<SimdType S, TupleType T >
        requires IsCompatible<S, T>
    inline S AddAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Add( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<TupleType S, SimdType T >
        requires IsCompatible<S, T>
    inline T AddAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Add( Traits::Load( a.values ), b.simd ) ) );
    }

    template<TupleType S, TupleType T >
        requires IsCompatible<S, T>
    inline typename S::Simd AddAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Add( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // SubAdjustUp

    template<SimdType S, SimdType T >
        requires IsCompatible<S, T>
    inline S SubAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sub( a.simd, b.simd ) ) );
    }

    template<SimdType S, TupleType T >
        requires IsCompatible<S, T>
    inline S SubAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sub( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<TupleType S, SimdType T >
        requires IsCompatible<S, T>
    inline T SubAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sub( Traits::Load( a.values ), b.simd ) ) );
    }

    template<TupleType S, TupleType T >
        requires IsCompatible<S, T>
    inline typename S::Simd SubAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sub( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // SubAdjustDown

    template<SimdType S, SimdType T >
        requires IsCompatible<S, T>
    inline S SubAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sub( a.simd, b.simd ) ) );
    }

    template<SimdType S, TupleType T >
        requires IsCompatible<S, T>
    inline S SubAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sub( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<TupleType S, SimdType T >
        requires IsCompatible<S, T>
    inline T SubAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sub( Traits::Load( a.values ), b.simd ) ) );
    }

    template<TupleType S, TupleType T >
        requires IsCompatible<S, T>
    inline typename S::Simd SubAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sub( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // MulAdjustUp

    template<SimdType S, SimdType T >
        requires IsCompatible<S, T>
    inline S MulAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Mul( a.simd, b.simd ) ) );
    }

    template<SimdType S, TupleType T >
        requires IsCompatible<S, T>
    inline S MulAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Mul( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<TupleType S, SimdType T >
        requires IsCompatible<S, T>
    inline T MulAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Mul( Traits::Load( a.values ), b.simd ) ) );
    }

    template<TupleType S, TupleType T >
        requires IsCompatible<S, T>
    inline typename S::Simd MulAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Mul( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // MulAdjustDown

    template<SimdType S, SimdType T >
        requires IsCompatible<S, T>
    inline S MulAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Mul( a.simd, b.simd ) ) );
    }

    template<SimdType S, TupleType T >
        requires IsCompatible<S, T>
    inline S MulAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Mul( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<TupleType S, SimdType T >
        requires IsCompatible<S, T>
    inline T MulAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Mul( Traits::Load( a.values ), b.simd ) ) );
    }

    template<TupleType S, TupleType T >
        requires IsCompatible<S, T>
    inline typename S::Simd MulAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Mul( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // DivAdjustUp

    template<SimdType S, SimdType T >
        requires IsCompatible<S, T>
    inline S DivAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Div( a.simd, b.simd ) ) );
    }

    template<SimdType S, TupleType T >
        requires IsCompatible<S, T>
    inline S DivAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Div( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<TupleType S, SimdType T >
        requires IsCompatible<S, T>
    inline T DivAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Div( Traits::Load( a.values ), b.simd ) ) );
    }

    template<TupleType S, TupleType T >
        requires IsCompatible<S, T>
    inline typename S::Simd DivAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Div( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // DivAdjustDown

    template<SimdType S, SimdType T >
        requires IsCompatible<S, T>
    inline S DivAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Div( a.simd, b.simd ) ) );
    }

    template<SimdType S, TupleType T >
        requires IsCompatible<S, T>
    inline S DivAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Div( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<TupleType S, SimdType T >
        requires IsCompatible<S, T>
    inline T DivAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Div( Traits::Load( a.values ), b.simd ) ) );
    }

    template<TupleType S, TupleType T >
        requires IsCompatible<S, T>
    inline typename S::Simd DivAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Div( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }


    // SqrtAdjustUp

    template<SimdType S >
    inline S SqrtAdjustUp( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sqrt( v.simd ) ) );
    }
    template<TupleType S >
    inline typename S::Simd SqrtAdjustUp( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sqrt( Traits::Load( v.values ) ) ) );
    }

    // SqrtAdjustDown

    template<SimdType S >
    inline S SqrtAdjustDown( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sqrt( v.simd ) ) );
    }
    template<TupleType S >
    inline typename S::Simd SqrtAdjustDown( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sqrt( Traits::Load( v.values ) ) ) );
    }

    // FMAAdjustUp

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, SimdType T, SimdType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline T FMAAdjustUp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, SimdType T, TupleType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline T FMAAdjustUp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, TupleType T, SimdType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline U FMAAdjustUp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, TupleType T, TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline ResultT FMAAdjustUp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values ), Traits::Load( c.values ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, SimdType T, SimdType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline T FMAAdjustUp( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, SimdType T, TupleType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline T FMAAdjustUp( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, TupleType T, SimdType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline U FMAAdjustUp( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values ), Traits::Fill( static_cast< Type >( b ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, TupleType T, TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline ResultT FMAAdjustUp( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, SimdType T, SimdType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline T FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, SimdType T, TupleType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline T FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, TupleType T, SimdType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline U FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, Traits::Load( b.values ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, TupleType T, TupleType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline S FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, Traits::Load( b.values ), Traits::Load( c.values ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<TupleType S, SimdType T, SimdType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline T FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values ), b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<TupleType S, SimdType T, TupleType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline T FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values ), b.simd, Traits::Load( c.values ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<TupleType S, TupleType T, SimdType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline U FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values ), Traits::Load( b.values ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<TupleType S, TupleType T, TupleType U, typename ResultT = typename T::Simd >
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline ResultT FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values ), Traits::Load( b.values ), Traits::Load( c.values ) ) ) );
    }

    // FMAAdjustDown

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, SimdType T, SimdType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline T FMAAdjustDown( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, SimdType T, TupleType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline T FMAAdjustDown( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, TupleType T, SimdType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline U FMAAdjustDown( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, TupleType T, TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline ResultT FMAAdjustDown( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values ), Traits::Load( c.values ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, SimdType T, SimdType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline T FMAAdjustDown( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, SimdType T, TupleType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline T FMAAdjustDown( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, TupleType T, SimdType U>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline U FMAAdjustDown( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values ), Traits::Fill( static_cast< Type >( b ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, TupleType T, TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& IsCompatible<T, U>
    inline ResultT FMAAdjustDown( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, SimdType T, SimdType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline T FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, SimdType T, TupleType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline T FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, TupleType T, SimdType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline U FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, Traits::Load( b.values ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<SimdType S, TupleType T, TupleType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline S FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, Traits::Load( b.values ), Traits::Load( c.values ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<TupleType S, SimdType T, SimdType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline T FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values ), b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<TupleType S, SimdType T, TupleType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline T FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values ), b.simd, Traits::Load( c.values ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<TupleType S, TupleType T, SimdType U>
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline U FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values ), Traits::Load( b.values ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<TupleType S, TupleType T, TupleType U, typename ResultT = typename T::Simd >
        requires IsCompatible<S, T>&& IsCompatible<T, U>
    inline ResultT FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values ), Traits::Load( b.values ), Traits::Load( c.values ) ) ) );
    }



    template<>
    class Vector<float, 2> : public Tuple2<Vector<float, 2>, float>, public Internal::VectorBase
    {
    public:
        using Base = Tuple2<Vector<float, 2>, float>;
        using Base::Base;
    };

    template<>
    class Vector<Int32, 2> : public Tuple2<Vector<Int32, 2>, Int32>, public Internal::VectorBase
    {
    public:
        using Base = Tuple2<Vector<Int32, 2>, Int32>;
        using Base::Base;
    };





    template<>
    class Vector<double, 2> : public Tuple2<Vector<double, 2>, double>, public Internal::VectorBase
    {
    public:
        using Base = Tuple2<Vector<double, 2>, double>;
        using Base::Base;
    };

    template<>
    class Vector<UInt32, 2> : public Tuple2<Vector<UInt32, 2>, UInt32>, public Internal::VectorBase
    {
    public:
        using Base = Tuple2<Vector<UInt32, 2>, UInt32>;
        using Base::Base;
    };


    template<>
    class Vector<float, 3> : public Tuple3<Vector<float, 3>, float>, public Internal::VectorBase
    {
    public:
        using Base = Tuple3<Vector<float, 3>, float>;
        using Base::Base;
    };

    template<>
    class Vector<Int32, 3> : public Tuple3<Vector<Int32, 3>, Int32>, public Internal::VectorBase
    {
    public:
        using Base = Tuple3<Vector<Int32, 3>, Int32>;
        using Base::Base;
    };


    template<>
    class Vector<double, 3> : public Tuple3<Vector<double, 3>, double>, public Internal::VectorBase
    {
    public:
        using Base = Tuple3<Vector<double, 3>, double>;
        using Base::Base;
    };

    template<>
    class Vector<UInt32, 3> : public Tuple3<Vector<UInt32, 3>, UInt32>, public Internal::VectorBase
    {
    public:
        using Base = Tuple3<Vector<UInt32, 3>, UInt32>;
        using Base::Base;
    };


    template<>
    class Vector<float, 4> : public Tuple4<Vector<float, 4>, float>, public Internal::VectorBase
    {
    public:
        using Base = Tuple4<Vector<float, 4>, float>;
        using Base::Base;
    };

    template<>
    class Vector<Int32, 4> : public Tuple4<Vector<Int32, 4>, Int32>, public Internal::VectorBase
    {
    public:
        using Base = Tuple4<Vector<Int32, 4>, Int32>;
        using Base::Base;
    };



    template<>
    class Vector<double, 4> : public Tuple4<Vector<double, 4>, double>, public Internal::VectorBase
    {
    public:
        using Base = Tuple4<Vector<double, 4>, double>;
        using Base::Base;
    };

    template<>
    class Vector<UInt32, 4> : public Tuple4<Vector<UInt32, 4>, UInt32>, public Internal::VectorBase
    {
    public:
        using Base = Tuple4<Vector<UInt32, 4>, UInt32>;
        using Base::Base;
    };


    namespace Internal
    {
        /// <summary>
        /// Calculates the angle in radians between two vectors.
        /// </summary>
        /// <param name="v1">
        /// The first vector.
        /// </param>
        /// <param name="v2">
        /// The second vector.
        /// </param>
        /// <returns>
        /// A vector where with each element set to the 
        /// angle between the two argument vectors.
        /// </returns>
        template<VectorSimdType S, VectorSimdType T>
            requires IsCompatible<S, T>
        inline S AngleBetweenImpl( const S& v1, const T& v2 ) noexcept
        {
            using Traits = typename S::Traits;
            using SIMDType = typename Traits::SIMDType;
            using Simd = S;

            constexpr SIMDType minusOne = { {-1.f,-1.f,-1.f,-1.f} };
            constexpr SIMDType one = { {1.f,1.f,1.f,1.f} };

            auto l1 = ReciprocalLength( v1 );
            auto l2 = ReciprocalLength( v2 );

            auto dot = Dot( v1, v2 );

            l1 = l1 * l2;

            auto cosine = dot * l1;
            cosine.simd = Traits::Clamp( cosine.simd, minusOne, one );

            return ACos( cosine );
        }
    }

    /// <summary>
    /// Calculates the angle in radians between two vectors.
    /// </summary>
    /// <param name="v1">
    /// The first vector.
    /// </param>
    /// <param name="v2">
    /// The second vector.
    /// </param>
    /// <returns>
    /// A vector where with each element set to the 
    /// angle between the two argument vectors.
    /// </returns>
    template<VectorOrVectorSimdType S, VectorOrVectorSimdType T>
        requires IsCompatible<S, T>
    inline auto AngleBetween( const S& v1, const T& v2 ) noexcept
    {
        return Internal::AngleBetweenImpl( Internal::ToSimdType( v1 ), Internal::ToSimdType( v2 ) );
    }


    namespace Internal
    {
        /// <summary>
        /// Calculates the angle in radians between two normalized vectors.
        /// </summary>
        /// <param name="v1">
        /// The first normalized vector.
        /// </param>
        /// <param name="v2"></param>
        /// The second normalized vector.
        /// <returns>
        /// A vector where with each element set to the 
        /// angle between the two argument vectors.
        /// </returns>
        template<VectorSimdType S, VectorSimdType T>
            requires IsCompatible<S, T>
        inline S AngleBetweenNormalizedImpl( const S& v1, const T& v2 ) noexcept
        {
            using Traits = typename S::Traits;
            using SIMDType = typename Traits::SIMDType;
            using Simd = typename S::Simd;

            constexpr SIMDType minusOne = { {-1.f,-1.f,-1.f,-1.f} };
            constexpr SIMDType one = { {1.f,1.f,1.f,1.f} };

            auto result = Traits::Dot( v1.simd, v2.simd );
            result = Traits::Clamp( result, minusOne, one );
            return Simd( Traits::ACos( result ) );
        }
    }

    /// <summary>
    /// Calculates the angle in radians between two normalized vectors.
    /// </summary>
    /// <param name="v1">
    /// The first normalized vector.
    /// </param>
    /// <param name="v2"></param>
    /// The second normalized vector.
    /// <returns>
    /// A vector where with each element set to the 
    /// angle between the two argument vectors.
    /// </returns>
    template<VectorOrVectorSimdType S, VectorOrVectorSimdType T>
        requires IsCompatible<S, T>
    inline auto AngleBetweenNormalized( const S& v1, const T& v2 ) noexcept
    {
        return Internal::AngleBetweenNormalizedImpl( Internal::ToSimdType( v1 ), Internal::ToSimdType( v2 ) );
    }


    // Vector2* Definitions
    using Vector2f = Vector<float, 2>;
    using Vector2d = Vector<double, 2>;
    using Vector2i = Vector<int, 2>;

    static_assert( sizeof( Vector2f ) == sizeof( std::array<float, 2> ) );

    // Vector3* Definitions
    using Vector3f = Vector<float, 3>;
    using Vector3d = Vector<double, 3>;
    using Vector3i = Vector<int, 3>;

    // Vector4* Definitions
    using Vector4f = Vector<float, 4>;
    using Vector4d = Vector<double, 4>;
    using Vector4i = Vector<int, 4>;


    template<ArithmeticType T, size_t N>
    class Scalar;


    template<>
    class Scalar<float, 2> : public Tuple2<Scalar<float, 2>, float>, public Internal::ScalarBase
    {
    public:
        using Base = Tuple2<Scalar<float, 2>, float>;
        using Base::Base;
    };

    template<>
    class Scalar<double, 2> : public Tuple2<Scalar<double, 2>, double>, public Internal::ScalarBase
    {
    public:
        using Base = Tuple2<Scalar<double, 2>, double>;
        using Base::Base;
    };

    template<>
    class Scalar<float, 3> : public Tuple3<Scalar<float, 3>, float>, public Internal::ScalarBase
    {
    public:
        using Base = Tuple3<Scalar<float, 3>, float>;
        using Base::Base;
    };

    template<>
    class Scalar<double, 3> : public Tuple3<Scalar<double, 3>, double>, public Internal::ScalarBase
    {
    public:
        using Base = Tuple3<Scalar<double, 3>, double>;
        using Base::Base;
    };

    template<>
    class Scalar<float, 4> : public Tuple4<Scalar<float, 4>, float>, public Internal::ScalarBase
    {
    public:
        using Base = Tuple4<Scalar<float, 4>, float>;
        using Base::Base;
    };



    template<>
    class Scalar<double, 4> : public Tuple4<Scalar<double, 4>, double>, public Internal::ScalarBase
    {
    public:
        using Base = Tuple4<Scalar<double, 4>, double>;
        using Base::Base;
    };



    namespace Internal
    {
        struct PointBase
        {
        };

        struct NormalBase
        {
        };
    }

    template<typename T>
    concept PointType = std::is_base_of_v<Internal::PointBase, T>;

    template<typename T>
    concept PointSimdType = std::is_base_of_v<Internal::PointBase, typename T::TupleType>;

    template<typename T>
    concept PointOrPointSimdType = PointType<T> || PointSimdType<T>;


    template<typename T>
    concept NormalType = std::is_base_of_v<Internal::NormalBase, T>;

    template<typename T>
    concept NormalSimdType = std::is_base_of_v<Internal::NormalBase, typename T::TupleType>;

    template<typename T>
    concept NormalOrNormalSimdType = NormalType<T> || NormalSimdType<T>;


    template<ArithmeticType T, size_t N>
    class Point;

    template<>
    class Point<Int32, 2> : public Tuple2<Point<Int32, 2>, Int32>, public Internal::PointBase
    {
    public:
        using Base = Tuple2<Point<Int32, 2>, Int32>;
        using Base::Base;
    };
    using Point2i = Point<Int32, 2>;

    template<>
    class Point<Int32, 3> : public Tuple3<Point<Int32, 3>, Int32>, public Internal::PointBase
    {
    public:
        using Base = Tuple3<Point<Int32, 3>, Int32>;
        using Base::Base;
    };

    using Point3i = Point<Int32, 3>;

    template<>
    class Point<float, 2> : public Tuple2<Point<float, 2>, float>, public Internal::PointBase
    {
    public:
        using Base = Tuple2<Point<float, 2>, float>;
        using Base::Base;
    };
    using Point2f = Point<float, 2>;


    // Copied from pbrt-v4 https://github.com/mmp/pbrt-v4
    // https://www.iquilezles.org/www/articles/ibilinear/ibilinear.htm,
    // with a fix for perfect quads
    inline Point2f InvertBilinear( const Point2f& p, const std::array<Point2f, 4>& vert )
    {
        using FloatT = typename Point2f::value_type;
        // The below assumes a quad (vs uv parametric layout) in v....
        auto a = vert[ 0 ];
        auto b = vert[ 1 ];
        auto c = vert[ 3 ];
        auto d = vert[ 2 ];

        Vector2f e = b - a;
        Vector2f f = d - a;
        Vector2f g = ( a - b ) + ( c - d );
        Vector2f h = p - a;

        auto cross2d = []( Vector2f a, Vector2f b ) { return DifferenceOfProducts( a.x, b.y, a.y, b.x ); };

        FloatT k2 = cross2d( g, f );
        FloatT k1 = cross2d( e, f ) + cross2d( h, g );
        FloatT k0 = cross2d( h, e );

        // if edges are parallel, this is a linear equation
        if ( std::abs( k2 ) < 0.001f )
        {
            if ( std::abs( e.x * k1 - g.x * k0 ) < 1e-5f )
            {
                return Point2f( ( h.y * k1 + f.y * k0 ) / ( e.y * k1 - g.y * k0 ), -k0 / k1 );
            }
            else
            {
                return Point2f( ( h.x * k1 + f.x * k0 ) / ( e.x * k1 - g.x * k0 ), -k0 / k1 );
            }
        }

        FloatT v0, v1;
        if ( !Quadratic( k2, k1, k0, &v0, &v1 ) )
        {
            return Point2f( 0, 0 );
        }
        FloatT u = ( h.x - f.x * v0 ) / ( e.x + g.x * v0 );
        if ( u < 0 || u > 1 || v0 < 0 || v0 > 1 )
        {
            return Point2f( ( h.x - f.x * v1 ) / ( e.x + g.x * v1 ), v1 );
        }
        return Point2f( u, v0 );
    }


    template<>
    class Point<float, 3> : public Tuple3<Point<float, 3>, float>, public Internal::PointBase
    {
    public:
        using Base = Tuple3<Point<float, 3>, float>;
        using Base::Base;
    };
    using Point3f = Point<float, 3>;


    namespace Internal
    {
        /// <summary>
        /// Calculates the minimum distance between a line and a point.
        /// </summary>
        /// <param name="linePoint1">
        /// First point on the line.
        /// </param>
        /// <param name="linePoint2">
        /// Second point on the line.
        /// </param>
        /// <param name="point">
        /// The reference point.
        /// </param>
        /// <returns>
        /// The minimum distance between a line and a point.
        /// </returns>
        template<PointSimdType S, PointSimdType T, PointSimdType U>
            requires IsCompatible<S, T>&& IsCompatible<S, U>
        inline S LinePointDistanceImpl( const S& linePoint1, const T& linePoint2, const U& point ) noexcept
        {
            auto pointVector = point - linePoint1;
            auto lineVector = linePoint2 - linePoint1;

            auto lengthSquared = LengthSquared( lineVector );

            auto pointProjectionScale = Dot( pointVector, lineVector );
            pointProjectionScale = pointProjectionScale / lengthSquared;

            auto distanceVector = lineVector * pointProjectionScale;
            distanceVector = pointVector - distanceVector;

            return Length( distanceVector );
        }
    }

    /// <summary>
    /// Calculates the minimum distance between a line and a point.
    /// </summary>
    /// <param name="linePoint1">
    /// First point on the line.
    /// </param>
    /// <param name="linePoint2">
    /// Second point on the line.
    /// </param>
    /// <param name="point">
    /// The reference point.
    /// </param>
    /// <returns>
    /// The minimum distance between a line and a point.
    /// </returns>
    template<PointOrPointSimdType S, PointOrPointSimdType T, PointOrPointSimdType U>
        requires IsCompatible<S, T>&& IsCompatible<S, U>
    inline auto LinePointDistance( const S& linePoint1, const T& linePoint2, const U& point ) noexcept
    {
        return LinePointDistance( Internal::ToSimdType( linePoint1 ), Internal::ToSimdType( linePoint2 ), Internal::ToSimdType( point ) );
    }


    template<ArithmeticType T, size_t N>
    class Normal;

    template<>
    class Normal<float, 3> : public Tuple3<Normal<float, 3>, float>, public Internal::NormalBase
    {
    public:
        using Base = Tuple3<Normal<float, 3>, float>;
        using Base::Base;
    };

    using Normal3f = Normal<float, 3>;


    namespace Internal
    {
        struct QuaternionSimdBase
        {
        };
        struct QuaternionBase
        {
        };
    }

    template<typename T>
    concept QuaternionSimdType = std::is_base_of_v<Internal::QuaternionSimdBase, T>;

    template<typename T>
    concept QuaternionType = std::is_base_of_v<Internal::QuaternionBase, T>;

    template<typename T>
    concept QuaternionOrQuaternionSimdType = QuaternionType<T> || QuaternionSimdType<T>;


    template<QuaternionOrQuaternionSimdType T, QuaternionOrQuaternionSimdType ...Other>
    constexpr bool IsCompatibleQuaternion = ( std::is_same_v<typename T::Traits, typename Other::Traits> && ... );

    namespace Internal
    {
        template<QuaternionSimdType T>
        inline constexpr const typename T::SIMDType ToSimd( const T& q ) noexcept
        {
            return q.simd;
        }

        template<QuaternionType T>
        inline typename T::SIMDType ToSimd( const T& q ) noexcept
        {
            using Traits = typename T::Traits;
            return Traits::Load( q.values );
        }

        template<QuaternionSimdType T>
        inline constexpr const T& ToSimdType( const T& q ) noexcept
        {
            return q;
        }

        template<QuaternionType T>
        inline const typename T::Simd ToSimdType( const T& q ) noexcept
        {
            return typename T::Simd( q );
        }

        template<QuaternionOrQuaternionSimdType ... Args>
        constexpr bool HasQuaternionSimdType = ( QuaternionSimdType<Args> || ... );

        template<QuaternionOrQuaternionSimdType ... Args>
        constexpr bool HasQuaternionType = ( QuaternionType<Args> || ... );
    }



    template<typename QuaternionT>
    class alignas( QuaternionT::Traits::AlignAs ) QuaternionSimd : public Internal::QuaternionSimdBase
    {
    public:
        using QuaternionType = QuaternionT;

        using ValueType = typename QuaternionType::ValueType;
        using size_type = size_t;
        using value_type = ValueType;
        using Vector = typename Vector<value_type, 3>;
        using VectorSimd = typename Vector::Simd;
        using Normal = Normal3f;
        using NormalSimd = typename Normal::Simd;

        using Simd = QuaternionSimd<QuaternionT>;

        using Matrix = SquareMatrix<ValueType, 4>;
        using MatrixSimd = SquareMatrixSimd<Matrix, 4>;

        static constexpr size_type Size = 4;

        using Traits = typename QuaternionType::Traits;
        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;

        SIMDType simd;

        QuaternionSimd( ) noexcept
            : simd( Traits::Zero( ) )
        {
        }

        QuaternionSimd( const QuaternionSimd& other ) noexcept
            : simd( other.simd )
        {
        }

        explicit QuaternionSimd( SIMDType other ) noexcept
            : simd( other )
        {
        }

        /// <summary>
        /// Creates a quaternion based on the pitch, yaw, and roll (Euler angles).
        /// </summary>
        /// <param name="pitchYawRoll">
        /// A vector containing the Euler angles in the order pitch 
        /// (around x-axis), then yaw (around y-axis), and then roll 
        /// (around z-axis).
        /// </param>
        template<SimdType T>
        QuaternionSimd( const T& pitchYawRoll )
        {
            if constexpr ( std::is_same_v<value_type, float> )
            {
                using Traits = SIMD::Traits<float, 4>;
                constexpr SIMDType sign = { { static_cast< value_type >( 1.0 ), static_cast< value_type >( -1.0 ), static_cast< value_type >( -1.0 ), static_cast< value_type >( 1.0 ) } };
                constexpr SIMDType oneHalf = { {static_cast< value_type >( 0.5 ),static_cast< value_type >( 0.5 ),static_cast< value_type >( 0.5 ),static_cast< value_type >( 0.5 )} };
                auto halfPitchYawRoll = Traits::Mul( pitchYawRoll.simd, oneHalf );

                SIMDType cosines;
                auto sines = Traits::FastSinCos( halfPitchYawRoll, &cosines );
                using P = typename Traits::PermuteType;

                auto p0 = Traits::Permute<P::X1, P::X2, P::X2, P::X2>( sines, cosines );
                auto y0 = Traits::Permute<P::Y2, P::Y1, P::Y2, P::Y2>( sines, cosines );
                auto r0 = Traits::Permute<P::Z2, P::Z2, P::Z1, P::Z2>( sines, cosines );
                auto p1 = Traits::Permute<P::X1, P::X2, P::X2, P::X2>( cosines, sines );
                auto y1 = Traits::Permute<P::Y2, P::Y1, P::Y2, P::Y2>( cosines, sines );
                auto r1 = Traits::Permute<P::Z2, P::Z2, P::Z1, P::Z2>( cosines, sines );

                auto q1 = Traits::Mul( p1, sign );
                auto q0 = Traits::Mul( p0, y0 );
                q1 = Traits::Mul( q1, y1 );
                q0 = Traits::Mul( q0, r0 );
                simd = Traits::FMAdd( q1, r1, q0 );
            }
        }

        /// <summary>
        /// Creates a quaternion based on the pitch, yaw, and roll (Euler angles).
        /// </summary>
        /// <param name="pitchYawRoll">
        /// A vector containing the Euler angles in the order pitch 
        /// (around x-axis), then yaw (around y-axis), and then roll 
        /// (around z-axis).
        /// </param>
        template<TupleType T>
        QuaternionSimd( const T& pitchYawRoll )
            : QuaternionSimd( pitchYawRoll.ToSimd( ) )
        {
        }


        template<SimdType T>
        QuaternionSimd( const T& xyz, value_type w )
            : simd( Traits::SetW( xyz.simd, w ) )
        {
        }

        template<TupleType T>
        QuaternionSimd( const T& xyz, value_type w )
            : simd( Traits::SetW( Traits::Load( xyz.values ), w ) )
        {
        }



        /// <summary>
        /// Creates a quaternion based on the pitch, yaw, and roll (Euler angles).
        /// </summary>
        /// <param name="pitch">
        /// Angle of rotation around the x-axis, in radians.
        /// </param>
        /// <param name="yaw">
        /// Angle of rotation around the y-axis, in radians.
        /// </param>
        /// <param name="roll">
        /// Angle of rotation around the z-axis, in radians.
        /// </param>
        QuaternionSimd( ValueType pitch, ValueType yaw, ValueType roll ) noexcept
            : QuaternionSimd( VectorSimd( Vector::Traits::Set( roll, yaw, pitch ) ) )
        {
        }

        explicit QuaternionSimd( const QuaternionType& quaternion ) noexcept;

        constexpr QuaternionSimd( ValueType xv, ValueType yv, ValueType zv, ValueType wv ) noexcept
            : simd( Traits::Set( wv, zv, yv, xv ) )
        {
        }


        /// <summary>
        /// Creates a rotation quaternion around a normalized axis.
        /// </summary>
        /// <param name="normalizedAxis">
        /// A normalized vector describing the axis of rotation.
        /// </param>
        /// <param name="angle">
        /// The angle of rotation in radians.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<SimdType T>
            requires IsCompatible<T, VectorSimd>
        static QuaternionSimd FromNormalizedAxisAndAngle( const T& normalizedAxis, float angle ) noexcept
        {
            using Constants = Traits::Constants;

            auto n = Traits::And( normalizedAxis.simd, Constants::Mask3 );
            n = Traits::Or( n, Constants::IdentityR4 );
            auto scale = Traits::Fill( 0.5f * angle );
            SIMDType cosine;
            auto sine = Traits::FastSinCos( scale, &cosine );
            scale = Traits::And( sine, Constants::Mask3 );
            cosine = Traits::And( cosine, Constants::MaskW );
            scale = Traits::Or( scale, cosine );
            return QuaternionSimd( Traits::Mul( n, scale ) );
        }

        /// <summary>
        /// Creates a rotation quaternion around a normalized axis.
        /// </summary>
        /// <param name="normalizedAxis">
        /// A normalized vector describing the axis of rotation.
        /// </param>
        /// <param name="angle">
        /// The angle of rotation in radians.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<TupleType T>
            requires IsCompatible<T, Vector>
        static QuaternionSimd FromNormalizedAxisAndAngle( const T& normalizedAxis, float angle ) noexcept
        {
            return FromNormalizedAxisAndAngle( normalizedAxis.ToSimd( ), angle );
        }

        /// <summary>
        /// Creates a rotation quaternion around an axis.
        /// </summary>
        /// <param name="normalizedAxis">
        /// A vector describing the axis of rotation.
        /// </param>
        /// <param name="angle">
        /// The angle of rotation in radians.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        //template<SimdType T>
        //    requires IsCompatible<T, Vector>
        static QuaternionSimd FromAxisAndAngle( const Math::Vector<float, 3>::Simd& axis, float angle ) noexcept
        {
            return FromNormalizedAxisAndAngle( Normalize( axis ), angle );
        }
        /// <summary>
        /// Creates a rotation quaternion around an axis.
        /// </summary>
        /// <param name="normalizedAxis">
        /// A vector describing the axis of rotation.
        /// </param>
        /// <param name="angle">
        /// The angle of rotation in radians.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        //template<TupleType T>
        //    requires IsCompatible<T, Vector>
        static QuaternionSimd FromAxisAndAngle( const Math::Vector<float, 3>& axis, float angle ) noexcept
        {
            return FromNormalizedAxisAndAngle( Normalize( axis ), angle );
        }

        /// <summary>
        /// Creates a rotation quaternion from a rotation matrix.
        /// </summary>
        /// <param name="matrix">
        /// The rotation matrix.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<size_t N>
            requires ( N > 2 )
        static QuaternionSimd FromMatrix( const std::array<SIMDType, N>& matrix ) noexcept;

        /// <summary>
        /// Creates a rotation quaternion from a rotation matrix.
        /// </summary>
        /// <param name="matrix">
        /// The rotation matrix.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        static QuaternionSimd FromMatrix( const MatrixSimd& matrix ) noexcept
        {
            return FromMatrix( matrix.simd );
        }
        /// <summary>
        /// Creates a rotation quaternion from a rotation matrix.
        /// </summary>
        /// <param name="matrix">
        /// The rotation matrix.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        static QuaternionSimd FromMatrix( const Matrix& matrix ) noexcept;


        /// <summary>
        /// Creates the shortest-arc rotation between two directions
        /// </summary>
        /// <param name="fromDir">
        /// The from direction.
        /// </param>
        /// /// <param name="toDir">
        /// The to direction.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<SimdType T, SimdType U>
            requires IsCompatible<T, VectorSimd, U>
        static QuaternionSimd ShortestArc( const T& fromDir, const U& toDir ) noexcept
        {
            const auto fromDirNormalized = Normalize( fromDir );
            const auto toDirNormalized = Normalize( toDir );

            const auto dot = Traits::Dot<0b0111'1111>( fromDirNormalized.simd, toDirNormalized.simd );
            const auto dotf = Traits::First( dot );
            if ( dotf >= 1.f )
            {
                return Identity( );
            }
            else if ( dotf <= -1.f )
            {
                auto axis = Cross( fromDirNormalized, T::Right( ) );
                if ( AllEqual( LengthSquared( axis ), T::Zero( ), T( T::Traits::Constants::Epsilon ) ) )
                {
                    axis = Cross( fromDirNormalized, T::Up( ) );
                }

                return FromAxisAndAngle( axis, T::Traits::Constants::Base::Pi );
            }
            else
            {
                QuaternionSimd result( Cross( fromDirNormalized, toDirNormalized ).simd );
                auto s = Traits::Sqrt( Traits::Mul( Traits::Add( Traits::Fill( 1.f ), dot ), Traits::Fill( 2.f ) ) );

                result.simd = Traits::Div( result.simd, s );
                s = Traits::Mul( s, Traits::Fill( 0.5f ) );
                result.simd = Traits::Permute<0, 1, 2, 7>( result.simd, s );
                return result;
            }
        }

        /// <summary>
        /// Creates the shortest-arc rotation between two directions
        /// </summary>
        /// <param name="fromDir">
        /// The from direction.
        /// </param>
        /// /// <param name="toDir">
        /// The to direction.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<SimdType T, TupleType U>
            requires IsCompatible<T, VectorSimd, U>
        static QuaternionSimd ShortestArc( const T& fromDir, const U& toDir ) noexcept
        {
            return ShortestArc( fromDir, toDir.ToSimd( ) );
        }
        /// <summary>
        /// Creates the shortest-arc rotation between two directions
        /// </summary>
        /// <param name="fromDir">
        /// The from direction.
        /// </param>
        /// /// <param name="toDir">
        /// The to direction.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<TupleType T, SimdType U>
            requires IsCompatible<T, VectorSimd, U>
        static QuaternionSimd ShortestArc( const T& fromDir, const U& toDir ) noexcept
        {
            return ShortestArc( fromDir.ToSimd( ), toDir );
        }
        /// <summary>
        /// Creates the shortest-arc rotation between two directions
        /// </summary>
        /// <param name="fromDir">
        /// The from direction.
        /// </param>
        /// /// <param name="toDir">
        /// The to direction.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<TupleType T, TupleType U>
            requires IsCompatible<T, VectorSimd, U>
        static QuaternionSimd ShortestArc( const T& fromDir, const U& toDir ) noexcept
        {
            return ShortestArc( fromDir.ToSimd( ), toDir.ToSimd( ) );
        }






        /// <summary>
        /// Returns the identity quaternion.
        /// </summary>
        /// <returns>
        /// The identity quaternion.
        /// </returns>
        static constexpr QuaternionSimd Identity( ) noexcept
        {
            constexpr SIMDType identity = { {0.f,0.f,0.f,1.f} };
            return QuaternionSimd( identity );
        }

        /// <summary>
        /// Returns a quaternion with all elements set to zero.
        /// </summary>
        /// <returns>
        /// A quaternion with all elements set to zero.
        /// </returns>
        static constexpr QuaternionSimd Zero( ) noexcept
        {
            constexpr SIMDType zero = { {0.f,0.f,0.f,0.f} };
            return QuaternionSimd( zero );
        }


        QuaternionSimd& operator = ( const QuaternionSimd& other ) noexcept
        {
            simd = other.simd;
            return *this;
        }

        QuaternionSimd& operator = ( SIMDType other ) noexcept
        {
            simd = other;
            return *this;
        }

        QuaternionSimd& operator = ( const QuaternionType& quaternion ) noexcept;

        bool operator == ( const QuaternionSimd& other ) const noexcept
        {
            return Traits::AllEqual( simd, other.simd );
        }

        bool operator != ( const QuaternionSimd& other ) const noexcept
        {
            return Traits::AllEqual( simd, other.simd ) == false;
        }

        bool operator == ( const QuaternionType& other ) const noexcept;
        bool operator != ( const QuaternionType& other ) const noexcept;


        QuaternionSimd operator - ( ) const noexcept
        {
            return QuaternionSimd( Traits::Negate( simd ) );
        }

        QuaternionSimd& operator += ( const QuaternionSimd& other ) noexcept
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }

        QuaternionSimd& operator += ( ValueType value ) noexcept
        {
            auto zero = static_cast< ValueType >( 0. );
            simd = Traits::Add( simd, Traits::Set( value, zero, zero, zero ) );
            return *this;
        }

        QuaternionSimd& operator += ( const QuaternionType& quaternion ) noexcept;

        QuaternionSimd& operator -= ( const QuaternionSimd& other ) noexcept;

        QuaternionSimd& operator -= ( ValueType value ) noexcept
        {
            auto zero = static_cast< ValueType >( 0. );
            simd = Traits::Sub( simd, Traits::Set( value, zero, zero, zero ) );
            return *this;
        }

        QuaternionSimd& operator -= ( const QuaternionType& quaternion ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Load( quaternion.values ) );
            return *this;
        }

        QuaternionSimd& operator *= ( const QuaternionSimd& other ) noexcept
        {
            simd = Traits::QuaternionMultiply( simd, other.simd );
            return *this;
        }

        QuaternionSimd& operator *= ( ValueType value ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Fill( value ) );
            return *this;
        }

        QuaternionSimd& operator *= ( const QuaternionType& quaternion ) noexcept;

        QuaternionSimd& operator /= ( ValueType value ) noexcept
        {
            simd = Traits::Div( simd, Traits::Fill( value ) );
            return *this;
        }

        /// <summary>
        /// Computes rotation about y-axis (y), then x-axis (x), then z-axis (z)
        /// </summary>
        /// <returns>
        /// The rotation about y-axis (y), then x-axis (x), then z-axis (z)
        /// </returns>
        inline VectorSimd ToEuler( ) const noexcept;

    };

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T">
    /// </typeparam>
    template<FloatingPointType T>
    class Quaternion : public Internal::QuaternionBase
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 4;

        using Traits = SIMD::Traits<ValueType, Size>;
        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Capacity = Size;
        using ArrayType = typename Traits::ArrayType;

        using reference = typename ArrayType::reference;
        using const_reference = typename ArrayType::const_reference;
        using pointer = typename ArrayType::pointer;
        using const_pointer = typename ArrayType::const_pointer;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
        using reverse_iterator = typename ArrayType::reverse_iterator;
        using const_reverse_iterator = typename ArrayType::const_reverse_iterator;

        using Simd = QuaternionSimd<Quaternion>;

        using Vector = typename Vector<value_type, 3>;
        using VectorSimd = typename Vector::Simd;
        using Normal = Normal3f;
        using NormalSimd = typename Normal::Simd;

        using Matrix = SquareMatrix<ValueType, 4>;
        using MatrixSimd = SquareMatrixSimd<Matrix, 4>;

        union
        {
            ArrayType values;
            struct
            {
                Vector v;
                ValueType w;
            };
        };


        constexpr Quaternion( ) noexcept
            : values{}
        {
        }
        constexpr Quaternion( ValueType xv, ValueType yv, ValueType zv, ValueType wv ) noexcept
            : values( { xv, yv, zv, wv } )
        {
        }

        constexpr Quaternion( const ArrayType& a ) noexcept
            : values( a )
        {
        }

        template<TupleType T>
            requires IsCompatible<T, Vector>
        constexpr Quaternion( const T& xyz, ValueType wv ) noexcept
            : v( xyz ), w( wv )
        {
        }

        template<SimdType T>
            requires IsCompatible<T, Vector>
        constexpr Quaternion( const T& xyz, ValueType wv ) noexcept
            : v( xyz ), w( wv )
        {
        }

        Quaternion( const Simd& qsimd ) noexcept
            : values( Traits::ToArray( qsimd.simd ) )
        {
        }

        /// <summary>
        /// Creates a quaternion based on the pitch, yaw, and roll (Euler angles).
        /// </summary>
        /// <param name="pitch">
        /// Angle of rotation around the x-axis, in radians.
        /// </param>
        /// <param name="yaw">
        /// Angle of rotation around the y-axis, in radians.
        /// </param>
        /// <param name="roll">
        /// Angle of rotation around the z-axis, in radians.
        /// </param>
        Quaternion( ValueType pitch, ValueType yaw, ValueType roll ) noexcept
        {
            if constexpr ( std::is_same_v<value_type, float> )
            {
                using Traits = SIMD::Traits<float, 4>;
                constexpr SIMDType sign = { { static_cast< value_type >( 1.0 ), static_cast< value_type >( -1.0 ), static_cast< value_type >( -1.0 ), static_cast< value_type >( 1.0 ) } };
                constexpr SIMDType oneHalf = { {static_cast< value_type >( 0.5 ),static_cast< value_type >( 0.5 ),static_cast< value_type >( 0.5 ),static_cast< value_type >( 0.5 )} };

                auto pitchYawRoll = Traits::Set( roll, yaw, pitch );

                auto halfPitchYawRoll = Traits::Mul( pitchYawRoll, oneHalf );

                SIMDType cosines;
                auto sines = Traits::FastSinCos( halfPitchYawRoll, &cosines );
                using P = typename Traits::PermuteType;

                auto p0 = Traits::Permute<P::X1, P::X2, P::X2, P::X2>( sines, cosines );
                auto y0 = Traits::Permute<P::Y2, P::Y1, P::Y2, P::Y2>( sines, cosines );
                auto r0 = Traits::Permute<P::Z2, P::Z2, P::Z1, P::Z2>( sines, cosines );
                auto p1 = Traits::Permute<P::X1, P::X2, P::X2, P::X2>( cosines, sines );
                auto y1 = Traits::Permute<P::Y2, P::Y1, P::Y2, P::Y2>( cosines, sines );
                auto r1 = Traits::Permute<P::Z2, P::Z2, P::Z1, P::Z2>( cosines, sines );

                auto q1 = Traits::Mul( p1, sign );
                auto q0 = Traits::Mul( p0, y0 );
                q1 = Traits::Mul( q1, y1 );
                q0 = Traits::Mul( q0, r0 );
                auto simd = Traits::FMAdd( q1, r1, q0 );
                values = Traits::ToArray( simd );
            }
        }

        Quaternion( const Quaternion& other ) noexcept
            : values( other.values )
        {
        }

        /// <summary>
        /// Creates a rotation quaternion around a normalized axis.
        /// </summary>
        /// <param name="normalizedAxis">
        /// A normalized vector describing the axis of rotation.
        /// </param>
        /// <param name="angle">
        /// The angle of rotation in radians.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<SimdType T>
            requires IsCompatible<T, VectorSimd>
        static Simd FromNormalizedAxisAndAngle( const T& normalizedAxis, float angle ) noexcept
        {
            return Simd::FromNormalizedAxisAndAngle( normalizedAxis, angle );
        }

        /// <summary>
        /// Creates a rotation quaternion around a normalized axis.
        /// </summary>
        /// <param name="normalizedAxis">
        /// A normalized vector describing the axis of rotation.
        /// </param>
        /// <param name="angle">
        /// The angle of rotation in radians.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<TupleType T>
            requires IsCompatible<T, Vector>
        static Simd FromNormalizedAxisAndAngle( const T& normalizedAxis, float angle ) noexcept
        {
            return Simd::FromNormalizedAxisAndAngle( normalizedAxis, angle );
        }

        /// <summary>
        /// Creates a rotation quaternion around an axis.
        /// </summary>
        /// <param name="normalizedAxis">
        /// A vector describing the axis of rotation.
        /// </param>
        /// <param name="angle">
        /// The angle of rotation in radians.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<SimdType T>
            requires IsCompatible<T, VectorSimd>
        static Simd FromAxisAndAngle( const T& axis, float angle ) noexcept
        {
            return Simd::FromAxisAndAngle( axis, angle );
        }

        /// <summary>
        /// Creates a rotation quaternion around an axis.
        /// </summary>
        /// <param name="normalizedAxis">
        /// A vector describing the axis of rotation.
        /// </param>
        /// <param name="angle">
        /// The angle of rotation in radians.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<TupleType T>
            requires IsCompatible<T, Vector>
        static Simd FromAxisAndAngle( const T& axis, float angle ) noexcept
        {
            return Simd::FromAxisAndAngle( axis, angle );
        }

        /// <summary>
        /// Creates a rotation quaternion from a rotation matrix.
        /// </summary>
        /// <param name="matrix">
        /// The rotation matrix.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        static Simd FromMatrix( const MatrixSimd& matrix ) noexcept
        {
            return Simd::FromMatrix( matrix );
        }
        /// <summary>
        /// Creates a rotation quaternion from a rotation matrix.
        /// </summary>
        /// <param name="matrix">
        /// The rotation matrix.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        static Simd FromMatrix( const Matrix& matrix ) noexcept
        {
            return Simd::FromMatrix( matrix );
        }


        /// <summary>
        /// Creates the shortest-arc rotation between two directions
        /// </summary>
        /// <param name="fromDir">
        /// The from direction.
        /// </param>
        /// /// <param name="toDir">
        /// The to direction.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<SimdType T, SimdType U>
            requires IsCompatible<T, VectorSimd, U>
        static Simd ShortestArc( const T& fromDir, const U& toDir ) noexcept
        {
            return Simd::ShortestArc( fromDir, toDir );
        }

        /// <summary>
        /// Creates the shortest-arc rotation between two directions
        /// </summary>
        /// <param name="fromDir">
        /// The from direction.
        /// </param>
        /// /// <param name="toDir">
        /// The to direction.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<SimdType T, TupleType U>
            requires IsCompatible<T, VectorSimd, U>
        static Simd ShortestArc( const T& fromDir, const U& toDir ) noexcept
        {
            return Simd::ShortestArc( fromDir, toDir );
        }

        /// <summary>
        /// Creates the shortest-arc rotation between two directions
        /// </summary>
        /// <param name="fromDir">
        /// The from direction.
        /// </param>
        /// /// <param name="toDir">
        /// The to direction.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<TupleType T, SimdType U>
            requires IsCompatible<T, VectorSimd, U>
        static Simd ShortestArc( const T& fromDir, const U& toDir ) noexcept
        {
            return Simd::ShortestArc( fromDir, toDir );
        }

        /// <summary>
        /// Creates the shortest-arc rotation between two directions
        /// </summary>
        /// <param name="fromDir">
        /// The from direction.
        /// </param>
        /// /// <param name="toDir">
        /// The to direction.
        /// </param>
        /// <returns>
        /// The rotation quaternion.
        /// </returns>
        template<TupleType T, TupleType U>
            requires IsCompatible<T, VectorSimd, U>
        static Simd ShortestArc( const T& fromDir, const U& toDir ) noexcept
        {
            return Simd::ShortestArc( fromDir, toDir );
        }

        /// <summary>
        /// Returns the identity quaternion.
        /// </summary>
        /// <returns>
        /// The identity quaternion.
        /// </returns>
        static constexpr Quaternion Identity( ) noexcept
        {
            return Quaternion( static_cast< ValueType >( 0. ), static_cast< ValueType >( 0. ), static_cast< ValueType >( 0. ), static_cast< ValueType >( 1. ) );
        }

        struct AxisAngle
        {
            Vector Axis;
            value_type Angle;
        };

        /// <summary>
        /// Returns the axis and angle of rotation about 
        /// that axis for the quaternion.
        /// </summary>
        /// <returns></returns>
        AxisAngle ToAxisAngle( ) const noexcept
        {
            return AxisAngle{ .Axis = v, .Angle = static_cast< ValueType >( 2. ) * ACos( w ) };
        }


        /// <summary>
        /// Computes rotation about y-axis (y), then x-axis (x), then z-axis (z)
        /// </summary>
        /// <returns>
        /// The rotation about y-axis (y), then x-axis (x), then z-axis (z)
        /// </returns>
        /// <remarks>
        /// Adopted from https://github.com/microsoft/DirectXTK12
        /// </remarks>
        VectorSimd ToEuler( ) const noexcept
        {
            const float xx = Sqr( v.x );
            const float yy = Sqr( v.y );
            const float zz = Sqr( v.z );

            const float m31 = 2.f * v.x * v.z + 2.f * v.y * v.w;
            const float m32 = 2.f * v.y * v.z - 2.f * v.x * v.w;
            const float m33 = 1.f - 2.f * xx - 2.f * yy;

            const float cy = Sqrt( m33 * m33 + m31 * m31 );
            const float cx = ATan2( -m32, cy );
            if ( cy > 16.f * FLT_EPSILON )
            {
                const float m12 = 2.f * v.x * v.y + 2.f * v.z * v.w;
                const float m22 = 1.f - 2.f * xx - 2.f * zz;

                return VectorSimd( cx, ATan2( m31, m33 ), ATan2( m12, m22 ) );
            }
            else
            {
                const float m11 = 1.f - 2.f * yy - 2.f * zz;
                const float m21 = 2.f * v.x * v.y - 2.f * v.z * v.w;

                return VectorSimd( cx, 0.f, ATan2( -m21, m11 ) );
            }
        }


        Quaternion& operator = ( const Simd& qsimd ) noexcept
        {
            values = Traits::ToArray( qsimd.simd );
            return *this;
        }

        Quaternion& operator = ( const Quaternion& other ) noexcept
        {
            values = other.values;
            return *this;
        }


        Simd ToSimd( ) const noexcept
        {
            return Simd( Traits::Load( values ) );
        }

        operator Simd( ) const noexcept
        {
            return ToSimd( );
        }

        bool operator == ( const Simd& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values ), other.simd );
        }

        bool operator != ( const Simd& other ) const noexcept
        {
            return Traits::AnyNotEqual( Traits::Load( values ), other.simd );
        }

        bool operator == ( const Quaternion& other ) const noexcept
        {
            return values == other.values;
        }
        bool operator != ( const Quaternion& other ) const noexcept
        {
            return values != other.values;
        }

        Simd operator - ( ) const noexcept
        {
            return Simd( Traits::Negate( Traits::Load( values ) ) );
        }

        const_reference operator[]( size_t index ) const noexcept
        {
            return values[ index ];
        }

        reference operator[]( size_t index ) noexcept
        {
            return values[ index ];
        }

        const_pointer data( ) const noexcept
        {
            return values.data( );
        }
        pointer data( ) noexcept
        {
            return values.data( );
        }

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }

        const_reference front( ) const noexcept
        {
            return values.front( );
        }
        reference front( ) noexcept
        {
            return values.front( );
        }

        const_reference back( ) const noexcept
        {
            return values.back( );
        }
        reference back( ) noexcept
        {
            return values.back( );
        }

        const_iterator begin( ) const noexcept
        {
            return values.begin( );
        }
        const_iterator cbegin( ) const noexcept
        {
            return values.cbegin( );
        }
        iterator begin( ) noexcept
        {
            return values.begin( );
        }
        const_iterator end( ) const noexcept
        {
            return values.end( );
        }
        const_iterator cend( ) const noexcept
        {
            return values.cend( );
        }
        iterator end( ) noexcept
        {
            return values.end( );
        }
        const_reverse_iterator rbegin( ) const noexcept
        {
            return values.rbegin( );
        }
        reverse_iterator rbegin( ) noexcept
        {
            return values.rbegin( );
        }
        const_reverse_iterator rend( ) const noexcept
        {
            return values.rend( );
        }
        reverse_iterator rend( ) noexcept
        {
            return values.rend( );
        }




    };

    static_assert( sizeof( Quaternion<float> ) == sizeof( std::array<float, 4> ) );

    template<typename QuaternionT>
    inline QuaternionSimd<QuaternionT>::QuaternionSimd( const QuaternionType& quaternion ) noexcept
        : simd( Traits::Load( quaternion.values ) )
    {
    }

    template<typename QuaternionT>
    inline QuaternionSimd<QuaternionT>& QuaternionSimd<QuaternionT>::operator = ( const QuaternionType& quaternion ) noexcept
    {
        simd = Traits::Load( quaternion.values );
        return *this;
    }

    template<typename QuaternionT>
    inline bool QuaternionSimd<QuaternionT>::operator == ( const QuaternionType& other ) const noexcept
    {
        return Traits::AllEqual( simd, Traits::Load( other.values ) );
    }
    template<typename QuaternionT>
    inline bool QuaternionSimd<QuaternionT>::operator != ( const QuaternionType& other ) const noexcept
    {
        return Traits::AllEqual( simd, Traits::Load( other.values ) ) == false;
    }

    template<typename QuaternionT>
    inline QuaternionSimd<QuaternionT>& QuaternionSimd<QuaternionT>::operator += ( const QuaternionType& quaternion ) noexcept
    {
        simd = Traits::Add( simd, Traits::Load( quaternion.values ) );
        return *this;
    }

    template<typename QuaternionT>
    inline QuaternionSimd<QuaternionT>& QuaternionSimd<QuaternionT>::operator -= ( const QuaternionSimd& other ) noexcept
    {
        simd = Traits::Sub( simd, other.simd );
        return *this;
    }

    template<typename QuaternionT>
    inline QuaternionSimd<QuaternionT>& QuaternionSimd<QuaternionT>::operator *= ( const QuaternionType& quaternion ) noexcept
    {
        simd = Traits::QuaternionMultiply( simd, Traits::Load( quaternion.values ) );
        return *this;
    }

    template<typename QuaternionT>
    inline typename QuaternionSimd<QuaternionT>::VectorSimd QuaternionSimd<QuaternionT>::ToEuler( ) const noexcept
    {
        QuaternionT q( *this );
        return q.ToEuler( );
    }


    // Addition

    template<QuaternionOrQuaternionSimdType T, QuaternionOrQuaternionSimdType U>
        requires IsCompatibleQuaternion<T, U>
    auto operator + ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        return ResultType( Traits::Add( Internal::ToSimd( q1 ), Internal::ToSimd( q2 ) ) );
    }

    // Scalar Addition

    template<QuaternionOrQuaternionSimdType T, ArithmeticType U>
    auto operator + ( const T& q1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        using ResultType = typename T::Simd;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        return ResultType( Traits::Add( Internal::ToSimd( q1 ), Traits::Set( v, zero, zero, zero ) ) );
    }
    template<ArithmeticType T, QuaternionOrQuaternionSimdType U>
    auto operator + ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using FloatT = typename Traits::Type;
        using ResultType = typename U::Simd;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        return ResultType( Traits::Add( Traits::Set( v, zero, zero, zero ), Internal::ToSimd( q2 ) ) );
    }

    // Subtraction

    template<QuaternionOrQuaternionSimdType T, QuaternionOrQuaternionSimdType U>
        requires IsCompatibleQuaternion<T, U>
    auto operator - ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        return ResultType( Traits::Sub( Internal::ToSimd( q1 ), Internal::ToSimd( q2 ) ) );
    }

    // Scalar Subtraction

    template<QuaternionOrQuaternionSimdType T, ArithmeticType U>
    auto operator - ( const T& q1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        using ResultType = typename T::Simd;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        return ResultType( Traits::Sub( Internal::ToSimd( q1 ), Traits::Set( v, zero, zero, zero ) ) );
    }

    template<ArithmeticType T, QuaternionOrQuaternionSimdType U>
    auto operator - ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using FloatT = typename Traits::Type;
        using ResultType = typename U::Simd;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        auto q2simd = Internal::ToSimd( q2 );
        auto tmp = Traits::Sub( Traits::Set( v, zero, zero, zero ), q2simd );
        return ResultType( Traits::Permute<4, 5, 6, 3>( tmp, q2simd ) );
    }

    // Multiplication

    template<QuaternionOrQuaternionSimdType T, QuaternionOrQuaternionSimdType U>
        requires IsCompatibleQuaternion<T, U>
    auto operator * ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        return ResultType( Traits::QuaternionMultiply( Internal::ToSimd( q1 ), Internal::ToSimd( q2 ) ) );
    }

    // Scalar Multiplication

    template<ArithmeticType T, QuaternionOrQuaternionSimdType U>
    auto operator * ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using FloatT = typename Traits::Type;
        using ResultType = typename U::Simd;
        return ResultType( Traits::Mul( Traits::Fill( static_cast< FloatT >( value ) ), Internal::ToSimd( q2 ) ) );
    }
    template<QuaternionOrQuaternionSimdType T, ArithmeticType U>
    auto operator * ( const T& q1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        using ResultType = typename T::Simd;
        return ResultType( Traits::Mul( Internal::ToSimd( q1 ), Traits::Fill( static_cast< FloatT >( value ) ) ) );
    }

    // Scalar Division

    template<QuaternionOrQuaternionSimdType T, ArithmeticType U>
    auto operator / ( const T& q1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        using ResultType = typename T::Simd;
        return ResultType( Traits::Div( Internal::ToSimd( q1 ), Traits::Fill( static_cast< FloatT >( value ) ) ) );
    }

    template<ArithmeticType T, QuaternionOrQuaternionSimdType U>
    auto operator / ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using FloatT = typename Traits::Type;
        using ResultType = typename U::Simd;
        return ResultType( Traits::Div( Traits::Fill( static_cast< FloatT >( value ) ), Internal::ToSimd( q2 ) ) );
    }


    /// <summary>
    /// Calculates the dot product of two quaternions.
    /// </summary>
    /// <param name="q1">
    /// The first quaternion.
    /// </param>
    /// <param name="q2">
    /// The second quaternion.
    /// </param>
    /// <returns>
    /// The dot product between q1 and q2.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T, QuaternionOrQuaternionSimdType U>
        requires IsCompatibleQuaternion<T, U>
    auto Dot( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        return ResultType( Traits::Dot( Internal::ToSimd( q1 ), Internal::ToSimd( q2 ) ) );
    }

    /// <summary>
    /// Calculates the dot product of two quaternions.
    /// </summary>
    /// <param name="q1">
    /// The first quaternion.
    /// </param>
    /// <param name="q2">
    /// The second quaternion.
    /// </param>
    /// <returns>
    /// The dot product between q1 and q2.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T, QuaternionOrQuaternionSimdType U>
        requires IsCompatibleQuaternion<T, U>
    auto ScalarDot( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Traits::Dot( Internal::ToSimd( q1 ), Internal::ToSimd( q2 ) ) );
    }


    // Length

    /// <summary>
    /// Calculates the magnitude of a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The magnitude of the quaternion.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto Length( const T& q ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        auto qSimd = Internal::ToSimd( q );
        return ResultType( Traits::Sqrt( Traits::HSum( Traits::Mul( qSimd, qSimd ) ) ) );
    }

    /// <summary>
    /// Calculates the magnitude of a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The magnitude of the quaternion.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto ScalarLength( const T& q ) noexcept
    {
        using Traits = typename T::Traits;
        auto qSimd = Internal::ToSimd( q );
        return Traits::First( Traits::Sqrt( Traits::HSum( Traits::Mul( qSimd, qSimd ) ) ) );
    }


    // LengthSquared

    /// <summary>
    /// Calculates the square of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The square of the magnitude of the quaternion.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto LengthSquared( const T& q ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        auto qSimd = Internal::ToSimd( q );
        return ResultType( Traits::HSum( Traits::Mul( qSimd, qSimd ) ) );
    }

    /// <summary>
    /// Calculates the square of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The square of the magnitude of the quaternion.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto ScalarLengthSquared( const T& q ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        auto qSimd = Internal::ToSimd( q );
        return Traits::First( Traits::HSum( Traits::Mul( qSimd, qSimd ) ) );
    }



    // ReciprocalLength

    /// <summary>
    /// Calculates the reciprocal of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The reciprocal of the magnitude of the quaternion.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto ReciprocalLength( const T& q1 ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        using ResultType = typename T::Simd;
        auto length = Length( q1 );
        return ResultType( Traits::Div( Traits::Fill( static_cast< Type >( 1. ) ), length.simd ) );
    }

    /// <summary>
    /// Calculates the reciprocal of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The reciprocal of the magnitude of the quaternion.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto ScalarReciprocalLength( const T& q1 ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        auto length = Length( q1 );
        return Traits::First( Traits::Div( Traits::Fill( static_cast< Type >( 1. ) ), length.simd ) );
    }


    // Conjugate

    /// <summary>
    /// Calculates the conjugate of a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The conjugate of the quaternion
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto Conjugate( const T& q ) noexcept
    {
        using Traits = typename T::Traits;
        using SIMDType = typename Traits::SIMDType;
        using ResultType = typename T::Simd;
        constexpr SIMDType flipXYZ = { { -1.0f, -1.0f, -1.0f, 1.0f } };
        return ResultType( Traits::Mul( Internal::ToSimd( q ), flipXYZ ) );
    }

    // Normalize

    /// <summary>
    /// Normalizes a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The normalized quaternion.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto Normalize( const T& q ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        auto v = Length( q );
        return ResultType( Traits::Div( Internal::ToSimd( q ), v.simd ) );
    }

    namespace Internal
    {
        /// <summary>
        /// Calculates the inverse of a quaternion.
        /// </summary>
        /// <param name="q">
        /// The quaternion.
        /// </param>
        /// <returns>
        /// The inverse quaternion.
        /// </returns>
        template<QuaternionSimdType T>
        T InverseImpl( const T& q ) noexcept
        {
            using Traits = typename T::Traits;
            using FloatT = typename Traits::Type;
            using SIMDType = typename Traits::SIMDType;
            using Simd = typename T::Simd;
            constexpr SIMDType epsilon = { {static_cast< FloatT >( 1.192092896e-7 ),static_cast< FloatT >( 1.192092896e-7 ),static_cast< FloatT >( 1.192092896e-7 ),static_cast< FloatT >( 1.192092896e-7 )} };
            constexpr SIMDType zero = { {static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. )} };

            auto l = LengthSquared( q );
            auto conjugate = Conjugate( q );

            auto selectZero = Traits::LessOrEqual( l.simd, epsilon );

            auto result = Traits::Div( conjugate.simd, l.simd );

            return Simd( Traits::Select( result, zero, selectZero ) );
        }
    }

    /// <summary>
    /// Calculates the inverse of a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The inverse quaternion.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto Inverse( const T& q ) noexcept
    {
        return Internal::InverseImpl( Internal::ToSimdType( q ) );
    }


    namespace Internal
    {
        /// <summary>
        /// Calculates the natural logarithm of a unit quaternion.
        /// </summary>
        /// <param name="q1">
        /// The unit quaternion.
        /// </param>
        /// <returns>
        /// The natural logarithm of q1.
        /// </returns>
        template<QuaternionSimdType T>
        T LogImpl( const T& q1 ) noexcept
        {
            using Traits = typename T::Traits;
            using FloatT = typename Traits::Type;
            using SIMDType = typename Traits::SIMDType;
            using Simd = typename T::Simd;
            constexpr SIMDType oneMinusEpsilon = { { static_cast< FloatT >( 1.0 - 0.00001 ), static_cast< FloatT >( 1.0 - 0.00001 ), static_cast< FloatT >( 1.0 - 0.00001 ), static_cast< FloatT >( 1.0 - 0.00001 ) } };
            constexpr SIMDType select1110 = { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0 } };

            auto qw = Traits::At<3>( q1.simd );
            auto qv = Traits::Select( select1110, q1.simd, select1110 );

            auto controlW = Traits::InBounds( qw, oneMinusEpsilon );

            auto theta = Traits::ACos( qw );
            auto sinTheta = Traits::Sin( theta );

            auto s = Traits::Div( theta, sinTheta );

            auto result = Traits::Mul( qv, s );
            return Simd( Traits::Select( qv, result, controlW ) );
        }
    }

    /// <summary>
    /// Calculates the natural logarithm of a unit quaternion.
    /// </summary>
    /// <param name="q">
    /// The unit quaternion.
    /// </param>
    /// <returns>
    /// The natural logarithm of q1.
    /// </returns>
    template<QuaternionOrQuaternionSimdType T>
    auto Log( const T& q ) noexcept
    {
        return Internal::LogImpl( Internal::ToSimdType( q ) );
    }


    /// <summary>
    /// Spherical linear interpolation between two unit quaternions.
    /// </summary>
    /// <param name="q1">
    /// The unit quaternion to interpolate from.
    /// </param>
    /// <param name="q2">
    /// The unit quaternion to interpolate to.
    /// </param>
    /// <param name="t">
    /// Interpolation control factor. Every element of this vector must be set to the same value.
    /// When the elements of t is 0.0, the function returns q1, and when the elements of t is 1.0, the function returns q2.
    /// </param>
    /// <returns></returns>
    template<QuaternionOrQuaternionSimdType T, QuaternionOrQuaternionSimdType U, SimdOrTupleType V>
        requires IsCompatibleQuaternion<T, U> && ( V::Size == 4 )
    auto Slerp( const T& q1, const U& q2, const V& t ) noexcept
    {
        using Traits = typename T::Traits;
        using ResultType = typename T::Simd;
        return ResultType( Traits::Slerp( Internal::ToSimd( q1 ), Internal::ToSimd( q2 ), Internal::ToSimd( t ) ) );
    }

    /// <summary>
    /// Spherical linear interpolation between two unit quaternions.
    /// </summary>
    /// <param name="q1">
    /// The unit quaternion to interpolate from.
    /// </param>
    /// <param name="q2">
    /// The unit quaternion to interpolate to.
    /// </param>
    /// <param name="t">
    /// Interpolation control factor. When the value of t is 0.0, the function returns q1, 
    /// and when the value of t is 1.0, the function returns q2.
    /// </param>
    /// <returns></returns>
    template<QuaternionOrQuaternionSimdType T, QuaternionOrQuaternionSimdType U, ArithmeticType V>
        requires IsCompatibleQuaternion<T, U>
    auto Slerp( const T& q1, const U& q2, const V t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        using ResultType = typename T::Simd;
        return ResultType( Traits::Slerp( Internal::ToSimd( q1 ), Internal::ToSimd( q2 ), Traits::Fill( static_cast< Type >( t ) ) ) );
    }

    namespace Internal
    {
        /// <summary>
        /// Rotates a vector using a quaternion.
        /// </summary>
        /// <param name="v">
        /// The vector to rotate.
        /// </param>
        /// <param name="rotationQuaternion">
        /// Quaternion describing the rotation to apply to the vector.
        /// </param>
        /// <returns>
        /// The rotated vector.
        /// </returns>
        template<SimdType S, QuaternionSimdType T >
            requires ( S::Size == 3 )
        S RotateImpl( const S& v, const T& rotationQuaternion )
        {
            using Traits = typename T::Traits;
            using Constants = typename Traits::Constants;
            using Simd = typename T::Simd;

            Simd a( Traits::Select( Constants::Select2221, v.simd, Constants::Select2221 ) );

            Simd qc = Conjugate( rotationQuaternion );

            Simd qca = qc * a;

            Simd result = qca * rotationQuaternion;

            return S( result.simd );
        }
    }

    /// <summary>
    /// Rotates a vector using a quaternion.
    /// </summary>
    /// <param name="v">
    /// The vector to rotate.
    /// </param>
    /// <param name="rotationQuaternion">
    /// Quaternion describing the rotation to apply to the vector.
    /// </param>
    /// <returns>
    /// The rotated vector.
    /// </returns>
    template<SimdOrTupleType S, QuaternionOrQuaternionSimdType T >
        requires ( S::Size == 3 )
    auto Rotate( const S& v, const T& rotationQuaternion )
    {
        return Internal::RotateImpl( Internal::ToSimdType( v ), Internal::ToSimdType( rotationQuaternion ) );
    }




    namespace Internal
    {
        /// <summary>
        /// Rotates a vector using the inverse of a quaternion.
        /// </summary>
        /// <param name="v">
        /// The vector to rotate.
        /// </param>
        /// <param name="rotationQuaternion">
        /// Quaternion describing the rotation to apply to the vector.
        /// </param>
        /// <returns>
        /// The rotated vector.
        /// </returns>
        template<SimdType S, QuaternionSimdType T >
            requires ( S::Size == 3 )
        S InverseRotateImpl( const S& v, const T& rotationQuaternion )
        {
            using Traits = typename T::Traits;
            using Constants = typename Traits::Constants;
            using Simd = T::Simd;

            Simd qa( Traits::Select( Constants::Select2221, v.simd, Constants::Select2221 ) );

            auto result = rotationQuaternion * qa;
            auto rc = Conjugate( rotationQuaternion );
            return S( ( result * rc ).simd );
        }
    }

    /// <summary>
    /// Rotates a vector using the inverse of a quaternion.
    /// </summary>
    /// <param name="v">
    /// The vector to rotate.
    /// </param>
    /// <param name="rotationQuaternion">
    /// Quaternion describing the rotation to apply to the vector.
    /// </param>
    /// <returns>
    /// The rotated vector.
    /// </returns>
    template<SimdOrTupleType S, QuaternionOrQuaternionSimdType T >
        requires ( S::Size == 3 )
    S InverseRotate( const S& v, const T& rotationQuaternion )
    {
        return Internal::InverseRotateImpl( Internal::ToSimdType( v ), Internal::ToSimdType( rotationQuaternion ) );
    }


    /// <summary>
    /// Creates the shortest-arc rotation between two directions
    /// </summary>
    /// <param name="fromDir">
    /// The from direction.
    /// </param>
    /// /// <param name="toDir">
    /// The to direction.
    /// </param>
    /// <returns>
    /// The rotation quaternion.
    /// </returns>
    template<SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<T, U> && ( T::Size == 3 )
    inline auto ShortestArc( const T& fromDir, const U& toDir ) noexcept
    {
        using q = Quaternion<typename T::value_type>::Simd;
        return q::ShortestArc( fromDir, toDir );
    }



    template<SimdType T, SimdType U>
        requires IsCompatible<T, U>
    constexpr inline auto ScalarAngleBetween( const T& v1, const U& v2 )
    {
        using Traits = typename T::Traits;
        using TupleType = typename T::TupleType;
        using FloatT = typename TupleType::value_type;

        auto dotProduct = Dot( v1, v2 );

        if ( Traits::First( dotProduct.simd ) < 0 )
        {
            TupleType s = Sqr( v1 + v2 );
            auto halfLength = Sqrt( s.x + s.y + s.z ) / static_cast< FloatT >( 2. );
            return Constants<FloatT>::Pi - static_cast< FloatT >( 2. ) * SafeASin( halfLength );
        }
        else
        {
            TupleType s = Sqr( v2 - v1 );
            auto halfLength = Sqrt( s.x + s.y + s.z ) / static_cast< FloatT >( 2. );
            return static_cast< FloatT >( 2. ) * SafeASin( halfLength );
        }
    }

    template<SimdType T, TupleType U>
        requires IsCompatible<T, U>
    constexpr inline auto ScalarAngleBetween( const T& v1, const U& v2 )
    {
        return ScalarAngleBetween( v1, typename U::Simd( v2 ) );
    }

    template<TupleType T, SimdType U>
        requires IsCompatible<T, U>
    constexpr inline auto ScalarAngleBetween( const T& v1, const U& v2 )
    {
        return ScalarAngleBetween( typename T::Simd( v1 ), v2 );
    }



    template<typename DerivedT, typename FloatT>
    constexpr inline FloatT ScalarAngleBetween( const Tuple3<DerivedT, FloatT>& v1, const Tuple3<DerivedT, FloatT>& v2 )
    {
        auto dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

        if ( dotProduct < 0 )
        {
            auto sx = v1.x + v2.x;
            sx *= sx;
            auto sy = v1.y + v2.y;
            sy *= sy;
            auto sz = v1.z + v2.z;
            sz *= sz;

            auto halfLength = Sqrt( sx + sy + sz ) / static_cast< FloatT >( 2. );
            return Constants<FloatT>::Pi - static_cast< FloatT >( 2. ) * SafeASin( halfLength );
        }
        else
        {
            auto sx = v2.x - v1.x;
            sx *= sx;
            auto sy = v2.y - v1.y;
            sy *= sy;
            auto sz = v2.z - v1.z;
            sz *= sz;

            auto halfLength = Sqrt( sx + sy + sz ) / static_cast< FloatT >( 2. );
            return static_cast< FloatT >( 2. ) * SafeASin( halfLength );
        }
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3<DerivedT, FloatT> AngleBetween( const Tuple3<DerivedT, FloatT>& v1, const Tuple3<DerivedT, FloatT>& v2 )
    {
        auto angle = ScalarAngleBetween( v1, v2 );
        return Tuple3<DerivedT, FloatT>( angle, angle, angle );
    }

    namespace Internal
    {
        template <size_t N, size_t... I, typename FloatT, typename... Args>
        constexpr inline void InitMatrix( std::index_sequence<I...>, std::array < std::array<FloatT, N>, N>& dest, Args... args )
        {
            ( ( dest[ I / N ][ I % N ] = static_cast< FloatT >( args ) ), ... );
        }

        template <size_t N, size_t... I, typename FloatT, typename... Args>
        constexpr inline void InitDiagonalMatrix( std::index_sequence<I...>, std::array < std::array<FloatT, N>, N>& dest, Args... args )
        {
            ( ( dest[ I ][ I ] = static_cast< FloatT >( args ) ), ... );
        }

        struct MatrixSimdBase
        {
        };

        struct MatrixBase
        {
        };



    }

    template<typename T>
    concept SquareMatrixSimdType = std::is_base_of_v<Internal::MatrixSimdBase, T>;

    template<typename T>
    concept SquareMatrixType = std::is_base_of_v<Internal::MatrixBase, T>;

    template<typename T>
    concept SquareMatrixOrSquareMatrixSimdType = SquareMatrixType<T> || SquareMatrixSimdType<T>;


    template<typename T, typename ... Other>
    constexpr bool IsCompatibleMatrix = ( ( std::is_same_v<typename T::Traits, typename Other::Traits> && ( T::Size == Other::Size ) ) && ... );

    namespace Internal
    {
        template<SquareMatrixSimdType T>
        const auto& ToSimd( const T& m )
        {
            return m.simd;
        }

        template<SquareMatrixType T>
        auto ToSimd( const T& m )
        {
            return m.ToSimd( ).simd;
        }

        template<SquareMatrixSimdType T>
        const auto& ToSimdType( const T& m )
        {
            return m;
        }

        template<SquareMatrixType T>
        auto ToSimdType( const T& m )
        {
            return m.ToSimd( );
        }

        template<SquareMatrixOrSquareMatrixSimdType ... T>
        constexpr bool HasSquareMatrixSimdType = ( SquareMatrixSimdType<T> || ... );

        template<SquareMatrixOrSquareMatrixSimdType ... T>
        constexpr bool HasSquareMatrixType = ( SquareMatrixType<T> || ... );


    }



    template<typename MatrixT, size_t N>
    struct SquareMatrixSimd
    {
    };

    enum class MatrixType : UInt32
    {
        Zero,
        Identity
    };


    template<typename MatrixT>
    struct alignas( SIMD::Traits<typename MatrixT::value_type, 1>::AlignAs )
        SquareMatrixSimd<MatrixT, 1> : public Internal::MatrixSimdBase
    {
        using MatrixType = MatrixT;
        using value_type = typename MatrixT::value_type;
        using Traits = SIMD::Traits<value_type, 1>;
        using SIMDType = typename Traits::SIMDType;
        using ArrayType = std::array<std::array<value_type, 1>, 1>;
        static constexpr size_t Size = 1;

        SIMDType simd;

        static SIMDType ToSimd( const ArrayType& matrix )
        {
            return Traits::Load( matrix[ 0 ].data( ) );
        }
        static ArrayType ToMatrix( const SquareMatrixSimd& simd )
        {
            ArrayType result;
            Traits::Store( result[ 0 ].data( ), simd.simd );
            return result;
        }

        SquareMatrixSimd( )
        {
        }
        explicit SquareMatrixSimd( SIMDType other )
            : simd( other )
        {
        }
        SquareMatrixSimd( const SquareMatrixSimd& other )
            : simd( other.simd )
        {
        }
        explicit SquareMatrixSimd( const ArrayType& matrix )
            : simd( Traits::Load( matrix[ 0 ].data( ) ) )
        {
        }

        explicit SquareMatrixSimd( const MatrixType& matrix )
            : simd( Traits::Load( matrix[ 0 ].data( ) ) )
        {
        }

    };
    template<typename MatrixT>
    struct alignas( SIMD::Traits<typename MatrixT::value_type, 4>::AlignAs )
        SquareMatrixSimd<MatrixT, 2> : public Internal::MatrixSimdBase
    {
        using MatrixType = MatrixT;
        using value_type = typename MatrixT::value_type;
        using Traits = SIMD::Traits<value_type, 4>;
        using SIMDType = typename Traits::SIMDType;
        using ArrayType = std::array<std::array<value_type, 2>, 2>;
        static constexpr size_t Size = 2;

        static constexpr SIMDType ZeroValues = { { static_cast< value_type >( 0. ), static_cast< value_type >( 0. ),static_cast< value_type >( 0. ),static_cast< value_type >( 0. ) } };
        static constexpr SIMDType IdentityValues = { { static_cast< value_type >( 1. ), static_cast< value_type >( 0. ),static_cast< value_type >( 0. ),static_cast< value_type >( 1. )} };

        SIMDType simd;

        static SIMDType ToSimd( const ArrayType& matrix )
        {
            return Traits::Load( matrix[ 0 ].data( ) );
        }
        static SIMDType ToSimd( const value_type matrix[ Size ][ Size ] )
        {
            return Traits::Load( &matrix[ 0 ][ 0 ] );
        }

        static ArrayType ToMatrix( const SquareMatrixSimd& simd )
        {
            ArrayType result;
            Traits::Store( result[ 0 ].data( ), simd.simd );
            return result;
        }

        SquareMatrixSimd( )
            : simd( ZeroValues )
        {
        }

        explicit SquareMatrixSimd( Math::MatrixType matrixType )
            : simd( matrixType == Math::MatrixType::Identity ? IdentityValues : ZeroValues )
        {
        }

        explicit SquareMatrixSimd( SIMDType other )
            : simd( other )
        {
        }
        SquareMatrixSimd( const SquareMatrixSimd& other )
            : simd( other.simd )
        {
        }
        explicit SquareMatrixSimd( const ArrayType& matrix )
            : simd( Traits::Load( matrix[ 0 ].data( ) ) )
        {
        }

        explicit SquareMatrixSimd( const MatrixType& matrix )
            : simd( Traits::Load( matrix[ 0 ].data( ) ) )
        {
        }

        bool operator == ( const SquareMatrixSimd& other ) const
        {
            return Traits::AllEqual( simd, other.simd );
        }
        bool operator != ( const SquareMatrixSimd& other ) const
        {
            return Traits::AllEqual( simd, other.simd ) == false;
        }

        static SquareMatrixSimd Zero( )
        {
            return SquareMatrixSimd( ZeroValues );
        }

        static SquareMatrixSimd Identity( )
        {
            return SquareMatrixSimd( IdentityValues );
        }

        bool IsIdentity( ) const
        {
            return Traits::AllEqual( simd, IdentityValues );
        }
    };


    template<typename MatrixT>
    struct alignas( SIMD::Traits<typename MatrixT::value_type, 3>::AlignAs )
        SquareMatrixSimd<MatrixT, 3> : public Internal::MatrixSimdBase
    {
        using MatrixType = MatrixT;
        using value_type = typename MatrixT::value_type;
        using Traits = SIMD::Traits<value_type, 3>;
        using Constants = typename Traits::Constants;
        using SIMDType = typename Traits::SIMDType;
        using ArrayType = std::array<std::array<value_type, 3>, 3>;
        static constexpr size_t Size = 3;

        std::array<SIMDType, 3> simd;

        static constexpr std::array<SIMDType, 3> ZeroValues{ Traits::Constants::Zero, Traits::Constants::Zero, Traits::Constants::Zero };
        static constexpr std::array<SIMDType, 3> IdentityValues{ Traits::Constants::IdentityR1, Traits::Constants::IdentityR2, Traits::Constants::IdentityR3 };

        static std::array<SIMDType, 3> ToSimd( const ArrayType& matrix )
        {
            std::array<SIMDType, 3> result;
            result[ 0 ] = Traits::Load( matrix[ 0 ] );
            result[ 1 ] = Traits::Load( matrix[ 1 ] );
            result[ 2 ] = Traits::Load( matrix[ 2 ] );
            return result;
        }
        static std::array<SIMDType, 3> ToSimd( const value_type matrix[ Size ][ Size ] )
        {
            std::array<SIMDType, 3> result;
            result[ 0 ] = Traits::Load( matrix[ 0 ] );
            result[ 1 ] = Traits::Load( matrix[ 1 ] );
            result[ 2 ] = Traits::Load( matrix[ 2 ] );
            return result;
        }

        static ArrayType ToMatrix( const SquareMatrixSimd& simd )
        {
            ArrayType result;
            Traits::Store( result[ 0 ].data( ), simd.simd[ 0 ] );
            Traits::Store( result[ 1 ].data( ), simd.simd[ 1 ] );
            Traits::Store( result[ 2 ].data( ), simd.simd[ 2 ] );
            return result;
        }

        SquareMatrixSimd( )
            : simd( ZeroValues )
        {
        }

        explicit SquareMatrixSimd( Math::MatrixType matrixType )
            : simd( matrixType == Math::MatrixType::Identity ? IdentityValues : ZeroValues )
        {
        }

        explicit SquareMatrixSimd( const std::array<SIMDType, 3>& other )
            : simd( other )
        {
        }

        explicit SquareMatrixSimd( const std::array<SIMDType, 4>& other )
            : simd
            {
                Traits::And( other[ 0 ], Traits::Constants::Mask3 ),
                Traits::And( other[ 1 ], Traits::Constants::Mask3 ),
                Traits::And( other[ 2 ], Traits::Constants::Mask3 )
            }
        {
        }

        explicit SquareMatrixSimd( const SIMDType r1, const SIMDType r2, const SIMDType r3 )
            : simd{ r1, r2, r3 }
        {
        }

        SquareMatrixSimd( const SquareMatrixSimd& other )
            : simd( other.simd )
        {
        }
        explicit SquareMatrixSimd( const ArrayType& matrix )
            : simd{ Traits::Load( matrix[ 0 ] ), Traits::Load( matrix[ 1 ] ), Traits::Load( matrix[ 2 ] ) }
        {
        }

        explicit SquareMatrixSimd( const MatrixType& matrix )
            : simd{ Traits::Load( matrix[ 0 ] ), Traits::Load( matrix[ 1 ] ), Traits::Load( matrix[ 2 ] ) }
        {
        }




        bool operator == ( const SquareMatrixSimd& other ) const
        {
            return Traits::AllEqual( simd[ 0 ], other.simd[ 0 ] ) &&
                Traits::AllEqual( simd[ 1 ], other.simd[ 1 ] ) &&
                Traits::AllEqual( simd[ 2 ], other.simd[ 2 ] );
        }
        bool operator != ( const SquareMatrixSimd& other ) const
        {
            return Traits::AllEqual( simd[ 0 ], other.simd[ 0 ] ) == false ||
                Traits::AllEqual( simd[ 1 ], other.simd[ 1 ] ) == false ||
                Traits::AllEqual( simd[ 2 ], other.simd[ 2 ] ) == false;
        }

        bool IsIdentity( ) const
        {
            return Traits::AllEqual( simd[ 0 ], Constants::IdentityR1 ) &&
                Traits::AllEqual( simd[ 1 ], Constants::IdentityR2 ) &&
                Traits::AllEqual( simd[ 2 ], Constants::IdentityR3 );
        }

        static SquareMatrixSimd Zero( )
        {
            return SquareMatrixSimd( ZeroValues );
        }

        static SquareMatrixSimd Identity( )
        {
            return SquareMatrixSimd( IdentityValues );
        }

        template<SimdType S>
            requires ( S::Size > 2 )
        SquareMatrixSimd operator * ( const S& v ) const noexcept
        {
            std::array<SIMDType, 3> result;
            result[ 0 ] = Traits::Mul( simd[ 0 ], v.simd );
            result[ 1 ] = Traits::Mul( simd[ 1 ], v.simd );
            result[ 2 ] = Traits::Mul( simd[ 2 ], v.simd );
            return SquareMatrixSimd( result );
        }

    };


    template<typename MatrixT>
    struct alignas( SIMD::Traits<typename MatrixT::value_type, 4>::AlignAs )
        SquareMatrixSimd<MatrixT, 4> : public Internal::MatrixSimdBase
    {
        using MatrixType = MatrixT;
        using value_type = typename MatrixT::value_type;
        using Traits = SIMD::Traits<value_type, 4>;
        using Constants = typename Traits::Constants;
        using SIMDType = typename Traits::SIMDType;
        using ArrayType = std::array<std::array<value_type, 4>, 4>;
        static constexpr size_t Size = 4;

        std::array<SIMDType, 4> simd;

        static constexpr std::array<SIMDType, 4> ZeroValues{ Traits::Constants::Zero, Traits::Constants::Zero, Traits::Constants::Zero, Traits::Constants::Zero };
        static constexpr std::array<SIMDType, 4> IdentityValues{ Traits::Constants::IdentityR1, Traits::Constants::IdentityR2, Traits::Constants::IdentityR3, Traits::Constants::IdentityR4 };

        static std::array<SIMDType, 4> ToSimd( const ArrayType matrix )
        {
            std::array<SIMDType, 4> result;
            result[ 0 ] = Traits::Load( matrix[ 0 ] );
            result[ 1 ] = Traits::Load( matrix[ 1 ] );
            result[ 2 ] = Traits::Load( matrix[ 2 ] );
            result[ 3 ] = Traits::Load( matrix[ 3 ] );
            return result;
        }

        static std::array<SIMDType, 4> ToSimd( const value_type matrix[ Size ][ Size ] )
        {
            std::array<SIMDType, 4> result;
            result[ 0 ] = Traits::Load( matrix[ 0 ] );
            result[ 1 ] = Traits::Load( matrix[ 1 ] );
            result[ 2 ] = Traits::Load( matrix[ 2 ] );
            result[ 3 ] = Traits::Load( matrix[ 3 ] );
            return result;
        }

        static ArrayType ToMatrix( const SquareMatrixSimd& simd )
        {
            ArrayType result;
            Traits::Store( result[ 0 ].data( ), simd.simd[ 0 ] );
            Traits::Store( result[ 1 ].data( ), simd.simd[ 1 ] );
            Traits::Store( result[ 2 ].data( ), simd.simd[ 2 ] );
            Traits::Store( result[ 3 ].data( ), simd.simd[ 3 ] );
            return result;
        }

        SquareMatrixSimd( )
            : simd( ZeroValues )
        {
        }

        explicit SquareMatrixSimd( Math::MatrixType matrixType )
            : simd( matrixType == Math::MatrixType::Identity ? IdentityValues : ZeroValues )
        {
        }

        explicit SquareMatrixSimd( const std::array<SIMDType, 4>& other )
            : simd( other )
        {
        }

        explicit SquareMatrixSimd( const std::array<SIMDType, 3>& other )
            : simd
            {
                Traits::And( other[ 0 ], Traits::Constants::Mask3 ),
                Traits::And( other[ 1 ], Traits::Constants::Mask3 ),
                Traits::And( other[ 2 ], Traits::Constants::Mask3 ),
                Constants::IdentityR4
            }
        {
        }

        explicit SquareMatrixSimd( const SIMDType r1, const SIMDType r2, const SIMDType r3 )
            : simd{ r1, r2, r3, Constants::IdentityR4 }
        {
        }

        explicit SquareMatrixSimd( const SIMDType r1, const SIMDType r2, const SIMDType r3, const SIMDType r4 )
            : simd{ r1, r2, r3, r4 }
        {
        }

        SquareMatrixSimd( const SquareMatrixSimd& other )
            : simd( other.simd )
        {
        }
        explicit SquareMatrixSimd( const ArrayType& matrix )
            : simd{ Traits::Load( matrix[ 0 ] ), Traits::Load( matrix[ 1 ] ), Traits::Load( matrix[ 2 ] ), Traits::Load( matrix[ 3 ] ) }
        {
        }

        explicit SquareMatrixSimd( const MatrixType& matrix )
            : simd{ Traits::Load( matrix[ 0 ] ), Traits::Load( matrix[ 1 ] ), Traits::Load( matrix[ 2 ] ), Traits::Load( matrix[ 3 ] ) }
        {
        }

        bool operator == ( const SquareMatrixSimd& other ) const
        {
            return Traits::AllEqual( simd[ 0 ], other.simd[ 0 ] ) &&
                Traits::AllEqual( simd[ 1 ], other.simd[ 1 ] ) &&
                Traits::AllEqual( simd[ 2 ], other.simd[ 2 ] ) &&
                Traits::AllEqual( simd[ 3 ], other.simd[ 3 ] );
        }
        bool operator != ( const SquareMatrixSimd& other ) const
        {
            return Traits::AllEqual( simd[ 0 ], other.simd[ 0 ] ) == false ||
                Traits::AllEqual( simd[ 1 ], other.simd[ 1 ] ) == false ||
                Traits::AllEqual( simd[ 2 ], other.simd[ 2 ] ) == false ||
                Traits::AllEqual( simd[ 3 ], other.simd[ 3 ] ) == false;
        }

        bool IsIdentity( ) const
        {
            return Traits::AllEqual( simd[ 0 ], Constants::IdentityR1 ) &&
                Traits::AllEqual( simd[ 1 ], Constants::IdentityR2 ) &&
                Traits::AllEqual( simd[ 2 ], Constants::IdentityR3 ) &&
                Traits::AllEqual( simd[ 3 ], Constants::IdentityR4 );
        }

        static SquareMatrixSimd Zero( )
        {
            return SquareMatrixSimd( ZeroValues );
        }

        static SquareMatrixSimd Identity( )
        {
            //return SquareMatrixSimd( IdentityValues );
            return SquareMatrixSimd(
                Traits::Set( 0.f, 0.f, 0.f, 1.f ),
                Traits::Set( 0.f, 0.f, 1.f, 0.f ),
                Traits::Set( 0.f, 1.f, 0.f, 0.f ),
                Traits::Set( 1.f, 0.f, 0.f, 0.f ) );
        }

    };



    // SquareMatrix Definition
    template<ArithmeticType T, size_t N>
    class SquareMatrix : public Internal::MatrixBase
    {
    public:
        using Base = Internal::MatrixBase;

        using ValueType = T;
        static constexpr size_t Size = N;
        using value_type = ValueType;
        using Simd = SquareMatrixSimd<SquareMatrix, N>;

        using Traits = typename Simd::Traits;

        using MatrixData = typename Simd::ArrayType;
        using ArrayType = typename MatrixData::value_type;

    private:
        static constexpr MatrixData MakeDefaultValue( ) noexcept
        {
            MatrixData m;
            for ( int i = 0; i < N; ++i )
            {
                for ( int j = 0; j < N; ++j )
                {
                    m[ i ][ j ] = ( i == j ) ? static_cast< value_type >( 1 ) : static_cast< value_type >( 0 );
                }
            }
            return m;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, value_type>
        static MatrixData MakeData( const T& mat ) noexcept
        {
            MatrixData result;
            memcpy( result[ 0 ].data( ), mat.data( ), std::min( Size * Size, mat.size( ) ) * sizeof( value_type ) );
            return result;
        }

        static MatrixData MakeData( const value_type mat[ Size ][ Size ] ) noexcept
        {
            MatrixData result;
            memcpy( result[ 0 ].data( ), &mat[ 0 ][ 0 ], Size * Size * sizeof( value_type ) );
            return result;
        }

        static constexpr MatrixData ZeroValue{};
        static constexpr MatrixData DefaultValue = MakeDefaultValue( );
        MatrixData data_ = DefaultValue;

    public:
        // SquareMatrix Public Methods
        constexpr static SquareMatrix Zero( ) noexcept
        {
            SquareMatrix zeroMatrix( ZeroValue );
            return zeroMatrix;
        }

        constexpr SquareMatrix( ) noexcept
            : data_( DefaultValue )
        {
        }

        SquareMatrix( const value_type( &mat )[ Size ][ Size ] )
            : data_( *reinterpret_cast< const MatrixData* >( &mat[ 0 ][ 0 ] ) )
        {
        }
        SquareMatrix( const value_type( &mat )[ Size * Size ] )
            : data_( *reinterpret_cast< const MatrixData* >( &mat[ 0 ] ) )
        {
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, value_type>
        SquareMatrix( const T& mat )
        {
            memcpy( data_[ 0 ].data( ), mat.data( ), std::min( Size * Size, mat.size( ) ) * sizeof( value_type ) );
        }

        SquareMatrix( const Simd& simd ) noexcept
            : data_( Simd::ToMatrix( simd ) )
        {
        }

        SquareMatrix( const MatrixData& data ) noexcept
            : data_( data )
        {
        }

        SquareMatrix& operator = ( const Simd& simd ) noexcept
        {
            data_ = Simd::ToMatrix( simd );
            return *this;
        }

        SquareMatrix& operator = ( const MatrixData& data ) noexcept
        {
            data_ = data;
            return *this;
        }

        template<typename...Args>
            requires ( sizeof...( Args ) == ( ( N * N ) - 1 ) )
        SquareMatrix( value_type v, Args... args )
        {
            Internal::InitMatrix( std::make_index_sequence<N * N>( ), data_, v, args... );
        }
        template <typename... Args>
        static SquareMatrix Diag( value_type v, Args... args )
        {
            SquareMatrix m;
            Internal::InitDiagonalMatrix( std::make_index_sequence<N>( ), m.data_, v, args... );
            return m;
        }

        const ArrayType& operator[]( size_t index ) const
        {
            return data_[ index ];
        }
        ArrayType& operator[]( size_t index )
        {
            return data_[ index ];
        }

        Simd ToSimd( ) const noexcept
        {
            return Simd( *this );
        }

        operator Simd( ) const noexcept
        {
            return ToSimd( );
        }


        bool operator==( const SquareMatrix& other ) const
        {
            return data_ == other.data_;
        }

        bool operator!=( const SquareMatrix& other ) const
        {
            return data_ != other.data_;
        }

        bool operator<( const SquareMatrix& other ) const
        {
            return data_ < other.data_;
        }

        bool IsIdentity( ) const
        {
            return data_ == DefaultValue;
        }

        std::string ToString( ) const
        {
            std::string s = "[ [";
            for ( int i = 0; i < N; ++i )
            {
                for ( int j = 0; j < N; ++j )
                {
                    s += std::format( " {}", data_[ i ][ j ] );
                    if ( j < N - 1 )
                        s += ',';
                    else
                        s += " ]";
                }
                if ( i < N - 1 )
                    s += ", [";
            }
            s += " ]";
            return s;
        }

        friend std::ostream& operator << ( std::ostream& stream, const SquareMatrix& m )
        {
            stream << m.ToString( );
            return stream;
        }

    };




    // Addition

    namespace Internal
    {
        template<SquareMatrixSimdType T1, SquareMatrixSimdType T2>
            requires IsCompatibleMatrix<T1, T2>
        inline T1 AddImpl( const T1& m1, const T2& m2 ) noexcept
        {
            using Traits = typename T1::Traits;
            using Simd = T1;
            constexpr auto N = T1::Size;
            if constexpr ( N == 2 )
            {
                Simd result( Traits::Add( m1.simd, m2.simd ) );
                return result;

            }
            else if constexpr ( N == 3 )
            {
                Simd result;
                result.simd[ 0 ] = Traits::Add( m1.simd[ 0 ], m2.simd[ 0 ] );
                result.simd[ 1 ] = Traits::Add( m1.simd[ 1 ], m2.simd[ 1 ] );
                result.simd[ 2 ] = Traits::Add( m1.simd[ 2 ], m2.simd[ 2 ] );
                return result;

            }
            else if constexpr ( N == 4 )
            {
                Simd result;
                result.simd[ 0 ] = Traits::Add( m1.simd[ 0 ], m2.simd[ 0 ] );
                result.simd[ 1 ] = Traits::Add( m1.simd[ 1 ], m2.simd[ 1 ] );
                result.simd[ 2 ] = Traits::Add( m1.simd[ 2 ], m2.simd[ 2 ] );
                result.simd[ 3 ] = Traits::Add( m1.simd[ 3 ], m2.simd[ 3 ] );
                return result;
            }
            else
            {
                static_assert( false, "Unsupported matrix dimensions." );
            }
        }
    }


    template<SquareMatrixSimdType T1, SquareMatrixSimdType T2>
        requires IsCompatibleMatrix<T1, T2>
    inline auto operator+( const T1& m1, const T2& m2 ) noexcept
    {
        return Internal::AddImpl( m1, m2 );
    }

    template<SquareMatrixOrSquareMatrixSimdType T1, SquareMatrixOrSquareMatrixSimdType T2>
        requires IsCompatibleMatrix<T1, T2>&& Internal::HasSquareMatrixType<T1, T2>
    inline auto operator+( const T1& m1, const T2& m2 ) noexcept
    {
        return Internal::AddImpl( Internal::ToSimdType( m1 ), Internal::ToSimdType( m2 ) );
    }



    // Subtraction

    namespace Internal
    {
        template<SquareMatrixSimdType T1, SquareMatrixSimdType T2>
            requires IsCompatibleMatrix<T1, T2>
        inline T1 SubImpl( const T1& m1, const T2& m2 ) noexcept
        {
            using Traits = typename T1::Traits;
            using Simd = T1;
            constexpr auto N = T1::Size;
            if constexpr ( N == 2 )
            {
                Simd result( Traits::Sub( m1.simd, m2.simd ) );
                return result;

            }
            else if constexpr ( N == 3 )
            {
                Simd result;
                result.simd[ 0 ] = Traits::Sub( m1.simd[ 0 ], m2.simd[ 0 ] );
                result.simd[ 1 ] = Traits::Sub( m1.simd[ 1 ], m2.simd[ 1 ] );
                result.simd[ 2 ] = Traits::Sub( m1.simd[ 2 ], m2.simd[ 2 ] );
                return result;

            }
            else if constexpr ( N == 4 )
            {
                Simd result;
                result.simd[ 0 ] = Traits::Sub( m1.simd[ 0 ], m2.simd[ 0 ] );
                result.simd[ 1 ] = Traits::Sub( m1.simd[ 1 ], m2.simd[ 1 ] );
                result.simd[ 2 ] = Traits::Sub( m1.simd[ 2 ], m2.simd[ 2 ] );
                result.simd[ 3 ] = Traits::Sub( m1.simd[ 3 ], m2.simd[ 3 ] );
                return result;
            }
            else
            {
                static_assert( false, "Unsupported matrix dimensions." );
            }
        }
    }

    template<SquareMatrixSimdType T1, SquareMatrixSimdType T2>
        requires IsCompatibleMatrix<T1, T2>
    inline auto operator-( const T1& m1, const T2& m2 ) noexcept
    {
        return Internal::SubImpl( m1, m2 );
    }

    template<SquareMatrixOrSquareMatrixSimdType T1, SquareMatrixOrSquareMatrixSimdType T2>
        requires IsCompatibleMatrix<T1, T2>&& Internal::HasSquareMatrixType<T1, T2>
    inline auto operator-( const T1& m1, const T2& m2 ) noexcept
    {
        return Internal::SubImpl( Internal::ToSimdType( m1 ), Internal::ToSimdType( m2 ) );
    }


    // Scalar Multiplication
    namespace Internal
    {
        template<SquareMatrixSimdType T1, ArithmeticType T2>
        T1 MulImpl( const T1& m, const T2 value ) noexcept
        {
            using Traits = typename T1::Traits;
            using Simd = T1;
            using ValueType = typename Traits::Type;
            constexpr auto N = T1::Size;
            auto v = Traits::Fill( static_cast< ValueType >( value ) );

            if constexpr ( N == 2 )
            {
                Simd result( Traits::Mul( m.simd, v ) );
                return result;

            }
            else if constexpr ( N == 3 )
            {
                Simd result;
                result.simd[ 0 ] = Traits::Mul( m.simd[ 0 ], v );
                result.simd[ 1 ] = Traits::Mul( m.simd[ 1 ], v );
                result.simd[ 2 ] = Traits::Mul( m.simd[ 2 ], v );
                return result;

            }
            else if constexpr ( N == 4 )
            {
                Simd result;
                result.simd[ 0 ] = Traits::Mul( m.simd[ 0 ], v );
                result.simd[ 1 ] = Traits::Mul( m.simd[ 1 ], v );
                result.simd[ 2 ] = Traits::Mul( m.simd[ 2 ], v );
                result.simd[ 3 ] = Traits::Mul( m.simd[ 3 ], v );
                return result;
            }
            else
            {
                static_assert( false, "Unsupported matrix dimensions." );
            }
        }
    }

    template<SquareMatrixSimdType T1, ArithmeticType T2>
    inline auto operator*( const T1& m, const T2 value ) noexcept
    {
        return Internal::MulImpl( m, value );
    }

    template<ArithmeticType T1, SquareMatrixSimdType T2 >
    inline auto operator*( const T1 value, const T2& m ) noexcept
    {
        return Internal::MulImpl( m, value );
    }

    template<SquareMatrixType T1, ArithmeticType T2>
    inline auto operator*( const T1& m, const T2 value ) noexcept
    {
        return Internal::MulImpl( m.ToSimd( ), value );
    }

    template<ArithmeticType T1, SquareMatrixType T2 >
    inline auto operator*( const T1 value, const T2& m ) noexcept
    {
        return Internal::MulImpl( m.ToSimd( ), value );
    }



    inline typename SquareMatrix<float, 4>::Simd Multiply( const typename SquareMatrix<float, 4>::Simd& matrix1, const typename SquareMatrix<float, 4>::Simd& matrix2 )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using Simd = typename SquareMatrix<float, 4>::Simd;

        auto rmm1 = _mm256_castps128_ps256( matrix1.simd[ 0 ] );
        rmm1 = _mm256_insertf128_ps( rmm1, matrix1.simd[ 1 ], 1 );
        auto rmm2 = _mm256_castps128_ps256( matrix1.simd[ 2 ] );
        rmm2 = _mm256_insertf128_ps( rmm2, matrix1.simd[ 3 ], 1 );

        auto rmm3 = _mm256_castps128_ps256( matrix2.simd[ 0 ] );
        rmm3 = _mm256_insertf128_ps( rmm3, matrix2.simd[ 1 ], 1 );
        auto rmm4 = _mm256_castps128_ps256( matrix2.simd[ 2 ] );
        rmm4 = _mm256_insertf128_ps( rmm4, matrix2.simd[ 3 ], 1 );

        auto rmm5 = _mm256_castsi256_ps( _mm256_shuffle_epi32( _mm256_castps_si256( rmm1 ), _MM_SHUFFLE( 0, 0, 0, 0 ) ) );
        auto rmm6 = _mm256_castsi256_ps( _mm256_shuffle_epi32( _mm256_castps_si256( rmm2 ), _MM_SHUFFLE( 0, 0, 0, 0 ) ) );
        auto rmm7 = _mm256_permute2f128_ps( rmm3, rmm3, 0x00 );
        auto rmm8 = _mm256_mul_ps( rmm5, rmm7 );
        auto rmm9 = _mm256_mul_ps( rmm6, rmm7 );

        rmm5 = _mm256_castsi256_ps( _mm256_shuffle_epi32( _mm256_castps_si256( rmm1 ), _MM_SHUFFLE( 1, 1, 1, 1 ) ) );
        rmm6 = _mm256_castsi256_ps( _mm256_shuffle_epi32( _mm256_castps_si256( rmm2 ), _MM_SHUFFLE( 1, 1, 1, 1 ) ) );
        rmm7 = _mm256_permute2f128_ps( rmm3, rmm3, 0x11 );
        auto rmm10 = _mm256_fmadd_ps( rmm5, rmm7, rmm8 );
        auto rmm11 = _mm256_fmadd_ps( rmm6, rmm7, rmm9 );

        rmm5 = _mm256_castsi256_ps( _mm256_shuffle_epi32( _mm256_castps_si256( rmm1 ), _MM_SHUFFLE( 2, 2, 2, 2 ) ) );
        rmm6 = _mm256_castsi256_ps( _mm256_shuffle_epi32( _mm256_castps_si256( rmm2 ), _MM_SHUFFLE( 2, 2, 2, 2 ) ) );
        auto rmm12 = _mm256_permute2f128_ps( rmm4, rmm4, 0x00 );
        auto rmm13 = _mm256_mul_ps( rmm5, rmm12 );
        auto rmm14 = _mm256_mul_ps( rmm6, rmm12 );

        rmm5 = _mm256_castsi256_ps( _mm256_shuffle_epi32( _mm256_castps_si256( rmm1 ), _MM_SHUFFLE( 3, 3, 3, 3 ) ) );
        rmm6 = _mm256_castsi256_ps( _mm256_shuffle_epi32( _mm256_castps_si256( rmm2 ), _MM_SHUFFLE( 3, 3, 3, 3 ) ) );
        rmm12 = _mm256_permute2f128_ps( rmm4, rmm4, 0x11 );
        auto rmm15 = _mm256_fmadd_ps( rmm5, rmm12, rmm13 );
        auto rmm16 = _mm256_fmadd_ps( rmm6, rmm12, rmm14 );

        rmm1 = _mm256_add_ps( rmm10, rmm15 );
        rmm2 = _mm256_add_ps( rmm11, rmm16 );

        Simd result;
        result.simd[ 0 ] = _mm256_castps256_ps128( rmm1 );
        result.simd[ 1 ] = _mm256_extractf128_ps( rmm1, 1 );
        result.simd[ 2 ] = _mm256_castps256_ps128( rmm2 );
        result.simd[ 3 ] = _mm256_extractf128_ps( rmm2, 1 );
        return result;
    }


    inline typename SquareMatrix<float, 3>::Simd Multiply( const typename SquareMatrix<float, 3>::Simd& matrix1, const typename SquareMatrix<float, 3>::Simd& matrix2 )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        using Simd = typename SquareMatrix<float, 3>::Simd;

        auto m10 = matrix1.simd[ 0 ];
        auto m11 = matrix1.simd[ 1 ];
        auto m12 = matrix1.simd[ 2 ];

        auto c0 = Traits::At<0>( m10 );
        auto c1 = Traits::At<0>( m11 );
        auto c2 = Traits::At<0>( m12 );

        auto m2v = matrix2.simd[ 0 ];

        c0 = Traits::Mul( c0, m2v );
        c1 = Traits::Mul( c1, m2v );
        c2 = Traits::Mul( c2, m2v );

        auto c0_1 = Traits::At<1>( m10 );
        auto c1_1 = Traits::At<1>( m11 );
        auto c2_1 = Traits::At<1>( m12 );

        m2v = matrix2.simd[ 1 ];

        c0 = Traits::FMAdd( c0_1, m2v, c0 );
        c1 = Traits::FMAdd( c1_1, m2v, c1 );
        c2 = Traits::FMAdd( c2_1, m2v, c2 );

        m10 = Traits::At<2>( m10 );
        m11 = Traits::At<2>( m11 );
        m12 = Traits::At<2>( m12 );

        m2v = matrix2.simd[ 2 ];

        Simd result;
        result.simd[ 0 ] = Traits::FMAdd( m10, m2v, c0 );
        result.simd[ 1 ] = Traits::FMAdd( m11, m2v, c1 );
        result.simd[ 2 ] = Traits::FMAdd( m12, m2v, c2 );
        return result;

    }

    inline typename SquareMatrix<float, 2>::Simd Multiply( const typename SquareMatrix<float, 2>::Simd& matrix1, const typename SquareMatrix<float, 2>::Simd& matrix2 )
    {
        using Traits = typename SquareMatrix<float, 2>::Traits;
        using Simd = typename SquareMatrix<float, 2>::Simd;

        //
        // a1 * a2 + b1 * c2      a1 * b2 + b1 * d2
        //
        // c1 * a2 + d1 * c2      c1 * b2 + d1 * d2
        //

        // a1 * a2 + b1 * c2
        // a1 * b2 + b1 * d2
        // c1 * a2 + d1 * c2
        // c1 * b2 + d1 * d2

        auto rmm1 = Traits::Swizzle<SIMD::Shuffle_v<2, 2, 0, 0>>( matrix1.simd );
        auto rmm2 = Traits::Swizzle<SIMD::Shuffle_v<1, 0, 1, 0>>( matrix2.simd );
        auto rmm3 = Traits::Mul( rmm1, rmm2 );
        rmm1 = Traits::Swizzle< SIMD::Shuffle_v<3, 3, 1, 1>>( matrix1.simd );
        rmm2 = Traits::Swizzle< SIMD::Shuffle_v<3, 2, 3, 2>>( matrix2.simd );
        return Simd( Traits::FMAdd( rmm1, rmm2, rmm3 ) );
    }


    template<SquareMatrixSimdType T1, SquareMatrixSimdType T2>
        requires IsCompatibleMatrix<T1, T2>
    inline T2 operator*( const T1& m1, const T2& m2 ) noexcept
    {
        return Math::Multiply( m1, m2 );
    }

    template<SquareMatrixOrSquareMatrixSimdType T1, SquareMatrixOrSquareMatrixSimdType T2>
        requires IsCompatibleMatrix<T1, T2>&& Internal::HasSquareMatrixType<T1, T2>
    inline T2 operator*( const T1& m1, const T2& m2 ) noexcept
    {
        return Math::Multiply( Internal::ToSimdType( m1 ), Internal::ToSimdType( m2 ) );
    }

    /// <summary>
    /// a*b^T, where a is a column vector and b is a row vector with the same
    /// number of elements as a. The result is square matrix.
    /// </summary>
    template<SimdType T1, SimdType T2>
        requires IsCompatible<T1, T2>&& FloatingPointType<typename T1::value_type>
    typename SquareMatrix<typename T1::value_type, T1::Size>::Simd OuterProduct( const T1& a, const T2& b )
    {
        using S = typename SquareMatrix<typename T1::value_type, T1::Size>::Simd;
        using Traits = typename S::Traits;

        if constexpr ( S::Size == 2 )
        {
            return S( Traits::OuterProduct2x2( a.simd, b.simd ) );
        }
        else if constexpr ( S::Size == 3 )
        {
            return S( Traits::OuterProduct3x3( a.simd, b.simd ) );
        }
        else if constexpr ( S::Size == 4 )
        {
            return S( Traits::OuterProduct4x4( a.simd, b.simd ) );
        }

    }

    template<SimdOrTupleType T1, SimdOrTupleType T2>
        requires IsCompatible<T1, T2>&& Internal::HasTupleType<T1,T2> && FloatingPointType<typename T1::value_type>
    typename SquareMatrix<typename T1::value_type, T1::Size>::Simd OuterProduct( const T1& a, const T2& b )
    {
        return OuterProduct( Internal::ToSimdType( a ), Internal::ToSimdType( b ) );
    }



    // Division
    namespace Internal
    {
        template<SquareMatrixSimdType T1, ArithmeticType T2>
        T1 DivImpl( const T1& m, const T2 value ) noexcept
        {
            using Traits = typename T1::Traits;
            using Simd = T1;
            using ValueType = typename Traits::Type;
            constexpr auto N = Traits::Size;
            auto v = Traits::Fill( static_cast< ValueType >( value ) );

            if constexpr ( N == 2 )
            {
                Simd result( Traits::Div( m.simd, v ) );
                return result;

            }
            else if constexpr ( N == 3 )
            {
                Simd result;
                result.simd[ 0 ] = Traits::Div( m.simd[ 0 ], v );
                result.simd[ 1 ] = Traits::Div( m.simd[ 1 ], v );
                result.simd[ 2 ] = Traits::Div( m.simd[ 2 ], v );
                return result;

            }
            else if constexpr ( N == 4 )
            {
                Simd result;
                result.simd[ 0 ] = Traits::Div( m.simd[ 0 ], v );
                result.simd[ 1 ] = Traits::Div( m.simd[ 1 ], v );
                result.simd[ 2 ] = Traits::Div( m.simd[ 2 ], v );
                result.simd[ 3 ] = Traits::Div( m.simd[ 3 ], v );
                return result;
            }
            else
            {
                // Not supported
            }
        }
    }


    template<SquareMatrixSimdType T1, ArithmeticType T2>
    inline auto operator/( const T1& m, const T2 value ) noexcept
    {
        return Internal::DivImpl( m, value );
    }

    template<SquareMatrixType T1, ArithmeticType T2>
    inline auto operator/( const T1& m, const T2 value ) noexcept
    {
        return Internal::DivImpl( m.ToSimd( ), value );
    }



    /// <summary>
    /// Calculates the determinant of a matrix.
    /// </summary>
    /// <param name="matrix">
    /// The matrix that the determinant will be calculated for.
    /// </param>
    /// <returns>
    /// Returns a Vector&lt;float,4&gt;::Simd with all the
    /// elements set to the determinant of the matrix. 
    /// </returns>
    inline typename Vector<float, 4>::Simd Determinant( const typename SquareMatrix<float, 4>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using ResultType = typename Vector<float, 4>::Simd;
        //using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
        using Select = typename Traits::SelectType;
        Traits::SIMDType sign( { { 1.0f, -1.0f, 1.0f, -1.0f } } );

        auto matrix2 = matrix.simd[ 2 ];
        auto matrix3 = matrix.simd[ 3 ];

        auto rmm0 = Traits::Swizzle< SIMD::Shuffle_v<Select::X, Select::X, Select::X, Select::Y>>( matrix2 );
        auto rmm1 = Traits::Swizzle< SIMD::Shuffle_v<Select::Y, Select::Y, Select::Z, Select::Z>>( matrix3 );
        auto rmm2 = Traits::Swizzle< SIMD::Shuffle_v<Select::Z, Select::W, Select::W, Select::W>>( matrix3 );
        auto rmm3 = Traits::Swizzle< SIMD::Shuffle_v<Select::Y, Select::Y, Select::Z, Select::Z>>( matrix2 );

        auto rmm4 = Traits::Mul( rmm0, rmm1 );
        auto rmm5 = Traits::Mul( rmm0, rmm2 );
        auto rmm6 = Traits::Mul( rmm3, rmm2 );
        rmm0 = Traits::Swizzle< SIMD::Shuffle_v<Select::Y, Select::Y, Select::Z, Select::Z>>( matrix2 );
        rmm1 = Traits::Swizzle< SIMD::Shuffle_v<Select::X, Select::X, Select::X, Select::Y>>( matrix3 );
        rmm2 = Traits::Swizzle< SIMD::Shuffle_v<Select::Z, Select::W, Select::W, Select::W>>( matrix2 );
        rmm3 = Traits::Swizzle< SIMD::Shuffle_v<Select::Y, Select::Y, Select::Z, Select::Z>>( matrix3 );

        rmm4 = Traits::FNMAdd( rmm0, rmm1, rmm4 );
        rmm5 = Traits::FNMAdd( rmm2, rmm1, rmm5 );
        rmm6 = Traits::FNMAdd( rmm2, rmm3, rmm6 );

        rmm3 = matrix.simd[ 1 ];

        rmm0 = Traits::Swizzle< SIMD::Shuffle_v<Select::Z, Select::W, Select::W, Select::W>>( rmm3 );
        rmm1 = Traits::Swizzle< SIMD::Shuffle_v<Select::Y, Select::Y, Select::Z, Select::Z>>( rmm3 );
        rmm2 = Traits::Swizzle< SIMD::Shuffle_v<Select::X, Select::X, Select::X, Select::Y>>( rmm3 );

        auto rmm7 = Traits::Mul( rmm0, rmm4 );
        rmm7 = Traits::FNMAdd( rmm1, rmm5, rmm7 );
        rmm7 = Traits::FMAdd( rmm2, rmm6, rmm7 );

        rmm3 = matrix.simd[ 0 ];
        rmm3 = Traits::Mul( rmm3, sign );

        return ResultType( Traits::Dot( rmm3, rmm7 ) );
    }

    /// <summary>
    /// Calculates the determinant of a matrix.
    /// </summary>
    /// <param name="matrix">
    /// The matrix that the determinant will be calculated for.
    /// </param>
    /// <returns>
    /// Returns a Vector&lt;float,4&gt;::Simd with all the
    /// elements set to the determinant of the matrix.
    /// </returns>
    inline typename Vector<float, 4>::Simd Determinant( const SquareMatrix<float, 4ULL>& matrix )
    {
        return Math::Determinant( matrix.ToSimd( ) );
    }

    /// <summary>
    /// Calculates the determinant of a matrix.
    /// </summary>
    /// <param name="matrix">
    /// The matrix that the determinant will be calculated for.
    /// </param>
    /// <returns>
    /// The determinant of the matrix.
    /// </returns>
    inline float ScalarDeterminant( const SquareMatrix<float, 4>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        return Traits::First( Math::Determinant( matrix ).simd );
    }

    /// <summary>
    /// Calculates the determinant of a matrix.
    /// </summary>
    /// <param name="matrix">
    /// The matrix that the determinant will be calculated for.
    /// </param>
    /// <returns>
    /// The determinant of the matrix.
    /// </returns>
    inline float ScalarDeterminant( const SquareMatrix<float, 4>& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        return Traits::First( Math::Determinant( matrix.ToSimd( ) ).simd );
    }


    inline typename Vector<float, 3>::Simd Determinant( const typename SquareMatrix<float, 3>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        using Simd = typename Vector<float, 3>::Simd;

        auto v1 = matrix.simd[ 1 ];
        auto v2 = matrix.simd[ 2 ];

        auto edd = Traits::Swizzle< SIMD::Shuffle_v<3, 0, 0, 1>>( v1 );
        auto iih = Traits::Swizzle< SIMD::Shuffle_v<3, 1, 2, 2>>( v2 );
        auto hgg = Traits::Swizzle< SIMD::Shuffle_v<3, 0, 0, 1>>( v2 );
        auto ffe = Traits::Swizzle< SIMD::Shuffle_v<3, 1, 2, 2>>( v1 );

        auto det = Traits::FMSub( edd, iih, Traits::Mul( hgg, ffe ) );

        Traits::SIMDType sign( { { 1.0f, -1.0f, 1.0f, 0.0f } } );
        auto v0 = Traits::Mul( matrix.simd[ 0 ], sign );

        return Simd( Traits::Dot( v0, det ) );
    }

    inline typename Vector<float, 3>::Simd Determinant( const typename SquareMatrix<float, 3>& matrix )
    {
        typename SquareMatrix<float, 3>::Simd simd = matrix.ToSimd( );
        return Math::Determinant( simd );
    }
    inline float ScalarDeterminant( const SquareMatrix<float, 3>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        return Traits::First( Math::Determinant( matrix ).simd );
    }

    inline float ScalarDeterminant( const SquareMatrix<float, 3>& matrix )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        return Traits::First( Math::Determinant( matrix.ToSimd( ) ).simd );
    }





    inline SquareMatrix<float, 3>::Simd Transpose( const SquareMatrix<float, 3>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        using MatrixSimd = SquareMatrix<float, 3>::Simd;

        auto rmm4 = Traits::Shuffle<1, 0, 1, 0>( matrix.simd[ 0 ], matrix.simd[ 1 ] );
        auto rmm5 = Traits::Shuffle<2, 2, 2, 2>( matrix.simd[ 0 ], matrix.simd[ 1 ] );

        MatrixSimd result;

        result.simd[ 0 ] = Traits::Shuffle<3, 0, 2, 0>( rmm4, matrix.simd[ 2 ] );
        result.simd[ 1 ] = Traits::Shuffle<3, 1, 3, 1>( rmm4, matrix.simd[ 2 ] );
        result.simd[ 2 ] = Traits::Shuffle<3, 2, 2, 0>( rmm5, matrix.simd[ 2 ] );

        return result;
    }

    inline SquareMatrix<float, 3>::Simd Transpose( const SquareMatrix<float, 3>& matrix )
    {
        return Transpose( matrix.ToSimd( ) );
    }

    /// <summary>
    /// Calculates the transpose of the matrix.
    /// </summary>
    /// <param name="matrix">
    /// The matrix to transpose.
    /// </param>
    /// <returns>
    /// The transposed matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Transpose( const SquareMatrix<float, 4>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using MatrixSimd = SquareMatrix<float, 4>::Simd;

        auto rmm1 = Traits::Shuffle<1, 0, 1, 0>( matrix.simd[ 0 ], matrix.simd[ 1 ] );
        auto rmm3 = Traits::Shuffle<3, 2, 3, 2>( matrix.simd[ 0 ], matrix.simd[ 1 ] );
        auto rmm2 = Traits::Shuffle<1, 0, 1, 0>( matrix.simd[ 2 ], matrix.simd[ 3 ] );
        auto rmm4 = Traits::Shuffle<3, 2, 3, 2>( matrix.simd[ 2 ], matrix.simd[ 3 ] );

        MatrixSimd result;

        result.simd[ 0 ] = Traits::Shuffle<2, 0, 2, 0>( rmm1, rmm2 );
        result.simd[ 1 ] = Traits::Shuffle<3, 1, 3, 1>( rmm1, rmm2 );
        result.simd[ 2 ] = Traits::Shuffle<2, 0, 2, 0>( rmm3, rmm4 );
        result.simd[ 3 ] = Traits::Shuffle<3, 1, 3, 1>( rmm3, rmm4 );

        return result;
    }

    /// <summary>
    /// Calculates the transpose of the matrix.
    /// </summary>
    /// <param name="matrix">
    /// The matrix to transpose.
    /// </param>
    /// <returns>
    /// The transposed matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Transpose( const SquareMatrix<float, 4>& matrix )
    {
        return Transpose( matrix.ToSimd( ) );
    }

    /// <summary>
    /// Calculates the inverse of the matrix.
    /// </summary>
    /// <param name="matrix">
    /// The matrix to invert.
    /// </param>
    /// <param name="determinant">
    /// Address of a Vector&lt;float, 4&gt;::Simd object where each element will
    /// be assigned the determinant of the matrix.
    /// </param>
    /// <returns>
    /// Returns the matrix inverse of <c>matrix</c>. If the 
    /// provided matrix is singular with a determinant equal to 0, 
    /// Inverse returns an infinite matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Inverse( const SquareMatrix<float, 4>::Simd& matrix, typename Vector<float, 4>::Simd* determinant = nullptr )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using MatrixSimd = SquareMatrix<float, 4>::Simd;

        auto vTemp1 = Traits::Shuffle<1, 0, 1, 0>( matrix.simd[ 0 ], matrix.simd[ 1 ] );
        auto vTemp3 = Traits::Shuffle<3, 2, 3, 2>( matrix.simd[ 0 ], matrix.simd[ 1 ] );
        auto vTemp2 = Traits::Shuffle<1, 0, 1, 0>( matrix.simd[ 2 ], matrix.simd[ 3 ] );
        auto vTemp4 = Traits::Shuffle<3, 2, 3, 2>( matrix.simd[ 2 ], matrix.simd[ 3 ] );

        MatrixSimd transposed;

        transposed.simd[ 0 ] = Traits::Shuffle<2, 0, 2, 0>( vTemp1, vTemp2 );
        transposed.simd[ 1 ] = Traits::Shuffle<3, 1, 3, 1>( vTemp1, vTemp2 );
        transposed.simd[ 2 ] = Traits::Shuffle<2, 0, 2, 0>( vTemp3, vTemp4 );
        transposed.simd[ 3 ] = Traits::Shuffle<3, 1, 3, 1>( vTemp3, vTemp4 );

        auto V00 = Traits::Swizzle< SIMD::Shuffle_v<1, 1, 0, 0>>( transposed.simd[ 2 ] );
        auto V10 = Traits::Swizzle< SIMD::Shuffle_v<3, 2, 3, 2>>( transposed.simd[ 3 ] );
        auto V01 = Traits::Swizzle< SIMD::Shuffle_v<1, 1, 0, 0>>( transposed.simd[ 0 ] );
        auto V11 = Traits::Swizzle< SIMD::Shuffle_v<3, 2, 3, 2>>( transposed.simd[ 1 ] );

        auto V02 = Traits::Shuffle<2, 0, 2, 0>( transposed.simd[ 2 ], transposed.simd[ 0 ] );
        auto V12 = Traits::Shuffle<3, 1, 3, 1>( transposed.simd[ 3 ], transposed.simd[ 1 ] );

        auto D0 = Traits::Mul( V00, V10 );
        auto D1 = Traits::Mul( V01, V11 );
        auto D2 = Traits::Mul( V02, V12 );


        V00 = Traits::Swizzle< SIMD::Shuffle_v<3, 2, 3, 2>>( transposed.simd[ 2 ] );
        V10 = Traits::Swizzle< SIMD::Shuffle_v<1, 1, 0, 0>>( transposed.simd[ 3 ] );
        V01 = Traits::Swizzle< SIMD::Shuffle_v<3, 2, 3, 2>>( transposed.simd[ 0 ] );
        V11 = Traits::Swizzle< SIMD::Shuffle_v<1, 1, 0, 0>>( transposed.simd[ 1 ] );

        V02 = Traits::Shuffle<3, 1, 3, 1>( transposed.simd[ 2 ], transposed.simd[ 0 ] );
        V12 = Traits::Shuffle<2, 0, 2, 0>( transposed.simd[ 3 ], transposed.simd[ 1 ] );


        D0 = Traits::FNMAdd( V00, V10, D0 );
        D1 = Traits::FNMAdd( V01, V11, D1 );
        D2 = Traits::FNMAdd( V02, V12, D2 );

        // V11 = D0Y,D0W,D2Y,D2Y
        V11 = Traits::Shuffle<1, 1, 3, 1>( D0, D2 );
        V00 = Traits::Swizzle< SIMD::Shuffle_v<1, 0, 2, 1>>( transposed.simd[ 1 ] );
        V10 = Traits::Shuffle<0, 3, 0, 2>( V11, D0 );
        V01 = Traits::Swizzle< SIMD::Shuffle_v<0, 1, 0, 2>>( transposed.simd[ 0 ] );
        V11 = Traits::Shuffle<2, 1, 2, 1>( V11, D0 );

        // V13 = D1Y,D1W,D2W,D2W
        auto V13 = Traits::Shuffle<3, 3, 3, 1>( D1, D2 );
        V02 = Traits::Swizzle< SIMD::Shuffle_v<1, 0, 2, 1>>( transposed.simd[ 3 ] );
        V12 = Traits::Shuffle<0, 3, 0, 2>( V13, D1 );
        auto V03 = Traits::Swizzle< SIMD::Shuffle_v<0, 1, 0, 2>>( transposed.simd[ 2 ] );
        V13 = Traits::Shuffle<2, 1, 2, 1>( V13, D1 );

        auto C0 = Traits::Mul( V00, V10 );
        auto C2 = Traits::Mul( V01, V11 );
        auto C4 = Traits::Mul( V02, V12 );
        auto C6 = Traits::Mul( V03, V13 );


        // V11 = D0X,D0Y,D2X,D2X
        V11 = Traits::Shuffle<0, 0, 1, 0>( D0, D2 );
        V00 = Traits::Swizzle< SIMD::Shuffle_v<2, 1, 3, 2>>( transposed.simd[ 1 ] );
        V10 = Traits::Shuffle<2, 1, 0, 3>( D0, V11 );
        V01 = Traits::Swizzle< SIMD::Shuffle_v<1, 3, 2, 3>>( transposed.simd[ 0 ] );
        V11 = Traits::Shuffle<0, 2, 1, 2>( D0, V11 );
        // V13 = D1X,D1Y,D2Z,D2Z
        V13 = Traits::Shuffle<2, 2, 1, 0>( D1, D2 );
        V02 = Traits::Swizzle< SIMD::Shuffle_v<2, 1, 3, 2>>( transposed.simd[ 3 ] );
        V12 = Traits::Shuffle<2, 1, 0, 3>( D1, V13 );
        V03 = Traits::Swizzle< SIMD::Shuffle_v<1, 3, 2, 3>>( transposed.simd[ 2 ] );
        V13 = Traits::Shuffle<0, 2, 1, 2>( D1, V13 );

        C0 = Traits::FNMAdd( V00, V10, C0 );
        C2 = Traits::FNMAdd( V01, V11, C2 );
        C4 = Traits::FNMAdd( V02, V12, C4 );
        C6 = Traits::FNMAdd( V03, V13, C6 );

        V00 = Traits::Swizzle< SIMD::Shuffle_v<0, 3, 0, 3>>( transposed.simd[ 1 ] );
        // V10 = D0Z,D0Z,D2X,D2Y
        V10 = Traits::Shuffle<1, 0, 2, 2>( D0, D2 );
        V10 = Traits::Swizzle< SIMD::Shuffle_v<0, 2, 3, 0>>( V10 );
        V01 = Traits::Swizzle< SIMD::Shuffle_v<2, 0, 3, 1>>( transposed.simd[ 0 ] );
        // V11 = D0X,D0W,D2X,D2Y
        V11 = Traits::Shuffle<1, 0, 3, 0>( D0, D2 );
        V11 = Traits::Swizzle< SIMD::Shuffle_v<2, 1, 0, 3>>( V11 );
        V02 = Traits::Swizzle< SIMD::Shuffle_v<0, 3, 0, 3>>( transposed.simd[ 3 ] );
        // V12 = D1Z,D1Z,D2Z,D2W
        V12 = Traits::Shuffle<3, 2, 2, 2>( D1, D2 );
        V12 = Traits::Swizzle< SIMD::Shuffle_v<0, 2, 3, 0>>( V12 );
        V03 = Traits::Swizzle< SIMD::Shuffle_v<2, 0, 3, 1>>( transposed.simd[ 2 ] );
        // V13 = D1X,D1W,D2Z,D2W
        V13 = Traits::Shuffle<3, 2, 3, 0>( D1, D2 );
        V13 = Traits::Swizzle< SIMD::Shuffle_v<2, 1, 0, 3>>( V13 );

        V00 = Traits::Mul( V00, V10 );
        V01 = Traits::Mul( V01, V11 );
        V02 = Traits::Mul( V02, V12 );
        V03 = Traits::Mul( V03, V13 );

        auto C1 = Traits::Sub( C0, V00 );
        C0 = Traits::Add( C0, V00 );
        auto C3 = Traits::Add( C2, V01 );
        C2 = Traits::Sub( C2, V01 );
        auto C5 = Traits::Sub( C4, V02 );
        C4 = Traits::Add( C4, V02 );
        auto C7 = Traits::Add( C6, V03 );
        C6 = Traits::Sub( C6, V03 );

        C0 = Traits::Shuffle<3, 1, 2, 0>( C0, C1 );
        C2 = Traits::Shuffle<3, 1, 2, 0>( C2, C3 );
        C4 = Traits::Shuffle<3, 1, 2, 0>( C4, C5 );
        C6 = Traits::Shuffle<3, 1, 2, 0>( C6, C7 );
        C0 = Traits::Swizzle< SIMD::Shuffle_v<3, 1, 2, 0 >>( C0 );
        C2 = Traits::Swizzle< SIMD::Shuffle_v<3, 1, 2, 0 >>( C2 );
        C4 = Traits::Swizzle< SIMD::Shuffle_v<3, 1, 2, 0 >>( C4 );
        C6 = Traits::Swizzle< SIMD::Shuffle_v<3, 1, 2, 0 >>( C6 );
        // Get the determinant
        auto vTemp = Traits::Dot( C0, transposed.simd[ 0 ] );
        if ( determinant != nullptr )
        {
            *determinant = vTemp;
        }
        vTemp = Traits::Div( Traits::Fill( 1.f ), vTemp );
        MatrixSimd result;
        result.simd[ 0 ] = Traits::Mul( C0, vTemp );
        result.simd[ 1 ] = Traits::Mul( C2, vTemp );
        result.simd[ 2 ] = Traits::Mul( C4, vTemp );
        result.simd[ 3 ] = Traits::Mul( C6, vTemp );
        return result;
    }

    /// <summary>
    /// Calculates the inverse of the matrix.
    /// </summary>
    /// <param name="matrix">
    /// The matrix to invert.
    /// </param>
    /// <param name="determinant">
    /// Address of a Vector&lt;float, 4&gt;::Simd object where each element will
    /// be assigned the determinant of the matrix.
    /// </param>
    /// <returns>
    /// Returns the matrix inverse of <c>matrix</c>. If the 
    /// provided matrix is singular with a determinant equal to 0, 
    /// Inverse returns an infinite matrix.
    /// </returns>
    inline typename SquareMatrix<float, 4>::Simd Inverse( const SquareMatrix<float, 4>& matrix, typename Vector<float, 4>::Simd* determinant = nullptr )
    {
        return Inverse( matrix.ToSimd( ), determinant );
    }

    inline typename SquareMatrix<float, 3>::Simd Inverse( const typename SquareMatrix<float, 3>::Simd& matrix, typename Vector<float, 3>::Simd* determinant = nullptr )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        using Simd = typename SquareMatrix<float, 3>::Simd;

        auto v0 = matrix.simd[ 0 ];
        auto v1 = matrix.simd[ 1 ];
        auto v2 = matrix.simd[ 2 ];

        auto edd = Traits::Swizzle<SIMD::Shuffle_v<3, 0, 0, 1>>( v1 );
        auto iih = Traits::Swizzle<SIMD::Shuffle_v<3, 1, 2, 2>>( v2 );
        auto hgg = Traits::Swizzle<SIMD::Shuffle_v<3, 0, 0, 1>>( v2 );
        auto ffe = Traits::Swizzle<SIMD::Shuffle_v<3, 1, 2, 2>>( v1 );

        auto det = Traits::FMSub( edd, iih, Traits::Mul( hgg, ffe ) );

        Traits::SIMDType sign0( { { 1.0f, -1.0f, 1.0f, 0.0f } } );
        auto v0s = Traits::Mul( matrix.simd[ 0 ], sign0 );

        det = Traits::Dot( v0s, det );

        if ( determinant )
        {
            *determinant = det;
        }

        // 
        // a b c
        // d e f
        // g h i
        // 
        // Transpose
        // 
        // a d g
        // b e h
        // c f i
        //
        // Adjugate
        // 
        //  (e * i - f * h)    -(b * i - c * h)     (b * f - c * e)
        // -(d * i - f * g)     (a * i - c * g)    -(a * f - c * d)
        //  (d * h - e * g)    -(a * h - b * g)     (a * e - b * d)
        // 

        //auto hgg = Traits::Swizzle<3, 0, 0, 1>( v2 );
        auto c0 = Traits::FMSub( edd, iih, Traits::Mul( ffe, hgg ) );
        auto baa = Traits::Swizzle<SIMD::Shuffle_v<3, 0, 0, 1>>( v0 );
        auto ccb = Traits::Swizzle<SIMD::Shuffle_v<3, 1, 2, 2>>( v0 );

        auto c1 = Traits::FMSub( baa, iih, Traits::Mul( ccb, hgg ) );
        auto c2 = Traits::FMSub( baa, ffe, Traits::Mul( ccb, edd ) );

        Traits::SIMDType sign1( { { -1.0f, 1.0f, -1.0f, 0.0f } } );
        c0 = Traits::Mul( c0, sign0 );
        c1 = Traits::Mul( c1, sign1 );
        c2 = Traits::Mul( c2, sign0 );

        auto rDet = Traits::Div( { { 1.0f, 1.0f, 1.0f, 0.0f } }, det );
        c0 = Traits::Mul( c0, rDet );
        c1 = Traits::Mul( c1, rDet );
        c2 = Traits::Mul( c2, rDet );

        //
        // a d g
        // b e h
        // c f i

        auto rmm4 = Traits::Shuffle<1, 0, 1, 0>( c0, c1 );
        auto rmm5 = Traits::Shuffle<2, 2, 2, 2>( c0, c1 );

        Simd result;

        result.simd[ 0 ] = Traits::Shuffle<3, 0, 2, 0>( rmm4, c2 );
        result.simd[ 1 ] = Traits::Shuffle<3, 1, 3, 1>( rmm4, c2 );
        result.simd[ 2 ] = Traits::Shuffle<3, 2, 2, 0>( rmm5, c2 );

        return result;
    }

    inline typename SquareMatrix<float, 3>::Simd Inverse( const SquareMatrix<float, 3>& matrix, typename Vector<float, 3>::Simd* determinant = nullptr )
    {
        return Inverse( matrix.ToSimd( ), determinant );
    }


    inline typename SquareMatrix<float, 2>::Simd Transpose( const typename SquareMatrix<float, 2>::Simd& matrix )
    {
        using Traits = SquareMatrix<float, 2>::Traits;
        using Simd = typename SquareMatrix<float, 2>::Simd;
        return Simd( Traits::Swizzle< SIMD::Shuffle_v<3, 1, 2, 0>>( matrix.simd ) );
    }

    inline SquareMatrix<float, 2>::Simd Transpose( const SquareMatrix<float, 2>& matrix )
    {
        return Transpose( matrix.ToSimd( ) );
    }


    inline typename Vector<float, 2>::Simd Determinant( const typename SquareMatrix<float, 2>::Simd& matrix )
    {
        using Traits = SquareMatrix<float, 2>::Traits;
        using Simd = typename Vector<float, 2>::Simd;

        auto rmm1 = Traits::Swizzle<SIMD::Shuffle_v<2, 1, 3, 0>>( matrix.simd );
        auto rmm2 = Traits::Swizzle<SIMD::Shuffle_v<2, 3, 0, 1>>( rmm1 );
        rmm1 = Traits::Mul( rmm1, rmm2 );
        rmm1 = Traits::Mul( rmm1, { {1.f,1.f,-1.f,-1.f} } );
        rmm2 = Traits::Swizzle< SIMD::Shuffle_v<1, 0, 3, 2>>( rmm1 );
        return Simd( Traits::Add( rmm1, rmm2 ) );
    }

    inline typename Vector<float, 2>::Simd Determinant( const SquareMatrix<float, 2>& matrix )
    {
        return Determinant( matrix.ToSimd( ) );
    }


    inline typename SquareMatrix<float, 2>::Simd Inverse( const typename SquareMatrix<float, 2>::Simd& matrix, typename SquareMatrix<float, 2>::Simd* determinant = nullptr )
    {
        using Traits = SquareMatrix<float, 2>::Traits;
        using Simd = typename SquareMatrix<float, 2>::Simd;
        auto rmm1 = Traits::Swizzle<SIMD::Shuffle_v<2, 1, 3, 0>>( matrix.simd );
        auto rmm2 = Traits::Swizzle<SIMD::Shuffle_v<2, 3, 0, 1>>( rmm1 );
        rmm1 = Traits::Mul( rmm1, rmm2 );
        rmm1 = Traits::Mul( rmm1, { {1.f,1.f,-1.f,-1.f} } );
        rmm2 = Traits::Swizzle< SIMD::Shuffle_v<1, 0, 3, 2>>( rmm1 );
        rmm1 = Traits::Add( rmm1, rmm2 );
        if ( determinant )
        {
            ( *determinant ).simd = rmm1;
        }
        rmm1 = Traits::Div( { {1.f,1.f,1.f,1.f} }, rmm1 );
        rmm2 = Traits::Swizzle< SIMD::Shuffle_v<0, 2, 1, 3>>( matrix.simd );
        rmm2 = Traits::Mul( rmm2, { {1.f,-1.f,-1.f,1.f} } );
        return Simd( Traits::Mul( rmm1, rmm2 ) );
    }

    inline SquareMatrix<float, 2>::Simd Inverse( const SquareMatrix<float, 2>& matrix )
    {
        return Inverse( matrix.ToSimd( ) );
    }


    /// <summary>
    /// Creates a translation matrix using the provided offsets.
    /// </summary>
    /// <param name="offsetX">
    /// Translation along the x-axis.
    /// </param>
    /// <param name="offsetY">
    /// Translation along the y-axis.
    /// </param>
    /// <param name="offsetZ">
    /// Translation along the z-axis.
    /// </param>
    /// <returns>
    /// The translation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Translation( float offsetX, float offsetY, float offsetZ )
    {
        using Simd = SquareMatrix<float, 4>::Simd;
        using Traits = Simd::Traits;
        using SIMDType = Traits::SIMDType;
        constexpr SIMDType r1 = { { 1.0f, 0.0f, 0.0f, 0.0f } };
        constexpr SIMDType r2 = { { 0.0f, 1.0f, 0.0f, 0.0f } };
        constexpr SIMDType r3 = { { 0.0f, 0.0f, 1.0f, 0.0f } };

        Simd result;
        result.simd[ 0 ] = r1;
        result.simd[ 1 ] = r2;
        result.simd[ 2 ] = r3;
        result.simd[ 3 ] = Traits::Set( 1.f, offsetZ, offsetY, offsetX );
        return result;
    }

    /// <summary>
    /// Creates a translation matrix using the provided offsets.
    /// </summary>
    /// <param name="offsets">
    /// Translations along the x, y and z axis.
    /// </param>
    /// <returns>
    /// The translation matrix.
    /// </returns>
    template<SimdType S>
        requires ( S::Size > 2 ) && std::is_same_v<typename S::value_type, float>
    inline SquareMatrix<float, 4>::Simd Translation( const S& offsets )
    {
        using Simd = SquareMatrix<float, 4>::Simd;
        using Traits = Simd::Traits;
        using SIMDType = Traits::SIMDType;
        constexpr SIMDType r1 = { { 1.0f, 0.0f, 0.0f, 0.0f } };
        constexpr SIMDType r2 = { { 0.0f, 1.0f, 0.0f, 0.0f } };
        constexpr SIMDType r3 = { { 0.0f, 0.0f, 1.0f, 0.0f } };
        constexpr SIMDType r4 = { { 0.0f, 0.0f, 0.0f, 1.0f } };
        constexpr SIMDType columnSelect = { { std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), 0 } };

        Simd result;
        result.simd[ 0 ] = r1;
        result.simd[ 1 ] = r2;
        result.simd[ 2 ] = r3;
        result.simd[ 3 ] = Traits::Select( r4, offsets.simd, columnSelect );
        return result;
    }

    /// <summary>
    /// Creates a translation matrix using the provided offsets.
    /// </summary>
    /// <param name="offsets">
    /// Translations along the x, y and z axis.
    /// </param>
    /// <returns>
    /// The translation matrix.
    /// </returns>
    template<TupleType S>
        requires ( S::Size > 2 ) && std::is_same_v<typename S::value_type, float>
    inline SquareMatrix<float, 4>::Simd Translation( const S& offsets )
    {
        return Translation( offsets.x, offsets.y, offsets.z );
    }


    inline SquareMatrix<float, 3>::Simd Translation( float offsetX, float offsetY )
    {
        using Simd = SquareMatrix<float, 3>::Simd;
        using Traits = Simd::Traits;
        using SIMDType = Traits::SIMDType;
        constexpr SIMDType r1 = { { 1.0f, 0.0f, 0.0f, 0.0f } };
        constexpr SIMDType r2 = { { 0.0f, 1.0f, 0.0f, 0.0f } };

        Simd result;
        result.simd[ 0 ] = r1;
        result.simd[ 1 ] = r2;
        result.simd[ 2 ] = Traits::Set( 1.f, offsetY, offsetX );
        return result;
    }


    /// <summary>
    /// Creates a transformation matrix for scaling along 
    /// the x-axis, y-axis, and z-axis.
    /// </summary>
    /// <param name="scaleX">
    /// Scaling factor along the x-axis.
    /// </param>
    /// <param name="scaleY">
    /// Scaling factor along the y-axis.
    /// </param>
    /// <param name="scaleZ">
    /// Scaling factor along the z-axis.
    /// </param>
    /// <returns>
    /// The scaling matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Scaling( float scaleX, float scaleY, float scaleZ )
    {
        using Simd = SquareMatrix<float, 4>::Simd;
        using Traits = Simd::Traits;
        using SIMDType = Traits::SIMDType;

        constexpr SIMDType r4 = { { 0.0f, 0.0f, 0.0f, 1.0f } };

        Simd result;

        result.simd[ 0 ] = Traits::Set( scaleX );
        result.simd[ 1 ] = Traits::Set( scaleY, 0 );
        result.simd[ 2 ] = Traits::Set( scaleZ, 0, 0 );
        result.simd[ 3 ] = r4;
        return result;
    }

    /// <summary>
    /// Creates a transformation matrix for scaling along 
    /// the x-axis, y-axis, and z-axis.
    /// </summary>
    /// <param name="v">
    /// Scaling factor along the x-axis, y-axis, and z-axis.
    /// </param>
    /// <returns>
    /// The scaling matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Scaling( float scale )
    {
        return Scaling( scale, scale, scale );
    }

    /// <summary>
    /// Creates a transformation matrix for scaling along 
    /// the x-axis, y-axis, and z-axis.
    /// </summary>
    /// <param name="v">
    /// Scaling factors along the x-axis, y-axis, and z-axis.
    /// </param>
    /// <returns>
    /// The scaling matrix.
    /// </returns>
    template<SimdType S>
        requires ( S::Size > 2 )
    inline SquareMatrix<float, 4>::Simd Scaling( const S& v ) noexcept
    {
        using SourceTraits = typename S::Traits;
        using MatrixSimd = SquareMatrix<float, 4>::Simd;
        using SIMDType = typename SourceTraits::SIMDType;

        constexpr auto bitsSet = std::bit_cast< float >( 0xFFFFFFFF );
        constexpr auto bitsClear = std::bit_cast< float >( 0x00000000 );
        constexpr SIMDType xMask = { {bitsSet, bitsClear, bitsClear, bitsClear} };
        constexpr SIMDType yMask = { {bitsClear, bitsSet, bitsClear, bitsClear} };
        constexpr SIMDType zMask = { {bitsClear, bitsClear, bitsSet, bitsClear} };
        constexpr SIMDType r4 = { { 0.0f, 0.0f, 0.0f, 1.0f } };

        MatrixSimd result;

        result.simd[ 0 ] = SourceTraits::And( v.simd, xMask );
        result.simd[ 1 ] = SourceTraits::And( v.simd, yMask );
        result.simd[ 2 ] = SourceTraits::And( v.simd, zMask );
        result.simd[ 3 ] = r4;
        return result;
    }

    /// <summary>
    /// Creates a transformation matrix for scaling along 
    /// the x-axis, y-axis, and z-axis.
    /// </summary>
    /// <param name="v">
    /// Scaling factors along the x-axis, y-axis, and z-axis.
    /// </param>
    /// <returns>
    /// The scaling matrix.
    /// </returns>
    template<TupleType S>
        requires ( S::Size > 2 )
    inline SquareMatrix<float, 4>::Simd Scaling( const S& v ) noexcept
    {
        using SourceTraits = typename S::Traits;
        using MatrixSimd = SquareMatrix<float, 4>::Simd;
        using SIMDType = typename SourceTraits::SIMDType;

        constexpr SIMDType r4 = { { 0.0f, 0.0f, 0.0f, 1.0f } };

        MatrixSimd result;

        result.simd[ 0 ] = SourceTraits::Set( v.x );
        result.simd[ 1 ] = SourceTraits::Set( v.y, 0 );
        result.simd[ 2 ] = SourceTraits::Set( v.z, 0, 0 );
        result.simd[ 3 ] = r4;
        return result;

    }

    inline SquareMatrix<float, 3>::Simd Scaling( float scaleX, float scaleY )
    {
        using Simd = SquareMatrix<float, 3>::Simd;
        using Traits = Simd::Traits;
        using SIMDType = Traits::SIMDType;

        constexpr SIMDType r3 = { { 0.0f, 0.0f, 1.0f, 0.0f } };

        Simd result;

        result.simd[ 0 ] = Traits::Set( scaleX );
        result.simd[ 1 ] = Traits::Set( scaleY, 0 );
        result.simd[ 3 ] = r3;
        return result;
    }

    /// <summary>
    /// Creates a transformation matrix that rotates about the y-axis, 
    /// then the x-axis, and finally the z-axis
    /// </summary>
    /// <param name="v">
    /// The angles of rotation around the x-axis, y-axis and z-axis, in radians.
    /// </param>
    /// <returns>
    /// The transformation matrix.
    /// </returns>
    template<SimdType S>
        requires ( S::Size > 2 )
    inline SquareMatrix<float, 4>::Simd Rotation( const S& v ) noexcept
    {
        using Simd = SquareMatrix<float, 4>::Simd;
        using Traits = Simd::Traits;
        using SIMDType = Traits::SIMDType;
        using P = Traits::PermuteType;

        constexpr SIMDType sign = { { 1.0f, -1.0f, -1.0f, 1.0f } };
        constexpr SIMDType r4 = { { 0.0f, 0.0f, 0.0f, 1.0f } };
        constexpr SIMDType zero = { { 0.0f, 0.0f, 0.0f, 0.0f } };
        constexpr SIMDType columnSelect = { { std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), 0 } };

        SIMDType cosines;
        auto sines = Traits::FastSinCos( v.simd, &cosines );

        auto p0 = Traits::Permute<P::X2, P::Z1, P::Z2, P::X2>( sines, cosines );
        auto p1 = Traits::Permute<P::Z2, P::Z1, P::Z2, P::Z1>( sines, cosines );
        auto p2 = Traits::Permute<P::Z1, P::Z2, P::Z1, P::Z2>( sines, cosines );
        auto p3 = Traits::Permute<P::Y1, P::Y1, P::Y2, P::Y2>( sines, cosines );

        auto y0 = Traits::Permute<P::Y1, P::X2, P::X2, P::Y2>( sines, cosines );
        auto y1 = Traits::Permute<P::Y2, P::Y2, P::Y1, P::Y1>( sines, cosines );
        auto y2 = Traits::At<0>( sines );

        auto ns = Traits::Negate( sines );


        auto q1 = Traits::Mul( p1, sign );
        q1 = Traits::Mul( q1, y1 );
        auto q2 = Traits::Mul( p2, y2 );
        q2 = Traits::FMAdd( q2, p3, q1 );

        auto q0 = Traits::Mul( p0, y0 );

        auto v0 = Traits::Permute<P::X2, P::Y1, P::Z2, P::W1>( q0, q2 );
        auto v1 = Traits::Permute<P::Y2, P::Z1, P::W2, P::W1>( q0, q2 );
        auto v2 = Traits::Permute<P::X1, P::X2, P::W1, P::W1>( q0, ns );

        Simd result;
        result.simd[ 0 ] = Traits::Select( zero, v0, columnSelect );
        result.simd[ 1 ] = Traits::Select( zero, v1, columnSelect );
        result.simd[ 2 ] = Traits::Select( zero, v2, columnSelect );
        result.simd[ 3 ] = r4;
        return result;
    }

    /// <summary>
    /// Creates a transformation matrix that rotates about the y-axis, 
    /// then the x-axis, and finally the z-axis.
    /// </summary>
    /// <param name="v">
    /// The angles of rotation around the x-axis, y-axis and z-axis, in radians.
    /// </param>
    /// <returns>
    /// The transformation matrix.
    /// </returns>
    template<TupleType S>
        requires ( S::Size > 2 )
    inline SquareMatrix<float, 4>::Simd Rotation( const S& v ) noexcept
    {
        return Rotation( v.ToSimd( ) );
    }

    /// <summary>
    /// Creates a transformation matrix that rotates about the y-axis, 
    /// then the x-axis, and finally the z-axis.
    /// </summary>
    /// <param name="xAxisRotation">
    /// The angle of rotation around the x-axis, in radians.
    /// </param>
    /// <param name="yAxisRotation">
    /// The angle of rotation around the y-axis, in radians.
    /// </param>
    /// <param name="zAxisRotation">
    /// The angle of rotation around the z-axis, in radians.
    /// </param>
    /// <returns>
    /// The transformation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Rotation( float xAxisRotation, float yAxisRotation, float zAxisRotation ) noexcept
    {
        using Simd = Vector<float, 3>::Simd;
        using Traits = Simd::Traits;
        return Rotation( Simd( Traits::Set( zAxisRotation, yAxisRotation, xAxisRotation ) ) );
    }

    /// <summary>
    /// Creates a matrix that rotates around the x-axis.
    /// </summary>
    /// <param name="angle">
    /// Thw clockwise angle of rotation, in radians, around the x-axis 
    /// when looking along the rotation axis toward the origin.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd RotationX( float angle ) noexcept
    {
        using Traits = SquareMatrix<float, 4>::Traits;
        using Constants = Traits::Constants;
        using Simd = SquareMatrix<float, 4>::Simd;
        float sine;
        float cosine;
        SinCos( angle, &sine, &cosine );

        auto sines = Traits::Set( sine );
        auto cosines = Traits::Set( cosine );
        cosines = Traits::Shuffle<3, 0, 0, 3>( cosines, sines );
        Simd result;
        result.simd[ 0 ] = Constants::IdentityR1;
        result.simd[ 1 ] = cosines;
        cosines = Traits::Shuffle<3, 1, 2, 0>( cosines );
        cosines = Traits::Mul( cosines, Constants::NegateY );
        result.simd[ 2 ] = cosines;
        result.simd[ 3 ] = Constants::IdentityR4;
        return result;
    }

    /// <summary>
    /// Creates a matrix that rotates around the y-axis.
    /// </summary>
    /// <param name="angle">
    /// Thw clockwise angle of rotation, in radians, around the y-axis 
    /// when looking along the rotation axis toward the origin.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd RotationY( float angle ) noexcept
    {
        using Traits = SquareMatrix<float, 4>::Traits;
        using Constants = Traits::Constants;
        using Simd = SquareMatrix<float, 4>::Simd;
        float sine;
        float cosine;
        SinCos( angle, &sine, &cosine );

        auto sines = Traits::Set( sine );
        auto cosines = Traits::Set( cosine );

        sines = Traits::Shuffle<3, 0, 3, 0>( sines, cosines );
        Simd result;
        result.simd[ 1 ] = Constants::IdentityR2;
        result.simd[ 2 ] = sines;

        sines = Traits::Shuffle<3, 0, 1, 2>( sines );
        sines = Traits::Mul( sines, Constants::NegateZ );
        result.simd[ 0 ] = sines;
        result.simd[ 3 ] = Constants::IdentityR4;
        return result;
    }

    /// <summary>
    /// Creates a matrix that rotates around the z-axis.
    /// </summary>
    /// <param name="angle">
    /// Thw clockwise angle of rotation, in radians, around the z-axis 
    /// when looking along the rotation axis toward the origin.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd RotationZ( float angle ) noexcept
    {
        using Traits = SquareMatrix<float, 4>::Traits;
        using Constants = Traits::Constants;
        using Simd = SquareMatrix<float, 4>::Simd;
        float sine;
        float cosine;
        SinCos( angle, &sine, &cosine );

        auto sines = Traits::Set( sine );
        auto cosines = Traits::Set( cosine );

        cosines = Traits::UnpackLow( cosines, sines );
        Simd result;
        result.simd[ 0 ] = cosines;
        cosines = Traits::Shuffle<3, 2, 0, 1>( cosines );
        cosines = Traits::Mul( cosines, Constants::NegateX );
        result.simd[ 1 ] = cosines;
        result.simd[ 2 ] = Constants::IdentityR3;
        result.simd[ 3 ] = Constants::IdentityR4;
        return result;
    }


    /// <summary>
    /// Creates a matrix that rotates around a normalized vector.
    /// </summary>
    /// <param name="normalizedAxis">
    /// Normalized vector defining the axis of rotation.
    /// </param>
    /// <param name="angle">
    /// The angle of rotation in radians, measured clockwise when 
    /// looking along the rotation axis toward the origin.
    /// </param>
    /// <returns>
    /// The rotation matrix
    /// </returns>
    template<SimdType S>
        requires ( S::Size > 2 )
    inline SquareMatrix<float, 4>::Simd RotationNormal( const S& normalizedAxis, float angle ) noexcept
    {
        using Traits = SIMD::Traits<float, 4>;
        using Constants = typename Traits::Constants;
        using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
        using SIMDType = typename Traits::SIMDType;
        constexpr SIMDType maskXYZ{ { std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), 0x00000000 } };

        float sine;
        float cosine;

        SinCos( angle, &sine, &cosine );

        auto C0 = Traits::Fill( sine );
        auto C1 = Traits::Fill( cosine );
        auto C2 = Traits::Fill( 1.0f - cosine );


        auto N0 = Traits::Shuffle<3, 0, 2, 1>( normalizedAxis.simd );
        auto N1 = Traits::Shuffle<3, 1, 0, 2>( normalizedAxis.simd );

        auto V0 = Traits::Mul( C2, N0 );
        V0 = Traits::Mul( V0, N1 );

        auto R0 = Traits::Mul( C2, normalizedAxis.simd );
        R0 = Traits::FMAdd( R0, normalizedAxis.simd, C1 );

        auto R1 = Traits::FMAdd( C0, normalizedAxis.simd, V0 );

        //auto R2 = Traits::Mul( C0, normalizedAxis.simd );
        //R2 = Traits::Sub( V0, R2 );
        auto R2 = Traits::FNMAdd( C0, normalizedAxis.simd, V0 );

        V0 = Traits::And( R0, maskXYZ );
        auto V1 = Traits::Shuffle<2, 1, 2, 0>( R1, R2 );
        V1 = Traits::Shuffle<0, 3, 2, 1>( V1, V1 );
        auto V2 = Traits::Shuffle<0, 0, 1, 1>( R1, R2 );
        V2 = Traits::Shuffle<2, 0, 2, 0>( V2, V2 );

        R2 = Traits::Shuffle<1, 0, 3, 0>( V0, V1 );
        R2 = Traits::Shuffle<1, 3, 2, 0>( R2, R2 );

        MatrixSimd result;
        result.simd[ 0 ] = R2;

        R2 = Traits::Shuffle<3, 2, 3, 1>( V0, V1 );
        R2 = Traits::Shuffle<1, 3, 0, 2>( R2, R2 );
        result.simd[ 1 ] = R2;

        V2 = Traits::Shuffle<3, 2, 1, 0>( V2, V0 );
        result.simd[ 2 ] = V2;
        result.simd[ 3 ] = { { 0.0f, 0.0f, 0.0f, 1.0f } };
        return result;
    }

    /// <summary>
    /// Creates a matrix that rotates around a normalized vector.
    /// </summary>
    /// <param name="normalizedAxis">
    /// Normalized vector defining the axis of rotation.
    /// </param>
    /// <param name="angle">
    /// The angle of rotation in radians, measured clockwise when 
    /// looking along the rotation axis toward the origin.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    template<TupleType S>
        requires ( S::Size > 2 )
    inline SquareMatrix<float, 4>::Simd RotationNormal( const S& normalizedAxis, float angle ) noexcept
    {
        using Simd = typename S::Simd;
        return RotationNormal( Simd( normalizedAxis ), angle );
    }

    /// <summary>
    /// Creates a matrix that rotates around an arbitrary axis.
    /// </summary>
    /// <param name="axis">
    /// The axis of rotation.
    /// </param>
    /// <param name="angle">
    /// The angle of rotation in radians, measured clockwise when 
    /// looking along the rotation axis toward the origin.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    template<SimdOrTupleType S>
        requires ( S::Size > 2 )
    inline SquareMatrix<float, 4>::Simd RotationAxis( const S& axis, float angle ) noexcept
    {
        return RotationNormal( Normalize( axis ), angle );
    }


    /// <summary>
    /// Creates a rotation matrix from a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion that defines the rotation.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Rotation( const Quaternion<float>::Simd& q ) noexcept
    {
        using Traits = SIMD::Traits<float, 4>;
        using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
        using SIMDType = typename Traits::SIMDType;
        constexpr SIMDType maskXYZ{ { std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), 0x00000000 } };

        auto Q0 = Traits::Add( q.simd, q.simd );
        auto Q1 = Traits::Mul( q.simd, Q0 );

        auto V0 = Traits::Shuffle<3, 0, 0, 1>( Q1 );
        V0 = Traits::And( V0, maskXYZ );
        auto V1 = Traits::Shuffle<3, 1, 2, 2>( Q1 );
        V1 = Traits::And( V1, maskXYZ );
        auto R0 = Traits::Sub( { { 1.0f, 1.0f, 1.0f, 0.0f } }, V0 );
        R0 = Traits::Sub( R0, V1 );

        V0 = Traits::Shuffle<3, 1, 0, 0>( q.simd );
        V1 = Traits::Shuffle<3, 2, 1, 2>( Q0 );
        V0 = Traits::Mul( V0, V1 );

        V1 = Traits::Shuffle<3, 3, 3, 3>( q.simd );
        auto V2 = Traits::Shuffle<3, 0, 2, 1>( Q0 );
        V1 = Traits::Mul( V1, V2 );

        auto R1 = Traits::Add( V0, V1 );
        auto R2 = Traits::Sub( V0, V1 );

        V0 = Traits::Shuffle<1, 0, 2, 1>( R1, R2 );
        V0 = Traits::Shuffle<1, 3, 2, 0>( V0 );
        V1 = Traits::Shuffle<2, 2, 0, 0>( R1, R2 );
        V1 = Traits::Shuffle<2, 0, 2, 0>( V1 );

        Q1 = Traits::Shuffle<1, 0, 3, 0>( R0, V0 );
        Q1 = Traits::Shuffle<1, 3, 2, 0>( Q1 );

        MatrixSimd result;
        result.simd[ 0 ] = Q1;

        Q1 = Traits::Shuffle<3, 2, 3, 1>( R0, V0 );
        Q1 = Traits::Shuffle<1, 3, 0, 2>( Q1 );
        result.simd[ 1 ] = Q1;

        Q1 = Traits::Shuffle<3, 2, 1, 0>( V1, R0 );
        result.simd[ 2 ] = Q1;
        result.simd[ 3 ] = { { 0.0f, 0.0f, 0.0f, 1.0f } };;
        return result;
    }

    /// <summary>
    /// Creates a rotation matrix from a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion that defines the rotation.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd Rotation( const Quaternion<float>& q ) noexcept
    {
        return Rotation( q.ToSimd( ) );
    }


    /// <summary>
    /// Creates a rotation matrix from a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion that defines the rotation.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd RotationQuaternion( const Quaternion<float>::Simd& q ) noexcept
    {
        return Rotation( q );
    }

    /// <summary>
    /// Creates a rotation matrix from a quaternion.
    /// </summary>
    /// <param name="q">
    /// The quaternion that defines the rotation.
    /// </param>
    /// <returns>
    /// The rotation matrix.
    /// </returns>
    inline SquareMatrix<float, 4>::Simd RotationQuaternion( const Quaternion<float>& q ) noexcept
    {
        return Rotation( q.ToSimd( ) );
    }


    namespace Internal
    {
        /// <summary>
        /// Creates a transformation matrix.
        /// </summary>
        /// <param name="scalingOrigin">
        /// The center of the scaling.
        /// </param>
        /// <param name="scalingOrientationQuaternion">
        /// The orientation of the scaling.
        /// </param>
        /// <param name="scaling">
        /// The scaling factors for the x-axis, y-axis, and z-axis.
        /// </param>
        /// <param name="rotationOrigin">
        /// The center of the rotation.
        /// </param>
        /// <param name="rotationQuaternion">
        /// The rotation around the origin provided by rotationOrigin parameter.
        /// </param>
        /// <param name="translation">
        /// The translations along the x-axis, y-axis, and z-axis.
        /// </param>
        /// <returns>
        /// The transformation matrix.
        /// </returns>
        inline SquareMatrix<float, 4>::Simd TransformationMatrixImpl( const Point3f::Simd& scalingOrigin,
            const Quaternion<float>::Simd& scalingOrientationQuaternion,
            const Vector<float, 3>::Simd& scaling,
            const Point3f::Simd& rotationOrigin,
            const Quaternion<float>::Simd& rotationQuaternion,
            const Vector<float, 3>::Simd& translation ) noexcept
        {
            using Traits = SIMD::Traits<float, 4>;
            using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
            using SIMDType = typename Traits::SIMDType;
            constexpr SIMDType columnSelect = { { std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), 0 } };

            auto filteredScalingOrigin = Traits::Select( columnSelect, scalingOrigin.simd, columnSelect );
            auto negScalingOrigin = -scalingOrigin;

            auto scalingOriginI = Translation( negScalingOrigin );
            auto scalingOrientation = RotationQuaternion( scalingOrientationQuaternion );
            auto scalingOrientationT = Transpose( scalingOrientation );
            auto scalingMatrix = Scaling( scaling );
            auto filteredRotationOrigin = Traits::Select( columnSelect, rotationOrigin.simd, columnSelect );
            auto rotationMatrix = RotationQuaternion( rotationQuaternion );
            auto filteredTranslation = Traits::Select( columnSelect, translation.simd, columnSelect );


            auto result = scalingOriginI * scalingOrientationT;
            result = result * scalingMatrix;
            result = result * scalingOrientation;
            result.simd[ 3 ] = Traits::Add( result.simd[ 3 ], filteredScalingOrigin );
            result.simd[ 3 ] = Traits::Sub( result.simd[ 3 ], filteredRotationOrigin );
            result = result * rotationMatrix;
            result.simd[ 3 ] = Traits::Add( result.simd[ 3 ], filteredRotationOrigin );
            result.simd[ 3 ] = Traits::Add( result.simd[ 3 ], filteredTranslation );
            return result;
        }
    }


    /// <summary>
    /// Creates a transformation matrix.
    /// </summary>
    /// <param name="scalingOrigin">
    /// The center of the scaling.
    /// </param>
    /// <param name="scalingOrientationQuaternion">
    /// The orientation of the scaling.
    /// </param>
    /// <param name="scaling">
    /// The scaling factors for the x-axis, y-axis, and z-axis.
    /// </param>
    /// <param name="rotationOrigin">
    /// The center of the rotation.
    /// </param>
    /// <param name="rotationQuaternion">
    /// The rotation around the origin provided by rotationOrigin parameter.
    /// </param>
    /// <param name="translation">
    /// The translations along the x-axis, y-axis, and z-axis.
    /// </param>
    /// <returns>
    /// The transformation matrix.
    /// </returns>
    template<PointOrPointSimdType PointT, QuaternionOrQuaternionSimdType QuaternionT, VectorOrVectorSimdType VectorT>
        requires ( PointT::Size == 3 ) && ( VectorT::Size == 3 ) && std::is_same_v<typename PointT::value_type, typename QuaternionT::value_type>&& std::is_same_v<typename PointT::value_type, typename VectorT::value_type>
    inline SquareMatrix<typename PointT::value_type, 4>::Simd TransformationMatrix( const PointT& scalingOrigin,
        const QuaternionT& scalingOrientationQuaternion,
        const VectorT& scaling,
        const PointT& rotationOrigin,
        const QuaternionT& rotationQuaternion,
        const VectorT& translation ) noexcept
    {
        return Internal::TransformationMatrixImpl( Internal::ToSimdType( scalingOrigin ),
            Internal::ToSimdType( scalingOrientationQuaternion ),
            Internal::ToSimdType( scaling ),
            Internal::ToSimdType( rotationOrigin ),
            Internal::ToSimdType( rotationQuaternion ),
            Internal::ToSimdType( translation ) );
    }

    namespace Internal
    {
        /// <summary>
        /// Creates an affine transformation matrix.
        /// </summary>
        /// <param name="scaling">
        /// The scaling factors for each dimension.
        /// </param>
        /// <param name="rotationOrigin">
        /// The center of rotation.
        /// </param>
        /// <param name="rotationQuaternion">
        /// Rotation factors as a quaternion.
        /// </param>
        /// <param name="translation">
        /// The translation offsets.
        /// </param>
        /// <returns></returns>
        template<SimdType S, SimdType T, typename U, SimdType W>
            requires ( S::Size > 2 ) && ( T::Size > 2 ) && ( W::Size > 2 ) && IsFloatingPoint<U>&&
        std::is_same_v<typename S::value_type, U>&& std::is_same_v<typename T::value_type, U>&&
            std::is_same_v<typename W::value_type, U>
            inline SquareMatrix<U, 4>::Simd AffineTransformationMatrixImpl( const S& scaling,
                const T& rotationOrigin,
                const QuaternionSimd<Quaternion<U>>& rotationQuaternion,
                const W& translation ) noexcept
        {
            using Traits = SIMD::Traits<U, 4>;
            using Constants = typename Traits::Constants;

            auto result = Scaling( scaling );
            auto rotationOriginXYZ = Traits::Select( Constants::Select2221, rotationOrigin.simd, Constants::Select2221 );
            auto rotationMatrix = RotationQuaternion( rotationQuaternion );
            auto translationXYZ = Traits::Select( Constants::Select2221, translation.simd, Constants::Select2221 );

            result.simd[ 3 ] = Traits::Sub( result.simd[ 3 ], rotationOriginXYZ );
            result = result * rotationMatrix;
            result.simd[ 3 ] = Traits::Add( result.simd[ 3 ], rotationOriginXYZ );
            result.simd[ 3 ] = Traits::Add( result.simd[ 3 ], translationXYZ );
            return result;
        }
    }

    /// <summary>
    /// Creates an affine transformation matrix.
    /// </summary>
    /// <param name="scaling">
    /// The scaling factors for each dimension.
    /// </param>
    /// <param name="rotationOrigin">
    /// The center of rotation.
    /// </param>
    /// <param name="rotationQuaternion">
    /// Rotation factors as a quaternion.
    /// </param>
    /// <param name="translation">
    /// The translation offsets.
    /// </param>
    /// <returns></returns>
    template<SimdOrTupleType S, SimdOrTupleType T, QuaternionOrQuaternionSimdType U, SimdOrTupleType W>
        requires ( S::Size > 2 ) && ( T::Size > 2 ) && ( W::Size > 2 ) &&
    std::is_same_v<typename S::value_type, typename T::value_type>&&
        std::is_same_v<typename S::value_type, typename U::value_type>&&
        std::is_same_v<typename S::value_type, typename W::value_type>
        inline SquareMatrix<typename S::value_type, 4>::Simd AffineTransformationMatrix( const S& scaling,
            const T& rotationOrigin,
            const U& rotationQuaternion,
            const W& translation ) noexcept
    {
        return Internal::AffineTransformationMatrixImpl( Internal::ToSimdType( scaling ), Internal::ToSimdType( rotationOrigin ), Internal::ToSimdType( rotationQuaternion ), Internal::ToSimdType( translation ) );
    }

    namespace Internal
    {
        /// <summary>
        /// Creates a view matrix using the left-handed coordinate system for the
        /// provided camera position, camera direction, and up direction.
        /// </summary>
        /// <param name="cameraPosition">
        /// The camera position.
        /// </param>
        /// <param name="cameraDirection">
        /// The camera direction.
        /// </param>
        /// <param name="upDirection">
        /// The up direction of the camera, often [0 1 0]
        /// </param>
        /// <returns>
        /// The view matrix transforming coordinates from world space to view space.
        /// </returns>
        template<SimdType S, SimdType T, SimdType U>
            requires IsCompatible<S, T, U> && ( S::Size == 3 )
        inline SquareMatrix<typename S::value_type, 4>::Simd LookToImpl( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
        {
            using Traits = SIMD::Traits<typename S::value_type, 4>;
            using Constants = typename Traits::Constants;
            using MatrixSimd = SquareMatrix<typename S::value_type, 4>::Simd;
            auto r2 = Normalize( cameraDirection );

            auto r0 = Cross( upDirection, r2 );
            r0 = Normalize( r0 );

            auto r1 = Cross( r2, r0 );

            auto negCameraPosition = -cameraPosition;

            auto d0 = Dot<0xFF>( r0, negCameraPosition );
            auto d1 = Dot<0xFF>( r1, negCameraPosition );
            auto d2 = Dot<0xFF>( r2, negCameraPosition );

            MatrixSimd result;
            result.simd[ 0 ] = Traits::Select( d0.simd, r0.simd, Constants::Select2221 );
            result.simd[ 1 ] = Traits::Select( d1.simd, r1.simd, Constants::Select2221 );
            result.simd[ 2 ] = Traits::Select( d2.simd, r2.simd, Constants::Select2221 );
            result.simd[ 3 ] = Constants::IdentityR4;

            return Transpose( result );
        }
    }

    /// <summary>
    /// Creates a view matrix using the left-handed coordinate system for the
    /// provided camera position, camera direction, and up direction.
    /// </summary>
    /// <param name="cameraPosition">
    /// The camera position.
    /// </param>
    /// <param name="cameraDirection">
    /// The camera direction.
    /// </param>
    /// <param name="upDirection">
    /// The up direction of the camera, often [0 1 0]
    /// </param>
    /// <returns>
    /// The view matrix transforming coordinates from world space to view space.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
    {
        return Internal::LookToImpl( Internal::ToSimdType( cameraPosition ), Internal::ToSimdType( cameraDirection ), Internal::ToSimdType( upDirection ) );
    }



    /// <summary>
    /// Creates a view matrix using the left-handed coordinate system for the
    /// provided camera position, focal point, and up direction.
    /// </summary>
    /// <param name="cameraPosition">
    /// The camera position.
    /// </param>
    /// <param name="focusPosition">
    /// The focal point.
    /// </param>
    /// <param name="upDirection">
    /// The up direction of the camera, often [0 1 0]
    /// </param>
    /// <returns>
    /// The view matrix transforming coordinates from world space to view space.
    /// </returns>
    template<SimdOrTupleType S, SimdOrTupleType T, SimdOrTupleType U>
        requires IsCompatible<S, T, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        auto cameraDirection = focusPosition - cameraPosition;
        return Internal::LookToImpl( Internal::ToSimdType( cameraPosition ), cameraDirection, Internal::ToSimdType( upDirection ) );
    }

    /// <summary>
    /// Creates a left-handed perspective projection matrix.
    /// </summary>
    /// <param name="viewWidth">
    /// The width of the frustum at the nearest clipping plane.
    /// </param>
    /// <param name="viewHeight">
    /// The height of the frustum at the nearest clipping plane.
    /// </param>
    /// <param name="nearZ">
    /// The distance to the nearest clipping plane. Cannot be equal to <c>farZ</c> and must be greater than zero.
    /// </param>
    /// <param name="farZ">
    /// The distance to the far clipping plane. Cannot be equal to <c>nearZ</c> and must be greater than zero.
    /// </param>
    /// <returns>
    /// The perspective projection matrix.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    inline SquareMatrix<T, 4>::Simd PerspectiveProjection( T viewWidth, T viewHeight, T nearZ, T farZ ) noexcept
    {
        using Traits = SIMD::Traits<T, 4>;
        using Constants = typename Traits::Constants;
        using MatrixSimd = SquareMatrix<T, 4>::Simd;

        T twoNearZ = nearZ + nearZ;
        T range = farZ / ( farZ - nearZ );

        MatrixSimd result;

        result.simd[ 0 ] = Traits::Set( twoNearZ / viewWidth );
        result.simd[ 1 ] = Traits::Set( twoNearZ / viewHeight, 0.f );
        result.simd[ 2 ] = Traits::Set( 1.f, range, 0.f, 0.f );
        result.simd[ 3 ] = Traits::Set( -range * nearZ, 0.f, 0.f );
        return result;
    }

    /// <summary>
    /// Creates a left-handed perspective projection matrix based on a field of view.
    /// </summary>
    /// <param name="fovAngleY">
    /// The top-down field-of-view angle in radians.
    /// </param>
    /// <param name="aspectRatio">
    /// The aspect ratio of the view-space X/Y.
    /// </param>
    /// <param name="nearZ">
    /// The distance to the nearest clipping plane. Cannot be equal to <c>farZ</c> and must be greater than zero.
    /// </param>
    /// <param name="farZ">
    /// The distance to the far clipping plane. Cannot be equal to <c>nearZ</c> and must be greater than zero.
    /// </param>
    /// <returns>
    /// The perspective projection matrix.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    inline SquareMatrix<T, 4>::Simd PerspectiveFovProjection( T fovAngleY, T aspectRatio, T nearZ, T farZ ) noexcept
    {
        using Traits = SIMD::Traits<T, 4>;
        using Constants = typename Traits::Constants;
        using MatrixSimd = SquareMatrix<T, 4>::Simd;

        T sineFov;
        T cosineFov;
        SinCos( static_cast< T >( 0.5 ) * fovAngleY, &sineFov, &cosineFov );

        T height = cosineFov / sineFov;
        T width = height / aspectRatio;
        T range = farZ / ( farZ - nearZ );

        MatrixSimd result;
        result.simd[ 0 ] = Traits::Set( width );
        result.simd[ 1 ] = Traits::Set( height, 0.f );
        result.simd[ 2 ] = Traits::Set( 1.f, range, 0.f, 0.f );
        result.simd[ 3 ] = Traits::Set( -range * nearZ, 0.f, 0.f );
        return result;
    }

    template<typename QuaternionT>
    template<size_t N>
        requires ( N > 2 )
    inline QuaternionSimd<QuaternionT> QuaternionSimd<QuaternionT>::FromMatrix( const std::array<SIMDType, N>& matrix ) noexcept
    {
        using Traits = SIMD::Traits<float, 4>;
        using Constants = Traits::Constants;
        using Simd = QuaternionSimd<QuaternionT>;
        constexpr SIMDType XMPMMP = { { +1.0f, -1.0f, -1.0f, +1.0f } };
        constexpr SIMDType XMMPMP = { { -1.0f, +1.0f, -1.0f, +1.0f } };
        constexpr SIMDType XMMMPP = { { -1.0f, -1.0f, +1.0f, +1.0f } };

        auto r0 = matrix[ 0 ];
        auto r1 = matrix[ 1 ];
        auto r2 = matrix[ 2 ];

        // (r00, r00, r00, r00)
        auto r00 = Traits::Shuffle<0, 0, 0, 0>( r0 );
        // (r11, r11, r11, r11)
        auto r11 = Traits::Shuffle<1, 1, 1, 1>( r1 );
        // (r22, r22, r22, r22)
        auto r22 = Traits::Shuffle<2, 2, 2, 2>( r2 );

        // x^2 >= y^2 equivalent to r11 - r00 <= 0
        // (r11 - r00, r11 - r00, r11 - r00, r11 - r00)
        auto r11mr00 = Traits::Sub( r11, r00 );
        auto x2gey2 = Traits::LessOrEqual( r11mr00, Constants::Zero );

        // z^2 >= w^2 equivalent to r11 + r00 <= 0
        // (r11 + r00, r11 + r00, r11 + r00, r11 + r00)
        auto r11pr00 = Traits::Add( r11, r00 );
        auto z2gew2 = Traits::LessOrEqual( r11pr00, Constants::Zero );

        // x^2 + y^2 >= z^2 + w^2 equivalent to r22 <= 0
        auto x2py2gez2pw2 = Traits::LessOrEqual( r22, Constants::Zero );

        // (4*x^2, 4*y^2, 4*z^2, 4*w^2)
        auto t0 = Traits::FMAdd( XMPMMP, r00, Constants::One );
        auto t1 = Traits::Mul( XMMPMP, r11 );
        auto t2 = Traits::FMAdd( XMMMPP, r22, t0 );
        auto x2y2z2w2 = Traits::Add( t1, t2 );

        // (r01, r02, r12, r11)
        t0 = Traits::Shuffle<1, 2, 2, 1>( r0, r1 );
        // (r10, r10, r20, r21)
        t1 = Traits::Shuffle<1, 0, 0, 0>( r1, r2 );
        // (r10, r20, r21, r10)
        t1 = Traits::Shuffle<1, 3, 2, 0>( t1 );
        // (4*x*y, 4*x*z, 4*y*z, unused)
        auto xyxzyz = Traits::Add( t0, t1 );

        // (r21, r20, r10, r10)
        t0 = Traits::Shuffle<0, 0, 0, 1>( r2, r1 );
        // (r12, r12, r02, r01)
        t1 = Traits::Shuffle<1, 2, 2, 2>( r1, r0 );
        // (r12, r02, r01, r12)
        t1 = Traits::Shuffle<1, 3, 2, 0>( t1 );
        // (4*x*w, 4*y*w, 4*z*w, unused)
        auto xwywzw = Traits::Sub( t0, t1 );
        xwywzw = Traits::Mul( XMMPMP, xwywzw );

        // (4*x^2, 4*y^2, 4*x*y, unused)
        t0 = Traits::Shuffle<0, 0, 1, 0>( x2y2z2w2, xyxzyz );
        // (4*z^2, 4*w^2, 4*z*w, unused)
        t1 = Traits::Shuffle<0, 2, 3, 2>( x2y2z2w2, xwywzw );
        // (4*x*z, 4*y*z, 4*x*w, 4*y*w)
        t2 = Traits::Shuffle<1, 0, 2, 1>( xyxzyz, xwywzw );

        // (4*x*x, 4*x*y, 4*x*z, 4*x*w)
        auto tensor0 = Traits::Shuffle<2, 0, 2, 0>( t0, t2 );
        // (4*y*x, 4*y*y, 4*y*z, 4*y*w)
        auto tensor1 = Traits::Shuffle<3, 1, 1, 2>( t0, t2 );
        // (4*z*x, 4*z*y, 4*z*z, 4*z*w)
        auto tensor2 = Traits::Shuffle<2, 0, 1, 0>( t2, t1 );
        // (4*w*x, 4*w*y, 4*w*z, 4*w*w)
        auto tensor3 = Traits::Shuffle<1, 2, 3, 2>( t2, t1 );

        // Select the row of the tensor-product matrix that has the largest
        // magnitude.
        t0 = Traits::And( x2gey2, tensor0 );
        t1 = Traits::AndNot( x2gey2, tensor1 );
        t0 = Traits::Or( t0, t1 );
        t1 = Traits::And( z2gew2, tensor2 );
        t2 = Traits::AndNot( z2gew2, tensor3 );
        t1 = Traits::Or( t1, t2 );
        t0 = Traits::And( x2py2gez2pw2, t0 );
        t1 = Traits::AndNot( x2py2gez2pw2, t1 );
        t2 = Traits::Or( t0, t1 );

        // Normalize the row.  No division by zero is possible because the
        // quaternion is unit-length (and the row is a nonzero multiple of
        // the quaternion).
        t0 = Length( Math::Vector<value_type, 4>::Simd( t2 ) ).simd;
        return Simd( Traits::Div( t2, t0 ) );
    }
    template<typename QuaternionT>
    inline QuaternionSimd<QuaternionT> QuaternionSimd<QuaternionT>::FromMatrix( const Matrix& matrix ) noexcept
    {
        return FromMatrix( matrix.ToSimd( ) );
    }


    /// <summary>
    /// Transforms a 2D vector by a matrix
    /// </summary>
    /// <param name="v">
    /// </param>
    /// <param name="matrix">
    /// </param>
    /// <returns></returns>
    inline Vector<float, 2>::Simd Transform( const Vector<float, 2>::Simd& v, const SquareMatrix<float, 3>::Simd& matrix ) noexcept
    {
        using Traits = Vector<float, 2>::Traits;
        using Simd = Vector<float, 2>::Simd;
        return Simd( Traits::TransformVector( v.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a 3D vector.
    /// </summary>
    /// <param name="v">
    /// The vector.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Vector<float, 3>::Simd Transform( const Vector<float, 3>::Simd& v, const SquareMatrix<float, 4>::Simd& matrix ) noexcept
    {
        using Traits = Vector<float, 3>::Traits;
        using Simd = Vector<float, 3>::Simd;
        return Simd( Traits::TransformVector( v.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] ) );
    }
    /// <summary>
    /// Applies a transformation matrix to a 3D vector.
    /// </summary>
    /// <param name="v">
    /// The vector.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Vector<float, 3>::Simd Transform( const Vector<float, 3>& v, const SquareMatrix<float, 4>::Simd& matrix ) noexcept
    {
        return Transform( v.ToSimd( ), matrix );
    }

    /// <summary>
    /// Applies a transformation matrix to a 3D vector.
    /// </summary>
    /// <param name="v">
    /// The vector.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Vector<float, 3>::Simd Transform( const Vector<float, 3>::Simd& v, const SquareMatrix<float, 4>& matrix ) noexcept
    {
        return Transform( v, matrix.ToSimd( ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a 3D vector.
    /// </summary>
    /// <param name="v">
    /// The vector.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Vector<float, 3>::Simd Transform( const Vector<float, 3>& v, const SquareMatrix<float, 4>& matrix ) noexcept
    {
        return Transform( v.ToSimd( ), matrix.ToSimd( ) );
    }


    inline Vector<float, 4>::Simd Transform( const Vector<float, 4>::Simd& v, const SquareMatrix<float, 4>::Simd& matrix ) noexcept
    {
        using Traits = Vector<float, 4>::Traits;
        using Simd = Vector<float, 4>::Simd;
        return Simd( Traits::TransformVector( v.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] ) );
    }


    /// <summary>
    /// Applies a transformation matrix to a 2D coordinate.
    /// </summary>
    /// <param name="p">
    /// The 2D coordinate.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Point2f::Simd Transform( const Point2f::Simd& p, const SquareMatrix<float, 3>::Simd& matrix ) noexcept
    {
        using Traits = SquareMatrix<float, 3>::Traits;
        using Simd = Point2f::Simd;
        return Simd( Traits::TransformPoint( p.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a 3D coordinate.
    /// </summary>
    /// <param name="p">
    /// The 3D coordinate.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Point3f::Simd Transform( const Point3f::Simd& p, const SquareMatrix<float, 4>::Simd& matrix ) noexcept
    {
        using Traits = SquareMatrix<float, 4>::Traits;
        using Simd = Point3f::Simd;
        return Simd( Traits::TransformPoint( p.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], matrix.simd[ 3 ] ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a 3D coordinate.
    /// </summary>
    /// <param name="p">
    /// The 3D coordinate.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Point3f::Simd Transform( const Point3f& p, const SquareMatrix<float, 4>::Simd& matrix ) noexcept
    {
        return Transform( p.ToSimd( ), matrix );
    }

    /// <summary>
    /// Applies a transformation matrix to a 3D coordinate.
    /// </summary>
    /// <param name="p">
    /// The 3D coordinate.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Point3f::Simd Transform( const Point3f::Simd& p, const SquareMatrix<float, 4>& matrix ) noexcept
    {
        return Transform( p, matrix.ToSimd( ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a 3D coordinate.
    /// </summary>
    /// <param name="p">
    /// The 3D coordinate.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Point3f::Simd Transform( const Point3f& p, const SquareMatrix<float, 4>& matrix ) noexcept
    {
        return Transform( p.ToSimd( ), matrix.ToSimd( ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a normal.
    /// </summary>
    /// <param name="p">
    /// The normal.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Normal3f::Simd Transform( const Normal3f::Simd& n, const SquareMatrix<float, 3>::Simd& matrix ) noexcept
    {
        using Traits = SquareMatrix<float, 3>::Traits;
        using Simd = Normal3f::Simd;
        return Simd( Traits::TransformNormal( n.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a normal.
    /// </summary>
    /// <param name="p">
    /// The normal.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Normal3f::Simd Transform( const Normal3f::Simd& n, const SquareMatrix<float, 4>::Simd& matrix ) noexcept
    {
        using Traits = SquareMatrix<float, 3>::Traits;
        using Simd = Normal3f::Simd;
        return Simd( Traits::TransformNormal( n.simd, matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ] ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a normal.
    /// </summary>
    /// <param name="p">
    /// The normal.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Normal3f::Simd Transform( const Normal3f& n, const SquareMatrix<float, 3>::Simd& matrix ) noexcept
    {
        return Transform( n.ToSimd( ), matrix );
    }

    /// <summary>
    /// Applies a transformation matrix to a normal.
    /// </summary>
    /// <param name="p">
    /// The normal.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Normal3f::Simd Transform( const Normal3f& n, const SquareMatrix<float, 4>::Simd& matrix ) noexcept
    {
        return Transform( n.ToSimd( ), matrix );
    }

    /// <summary>
    /// Applies a transformation matrix to a normal.
    /// </summary>
    /// <param name="p">
    /// The normal.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Normal3f::Simd Transform( const Normal3f::Simd& n, const SquareMatrix<float, 3>& matrix ) noexcept
    {
        return Transform( n, matrix.ToSimd( ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a normal.
    /// </summary>
    /// <param name="p">
    /// The normal.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Normal3f::Simd Transform( const Normal3f::Simd& n, const SquareMatrix<float, 4>& matrix ) noexcept
    {
        return Transform( n, matrix.ToSimd( ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a normal.
    /// </summary>
    /// <param name="p">
    /// The normal.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Normal3f::Simd Transform( const Normal3f& n, const SquareMatrix<float, 3>& matrix ) noexcept
    {
        return Transform( n.ToSimd( ), matrix.ToSimd( ) );
    }

    /// <summary>
    /// Applies a transformation matrix to a normal.
    /// </summary>
    /// <param name="p">
    /// The normal.
    /// </param>
    /// <param name="matrix">
    /// The transformation matrix.
    /// </param>
    /// <returns>
    /// The transformation result.
    /// </returns>
    inline Normal3f::Simd Transform( const Normal3f& n, const SquareMatrix<float, 4>& matrix ) noexcept
    {
        return Transform( n.ToSimd( ), matrix.ToSimd( ) );
    }

    /// <summary>
    /// Projects a 3D coordinate from object space into screen space.
    /// </summary>
    /// <param name="v">
    /// The 3D coordinate.
    /// </param>
    /// <param name="viewportX">
    /// The x-coordinate of the upper-left corner of the viewport. Assign 0 
    /// to this parameter, unless you only need to render to a subset of 
    /// the surface, 
    /// </param>
    /// <param name="viewportY">
    /// The y-coordinate of the upper-left corner of the viewport. Assign 0 
    /// to this parameter, unless you only need to render to a subset of 
    /// the surface.
    /// </param>
    /// <param name="viewportWidth">
    /// The width of the clip volume, Assign the width of the render target
    /// surface to this parameter, unless you only need to render to a subset of 
    /// the surface.
    /// </param>
    /// <param name="viewportHeight">
    /// The height of the clip volume, Assign the height of the render target
    /// surface to this parameter, unless you only need to render to a subset of 
    /// the surface.
    /// </param>
    /// <param name="viewportMinZ">
    /// The minimum depth of the clip volume, usually 0.0f. 
    /// </param>
    /// <param name="viewportMaxZ">
    /// The maximum depth of the clip volume, usually 1.0f. 
    /// </param>
    /// <param name="projection">
    /// The projection matrix.
    /// </param>
    /// <param name="viewTransform">
    /// The view transform matrix.
    /// </param>
    /// <param name="WorldTransform">
    /// The world transform matrix.
    /// </param>
    /// <returns>
    /// Returns the coordinate projected into screen space.
    /// </returns>
    template<SimdType S, typename FloatT = S::value_type, typename MatrixT = typename SquareMatrix<FloatT, 4>::Simd>
    S Project( const S& v, FloatT viewportX, FloatT viewportY, FloatT viewportWidth, FloatT viewportHeight, FloatT viewportMinZ, FloatT viewportMaxZ,
        const MatrixT& projection, const MatrixT& viewTransform, const MatrixT& WorldTransform ) noexcept
    {
        using Traits = SIMD::Traits<FloatT, 4>;
        const FloatT halfViewportWidth = viewportWidth * static_cast< FloatT >( 0.5 );
        const FloatT halfViewportHeight = viewportHeight * static_cast< FloatT >( 0.5 );

        auto scale = Traits::Set( viewportMaxZ - viewportMinZ, -halfViewportHeight, halfViewportWidth );
        auto offset = Traits::Set( viewportMinZ, viewportY + halfViewportHeight, viewportX + halfViewportWidth );

        auto transformation = WorldTransform * viewTransform;
        transformation = transformation * projection;

        auto result = Traits::TransformPoint( v.simd, transformation.simd[ 0 ], transformation.simd[ 1 ], transformation.simd[ 2 ], transformation.simd[ 3 ] );

        return S( SIMD::Traits<FloatT, 3>::FMAdd( result, scale, offset ) );
    }


    namespace Internal
    {
        template<FloatingPointType T>
        void RankDecompose( T x, T y, T z, size_t& a, size_t& b, size_t& c )
        {
            if ( x < y )
            {
                if ( y < z )
                {
                    a = 2;
                    b = 1;
                    c = 0;
                }
                else
                {
                    a = 1;

                    if ( x < z )
                    {
                        b = 2;
                        c = 0;
                    }
                    else
                    {
                        b = 0;
                        c = 2;
                    }
                }
            }
            else
            {
                if ( x < z )
                {
                    a = 2;
                    b = 0;
                    c = 1;
                }
                else
                {
                    a = 0;

                    if ( y < z )
                    {
                        b = 2;
                        c = 1;
                    }
                    else
                    {
                        b = 1;
                        c = 2;
                    }
                }
            }
        }
    }

    inline bool Decompose( const SquareMatrix<float, 4>::Simd& matrix, Vector3f::Simd* outScale, Quaternion<float>::Simd* outRotQuat, Vector3f::Simd* outTrans ) noexcept
    {
        constexpr float DecomposeEpsilon = 0.0001f;

        using VTraits = Vector3f::Traits;
        using MTraits = SquareMatrix<float, 4>::Traits;
        using Constants = MTraits::Constants;
        using SIMDType = MTraits::SIMDType;
        using MatrixSimd = SquareMatrix<float, 4>::Simd;


        const Vector3f::Simd canonicalBasis[ 3 ] = { Constants::IdentityR1, Constants::IdentityR2, Constants::IdentityR3 };

        assert( outScale != nullptr );
        assert( outRotQuat != nullptr );
        assert( outTrans != nullptr );

        // Get the translation
        ( *outTrans ).simd = matrix.simd[ 3 ];


        MatrixSimd matTemp( matrix.simd[ 0 ], matrix.simd[ 1 ], matrix.simd[ 2 ], Constants::IdentityR4 );

        Vector3f::Simd* vectorBasis[ 3 ];
        vectorBasis[ 0 ] = reinterpret_cast< Vector3f::Simd* >( &matTemp.simd[ 0 ] );
        vectorBasis[ 1 ] = reinterpret_cast< Vector3f::Simd* >( &matTemp.simd[ 1 ] );
        vectorBasis[ 2 ] = reinterpret_cast< Vector3f::Simd* >( &matTemp.simd[ 2 ] );

        auto& scales = *outScale;
        scales = Vector3f::Simd( ScalarLength( *vectorBasis[ 0 ] ), ScalarLength( *vectorBasis[ 1 ] ), ScalarLength( *vectorBasis[ 2 ] ) );

        size_t a, b, c;

        Internal::RankDecompose( scales[ 0 ], scales[ 1 ], scales[ 2 ], a, b, c );

        if ( scales[ a ] < DecomposeEpsilon )
        {
            *vectorBasis[ a ] = canonicalBasis[ a ];
        }
        *vectorBasis[ a ] = Normalize( *vectorBasis[ a ] );

        if ( scales[ b ] < DecomposeEpsilon )
        {
            Vector3f tmp = Abs( *vectorBasis[ a ] );

            size_t aa, bb, cc;

            Internal::RankDecompose( tmp.x, tmp.y, tmp.z, aa, bb, cc );

            *vectorBasis[ b ] = Vector3f::Simd( VTraits::Cross( ( *vectorBasis[ a ] ).simd, canonicalBasis[ cc ].simd ) );
        }

        *vectorBasis[ b ] = Normalize( *vectorBasis[ b ] );

        if ( scales[ c ] < DecomposeEpsilon )
        {
            *vectorBasis[ c ] = Vector3f::Simd( VTraits::Cross( ( *vectorBasis[ a ] ).simd, ( *vectorBasis[ b ] ).simd ) );
        }
        *vectorBasis[ c ] = Normalize( *vectorBasis[ c ] );


        float fDet = ScalarDeterminant( matTemp );

        // use Kramer's rule to check for handedness of coordinate system
        if ( fDet < 0.0f )
        {
            // switch coordinate system by negating the scale and inverting the basis vector on the x-axis
            switch ( a )
            {
                case 0:
                    scales = scales.WithNegatedX( );
                    break;
                case 1:
                    scales = scales.WithNegatedY( );
                    break;
                case 2:
                    scales = scales.WithNegatedZ( );
                    break;
            }

            *vectorBasis[ a ] = -( *vectorBasis[ a ] );

            fDet = -fDet;
        }

        fDet -= 1.0f;
        fDet *= fDet;

        if ( DecomposeEpsilon < fDet )
        {
            // Non-SRT matrix encountered
            return false;
        }

        // generate the quaternion from the matrix
        *outRotQuat = Quaternion<float>::Simd::FromMatrix( matTemp );
        return true;
    }


    



    namespace Internal
    {
        struct PlaneSimdBase
        {
        };
        struct PlaneBase
        {
        };
    }


    template<typename T>
    concept PlaneSimdType = std::is_base_of_v<Internal::PlaneSimdBase, T>;

    template<typename T>
    concept PlaneType = std::is_base_of_v<Internal::PlaneBase, T>;

    template<typename T>
    concept PlaneOrPlaneSimdType = PlaneType<T> || PlaneSimdType<T>;

    template<PlaneOrPlaneSimdType T, PlaneOrPlaneSimdType ... Other>
    constexpr bool IsCompatiblePlane = ( std::is_same_v<typename T::Traits, typename Other::Traits> && ... );

    template<FloatingPointType T>
    class Plane;


    template<typename PlaneT>
    class PlaneSimd : public Internal::PlaneSimdBase
    {
    public:
        using PlaneType = PlaneT;

        using ValueType = typename PlaneType::ValueType;
        using size_type = size_t;
        using value_type = ValueType;
        using Vector = Math::Vector<ValueType, 3>;

        using Simd = PlaneSimd<PlaneT>;

        static constexpr size_type Size = 4;

        using Traits = typename PlaneType::Traits;
        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;

        SIMDType simd;

        PlaneSimd( ) noexcept
            : simd( Traits::Zero( ) )
        {
        }

        PlaneSimd( const PlaneSimd& other ) noexcept
            : simd( other.simd )
        {
        }

        explicit PlaneSimd( SIMDType other ) noexcept
            : simd( other )
        {
        }

        inline PlaneSimd( const PlaneType& plane ) noexcept;

        template<SimdType T>
        PlaneSimd( const T& normal, value_type distance )
            : simd( Traits::SetW( normal.simd, distance ) )
        {
        }

        template<TupleType T>
        PlaneSimd( const T& normal, value_type distance )
            : simd( Traits::SetW( Traits::Load( normal.values ), distance ) )
        {
        }


        template<SimdType S, SimdType T, SimdType U>
            requires IsCompatible<S, T, U> && ( S::Size > 2 ) && std::is_same_v<value_type, typename S::value_type>
        PlaneSimd( const S& point1, const T& point2, const U& point3 ) noexcept
        {
            using Constants = typename Traits::Constants;
            Vector v21 = point1 - point2;
            Vector v31 = point1 - point3;

            auto n = Cross( v21, v31 );
            n = Normalize( n );

            auto distance = Traits::Negate( Traits::Dot<0x7f>( n.simd, point1.simd ) );

            simd = Traits::Select( n.simd, distance, Constants::Select1112 );
        }



        PlaneSimd& operator = ( const PlaneSimd& other ) noexcept
        {
            simd = other.simd;
            return *this;
        }

        PlaneSimd& operator = ( SIMDType other ) noexcept
        {
            simd = other;
            return *this;
        }

        PlaneSimd& operator = ( const PlaneType& quaternion ) noexcept;

        bool operator == ( const PlaneSimd& other ) const noexcept
        {
            return Traits::AllEqual( simd, other.simd );
        }

        bool operator != ( const PlaneSimd& other ) const noexcept
        {
            return Traits::AllEqual( simd, other.simd ) == false;
        }

        bool operator == ( const PlaneType& other ) const noexcept;
        bool operator != ( const PlaneType& other ) const noexcept;


    };


    template<FloatingPointType T>
    class Plane : public Internal::PlaneBase
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 4;

        using Traits = SIMD::Traits<ValueType, Size>;
        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Capacity = Size;
        using ArrayType = typename Traits::ArrayType;

        using reference = typename ArrayType::reference;
        using const_reference = typename ArrayType::const_reference;
        using pointer = typename ArrayType::pointer;
        using const_pointer = typename ArrayType::const_pointer;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
        using reverse_iterator = typename ArrayType::reverse_iterator;
        using const_reverse_iterator = typename ArrayType::const_reverse_iterator;

        using Simd = PlaneSimd<Plane>;

        using Vector = Math::Vector<ValueType, 3>;

        // smallest such that 1.0+NormalizeEpsilon != 1.0
        static constexpr float NormalizeEpsilon = 1.192092896e-07f;

        union
        {
            ArrayType values;
            struct
            {
                /// <summary>
                /// The normal vector of the plane.
                /// </summary>
                Vector Normal;

                /// <summary>
                /// The distance of the plane along its normal from the origin.
                /// </summary>
                ValueType Distance;
            };
        };

        constexpr Plane( ) noexcept
            : values{}
        {
        }
        constexpr Plane( ValueType x, ValueType y, ValueType z, ValueType distance ) noexcept
            : values( { x, y, z, distance } )
        {
        }

        constexpr Plane( const ArrayType& plane ) noexcept
            : values( plane )
        {
        }

        template<TupleType T>
            requires IsCompatible<T, Vector>
        constexpr Plane( const T& normal, ValueType distance ) noexcept
            : Normal( normal ), Distance( distance )
        {
        }

        template<SimdType T>
            requires IsCompatible<T, Vector>
        constexpr Plane( const T& normal, ValueType distance ) noexcept
            : Normal( normal ), Distance( distance )
        {
        }

        Plane( const Simd& plane ) noexcept
            : values( Traits::ToArray( plane.simd ) )
        {
        }

        Plane& operator = ( const Simd& plane ) noexcept
        {
            values = Traits::ToArray( plane.simd );
            return *this;
        }

        Plane& operator = ( const Plane& other ) noexcept
        {
            values = other.values;
            return *this;
        }


        Simd ToSimd( ) const noexcept
        {
            return Simd( Traits::Load( values ) );
        }

        operator Simd( ) const noexcept
        {
            return ToSimd( );
        }

        bool operator == ( const Simd& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values ), other.simd );
        }

        bool operator != ( const Simd& other ) const noexcept
        {
            return Traits::AnyNotEqual( Traits::Load( values ), other.simd );
        }

        bool operator == ( const Plane& other ) const noexcept
        {
            return values == other.values;
        }
        bool operator != ( const Plane& other ) const noexcept
        {
            return values != other.values;
        }

        Simd operator - ( ) const noexcept
        {
            return Simd( Traits::Negate( Traits::Load( values ) ) );
        }

        const_reference operator[]( size_t index ) const noexcept
        {
            return values[ index ];
        }

        reference operator[]( size_t index ) noexcept
        {
            return values[ index ];
        }

        const_pointer data( ) const noexcept
        {
            return values.data( );
        }
        pointer data( ) noexcept
        {
            return values.data( );
        }

        constexpr size_t size( ) const noexcept
        {
            return Size;
        }

        const_reference front( ) const noexcept
        {
            return values.front( );
        }
        reference front( ) noexcept
        {
            return values.front( );
        }

        const_reference back( ) const noexcept
        {
            return values.back( );
        }
        reference back( ) noexcept
        {
            return values.back( );
        }

        const_iterator begin( ) const noexcept
        {
            return values.begin( );
        }
        const_iterator cbegin( ) const noexcept
        {
            return values.cbegin( );
        }
        iterator begin( ) noexcept
        {
            return values.begin( );
        }
        const_iterator end( ) const noexcept
        {
            return values.end( );
        }
        const_iterator cend( ) const noexcept
        {
            return values.cend( );
        }
        iterator end( ) noexcept
        {
            return values.end( );
        }
        const_reverse_iterator rbegin( ) const noexcept
        {
            return values.rbegin( );
        }
        reverse_iterator rbegin( ) noexcept
        {
            return values.rbegin( );
        }
        const_reverse_iterator rend( ) const noexcept
        {
            return values.rend( );
        }
        reverse_iterator rend( ) noexcept
        {
            return values.rend( );
        }
    };

    template<typename PlaneT>
    inline PlaneSimd<PlaneT>::PlaneSimd( const PlaneT& plane ) noexcept
        : simd( Traits::Load( plane.values ) )
    {
    }

    template<typename PlaneT>
    inline PlaneSimd<PlaneT>& PlaneSimd<PlaneT>::operator = ( const PlaneT& plane ) noexcept
    {
        simd = Traits::Load( plane.values );
        return *this;
    }

    template<typename PlaneT>
    inline bool PlaneSimd<PlaneT>::operator == ( const PlaneT& other ) const noexcept
    {
        return Traits::AllEqual( simd, Traits::Load( other.values ) );
    }
    template<typename PlaneT>
    inline bool PlaneSimd<PlaneT>::operator != ( const PlaneT& other ) const noexcept
    {
        return Traits::AllEqual( simd, Traits::Load( other.values ) ) == false;
    }

    template<PlaneSimdType T>
    inline T Normalize( const T& plane ) noexcept
    {
        using Traits = typename T::Traits;
        using Constants = typename Traits::Constants;

        auto lengthSquared = Traits::Dot<0x7f>( plane.simd, plane.simd );
        auto length = Traits::Sqrt( lengthSquared );
        auto notInfinity = Traits::NotEqual( lengthSquared, Constants::Infinity );
        auto result = Traits::Div( plane.simd, length );
        return T( Traits::And( result, notInfinity ) );
    }

    template<PlaneType T>
    inline typename T::Simd Normalize( const T& plane ) noexcept
    {
        return Normalize( plane.ToSimd( ) );
    }

    template<PlaneSimdType T>
    inline T FastNormalize( const T& plane ) noexcept
    {
        using Traits = typename T::Traits;
        using Constants = typename Traits::Constants;

        auto lengthSquared = Traits::Dot<0x7f>( plane.simd, plane.simd );
        auto scale = Traits::ReciprocalSqrt( lengthSquared );
        return T( Traits::Mul( scale, plane.simd ) );
    }

    template<PlaneType T>
    inline typename T::Simd FastNormalize( const T& plane ) noexcept
    {
        return FastNormalize( plane.ToSimd( ) );
    }


    template<PlaneSimdType P, VectorSimdType V>
        requires std::is_same_v<typename P::value_type, typename V::value_type> && ( V::Size > 2 )
    inline V Dot( const P& plane, const V& v )
    {
        using Traits = typename P::Traits;
        return V( Traits::Dot( plane.simd, v.simd ) );
    }

    template<PlaneSimdType P, NormalSimdType N>
        requires std::is_same_v<typename P::value_type, typename N::value_type> && ( N::Size > 2 )
    inline N Dot( const P& plane, const N& normal )
    {
        using Traits = typename N::Traits;
        return N( Traits::Dot<0x7f>( plane.simd, normal.simd ) );
    }

    template<PlaneSimdType P, PointSimdType PT>
    inline PT Dot( const P& plane, const PT& point )
    {
        using Traits = typename P::Traits;
        return PT( Traits::Dot( plane.simd, Traits::SetW( point.simd, static_cast< typename Traits::Type >( 1 ) ) ) );
    }

    namespace Internal
    {
        template<typename T>
        concept VectorNormalOrPointSimdType = VectorSimdType<T> || NormalSimdType<T> || PointSimdType<T>;

        template<typename T>
        concept VectorNormalOrPointType = VectorType<T> || NormalType<T> || PointType<T>;
    }

    template<Internal::VectorNormalOrPointSimdType T, PlaneSimdType P>
    inline T Dot( const T& v, const P& plane )
    {
        return Dot( plane, v );
    }

    template<Internal::VectorNormalOrPointType T, PlaneSimdType P>
    inline T Dot( const T& v, const P& plane )
    {
        return Dot( plane, v.ToSimd( ) );
    }

    template<Internal::VectorNormalOrPointType T, PlaneType P>
    inline T Dot( const T& v, const P& plane )
    {
        return Dot( plane.ToSimd( ), v.ToSimd( ) );
    }

    template<PlaneType P, Internal::VectorNormalOrPointType T>
    inline T Dot( const P& plane, const T& v )
    {
        return Dot( plane.ToSimd( ), v.ToSimd( ) );
    }

    template<PlaneType P, PointSimdType PT>
    inline PT Intersect( const P& plane, const PT& linePoint1, const PT& linePoint2 ) noexcept
    {
        using Traits = typename P::Traits;

        using Constants = typename Traits::Constants;
        using FloatT = typename Traits::Type;
        using Vector = typename Math::Vector<FloatT, 3>::Simd;
        Vector v1 = Traits::Dot<0x7f>( plane.simd, linePoint1.simd );
        Vector v2 = Traits::Dot<0x7f>( plane.simd, linePoint2.simd );
        auto d = v1 - v2;

        Vector vt = Dot( plane, linePoint1 );
        vt = vt / d;

        Vector point = linePoint2 - linePoint1;
        point.simd = Traits::FMAdd( point.simd, vt.simd, linePoint1.simd );

        const auto zero = Traits::Zero( );
        const auto nearEqual = Traits::NearEqual( d.simd, zero, Constants::Epsilon );

        return PT( Traits::Select( point.simd, Constants::QNaN, nearEqual ) );
    }

    inline std::pair<Point3f::Simd, Point3f::Simd> Intersect( const Plane<float>::Simd& plane1, const Plane<float>::Simd& plane2 ) noexcept
    {
        using Traits = typename Plane<float>::Traits;

        using Constants = typename Traits::Constants;
        using FloatT = typename Traits::Type;
        using Vector = typename Math::Vector<FloatT, 3>::Simd;

        Vector v1 = Vector::Traits::Cross( plane2.simd, plane1.simd );

        auto lengthSquared = LengthSquared( v1 );

        Vector v2 = Vector::Traits::Cross( plane2.simd, v1.simd );

        auto plane1W = Traits::At<3>( plane1.simd );
        auto point = Traits::Mul( v2.simd, plane1W );

        Vector v3 = Vector::Traits::Cross( v1.simd, plane1.simd );

        auto plane2W = Traits::At<3>( plane2.simd );
        point = Traits::FMAdd( v3.simd, plane2W, point );

        auto linePoint1 = Traits::Div( point, lengthSquared.simd );

        auto linePoint2 = Traits::Add( linePoint1, v1.simd );

        auto control = Traits::LessOrEqual( lengthSquared.simd, Constants::Epsilon );
        linePoint1 = Traits::Select( linePoint1, Constants::QNaN, control );
        linePoint2 = Traits::Select( linePoint2, Constants::QNaN, control );
        return { linePoint1, linePoint2 };
    }



    inline Plane<float>::Simd Transform( const Plane<float>::Simd& plane, const SquareMatrix<float, 4>::Simd& transformationMatrix ) noexcept
    {
        using Traits = SquareMatrix<float, 4>::Traits;

        auto row = Traits::At<3>( plane.simd );
        auto result = Traits::Mul( row, transformationMatrix.simd[ 3 ] );
        row = Traits::At<2>( plane.simd );
        result = Traits::FMAdd( row, transformationMatrix.simd[ 2 ], result );
        row = Traits::At<1>( plane.simd );
        result = Traits::FMAdd( row, transformationMatrix.simd[ 1 ], result );
        row = Traits::At<0>( plane.simd );
        return Plane<float>::Simd( Traits::FMAdd( row, transformationMatrix.simd[ 0 ], result ) );
    }




    //using Traits = SIMD::Traits<float,4>;


}

namespace std
{
    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<float, 2>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<float, 2>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x, value.y );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x, value.y );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<float, 2>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<float, 2>::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x( ), value.y( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x( ), value.y( ) );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<int, 2>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<int, 2>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x, value.y );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x, value.y );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<int, 2>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<int, 2>::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x( ), value.y( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x( ), value.y( ) );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<float, 3>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<float, 3>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x, value.y, value.z );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x, value.y, value.z );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<float, 3>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<float, 3>::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<int, 3>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<int, 3>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x, value.y, value.z );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x, value.y, value.z );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<int, 3>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<int, 3>::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<float, 4>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<float, 4>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}; {}]", value.x, value.y, value.z, value.w );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}; {}]", value.x, value.y, value.z, value.w );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<float, 4>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<float, 4>::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}; {}]", value.x( ), value.y( ), value.z( ), value.w( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}; {}]", value.x( ), value.y( ), value.z( ), value.w( ) );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<int, 4>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<int, 4>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}; {}]", value.x, value.y, value.z, value.w );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}; {}]", value.x, value.y, value.z, value.w );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Vector<int, 4>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Vector<int, 4>::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}; {}]", value.x( ), value.y( ), value.z( ), value.w( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}; {}]", value.x( ), value.y( ), value.z( ), value.w( ) );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Math::Point2f, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Point2f& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x, value.y );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x, value.y );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Point2f::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Point2f::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x( ), value.y( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x( ), value.y( ) );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Math::Point2i, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Point2i& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x, value.y );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x, value.y );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Point2i::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Point2i::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x( ), value.y( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x( ), value.y( ) );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Math::Point3f, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Point3f& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x, value.y, value.z );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x, value.y, value.z );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Point3f::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Point3f::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Math::Point3i, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Point3i& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x, value.y, value.z );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x, value.y, value.z );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Point3i::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Point3i::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
        }
    };



    template<typename CharT>
    struct formatter<Harlinn::Math::Normal3f, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Normal3f& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x, value.y, value.z );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x, value.y, value.z );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::Normal3f::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Normal3f::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}]", value.x( ), value.y( ), value.z( ) );
            }
        }
    };



    template<typename CharT>
    struct formatter<Harlinn::Math::Quaternion<float>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::Quaternion<float>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}; {}]", value.v.x, value.v.y, value.v.z, value.w );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}; {}]", value.v.x, value.v.y, value.v.z, value.w );
            }
        }
    };

    template<typename CharT>
    struct formatter<typename Harlinn::Math::Quaternion<float>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const typename Harlinn::Math::Quaternion<float>::Simd& q, FormatContext& ctx ) const
        {
            Harlinn::Math::Quaternion<float> value( q );
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}; {}; {}]", value.v.x, value.v.y, value.v.z, value.w );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}; {}; {}]", value.v.x, value.v.y, value.v.z, value.w );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::SquareMatrix<float, 3>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::SquareMatrix<float, 3>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[[{}; {}; {}][{}; {}; {}][{}; {}; {}]]",
                    value[ 0 ][ 0 ], value[ 0 ][ 1 ], value[ 0 ][ 2 ],
                    value[ 1 ][ 0 ], value[ 1 ][ 1 ], value[ 1 ][ 2 ],
                    value[ 2 ][ 0 ], value[ 2 ][ 1 ], value[ 2 ][ 2 ] );
            }
            else
            {
                return std::format_to( ctx.out( ), "[[{}; {}; {}][{}; {}; {}][{}; {}; {}]]",
                    value[ 0 ][ 0 ], value[ 0 ][ 1 ], value[ 0 ][ 2 ],
                    value[ 1 ][ 0 ], value[ 1 ][ 1 ], value[ 1 ][ 2 ],
                    value[ 2 ][ 0 ], value[ 2 ][ 1 ], value[ 2 ][ 2 ] );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::SquareMatrix<float, 3>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::SquareMatrix<float, 3>::Simd& value, FormatContext& ctx ) const
        {
            Harlinn::Math::SquareMatrix<float, 3> m( value );
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"{}", m );
            }
            else
            {
                return std::format_to( ctx.out( ), "{}", m );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::SquareMatrix<float, 4>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::SquareMatrix<float, 4>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[[{}; {}; {}; {}][{}; {}; {}; {}][{}; {}; {}; {}][{}; {}; {}; {}]]",
                    value[ 0 ][ 0 ], value[ 0 ][ 1 ], value[ 0 ][ 2 ], value[ 0 ][ 3 ],
                    value[ 1 ][ 0 ], value[ 1 ][ 1 ], value[ 1 ][ 2 ], value[ 1 ][ 3 ],
                    value[ 2 ][ 0 ], value[ 2 ][ 1 ], value[ 2 ][ 2 ], value[ 2 ][ 3 ],
                    value[ 3 ][ 0 ], value[ 3 ][ 1 ], value[ 3 ][ 2 ], value[ 3 ][ 3 ] );
            }
            else
            {
                return std::format_to( ctx.out( ), "[[{}; {}; {}; {}][{}; {}; {}; {}][{}; {}; {}; {}][{}; {}; {}; {}]]",
                    value[ 0 ][ 0 ], value[ 0 ][ 1 ], value[ 0 ][ 2 ], value[ 0 ][ 3 ],
                    value[ 1 ][ 0 ], value[ 1 ][ 1 ], value[ 1 ][ 2 ], value[ 1 ][ 3 ],
                    value[ 2 ][ 0 ], value[ 2 ][ 1 ], value[ 2 ][ 2 ], value[ 2 ][ 3 ],
                    value[ 3 ][ 0 ], value[ 3 ][ 1 ], value[ 3 ][ 2 ], value[ 3 ][ 3 ] );
            }
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Math::SquareMatrix<float, 4>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Math::SquareMatrix<float, 4>::Simd& value, FormatContext& ctx ) const
        {
            Harlinn::Math::SquareMatrix<float, 4> m( value );
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"{}", m );
            }
            else
            {
                return std::format_to( ctx.out( ), "{}", m );
            }
        }
    };

}

namespace Harlinn::Math
{
    template<typename CharT, size_t N>
    inline auto operator<<( std::basic_ostream<CharT>& os, const SquareMatrix<float, N>& value )
    {
        if constexpr ( std::is_same_v<CharT, wchar_t> )
        {
            os << std::format( L"{}", value );
        }
        else
        {
            os << std::format( "{}", value );
        }
        return os;
    }
}


#endif
