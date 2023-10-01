#pragma once
#ifndef HCCZMQ_h_
#define HCCZMQ_h_


#include <zmq.hpp>
#include "HCCIOBase.h"
#include "HCCIO.h"
#include "HCCMemory.h"
#include "HCCThread.h"

namespace Harlinn::Common::Core::ZeroMq
{
    using SocketType = zmq::socket_type;
    using SendFlags = zmq::send_flags;
    using SendResult = zmq::send_result_t;
    using ReceiveFlags = zmq::recv_flags;
    using ReceiveBufferResult = zmq::recv_buffer_result_t;
    using ReceiveResult = zmq::recv_result_t;
    using MutableBuffer = zmq::mutable_buffer;
    using PollItem = zmq::pollitem_t;
    using ConstBuffer = zmq::const_buffer;

    using MemoryManager = FixedSizeMemoryManager<64 * 1024, 1024>;


    class Message : public zmq::message_t
    {
    public:
        using Base = zmq::message_t;

        Message( ) noexcept
            : Base()
        {
        }

        explicit Message( size_t size )
            : Base( size )
        {
        }

        template<class ForwardIter> 
        Message( ForwardIter first, ForwardIter last )
            : Base( first, last )
        {
        }

        Message( const void* data_, size_t size_ )
            : Base( data_, size_ )
        {
        }

        Message( void* data_, size_t size_, zmq::free_fn* ffn_, void* hint_ = ZMQ_NULLPTR )
            : Base( data_, size_, ffn_, hint_ )
        {
        }



    };

    
    class Context;

    class Socket : public zmq::socket_t
    {
    public:
        using Base = zmq::socket_t;
    private:    
        ZeroMq::Context* context_;
    public:
        inline Socket( ZeroMq::Context& context, SocketType socketType );

        Socket( const Socket& other ) = delete;
        Socket( Socket&& other ) = default;

        Socket& operator = ( const Socket& other ) = delete;
        Socket& operator = ( Socket&& other ) = default;


        ZeroMq::Context& Context( ) noexcept
        {
            return *context_;
        }

        inline ZeroMq::MemoryManager* MemoryManager( );


        void Close( )
        {
            Base::close( );
        }

        void Connect( const char* address )
        {
            Base::connect( address );
        }
        template<SimpleAnsiStringLike StringT>
        void Connect( const StringT& address )
        {
            Base::connect( address.c_str() );
        }
        template<SimpleWideStringLike StringT>
        void Connect( const StringT& address )
        {
            auto str = ToAnsiString( address );
            Base::connect( str.c_str( ) );
        }
        void Connect( const wchar_t* address )
        {
            auto str = ToAnsiString( address );
            Base::connect( str.c_str( ) );
        }

        void Disconnect( const char* address )
        {
            Base::disconnect( address );
        }

        template<SimpleAnsiStringLike StringT>
        void Disconnect( const StringT& address )
        {
            Base::disconnect( address.c_str( ) );
        }
        template<SimpleWideStringLike StringT>
        void Disconnect( const StringT& address )
        {
            auto str = ToAnsiString( address );
            Base::disconnect( str.c_str( ) );
        }
        void Disconnect( const wchar_t* address )
        {
            auto str = ToAnsiString( address );
            Base::disconnect( str.c_str( ) );
        }

        void Bind( const char* address )
        {
            Base::bind( address );
        }

        template<SimpleAnsiStringLike StringT>
        void Bind( const StringT& address )
        {
            Base::bind( address.c_str( ) );
        }
        template<SimpleWideStringLike StringT>
        void Bind( const StringT& address )
        {
            auto str = ToAnsiString( address );
            Base::bind( str.c_str( ) );
        }
        void Bind( const wchar_t* address )
        {
            auto str = ToAnsiString( address );
            Base::bind( str.c_str( ) );
        }

        void Unbind( const char* address )
        {
            Base::unbind( address );
        }

