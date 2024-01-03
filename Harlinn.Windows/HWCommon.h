#pragma once
#ifndef __HWCOMMON_H__
#define __HWCOMMON_H__
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

#include <HWDef.h>

#pragma pack(push,8)

namespace Harlinn::Windows
{
    namespace Internal
    {
        template<class, template<class...> class>
        inline constexpr bool IsSpecializationOf = false;

        template<template<class...> class T, class... Args>
        inline constexpr bool IsSpecializationOf<T<Args...>, T> = true;

        template<typename Type, typename... TypeList>
        inline constexpr bool IsAnyOf_v = std::disjunction_v<std::is_same<Type, TypeList>...>;
    }

    template <typename T>
    concept WindowsPointType = Internal::IsAnyOf_v<T, POINT, POINTL, D2D_POINT_2F, D2D_POINT_2U>;

    template <typename T>
    concept WindowsSizeType = Internal::IsAnyOf_v<T, SIZE, D2D1_SIZE_F, D2D1_SIZE_U>;

    template <typename T>
    concept WindowsRectangleType = Internal::IsAnyOf_v<T, RECT, D2D1_RECT_F, D2D1_RECT_U>;

    template<WindowsPointType PT>
    class PointT;

    template<WindowsSizeType ST>
    class SizeT;

    namespace Internal
    {
        template<typename T>
        concept PointType = IsSpecializationOf<T, PointT>;
        template<typename T>
        concept SizeType = IsSpecializationOf<T, SizeT>;

        template<typename T>
        struct Traits{};

        template<> struct Traits<POINT> { using ValueType = int; };
        template<> struct Traits<POINTL> { using ValueType = int; };
        template<> struct Traits<D2D_POINT_2F> { using ValueType = float; };
        template<> struct Traits<D2D_POINT_2U> { using ValueType = UInt32; };
        template<> struct Traits<SIZE> { using ValueType = int; };
        template<> struct Traits<D2D1_SIZE_F> { using ValueType = float; };
        template<> struct Traits<D2D1_SIZE_U> { using ValueType = UInt32; };
        template<> struct Traits<RECT> 
        { 
            using ValueType = int;
            using PointType = PointT<POINT>;
            using SizeType = SizeT<SIZE>;
        };
        template<> struct Traits<D2D1_RECT_F> 
        { 
            using ValueType = float; 
            using PointType = PointT<D2D_POINT_2F>;
            using SizeType = SizeT<D2D1_SIZE_F>;
        };
        template<> struct Traits<D2D1_RECT_U> 
        { 
            using ValueType = UInt32; 
            using PointType = PointT<D2D_POINT_2U>;
            using SizeType = SizeT<D2D1_SIZE_U>;
        };

    }

    namespace Internal
    {
        template<typename T, typename U>
        concept StaticCastableTo = requires( T t )
        {
            { static_cast<U>( t ) };
        };
        template<typename T, typename U, typename V>
        concept StaticCastable2To = requires( T t, U u )
        {
            static_cast<V>( t );
            static_cast<V>( u );
        };

        template<typename A, typename B, typename C, typename D, typename V>
        concept StaticCastable4To = requires( A a, B b, C c, D d )
        {
            static_cast<V>( a );
            static_cast<V>( b );
            static_cast<V>( c );
            static_cast<V>( d );
        };


        template<typename T, typename U>
        concept ImplementsXAndYFunctions = requires( T t )
        {
            static_cast<U>( t.X( ) );
            static_cast<U>( t.Y( ) );
        };

        template<typename T, typename U>
        concept ImplementsWidthAndHeightFunctions = requires( T t )
        {
            static_cast<U>( t.Width( ) );
            static_cast<U>( t.Height( ) );
        };

        template<typename T, typename U>
        concept ImplementsLeftTopRightAndBottomFunctions = requires( T t )
        {
            static_cast<U>( t.Left( ) );
            static_cast<U>( t.Top( ) );
            static_cast<U>( t.Right( ) );
            static_cast<U>( t.Bottom( ) );
        };

        template<typename T, typename U>
        concept HasXAndY = requires( T t )
        {
            static_cast<U>( t.x );
            static_cast<U>( t.y );
        };
        static_assert( HasXAndY<POINT, int> );
        static_assert( HasXAndY<D2D_POINT_2F, float> );
        static_assert( HasXAndY<D2D_POINT_2U, UInt32> );


        template<typename T, typename U>
        concept HasCXAndCY = requires( T t )
        {
            static_cast<U>( t.cx );
            static_cast<U>( t.cy );
        };
        static_assert( HasCXAndCY<SIZE, int > );

        template<typename T, typename U>
        concept HasWidthAndHeight = requires( T t )
        {
            static_cast<U>( t.width );
            static_cast<U>( t.height );
        };
        static_assert( HasWidthAndHeight<D2D_SIZE_F, float > );
        static_assert( HasWidthAndHeight<D2D_SIZE_U, UInt32> );

        template<typename T, typename V>
        concept HasLeftTopRightAndBottom = requires( T t )
        {
            { static_cast<V>( t.left ) };
            { static_cast<V>( t.top ) };
            { static_cast<V>( t.right ) };
            { static_cast<V>( t.bottom ) };
        };


        static_assert( HasLeftTopRightAndBottom<RECT, int > );
        static_assert( HasLeftTopRightAndBottom<D2D_RECT_F, float > );
        static_assert( HasLeftTopRightAndBottom<D2D_RECT_U, UInt32 > );
    }

    

