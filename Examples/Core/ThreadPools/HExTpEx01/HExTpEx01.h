#pragma once
#ifndef __HEXTPEX01_H__
#define __HEXTPEX01_H__

#include <HCCThreadpools.h>
#include <HCCIO.h>
#include <HExTypes.h>


using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Examples;

//constexpr size_t TotalSensorValueCount = 1'000'000'000;
constexpr size_t TotalSensorValueCount = 100'000'000;
constexpr size_t SensorValueBatchSize = 200'000;

//constexpr size_t TotalSensorValueCount = 100;
//constexpr size_t SensorValueBatchSize = 20;

// # define LOG_USING_PRINTF


#pragma pack(push,1)
struct SensorDataHeader
{
    size_t Count;
    UInt32 Index;

    SensorDataHeader( )
        : Count(0), Index(0)
    { }
    SensorDataHeader( size_t count, UInt32 index )
        : Count( count ), Index( index )
    { }
};
#pragma pack(pop)

class ClientConnectRequest : public ThreadPools::SocketConnectRequest
{
public:
    using Base = ThreadPools::SocketConnectRequest;
public:
    ClientConnectRequest( const Socket& socket, const AddressType& addr, void* buffer, UInt32 numberOfBytesToSend )
        : Base( socket, addr, buffer, numberOfBytesToSend )
    {
        
    }
};


class ClientReceiveRequest : public ThreadPools::SocketReceiveRequest
{
public:
    using Base = ThreadPools::SocketReceiveRequest;
private:
    WSABUF wsaBuf_;
public:
    ClientReceiveRequest( const Socket& socket, void* buffer, UInt32 numberOfBytesToReceive )
        : Base( socket, &wsaBuf_, 1, MessageFlags::None ),
          wsaBuf_{ numberOfBytesToReceive, (CHAR*)buffer }
    {
    }

    UInt32 NumberOfBytesToReceive( ) const
    {
        return wsaBuf_.len;
    }

    Byte* Buffer( ) const
    {
        return (Byte*)wsaBuf_.buf;
    }
};

class ClientSendRequest : public ThreadPools::SocketSendRequest
{
public:
    using Base = ThreadPools::SocketSendRequest;
private:
    WSABUF wsaBuf_;
public:
    ClientSendRequest( const Socket& socket, void* buffer, UInt32 numberOfBytesToSend )
        : Base( socket, &wsaBuf_, 1, MessageFlags::None ),
          wsaBuf_{ numberOfBytesToSend, (CHAR*)buffer }
    {
        
    }

    UInt32 NumberOfBytesToSend( ) const
    {
        return wsaBuf_.len;
    }

    Byte* Buffer( ) const
    {
        return (Byte*)wsaBuf_.buf;
    }

};


class ClientDisconnectRequest : public ThreadPools::SocketDisconnectRequest
{
public:
    using Base = ThreadPools::SocketDisconnectRequest;

    ClientDisconnectRequest( const Socket& socket, bool reuse )
        : Base( socket, reuse )
    {
    }
};



class TCPClient : public ThreadPools::SocketHandler<TCPClient>
{
    template<typename DerivedT>
    friend class SocketHandler;
public:
    using Base = ThreadPools::SocketHandler<TCPClient>;
private:
    Base::Socket socket_;
    SensorDataHeader header_;
    size_t headerBytesSent_;
    std::vector<SensorValue> records_;
    size_t numberOfRecordsSent_ = 0;
    size_t numberOfRecordsReceivedByServer_ = 0;
    Stopwatch stopwatch_;
    std::unique_ptr<ClientConnectRequest> connectRequest_;
    std::unique_ptr<ClientReceiveRequest> receiveRequest_;
    std::unique_ptr<ClientSendRequest> sendRequest_;
    std::unique_ptr<ClientDisconnectRequest> disconnectRequest_;
public:
    boost::signals2::signal<void( )> OnDisconnected;

