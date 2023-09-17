#include <HODBC.h>
#include <HCCApplication.h>

using namespace Harlinn::Common;
using namespace Harlinn::ODBC;
using namespace Harlinn;


class TimeseriesValue2DateReader : public DataReaderBase
{
    Int64 id_ = 0;
    Int64 ts_;
    Int32 flags_ = 0;
    Double value_ = 0.0;
public:
    static constexpr SQLUSMALLINT ID_ID = 1;
    static constexpr SQLUSMALLINT TS_ID = 2;
    static constexpr SQLUSMALLINT FLAGS_ID = 3;
    static constexpr SQLUSMALLINT VALUE_ID = 4;

    using Base = DataReaderBase;

    TimeseriesValue2DateReader( const Statement* statement )
        : Base( statement )
    {
        Bind( ID_ID, &id_ );
        Bind( TS_ID, &ts_ );
        Bind( FLAGS_ID, &flags_ );
        Bind( VALUE_ID, &value_ );
    }

    constexpr Int64 Id( ) const noexcept
    {
        return id_;
    }
    constexpr Int64 Timestamp( ) const noexcept
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






int main( )
{
    auto applicationOptions = std::make_shared<ApplicationOptions>( );
    applicationOptions->Load( );
    Application application( applicationOptions );
    application.Start( );

//#define SELECT_ONLY 1
    std::wstring DataSource = L"Ajaworks";
    std::wstring DatabaseName = L"AjaworksDev";

    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    connection.SetAutoCommitMode( false );

#ifndef SELECT_ONLY
    auto deleteStatement = connection.CreateStatement( );
    deleteStatement.ExecDirect( L"delete from dbo.TimeseriesValue2" );
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
    insertStatement.Prepare( L"INSERT INTO dbo.TimeseriesValue2(Id,Ts,Flags,Val) " \
        "VALUES(?,?,?,?)" );

    Int64 id;
    Int64 timestamp;
    Int32 flags;
    double value;

    insertStatement.BindParameter( 1, ParameterDirection::Input, &id );
    insertStatement.BindParameter( 2, ParameterDirection::Input, &timestamp );
    insertStatement.BindParameter( 3, ParameterDirection::Input, &flags );
    insertStatement.BindParameter( 4, ParameterDirection::Input, &value );


    Stopwatch stopwatch;
    stopwatch.Start( );

    for ( int i = 0; i < count; ++i )
    {
        auto ts = firstTimestamp + TimeSpan( oneSecond * ( i + 1 ) );
        id = 3;
        timestamp = ts.Ticks( );
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
    selectStatement.BindParameter( 1, ParameterDirection::Input, &id );
#ifndef SELECT_ONLY
    stopwatch.Restart( );
#else
    stopwatch.Start( );
#endif
    auto reader = selectStatement.ExecuteReader<TimeseriesValue2DateReader>( L"select Id, Ts, Flags, val from TimeseriesValue2 where Id = ?" );
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

    application.Stop( );

}
