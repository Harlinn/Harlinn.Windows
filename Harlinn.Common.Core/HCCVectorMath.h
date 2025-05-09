#pragma once
#ifndef __HCCMATRIX_H__
#define __HCCMATRIX_H__
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

#include <HCCMath.h>
#include <HCCString.h>

namespace Harlinn::Common::Core::Math
{
    template<typename MatrixT, typename size_t N>
    struct SquareMatrixSimd;


    template<typename T, size_t N>
    class SquareMatrix;




    template<typename T>
    constexpr bool IsLoadedType = T::Loaded;

    template<typename T>
    constexpr bool IsUnloadedType = T::Unloaded;

    namespace Internal
    {
        struct VectorBase
        { };

        struct ScalarBase
        { };
    }

    template<typename T>
    concept VectorType = std::is_base_of_v<Internal::VectorBase, T>;

    template<typename T>
    concept VectorSimdType = std::is_base_of_v<Internal::VectorBase, typename T::TupleType>;

    template<typename T>
    concept ScalarType = std::is_base_of_v<Internal::ScalarBase, T>;

    template<typename T>
    concept ScalarSimdType = std::is_base_of_v<Internal::ScalarBase, typename T::TupleType>;



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
    template<typename ValueT, size_t N>
    class alignas( Core::SIMD::Traits<ValueT, N>::AlignAs ) Vector : public Internal::VectorBase
    {
    public:
        using Indices = std::make_index_sequence<N>;
        static constexpr size_t Size = N;
        using ValueType = std::remove_cvref_t<ValueT>;
        using UIntType = MakeUnsigned<ValueType>;
        using Traits = Core::SIMD::Traits<ValueType, N>;
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




        [[nodiscard]] WideString ToString( ) const
        {
            if ( Size )
            {
                WideString result( L"[" );
                for ( size_t i = 0; i < Size; ++i )
                {
                    if ( ( i + 1 ) != Size )
                    {
                        result += Format( L"{},", values_[i] );
                    }
                    else
                    {
                        result += Format( L"{}", values_[i] );
                    }
                }
                result += L"]";
                return result;
            }
            else
            {
                return WideString(L"[]");
            }
        }

    };

    namespace Internal
    {
        struct TupleBase
        { };

        struct TupleSimdBase
        { };

        template<typename T>
        concept SimdType = std::is_base_of_v<TupleSimdBase, T>;

        template<typename T>
        concept TupleType = std::is_base_of_v<TupleBase, T>;

        template<typename T1, typename T2>
        constexpr bool IsCompatible =
            std::is_same_v<typename T1::Traits, typename T2::Traits>;

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
    /// <para>
    /// Holds the SIMD value for a Tuple2, Tuple3 or Tuple4.
    /// </para>
    /// <para>
    /// Mathematical operations for a particular Tuple2, Tuple3 
    /// or Tuple4 derived type should generally be performed as 
    /// a sequence of operations on this type, not the Tuple2, Tuple3 
    /// or Tuple4 derived type, as this type represents the loaded
    /// state of the data. 
    /// </para>
    /// </summary>
    /// <typeparam name="TraitsT">
    /// The SIMD::Traits specialization that will be
    /// used to select the SIMD intrinsics that
    /// operates on the simd value held by this TupleSimd.
    /// </typeparam>
    /// <typeparam name="TupleT">
    /// A Tuple2, Tuple3 or Tuple4 derived type.
    /// </typeparam>
    /// <remarks>
    /// This implementation passes TupleSimd objects by reference,
    /// since passing the TupleSimd objects by value degraded
    /// the performance of pbrto by approximately 10 %.
    /// </remarks>

    template<typename TraitsT, typename TupleT>
    class alignas( TraitsT::AlignAs ) TupleSimd : public Internal::TupleSimdBase
    {
    public:
        using Traits = TraitsT;
        using TupleType = TupleT;
        using DerivedType = typename TupleType::Simd;
        using value_type = typename Traits::Type;
        using size_type = size_t;

        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Size = TupleType::Size;
        static constexpr bool Loaded = true;
        static constexpr bool Unloaded = false;
        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;

        SIMDType simd;

        TupleSimd( ) noexcept
            : simd( Traits::Zero( ) )
        {
        }

        TupleSimd( SIMDType other ) noexcept
            : simd( other )
        {
        }

        template<Internal::SimdType S>
            requires std::is_same_v<Traits, typename S::Traits> ||
                ( std::is_same_v<typename Traits::Type, typename S::Traits::Type> && ( Size > S::Size ) )
        TupleSimd( const S& other ) noexcept
            : simd( other.simd )
        {
        }

        template<Internal::SimdType S>
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



        TupleSimd( const TupleType& other ) noexcept
            : simd( Traits::Load( other.values.data( ) ) )
        {
        }

        TupleSimd( value_type x, value_type y ) noexcept requires ( Size == 2 )
            : simd( Traits::Set(y, x) )
        {
        }

        TupleSimd( value_type x, value_type y, value_type z ) noexcept requires ( Size == 3 )
            : simd( Traits::Set( z, y, x ) )
        {
        }

        TupleSimd( value_type x, value_type y, value_type z, value_type w ) noexcept requires ( Size == 4 )
            : simd( Traits::Set( w, z, y, x ) )
        {
        }

        explicit TupleSimd( value_type x ) noexcept requires ( Size == 2 )
            : simd( Traits::Set( x, x ) )
        { }
        explicit TupleSimd( value_type x ) noexcept requires ( Size == 3 )
            : simd( Traits::Set( x, x, x ) )
        {
        }
        explicit TupleSimd( value_type x ) noexcept requires ( Size == 4 )
            : simd( Traits::Set( x, x, x, x ) )
        { }
        explicit TupleSimd( value_type x ) noexcept requires ( Size == 8 )
            : simd( Traits::Set( x, x, x, x, x, x, x, x ) )
        {
        }

        TupleType Values( ) const noexcept
        {
            return TupleType( *this );
        }


        TupleSimd operator - ( ) const noexcept
        {
            return Traits::Negate( simd );
        }

        bool operator == ( const TupleSimd& other ) const noexcept
        {
            return Traits::AllEqual( simd, other.simd );
        }

        bool operator != ( const TupleSimd& other ) const noexcept
        {
            return Traits::AllEqual( simd, other.simd ) == false;
        }

        bool operator == ( const value_type& value ) const noexcept
        {
            return Traits::AllEqual( simd, Traits::Fill( value ) );
        }

        bool operator != ( const value_type& value ) const noexcept
        {
            return Traits::AllEqual( simd, Traits::Fill( value ) ) == false;
        }

        bool AnyEqual( const value_type& value ) const noexcept
        {
            return Traits::AnyEqual( simd, Traits::Fill( value ) );
        }
        bool AnyNotEqual( const value_type& value ) const noexcept
        {
            return Traits::AnyNotEqual( simd, Traits::Fill( value ) );
        }

