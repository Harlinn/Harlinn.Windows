#include "pch.h"
#include <HCCSocket.h>
#include <ws2tcpip.h>
#include <HCCSync.h>
#include <HCCLogging.h>

namespace Harlinn::Common::Core::IO
{
    void IOCompletionPort::Bind( const Sockets::Socket& socket, void* data ) const
    {
        Bind( (HANDLE)socket.Handle(), data );
    }
}
namespace Harlinn::Common::Core::IO::Sockets
{
    namespace
    {
        void _ThrowSocketError( WinError error )
        {
            if ( error != WinError::None )
            {
                auto errorMessage = FormatError( static_cast<DWORD>( error ) );
                SocketException exception( static_cast<Int64>( error ), errorMessage );
                throw exception;
            }
        }

        void _ThrowSocketError( WinError error, const wchar_t* function, const wchar_t* filename, int lineNumber )
        {
            if ( error != WinError::None )
            {
                auto errorMessage = FormatError( static_cast<DWORD>( error ) );
                ExceptionLocation location( function, filename, lineNumber );
                SocketException exception( location, static_cast<Int64>( error ), errorMessage );
                throw exception;
            }
        }

        void _ThrowLastSocketError( )
        {
            auto err = std::bit_cast<WinError>( WSAGetLastError( ) );
            _ThrowSocketError( err );
        }

        void _ThrowLastSocketError( const wchar_t* function, const wchar_t* filename, int lineNumber )
        {
            auto err = std::bit_cast<WinError>( WSAGetLastError( ) );
            _ThrowSocketError( err, function, filename, lineNumber );
        }

    }
    // ------------------------------------------------------------------------
    // Address
    // ------------------------------------------------------------------------
    Address::Address( AddressFamily addressFamily, const wchar_t* addressString )
        : length_( 0 ), storage_{}
    {
        int sizeofStorage = DataSize;
        auto rc = WSAStringToAddressW( (LPWSTR)addressString, static_cast<int>( addressFamily ), nullptr, (sockaddr*)&storage_, &sizeofStorage );
        if ( rc == SOCKET_ERROR )
        {
            HCC_THROW_LAST_SOCKET_ERROR( );
        }
        length_ = sizeofStorage;
    }

    Address::Address( AddressFamily addressFamily, const ProtocolInfo& protocolInfo, const wchar_t* addressString )
        : length_( 0 ), storage_{}
    {
        int sizeofStorage = DataSize;
        auto rc = WSAStringToAddressW( (LPWSTR)addressString, static_cast<int>( addressFamily ), const_cast<WSAPROTOCOL_INFOW*>( protocolInfo.data() ), (sockaddr*)&storage_, &sizeofStorage );
        if ( rc == SOCKET_ERROR )
        {
            HCC_THROW_LAST_SOCKET_ERROR( );
        }
        length_ = sizeofStorage;
    }

    Address::Address( const wchar_t* nodeName, const wchar_t* serviceName, const ADDRINFOW* hints )
        : length_( 0 ), storage_{}
    {
        ADDRINFOW* ai = nullptr;
        auto rc = std::bit_cast<WinError>( GetAddrInfoW( nodeName, serviceName, hints, &ai ) );
        if ( rc != WinError::None )
        {
            HCC_THROW_SOCKET_ERROR( rc );
        }

        memcpy( &storage_, ai->ai_addr, ai->ai_addrlen );
        FreeAddrInfoW( ai );
    }
    Address::Address( const wchar_t* nodeName, UInt16 portNumber, const ADDRINFOW* hints )
        : length_( 0 ), storage_{}
    {
        ADDRINFOW* ai = nullptr;
        wchar_t buffer[7] = {0,};
        _itow_s( static_cast<int>(portNumber), buffer, 10 );

        auto rc = static_cast<WinError>( GetAddrInfoW( nodeName, buffer, hints, &ai ) );
        if ( rc != WinError::None )
        {
            HCC_THROW_SOCKET_ERROR( rc );
        }

        memcpy( &storage_, ai->ai_addr, ai->ai_addrlen );
        length_ = static_cast<int>(ai->ai_addrlen);
        FreeAddrInfoW( ai );
    }

    Address::Address( UInt16 portNumber, const ADDRINFOW* hints )
        : Address( L"localhost", portNumber, hints )
    {
    }


