#include <HExTypes.h>
#include <HExDatabase.h>
#include <HExEngine.h>
#include <HExOptionParser.h>
#include <HCCApplication.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Examples;

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
    return Format( "S%08x", value );
}

std::string GetCatalogName( size_t value )
{
    return Format( "C%08x", value );
}

std::string GetAssetName( size_t value )
{
    return Format( "A%08x", value );
}


enum class OperationType
{
    Create,
    Retrieve,
    Update,
    Delete
};

template<typename F, typename ...Args>
void PerformanceOf( const char* functionName, OperationType operationType,F testFunction, Args&&... args )
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
        std::string message = exc.what( );
        printf("Exception while executing %s: %s", functionName, message.c_str() );
        return;
    }
    auto end = std::chrono::high_resolution_clock::now( );
    auto testDuration = Seconds( end - start );
    switch ( operationType )
    {
        case OperationType::Create:
            printf( "Executed %s: inserted %lld rows in %f seconds - %f rows per second\n", functionName, testResult, testDuration.count( ), testResult / testDuration.count( ) );
            break;
        case OperationType::Retrieve:
            printf( "Executed %s: read %lld rows in %f seconds - %f rows per second\n", functionName, testResult, testDuration.count( ), testResult / testDuration.count( ) );
            break;
        case OperationType::Delete:
            printf( "Executed %s in %f seconds\n", functionName, testDuration.count( ) );
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
    DateTime start( 2020, 1, 1 );
    DateTime end( 2020, 2, 1 );
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
    points.reserve( 50000 );
    for ( auto& sensor : sensors )
    {
        session.GetSensorPoints( sensor.Id, points );
        result += points.size( );
    }
    return result;
}

size_t ReadSensorDataForInterval( Session& session, std::vector<Examples::Sensor>& sensors )
{
    DateTime start( 2020, 1, 10 );
    DateTime end( 2020, 1, 25 );
    size_t result = 0;
    std::vector<SensorPoint> points;
    points.reserve( 25000 );
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
    std::vector<SensorPoint> points;
    points.reserve( 25000 );
    for ( auto& sensor : sensors )
    {
        session.GetSensorPoints( sensor.Id, start, end, points );
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
            auto previousTimestamp = points.front( ).Timestamp - TimeSpan( 1 );
            for ( const auto& point : points )
            {
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

    PerformanceOf( "BuildStructure", OperationType::Create, BuildStructure, session, 10, 10, 10 );
    PerformanceOf( "ReadStructure", OperationType::Retrieve, ReadStructure, session, catalogs );
    
    PerformanceOf( "ReadSensors", OperationType::Retrieve, ReadSensors, session, sensors );
    PerformanceOf( "GenerateSensorData", OperationType::Create, GenerateSensorData, session, sensors );

    PerformanceOf( "GetCatalogItemCount", OperationType::Retrieve, GetCatalogItemCount, session );
    PerformanceOf( "GetSensorCount", OperationType::Retrieve, GetSensorCount, session );
    PerformanceOf( "GetSensorValueCount", OperationType::Retrieve, GetSensorValueCount, session );

    PerformanceOf( "ReadAllSensorData", OperationType::Retrieve, ReadAllSensorData, session, sensors );
    PerformanceOf( "ReadSensorDataForInterval", OperationType::Retrieve, ReadSensorDataForInterval, session, sensors );
    PerformanceOf( "ReadSensorDataForIntervalWithCheck", OperationType::Retrieve, ReadSensorDataForIntervalWithCheck, session, sensors );

#ifdef _DEBUG
    PerformanceOf( "DeleteCatalog", OperationType::Delete, DeleteCatalog, session, catalogs.front().Id );

    PerformanceOf( "GetCatalogItemCount", OperationType::Retrieve, GetCatalogItemCount, session );
    PerformanceOf( "GetSensorCount", OperationType::Retrieve, GetSensorCount, session );
    PerformanceOf( "GetSensorValueCount", OperationType::Retrieve, GetSensorValueCount, session );
#endif
    
    //PerformanceOf( "DeleteSensorDataForInterval", OperationType::Delete, DeleteSensorDataForInterval, session, sensors );
    //PerformanceOf( "ReadAllSensorData", OperationType::Retrieve, ReadAllSensorData, session, sensors );
    //PerformanceOf( "DeleteSensors", OperationType::Delete, DeleteSensors, session, sensors );
    //PerformanceOf( "ReadSensors", OperationType::Retrieve, ReadSensors, session, sensors );
    
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
    ApplicationOptions options;
    options.Load( );
    Application application( options );
    application.Start( );
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
        std::string message = exc.what( );
        printf( "Exception: %s", message.c_str( ) );
    }
    application.Start( );
    return 0;
}

