#pragma once
#ifndef HARLINN_COMMON_CORE_HCCTCPSERVER_H_
#define HARLINN_COMMON_CORE_HCCTCPSERVER_H_
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

#include <HCCSocket.h>

namespace Harlinn::Common::Core::IO::Sockets::Tcp::Server
{
    using TcpSocket = Sockets::TcpSocket;


    template<typename ConnectionHandlerT,  typename RequestsPoolTypeParamsT = RequestsPoolTypeParams<> >
    class ConnectionHandlerRequestsPool : public RequestsPool<RequestsPoolTypeParamsT>
    {
    public:
        using Base = RequestsPool<RequestsPoolTypeParamsT>;
        using ConnectionHandlerType = ConnectionHandlerT;
    private:
        ConnectionHandlerType& connectionHandler_;
    public:
        ConnectionHandlerRequestsPool( ConnectionHandlerType& connectionHandler )
            : connectionHandler_( connectionHandler )
        { }

        const TcpSocket& ConnectionSocket( ) const
        {
            return connectionHandler_.Socket( );
        }
        const TcpSocket& ListenerSocket( ) const
        {
            return connectionHandler_.Listener( )->Socket( );
        }

        using ConnectRequestType = typename Base::ConnectRequestType;
        using AcceptRequestType = typename Base::AcceptRequestType;
        using DisconnectRequestType = typename Base::DisconnectRequestType;
        using IoctlRequestType = typename Base::IoctlRequestType;
        using ReceiveRequestType = typename Base::ReceiveRequestType;
        using ReceiveFromRequestType = typename Base::ReceiveFromRequestType;
        using ReceiveMsgRequestType = typename Base::ReceiveMsgRequestType;
        using SendRequestType = typename Base::SendRequestType;
        using SendToRequestType = typename Base::SendToRequestType;
        using SendMsgRequestType = typename Base::SendMsgRequestType;
        using TransmitFileRequestType = typename Base::TransmitFileRequestType;
        using TransmitPacketsRequestType = typename Base::TransmitPacketsRequestType;

        ConnectRequestType* AcquireConnectRequest( const Sockets::Address& address, const Byte* buffer = nullptr, UInt32 numberOfBytesToSend = 0 )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireConnectRequest( connectionSocket, address, buffer, numberOfBytesToSend );
        }