    TCPClient( Base::Socket&& socket, ThreadPools::Environment& environment )
        : Base( socket, environment ), socket_( std::move( socket ) ), header_( TotalSensorValueCount, 1 ), headerBytesSent_(0)
    {
        records_.resize( SensorValueBatchSize, SensorValue{ Guid( ), DateTime( static_cast<Int64>( header_.Index + 1 ) ),header_.Index + 1, 1.0 } );
    }

    TCPClient( IO::Sockets::AddressFamily addressFamily, ThreadPools::Environment& environment )
        : TCPClient( Base::Socket( addressFamily,
            IO::Sockets::SocketType::Stream,
            IO::Sockets::ProtocolType::Tcp,
            IO::Sockets::SocketFlags::Overlapped ), environment )
    {
    }

    TCPClient( ThreadPools::Environment& environment )
        : TCPClient( IO::Sockets::AddressFamily::InterNetworkV6, environment )
    {
    }

    const Base::Socket& Socket( ) const
    {
        return socket_;
    }

    ClientConnectRequest* ConnectRequest( const IO::Sockets::Address& address, void* buffer, UInt32 numberOfBytesToSend )
    {
        if ( !connectRequest_ )
        {
            connectRequest_ = std::make_unique<ClientConnectRequest>( socket_, address, buffer, numberOfBytesToSend );
        }
        return connectRequest_.get( );
    }
    ClientReceiveRequest* ReceiveRequest( void* buffer, UInt32 numberOfBytesToReceive )
    {
        if ( !receiveRequest_ )
        {
            receiveRequest_ = std::make_unique<ClientReceiveRequest>( socket_, buffer, numberOfBytesToReceive );
        }
        return receiveRequest_.get( );
    }
    ClientSendRequest* SendRequest( void* buffer, UInt32 numberOfBytesToSend )
    {
        if ( !sendRequest_ )
        {
            sendRequest_ = std::make_unique<ClientSendRequest>( socket_, buffer, numberOfBytesToSend );
        }
        return sendRequest_.get( );
    }

    ClientDisconnectRequest* DisconnectRequest( bool reuse = false )
    {
        if ( !disconnectRequest_ )
        {
            disconnectRequest_ = std::make_unique<ClientDisconnectRequest>( socket_, reuse );
        }
        return disconnectRequest_.get( );
    }

    void Start( const IO::Sockets::Address& address )
    {
        stopwatch_.Start( );
        //auto request = ConnectRequest( address, &header_, sizeof(SensorDataHeader) );
        //BeginConnect( *request );

        socket_.Connect( address );
        auto request = SendRequest( &header_, sizeof( SensorDataHeader ) );
        BeginSend( *request );

    }

    size_t NumberOfRecordsSent( ) const
    {
        return numberOfRecordsSent_;
    }
    size_t NumberOfRecordsReceivedByServer( ) const
    {
        return numberOfRecordsReceivedByServer_;
    }

    double Duration( ) const
    {
        return stopwatch_.TotalSeconds( );
    }

private:
    void BeginSendTimeseriesPoints( )
    {
#ifdef LOG_USING_PRINTF
        printf( "TCPClient::BeginSendTimeseriesPoints - sent:%zu\n", numberOfRecordsSent_ );
#endif
        if ( numberOfRecordsSent_ < header_.Count )
        {
            Byte* buffer = reinterpret_cast<Byte*>( records_.data( ) );
            UInt32 bufferSize = static_cast<UInt32>(records_.size( ) * sizeof( SensorValue ));
            auto sendRequest = SendRequest( buffer, bufferSize );
            BeginSend( *sendRequest );
        }
    }

    void BeginReceiveServerReceivedCount( )
    {
#ifdef LOG_USING_PRINTF
        printf( "TCPClient::BeginReceiveServerReceivedCount - sent:%zu\n", numberOfRecordsSent_ );
#endif
        Byte* buffer = reinterpret_cast<Byte*>( &numberOfRecordsReceivedByServer_ );
        UInt32 bufferSize = static_cast<UInt32>( sizeof( numberOfRecordsReceivedByServer_ ));
        auto sendRequest = ReceiveRequest( buffer, bufferSize );
        BeginReceive( *sendRequest );
    }

