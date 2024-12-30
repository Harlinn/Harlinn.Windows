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


    template<typename TraitsT, typename TupleT>
    class TupleSimd : public Internal::TupleSimdBase
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

        TupleSimd( const TupleType& other ) noexcept
            : simd( Traits::Load( other.values.data( ) ) )
        {
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
        DerivedType& operator += ( const T& other ) noexcept
        {
            simd = Traits::Add( simd, Traits::Load( other.values.data( ) ) );
            return static_cast< DerivedType& >(*this);
        }
        DerivedType& operator += ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Add( simd, other.simd );
            return static_cast< DerivedType& >( *this );
        }

        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        DerivedType& operator -= ( const T& other ) noexcept
        {
            simd = Traits::Sub( simd, Traits::Load( other.values.data( ) ) );
            return static_cast< DerivedType& >( *this );
        }
        DerivedType& operator -= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Sub( simd, other.simd );
            return static_cast< DerivedType& >( *this );
        }

        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        DerivedType& operator *= ( const T& other ) noexcept
        {
            simd = Traits::Mul( simd, Traits::Load( other.values.data( ) ) );
            return static_cast< DerivedType& >( *this );
        }
        DerivedType& operator *= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Mul( simd, other.simd );
            return static_cast< DerivedType& >( *this );
        }

        template<Internal::TupleType T>
            requires std::is_same_v<Traits, typename T::Traits>
        DerivedType& operator /= ( const T& other ) noexcept
        {
            simd = Traits::Div( simd, Traits::Load( other.values.data( ) ) );
            return static_cast< DerivedType& >( *this );
        }
        DerivedType& operator /= ( const TupleSimd& other ) noexcept
        {
            simd = Traits::Div( simd, other.simd );
            return static_cast< DerivedType& >( *this );
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

        Tuple2( value_type xv, value_type yv) noexcept
            : x( xv ), y(yv)
        { }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple2( const U& other ) noexcept
            : values( Traits::ToArray( other.simd ) )
        {
        }

        template<Internal::TupleType U>
            requires std::is_same_v<Traits, typename U::Traits>
        Tuple2( const U& other ) noexcept
            : values( other.values )
        {
        }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        DerivedType& operator = ( const U& other ) noexcept
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

        DerivedType& operator += ( const Tuple2& other ) noexcept
        {
            x += other.x;
            y += other.y;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator += ( const value_type& value ) noexcept
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

        DerivedType& operator -= ( const Tuple2& other ) noexcept
        {
            x -= other.x;
            y -= other.y;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const value_type& value ) noexcept
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

        DerivedType& operator *= ( const Tuple2& other ) noexcept
        {
            x *= other.x;
            y *= other.y;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator *= ( const value_type& value ) noexcept
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

        DerivedType& operator /= ( const Tuple2& other ) noexcept
        {
            x /= other.x;
            y /= other.y;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator /= ( const value_type& value ) noexcept
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

        Tuple3( value_type xv, value_type yv, value_type zv ) noexcept
            : x( xv ), y( yv ), z( zv )
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

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        DerivedType& operator = ( const U& other ) noexcept
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

        DerivedType& operator += ( const Tuple3& other ) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator += ( const value_type& value ) noexcept
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

        DerivedType& operator -= ( const Tuple3& other ) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const value_type& value ) noexcept
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

        DerivedType& operator *= ( const Tuple3& other ) noexcept
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator *= ( const value_type& value ) noexcept
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

        DerivedType& operator /= ( const Tuple3& other ) noexcept
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator /= ( const value_type& value ) noexcept
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
            : x( 0.0 ), y( 0.0 ), z( 0.0 ), w( 0.0 )
        {
        }

        Tuple4( value_type xv, value_type yv, value_type zv, value_type wv ) noexcept
            : x( xv ), y( yv ), z( zv ), w( wv )
        {
        }

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
        {
        }

        template<Internal::SimdType U>
            requires std::is_same_v<Traits, typename U::Traits>
        DerivedType& operator = ( const U& other ) noexcept
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

        DerivedType& operator += ( const Tuple4& other ) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator += ( const value_type& value ) noexcept
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

        DerivedType& operator -= ( const Tuple4& other ) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator -= ( const value_type& value ) noexcept
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

        DerivedType& operator *= ( const Tuple4& other ) noexcept
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator *= ( const value_type& value ) noexcept
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

        DerivedType& operator /= ( const Tuple4& other ) noexcept
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return static_cast< DerivedType& >( *this );
        }

        DerivedType& operator /= ( const value_type& value ) noexcept
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
        return Traits::Sub( Traits::Load( lhs.values ), rhs.simd );
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
        return Traits::Abs( Traits::Load( t.values.data() ) );
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
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT> && Internal::IsCompatible<T, U> 
    inline T Lerp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Lerp( static_cast<Type>( a ), b.simd, c.simd );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<typename NumberT, Internal::SimdType T, Internal::TupleType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline T Lerp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Lerp( static_cast< Type >( a ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::SimdType U>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline U Lerp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Lerp( static_cast< Type >( a ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<typename NumberT, Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires std::is_arithmetic_v<NumberT>&& Internal::IsCompatible<T, U>
    inline ResultT Lerp( NumberT a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        using Type = Traits::Type;
        return Traits::Lerp( static_cast< Type >( a ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( a.simd, b.simd, c.simd );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( a.simd, b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( a.simd, Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline S Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( a.simd, Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
    }

    //

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( Traits::Load( a.values.data( ) ), b.simd, c.simd );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline T Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( Traits::Load( a.values.data( ) ), b.simd, Traits::Load( c.values.data( ) ) );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<T, U>
    inline U Lerp( const S& a, const T& b, const U& c ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Lerp( Traits::Load( a.values.data( ) ), Traits::Load( b.values.data( ) ), c.simd );
    }

    /// <summary>
    /// Calculates the linear interpolation between the
    /// the elements of a and the elements of b, for elements of
    /// c is inside [0,1), or the linear extrapolation for elements
    /// in c outside [0,1).
    /// </summary>
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
        return Traits::Clamp( Traits::Fill( v ), Traits::Load( lowerBounds.values.data( ) ), Traits::Load( upperBounds.values.data( ) ) );
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

    // ReciprocalSqrt

    /// <summary>
    /// Calculates the reciprocal square root of each element in the argument.
    /// </summary>
    template<Internal::SimdType T>
    inline T ReciprocalSqrt( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        return Traits::Div(Traits::Fill(Constants<FloatT>::One), Traits::Sqrt( t.simd ));
    }
    /// <summary>
    /// Calculates the reciprocal square root of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT ReciprocalSqrt( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        return Traits::Div( Traits::Fill( Constants<FloatT>::One ), Traits::Sqrt( Traits::Load( t.values ) ) );
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
        return Traits::Div( Traits::Fill( Constants<FloatT>::One ), t.simd );
    }

    /// <summary>
    /// Calculates the reciprocal of each element in the argument.
    /// </summary>
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Reciprocal( const T& t ) noexcept
    {
        using Traits = typename T::Traits;
        using FloatT = typename Traits::Type;
        return Traits::Div( Traits::Fill( Constants<FloatT>::One ), Traits::Load( t.values ) );
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
        return Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd );
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
        return Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
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
        return Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
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
        return Traits::FMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMSub( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd );
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
        return Traits::FMSub( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
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
        return Traits::FMSub( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
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
        return Traits::FMSub( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMSub( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FMSub( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FMSub( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMAddSub( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd );
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
        return Traits::FMAddSub( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
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
        return Traits::FMAddSub( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
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
        return Traits::FMAddSub( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMAddSub( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FMAddSub( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMAddSub( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FMAddSub( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMSubAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd );
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
        return Traits::FMSubAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
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
        return Traits::FMSubAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
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
        return Traits::FMSubAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMSubAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FMSubAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FMSubAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FMSubAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FNMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd );
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
        return Traits::FNMAdd( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
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
        return Traits::FNMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
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
        return Traits::FNMAdd( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FNMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FNMAdd( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FNMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FNMAdd( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FNMSub( Traits::Fill( static_cast< Type >( a ) ), b.simd, c.simd );
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
        return Traits::FNMSub( Traits::Fill( static_cast< Type >( a ) ), b.simd, Traits::Load( c.values.data( ) ) );
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
        return Traits::FNMSub( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), c.simd );
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
        return Traits::FNMSub( Traits::Fill( static_cast< Type >( a ) ), Traits::Load( b.values.data( ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FNMSub( a.simd, Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FNMSub( a.simd, Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::FNMSub( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), c.simd );
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
        return Traits::FNMSub( Traits::Load( a.values.data( ) ), Traits::Fill( static_cast< Type >( b ) ), Traits::Load( c.values.data( ) ) );
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
        return Traits::Sin( Traits::Load( v.values.data( ) ) );
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
        return Traits::Cos( Traits::Load( v.values.data( ) ) );
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
    template<Internal::TupleType T, typename ResultT = typename T::Simd>
    inline ResultT Tan( const T& v ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Tan( Traits::Load( v.values.data( ) ) );
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
        auto result = Traits::Round( Traits::Mul( angles.simd, Traits::Fill( Constants<FloatT>::Inv2Pi ) ) );
        return Traits::FNMAdd( result, Traits::Fill( Constants<FloatT>::PiTimes2 ), angles.simd );
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
        return Traits::Sub( result, offset );
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
        return Traits::Sub( result, offset );
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
        return Traits::FMAdd( secondTangent.simd, t1, result );
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
        return Traits::Dot( v1.simd, Traits::Load( v2.values.data( ) ) );
    }
    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T Dot( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Dot( Traits::Load( v1.values.data( ) ), v2.simd );
    }

    // ScalarDot

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Dot(v1,v2).simd );
    }

    template<Internal::TupleType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Dot( v1, v2 ).simd );
    }

    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline typename T::value_type ScalarDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( Dot( v1, v2 ).simd );
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

    /// <summary>
    /// Calculates the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT Dot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Fill( ScalarDot( v1, v2 ) );
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
        return Traits::Abs( Dot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline T AbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Dot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline T AbsDot( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Dot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U, typename ResultT = typename T::Simd>
        requires Internal::IsCompatible<T, U>
    inline ResultT AbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::Abs( Dot( v1, v2 ).simd );
    }

    // ScalarAbsDot

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarAbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( AbsDot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::SimdType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarAbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( AbsDot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType U, Internal::SimdType T>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarAbsDot( const U& v1, const T& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( AbsDot( v1, v2 ).simd );
    }

    /// <summary>
    /// Calculates the absolute value of the dot product between v1 and v2.
    /// </summary>
    template<Internal::TupleType T, Internal::TupleType U>
        requires Internal::IsCompatible<T, U>
    inline auto ScalarAbsDot( const T& v1, const U& v2 ) noexcept
    {
        using Traits = typename T::Traits;
        return Traits::First( AbsDot( v1, v2 ).simd );
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
        return Traits::Div( Traits::Fill( static_cast< Type >(1.) ), length.simd );
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

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename V::Simd;
        return DifferenceOfProducts( v1, v2, v3, Simd( Traits::Load( v4.values) ) );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename U::Simd;
        return DifferenceOfProducts( v1, v2, Simd( Traits::Load( v3.values ) ), v4  );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename U::Simd;
        return DifferenceOfProducts( v1, v2, Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return DifferenceOfProducts( v1, Simd( Traits::Load( v2.values ) ), v3, v4 );
    }
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return DifferenceOfProducts( v1, Simd( Traits::Load( v2.values ) ), v3, Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return DifferenceOfProducts( v1, Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), v4 );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return DifferenceOfProducts( v1, Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }
    //
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), v2, v3, Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), v2, Simd( Traits::Load( v3.values ) ), v4 );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), v2, Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), v3, v4 );
    }
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), v3, Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline V DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), v4 );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline typename S::Simd DifferenceOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return DifferenceOfProducts( Simd(Traits::Load( v1.values )), Simd( Traits::Load( v2.values )), Simd( Traits::Load( v3.values )), Simd( Traits::Load( v4.values ) ) );
    }

    // SumOfProducts

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

    template<Internal::SimdType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename V::Simd;
        return SumOfProducts( v1, v2, v3, Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename U::Simd;
        return SumOfProducts( v1, v2, Simd( Traits::Load( v3.values ) ), v4 );
    }

    template<Internal::SimdType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename U::Simd;
        return SumOfProducts( v1, v2, Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return SumOfProducts( v1, Simd( Traits::Load( v2.values ) ), v3, v4 );
    }
    template<Internal::SimdType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return SumOfProducts( v1, Simd( Traits::Load( v2.values ) ), v3, Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return SumOfProducts( v1, Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), v4 );
    }

    template<Internal::SimdType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline S SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename T::Simd;
        return SumOfProducts( v1, Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }
    //
    template<Internal::TupleType S, Internal::SimdType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), v2, v3, Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), v2, Simd( Traits::Load( v3.values ) ), v4 );
    }

    template<Internal::TupleType S, Internal::SimdType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline T SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), v2, Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), v3, v4 );
    }
    template<Internal::TupleType S, Internal::TupleType T, Internal::SimdType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline U SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), v3, Simd( Traits::Load( v4.values ) ) );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::SimdType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline V SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), v4 );
    }

    template<Internal::TupleType S, Internal::TupleType T, Internal::TupleType U, Internal::TupleType V>
        requires Internal::IsCompatible<S, T>&& Internal::IsCompatible<S, U>&& Internal::IsCompatible<S, V>
    inline typename S::Simd SumOfProducts( const S& v1, const T& v2, const U& v3, const V& v4 ) noexcept
    {
        using Traits = typename S::Traits;
        using Simd = typename S::Simd;
        return SumOfProducts( Simd( Traits::Load( v1.values ) ), Simd( Traits::Load( v2.values ) ), Simd( Traits::Load( v3.values ) ), Simd( Traits::Load( v4.values ) ) );
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
            return Min( v.x, v.y );
        }
        else if constexpr ( T::Size == 3 )
        {
            return Min( v.x, v.y, v.z );
        }
        else
        {
            return Min( v.x, v.y, v.z, v.w );
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
            return Max( v.x, v.y );
        }
        else if constexpr ( T::Size == 3 )
        {
            return Max( v.x, v.y, v.z );
        }
        else
        {
            return Max( v.x, v.y, v.z, v.w );
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
        explicit Vector( float v ) noexcept
            : Base( v, v )
        {
        }
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
        explicit Vector( double v ) noexcept
            : Base( v, v )
        {
        }
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
        explicit Vector( float v ) noexcept
            : Base( v, v, v )
        {
        }
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
        explicit Vector( double v ) noexcept
            : Base( v, v, v )
        {
        }
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
        explicit Vector( float v ) noexcept
            : Base( v, v, v, v )
        {
        }
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
        explicit Vector( double v ) noexcept
            : Base( v, v, v, v )
        {
        }
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

        using reference = typename ArrayType::reference;
        using const_reference = typename ArrayType::const_reference;
        using pointer = typename ArrayType::pointer;
        using const_pointer = typename ArrayType::const_pointer;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
        using reverse_iterator = typename ArrayType::reverse_iterator;
        using const_reverse_iterator = typename ArrayType::const_reverse_iterator;

        using Simd = QuaternionSimd<ValueType>;

        union
        {
            ArrayType values;
            struct
            {
                Vector<ValueType, 3> v;
                ValueType w;
            };
        };


        Quaternion( ) noexcept
            : values{}
        { }
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

        Simd operator - ( ) const
        {
            return Traits::Negate( Traits::Load( values ) );
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

    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T,4>::Simd Dot( const QuaternionSimd<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename QuaternionSimd<T>::Traits;
        return Traits::Dot( q1.simd, q2.simd );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Dot( const Quaternion<T>& q1, const QuaternionSimd<T>& q2 ) noexcept
    {
        using Traits = typename QuaternionSimd<T>::Traits;
        return Traits::Dot( Traits::Load( q1.values ), q2.simd );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Dot( const QuaternionSimd<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename QuaternionSimd<T>::Traits;
        return Traits::Dot( q1.simd, Traits::Load( q2.values ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Dot( const Quaternion<T>& q1, const Quaternion<T>& q2 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Dot( Traits::Load( q1.values ), Traits::Load( q2.values ) );
    }

    // Length

    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Length( const QuaternionSimd<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::Sqrt( Traits::HSum( Traits::Mul( q1.simd, q1.simd ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename Vector<T, 4>::Simd Length( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        auto simd = Traits::Load( q1.values );
        return Traits::Sqrt( Traits::HSum( Traits::Mul( simd, simd ) ) );
    }

    // ScalarLength

    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarLength( const QuaternionSimd<T>& q1 ) noexcept
    {
        using Traits = typename QuaternionSimd<T>::Traits;
        return Traits::First( Length( q1 ).simd );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    typename T ScalarLength( const Quaternion<T>& q1 ) noexcept
    {
        using Traits = typename Quaternion<T>::Traits;
        return Traits::First( Length( q1 ).simd );
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

    template<Internal::SimdType T, Internal::SimdType U>
        requires Internal::IsCompatible<T, U>
    constexpr inline auto ScalarAngleBetween( const T& v1, const U& v2 )
    {
        using Traits = typename T::Traits;
        using TypleType = typename T::TupleType;
        using FloatT = typename TypleType::value_type;

        auto dotProduct = Dot( v1, v2);

        if ( Traits::First( dotProduct.simd ) < 0 )
        {
            TypleType s = Sqr( v1 + v2 );
            auto halfLength = Sqrt( s.x + s.y + s.z ) / static_cast< FloatT >( 2. );
            return Constants<FloatT>::Pi - static_cast< FloatT >( 2. ) * SafeASin( halfLength );
        }
        else
        {
            TypleType s = Sqr( v2 - v1 );
            auto halfLength = Sqrt( s.x + s.y + s.z ) / static_cast< FloatT >( 2. );
            return static_cast< FloatT >( 2. ) * SafeASin( halfLength );
        }
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

    //template <typename FloatT, size_t N>
    //class SquareMatrix;
    //template <typename FloatT, size_t N>
    //SquareMatrix<FloatT, N> operator*( const SquareMatrix<FloatT, N>& matrix1, const SquareMatrix<FloatT, N>& matrix2 );


    // SquareMatrix Definition
    template <typename FloatT, size_t N>
    class SquareMatrix : public Internal::MatrixBase
    {
        //template <typename FloatT, size_t N>
        //friend SquareMatrix<FloatT, N> operator*( const SquareMatrix<FloatT, N>& matrix1, const SquareMatrix<FloatT, N>& matrix2 );
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

        SquareMatrix( const value_type mat[ N ][ N ] )
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
                static_assert( false, "Unsupported matrix dimensions." );
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
    inline T1 operator+( const T1& m1, const T2& m2 ) noexcept
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

        auto rmm1 = _mm256_castps128_ps256( matrix1[ 0 ] );
        rmm1 = _mm256_insertf128_ps( rmm1, matrix1[ 1 ], 1 );
        auto rmm2 = _mm256_castps128_ps256( matrix1[ 2 ] );
        rmm2 = _mm256_insertf128_ps( rmm2, matrix1[ 3 ], 1 );

        auto rmm3 = _mm256_castps128_ps256( matrix2[ 0 ] );
        rmm3 = _mm256_insertf128_ps( rmm3, matrix2[ 1 ], 1 );
        auto rmm4 = _mm256_castps128_ps256( matrix2[ 2 ] );
        rmm4 = _mm256_insertf128_ps( rmm4, matrix2[ 3 ], 1 );

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
        result[ 0 ] = _mm256_castps256_ps128( rmm1 );
        result[ 1 ] = _mm256_extractf128_ps( rmm1, 1 );
        result[ 2 ] = _mm256_castps256_ps128( rmm2 );
        result[ 3 ] = _mm256_extractf128_ps( rmm2, 1 );
        return result;
    }

    inline typename SquareMatrix<float, 3>::Simd Multiply( const typename SquareMatrix<float, 3>::Simd& matrix1, const typename SquareMatrix<float, 3>::Simd& matrix2 )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        using Simd = typename SquareMatrix<float, 3>::Simd;

        auto m10 = matrix1[ 0 ];
        auto m11 = matrix1[ 1 ];
        auto m12 = matrix1[ 2 ];

        auto c0 = Traits::At<0>( m10 );
        auto c1 = Traits::At<0>( m11 );
        auto c2 = Traits::At<0>( m12 );

        auto m2v = matrix2[ 0 ];

        c0 = Traits::Mul( c0, m2v );
        c1 = Traits::Mul( c1, m2v );
        c2 = Traits::Mul( c2, m2v );

        auto c0_1 = Traits::At<1>( m10 );
        auto c1_1 = Traits::At<1>( m11 );
        auto c2_1 = Traits::At<1>( m12 );

        m2v = matrix2[ 1 ];

        c0 = Traits::FMAdd( c0_1, m2v, c0 );
        c1 = Traits::FMAdd( c1_1, m2v, c1 );
        c2 = Traits::FMAdd( c2_1, m2v, c2 );

        m10 = Traits::At<2>( m10 );
        m11 = Traits::At<2>( m11 );
        m12 = Traits::At<2>( m12 );

        m2v = matrix2[ 2 ];

        Simd result;
        result[ 0 ] = Traits::FMAdd( m10, m2v, c0 );
        result[ 1 ] = Traits::FMAdd( m11, m2v, c1 );
        result[ 2 ] = Traits::FMAdd( m12, m2v, c2 );
        return result;

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




    inline typename Vector<float,4>::Simd Determinant( const typename SquareMatrix<float, 4>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        using MatrixSimd = typename SquareMatrix<float, 4>::Simd;
        using Union = typename Traits::Union;
        using Select = typename Traits::SelectType;
        Traits::SIMDType sign( { { 1.0f, -1.0f, 1.0f, -1.0f } } );
        
        auto matrix2 = matrix[ 2 ];
        auto matrix3 = matrix[ 3 ];

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

        rmm3 = matrix[ 1 ];

        rmm0 = Traits::Swizzle<Select::Z, Select::W, Select::W, Select::W>( rmm3 );
        rmm1 = Traits::Swizzle<Select::Y, Select::Y, Select::Z, Select::Z>( rmm3 );
        rmm2 = Traits::Swizzle<Select::X, Select::X, Select::X, Select::Y>( rmm3 );
        
        auto rmm7 = Traits::Mul( rmm0, rmm4 );
        rmm7 = Traits::FNMAdd( rmm1, rmm5, rmm7 );
        rmm7 = Traits::FMAdd( rmm2, rmm6, rmm7 );

        rmm3 = matrix[ 0 ];
        rmm3 = Traits::Mul( rmm3, sign );

        return Traits::Dot( rmm3, rmm7 );
    }

    inline typename Vector<float, 4>::Simd Determinant( const typename SquareMatrix<float, 4>& matrix )
    {
        return Math::Determinant( matrix.ToSimd( ) );
    }

    inline float ScalarDeterminant( const SquareMatrix<float, 4>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        return Traits::First( Math::Determinant( matrix ).simd );
    }

    inline float ScalarDeterminant( const SquareMatrix<float, 4>& matrix )
    {
        using Traits = typename SquareMatrix<float, 4>::Traits;
        return Traits::First( Math::Determinant( matrix.ToSimd() ).simd );
    }


    inline typename Vector<float, 3>::Simd Determinant( const typename SquareMatrix<float, 3>::Simd& matrix )
    {
        using Traits = typename SquareMatrix<float, 3>::Traits;
        using Simd = typename SquareMatrix<float, 3>::Simd;

        auto v1 = matrix[ 1 ];
        auto v2 = matrix[ 2 ];

        auto edd = Traits::Swizzle<3, 0, 0, 1>( v1 );
        auto iih = Traits::Swizzle<3, 1, 2, 2>( v2 );
        auto hgg = Traits::Swizzle<3, 0, 0, 1>( v2 );
        auto ffe = Traits::Swizzle<3, 1, 2, 2>( v1 );

        auto det = Traits::Sub( Traits::Mul( edd, iih ), Traits::Mul( hgg, ffe ) );

        Traits::SIMDType sign( { { 1.0f, -1.0f, 1.0f, 0.0f } } );
        auto v0 = Traits::Mul( matrix[ 0 ], sign );

        return Traits::Dot( v0, det );

        /*
        Traits::SIMDType sign( { { 1.0f, -1.0f, 1.0f, 0.0f } } );
        auto v0 = matrix[ 0 ];
        auto v1 = matrix[ 1 ];
        auto v2 = matrix[ 2 ];

        auto edd = Traits::Swizzle<3, 0, 0, 1>( v1 );
        auto iih = Traits::Swizzle<3, 1, 2, 2>( v2 );
        auto hgg = Traits::Swizzle<3, 0, 0, 1>( v2 );
        auto ffe = Traits::Swizzle<3, 1, 2, 2>( v1 );

        auto det = Traits::Sub( Traits::Mul( edd, iih ), Traits::Mul( hgg, ffe ) );

        v0 = Traits::Mul( v0, sign );

        return Traits::Dot( v0, det );
        */
    }

    inline typename Vector<float, 3>::Simd Determinant( const typename SquareMatrix<float, 3>& matrix )
    {
        return Math::Determinant( matrix.ToSimd( ) );
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
        
        auto rmm4 = Traits::Shuffle<1, 0, 1, 0>( matrix[ 0 ], matrix[ 1 ] );
        auto rmm5 = Traits::Shuffle<2, 2, 2, 2>( matrix[ 0 ], matrix[ 1 ] );

        MatrixSimd result;

        result[ 0 ] = Traits::Shuffle<3, 0, 2, 0>( rmm4, matrix[ 2 ] );
        result[ 1 ] = Traits::Shuffle<3, 1, 3, 1>( rmm4, matrix[ 2 ] );
        result[ 2 ] = Traits::Shuffle<3, 2, 2, 0>( rmm5, matrix[ 2 ] );

        return result;
    }

    inline SquareMatrix<float, 3>::Simd Transpose( const SquareMatrix<float, 3>& matrix )
    {
        return Transpose( matrix.ToSimd( ) );
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
