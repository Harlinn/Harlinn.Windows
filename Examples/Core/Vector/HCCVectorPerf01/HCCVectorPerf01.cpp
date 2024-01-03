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


#include <HCCVector.h>
#include <HCCDateTime.h>
#include <HCCApplication.h>


using namespace Harlinn::Common::Core;


class TimeseriesPoint
{
    DateTime timestamp_;
    UInt64 flags_;
    double value_;
public:
    constexpr TimeseriesPoint( ) noexcept
        : flags_( 0 ), value_( 0 )
    {
    }

    constexpr TimeseriesPoint( DateTime timestamp, double value ) noexcept
        : timestamp_( timestamp ), flags_( 0 ), value_( value )
    {
    }
    constexpr TimeseriesPoint( DateTime timestamp, UInt64 flags, double value ) noexcept
        : timestamp_( timestamp ), flags_( flags ), value_( value )
    {
    }

    constexpr void Assign( DateTime timestamp, double value ) noexcept
    {
        timestamp_ = timestamp;
        flags_ = 0;
        value_ = value;
    }
    constexpr void Assign( DateTime timestamp, UInt64 flags, double value ) noexcept
    {
        timestamp_ = timestamp;
        flags_ = flags;
        value_ = value;
    }

    constexpr DateTime Timestamp( ) const noexcept
    {
        return timestamp_;
    }
    constexpr UInt64 Flags( ) const noexcept
    {
        return flags_;
    }
    constexpr double Value( ) const noexcept
    {
        return value_;
    }

    auto operator<=>( const TimeseriesPoint& ) const = default;
};


