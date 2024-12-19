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

    template<typename T>
    constexpr bool IsLoadedType = T::Loaded;

    template<typename T>
    constexpr bool IsUnloadedType = T::Unloaded;



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
        struct TupleBase
        { };

        struct TupleSimdBase
        { };
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


    template<typename TraitsT, typename TupleT>
    class TupleSimd : public Internal::TupleSimdBase
    {
    public:
        using Traits = TraitsT;
        using TupleType = TupleT;
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

        TupleSimd( const TupleType& other ) noexcept
            : simd( Traits::Load( other.values.data( ) ) )
        {
        }

        bool operator == ( const TupleSimd& other ) const noexcept
        {
            return Traits::Equals( simd, other.simd );
        }

        bool operator != ( const TupleSimd& other ) const noexcept
        {
            return Traits::Equals( simd, other.simd ) == false;
        }

        template<typename T>
            requires (T::Unloaded && T::Size == Size && std::is_same_v<value_type, typename T::value_type>)
        bool operator == ( const T& other ) const noexcept
        {
            return Traits::Equals( simd, Traits::Load( other.values.data() ) );
        }

        template<typename T>
            requires ( T::Unloaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        bool operator != ( const T& other ) const noexcept
        {
            return Traits::Equals( simd, Traits::Load( other.values.data() ) ) == false;
        }

        template<typename T>
            requires ( T::Unloaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
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

        template<typename T>
            requires ( T::Unloaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
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

        template<typename T>
            requires ( T::Unloaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
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

        template<typename T>
            requires ( T::Unloaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
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

        template<typename T>
            requires ( T::Unloaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
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
    };

    namespace Internal
    {
        template<typename T>
        concept SimdType = std::is_base_of_v<TupleSimdBase, T>;

        template<typename T>
        concept TupleType = std::is_base_of_v<TupleBase,T>;

        template<typename T1, typename T2>
        constexpr bool IsCompatible =
            std::is_same_v<typename T1::Traits, typename T2::Traits>;
    }


    /// <summary>
    /// A tuple holding two numbers.
    /// </summary>
    /// <typeparam name="DerivedT">
    /// A concrete type derived from this template.
    /// </typeparam>
    /// <typeparam name="T">
    /// The type of the values.
    /// </typeparam>
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
        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using Simd = TupleSimd<Traits,DerivedT>;

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

        Tuple2( value_type xv, value_type yv) noexcept
            : x( xv ), y(yv)
        { }

        template<typename T>
            requires ( T::Loaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        Tuple2( const T& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        {
        }
            
        template<typename T>
            requires ( T::Loaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        DerivedType& operator = ( const T& other ) noexcept
        {
            values = Traits::ToArray( other.simd );
            return static_cast< DerivedType& >( *this );
        }

        constexpr bool operator == ( const Tuple2& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y );
        }
        constexpr bool operator != ( const Tuple2& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y );
        }

        template<typename T>
            requires ( T::Loaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        bool operator == ( const T& other ) const noexcept
        {
            return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
        }

        template<typename T>
            requires ( T::Loaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        bool operator != ( const T& other ) const noexcept
        {
            return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values.data( ) ) );
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
        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using Simd = TupleSimd<Traits, DerivedT>;

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

        Tuple3( value_type xv, value_type yv, value_type zv ) noexcept
            : x( xv ), y( yv ), z( zv )
        { }

        template<Internal::SimdType T>
            requires std::is_same_v<Traits, typename T::Traits>
        Tuple3( const T& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        { }

        template<Internal::SimdType T>
            requires std::is_same_v<Traits, typename T::Traits>
        DerivedType& operator = ( const T& other ) noexcept
        {
            values = Traits::ToArray( other.simd );
            return static_cast< DerivedType& >( *this );
        }

        constexpr bool operator == ( const Tuple3& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z );
        }
        constexpr bool operator != ( const Tuple3& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y ) || !IsSameValue( z, other.z );
        }

        template<Internal::SimdType T>
            requires std::is_same_v<Traits, typename T::Traits>
        bool operator == ( const T& other ) const noexcept
        {
            return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
        }

        template<Internal::SimdType T>
            requires std::is_same_v<Traits, typename T::Traits>
        bool operator != ( const T& other ) const noexcept
        {
            return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values.data( ) ) );
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
        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using Simd = TupleSimd<Traits, DerivedT>;

        union
        {
            ArrayType values;
            struct
            {
                value_type x, y, z, w;
            };
        };

        Tuple4( ) noexcept
            : x( 0.0 ), y( 0.0 ), z( 0.0 ), w( 0.0 )
        {
        }

        Tuple4( value_type xv, value_type yv, value_type zv, value_type wv ) noexcept
            : x( xv ), y( yv ), z( zv ), w( wv )
        {
        }

        template<typename T>
            requires ( T::Loaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        Tuple4( const T& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        {
        }

        template<typename T>
            requires ( T::Loaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        DerivedType& operator = ( const T& other ) noexcept
        {
            values = Traits::ToArray( other.simd );
            return static_cast< DerivedType& >( *this );
        }

        constexpr bool operator == ( const Tuple4& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z ) && IsSameValue( w, other.w );
        }
        constexpr bool operator != ( const Tuple4& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y ) || !IsSameValue( z, other.z ) || !IsSameValue( w, other.w );
        }

        template<typename T>
            requires ( T::Loaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        bool operator == ( const T& other ) const noexcept
        {
            return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
        }

        template<typename T>
            requires ( T::Loaded&& T::Size == Size && std::is_same_v<value_type, typename T::value_type> )
        bool operator != ( const T& other ) const noexcept
        {
            return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
        }

        Simd operator-( ) const noexcept
        {
            return Traits::Negate( Traits::Load( values.data( ) ) );
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
        return Traits::Sub( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T operator - ( const U& lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ), rhs.simd ) );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT operator - ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
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
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), lhs.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT operator * ( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    template<Internal::SimdType T, typename U>
        requires std::is_arithmetic_v<U>
    inline T operator * ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Mul( lhs.simd, Traits::Fill( static_cast< Type >( rhs ) ) );
    }
    template<typename U, Internal::SimdType T>
        requires std::is_arithmetic_v<U>
    inline T operator * ( const U lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Mul( Traits::Fill( static_cast< Type >( lhs ) ), rhs.simd );
    }

    template<Internal::TupleType T, typename U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<U>
    inline ResultT operator * ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Fill( static_cast< Type >( rhs ) ) );
    }
    template<typename U, Internal::TupleType T, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<U>
    inline ResultT operator * ( const U lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Mul( Traits::Fill( static_cast< Type >( lhs ) ), Traits::Load( rhs.values.data( ) ) );
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
        requires std::is_arithmetic_v<U>
    inline T operator / ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Div( lhs.simd, Traits::Fill( static_cast< Type >( rhs ) ) );
    }
    template<typename U, Internal::SimdType T>
        requires std::is_arithmetic_v<U>
    inline T operator / ( const U lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Div( Traits::Fill( static_cast< Type >( lhs ) ), rhs.simd );
    }

    template<Internal::TupleType T, typename U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<U>
    inline ResultT operator / ( const T& lhs, const U rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::Fill( static_cast< Type >( rhs ) ) );
    }
    template<typename U, Internal::TupleType T, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<U>
    inline ResultT operator / ( const U lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        return Traits::Div( Traits::Fill( static_cast< Type >( lhs ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Operations
    
    
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
        else 
        {
            return t.x + t.y + t.z + t.w;
        }
    }
    /// <summary>
    /// Calculates the horizontal sum of the elements in the vector.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT HSum( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill( ScalarHSum( t ) );
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
        else
        {
            return t.x * t.y * t.z * t.w;
        }
    }
    /// <summary>
    /// Calculates the horizontal product of the elements in the vector.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT HProd( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill( ScalarHProc( t ) );
    }

    // Abs

    template<Internal::SimdType T>
    inline T Abs( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Abs( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Traits::Load( t.values.data() ) );
    }

    // Min

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Min( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Min( lhs.simd, rhs.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Min( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Min( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Min( const U& lhs, const T& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Min( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Min( const T& lhs, const U& rhs ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Min( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Max

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

    template<Internal::SimdType T>
    inline T Sqr( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Mul( t.simd, t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Sqr( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Sqr<typename T::Simd>( Traits::Load( t.values.data( ) ) );
    }

    // Ceil

    template<Internal::SimdType T>
    inline T Ceil( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Ceil( t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Ceil( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Ceil( Traits::Load( t.values.data( ) ) );
    }

    // Floor

    template<Internal::SimdType T>
    inline T Floor( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Floor( t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Floor( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Floor( Traits::Load( t.values.data( ) ) );
    }

    // Round

    template<Internal::SimdType T>
    inline T Round( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Round( t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Round( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Round( Traits::Load( t.values.data( ) ) );
    }

    // Trunc

    template<Internal::SimdType T>
    inline T Trunc( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Truncate( t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Trunc( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Truncate( Traits::Load( t.values.data( ) ) );
    }

    // Lerp

    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT> && Internal::IsCompatible<T, U> 
    inline T Lerp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Lerp( static_cast<Type>( a ), b.simd, c.simd );
    }

    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T Lerp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Lerp( static_cast< Type >( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U Lerp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Lerp( static_cast< Type >( a ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT Lerp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Lerp( static_cast< Type >( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( a.simd, b.simd, c.simd );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
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

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    //

    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, upperBounds.simd );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename S::Simd>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT Clamp( const S& v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT> && Internal::IsCompatible<T, U>
    inline ResultT Clamp( NumberT v, const T& lowerBounds, const U& upperBounds ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Clamp( Traits::Fill( v ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }


    // Saturate

    template<Internal::SimdType T>
    inline T Saturate( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Saturate( t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Saturate( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // Sqrt

    template<Internal::SimdType T>
    inline T Sqrt( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Sqrt( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( Traits::Load( t.values.data( ) ) );
    }


    // FMA

    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMA( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd );
    }

    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMA( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMA( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMA( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMA( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd );
    }

    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMA( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMA( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd );
    }

    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMA( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( a.simd, b.simd, c.simd );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FMA( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    // FMSub

    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd );
    }

    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMSub( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd );
    }

    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T FMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U FMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd );
    }

    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT FMSub( const T& a, NumberT b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( a.simd, b.simd, c.simd );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline ResultT FMSub( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }


    // Sin

    template<Internal::SimdType T>
    inline T Sin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sin( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Sin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sin( Traits::Load( v.values.data( ) ) );
    }

    // Cos

    template<Internal::SimdType T>
    inline T Cos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cos( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Cos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cos( Traits::Load( v.values.data( ) ) );
    }

    // Tan

    template<Internal::SimdType T>
    inline T Tan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Tan( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Tan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Tan( Traits::Load( v.values.data( ) ) );
    }

    // ASin

    template<Internal::SimdType T>
    inline T ASin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ASin( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ASin( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ASin( Traits::Load( v.values.data( ) ) );
    }

    // ACos

    template<Internal::SimdType T>
    inline T ACos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ACos( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ACos( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ACos( Traits::Load( v.values.data( ) ) );
    }

    // ATan

    template<Internal::SimdType T>
    inline T ATan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ATan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan( Traits::Load( v.values.data( ) ) );
    }


    // ATan2

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T ATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan2( x.simd, y.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T ATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T ATan2( const U& x, const T& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), y.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT ATan2( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // SinH

    template<Internal::SimdType T>
    inline T SinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::SinH( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT SinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::SinH( Traits::Load( v.values.data( ) ) );
    }


    // CosH

    template<Internal::SimdType T>
    inline T CosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::CosH( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT CosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::CosH( Traits::Load( v.values.data( ) ) );
    }

    // TanH

    template<Internal::SimdType T>
    inline T TanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::TanH( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT TanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::TanH( Traits::Load( v.values.data( ) ) );
    }

    // ASinH

    template<Internal::SimdType T>
    inline T ASinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ASinH( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ASinH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ASinH( Traits::Load( v.values.data( ) ) );
    }

    // ACosH

    template<Internal::SimdType T>
    inline T ACosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ACosH( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ACosH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ACosH( Traits::Load( v.values.data( ) ) );
    }

    // ATanH

    template<Internal::SimdType T>
    inline T ATanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATanH( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ATanH( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ATanH( Traits::Load( v.values.data( ) ) );
    }

    // Log

    template<Internal::SimdType T>
    inline T Log( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Log( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log( Traits::Load( v.values.data( ) ) );
    }

    // Log1P

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

    template<Internal::SimdType T>
    inline T Log10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log10( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Log10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log10( Traits::Load( v.values.data( ) ) );
    }

    // Log2

    template<Internal::SimdType T>
    inline T Log2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log2( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Log2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Log2( Traits::Load( v.values.data( ) ) );
    }

    // Exp

    template<Internal::SimdType T>
    inline T Exp( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Exp( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp( Traits::Load( v.values.data( ) ) );
    }

    // Exp10

    template<Internal::SimdType T>
    inline T Exp10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp10( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Exp10( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp10( Traits::Load( v.values.data( ) ) );
    }

    // Exp2

    template<Internal::SimdType T>
    inline T Exp2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp2( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Exp2( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Exp2( Traits::Load( v.values.data( ) ) );
    }

    // ExpM1

    template<Internal::SimdType T>
    inline T ExpM1( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ExpM1( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ExpM1( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::ExpM1( Traits::Load( v.values.data( ) ) );
    }


    // Pow

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Pow( const T& base, const U& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Pow( base.simd, exponent.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Pow( const T& base, const U& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Pow( base.simd, Traits::Load( exponent.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Pow( const U& base, const T& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), exponent.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Pow( const T& base, const U& exponent ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), Traits::Load( exponent.values.data( ) ) );
    }

    // Hypot

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Hypot( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Hypot( x.simd, y.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Hypot( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Hypot( x.simd, Traits::Load( y.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Hypot( const U& x, const T& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), y.simd );
    }
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Hypot( const T& x, const U& y ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // Dot

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot( v1.simd, v2.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot( v1.simd, Traits::Load( v2.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Dot( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::value_type>
        requires Internal::IsCompatible<T, U>
    constexpr inline ResultT ScalarDot( const T& v1, const U& v2 ) noexcept
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

    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill( ScalarDot( v1, v2 ) );
    }

    // Cross

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Cross( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cross( v1.simd, v2.simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Cross( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cross( v1.simd, Traits::Load( v2.values.data( ) ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Cross( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cross( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Cross( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Cross( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
    }


    // LengthSquared

    template<Internal::SimdType T>
    inline T LengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HSum( Sqr( v ).simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT LengthSquared( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HSum( Sqr( v ).simd );
    }


    // Length

    template<Internal::SimdType T>
    inline T Length( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( LengthSquared( v ).simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Length( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( LengthSquared( v ).simd );
    }

    // Normalize

    template<Internal::SimdType T>
    inline T Normalize( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return v / Length( v );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Normalize( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Normalize( Traits::Load( v.values ) );
    }

    // ReciprocalLength

    template<Internal::SimdType T>
    inline T ReciprocalLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = typename Traits::Type;
        auto length = Length( v );
        return Traits::Div( Traits::Fill( static_cast< Type >(1.) ), length.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ReciprocalLength( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return ReciprocalLength( Traits::Load( v.values ) );
    }


    // DistanceSquared

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T DistanceSquared( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( v1.simd, v2.simd );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T DistanceSquared( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( v1.simd, Traits::Load( v2.values.data( ) ) );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T DistanceSquared( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( Traits::Load( v1.values.data( ) ), v2.simd );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT DistanceSquared( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        auto diff = Traits::Sub( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    // Distance

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline T Distance( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( DistanceSquared( v1, v2 ).simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T Distance( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( DistanceSquared( v1, v2 ).simd );
    }
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Distance( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( DistanceSquared( v1, v2 ).simd );
    }

    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Distance( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Sqrt( DistanceSquared( v1, v2 ).simd );
    }

    // DifferenceOfProducts

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T> && Internal::IsCompatible<S, U> && Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        auto v34 = v3 * v4;
        auto differenceOfProducts = FMA( v1, v2, -v34 );
        auto error = FMA( -v3, v4, v34 );
        return differenceOfProducts + error;
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( v1, v2, v3, Traits::Load( v4.values) );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( v1, v2, Traits::Load( v3.values ), v4  );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( v1, v2, Traits::Load( v3.values ), Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( v1, Traits::Load( v2.values ), v3, v4 );
    }
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( v1, Traits::Load( v2.values ), v3, Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( v1, Traits::Load( v2.values ), Traits::Load( v3.values ), v4 );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( v1, Traits::Load( v2.values ), Traits::Load( v3.values ), Traits::Load( v4.values ) );
    }
    //
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( Traits::Load( v1.values ), v2, v3, Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( Traits::Load( v1.values ), v2, Traits::Load( v3.values ), v4 );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( Traits::Load( v1.values ), v2, Traits::Load( v3.values ), Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( Traits::Load( v1.values ), Traits::Load( v2.values ), v3, v4 );
    }
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( Traits::Load( v1.values ), Traits::Load( v2.values ), v3, Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline V DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( Traits::Load( v1.values ), Traits::Load( v2.values ), Traits::Load( v3.values ), v4 );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline typename S::Simd DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return DifferenceOfProducts( Traits::Load( v1.values ), Traits::Load( v2.values ), Traits::Load( v3.values ), Traits::Load( v4.values ) );
    }

    // SumOfProducts

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::SimdType V >
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        auto v34 = v3 * v4;
        auto sumOfProducts = FMA( v1, v2, v34 );
        auto error = FMA( v3, v4, -v34 );
        return sumOfProducts + error;
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( v1, v2, v3, Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( v1, v2, Traits::Load( v3.values ), v4 );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( v1, v2, Traits::Load( v3.values ), Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( v1, Traits::Load( v2.values ), v3, v4 );
    }
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( v1, Traits::Load( v2.values ), v3, Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( v1, Traits::Load( v2.values ), Traits::Load( v3.values ), v4 );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( v1, Traits::Load( v2.values ), Traits::Load( v3.values ), Traits::Load( v4.values ) );
    }
    //
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( Traits::Load( v1.values ), v2, v3, Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( Traits::Load( v1.values ), v2, Traits::Load( v3.values ), v4 );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( Traits::Load( v1.values ), v2, Traits::Load( v3.values ), Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( Traits::Load( v1.values ), Traits::Load( v2.values ), v3, v4 );
    }
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( Traits::Load( v1.values ), Traits::Load( v2.values ), v3, Traits::Load( v4.values ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline V SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( Traits::Load( v1.values ), Traits::Load( v2.values ), Traits::Load( v3.values ), v4 );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline typename S::Simd SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        return SumOfProducts( Traits::Load( v1.values ), Traits::Load( v2.values ), Traits::Load( v3.values ), Traits::Load( v4.values ) );
    }


    template<Internal::SimdType T, typename ResultT = typename T::value_type >
    inline ResultT MinComponentValue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HorizontalMin( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::value_type>
    constexpr inline ResultT MinComponentValue( const T& v ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return std::min( v.x, v.y );
        }
        else if constexpr ( T::Size == 3 )
        {
            return std::min( v.x, v.y, v.z );
        }
        else
        {
            return std::min( v.x, v.y, v.z, v.w );
        }
    }

    template<Internal::SimdType T, typename ResultT = typename T::value_type >
    inline ResultT MaxComponentValue( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::HorizontalMax( v.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::value_type>
    constexpr inline ResultT MaxComponentValue( const T& v ) noexcept
    {
        if constexpr ( T::Size == 2 )
        {
            return std::max( v.x, v.y );
        }
        else if constexpr ( T::Size == 3 )
        {
            return std::max( v.x, v.y, v.z );
        }
        else
        {
            return std::max( v.x, v.y, v.z, v.w );
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

    template<Internal::SimdType T, typename ResultT = typename T::value_type >
    constexpr inline size_t MaxComponentIndex( const T& v ) noexcept
    {
        using TupleT = T::TupleType;
        TupleT tmp( v );
        return MaxComponentIndex( tmp );
    }

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

    template<Internal::SimdType T, typename ResultT = typename T::value_type >
    constexpr inline size_t MinComponentIndex( const T& v ) noexcept
    {
        using TupleT = T::TupleType;
        TupleT tmp( v );
        return MinComponentIndex( tmp );
    }

    
    
    template<>
    class Vector<float, 2> : public Tuple2<Vector<float, 2>, float>
    {
    public:
        using Base = Tuple2<Vector<float, 2>, float>;
        
        using Traits = Base::Traits;

        Vector( ) noexcept = default;
        Vector( float xv, float yv ) noexcept
            : Base( xv, yv )
        { }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        { }
    };

    


    
    template<>
    class Vector<double, 2> : public Tuple2<Vector<double, 2>, double>
    {
    public:
        using Base = Tuple2<Vector<double, 2>, double>;
        using Traits = Base::Traits;

        Vector( ) noexcept = default;
        Vector( double xv, double yv ) noexcept
            : Base( xv, yv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    template<>
    class Vector<float, 3> : public Tuple3<Vector<float, 3>,float>
    {
    public:
        using Base = Tuple3<Vector<float, 3>, float>;
        using Traits = Base::Traits;

        Vector( ) noexcept = default;
        Vector( float xv, float yv, float zv ) noexcept
            : Base( xv, yv, zv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    template<>
    class Vector<double, 3> : public Tuple3<Vector<double, 3>, double>
    {
    public:
        using Base = Tuple3<Vector<double, 3>, double>;
        using Traits = Base::Traits;

        Vector( ) noexcept = default;
        Vector( double xv, double yv, double zv ) noexcept
            : Base( xv, yv, zv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    template<>
    class Vector<float, 4> : public Tuple4<Vector<float, 4>,float>
    {
    public:
        using Base = Tuple4<Vector<float, 4>, float>;

        using Traits = Base::Traits;
        using Base::Size;
        using value_type = Base::value_type;

        Vector( ) noexcept = default;
        Vector( float xv, float yv, float zv, float wv ) noexcept
            : Base( xv, yv, zv, wv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        {
        }
    };



    template<>
    class Vector<double, 4> : public Tuple4<Vector<double, 4>, double>
    {
    public:
        using Base = Tuple4<Vector<double, 4>, double>;

        using Traits = Base::Traits;

        Vector( ) noexcept = default;
        Vector( double xv, double yv, double zv, double wv ) noexcept
            : Base( xv, yv, zv, wv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        {
        }
    };


    template<>
    class Vector<Int32, 2> : public Tuple2<Vector<Int32, 2>, Int32>
    {
    public:
        using Base = Tuple2<Vector<Int32, 2>, Int32>;

        using Traits = Base::Traits;

        Vector( ) noexcept = default;
        Vector( Int32 xv, Int32 yv ) noexcept
            : Base( xv, yv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    template<>
    class Vector<Int32, 3> : public Tuple3<Vector<Int32, 3>, Int32>
    {
    public:
        using Base = Tuple3<Vector<Int32, 3>, Int32>;

        using Traits = Base::Traits;

        Vector( ) noexcept = default;
        Vector( Int32 xv, Int32 yv, Int32 zv ) noexcept
            : Base( xv, yv, zv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    template<>
    class Vector<Int32, 4> : public Tuple4<Vector<Int32, 4>, Int32>
    {
    public:
        using Base = Tuple4<Vector<Int32, 4>, Int32>;

        using Traits = Base::Traits;

        Vector( ) noexcept = default;
        Vector( Int32 xv, Int32 yv, Int32 zv, Int32 wv ) noexcept
            : Base( xv, yv, zv, wv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other ) noexcept
            : Base( other )
        {
        }
    };


    // Vector2* Definitions
    using Vector2f = Vector<float,2>;
    using Vector2i = Vector<int,2>;

    // Vector3* Definitions
    using Vector3f = Vector<float,3>;
    using Vector3i = Vector<int, 3>;


    class Point2i : public Tuple2<Point2i, Int32>
    {
    public:
        using Base = Tuple2<Point2i, Int32>;

        using Traits = Base::Traits;

        Point2i( ) noexcept = default;
        Point2i( Int32 xv, Int32 yv ) noexcept
            : Base( xv, yv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Point2i( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    class Point3i : public Tuple3<Point3i, Int32>
    {
    public:
        using Base = Tuple3<Point3i, Int32>;

        using Traits = Base::Traits;

        Point3i( ) noexcept = default;
        Point3i( Int32 xv, Int32 yv, Int32 zv ) noexcept
            : Base( xv, yv, zv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Point3i( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    class Point2f : public Tuple2<Point2f, float>
    {
    public:
        using Base = Tuple2<Point2f, float>;
        using Traits = Base::Traits;

        Point2f( ) noexcept = default;
        Point2f( float xv, float yv ) noexcept
            : Base( xv, yv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Point2f( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    // https://www.iquilezles.org/www/articles/ibilinear/ibilinear.htm,
    // with a fix for perfect quads
    inline Point2f InvertBilinear( const Point2f& p, const std::span<const Point2f>& vert )
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



    class Point3f : public Tuple3<Point3f, float>
    {
    public:
        using Base = Tuple3<Point3f, float>;
        using Traits = Base::Traits;

        Point3f( ) noexcept = default;
        Point3f( float xv, float yv, float zv ) noexcept
            : Base( xv, yv, zv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Point3f( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    class Normal3f : public Tuple3<Normal3f, float>
    {
    public:
        using Base = Tuple3<Normal3f, float>;
        using Traits = Base::Traits;

        Normal3f( ) noexcept = default;
        Normal3f( float xv, float yv, float zv ) noexcept
            : Base( xv, yv, zv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Normal3f( const T& other ) noexcept
            : Base( other )
        {
        }
    };

    template<typename T>
        requires IsFloatingPoint<T>
    class Quaternion;

    
    template<typename T>
        requires IsFloatingPoint<T>
    class QuaternionSimd
    {
    public:
        using ValueType = T;
        using size_type = size_t;
        using value_type = ValueType;
        static constexpr size_type Size = 4;
        static constexpr bool Loaded = true;
        static constexpr bool Unloaded = false;

        using Traits = SIMD::Traits<ValueType, Size>;

        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;
        using Quaternion = Quaternion<ValueType>;

        SIMDType simd;

        QuaternionSimd() noexcept
            : simd(Traits::Zero())
        { }

        QuaternionSimd( const QuaternionSimd& other) noexcept
            : simd( other.simd )
        { }

        QuaternionSimd( SIMDType other ) noexcept
            : simd( other )
        {
        }

        QuaternionSimd( const Quaternion& quaternion ) noexcept;

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

        QuaternionSimd& operator = ( const Quaternion& quaternion ) noexcept;

        bool operator == ( const QuaternionSimd& other ) const noexcept
        {
            return Traits::Equals( simd, other.simd );
        }

        bool operator != ( const QuaternionSimd& other ) const noexcept
        {
            return Traits::Equals( simd, other.simd ) == false;
        }

        bool operator == ( const Quaternion& other ) const noexcept;
        bool operator != ( const Quaternion& other ) const noexcept;


        QuaternionSimd& operator += ( const QuaternionSimd& other ) noexcept
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }

        QuaternionSimd& operator += ( const Quaternion& quaternion ) noexcept;

        QuaternionSimd& operator -= ( const QuaternionSimd& other ) noexcept
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        QuaternionSimd& operator -= ( const Quaternion& quaternion ) noexcept;

        QuaternionSimd& operator *= ( const QuaternionSimd& other ) noexcept
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        QuaternionSimd& operator *= ( ValueType value ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Fill( value ) );
            return *this;
        }

        QuaternionSimd& operator *= ( const Quaternion& quaternion ) noexcept;

        QuaternionSimd& operator /= ( const QuaternionSimd& other ) noexcept
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }

        QuaternionSimd& operator /= ( ValueType value ) noexcept
        {
            simd = Traits::Div( simd, Traits::Fill( value ) );
            return *this;
        }

        QuaternionSimd& operator /= ( const Quaternion& quaternion ) noexcept;



    };

    template<typename T>
        requires IsFloatingPoint<T>
    class Quaternion 
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using ValueType = value_type;
        using SizeType = size_type;
        static constexpr size_type Size = 4;
        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;

        using Traits = SIMD::Traits<ValueType, Size>;
        using SIMDType = typename Traits::SIMDType;

        static constexpr size_type Capacity = Size;
        using ArrayType = typename Traits::ArrayType;

        using SimdImpl = QuaternionSimd<ValueType>;

        union
        {
            ArrayType values;
            struct
            {
                Vector<ValueType, 3> v;
                ValueType w;
            };
        };


        Quaternion( ) noexcept = default;
        Quaternion( ValueType xv, ValueType yv, ValueType zv, ValueType wv ) noexcept
            : values( { xv, yv, zv, wv } )
        {
        }

        Quaternion( const Vector<ValueType,3>& vv, ValueType wv ) noexcept
            : v( vv ), w( wv )
        {
        }

        template<typename U>
        Quaternion( const QuaternionSimd<U>& qsimd ) noexcept
            : values( Traits::ToArray( qsimd.simd ) )
        {
        }

        
        Quaternion( const Quaternion& other ) noexcept
            : values( other.values )
        {
        }

        template<typename U>
        Quaternion& operator = ( const QuaternionSimd<U>& qsimd ) noexcept
        {
            values = Traits::ToArray( qsimd.simd );
            return *this;
        }

        Quaternion& operator = ( const Quaternion& other ) noexcept
        {
            values = other.values;
            return *this;
        }

        template<typename U>
        bool operator == ( const QuaternionSimd<U>& other ) const noexcept
        {
            return Traits::Equals(Traits::Load( values.data( ) ), other.simd );
        }

        template<typename U>
        bool operator != ( const QuaternionSimd<U>& other ) const noexcept
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


    };

    static_assert( sizeof( Quaternion<float> ) == sizeof(std::array<float,4>));

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T>::QuaternionSimd( const Quaternion& quaternion ) noexcept
        : simd( Traits::Load( quaternion.values.data() ) )
    { }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T>& QuaternionSimd<T>::operator = ( const Quaternion& quaternion ) noexcept
    {
        simd = Traits::Load( quaternion.values.data( ) );
        return *this;
    }

    template<typename T>
        requires IsFloatingPoint<T>
    bool QuaternionSimd<T>::operator == ( const Quaternion& other ) const noexcept
    {
        return Traits::Equals( simd, Traits::Load( other.values.data( ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    bool QuaternionSimd<T>::operator != ( const Quaternion& other ) const noexcept
    {
        return Traits::Equals( simd, Traits::Load( other.values.data() ) ) == false;
    }


    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T>& QuaternionSimd<T>::operator += ( const Quaternion& quaternion ) noexcept
    {
        simd = Traits::Add( simd, Traits::Load( quaternion.values.data( ) ) );
        return *this;
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T>& QuaternionSimd<T>::operator -= ( const Quaternion& quaternion ) noexcept
    {
        simd = Traits::Sub( simd, Traits::Load( quaternion.values.data( ) ) );
        return *this;
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T>& QuaternionSimd<T>::operator *= ( const Quaternion& quaternion ) noexcept
    {
        simd = Traits::Mul( simd, Traits::Load( quaternion.values.data( ) ) );
        return *this;
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T>& QuaternionSimd<T>::operator /= ( const Quaternion& quaternion ) noexcept
    {
        simd = Traits::Div( simd, Traits::Load( quaternion.values.data( ) ) );
        return *this;
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator + ( const QuaternionSimd<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Add( q1.simd, q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator + ( const Quaternion<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Add( Traits::Load( q1.values.data()), q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator + ( const QuaternionSimd<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Add( q1.simd, Traits::Load( q2.values.data( ) ) );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator + ( const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Add( Traits::Load( q1.values.data( ) ), Traits::Load( q2.values.data( ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator - ( const QuaternionSimd<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Sub( q1.simd, q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator - ( const Quaternion<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Sub( Traits::Load( q1.values.data( ) ), q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator - ( const QuaternionSimd<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Sub( q1.simd, Traits::Load( q2.values.data( ) ) );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator - ( const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Sub( Traits::Load( q1.values.data( ) ), Traits::Load( q2.values.data( ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator * ( const QuaternionSimd<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( q1.simd, q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator * ( const Quaternion<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( Traits::Load( q1.values.data( ) ), q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator * ( const QuaternionSimd<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( q1.simd, Traits::Load( q2.values.data( ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator * ( T value, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( Traits::Fill( value ), q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator * ( const QuaternionSimd<T>& q1, T value ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( q1.simd, Traits::Fill( value ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator * ( const Quaternion<T>& q1, T value ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( Traits::Load( q1.values.data( ) ), Traits::Fill( value ) );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator * ( T value, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( Traits::Fill( value ), Traits::Load( q2.values.data( ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator * ( const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( Traits::Load( q1.values.data( ) ), Traits::Load( q2.values.data( ) ) );
    }

    

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator / ( const QuaternionSimd<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( q1.simd, q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator / ( const Quaternion<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( Traits::Load( q1.values.data( ) ), q2.simd );
    }
    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator / ( const QuaternionSimd<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( q1.simd, Traits::Load( q2.values.data( ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator / ( const QuaternionSimd<T>& q1, T value ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( q1.simd, Traits::Fill( value ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator / ( const Quaternion<T>& q1, T value ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( Traits::Load( q1.values.data( ) ), Traits::Fill( value ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    QuaternionSimd<T> operator / ( const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Mul( Traits::Load( q1.values.data( ) ), Traits::Load( q2.values.data( ) ) );
    }

    

    /*
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Cross( const Tuple3<DerivedT, FloatT>& v1, const Tuple3<DerivedT, FloatT>& v2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Cross( Traits::Load( v1.values.data() ), Traits::Load( v2.values.data( ) ) );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Cross( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v1, const Tuple3<DerivedT, FloatT>& v2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Cross( v1.simd, Traits::Load( v2.values.data( ) ) );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Cross( const Tuple3<DerivedT, FloatT>& v1, const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Cross( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Cross( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v1, const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Cross( v1.simd, v2.simd );
    }


    */

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
            auto halfLength = Sqrt( sz + sy + sz ) / static_cast< FloatT >( 2. );
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
            auto halfLength = Sqrt( sz + sy + sz ) / static_cast< FloatT >( 2. );
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

        template<typename MatrixT, typename TraitsT = typename MatrixT::Traits>
        struct alignas( TraitsT::AlignAs ) SquareMatrixSimd : public std::array<typename TraitsT::SIMDType, TraitsT::Size>, public MatrixSimdBase
        {
            using MatrixType = MatrixT;
            using Traits = typename MatrixType::Traits;
            using SIMDType = typename Traits::SIMDType;
            using value_type = typename MatrixType::value_type;
            static constexpr size_t Size = Traits::Size;
            static constexpr bool Loaded = true;
            static constexpr bool Unloaded = false;
            static constexpr bool IsSquareMatrix = true;
        };

        template<typename T>
        concept SquareMatrixSimdType = std::is_base_of_v<MatrixSimdBase,T>;

        template<typename T>
        concept SquareMatrixType = std::is_base_of_v<MatrixBase, T>;

        template<typename T1, typename T2>
        constexpr bool IsCompatibleMatrix =
            std::is_same_v<typename T1::Traits, typename T2::Traits> && T1::Size == T2::Size;

    }

    template <typename FloatT, size_t N>
    class SquareMatrix;
    template <typename FloatT, size_t N>
    SquareMatrix<FloatT, N> operator*( const SquareMatrix<FloatT, N>& matrix1, const SquareMatrix<FloatT, N>& matrix2 );


    // SquareMatrix Definition
    template <typename FloatT, size_t N>
    class SquareMatrix : public Internal::MatrixBase
    {
        template <typename FloatT, size_t N>
        friend SquareMatrix<FloatT, N> operator*( const SquareMatrix<FloatT, N>& matrix1, const SquareMatrix<FloatT, N>& matrix2 );
    public:
        using value_type = FloatT;
        static constexpr size_t Size = N;
        using Traits = SIMD::Traits<FloatT, Size>;
        using ArrayType = typename Traits::ArrayType;

        using Data = std::array<ArrayType, N>;
        using Simd = Internal::SquareMatrixSimd<SquareMatrix>;

        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;
        static constexpr bool IsSquareMatrix = true;
    private:
        static constexpr Data MakeDefaultValue( ) noexcept
        {
            Data m;
            for ( int i = 0; i < N; ++i )
            {
                for ( int j = 0; j < N; ++j )
                {
                    m[ i ][ j ] = ( i == j ) ? static_cast<value_type>( 1 ) : static_cast< value_type >( 0 );
                }
            }
            return m;
        }
        static constexpr Data DefaultValue = MakeDefaultValue( );
        Data data_ = DefaultValue;

    public:
        // SquareMatrix Public Methods
        constexpr static SquareMatrix Zero( ) noexcept
        {
            SquareMatrix m{};
            return m;
        }

        constexpr SquareMatrix( ) noexcept = default;

        SquareMatrix( const value_type (&mat)[ N ][ N ] )
            : data_( mat )
        {
        }

        SquareMatrix( const Simd& simd ) noexcept
        {
            for ( size_t i = 0; i < N; i++ )
            {
                data_[ i ] = Traits::ToArray( simd[i] );
            }
        }

        SquareMatrix( const Data& data ) noexcept
            : data_( data )
        {
        }

        SquareMatrix& operator = ( const Simd& simd ) noexcept
        {
            for ( size_t i = 0; i < N; i++ )
            {
                data_[ i ] = Traits::ToArray( simd[ i ] );
            }
            return *this;
        }

        SquareMatrix& operator = ( const Data& data ) noexcept
        {
            data_ = data;
            return *this;
        }

        /*
        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, value_type>
        SquareMatrix( const T& t );
        */

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
            InitDiagonalMatrix( std::make_index_sequence<N>( ), m.data_, v, args... );
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
        const value_type& operator[]( size_t row, size_t column ) const
        {
            return data_[ row ][ column ];
        }
        value_type& operator[]( size_t row, size_t column )
        {
            return data_[ row ][ column ];
        }

        Simd ToSimd( ) const noexcept
        {
            if constexpr ( N == 2 )
            {
                Simd result;
                result[ 0 ] = Traits::Load( data_[ 0 ] );
                result[ 1 ] = Traits::Load( data_[ 1 ] );
                return result;
            }
            else if constexpr ( N == 3 )
            {
                Simd result;
                result[ 0 ] = Traits::Load( data_[ 0 ] );
                result[ 1 ] = Traits::Load( data_[ 1 ] );
                result[ 2 ] = Traits::Load( data_[ 2 ] );
                return result;
            }
            else if constexpr ( N == 4 )
            {
                Simd result;
                result[ 0 ] = Traits::Load( data_[ 0 ] );
                result[ 1 ] = Traits::Load( data_[ 1 ] );
                result[ 2 ] = Traits::Load( data_[ 2 ] );
                result[ 3 ] = Traits::Load( data_[ 3 ] );
                return result;
            }
            else
            {
                // Not supported
            }
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

        std::string ToString( ) const;

    };


    // Addition

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1,T2>
    T1 operator+( const T1& m1, const T2& m2 ) noexcept
    {
        using Traits = typename T1::Traits;
        using Simd = T1;
        constexpr auto N = Traits::Size;
        if constexpr ( N == 2 )
        {
            Simd result;
            result[ 0 ] = Traits::Add( m1[ 0 ], m2[ 0 ] );
            result[ 1 ] = Traits::Add( m1[ 1 ], m2[ 1 ] );
            return result;

        }
        else if constexpr ( N == 3 )
        {
            Simd result;
            result[ 0 ] = Traits::Add( m1[ 0 ], m2[ 0 ] );
            result[ 1 ] = Traits::Add( m1[ 1 ], m2[ 1 ] );
            result[ 2 ] = Traits::Add( m1[ 2 ], m2[ 2 ] );
            return result;

        }
        else if constexpr ( N == 4 )
        {
            Simd result;
            result[ 0 ] = Traits::Add( m1[ 0 ], m2[ 0 ] );
            result[ 1 ] = Traits::Add( m1[ 1 ], m2[ 1 ] );
            result[ 2 ] = Traits::Add( m1[ 2 ], m2[ 2 ] );
            result[ 3 ] = Traits::Add( m1[ 3 ], m2[ 3 ] );
            return result;
        }
        else
        {
            // Not supported
        }
    }

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    T2 operator+( const T1& m1, const T2& m2 ) noexcept
    {
        return m1.ToSimd( ) + m2;
    }

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    T1 operator+( const T1& m1, const T2& m2 ) noexcept
    {
        return m1 + m2.ToSimd( );
    }

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    T1 operator+( const T1& m1, const T2& m2 ) noexcept
    {
        return m1.ToSimd( ) + m2.ToSimd( );
    }


    // Subtraction

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    T1 operator-( const T1& m1, const T2& m2 ) noexcept
    {
        using Traits = typename T1::Traits;
        using Simd = T1;
        constexpr auto N = Traits::Size;
        if constexpr ( N == 2 )
        {
            Simd result;
            result[ 0 ] = Traits::Sub( m1[ 0 ], m2[ 0 ] );
            result[ 1 ] = Traits::Sub( m1[ 1 ], m2[ 1 ] );
            return result;

        }
        else if constexpr ( N == 3 )
        {
            Simd result;
            result[ 0 ] = Traits::Sub( m1[ 0 ], m2[ 0 ] );
            result[ 1 ] = Traits::Sub( m1[ 1 ], m2[ 1 ] );
            result[ 2 ] = Traits::Sub( m1[ 2 ], m2[ 2 ] );
            return result;

        }
        else if constexpr ( N == 4 )
        {
            Simd result;
            result[ 0 ] = Traits::Sub( m1[ 0 ], m2[ 0 ] );
            result[ 1 ] = Traits::Sub( m1[ 1 ], m2[ 1 ] );
            result[ 2 ] = Traits::Sub( m1[ 2 ], m2[ 2 ] );
            result[ 3 ] = Traits::Sub( m1[ 3 ], m2[ 3 ] );
            return result;
        }
        else
        {
            // Not supported
        }
    }

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixSimdType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    T2 operator-( const T1& m1, const T2& m2 ) noexcept
    {
        return m1.ToSimd( ) - m2;
    }

    template<Internal::SquareMatrixSimdType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    T1 operator-( const T1& m1, const T2& m2 ) noexcept
    {
        return m1 - m2.ToSimd( );
    }

    template<Internal::SquareMatrixType T1, Internal::SquareMatrixType T2>
        requires Internal::IsCompatibleMatrix<T1, T2>
    T1 operator-( const T1& m1, const T2& m2 ) noexcept
    {
        return m1.ToSimd( ) - m2.ToSimd( );
    }


    // Multiplication

    template<Internal::SquareMatrixSimdType T1, typename T2>
        requires std::is_arithmetic_v<T2>
    T1 operator*( const T1& m, const T2 value ) noexcept
    {
        using Traits = typename T1::Traits;
        using Simd = T1;
        using ValueType = typename Traits::Type;
        constexpr auto N = Traits::Size;
        auto v = Traits::Fill( static_cast< ValueType >( value ) );
        
        if constexpr ( N == 2 )
        {
            Simd result;
            result[ 0 ] = Traits::Mul( m[ 0 ], v );
            result[ 1 ] = Traits::Mul( m[ 1 ], v );
            return result;

        }
        else if constexpr ( N == 3 )
        {
            Simd result;
            result[ 0 ] = Traits::Mul( m[ 0 ], v );
            result[ 1 ] = Traits::Mul( m[ 1 ], v );
            result[ 2 ] = Traits::Mul( m[ 2 ], v );
            return result;

        }
        else if constexpr ( N == 4 )
        {
            Simd result;
            result[ 0 ] = Traits::Mul( m[ 0 ], v );
            result[ 1 ] = Traits::Mul( m[ 1 ], v );
            result[ 2 ] = Traits::Mul( m[ 2 ], v );
            result[ 3 ] = Traits::Mul( m[ 3 ], v );
            return result;
        }
        else
        {
            // Not supported
        }
    }

    template<Internal::SquareMatrixType T1, typename T2>
        requires std::is_arithmetic_v<T2>
    T1 operator*( const T1& m, const T2 value ) noexcept
    {
        return m.ToSimd( ) * value;
    }

    template<Internal::SquareMatrixSimdType T1, typename T2>
        requires std::is_arithmetic_v<T2>
    T2 operator*( const T2 value, const T2& m ) noexcept
    {
        return m * value;
    }

    template<Internal::SquareMatrixType T1, typename T2>
        requires std::is_arithmetic_v<T2>
    T2 operator*( const T2 value, const T2& m ) noexcept
    {
        return m.ToSimd() * value;
    }


    template <>
    inline SquareMatrix<float, 4> operator*<float, 4>( const SquareMatrix<float, 4>& matrix1, const SquareMatrix<float, 4>& matrix2 )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        auto rmm1 = _mm256_castps128_ps256( Traits::Load( matrix1.data_[ 0 ].data( ) ) );
        rmm1 = _mm256_insertf128_ps( rmm1, Traits::Load( matrix1.data_[ 1 ].data( ) ), 1 );
        auto rmm2 = _mm256_castps128_ps256( Traits::Load( matrix1.data_[ 2 ].data( ) ) );
        rmm2 = _mm256_insertf128_ps( rmm2, Traits::Load( matrix1.data_[ 3 ].data( ) ), 1 );

        auto rmm3 = _mm256_castps128_ps256( Traits::Load( matrix2.data_[ 0 ].data( ) ) );
        rmm3 = _mm256_insertf128_ps( rmm3, Traits::Load( matrix2.data_[ 1 ].data( ) ), 1 );
        auto rmm4 = _mm256_castps128_ps256( Traits::Load( matrix2.data_[ 2 ].data( ) ) );
        rmm4 = _mm256_insertf128_ps( rmm4, Traits::Load( matrix2.data_[ 3 ].data( ) ), 1 );

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

        SquareMatrix<float, 4> result;
        Traits::Store( result.data_[ 0 ].data( ), _mm256_castps256_ps128( rmm1 ) );
        Traits::Store( result.data_[ 1 ].data( ), _mm256_extractf128_ps( rmm1, 1 ) );
        Traits::Store( result.data_[ 2 ].data( ), _mm256_castps256_ps128( rmm2 ) );
        Traits::Store( result.data_[ 3 ].data( ), _mm256_extractf128_ps( rmm2, 1 ) );
        return result;
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
            Simd result;
            result[ 0 ] = Traits::Div( m[ 0 ], v );
            result[ 1 ] = Traits::Div( m[ 1 ], v );
            return result;

        }
        else if constexpr ( N == 3 )
        {
            Simd result;
            result[ 0 ] = Traits::Div( m[ 0 ], v );
            result[ 1 ] = Traits::Div( m[ 1 ], v );
            result[ 2 ] = Traits::Div( m[ 2 ], v );
            return result;

        }
        else if constexpr ( N == 4 )
        {
            Simd result;
            result[ 0 ] = Traits::Div( m[ 0 ], v );
            result[ 1 ] = Traits::Div( m[ 1 ], v );
            result[ 2 ] = Traits::Div( m[ 2 ], v );
            result[ 3 ] = Traits::Div( m[ 3 ], v );
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
        return m.ToSimd( ) * value;
    }




    template <typename FloatT, size_t N>
    Vector<FloatT,N>::Simd Determinant( const SquareMatrix<FloatT,N>& matrix );

    template <typename FloatT, size_t N>
    FloatT ScalarDeterminant( const SquareMatrix<FloatT, N>& matrix );

    template <>
    inline Vector<float,4>::Simd Determinant<float, 4>( const SquareMatrix<float, 4>& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
        using Union = typename Traits::Union;
        using Select = typename Traits::Select;
        Traits::SIMDType sign( { { 1.0f, -1.0f, 1.0f, -1.0f } } );
        
        auto matrix2 = Traits::Load( matrix[ 2 ] );
        auto matrix3 = Traits::Load( matrix[ 3 ] );

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

        rmm3 = Traits::Load( matrix[ 1 ] );

        rmm0 = Traits::Swizzle<Select::Z, Select::W, Select::W, Select::W>( rmm3 );
        rmm1 = Traits::Swizzle<Select::Y, Select::Y, Select::Z, Select::Z>( rmm3 );
        rmm2 = Traits::Swizzle<Select::X, Select::X, Select::X, Select::Y>( rmm3 );
        
        auto rmm7 = Traits::Mul( rmm0, rmm4 );
        rmm7 = Traits::FNMAdd( rmm1, rmm5, rmm7 );
        rmm7 = Traits::FMAdd( rmm2, rmm6, rmm7 );

        rmm3 = Traits::Load( matrix[ 0 ] );
        rmm3 = Traits::Mul( rmm3, sign );

        return Traits::Dot( rmm3, rmm7 );
    }

    template <>
    inline float ScalarDeterminant<float, 4>( const SquareMatrix<float, 4>& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        return Traits::First( Determinant( matrix ).simd );
    }

    inline SquareMatrix<float, 4>::Simd Transpose( const SquareMatrix<float, 4>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using MatrixSimd = SquareMatrix<float, 4>::Simd;

        auto rmm1 = Traits::Shuffle<1, 0, 1, 0>( matrix[ 0 ], matrix[ 1 ] );
        auto rmm3 = Traits::Shuffle<3, 2, 3, 2>( matrix[ 0 ], matrix[ 1 ] );
        auto rmm2 = Traits::Shuffle<1, 0, 1, 0>( matrix[ 2 ], matrix[ 3 ] );
        auto rmm4 = Traits::Shuffle<3, 2, 3, 2>( matrix[ 2 ], matrix[ 3 ] );

        MatrixSimd result;

        result[ 0 ] = Traits::Shuffle<2, 0, 2, 0>( rmm1, rmm2 );
        result[ 1 ] = Traits::Shuffle<3, 1, 3, 1>( rmm1, rmm2 );
        result[ 2 ] = Traits::Shuffle<2, 0, 2, 0>( rmm3, rmm4 );
        result[ 3 ] = Traits::Shuffle<3, 1, 3, 1>( rmm3, rmm4 );

        return result;
    }

    inline SquareMatrix<float, 4>::Simd Transpose( const SquareMatrix<float, 4>& matrix )
    {
        return Transpose( matrix.ToSimd( ) );
    }


    inline SquareMatrix<float, 4>::Simd Inverse( const SquareMatrix<float, 4>::Simd& matrix, typename Vector<float, 4>::Simd* determinant = nullptr )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using MatrixSimd = SquareMatrix<float, 4>::Simd;

        auto vTemp1 = Traits::Shuffle<1, 0, 1, 0>( matrix[ 0 ], matrix[ 1 ] );
        auto vTemp3 = Traits::Shuffle<3, 2, 3, 2>( matrix[ 0 ], matrix[ 1 ] );
        auto vTemp2 = Traits::Shuffle<1, 0, 1, 0>( matrix[ 2 ], matrix[ 3 ] );
        auto vTemp4 = Traits::Shuffle<3, 2, 3, 2>( matrix[ 2 ], matrix[ 3 ] );

        MatrixSimd transposed;

        transposed[ 0 ] = Traits::Shuffle<2, 0, 2, 0>( vTemp1, vTemp2 );
        transposed[ 1 ] = Traits::Shuffle<3, 1, 3, 1>( vTemp1, vTemp2 );
        transposed[ 2 ] = Traits::Shuffle<2, 0, 2, 0>( vTemp3, vTemp4 );
        transposed[ 3 ] = Traits::Shuffle<3, 1, 3, 1>( vTemp3, vTemp4 );
        
        auto V00 = Traits::Swizzle<1, 1, 0, 0>( transposed[ 2 ] );
        auto V10 = Traits::Swizzle<3, 2, 3, 2>( transposed[ 3 ] );
        auto V01 = Traits::Swizzle<1, 1, 0, 0>( transposed[ 0 ] );
        auto V11 = Traits::Swizzle<3, 2, 3, 2>( transposed[ 1 ] );

        auto V02 = Traits::Shuffle<2, 0, 2, 0>( transposed[ 2 ], transposed[ 0 ] );
        auto V12 = Traits::Shuffle<3, 1, 3, 1>( transposed[ 3 ], transposed[ 1 ] );

        auto D0 = Traits::Mul( V00, V10 );
        auto D1 = Traits::Mul( V01, V11 );
        auto D2 = Traits::Mul( V02, V12 );


        V00 = Traits::Swizzle<3, 2, 3, 2>( transposed[ 2 ]);
        V10 = Traits::Swizzle<1, 1, 0, 0>( transposed[ 3 ]);
        V01 = Traits::Swizzle<3, 2, 3, 2>( transposed[ 0 ]);
        V11 = Traits::Swizzle<1, 1, 0, 0>( transposed[ 1 ]);

        V02 = Traits::Shuffle<3, 1, 3, 1>( transposed[ 2 ], transposed[ 0 ] );
        V12 = Traits::Shuffle<2, 0, 2, 0>( transposed[ 3 ], transposed[ 1 ] );


        D0 = Traits::FNMAdd( V00, V10, D0 );
        D1 = Traits::FNMAdd( V01, V11, D1 );
        D2 = Traits::FNMAdd( V02, V12, D2 );

        // V11 = D0Y,D0W,D2Y,D2Y
        V11 = Traits::Shuffle<1, 1, 3, 1>( D0, D2 );
        V00 = Traits::Swizzle<1, 0, 2, 1>( transposed[ 1 ] );
        V10 = Traits::Shuffle<0, 3, 0, 2>( V11, D0 );
        V01 = Traits::Swizzle<0, 1, 0, 2>( transposed[ 0 ] );
        V11 = Traits::Shuffle<2, 1, 2, 1>( V11, D0 );

        // V13 = D1Y,D1W,D2W,D2W
        auto V13 = Traits::Shuffle<3, 3, 3, 1>( D1, D2 );
        V02 = Traits::Swizzle<1, 0, 2, 1>( transposed[ 3 ] );
        V12 = Traits::Shuffle<0, 3, 0, 2>( V13, D1 );
        auto V03 = Traits::Swizzle<0, 1, 0, 2>( transposed[ 2 ] );
        V13 = Traits::Shuffle<2, 1, 2, 1>( V13, D1 );

        auto C0 = Traits::Mul( V00, V10 );
        auto C2 = Traits::Mul( V01, V11 );
        auto C4 = Traits::Mul( V02, V12 );
        auto C6 = Traits::Mul( V03, V13 );


        // V11 = D0X,D0Y,D2X,D2X
        V11 = Traits::Shuffle<0, 0, 1, 0>( D0, D2 );
        V00 = Traits::Swizzle<2, 1, 3, 2>( transposed[ 1 ] );
        V10 = Traits::Shuffle<2, 1, 0, 3>( D0, V11 );
        V01 = Traits::Swizzle<1, 3, 2, 3>( transposed[ 0 ] );
        V11 = Traits::Shuffle<0, 2, 1, 2>( D0, V11 );
        // V13 = D1X,D1Y,D2Z,D2Z
        V13 = Traits::Shuffle<2, 2, 1, 0>( D1, D2 );
        V02 = Traits::Swizzle<2, 1, 3, 2>( transposed[ 3 ] );
        V12 = Traits::Shuffle<2, 1, 0, 3>( D1, V13 );
        V03 = Traits::Swizzle<1, 3, 2, 3>( transposed[ 2 ] );
        V13 = Traits::Shuffle<0, 2, 1, 2>( D1, V13 );

        C0 = Traits::FNMAdd( V00, V10, C0 );
        C2 = Traits::FNMAdd( V01, V11, C2 );
        C4 = Traits::FNMAdd( V02, V12, C4 );
        C6 = Traits::FNMAdd( V03, V13, C6 );

        V00 = Traits::Swizzle<0, 3, 0, 3>( transposed[ 1 ] );
        // V10 = D0Z,D0Z,D2X,D2Y
        V10 = Traits::Shuffle<1, 0, 2, 2>( D0, D2 );
        V10 = Traits::Swizzle<0, 2, 3, 0>( V10 );
        V01 = Traits::Swizzle<2, 0, 3, 1>( transposed[ 0 ] );
        // V11 = D0X,D0W,D2X,D2Y
        V11 = Traits::Shuffle<1, 0, 3, 0>( D0, D2 );
        V11 = Traits::Swizzle<2, 1, 0, 3>( V11 );
        V02 = Traits::Swizzle<0, 3, 0, 3>( transposed[ 3 ] );
        // V12 = D1Z,D1Z,D2Z,D2W
        V12 = Traits::Shuffle<3, 2, 2, 2>( D1, D2 );
        V12 = Traits::Swizzle<0, 2, 3, 0>( V12 );
        V03 = Traits::Swizzle<2, 0, 3, 1>( transposed[ 2 ] );
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
        auto vTemp = Traits::Dot( C0, transposed[ 0 ] );
        if ( determinant != nullptr )
        {
            *determinant = vTemp;
        }
        vTemp = Traits::Div( Traits::Fill(1.f), vTemp );
        MatrixSimd result;
        result[ 0 ] = Traits::Mul( C0, vTemp );
        result[ 1 ] = Traits::Mul( C2, vTemp );
        result[ 2 ] = Traits::Mul( C4, vTemp );
        result[ 3 ] = Traits::Mul( C6, vTemp );
        return result;
    }

    inline SquareMatrix<float, 4>::Simd Inverse( const SquareMatrix<float, 4>& matrix, typename Vector<float, 4>::Simd* determinant = nullptr )
    {
        return Inverse( matrix.ToSimd( ), determinant );
    }


}


#endif
