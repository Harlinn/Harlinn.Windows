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

    
    template<typename Tuple2T>
    class Tuple2Simd;

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

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
        static constexpr size_type Capacity = Size;
        using ArrayType = std::array<value_type, Size>;
        /// <summary>
        /// The mathematical operations are performed using 
        /// this type which holds a SIMD vector.  
        /// </summary>
        using SimdImpl = Tuple2Simd<DerivedT>;

        union
        {
            ArrayType values;
            struct
            {
                value_type x, y;
            };
        };

        Tuple2( )
            : x( static_cast< value_type >(0) ), y( static_cast< value_type >( 0 ) )
        {
        }

        Tuple2( value_type xv, value_type yv)
            : x( xv ), y(yv)
        { }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT> && std::is_same_v<T2, T>
        Tuple2( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other );
            
        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        DerivedT& operator = ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other );

        constexpr bool operator == ( const Tuple2& other ) const
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y );
        }
        constexpr bool operator != ( const Tuple2& other ) const
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y );
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator == ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) const;

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator != ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) const;

        Tuple2Simd<Tuple2<DerivedT, T>> operator-( ) const;

        void Assign( value_type xv, value_type yv )
        {
            x = xv;
            y = yv;
        }
        void Assign( const ArrayType& src )
        {
            values = src;
        }
        void Assign( SIMDType src )
        {
            values = Traits::ToArray( src );
        }
    };

    /// <summary>
    /// <para>
    /// Holds the SIMD value for a Tuple2.
    /// </para>
    /// <para>
    /// Mathematical operations for a particular Tuple2
    /// derived type should generally be performed as 
    /// a sequence of operations on this type, not the Tuple2
    /// derived type, as this type represents the loaded
    /// state of the data from the Tuple2 type. 
    /// </para>
    /// </summary>
    /// <typeparam name="Tuple2T">
    /// A Tuple2 derived type.
    /// </typeparam>
    template<typename Tuple2T>
    class Tuple2Simd
    {
    public:
        using TupleType = Tuple2T;
        using value_type = typename TupleType::value_type;
        using size_type = size_t;
        static constexpr size_type Size = 2;

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
            
        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;
            
        SIMDType simd;

        Tuple2Simd( )
            : simd( Traits::Zero( ) )
        { }

        Tuple2Simd( SIMDType other )
            : simd( other )
        { }

        Tuple2Simd( const TupleType& other )
            : simd( Traits::Load( other.values.data() ) )
        { }

        bool operator == ( const Tuple2Simd& other ) const
        {
            return Traits::Equals( other.simd );
        }

        bool operator != ( const Tuple2Simd& other ) const
        {
            return Traits::Equals( other.simd ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator == ( const Tuple2<DerivedT, T>& other ) const
        {
            return Traits::Equals( Traits::Load( other.values ) );
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator != ( const Tuple2<DerivedT, T>& other ) const
        {
            return Traits::Equals( Traits::Load( other.values ) ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple2Simd& operator += ( const Tuple2<DerivedT, T>& other )
        {
            simd = Traits::Add( simd, Traits::Load( other.values.data() ) );
            return *this;
        }
        Tuple2Simd& operator += ( const Tuple2Simd& other )
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple2Simd& operator -= ( const Tuple2<DerivedT, T>& other )
        {
            simd = Traits::Sub( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple2Simd& operator -= ( const Tuple2Simd& other )
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple2Simd& operator *= ( const Tuple2<DerivedT, T>& other )
        {
            simd = Traits::Mul( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple2Simd& operator *= ( const Tuple2Simd& other )
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple2Simd& operator /= ( const Tuple2<DerivedT, T>& other )
        {
            simd = Traits::Div( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple2Simd& operator /= ( const Tuple2Simd& other )
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }


        void Assign( const Tuple2T& other )
        {
            simd = Traits::Load( other.values.data( ) );
        }
        void Assign( value_type x, value_type y )
        {
            simd = Traits::Set( y, x );
        }

        void Assign( SIMDType other )
        {
            simd = other;
        }

    };

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    inline Tuple2<DerivedT, T>::Tuple2( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other )
        : values(Traits::ToArray( other.simd ))
    { }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    DerivedT& Tuple2<DerivedT, T>::operator = ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other )
    {
        values = Traits::ToArray( other.simd );
        return reinterpret_cast< DerivedT& >( *this );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple2<DerivedT, T>::operator == ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) const
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple2<DerivedT, T>::operator != ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) const
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
    }

    template<typename DerivedT, typename T>
    Tuple2Simd<Tuple2<DerivedT, T>> Tuple2<DerivedT, T>::operator-( ) const
    {
        return Traits::Negate( Traits::Load( values.data( ) ) );
    }


    // Addition
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
        
    // Subtraction
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Multiplication

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2<DerivedT, NumberT>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Division

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2<DerivedT, NumberT>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs );
    }
     
    // Operations

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Abs( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Abs( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Abs( const Tuple2<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Abs( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Min( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t1, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Min( const Tuple2<DerivedT, NumberT>& t1, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Min( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t1, const Tuple2<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Min( const Tuple2<DerivedT, NumberT>& t1, const Tuple2<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Max( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t1, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Max( const Tuple2<DerivedT, NumberT>& t1, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Max( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t1, const Tuple2<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Max( const Tuple2<DerivedT, NumberT>& t1, const Tuple2<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sqr( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( t.simd, t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sqr( const Tuple2<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Sqr( Traits::Load( t.values.data( ) ) );
    }


    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Ceil( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Ceil( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Ceil( const Tuple2<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Ceil( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Floor( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Floor( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Floor( const Tuple2<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Floor( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Round( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Round( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Round( const Tuple2<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Round( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Trunc( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Trunc( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Trunc( const Tuple2<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Trunc( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Lerp( NumberT t, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v0, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v1)
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, v1.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Lerp( NumberT t, const Tuple2<DerivedT, NumberT>& v0, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v1 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), v1.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Lerp( NumberT t, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v0, Tuple2<DerivedT, NumberT>& v1 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, Traits::Load( v1.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Lerp( NumberT t, const Tuple2<DerivedT, NumberT>& v0, const Tuple2<DerivedT, NumberT>& v1 )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), Traits::Load( v1.values.data( ) ) );
    }

    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Permute( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( v.simd );
    }
    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Permute( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( Traits::Load( v.values.data( ) ) );
    }

    // Clamp

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lowerBounds, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2<DerivedT, NumberT>& v, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lowerBounds, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v, const Tuple2<DerivedT, NumberT>& lowerBounds, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lowerBounds, const Tuple2<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2<DerivedT, NumberT>& v, const Tuple2<DerivedT, NumberT>& lowerBounds, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v, const Tuple2<DerivedT, NumberT>& lowerBounds, const Tuple2<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2<DerivedT, NumberT>& v, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lowerBounds, const Tuple2<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2<DerivedT, NumberT>& v, const Tuple2<DerivedT, NumberT>& lowerBounds, const Tuple2<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    // Saturate
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Saturate( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Saturate( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Saturate( const Tuple2<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // Sqrt
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sqrt( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sqrt( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sqrt( const Tuple2<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // FMA

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( NumberT a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( NumberT a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( NumberT a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( NumberT a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, NumberT b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, NumberT b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, NumberT b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, NumberT b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // FMSub

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( NumberT a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( NumberT a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( NumberT a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( NumberT a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, NumberT b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, NumberT b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, NumberT b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, NumberT b, const Tuple2<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // Sin

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sin( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sin( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sin( Traits::Load( v.values.data( ) ) );
    }

    // Cos

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Cos( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Cos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Cos( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Cos( Traits::Load( v.values.data( ) ) );
    }

    // Tan

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Tan( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Tan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Tan( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Tan( Traits::Load( v.values.data( ) ) );
    }

    // ASin

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ASin( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ASin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ASin( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ASin( Traits::Load( v.values.data( ) ) );
    }

    // ACos

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ACos( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ACos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ACos( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ACos( Traits::Load( v.values.data( ) ) );
    }

    // ATan

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan( Traits::Load( v.values.data( ) ) );
    }

    // ATan2

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan2( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& x, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan2( const Tuple2<DerivedT, NumberT>& x, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan2( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& x, const Tuple2<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan2( const Tuple2<DerivedT, NumberT>& x, const Tuple2<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // SinH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> SinH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::SinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> SinH( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::SinH( Traits::Load( v.values.data( ) ) );
    }

    // CosH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> CosH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::CosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> CosH( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::CosH( Traits::Load( v.values.data( ) ) );
    }

    // TanH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> TanH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::TanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> TanH( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::TanH( Traits::Load( v.values.data( ) ) );
    }

    // ASinH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ASinH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ASinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ASinH( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ASinH( Traits::Load( v.values.data( ) ) );
    }

    // ACosH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ACosH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ACosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ACosH( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ACosH( Traits::Load( v.values.data( ) ) );
    }

    // ATanH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATanH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATanH( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATanH( Traits::Load( v.values.data( ) ) );
    }

    // Log

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log( Traits::Load( v.values.data( ) ) );
    }

    // Log1P

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log1P( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log1P( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log1P( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log1P( Traits::Load( v.values.data( ) ) );
    }

    // Log10

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log10( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log10( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log10( Traits::Load( v.values.data( ) ) );
    }

    // Log2

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log2( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log2( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log2( Traits::Load( v.values.data( ) ) );
    }

    // Exp

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp( Traits::Load( v.values.data( ) ) );
    }

    // Exp10

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp10( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp10( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp10( Traits::Load( v.values.data( ) ) );
    }

    // Exp2

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp2( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp2( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp2( Traits::Load( v.values.data( ) ) );
    }

    // ExpM1

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ExpM1( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ExpM1( const Tuple2<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( Traits::Load( v.values.data( ) ) );
    }

    // Pow

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Pow( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& base, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& exponent )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Pow( const Tuple2<DerivedT, NumberT>& base, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& exponent )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Pow( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& base, const Tuple2<DerivedT, NumberT>& exponent )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, Traits::Load( exponent.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Pow( const Tuple2<DerivedT, NumberT>& base, const Tuple2<DerivedT, NumberT>& exponent )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), Traits::Load( exponent.values.data( ) ) );
    }

    // Hypot

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Hypot( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& x, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Hypot( const Tuple2<DerivedT, NumberT>& x, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Hypot( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& x, const Tuple2<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, Traits::Load( y.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Hypot( const Tuple2<DerivedT, NumberT>& x, const Tuple2<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    



    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple2<DerivedT, NumberT>& v )
    {
        return std::min( v.x, v.y );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMax( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple2<DerivedT, NumberT>& v )
    {
        return std::max( v.x, v.y );
    }

    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple2<DerivedT, NumberT>& v )
    {
        return v.x < v.y ? 0 : 1;
    }
    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        Tuple2<DerivedT, NumberT> tmp( v );
        return MinComponentIndex( tmp );
    }

    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple2<DerivedT, NumberT>& v )
    {
        return v.x > v.y ? 0 : 1;
    }
    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v )
    {
        Tuple2<DerivedT, NumberT> tmp( v );
        return MaxComponentIndex( tmp );
    }


    template<typename Tuple3T>
    class Tuple3Simd;

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

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
            
        static constexpr size_type Capacity = Size;
        using ArrayType = std::array<value_type, Size>;
        using SimdImpl = Tuple3Simd<DerivedT>;

        union
        {
            ArrayType values;
            struct
            {
                value_type x, y, z;
            };
        };

        Tuple3( value_type xv, value_type yv, value_type zv )
            : x( xv ), y( yv ), z( zv )
        {
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        Tuple3( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other );

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        DerivedT& operator = ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other );

        constexpr bool operator == ( const Tuple3& other ) const
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z );
        }
        constexpr bool operator != ( const Tuple3& other ) const
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y ) || !IsSameValue( z, other.z );
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator == ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) const;

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator != ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) const;

        Tuple3Simd<Tuple3<DerivedT, T>> operator-( ) const;

        void Assign( value_type xv, value_type yv, value_type zv )
        {
            x = xv;
            y = yv;
            z = zv;
        }
        void Assign( const ArrayType& src )
        {
            values = src;
        }
        void Assign( SIMDType src )
        {
            values = Traits::ToArray( src );
        }

    };


    template<typename Tuple3T>
    class Tuple3Simd
    {
    public:
        using size_type = size_t;
        using value_type = typename Tuple3T::value_type;
        static constexpr size_type Size = 3;

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;
        SIMDType simd;

        Tuple3Simd( )
            : simd( Traits::Zero( ) )
        {
        }

        Tuple3Simd( SIMDType other )
            : simd( other )
        {
        }

        Tuple3Simd( const Tuple3T& other )
            : simd( Traits::Load( other.values.data( ) ) )
        {
        }

        bool operator == ( const Tuple3Simd& other ) const
        {
            return Traits::Equals( other.simd );
        }

        bool operator != ( const Tuple3Simd& other ) const
        {
            return Traits::Equals( other.simd ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator == ( const Tuple3<DerivedT, T>& other ) const
        {
            return Traits::Equals( Traits::Load( other.values ) );
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator != ( const Tuple3<DerivedT, T>& other ) const
        {
            return Traits::Equals( Traits::Load( other.values ) ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple3Simd& operator += ( const Tuple3<DerivedT, T>& other )
        {
            simd = Traits::Add( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple3Simd& operator += ( const Tuple3Simd& other )
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple3Simd& operator -= ( const Tuple3<DerivedT, T>& other )
        {
            simd = Traits::Sub( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple3Simd& operator -= ( const Tuple3Simd& other )
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple3Simd& operator *= ( const Tuple3<DerivedT, T>& other )
        {
            simd = Traits::Mul( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple3Simd& operator *= ( const Tuple3Simd& other )
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple3Simd& operator /= ( const Tuple3<DerivedT, T>& other )
        {
            simd = Traits::Div( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple3Simd& operator /= ( const Tuple3Simd& other )
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }

        void Assign( const Tuple3T& other )
        {
            simd = Traits::Load( other.values.data( ) );
        }
        void Assign( value_type x, value_type y, value_type z )
        {
            simd = Traits::Set( z, y, x );
        }

        void Assign( SIMDType other )
        {
            simd = other;
        }
    };

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    inline Tuple3<DerivedT, T>::Tuple3( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other )
        : values( Traits::ToArray( other.simd ) )
    {
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    DerivedT& Tuple3<DerivedT, T>::operator = ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other )
    {
        values = Traits::ToArray( other.simd );
        return reinterpret_cast< DerivedT& >( *this );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple3<DerivedT, T>::operator == ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) const
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple3<DerivedT, T>::operator != ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) const
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
    }

    template<typename DerivedT, typename T>
    Tuple3Simd<Tuple3<DerivedT, T>> Tuple3<DerivedT, T>::operator-( ) const
    {
        return Traits::Negate( Traits::Load( values.data( ) ) );
    }

    // Addition
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Subtraction
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Multiplication

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3<DerivedT, NumberT>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Division

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3<DerivedT, NumberT>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Operations

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Abs( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Abs( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Abs( const Tuple3<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Abs( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Min( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t1, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Min( const Tuple3<DerivedT, NumberT>& t1, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Min( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t1, const Tuple3<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Min( const Tuple3<DerivedT, NumberT>& t1, const Tuple3<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Max( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t1, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Max( const Tuple3<DerivedT, NumberT>& t1, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Max( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t1, const Tuple3<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Max( const Tuple3<DerivedT, NumberT>& t1, const Tuple3<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sqr( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( t.simd, t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sqr( const Tuple3<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Sqr( Traits::Load( t.values.data( ) ) );
    }


    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Ceil( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Ceil( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Ceil( const Tuple3<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Ceil( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Floor( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Floor( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Floor( const Tuple3<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Floor( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Round( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Round( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Round( const Tuple3<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Round( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Trunc( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Trunc( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Trunc( const Tuple3<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Trunc( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Lerp( NumberT t, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v0, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v1 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, v1.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Lerp( NumberT t, const Tuple3<DerivedT, NumberT>& v0, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v1 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), v1.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Lerp( NumberT t, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v0, Tuple3<DerivedT, NumberT>& v1 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, Traits::Load( v1.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Lerp( NumberT t, const Tuple3<DerivedT, NumberT>& v0, const Tuple3<DerivedT, NumberT>& v1 )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), Traits::Load( v1.values.data( ) ) );
    }

    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Permute( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( v.simd );
    }
    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Permute( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( Traits::Load( v.values.data( ) ) );
    }

    // Clamp

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lowerBounds, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3<DerivedT, NumberT>& v, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lowerBounds, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v, const Tuple3<DerivedT, NumberT>& lowerBounds, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lowerBounds, const Tuple3<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3<DerivedT, NumberT>& v, const Tuple3<DerivedT, NumberT>& lowerBounds, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v, const Tuple3<DerivedT, NumberT>& lowerBounds, const Tuple3<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3<DerivedT, NumberT>& v, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lowerBounds, const Tuple3<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3<DerivedT, NumberT>& v, const Tuple3<DerivedT, NumberT>& lowerBounds, const Tuple3<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    // Saturate
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Saturate( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Saturate( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Saturate( const Tuple3<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // Sqrt
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sqrt( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sqrt( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sqrt( const Tuple3<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // FMA

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( NumberT a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( NumberT a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( NumberT a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( NumberT a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, NumberT b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, NumberT b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, NumberT b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, NumberT b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // FMSub

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( NumberT a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( NumberT a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( NumberT a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( NumberT a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, NumberT b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, NumberT b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, NumberT b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, NumberT b, const Tuple3<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // Sin

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sin( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sin( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sin( Traits::Load( v.values.data( ) ) );
    }

    // Cos

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Cos( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Cos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Cos( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Cos( Traits::Load( v.values.data( ) ) );
    }

    // Tan

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Tan( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Tan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Tan( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Tan( Traits::Load( v.values.data( ) ) );
    }

    // ASin

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ASin( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ASin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ASin( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ASin( Traits::Load( v.values.data( ) ) );
    }

    // ACos

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ACos( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ACos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ACos( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ACos( Traits::Load( v.values.data( ) ) );
    }

    // ATan

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan( Traits::Load( v.values.data( ) ) );
    }

    // ATan2

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan2( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& x, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan2( const Tuple3<DerivedT, NumberT>& x, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan2( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& x, const Tuple3<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan2( const Tuple3<DerivedT, NumberT>& x, const Tuple3<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // SinH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> SinH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::SinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> SinH( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::SinH( Traits::Load( v.values.data( ) ) );
    }

    // CosH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> CosH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::CosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> CosH( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::CosH( Traits::Load( v.values.data( ) ) );
    }

    // TanH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> TanH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::TanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> TanH( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::TanH( Traits::Load( v.values.data( ) ) );
    }

    // ASinH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ASinH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ASinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ASinH( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ASinH( Traits::Load( v.values.data( ) ) );
    }

    // ACosH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ACosH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ACosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ACosH( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ACosH( Traits::Load( v.values.data( ) ) );
    }

    // ATanH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATanH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATanH( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATanH( Traits::Load( v.values.data( ) ) );
    }

    // Log

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log( Traits::Load( v.values.data( ) ) );
    }

    // Log1P

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log1P( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log1P( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log1P( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log1P( Traits::Load( v.values.data( ) ) );
    }

    // Log10

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log10( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log10( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log10( Traits::Load( v.values.data( ) ) );
    }

    // Log2

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log2( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log2( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log2( Traits::Load( v.values.data( ) ) );
    }

    // Exp

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp( Traits::Load( v.values.data( ) ) );
    }

    // Exp10

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp10( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp10( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp10( Traits::Load( v.values.data( ) ) );
    }

    // Exp2

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp2( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp2( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp2( Traits::Load( v.values.data( ) ) );
    }

    // ExpM1

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ExpM1( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ExpM1( const Tuple3<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( Traits::Load( v.values.data( ) ) );
    }

    // Pow

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Pow( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& base, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& exponent )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Pow( const Tuple3<DerivedT, NumberT>& base, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& exponent )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Pow( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& base, const Tuple3<DerivedT, NumberT>& exponent )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, Traits::Load( exponent.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Pow( const Tuple3<DerivedT, NumberT>& base, const Tuple3<DerivedT, NumberT>& exponent )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), Traits::Load( exponent.values.data( ) ) );
    }

    // Hypot

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Hypot( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& x, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Hypot( const Tuple3<DerivedT, NumberT>& x, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Hypot( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& x, const Tuple3<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, Traits::Load( y.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Hypot( const Tuple3<DerivedT, NumberT>& x, const Tuple3<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }


    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple3<DerivedT, NumberT>& v )
    {
        return std::min( v.x, std::min( v.y, v.z ) );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMax( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple3<DerivedT, NumberT>& v )
    {
        return std::max( v.x, std::max( v.y, v.z ) );
    }

    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple3<DerivedT, NumberT>& v )
    {
        return ( v.x < v.y ) ? ( ( v.x < v.z ) ? 0 : 2 ) : ( ( v.y < v.z ) ? 1 : 2 );
    }
    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        Tuple3<DerivedT, NumberT> tmp( v );
        return MinComponentIndex( tmp );
    }

    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple3<DerivedT, NumberT>& v )
    {
        return ( v.x > v.y ) ? ( ( v.x > v.z ) ? 0 : 2 ) : ( ( v.y > v.z ) ? 1 : 2 );
    }
    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v )
    {
        Tuple3<DerivedT, NumberT> tmp( v );
        return MaxComponentIndex( tmp );
    }


    template<typename Tuple4T>
    class Tuple4Simd;

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

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
            
        static constexpr size_type Capacity = Size;
        using ArrayType = typename Traits::ArrayType;

        using SimdImpl = Tuple4Simd<DerivedT>;

        union
        {
            ArrayType values;
            struct
            {
                value_type x, y, z, w;
            };
        };

        Tuple4( value_type xv, value_type yv, value_type zv, value_type wv )
            : x( xv ), y( yv ), z( zv ), w( wv )
        {
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        Tuple4( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other );

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        DerivedT& operator = ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other );

        constexpr bool operator == ( const Tuple4& other ) const
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z ) && IsSameValue( w, other.w );
        }
        constexpr bool operator != ( const Tuple4& other ) const
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y ) || !IsSameValue( z, other.z ) || !IsSameValue( w, other.w );
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator == ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) const;

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator != ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) const;

        Tuple4Simd<Tuple4<DerivedT, T>> operator-( ) const;

        void Assign( value_type xv, value_type yv, value_type zv, value_type wv )
        {
            x = xv;
            y = yv;
            z = zv;
            w = wv;
        }
        void Assign( const ArrayType& src )
        {
            values = src;
        }
        void Assign( SIMDType src )
        {
            values = Traits::ToArray( src );
        }

    };


    template<typename Tuple4T>
    class Tuple4Simd
    {
    public:
        using size_type = size_t;
        using value_type = typename Tuple4T::value_type;
        static constexpr size_type Size = 4;
        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;
            
        SIMDType simd;

        Tuple4Simd( )
            : simd( Traits::Zero( ) )
        {
        }

        Tuple4Simd( SIMDType other )
            : simd( other )
        {
        }

        Tuple4Simd( const Tuple4T& other )
            : simd( Traits::Load( other.values.data( ) ) )
        {
        }

        bool operator == ( const Tuple4Simd& other ) const
        {
            return Traits::Equals( other.simd );
        }

        bool operator != ( const Tuple4Simd& other ) const
        {
            return Traits::Equals( other.simd ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator == ( const Tuple4<DerivedT, T>& other ) const
        {
            return Traits::Equals( Traits::Load( other.values ) );
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator != ( const Tuple4<DerivedT, T>& other ) const
        {
            return Traits::Equals( Traits::Load( other.values ) ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple4Simd& operator += ( const Tuple4<DerivedT, T>& other )
        {
            simd = Traits::Add( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple4Simd& operator += ( const Tuple4Simd& other )
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple4Simd& operator -= ( const Tuple4<DerivedT, T>& other )
        {
            simd = Traits::Sub( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple4Simd& operator -= ( const Tuple4Simd& other )
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple4Simd& operator *= ( const Tuple4<DerivedT, T>& other )
        {
            simd = Traits::Mul( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple4Simd& operator *= ( const Tuple4Simd& other )
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple4Simd& operator /= ( const Tuple4<DerivedT, T>& other )
        {
            simd = Traits::Div( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple4Simd& operator /= ( const Tuple4Simd& other )
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }

        void Assign( const Tuple4T& other )
        {
            simd = Traits::Load( other.values.data( ) );
        }
        void Assign( value_type x, value_type y, value_type z, value_type w )
        {
            simd = Traits::Set( w, z, y, x );
        }

        void Assign( SIMDType other )
        {
            simd = other;
        }


    };

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    inline Tuple4<DerivedT, T>::Tuple4( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other )
        : values( Traits::ToArray( other.simd ) )
    {
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    DerivedT& Tuple4<DerivedT, T>::operator = ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other )
    {
        values = Traits::ToArray( other.simd );
        return reinterpret_cast< DerivedT& >( *this );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple4<DerivedT, T>::operator == ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) const
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple4<DerivedT, T>::operator != ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) const
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
    }

    template<typename DerivedT, typename T>
    Tuple4Simd<Tuple4<DerivedT, T>> Tuple4<DerivedT, T>::operator-( ) const
    {
        return Traits::Negate( Traits::Load( values.data( ) ) );
    }

    // Addition
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Subtraction
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Multiplication

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4<DerivedT, NumberT>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Division

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4<DerivedT, NumberT>& rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4<DerivedT, NumberT>& lhs, NumberT rhs )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Operations

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Abs( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Abs( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Abs( const Tuple4<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Abs( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Min( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t1, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Min( const Tuple4<DerivedT, NumberT>& t1, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Min( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t1, const Tuple4<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Min( const Tuple4<DerivedT, NumberT>& t1, const Tuple4<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Max( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t1, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Max( const Tuple4<DerivedT, NumberT>& t1, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t2 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Max( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t1, const Tuple4<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Max( const Tuple4<DerivedT, NumberT>& t1, const Tuple4<DerivedT, NumberT>& t2 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sqr( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( t.simd, t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sqr( const Tuple4<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Sqr( Traits::Load( t.values.data( ) ) );
    }


    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Ceil( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Ceil( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Ceil( const Tuple4<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Ceil( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Floor( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Floor( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Floor( const Tuple4<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Floor( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Round( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Round( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Round( const Tuple4<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Round( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Trunc( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Trunc( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Trunc( const Tuple4<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Trunc( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Lerp( NumberT t, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v0, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v1 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, v1.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Lerp( NumberT t, const Tuple4<DerivedT, NumberT>& v0, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v1 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), v1.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Lerp( NumberT t, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v0, Tuple4<DerivedT, NumberT>& v1 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, Traits::Load( v1.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Lerp( NumberT t, const Tuple4<DerivedT, NumberT>& v0, const Tuple4<DerivedT, NumberT>& v1 )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), Traits::Load( v1.values.data( ) ) );
    }

    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Permute( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( v.simd );
    }
    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Permute( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( Traits::Load( v.values.data( ) ) );
    }


    // Clamp

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lowerBounds, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4<DerivedT, NumberT>& v, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lowerBounds, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v, const Tuple4<DerivedT, NumberT>& lowerBounds, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lowerBounds, const Tuple4<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4<DerivedT, NumberT>& v, const Tuple4<DerivedT, NumberT>& lowerBounds, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& upperBounds )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v, const Tuple4<DerivedT, NumberT>& lowerBounds, const Tuple4<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4<DerivedT, NumberT>& v, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lowerBounds, const Tuple4<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4<DerivedT, NumberT>& v, const Tuple4<DerivedT, NumberT>& lowerBounds, const Tuple4<DerivedT, NumberT>& upperBounds )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    // Saturate
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Saturate( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Saturate( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Saturate( const Tuple4<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // Sqrt
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sqrt( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sqrt( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sqrt( const Tuple4<DerivedT, NumberT>& t )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // FMA

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( NumberT a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( NumberT a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( NumberT a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( NumberT a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, NumberT b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, NumberT b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, NumberT b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, NumberT b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // FMSub

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( NumberT a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( NumberT a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( NumberT a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( NumberT a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, NumberT b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, NumberT b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, NumberT b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, NumberT b, const Tuple4<DerivedT, NumberT>& c )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // Sin

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sin( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sin( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sin( Traits::Load( v.values.data( ) ) );
    }

    // Cos

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Cos( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Cos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Cos( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Cos( Traits::Load( v.values.data( ) ) );
    }

    // Tan

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Tan( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Tan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Tan( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Tan( Traits::Load( v.values.data( ) ) );
    }

    // ASin

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ASin( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ASin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ASin( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ASin( Traits::Load( v.values.data( ) ) );
    }

    // ACos

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ACos( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ACos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ACos( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ACos( Traits::Load( v.values.data( ) ) );
    }

    // ATan

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan( Traits::Load( v.values.data( ) ) );
    }

    // ATan2

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan2( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& x, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan2( const Tuple4<DerivedT, NumberT>& x, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan2( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& x, const Tuple4<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan2( const Tuple4<DerivedT, NumberT>& x, const Tuple4<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // SinH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> SinH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::SinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> SinH( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::SinH( Traits::Load( v.values.data( ) ) );
    }

    // CosH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> CosH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::CosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> CosH( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::CosH( Traits::Load( v.values.data( ) ) );
    }

    // TanH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> TanH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::TanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> TanH( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::TanH( Traits::Load( v.values.data( ) ) );
    }

    // ASinH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ASinH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ASinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ASinH( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ASinH( Traits::Load( v.values.data( ) ) );
    }

    // ACosH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ACosH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ACosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ACosH( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ACosH( Traits::Load( v.values.data( ) ) );
    }

    // ATanH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATanH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATanH( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATanH( Traits::Load( v.values.data( ) ) );
    }

    // Log

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log( Traits::Load( v.values.data( ) ) );
    }

    // Log1P

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log1P( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log1P( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log1P( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log1P( Traits::Load( v.values.data( ) ) );
    }

    // Log10

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log10( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log10( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log10( Traits::Load( v.values.data( ) ) );
    }

    // Log2

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log2( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log2( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log2( Traits::Load( v.values.data( ) ) );
    }

    // Exp

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp( Traits::Load( v.values.data( ) ) );
    }

    // Exp10

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp10( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp10( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp10( Traits::Load( v.values.data( ) ) );
    }

    // Exp2

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp2( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp2( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp2( Traits::Load( v.values.data( ) ) );
    }

    // ExpM1

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ExpM1( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ExpM1( const Tuple4<DerivedT, NumberT>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( Traits::Load( v.values.data( ) ) );
    }

    // Pow

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Pow( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& base, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& exponent )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Pow( const Tuple4<DerivedT, NumberT>& base, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& exponent )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Pow( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& base, const Tuple4<DerivedT, NumberT>& exponent )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, Traits::Load( exponent.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Pow( const Tuple4<DerivedT, NumberT>& base, const Tuple4<DerivedT, NumberT>& exponent )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), Traits::Load( exponent.values.data( ) ) );
    }

    // Hypot

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Hypot( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& x, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Hypot( const Tuple4<DerivedT, NumberT>& x, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& y )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Hypot( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& x, const Tuple4<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, Traits::Load( y.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Hypot( const Tuple4<DerivedT, NumberT>& x, const Tuple4<DerivedT, NumberT>& y )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple4<DerivedT, NumberT>& v )
    {
        return std::min( v.x, std::min( v.y, v.z ) );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMax( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple4<DerivedT, NumberT>& v )
    {
        return std::max( v.x, std::max( v.y, v.z ) );
    }

    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple4<DerivedT, NumberT>& v )
    {
        return ( v.x < v.y ) ? ( ( v.x < v.z ) ? 0 : 2 ) : ( ( v.y < v.z ) ? 1 : 2 );
    }
    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        Tuple4<DerivedT, NumberT> tmp( v );
        return MinComponentIndex( tmp );
    }

    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple4<DerivedT, NumberT>& v )
    {
        return ( v.x > v.y ) ? ( ( v.x > v.z ) ? 0 : 2 ) : ( ( v.y > v.z ) ? 1 : 2 );
    }
    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v )
    {
        Tuple4<DerivedT, NumberT> tmp( v );
        return MaxComponentIndex( tmp );
    }

    template<>
    class Vector<float, 2> : public Tuple2<Vector<float, 2>, float>
    {
    public:
        using Base = Tuple2<Vector<float, 2>, float>;
        using Simd = Tuple2Simd<Vector<float, 2>>;
        using Traits = Base::Traits;

        Vector( ) = default;
        Vector( float xv, float yv )
            : Base( xv, yv )
        { }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other )
            : Base( other )
        { }
    };

    inline Vector<float, 2>::Simd Dot( const Vector<float, 2>::Simd& v1, const Vector<float, 2>::Simd& v2 )
    {
        using Traits = Vector<float, 2>::Traits;
        return Traits::Dot( v1.simd, v2.simd );
    }

    inline Vector<float, 2>::Simd Dot( const Vector<float, 2>& v1, const Vector<float, 2>::Simd& v2 )
    {
        using Traits = Vector<float, 2>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data() ), v2.simd );
    }

    inline Vector<float, 2>::Simd Dot( const Vector<float, 2>::Simd& v1, const Vector<float, 2>& v2 )
    {
        using Traits = Vector<float, 2>::Traits;
        return Traits::Dot( v1.simd, Traits::Load( v2.values.data( ) ) );
    }

    inline Vector<float, 2>::Simd Dot( const Vector<float, 2>& v1, const Vector<float, 2>& v2 )
    {
        using Traits = Vector<float, 2>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
    }

    
    template<>
    class Vector<float, 3> : public Tuple3<Vector<float, 3>,float>
    {
    public:
        using Base = Tuple3<Vector<float, 3>, float>;
        using Simd = Tuple3Simd<Vector<float, 3>>;
        using Traits = Base::Traits;

        Vector( ) = default;
        Vector( float xv, float yv, float zv )
            : Base( xv, yv, zv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other )
            : Base( other )
        {
        }
    };

    inline Vector<float, 3>::Simd Dot( const Vector<float, 3>::Simd& v1, const Vector<float, 3>::Simd& v2 )
    {
        using Traits = Vector<float, 3>::Traits;
        return Traits::Dot( v1.simd, v2.simd );
    }

    inline Vector<float, 3>::Simd Dot( const Vector<float, 3>& v1, const Vector<float, 3>::Simd& v2 )
    {
        using Traits = Vector<float, 3>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    inline Vector<float, 3>::Simd Dot( const Vector<float, 3>::Simd& v1, const Vector<float, 3>& v2 )
    {
        using Traits = Vector<float, 3>::Traits;
        return Traits::Dot( v1.simd, Traits::Load( v2.values.data( ) ) );
    }

    inline Vector<float, 3>::Simd Dot( const Vector<float, 3>& v1, const Vector<float, 3>& v2 )
    {
        using Traits = Vector<float, 3>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
    }


    template<>
    class Vector<float, 4> : public Tuple4<Vector<float, 4>,float>
    {
    public:
        using Base = Tuple4<Vector<float, 4>, float>;

        using Simd = Tuple4Simd<Vector<float, 4>>;
        using Traits = Base::Traits;

        Vector( ) = default;
        Vector( float xv, float yv, float zv, float wv )
            : Base( xv, yv, zv, wv )
        {
        }

        template<typename T>
            requires std::is_same_v<typename T::SIMDType, typename Traits::SIMDType >
        Vector( const T& other )
            : Base( other )
        {
        }
    };
    
    inline Vector<float, 4>::Simd Dot( const Vector<float, 4>::Simd& v1, const Vector<float, 4>::Simd& v2 )
    {
        using Traits = Vector<float, 4>::Traits;
        return Traits::Dot( v1.simd, v2.simd );
    }

    inline Vector<float, 4>::Simd Dot( const Vector<float, 4>& v1, const Vector<float, 4>::Simd& v2 )
    {
        using Traits = Vector<float, 4>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    inline Vector<float, 4>::Simd Dot( const Vector<float, 4>::Simd& v1, const Vector<float, 4>& v2 )
    {
        using Traits = Vector<float, 4>::Traits;
        return Traits::Dot( v1.simd, Traits::Load( v2.values.data( ) ) );
    }

    inline Vector<float, 4>::Simd Dot( const Vector<float, 4>& v1, const Vector<float, 4>& v2 )
    {
        using Traits = Vector<float, 4>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
    }


    /*
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
    */

}


#endif
