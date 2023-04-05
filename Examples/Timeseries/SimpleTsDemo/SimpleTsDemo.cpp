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

int main()
{
    ApplicationOptions applicationOptions;
    applicationOptions.Load( );
    Application application( applicationOptions );
    application.Start( );

    using Engine = Timeseries::Engine<>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;
    DateTime timestamp1( 2020, 1, 1 ), timestamp2( 2020, 1, 2 ),
        timestamp3( 2020, 1, 3 ), timestamp4( 2020, 1, 4 );

    auto DatabaseDir = GetDatabaseDir( );
    printf( "Database directory:%s\n", DatabaseDir.c_str( ) );
    Timeseries::TimeseriesEngineOptions options( DatabaseDir, true );
    auto timeseriesId1 = Test::Ids[0];

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );
    auto timeseriesCursor = transaction.OpenTimeseries( timeseriesId1 );

    timeseriesCursor.Insert( timestamp1, 1 );
    timeseriesCursor.Insert( timestamp2, 2 );
    timeseriesCursor.Insert( timestamp3, 3 );
    timeseriesCursor.Insert( timestamp4, 4 );

    if ( timeseriesCursor.MoveFirst( ) )
    {
        do
        {
            auto& current = timeseriesCursor.Current( );
            std::cout << "Timestamp: " << current.Timestamp( ) 
                << ", Flags: " << current.Flags( ) 
                << ", Value: " << current.Value( ) << std::endl;
        } while ( timeseriesCursor.MoveNext( ) );
    }
    DateTime timestamp( 2020, 1, 2, 12, 0, 0 );
    auto found = timeseriesCursor.Search( timestamp );
    if ( found )
    {
        auto& current = timeseriesCursor.Current( );
        std::cout << "Found Timestamp: " << current.Timestamp( )
            << ", Flags: " << current.Flags( )
            << ", Value: " << current.Value( ) << std::endl;
    }


    timeseriesCursor.Close( );
    transaction.Commit( );

    application.Stop( );
}
