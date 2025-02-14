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


#include <HODBC.h>
#include <HCCApplication.h>

using namespace Harlinn::ODBC;
using namespace Harlinn;

#ifdef _DEBUG
constexpr int rowCount = 10;
#else
constexpr int rowCount = 1'000'000;
#endif


void CreateRows( const ODBC::Connection& connection )
{
    
    DateTime lastTimestamp( 2020, 1, 1 );
    auto firstTimestamp = lastTimestamp - TimeSpan::FromSeconds( rowCount );
    auto oneSecond = TimeSpan::FromSeconds( 1 ).Ticks( );

    Stopwatch stopwatch;
    stopwatch.Start( );

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

    for ( int i = 0; i < rowCount; ++i )
    {
        id = 3;
        timestamp = firstTimestamp + TimeSpan( oneSecond * ( i + 1 ) );
        flags = 0;
        value = static_cast< double >( i ) + 1.0;

        insertStatement.Execute( );
    }
    connection.Commit( );
    stopwatch.Stop( );
    
    auto message = Format( "{} rows inserted in {} seconds.", rowCount, stopwatch.Elapsed( ).TotalSeconds( ) );
    puts( message.c_str( ) );

}

void RetrieveRows1( const ODBC::Connection& connection )
{
    Stopwatch stopwatch;
    stopwatch.Start( );
    auto queryStatement = connection.CreateStatement( );
    auto reader = queryStatement.ExecuteReader( L"SELECT Id,Ts,Flags,Val FROM dbo.TimeseriesValue1" );
    size_t count = 0;

    while ( reader->Read( ) )
    {
        Int64 id = reader->GetInt64( 1 );
        DateTime timestamp = reader->GetDateTime( 2 );
        Int32 flags = reader->GetInt32( 3 );
        double value = reader->GetDouble( 4 );
        ++count;
    }
    stopwatch.Stop( );
    auto message = Format( "{} rows retrieved in {} seconds.", count, stopwatch.Elapsed( ).TotalSeconds( ) );
    puts( message.c_str( ) );
}

void RetrieveRows2( const ODBC::Connection& connection )
{
    Stopwatch stopwatch;
    stopwatch.Start( );
    auto queryStatement = connection.CreateStatement( );
    
    size_t count = 0;

    Int64 id;
    ODBC::TimeStamp timestamp;
    Int32 flags;
    double value;

    queryStatement.BindInt64Column( 1, &id, nullptr );
    queryStatement.BindTimeStampColumn( 2, &timestamp, nullptr );
    queryStatement.BindInt32Column( 3, &flags, nullptr );
    queryStatement.BindDoubleColumn( 4, &value, nullptr );

    queryStatement.ExecDirect( L"SELECT Id,Ts,Flags,Val FROM dbo.TimeseriesValue1" );

    while ( queryStatement.Fetch( ) != ODBC::Result::NoData )
    {
        ++count;
    }
    stopwatch.Stop( );
    auto message = Format( "{} rows retrieved in {} seconds.", count, stopwatch.Elapsed( ).TotalSeconds( ) );
    puts( message.c_str( ) );
}


void RetrieveRows3( const ODBC::Connection& connection )
{
    Stopwatch stopwatch;
    stopwatch.Start( );
    auto queryStatement = connection.CreateStatement( );

    size_t count = 0;
    size_t numRowsFetched = 0;

    std::vector<Int64> id;
    id.resize( 1000 );
    std::vector<ODBC::TimeStamp> timestamp;
    timestamp.resize( 1000 );
    std::vector<Int32> flags;
    flags.resize( 1000 );
    std::vector<double> value;
    value.resize( 1000 );

    queryStatement.SetRowBindByColumn( );
    queryStatement.SetRowArraySize( 1000 );
    queryStatement.SetRowsFetchedPointer( &numRowsFetched );

    queryStatement.BindInt64Column( 1, id.data(), nullptr );
    queryStatement.BindTimeStampColumn( 2, timestamp.data( ), nullptr );
    queryStatement.BindInt32Column( 3, flags.data( ), nullptr );
    queryStatement.BindDoubleColumn( 4, value.data( ), nullptr );

    queryStatement.ExecDirect( L"SELECT Id,Ts,Flags,Val FROM dbo.TimeseriesValue1" );

    while ( queryStatement.FetchScroll(ODBC::FetchOrientation::Next, 0) != ODBC::Result::NoData )
    {
        count += numRowsFetched;
    }
    stopwatch.Stop( );
    auto message = Format( "{} rows retrieved in {} seconds.", count, stopwatch.Elapsed( ).TotalSeconds( ) );
    puts( message.c_str( ) );
}

