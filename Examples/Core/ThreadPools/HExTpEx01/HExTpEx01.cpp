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


#include <HCCIO.h>

int main( )
{
    puts( "Windows threadpool API is currently not supported, but this may change at a later date." );
    return -1;
}
/*
#include "HExTpEx01.h"
#include <HCCApplication.h>


int main()
{
    ApplicationOptions options;
    options.Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    std::set_terminate( []( ) {printf( "C++ terminate\n" ); } );
    try
    {
        IO::Sockets::WSA wsa;
        ThreadPools::Environment environment;

        {

            EventWaitHandle event( true );
            environment.TrySubmit( [&event]( )
            {
                printf( "In TrySubmit callback\n" );
                event.Signal( );
            } );
            printf( "Waiting for TrySubmit callback\n" );
            event.Wait( );
        }

        {
            ThreadPools::TimerDispatcher timerDispatcher( environment );

            EventWaitHandle event( true );
            timerDispatcher.OnCallback.connect( [&event]( const ThreadPools::TimerDispatcher& dispatcher, const ThreadPools::CallbackInstance& instance )
            {
                printf( "In TimerDispatcher callback\n" );
                event.Signal( );
            } );
            timerDispatcher.SetTimer( TimeSpan::FromSeconds( 1 ), 0, 0 );
            printf( "Waiting\n" );
            event.Wait( );
            timerDispatcher.WaitForCallbacks( );
            printf( "Done with TimerDispatcher\n" );
        }

        {
            ThreadPools::WorkDispatcher dispatcher( environment );

            EventWaitHandle event1( true );
            EventWaitHandle event2( true );
            dispatcher.OnCallback.connect( [&event1, &event2 ]( const ThreadPools::WorkDispatcher& dispatcher, const ThreadPools::CallbackInstance& instance )
            {
                printf( "In WorkDispatcher callback\n" );
                printf( "Waiting in callback\n" );
                event1.Wait( );
                event2.Signal( );
            } );
            dispatcher.Submit();
            
            event1.Signal( );
            printf( "Waiting in main\n" );
            event2.Wait( );
            dispatcher.WaitForCallbacks( );
            printf( "Done with WorkDispatcher\n" );
        }

        {
            ThreadPools::WaitDispatcher dispatcher( environment );

            EventWaitHandle event1( true );
            EventWaitHandle event2( true );
            dispatcher.OnCallback.connect( [&event2]( const ThreadPools::WaitDispatcher& dispatcher, const ThreadPools::CallbackInstance& instance, bool timedout )
            {
                printf( "In WaitDispatcher callback\n" );
                event2.Signal( );
            } );
            dispatcher.SetWait(event1.GetHandle());

            event1.Signal( );
            printf( "Waiting in main\n" );
            event2.Wait( );
            dispatcher.WaitForCallbacks( );
            printf( "Done with WaitDispatcher\n" );
        }

        {
            auto filename = IO::Path::GetTemporary( ) + L"HExTpEx01.txt";

            IO::FileStream fileStream( filename, 
                IO::FileAccess::Default, 
                IO::FileShare::Default,
                IO::FileMode::OpenOrCreate,
                IO::FileAttributes::Normal, 
                IO::FileOptions::Asynchronous | IO::FileOptions::DeleteOnClose );

            ThreadPools::FileDispatcher dispatcher( fileStream.Handle(), environment );
            const char* textToWrite = "Some text to write to the file";
            UInt32 numberOfBytesToWrite = 30;
            void* buffer = const_cast<char*>(textToWrite);

            ThreadPools::WriteFileRequest writeFileRequest( fileStream.Handle( ), 0, buffer, numberOfBytesToWrite );

            EventWaitHandle writeDoneEvent( true );
            dispatcher.OnWrite.connect( [&writeDoneEvent]( const ThreadPools::FileDispatcher& dispatcher, const ThreadPools::CallbackInstance& instance, ThreadPools::WriteFileRequest* request )
            {
                printf( "Write done\n" );
                writeDoneEvent.Signal( );
                
            } );

            dispatcher.BeginWrite( writeFileRequest );
            printf( "Waiting for Write\n" );
            writeDoneEvent.Wait( );

            std::string str;
            str.resize( numberOfBytesToWrite );

            ThreadPools::ReadFileRequest readFileRequest( fileStream.Handle( ), 0, str.data(), numberOfBytesToWrite );
            EventWaitHandle readDoneEvent( true );
            dispatcher.OnRead.connect( [&readDoneEvent]( const ThreadPools::FileDispatcher& dispatcher, const ThreadPools::CallbackInstance& instance, ThreadPools::ReadFileRequest* request )
            {
                printf( "Read done\n" );
                readDoneEvent.Signal( );
            } );
            dispatcher.BeginRead( readFileRequest );
            printf( "Waiting for Read\n" );
            readDoneEvent.Wait( );

            bool isEqual = str == textToWrite;
            if ( isEqual )
            {
                printf( "Equal\n" );
            }
            else
            {
                printf( "Not equal\n" );
            }
        }


        {
            IO::Sockets::Address address( 42000 );
            TCPSimpleServer simpleServer( address, 12, environment );
            simpleServer.Start( );
            TCPClient client( environment );
            EventWaitHandle clientDisconnectedEvent( true );
            client.OnDisconnected.connect( [&clientDisconnectedEvent]( )
            {
                clientDisconnectedEvent.Signal( );
            } );
            client.Start( address );
            clientDisconnectedEvent.Wait( );
            simpleServer.Stop( );
            auto numberOfRecordsSent = client.NumberOfRecordsSent( );
            auto numberOfRecordsReceivedByServer = client.NumberOfRecordsReceivedByServer( );
            auto duration = client.Duration( );
            double recordsPresecond = numberOfRecordsReceivedByServer / duration;
            printf( "Client sent %zu, server received %zu in %f seconds - records per second %f\n", numberOfRecordsSent, numberOfRecordsReceivedByServer, duration, recordsPresecond );



        }


    }
    catch ( std::exception& exc )
    {
        auto what = exc.what( );
        printf( "Exception caught in main:%s\n", what );
    }
    application->Stop( );
}
*/
