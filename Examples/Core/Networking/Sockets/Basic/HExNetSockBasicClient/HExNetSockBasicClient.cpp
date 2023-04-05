#include <HCCSocket.h>
using namespace Harlinn::Common::Core;


bool isRunning = false;
BOOL __stdcall ConsoleCtrlHandler( DWORD ctrlType )
{
    switch ( ctrlType )
    {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_CLOSE_EVENT:
        {
            isRunning = false;
            return TRUE;
        }
        break;
    }
    return FALSE;
}


int main()
{
    CurrentThread::SetDescription( L"Client main thread." );
    try
    {
        constexpr UInt16 PortNumber = 42000;
        IO::Sockets::WSAInitTerm wsaInitTerm;

        IO::Sockets::Address serverAddress( PortNumber );
        IO::Sockets::TcpSocket client( IO::Sockets::AddressFamily::InterNetworkV6 );
        isRunning = true;
        client.Connect( serverAddress );

        SetConsoleCtrlHandler( ConsoleCtrlHandler, TRUE );

        while ( isRunning )
        {
            std::string input;
            std::getline( std::cin, input );
            if ( isRunning )
            {
                std::cout << "Sending '" << input << "' to server." << std::endl;
                size_t bytesToSend = input.length( );
                size_t totalBytesSendt = 0;
                const char* dataToSend = input.c_str( );
                while ( isRunning && totalBytesSendt < bytesToSend )
                {
                    size_t remainingBytesToSend = bytesToSend - totalBytesSendt;
                    size_t bytesSendt = client.Send( &dataToSend[totalBytesSendt], remainingBytesToSend, IO::Sockets::MessageFlags::None );
                    totalBytesSendt += bytesSendt;
                }
                if ( isRunning )
                {
                    std::cout << "Receiving data from server." << std::endl;
                    std::string serverData( bytesToSend, '\x0' );
                    size_t bytesToReceive = bytesToSend;
                    size_t totalBytesReceived = 0;
                    char* dataToReceive = serverData.data( );
                    while ( isRunning && totalBytesReceived < bytesToReceive )
                    {
                        size_t remainingBytesToReceive = bytesToReceive - totalBytesReceived;
                        size_t bytesReceived = client.Receive( &dataToReceive[totalBytesReceived], remainingBytesToReceive, IO::Sockets::MessageFlags::None );
                        totalBytesReceived += bytesReceived;
                    }
                    std::cout << "Received '" << serverData << "' from server." << std::endl;
                }
            }
        }
        std::cout << "Closing connection to server." << std::endl;
        client.Shutdown( IO::Sockets::ShutdownFlag::Both );

        SetConsoleCtrlHandler( ConsoleCtrlHandler, FALSE );
        std::cout << "Client is exiting." << std::endl;

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
