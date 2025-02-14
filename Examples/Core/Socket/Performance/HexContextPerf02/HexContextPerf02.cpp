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

enum class RequestType : UInt16
{
    Unknown,
    Fault,
    SessionConnect,
    SessionDisconnect,
    SessionWriteValues

};

class RequestReplyBase
{
public:
    template<IO::StreamReader StreamReaderT>
    static RequestType ReadRequestType( IO::BinaryReader<StreamReaderT>& reader )
    {
        return static_cast<RequestType>( reader.Read<UInt16>( ) );
    }
};


template<typename DerivedT>
class Request : public RequestReplyBase
{
public:
    using DerivedType = DerivedT;
private:
    RequestType requestType_;
    UInt64 id_;
protected:
    constexpr Request( RequestType requestType, UInt64 id = 0 ) noexcept
        : requestType_( requestType ), id_( id )
    { }
public:

    constexpr RequestType Kind( ) const noexcept
    {
        return requestType_;
    }
    constexpr UInt64 Id( ) const noexcept
    {
        return id_;
    }
    constexpr void SetId( UInt64 id ) noexcept
    {
        id_ = id;
    }

    void Assign( UInt64 id )
    {
        id_ = id;
    }

    

    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        id_ = reader.Read<UInt64>( );
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        writer.Write( static_cast<UInt16>( requestType_ ) );
        writer.Write( id_ );
    }

};


class SessionConnectRequest : public Request<SessionConnectRequest>
{
public:
    using Base = Request<SessionConnectRequest>;
private:
    Guid sessionId_;
public:
    constexpr SessionConnectRequest( UInt64 id = 0, const Guid& sessionId = Guid() ) noexcept
        : Base( RequestType::SessionConnect, id ), sessionId_( sessionId )
    { }

    void Assign( UInt64 id, const Guid& sessionId = Guid( ) )
    {
        Base::Assign( id );
        sessionId_ = sessionId;
    }

    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        Base::Read( reader );
        sessionId_ = reader.Read<Guid>( );
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        Base::Write( writer );
        writer.Write( sessionId_ );
    }

    constexpr const Guid& SessionId( ) const noexcept
    {
        return sessionId_;
    }
    constexpr void SetSessionId( const Guid& sessionId ) noexcept
    {
        sessionId_ = sessionId;
    }

};




template<typename DerivedT>
class SessionRequest : public Request<DerivedT>
{
public:
    using Base = Request<DerivedT>;
private:
    Guid sessionId_;
public:
    constexpr SessionRequest( RequestType requestType, UInt64 id = 0, const Guid& sessionId = Guid() ) noexcept
        : Base( requestType, id ), sessionId_( sessionId )
    {

    }

    void Assign( UInt64 id, const Guid& sessionId )
    {
        Base::Assign( id );
        sessionId_ = sessionId;
    }

    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        Base::Read( reader );
        sessionId_ = reader.Read<Guid>( );
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        Base::Write( writer );
        writer.Write( sessionId_ );
    }

};



template<typename DerivedT>
class Reply : public RequestReplyBase
{
public:
    using Base = RequestReplyBase;
private:
    RequestType requestType_;
    UInt64 id_;
protected:
    constexpr Reply( RequestType requestType, UInt64 id = 0 ) noexcept
        : requestType_( requestType ), id_( id )
    {
    }
public:
    constexpr RequestType Kind( ) const noexcept
    {
        return requestType_;
    }
    constexpr UInt64 Id( ) const noexcept
    {
        return id_;
    }
    constexpr void SetId( UInt64 id ) noexcept
    {
        id_ = id;
    }

    constexpr void Assign( UInt64 id ) noexcept
    {
        id_ = id;
    }


    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        id_ = reader.Read<UInt64>( );
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        writer.Write( static_cast<UInt16>( requestType_ ) );
        writer.Write( id_ );
    }
};


