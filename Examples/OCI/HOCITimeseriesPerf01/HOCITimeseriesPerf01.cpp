#include <DataContext.h>
#include <HCCXml.h>
#include <HCCApplication.h>

struct LoginInfo
{
public:

    std::wstring Username;
    std::wstring Password;
    std::wstring Alias;

    LoginInfo( )
    {
        auto xmlFilename = IO::Directory::GetExecutableDirectory<WideString>( ) + L"Harlinn.OCI.Tests.xml";

        auto document = Xml::Dom::Document::Create( );
        document.SetAsync( false );
        document.SetValidateOnParse( false );
        document.SetResolveExternals( false );
        document.SetPreserveWhiteSpace( true );

        auto success = document.Load( xmlFilename );


        auto documentElement = document.DocumentElement( );
        auto list = documentElement.ElementsByTagName( L"Oracle" );
        if ( list.size( ) )
        {
            Xml::Dom::Element element = list[0];

            auto username = element.Attribute( L"Username" );
            auto password = element.Attribute( L"Password" );
            auto alias = element.Attribute( L"Alias" );

            Username = username.As<std::wstring>( );
            Password = password.As<std::wstring>( );
            Alias = alias.As<std::wstring>( );
        }

    }
};



int main()
{
    ApplicationOptions applicationOptions;
    applicationOptions.Load( );
    Application application( applicationOptions );
    application.Start( );

    using namespace Harlinn::Common::Core;

    CoInitializeEx( nullptr, COINIT_MULTITHREADED );

    LoginInfo loginInfo;

    Engine engine;
    Session session( engine, loginInfo.Username, loginInfo.Password, loginInfo.Alias );
    DataContext dataContext( session );
#if 1
    dataContext.ClearTimeseriesPointSegments( );
    dataContext.ClearOwnedObjects( );
    dataContext.ClearOwnedObjectTypes( );
    //session.Commit( );


    auto ownedObjectType = dataContext.CreateOwnedObjectType( L"Type1", L"Type1 description" );
    auto ownedObject = dataContext.CreateOwnedObject( ownedObjectType->Id, L"Object1", L"Object1 description" );

    constexpr size_t PointCount = 12500* TimeseriesPointSegment::MaxPoints;
    constexpr size_t SegmentCount = PointCount / TimeseriesPointSegment::MaxPoints;
    DateTime endTimestamp(2020,1,1);
    DateTime startTimestamp = endTimestamp - TimeSpan::FromSeconds( PointCount );
    DateTime current = startTimestamp;
    TimeSpan oneSecond = TimeSpan::FromSeconds( 1 );
    auto segmentPtr = std::make_unique<TimeseriesPointSegment>( );
    auto& segment = *segmentPtr;
    segment.SetSize( TimeseriesPointSegment::MaxPoints );

    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( size_t i = 0; i < SegmentCount; ++i )
    {
        for ( size_t j = 0; j < TimeseriesPointSegment::MaxPoints; ++j )
        {
            DateTime timestamp( static_cast<Int64>((i * TimeseriesPointSegment::MaxPoints * DateTime::TicksPerSecond) + (j* DateTime::TicksPerSecond )) );
            segment[j] = TimeseriesPoint( timestamp, 0, static_cast<double>(j) );
        }
        dataContext.InsertTimeseriesPointSegment( ownedObject->Id, segment );
    }
    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto pointsPerSecond = PointCount / duration;
    printf( "Inserted %zu timeseries points in %f seconds - %f points per second\n", PointCount, duration, pointsPerSecond );

    stopwatch.Restart( );
#else
    double duration = 0;
    double pointsPerSecond = 0;
    auto ownedObjects = dataContext.ReadOwnedObjects( );
    auto ownedObject = ownedObjects.begin( )->second.get( );


    Stopwatch stopwatch;
    stopwatch.Start( );


#endif

    auto timeseriesPoints = dataContext.ReadSegments( ownedObject->Id );

    stopwatch.Stop( );
    duration = stopwatch.TotalSeconds( );
    size_t pointsRead = timeseriesPoints.Size( );

    auto segmentRead = timeseriesPoints.First( );
    size_t validated = 0;
    for ( size_t i = 0; i < SegmentCount; ++i )
    {
        for ( size_t j = 0; j < TimeseriesPointSegment::MaxPoints; ++j )
        {
            DateTime timestamp( static_cast<Int64>( ( i * TimeseriesPointSegment::MaxPoints * DateTime::TicksPerSecond ) + ( j * DateTime::TicksPerSecond ) ) );
            if ( ( *segmentRead )[j] != TimeseriesPoint( timestamp, 0, static_cast<double>( j ) )  )
            {
                printf( "Trouble at [%zu,%zu]\n", i, j );
            }
            validated++;
        }
        segmentRead = segmentRead->Next( );
    }


    pointsPerSecond = pointsRead / duration;

    printf( "Validated %zu timeseries points\n", validated );
    printf( "Read %zu timeseries points in %f seconds - %f points per second\n", pointsRead, duration, pointsPerSecond );

    CoUninitialize( );

    application.Stop( );

    return 0;
}

