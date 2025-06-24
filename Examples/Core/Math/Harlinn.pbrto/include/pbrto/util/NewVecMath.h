#pragma once
#ifndef PBRT_UTIL_NEWVECMATH_H_
#define PBRT_UTIL_NEWVECMATH_H_
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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>
#include <pbrto/util/NewFloat.h>
#include <pbrto/util/NewMath.h>

#include <pbrto/util/NewCheck.h>

#include <pbrto/util/NewPStd.h>

#include <Harlinn/Math/VectorMath.h>


namespace pbrto
{

    namespace internal
    {

        template <typename T>
        std::string ToString2( T x, T y );
        template <typename T>
        std::string ToString3( T x, T y, T z );

    }  // namespace internal

    extern template std::string internal::ToString2( float, float );
    extern template std::string internal::ToString2( double, double );
    extern template std::string internal::ToString2( int, int );
    extern template std::string internal::ToString3( float, float, float );
    extern template std::string internal::ToString3( double, double, double );
    extern template std::string internal::ToString3( int, int, int );

    namespace
    {

        template<typename T>
            requires IsFloatingPoint<T>
        inline bool IsNaN( Interval& fi )
        {
            return Math::IsNaN( Float( fi ) );
        }

        // TupleLength Definition
        template <typename T>
        struct TupleLength
        {
            using type = Float;
        };

        template <>
        struct TupleLength<double>
        {
            using type = double;
        };

        template <>
        struct TupleLength<long double>
        {
            using type = long double;
        };

        template <>
        struct TupleLength<Interval>
        {
            using type = Interval;
        };

    }  // anonymous namespace

    // Tuple2 Definition
    template <template <typename> class Child, typename T>
    class Tuple2
    {
    public:
        // Tuple2 Public Methods
        static const int nDimensions = 2;

        // Tuple2 Public Members
        T x{}, y{};


        Tuple2( ) = default;

        Tuple2( T x, T y )
            : x( x ), y( y )
        {
            NDCHECK( !HasNaN( ) );
        }

        bool HasNaN( ) const
        {
            return IsNaN( x ) ||
                IsNaN( y );
        }
#ifdef PBRT_DEBUG_BUILD
        // The default versions of these are fine for release builds; for debug
        // we define them so that we can add the Assert checks.
        PBRT_CPU_GPU
            Tuple2( Child<T> c )
        {
            NDCHECK( !c.HasNaN( ) );
            x = c.x;
            y = c.y;
        }
        PBRT_CPU_GPU
            Child<T>& operator=( Child<T> c )
        {
            NDCHECK( !c.HasNaN( ) );
            x = c.x;
            y = c.y;
            return static_cast< Child<T> & >( *this );
        }
#endif

        template <typename U>
        auto operator+( const Child<U>& c ) const->Child<decltype( T{} + U{} ) >
        {
            NDCHECK( !c.HasNaN( ) );
            return { x + c.x, y + c.y };
        }
        template <typename U>
        Child<T>& operator+=( const Child<U>& c )
        {
            NDCHECK( !c.HasNaN( ) );
            x += c.x;
            y += c.y;
            return static_cast< Child<T> & >( *this );
        }

        template <typename U>
        auto operator-( const Child<U>& c ) const->Child<decltype( T{} - U{} ) >
        {
            NDCHECK( !c.HasNaN( ) );
            return { x - c.x, y - c.y };
        }
        template <typename U>
        Child<T>& operator-=( const Child<U>& c )
        {
            NDCHECK( !c.HasNaN( ) );
            x -= c.x;
            y -= c.y;
            return static_cast< Child<T> & >( *this );
        }

        bool operator==( const Child<T>& c ) const
        {
            return x == c.x && y == c.y;
        }

            bool operator!=( const Child<T>& c ) const
        {
            return x != c.x || y != c.y;
        }

        template <typename U>
        PBRT_CPU_GPU auto operator*( const U& s ) const->Child<decltype( T{} *U{} ) >
        {
            return { s * x, s * y };
        }


        template <typename U>
        PBRT_CPU_GPU Child<T>& operator*=( const U& s )
        {
            NDCHECK( !IsNaN( s ) );
            x *= s;
            y *= s;
            return static_cast< Child<T> & >( *this );
        }

        template <typename U>
        auto operator/( const U& d ) const->Child<decltype( T{} / U{} ) >
        {
            NDCHECK( d != 0 && !IsNaN( d ) );
            return { x / d, y / d };
        }

        template <typename U>
        Child<T>& operator/=( const U& d )
        {
            NDCHECK_NE( d, 0 );
            NDCHECK( !IsNaN( d ) );
            x /= d;
            y /= d;
            return static_cast< Child<T> & >( *this );
        }

        Child<T> operator-( ) const { return { -x, -y }; }


        T operator[]( size_t i ) const
        {
            NDCHECK( i <= 1 );
            return ( i == 0 ) ? x : y;
        }

        T& operator[]( size_t i )
        {
            NDCHECK( i <= 1 );
            return ( i == 0 ) ? x : y;
        }

        std::string ToString( ) const
        {
            return std::format( "[ x: {} y: {} ]", x, y );
        }


    };

    // Tuple2 Inline Functions
    template <template <class> class C, typename T, typename U>
    inline auto operator*( const U& s, const Tuple2<C, T>& t )->C<decltype( T{} *U{} ) >
    {
        NDCHECK( !t.HasNaN( ) );
        return t * s;
    }


    template <template <class> class C, typename T>
    inline C<T> Abs( const Tuple2<C, T>& t )
    {
        // "argument-dependent lookup..." (here and elsewhere)
        using std::abs;
        return { abs( t.x ), abs( t.y ) };
    }

    template <template <class> class C, typename T>
    inline C<T> Ceil( const Tuple2<C, T>& t )
    {
        using pstdo::ceil;
        return { ceil( t.x ), ceil( t.y ) };
    }

    template <template <class> class C, typename T>
    inline C<T> Floor( const Tuple2<C, T>& t )
    {
        using pstdo::floor;
        return { floor( t.x ), floor( t.y ) };
    }

    template <template <class> class C, typename T>
    inline auto Lerp2( Float t, const Tuple2<C, T>& t0, const Tuple2<C, T>& t1 )
    {
        return ( 1 - t ) * t0 + t * t1;
    }

    template <template <class> class C, typename T>
    inline C<T> FMA( Float a, const Tuple2<C, T>& b, const Tuple2<C, T>& c )
    {
        return { FMA( a, b.x, c.x ), FMA( a, b.y, c.y ) };
    }

    template <template <class> class C, typename T>
    inline C<T> FMA( const Tuple2<C, T>& a, Float b, const Tuple2<C, T>& c )
    {
        return FMA( b, a, c );
    }

    template <template <class> class C, typename T>
    inline C<T> Min( const Tuple2<C, T>& t0, const Tuple2<C, T>& t1 )
    {
        using std::min;
        return { min( t0.x, t1.x ), min( t0.y, t1.y ) };
    }

    template <template <class> class C, typename T>
    inline T MinComponentValue( const Tuple2<C, T>& t )
    {
        using std::min;
        return min( { t.x, t.y } );
    }

    template <template <class> class C, typename T>
    inline int MinComponentIndex( const Tuple2<C, T>& t )
    {
        return ( t.x < t.y ) ? 0 : 1;
    }

    template <template <class> class C, typename T>
    inline C<T> Max( const Tuple2<C, T>& t0, const Tuple2<C, T>& t1 )
    {
        using std::max;
        return { max( t0.x, t1.x ), max( t0.y, t1.y ) };
    }

    template <template <class> class C, typename T>
    inline T MaxComponentValue( const Tuple2<C, T>& t )
    {
        using std::max;
        return max( { t.x, t.y } );
    }

    template <template <class> class C, typename T>
    inline int MaxComponentIndex( const Tuple2<C, T>& t )
    {
        return ( t.x > t.y ) ? 0 : 1;
    }

    /*
    template <template <class> class C, typename T>
    inline C<T> Permute( const Tuple2<C, T>& t, const pstdo::array<int, 2>& p )
    {
        return { t[ p[ 0 ] ], t[ p[ 1 ] ] };
    }
    */

    template <template <class> class C, typename T>
    inline T HProd( const Tuple2<C, T>& t )
    {
        return t.x * t.y;
    }

    // Tuple3 Definition
    template <template <typename> class Child, typename T>
    class Tuple3
    {
    public:
        // Tuple3 Public Members
        T x{}, y{}, z{};

        // Tuple3 Public Methods
        Tuple3( ) = default;

        Tuple3( T x, T y, T z )
            : x( x ), y( y ), z( z )
        {
            NDCHECK( !HasNaN( ) );
        }

        bool HasNaN( ) const
        {
            return IsNaN( x ) || IsNaN( y ) || IsNaN( z );
        }

        T operator[]( size_t i ) const
        {
            NDCHECK( i <= 2 );
            if ( i == 0 )
                return x;
            if ( i == 1 )
                return y;
            return z;
        }

        T& operator[]( size_t i )
        {
            NDCHECK( i <= 2 );
            if ( i == 0 )
                return x;
            if ( i == 1 )
                return y;
            return z;
        }

        template <typename U>
        auto operator+( const Child<U>& c ) const->Child<decltype( T{} + U{} ) >
        {
            NDCHECK( !c.HasNaN( ) );
            return { x + c.x, y + c.y, z + c.z };
        }

        static const int nDimensions = 3;

#ifdef PBRT_DEBUG_BUILD
        // The default versions of these are fine for release builds; for debug
        // we define them so that we can add the Assert checks.
        PBRT_CPU_GPU
            Tuple3( Child<T> c )
        {
            NDCHECK( !c.HasNaN( ) );
            x = c.x;
            y = c.y;
            z = c.z;
        }

        PBRT_CPU_GPU
            Child<T>& operator=( Child<T> c )
        {
            NDCHECK( !c.HasNaN( ) );
            x = c.x;
            y = c.y;
            z = c.z;
            return static_cast< Child<T> & >( *this );
        }
#endif

        template <typename U>
        Child<T>& operator+=( const Child<U>& c )
        {
            NDCHECK( !c.HasNaN( ) );
            x += c.x;
            y += c.y;
            z += c.z;
            return static_cast< Child<T> & >( *this );
        }

        template <typename U>
        auto operator-( const Child<U>& c ) const->Child<decltype( T{} - U{} ) >
        {
            NDCHECK( !c.HasNaN( ) );
            return { x - c.x, y - c.y, z - c.z };
        }

        template <typename U>
        Child<T>& operator-=( const Child<U>& c )
        {
            NDCHECK( !c.HasNaN( ) );
            x -= c.x;
            y -= c.y;
            z -= c.z;
            return static_cast< Child<T> & >( *this );
        }

        bool operator==( const Child<T>& c ) const
        {
            return x == c.x && y == c.y && z == c.z;
        }

        bool operator!=( const Child<T>& c ) const
        {
            return x != c.x || y != c.y || z != c.z;
        }

        template <typename U>
        auto operator*( const U& s ) const->Child<decltype( T{} *U{} ) >
        {
            return { s * x, s * y, s * z };
        }
        template <typename U>
        Child<T>& operator*=( const U& s )
        {
            NDCHECK( !IsNaN( s ) );
            x *= s;
            y *= s;
            z *= s;
            return static_cast< Child<T> & >( *this );
        }

        template <typename U>
        auto operator/( const U& d ) const->Child<decltype( T{} / U{} ) >
        {
            NDCHECK_NE( d, 0 );
            return { x / d, y / d, z / d };
        }
        template <typename U>
        Child<T>& operator/=( const U& d )
        {
            NDCHECK_NE( d, 0 );
            x /= d;
            y /= d;
            z /= d;
            return static_cast< Child<T> & >( *this );
        }

        Child<T> operator-( ) const 
        { 
            return { -x, -y, -z }; 
        }

        std::string ToString( ) const
        {
            return std::format( "[ x: {} y: {} z: {} ]", x, y, z );
        }

    };