    void BeginDisconnectFromServer( )
    {
#ifdef LOG_USING_PRINTF
        printf( "TCPClient::BeginDisconnectFromServer - sent:%zu\n", numberOfRecordsSent_ );
#endif
        auto disconnectRequest = DisconnectRequest( );
        BeginDisconnect( *disconnectRequest );
    }


    template<typename RequestT>
    void ProcessSendRequest( RequestT* clientRequest )
    {
#ifdef LOG_USING_PRINTF
        printf( "TCPClient::ProcessSendRequest - sent:%zu\n", numberOfRecordsSent_ );
#endif
        auto numberOfBytesTransferred = clientRequest->NumberOfBytesTransferred( );
        auto numberOfBytesToSend = clientRequest->NumberOfBytesToSend( );
        if ( headerBytesSent_ < sizeof( SensorDataHeader ) )
        {
            if( numberOfBytesTransferred < numberOfBytesToSend )
            { 
                headerBytesSent_ += numberOfBytesTransferred;
                Byte* data = ( (Byte*)&header_ ) + headerBytesSent_;
                UInt32 remaining = static_cast<UInt32>( sizeof( SensorDataHeader ) - headerBytesSent_);
                auto sendRequest = SendRequest( data, remaining );
                BeginSend( *sendRequest );
            }
            else
            {
                headerBytesSent_ = sizeof( SensorDataHeader );
                BeginSendTimeseriesPoints( );
            }
        }
        else
        {
            if ( numberOfBytesTransferred < numberOfBytesToSend )
            {
                Byte* buffer = reinterpret_cast<Byte*>( clientRequest->Buffer( ) );
                Byte* remainingBuffer = &buffer[numberOfBytesTransferred];
                auto remainingNumberOfBytesToSend = static_cast<UInt32>( numberOfBytesToSend - numberOfBytesTransferred );
                auto sendRequest = SendRequest( remainingBuffer, remainingNumberOfBytesToSend );
                BeginSend( *sendRequest );
            }
            else
            {
                this->numberOfRecordsSent_ += records_.size( );
                if ( numberOfRecordsSent_ < header_.Count )
                {
                    BeginSendTimeseriesPoints( );
                }
                else
                {
                    BeginReceiveServerReceivedCount( );
                }
            }
        }
    }

    void HandleConnect( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketConnectRequest* request )
    {
#ifdef LOG_USING_PRINTF
        printf( "TCPClient::HandleConnect\n" );
#endif
        auto clientRequest = static_cast<ClientConnectRequest*>( request );
        auto connectRequest = std::move( connectRequest_ );
        ProcessSendRequest( clientRequest );
    }

    void HandleDisconnect( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketDisconnectRequest* request )
    {
#ifdef LOG_USING_PRINTF
        printf( "TCPClient::HandleDisconnect\n" );
#endif
        auto disconnectRequest = std::move( disconnectRequest_ );
        stopwatch_.Stop( );
        OnDisconnected( );
    }
    void HandleReceive( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketReceiveRequest* request )
    {
#ifdef LOG_USING_PRINTF
        printf( "TCPClient::HandleReceive\n" );
#endif
        auto clientRequest = static_cast<ClientReceiveRequest*>( request );
        auto receiveRequest = std::move( receiveRequest_ );
        auto numberOfBytesTransferred = clientRequest->NumberOfBytesTransferred( );
        auto numberOfBytesToReceive = clientRequest->NumberOfBytesToReceive( );
        if ( numberOfBytesTransferred == numberOfBytesToReceive )
        {
            // We are done
            BeginDisconnectFromServer( );
        }
        else
        {
            Byte* buffer = clientRequest->Buffer( );
            auto remainingBuffer = buffer + numberOfBytesTransferred;
            auto remaining = static_cast<UInt32>( numberOfBytesToReceive - numberOfBytesTransferred );
            auto remainingRequest = ReceiveRequest( remainingBuffer, remaining );
            BeginReceive( *receiveRequest );
        }
    }