        explicit operator bool( ) const noexcept
        {
            return Traits::AnyNotEqual( simd, Traits::Zero( ) );
        }


        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        bool operator == ( const T& other ) const noexcept
        {
            return Traits::AllEqual( simd, Traits::Load( other.values.data() ) );
        }

        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        bool operator != ( const T& other ) const noexcept
        {
            return Traits::AllEqual( simd, Traits::Load( other.values.data() ) ) == false;
        }

        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        TupleSimd& operator += ( const T& other ) noexcept
        {
            simd = Traits::Add( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        TupleSimd& operator += ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }
        TupleSimd& operator += ( const value_type other ) noexcept
        {
            simd = Traits::Add( simd, Traits::Fill<Size>( other ) );
            return *this;
        }

        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        TupleSimd& operator -= ( const T& other ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        TupleSimd& operator -= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        TupleSimd& operator -= ( const value_type other ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Fill<Size>( other ) );
            return *this;
        }


        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        TupleSimd& operator *= ( const T& other ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        TupleSimd& operator *= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        TupleSimd& operator *= ( const value_type other ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Fill<Size>( other ) );
            return *this;
        }

        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        TupleSimd& operator /= ( const T& other ) noexcept
        {
            simd = Traits::Div( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        TupleSimd& operator /= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }

        TupleSimd& operator /= ( const value_type v ) noexcept
        {
            simd = Traits::Div( simd, Traits::FillDivisor<Size>( v ) );
            return *this;
        }

        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        void Assign( const T& other ) noexcept
        {
            simd = Traits::Load( other.values.data( ) );
        }

        void Assign( SIMDType other ) noexcept
        {
            simd = other;
        }

        bool HasNaN( ) const noexcept
        {
            return Traits::HasNaN( simd );
        }

        TupleSimd X( ) const
        {
            return Traits::Trim( Traits::At<0>( simd ) );
        }
        value_type x( ) const
        {
            return Traits::Extract<0>( simd );
        }
        void SetX( SIMDType src )
        {
            simd = Traits::Permute<4, 1, 2, 3>( simd, src );
        }
        void SetX( const TupleSimd& src )
        {
            SetX( src.simd );
        }
        void SetX( const value_type value )
        {
            SetX( Traits::Fill<Size>( value ) );
        }
        void AbsX( )
        {
            simd = Traits::AbsX( simd );
        }
        TupleSimd WithAbsX( ) const
        {
            return Traits::AbsX( simd );
        }
        void NegateX( )
        {
            simd = Traits::NegateX( simd );
        }
        TupleSimd WithNegatedX( ) const
        {
            return Traits::NegateX( simd );
        }


        TupleSimd Y( ) const
        {
            return Traits::Trim( Traits::At<1>( simd ) );
        }
        value_type y( ) const
        {
            return Traits::Extract<1>( simd );
        }
        void SetY( SIMDType src )
        {
            simd = Traits::Permute<0, 5, 2, 3>( simd, src );
        }
        void SetY( const TupleSimd& src )
        {
            SetY( src.simd );
        }
        void SetY( const value_type value )
        {
            SetY( Traits::Fill<Size>( value ) );
        }
        void AbsY( )
        {
            simd = Traits::AbsY( simd );
        }
        TupleSimd WithAbsY( ) const noexcept
        {
            return Traits::AbsY( simd );
        }
        void NegateY( )
        {
            simd = Traits::NegateY( simd );
        }
        TupleSimd WithNegatedY( ) const
        {
            return Traits::NegateY( simd );
        }

        void AbsXY( )
        {
            simd = Traits::AbsXY( simd );
        }
        TupleSimd WithAbsXY( ) const noexcept
        {
            return Traits::AbsXY( simd );
        }
        void NegateXY( )
        {
            simd = Traits::NegateXY( simd );
        }
        TupleSimd WithNegatedXY( ) const
        {
            return Traits::NegateXY( simd );
        }

        TupleSimd Z( ) const requires (Size > 2)
        {
            return Traits::Trim( Traits::At<2>( simd ) );
        }
        value_type z( ) const requires ( Size > 2 )
        {
            return Traits::Extract<2>( simd );
        }
        void SetZ( SIMDType src ) requires ( Size > 2 )
        {
            simd = Traits::Permute<0, 1, 6, 3>( simd, src );
        }
        void SetZ( const TupleSimd& src ) requires ( Size > 2 )
        {
            SetZ( src.simd );
        }
        void SetZ( const value_type value ) requires ( Size > 2 )
        {
            SetZ( Traits::Fill<Size>( value ) );
        }
        void AbsZ( ) requires ( Size > 2 )
        {
            simd = Traits::AbsZ( simd );
        }
        TupleSimd WithAbsZ( ) const noexcept requires ( Size > 2 )
        {
            return Traits::AbsZ( simd );
        }
        void NegateZ( ) requires ( Size > 2 )
        {
            simd = Traits::NegateZ( simd );
        }
        TupleSimd WithNegatedZ( ) const requires ( Size > 2 )
        {
            return Traits::NegateZ( simd );
        }

        void SetXYZ( SIMDType src ) requires ( Size > 2 )
        {
            simd = Traits::Permute<0, 1, 2, 7>( src, simd );
        }
        void SetXYZ( const TupleSimd& src )
        {
            SetXYZ( src.simd );
        }
        TupleSimd W( ) const requires ( Size > 3 )
        {
            return Traits::Trim( Traits::At<3>( simd ) );
        }
        value_type w( ) const requires ( Size > 3 )
        {
            return Traits::Extract<3>( simd );
        }

        void SetW( SIMDType src ) requires ( Size > 3 )
        {
            simd = Traits::Permute<0, 1, 2, 7>( simd, src );
        }
        void SetW( const TupleSimd& src ) requires ( Size > 3 )
        {
            SetW( src.simd );
        }
        void SetW( const value_type value ) requires ( Size > 3 )
        {
            SetW( Traits::Fill<Size>( value ) );
        }

        void AbsW( ) requires ( Size > 3 )
        {
            simd = Traits::AbsW( simd );
        }
        TupleSimd WithAbsW( ) const noexcept requires ( Size > 3 )
        {
            return Traits::AbsW( simd );
        }
        void NegateW( ) requires ( Size > 3 )
        {
            simd = Traits::NegateW( simd );
        }
        TupleSimd WithNegatedW( ) const requires ( Size > 3 )
        {
            return Traits::NegateW( simd );
        }

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
            return operator[]( idx % Size );
        }



        WideString ToString( ) const
        {
            if constexpr ( Size == 2 )
            {
                return Format( L"[{}, {}]", Traits::First( X().simd ), Traits::First( Y( ).simd ) );
            }
            else if constexpr ( Size == 3 )
            {
                return Format( L"[{}, {}, {}]", Traits::First( X( ).simd ), Traits::First( Y( ).simd ), Traits::First( Z( ).simd ) );
            }
            else
            {
                return Format( L"[{}, {}, {}, {}]", Traits::First( X( ).simd ), Traits::First( Y( ).simd ), Traits::First( Z( ).simd ), Traits::First( W( ).simd ) );
            }
        }
        std::string ToStdString( ) const
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
            stream << t.ToStdString( );
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
    template<class DerivedT, typename T>
    class Tuple2 : public Internal::TupleBase
    {
    public:
        using DerivedType = DerivedT;
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 2;
        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;

        using Traits = SIMD::Traits<value_type, Size>;
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


        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using Simd = TupleSimd<Traits,DerivedType>;

        union
        {
            ArrayType values;
            struct
            {
                value_type x, y;
            };
        };

        Tuple2( ) noexcept
            : x( static_cast< value_type >(0) ), y( static_cast< value_type >( 0 ) )
        {
        }

        explicit Tuple2( value_type v ) noexcept
            : x( v ), y( v )
        { }

        Tuple2( value_type xv, value_type yv) noexcept
            : x( xv ), y(yv)
        { }

        Tuple2( const ArrayType a ) noexcept
            : values(a)
        { }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple2( const U& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        { }

        template<Internal::TupleType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple2( const U& other ) noexcept
            : values( other.values )
        { }

        template<Internal::TupleType U>
            requires (std::is_same_v<Traits, typename U::Traits> == false )
        explicit Tuple2( const U& other ) noexcept
            : x( static_cast< value_type >( other.x ) ), y( static_cast< value_type >( other.y ) )
        { }

        template<Internal::SimdType U>
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

        template<Internal::TupleType U>
            requires ( U::Size == Size )
        constexpr bool operator == ( const U& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y );
        }
        template<Internal::TupleType U>
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


        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator == ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values.data( ) ), other.simd );
        }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator != ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values.data( ) ), other.simd ) == false;
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values.data( ) ) );
        }

        DerivedType& operator += ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Add( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        
        WideString ToString( ) const
        {
            return Format( L"[{}, {}]", x, y );
        }


    };

    template<typename DerivedT, typename T>
    class Tuple3 : public Internal::TupleBase
    {
    public:
        using DerivedType = DerivedT;
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 3;
        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;

        using Traits = SIMD::Traits<value_type, Size>;
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

        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using Simd = TupleSimd<Traits, DerivedType>;

        union
        {
            ArrayType values;
            struct
            {
                value_type x, y, z;
            };
        };

        Tuple3( ) noexcept
            : x{}, y{}, z{}
        { }

        explicit Tuple3( value_type v ) noexcept
            : x( v ), y( v ), z( v )
        {
        }

        Tuple3( value_type xv, value_type yv, value_type zv ) noexcept
            : x( xv ), y( yv ), z( zv )
        { }

        Tuple3( const ArrayType a ) noexcept
            : values( a )
        { }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple3( const U& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        { }

        template<Internal::TupleType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple3( const U& other ) noexcept
            : values( other.values )
        { }

        template<Internal::TupleType U>
            requires ( std::is_same_v<Traits, typename U::Traits> == false )
        explicit Tuple3( const U& other ) noexcept
            : x( static_cast< value_type >( other.x ) ), y( static_cast< value_type >( other.y ) ), z( static_cast< value_type >( other.z ) )
        { }

        template<Internal::SimdType U>
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

        template<Internal::TupleType U>
            requires (U::Size == Size)
        constexpr bool operator == ( const U& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z );
        }
        template<Internal::TupleType U>
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

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator == ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values.data( ) ), other.simd );
        }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator != ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values.data( ) ), other.simd ) == false;
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values.data( ) ) );
        }

        DerivedType& operator += ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Add( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >(*this );
        }

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        WideString ToString( ) const
        {
            return Format( L"[{}, {}, {}]", x, y, z );
        }
    };

    template<typename DerivedT, typename T>
    class Tuple4 : public Internal::TupleBase
    {
    public:
        using DerivedType = DerivedT;
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 4;
        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;

        using Traits = SIMD::Traits<value_type, Size>;
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

        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using Simd = TupleSimd<Traits, DerivedType>;

        union
        {
            ArrayType values;
            struct
            {
                value_type x, y, z, w;
            };
        };

        Tuple4( ) noexcept
            : x( static_cast<value_type>( 0 ) ), y( static_cast< value_type >( 0 ) ), z( static_cast< value_type >( 0 ) ), w( static_cast< value_type >( 0 ) )
        { }

        Tuple4( value_type value ) noexcept
            : x( value ), y( value ), z( value ), w( value )
        { }

        Tuple4( value_type xv, value_type yv, value_type zv, value_type wv ) noexcept
            : x( xv ), y( yv ), z( zv ), w( wv )
        { }

        Tuple4( const ArrayType& a ) noexcept
            : values( a )
        { }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple4( const U& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        {
        }

        template<Internal::TupleType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple4( const U& other ) noexcept
            : values( other.values )
        { }

        template<Internal::TupleType U>
            requires ( std::is_same_v<Traits, typename U::Traits> == false )
        explicit Tuple4( const U& other ) noexcept
            : x( static_cast< value_type >( other.x ) ), y( static_cast< value_type >( other.y ) ), z( static_cast< value_type >( other.z ) ), w( static_cast< value_type >( other.w ) )
        { }

        template<Internal::SimdType U>
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

        template<Internal::TupleType U>
            requires ( U::Size == Size )
        constexpr bool operator == ( const U& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z ) && IsSameValue( w, other.w );
        }

        template<Internal::TupleType U>
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

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator == ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values.data( ) ), other.simd );
        }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        bool operator != ( const U& other ) const noexcept
        {
            return Traits::AllEqual( Traits::Load( values.data( ) ), other.simd ) == false;
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values.data( ) ) );
        }

        DerivedType& operator += ( const Simd& other ) noexcept
        {
            values = Traits::ToArray( Traits::Add( Traits::Load( values ), other.simd ) );
            return static_cast< DerivedType& >( *this );
        }

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        template<Internal::TupleType U>
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

        WideString ToString( ) const
        {
            return Format( L"[{}, {}, {}, {}]", x, y, z, w );
        }

    };


    // Addition

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T,U>
    inline T operator + ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Add( lhs.simd, rhs.simd );
    }
    
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T operator + ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Add( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T operator + ( const U& lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT operator + ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    template<Internal::SimdType T, typename U>
        requires IsArithmetic<U>
    inline T operator + ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Add( lhs.simd, Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) );
    }

    template<Internal::TupleType T, typename U>
        requires IsArithmetic<U>
    inline typename T::Simd operator + ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Add( Traits::Load( lhs.values ), Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) );
    }

    template< typename T, Internal::SimdType U>
        requires IsArithmetic<T>
    inline U operator + ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        return Traits::Add( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), rhs.simd );
    }

    template< typename T, Internal::TupleType U>
        requires IsArithmetic<T>
    inline typename U::Simd operator + ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Add( Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( lhs ) ), Traits::Load( rhs.values ) );
    }


    // Subtraction
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T operator - ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( lhs.simd, rhs.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T operator - ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( lhs.simd, Traits::Load( rhs.values ) );
    }

    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T operator - ( const U& lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( Traits::Load( lhs.values ), rhs.simd );
    }

    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT operator - ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( Traits::Load( lhs.values ), Traits::Load( rhs.values ) );
    }


    template<Internal::SimdType T, typename U>
        requires IsArithmetic<U>
    inline T operator - ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( lhs.simd, Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) );
    }

    template<Internal::TupleType T, typename U>
        requires IsArithmetic<U>
    inline typename T::Simd operator - ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( Traits::Load( lhs.values ), Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( rhs ) ) );
    }

    template< typename T, Internal::SimdType U>
        requires IsArithmetic<T>
    inline U operator - ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename U::Traits;
        return Traits::Sub( Traits::Fill<Traits::Size>( static_cast< typename U::value_type >( lhs ) ), rhs.simd );
    }

    template< typename T, Internal::TupleType U>
        requires IsArithmetic<T>
    inline typename U::Simd operator - ( const T lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( Traits::Fill<Traits::Size>( static_cast< typename T::value_type >( lhs ) ), Traits::Load( rhs.values ) );
    }


    // Multiplication

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T operator * ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Mul( lhs.simd, rhs.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T operator * ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Mul( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T operator * ( const U& lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Mul( Traits::Load( lhs.values ), rhs.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT operator * ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    template<Internal::SimdType T, typename U>
        requires IsArithmetic<U>
    inline T operator * ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Mul( lhs.simd, Traits::Fill<Traits::Size>( static_cast< Type >( rhs ) ) );
    }
    template<typename U, Internal::SimdType T>
        requires IsArithmetic<U>
    inline T operator * ( const U lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Mul( Traits::Fill<Traits::Size>( static_cast< Type >( lhs ) ), rhs.simd );
    }

    template<Internal::TupleType T, typename U, typename ResultT = typename T::Simd>
        requires IsArithmetic<U>
    inline ResultT operator * ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( rhs ) ) );
    }
    template<typename U, Internal::TupleType T, typename ResultT = typename T::Simd>
        requires IsArithmetic<U>
    inline ResultT operator * ( const U lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Mul( Traits::Fill<Traits::Size>( static_cast< Type >( lhs ) ), Traits::Load( rhs.values.data( ) ) );
    }


    // Division

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T operator / ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Div( lhs.simd, rhs.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T operator / ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Div( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T operator / ( const U& lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), lhs.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT operator / ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    template<Internal::SimdType T, typename U>
        requires IsArithmetic<U>
    inline T operator / ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Div( lhs.simd, Traits::FillDivisor<Traits::Size>( static_cast< Type >( rhs ) ) );
    }
    template<typename U, Internal::SimdType T>
        requires IsArithmetic<U>
    inline T operator / ( const U lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Div( Traits::Fill<Traits::Size>( static_cast< Type >( lhs ) ), rhs.simd );
    }

    template<Internal::TupleType T, typename U, typename ResultT = typename T::Simd>
        requires IsArithmetic<U>
    inline ResultT operator / ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::FillDivisor<Traits::Size>( static_cast< Type >( rhs ) ) );
    }
    template<typename U, Internal::TupleType T, typename ResultT = typename T::Simd>
        requires IsArithmetic<U>
    inline ResultT operator / ( const U lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Div( Traits::Fill<Traits::Size>( static_cast< Type >( lhs ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Operations
    
    


    /// <summary>
    /// Retrieves the lowest element of v 
    /// </summary>
    template<Internal::SimdType T>
    inline auto First( const T& v )
    {
        using Traits = typename T::Traits;
        return Traits::First( v.simd );
    }
    /// <summary>
    /// Retrieves the lowest element of v 
    /// </summary>
    template<Internal::TupleType T>
    inline auto First( const T& v )
    {
        return v.x;
    }


    /// <summary>
    /// Calculates the horizontal sum of the elements in the vector.
    /// </summary>
    template<Internal::SimdType T>
    inline T HSum( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HSum( t.simd );
    }

    /// <summary>
    /// Calculates the horizontal sum of the elements in the vector.
    /// </summary>
    template<Internal::SimdType T, typename ResultT = typename T::value_type>
    inline ResultT ScalarHSum( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Traits::HSum( t.simd ) );
    }

    /// <summary>
    /// Calculates the horizontal sum of the elements in the vector.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::value_type>
    inline ResultT ScalarHSum( const T& t ) noexcept
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
            ResultT result{};
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
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT HSum( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill<Traits::Size>( ScalarHSum( t ) );
    }

    // Avg

    /// <summary>
    /// Calculates the average value of the elements in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Avg( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Div( Traits::HSum( t.simd ), Traits::FillDivisor<Traits::Size>( static_cast<typename Traits::Type>( Traits::Size ) ));
    }

    /// <summary>
    /// Calculates the average value of the elements in the argument.
    /// </summary>
    template<Internal::TupleType T>
    inline typename T::Simd Avg( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Div( Traits::HSum( Traits::Load( t.values ) ), Traits::FillDivisor<Traits::Size>( static_cast< typename Traits::Type >( Traits::Size ) ) );
    }

    /// <summary>
    /// Calculates the average value of the elements in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline typename T::value_type ScalarAvg( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return ScalarHSum( t ) / static_cast< typename Traits::Type >( Traits::Size );
    }

    /// <summary>
    /// Calculates the average value of the elements in the argument.
    /// </summary>
    template<Internal::TupleType T>
    inline typename T::value_type ScalarAvg( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return ScalarHSum( t ) / static_cast< typename Traits::Type >( Traits::Size );
    }




    /// <summary>
    /// Calculates the horizontal product of the elements in the vector.
    /// </summary>
    template<Internal::SimdType T>
    inline T HProd( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HProd( t.simd );
    }

    template<Internal::SimdType T>
    inline auto ScalarHProd( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::HProd( t ).simd );
    }

    /// <summary>
    /// Calculates the horizontal product of the elements in the vector.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::value_type>
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
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT HProd( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill<Traits::Size>( ScalarHProc( t ) );
    }


    /// <summary>
    /// 
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T> && Internal::IsCompatible<S, U>
    inline bool Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( lhs.simd, rhs.simd, epsilon.simd );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline bool Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( lhs.simd, rhs.simd, Traits::Load( epsilon.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline bool Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( lhs.simd, Traits::Load( rhs.values ), epsilon.simd );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline bool Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( lhs.simd, Traits::Load( rhs.values ), Traits::Load( epsilon.values ) );
    }

    //
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline bool Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( Traits::Load( lhs.values ), rhs.simd, epsilon.simd );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline bool Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( Traits::Load( lhs.values ), rhs.simd, Traits::Load( epsilon.values ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline bool Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( Traits::Load( lhs.values ), Traits::Load( rhs.values ), epsilon.simd );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline bool Equal( const S& lhs, const T& rhs, const U& epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( Traits::Load( lhs.values ), Traits::Load( rhs.values ), Traits::Load( epsilon.values ) );
    }

    template<Internal::SimdType S, Internal::SimdType T, typename U>
        requires Internal::IsCompatible<S, T> && IsArithmetic<U>
    inline bool Equal( const S& lhs, const T& rhs, U epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( lhs.simd, rhs.simd, Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( epsilon ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, typename U>
        requires Internal::IsCompatible<S, T>&& IsArithmetic<U>
    inline bool Equal( const S& lhs, const T& rhs, U epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( lhs.simd, Traits::Load( rhs.values ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( epsilon ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T, typename U>
        requires Internal::IsCompatible<S, T>&& IsArithmetic<U>
    inline bool Equal( const S& lhs, const T& rhs, U epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( Traits::Load( lhs.values ), rhs.simd, Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( epsilon ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, typename U>
        requires Internal::IsCompatible<S, T>&& IsArithmetic<U>
    inline bool Equal( const S& lhs, const T& rhs, U epsilon ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::AllEqual( Traits::Load( lhs.values ), Traits::Load( rhs.values ), Traits::Fill<Traits::Size>( static_cast< typename Traits::Type >( epsilon ) ) );
    }

    template<Internal::SimdType S, Internal::SimdType T>
        requires Internal::IsCompatible<S, T>
    inline bool Equal( const S& lhs, const T& rhs ) noexcept
    {
        using Traits = typename S::Traits;
        using Constants = typename Traits::Constants;
        return Traits::AllEqual( lhs.simd, rhs.simd, Constants::Epsilon );
    }
    template<Internal::SimdType S, Internal::TupleType T>
        requires Internal::IsCompatible<S, T>
    inline bool Equal( const S& lhs, const T& rhs ) noexcept
    {
        using Traits = typename S::Traits;
        using Constants = typename Traits::Constants;
        return Traits::AllEqual( lhs.simd, Traits::Load( rhs.values ), Constants::Epsilon );
    }
    template<Internal::TupleType S, Internal::SimdType T>
        requires Internal::IsCompatible<S, T>
    inline bool Equal( const S& lhs, const T& rhs ) noexcept
    {
        using Traits = typename S::Traits;
        using Constants = typename Traits::Constants;
        return Traits::AllEqual( Traits::Load( lhs.values ), rhs.simd, Constants::Epsilon );
    }
    template<Internal::TupleType S, Internal::TupleType T>
        requires Internal::IsCompatible<S, T>
    inline bool Equal( const S& lhs, const T& rhs ) noexcept
    {
        using Traits = typename S::Traits;
        using Constants = typename Traits::Constants;
        return Traits::AllEqual( Traits::Load( lhs.values ), Traits::Load( rhs.values ), Constants::Epsilon );
    }



    // Abs

    /// <summary>
    /// Computes the absolute value of each element held by the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Abs( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( t.simd );
    }
    /// <summary>
    /// Computes the absolute value of each element held by the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Abs( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Traits::Load( t.values ) );
    }

    // FastAbs

    /// <summary>
    /// Computes the absolute value of each element held by the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T FastAbs( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastAbs( t.simd );
    }
    /// <summary>
    /// Computes the absolute value of each element held by the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT FastAbs( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastAbs( Traits::Load( t.values ) );
    }



    // Min

    /// <summary>
    /// Makes a comparison between the elements held by the two arguments, and 
    /// returns a TupleSimd containing the smallest elements.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Min( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Min( lhs.simd, rhs.simd );
    }

    /// <summary>
    /// Makes a comparison between the elements held by the two arguments, and 
    /// returns a TupleSimd containing the smallest elements.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Min( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Min( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }

    /// <summary>
    /// Makes a comparison between the elements held by the two arguments, and 
    /// returns a TupleSimd containing the smallest elements.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Min( const U& lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Min( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }

    /// <summary>
    /// Makes a comparison between the elements held by the two arguments, and 
    /// returns a TupleSimd containing the smallest elements.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Min( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Min( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Max

    /// <summary>
    /// Makes a comparison between the elements held by the two arguments, and 
    /// returns a TupleSimd containing the largest elements.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Max( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Max( lhs.simd, rhs.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Max( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Max( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Max( const U& lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Max( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Max( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Max( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }


    // Sqr

    /// <summary>
    /// Computes the square value of each element held by the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Sqr( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Mul( t.simd, t.simd );
    }
    /// <summary>
    /// Computes the square value of each element held by the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Sqr( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Sqr<typename T::Simd>( Traits::Load( t.values.data( ) ) );
    }

    // Ceil


    /// <summary>
    /// Computes the ceiling of each element held by the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Ceil( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Ceil( t.simd );
    }
    /// <summary>
    /// Computes the ceiling of each element held by the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Ceil( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Ceil( Traits::Load( t.values.data( ) ) );
    }

    // Floor

    /// <summary>
    /// Computes the floor of each element held by the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Floor( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Floor( t.simd );
    }

    /// <summary>
    /// Computes the floor of each element held by the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Floor( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Floor( Traits::Load( t.values.data( ) ) );
    }

    // Round

    /// <summary>
    /// Rounds each element held by the argument towards the nearest even integer.
    /// </summary>
    template<Internal::SimdType T>
    inline T Round( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Round( t.simd );
    }
    /// <summary>
    /// Rounds each element held by the argument towards the nearest even integer.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Round( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Round( Traits::Load( t.values.data( ) ) );
    }

    // Trunc


    /// <summary>
    /// Rounds each element held by the argument to the nearest integer in the direction of zero.
    /// </summary>
    template<Internal::SimdType T>
    inline T Trunc( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Truncate( t.simd );
    }
    /// <summary>
    /// Rounds each element held by the argument to the nearest integer in the direction of zero.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Trunc( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Truncate( Traits::Load( t.values.data( ) ) );
    }

    // Lerp

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U, typename NumberT>
        requires std::is_arithmetic_v<NumberT> && Internal::IsCompatible<T, U> 
    inline T Lerp( const T& a, const U& b, NumberT t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp( a.simd, b.simd, static_cast< Type >( t ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U, typename NumberT>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T Lerp( const T& a, const U& b, NumberT t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp( a.simd, Traits::Load( b.values ), static_cast< Type >( t ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType T, Internal::SimdType U, typename NumberT>
        requires std::is_arithmetic_v<NumberT> && Internal::IsCompatible<T, U>
    inline U Lerp( const T& a, const U& b, NumberT t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp( Traits::Load( a.values ), b.simd, static_cast< Type >( t ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT Lerp( const T& a, const U& b, NumberT t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp( Traits::Load( a.values ), Traits::Load( b.values ), static_cast< Type >( t ) ) );
    }

    

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp( a.simd, b.simd, t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp( a.simd, b.simd, Traits::Load( t.values ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp( a.simd, Traits::Load( b.values ), t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp( a.simd, Traits::Load( b.values ), Traits::Load( t.values ) ) );
    }

    //

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp( Traits::Load( a.values ), b.simd, t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp( Traits::Load( a.values ), b.simd, Traits::Load( t.values ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT Lerp( const S& a, const T& b, const U& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp( Traits::Load( a.values ), Traits::Load( b.values ), Traits::Load( t.values ) ) );
    }

    
    /// <summary>
    /// Calculates the linear interpolation between a and b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<typename NumberT1, typename NumberT2, Internal::SimdType T>
        requires std::is_arithmetic_v<NumberT1> && std::is_arithmetic_v<NumberT2>
    inline T Lerp( NumberT1 a, NumberT2 b, const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp( Traits::Fill<T::Size>( static_cast< Type >( a ) ), Traits::Fill<T::Size>( static_cast< Type >( b ) ), t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between a and b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<typename NumberT1, typename NumberT2, Internal::TupleType T>
        requires std::is_arithmetic_v<NumberT1>&& std::is_arithmetic_v<NumberT2>
    inline typename T::Simd Lerp( NumberT1 a, NumberT2 b, const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp( Traits::Fill<T::Size>( static_cast< Type >( a ) ), Traits::Fill<T::Size>( static_cast< Type >( b ) ), Traits::Load( t.values ) ) );
    }
    

    // Lerp2

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U, typename NumberT>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T Lerp2( NumberT t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp2( a.simd, b.simd, static_cast< Type >( t ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U, typename NumberT>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T Lerp2( NumberT t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp2( a.simd, Traits::Load( b.values ), static_cast< Type >( t ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType T, Internal::SimdType U, typename NumberT>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U Lerp2( NumberT t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp2( Traits::Load( a.values ), b.simd, static_cast< Type >( t ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT Lerp2( NumberT t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp2( Traits::Load( a.values ), Traits::Load( b.values ), static_cast< Type >( t ) ) );
    }



    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp2( a.simd, b.simd, t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp2( a.simd, Traits::Load( b.values ), t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp2( Traits::Load( a.values ), b.simd, t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp2( Traits::Load( a.values ), Traits::Load( b.values ), t.simd ) );
    }

    //

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp2( a.simd, b.simd, Traits::Load( t.values ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp2( a.simd, Traits::Load( b.values ), Traits::Load( t.values ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp2( Traits::Load( a.values ), b.simd, Traits::Load( t.values ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT Lerp2( const S& t, const T& a, const U& b ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::Lerp2( Traits::Load( a.values ), Traits::Load( b.values ), Traits::Load( t.values ) ) );
    }


    /// <summary>
    /// Calculates the linear interpolation between a and b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::SimdType T, typename NumberT1, typename NumberT2>
        requires std::is_arithmetic_v<NumberT1>&& std::is_arithmetic_v<NumberT2>
    inline T Lerp2( const T& t, NumberT1 a, NumberT2 b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp2( Traits::Fill<T::Size>( static_cast< Type >( a ) ), Traits::Fill<T::Size>( static_cast< Type >( b ) ), t.simd ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between a and b, for elements of
    /// t is inside [0,1), or the linear extrapolation for elements
    /// in t outside [0,1).
    /// </summary>
    template<Internal::TupleType T, typename NumberT1, typename NumberT2>
        requires std::is_arithmetic_v<NumberT1>&& std::is_arithmetic_v<NumberT2>
    inline typename T::Simd Lerp2( const T& t, NumberT1 a, NumberT2 b ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::Lerp2( Traits::Fill<T::Size>( static_cast< Type >( a ) ), Traits::Fill<T::Size>( static_cast< Type >( b ) ), Traits::Load( t.values ) ) );
    }

    
    // Permute

    template<int shuffleMask, Internal::SimdType T>
    inline T Permute( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Permute<shuffleMask>( t.simd );
    }
    template<int shuffleMask, Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Permute( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Permute<shuffleMask>( Traits::Load( t.values.data( ) ) );
    }

    // Clamp

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    //
    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, upperBounds.simd );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename S::Simd>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified the elements of lowerBounds
    /// and the elements of upperBounds, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT> && Internal::IsCompatible<T, U>
    inline ResultT Clamp( NumberT v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Fill<Traits::Size>( v ), Traits::Load( lowerBounds.values ), Traits::Load( upperBounds.values ) );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified by lowerBound
    /// and upperBound, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::SimdType S, typename T, typename U>
        requires IsArithmetic<T> && IsArithmetic<U>
    inline S Clamp( const S& v, const T& lowerBound, const U& upperBound ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Clamp( v.simd, Traits::Fill( static_cast<typename S::value_type>( lowerBound ) ), Traits::Fill( static_cast< typename S::value_type >( upperBound ) ) );
    }

    /// <summary>
    /// Returns the elements of v, if the elements are between their
    /// respective boundaries specified by lowerBound
    /// and upperBound, otherwise the value of nearest
    /// boundary is returned.
    /// </summary>
    template<Internal::TupleType S, typename T, typename U>
        requires IsArithmetic<T>&& IsArithmetic<U>
    inline typename S::Simd Clamp( const S& v, const T& lowerBound, const U& upperBound ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Clamp( Traits::Load( v.values ), Traits::Fill( static_cast< typename S::value_type >( lowerBound ) ), Traits::Fill( static_cast< typename S::value_type >( upperBound ) ) );
    }


    template<Internal::SimdType S>
    inline S ClampZero( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Max( Traits::Zero(), v.simd );
    }

    template<Internal::TupleType S>
    inline typename S::Simd ClampZero( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Max( Traits::Zero( ), Traits::Load( v.values ) );
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
    template<Internal::SimdType S, Internal::SimdType T>
        requires Internal::IsCompatible<S, T>
    inline S InBounds( const S& v, const T& bounds ) noexcept
    {
        using Traits = typename T::Traits;
        return S( Traits::InBounds( v.simd, bounds.simd ) );
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
    template<Internal::SimdType S, Internal::TupleType T>
        requires Internal::IsCompatible<S, T>
    inline S InBounds( const S& v, const T& bounds ) noexcept
    {
        using Traits = typename T::Traits;
        return S( Traits::InBounds( v.simd, Traits::Load( bounds.values ) ) );
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
    template<Internal::TupleType S, Internal::SimdType T>
        requires Internal::IsCompatible<S, T>
    inline T InBounds( const S& v, const T& bounds ) noexcept
    {
        using Traits = typename T::Traits;
        return T( Traits::InBounds( Traits::Load( v.values ), bounds.simd ) );
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
    template<Internal::TupleType S, Internal::TupleType T>
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd InBounds( const S& v, const T& bounds ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename S::Simd;
        return Simd( Traits::InBounds( Traits::Load( v.values ), Traits::Load( v.bounds ) ) );
    }


    // ClampLength

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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T> && Internal::IsCompatible<S, U>
    inline S ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline S ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;

        return ClampLength( v, lengthMin, Simd( lengthMax ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline S ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;

        return ClampLength( v, Simd( lengthMin ), lengthMax );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline S ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;

        return ClampLength( v, Simd( lengthMin ), Simd( lengthMax ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline typename S::Simd ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return ClampLength( Simd( v ), lengthMin, lengthMax );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline typename S::Simd ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return ClampLength( Simd( v ), lengthMin, Simd( lengthMax ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline typename S::Simd ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return ClampLength( Simd( v ), Simd( lengthMin ), lengthMax );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline typename S::Simd ClampLength( const S& v, const T& lengthMin, const U& lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return ClampLength( Simd( v ), Simd( lengthMin ), Simd( lengthMax ) );
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
    template<Internal::SimdType S, typename T, typename U>
        requires IsFloatingPoint<T> && IsFloatingPoint<U>
    inline S ClampLength( const S& v, const T lengthMin, const U lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using FloatT = typename Traits::Type;
        using Simd = S;

        return ClampLength( v, Simd( Traits::Fill<Traits::Size>( static_cast< FloatT >( lengthMin ) ) ), Simd( Traits::Fill<Traits::Size>( static_cast< FloatT >( lengthMax ) ) ) );
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
    template<Internal::TupleType S, typename T, typename U>
        requires IsFloatingPoint<T>&& IsFloatingPoint<U>
    inline S ClampLength( const S& v, const T lengthMin, const U lengthMax ) noexcept
    {
        using Traits = typename S::Traits;
        using FloatT = typename Traits::Type;
        using Simd = S;

        return ClampLength( Simd( v ), Simd( Traits::Fill<Traits::Size>( static_cast< FloatT >( lengthMin ) ) ), Simd( Traits::Fill<Traits::Size>( static_cast< FloatT >( lengthMax ) ) ) );
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
    template<Internal::SimdType S, Internal::SimdType T>
        requires Internal::IsCompatible<S, T>
    inline S Reflect( const S& incident, const T& normal ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;

        auto result = Traits::Dot( incident.simd, normal.simd );
        result = Traits::Add( result, result );
        return Simd( Traits::FNMSub( result, normal.simd, incident.simd ) );
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
    template<Internal::SimdType S, Internal::TupleType T>
        requires Internal::IsCompatible<S, T>
    inline S Reflect( const S& incident, const T& normal ) noexcept
    {
        using Simd = S;

        return Reflect( incident, Simd( normal ) );
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
    template<Internal::TupleType S, Internal::SimdType T>
        requires Internal::IsCompatible<S, T>
    inline T Reflect( const S& incident, const T& normal ) noexcept
    {
        using Simd = T;

        return Reflect( Simd( incident ), normal );
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
    template<Internal::TupleType S, Internal::TupleType T>
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd Reflect( const S& incident, const T& normal ) noexcept
    {
        using Simd = typename S::Simd;

        return Reflect( Simd( incident ), Simd( normal ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T> && Internal::IsCompatible<S, U>
    inline S Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline S Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return Refract( incident, normal, Simd( refractionIndex ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline S Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return Refract( incident, Simd( normal ), refractionIndex );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline S Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return Refract( incident, Simd( normal ), Simd( refractionIndex ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline typename S::Simd Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return Refract( Simd( incident ), normal, refractionIndex );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline typename S::Simd Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return Refract( Simd( incident ), normal, Simd( refractionIndex ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline typename S::Simd Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return Refract( Simd( incident ), Simd( normal ), refractionIndex );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline typename S::Simd Refract( const S& incident, const T& normal, const U& refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return Refract( Simd( incident ), Simd( normal ), Simd( refractionIndex ) );
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
    template<Internal::SimdType S, Internal::SimdType T, typename U>
        requires Internal::IsCompatible<S, T>&& IsFloatingPoint<U>
    inline S Refract( const S& incident, const T& normal, const U refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return Refract( incident, normal, Simd( Traits::Fill( refractionIndex ) ) );
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
    template<Internal::SimdType S, Internal::TupleType T, typename U>
        requires Internal::IsCompatible<S, T>&& IsFloatingPoint<U>
    inline S Refract( const S& incident, const T& normal, const U refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return Refract( incident, Simd( normal ), Simd( Traits::Fill( refractionIndex ) ) );
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
    template<Internal::TupleType S, Internal::SimdType T, typename U>
        requires Internal::IsCompatible<S, T>&& IsFloatingPoint<U>
    inline typename S::Simd Refract( const S& incident, const T& normal, const U refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return Refract( Simd( incident ), normal, Simd( Traits::Fill( refractionIndex ) ) );
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
    template<Internal::TupleType S, Internal::TupleType T, typename U>
        requires Internal::IsCompatible<S, T>&& IsFloatingPoint<U>
    inline typename S::Simd Refract( const S& incident, const T& normal, const U refractionIndex ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return Refract( Simd( incident ), Simd( normal ), Simd( Traits::Fill( refractionIndex ) ) );
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
    template<Internal::SimdType S>
    inline S Orthogonal( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;

        return Simd( Traits::Orthogonal( v.simd ) );
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
    template<Internal::TupleType S>
    inline typename S::Simd Orthogonal( const S& v ) noexcept
    {
        using Simd = typename S::Simd;
        return Orthogonal( Simd( v ) );
    }


    // Saturate

    /// <summary>
    /// Saturates the elements of v to the range 0.0 to 1.0.
    /// </summary>
    template<Internal::SimdType T>
    inline T Saturate( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Saturate( v.simd );
    }
    /// <summary>
    /// Saturates the elements of v to the range 0.0 to 1.0.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Saturate( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Saturate( Traits::Load( v.values ) );
    }

    // Sqrt

    /// <summary>
    /// Calculates the square root of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Sqrt( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( v.simd );
    }

    /// <summary>
    /// Calculates the square root of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Sqrt( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( Traits::Load( v.values ) );
    }

    // SafeSqrt

    /// <summary>
    /// Calculates the square root of each element greater or 
    /// equal to 0.f in the argument. For elements less than 
    /// 0.f, the result is 0.f.
    /// </summary>
    template<Internal::SimdType T>
    inline T SafeSqrt( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( Traits::Max( Traits::Zero(), v.simd ) );
    }

    /// <summary>
    /// Calculates the square root of each element greater or 
    /// equal to 0.f in the argument. For elements less than 
    /// 0.f, the result is 0.f.
    /// </summary>
    template<Internal::TupleType T>
    inline typename T::Simd SafeSqrt( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( Traits::Max( Traits::Zero( ), Traits::Load( v.values ) ) );
    }


    // ReciprocalSqrt

    /// <summary>
    /// Calculates the reciprocal square root of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T ReciprocalSqrt( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        return Traits::Div(Traits::Fill<Traits::Size>(Constants<FloatT>::One), Traits::Sqrt( t.simd ));
    }
    /// <summary>
    /// Calculates the reciprocal square root of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ReciprocalSqrt( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        return Traits::Div( Traits::Fill<Traits::Size>( Constants<FloatT>::One ), Traits::Sqrt( Traits::Load( t.values ) ) );
    }

    // Reciprocal

    /// <summary>
    /// Calculates the reciprocal of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Reciprocal( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        return Traits::Div( Traits::Fill<Traits::Size>( Constants<FloatT>::One ), t.simd );
    }

    /// <summary>
    /// Calculates the reciprocal of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Reciprocal( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        return Traits::Div( Traits::Fill<Traits::Size>( Constants<FloatT>::One ), Traits::Load( t.values ) );
    }


    // FMA

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMA( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMA( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMA( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMA( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMA( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMA( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMA( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMA( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( a.simd, b.simd, c.simd );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }


    /// <summary>
    /// Evaluates the provided polynomial using Horner’s method
    /// </summary>

    template <Internal::SimdType T, typename C>
        requires IsArithmetic<C>
    constexpr inline T EvaluatePolynomial( const T& t, C c )
    {
        using Traits = typename T::Traits;
        return Traits::Fill<Traits::Size>( c );
    }
    template <Internal::SimdType T, Internal::SimdType C>
        requires Internal::IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, C c )
    {
        return c;
    }

    template <Internal::SimdType T, typename C, typename... Args>
        requires IsArithmetic<C>
    constexpr inline T EvaluatePolynomial( const T& t, C c, Args... remaining );

    template <Internal::TupleType T, typename C, typename... Args>
        requires IsArithmetic<C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, C c, Args... remaining );

    template <Internal::SimdType T, Internal::SimdType C, typename... Args>
        requires Internal::IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, const C& c, Args... remaining );

    template <Internal::TupleType T, Internal::SimdType C, typename... Args>
        requires Internal::IsCompatible<T, C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, const C& c, Args... remaining );

    template <Internal::SimdType T, Internal::TupleType C, typename... Args>
        requires Internal::IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, const C& c, Args... remaining );

    template <Internal::TupleType T, Internal::TupleType C, typename... Args>
        requires Internal::IsCompatible<T, C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, const C& c, Args... remaining );


    template <Internal::SimdType T, typename C, typename... Args>
        requires IsArithmetic<C>
    constexpr inline T EvaluatePolynomial( const T& t, C c, Args... remaining )
    {
        using Traits = typename T::Traits;
        return FMA( t, EvaluatePolynomial( t, remaining... ), T( Traits::Fill<Traits::Size>( c ) ) );
    }

    template <Internal::TupleType T, typename C, typename... Args>
        requires IsArithmetic<C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, C c, Args... remaining )
    {
        using Traits = typename T::Traits;
        using SimdType = typename T::Simd;
        SimdType tSimd( t );
        return FMA( tSimd, EvaluatePolynomial( tSimd, remaining... ), SimdType( Traits::Fill<Traits::Size>( c ) ) );
    }

    template <Internal::SimdType T, Internal::SimdType C, typename... Args>
        requires Internal::IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, const C& c, Args... remaining )
    {
        using Traits = typename T::Traits;
        return FMA( t, EvaluatePolynomial( t, remaining... ), c );
    }

    template <Internal::TupleType T, Internal::SimdType C, typename... Args>
        requires Internal::IsCompatible<T, C>
    constexpr inline typename T::Simd EvaluatePolynomial( const T& t, const C& c, Args... remaining )
    {
        using Traits = typename T::Traits;
        using SimdType = typename T::Simd;
        SimdType tSimd( t );
        return FMA( tSimd, EvaluatePolynomial( tSimd, remaining... ), c );
    }

    template <Internal::SimdType T, Internal::TupleType C, typename... Args>
        requires Internal::IsCompatible<T, C>
    constexpr inline T EvaluatePolynomial( const T& t, const C& c, Args... remaining )
    {
        using Traits = typename T::Traits;
        using SimdType = typename C::Simd;
        SimdType cSimd( c );
        return FMA( t, EvaluatePolynomial( t, remaining... ), cSimd );
    }
    template <Internal::TupleType T, Internal::TupleType C, typename... Args>
        requires Internal::IsCompatible<T, C>
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
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( a.simd, b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the infinite precision intermediate results are obtained. From the 
    /// infinite precision intermediate results, the values in the third operand, c, are subtracted. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAddSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAddSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAddSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAddSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMAddSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAddSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMAddSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAddSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAddSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAddSub( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAddSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAddSub( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMAddSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAddSub( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMAddSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAddSub( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAddSub( a.simd, b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAddSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAddSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAddSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAddSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAddSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAddSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-add-subtract computation on a, b, and c. Corresponding values in two operands, a and b, are 
    /// multiplied and infinite precision intermediate results are obtained. The odd values in the third operand, 
    /// c, are added to the intermediate results while the even values are subtracted from them. The final results 
    /// are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FMAddSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAddSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    // FMSubAdd

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSubAdd( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSubAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSubAdd( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSubAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMSubAdd( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSubAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMSubAdd( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSubAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSubAdd( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSubAdd( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSubAdd( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSubAdd( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMSubAdd( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSubAdd( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMSubAdd( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSubAdd( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSubAdd( a.simd, b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSubAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSubAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSubAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSubAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSubAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSubAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of multiply-subtract-add computation on a, b, and c. Corresponding values in two operands, a and b, 
    /// are multiplied and infinite precision intermediate results are obtained. The odd values in the third 
    /// operand, c, are subtracted from the intermediate results while the even values are added to them. 
    /// The final results are rounded to the nearest floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FMSubAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSubAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    // FNMAdd

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FNMAdd( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FNMAdd( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FNMAdd( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FNMAdd( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMAdd( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FNMAdd( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMAdd( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FNMAdd( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMAdd( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FNMAdd( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMAdd( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FNMAdd( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMAdd( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMAdd( a.simd, b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-add computation on a, b, and c. Corresponding values in two operands, 
    /// a and b, are multiplied and the negated infinite precision intermediate results are added to 
    /// the values in the third operand, c, after which the final results are rounded to the nearest 
    /// floating point values.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FNMAdd( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    // FNMSub

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FNMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FNMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FNMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FNMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMSub( Traits::Fill<Traits::Size>( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FNMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMSub( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FNMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMSub( a.simd, Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FNMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMSub( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FNMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FNMSub( Traits::Load( a.values.data( ) ), Traits::Fill<Traits::Size>( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMSub( a.simd, b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Performs a set of negated multiply-subtract computation on a, b, and c. The values in two operands, a and b, 
    /// are multiplied and the negated infinite precision intermediate result is obtained. From this negated 
    /// intermediate result, the value in the third operand, c, is subtracted. The final result is rounded 
    /// to the nearest floating point value.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FNMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FNMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }


    // Sin

    /// <summary>
    /// Calculates the sine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T Sin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sin( v.simd );
    }
    /// <summary>
    /// Calculates the sine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Sin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sin( Traits::Load( v.values ) );
    }

    // FastSin

    /// <summary>
    /// Calculates the sine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T FastSin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastSin( v.simd );
    }
    /// <summary>
    /// Calculates the sine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT FastSin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastSin( Traits::Load( v.values ) );
    }


    // Cos

    /// <summary>
    /// Calculates the cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T Cos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cos( v.simd );
    }
    /// <summary>
    /// Calculates the cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Cos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cos( Traits::Load( v.values ) );
    }

    // FastCos

    /// <summary>
    /// Calculates the cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T FastCos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastCos( v.simd );
    }
    /// <summary>
    /// Calculates the cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T>
    inline typename T::Simd FastCos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastCos( Traits::Load( v.values ) );
    }


    // SinCos

    /// <summary>
    /// Calculates the sine and cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T SinCos( const T& v, T* cosines ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::SinCos( v.simd, &cosines->simd );
    }

    /// <summary>
    /// Calculates the sine and cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T>
    inline typename T::Simd SinCos( const T& v, typename T::Simd* cosines ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::SinCos( Traits::Load( v.values ), &cosines->simd );
    }

    // FastSinCos

    /// <summary>
    /// Calculates the sine and cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T FastSinCos( const T& v, T* cosines ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastSinCos( v.simd, &cosines->simd );
    }

    /// <summary>
    /// Calculates the sine and cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T>
    inline typename T::Simd FastSinCos( const T& v, typename T::Simd* cosines ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastSinCos( Traits::Load( v.values ), &cosines->simd );
    }




    // Tan

    /// <summary>
    /// Calculates the tangent of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T Tan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Tan( v.simd );
    }

    /// <summary>
    /// Calculates the tangent of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T>
    inline typename T::Simd Tan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Tan( Traits::Load( v.values ) );
    }


    // FastTan

    /// <summary>
    /// Calculates the tangent of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T FastTan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastTan( v.simd );
    }

    /// <summary>
    /// Calculates the tangent of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T>
    inline typename T::Simd FastTan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastTan( Traits::Load( v.values ) );
    }


    // ASin

    /// <summary>
    /// Calculates the inverse sine of each element in the argument, in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T ASin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ASin( v.simd );
    }
    /// <summary>
    /// Calculates the inverse sine of each element in the argument, in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ASin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ASin( Traits::Load( v.values.data( ) ) );
    }

    // ACos

    /// <summary>
    /// Calculates the inverse cosine of each element in the argument, in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T ACos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ACos( v.simd );
    }

    /// <summary>
    /// Calculates the inverse cosine of each element in the argument, in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ACos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ACos( Traits::Load( v.values.data( ) ) );
    }

    // ATan

    /// <summary>
    /// Calculates the inverse tangent of each element in the argument, in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T ATan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan( v.simd );
    }
    /// <summary>
    /// Calculates the inverse tangent of each element in the argument, in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ATan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan( Traits::Load( v.values.data( ) ) );
    }


    // FastATan

    /// <summary>
    /// Calculates the inverse tangent of each element in the argument, in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T FastATan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastATan( v.simd );
    }
    /// <summary>
    /// Calculates the inverse tangent of each element in the argument, in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT FastATan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastATan( Traits::Load( v.values.data( ) ) );
    }



    // ATan2

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T ATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan2( x.simd, y.simd );
    }

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T ATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T ATan2( const U& x, const T& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), y.simd );
    }

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT ATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }


    // FastATan2

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T FastATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastATan2( x.simd, y.simd );
    }

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T FastATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T FastATan2( const U& x, const T& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastATan2( Traits::Load( x.values.data( ) ), y.simd );
    }

    /// <summary>
    /// Calculates the inverse tangent of each element in x divided by the
    /// corresponding element in y, in radians.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT FastATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FastATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
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
    template<Internal::SimdType T>
    inline T ModAngles( const T& angles )
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;

        auto result = Traits::Round( Traits::Mul( angles.simd, Traits::Fill<Traits::Size>( Constants<FloatT>::Inv2Pi ) ) );
        return Traits::FNMAdd( result, Traits::Fill<Traits::Size>( Constants<FloatT>::PiTimes2 ), angles.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ModAngles( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Math::ModAngles( Simd( Traits::Load( v.values ) ) );
    }

    // AddAngles

    /// <summary>
    /// Adds the angles in the corresponding elements of v1 and v2.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T AddAngles( const T& v1, const U& v2 ) noexcept
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

    /// <summary>
    /// Adds the angles in the corresponding elements of v1 and v2.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T AddAngles( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Math::AddAngles( v1, Simd(Traits::Load( v2.values )) );
    }

    /// <summary>
    /// Adds the angles in the corresponding elements of v1 and v2.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T AddAngles( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Math::AddAngles( Simd(Traits::Load( v1.values )), v2 );
    }
    /// <summary>
    /// Adds the angles in the corresponding elements of v1 and v2.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT AddAngles( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Math::AddAngles( Simd(Traits::Load( v1.values )), Simd(Traits::Load( v2.values )) );
    }

    // SubtractAngles

    /// <summary>
    /// Subtracts the angles in v2 from the corresponding elements of v1.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T SubtractAngles( const T& v1, const U& v2 ) noexcept
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

    /// <summary>
    /// Subtracts the angles in v2 from the corresponding elements of v1.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T SubtractAngles( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Math::SubtractAngles( v1, Simd( Traits::Load( v2.values ) ) );
    }

    /// <summary>
    /// Subtracts the angles in v2 from the corresponding elements of v1.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T SubtractAngles( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Math::SubtractAngles( Simd( Traits::Load( v1.values ) ), v2 );
    }

    /// <summary>
    /// Subtracts the angles in v2 from the corresponding elements of v1.
    /// The argument angles must be in the range [-PI,PI), and the
    /// computed angles will be in the range [-PI,PI) 
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT SubtractAngles( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Math::SubtractAngles( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ) );
    }


    // SinH

    /// <summary>
    /// Calculates the hyperbolic sine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T SinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::SinH( v.simd );
    }
    /// <summary>
    /// Calculates the hyperbolic sine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT SinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::SinH( Traits::Load( v.values.data( ) ) );
    }


    // CosH

    /// <summary>
    /// Calculates the hyperbolic cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T CosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::CosH( v.simd );
    }
    /// <summary>
    /// Calculates the hyperbolic cosine of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT CosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::CosH( Traits::Load( v.values.data( ) ) );
    }

    // TanH

    /// <summary>
    /// Calculates the hyperbolic tangent of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T TanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::TanH( v.simd );
    }
    /// <summary>
    /// Calculates the hyperbolic tangent of each element in the argument expressed in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT TanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::TanH( Traits::Load( v.values.data( ) ) );
    }

    // ASinH

    /// <summary>
    /// Calculates the inverse hyperbolic sine of each element in the argument, in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T ASinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ASinH( v.simd );
    }
    /// <summary>
    /// Calculates the inverse hyperbolic sine of each element in the argument, in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ASinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ASinH( Traits::Load( v.values.data( ) ) );
    }

    // ACosH

    /// <summary>
    /// Calculates the inverse hyperbolic cosine of each element in the argument, in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T ACosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ACosH( v.simd );
    }
    /// <summary>
    /// Calculates the inverse hyperbolic cosine of each element in the argument, in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ACosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ACosH( Traits::Load( v.values.data( ) ) );
    }

    // ATanH

    /// <summary>
    /// Calculates the inverse hyperbolic tangent of each element in the argument, in radians.
    /// </summary>
    template<Internal::SimdType T>
    inline T ATanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATanH( v.simd );
    }
    /// <summary>
    /// Calculates the inverse hyperbolic tangent of each element in the argument, in radians.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ATanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATanH( Traits::Load( v.values.data( ) ) );
    }

    // Log

    /// <summary>
    /// Calculates the natural logarithm of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Log( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log( v.simd );
    }

    /// <summary>
    /// Calculates the natural logarithm of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Log( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log( Traits::Load( v.values.data( ) ) );
    }

    // Log1P

    /// <summary>
    /// Calculates the natural logarithm of 1 + each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Log1P( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log1P( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Log1P( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log1P( Traits::Load( v.values.data( ) ) );
    }

    // Log10

    /// <summary>
    /// Calculates the base-10 logarithm of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Log10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log10( v.simd );
    }
    /// <summary>
    /// Calculates the base-10 logarithm of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Log10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log10( Traits::Load( v.values.data( ) ) );
    }

    // Log2

    /// <summary>
    /// Calculates the base-2 logarithm, $$log_{2}_$$, of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Log2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log2( v.simd );
    }
    /// <summary>
    /// Calculates the base-2 logarithm, $$log_{2}_$$, of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Log2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log2( Traits::Load( v.values.data( ) ) );
    }

    // Exp

    /// <summary>
    /// Calculates  $$e$$ (Euler's number, 2.7182818...), raised to the power of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Exp( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp( v.simd );
    }
    /// <summary>
    /// Calculates  $$e$$ (Euler's number, 2.7182818...), raised to the power of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Exp( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp( Traits::Load( v.values.data( ) ) );
    }

    // Exp10

    /// <summary>
    /// Calculates the base-10 exponential of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Exp10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp10( v.simd );
    }
    /// <summary>
    /// Calculates the base-10 exponential of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Exp10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp10( Traits::Load( v.values.data( ) ) );
    }

    // Exp2

    /// <summary>
    /// Calculates the base-2 exponential of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T Exp2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp2( v.simd );
    }
    /// <summary>
    /// Calculates the base-2 exponential of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Exp2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp2( Traits::Load( v.values.data( ) ) );
    }

    // ExpM1

    /// <summary>
    /// Calculates  $$e$$ (Euler's number, 2.7182818...), raised to the power of each element in the argument, $$-1.0$$.
    /// </summary>
    template<Internal::SimdType T>
    inline T ExpM1( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ExpM1( v.simd );
    }
    /// <summary>
    /// Calculates  $$e$$ (Euler's number, 2.7182818...), raised to the power of each element in the argument, $$-1.0$$.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ExpM1( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ExpM1( Traits::Load( v.values.data( ) ) );
    }


    // Pow

    /// <summary>
    /// Calculates the elements in base raised to the corresponding element in exponent.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Pow( const T& base, const U& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Pow( base.simd, exponent.simd );
    }

    /// <summary>
    /// Calculates the elements in base raised to the corresponding element in exponent.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Pow( const T& base, const U& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Pow( base.simd, Traits::Load( exponent.values.data( ) ) );
    }
    /// <summary>
    /// Calculates the elements in base raised to the corresponding element in exponent.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Pow( const U& base, const T& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), exponent.simd );
    }
    /// <summary>
    /// Calculates the elements in base raised to the corresponding element in exponent.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Pow( const T& base, const U& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), Traits::Load( exponent.values.data( ) ) );
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

    template<int n, Internal::SimdType T>
    inline T FastPow( const T& v )
    {
        return Internal::SimdFastPowImpl<T>::Pow<n>( v );
    }

    template<int n, Internal::TupleType T>
    inline typename T::Simd FastPow( const T& v )
    {
        return Internal::SimdFastPowImpl<typename T::Simd>::Pow<n>( v );
    }



    // FMod

    /// <summary>
    /// Computes the floating-point remainder of the division operation $x/y$.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T FMod( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMod( x.simd, y.simd );
    }

    /// <summary>
    /// Computes the floating-point remainder of the division operation $x/y$.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T FMod( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMod( x.simd, Traits::Load( y.values ) );
    }
    /// <summary>
    /// Computes the floating-point remainder of the division operation $x/y$.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T FMod( const U& x, const T& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMod( Traits::Load( x.values ), y.simd );
    }
    /// <summary>
    /// Computes the floating-point remainder of the division operation $x/y$.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT FMod( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMod( Traits::Load( x.values ), Traits::Load( y.values ) );
    }

    /// <summary>
    /// Computes the floating-point remainder of the division operation $x/y$.
    /// </summary>
    template<Internal::SimdType T, typename U>
        requires std::is_convertible_v<U,typename T::Traits::Type>
    inline T FMod( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::FMod( x.simd, Traits::Fill( static_cast< T::Traits::Type >( y ) ) ) );
    }

    template<Internal::TupleType T, typename U>
        requires std::is_convertible_v<U, typename T::Traits::Type>
    inline T FMod( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::FMod( Traits::Load( x.values ), Traits::Fill( static_cast< T::Traits::Type >( y ) ) ) );
    }


    // Hypot

    /// <summary>
    /// Calculates the square root of the sum of the squares of each corresponding 
    /// element in x and y, without undue overflow or underflow at intermediate 
    /// stages of the computation.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Hypot( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Hypot( x.simd, y.simd );
    }

    /// <summary>
    /// Calculates the square root of the sum of the squares of each corresponding 
    /// element in x and y, without undue overflow or underflow at intermediate 
    /// stages of the computation.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Hypot( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Hypot( x.simd, Traits::Load( y.values.data( ) ) );
    }

    /// <summary>
    /// Calculates the square root of the sum of the squares of each corresponding 
    /// element in x and y, without undue overflow or underflow at intermediate 
    /// stages of the computation.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Hypot( const U& x, const T& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), y.simd );
    }

    /// <summary>
    /// Calculates the square root of the sum of the squares of each corresponding 
    /// element in x and y, without undue overflow or underflow at intermediate 
    /// stages of the computation.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Hypot( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // Hermite

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<T, U> && Internal::IsCompatible<T, V> && Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename T::value_type;
        auto t2 = t * t;
        auto t3 = t * t2;

        auto p0 = Traits::Fill( static_cast<FloatT>(2.0) * t3 - static_cast< FloatT >( 3.0 ) * t2 + static_cast< FloatT >( 1.0 ) );
        auto t0 = Traits::Fill( t3 - static_cast< FloatT >( 2.0 ) * t2 + t );
        auto p1 = Traits::Fill( static_cast< FloatT >( -2.0 ) * t3 + static_cast< FloatT >( 3.0 ) * t2 );
        auto t1 = Traits::Fill( t3 - t2 );

        auto result = Traits::Mul( p0, firstPosition.simd );
        result = Traits::FMAdd( firstTangent.simd, t0, result );
        result = Traits::FMAdd( secondPosition.simd, p1, result );
        return Traits::Trim( Traits::FMAdd( secondTangent.simd, t1, result ) );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename W::Simd;
        return Math::Hermite( firstPosition, firstTangent, secondPosition, Simd( Traits::Load( secondTangent.values ) ), t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename V::Simd;
        return Math::Hermite( firstPosition, firstTangent, Simd( Traits::Load( secondPosition.values ) ), secondTangent, t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename V::Simd;
        return Math::Hermite( firstPosition, firstTangent, Simd( Traits::Load( secondPosition.values ) ), Simd( Traits::Load( secondTangent.values ) ), t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename U::Simd;
        return Math::Hermite( firstPosition, Simd( Traits::Load( firstTangent.values ) ), secondPosition, secondTangent, t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename W::Simd;
        return Math::Hermite( firstPosition, Simd( Traits::Load( firstTangent.values ) ), secondPosition, Simd( Traits::Load( secondTangent.values ) ), t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename V::Simd;
        return Math::Hermite( firstPosition, Simd( Traits::Load( firstTangent.values ) ), Simd( Traits::Load( secondPosition.values ) ), secondTangent, t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename V::Simd;
        return Math::Hermite( firstPosition, Simd( Traits::Load( firstTangent.values ) ), Simd( Traits::Load( secondPosition.values ) ), Simd( Traits::Load( secondTangent.values ) ), t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Math::Hermite( Simd( Traits::Load( firstPosition.values ) ), firstTangent, secondPosition, secondTangent, t );
    }

    ///

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename W::Simd;
        return Math::Hermite( Simd( Traits::Load( firstPosition.values ) ), firstTangent, secondPosition, Simd( Traits::Load( secondTangent.values ) ), t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename V::Simd;
        return Math::Hermite( Simd( Traits::Load( firstPosition.values ) ), firstTangent, Simd( Traits::Load( secondPosition.values ) ), secondTangent, t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename V::Simd;
        return Math::Hermite( Simd( Traits::Load( firstPosition.values ) ), firstTangent, Simd( Traits::Load( secondPosition.values ) ), Simd( Traits::Load( secondTangent.values ) ), t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename U::Simd;
        return Math::Hermite( Simd( Traits::Load( firstPosition.values ) ), Simd( Traits::Load( firstTangent.values ) ), secondPosition, secondTangent, t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename W::Simd;
        return Math::Hermite( Simd( Traits::Load( firstPosition.values ) ), Simd( Traits::Load( firstTangent.values ) ), secondPosition, Simd( Traits::Load( secondTangent.values ) ), t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename V::Simd;
        return Math::Hermite( Simd( Traits::Load( firstPosition.values ) ), Simd( Traits::Load( firstTangent.values ) ), Simd( Traits::Load( secondPosition.values ) ), secondTangent, t );
    }

    /// <summary>
    /// Calculates the Hermite spline interpolation, using the specified arguments.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<T, U>&& Internal::IsCompatible<T, V>&& Internal::IsCompatible<T, W>
    inline T Hermite( const T& firstPosition, const U& firstTangent, const V& secondPosition, const W& secondTangent, typename T::value_type t ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename V::Simd;
        return Math::Hermite( Simd( Traits::Load( firstPosition.values ) ), Simd( Traits::Load( firstTangent.values ) ), Simd( Traits::Load( secondPosition.values ) ), Simd( Traits::Load( secondTangent.values ) ), t );
    }



    // AllTrue

    /// <summary>
    /// Returns true if all the elements of the argument have all their bits set to 1 
    /// </summary>
    template<Internal::SimdType T>
    inline bool AllTrue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllTrue( v.simd );
    }
    /// <summary>
    /// Returns true if all the elements of the argument have all their bits set to 1 
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT AllTrue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllTrue( Traits::Load( v.values ) );
    }

    // AnyTrue

    /// <summary>
    /// Returns true if any of the elements of the argument have all their bits set to 1 
    /// </summary>
    template<Internal::SimdType T>
    inline bool AnyTrue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllTrue( v.simd );
    }
    /// <summary>
    /// Returns true if any of the elements of the argument have all their bits set to 1 
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT AnyTrue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyTrue( Traits::Load( v.values ) );
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
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Less( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Less( v1.simd, v2.simd );
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
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Less( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Less( v1.simd, Traits::Load( v2.values ) );
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
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline typename T::Simd Less( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Less( Traits::Load( v1.values ), v2.simd );
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
    template<Internal::TupleType U, Internal::TupleType T>
        requires Internal::IsCompatible<T, U>
    inline typename T::Simd Less( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Less( Traits::Load( v1.values ), Traits::Load( v2.values ) );
    }

    /// <summary>
    /// Determines whether the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// If an element of v1 is less than value, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<Internal::SimdType T, typename U>
        requires IsArithmetic<U>
    inline T Less( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Less( v1.simd, Traits::Fill<Traits::Size>( value ) );
    }

    /// <summary>
    /// Determines whether the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// If an element of v1 is less than value, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<Internal::TupleType T, typename U>
        requires IsArithmetic<U>
    inline T Less( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Less( Traits::Load( v1.values ), Traits::Fill<Traits::Size>( value ) );
    }

    /// <summary>
    /// Determines whether value is less than the elements of v2.
    /// </summary>
    /// <returns>
    /// If value is less than an element of v2, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<typename T, Internal::SimdType U>
        requires IsArithmetic<T>
    inline U Less( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Less( Traits::Fill<Traits::Size>( value ), v2.simd );
    }

    /// <summary>
    /// Determines whether value is less than the elements of v2.
    /// </summary>
    /// <returns>
    /// If value is less than an element of v2, the corresponding element 
    /// in the result will be set to 0xFFFFFFFF, otherwise the corresponding 
    /// element in the result will be set to 0.
    /// </returns>
    template<typename T, Internal::TupleType U>
        requires IsArithmetic<T>
    inline U Less( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Less( Traits::Fill<Traits::Size>( value ), Traits::Load( v2.values ) );
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
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline bool AllLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( v1.simd, v2.simd );
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
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline bool AllLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( v1.simd, Traits::Load( v2.values ) );
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
    template<Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline bool AllLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( Traits::Load( v1.values ), v2.simd );
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
    template<Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline bool AllLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( Traits::Load( v1.values ), Traits::Load( v2.values ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// true if all the elements of v1 is less than value, otherwise false.
    /// </returns>
    template<Internal::SimdType T, typename U>
        requires IsArithmetic<U>
    inline bool AllLess( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( v1.simd, Traits::Fill<Traits::Size>( value ) );
    }

    /// <summary>
    /// Determines whether all the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// true if all the elements of v1 is less than value, otherwise false.
    /// </returns>
    template<Internal::TupleType T, typename U>
        requires IsArithmetic<U>
    inline bool AllLess( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( Traits::Load( v1.values ), Traits::Fill<Traits::Size>( value ) );
    }

    /// <summary>
    /// Determines whether value is less than all the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is less than all the elements of v2, otherwise false.
    /// </returns>
    template< typename T, Internal::SimdType U>
        requires IsArithmetic<T>
    inline bool AllLess( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( Traits::Fill<Traits::Size>( value ), v2.simd );
    }

    /// <summary>
    /// Determines whether value is less than all the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is less than all the elements of v2, otherwise false.
    /// </returns>
    template< typename T, Internal::TupleType U>
        requires IsArithmetic<T>
    inline bool AllLess( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AllLess( Traits::Fill<Traits::Size>( value ), Traits::Load( v2.values ) );
    }


    // AnyLess

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
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline bool AnyLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( v1.simd, v2.simd );
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
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline bool AnyLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( v1.simd, Traits::Load( v2.values ) );
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
    template<Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline bool AnyLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( Traits::Load( v1.values ), v2.simd );
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
    template<Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline bool AnyLess( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( Traits::Load( v1.values ), Traits::Load( v2.values ) );
    }

    /// <summary>
    /// Determines whether any of the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// true if any of the elements of v1 is less than value, otherwise false.
    /// </returns>
    template<Internal::SimdType T, typename U>
        requires IsArithmetic<U>
    inline bool AnyLess( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( v1.simd, Traits::Fill<Traits::Size>( value ) );
    }

    /// <summary>
    /// Determines whether any of the elements of v1 are less than value.
    /// </summary>
    /// <returns>
    /// true if any of the elements of v1 is less than value, otherwise false.
    /// </returns>
    template<Internal::TupleType T, typename U>
        requires IsArithmetic<U>
    inline bool AnyLess( const T& v1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( Traits::Load( v1.values ), Traits::Fill<Traits::Size>( value ) );
    }

    /// <summary>
    /// Determines whether value is less than any of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is less than any of the elements of v2, otherwise false.
    /// </returns>
    template< typename T, Internal::SimdType U>
        requires IsArithmetic<T>
    inline bool AnyLess( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( Traits::Fill<Traits::Size>( value ), v2.simd );
    }

    /// <summary>
    /// Determines whether value is less than any of the elements of v2.
    /// </summary>
    /// <returns>
    /// true value is less than any of the elements of v2, otherwise false.
    /// </returns>
    template< typename T, Internal::TupleType U>
        requires IsArithmetic<T>
    inline bool AnyLess( T value, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::AnyLess( Traits::Fill<Traits::Size>( value ), Traits::Load( v2.values ) );
    }


    // Dot

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot( v1.simd, v2.simd );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot( v1.simd, Traits::Load( v2.values ) );
    }
    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline typename T::Simd Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot( Traits::Load( v1.values ), v2.simd );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<int mask, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot<mask>( v1.simd, v2.simd );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<int mask, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot<mask>( v1.simd, Traits::Load( v2.values.data( ) ) );
    }
    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<int mask, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline typename T::Simd Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot<mask>( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<int mask, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline typename T::Simd Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot<mask>( Traits::Load( v1.values ), Traits::Load( v2.values ) );
    }

    // ScalarDot

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Dot(v1,v2).simd );
    }

    template<Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Dot( v1, v2 ).simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Dot( v1, v2 ).simd );
    }

    template<Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
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
            return v1.x* v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
        }
    }

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill<Traits::Size>( ScalarDot( v1, v2 ) );
    }

    

    // AbsDot

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T AbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Math::Dot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T AbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Math::Dot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T AbsDot( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Math::Dot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline typename T::Simd AbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Math::Dot( v1, v2 ).simd );
    }

    // ScalarAbsDot

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarAbsDot( const T& v1, const U& v2 ) noexcept
    {
        return Math::Abs( ScalarDot( v1, v2 ) );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarAbsDot( const T& v1, const U& v2 ) noexcept
    {
        return Math::Abs( ScalarDot( v1, v2 ) );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarAbsDot( const U& v1, const T& v2 ) noexcept
    {
        return Math::Abs( ScalarDot( v1, v2 ) );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarAbsDot( const T& v1, const U& v2 ) noexcept
    {
        return Math::Abs( ScalarDot( v1, v2 ) );
    }



    // Cross

    /// <summary>
    /// Calculates the cross product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Cross( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cross( v1.simd, v2.simd );
    }

    /// <summary>
    /// Calculates the cross product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Cross( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cross( v1.simd, Traits::Load( v2.values.data( ) ) );
    }
    /// <summary>
    /// Calculates the cross product between v1 and v2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Cross( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cross( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    /// <summary>
    /// Calculates the cross product between v1 and v2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Cross( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cross( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
    }


    // LengthSquared


    /// <summary>
    /// Calculates the squared length of v.
    /// </summary>
    template<Internal::SimdType T>
    inline T LengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HSum( Traits::Mul( v.simd, v.simd ) );
    }
    /// <summary>
    /// Calculates the squared length of v.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT LengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Math::LengthSquared( typename T::Simd(Traits::Load( v.values )) );
    }


    // ScalarLengthSquared

    /// <summary>
    /// Calculates the squared length of v.
    /// </summary>
    template<Internal::SimdType T>
    inline auto ScalarLengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::LengthSquared( v ).simd );
    }

    /// <summary>
    /// Calculates the squared length of v.
    /// </summary>
    template<Internal::TupleType T>
    inline auto ScalarLengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::LengthSquared( v ).simd );
    }

    // Length

    /// <summary>
    /// Calculates the length of v.
    /// </summary>
    template<Internal::SimdType T>
    inline T Length( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( Math::LengthSquared( v ).simd );
    }
    /// <summary>
    /// Calculates the length of v.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Length( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( Math::LengthSquared( v ).simd );
    }

    // ScalarLength

    /// <summary>
    /// Calculates the length of v.
    /// </summary>
    template<Internal::SimdType T>
    inline auto ScalarLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Length( v ).simd );
    }
    /// <summary>
    /// Calculates the length of v.
    /// </summary>
    template<Internal::TupleType T>
    inline auto ScalarLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::Length( v ).simd );
    }


    // Normalize

    /// <summary>
    /// Normalizes v.
    /// </summary>
    template<Internal::SimdType T>
    inline T Normalize( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return v / Length( v );
    }
    /// <summary>
    /// Normalizes v.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Normalize( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Normalize( Simd(Traits::Load( v.values )) );
    }

    // ReciprocalLength

    /// <summary>
    /// Calculates the reciprocal length of v.
    /// </summary>
    template<Internal::SimdType T>
    inline T ReciprocalLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        auto length = Length( v );
        return T( Traits::Div( Traits::Fill<Traits::Size>( static_cast< Type >(1.) ), length.simd ) );
    }
    /// <summary>
    /// Calculates the reciprocal length of v.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ReciprocalLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return ReciprocalLength( Simd(Traits::Load( v.values )) );
    }

    // ScalarReciprocalLength

    /// <summary>
    /// Calculates the squared length of v.
    /// </summary>
    template<Internal::SimdType T>
    inline auto ScalarReciprocalLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::ReciprocalLength( v ).simd );
    }

    /// <summary>
    /// Calculates the squared length of v.
    /// </summary>
    template<Internal::TupleType T>
    inline auto ScalarReciprocalLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Math::ReciprocalLength( v ).simd );
    }

    // DistanceSquared

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T DistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( p1.simd, p2.simd );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T DistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( p1.simd, Traits::Load( p2.values.data( ) ) );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T DistanceSquared( const U& p1, const T& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( Traits::Load( p1.values.data( ) ), p2.simd );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT DistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( Traits::Load( p1.values.data( ) ), Traits::Load( p2.values.data( ) ) );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    // ScalarDistanceSquared

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarDistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( DistanceSquared(p1, p2).simd );
    }

    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarDistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( DistanceSquared( p1, p2 ).simd );
    }
    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarDistanceSquared( const U& p1, const T& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( DistanceSquared( p1, p2 ).simd );
    }
    /// <summary>
    /// Calculates the squared distance between p1 and p2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarDistanceSquared( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( DistanceSquared( p1, p2 ).simd );
    }

    // Distance

    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Distance( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }

    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Distance( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }

    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Distance( const U& p1, const T& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }

    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Distance( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }

    // ScalarDistance

    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarDistance( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Distance( p1, p2 ).simd );
    }

    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarDistance( const T& p1, const U& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Distance( p1, p2 ).simd );
    }
    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarDistance( const U& p1, const T& p2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Distance( p1, p2 ).simd );
    }
    /// <summary>
    /// Calculates the distance between p1 and p2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T> && Internal::IsCompatible<S, U> && Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        auto v34 = v3 * v4;
        return FMA( v1, v2, -v34 );
        /*
        auto v34 = v3 * v4;
        auto differenceOfProducts = FMA( v1, v2, -v34 );
        auto error = FMA( -v3, v4, v34 );
        return differenceOfProducts + error;
        */
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename V::Simd;
        return DifferenceOfProducts( v1, v2, v3, Simd( Traits::Load( v4.values) ) );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename U::Simd;
        return DifferenceOfProducts( v1, v2, Simd( Traits::Load( v3.values ) ), v4  );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename U::Simd;
        return DifferenceOfProducts( v1, v2, Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return DifferenceOfProducts( v1, Simd( Traits::Load( v2.values ) ), v3, v4 );
    }
    
    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return DifferenceOfProducts( v1, Simd( Traits::Load( v2.values ) ), v3, Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return DifferenceOfProducts( v1, Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), v4 );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return DifferenceOfProducts( v1, Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }
    //
    
    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), v2, v3, Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), v2, Simd( Traits::Load( v3.values ) ), v4 );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), v2, Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), v3, v4 );
    }
    
    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), v3, Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline V DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), v4 );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline typename S::Simd DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd(Traits::Load( v1.values )), Simd( Traits::Load( v2.values )), Simd( Traits::Load( v3.values )), Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<typename S, Internal::SimdType T, typename U, Internal::SimdType V>
        requires Internal::IsCompatible<T,V> && IsArithmetic<S> && IsArithmetic<U>
    inline T DifferenceOfProducts( S v1, const T& v2, U v3, const V& v4 ) noexcept
    {
        using Traits = typename T::Traits;
        using ValueType = typename Traits::Type;
        
        auto v34 = static_cast< ValueType >(v3) * v4;
        return FMA( static_cast< ValueType >( v1 ), v2, -v34 );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<typename S, Internal::SimdType T, typename U, Internal::TupleType V>
        requires Internal::IsCompatible<T, V>&& IsArithmetic<S>&& IsArithmetic<U>
    inline T DifferenceOfProducts( S v1, const T& v2, U v3, const V& v4 ) noexcept
    {
        using Traits = typename T::Traits;
        using ValueType = typename Traits::Type;

        auto v34 = static_cast< ValueType >( v3 ) * v4;
        return FMA( static_cast< ValueType >( v1 ), v2, -v34 );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<typename S, Internal::TupleType T, typename U, Internal::SimdType V>
        requires Internal::IsCompatible<T, V>&& IsArithmetic<S>&& IsArithmetic<U>
    inline typename T::Simd DifferenceOfProducts( S v1, const T& v2, U v3, const V& v4 ) noexcept
    {
        using Traits = typename T::Traits;
        using ValueType = typename Traits::Type;

        auto v34 = static_cast< ValueType >( v3 ) * v4;
        return FMA( static_cast< ValueType >( v1 ), v2, -v34 );
    }

    /// <summary>
    /// Calculates the difference between the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<typename S, Internal::TupleType T, typename U, Internal::TupleType V>
        requires Internal::IsCompatible<T, V>&& IsArithmetic<S>&& IsArithmetic<U>
    inline typename T::Simd DifferenceOfProducts( S v1, const T& v2, U v3, const V& v4 ) noexcept
    {
        using Traits = typename T::Traits;
        using ValueType = typename Traits::Type;

        auto v34 = static_cast< ValueType >( v3 ) * v4;
        return FMA( static_cast< ValueType >( v1 ), v2, -v34 );
    }


    // SumOfProducts

    
    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        auto v34 = v3 * v4;
        return FMA( v1, v2, v34 );
        /*
        auto v34 = v3 * v4;
        auto sumOfProducts = FMA( v1, v2, v34 );
        auto error = FMA( v3, v4, -v34 );
        return sumOfProducts + error;
        */
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename V::Simd;
        return SumOfProducts( v1, v2, v3, Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename U::Simd;
        return SumOfProducts( v1, v2, Simd( Traits::Load( v3.values ) ), v4 );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename U::Simd;
        return SumOfProducts( v1, v2, Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return SumOfProducts( v1, Simd( Traits::Load( v2.values ) ), v3, v4 );
    }
    
    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return SumOfProducts( v1, Simd( Traits::Load( v2.values ) ), v3, Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return SumOfProducts( v1, Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), v4 );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return SumOfProducts( v1, Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }
    //
    
    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), v2, v3, Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), v2, Simd( Traits::Load( v3.values ) ), v4 );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), v2, Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), v3, v4 );
    }
    
    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), v3, Simd( Traits::Load( v4.values ) ) );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline V SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), v4 );
    }

    /// <summary>
    /// Calculates the sum of the product of the first and the second argument, 
    /// and the product of the third and fourth argument.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline typename S::Simd SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    // BaryCentric

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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;

        auto rmm1 = Traits::Sub( p2.simd, p1.simd );
        auto rmm2 = Traits::Sub( p3.simd, p1.simd );
        rmm1 = Traits::FMAdd( rmm1.simd, f.simd, p1.simd );
        return Simd(Traits::FMAdd( rmm2.simd, g.simd, rmm1.simd ));
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, p2, p3, f, Simd( g ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, p2, p3, Simd( f ), g );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, p2, p3, Simd( f ), Simd( g ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, p2, Simd( p3 ), f, g );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, p2, Simd( p3 ), f, Simd( g ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, p2, Simd( p3 ), Simd( f ), g );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, p2, Simd( p3 ), Simd( f ), Simd( g ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, Simd( p2 ), p3, f, g );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, Simd( p2 ), p3, f, Simd( g ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, Simd( p2 ), p3, Simd( f ), g );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, Simd( p2 ), p3, Simd( f ), Simd( g ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, Simd( p2 ), Simd( p3 ), f, g );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, Simd( p2 ), Simd( p3 ), f, Simd( g ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, Simd( p2 ), Simd( p3 ), Simd( f ), g );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return BaryCentric( p1, Simd( p2 ), Simd( p3 ), Simd( f ), Simd( g ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), p2, p3, f, g );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), p2, p3, f, Simd( g ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), p2, p3, Simd( f ), g );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), p2, p3, Simd( f ), Simd( g ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), p2, Simd( p3 ), f, g );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), p2, Simd( p3 ), f, Simd( g ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), p2, Simd( p3 ), Simd( f ), g );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), p2, Simd( p3 ), Simd( f ), Simd( g ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), Simd( p2 ), p3, f, g );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), Simd( p2 ), p3, f, Simd( g ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), Simd( p2 ), p3, Simd( f ), g );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept   
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), Simd( p2 ), p3, Simd( f ), Simd( g ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), Simd( p2 ), Simd( p3 ), f, g );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), Simd( p2 ), Simd( p3 ), f, Simd( g ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), Simd( p2 ), Simd( p3 ), Simd( f ), g );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V& f, const W& g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return BaryCentric( Simd( p1 ), Simd( p2 ), Simd( p3 ), Simd( f ), Simd( g ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, typename V, typename W>
        requires Internal::IsCompatible<S, T> && Internal::IsCompatible<S, U> && IsFloatingPoint<V> && IsFloatingPoint<W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return BaryCentric( p1, p2, p3, Simd(Traits::Fill<Traits::Size>( f )), Simd(Traits::Fill<Traits::Size>( g )) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, typename V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& IsFloatingPoint<V>&& IsFloatingPoint<W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return BaryCentric( p1, p2, Simd( p3 ), Simd( Traits::Fill<Traits::Size>( f ) ), Simd( Traits::Fill<Traits::Size>( g ) ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, typename V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& IsFloatingPoint<V>&& IsFloatingPoint<W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return BaryCentric( p1, Simd( p2 ), p3, Simd( Traits::Fill<Traits::Size>( f ) ), Simd( Traits::Fill<Traits::Size>( g ) ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, typename V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& IsFloatingPoint<V>&& IsFloatingPoint<W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return BaryCentric( p1, Simd( p2 ), Simd( p3 ), Simd( Traits::Fill<Traits::Size>( f ) ), Simd( Traits::Fill<Traits::Size>( g ) ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, typename V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& IsFloatingPoint<V>&& IsFloatingPoint<W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return BaryCentric( Simd( p1 ), p2, p3, Simd( Traits::Fill<Traits::Size>( f ) ), Simd( Traits::Fill<Traits::Size>( g ) ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, typename V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& IsFloatingPoint<V>&& IsFloatingPoint<W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return BaryCentric( Simd( p1 ), p2, Simd( p3 ), Simd( Traits::Fill<Traits::Size>( f ) ), Simd( Traits::Fill<Traits::Size>( g ) ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, typename V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& IsFloatingPoint<V>&& IsFloatingPoint<W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return BaryCentric( Simd( p1 ), Simd( p2 ), p3, Simd( Traits::Fill<Traits::Size>( f ) ), Simd( Traits::Fill<Traits::Size>( g ) ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& IsFloatingPoint<V>&& IsFloatingPoint<W>
    inline typename S::Simd BaryCentric( const S& p1, const T& p2, const U& p3, const V f, const W g ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;

        return BaryCentric( Simd( p1 ), Simd( p2 ), Simd( p3 ), Simd( Traits::Fill<Traits::Size>( f ) ), Simd( Traits::Fill<Traits::Size>( g ) ) );
    }


    // CatmullRom

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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, p3, p4, Simd( t ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, p3, Simd( p4 ), t );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, p3, Simd( p4 ), Simd( t ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, Simd( p3 ), p4, t );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, Simd( p3 ), p4, Simd( t ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, Simd( p3 ), Simd( p4 ), Simd( t ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), p3, p4, t );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), p3, p4, Simd( t ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), p3, Simd( p4 ), t );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), p3, Simd( p4 ), Simd( t ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), Simd( p3 ), p4, t );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), Simd( p3 ), p4, Simd( t ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), Simd( p3 ), Simd( p4 ), Simd( t ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, p3, p4, t );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, p3, p4, Simd( t ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, p3, Simd( p4 ), t );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, p3, Simd( p4 ), Simd( t ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, Simd( p3 ), p4, t );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, Simd( p3 ), p4, Simd( t ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, Simd( p3 ), Simd( p4 ), Simd( t ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), p3, p4, t );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), p3, p4, Simd( t ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), p3, Simd( p4 ), t );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), p3, Simd( p4 ), Simd( t ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::SimdType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), Simd( p3 ), p4, t );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), Simd( p3 ), p4, Simd( t ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, Internal::TupleType W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& Internal::IsCompatible<S, W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W& t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), Simd( p3 ), Simd( p4 ), Simd( t ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using FloatT = typename Traits::Type;
        using Simd = S;

        FloatT t2 = t * t;
        FloatT t3 = t * t2;

        auto P1 = Traits::Fill( ( -t3 + static_cast<FloatT>(2.0) * t2 - t ) * static_cast< FloatT >( 0.5 ) );
        auto P2 = Traits::Fill( ( static_cast< FloatT >( 3.0 ) * t3 - static_cast< FloatT >( 5.0 ) * t2 + static_cast< FloatT >( 2.0 ) ) * static_cast< FloatT >( 0.5 ) );
        auto P3 = Traits::Fill( ( static_cast< FloatT >( -3.0 ) * t3 + static_cast< FloatT >( 4.0 ) * t2 + t ) * static_cast< FloatT >( 0.5 ) );
        auto P4 = Traits::Fill( ( t3 - t2 ) * static_cast< FloatT >( 0.5 ) );

        P2 = Traits::Mul( p2.simd, P2 );
        P1 = Traits::FMAdd( p1.simd, P1, P2 );
        P4 = Traits::Mul( p4.simd, P4 );
        P3 = Traits::FMAdd( p3.simd, P3, P4 );
        return Simd( Traits::Trim( Traits::Add( P1, P3 ) ));
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, p3, Simd( p4 ), t );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, Simd( p3 ), p4, t );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, p2, Simd( p3 ), Simd( p4 ), t );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), p3, p4, t );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), p3, Simd( p4 ), t );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), Simd( p3 ), p4, t );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline S CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = S;
        return CatmullRom( p1, Simd( p2 ), Simd( p3 ), Simd( p4 ), t );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, p3, p4, t );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, p3, Simd( p4 ), t );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, Simd( p3 ), p4, t );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), p2, Simd( p3 ), Simd( p4 ), t );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), p3, p4, t );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), p3, Simd( p4 ), t );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), Simd( p3 ), p4, t );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V, typename W>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>&& IsFloatingPoint<W>
    inline typename S::Simd CatmullRom( const S& p1, const T& p2, const U& p3, const V& p4, const W t ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return CatmullRom( Simd( p1 ), Simd( p2 ), Simd( p3 ), Simd( p4 ), t );
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
    template<Internal::SimdType T, typename ResultT = typename T::value_type >
    inline ResultT MinComponentValue( const T& v ) noexcept
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
    template<Internal::TupleType T, typename ResultT = typename T::value_type>
    constexpr inline ResultT MinComponentValue( const T& v ) noexcept
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
    template<Internal::SimdType T, typename ResultT = typename T::value_type >
    inline ResultT MaxComponentValue( const T& v ) noexcept
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
    template<Internal::TupleType T, typename ResultT = typename T::value_type>
    constexpr inline ResultT MaxComponentValue( const T& v ) noexcept
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
    template<Internal::TupleType T>
    constexpr inline size_t MaxComponentIndex( const T& v ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return Internal::MaxIndex( v.values, 0, 1 );
        }
        else if constexpr ( T::Size == 3 )
        {
            return Internal::MaxIndex( v.values, Internal::MaxIndex( v.values, 0, 1 ), 2);
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
    template<Internal::SimdType T, typename ResultT = typename T::value_type >
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
    template<Internal::TupleType T>
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
    template<Internal::SimdType T, typename ResultT = typename T::value_type >
    constexpr inline size_t MinComponentIndex( const T& v ) noexcept
    {
        using TupleT = T::TupleType;
        TupleT tmp( v );
        return MinComponentIndex( tmp );
    }


    // AddAdjustUp

    template<Internal::SimdType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline S AddAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Add( a.simd, b.simd ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline S AddAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Add( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline T AddAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Add( Traits::Load( a.values ), b.simd ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd AddAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Add( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }


    // AddAdjustDown

    template<Internal::SimdType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline S AddAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Add( a.simd, b.simd ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline S AddAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Add( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline T AddAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Add( Traits::Load( a.values ), b.simd ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd AddAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Add( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // SubAdjustUp

    template<Internal::SimdType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline S SubAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sub( a.simd, b.simd ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline S SubAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sub( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline T SubAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sub( Traits::Load( a.values ), b.simd ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd SubAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sub( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // SubAdjustDown

    template<Internal::SimdType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline S SubAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sub( a.simd, b.simd ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline S SubAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sub( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline T SubAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sub( Traits::Load( a.values ), b.simd ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd SubAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sub( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // MulAdjustUp

    template<Internal::SimdType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline S MulAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Mul( a.simd, b.simd ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline S MulAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Mul( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline T MulAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Mul( Traits::Load( a.values ), b.simd ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd MulAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Mul( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // MulAdjustDown

    template<Internal::SimdType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline S MulAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Mul( a.simd, b.simd ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline S MulAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Mul( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline T MulAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Mul( Traits::Load( a.values ), b.simd ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd MulAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Mul( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // DivAdjustUp

    template<Internal::SimdType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline S DivAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Div( a.simd, b.simd ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline S DivAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Div( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline T DivAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Div( Traits::Load( a.values ), b.simd ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd DivAdjustUp( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Div( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    // DivAdjustDown

    template<Internal::SimdType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline S DivAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Div( a.simd, b.simd ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline S DivAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Div( a.simd, Traits::Load( b.values ) ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T >
        requires Internal::IsCompatible<S, T>
    inline T DivAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Div( Traits::Load( a.values ), b.simd ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T >
        requires Internal::IsCompatible<S, T>
    inline typename S::Simd DivAdjustDown( const S& a, const T& b ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Div( Traits::Load( a.values ), Traits::Load( b.values ) ) ) );
    }

    
    // SqrtAdjustUp

    template<Internal::SimdType S >
    inline S SqrtAdjustUp( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sqrt( v.simd ) ) );
    }
    template<Internal::TupleType S >
    inline typename S::Simd SqrtAdjustUp( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextUp( Traits::Sqrt( Traits::Load( v.values ) ) ) );
    }

    // SqrtAdjustDown

    template<Internal::SimdType S >
    inline S SqrtAdjustDown( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sqrt( v.simd ) ) );
    }
    template<Internal::TupleType S >
    inline typename S::Simd SqrtAdjustDown( const S& v ) noexcept
    {
        using Traits = typename S::Traits;
        return Traits::Trim( Traits::NextDown( Traits::Sqrt( Traits::Load( v.values ) ) ) );
    }

    // FMAAdjustUp

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustUp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustUp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMAAdjustUp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMAAdjustUp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustUp( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustUp( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMAAdjustUp( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMAAdjustUp( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FMAAdjustUp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextUp( Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    // FMAAdjustDown

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustDown( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustDown( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMAAdjustDown( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMAAdjustDown( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustDown( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustDown( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMAAdjustDown( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMAAdjustDown( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    //

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd ) ) );
    }

    /// <summary>
    /// Multiplies the corresponding elements of a and b, adding the result to the corresponding element of c.
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FMAAdjustDown( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trim( Traits::NextDown( Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) ) ) );
    }

    
    
    template<>
    class Vector<float, 2> : public Tuple2<Vector<float, 2>, float>, public Internal::VectorBase
    {
    public:
        using Base = Tuple2<Vector<float, 2>, float>;
        using Base::Base;
        
        using Traits = Base::Traits;
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
    class Vector<float, 3> : public Tuple3<Vector<float, 3>,float>, public Internal::VectorBase
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
    class Vector<float, 4> : public Tuple4<Vector<float, 4>,float>, public Internal::VectorBase
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
        requires Internal::IsCompatible<S, T>
    inline S AngleBetween(const S& v1, const T& v2 ) noexcept
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
        requires Internal::IsCompatible<S, T>
    inline S AngleBetweenNormals( const S& v1, const T& v2 ) noexcept
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


    // Vector2* Definitions
    using Vector2f = Vector<float,2>;
    using Vector2i = Vector<int,2>;

    // Vector3* Definitions
    using Vector3f = Vector<float,3>;
    using Vector3i = Vector<int, 3>;

    // Vector4* Definitions
    using Vector4f = Vector<float, 4>;
    using Vector4i = Vector<int, 4>;

    
    template<typename T, size_t N>
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
        { };

        struct NormalBase
        { };
    }

    template<typename T>
    concept PointType = std::is_base_of_v<Internal::PointBase, T>;

    template<typename T>
    concept PointSimdType = std::is_base_of_v<Internal::PointBase, typename T::TupleType>;

    template<typename T>
    concept NormalType = std::is_base_of_v<Internal::NormalBase, T>;

    template<typename T>
    concept NormalSimdType = std::is_base_of_v<Internal::NormalBase, typename T::TupleType>;


    class Point2i : public Tuple2<Point2i, Int32>, public Internal::PointBase
    {
    public:
        using Base = Tuple2<Point2i, Int32>;
        using Base::Base;
    };

    class Point3i : public Tuple3<Point3i, Int32>, public Internal::PointBase
    {
    public:
        using Base = Tuple3<Point3i, Int32>;
        using Base::Base;
    };

    class Point2f : public Tuple2<Point2f, float>, public Internal::PointBase
    {
    public:
        using Base = Tuple2<Point2f, float>;
        using Base::Base;
    };


    // Copied from pbrt-v4 https://github.com/mmp/pbrt-v4
    // https://www.iquilezles.org/www/articles/ibilinear/ibilinear.htm,
    // with a fix for perfect quads
    inline Point2f InvertBilinear( const Point2f& p, const std::array<Point2f,4>& vert )
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



    class Point3f : public Tuple3<Point3f, float>, public Internal::PointBase
    {
    public:
        using Base = Tuple3<Point3f, float>;
        using Base::Base;
    };



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
        requires Internal::IsCompatible<S,T> && Internal::IsCompatible<S, U>
    inline S LinePointDistance(const S& linePoint1, const T& linePoint2, const U& point ) noexcept
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



    class Normal3f : public Tuple3<Normal3f, float>, public Internal::NormalBase
    {
    public:
        using Base = Tuple3<Normal3f, float>;
        using Base::Base;
    };


    



    namespace Internal
    {
        struct QuaternionSimdBase
        { };
        struct QuaternionBase
        { };

        template<typename T>
        concept QuaternionSimdType = std::is_base_of_v<QuaternionSimdBase, T> && IsFloatingPoint<typename T::value_type>;

        template<typename T>
        concept QuaternionType = std::is_base_of_v<QuaternionBase, T> && IsFloatingPoint<typename T::value_type>;

        template<typename T1, typename T2>
        constexpr bool IsCompatibleQuaternion =
            std::is_same_v<typename T1::Traits, typename T2::Traits>;

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

        using Matrix = SquareMatrix<ValueType, 4>;
        using MatrixSimd = typename Matrix::Simd;

        static constexpr size_type Size = 4;
        static constexpr bool Loaded = true;
        static constexpr bool Unloaded = false;

        using Traits = typename QuaternionType::Traits;
        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;

        SIMDType simd;

        QuaternionSimd() noexcept
            : simd(Traits::Zero())
        { }

        QuaternionSimd( const QuaternionSimd& other) noexcept
            : simd( other.simd )
        { }

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
        template<Internal::SimdType T>
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
        template<Internal::TupleType T>
        QuaternionSimd( const T& pitchYawRoll )
            : QuaternionSimd( pitchYawRoll.ToSimd() )
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
        { }

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
        static QuaternionSimd FromNormalizedAxisAndAngle( const VectorSimd& normalizedAxis, float angle ) noexcept
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
        static QuaternionSimd FromNormalizedAxisAndAngle( const Vector& normalizedAxis, float angle ) noexcept
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
        static QuaternionSimd FromAxisAndAngle( const VectorSimd& axis, float angle ) noexcept
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
        static QuaternionSimd FromAxisAndAngle( const Vector& axis, float angle ) noexcept
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
        static QuaternionSimd FromMatrix( const std::array<SIMDType,N>& matrix ) noexcept;

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
            return QuaternionSimd(Traits::Negate( simd ));
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
    };

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T">
    /// </typeparam>
    template<typename T>
        requires IsFloatingPoint<T>
    class Quaternion : public Internal::QuaternionBase
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 4;
        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;

        using Traits = Core::SIMD::Traits<ValueType, Size>;
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
        using MatrixSimd = typename Matrix::Simd;

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
        { }
        constexpr Quaternion( ValueType xv, ValueType yv, ValueType zv, ValueType wv ) noexcept
            : values( { xv, yv, zv, wv } )
        {
        }

        constexpr Quaternion( const ArrayType& a ) noexcept
            : values( a )
        {
        }

        constexpr Quaternion( const Vector& vv, ValueType wv ) noexcept
            : v( vv ), w( wv )
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
        static Simd FromNormalizedAxisAndAngle( const VectorSimd& normalizedAxis, float angle ) noexcept
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
        static Simd FromNormalizedAxisAndAngle( const Vector& normalizedAxis, float angle ) noexcept
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
        static Simd FromAxisAndAngle( const VectorSimd& axis, float angle ) noexcept
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
        static Simd FromAxisAndAngle( const Vector& axis, float angle ) noexcept
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
            return Traits::Equals(Traits::Load( values.data( ) ), other.simd );
        }

        bool operator != ( const Simd& other ) const noexcept
        {
            return Traits::Equals( Traits::Load( values.data( ) ), other.simd ) == false;
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
            return Simd(Traits::Negate( Traits::Load( values ) ));
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

    //static_assert( sizeof( Quaternion<float> ) == sizeof(std::array<float,4>));

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


    // Addition

    template<Internal::QuaternionSimdType T, Internal::QuaternionSimdType U>
        requires Internal::IsCompatibleQuaternion<T,U>
    T operator + ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return T(Traits::Add( q1.simd, q2.simd ));
    }
    template<Internal::QuaternionType T, Internal::QuaternionSimdType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    U operator + ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return U(Traits::Add( Traits::Load( q1.values ), q2.simd ));
    }
    template<Internal::QuaternionSimdType T, Internal::QuaternionType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    T operator + ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return T(Traits::Add( q1.simd, Traits::Load( q2.values ) ));
    }
    template<Internal::QuaternionType T, Internal::QuaternionType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    typename T::Simd operator + ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return typename T::Simd(Traits::Add( Traits::Load( q1.values ), Traits::Load( q2.values ) ));
    }


    // Scalar Addition

    template<Internal::QuaternionSimdType T, typename U>
        requires std::is_arithmetic_v<U>
    T operator + ( const T& q1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        return T( Traits::Add( q1.simd, Traits::Set( v, zero, zero, zero ) ) );
    }

    template<typename T, Internal::QuaternionSimdType U>
        requires std::is_arithmetic_v<T>
    U operator + ( const T& value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using FloatT = typename Traits::Type;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        return U( Traits::Add( Traits::Set( v, zero, zero, zero ), q2.simd ) );
    }

    template<Internal::QuaternionType T, typename U>
        requires std::is_arithmetic_v<U>
    typename T::Simd operator + ( const T& q1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        using Simd = typename T::Simd;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );

        return Simd( Traits::Add( Traits::Load( q1.values ), Traits::Set( v, zero, zero, zero ) ) );
    }
    template<typename T, Internal::QuaternionType U>
        requires std::is_arithmetic_v<T>
    typename U::Simd operator + ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using FloatT = typename Traits::Type;
        using Simd = typename U::Simd;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );

        return Simd( Traits::Add( Traits::Set( v, zero, zero, zero ), Traits::Load( q2.values ) ) );
    }


    // Subtraction

    template<Internal::QuaternionSimdType T, Internal::QuaternionSimdType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    T operator - ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return T(Traits::Sub( q1.simd, q2.simd ));
    }
    template<Internal::QuaternionType T, Internal::QuaternionSimdType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    U operator - ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return U(Traits::Sub( Traits::Load( q1.values ), q2.simd ));
    }
    template<Internal::QuaternionSimdType T, Internal::QuaternionType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    T operator - ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return T(Traits::Sub( q1.simd, Traits::Load( q2.values ) ));
    }
    template<Internal::QuaternionType T, Internal::QuaternionType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    typename T::Simd operator - ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return typename T::Simd(Traits::Sub( Traits::Load( q1.values.data( ) ), Traits::Load( q2.values ) ));
    }


    // Scalar Subtraction

    template<Internal::QuaternionSimdType T, typename U>
        requires std::is_arithmetic_v<U>
    T operator - ( const T& q1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        return T( Traits::Sub( q1.simd, Traits::Set( v, zero, zero, zero ) ) );
    }

    template<typename T, Internal::QuaternionSimdType U>
        requires std::is_arithmetic_v<T>
    U operator - ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using FloatT = typename Traits::Type;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        auto tmp = Traits::Sub( Traits::Set( v, zero, zero, zero ), q2.simd );
        return U( Traits::Permute<4, 5, 6, 3>( tmp, q2.simd ) );
    }

    template<Internal::QuaternionType T, typename U>
        requires std::is_arithmetic_v<U>
    typename T::Simd operator - ( const T& q1, const U value ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        using Simd = typename T::Simd;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );

        return Simd( Traits::Sub( Traits::Load( q1.values ), Traits::Set( v, zero, zero, zero ) ) );
    }
    template<typename T, Internal::QuaternionType U>
        requires std::is_arithmetic_v<T>
    typename U::Simd operator - ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using FloatT = typename Traits::Type;
        using Simd = typename U::Simd;
        auto v = static_cast< FloatT >( value );
        auto zero = static_cast< FloatT >( 0. );
        auto vals = Traits::Load( q2.values );
        auto tmp = Traits::Sub( Traits::Set( v, zero, zero, zero ), vals );

        return Simd( Traits::Permute<4, 5, 6, 3>( tmp, vals ) );
    }


    // Multiplication

    template<Internal::QuaternionSimdType T, Internal::QuaternionSimdType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    T operator * ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return T( Traits::QuaternionMultiply( q1.simd, q2.simd ));
    }
    template<Internal::QuaternionType T, Internal::QuaternionSimdType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    U operator *( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        return U( Traits::QuaternionMultiply( Traits::Load( q1.values )), q2.simd );
    }
    template<Internal::QuaternionSimdType T, Internal::QuaternionType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    T operator * ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        return T( Traits::QuaternionMultiply( q1.simd, Traits::Load( q2.values ) ));
    }
    template<Internal::QuaternionType T, Internal::QuaternionType U>
        requires Internal::IsCompatibleQuaternion<T, U>
    typename T::Simd operator * ( const T& q1, const U& q2 ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Simd( Traits::QuaternionMultiply( Traits::Load( q1.values ), Traits::Load( q2.values ) ));
    }


    // Scalar Multiplication

    template<typename T, Internal::QuaternionSimdType U>
        requires IsFloatingPoint<T>
    U operator * ( T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        return U(Traits::Mul( Traits::Fill( value ), q2.simd ));
    }
    template<Internal::QuaternionSimdType T, typename U>
        requires IsFloatingPoint<U>
    T operator * ( const T& q1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return T(Traits::Mul( q1.simd, Traits::Fill( value ) ));
    }

    template<typename T, Internal::QuaternionType U>
        requires IsFloatingPoint<T>
    typename U::Simd operator * ( T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        return typename U::Simd(Traits::Mul( Traits::Fill( value ), Traits::Load( q2.values ) ));
    }
    template<Internal::QuaternionType T, typename U>
        requires IsFloatingPoint<U>
    typename T::Simd operator * ( const T& q1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return typename T::Simd(Traits::Mul( Traits::Load( q1.values ), Traits::Fill( value ) ));
    }

    // Scalar Division


    template<Internal::QuaternionSimdType T, typename U>
        requires IsFloatingPoint<U>
    T operator / ( const T& q1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        return T( Traits::Div( q1.simd, Traits::Fill( value ) ) );
    }

    template<typename T, Internal::QuaternionSimdType U>
        requires IsFloatingPoint<T>
    U operator / ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        return U( Traits::Div( Traits::Fill( value ), q2.simd ) );
    }

    template<Internal::QuaternionType T, typename U>
        requires IsFloatingPoint<U>
    typename T::Simd operator / ( const T& q1, U value ) noexcept
    {
        using Traits = typename T::Traits;
        using Simd = typename T::Simd;
        return Simd(Traits::Div( Traits::Load( q1.values ), Traits::Fill( value ) ));
    }

    template<typename T, Internal::QuaternionType U>
        requires IsFloatingPoint<T>
    typename U::Simd operator / ( const T value, const U& q2 ) noexcept
    {
        using Traits = typename U::Traits;
        using Simd = typename U::Simd;
        return Simd( Traits::Div( Traits::Fill( value ), Traits::Load( q2.values ) ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T,4>::Simd Dot( const QuaternionSimd<Quaternion<T>>& q1, const QuaternionSimd<Quaternion<T>>& q2 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        return Traits::Dot( q1.simd, q2.simd );
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
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Dot( const Quaternion<T>& q1, const QuaternionSimd<Quaternion<T>>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Dot( Traits::Load( q1.values ), q2.simd );
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
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Dot( const QuaternionSimd<Quaternion<T>>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Dot( q1.simd, Traits::Load( q2.values ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Dot( const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Dot( Traits::Load( q1.values ), Traits::Load( q2.values ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarDot( const QuaternionSimd<Quaternion<T>>& q1, const QuaternionSimd<Quaternion<T>>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::First( Traits::Dot( q1.simd, q2.simd ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarDot( const Quaternion<T>& q1, const QuaternionSimd<Quaternion<T>>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::First( Traits::Dot( Traits::Load( q1.values ), q2.simd ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarDot( const QuaternionSimd<Quaternion<T>>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::First( Traits::Dot( q1.simd, Traits::Load( q2.values ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarDot( const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::First( Traits::Dot( Traits::Load( q1.values ), Traits::Load( q2.values ) ) );
    }
    

    // Length

    /// <summary>
    /// Calculates the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Length( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        return Traits::Sqrt( Traits::HSum( Traits::Mul( q1.simd, q1.simd ) ) );
    }

    /// <summary>
    /// Calculates the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Length( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        auto simd = Traits::Load( q1.values );
        return Traits::Sqrt( Traits::HSum( Traits::Mul( simd, simd ) ) );
    }

    // ScalarLength

    /// <summary>
    /// Calculates the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarLength( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        return Traits::First( Length( q1 ).simd );
    }

    /// <summary>
    /// Calculates the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarLength( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::First( Length( q1 ).simd );
    }

    // LengthSquared

    /// <summary>
    /// Calculates the square of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The square of the magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd LengthSquared( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        return Vector<T, 4>::Simd( Traits::HSum( Traits::Mul( q1.simd, q1.simd ) ) );
    }

    /// <summary>
    /// Calculates the square of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The square of the magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd LengthSquared( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        auto simd = Traits::Load( q1.values );
        return Vector<T, 4>::Simd( Traits::HSum( Traits::Mul( simd, simd ) ) );
    }

    // ScalarLengthSquared

    /// <summary>
    /// Calculates the square of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The square of the magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarLengthSquared( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        return Traits::First( Traits::HSum( Traits::Mul( q1.simd, q1.simd ) ) );
    }

    /// <summary>
    /// Calculates the square of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The square of the magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarLengthSquared( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        auto simd = Traits::Load( q1.values );
        return Traits::First( Traits::HSum( Traits::Mul( simd, simd ) ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd ReciprocalLength( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        using Type = typename Traits::Type;
        auto length = Length( q1 );
        return Vector<T, 4>::Simd( Traits::Div( Traits::Fill( static_cast< Type >( 1. ) ), length.simd ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd ReciprocalLength( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using Type = typename Traits::Type;
        auto length = Length( q1 );
        return Vector<T, 4>::Simd( Traits::Div( Traits::Fill( static_cast< Type >( 1. ) ), length.simd ) );
    }

    // ScalarReciprocalLength

    /// <summary>
    /// Calculates the reciprocal of the magnitude of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The reciprocal of the magnitude of the quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarReciprocalLength( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<Quaternion<T>>::Traits;
        using Type = typename Traits::Type;
        auto length = ScalarLength( q1 );
        return static_cast< Type >( 1. ) / length;
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
    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarReciprocalLength( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using Type = typename Traits::Type;
        auto length = ScalarLength( q1 );
        return static_cast< Type >( 1. ) / length;
    }


    // Conjugate

    /// <summary>
    /// Calculates the conjugate of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The conjugate of the quaternion
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Conjugate( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using SIMDType = typename Traits::SIMDType;
        constexpr SIMDType flipXYZ = { { -1.0f, -1.0f, -1.0f, 1.0f } };
        return QuaternionSimd<Quaternion<T>>( Traits::Mul( q1.simd, flipXYZ ) );
    }

    /// <summary>
    /// Calculates the conjugate of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The conjugate of the quaternion
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Conjugate( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using SIMDType = typename Traits::SIMDType;
        constexpr SIMDType flipXYZ = { { -1.0f, -1.0f, -1.0f, 1.0f } };
        return QuaternionSimd<Quaternion<T>>( Traits::Mul( Traits::Load( q1.values ), flipXYZ ) );
    }

    // Normalize

    /// <summary>
    /// Normalizes a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The normalized quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Normalize( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        auto v = Length( q1 );
        return QuaternionSimd<Quaternion<T>>(Traits::Div( q1.simd, v.simd ));
    }

    /// <summary>
    /// Normalizes a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The normalized quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Normalize( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using Simd = QuaternionSimd<Quaternion<T>>;
        auto simd = Simd( Traits::Load( q1.values ) );
        return Normalize( simd );
    }


    /// <summary>
    /// Calculates the inverse of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The inverse quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Inverse( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using FloatT = typename Traits::Type;
        using SIMDType = typename Traits::SIMDType;
        using Simd = QuaternionSimd<Quaternion<T>>;
        constexpr SIMDType epsilon = { {static_cast< FloatT >( 1.192092896e-7 ),static_cast< FloatT >( 1.192092896e-7 ),static_cast< FloatT >( 1.192092896e-7 ),static_cast< FloatT >( 1.192092896e-7 )} };
        constexpr SIMDType zero = { {static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. ),static_cast< FloatT >( 0. )} };

        auto l = LengthSquared( q1 );
        auto conjugate = Conjugate( q1 );

        auto selectZero = Traits::LessOrEqual( l.simd, epsilon );

        auto result = Traits::Div( conjugate.simd, l.simd );

        return Simd( Traits::Select( result, zero, selectZero ) );
    }

    /// <summary>
    /// Calculates the inverse of a quaternion.
    /// </summary>
    /// <param name="q1">
    /// The quaternion.
    /// </param>
    /// <returns>
    /// The inverse quaternion.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Inverse( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using Simd = QuaternionSimd<Quaternion<T>>;
        return Inverse( Simd( q1 ) );
    }

    /// <summary>
    /// Calculates the natural logarithm of a unit quaternion.
    /// </summary>
    /// <param name="q1">
    /// The unit quaternion.
    /// </param>
    /// <returns>
    /// The natural logarithm of q1.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Log( const QuaternionSimd<Quaternion<T>>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using FloatT = typename Traits::Type;
        using SIMDType = typename Traits::SIMDType;
        using Simd = QuaternionSimd<Quaternion<T>>;
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

    /// <summary>
    /// Calculates the natural logarithm of a unit quaternion.
    /// </summary>
    /// <param name="q1">
    /// The unit quaternion.
    /// </param>
    /// <returns>
    /// The natural logarithm of q1.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Log( const Quaternion<T>& q1 ) noexcept
    {
        using Simd = QuaternionSimd<Quaternion<T>>;
        return Log( Simd( q1 ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const QuaternionSimd<Quaternion<T>>& q1, const QuaternionSimd<Quaternion<T>>& q2, const typename Vector<T, 4>::Simd& t ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using Simd = QuaternionSimd<Quaternion<T>>;
        return Simd( Traits::Slerp( q1.simd, q2.simd, t.simd ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const QuaternionSimd<Quaternion<T>>& q1, const QuaternionSimd<Quaternion<T>>& q2, const T t ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        using Simd = QuaternionSimd<Quaternion<T>>;
        return Simd( Traits::Slerp( q1.simd, q2.simd, Traits::Fill( t ) ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const QuaternionSimd<Quaternion<T>>& q1, const QuaternionSimd<Quaternion<T>>& q2, const Vector<T, 4>& t ) noexcept
    {
        return Math::Slerp( q1, q2, t.ToSimd( ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const QuaternionSimd<Quaternion<T>>& q1, const Quaternion<T>& q2, const typename Vector<T, 4>::Simd& t ) noexcept
    {
        return Math::Slerp( q1, q2.ToSimd( ), t );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const QuaternionSimd<Quaternion<T>>& q1, const Quaternion<T>& q2, const Vector<T, 4>& t ) noexcept
    {
        return Math::Slerp( q1, q2.ToSimd( ), t.ToSimd( ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const Quaternion<T>& q1, const QuaternionSimd<Quaternion<T>>& q2, const typename Vector<T, 4>::Simd& t ) noexcept
    {
        return Math::Slerp( q1.ToSimd( ), q2, t );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const Quaternion<T>& q1, const QuaternionSimd<Quaternion<T>>& q2, const Vector<T, 4>& t ) noexcept
    {
        return Math::Slerp( q1.ToSimd( ), q2, t.ToSimd( ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const Quaternion<T>& q1, const Quaternion<T>& q2, const typename Vector<T, 4>::Simd& t ) noexcept
    {
        return Math::Slerp( q1.ToSimd( ), q2.ToSimd( ), t );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const Quaternion<T>& q1, const Quaternion<T>& q2, const Vector<T, 4>& t ) noexcept
    {
        return Math::Slerp( q1.ToSimd( ), q2.ToSimd( ), t.ToSimd( ) );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const QuaternionSimd<Quaternion<T>>& q1, const Quaternion<T>& q2, const T t ) noexcept
    {
        return Math::Slerp( q1, q2.ToSimd( ), t );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const Quaternion<T>& q1, const QuaternionSimd<Quaternion<T>>& q2, const T t ) noexcept
    {
        return Math::Slerp( q1.ToSimd( ), q2, t );
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
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<Quaternion<T>> Slerp( const Quaternion<T>& q1, const Quaternion<T>& q2, const T t ) noexcept
    {
        return Math::Slerp( q1.ToSimd( ), q2.ToSimd( ), t );
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
    template<Internal::SimdType S, typename FloatT = typename S::value_Type >
        requires ( S::Size == 3 )
    S Rotate( const S& v, const QuaternionSimd<Quaternion<FloatT>>& rotationQuaternion )
    {
        using Traits = SIMD::Traits<FloatT, 4>;
        using Constants = Traits::Constants;
        using Q = QuaternionSimd<Quaternion<FloatT>>;

        Q a( Traits::Select( Constants::Select2221, v.simd, Constants::Select2221 ) );
        
        Q qc = Conjugate( rotationQuaternion );

        Q qca = qc * a;

        Q result = qca * rotationQuaternion;

        return S( result.simd);
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
    template<Internal::SimdType S, typename FloatT = typename S::value_Type >
        requires ( S::Size == 3 )
    S Rotate( const S& v, const Quaternion<FloatT>& rotationQuaternion )
    {
        return Rotate( v, rotationQuaternion.ToSimd( ) );
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
    template<Internal::TupleType S, typename FloatT = typename S::value_Type >
        requires ( S::Size == 3 )
    typename S::Simd Rotate( const S& v, const QuaternionSimd<Quaternion<FloatT>>& rotationQuaternion )
    {
        return Rotate( v.ToSimd( ), rotationQuaternion );
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
    template<Internal::TupleType S, typename FloatT = typename S::value_Type >
        requires ( S::Size == 3 )
    typename S::Simd Rotate( const S& v, const Quaternion<FloatT>& rotationQuaternion )
    {
        return Rotate( v.ToSimd( ), rotationQuaternion.ToSimd( ) );
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
    template<Internal::SimdType S, typename FloatT = typename S::value_Type >
        requires ( S::Size == 3 )
    S InverseRotate( const S& v, const QuaternionSimd<Quaternion<FloatT>>& rotationQuaternion )
    {
        using Traits = SIMD::Traits<FloatT, 4>;
        using Constants = Traits::Constants;
        using Q = QuaternionSimd<Quaternion<FloatT>>;

        Q qa( Traits::Select( Constants::Select2221, v.simd, Constants::Select2221 ) );

        auto result = rotationQuaternion * qa;
        auto rc = Conjugate( rotationQuaternion );
        return S(( result * rc ).simd );
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
    template<Internal::SimdType S, typename FloatT = typename S::value_Type >
        requires ( S::Size == 3 )
    S InverseRotate( const S& v, const Quaternion<FloatT>& rotationQuaternion )
    {
        return InverseRotate( v, rotationQuaternion.ToSimd( ) );
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
    template<Internal::TupleType S, typename FloatT = typename S::value_Type >
        requires ( S::Size == 3 )
    S InverseRotate( const S& v, const QuaternionSimd<Quaternion<FloatT>>& rotationQuaternion )
    {
        return InverseRotate( v.ToSimd( ), rotationQuaternion );
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
    template<Internal::TupleType S, typename FloatT = typename S::value_Type >
        requires ( S::Size == 3 )
    S InverseRotate( const S& v, const Quaternion<FloatT>& rotationQuaternion )
    {
        return InverseRotate( v.ToSimd( ), rotationQuaternion.ToSimd( ) );
    }


    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline auto ScalarAngleBetween( const T& v1, const U& v2 )
    {
        using Traits = typename T::Traits;
        using TupleType = typename T::TupleType;
        using FloatT = typename TupleType::value_type;

        auto dotProduct = Dot( v1, v2);

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

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline auto ScalarAngleBetween( const T& v1, const U& v2 )
    {
        return ScalarAngleBetween( v1, typename U::Simd( v2 ) );
    }

    template<Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
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
            // Expanding the code inline performs consistently better 
            auto sx = v1.x + v2.x;
            sx *= sx;
            auto sy = v1.y + v2.y; 
            sy *= sy;
            auto sz = v1.z + v2.z;
            sz *= sz;
            
            /*
            auto sx = Sqr(v1.x + v2.x);
            auto sy = Sqr(v1.y + v2.y);
            auto sz = Sqr(v1.z + v2.z);
            */
            auto halfLength = Sqrt( sx + sy + sz ) / static_cast< FloatT >( 2. );
            return Constants<FloatT>::Pi - static_cast< FloatT >( 2. ) * SafeASin( halfLength );
        }
        else
        {
            // Expanding the code inline performs consistently better 
            auto sx = v2.x - v1.x;
            sx *= sx;
            auto sy = v2.y - v1.y;
            sy *= sy;
            auto sz = v2.z - v1.z;
            sz *= sz;

            /*
            auto sx = Sqr(v2.x - v1.x);
            auto sy = Sqr(v2.y - v1.y);
            auto sz = Sqr(v2.z - v1.z);
            */
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
        constexpr inline void InitMatrix( std::index_sequence<I...>, std::array < std::array<FloatT, N>, N>& dest,Args... args )
        {
            ( ( dest[ I/N ][ I%N ] = static_cast< FloatT >( args ) ), ... );
        }

        template <size_t N, size_t... I, typename FloatT, typename... Args>
        constexpr inline void InitDiagonalMatrix( std::index_sequence<I...>, std::array < std::array<FloatT, N>,N>& dest, Args... args )
        {
            ( ( dest[ I ][ I ] = static_cast< FloatT >( args ) ), ... );
        }

        struct MatrixSimdBase
        { };

        struct MatrixBase
        { };

        template<typename T>
        concept SquareMatrixSimdType = std::is_base_of_v<MatrixSimdBase, T>;

        template<typename T>
        concept SquareMatrixType = std::is_base_of_v<MatrixBase, T>;

        template<typename T1, typename T2>
        constexpr bool IsCompatibleMatrix = std::is_same_v<typename T1::Traits, typename T2::Traits> && ( T1::Size == T2::Size );

    }

    
    template<typename MatrixT, typename size_t N>
    struct SquareMatrixSimd
    {
    };

    enum class MatrixType : UInt32
    {
        Zero,
        Identity
    };


    template<typename MatrixT>
    struct alignas( Core::SIMD::Traits<typename MatrixT::value_type, 1>::AlignAs )
        SquareMatrixSimd<MatrixT, 1> : public Internal::MatrixSimdBase
    {
        using MatrixType = MatrixT;
        using value_type = typename MatrixT::value_type;
        using Traits = Core::SIMD::Traits<value_type, 1>;
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
            : simd( ToSimd( matrix ) )
        {
        }

    };
    template<typename MatrixT>
    struct alignas( Core::SIMD::Traits<typename MatrixT::value_type, 4>::AlignAs )
        SquareMatrixSimd<MatrixT, 2> : public Internal::MatrixSimdBase
    {
        using MatrixType = MatrixT;
        using value_type = typename MatrixT::value_type;
        using Traits = Core::SIMD::Traits<value_type, 4>;
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
        static SIMDType ToSimd( const value_type matrix[Size][ Size ] )
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
            : simd( matrixType == Math::MatrixType::Identity? IdentityValues : ZeroValues )
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
            : simd( ToSimd( matrix ) )
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
    struct alignas( Core::SIMD::Traits<typename MatrixT::value_type, 3>::AlignAs )
        SquareMatrixSimd<MatrixT, 3> : public Internal::MatrixSimdBase
    {
        using MatrixType = MatrixT;
        using value_type = typename MatrixT::value_type;
        using Traits = Core::SIMD::Traits<value_type, 3>;
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
        static std::array<SIMDType, 3> ToSimd( const value_type matrix[Size][ Size ] )
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
        { }

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
            : simd( ToSimd( matrix ) )
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

        template<Internal::SimdType S>
            requires (S::Size > 2)
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
    struct alignas( Core::SIMD::Traits<typename MatrixT::value_type, 4>::AlignAs )
        SquareMatrixSimd<MatrixT, 4> : public Internal::MatrixSimdBase
    {
        using MatrixType = MatrixT;
        using value_type = typename MatrixT::value_type;
        using Traits = Core::SIMD::Traits<value_type, 4>;
        using Constants = typename Traits::Constants;
        using SIMDType = typename Traits::SIMDType;
        using ArrayType = std::array<std::array<value_type, 4>, 4>;
        static constexpr size_t Size = 4;

        std::array<SIMDType, 4> simd;

        static constexpr std::array<SIMDType, 4> ZeroValues{ Traits::Constants::Zero, Traits::Constants::Zero, Traits::Constants::Zero, Traits::Constants::Zero };
        static constexpr std::array<SIMDType, 4> IdentityValues{ Traits::Constants::IdentityR1, Traits::Constants::IdentityR2, Traits::Constants::IdentityR3, Traits::Constants::IdentityR4 };

        static std::array<SIMDType, 4> ToSimd( const ArrayType& matrix )
        {
            std::array<SIMDType, 4> result;
            result[ 0 ] = Traits::Load( matrix[ 0 ] );
            result[ 1 ] = Traits::Load( matrix[ 1 ] );
            result[ 2 ] = Traits::Load( matrix[ 2 ] );
            result[ 3 ] = Traits::Load( matrix[ 3 ] );
            return result;
        }

        static std::array<SIMDType, 4> ToSimd( const value_type matrix[Size][Size] )
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
        { }

        explicit SquareMatrixSimd( Math::MatrixType matrixType )
            : simd( matrixType == Math::MatrixType::Identity ? IdentityValues : ZeroValues )
        { }

        explicit SquareMatrixSimd( const std::array<SIMDType,4>& other )
            : simd( other )
        { }

        explicit SquareMatrixSimd( const std::array<SIMDType, 3>& other )
            : simd
            {
                Traits::And( other[ 0 ], Traits::Constants::Mask3 ),
                Traits::And( other[ 1 ], Traits::Constants::Mask3 ),
                Traits::And( other[ 2 ], Traits::Constants::Mask3 ),
                Constants::IdentityR4
            }
        { }

        explicit SquareMatrixSimd( const SIMDType r1, const SIMDType r2, const SIMDType r3 )
            : simd{ r1, r2, r3, Constants::IdentityR4 }
        {
        }

        explicit SquareMatrixSimd( const SIMDType r1, const SIMDType r2, const SIMDType r3, const SIMDType r4 )
            : simd { r1, r2, r3, r4 }
        {
        }

        SquareMatrixSimd( const SquareMatrixSimd& other )
            : simd( other.simd )
        { }
        explicit SquareMatrixSimd( const ArrayType& matrix )
            : simd( ToSimd( matrix ) )
        { }

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
    template<typename T, size_t N>
    class SquareMatrix : public Internal::MatrixBase
    {
    public:
        using Base = Internal::MatrixBase;

        using ValueType = T;
        static constexpr size_t Size = N;
        using value_type = ValueType;
        using Simd = SquareMatrixSimd<SquareMatrix,N>;

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
                    m[ i ][ j ] = ( i == j ) ? static_cast<value_type>( 1 ) : static_cast< value_type >( 0 );
                }
            }
            return m;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, value_type>
        static MatrixData MakeData( const T& mat ) noexcept
        {
            MatrixData result;
            memcpy( result[ 0 ].data( ), mat.data( ), std::min( Size * Size, mat.size( ) )*sizeof(value_type));
            return result;
        }
        
        static MatrixData MakeData( const value_type mat[ Size ][ Size ] ) noexcept
        {
            MatrixData result;
            memcpy( result[ 0 ].data( ), &mat[0][0], Size * Size * sizeof( value_type ) );
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
        { }

        SquareMatrix( const value_type (&mat)[ Size ][ Size ] )
            : data_(*reinterpret_cast< const MatrixData* >( &mat[ 0 ][ 0 ] ))
        { }
        SquareMatrix( const value_type( &mat )[ Size * Size ] )
            : data_( *reinterpret_cast< const MatrixData* >( &mat[ 0 ] ) )
        { }

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
            return Simd( Simd::ToSimd( data_ ) );
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

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1,T2>
    inline T1 operator+( const T1& m1, const T2& m2 ) noexcept
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

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline T2 operator+( const T1& m1, const T2& m2 ) noexcept
    {
        return m1.ToSimd( ) + m2;
    }

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline T1 operator+( const T1& m1, const T2& m2 ) noexcept
    {
        return m1 + m2.ToSimd( );
    }

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline auto operator+( const T1& m1, const T2& m2 ) noexcept
    {
        return m1.ToSimd( ) + m2.ToSimd( );
    }


    // Subtraction

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline T1 operator-( const T1& m1, const T2& m2 ) noexcept
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

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline T2 operator-( const T1& m1, const T2& m2 ) noexcept
    {
        return m1.ToSimd( ) - m2;
    }

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline T1 operator-( const T1& m1, const T2& m2 ) noexcept
    {
        return m1 - m2.ToSimd( );
    }

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline auto operator-( const T1& m1, const T2& m2 ) noexcept
    {
        return m1.ToSimd( ) - m2.ToSimd( );
    }


    // Scalar Multiplication

    template<Internal::SquareMatrixSimdType T1, typename T2>
        requires std::is_arithmetic_v<T2>
    T1 operator*( const T1& m, const T2 value ) noexcept
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

    template<Internal::SquareMatrixType T1, typename T2>
        requires IsFloatingPoint<T2>
    inline auto operator*( const T1& m, const T2 value ) noexcept
    {
        return m.ToSimd( ) * value;
    }

    template<Internal::SquareMatrixSimdType T1, typename T2>
        requires IsFloatingPoint<T2>
    inline auto operator*( const T2 value, const T1& m ) noexcept
    {
        return m * value;
    }

    template<Internal::SquareMatrixType T1, typename T2>
        requires IsFloatingPoint<T2>
    inline auto operator*( const T2 value, const T1& m ) noexcept
    {
        return m.ToSimd() * value;
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

        auto rmm5 = _mm256_shuffle_ps( rmm1, rmm1, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        auto rmm6 = _mm256_shuffle_ps( rmm2, rmm2, _MM_SHUFFLE( 0, 0, 0, 0 ) );
        auto rmm7 = _mm256_permute2f128_ps( rmm3, rmm3, 0x00 );
        auto rmm8 = _mm256_mul_ps( rmm5, rmm7 );
        auto rmm9 = _mm256_mul_ps( rmm6, rmm7 );

        rmm5 = _mm256_shuffle_ps( rmm1, rmm1, _MM_SHUFFLE( 1, 1, 1, 1 ) );
        rmm6 = _mm256_shuffle_ps( rmm2, rmm2, _MM_SHUFFLE( 1, 1, 1, 1 ) );
        rmm7 = _mm256_permute2f128_ps( rmm3, rmm3, 0x11 );
        auto rmm10 = _mm256_fmadd_ps( rmm5, rmm7, rmm8 );
        auto rmm11 = _mm256_fmadd_ps( rmm6, rmm7, rmm9 );

        rmm5 = _mm256_shuffle_ps( rmm1, rmm1, _MM_SHUFFLE( 2, 2, 2, 2 ) );
        rmm6 = _mm256_shuffle_ps( rmm2, rmm2, _MM_SHUFFLE( 2, 2, 2, 2 ) );
        auto rmm12 = _mm256_permute2f128_ps( rmm4, rmm4, 0x00 );
        auto rmm13 = _mm256_mul_ps( rmm5, rmm12 );
        auto rmm14 = _mm256_mul_ps( rmm6, rmm12 );

        rmm5 = _mm256_shuffle_ps( rmm1, rmm1, _MM_SHUFFLE( 3, 3, 3, 3 ) );
        rmm6 = _mm256_shuffle_ps( rmm2, rmm2, _MM_SHUFFLE( 3, 3, 3, 3 ) );
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

        auto rmm1 = Traits::Swizzle<2, 2, 0, 0>( matrix1.simd );
        auto rmm2 = Traits::Swizzle<1, 0, 1, 0>( matrix2.simd );
        auto rmm3 = Traits::Mul( rmm1, rmm2 );
        rmm1 = Traits::Swizzle<3, 3, 1, 1>( matrix1.simd );
        rmm2 = Traits::Swizzle<3, 2, 3, 2>( matrix2.simd );
        return Simd(Traits::FMAdd( rmm1, rmm2, rmm3 ));
    }


    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline T2 operator*( const T1& m1, const T2& m2 ) noexcept
    {
        return Math::Multiply( m1, m2 );
    }

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline T2 operator*( const T1& m1, const T2& m2 ) noexcept
    {
        return Math::Multiply( m1.ToSimd( ), m2 );
    }

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline T1 operator*( const T1& m1, const T2& m2 ) noexcept
    {
        return Math::Multiply( m1, m2.ToSimd( ) );
    }

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    inline auto operator*( const T1& m1, const T2& m2 ) noexcept
    {
        return Math::Multiply( m1.ToSimd( ), m2.ToSimd( ) );
    }

    // Division

    template<Internal::SquareMatrixSimdType T1, typename T2>
        requires std::is_arithmetic_v<T2>
    T1 operator/( const T1& m, const T2 value ) noexcept
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

    template<Internal::SquareMatrixType T1, typename T2>
        requires std::is_arithmetic_v<T2>
    T1 operator/( const T1& m, const T2 value ) noexcept
    {
        using FloatT = typename T1::value_type;
        return m.ToSimd( ) / static_cast< FloatT >( value );
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
    inline typename Vector<float,4>::Simd Determinant( const typename SquareMatrix<float, 4>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using ResultType = typename Vector<float, 4>::Simd;
        //using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
        using Select = typename Traits::SelectType;
        Traits::SIMDType sign( { { 1.0f, -1.0f, 1.0f, -1.0f } } );
        
        auto matrix2 = matrix.simd[ 2 ];
        auto matrix3 = matrix.simd[ 3 ];

        auto rmm0 = Traits::Swizzle<Select::X, Select::X, Select::X, Select::Y>( matrix2 );
        auto rmm1 = Traits::Swizzle<Select::Y, Select::Y, Select::Z, Select::Z>( matrix3 );
        auto rmm2 = Traits::Swizzle<Select::Z, Select::W, Select::W, Select::W>( matrix3 );
        auto rmm3 = Traits::Swizzle<Select::Y, Select::Y, Select::Z, Select::Z>( matrix2 );

        auto rmm4 = Traits::Mul( rmm0, rmm1 );
        auto rmm5 = Traits::Mul( rmm0, rmm2 );
        auto rmm6 = Traits::Mul( rmm3, rmm2 );
        rmm0 = Traits::Swizzle<Select::Y, Select::Y, Select::Z, Select::Z>( matrix2 );
        rmm1 = Traits::Swizzle<Select::X, Select::X, Select::X, Select::Y>( matrix3 );
        rmm2 = Traits::Swizzle<Select::Z, Select::W, Select::W, Select::W>( matrix2 );
        rmm3 = Traits::Swizzle<Select::Y, Select::Y, Select::Z, Select::Z>( matrix3 );

        rmm4 = Traits::FNMAdd( rmm0, rmm1, rmm4 );
        rmm5 = Traits::FNMAdd( rmm2, rmm1, rmm5 );
        rmm6 = Traits::FNMAdd( rmm2, rmm3, rmm6 );

        rmm3 = matrix.simd[ 1 ];

        rmm0 = Traits::Swizzle<Select::Z, Select::W, Select::W, Select::W>( rmm3 );
        rmm1 = Traits::Swizzle<Select::Y, Select::Y, Select::Z, Select::Z>( rmm3 );
        rmm2 = Traits::Swizzle<Select::X, Select::X, Select::X, Select::Y>( rmm3 );
        
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
        return Traits::First( Math::Determinant( matrix.ToSimd() ).simd );
    }


    inline typename Vector<float, 3>::Simd Determinant( const typename SquareMatrix<float, 3>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        using Simd = typename Vector<float, 3>::Simd;

        auto v1 = matrix.simd[ 1 ];
        auto v2 = matrix.simd[ 2 ];

        auto edd = Traits::Swizzle<3, 0, 0, 1>( v1 );
        auto iih = Traits::Swizzle<3, 1, 2, 2>( v2 );
        auto hgg = Traits::Swizzle<3, 0, 0, 1>( v2 );
        auto ffe = Traits::Swizzle<3, 1, 2, 2>( v1 );

        auto det = Traits::FMSub( edd, iih, Traits::Mul( hgg, ffe ) );

        Traits::SIMDType sign( { { 1.0f, -1.0f, 1.0f, 0.0f } } );
        auto v0 = Traits::Mul( matrix.simd[ 0 ], sign );

        return Simd(Traits::Dot( v0, det ));
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
        
        auto V00 = Traits::Swizzle<1, 1, 0, 0>( transposed.simd[ 2 ] );
        auto V10 = Traits::Swizzle<3, 2, 3, 2>( transposed.simd[ 3 ] );
        auto V01 = Traits::Swizzle<1, 1, 0, 0>( transposed.simd[ 0 ] );
        auto V11 = Traits::Swizzle<3, 2, 3, 2>( transposed.simd[ 1 ] );

        auto V02 = Traits::Shuffle<2, 0, 2, 0>( transposed.simd[ 2 ], transposed.simd[ 0 ] );
        auto V12 = Traits::Shuffle<3, 1, 3, 1>( transposed.simd[ 3 ], transposed.simd[ 1 ] );

        auto D0 = Traits::Mul( V00, V10 );
        auto D1 = Traits::Mul( V01, V11 );
        auto D2 = Traits::Mul( V02, V12 );


        V00 = Traits::Swizzle<3, 2, 3, 2>( transposed.simd[ 2 ]);
        V10 = Traits::Swizzle<1, 1, 0, 0>( transposed.simd[ 3 ]);
        V01 = Traits::Swizzle<3, 2, 3, 2>( transposed.simd[ 0 ]);
        V11 = Traits::Swizzle<1, 1, 0, 0>( transposed.simd[ 1 ]);

        V02 = Traits::Shuffle<3, 1, 3, 1>( transposed.simd[ 2 ], transposed.simd[ 0 ] );
        V12 = Traits::Shuffle<2, 0, 2, 0>( transposed.simd[ 3 ], transposed.simd[ 1 ] );


        D0 = Traits::FNMAdd( V00, V10, D0 );
        D1 = Traits::FNMAdd( V01, V11, D1 );
        D2 = Traits::FNMAdd( V02, V12, D2 );

        // V11 = D0Y,D0W,D2Y,D2Y
        V11 = Traits::Shuffle<1, 1, 3, 1>( D0, D2 );
        V00 = Traits::Swizzle<1, 0, 2, 1>( transposed.simd[ 1 ] );
        V10 = Traits::Shuffle<0, 3, 0, 2>( V11, D0 );
        V01 = Traits::Swizzle<0, 1, 0, 2>( transposed.simd[ 0 ] );
        V11 = Traits::Shuffle<2, 1, 2, 1>( V11, D0 );

        // V13 = D1Y,D1W,D2W,D2W
        auto V13 = Traits::Shuffle<3, 3, 3, 1>( D1, D2 );
        V02 = Traits::Swizzle<1, 0, 2, 1>( transposed.simd[ 3 ] );
        V12 = Traits::Shuffle<0, 3, 0, 2>( V13, D1 );
        auto V03 = Traits::Swizzle<0, 1, 0, 2>( transposed.simd[ 2 ] );
        V13 = Traits::Shuffle<2, 1, 2, 1>( V13, D1 );

        auto C0 = Traits::Mul( V00, V10 );
        auto C2 = Traits::Mul( V01, V11 );
        auto C4 = Traits::Mul( V02, V12 );
        auto C6 = Traits::Mul( V03, V13 );


        // V11 = D0X,D0Y,D2X,D2X
        V11 = Traits::Shuffle<0, 0, 1, 0>( D0, D2 );
        V00 = Traits::Swizzle<2, 1, 3, 2>( transposed.simd[ 1 ] );
        V10 = Traits::Shuffle<2, 1, 0, 3>( D0, V11 );
        V01 = Traits::Swizzle<1, 3, 2, 3>( transposed.simd[ 0 ] );
        V11 = Traits::Shuffle<0, 2, 1, 2>( D0, V11 );
        // V13 = D1X,D1Y,D2Z,D2Z
        V13 = Traits::Shuffle<2, 2, 1, 0>( D1, D2 );
        V02 = Traits::Swizzle<2, 1, 3, 2>( transposed.simd[ 3 ] );
        V12 = Traits::Shuffle<2, 1, 0, 3>( D1, V13 );
        V03 = Traits::Swizzle<1, 3, 2, 3>( transposed.simd[ 2 ] );
        V13 = Traits::Shuffle<0, 2, 1, 2>( D1, V13 );

        C0 = Traits::FNMAdd( V00, V10, C0 );
        C2 = Traits::FNMAdd( V01, V11, C2 );
        C4 = Traits::FNMAdd( V02, V12, C4 );
        C6 = Traits::FNMAdd( V03, V13, C6 );

        V00 = Traits::Swizzle<0, 3, 0, 3>( transposed.simd[ 1 ] );
        // V10 = D0Z,D0Z,D2X,D2Y
        V10 = Traits::Shuffle<1, 0, 2, 2>( D0, D2 );
        V10 = Traits::Swizzle<0, 2, 3, 0>( V10 );
        V01 = Traits::Swizzle<2, 0, 3, 1>( transposed.simd[ 0 ] );
        // V11 = D0X,D0W,D2X,D2Y
        V11 = Traits::Shuffle<1, 0, 3, 0>( D0, D2 );
        V11 = Traits::Swizzle<2, 1, 0, 3>( V11 );
        V02 = Traits::Swizzle<0, 3, 0, 3>( transposed.simd[ 3 ] );
        // V12 = D1Z,D1Z,D2Z,D2W
        V12 = Traits::Shuffle<3, 2, 2, 2>( D1, D2 );
        V12 = Traits::Swizzle<0, 2, 3, 0>( V12 );
        V03 = Traits::Swizzle<2, 0, 3, 1>( transposed.simd[ 2 ] );
        // V13 = D1X,D1W,D2Z,D2W
        V13 = Traits::Shuffle<3, 2, 3, 0>( D1, D2 );
        V13 = Traits::Swizzle<2, 1, 0, 3>( V13 );

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
        C0 = Traits::Swizzle<3, 1, 2, 0>( C0 );
        C2 = Traits::Swizzle<3, 1, 2, 0>( C2 );
        C4 = Traits::Swizzle<3, 1, 2, 0>( C4 );
        C6 = Traits::Swizzle<3, 1, 2, 0>( C6 );
        // Get the determinant
        auto vTemp = Traits::Dot( C0, transposed.simd[ 0 ] );
        if ( determinant != nullptr )
        {
            *determinant = vTemp;
        }
        vTemp = Traits::Div( Traits::Fill(1.f), vTemp );
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

        auto edd = Traits::Swizzle<3, 0, 0, 1>( v1 );
        auto iih = Traits::Swizzle<3, 1, 2, 2>( v2 );
        auto hgg = Traits::Swizzle<3, 0, 0, 1>( v2 );
        auto ffe = Traits::Swizzle<3, 1, 2, 2>( v1 );

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
        auto baa = Traits::Swizzle<3, 0, 0, 1>( v0 );
        auto ccb = Traits::Swizzle<3, 1, 2, 2>( v0 );
        
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
        return Simd( Traits::Swizzle<3, 1, 2, 0>( matrix.simd ));
    }

    inline SquareMatrix<float, 2>::Simd Transpose( const SquareMatrix<float, 2>& matrix )
    {
        return Transpose( matrix.ToSimd( ) );
    }


    inline typename Vector<float, 2>::Simd Determinant( const typename SquareMatrix<float, 2>::Simd& matrix )
    {
        using Traits = SquareMatrix<float, 2>::Traits;
        using Simd = typename Vector<float, 2>::Simd;

        auto rmm1 = Traits::Swizzle<2, 1, 3, 0>( matrix.simd );
        auto rmm2 = Traits::Swizzle<2, 3, 0, 1>( rmm1 );
        rmm1 = Traits::Mul( rmm1, rmm2 );
        rmm1 = Traits::Mul( rmm1, { {1.f,1.f,-1.f,-1.f} } );
        rmm2 = Traits::Swizzle<1, 0, 3, 2>( rmm1 );
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
        auto rmm1 = Traits::Swizzle<2, 1, 3, 0>( matrix.simd );
        auto rmm2 = Traits::Swizzle<2, 3, 0, 1>( rmm1 );
        rmm1 = Traits::Mul( rmm1, rmm2 );
        rmm1 = Traits::Mul( rmm1, { {1.f,1.f,-1.f,-1.f} });
        rmm2 = Traits::Swizzle<1, 0, 3, 2>( rmm1 );
        rmm1 = Traits::Add( rmm1, rmm2 );
        if ( determinant )
        {
            (*determinant).simd = rmm1;
        }
        rmm1 = Traits::Div( { {1.f,1.f,1.f,1.f} }, rmm1 );
        rmm2 = Traits::Swizzle<0, 2, 1, 3>( matrix.simd );
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
    template<Internal::SimdType S>
        requires (S::Size > 2) && std::is_same_v<typename S::value_type, float>
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
    template<Internal::TupleType S>
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
    template<Internal::SimdType S>
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
    template<Internal::TupleType S>
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
    template<Internal::SimdType S>
        requires (S::Size > 2)
    inline SquareMatrix<float, 4>::Simd Rotation( const S& v ) noexcept
    {
        using Simd = SquareMatrix<float, 4>::Simd;
        using Traits = Simd::Traits;
        using SIMDType = Traits::SIMDType;
        using P = Traits::PermuteType;

        constexpr SIMDType sign = { { 1.0f, -1.0f, -1.0f, 1.0f } };
        constexpr SIMDType r4 = { { 0.0f, 0.0f, 0.0f, 1.0f } };
        constexpr SIMDType zero = { { 0.0f, 0.0f, 0.0f, 0.0f } };
        constexpr SIMDType columnSelect = { { std::bit_cast<float>( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), 0 } };

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
    template<Internal::TupleType S>
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
    template<Internal::SimdType S>
        requires ( S::Size > 2 ) 
    inline SquareMatrix<float, 4>::Simd RotationNormal( const S& normalizedAxis, float angle ) noexcept
    {
        using Traits = SIMD::Traits<float, 4>;
        using Constants = typename Traits::Constants;
        using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
        using SIMDType = typename Traits::SIMDType;
        constexpr SIMDType maskXYZ{ { std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), 0x00000000 } };
        /*
        SIMDType C1;
        auto C0 = Traits::FastSinCos( Traits::Fill( angle ), &C1 );
        auto C2 = Traits::Sub( Constants::One, C1 );
        */
        
        
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
    template<Internal::TupleType S>
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
    template<Internal::SimdType S>
        requires ( S::Size > 2 )
    inline SquareMatrix<float, 4>::Simd RotationAxis( const S& axis, float angle ) noexcept
    {
        return RotationNormal( Normalize( axis ), angle );
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
    template<Internal::TupleType S>
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
    inline SquareMatrix<float, 4>::Simd Rotation( const QuaternionSimd<Quaternion<float>>& q ) noexcept
    {
        using Traits = SIMD::Traits<float, 4>;
        using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
        using SIMDType = typename Traits::SIMDType;
        constexpr SIMDType maskXYZ{ { std::bit_cast<float>( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), std::bit_cast< float >( 0xFFFFFFFF ), 0x00000000 } };

        auto Q0 = Traits::Add( q.simd, q.simd );
        auto Q1 = Traits::Mul( q.simd, Q0 );

        auto V0 = Traits::Shuffle<3, 0, 0, 1>( Q1 );
        V0 = Traits::And( V0, maskXYZ );
        auto V1 = Traits::Shuffle<3, 1, 2, 2>( Q1);
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
    inline SquareMatrix<float, 4>::Simd RotationQuaternion( const QuaternionSimd<Quaternion<float>>& q ) noexcept
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin, rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f::Simd& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin, scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion,
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion,
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion, scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin, rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>::Simd& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f::Simd& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const QuaternionSimd<Quaternion<float>>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>::Simd& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    inline SquareMatrix<float, 4>::Simd TransformationMatrix( const Point3f& scalingOrigin, 
                                                            const Quaternion<float>& scalingOrientationQuaternion, 
                                                            const Vector<float,3>& scaling,
                                                            const Point3f& rotationOrigin, 
                                                            const Quaternion<float>& rotationQuaternion, 
                                                            const Vector<float, 3>& translation ) noexcept
    {
        return TransformationMatrix( scalingOrigin.ToSimd( ), scalingOrientationQuaternion.ToSimd( ), scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    template<Internal::SimdType S, Internal::SimdType T, typename U, Internal::SimdType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
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
    template<Internal::SimdType S, Internal::SimdType T, typename U, Internal::TupleType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const QuaternionSimd<Quaternion<U>>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    template<Internal::SimdType S, Internal::SimdType T, typename U, Internal::SimdType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const Quaternion<U>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    template<Internal::SimdType S, Internal::SimdType T, typename U, Internal::TupleType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const Quaternion<U>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling, rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    template<Internal::SimdType S, Internal::TupleType T, typename U, Internal::SimdType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const QuaternionSimd<Quaternion<U>>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    template<Internal::SimdType S, Internal::TupleType T, typename U, Internal::TupleType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const QuaternionSimd<Quaternion<U>>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling, rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    template<Internal::SimdType S, Internal::TupleType T, typename U, Internal::SimdType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const Quaternion<U>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    template<Internal::SimdType S, Internal::TupleType T, typename U, Internal::TupleType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const Quaternion<U>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling, rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    template<Internal::TupleType S, Internal::SimdType T, typename U, Internal::SimdType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const QuaternionSimd<Quaternion<U>>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation );
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
    template<Internal::TupleType S, Internal::SimdType T, typename U, Internal::TupleType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const QuaternionSimd<Quaternion<U>>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling.ToSimd( ), rotationOrigin, rotationQuaternion, translation.ToSimd( ) );
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
    template<Internal::TupleType S, Internal::SimdType T, typename U, Internal::SimdType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const Quaternion<U>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation );
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
    template<Internal::TupleType S, Internal::SimdType T, typename U, Internal::TupleType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const Quaternion<U>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling.ToSimd( ), rotationOrigin, rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    template<Internal::TupleType S, Internal::TupleType T, typename U, Internal::SimdType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const QuaternionSimd<Quaternion<U>>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion, translation );
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
    template<Internal::TupleType S, Internal::TupleType T, typename U, Internal::TupleType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const QuaternionSimd<Quaternion<U>>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling.ToSimd(), rotationOrigin.ToSimd( ), rotationQuaternion, translation.ToSimd( ) );
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
    template<Internal::TupleType S, Internal::TupleType T, typename U, Internal::SimdType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const Quaternion<U>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling.ToSimd( ), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation );
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
    template<Internal::TupleType S, Internal::TupleType T, typename U, Internal::TupleType W>
        requires (S::Size > 2) && (T::Size > 2) && (W::Size > 2) && IsFloatingPoint<U> &&
            std::is_same_v<typename S::value_type,U> && std::is_same_v<typename T::value_type, U> && 
                std::is_same_v<typename W::value_type, U>
    inline SquareMatrix<U, 4>::Simd AffineTransformationMatrix( const S& scaling,
                                                                const T& rotationOrigin,
                                                                const Quaternion<U>& rotationQuaternion,
                                                                const W& translation ) noexcept
    {
        return AffineTransformationMatrix( scaling.ToSimd(), rotationOrigin.ToSimd( ), rotationQuaternion.ToSimd( ), translation.ToSimd( ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S,T> && Internal::IsCompatible<S, U> && (S::Size == 3)
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
    {
        return LookTo( cameraPosition, cameraDirection, upDirection.ToSimd() );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
    {
        return LookTo( cameraPosition, cameraDirection.ToSimd( ), upDirection );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
    {
        return LookTo( cameraPosition, cameraDirection.ToSimd( ), upDirection.ToSimd( ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
    {
        return LookTo( cameraPosition.ToSimd( ), cameraDirection, upDirection );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
    {
        return LookTo( cameraPosition.ToSimd( ), cameraDirection, upDirection.ToSimd( ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
    {
        return LookTo( cameraPosition.ToSimd( ), cameraDirection.ToSimd( ), upDirection );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookTo( const S& cameraPosition, const T& cameraDirection, const U& upDirection ) noexcept
    {
        return LookTo( cameraPosition.ToSimd( ), cameraDirection.ToSimd( ), upDirection.ToSimd( ) );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        auto cameraDirection = focusPosition - cameraPosition;
        return LookTo( cameraPosition, cameraDirection, upDirection );
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
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        return LookAt( cameraPosition, focusPosition, upDirection.ToSimd( ) );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        return LookAt( cameraPosition, focusPosition.ToSimd( ), upDirection );
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
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        return LookAt( cameraPosition, focusPosition.ToSimd( ), upDirection.ToSimd( ) );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        return LookAt( cameraPosition.ToSimd( ), focusPosition, upDirection );
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
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        return LookAt( cameraPosition.ToSimd( ), focusPosition, upDirection.ToSimd( ) );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        return LookAt( cameraPosition.ToSimd( ), focusPosition.ToSimd( ), upDirection );
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
    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U> && ( S::Size == 3 )
    inline SquareMatrix<typename S::value_type, 4>::Simd LookAt( const S& cameraPosition, const T& focusPosition, const U& upDirection ) noexcept
    {
        return LookAt( cameraPosition.ToSimd( ), focusPosition.ToSimd( ), upDirection.ToSimd( ) );
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
        SinCos( static_cast< T >(0.5) * fovAngleY, &sineFov, &cosineFov );

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
        requires (N > 2)
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
        t0 = Length( Math::Vector<value_type,4>::Simd( t2 ) ).simd;
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
        return Transform( v.ToSimd(), matrix );
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
    template<Internal::SimdType S, typename FloatT = S::value_type, typename MatrixT = typename SquareMatrix<FloatT, 4>::Simd>
    S Project (const S& v, FloatT viewportX, FloatT viewportY, FloatT viewportWidth, FloatT viewportHeight, FloatT viewportMinZ, FloatT viewportMaxZ,
        const MatrixT& projection, const MatrixT& viewTransform, const MatrixT& WorldTransform ) noexcept
    {
        using Traits = SIMD::Traits<FloatT, 4>;
        const FloatT halfViewportWidth = viewportWidth * static_cast< FloatT >(0.5);
        const FloatT halfViewportHeight = viewportHeight * static_cast< FloatT >( 0.5 );

        auto scale = Traits::Set( viewportMaxZ - viewportMinZ, -halfViewportHeight, halfViewportWidth );
        auto offset = Traits::Set( viewportMinZ, viewportY + halfViewportHeight, viewportX + halfViewportWidth );

        auto transformation = WorldTransform * viewTransform;
        transformation = transformation * projection;

        auto result = Traits::TransformPoint( v.simd, transformation.simd[0], transformation.simd[ 1 ], transformation.simd[ 2 ], transformation.simd[ 3 ] );

        return S( SIMD::Traits<FloatT, 3>::FMAdd( result, scale, offset ) );
    }
}

namespace std
{
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Math::Vector<float,2>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<float,2>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<float, 2>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<float, 2>::Simd& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}; {}]", value.x(), value.y() );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}; {}]", value.x(), value.y() );
            }
        }
    };


    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Math::Vector<int, 2>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<int, 2>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<int, 2>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<int, 2>::Simd& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<float, 3>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<float, 3>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<float, 3>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<float, 3>::Simd & value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<int, 3>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<int, 3>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<int, 3>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<int, 3>::Simd& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<float, 4>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<float, 4>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<float, 4>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<float, 4>::Simd& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<int, 4>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<int, 4>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Vector<int, 4>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Vector<int, 4>::Simd& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Point2f, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Point2f& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Point2f::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Point2f::Simd& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Point2i, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Point2i& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Point2i::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Point2i::Simd& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Point3f, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Point3f& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Point3f::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Point3f::Simd & value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Point3i, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Point3i& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Point3i::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Point3i::Simd& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Normal3f, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Normal3f& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Normal3f::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Normal3f::Simd& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::Quaternion<float>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Quaternion<float>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::SquareMatrix<float,3>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::SquareMatrix<float, 3>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::SquareMatrix<float, 3>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::SquareMatrix<float, 3>::Simd& value, FormatContext& ctx ) const
        {
            Harlinn::Common::Core::Math::SquareMatrix<float, 3> m( value );
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
    struct formatter<Harlinn::Common::Core::Math::SquareMatrix<float, 4>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::SquareMatrix<float, 4>& value, FormatContext& ctx ) const
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
    struct formatter<Harlinn::Common::Core::Math::SquareMatrix<float, 4>::Simd, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::SquareMatrix<float, 4>::Simd& value, FormatContext& ctx ) const
        {
            Harlinn::Common::Core::Math::SquareMatrix<float, 4> m( value );
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

namespace Harlinn::Common::Core::Math
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
