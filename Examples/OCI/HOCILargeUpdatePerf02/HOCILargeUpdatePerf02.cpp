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

struct TimeseriesValues1
{
    Int64 Id;
    DateTime Timestamp;
    Int64 Flags;
    double Value;
};

class TimeseriesValues1Reader : public ArrayDataReader
{
public:
    using Base = ArrayDataReader;
    constexpr static UInt32 ID_ID = 0;
    constexpr static UInt32 TS_ID = 1;
    constexpr static UInt32 FLAGS_ID = 2;
    constexpr static UInt32 VAL_ID = 3;

    constexpr static wchar_t SQL[] = L"SELECT Id,Ts,Flags,Val FROM TimeseriesValue1 ORDER BY Id,Ts";
public:
    TimeseriesValues1Reader( const OCI::Statement& statement, size_t size )
        : Base( statement, size )
    {
    }
    virtual void InitializeDefines( ) override
    {
        Define<Int64>( ID_ID + 1 );
        Define<DateTime>( TS_ID + 1 );
        Define<Int64>( FLAGS_ID + 1 );
        Define<Double>( VAL_ID + 1 );
    }
    UInt64 Id( ) const { return GetInt64( ID_ID ); }
    DateTime Timestamp( ) const { return GetDateTime( TS_ID ); }
    UInt64 Flag( ) const { return GetInt64( FLAGS_ID ); }
    Double Value( ) const { return GetDouble( VAL_ID ); }
};


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

    constexpr UInt32 PrefetchRows = 32'000;
    auto selectStatement = serviceContext.CreateStatement( TimeseriesValues1Reader::SQL );
    selectStatement.SetPrefetchRows( PrefetchRows );

    auto reader = selectStatement.ExecuteReader<TimeseriesValues1Reader>( PrefetchRows * 5 );
    size_t count = 0;
    std::vector<TimeseriesValues1> rows;
    TimeseriesValues1 timeseriesValues1;
    while ( reader->Read( ) )
    {
        timeseriesValues1.Id = reader->Id( );
        timeseriesValues1.Timestamp = reader->Timestamp( );
        timeseriesValues1.Flags = reader->Flag( );
        timeseriesValues1.Value = reader->Value( );
        rows.emplace_back( timeseriesValues1 );
        count++;
    }



    constexpr wchar_t sql[] = L"UPDATE TimeseriesValue1 SET Flags=:1, Val=:2 WHERE Id=:3 AND Ts=:4";
    auto updateStatement = serviceContext.CreateStatement( sql );

    auto flag = updateStatement.Bind<UInt64ArrayBind>( 1 );
    auto value = updateStatement.Bind<DoubleArrayBind>( 2 );
    auto id = updateStatement.Bind<UInt64ArrayBind>( 3 );
    auto timestamp = updateStatement.Bind<TimestampArrayBind>( 4 );

    std::vector<UInt64> ids( count );
    std::vector<DateTime> timestamps( count );
    std::vector<UInt64> flags( count );
    std::vector<double> values( count );

    for ( size_t i = 0; i < count; ++i )
    {
        auto& row = rows[i];
        ids[i] = row.Id;
        timestamps[i] = row.Timestamp;
        flags[i] = row.Flags*2;
        values[i] = row.Value*2;
    }

    // Assign the vectors to the bind objects
    id->Assign( std::move( ids ) );
    timestamp->Assign( timestamps );
    flag->Assign( std::move( flags ) );
    value->Assign( std::move( values ) );


    Stopwatch stopwatch;
    stopwatch.Start( );
    
    updateStatement.ExecuteNonQuery( static_cast<UInt32>( count ) );
    serviceContext.TransactionCommit( );

    stopwatch.Stop( );
    auto duration = stopwatch.TotalSeconds( );
    auto rowsPerSecond = count / duration;
    printf( "Updated %zu rows in %f seconds - %f rows per seconds\n",
        count, duration, rowsPerSecond );

    serviceContext.SessionEnd( );
    CoUninitialize( );

    application->Stop( );
}

