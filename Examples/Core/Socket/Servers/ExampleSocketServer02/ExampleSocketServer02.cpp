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

