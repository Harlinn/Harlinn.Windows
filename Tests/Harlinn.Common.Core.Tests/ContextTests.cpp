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

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::IO::Sockets;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( ContextTests, LocalFixture )

// --run_test=ContextTests/ContextTest1
BOOST_AUTO_TEST_CASE( ContextTest1 )
{
    EventWaitHandle event( true );
    IO::Context context( 8 );
    context.Start( );
    context.Async( [&event]( )
    {
        event.Signal( );
    } );
    BOOST_CHECK( event.Wait() );
    context.Stop( );
}


// --run_test=ContextTests/FileWriteReadTest1
BOOST_AUTO_TEST_CASE( FileWriteReadTest1 )
{
    EventWaitHandle event( true );
    auto context = std::make_shared<IO::Context>( 8 );
    context->Start( );

    auto filename = IO::Directory::GetTemporary( ) + L"HExTpEx01.txt";

    IO::FileStream fileStream( filename,
        IO::FileAccess::Default,
        IO::FileShare::Default,
        IO::FileMode::OpenOrCreate,
        IO::FileAttributes::Normal,
        IO::FileOptions::Asynchronous | IO::FileOptions::DeleteOnClose );

    auto dispatcher = std::make_shared<IO::FileDispatcher>( context, fileStream );
    const char* textToWrite = "Some text to write to the file";
    UInt32 numberOfBytesToWrite = 30;
    Byte* buffer = (Byte*)textToWrite;

    IO::WriteFileRequest writeFileRequest( fileStream.Handle(), buffer, numberOfBytesToWrite );

    EventWaitHandle writeDoneEvent( true );
    dispatcher->OnWriteCompleted.connect( [&writeDoneEvent]( const IO::FileDispatcher& dispatcher, IO::WriteFileRequest* request )
    {
        printf( "Write done\n" );
        writeDoneEvent.Signal( );

    } );

    dispatcher->BeginAsyncWrite( &writeFileRequest );
    printf( "Waiting for Write\n" );
    writeDoneEvent.Wait( );

    AnsiString str;
    str.resize( numberOfBytesToWrite );

    IO::ReadFileRequest readFileRequest( fileStream.Handle( ), (Byte*)str.data( ), numberOfBytesToWrite );
    EventWaitHandle readDoneEvent( true );
    dispatcher->OnReadCompleted.connect( [&readDoneEvent]( const IO::FileDispatcher& dispatcher, const IO::ReadFileRequest* request )
    {
        printf( "Read done\n" );
        readDoneEvent.Signal( );
    } );
    dispatcher->BeginAsyncRead( &readFileRequest );
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
    

    context->Stop( );
}





BOOST_AUTO_TEST_SUITE_END( )