class VectorPoints
{
    SSizeT id_;
    Vector<TimeseriesPoint> values_;
public:
    VectorPoints( SSizeT id, SSizeT count )
        : id_( id )
    {
        values_.reserve( count );
        for ( SSizeT i = 0; i < count; ++i )
        {
            SSizeT value = ( i + 1 );
            values_.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    constexpr SSizeT Id( ) const noexcept
    {
        return id_;
    }

};

class StdVectorPoints
{
    SSizeT id_;
    std::vector<TimeseriesPoint> values_;
public:
    StdVectorPoints( SSizeT id, SSizeT count )
        : id_( id )
    {
        values_.reserve( count );
        for ( SSizeT i = 0; i < count; ++i )
        {
            SSizeT value = ( i + 1 );
            values_.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    constexpr SSizeT Id( ) const noexcept
    {
        return id_;
    }

};


class SmallVectorPoints
{
    SSizeT id_;
    std::vector<TimeseriesPoint> values_;
public:
    SmallVectorPoints( SSizeT id, SSizeT count )
        : id_( id )
    {
        values_.reserve( count );
        for ( SSizeT i = 0; i < count; ++i )
        {
            SSizeT value = ( i + 1 );
            values_.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    constexpr SSizeT Id( ) const noexcept
    {
        return id_;
    }

};



class CopyableObject
{
    Int64 id_;
public:
    constexpr CopyableObject() noexcept
        : id_(0)
    { }

    constexpr explicit CopyableObject( Int64 id ) noexcept
        : id_( id )
    {
    }

    

    constexpr CopyableObject(const CopyableObject& other ) noexcept
        : id_( other.id_ )
    {
    }

    constexpr CopyableObject( CopyableObject&& other ) = delete;


    ~CopyableObject( )
    {
    }

    constexpr CopyableObject& operator = ( const CopyableObject& other ) noexcept
    {
        id_ = other.id_;
        return *this;
    }

    constexpr CopyableObject& operator = ( CopyableObject&& other ) = delete;

    constexpr Int64 Id( ) const noexcept
    {
        return id_;
    }


};

class MoveableObject
{
    Int64 id_;
public:
    constexpr MoveableObject( ) noexcept
        : id_( 0 )
    {
    }

    constexpr explicit MoveableObject( Int64 id ) noexcept
        : id_( id )
    {
    }


    ~MoveableObject( )
    {
    }

    constexpr Int64 Id( ) const noexcept
    {
        return id_;
    }

};


constexpr bool timeseriesPointIsTriviallyConstructible = std::is_trivially_constructible_v<TimeseriesPoint>;
constexpr bool timeseriesPointIsTriviallyCopyable = std::is_trivially_copyable_v<TimeseriesPoint>;
constexpr bool timeseriesPointIsMoveConstructible = std::is_move_constructible_v<TimeseriesPoint>;
constexpr bool timeseriesPointIsMoveAssignable = std::is_move_assignable_v<TimeseriesPoint>;
constexpr bool timeseriesPointIsTriviallyDestructible = std::is_trivially_destructible_v<TimeseriesPoint>;

constexpr bool vectorPointsIsTriviallyConstructible = std::is_trivially_constructible_v<VectorPoints>;
constexpr bool vectorPointsIsTriviallyCopyable = std::is_trivially_copyable_v<VectorPoints>;
constexpr bool vectorPointsIsMoveConstructible = std::is_move_constructible_v<VectorPoints>;
constexpr bool vectorPointsIsMoveAssignable = std::is_move_assignable_v<VectorPoints>;
constexpr bool vectorPointsIsTriviallyDestructible = std::is_trivially_destructible_v<VectorPoints>;

constexpr bool copyableObjectIsTriviallyConstructible = std::is_trivially_constructible_v<CopyableObject>;
constexpr bool copyableObjectIsTriviallyCopyable = std::is_trivially_copyable_v<CopyableObject>;
constexpr bool copyableObjectIsMoveConstructible = std::is_move_constructible_v<CopyableObject>;
constexpr bool copyableObjectIsMoveAssignable = std::is_move_assignable_v<CopyableObject>;
constexpr bool copyableObjectIsTriviallyDestructible = std::is_trivially_destructible_v<CopyableObject>;
constexpr bool copyableObjectIsCopyConstructible = std::is_copy_constructible_v<CopyableObject>;
constexpr bool copyableObjectIsCopyAssignable = std::is_copy_assignable_v<CopyableObject>;

constexpr bool moveableObjectIsTriviallyConstructible = std::is_trivially_constructible_v<MoveableObject>;
constexpr bool moveableObjectIsTriviallyCopyable = std::is_trivially_copyable_v<MoveableObject>;
constexpr bool moveableObjectIsMoveConstructible = std::is_move_constructible_v<MoveableObject>;
constexpr bool moveableObjectIsMoveAssignable = std::is_move_assignable_v<MoveableObject>;
constexpr bool moveableObjectIsTriviallyDestructible = std::is_trivially_destructible_v<MoveableObject>;




void VectorEmplaceBackTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_back using trivially copyable TimeseriesPoint: %lld iterations, reserves required capacity and calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}


void VectorEmplaceBackTest1b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_back using trivially copyable TimeseriesPoint: %lld iterations, reserves required capacity and calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}

void VectorEmplaceBackTest1c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_back using trivially copyable TimeseriesPoint: %lld iterations, reserves required capacity and calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}



void VectorEmplaceBackTest2a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_back using trivially copyable TimeseriesPoint: %lld iterations, calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint,16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEmplaceBackTest2b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_back using trivially copyable TimeseriesPoint: %lld iterations, calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorEmplaceBackTest2c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_back using trivially copyable TimeseriesPoint: %lld iterations, calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}



void VectorEmplaceBackTest3a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_back using MoveableObject: %lld iterations, reserves required capacity and calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value  );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject,16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorEmplaceBackTest3b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_back using MoveableObject: %lld iterations, reserves required capacity and calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEmplaceBackTest3c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_back using MoveableObject: %lld iterations, reserves required capacity and calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}



void VectorEmplaceBackTest4a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_back using MoveableObject: %lld iterations, calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject,16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEmplaceBackTest4b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_back using MoveableObject: %lld iterations, calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEmplaceBackTest4c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_back using MoveableObject: %lld iterations, calls emplace_back %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_back( value );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEmplaceFrontTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_front using trivially copyable TimeseriesPoint: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_front( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint,16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );


}


