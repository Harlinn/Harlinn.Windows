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

        result.Username = username.As<std::wstring>( );
        result.Password = password.As<std::wstring>( );
        result.Alias = alias.As<std::wstring>( );
    }
    return result;
}

int main()
{
    auto applicationOptions = std::make_shared<ApplicationOptions>( );
    applicationOptions->Load( );
    auto application = std::make_shared<Application>( applicationOptions );
    application->Start( );

    CoInitializeEx( nullptr, COINIT_MULTITHREADED );
    auto loginInfo = GetLoginInfo( );

    EnvironmentOptions options;
    OCI::Environment environment( options );
    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( loginInfo.Username, loginInfo.Password, loginInfo.Alias );
    serviceContext.SessionBegin( );
    {
        auto statement = serviceContext.CreateStatement( L"SELECT Id,Ts,Flags,Val FROM TimeseriesValue2 ORDER BY Id,Ts" );
        statement.SetPrefetchRows( 30'000 );

        Stopwatch stopwatch;
        stopwatch.Start( );
        auto reader = statement.ExecuteReader<ArrayDataReader>( 120'000 );
        size_t count = 0;
        while ( reader->Read( ) )
        {
            auto id = reader->GetUInt64( 0 );
            auto ts = reader->GetUInt64( 1 );
            auto flags = reader->GetUInt64( 2 );
            auto value = reader->GetDouble( 3 );
            count++;
        }
        stopwatch.Stop( );
        auto duration = stopwatch.TotalSeconds( );
        auto rowsPerSecond = count / duration;
        printf( "Retrieved %zu rows in %f seconds - %f rows per seconds\n",
            count, duration, rowsPerSecond );

    }
    serviceContext.SessionEnd( );
    CoUninitialize( );

    application->Stop( );

}