        template<SimpleAnsiStringLike StringT>
        void Unbind( const StringT& address )
        {
            Base::unbind( address.c_str( ) );
        }
        template<SimpleWideStringLike StringT>
        void Unbind( const StringT& address )
        {
            auto str = ToAnsiString( address );
            Base::unbind( str.c_str( ) );
        }
        void Unbind( const wchar_t* address )
        {
            auto str = ToAnsiString( address );
            Base::unbind( str.c_str( ) );
        }



        SendResult Send( Message& message, SendFlags flags = SendFlags::none )
        {
            return Base::send( message, flags );
        }
        
        SendResult Send( ConstBuffer& buffer, SendFlags flags = SendFlags::none )
        {
            return Base::send( buffer, flags );
        }

        SendResult Send( const IO::MemoryStream& memoryStream, SendFlags flags = SendFlags::none )
        {
            ConstBuffer buffer( memoryStream.Buffer( ), memoryStream.Size( ) );
            return Base::send( buffer, flags );
        }

        SendResult Send( const void* data, size_t dataSize, SendFlags flags = SendFlags::none )
        {
            ConstBuffer buffer( data, dataSize );
            return Base::send( buffer, flags );
        }

        template<SimpleAnsiStringLike StringT>
        SendResult Send( const StringT& str, SendFlags flags = SendFlags::none )
        {
            ConstBuffer buffer( str.data( ), str.size( ) );
            return Base::send( buffer, flags );
        }

        template<SimpleWideStringLike StringT>
        SendResult Send( const StringT& wstr, SendFlags flags = SendFlags::none )
        {
            auto str = ToAnsiString( wstr );
            ConstBuffer buffer( str.data( ), str.size( ) );
            return Base::send( buffer, flags );
        }
        SendResult Send( const wchar_t* wstr, SendFlags flags = SendFlags::none )
        {
            auto str = ToAnsiString( wstr );
            ConstBuffer buffer( str.data( ), str.size( ) );
            return Base::send( buffer, flags );
        }

        SendResult Send( const char* astr, SendFlags flags = SendFlags::none )
        {
            auto str = ToAnsiString( astr );
            ConstBuffer buffer( str.data( ), str.size( ) );
            return Base::send( buffer, flags );
        }



        ReceiveResult Receive( Message& message, ReceiveFlags flags = ReceiveFlags::none )
        {
            return Base::recv( message, flags );
        }

        ReceiveBufferResult Receive( MutableBuffer& buffer, ReceiveFlags flags = ReceiveFlags::none )
        {
            return Base::recv( buffer, flags );
        }



    };

    
    class Context : public zmq::context_t
    {
    public:
        using Base = zmq::context_t;
        static constexpr size_t BlockSize = MemoryManager::BlockSize;
        static constexpr size_t MaxFreeCount = MemoryManager::MaxFreeCount;
        
    private:
        ZeroMq::MemoryManager memoryManager_;
    public:
        Context()
            : Base( )
        { }

        Context( int io_threads_, int max_sockets_ = ZMQ_MAX_SOCKETS_DFLT )
            : Base( io_threads_, max_sockets_ )
        {
        }

        void Close( )
        {
            Base::close( );
        }

        void Shutdown( )
        {
            Base::shutdown( );
        }


        ZeroMq::MemoryManager* MemoryManager( )
        {
            return &memoryManager_;
        }

    };

    inline Socket::Socket( ZeroMq::Context& context, SocketType socketType )
        : Base( context, socketType ), context_( &context )
    {
    }

    inline ZeroMq::MemoryManager* Socket::MemoryManager( )
    {
        return context_->MemoryManager( );
    }


    class ZMQStreamBase
    {
    public:
        
    private:
        ZeroMq::Socket& socket_;
    public:
        ZMQStreamBase( ZeroMq::Socket& socket )
            : socket_( socket )
        { }
    protected:
        ZeroMq::Socket& Socket( )
        {
            return socket_;
        }
    };


    class ZMQReadStream : public ZMQStreamBase
    {
    public:
        using recv_result_t = zmq::recv_result_t;
    private:
        Message message_;
        recv_result_t recvResult_;
        bool more_ = false;
        Byte* buffer_ = nullptr;
        size_t bufferSize_ = 0;
        size_t bufferPosition_ = 0;
    public:
        using Base = ZMQStreamBase;

