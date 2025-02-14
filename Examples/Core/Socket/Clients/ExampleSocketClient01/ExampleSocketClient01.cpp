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


#include <HCCThread.h>
#include <HCCIOContext.h>
#include <HCCSocket.h>
#include <HCCGuid.h>
#include <HCCApplication.h>

#include <HExTypes.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::IO::Sockets;
using namespace Harlinn::Common::Core::Examples;

int main()
{
    auto options = std::make_shared<Harlinn::Common::Core::ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    WSAInitTerm wsa;
#ifdef _DEBUG
    size_t recordCount = 100;
    size_t batchSize = 20;
#else
    size_t recordCount = 1'000'000'000;
    size_t batchSize = 20'000;
#endif
    Socket clientSocket( AddressFamily::InterNetworkV6, SocketType::Stream, ProtocolType::Tcp );
    Address address( 42000 );
    clientSocket.Connect( address );

    clientSocket.Send( &recordCount, sizeof( recordCount ), MessageFlags::None );

    Int32 index = 1;
    clientSocket.Send( &index, sizeof( index ), MessageFlags::None );

    std::vector<SensorValue> records;
    records.resize( batchSize, SensorValue{ Guid( ), DateTime( static_cast<Int64>( index + 1 ) ),index + 3, 4.0 } );
    size_t sent = 0;
    while ( sent < recordCount )
    {
        clientSocket.Send( records.data( ), records.size( ) * sizeof( SensorValue ), MessageFlags::None );
        sent += records.size( );
    }
    clientSocket.Disconnect( );
    //puts( "Press enter to exit" );
    //while ( getc( stdin ) != '\n' );

    application->Stop( );

}

