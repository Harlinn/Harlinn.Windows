// ZeroMqNCSServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HCCDef.h"
#include "HCCZMQ.h"
#include "HCCBinaryReader.h"
#include "HCCBinaryWriter.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::ZeroMq;

int main()
{
    try
    {
        AnsiString serverListenEndpoint = "tcp://*:42500";
        AnsiString serverListenInprocEndpoint = "inproc://server-inproc";

        Context context;
        ZMQNotificationServer server( context, L"TestServer", serverListenEndpoint, serverListenInprocEndpoint );
        server.Start( );

        server.OnProcess.connect( []( ZMQServer* sender, ZMQReadStream& requestStream, ZMQWriteStream& replyStream, ZMQWriteStream& errorStream )
            {
                printf( "In Server\n" );
                ZMQNotificationServer* notificationServer = static_cast< ZMQNotificationServer* >( sender );
                IO::BinaryReader<ZMQReadStream> reader( requestStream );
                auto commandStr = reader.Read<WideString>( );
                auto argumentStr = reader.Read<WideString>( );

                if ( commandStr == L"add" )
                {
                    wprintf( L"add %s\n", argumentStr.c_str( ) );
                    notificationServer->AddClient( ToAnsiString( argumentStr ) );
                }
                else if ( commandStr == L"remove" )
                {
                    wprintf( L"remove %s\n", argumentStr.c_str( ) );
                    notificationServer->RemoveClient( ToAnsiString( argumentStr ) );
                }
                else if ( commandStr == L"echo" )
                {
                    auto notification = std::make_shared<ZMQNotificationMemoryStream>( );
                    IO::BinaryWriter<ZMQNotificationMemoryStream> writer( *notification );
                    writer.Write( argumentStr );
                    wprintf( L"echo %s\n", argumentStr.c_str( ) );
                    notificationServer->Publish( notification );
                }

            } );

        printf( "Press any key to exit...\n" );
        getc( stdin );

        server.Stop( );
    }
    catch ( std::exception& exc )
    {
        auto message = exc.what( );
        puts( message );
    }

}

