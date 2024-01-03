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

#include "pch.h"

using namespace Harlinn::Common::Core;

class TimeseriesPoint
{
    DateTime timestamp_;
    UInt64 flags_;
    double value_;
public:
    constexpr TimeseriesPoint() noexcept
        : flags_(0), value_(0)
    { }

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

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    class PointsContainer
    {
        SSizeT id_;
        Vector<TimeseriesPoint> values_;
    public:
        constexpr PointsContainer( ) noexcept
            : id_(0)
        { }


        PointsContainer( SSizeT id, SSizeT count )
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



}

BOOST_FIXTURE_TEST_SUITE( VectorTests, LocalFixture )

// --run_test=VectorTests/VectorIteratorTraitTest1
BOOST_AUTO_TEST_CASE( VectorIteratorTraitTest1 )
{
    using IntVector = Vector<int>;
    constexpr bool isRandomAccessIterator = IsRandomAccessIterator_v<IntVector::iterator>;
    BOOST_CHECK( isRandomAccessIterator );
}


// --run_test=VectorTests/VectorConstructorTest1
BOOST_AUTO_TEST_CASE( VectorConstructorTest1 )
{
    Vector<DateTime> vector;

    BOOST_CHECK( vector.begin() == nullptr );
    BOOST_CHECK( vector.end( ) == nullptr );
    BOOST_CHECK( vector.data( ) == nullptr );
    BOOST_CHECK( vector.size( ) == 0 );
    BOOST_CHECK( vector.capacity( ) == 0 );
}

// --run_test=VectorTests/VectorConstructorTest2
BOOST_AUTO_TEST_CASE( VectorConstructorTest2 )
{
    Vector<PointsContainer> vector;

    BOOST_CHECK( vector.begin( ) == nullptr );
    BOOST_CHECK( vector.end( ) == nullptr );
    BOOST_CHECK( vector.data( ) == nullptr );
    BOOST_CHECK( vector.size( ) == 0 );
    BOOST_CHECK( vector.capacity( ) == 0 );
}



// --run_test=VectorTests/VectorConstructorTest3
BOOST_AUTO_TEST_CASE( VectorConstructorTest3 )
{
    DateTime now = DateTime::Now( );
    SSizeT count = 5;
    Vector<DateTime> vector(count,now);

    BOOST_CHECK( vector.begin( ) != nullptr );
    BOOST_CHECK( vector.end( ) != nullptr );
    BOOST_CHECK( vector.data( ) != nullptr );
    BOOST_CHECK( vector.size( ) == count );
    BOOST_CHECK( vector.capacity( ) >= count );
}

// --run_test=VectorTests/VectorConstructorTest4
BOOST_AUTO_TEST_CASE( VectorConstructorTest4 )
{
    SSizeT count = 5;
    PointsContainer pointsContainer( 1, 10 );

    Vector<PointsContainer> vector( count, pointsContainer );

    BOOST_CHECK( vector.begin( ) != nullptr );
    BOOST_CHECK( vector.end( ) != nullptr );
    BOOST_CHECK( vector.data( ) != nullptr );
    BOOST_CHECK( vector.size( ) == count );
    BOOST_CHECK( vector.capacity( ) >= count );
}



// --run_test=VectorTests/VectorConstructorTest5
BOOST_AUTO_TEST_CASE( VectorConstructorTest5 )
{
    SSizeT count = 5;
    Vector<DateTime> vector( count );

    BOOST_CHECK( vector.begin( ) != nullptr );
    BOOST_CHECK( vector.end( ) != nullptr );
    BOOST_CHECK( vector.data( ) != nullptr );
    BOOST_CHECK( vector.size( ) == count );
    BOOST_CHECK( vector.capacity( ) >= count );
    BOOST_CHECK( vector[0] == DateTime( 0LL ) );
    BOOST_CHECK( vector[4] == DateTime( 0LL ) );
}


// --run_test=VectorTests/VectorConstructorTest6
BOOST_AUTO_TEST_CASE( VectorConstructorTest6 )
{
    SSizeT count = 5;
    Vector<PointsContainer> vector( count );

    BOOST_CHECK( vector.begin( ) != nullptr );
    BOOST_CHECK( vector.end( ) != nullptr );
    BOOST_CHECK( vector.data( ) != nullptr );
    BOOST_CHECK( vector.size( ) == count );
    BOOST_CHECK( vector.capacity( ) >= count );
    BOOST_CHECK( vector[0].Id( ) == 0LL );
    BOOST_CHECK( vector[4].Id( ) == 0LL );
}


// --run_test=VectorTests/VectorConstructorTest7
BOOST_AUTO_TEST_CASE( VectorConstructorTest7 )
{
    SSizeT count = 5;
    Vector<Int32> vector( count );

    BOOST_CHECK( vector.begin( ) != nullptr );
    BOOST_CHECK( vector.end( ) != nullptr );
    BOOST_CHECK( vector.data( ) != nullptr );
    BOOST_CHECK( vector.size( ) == count );
    BOOST_CHECK( vector.capacity( ) >= count );
    BOOST_CHECK( vector[0] == 0 );
    BOOST_CHECK( vector[4] == 0 );
}



// --run_test=VectorTests/VectorConstructorTest8
BOOST_AUTO_TEST_CASE( VectorConstructorTest8 )
{
    Vector<DateTime> vector1;
    Vector<DateTime> vector2( vector1 );

    BOOST_CHECK( vector2.begin( ) == nullptr );
    BOOST_CHECK( vector2.end( ) == nullptr );
    BOOST_CHECK( vector2.data( ) == nullptr );
    BOOST_CHECK( vector2.size( ) == 0 );
    BOOST_CHECK( vector2.capacity( ) == 0 );
}

// --run_test=VectorTests/VectorConstructorTest9
BOOST_AUTO_TEST_CASE( VectorConstructorTest9 )
{
    Vector<PointsContainer> vector1;
    Vector<PointsContainer> vector2( vector1 );

    BOOST_CHECK( vector2.begin( ) == nullptr );
    BOOST_CHECK( vector2.end( ) == nullptr );
    BOOST_CHECK( vector2.data( ) == nullptr );
    BOOST_CHECK( vector2.size( ) == 0 );
    BOOST_CHECK( vector2.capacity( ) == 0 );
}


// --run_test=VectorTests/VectorConstructorTest10
BOOST_AUTO_TEST_CASE( VectorConstructorTest10 )
{
    DateTime now = DateTime::Now( );
    SSizeT count = 5;
    Vector<DateTime> vector1( count, now );
    Vector<DateTime> vector2( vector1 );

    BOOST_CHECK( vector2.begin( ) != nullptr );
    BOOST_CHECK( vector2.end( ) != nullptr );
    BOOST_CHECK( vector2.data( ) != nullptr );
    BOOST_CHECK( vector2.size( ) == count );
    BOOST_CHECK( vector2.capacity( ) >= count );
}

// --run_test=VectorTests/VectorConstructorTest11
BOOST_AUTO_TEST_CASE( VectorConstructorTest11 )
{
    PointsContainer pointsContainer(1, 10 );
    SSizeT count = 5;
    Vector<PointsContainer> vector1( count, pointsContainer );
    Vector<PointsContainer> vector2( vector1 );

    BOOST_CHECK( vector2.begin( ) != nullptr );
    BOOST_CHECK( vector2.end( ) != nullptr );
    BOOST_CHECK( vector2.data( ) != nullptr );
    BOOST_CHECK( vector2.size( ) == count );
    BOOST_CHECK( vector2.capacity( ) >= count );
}


// --run_test=VectorTests/VectorConstructorTest12
BOOST_AUTO_TEST_CASE( VectorConstructorTest12 )
{
    SSizeT count = 5;
    Vector vector = {1,2,3,4,5};

    BOOST_CHECK( vector.begin( ) != nullptr );
    BOOST_CHECK( vector.end( ) != nullptr );
    BOOST_CHECK( vector.data( ) != nullptr );
    BOOST_CHECK( vector.size( ) == count );
    BOOST_CHECK( vector.capacity( ) >= count );
    BOOST_CHECK( vector[0] == 1 );
    BOOST_CHECK( vector[4] == 5 );
}



// --run_test=VectorTests/VectorEmplaceBackTest1
BOOST_AUTO_TEST_CASE( VectorEmplaceBackTest1 )
{
    constexpr SSizeT ItemCount = 50;

    Vector<TimeseriesPoint> points;
    points.reserve( ItemCount );
    for ( SSizeT i = 0; i < ItemCount; ++i )
    {
        SSizeT value = i + 1;
        points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
    }

    for ( SSizeT i = 0; i < ItemCount; ++i )
    {
        SSizeT value = i + 1;
        DateTime expectedTimestamp( value );
        double expectedValue = static_cast<double>( value );
        auto& point = points[i];

        BOOST_CHECK( point.Timestamp( ) == expectedTimestamp );
        BOOST_CHECK( point.Flags( ) == 0 );
        BOOST_CHECK( point.Value( ) == expectedValue );
    }
}

// --run_test=VectorTests/VectorEmplaceBackTest2
BOOST_AUTO_TEST_CASE( VectorEmplaceBackTest2 )
{
    constexpr SSizeT ItemCount = 50;

    Vector<TimeseriesPoint> points;
    for ( SSizeT i = 0; i < ItemCount; ++i )
    {
        SSizeT value = i + 1;
        points.emplace_back( DateTime( value ), 0, static_cast<double>( value ) );
    }

    for ( SSizeT i = 0; i < ItemCount; ++i )
    {
        SSizeT value = i + 1;
        DateTime expectedTimestamp( value );
        double expectedValue = static_cast<double>( value );
        auto& point = points[i];

        BOOST_CHECK( point.Timestamp( ) == expectedTimestamp );
        BOOST_CHECK( point.Flags( ) == 0 );
        BOOST_CHECK( point.Value( ) == expectedValue );
    }
}



// --run_test=VectorTests/VectorEmplaceFrontTest1
BOOST_AUTO_TEST_CASE( VectorEmplaceFrontTest1 )
{
    constexpr SSizeT ItemCount = 50;

    Vector<TimeseriesPoint> points;
    points.reserve( ItemCount );
    for ( SSizeT i = 0; i < ItemCount; ++i )
    {
        SSizeT value = i + 1;
        points.emplace_front( DateTime( value ), 0, static_cast<double>( value ) );
    }

    for ( SSizeT i = 0; i < ItemCount; ++i )
    {
        SSizeT value = ItemCount - i;

        DateTime expectedTimestamp( value );
        double expectedValue = static_cast<double>( value );
        auto& point = points[i];

        BOOST_CHECK( point.Timestamp( ) == expectedTimestamp );
        BOOST_CHECK( point.Flags( ) == 0 );
        BOOST_CHECK( point.Value( ) == expectedValue );
    }
}

// --run_test=VectorTests/VectorEmplaceFrontTest2
BOOST_AUTO_TEST_CASE( VectorEmplaceFrontTest2 )
{
    constexpr SSizeT ItemCount = 50;

    Vector<TimeseriesPoint> points;
    for ( SSizeT i = 0; i < ItemCount; ++i )
    {
        SSizeT value = i + 1;
        points.emplace_front( DateTime( value ), 0, static_cast<double>( value ) );
    }

    for ( SSizeT i = 0; i < ItemCount; ++i )
    {
        SSizeT value = ItemCount - i;

        DateTime expectedTimestamp( value );
        double expectedValue = static_cast<double>( value );
        auto& point = points[i];

        BOOST_CHECK( point.Timestamp( ) == expectedTimestamp );
        BOOST_CHECK( point.Flags( ) == 0 );
        BOOST_CHECK( point.Value( ) == expectedValue );
    }
}






// --run_test=VectorTests/VectorEmplaceFrontTest3
BOOST_AUTO_TEST_CASE( VectorEmplaceFrontTest3 )
{
    using Points = PointsContainer;
    constexpr SSizeT ItemCount = 50;

    Vector<Points> points;
    points.reserve( ItemCount );
    for ( SSizeT j = 0; j < ItemCount; ++j )
    {
        points.emplace_front( j, 10 );
        BOOST_CHECK( points.front( ).Id( ) == j );
    }
    for ( SSizeT j = 0; j < ItemCount; ++j )
    {
        auto& pts = points[j];
        auto id = pts.Id( );
        BOOST_CHECK( id == ItemCount - (j+1) );
    }
}

// --run_test=VectorTests/VectorEmplaceFrontTest4
BOOST_AUTO_TEST_CASE( VectorEmplaceFrontTest4 )
{
    using Points = PointsContainer;
    constexpr SSizeT ItemCount = 50;

    Vector<Points> points;
    for ( SSizeT j = 0; j < ItemCount; ++j )
    {
        points.emplace_front( j, 10 );
        BOOST_CHECK( points.front( ).Id( ) == j );
    }
    for ( SSizeT j = 0; j < ItemCount; ++j )
    {
        auto& pts = points[j];
        auto id = pts.Id( );
        BOOST_CHECK( id == ItemCount - ( j + 1 ) );
    }
}


// --run_test=VectorTests/VectorResizeTest1
BOOST_AUTO_TEST_CASE( VectorResizeTest1 )
{
    constexpr SSizeT ItemCount = 50;

    SSizeT value = 1;

    DateTime expectedTimestamp( value );
    double expectedValue = static_cast<double>( value );

    Vector<TimeseriesPoint> points;
    points.resize( ItemCount, TimeseriesPoint( DateTime( value ),0, static_cast<double>( value ) ) );

    SSizeT count = 0;

    for ( const auto& point : points )
    {
        BOOST_CHECK( point.Timestamp( ) == expectedTimestamp );
        BOOST_CHECK( point.Flags( ) == 0 );
        BOOST_CHECK( point.Value( ) == expectedValue );
        count++;
    }
    BOOST_CHECK( count == ItemCount );
}

// --run_test=VectorTests/VectorEraseTest1
BOOST_AUTO_TEST_CASE( VectorEraseTest1 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };
    
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    ++it;
    vector.erase( it );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 3 );
    BOOST_CHECK( vector[2].Id( ) == 4 );
    BOOST_CHECK( vector[3].Id( ) == 5 );
}