class FaultReply : public Reply<FaultReply>
{
public:
    using Base = Reply<FaultReply>;
private:
    UInt64 code_;
    std::string message_;
public:
    FaultReply( RequestType requestType, UInt64 id = 0, UInt64 code = 0, const std::string& message = std::string() )
        : Base(RequestType::Fault, id), code_( code ), message_( message )
    {
    }
    FaultReply( RequestType requestType, UInt64 id, UInt64 code, std::string&& message ) noexcept
        : Base( RequestType::Fault, id ), code_( code ), message_( std::move(message) )
    {
    }

    constexpr UInt64 Code( ) const noexcept
    {
        return code_;
    }
    constexpr void SetCode( UInt64 code ) noexcept
    {
        code_ = code;
    }

    constexpr const std::string& Message( ) const noexcept
    {
        return message_;
    }
    void SetMessage( const std::string& message )
    {
        message_ = message;
    }
    void SetMessage( std::string&& message )
    {
        message_ =  std::move(message);
    }

    void Assign( UInt64 id, UInt64 code, const std::string& message = std::string( ) )
    {
        Base::Assign( id );
        code_ = code;
        message_ = message;
    }
    void Assign( UInt64 id, UInt64 code, std::string&& message ) noexcept
    {
        Base::Assign( id );
        code_ = code;
        message_ = std::move(message);
    }

    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        Base::Read( reader );
        reader.Read( code_ );
        reader.Read( message_ );
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        Base::Write( writer );
        writer.Write( code_ );
        writer.Write( message_ );
    }
};

class SessionConnectReply : public Reply<SessionConnectReply>
{
public:
    using Base = Reply<SessionConnectReply>;
private:
    Guid sessionId_;
public:
    SessionConnectReply( UInt64 id = 0, const Guid& sessionId = Guid() )
        : Base( RequestType::SessionConnect, id ), sessionId_( sessionId )
    {
    }

    void Assign( UInt64 id, const Guid& sessionId = Guid( ) )
    {
        Base::Assign( id );
        sessionId_ = sessionId;
    }

    constexpr const Guid& SessionId( ) const noexcept
    {
        return sessionId_;
    }
    constexpr void SetSessionId( const Guid& sessionId ) noexcept
    {
        sessionId_ = sessionId;
    }

    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        Base::Read( reader );
        reader.Read( sessionId_ );
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        Base::Write( writer );
        writer.Write( sessionId_ );
    }

};

class SessionDisconnectRequest : public SessionRequest<SessionDisconnectRequest>
{
public:
    using Base = SessionRequest<SessionDisconnectRequest>;
public:
    constexpr SessionDisconnectRequest( UInt64 id = 0, const Guid& sessionId = Guid( ) ) noexcept
        : Base( RequestType::SessionDisconnect, id, sessionId )
    { }
};

class SessionDisconnectReply : public Reply<SessionDisconnectReply>
{
public:
    using Base = Reply<SessionDisconnectReply>;

    constexpr SessionDisconnectReply( UInt64 id = 0 ) noexcept
        : Base( RequestType::SessionDisconnect, id )
    { }
};

struct Record
{
    Guid id;
    DateTime timestamp;
    Int64 flags;
    double value;

    Record()
        : flags(0), value(0)
    { }

    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        reader.Read( id );
        reader.Read( timestamp );
        reader.Read( flags );
        reader.Read( value );
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        writer.Write( id );
        writer.Write( timestamp );
        writer.Write( flags );
        writer.Write( value );
    }

};



class SessionWriteValuesRequest : public SessionRequest<SessionDisconnectRequest>
{
public:
    using Base = SessionRequest<SessionDisconnectRequest>;
    using RecordArray = std::array<Record, MaxInt16>;
private:
    size_t recordCount_;
    RecordArray records_;
public:
    SessionWriteValuesRequest( UInt64 id = 0, const Guid& sessionId = Guid( ) ) noexcept
        : Base( RequestType::SessionWriteValues, id, sessionId ), recordCount_(0)
    {
    }

    void Assign( UInt64 id, const Guid& sessionId )
    {
        Base::Assign( id, sessionId );
    }


