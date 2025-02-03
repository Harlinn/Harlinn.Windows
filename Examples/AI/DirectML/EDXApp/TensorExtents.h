#pragma once
#ifndef TENSOREXTENTS_H_
#define TENSOREXTENTS_H_

//-----------------------------------------------------------------------------
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//-----------------------------------------------------------------------------


#include "HAIDef.h"

using namespace Harlinn::Windows;

template <size_t DimensionCount> struct TensorExtents {}; // Purposefully undefined

template <>
struct TensorExtents<1> // nExtents for 1D arrays of n elements.
{
    static constexpr size_t DimensionCount = 1;

    union
    {
        struct
        {
            UInt32 n;
        };

        UInt32 asArray[ DimensionCount ];
    };

    // Constructors

    TensorExtents( ) = default;

    /*implicit*/ TensorExtents( std::span<const UInt32> extents )
    {
        assert( extents.size( ) == DimensionCount );
        std::copy( extents.begin( ), extents.end( ), asArray );
    }

    TensorExtents( UInt32 n )
    {
        this->n = n;
    }

    // Accessors
    UInt32& operator[]( size_t i ) { assert( i < DimensionCount ); return asArray[ i ]; }
    const UInt32& operator[]( size_t i ) const { assert( i < DimensionCount ); return asArray[ i ]; }

    constexpr size_t size( ) const { return DimensionCount; }
};

//-----------------------------------------------------------------------------

template <>
struct TensorExtents<2> // HwExtents
{
    static constexpr size_t DimensionCount = 2;

    union
    {
        struct
        {
            UInt32 h;
            UInt32 w;
        };

        UInt32 asArray[ DimensionCount ];
    };

    // Constructors

    TensorExtents( ) = default;

    /*implicit*/ TensorExtents( std::span<const UInt32> extents )
    {
        assert( extents.size( ) == DimensionCount );
        std::copy( extents.begin( ), extents.end( ), asArray );
    }

    TensorExtents( UInt32 h, UInt32 w )
    {
        this->h = h;
        this->w = w;
    }

    // Accessors
    UInt32& operator[]( size_t i ) { assert( i < DimensionCount ); return asArray[ i ]; }
    const UInt32& operator[]( size_t i ) const { assert( i < DimensionCount ); return asArray[ i ]; }

    constexpr size_t size( ) const { return DimensionCount; }
};

//-----------------------------------------------------------------------------

template <>
struct TensorExtents<3> // ChwExtents
{
    static constexpr size_t DimensionCount = 3;

    union
    {
        struct
        {
            UInt32 c;
            UInt32 h;
            UInt32 w;
        };

        UInt32 asArray[ DimensionCount ];
    };

    // Constructors

    TensorExtents( ) = default;

    /*implicit*/ TensorExtents( std::span<const UInt32> extents )
    {
        assert( extents.size( ) == DimensionCount );
        std::copy( extents.begin( ), extents.end( ), asArray );
    }

    TensorExtents( UInt32 c, UInt32 h, UInt32 w )
    {
        this->c = c;
        this->h = h;
        this->w = w;
    }

    TensorExtents( UInt32 h, UInt32 w )
        : TensorExtents( 0, h, w )
    {
    }

    // Accessors
    UInt32& operator[]( size_t i ) { assert( i < DimensionCount ); return asArray[ i ]; }
    const UInt32& operator[]( size_t i ) const { assert( i < DimensionCount ); return asArray[ i ]; }

    constexpr size_t size( ) const { return DimensionCount; }
};

//-----------------------------------------------------------------------------

template <>
struct TensorExtents<4> // NchwExtents
{
    static constexpr size_t DimensionCount = 4;

    union
    {
        struct
        {
            UInt32 n;
            UInt32 c;
            UInt32 h;
            UInt32 w;
        };

        UInt32 asArray[ DimensionCount ];
    };

    // Constructors

    TensorExtents( ) = default;

    /*implicit*/ TensorExtents( std::span<const UInt32> extents )
    {
        assert( extents.size( ) == DimensionCount );
        std::copy( extents.begin( ), extents.end( ), asArray );
    }

    TensorExtents( UInt32 n, UInt32 c, UInt32 h, UInt32 w )
    {
        this->n = n;
        this->c = c;
        this->h = h;
        this->w = w;
    }

    TensorExtents( UInt32 c, UInt32 h, UInt32 w )
        : TensorExtents( 0, c, h, w )
    {
    }

    TensorExtents( UInt32 h, UInt32 w )
        : TensorExtents( 0, 0, h, w )
    {
    }

    // Accessors
    UInt32& operator[]( size_t i ) { assert( i < DimensionCount ); return asArray[ i ]; }
    const UInt32& operator[]( size_t i ) const { assert( i < DimensionCount ); return asArray[ i ]; }

    std::span<const UInt32> AsSpan( ) const noexcept { return std::span<const UInt32>( data( ), size( ) ); }
    std::span<UInt32> AsSpan( ) noexcept { return std::span<UInt32>( data( ), size( ) ); }