// --run_test=VectorTests/VectorEraseTest2
BOOST_AUTO_TEST_CASE( VectorEraseTest2 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    vector.erase( it );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Id( ) == 2 );
    BOOST_CHECK( vector[1].Id( ) == 3 );
    BOOST_CHECK( vector[2].Id( ) == 4 );
    BOOST_CHECK( vector[3].Id( ) == 5 );
}

// --run_test=VectorTests/VectorEraseTest3
BOOST_AUTO_TEST_CASE( VectorEraseTest3 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( ) - 1;
    vector.erase( it );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 2 );
    BOOST_CHECK( vector[2].Id( ) == 3 );
    BOOST_CHECK( vector[3].Id( ) == 4 );
}

// --run_test=VectorTests/VectorEraseTest4
BOOST_AUTO_TEST_CASE( VectorEraseTest4 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<TimeseriesPoint> vector
    {
        TimeseriesPoint( DateTime( 1LL ), 1.0 ),
        TimeseriesPoint( DateTime( 2LL ), 2.0 ),
        TimeseriesPoint( DateTime( 3LL ), 3.0 ),
        TimeseriesPoint( DateTime( 4LL ), 4.0 ),
        TimeseriesPoint( DateTime( 5LL ), 5.0 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    ++it;
    vector.erase( it );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Value( ) == 1.0 );
    BOOST_CHECK( vector[1].Value( ) == 3.0 );
    BOOST_CHECK( vector[2].Value( ) == 4.0 );
    BOOST_CHECK( vector[3].Value( ) == 5.0 );
}

// --run_test=VectorTests/VectorEraseTest5
BOOST_AUTO_TEST_CASE( VectorEraseTest5 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<TimeseriesPoint> vector
    {
        TimeseriesPoint( DateTime( 1LL ), 1.0 ),
        TimeseriesPoint( DateTime( 2LL ), 2.0 ),
        TimeseriesPoint( DateTime( 3LL ), 3.0 ),
        TimeseriesPoint( DateTime( 4LL ), 4.0 ),
        TimeseriesPoint( DateTime( 5LL ), 5.0 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    vector.erase( it );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Value( ) == 2.0 );
    BOOST_CHECK( vector[1].Value( ) == 3.0 );
    BOOST_CHECK( vector[2].Value( ) == 4.0 );
    BOOST_CHECK( vector[3].Value( ) == 5.0 );
}

// --run_test=VectorTests/VectorEraseTest6
BOOST_AUTO_TEST_CASE( VectorEraseTest6 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<TimeseriesPoint> vector
    {
        TimeseriesPoint( DateTime( 1LL ), 1.0 ),
        TimeseriesPoint( DateTime( 2LL ), 2.0 ),
        TimeseriesPoint( DateTime( 3LL ), 3.0 ),
        TimeseriesPoint( DateTime( 4LL ), 4.0 ),
        TimeseriesPoint( DateTime( 5LL ), 5.0 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( ) - 1;
    vector.erase( it );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Value( ) == 1.0 );
    BOOST_CHECK( vector[1].Value( ) == 2.0 );
    BOOST_CHECK( vector[2].Value( ) == 3.0 );
    BOOST_CHECK( vector[3].Value( ) == 4.0 );
}

// --run_test=VectorTests/VectorEraseTest7
BOOST_AUTO_TEST_CASE( VectorEraseTest7 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    ++it;
    auto itLast = it + 1;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 3 );
    BOOST_CHECK( vector[2].Id( ) == 4 );
    BOOST_CHECK( vector[3].Id( ) == 5 );
}

// --run_test=VectorTests/VectorEraseTest8
BOOST_AUTO_TEST_CASE( VectorEraseTest8 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    auto itLast = it + 1;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Id( ) == 2 );
    BOOST_CHECK( vector[1].Id( ) == 3 );
    BOOST_CHECK( vector[2].Id( ) == 4 );
    BOOST_CHECK( vector[3].Id( ) == 5 );
}

// --run_test=VectorTests/VectorEraseTest9
BOOST_AUTO_TEST_CASE( VectorEraseTest9 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( ) - 1;
    auto itLast = it + 1;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 4 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 2 );
    BOOST_CHECK( vector[2].Id( ) == 3 );
    BOOST_CHECK( vector[3].Id( ) == 4 );
}

