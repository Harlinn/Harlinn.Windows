#pragma once
#ifndef HCCZMQ_h_
#define HCCZMQ_h_


#include <zmq.hpp>
#include "HCCIOBase.h"
#include "HCCMemory.h"

namespace Harlinn::Common::Core::ZeroMq
{
    using SocketType = zmq::socket_type;
    using SendFlags = zmq::send_flags;
    using PollItem = zmq::pollitem_t;

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
        ZeroMq::Context& context_;
    public:

        inline Socket( ZeroMq::Context& context, SocketType socketType );

        Socket( const Socket& other ) = delete;
        Socket( Socket&& other ) = default;

        Socket& operator = ( const Socket& other ) = delete;
        Socket& operator = ( Socket&& other ) = default;


        ZeroMq::Context& Context( ) noexcept
        {
            return context_;
        }

        inline ZeroMq::MemoryManager* MemoryManager( );

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

        ZeroMq::MemoryManager* MemoryManager( )
        {
            return &memoryManager_;
        }

    };

    inline Socket::Socket( ZeroMq::Context& context, SocketType socketType )
        : Base( context, socketType ), context_( context )
    {
    }

    inline ZeroMq::MemoryManager* Socket::MemoryManager( )
    {
        return context_.MemoryManager( );
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
    public:
        using Base = ZMQStreamBase;

        ZMQWriteStream( ZeroMq::Socket& socket )
            : Base( socket )
        {
            buffer_ = AllocateBuffer( );
        }
        ~ZMQWriteStream( )
        {
            Flush( );
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
            if ( bufferPosition_ )
            {
                auto& socket = Socket( );
                auto* memoryManager = socket.MemoryManager( );
                Message message( buffer_, bufferPosition_, []( void* data, void* hint ) {if ( data && hint ) { reinterpret_cast< ZeroMq::MemoryManager* >( hint )->Free( data ); }}, memoryManager );
                socket.send( std::move( message ), last ? SendFlags::none : SendFlags::sndmore );
                bufferPosition_ = 0;
                buffer_ = AllocateBuffer( );
            }
            else if( last )
            {
                auto& socket = Socket( );
                Message message;
                socket.send( std::move( message ), SendFlags::none );
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
            if ( socket.connected( ) )
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


}


#endif