    WideString Address::ToString( ) const
    {
        wchar_t buffer[128];
        DWORD bufferSize = sizeof( buffer )/sizeof(wchar_t);
        WSAAddressToStringW( (sockaddr*)&storage_, length_, nullptr, buffer, &bufferSize );
        WideString result( buffer, static_cast<size_t>( bufferSize - 1 ) );
        return result;
    }

    // ------------------------------------------------------------------------
    // AddressInfo
    // ------------------------------------------------------------------------
    AddressInfo::AddressInfo( const wchar_t* nodeName, const wchar_t* serviceName, DWORD addressNamespace, const Guid* namespaceId, timeval* timeout, const ADDRINFOEXW* hints )
    {
        auto rc = std::bit_cast<WinError>( GetAddrInfoExW( nodeName, serviceName, static_cast<DWORD>( addressNamespace ), (GUID*)namespaceId,hints, &data_, timeout, nullptr, nullptr, nullptr ) );
        if ( rc != WinError::None )
        {
            HCC_THROW_SOCKET_ERROR( rc );
        }
    }
    AddressInfo::~AddressInfo( )
    {
        if ( data_ )
        {
            FreeAddrInfoExW( data_ );
        }
    }



    // ------------------------------------------------------------------------
    // Socket
    // ------------------------------------------------------------------------

    void Socket::ThrowLastSocketError( )
    {
        _ThrowLastSocketError( );
    }
    void Socket::ThrowLastSocketError( const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        _ThrowLastSocketError( function, filename, lineNumber );
    }

    void Socket::ThrowSocketError( WinError error )
    {
        _ThrowSocketError( error );
    }
    void Socket::ThrowSocketError( WinError error, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        _ThrowSocketError( error, function, filename, lineNumber );
    }


    namespace
    {
        LPFN_WSARECVMSG  RecvMsgPtr = nullptr;
        LPFN_WSASENDMSG  SendMsgPtr = nullptr;
        LPFN_WSAPOLL PollPtr = nullptr;
        LPFN_TRANSMITFILE TransmitFilePtr = nullptr;
        LPFN_TRANSMITPACKETS TransmitPacketsPtr = nullptr;

        LPFN_CONNECTEX ConnectExPtr = nullptr;
        LPFN_ACCEPTEX AcceptExPtr = nullptr;
        LPFN_GETACCEPTEXSOCKADDRS GetAcceptExSockaddrsPtr = nullptr;
        LPFN_DISCONNECTEX DisconnectExPtr = nullptr;
        CriticalSection criticalSection;


