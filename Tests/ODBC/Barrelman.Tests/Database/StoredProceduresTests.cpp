#include <HCCIO.h>
#include "Database/StoredProcedures.h"
#include "Database/DatabaseReaders.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common;
using namespace Harlinn::ODBC;
using namespace Harlinn;
using namespace Barrelman;
using namespace Barrelman::Data;

class StoredProceduresLocalFixture
{
public:
    WideString DataSource = L"Barrelman";
    WideString DatabaseName = L"Barrelman";

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

    Database::InsertAircraftType( connection, id, name1 );

    auto statementAfterInsert = connection.CreateStatement( );

    auto readerAfterInsert = statementAfterInsert.ExecuteReader<Database::SimpleAircraftTypeDataReader>( Database::SimpleAircraftTypeDataReader::BaseQuery );
    if ( readerAfterInsert->Read( ) )
    {
        const auto& name = readerAfterInsert->Name( );
        
    }
    Database::UpdateAircraftType( connection, id, rowVersion, name2 );

    auto statementAfterUpdate = connection.CreateStatement( );
    auto readerAfterUpdate = statementAfterUpdate.ExecuteReader<Database::SimpleAircraftTypeDataReader>( Database::SimpleAircraftTypeDataReader::BaseQuery );
    if ( readerAfterUpdate->Read( ) )
    {
        const auto& name = readerAfterUpdate->Name( );

    }

}
BOOST_AUTO_TEST_SUITE_END( )