// --run_test=VectorTests/VectorEraseTest10
BOOST_AUTO_TEST_CASE( VectorEraseTest10 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    ++it;
    auto itLast = it + 4;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 1 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
}

// --run_test=VectorTests/VectorEraseTest11
BOOST_AUTO_TEST_CASE( VectorEraseTest11 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    auto itLast = vector.end( );
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 0 );
}

// --run_test=VectorTests/VectorEraseTest12
BOOST_AUTO_TEST_CASE( VectorEraseTest12 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( ) + 1;
    auto itLast = vector.end( ) - 1;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 2 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 5 );
}

// --run_test=VectorTests/VectorEraseTest13
BOOST_AUTO_TEST_CASE( VectorEraseTest13 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( ) + 1;
    auto itLast = it;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 5 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 2 );
    BOOST_CHECK( vector[2].Id( ) == 3 );
    BOOST_CHECK( vector[3].Id( ) == 4 );
    BOOST_CHECK( vector[4].Id( ) == 5 );
}

// --run_test=VectorTests/VectorEraseTest14
BOOST_AUTO_TEST_CASE( VectorEraseTest14 )
{
    constexpr SSizeT ItemCount = 5;

    Vector<MoveableObject> vector
    {
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
    };

    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( );
    auto itLast = it;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 5 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 2 );
    BOOST_CHECK( vector[2].Id( ) == 3 );
    BOOST_CHECK( vector[3].Id( ) == 4 );
    BOOST_CHECK( vector[4].Id( ) == 5 );
}