    void Assign( UInt64 id, const Guid& sessionId, size_t recordCount, const RecordArray& records )
    {
        Base::Assign( id, sessionId );
        recordCount_ = recordCount;
        std::copy_n( records.begin( ), recordCount, records_.begin( ) );
    }

    void Assign( size_t recordCount, const RecordArray& records )
    {
        recordCount_ = recordCount;
        std::copy_n( records.begin( ), recordCount, records_.begin( ) );
    }


    constexpr size_t RecordCount( ) const noexcept
    {
        return recordCount_;
    }

    constexpr void SetRecordCount( size_t recordCount ) noexcept
    {
        recordCount_ = recordCount;
    }

    constexpr const RecordArray& Records( ) const noexcept
    {
        return records_;
    }
    constexpr RecordArray& Records( ) noexcept
    {
        return records_;
    }

    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        Base::Read( reader );
        reader.Read( recordCount_ );
        for ( size_t i = 0; i < recordCount_; ++i )
        {
            records_[i].Read( reader );
        }
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        Base::Write( writer );
        writer.Write( recordCount_ );
        for ( size_t i = 0; i < recordCount_; ++i )
        {
            records_[i].Write( writer );
        }
    }

};

class SessionWriteValuesReply : public Reply<SessionWriteValuesReply>
{
public:
    using Base = Reply<SessionWriteValuesReply>;
private:
    size_t recordCount_;
public:
    constexpr SessionWriteValuesReply( UInt64 id = 0, size_t recordCount = 0 ) noexcept
        : Base( RequestType::SessionWriteValues, id ), recordCount_( 0 )
    {
    }

    void Assign( UInt64 id = 0, size_t recordCount = 0 )
    {
        Base::Assign( id );
        recordCount_ = recordCount;
    }
    constexpr size_t RecordCount( ) const noexcept
    {
        return recordCount_;
    }

    constexpr void SetRecordCount( size_t recordCount ) noexcept
    {
        recordCount_ = recordCount;
    }

    template<IO::StreamReader StreamReaderT>
    void Read( IO::BinaryReader<StreamReaderT>& reader )
    {
        Base::Read( reader );
        reader.Read( recordCount_ );
    }

    template<IO::StreamWriter StreamWriterT>
    void Write( IO::BinaryWriter<StreamWriterT>& writer )
    {
        Base::Write( writer );
        writer.Write( recordCount_ );
    }


};


struct ThreadData
{
    Int32 index_;
    Stopwatch stopwatch_;
    EventWaitHandle clientDoneEvent_;
    DateTime startTime_;
    DateTime firstWrite_;
    DateTime stopTime_;
    size_t bytesSent_;

    ThreadData( )
        : index_( 0 ), clientDoneEvent_( true ), bytesSent_( 0 )
    {
    }
};