    void HandleSend( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketSendRequest* request )
    {
#ifdef LOG_USING_PRINTF
        printf( "TCPClient::HandleSend\n" );
#endif
        auto clientRequest = static_cast<ClientSendRequest*>( request );
        auto sendRequest = std::move( sendRequest_ );
        ProcessSendRequest( clientRequest );

    }

};


class TCPSessionHandler;
class ServerAcceptRequest : public ThreadPools::SocketAcceptRequest
{
public:
    using Base = ThreadPools::SocketAcceptRequest;
    static constexpr UInt32 ReceiveSize = sizeof(SensorDataHeader);
    static constexpr UInt32 ReceiveBufferSize = ThreadPools::SocketAcceptRequest::CalculateBufferSizeFor( ReceiveSize );
private:
    TCPSessionHandler* sessionHandler_;
public:
    ServerAcceptRequest( const Socket& listenSocket, const Socket& acceptSocket, TCPSessionHandler* sessionHandler, void* buffer, UInt32 numberOfBytesToReceive )
        : Base( listenSocket, acceptSocket, buffer, numberOfBytesToReceive ), sessionHandler_( sessionHandler )
    {
    }
    TCPSessionHandler* SessionHandler( ) const
    {
        return sessionHandler_;
    }
    void SetSessionHandler( TCPSessionHandler* sessionHandler )
    {
        sessionHandler_ = sessionHandler;
    }

    UInt32 NumberOfBytesToReceive( ) const
    {
        return Base::ReceiveDataLength( );
    }

};

class ServerReceiveRequest : public ThreadPools::SocketReceiveRequest
{
public:
    using Base = ThreadPools::SocketReceiveRequest;
private:
    WSABUF wsaBuf_;
public:
    ServerReceiveRequest( const Socket& socket, void* buffer, UInt32 numberOfBytesToReceive )
        : Base( socket, &wsaBuf_, 1, MessageFlags::None ),
          wsaBuf_{ numberOfBytesToReceive, (CHAR*)buffer }
    {
    }

    UInt32 NumberOfBytesToReceive( ) const
    {
        return wsaBuf_.len;
    }

    Byte* Buffer( ) const
    {
        return (Byte*)wsaBuf_.buf;
    }
};

class ServerSendRequest : public ThreadPools::SocketSendRequest
{
public:
    using Base = ThreadPools::SocketSendRequest;
private:
    WSABUF wsaBuf_;
public:
    ServerSendRequest( const Socket& socket, void* buffer, UInt32 numberOfBytesToSend )
        : Base( socket, &wsaBuf_, 1, MessageFlags::None ),
          wsaBuf_{ numberOfBytesToSend, (CHAR*)buffer }
    {
        
    }

    UInt32 NumberOfBytesToSend( ) const
    {
        return wsaBuf_.len;
    }

    Byte* Buffer( )
    {
        return (Byte*)wsaBuf_.buf;
    }
};


class ServerDisconnectRequest : public ThreadPools::SocketDisconnectRequest
{
public:
    using Base = ThreadPools::SocketDisconnectRequest;

    ServerDisconnectRequest( const Socket& socket, bool reuse )
        : Base( socket, reuse )
    {
    }
};


class TCPSimpleServer;
class TCPListener;
class TCPSessionHandler : public ThreadPools::SocketHandler<TCPSessionHandler>
{
    template<typename DerivedT>
    friend class SocketHandler;
    template<typename DerivedT>
    friend class IOHandler;
    friend class TCPListener;
public:
    using Base = ThreadPools::SocketHandler<TCPSessionHandler>;
private:
    Base::Socket socket_;
    std::atomic<bool> closed_;
    SensorDataHeader header_;
    size_t headerBytesReceived_;
    TCPSimpleServer* server_;
    std::array<SensorValue, SensorValueBatchSize> records_;
    size_t numberOfRecordsReceived_;
    std::unique_ptr<ServerAcceptRequest> acceptRequest_;
    std::unique_ptr<ServerReceiveRequest> receiveRequest_;
    std::unique_ptr<ServerSendRequest> sendRequest_;
    std::unique_ptr<ServerDisconnectRequest> disconnectRequest_;
public:
    TCPSessionHandler( Base::Socket&& socket, ThreadPools::Environment& environment, TCPSimpleServer* server )
        : Base( socket, environment ), socket_( std::move( socket ) ), closed_(false), server_( server ), headerBytesReceived_(0), numberOfRecordsReceived_(0)
    {
    }

