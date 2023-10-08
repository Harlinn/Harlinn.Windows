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
    using Engine = Timeseries::Engine<Timeseries::TimeseriesPoint, 6>;
    constexpr size_t NumberOfPoints = 30;
    constexpr size_t BatchSize = 5;

#else
    constexpr size_t NumberOfPoints = 250'000'000;
    constexpr size_t BatchSize = 1000;
    using Engine = Timeseries::TimeseriesEngine;
#endif
    constexpr size_t BatchCount = NumberOfPoints / BatchSize;

    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );
    printf( "Database directory:%s\n", DatabaseDir.c_str( ) );

    Guid timeseriesId1( L"{9B3DD446-C19A-4D19-8993-DFE8FC10992A}" );
    Guid timeseriesId2( L"{9C8871E8-66E7-4974-8E13-707D69F7C44D}" );
    Guid timeseriesId3( L"{53242803-808A-4C66-9382-B02FB1B1ECF0}" );
    Guid timeseriesId4( L"{9BEE8BBC-F44B-46F5-A5A9-92FAA1D7361B}" );

    std::array timeseriesIds = { timeseriesId1,timeseriesId2,timeseriesId3,timeseriesId4 };


    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );

    auto timeseriesCursor1 = transaction.OpenTimeseries( timeseriesId1 );

    Int64 sumWritten = 0;
    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( size_t i = 0; i < BatchCount; ++i )
    {
        for ( auto& timeseriesId : timeseriesIds )
        {
            timeseriesCursor1.ChangeTimeseries( timeseriesId );
            for ( size_t j = 0; j < BatchSize; ++j )
            {
                Int64 value = static_cast<Int64>(( i * BatchSize ) + j) + 1;
                sumWritten += value;
                timeseriesCursor1.Insert( DateTime( value ), 0, static_cast<double>( value ) );
            }
        }
    }

    timeseriesCursor1.Close( );
    transaction.Commit( );
    stopwatch.Stop( );

    auto totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    auto totalPoints = timeseriesIds.size( ) * NumberOfPoints;
    auto pointsPrSeconds = static_cast<double>( totalPoints ) / totalSeconds;
    printf( "Wrote %llu timeseries points in %f seconds - points pr. second: %f\n", totalPoints, totalSeconds, pointsPrSeconds );


    Int64 sumRead = 0;
    stopwatch.Restart( );

    transaction = engine.BeginTransaction( LMDB::TransactionFlags::ReadOnly );
    

    auto timeseriesCursor2 = transaction.OpenTimeseries( timeseriesId1 );

    
    size_t totalRows = 0;
    for ( auto& timeseriesId : timeseriesIds )
    {
        timeseriesCursor2.ChangeTimeseries( timeseriesId );
        timeseriesCursor2.MoveFirst( );
        size_t rows = 0;
        do
        {
            rows++;
            auto& current = timeseriesCursor2.Current( );
            auto ticks = current.Timestamp( ).Ticks( );
            auto value = current.Value( );
            if ( static_cast<size_t>( ticks ) != rows || static_cast<double>( ticks ) != current.Value( ) )
            {
                printf( "Unexpected: Row: %zu, Ticks: %lld, Flags: %llu, Value: %f\n", 
                    rows, ticks, current.Flags( ), value );
                break;
            }
            sumRead += ticks;
        } while ( timeseriesCursor2.MoveNext( ) );
        totalRows += rows;

    }



    timeseriesCursor2.Close( );
    transaction.Close( );

    totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    pointsPrSeconds = static_cast<double>( totalRows ) / totalSeconds;
    printf( "Read  %zu timeseries points in %f seconds - points pr. second: %f\n", totalRows, totalSeconds, pointsPrSeconds );
    printf( "Sum inserted:%lld,\n"
            "Sum read:    %lld\n", sumWritten, sumRead );

    application->Stop( );

}