        ZMQReadStream( ZeroMq::Socket& socket )
            : Base( socket )
        {
        }
    private:
        void ReceiveMessage( bool dontWait = false )
        {
            auto& socket = Socket( );
            recvResult_ = socket.recv( message_, dontWait ? zmq::recv_flags::dontwait : zmq::recv_flags::none );
            more_ = message_.more( );
            buffer_ = reinterpret_cast< Byte* >( message_.data( ) );
            bufferSize_ = message_.size( );
            bufferPosition_ = 0;
        }
    public:
        long long Read( void* buffer, size_t numberOfBytesToRead )
        {
            Byte* bufferPtr = reinterpret_cast< Byte* >( buffer );
            auto numberOfBytesRemainingToRead = numberOfBytesToRead;
            if ( numberOfBytesRemainingToRead )
            {
                do
                {
                    if ( bufferPosition_ >= bufferSize_ )
                    {
                        do
                        {
                            ReceiveMessage( true );
                        } while ( bufferSize_ == 0 && more_ == true );
                        if ( bufferSize_ == 0 )
                        {
                            return static_cast< long long >( numberOfBytesToRead - numberOfBytesRemainingToRead );
                        }
                    }
                    auto remaining = bufferSize_ - bufferPosition_;
                    if ( numberOfBytesRemainingToRead < remaining )
                    {
                        memcpy( bufferPtr, buffer_ + bufferPosition_, numberOfBytesRemainingToRead );
                        bufferPtr += numberOfBytesRemainingToRead;
                        bufferPosition_ += numberOfBytesRemainingToRead;
                        numberOfBytesRemainingToRead = 0;
                    }
                    else
                    {
                        memcpy( bufferPtr, buffer_ + bufferPosition_, remaining );
                        bufferPtr += remaining;
                        bufferPosition_ += remaining;
                        numberOfBytesRemainingToRead -= remaining;
                    }
                } while ( numberOfBytesRemainingToRead );
            }
            return numberOfBytesToRead;
        }

        constexpr bool CanRead( ) const noexcept
        {
            return true;
        }
        constexpr bool CanSeek( ) const noexcept
        {
            return false;
        }
        constexpr bool CanTimeout( ) const noexcept
        {
            return true;
        }
        constexpr bool CanWrite( ) const noexcept
        {
            return false;
        }
    };
    static_assert( IO::StreamReader<ZMQReadStream> );

    
    class ZMQWriteStream : public ZMQStreamBase
    {
    public:
        static constexpr size_t BufferSize = Context::BlockSize;
    private:
        size_t bufferPosition_ = 0;
        Byte* buffer_ = nullptr;
        bool lastSeen_ = false;
    public:
        using Base = ZMQStreamBase;

        ZMQWriteStream( ZeroMq::Socket& socket )
            : Base( socket )
        {
            buffer_ = AllocateBuffer( );
        }
        ~ZMQWriteStream( )
        {
            if ( bufferPosition_ )
            {
                Flush( );
            }
            FreeBuffer( );
        }
    private:
        Byte* AllocateBuffer()
        { 
            auto& socket = Socket( );
            auto* memoryManager = socket.MemoryManager( );
            return reinterpret_cast< Byte* >( memoryManager->Malloc( ) );
        }
        void FreeBuffer( )
        {
            if ( buffer_ )
            {
                auto& socket = Socket( );
                auto* memoryManager = socket.MemoryManager();
                memoryManager->Free( buffer_ );
            }
        }