// --run_test=VectorTests/VectorEraseTest15
BOOST_AUTO_TEST_CASE( VectorEraseTest15 )
{
    Vector<MoveableObject> vector;

    BOOST_CHECK( vector.size( ) == 0 );
    auto it = vector.end( );
    auto itLast = it;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 0 );
}

// --run_test=VectorTests/VectorEraseTest16
BOOST_AUTO_TEST_CASE( VectorEraseTest16 )
{
    Vector<MoveableObject> vector;

    BOOST_CHECK( vector.size( ) == 0 );
    auto it = vector.begin( );
    auto itLast = it;
    vector.erase( it, itLast );
    BOOST_CHECK( vector.size( ) == 0 );
}


// --run_test=VectorTests/VectorEmplaceTest1
BOOST_AUTO_TEST_CASE( VectorEmplaceTest1 )
{
    Vector<MoveableObject> vector;

    vector.emplace( vector.begin( ), 1 );

    BOOST_CHECK( vector.size( ) == 1 );
    BOOST_CHECK( vector[0].Id() == 1 );
}

// --run_test=VectorTests/VectorEmplaceTest2
BOOST_AUTO_TEST_CASE( VectorEmplaceTest2 )
{
    Vector<MoveableObject> vector;

    vector.emplace( vector.begin( ), 1 );
    vector.emplace( vector.begin( ) + 1, 2 );

    BOOST_CHECK( vector.size( ) == 2 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 2 );
}