    constexpr size_t size( ) const { return DimensionCount; }
    const UInt32* data( ) const noexcept { return &asArray[ 0 ]; }
    const UInt32* begin( ) const noexcept { return &asArray[ 0 ]; }
    const UInt32* end( ) const noexcept { return &asArray[ DimensionCount ]; }
    UInt32* data( ) noexcept { return &asArray[ 0 ]; }
    UInt32* begin( ) noexcept { return &asArray[ 0 ]; }
    UInt32* end( ) noexcept { return &asArray[ DimensionCount ]; }
};

//-----------------------------------------------------------------------------

template <>
struct TensorExtents<5> // NcdhwExtents
{
    static constexpr size_t DimensionCount = 5;

    union
    {
        struct
        {
            UInt32 n;
            UInt32 c;
            UInt32 d;
            UInt32 h;
            UInt32 w;
        };

        UInt32 asArray[ DimensionCount ];
    };

    // Constructors

    TensorExtents( ) = default;

    /*implicit*/ TensorExtents( std::span<const UInt32> extents )
    {
        assert( extents.size( ) == DimensionCount );
        std::copy( extents.begin( ), extents.end( ), asArray );
    }

    TensorExtents( UInt32 n, UInt32 c, UInt32 d, UInt32 h, UInt32 w )
    {
        this->n = n;
        this->c = c;
        this->d = d;
        this->h = h;
        this->w = w;
    }

    TensorExtents( UInt32 n, UInt32 c, UInt32 h, UInt32 w )
        : TensorExtents( n, c, 0, h, w )
    {
    }

    TensorExtents( UInt32 c, UInt32 h, UInt32 w )
        : TensorExtents( 0, c, 0, h, w )
    {
    }

    TensorExtents( UInt32 h, UInt32 w )
        : TensorExtents( 0, 0, 0, h, w )
    {
    }

    // Accessors
    UInt32& operator[]( size_t i ) { assert( i < DimensionCount ); return asArray[ i ]; }
    const UInt32& operator[]( size_t i ) const { assert( i < DimensionCount ); return asArray[ i ]; }

    std::span<const UInt32> AsSpan( ) const noexcept { return std::span<const UInt32>( data( ), size( ) ); }
    std::span<UInt32> AsSpan( ) noexcept { return std::span<UInt32>( data( ), size( ) ); }

    constexpr size_t size( ) const { return DimensionCount; }
    const UInt32* data( ) const noexcept { return &asArray[ 0 ]; }
    const UInt32* begin( ) const noexcept { return &asArray[ 0 ]; }
    const UInt32* end( ) const noexcept { return &asArray[ DimensionCount ]; }
    UInt32* data( ) noexcept { return &asArray[ 0 ]; }
    UInt32* begin( ) noexcept { return &asArray[ 0 ]; }
    UInt32* end( ) noexcept { return &asArray[ DimensionCount ]; }
};

//-----------------------------------------------------------------------------
// Operator overloads

template <size_t DimensionCount>
bool operator==( const TensorExtents<DimensionCount>& lhs, const TensorExtents<DimensionCount>& rhs )
{
    return std::equal( std::begin( lhs.asArray ), std::end( lhs.asArray ), std::begin( rhs.asArray ), std::end( rhs.asArray ) );
}

template <size_t DimensionCount>
bool operator!=( const TensorExtents<DimensionCount>& lhs, const TensorExtents<DimensionCount>& rhs )
{
    return !( lhs == rhs );
}

template <size_t DimensionCount>
TensorExtents<DimensionCount>& operator+=( TensorExtents<DimensionCount>& lhs, const TensorExtents<DimensionCount>& rhs )
{
    for ( size_t i = 0; i < DimensionCount; ++i )
    {
        lhs[ i ] += rhs[ i ];
    }
    return lhs;
}

template <size_t DimensionCount>
TensorExtents<DimensionCount> operator+( TensorExtents<DimensionCount> lhs, const TensorExtents<DimensionCount>& rhs )
{
    lhs += rhs;
    return lhs;
}

template <size_t DimensionCount>
TensorExtents<DimensionCount>& operator-=( TensorExtents<DimensionCount>& lhs, const TensorExtents<DimensionCount>& rhs )
{
    for ( size_t i = 0; i < DimensionCount; ++i )
    {
        lhs[ i ] -= rhs[ i ];
    }
    return lhs;
}

template <size_t DimensionCount>
TensorExtents<DimensionCount> operator-( TensorExtents<DimensionCount> lhs, const TensorExtents<DimensionCount>& rhs )
{
    lhs -= rhs;
    return lhs;
}

template <size_t DimensionCount>
TensorExtents<DimensionCount>& operator&=( TensorExtents<DimensionCount>& lhs, const TensorExtents<DimensionCount>& rhs )
{
    for ( size_t i = 0; i < DimensionCount; ++i )
    {
        lhs[ i ] &= rhs[ i ];
    }
    return lhs;
}

template <size_t DimensionCount>
TensorExtents<DimensionCount> operator&( TensorExtents<DimensionCount> lhs, const TensorExtents<DimensionCount>& rhs )
{
    lhs &= rhs;
    return lhs;
}

//-----------------------------------------------------------------------------
// Helper typedefs
using HwExtents = TensorExtents<2>;
using ChwExtents = TensorExtents<3>;
using NchwExtents = TensorExtents<4>;
using NcdhwExtents = TensorExtents<5>;

#endif