        void SendMessage( bool last )
        {
            if ( lastSeen_ == false )
            {
                lastSeen_ = last;
                if ( bufferPosition_ )
                {
                    auto& socket = Socket( );
                    auto* memoryManager = socket.MemoryManager( );
                    Message message( buffer_, bufferPosition_, []( void* data, void* hint ) {if ( data && hint ) { reinterpret_cast< ZeroMq::MemoryManager* >( hint )->Free( data ); }}, memoryManager );
                    socket.send( std::move( message ), last ? SendFlags::none : SendFlags::sndmore );
                    bufferPosition_ = 0;
                    buffer_ = AllocateBuffer( );
                }
                else if ( last )
                {
                    auto& socket = Socket( );
                    Message message;
                    socket.send( std::move( message ), SendFlags::none );
                }
            }
        }
    public:
        long long Write( const void* buffer, size_t numberOfBytesToWrite )
        {
            const Byte* bufferPtr = reinterpret_cast< const Byte* >( buffer );
            auto numberOfBytesRemainingToWrite = numberOfBytesToWrite;
            while ( numberOfBytesRemainingToWrite )
            {
                auto remaining = BufferSize - bufferPosition_;
                if ( numberOfBytesRemainingToWrite < remaining )
                {
                    memcpy( buffer_ + bufferPosition_, bufferPtr, numberOfBytesRemainingToWrite );
                    bufferPosition_ += numberOfBytesRemainingToWrite;
                    bufferPtr += numberOfBytesRemainingToWrite;
                    numberOfBytesRemainingToWrite = 0;
                }
                else
                {
                    memcpy( buffer_ + bufferPosition_, bufferPtr, remaining );
                    bufferPosition_ = BufferSize;
                    SendMessage( false );
                    bufferPtr += remaining;
                    numberOfBytesRemainingToWrite -= remaining;
                }
            }
            return static_cast< long long >( numberOfBytesToWrite );
        }
    

        void Flush( )
        {
            auto& socket = Socket( );
            if ( socket.handle( ) != nullptr )
            {
                SendMessage( true );
            }
        }
    public:



        constexpr bool CanRead( ) const noexcept
        {
            return false;
            
        }
        constexpr bool CanSeek( ) const noexcept
        {
            return false;
        }
        constexpr bool CanTimeout( ) const noexcept
        {
            return true;
        }
        constexpr bool CanWrite( ) const noexcept
        {
            return true;
        }
    };
    static_assert( IO::StreamWriter<ZMQWriteStream> );
    static_assert( IO::StreamFlush<ZMQWriteStream> );

    class ZMQServer : public std::enable_shared_from_this<ZMQServer>
    {
    public:
        ZeroMq::Context& context_;
        WideString threadName_;
        AnsiString serverEndpoint_;
        AnsiString serverInprocEndpoint_;
        Thread thread_;
    public:
        boost::signals2::signal<void( ZMQServer* sender, IO::MemoryStream& requestStream, IO::MemoryStream& replyStream, IO::MemoryStream& errorStream )> OnProcess;
        ZMQServer( ZeroMq::Context& context, const WideString& threadName, const AnsiString& serverEndpoint, const AnsiString& serverInprocEndpoint )
            : context_( context ), threadName_( threadName ), serverEndpoint_( serverEndpoint ), serverInprocEndpoint_( serverInprocEndpoint )
        { }

        ZeroMq::Context& Context( )
        {
            return context_;
        }

        virtual void Start( )
        {
            if ( threadName_.empty( ) )
            {
                threadName_ = L"ZMQServer";
            }
            auto threadRunner = std::bind( &ZMQServer::Run, this );
            thread_ = Thread( [ threadRunner ]( )
                {
                    threadRunner( );
                } );
        }

        virtual void Stop( )
        {
            if ( thread_.GetHandle( ) )
            {
                auto socket = CreateInprocServerRequestSocket( );
                socket.Connect( serverInprocEndpoint_ );
                socket.Send( "S" );
                socket.Disconnect( serverInprocEndpoint_ );
                thread_.join( );
            }
        }

        const AnsiString& LocalServerEndPoint( ) const noexcept
        {
            return serverEndpoint_;
        }
        const AnsiString& LocalServerEndPointForRemoteHost( ) const noexcept
        {
            if ( serverEndpoint_.StartsWith( "tcp://*:" ) )
            {

            }
            return serverEndpoint_;
        }