    TCPSessionHandler( IO::Sockets::AddressFamily addressFamily, ThreadPools::Environment& environment, TCPSimpleServer* server )
        : TCPSessionHandler( Base::Socket( addressFamily,
            IO::Sockets::SocketType::Stream,
            IO::Sockets::ProtocolType::Tcp,
            IO::Sockets::SocketFlags::Overlapped ), environment, server )
    {
    }

    TCPSessionHandler( ThreadPools::Environment& environment, TCPSimpleServer* server )
        : TCPSessionHandler( IO::Sockets::AddressFamily::InterNetworkV6, environment, server )
    {
    }

    void Close( )
    {
        closed_ = true;
        
        SOCKET socketHandle = socket_.Handle( );
        if ( acceptRequest_ && acceptRequest_->Cancel() )
        {
            acceptRequest_->Wait( );
        }
        if ( receiveRequest_ && receiveRequest_->Cancel( ) )
        {
            receiveRequest_->Wait( );
        }
        if ( sendRequest_ && sendRequest_->Cancel( ) )
        {
            sendRequest_->Wait( );
        }
        if ( disconnectRequest_ && disconnectRequest_->Cancel( ) )
        {
            disconnectRequest_->Wait( );
        }
        socket_.Close( );
        CancelIoEx( reinterpret_cast<HANDLE>( socketHandle ), nullptr );

        Base::WaitForCallbacks( true );
        Base::Close( );
    }

    const Base::Socket& Socket( ) const
    {
        return socket_;
    }

    ServerAcceptRequest* AcceptRequest( const IO::Sockets::Socket& listenSocket )
    {
        if ( !acceptRequest_ )
        {
            acceptRequest_ = std::make_unique<ServerAcceptRequest>( listenSocket, socket_, this, &header_, static_cast<UInt32>(sizeof(SensorDataHeader)) );
        }
        return acceptRequest_.get( );
    }

    ServerReceiveRequest* ReceiveRequest( void* buffer, UInt32 numberOfBytesToReceive )
    {
        if ( !receiveRequest_ )
        {
            receiveRequest_ = std::make_unique<ServerReceiveRequest>( socket_, buffer, numberOfBytesToReceive );
        }
        return receiveRequest_.get( );
    }

    ServerSendRequest* SendRequest( void* buffer, UInt32 numberOfBytesToSend )
    {
        if ( !sendRequest_ )
        {
            sendRequest_ = std::make_unique<ServerSendRequest>( socket_, buffer, numberOfBytesToSend );
        }
        return sendRequest_.get( );
    }

    ServerDisconnectRequest* DisconnectRequest( bool reuse = true )
    {
        if ( !disconnectRequest_ )
        {
            disconnectRequest_ = std::make_unique<ServerDisconnectRequest>( socket_, reuse );
        }
        return disconnectRequest_.get( );
    }

private:

    void BeginReceivingSensorValues( )
    {
        auto buffer = (Byte*)records_.data();
        auto bufferSize = static_cast<UInt32>(SensorValueBatchSize * sizeof( SensorValue ));
        auto receiveRequest = ReceiveRequest( buffer, bufferSize );
        BeginReceive( *receiveRequest );
    }

    void BeginSendResult( )
    {
        auto buffer = (Byte*)&numberOfRecordsReceived_;
        constexpr auto bufferSize = static_cast<UInt32>( sizeof( numberOfRecordsReceived_ ) );
        auto sendRequest = SendRequest( buffer, bufferSize );
        BeginSend( *sendRequest );
    }

    void BeginDisconnectFromClient( )
    {
        auto disconnectRequest = DisconnectRequest( true );
        BeginDisconnect( *disconnectRequest );
    }