// --run_test=VectorTests/VectorEmplaceTest3
BOOST_AUTO_TEST_CASE( VectorEmplaceTest3 )
{
    Vector<MoveableObject> vector;

    vector.emplace( vector.begin( ), 2 );
    vector.emplace( vector.begin( ), 1 );

    BOOST_CHECK( vector.size( ) == 2 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 2 );
}

// --run_test=VectorTests/VectorEmplaceTest4
BOOST_AUTO_TEST_CASE( VectorEmplaceTest4 )
{
    Vector<MoveableObject> vector;

    auto it = vector.begin( );
    vector.emplace( it, 3 );
    it = vector.begin( );
    vector.emplace( it, 1 );
    it = vector.begin( ) + 1;
    vector.emplace( it, 2 );

    BOOST_CHECK( vector.size( ) == 3 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 2 );
    BOOST_CHECK( vector[2].Id( ) == 3 );
}


// --run_test=VectorTests/VectorEmplaceTest5
BOOST_AUTO_TEST_CASE( VectorEmplaceTest5 )
{
    constexpr SSizeT FirstId = 2;
    constexpr SSizeT ItemCount = 16;
    Vector<MoveableObject> vector;
    for ( SSizeT i = 0; i < ItemCount; i++ )
    {
        auto itIns = vector.begin( );
        vector.emplace( itIns, ItemCount - i + FirstId - 1 );
    }
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    vector.emplace( it, 1 );
    BOOST_CHECK( vector.size( ) == ItemCount + 1 );
    BOOST_CHECK( vector.back( ).Id( ) == 17 );
    BOOST_CHECK( vector.front( ).Id( ) == 1 );
}

// --run_test=VectorTests/VectorEmplaceTest6
BOOST_AUTO_TEST_CASE( VectorEmplaceTest6 )
{
    constexpr SSizeT FirstId = 1;
    constexpr SSizeT ItemCount = 16;
    Vector<MoveableObject> vector;
    for ( SSizeT i = 0; i < ItemCount; i++ )
    {
        auto itIns = vector.begin( );
        vector.emplace( itIns, ItemCount - i + FirstId - 1 );
    }
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( );
    vector.emplace( it, 17 );
    BOOST_CHECK( vector.size( ) == ItemCount + 1 );
    BOOST_CHECK( vector.back( ).Id( ) == 17 );
    BOOST_CHECK( vector.front( ).Id( ) == 1 );
}

// --run_test=VectorTests/VectorEmplaceTest7
BOOST_AUTO_TEST_CASE( VectorEmplaceTest7 )
{
    constexpr SSizeT FirstId = 1;
    constexpr SSizeT ItemCount = 16;
    Vector<MoveableObject> vector;
    for ( SSizeT i = 0; i < ItemCount; i++ )
    {
        auto itIns = vector.begin( );
        vector.emplace( itIns, ItemCount - i + FirstId - 1 );
    }
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( ) - 1;
    vector.emplace( it, 17 );
    BOOST_CHECK( vector.size( ) == ItemCount + 1 );
    BOOST_CHECK( vector.back( ).Id( ) == 16 );
    BOOST_CHECK( (vector.end() - 2 )->Id( ) == 17 );
    BOOST_CHECK( vector.front( ).Id( ) == 1 );
}


// --run_test=VectorTests/VectorEmplaceTest8
BOOST_AUTO_TEST_CASE( VectorEmplaceTest8 )
{
    constexpr SSizeT FirstId = 1;
    constexpr SSizeT ItemCount = 16;
    Vector<MoveableObject> vector;
    for ( SSizeT i = 0; i < ItemCount; i++ )
    {
        auto itIns = vector.begin( );
        vector.emplace( itIns, ItemCount - i + FirstId - 1 );
    }
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( ) - 1;
    vector.emplace( it, 17 );
    BOOST_CHECK( vector.size( ) == ItemCount + 1 );
    BOOST_CHECK( vector.back( ).Id( ) == 16 );
    BOOST_CHECK( ( vector.end( ) - 2 )->Id( ) == 17 );
    BOOST_CHECK( vector.front( ).Id( ) == 1 );
}

