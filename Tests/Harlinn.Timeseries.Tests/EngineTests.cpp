#include <HCCEnvironment.h>
#include <HCCIO.h>
#include <HCCGuid.h>
#include <HTEngine.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn;
using namespace Harlinn::Common::Core;

namespace
{
    std::string GetDatabaseDir( )
    {
        std::string TestDataRoot = Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
        auto directoryPath = IO::Path::Append( TestDataRoot, "\\LMDB" );

        if ( IO::Directory::Exist( directoryPath ) == false )
        {
            IO::Directory::Create( directoryPath );
        }
        return directoryPath;
    }

    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };


    template<typename T>
    void Generate( T& timeseriesCursor, Int64 numberOfPoints, Int64 start, Int64 step, Int64 offset )
    {
        for ( Int64 i = 0; i < numberOfPoints; ++i )
        {
            Int64 value = start + i * step;
            timeseriesCursor.Insert( DateTime( value ), static_cast<double>( value + offset ) );
        }
    }

    template<typename T>
    void Generate( T& engine, Int64 numberOfTimeseries, Int64 numberOfPoints, Int64 start, Int64 step, Int64 offset )
    {
        Guid timeseriesId1 = Test::Ids[0];
        auto transaction = engine.BeginTransaction( );
        auto timeseriesCursor = transaction.OpenTimeseries( timeseriesId1 );

        for ( Int64 i = 0; i < numberOfTimeseries; ++i )
        {
            auto timeseriesId = Test::Ids[i];
            timeseriesCursor.ChangeTimeseries( timeseriesId );
            Generate( timeseriesCursor, numberOfPoints, start, step, i * offset );
        }
        timeseriesCursor.Close( );
        transaction.Commit( );
    }

}

BOOST_FIXTURE_TEST_SUITE( TsEngineTests, LocalFixture )


// --run_test=TsEngineTests/ReadWriteTest3
BOOST_AUTO_TEST_CASE( ReadWriteTest3 )
{
    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 3>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );
    auto timeseriesId = Test::Ids[0];

    std::vector<Point> points1, points2, points3;
    for ( size_t i = 0; i < 10; i++ )
    {
        auto v = static_cast<Int64>( ( i + 1 ) * 3 );
        DateTime timestamp1( v );
        double value = static_cast<double>( v );
        points1.emplace_back( Point( timestamp1, 0, value ) );

        v++;
        DateTime timestamp2( v );
        value = static_cast<double>( v );
        points2.emplace_back( Point( timestamp2, 0, value ) );

        v++;
        DateTime timestamp3( v );
        value = static_cast<double>( v );
        points3.emplace_back( Point( timestamp3, 0, value ) );

    }
    std::reverse( points1.begin( ), points1.end( ) );


    double sumWritten = 0.0;
    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );

    auto timeseriesCursor1 = transaction.OpenTimeseries( timeseriesId );

    for ( auto& point : points1 )
    {
        sumWritten += point.Value( );
        timeseriesCursor1.Insert( point );
    }

    for ( auto& point : points2 )
    {
        sumWritten += point.Value( );
        timeseriesCursor1.Insert( point );
    }

    for ( size_t i = 0; i < points3.size( ) / 2; ++i )
    {
        const auto& point1 = points3[i];
        const auto& point2 = points3[( points3.size( ) - 1 ) - i];

        sumWritten += point1.Value( );
        timeseriesCursor1.Insert( point1 );

        sumWritten += point2.Value( );
        timeseriesCursor1.Insert( point2 );
    }


    timeseriesCursor1.Flush( );
    timeseriesCursor1.Dump( );

    timeseriesCursor1.Close( );
    transaction.Commit( );

    double sumRead = 0.0;

    transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    auto timeseriesCursor2 = transaction.OpenTimeseries( timeseriesId );

    auto found = timeseriesCursor2.MoveFirst( );
    BOOST_CHECK( found );
    size_t rows = 0;
    do
    {
        auto& current = timeseriesCursor2.Current( );
        auto ticks = current.Timestamp( ).Ticks( );
        auto value = current.Value( );
        sumRead += value;

    } while ( timeseriesCursor2.MoveNext( ) );

    BOOST_CHECK( sumRead == sumWritten );

    timeseriesCursor2.Close( );
    transaction.Close( );
}

