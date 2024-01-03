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

#include "pch.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::IO::Sockets;

namespace
{
    constexpr UInt16 PortNumber = 42000;
    constexpr UInt32 ContextThreadCount = 24;

    class LocalFixture
    {
        IO::Sockets::WSAInitTerm wsa_;
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };



    enum class OperationType
    {

    };

    class Operation
    {

    };



    class Conversation
    {
        int id_;
    public:
        Conversation( int id )
            : id_(id)
        { }


    };



    namespace TcpTestServer
    {
        class ConnectionHandler;

        struct Buffer : public WSABUF
        {
            using Base = WSABUF;
            Buffer( )
                : Base{}
            { }

            Buffer( const Byte* buffer, size_t bufferSize )
                : Base{}
            {
                if ( buffer && bufferSize )
                {
                    buf = (char*)malloc( bufferSize );
                    if ( buf )
                    {
                        len = static_cast<ULONG>( bufferSize );
                        memcpy( buf, buffer, bufferSize );
                    }
                    else
                    {
                        throw std::bad_alloc( );
                    }
                }
            }

            Buffer( const Byte* buffer, size_t bufferSize, size_t extraSpace )
                : Base{}
            {
                if ( buffer && bufferSize )
                {
                    buf = (char*)malloc( bufferSize + extraSpace );
                    if ( buf )
                    {
                        len = static_cast<ULONG>( bufferSize );
                        memcpy( buf, buffer, bufferSize );
                        memset( buf + bufferSize, 0, extraSpace );
                    }
                    else
                    {
                        throw std::bad_alloc( );
                    }
                }
            }


            explicit Buffer( size_t bufferSize )
                : Base{}
            {
                if ( bufferSize )
                {
                    buf = (char*)malloc( bufferSize );
                    if ( buf )
                    {
                        len = static_cast<ULONG>( bufferSize );
                        memset( buf, 0, bufferSize );
                    }
                    else
                    {
                        throw std::bad_alloc( );
                    }
                }
            }
            explicit Buffer( size_t bufferSize, size_t extraSpace )
                : Base{}
            {
                if ( bufferSize )
                {
                    buf = (char*)malloc( bufferSize + extraSpace );
                    if ( buf )
                    {
                        len = static_cast<ULONG>( bufferSize );
                        memset( buf, 0, bufferSize + extraSpace );
                    }
                    else
                    {
                        throw std::bad_alloc( );
                    }
                }
            }


            ~Buffer( )
            {
                if ( buf )
                {
                    free( buf );
                }
            }

            Byte* data( )
            {
                return std::bit_cast<Byte*>( buf );
            }
            const Byte* data( ) const
            {
                return std::bit_cast<const Byte*>( buf );
            }
        };

        class Listener;
        class ConnectionHandler : public Tcp::Server::ConnectionHandler<ConnectionHandler, TcpTestServer::Listener>
        {
        public:
            using Base = Tcp::Server::ConnectionHandler<ConnectionHandler, TcpTestServer::Listener>;
            using SocketType = Tcp::Server::TcpSocket;
        private:
            Buffer acceptRequestBuffer_{ 1024, IO::Sockets::AcceptRequest::CalculateBufferSizeFor( 0 ) };
            static constexpr size_t MaxReadSize = 1024;
            Buffer readBuffer_{ MaxReadSize };
            static constexpr size_t MaxSendSize = 1024;
            Buffer writeBuffer_{ MaxSendSize };
        public:
            ConnectionHandler( const std::shared_ptr<TcpTestServer::Listener>& listener, AddressFamily addressFamily )
                : Base( listener, addressFamily )
            {
                wprintf( L"%s\r\n", CURRENT_FUNCTION );
            }
            virtual ~ConnectionHandler()
            {
                wprintf( L"%s\r\n", CURRENT_FUNCTION );
            }

        };

        class Listener : public Tcp::Server::ListenerHandler<Listener, ConnectionHandler>
        {
            std::atomic<size_t> connectionCount_ = 0;
        public:
            using Base = Tcp::Server::ListenerHandler<Listener, ConnectionHandler>;

            Listener( const std::shared_ptr<IO::Context>& context, const IO::Sockets::Address& listenAddress )
                : Base( context, listenAddress, 2, AddressFamily::InterNetworkV6 )
            { }

            ~Listener( )
            {
                wprintf( L"%s\r\n", CURRENT_FUNCTION );
            }


            bool HandleAcceptCompleted( AcceptRequest* request )
            {
                wprintf( L"%s\r\n", CURRENT_FUNCTION );
                Base::HandleAcceptCompleted( request );
                connectionCount_++;
                return false;
            }

            size_t ConnectionCount( ) const
            {
                return connectionCount_.load( );
            }


        };

        

        class Server
        {
            std::shared_ptr<IO::Context> context_;
            IO::Sockets::Address address{ PortNumber };
            std::shared_ptr<Listener> listener_;
        public:
            Server()
                : context_( std::make_shared<IO::Context>( ContextThreadCount ) ),
                  listener_( std::make_shared<Listener>( context_, address ) )
            {
                context_->Add( listener_ );
            }

            void Start( )
            {
                wprintf( L"%s\r\n", CURRENT_FUNCTION );
                context_->Start( );
            }
            void Stop( )
            {
                wprintf( L"%s\r\n", CURRENT_FUNCTION );
                context_->Stop( );
            }

            size_t ConnectionCount( ) const
            {
                return listener_->ConnectionCount( );
            }

        };

    }


    namespace TcpTestClient
    {
        class Client
        {
            IO::Sockets::Address address_{ PortNumber };
            IO::Sockets::TcpSocket connection_;
        public:
            Client( )
            { }

            void Connect( )
            {
                wprintf( L"%s\r\n", CURRENT_FUNCTION );
                connection_.Open( AddressFamily::InterNetworkV6 );
                connection_.Connect( address_ );
            }

            void Close( )
            {
                wprintf( L"%s\r\n", CURRENT_FUNCTION );
                connection_.Close( );
            }

        };
    }




}

BOOST_FIXTURE_TEST_SUITE( SocketTests2, LocalFixture )

// --run_test=SocketTests2/ServerStartAndStopTest1
BOOST_AUTO_TEST_CASE( ServerStartAndStopTest1 )
{
    TcpTestServer::Server server;
    server.Start( );
    server.Stop( );
}

// --run_test=SocketTests2/ClientConnectTest1
BOOST_AUTO_TEST_CASE( ClientConnectTest1 )
{
    size_t ConnectionCount = 100;
    TcpTestServer::Server server;
    TcpTestClient::Client client;
    server.Start( );
    for ( size_t i = 0; i < ConnectionCount; i++ )
    {
        client.Connect( );
        client.Close( );
    }
    server.Stop( );
    auto connectionCount = server.ConnectionCount( );
    BOOST_CHECK( connectionCount == ConnectionCount );

}




BOOST_AUTO_TEST_SUITE_END( )