// --run_test=VectorTests/VectorEmplaceTest9
BOOST_AUTO_TEST_CASE( VectorEmplaceTest9 )
{
    Vector<TimeseriesPoint> vector;

    vector.emplace( vector.begin( ), DateTime( 1LL ), static_cast<double>( 1 ) );

    BOOST_CHECK( vector.size( ) == 1 );
    BOOST_CHECK( vector[0].Value( ) == 1.0 );
}

// --run_test=VectorTests/VectorEmplaceTest10
BOOST_AUTO_TEST_CASE( VectorEmplaceTest10 )
{
    Vector<TimeseriesPoint> vector;

    vector.emplace( vector.begin( ), DateTime( 1LL ), static_cast<double>( 1 ) );
    vector.emplace( vector.begin( ) + 1, DateTime( 2LL ), static_cast<double>( 2 ) );

    BOOST_CHECK( vector.size( ) == 2 );
    BOOST_CHECK( vector[0].Value( ) == 1.0 );
    BOOST_CHECK( vector[1].Value( ) == 2.0 );
}

// --run_test=VectorTests/VectorEmplaceTest11
BOOST_AUTO_TEST_CASE( VectorEmplaceTest11 )
{
    Vector<TimeseriesPoint> vector;

    vector.emplace( vector.begin( ), DateTime( 2LL ), static_cast<double>( 2 ) );
    vector.emplace( vector.begin( ), DateTime( 1LL ), static_cast<double>( 1 ) );

    BOOST_CHECK( vector.size( ) == 2 );
    BOOST_CHECK( vector[0].Value( ) == 1.0 );
    BOOST_CHECK( vector[1].Value( ) == 2.0 );
}

// --run_test=VectorTests/VectorEmplaceTest12
BOOST_AUTO_TEST_CASE( VectorEmplaceTest12 )
{
    Vector<TimeseriesPoint> vector;

    auto it = vector.begin( );
    vector.emplace( it, DateTime( 3LL ), static_cast<double>( 3 ) );
    it = vector.begin( );
    vector.emplace( it, DateTime( 1LL ), static_cast<double>( 1 ) );
    it = vector.begin( ) + 1;
    vector.emplace( it, DateTime( 2LL ), static_cast<double>( 2 ) );

    BOOST_CHECK( vector.size( ) == 3 );
    BOOST_CHECK( vector[0].Value( ) == 1.0 );
    BOOST_CHECK( vector[1].Value( ) == 2.0 );
    BOOST_CHECK( vector[2].Value( ) == 3.0 );
}


// --run_test=VectorTests/VectorEmplaceTest13
BOOST_AUTO_TEST_CASE( VectorEmplaceTest13 )
{
    constexpr SSizeT FirstId = 2;
    constexpr SSizeT ItemCount = 16;
    Vector<TimeseriesPoint> vector;
    for ( SSizeT i = 0; i < ItemCount; i++ )
    {
        auto itIns = vector.begin( );
        auto val = ItemCount - i + FirstId - 1;
        vector.emplace( itIns, DateTime( val ), static_cast<double>( val ) );
    }
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.begin( );
    vector.emplace( it, DateTime( 1LL ), static_cast<double>( 1 ) );
    BOOST_CHECK( vector.size( ) == ItemCount + 1 );
    BOOST_CHECK( vector.back( ).Value( ) == 17.0 );
    BOOST_CHECK( vector.front( ).Value( ) == 1.0 );
}

// --run_test=VectorTests/VectorEmplaceTest14
BOOST_AUTO_TEST_CASE( VectorEmplaceTest14 )
{
    constexpr SSizeT FirstId = 1;
    constexpr SSizeT ItemCount = 16;
    Vector<TimeseriesPoint> vector;
    for ( SSizeT i = 0; i < ItemCount; i++ )
    {
        auto itIns = vector.begin( );
        auto val = ItemCount - i + FirstId - 1;
        vector.emplace( itIns, DateTime( val ), static_cast<double>( val ) );
    }
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( );
    vector.emplace( it, DateTime( 17LL ), static_cast<double>( 17 ) );
    BOOST_CHECK( vector.size( ) == ItemCount + 1 );
    BOOST_CHECK( vector.back( ).Value( ) == 17.0 );
    BOOST_CHECK( vector.front( ).Value( ) == 1.0 );
}

// --run_test=VectorTests/VectorEmplaceTest15
BOOST_AUTO_TEST_CASE( VectorEmplaceTest15 )
{
    constexpr SSizeT FirstId = 1;
    constexpr SSizeT ItemCount = 16;
    Vector<TimeseriesPoint> vector;
    for ( SSizeT i = 0; i < ItemCount; i++ )
    {
        auto itIns = vector.begin( );
        auto val = ItemCount - i + FirstId - 1;
        vector.emplace( itIns, DateTime( val ), static_cast<double>( val ) );
    }
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( ) - 1;
    vector.emplace( it, DateTime( 17LL ), static_cast<double>( 17 ) );
    BOOST_CHECK( vector.size( ) == ItemCount + 1 );
    BOOST_CHECK( vector.back( ).Value( ) == 16.0 );
    BOOST_CHECK( ( vector.end( ) - 2 )->Value( ) == 17.0 );
    BOOST_CHECK( vector.front( ).Value( ) == 1.0 );
}