    void Callback( const ThreadPools::CallbackInstance& instance, IO::Request* request, UInt32 ioResult, UInt64 numberOfBytesTransferred )
    {
        try
        {

            if ( !closed_ && request->IoResult() != ERROR_OPERATION_ABORTED )
            {
                Base::Callback( instance, request, ioResult, numberOfBytesTransferred );
            }
        }
        catch ( ... )
        {
        }
    }


    void HandleAccept( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketAcceptRequest* request )
    {
        if ( !closed_ )
        {
#ifdef LOG_USING_PRINTF
            printf( "TCPSessionHandler::HandleAccept\n" );
#endif
            //records_.resize( SensorValueBatchSize );
            //records_.resize( SensorValueBatchSize, SensorValue{ Guid( ), DateTime::MinValue( ),0, 0.0 } );
            auto serverRequest = static_cast<ServerAcceptRequest*>( request );
            auto acceptRequest = std::move( acceptRequest_ );
            auto ioResult = serverRequest->IoResult( );

            auto numberOfBytesTransferred = serverRequest->NumberOfBytesTransferred( );
            auto numberOfBytesToReceive = serverRequest->NumberOfBytesToReceive( );
            headerBytesReceived_ = numberOfBytesTransferred;
            if ( numberOfBytesTransferred < numberOfBytesToReceive )
            {
                auto buffer = (Byte*)serverRequest->Buffer( );
                auto remainingBuffer = buffer + numberOfBytesTransferred;
                auto remainingBufferSize = static_cast<UInt32>( numberOfBytesToReceive - numberOfBytesTransferred );
                auto receiveRequest = ReceiveRequest( remainingBuffer, remainingBufferSize );
                BeginReceive( *receiveRequest );
            }
            else
            {
                BeginReceivingSensorValues( );
            }
        }


    }

    void BeginAccept( );

    void HandleDisconnect( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketDisconnectRequest* request )
    {
        if ( !closed_ )
        {
#ifdef LOG_USING_PRINTF
            printf( "TCPSessionHandler::HandleDisconnect\n" );
#endif
            auto serverRequest = static_cast<ServerDisconnectRequest*>( request );
            auto disconnectRequest = std::move( disconnectRequest_ );
            if ( serverRequest->Reuse( ) )
            {
                BeginAccept( );
            }
        }
    }
    void HandleReceive( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketReceiveRequest* request )
    {
        if ( !closed_ )
        {
#ifdef LOG_USING_PRINTF
            printf( "TCPSessionHandler::HandleReceive\n" );
#endif
            auto serverRequest = static_cast<ServerReceiveRequest*>( request );
            auto receiveRequest = std::move( receiveRequest_ );

            auto numberOfBytesTransferred = serverRequest->NumberOfBytesTransferred( );
            auto numberOfBytesToReceive = serverRequest->NumberOfBytesToReceive( );

            if ( numberOfBytesTransferred < numberOfBytesToReceive )
            {
                auto buffer = (Byte*)serverRequest->Buffer( );
                auto remainingBuffer = buffer + numberOfBytesTransferred;
                auto remainingBufferSize = static_cast<UInt32>( numberOfBytesToReceive - numberOfBytesTransferred );
                auto remainingReceiveRequest = ReceiveRequest( remainingBuffer, remainingBufferSize );
                BeginReceive( *remainingReceiveRequest );
            }
            else
            {
                if ( headerBytesReceived_ == sizeof( SensorDataHeader ) )
                {
                    numberOfRecordsReceived_ += records_.size( );
                }
                else
                {
                    headerBytesReceived_ = sizeof( SensorDataHeader );
                }
                if ( numberOfRecordsReceived_ < header_.Count )
                {
                    BeginReceivingSensorValues( );
                }
                else
                {
                    BeginSendResult( );
                }
            }
        }

    }