    protected:
        virtual bool Process( IO::MemoryStream& requestStream, IO::MemoryStream& replyStream, IO::MemoryStream& errorStream )
        {
            OnProcess( this, requestStream, replyStream, errorStream );
            return true;
        }
    private:
        Socket CreateServerSocket( )
        {
            Socket socket( context_, SocketType::rep );
            return socket;
        }

        Socket CreateCreateInprocServerResponseSocket( )
        {
            Socket socket( context_, zmq::socket_type::rep );
            return socket;
        }

        Socket CreateInprocServerRequestSocket( )
        {
            Socket socket( context_, zmq::socket_type::req );
            return socket;
        }

        void Run( )
        {
            try
            {
                if ( this->BeforeProcessMessages( ) )
                {
                    ProcessMessages( );
                    this->AfterProcessMessages( );
                }
            }
            catch ( ... )
            {

            }
        }
    protected:
        virtual bool BeforeProcessMessages( )
        {
            return true;
        }

        virtual void AfterProcessMessages( )
        {

        }
    private:
        void ProcessMessages( )
        {
            try
            {
                if ( threadName_.empty( ) == false )
                {
                    CurrentThread::SetDescription( threadName_.c_str( ) );
                }

                AnsiString endpoint = serverEndpoint_;
                AnsiString inprocEndPoint = serverInprocEndpoint_;

                auto socket = CreateServerSocket( );
                auto inprocSocket = CreateCreateInprocServerResponseSocket( );

                socket.bind( endpoint.c_str( ) );
                inprocSocket.bind( inprocEndPoint.c_str( ) );

                printf( "TCP Server listening on:%s\n", endpoint.c_str( ) );

                PollItem pollItems[ 2 ] =
                {
                    { socket.handle( ), 0, static_cast< short >( ZMQ_POLLIN ), 0 },
                    { inprocSocket.handle( ), 0, static_cast< short >( ZMQ_POLLIN ), 0 }
                };


                while ( true )
                {
                    zmq::poll( pollItems, 2 );

                    if ( ( pollItems[ 0 ].revents & ZMQ_POLLIN ) == ZMQ_POLLIN )
                    {
                        /*
                        ZMQReadStream requestStream( socket );
                        ZMQWriteStream replyStream( socket );
                        ZMQWriteStream errorStream( socket );
                        bool processed = this->Process( requestStream, replyStream, errorStream );
                        */
                        
                        Message requestMessage;
                        socket.Receive( requestMessage );

                        IO::MemoryStream requestStream( reinterpret_cast<Byte*>(requestMessage.data()), requestMessage.size(), false );
                        IO::MemoryStream replyStream;
                        replyStream.SetCapacity( 64 * 1024 );
                        
                        IO::MemoryStream errorStream;

                        bool processed = this->Process( requestStream, replyStream, errorStream );

                        if ( processed )
                        {
                            socket.Send( replyStream );
                        }
                        else
                        {
                            socket.Send( errorStream );
                        }
                    }

                    if ( ( pollItems[ 1 ].revents & ZMQ_POLLIN ) == ZMQ_POLLIN )
                    {
                        Message message;
                        inprocSocket.Receive( message );

                        break;
                    }
                }

                wprintf( L"TCP Server shutting down\n" );

            }
            catch ( ... )
            {

            }
        }
        
    };

    class ZMQNotification : public std::enable_shared_from_this<ZMQNotification>
    {
    public:
        ZMQNotification( ) = default;
        virtual ~ZMQNotification( ) = default;
        virtual const Byte* data( ) const = 0;
        virtual size_t size( ) const = 0;
    };

    class ZMQNotificationMemoryStream : public ZMQNotification, public IO::MemoryStream
    { 
    public:
        using Base = IO::MemoryStream;
        ZMQNotificationMemoryStream( ) = default;
        ZMQNotificationMemoryStream( Byte* buffer, size_t bufferSize )
            : Base( buffer, bufferSize )
        { }

        ZMQNotificationMemoryStream( Byte* buffer, size_t bufferSize, bool ownsData )
            : Base( buffer, bufferSize, ownsData )
        { }

