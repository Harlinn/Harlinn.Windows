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
    class TupleSimd
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
        concept SimdType = T::Loaded;

        template<typename T>
        concept TupleType = T::Unloaded;

        template<typename SimdT1, typename SimdT2>
        constexpr bool IsCompatible =
            std::is_same_v<typename SimdT1::Traits, typename SimdT2::Traits>;
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
    class Tuple2
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
    class Tuple3
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
    class Tuple4
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
        return Traits::Sqr( t.simd, t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Sqr( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Sqr( Traits::Load( t.values.data( ) ) );
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
        return Traits::Trunc( t.simd );
    }
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Trunc( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Trunc( Traits::Load( t.values.data( ) ) );
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
        template <int N, typename FloatT>
        constexpr inline void InitMatrix( std::array<std::array<FloatT, N>, N>& m, int i, int j ) 
        {}

        template <int N, typename FloatT, typename... Args>
        constexpr inline void InitMatrix( std::array<std::array<FloatT, N>, N>& m, int i, int j, FloatT v, Args... args )
        {
            m[ i ][ j ] = v;
            if ( ++j == N )
            {
                ++i;
                j = 0;
            }
            InitMatrix<N>( m, i, j, args... );
        }

        template <int N, typename FloatT>
        constexpr inline void InitDiagonalMatrix( std::array<std::array<FloatT, N>, N>& m, int i ) {}

        template <int N, typename FloatT, typename... Args>
        constexpr inline void InitDiagonalMatrix( std::array<std::array<FloatT, N>, N>& m, int i, FloatT v, Args... args )
        {
            m[ i ][ i ] = v;
            InitDiagonalMatrix<N>( m, i + 1, args... );
        }
    }
    

    // SquareMatrix Definition
    template <typename FloatT, int N>
        requires IsFloatingPoint<FloatT> && ((N == 3)|| ( N == 4 ) )
    class SquareMatrix
    {
    public:
        using value_type = FloatT;
        using Data = std::array<std::array<value_type, N>, N>;
    private:
        Data m;
    public:
        // SquareMatrix Public Methods
        constexpr static SquareMatrix Zero( )
        {
            SquareMatrix m{};
            return m;
        }

        SquareMatrix( )
        {
            for ( int i = 0; i < N; ++i )
            {
                for ( int j = 0; j < N; ++j )
                {
                    m[ i ][ j ] = ( i == j ) ? 1 : 0;
                }
            }
        }
        SquareMatrix( const value_type mat[ N ][ N ] )
        {
            for ( int i = 0; i < N; ++i )
                for ( int j = 0; j < N; ++j )
                    m[ i ][ j ] = mat[ i ][ j ];
        }

        SquareMatrix( std::span<const FloatT> t );

        template <typename... Args>
        SquareMatrix( value_type v, Args... args )
        {
            static_assert( 1 + sizeof...( Args ) == N * N,
                "Incorrect number of values provided to SquareMatrix constructor" );
            Internal::InitMatrix<N>( m, 0, 0, v, args... );
        }
        template <typename... Args>
        static SquareMatrix Diag( value_type v, Args... args )
        {
            static_assert( 1 + sizeof...( Args ) == N,
                "Incorrect number of values provided to SquareMatrix::Diag" );
            SquareMatrix m;
            InitDiagonalMatrix<N>( m.m, 0, v, args... );
            return m;
        }

        SquareMatrix operator+( const SquareMatrix& m ) const
        {
            SquareMatrix r = *this;
            for ( int i = 0; i < N; ++i )
                for ( int j = 0; j < N; ++j )
                    r.m[ i ][ j ] += m.m[ i ][ j ];
            return r;
        }

        SquareMatrix operator*( value_type s ) const
        {
            SquareMatrix r = *this;
            for ( int i = 0; i < N; ++i )
                for ( int j = 0; j < N; ++j )
                    r.m[ i ][ j ] *= s;
            return r;
        }
        SquareMatrix operator/( value_type s ) const
        {
            SquareMatrix r = *this;
            for ( int i = 0; i < N; ++i )
                for ( int j = 0; j < N; ++j )
                    r.m[ i ][ j ] /= s;
            return r;
        }

        bool operator==( const SquareMatrix& m2 ) const
        {
            for ( int i = 0; i < N; ++i )
                for ( int j = 0; j < N; ++j )
                    if ( m[ i ][ j ] != m2.m[ i ][ j ] )
                        return false;
            return true;
        }

        bool operator!=( const SquareMatrix& m2 ) const
        {
            for ( int i = 0; i < N; ++i )
                for ( int j = 0; j < N; ++j )
                    if ( m[ i ][ j ] != m2.m[ i ][ j ] )
                        return true;
            return false;
        }

        bool operator<( const SquareMatrix& m2 ) const
        {
            for ( int i = 0; i < N; ++i )
            {
                for ( int j = 0; j < N; ++j )
                {
                    if ( m[ i ][ j ] < m2.m[ i ][ j ] )
                        return true;
                    if ( m[ i ][ j ] > m2.m[ i ][ j ] )
                        return false;
                }
            }
            return false;
        }

        bool IsIdentity( ) const;

        std::string ToString( ) const;

        std::span<const value_type> operator[]( int i ) const { return m[ i ]; }
        std::span<value_type> operator[]( int i ) { return std::span<value_type>( m[ i ] ); }

    
        
    };

}


#endif