// --run_test=VectorTests/VectorEmplaceTest16
BOOST_AUTO_TEST_CASE( VectorEmplaceTest16 )
{
    constexpr SSizeT FirstId = 1;
    constexpr SSizeT ItemCount = 16;
    Vector<TimeseriesPoint> vector;
    for ( SSizeT i = 0; i < ItemCount; i++ )
    {
        auto itIns = vector.begin( );
        auto val = ItemCount - i + FirstId - 1;
        vector.emplace( itIns, DateTime( val ), static_cast<double>( val ) );
    }
    BOOST_CHECK( vector.size( ) == ItemCount );
    auto it = vector.end( ) - 1;
    vector.emplace( it, DateTime( 17LL ), static_cast<double>( 17 ) );
    BOOST_CHECK( vector.size( ) == ItemCount + 1 );
    BOOST_CHECK( vector.back( ).Value( ) == 16.0 );
    BOOST_CHECK( ( vector.end( ) - 2 )->Value( ) == 17.0 );
    BOOST_CHECK( vector.front( ).Value( ) == 1.0 );
}

// --run_test=VectorTests/VectorMoveToFrontTest1
BOOST_AUTO_TEST_CASE( VectorMoveToFrontTest1 )
{
    Vector vector{0,1,2,3,4,5,6,7,8,9};
    auto srcIt = vector.begin( ) + 9;
    vector.MoveToFront( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0] == 9 );
    BOOST_CHECK( vector[1] == 0 );
    BOOST_CHECK( vector[9] == 8 );
}

// --run_test=VectorTests/VectorMoveToFrontTest2
BOOST_AUTO_TEST_CASE( VectorMoveToFrontTest2 )
{
    Vector vector
    { 
        MoveableObject( 0 ),
        MoveableObject( 1 ), 
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
        MoveableObject( 6 ),
        MoveableObject( 7 ),
        MoveableObject( 8 ),
        MoveableObject( 9 )
    };
    auto srcIt = vector.begin( ) + 9;
    vector.MoveToFront( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0].Id( ) == 9 );
    BOOST_CHECK( vector[1].Id( ) == 0 );
    BOOST_CHECK( vector[9].Id( ) == 8 );
}

// --run_test=VectorTests/VectorMoveToFrontTest3
BOOST_AUTO_TEST_CASE( VectorMoveToFrontTest3 )
{
    Vector vector{ 0,1,2,3,4,5,6,7,8,9 };
    auto srcIt = vector.begin( );
    vector.MoveToFront( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0] == 0 );
    BOOST_CHECK( vector[1] == 1 );
    BOOST_CHECK( vector[9] == 9 );
}

// --run_test=VectorTests/VectorMoveToFrontTest4
BOOST_AUTO_TEST_CASE( VectorMoveToFrontTest4 )
{
    Vector vector
    {
        MoveableObject( 0 ),
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
        MoveableObject( 6 ),
        MoveableObject( 7 ),
        MoveableObject( 8 ),
        MoveableObject( 9 )
    };
    auto srcIt = vector.begin( );
    vector.MoveToFront( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0].Id( ) == 0 );
    BOOST_CHECK( vector[1].Id( ) == 1 );
    BOOST_CHECK( vector[9].Id( ) == 9 );
}

// --run_test=VectorTests/VectorMoveToFrontTest5
BOOST_AUTO_TEST_CASE( VectorMoveToFrontTest5 )
{
    Vector vector{ 0,1,2,3,4,5,6,7,8,9 };
    auto srcIt = vector.begin( ) + 1;
    vector.MoveToFront( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0] == 1 );
    BOOST_CHECK( vector[1] == 0 );
    BOOST_CHECK( vector[2] == 2 );
    BOOST_CHECK( vector[9] == 9 );
}

// --run_test=VectorTests/VectorMoveToFrontTest6
BOOST_AUTO_TEST_CASE( VectorMoveToFrontTest6 )
{
    Vector vector
    {
        MoveableObject( 0 ),
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
        MoveableObject( 6 ),
        MoveableObject( 7 ),
        MoveableObject( 8 ),
        MoveableObject( 9 )
    };
    auto srcIt = vector.begin( ) + 1;
    vector.MoveToFront( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 0 );
    BOOST_CHECK( vector[2].Id( ) == 2 );
    BOOST_CHECK( vector[9].Id( ) == 9 );
}

// --run_test=VectorTests/VectorMoveToFrontTest7
BOOST_AUTO_TEST_CASE( VectorMoveToFrontTest7 )
{
    Vector vector{ 0,1,2,3,4,5,6,7,8,9 };
    auto srcIt = vector.begin( ) + 2;
    vector.MoveToFront( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0] == 2 );
    BOOST_CHECK( vector[1] == 0 );
    BOOST_CHECK( vector[2] == 1 );
    BOOST_CHECK( vector[3] == 3 );
    BOOST_CHECK( vector[9] == 9 );
}