// --run_test=TsEngineTests/ReadWriteTest4
BOOST_AUTO_TEST_CASE( ReadWriteTest4 )
{
    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 3>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );
    auto timeseriesId1 = Test::Ids[0];
    auto timeseriesId2 = Test::Ids[1];

    std::vector<Point> points1, points2, points3;
    for ( size_t i = 0; i < 10; i++ )
    {
        auto v = static_cast<Int64>( ( i + 1 ) * 3 );
        DateTime timestamp1( v );
        double value = static_cast<double>( v );
        points1.emplace_back( Point( timestamp1, 0, value ) );

        v++;
        DateTime timestamp2( v );
        value = static_cast<double>( v );
        points2.emplace_back( Point( timestamp2, 0, value ) );

        v++;
        DateTime timestamp3( v );
        value = static_cast<double>( v );
        points3.emplace_back( Point( timestamp3, 0, value ) );

    }
    std::reverse( points1.begin( ), points1.end( ) );


    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );
    auto timeseriesCursor1 = transaction.OpenTimeseries( timeseriesId1 );

    double sumWritten = 0.0;

    for ( auto& point : points1 )
    {
        timeseriesCursor1.ChangeTimeseries( timeseriesId1 );
        sumWritten += point.Value( );
        timeseriesCursor1.Insert( point );
        timeseriesCursor1.ChangeTimeseries( timeseriesId2 );
        sumWritten += point.Value( );
        timeseriesCursor1.Insert( point );
    }


    for ( auto& point : points2 )
    {
        timeseriesCursor1.ChangeTimeseries( timeseriesId1 );
        sumWritten += point.Value( );
        timeseriesCursor1.Insert( point );
        timeseriesCursor1.ChangeTimeseries( timeseriesId2 );
        sumWritten += point.Value( );
        timeseriesCursor1.Insert( point );
    }


    for ( size_t i = 0; i < points3.size( ) / 2; ++i )
    {
        const auto& point1 = points3[i];
        const auto& point2 = points3[( points3.size( ) - 1 ) - i];

        timeseriesCursor1.ChangeTimeseries( timeseriesId1 );
        sumWritten += point1.Value( );
        timeseriesCursor1.Insert( point1 );
        timeseriesCursor1.ChangeTimeseries( timeseriesId2 );
        sumWritten += point1.Value( );
        timeseriesCursor1.Insert( point1 );

        timeseriesCursor1.ChangeTimeseries( timeseriesId1 );
        sumWritten += point2.Value( );
        timeseriesCursor1.Insert( point2 );
        timeseriesCursor1.ChangeTimeseries( timeseriesId2 );
        sumWritten += point2.Value( );
        timeseriesCursor1.Insert( point2 );
    }


    timeseriesCursor1.ChangeTimeseries( timeseriesId1 );
    timeseriesCursor1.Dump( );
    double sumRead = 0.0;
    BOOST_CHECK( timeseriesCursor1.MoveFirst( ) );
    do
    {
        const auto& current = timeseriesCursor1.Current( );
        sumRead += current.Value( );
    } while ( timeseriesCursor1.MoveNext( ) );
    timeseriesCursor1.ChangeTimeseries( timeseriesId2 );
    timeseriesCursor1.Dump( );
    BOOST_CHECK( timeseriesCursor1.MoveFirst( ) );
    do
    {
        const auto& current = timeseriesCursor1.Current( );
        sumRead += current.Value( );
    } while ( timeseriesCursor1.MoveNext( ) );

    BOOST_CHECK( sumRead == sumWritten );

    timeseriesCursor1.Close( );
    transaction.Commit( );




    transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    auto timeseriesCursor2 = transaction.OpenTimeseries( timeseriesId1 );
    timeseriesCursor2.Dump( );
    timeseriesCursor2.ChangeTimeseries( timeseriesId2 );
    timeseriesCursor2.Dump( );

    timeseriesCursor2.Close( );
    transaction.Close( );

}