    /// <summary>
    /// Provides a unified api for point types
    /// </summary>
    template<WindowsPointType PT>
    class PointT
    {
    public:
        using value_type = typename Internal::Traits<PT>::ValueType;
        using PointType = PT;
    protected:
        value_type x_;
        value_type y_;
    public:
        constexpr PointT( ) noexcept
            : x_( 0 ), y_( 0 )
        {
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr PointT( U x, V y ) noexcept
            : x_( static_cast<value_type>( x ) ), y_( static_cast<value_type>( y ) )
        {
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr PointT( U value ) noexcept
            : x_( static_cast<value_type>( value ) ), y_( static_cast<value_type>( value ) )
        {
        }

        
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type> 
        constexpr explicit PointT( const U& value ) noexcept
            : x_( static_cast<value_type>( value.cx ) ), y_( static_cast<value_type>( value.cy ) )
        {
        }

        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr explicit PointT( const U& value ) noexcept
            : x_( static_cast<value_type>( value.width ) ), y_( static_cast<value_type>( value.height ) )
        {
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT( const U& value ) noexcept
            : x_( static_cast<value_type>( value.x ) ), y_( static_cast<value_type>( value.y ) )
        {
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U,value_type>
        constexpr PointT( const U& value ) noexcept
            : x_( static_cast<value_type>( value.X( ) ) ), y_( static_cast<value_type>( value.Y( ) ) )
        {
        }

        template<typename U>
            requires (Internal::ImplementsWidthAndHeightFunctions<U, value_type> &&
                Internal::ImplementsLeftTopRightAndBottomFunctions< U, value_type> == false )
        constexpr explicit PointT( const U& value ) noexcept
            : x_( static_cast<value_type>( value.Width( ) ) ), y_( static_cast<value_type>( value.Height( ) ) )
        {
        }

        constexpr const value_type& operator[]( size_t index ) const noexcept
        {
            return index == 0 ? x_ : y_;
        }
        constexpr value_type& operator[]( size_t index ) noexcept
        {
            return index == 0 ? x_ : y_;
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT& operator = ( const U& value ) noexcept
        {
            x_ = static_cast<value_type>( value.cx );
            y_ = static_cast<value_type>( value.cy );
            return *this;
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator = ( const U& value ) noexcept
        {
            x_ = static_cast<value_type>( value.x );
            y_ = static_cast<value_type>( value.y );
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator = ( const U& value ) noexcept
        {
            x_ = static_cast<value_type>( value.X( ) );
            y_ = static_cast<value_type>( value.Y( ) );
            return *this;
        }


        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr PointT& operator = ( const U& value ) noexcept
        {
            x_ = static_cast<value_type>( value.width );
            y_ = static_cast<value_type>( value.height );
            return *this;
        }

        template<typename U>
            requires (Internal::ImplementsWidthAndHeightFunctions<U, value_type> &&
                Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false )
        constexpr PointT& operator = ( const U& value ) noexcept
        {
            x_ = static_cast<value_type>( value.Width( ) );
            y_ = static_cast<value_type>( value.Height( ) );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return x_ != static_cast<value_type>( 0 ) || y_ != static_cast<value_type>( 0 );
        }

        constexpr bool operator == ( const PointT& other ) const noexcept
        {
            return x_ == other.x_ &&
                y_ == other.y_;
        }
        constexpr bool operator != ( const PointT& other ) const noexcept
        {
            return x_ != other.x_ ||
                y_ != other.y_;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U,value_type>
        constexpr PointT& operator += ( const U& value ) noexcept
        {
            x_ += static_cast<value_type>( value );
            y_ += static_cast<value_type>( value );
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator += ( const U& value ) noexcept
        {
            x_ += static_cast<value_type>( value.X() );
            y_ += static_cast<value_type>( value.Y() );
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr PointT& operator += ( const U& value ) noexcept
        {
            x_ += static_cast<value_type>( value.Width() );
            y_ += static_cast<value_type>( value.Height() );
            return *this;
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator += ( const U& value ) noexcept
        {
            x_ += static_cast<value_type>( value.x );
            y_ += static_cast<value_type>( value.y );
            return *this;
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT& operator += ( const U& value ) noexcept
        {
            x_ += static_cast<value_type>( value.cx );
            y_ += static_cast<value_type>( value.cy );
            return *this;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U,value_type>
        constexpr PointT& operator -= ( const U& value ) noexcept
        {
            x_ -= static_cast<value_type>( value );
            y_ -= static_cast<value_type>( value );
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator -= ( const U& value ) noexcept
        {
            x_ -= static_cast<value_type>( value.X() );
            y_ -= static_cast<value_type>( value.Y() );
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr PointT& operator -= ( const U& value ) noexcept
        {
            x_ -= static_cast<value_type>( value.Width() );
            y_ -= static_cast<value_type>( value.Height() );
            return *this;
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator -= ( const U& value ) noexcept
        {
            x_ -= static_cast<value_type>( value.x );
            y_ -= static_cast<value_type>( value.y );
            return *this;
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT& operator -= ( const U& value ) noexcept
        {
            x_ -= static_cast<value_type>( value.cx );
            y_ -= static_cast<value_type>( value.cy );
            return *this;
        }

        template<typename U>
            requires Internal::StaticCastableTo<U,value_type>
        constexpr PointT& operator *= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                x_ = static_cast<value_type>( static_cast<U>( x_ ) * value );
                y_ = static_cast<value_type>( static_cast<U>( y_ ) * value );
            }
            else
            {
                x_ *= static_cast<value_type>( value );
                y_ *= static_cast<value_type>( value );
            }
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator *= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                x_ = static_cast<value_type>( static_cast<typename U::value_type>( x_ ) * value.X( ) );
                y_ = static_cast<value_type>( static_cast<typename U::value_type>( y_ ) * value.Y( ) );
            }
            else
            {
                x_ *= static_cast<value_type>( value.X( ) );
                y_ *= static_cast<value_type>( value.Y( ) );
            }
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr PointT& operator *= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                x_ = static_cast<value_type>( static_cast<typename U::value_type>( x_ ) * value.Width( ) );
                y_ = static_cast<value_type>( static_cast<typename U::value_type>( y_ ) * value.Height( ) );
            }
            else
            {
                x_ *= static_cast<value_type>( value.Width( ) );
                y_ *= static_cast<value_type>( value.Height( ) );
            }
            return *this;
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator *= ( const U& value ) noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                x_ = static_cast<value_type>( static_cast<ArgumentValueType>( x_ ) * value.x );
                y_ = static_cast<value_type>( static_cast<ArgumentValueType>( y_ ) * value.y );
            }
            else
            {
                x_ *= static_cast<value_type>( value.x );
                y_ *= static_cast<value_type>( value.y );
            }
            return *this;
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT& operator *= ( const U& value ) noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                x_ = static_cast<value_type>( static_cast<ArgumentValueType>( x_ ) * value.cx );
                y_ = static_cast<value_type>( static_cast<ArgumentValueType>( y_ ) * value.cy );
            }
            else
            {
                x_ *= static_cast<value_type>( value.cx );
                y_ *= static_cast<value_type>( value.cy );
            }
            return *this;
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr PointT& operator /= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                x_ = static_cast<value_type>( static_cast<U>( x_ ) / value );
                y_ = static_cast<value_type>( static_cast<U>( y_ ) / value );
            }
            else
            {
                x_ /= static_cast<value_type>( value );
                y_ /= static_cast<value_type>( value );
            }
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator /= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                x_ = static_cast<value_type>( static_cast<typename U::value_type>( x_ ) / value.X( ) );
                y_ = static_cast<value_type>( static_cast<typename U::value_type>( y_ ) / value.Y( ) );
            }
            else
            {
                x_ /= static_cast<value_type>( value.X( ) );
                y_ /= static_cast<value_type>( value.Y( ) );
            }
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr PointT& operator /= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                x_ = static_cast<value_type>( static_cast<typename U::value_type>( x_ ) / value.Width( ) );
                y_ = static_cast<value_type>( static_cast<typename U::value_type>( y_ ) / value.Height( ) );
            }
            else
            {
                x_ /= static_cast<value_type>( value.Width( ) );
                y_ /= static_cast<value_type>( value.Height( ) );
            }
            return *this;
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT& operator /= ( const U& value ) noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                x_ = static_cast<value_type>( static_cast<ArgumentValueType>( x_ ) / value.x );
                y_ = static_cast<value_type>( static_cast<ArgumentValueType>( y_ ) / value.y );
            }
            else
            {
                x_ /= static_cast<value_type>( value.x );
                y_ /= static_cast<value_type>( value.y );
            }
            return *this;
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT& operator /= ( const U& value ) noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                x_ = static_cast<value_type>( static_cast<ArgumentValueType>( x_ ) / value.cx );
                y_ = static_cast<value_type>( static_cast<ArgumentValueType>( y_ ) / value.cy );
            }
            else
            {
                x_ /= static_cast<value_type>( value.cx );
                y_ /= static_cast<value_type>( value.cy );
            }
            return *this;
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr PointT operator + ( const U& value ) const noexcept
        {
            return PointT( x_ + static_cast<value_type>( value ), y_ + static_cast<value_type>( value ) );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT operator + ( const U& value ) const noexcept
        {
            return PointT( x_ + static_cast<value_type>( value.X( ) ), y_ + static_cast<value_type>( value.Y( ) ) );
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr PointT operator + ( const U& value ) const noexcept
        {
            return PointT( x_ + static_cast<value_type>( value.Width( ) ), y_ + static_cast<value_type>( value.Height( ) ) );
        }

        template<typename U>
            requires (Internal::HasXAndY<U, value_type> && (Internal::ImplementsXAndYFunctions<U, value_type> == false))
        constexpr PointT operator + ( const U& value ) const noexcept
        {
            return PointT( x_ + static_cast<value_type>( value.x ), y_ + static_cast<value_type>( value.y ) );
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT operator + ( const U& value ) const noexcept
        {
            return PointT( x_ + static_cast<value_type>( value.cx ), y_ + static_cast<value_type>( value.cy ) );
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr PointT operator - ( const U& value ) const noexcept
        {
            return PointT( x_ - static_cast<value_type>( value ), y_ - static_cast<value_type>( value ) );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT operator - ( const U& value ) const noexcept
        {
            return PointT( x_ - static_cast<value_type>( value.X( ) ), y_ - static_cast<value_type>( value.Y( ) ) );
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr PointT operator - ( const U& value ) const noexcept
        {
            return PointT( x_ - static_cast<value_type>( value.Width( ) ), y_ - static_cast<value_type>( value.Height( ) ) );
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT operator - ( const U& value ) const noexcept
        {
            return PointT( x_ - static_cast<value_type>( value.x ), y_ - static_cast<value_type>( value.y ) );
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT operator - ( const U& value ) const noexcept
        {
            return PointT( x_ - static_cast<value_type>( value.cx ), y_ - static_cast<value_type>( value.cy ) );
        }



        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr PointT operator * ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                return PointT( static_cast<value_type>( static_cast<U>( x_ ) * value ),
                    static_cast<value_type>( static_cast<U>( y_ ) * value ) );
            }
            else
            {
                return PointT( x_ * static_cast<value_type>( value ), y_ * static_cast<value_type>( value ) );
            }
        }


        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT operator * ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                return PointT( static_cast<value_type>( static_cast<typename U::value_type>( x_ ) * value.X( ) ),
                    static_cast<value_type>( static_cast<typename U::value_type>( y_ ) * value.Y( ) ) );
            }
            else
            {
                return PointT( x_ * static_cast<value_type>( value.X( ) ), y_ * static_cast<value_type>( value.Y( ) ) );
            }
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr PointT operator * ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                return PointT( static_cast<value_type>( static_cast<typename U::value_type>( x_ ) * value.Width( ) ),
                    static_cast<value_type>( static_cast<typename U::value_type>( y_ ) * value.Height( ) ) );
            }
            else
            {
                return PointT( x_ * static_cast<value_type>( value.Width( ) ), y_ * static_cast<value_type>( value.Height( ) ) );
            }
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT operator * ( const U& value ) const noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                return PointT( static_cast<value_type>( static_cast<ArgumentValueType>( x_ ) * value.Width( ) ),
                    static_cast<value_type>( static_cast<ArgumentValueType>( y_ ) * value.Height( ) ) );
            }
            else
            {
                return PointT( x_ * static_cast<value_type>( value.Width( ) ), y_ * static_cast<value_type>( value.Height( ) ) );
            }
        }


        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT operator * ( const U& value ) const noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                return PointT( static_cast<value_type>( static_cast<ArgumentValueType>( x_ ) * value.Width( ) ),
                    static_cast<value_type>( static_cast<ArgumentValueType>( y_ ) * value.Height( ) ) );
            }
            else
            {
                return PointT( x_ * static_cast<value_type>( value.Width( ) ), y_ * static_cast<value_type>( value.Height( ) ) );
            }
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr PointT operator / ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                return PointT( static_cast<value_type>( static_cast<U>( x_ ) / value ),
                    static_cast<value_type>( static_cast<U>( y_ ) / value ) );
            }
            else
            {
                return PointT( x_ / static_cast<value_type>( value ), y_ / static_cast<value_type>( value ) );
            }
        }


        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT operator / ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                return PointT( static_cast<value_type>( static_cast<typename U::value_type>( x_ ) / value.X( ) ),
                    static_cast<value_type>( static_cast<typename U::value_type>( y_ ) / value.Y( ) ) );
            }
            else
            {
                return PointT( x_ / static_cast<value_type>( value.X( ) ), y_ / static_cast<value_type>( value.Y( ) ) );
            }
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr PointT operator / ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                return PointT( static_cast<value_type>( static_cast<typename U::value_type>( x_ ) / value.Width( ) ),
                    static_cast<value_type>( static_cast<typename U::value_type>( y_ ) / value.Height( ) ) );
            }
            else
            {
                return PointT( x_ / static_cast<value_type>( value.Width( ) ), y_ / static_cast<value_type>( value.Height( ) ) );
            }
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT operator / ( const U& value ) const noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                return PointT( static_cast<value_type>( static_cast<ArgumentValueType>( x_ ) / value.Width( ) ),
                    static_cast<value_type>( static_cast<ArgumentValueType>( y_ ) / value.Height( ) ) );
            }
            else
            {
                return PointT( x_ / static_cast<value_type>( value.Width( ) ), y_ / static_cast<value_type>( value.Height( ) ) );
            }
        }


        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr PointT operator / ( const U& value ) const noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                return PointT( static_cast<value_type>( static_cast<ArgumentValueType>( x_ ) / value.Width( ) ),
                    static_cast<value_type>( static_cast<ArgumentValueType>( y_ ) / value.Height( ) ) );
            }
            else
            {
                return PointT( x_ / static_cast<value_type>( value.Width( ) ), y_ / static_cast<value_type>( value.Height( ) ) );
            }
        }


