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


int main( )
{
    ApplicationOptions applicationOptions;
    applicationOptions.Load( );
    Application application( applicationOptions );
    application.Start( );

    // Number of rows to insert
    constexpr size_t count = 1'000'000;

    CoInitializeEx( nullptr, COINIT_MULTITHREADED );
    auto loginInfo = GetLoginInfo( );

    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( loginInfo.Username, loginInfo.Password, loginInfo.Alias );
    serviceContext.SessionBegin( );

    std::wstring sql1( L"DELETE FROM TimeseriesValue2" );
    auto deleteStatement = serviceContext.CreateStatement( sql1 );
    deleteStatement.Execute( );
    serviceContext.TransactionCommit( );

    std::wstring sql2( L"INSERT INTO TimeseriesValue2(Id,Ts,Flags,Val) "
        L"VALUES( :1, :2, :3, :4)" );

    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( size_t i = 0; i < count; ++i )
    {
        auto id = i + 1;
        auto timestamp = i + 1;
        auto flags = i + 1;
        auto value = static_cast<double>( i + 1 );

        // Create the statement
        auto insertStatement = serviceContext.CreateStatement( sql2, id, timestamp, flags, value );
        // Execute the insert
        insertStatement.Execute( );
    }
    // commit the changes
    serviceContext.TransactionCommit( );
    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto rowsPerSecond = count / duration;
    printf( "Inserted %zu rows in %f seconds - %f rows per seconds\n",
        count, duration, rowsPerSecond );

    std::wstring sql3( L"SELECT COUNT(*) FROM TimeseriesValue2" );

    auto result = serviceContext.ExecuteScalar<Int64>( sql3 );
    if ( result.has_value( ) )
    {
        printf( "Found %zu rows in TimeseriesValue2\n", result.value( ) );
    }


    serviceContext.SessionEnd( );
    CoUninitialize( );

    application.Stop( );
}