// --run_test=TsEngineTests/SearchTest1
BOOST_AUTO_TEST_CASE( SearchTest1 )
{
    constexpr Int64 NumberOfPoints = 30;
    constexpr Int64 Step = 30;
    constexpr DateTime lastTimestamp( ( NumberOfPoints - 1 ) * Step );
    constexpr DateTime beyondLastTimestamp( (NumberOfPoints)*Step );
    constexpr DateTime middleTimestamp( ( NumberOfPoints / 2 ) * Step );
    constexpr DateTime middlePlusOneTimestamp( ( ( NumberOfPoints / 2 ) * Step ) + 1 );

    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 3>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );

    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    auto timeseriesId1 = Test::Ids[0];
    auto timeseriesId2 = Test::Ids[1];

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );
    auto timeseriesCursor1 = transaction.OpenTimeseries( timeseriesId1 );

    for ( Int64 i = 0; i < NumberOfPoints; ++i )
    {
        Int64 value = i * Step;
        timeseriesCursor1.Insert( DateTime( value ), static_cast<double>( value ) );
    }

    auto searchResult = timeseriesCursor1.Search( beyondLastTimestamp );
    BOOST_CHECK( searchResult.IsLess( ) );

    searchResult = timeseriesCursor1.Search( lastTimestamp );
    BOOST_CHECK( searchResult.IsEqual( ) );

    searchResult = timeseriesCursor1.Search( middlePlusOneTimestamp );
    BOOST_CHECK( searchResult.IsLess( ) );
    auto& current = timeseriesCursor1.Current( );
    BOOST_CHECK( current.Timestamp( ) == middleTimestamp );

    for ( Int64 i = 0; i < NumberOfPoints; ++i )
    {
        Int64 value = i * Step;
        DateTime timestamp( value );
        searchResult = timeseriesCursor1.Search( timestamp );
        BOOST_CHECK( searchResult.IsEqual( ) );
        if ( searchResult.IsEqual( ) == false )
        {
            printf( "Error no equal\n" );
        }
        for ( Int64 j = 1; j < Step; ++j )
        {
            DateTime timestamp2( value + j );
            searchResult = timeseriesCursor1.Search( timestamp2 );
            if ( searchResult.IsLess( ) == false )
            {
                printf( "Error not less\n" );
            }

            BOOST_CHECK( searchResult.IsLess( ) );
            auto& curr = timeseriesCursor1.Current( );
            BOOST_CHECK( curr.Timestamp( ) == timestamp );
        }
    }


}


// --run_test=TsEngineTests/CursorTest1
BOOST_AUTO_TEST_CASE( CursorTest1 )
{
    constexpr Int64 NumberOfTimeseries = 3;
    constexpr Int64 NumberOfPoints = 10;
    constexpr Int64 Start = 10;
    constexpr Int64 Step = 10;

    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 3>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );

    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Guid timeseriesId1 = Test::Ids[0];

    Engine engine( options );
    Generate( engine, NumberOfTimeseries, NumberOfPoints, Start, Step, 1 );

    auto transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    auto timeseriesCursor = transaction.OpenTimeseries( timeseriesId1 );

    for ( Int64 i = 0; i < NumberOfTimeseries; ++i )
    {
        auto timeseriesId = Test::Ids[i];
        timeseriesCursor.ChangeTimeseries( timeseriesId );
        if ( timeseriesCursor.MoveLast( ) )
        {
            do
            {
                const Point& currentPoint = timeseriesCursor.Current( );
            } while ( timeseriesCursor.MovePrevious( ) );
        }
    }

}

// --run_test=TsEngineTests/CursorTest2
BOOST_AUTO_TEST_CASE( CursorTest2 )
{
    constexpr Int64 NumberOfTimeseries = 3;
    constexpr Int64 NumberOfPoints = 10;
    constexpr Int64 Start = 10;
    constexpr Int64 Step = 10;

    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 3>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );

    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Guid timeseriesId1 = Test::Ids[0];

    Engine engine( options );
    Generate( engine, NumberOfTimeseries, NumberOfPoints, Start, Step, 1 );

    auto transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    auto timeseriesCursor = transaction.OpenTimeseries( timeseriesId1 );

    for ( Int64 i = 0; i < NumberOfTimeseries; ++i )
    {
        auto timeseriesId = Test::Ids[i];
        timeseriesCursor.ChangeTimeseries( timeseriesId );
        if ( timeseriesCursor.MoveFirst( ) )
        {
            do
            {
                const Point& currentPoint = timeseriesCursor.Current( );
            } while ( timeseriesCursor.MoveNext( ) );
        }
    }

}


