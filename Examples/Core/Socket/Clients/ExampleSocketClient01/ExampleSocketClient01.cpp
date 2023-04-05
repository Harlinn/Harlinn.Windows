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
    ApplicationOptions options;
    options.Load( );
    Application application( options );
    application.Start( );

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

    clientSocket.Write( &recordCount, sizeof( recordCount ) );

    Int32 index = 1;
    clientSocket.Write( &index, sizeof( index ) );

    std::vector<SensorValue> records;
    records.resize( batchSize, SensorValue{ Guid( ), DateTime( static_cast<Int64>( index + 1 ) ),index + 3, 4.0 } );
    size_t sent = 0;
    while ( sent < recordCount )
    {
        clientSocket.Write( records.data( ), records.size( ) * sizeof( SensorValue ) );
        sent += records.size( );
    }
    clientSocket.Disconnect( );
    //puts( "Press enter to exit" );
    //while ( getc( stdin ) != '\n' );

    application.Stop( );

}