struct RowDats
{
    Int64 id;
    ODBC::TimeStamp timestamp;
    Int32 flags;
    double value;
};

void RetrieveRows4( const ODBC::Connection& connection )
{
    Stopwatch stopwatch;
    stopwatch.Start( );
    auto queryStatement = connection.CreateStatement( );

    size_t count = 0;
    size_t numRowsFetched = 0;

    std::vector<RowDats> rowData;
    rowData.resize( 10 );
    auto rowDataPtr = rowData.data( );

    queryStatement.SetRowSize( sizeof( RowDats ) );
    queryStatement.SetRowArraySize( 10 );
    queryStatement.SetRowsFetchedPointer( &numRowsFetched );

    queryStatement.BindInt64Column( 1, &rowDataPtr[0].id, nullptr );
    queryStatement.BindTimeStampColumn( 2, &rowDataPtr[ 0 ].timestamp, nullptr );
    queryStatement.BindInt32Column( 3, &rowDataPtr[ 0 ].flags, nullptr );
    queryStatement.BindDoubleColumn( 4, &rowDataPtr[ 0 ].value, nullptr );

    queryStatement.ExecDirect( L"SELECT Id,Ts,Flags,Val FROM dbo.TimeseriesValue1" );

    while ( queryStatement.FetchScroll( ODBC::FetchOrientation::Next, 0 ) != ODBC::Result::NoData )
    {
        count += numRowsFetched;
    }
    stopwatch.Stop( );
    auto message = Format( "{} rows retrieved in {} seconds.", count, stopwatch.Elapsed( ).TotalSeconds( ) );
    puts( message.c_str( ) );
}



void UpdateRows( const ODBC::Connection& connection )
{
    Stopwatch stopwatch;
    stopwatch.Start( );
    DateTime lastTimestamp( 2020, 1, 1 );
    auto firstTimestamp = lastTimestamp - TimeSpan::FromSeconds( rowCount );
    auto oneSecond = TimeSpan::FromSeconds( 1 ).Ticks( );

    auto updateStatement = connection.CreateStatement( );
    updateStatement.Prepare( L"UPDATE dbo.TimeseriesValue1 SET [Val] = ? WHERE [Id] = 3 AND [Ts] = ?" );

    double value;
    ODBC::TimeStamp timestamp;

    updateStatement.BindDoubleParameter( 1, &value );
    updateStatement.BindTimeStampParameter( 2, 7, &timestamp );

    for ( int i = 0; i < rowCount; ++i )
    {
        timestamp = firstTimestamp + TimeSpan( oneSecond * ( i + 1 ) );
        value = static_cast< double >( i ) + 2.0;

        updateStatement.Execute( );
    }
    connection.Commit( );
    stopwatch.Stop( );

    auto message = Format( "{} rows updated in {} seconds.", rowCount, stopwatch.Elapsed( ).TotalSeconds( ) );
    puts( message.c_str( ) );
}

void DeleteRows( const ODBC::Connection& connection )
{
    Stopwatch stopwatch;
    stopwatch.Start( );
    auto deleteStatement = connection.CreateStatement( );
    deleteStatement.ExecDirect( L"delete from dbo.TimeseriesValue1" );
    auto numberOfRowsDeleted = deleteStatement.RowCount( );
    connection.Commit( );
    stopwatch.Stop( );

    auto message = Format( "{} rows deleted in {} seconds.", numberOfRowsDeleted, stopwatch.Elapsed().TotalSeconds() );
    puts( message.c_str( ) );

}

void Run( const ODBC::Environment& environment )
{
    std::wstring DataSource = L"Ajaworks";
    std::wstring DatabaseName = L"AjaworksDev";
    ODBC::Connection connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    connection.SetAutoCommitMode( false );
    DeleteRows( connection );
    CreateRows( connection );
    RetrieveRows1( connection );
    RetrieveRows2( connection );
    RetrieveRows3( connection );
    RetrieveRows4( connection );
    UpdateRows( connection );
    RetrieveRows2( connection );
    DeleteRows( connection );

}

void Run( )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    Run( environment );
}



int main()
{
    auto applicationOptions = std::make_shared<ApplicationOptions>( );
    applicationOptions->Load( );
    auto application = std::make_shared<Application>( applicationOptions );
    application->Start( );

    try
    {
        Run( );
    }
    catch ( std::exception& exc )
    {
        auto message = Format( "Exception caught in main, message: {}.", exc.what() );
        puts( message.c_str( ) );
    }
    catch ( ... )
    {
        puts( "Unknown exception caught in main." );
    }

    application->Stop( );
}