        ZMQNotificationMemoryStream( const MemoryStream& other )
            : Base( other )
        { }

        ZMQNotificationMemoryStream( MemoryStream&& other )
            : Base( std::move(other) )
        { }

        virtual const Byte* data( ) const override
        {
            return Base::Buffer( );
        }
        virtual size_t size( ) const override
        {
            return Base::Size( );
        }

    };


    class ZMQNotificationClientEndPoint : public std::enable_shared_from_this<ZMQNotificationClientEndPoint>
    {
        AnsiString endPoint_;
    public:
        ZMQNotificationClientEndPoint(const AnsiString& endPoint )
            : endPoint_( endPoint )
        { }
        virtual ~ZMQNotificationClientEndPoint( ) = default;

        const AnsiString& EndPoint( ) const noexcept
        {
            return endPoint_;
        }
    };



    class ZMQNotificationServer : public ZMQServer
    {
    public:
        using Base = ZMQServer;
        static constexpr size_t MaxNotificationQueueSize = 1024;
    protected:
        virtual void DoBeforeSendNotification( Socket& socket, const std::shared_ptr<ZMQNotificationClientEndPoint>& clientEndpoint, const std::shared_ptr<ZMQNotification>& notification )
        {

        }
        virtual void DoAfterSendNotification( Socket& socket, const std::shared_ptr<ZMQNotificationClientEndPoint>& clientEndpoint, const std::shared_ptr<ZMQNotification>& notification )
        {

        }
    private:
        class NotificationEntry : public std::enable_shared_from_this<NotificationEntry>
        {
            enum class NotificationMessageType
            {
                Unknown,
                Stop,
                Send
            };
            struct NotificationMessage
            {
                NotificationMessageType Type;
                std::shared_ptr<ZMQNotification> Payload;

            };
            using ConcurrentQueue = SimpleConcurrentQueue<NotificationMessage, MaxNotificationQueueSize>;

            ZMQNotificationServer& server_;
            ConcurrentQueue messages_;
            WideString threadName_;
            std::atomic<bool> started_;
            std::atomic<bool> stopped_;
            std::shared_ptr<ZMQNotificationClientEndPoint> clientEndpoint_;
            std::unique_ptr<Socket> socket_;
            Thread thread_;
        public:
            NotificationEntry( ZMQNotificationServer& server, const std::shared_ptr<ZMQNotificationClientEndPoint>& clientEndpoint )
                : server_( server ), clientEndpoint_( clientEndpoint )
            {
            }

            NotificationEntry( ZMQNotificationServer& server, const AnsiString& clientEndpoint )
                : server_( server ), clientEndpoint_( std::make_shared<ZMQNotificationClientEndPoint>( clientEndpoint ) )
            { }


            void Start( )
            {
                auto self = shared_from_this( );
                thread_ = Thread( [ self ]
                    {
                        const auto& threadName = self->ThreadName( );
                        CurrentThread::SetDescription( threadName.c_str( ) );
                        self->Run( );
                    } );
            }
            void Stop( )
            {
                if ( stopped_ )
                    return;
                stopped_ = true;
                PostStopMessage( );
                messages_.Close( );
                thread_.Wait( );
            }


            Socket CreateNotificationSocket( )
            {
                Socket socket( server_.Context(), SocketType::req );
                return socket;
            }

            const WideString& ThreadName( ) const noexcept
            {
                return threadName_;
            }

            bool Started( ) const noexcept
            {
                return started_;
            }

            bool Stopped( ) const noexcept
            {
                return stopped_;
            }

            bool PostNotification( const std::shared_ptr<ZMQNotification>& notification )
            {
                if ( messages_.IsClosed( ) == false )
                {
                    NotificationMessage message{ .Type = NotificationMessageType::Send, .Payload = notification };
                    messages_.Push( message );
                    return true;
                }
                else
                {
                    return false;
                }
            }

            bool PostStopMessage( )
            {
                if ( messages_.IsClosed( ) == false )
                {
                    NotificationMessage message{ .Type = NotificationMessageType::Stop, .Payload = nullptr };
                    messages_.Push( message );
                    return true;
                }
                else
                {
                    return false;
                }
            }

