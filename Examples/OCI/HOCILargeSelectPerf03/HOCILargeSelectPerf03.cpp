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


#include <HOCI.h>
#include <HCCXml.h>
#include <oci.h>
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

#pragma comment(lib,"oci.lib")

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
        struct TimeseriesValue
        {
            Int64 Id;
            Int64 Timestamp;
            Int64 Flags;
            Double Value;
        };

        constexpr UInt32 PrefetchRows = 32'000;
        auto statement = serviceContext.CreateStatement( L"SELECT Id,Ts,Flags,Val FROM TimeseriesValue2 ORDER BY Id,Ts" );
        statement.SetPrefetchRows( PrefetchRows );


        std::vector<TimeseriesValue> values( PrefetchRows * 4 );
        TimeseriesValue* data = values.data( );

        OCIStmt* statementHandle = ( OCIStmt* )statement.Handle( );
        auto& error = statement.Error( );
        OCIError* errorHandle = ( OCIError* )error.Handle( );

        OCIDefine* idDefineHandle = nullptr;
        auto rc = OCIDefineByPos2( statementHandle, &idDefineHandle, errorHandle, 1,
            &data->Id, sizeof( data->Id ), SQLT_INT,
            nullptr, nullptr, nullptr, OCI_DEFAULT );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        rc = OCIDefineArrayOfStruct( idDefineHandle, errorHandle,
            sizeof( TimeseriesValue ), 0, 0, 0 );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }

        OCIDefine* timestampDefineHandle = nullptr;
        rc = OCIDefineByPos2( statementHandle, &timestampDefineHandle, errorHandle, 2,
            &data->Timestamp, sizeof( data->Timestamp ), SQLT_INT,
            nullptr, nullptr, nullptr, OCI_DEFAULT );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        rc = OCIDefineArrayOfStruct( timestampDefineHandle, errorHandle,
            sizeof( TimeseriesValue ), 0, 0, 0 );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        OCIDefine* flagsDefineHandle = nullptr;
        rc = OCIDefineByPos2( statementHandle, &flagsDefineHandle, errorHandle, 3,
            &data->Flags, sizeof( data->Timestamp ), SQLT_INT,
            nullptr, nullptr, nullptr, OCI_DEFAULT );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        rc = OCIDefineArrayOfStruct( flagsDefineHandle, errorHandle,
            sizeof( TimeseriesValue ), 0, 0, 0 );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        OCIDefine* valueDefineHandle = nullptr;
        rc = OCIDefineByPos2( statementHandle, &valueDefineHandle, errorHandle, 4,
            &data->Value, sizeof( data->Value ), SQLT_BDOUBLE,
            nullptr, nullptr, nullptr, OCI_DEFAULT );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        rc = OCIDefineArrayOfStruct( valueDefineHandle, errorHandle,
            sizeof( TimeseriesValue ), 0, 0, 0 );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }


        OCISvcCtx* serviceContextHandle = ( OCISvcCtx* )serviceContext.Handle( );
        Stopwatch stopwatch;
        stopwatch.Start( );
        size_t count = 0;
        rc = OCIStmtExecute( serviceContextHandle, statementHandle, errorHandle,
            0, 0, NULL, NULL, OCI_DEFAULT );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }

        rc = OCIStmtFetch2( statementHandle, errorHandle,
            static_cast< UInt32 >( values.size( ) ),
            OCI_FETCH_NEXT, 0, OCI_DEFAULT );
        if ( rc >= OCI_SUCCESS )
        {
            UInt32 rowsFetched = statement.RowsFetched( );
            while ( rowsFetched && rc >= OCI_SUCCESS )
            {
                for ( UInt32 i = 0; i < rowsFetched; ++i )
                {
                    auto id = data[ i ].Id;
                    auto ts = data[ i ].Timestamp;
                    auto flags = data[ i ].Flags;
                    auto value = data[ i ].Value;
                    count++;
                }
                if ( rc != OCI_NO_DATA )
                {
                    rc = OCIStmtFetch2( statementHandle, errorHandle,
                        static_cast< UInt32 >( values.size( ) ),
                        OCI_FETCH_NEXT, 0, OCI_DEFAULT );
                    rowsFetched = statement.RowsFetched( );
                }
                else
                {
                    rowsFetched = 0;
                }
            }
        }
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
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

