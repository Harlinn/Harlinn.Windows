#include <HCCEnvironment.h>
#include <HCCIO.h>
#include <HCCGuid.h>
#include <HTEngine.h>
#include <HCCApplication.h>

using namespace Harlinn;
using namespace Harlinn::Common::Core;

AnsiString GetDatabaseDir( )
{
    auto TestDataRoot = Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
    auto directoryPath = IO::Path::Combine( TestDataRoot, "\\LMDB" );

    if ( IO::Directory::Exist( directoryPath ) == false )
    {
        IO::Directory::Create( directoryPath );
    }
    return directoryPath;
}


int main()
{
    ApplicationOptions applicationOptions;
    applicationOptions.Load( );
    Application application( applicationOptions );
    application.Start( );

    using Engine = Timeseries::TimeseriesEngine;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );
    printf( "Database directory:%s\n", DatabaseDir.c_str( ) );

    Guid timeseriesId( L"{9B3DD446-C19A-4D19-8993-DFE8FC10992A}" );
    constexpr size_t NumberOfPoints = 1'000'000'000;

    Timeseries::TimeseriesEngineOptions options( DatabaseDir, true );

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );

    auto timeseriesCursor1 = transaction.OpenTimeseries( timeseriesId );

    double sumWritten = 0;
    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( size_t i = 0; i < NumberOfPoints; ++i )
    {
        Int64 value = static_cast<Int64>( i + 1 );
        sumWritten += static_cast<double>( value );
        timeseriesCursor1.Insert( DateTime( value ), 0, static_cast<double>( value ) );
    }

    timeseriesCursor1.Close( );
    transaction.Commit( );
    stopwatch.Stop( );

    auto totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    auto pointsPrSeconds = static_cast<double>( NumberOfPoints ) / totalSeconds;
    printf( "Wrote %llu timeseries points in %f seconds - points pr. second: %f\n", NumberOfPoints, totalSeconds, pointsPrSeconds );


    //size_t sumRead = 0;
    double sumRead = 0;
    stopwatch.Restart( );

    transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );

    auto timeseriesCursor2 = transaction.OpenTimeseries( timeseriesId );
    auto rows = timeseriesCursor2.ForEach( [](const Point& point, double& sumRead ) 
    {
        sumRead += point.Value();
    }, sumRead );

    timeseriesCursor2.Close( );
    transaction.Close( );

    totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    pointsPrSeconds = static_cast<double>( rows ) / totalSeconds;
    printf( "Read  %llu timeseries points in %f seconds - points pr. second: %f\n", rows, totalSeconds, pointsPrSeconds );
    printf( "Sum inserted:%f,\n"
        "Sum read:    %f\n", sumWritten, sumRead );
    application.Stop( );

        
}

