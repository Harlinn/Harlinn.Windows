#include <HCCArray.h>
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


template<size_t N>
class ArrayPoints
{
    SSizeT id_;
    Array<TimeseriesPoint,N> values_;
public:
    ArrayPoints( SSizeT id )
        : id_( id )
    {
        for ( size_t i = 0; i < N; ++i )
        {
            SSizeT value = ( i + 1 );
            values_[i] = TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    constexpr SSizeT Id( ) const noexcept
    {
        return id_;
    }

};

template<size_t N>
class StdArrayPoints
{
    SSizeT id_;
    std::array<TimeseriesPoint, N> values_;
public:
    StdArrayPoints( SSizeT id )
        : id_( id )
    {
        for ( size_t i = 0; i < N; ++i )
        {
            SSizeT value = ( i + 1 );
            values_[i] = TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) );
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
    constexpr CopyableObject( ) noexcept
        : id_( 0 )
    {
    }

    constexpr explicit CopyableObject( Int64 id ) noexcept
        : id_( id )
    {
    }



    constexpr CopyableObject( const CopyableObject& other ) noexcept
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


void ArrayAssignTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "Assigns trivially copyable TimeseriesPoint: %lld iterations, creates a TimeseriesPoint and assigns it using operator[](...) %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Array<TimeseriesPoint, ItemCount> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points[j] = TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tArray: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::array<TimeseriesPoint, ItemCount> points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points[j] = TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::array: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        TimeseriesPoint points[ItemCount];
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            points[j] = TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) );
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tc style array: %f seconds.\n\n", duration );


}


void ArrayAssignTest1b( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "Assigns trivially copyable TimeseriesPoint: %lld iterations, creates a TimeseriesPoint and assigns it using an iterator %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Array<TimeseriesPoint, ItemCount> points;
        auto it = points.begin( );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            *it = TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) );
            ++it;
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tArray: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::array<TimeseriesPoint, ItemCount> points;
        auto it = points.begin( );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            *it = TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) );
            ++it;
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::array: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        TimeseriesPoint points[ItemCount];
        auto* it = points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            SSizeT value = ( i * ItemCount ) + ( j + 1 );
            *it = TimeseriesPoint( DateTime( value ), 0, static_cast<double>( value ) );
            ++it;
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tc style array: %f seconds.\n\n", duration );
}

void ArrayAssignTest1c( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "Assigns a byte: %lld iterations, using an iterator %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Array<Byte, ItemCount> points;
        auto it = points.begin( );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            Byte value = static_cast<Byte>( i % ItemCount ) + static_cast<Byte>( __rdtsc( ) + j );
            *it = value;
            ++it;
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tArray: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::array<Byte, ItemCount> points;
        auto it = points.begin( );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            Byte value = static_cast<Byte>( i % ItemCount ) + static_cast<Byte>( __rdtsc( ) + j );
            *it = value;
            ++it;
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::array: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Byte points[ItemCount];
        auto* it = points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            Byte value = static_cast<Byte>( i % ItemCount ) + static_cast<Byte>( __rdtsc( ) + j );
            *it = value;
            ++it;
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tc style array: %f seconds.\n\n", duration );
}

void ArrayAssignTest1d( )
{
    printf( "%s\n", __FUNCTION__ );
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;

    printf( "Assigns a byte: %lld iterations, using an iterator %lld times per iteration\n", InterationCount, ItemCount );

    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Array<Byte, ItemCount> points;
        auto it = points.begin( );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            Byte value = static_cast<Byte>( i % ItemCount ) + static_cast<Byte>( i + j );
            *it = value;
            ++it;
        }
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tArray: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::array<Byte, ItemCount> points;
        auto it = points.begin( );
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            Byte value = static_cast<Byte>( i % ItemCount ) + static_cast<Byte>( i + j );
            *it = value;
            ++it;
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::array: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Byte points[ItemCount];
        auto* it = points;
        for ( SSizeT j = 0; j < ItemCount; ++j )
        {
            Byte value = static_cast<Byte>( i % ItemCount ) + static_cast<Byte>( i + j );
            *it = value;
            ++it;
        }
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tc style array: %f seconds.\n\n", duration );
}




void ArrayCopyTest1a( )
{
    printf( "%s\n", __FUNCTION__ );
#ifdef _DEBUG
    constexpr SSizeT InterationCount = 1;
    constexpr SSizeT ItemCount = 5;
#else
    constexpr SSizeT InterationCount = 100000000;
    constexpr SSizeT ItemCount = 50;
#endif
    printf( "Copies a byte array: %lld iterations, array size %lld\n", InterationCount, ItemCount );

    Array<Byte, ItemCount> source_1;
    for ( SSizeT j = 0; j < ItemCount; ++j )
    {
        Byte value = static_cast<Byte>( __rdtsc( ) + j );
        source_1[j] = value;
    }

    std::array<Byte, ItemCount> source_2;
    for ( SSizeT j = 0; j < ItemCount; ++j )
    {
        Byte value = static_cast<Byte>( __rdtsc( ) + j );
        source_2[j] = value;
    }
    Byte source_3[ItemCount];
    for ( SSizeT j = 0; j < ItemCount; ++j )
    {
        Byte value = static_cast<Byte>( __rdtsc( ) + j );
        source_3[j] = value;
    }


    Stopwatch stopwatch;
    stopwatch.Start( );


    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Array<Byte, ItemCount> points;
        std::copy( source_1.begin( ), source_1.end( ), points.begin( ) );
    }

    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    printf( "\tArray: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        std::array<Byte, ItemCount> points;
        std::copy( source_2.begin( ), source_2.end( ), points.begin( ) );
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tstd::array: %f seconds.\n", duration );

    stopwatch.Reset( );
    stopwatch.Start( );

    for ( SSizeT i = 0; i < InterationCount; ++i )
    {
        Byte points[ItemCount];
        std::copy( source_3, source_3 + ItemCount, points );
    }


    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );

    printf( "\tc style array: %f seconds.\n\n", duration );
}



int main()
{
    ApplicationOptions options;
    options.Load( );
    Application application( options );
    application.Start( );

    //ArrayAssignTest1a( );
    //ArrayAssignTest1b( );
    //ArrayAssignTest1c( );
    //ArrayAssignTest1d( );
    //ArrayCopyTest1a( );

    /*
    auto dtStart = DateTime::UtcNow( );
    auto tscStart = __rdtsc( );

    Sleep( 3 * 1000 );

    auto dtStop = DateTime::UtcNow( );
    auto tscStop = __rdtsc( );

    auto duration = dtStop - dtStart;

    auto frequency = static_cast<double>( tscStop - tscStart ) / duration.TotalSeconds( );
    auto frequency2 = static_cast<double>( 2712 ) * 1000.0 * 1000.0033444;
    printf( "TSC frequency: %f (%f)\n", frequency, frequency2 );
    */
    application.Stop( );

}