    void HandleSend( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketSendRequest* request )
    {
        if ( !closed_ )
        {
#ifdef LOG_USING_PRINTF
            printf( "TCPSessionHandler::HandleSend\n" );
#endif
            auto serverRequest = static_cast<ServerSendRequest*>( request );
            auto sendRequest = std::move( sendRequest_ );

            auto numberOfBytesTransferred = serverRequest->NumberOfBytesTransferred( );
            auto numberOfBytesToSend = serverRequest->NumberOfBytesToSend( );
            if ( numberOfBytesTransferred < numberOfBytesToSend )
            {
                auto buffer = (Byte*)serverRequest->Buffer( );
                auto remainingBuffer = buffer + numberOfBytesTransferred;
                auto remainingBufferSize = static_cast<UInt32>( numberOfBytesToSend - numberOfBytesTransferred );
                auto remainingSendRequest = SendRequest( remainingBuffer, remainingBufferSize );
                BeginSend( *remainingSendRequest );
            }
            else
            {
                BeginDisconnectFromClient( );
            }
        }

    }

    bool HandleDisconnectError( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketDisconnectRequest* request )
    {

    }
    bool HandleReceiveError( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketReceiveRequest* request )
    {

    }

    bool HandleSendError( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketSendRequest* request )
    {

    }
};



class TCPListener : public ThreadPools::SocketHandler<TCPListener>
{
    template<typename DerivedT>
    friend class SocketHandler;
public:
    using Base = ThreadPools::SocketHandler<TCPListener>;
private:
    IO::Sockets::Address address_;
    Base::Socket socket_;
    std::atomic<bool> closed_;
private:
    TCPListener( Base::Socket&& socket, ThreadPools::Environment& environment )
        : Base( socket, environment ), socket_( std::move( socket ) ), closed_(false)
    {
        
    }
public:
    TCPListener( const IO::Sockets::Address& address, ThreadPools::Environment& environment )
        : TCPListener( Base::Socket( address.Family( ),
            IO::Sockets::SocketType::Stream,
            IO::Sockets::ProtocolType::Tcp,
            IO::Sockets::SocketFlags::Overlapped ), environment )
    {
        address_ = address;
    }

    const Base::Socket& Socket( ) const
    {
        return socket_;
    }

    void Close( )
    {
        closed_ = true;
        SOCKET socketHandle = socket_.Handle( );
        socket_.Close( );
        CancelIoEx( reinterpret_cast<HANDLE>( socketHandle ), nullptr );

        Base::WaitForCallbacks( );
        Base::Close( );
    }

    void Bind( ) const
    {
        socket_.Bind( address_ );
    }
    void Listen( ) const
    {
        socket_.Listen( );
    }

private:
    void HandleAccept( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketAcceptRequest* request )
    {
        if ( !closed_ )
        {
            auto serverRequest = static_cast<ServerAcceptRequest*>( request );
            auto sessionHandler = serverRequest->SessionHandler( );
            sessionHandler->HandleAccept( instance, request );
        }
    }
    void HandleDisconnect( const ThreadPools::CallbackInstance& instance, ThreadPools::SocketDisconnectRequest* request )
    {

    }


};


class TCPSimpleServer
{
    ThreadPools::Environment& environment_;
    TCPListener listener_;
    std::vector<std::unique_ptr<TCPSessionHandler>> sessions_;

public:
    TCPSimpleServer( const IO::Sockets::Address& address, size_t sessionPoolSize, ThreadPools::Environment& environment )
        : environment_( environment ), listener_( address, environment )
    {
        sessions_.reserve( sessionPoolSize );
        for ( size_t i = 0; i < sessionPoolSize; ++i )
        {
            sessions_.emplace_back( std::make_unique<TCPSessionHandler>( environment, this ) );
        }
    }

    void Start( )
    {
        listener_.Bind( );
        listener_.Listen( );
        for ( auto& session : sessions_ )
        {
            BeginAccept( session.get( ) );
        }
    }

    void BeginAccept( TCPSessionHandler* sessionHandler )
    {
        auto acceptRequest = sessionHandler->AcceptRequest( listener_.Socket( ) );
        listener_.BeginAccept( *acceptRequest );
    }

    void Stop( )
    {
        listener_.Close( );
        for ( auto& session : sessions_ )
        {
            session->Close( );
        }
        
    }
};

void TCPSessionHandler::BeginAccept( )
{
    if ( !closed_ )
    {
        server_->BeginAccept( this );
    }
}



#endif