// --run_test=VectorTests/VectorMoveToFrontTest8
BOOST_AUTO_TEST_CASE( VectorMoveToFrontTest8 )
{
    Vector vector
    {
        MoveableObject( 0 ),
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
        MoveableObject( 6 ),
        MoveableObject( 7 ),
        MoveableObject( 8 ),
        MoveableObject( 9 )
    };
    auto srcIt = vector.begin( ) + 2;
    vector.MoveToFront( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0].Id( ) == 2 );
    BOOST_CHECK( vector[1].Id( ) == 0 );
    BOOST_CHECK( vector[2].Id( ) == 1 );
    BOOST_CHECK( vector[3].Id( ) == 3 );
    BOOST_CHECK( vector[9].Id( ) == 9 );
}

// --run_test=VectorTests/VectorMoveToBackTest1
BOOST_AUTO_TEST_CASE( VectorMoveToBackTest1 )
{
    Vector vector{ 0,1,2,3,4,5,6,7,8,9 };
    auto srcIt = vector.begin( );
    vector.MoveToBack( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0] == 1 );
    BOOST_CHECK( vector[1] == 2 );
    BOOST_CHECK( vector[8] == 9 );
    BOOST_CHECK( vector[9] == 0 );
}


// --run_test=VectorTests/VectorMoveToBackTest2
BOOST_AUTO_TEST_CASE( VectorMoveToBackTest2 )
{
    Vector vector
    {
        MoveableObject( 0 ),
        MoveableObject( 1 ),
        MoveableObject( 2 ),
        MoveableObject( 3 ),
        MoveableObject( 4 ),
        MoveableObject( 5 ),
        MoveableObject( 6 ),
        MoveableObject( 7 ),
        MoveableObject( 8 ),
        MoveableObject( 9 )
    };
    auto srcIt = vector.begin( );
    vector.MoveToBack( srcIt );
    BOOST_CHECK( vector.size( ) == 10 );
    BOOST_CHECK( vector[0].Id( ) == 1 );
    BOOST_CHECK( vector[1].Id( ) == 2 );
    BOOST_CHECK( vector[8].Id( ) == 9 );
    BOOST_CHECK( vector[9].Id( ) == 0 );
}

// --run_test=VectorTests/VectorFindTest1
BOOST_AUTO_TEST_CASE( VectorFindTest1 )
{
    Vector vector{ 0,1,2,3,4,5,6,7,8,9 };
    
    auto foundIt = vector.find( 0 );
    BOOST_CHECK( foundIt != vector.end( ) );
    BOOST_CHECK( (*foundIt) == 0 );

    foundIt = vector.find( 1 );
    BOOST_CHECK( foundIt != vector.end( ) );
    BOOST_CHECK( ( *foundIt ) == 1 );

    foundIt = vector.find( 9 );
    BOOST_CHECK( foundIt != vector.end( ) );
    BOOST_CHECK( ( *foundIt ) == 9 );

    foundIt = vector.find( 11 );
    BOOST_CHECK( foundIt == vector.end( ) );
}

// --run_test=VectorTests/VectorFindTest2
BOOST_AUTO_TEST_CASE( VectorFindTest2 )
{
    Vector<int> vector;

    auto foundIt = vector.find( 0 );
    BOOST_CHECK( foundIt == vector.end( ) );
}



// --run_test=VectorTests/VectorReverseFindTest1
BOOST_AUTO_TEST_CASE( VectorReverseFindTest1 )
{
    Vector vector{ 0,1,2,3,4,5,6,7,8,9 };

    auto foundIt = vector.reverse_find( 0 );
    BOOST_CHECK( foundIt != vector.end( ) );
    BOOST_CHECK( ( *foundIt ) == 0 );

    foundIt = vector.reverse_find( 1 );
    BOOST_CHECK( foundIt != vector.end( ) );
    BOOST_CHECK( ( *foundIt ) == 1 );

    foundIt = vector.reverse_find( 9 );
    BOOST_CHECK( foundIt != vector.end( ) );
    BOOST_CHECK( ( *foundIt ) == 9 );

    foundIt = vector.reverse_find( 11 );
    BOOST_CHECK( foundIt == vector.end( ) );
}

// --run_test=VectorTests/VectorReverseFindTest2
BOOST_AUTO_TEST_CASE( VectorReverseFindTest2 )
{
    Vector vector{ 0,1,2,3,4,5,6,7,8,9 };
    auto lastIt = vector.end( ) - 1;

    auto foundIt = vector.reverse_find( 0, lastIt );
    BOOST_CHECK( foundIt != vector.end( ) );
    BOOST_CHECK( ( *foundIt ) == 0 );

    foundIt = vector.reverse_find( 1, lastIt );
    BOOST_CHECK( foundIt != vector.end( ) );
    BOOST_CHECK( ( *foundIt ) == 1 );

    foundIt = vector.reverse_find( 9, lastIt );
    BOOST_CHECK( foundIt == vector.end( ) );

    foundIt = vector.reverse_find( 11, lastIt );
    BOOST_CHECK( foundIt == vector.end( ) );
}

// --run_test=VectorTests/VectorReverseFindTest3
BOOST_AUTO_TEST_CASE( VectorReverseFindTest3 )
{
    Vector<int> vector;

    auto foundIt = vector.reverse_find( 0 );
    BOOST_CHECK( foundIt == vector.end( ) );
}





BOOST_AUTO_TEST_SUITE_END( )


