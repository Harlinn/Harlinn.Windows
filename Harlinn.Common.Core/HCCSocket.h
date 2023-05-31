#pragma once
#ifndef __HCCSOCKET_H__
#define __HCCSOCKET_H__

#include <HCCIO.h>
#include <HCCIOContext.h>
#include <HCCBinaryReader.h>
#include <HCCBinaryWriter.h>

#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"Ws2_32.lib")

namespace Harlinn::Common::Core::IO::Sockets
{

    enum class AddressFamily : UInt16
    {
        Unknown = 0xFFFF,
        Unspecified = AF_UNSPEC,
        // local to host (pipes, portals)
        Unix = AF_UNIX,
        // internetwork: UDP, TCP, etc.
        InterNetwork = AF_INET,
        INet = AF_INET,
        INetV4 = AF_INET,
        // arpanet imp addresses
        ImpLink = AF_IMPLINK,
        // pup protocols: e.g. BSP
        Pup = AF_PUP,
        // mit CHAOS protocols
        Chaos = AF_CHAOS,
        // XEROX NS protocols
        NS = AF_NS,
        // IPX protocols: IPX, SPX, etc.
        Ipx = AF_IPX,
        // ISO protocols
        Iso = AF_ISO,
        // OSI is ISO
        Osi = AF_OSI,
        // european computer manufacturers
        Ecma = AF_ECMA,
        // datakit protocols
        DataKit = AF_DATAKIT,
        // CCITT protocols, X.25 etc
        Ccitt = AF_CCITT,
        // IBM SNA
        Sna = AF_SNA,
        // DECnet
        DecNet = AF_DECnet,
        // Direct data link interface
        DataLink = AF_DLI,
        // LAT
        Lat = AF_LAT,
        // NSC Hyperchannel
        HyperChannel = AF_HYLINK,
        // AppleTalk
        AppleTalk = AF_APPLETALK,
        // NetBios-style addresses
        NetBios = AF_NETBIOS,
        // VoiceView
        VoiceView = AF_VOICEVIEW,
        // Protocols from Firefox
        FireFox = AF_FIREFOX,
        // Banyan
        Banyan = AF_BAN,
        // Native ATM Services
        Atm = AF_ATM,
        // Internetwork Version 6
        InterNetworkV6 = AF_INET6,
        INetV6 = AF_INET6,
        // Microsoft Wolfpack
        Cluster = AF_CLUSTER,
        // IEEE 1284.4 workgroup address
        Ieee12844 = AF_12844,
        // IrDA
        Irda = AF_IRDA,
        // Network Designers OSI & gateway
        NetworkDesigners = AF_NETDES,


        TCNProcess = AF_TCNPROCESS,
        TCNMessage = AF_TCNMESSAGE,
        ICLFXBM = AF_ICLFXBM,
        // Bluetooth RFCOMM/L2CAP protocols
        Bluetooth = AF_BTH,
        Link = AF_LINK,
        HyperV = AF_HYPERV

    };

    template<typename DerivedT>
    class SocketHandler;
    class Socket;
    class ProtocolInfo;

    /// <summary>
    /// Provides a generic mechanism for specifying a transport address.
    /// </summary>
    class Address
    {
        friend class Socket;
        template<typename DerivedT>
        friend class SocketHandler;
        int length_;
        SOCKADDR_STORAGE storage_;
    public:
        static constexpr size_t DataSize = sizeof( SOCKADDR_STORAGE );
        constexpr Address( ) noexcept
            : length_(0),storage_{}
        {
        }

        /// <summary>
        /// Initializes a new Address object by converting zero-terminated string
        /// according to the specified address family.
        /// </summary>
        /// <param name="addressFamily">
        /// <p>
        /// The address family of the network address pointed to by the <c>addressString</c> parameter.
        /// </p>
        /// <p>
        /// An exception is thrown if <c>addressFamily</c> is not equal to <c>AddressFamily::INetV4</c>
        /// or <c>AddressFamily::INetV6</c>.
        /// </p>
        /// </param>
        /// <param name="addressString">
        /// A pointer to the zero-terminated string that contains the network address in standard text form to convert
        /// </param>
        HCC_EXPORT Address( AddressFamily addressFamily, const wchar_t* addressString );

        /// <summary>
        /// Initializes a new Address object by converting zero-terminated string
        /// according to the specified address family and <c>ProtocolInfo</c>.
        /// </summary>
        /// <param name="addressFamily">
        /// <p>
        /// The address family of the network address pointed to by the <c>addressString</c> parameter.
        /// </p>
        /// <p>
        /// An exception is thrown if <c>addressFamily</c> is not equal to <c>AddressFamily::INetV4</c>
        /// or <c>AddressFamily::INetV6</c>.
        /// </p>
        /// </param>
        /// <param name="protocolInfo">
        /// A reference to the ProtocolInfo object associated with the provider to be used.
        /// </param>
        /// <param name="addressString">
        /// A pointer to the zero-terminated string that contains the network address in standard text form to convert
        /// </param>
        HCC_EXPORT Address( AddressFamily addressFamily, const ProtocolInfo& protocolInfo, const wchar_t* addressString );

        /// <summary>
        /// Initializes a new Address object from the provided <c>sockaddr</c> structure.
        /// </summary>
        /// <param name="addr">
        /// A pointer to the <c>sockaddr</c> structure containing the address to copy.
        /// </param>
        /// <param name="addrlen">
        /// The length, in bytes, of the information in the provided <c>sockaddr</c> structure. 
        /// </param>
        Address( const struct sockaddr* addr, size_t addrlen )
            : length_( static_cast<int>( addrlen ) ), storage_{}
        {
            assert( addrlen <= DataSize );
            memcpy( &storage_, addr, addrlen );
        }

        HCC_EXPORT Address( const wchar_t* nodeName, const wchar_t* serviceName, const ADDRINFOW* hints = nullptr );
        HCC_EXPORT Address( const wchar_t* nodeName, UInt16 portNumber, const ADDRINFOW* hints = nullptr );
        HCC_EXPORT Address( UInt16 portNumber, const ADDRINFOW* hints = nullptr );

        void Assign( const struct sockaddr* addr, int addrlen ) noexcept
        {
            assert( addrlen <= DataSize );
            memcpy( &storage_, addr, static_cast<size_t>(addrlen) );
            length_ = addrlen;
        }

        void Reset( )
        {
            length_ = 0;
            storage_ = {};
        }


        constexpr int length( ) const noexcept
        {
            return length_;
        }
        void SetLength( int newLength ) noexcept
        {
            assert( newLength <= DataSize );
            length_ = newLength;
        }

        const sockaddr* data( ) const noexcept
        {
            return (const sockaddr*)&storage_;
        }
        sockaddr* data( ) noexcept
        {
            return (sockaddr*)&storage_;
        }

        AddressFamily Family( ) const noexcept
        {
            return static_cast<AddressFamily>( storage_.ss_family );
        }


        HCC_EXPORT std::wstring ToString( ) const;

    };


    




#pragma pack(push,8)
    /// <summary>
    /// A type that is binary compatible with SOCKET_ADDRESS_LIST.
    /// </summary>
    /// <remarks>
    /// If the number of elements that would be assigned to a SOCKET_ADDRESS_LIST
    /// object is known at compile-time 
    /// </remarks>
    template<size_t size>
    struct SocketAddressList
    {
        static constexpr size_t Size = size;
        INT iAddressCount = 0;
        SOCKET_ADDRESS Address[Size];

        SocketAddressList( )
            : Address{}
        {
        }

        template<size_t N>
            requires ( N <= Size )
        SocketAddressList( const std::array<Sockets::Address, N>& adresses )
            : iAddressCount( static_cast<INT>( N ) )
        {
            for ( size_t i = 0; i < N; ++i )
            {
                Address[i].iSockaddrLength = adresses[i].length( );
                Address[i].lpSockaddr = const_cast<SOCKADDR*>( reinterpret_cast<const SOCKADDR*>( adresses[i].data( ) ) );
            }
            for ( size_t i = N; i < Size; ++i )
            {
                Address[i].iSockaddrLength = 0;
                Address[i].lpSockaddr = nullptr;
            }
        }

        template<size_t N>
            requires ( N <= Size )
        SocketAddressList( Sockets::Address( &addresses )[N] )
            : iAddressCount( static_cast<INT>( N ) )
        {
            for ( size_t i = 0; i < N; ++i )
            {
                Address[i].iSockaddrLength = addresses[i].length( );
                Address[i].lpSockaddr = const_cast<SOCKADDR*>( reinterpret_cast<const SOCKADDR*>( addresses[i].data( ) ) );
            }
            for ( size_t i = N; i < Size; ++i )
            {
                Address[i].iSockaddrLength = 0;
                Address[i].lpSockaddr = nullptr;
            }
        }

        operator SOCKET_ADDRESS_LIST* ( )
        {
            return reinterpret_cast<SOCKET_ADDRESS_LIST*>( this );
        }
        operator const SOCKET_ADDRESS_LIST* ( ) const
        {
            return reinterpret_cast<const SOCKET_ADDRESS_LIST*>( this );
        }

    };
    static_assert( sizeof( SOCKET_ADDRESS_LIST ) == sizeof( SocketAddressList<1> ) );

#pragma pack(pop)


    namespace Inernal
    {

        class AddressListAdaptor
        {
        private:
            static constexpr size_t AddressOffset = offsetof( SOCKET_ADDRESS_LIST, Address );
            static constexpr size_t SocketAddressSize = sizeof( SOCKET_ADDRESS );
            SOCKET_ADDRESS_LIST* data_ = nullptr;

            static constexpr size_t DataSizeFor( size_t socketAddressCount )
            {
                size_t result = AddressOffset + ( socketAddressCount * SocketAddressSize );
                return result;
            }
        public:
            //template<typename VectorT>
            AddressListAdaptor(const std::vector<Address>& vector )
                : data_( reinterpret_cast<SOCKET_ADDRESS_LIST*> ( new Byte[DataSizeFor( vector.size() )] ) )
            {
                size_t size = vector.size( );
                data_->iAddressCount = static_cast<int>( vector.size( ) );
                for ( size_t i = 0; i < size; ++i )
                {
                    data_->Address[i].iSockaddrLength = vector[i].length( );
                    data_->Address[i].lpSockaddr = const_cast<SOCKADDR*>( reinterpret_cast<const SOCKADDR*>( vector[i].data( ) ) );
                }
            }

            AddressListAdaptor( const AddressListAdaptor& other ) = delete;
            AddressListAdaptor( AddressListAdaptor&& other ) = delete;

            ~AddressListAdaptor( )
            {
                if ( data_ )
                {
                    Byte* ptr = reinterpret_cast<Byte*>( data_ );
                    delete[] ptr;
                }
            }

            AddressListAdaptor& operator = ( const AddressListAdaptor& other ) = delete;
            AddressListAdaptor& operator = ( AddressListAdaptor&& other ) = delete;

            SOCKET_ADDRESS_LIST* data( ) const
            {
                return data_;
            }
        };
    }


    enum class SocketType 
    {
        // Supports reliable, two-way, connection-based byte streams without the duplication 
        // of data and without preservation of boundaries. A Socket of this type communicates 
        // with a single peer and requires a remote host connection before communication can begin. 
        // Stream uses the Transmission Control Protocol (ProtocolType.Tcp) and the 
        // AddressFamily.InterNetwork or AddressFamily.InterNetworkV6 address family.
        Stream = SOCK_STREAM,
        // datagram socket
        Datagram = SOCK_DGRAM,
        Raw = SOCK_RAW,
        ReliableDatagramMessage = SOCK_RDM,
        SequencedPacketStream = SOCK_SEQPACKET
    };

    enum class ProtocolType
    {
        IP = 0, // dummy for IP
        Unspecified = 0,
        IPv6HopByHopOptions = IPPROTO_HOPOPTS,
        Icmp = IPPROTO_ICMP,    // control message protocol
        Igmp = IPPROTO_IGMP,    // group management protocol
        Ggp = IPPROTO_GGP,    // gateway^2 (deprecated)
        IPv4 = IPPROTO_IPV4,
        Stream = IPPROTO_ST,
        Tcp = IPPROTO_TCP,    // tcp
        CoreBasedTrees = IPPROTO_CBT,
        ExteriorGateway = IPPROTO_EGP,
        PrivateInteriorGateway = IPPROTO_IGP,
        ParcUniversalPacket = IPPROTO_PUP,   // pup
        UserDatagram = IPPROTO_UDP,   // user datagram protocol
        InternetDatagram = IPPROTO_IDP,   // xns idp
        ReliableData = IPPROTO_RDP,
        // IPv6 header
        IPv6 = IPPROTO_IPV6,
        // IPv6 Routing header
        IPv6RoutingHeader = IPPROTO_ROUTING,
        // IPv6 fragmentation header
        IPv6FragmentHeader = IPPROTO_FRAGMENT,
        // encapsulating security payload
        IPSecEncapsulatingSecurityPayload = IPPROTO_ESP,
        // authentication header
        IPSecAuthenticationHeader = IPPROTO_AH,
        // ICMPv6
        IcmpV6 = IPPROTO_ICMPV6,
        // IPv6 no next header
        IPv6NoNextHeader = IPPROTO_NONE,
        // IPv6 Destination options
        IPv6DestinationOptions = IPPROTO_DSTOPTS,
        // Net disk protocol
        NetDisk = IPPROTO_ND,
        // Wideband monitoring
        WidebandMonitoring = IPPROTO_ICLFXBM,
        // Protocol independent multicast
        PIM = IPPROTO_PIM,
        // Pragmatic general multicast
        PGM = IPPROTO_PGM,
        // Level 2 tunneling protocol
        L2TP = IPPROTO_L2TP,
        // Stream control transmission protocol
        SCTP = IPPROTO_SCTP,
        // raw IP packet
        Raw = IPPROTO_RAW,  
        Ipx = 1000,
        Spx = 1256,
        SpxII = 1257,
        Unknown = -1,   // unknown protocol type
    };


    enum class AddressNamespace
    {
        All = NS_ALL,
        Sap = NS_SAP,
        Nds = NS_NDS,
        PeerBrowse = NS_PEER_BROWSE,
        Slp = NS_SLP,
        Dhcp = NS_DHCP,
        TcpIpLocal = NS_TCPIP_LOCAL,
        TcpIpHosts = NS_TCPIP_HOSTS,
        Dns = NS_DNS,
        NetbiosOverTcpIp = NS_NETBT,
        Wins = NS_WINS,
        Nls = NS_NLA,
        Bluetooth = NS_BTH,
        LocalName = NS_LOCALNAME,
        Nbp = NS_NBP,
        Ms = NS_MS,
        Stda = NS_STDA,
        Ntds = NS_NTDS,
        EMail = NS_EMAIL,
        PrnpName = NS_PNRPNAME,
        PrnpCloud = NS_PNRPCLOUD,
        X500 = NS_X500,
        Nis = NS_NIS,
        NisPlus = NS_NISPLUS,
        Wrq = NS_WRQ,
        NetDes = NS_NETDES
    };

    enum class AddressInfoFlags : UInt32
    {
        None = 0,
        Passive = AI_PASSIVE,
        CanonicalName = AI_CANONNAME,
        NumericHost = AI_NUMERICHOST,
        NumericServiceName = AI_NUMERICSERV,
        DnsOnly = AI_DNS_ONLY,
        ForceClearText = AI_FORCE_CLEAR_TEXT,
        BypassDnsCache = AI_BYPASS_DNS_CACHE,
        ReturnTtl = AI_RETURN_TTL,
        All = AI_ALL,
        AddressConfigured = AI_ADDRCONFIG,
        V4Mapped = AI_V4MAPPED,
        NonAuthoritative = AI_NON_AUTHORITATIVE,
        Secure = AI_SECURE,
        ReturnPreferredNames = AI_RETURN_PREFERRED_NAMES,
        FullyQualifiedDomainName = AI_FQDN,
        Fileserver = AI_FILESERVER,
        DisableIdnEncoding = AI_DISABLE_IDN_ENCODING,
        SecureWithFallback = AI_SECURE_WITH_FALLBACK,
        ExclusiveCustomServers = AI_EXCLUSIVE_CUSTOM_SERVERS,
        ReturnResponseFlags = AI_RETURN_RESPONSE_FLAGS,
        RequireSecure = AI_REQUIRE_SECURE,
        ResolutionHandle = AI_RESOLUTION_HANDLE,
        Extended = AI_EXTENDED
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( AddressInfoFlags, UInt32 );


    class AddressInfo
    {
    private:
        ADDRINFOEXW* data_ = nullptr;
    public:
        AddressInfo( )
        {
        }

        HCC_EXPORT AddressInfo( const wchar_t* nodeName, const wchar_t* serviceName, DWORD addressNamespace, const Guid* namespaceId = nullptr, timeval* timeout = nullptr, const ADDRINFOEXW* hints = nullptr );
        AddressInfo( const wchar_t* nodeName, const wchar_t* serviceName = nullptr, AddressNamespace addressNamespace = AddressNamespace::All, const Guid* namespaceId = nullptr, timeval* timeout = nullptr, const ADDRINFOEXW* hints = nullptr )
            : AddressInfo( nodeName, serviceName, static_cast<DWORD>( addressNamespace ), namespaceId, timeout, hints )
        {
        }

        AddressInfo( const AddressInfo& other ) = delete;
        AddressInfo( AddressInfo&& other ) noexcept
            : data_( other.data_ )
        {
            other.data_ = nullptr;
        }

        HCC_EXPORT ~AddressInfo( );

        AddressInfo& operator = ( const AddressInfo& other ) = delete;
        AddressInfo& operator = ( AddressInfo&& other ) noexcept
        {
            std::swap( data_, other.data_ );
            return *this;
        }


    public:
        class Entry
        {
            const AddressInfo* addressInfo_ = nullptr;
            const ADDRINFOEXW* data_ = nullptr;
        public:
            Entry( )
            { }
            Entry( const AddressInfo* addressInfo, const ADDRINFOEXW* data )
                : addressInfo_( addressInfo ), data_( data )
            {
            }

            auto operator<=>( const Entry& ) const = default;

            constexpr bool IsValid( ) const noexcept
            {
                return data_ != nullptr;
            }

            constexpr explicit operator bool( ) const noexcept
            {
                return data_ != nullptr;
            }

            AddressInfoFlags Flags( ) const noexcept
            {
                return static_cast<AddressInfoFlags>( data_->ai_flags );
            }
            AddressFamily Family( ) const noexcept
            {
                return static_cast<AddressFamily>( data_->ai_family );
            }

            Sockets::SocketType SocketType( ) const noexcept
            {
                return static_cast<Sockets::SocketType>( data_->ai_socktype );
            }

            Sockets::ProtocolType Protocol( ) const noexcept
            {
                return static_cast<Sockets::ProtocolType>( data_->ai_protocol );
            }

            Sockets::Address Address( ) const noexcept
            {
                return Sockets::Address( data_->ai_addr, data_->ai_addrlen );
            }

            std::span<const Byte> Blob( ) const noexcept
            {
                return std::span<const Byte>( (const Byte*)data_->ai_blob, static_cast<size_t>( data_->ai_bloblen ) );
            }

            std::wstring_view CanonicalName( ) const noexcept
            {
                return data_->ai_canonname;
            }

            const Guid& Provider( ) const noexcept
            {
                return reinterpret_cast<const Guid&>( data_->ai_provider );
            }

            Entry Next( ) const noexcept
            {
                return Entry( addressInfo_, data_->ai_next );
            }
        };

        Entry First( ) const noexcept
        {
            return Entry( this, data_ );
        }

        class Iterator
        {
            Entry entry_;
        public:
            Iterator( ) noexcept 
            { }

            Iterator( Entry entry ) noexcept :
                entry_( entry )
            { }

            Iterator& operator++( )
            {
                if ( entry_ )
                {
                    entry_ = entry_.Next( );
                }
                return *this;
            }

            Iterator operator++( int )
            {
                Iterator iterator( entry_ );
                if ( entry_ )
                {
                    entry_ = entry_.Next( );
                }
                return iterator;
            }

            bool operator!=( const Iterator& iterator )
            {
                return entry_ != iterator.entry_;
            }

            const Entry& operator*( )
            {
                return entry_;
            }
        };

        Iterator begin( ) const
        {
            return Iterator( First( ) );
        }
        Iterator end( ) const
        {
            return Iterator( );
        }


    };


    enum class SocketFlags : UInt32
    {
        None = 0,
        Overlapped = WSA_FLAG_OVERLAPPED,
        MultipointCRoot = WSA_FLAG_MULTIPOINT_C_ROOT,
        MultipointCLeaf = WSA_FLAG_MULTIPOINT_C_LEAF,
        MultipointDRoot = WSA_FLAG_MULTIPOINT_D_ROOT,
        MultipointDLeaf = WSA_FLAG_MULTIPOINT_D_LEAF,
        AccessSystemSecurity = WSA_FLAG_ACCESS_SYSTEM_SECURITY,
        NoHandleInherit = WSA_FLAG_NO_HANDLE_INHERIT,
        RegisteredIo = WSA_FLAG_REGISTERED_IO
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( SocketFlags, UInt32 );


    enum class ShutdownFlag : Int32
    {
        Receive = SD_RECEIVE,
        Send = SD_SEND,
        Both = SD_BOTH
    };


    enum class MessageFlags : UInt32
    {
        None = 0,
        // process out-of-band data
        OutOfBand = MSG_OOB,

        // Peeks at the incoming data. The data is copied into the buffer, 
        // but is not removed from the input queue.
        // This flag is valid only for nonoverlapped sockets.
        Peek = MSG_PEEK,

        // Specifies that the data should not be subject to routing. 
        // A Windows Sockets service provider can choose to ignore this flag.
        DontRoute = MSG_DONTROUTE,

        // The receive request will complete only when one of the following events occurs:
        //   * The buffer supplied by the caller is completely full.
        //   * The connection has been closed.
        //   * The request has been canceled or an error occurred.
        // Be aware that if the underlying transport provider does not support 
        // WaitAll, or if the socket is in a non-blocking mode, then this call 
        // will fail with WSAEOPNOTSUPP. Also, if WaitAll is specified along with 
        // OutOfBand, Peek, or Partial, then this call will fail with WSAEOPNOTSUPP.
        //
        // This flag is not supported on datagram sockets or message-oriented sockets.
        WaitAll = MSG_WAITALL,

        // This flag is for message-oriented sockets only. On output, this flag indicates 
        // that the data specified is a portion of the message transmitted by the sender. 
        // Remaining portions of the message will be specified in subsequent receive 
        // operations. A subsequent receive operation with the Partial flag cleared 
        // indicates end of sender's message.
        // As an input parameter, this flag indicates that the receive operation should 
        // complete even if only part of a message has been received by the transport provider.
        Partial = MSG_PARTIAL,

        // This flag is for stream-oriented sockets only. This flag allows an application 
        // that uses stream sockets to tell the transport provider not to delay completion 
        // of partially filled pending receive requests. This is a hint to the transport 
        // provider that the application is willing to receive any incoming data as soon 
        // as possible without necessarily waiting for the remainder of the data that might 
        // still be in transit. What constitutes a partially filled pending receive request 
        // is a transport-specific matter.
        //
        // In the case of TCP, this refers to the case of incoming TCP segments being placed
        // into the receive request data buffer where none of the TCP segments indicated a 
        // PUSH bit value of 1. In this case, TCP may hold the partially filled receive 
        // request a little longer to allow the remainder of the data to arrive with a 
        // TCP segment that has the PUSH bit set to 1. This flag tells TCP not to hold 
        // the receive request but to complete it immediately.
        //
        // Using this flag for large block transfers is not recommended since processing 
        // partial blocks is often not optimal. This flag is useful only for cases where 
        // receiving and processing the partial data immediately helps decrease processing 
        // latency.
        //
        // This flag is a hint rather than an actual guarantee.
        //
        // This flag is supported on Windows 8.1, Windows Server 2012 R2, and later.
        PushImmediate = MSG_PUSH_IMMEDIATE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( MessageFlags, UInt32 );

    /// <summary>
    /// Defines the values for a bit-mask that indicates the desire 
    /// for, or notification of, network events.
    /// </summary>
    /// <remarks>
    /// <p>
    /// To specify two, or more, event notifications use the binary or operator:
    /// </p>
    /// <code>
    /// EventFlags eventFlags = EventFlags::Read | EventFlags::Write;
    /// </code>
    /// </remarks>
    enum class EventFlags : Int32
    {
        None = 0,
        /// <summary>
        /// Wants to receive notification of readiness for reading.
        /// </summary>
        Read = FD_READ,
        /// <summary>
        /// Wants to receive notification of readiness for writing.
        /// </summary>
        Write = FD_WRITE,
        /// <summary>
        /// Wants to receive notification of the arrival of OOB data.
        /// </summary>
        OutOfBand = FD_OOB,
        /// <summary>
        /// Wants to receive notification of incoming connections.
        /// </summary>
        Accept = FD_ACCEPT,
        /// <summary>
        /// Wants to receive notification of completed connection or multipoint join operation.
        /// </summary>
        Connect = FD_CONNECT,
        /// <summary>
        /// Wants to receive notification of socket closure.
        /// </summary>
        Close = FD_CLOSE,
        /// <summary>
        /// Wants to receive notification of socket QoS changes.
        /// </summary>
        QualityOfService = FD_QOS,
        /// <summary>
        /// Want to receive notification of socket group QoS changes.
        /// </summary>
        GroupQualityOfService = FD_GROUP_QOS,
        /// <summary>
        /// Wants to receive notification of routing interface changes for the specified destination.
        /// </summary>
        RoutingInterfaceChange = FD_ROUTING_INTERFACE_CHANGE,
        /// <summary>
        /// Wants to receive notification of local address list changes for the address family of the socket.
        /// </summary>
        AddressListChange = FD_ADDRESS_LIST_CHANGE,
        All = FD_ALL_EVENTS
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( EventFlags, Int32 );


    /// <summary>
    /// Used to store a socket's internal information about network events
    /// </summary>
    class NetworkEvents : public WSANETWORKEVENTS
    {
    public:
        using Base = WSANETWORKEVENTS;

        NetworkEvents()
            : Base{}
        { }

        /// <summary>
        /// Retrieves the Sockets::EventFlags for this NetworkEvents object.
        /// </summary>
        /// <returns>
        /// The Sockets::EventFlags for this NetworkEvents object.
        /// </returns>
        constexpr Sockets::EventFlags EventFlags( ) const noexcept
        {
            return static_cast<Sockets::EventFlags>( lNetworkEvents );
        }

        /// <summary>
        /// Check if any of the events specified by the <c>eventFlags</c> is present
        /// in this NetworkEvents object.
        /// </summary>
        /// <param name="eventFlags">
        /// A bit-mask specifying the desired events.
        /// </param>
        /// <returns>
        /// <c>true</c> if any of the events are present, otherwise <c>false</c>.
        /// </returns>
        constexpr bool CheckForAnyOf( Sockets::EventFlags eventFlags ) const noexcept
        {
            return ContainsAnyOf( EventFlags( ), eventFlags );
        }
        
        /// <summary>
        /// Check if all of the events specified by the <c>eventFlags</c> is present
        /// in this NetworkEvents object.
        /// </summary>
        /// <param name="eventFlags">
        /// A bit-mask specifying the desired events.
        /// </param>
        /// <returns>
        /// <c>true</c> if all of the events are present, otherwise <c>false</c>.
        /// </returns>
        constexpr bool CheckForAllOf( Sockets::EventFlags eventFlags ) const noexcept
        {
            return ContainsAllOf( EventFlags( ), eventFlags );
        }

        /// <summary>
        /// Detect if the Socket is ready for reading.
        /// </summary>
        /// <returns>
        /// <c>true</c> if the Socket is ready for reading.
        /// </returns>
        constexpr bool ReadEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::Read ) != Sockets::EventFlags::None;
        }
        
        /// <summary>
        /// Detect if the Socket is ready for writing.
        /// </summary>
        /// <returns>
        /// <c>true</c> if the Socket is writing for reading.
        /// </returns>
        constexpr bool WriteEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::Write ) != Sockets::EventFlags::None;
        }
        

