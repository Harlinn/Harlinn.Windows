#include "pch.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::IO::Sockets;
namespace
{
    class LocalFixture
    {
        IO::Sockets::WSAInitTerm wsa_;
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    class SocketServer
    {
        std::atomic<bool> stopped_;
        std::atomic<size_t> clientConnects_;
        Thread thread_;
        Blocks::Stream received_;
        IO::Sockets::TcpSocket listenSocket_;
        EventWaitHandle startEvent_;
        EventWaitHandle clientEvent_;
        const char* testName_;
    public:
        static constexpr UInt16 PortNumber = 42000;


        SocketServer(const char* testName )
            : startEvent_(true), testName_( testName ), clientEvent_(true)
        {

        }

        void Start( )
        {
            stopped_ = false;
            thread_ = Thread( []( SocketServer* server ) 
            {
                try
                {
                    server->Run( );
                }
                catch ( std::exception& exc )
                {
                    if ( server->Stopped( ) == false )
                    {
                        auto what = exc.what( );
                        printf( "Exception in SocketServer::Run( ): %s\n", what );
                    }
                }
                catch ( ... )
                {
                    if ( server->Stopped( ) == false )
                    {
                        printf( "Unknown exception in SocketServer::Run( )\n" );
                    }
                }
            }, this );
            startEvent_.Wait( );
        }

        void Stop( )
        {
            stopped_ = true;
            listenSocket_.Close( );
        }

        bool Stopped( )
        {
            return stopped_.load( );
        }

        void Run( )
        {
            IO::Sockets::Address address( 42000 );
            listenSocket_ = IO::Sockets::TcpSocket( IO::Sockets::AddressFamily::InterNetworkV6 );

            listenSocket_.Bind( address );
            listenSocket_.SetConditionalAccept( true );
            listenSocket_.Listen( );
            startEvent_.Signal( );

            while ( Stopped( ) == false )
            {
                auto clientSocket = listenSocket_.Accept( );
                if ( clientSocket )
                {
                    ++clientConnects_;
                    clientSocket.SetReceiveTimeout( 500 );
                    this->Process( clientSocket );
                    clientEvent_.Signal( );
                    clientSocket.Close( );
                }
            }
            listenSocket_.Close( );
        }

        virtual void Process( IO::Sockets::Socket& clientSocket )
        {
            std::array<Byte, 8176> buffer;
            for ( ;;)
            {
                auto count = clientSocket.Receive( buffer.data( ), buffer.size( ),MessageFlags::None );
                if ( count )
                {
                    received_.Write( buffer.data( ), static_cast<size_t>( count ) );
                    auto bytesToSend = count;
                    Int64 offset = 0;
                    while ( offset < bytesToSend )
                    {
                        Byte* data = buffer.data( ) + offset;
                        size_t length = bytesToSend - offset;
                        auto written = clientSocket.Send( data, static_cast<size_t>( length ), IO::Sockets::MessageFlags::None );
                        offset += written;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        bool Wait( )
        {
            return thread_.Wait( );
        }

        bool WaitForRequest( )
        {
            return clientEvent_.Wait( );
        }

        size_t ClientConnects( ) const
        {
            return clientConnects_.load( );
        }

        Blocks::Stream& Received( )
        {
            return received_;
        }

    };
}

BOOST_FIXTURE_TEST_SUITE( SocketTests, LocalFixture )

// --run_test=SocketTests/ShutdownTest1
BOOST_AUTO_TEST_CASE( ShutdownTest1 )
{
    TcpSocket tcpSocket( AddressFamily::InterNetworkV6 );
    WinError error = WinError::None;
    try
    {
        tcpSocket.Shutdown( ShutdownFlag::Receive );
    }
    catch ( IO::Sockets::SocketException& exc )
    {
        error = static_cast<WinError>( exc.GetCode( ) );
    }
    BOOST_CHECK( error == WinError::None || error == WinError::WsaNotConnected );
}


// --run_test=SocketTests/StartAndStopTest1
BOOST_AUTO_TEST_CASE( StartAndStopTest1 )
{
    SocketServer server("StartAndStopTest1");
    server.Start( );
    server.Stop( );
    auto serverSuccess = server.Wait( );
    BOOST_CHECK( serverSuccess );
}

// --run_test=SocketTests/ClientConnectTest1
BOOST_AUTO_TEST_CASE( ClientConnectTest1 )
{
    SocketServer server( "ClientConnectTest1" );
    server.Start( );

    TcpSocket clientSocket( AddressFamily::InterNetworkV6 );
    Address address( 42000 );
    clientSocket.Connect( address );
    clientSocket.Close( );

    server.Stop( );
    auto serverSuccess = server.Wait( );
    BOOST_CHECK( serverSuccess );
    auto clientConnects = server.ClientConnects( );
    BOOST_CHECK( clientConnects == 1 );
}


// --run_test=SocketTests/ClientWriteTest1
BOOST_AUTO_TEST_CASE( ClientWriteTest1 )
{
    std::array<Byte, 3> dataToWrite{1,2,3};
    std::array<Byte, 3> dataReceived{ 0,0,0 };
    SocketServer server( "ClientWriteTest1" );
    server.Start( );

    TcpSocket clientSocket( AddressFamily::InterNetworkV6 );
    Address address( 42000 );
    clientSocket.Connect( address );
    clientSocket.Send( dataToWrite.data(), dataToWrite.size(), IO::Sockets::MessageFlags::None );
    server.WaitForRequest( );
    clientSocket.Close( );

    server.Stop( );
    auto serverSuccess = server.Wait( );
    BOOST_CHECK( serverSuccess );
    auto clientConnects = server.ClientConnects( );
    BOOST_CHECK( clientConnects == 1 );

    auto& received = server.Received( );
    received.SetPosition( 0 );
    auto receivedSize = received.size( );
    BOOST_CHECK( dataToWrite.size( ) == receivedSize );
    received.Read( dataReceived.data(), dataReceived.size() );
    bool equal = dataReceived == dataToWrite;
    BOOST_CHECK( equal );
}

// --run_test=SocketTests/ClientReadTest1
BOOST_AUTO_TEST_CASE( ClientReadTest1 )
{
    std::array<Byte, 3> dataToWrite{ 1,2,3 };
    std::array<Byte, 3> dataReceived{ 0,0,0 };
    SocketServer server( "ClientWriteTest1" );
    server.Start( );

    //Address address( L"127.0.0.1", 42000 );
    Address address( L"localhost", 42000 );
    //Address address( AddressFamily::InterNetwork, L"127.0.0.1:42000" );
    TcpSocket clientSocket( address.Family() );
    
    clientSocket.Connect( address, nullptr, nullptr, nullptr );
    clientSocket.Send( dataToWrite.data( ), dataToWrite.size( ), MessageFlags::None );
    clientSocket.Receive( dataReceived.data(), dataReceived.size() );
    bool equal = dataReceived == dataToWrite;
    BOOST_CHECK( equal );
    server.WaitForRequest( );
    clientSocket.Close( );

    server.Stop( );
    auto serverSuccess = server.Wait( );
    BOOST_CHECK( serverSuccess );
    auto clientConnects = server.ClientConnects( );
    BOOST_CHECK( clientConnects == 1 );
}

// --run_test=SocketTests/DebugTest1
BOOST_AUTO_TEST_CASE( DebugTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto debug = socket.Debug( );
    BOOST_CHECK( debug == false );
    socket.SetDebug( true );
    debug = socket.Debug( );
    BOOST_CHECK( debug );
    socket.SetDebug( false );
    debug = socket.Debug( );
    BOOST_CHECK( debug == false );

    socket.Close( );
}

// --run_test=SocketTests/ConditionalAcceptTest1
BOOST_AUTO_TEST_CASE( ConditionalAcceptTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto conditionalAccept = socket.ConditionalAccept( );
    BOOST_CHECK( conditionalAccept == false );
    socket.SetConditionalAccept( true );
    conditionalAccept = socket.ConditionalAccept( );
    BOOST_CHECK( conditionalAccept );
    socket.SetConditionalAccept( false );
    conditionalAccept = socket.ConditionalAccept( );
    BOOST_CHECK( conditionalAccept == false );
    socket.Close( );
}

// --run_test=SocketTests/DontLingerTest1
BOOST_AUTO_TEST_CASE( DontLingerTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto dontLinger = socket.DontLinger( );
    BOOST_CHECK( dontLinger == true );
    socket.SetDontLinger( false );
    dontLinger = socket.DontLinger( );
    BOOST_CHECK( dontLinger == false );
    socket.SetDontLinger( true );
    dontLinger = socket.DontLinger( );
    BOOST_CHECK( dontLinger == true );
    socket.Close( );
}
// --run_test=SocketTests/LingerTest1
BOOST_AUTO_TEST_CASE( LingerTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto linger = socket.Linger( );
    BOOST_CHECK( linger == false );
    socket.SetLinger( true, 5 );
    linger = socket.Linger( );
    BOOST_CHECK( linger == true );
    BOOST_CHECK( linger.Seconds() == 5 );
    socket.SetLinger( false, 0 );
    linger = socket.Linger( );
    BOOST_CHECK( linger == false );
    socket.Close( );
}
// --run_test=SocketTests/ErrorCodeTest1
BOOST_AUTO_TEST_CASE( ErrorCodeTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto errorCode = socket.ErrorCode( );
    BOOST_CHECK( errorCode == 0 );
    socket.Close( );
}

// --run_test=SocketTests/ReceiveTimeoutTest1
BOOST_AUTO_TEST_CASE( ReceiveTimeoutTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto receiveTimeout = socket.ReceiveTimeout( );
    auto original = receiveTimeout;
    BOOST_CHECK( receiveTimeout == 0 );
    socket.SetReceiveTimeout( 500 );
    receiveTimeout = socket.ReceiveTimeout( );
    BOOST_CHECK( receiveTimeout == 500 );
    socket.SetReceiveTimeout( original );
    receiveTimeout = socket.ReceiveTimeout( );
    BOOST_CHECK( receiveTimeout == original );
    socket.Close( );
}

// --run_test=SocketTests/SendTimeoutTest1
BOOST_AUTO_TEST_CASE( SendTimeoutTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto sendTimeout = socket.SendTimeout( );
    auto original = sendTimeout;
    BOOST_CHECK( sendTimeout == 0 );
    socket.SetSendTimeout( 500 );
    sendTimeout = socket.SendTimeout( );
    BOOST_CHECK( sendTimeout == 500 );
    socket.SetSendTimeout( original );
    sendTimeout = socket.SendTimeout( );
    BOOST_CHECK( sendTimeout == original );
    socket.Close( );
}

// --run_test=SocketTests/KeepAliveTest1
BOOST_AUTO_TEST_CASE( KeepAliveTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto keepAlive = socket.KeepAlive( );
    BOOST_CHECK( keepAlive == false );
    socket.SetKeepAlive( true );
    keepAlive = socket.KeepAlive( );
    BOOST_CHECK( keepAlive );
    socket.SetKeepAlive( false );
    keepAlive = socket.KeepAlive( );
    BOOST_CHECK( keepAlive == false );

    socket.Close( );
}

// --run_test=SocketTests/SendBufferSizeTest1
BOOST_AUTO_TEST_CASE( SendBufferSizeTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto sendBufferSize = socket.SendBufferSize( );
    auto original = sendBufferSize;
    BOOST_CHECK( sendBufferSize > (50*1024) /*== 65536*/ );
    socket.SetSendBufferSize( 128*1024 );
    sendBufferSize = socket.SendBufferSize( );
    BOOST_CHECK( sendBufferSize == 128 * 1024 );
    socket.SetSendBufferSize( original );
    sendBufferSize = socket.SendBufferSize( );
    BOOST_CHECK( sendBufferSize == original );
    socket.Close( );
}

// --run_test=SocketTests/ReceiveBufferSizeTest1
BOOST_AUTO_TEST_CASE( ReceiveBufferSizeTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto receiveBufferSize = socket.ReceiveBufferSize( );
    auto original = receiveBufferSize;
    BOOST_CHECK( receiveBufferSize == 65536 );
    socket.SetReceiveBufferSize( 128 * 1024 );
    receiveBufferSize = socket.ReceiveBufferSize( );
    BOOST_CHECK( receiveBufferSize == 128 * 1024 );
    socket.SetReceiveBufferSize( original );
    receiveBufferSize = socket.ReceiveBufferSize( );
    BOOST_CHECK( receiveBufferSize == original );
    socket.Close( );
}

// --run_test=SocketTests/NoDelayTest1
BOOST_AUTO_TEST_CASE( NoDelayTest1 )
{
    TcpSocket socket( AddressFamily::InterNetworkV6 );
    auto value = socket.NoDelay( );
    BOOST_CHECK( value == false );
    socket.SetNoDelay( true );
    value = socket.NoDelay( );
    BOOST_CHECK( value == true );
    socket.SetNoDelay( false );
    value = socket.NoDelay( );
    BOOST_CHECK( value == false );
    socket.Close( );
}




// --run_test=SocketTests/AsyncClientWriteTest1
BOOST_AUTO_TEST_CASE( AsyncClientWriteTest1 )
{
    std::array<Byte, 3> dataToWrite{ 1,2,3 };
    std::array<Byte, 3> dataReceived{ 0,0,0 };
    SocketServer server( "AsyncClientWriteTest1" );
    server.Start( );

    IO::IOCompletionPort ioCompletionPort( 2 );

    TcpSocket clientSocket( AddressFamily::InterNetworkV6 );
    ioCompletionPort.Bind( clientSocket );
    Address address( 42000 );
    clientSocket.Connect( address );
    IO::Request request;
    auto* requestPtr = &request;
    EventWaitHandle event( true );
    std::atomic<bool> processedByIoCompletionPort;
    Thread ioCompletionPortThread( [&ioCompletionPort, requestPtr,&event,&processedByIoCompletionPort]( )
    {
        auto message = ioCompletionPort.Dequeue( 2000 );
        if ( message.Overlapped() == requestPtr )
        {
            processedByIoCompletionPort = true;
        }
        event.Signal( );
    } );
    WSABUF wsaBuf{};
    wsaBuf.buf = reinterpret_cast<CHAR*>( dataToWrite.data( ) );
    wsaBuf.len = static_cast<ULONG>(dataToWrite.size( ));
    DWORD bytesWritten = 0;
    auto result = clientSocket.Send( &wsaBuf, 1, requestPtr );
    //BOOST_CHECK( result == WinError::IoPending );

    event.Wait( );
    BOOST_CHECK( processedByIoCompletionPort.load( ) );

    server.WaitForRequest( );
    clientSocket.Close( );

    server.Stop( );
    auto serverSuccess = server.Wait( );
    BOOST_CHECK( serverSuccess );
    auto clientConnects = server.ClientConnects( );
    BOOST_CHECK( clientConnects == 1 );

    auto& received = server.Received( );
    received.SetPosition( 0 );
    auto receivedSize = received.size( );
    BOOST_CHECK( dataToWrite.size( ) == receivedSize );
    received.Read( dataReceived.data( ), dataReceived.size( ) );
    bool equal = dataReceived == dataToWrite;
    BOOST_CHECK( equal );
}





BOOST_AUTO_TEST_SUITE_END( )