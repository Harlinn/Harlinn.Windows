# Introduction to Communications using Windows Winsock 2 API

The primary source of information about Windows Winsock 2 API is, obviously, [Microsoft's Windows Sockets 2 documentation](https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2). 

Another excellent source of information about Windows Winsock 2 development can be found at 
[Tutorials on 'Advanced' Winsock 2 Network Programming using C](https://www.winsocketdotnetworkprogramming.com/winsock2programming/).

It is probably fair to describe my set of articles about Windows Winsock 2 development as an
abridged version of the above, with a few extra bits thrown in. The Winsock 2 API is a C 
API, so I will also introduce a set of C++ classes, and templates, that I use to simplify Winsock 2 development.

The bulk of the declarations lives inside the `Harlinn::Common::Core::IO::Sockets` namespace, provided in *HCCSocket.h*, so you need to put: 
```C++
#include <HCCSocket.h>
```
somewhere in your source code before you can use them.

## Winsock 2 Initialization and Termination
Every application that is going to use the Winsock 2 API, must call the `WSAStartup` before 
attempting to call the other functions of the API. `WSAStartup` requires that the developer 
specifies the version of Windows Sockets required, and it retrieves the details of the specific 
Windows Sockets implementation. The current version of the API is version 2.2, which was introduced 
with Windows NT 4.0. So, unless a new version comes along, version 2.2 is the version
you most likely want to specify when calling `WSAStartup`.

When the application is done using the Winsock API, it must call `WSACleanup` to free the internal 
Winsock resources used by the application.

The application can call `WSAStartup` more than once if it needs to, and each call must be matched
by a call to `WSACleanup`. A simple way to ensure this, is to create a class that calls `WSAStartup`
in its constructor, and `WSACleanup` is its destructor:
```C++
    class WSAInitTerm
    {
        WORD versionRequested_;
        WSADATA wsaData_;
    public:
        HCC_EXPORT explicit WSAInitTerm( WORD versionRequested = MAKEWORD( 2, 2 ) );
        HCC_EXPORT ~WSAInitTerm( );
        const WSADATA& data( ) const noexcept
        {
            return wsaData_;
        }
    };
``` 

Where the constructor and destructor is implemented as:
```C++
    WSAInitTerm::WSAInitTerm( WORD versionRequested )
        : versionRequested_( versionRequested ), wsaData_{}
    {
        auto rc = static_cast<WinError>(WSAStartup( versionRequested_, &wsaData_ ));
        if ( rc != WinError::None )
        {
            _ThrowSocketError( rc );
        }
    }
    WSAInitTerm::~WSAInitTerm( )
    {
        WSACleanup( );
    }
``` 

making it simple to ensure that the call to `WSAStartup` is matched by a call to `WSACleanup`:
```C++
#include <HCCSocket.h>
using namespace Harlinn::Common::Core;

int main()
{
    IO::Sockets::WSAInitTerm wsaInitTerm;
}
``` 

## Error handling
The header file *HCCWinError.h* declares the enumeration `enum class WinError`, which maps 
a subset of the `#define`d error identification constants in *winerror.h* to enumeration
values. Since the Visual Studio debugger displays the name of an enumeration value, and 
not just the integer value, this cuts down the time it takes to figure out what went wrong
in a debugging session.

Assuming that `s` is a `SOCKET` representing a non-blocking, connected, TCP session; the 
following code can be used to receive some data arriving on that socket:
```C++
    char buffer[1024];
    int bytesReceived = recv(s, buffer, sizeof(buffer) );
    if( bytesReceived == SOCKET_ERROR )
    {
        // since bytesReceived is equal to SOCKET_ERROR,
        // we know something *may* have gone wrong, so now
        // we call WSAGetLastError to get the actual error 
        // code:
        int errorCode = WSAGetLastError( );
        // Handle the error code, which *may* be an actual
        // error, or perhaps just a notification. 
    }
    else if( bytesReceived == 0)
    {
        // Peer initiated a graceful close of the connection
    }
    else
    {
        // Process the data
    }
```
Compared to most of the Windows API, Winsock 2 error handling requires a bit more coding
to get right. When [`SetEvent`](https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-setevent) 
returns `FALSE`, we know that something went wrong enough to justify throwing an exception. 
When `recv` returns `SOCKET_ERROR`, `WSAGetLastError` may return `WSAEWOULDBLOCK`, indicating 
that the receive operation would block. Whether this should be considered an error that 
justifies throwing an exception, or a notification that must be handled by the caller, 
depends on how the rest of the code for I/O on the socket is wired together.

It is also worth noting that when `recv` return `0` for this type of socket, it indicates
that the client has called `shutdown` with `SD_SEND` or `SD_BOTH`, initiating a graceful
shutdown of the TCP session; or, if the server called `shutdown` with `SD_SEND` first,
the final shutdown notification for the socket on the server.

If `s` represents an UDP socket, `recv` will return `0` for a zero length UDP message,
which is a perfectly valid UDP message.

The `Socket` class implements a static function `LastSocketError` that converts the 
return value of `WSAGetLastError` into a `WinError` enumeration value:
```C++
    class Socket 
    {
    public:
        .
        .
        static WinError LastSocketError( )
        {
            return std::bit_cast<WinError>( WSAGetLastError( ) );
        }
        .
        .
    };
```
## The `Address` class
The `Address` class provides a generic mechanism for specifying a transport address. The 
WinSock 2 API provides several functions that can be used to parse a textual representation
into the binary format required for a particular address family. The address family is
specified using a value from the `enum class AddressFamily` enumeration, where:

- `AddressFamily::INetV4` specifies an IP version 4 formatted address.
- `AddressFamily::INetV6` specifies an IP version 6 formatted address.

The class is implemented using two functions from the Winsock 2 API to parse addresses.
Two of the `Address` constructors: 
```C++
    Address( AddressFamily addressFamily, const wchar_t* addressString );
    Address( AddressFamily addressFamily, const ProtocolInfo& protocolInfo, const wchar_t* addressString );
```
are implemented using `WSAStringToAddressW`, while 
```C++
    Address( const wchar_t* nodeName, const wchar_t* serviceName, const ADDRINFOW* hints = nullptr );
    Address( const wchar_t* nodeName, UInt16 portNumber, const ADDRINFOW* hints = nullptr );
    Address( UInt16 portNumber, const ADDRINFOW* hints = nullptr );
```
are implemented using `GetAddrInfoW`. While it is quite possible that `GetAddrInfoW` will return 
more than one transport address, the first one is usually good enough for the `Address` class
implementation. When it is not, use the `AddressInfo` class which supports iteration over the returned
collection of addresses.  




## The `Socket` class
The `Socket` class is a wrapper for the Winsock 2 `SOCKET` type. Like the rest of the handle 
type classes under the `Harlinn::Common::Core` namespace, it is move constructible and
move assignable, but neither copy constructible nor copy assignable.

The default constructor assigns `INVALID_SOCKET` to `socket_`, the only member variable of
the `Socket` class, and a `static_assert( sizeof( SOCKET ) == sizeof( Socket ) );` 
verifies that use the `Socket` class adds no additional memory requirements to the application. 

The destructor will call `closesocket` on `socket_` if its value is not equal to `INVALID_SOCKET`:
```C++
    ~Socket( )
    {
        if ( socket_ != INVALID_SOCKET )
        {
            closesocket( socket_ );
        }
    }
```
This design prevents the application from leaking resources when a `Socket` object goes out 
of scope. 

The Winsock 2 API is designed to handle multiple protocols, which is good. However,
it does not, for good and valid reasons, isolate the developer from all the differences 
between how each supported protocol works. The Winsock 2 API provides 5 socket types:
- `SOCK_STREAM`: A socket type that provides sequenced, reliable, two-way, connection-based byte streams with an OOB data transmission mechanism. 
- `SOCK_DGRAM`: A socket type that supports datagrams, which are connectionless, unreliable buffers of a fixed maximum length. 
- `SOCK_RAW`: A socket type that provides a raw socket that allows an application to manipulate the next upper-layer protocol header. 
- `SOCK_RDM`: A socket type that provides a reliable message datagram.
- `SOCK_SEQPACKET`: A socket type that provides a pseudo-stream packet based on datagrams.

These `#define`d values are mapped to an enumeration: 
```C++
    enum class SocketType 
    {
        Stream = SOCK_STREAM,
        Datagram = SOCK_DGRAM,
        Raw = SOCK_RAW,
        ReliableDatagramMessage = SOCK_RDM,
        SequencedPacketStream = SOCK_SEQPACKET
    };
```
and a set of templates: 
```C++
    template<ProtocolType protocolType>
    using StreamSocket = SocketT<SocketType::Stream, protocolType>;

    template<ProtocolType protocolType>
    using DatagramSocket = SocketT<SocketType::Datagram, protocolType>;

    template<ProtocolType protocolType>
    using RawSocket = SocketT<SocketType::Raw, protocolType>;

    template<ProtocolType protocolType>
    using ReliableDatagramMessageSocket = SocketT<SocketType::ReliableDatagramMessage, protocolType>;

    template<ProtocolType protocolType>
    using SequencedPacketStreamSocket = SocketT<SocketType::SequencedPacketStream, protocolType>;
```
Where SocketT is a simple C++ template:
```C++
    template<SocketType socketType, ProtocolType protocolType>
    class SocketT : public Socket
    {
    public:
        using Base = Socket;
        static constexpr Sockets::SocketType SocketType = socketType;
        static constexpr Sockets::ProtocolType ProtocolType = protocolType;

        SocketT()
            : Base()
        { }
    protected:
        SocketT( SOCKET socket )
            : Base( socket )
        { }
    public:
        template< typename ... Args >
        SocketT( AddressFamily addressFamily, Args&&... args )
            : Base( addressFamily, SocketType, ProtocolType, std::forward<Args>(args)... )
        { }

        void Open( AddressFamily addressFamily, Flags flags = Flags::None )
        {
            Base::Open( addressFamily, SocketType, ProtocolType, flags );
        }
    };
```
and `ProtocolType` is another enumeration that maps the set of `IPPROTO_`xxx `#define`d values to enumeration values.

The `Socket` class implements the interface to the Winsock 2 API, 


### The `TcpSocket` class
The `TcpSocket` class is derived from the `StreamSocket` template, instantiated for `ProtocolType::Tcp`.



### The `UdpSocket` class
The `UdpSocket` class is derived from the `DatagramSocket` template, instantiated for `ProtocolType::UserDatagram`.