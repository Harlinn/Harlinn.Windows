#pragma once
#ifndef __HCCSOCKETSERVER_H__
#define __HCCSOCKETSERVER_H__
/*
   Copyright 2024 Espen Harlinn

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

namespace Harlinn::Common::Core::IO::Sockets::Server
{
    template <typename DerivedT>
    class TcpConnectionHandlerBase : public SocketHandler<DerivedT>
    {
    public:
        using Base = SocketHandler<DerivedT>;
        using DerivedType = DerivedT;
    private:
        Sockets::TcpSocket socket_;
    public:
        TcpConnectionHandlerBase( const std::shared_ptr<IO::Context>& context, AddressFamily addressFamily = AddressFamily::InterNetworkV6 )
            : Base( context ), socket_( addressFamily, SocketFlags::Overlapped )
        {
            Base::BindToContext( socket_ );
        }

        const Sockets::TcpSocket& Socket( ) const noexcept
        {
            return socket_;
        }
        SOCKET SocketHandle( ) const noexcept
        {
            return socket_.Handle( );
        }


        void Close( )
        {
            socket_.Close( );
        }
    };

    template <typename DerivedT>
    class TcpListenerBase : public SocketHandler<DerivedT>
    {
    public:
        using Base = SocketHandler<DerivedT>;
        using DerivedType = DerivedT;
    private:
        Sockets::TcpSocket socket_;
    public:
        TcpListenerBase( const std::shared_ptr<IO::Context>& context, AddressFamily addressFamily = AddressFamily::InterNetworkV6 )
            : Base( context ), socket_( addressFamily, SocketFlags::Overlapped )
        {
            Base::BindToContext( socket_ );
        }

        const Sockets::TcpSocket& Socket( ) const noexcept
        {
            return socket_;
        }
        SOCKET SocketHandle( ) const noexcept
        {
            return socket_.Handle( );
        }


        void Close( )
        {
            socket_.Close( );
        }
    };

    constexpr size_t BufferDataOffset( ) noexcept;

    class Buffer
    {
        friend constexpr size_t BufferDataOffset( ) noexcept;
    public:
        static constexpr size_t BufferSize = 64 * 1024;
        static constexpr size_t AddressInfoSize = AcceptRequest::CalculateBufferSizeFor( 0 );
        static constexpr size_t AcceptBufferSize = BufferSize - AddressInfoSize;
        using size_type = size_t;
        using value_type = Byte;
    private:
        size_t position_ = 0;
        size_t size_ = 0;
        Buffer* previous_ = nullptr;
        Buffer* next_ = nullptr;
        std::array<Byte, BufferSize> data_;
    public:
        Buffer( )
        {
            
        }
        
        void Reset( ) noexcept
        {
            position_ = 0;
            previous_ = nullptr;
            next_ = nullptr;
        }

        size_t Position( ) const noexcept
        {
            return position_;
        }
        void SetPosition( size_t position ) noexcept
        {
            position_ = position;
        }

        size_t Size( ) const noexcept
        {
            return size_;
        }

        size_t size( ) const noexcept
        {
            return size_;
        }

        void SetSize( size_t size ) noexcept
        {
            size_ = size;
        }

        Byte* Data( )
        {
            return data_.data( );
        }

        const Byte* Data( ) const
        {
            return data_.data( );
        }

        Byte* data( )
        {
            return data_.data( );
        }

        const Byte* data( ) const
        {
            return data_.data( );
        }

        bool Contains( const Byte* ptr ) const
        {
            return ptr >= data_.data( ) && ptr < (data_.data( ) + size( ));
        }


        Buffer* Previous( ) const noexcept
        {
            return previous_;
        }

        Buffer* Next( ) const noexcept
        {
            return next_;
        }

        void Append( Buffer* buffer )
        {
            assert( next_ == nullptr );
            next_ = buffer;
            buffer->previous_ = this;
        }

        void Prepend( Buffer* buffer )
        {
            assert( previous_ == nullptr );
            previous_ = buffer;
            buffer->next_ = this;
        }

        void Remove( )
        {
            if ( next_ )
            {
                if ( previous_ )
                {
                    next_->previous_ = previous_;
                    previous_->next_ = next_;
                    previous_ = nullptr;
                }
                else
                {
                    next_->previous_ = nullptr;
                }
                next_ = nullptr;
            }
            else if ( previous_ )
            {
                previous_->next_ = nullptr;
                previous_ = nullptr;
            }
        }

        void PrepareForWrite( )
        {
            position_ = 0;
            size_ = BufferSize;
        }
        void PrepareForRead( size_t numberOfBytesReceived )
        {
            position_ = 0;
            size_ = numberOfBytesReceived;
        }


        void PrepareForAccept( )
        {
            position_ = 0;
            size_ = AcceptBufferSize;
        }

        void PrepareForReceive( )
        {
            position_ = 0;
            size_ = BufferSize;
        }

        void PrepareForSend( )
        {
            size_ = position_;
            position_ = 0;
        }

        bool AtEnd( ) const
        {
            return position_ == size_;
        }

        size_t Write( const void* buffer, size_t bufferSize )
        {
            size_t remaining = BufferSize - position_;
            if ( bufferSize <= remaining )
            {
                Byte* dest = data_.data( ) + position_;
                memcpy( dest, buffer, bufferSize );
                position_ += bufferSize;
                return bufferSize;
            }
            else
            {
                Byte* dest = data_.data( ) + position_;
                memcpy( dest, buffer, remaining );
                position_ = BufferSize;
                return remaining;
            }
        }
        size_t Read( void* buffer, size_t bufferSize )
        {
            size_t remaining = size_ - position_;
            if ( bufferSize <= remaining )
            {
                Byte* source = data_.data( ) + position_;
                memcpy( buffer, source, bufferSize );
                position_ += bufferSize;
                return bufferSize;
            }
            else
            {
                Byte* source = data_.data( ) + position_;
                memcpy( buffer, source, remaining );
                position_ = size_;
                return remaining;
            }
        }

    };

    constexpr size_t BufferDataOffset( ) noexcept
    {
        return offsetof( Buffer, data_ );
    }


    namespace Internal
    {
        class BufferQueue
        {
            Buffer* head_ = nullptr;
            Buffer* tail_ = nullptr;
            size_t size_ = 0;
        public:
            BufferQueue()
            { }

            BufferQueue( const BufferQueue& ) = delete;
            BufferQueue( BufferQueue&& ) = delete;
            BufferQueue& operator = ( const BufferQueue& ) = delete;
            BufferQueue& operator = ( BufferQueue&& ) = delete;

            constexpr size_t size( ) const
            {
                return size_;
            }


            Buffer* Dequeue( )
            {
                if ( head_ != nullptr )
                {
                    auto result = head_;
                    head_ = head_->Next( );
                    result->Remove( );
                    if ( !head_ )
                    {
                        tail_ = nullptr;
                    }
                    size_--;
                    return result;
                }
                else
                {
                    return nullptr;
                }
            }

            void Enqueue( Buffer* buffer )
            {
                if ( head_ == nullptr )
                {
                    head_ = buffer;
                    tail_ = buffer;
                }
                else
                {
                    tail_->Append( buffer );
                    tail_ = buffer;
                }
                size_++;
            }



        };
    }



    template<typename DerivedT, typename ListenerT, typename ProtocolT >
    class TcpConnectionHandler;

    template<typename ConnectionHandlerT >
    class BufferedSocketStream
    {
        template<typename DerivedT, typename ListenerT, typename ProtocolT >
        friend class TcpConnectionHandler;
    public:
        using ConnectionHandlerType = ConnectionHandlerT;
    private:
        ConnectionHandlerType& handler_;
        const TcpSocket& socket_;
        bool canRead_ = true;
        Buffer* readBuffer_ = nullptr;
        Buffer* writeBuffer_ = nullptr;
    public:
        BufferedSocketStream( ConnectionHandlerType& handler )
            : handler_( handler ), socket_( handler.Socket( ) )
        {}
        ~BufferedSocketStream( )
        {
        }

        Buffer* AcquireReceiveBuffer( )
        {
            return handler_.AcquireReceiveBuffer( );
        }

        void ReleaseReceiveBuffer( Buffer* buffer )
        {
            handler_.ReleaseReceiveBuffer( buffer );
        }

        Buffer* AcquireSendBuffer( )
        {
            return handler_.AcquireSendBuffer( );
        }

        void Enqueue( Buffer* writeBuffer )
        {
            handler_.Enqueue( writeBuffer );
        }

        const Buffer* ReadBuffer( ) const
        {
            return readBuffer_;
        }
        Buffer* ReadBuffer( )
        {
            return readBuffer_;
        }
        void SetReadBuffer( Buffer* buffer )
        {
            readBuffer_ = buffer;
        }
        void ResetReadBuffer( Buffer* buffer )
        {
            assert( buffer );
            if ( readBuffer_ )
            {
                ReleaseReceiveBuffer( readBuffer_ );
            }
            readBuffer_ = buffer;
        }

        bool HasInputData( ) const
        {
            return readBuffer_ && readBuffer_->Position( ) < readBuffer_->Size( );
        }

        const Buffer* WriteBuffer( ) const
        {
            return writeBuffer_;
        }
        Buffer* WriteBuffer( )
        {
            return writeBuffer_;
        }
    private:
        long long ReadData( void* buffer, size_t numberOfBytesToRead )
        {
            Byte* ptr = reinterpret_cast<Byte*>( buffer );
            size_t bytesRetrieved = 0;
            while ( bytesRetrieved < numberOfBytesToRead )
            {
                size_t remaining = numberOfBytesToRead - bytesRetrieved;
                size_t count = readBuffer_->Read(ptr, remaining );
                bytesRetrieved += count;
                ptr += count;
                if ( count < remaining ) [[unlikely]]
                {
                    if ( canRead_ )
                    {
                        readBuffer_->PrepareForReceive( );
                        constexpr size_t bufferDataOffset = BufferDataOffset( );
                        Byte* buffer = reinterpret_cast<Byte*>( readBuffer_ ) + bufferDataOffset;
                        size_t bufferSize = readBuffer_->Size( );
                        size_t received = static_cast<size_t>(socket_.Receive( buffer, bufferSize, MessageFlags::None ));
                        if ( received )
                        {
                            readBuffer_->PrepareForRead( received );
                        }
                        else
                        {
                            // The socket was closed, or we timed out
                            canRead_ = false;
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }

            }
            return bytesRetrieved;
        }
    public:
        long long Read( void* buffer, size_t numberOfBytesToRead )
        {
            if ( readBuffer_ )
            {
                return ReadData( buffer, numberOfBytesToRead );
            }
            else
            {
                readBuffer_ = AcquireReceiveBuffer( );
                readBuffer_->PrepareForRead( 0 );
                return ReadData( buffer, numberOfBytesToRead );
            }
        }

    private:
        long long WriteData( const void* buffer, size_t numberOfBytesToWrite )
        {
            const Byte* ptr = reinterpret_cast<const Byte*>( buffer );
            size_t bytesWritten = 0;
            while ( bytesWritten < numberOfBytesToWrite )
            {
                size_t remaining = numberOfBytesToWrite - bytesWritten;
                size_t count = writeBuffer_->Write( ptr, remaining );
                if ( count < remaining ) [[unlikely]]
                {
                    Enqueue( writeBuffer_ );
                    writeBuffer_ = AcquireSendBuffer( );
                    writeBuffer_->PrepareForWrite( );
                }
                bytesWritten += count;
                ptr += count;
            }
            return bytesWritten;
        }
    public:
        long long Write( const void* buffer, size_t numberOfBytesToWrite )
        {
            if ( writeBuffer_ ) [[likely]]
            {
                return WriteData( buffer, numberOfBytesToWrite );
            }
            else
            {
                writeBuffer_ = AcquireSendBuffer( );
                writeBuffer_->PrepareForWrite( );
                return WriteData( buffer, numberOfBytesToWrite );
            }
        }

    };

    enum class TcpConnectionHandlerState
    {
        Unknown,
        Disconnected,
        Connected,
        FlushingWriteQueue,
        FlushingWriteQueueBeforeDisconnect,
        Disconnecting,
        Stopped
    };


    template<size_t N>
    class BufferPool
    {
    public:
        static constexpr size_t Size = N;
        static constexpr UInt32 DefaultAcquireTimeout = 60 * 1000;
    private:
        Semaphore semaphore_;
        CriticalSection criticalSection_;
        std::array<Buffer, Size> buffers_;
        size_t freeCount_ = Size;
        std::array<Buffer*, Size> freeBuffers_;
    public:
        BufferPool( )
            : semaphore_( Size, Size )
        {
            for ( size_t i = 0; i < Size; i++ )
            {
                freeBuffers_[i] = std::addressof( buffers_[i] );
            }
        }

        BufferPool( const BufferPool& other ) = delete;
        BufferPool( BufferPool&& other ) = delete;
        BufferPool& operator = ( const BufferPool& other ) = delete;
        BufferPool& operator = ( BufferPool&& other ) = delete;

        Buffer* Acquire( UInt32 timeoutInMillis = DefaultAcquireTimeout )
        {
            if ( semaphore_.Wait( timeoutInMillis ) )
            {
                std::unique_lock lock( criticalSection_ );
                if ( freeCount_ )
                {
                    freeCount_--;
                    auto* result = freeBuffers_[freeCount_];
#ifdef _DEBUG
                    freeBuffers_[freeCount_] = nullptr;
#endif
                    return result;
                }
            }
            return nullptr;
        }
    private:
        bool Contains( Buffer* buffer )
        {
            for ( size_t i = 0; i < Size; i++ )
            {
                if ( freeBuffers_[i] == buffer )
                {
                    return true;
                }
            }
            return false;
        }
    public:
        void Release( Buffer* buffer )
        {
            {
                std::unique_lock lock( criticalSection_ );
                assert( freeCount_ < Size );

#ifdef _DEBUG
                assert( freeBuffers_[freeCount_] == nullptr );
                assert( Contains( buffer ) );
#endif
                freeBuffers_[freeCount_] = buffer;
                freeCount_++;
            }
            semaphore_.Release( );
        }
    };



    template<typename DerivedT, typename ConnectionHandler>
    class TcpListener;

    template<typename DerivedT, typename ListenerT, typename ProtocolT >
    class TcpConnectionHandler : public Server::TcpConnectionHandlerBase< DerivedT >
    {
        template<typename DerivedT>
        friend class SocketHandler;

        template<typename DerivedT, typename ConnectionHandler>
        friend class TcpListener;

        template<typename ConnectionHandlerT>
        friend class BufferedSocketStream;

        static constexpr size_t MaxReceiveBuffers = 2;
        static constexpr size_t MaxSendBuffers = 20;
    public:
        using Base = Server::TcpConnectionHandlerBase< DerivedT >;
        using DerivedType = DerivedT;
        using ListenerType = ListenerT;
        using ProtocolType = ProtocolT;
        using SocketStream = BufferedSocketStream<TcpConnectionHandler>;
        using Base::Socket;
    private:
        using BufferQueue = Internal::BufferQueue;

        std::weak_ptr<ListenerType> listener_;
        TcpConnectionHandlerState state_;
        ProtocolType protocol_;
        std::unique_ptr<AcceptRequest> acceptRequest_;
        std::unique_ptr<ReceiveRequest> receiveRequest_;
        std::unique_ptr<SendRequest> sendRequest_;
        std::unique_ptr<DisconnectRequest> disconnectRequest_;
        SocketStream socketStream_;

        BufferPool<MaxReceiveBuffers> receivePool_;
        BufferPool<MaxSendBuffers> sendPool_;

        CriticalSection criticalSection_;
        WSABUF receiveBuf_ = {};
        Buffer* receiveBuffer_ = nullptr;

        BufferQueue writeQueue_;
        WSABUF sendBuf_ = {};
        Buffer* sendBuffer_ = nullptr;


    public:
        template<typename ... Args>
        TcpConnectionHandler( const std::shared_ptr<IO::Context>& context, const std::shared_ptr<ListenerType>& listener, Args&&... args )
            : Base( context ),
              listener_( listener ),
              state_( TcpConnectionHandlerState::Disconnected ),
              protocol_( std::forward<Args>( args )... ),
              acceptRequest_( std::make_unique<AcceptRequest>() ),
              receiveRequest_( std::make_unique<ReceiveRequest>() ),
              sendRequest_( std::make_unique<SendRequest>() ),
              disconnectRequest_( std::make_unique<DisconnectRequest>() ),
              socketStream_( *this )
        {
        }

        ~TcpConnectionHandler( )
        {
        }

        std::shared_ptr<ListenerType> Listener( )
        {
            return listener_.lock( );
        }
        std::shared_ptr<const ListenerType> Listener( ) const
        {
            return listener_.lock( );
        }


        void Stop( ) override
        {
            state_ = TcpConnectionHandlerState::Stopped;
            Base::Stop( );
        }

    private:
        Buffer* AcquireReceiveBuffer( )
        {
            return receivePool_.Acquire( );
        }
        void ReleaseReceiveBuffer( Buffer* buffer )
        {
            receivePool_.Release( buffer );
        }

        Buffer* AcquireSendBuffer( )
        {
            return sendPool_.Acquire( );
        }
        void ReleaseSendBuffer( Buffer* buffer )
        {
            sendPool_.Release( buffer );
        }


    private:
        AcceptRequest* GetAcceptRequest( const TcpSocket& server )
        {
            receiveBuffer_ = AcquireReceiveBuffer( );
            receiveBuffer_->PrepareForAccept( );

            constexpr size_t bufferDataOffset = BufferDataOffset( );
            Byte* buffer = reinterpret_cast<Byte*>( receiveBuffer_ ) + bufferDataOffset;

            auto result = acceptRequest_.get( );
            receiveBuf_ = { static_cast< ULONG >( receiveBuffer_->Size( ) ),reinterpret_cast< char* >( buffer ) };

            result->Reset( server, Socket( ), buffer, static_cast<UInt32>( receiveBuffer_->Size() ) );
            return result;
        }

        ReceiveRequest* GetReceiveRequest( )
        {
            receiveBuffer_ = AcquireReceiveBuffer( );
            receiveBuffer_->PrepareForReceive( );

            constexpr size_t bufferDataOffset = BufferDataOffset( );
            Byte* buffer = reinterpret_cast<Byte*>( receiveBuffer_ ) + bufferDataOffset;

            auto result = receiveRequest_.get( );
            receiveBuf_ = { static_cast< ULONG >( receiveBuffer_->Size( ) ),reinterpret_cast< char* >( buffer ) };
            result->Reset( Socket( ), &receiveBuf_, 1, MessageFlags::None );

            return result;
        }

        SendRequest* GetSendRequest( )
        {
            auto result = sendRequest_.get( );
            result->Reset( Socket( ) );

            return result;
        }


        DisconnectRequest* GetDisconnectRequest( )
        {
            auto result = disconnectRequest_.get( );
            result->Reset( Socket( ), false );

            return result;
        }

        void Accept( );
        void Destroy( );

        template<IO::StreamReader StreamReaderT, IO::StreamWriter StreamWriterT>
        bool ProcessData( IO::BinaryReader<StreamReaderT>& requestReader, IO::BinaryWriter<StreamWriterT>& replyWriter )
        {
            bool doNotDisconnect = true;
            while ( doNotDisconnect && socketStream_.HasInputData( ) && state_ < TcpConnectionHandlerState::Stopped )
            {
                try
                {
                    doNotDisconnect = protocol_.Process( requestReader, replyWriter );
                }
                catch ( Exception& exc )
                {
                    exc.Log( );
                    doNotDisconnect = false;
                }
            }
            return doNotDisconnect;
        }

    protected:
        bool HandleAcceptCompleted( AcceptRequest* request )
        {
            constexpr size_t bufferDataOffset = BufferDataOffset( );
            Byte* buffer = request->Buffer( );
            Buffer* acceptBuffer = reinterpret_cast<Buffer*>( buffer - bufferDataOffset );
            acceptBuffer->PrepareForRead( request->NumberOfBytesTransferred() );
            socketStream_.ResetReadBuffer( acceptBuffer );
            IO::BinaryReader requestReader( socketStream_ );
            IO::BinaryWriter replyWriter( socketStream_ );
            auto doNotDisconnect = ProcessData( requestReader, replyWriter );
            FlushWrite( doNotDisconnect );
            return true;
        }
    private:
        void Read( )
        {
            state_ = TcpConnectionHandlerState::Connected;
            auto newRequest = GetReceiveRequest( );
            Base::BeginAsyncReceive( newRequest );
        }
    protected:
        bool HandleReceiveCompleted( ReceiveRequest* request )
        {
            constexpr size_t bufferDataOffset = BufferDataOffset( );
            auto bufferCount = request->BufferCount( );
            auto buffers = request->Buffers( );
            size_t remainingNumberOfBytesToProcess = request->NumberOfBytesTransferred( );
            bool doNotDisconnect = true;
            UInt32 i = 0;
            while ( doNotDisconnect && i < bufferCount )
            {
                Byte* buffer = reinterpret_cast<Byte*>(buffers[i].buf);
                size_t bufferLength = buffers[ i ].len;
                size_t bytesToProcessInBuffer = std::min( remainingNumberOfBytesToProcess, bufferLength );

                Buffer* receiveBuffer = reinterpret_cast< Buffer* >( buffer - bufferDataOffset );
                receiveBuffer->PrepareForRead( bytesToProcessInBuffer );
                socketStream_.ResetReadBuffer( receiveBuffer );

                IO::BinaryReader requestReader( socketStream_ );
                IO::BinaryWriter replyWriter( socketStream_ );

                doNotDisconnect = ProcessData( requestReader, replyWriter );
                remainingNumberOfBytesToProcess -= bytesToProcessInBuffer;
                ++i;
            }
            FlushWrite( doNotDisconnect );
            return true;
        }
    private:
        void FlushWrite( bool constinueReading )
        {
            if ( constinueReading && state_ < TcpConnectionHandlerState::Stopped )
            {
                FlushWriteQueueBeforeRead( );
            }
            else
            {
                FlushWriteQueueBeforeDisconnect( );
            }
        }

        void FlushWriteQueueBeforeRead( )
        {
            state_ = TcpConnectionHandlerState::FlushingWriteQueue;
            FlushWrites( );
        }
        void FlushWriteQueueBeforeDisconnect( )
        {
            state_ = TcpConnectionHandlerState::FlushingWriteQueueBeforeDisconnect;
            FlushWrites( );
        }

        void FlushWrites( )
        {
            if ( socketStream_.writeBuffer_ )
            {
                if ( socketStream_.writeBuffer_->size( ) )
                {
                    std::unique_lock lock( criticalSection_ );
                    auto writeBuffer = socketStream_.writeBuffer_;
                    socketStream_.writeBuffer_ = nullptr;
                    EnqueueNoLock( writeBuffer );
                }
            }
        }
    private:
        void EnqueueNoLock( Buffer* writeBuffer )
        {
            if ( sendBuffer_ == nullptr )
            {
                // No buffer in flight, so it can be sendt immedeately
                SendBuffer( writeBuffer );
            }
            else
            {
                // There is a buffer in flight, so we enqueue for later processing
                writeQueue_.Enqueue( writeBuffer );
            }
        }
    public:
        void Enqueue( Buffer* writeBuffer )
        {
            std::unique_lock lock( criticalSection_ );
            EnqueueNoLock( writeBuffer );
        }

    private:
        void SendBuffer( Buffer* writeBuffer, size_t startOffset = 0 )
        {
#ifdef _DEBUG
            assert( writeBuffer != nullptr );
            assert( writeBuffer->size() > startOffset );
#endif
            auto request = GetSendRequest( );

            sendBuf_.len = static_cast< ULONG >( writeBuffer->size( ) - startOffset );
            sendBuf_.buf = reinterpret_cast<CHAR*>( writeBuffer->data( ) + startOffset );
            
            request->Reset( Socket( ), &sendBuf_, 1, MessageFlags::None );

            sendBuffer_ = writeBuffer;
            Base::BeginAsyncSend( request );
        }


        bool ProcessCompletedSendRequest( SendRequest* request )
        {
#ifdef _DEBUG
            assert( sendBuffer_ != nullptr );
            assert( sendBuffer_->Contains( reinterpret_cast<Byte*>( sendBuf_.buf ) ) );
#endif
            auto sendBuffer = sendBuffer_;
            sendBuffer_ = nullptr;
            auto numberOfBytesTransferred = request->NumberOfBytesTransferred( );
            if ( sendBuf_.len > numberOfBytesTransferred )
            {
                size_t originalSendBufferOffset = reinterpret_cast< Byte* >( sendBuf_.buf ) - sendBuffer->data( );
                SendBuffer( sendBuffer, originalSendBufferOffset + numberOfBytesTransferred );
                return false;
            }
            sendPool_.Release( sendBuffer );
            if ( writeQueue_.size( ) )
            {
                auto nextSendBuffer = writeQueue_.Dequeue( );
                SendBuffer( nextSendBuffer );
                return false;
            }
            return true;
        }

    protected:
        bool HandleSendCompleted( SendRequest* request )
        {
            std::unique_lock lock( criticalSection_ );

            auto doneSending = ProcessCompletedSendRequest( request );
            if ( doneSending )
            {
                // what is the next step?
                switch ( state_ )
                {
                    case TcpConnectionHandlerState::FlushingWriteQueue:
                    {
                        Read( );
                    }
                    break;
                    case TcpConnectionHandlerState::FlushingWriteQueueBeforeDisconnect:
                    {
                        Disconnect( );
                    }
                    break;
                }
            }
            return true;
        }


        void Disconnect( )
        {
            state_ = TcpConnectionHandlerState::Disconnecting;
            auto newRequest = GetDisconnectRequest( );
            Base::BeginAsyncDisconnect( newRequest );
        }

        bool HandleDisconnectCompleted( DisconnectRequest* request )
        {
            Destroy( );
            return true;
        }
    };

    template<typename DerivedT, typename ConnectionHandlerT>
    class TcpListener : public IO::Sockets::Server::TcpListenerBase<DerivedT>
    {
        template<typename DerivedT>
        friend class SocketHandler;

    public:
        using Base = IO::Sockets::Server::TcpListenerBase<DerivedT>;
        using DerivedType = DerivedT;
        using ConnectionHandlerType = ConnectionHandlerT;

        using Base::Socket;
    private:
        CriticalSection criticalSection_;
        std::atomic<bool> stopping_;
        Address address_;
        boost::container::flat_map<SOCKET, std::shared_ptr<ConnectionHandlerType>> connectionHandlers_;

        class ConnectionHandlerFactoryBase
        {
        public:
            ConnectionHandlerFactoryBase( )
            {
            }
            virtual ~ConnectionHandlerFactoryBase( )
            {
            }
            virtual std::shared_ptr<ConnectionHandlerType> Create( ) = 0;
        };


        template <typename... Args>
        class ConnectionHandlerFactory : public ConnectionHandlerFactoryBase
        {
        public:
            using Base = ConnectionHandlerFactoryBase;
            using TupleType = std::tuple<Args...>;
        private:
            std::weak_ptr<IO::Context> context_;
            DerivedType* listener_;
            TupleType tuple_;
        public:
            ConnectionHandlerFactory( const std::shared_ptr<IO::Context>& context, DerivedType* listener, Args&&... args )
                : Base( ),
                context_( context ),
                listener_( listener ),
                tuple_( std::forward<Args>( args )... )
            {
            }
        private:
            template<std::size_t... I>
            constexpr std::shared_ptr<ConnectionHandlerType> CreateImpl( std::index_sequence<I...> )
            {
                auto context = context_.lock( );
                if ( context )
                {
                    auto listener = listener_->Self( );
                    return std::make_shared<ConnectionHandlerType>( context, listener, std::get<I>( tuple_ )... );
                }
                else
                {
                    return nullptr;
                }
            }
        public:
            virtual std::shared_ptr<ConnectionHandlerType> Create( ) override
            {
                return CreateImpl( std::make_index_sequence < std::tuple_size_v<TupleType>>{} );
            }
        };
        std::unique_ptr<ConnectionHandlerFactoryBase> factory_;
        size_t initialConnectionHandlerCount_;
    public:
        template <typename... Args>
        TcpListener( const std::shared_ptr<IO::Context>& context,
                     const Address& listenAddress,
                     size_t initialConnectionHandlerCount, Args&&... args )
            : Base( context ),
              address_( listenAddress ), stopping_( false ), initialConnectionHandlerCount_( initialConnectionHandlerCount )
        {
            auto* self = static_cast<DerivedType*>( this );
            factory_ = std::make_unique<ConnectionHandlerFactory<Args...> >( context, self, std::forward<Args>( args )... );
        }
        
        bool IsRunning( ) const noexcept
        {
            return stopping_.load( ) != false;
        }


        void Start( ) override
        {
            //printf( "Starting listener\n" );
            Base::Socket( ).Bind( address_ );
            Base::Socket( ).Listen( );

            for ( size_t i = 0; i < initialConnectionHandlerCount_; ++i )
            {
                auto handler = factory_->Create( );
                connectionHandlers_.emplace( handler->SocketHandle( ), handler );
                Accept( handler );
            }
        }

        void Accept( const std::shared_ptr<ConnectionHandlerType>& connectionHandler )
        {
            //printf( "In TcpListener Accept: Handle=0x%08llx \n", connectionHandler->Client( ).Handle( ) );
            auto* request = connectionHandler->GetAcceptRequest( Base::Socket( ) );
            Base::BeginAsyncAccept( request );
        }

        bool RemoveHandler( const std::shared_ptr<ConnectionHandlerType>& connectionHandler )
        {
            std::unique_lock lock( criticalSection_ );
            auto connectionSocketHandle = connectionHandler->SocketHandle( );
            auto numberOfElementsErased = connectionHandlers_.erase( connectionSocketHandle );
            return numberOfElementsErased == 1;
        }

        bool AddNewHandler( )
        {
            if ( IsRunning( ) )
            {
                std::unique_lock lock( criticalSection_ );
                auto handler = factory_->Create( );
                connectionHandlers_.emplace( handler->SocketHandle( ), handler );

                Accept( handler );
                return true;
            }
            else
            {
                return false;
            }
        }

        void Stop( ) override
        {
            //printf( "In TcpListener Stop \n" );
            std::unique_lock lock( criticalSection_ );
            stopping_ = true;
            for ( auto& entry : connectionHandlers_ )
            {
                entry.second->Close( );
            }
            Base::Close( );
        }

    protected:
        bool HandleAcceptCompleted( AcceptRequest* request )
        {

#ifdef _DEBUG
            printf( "In TcpListener HandleAccept: IoResult=%u, transferred = %llu\n", request->IoResult( ), request->NumberOfBytesTransferred( ) );
#endif
            WinError ioResult = request->IoResult( );
            if ( ioResult != WinError::OperationAborted &&
                ioResult != WinError::StatusCancelled &&
                ioResult != WinError::StatusLocalDisconnect &&
                ioResult != WinError::StatusRemoteDisconnect &&
                ioResult != WinError::WsaNotSocket )
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

    template<typename DerivedT, typename ListenerT, typename ProtocolT >
    inline void TcpConnectionHandler<DerivedT, ListenerT, ProtocolT>::Accept( )
    {
        auto self = Base::Self( );
        state_ = TcpConnectionHandlerState::Disconnected;
        auto listener = Listener( );
        listener->Accept( self );
    }

    template<typename DerivedT, typename ListenerT, typename ProtocolT >
    inline void TcpConnectionHandler<DerivedT, ListenerT, ProtocolT>::Destroy( )
    {
        auto self = Base::Self( );
        auto listener = Listener( );
        if ( listener->RemoveHandler( self ) == false )
        {
            printf( "Unable to remove connection handler\n" );
        }
        self.reset( );
        if ( listener->AddNewHandler( ) == false )
        {
            if ( listener->IsRunning( ) )
            {
                printf( "Unable to add new connection handler\n" );
            }
        }
    }


    template <typename ProtocolT>
    class TcpSimpleListener;

    template<typename ListenerT, typename ProtocolT>
    class TcpSimpleConnectionHandler : public TcpConnectionHandler<TcpSimpleConnectionHandler<ListenerT, ProtocolT>, ListenerT, ProtocolT>
    {
    public:
        using Base = TcpConnectionHandler<TcpSimpleConnectionHandler<ListenerT, ProtocolT>, ListenerT, ProtocolT>;

        template<typename ...Args>
        TcpSimpleConnectionHandler( const std::shared_ptr<IO::Context>& context, const std::shared_ptr<ListenerT>& listener, Args&&... args )
            : Base( context, listener, std::forward<Args>( args )... )
        {
        }
    };


    template <typename ProtocolT>
    class TcpSimpleListener : public TcpListener<TcpSimpleListener<ProtocolT>, TcpSimpleConnectionHandler<TcpSimpleListener<ProtocolT>, ProtocolT> >
    {
    public:
        using Base = TcpListener<TcpSimpleListener<ProtocolT>, TcpSimpleConnectionHandler<TcpSimpleListener<ProtocolT>, ProtocolT> >;

        template<typename ...Args>
        TcpSimpleListener( const std::shared_ptr<IO::Context>& context, const Address& listenAddress, size_t clientSocketCount, Args&&... args )
            : Base( context, listenAddress, clientSocketCount, std::forward<Args>( args )... )
        {
        }
    };
}


#endif
