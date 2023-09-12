// ZeroMqNCSClient1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HCCDef.h"
#include "HCCZMQ.h"
#include "HCCBinaryReader.h"
#include "HCCBinaryWriter.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::ZeroMq;

void SendCommand( ZMQNotificationClient& client, const WideString& commandString, const WideString& argumentString )
{
    ZMQWriteStream zmqWriteStream( client.ClientSocket( ) );
    IO::BinaryWriter<ZMQWriteStream> writer( zmqWriteStream );
    writer.Write( commandString );
    writer.Write( argumentString );
    zmqWriteStream.Flush( );
    Message message;
    client.Receive( message );
}

int main()
{
    try
    {
        WideString notificationEndpoint = L"tcp://127.0.0.1:42501";
        AnsiString serverEndpoint = "tcp://127.0.0.1:42500";
        AnsiString notificationListenEndpoint = "tcp://*:42501";
        AnsiString notificationListenInprocEndpoint = "inproc://notify-inproc";

        Context context;
        ZMQNotificationClient client( context, L"TestClient1", serverEndpoint, notificationListenEndpoint, notificationListenInprocEndpoint );
        client.Start( );

        client.OnProcess.connect( []( ZMQServer* sender, ZMQReadStream& requestStream, ZMQWriteStream& replyStream, ZMQWriteStream& errorStream )
            {
                IO::BinaryReader<ZMQReadStream> reader( requestStream );
                auto str = reader.Read<WideString>( );
                wprintf( L"Received: %s\n", str.c_str( ) );
            } );

        
        client.Connect( );
        SendCommand( client, L"add", notificationEndpoint );
        SendCommand( client, L"echo", L"first" );
        SendCommand( client, L"echo", L"second" );
        SendCommand( client, L"echo", L"third" );
        SendCommand( client, L"remove", notificationEndpoint );
        client.Disconnect( );
        client.Stop( );
    }
    catch ( std::exception& exc )
    {
        auto message = exc.what( );
        puts( message );
    }
}