// --run_test=TsEngineTests/SearchTest2
BOOST_AUTO_TEST_CASE( SearchTest2 )
{
    constexpr Int64 NumberOfTimeseries = 3;
    constexpr Int64 NumberOfPoints = 10;
    constexpr Int64 Start = 10;
    constexpr Int64 Step = 10;
    constexpr Int64 Offset = 1;

    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 3>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );

    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Guid timeseriesId1 = Test::Ids[0];

    Engine engine( options );
    Generate( engine, NumberOfTimeseries, NumberOfPoints, Start, Step, Offset );

    auto transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    auto timeseriesCursor = transaction.OpenTimeseries( timeseriesId1 );

    for ( Int64 i = 0; i < NumberOfTimeseries; ++i )
    {
        auto timeseriesId = Test::Ids[i];
        timeseriesCursor.ChangeTimeseries( timeseriesId );

        auto searchResult = timeseriesCursor.Search( DateTime( 0LL ) );
        BOOST_CHECK( searchResult.IsGreater( ) );
        for ( Int64 j = 0; j < NumberOfPoints; ++j )
        {
            DateTime expectedTimestamp( Start + ( j * Step ) );
            double expectedValue = static_cast<double>( Start + ( j * Step ) + ( i * Offset ) );
            searchResult = timeseriesCursor.Search( DateTime( expectedTimestamp ) );
            BOOST_CHECK( searchResult.IsEqual( ) );
            const Point& currentPoint1 = timeseriesCursor.Current( );
            BOOST_CHECK( currentPoint1.Value( ) == expectedValue );
            searchResult = timeseriesCursor.Search( DateTime( expectedTimestamp + TimeSpan( 1 ) ) );
            BOOST_CHECK( searchResult.IsLess( ) );
            const Point& currentPoint2 = timeseriesCursor.Current( );
            BOOST_CHECK( currentPoint2.Value( ) == expectedValue );
        }
    }
}


// --run_test=TsEngineTests/SearchTest3
BOOST_AUTO_TEST_CASE( SearchTest3 )
{
    constexpr Int64 NumberOfTimeseries = 3;
    constexpr Int64 NumberOfPoints = 10;
    constexpr Int64 Start = 10;
    constexpr Int64 Step = 10;
    constexpr Int64 Offset = 1;

    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 3>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );

    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Guid timeseriesId1 = Test::Ids[0];

    Engine engine( options );
    Generate( engine, NumberOfTimeseries, NumberOfPoints, Start, Step, Offset );

    auto transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    auto timeseriesCursor = transaction.OpenTimeseries( timeseriesId1 );

    for ( Int64 i = 0; i < NumberOfTimeseries; ++i )
    {
        auto timeseriesId = Test::Ids[i];
        timeseriesCursor.ChangeTimeseries( timeseriesId );

        auto searchResult = timeseriesCursor.Search( DateTime( 0LL ) );
        BOOST_CHECK( searchResult.IsGreater( ) );
        for ( Int64 j = 0; j < NumberOfPoints; ++j )
        {
            DateTime expectedTimestamp1( Start + ( j * Step ) );
            double expectedValue1 = static_cast<double>( Start + ( j * Step ) + ( i * Offset ) );
            searchResult = timeseriesCursor.Search( DateTime( expectedTimestamp1 ) );
            BOOST_CHECK( searchResult.IsEqual( ) );
            const Point& currentPoint1 = timeseriesCursor.Current( );
            BOOST_CHECK( currentPoint1.Value( ) == expectedValue1 );
            searchResult = timeseriesCursor.Search( DateTime( expectedTimestamp1 + TimeSpan( 1 ) ) );
            BOOST_CHECK( searchResult.IsLess( ) );
            const Point& currentPoint2 = timeseriesCursor.Current( );
            BOOST_CHECK( currentPoint2.Value( ) == expectedValue1 );
            if ( timeseriesCursor.MoveNext( ) )
            {
                DateTime expectedTimestamp2( Start + ( ( j + 1 ) * Step ) );
                double expectedValue2 = static_cast<double>( Start + ( ( j + 1 ) * Step ) + ( i * Offset ) );
                const Point& currentPoint3 = timeseriesCursor.Current( );
                BOOST_CHECK( currentPoint3.Timestamp( ) == expectedTimestamp2 );
                BOOST_CHECK( currentPoint3.Value( ) == expectedValue2 );
                BOOST_CHECK( timeseriesCursor.MovePrevious( ) );
                const Point& currentPoint4 = timeseriesCursor.Current( );
                BOOST_CHECK( currentPoint4.Timestamp( ) == expectedTimestamp1 );
                BOOST_CHECK( currentPoint4.Value( ) == expectedValue1 );
                if ( timeseriesCursor.MovePrevious( ) )
                {
                    DateTime expectedTimestamp3( Start + ( ( j - 1 ) * Step ) );
                    double expectedValue3 = static_cast<double>( Start + ( ( j - 1 ) * Step ) + ( i * Offset ) );
                    const Point& currentPoint5 = timeseriesCursor.Current( );
                    BOOST_CHECK( currentPoint5.Timestamp( ) == expectedTimestamp3 );
                    BOOST_CHECK( currentPoint5.Value( ) == expectedValue3 );
                }
                else
                {
                    BOOST_CHECK( j == 0 );
                }

            }
            else
            {
                BOOST_CHECK( j == ( NumberOfPoints - 1 ) );
            }
        }
    }
}


BOOST_AUTO_TEST_SUITE_END( )