        constexpr value_type X( ) const noexcept
        {
            return x_;
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetX( U value ) noexcept
        {
            x_ = static_cast<value_type>(value);
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddToX( U value ) noexcept
        {
            x_ += static_cast<value_type>(value);
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractFromX( U value ) noexcept
        {
            x_ -= static_cast<value_type>(value);
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void MinX( U value ) noexcept
        {
            x_ = std::min( x_, static_cast<value_type>(value) );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void MaxX( U value ) noexcept
        {
            x_ = std::max( x_, static_cast<value_type>(value) );
        }

        constexpr void SwapX( PointT& other ) noexcept
        {
            std::swap( x_, other.x_ );
        }

        constexpr void SwapX( value_type& value ) noexcept
        {
            std::swap( x_, value );
        }

        constexpr value_type Y( ) const noexcept
        {
            return y_;
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetY( U value ) noexcept
        {
            y_ = static_cast<value_type>( value );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddToY( U value ) noexcept
        {
            y_ += static_cast<value_type>( value );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractFromY( U value ) noexcept
        {
            y_ -= static_cast<value_type>( value );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void MinY( U value ) noexcept
        {
            y_ = std::min( y_, static_cast<value_type>( value ) );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void MaxY( U value ) noexcept
        {
            y_ = std::max( y_, static_cast<value_type>( value ) );
        }

        constexpr void SwapY( PointT& other ) noexcept
        {
            std::swap( y_, other.y_ );
        }


        constexpr void SwapY( value_type& value ) noexcept
        {
            std::swap( y_, value );
        }

        constexpr void swap( PointT& other ) noexcept
        {
            std::swap( x_, other.x_ );
            std::swap( y_, other.y_ );
        }


        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V ,value_type>
        constexpr void Assign( U x, V y ) noexcept
        {
            x_ = static_cast<value_type>( x );
            y_ = static_cast<value_type>( y );
        }


        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void Add( U x, V y ) noexcept
        {
            x_ += static_cast<value_type>( x );
            y_ += static_cast<value_type>( y );
        }


        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void AssignMax( U x, V y ) noexcept
        {
            x_ = std::max( x_,  static_cast<value_type>( x ) );
            y_ = std::max( y_, static_cast<value_type>( y ) );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void AssignMax( const U& point ) noexcept
        {
            AssignMax( point.X(), point.Y() );
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void AssignMax( const U& point ) noexcept
        {
            AssignMax( point.x, point.y );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr PointT Max( U x, V y ) const noexcept
        {
            return { std::max( x_,  static_cast<value_type>( x ) ), std::max( y_, static_cast<value_type>( y ) ) };
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT Max( const U& point ) const noexcept
        {
            return Max( point.X(), point.Y() );
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr PointT Max( const U& point ) const noexcept
        {
            return Max( point.x, point.y );
        }


        constexpr PointT max( const PointT& other ) const noexcept
        {
            return Max( other.X( ), other.Y( ) );
        }


        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void AssignMin( U x, V y ) noexcept
        {
            x_ = std::min( x_,  static_cast<value_type>( x ) );
            y_ = std::min( y_, static_cast<value_type>( y ) );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void AssignMin( const U& point ) noexcept
        {
            AssignMin( point.X(), point.Y() );
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void AssignMin( const U& point ) noexcept
        {
            AssignMin( point.x, point.y );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr PointT Min( U x, V y ) const noexcept
        {
            return { std::min( x_,  static_cast<value_type>( x ) ), std::min( y_, static_cast<value_type>( y ) ) };
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT Min( const U& point ) const noexcept
        {
            return Min( point.X(), point.Y() );
        }

        constexpr PointT min( const PointT& other ) const noexcept
        {
            return Min( other.X( ), other.Y( ) );
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr PointT Min( const U& point ) const noexcept
        {
            return Min( point.x, point.y );
        }



        template<typename X1, typename Y1, typename X2, typename Y2>
            requires Internal::StaticCastable4To<X1, Y1, X2, Y2, value_type>
        constexpr PointT Clamp( X1 minX, Y1 minY, X2 maxX, Y2 maxY ) const noexcept
        {
            return { ( x_ < static_cast<value_type>( minX ) ) ? static_cast<value_type>( minX ) : ( x_ > static_cast<value_type>( maxX ) ) ? static_cast<value_type>( maxX ) : x_, 
                ( y_ < static_cast<value_type>( minY ) ) ? static_cast<value_type>( minY ) : ( y_ > static_cast<value_type>( maxY ) ) ? static_cast<value_type>( maxY ) : y_ };
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr PointT Clamp( const U& min, const U& max )
        {
            return Clamp( min.X( ), min.Y( ), max.X( ), max.Y( ) );
        }


        value_type Dot( const PointT& other ) const noexcept
        {
            return ( x_ * other.x_ ) + ( y_ * other.y_ );
        }

        constexpr value_type LengthSqr( ) const noexcept
        {
            return ( x_ * x_ ) + ( y_ * y_ );
        }



        constexpr operator PointType& ( ) noexcept
        {
            return *( (PointType*)&x_ );
        }
        constexpr operator const PointType& ( ) const noexcept
        {
            return *( (PointType*)&x_ );
        }

    };
}

namespace std
{
    template<typename T>
    inline constexpr Harlinn::Windows::PointT<T> min( const Harlinn::Windows::PointT<T>& first, const Harlinn::Windows::PointT<T>& second ) noexcept
    {
        return 
        { 
            first.X( ) < second.X( ) ? first.X( ) : second.X( ),
            first.Y( ) < second.Y( ) ? first.Y( ) : second.Y( )
        };
    }

    template<typename T>
    inline constexpr Harlinn::Windows::PointT<T> max( const Harlinn::Windows::PointT<T>& first, const Harlinn::Windows::PointT<T>& second ) noexcept
    {
        return 
        { 
            first.X( ) >= second.X( ) ? first.X( ) : second.X( ),
            first.Y( ) >= second.Y( ) ? first.Y( ) : second.Y( )
        };
    }

    template<typename T>
    inline constexpr Harlinn::Windows::PointT<T> clamp( const Harlinn::Windows::PointT<T>& point, const Harlinn::Windows::PointT<T>& min, const Harlinn::Windows::PointT<T>& max ) noexcept
    {
        return
        {
            clamp( point.X( ), min.X( ),max.X( ) ),
            clamp( point.Y( ), min.Y( ),max.Y( ) )
        };
    }
}

namespace Harlinn::Windows
{

    /// <summary>
    /// Provides a unified api for size types
    /// </summary>
    template<WindowsSizeType ST>
    class SizeT
    {
    public:
        using value_type = typename Internal::Traits<ST>::ValueType;
        using SizeType = ST;
    protected:
        value_type width_;
        value_type height_;
    public:
        constexpr SizeT( ) noexcept
            : width_( 0 ), height_( 0 )
        {
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr SizeT( U width, V height ) noexcept
            : width_( static_cast<value_type>( width ) ), height_( static_cast<value_type>( height ) )
        {
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT( U value ) noexcept
            : width_( static_cast<value_type>( value ) ), height_( static_cast<value_type>( value ) )
        {
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT( const U& value ) noexcept
            : width_( static_cast<value_type>( value.cx ) ), height_( static_cast<value_type>( value.cy ) )
        {
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr explicit SizeT( const U& value ) noexcept
            : width_( static_cast<value_type>( value.x ) ), height_( static_cast<value_type>( value.y ) )
        {
        }

        template<typename U>
        requires (Internal::ImplementsXAndYFunctions<U,value_type> &&
                    Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false )
        constexpr explicit SizeT( const U& value ) noexcept
            : width_( static_cast<value_type>( value.X( ) ) ), height_( static_cast<value_type>( value.Y( ) ) )
        {
        }


        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr SizeT( const U& value ) noexcept
            : width_( static_cast<value_type>( value.width ) ), height_( static_cast<value_type>( value.height ) )
        {
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT( const U& value ) noexcept
            : width_( static_cast<value_type>( value.Width( ) ) ), height_( static_cast<value_type>( value.Height( ) ) )
        {
        }

        constexpr const value_type& operator[]( size_t index ) const noexcept
        {
            return index == 0 ? width_ : height_;
        }
        constexpr value_type& operator[]( size_t index ) noexcept
        {
            return index == 0 ? width_ : height_;
        }


        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT& operator = ( const U& value ) noexcept
        {
            width_ = static_cast<value_type>( value.cx );
            height_ = static_cast<value_type>( value.cy );
            return *this;
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator = ( const U& value ) noexcept
        {
            width_ = static_cast<value_type>( value.x );
            height_ = static_cast<value_type>( value.y );
            return *this;
        }

        template<typename U>
            requires (Internal::ImplementsXAndYFunctions<U, value_type> && 
                Internal::ImplementsLeftTopRightAndBottomFunctions<U,value_type> == false )
        constexpr SizeT& operator = ( const U& value ) noexcept
        {
            width_ = static_cast<value_type>( value.X( ) );
            height_ = static_cast<value_type>( value.Y( ) );
            return *this;
        }

        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr SizeT& operator = ( const U& value ) noexcept
        {
            width_ = static_cast<value_type>( value.width );
            height_ = static_cast<value_type>( value.height );
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT& operator = ( const U& value ) noexcept
        {
            width_ = static_cast<value_type>( value.Width( ) );
            height_ = static_cast<value_type>( value.Height( ) );
            return *this;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return width_ != static_cast<value_type>( 0 ) || height_ != static_cast<value_type>( 0 );
        }

        constexpr bool operator == ( const SizeT& other ) const noexcept
        {
            return width_ == other.width_ &&
                height_ == other.height_;
        }
        constexpr bool operator != ( const SizeT& other ) const noexcept
        {
            return width_ != other.width_ ||
                height_ != other.height_;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT& operator += ( const U& value ) noexcept
        {
            width_ += static_cast<value_type>( value );
            height_ += static_cast<value_type>( value );
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator += ( const U& value ) noexcept
        {
            width_ += static_cast<value_type>( value.X() );
            height_ += static_cast<value_type>( value.Y() );
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT& operator += ( const U& value ) noexcept
        {
            width_ += static_cast<value_type>( value.Width() );
            height_ += static_cast<value_type>( value.Height() );
            return *this;
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator += ( const U& value ) noexcept
        {
            width_ += static_cast<value_type>( value.x );
            height_ += static_cast<value_type>( value.y );
            return *this;
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT& operator += ( const U& value ) noexcept
        {
            width_ += static_cast<value_type>( value.cx );
            height_ += static_cast<value_type>( value.cy );
            return *this;
        }



        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT& operator -= ( const U& value ) noexcept
        {
            width_ -= static_cast<value_type>( value );
            height_ -= static_cast<value_type>( value );
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator -= ( const U& value ) noexcept
        {
            width_ -= static_cast<value_type>( value.X() );
            height_ -= static_cast<value_type>( value.Y() );
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT& operator -= ( const U& value ) noexcept
        {
            width_ -= static_cast<value_type>( value.Width() );
            height_ -= static_cast<value_type>( value.Height() );
            return *this;
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator -= ( const U& value ) noexcept
        {
            width_ -= static_cast<value_type>( value.x );
            height_ -= static_cast<value_type>( value.y );
            return *this;
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT& operator -= ( const U& value ) noexcept
        {
            width_ -= static_cast<value_type>( value.cx );
            height_ -= static_cast<value_type>( value.cy );
            return *this;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT& operator *= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                width_ = static_cast<value_type>( static_cast<U>( width_ ) * value );
                height_ = static_cast<value_type>( static_cast<U>( height_ ) * value );
            }
            else
            {
                width_ *= static_cast<value_type>( value );
                height_ *= static_cast<value_type>( value );
            }
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator *= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                width_ = static_cast<value_type>( static_cast<typename U::value_type>( width_ ) * value.X( ) );
                height_ = static_cast<value_type>( static_cast<typename U::value_type>( height_ ) * value.Y( ) );
            }
            else
            {
                width_ *= static_cast<value_type>( value.X( ) );
                height_ *= static_cast<value_type>( value.Y( ) );
            }
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT& operator *= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                width_ = static_cast<value_type>( static_cast<typename U::value_type>( width_ ) * value.Width( ) );
                height_ = static_cast<value_type>( static_cast<typename U::value_type>( height_ ) * value.Height( ) );
            }
            else
            {
                width_ *= static_cast<value_type>( value.Width( ) );
                height_ *= static_cast<value_type>( value.Height( ) );
            }
            return *this;
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator *= ( const U& value ) noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                width_ = static_cast<value_type>( static_cast<ArgumentValueType>( width_ ) * value.x );
                height_ = static_cast<value_type>( static_cast<ArgumentValueType>( height_ ) * value.y );
            }
            else
            {
                width_ *= static_cast<value_type>( value.x );
                height_ *= static_cast<value_type>( value.y );
            }
            return *this;
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT& operator *= ( const U& value ) noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                width_ = static_cast<value_type>( static_cast<ArgumentValueType>( width_ ) * value.cx );
                height_ = static_cast<value_type>( static_cast<ArgumentValueType>( height_ ) * value.cy );
            }
            else
            {
                width_ *= static_cast<value_type>( value.cx );
                height_ *= static_cast<value_type>( value.cy );
            }
            return *this;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT& operator /= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                width_ = static_cast<value_type>( static_cast<U>( width_ ) / value );
                height_ = static_cast<value_type>( static_cast<U>( height_ ) / value );
            }
            else
            {
                width_ /= static_cast<value_type>( value );
                height_ /= static_cast<value_type>( value );
            }
            return *this;
        }


        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator /= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                width_ = static_cast<value_type>( static_cast<typename U::value_type>( width_ ) / value.X( ) );
                height_ = static_cast<value_type>( static_cast<typename U::value_type>( height_ ) / value.Y( ) );
            }
            else
            {
                width_ /= static_cast<value_type>( value.X( ) );
                height_ /= static_cast<value_type>( value.Y( ) );
            }
            return *this;
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT& operator /= ( const U& value ) noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                width_ = static_cast<value_type>( static_cast<typename U::value_type>( width_ ) / value.Width( ) );
                height_ = static_cast<value_type>( static_cast<typename U::value_type>( height_ ) / value.Height( ) );
            }
            else
            {
                width_ /= static_cast<value_type>( value.Width( ) );
                height_ /= static_cast<value_type>( value.Height( ) );
            }
            return *this;
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT& operator /= ( const U& value ) noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                width_ = static_cast<value_type>( static_cast<ArgumentValueType>( width_ ) / value.x );
                height_ = static_cast<value_type>( static_cast<ArgumentValueType>( height_ ) / value.y );
            }
            else
            {
                width_ /= static_cast<value_type>( value.x );
                height_ /= static_cast<value_type>( value.y );
            }
            return *this;
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT& operator /= ( const U& value ) noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                width_ = static_cast<value_type>( static_cast<ArgumentValueType>( width_ ) / value.cx );
                height_ = static_cast<value_type>( static_cast<ArgumentValueType>( height_ ) / value.cy );
            }
            else
            {
                width_ /= static_cast<value_type>( value.cx );
                height_ /= static_cast<value_type>( value.cy );
            }
            return *this;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT operator + ( const U& value ) const noexcept
        {
            return SizeT( width_ + static_cast<value_type>( value ), height_ + static_cast<value_type>( value ) );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT operator + ( const U& value ) const noexcept
        {
            return SizeT( width_ + static_cast<value_type>( value.X( ) ), height_ + static_cast<value_type>( value.Y( ) ) );
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT operator + ( const U& value ) const noexcept
        {
            return SizeT( width_ + static_cast<value_type>( value.Width( ) ), height_ + static_cast<value_type>( value.Height( ) ) );
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT operator + ( const U& value ) const noexcept
        {
            return SizeT( width_ + static_cast<value_type>( value.x ), height_ + static_cast<value_type>( value.y ) );
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT operator + ( const U& value ) const noexcept
        {
            return SizeT( width_ + static_cast<value_type>( value.cx ), height_ + static_cast<value_type>( value.cy ) );
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT operator - ( const U& value ) const noexcept
        {
            return SizeT( width_ - static_cast<value_type>( value ), height_ - static_cast<value_type>( value ) );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT operator - ( const U& value ) const noexcept
        {
            return SizeT( width_ - static_cast<value_type>( value.X( ) ), height_ - static_cast<value_type>( value.Y( ) ) );
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT operator - ( const U& value ) const noexcept
        {
            return SizeT( width_ - static_cast<value_type>( value.Width( ) ), height_ - static_cast<value_type>( value.Height( ) ) );
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT operator - ( const U& value ) const noexcept
        {
            return SizeT( width_ - static_cast<value_type>( value.x ), height_ - static_cast<value_type>( value.y ) );
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT operator - ( const U& value ) const noexcept
        {
            return SizeT( width_ - static_cast<value_type>( value.cx ), height_ - static_cast<value_type>( value.cy ) );
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT operator * ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                return SizeT( static_cast<value_type>( static_cast<U>( width_ ) * value ),
                    static_cast<value_type>( static_cast<U>( height_ ) * value ) );
            }
            else
            {
                return SizeT( width_ * static_cast<value_type>( value ), height_ * static_cast<value_type>( value ) );
            }
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT operator * ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                return SizeT( static_cast<value_type>( static_cast<typename U::value_type>( width_ ) * value.X( ) ),
                    static_cast<value_type>( static_cast<typename U::value_type>( height_ ) * value.Y( ) ) );
            }
            else
            {
                return SizeT( width_ * static_cast<value_type>( value.X( ) ), height_ * static_cast<value_type>( value.Y( ) ) );
            }
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT operator * ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                return SizeT( static_cast<value_type>( static_cast<typename U::value_type>( width_ ) * value.Width( ) ),
                    static_cast<value_type>( static_cast<typename U::value_type>( height_ ) * value.Height( ) ) );
            }
            else
            {
                return SizeT( width_ * static_cast<value_type>( value.Width( ) ), height_ * static_cast<value_type>( value.Height( ) ) );
            }
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT operator * ( const U& value ) const noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                return SizeT( static_cast<value_type>( static_cast<ArgumentValueType>( width_ ) * value.Width( ) ),
                    static_cast<value_type>( static_cast<ArgumentValueType>( height_ ) * value.Height( ) ) );
            }
            else
            {
                return SizeT( width_ * static_cast<value_type>( value.Width( ) ), height_ * static_cast<value_type>( value.Height( ) ) );
            }
        }


        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT operator * ( const U& value ) const noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                return SizeT( static_cast<value_type>( static_cast<ArgumentValueType>( width_ ) * value.Width( ) ),
                    static_cast<value_type>( static_cast<ArgumentValueType>( height_ ) * value.Height( ) ) );
            }
            else
            {
                return SizeT( width_ * static_cast<value_type>( value.Width( ) ), height_ * static_cast<value_type>( value.Height( ) ) );
            }
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr SizeT operator / ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                return SizeT( static_cast<value_type>( static_cast<U>( width_ ) / value ),
                    static_cast<value_type>( static_cast<U>( height_ ) / value ) );
            }
            else
            {
                return SizeT( width_ / static_cast<value_type>( value ), height_ / static_cast<value_type>( value ) );
            }
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT operator / ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                return SizeT( static_cast<value_type>( static_cast<typename U::value_type>( width_ ) / value.X( ) ),
                    static_cast<value_type>( static_cast<typename U::value_type>( height_ ) / value.Y( ) ) );
            }
            else
            {
                return SizeT( width_ / static_cast<value_type>( value.X( ) ), height_ / static_cast<value_type>( value.Y( ) ) );
            }
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT operator / ( const U& value ) const noexcept
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<typename U::value_type> )
            {
                return SizeT( static_cast<value_type>( static_cast<typename U::value_type>( width_ ) / value.Width( ) ),
                    static_cast<value_type>( static_cast<typename U::value_type>( height_ ) / value.Height( ) ) );
            }
            else
            {
                return SizeT( width_ / static_cast<value_type>( value.Width( ) ), height_ / static_cast<value_type>( value.Height( ) ) );
            }
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type> && !Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr SizeT operator / ( const U& value ) const noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                return SizeT( static_cast<value_type>( static_cast<ArgumentValueType>( width_ ) / value.Width( ) ),
                    static_cast<value_type>( static_cast<ArgumentValueType>( height_ ) / value.Height( ) ) );
            }
            else
            {
                return SizeT( width_ / static_cast<value_type>( value.Width( ) ), height_ / static_cast<value_type>( value.Height( ) ) );
            }
        }


        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT operator / ( const U& value ) const noexcept
        {
            using ArgumentValueType = std::remove_cvref_t<decltype( value.x )>;
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<ArgumentValueType> )
            {
                return SizeT( static_cast<value_type>( static_cast<ArgumentValueType>( width_ ) / value.Width( ) ),
                    static_cast<value_type>( static_cast<ArgumentValueType>( height_ ) / value.Height( ) ) );
            }
            else
            {
                return SizeT( width_ / static_cast<value_type>( value.Width( ) ), height_ / static_cast<value_type>( value.Height( ) ) );
            }
        }


        constexpr value_type Width( ) const noexcept
        {
            return width_;
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetWidth( U width ) noexcept
        {
            width_ = static_cast<value_type>( width );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddToWidth( U width ) noexcept
        {
            width_ += static_cast<value_type>( width );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractFromWidth( U width ) noexcept
        {
            width_ -= static_cast<value_type>( width );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void MaxWidth( U width ) noexcept
        {
            width_ = std::max( width_,static_cast<value_type>( width ));
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void MinWidth( U width ) noexcept
        {
            width_ = std::min( width_,static_cast<value_type>( width ));
        }

        constexpr void SwapWidth( SizeT& other ) noexcept
        {
            std::swap( width_, other.width_ );
        }


        constexpr void SwapWidth( value_type& value ) noexcept
        {
            std::swap( width_, value );
        }


        constexpr value_type Height( ) const noexcept
        {
            return height_;
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetHeight( U height ) noexcept
        {
            height_ = static_cast<value_type>( height );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddToHeight( U height ) noexcept
        {
            height_ += static_cast<value_type>( height );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractFromHeight( U height ) noexcept
        {
            height_ -= static_cast<value_type>( height );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void MaxHeight( U height ) noexcept
        {
            height_ = std::max( height_, static_cast<value_type>( height ) );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void MinHeight( U height ) noexcept
        {
            height_ = std::min( height_, static_cast<value_type>( height ) );
        }

        constexpr void SwapHeight( SizeT& other ) noexcept
        {
            std::swap( height_, other.height_ );
        }


        constexpr void SwapHeight( value_type& value ) noexcept
        {
            std::swap( height_, value );
        }

        constexpr void swap( SizeT& other ) noexcept
        {
            std::swap( width_, other.width_ );
            std::swap( height_, other.height_ );
        }


        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void Assign( U width, V height ) noexcept
        {
            width_ = static_cast<value_type>( width );
            height_ = static_cast<value_type>( height );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void Add( U width, V height ) noexcept
        {
            width_ += static_cast<value_type>( width );
            height_ += static_cast<value_type>( height );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void AssignMax( U width, V height ) noexcept
        {
            width_ = std::max( width_,  static_cast<value_type>( width ) );
            height_ = std::max( height_, static_cast<value_type>( height ) );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr SizeT Max( U width, V height ) const noexcept
        {
            return { std::max( width_,  static_cast<value_type>( width ) ), std::max( height_, static_cast<value_type>( height ) ) };
        }


        constexpr SizeT max( const SizeT& point ) const noexcept
        {
            return Max( point.Width( ), point.Height( ) );
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT Max( const U& point ) const noexcept
        {
            return Max( point.Width(), point.Height() );
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT Max( const U& point ) const noexcept
        {
            return Max( point.cx, point.cy );
        }

        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr SizeT Max( const U& point ) const noexcept
        {
            return Max( point.width, point.height );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void AssignMin( U width, V height ) noexcept
        {
            width_ = std::min( width_,  static_cast<value_type>( width ) );
            height_ = std::min( height_, static_cast<value_type>( height ) );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr SizeT Min( U width, V height ) const noexcept
        {
            return { std::min( width_,  static_cast<value_type>( width ) ), std::min( height_, static_cast<value_type>( height ) ) };
        }

        constexpr SizeT min( const SizeT& point ) const noexcept
        {
            return Min( point.Width( ), point.Height( ) );
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT Min( const U& point ) const noexcept
        {
            return Min( point.Width(), point.Height() );
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr SizeT Min( const U& point ) const noexcept
        {
            return Min( point.cx, point.cy );
        }

        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr SizeT Min( const U& point ) const noexcept
        {
            return Min( point.width, point.height );
        }
        
        template<typename W1, typename H1, typename W2, typename H2>
            requires Internal::StaticCastable4To<W1, H1, W2, H2, value_type>
        constexpr SizeT Clamp( W1 minWidth, H1 minHeight, W2 maxWidth, H2 maxHeight ) const noexcept
        {
            return { ( width_ < static_cast<value_type>( minWidth ) ) ? static_cast<value_type>( minWidth ) : ( width_ > static_cast<value_type>( maxHeight ) ) ? static_cast<value_type>( maxHeight ) : width_,
                ( height_ < static_cast<value_type>( minHeight ) ) ? static_cast<value_type>( minHeight ) : ( height_ > static_cast<value_type>( maxHeight ) ) ? static_cast<value_type>( maxHeight ) : height_ };
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr SizeT Clamp( const U& min, const U& max )
        {
            return Clamp( min.Width( ), min.Height( ), max.Width( ), max.Height( ) );
        }


        constexpr operator SizeType& ( ) noexcept
        {
            return *( (SizeType*)&width_ );
        }
        constexpr operator const SizeType& ( ) const noexcept
        {
            return *( (SizeType*)&width_ );
        }
    };

}

namespace std
{
    template<typename T>
    inline constexpr Harlinn::Windows::SizeT<T> min( const Harlinn::Windows::SizeT<T>& first, const Harlinn::Windows::SizeT<T>& second ) noexcept
    {
        return
        {
            first.Width( ) < second.Width( ) ? first.Width( ) : second.Width( ),
            first.Height( ) < second.Height( ) ? first.Height( ) : second.Height( )
        };
    }

    template<typename T>
    inline constexpr Harlinn::Windows::SizeT<T> max( const Harlinn::Windows::SizeT<T>& first, const Harlinn::Windows::SizeT<T>& second ) noexcept
    {
        return
        {
            first.Width( ) >= second.Width( ) ? first.Width( ) : second.Width( ),
            first.Height( ) >= second.Height( ) ? first.Height( ) : second.Height( )
        };
    }

    template<typename T>
    inline constexpr Harlinn::Windows::SizeT<T> clamp( const Harlinn::Windows::SizeT<T>& size, const Harlinn::Windows::SizeT<T>& min, const Harlinn::Windows::SizeT<T>& max ) noexcept
    {
        return
        {
            clamp( size.Width( ), min.Width( ),max.Width( ) ),
            clamp( size.Height( ), min.Height( ),max.Height( ) )
        };
    }
}

namespace Harlinn::Windows
{

    /// <summary>
    /// Provides a unified api for rectangle types
    /// </summary>
    template<WindowsRectangleType RT>
    class RectangleT
    {
    public:
        using value_type = typename Internal::Traits<RT>::ValueType;
        using RectangleType = RT;
        using PointType = typename Internal::Traits<RT>::PointType;
        using SizeType = typename Internal::Traits<RT>::SizeType;
    protected:
        value_type left_;
        value_type top_;
        value_type right_;
        value_type bottom_;
    public:
        constexpr RectangleT( ) noexcept
            : left_( 0 ), top_( 0 ), right_( 0 ), bottom_( 0 )
        {
        }

        template<typename U>
            requires Internal::HasLeftTopRightAndBottom<U,value_type>
        constexpr RectangleT( const U& other ) noexcept
            : left_( static_cast<value_type>( other.left ) ),
              top_( static_cast<value_type>( other.top ) ),
              right_( static_cast<value_type>( other.right ) ),
              bottom_( static_cast<value_type>( other.bottom ) )
        {
        }

        template<typename U>
            requires Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type>
        constexpr RectangleT( const U& other ) noexcept
            : left_( static_cast<value_type>( other.Left() ) ),
              top_( static_cast<value_type>( other.Top() ) ),
              right_( static_cast<value_type>( other.Right() ) ),
              bottom_( static_cast<value_type>( other.Bottom() ) )
        {
        }

        template<typename A,typename B, typename C, typename D>
            requires Internal::StaticCastable4To<A,B,C,D,value_type>
        constexpr RectangleT( A left, B top, C right, D bottom ) noexcept
            : left_( static_cast<value_type>( left ) ), 
              top_( static_cast<value_type>( top ) ), 
              right_( static_cast<value_type>( right ) ), 
              bottom_( static_cast<value_type>( bottom ) )
        {
        }

        template<typename A,typename B, typename C, typename D>
            requires Internal::StaticCastable4To<A,B,C,D,value_type>
        constexpr RectangleT( A left, B top, C right, D bottom, bool normalized ) noexcept
            : left_( static_cast<value_type>( left ) ), 
              top_( static_cast<value_type>( top ) ), 
              right_( static_cast<value_type>( right ) ), 
              bottom_( static_cast<value_type>( bottom ) )
        {
            if ( normalized )
            {
                Normalize( );
            }
        }



        template<typename P1, typename P2>
            requires ( Internal::ImplementsXAndYFunctions<P1,value_type> &&
                Internal::ImplementsXAndYFunctions<P2, value_type> )
        constexpr RectangleT( const P1& leftTop, const P2& rightBottom ) noexcept
            : left_( static_cast<value_type>( leftTop.X( ) ) ),
              top_( static_cast<value_type>( leftTop.Y( ) ) ),
              right_( static_cast<value_type>( rightBottom.X( ) ) ),
              bottom_( static_cast<value_type>( rightBottom.Y( ) ) ) 
        {
        }

        template<typename P1, typename P2>
            requires ( Internal::ImplementsXAndYFunctions<P1,value_type> &&
                Internal::ImplementsXAndYFunctions<P2, value_type> )
        constexpr RectangleT( const P1& leftTop, const P2& rightBottom, bool normalized ) noexcept
            : left_( static_cast<value_type>( leftTop.X( ) ) ),
              top_( static_cast<value_type>( leftTop.Y( ) ) ),
              right_( static_cast<value_type>( rightBottom.X( ) ) ),
              bottom_( static_cast<value_type>( rightBottom.Y( ) ) ) 
        {
            if ( normalized )
            {
                Normalize( );
            }
        }

        template<typename P1, typename P2>
            requires ( Internal::ImplementsXAndYFunctions<P1,value_type> &&
                Internal::HasXAndY<P2, value_type> )
        constexpr RectangleT( const P1& leftTop, const P2& rightBottom ) noexcept
            : left_( static_cast<value_type>( leftTop.X( ) ) ),
              top_( static_cast<value_type>( leftTop.Y( ) ) ),
              right_( static_cast<value_type>( rightBottom.x ) ),
              bottom_( static_cast<value_type>( rightBottom.y ) ) 
        {
        }

        template<typename P1, typename P2>
            requires ( Internal::ImplementsXAndYFunctions<P1,value_type> &&
                Internal::HasXAndY<P2, value_type> )
        constexpr RectangleT( const P1& leftTop, const P2& rightBottom, bool normalized ) noexcept
            : left_( static_cast<value_type>( leftTop.X( ) ) ),
              top_( static_cast<value_type>( leftTop.Y( ) ) ),
              right_( static_cast<value_type>( rightBottom.x ) ),
              bottom_( static_cast<value_type>( rightBottom.y ) ) 
        {
            if ( normalized )
            {
                Normalize( );
            }
        }

        template<typename P1, typename P2>
            requires ( Internal::HasXAndY<P1,value_type> &&
                Internal::ImplementsXAndYFunctions<P2, value_type> )
        constexpr RectangleT( const P1& leftTop, const P2& rightBottom ) noexcept
            : left_( static_cast<value_type>( leftTop.x ) ),
              top_( static_cast<value_type>( leftTop.y ) ),
              right_( static_cast<value_type>( rightBottom.X( ) ) ),
              bottom_( static_cast<value_type>( rightBottom.Y( ) ) ) 
        {
        }

        template<typename P1, typename P2>
            requires ( Internal::HasXAndY<P1,value_type> &&
                Internal::ImplementsXAndYFunctions<P2, value_type> )
        constexpr RectangleT( const P1& leftTop, const P2& rightBottom, bool normalized ) noexcept
            : left_( static_cast<value_type>( leftTop.x ) ),
              top_( static_cast<value_type>( leftTop.y ) ),
              right_( static_cast<value_type>( rightBottom.X( ) ) ),
              bottom_( static_cast<value_type>( rightBottom.Y( ) ) ) 
        {
            if ( normalized )
            {
                Normalize( );
            }
        }


        template<typename P1, typename P2>
            requires ( Internal::HasXAndY<P1,value_type> &&
                Internal::HasXAndY<P2, value_type> )
        constexpr RectangleT( const P1& leftTop, const P2& rightBottom ) noexcept
            : left_( static_cast<value_type>( leftTop.x ) ),
              top_( static_cast<value_type>( leftTop.y ) ),
              right_( static_cast<value_type>( rightBottom.x ) ),
              bottom_( static_cast<value_type>( rightBottom.y ) ) 
        {
        }

        template<typename P1, typename P2>
            requires ( Internal::HasXAndY<P1,value_type> &&
                Internal::HasXAndY<P2, value_type> )
        constexpr RectangleT( const P1& leftTop, const P2& rightBottom, bool normalized ) noexcept
            : left_( static_cast<value_type>( leftTop.x ) ),
              top_( static_cast<value_type>( leftTop.y ) ),
              right_( static_cast<value_type>( rightBottom.x ) ),
              bottom_( static_cast<value_type>( rightBottom.y ) ) 
        {
            if ( normalized )
            {
                Normalize( );
            }
        }

        template<typename P, typename S>
            requires ( Internal::ImplementsXAndYFunctions<P,value_type> &&
                Internal::ImplementsWidthAndHeightFunctions<S, value_type> )
        constexpr RectangleT( const P& position, const S& size ) noexcept
            : left_( static_cast<value_type>( position.X( ) ) ), 
              top_( static_cast<value_type>( position.Y( ) ) ), 
              right_( static_cast<value_type>( position.X( ) ) + static_cast<value_type>( size.Width( ) ) ),
              bottom_( static_cast<value_type>( position.Y( ) ) + static_cast<value_type>( size.Height( ) ) )
        {
        }

        template<typename P, typename S>
            requires ( Internal::ImplementsXAndYFunctions<P,value_type> &&
                Internal::ImplementsWidthAndHeightFunctions<S, value_type> )
        constexpr RectangleT( const P& position, const S& size, bool normalized ) noexcept
            : left_( static_cast<value_type>( position.X( ) ) ), 
              top_( static_cast<value_type>( position.Y( ) ) ), 
              right_( static_cast<value_type>( position.X( ) ) + static_cast<value_type>( size.Width( ) ) ),
              bottom_( static_cast<value_type>( position.Y( ) ) + static_cast<value_type>( size.Height( ) ) )
        {
            if ( normalized )
            {
                Normalize( );
            }
        }

        template<typename P, typename S>
            requires ( Internal::ImplementsXAndYFunctions<P, value_type>&&
                Internal::HasWidthAndHeight<S, value_type> )
        constexpr RectangleT( const P& position, const S& size ) noexcept
            : left_( static_cast<value_type>( position.X( ) ) ),
              top_( static_cast<value_type>( position.Y( ) ) ),
              right_( static_cast<value_type>( position.X( ) ) + static_cast<value_type>( size.width ) ),
              bottom_( static_cast<value_type>( position.Y( ) ) + static_cast<value_type>( size.height ) )
        {
        }

        template<typename P, typename S>
            requires ( Internal::ImplementsXAndYFunctions<P, value_type>&&
                Internal::HasWidthAndHeight<S, value_type> )
        constexpr RectangleT( const P& position, const S& size, bool normalized ) noexcept
            : left_( static_cast<value_type>( position.X( ) ) ),
              top_( static_cast<value_type>( position.Y( ) ) ),
              right_( static_cast<value_type>( position.X( ) ) + static_cast<value_type>( size.width ) ),
              bottom_( static_cast<value_type>( position.Y( ) ) + static_cast<value_type>( size.height ) )
        {
            if ( normalized )
            {
                Normalize( );
            }
        }

        template<typename P, typename S>
            requires ( Internal::ImplementsXAndYFunctions<P, value_type>&&
                Internal::HasCXAndCY<S, value_type> )
        constexpr RectangleT( const P& position, const S& size ) noexcept
            : left_( static_cast<value_type>( position.X( ) ) ),
              top_( static_cast<value_type>( position.Y( ) ) ),
              right_( static_cast<value_type>( position.X( ) ) + static_cast<value_type>( size.cx ) ),
              bottom_( static_cast<value_type>( position.Y( ) ) + static_cast<value_type>( size.cy ) )
        {
        }

        template<typename P, typename S>
            requires ( Internal::ImplementsXAndYFunctions<P, value_type>&&
                Internal::HasCXAndCY<S, value_type> )
        constexpr RectangleT( const P& position, const S& size, bool normalized ) noexcept
            : left_( static_cast<value_type>( position.X( ) ) ),
              top_( static_cast<value_type>( position.Y( ) ) ),
              right_( static_cast<value_type>( position.X( ) ) + static_cast<value_type>( size.cx ) ),
              bottom_( static_cast<value_type>( position.Y( ) ) + static_cast<value_type>( size.cy ) )
        {
            if ( normalized )
            {
                Normalize( );
            }
        }

        template<typename P, typename S>
            requires ( Internal::HasXAndY<P, value_type> &&
                Internal::ImplementsWidthAndHeightFunctions<S, value_type> )
        constexpr RectangleT( const P& position, const S& size ) noexcept
            : left_( static_cast<value_type>( position.x ) ),
              top_( static_cast<value_type>( position.y ) ),
              right_( static_cast<value_type>( position.x ) + static_cast<value_type>( size.Width( ) ) ),
              bottom_( static_cast<value_type>( position.y ) + static_cast<value_type>( size.Height( ) ) )
        {
        }

        template<typename P, typename S>
            requires ( Internal::HasXAndY<P, value_type> &&
                Internal::ImplementsWidthAndHeightFunctions<S, value_type> )
        constexpr RectangleT( const P& position, const S& size, bool normalized ) noexcept
            : left_( static_cast<value_type>( position.x ) ),
              top_( static_cast<value_type>( position.y ) ),
              right_( static_cast<value_type>( position.x ) + static_cast<value_type>( size.Width( ) ) ),
              bottom_( static_cast<value_type>( position.y ) + static_cast<value_type>( size.Height( ) ) )
        {
            if ( normalized )
            {
                Normalize( );
            }
        }

        template<typename P, typename S>
            requires ( Internal::HasXAndY<P, value_type>&&
                Internal::HasWidthAndHeight<S, value_type> )
        constexpr RectangleT( const P& position, const S& size ) noexcept
            : left_( static_cast<value_type>( position.x ) ),
              top_( static_cast<value_type>( position.y ) ),
              right_( static_cast<value_type>( position.x ) + static_cast<value_type>( size.width ) ),
              bottom_( static_cast<value_type>( position.y ) + static_cast<value_type>( size.height ) )
        {
        }

        template<typename P, typename S>
            requires ( Internal::HasXAndY<P, value_type>&&
                Internal::HasWidthAndHeight<S, value_type> )
        constexpr RectangleT( const P& position, const S& size, bool normalized ) noexcept
            : left_( static_cast<value_type>( position.x ) ),
              top_( static_cast<value_type>( position.y ) ),
              right_( static_cast<value_type>( position.x ) + static_cast<value_type>( size.width ) ),
              bottom_( static_cast<value_type>( position.y ) + static_cast<value_type>( size.height ) )
        {
            if ( normalized )
            {
                Normalize( );
            }
        }

        template<typename P, typename S>
            requires ( Internal::HasXAndY<P, value_type>&&
                Internal::HasCXAndCY<S, value_type> )
        constexpr RectangleT( const P& position, const S& size ) noexcept
            : left_( static_cast<value_type>( position.x ) ),
              top_( static_cast<value_type>( position.y ) ),
              right_( static_cast<value_type>( position.x ) + static_cast<value_type>( size.cx ) ),
              bottom_( static_cast<value_type>( position.y ) + static_cast<value_type>( size.cy ) )
        {
        }

        template<typename P, typename S>
            requires ( Internal::HasXAndY<P, value_type>&&
                Internal::HasCXAndCY<S, value_type> )
        constexpr RectangleT( const P& position, const S& size, bool normalized ) noexcept
            : left_( static_cast<value_type>( position.x ) ),
              top_( static_cast<value_type>( position.y ) ),
              right_( static_cast<value_type>( position.x ) + static_cast<value_type>( size.cx ) ),
              bottom_( static_cast<value_type>( position.y ) + static_cast<value_type>( size.cy ) )
        {
            if ( normalized )
            {
                Normalize( );
            }
        }


        template<typename U>
            requires (Internal::ImplementsWidthAndHeightFunctions<U, value_type> &&
                Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false )
        constexpr RectangleT( const U& size ) noexcept
            : left_( 0 ), top_( 0 ), 
              right_( static_cast<value_type>( size.Width( ) ) ), 
              bottom_( static_cast<value_type>( size.Height( ) ) )
        {
        }

        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr RectangleT( const U& size ) noexcept
            : left_( 0 ), top_( 0 ),
              right_( static_cast<value_type>( size.width ) ),
              bottom_( static_cast<value_type>( size.height ) )
        {
        }

        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr RectangleT( const U& size ) noexcept
            : left_( 0 ), top_( 0 ),
              right_( static_cast<value_type>( size.cx ) ),
              bottom_( static_cast<value_type>( size.cy ) )
        {
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        explicit RectangleT( U size ) noexcept
            : left_( 0 ), top_( 0 ), 
              right_( static_cast<value_type>( size ) ), 
              bottom_( static_cast<value_type>( size ) )
        {
        }


        template<typename U>
            requires Internal::HasLeftTopRightAndBottom<U,value_type>
        constexpr RectangleT& operator = ( const U& other ) noexcept
        {
            left_ = static_cast<value_type>( other.left );
            top_ = static_cast<value_type>( other.top );
            right_ = static_cast<value_type>( other.right );
            bottom_ = static_cast<value_type>( other.bottom );
            return *this;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="A">The type of the left parameter</typeparam>
        /// <typeparam name="B">The type of the top parameter</typeparam>
        /// <typeparam name="C">The type of the right parameter</typeparam>
        /// <typeparam name="D">The type of the bottom parameter</typeparam>
        /// <param name="left"></param>
        /// <param name="top"></param>
        /// <param name="right"></param>
        /// <param name="bottom"></param>
        template<typename A, typename B, typename C, typename D>
            requires Internal::StaticCastable4To<A, B, C, D, value_type>
        constexpr void NormalizedAssign( A left, B top, C right, D bottom )
        { 
            auto leftValue = static_cast<value_type>( left );
            auto topValue = static_cast<value_type>( top );
            auto rightValue = static_cast<value_type>( right );
            auto bottomValue = static_cast<value_type>( bottom );
            if ( leftValue <= rightValue ) [[likely]]
            {
                left_ = leftValue;
                right_ = rightValue;
            }
            else
            {
                left_ = rightValue;
                right_ = leftValue;
            }
            if ( topValue <= bottomValue ) [[likely]]
            {
                top_ = topValue;
                bottom_ = bottomValue;
            }
            else
            {
                top_ = bottomValue;
                bottom_ = topValue;
            }
        }

        template<typename U, typename V>
        requires Internal::ImplementsXAndYFunctions<U, value_type> && 
            ( Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false ) &&
            Internal::ImplementsXAndYFunctions<V, value_type> &&
            ( Internal::ImplementsLeftTopRightAndBottomFunctions<V, value_type> == false )
        constexpr void NormalizedAssign( const U& leftTop, const V& rightBottom )
        {
            NormalizedAssign( leftTop.X( ), leftTop.Y( ), rightBottom.X( ), rightBottom.Y( ) );
        }

        template<typename U, typename V>
        requires Internal::ImplementsXAndYFunctions<U, value_type> &&
            ( Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false ) &&
            Internal::ImplementsWidthAndHeightFunctions<V, value_type> &&
            ( Internal::ImplementsLeftTopRightAndBottomFunctions<V, value_type> == false )
        constexpr void NormalizedAssign( const U& leftTop, const V& size )
        {
            NormalizedAssign( leftTop.X( ), leftTop.Y( ), leftTop.X( ) + size.Width(), leftTop.Y( ) + size.Height() );
        }


        template<typename A, typename B, typename C, typename D>
            requires Internal::StaticCastable4To<A, B, C, D, value_type>
        constexpr void Assign( A left, B top, C right, D bottom )
        { 
            left_ = static_cast<value_type>( left );
            top_ = static_cast<value_type>( top );
            right_ = static_cast<value_type>( right );
            bottom_ = static_cast<value_type>( bottom );
        }

        template<typename U, typename V>
        requires Internal::ImplementsXAndYFunctions<U, value_type> && 
            ( Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false ) &&
            Internal::ImplementsXAndYFunctions<V, value_type> &&
            ( Internal::ImplementsLeftTopRightAndBottomFunctions<V, value_type> == false )
        constexpr void Assign( const U& leftTop, const V& rightBottom )
        {
            Assign( leftTop.X( ), leftTop.Y( ), rightBottom.X( ), rightBottom.Y( ) );
        }

        template<typename U, typename V>
        requires Internal::ImplementsXAndYFunctions<U, value_type> &&
            ( Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false ) &&
            Internal::ImplementsWidthAndHeightFunctions<V, value_type> &&
            ( Internal::ImplementsLeftTopRightAndBottomFunctions<V, value_type> == false )
        constexpr void Assign( const U& leftTop, const V& size )
        {
            Assign( leftTop.X( ), leftTop.Y( ), leftTop.X( ) + size.Width(), leftTop.Y( ) + size.Height() );
        }



        template<typename X, typename Y>
            requires Internal::StaticCastable2To<X, Y, value_type>
        void Add( X x, Y y ) 
        { 
            auto xValue = static_cast<value_type>( x );
            auto yValue = static_cast<value_type>( y );
            if ( left_ > xValue )
            {
                left_ = xValue;
            }
            if ( top_ > yValue )
            {
                top_ = yValue;
            }
            if ( right_ < xValue )
            {
                right_ = xValue;
            }
            if ( bottom_ < yValue )
            {
                bottom_ = yValue;
            }
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type> && ( Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false )
        void Add( const U& point )
        {
            Add( point.X(), point.Y() );
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        void Add( const U& point )
        {
            Add( point.x, point.y );
        }


        template<typename A, typename B, typename C, typename D>
            requires Internal::StaticCastable4To<A, B, C, D, value_type>
        void Add( A left, B top, C right, D bottom )
        { 
            auto leftValue = static_cast<value_type>( left );
            auto topValue = static_cast<value_type>( top );
            auto rightValue = static_cast<value_type>( right );
            auto bottomValue = static_cast<value_type>( bottom );
            if ( left_ > leftValue )
            {
                left_ = leftValue;
            }
            if ( top_ > topValue )
            {
                top_ = topValue;
            }
            if ( right_ < rightValue )
            {
                right_ = rightValue;
            }
            if ( bottom_ < bottomValue )
            {
                bottom_ = bottomValue;
            }
        }

        template<typename U>
            requires Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type>
        void Add( const U& rectangle )
        {
            Add( rectangle.Left(), rectangle.Top(), rectangle.Right(), rectangle.Bottom() );
        }

        template<typename U>
            requires Internal::HasLeftTopRightAndBottom<U, value_type>
        void Add( const U& rectangle )
        {
            Add( rectangle.left, rectangle.top, rectangle.right, rectangle.bottom );
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return ( left_ != 0 ) || ( top_ != 0 ) || ( right_ != 0 ) || ( bottom_ != 0 );
        }



        constexpr bool operator == ( const RectangleT& other ) const noexcept
        {
            return left_ == other.left_ &&
                top_ == other.top_ &&
                right_ == other.right_ &&
                bottom_ == other.bottom_;
        }
        constexpr bool operator != ( const RectangleT& other ) const noexcept
        {
            return left_ != other.left_ ||
                top_ != other.top_ ||
                right_ != other.right_ ||
                bottom_ != other.bottom_;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr RectangleT& operator += ( U value )
        {
            left_ += static_cast<value_type>( value );
            top_ += static_cast<value_type>( value );
            right_ += static_cast<value_type>( value );
            bottom_ += static_cast<value_type>( value );
            return *this;
        }


        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr RectangleT& operator += ( const U& value )
        {
            left_ += static_cast<value_type>( value.X( ) );
            top_ += static_cast<value_type>( value.Y( ) );
            right_ += static_cast<value_type>( value.X( ) );
            bottom_ += static_cast<value_type>( value.Y( ) );
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr RectangleT& operator += ( const U& value )
        {
            right_ += static_cast<value_type>( value.Width( ) );
            bottom_ += static_cast<value_type>( value.Height( ) );
            return *this;
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr RectangleT& operator -= ( U value )
        {
            left_ -= static_cast<value_type>( value );
            top_ -= static_cast<value_type>( value );
            right_ -= static_cast<value_type>( value );
            bottom_ -= static_cast<value_type>( value );
            return *this;
        }


        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr RectangleT& operator -= ( const U& value )
        {
            left_ -= static_cast<value_type>( value.X( ) );
            top_ -= static_cast<value_type>( value.Y( ) );
            right_ -= static_cast<value_type>( value.X( ) );
            bottom_ -= static_cast<value_type>( value.Y( ) );
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr RectangleT& operator -= ( const U& value )
        {
            right_ -= static_cast<value_type>( value.Width( ) );
            bottom_ -= static_cast<value_type>( value.Height( ) );
            return *this;
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr RectangleT& operator *= ( U value )
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                left_ = static_cast<value_type>( static_cast<U>( left_ ) * value );
                top_ = static_cast<value_type>( static_cast<U>( top_ ) * value );
                right_ = static_cast<value_type>( static_cast<U>( right_ ) * value );
                bottom_ = static_cast<value_type>( static_cast<U>( bottom_ ) * value );
            }
            else
            {
                left_ *= static_cast<value_type>( value );
                top_ *= static_cast<value_type>( value );
                right_ *= static_cast<value_type>( value );
                bottom_ *= static_cast<value_type>( value );
            }
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr RectangleT& operator *= ( const U& value )
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                left_ = static_cast<value_type>( static_cast<U>( left_ ) * value.X( ) );
                top_ = static_cast<value_type>( static_cast<U>( top_ ) * value.Y( ) );
                right_ = static_cast<value_type>( static_cast<U>( right_ ) * value.X( ) );
                bottom_ = static_cast<value_type>( static_cast<U>( bottom_ ) * value.Y( ) );
            }
            else
            {
                left_ *= static_cast<value_type>( value.X( ) );
                top_ *= static_cast<value_type>( value.Y( ) );
                right_ *= static_cast<value_type>( value.X( ) );
                bottom_ *= static_cast<value_type>( value.Y( ) );
            }
            return *this;
        }



        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr RectangleT& operator /= ( U value )
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                left_ = static_cast<value_type>( static_cast<U>( left_ ) / value );
                top_ = static_cast<value_type>( static_cast<U>( top_ ) / value );
                right_ = static_cast<value_type>( static_cast<U>( right_ ) / value );
                bottom_ = static_cast<value_type>( static_cast<U>( bottom_ ) / value );
            }
            else
            {
                left_ /= static_cast<value_type>( value );
                top_ /= static_cast<value_type>( value );
                right_ /= static_cast<value_type>( value );
                bottom_ /= static_cast<value_type>( value );
            }
            return *this;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr RectangleT& operator /= ( const U& value )
        {
            if constexpr ( std::is_integral_v<value_type> && std::is_floating_point_v<U> )
            {
                left_ = static_cast<value_type>( static_cast<U>( left_ ) / value.X( ) );
                top_ = static_cast<value_type>( static_cast<U>( top_ ) / value.Y( ) );
                right_ = static_cast<value_type>( static_cast<U>( right_ ) / value.X( ) );
                bottom_ = static_cast<value_type>( static_cast<U>( bottom_ ) / value.Y( ) );
            }
            else
            {
                left_ /= static_cast<value_type>( value.X( ) );
                top_ /= static_cast<value_type>( value.Y( ) );
                right_ /= static_cast<value_type>( value.X( ) );
                bottom_ /= static_cast<value_type>( value.Y( ) );
            }
            return *this;
        }



        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr RectangleT operator + ( U value ) const
        {
            RectangleT copy( *this );
            copy += value;
            return copy;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr RectangleT operator + ( const U& value ) const
        {
            RectangleT copy( *this );
            copy += value;
            return copy;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr RectangleT operator - ( U value ) const
        {
            RectangleT copy( *this );
            copy -= value;
            return copy;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr RectangleT operator - ( U value ) const
        {
            RectangleT copy( *this );
            copy -= value;
            return copy;
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr RectangleT operator * ( U value ) const
        {
            RectangleT copy( *this );
            copy *= value;
            return copy;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr RectangleT operator * ( U value ) const
        {
            RectangleT copy( *this );
            copy *= value;
            return copy;
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr RectangleT operator / ( U value ) const
        {
            RectangleT copy( *this );
            copy /= value;
            return copy;
        }
        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr RectangleT operator / ( U value ) const
        {
            RectangleT copy( *this );
            copy /= value;
            return copy;
        }


        constexpr value_type X( ) const noexcept
        {
            return left_;
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetX( U value ) noexcept
        {
            left_ = static_cast<value_type>( value );
        }
        constexpr value_type Y( ) const noexcept
        {
            return top_;
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetY( U value ) noexcept
        {
            top_ = static_cast<value_type>( value );
        }

        value_type Width( ) const noexcept
        {
            if constexpr ( std::is_unsigned_v<value_type> )
            {
                return right_ > left_ ? right_ - left_ : left_ - right_;
            }
            else
            {
                return std::abs( right_ - left_ );
            }
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetWidth( U width ) noexcept
        {
            right_ = left_ + static_cast<value_type>( width );
        }
        value_type Height( ) const noexcept
        {
            if constexpr ( std::is_unsigned_v<value_type> )
            {
                return bottom_ > top_ ? bottom_ - top_ : top_ - bottom_;
            }
            else
            {
                return std::abs( bottom_ - top_ );
            }
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetHeight( U value ) noexcept
        {
            bottom_ = top_ + static_cast<value_type>( value );
        }


        constexpr value_type Left( ) const noexcept
        {
            return left_;
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetLeft( U value ) noexcept
        {
            left_ = static_cast<value_type>( value );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddToLeft( U value ) noexcept
        {
            left_ += static_cast<value_type>( value );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractFromLeft( U value ) noexcept
        {
            left_ -= static_cast<value_type>( value );
        }

        constexpr void SwapLeft( RectangleT& other ) noexcept
        {
            std::swap( left_, other.left_ );
        }

        constexpr value_type Top( ) const noexcept
        {
            return top_;
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetTop( U value ) noexcept
        {
            top_ = static_cast<value_type>( value );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddToTop( U value ) noexcept
        {
            top_ += static_cast<value_type>( value );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractFromTop( U value ) noexcept
        {
            top_ -= static_cast<value_type>( value );
        }

        constexpr void SwapTop( RectangleT& other ) noexcept
        {
            std::swap( top_, other.top_ );
        }


        constexpr value_type Right( ) const noexcept
        {
            return right_;
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetRight( U value ) noexcept
        {
            right_ = static_cast<value_type>( value );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddToRight( U value ) noexcept
        {
            right_ += static_cast<value_type>( value );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractFromRight( U value ) noexcept
        {
            right_ -= static_cast<value_type>( value );
        }

        constexpr void SwapRight( RectangleT& other ) noexcept
        {
            std::swap( right_, other.right_ );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U,V, value_type>
        constexpr void SetLeftAndRight( U left, V right ) noexcept
        {
            left_ = static_cast<value_type>( left );
            right_ = static_cast<value_type>( right );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U,value_type>
        constexpr void SetLeftAndRight( U value ) noexcept
        {
            left_ = static_cast<value_type>( value );
            right_ = static_cast<value_type>( value );
        }

        constexpr void SwapLeftAndRight( ) noexcept
        {
            std::swap( left_, right_ );
        }


        constexpr value_type Bottom( ) const noexcept
        {
            return bottom_;
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SetBottom( U value ) noexcept
        {
            bottom_ = static_cast<value_type>( value );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddToBottom( U value ) noexcept
        {
            bottom_ += static_cast<value_type>( value );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractFromBottom( U value ) noexcept
        {
            bottom_ -= static_cast<value_type>( value );
        }

        constexpr void SwapBottom( RectangleT& other ) noexcept
        {
            std::swap( bottom_, other.bottom_ );
        }


        template<typename U, typename V>
            requires Internal::StaticCastable2To<U,V, value_type>
        constexpr void SetTopAndBottom( U top, V bottom ) noexcept
        {
            top_ = static_cast<value_type>( top );
            bottom_ = static_cast<value_type>( bottom );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U,value_type>
        constexpr void SetTopAndBottom( U value ) noexcept
        {
            top_ = static_cast<value_type>( value );
            bottom_ = static_cast<value_type>( value );
        }

        constexpr void SwapTopAndBottom( ) noexcept
        {
            std::swap( top_, bottom_ );
        }

        constexpr PointType Position( ) const noexcept
        {
            return PointType( left_, top_ );
        }
        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V ,value_type>
        constexpr void SetPosition( U x, V y ) noexcept
        {
            value_type width = right_ - left_;
            value_type height = bottom_ - top_;
            left_ = static_cast<value_type>( x );
            top_ = static_cast<value_type>( y );
            right_ = left_ + width;
            bottom_ = top_ + height;
        }


        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void SetPosition( const U& pt ) noexcept
        {
            SetPosition( pt.X( ), pt.Y( ) );
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void SetPosition( const U& pt ) noexcept
        {
            SetPosition( pt.x, pt.y );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V ,value_type>
        constexpr void Translate( U dx, V dy ) noexcept
        {
            auto dxValue = static_cast<value_type>( dx );
            auto dyValue = static_cast<value_type>( dy );
            left_ += dxValue;
            top_ += dyValue;
            right_ += dxValue;
            bottom_ += dyValue;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void Translate( const U& pt ) noexcept
        {
            Translate( pt.X( ), pt.Y( ) );
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr void Translate( const U& pt ) noexcept
        {
            Translate( pt.Width( ), pt.Height( ) );
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void Translate( const U& pt ) noexcept
        {
            Translate( pt.x, pt.y );
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        constexpr void Translate( const U& pt ) noexcept
        {
            Translate( pt.cx, pt.cy );
        }

        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        void TranslateX( U dx ) 
        { 
            left_ += static_cast<value_type>( dx );
            right_ += static_cast<value_type>( dx );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        void AddToLeftAndRight( U dx ) 
        { 
            left_ += static_cast<value_type>( dx );
            right_ += static_cast<value_type>( dx );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        void SubtractFromLeftAndRight( U dx ) 
        { 
            left_ -= static_cast<value_type>( dx );
            right_ -= static_cast<value_type>( dx );
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        void TranslateY( U dy ) 
        { 
            top_ += static_cast<value_type>( dy );
            bottom_ += static_cast<value_type>( dy );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        void AddToTopAndBottom( U dy ) 
        { 
            top_ += static_cast<value_type>( dy );
            bottom_ += static_cast<value_type>( dy );
        }
        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        void SubtractFromTopAndBottom( U dy ) 
        { 
            top_ -= static_cast<value_type>( dy );
            bottom_ -= static_cast<value_type>( dy );
        }



        constexpr PointType LeftTop( ) const noexcept
        {
            return PointType( left_, top_ );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void SetLeftTop( U left, V top ) noexcept
        {
            left_ = static_cast<value_type>( left );
            top_ = static_cast<value_type>( top );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void SetLeftTop( const U& pt ) noexcept
        {
            SetLeftTop( pt.X( ), pt.Y( ) );
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void SetLeftTop( const U& pt ) noexcept
        {
            SetLeftTop( pt.x, pt.y );
        }

        constexpr PointType RightTop( ) const noexcept
        {
            return PointType( right_, top_ );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void SetRightTop( U right, V top ) noexcept
        {
            right_ = static_cast<value_type>( right );
            top_ = static_cast<value_type>( top );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void SetRightTop( const U& pt ) noexcept
        {
            SetRightTop( pt.X( ), pt.Y( ) );
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void SetRightTop( const U& pt ) noexcept
        {
            SetRightTop( pt.x, pt.y );
        }


        constexpr PointType LeftBottom( ) const noexcept
        {
            return PointType( left_, bottom_ );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void SetLeftBottom( U left, V bottom ) noexcept
        {
            left_ = static_cast<value_type>( left );
            bottom_ = static_cast<value_type>( bottom );
        }
        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void SetLeftBottom( const U& pt ) noexcept
        {
            SetLeftBottom( pt.X( ), pt.Y( ) );
        }

        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void SetLeftBottom( const U& pt ) noexcept
        {
            SetLeftBottom( pt.x, pt.y );
        }

        constexpr PointType RightBottom( ) const noexcept
        {
            return PointType( right_, bottom_ );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void SetRightBottom( U right, V bottom ) noexcept
        {
            right_ = static_cast<value_type>( right );
            bottom_ = static_cast<value_type>( bottom );
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void SetRightBottom( const U& pt ) noexcept
        {
            SetRightBottom( pt.X( ), pt.Y( ) );
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void SetRightBottom( const U& pt ) noexcept
        {
            SetRightBottom( pt.x, pt.y );
        }

        

        constexpr PointType Center( ) const noexcept
        {
            return PointType( ( left_ + right_ ) / 2, ( top_ + bottom_ ) / 2 );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void SetCenter( U x, V y ) noexcept
        {
            int width = ( right_ - left_ );
            int height = ( bottom_ - top_ );
            left_ = static_cast<value_type>( x ) - ( width / 2 );
            top_ = static_cast<value_type>( y ) - ( height / 2 );
            right_ = left_ + width;
            bottom_ = top_ + height;
        }

        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        constexpr void SetCenter( const U& pt ) noexcept
        {
            SetCenter( pt.X( ), pt.Y( ) );
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        constexpr void SetCenter( const U& pt ) noexcept
        {
            SetCenter( pt.x, pt.y );
        }

        constexpr PointType LeftCenter( ) const noexcept
        {
            return PointType( left_, ( top_ + bottom_ ) / 2 );
        }

        constexpr PointType RightCenter( ) const noexcept
        {
            return PointType( right_, ( top_ + bottom_ ) / 2 );
        }

        constexpr PointType TopCenter( ) const noexcept
        {
            return PointType( ( left_ + right_ ) / 2, top_ );
        }

        constexpr PointType BottomCenter( ) const noexcept
        {
            return PointType( ( left_ + right_ ) / 2, bottom_ );
        }

        constexpr SizeType Size( ) const noexcept
        {
            if ( left_ <= right_ ) [[likely]]
            {
                if ( top_ <= bottom_ ) [[likely]]
                {
                    return SizeType( right_ - left_, bottom_ - top_ );
                }
                else
                {
                    return SizeType( right_ - left_, top_ - bottom_ );
                }
            }
            else
            {
                if ( bottom_ <= top_ ) [[likely]]
                {
                    return SizeType( left_ - right_ , top_ - bottom_ );
                }
                else
                {
                    return SizeType( left_ - right_, bottom_ - top_  );
                }
            }
        }

        constexpr value_type Area() const noexcept
        { 
            if ( left_ <= right_ ) [[likely]]
            {
                if ( top_ <= bottom_ ) [[likely]]
                {
                    return ( right_ - left_ ) * ( bottom_ - top_ );
                }
                else
                {
                    return ( right_ - left_ ) * ( top_ - bottom_ );
                }
            }
            else
            {
                if ( bottom_ <= top_ ) [[likely]]
                {
                    return ( left_ - right_ ) * ( top_ - bottom_ );
                }
                else
                {
                    return ( left_ - right_ ) * ( bottom_ - top_ );
                }
            }
        }


        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void SetSize( U width, V height ) noexcept
        {
            right_ = left_ + static_cast<value_type>( std::abs( width ) );
            bottom_ = top_ + static_cast<value_type>( std::abs( height ) );
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr void SetSize( const U& size ) noexcept
        {
            SetSize( size.Width(), size.Height() );
        }
        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr void SetSize( const U& size ) noexcept
        {
            SetSize( size.width, size.height );
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void AddSize( U widthAndHeight ) noexcept
        {
            right_ += static_cast<value_type>( widthAndHeight );
            bottom_ += static_cast<value_type>( widthAndHeight );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void AddSize( U width, V height ) noexcept
        {
            right_ += static_cast<value_type>( width );
            bottom_ += static_cast<value_type>( height );
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr void AddSize( const U& size ) noexcept
        {
            AddSize( size.Width(), size.Height() );
        }
        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr void AddSize( const U& size ) noexcept
        {
            AddSize( size.width, size.height );
        }


        template<typename U>
            requires Internal::StaticCastableTo<U, value_type>
        constexpr void SubtractSize( U widthAndHeight ) noexcept
        {
            right_ -= static_cast<value_type>( widthAndHeight );
            bottom_ -= static_cast<value_type>( widthAndHeight );
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr void SubtractSize( U width, V height ) noexcept
        {
            right_ -= static_cast<value_type>( width );
            bottom_ -= static_cast<value_type>( height );
        }

        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        constexpr void SubtractSize( const U& size ) noexcept
        {
            SubtractSize( size.Width(), size.Height() );
        }
        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        constexpr void SubtractSize( const U& size ) noexcept
        {
            SubtractSize( size.width, size.height );
        }


        bool IsEmptyArea( ) const noexcept
        {
            if constexpr ( std::is_floating_point_v<value_type> )
            {
                return ( Width( ) <= std::numeric_limits<value_type>::epsilon( ) ) || ( Height( ) <= std::numeric_limits<value_type>::epsilon( ) );
            }
            else
            {
                return left_ == right_ || top_ == bottom_;
            }
        }
        bool IsEmpty( ) const noexcept
        {
            return left_ == right_ && top_ == bottom_;
        }

        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        constexpr bool Contains( U x, V y ) const noexcept
        {
            return static_cast<value_type>( x ) >= left_ && 
                static_cast<value_type>( x ) < right_ &&
                static_cast<value_type>( y ) >= bottom_ && 
                static_cast<value_type>( y ) < top_;
        }

        template<typename A, typename B, typename C, typename D>
            requires Internal::StaticCastable4To<A, B, C, D ,value_type>
        constexpr bool Contains( A left, B top, C right, D bottom ) const noexcept
        {
            return left_ <= static_cast<value_type>( left ) && 
                top_ <= static_cast<value_type>( top ) && 
                static_cast<value_type>( right ) <= right_ && 
                static_cast<value_type>( bottom ) <= bottom_;
        }

        template<typename U> 
            requires Internal::ImplementsXAndYFunctions<U,value_type> && ( Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type> == false )
        constexpr bool Contains( const U& point ) const noexcept
        {
            return Contains( point.X(), point.Y() );
        }

        template<typename U> 
            requires Internal::HasXAndY<U,value_type>
        constexpr bool Contains( const U& point ) const noexcept
        {
            return Contains( point.x, point.y );
        }
        template<typename U> 
            requires Internal::ImplementsLeftTopRightAndBottomFunctions<U,value_type>
        constexpr bool Contains( const U& rectangle ) const noexcept
        {
            return Contains( rectangle.Left(), rectangle.Top(), rectangle.Right(), rectangle.Bottom() );
        }

        template<typename U> 
            requires Internal::HasLeftTopRightAndBottom<U,value_type>
        constexpr bool Contains( const U& rectangle ) const noexcept
        {
            return Contains( rectangle.left, rectangle.top, rectangle.right, rectangle.bottom );
        }

        template<typename A, typename B, typename C, typename D>
            requires Internal::StaticCastable4To<A, B, C, D ,value_type>
        constexpr bool Overlaps( A left, B top, C right, D bottom ) const noexcept
        {
            if ( left <= right )
            {
                if ( top <= bottom )
                {
                    return static_cast<value_type>( right ) > left_ &&
                        static_cast<value_type>( bottom ) > top_ &&
                        static_cast<value_type>( left ) < right_ &&
                        static_cast<value_type>( top ) < bottom_;
                }
                else
                {
                    return static_cast<value_type>( right ) > left_ &&
                        static_cast<value_type>( top ) > top_ &&
                        static_cast<value_type>( left ) < right_ &&
                        static_cast<value_type>( bottom ) < bottom_;
                }
            }
            else
            {
                if ( top <= bottom )
                {
                    return static_cast<value_type>( left ) > left_ &&
                        static_cast<value_type>( bottom ) > top_ &&
                        static_cast<value_type>( right ) < right_ &&
                        static_cast<value_type>( top ) < bottom_;
                }
                else
                {
                    return static_cast<value_type>( left ) > left_ &&
                        static_cast<value_type>( top ) > top_ &&
                        static_cast<value_type>( right ) < right_ &&
                        static_cast<value_type>( bottom ) < bottom_;
                }
            }
        }


        template<typename U>
            requires Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type>
        constexpr bool Overlaps( const U& rectangle ) const noexcept
        {
            return Overlaps( rectangle.Left( ), rectangle.Top( ), rectangle.Right( ), rectangle.Bottom( ) );
        }


        template<typename U> 
            requires Internal::HasLeftTopRightAndBottom<U,value_type>
        constexpr bool Overlaps( const U& rectangle ) const noexcept
        {
            return Overlaps( rectangle.left, rectangle.top, rectangle.right, rectangle.bottom );
        }




        template<typename U, typename V>
            requires Internal::StaticCastable2To<U, V, value_type>
        void Inflate( U dx, V dy ) noexcept
        {
            left_ -= static_cast<value_type>( dx );
            top_ -= static_cast<value_type>( dy );
            right_ += static_cast<value_type>( dx );
            bottom_ += static_cast<value_type>( dy );
        }

        template<typename U>
        requires Internal::StaticCastableTo<U, value_type>
            void Inflate( U delta ) noexcept
        {
            left_ -= static_cast<value_type>( delta );
            top_ -= static_cast<value_type>( delta );
            right_ += static_cast<value_type>( delta );
            bottom_ += static_cast<value_type>( delta );
        }
        template<typename U>
            requires Internal::ImplementsXAndYFunctions<U, value_type>
        void Inflate( const U& point ) noexcept
        {
            Inflate( point.X(), point.Y() );
        }
        template<typename U>
            requires Internal::HasXAndY<U, value_type>
        void Inflate( const U& point ) noexcept
        {
            Inflate( point.x, point.x );
        }
        template<typename U>
            requires Internal::ImplementsWidthAndHeightFunctions<U, value_type>
        void Inflate( const U& size ) noexcept
        {
            Inflate( size.Width(), size.Height() );
        }
        template<typename U>
            requires Internal::HasWidthAndHeight<U, value_type>
        void Inflate( const U& size ) noexcept
        {
            Inflate( size.width, size.height );
        }
        template<typename U>
            requires Internal::HasCXAndCY<U, value_type>
        void Inflate( const U& size ) noexcept
        {
            Inflate( size.cx, size.cy );
        }

        template<typename A, typename B, typename C, typename D>
            requires Internal::StaticCastable4To<A, B, C, D, value_type>
        void IntersectWith( A left, B top, C right, D bottom )
        { 
            auto leftValue = static_cast<value_type>( left );
            auto topValue = static_cast<value_type>( top );
            auto rightValue = static_cast<value_type>( right );
            auto bottomValue = static_cast<value_type>( bottom );
            if ( left_ <= right_ )
            {
                if ( leftValue <= rightValue )
                {
                    left_ = std::max( left_, leftValue );
                    right_ = std::min( right_, rightValue );
                }
                else
                {
                    left_ = std::max( left_, rightValue );
                    right_ = std::min( right_, leftValue );
                }
            }
            else
            {
                if ( leftValue <= rightValue )
                {
                    auto tmp = left_;
                    left_ = std::max( right_, leftValue );
                    right_ = std::min( tmp, rightValue );
                }
                else
                {
                    auto tmp = left_;
                    left_ = std::max( right_, rightValue );
                    right_ = std::min( tmp, leftValue );
                }
            }
            if ( top_ <= bottom_ )
            {
                if ( topValue <= bottomValue )
                {
                    top_ = std::max( top_, topValue );
                    bottom_ = std::min( bottom_, bottomValue );
                }
                else
                {
                    top_ = std::max( top_, bottomValue );
                    bottom_ = std::min( bottom_, topValue );
                }
            }
            else
            {
                if ( topValue <= bottomValue )
                {
                    auto tmp = top_;
                    top_ = std::max( bottom_, topValue );
                    bottom_ = std::min( tmp, bottomValue );
                }
                else
                {
                    auto tmp = top_;
                    top_ = std::max( bottom_, bottomValue );
                    bottom_ = std::min( tmp, topValue );
                }
            }
        }

        template<typename U>
            requires Internal::ImplementsLeftTopRightAndBottomFunctions<U, value_type>
        void IntersectWith( const U& rectangle )
        {
            IntersectWith( rectangle.Left( ), rectangle.Top( ), rectangle.Right( ), rectangle.Bottom( ) );
        }

        template<typename U>
            requires Internal::HasLeftTopRightAndBottom<U, value_type>
        void IntersectWith( const U& rectangle )
        {
            IntersectWith( rectangle.left, rectangle.top, rectangle.right, rectangle.bottom );
        }

        constexpr bool IsInverted( ) const noexcept 
        { 
            return left_ > right_ || top_ > bottom_; 
        }

        constexpr void Normalize( ) noexcept
        {
            if ( left_ > right_ ) [[unlikely]]
            {
                std::swap( left_, right_ );
            }
            if ( top_ > bottom_ ) [[unlikely]]
            {
                std::swap( top_, bottom_ );
            }
        }


        constexpr operator RectangleType& ( ) noexcept
        {
            return *( (RectangleType*)&left_ );
        }
        constexpr operator const RectangleType& ( ) const noexcept
        {
            return *( (RectangleType*)&left_ );
        }
    };

    using Point = PointT<POINT>;
    static_assert( std::is_convertible_v<Point, POINT> );
    static_assert( std::is_convertible_v<POINT, Point> );

    using Size = SizeT<SIZE>;
    static_assert( std::is_convertible_v<Size, SIZE> );
    static_assert( std::is_convertible_v<SIZE, Size> );

    using Rectangle = RectangleT<RECT>;
    static_assert( std::is_convertible_v<Rectangle, RECT> );
    static_assert( std::is_convertible_v<RECT, Rectangle> );

    using Rect = Rectangle;

    namespace Graphics
    {
        using PointF = PointT<D2D_POINT_2F>;
        static_assert( std::is_convertible_v<PointF, D2D_POINT_2F> );
        static_assert( std::is_convertible_v<D2D_POINT_2F, PointF> );

        using SizeF = SizeT<D2D1_SIZE_F>;
        static_assert( std::is_convertible_v<SizeF, D2D1_SIZE_F> );
        static_assert( std::is_convertible_v<D2D1_SIZE_F, SizeF> );

        using RectangleF = RectangleT< D2D1_RECT_F>;
        static_assert( std::is_convertible_v<RectangleF, D2D1_RECT_F> );
        static_assert( std::is_convertible_v<D2D1_RECT_F, RectangleF> );

        using RectF = RectangleF;

        using PointU = PointT<D2D_POINT_2U>;
        static_assert( std::is_convertible_v<PointU, D2D_POINT_2U> );
        static_assert( std::is_convertible_v<D2D_POINT_2U, PointU> );

        using SizeU = SizeT<D2D1_SIZE_U>;
        static_assert( std::is_convertible_v<SizeU, D2D1_SIZE_U> );
        static_assert( std::is_convertible_v<D2D1_SIZE_U, SizeU> );

        using RectangleU = RectangleT<D2D1_RECT_U>;
        static_assert( std::is_convertible_v<RectangleU, D2D1_RECT_U> );
        static_assert( std::is_convertible_v<D2D1_RECT_U, RectangleU> );

        using RectU = RectangleU;

        using PointL = Windows::Point;
        using SizeL = Windows::Size;
        using RectangleL = Windows::Rectangle;
    }
}

namespace Harlinn::Common::Core::Math
{
    constexpr Harlinn::Windows::Point Min( const Harlinn::Windows::Point& first, const Harlinn::Windows::Point& second )
    {
        return first.min( second );
    }
    constexpr Harlinn::Windows::Point Max( const Harlinn::Windows::Point& first, const Harlinn::Windows::Point& second )
    {
        return first.max( second );
    }
    constexpr Harlinn::Windows::Graphics::PointF Min( const Harlinn::Windows::Graphics::PointF& first, const Harlinn::Windows::Graphics::PointF& second )
    {
        return first.min( second );
    }
    constexpr Harlinn::Windows::Graphics::PointF Max( const Harlinn::Windows::Graphics::PointF& first, const Harlinn::Windows::Graphics::PointF& second )
    {
        return first.max( second );
    }

    constexpr Harlinn::Windows::Size Min( const Harlinn::Windows::Size& first, const Harlinn::Windows::Size& second )
    {
        return first.min( second );
    }
    constexpr Harlinn::Windows::Size Max( const Harlinn::Windows::Size& first, const Harlinn::Windows::Size& second )
    {
        return first.max( second );
    }

    constexpr Harlinn::Windows::Graphics::SizeF Min( const Harlinn::Windows::Graphics::SizeF& first, const Harlinn::Windows::Graphics::SizeF& second )
    {
        return first.min( second );
    }
    constexpr Harlinn::Windows::Graphics::SizeF Max( const Harlinn::Windows::Graphics::SizeF& first, const Harlinn::Windows::Graphics::SizeF& second )
    {
        return first.max( second );
    }

    template<typename T>
        requires Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::PointT>
    constexpr inline std::remove_cvref_t<T> Clamp( T value, T minimumValue, T maximumValue ) noexcept
    {
        return
        {
            Clamp( value.X( ), minimumValue.X( ), maximumValue.X( ) ),
            Clamp( value.Y( ), minimumValue.Y( ), maximumValue.Y( ) )
        };
    }

    template<typename T>
        requires Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::SizeT>
    constexpr inline std::remove_cvref_t<T> Clamp( T value, T minimumValue, T maximumValue ) noexcept
    {
        return
        {
            Clamp( value.Width( ), minimumValue.Width( ), maximumValue.Width( ) ),
            Clamp( value.Height( ), minimumValue.Height( ), maximumValue.Height( ) )
        };
    }


    template<typename T>
        requires Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::PointT>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept
    {
        return
        {
            Floor( value.X( ) ),
            Floor( value.Y( ) )
        };
    }

    template<typename T>
        requires Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::SizeT>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept
    {
        return
        {
            Floor( value.Width( ) ),
            Floor( value.Height( ) )
        };
    }

    template<typename T>
        requires Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::PointT>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept
    {
        return
        {
            Ceil( value.X( ) ),
            Ceil( value.Y( ) )
        };
    }

    template<typename T>
        requires Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::SizeT>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept
    {
        return
        {
            Ceil( value.Width( ) ),
            Ceil( value.Height( ) )
        };
    }



    template<typename T>
        requires Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::PointT>
    constexpr inline std::remove_cvref_t<T> Lerp( T a, T b, T t ) noexcept
    {
        return
        {
            Lerp( a.X( ), b.X( ), t.X( ) ),
            Lerp( a.Y( ), b.Y( ), t.Y( ) )
        };
    }

    template<typename T, typename U >
        requires (Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::PointT> && IsFloatingPoint<U> )
    constexpr inline std::remove_cvref_t<T> Lerp( T a, T b, U t ) noexcept
    {
        return
        {
            Lerp( a.X( ), b.X( ), t ),
            Lerp( a.Y( ), b.Y( ), t )
        };
    }

    template<typename T>
        requires Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::SizeT>
    constexpr inline std::remove_cvref_t<T> Lerp( T a, T b, T t ) noexcept
    {
        return
        {
            Lerp( a.Width( ), b.Width( ), t.Width( ) ),
            Lerp( a.Height( ), b.Height( ), t.Height( ) )
        };
    }

}

namespace std
{
    template<typename T>
        requires (Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::PointT> || Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::SizeT> )
    constexpr auto min( const T& first, const T& second )
    {
        return first.min( second );
    }
    template<typename T>
        requires (Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::PointT> || Harlinn::Windows::Internal::IsSpecializationOf<std::remove_cvref_t<T>, Harlinn::Windows::SizeT> )
    constexpr auto max( const T& first, const T& second )
    {
        return first.max( second );
    }
}

#pragma pack(pop)

#endif