        AcceptRequestType* AcquireAcceptRequest( Byte* buffer, UInt32 receiveDataLength, UInt32 localAddressLength = AcceptRequest::MaxLocalAddressLength, UInt32 remoteAddressLength = AcceptRequest::MaxRemoteAddressLength )
        {
            const auto& connectionSocket = ConnectionSocket( );
            const auto& listenerSocket = ListenerSocket( );
            return Base::AcquireAcceptRequest( listenerSocket, connectionSocket, buffer, receiveDataLength, localAddressLength, remoteAddressLength );
        }
        DisconnectRequestType* AcquireDisconnectRequest( bool reuse = true )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireDisconnectRequest( connectionSocket, reuse );
        }
        IoctlRequestType* AcquireIoctlRequest( UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireIoctlRequest( connectionSocket, ioControlCode, inBuffer, inBufferLength,outBuffer, outBufferLength );
        }
        ReceiveRequestType* AcquireReceiveRequest( WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireReceiveRequest( connectionSocket, buffers, bufferCount, flags );
        }

        ReceiveFromRequestType* AcquireReceiveFromRequest( WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireReceiveFromRequest( connectionSocket, buffers, bufferCount, flags );
        }

        ReceiveMsgRequestType* AcquireReceiveMsgRequest( WSAMSG* msg = nullptr )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireReceiveMsgRequest( connectionSocket, msg );
        }

        SendRequestType* AcquireSendRequest( WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireSendRequest( connectionSocket, buffers, bufferCount, flags );
        }

        SendToRequestType* AcquireSendToRequest( WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireSendToRequest( connectionSocket, buffers, bufferCount, flags, destinationAddress );
        }

        SendMsgRequestType* AcquireSendMsgRequest( WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireSendMsgRequest( connectionSocket, msg, flags );
        }

        TransmitFileRequestType* AcquireTransmitFileRequest( HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return AcquireTransmitFileRequest( connectionSocket, hFile, numberOfBytesToWrite, numberOfBytesPerSend, transmitBuffers, flags );
        }

        TransmitPacketsRequestType* AcquireTransmitPacketsRequest( TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None )
        {
            const auto& connectionSocket = ConnectionSocket( );
            return Base::AcquireTransmitPacketsRequest( connectionSocket, packetArray, packetArrayCount, sendSize, flags );
        }

        template<typename RequestType, typename ...Args>
            requires !std::is_same_v<RequestType, AcceptRequestType>
        RequestType* Acquire( Args&& ... args )
        {
            const auto& connectionSocket = ConnectionSocket( );
            RequestType* result = Base:: template Acquire<RequestType>( connectionSocket, std::forward<Args>( args )... );
            return result;
        }

        template<typename RequestType, typename ...Args>
            requires std::is_same_v<RequestType, AcceptRequestType>
        AcceptRequestType* Acquire( Args&& ... args )
        {
            const auto& connectionSocket = ConnectionSocket( );
            const auto& listenerSocket = ListenerSocket( );
            AcceptRequestType* result = Base:: template Acquire<AcceptRequestType>( listenerSocket, connectionSocket, std::forward<Args>( args )... );
            return result;
        }




    };



    enum class ConnectionHandlerState : UInt32
    {
        Unknown,
        Open,
        Connected,
        ClientDisconnected,
        HandlerDisconnected,
        Closing,
        Closed,
        Destroying
    };

    template< typename DerivedT, typename ConnectionHandlerT, typename ConnectionHandlerPoolT >
    class ListenerHandler;

    template< typename DerivedT, typename ListenerHandlerT, typename RequestsPoolT = ConnectionHandlerRequestsPool<DerivedT> >
    class ConnectionHandler : public SocketHandler<DerivedT>
    {
        template<typename DerivedT>
        friend class SocketHandler;

        template< typename DerivedT, typename ConnectionHandlerT, typename ConnectionHandlerPoolT >
        friend class ListenerHandler;
    public:
        using Base = SocketHandler<DerivedT>;
        using DerivedType = DerivedT;
        using ListenerHandlerType = ListenerHandlerT;
        using RequestsPoolType = RequestsPoolT;
    private:
        Server::TcpSocket socket_;
        CriticalSection criticalSection_;
        std::weak_ptr<ListenerHandlerType> listener_;
        AddressFamily addressFamily_;
        RequestsPoolType requestsPool_;
        std::atomic<size_t> outstandingRequests_;
        std::atomic<ConnectionHandlerState> state_ = ConnectionHandlerState::Unknown;
        Sockets::Address localAddress_;
        Sockets::Address remoteAddress_;
    public:
        ConnectionHandler( const std::shared_ptr<ListenerHandlerType>& listener, AddressFamily addressFamily )
            : Base( listener->Context( ) ), listener_( listener ), addressFamily_( addressFamily ), outstandingRequests_( 0 ), requestsPool_( static_cast<DerivedType&>( *this ) )
        {
        }

        virtual ~ConnectionHandler( )
        {
            state_ = ConnectionHandlerState::Destroying;
        }

        void Open( )
        {
            socket_.Open( addressFamily_, SocketFlags::Overlapped );
            auto context = Base::Context( );
            context->Bind( socket_, this );
            state_ = ConnectionHandlerState::Open;
        }
    public:
        bool IsRunning( ) const
        {
            ConnectionHandlerState state = state_.load( );
            if ( state > ConnectionHandlerState::Unknown && state < ConnectionHandlerState::ClientDisconnected )
            {
                auto listener = Listener( );
                if ( listener )
                {
                    return listener->IsRunning( );
                }
            }
            return false;
        }

        std::shared_ptr<ListenerHandlerType> Listener( )
        {
            return listener_.lock( );
        }
        std::shared_ptr<const ListenerHandlerType> Listener( ) const
        {
            return listener_.lock( );
        }

        const Server::TcpSocket& Socket( )
        {
            return socket_;
        }

        void Close( bool graceful )
        {
            auto state = state_.load( );
            if ( state < ConnectionHandlerState::Closing )
            {
                state_ = ConnectionHandlerState::Closing;
                if ( socket_.Handle( ) != INVALID_SOCKET )
                {
                    CancelIoEx( std::bit_cast<HANDLE>( socket_.Handle( ) ), nullptr );
                    while ( outstandingRequests_.load( ) != 0 )
                    {
                        CurrentThread::Yield( );
                    }

                    if ( graceful == false )
                    {
                        socket_.SetLinger( true, 0 );
                    }
                    socket_.Close( );
                }
                
                state_ = ConnectionHandlerState::Closed;
            }
        }

        void Shutdown( ShutdownFlag shutdownFlag = ShutdownFlag::Send ) const
        {
            socket_.Shutdown( shutdownFlag );
        }

        void Start( ) override
        {
            
        }

        void Stop( ) override
        {
            Close( false );
        }

        void ReleaseRequest( SocketRequest* socketRequest )
        {
            std::unique_lock lock( criticalSection_ );
            requestsPool_.Release( socketRequest );
        }


        constexpr bool OnAcceptCompleted( AcceptRequest* request ) const noexcept
        {
            return true;
        }

    protected:
        virtual void ProcessDone( Base::Message& message ) override
        {
            auto* request = static_cast<SocketRequest*>( message.Request( ) );
            if ( request )
            {
                ReleaseRequest( request );
                outstandingRequests_--;
            }
        }


    };


    template<typename ConnectionHandlerT>
    class ConnectionHandlerFactoryBase
    {
        using ConnectionHandlerType = ConnectionHandlerT;
    public:
        ConnectionHandlerFactoryBase( ) = default;
        virtual ~ConnectionHandlerFactoryBase( ) = default;
        virtual std::shared_ptr<ConnectionHandlerType> Create( ) = 0;
    };


    template<typename ListenerHandlerT, typename ConnectionHandlerT, typename... Args>
    class ConnectionHandlerFactory : public ConnectionHandlerFactoryBase<ConnectionHandlerT>
    {
    public:
        using Base = ConnectionHandlerFactoryBase<ConnectionHandlerT>;
        using ListenerHandlerType = ListenerHandlerT;
        using ConnectionHandlerType = ConnectionHandlerT;
        using TupleType = std::tuple<Args...>;
    private:
        ListenerHandlerType& listener_;
        AddressFamily addressFamily_;
        TupleType tuple_;
    public:
        ConnectionHandlerFactory( ListenerHandlerType& listener, AddressFamily addressFamily, Args&&... args )
            : Base( ),
            listener_( listener ), addressFamily_( addressFamily ),
            tuple_( std::forward<Args>( args )... )
        {
        }

        virtual ~ConnectionHandlerFactory( )
        {

        }
    private:
        template<std::size_t... I>
        constexpr std::shared_ptr<ConnectionHandlerType> CreateImpl( std::index_sequence<I...> )
        {
            return std::make_shared<ConnectionHandlerType>( listener_.Self( ), addressFamily_, std::get<I>( tuple_ )... );
        }
    public:
        virtual std::shared_ptr<ConnectionHandlerType> Create( ) override
        {
            return CreateImpl( std::make_index_sequence < std::tuple_size_v<TupleType>>{} );
        }
    };



    template<typename ListenerHandlerT, typename ConnectionHandlerT, size_t maxFreeConnectionHandlers = 64 >
    class ConnectionHandlerPool
    {
    public:
        using ListenerHandlerType = ListenerHandlerT;
        using ConnectionHandlerType = ConnectionHandlerT;
        static constexpr size_t MaxFreeConnectionHandlers = maxFreeConnectionHandlers;
    private:
        CriticalSection criticalSection_;
        AddressFamily addressFamily_;
        std::unique_ptr<ConnectionHandlerFactoryBase<ConnectionHandlerType>> factory_;
        std::vector< std::shared_ptr<ConnectionHandlerType> > connectionHandlers_;
        boost::container::small_vector< std::weak_ptr<ConnectionHandlerType>, MaxFreeConnectionHandlers> freeConnectionHandlers_;
    public:
        template<typename ... ConnectionHandlerArgs>
        ConnectionHandlerPool( ListenerHandlerType& listener, AddressFamily addressFamily, ConnectionHandlerArgs&& ... connectionHandlerArgs )
        {
            factory_ = std::make_unique<ConnectionHandlerFactory<ListenerHandlerType, ConnectionHandlerType, ConnectionHandlerArgs...> >( listener, addressFamily, std::forward<ConnectionHandlerArgs>( connectionHandlerArgs )... );
        }

        ~ConnectionHandlerPool( )
        {
            freeConnectionHandlers_.clear( );
            connectionHandlers_.clear( );
            
        }

        void Clear( )
        {
            std::unique_lock lock( criticalSection_ );
            freeConnectionHandlers_.clear( );
            connectionHandlers_.clear( );
        }

        std::shared_ptr<ConnectionHandlerType> Aquire( )
        {
            std::unique_lock lock( criticalSection_ );
            if ( freeConnectionHandlers_.empty( ) == false )
            {
                std::shared_ptr<ConnectionHandlerType> result = freeConnectionHandlers_.back( ).lock( );
                freeConnectionHandlers_.pop_back( );
                result->Open( );
                return result;
            }
            else
            {
                std::shared_ptr<ConnectionHandlerType> result = factory_->Create( );
                result->Open( );
                connectionHandlers_.emplace_back( result );
                return result;
            }
        }

        void Release( const std::shared_ptr<ConnectionHandlerType>& connectionHandler )
        {
            assert( connectionHandler != nullptr );
            connectionHandler->Stop( );
            std::unique_lock lock( criticalSection_ );
            
            if ( freeConnectionHandlers_.size( ) < MaxFreeConnectionHandlers )
            {
                freeConnectionHandlers_.emplace_back( connectionHandler );
            }
            else
            {
                auto it = std::ranges::find_if( connectionHandlers_, [connectionHandler]( const auto& ptr ) { return ptr == connectionHandler; } );
                if ( it != connectionHandlers_.end( ) )
                {
                    connectionHandlers_.erase( it );
                }
            }
        }
    };



    enum class ListenerHandlerState : UInt32
    {
        Unknown,
        Starting,
        Listening,
        Stopping,
        Stopped,
        Destroying
    };


    class ListenerAcceptRequest : public Sockets::AcceptRequest
    {
    public:
        using Base = Sockets::AcceptRequest;
        static constexpr size_t ReceiveDataLength = 1024;
        static constexpr size_t BufferSize = Sockets::AcceptRequest::CalculateBufferSizeFor( ReceiveDataLength );
    private:
        Byte buffer_[BufferSize] = {};
    public:
        ListenerAcceptRequest( SOCKET listenSocketHandle, SOCKET acceptSocketHandle = INVALID_SOCKET )
            : Base( listenSocketHandle, acceptSocketHandle, buffer_, ReceiveDataLength )
        {
        }

        ListenerAcceptRequest( const TcpSocket& listenSocket, const TcpSocket& acceptSocket )
            : ListenerAcceptRequest( listenSocket.Handle(), acceptSocket.Handle() )
        {
        }

        void Reset( SOCKET listenSocketHandle, SOCKET acceptSocketHandle = INVALID_SOCKET )
        {
            Base::Reset( listenSocketHandle, acceptSocketHandle, buffer_, ReceiveDataLength );
        }

        void Reset( const TcpSocket& listenSocket, const TcpSocket& acceptSocket )
        {
            Base::Reset( listenSocket, acceptSocket, buffer_, ReceiveDataLength );
        }


    };


    template< typename DerivedT, typename ConnectionHandlerT, typename ConnectionHandlerPoolT = ConnectionHandlerPool<DerivedT, ConnectionHandlerT> >
    class ListenerHandler : public SocketHandler<DerivedT>
    {
        template<typename DerivedT>
        friend class SocketHandler;

        template< typename DerivedT, typename ListenerHandlerT, typename RequestsPoolT >
        friend class ConnectionHandler;
    public:    
        using Base = SocketHandler<DerivedT>;
        using DerivedType = DerivedT;
        using ConnectionHandlerType = ConnectionHandlerT;
        using ConnectionHandlerPoolType = ConnectionHandlerPoolT;
        using ActiveConnectionHandlerMap = boost::container::flat_map<SOCKET, std::shared_ptr<ConnectionHandlerType> >;
    private:
        CriticalSection criticalSection_;
        mutable std::atomic<ListenerHandlerState> state_ = ListenerHandlerState::Unknown;
        Sockets::Address address_;
        ActiveConnectionHandlerMap activeConnectionHandlers_;
        Server::TcpSocket socket_;
        size_t initialSocketCount_;
        Sockets::RequestPool< ListenerAcceptRequest, 64> acceptRequestPool_;
        std::atomic<size_t> outstandingRequests_;
        ConnectionHandlerPoolType pool_;
    private:
        template<typename ... ConnectionHandlerArgs>
        ListenerHandler( const std::shared_ptr<IO::Context>& context, const Address& listenAddress, size_t initialSocketCount, AddressFamily addressFamily, Server::TcpSocket&& socket, ConnectionHandlerArgs&& ... connectionHandlerArgs )
            : Base( context, socket ), address_( listenAddress ), initialSocketCount_( initialSocketCount ), socket_( std::move( socket ) ), outstandingRequests_(0), pool_( static_cast<DerivedType&>( *this ), addressFamily, std::forward<ConnectionHandlerArgs>( connectionHandlerArgs )... )
        {
            
        }
    public:
        template<typename ... ConnectionHandlerArgs>
        ListenerHandler( const std::shared_ptr<IO::Context>& context, const Address& listenAddress, size_t initialSocketCount, AddressFamily addressFamily, ConnectionHandlerArgs&& ... connectionHandlerArgs )
            : ListenerHandler( context, listenAddress, initialSocketCount, addressFamily, Server::TcpSocket( addressFamily, SocketFlags::Overlapped ), std::forward<ConnectionHandlerArgs>( connectionHandlerArgs )... )
        {
        }

        ~ListenerHandler( )
        {
            state_ = ListenerHandlerState::Destroying;
#ifdef _DEBUG
            printf( "In ListenerHandler::~ListenerHandler\n" );
#endif
        }

        bool IsRunning( ) const
        {
            auto state = state_.load( );
            return state == ListenerHandlerState::Listening;
        }
        

        const Sockets::Address& Address( ) const
        {
            return address_;
        }

        std::shared_ptr<ConnectionHandlerType> GetConnectionHandlerBySocket( SOCKET socketHandle ) const
        {
            std::unique_lock lock( criticalSection_ );
            auto it = activeConnectionHandlers_.find( socketHandle );
            if ( it != activeConnectionHandlers_.end( ) )
            {
                auto result = it->second;
                return result;
            }
            return nullptr;
        }
        std::shared_ptr<ConnectionHandlerType> GetConnectionHandlerBySocket( const TcpSocket& socket ) const
        {
            SOCKET socketHandle = socket.Handle( );
            return GetConnectionHandlerBySocket( socketHandle );
        }
    private:
        void AquireAndStartConnectionHandler( )
        {
            if ( IsRunning( ) )
            {
                std::unique_lock lock( criticalSection_ );
                auto handler = pool_.Aquire( );
                activeConnectionHandlers_.emplace( handler->Socket( ).Handle( ), handler );
                BeginAccept( handler );
            }
        }

        void ReleaseConnectionHandler( const std::shared_ptr<ConnectionHandlerType>& connectionHandler )
        {
            std::unique_lock lock( criticalSection_ );
            const auto& connectionSocket = connectionHandler->Socket( );
            auto connectionSocketHandle = connectionSocket.Handle( );
            auto it = activeConnectionHandlers_.find( connectionSocketHandle );
            if ( it != activeConnectionHandlers_.end( ) )
            {
                activeConnectionHandlers_.erase( it );
                pool_.Release( connectionHandler );
            }

        }

    public:
        const Server::TcpSocket& Socket( ) const
        {
            return socket_;
        }

    private:
        void Bind( ) const
        {
            socket_.Bind( address_ );
        }

        void Listen( int backlog = SOMAXCONN ) const
        {
            socket_.Listen( backlog );
            state_ = ListenerHandlerState::Listening;
        }

        void Accept( )
        {
            std::unique_lock lock( criticalSection_ );

            for ( size_t i = 0; i < initialSocketCount_; ++i )
            {
                auto handler = pool_.Aquire( );
                activeConnectionHandlers_.emplace( handler->Socket( ).Handle( ), handler );
                BeginAccept( handler );
            }
        }
    public:
        void Start( ) override
        {
            state_ = ListenerHandlerState::Starting;
            Bind( );
            Listen( );
            Accept( );
        }

        void Stop( ) override
        {
            auto state = state_.load( );
            if ( state != ListenerHandlerState::Unknown && state < ListenerHandlerState::Stopping )
            {
                state_ = ListenerHandlerState::Stopping;

                CancelIoEx( std::bit_cast<HANDLE>( socket_.Handle( ) ), nullptr );

                while ( outstandingRequests_.load( ) != 0 )
                {
                    CurrentThread::Yield( );
                }
                socket_.Close( );

                for ( auto& entry : activeConnectionHandlers_ )
                {
                    entry.second->Stop( );
                }
                
                std::unique_lock lock( criticalSection_ );
                activeConnectionHandlers_.clear( );
                pool_.Clear( );
                state_ = ListenerHandlerState::Stopped;
            }
        }

    private:
        AcceptRequest* AcquireAcceptRequest( const std::shared_ptr<ConnectionHandlerType>& connectionHandler )
        {
            std::unique_lock lock( criticalSection_ );
            auto* result = acceptRequestPool_.Acquire( socket_, connectionHandler->Socket( ) );
            outstandingRequests_++;
            return result;
        }
        void ReleaseAcceptRequest( AcceptRequest* request )
        {
            std::unique_lock lock( criticalSection_ );
            acceptRequestPool_.Release( static_cast<ListenerAcceptRequest*>( request ) );
            outstandingRequests_--;
        }

        void BeginAccept( const std::shared_ptr<ConnectionHandlerType>& connectionHandler )
        {
            if ( IsRunning( ) )
            {
                auto* request = AcquireAcceptRequest( connectionHandler );
                bool executedSynchronously = Base::BeginAsyncAccept( request );
                if ( executedSynchronously )
                {
                    ReleaseAcceptRequest( request );
                }
            }
        }
        

    protected:
        bool BeforeHandleAcceptCompleted( AcceptRequest* request )
        {
            if ( IsRunning( ) )
            {
                AquireAndStartConnectionHandler( );

                WinError ioResult = static_cast<WinError>( request->IoResult( ) );
                if ( ioResult != WinError::None )
                {
                    auto acceptSocket = request->AcceptSocket( );
                    auto connectionHandler = GetConnectionHandlerBySocket( acceptSocket );
                    if ( connectionHandler )
                    {
                        ReleaseConnectionHandler( connectionHandler );
                    }
                    return false;
                }
                else
                {
                    auto acceptSocketHandle = request->AcceptSocket( );
                    auto connectionHandler = GetConnectionHandlerBySocket( acceptSocketHandle );
                    assert( connectionHandler != nullptr );
                    const TcpSocket& acceptSocket = connectionHandler->Socket( );
                    acceptSocket.UpdateAcceptContext( socket_ );
                    request->GetAddresses( connectionHandler->localAddress_, connectionHandler->remoteAddress_ );
                    return true;
                }
            }
            else
            {
                return false;
            }
        }

        bool ProcessAcceptCompleted( AcceptRequest* request ) noexcept
        {
            auto result = Base::ProcessAcceptCompleted( request );
            if ( result == false )
            {
                if ( IsRunning( ) )
                {
                    auto acceptSocket = request->AcceptSocket( );
                    auto connectionHandler = GetConnectionHandlerBySocket( acceptSocket );
                    if ( connectionHandler )
                    {
                        result = connectionHandler->OnAcceptCompleted( request );
                    }
                }
            }
            return result;
        }

    protected:
        virtual void ProcessDone( Base::Message& message ) override
        {
            ListenerAcceptRequest* request = static_cast<ListenerAcceptRequest*>( message.Request( ) );
            if ( request )
            {
                ReleaseAcceptRequest( request );
            }
        }

    };


}


#endif