        /// <summary>
        /// Detect if out-of-band data has arrived on the Socket.
        /// </summary>
        /// <returns>
        /// <c>true</c> if out-of-band data has arrived on the Socket.
        /// </returns>
        constexpr bool OutOfBandEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::OutOfBand ) != Sockets::EventFlags::None;
        }

        /// <summary>
        /// Detect if incoming connections has arrived on the Socket.
        /// </summary>
        /// <returns>
        /// <c>true</c> if incoming connections has arrived on the Socket.
        /// </returns>
        constexpr bool AcceptEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::Accept ) != Sockets::EventFlags::None;
        }
        
        
        /// <summary>
        /// Detect if connect, or multi-point join, operations has completed.
        /// </summary>
        /// <returns>
        /// <c>true</c> if connect, or multi-point join, operations has completed.
        /// </returns>
        constexpr bool ConnectEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::Connect ) != Sockets::EventFlags::None;
        }


        /// <summary>
        /// Detect if a closure operation has completed.
        /// </summary>
        /// <returns>
        /// <c>true</c> if a closure operation has completed.
        /// </returns>
        constexpr bool CloseEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::Close ) != Sockets::EventFlags::None;
        }
        
        /// <summary>
        /// Detect if quality-of-service has changed.
        /// </summary>
        /// <returns>
        /// <c>true</c> if quality-of-service has changed.
        /// </returns>
        constexpr bool QualityOfServiceEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::QualityOfService ) != Sockets::EventFlags::None;
        }
        /// <summary>
        /// Detect if group quality-of-service has changed.
        /// </summary>
        /// <returns>
        /// <c>true</c> if group quality-of-service has changed.
        /// </returns>
        constexpr bool GroupQualityOfServiceEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::GroupQualityOfService ) != Sockets::EventFlags::None;
        }
        
        /// <summary>
        /// Detect if there are routing interface changes for the specified destination.
        /// </summary>
        /// <returns>
        /// <c>true</c> if there are routing interface changes for the specified destination.
        /// </returns>
        constexpr bool RoutingInterfaceChangeEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::RoutingInterfaceChange ) != Sockets::EventFlags::None;
        }
        
        /// <summary>
        /// Detect if there are local address list changes for the address family of the socket.
        /// </summary>
        /// <returns>
        /// <c>true</c> if there are local address list changes for the address family of the socket.
        /// </returns>
        constexpr bool AddressListChangeEvent( ) const noexcept
        {
            auto eventFlags = EventFlags( );
            return ( eventFlags & Sockets::EventFlags::AddressListChange ) != Sockets::EventFlags::None;
        }

        constexpr WinError ReadResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_READ_BIT] );
        }
        constexpr WinError WriteResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_WRITE_BIT] );
        }
        constexpr WinError OutOfBandResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_OOB_BIT] );
        }
        constexpr WinError AcceptResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_ACCEPT_BIT] );
        }
        constexpr WinError ConnectResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_CONNECT_BIT] );
        }
        constexpr WinError CloseResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_CLOSE_BIT] );
        }
        constexpr WinError QualityOfServiceResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_QOS_BIT] );
        }
        constexpr WinError GroupQualityOfServiceResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_GROUP_QOS_BIT] );
        }
        constexpr WinError RoutingInterfaceChangeResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_ROUTING_INTERFACE_CHANGE_BIT] );
        }
        constexpr WinError AddressListChangeResult( ) const noexcept
        {
            return static_cast<WinError>( iErrorCode[FD_ADDRESS_LIST_CHANGE_BIT] );
        }

    };


    struct TransmitFileBuffers : TRANSMIT_FILE_BUFFERS
    {
        using Base = TRANSMIT_FILE_BUFFERS;
        TransmitFileBuffers()
            : Base{}
        { }
    };

    struct TransmitPacketsElement : TRANSMIT_PACKETS_ELEMENT
    {
        using Base = TRANSMIT_PACKETS_ELEMENT;
        TransmitPacketsElement()
            : Base{}
        { }
    };


    enum class TransmitFileFlags : UInt32
    {
        None = 0,
        Disconnect = TF_DISCONNECT,
        ReuseSocket = TF_REUSE_SOCKET,
        WriteBehind = TF_WRITE_BEHIND,
        UseDefaultWorkee = TF_USE_DEFAULT_WORKER,
        UseSystemTHread = TF_USE_SYSTEM_THREAD,
        UseKernelAPc = TF_USE_KERNEL_APC
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TransmitFileFlags, UInt32 );


    enum class ServiceFlags1 : UInt32
    {
        None = 0,
        /// <summary>
        /// Provides connectionless (datagram) service. If not set, the protocol supports connection-oriented data transfer.
        /// </summary>
        Connectionless = XP1_CONNECTIONLESS,
        /// <summary>
        /// Guarantees that all data sent will reach the intended destination.
        /// </summary>
        GuaranteedDelivery = XP1_GUARANTEED_DELIVERY,
        /// <summary>
        /// Guarantees that data only arrives in the order in which it was 
        /// sent and that it is not duplicated. This characteristic does not 
        /// necessarily mean that the data is always delivered, but that any 
        /// data that is delivered is delivered in the order in which it was 
        /// sent.
        /// </summary>
        GuaranteedOrder = XP1_GUARANTEED_ORDER,
        /// <summary>
        /// Honors message boundaries—as opposed to a stream-oriented protocol 
        /// where there is no concept of message boundaries.
        /// </summary>
        MessageOriented = XP1_MESSAGE_ORIENTED,
        /// <summary>
        /// A message-oriented protocol, but message boundaries are ignored for 
        /// all receipts. This is convenient when an application does not desire 
        /// message framing to be done by the protocol.
        /// </summary>
        PseudoStream = XP1_PSEUDO_STREAM,
        /// <summary>
        /// Supports two-phase (graceful) close. If not set, only abortive 
        /// closes are performed.
        /// </summary>
        GracefulClose = XP1_GRACEFUL_CLOSE,
        /// <summary>
        /// Supports expedited (urgent) data.
        /// </summary>
        ExpeditedData = XP1_EXPEDITED_DATA,
        /// <summary>
        /// Supports connect data.
        /// </summary>
        ConnectData = XP1_CONNECT_DATA,
        /// <summary>
        /// Supports disconnect data.
        /// </summary>
        DisconnectData = XP1_DISCONNECT_DATA,
        /// <summary>
        /// Supports a broadcast mechanism.
        /// </summary>
        SupportBroadcast = XP1_SUPPORT_BROADCAST,
        /// <summary>
        /// Supports a multipoint or multicast mechanism. Control and 
        /// data plane attributes are indicated below.
        /// </summary>
        SupportMultipoint = XP1_SUPPORT_MULTIPOINT,
        /// <summary>
        /// Indicates whether the control plane is rooted (value = 1) or nonrooted (value = 0).
        /// </summary>
        MultipointControlPlane = XP1_MULTIPOINT_CONTROL_PLANE,
        /// <summary>
        /// Indicates whether the data plane is rooted (value = 1) or nonrooted (value = 0).
        /// </summary>
        MultipointDataPlane = XP1_MULTIPOINT_DATA_PLANE,
        /// <summary>
        /// Supports quality of service requests.
        /// </summary>
        QosSupported = XP1_QOS_SUPPORTED,
        /// <summary>
        /// Bit is reserved.
        /// </summary>
        Interrupt = XP1_INTERRUPT,
        /// <summary>
        /// Protocol is unidirectional in the send direction.
        /// </summary>
        UnidirectionalSend = XP1_UNI_SEND,
        /// <summary>
        /// Protocol is unidirectional in the recv direction.
        /// </summary>
        UnidirectionalReceive = XP1_UNI_RECV,
        /// <summary>
        /// Socket descriptors returned by the provider are operating system Installable File System (IFS) handles.
        /// </summary>
        InstallableFileSystemHandles = XP1_IFS_HANDLES,
        /// <summary>
        /// The MessageFlags::Partial flag is supported in Socket::Send and Socket::SendTo.
        /// </summary>
        PartialMessage = XP1_PARTIAL_MESSAGE,
        /// <summary>
        /// The protocol provides support for SAN.
        /// </summary>
        SanSupportSdp = XP1_SAN_SUPPORT_SDP

    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ServiceFlags1, UInt32 );

    enum class ProviderFlags : UInt32
    {
        None = 0,
        /// <summary>
        /// Indicates that this is one of two or more entries for a single 
        /// protocol (from a given provider) which is capable of implementing 
        /// multiple behaviors. An example of this is SPX which, on the 
        /// receiving side, can behave either as a message-oriented or a 
        /// stream-oriented protocol.
        /// </summary>
        MultipleProtocolEntries = PFL_MULTIPLE_PROTO_ENTRIES,
        /// <summary>
        /// Indicates that this is the recommended or most frequently used 
        /// entry for a protocol that is capable of implementing multiple behaviors.
        /// </summary>
        RecommendedProtocolEntry = PFL_RECOMMENDED_PROTO_ENTRY,
        /// <summary>
        /// Set by a provider to indicate to the Ws2_32.dll that this 
        /// protocol should not be returned in the result buffer generated 
        /// by WSAEnumProtocols. Obviously, a Windows Sockets 2 application 
        /// should never see an entry with this bit set.
        /// </summary>
        Hidden = PFL_HIDDEN,
        /// <summary>
        /// Indicates that a value of zero in the protocol parameter of 
        /// socket or WSASocket matches this protocol entry.
        /// </summary>
        MatchesProtocolZero = PFL_MATCHES_PROTOCOL_ZERO,
        /// <summary>
        /// Set by a provider to indicate support for network direct access.
        /// </summary>
        NetworkDirectProvider = PFL_NETWORKDIRECT_PROVIDER
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ProviderFlags, UInt32 );

    /// <summary>
    /// The ProtocolChain associated with the protocol. If the length 
    /// of the chain is 0, this ProtocolInfo entry represents a layered protocol 
    /// which has Windows Sockets 2 SPI as both its top and bottom edges. If the 
    /// length of the chain equals 1, this entry represents a base protocol whose 
    /// Catalog Entry identifier can be retrieved by calling CatalogEntryId() function 
    /// of the ProtocolInfo object. If the length of the chain is larger than 1, 
    /// this entry represents a protocol chain which consists of one or more layered 
    /// protocols on top of a base protocol. The corresponding Catalog Entry identifiers
    /// are in the ProtocolChain array starting with the layered protocol at the 
    /// top (the zero element in the ProtocolChain array) and ending with 
    /// the base protocol. Refer to the Windows Sockets 2 Service Provider Interface 
    /// specification for more information on protocol chains.
    /// </summary>
    class ProtocolChain : public WSAPROTOCOLCHAIN
    {
    public:
        size_t length( ) const noexcept
        {
            return static_cast<size_t>( ChainLen );
        }
        size_t size( ) const noexcept
        {
            return static_cast<size_t>( ChainLen );
        }
        DWORD* begin( )
        {
            return ChainEntries;
        }
        DWORD* end( )
        {
            return &ChainEntries[ChainLen];
        }
        const DWORD* begin( ) const
        {
            return ChainEntries;
        }
        const DWORD* end( ) const
        {
            return &ChainEntries[ChainLen];
        }
        DWORD& operator[]( size_t index )
        {
            return ChainEntries[index];
        }
        DWORD operator[]( size_t index ) const
        {
            return ChainEntries[index];
        }
    };

    enum class NetworkByteOrder
    { 
        BigEndian = BIGENDIAN,
        LittleEndian = LITTLEENDIAN
    };


    enum class SecurityProtocol
    {
        None = SECURITY_PROTOCOL_NONE
    };


    /// <summary>
    /// Used to store or retrieve complete information for a given protocol.
    /// </summary>
    class ProtocolInfo
    {
        WSAPROTOCOL_INFOW data_;
    public:
        ProtocolInfo( )
            : data_{}
        {
        }

        const WSAPROTOCOL_INFOW* data( ) const
        {
            return &data_;
        }
        WSAPROTOCOL_INFOW* data( )
        {
            return &data_;
        }

        /// <summary>
        /// Returns a bit-mask that describes the services provided by the protocol.
        /// </summary>
        /// <returns>
        /// A bit-mask of values from the <c>Sockets::ServiceFlags1</c> enumeration.
        /// </returns>
        constexpr Sockets::ServiceFlags1 ServiceFlags1( ) const noexcept
        {
            return static_cast<Sockets::ServiceFlags1>( data_.dwServiceFlags1 );
        }
        /// <summary>
        /// Sets a bit-mask that describes the services provided by the protocol.
        /// </summary>
        /// <param name="value">
        /// A bit-mask of values from the <c>Sockets::ServiceFlags1</c> enumeration.
        /// </param>
        void SetServiceFlags1( Sockets::ServiceFlags1 value ) noexcept
        {
            data_.dwServiceFlags1 = static_cast<DWORD>( value );
        }

        /// <summary>
        /// Reserved for additional protocol-attribute definitions.
        /// </summary>
        constexpr DWORD ServiceFlags2( ) const noexcept
        {
            return data_.dwServiceFlags2;
        }
        /// <summary>
        /// Reserved for additional protocol-attribute definitions.
        /// </summary>
        void SetServiceFlags2( DWORD value ) noexcept
        {
            data_.dwServiceFlags2 = value;
        }

        /// <summary>
        /// Reserved for additional protocol-attribute definitions.
        /// </summary>
        constexpr DWORD ServiceFlags3( ) const noexcept
        {
            return data_.dwServiceFlags3;
        }
        /// <summary>
        /// Reserved for additional protocol-attribute definitions.
        /// </summary>
        void SetServiceFlags3( DWORD value ) noexcept
        {
            data_.dwServiceFlags3 = value;
        }


        /// <summary>
        /// Reserved for additional protocol-attribute definitions.
        /// </summary>
        constexpr DWORD ServiceFlags4( ) const noexcept
        {
            return data_.dwServiceFlags4;
        }
        /// <summary>
        /// Reserved for additional protocol-attribute definitions.
        /// </summary>
        void SetServiceFlags4( DWORD value ) noexcept
        {
            data_.dwServiceFlags4 = value;
        }

        /// <summary>
        /// Returns a set of flags that provides information on how 
        /// this protocol is represented in the Winsock catalog.
        /// </summary>
        /// <returns>
        /// A bit-mask of values from the Sockets::ProviderFlags enumeration.
        /// </returns>
        constexpr Sockets::ProviderFlags ProviderFlags( ) const noexcept
        {
            return static_cast<Sockets::ProviderFlags>( data_.dwProviderFlags );
        }

        void SetProviderFlags( Sockets::ProviderFlags flags ) noexcept
        {
            data_.dwProviderFlags = static_cast<DWORD>( flags );
        }

        /// <summary>
        /// Returns a globally unique identifier (Guid) assigned to the 
        /// provider by the service provider vendor. This value is useful 
        /// for instances where more than one service provider is able to 
        /// implement a particular protocol. An application can use the 
        /// ProviderId member to distinguish between providers that might 
        /// otherwise be indistinguishable.
        /// </summary>
        /// <returns></returns>
        constexpr const Guid& ProviderId( ) const noexcept
        {
            return *std::bit_cast<Guid*>( &data_.ProviderId );
        }
        void SetProviderId( const Guid& value ) noexcept
        {
            data_.ProviderId = value.AsGuid( );
        }

        /// <summary>
        /// A unique identifier assigned by the WS2_32.DLL for each WSAPROTOCOL_INFO structure.
        /// </summary>
        /// <returns></returns>
        constexpr DWORD CatalogEntryId( ) const noexcept
        {
            return data_.dwCatalogEntryId;
        }
        void SetCatalogEntryId( DWORD value ) noexcept
        {
            data_.dwCatalogEntryId = value;
        }

        /// <summary>
        /// Retrieves a reference to the ProtocolChain associated with the protocol.
        /// </summary>
        /// <returns>
        /// A reference to the ProtocolChain.
        /// </returns>
        const Sockets::ProtocolChain& ProtocolChain( ) const noexcept
        {
            return *static_cast<const Sockets::ProtocolChain*>( &data_.ProtocolChain );
        }

        /// <summary>
        /// The protocol version identifier.
        /// </summary>
        /// <returns>
        /// The protocol version identifier
        /// </returns>
        constexpr int Version( ) const noexcept
        {
            return data_.iVersion;
        }

        /// <summary>
        /// Retrieves a value to pass as the address family parameter to the Socket constructor or 
        /// the Socket::Open function in order to open a socket for this protocol. This 
        /// value also uniquely defines the structure of a protocol address for a 
        /// Sockets::Address object used by the protocol.
        /// </summary>
        /// <returns>
        /// The Sockets::AddressFamily value for the protocol.
        /// </returns>
        constexpr Sockets::AddressFamily AddressFamily( ) const noexcept
        {
            return static_cast<Sockets::AddressFamily>( data_.iAddressFamily );
        }

        /// <summary>
        /// The maximum address length, in bytes.
        /// </summary>
        /// <returns>
        /// The maximum address length, in bytes.
        /// </returns>
        constexpr int MaxSocketAddressLength( ) const noexcept
        {
            return data_.iMaxSockAddr;
        }

        /// <summary>
        /// The minimum address length, in bytes.
        /// </summary>
        /// <returns>
        /// The minimum address length, in bytes.
        /// </returns>
        constexpr int MinSocketAddressLength( ) const noexcept
        {
            return data_.iMinSockAddr;
        }

        /// <summary>
        /// Retrieves the value to pass as the socket type parameter to the to the
        /// Socket constructor or the Socket::Open function in order to open a socket 
        /// for this protocol.
        /// </summary>
        /// <returns>
        /// The socket type value for the protocol.
        /// </returns>
        constexpr Sockets::SocketType SocketType( ) const noexcept
        {
            return static_cast<Sockets::SocketType>( data_.iSocketType );
        }

        /// <summary>
        /// Retrieves the value to pass as the protocol parameter to the to the
        /// Socket constructor or the Socket::Open function in order to open a socket 
        /// for this protocol.
        /// </summary>
        /// <returns>
        /// The protocol value for the protocol.
        /// </returns>
        constexpr Sockets::ProtocolType ProtocolType( ) const noexcept
        {
            return static_cast<Sockets::ProtocolType>( data_.iProtocol );
        }

        /// <summary>
        /// The maximum value that may be added to the numeric value of the result 
        /// of the Protocol( ) member function when supplying a value for the 
        /// protocolType parameter of the Socket constructor or the Socket::Open function. 
        /// Not all protocols allow a range of values. When this is the case ProtocolMaxOffset 
        /// returns is zero.
        /// </summary>
        /// <returns></returns>
        constexpr int ProtocolMaxOffset( ) const noexcept
        {
            return data_.iProtocolMaxOffset;
        }

        /// <summary>
        /// Returns a value that indicates either big-endian or little-endian with 
        /// the values NetworkByteOrder::BigEndian and NetworkByteOrder::LittleEndian respectively.
        /// </summary>
        /// <returns>
        /// The network byte order for the protocol.
        /// </returns>
        constexpr Sockets::NetworkByteOrder NetworkByteOrder() const noexcept
        {
            return static_cast<Sockets::NetworkByteOrder>( data_.iNetworkByteOrder );
        }

        /// <summary>
        /// The type of security scheme employed (if any). A value of SecurityProtocol::None 
        /// is used for protocols that do not incorporate security provisions.
        /// </summary>
        /// <returns>
        /// The type of security scheme
        /// </returns>
        constexpr Sockets::SecurityProtocol SecurityScheme( ) const noexcept
        {
            return static_cast<Sockets::SecurityProtocol>( data_.iSecurityScheme );
        }

        /// <summary>
        /// <p>
        /// The maximum message size, in bytes, supported by the protocol. This 
        /// is the maximum size that can be sent from any of the host's local 
        /// interfaces. For protocols that do not support message framing, the 
        /// actual maximum that can be sent to a given address may be less. There 
        /// is no standard provision to determine the maximum inbound message size. 
        /// The following special values are defined.
        /// </p>
        /// <ul>
        /// <li>
        /// 0: The protocol is stream-oriented and hence the concept of message size is not relevant.
        /// </li>
        /// <li>
        /// 1: The maximum outbound (send) message size is dependent on the underlying network MTU 
        /// (maximum sized transmission unit) and hence cannot be known until after a socket is 
        /// bound. Applications should use Socket::MaxMessageSize( ) to retrieve the maximum outbound 
        /// message size after the socket has been bound to a local address.
        /// </li>
        /// <li>
        /// 0xFFFFFFFF: The protocol is message-oriented, but there is no maximum limit to the size 
        /// of messages that may be transmitted.
        /// </li>
        /// </ul>
        /// </summary>
        /// <returns>
        /// The maximum message size.
        /// </returns>
        constexpr DWORD MessageSize( ) const noexcept
        {
            return data_.dwMessageSize;
        }

        /// <summary>
        /// Reserved for use by service providers.
        /// </summary>
        constexpr DWORD ProviderReserved( ) const noexcept
        {
            return data_.dwProviderReserved;
        }

        /// <summary>
        /// The human-readable name identifying the protocol.
        /// </summary>
        /// <returns>
        /// The name of the protocol.
        /// </returns>
        const wchar_t* Protocol( ) const noexcept
        {
            return data_.szProtocol;
        }
    };





    /// <summary>
    /// Maintains information about a specific socket that specifies how 
    /// that socket should behave when data is queued to be sent and the 
    /// Socket::Close function is called on the socket.
    /// </summary>
    class Linger : public linger
    {
    public:
        using Base = linger;
        Linger( )
            : Base{}
        {
        }

        explicit Linger( bool linger, UInt16 seconds )
            : Base{ linger ? static_cast< UInt16>(1) : static_cast<UInt16>( 0 ), seconds }
        {
        }

        explicit Linger( bool linger, const TimeSpan& time )
            : Base{ linger ? static_cast<UInt16>( 1 ) : static_cast<UInt16>( 0 ), static_cast<UInt16>( time.TotalSeconds() ) }
        {
        }

        constexpr operator bool( ) const noexcept
        {
            return l_onoff != 0;
        }

        constexpr bool Enabled( ) const noexcept
        {
            return l_onoff != 0;
        }
        constexpr bool Disabled( ) const noexcept
        {
            return l_onoff == 0;
        }
        constexpr UInt16 Seconds( ) const noexcept
        {
            return l_linger;
        }
        constexpr TimeSpan Time( ) const noexcept
        {
            return TimeSpan( static_cast<Int64>(l_linger)* TimeSpan::TicksPerSecond );
        }
    };

    using FlowSpec = FLOWSPEC;

    class QualityOfService : public QOS
    {
    public:
        using Base = QOS;

        constexpr QualityOfService( )
            : Base{}
        { }

    };


