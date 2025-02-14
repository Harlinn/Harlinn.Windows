/*
   Copyright 2024-2025 Espen Harlinn

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


#include <HExTypes.h>
#include <HExDatabase.h>
#include <HExEngine.h>
#include <HExOptionParser.h>
#include <HCCApplication.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Examples;

#ifdef _DEBUG
DateTime IntervalStart( 2020, 1, 1 );
DateTime IntervalEnd( 2020, 2, 1 );
#else
DateTime IntervalStart( 2020, 1, 1 );
DateTime IntervalEnd( 2020, 2, 1 );
#endif

#ifdef _DEBUG
TimeSpan IntervalStep = TimeSpan::FromDays( 1 );
#else
TimeSpan IntervalStep = TimeSpan::FromMinutes( 1 );
#endif

size_t IntervalStepCount = static_cast< size_t >( ( IntervalEnd - IntervalStart ).Ticks( ) / IntervalStep.Ticks( ) );

class Engine;
class Session : public SessionT<Engine>
{
public:
    using Base = SessionT<Engine>;
public:
    Session( Engine& engine, Int64 id, bool createDatabase )
        : Base( engine, id, createDatabase )
    {
    }
};

class Engine : public EngineT<Engine,Session>
{
public:
    using Base = EngineT<Engine, Session>;
public:
    Engine( const EngineOptions& options, const char* instanceName )
        : Base( options, instanceName )
    {
    }
};



std::string GetSensorName( size_t value )
{
    return std::format( "S{:08x}", value );
}

std::string GetCatalogName( size_t value )
{
    return std::format( "C{:08x}", value );
}

std::string GetAssetName( size_t value )
{
    return std::format( "A{:08x}", value );
}


enum class OperationType
{
    Create,
    Retrieve,
    Update,
    Delete
};

template<typename F, typename ...Args>
void PerformanceOf( const wchar_t* functionName, OperationType operationType,F testFunction, Args&&... args )
{
    using Seconds = std::chrono::duration<double, std::chrono::seconds::period>;
    size_t testResult = 0;
    auto start = std::chrono::high_resolution_clock::now( );
    try
    {
        testResult = testFunction( std::forward<Args>( args )... );
    }
    catch ( std::exception& exc )
    {
        WideString message = WideString::From( exc.what( ) );
        PrintLn( L"Exception while executing {}: {}", functionName, message );
        return;
    }
    auto end = std::chrono::high_resolution_clock::now( );
    auto testDuration = Seconds( end - start );
    switch ( operationType )
    {
        case OperationType::Create:
            PrintLn( L"Executed {}: inserted {} rows in {} seconds - {} rows per second", functionName, testResult, testDuration.count( ), testResult / testDuration.count( ) );
            break;
        case OperationType::Retrieve:
            PrintLn( L"Executed {}: read {} rows in {} seconds - {} rows per second", functionName, testResult, testDuration.count( ), testResult / testDuration.count( ) );
            break;
        case OperationType::Delete:
            PrintLn( L"Executed {} in {} seconds\n", functionName, testDuration.count( ) );
            break;
    }
}

size_t AddCatalogs( Session& session, const Guid& ownerCatalogId, size_t count, std::vector<Catalog>& result )
{
    auto transaction = session.StartTransaction( );
    for ( size_t i = 0; i < count; ++i )
    {
        auto catalogName = GetCatalogName( i + 1 );
        auto catalog = session.CreateOrRetrieveCatalog( ownerCatalogId, catalogName );
        result.emplace_back( catalog );
    }
    transaction.Commit( );
    return count;
}

size_t AddAssets( Session& session, const Guid& ownerCatalogId, size_t count, std::vector<Asset>& result )
{
    Guid ownerId;
    auto transaction = session.StartTransaction( );
    for ( size_t i = 0; i < count; ++i )
    {
        auto assetName = GetAssetName( i + 1 );
        auto asset = session.CreateOrRetrieveAsset( ownerId, assetName );
        result.emplace_back( asset );
    }
    transaction.Commit( );
    return count;
}




size_t AddSensors( Session& session, const Guid& assetId, size_t count, std::vector<Examples::Sensor>& sensors )
{
    Examples::Sensor sensor;
    auto transaction = session.StartTransaction( );
    for ( size_t i = 0; i < count; ++i )
    {
        auto sensorName = GetSensorName( i + 1 );
        sensor.Id = Guid( );
        session.CreateOrRetrieveSensor( assetId, sensorName, sensor );
        sensors.emplace_back( sensor );
    }
    transaction.Commit( );
    return count;
}

size_t BuildStructure( Session& session, 
    size_t numberOfCatalogs, 
    size_t numberOfAssetsPerCatalog, 
    size_t numberOfSensorsPerAsset )
{
    Guid empty;
    size_t result = 0;
    auto transaction = session.StartTransaction( );
    for ( size_t i = 0; i < numberOfCatalogs; i++ )
    {
        auto catalogName = GetCatalogName( i + 1 );
        auto catalog = session.CreateOrRetrieveCatalog( empty, catalogName );
        result++;
        for ( size_t j = 0; j < numberOfAssetsPerCatalog; j++ )
        {
            auto assetName = GetAssetName( j + 1 );
            auto asset = session.CreateOrRetrieveAsset( catalog.Id, assetName );
            result++;
            for ( size_t k = 0; k < numberOfSensorsPerAsset; k++ )
            {
                auto sensorName = GetSensorName( k + 1 );
                Examples::Sensor sensor = session.CreateOrRetrieveSensor( asset.Id, sensorName );
                result++;
            }
        }
    }
    transaction.Commit( );
    return result;
}


struct AssetData : Asset
{
    std::vector<Examples::Sensor> Sensors;
    void Assign( const Asset& asset )
    {
        Id = asset.Id;
        Owner = asset.Owner;
        Name = asset.Name;
    }
};


struct CatalogData : Catalog
{
    std::vector<AssetData> Assets;
    void Assign( const Catalog& catalog )
    {
        Id = catalog.Id;
        Owner = catalog.Owner;
        Name = catalog.Name;
    }
};


size_t ReadStructure( Session& session, std::vector<CatalogData>& result )
{
    size_t count = 0;
    Guid root;
    std::vector<CatalogItem> catalogItems;
    session.GetCatalogItems( root, catalogItems );
    count += catalogItems.size( );
    for ( auto& catalogItem : catalogItems )
    {
        auto& catalog = std::get<Catalog>( catalogItem );
        CatalogData& catalogData = result.emplace_back();
        catalogData.Assign(catalog);
        std::vector<CatalogItem> assets;
        session.GetCatalogItems( catalogData.Id, assets );
        count += assets.size( );
        for ( auto& assetItem : assets )
        {
            auto& asset = std::get<Asset>( assetItem );
            AssetData& assetData = catalogData.Assets.emplace_back();
            assetData.Assign( asset );
            session.GetSensors( assetData.Id, assetData.Sensors );
            count += assetData.Sensors.size( );
        }
    }
    return count;
}


size_t ReadSensors( Session& session, std::vector<Examples::Sensor>& sensors )
{
    session.GetSensors( sensors );
    return sensors.size( );
}

size_t GenerateDataForSensor( Session& session,
    const Examples::Sensor& sensor,
    const DateTime& start,
    const DateTime& end,
    const TimeSpan& step )
{
    size_t result = 0;
    auto transaction = session.StartTransaction( );
    SensorValue sensorValue{ sensor.Id,start,0,0.0 };
    DateTime current = start;
    while ( current < end )
    {
        double value = static_cast<double>(current.Ticks( ));
        sensorValue.Timestamp = current;
        sensorValue.Value = value;
        session.Write( sensorValue );
        current += step;
        result++;
    }
    transaction.Commit( );
    return result;
}


size_t GenerateSensorData( Session& session, std::vector<Examples::Sensor>& sensors )
{
    size_t result = 0;
    DateTime start = IntervalStart;
    DateTime end = IntervalEnd;
#ifdef _DEBUG
    TimeSpan step = TimeSpan::FromDays( 1 );
#else
    TimeSpan step = TimeSpan::FromMinutes( 1 );
#endif
    for ( auto& sensor : sensors )
    {
        result += GenerateDataForSensor( session, sensor, start, end, step );
    }
    return result;
}

size_t ReadAllSensorData( Session& session, std::vector<Examples::Sensor>& sensors )
{
    size_t result = 0;
    std::vector<SensorPoint> points;
    points.reserve( IntervalStepCount );
    for ( auto& sensor : sensors )
    {
        session.GetSensorPoints( sensor.Id, points );
        result += points.size( );
    }
    return result;
}

size_t ReadAllSensorData2( Session& session )
{
    SensorPoint sensorPoint;
    const auto& values = session.Values( );
    values.SetSequential( );
    size_t result = 0;

    if ( values.MoveFirst( ) )
    {
        do
        {
            values.Read( sensorPoint );
            result++;
        } while ( values.MoveNext( ) );
    }
    return result;
}


size_t ReadAllSensorData3( Session& session )
{
    SensorPoint sensorPoint;
    const auto& values = session.Values( );
    values.SetSequential( );
    size_t result = 0;

    if ( values.MoveFirst( ) )
    {
        do
        {
            values.Read2( sensorPoint );
            result++;
        } while ( values.MoveNext( ) );
    }
    return result;
}



size_t ReadSensorDataForInterval( Session& session, std::vector<Examples::Sensor>& sensors )
{
    DateTime start( 2020, 1, 10 );
    DateTime end( 2020, 1, 25 );
    size_t result = 0;
    std::vector<SensorPoint> points;
    points.reserve( IntervalStepCount );
    for ( auto& sensor : sensors )
    {
        session.GetSensorPoints( sensor.Id, start, end, points );
        result += points.size( );
    }
    return result;
}

size_t ReadSensorDataForIntervalWithCheck( Session& session, std::vector<Examples::Sensor>& sensors )
{
    DateTime start( 2020, 1, 10 );
    DateTime end( 2020, 1, 25 );
    size_t result = 0;
    std::vector<SensorValue> points;
    points.reserve( IntervalStepCount );
    for ( auto& sensor : sensors )
    {
        session.GetSensorValues( sensor.Id, start, end, points );
        result += points.size( );
        if ( points.size( ) )
        {
            if ( points.front( ).Timestamp < start )
            {
                printf( "First point earlier than requested interval\n" );
            }
            if ( points.back( ).Timestamp >= end )
            {
                printf( "Last point later than requested interval\n" );
            }
            auto previousTimestamp = points.front( ).Timestamp - TimeSpan::FromMinutes( 1 );
            for ( const auto& point : points )
            {
                if ( point.Sensor != sensor.Id )
                {
                    printf( "Point from another timeseries\n" );
                }
                if ( previousTimestamp >= point.Timestamp )
                {
                    printf("Points not in expected order\n" );
                }
                previousTimestamp = point.Timestamp;
            }
        }
        else
        {
            printf( "No data\n" );
        }
    }
    return result;
}


size_t DeleteSensorDataForInterval( Session& session, std::vector<Examples::Sensor>& sensors )
{
    DateTime start( 2020, 1, 10 );
    DateTime end( 2020, 1, 25 );
    
    for ( auto& sensor : sensors )
    {
        session.DeleteValues( sensor.Id, start, end );
    }
    return 0;
}


size_t DeleteSensors( Session& session, std::vector<Examples::Sensor>& sensors )
{
    for ( auto& sensor : sensors )
    {
        session.DeleteSensor( sensor.Id );
    }
    return 0;
}

size_t DeleteCatalog( Session& session, const Guid& catalogId )
{
    auto transaction = session.StartTransaction( );
    session.DeleteCatalogItem( catalogId );
    transaction.Commit( );
    return 1;
}

size_t GetSensorCount( Session& session )
{
    return session.GetSensorCount( );
}

size_t GetCatalogItemCount( Session& session )
{
    return session.GetCatalogItemCount( );
}

size_t GetSensorValueCount( Session& session )
{
    return session.GetSensorValueCount( );
}


void RunTests( Session& session )
{
    size_t result = 0;
    std::vector<Examples::Sensor> sensors;
    std::vector<CatalogData> catalogs;
#ifdef _DEBUG
    PerformanceOf( L"BuildStructure", OperationType::Create, BuildStructure, session, 10, 10, 10 );
#else
    PerformanceOf( L"BuildStructure", OperationType::Create, BuildStructure, session, 10, 10, 10 );
#endif
    PerformanceOf( L"ReadStructure", OperationType::Retrieve, ReadStructure, session, catalogs );
    
    PerformanceOf( L"ReadSensors", OperationType::Retrieve, ReadSensors, session, sensors );
    PerformanceOf( L"GenerateSensorData", OperationType::Create, GenerateSensorData, session, sensors );

    PerformanceOf( L"GetCatalogItemCount", OperationType::Retrieve, GetCatalogItemCount, session );
    PerformanceOf( L"GetSensorCount", OperationType::Retrieve, GetSensorCount, session );
    PerformanceOf( L"GetSensorValueCount", OperationType::Retrieve, GetSensorValueCount, session );

    PerformanceOf( L"ReadAllSensorData", OperationType::Retrieve, ReadAllSensorData, session, sensors );
    PerformanceOf( L"ReadAllSensorData2", OperationType::Retrieve, ReadAllSensorData2, session );
    PerformanceOf( L"ReadAllSensorData3", OperationType::Retrieve, ReadAllSensorData3, session );
    PerformanceOf( L"ReadSensorDataForInterval", OperationType::Retrieve, ReadSensorDataForInterval, session, sensors );
    PerformanceOf( L"ReadSensorDataForIntervalWithCheck", OperationType::Retrieve, ReadSensorDataForIntervalWithCheck, session, sensors );

#ifdef _DEBUG
    PerformanceOf( L"DeleteCatalog", OperationType::Delete, DeleteCatalog, session, catalogs.front().Id );

    PerformanceOf( L"GetCatalogItemCount", OperationType::Retrieve, GetCatalogItemCount, session );
    PerformanceOf( L"GetSensorCount", OperationType::Retrieve, GetSensorCount, session );
    PerformanceOf( L"GetSensorValueCount", OperationType::Retrieve, GetSensorValueCount, session );
#endif
    
    //PerformanceOf( L"DeleteSensorDataForInterval", OperationType::Delete, DeleteSensorDataForInterval, session, sensors );
    PerformanceOf( L"ReadAllSensorData", OperationType::Retrieve, ReadAllSensorData, session, sensors );
    //PerformanceOf( L"DeleteSensors", OperationType::Delete, DeleteSensors, session, sensors );
    PerformanceOf( L"ReadSensors", OperationType::Retrieve, ReadSensors, session, sensors );
    
}

/*

Executed BuildStructure: inserted 1110 rows in 0.141570 seconds - 7840.649743 rows per second
Executed ReadStructure: read 1110 rows in 0.017056 seconds - 65078.592661 rows per second
Executed ReadSensors: read 1000 rows in 0.001043 seconds - 958313.368471 rows per second
Executed GenerateSensorData: inserted 44640000 rows in 494.297817 seconds - 90309.927503 rows per second
Executed GetCatalogItemCount: read 110 rows in 0.011975 seconds - 9185.880467 rows per second
Executed GetSensorCount: read 1000 rows in 0.014779 seconds - 67662.203217 rows per second
Executed GetSensorValueCount: read 44640000 rows in 169.681985 seconds - 263080.374024 rows per second
Executed ReadAllSensorData: read 44640000 rows in 248.202096 seconds - 179853.437072 rows per second
Executed ReadSensorDataForInterval: read 21600000 rows in 119.960240 seconds - 180059.660518 rows per second
Executed ReadSensorDataForIntervalWithCheck: read 21600000 rows in 120.187719 seconds - 179718.861442 rows per second

*/


int main( int argc, char* argv[] )
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    auto application= std::make_shared<Application>( options );
    application->Start( );
    try
    {
        EngineOptions options;
        if ( ParseOptions( argc, argv, options ) )
        {
            Engine engine( options, "TestInstance" );
            auto session = engine.CreateSession( );

            if ( options.RunTests )
            {
                RunTests( *session );
            }
            session->Close( );
        }
    }
    catch ( std::exception& exc )
    {
        AnsiString message( exc.what( ) );
        printf( "Exception: %s", message.c_str( ) );
    }
    application->Stop( );
    return 0;
}