void Client( ThreadData* threadData, size_t count )
{
    constexpr size_t RecordCount = 1000;
    threadData->startTime_ = DateTime::Now( );
    threadData->stopwatch_.Start( );
    try
    {
        TcpSocket clientSocket( AddressFamily::InterNetworkV6 );
        Address address( 42000 );
        clientSocket.Connect( address );
        IO::MemoryStream memoryStream;

        clientSocket.SetReceiveTimeout( 10000 );
        TcpSocketStream clientSocketStream( clientSocket );


        IO::BinaryReader reader( clientSocketStream );
        IO::BinaryWriter writer( memoryStream );

        UInt64 requestId = 1;
        SessionConnectRequest sessionConnectRequest( requestId );
        sessionConnectRequest.Write( writer );
        clientSocketStream.Write( memoryStream.Buffer( ), memoryStream.Position( ) );
        threadData->bytesSent_ += memoryStream.Position( );
        memoryStream.SetPosition( 0 );

        auto replyType = RequestReplyBase::ReadRequestType( reader );
        SessionConnectReply sessionConnectReply;
        sessionConnectReply.Read( reader );

        auto sessionId = sessionConnectReply.SessionId( );
        UInt64 replyId = sessionConnectReply.Id( );


        auto sessionWriteValuesRequest = std::make_unique<SessionWriteValuesRequest>( );
        sessionWriteValuesRequest->SetRecordCount( RecordCount );
        for ( size_t i = 0; i < RecordCount; ++i )
        {
            sessionWriteValuesRequest->Records( )[i].value = static_cast<double>( i + 1.0 );
        }
        threadData->firstWrite_ = DateTime::Now( );
        SessionWriteValuesReply sessionWriteValuesReply;
        for ( size_t i = 0; i < count; i++ )
        {
            requestId++;
            sessionWriteValuesRequest->Assign( requestId, sessionId );
            sessionWriteValuesRequest->Write( writer );

            clientSocketStream.Write( memoryStream.Buffer( ), memoryStream.Position( ) );
            threadData->bytesSent_ += memoryStream.Position( );
            memoryStream.SetPosition( 0 );

            replyType = RequestReplyBase::ReadRequestType( reader );
            sessionWriteValuesReply.Read( reader );
            replyId = sessionWriteValuesReply.Id( );
        }

        requestId++;
        SessionDisconnectRequest sessionDisconnectRequest( requestId );
        sessionDisconnectRequest.Write( writer );

        clientSocketStream.Write( memoryStream.Buffer( ), memoryStream.Position( ) );
        threadData->bytesSent_ += memoryStream.Position( );
        memoryStream.SetPosition( 0 );
        clientSocket.Shutdown( ShutdownFlag::Send );
        replyType = RequestReplyBase::ReadRequestType( reader );
        SessionDisconnectReply sessionDisconnectReply;
        sessionDisconnectReply.Read( reader );
        clientSocket.Close( );
    }
    HCC_CATCH_ALL_AND_REPORT_EXCEPTION
    threadData->stopwatch_.Stop( );
    threadData->stopTime_ = DateTime::Now( );
    threadData->clientDoneEvent_.Signal( );

}

enum class ProtocolState
{
    Unknown,
    WaitingForClientToConnect,
    WaitingForCommand

};
class Protocol
{
    ProtocolState state_;
    std::vector<ThreadData>& threadData_;
    SessionWriteValuesRequest sessionWriteValuesRequest_;
public:
    Protocol( std::vector<ThreadData>& threadData )
        : state_( ProtocolState::WaitingForClientToConnect ), threadData_( threadData )
    {
    }

    template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
    bool Process( IO::BinaryReader<StreamReaderT>& requestReader,
        IO::BinaryWriter<StreamWriterT>& replyWriter )
    {

        bool result = false;
        switch ( state_ )
        {
            case ProtocolState::WaitingForClientToConnect:
            {
                result = HandleSessionConnect( requestReader, replyWriter );
            }
            break;
            case ProtocolState::WaitingForCommand:
            {
                result = HandleCommand( requestReader, replyWriter );
            }
            break;
        }
        return result;
    }

    template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
    bool HandleSessionConnect( IO::BinaryReader<StreamReaderT>& requestReader,
        IO::BinaryWriter<StreamWriterT>& replyWriter )
    {
        auto requestType = RequestReplyBase::ReadRequestType( requestReader );
        if ( requestType == RequestType::SessionConnect )
        {
            SessionConnectRequest request;
            request.Read( requestReader );
            auto requestedSessionId = request.SessionId( );
            if ( requestedSessionId.IsEmpty( ) )
            {
                requestedSessionId = Guid::NewGuid( );
            }
            SessionConnectReply reply( request.Id( ), requestedSessionId );
            reply.Write( replyWriter );
            state_ = ProtocolState::WaitingForCommand;
            return true;
        }
        else
        {
            state_ = ProtocolState::WaitingForClientToConnect;
            return false;
        }
    }

    template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
    bool HandleCommand( IO::BinaryReader<StreamReaderT>& requestReader,
        IO::BinaryWriter<StreamWriterT>& replyWriter )
    {
        bool result = false;
        auto requestType = RequestReplyBase::ReadRequestType( requestReader );
        switch ( requestType )
        {
            case RequestType::SessionDisconnect:
            {
                result = HandleSessionDisconnect( requestReader, replyWriter );
            }
            break;

            case RequestType::SessionWriteValues:
            {
                result = HandleSessionWriteValues( requestReader, replyWriter );
            }
            break;
        }
        return result;
    }

