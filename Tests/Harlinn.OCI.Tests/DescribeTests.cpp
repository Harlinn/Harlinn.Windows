#include <HOCI.h>
#include <HCCXml.h>
#include <HCCIO.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <OCITestFixture.h>

using namespace Harlinn::Common;
using namespace Harlinn::OCI;
using namespace Harlinn;

BOOST_FIXTURE_TEST_SUITE( DescribeTests, LocalFixture )

// --run_test=DescribeTests/ExecuteTest1
BOOST_AUTO_TEST_CASE( ExecuteTest1 )
{
    EnvironmentOptions options;
    OCI::Environment environment( options );

    auto server = environment.CreateServer( );
    auto serviceContext = server.CreateServiceContext( Username, Password, Alias );
    serviceContext.SessionBegin( );

    Metadata::Database database( serviceContext );

    size_t schemaObjectCount = 0;
    size_t columnCount = 0;
    auto schemas = database.Schemas( );
    for ( const auto& schemaEntry : schemas )
    {
        const auto& schema = schemaEntry.second;
        auto schemaObjects = schema->Objects( );

        for ( const auto& schemaObjectEntry : schemaObjects )
        {
            const auto& schemaObject = schemaObjectEntry.second;
            auto kind = schemaObject->Kind( );
            switch ( kind )
            {
                case Metadata::Kind::Table:
                case Metadata::Kind::View:
                {
                    auto* tableOrView = static_cast<Metadata::TableOrView*>( schemaObject.get() );
                    auto columns = tableOrView->Columns( );
                    columnCount += columns.size( );
                }
                break;
            }
        }

        schemaObjectCount += schemaObjects.size( );
    }



    serviceContext.SessionEnd( );
}

BOOST_AUTO_TEST_SUITE_END( )