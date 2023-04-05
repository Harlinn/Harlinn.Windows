#include <HCCThread.h>
#include <HCCIOContext.h>
#include <HCCSocketServer.h>
#include <HCCGuid.h>
#include <HCCApplication.h>

#include <HExTypes.h>
#include <boost/container/flat_map.hpp>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::IO::Sockets;
using namespace Harlinn::Common::Core::Examples;

#ifdef _DEBUG
constexpr size_t BatchSize = 20;
#else
constexpr size_t BatchSize = 20'000;
#endif

#pragma pack(push,1)
struct Header
{
    size_t RecordCount;
    Int32 Index;
    Header( ) : RecordCount(0), Index(0)
    { }
};
#pragma pack(pop)

struct AcceptRequestBuffer : public Header
{
    using Base = Header;
    constexpr static size_t AddressInfoSize = AcceptRequest::CalculateBufferSizeFor( 0 );
    Byte AddressInfo[AddressInfoSize];
    AcceptRequestBuffer()
        : Base(), AddressInfo{}
    {}
};



enum class ConnectionHandlerState
{
    Unknown,
    Accepting,
    ReceivingHeader,
    ReceivingValues,
    Disconnecting
};

class Listener;
class ConnectionHandler 
    : public Server::TcpConnectionHandlerBase<ConnectionHandler>
{
    template<typename DerivedT>
    friend class SocketHandler;
public:
    using Base = Server::TcpConnectionHandlerBase<ConnectionHandler>;
private:
    std::weak_ptr<Listener> listener_;
    ConnectionHandlerState state_;
    size_t received_;
    Stopwatch stopwatch_;
    AcceptRequestBuffer header_;
    WSABUF wsabuf_;
    std::vector<SensorValue> records_;
    std::unique_ptr<AcceptRequest> acceptRequest_;
    std::unique_ptr<ReceiveRequest> receiveRequest_;
    std::unique_ptr<DisconnectRequest> disconnectRequest_;
public:
    ConnectionHandler( const std::shared_ptr<IO::Context>& context, const std::shared_ptr<Listener>& listener )
        : Base( context ), 
          listener_( listener ), 
          state_( ConnectionHandlerState::Accepting ),
          received_(0), 
          wsabuf_{}
    { 
    }


    AcceptRequest* GetAcceptRequest( const Socket& server )
    {
        if ( !acceptRequest_ )
        {
            acceptRequest_ = std::make_unique<AcceptRequest>( server, 
                Client(), reinterpret_cast<Byte*>(&header_), static_cast<UInt32>( sizeof( Header ) ) );
        }
        else
        {
            acceptRequest_->Clear( );
        }
        return acceptRequest_.get( );
    }

    ReceiveRequest* GetReceiveRequest( )
    {
        if ( !receiveRequest_ )
        {
            records_.resize( BatchSize );
            wsabuf_.buf = (CHAR*) records_.data( );
            wsabuf_.len = static_cast<int>(records_.size( ) * sizeof( SensorValue ));
            receiveRequest_ = std::make_unique<ReceiveRequest>( Client( ), &wsabuf_,1, MessageFlags::WaitAll );
        }
        else
        {
            receiveRequest_->Clear( );
        }
        return receiveRequest_.get( );
    }
    DisconnectRequest* GetDisconnectRequest( )
    {
        if ( !disconnectRequest_ )
        {
            disconnectRequest_ = std::make_unique<DisconnectRequest>( Client( ), true );
        }
        else
        {
            disconnectRequest_->Clear( );
        }
        return disconnectRequest_.get( );
    }

    bool HandleAcceptCompleted( AcceptRequest* request )
    {
#ifdef _DEBUG
        printf( "In ConnectionHandler HandleAccept\n" );
#endif
        if ( request->IoResult( ) == WinError::None )
        {
            stopwatch_.Start( );
            received_ = 0;
            auto nextRequest = GetReceiveRequest( );
            if ( request->NumberOfBytesTransferred( ) < request->NumberOfBytesToRead( ) )
            {
                state_ = ConnectionHandlerState::ReceivingHeader;
                wsabuf_.buf = ((char*)request->Buffer( )) + request->NumberOfBytesTransferred( );
                wsabuf_.len = request->NumberOfBytesToRead( ) - static_cast<UInt32>( request->NumberOfBytesTransferred( ) );
            }
            else
            {
                state_ = ConnectionHandlerState::ReceivingValues;
                wsabuf_.buf = (char*)records_.data( );
                wsabuf_.len = static_cast<int>( records_.size( ) * sizeof( SensorValue ) );
            }
            BeginAsyncReceive( nextRequest );
        }
        else
        {
            printf( "In ConnectionHandler HandleAccept: IoResult=%u, transferred = %llu\n", request->IoResult( ), request->NumberOfBytesTransferred( ) );
            Disconnect( );
        
        }
        return true;
    }

    bool HandleReceiveCompleted( ReceiveRequest* request )
    {
#ifdef _DEBUG
        printf( "In ConnectionHandler HandleReceive: IoResult=%u, transferred = %llu\n", request->IoResult( ), request->NumberOfBytesTransferred( ) );
#endif
        if ( request->IoResult( ) == WinError::None )
        {
            if ( request->NumberOfBytesTransferred( ) < static_cast<size_t>(wsabuf_.len) )
            {
                wsabuf_.buf = wsabuf_.buf + request->NumberOfBytesTransferred( );
                wsabuf_.len = wsabuf_.len - static_cast<UInt32>( request->NumberOfBytesTransferred( ) );
                request->Clear( );
                BeginAsyncReceive( request );
            }
            else
            {
                switch ( state_ )
                {
                    case ConnectionHandlerState::ReceivingHeader:
                    {
                        state_ = ConnectionHandlerState::ReceivingValues;
                        wsabuf_.buf = (CHAR*)records_.data( );
                        wsabuf_.len = static_cast<int>( records_.size( ) * sizeof( SensorValue ) );
                        request->Clear( );
                        BeginAsyncReceive( request );
                    }
                    break;
                    case ConnectionHandlerState::ReceivingValues:
                    {
                        if ( received_ + BatchSize < header_.RecordCount )
                        {
                            received_ += BatchSize;
                            wsabuf_.buf = (CHAR*)records_.data( );
                            wsabuf_.len = static_cast<int>( records_.size( ) * sizeof( SensorValue ) );
                            request->Clear( );
                            BeginAsyncReceive( request );
                        }
                        else
                        {
                            received_ += BatchSize;
                            stopwatch_.Stop( );

                            auto duration = stopwatch_.Elapsed( ).TotalSeconds( );
                            auto pointsPerSecond = ( received_ ) / duration;
                            auto gbPerSecond = ( pointsPerSecond * sizeof( SensorValue ) ) / ( 1024ll * 1024 * 1024 );

                            wprintf( L"Received %llu records in %f seconds, %f records and %f GB per second.\n", received_, duration, pointsPerSecond, gbPerSecond );

                            Disconnect( );
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            printf( "In ConnectionHandler HandleReceive: IoResult=%u, transferred = %llu\n", request->IoResult( ), request->NumberOfBytesTransferred( ) );
            Disconnect( );
        }
        return true;

    }

    void Disconnect( )
    {
        printf( "In ConnectionHandler Disconnect: Handle=0x%08llx \n", Client( ).Handle( ) );

        state_ = ConnectionHandlerState::Disconnecting;
        auto nextRequest = GetDisconnectRequest( );
        BeginAsyncDisconnect( nextRequest );
    }

    void Accept( );
    void Destroy( );
    

    bool HandleDisconnectCompleted( DisconnectRequest* request )
    {
//#ifdef _DEBUG
        printf( "In ConnectionHandler HandleDisconnect: IoResult=%u, transferred = %llu\n", request->IoResult( ), request->NumberOfBytesTransferred( ) );
//#endif
        if ( request->IoResult( ) == WinError::None )
        {
            //Accept( );
            Destroy( );
        }
        return true;
    }
};

class Listener : public Server::TcpListenerBase<Listener>
{
    template<typename DerivedT>
    friend class SocketHandler;
public:
    using Base = Server::TcpListenerBase<Listener>;
private:
    CriticalSection criticalSection_;
    Address address_;
    size_t initialNumberOfConnections_;
    boost::container::flat_map<SOCKET, std::shared_ptr<ConnectionHandler>> connectionHandlers_;
public:
    Listener( const std::shared_ptr<IO::Context>& context, const Address& address, size_t initialNumberOfConnections )
        : Base( context ), address_( address ), initialNumberOfConnections_( initialNumberOfConnections )
    { 
    }

    void Start( ) override
    {
        printf( "Starting listener\n" );
        Server( ).Bind( address_ );
        Server( ).Listen( );

        auto context = Context( );

        for ( size_t i = 0; i < initialNumberOfConnections_; ++i )
        {
            auto handler = std::make_shared<ConnectionHandler>( context, Self() );
            connectionHandlers_.emplace( handler->Client( ).Handle( ), handler );
            Accept( handler );
        }
    }

    void Accept( const std::shared_ptr<ConnectionHandler>& connectionHandler )
    {
        printf( "In Listener Accept: Handle=0x%08llx \n", connectionHandler->Client().Handle() );
        auto* request = connectionHandler->GetAcceptRequest( Server( ) );
        BeginAsyncAccept( request );
    }

    void DestroyAndAddNewHandler( ConnectionHandler* connectionHandler )
    {
        std::unique_lock lock( criticalSection_ );
        auto acceptSocket = connectionHandler->Client( ).Handle( );
        auto it = connectionHandlers_.find( acceptSocket );
        if ( it != connectionHandlers_.end( ) )
        {
            auto handlerPtr = std::move( it->second );
            connectionHandlers_.erase( acceptSocket );
            auto context = Context( );
            auto handler = std::make_shared<ConnectionHandler>( context, Self() );
            connectionHandlers_.emplace( handler->Client( ).Handle( ), handler );
            Accept( handler );
        }
    }

    void Stop( ) override
    {
        printf( "In Listener Stop \n" );
        for ( auto& entry : connectionHandlers_ )
        {
            entry.second->Close( );
        }
        Server( ).Close( );
    }

    bool HandleAcceptCompleted( AcceptRequest* request )
    {
        
#ifdef _DEBUG
        printf( "In Listener HandleAccept: IoResult=%u, transferred = %llu\n", request->IoResult(), request->NumberOfBytesTransferred() );
#endif
        auto ioResult = request->IoResult( );
        if ( request->IoResult( ) != WinError::OperationAborted &&
            request->IoResult( ) != WinError::StatusCancelled &&
            request->IoResult( ) != WinError::StatusLocalDisconnect &&
            request->IoResult( ) != WinError::StatusRemoteDisconnect )
        {
            auto acceptSocket = request->AcceptSocket( );
            auto it = connectionHandlers_.find( acceptSocket );
            if ( it != connectionHandlers_.end( ) )
            {
                it->second->HandleAcceptCompleted( request );
            }
        }
        return true;
    }
};

inline void ConnectionHandler::Accept( )
{
    state_ = ConnectionHandlerState::Accepting;
    auto listener = listener_.lock( );
    listener->Accept( Self() );
}

inline void ConnectionHandler::Destroy( )
{
    auto listener = listener_.lock( );
    listener->DestroyAndAddNewHandler( this );
}



int main()
{
    ApplicationOptions options;
    options.Load( );
    Application application( options );
    application.Start( );
    try
    {
        WSAInitTerm wsa;
        constexpr DWORD ThreadPoolSize = 12;

        auto context = std::make_shared<IO::Context>( ThreadPoolSize );
        Address address( 42000 );
        auto listener = std::make_shared<Listener>( context, address, 2 );
        context->Start( );

        puts( "Press enter to exit" );
        while ( getc( stdin ) != '\n' );

        context->Stop( );
    }
    catch ( std::exception& exc )
    {
        auto* message = exc.what( );
        printf( "Exception: %s\n", message );
    }
    application.Stop( );
}