#define HCC_THROW_LAST_SOCKET_ERROR() Harlinn::Common::Core::IO::Sockets::Socket::ThrowLastSocketError( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ )
#define HCC_THROW_SOCKET_ERROR( error ) Harlinn::Common::Core::IO::Sockets::Socket::ThrowSocketError( error, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ )

    /// <summary>
    /// Represents a socket descriptor that is bound to a specific transport-service provider.
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    class Socket 
    {
        SOCKET socket_;
    public:
        HCC_EXPORT static void ThrowLastSocketError( );
        HCC_EXPORT static void ThrowLastSocketError( const wchar_t* function, const wchar_t* filename, int lineNumber );

        HCC_EXPORT static void ThrowSocketError( WinError error );
        HCC_EXPORT static void ThrowSocketError( WinError error, const wchar_t* function, const wchar_t* filename, int lineNumber );

        /// <summary>
        /// Returns the error code for the last Windows Sockets operation that failed.
        /// </summary>
        /// <returns></returns>
        static WinError LastSocketError( )
        {
            return std::bit_cast<WinError>( WSAGetLastError( ) );
        }
    public:
        using Flags = SocketFlags;
        /// <summary>
        /// Initializes a new Socket object that is not bound to a socket descriptor.
        /// </summary>
        Socket( )
            : socket_( INVALID_SOCKET )
        {
        }
    protected:
        Socket( SOCKET socket )
            : socket_( socket )
        {
        }
    public:
        /// <summary>
        /// Initializes a new Socket object that is bound to a specific transport service provider.
        /// </summary>
        /// <param name="addressFamily">
        /// The address family specification. 
        /// </param>
        /// <param name="socketType">
        /// The type specification for the new socket.
        /// </param>
        /// <param name="protocolType">
        /// The protocol to be used. The possible options for the protocol parameter are specific 
        /// to the address family and socket type specified.
        /// </param>
        Socket( AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType )
            : socket_( INVALID_SOCKET )
        {
            auto sckt = ::socket( static_cast<int>( addressFamily ), static_cast<int>( socketType ), static_cast<int>( protocolType ) );
            if ( sckt == INVALID_SOCKET )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            socket_ = sckt;
        }


        /// <summary>
        /// Initializes a new Socket object that is bound to a specific transport service provider.
        /// </summary>
        /// <param name="addressFamily">
        /// The address family specification
        /// </param>
        /// <param name="socketType">
        /// The type specification for the new socket.
        /// </param>
        /// <param name="protocolType">
        /// The protocol to be used. The possible options for the protocol parameter are specific to 
        /// the address family and socket type specified. 
        /// </param>
        /// <param name="protocolInfo">
        /// A reference to a ProtocolInfo object that defines the characteristics of the socket to be created.
        /// </param>
        /// <param name="group">
        /// <p>
        /// An existing socket group ID or an appropriate action to take when creating a new socket and a new socket group.
        /// </p>
        /// <p>
        /// If <c>group</c> is an existing socket group ID, join the new socket to this socket group, 
        /// provided all the requirements set by this group are met.
        /// </p>
        /// <p>
        /// If <c>group</c> is not an existing socket group ID, then the following values are possible:
        /// </p>
        /// <table>
        /// <tr>
        /// <th>group</th>
        /// <th>Meaning</th>
        /// </tr>
        /// <tr>
        /// <td>
        /// 0
        /// </td>
        /// <td>
        /// No group operation is performed.
        /// </td>
        /// </tr>
        /// <tr>
        /// <td>
        /// SG_UNCONSTRAINED_GROUP 
        /// </td>
        /// <td>
        /// Create an unconstrained socket group and have the new socket be the first member. For an unconstrained 
        /// group, Winsock does not constrain all sockets in the socket group to have been created with the same 
        /// value for the type and protocol parameters.
        /// </td>
        /// </tr>
        /// <tr>
        /// <td>
        /// SG_CONSTRAINED_GROUP
        /// </td>
        /// <td>
        /// Create a constrained socket group and have the new socket be the first member. For a constrained socket 
        /// group, Winsock constrains all sockets in the socket group to have been created with the same value for 
        /// the type and protocol parameters. A constrained socket group may consist only of connection-oriented 
        /// sockets, and requires that connections on all grouped sockets be to the same address on the same host.
        /// </td>
        /// </tr>
        /// </table>
        /// </param>
        /// <param name="flags">
        /// A set of flags used to specify additional socket attributes.
        /// </param>
        Socket( AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType, const ProtocolInfo& protocolInfo, GROUP group, Flags flags )
            : socket_( INVALID_SOCKET )
        {
            auto sckt = WSASocketW( static_cast<int>( addressFamily ), static_cast<int>( socketType ), static_cast<int>( protocolType ), const_cast<LPWSAPROTOCOL_INFOW>(protocolInfo.data()), group, static_cast<UInt32>( flags ) );
            if ( sckt == INVALID_SOCKET )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            socket_ = sckt;
        }

        /// <summary>
        /// Initializes a new Socket object that is bound to a specific transport service provider.
        /// </summary>
        /// <param name="addressFamily">
        /// The address family specification
        /// </param>
        /// <param name="socketType">
        /// The type specification for the new socket.
        /// </param>
        /// <param name="protocolType">
        /// The protocol to be used. The possible options for the protocol parameter are specific to 
        /// the address family and socket type specified. 
        /// </param>
        /// <param name="flags">
        /// A set of flags used to specify additional socket attributes.
        /// </param>
        Socket( AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType, Flags flags )
            : socket_( INVALID_SOCKET )
        {
            auto sckt = WSASocketW( static_cast<int>( addressFamily ), static_cast<int>( socketType ), static_cast<int>( protocolType ), nullptr, 0, static_cast<UInt32>( flags ) );
            if ( sckt == INVALID_SOCKET )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            socket_ = sckt;
        }

        /// <summary>
        /// No copy constructor
        /// </summary>
        Socket( const Socket& other ) = delete;
        /// <summary>
        /// Initializes a new Socket object, taking ownership of the socket descriptor
        /// of the argument Socket object.
        /// </summary>
        /// <param name="other">
        /// The Socket that holds the socket descriptor that will be moved to the new Socket object.
        /// </param>
        Socket( Socket&& other ) noexcept
            : socket_( other.socket_ )
        { 
            other.socket_ = INVALID_SOCKET;
        }

        /// <summary>
        /// <p>
        /// The destructor for the Socket object.
        /// </p>
        /// <p>
        /// Will close the handle to the socket descriptor currently held by the object.
        /// </p>
        /// </summary>
        ~Socket( )
        {
            if ( socket_ != INVALID_SOCKET )
            {
                closesocket( socket_ );
            }
        }

    protected:
        [[nodiscard]]
        SOCKET Release( )
        {
            auto result = socket_;
            socket_ = INVALID_SOCKET;
            return result;
        }
    public:


        /// <summary>
        /// No copy assignment allowed.
        /// </summary>
        Socket& operator = ( const Socket& other ) = delete;

        /// <summary>
        /// Takes ownership of the socket descriptor of the argument Socket object.
        /// </summary>
        /// <param name="other">
        /// The Socket that holds the socket descriptor that will be moved to this Socket object.
        /// </param>
        /// <returns></returns>
        Socket& operator = ( Socket&& other ) noexcept
        {
            std::swap(socket_, other.socket_);
            return *this;
        }

        /// <summary>
        /// Closes the socket descriptor.
        /// </summary>
        void Close( ) noexcept
        {
            if ( socket_ != INVALID_SOCKET )
            {
                closesocket( socket_ );
                socket_ = INVALID_SOCKET;
            }
        }


        [[nodiscard]]
        WinError Open( AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType, LPWSAPROTOCOL_INFOW protocolInfo, GROUP group, Flags flags = Flags::None ) 
        {
            if ( socket_ == INVALID_SOCKET )
            {
                auto sckt = WSASocketW( static_cast<int>( addressFamily ), static_cast<int>( socketType ), static_cast<int>( protocolType ), protocolInfo, group, static_cast<UInt32>( flags ) );
                if ( sckt == INVALID_SOCKET )
                {
                    return LastSocketError( );
                }
                socket_ = sckt;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"This Socket object is already bound to a socket descriptor." );
            }
            return WinError::None;
        }


        /// <summary>
        /// Opens a new socket descriptor for the Socket object that is bound to a specific transport service provider.
        /// </summary>
        /// <param name="addressFamily">
        /// The address family specification
        /// </param>
        /// <param name="socketType">
        /// The type specification for the new socket.
        /// </param>
        /// <param name="protocolType">
        /// The protocol to be used. The possible options for the protocol parameter are specific to 
        /// the address family and socket type specified. 
        /// </param>
        /// <param name="flags">
        /// A set of flags used to specify additional socket attributes.
        /// </param>
        void Open( AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType, Flags flags = Flags::None )
        {
            if ( socket_ == INVALID_SOCKET )
            {
                auto sckt = WSASocketW( static_cast<int>( addressFamily ), static_cast<int>( socketType ), static_cast<int>( protocolType ), nullptr, 0, static_cast<UInt32>( flags ) );
                if ( sckt == INVALID_SOCKET )
                {
                    HCC_THROW_LAST_SOCKET_ERROR( );
                }
                socket_ = sckt;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"This Socket object is already bound to a socket descriptor." );
            }
        }


        /// <summary>
        /// Checks that the value for the socket handle/descriptor
        /// is not INVALID_SOCKET. 
        /// </summary>
        /// <returns>
        /// <c>true</c> if the value for the socket handle/descriptor
        /// is not INVALID_SOCKET, otherwise <c>false</c>.
        /// </returns>
        [[nodiscard]]
        constexpr explicit operator bool( ) const noexcept
        {
            return socket_ != INVALID_SOCKET;
        }

        /// <summary>
        /// Checks that the value for the socket handle/descriptor
        /// is not INVALID_SOCKET. 
        /// </summary>
        /// <returns>
        /// <c>true</c> if the value for the socket handle/descriptor
        /// is not INVALID_SOCKET, otherwise <c>false</c>.
        /// </returns>
        [[nodiscard]]
        constexpr bool IsValid( ) const noexcept
        {
            return socket_ != INVALID_SOCKET;
        }

        /// <summary>
        /// Retrieves the value for the socket handle/descriptor.
        /// </summary>
        /// <returns>
        /// The value for the socket handle/descriptor.
        /// </returns>
        [[nodiscard]]
        constexpr SOCKET Handle( ) const
        {
            return socket_;
        }

    protected:
        void ThrowIfSocketIsValid( const Socket& socket ) const
        {
            if ( socket.Handle( ) != INVALID_SOCKET )
            {
                HCC_THROW( InvalidOperationException, L"Socket instance must not hold a valid socket handle." );
            }
        }
    public:

        template<typename ConnectionSocketT>
            requires std::is_base_of_v<Sockets::Socket,ConnectionSocketT>
        [[nodiscard]]
        WinError Accept( sockaddr* address, int* addressLength, ConnectionSocketT& result ) const
        {
            ThrowIfSocketIsValid( result );
            auto sckt = ::accept( socket_, address, addressLength );
            if ( sckt != INVALID_SOCKET )
            {
                result.socket_ = sckt;
                return WinError::None;
            }
            else
            {
                return LastSocketError( );
            }
        }

        template<typename ConnectionSocketT>
            requires std::is_base_of_v<Sockets::Socket, ConnectionSocketT>
        [[nodiscard]]
        WinError Accept( Address& address, ConnectionSocketT& result ) const
        {
            int addressLength = static_cast<int>( Address::DataSize );
            auto rc = Accept( address.data(), &addressLength, result );
            if ( rc == WinError::None )
            {
                address.SetLength( addressLength );
                return WinError::None;
            }
            else
            {
                address.Reset( );
                return rc;
            }
        }

        template<typename ConnectionSocketT>
            requires std::is_base_of_v<Sockets::Socket, ConnectionSocketT>
        [[nodiscard]]
        WinError Accept( ConnectionSocketT& result ) const
        {
            return Accept( nullptr, nullptr, result );
        }

        /// <summary>
        /// Permits an incoming connection attempt on a socket.
        /// </summary>
        /// <param name="address">
        /// A reference to a Sockets::Address object that receives the address of the 
        /// connecting entity, as known to the communications layer. 
        /// </param>
        /// <returns>
        /// <p>
        /// If no error occurs, Accept returns a Socket object that is a descriptor for 
        /// the new socket. This descriptor is a handle for the socket on which the actual 
        /// connection is made.
        /// </p>
        /// <p>
        /// An invalid Socket object is returned if an incoming connection was indicated, 
        /// but was subsequently terminated by the remote peer prior to accepting the call.
        /// </p>
        /// </returns>
        [[nodiscard]]
        Socket Accept( Address& address ) const
        {
            int sizeofAddress = static_cast<int>(Address::DataSize);
            auto sckt = ::accept( socket_, (sockaddr*)&address, &sizeofAddress );
            if ( sckt == INVALID_SOCKET )
            {
                auto error = LastSocketError( );
                if ( error != WinError::WsaConnectionReset )
                {
                    HCC_THROW_LAST_SOCKET_ERROR( );
                }
                address.storage_.ss_family = static_cast<ADDRESS_FAMILY>( AddressFamily::Unknown );
                address.length_ = 0;
                return Socket( );
            }
            address.length_ = sizeofAddress;
            return Socket( sckt );
        }

    private:
        [[nodiscard]]
        Socket CheckAcceptResult( ) const
        {
            auto error = LastSocketError( );
            if ( error != WinError::WsaConnectionRefused && error != WinError::WsaConnectionReset && error != WinError::WsaInterrupted )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
            return Socket( );
        }
    public:
        /// <summary>
        /// Permits an incoming connection attempt on a socket.
        /// </summary>
        /// <returns>
        /// <p>
        /// If no error occurs, Accept returns a Socket object that is a descriptor for 
        /// the new socket. This descriptor is a handle for the socket on which the actual 
        /// connection is made.
        /// </p>
        /// <p>
        /// An invalid Socket object is returned if: 
        /// </p>
        /// <ul>
        /// <li>
        /// An incoming connection was indicated, but was subsequently terminated by 
        /// the remote peer prior to accepting the call.
        /// </li>
        /// <li>
        /// The listening socket is closed.
        /// </li>
        /// </ul>
        /// </returns>
        [[nodiscard]]
        Socket Accept( ) const
        {
            auto sckt = ::accept( socket_, nullptr, nullptr );
            if ( sckt == INVALID_SOCKET )
            {
                return CheckAcceptResult( );
            }
            return Socket( sckt );
        }

        [[nodiscard]]
        WinError Accept( LPCONDITIONPROC conditionFunction, ULONG_PTR callbackData, sockaddr* address, int* addressLength, Socket& result ) const
        {
            ThrowIfSocketIsValid( result );
            auto sckt = WSAAccept( socket_, address, addressLength, conditionFunction, callbackData );
            if ( sckt != INVALID_SOCKET )
            {
                result.socket_ = sckt;
                return WinError::None;
            }
            else
            {
                return LastSocketError( );
            }
        }
        [[nodiscard]]
        WinError Accept( LPCONDITIONPROC conditionFunction, ULONG_PTR callbackData, Address& address, Socket& result ) const
        {
            int addressLength = static_cast<int>( Address::DataSize );
            auto rc = Accept( conditionFunction, callbackData, address.data( ), &addressLength, result );
            if ( rc == WinError::None )
            {
                address.SetLength( addressLength );
                return WinError::None;
            }
            else
            {
                address.Reset( );
                return rc;
            }
        }


        /// <summary>
        /// Conditionally accepts a connection based on the return value of a 
        /// condition function, provides quality of service flow specifications, 
        /// and allows the transfer of connection data.
        /// </summary>
        /// <param name="conditionFunction">
        /// The address of an optional application-specified condition function 
        /// that will make an accept/reject decision based on the caller information 
        /// passed in as parameters, and optionally create or join a socket group by 
        /// assigning an appropriate value to the result parameter g of this function. 
        /// If this parameter is NULL, then no condition function is called.
        /// </param>
        /// <param name="callbackData">
        /// Callback data passed back to the application-specified condition function 
        /// as the value of the dwCallbackData parameter passed to the condition function. 
        /// This parameter is only applicable if the conditionFunction parameter is not 
        /// nullptr. This parameter is not interpreted by Windows Sockets.
        /// </param>
        /// <param name="addr">
        /// An optional pointer to an sockaddr structure that receives the address of the 
        /// connecting entity, as known to the communications layer. 
        /// </param>
        /// <param name="addrlen">
        /// An optional pointer to an integer that contains the length of the sockaddr 
        /// structure pointed to by the addr parameter, in bytes.
        /// </param>
        /// <returns>
        /// <p>
        /// If no error occurs, Accept returns a Socket object that is a descriptor for 
        /// the new socket. This descriptor is a handle for the socket on which the actual 
        /// connection is made.
        /// </p>
        /// <p>
        /// An invalid Socket object is returned if an incoming connection was indicated, 
        /// but was subsequently terminated by the remote peer prior to accepting the call,
        /// or if the connection was refused by the conditionFunction.
        /// </p>
        /// </returns>
        [[nodiscard]]
        Socket Accept( LPCONDITIONPROC conditionFunction, ULONG_PTR callbackData, sockaddr* addr = nullptr, int* addrlen = nullptr ) const
        {
            auto sckt = WSAAccept( socket_, addr, addrlen, conditionFunction, callbackData );
            if ( sckt == INVALID_SOCKET )
            {
                return CheckAcceptResult( );
            }
            return Socket( sckt );
        }
        [[nodiscard]]
        Socket Accept( LPCONDITIONPROC conditionFunction, ULONG_PTR callbackData, Address& address ) const
        {
            int addressLength = static_cast<int>( Address::DataSize );
            auto sckt = Accept( conditionFunction, callbackData, address.data( ), &addressLength );
            if ( sckt )
            {
                address.SetLength( addressLength );
            }
            else
            {
                address.Reset( );
            }
            return sckt;
        }


        [[nodiscard]]
        HCC_EXPORT static WinError RecvMsg(SOCKET s, LPWSAMSG msg, LPDWORD numberOfBytesRecvd, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine);
        [[nodiscard]]
        HCC_EXPORT static WinError SendMsg(SOCKET s, LPWSAMSG msg, DWORD flags, LPDWORD numberOfBytesSent, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine );
        [[nodiscard]]
        HCC_EXPORT static WinError Poll( LPWSAPOLLFD fdarray, ULONG nfds, INT timeout, Int32* result );
        [[nodiscard]]
        HCC_EXPORT static WinError TransmitFile( SOCKET hSocket, HANDLE hFile, DWORD numberOfBytesToWrite, DWORD numberOfBytesPerSend, LPOVERLAPPED overlapped, LPTRANSMIT_FILE_BUFFERS transmitBuffers, DWORD flags );
        [[nodiscard]]
        HCC_EXPORT static WinError TransmitPackets( SOCKET hSocket, LPTRANSMIT_PACKETS_ELEMENT packetArray, DWORD elementCount, DWORD sendSize, LPOVERLAPPED overlapped, DWORD flags );

        [[nodiscard]]
        HCC_EXPORT static WinError ConnectEx( SOCKET socket, const sockaddr* name, int namelen, PVOID sendBuffer, DWORD sendDataLength, LPDWORD bytesSent, OVERLAPPED* overlapped );
        [[nodiscard]]
        HCC_EXPORT static WinError AcceptEx( SOCKET socket, SOCKET acceptSocket, PVOID outputBuffer, DWORD receiveDataLength, DWORD localAddressLength, DWORD remoteAddressLength, DWORD* bytesReceived, OVERLAPPED* overlapped );
        [[nodiscard]]
        HCC_EXPORT static WinError GetAcceptExSockaddrs( SOCKET socket, const Byte* outputBuffer, DWORD receiveDataLength, DWORD localAddressLength, DWORD remoteAddressLength, struct sockaddr** LocalSockaddr, LPINT LocalSockaddrLength, struct sockaddr** RemoteSockaddr, LPINT RemoteSockaddrLength );
        [[nodiscard]]
        HCC_EXPORT static WinError DisconnectEx( SOCKET socket, OVERLAPPED* overlapped, bool reuse );

        [[nodiscard]]
        HCC_EXPORT WinError ConnectEx( const sockaddr* name, int namelen, PVOID sendBuffer, DWORD sendDataLength, LPDWORD bytesSent, OVERLAPPED* overlapped ) const;
        [[nodiscard]]
        HCC_EXPORT WinError AcceptEx( const Socket& acceptSocket, PVOID outputBuffer, DWORD receiveDataLength, DWORD localAddressLength, DWORD remoteAddressLength, DWORD* bytesReceived, OVERLAPPED* overlapped ) const;
        
        HCC_EXPORT void GetAcceptExSockaddrs( const Byte* outputBuffer, DWORD receiveDataLength, DWORD localAddressLength, DWORD remoteAddressLength, struct sockaddr** LocalSockaddr, LPINT LocalSockaddrLength, struct sockaddr** RemoteSockaddr, LPINT RemoteSockaddrLength ) const;

        [[nodiscard]]
        HCC_EXPORT WinError DisconnectEx( OVERLAPPED* overlapped, bool reuse ) const;

        [[nodiscard]]
        HCC_EXPORT WinError Disconnect( bool reuse = false ) const;


        /// <summary>
        /// Associates a local address with a socket
        /// </summary>
        /// <param name="addr">
        /// A pointer to a sockaddr structure of the local address to assign to the bound socket .
        /// </param>
        /// <param name="addrlen">
        /// The length, in bytes, of the value pointed to by the addr parameter.
        /// </param>
        /// <remarks>
        /// <p>
        /// The Bind function is required on an unconnected socket before subsequent 
        /// calls to the Listen function. It is normally used to bind to either 
        /// connection-oriented (stream) or connectionless (datagram) sockets. The 
        /// bind function may also be used to bind to a raw socket (the socket was 
        /// created by calling the socket function with the type parameter set to SocketType::Raw). 
        /// The bind function may also be used on an unconnected socket before subsequent 
        /// calls to any of the Connect functions before send operations.
        /// </p>
        /// <p>
        /// When a Socket is created it exists in a namespace (address family), but it has 
        /// no name assigned to it. Use the Bind function to establish the local association 
        /// of the socket by assigning a local name to an unnamed socket.
        /// </p>
        /// <p>
        /// A name consists of three parts when using the Internet address family:
        /// </p>
        /// <ul>
        /// <li>The address family.</li>
        /// <li>A host address.</li>
        /// <li>A port number that identifies the application.</li>
        /// </ul>
        /// <p>
        /// In Windows Sockets 2, the addr parameter is not strictly interpreted as a pointer 
        /// to a sockaddr structure. It is cast this way for Windows Sockets 1.1 compatibility. 
        /// Service providers are free to regard it as a pointer to a block of memory of size addrlen. 
        /// The first 2 bytes in this block (corresponding to the sa_family member of the sockaddr 
        /// structure, the sin_family member of the sockaddr_in structure, or the sin6_family member of 
        /// the sockaddr_in6 structure) must contain the address family that was used to create the socket. 
        /// Otherwise, an error WinError::WsaFault occurs.
        /// </p>
        /// <p>
        /// If an application does not care what local address is assigned, specify the constant value 
        /// INADDR_ANY for an IPv4 local address or the constant value in6addr_any for an IPv6 local 
        /// address in the sa_data member of the name parameter. This allows the underlying service 
        /// provider to use any appropriate network address, potentially simplifying application programming 
        /// in the presence of multihomed hosts (that is, hosts that have more than one network interface and 
        /// address).
        /// </p>
        /// <p>
        /// For TCP/IP, if the port is specified as zero, the service provider assigns a unique port to the 
        /// application from the dynamic client port range. On Windows Vista and later, the dynamic client 
        /// port range is a value between 49152 and 65535. This is a change from Windows Server 2003 and earlier 
        /// where the dynamic client port range was a value between 1025 and 5000. The maximum value for the 
        /// client dynamic port range can be changed by setting a value under the following registry key:
        /// </p>
        /// <p>
        /// <c>HKLM\SYSTEM\CurrentControlSet\Services\Tcpip\Parameters</c>
        /// </p>
        /// <p>
        /// The MaxUserPort registry value sets the value to use for the maximum value of the dynamic 
        /// client port range. You must restart the computer for this setting to take effect.
        /// </p>
        /// <p>
        /// On Windows Vista and later, the dynamic client port range can be viewed and changed using 
        /// netsh commands. The dynamic client port range can be set differently for UDP and TCP and also 
        /// for IPv4 and IPv6.
        /// </p>
        /// <p>
        /// The application can use Socket::Name( ) after calling Bind to learn the address and the 
        /// port that has been assigned to the socket. If the Internet address is equal to INADDR_ANY 
        /// or in6addr_any, Socket::Name( ) cannot necessarily supply the address until the socket is 
        /// connected, since several addresses can be valid if the host is multihomed. Binding to a 
        /// specific port number other than port 0 is discouraged for client applications, since there 
        /// is a danger of conflicting with another socket already using that port number on the local computer.
        /// </p>
        /// <p>
        /// For multicast operations, the preferred method is to call the bind function to associate a 
        /// socket with a local IP address and then join the multicast group. Although this order of 
        /// operations is not mandatory, it is strongly recommended. So a multicast application would 
        /// first select an IPv4 or IPv6 address on the local computer, the wildcard IPv4 address 
        /// (INADDR_ANY), or the wildcard IPv6 address (in6addr_any). The the multicast application 
        /// would then call the bind function with this address in the in the sa_data member of the 
        /// name parameter to associate the local IP address with the socket. If a wildcard address 
        /// was specified, then Windows will select the local IP address to use. After the Bind function 
        /// completes, an application would then join the multicast group of interest. For more information 
        /// on how to join a multicast group, see the section on Multicast Programming. This socket can 
        /// then be used to receive multicast packets from the multicast group using the Socket::Receive, 
        /// Socket::ReceiveFrom, or Socket::ReceiveMsg functions.
        /// </p>
        /// <p>
        /// The Bind function is not normally required for send operations to a multicast group. 
        /// The Socket::SendTo and Socket::SendMsg functions implicitly bind the socket to the 
        /// wildcard address if the socket is not already bound. The Bind function is required before 
        /// the use of the Socket::Send functions which do not perform an implicit bind and are 
        /// allowed only on connected sockets, which means the socket must have already been bound 
        /// for it to be connected. The Bind function might be used before send operations using 
        /// the Socket::SendTo and Socket::SendMsg functions if an application wanted to select a 
        /// specific local IP address on a local computer with multiple network interfaces and 
        /// local IP addresses. Otherwise an implicit bind to the wildcard address using the 
        /// Socket::SendTo and Socket::SendMsg functions might result in a different local IP 
        /// address being used for send operations.
        /// </p>
        /// </remarks>
        [[nodiscard]]
        WinError Bind( const sockaddr* addr, int addrlen ) const
        {
            auto rc = ::bind( socket_, addr, addrlen );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError Bind( const Address& address ) const
        {
            return Bind( address.data(), address.length() );
        }

        [[nodiscard]]
        WinError Bind( const wchar_t* address, UInt16 port ) const
        {
            Address addr( address, port );
            return Bind( addr );
        }
        [[nodiscard]]
        WinError Bind( UInt16 port ) const
        {
            Address addr( port );
            return Bind( addr );
        }

        /// <summary>
        /// The <c>Connect</c> function establishes a connection to a specified socket.
        /// </summary>
        /// <param name="name">
        /// A pointer to the sockaddr structure to which the connection should be established.
        /// </param>
        /// <param name="addrLength">
        /// The length, in bytes, of the sockaddr structure pointed to by the <c>addr</c> parameter.
        /// </param>
        /// <returns>
        /// <p>
        /// If the operation completes successfully, <c>Connect</c> returns <c>true</c>. 
        /// </p>
        /// <p>
        /// On a blocking socket, the return value indicates success or failure 
        /// of the connection attempt.
        /// </p>
        /// <p>
        /// With a nonblocking socket, the connection attempt cannot be completed 
        /// immediately. In this case, <c>Connect</c> will return <c>false</c>. In this 
        /// case, there are two possible scenarios:
        /// </p>
        /// <ul>
        /// <li>
        /// Use the <c>Socket::Select</c> function to determine the completion of the 
        /// connection request by checking to see if the socket is writable.
        /// </li>
        /// <li>
        /// Use the <c>Socket::EventSelect</c> to indicate interest in connection events, 
        /// and then wait for the event object to become signaled, indicating that 
        /// the connect operation is complete (successfully or not).
        /// </li>
        /// </ul>
        /// <p>
        /// Until the connection attempt completes on a nonblocking socket, all 
        /// subsequent calls to connect on the same socket will return <c>false</c>.
        /// </p>
        /// </returns>
        [[nodiscard]]
        WinError Connect( const sockaddr* addr, int addrLength ) const
        {
            auto rc = ::connect( socket_, addr, addrLength );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError Connect( const Address& address ) const
        {
            return Connect( address.data( ), address.length( ) );
        }

        /// <summary>
        /// Establishes a connection to another socket application, exchanges connect 
        /// data, and specifies required quality of service based on the specified 
        /// FLOWSPEC structure.
        /// </summary>
        /// <param name="addr">
        /// A pointer to a sockaddr structure that specifies the address to which to connect.
        /// </param>
        /// <param name="addrLength">
        /// The length, in bytes, of the sockaddr structure pointed to by the <c>addr</c> parameter.
        /// </param>
        /// <param name="callerData">
        /// A pointer to the user data that is to be transferred to the other socket during 
        /// connection establishment.
        /// </param>
        /// <param name="calleeData">
        /// A pointer to the user data that is to be transferred back from the other socket 
        /// during connection establishment.
        /// </param>
        /// <param name="SQOS">
        /// A pointer to the FLOWSPEC structures for socket s, one for each direction.
        /// </param>
        /// <param name="GQOS">
        /// Reserved for future use with socket groups. A pointer to the FLOWSPEC structures 
        /// for the socket group (if applicable). This parameter should be nullptr.
        /// </param>
        /// <returns>
        /// <p>
        /// If the operation completes successfully, <c>Connect</c> returns <c>true</c>. 
        /// </p>
        /// <p>
        /// On a blocking socket, the return value indicates success or failure 
        /// of the connection attempt.
        /// </p>
        /// <p>
        /// With a nonblocking socket, the connection attempt cannot be completed 
        /// immediately. In this case, <c>Connect</c> will return <c>false</c>. In this 
        /// case, there are two possible scenarios:
        /// </p>
        /// <ul>
        /// <li>
        /// Use the <c>Socket::Select</c> function to determine the completion of the 
        /// connection request by checking to see if the socket is writable.
        /// </li>
        /// <li>
        /// Use the <c>Socket::EventSelect</c> to indicate interest in connection events, 
        /// and then wait for the event object to become signaled, indicating that 
        /// the connect operation is complete (successfully or not).
        /// </li>
        /// </ul>
        /// <p>
        /// Until the connection attempt completes on a nonblocking socket, all 
        /// subsequent calls to connect on the same socket will return <c>false</c>.
        /// </p>
        /// </returns>
        /// <remarks>
        /// <p>
        /// <c>Connect</c> is used to create a connection to the specified destination, 
        /// and to perform a number of other ancillary operations that occur at connect time. 
        /// If the socket is unbound, unique values are assigned to the local association 
        /// by the system, and the socket is marked as bound.
        /// </p>
        /// <p>
        /// For connection-oriented sockets (for example, SocketType::Stream), an active 
        /// connection is initiated to the foreign host using <c>addr</c> (an address in 
        /// the namespace of the socket; for a detailed description, please see Bind). When 
        /// this call completes successfully, the socket is ready to send/receive data.
        /// </p>
        /// <p>
        /// For connection-oriented, nonblocking sockets, it is often not possible to complete 
        /// the connection immediately. In such cases, this function returns <c>false</c>. 
        /// However, the operation proceeds. When the success or failure outcome becomes known, 
        /// it may be reported in one of several ways depending on how the client registers for 
        /// notification. If the client uses select, success is reported in the <c>writefds</c> 
        /// set and failure is reported in the <c>exceptfds</c> set. If the client uses 
        /// <c>Socket::EventSelect</c>, the notification is announced with <c>EventFlags::Connect</c> 
        /// and the error code associated with the <c>EventFlags::Connect</c> indicates either 
        /// success or a specific reason for failure.
        /// </p>
        /// <p>
        /// For a connectionless socket (for example, type <c>SocketType::Dgram</c>), the operation performed 
        /// by <c>Connect</c> is merely to establish a default destination address so that the socket can be 
        /// used on subsequent connection-oriented send and receive operations (<c>Socket::Send</c> and <c>Socket::Receive</c>). 
        /// Any datagrams received from an address other than the destination address specified 
        /// will be discarded. If the entire name structure is all zeros (not just the address parameter 
        /// of the name structure), then the socket will be disconnected. Then, the default remote address will 
        /// be indeterminate, so Socket::Send and Socket::Receive calls will throw an exception. However, 
        /// <c>Socket::SendTo</c> and <c>Socket::ReceiveFrom</c> can still be used. The default destination can be 
        /// changed by simply calling <c>Connect</c> again, even if the socket is already connected. Any 
        /// datagrams queued for receipt are discarded if <c>addr</c> is different from the previous call to <c>Connect</c>.
        /// </p>
        /// <p>
        /// For connectionless sockets, <c>addr</c> can indicate any valid address, including a broadcast 
        /// address. However, to connect to a broadcast address, a socket must have <c>Socket::SetSocketOption(SOL_SOCKET, SO_BROADCAST,...)</c>, 
        /// or Socket::SetBroadcast, enabled. Otherwise, Connect will throw an exception for WinError::WsaAccess.
        /// </p>
        /// </remarks>
        [[nodiscard]]
        WinError Connect( const sockaddr* addr, int addrLength, WSABUF* callerData, WSABUF* calleeData, QOS* SQOS, QOS* GQOS = nullptr ) const
        {
            auto rc = WSAConnect( socket_, addr, addrLength, callerData, calleeData, SQOS, GQOS );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }
        [[nodiscard]]
        WinError Connect( const Address& address, WSABUF* callerData, WSABUF* calleeData, QOS* SQOS, QOS* GQOS = nullptr ) const
        {
            return Connect( address.data( ), address.length( ), callerData, calleeData, SQOS, GQOS );
        }
        /// <summary>
        /// <p>
        /// Establishes a connection to one out of a collection of possible endpoints 
        /// represented by a set of destination addresses (host names and ports). This 
        /// function takes all the destination addresses passed to it and all of the 
        /// local computer's source addresses, and tries connecting using all possible 
        /// address combinations before giving up.
        /// </p>
        /// <p>
        /// This function supports both IPv4and IPv6 addresses.
        /// </p>
        /// </summary>
        /// <param name="socketAddresses">
        /// A pointer to a SOCKET_ADDRESS_LIST structure that represents the possible 
        /// destination address and port pairs to connect to a peer. It is the application's 
        /// responsibility to fill in the port number in the each SOCKET_ADDRESS structure 
        /// in the SOCKET_ADDRESS_LIST.
        /// </param>
        /// <param name="localAddressLength">
        /// On input, a pointer to the size, in bytes, of the <c>localAddress</c> buffer provided 
        /// by the caller. On output, a pointer to the size, in bytes, of the SOCKADDR for 
        /// the local address stored in the <c>localAddress</c> buffer filled in by the system. 
        /// upon successful completion of the call.
        /// </param>
        /// <param name="localAddress">
        /// A pointer to the SOCKADDR structure that receives the local address of the connection. 
        /// The size of the parameter is exactly the size returned in <c>localAddressLength</c>. 
        /// This is the same information that would be returned by the <c>Socket::Name()</c> function. 
        /// This parameter can be nullptr, in which case, the <c>localAddressLength</c> parameter is ignored.
        /// </param>
        /// <param name="remoteAddressLength">
        /// On input, a pointer to the size, in bytes, of the <c>remoteAddress</c> buffer provided 
        /// by the caller. On output, a pointer to the size, in bytes, of the SOCKADDR for the remote 
        /// address stored in <c>remoteAddress</c> buffer filled-in by the system upon successful 
        /// completion of the call.
        /// </param>
        /// <param name="remoteAddress">
        /// A pointer to the SOCKADDR structure that receives the remote address of the connection. 
        /// This is the same information that would be returned by the <c>Socket::PeerName()</c> 
        /// function. This parameter can be nullptr, in which case, the <c>remoteAddressLength</c> is ignored.
        /// </param>
        /// <param name="timeout">
        /// The time, in milliseconds, to wait for a response from the remote application before aborting the 
        /// call. This parameter can be nullptr in which case Connect will complete after either the connection 
        /// is successfully established or after a connection was attempted and failed on all possible 
        /// local-remote address pairs.
        /// </param>
        /// <param name="reserved">
        /// Reserved for future implementation. This parameter must be set to <c>nullptr</c>.
        /// </param>
        /// <returns>
        /// <p>
        /// <c>true</c> if a connection was established, or <c>false</c> if the operation timed out or none of the specified hosts were reachable.
        /// </p>
        /// <p>
        /// Any other error will cause this function to throw an exception.
        /// </p>
        /// </returns>
        [[nodiscard]]
        WinError ConnectByList( SOCKET_ADDRESS_LIST* socketAddresses, DWORD* localAddressLength, SOCKADDR* localAddress, DWORD* remoteAddressLength, SOCKADDR* remoteAddress, const timeval* timeout = nullptr, OVERLAPPED* reserved = nullptr ) const
        {
            auto rc = WSAConnectByList( socket_, socketAddresses, localAddressLength, localAddress, remoteAddressLength, remoteAddress, timeout, reserved );
            if ( rc == FALSE )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError ConnectByList( SOCKET_ADDRESS_LIST* socketAddresses, Sockets::Address& localAddress, Sockets::Address& remoteAddress, const timeval* timeout = nullptr, OVERLAPPED* reserved = nullptr ) const
        {
            DWORD localAddressLength = static_cast<DWORD>( Sockets::Address::DataSize );
            DWORD remoteAddressLength = static_cast<DWORD>( Sockets::Address::DataSize );
            WinError result = ConnectByList( socketAddresses, &localAddressLength, localAddress.data( ), &remoteAddressLength, remoteAddress.data( ), timeout, reserved );
            if ( result == WinError::None )
            {
                localAddress.SetLength( static_cast<int>(localAddressLength) );
                remoteAddress.SetLength( static_cast<int>( remoteAddressLength ) );
            }
            else
            {
                localAddress.Reset( );
                remoteAddress.Reset( );
            }
            return result;
        }

        [[nodiscard]]
        WinError ConnectByName( LPWSTR nodeName, LPWSTR serviceName, DWORD* localAddressLength, SOCKADDR* localAddress, DWORD* remoteAddressLength, SOCKADDR* remoteAddress, const timeval* timeout = nullptr, OVERLAPPED* reserved = nullptr ) const
        {
            auto rc = WSAConnectByNameW( socket_, nodeName, serviceName, localAddressLength, localAddress, remoteAddressLength, remoteAddress, timeout, reserved );
            if ( rc == FALSE )
            {
                return LastSocketError( );
            } 
            return WinError::None;
        }

        [[nodiscard]]
        WinError ConnectByName( LPWSTR nodeName, LPWSTR serviceName, Sockets::Address& localAddress, Sockets::Address& remoteAddress, const timeval* timeout = nullptr, OVERLAPPED* reserved = nullptr ) const
        {
            DWORD localAddressLength = static_cast<DWORD>( Sockets::Address::DataSize );
            DWORD remoteAddressLength = static_cast<DWORD>( Sockets::Address::DataSize );
            WinError result = ConnectByName( nodeName, serviceName, &localAddressLength, localAddress.data( ), &remoteAddressLength, remoteAddress.data( ), timeout, reserved );
            if ( result == WinError::None )
            {
                localAddress.SetLength( static_cast<int>( localAddressLength ) );
                remoteAddress.SetLength( static_cast<int>( remoteAddressLength ) );
            }
            else
            {
                localAddress.Reset( );
                remoteAddress.Reset( );
            }
            return result;
        }

        [[nodiscard]]
        WinError Duplicate( DWORD processId, ProtocolInfo& protocolInfo ) const
        {
            auto rc = WSADuplicateSocketW( socket_, processId, protocolInfo.data( ) );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        /// <summary>
        /// Discovers occurrences of network events for the socket, clears 
        /// internal network event records, and, optionally, reset the event object.
        /// </summary>
        /// <param name="networkEvents">
        /// A pointer to a <c>WSANETWORKEVENTS</c> structure that is filled with a record 
        /// of network events that occurred and any associated error codes.
        /// </param>
        /// <param name="eventHandle">
        /// An optional handle identifying an associated event object to be reset.
        /// </param>
        /// <remarks>
        /// <p>
        /// The <c>EnumNetworkEvents</c> function is used to discover which network events 
        /// have occurred for the <c>Socket</c> since the last invocation of this function. 
        /// It is intended for use in conjunction with <c>Socket::EventSelect</c>, which 
        /// associates an event object with one or more network events. The recording of 
        /// network events commences when <c>Socket::EventSelect</c> is called with a  
        /// <c>networkEvents</c> parameter not equal to <c>EventFlags::None</c> and 
        /// remains in effect until another call is made to <c>Socket::EventSelect</c> 
        /// with the networkEvents parameter set to <c>EventFlags::None</c>.
        /// </p>
        /// <p>
        /// EnumNetworkEvents only reports network activity and errors nominated through 
        /// <c>Socket::EventSelect</c>.
        /// </p>
        /// <p>
        /// The socket's internal record of network events is copied to the structure 
        /// referenced by the <c>networkEvents</c> parameter, after which the internal 
        /// network events record is cleared. If the <c>eventHandle</c> parameter is 
        /// not 0, the indicated event object is also reset. The Windows Sockets provider 
        /// guarantees that the operations of copying the network event record, clearing it 
        /// and resetting any associated event object are atomic, such that the next occurrence 
        /// of a nominated network event will cause the event object to become set. 
        /// </p>
        /// <p>
        /// If this function throws an exception, then the associated event object is not 
        /// reset and the record of network events is not cleared.
        /// </p>
        /// 
        /// </remarks>
        [[nodiscard]]
        WinError EnumNetworkEvents( WSANETWORKEVENTS* networkEvents, HANDLE eventHandle = 0 ) const
        {
            auto rc = WSAEnumNetworkEvents( socket_, eventHandle, networkEvents );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError EventSelect( HANDLE eventHandle, EventFlags networkEvents ) const
        {
            auto rc = WSAEventSelect( socket_, eventHandle, static_cast<long>( networkEvents ) );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError Listen( int backlog = SOMAXCONN ) const
        {
            auto rc = ::listen( socket_, backlog );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }


        [[nodiscard]]
        WinError Shutdown( ShutdownFlag flag ) const
        {
            auto rc = ::shutdown( socket_, static_cast<int>( flag ) );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError JoinLeaf( const sockaddr* name, int namelen, WSABUF* callerData, WSABUF* calleeData, QOS* SQOS, QOS* GQOS, DWORD flags, Socket& result ) const
        {
            ThrowIfSocketIsValid( result );
            SOCKET soc = WSAJoinLeaf( socket_, name, namelen, callerData, calleeData, SQOS, GQOS, flags );
            if ( soc != INVALID_SOCKET )
            {
                result.socket_ = soc;
                return WinError::None;
            }
            else
            {
                return LastSocketError( );
            }
        }

        [[nodiscard]]
        Socket JoinLeaf( const sockaddr* name, int namelen, WSABUF* callerData, WSABUF* calleeData, QOS* SQOS, QOS* GQOS, DWORD flags ) const
        {
            SOCKET soc = WSAJoinLeaf( socket_, name, namelen, callerData, calleeData, SQOS, GQOS, flags );
            if ( soc == INVALID_SOCKET )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            return Socket( soc );
        }

        [[nodiscard]]
        WinError Ioctl( DWORD ioControlCode, void* inBuffer, DWORD inBufferSize, void* outBuffer, DWORD outBufferSize, DWORD* bytesReturned, OVERLAPPED* overlapped = nullptr, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine = nullptr ) const
        {
            auto rc = WSAIoctl( socket_, ioControlCode, inBuffer, inBufferSize, outBuffer, outBufferSize, bytesReturned, overlapped, completionRoutine );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError Ioctl( long cmd, u_long* argp ) const
        {
            auto rc = ioctlsocket( socket_, cmd, argp );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError PeerName( Sockets::Address& remoteAddress ) const
        {
            int dataSize = static_cast<int>( Sockets::Address::DataSize );
            auto rc = getpeername( socket_, remoteAddress.data( ), &dataSize );
            if ( rc != SOCKET_ERROR )
            {
                remoteAddress.SetLength( dataSize );
                return WinError::None;
            }
            else
            {
                remoteAddress.Reset( );
                return LastSocketError( );
            }
        }

        [[nodiscard]]
        Sockets::Address PeerName( ) const
        {
            Sockets::Address result;
            int dataSize = static_cast<int>( Sockets::Address::DataSize );
            auto rc = getpeername( socket_, result.data( ), &dataSize );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            result.SetLength( dataSize );
            return result;
        }


        [[nodiscard]]
        WinError Name( Sockets::Address& localAddress ) const
        {
            int dataSize = static_cast<int>( Sockets::Address::DataSize );
            auto rc = getsockname( socket_, localAddress.data( ), &dataSize );
            if ( rc != SOCKET_ERROR )
            {
                localAddress.SetLength( dataSize );
                return WinError::None;
            }
            else
            {
                localAddress.Reset( );
                return LastSocketError( );
            }
        }


        [[nodiscard]]
        Sockets::Address Name( ) const
        {
            Sockets::Address result;
            int dataSize = static_cast<int>( Sockets::Address::DataSize );
            auto rc = getsockname( socket_, result.data( ), &dataSize );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            result.SetLength( dataSize );
            return result;
        }

        [[nodiscard]]
        static WinError Select( int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const timeval* timeout, int* selectResult )
        {
            auto rc = select( nfds, readfds, writefds, exceptfds, timeout );
            if ( rc != SOCKET_ERROR )
            {
                *selectResult = rc;
                return WinError::None;
            }
            else
            {
                return LastSocketError( );
            }
        }

        [[nodiscard]]
        static int Select( int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const timeval* timeout = nullptr )
        {
            auto rc = select( nfds, readfds, writefds, exceptfds, timeout );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            return rc;
        }

        bool GetOverlappedResult( OVERLAPPED* overlapped, DWORD* numberOfBytesTransferred, bool wait, MessageFlags* flags ) const
        {
            auto rc = WSAGetOverlappedResult( socket_, overlapped, numberOfBytesTransferred, wait, reinterpret_cast<DWORD*>( flags ) );
            if ( !rc )
            {
                auto error = LastSocketError( );
                if ( error != WinError::IoIncomplete )
                {
                    HCC_THROW_SOCKET_ERROR( error );
                }
                return false;
            }
            return true;
        }

        /// <summary>
        /// Receives data from a connected socket or a bound connectionless socket.
        /// </summary>
        /// <param name="buffers">
        /// A pointer to an array of WSABUF structures. Each WSABUF structure contains 
        /// a pointer to a buffer and the length, in bytes, of the buffer.
        /// </param>
        /// <param name="bufferCount">
        /// The number of WSABUF structures in the <c>buffers</c> array.
        /// </param>
        /// <param name="numberOfBytesRecvd">
        /// <p>
        /// A pointer to the number, in bytes, of data received by this call if the 
        /// receive operation completes immediately.
        /// </p>
        /// <p>
        /// Use <c>nullptr</c> for this parameter if the <c>overlapped</c> parameter 
        /// is not <c>nullptr</c> to avoid potentially erroneous results. This parameter 
        /// can be <c>nullptr</c> only if the <c>overlapped</c> parameter is not <c>nullptr</c>.
        /// </p>
        /// </param>
        /// <param name="flags">
        /// A pointer to flags used to modify the behavior of the <c>Receive</c> function call.
        /// </param>
        /// <param name="overlapped">
        /// A pointer to an <c>OVERLAPPED</c> structure (ignored for non-overlapped sockets).
        /// </param>
        /// <param name="completionRoutine">
        /// A pointer to the completion routine called when the receive operation has been 
        /// completed (ignored for non-overlapped sockets).
        /// </param>
        /// <returns>
        /// <p>
        /// If no error occurs and the receive operation has completed immediately, <c>Receive</c> 
        /// returns <c>true</c>. In this case, the completion routine will have already been 
        /// scheduled to be called once the calling thread is in the alertable state.
        /// </p>
        /// <p>
        /// A return value of <c>false</c> indicates that the overlapped operation has 
        /// been successfully initiated and that completion will be indicated at a later time.
        /// </p>
        /// </returns>
        /// <remarks>
        /// <p>
        /// This overload of the <c>Receive</c> function provides some additional features 
        /// compared to the overloads implemented using the standard <c>recv</c> function 
        /// in three important areas:
        /// </p>
        /// <ul>
        /// <li>
        /// It can be used in conjunction with overlapped sockets to perform overlapped receive 
        /// operations.
        /// </li>
        /// <li>
        /// It allows multiple receive buffers to be specified making it applicable to the 
        /// scatter/gather type of I/O.
        /// </li>
        /// <li>
        /// The <c>flags</c> parameter is used both on input and returned on output, allowing 
        /// applications to sense the output state of the MessageFlags::Partial flag bit. The 
        /// MessageFlags::Partial flag is, however, not supported by all protocols.
        /// </li>
        /// </ul>
        /// <p>
        /// This overload works with connected sockets or bound connectionless sockets and 
        /// is used to read incoming data. The socket's local address must be known. For 
        /// server applications, this is usually done explicitly through <c>Socket::Bind</c> or implicitly 
        /// through <c>Socket::Accept</c>. Explicit binding is discouraged for client applications. For 
        /// client applications the socket can become bound implicitly to a local address through 
        /// <c>Socket::Connect</c>, <c>Socket::SendTo</c>, or <c>Socket::JoinLeaf</c>.
        /// </p>
        /// <p>
        /// For connected, connectionless sockets, this overload restricts the addresses from 
        /// which received messages are accepted. This overload only returns messages from the 
        /// remote address specified in the connection. Messages from other addresses are silently 
        /// discarded.
        /// </p>
        /// <p>
        /// For overlapped sockets, this overload is used to post one or more buffers into 
        /// which incoming data will be placed as it becomes available, after which the 
        /// application-specified completion indication (invocation of the completion 
        /// routine or setting of an event object) occurs. If the operation does not complete 
        /// immediately, the final completion status is retrieved through the completion routine,  
        /// or `Socket::GetOverlappedResult`.
        /// </p>
        /// <p>
        /// If both <c>overlapped</c> and <c>completionRoutine</c> are <c>nullptr</c>, the socket 
        /// will be treated as a non-overlapped socket.
        /// </p>
        /// <p>
        /// For non-overlapped sockets, the blocking semantics are identical to that of the 
        /// standard recv function and the <c>overlapped</c> and <c>completionRoutine</c> parameters 
        /// are ignored. Any data that has already been received and buffered by the transport will 
        /// be copied into the specified user buffers. In the case of a blocking socket with no data 
        /// currently having been received and buffered by the transport, the call will block until 
        /// data is received. Windows Sockets 2 does not define any standard blocking time-out mechanism 
        /// for this function. For protocols acting as byte-stream protocols the stack tries to return 
        /// as much data as possible subject to the available buffer space and amount of received data 
        /// available. However, receipt of a single byte is sufficient to unblock the caller. There is 
        /// no guarantee that more than a single byte will be returned. For protocols acting as 
        /// message-oriented, a full message is required to unblock the caller.
        /// </p>
        /// <p>
        /// Whether or not a protocol is acting as byte stream is determined by the setting 
        /// of <c>ServiceFlags1::MessageOriented</c> and <c>ServiceFlags1::PseudoStream</c> in 
        /// the value returned by <c>ProtocolInfo::ServiceFlags1( )</c> for the ProtocolInfo 
        /// object for this Socket and the setting of the MessageFlags::Partial flag passed in 
        /// to this overload for protocols that support it. The following table lists relevant 
        /// combinations, (an asterisk (*) indicates that the setting of this bit does not matter in this case).
        /// </p>
        /// <table>
        /// <tr>
        /// <th>ServiceFlags1::MessageOriented</th><th>ServiceFlags1::PseudoStream</th><th>MessageFlags::Partial</th><th>Act as</th>
        /// </tr>
        /// <tr>
        /// <td>not set</td><td>*</td><td>*</td><td>Byte stream</td>
        /// </tr>
        /// <tr>
        /// <td>*</td><td>Set</td><td>*</td><td>Byte stream</td>
        /// </tr>
        /// <tr>
        /// <td>Set</td><td>Not set</td><td>set</td><td>Byte stream</td>
        /// </tr>
        /// <tr>
        /// <td>set</td><td>Not set</td><td>Not set</td><td>Message oriented</td>
        /// </tr>
        /// </table>
        /// <p>
        /// The buffers are filled in the order in which they appear in the array pointed to 
        /// by <c>buffers</c>, and the buffers are packed so that no holes are created.
        /// </p>
        /// <p>
        /// If this function is completed in an overlapped manner, it is the Winsock service 
        /// provider's responsibility to capture the <c>WSABUF</c> structures before returning from 
        /// this call. This enables applications to build stack-based <c>WSABUF</c> arrays pointed to 
        /// by the <c>buffers</c> parameter.
        /// </p>
        /// <p>
        /// For byte stream-style sockets (for example, type <c>SocketType::Stream<c>), incoming data 
        /// is placed into the buffers until the buffers are filled, the connection is closed, 
        /// or the internally buffered data is exhausted. Regardless of whether or not the incoming 
        /// data fills all the buffers, the completion indication occurs for overlapped sockets.
        /// </p>
        /// <p>
        /// For message-oriented sockets (for example, type <c>SocketType::Dgram</c>), an incoming message 
        /// is placed into the buffers up to the total size of the buffers, and the completion 
        /// indication occurs for overlapped sockets. If the message is larger than the buffers, the 
        /// buffers are filled with the first part of the message. If the <c>MessageFlags::Partial</c> 
        /// feature is supported by the underlying service provider, the <c>MessageFlags::Partial</c> 
        /// flag is set in <c>flags</c> and subsequent receive operations will retrieve the rest of 
        /// the message. If <c>MessageFlags::Partial</c> is not supported but the protocol is 
        /// reliable, <c>Receive</c> throws an exception for <c>WinError::WsaMessageSize</c> and a subsequent 
        /// receive operation with a larger buffer can be used to retrieve the entire message. Otherwise, 
        /// (that is, the protocol is unreliable and does not support <c>MessageFlags::Partial</c>), the 
        /// excess data is lost, and <c>Receive</c> throws an exception for <c>WinError::WsaMessageSize</c>.
        /// </p>
        /// <p>
        /// For connection-oriented sockets, <c>Receive</c> can indicate the graceful termination of 
        /// the virtual circuit in one of two ways that depend on whether the socket is byte stream or 
        /// message oriented. For byte streams, zero bytes having been read (as indicated by a zero 
        /// return value to indicate success, and <c>numberOfBytesRecvd</c> value of zero) indicates 
        /// graceful closure and that no more bytes will ever be read. For message-oriented sockets, 
        /// where a zero byte message is often allowable, a failure with an error code of 
        /// WinError::WsaDisconnected is used to indicate graceful closure. In any case a return error code 
        /// of WinError::WsaConnectionReset indicates an abortive close has occurred.
        /// </p>
        /// </remarks>
        [[nodiscard]]
        WinError Receive( LPWSABUF buffers, DWORD bufferCount, LPDWORD numberOfBytesRecvd, MessageFlags* flags, OVERLAPPED* overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine ) const
        {
            auto rc = ::WSARecv( socket_, buffers, bufferCount, numberOfBytesRecvd, (LPDWORD)flags, overlapped, completionRoutine );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError();
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError Receive( LPWSABUF buffers, DWORD bufferCount, LPDWORD numberOfBytesRecvd, MessageFlags* flags ) const
        {
            auto rc = Receive( buffers, bufferCount, numberOfBytesRecvd, flags, nullptr, nullptr );
            return rc;
        }

        [[nodiscard]]
        WinError Receive( LPWSABUF buffers, DWORD bufferCount, OVERLAPPED* overlapped, MessageFlags flags = MessageFlags::None, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine = nullptr ) const
        {
            auto rc = Receive( buffers, bufferCount, nullptr, &flags, overlapped, completionRoutine );
            return rc;
        }

    private:
        long long CheckReceiveError( ) const
        {
            auto error = LastSocketError( );
            if ( error != WinError::WsaTimedout )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
            return 0;
        }
    public:
        
        WinError Receive( void* buffer, size_t numberOfBytesToRead, size_t* numberOfBytesReceived, MessageFlags flags ) const
        {
            int bufferSize = static_cast<int>( numberOfBytesToRead );
            auto received = ::recv( Handle( ), (char*)buffer, bufferSize, static_cast<int>( flags ) );
            if ( received != SOCKET_ERROR )
            {
                *numberOfBytesReceived = static_cast<size_t>( received );
                return WinError::None;
            }
            else
            {
                return LastSocketError( );
            }
        }

        /// <summary>
        /// The Receive function receives data from a connected socket or 
        /// a bound connectionless socket.
        /// </summary>
        /// <param name="buffer">
        /// A pointer to the buffer to receive the incoming data.
        /// </param>
        /// <param name="numberOfBytesToRead">
        /// The length, in bytes, of the buffer pointed to by the buf parameter.
        /// </param>
        /// <param name="flags">
        /// A set of flags that influences the behavior of this function. See 
        /// remarks below. See the Remarks section for details on the possible 
        /// value for this parameter.
        /// </param>
        /// <returns>
        /// If no error occurs, the function returns the number of bytes 
        /// received and the buffer pointed to by the <c>buffer</c> parameter 
        /// will contain the received data. If the connection has been gracefully 
        /// closed, or the operation timed out, the return value is zero.
        /// </returns>
        /// <remarks>
        /// <p>
        /// The <c>Receive</c> function is used to read incoming data on 
        /// connection-oriented sockets, or connectionless sockets. When using a 
        /// connection-oriented protocol, the sockets must be connected before 
        /// calling <c>Receive</c>. When using a connectionless protocol, the 
        /// sockets must be bound before calling <c>Receive</c>.
        /// </p>
        /// <p>
        /// The local address of the socket must be known. For server applications, 
        /// use an explicit bind function or an implicit Accept. Explicit binding is 
        /// discouraged for client applications. For client applications, the socket 
        /// can become bound implicitly to a local address using Connect, SendTo, or 
        /// JoinLeaf.
        /// </p>
        /// <p>
        /// For connected or connectionless sockets, the <c>Receive</c> function restricts 
        /// the addresses from which received messages are accepted. The function only 
        /// returns messages from the remote address specified in the connection. Messages 
        /// from other addresses are (silently) discarded.
        /// </p>
        /// <p>
        /// For connection-oriented sockets (SocketType::Stream for example), calling 
        /// <c>Receive</c> will return as much data as is currently available—up to the 
        /// size of the buffer specified. If the socket has been configured for in-line 
        /// reception of OOB data (socket option SO_OOBINLINE) and OOB data is yet unread, 
        /// only OOB data will be returned. The application can use the Ioctl functions 
        /// to determine whether any more OOB data remains to be read.
        /// </p>
        /// </remarks>
        [[nodiscard]]
        long long Receive( void* buffer, size_t numberOfBytesToRead, MessageFlags flags ) const
        {
            int bufferSize = static_cast<int>( numberOfBytesToRead );
            auto result = ::recv( Handle( ), (char*)buffer, bufferSize, static_cast<int>( flags ) );
            if ( result == SOCKET_ERROR )
            {
                return CheckReceiveError( );
            }
            return result;
        }

        [[nodiscard]]
        long long Receive( void* buffer, size_t numberOfBytesToRead ) const
        {
            size_t bytesReceived = 0;
            Byte* ptr = (Byte*)buffer;
            while ( bytesReceived < numberOfBytesToRead )
            {
                size_t count = static_cast<size_t>(Receive( ptr, numberOfBytesToRead - bytesReceived, MessageFlags::WaitAll ));
                if ( count )
                {
                    bytesReceived += count;
                    ptr += count;
                }
                else
                {
                    memset( ptr, 0, numberOfBytesToRead - bytesReceived );
                    break;
                }
            }
            return bytesReceived;
        }

        [[nodiscard]]
        long long Receive( void* buffer, size_t bufferSize, size_t minimumNumberOfBytesToRead ) const
        {
            int iBufferSize = static_cast<int>( bufferSize );
            int numberOfBytesToRead = static_cast<int>( minimumNumberOfBytesToRead );

            auto numberOfBytesRead = static_cast<size_t>( Receive( buffer, bufferSize, MessageFlags::None ) );
            if ( numberOfBytesRead < minimumNumberOfBytesToRead )
            {
                Byte* ptr = (Byte*)buffer;
                ptr += numberOfBytesRead;
                auto size = bufferSize - numberOfBytesRead;
                auto received = static_cast<size_t>( Receive( ptr, size, MessageFlags::WaitAll ) );
                return static_cast<Int64>( received + numberOfBytesRead );
            }
            return numberOfBytesRead;
        }

        [[nodiscard]]
        WinError ReceiveFrom( WSABUF* buffers, DWORD bufferCount, DWORD* numberOfBytesRecvd, MessageFlags* flags, sockaddr* fromAddress, int* fromAddressLength, OVERLAPPED* overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine ) const
        {
            auto result = WSARecvFrom( socket_, buffers, bufferCount, numberOfBytesRecvd, reinterpret_cast<DWORD*>( flags ), fromAddress, fromAddressLength, overlapped, completionRoutine );
            if ( result == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError ReceiveFrom( WSABUF* buffers, DWORD bufferCount, DWORD* numberOfBytesRecvd, MessageFlags* flags, sockaddr* fromAddress, int* fromAddressLength ) const
        {
            return ReceiveFrom( buffers, bufferCount, numberOfBytesRecvd, flags, fromAddress, fromAddressLength, nullptr, nullptr );
        }

        [[nodiscard]]
        WinError ReceiveFrom( WSABUF* buffers, DWORD bufferCount, DWORD* numberOfBytesRecvd, MessageFlags* flags, Address& fromAddress ) const
        {
            int fromAddressLength = static_cast<int>( Address::DataSize );
            auto rc = ReceiveFrom( buffers, bufferCount, numberOfBytesRecvd, flags, fromAddress.data( ), &fromAddressLength, nullptr, nullptr );
            if ( rc == WinError::None )
            {
                fromAddress.SetLength( fromAddressLength );
                return WinError::None;
            }
            else
            {
                fromAddress.Reset( );
                return rc;
            }
        }

        [[nodiscard]]
        WinError ReceiveFrom( WSABUF* buffers, DWORD bufferCount, OVERLAPPED* overlapped, MessageFlags* flags, sockaddr* fromAddress, int* fromAddressLength, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine = nullptr ) const
        {
            return ReceiveFrom( buffers, bufferCount, nullptr, flags, fromAddress, fromAddressLength, overlapped, completionRoutine );
        }

        [[nodiscard]]
        WinError ReceiveFrom( WSABUF* buffers, DWORD bufferCount, OVERLAPPED* overlapped, MessageFlags* flags, Address& fromAddress, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine = nullptr ) const
        {
            return ReceiveFrom( buffers, bufferCount, nullptr, flags, fromAddress.data(), &fromAddress.length_, overlapped, completionRoutine );
        }


        [[nodiscard]]
        WinError ReceiveFrom( void* buffer, size_t bufferSize, size_t* numberOfBytesRecvd, MessageFlags flags = MessageFlags::None, sockaddr* fromAddress = nullptr, int* fromAddressLength = nullptr ) const
        {
            auto result = recvfrom( socket_, (char*)buffer, static_cast<int>( bufferSize ), static_cast<int>( flags ), fromAddress, fromAddressLength );
            if ( result != SOCKET_ERROR )
            {
                *numberOfBytesRecvd = static_cast<size_t>( result );
                return WinError::None;
            }
            else
            {
                return LastSocketError( );
            }
        }

        [[nodiscard]]
        long long ReceiveFrom( void* buffer, size_t bufferSize, MessageFlags flags = MessageFlags::None, sockaddr* fromAddress = nullptr, int* fromAddressLength = nullptr ) const
        {
            auto result = recvfrom( socket_, (char*)buffer, static_cast<int>( bufferSize ), static_cast<int>( flags ), fromAddress, fromAddressLength );
            if ( result == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            return result;
        }
        [[nodiscard]]
        long long ReceiveFrom( void* buffer, size_t bufferSize, MessageFlags flags, Sockets::Address& from ) const
        {
            int dataSize = static_cast<int>( Sockets::Address::DataSize );
            auto result = ReceiveFrom( buffer, bufferSize, flags, from.data(), &dataSize );
            from.SetLength( dataSize );
            return result;
        }
        [[nodiscard]]
        long long ReceiveFrom( void* buffer, size_t bufferSize, Sockets::Address& from ) const
        {
            return ReceiveFrom( buffer, bufferSize, MessageFlags::None, from );
        }


        [[nodiscard]]
        long long Send( const void* buffer, size_t numberOfBytesToSend, MessageFlags flags ) const
        {
            auto rc = send( socket_, (const char*)buffer, static_cast<int>( numberOfBytesToSend ), static_cast<int>( flags ) );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            return rc;
        }

        [[nodiscard]]
        WinError Send( LPWSABUF buffers, DWORD bufferCount, LPDWORD numberOfBytesSent, MessageFlags flags, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine ) const
        {
            auto rc = ::WSASend( socket_, buffers, bufferCount, numberOfBytesSent, (DWORD)flags, overlapped, completionRoutine );
            if ( rc == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError Send( LPWSABUF buffers, DWORD bufferCount, LPDWORD numberOfBytesSent, MessageFlags flags = MessageFlags::None ) const
        {
            return Send( buffers, bufferCount, numberOfBytesSent, flags, nullptr, nullptr );
        }
        [[nodiscard]]
        WinError Send( LPWSABUF buffers, DWORD bufferCount, LPWSAOVERLAPPED overlapped, MessageFlags flags = MessageFlags::None, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine = nullptr ) const
        {
            return Send( buffers, bufferCount, nullptr, flags, overlapped, completionRoutine );
        }


        [[nodiscard]]
        long long SendTo( const void* buffer, size_t numberOfBytesToSend, MessageFlags flags = MessageFlags::None, const sockaddr* destinationAddress = nullptr, int destinationAddressSize = 0 ) const
        {
            auto rc = sendto( socket_, (const char*)buffer, static_cast<int>( numberOfBytesToSend ), static_cast<int>( flags ), destinationAddress, destinationAddressSize );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            return rc;
        }

        [[nodiscard]]
        long long SendTo( const void* buffer, size_t numberOfBytesToSend, MessageFlags flags, const Sockets::Address& destinationAddress ) const
        {
            return SendTo( buffer, numberOfBytesToSend, flags, destinationAddress.data(), destinationAddress.length() );
        }

        [[nodiscard]]
        long long SendTo( const void* buffer, size_t numberOfBytesToSend, const Sockets::Address& destinationAddress ) const
        {
            return SendTo( buffer, numberOfBytesToSend, MessageFlags::None, destinationAddress.data( ), destinationAddress.length( ) );
        }

        [[nodiscard]]
        WinError SendTo( WSABUF* buffers, DWORD bufferCount, DWORD* numberOfBytesSent, MessageFlags flags, const sockaddr* destinationAddress, int destinationAddressLength, OVERLAPPED* overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine ) const
        {
            auto result = WSASendTo( socket_, buffers, bufferCount, numberOfBytesSent, static_cast<DWORD>( flags ), destinationAddress, destinationAddressLength, overlapped, completionRoutine );
            if ( result == SOCKET_ERROR )
            {
                return LastSocketError( );
            }
            return WinError::None;
        }

        [[nodiscard]]
        WinError SendTo( WSABUF* buffers, DWORD bufferCount, DWORD* numberOfBytesSent, MessageFlags flags, const sockaddr* destinationAddress, int destinationAddressLength ) const
        {
            return SendTo( buffers, bufferCount, numberOfBytesSent, flags, destinationAddress, destinationAddressLength, nullptr, nullptr );
        }

        [[nodiscard]]
        WinError SendTo( WSABUF* buffers, DWORD bufferCount, OVERLAPPED* overlapped, MessageFlags flags, const sockaddr* destinationAddress, int destinationAddressLength, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine = nullptr ) const
        {
            return SendTo( buffers, bufferCount, nullptr, flags, destinationAddress, destinationAddressLength, overlapped, completionRoutine );
        }



        /// <summary>
        /// Sets a socket option.
        /// </summary>
        /// <param name="level">
        /// The level at which the option is defined (for example, SOL_SOCKET).
        /// </param>
        /// <param name="option">
        /// The socket option for which the value is to be set (for example, 
        /// SO_BROADCAST). The option parameter must be a socket option defined 
        /// within the specified level, or behavior is undefined.
        /// </param>
        /// <param name="optionData">
        /// A pointer to the buffer in which the value for the requested option 
        /// is specified.
        /// </param>
        /// <param name="optionDataLength">
        /// The size, in bytes, of the buffer pointed to by the optionData parameter.
        /// </param>
        void SetSocketOption( int level, int option, const void* optionData, int optionDataLength ) const
        {
            auto rc = ::setsockopt( socket_, level, option, (const char*)optionData, optionDataLength );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
        }

        /// <summary>
        /// Sets a socket option.
        /// </summary>
        /// <param name="level">
        /// The level at which the option is defined (for example, SOL_SOCKET).
        /// </param>
        /// <param name="option">
        /// The socket option for which the value is to be set (for example, 
        /// SO_BROADCAST). The option parameter must be a socket option defined 
        /// within the specified level, or behavior is undefined.
        /// </param>
        /// <param name="value">
        /// The value to set for the option.
        /// </param>
        void SetSocketOption( int level, int option, Int32 value ) const
        {
            SetSocketOption( level, option, &value, sizeof( value ) );
        }
        /// <summary>
        /// Sets a socket option.
        /// </summary>
        /// <param name="level">
        /// The level at which the option is defined (for example, SOL_SOCKET).
        /// </param>
        /// <param name="option">
        /// The socket option for which the value is to be set (for example, 
        /// SO_BROADCAST). The option parameter must be a socket option defined 
        /// within the specified level, or behavior is undefined.
        /// </param>
        /// <param name="value">
        /// The value to set for the option.
        /// </param>
        void SetSocketOption( int level, int option, UInt32 value ) const
        {
            SetSocketOption( level, option, &value, sizeof( value ) );
        }

        /// <summary>
        /// Retrieves a socket option.
        /// </summary>
        /// <param name="level">
        /// The level at which the option is defined. Example: SOL_SOCKET.
        /// </param>
        /// <param name="option">
        /// The socket option for which the value is to be retrieved. Example: SO_ACCEPTCONN. 
        /// The option value must be a socket option defined within the specified level, 
        /// or behavior is undefined.
        /// </param>
        /// <param name="optionData">
        /// A pointer to the buffer in which the value for the requested option is to be returned.
        /// </param>
        /// <param name="optionDataLength">
        /// A pointer to the size, in bytes, of the optionData buffer. If the function succeeds
        /// the pointed to value holds the number of bytes retrieved for the option.
        /// </param>
        void GetSocketOption( int level, int option, void* optionData, int* optionDataLength ) const
        {
            auto rc = ::getsockopt( socket_, level, option, (char*)optionData, optionDataLength );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
        }

        /// <summary>
        /// <p>
        /// Returns true if the socket is connected.
        /// </p>
        /// <p>
        /// This member function is only valid for connection-oriented protocols.
        /// </p>
        /// </summary>
        /// <returns>
        /// Returns true if the socket is connected, otherwise false.
        /// </returns>
        bool IsConnected( ) const
        {
            Int32 value = 0;
            int valueLength = sizeof( Int32 );
            auto rc = ::getsockopt( socket_, SOL_SOCKET, SO_CONNECT_TIME, (char*)&value, &valueLength );
            return rc != SOCKET_ERROR;
        }

        /// <summary>
        /// This function is used with the AcceptEx function. This option updates the 
        /// properties of the socket which are inherited from the listening socket. This 
        /// function should be called if the PeerName, Name, GetSocketOption, or SetSocketOption 
        /// functions are to be used on the accepted socket.
        /// </summary>
        /// <param name="listenerSocketHandle">
        /// The listening Socket
        /// </param>
        /// <param name="acceptingSocketHandle">
        /// The Socket to update
        /// </param>
        static void UpdateAcceptContext( SOCKET listenerSocketHandle, SOCKET acceptingSocketHandle )
        {
            auto rc = setsockopt( acceptingSocketHandle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (const char*)&listenerSocketHandle, sizeof( listenerSocketHandle ) );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
        }

        /// <summary>
        /// This function is used with the AcceptEx function. This option updates the 
        /// properties of the socket which are inherited from the listening socket. This 
        /// function should be called if the PeerName, Name, GetSocketOption, or SetSocketOption 
        /// functions are to be used on the accepted socket.
        /// </summary>
        /// <param name="listenerSocketHandle">
        /// The listening Socket
        /// </param>
        void UpdateAcceptContext( const Socket& listenerSocket ) const
        {
            auto listenerSocketHandle = listenerSocket.Handle( );
            UpdateAcceptContext( listenerSocketHandle, socket_ );
        }




        Int32 GetInt32Option( int level, int option ) const
        {
            Int32 value = 0;
            int valueLength = sizeof( Int32 );
            GetSocketOption( level, option, &value, &valueLength );
            return value;
        }

        UInt32 GetUInt32Option( int level, int option ) const
        {
            UInt32 value = 0;
            int valueLength = sizeof( UInt32 );
            GetSocketOption( level, option, &value, &valueLength );
            return value;
        }

        /// <summary>
        /// <p>
        /// Returns whether the socket is in listening mode.
        /// </p>
        /// <p>
        /// This function is only Valid for connection-oriented protocols.
        /// </p>
        /// </summary>
        /// <returns>
        /// <c>true</c> if the socket is in listening mode, otherwise <c>false</c>.
        /// </returns>
        bool AcceptsConnections( ) const
        {
            return GetInt32Option( SOL_SOCKET, SO_ACCEPTCONN );
        }

        /// <summary>
        /// <p>
        /// Returns whether the socket is in listening mode.
        /// </p>
        /// <p>
        /// This function is only Valid for connection-oriented protocols.
        /// </p>
        /// </summary>
        /// <returns>
        /// <c>true</c> if the socket is in listening mode, otherwise <c>false</c>.
        /// </returns>
        bool IsListening( ) const
        {
            return AcceptsConnections( );
        }

        /// <summary>
        /// <p>
        /// Check if the socket is configured to broadcast data when sending.
        /// </p>
        /// <p>
        /// This function is only valid for protocols that support broadcasting 
        /// (IPX and UDP, for example).
        /// </p>
        /// </summary>
        /// <returns>
        /// <c>true</c> if the socket is configured to broadcast data, otherwise <c>false</c>.
        /// </returns>
        bool Broadcast( ) const
        {
            return GetInt32Option( SOL_SOCKET, SO_BROADCAST );
        }

        /// <summary>
        /// <p>
        /// Configure the socket to broadcast data when sending.
        /// </p>
        /// <p>
        /// This function is only valid for protocols that support broadcasting 
        /// (IPX and UDP, for example).
        /// </p>
        /// </summary>
        /// <param name="broadcast">
        /// <c>true</c> to turn broadcasting on, <c>false</c> to turn broadcasting off.
        /// </param>
        void SetBroadcast( bool broadcast = true ) const
        {
            SetSocketOption( SOL_SOCKET, SO_BROADCAST, broadcast );
        }


        // Indicates if incoming connections are to be accepted or rejected by 
        // the application, not by the protocol stack.

        /// <summary>
        /// Check if the socket is configured to pass incoming connect request to
        /// the application, or let the protocol stack handle the requests.
        /// </summary>
        /// <returns>
        /// <c>true</c> if the socket is configured to pass incoming connect request to
        /// the application, otherwise false.
        /// </returns>
        bool ConditionalAccept( ) const
        {
            return GetInt32Option( SOL_SOCKET, SO_CONDITIONAL_ACCEPT );
        }

        // Indicates if incoming connections are to be accepted or rejected by 
        // the application, not by the protocol stack.
        void SetConditionalAccept( bool conditionalAccept ) const
        {
            SetSocketOption( SOL_SOCKET, SO_CONDITIONAL_ACCEPT, conditionalAccept );
        }

        // Enable debug output.
        bool Debug( ) const
        {
            return GetInt32Option( SOL_SOCKET, SO_DEBUG );
        }

        // Enable debug output.
        void SetDebug( bool debug ) const
        {
            SetSocketOption( SOL_SOCKET, SO_DEBUG, debug );
        }

        // Returns the number of seconds the socket has been connected
        int ConnectTimeInSeconds( ) const
        {
            return GetInt32Option( SOL_SOCKET, SO_CONNECT_TIME );
        }

        TimeSpan ConnectTime( ) const
        {
            return TimeSpan(TimeSpan::TicksPerSecond * ConnectTimeInSeconds( ));
        }

        // If TRUE, SO_LINGER is disabled.
        bool DontLinger( ) const
        {
            return GetInt32Option( SOL_SOCKET, SO_DONTLINGER );
        }

        // If TRUE, SO_LINGER is disabled.
        void SetDontLinger( bool dontLinger ) const
        {
            SetSocketOption( SOL_SOCKET, SO_DONTLINGER, dontLinger );
        }

        Sockets::Linger Linger( ) const
        {
            Sockets::Linger linger{};
            int lingerSize = sizeof( Sockets::Linger );
            GetSocketOption( SOL_SOCKET, SO_LINGER, &linger, &lingerSize );
            return linger;
        }
        void SetLinger( const Sockets::Linger& linger ) const
        {
            int lingerSize = sizeof( Sockets::Linger );
            SetSocketOption( SOL_SOCKET, SO_LINGER, &linger, lingerSize );
        }
        void SetLinger( bool linger, UInt16 seconds ) const
        {
            Sockets::Linger lngr( linger, seconds );
            SetLinger( lngr );
        }



        // Returns the error status
        int ErrorCode() const
        {
            return GetInt32Option( SOL_SOCKET, SO_ERROR );
        }

        /// <summary>
        /// Sets the timeout, in milliseconds, for blocking receive calls.
        /// </summary>
        /// <param name="timeoutInMillis">the timeout value</param>
        void SetReceiveTimeout( UInt32 timeoutInMillis ) const
        {
            SetSocketOption( SOL_SOCKET, SO_RCVTIMEO, timeoutInMillis );
        }

        UInt32 ReceiveTimeout( ) const
        {
            return GetUInt32Option( SOL_SOCKET, SO_RCVTIMEO );
        }
        void SetSendTimeout( UInt32 timeoutInMillis ) const
        {
            SetSocketOption( SOL_SOCKET, SO_SNDTIMEO, timeoutInMillis );
        }
        UInt32 SendTimeout( ) const
        {
            return GetUInt32Option( SOL_SOCKET, SO_SNDTIMEO );
        }

        // sends keep-alive packets?
        bool KeepAlive( ) const
        {
            return GetInt32Option( SOL_SOCKET, SO_KEEPALIVE );
        }

        // Enables sending keep-alive packets for a socket connection
        void SetKeepAlive( bool keepAlive ) const
        {
            SetSocketOption( SOL_SOCKET, SO_KEEPALIVE, keepAlive );
        }

        void SetSendBufferSize( UInt32 sendBufferSize ) const
        {
            SetSocketOption( SOL_SOCKET, SO_SNDBUF, sendBufferSize );
        }
        UInt32 SendBufferSize( ) const
        {
            return GetUInt32Option( SOL_SOCKET, SO_SNDBUF );
        }
        void SetReceiveBufferSize( UInt32 receiveBufferSize ) const
        {
            SetSocketOption( SOL_SOCKET, SO_RCVBUF, receiveBufferSize );
        }
        UInt32 ReceiveBufferSize( ) const
        {
            return GetUInt32Option( SOL_SOCKET, SO_RCVBUF );
        }

        bool NoDelay( ) const
        {
            return GetInt32Option( SOL_SOCKET, TCP_NODELAY );
        }

        void SetNoDelay( bool noDelay ) const
        {
            SetSocketOption( SOL_SOCKET, TCP_NODELAY, noDelay );
        }

        /// <summary>
        /// Returns the maximum outbound message size for message-oriented 
        /// sockets supported by the protocol. Has no meaning for stream-oriented 
        /// sockets.
        /// </summary>
        /// <returns>
        /// The maximum outbound message size.
        /// </returns>
        UInt32 MaxMessageSize( ) const
        {
            return GetUInt32Option( SOL_SOCKET, SO_MAX_MSG_SIZE );
        }



        void GetProtocolInfo( WSAPROTOCOL_INFOW* info ) const
        {
            int infoSize = sizeof( sizeof( WSAPROTOCOL_INFOW ) );
            GetSocketOption( SOL_SOCKET, SO_PROTOCOL_INFO, info, &infoSize );
        }


        // Gets the amount of data pending in the network's input buffer that can be
        // read from the socket.
        size_t Available( ) const
        {
            u_long result = 0;
            auto rc = ioctlsocket( Handle( ), FIONREAD, &result );
            if ( rc == SOCKET_ERROR )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            return result;
        }

        
    };
    static_assert( sizeof( SOCKET ) == sizeof( Socket ) );

    

    /// <summary>
    /// Specializes a Socket for a particular SocketType and 
    /// a particular ProtocolType.
    /// </summary>
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


    /// <summary>
    /// Indicates the possible states of a Transmission Control Protocol (TCP) connection.
    /// </summary>
    enum class TcpState : Int32
    {
        /// <summary>
        /// The TCP connection has no connection state at all. 
        /// This state represents the state when there is no 
        /// Transmission Control Block (TCB), and therefore, no connection.
        /// </summary>
        Closed = TCPSTATE_CLOSED,
        /// <summary>
        /// The TCP connection is waiting for a connection request from any 
        /// remote TCPand port.
        /// </summary>
        Listen = TCPSTATE_LISTEN,
        /// <summary>
        /// The TCP connection is waiting for a matching connection request 
        /// after sending a connection request.
        /// </summary>
        SynSent = TCPSTATE_SYN_SENT,
        /// <summary>
        /// The TCP connection is waiting for an acknowledgment that confirms 
        /// the connection request after both receiving and sending a connection 
        /// request.
        /// </summary>
        SynRcvd = TCPSTATE_SYN_RCVD,
        /// <summary>
        /// The TCP connection is an open connection, so the data received can 
        /// be delivered to the user.This state is normal state for the data 
        /// transfer phase of the connection.
        /// </summary>
        Established = TCPSTATE_ESTABLISHED,
        /// <summary>
        /// The TCP connection is waiting for a request to end the connection 
        /// from the remote TCP, or an acknowledgment of the previously sent 
        /// request to end the connection.
        /// </summary>
        FinWait1 = TCPSTATE_FIN_WAIT_1,
        /// <summary>
        /// The TCP connection is waiting for a request to end the connection 
        /// from the remote TCP.
        /// </summary>
        FinWait2 = TCPSTATE_FIN_WAIT_2,
        /// <summary>
        /// The TCP connection is waiting for a request to end the connection 
        /// from the local user.
        /// </summary>
        CloseWait = TCPSTATE_CLOSE_WAIT,
        /// <summary>
        /// The TCP connection is waiting for an acknowledgment of the request 
        /// to end the connection from the remote TCP.
        /// </summary>
        Closing = TCPSTATE_CLOSING,
        /// <summary>
        /// The TCP connection is waiting for an acknowledgment of the request 
        /// to end the connection that was previously sent to the remote TCP, 
        /// which includes an acknowledgment of its request to end the connection.
        /// </summary>
        LastAck = TCPSTATE_LAST_ACK,
        /// <summary>
        /// The TCP connection is waiting for enough time to pass to be sure the 
        /// remote TCP received the acknowledgment of its request to end the 
        /// connection.
        /// </summary>
        TimeWait = TCPSTATE_TIME_WAIT,

        Max = TCPSTATE_MAX
    };

    class TcpInfo
    {
    private:
        TCP_INFO_v1 data_;
    public:
        TcpInfo()
            : data_{}
        { }
        TCP_INFO_v1* data( )
        {
            return &data_;
        }
        const TCP_INFO_v1* data( ) const
        {
            return &data_;
        }

        /// <summary>
        /// Returns the state of a Transmission Control Protocol connection.
        /// </summary>
        /// <returns>
        /// The state of a Transmission Control Protocol connection.
        /// </returns>
        constexpr Sockets::TcpState State( ) const noexcept
        {
            return static_cast<Sockets::TcpState>( data_.State );
        }

        /// <summary>
        /// Returns the current maximum segment size (MSS) for the connection, in bytes.
        /// </summary>
        /// <returns>
        /// The current maximum segment size (MSS) for the connection, in bytes.
        /// </returns>
        constexpr ULONG MaximumSegmentSize( ) const noexcept
        {
            return data_.Mss;
        }

        /// <summary>
        /// Returns the lifetime of the connection, in milliseconds.
        /// </summary>
        /// <returns>
        /// The lifetime of the connection, in milliseconds.
        /// </returns>
        constexpr ULONG64 ConnectionTimeInMilliseconds( ) const noexcept
        {
            return data_.ConnectionTimeMs;
        }

        /// <summary>
        /// Returns the lifetime of the connection.
        /// </summary>
        /// <returns>
        /// The lifetime of the connection.
        /// </returns>
        constexpr TimeSpan ConnectionTime( ) const noexcept
        {
            return TimeSpan(static_cast<Int64>(data_.ConnectionTimeMs * TimeSpan::TicksPerMillisecond) );
        }

        /// <summary>
        /// <c>true</c> if TCP time stamps are turned on for the connection; otherwise <c>false</c>.
        /// </summary>
        constexpr bool TimestampsEnabled( ) const noexcept
        {
            return data_.TimestampsEnabled != FALSE;
        }

        /// <summary>
        /// The current estimated round-trip time for the connection, in microseconds.
        /// </summary>
        constexpr UInt32 RoundtripTimeInMicroseconds( ) const noexcept
        {
            return data_.RttUs;
        }
        /// <summary>
        /// The current estimated round-trip time for the connection.
        /// </summary>
        constexpr TimeSpan RoundtripTime( ) const noexcept
        {
            return TimeSpan( static_cast<Int64>( data_.RttUs) * TimeSpan::TicksPerMicrosecond );
        }

        /// <summary>
        /// The minimum sampled round trip time, in microseconds.
        /// </summary>
        constexpr UInt32 MinRoundtripTimeInMicroseconds( ) const noexcept
        {
            return data_.MinRttUs;
        }

        /// <summary>
        /// The minimum sampled round trip time.
        /// </summary>
        constexpr TimeSpan MinRoundtripTime( ) const noexcept
        {
            return TimeSpan( static_cast<Int64>( data_.MinRttUs ) * TimeSpan::TicksPerMicrosecond );
        }

        /// <summary>
        /// The current number of sent bytes that are unacknowledged.
        /// </summary>
        constexpr UInt32 BytesInFlight( ) const noexcept
        {
            return data_.BytesInFlight;
        }

        /// <summary>
        /// The size of the current congestion window, in bytes.
        /// </summary>
        constexpr UInt32 CongestionWindowSize( ) const noexcept
        {
            return data_.Cwnd;
        }

        /// <summary>
        /// The size of the send window
        /// </summary>
        constexpr UInt32 SendWindowSize( ) const noexcept
        {
            return data_.SndWnd;
        }

        /// <summary>
        /// The size of the receive window
        /// </summary>
        constexpr UInt32 ReceiveWindowSize( ) const noexcept
        {
            return data_.RcvWnd;
        }

        /// <summary>
        /// The size of the current receive buffer, in bytes. The size of the 
        /// receive buffer changes dynamically when auto-tuning is turned on 
        /// for the receive window.
        /// </summary>
        constexpr UInt32 ReceiveBufferSize( ) const noexcept
        {
            return data_.RcvBuf;
        }

        /// <summary>
        /// The total number of bytes sent.
        /// </summary>
        constexpr UInt64 TotalBytesSent( ) const noexcept
        {
            return data_.BytesOut;
        }

        /// <summary>
        /// The total number of bytes received.
        /// </summary>
        constexpr UInt64 TotalBytesReceived( ) const noexcept
        {
            return data_.BytesIn;
        }

        /// <summary>
        /// The total number of bytes reordered.
        /// </summary>
        constexpr UInt32 TotalBytesReordered( ) const noexcept
        {
            return data_.BytesReordered;
        }

        /// <summary>
        /// The total number of bytes retransmitted.
        /// </summary>
        constexpr UInt32 TotalBytesRetransmitted( ) const noexcept
        {
            return data_.BytesRetrans;
        }

        /// <summary>
        /// The number of calls of the Fast Retransmit algorithm.
        /// </summary>
        constexpr UInt32 FastRetransmitCalls( ) const noexcept
        {
            return data_.FastRetrans;
        }

        /// <summary>
        /// The total number of duplicate acknowledgments received.
        /// </summary>
        constexpr UInt32 DuplicateAcknowledgmentsReceived( ) const noexcept
        {
            return data_.DupAcksIn;
        }

        /// <summary>
        /// The total number of retransmission timeout episodes. Each episode 
        /// can consist of multiple timeouts.
        /// </summary>
        constexpr UInt32 RetransmissionTimeoutEpisodes( ) const noexcept
        {
            return data_.TimeoutEpisodes;
        }

        /// <summary>
        /// The total number of retransmitted synchronize control flags (SYNs).
        /// </summary>
        constexpr Byte SynsRetransmitted( ) const noexcept
        {
            return data_.SynRetrans;
        }

        /// <summary>
        /// The number of transitions into the "Receiver Limited" state from 
        /// either the "Congestion Limited" or "Sender Limited" states.
        /// </summary>
        constexpr UInt32 SndLimTransRwin( ) const noexcept
        {
            return data_.SndLimTransRwin;
        }
        /// <summary>
        /// The cumulative time, in milliseconds, spent in the "Receiver Limited" 
        /// state where TCP transmission stops because the sender has filled the 
        /// announced receiver window.
        /// </summary>
        constexpr UInt32 SndLimTimeRwinInMilliseconds( ) const noexcept
        {
            return data_.SndLimTimeRwin;
        }
        
        /// <summary>
        /// The cumulative time spent in the "Receiver Limited" state where TCP 
        /// transmission stops because the sender has filled the announced receiver 
        /// window.
        /// </summary>
        constexpr TimeSpan SndLimTimeRwin( ) const noexcept
        {
            return TimeSpan( static_cast<Int64>( data_.SndLimTimeRwin ) * TimeSpan::TicksPerMillisecond );
        }

        /// <summary>
        /// The total number of bytes sent in the "Receiver Limited" state.
        /// </summary>
        constexpr UInt64 SndLimBytesRwin( ) const noexcept
        {
            return data_.SndLimBytesRwin;
        }

        /// <summary>
        /// The number of transitions into the "Congestion Limited" state 
        /// from either the "Receiver Limited" or "Sender Limited" states.
        /// </summary>
        constexpr UInt32 SndLimTransCwnd( ) const noexcept
        {
            return data_.SndLimTransCwnd;
        }

        /// <summary>
        /// The cumulative time, in milliseconds, spent in the "Congestion Limited" 
        /// state. When there is a retransmission timeout, it is counted in this 
        /// member and not the cumulative time for some other state.
        /// </summary>
        constexpr UInt32 SndLimTimeCwndInMilliseconds( ) const noexcept
        {
            return data_.SndLimTimeCwnd;
        }

        /// <summary>
        /// The cumulative time spent in the "Congestion Limited" state. When there 
        /// is a retransmission timeout, it is counted in this member and not the 
        /// cumulative time for some other state.
        /// </summary>
        constexpr TimeSpan SndLimTimeCwnd( ) const noexcept
        {
            return TimeSpan( static_cast<Int64>(data_.SndLimTimeCwnd)* TimeSpan::TicksPerMillisecond );
        }

        /// <summary>
        /// The total number of bytes sent in the "Congestion Limited" state.
        /// </summary>
        constexpr UInt64 SndLimBytesCwnd( ) const noexcept
        {
            return data_.SndLimBytesCwnd;
        }

        /// <summary>
        /// The number of transitions into the "Sender Limited" state from either 
        /// the "Receiver Limited" or "Congestion Limited" states.
        /// </summary>
        constexpr UInt32 SndLimTransSnd( ) const noexcept
        {
            return data_.SndLimTransSnd;
        }

        /// <summary>
        /// The cumulative time, in milliseconds, spent in the "Sender Limited" state.
        /// </summary>
        constexpr UInt32 SndLimTimeSndInMilliseconds( ) const noexcept
        {
            return data_.SndLimTimeSnd;
        }

        /// <summary>
        /// The cumulative time spent in the "Sender Limited" state.
        /// </summary>
        constexpr TimeSpan SndLimTimeSnd( ) const noexcept
        {
            return TimeSpan( static_cast<Int64>( data_.SndLimTimeSnd ) * TimeSpan::TicksPerMillisecond );
        }

        /// <summary>
        /// The total number of bytes sent in the "Sender Limited" state.
        /// </summary>
        constexpr UInt64 SndLimBytesSnd( ) const noexcept
        {
            return data_.SndLimBytesSnd;
        }
    };


    /// <summary>
    /// Encapsulates a TCP socket descriptor.
    /// </summary>
    class TcpSocket : public StreamSocket<ProtocolType::Tcp>
    {
    public:
        using Base = StreamSocket<ProtocolType::Tcp>;

        TcpSocket( )
            : Base( )
        { }
    protected:
        TcpSocket( SOCKET socket )
            : Base( socket )
        { }
    public:
        template< typename ... Args >
        TcpSocket( AddressFamily addressFamily, Args&&... args )
            : Base( addressFamily, std::forward<Args>( args )... )
        { }


        void GetTcpInfo( TcpInfo& tcpInfo ) const
        {
            DWORD version = 1;
            DWORD bytesReturned = 0;
            auto error = Ioctl( SIO_TCP_INFO, &version, sizeof( DWORD ), tcpInfo.data( ), sizeof( TCP_INFO_v1 ), &bytesReturned );
            if ( error != WinError::None )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
        }

        template<typename ...Args>
        void Bind( Args&&... args ) const
        {
            auto error = Base::Bind( std::forward<Args>(args)... );
            if ( error != WinError::None )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
        }

        void Listen( int backlog = SOMAXCONN ) const
        {
            auto error = Base::Listen( backlog );
            if ( error != WinError::None )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
        }

        template<typename ...Args>
        bool Connect( Args&&... args ) const
        {
            auto error = Base::Connect( std::forward<Args>( args )... );
            if ( error == WinError::WsaAlready || 
                error == WinError::WsaWouldBlock )
            {
                return false;
            }
            else if ( error != WinError::None && 
                error != WinError::WsaIsConnected )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
            return true;
        }

        template<typename ...Args>
        void ConnectByList( Args&&... args ) const
        {
            auto error = Base::ConnectByList( std::forward<Args>( args )... );
            if ( error != WinError::None )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
        }

        template<typename ...Args>
        void ConnectByName( Args&&... args ) const
        {
            auto error = Base::ConnectByName( std::forward<Args>( args )... );
            if ( error != WinError::None )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
        }

        [[nodiscard]]
        TcpSocket Accept(Sockets::Address& remoteAddress ) const
        {
            TcpSocket connectionSocket;
            WinError error = Base::Accept( remoteAddress, connectionSocket );
            if ( error != WinError::None )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
            return connectionSocket;
        }

        [[nodiscard]]
        TcpSocket Accept( ) const
        {
            TcpSocket connectionSocket;
            WinError error = Base::Accept( connectionSocket );
            if ( error != WinError::None &&
                error != WinError::WsaInterrupted )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
            return connectionSocket;
        }

        void Shutdown( ShutdownFlag flags )
        {
            WinError error = Base::Shutdown( flags );
            if ( error != WinError::None && error != WinError::WsaNotConnected )
            {
                HCC_THROW_SOCKET_ERROR( error );
            }
        }



    };


    class UdpSocket : public DatagramSocket<ProtocolType::UserDatagram>
    {
    public:
        using Base = DatagramSocket<ProtocolType::UserDatagram>;

        UdpSocket( )
            : Base( )
        {
        }
    protected:
        UdpSocket( SOCKET socket )
            : Base( socket )
        {
        }
    public:
        template< typename ... Args >
        UdpSocket( AddressFamily addressFamily, Args&&... args )
            : Base( addressFamily, std::forward<Args>( args )... )
        {
        }

    };
    

    template<ProtocolType protocolType>
    class SocketStream
    {
        const StreamSocket<protocolType>& socket_;
        mutable bool canRead_ = true;
    public:
        SocketStream( const StreamSocket<protocolType>& socket )
            : socket_( socket )
        { }
    protected:
        SOCKET Handle( ) const
        {
            return socket_.Handle( );
        }

        [[nodiscard]]
        long long Receive( void* buffer, size_t numberOfBytesToRead ) const
        {
            if ( canRead_ )
            {
                size_t bytesReceived = 0;
                Byte* ptr = (Byte*)buffer;
                while ( bytesReceived < numberOfBytesToRead )
                {
                    size_t count = static_cast<size_t>( socket_.Receive( ptr, numberOfBytesToRead - bytesReceived, MessageFlags::None ) );
                    if ( count )
                    {
                        bytesReceived += count;
                        ptr += count;
                    }
                    else
                    {
                        canRead_ = false;
                        memset( ptr, 0, numberOfBytesToRead - bytesReceived );
                        break;
                    }
                }
                return bytesReceived;
            }
            else
            {
                return 0;
            }
        }

    public:
        long long Read( void* buffer, size_t numberOfBytesToRead ) const
        {
            return Receive( buffer, numberOfBytesToRead );
        }
        long long Write( const void* buffer, size_t numberOfBytesToWrite ) const
        {
            const char* ptr = (const char*)buffer;
            int bytesWritten = 0;
            int bytesToWrite = static_cast<int>( numberOfBytesToWrite );
            int bufferSize = bytesToWrite;
            while ( bytesWritten < bytesToWrite )
            {
                auto result = ::send( Handle( ), ptr, bufferSize, 0 );
                if ( result == SOCKET_ERROR )
                {
                    HCC_THROW_LAST_SOCKET_ERROR( );
                }
                bytesWritten += result;
                ptr += result;
                bufferSize -= result;
            }
            return bytesWritten;
        }

    };

    using TcpSocketStream = SocketStream<ProtocolType::Tcp>;

    static_assert( IO::StreamReader<TcpSocketStream> );
    static_assert( IO::StreamWriter<TcpSocketStream> );
    static_assert( IO::StreamIO<TcpSocketStream> );




    enum class SocketRequestType
    {
        Unknown,
        Connect,
        Accept,
        Disconnect,
        Ioctl,
        Receive,
        ReceiveFrom,
        ReceiveMsg,
        Send,
        SendTo,
        SendMsg,
        TransmitFile,
        TransmitPackets
    };

    /// <summary>
    /// Base class for all asynchronous socket requests
    /// </summary>
    class SocketRequest : public IO::Request
    {
    public:
        using Base = IO::Request;
    private:
        SocketRequestType type_;
    protected:
        SocketRequest( SocketRequestType type )
            : Base(), type_( type )
        { }

        SocketRequest( SOCKET handle, SocketRequestType type )
            : Base( reinterpret_cast<HANDLE>( handle ) ), type_( type )
        { }
        constexpr SocketRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, SocketRequestType type ) noexcept
            : Base( reinterpret_cast<HANDLE>( handle ), manualResetEvent, ownsEvent ), type_( type )
        { }

        SocketRequest( const Socket& socket, SocketRequestType type )
            : SocketRequest( socket.Handle(), type )
        { }
        constexpr SocketRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, SocketRequestType type ) noexcept
            : SocketRequest( socket.Handle( ), manualResetEvent, ownsEvent, type )
        { }
    public:
        constexpr SocketRequestType Type( ) const noexcept
        {
            return type_;
        }

        using Base::SetHandle;
        void SetHandle( SOCKET s )
        {
            Base::SetHandle( std::bit_cast<HANDLE>( s ) );
        }

    };


    /// <summary>
    /// For use with SocketHandler::BeginAsyncConnect 
    /// </summary>
    class ConnectRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::Connect;
    private:
        Sockets::Address address_;
        const Byte* buffer_ = nullptr;
        UInt32 numberOfBytesToSend_ = 0;
    public:
        ConnectRequest( )
            : Base( RequestType )
        { }

        /// <summary>
        /// Initializes a new ConnectRequest object.
        /// </summary>
        /// <param name="handle">
        /// A descriptor that identifies an unconnected, previously bound socket.
        /// </param>
        /// <param name="address">
        /// The address to which to connect.
        /// </param>
        /// <param name="buffer">
        /// A pointer to the buffer to be transferred after a connection is established. 
        /// This parameter is optional. If the TCP_FASTOPEN option is enabled on handle 
        /// before BeginAsyncConnect is called, then some of this data may be sent during 
        /// connection establishment.
        /// </param>
        /// <param name="numberOfBytesToSend">
        /// The length, in bytes, of data pointed to by the buffer parameter. This parameter 
        /// is ignored when the buffer parameter is nullptr.
        /// </param>
        ConnectRequest( SOCKET handle, const Sockets::Address& address, const Byte* buffer = nullptr, UInt32 numberOfBytesToSend = 0 )
            : Base( handle, RequestType ), address_( address ), buffer_( buffer ), numberOfBytesToSend_( numberOfBytesToSend )
        {
        }

        /// <summary>
        /// Initializes a new ConnectRequest object.
        /// </summary>
        /// <param name="handle">
        /// A descriptor that identifies an unconnected, previously bound socket.
        /// </param>
        /// <param name="manualResetEvent">
        /// A handle to an event that will be set to a signaled state by the system 
        /// when the operation has completed.
        /// </param>
        /// <param name="ownsEvent">
        /// if set to true, the destructor will close the handle passed in manualResetEvent.
        /// </param>
        /// <param name="address">
        /// The address to which to connect.
        /// </param>
        /// <param name="buffer">
        /// A pointer to the buffer to be transferred after a connection is established. 
        /// This parameter is optional. If the TCP_FASTOPEN option is enabled on handle 
        /// before BeginAsyncConnect is called, then some of this data may be sent during 
        /// connection establishment.
        /// </param>
        /// <param name="numberOfBytesToSend">
        /// The length, in bytes, of data pointed to by the buffer parameter. This parameter 
        /// is ignored when the buffer parameter is nullptr.
        /// </param>
        constexpr ConnectRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, const Sockets::Address& address, const Byte* buffer = nullptr, UInt32 numberOfBytesToSend = 0) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), address_( address ), buffer_( buffer ), numberOfBytesToSend_( numberOfBytesToSend )
        {
        }
        /// <summary>
        /// Initializes a new ConnectRequest object.
        /// </summary>
        /// <param name="socket">
        /// Identifies an unconnected, previously bound socket.
        /// </param>
        /// <param name="address">
        /// The address to which to connect.
        /// </param>
        /// <param name="buffer">
        /// A pointer to the buffer to be transferred after a connection is established. 
        /// This parameter is optional. If the TCP_FASTOPEN option is enabled on handle 
        /// before BeginAsyncConnect is called, then some of this data may be sent during 
        /// connection establishment.
        /// </param>
        /// <param name="numberOfBytesToSend">
        /// The length, in bytes, of data pointed to by the buffer parameter. This parameter 
        /// is ignored when the buffer parameter is nullptr.
        /// </param>
        ConnectRequest( const Socket& socket, const Sockets::Address& address, const Byte* buffer = nullptr, UInt32 numberOfBytesToSend = 0)
            : Base( socket, RequestType ), address_( address ), buffer_( buffer ), numberOfBytesToSend_( numberOfBytesToSend )
        {
        }
        /// <summary>
        /// Initializes a new ConnectRequest object.
        /// </summary>
        /// <param name="socket">
        /// Identifies an unconnected, previously bound socket.
        /// </param>
        /// <param name="manualResetEvent">
        /// A handle to an event that will be set to a signaled state by the system 
        /// when the operation has completed.
        /// </param>
        /// <param name="ownsEvent">
        /// if set to true, the destructor will close the handle passed in manualResetEvent.
        /// </param>
        /// <param name="address">
        /// The address to which to connect.
        /// </param>
        /// <param name="buffer">
        /// A pointer to the buffer to be transferred after a connection is established. 
        /// This parameter is optional. If the TCP_FASTOPEN option is enabled on handle 
        /// before BeginAsyncConnect is called, then some of this data may be sent during 
        /// connection establishment.
        /// </param>
        /// <param name="numberOfBytesToSend">
        /// The length, in bytes, of data pointed to by the buffer parameter. This parameter 
        /// is ignored when the buffer parameter is nullptr.
        /// </param>
        constexpr ConnectRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, const Sockets::Address& address, const Byte* buffer = nullptr, UInt32 numberOfBytesToSend = 0) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), address_( address ), buffer_( buffer ), numberOfBytesToSend_( numberOfBytesToSend )
        {
        }

        /// <summary>
        /// Retrieves the address to which to connect.
        /// </summary>
        /// <returns>A reference to the address to which to connect.</returns>
        constexpr const Sockets::Address& Address( ) const noexcept
        {
            return address_;
        }

        /// <summary>
        /// Retrieves a pointer to the buffer to be transferred after a connection is established.
        /// </summary>
        /// <returns>
        /// A pointer to the buffer to be transferred after a connection is established.
        /// </returns>
        constexpr const Byte* Buffer( ) const noexcept
        {
            return buffer_;
        }
        /// <summary>
        /// Retrieves the length, in bytes, of data pointed to by the buffer parameter.
        /// </summary>
        /// <returns>
        /// The length, in bytes, of data pointed to by the buffer parameter.
        /// </returns>
        UInt32 NumberOfBytesToSend( ) const noexcept
        {
            return numberOfBytesToSend_;
        }
    };

    /// <summary>
    /// For use with SocketHandler::BeginAsyncAccept
    /// </summary>
    class AcceptRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::Accept;
        static constexpr UInt32 MaxLocalAddressLength = sizeof( SOCKADDR_STORAGE ) + 16;
        static constexpr UInt32 MaxRemoteAddressLength = sizeof( SOCKADDR_STORAGE ) + 16;
    private:
        SOCKET acceptSocket_ = INVALID_SOCKET;
        Byte* buffer_ = nullptr;
        UInt32 receiveDataLength_ = 0;
        UInt32 localAddressLength_ = 0;
        UInt32 remoteAddressLength_ = 0;
    public:
        /// <summary>
        /// Calculates the allocation size, in bytes, for the
        /// <c>buffer</c> parameter to the constructors of this class.
        /// This is required because this buffer will receive:
        /// <ol>
        /// <li>The first block of data received from the client.</li>
        /// <li>The remote addresses for the connection.</li>
        /// <li>The local addresses for the connection.</li>
        /// </ol>
        /// </summary>
        /// <param name="receiveDataLength">
        /// The expected number of bytes for the first block of 
        /// data received from the client.
        /// </param>
        /// <returns>
        /// The number of bytes that must be allocated for the
        /// <c>buffer</c> parameter to the constructors to be
        /// able to receive <c>receiveDataLength</c> number of bytes
        /// while processing the asynchronous request initiated
        /// by a call to BeginAsyncAccept.
        /// </returns>
        static constexpr UInt32 CalculateBufferSizeFor( UInt32 receiveDataLength )
        {
            return receiveDataLength + MaxLocalAddressLength + MaxRemoteAddressLength;
        }
        
        AcceptRequest( )
            : Base( RequestType )
        {
        }

        /// <summary>
        /// Initializes a new AcceptRequest object.
        /// </summary>
        /// <param name="listenSocket">
        /// A descriptor identifying a socket that has already 
        /// been called with the listen function. A server 
        /// application waits for attempts to connect on this socket.
        /// </param>
        /// <param name="acceptSocket">
        /// A descriptor identifying a socket on which to accept an 
        /// incoming connection. This socket must not be bound or 
        /// connected.
        /// </param>
        /// <param name="buffer">
        /// A pointer to a buffer that receives the first block of data 
        /// sent on a new connection, the local address of the server, 
        /// and the remote address of the client. The receive data is 
        /// written to the first part of the buffer starting at offset zero, 
        /// while the addresses are written to the latter part of the buffer. 
        /// This parameter must be specified.
        /// </param>
        /// <param name="receiveDataLength">
        /// The number of bytes in <c>buffer</c> that will be used for 
        /// actual receive data at the beginning of the buffer. This size 
        /// should not include the size of the local address of the server, 
        /// nor the remote address of the client; they are appended to the 
        /// output buffer. If <c>receiveDataLength</c> is zero, accepting 
        /// the connection will not result in a receive operation. Instead, 
        /// BeginAsyncAccept completes as soon as a connection arrives, 
        /// without waiting for any data.
        /// </param>
        /// <param name="localAddressLength">
        /// The number of bytes reserved for the local address information. This 
        /// value must be at least 16 bytes more than the maximum address length 
        /// for the transport protocol in use.
        /// </param>
        /// <param name="remoteAddressLength">
        /// The number of bytes reserved for the remote address information. This 
        /// value must be at least 16 bytes more than the maximum address length 
        /// for the transport protocol in use. Cannot be zero.
        /// </param>
        /// <remarks>
        /// The easiest way to get the size of the allocation for <c>buffer</c> right
        /// is to use the static <c>CalculateBufferSizeFor</c> function to calculate the
        /// required size. and then just accept the default values for <c>localAddressLength</c>
        /// and <c>remoteAddressLength</c>.
        /// </remarks>
        AcceptRequest( SOCKET listenSocket, SOCKET acceptSocket = INVALID_SOCKET, Byte* buffer = nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength )
            : Base( listenSocket, RequestType ),
              acceptSocket_( acceptSocket ), 
              buffer_( buffer ), 
              receiveDataLength_( receiveDataLength ), 
              localAddressLength_( localAddressLength ), 
              remoteAddressLength_( remoteAddressLength )
        { 
        }

        /// <summary>
        /// Initializes a new AcceptRequest object.
        /// </summary>
        /// <param name="listenSocket">
        /// A descriptor identifying a socket that has already 
        /// been called with the listen function. A server 
        /// application waits for attempts to connect on this socket.
        /// </param>
        /// <param name="manualResetEvent">
        /// A handle to an event that will be set to a signaled state by the system 
        /// when the operation has completed.
        /// </param>
        /// <param name="ownsEvent">
        /// if set to <c>true</c>, the destructor will close the handle passed in <c>manualResetEvent</c>.
        /// </param>
        /// <param name="acceptSocket">
        /// A descriptor identifying a socket on which to accept an 
        /// incoming connection. This socket must not be bound or 
        /// connected.
        /// </param>
        /// <param name="buffer">
        /// A pointer to a buffer that receives the first block of data 
        /// sent on a new connection, the local address of the server, 
        /// and the remote address of the client. The receive data is 
        /// written to the first part of the buffer starting at offset zero, 
        /// while the addresses are written to the latter part of the buffer. 
        /// This parameter must be specified.
        /// </param>
        /// <param name="receiveDataLength">
        /// The number of bytes in <c>buffer</c> that will be used for 
        /// actual receive data at the beginning of the buffer. This size 
        /// should not include the size of the local address of the server, 
        /// nor the remote address of the client; they are appended to the 
        /// output buffer. If <c>receiveDataLength</c> is zero, accepting 
        /// the connection will not result in a receive operation. Instead, 
        /// BeginAsyncAccept completes as soon as a connection arrives, 
        /// without waiting for any data.
        /// </param>
        /// <param name="localAddressLength">
        /// The number of bytes reserved for the local address information. This 
        /// value must be at least 16 bytes more than the maximum address length 
        /// for the transport protocol in use.
        /// </param>
        /// <param name="remoteAddressLength">
        /// The number of bytes reserved for the remote address information. This 
        /// value must be at least 16 bytes more than the maximum address length 
        /// for the transport protocol in use. Cannot be zero.
        /// </param>
        /// <remarks>
        /// The easiest way to get the size of the allocation for <c>buffer</c> right
        /// is to use the static <c>CalculateBufferSizeFor</c> function to calculate the
        /// required size. and then just accept the default values for <c>localAddressLength</c>
        /// and <c>remoteAddressLength</c>.
        /// </remarks>
        constexpr AcceptRequest( SOCKET listenSocket, HANDLE manualResetEvent, bool ownsEvent, SOCKET acceptSocket = INVALID_SOCKET, Byte* buffer = nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength ) noexcept
            : Base( listenSocket, manualResetEvent, ownsEvent, RequestType ),
              acceptSocket_( acceptSocket ), 
              buffer_( buffer ), 
              receiveDataLength_( receiveDataLength ), 
              localAddressLength_( localAddressLength ), 
              remoteAddressLength_( remoteAddressLength )
        { 
        }

        /// <summary>
        /// Initializes a new AcceptRequest object.
        /// </summary>
        /// <param name="listenSocket">
        /// A socket that has already been called with the listen function. 
        /// A server application waits for attempts to connect on this socket.
        /// </param>
        /// <param name="acceptSocket">
        /// A a socket on which to accept an incoming connection. 
        /// This socket must not be bound or connected.
        /// </param>
        /// <param name="buffer">
        /// A pointer to a buffer that receives the first block of data 
        /// sent on a new connection, the local address of the server, 
        /// and the remote address of the client. The receive data is 
        /// written to the first part of the buffer starting at offset zero, 
        /// while the addresses are written to the latter part of the buffer. 
        /// This parameter must be specified.
        /// </param>
        /// <param name="receiveDataLength">
        /// The number of bytes in <c>buffer</c> that will be used for 
        /// actual receive data at the beginning of the buffer. This size 
        /// should not include the size of the local address of the server, 
        /// nor the remote address of the client; they are appended to the 
        /// output buffer. If <c>receiveDataLength</c> is zero, accepting 
        /// the connection will not result in a receive operation. Instead, 
        /// BeginAsyncAccept completes as soon as a connection arrives, 
        /// without waiting for any data.
        /// </param>
        /// <param name="localAddressLength">
        /// The number of bytes reserved for the local address information. This 
        /// value must be at least 16 bytes more than the maximum address length 
        /// for the transport protocol in use.
        /// </param>
        /// <param name="remoteAddressLength">
        /// The number of bytes reserved for the remote address information. This 
        /// value must be at least 16 bytes more than the maximum address length 
        /// for the transport protocol in use. Cannot be zero.
        /// </param>
        /// <remarks>
        /// The easiest way to get the size of the allocation for <c>buffer</c> right
        /// is to use the static <c>CalculateBufferSizeFor</c> function to calculate the
        /// required size. and then just accept the default values for <c>localAddressLength</c>
        /// and <c>remoteAddressLength</c>.
        /// </remarks>
        AcceptRequest( const Socket& listenSocket, const Socket& acceptSocket, Byte* buffer = nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength )
            : Base( listenSocket, RequestType ),
              acceptSocket_( acceptSocket.Handle( ) ), buffer_( buffer ), receiveDataLength_( receiveDataLength ), localAddressLength_( localAddressLength ), remoteAddressLength_( remoteAddressLength )
        {
        }


        /// <summary>
        /// Initializes a new AcceptRequest object.
        /// </summary>
        /// <param name="listenSocket">
        /// A socket that has already been called with the listen function. 
        /// A server application waits for attempts to connect on this socket.
        /// </param>
        /// <param name="manualResetEvent">
        /// A handle to an event that will be set to a signaled state by the system 
        /// when the operation has completed.
        /// </param>
        /// <param name="ownsEvent">
        /// if set to <c>true</c>, the destructor will close the handle passed in <c>manualResetEvent</c>.
        /// </param>
        /// <param name="acceptSocket">
        /// A socket on which to accept an incoming connection. 
        /// This socket must not be bound or connected.
        /// </param>
        /// <param name="buffer">
        /// A pointer to a buffer that receives the first block of data 
        /// sent on a new connection, the local address of the server, 
        /// and the remote address of the client. The receive data is 
        /// written to the first part of the buffer starting at offset zero, 
        /// while the addresses are written to the latter part of the buffer. 
        /// This parameter must be specified.
        /// </param>
        /// <param name="receiveDataLength">
        /// The number of bytes in <c>buffer</c> that will be used for 
        /// actual receive data at the beginning of the buffer. This size 
        /// should not include the size of the local address of the server, 
        /// nor the remote address of the client; they are appended to the 
        /// output buffer. If <c>receiveDataLength</c> is zero, accepting 
        /// the connection will not result in a receive operation. Instead, 
        /// BeginAsyncAccept completes as soon as a connection arrives, 
        /// without waiting for any data.
        /// </param>
        /// <param name="localAddressLength">
        /// The number of bytes reserved for the local address information. This 
        /// value must be at least 16 bytes more than the maximum address length 
        /// for the transport protocol in use.
        /// </param>
        /// <param name="remoteAddressLength">
        /// The number of bytes reserved for the remote address information. This 
        /// value must be at least 16 bytes more than the maximum address length 
        /// for the transport protocol in use. Cannot be zero.
        /// </param>
        /// <remarks>
        /// The easiest way to get the size of the allocation for <c>buffer</c> right
        /// is to use the static <c>CalculateBufferSizeFor</c> function to calculate the
        /// required size. and then just accept the default values for <c>localAddressLength</c>
        /// and <c>remoteAddressLength</c>.
        /// </remarks>
        constexpr AcceptRequest( const Socket& listenSocket, HANDLE manualResetEvent, bool ownsEvent, const Socket& acceptSocket, Byte* buffer = nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength ) noexcept
            : Base( listenSocket, manualResetEvent, ownsEvent, RequestType ),
              acceptSocket_( acceptSocket.Handle( ) ), buffer_( static_cast<Byte*>( buffer ) ), receiveDataLength_( receiveDataLength ), localAddressLength_( localAddressLength ), remoteAddressLength_( remoteAddressLength )
        {
        }
        
    protected:
        void ResetMembers( SOCKET acceptSocket = INVALID_SOCKET, Byte* buffer = nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = 0, UInt32 remoteAddressLength = 0 )
        {
            acceptSocket_ = acceptSocket;
            buffer_ = buffer;
            receiveDataLength_ = receiveDataLength;
            localAddressLength_ = localAddressLength;
            remoteAddressLength_ = remoteAddressLength;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }

        void Reset( SOCKET listenSocket, SOCKET acceptSocket = INVALID_SOCKET, Byte* buffer = nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength )
        {
            Base::Reset( std::bit_cast<HANDLE>( listenSocket ) );
            ResetMembers( acceptSocket, buffer, receiveDataLength, localAddressLength, remoteAddressLength );
        }
        void Reset( SOCKET listenSocket, HANDLE manualResetEvent, bool ownsEvent, SOCKET acceptSocket = INVALID_SOCKET, Byte* buffer = nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength ) noexcept
        {
            Base::Reset( std::bit_cast<HANDLE>( listenSocket ), manualResetEvent, ownsEvent );
            ResetMembers( acceptSocket, buffer, receiveDataLength, localAddressLength, remoteAddressLength );
        }
        void Reset( const Socket& listenSocket, const Socket& acceptSocket, Byte* buffer = nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength )
        {
            Base::Reset( std::bit_cast<HANDLE>( listenSocket.Handle( ) ) );
            ResetMembers( acceptSocket.Handle( ), buffer, receiveDataLength, localAddressLength, remoteAddressLength );
        }
        void Reset( const Socket& listenSocket, HANDLE manualResetEvent, bool ownsEvent, const Socket& acceptSocket, Byte* buffer= nullptr, UInt32 receiveDataLength = 0, UInt32 localAddressLength = MaxLocalAddressLength, UInt32 remoteAddressLength = MaxRemoteAddressLength )
        {
            Base::Reset( std::bit_cast<HANDLE>( listenSocket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( acceptSocket.Handle( ), buffer, receiveDataLength, localAddressLength, remoteAddressLength );
        }

        
        constexpr SOCKET AcceptSocket( ) const noexcept
        {
            return acceptSocket_;
        }

        constexpr Byte* Buffer( ) const noexcept
        {
            return buffer_;
        }

        constexpr UInt32 NumberOfBytesToRead( ) const noexcept
        {
            return receiveDataLength_;
        }
        constexpr UInt32 LocalAddressLength( ) const noexcept
        {
            return localAddressLength_;
        }
        constexpr UInt32 RemoteAddressLength( ) const noexcept
        {
            return remoteAddressLength_;
        }

        void GetAddresses( Sockets::Address& localAddress, Sockets::Address& remoteAddress )
        {
            sockaddr* local = nullptr;
            int localLen = 0;
            sockaddr* remote = nullptr;
            int remoteLen = 0;

            GetAcceptExSockaddrs( buffer_, receiveDataLength_, localAddressLength_, remoteAddressLength_, &local, &localLen, &remote, &remoteLen );
            localAddress.Assign( local, localLen );
            remoteAddress.Assign( remote, remoteLen );
        }

    };

    /// <summary>
    /// For use with SocketHandler::BeginAsyncDisconnect
    /// </summary>
    class DisconnectRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::Disconnect;
    private:
        bool reuse_ = false;
    public:
        DisconnectRequest( )
            : Base( RequestType )
        {
        }

        /// <summary>
        /// Initializes a new DisconnectRequest object.
        /// </summary>
        /// <param name="handle">
        /// A handle to a connected, connection-oriented socket.
        /// </param>
        /// <param name="reuse">
        /// If set to <c>true</c> then this request prepares the socket handle to be reused. 
        /// When the request initiated by <c>BeginAsyncDisconnect</c> completes, the 
        /// socket handle can be passed to the constructor for a <c>ConnectRequest</c> 
        /// object, or as the <c>acceptSocket</c> parameter of a constructor for an 
        /// <c>AcceptRequest</c> object.
        /// </param>
        explicit DisconnectRequest( SOCKET handle, bool reuse = false )
            : Base( handle, RequestType ), reuse_( reuse )
        {
        }

        /// <summary>
        /// Initializes a new DisconnectRequest object.
        /// </summary>
        /// <param name="handle">
        /// A handle to a connected, connection-oriented socket.
        /// </param>
        /// <param name="manualResetEvent">
        /// A handle to an event that will be set to a signaled state by the system 
        /// when the operation has completed.
        /// </param>
        /// <param name="ownsEvent">
        /// If set to <c>true</c>, the destructor will close the handle passed in <c>manualResetEvent</c>.
        /// </param>
        /// <param name="reuse">
        /// If set to <c>true</c> then this request prepares the socket handle to be reused. 
        /// When the request initiated by <c>BeginAsyncDisconnect</c> completes, the 
        /// socket handle can be passed to the constructor for a <c>ConnectRequest</c> 
        /// object, or as the <c>acceptSocket</c> parameter of a constructor for an 
        /// <c>AcceptRequest</c> object.
        /// </param>
        constexpr DisconnectRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, bool reuse = false ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), reuse_( reuse )
        {
        }
        /// <summary>
        /// Initializes a new DisconnectRequest object.
        /// </summary>
        /// <param name="handle">
        /// A connected, connection-oriented socket.
        /// </param>
        /// <param name="reuse">
        /// If set to <c>true</c> then this request prepares the socket handle to be reused. 
        /// When the request initiated by <c>BeginAsyncDisconnect</c> completes, the 
        /// socket handle can be passed to the constructor for a <c>ConnectRequest</c> 
        /// object, or as the <c>acceptSocket</c> parameter of a constructor for an 
        /// <c>AcceptRequest</c> object.
        /// </param>
        DisconnectRequest( const Socket& socket, bool reuse = false )
            : Base( socket, RequestType ), reuse_( reuse )
        {
        }
        
        /// <summary>
        /// Initializes a new DisconnectRequest object.
        /// </summary>
        /// <param name="handle">
        /// A handle to a connected, connection-oriented socket.
        /// </param>
        /// <param name="manualResetEvent">
        /// A handle to an event that will be set to a signaled state by the system 
        /// when the operation has completed.
        /// </param>
        /// <param name="ownsEvent">
        /// If set to <c>true</c>, the destructor will close the handle passed in <c>manualResetEvent</c>.
        /// </param>
        /// <param name="reuse">
        /// If set to <c>true</c> then this request prepares the socket handle to be reused. 
        /// When the request initiated by <c>BeginAsyncDisconnect</c> completes, the 
        /// socket handle can be passed to the constructor for a <c>ConnectRequest</c> 
        /// object, or as the <c>acceptSocket</c> parameter of a constructor for an 
        /// <c>AcceptRequest</c> object.
        /// </param>
        constexpr DisconnectRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, bool reuse = false ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), reuse_( reuse )
        {
        }

    protected:
        void ResetMembers( bool reuse = false )
        {
            reuse_ = reuse;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }
        void Reset( SOCKET socket, bool reuse = false )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ) );
            ResetMembers( reuse );
        }
        void Reset( const Socket& socket, bool reuse = false )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ) );
            ResetMembers( reuse );
        }
        void Reset( SOCKET socket, HANDLE manualResetEvent, bool ownsEvent, bool reuse = false )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ), manualResetEvent, ownsEvent );
            ResetMembers( reuse );
        }
        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, bool reuse = false )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( reuse );
        }

        /// <summary>
        /// If set to <c>true</c> then this request prepares the socket handle to be reused. 
        /// When the request initiated by <c>BeginAsyncDisconnect</c> completes, the 
        /// socket handle can be passed to the constructor for a <c>ConnectRequest</c> 
        /// object, or as the <c>acceptSocket</c> parameter of a constructor for an 
        /// <c>AcceptRequest</c> object.
        /// </summary>
        /// <returns></returns>
        constexpr bool Reuse( ) const noexcept
        {
            return reuse_;
        }
    };


    /// <summary>
    /// For use with SocketHandler::BeginAsyncIoctl
    /// </summary>
    class IoctlRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::Ioctl;
    private:
        UInt32 ioControlCode_ = 0;
        const Byte* inBuffer_ = nullptr;
        UInt32 inBufferLength_ = 0;
        Byte* outBuffer_ = nullptr;
        UInt32 outBufferLength_ = 0;
    public:
        IoctlRequest( )
            : Base( RequestType )
        {
        }

        /// <summary>
        /// Initializes a new IoctlRequest object
        /// </summary>
        /// <param name="handle">
        /// A descriptor identifying a socket.
        /// </param>
        /// <param name="ioControlCode">
        /// The control code of operation to perform.
        /// </param>
        /// <param name="inBuffer">
        /// A pointer to the input buffer. This pointer must 
        /// remain valid until the asynchronous operation 
        /// completes.
        /// </param>
        /// <param name="inBufferLength">
        /// The size, in bytes, of the input buffer.
        /// </param>
        /// <param name="outBuffer">
        /// A pointer to the output buffer. This pointer must 
        /// remain valid until the asynchronous operation 
        /// completes.
        /// </param>
        /// <param name="outBufferLength">
        /// The size, in bytes, of the output buffer.
        /// </param>
        explicit IoctlRequest( SOCKET handle, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
            : Base( handle, RequestType ), ioControlCode_( ioControlCode ), inBuffer_( inBuffer ), inBufferLength_( inBufferLength ), outBuffer_( outBuffer ), outBufferLength_( outBufferLength )
        {
        }

        /// <summary>
        /// Initializes a new IoctlRequest object
        /// </summary>
        /// <param name="handle">
        /// A descriptor identifying a socket.
        /// </param>
        /// <param name="manualResetEvent">
        /// A handle to an event that will be set to a signaled state by the system 
        /// when the operation has completed.
        /// </param>
        /// <param name="ownsEvent">
        /// If set to <c>true</c>, the destructor will close the handle passed in <c>manualResetEvent</c>.
        /// </param>
        /// <param name="ioControlCode">
        /// The control code of operation to perform.
        /// </param>
        /// <param name="inBuffer">
        /// A pointer to the input buffer. This pointer must 
        /// remain valid until the asynchronous operation 
        /// completes.
        /// </param>
        /// <param name="inBufferLength">
        /// The size, in bytes, of the input buffer.
        /// </param>
        /// <param name="outBuffer">
        /// A pointer to the output buffer. This pointer must 
        /// remain valid until the asynchronous operation 
        /// completes.
        /// </param>
        /// <param name="outBufferLength">
        /// The size, in bytes, of the output buffer.
        /// </param>
        constexpr IoctlRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), ioControlCode_( ioControlCode ), inBuffer_( inBuffer ), inBufferLength_( inBufferLength ), outBuffer_( outBuffer ), outBufferLength_( outBufferLength )
        {
        }

        /// <summary>
        /// Initializes a new IoctlRequest object
        /// </summary>
        /// <param name="socket">
        /// The socket that will receive the ioctl request.
        /// </param>
        /// <param name="ioControlCode">
        /// The control code of operation to perform.
        /// </param>
        /// <param name="inBuffer">
        /// A pointer to the input buffer. This pointer must 
        /// remain valid until the asynchronous operation 
        /// completes.
        /// </param>
        /// <param name="inBufferLength">
        /// The size, in bytes, of the input buffer.
        /// </param>
        /// <param name="outBuffer">
        /// A pointer to the output buffer. This pointer must 
        /// remain valid until the asynchronous operation 
        /// completes.
        /// </param>
        /// <param name="outBufferLength">
        /// The size, in bytes, of the output buffer.
        /// </param>
        explicit IoctlRequest( const Socket& socket, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
            : Base( socket, RequestType ), ioControlCode_( ioControlCode ), inBuffer_( inBuffer ), inBufferLength_( inBufferLength ), outBuffer_( outBuffer ), outBufferLength_( outBufferLength )
        {
        }

        /// <summary>
        /// Initializes a new IoctlRequest object
        /// </summary>
        /// <param name="socket">
        /// The socket that will receive the ioctl request.
        /// </param>
        /// <param name="manualResetEvent">
        /// A handle to an event that will be set to a signaled state by the system 
        /// when the operation has completed.
        /// </param>
        /// <param name="ownsEvent">
        /// If set to <c>true</c>, the destructor will close the handle passed in <c>manualResetEvent</c>.
        /// </param>
        /// <param name="ioControlCode">
        /// The control code of operation to perform.
        /// </param>
        /// <param name="inBuffer">
        /// A pointer to the input buffer. This pointer must 
        /// remain valid until the asynchronous operation 
        /// completes.
        /// </param>
        /// <param name="inBufferLength">
        /// The size, in bytes, of the input buffer.
        /// </param>
        /// <param name="outBuffer">
        /// A pointer to the output buffer. This pointer must 
        /// remain valid until the asynchronous operation 
        /// completes.
        /// </param>
        /// <param name="outBufferLength">
        /// The size, in bytes, of the output buffer.
        /// </param>
        constexpr IoctlRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), ioControlCode_( ioControlCode ), inBuffer_( inBuffer ), inBufferLength_( inBufferLength ), outBuffer_( outBuffer ), outBufferLength_( outBufferLength )
        {
        }
    protected:
        void ResetMembers( UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
        {
            ioControlCode_ = ioControlCode;
            inBuffer_ = inBuffer; 
            inBufferLength_ = inBufferLength; 
            outBuffer_ = outBuffer; 
            outBufferLength_ = outBufferLength;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }

        void Reset( SOCKET handle, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
        {
            Base::Reset( std::bit_cast<HANDLE>( handle ) );
            ResetMembers( ioControlCode, inBuffer, inBufferLength, outBuffer, outBufferLength );
        }
        void Reset( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
        {
            Base::Reset( std::bit_cast<HANDLE>( handle ), manualResetEvent, ownsEvent );
            ResetMembers( ioControlCode, inBuffer, inBufferLength, outBuffer, outBufferLength );
        }
        void Reset( const Socket& socket, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ) );
            ResetMembers( ioControlCode, inBuffer, inBufferLength, outBuffer, outBufferLength );
        }
        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( ioControlCode, inBuffer, inBufferLength, outBuffer, outBufferLength );
        }


        /// <summary>
        /// Retrieves the control code of operation to perform.
        /// </summary>
        /// <returns>The control code of operation.</returns>
        constexpr UInt32 ControlCode( ) const noexcept
        {
            return ioControlCode_;
        }

        /// <summary>
        /// Retrieves the pointer to the input buffer. This pointer
        /// must remain valid until the asynchronous operation 
        /// completes.
        /// </summary>
        /// <returns>
        /// The pointer to the input buffer.
        /// </returns>
        constexpr const Byte* InBuffer( ) const noexcept
        {
            return inBuffer_;
        }

        /// <summary>
        /// Retrieves the size, in bytes, of the input buffer.
        /// </summary>
        /// <returns>
        /// The size, in bytes, of the input buffer.
        /// </returns>
        constexpr UInt32 InBufferLength( ) const noexcept
        {
            return inBufferLength_;
        }

        /// <summary>
        /// Retrieves the pointer to the output buffer. This pointer
        /// must remain valid until the asynchronous operation 
        /// completes.
        /// </summary>
        /// <returns>
        /// The pointer to the output buffer.
        /// </returns>
        constexpr Byte* OutBuffer( ) const noexcept
        {
            return outBuffer_;
        }
        /// <summary>
        /// Retrieves the size, in bytes, of the output buffer.
        /// </summary>
        /// <returns>
        /// The size, in bytes, of the output buffer.
        /// </returns>
        constexpr UInt32 OutBufferLength( ) const noexcept
        {
            return outBufferLength_;
        }

    };


    template<typename DerivedT>
    class SocketHandler;
    /// <summary>
    /// For use with SocketHandler::BeginAsyncReceive
    /// </summary>
    class ReceiveRequest : public SocketRequest
    {
        template<typename DerivedT>
        friend class SocketHandler;
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::Receive;
    private:
        WSABUF* buffers_ = nullptr;
        UInt32 bufferCount_ = 0;
        MessageFlags flags_ = MessageFlags::None;
    public:
        ReceiveRequest( )
            : Base( RequestType )
        {
        }

        /// <summary>
        /// Initializes a new ReceiveRequest object
        /// </summary>
        /// <param name="handle">
        /// </param>
        /// <param name="buffers">
        /// </param>
        /// <param name="bufferCount">
        /// </param>
        /// <param name="flags">
        /// 
        /// </param>
        ReceiveRequest( SOCKET handle, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
            : Base( handle, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        constexpr ReceiveRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent , WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }

        ReceiveRequest( const Socket& socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
            : Base( socket, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        constexpr ReceiveRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }

    protected:
        void ResetMembers( WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None ) noexcept
        {
            buffers_ = buffers;
            bufferCount_ = bufferCount;
            flags_ = flags;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }

        void Reset( SOCKET socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ) );
            ResetMembers( buffers, bufferCount, flags );
        }
        void Reset( SOCKET socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ), manualResetEvent, ownsEvent );
            ResetMembers( buffers, bufferCount, flags );
        }

        void Reset( const Socket& socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ) );
            ResetMembers( buffers, bufferCount, flags );
        }
        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( buffers, bufferCount, flags );
        }


        constexpr WSABUF* Buffers( ) const noexcept
        {
            return buffers_;
        }
        constexpr UInt32 BufferCount( ) const noexcept
        {
            return bufferCount_;
        }
        constexpr MessageFlags Flags( ) const noexcept
        {
            return flags_;
        }

        constexpr DWORD* FlagsPtr( ) const noexcept
        {
            return (DWORD*)&flags_;
        }

        /// <summary>
        /// Returns true if the connection was closed. 
        /// </summary>
        /// <returns>
        /// <c>true</c> if the connection was closed, otherwise <c>false</c>.
        /// </returns>
        constexpr bool ConnectionClosed( bool streamOrientedSocket ) const noexcept
        {
            if ( streamOrientedSocket )
            {
                return (( Status( ) == NO_ERROR ) && ( NumberOfBytesTransferred( ) == 0 )) || (Status( ) == WSAECONNRESET);
            }
            else
            {
                return (Status( ) == WSAEDISCON) || ( Status( ) == WSAECONNRESET );
            }
        }

        

    };

    class ReceiveFromRequest : public SocketRequest
    {
        template<typename DerivedT>
        friend class SocketHandler;
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::ReceiveFrom;
    private:
        WSABUF* buffers_ = nullptr;
        UInt32 bufferCount_ = 0;
        MessageFlags flags_ = MessageFlags::None;
        Sockets::Address address_;
    public:
        explicit ReceiveFromRequest( SOCKET handle )
            : Base( handle, RequestType )
        {
        }

        explicit ReceiveFromRequest( const Socket& socket )
            : Base( socket.Handle( ), RequestType )
        {
        }

        ReceiveFromRequest( SOCKET handle, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
            : Base( handle, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        constexpr ReceiveFromRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers, UInt32 bufferCount, MessageFlags flags ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        ReceiveFromRequest( const Socket& socket, WSABUF* buffers, UInt32 bufferCount, MessageFlags flags )
            : Base( socket, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        constexpr ReceiveFromRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers, UInt32 bufferCount, MessageFlags flags ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }

    protected:
        void ResetMembers( WSABUF* buffers = nullptr, UInt32 bufferCount = 1, MessageFlags flags = MessageFlags::None ) noexcept
        {
            buffers_ = buffers;
            bufferCount_ = bufferCount;
            flags_ = flags;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }

        void Reset( SOCKET socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 1, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ) );
            ResetMembers( buffers, bufferCount, flags );
        }
        void Reset( SOCKET socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 1, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ), manualResetEvent, ownsEvent );
            ResetMembers( buffers, bufferCount, flags );
        }

        void Reset( const Socket& socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 1, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ) );
            ResetMembers( buffers, bufferCount, flags );
        }
        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 1, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( buffers, bufferCount, flags );
        }

        constexpr WSABUF* Buffers( ) const noexcept
        {
            return buffers_;
        }
        constexpr UInt32 BufferCount( ) const noexcept
        {
            return bufferCount_;
        }
        constexpr MessageFlags Flags( ) const noexcept
        {
            return flags_;
        }

        constexpr DWORD* FlagsPtr( ) const noexcept
        {
            return (DWORD*)&flags_;
        }

        constexpr const Sockets::Address& Address( ) const noexcept
        {
            return address_;
        }
        constexpr Sockets::Address& Address( ) noexcept
        {
            return address_;
        }

    };

    class ReceiveMsgRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::ReceiveMsg;
    private:
        WSAMSG* msg_ = nullptr;
    public:
        explicit ReceiveMsgRequest( SOCKET handle )
            : Base( handle, RequestType )
        {
        }

        explicit ReceiveMsgRequest( const Socket& socket )
            : Base( socket.Handle( ), RequestType )
        {
        }

        ReceiveMsgRequest( SOCKET handle, WSAMSG* msg )
            : Base( handle, RequestType ), msg_( msg )
        {
        }
        constexpr ReceiveMsgRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, WSAMSG* msg ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), msg_( msg )
        {
        }
        ReceiveMsgRequest( const Socket& socket, WSAMSG* msg )
            : Base( socket, RequestType ), msg_( msg )
        {
        }
        constexpr ReceiveMsgRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSAMSG* msg ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), msg_( msg )
        {
        }

        
        constexpr void Assign( WSAMSG* msg ) noexcept
        {
            msg_ = msg;
        }
        

        constexpr WSAMSG* Msg( ) const noexcept
        {
            return msg_;
        }
        constexpr WSAMSG* Message( ) const noexcept
        {
            return msg_;
        }

    };

    class SendRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::Send;
    private:
        WSABUF* buffers_ = nullptr;
        UInt32 bufferCount_ = 0;
        MessageFlags flags_ = MessageFlags::None;
    public:
        explicit SendRequest( )
            : Base( RequestType )
        { }

        SendRequest( SOCKET handle, WSABUF* buffers = nullptr, UInt32 bufferCount= 0, MessageFlags flags = MessageFlags::None )
            : Base( handle, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        constexpr SendRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }

        SendRequest( const Socket& socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
            : Base( socket, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }
        constexpr SendRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags )
        {
        }

        
    protected:
        void ResetMembers( WSABUF* buffers = nullptr, UInt32 bufferCount = 1, MessageFlags flags = MessageFlags::None ) noexcept
        {
            buffers_ = buffers;
            bufferCount_ = bufferCount;
            flags_ = flags;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }

        void Reset( SOCKET socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ) );
            ResetMembers( buffers, bufferCount, flags );
        }
        void Reset( SOCKET socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ), manualResetEvent, ownsEvent );
            ResetMembers( buffers, bufferCount, flags );
        }

        void Reset( const Socket& socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ) );
            ResetMembers( buffers, bufferCount, flags );
        }

        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( buffers, bufferCount, flags );
        }


        constexpr WSABUF* Buffers( ) const noexcept
        {
            return buffers_;
        }
        constexpr UInt32 BufferCount( ) const noexcept
        {
            return bufferCount_;
        }
        constexpr MessageFlags Flags( ) const noexcept
        {
            return flags_;
        }
    };

    class SendToRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::SendTo;
    private:
        WSABUF* buffers_ = nullptr;
        UInt32 bufferCount_ = 0;
        MessageFlags flags_ = MessageFlags::None;
        Sockets::Address destinationAddress_;
    public:
        explicit SendToRequest( )
            : Base( RequestType )
        {
        }

        SendToRequest( SOCKET handle, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address() )
            : Base( handle, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags ), destinationAddress_( destinationAddress )
        {
        }
        constexpr SendToRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags ), destinationAddress_( destinationAddress )
        {
        }
        SendToRequest( const Socket& socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) )
            : Base( socket, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags ), destinationAddress_( destinationAddress )
        {
        }
        constexpr SendToRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), buffers_( buffers ), bufferCount_( bufferCount ), flags_( flags ), destinationAddress_( destinationAddress )
        {
        }

    protected:
        void ResetMembers( WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) ) noexcept
        {
            buffers_ = buffers;
            bufferCount_ = bufferCount;
            flags_ = flags;
            destinationAddress_ = destinationAddress;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }

        void Reset( SOCKET socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ) );
            ResetMembers( buffers, bufferCount, flags, destinationAddress );
        }
        void Reset( SOCKET socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket ), manualResetEvent, ownsEvent );
            ResetMembers( buffers, bufferCount, flags, destinationAddress );
        }

        void Reset( const Socket& socket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ) );
            ResetMembers( buffers, bufferCount, flags, destinationAddress );
        }
        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( buffers, bufferCount, flags, destinationAddress );
        }

        constexpr WSABUF* Buffers( ) const noexcept
        {
            return buffers_;
        }
        constexpr UInt32 BufferCount( ) const noexcept
        {
            return bufferCount_;
        }
        constexpr MessageFlags Flags( ) const noexcept
        {
            return flags_;
        }
        const Sockets::Address& DestinationAddress( ) const noexcept
        {
            return destinationAddress_;
        }

    };

    class SendMsgRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::SendMsg;
    private:
        WSAMSG* msg_ = nullptr;
        MessageFlags flags_ = MessageFlags::None;
    public:
        SendMsgRequest( )
            : Base( RequestType )
        {
        }

        SendMsgRequest( SOCKET handle, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None )
            : Base( handle, RequestType ), msg_( msg ), flags_( flags )
        {
        }
        constexpr SendMsgRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), msg_( msg ), flags_( flags )
        {
        }
        SendMsgRequest( const Socket& socket, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None )
            : Base( socket, RequestType ), msg_( msg ), flags_( flags )
        {
        }
        constexpr SendMsgRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), msg_( msg ), flags_( flags )
        {
        }

    protected:
        void ResetMembers( WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None ) noexcept
        {
            WSAMSG* msg_ = msg;
            MessageFlags flags_ = flags;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }


        void Reset( SOCKET handle, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( handle ) );
            ResetMembers( msg, flags );
        }
        void Reset( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None ) noexcept
        {
            Base::Reset( std::bit_cast<HANDLE>( handle ), manualResetEvent, ownsEvent );
            ResetMembers( msg, flags );
        }
        void Reset( const Socket& socket, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ) );
            ResetMembers( msg, flags );
        }
        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None ) noexcept
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( msg, flags );
        }


        constexpr MessageFlags Flags( ) const noexcept
        {
            return flags_;
        }

        constexpr WSAMSG* Msg( ) const noexcept
        {
            return msg_;
        }
        constexpr WSAMSG* Message( ) const noexcept
        {
            return msg_;
        }
    };

    class TransmitFileRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::TransmitFile;
    private:
        HANDLE hFile_ = INVALID_HANDLE_VALUE;
        UInt32 numberOfBytesToWrite_ = 0;
        UInt32 numberOfBytesPerSend_ = 0;
        TransmitFileBuffers* transmitBuffers_ = nullptr;
        TransmitFileFlags flags_ = TransmitFileFlags::None;
    public:
        TransmitFileRequest( )
            : Base( RequestType )
        {
        }

        explicit TransmitFileRequest( SOCKET handle, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None )
            : Base( handle, RequestType ), hFile_( hFile ), numberOfBytesToWrite_( numberOfBytesToWrite ), numberOfBytesPerSend_( numberOfBytesPerSend ), transmitBuffers_( transmitBuffers ), flags_( flags )
        {
        }
        constexpr explicit TransmitFileRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), hFile_( hFile ), numberOfBytesToWrite_( numberOfBytesToWrite ), numberOfBytesPerSend_( numberOfBytesPerSend ), transmitBuffers_( transmitBuffers ), flags_( flags )
        {
        }
        explicit TransmitFileRequest( const Socket& socket, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None )
            : Base( socket, RequestType ), hFile_( hFile ), numberOfBytesToWrite_( numberOfBytesToWrite ), numberOfBytesPerSend_( numberOfBytesPerSend ), transmitBuffers_( transmitBuffers ), flags_( flags )
        {
        }
        constexpr explicit TransmitFileRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), hFile_( hFile ), numberOfBytesToWrite_( numberOfBytesToWrite ), numberOfBytesPerSend_( numberOfBytesPerSend ), transmitBuffers_( transmitBuffers ), flags_( flags )
        {
        }

    protected:
        void ResetMembers( HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
        {
            hFile_ = hFile;
            numberOfBytesToWrite_ = numberOfBytesToWrite;
            numberOfBytesPerSend_ = numberOfBytesPerSend;
            transmitBuffers_ = transmitBuffers;
            flags_ = flags;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }

        void Reset( SOCKET handle, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( handle ) );
            ResetMembers( hFile, numberOfBytesToWrite, numberOfBytesPerSend, transmitBuffers, flags );
        }
        void Reset( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
        {
            Base::Reset( std::bit_cast<HANDLE>( handle ), manualResetEvent, ownsEvent );
            ResetMembers( hFile, numberOfBytesToWrite, numberOfBytesPerSend, transmitBuffers, flags );
        }
        void Reset( const Socket& socket, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ) );
            ResetMembers( hFile, numberOfBytesToWrite, numberOfBytesPerSend, transmitBuffers, flags );
        }
        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( hFile, numberOfBytesToWrite, numberOfBytesPerSend, transmitBuffers, flags );
        }



        constexpr HANDLE FileHandle( ) const noexcept
        {
            return hFile_;
        }
        constexpr UInt32 NumberOfBytesToWrite( ) const noexcept
        {
            return numberOfBytesToWrite_;
        }
        constexpr UInt32 NumberOfBytesPerSend( ) const noexcept
        {
            return numberOfBytesPerSend_;
        }
        constexpr TransmitFileBuffers* TransmitBuffers( ) const noexcept
        {
            return transmitBuffers_;
        }
        constexpr TransmitFileFlags Flags( ) const noexcept
        {
            return flags_;
        }

    };

    class TransmitPacketsRequest : public SocketRequest
    {
    public:
        using Base = SocketRequest;
        static constexpr SocketRequestType RequestType = SocketRequestType::TransmitPackets;
    private:
        TransmitPacketsElement* packetArray_ = nullptr;
        UInt32 packetArrayCount_ = 0;
        UInt32 sendSize_ = 0;
        TransmitFileFlags flags_ = TransmitFileFlags::None;
    public:
        TransmitPacketsRequest( )
            : Base( RequestType )
        {
        }

        TransmitPacketsRequest( SOCKET handle, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None )
            : Base( handle, RequestType ), packetArray_( packetArray ), packetArrayCount_( packetArrayCount ), sendSize_( sendSize ), flags_( flags )
        {
        }
        constexpr TransmitPacketsRequest( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), packetArray_( packetArray ), packetArrayCount_( packetArrayCount ), sendSize_( sendSize ), flags_( flags )
        {
        }
        TransmitPacketsRequest( const Socket& socket, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None )
            : Base( socket, RequestType ), packetArray_( packetArray ), packetArrayCount_( packetArrayCount ), sendSize_( sendSize ), flags_( flags )
        {
        }
        constexpr TransmitPacketsRequest( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
            : Base( socket, manualResetEvent, ownsEvent, RequestType ), packetArray_( packetArray ), packetArrayCount_( packetArrayCount ), sendSize_( sendSize ), flags_( flags )
        {
        }

    protected:
        void ResetMembers( TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
        {
            TransmitPacketsElement* packetArray_ = packetArray;
            UInt32 packetArrayCount_ = packetArrayCount;
            UInt32 sendSize_ = sendSize;
            TransmitFileFlags flags_ = flags;
        }
    public:
        void Reset( )
        {
            Base::Reset( );
            ResetMembers( );
        }

        void Reset( SOCKET handle, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( handle ) );
            ResetMembers( packetArray, packetArrayCount, sendSize, flags );
        }
        void Reset( SOCKET handle, HANDLE manualResetEvent, bool ownsEvent, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
        {
            Base::Reset( std::bit_cast<HANDLE>( handle ), manualResetEvent, ownsEvent );
            ResetMembers( packetArray, packetArrayCount, sendSize, flags );
        }
        void Reset( const Socket& socket, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None )
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle() ) );
            ResetMembers( packetArray, packetArrayCount, sendSize, flags );
        }
        void Reset( const Socket& socket, HANDLE manualResetEvent, bool ownsEvent, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None ) noexcept
        {
            Base::Reset( std::bit_cast<HANDLE>( socket.Handle( ) ), manualResetEvent, ownsEvent );
            ResetMembers( packetArray, packetArrayCount, sendSize, flags );
        }


        constexpr TransmitPacketsElement* Packets( ) const noexcept
        {
            return packetArray_;
        }
        constexpr UInt32 PacketCount( ) const noexcept
        {
            return packetArrayCount_;
        }
        constexpr UInt32 SendSize( ) const noexcept
        {
            return sendSize_;
        }
        constexpr TransmitFileFlags Flags( ) const noexcept
        {
            return flags_;
        }
    };

    /// <summary>
    /// A pool of requests specified by the 
    /// </summary>
    /// <typeparam name="RequestT">
    /// A type derived from <c>SocketRequest</c>
    /// </typeparam>
    template<typename RequestT, size_t N, size_t maxFreeRequestCount = N>
    class RequestPool
    {
    public:
        static_assert( std::is_base_of_v<SocketRequest, RequestT>, "RequestT must be derived from SocketRequest." );

        using RequestType = RequestT;
        static constexpr size_t StaticCapacity = N;
        static constexpr size_t MaxFreeRequestCount = maxFreeRequestCount;
    private:
        boost::container::small_vector<std::unique_ptr<RequestType>, StaticCapacity> items_;
        boost::container::small_vector<RequestType*, StaticCapacity> freeItems_;
        size_t acquiredCount_ = 0;
    public:
        RequestPool( )
        {
        }

        template<typename ...Args>
        RequestType* Acquire( Args&&... args )
        {
            if ( freeItems_.empty( ) == false )
            {
                RequestType* result = freeItems_.back( );
                freeItems_.pop_back( );
                result->Reset( std::forward<Args>( args )... );
                acquiredCount_++;
                return result;
            }
            else
            {
                std::unique_ptr<RequestType> request = std::make_unique<RequestType>( std::forward<Args>( args )... );
                RequestType* result = request.get( );
                items_.emplace_back( std::move( request ) );
                acquiredCount_++;
                return result;
            }
        }

        void Release( RequestType* request )
        {
            if ( freeItems_.size( ) <= MaxFreeRequestCount )
            {
                freeItems_.emplace_back( request );
            }
            else
            {
                auto it = std::ranges::find_if( items_, [request]( const auto& uptr ) { return uptr.get( ) == request; } );
                if ( it != items_.end( ) )
                {
                    items_.erase( it );
                }
            }
            acquiredCount_--;
        }

        constexpr bool CanClear( ) const noexcept
        {
            return  acquiredCount_ == 0;
        }

        bool Clear( )
        {
            if ( CanClear( ) )
            {
                items_.clear( );
                freeItems_.clear( );
            }
        }

    };

    /// <summary>
    /// 
    /// </summary>
    template<typename ConnectRequestPoolT = RequestPool<ConnectRequest, 2>,
        typename AcceptRequestPoolT = RequestPool<AcceptRequest, 2>,
        typename DisconnectRequestPoolT = RequestPool<DisconnectRequest, 2>,
        typename IoctlRequestPoolT = RequestPool<IoctlRequest, 2>,
        typename ReceiveRequestPoolT = RequestPool<ReceiveRequest, 2>,
        typename ReceiveFromRequestPoolT = RequestPool<ReceiveFromRequest, 2>,
        typename ReceiveMsgRequestPoolT = RequestPool<ReceiveMsgRequest, 2>,
        typename SendRequestPoolT = RequestPool<SendRequest, 2>,
        typename SendToRequestPoolT = RequestPool<SendToRequest, 2>,
        typename SendMsgRequestPoolT = RequestPool<SendMsgRequest, 2>,
        typename TransmitFileRequestPoolT = RequestPool<TransmitFileRequest, 2>,
        typename TransmitPacketsRequestPoolT = RequestPool<TransmitPacketsRequest, 2> >
    struct RequestsPoolTypeParams
    {
        using ConnectRequestPoolType = ConnectRequestPoolT;
        using AcceptRequestPoolType = AcceptRequestPoolT;
        using DisconnectRequestPoolType = DisconnectRequestPoolT;
        using IoctlRequestPoolType = IoctlRequestPoolT;
        using ReceiveRequestPoolType = ReceiveRequestPoolT;
        using ReceiveFromRequestPoolType = ReceiveFromRequestPoolT;
        using ReceiveMsgRequestPoolType = ReceiveMsgRequestPoolT;
        using SendRequestPoolType = SendRequestPoolT;
        using SendToRequestPoolType = SendToRequestPoolT;
        using SendMsgRequestPoolType = SendMsgRequestPoolT;
        using TransmitFileRequestPoolType = TransmitFileRequestPoolT;
        using TransmitPacketsRequestPoolType = TransmitPacketsRequestPoolT;
    };


    /// <summary>
    /// This is the implementation of the default RequestsPool. 
    /// It delegates all operations to instances of request type
    /// specific pool implementations specified by the RequestsPoolTypeParamsT
    /// template parameter.
    /// </summary>
    template<typename RequestsPoolTypeParamsT = RequestsPoolTypeParams<> >
    class RequestsPool
    {
    public:
        using RequestsPoolTypeParamsType = RequestsPoolTypeParamsT;
        using ConnectRequestPoolType = typename RequestsPoolTypeParamsType::ConnectRequestPoolType;
        using AcceptRequestPoolType = typename RequestsPoolTypeParamsType::AcceptRequestPoolType;
        using DisconnectRequestPoolType = typename RequestsPoolTypeParamsType::DisconnectRequestPoolType;
        using IoctlRequestPoolType = typename RequestsPoolTypeParamsType::IoctlRequestPoolType;
        using ReceiveRequestPoolType = typename RequestsPoolTypeParamsType::ReceiveRequestPoolType;
        using ReceiveFromRequestPoolType = typename RequestsPoolTypeParamsType::ReceiveFromRequestPoolType;
        using ReceiveMsgRequestPoolType = typename RequestsPoolTypeParamsType::ReceiveMsgRequestPoolType;
        using SendRequestPoolType = typename RequestsPoolTypeParamsType::SendRequestPoolType;
        using SendToRequestPoolType = typename RequestsPoolTypeParamsType::SendToRequestPoolType;
        using SendMsgRequestPoolType = typename RequestsPoolTypeParamsType::SendMsgRequestPoolType;
        using TransmitFileRequestPoolType = typename RequestsPoolTypeParamsType::TransmitFileRequestPoolType;
        using TransmitPacketsRequestPoolType = typename RequestsPoolTypeParamsType::TransmitPacketsRequestPoolType;

        static_assert( std::is_base_of_v<ConnectRequest, typename ConnectRequestPoolType::RequestType>, "The RequestType must be derived from ConnectRequest." );
        static_assert( std::is_base_of_v<AcceptRequest, typename AcceptRequestPoolType::RequestType>, "The RequestType must be derived from AcceptRequest." );
        static_assert( std::is_base_of_v<DisconnectRequest, typename DisconnectRequestPoolType::RequestType>, "The RequestType must be derived from DisconnectRequest." );
        static_assert( std::is_base_of_v<IoctlRequest, typename IoctlRequestPoolType::RequestType>, "The RequestType must be derived from IoctlRequest." );
        static_assert( std::is_base_of_v<ReceiveRequest, typename ReceiveRequestPoolType::RequestType>, "The RequestType must be derived from ReceiveRequest." );
        static_assert( std::is_base_of_v<ReceiveFromRequest, typename ReceiveFromRequestPoolType::RequestType>, "The RequestType must be derived from ReceiveFromRequest." );
        static_assert( std::is_base_of_v<ReceiveMsgRequest, typename ReceiveMsgRequestPoolType::RequestType>, "The RequestType must be derived from ReceiveMsgRequest." );
        static_assert( std::is_base_of_v<SendRequest, typename SendRequestPoolType::RequestType>, "The RequestType must be derived from SendRequest." );
        static_assert( std::is_base_of_v<SendToRequest, typename SendToRequestPoolType::RequestType>, "The RequestType must be derived from SendToRequest." );
        static_assert( std::is_base_of_v<SendToRequest, typename SendToRequestPoolType::RequestType>, "The RequestType must be derived from SendToRequest." );
        static_assert( std::is_base_of_v<TransmitFileRequest, typename TransmitFileRequestPoolType::RequestType>, "The RequestType must be derived from TransmitFileRequest." );
        static_assert( std::is_base_of_v<TransmitPacketsRequest, typename TransmitPacketsRequestPoolType::RequestType>, "The RequestType must be derived from TransmitPacketsRequest." );

        using ConnectRequestType = typename ConnectRequestPoolType::RequestType;
        using AcceptRequestType = typename AcceptRequestPoolType::RequestType;
        using DisconnectRequestType = typename DisconnectRequestPoolType::RequestType;
        using IoctlRequestType = typename IoctlRequestPoolType::RequestType;
        using ReceiveRequestType = typename ReceiveRequestPoolType::RequestType;
        using ReceiveFromRequestType = typename ReceiveFromRequestPoolType::RequestType;
        using ReceiveMsgRequestType = typename ReceiveMsgRequestPoolType::RequestType;
        using SendRequestType = typename SendRequestPoolType::RequestType;
        using SendToRequestType = typename SendToRequestPoolType::RequestType;
        using SendMsgRequestType = typename SendMsgRequestPoolType::RequestType;
        using TransmitFileRequestType = typename TransmitFileRequestPoolType::RequestType;
        using TransmitPacketsRequestType = typename TransmitPacketsRequestPoolType::RequestType;

    private:
        ConnectRequestPoolType connectRequestPool_;
        AcceptRequestPoolType acceptRequestPool_;
        DisconnectRequestPoolType disconnectRequestPool_;
        IoctlRequestPoolType ioctlRequestPool_;
        ReceiveRequestPoolType receiveRequestPool_;
        ReceiveFromRequestPoolType receiveFromRequestPool_;
        ReceiveMsgRequestPoolType receiveMsgRequestPool_;
        SendRequestPoolType sendRequestPool_;
        SendToRequestPoolType sendToRequestPool_;
        SendMsgRequestPoolType sendMsgRequestPool_;
        TransmitFileRequestPoolType transmitFileRequestPool_;
        TransmitPacketsRequestPoolType transmitPacketsRequestPool_;

    public:
        RequestsPool( )
        {
        }

        RequestsPool( const RequestsPool& other ) = delete;
        RequestsPool( RequestsPool&& other ) = delete;
        RequestsPool& operator = ( const RequestsPool& other ) = delete;
        RequestsPool& operator = ( RequestsPool&& other ) = delete;


        bool CanClear( ) const noexcept
        {
            return connectRequestPool_.CanClear( ) &&
                acceptRequestPool_.CanClear( ) &&
                disconnectRequestPool_.CanClear( ) &&
                ioctlRequestPool_.CanClear( ) &&
                receiveRequestPool_.CanClear( ) &&
                receiveFromRequestPool_.CanClear( ) &&
                receiveMsgRequestPool_.CanClear( ) &&
                sendRequestPool_.CanClear( ) &&
                sendToRequestPool_.CanClear( ) &&
                sendMsgRequestPool_.CanClear( ) &&
                transmitFileRequestPool_.CanClear( ) &&
                transmitPacketsRequestPool_.CanClear( );
        }

        void Clear( )
        {
            if ( CanClear( ) )
            {
                connectRequestPool_.Clear( );
                acceptRequestPool_.Clear( );
                disconnectRequestPool_.Clear( );
                ioctlRequestPool_.Clear( );
                receiveRequestPool_.Clear( );
                receiveFromRequestPool_.Clear( );
                receiveMsgRequestPool_.Clear( );
                sendRequestPool_.Clear( );
                sendToRequestPool_.Clear( );
                sendMsgRequestPool_.Clear( );
                transmitFileRequestPool_.Clear( );
                transmitPacketsRequestPool_.Clear( );
            }
        }


        void Release( SocketRequest* request )
        {
            assert( request != nullptr );
            SocketRequestType socketRequestType = request->Type( );
            switch ( socketRequestType )
            {
                case SocketRequestType::Connect:
                {
                    ConnectRequestType* connectRequest = static_cast<ConnectRequestType*>( request );
                    connectRequestPool_.Release( connectRequest );
                }
                break;
                case SocketRequestType::Accept:
                {
                    AcceptRequestType* acceptRequest = static_cast<AcceptRequestType*>( request );
                    acceptRequestPool_.Release( acceptRequest );
                }
                break;
                case SocketRequestType::Disconnect:
                {
                    DisconnectRequestType* disconnectRequest = static_cast<DisconnectRequestType*>( request );
                    disconnectRequestPool_.Release( disconnectRequest );
                }
                break;
                case SocketRequestType::Ioctl:
                {
                    IoctlRequestType* ioctlRequest = static_cast<IoctlRequestType*>( request );
                    ioctlRequestPool_.Release( ioctlRequest );
                }
                break;
                case SocketRequestType::Receive:
                {
                    ReceiveRequestType* receiveRequest = static_cast<ReceiveRequestType*>( request );
                    receiveRequestPool_.Release( receiveRequest );
                }
                break;
                case SocketRequestType::ReceiveFrom:
                {
                    ReceiveFromRequestType* receiveFromRequest = static_cast<ReceiveFromRequestType*>( request );
                    receiveFromRequestPool_.Release( receiveFromRequest );
                }
                break;
                case SocketRequestType::ReceiveMsg:
                {
                    ReceiveMsgRequestType* receiveMsgRequest = static_cast<ReceiveMsgRequestType*>( request );
                    receiveMsgRequestPool_.Release( receiveMsgRequest );
                }
                break;
                case SocketRequestType::Send:
                {
                    SendRequestType* sendRequest = static_cast<SendRequestType*>( request );
                    sendRequestPool_.Release( sendRequest );
                }
                break;
                case SocketRequestType::SendTo:
                {
                    SendToRequestType* sendToRequest = static_cast<SendToRequestType*>( request );
                    sendToRequestPool_.Release( sendToRequest );
                }
                break;
                case SocketRequestType::SendMsg:
                {
                    SendMsgRequestType* sendMsgRequest = static_cast<SendMsgRequestType*>( request );
                    sendMsgRequestPool_.Release( sendMsgRequest );
                }
                break;
                case SocketRequestType::TransmitFile:
                {
                    TransmitFileRequestType* transmitFileRequest = static_cast<TransmitFileRequestType*>( request );
                    transmitFileRequestPool_.Release( transmitFileRequest );
                }
                break;
                case SocketRequestType::TransmitPackets:
                {
                    TransmitPacketsRequestType* transmitPacketsRequest = static_cast<TransmitPacketsRequestType*>( request );
                    transmitPacketsRequestPool_.Release( transmitPacketsRequest );
                }
                break;
            }
        }


        template<typename SocketType>
        ConnectRequestType* AcquireConnectRequest( const SocketType& connectionSocket, const Sockets::Address& address, const Byte* buffer = nullptr, UInt32 numberOfBytesToSend = 0 )
        {
            ConnectRequestType* result = connectRequestPool_.Acquire( connectionSocket.Handle( ), address, buffer, numberOfBytesToSend );
            return result;
        }
        
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, ConnectRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            ConnectRequestType* result = connectRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>(args)... );
            return result;
        }

        template<typename SocketType>
        AcceptRequestType* AcquireAcceptRequest( const SocketType& listenerSocket, const SocketType& connectionSocket, Byte* buffer, UInt32 receiveDataLength, UInt32 localAddressLength = AcceptRequest::MaxLocalAddressLength, UInt32 remoteAddressLength = AcceptRequest::MaxRemoteAddressLength )
        {
            AcceptRequestType* result = acceptRequestPool_.Acquire( listenerSocket.Handle( ), connectionSocket.Handle( ), buffer, receiveDataLength, localAddressLength, remoteAddressLength );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, AcceptRequestType>
        RequestType* Acquire( const SocketType& listenerSocket, const SocketType& connectionSocket, Args&& ... args )
        {
            AcceptRequestType* result = acceptRequestPool_.Acquire( listenerSocket.Handle( ), connectionSocket.Handle(), std::forward<Args>( args )... );
            return result;
        }


        template<typename SocketType>
        DisconnectRequestType* AcquireDisconnectRequest( const SocketType& connectionSocket, bool reuse = true )
        {
            DisconnectRequestType* result = disconnectRequestPool_.Acquire( connectionSocket.Handle( ), reuse );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, DisconnectRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            DisconnectRequestType* result = disconnectRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }

        template<typename SocketType>
        IoctlRequestType* AcquireIoctlRequest( const SocketType& connectionSocket, UInt32 ioControlCode = 0, const Byte* inBuffer = nullptr, UInt32 inBufferLength = 0, Byte* outBuffer = nullptr, UInt32 outBufferLength = 0 )
        {
            IoctlRequestType* result = ioctlRequestPool_.Acquire( connectionSocket.Handle( ), ioControlCode, inBuffer, inBufferLength, outBuffer, outBufferLength );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, IoctlRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            IoctlRequestType* result = ioctlRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }

        template<typename SocketType>
        ReceiveRequestType* AcquireReceiveRequest( const SocketType& connectionSocket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            ReceiveRequestType* result = receiveRequestPool_.Acquire( connectionSocket.Handle( ), buffers, bufferCount, flags );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, ReceiveRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            ReceiveRequestType* result = receiveRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }

        template<typename SocketType>
        ReceiveFromRequestType* AcquireReceiveFromRequest( const SocketType& connectionSocket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            ReceiveFromRequestType* result = receiveFromRequestPool_.Acquire( connectionSocket.Handle( ), buffers, bufferCount, flags );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, ReceiveFromRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            ReceiveFromRequestType* result = receiveFromRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }

        template<typename SocketType>
        ReceiveMsgRequestType* AcquireReceiveMsgRequest( const SocketType& connectionSocket, WSAMSG* msg = nullptr)
        {
            ReceiveMsgRequestType* result = receiveMsgRequestPool_.Acquire( connectionSocket.Handle( ), msg );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, ReceiveMsgRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            ReceiveMsgRequestType* result = receiveMsgRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }

        template<typename SocketType>
        SendRequestType* AcquireSendRequest( const SocketType& connectionSocket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None )
        {
            SendRequestType* result = sendRequestPool_.Acquire( connectionSocket.Handle( ), buffers, bufferCount, flags );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, SendRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            SendRequestType* result = sendRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }

        template<typename SocketType>
        SendToRequestType* AcquireSendToRequest( const SocketType& connectionSocket, WSABUF* buffers = nullptr, UInt32 bufferCount = 0, MessageFlags flags = MessageFlags::None, const Sockets::Address& destinationAddress = Sockets::Address( ) )
        {
            SendToRequestType* result = sendToRequestPool_.Acquire( connectionSocket.Handle( ), buffers, bufferCount, flags, destinationAddress );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, SendToRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            SendToRequestType* result = sendToRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }

        template<typename SocketType>
        SendMsgRequestType* AcquireSendMsgRequest( const SocketType& connectionSocket, WSAMSG* msg = nullptr, MessageFlags flags = MessageFlags::None )
        {
            SendMsgRequestType* result = sendMsgRequestPool_.Acquire( connectionSocket.Handle( ), msg, flags );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, SendMsgRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            SendMsgRequestType* result = sendMsgRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }

        template<typename SocketType>
        TransmitFileRequestType* AcquireTransmitFileRequest( const SocketType& connectionSocket, HANDLE hFile = INVALID_HANDLE_VALUE, UInt32 numberOfBytesToWrite = 0, UInt32 numberOfBytesPerSend = 0, TransmitFileBuffers* transmitBuffers = nullptr, TransmitFileFlags flags = TransmitFileFlags::None )
        {
            TransmitFileRequestType* result = transmitFileRequestPool_.Acquire( connectionSocket.Handle( ), hFile, numberOfBytesToWrite, numberOfBytesPerSend, transmitBuffers, flags );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, TransmitFileRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            TransmitFileRequestType* result = transmitFileRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }


        template<typename SocketType>
        TransmitPacketsRequestType* AcquireTransmitPacketsRequest( const SocketType& connectionSocket, TransmitPacketsElement* packetArray = nullptr, UInt32 packetArrayCount = 0, UInt32 sendSize = 0, TransmitFileFlags flags = TransmitFileFlags::None )
        {
            TransmitPacketsRequestType* result = transmitPacketsRequestPool_.Acquire( connectionSocket.Handle( ), packetArray, packetArrayCount, sendSize, flags );
            return result;
        }
        template<typename RequestType, typename SocketType, typename ...Args>
            requires std::is_same_v<RequestType, TransmitPacketsRequestType>
        RequestType* Acquire( const SocketType& connectionSocket, Args&& ... args )
        {
            TransmitPacketsRequestType* result = transmitPacketsRequestPool_.Acquire( connectionSocket.Handle( ), std::forward<Args>( args )... );
            return result;
        }



    };



    /// <summary>
    /// Classes derived from this template are used to implement
    /// asynchronous operations on sockets.
    /// </summary>
    /// <remarks>
    /// This template uses static polymorphism to dispatch completion
    /// notifications to the handler functions implemented by classes
    /// derived from this template.
    /// </remarks>
    /// <typeparam name="DerivedT">
    /// The instantiated type derived from this template.
    /// </typeparam>
    template<typename DerivedT>
    class SocketHandler : public ContextHandler
    {
    public:
        using Base = ContextHandler;
        using DerivedType = DerivedT;
    protected:
        SocketHandler( const std::shared_ptr<IO::Context>& context, Sockets::Socket& socket )
            : Base( context )
        {
            context->Bind( socket, this );
        }
        SocketHandler( const std::shared_ptr<IO::Context>& context )
            : Base( context )
        {
        }

        
        static void ThrowLastSocketError( )
        {
            Socket::ThrowLastSocketError( );
        }
        static void ThrowSocketError( WinError error )
        {
            Socket::ThrowSocketError( error );
        }

    public:
        std::shared_ptr<const DerivedType> Self( ) const
        {
            return std::dynamic_pointer_cast<const DerivedType>( shared_from_this( ) );
        }
        std::shared_ptr<DerivedType> Self( )
        {
            return std::dynamic_pointer_cast<DerivedType>( shared_from_this( ) );
        }

        const DerivedType* This( ) const noexcept
        {
            return static_cast<const DerivedType*>( this );
        }
        DerivedType* This( ) noexcept
        {
            return static_cast<DerivedType*>( this );
        }
    protected:
        void BindToContext( const Sockets::Socket& socket )
        {
            auto context = Context( );
            context->Bind( socket, this );
        }
    private:
        UInt32 GetRequestFlags( SocketRequest* request )
        {
            static_assert( sizeof( SOCKET ) == sizeof( HANDLE ) );
            DWORD flags = 0;
            DWORD bytesTransferred = 0;
            SOCKET s = std::bit_cast<SOCKET>( request->Handle( ) );
            auto rc = WSAGetOverlappedResult( s, request, &bytesTransferred, FALSE, &flags );
            if ( !rc )
            {
                HCC_THROW_LAST_SOCKET_ERROR( );
            }
            return flags;
        }
    public:
        
        /// <summary>
        /// Establishes a connection to a specified socket, and optionally sends 
        /// data once the connection is established. The <c>BeginAsyncConnect</c> function 
        /// is only supported on connection-oriented sockets.
        /// </summary>
        /// <param name="request">
        /// A pointer to a <c>ConnectRequest</c> object that holds the information
        /// required for this asynchronous operation. This pointer must be valid 
        /// until the operation has completed. 
        /// </param>
        /// <remarks>
        /// <p>
        /// To handle the completion notification for this request, the concrete
        /// implementation derived from this template must implement:
        /// </p>
        /// <code>
        /// bool HandleConnectCompleted( ConnectRequest* request )
        /// </code>
        /// <p>
        /// The implementation of <c>HandleConnectCompleted</c> must return
        /// <c>true</c> to signal that it was able to process this notification.
        /// </p>
        /// </remarks>
        /// <returns>
        /// returns true if the call completed synchronously, otherwise false.
        /// </returns>
        bool BeginAsyncConnect( ConnectRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            const Address& address = request->Address( );
            auto buffer = request->Buffer( );
            DWORD bytesSent = 0;
            auto numberOfBytesToSend = request->NumberOfBytesToSend( );
            auto rc = Socket::ConnectEx( socket, address.data( ), address.length( ), buffer, numberOfBytesToSend, &bytesSent, request );
            if ( rc == WinError::None )
            {
                request->SetResult( NO_ERROR, bytesSent );
                DerivedType& self = static_cast<DerivedType&>( *this );
                self.ProcessConnectCompleted( request );
                return true;
            }
            else if ( rc != WinError::IoPending )
            {
                HCC_THROW_SOCKET_ERROR( rc );
            }
            return false;
        }

        /// <summary>
        /// Begins an asynchronous accept request.
        /// </summary>
        /// <param name="request">
        /// A pointer to an <c>AcceptRequest</c> object that holds the information
        /// required for this asynchronous operation. This pointer must be valid 
        /// until the operation has completed.
        /// </param>
        /// <remarks>
        /// <p>
        /// To handle the completion notification for this request, the concrete
        /// implementation derived from this template must implement:
        /// </p>
        /// <code>
        /// bool HandleAcceptCompleted( AcceptRequest* request )
        /// </code>
        /// <p>
        /// The implementation of <c>HandleAcceptCompleted</c> must return
        /// <c>true</c> to signal that it was able to process this notification.
        /// </p>
        /// </remarks>
        /// <returns>
        /// returns true if the call completed synchronously, otherwise false.
        /// </returns>
        bool BeginAsyncAccept( AcceptRequest* request )
        {
            BindRequestToContext( request );
            auto listenSocket = (SOCKET)request->Handle( );
            auto acceptSocket = request->AcceptSocket( );
            auto buffer = request->Buffer( );
            DWORD receiveDataLength = request->NumberOfBytesToRead( );
            DWORD localAddressLength = request->LocalAddressLength( );
            DWORD remoteAddressLength = request->RemoteAddressLength( );
            DWORD bytesReceived = 0;

            auto rc = Socket::AcceptEx( listenSocket, acceptSocket, buffer, receiveDataLength, localAddressLength, remoteAddressLength, &bytesReceived, request );
            if ( rc == WinError::None )
            {
                DerivedType& self = static_cast<DerivedType&>( *this );
                self.ProcessAcceptCompleted( request );
                return true;
            }
            else if ( rc != WinError::IoPending )
            {
                HCC_THROW_SOCKET_ERROR( rc );
            }
            return false;
        }

        /// <summary>
        /// Begins an asynchronous disconnect request.
        /// </summary>
        /// <param name="request">
        /// A pointer to a <c>DisconnectRequest</c> object that holds the information
        /// required for this asynchronous operation. This pointer must be valid 
        /// until the operation has completed.
        /// </param>
        /// <remarks>
        /// <p>
        /// To handle the completion notification for this request, the concrete
        /// implementation derived from this template must implement:
        /// </p>
        /// <code>
        /// bool HandleDisconnectCompleted( DisconnectRequest* request )
        /// </code>
        /// <p>
        /// The implementation of <c>HandleDisconnectCompleted</c> must return
        /// <c>true</c> to signal that it was able to process this notification.
        /// </p>
        /// </remarks>
        /// <returns>
        /// returns true if the call completed synchronously, otherwise false.
        /// </returns>
        bool BeginAsyncDisconnect( DisconnectRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            bool reuse = request->Reuse( );

            auto rc = Socket::DisconnectEx( socket, request, reuse );
            if ( rc == WinError::None )
            {
                DerivedType& self = static_cast<DerivedType&>( *this );
                self.ProcessDisconnectCompleted( request );
                return true;
            }
            else if ( rc != WinError::IoPending )
            {
                HCC_THROW_SOCKET_ERROR( rc );
            }
            return false;
        }

        /// <summary>
        /// Begins an asynchronous ioctl request.
        /// </summary>
        /// <param name="request">
        /// A pointer to a <c>IoctlRequest</c> object that holds the information
        /// required for this asynchronous operation. This pointer must be valid 
        /// until the operation has completed.
        /// </param>
        /// <remarks>
        /// <p>
        /// To handle the completion notification for this request, the concrete
        /// implementation derived from this template must implement:
        /// </p>
        /// <code>
        /// bool HandleIoctlCompleted( IoctlRequest* request )
        /// </code>
        /// <p>
        /// The implementation of <c>HandleIoctlCompleted</c> must return
        /// <c>true</c> to signal that it was able to process this notification.
        /// </p>
        /// </remarks>
        /// <returns>
        /// returns true if the call completed synchronously, otherwise false.
        /// </returns>
        bool BeginAsyncIoctl( IoctlRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            UInt32 ioControlCode = request->ControlCode( );
            void* inBuffer = request->InBuffer( );
            UInt32 inBufferLength = request->InBufferLength( );
            void* outBuffer = request->OutBuffer( );
            UInt32 outBufferLength = request->OutBufferLength( );
            DWORD bytesReceived = 0;
            auto rc = WSAIoctl( socket, ioControlCode, inBuffer, inBufferLength,outBuffer, outBufferLength, &bytesReceived, request, nullptr );
            if ( rc == SOCKET_ERROR )
            {
                auto err = IO::Sockets::Socket::LastSocketError( );
                if ( err != WinError::IoPending )
                {
                    HCC_THROW_SOCKET_ERROR( err );
                }
                return false;
            }
            else
            {
                request->SetResult( NO_ERROR, bytesReceived );
                DerivedType& self = static_cast<DerivedType&>( *this );
                self.ProcessIoctlCompleted( request );
                return true;
            }
        }

        /// <summary>
        /// Begins an asynchronous receive request.
        /// </summary>
        /// <param name="request">
        /// A pointer to a <c>ReceiveRequest</c> object that holds the information
        /// required for this asynchronous operation. This pointer must be valid 
        /// until the operation has completed.
        /// </param>
        /// <remarks>
        /// <p>
        /// To handle the completion notification for this request, the concrete
        /// implementation derived from this template must implement:
        /// </p>
        /// <code>
        /// bool HandleReceiveCompleted( ReceiveRequest* request )
        /// </code>
        /// <p>
        /// The implementation of <c>HandleReceiveCompleted</c> must return
        /// <c>true</c> to signal that it was able to process this notification.
        /// </p>
        /// <p>
        /// The asynchronous request initiated by a call to <c>BeginAsyncReceive</c> 
        /// has a couple of interesting features: 
        /// </p>
        /// <ul>
        /// <li>
        /// It allows multiple receive buffers to be specified making it applicable 
        /// to the scatter/gather type of I/O.
        /// </li>
        /// <li>
        /// The flags are used both on input and returned on output, allowing 
        /// applications to sense the output state of the MessageFlags::Partial 
        /// flag bit. However, the MessageFlags::Partial flag bit is not supported 
        /// by all protocols.
        /// </li>
        /// </ul>
        /// <p>
        /// The <c>BeginAsyncReceive</c> function is used on connected sockets or 
        /// bound connectionless sockets specified by either the <c>handle</c> or 
        /// <c>socket</c> constructor parameter and is used to read incoming data. 
        /// The socket's local address must be known. For server applications, this 
        /// is usually done explicitly through bind or implicitly through BeginAsyncAccept. 
        /// For client applications the socket can become bound implicitly to a 
        /// local address through BeginAsyncConnect.
        /// </p>
        /// <p>
        /// For connected, connectionless sockets, this function restricts the 
        /// addresses from which received messages are accepted. The function only 
        /// returns messages from the remote address specified in the connection. 
        /// Messages from other addresses are (silently) discarded.
        /// </p>
        /// <p>
        /// <c>BeginAsyncReceive</c> is used to post one or more buffers into which 
        /// incoming data will be placed as it becomes available, after which the 
        /// application will be notified through its implementation of 
        /// <c>HandleReceiveCompleted</c>.
        /// </p>
        /// <p>
        /// 
        /// </p>
        /// </remarks>
        /// <returns>
        /// returns true if the call completed synchronously, otherwise false.
        /// </returns>
        bool BeginAsyncReceive( ReceiveRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            auto buffers = request->Buffers( );
            auto bufferCount = request->BufferCount( );
            auto flags = request->FlagsPtr( );
            auto rc = WSARecv( socket, buffers, bufferCount, nullptr, flags, request, nullptr );
            if ( rc == SOCKET_ERROR )
            {
                auto err = IO::Sockets::Socket::LastSocketError( );
                if ( err != WinError::IoPending )
                {
                    HCC_THROW_SOCKET_ERROR( err );
                }
                return false;
            }
            return true;
        }

        bool BeginAsyncReceiveFrom( ReceiveFromRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            auto buffers = request->Buffers( );
            auto bufferCount = request->BufferCount( );
            auto flags = request->FlagsPtr( );
            sockaddr* addr = request->Address( ).data( );
            Int32* addrLen = &request->Address( ).length_;
            *addrLen = static_cast<Int32>( Address::DataSize );

            auto rc = WSARecvFrom( socket, buffers, bufferCount, nullptr, flags, addr, addrLen, request, nullptr );
            if ( rc == SOCKET_ERROR )
            {
                auto err = IO::Sockets::Socket::LastSocketError( );
                if ( err != WinError::IoPending )
                {
                    HCC_THROW_SOCKET_ERROR( err );
                }
            }
            return false;
        }

        bool BeginAsyncReceiveMsg( ReceiveMsgRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            auto message = request->Message( );

            auto rc = Socket::RecvMsg( socket, message, nullptr, request, nullptr );
            if ( rc != WinError::IoPending )
            {
                HCC_THROW_SOCKET_ERROR( rc );
            }
            return false;
        }

        bool BeginAsyncSend( SendRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            auto buffers = request->Buffers( );
            auto bufferCount = request->BufferCount( );
            auto flags = static_cast<DWORD>( request->Flags( ) );

            auto rc = WSASend( socket, buffers, bufferCount, nullptr, flags, request, nullptr );
            if ( rc == SOCKET_ERROR )
            {
                auto err = IO::Sockets::Socket::LastSocketError( );
                if ( err != WinError::IoPending )
                {
                    HCC_THROW_SOCKET_ERROR( err );
                }
            }
            return false;
        }

        bool BeginAsyncSendTo( SendToRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            auto buffers = request->Buffers( );
            auto bufferCount = request->BufferCount( );
            auto flags = static_cast<DWORD>( request->Flags( ) );
            auto& destinationAddress = request->DestinationAddress( );
            DWORD bytesReceived = 0;
            auto rc = WSASendTo( socket, buffers, bufferCount, &bytesReceived, flags, destinationAddress.data(), destinationAddress.length(), request, nullptr );
            if ( rc == SOCKET_ERROR )
            {
                auto err = IO::Sockets::Socket::LastSocketError( );
                if ( err != WinError::IoPending )
                {
                    HCC_THROW_SOCKET_ERROR( err );
                }
                return false;
            }
            else
            {
                request->SetResult( NO_ERROR, bytesReceived );
                DerivedType& self = static_cast<DerivedType&>( *this );
                self.ProcessSendToCompleted( request );
                return true;
            }
        }

        bool BeginAsyncSendMsg( SendMsgRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            auto flags = static_cast<DWORD>( request->Flags( ) );
            auto message = request->Message( );

            auto rc = Socket::SendMsg( socket, message, flags, nullptr, request, nullptr );
            if ( rc != WinError::IoPending )
            {
                HCC_THROW_SOCKET_ERROR( rc );
            }

            return false;
        }

        bool BeginAsyncTransmitFile( TransmitFileRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            HANDLE hFile = request->FileHandle( );
            UInt32 numberOfBytesToWrite = request->NumberOfBytesToWrite( );
            UInt32 numberOfBytesPerSend = request->NumberOfBytesPerSend( );
            TransmitFileBuffers* transmitBuffers = request->TransmitBuffers( );
            DWORD flags = static_cast<DWORD>( request->Flags( ) );

            auto rc = Socket::TransmitFile( socket, hFile, numberOfBytesToWrite, numberOfBytesPerSend, request, transmitBuffers, flags );
            if ( rc == WinError::None )
            {
                request->SetResult( NO_ERROR );
                DerivedType& self = static_cast<DerivedType&>( *this );
                self.ProcessTransmitFileCompleted( request );
                return true;
            }
            else if ( rc != WinError::IoPending )
            {
                HCC_THROW_SOCKET_ERROR( rc );
            }
            return false;
        }

        bool BeginAsyncTransmitPackets( TransmitPacketsRequest* request )
        {
            BindRequestToContext( request );
            auto socket = (SOCKET)request->Handle( );
            TransmitPacketsElement* packetArray = request->Packets( );
            UInt32 packetArrayCount = request->PacketCount( );
            UInt32 sendSize = request->SendSize( );
            DWORD flags = static_cast<DWORD>( request->Flags( ) );

            auto rc = Socket::TransmitPackets( socket, packetArray, packetArrayCount, sendSize,request, flags );
            if ( rc == WinError::None )
            {
                request->SetResult( NO_ERROR );
                DerivedType& self = static_cast<DerivedType&>( *this );
                self.ProcessTransmitPacketsCompleted( request );
                return true;
            }
            else if ( rc != WinError::IoPending )
            {
                HCC_THROW_SOCKET_ERROR( rc );
            }
            return false;
        }

        virtual bool Process( Message& message ) override
        {
            bool result = false;
            auto request = static_cast<SocketRequest*>( message.Request( ) );
            DerivedType& self = static_cast<DerivedType&>( *this );
            SocketRequestType requestType = request->Type( );
            switch ( requestType )
            {
                case SocketRequestType::Connect:
                {
                    auto* connectRequest = static_cast<ConnectRequest*>( request );
                    result = self.ProcessConnectCompleted( connectRequest );
                }
                break;
                case SocketRequestType::Accept:
                {
                    auto* acceptRequest = static_cast<AcceptRequest*>( request );
                    result = self.ProcessAcceptCompleted( acceptRequest );
                }
                break;
                case SocketRequestType::Disconnect:
                {
                    auto* disconnectRequest = static_cast<DisconnectRequest*>( request );
                    result = self.ProcessDisconnectCompleted( disconnectRequest );
                }
                break;
                case SocketRequestType::Ioctl:
                {
                    auto* ioctlRequest = static_cast<IoctlRequest*>( request );
                    result = self.ProcessIoctlCompleted( ioctlRequest );
                }
                break;
                case SocketRequestType::Receive:
                {
                    auto* receiveRequest = static_cast<ReceiveRequest*>( request );
                    /*
                    DWORD flags = GetRequestFlags( receiveRequest );
                    receiveRequest->flags_ = static_cast<MessageFlags>( flags );
                    */
                    result = self.ProcessReceiveCompleted( receiveRequest );
                }
                break;
                case SocketRequestType::ReceiveFrom:
                {
                    auto* receiveFromRequest = static_cast<ReceiveFromRequest*>( request );
                    /*
                    DWORD flags = GetRequestFlags( receiveFromRequest );
                    receiveFromRequest->flags_ = static_cast<MessageFlags>( flags );
                    */
                    result = self.ProcessReceiveFromCompleted( receiveFromRequest );
                }
                break;
                case SocketRequestType::ReceiveMsg:
                {
                    auto* receiveMsgRequest = static_cast<ReceiveMsgRequest*>( request );
                    result = self.ProcessReceiveMsgCompleted( receiveMsgRequest );
                }
                break;
                case SocketRequestType::Send:
                {
                    auto* sendRequest = static_cast<SendRequest*>( request );
                    result = self.ProcessSendCompleted( sendRequest );
                }
                break;
                case SocketRequestType::SendTo:
                {
                    auto* sendToRequest  = static_cast<SendToRequest*>( request );
                    result = self.ProcessSendToCompleted( sendToRequest );
                }
                break;
                case SocketRequestType::SendMsg:
                {
                    auto* sendMsgRequest = static_cast<SendMsgRequest*>( request );
                    result = self.ProcessSendMsgCompleted( sendMsgRequest );
                }
                break;
                case SocketRequestType::TransmitFile:
                {
                    auto* transmitFileRequest = static_cast<TransmitFileRequest*>( request );
                    result = self.ProcessTransmitFileCompleted( transmitFileRequest );
                }
                break;
                case SocketRequestType::TransmitPackets:
                {
                    auto* transmitPacketsRequest = static_cast<TransmitPacketsRequest*>( request );
                    result = self.ProcessTransmitPacketsCompleted( transmitPacketsRequest );
                }
                break;
            }
            return result;
        }
    protected:
        constexpr bool ProcessConnectCompleted( ConnectRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleConnectCompleted( request );
            if ( result )
            {
                result = self.HandleConnectCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleConnectCompleted( ConnectRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleConnectCompleted( ConnectRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessAcceptCompleted( AcceptRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleAcceptCompleted( request );
            if ( result )
            {
                result = self.HandleAcceptCompleted( request );
                self.AfterHandleAcceptCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleAcceptCompleted( AcceptRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleAcceptCompleted( AcceptRequest* request ) const noexcept
        {
            return false;
        }
        constexpr void AfterHandleAcceptCompleted( AcceptRequest* request ) const noexcept
        {
            
        }

        constexpr bool ProcessDisconnectCompleted( DisconnectRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleDisconnectCompleted( request );
            if ( result )
            {
                result = self.HandleDisconnectCompleted( request );
                self.AfterHandleDisconnectCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleDisconnectCompleted( DisconnectRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleDisconnectCompleted( DisconnectRequest* request ) const noexcept
        {
            return false;
        }
        constexpr void AfterHandleDisconnectCompleted( DisconnectRequest* request ) const noexcept
        {
            
        }

        constexpr bool ProcessIoctlCompleted( IoctlRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleIoctlCompleted( request );
            if ( result )
            {
                result = self.HandleIoctlCompleted( request );
            }
            return result;
        }

        constexpr bool BeforeHandleIoctlCompleted( IoctlRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleIoctlCompleted( IoctlRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessReceiveCompleted( ReceiveRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleReceiveCompleted( request );
            if ( result )
            {
                result = self.HandleReceiveCompleted( request );
            }
            return result;
        }

        constexpr bool BeforeHandleReceiveCompleted( ReceiveRequest* request ) const noexcept
        {
            return true;
        }

        constexpr bool HandleReceiveCompleted( ReceiveRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessReceiveFromCompleted( ReceiveFromRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleReceiveFromCompleted( request );
            if ( result )
            {
                result = self.HandleReceiveFromCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleReceiveFromCompleted( ReceiveFromRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleReceiveFromCompleted( ReceiveFromRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessReceiveMsgCompleted( ReceiveMsgRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleReceiveMsgCompleted( request );
            if ( result )
            {
                result = self.HandleReceiveMsgCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleReceiveMsgCompleted( ReceiveMsgRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleReceiveMsgCompleted( ReceiveMsgRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessSendCompleted( SendRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleSendCompleted( request );
            if ( result )
            {
                result = self.HandleSendCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleSendCompleted( SendRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleSendCompleted( SendRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessSendToCompleted( SendToRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleSendToCompleted( request );
            if ( result )
            {
                result = self.HandleSendToCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleSendToCompleted( SendToRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleSendToCompleted( SendToRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessSendMsgCompleted( SendMsgRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleSendMsgCompleted( request );
            if ( result )
            {
                result = self.HandleSendMsgCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleSendMsgCompleted( SendMsgRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleSendMsgCompleted( SendMsgRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessTransmitFileCompleted( TransmitFileRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleTransmitFileCompleted( request );
            if ( result )
            {
                result = self.HandleTransmitFileCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleTransmitFileCompleted( TransmitFileRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleTransmitFileCompleted( TransmitFileRequest* request ) const noexcept
        {
            return false;
        }

        constexpr bool ProcessTransmitPacketsCompleted( TransmitPacketsRequest* request ) noexcept
        {
            DerivedType& self = static_cast<DerivedType&>( *this );
            bool result = self.BeforeHandleTransmitPacketsCompleted( request );
            if ( result )
            {
                result = self.HandleTransmitPacketsCompleted( request );
            }
            return result;
        }
        constexpr bool BeforeHandleTransmitPacketsCompleted( TransmitPacketsRequest* request ) const noexcept
        {
            return true;
        }
        constexpr bool HandleTransmitPacketsCompleted( TransmitPacketsRequest* request ) const noexcept
        {
            return false;
        }
    };








    class Span
    {
        UInt32 length_;
        const Byte* buffer_;
    public:
        constexpr Span( ) noexcept 
            : length_(0), buffer_(nullptr)
        { }
        constexpr Span(const Byte* data, size_t dataLength ) noexcept 
            : length_( static_cast<UInt32>( dataLength ) ), buffer_( data )
        {
        }

        void Reset( const Byte* data = nullptr, size_t dataLength = 0 ) noexcept
        {
            buffer_ = data;
            length_ = static_cast<UInt32>( dataLength );
        }

        constexpr size_t size( ) const noexcept
        {
            return length_;
        }
        constexpr size_t Size( ) const noexcept
        {
            return length_;
        }
        constexpr void SetSize( size_t value ) noexcept
        {
            length_ = static_cast<UInt32>( value );
        }
        constexpr const Byte* data( ) const noexcept
        {
            return buffer_;
        }

        constexpr const Byte* begin( ) const noexcept
        {
            return buffer_;
        }
        constexpr const Byte* end( ) const noexcept
        {
            return buffer_ + size( );
        }
        constexpr const Byte* cbegin( ) const noexcept
        {
            return buffer_;
        }
        constexpr const Byte* cend( ) const noexcept
        {
            return buffer_ + size( );
        }

    };

    static_assert( sizeof( Span ) == sizeof( WSABUF ) );


    class WSAInitTerm
    {
        WORD versionRequested_ = MAKEWORD( 2, 2 );
        WSADATA wsaData_;
    public:
        HCC_EXPORT explicit WSAInitTerm( WORD versionRequested = MAKEWORD( 2, 2 ) );
        HCC_EXPORT ~WSAInitTerm( );
        const WSADATA& data( ) const noexcept
        {
            return wsaData_;
        }
    };

}

#endif
