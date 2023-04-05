#include "pch.h"

using namespace Harlinn::Common::Core;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        {
        }
        ~LocalFixture( )
        {
        }
    };
}

BOOST_FIXTURE_TEST_SUITE( SerialPortTests, LocalFixture )

// --run_test=SerialPortTests/SerialPortsTest1
BOOST_AUTO_TEST_CASE( SerialPortsTest1 )
{
    IO::SerialPorts serialPorts;

    for ( const auto& serialPort : serialPorts )
    {
        std::wcout << serialPort.Name( ) << std::endl;
        auto commConfig = serialPort.DefaultConfig( );
        auto configData = commConfig.data( );
        if ( configData )
        {
            std::wcout << L"Found config data" << std::endl;
        }
    }
}


BOOST_AUTO_TEST_SUITE_END( )