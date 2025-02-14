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
#include <HCCSocketServer.h>
#include <HCCGuid.h>
#include <HCCApplication.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::IO::Sockets;

struct Record
{
    Guid id;
    DateTime timestamp;
    Int64 flags;
    double value;
};

struct ThreadData
{
    Int32 index;
    Stopwatch stopwatch;
    EventWaitHandle serverDoneEvent;

    ThreadData( )
        : index( 0 ), serverDoneEvent( true )
    {
    }
};

void Client( ThreadData& threadData, size_t count )
{
    TcpSocket clientSocket( AddressFamily::INetV6 );
    Address address( 42000 );
    clientSocket.Connect( address );

    clientSocket.Send( &count, sizeof( count ),MessageFlags::None );

    Int32 index = static_cast<Int32>( threadData.index );
    clientSocket.Send( &index, sizeof( index ), MessageFlags::None );

    std::vector<Record> records;
    records.resize( 2000, Record{ Guid( ), DateTime( static_cast<Int64>( index + 1 ) ),index + 1, 1.0 } );
    size_t sent = 0;
    while ( sent < count )
    {
        clientSocket.Send( records.data( ), records.size( ) * sizeof( Record ), MessageFlags::None );
        sent += records.size( );
    }
}


class Protocol
{
    std::vector<ThreadData>& threadData_;
public:
    Protocol( std::vector<ThreadData>& threadData )
        : threadData_(threadData )
    { }

    template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
    bool Process( IO::BinaryReader<StreamReaderT>& requestReader, 
        IO::BinaryWriter<StreamWriterT>& replyWriter )
    {
        std::vector<Record> records;
        records.resize( 200000 );

        size_t count = requestReader.Read<UInt64>( );
        Int32 index = requestReader.Read<Int32>( );

        size_t received = 0;
        while ( received < count )
        {
            requestReader.Read( records.data( ), records.size( ) * sizeof( Record ) );
            received += records.size( );
        }
        auto& entry = threadData_[index];
        entry.stopwatch.Stop( );
        entry.serverDoneEvent.Signal( );
        return false;
    }
};


void ContextTest2( )
{
    constexpr size_t ClientCount = 100;
    constexpr DWORD ThreadPoolSize = 12;
    size_t PerClientRecordCount = 100'000'000;

    std::vector<ThreadData> threadData;
    for ( size_t i = 0; i < ClientCount; i++ )
    {
        threadData.emplace_back( ).index = static_cast<Int32>( i );
    }

    auto context = std::make_shared<IO::Context>( ThreadPoolSize );
    Address address( 42000 );
    auto listener = std::make_shared<Server::TcpSimpleListener<Protocol>>( context, address, ClientCount, threadData );
    context->Add( listener );
    context->Start( );

    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( size_t i = 0; i < ClientCount; i++ )
    {
        Thread thread( [&threadData, i, PerClientRecordCount]( )
        {
            Client( threadData[i], PerClientRecordCount );
        } );
    }

    for ( size_t i = 0; i < ClientCount; i++ )
    {
        auto& threadDataEntry = threadData[i];
        threadDataEntry.serverDoneEvent.Wait( );
    }
    stopwatch.Stop( );
    context->Stop( );

    auto TotalPoints = ClientCount * PerClientRecordCount;
    auto duration = stopwatch.Elapsed( ).TotalSeconds( );
    auto pointsPerSecond = ( TotalPoints ) / duration;
    auto gbPerSecond = ( pointsPerSecond * sizeof( Record ) ) / ( 1024ll * 1024 * 1024 );

    wprintf( L"Sent %llu records in %f seconds using %llu concurrent client(s), %f GB per second.\n", TotalPoints, duration, ClientCount, gbPerSecond );

    
}

void ContextTest3( )
{
    constexpr size_t ClientCount = 4;
    constexpr DWORD ThreadPoolSize = 12;
    size_t PerClientRecordCount = 100'000'000;

    std::vector<ThreadData> threadData;

    for ( size_t i = 0; i < ClientCount; i++ )
    {
        auto& element = threadData.emplace_back( );
        element.index = static_cast<Int32>( i );
    }

    auto context = std::make_shared<IO::Context>( ThreadPoolSize );
    Address address( 42000 );
    auto listener = std::make_shared<Server::TcpSimpleListener<Protocol>>( context, address, ClientCount, threadData );
    context->Add( listener );
    context->Start( );

    Stopwatch stopwatch;
    stopwatch.Start( );
    for ( size_t i = 0; i < ClientCount; i++ )
    {
        Thread thread( [&threadData, i, PerClientRecordCount]( )
        {
            Client( threadData[i], PerClientRecordCount );
        } );
    }

    for ( size_t i = 0; i < ClientCount; i++ )
    {
        auto& threadDataEntry = threadData[i];
        threadDataEntry.serverDoneEvent.Wait( );
    }
    stopwatch.Stop( );
    context->Stop( );

    auto TotalPoints = ClientCount * PerClientRecordCount;
    auto duration = stopwatch.Elapsed( ).TotalSeconds( );
    auto pointsPerSecond = ( TotalPoints ) / duration;
    auto gbPerSecond = ( pointsPerSecond * sizeof( Record ) ) / ( 1024ll * 1024 * 1024 );

    wprintf( L"Sent %llu records in %f seconds using %llu concurrent client(s), %f GB per second.\n", TotalPoints, duration, ClientCount, gbPerSecond );

}


int main()
{
    auto options = std::make_shared<ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    WSAInitTerm wsa;
    ContextTest2( );
    ContextTest3( );

    application->Stop( );

}

