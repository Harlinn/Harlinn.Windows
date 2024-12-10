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
        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;

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

        Tuple2( ) noexcept
            : x( static_cast< value_type >(0) ), y( static_cast< value_type >( 0 ) )
        {
        }

        Tuple2( value_type xv, value_type yv) noexcept
            : x( xv ), y(yv)
        { }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT> && std::is_same_v<T2, T>
        Tuple2( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) noexcept;
            
        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        DerivedT& operator = ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) noexcept;

        constexpr bool operator == ( const Tuple2& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y );
        }
        constexpr bool operator != ( const Tuple2& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y );
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator == ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) const noexcept;

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator != ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) const noexcept;

        Tuple2Simd<Tuple2<DerivedT, T>> operator-( ) const noexcept;

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
        static constexpr bool Loaded = true;
        static constexpr bool Unloaded = false;

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
            
        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;
            
        SIMDType simd;

        Tuple2Simd( ) noexcept
            : simd( Traits::Zero( ) )
        { }

        Tuple2Simd( SIMDType other ) noexcept
            : simd( other )
        { }

        Tuple2Simd( const TupleType& other ) noexcept
            : simd( Traits::Load( other.values.data() ) )
        { }

        bool operator == ( const Tuple2Simd& other ) const noexcept
        {
            return Traits::Equals( other.simd );
        }

        bool operator != ( const Tuple2Simd& other ) const noexcept
        {
            return Traits::Equals( other.simd ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator == ( const Tuple2<DerivedT, T>& other ) const noexcept
        {
            return Traits::Equals( Traits::Load( other.values ) );
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator != ( const Tuple2<DerivedT, T>& other ) const noexcept
        {
            return Traits::Equals( Traits::Load( other.values ) ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple2Simd& operator += ( const Tuple2<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Add( simd, Traits::Load( other.values.data() ) );
            return *this;
        }
        Tuple2Simd& operator += ( const Tuple2Simd& other ) noexcept
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple2Simd& operator -= ( const Tuple2<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple2Simd& operator -= ( const Tuple2Simd& other ) noexcept
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple2Simd& operator *= ( const Tuple2<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple2Simd& operator *= ( const Tuple2Simd& other ) noexcept
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple2Simd& operator /= ( const Tuple2<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Div( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple2Simd& operator /= ( const Tuple2Simd& other ) noexcept
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }


        void Assign( const Tuple2T& other ) noexcept
        {
            simd = Traits::Load( other.values.data( ) );
        }
        void Assign( value_type x, value_type y ) noexcept
        {
            simd = Traits::Set( y, x );
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

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    inline Tuple2<DerivedT, T>::Tuple2( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) noexcept
        : values(Traits::ToArray( other.simd ))
    { }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    DerivedT& Tuple2<DerivedT, T>::operator = ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) noexcept
    {
        values = Traits::ToArray( other.simd );
        return reinterpret_cast< DerivedT& >( *this );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple2<DerivedT, T>::operator == ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) const noexcept
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple2<DerivedT, T>::operator != ( const Tuple2Simd< Tuple2<DerivedT2, T2> >& other ) const noexcept
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
    }

    template<typename DerivedT, typename T>
    Tuple2Simd<Tuple2<DerivedT, T>> Tuple2<DerivedT, T>::operator-( ) const noexcept
    {
        return Traits::Negate( Traits::Load( values.data( ) ) );
    }


    // Addition
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator + ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
        
    // Subtraction
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator - ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Multiplication

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator * ( const Tuple2<DerivedT, NumberT>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Division

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, typename Tuple2Simd<Tuple2<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2<DerivedT, NumberT>& lhs, const Tuple2<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> operator / ( const Tuple2<DerivedT, NumberT>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs );
    }
     
    // Operations
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> HSum( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::HSum( t.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT HSum( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        return t.x + t.y;
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> HProd( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::HProd( t.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT HProd( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        return t.x * t.y;
    }


    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Abs( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Abs( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Abs( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Abs( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Min( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t1, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Min( const Tuple2<DerivedT, NumberT>& t1, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Min( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t1, const Tuple2<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Min( const Tuple2<DerivedT, NumberT>& t1, const Tuple2<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Max( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t1, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Max( const Tuple2<DerivedT, NumberT>& t1, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Max( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t1, const Tuple2<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Max( const Tuple2<DerivedT, NumberT>& t1, const Tuple2<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sqr( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Mul( t.simd, t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sqr( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Sqr( Traits::Load( t.values.data( ) ) );
    }


    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Ceil( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Ceil( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Ceil( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Ceil( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Floor( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Floor( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Floor( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Floor( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Round( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Round( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Round( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Round( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Trunc( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Trunc( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Trunc( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Trunc( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Lerp( NumberT t, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v0, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v1) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, v1.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Lerp( NumberT t, const Tuple2<DerivedT, NumberT>& v0, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v1 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), v1.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Lerp( NumberT t, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v0, Tuple2<DerivedT, NumberT>& v1 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, Traits::Load( v1.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Lerp( NumberT t, const Tuple2<DerivedT, NumberT>& v0, const Tuple2<DerivedT, NumberT>& v1 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), Traits::Load( v1.values.data( ) ) );
    }

    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Permute( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( v.simd );
    }
    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Permute( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( Traits::Load( v.values.data( ) ) );
    }

    // Clamp

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lowerBounds, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2<DerivedT, NumberT>& v, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lowerBounds, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v, const Tuple2<DerivedT, NumberT>& lowerBounds, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lowerBounds, const Tuple2<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2<DerivedT, NumberT>& v, const Tuple2<DerivedT, NumberT>& lowerBounds, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v, const Tuple2<DerivedT, NumberT>& lowerBounds, const Tuple2<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2<DerivedT, NumberT>& v, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& lowerBounds, const Tuple2<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Clamp( const Tuple2<DerivedT, NumberT>& v, const Tuple2<DerivedT, NumberT>& lowerBounds, const Tuple2<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    // Saturate
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Saturate( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Saturate( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Saturate( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // Sqrt
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sqrt( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sqrt( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sqrt( const Tuple2<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // FMA

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( NumberT a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( NumberT a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( NumberT a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( NumberT a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
        //return Traits::FMAdd( Traits::Set( a, a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, NumberT b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, NumberT b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, NumberT b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMA( const Tuple2<DerivedT, NumberT>& a, NumberT b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // FMSub

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( NumberT a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( NumberT a, const Tuple2<DerivedT, NumberT>& b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( NumberT a, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( NumberT a, const Tuple2<DerivedT, NumberT>& b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, NumberT b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, NumberT b, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& a, NumberT b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> FMSub( const Tuple2<DerivedT, NumberT>& a, NumberT b, const Tuple2<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // Sin

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sin( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Sin( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Sin( Traits::Load( v.values.data( ) ) );
    }

    // Cos

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Cos( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Cos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Cos( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Cos( Traits::Load( v.values.data( ) ) );
    }

    // Tan

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Tan( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Tan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Tan( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Tan( Traits::Load( v.values.data( ) ) );
    }

    // ASin

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ASin( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ASin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ASin( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ASin( Traits::Load( v.values.data( ) ) );
    }

    // ACos

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ACos( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ACos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ACos( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ACos( Traits::Load( v.values.data( ) ) );
    }

    // ATan

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan( Traits::Load( v.values.data( ) ) );
    }

    // ATan2

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan2( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& x, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan2( const Tuple2<DerivedT, NumberT>& x, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan2( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& x, const Tuple2<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATan2( const Tuple2<DerivedT, NumberT>& x, const Tuple2<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // SinH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> SinH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::SinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> SinH( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::SinH( Traits::Load( v.values.data( ) ) );
    }

    // CosH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> CosH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::CosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> CosH( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::CosH( Traits::Load( v.values.data( ) ) );
    }

    // TanH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> TanH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::TanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> TanH( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::TanH( Traits::Load( v.values.data( ) ) );
    }

    // ASinH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ASinH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ASinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ASinH( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ASinH( Traits::Load( v.values.data( ) ) );
    }

    // ACosH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ACosH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ACosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ACosH( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ACosH( Traits::Load( v.values.data( ) ) );
    }

    // ATanH

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATanH( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ATanH( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ATanH( Traits::Load( v.values.data( ) ) );
    }

    // Log

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log( Traits::Load( v.values.data( ) ) );
    }

    // Log1P

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log1P( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log1P( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log1P( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log1P( Traits::Load( v.values.data( ) ) );
    }

    // Log10

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log10( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log10( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log10( Traits::Load( v.values.data( ) ) );
    }

    // Log2

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log2( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Log2( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Log2( Traits::Load( v.values.data( ) ) );
    }

    // Exp

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp( Traits::Load( v.values.data( ) ) );
    }

    // Exp10

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp10( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp10( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp10( Traits::Load( v.values.data( ) ) );
    }

    // Exp2

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp2( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Exp2( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Exp2( Traits::Load( v.values.data( ) ) );
    }

    // ExpM1

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ExpM1( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> ExpM1( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( Traits::Load( v.values.data( ) ) );
    }

    // Pow

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Pow( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& base, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& exponent ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Pow( const Tuple2<DerivedT, NumberT>& base, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& exponent ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Pow( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& base, const Tuple2<DerivedT, NumberT>& exponent ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, Traits::Load( exponent.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Pow( const Tuple2<DerivedT, NumberT>& base, const Tuple2<DerivedT, NumberT>& exponent ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), Traits::Load( exponent.values.data( ) ) );
    }

    // Hypot

    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Hypot( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& x, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Hypot( const Tuple2<DerivedT, NumberT>& x, const Tuple2Simd<Tuple2<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Hypot( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& x, const Tuple2<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, Traits::Load( y.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple2Simd<Tuple2<DerivedT, NumberT>> Hypot( const Tuple2<DerivedT, NumberT>& x, const Tuple2<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    



    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        return std::min( v.x, v.y );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMax( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        return std::max( v.x, v.y );
    }

    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        return v.x < v.y ? 0 : 1;
    }
    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
    {
        Tuple2<DerivedT, NumberT> tmp( v );
        return MinComponentIndex( tmp );
    }

    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple2<DerivedT, NumberT>& v ) noexcept
    {
        return v.x > v.y ? 0 : 1;
    }
    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple2Simd<Tuple2<DerivedT, NumberT>>& v ) noexcept
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
        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;

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

        Tuple3( value_type xv, value_type yv, value_type zv ) noexcept
            : x( xv ), y( yv ), z( zv )
        {
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        Tuple3( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) noexcept;

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        DerivedT& operator = ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) noexcept;

        constexpr bool operator == ( const Tuple3& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z );
        }
        constexpr bool operator != ( const Tuple3& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y ) || !IsSameValue( z, other.z );
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator == ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) const noexcept;

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator != ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) const noexcept;

        Tuple3Simd<Tuple3<DerivedT, T>> operator-( ) const noexcept;

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


    template<typename Tuple3T>
    class Tuple3Simd
    {
    public:
        using size_type = size_t;
        using value_type = typename Tuple3T::value_type;
        static constexpr size_type Size = 3;
        static constexpr bool Loaded = true;
        static constexpr bool Unloaded = false;

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;
        SIMDType simd;

        Tuple3Simd( ) noexcept
            : simd( Traits::Zero( ) )
        {
        }

        Tuple3Simd( SIMDType other ) noexcept
            : simd( other )
        {
        }

        Tuple3Simd( const Tuple3T& other ) noexcept
            : simd( Traits::Load( other.values.data( ) ) )
        {
        }

        bool operator == ( const Tuple3Simd& other ) const noexcept
        {
            return Traits::Equals( other.simd );
        }

        bool operator != ( const Tuple3Simd& other ) const noexcept
        {
            return Traits::Equals( other.simd ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator == ( const Tuple3<DerivedT, T>& other ) const noexcept
        {
            return Traits::Equals( Traits::Load( other.values ) );
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator != ( const Tuple3<DerivedT, T>& other ) const noexcept
        {
            return Traits::Equals( Traits::Load( other.values ) ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple3Simd& operator += ( const Tuple3<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Add( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple3Simd& operator += ( const Tuple3Simd& other ) noexcept
        {
            simd = Traits::Add( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple3Simd& operator -= ( const Tuple3<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple3Simd& operator -= ( const Tuple3Simd& other ) noexcept
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple3Simd& operator *= ( const Tuple3<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple3Simd& operator *= ( const Tuple3Simd& other ) noexcept
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple3Simd& operator /= ( const Tuple3<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Div( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple3Simd& operator /= ( const Tuple3Simd& other ) noexcept
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }

        void Assign( const Tuple3T& other ) noexcept
        {
            simd = Traits::Load( other.values.data( ) );
        }
        void Assign( value_type x, value_type y, value_type z ) noexcept
        {
            simd = Traits::Set( z, y, x );
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

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    inline Tuple3<DerivedT, T>::Tuple3( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) noexcept
        : values( Traits::ToArray( other.simd ) ) 
    {
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    DerivedT& Tuple3<DerivedT, T>::operator = ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) noexcept
    {
        values = Traits::ToArray( other.simd );
        return reinterpret_cast< DerivedT& >( *this );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple3<DerivedT, T>::operator == ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) const noexcept
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple3<DerivedT, T>::operator != ( const Tuple3Simd< Tuple3<DerivedT2, T2> >& other ) const noexcept
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
    }

    template<typename DerivedT, typename T>
    Tuple3Simd<Tuple3<DerivedT, T>> Tuple3<DerivedT, T>::operator-( ) const noexcept
    {
        return Traits::Negate( Traits::Load( values.data( ) ) );
    }

    // Addition
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator + ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Subtraction
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator - ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Multiplication

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator * ( const Tuple3<DerivedT, NumberT>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Division

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, typename Tuple3Simd<Tuple3<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3<DerivedT, NumberT>& lhs, const Tuple3<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> operator / ( const Tuple3<DerivedT, NumberT>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Operations
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> HSum( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::HSum( t.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT HSum( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        return t.x + t.y + t.z;
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> HProd( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::HProd( t.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT HProd( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        return t.x * t.y * t.z;
    }


    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Abs( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Abs( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Abs( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Abs( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Min( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t1, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Min( const Tuple3<DerivedT, NumberT>& t1, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Min( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t1, const Tuple3<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Min( const Tuple3<DerivedT, NumberT>& t1, const Tuple3<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Max( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t1, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Max( const Tuple3<DerivedT, NumberT>& t1, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Max( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t1, const Tuple3<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Max( const Tuple3<DerivedT, NumberT>& t1, const Tuple3<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sqr( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Mul( t.simd, t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sqr( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Sqr( Traits::Load( t.values.data( ) ) );
    }


    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Ceil( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Ceil( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Ceil( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Ceil( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Floor( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
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
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Round( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Round( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Round( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Round( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Trunc( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Trunc( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Trunc( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Trunc( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Lerp( NumberT t, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v0, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v1 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, v1.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Lerp( NumberT t, const Tuple3<DerivedT, NumberT>& v0, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v1 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), v1.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Lerp( NumberT t, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v0, Tuple3<DerivedT, NumberT>& v1 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, Traits::Load( v1.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Lerp( NumberT t, const Tuple3<DerivedT, NumberT>& v0, const Tuple3<DerivedT, NumberT>& v1 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), Traits::Load( v1.values.data( ) ) );
    }

    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Permute( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( v.simd );
    }
    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Permute( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( Traits::Load( v.values.data( ) ) );
    }

    // Clamp

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lowerBounds, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3<DerivedT, NumberT>& v, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lowerBounds, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v, const Tuple3<DerivedT, NumberT>& lowerBounds, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lowerBounds, const Tuple3<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3<DerivedT, NumberT>& v, const Tuple3<DerivedT, NumberT>& lowerBounds, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v, const Tuple3<DerivedT, NumberT>& lowerBounds, const Tuple3<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3<DerivedT, NumberT>& v, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& lowerBounds, const Tuple3<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Clamp( const Tuple3<DerivedT, NumberT>& v, const Tuple3<DerivedT, NumberT>& lowerBounds, const Tuple3<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    // Saturate
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Saturate( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Saturate( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Saturate( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // Sqrt
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sqrt( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sqrt( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sqrt( const Tuple3<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // FMA

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( NumberT a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( NumberT a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( NumberT a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( NumberT a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        //return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, NumberT b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, NumberT b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, NumberT b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMA( const Tuple3<DerivedT, NumberT>& a, NumberT b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // FMSub

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( NumberT a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( NumberT a, const Tuple3<DerivedT, NumberT>& b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( NumberT a, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( NumberT a, const Tuple3<DerivedT, NumberT>& b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, NumberT b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, NumberT b, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& a, NumberT b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> FMSub( const Tuple3<DerivedT, NumberT>& a, NumberT b, const Tuple3<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // Sin

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sin( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Sin( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Sin( Traits::Load( v.values.data( ) ) );
    }

    // Cos

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Cos( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Cos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Cos( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Cos( Traits::Load( v.values.data( ) ) );
    }

    // Tan

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Tan( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Tan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Tan( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Tan( Traits::Load( v.values.data( ) ) );
    }

    // ASin

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ASin( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ASin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ASin( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ASin( Traits::Load( v.values.data( ) ) );
    }

    // ACos

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ACos( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ACos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ACos( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ACos( Traits::Load( v.values.data( ) ) );
    }

    // ATan

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan( Traits::Load( v.values.data( ) ) );
    }

    // ATan2

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan2( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& x, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan2( const Tuple3<DerivedT, NumberT>& x, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan2( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& x, const Tuple3<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATan2( const Tuple3<DerivedT, NumberT>& x, const Tuple3<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // SinH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> SinH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::SinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> SinH( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::SinH( Traits::Load( v.values.data( ) ) );
    }

    // CosH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> CosH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::CosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> CosH( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::CosH( Traits::Load( v.values.data( ) ) );
    }

    // TanH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> TanH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::TanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> TanH( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::TanH( Traits::Load( v.values.data( ) ) );
    }

    // ASinH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ASinH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ASinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ASinH( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ASinH( Traits::Load( v.values.data( ) ) );
    }

    // ACosH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ACosH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ACosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ACosH( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ACosH( Traits::Load( v.values.data( ) ) );
    }

    // ATanH

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATanH( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ATanH( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ATanH( Traits::Load( v.values.data( ) ) );
    }

    // Log

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log( Traits::Load( v.values.data( ) ) );
    }

    // Log1P

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log1P( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log1P( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log1P( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log1P( Traits::Load( v.values.data( ) ) );
    }

    // Log10

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log10( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log10( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log10( Traits::Load( v.values.data( ) ) );
    }

    // Log2

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log2( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Log2( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Log2( Traits::Load( v.values.data( ) ) );
    }

    // Exp

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp( Traits::Load( v.values.data( ) ) );
    }

    // Exp10

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp10( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp10( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp10( Traits::Load( v.values.data( ) ) );
    }

    // Exp2

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp2( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Exp2( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Exp2( Traits::Load( v.values.data( ) ) );
    }

    // ExpM1

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ExpM1( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> ExpM1( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( Traits::Load( v.values.data( ) ) );
    }

    // Pow

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Pow( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& base, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& exponent ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Pow( const Tuple3<DerivedT, NumberT>& base, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& exponent ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Pow( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& base, const Tuple3<DerivedT, NumberT>& exponent ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, Traits::Load( exponent.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Pow( const Tuple3<DerivedT, NumberT>& base, const Tuple3<DerivedT, NumberT>& exponent ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), Traits::Load( exponent.values.data( ) ) );
    }

    // Hypot

    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Hypot( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& x, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Hypot( const Tuple3<DerivedT, NumberT>& x, const Tuple3Simd<Tuple3<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Hypot( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& x, const Tuple3<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, Traits::Load( y.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple3Simd<Tuple3<DerivedT, NumberT>> Hypot( const Tuple3<DerivedT, NumberT>& x, const Tuple3<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }


    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        return std::min( v.x, std::min( v.y, v.z ) );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMax( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        return std::max( v.x, std::max( v.y, v.z ) );
    }

    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        return ( v.x < v.y ) ? ( ( v.x < v.z ) ? 0 : 2 ) : ( ( v.y < v.z ) ? 1 : 2 );
    }
    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
    {
        Tuple3<DerivedT, NumberT> tmp( v );
        return MinComponentIndex( tmp );
    }

    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple3<DerivedT, NumberT>& v ) noexcept
    {
        return ( v.x > v.y ) ? ( ( v.x > v.z ) ? 0 : 2 ) : ( ( v.y > v.z ) ? 1 : 2 );
    }
    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple3Simd<Tuple3<DerivedT, NumberT>>& v ) noexcept
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
        static constexpr bool Loaded = false;
        static constexpr bool Unloaded = true;

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

        Tuple4( ) noexcept
            : x( 0.0 ), y( 0.0 ), z( 0.0 ), w( 0.0 )
        {
        }

        Tuple4( value_type xv, value_type yv, value_type zv, value_type wv ) noexcept
            : x( xv ), y( yv ), z( zv ), w( wv )
        {
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        Tuple4( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) noexcept;

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        DerivedT& operator = ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) noexcept;

        constexpr bool operator == ( const Tuple4& other ) const noexcept
        {
            return IsSameValue( x, other.x ) && IsSameValue( y, other.y ) && IsSameValue( z, other.z ) && IsSameValue( w, other.w );
        }
        constexpr bool operator != ( const Tuple4& other ) const noexcept
        {
            return !IsSameValue( x, other.x ) || !IsSameValue( y, other.y ) || !IsSameValue( z, other.z ) || !IsSameValue( w, other.w );
        }

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator == ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) const noexcept;

        template<class DerivedT2, typename T2>
            requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
        bool operator != ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) const noexcept;

        Tuple4Simd<Tuple4<DerivedT, T>> operator-( ) const noexcept;

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


    template<typename Tuple4T>
    class Tuple4Simd
    {
    public:
        using size_type = size_t;
        using value_type = typename Tuple4T::value_type;
        static constexpr size_type Size = 4;
        static constexpr bool Loaded = true;
        static constexpr bool Unloaded = false;

        using Traits = SIMD::Traits<value_type, Size>;
        using SIMDType = typename Traits::SIMDType;
        static constexpr size_type Capacity = Traits::SIMDTypeCapacity;
            
        SIMDType simd;

        Tuple4Simd( ) noexcept
            : simd( Traits::Zero( ) )
        {
        }

        Tuple4Simd( SIMDType other ) noexcept
            : simd( other )
        {
        }

        Tuple4Simd( const Tuple4T& other ) noexcept
            : simd( Traits::Load( other.values.data( ) ) )
        {
        }

        bool operator == ( const Tuple4Simd& other ) const noexcept
        {
            return Traits::Equals( other.simd );
        }

        bool operator != ( const Tuple4Simd& other ) const noexcept
        {
            return Traits::Equals( other.simd ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator == ( const Tuple4<DerivedT, T>& other ) const noexcept
        {
            return Traits::Equals( simd, Traits::Load( other.values ) );
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        bool operator != ( const Tuple4<DerivedT, T>& other ) const noexcept
        {
            return Traits::Equals( simd, Traits::Load( other.values ) ) == false;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple4Simd& operator += ( const Tuple4<DerivedT, T>& other ) noexcept
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
        Tuple4Simd& operator -= ( const Tuple4<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple4Simd& operator -= ( const Tuple4Simd& other ) noexcept
        {
            simd = Traits::Sub( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple4Simd& operator *= ( const Tuple4<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple4Simd& operator *= ( const Tuple4Simd& other ) noexcept
        {
            simd = Traits::Mul( simd, other.simd );
            return *this;
        }

        template<class DerivedT, typename T>
            requires std::is_same_v<T, value_type>
        Tuple4Simd& operator /= ( const Tuple4<DerivedT, T>& other ) noexcept
        {
            simd = Traits::Div( simd, Traits::Load( other.values.data( ) ) );
            return *this;
        }
        Tuple4Simd& operator /= ( const Tuple4Simd& other ) noexcept
        {
            simd = Traits::Div( simd, other.simd );
            return *this;
        }

        void Assign( const Tuple4T& other ) noexcept
        {
            simd = Traits::Load( other.values.data( ) );
        }
        void Assign( value_type x, value_type y, value_type z, value_type w ) noexcept
        {
            simd = Traits::Set( w, z, y, x );
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

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    inline Tuple4<DerivedT, T>::Tuple4( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) noexcept
        : values( Traits::ToArray( other.simd ) ) 
    {
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    DerivedT& Tuple4<DerivedT, T>::operator = ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) noexcept
    {
        values = Traits::ToArray( other.simd );
        return reinterpret_cast< DerivedT& >( *this );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple4<DerivedT, T>::operator == ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) const noexcept
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd );
    }

    template<typename DerivedT, typename T>
    template<class DerivedT2, typename T2>
        requires std::is_same_v<DerivedT2, DerivedT>&& std::is_same_v<T2, T>
    bool Tuple4<DerivedT, T>::operator != ( const Tuple4Simd< Tuple4<DerivedT2, T2> >& other ) const noexcept
    {
        return Traits::Equal( Traits::Load( values.data( ) ), other.simd ) == false;
    }

    template<typename DerivedT, typename T>
    Tuple4Simd<Tuple4<DerivedT, T>> Tuple4<DerivedT, T>::operator-( ) const noexcept
    {
        return Traits::Negate( Traits::Load( values.data( ) ) );
    }

    // Addition
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator + ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Add( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Subtraction
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator - ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sub( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }

    // Multiplication

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( NumberT lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( lhs, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator * ( const Tuple4<DerivedT, NumberT>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Division

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs, rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, typename Tuple4Simd<Tuple4<DerivedT, NumberT>>::SIMDType rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4<DerivedT, NumberT>& lhs, const Tuple4<DerivedT, NumberT>& rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), Traits::Load( rhs.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( lhs.simd, rhs );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> operator / ( const Tuple4<DerivedT, NumberT>& lhs, NumberT rhs ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Div( Traits::Load( lhs.values.data( ) ), rhs );
    }

    // Operations
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> HSum( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::HSum( t.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT HSum( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        return t.x + t.y + t.z + t.w;
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> HProd( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::HProd( t.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT HProd( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        return t.x * t.y * t.z * t.w;
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Abs( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Abs( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Abs( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Abs( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Min( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t1, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Min( const Tuple4<DerivedT, NumberT>& t1, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Min( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t1, const Tuple4<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Min( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Min( const Tuple4<DerivedT, NumberT>& t1, const Tuple4<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Min( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Max( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t1, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Max( const Tuple4<DerivedT, NumberT>& t1, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t2 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), t2.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Max( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t1, const Tuple4<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Max( t1.simd, Traits::Load( t2.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Max( const Tuple4<DerivedT, NumberT>& t1, const Tuple4<DerivedT, NumberT>& t2 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Max( Traits::Load( t1.values.data( ) ), Traits::Load( t2.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sqr( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Mul( t.simd, t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sqr( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Sqr( Traits::Load( t.values.data( ) ) );
    }


    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Ceil( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Ceil( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Ceil( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Ceil( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Floor( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Floor( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Floor( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Floor( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Round( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Round( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Round( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Round( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Trunc( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Trunc( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Trunc( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Trunc( Traits::Load( t.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Lerp( NumberT t, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v0, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v1 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, v1.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Lerp( NumberT t, const Tuple4<DerivedT, NumberT>& v0, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v1 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), v1.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Lerp( NumberT t, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v0, Tuple4<DerivedT, NumberT>& v1 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, v0.simd, Traits::Load( v1.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Lerp( NumberT t, const Tuple4<DerivedT, NumberT>& v0, const Tuple4<DerivedT, NumberT>& v1 ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Lerp( t, Traits::Load( v0.values.data( ) ), Traits::Load( v1.values.data( ) ) );
    }

    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Permute( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( v.simd );
    }
    template<int shuffleMask, typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Permute( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Permute<shuffleMask>( Traits::Load( v.values.data( ) ) );
    }


    // Clamp

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lowerBounds, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4<DerivedT, NumberT>& v, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lowerBounds, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v, const Tuple4<DerivedT, NumberT>& lowerBounds, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lowerBounds, const Tuple4<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4<DerivedT, NumberT>& v, const Tuple4<DerivedT, NumberT>& lowerBounds, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& upperBounds ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), upperBounds.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v, const Tuple4<DerivedT, NumberT>& lowerBounds, const Tuple4<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( v.simd, Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4<DerivedT, NumberT>& v, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& lowerBounds, const Tuple4<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), lowerBounds.simd, Traits::Load( upperBounds.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Clamp( const Tuple4<DerivedT, NumberT>& v, const Tuple4<DerivedT, NumberT>& lowerBounds, const Tuple4<DerivedT, NumberT>& upperBounds ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Clamp( Traits::Load( v.values.data( ) ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
    }

    // Saturate
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Saturate( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Saturate( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Saturate( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // Sqrt
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sqrt( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sqrt( t.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sqrt( const Tuple4<DerivedT, NumberT>& t ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Saturate( Traits::Load( t.values.data( ) ) );
    }

    // FMA

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( NumberT a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( NumberT a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( NumberT a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( NumberT a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, NumberT b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, NumberT b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, NumberT b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMA( const Tuple4<DerivedT, NumberT>& a, NumberT b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // FMSub

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( NumberT a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( NumberT a, const Tuple4<DerivedT, NumberT>& b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( NumberT a, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( NumberT a, const Tuple4<DerivedT, NumberT>& b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Fill( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, NumberT b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, NumberT b, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), c.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& a, NumberT b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( a.simd, Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> FMSub( const Tuple4<DerivedT, NumberT>& a, NumberT b, const Tuple4<DerivedT, NumberT>& c ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( b ), Traits::Load( c.values.data( ) ) );
    }

    // Sin

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sin( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Sin( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Sin( Traits::Load( v.values.data( ) ) );
    }

    // Cos

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Cos( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Cos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Cos( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Cos( Traits::Load( v.values.data( ) ) );
    }

    // Tan

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Tan( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Tan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Tan( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Tan( Traits::Load( v.values.data( ) ) );
    }

    // ASin

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ASin( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ASin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ASin( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ASin( Traits::Load( v.values.data( ) ) );
    }

    // ACos

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ACos( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ACos( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ACos( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ACos( Traits::Load( v.values.data( ) ) );
    }

    // ATan

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan( Traits::Load( v.values.data( ) ) );
    }

    // ATan2

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan2( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& x, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan2( const Tuple4<DerivedT, NumberT>& x, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), y.simd );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan2( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& x, const Tuple4<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan2( x.simd, Traits::Load( y.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATan2( const Tuple4<DerivedT, NumberT>& x, const Tuple4<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATan2( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    // SinH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> SinH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::SinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> SinH( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::SinH( Traits::Load( v.values.data( ) ) );
    }

    // CosH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> CosH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::CosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> CosH( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::CosH( Traits::Load( v.values.data( ) ) );
    }

    // TanH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> TanH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::TanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> TanH( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::TanH( Traits::Load( v.values.data( ) ) );
    }

    // ASinH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ASinH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ASinH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ASinH( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ASinH( Traits::Load( v.values.data( ) ) );
    }

    // ACosH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ACosH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ACosH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ACosH( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ACosH( Traits::Load( v.values.data( ) ) );
    }

    // ATanH

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATanH( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATanH( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ATanH( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ATanH( Traits::Load( v.values.data( ) ) );
    }

    // Log

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log( Traits::Load( v.values.data( ) ) );
    }

    // Log1P

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log1P( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log1P( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log1P( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log1P( Traits::Load( v.values.data( ) ) );
    }

    // Log10

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log10( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log10( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log10( Traits::Load( v.values.data( ) ) );
    }

    // Log2

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log2( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Log2( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Log2( Traits::Load( v.values.data( ) ) );
    }

    // Exp

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp( Traits::Load( v.values.data( ) ) );
    }

    // Exp10

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp10( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp10( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp10( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp10( Traits::Load( v.values.data( ) ) );
    }

    // Exp2

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp2( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp2( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Exp2( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Exp2( Traits::Load( v.values.data( ) ) );
    }

    // ExpM1

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ExpM1( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> ExpM1( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::ExpM1( Traits::Load( v.values.data( ) ) );
    }

    // Pow

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Pow( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& base, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& exponent ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Pow( const Tuple4<DerivedT, NumberT>& base, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& exponent ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), exponent.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Pow( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& base, const Tuple4<DerivedT, NumberT>& exponent ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Pow( base.simd, Traits::Load( exponent.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Pow( const Tuple4<DerivedT, NumberT>& base, const Tuple4<DerivedT, NumberT>& exponent ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Pow( Traits::Load( base.values.data( ) ), Traits::Load( exponent.values.data( ) ) );
    }

    // Hypot

    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Hypot( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& x, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Hypot( const Tuple4<DerivedT, NumberT>& x, const Tuple4Simd<Tuple4<DerivedT, NumberT>>& y ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), y.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Hypot( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& x, const Tuple4<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Hypot( x.simd, Traits::Load( y.values.data( ) ) );
    }
    template<typename DerivedT, typename NumberT>
    inline Tuple4Simd<Tuple4<DerivedT, NumberT>> Hypot( const Tuple4<DerivedT, NumberT>& x, const Tuple4<DerivedT, NumberT>& y ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::Hypot( Traits::Load( x.values.data( ) ), Traits::Load( y.values.data( ) ) );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMin( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MinComponentValue( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        return std::min( v.x, v.y, v.z, v.w );
    }

    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        using Traits = typename Tuple4<DerivedT, NumberT>::Traits;
        return Traits::HorizontalMax( v.simd );
    }
    template<typename DerivedT, typename NumberT>
    inline NumberT MaxComponentValue( const Tuple4<DerivedT, NumberT>& v ) noexcept
    {
        return std::max( v.x, v.y, v.z, v.w );
    }

    template<typename DerivedT, typename NumberT>
    inline int MinComponentIndex( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
    {
        Tuple4<DerivedT, NumberT> tmp( v );
        return MinComponentIndex( tmp );
    }

    template<typename DerivedT, typename NumberT>
    inline int MaxComponentIndex( const Tuple4Simd<Tuple4<DerivedT, NumberT>>& v ) noexcept
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

    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> Dot( const Tuple2Simd<Tuple2<DerivedT, FloatT>>& v1, const Tuple2Simd<Tuple2<DerivedT, FloatT>>& v2 ) noexcept
    {
        using Traits = Tuple2<DerivedT, FloatT>::Traits;
        return Traits::Dot( v1.simd, v2.simd );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> Dot( const Tuple2<DerivedT, FloatT>& v1, const Tuple2Simd<Tuple2<DerivedT, FloatT>>& v2 ) noexcept
    {
        using Traits = Tuple2<DerivedT, FloatT>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> Dot( const Tuple2Simd<Tuple2<DerivedT, FloatT>>& v1, const Tuple2<DerivedT, FloatT>& v2 ) noexcept
    {
        using Traits = Tuple2<DerivedT, FloatT>::Traits;
        return Traits::Dot( v1.simd, Traits::Load( v2.values.data( ) ) );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> Dot( const Tuple2<DerivedT, FloatT>& v1, const Tuple2<DerivedT, FloatT>& v2 ) noexcept
    {
        using Traits = Tuple2<DerivedT, FloatT>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
    }

    
    template<>
    class Vector<double, 2> : public Tuple2<Vector<double, 2>, double>
    {
    public:
        using Base = Tuple2<Vector<double, 2>, double>;
        using Simd = Tuple2Simd<Vector<double, 2>>;
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
        using Simd = Tuple3Simd<Vector<float, 3>>;
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

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Dot( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v1, const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v2 ) noexcept
    {
        using Traits = Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Dot( v1.simd, v2.simd );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Dot( const Tuple3<DerivedT, FloatT>& v1, const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v2 ) noexcept
    {
        using Traits = Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Dot( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v1, const Tuple3<DerivedT, FloatT>& v2 ) noexcept
    {
        using Traits = Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Dot( v1.simd, Traits::Load( v2.values.data( ) ) );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Dot( const Tuple3<DerivedT, FloatT>& v1, const Tuple3<DerivedT, FloatT>& v2 ) noexcept
    {
        using Traits = Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
    }


    template<>
    class Vector<double, 3> : public Tuple3<Vector<double, 3>, double>
    {
    public:
        using Base = Tuple3<Vector<double, 3>, double>;
        using Simd = Tuple3Simd<Vector<double, 3>>;
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

        using Simd = Tuple4Simd<Vector<float, 4>>;
        using Traits = Base::Traits;

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
    
    inline Vector<float, 4>::Simd Dot( const Vector<float, 4>::Simd& v1, const Vector<float, 4>::Simd& v2 ) noexcept
    {
        using Traits = Vector<float, 4>::Traits;
        return Traits::Dot( v1.simd, v2.simd );
    }

    inline Vector<float, 4>::Simd Dot( const Vector<float, 4>& v1, const Vector<float, 4>::Simd& v2 ) noexcept
    {
        using Traits = Vector<float, 4>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    inline Vector<float, 4>::Simd Dot( const Vector<float, 4>::Simd& v1, const Vector<float, 4>& v2 ) noexcept
    {
        using Traits = Vector<float, 4>::Traits;
        return Traits::Dot( v1.simd, Traits::Load( v2.values.data( ) ) );
    }

    inline Vector<float, 4>::Simd Dot( const Vector<float, 4>& v1, const Vector<float, 4>& v2 ) noexcept
    {
        using Traits = Vector<float, 4>::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), Traits::Load( v2.values.data( ) ) );
    }

    template<>
    class Vector<double, 4> : public Tuple4<Vector<double, 4>, double>
    {
    public:
        using Base = Tuple4<Vector<double, 4>, double>;

        using Simd = Tuple4Simd<Vector<double, 4>>;
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

        using Simd = Tuple3Simd<Vector<Int32, 2>>;
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

        using Simd = Tuple3Simd<Vector<Int32, 3>>;
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

        using Simd = Tuple4Simd<Vector<Int32, 4>>;
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

        using Simd = Tuple3Simd<Point2i>;
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

        using Simd = Tuple3Simd<Point3i>;
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
        using Simd = Tuple3Simd<Point2f>;
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
        using Simd = Tuple3Simd<Point3f>;
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
        using Simd = Tuple3Simd<Normal3f>;
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





    
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> LengthSquared( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::HSum( Sqr( v ).simd );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> LengthSquared( const Tuple3<DerivedT, FloatT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        Tuple3Simd<Tuple3<DerivedT, FloatT>> vl( v );
        return Traits::HSum( Sqr( vl ).simd );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Length( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( LengthSquared(v).simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Length( const Tuple3<DerivedT, FloatT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( LengthSquared( v ).simd );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Normalize( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v ) noexcept
    {
        return v / Length( v );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Normalize( const Tuple3<DerivedT, FloatT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Normalize( Traits::Load( v.values ) );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> DistanceSquared( const Tuple2<DerivedT, FloatT>& p1, const Tuple2<DerivedT, FloatT>& p2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, FloatT>::Traits;
        auto diff = Traits::Sub( Traits::Load( p1.values.data( ) ), Traits::Load( p2.values.data( ) ) );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> DistanceSquared( const Tuple2Simd<Tuple2<DerivedT, FloatT>>& p1, const Tuple2<DerivedT, FloatT>& p2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, FloatT>::Traits;
        auto diff = Traits::Sub( p1.simd, Traits::Load( p2.values.data( ) ) );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> DistanceSquared( const Tuple2<DerivedT, FloatT>& p1, const Tuple2Simd<Tuple2<DerivedT, FloatT>>& p2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, FloatT>::Traits;
        auto diff = Traits::Sub( Traits::Load( p1.values.data( ) ), p2.simd );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> DistanceSquared( const Tuple2Simd<Tuple2<DerivedT, FloatT>>& p1, const Tuple2Simd<Tuple2<DerivedT, FloatT>>& p2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, FloatT>::Traits;
        auto diff = Traits::Sub( p1.simd, p2.simd );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> DistanceSquared( const Tuple3<DerivedT, FloatT>& p1, const Tuple3<DerivedT, FloatT>& p2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        auto diff = Traits::Sub( Traits::Load( p1.values.data( ) ), Traits::Load( p2.values.data( ) ) );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> DistanceSquared( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& p1, const Tuple3<DerivedT, FloatT>& p2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        auto diff = Traits::Sub( p1.simd, Traits::Load( p2.values.data( ) ) );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> DistanceSquared( const Tuple3<DerivedT, FloatT>& p1, const Tuple3Simd<Tuple3<DerivedT, FloatT>>& p2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        auto diff = Traits::Sub( Traits::Load( p1.values.data( ) ), p2.simd );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> DistanceSquared( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& p1, const Tuple3Simd<Tuple3<DerivedT, FloatT>>& p2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        auto diff = Traits::Sub( p1.simd, p2.simd );
        return Traits::HSum( Traits::Mul( diff, diff ) );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> Distance( const Tuple2<DerivedT, FloatT>& p1, const Tuple2<DerivedT, FloatT>& p2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> Distance( const Tuple2Simd<Tuple2<DerivedT, FloatT>>& p1, const Tuple2<DerivedT, FloatT>& p2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> Distance( const Tuple2<DerivedT, FloatT>& p1, const Tuple2Simd<Tuple2<DerivedT, FloatT>>& p2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple2Simd<Tuple2<DerivedT, FloatT>> Distance( const Tuple2Simd<Tuple2<DerivedT, FloatT>>& p1, const Tuple2Simd<Tuple2<DerivedT, FloatT>>& p2 ) noexcept
    {
        using Traits = typename Tuple2<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Distance( const Tuple3<DerivedT, FloatT>& p1, const Tuple3<DerivedT, FloatT>& p2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Distance( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& p1, const Tuple3<DerivedT, FloatT>& p2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Distance( const Tuple3<DerivedT, FloatT>& p1, const Tuple3Simd<Tuple3<DerivedT, FloatT>>& p2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> Distance( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& p1, const Tuple3Simd<Tuple3<DerivedT, FloatT>>& p2 ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        return Traits::Sqrt( DistanceSquared( p1, p2 ).simd );
    }

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


    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> ReciprocalLength( const Tuple3Simd<Tuple3<DerivedT, FloatT>>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        auto length = Length( v );
        return Traits::Div( Traits::Fill( 1.f ), length.simd );
    }
    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> ReciprocalLength( const Tuple3<DerivedT, FloatT>& v ) noexcept
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        Tuple3Simd<Tuple3<DerivedT, FloatT>> vl( v );
        return ReciprocalLength( vl );
    }

    template<typename DerivedT, typename FloatT>
    inline Tuple3Simd<Tuple3<DerivedT, FloatT>> AngleBetween( const Tuple3<DerivedT, FloatT>& v1, const Tuple3<DerivedT, FloatT>& v2 )
    {
        using Traits = typename Tuple3<DerivedT, FloatT>::Traits;
        using SimdT = Tuple3Simd<Tuple3<DerivedT, FloatT>>;
        SimdT vl1( v1 );
        SimdT vl2( v2 );
        Tuple3<DerivedT, FloatT> multiplied = vl1 * vl2;
        auto dotProduct = HSum( multiplied );

        if ( dotProduct < 0 )
        {
            return Traits::Fill( Constants<FloatT>::Pi - 2 * SafeASin( Traits::Lower( Length( v1 + v2 ).simd ) / 2 ) );
        }
        else
        {
            return Traits::Fill( 2 * SafeASin( Traits::Lower( Length( v2 - v1 ).simd ) / 2 ) );
        }


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
