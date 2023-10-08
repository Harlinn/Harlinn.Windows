#include "ServerEngine.h"
#include <HExOptionParser.h>
#include <HCCApplication.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Examples;

int main( int argc, char* argv[] )
{
    auto options = std::make_shared<ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    try
    {
        EngineOptions options;
        if ( ParseOptions( argc, argv, options ) )
        {
            ServerEngine engine( options, "TestInstance" );

            WSAInitTerm wsa;
            constexpr DWORD ThreadPoolSize = 12;
            constexpr size_t SocketCount = 200;

            auto context = std::make_shared<IO::Context>( ThreadPoolSize );
            Address address( options.Port );
            
            auto listener = std::make_shared<Server::TcpSimpleListener<Protocol> >( context, address, SocketCount, &engine );

            context->Start( );

            puts( "Press enter to exit" );
            while ( getc( stdin ) != '\n' );

            context->Stop( );

        }
    }
    catch ( std::exception& exc )
    {
        std::string message = exc.what( );
        printf( "Exception: %s", message.c_str( ) );
    }

    application->Stop( );
    return 0;
}