            void ProcessMessage( const NotificationMessage& message )
            {
                switch ( message.Type )
                {
                    case NotificationMessageType::Send:
                        ProcessSendMessage( message.Payload );
                        break;
                }
            }

            void DoBeforeSendNotification( const std::shared_ptr<ZMQNotification>& notification )
            {
                server_.DoBeforeSendNotification( *socket_.get( ), clientEndpoint_, notification );
            }
            void DoAfterSendNotification( const std::shared_ptr<ZMQNotification>& notification )
            {
                server_.DoAfterSendNotification( *socket_.get( ), clientEndpoint_, notification );
            }

            void ProcessSendMessage( const std::shared_ptr<ZMQNotification>& notification )
            {
                if ( notification )
                {
                    if ( socket_ == nullptr )
                    {
                        socket_ = std::make_unique<Socket>( server_.Context(), SocketType::req );
                        socket_->Connect( clientEndpoint_->EndPoint() );
                    }
                    DoBeforeSendNotification( notification );
                    socket_->Send( notification->data(), notification->size() );
                    Message replyMessage;
                    socket_->Receive( replyMessage );
                    DoAfterSendNotification( notification );
                }
            }

            void Run( )
            {
                try
                {
                    ProcessMessages( );
                }
                catch(...)
                { }
                if ( socket_ != nullptr )
                {
                    socket_->Disconnect( clientEndpoint_->EndPoint() );
                    socket_->Close( );
                    socket_.reset( );
                }
                
            }

            void ProcessMessages( )
            {
                while ( true )
                {
                    try
                    {
                        NotificationMessage message;
                        messages_.Pop( message );
                        if ( message.Type != NotificationMessageType::Stop )
                        {
                            ProcessMessage( message );
                        }
                        else
                        {
                            break;
                        }
                    }
                    catch ( std::exception& ex )
                    {
                        auto message = Format( L"Exception caught in {}", CURRENT_FUNCTION );
                     //   HandleException( ex, message );
                    }
                }
            }
        };

        CriticalSection criticalSection_;
        std::unordered_map<AnsiString, std::shared_ptr<NotificationEntry>> entries_;
    public:
        ZMQNotificationServer( ZeroMq::Context& context, const WideString& threadName, const AnsiString& serverEndpoint, const AnsiString& serverInprocEndpoint )
            : Base( context, threadName, serverEndpoint, serverInprocEndpoint )
        { }
    private:
        NotificationEntry* FindClient( const AnsiString& clientEndpoint )
        {
            auto it = entries_.find( clientEndpoint );
            if ( it != entries_.end( ) )
            {
                return it->second.get( );
            }
        }

        void RemoveAll(  )
        {
            std::lock_guard guard( criticalSection_ );
            while ( entries_.size( ) )
            {
                auto name = entries_.begin( )->first;
                RemoveClient( name );
            }
        }
    protected:
        virtual void AfterProcessMessages( ) override
        {
            RemoveAll( );
            Base::AfterProcessMessages( );
        }
    public:

        bool AddClient( const std::shared_ptr<ZMQNotificationClientEndPoint>& clientEndpoint )
        {
            std::lock_guard guard( criticalSection_ );
            if ( entries_.contains( clientEndpoint->EndPoint() ) == false )
            {
                auto newEntry = std::make_shared<NotificationEntry>( *this, clientEndpoint );
                entries_.emplace( clientEndpoint->EndPoint( ), newEntry );
                newEntry->Start( );
                return true;
            }
            return false;
        }

        bool AddClient( const AnsiString& clientEndpoint )
        {
            return AddClient( std::make_shared<ZMQNotificationClientEndPoint>( clientEndpoint ) );
        }

        bool RemoveClient( const AnsiString& clientEndpoint )
        {
            std::lock_guard guard( criticalSection_ );
            auto it = entries_.find( clientEndpoint );
            if ( it != entries_.end( ) )
            {
                auto entry = it->second;
                entries_.erase( clientEndpoint );
                entry->Stop( );
            }
            return false;
        }
        bool RemoveClient( const std::shared_ptr<ZMQNotificationClientEndPoint>& clientEndpoint )
        {
            return RemoveClient( clientEndpoint->EndPoint( ) );
        }