        LPFN_WSARECVMSG GetRecvMsg( SOCKET s )
        {
            if ( RecvMsgPtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( RecvMsgPtr == nullptr )
                {
                    GUID RecvMsgId = WSAID_WSARECVMSG;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &RecvMsgId, sizeof( RecvMsgId ), &RecvMsgPtr, sizeof( RecvMsgPtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return RecvMsgPtr;
        }

        LPFN_WSASENDMSG GetSendMsg( SOCKET s )
        {
            if ( SendMsgPtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( SendMsgPtr == nullptr )
                {
                    GUID SendMsgId = WSAID_WSASENDMSG;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &SendMsgId, sizeof( SendMsgId ), &SendMsgPtr, sizeof( SendMsgPtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return SendMsgPtr;
        }

        LPFN_WSAPOLL GetPoll( SOCKET s )
        {
            if ( PollPtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( PollPtr == nullptr )
                {
                    GUID PollId = WSAID_WSAPOLL;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &PollId, sizeof( PollId ), &PollPtr, sizeof( PollPtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return PollPtr;
        }

        LPFN_TRANSMITFILE GetTransmitFile( SOCKET s )
        {
            if ( TransmitFilePtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( TransmitFilePtr == nullptr )
                {
                    GUID TransmitFileId = WSAID_TRANSMITPACKETS;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &TransmitFileId, sizeof( TransmitFileId ), &TransmitFilePtr, sizeof( TransmitFilePtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return TransmitFilePtr;
        }

        LPFN_TRANSMITPACKETS GetTransmitPackets( SOCKET s )
        {
            if ( TransmitPacketsPtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( TransmitPacketsPtr == nullptr )
                {
                    GUID TransmitPacketsExId = WSAID_TRANSMITPACKETS;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &TransmitPacketsExId, sizeof( TransmitPacketsExId ), &TransmitPacketsPtr, sizeof( TransmitPacketsPtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return TransmitPacketsPtr;
        }

        LPFN_CONNECTEX GetConnectEx( SOCKET s )
        {
            if ( ConnectExPtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( ConnectExPtr == nullptr )
                {
                    GUID GuidConnectEx = WSAID_CONNECTEX;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidConnectEx, sizeof( GuidConnectEx ), &ConnectExPtr, sizeof( ConnectExPtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return ConnectExPtr;
        }

        LPFN_ACCEPTEX GetAcceptEx( SOCKET s )
        {
            if ( AcceptExPtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( AcceptExPtr == nullptr )
                {
                    GUID GuidAcceptEx = WSAID_ACCEPTEX;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx, sizeof( GuidAcceptEx ), &AcceptExPtr, sizeof( AcceptExPtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return AcceptExPtr;
        }
        LPFN_GETACCEPTEXSOCKADDRS GetGetAcceptExSockaddrsPtr( SOCKET s )
        {
            if ( GetAcceptExSockaddrsPtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( GetAcceptExSockaddrsPtr == nullptr )
                {
                    GUID GuidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidGetAcceptExSockaddrs, sizeof( GuidGetAcceptExSockaddrs ), &GetAcceptExSockaddrsPtr, sizeof( GetAcceptExSockaddrsPtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return GetAcceptExSockaddrsPtr;
        }

        LPFN_DISCONNECTEX GetDisconnectEx( SOCKET s )
        {
            if ( DisconnectExPtr == nullptr )
            {
                std::lock_guard<CriticalSection> lockGuard( criticalSection );
                if ( DisconnectExPtr == nullptr )
                {
                    GUID GuidDisconnectEx = WSAID_DISCONNECTEX;
                    DWORD dwBytes = 0;
                    auto rc = WSAIoctl( s, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidDisconnectEx, sizeof( GuidDisconnectEx ), &DisconnectExPtr, sizeof( DisconnectExPtr ), &dwBytes, NULL, NULL );
                    if ( rc == SOCKET_ERROR )
                    {
                        HCC_THROW_LAST_SOCKET_ERROR( );
                    }
                }
            }
            return DisconnectExPtr;
        }
    }

    WinError Socket::RecvMsg( SOCKET socket, LPWSAMSG msg, LPDWORD numberOfBytesRecvd, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine )
    {
        auto function = GetRecvMsg( socket );
        auto rc = function( socket, msg, numberOfBytesRecvd, overlapped, completionRoutine );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }
    WinError Socket::SendMsg( SOCKET socket, LPWSAMSG msg, DWORD flags, LPDWORD numberOfBytesSent, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine )
    {
        auto function = GetSendMsg( socket );
        auto rc = function( socket, msg, flags, numberOfBytesSent, overlapped, completionRoutine );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }
    WinError Socket::Poll( LPWSAPOLLFD fdarray, ULONG nfds, INT timeout, Int32* result )
    {
        if ( nfds )
        {
            auto function = GetPoll( fdarray[0].fd );
            auto rc = function( fdarray, nfds, timeout );
            if ( rc == SOCKET_ERROR )
            {
                *result = 0;
                return LastSocketError( );
            }
            *result = rc;
            return WinError::None;
        }
        else
        {
            *result = 0;
            return WinError::None;
        }
    }
    WinError Socket::TransmitFile( SOCKET hSocket, HANDLE hFile, DWORD numberOfBytesToWrite, DWORD numberOfBytesPerSend, LPOVERLAPPED overlapped, LPTRANSMIT_FILE_BUFFERS transmitBuffers, DWORD flags )
    {
        auto function = GetTransmitFile( hSocket );
        auto rc = function( hSocket, hFile, numberOfBytesToWrite, numberOfBytesPerSend, overlapped, transmitBuffers, flags );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }
    WinError Socket::TransmitPackets( SOCKET hSocket, LPTRANSMIT_PACKETS_ELEMENT packetArray, DWORD elementCount, DWORD sendSize, LPOVERLAPPED overlapped, DWORD flags )
    {
        auto function = GetTransmitPackets( hSocket );
        auto rc = function( hSocket, packetArray, elementCount, sendSize, overlapped, flags );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }


    WinError Socket::ConnectEx( SOCKET socket, const sockaddr* name, int namelen, PVOID sendBuffer, DWORD sendDataLength, LPDWORD bytesSent, OVERLAPPED* overlapped )
    {
        auto function = GetConnectEx( socket );
        auto rc = function( socket, name, namelen, sendBuffer, sendDataLength, bytesSent, overlapped );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }

    WinError Socket::AcceptEx( SOCKET socket, SOCKET acceptSocket, PVOID outputBuffer, DWORD receiveDataLength, DWORD localAddressLength, DWORD remoteAddressLength, DWORD* bytesReceived, OVERLAPPED* overlapped )
    {
        auto function = GetAcceptEx( socket );
        auto rc = function( socket, acceptSocket, outputBuffer, receiveDataLength, localAddressLength, remoteAddressLength, bytesReceived, overlapped );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }

    WinError Socket::GetAcceptExSockaddrs( SOCKET socket, const Byte* outputBuffer, DWORD receiveDataLength, DWORD localAddressLength, DWORD remoteAddressLength, struct sockaddr** localSockaddr, LPINT localSockaddrLength, struct sockaddr** remoteSockaddr, LPINT remoteSockaddrLength )
    {
        auto function = GetGetAcceptExSockaddrsPtr( socket );
        function( (PVOID)outputBuffer, receiveDataLength, localAddressLength, remoteAddressLength, localSockaddr, localSockaddrLength, remoteSockaddr, remoteSockaddrLength );
        return WinError::None;
    }

    WinError Socket::DisconnectEx( SOCKET socket, OVERLAPPED* overlapped, bool reuse )
    {
        auto function = GetDisconnectEx( socket );
        auto rc = function( socket, overlapped, reuse ? TF_REUSE_SOCKET : 0, 0 );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }



    WinError Socket::ConnectEx( const sockaddr* name, int namelen, PVOID sendBuffer, DWORD sendDataLength, LPDWORD bytesSent, OVERLAPPED* overlapped ) const
    {
        auto function = GetConnectEx( Handle( ) );
        auto rc = function( Handle( ), name, namelen, sendBuffer, sendDataLength, bytesSent, overlapped );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }

    WinError Socket::AcceptEx( const Socket& acceptSocket, PVOID outputBuffer, DWORD receiveDataLength, DWORD localAddressLength, DWORD remoteAddressLength, DWORD* bytesReceived, OVERLAPPED* overlapped ) const
    {
        auto function = GetAcceptEx( Handle( ) );
        auto rc = function( Handle( ), acceptSocket.Handle( ), outputBuffer, receiveDataLength, localAddressLength, remoteAddressLength, bytesReceived, overlapped );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }

    void Socket::GetAcceptExSockaddrs( const Byte* outputBuffer, DWORD receiveDataLength, DWORD localAddressLength, DWORD remoteAddressLength, struct sockaddr** localSockaddr, LPINT localSockaddrLength, struct sockaddr** remoteSockaddr, LPINT remoteSockaddrLength ) const
    {
        auto function = GetGetAcceptExSockaddrsPtr( Handle( ) );
        function( (PVOID)outputBuffer, receiveDataLength, localAddressLength, remoteAddressLength, localSockaddr, localSockaddrLength, remoteSockaddr, remoteSockaddrLength );
    }

    WinError Socket::DisconnectEx( OVERLAPPED* overlapped, bool reuse ) const
    {
        auto function = GetDisconnectEx( Handle( ) );
        auto rc = function( Handle( ), overlapped, reuse ? TF_REUSE_SOCKET : 0, 0 );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }

    WinError Socket::Disconnect( bool reuse ) const
    {
        auto function = GetDisconnectEx( Handle( ) );
        auto rc = function( Handle( ), nullptr, reuse ? TF_REUSE_SOCKET : 0, 0 );
        if ( !rc )
        {
            return LastSocketError( );
        }
        return WinError::None;
    }


    // ------------------------------------------------------------------------
    // WSA
    // ------------------------------------------------------------------------

    WSAInitTerm::WSAInitTerm( WORD versionRequested )
        : versionRequested_( versionRequested ), wsaData_{}
    {
        auto rc = static_cast<WinError>(WSAStartup( versionRequested_, &wsaData_ ));
        if ( rc != WinError::None )
        {
            HCC_THROW_SOCKET_ERROR( rc );
        }
    }
    WSAInitTerm::~WSAInitTerm( )
    {
        WSACleanup( );
    }
}