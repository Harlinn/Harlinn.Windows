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

#include "pch.h"
#include "HCCZMQ.h"


using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::ZeroMq;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };


    


}

BOOST_FIXTURE_TEST_SUITE( ZMQTests, LocalFixture )



// --run_test=ZMQTests/ServerStartStopTest1
BOOST_AUTO_TEST_CASE( ServerStartStopTest1 )
{
    try
    {
        AnsiString serverEndpoint{ "tcp://*:42500" };
        AnsiString serverInprocEndpoint{ "inproc://server-inproc" };
        Context context;
        ZMQServer server( context, L"TestServer", serverEndpoint, serverInprocEndpoint );
        server.Start( );
        server.Stop( );
    }
    catch ( std::exception& exc )
    {
        auto message = exc.what( );
        puts( message );
    }
}

// --run_test=ZMQTests/NotificationClientServerTest1
BOOST_AUTO_TEST_CASE( NotificationClientServerTest1 )
{
    try
    {
        WideString receivedOnServer;
        WideString receivedOnClient1;
        WideString receivedOnClient2;
        EventWaitHandle eventWaitHandle1( true );
        EventWaitHandle eventWaitHandle2( true );

        AnsiString serverListenEndpoint{ "tcp://*:42500" };
        AnsiString serverListenInprocEndpoint{ "inproc://server-inproc" };

        AnsiString notificationListenEndpoint1{ "tcp://*:42501" };
        AnsiString notificationListenInprocEndpoint1{ "inproc://notify-inproc1" };

        AnsiString notificationListenEndpoint2{ "tcp://*:42502" };
        AnsiString notificationListenInprocEndpoint2{ "inproc://notify-inproc2" };

        AnsiString serverEndpoint{ "tcp://127.0.0.1:42500" };
        AnsiString notificationEndpoint1{ "tcp://127.0.0.1:42501" };
        AnsiString notificationEndpoint2{ "tcp://127.0.0.1:42502" };

        Context context;
        ZMQNotificationServer server( context, L"TestServer", serverListenEndpoint, serverListenInprocEndpoint );
        server.Start( );

        ZMQNotificationClient client1( context, L"TestClient1", serverEndpoint, notificationListenEndpoint1, notificationListenInprocEndpoint1 );

        ZMQNotificationClient client2( context, L"TestClient2", serverEndpoint, notificationListenEndpoint2, notificationListenInprocEndpoint2 );

        server.OnProcess.connect( [&receivedOnServer ]( ZMQServer* sender, IO::MemoryStream& requestStream, IO::MemoryStream& replyStream, IO::MemoryStream& errorStream )
            {
                printf( "In Server\n" );
                ZMQNotificationServer* notificationServer = static_cast< ZMQNotificationServer* >( sender );
                IO::BinaryReader<IO::MemoryStream> reader( requestStream );
                auto str = reader.Read<WideString>( );
                receivedOnServer = str;

                auto notification = std::make_shared<ZMQNotificationMemoryStream>( );
                IO::BinaryWriter<ZMQNotificationMemoryStream> writer( *notification );
                writer.Write( str );
                wprintf( L"Publishing %s\n", str.c_str( ) );
                notificationServer->Publish( notification );
            } );

        client1.OnProcess.connect( [&receivedOnClient1, &eventWaitHandle1 ]( ZMQServer* sender, IO::MemoryStream& requestStream, IO::MemoryStream& replyStream, IO::MemoryStream& errorStream )
            {
                printf( "In Client1\n" );
                IO::BinaryReader<IO::MemoryStream> reader( requestStream );
                auto str = reader.Read<WideString>( );
                receivedOnClient1 = str;
                eventWaitHandle1.Signal( );
            } );

        client2.OnProcess.connect( [&receivedOnClient2, &eventWaitHandle2 ]( ZMQServer* sender, IO::MemoryStream& requestStream, IO::MemoryStream& replyStream, IO::MemoryStream& errorStream )
            {
                printf( "In Client2\n" );
                IO::BinaryReader<IO::MemoryStream> reader( requestStream );
                auto str = reader.Read<WideString>( );
                receivedOnClient2 = str;
                eventWaitHandle2.Signal( );
            } );

        client1.Start( );
        client2.Start( );

        client1.Connect( );
        client2.Connect( );

        server.AddClient( notificationEndpoint1 );
        server.AddClient( notificationEndpoint2 );

        ZMQWriteStream zmqWriteStream( client1.ClientSocket() );
        IO::BinaryWriter<ZMQWriteStream> writer( zmqWriteStream );

        WideString text{ L"Message" };

        writer.Write( text );
        zmqWriteStream.Flush( );
        Message replyMessage;
        client1.Receive( replyMessage );

        eventWaitHandle1.Wait( );
        eventWaitHandle2.Wait( );

        eventWaitHandle1.Reset( );
        eventWaitHandle2.Reset( );

        client2.Disconnect( );
        client1.Disconnect( );

        client2.Stop( );
        client1.Stop( );

        server.Stop( );
        
        context.Shutdown( );
        //context.Close( );
        printf( "Done\n" );
    }
    catch ( std::exception& exc )
    {
        auto message = exc.what( );
        puts( message );
    }
}



BOOST_AUTO_TEST_SUITE_END( )