    template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
    bool HandleSessionDisconnect( IO::BinaryReader<StreamReaderT>& requestReader,
        IO::BinaryWriter<StreamWriterT>& replyWriter )
    {
        SessionDisconnectRequest request;
        request.Read( requestReader );

        SessionDisconnectReply reply( request.Id() );
        reply.Write( replyWriter );
        return false;
    }

    template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
    bool HandleSessionWriteValues( IO::BinaryReader<StreamReaderT>& requestReader,
        IO::BinaryWriter<StreamWriterT>& replyWriter )
    {
        sessionWriteValuesRequest_.Read( requestReader );

        SessionWriteValuesReply reply( sessionWriteValuesRequest_.Id( ), sessionWriteValuesRequest_.RecordCount( ) );
        reply.Write( replyWriter );
        return true;
    }
};


void ContextTest( )
{
#ifndef _DEBUG
    constexpr size_t ClientCount = 1000;
#else
    constexpr size_t ClientCount = 10;
#endif
    constexpr DWORD ThreadPoolSize = 12;
    size_t PerClientRecordCount = 10000;

    std::vector<ThreadData> threadData;
    for ( size_t i = 0; i < ClientCount; i++ )
    {
        threadData.emplace_back( ).index_ = static_cast<Int32>( i );
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
        ThreadData* data = &threadData[i];
        Thread thread( [data, i, PerClientRecordCount]( )
        {
            CurrentThread::SetDescription( L"Client Thread" );
            Client( data, PerClientRecordCount );
        } );
    }

    for ( size_t i = 0; i < ClientCount; i++ )
    {
        auto& threadDataEntry = threadData[i];
        threadDataEntry.clientDoneEvent_.Wait( );
    }
    stopwatch.Stop( );
    context->Stop( );

    auto TotalPoints = ClientCount * PerClientRecordCount;
    auto duration = stopwatch.Elapsed( ).TotalSeconds( );
    auto pointsPerSecond = ( TotalPoints ) / duration;
    //auto gbPerSecond = ( pointsPerSecond * sizeof( Record ) ) / ( 1024ll * 1024 * 1024 );
    
    size_t bytesSent = 0;
    DateTime endDateTime = DateTime::Now( );
    DateTime firstStartTime = endDateTime;
    std::ranges::for_each( threadData, [&firstStartTime,&bytesSent]( const ThreadData& threadData )
    {
        bytesSent += threadData.bytesSent_;
        if ( threadData.startTime_ < firstStartTime  )
        {
            firstStartTime = threadData.startTime_;
        }
    } );


    auto bytesSentPerSecond = bytesSent / duration;
    auto gbPerSecond = ( bytesSentPerSecond ) / ( 1024ll * 1024 * 1024 );

    DateTime lastFirstWrite = firstStartTime;
    std::ranges::for_each( threadData, [&lastFirstWrite]( const ThreadData& threadData )
    {
        if ( threadData.firstWrite_ > lastFirstWrite )
        {
            lastFirstWrite = threadData.firstWrite_;
        }
    } );

    auto allServedOnce = lastFirstWrite - firstStartTime;
    auto allServedOnceSeconds = allServedOnce.TotalSeconds( );
    auto totalMessages = TotalPoints + ( ClientCount * 2 );
    auto messagesPerSecond = totalMessages / duration;



    wprintf( L"Server processed %llu distinct messages in %f seconds using %llu concurrent client(s), %f GB per second, %f messages per second. All clients served at least once in %f seconds.\n", totalMessages, duration, ClientCount, gbPerSecond, messagesPerSecond,allServedOnceSeconds );


}



int main( )
{
    auto options = std::make_shared<ApplicationOptions>( );
    options->Load( );
    auto application = std::make_shared<Application>( options );
    application->Start( );

    WSAInitTerm wsa;
    ContextTest( );

    application->Stop( );
}