    // Tuple3 Inline Functions
    template <template <class> class C, typename T, typename U>
    inline auto operator*( const U& s, const Tuple3<C, T>& t )->C<decltype( T{} *U{} ) >
    {
        return t * s;
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline C<T> Abs( const Tuple3<C, T>& t )
    {
        using std::abs;
        return { abs( t.x ), abs( t.y ), abs( t.z ) };
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline C<T> Ceil( const Tuple3<C, T>& t )
    {
        using pstdo::ceil;
        return { ceil( t.x ), ceil( t.y ), ceil( t.z ) };
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline C<T> Floor( const Tuple3<C, T>& t )
    {
        using pstdo::floor;
        return { floor( t.x ), floor( t.y ), floor( t.z ) };
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline auto Lerp2( Float t, const Tuple3<C, T>& t0, const Tuple3<C, T>& t1 )
    {
        return ( 1 - t ) * t0 + t * t1;
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline C<T> FMA( Float a, const Tuple3<C, T>& b, const Tuple3<C, T>& c )
    {
        return { FMA( a, b.x, c.x ), FMA( a, b.y, c.y ), FMA( a, b.z, c.z ) };
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline C<T> FMA( const Tuple3<C, T>& a, Float b, const Tuple3<C, T>& c )
    {
        return FMA( b, a, c );
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline C<T> Min( const Tuple3<C, T>& t1, const Tuple3<C, T>& t2 )
    {
        using std::min;
        return { min( t1.x, t2.x ), min( t1.y, t2.y ), min( t1.z, t2.z ) };
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline T MinComponentValue( const Tuple3<C, T>& t )
    {
        using std::min;
        return min( { t.x, t.y, t.z } );
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline int MinComponentIndex( const Tuple3<C, T>& t )
    {
        return ( t.x < t.y ) ? ( ( t.x < t.z ) ? 0 : 2 ) : ( ( t.y < t.z ) ? 1 : 2 );
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline C<T> Max( const Tuple3<C, T>& t1, const Tuple3<C, T>& t2 )
    {
        using std::max;
        return { max( t1.x, t2.x ), max( t1.y, t2.y ), max( t1.z, t2.z ) };
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline T MaxComponentValue( const Tuple3<C, T>& t )
    {
        using std::max;
        return max( { t.x, t.y, t.z } );
    }

    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline int MaxComponentIndex( const Tuple3<C, T>& t )
    {
        return ( t.x > t.y ) ? ( ( t.x > t.z ) ? 0 : 2 ) : ( ( t.y > t.z ) ? 1 : 2 );
    }
    /*
    template <template <class> class C, typename T>
    inline C<T> Permute( const Tuple3<C, T>& t, const pstdo::array<int, 3>& p )
    {
        return { t[ p[ 0 ] ], t[ p[ 1 ] ], t[ p[ 2 ] ] };
    }
    */


    template <template <class> class C, typename T>
        requires ( IsArithmetic<T> == false )
    inline T HProd( const Tuple3<C, T>& t )
    {
        return t.x * t.y * t.z;
    }

    // Vector2 Definition
    template <typename T>
    class Vector2 : public Tuple2<Vector2, T>
    {
    public:
        // Vector2 Public Methods
        using Tuple2<Vector2, T>::x;
        using Tuple2<Vector2, T>::y;

        Vector2( ) = default;

        Vector2( T x, T y )
            : Tuple2<pbrto::Vector2, T>( x, y )
        {
        }
        template <typename U>
        explicit Vector2( const Point2<U>& p );

        template <typename U>
        explicit Vector2( const Vector2<U>& v )
            : Tuple2<pbrto::Vector2, T>( T( v.x ), T( v.y ) )
        {
        }
    };

    // Vector3 Definition
    template <typename T>
    class Vector3 : public Tuple3<Vector3, T>
    {
    public:
        // Vector3 Public Methods
        using Tuple3<Vector3, T>::x;
        using Tuple3<Vector3, T>::y;
        using Tuple3<Vector3, T>::z;

        Vector3( ) = default;

        Vector3( T x, T y, T z )
            : Tuple3<pbrto::Vector3, T>( x, y, z )
        {
        }

        template <typename U>
        explicit Vector3( const Vector3<U>& v )
            : Tuple3<pbrto::Vector3, T>( T( v.x ), T( v.y ), T( v.z ) )
        {
        }

        template <typename U>
        explicit Vector3( const Point3<U>& p );

        template <typename U>
        explicit Vector3( const Normal3<U>& n );
    };

    template<>
    class Vector2<Float> : public Math::Vector<Float, 2>
    {
    public:
        using Base = Math::Vector<Float, 2>;
        using Base::Base;
    };

    template<>
    class Vector3<Float> : public Math::Vector<Float, 3>
    {
    public:
        using Base = Math::Vector<Float, 3>;
        using Base::Base;

        Vector3( const Vector3<double>& other )
            : Base( static_cast< Float >( other.x ), static_cast< Float >( other.y ), static_cast< Float >( other.z ) )
        {
        }
        template<typename T>
            requires ( T::nDimensions == 3 ) && requires ( T t )
        {
            { t.x.Midpoint( ) }->std::convertible_to<Float>;
        }
        Vector3( const T& pi ) noexcept
            : Base( static_cast< float >( pi.x ), static_cast< float >( pi.y ), static_cast< float >( pi.z ) )
        {
        }

        explicit operator Vector3<double>( ) const
        {
            return Vector3<double>( static_cast< double >( x ), static_cast< double >( y ), static_cast< double >( z ) );
        }


    };


    inline Vector2<float> Permute( const Vector2<float>& t, const std::array<int, 2>& p )
    {
        return { t[ p[ 0 ] ], t[ p[ 1 ] ] };
    }

    inline Vector3<float> Permute( const Vector3<float>& t, const std::array<int, 3>& p )
    {
        return { t[ p[ 0 ] ], t[ p[ 1 ] ], t[ p[ 2 ] ] };
    }

    template<>
    class Vector2<Int32> : public Math::Vector<Int32, 2>
    {
    public:
        using Base = Math::Vector<Int32, 2>;
        using Base::Base;

        explicit operator Vector2<Float>( ) const
        {
            return Vector2<Float>( static_cast<float>( x ), static_cast< float >( y ) );
        }

        std::string ToString( ) const
        {
            return std::format( "[ x: {} y: {} ]", x, y );
        }

    };

    inline Vector2<float> ToVector2f( const Vector2<float>::Simd& other )
    {
        return Vector2<float>( other );
    }

    inline Vector2<float> ToVector2f( const Vector2<Int32>& other )
    {
        return Vector2<float>( static_cast< Float >( other.x ), static_cast< Float >( other.y ) );
    }
    inline Vector2<float> ToVector2f( const Vector2<Int32>::Simd& other )
    {
        Vector2<Int32> tmp( other );
        return Vector2<float>( static_cast< Float >( tmp.x ), static_cast< Float >( tmp.y ) );
    }


    template<>
    class Vector3<Int32> : public Math::Vector<Int32, 3>
    {
    public:
        using Base = Math::Vector<Int32, 3>;
        using Base::Base;

        template<typename T>
            requires ( T::nDimensions == 3 ) && requires ( T t )
        {
            { t.x.Midpoint( ) }->std::convertible_to<Float>;
        }
        Vector3( const T& pi ) noexcept
            : Base( static_cast< Int32 >( pi.x ), static_cast< Int32 >( pi.y ), static_cast< Int32 >( pi.z ) )
        {
        }

        explicit operator Vector3<Float>( ) const
        {
            return Vector3<Float>( static_cast< float >( x ), static_cast< float >( y ), static_cast< float >( z ) );
        }


    };


    // Vector2* Definitions
    using Vector2f = Vector2<Float>;
    using Vector2i = Vector2<int>;

    // Vector3* Definitions
    using Vector3f = Vector3<Float>;
    using Vector3i = Vector3<int>;

    // Vector3fi Definition
    class Vector3fi : public Vector3<Interval>
    {
    public:
        // Vector3fi Public Methods
        using Vector3<Interval>::x;
        using Vector3<Interval>::y;
        using Vector3<Interval>::z;
        using Vector3<Interval>::HasNaN;
        using Vector3<Interval>::operator+;
        using Vector3<Interval>::operator+=;
        using Vector3<Interval>::operator*;
        using Vector3<Interval>::operator*=;

        Vector3fi( ) = default;

        Vector3fi( Float x, Float y, Float z )
            : Vector3<Interval>( Interval( x ), Interval( y ), Interval( z ) )
        {
        }

        Vector3fi( const Interval& x, const Interval& y, const Interval& z )
            : Vector3<Interval>( x, y, z )
        {
        }

        Vector3fi( const Vector3f& p )
            : Vector3<Interval>( Interval( p.x ), Interval( p.y ), Interval( p.z ) )
        {
        }

        template <typename T>
        explicit Vector3fi( const Point3<T>& p )
            : Vector3<Interval>( Interval( p.x ), Interval( p.y ), Interval( p.z ) )
        {
        }

        Vector3fi( const Vector3<Interval>& pfi )
            : Vector3<Interval>( pfi )
        {
        }

        Vector3fi( const Vector3f& v, const Vector3f& e )
            : Vector3<Interval>( Interval::FromValueAndError( v.x, e.x ),
                Interval::FromValueAndError( v.y, e.y ),
                Interval::FromValueAndError( v.z, e.z ) )
        {
        }

        Vector3f Error( ) const
        {
            return Vector3f( x.Width( ) / 2, y.Width( ) / 2, z.Width( ) / 2 );
        }
        bool IsExact( ) const { return x.Width( ) == 0 && y.Width( ) == 0 && z.Width( ) == 0; }

    };


    inline Vector3<float> ToVector3f( const Vector3<float>::Simd& other )
    {
        return Vector3<float>( other );
    }

    inline Vector3<float> ToVector3f( const Vector3<Int32>& other )
    {
        return Vector3<float>( static_cast< Float >( other.x ), static_cast< Float >( other.y ), static_cast< Float >( other.z ) );
    }
    inline Vector3<float> ToVector3f( const Vector3<Int32>::Simd& other )
    {
        Vector3<Int32> tmp( other );
        return Vector3<float>( static_cast< Float >( tmp.x ), static_cast< Float >( tmp.y ), static_cast< Float >( tmp.z ) );
    }


    // Point2 Definition
    template <typename T>
    class Point2 : public Tuple2<Point2, T>
    {
    public:
        // Point2 Public Methods
        using Tuple2<Point2, T>::x;
        using Tuple2<Point2, T>::y;
        using Tuple2<Point2, T>::HasNaN;
        using Tuple2<Point2, T>::operator+;
        using Tuple2<Point2, T>::operator+=;
        using Tuple2<Point2, T>::operator*;
        using Tuple2<Point2, T>::operator*=;

        Point2( )
        {
            x = y = 0;
        }

        Point2( T x, T y )
            : Tuple2<pbrto::Point2, T>( x, y )
        {
        }

        template <typename U>
        explicit Point2( const Point2<U>& v )
            : Tuple2<pbrto::Point2, T>( T( v.x ), T( v.y ) )
        {
        }

        template <typename U>
        explicit Point2( const Vector2<U>& v )
            : Tuple2<pbrto::Point2, T>( T( v.x ), T( v.y ) )
        {
        }

        template <typename U>
        auto operator+( const Vector2<U>& v ) const->Point2<decltype( T{} + U{} ) >
        {
            NDCHECK( !v.HasNaN( ) );
            return { x + v.x, y + v.y };
        }

        template <typename U>
        Point2<T>& operator+=( const Vector2<U>& v )
        {
            NDCHECK( !v.HasNaN( ) );
            x += v.x;
            y += v.y;
            return *this;
        }

        // We can't do using operator- above, since we don't want to pull in
        // the Point-Point -> Point one so that we can return a vector
        // instead...
        Point2<T> operator-( ) const 
        { 
            return { -x, -y }; 
        }

        template <typename U>
        auto operator-( const Point2<U>& p ) const->Vector2<decltype( T{} - U{} ) >
        {
            NDCHECK( !p.HasNaN( ) );
            return { x - p.x, y - p.y };
        }
        template <typename U>
        auto operator-( const Vector2<U>& v ) const->Point2<decltype( T{} - U{} ) >
        {
            NDCHECK( !v.HasNaN( ) );
            return { x - v.x, y - v.y };
        }
        template <typename U>
        Point2<T>& operator-=( const Vector2<U>& v )
        {
            NDCHECK( !v.HasNaN( ) );
            x -= v.x;
            y -= v.y;
            return *this;
        }
    };

    template <>
    class Point2<Float> : public Math::Point2f
    {
    public:
        using Base = Math::Point2f;
        using Base::Base;

        template<typename U>
            requires ( std::is_same_v<U, float> == false )
        explicit operator Point2<U>( ) const
        {
            return Point2<U>( static_cast< U >( x ), static_cast< U >( y ) );
        }
        template<typename U>
        explicit operator Vector2<U>( ) const
        {
            return Vector2<U>( static_cast< U >( x ), static_cast< U >( y ) );
        }

    };

    template <>
    class Point2<Int32> : public Math::Point2i
    {
    public:
        using Base = Math::Point2i;
        using Base::Base;

        template<typename U>
            requires ( std::is_same_v<U, Int32> == false )
        explicit operator Point2<U>( ) const
        {
            return Point2<U>( static_cast< U >( x ), static_cast< U >( y ) );
        }

        template<typename U>
        explicit operator Vector2<U>( ) const
        {
            return Vector2<U>( static_cast< U >( x ), static_cast< U >( y ) );
        }

    };

    inline Point2<float>::Simd operator+( const Point2<float>& p, const Vector2<float>& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Add( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Point2<float>::Simd operator+( const Point2<float>::Simd& p, const Vector2<float>& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Add( p.simd, Traits::Load( v.values ) );
    }
    inline Point2<float>::Simd operator+( const Point2<float>& p, const Vector2<float>::Simd& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Add( Traits::Load( p.values ), v.simd );
    }
    inline Point2<float>::Simd operator+( const Point2<float>::Simd& p, const Vector2<float>::Simd& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Add( p.simd, v.simd );
    }

    inline Point2<float>::Simd operator-( const Point2<float>& p, const Vector2<float>& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Sub( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Point2<float>::Simd operator-( const Point2<float>::Simd& p, const Vector2<float>& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Sub( p.simd, Traits::Load( v.values ) );
    }
    inline Point2<float>::Simd operator-( const Point2<float>& p, const Vector2<float>::Simd& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Sub( Traits::Load( p.values ), v.simd );
    }
    inline Point2<float>::Simd operator-( const Point2<float>::Simd& p, const Vector2<float>::Simd& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Sub( p.simd, v.simd );
    }

    inline Vector2<float>::Simd operator-( const Point2<float>& p, const Point2<float>& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Sub( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Vector2<float>::Simd operator-( const Point2<float>::Simd& p, const Point2<float>& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Sub( p.simd, Traits::Load( v.values ) );
    }
    inline Vector2<float>::Simd operator-( const Point2<float>& p, const Point2<float>::Simd& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Sub( Traits::Load( p.values ), v.simd );
    }
    inline Vector2<float>::Simd operator-( const Point2<float>::Simd& p, const Point2<float>::Simd& v )
    {
        using Traits = Point2<float>::Traits;
        return Traits::Sub( p.simd, v.simd );
    }


    //
    inline Point2<Int32>::Simd operator+( const Point2<Int32>& p, const Vector2<Int32>& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Add( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Point2<Int32>::Simd operator+( const Point2<Int32>::Simd& p, const Vector2<Int32>& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Add( p.simd, Traits::Load( v.values ) );
    }
    inline Point2<Int32>::Simd operator+( const Point2<Int32>& p, const Vector2<Int32>::Simd& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Add( Traits::Load( p.values ), v.simd );
    }
    inline Point2<Int32>::Simd operator+( const Point2<Int32>::Simd& p, const Vector2<Int32>::Simd& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Add( p.simd, v.simd );
    }

    inline Point2<Int32>::Simd operator-( const Point2<Int32>& p, const Vector2<Int32>& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Sub( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Point2<Int32>::Simd operator-( const Point2<Int32>::Simd& p, const Vector2<Int32>& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Sub( p.simd, Traits::Load( v.values ) );
    }
    inline Point2<Int32>::Simd operator-( const Point2<Int32>& p, const Vector2<Int32>::Simd& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Sub( Traits::Load( p.values ), v.simd );
    }
    inline Point2<Int32>::Simd operator-( const Point2<Int32>::Simd& p, const Vector2<Int32>::Simd& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Sub( p.simd, v.simd );
    }

    inline Vector2<Int32>::Simd operator-( const Point2<Int32>& p, const Point2<Int32>& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Sub( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Vector2<Int32>::Simd operator-( const Point2<Int32>::Simd& p, const Point2<Int32>& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Sub( p.simd, Traits::Load( v.values ) );
    }
    inline Vector2<Int32>::Simd operator-( const Point2<Int32>& p, const Point2<Int32>::Simd& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Sub( Traits::Load( p.values ), v.simd );
    }
    inline Vector2<Int32>::Simd operator-( const Point2<Int32>::Simd& p, const Point2<Int32>::Simd& v )
    {
        using Traits = Point2<Int32>::Traits;
        return Traits::Sub( p.simd, v.simd );
    }



    // Point2 Inline Functions

    // https://www.iquilezles.org/www/articles/ibilinear/ibilinear.htm,
    // with a fix for perfect quads
    PBRT_CPU_GPU inline Point2f InvertBilinear( const Point2f& p, const std::array<Point2f, 4>& vert )
    {
        // The below assumes a quad (vs uv parametric layout) in v....
        Point2f a = vert[ 0 ], b = vert[ 1 ], c = vert[ 3 ], d = vert[ 2 ];
        Vector2f e = b - a, f = d - a, g = ( a - b ) + ( c - d ), h = p - a;

        auto cross2d = []( Vector2f a, Vector2f b )
            {
                return DifferenceOfProducts( a.x, b.y, a.y, b.x );
            };

        Float k2 = cross2d( g, f );
        Float k1 = cross2d( e, f ) + cross2d( h, g );
        Float k0 = cross2d( h, e );

        // if edges are parallel, this is a linear equation
        if ( Math::FastAbs( k2 ) < 0.001f )
        {
            if ( Math::FastAbs( e.x * k1 - g.x * k0 ) < 1e-5f )
                return Point2f( ( h.y * k1 + f.y * k0 ) / ( e.y * k1 - g.y * k0 ), -k0 / k1 );
            else
                return Point2f( ( h.x * k1 + f.x * k0 ) / ( e.x * k1 - g.x * k0 ), -k0 / k1 );
        }

        Float v0, v1;
        if ( !Quadratic( k2, k1, k0, &v0, &v1 ) )
            return Point2f( 0, 0 );

        Float u = ( h.x - f.x * v0 ) / ( e.x + g.x * v0 );
        if ( u < 0 || u > 1 || v0 < 0 || v0 > 1 )
            return Point2f( ( h.x - f.x * v1 ) / ( e.x + g.x * v1 ), v1 );
        return Point2f( u, v0 );
    }

    // Point3 Definition
    template <typename T>
    class Point3 : public Tuple3<Point3, T>
    {
    public:
        // Point3 Public Methods
        using Tuple3<Point3, T>::x;
        using Tuple3<Point3, T>::y;
        using Tuple3<Point3, T>::z;
        using Tuple3<Point3, T>::HasNaN;
        using Tuple3<Point3, T>::operator+;
        using Tuple3<Point3, T>::operator+=;
        using Tuple3<Point3, T>::operator*;
        using Tuple3<Point3, T>::operator*=;

        Point3( ) = default;

        Point3( T x, T y, T z )
            : Tuple3<pbrto::Point3, T>( x, y, z )
        {
        }

        // We can't do using operator- above, since we don't want to pull in
        // the Point-Point -> Point one so that we can return a vector
        // instead...
        Point3<T> operator-( ) const
        {
            return { -x, -y, -z };
        }

        template <typename U>
        explicit Point3( const Point3<U>& p )
            : Tuple3<pbrto::Point3, T>( T( p.x ), T( p.y ), T( p.z ) )
        { }

        template <typename U>
        explicit Point3( const Vector3<U>& v )
            : Tuple3<pbrto::Point3, T>( T( v.x ), T( v.y ), T( v.z ) )
        { }

        template <typename U>
        auto operator+( const Vector3<U>& v ) const->Point3<decltype( T{} + U{} ) >
        {
            NDCHECK( !v.HasNaN( ) );
            return { x + v.x, y + v.y, z + v.z };
        }
        template <typename U>
        Point3<T>& operator+=( const Vector3<U>& v )
        {
            NDCHECK( !v.HasNaN( ) );
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        template <typename U>
        auto operator-( const Vector3<U>& v ) const -> Point3<decltype( T{} - U{} ) >
        {
            NDCHECK( !v.HasNaN( ) );
            return { x - v.x, y - v.y, z - v.z };
        }
        template <typename U>
        Point3<T>& operator-=( const Vector3<U>& v )
        {
            NDCHECK( !v.HasNaN( ) );
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        template <typename U>
        auto operator-( const Point3<U>& p ) const->Vector3<decltype( T{} - U{} ) >
        {
            NDCHECK( !p.HasNaN( ) );
            return { x - p.x, y - p.y, z - p.z };
        }

    };

    template <>
    class Point3<Float> : public Math::Point3f
    {
    public:
        using Base = Math::Point3f;
        using Base::Base;
        /*
        Point3( ) = default;
        Point3( Float x, Float y, Float z )
            : Base( x, y, z )
        {
        }
        Point3( const Point3<Float>& v )
            : Base( v.x, v.y, v.z )
        {
        }
        Point3( const Vector3<Float>& v )
            : Base( v.x, v.y, v.z )
        {
        }

        template<Math::Internal::SimdType T>
            requires std::is_same_v<Traits, typename T::Traits>
        Point3( const T& other ) noexcept
            : Base( other )
        {
        }
        */
        template<typename T>
            requires ( T::nDimensions == 3 ) && requires ( T t )
        {
            { t.x.Midpoint( ) }->std::convertible_to<Float>;
        }
        Point3( const T& pi ) noexcept
            : Base( static_cast< float >( pi.x ), static_cast< float >( pi.y ), static_cast< float >( pi.z ) )
        {
        }
        explicit operator Vector3<double>( ) const
        {
            return Vector3<double>( static_cast< double >( x ), static_cast< double >( y ), static_cast< double >( z ) );
        }

        template<typename U>
            requires ( std::is_same_v<U, float> == false )
        explicit operator Point3<U>( ) const
        {
            return Point3<U>( static_cast< U >( x ), static_cast< U >( y ), static_cast< U >( z ) );
        }
    };

    


    template <>
    class Point3<Int32> : public Math::Point3i
    {
    public:
        using Base = Math::Point3i;
        using Base::Base;
        /*
        Point3( ) = default;
        Point3( Int32 x, Int32 y, Int32 z )
            : Base( x, y, z )
        {
        }
        Point3( const Point3<Int32>& v )
            : Base( v.x, v.y, v.z )
        {
        }
        Point3( const Vector3<Int32>& v )
            : Base( v.x, v.y, v.z )
        {
        }

        template<Math::Internal::SimdType T>
            requires std::is_same_v<Traits, typename T::Traits>
        Point3( const T& other ) noexcept
            : Base( other )
        {
        }
        */
        template<typename T>
            requires ( T::nDimensions == 3 ) && requires ( T t )
        {
            { t.x.Midpoint( ) }->std::convertible_to<Float>;
        }
        Point3( const T& pi ) noexcept
            : Base( static_cast< Int32 >( pi.x ), static_cast< Int32 >( pi.y ), static_cast< Int32 >( pi.z ) )
        {
        }
        explicit operator Vector3<Float>( ) const
        {
            return Vector3<Float>( static_cast< Float >( x ), static_cast< Float >( y ), static_cast< Float >( z ) );
        }
        template<typename U>
            requires (std::is_same_v<U,Int32> == false)
        explicit operator Point3<U>( ) const
        {
            return Point3<U>( static_cast<U>( x ), static_cast< U >( y ), static_cast< U >( z ) );
        }

    };


    inline Point3<float>::Simd operator+( const Point3<float>& p, const Vector3<float>& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Add( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Point3<float>::Simd operator+( const Point3<float>::Simd& p, const Vector3<float>& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Add( p.simd, Traits::Load( v.values ) );
    }
    inline Point3<float>::Simd operator+( const Point3<float>& p, const Vector3<float>::Simd& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Add( Traits::Load( p.values ), v.simd );
    }
    inline Point3<float>::Simd operator+( const Point3<float>::Simd& p, const Vector3<float>::Simd&  v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Add( p.simd, v.simd );
    }

    inline Point3<float>::Simd operator-( const Point3<float>& p, const Vector3<float>& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Sub( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Point3<float>::Simd operator-( const Point3<float>::Simd& p, const Vector3<float>& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Sub( p.simd, Traits::Load( v.values ) );
    }
    inline Point3<float>::Simd operator-( const Point3<float>& p, const Vector3<float>::Simd& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Sub( Traits::Load( p.values ), v.simd );
    }
    inline Point3<float>::Simd operator-( const Point3<float>::Simd& p, const Vector3<float>::Simd& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Sub( p.simd, v.simd );
    }

    inline Vector3<float>::Simd operator-( const Point3<float>& p, const Point3<float>& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Sub( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Vector3<float>::Simd operator-( const Point3<float>::Simd& p, const Point3<float>& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Sub( p.simd, Traits::Load( v.values ) );
    }
    inline Vector3<float>::Simd operator-( const Point3<float>& p, const Point3<float>::Simd& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Sub( Traits::Load( p.values ), v.simd );
    }
    inline Vector3<float>::Simd operator-( const Point3<float>::Simd& p, const Point3<float>::Simd& v )
    {
        using Traits = Point3<float>::Traits;
        return Traits::Sub( p.simd, v.simd );
    }


    //
    inline Point3<Int32>::Simd operator+( const Point3<Int32>& p, const Vector3<Int32>& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Add( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Point3<Int32>::Simd operator+( const Point3<Int32>::Simd& p, const Vector3<Int32>& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Add( p.simd, Traits::Load( v.values ) );
    }
    inline Point3<Int32>::Simd operator+( const Point3<Int32>& p, const Vector3<Int32>::Simd& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Add( Traits::Load( p.values ), v.simd );
    }
    inline Point3<Int32>::Simd operator+( const Point3<Int32>::Simd& p, const Vector3<Int32>::Simd& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Add( p.simd, v.simd );
    }

    inline Point3<Int32>::Simd operator-( const Point3<Int32>& p, const Vector3<Int32>& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Sub( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Point3<Int32>::Simd operator-( const Point3<Int32>::Simd& p, const Vector3<Int32>& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Sub( p.simd, Traits::Load( v.values ) );
    }
    inline Point3<Int32>::Simd operator-( const Point3<Int32>& p, const Vector3<Int32>::Simd& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Sub( Traits::Load( p.values ), v.simd );
    }
    inline Point3<Int32>::Simd operator-( const Point3<Int32>::Simd& p, const Vector3<Int32>::Simd& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Sub( p.simd, v.simd );
    }

    inline Vector3<Int32>::Simd operator-( const Point3<Int32>& p, const Point3<Int32>& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Sub( Traits::Load( p.values ), Traits::Load( v.values ) );
    }
    inline Vector3<Int32>::Simd operator-( const Point3<Int32>::Simd& p, const Point3<Int32>& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Sub( p.simd, Traits::Load( v.values ) );
    }
    inline Vector3<Int32>::Simd operator-( const Point3<Int32>& p, const Point3<Int32>::Simd& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Sub( Traits::Load( p.values ), v.simd );
    }
    inline Vector3<Int32>::Simd operator-( const Point3<Int32>::Simd& p, const Point3<Int32>::Simd& v )
    {
        using Traits = Point3<Int32>::Traits;
        return Traits::Sub( p.simd, v.simd );
    }


    // Point2* Definitions
    using Point2f = Point2<Float>;
    using Point2i = Point2<int>;

    // Point3* Definitions
    using Point3f = Point3<Float>;
    using Point3i = Point3<int>;

    // Point3fi Definition
    class Point3fi : public Point3<Interval>
    {
    public:
        using Point3<Interval>::x;
        using Point3<Interval>::y;
        using Point3<Interval>::z;
        using Point3<Interval>::HasNaN;
        using Point3<Interval>::operator+;
        using Point3<Interval>::operator*;
        using Point3<Interval>::operator*=;

        Point3fi( ) = default;
        Point3fi( const Interval& x, const Interval& y, const Interval& z )
            : Point3<Interval>( x, y, z )
        {
        }

        Point3fi( Float x, Float y, Float z )
            : Point3<Interval>( Interval( x ), Interval( y ), Interval( z ) )
        {
        }

        Point3fi( const Point3f& p )
            : Point3<Interval>( Interval( p.x ), Interval( p.y ), Interval( p.z ) )
        {
        }

        Point3fi( const Point3f::Simd& p )
            : Point3fi( Point3f(p) )
        { }


        Point3fi( const Point3<Interval>& p )
            : Point3<Interval>( p )
        {
        }

        Point3fi( const Point3f& p, const Vector3f& e )
            : Point3<Interval>( Interval::FromValueAndError( p.x, e.x ),
                Interval::FromValueAndError( p.y, e.y ),
                Interval::FromValueAndError( p.z, e.z ) )
        {
        }

        Vector3f Error( ) const
        {
            return { x.Width( ) / 2, y.Width( ) / 2, z.Width( ) / 2 };
        }
        bool IsExact( ) const
        {
            return x.Width( ) == 0 && y.Width( ) == 0 && z.Width( ) == 0;
        }

        // Meh--can't seem to get these from Point3 via using declarations...
        template <typename U>
        Point3fi operator+( const Vector3<U>& v ) const
        {
            NDCHECK( !v.HasNaN( ) );
            return { x + v.x, y + v.y, z + v.z };
        }

        template <typename U>
        Point3fi& operator+=( const Vector3<U>& v )
        {
            NDCHECK( !v.HasNaN( ) );
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Point3fi operator-( ) const { return { -x, -y, -z }; }

        template <typename U>
        Point3fi operator-( const Point3<U>& p ) const
        {
            NDCHECK( !p.HasNaN( ) );
            return { x - p.x, y - p.y, z - p.z };
        }
        template <typename U>
        Point3fi operator-( const Vector3<U>& v ) const
        {
            NDCHECK( !v.HasNaN( ) );
            return { x - v.x, y - v.y, z - v.z };
        }

        Point3fi operator/( Float value ) const
        {
            return Point3fi( x - value, y - value, z - value );
        }

        Point3fi operator*( Float value ) const
        {
            return Point3fi( x * value, y * value, z * value );
        }

        Point3fi operator*( const Vector3<Float>& v ) const
        {
            return Point3fi( x * v.x, y * v.y, z * v.z );
        }


        template <typename U>
        Point3fi& operator-=( const Vector3<U>& v )
        {
            NDCHECK( !v.HasNaN( ) );
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        template <typename T>
            requires ( Math::SimdType<T> == false && Math::TupleType<T> == false )
        Point3fi& operator+=( const T& v )
        {
            NDCHECK( !v.HasNaN( ) );
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        template <Math::SimdType T>
        PBRT_CPU_GPU Point3fi& operator+=( const T& vec )
        {
            Vector3<float> v( vec );
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        template <Math::TupleType T>
        PBRT_CPU_GPU Point3fi& operator+=( const T& v )
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }


    };


    // Normal3 Definition
    template <typename T>
    class Normal3 : public Tuple3<Normal3, T>
    {
    public:
        // Normal3 Public Methods
        using Tuple3<Normal3, T>::x;
        using Tuple3<Normal3, T>::y;
        using Tuple3<Normal3, T>::z;
        using Tuple3<Normal3, T>::HasNaN;
        using Tuple3<Normal3, T>::operator+;
        using Tuple3<Normal3, T>::operator*;
        using Tuple3<Normal3, T>::operator*=;

        Normal3( ) = default;

        Normal3( T x, T y, T z )
            : Tuple3<pbrto::Normal3, T>( x, y, z )
        {
        }
        template <typename U>
        explicit Normal3<T>( const Normal3<U>& v )
            : Tuple3<pbrto::Normal3, T>( T( v.x ), T( v.y ), T( v.z ) )
        {
        }

        template <typename U>
        explicit Normal3<T>( const Vector3<U>& v )
            : Tuple3<pbrto::Normal3, T>( T( v.x ), T( v.y ), T( v.z ) )
        {
        }
    };

    template <>
    class Normal3<Float> : public Math::Normal3f
    {
    public:
        using Base = Math::Normal3f;
        Normal3( ) = default;
        Normal3( Float x, Float y, Float z )
            : Base( x, y, z )
        {
        }
        template <typename U>
        Normal3( const Normal3<U>& v )
            : Base( v.x, v.y, v.z )
        {
        }
        template <typename U>
        Normal3( const Vector3<U>& v )
            : Base( v.x, v.y, v.z )
        {
        }

        template<Math::SimdType T>
            requires std::is_same_v<Traits, typename T::Traits>
        Normal3( const T& other ) noexcept
            : Base( other )
        {
        }

    };

    inline Point2i ToPoint2i( const Vector2<float>::Simd& other )
    {
        Vector2<float> tmp( other );
        return Point2i( static_cast< int >( tmp.x ), static_cast< int >( tmp.y ) );
    }

    inline Point2i ToPoint2i( const Point2<float>::Simd& other )
    {
        Point2<float> tmp( other );
        return Point2i( static_cast< int >( tmp.x ), static_cast< int >( tmp.y ) );
    }

    inline Point2f ToPoint2f( const Vector2<float>::Simd& other )
    {
        Vector2<float> tmp( other );
        return Point2f( tmp.x, tmp.y );
    }

    inline Point2f ToPoint2f( const Point2<float>::Simd& other )
    {
        Vector2<float> tmp( other );
        return Point2f( tmp.x, tmp.y );
    }

    inline Point2f ToPoint2f( const Point2i& other )
    {
        return Point2f( static_cast< Float >( other.x ), static_cast< Float >( other.y ) );
    }


    inline Vector2i ToVector2i( const Point2<float>::Simd& other )
    {
        Point2<float> tmp( other );
        return Vector2i( static_cast< int >( tmp.x ), static_cast< int >( tmp.y ) );
    }

    inline Vector2i ToVector2i( const Point2<float>& other )
    {
        return Vector2i( static_cast< int >( other.x ), static_cast< int >( other.y ) );
    }

    inline Vector2i ToVector2i( const Point2<Int32>::Simd& other )
    {
        Point2<Int32> tmp( other );
        return Vector2i( tmp.x, tmp.y );
    }

    inline Vector2i ToVector2i( const Point2<Int32>& other )
    {
        return Vector2i( other.x, other.y );
    }



    inline Point3i ToPoint3i( const Vector3<float>::Simd& other )
    {
        Vector3<float> tmp( other );
        return Point3i( static_cast< int >( tmp.x ), static_cast< int >( tmp.y ), static_cast< int >( tmp.z ) );
    }


    inline Point3f ToPoint3f( const Vector3<float>::Simd& other )
    {
        Vector3<float> tmp( other );
        return Point3f( tmp.x, tmp.y, tmp.z );
    }

    inline Point3f ToPoint3f( const Point3i& other )
    {
        return Point3f( static_cast< Float >( other.x ), static_cast< Float >( other.y ), static_cast< Float >( other.z ) );
    }


    using Normal3f = Normal3<Float>;

    using Quaternion = Math::Quaternion<Float>;


    // Vector2 Inline Functions
    template <typename T>
    template <typename U>
    Vector2<T>::Vector2( const Point2<U>& p )
        : Tuple2<pbrto::Vector2, T>( T( p.x ), T( p.y ) )
    {
    }


    // Vector3 Inline Functions
    template <typename T>
    template <typename U>
    Vector3<T>::Vector3( const Point3<U>& p )
        : Tuple3<pbrto::Vector3, T>( T( p.x ), T( p.y ), T( p.z ) )
    {
    }


    
    template <typename T>
        requires ( IsArithmetic<T> == false )
        //requires ( std::is_same_v<T, float> == false )
    inline Vector3<T> Cross( const Vector3<T>& v1, const Normal3<T>& v2 )
    {
        NDCHECK( !v1.HasNaN( ) && !v2.HasNaN( ) );
        return { DifferenceOfProducts( v1.y, v2.z, v1.z, v2.y ),
                DifferenceOfProducts( v1.z, v2.x, v1.x, v2.z ),
                DifferenceOfProducts( v1.x, v2.y, v1.y, v2.x ) };
    }

    template <typename T>
        requires IsArithmetic<T>
    inline typename Vector3<T>::Simd Cross( const Vector3<T>& v1, const Normal3<T>& v2 )
    {
        return Math::Cross( v1, v2 );
    }
    template <typename T>
        requires IsArithmetic<T>
    inline typename Vector3<T>::Simd Cross( const typename Vector3<T>::Simd& v1, const Normal3<T>& v2 )
    {
        return Math::Cross( v1, v2 );
    }
    template <typename T>
        requires IsArithmetic<T>
    inline typename Vector3<T>::Simd Cross( const Vector3<T>& v1, const typename Normal3<T>::Simd& v2 )
    {
        return Math::Cross( v1, v2 );
    }
    template <typename T>
        requires IsArithmetic<T>
    inline typename Vector3<T>::Simd Cross( const typename Vector3<T>::Simd& v1, const typename Normal3<T>::Simd& v2 )
    {
        return Math::Cross( v1, v2 );
    }


    template <typename T>
        requires ( IsArithmetic<T> == false )
        //requires ( std::is_same_v<T, float> == false )
    inline Vector3<T> Cross( const Normal3<T>& v1, const Vector3<T>& v2 )
    {
        NDCHECK( !v1.HasNaN( ) && !v2.HasNaN( ) );
        return { DifferenceOfProducts( v1.y, v2.z, v1.z, v2.y ),
                DifferenceOfProducts( v1.z, v2.x, v1.x, v2.z ),
                DifferenceOfProducts( v1.x, v2.y, v1.y, v2.x ) };
    }

    template <typename T>
        requires IsArithmetic<T>
    inline typename Vector3<T>::Simd Cross( const Normal3<T>& v1, const Vector3<T>& v2 )
    {
        return Math::Cross( v1, v2 );
    }
    template <typename T>
        requires IsArithmetic<T>
    inline typename Vector3<T>::Simd Cross( const typename Normal3<T>::Simd& v1, const Vector3<T>& v2 )
    {
        return Math::Cross( v1, v2 );
    }
    template <typename T>
        requires IsArithmetic<T>
    inline typename Vector3<T>::Simd Cross( const Normal3<T>& v1, const typename Vector3<T>::Simd& v2 )
    {
        return Math::Cross( v1, v2 );
    }
    template <typename T>
        requires IsArithmetic<T>
    inline typename Vector3<T>::Simd Cross( const typename Normal3<T>::Simd& v1, const typename Vector3<T>::Simd& v2 )
    {
        return Math::Cross( v1, v2 );
    }


    template <typename T>
        requires ( IsArithmetic<T> == false || std::is_same_v<T, double> )
        //requires ( std::is_same_v<T, float> == false )
    inline Vector3<T> Cross( const Vector3<T>& v, const Vector3<T>& w )
    {
        NDCHECK( !v.HasNaN( ) && !w.HasNaN( ) );
        return { DifferenceOfProducts( v.y, w.z, v.z, w.y ),
                DifferenceOfProducts( v.z, w.x, v.x, w.z ),
                DifferenceOfProducts( v.x, w.y, v.y, w.x ) };
    }

    template <typename T>
        requires ( std::is_same_v<T, float> == false )
    inline T ScalarLengthSquared( const Vector3<T>& v )
    {
        return Sqr( v.x ) + Sqr( v.y ) + Sqr( v.z );
    }

    template <typename T>
        requires ( std::is_same_v<T, float> == false )
    inline auto ScalarLength( const Vector3<T>& v ) -> typename TupleLength<T>::type
    {
        using std::sqrt;
        return sqrt( ScalarLengthSquared( v ) );
    }

    template <typename T>
        requires ( std::is_same_v<T, float> == false )
    inline auto Normalize( const Vector3<T>& v )
    {
        return v / ScalarLength( v );
    }

    template <typename T>
        requires ( std::is_same_v<T, float> == false )
    inline T ScalarDot( const Vector3<T>& v, const Vector3<T>& w )
    {
        NDCHECK( !v.HasNaN( ) && !w.HasNaN( ) );
        return v.x * w.x + v.y * w.y + v.z * w.z;
    }
    


    template <typename T>
    inline Vector3<T> GramSchmidt( const Vector3<T>& v, const Vector3<T>& w )
    {
        return v - Dot( v, w ) * w;
    }

    inline Vector3f::Simd GramSchmidt( const Vector3f::Simd& v, const Vector3f::Simd& w )
    {
        return v - Dot( v, w ) * w;
    }

    
    
    

    template <typename T>
    inline void CoordinateSystem( const Vector3<T>& v1, Vector3<T>* v2, Vector3<T>* v3 )
    {
        Float sign = Math::CopySign( Float( 1 ), v1.z );
        Float a = -1 / ( sign + v1.z );
        Float b = v1.x * v1.y * a;
        *v2 = Vector3<T>( 1 + sign * Sqr( v1.x ) * a, sign * b, -sign * v1.x );
        *v3 = Vector3<T>( b, sign + Sqr( v1.y ) * a, -v1.y );
    }

    template <>
    inline void CoordinateSystem<Float>( const Vector3<Float>& v1, Vector3<Float>* v2, Vector3<Float>* v3 )
    {
        Float sign = Math::CopySign( Float( 1 ), v1.z );
        Float a = -1 / ( sign + v1.z );
        Float b = v1.x * v1.y * a;
        *v2 = Vector3<Float>( 1 + sign * Sqr( v1.x ) * a, sign * b, -sign * v1.x );
        *v3 = Vector3<Float>( b, sign + Sqr( v1.y ) * a, -v1.y );
    }

    

    template <typename T>
    inline void CoordinateSystem( const Normal3<T>& v1, Vector3<T>* v2, Vector3<T>* v3 )
    {
        Float sign = Math::CopySign( Float( 1 ), v1.z );
        Float a = -1 / ( sign + v1.z );
        Float b = v1.x * v1.y * a;
        *v2 = Vector3<T>( 1 + sign * Sqr( v1.x ) * a, sign * b, -sign * v1.x );
        *v3 = Vector3<T>( b, sign + Sqr( v1.y ) * a, -v1.y );
    }

    template<>
    inline void CoordinateSystem<Float>( const Normal3<Float>& v1, Vector3<Float>* v2, Vector3<Float>* v3 )
    {
        Float sign = Math::CopySign( Float( 1 ), v1.z );
        Float a = -1.f / ( sign + v1.z );
        Float b = v1.x * v1.y * a;
        *v2 = Vector3<Float>( 1 + sign * Sqr( v1.x ) * a, sign * b, -sign * v1.x );
        *v3 = Vector3<Float>( b, sign + Sqr( v1.y ) * a, -v1.y );
    }

    template <typename T>
    template <typename U>
    Vector3<T>::Vector3( const Normal3<U>& n )
        : Tuple3<pbrto::Vector3, T>( T( n.x ), T( n.y ), T( n.z ) )
    { }

    

    template <typename T>
    inline Normal3<T> FaceForward( Normal3<T> n, Vector3<T> v )
    {
        return ( Dot( n, v ) < 0.f ) ? -n : n;
    }
    template <>
    inline Normal3<Float> FaceForward<Float>( Normal3<Float> n, Vector3<Float> v )
    {
        return ( ScalarDot( n, v ) < 0.f ) ? Normal3<Float>( -n ) : n;
    }
    inline Normal3f::Simd FaceForward( Normal3f::Simd n, Vector3f::Simd v )
    {
        return ( ScalarDot( n, v ) < 0.f ) ? -n : n;
    }
    


    template <typename T>
    inline Normal3<T> FaceForward( Normal3<T> n, Normal3<T> n2 )
    {
        return ( Dot( n, n2 ) < 0.f ) ? -n : n;
    }

    template <>
    inline Normal3<Float> FaceForward<Float>( Normal3<Float> n, Normal3<Float> n2 )
    {
        return ( ScalarDot( n, n2 ) < 0.f ) ? Normal3<Float>( -n ) : n;
    }

    inline Normal3f::Simd FaceForward( Normal3f::Simd n, Normal3f::Simd n2 )
    {
        return ( ScalarDot( n, n2 ) < 0.f ) ? -n : n;
    }



    template <typename T>
    inline Vector3<T> FaceForward( Vector3<T> v, Vector3<T> v2 )
    {
        return ( Dot( v, v2 ) < 0.f ) ? -v : v;
    }

    template <>
    inline Vector3<Float> FaceForward<Float>( Vector3<Float> v, Vector3<Float> v2 )
    {
        return ( ScalarDot( v, v2 ) < 0.f ) ? Vector3<Float>( -v ) : v;
    }

    inline Vector3f::Simd FaceForward( Vector3f::Simd v, Vector3f::Simd v2 )
    {
        return ( ScalarDot( v, v2 ) < 0.f ) ? -v : v;
    }


    template <typename T>
    inline Vector3<T> FaceForward( Vector3<T> v, Normal3<T> n2 )
    {
        return ( Dot( v, n2 ) < 0.f ) ? -v : v;
    }

    template <>
    inline Vector3<Float> FaceForward<Float>( Vector3<Float> v, Normal3<Float> n2 )
    {
        return ( ScalarDot( v, n2 ) < 0.f ) ? Vector3<Float>( -v ) : v;
    }

    inline Vector3f::Simd FaceForward( Vector3f::Simd v, Normal3f::Simd n2 )
    {
        return ( ScalarDot( v, n2 ) < 0.f ) ? -v : v;
    }


    inline Float AngleBetween( Quaternion q1, Quaternion q2 )
    {
        if ( ScalarDot( q1, q2 ) < 0.f )
            return Pi - 2 * SafeASin( ScalarLength( q1 + q2 ) / 2 );
        else
            return 2 * SafeASin( ScalarLength( q2 - q1 ) / 2 );
    }

    inline Float AngleBetween( Quaternion::Simd q1, Quaternion::Simd q2 )
    {
        if ( ScalarDot( q1, q2 ) < 0.f )
            return Pi - 2 * SafeASin( ScalarLength( q1 + q2 ) / 2 );
        else
            return 2 * SafeASin( ScalarLength( q2 - q1 ) / 2 );
    }
    
    inline Quaternion Slerp( Float t, const Quaternion& q1, const Quaternion& q2 )
    {
        return Math::Slerp( q1, q2, t );
    }
    
    // Bounds2 Definition
    template <typename T>
    class Bounds2
    {
    public:
        // Bounds2 Public Members
        //Point2<T> pMin, pMax;
        
        union
        {
            struct
            {
                Point2<T> pMin, pMax;
            };
            std::array<Point2<T>, 2> boundaries_;
        };
        

        // Bounds2 Public Methods
        Bounds2( )
        {
            T minNum = std::numeric_limits<T>::lowest( );
            T maxNum = std::numeric_limits<T>::max( );
            pMin = Point2<T>( maxNum, maxNum );
            pMax = Point2<T>( minNum, minNum );
        }
        explicit Bounds2( const Point2<T>& p ) 
            : pMin( p ), pMax( p ) 
        { }

        Bounds2( const Point2<T>& p1, const Point2<T>& p2 )
            : pMin( Min( p1, p2 ) ), pMax( Max( p1, p2 ) ) 
        { }

        Bounds2( const Bounds2& other )
            : pMin( other.pMin ), pMax( other.pMax )
        { }

        template <typename U>
            requires ( std::is_same_v<T,U> == false )
        explicit Bounds2( const Bounds2<U>& b )
        {
            if ( b.IsEmpty( ) )
                // Be careful about overflowing float->int conversions and the
                // like.
                *this = Bounds2<T>( );
            else
            {
                pMin = Point2<T>( b.pMin );
                pMax = Point2<T>( b.pMax );
            }
        }

        Bounds2& operator = ( const Bounds2& other )
        {
            pMin = other.pMin; 
            pMax = other.pMax;
            return *this;
        }

        Vector2<T> Diagonal( ) const 
        { 
            return pMax - pMin; 
        }

        T Area( ) const
        {
            Vector2<T> d = pMax - pMin;
            return d.x * d.y;
        }

        bool IsEmpty( ) const 
        { 
            return pMin.x >= pMax.x || pMin.y >= pMax.y; 
        }

        bool IsDegenerate( ) const 
        { 
            return pMin.x > pMax.x || pMin.y > pMax.y; 
        }

        int MaxDimension( ) const
        {
            Vector2<T> diag = Diagonal( );
            if ( diag.x > diag.y )
                return 0;
            else
                return 1;
        }
        const Point2<T>& operator[]( int i ) const
        {
            NDCHECK( i == 0 || i == 1 );
            return boundaries_[ i ];
            //return ( i == 0 ) ? pMin : pMax;
        }
        Point2<T>& operator[]( int i )
        {
            NDCHECK( i == 0 || i == 1 );
            return boundaries_[ i ];
            //return ( i == 0 ) ? pMin : pMax;
        }
        bool operator==( const Bounds2<T>& b ) const
        {
            return b.pMin == pMin && b.pMax == pMax;
        }
        bool operator!=( const Bounds2<T>& b ) const
        {
            return b.pMin != pMin || b.pMax != pMax;
        }
        PBRT_CPU_GPU
            Point2<T> Corner( int corner ) const
        {
            NDCHECK( corner >= 0 && corner < 4 );
            return Point2<T>( ( *this )[ ( corner & 1 ) ].x, ( *this )[ ( corner & 2 ) ? 1 : 0 ].y );
        }

        Point2<T> Lerp2( Point2f t ) const
        {
            return Point2<T>(
                    pbrto::Lerp2( t.x, pMin.x, pMax.x ),
                    pbrto::Lerp2( t.y, pMin.y, pMax.y ) );
        }
        PBRT_CPU_GPU
            Vector2<T> Offset( Point2<T> p ) const
        {
            Vector2<T> o = p - pMin;
            if ( pMax.x > pMin.x )
                o.x /= pMax.x - pMin.x;
            if ( pMax.y > pMin.y )
                o.y /= pMax.y - pMin.y;
            return o;
        }
        PBRT_CPU_GPU
            void BoundingSphere( Point2<T>* c, Float* rad ) const
        {
            *c = ( pMin + pMax ) / 2;
            *rad = Inside( *c, *this ) ? ScalarDistance( *c, pMax ) : 0;
        }

        std::string ToString( ) const { return StringPrintf( "[ %s - %s ]", pMin, pMax ); }

        
    };

    // Bounds3 Definition
    template <typename T>
    class Bounds3
    {
    public:
        // Bounds3 Public Members
        //Point3<T> pMin, pMax;
        
        union
        { 
            struct
            { 
                Point3<T> pMin, pMax;
            };
            std::array<Point3<T>, 2> boundaries_;
        };
        

        // Bounds3 Public Methods
        Bounds3( )
        {
            T minNum = std::numeric_limits<T>::lowest( );
            T maxNum = std::numeric_limits<T>::max( );
            pMin = Point3<T>( maxNum, maxNum, maxNum );
            pMax = Point3<T>( minNum, minNum, minNum );
        }

        explicit Bounds3( const Point3<T>& p ) 
            : pMin( p ), pMax( p ) 
        { }

        Bounds3( const Point3<T>& p1, const Point3<T>& p2 )
            : pMin( Min( p1, p2 ) ), pMax( Max( p1, p2 ) ) 
        { }

        Bounds3( const Bounds3& bounds )
            : pMin( bounds.pMin ), pMax( bounds.pMax )
        { }

        template <typename U>
            requires ( std::is_same_v<T, U> == false )
        explicit Bounds3( const Bounds3<U>& b )
        {
            if ( b.IsEmpty( ) )
                // Be careful about overflowing float->int conversions and the
                // like.
                *this = Bounds3<T>( );
            else
            {
                pMin = Point3<T>( b.pMin );
                pMax = Point3<T>( b.pMax );
            }
        }

        Bounds3& operator = ( const Bounds3& other )
        {
            pMin = other.pMin;
            pMax = other.pMax;
            return *this;
        }

        const Point3<T>& operator[]( int i ) const
        {
            NDCHECK( i == 0 || i == 1 );
            return boundaries_[ i ];
        }
        Point3<T>& operator[]( int i )
        {
            NDCHECK( i == 0 || i == 1 );
            return boundaries_[ i ];
        }

        typename Point3<T>::Simd Corner( int corner ) const 
        {
            NDCHECK( corner >= 0 && corner < 8 );
            /*
            return Point3<T>( 
                ( *this )[ ( corner & 1 ) ].x, 
                ( *this )[ ( corner & 2 ) ? 1 : 0 ].y,
                ( *this )[ ( corner & 4 ) ? 1 : 0 ].z );
            */
            using Point = typename Point3<T>::Simd;
            switch ( corner )
            {
                case 0:
                {
                    return pMin;
                }
                break;
                case 1:
                {
                    return Point( pMax.x, pMin.y, pMin.z );
                }
                break;
                case 2:
                {
                    return Point( pMin.x, pMax.y, pMin.z );
                }
                break;
                case 3:
                {
                    return Point( pMax.x, pMax.y, pMin.z );
                }
                break;
                case 4:
                {
                    return Point( pMin.x, pMin.y, pMax.z );
                }
                break;
                case 5:
                {
                    return Point( pMax.x, pMin.y, pMax.z );
                }
                break;
                case 6:
                {
                    return Point( pMin.x, pMax.y, pMax.z );
                }
                break;
                //case 7:
                default:
                {
                    return pMax;
                }
                break;
            }
        }

        typename Vector3<T>::Simd Diagonal( ) const
        { 
            return pMax - pMin; 
        }

        T SurfaceArea( ) const
        {
            if constexpr ( std::is_same_v<Float, T> )
            {
                auto d = pMax - pMin;

                /*
                d.x * d.y + 
                d.x * d.z + 
                d.y * d.z
                */
                using Traits = SIMD::Traits<Float, 3>;
                auto result = 2.f * Traits::First( Traits::HSum( Traits::Mul( Traits::Swizzle< Math::SIMD::Shuffle_v<3, 1, 0, 0>>( d.simd ), Traits::Swizzle< Math::SIMD::Shuffle_v<3, 2, 2, 1>>( d.simd ) ) ) );
                return result;

                //return 2 * ( d.x * d.y + d.x * d.z + d.y * d.z );
            }
            else
            {
                Vector3<T> d = Diagonal( );
                return 2 * ( d.x * d.y + d.x * d.z + d.y * d.z );
            }
        }

        T Volume( ) const
        {
            Vector3<T> d = Diagonal( );
            return d.x * d.y * d.z;
        }

        int MaxDimension( ) const
        {
            Vector3<T> d = Diagonal( );
            if ( d.x > d.y && d.x > d.z )
                return 0;
            else if ( d.y > d.z )
                return 1;
            else
                return 2;
        }

        Point3f::Simd Lerp2( Point3f::Simd t ) const
        {
            return Point3f::Simd( Math::Lerp2( t, pMin, pMax  ) );
            /*
            return Point3f( 
                pbrto::Lerp2( t.x, pMin.x, pMax.x ), 
                pbrto::Lerp2( t.y, pMin.y, pMax.y ),
                pbrto::Lerp2( t.z, pMin.z, pMax.z ) );
             */
        }

        Vector3f::Simd Offset( Point3f::Simd p ) const
        {
            using Traits = Vector3f::Traits;
            Point3f::Simd maxP( pMax );
            Point3f::Simd minP( pMin );

            Vector3f::Simd o = p - minP;
            auto greater = Traits::Greater( maxP.simd, minP.simd );
            auto oAdjusted = Traits::Div( o.simd, Traits::Sub( maxP.simd, minP.simd ) );
            auto result = Traits::Select( o.simd, oAdjusted, greater );
            return Vector3f::Simd( result );

            /*
            Vector3f o = p - pMin;
            if ( pMax.x > pMin.x )
                o.x /= pMax.x - pMin.x;
            if ( pMax.y > pMin.y )
                o.y /= pMax.y - pMin.y;
            if ( pMax.z > pMin.z )
                o.z /= pMax.z - pMin.z;
            return o;
            */
        }

        void BoundingSphere( Point3<T>* center, Float* radius ) const
        {
            *center = ( pMin + pMax ) / 2;
            *radius = Inside( *center, *this ) ? ScalarDistance( *center, pMax ) : 0;
        }
        void BoundingSphere( Point3f::Simd* center, Float* radius ) const
        {
            *center = ( pMin + pMax ) / 2;
            *radius = Inside( Point3f(*center), *this ) ? ScalarDistance( *center, pMax ) : 0;
        }

        bool IsEmpty( ) const
        {
            return pMin.x >= pMax.x || 
                   pMin.y >= pMax.y || 
                   pMin.z >= pMax.z;
        }
        bool IsDegenerate( ) const
        {
            return 
                pMin.x > pMax.x || 
                pMin.y > pMax.y || 
                pMin.z > pMax.z;
        }

        
        PBRT_CPU_GPU
        bool operator==( const Bounds3<T>& b ) const
        {
            return b.pMin == pMin && b.pMax == pMax;
        }
        PBRT_CPU_GPU
        bool operator!=( const Bounds3<T>& b ) const
        {
            return b.pMin != pMin || b.pMax != pMax;
        }
        PBRT_CPU_GPU
        bool IntersectP( Point3f::Simd o, Vector3f::Simd d, Float tMax = Infinity, Float* hitt0 = nullptr, Float* hitt1 = nullptr ) const;
        PBRT_CPU_GPU
        bool IntersectP( Point3f o, Vector3f d, Float tMax, Vector3f invDir, const int dirIsNeg[ 3 ] ) const;

        std::string ToString( ) const { return StringPrintf( "[ %s - %s ]", pMin, pMax ); }

        
    };

    // Bounds[23][fi] Definitions
    using Bounds2f = Bounds2<Float>;
    using Bounds2i = Bounds2<int>;
    using Bounds3f = Bounds3<Float>;
    using Bounds3i = Bounds3<int>;

    class Bounds2iIterator : public std::forward_iterator_tag
    {
        Point2i p;
        const Bounds2i* bounds;
    public:
        Bounds2iIterator( const Bounds2i& b, const Point2i& pt ) 
            : p( pt ), bounds( &b ) 
        { }
        Bounds2iIterator operator++( )
        {
            advance( );
            return *this;
        }
        Bounds2iIterator operator++( int )
        {
            Bounds2iIterator old = *this;
            advance( );
            return old;
        }
        bool operator==( const Bounds2iIterator& bi ) const
        {
            return p == bi.p && bounds == bi.bounds;
        }
        bool operator!=( const Bounds2iIterator& bi ) const
        {
            return p != bi.p || bounds != bi.bounds;
        }

        Point2i operator*( ) const 
        { 
            return p; 
        }

    private:
        void advance( )
        {
            ++p.x;
            if ( p.x == bounds->pMax.x )
            {
                p.x = bounds->pMin.x;
                ++p.y;
            }
        }
        
    };

    // Bounds2 Inline Functions
    template <typename T>
    PBRT_CPU_GPU inline Bounds2<T> Union( const Bounds2<T>& b1, const Bounds2<T>& b2 )
    {
        // Be careful to not run the two-point Bounds constructor.
        Bounds2<T> ret;
        ret.pMin = Min( b1.pMin, b2.pMin );
        ret.pMax = Max( b1.pMax, b2.pMax );
        return ret;
    }

    template <typename T>
    PBRT_CPU_GPU inline Bounds2<T> Intersect( const Bounds2<T>& b1, const Bounds2<T>& b2 )
    {
        // Be careful to not run the two-point Bounds constructor.
        Bounds2<T> b;
        b.pMin = Max( b1.pMin, b2.pMin );
        b.pMax = Min( b1.pMax, b2.pMax );
        return b;
    }

    template <typename T>
    PBRT_CPU_GPU inline bool Overlaps( const Bounds2<T>& ba, const Bounds2<T>& bb )
    {
        bool x = 
            ( ba.pMax.x >= bb.pMin.x ) && 
            ( ba.pMin.x <= bb.pMax.x );
        bool y = 
            ( ba.pMax.y >= bb.pMin.y ) && 
            ( ba.pMin.y <= bb.pMax.y );
        return ( x && y );
    }

    template <typename T>
    PBRT_CPU_GPU inline bool Inside( Point2<T> pt, const Bounds2<T>& b )
    {
        return ( 
            pt.x >= b.pMin.x && 
            pt.y >= b.pMin.y &&
            pt.x <= b.pMax.x &&
            pt.y <= b.pMax.y );
    }

    template <typename T>
    PBRT_CPU_GPU inline bool Inside( const Bounds2<T>& ba, const Bounds2<T>& bb )
    {
        return ( ba.pMin.x >= bb.pMin.x && ba.pMax.x <= bb.pMax.x && ba.pMin.y >= bb.pMin.y &&
            ba.pMax.y <= bb.pMax.y );
    }

    template <typename T>
    PBRT_CPU_GPU inline bool InsideExclusive( Point2<T> pt, const Bounds2<T>& b )
    {
        return ( pt.x >= b.pMin.x && pt.x < b.pMax.x && pt.y >= b.pMin.y && pt.y < b.pMax.y );
    }

    template <typename T, typename U>
    PBRT_CPU_GPU inline Bounds2<T> Expand( const Bounds2<T>& b, U delta )
    {
        Bounds2<T> ret;
        ret.pMin = b.pMin - Vector2<T>( delta, delta );
        ret.pMax = b.pMax + Vector2<T>( delta, delta );
        return ret;
    }

    // Bounds3 Inline Functions
    template <typename T>
    inline Bounds3<T> Union( const Bounds3<T>& b, Point3<T> p )
    {
        Bounds3<T> ret;
        ret.pMin = Min( b.pMin, p );
        ret.pMax = Max( b.pMax, p );
        return ret;
    }

    inline Bounds3f Union( const Bounds3f& b, Point3f::Simd p )
    {
        Bounds3f ret;
        ret.pMin = Min( b.pMin, p );
        ret.pMax = Max( b.pMax, p );
        return ret;
    }


    template <typename T>
    PBRT_CPU_GPU inline Bounds3<T> Union( const Bounds3<T>& b1, const Bounds3<T>& b2 )
    {
        Bounds3<T> ret;
        ret.pMin = Min( b1.pMin, b2.pMin );
        ret.pMax = Max( b1.pMax, b2.pMax );
        return ret;
    }

    template <typename T>
    PBRT_CPU_GPU inline Bounds3<T> Intersect( const Bounds3<T>& b1, const Bounds3<T>& b2 )
    {
        Bounds3<T> b;
        b.pMin = Max( b1.pMin, b2.pMin );
        b.pMax = Min( b1.pMax, b2.pMax );
        return b;
    }

    template <typename T>
    PBRT_CPU_GPU inline bool Overlaps( const Bounds3<T>& b1, const Bounds3<T>& b2 )
    {
        bool x = ( b1.pMax.x >= b2.pMin.x ) && ( b1.pMin.x <= b2.pMax.x );
        bool y = ( b1.pMax.y >= b2.pMin.y ) && ( b1.pMin.y <= b2.pMax.y );
        bool z = ( b1.pMax.z >= b2.pMin.z ) && ( b1.pMin.z <= b2.pMax.z );
        return ( x && y && z );
    }

    template <typename T>
    inline bool Inside( Point3<T> p, const Bounds3<T>& b )
    {
        return ( 
            p.x >= b.pMin.x && 
            p.y >= b.pMin.y &&
            p.z >= b.pMin.z &&
            p.x <= b.pMax.x &&
            p.y <= b.pMax.y &&
            p.z <= b.pMax.z );
    }

    template <>
    inline bool Inside<float>( Point3<float> p, const Bounds3<float>& b )
    {
        using Traits = Point3<float>::Traits;
        auto pmm = Traits::Load( p.values );
        return Traits::AllGreaterOrEqual( pmm, Traits::Load( b.pMin.values ) ) &&
            Traits::AllLessOrEqual( pmm, Traits::Load( b.pMax.values ) );
    }

    inline bool Inside( Point3f::Simd p, const Bounds3<float>& b )
    {
        using Traits = Point3<float>::Traits;
        return Traits::AllGreaterOrEqual( p.simd, Traits::Load( b.pMin.values ) ) &&
            Traits::AllLessOrEqual( p.simd, Traits::Load( b.pMax.values ) );
    }


    template <typename T>
    inline bool InsideExclusive( Point3<T> p, const Bounds3<T>& b )
    {
        return ( 
            p.x >= b.pMin.x && 
            p.y >= b.pMin.y &&
            p.z >= b.pMin.z &&
            p.x < b.pMax.x &&
            p.y < b.pMax.y &&
            p.z < b.pMax.z );
    }

    template <>
    inline bool InsideExclusive<float>( Point3<float> p, const Bounds3<float>& b )
    {
        using Traits = Point3<float>::Traits;
        auto pmm = Traits::Load( p.values );
        return Traits::AllGreaterOrEqual( pmm, Traits::Load( b.pMin.values ) ) &&
            Traits::AllLess( pmm, Traits::Load( b.pMax.values ) );
    }

    inline bool InsideExclusive( Point3f::Simd p, const Bounds3<float>& b )
    {
        using Traits = Point3<float>::Traits;
        return Traits::AllGreaterOrEqual( p.simd, Traits::Load( b.pMin.values ) ) &&
            Traits::AllLess( p.simd, Traits::Load( b.pMax.values ) );
    }


    template <typename T, typename U>
    PBRT_CPU_GPU inline auto ScalarDistanceSquared( Point3<T> p, const Bounds3<U>& b )
    {
        using TDist = decltype( T{} - U{} );
        TDist dx = std::max<TDist>( { 0, b.pMin.x - p.x, p.x - b.pMax.x } );
        TDist dy = std::max<TDist>( { 0, b.pMin.y - p.y, p.y - b.pMax.y } );
        TDist dz = std::max<TDist>( { 0, b.pMin.z - p.z, p.z - b.pMax.z } );
        return Sqr( dx ) + Sqr( dy ) + Sqr( dz );
    }

    template <>
    inline auto ScalarDistanceSquared<float,float>( Point3<float> p, const Bounds3<float>& b )
    {
        using Traits = Point3<float>::Traits;
        auto pmm = Traits::Load( p.values );
        auto pMin = Traits::Load( b.pMin.values );
        auto pMax = Traits::Load( b.pMax.values );
        auto rmm = Traits::Max( Traits::Zero( ), Traits::Max( Traits::Sub( pMin, pmm ), Traits::Sub( pmm, pMax ) ) );
        return Traits::First( Traits::HSum( Traits::Mul( rmm, rmm ) ) );
    }

    inline auto ScalarDistanceSquared( Point3f::Simd p, const Bounds3<float>& b )
    {
        using Traits = Point3<float>::Traits;
        auto pMin = Traits::Load( b.pMin.values );
        auto pMax = Traits::Load( b.pMax.values );
        auto rmm = Traits::Max( Traits::Zero( ), Traits::Max( Traits::Sub( pMin, p.simd ), Traits::Sub( p.simd, pMax ) ) );
        return Traits::First( Traits::HSum( Traits::Mul( rmm, rmm ) ) );
    }


    template <typename T, typename U>
    inline auto ScalarDistance( Point3<T> p, const Bounds3<U>& b )
    {
        auto dist2 = ScalarDistanceSquared( p, b );
        using TDist = typename TupleLength<decltype( dist2 )>::type;
        return Math::Sqrt( TDist( dist2 ) );
    }

    inline auto ScalarDistance( Point3f::Simd p, const Bounds3<float>& b )
    {
        auto dist2 = ScalarDistanceSquared( p, b );
        return Math::Sqrt( dist2 );
    }

    template <typename T, typename U>
    PBRT_CPU_GPU inline Bounds3<T> Expand( const Bounds3<T>& b, U delta )
    {
        Bounds3<T> ret;
        ret.pMin = b.pMin - Vector3<T>( delta, delta, delta );
        ret.pMax = b.pMax + Vector3<T>( delta, delta, delta );
        return ret;
    }

    template <typename T>
    inline bool Bounds3<T>::IntersectP( Point3f::Simd o, Vector3f::Simd d, Float tMax, Float* hitt0, Float* hitt1 ) const
    {
        using Traits = Vector3f::Traits;
        Float t0 = 0, t1 = tMax;

        // Update interval for _i_th bounding box slab
        Vector3f::Simd invRayDir = Math::Reciprocal( d );
        Vector3f::Simd vNear = ( pMin - o ) * invRayDir;
        Vector3f::Simd vFar = ( pMax - o ) * invRayDir;

        // Update parametric interval from slab intersection $t$ values
        auto greater = Traits::Greater( vNear.simd, vFar.simd );
        Vector3f::Simd nearV = Traits::Select( vNear.simd, vFar.simd, greater );
        Vector3f::Simd farV = Traits::Select( vFar.simd, vNear.simd, greater );

        // Update _tFar_ to ensure robust ray--bounds intersection
        farV *= 1.f + 2.f * gamma( 3 );

        Vector3f n( nearV );
        Vector3f f( farV );

        for ( int i = 0; i < 3; ++i )
        {
            Float tNear = n[ i ];
            Float tFar = f[ i ];

            t0 = tNear > t0 ? tNear : t0;
            t1 = tFar < t1 ? tFar : t1;
            if ( t0 > t1 )
                return false;
        }
        if ( hitt0 )
            *hitt0 = t0;
        if ( hitt1 )
            *hitt1 = t1;
        return true;
    }

    template <typename T>
    inline bool Bounds3<T>::IntersectP( Point3f o, Vector3f d, Float raytMax, Vector3f invDir, const int dirIsNeg[ 3 ] ) const
    {
        const Bounds3f& bounds = *this;
        // Check for ray intersection against $x$ and $y$ slabs
        Float tMin = ( bounds[ dirIsNeg[ 0 ] ].x - o.x ) * invDir.x;
        Float tMax = ( bounds[ 1 - dirIsNeg[ 0 ] ].x - o.x ) * invDir.x;
        Float tyMin = ( bounds[ dirIsNeg[ 1 ] ].y - o.y ) * invDir.y;
        Float tyMax = ( bounds[ 1 - dirIsNeg[ 1 ] ].y - o.y ) * invDir.y;
        // Update _tMax_ and _tyMax_ to ensure robust bounds intersection
        tMax *= 1 + 2 * gamma( 3 );
        tyMax *= 1 + 2 * gamma( 3 );

        if ( tMin > tyMax || tyMin > tMax )
            return false;
        if ( tyMin > tMin )
            tMin = tyMin;
        if ( tyMax < tMax )
            tMax = tyMax;

        // Check for ray intersection against $z$ slab
        Float tzMin = ( bounds[ dirIsNeg[ 2 ] ].z - o.z ) * invDir.z;
        Float tzMax = ( bounds[ 1 - dirIsNeg[ 2 ] ].z - o.z ) * invDir.z;
        // Update _tzMax_ to ensure robust bounds intersection
        tzMax *= 1 + 2 * gamma( 3 );

        if ( tMin > tzMax || tzMin > tMax )
            return false;
        if ( tzMin > tMin )
            tMin = tzMin;
        if ( tzMax < tMax )
            tMax = tzMax;

        return ( tMin < raytMax ) && ( tMax > 0 );
    }

    PBRT_CPU_GPU
        inline Bounds2iIterator begin( const Bounds2i& b )
    {
        return Bounds2iIterator( b, b.pMin );
    }

    PBRT_CPU_GPU
        inline Bounds2iIterator end( const Bounds2i& b )
    {
        // Normally, the ending point is at the minimum x value and one past
        // the last valid y value.
        Point2i pEnd( b.pMin.x, b.pMax.y );
        // However, if the bounds are degenerate, override the end point to
        // equal the start point so that any attempt to iterate over the bounds
        // exits out immediately.
        if ( b.pMin.x >= b.pMax.x || b.pMin.y >= b.pMax.y )
            pEnd = b.pMin;
        return Bounds2iIterator( b, pEnd );
    }

    template <typename T>
    PBRT_CPU_GPU inline Bounds2<T> Union( const Bounds2<T>& b, Point2<T> p )
    {
        // Be careful to not run the two-point Bounds constructor.
        Bounds2<T> ret;
        ret.pMin = Min( b.pMin, p );
        ret.pMax = Max( b.pMax, p );
        return ret;
    }

    // Spherical Geometry Inline Functions
    inline Float SphericalTriangleArea( const Vector3f::Simd a, const Vector3f::Simd b, const Vector3f::Simd c )
    {
        return Math::FastAbs( 2.f * Math::ATan2( ScalarDot( a, Cross( b, c ) ), 1.f + ScalarDot( a, b ) + ScalarDot( a, c ) + ScalarDot( b, c ) ) );
    }

    inline Float SphericalQuadArea( const Vector3f::Simd a, const Vector3f::Simd b, const Vector3f::Simd c, const Vector3f::Simd d )
    {
        using Traits = typename Vector3f::Traits;
        auto axb = Math::Cross( a, b );
        auto bxc = Math::Cross( b, c );
        auto cxd = Math::Cross( c, d );
        auto dxa = Math::Cross( d, a );


        if ( Math::ScalarLengthSquared( axb ) == 0 ||
            Math::ScalarLengthSquared( bxc ) == 0 ||
            Math::ScalarLengthSquared( cxd ) == 0 ||
            Math::ScalarLengthSquared( dxa ) == 0 )
            return 0;
        axb = Normalize( axb );
        bxc = Normalize( bxc );
        cxd = Normalize( cxd );
        dxa = Normalize( dxa );

        Float alpha = Math::ScalarAngleBetween( dxa, -axb );
        Float beta = Math::ScalarAngleBetween( axb, -bxc );
        Float gamma = Math::ScalarAngleBetween( bxc, -cxd );
        Float delta = Math::ScalarAngleBetween( cxd, -dxa );

        return Math::FastAbs( alpha + beta + gamma + delta - 2 * Pi );
    }

    inline Vector3f::Simd SphericalDirection( Float sinTheta, Float cosTheta, Float phi )
    {
        NDCHECK( sinTheta >= -1.0001 && sinTheta <= 1.0001 );
        NDCHECK( cosTheta >= -1.0001 && cosTheta <= 1.0001 );

        Float sinPhi;
        Float cosPhi;
        SinCos( phi, &sinPhi, &cosPhi );

        return Vector3f::Simd( 
            Math::Clamp( sinTheta, -1.0f, 1.0f ) * cosPhi,
            Math::Clamp( sinTheta, -1.0f, 1.0f ) * sinPhi, 
            Math::Clamp( cosTheta, -1.0f, 1.0f ) );
    }

    inline Float SphericalTheta( const Vector3f v )
    {
        return SafeACos( v.z );
    }
    inline Float SphericalTheta( const Vector3f::Simd v )
    {
        return SafeACos( v.z( ) );
    }

    inline Float SphericalPhi( const Vector3f v )
    {
        Float p = Math::ATan2( v.y, v.x );
        return ( p < 0 ) ? ( p + 2.f * Pi ) : p;
    }
    inline Float SphericalPhi( const Vector3f::Simd v )
    {
        Float p = Math::ATan2( v.y( ), v.x( ) );
        return ( p < 0 ) ? ( p + 2.f * Pi ) : p;
    }

    inline Float CosTheta( const Vector3f w )
    {
        return w.z;
    }
    inline Float CosTheta( const Vector3f::Simd w )
    {
        return w.z( );
    }

    inline Float Cos2Theta( const Vector3f w )
    {
        return Sqr( w.z );
    }
    inline Float Cos2Theta( const Vector3f::Simd w )
    {
        return Sqr( w.z( ) );
    }

    inline Float AbsCosTheta( const Vector3f w )
    {
        return Math::FastAbs( w.z );
    }
    inline Float AbsCosTheta( const Vector3f::Simd w )
    {
        return Math::FastAbs( w.z( ) );
    }

    inline Float Sin2Theta( const Vector3f w )
    {
        return std::max<Float>( 0.f, 1.f - Cos2Theta( w ) );
    }
    inline Float Sin2Theta( const Vector3f::Simd w )
    {
        return std::max<Float>( 0.f, 1.f - Cos2Theta( w ) );
    }
    inline Float SinTheta( const Vector3f w )
    {
        return Math::Sqrt( Sin2Theta( w ) );
    }
    inline Float SinTheta( const Vector3f::Simd w )
    {
        return Math::Sqrt( Sin2Theta( w ) );
    }

    inline Float TanTheta( const Vector3f w )
    {
        return SinTheta( w ) / CosTheta( w );
    }
    inline Float TanTheta( const Vector3f::Simd w )
    {
        return SinTheta( w ) / CosTheta( w );
    }
    inline Float Tan2Theta( const Vector3f w )
    {
        return Sin2Theta( w ) / Cos2Theta( w );
    }
    inline Float Tan2Theta( const Vector3f::Simd w )
    {
        return Sin2Theta( w ) / Cos2Theta( w );
    }

    inline Float CosPhi( const Vector3f w )
    {
        Float sinTheta = SinTheta( w );
        return ( sinTheta == 0 ) ? 1 : Math::Clamp( w.x / sinTheta, -1.f, 1.f );
    }
    inline Float CosPhi( const Vector3f::Simd w )
    {
        Float sinTheta = SinTheta( w );
        return ( sinTheta == 0 ) ? 1 : Math::Clamp( w.x( ) / sinTheta, -1.f, 1.f );
    }

    inline Float SinPhi( const Vector3f w )
    {
        Float sinTheta = SinTheta( w );
        return ( sinTheta == 0 ) ? 0 : Math::Clamp( w.y / sinTheta, -1.f, 1.f );
    }
    inline Float SinPhi( const Vector3f::Simd w )
    {
        Float sinTheta = SinTheta( w );
        return ( sinTheta == 0 ) ? 0 : Math::Clamp( w.y() / sinTheta, -1.f, 1.f );
    }


    inline Float CosDPhi( const Vector3f wa, const Vector3f wb )
    {
        Float waxy = Sqr( wa.x ) + Sqr( wa.y ); 
        Float wbxy = Sqr( wb.x ) + Sqr( wb.y );
        if ( waxy == 0.f || wbxy == 0.f )
            return 1.f;
        return Math::Clamp( ( wa.x * wb.x + wa.y * wb.y ) / Math::Sqrt( waxy * wbxy ), -1.f, 1.f );
    }
    inline Float CosDPhi( const Vector3f::Simd wa, const Vector3f::Simd wb )
    {
        Float wax = wa.x( );
        Float way = wa.y( );
        Float wbx = wb.x( );
        Float wby = wb.y( );

        Float waxy = Sqr( wax ) + Sqr( way );
        Float wbxy = Sqr( wbx ) + Sqr( wby );
        if ( waxy == 0.f || wbxy == 0.f )
            return 1.f;
        return Math::Clamp( ( wax * wbx + way * wby ) / Math::Sqrt( waxy * wbxy ), -1.f, 1.f );
    }

    inline bool SameHemisphere( const Vector3f w, const Vector3f wp )
    {
        return w.z * wp.z > 0;
    }
    inline bool SameHemisphere( const Vector3f::Simd w, const Vector3f::Simd wp )
    {
        return w.z() * wp.z() > 0;
    }


    inline bool SameHemisphere( const Vector3f w, const Normal3f wp )
    {
        return w.z * wp.z > 0;
    }
    inline bool SameHemisphere( const Vector3f::Simd w, const Normal3f::Simd wp )
    {
        return w.z( ) * wp.z( ) > 0;
    }

    // OctahedralVector Definition
    class OctahedralVector
    {
        // OctahedralVector Private Members
        uint16_t x = 0, y = 0;
    public:
        // OctahedralVector Public Methods
        OctahedralVector( ) = default;
        OctahedralVector( const Vector3f vec )
        {
            //Vector3f v = vec / ( Math::FastAbs( vec.x ) + Math::FastAbs( vec.y ) + Math::FastAbs( vec.z ) );
            Vector3f v = vec / Math::HSum( Math::FastAbs( vec ) );

            if ( v.z >= 0 )
            {
                x = Encode( v.x );
                y = Encode( v.y );
            }
            else
            {
                // Encode octahedral vector with $z < 0$
                x = Encode( Math::CopySign( 1 - Math::FastAbs( v.y ), v.x ) );
                y = Encode( Math::CopySign( 1 - Math::FastAbs( v.x ), v.y ) );
            }
        }

        OctahedralVector( const Vector3f::Simd vec )
        {
            Vector3f v = vec / Math::HSum( Math::FastAbs( vec ) );

            if ( v.z >= 0 )
            {
                x = Encode( v.x );
                y = Encode( v.y );
            }
            else
            {
                // Encode octahedral vector with $z < 0$
                x = Encode( Math::CopySign( 1 - Math::FastAbs( v.y ), v.x ) );
                y = Encode( Math::CopySign( 1 - Math::FastAbs( v.x ), v.y ) );
            }
        }


        explicit operator Vector3f( ) const
        {
            Vector3f v;
            v.x = -1 + 2 * ( x / 65535.f );
            v.y = -1 + 2 * ( y / 65535.f );
            v.z = 1 - ( Math::FastAbs( v.x ) + Math::FastAbs( v.y ) );
            // Reparameterize directions in the $z<0$ portion of the octahedron
            if ( v.z < 0 )
            {
                Float xo = v.x;
                //v.x = ( 1 - Math::FastAbs( v.y ) ) * Sign( xo );
                //v.y = ( 1 - Math::FastAbs( xo ) ) * Sign( v.y );
                v.x = Math::CopySign( 1 - Math::FastAbs( v.y ), xo );
                v.y = Math::CopySign( 1 - Math::FastAbs( xo ), v.y );
            }

            return Normalize( v );
        }

        std::string ToString( ) const
        {
            return std::format( "[ OctahedralVector x: {} y: {} ]", x, y );
        }
    private:
        // OctahedralVector Private Methods
        static Float Sign( Float v )
        {
            return Math::CopySign( 1.f, v );
        }

        static uint16_t Encode( Float f )
        {
            return static_cast< uint16_t >( Math::Round( Math::Clamp( ( f + 1 ) / 2, 0.f, 1.f ) * 65535.f ) );
        }


    };

    // DirectionCone Definition
    class DirectionCone
    {
    public:
        // DirectionCone Public Members
        Vector3f::Simd w;
        Float cosTheta = Infinity;

        // DirectionCone Public Methods
        DirectionCone( ) = default;

        DirectionCone( const Vector3f::Simd& w, Float cosTheta )
            : w( Normalize( w ) ), cosTheta( cosTheta )
        {
        }

        explicit DirectionCone( const Vector3f::Simd& w )
            : DirectionCone( w, 1 )
        {
        }

        bool IsEmpty( ) const
        {
            return cosTheta == Infinity;
        }

        static DirectionCone EntireSphere( )
        {
            return DirectionCone( Vector3f::Simd( 0, 0, 1 ), -1 );
        }

        Vector3f::Simd ClosestVectorInCone( const Vector3f::Simd& wp ) const;
    };

    // DirectionCone Inline Functions
    inline bool Inside( const DirectionCone& d, const Vector3f::Simd& w )
    {
        return !d.IsEmpty( ) && Math::ScalarDot( d.w, Normalize( w ) ) >= d.cosTheta;
    }

    inline DirectionCone BoundSubtendedDirections( const Bounds3f& b, const Point3f::Simd& p )
    {
        // Compute bounding sphere for _b_ and check if _p_ is inside
        Float radius;
        Point3f::Simd pCenter;
        b.BoundingSphere( &pCenter, &radius );
        if ( ScalarDistanceSquared( p, pCenter ) < Sqr( radius ) )
        {
            return DirectionCone::EntireSphere( );
        }

        // Compute and return _DirectionCone_ for bounding sphere
        Vector3f::Simd w = Normalize( pCenter - p );
        Float sin2ThetaMax = Sqr( radius ) / ScalarDistanceSquared( pCenter, p );

        Float cosThetaMax = Math::SafeSqrt( 1 - sin2ThetaMax );
        return DirectionCone( w, cosThetaMax );
    }

    inline Vector3f::Simd DirectionCone::ClosestVectorInCone( const Vector3f::Simd& wpv ) const
    {
        NDCHECK( !IsEmpty( ) );
        Vector3f::Simd wp = Normalize( wpv );
        // Return provided vector if it is inside the cone
        if ( ScalarDot( wp, w ) > cosTheta )
            return wp;

        // Find closest vector by rotating _wp_ until it touches the cone
        Float sinTheta = -Math::SafeSqrt( 1 - cosTheta * cosTheta );
        Vector3f::Simd a = Cross( wp, w );
        Vector3f wTmp( w );
        Vector3f wpTmp( wp );
        return cosTheta * w +
            ( sinTheta / Length( a ) ) *
            Vector3f::Simd(
                wTmp.x * ( wpTmp.y * wTmp.y + wpTmp.z * wTmp.z ) - wpTmp.x * ( Sqr( wTmp.y ) + Sqr( wTmp.z ) ),
                wTmp.y * ( wpTmp.x * wTmp.x + wpTmp.z * wTmp.z ) - wpTmp.y * ( Sqr( wTmp.x ) + Sqr( wTmp.z ) ),
                wTmp.z * ( wpTmp.x * wTmp.x + wpTmp.y * wTmp.y ) - wpTmp.z * ( Sqr( wTmp.x ) + Sqr( wTmp.y ) ) );
    }

    // DirectionCone Function Declarations
    PBRTO_EXPORT DirectionCone Union( const DirectionCone& a, const DirectionCone& b );

    // Frame Definition
    class alignas( Vector3f::Traits::AlignAs ) Frame
    {
    public:
        // Frame Public Members
        Vector3f::Simd x, y, z;

        // Frame Public Methods
        Frame( ) 
            : x( 1, 0, 0 ), y( 0, 1, 0 ), z( 0, 0, 1 )
        { }

        Frame( const Vector3f& x, const Vector3f& y, const Vector3f& z )
            : x( x ), y( y ), z( z )
        {
            NDCHECK_LT( Math::FastAbs( ScalarLengthSquared( x ) - 1 ), 1e-4 );
            NDCHECK_LT( Math::FastAbs( ScalarLengthSquared( y ) - 1 ), 1e-4 );
            NDCHECK_LT( Math::FastAbs( ScalarLengthSquared( z ) - 1 ), 1e-4 );
            NDCHECK_LT( Math::FastAbs( ScalarDot( x, y ) ), 1e-4 );
            NDCHECK_LT( Math::FastAbs( ScalarDot( y, z ) ), 1e-4 );
            NDCHECK_LT( Math::FastAbs( ScalarDot( z, x ) ), 1e-4 );
        }

        Frame( const Vector3f::Simd& x, const Vector3f::Simd& y, const Vector3f::Simd& z )
            : x( x ), y( y ), z( z )
        {

        }

        static Frame FromXZ( const Vector3f& x, const Vector3f& z )
        {
            return Frame( Vector3f::Simd(x), Cross( z, x ), Vector3f::Simd(z) );
        }
        static Frame FromXZ( const Vector3f::Simd& x, const Vector3f::Simd& z )
        {
            return Frame( x, Cross( z, x ), z );
        }

        static Frame FromXY( const Vector3f& x, const Vector3f& y )
        {
            return Frame( Vector3f::Simd(x), Vector3f::Simd(y), Cross( x, y ) );
        }
        static Frame FromXY( const Vector3f::Simd& x, const Vector3f::Simd& y )
        {
            return Frame( x, y, Cross( x, y ) );
        }

        static Frame FromZ( const Vector3f& z )
        {
            Vector3f x, y;
            CoordinateSystem( z, &x, &y );
            return Frame( x, y, z );
        }

        static Frame FromX( const Vector3f& x )
        {
            Vector3f y, z;
            CoordinateSystem( x, &y, &z );
            return Frame( x, y, z );
        }

        static Frame FromY( const Vector3f& y )
        {
            Vector3f x, z;
            CoordinateSystem( y, &z, &x );
            return Frame( x, y, z );
        }

        static Frame FromX( const Normal3f& x )
        {
            Vector3f y, z;
            CoordinateSystem( x, &y, &z );
            return Frame( Vector3f( x ), y, z );
        }

        static Frame FromX( const Normal3f::Simd& x )
        {
            return FromX( Normal3f( x ) );
        }

        static Frame FromY( const Normal3f& y )
        {
            Vector3f x, z;
            CoordinateSystem( y, &z, &x );
            return Frame( x, Vector3f( y ), z );
        }

        static Frame FromY( const Normal3f::Simd& y )
        {
            return FromY( Normal3f( y ) );
        }

        static Frame FromZ( const Normal3f& z )
        {
            return FromZ( Vector3f( z ) );
        }

        static Frame FromZ( const Vector3f::Simd& z )
        {
            return FromZ( Vector3f( z ) );
        }
        static Frame FromZ( const Point3f::Simd& z )
        {
            return FromZ( Vector3f( z ) );
        }
        static Frame FromZ( const Normal3f::Simd& z )
        {
            return FromZ( Normal3f( z ) );
        }

        Vector3f ToLocal( const Vector3f& v ) const
        {
            return Vector3f( ScalarDot( v, x ), ScalarDot( v, y ), ScalarDot( v, z ) );
        }
        Vector3f::Simd ToLocal( const Vector3f::Simd& v ) const
        {
            return Vector3f::Simd( ScalarDot( v, x ), ScalarDot( v, y ), ScalarDot( v, z ) );
        }

        Normal3f ToLocal( const Normal3f& n ) const
        {
            return Normal3f( ScalarDot( n, x ), ScalarDot( n, y ), ScalarDot( n, z ) );
        }
        Normal3f::Simd ToLocal( const Normal3f::Simd& n ) const
        {
            return Normal3f::Simd( ScalarDot( n, x ), ScalarDot( n, y ), ScalarDot( n, z ) );
        }

        Vector3f FromLocal( const Vector3f& v ) const
        {
            return v.x * x + v.y * y + v.z * z;
        }
        Vector3f::Simd FromLocal( const Vector3f::Simd& v ) const
        {
            return v.X() * x + v.Y() * y + v.Z() * z;
        }

        Normal3f FromLocal( const Normal3f& n ) const
        {
            return Normal3f( n.x * x + n.y * y + n.z * z );
        }

        Normal3f::Simd FromLocal( const Normal3f::Simd& n ) const
        {
            return n.X() * x + n.Y() * y + n.Z() * z;
        }

        std::string ToString( ) const
        {
            Vector3f X(x), Y(y), Z(z);
            return std::format( "[ Frame x: {} y: {} z: {} ]", X, Y, Z );
        }
        
    };

    
    

}


namespace std
{

    template<typename CharT>
    struct formatter<pbrto::Bounds2f, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const pbrto::Bounds2f& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}, {}]", value.pMin, value.pMax );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}, {}]", value.pMin, value.pMax );
            }
        }
    };

    template<typename CharT>
    struct formatter<pbrto::Bounds2i, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const pbrto::Bounds2i& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}, {}]", value.pMin, value.pMax );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}, {}]", value.pMin, value.pMax );
            }
        }
    };

    template<typename CharT>
    struct formatter<pbrto::Bounds3f, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const pbrto::Bounds3f& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}, {}]", value.pMin, value.pMax );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}, {}]", value.pMin, value.pMax );
            }
        }
    };

    template<typename CharT>
    struct formatter<pbrto::Bounds3i, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const pbrto::Bounds3i& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}, {}]", value.pMin, value.pMax );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}, {}]", value.pMin, value.pMax );
            }
        }
    };


    /*
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Math::Half, CharT>
    {
        formatter<float, CharT> floatFormatter;
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return floatFormatter.parse( ctx );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Half& half, FormatContext& ctx ) const
        {
            float v = static_cast< float >( half );
            return floatFormatter.format( v, ctx );
        }
    };
    */
}



#endif