void VectorEmplaceFrontTest1b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_front using trivially copyable TimeseriesPoint: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_front( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );


}

void VectorEmplaceFrontTest1c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_front using trivially copyable TimeseriesPoint: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_front( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );


}




void VectorEmplaceFrontTest2a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_front using trivially copyable TimeseriesPoint: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_front( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}


void VectorEmplaceFrontTest2b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_front using trivially copyable TimeseriesPoint: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_front( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}


void VectorEmplaceFrontTest2c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_front using trivially copyable TimeseriesPoint: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace_front( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points.emplace( points.begin( ), DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}


void VectorEmplaceFrontTest3a( )
{
    printf( "%s\n", __FUNCTION__ );
    using Points = VectorPoints;
    using StdPoints = StdVectorPoints;

    constexpr SSizeT InterationCount = 1000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_front using move constructible, move assignable VectorPoints/StdVectorPoints/SmallVectorPoints: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<Points> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j, 10 );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<StdPoints> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<SmallVectorPoints,16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}

void VectorEmplaceFrontTest3b( )
{
    printf( "%s\n", __FUNCTION__ );
    using Points = VectorPoints;
    using StdPoints = StdVectorPoints;

    constexpr SSizeT InterationCount = 1000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_front using move constructible, move assignable VectorPoints/StdVectorPoints/SmallVectorPoints: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<Points> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j, 10 );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<StdPoints> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<SmallVectorPoints, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}


void VectorEmplaceFrontTest3c( )
{
    printf( "%s\n", __FUNCTION__ );
    using Points = VectorPoints;
    using StdPoints = StdVectorPoints;

    constexpr SSizeT InterationCount = 1000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_front using move constructible, move assignable VectorPoints/StdVectorPoints/SmallVectorPoints: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<Points> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j, 10 );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<StdPoints> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<SmallVectorPoints, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}


void VectorEmplaceFrontTest4a( )
{
    printf( "%s\n", __FUNCTION__ );
    using Points = VectorPoints;
    using StdPoints = StdVectorPoints;

    constexpr bool pointsIsTriviallyCopyable = std::is_trivially_copyable_v<Points>;
    constexpr bool pointsIsMoveConstructible = std::is_move_constructible_v<Points>;
    constexpr bool pointsIsMoveAssignable = std::is_move_assignable_v<Points>;
    constexpr bool stdPointsIsTriviallyCopyable = std::is_trivially_copyable_v<StdPoints>;

    constexpr SSizeT InterationCount = 1000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_front using move constructible, move assignable VectorPoints/StdVectorPoints/SmallVectorPoints: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<Points> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j, 10 );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<StdPoints> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<SmallVectorPoints, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}

void VectorEmplaceFrontTest4b( )
{
    printf( "%s\n", __FUNCTION__ );
    using Points = VectorPoints;
    using StdPoints = StdVectorPoints;

    constexpr bool pointsIsTriviallyCopyable = std::is_trivially_copyable_v<Points>;
    constexpr bool pointsIsMoveConstructible = std::is_move_constructible_v<Points>;
    constexpr bool pointsIsMoveAssignable = std::is_move_assignable_v<Points>;
    constexpr bool stdPointsIsTriviallyCopyable = std::is_trivially_copyable_v<StdPoints>;

    constexpr SSizeT InterationCount = 1000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_front using move constructible, move assignable VectorPoints/StdVectorPoints/SmallVectorPoints: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<Points> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j, 10 );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<StdPoints> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<SmallVectorPoints, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}

void VectorEmplaceFrontTest4c( )
{
    printf( "%s\n", __FUNCTION__ );
    using Points = VectorPoints;
    using StdPoints = StdVectorPoints;

    constexpr SSizeT InterationCount = 1000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_front using move constructible, move assignable VectorPoints/StdVectorPoints/SmallVectorPoints: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<Points> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j, 10 );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<StdPoints> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<SmallVectorPoints, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j, 10 );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}



void VectorEmplaceFrontTest5a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_front using MoveableObject: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject,16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}

