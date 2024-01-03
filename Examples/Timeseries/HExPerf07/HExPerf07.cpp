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

struct TimeseriesData
{
    Guid id;
    std::vector<Timeseries::TimeseriesPoint> points;
};


template<typename EngineT>
double InsertData( EngineT& engine, const std::vector<TimeseriesData>& timeseriesDataContainer )
{
    double result = 0;

    if ( timeseriesDataContainer.size( ) )
    {
        auto transaction = engine.BeginTransaction( );
        for ( const TimeseriesData& timeseriesData : timeseriesDataContainer )
        {
            const auto& timeseriesId = timeseriesData.id;
            const auto& points = timeseriesData.points;
            auto timeseriesCursor = transaction.OpenTimeseries( timeseriesId );

            for ( const auto& point : points )
            {
                timeseriesCursor.Insert( point );
            }
            timeseriesCursor.Close( );
        }
        transaction.Commit( );
    }
    return result;
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
    using Engine = Timeseries::Engine<>;
    constexpr size_t TimeseriesCount = 1'000;
#endif


    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;

    auto DatabaseDir = GetDatabaseDir( );
    printf( "Database directory:%s\n", DatabaseDir.c_str( ) );

    Guid timeseriesId1 = Test::Ids[0];

    std::vector<TimeseriesData> timeseriesDataContainer;

    for ( size_t i = 0; i < TimeseriesCount; ++i )
    {
        auto& timeseriesId = Test::Ids[i];
        auto& timeseriesData = timeseriesDataContainer.emplace_back( );
        timeseriesData.id = timeseriesId;
        auto& points = timeseriesData.points;
        points.reserve( NumberOfPoints );
        for ( size_t i = 0; i < NumberOfPoints; ++i )
        {
            Int64 value = static_cast<Int64>( i + 1 );
            auto& point = points.emplace_back( );
            point.SetTimesetamp( DateTime( value ) );
            point.SetValue( static_cast<double>( value ) );
        }
    }

    Timeseries::TimeseriesEngineOptions options;
    options.DatabaseDirectory = DatabaseDir;
    options.Create = true;

    Engine engine( options );

    Stopwatch stopwatch;
    stopwatch.Start( );
    InsertData( engine, timeseriesDataContainer );
    stopwatch.Stop( );
    

    auto totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    auto totalPoints = timeseriesDataContainer.size( ) * NumberOfPoints;
    auto pointsPrSeconds = static_cast<double>( totalPoints ) / totalSeconds;
    printf( "Inserted %llu timeseries points into %zu timeseries in %f seconds\n\t - points pr. second: %f\n", totalPoints, TimeseriesCount, totalSeconds, pointsPrSeconds );


    timeseriesDataContainer.clear( );

    for ( size_t i = 0; i < TimeseriesCount; ++i )
    {
        auto& timeseriesId = Test::Ids[i];
        auto& timeseriesData = timeseriesDataContainer.emplace_back( );
        timeseriesData.id = timeseriesId;
        auto& points = timeseriesData.points;
        points.reserve( NumberOfPoints );
        for ( size_t i = 0; i < NumberOfPoints; ++i )
        {
            Int64 value = static_cast<Int64>( i + NumberOfPoints + 1 );
            auto& point = points.emplace_back( );
            point.SetTimesetamp( DateTime( value ) );
            point.SetValue( static_cast<double>( value ) );
        }
    }


    stopwatch.Reset( );
    stopwatch.Start( );
    InsertData( engine, timeseriesDataContainer );
    stopwatch.Stop( );


    totalSeconds = stopwatch.Elapsed( ).TotalSeconds( );
    totalPoints = timeseriesDataContainer.size( ) * NumberOfPoints;
    pointsPrSeconds = static_cast<double>( totalPoints ) / totalSeconds;
    printf( "Inserted %llu timeseries points into %zu timeseries in %f seconds\n\t - points pr. second: %f\n", totalPoints, TimeseriesCount, totalSeconds, pointsPrSeconds );

    application->Stop( );


}

