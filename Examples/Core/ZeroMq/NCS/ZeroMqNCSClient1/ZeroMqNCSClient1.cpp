/*
   Copyright 2024-2026 Espen Harlinn

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
    IO::MemoryStream writeStream;
    IO::BinaryWriter<IO::MemoryStream> writer( writeStream );
    writer.Write( commandString );
    writer.Write( argumentString );
    client.Send( writeStream );
    Message message;
    client.Receive( message );
}

void SendCommand( ZMQNotificationClient& client, const wchar_t* commandString, const WideString& argumentString )
{
    SendCommand( client, WideString( commandString ), argumentString );
}
void SendCommand( ZMQNotificationClient& client, const wchar_t* commandString, const wchar_t* argumentString )
{
    SendCommand( client, WideString( commandString ), WideString( argumentString ) );
}

int main()
{
    try
    {
        WideString notificationEndpoint{ L"tcp://127.0.0.1:42501" };
        AnsiString serverEndpoint{ "tcp://127.0.0.1:42500" };
        AnsiString notificationListenEndpoint{ "tcp://*:42501" };
        AnsiString notificationListenInprocEndpoint{ "inproc://notify-inproc" };

        Context context;
        ZMQNotificationClient client( context, L"TestClient1", serverEndpoint, notificationListenEndpoint, notificationListenInprocEndpoint );
        client.Start( );

        client.OnProcess.connect( []( ZMQServer* sender, IO::MemoryStream& requestStream, IO::MemoryStream& replyStream, IO::MemoryStream& errorStream )
            {
                IO::BinaryReader<IO::MemoryStream> reader( requestStream );
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

