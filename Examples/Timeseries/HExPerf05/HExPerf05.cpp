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



int main( )
{
    auto applicationOptions = std::make_shared<ApplicationOptions>( );
    applicationOptions->Load( );
    auto application = std::make_shared<Application>( applicationOptions );
    application->Start( );
#ifdef _DEBUG
    constexpr size_t NumberOfPoints = 30;
    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 6>;
    constexpr size_t TimeseriesCount = 4;
#else
    constexpr size_t NumberOfPoints = 100'000;
    //using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint,83>;
    using Engine = Timeseries::Engine<>;
    constexpr size_t TimeseriesCount = 10'000;
#endif


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

    Timeseries::TimeseriesEngineOptions options( DatabaseDir, false );

    Engine engine( options );

    double sumRead = 0;

    Stopwatch stopwatch;
    stopwatch.Start( );

    auto transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    auto timeseriesCursor2 = transaction.OpenTimeseries( timeseriesId1 );

    size_t totalRows = 0;
    for ( auto& timeseriesId : timeseriesIds )
    {
        timeseriesCursor2.ChangeTimeseries( timeseriesId );

        totalRows += timeseriesCursor2.ForEach( []( const Point& point, double& sumRead )
        {
            sumRead += point.Value();
        }, sumRead );
    }
    
    transaction.Close( );
    stopwatch.Stop( );

    auto totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    auto pointsPrSeconds = static_cast<double>( totalRows ) / totalSeconds;
    printf( "Read  %llu timeseries points from %zu timeseries in %f seconds\n\t - points pr. second: %f\n", totalRows, TimeseriesCount, totalSeconds, pointsPrSeconds );
    printf( "Sum read:    %f\n", sumRead );

    application->Stop( );

}

