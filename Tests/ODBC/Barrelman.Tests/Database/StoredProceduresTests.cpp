#include <HCCIO.h>
#include "Databases/MsSql/MsSqlStoredProcedures.h"
#include "Databases/MsSql/MsSqlSimpleDatabaseReaders.h"
#include "Databases/MsSql/MsSqlComplexDatabaseReaders.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common;
using namespace Harlinn::ODBC;
using namespace Harlinn;
using namespace Barrelman;
using namespace Barrelman::Types;

class StoredProceduresLocalFixture
{
public:
    WideString DataSource{ L"Barrelman" };
    WideString DatabaseName{ L"Barrelman" };

    StoredProceduresLocalFixture( ) = default;
    ~StoredProceduresLocalFixture( ) = default;
};

BOOST_FIXTURE_TEST_SUITE( StoredProceduresTests, StoredProceduresLocalFixture )

// --run_test=StoredProceduresTests/AircraftTypeTest
BOOST_AUTO_TEST_CASE( AircraftTypeTest )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    connection.SetCurrentCatalog( DatabaseName );

    Guid id( L"{E9D19608-ADEE-41B5-ADDF-E519AE336B0C}" );
    FixedDBWideString<127> name1 = L"Lockheed Martin F-35 Lightning II";
    FixedDBWideString<127> name2 = L"NASA M2-F1";
    Int64 rowVersion = 0;
    auto deleteStatement = connection.CreateStatement( );
    deleteStatement.BindGuidParameter( 1, &id );
    deleteStatement.ExecDirect( L"DELETE FROM AircraftType WHERE Id = ?" );

    auto inserted = Databases::MsSql::InsertAircraftType( connection, id, name1 );
    BOOST_CHECK( inserted );
    auto statementAfterInsert = connection.CreateStatement( );
    statementAfterInsert.BindGuidParameter( 1, &id );
    auto readerAfterInsert = statementAfterInsert.ExecuteReader<Databases::MsSql::SimpleAircraftTypeDataReader>( Databases::MsSql::SimpleAircraftTypeDataReader::BaseQuery + L" WHERE Id = ?" );
    bool readerAfterInsertHasData = readerAfterInsert->Read( );
    BOOST_CHECK( readerAfterInsertHasData );
    if ( readerAfterInsertHasData )
    {
        const auto& name = readerAfterInsert->Name( );
        bool equal = name == name1;
        BOOST_CHECK( equal );
        
    }
    
    auto updated = Databases::MsSql::UpdateAircraftType( connection, id, rowVersion, name2 );
    BOOST_CHECK( updated );
    auto statementAfterUpdate = connection.CreateStatement( );
    statementAfterUpdate.BindGuidParameter( 1, &id );
    auto readerAfterUpdate = statementAfterUpdate.ExecuteReader<Databases::MsSql::SimpleAircraftTypeDataReader>( Databases::MsSql::SimpleAircraftTypeDataReader::BaseQuery + L" WHERE Id = ?" );
    bool readerAfterUpdateHasData = readerAfterUpdate->Read( );
    BOOST_CHECK( readerAfterUpdateHasData );
    if ( readerAfterUpdateHasData )
    {
        const auto& name = readerAfterUpdate->Name( );
        bool equal = name == name2;
        BOOST_CHECK( equal );
    }

    auto deleted = Databases::MsSql::DeleteAircraftType( connection, id, rowVersion );
    BOOST_CHECK( deleted );

}

// --run_test=StoredProceduresTests/TimeseriesCatalogTest
BOOST_AUTO_TEST_CASE( TimeseriesCatalogTest )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    connection.SetCurrentCatalog( DatabaseName );

    Guid id( L"{51F94DF8-2BED-45E1-A64A-18D97434808D}" );
    FixedDBWideString<127> name1 = L"Devices";
    Int64 rowVersion = 0;

    Databases::MsSql::DeleteTimeseriesCatalog( connection, id, rowVersion );

    auto inserted = Databases::MsSql::InsertTimeseriesCatalog( connection, id, {}, name1 );
    BOOST_CHECK( inserted );

    auto statementAfterInsert = connection.CreateStatement( );
    statementAfterInsert.BindGuidParameter( 1, &id );

    auto sql = Databases::MsSql::ComplexTimeseriesCatalogElementDataReader::BaseQuery + L" WHERE " + Databases::MsSql::ComplexTimeseriesCatalogElementDataReader::ViewAliasName + L".Id = ?";

    auto readerAfterInsert = statementAfterInsert.ExecuteReader<Databases::MsSql::ComplexTimeseriesCatalogElementDataReader>( sql );
    bool readerAfterInsertHasData = readerAfterInsert->Read( );
    BOOST_CHECK( readerAfterInsertHasData );
    
    if ( readerAfterInsertHasData )
    {
        const auto& name = readerAfterInsert->Name( );
        bool equal = name == name1;
        BOOST_CHECK( equal );

    }

    auto deleted = Databases::MsSql::DeleteTimeseriesCatalog( connection, id, rowVersion );
    BOOST_CHECK( deleted );

}


BOOST_AUTO_TEST_SUITE_END( )