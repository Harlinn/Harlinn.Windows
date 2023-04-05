#include <HCCSocket.h>
using namespace Harlinn::Common::Core;

IO::Sockets::TcpSocket listener;

BOOL __stdcall ConsoleCtrlHandler( DWORD ctrlType )
{
    switch ( ctrlType )
    {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_CLOSE_EVENT:
        {
            if ( listener )
            {
                listener.Close( );
            }
            return TRUE;
        }
        break;
    }
    return FALSE;
}
int main()
{
    CurrentThread::SetDescription( L"Server main thread." );
    try
    {
        constexpr UInt16 PortNumber = 42000;
        IO::Sockets::WSAInitTerm wsaInitTerm;

        IO::Sockets::Address listenAddress( PortNumber );

        listener = IO::Sockets::TcpSocket( IO::Sockets::AddressFamily::InterNetworkV6 );

        SetConsoleCtrlHandler( ConsoleCtrlHandler, TRUE );

        listener.Bind( listenAddress );
        listener.Listen( );
        std::cout << "Server started, press Ctrl+C to exit." << std::endl;
        while ( listener )
        {
            auto connection = listener.Accept( );
            if ( connection )
            {
                Byte buffer[1024];
                while ( true )
                {
                    size_t received = static_cast<size_t>( connection.Receive( buffer, sizeof( buffer ), IO::Sockets::MessageFlags::None ) );
                    if ( received == 0 )
                    {
                        std::cout << "Shutting down connection to client." << std::endl;
                        connection.SetLinger( true, 0 );
                        connection.Shutdown( IO::Sockets::ShutdownFlag::Both );
                        break;
                    }
                    else
                    {
                        std::cout << "Echoing received data back to client." << std::endl;
                        size_t totalBytesSendt = 0;
                        while ( totalBytesSendt < received )
                        {
                            size_t bytesToSend = received - totalBytesSendt;
                            size_t bytesSendt = static_cast<size_t>(connection.Send( &buffer[totalBytesSendt], bytesToSend, IO::Sockets::MessageFlags::None ));
                            totalBytesSendt += bytesSendt;
                        }
                    }
                }
            }
        }
        SetConsoleCtrlHandler( ConsoleCtrlHandler, FALSE );
        std::cout << "Server is exiting." << std::endl;
    }
    catch ( Exception& exception )
    {
        ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
    }
    catch ( std::exception& exc )
    {
        ReportException( exc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
    }
    catch ( ... )
    {
        ReportUnknownException( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
    }

}