        bool Publish( const std::shared_ptr<ZMQNotification>& notification )
        {
            std::lock_guard guard( criticalSection_ );
            if ( entries_.size( ) )
            {
                for ( auto& entry : entries_ )
                {
                    entry.second->PostNotification( notification );
                }
                return true;
            }
            return false;
        }

        bool Publish( const AnsiString& sender, const std::shared_ptr<ZMQNotification>& notification )
        {
            std::lock_guard guard( criticalSection_ );
            if ( entries_.size( ) )
            {
                for ( auto& entry : entries_ )
                {
                    if ( entry.first != sender )
                    {
                        entry.second->PostNotification( notification );
                    }
                }
                return true;
            }
            return false;
        }


    };


    class ZMQNotificationClient : public ZMQServer
    {
        AnsiString serverEndpoint_;
        Socket clientSocket_;
    public:
        using Base = ZMQServer;
        ZMQNotificationClient( ZeroMq::Context& context, const WideString& threadName, const AnsiString& serverEndpoint, const AnsiString& notificationEndpoint, const AnsiString& notificationInprocEndpoint )
            : Base( context, threadName, notificationEndpoint, notificationInprocEndpoint ), serverEndpoint_( serverEndpoint ), clientSocket_( context, SocketType::req )
        {
        }

        Socket& ClientSocket( )
        {
            return clientSocket_;
        }

        void Connect( )
        {
            clientSocket_.Connect( serverEndpoint_ );
        }

        void Disconnect( )
        {
            clientSocket_.Connect( serverEndpoint_ );
        }

        SendResult Send( Message& message, SendFlags flags = SendFlags::none )
        {
            return clientSocket_.Send( message, flags );
        }

        SendResult Send( ConstBuffer& buffer, SendFlags flags = SendFlags::none )
        {
            return clientSocket_.Send( buffer, flags );
        }

        SendResult Send( const IO::MemoryStream& memoryStream, SendFlags flags = SendFlags::none )
        {
            ConstBuffer buffer( memoryStream.Buffer( ), memoryStream.Size( ) );
            return clientSocket_.Send( buffer, flags );
        }

        SendResult Send( const void* data, size_t dataSize, SendFlags flags = SendFlags::none )
        {
            ConstBuffer buffer( data, dataSize );
            return clientSocket_.Send( buffer, flags );
        }

        template<SimpleAnsiStringLike StringT>
        SendResult Send( const StringT& str, SendFlags flags = SendFlags::none )
        {
            ConstBuffer buffer( str.data( ), str.size( ) );
            return clientSocket_.Send( buffer, flags );
        }

        template<SimpleWideStringLike StringT>
        SendResult Send( const StringT& wstr, SendFlags flags = SendFlags::none )
        {
            auto str = ToAnsiString( wstr );
            ConstBuffer buffer( str.data( ), str.size( ) );
            return clientSocket_.Send( buffer, flags );
        }
        SendResult Send( const wchar_t* wstr, SendFlags flags = SendFlags::none )
        {
            auto str = ToAnsiString( wstr );
            ConstBuffer buffer( str.data( ), str.size( ) );
            return clientSocket_.Send( buffer, flags );
        }

        SendResult Send( const char* astr, SendFlags flags = SendFlags::none )
        {
            auto str = ToAnsiString( astr );
            ConstBuffer buffer( str.data( ), str.size( ) );
            return clientSocket_.Send( buffer, flags );
        }


        ReceiveResult Receive( Message& message, ReceiveFlags flags = ReceiveFlags::none )
        {
            return clientSocket_.Receive( message, flags );
        }

        ReceiveBufferResult Receive( MutableBuffer& buffer, ReceiveFlags flags = ReceiveFlags::none )
        {
            return clientSocket_.Receive( buffer, flags );
        }



    };



}


#endif
