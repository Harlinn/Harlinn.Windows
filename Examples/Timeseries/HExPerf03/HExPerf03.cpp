#include <HCCEnvironment.h>
#include <HCCIO.h>
#include <HCCGuid.h>
#include <HTEngine.h>
#include <HCCApplication.h>

using namespace Harlinn;
using namespace Harlinn::Common::Core;

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



int main( )
{
    ApplicationOptions applicationOptions;
    applicationOptions.Load( );
    Application application( applicationOptions );
    application.Start( );

#ifdef _DEBUG
    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 6>;
    constexpr size_t NumberOfPoints = 30;
    constexpr size_t BatchSize = 5;

#else
    constexpr size_t NumberOfPoints = 100'000;
    constexpr size_t BatchSize = 250;
    using Engine = Timeseries::TimeseriesEngine;
#endif
    constexpr size_t BatchCount = NumberOfPoints / BatchSize;
    constexpr size_t TimeseriesCount = 10'000;

    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );
    printf( "Database directory:%s\n", DatabaseDir.c_str( ) );

    Guid timeseriesId1 = Test::Ids[0];
    std::vector<Guid> timeseriesIds;
    for ( size_t i = 0; i < TimeseriesCount; ++i )
    {
        timeseriesIds.push_back( Test::Ids[i] );
    }

    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );

    auto timeseriesCursor1 = transaction.OpenTimeseries( timeseriesId1 );

    double sumWritten = 0;
    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( size_t i = 0; i < BatchCount; ++i )
    {
        for ( auto& timeseriesId : timeseriesIds )
        {
            timeseriesCursor1.ChangeTimeseries( timeseriesId );
            for ( size_t j = 0; j < BatchSize; ++j )
            {
                Int64 value = static_cast<Int64>( ( i * BatchSize ) + j ) + 1;
                sumWritten += static_cast<double>( value );
                timeseriesCursor1.Insert( Point( DateTime( value ), 0, static_cast<double>( value ) ) );
            }
        }
    }

    timeseriesCursor1.Close( );
    transaction.Commit( );
    stopwatch.Stop( );

    auto totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    auto totalPoints = timeseriesIds.size( ) * NumberOfPoints;
    auto pointsPrSeconds = static_cast<double>( totalPoints ) / totalSeconds;
    printf( "Inserted %zu timeseries points into %zu timeseries in %f seconds\n\t - points pr. second: %f\n", totalPoints, TimeseriesCount, totalSeconds, pointsPrSeconds );

    double sumRead = 0;
    stopwatch.Restart( );

    transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );

    auto timeseriesCursor2 = transaction.OpenTimeseries( timeseriesId1 );


    size_t totalRows = 0;
    for ( auto& timeseriesId : timeseriesIds )
    {
        timeseriesCursor2.ChangeTimeseries( timeseriesId );
        
        totalRows += timeseriesCursor2.ForEach( []( const Point& point, double& sumRead )
        {
            auto ticks = point.Timestamp( ).Ticks( );
            sumRead += ticks;
        }, sumRead );
    }



    timeseriesCursor2.Close( );
    transaction.Close( );

    totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    pointsPrSeconds = static_cast<double>( totalRows ) / totalSeconds;
    printf( "Read  %llu timeseries points from %zu timeseries in %f seconds\n\t - points pr. second: %f\n", totalRows, TimeseriesCount, totalSeconds, pointsPrSeconds );
    printf( "Sum inserted:%f,\n"
            "Sum read:    %f\n", sumWritten, sumRead );


    application.Stop( );
}