void VectorEmplaceFrontTest5b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_front using MoveableObject: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}

void VectorEmplaceFrontTest5c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_front using MoveableObject: %lld iterations, reserves required capacity and calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> points;
        points.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );
}


void VectorEmplaceFrontTest6a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace_front using MoveableObject: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject,16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEmplaceFrontTest6b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace_front using MoveableObject: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEmplaceFrontTest6c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 17;

    printf( "emplace_front using MoveableObject: %lld iterations, calls emplace_front %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace_front( j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            points.emplace( points.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}



void VectorResizeTest1( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "resize using trivially copyable TimeseriesPoint: %lld iterations, sets the size to %lld.\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        SSizeT value = ( i * ItemCount ) + 1;
        Vector<TimeseriesPoint> points;
        points.resize( ItemCount, TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) ) );

    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        SSizeT value = ( i * ItemCount ) + 1;
        std::vector<TimeseriesPoint> points;
        points.resize( ItemCount, TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) ) );
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );
}


void VectorArrayOperatorTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 1000000000;
    constexpr SSizeT ItemCount = 50;

    printf( "operator[]( offset ) using trivially copyable TimeseriesPoint: %lld iterations, calls operator[]( offset ) %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    {
        Vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    {
        std::vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }



    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    {
        boost::container::small_vector<TimeseriesPoint, 16> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorArrayOperatorTest1b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 1000000000;
    constexpr SSizeT ItemCount = 16;

    printf( "operator[]( offset ) using trivially copyable TimeseriesPoint: %lld iterations, calls operator[]( offset ) %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    {
        Vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    {
        std::vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }



    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    {
        boost::container::small_vector<TimeseriesPoint, 16> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorArrayOperatorTest1c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 1000000000;
    constexpr SSizeT ItemCount = 17;

    printf( "operator[]( offset ) using trivially copyable TimeseriesPoint: %lld iterations, calls operator[]( offset ) %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    {
        Vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    {
        std::vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }



    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    {
        boost::container::small_vector<TimeseriesPoint, 16> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( SSizeT j = 0; j < ItemCount; ++j )
            {
                auto& point = vector[j];
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorRangeForLoopTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 1000000000;
    constexpr SSizeT ItemCount = 50;

    printf( "for ( auto& point : vector ) using trivially copyable TimeseriesPoint: %lld iterations, vector holds %lld points\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    {
        Vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( auto& point : vector )
            {
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    {
        std::vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( auto& point : vector )
            {
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }



    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    {
        boost::container::small_vector<TimeseriesPoint, 16> vector( ItemCount );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( auto& point : vector )
            {
                if ( point.Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorIteratorForLoopTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 1000000000;
    constexpr SSizeT ItemCount = 50;

    printf( "for ( auto it = vector.begin( ); it != end; ++it ) using trivially copyable TimeseriesPoint: %lld iterations, vector holds %lld points\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    {
        const Vector<TimeseriesPoint> vector( ItemCount );
        
        auto end = vector.end( );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( auto it = vector.begin( ); it != end; ++it )
            {
                if ( it->Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    {
        const std::vector<TimeseriesPoint> vector( ItemCount );

        auto end = vector.end( );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( auto it = vector.begin( ); it != end; ++it )
            {
                if ( it->Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }



    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    {
        const boost::container::small_vector<TimeseriesPoint, 16> vector( ItemCount );

        auto end = vector.end( );
        for ( SSizeT i = 0; i < InterationCount; ++i )
        {
            for ( auto it = vector.begin( ); it != end; ++it )
            {
                if ( it->Flags( ) != 0 )
                {
                    printf( "Surprise!!!\n" );
                }
            }
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}




void VectorEraseTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "erase using MoveableObject: %lld iterations, calls erase %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> vector( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            auto it = vector.begin( );
            vector.erase( it );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> vector( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            auto it = vector.begin( );
            vector.erase( it );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject,16> vector( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            auto it = vector.begin( );
            vector.erase( it );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEraseTest2a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "erase using trivially copyable TimeseriesPoint: %lld iterations, calls erase %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            auto it = vector.begin( );
            vector.erase( it );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> vector( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            auto it = vector.begin( );
            vector.erase( it );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> vector( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            auto it = vector.begin( );
            vector.erase( it );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorEmplaceTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace using MoveableObject: %lld iterations, reserves required capacity and calls emplace %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorEmplaceTest1b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 16;

    printf( "emplace using MoveableObject: %lld iterations, reserves required capacity and calls emplace %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorEmplaceTest2a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace using MoveableObject: %lld iterations, calls emplace %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


void VectorEmplaceTest3a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace using MoveableObject: %lld iterations, calls emplace %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<MoveableObject> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.end( ), j );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<MoveableObject> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.end( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<MoveableObject, 16> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.end( ), j );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}



void VectorEmplaceTest4a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace trivially copyable TimeseriesPoint: %lld iterations, reserves required capacity and calls emplace %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), DateTime( j ), static_cast<double>( j ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), DateTime( j ), static_cast<double>( j ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> vector;
        vector.reserve( ItemCount );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), DateTime( j ), static_cast<double>( j ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}

void VectorEmplaceTest5a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 10000000;
    constexpr SSizeT ItemCount = 50;

    printf( "emplace trivially copyable TimeseriesPoint: %lld iterations, calls emplace %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Vector<TimeseriesPoint> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), DateTime( j ), static_cast<double>( j ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tVector: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::vector<TimeseriesPoint> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), DateTime( j ), static_cast<double>( j ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::vector: %f seconds.\n", duration );


    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        boost::container::small_vector<TimeseriesPoint, 16> vector;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            vector.emplace( vector.begin( ), DateTime( j ), static_cast<double>( j ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tboost::container::small_vector: %f seconds.\n\n", duration );

}


int main()
{
    auto options = std::make_shared<ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

#define RUN_ALL 1
#ifdef RUN_ALL
    VectorEmplaceBackTest1a( );
#endif
    VectorEmplaceBackTest1b( );
#ifdef RUN_ALL
    VectorEmplaceBackTest1c( );

    VectorEmplaceBackTest2a( );
    VectorEmplaceBackTest2b( );
    VectorEmplaceBackTest2c( );
    
    VectorEmplaceBackTest3a( );
    VectorEmplaceBackTest3b( );
    VectorEmplaceBackTest3c( );
    VectorEmplaceBackTest4a( );
    VectorEmplaceBackTest4b( );
    VectorEmplaceBackTest4c( );
    
    
    VectorEmplaceFrontTest1a( );
    VectorEmplaceFrontTest1b( );
    VectorEmplaceFrontTest1c( );
    
    
    VectorEmplaceFrontTest2a( );
    VectorEmplaceFrontTest2b( );
    VectorEmplaceFrontTest2c( );
    
    
    VectorEmplaceFrontTest3a( );
    VectorEmplaceFrontTest3b( );
    VectorEmplaceFrontTest3c( );
    
    
    VectorEmplaceFrontTest4a( );
    VectorEmplaceFrontTest4b( );
    VectorEmplaceFrontTest4c( );
    

    VectorEmplaceFrontTest5a( );
    VectorEmplaceFrontTest5b( );
    VectorEmplaceFrontTest5c( );
    
    
    VectorEmplaceFrontTest6a( );
    VectorEmplaceFrontTest6b( );
    VectorEmplaceFrontTest6c( );

    VectorResizeTest1( );

    VectorArrayOperatorTest1a( );
    VectorArrayOperatorTest1b( );
    VectorArrayOperatorTest1c( );
    

    VectorRangeForLoopTest1a( );
    VectorIteratorForLoopTest1a( );


    VectorEraseTest1a( );
    VectorEraseTest2a( );

    VectorEmplaceTest1a( );
    VectorEmplaceTest1b( );
    VectorEmplaceTest2a( );

    VectorEmplaceTest3a( );
    VectorEmplaceTest4a( );
    VectorEmplaceTest5a( );
#endif
    application->Stop( );
}

