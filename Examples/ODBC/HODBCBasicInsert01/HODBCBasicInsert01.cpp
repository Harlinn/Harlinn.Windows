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


#include <HODBC.h>
#include <HCCApplication.h>

using namespace Harlinn::Common;
using namespace Harlinn::ODBC;
using namespace Harlinn;


class TimeseriesValue1DateReader : public DataReader
{
    Int64 id_ = 0;
    ODBC::TimeStamp ts_;
    Int32 flags_ = 0;
    Double value_ = 0.0;
public:
    static constexpr SQLUSMALLINT ID_ID = 1;
    static constexpr SQLUSMALLINT TS_ID = 2;
    static constexpr SQLUSMALLINT FLAGS_ID = 3;
    static constexpr SQLUSMALLINT VALUE_ID = 4;

    using Base = DataReader;

    TimeseriesValue1DateReader( const ODBC::Statement* statement )
        : Base( statement )
    {
        BindInt64( ID_ID, &id_ );
        BindTimeStamp( TS_ID, &ts_ );
        BindInt32( FLAGS_ID, &flags_ );
        BindDouble( VALUE_ID, &value_ );
    }

    constexpr Int64 Id( ) const noexcept
    {
        return id_;
    }
    constexpr const ODBC::TimeStamp& Timestamp( ) const noexcept
    {
        return ts_;
    }
    constexpr Int32 Flags( ) const noexcept
    {
        return flags_;
    }
    constexpr Double Value( ) const noexcept
    {
        return value_;
    }
};






int main()
{
    auto applicationOptions = std::make_shared<ApplicationOptions>( );
    applicationOptions->Load( );
    auto application = std::make_shared<Application>( applicationOptions );
    application->Start( );

//#define SELECT_ONLY 1
    std::wstring DataSource = L"Ajaworks";
    std::wstring DatabaseName = L"AjaworksDev";

    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    connection.SetAutoCommitMode( false );

#ifndef SELECT_ONLY
    auto deleteStatement = connection.CreateStatement( );
    deleteStatement.ExecDirect( L"delete from dbo.TimeseriesValue1" );
    connection.Commit( );
#endif

#ifdef _DEBUG
    int count = 10;
#else
    int count = 1'000'000;
#endif



#ifndef SELECT_ONLY
    DateTime lastTimestamp( 2020, 1, 1 );
    auto firstTimestamp = lastTimestamp - TimeSpan::FromSeconds( count );
    auto oneSecond = TimeSpan::FromSeconds( 1 ).Ticks( );

    auto insertStatement = connection.CreateStatement( );
    insertStatement.Prepare( L"INSERT INTO dbo.TimeseriesValue1(Id,Ts,Flags,Val) " \
        "VALUES(?,?,?,?)" );

    Int64 id;
    ODBC::TimeStamp timestamp;
    Int32 flags;
    double value;

    insertStatement.BindInt64Parameter( 1, &id );
    insertStatement.BindTimeStampParameter( 2, 7, &timestamp );
    insertStatement.BindInt32Parameter( 3, &flags );
    insertStatement.BindDoubleParameter( 4, &value );


    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( int i = 0; i < count; ++i )
    {
        id = 3;
        timestamp = firstTimestamp + TimeSpan( oneSecond * ( i + 1 ) );
        flags = 0;
        value = static_cast<double>( i ) + 1.0;

        insertStatement.Execute( );
    }
    connection.Commit( );
    stopwatch.Stop( );

    auto duration = stopwatch.TotalSeconds( );
    double perSecond = count / duration;
    printf( "Inserted %d rows in %f seconds - %f rows per second.\n", count, duration, perSecond );
    flushall( );
#else
    Int64 id;
    Stopwatch stopwatch;
#endif
    auto selectStatement = connection.CreateStatement( );
    id = 3;
    selectStatement.BindInt64Parameter( 1, &id );
    //selectStatement.SetR
#ifndef SELECT_ONLY
    stopwatch.Restart( );
#else
    stopwatch.Start( );
#endif
    auto reader = selectStatement.ExecuteReader<TimeseriesValue1DateReader>( L"select Id, Ts, Flags, val from TimeseriesValue1 where Id = ?" );
    size_t selectedCount = 0;
    while ( reader->Read( ) )
    {
        selectedCount++;
    }
    stopwatch.Stop( );
#ifndef SELECT_ONLY
    duration = stopwatch.TotalSeconds( );
    perSecond = selectedCount / duration;
#else
    double duration = stopwatch.TotalSeconds( );
    double perSecond = selectedCount / duration;
#endif
    printf( "Selected %zu rows in %f seconds - %f rows per second.\n", selectedCount, duration, perSecond );
    flushall( );

    application->Stop( );

}
