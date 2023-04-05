#include <HOCI.h>
#include <HCCXml.h>
#include <HCCApplication.h>

using namespace Harlinn::Common;
using namespace Harlinn::OCI;
using namespace Harlinn;

struct LoginInfo
{
    std::wstring Username;
    std::wstring Password;
    std::wstring Alias;
};

LoginInfo GetLoginInfo( )
{
    LoginInfo result;
    auto xmlFilename = IO::Directory::GetExecutableDirectory( ) + L"Harlinn.OCI.Tests.xml";

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

        result.Username = username.As<std::wstring>( );
        result.Password = password.As<std::wstring>( );
        result.Alias = alias.As<std::wstring>( );
    }
    return result;
}

class TimeseriesValues2Reader : public ArrayDataReader
{
public:
    using Base = ArrayDataReader;
    constexpr static UInt32 ID_ID = 0;
    constexpr static UInt32 TS_ID = 1;
    constexpr static UInt32 FLAGS_ID = 2;
    constexpr static UInt32 VAL_ID = 3;

    constexpr static wchar_t SQL[] = L"SELECT Id,Ts,Flags,Val FROM TimeseriesValue2 ORDER BY Id,Ts";
public:
    TimeseriesValues2Reader( const OCI::Statement& statement, size_t size )
        : Base( statement, size )
    {
    }
    virtual void InitializeDefines( ) override
    {
        Define<Int64>( ID_ID + 1 );
        Define<Int64>( TS_ID + 1 );
        Define<Int64>( FLAGS_ID + 1 );
        Define<Double>( VAL_ID + 1 );
    }
    UInt64 Id( ) const { return GetInt64( ID_ID ); }
    UInt64 Timestamp( ) const { return GetInt64( TS_ID ); }
    UInt64 Flag( ) const { return GetInt64( FLAGS_ID ); }
    Double Value( ) const { return GetDouble( VAL_ID ); }
};


int main()
{
    ApplicationOptions applicationOptions;
    applicationOptions.Load( );
    Application application( applicationOptions );
    application.Start( );

    CoInitializeEx( nullptr, COINIT_MULTITHREADED );
    auto loginInfo = GetLoginInfo( );

    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( loginInfo.Username, loginInfo.Password, loginInfo.Alias );
    serviceContext.SessionBegin( );

    constexpr UInt32 PrefetchRows = 32'000;
    auto statement = serviceContext.CreateStatement( TimeseriesValues2Reader::SQL );
    statement.SetPrefetchRows( PrefetchRows );

    Stopwatch stopwatch;
    stopwatch.Start( );
    auto start = TimeSpan::UserTime( );
    auto reader = statement.ExecuteReader<TimeseriesValues2Reader>( PrefetchRows * 5 );
    size_t count = 0;
    while ( reader->Read( ) )
    {
        auto id = reader->Id( );
        auto ts = reader->Timestamp( );
        auto flags = reader->Flag( );
        auto value = reader->Value( );
        count++;
    }
    auto stop = TimeSpan::UserTime( );
    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto userTime = stop.TotalSeconds( ) - start.TotalSeconds( );
    auto rowsPerSecond = count / duration;
    printf( "Retrieved %zu rows in %f seconds - %f rows per seconds, user time: %f\n",
        count, duration, rowsPerSecond, userTime );

    serviceContext.SessionEnd( );
    CoUninitialize( );

    application.Stop( );

}

