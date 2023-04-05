## 2022.07.21
- Upgraded the version of fmt included with Harlinn.Common.Core from 8.0.1 to 9.0.0
## 2022.02.20
- General improvements to the implementation of the `IO::Sockets::Socket` class:
  - Continued work on the documentation.
- Added new class `IO::Sockets::NetworkEvents` to HCCSocket.h, making it simpler to decode the information provided in a `struct WSANETWORKEVENTS`.  
- Changed the implementation of `long long IO::Sockets::Socket::Receive( void* buffer, size_t numberOfBytesToRead, MessageFlags flags ) const`
  The function will now return `0` and **not** throw an exception on timeout.  
## 2022.02.19
- General improvements to the implementation of the `IO::Sockets::Socket` class:
  - Continued work on the documentation.
- Finished initial implementation of class `IO::Sockets::ProtocolInfo` in HCCSocket.h, making it simpler to decode the information provided in a `struct WSAPROTOCOL_INFOW`.
- Added new class `IO::Sockets::ProtocolChain` to HCCSocket.h, making it simpler to decode the information provided in a `struct WSAPROTOCOLCHAIN`, used with `IO::Sockets::ProtocolInfo`.
- Added new enumeration `IO::Sockets::SecurityProtocol` in HCCSocket.h, used with `IO::Sockets::ProtocolInfo`.
- Added new enumeration `IO::Sockets::NetworkByteOrder` in HCCSocket.h, used with `IO::Sockets::ProtocolInfo`.
- Added, and documented, new enumeration `IO::Sockets::ProviderFlags` in HCCSocket.h, used with `IO::Sockets::ProtocolInfo`.
- Added, and documented, new enumeration `IO::Sockets::ServiceFlags1` in HCCSocket.h, used with `IO::Sockets::ProtocolInfo`.
- Added new template `template<size_t size> struct SocketAddressList` in HCCSocket.h, which is binary compatible with SOCKET_ADDRESS_LIST. 
  The justification for this template is that it can be allocated on the stack. Using:
  ```C++ 
    SocketAddressList<2> addressList;
  ``` 
  will create an SOCKET_ADDRESS_LIST compatible structure with room for two entries.
## 2022.02.18
- General improvements to the implementation of the `IO::Sockets::Socket` class:
  - Improved documentation.
  - Improved, and more consistent, error handling.
## 2022.02.17
- Fix object lifetime issues for `IO::Context` and related classes: 
  - Updated `Tests\\Harlinn.Common.Core.Tests`
  - Updated the examples located under `Examples\\Core\\Socket`
- Added new functions to `IO::Sockets::Socket`:
  ```C++ 
  bool Open( AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType, Flags flags = Flags::None );
  Socket Accept( LPCONDITIONPROC conditionFunction, ULONG_PTR callbackData, sockaddr* addr = nullptr, int* addrlen = nullptr ) const;
  void Connect( const sockaddr* name, int namelen, WSABUF* callerData, WSABUF* calleeData, QOS* SQOS, QOS* GQOS = nullptr ) const;
  void Connect( const Address& address, WSABUF* callerData, WSABUF* calleeData, QOS* SQOS, QOS* GQOS = nullptr ) const;
  void ConnectByList( SOCKET_ADDRESS_LIST* socketAddress, DWORD* localAddressLength, SOCKADDR* localAddress, DWORD* remoteAddressLength, SOCKADDR* remoteAddress, const timeval* timeout = nullptr, OVERLAPPED* reserved = nullptr ) const;
  void ConnectByName( LPWSTR nodeName, LPWSTR serviceName, DWORD* localAddressLength, SOCKADDR* localAddress, DWORD* remoteAddressLength, SOCKADDR* remoteAddress, const timeval* timeout = nullptr, OVERLAPPED* reserved = nullptr ) const;
  void Duplicate( DWORD processId, ProtocolInfo& protocolInfo ) const;
  void EnumNetworkEvents( WSANETWORKEVENTS* networkEvents, HANDLE eventHandle = 0 ) const;
  void EventSelect( HANDLE eventHandle, EventFlags flags ) const;
  Socket JoinLeaf( const sockaddr* name, int namelen, WSABUF* callerData, WSABUF* calleeData, QOS* SQOS, QOS* GQOS, DWORD flags ) const;
  void Ioctl( DWORD ioControlCode, void* inBuffer, DWORD inBufferSize, void* outBuffer, DWORD outBufferSize, DWORD* bytesReturned, OVERLAPPED* overlapped = nullptr, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine = nullptr ) const;
  void Ioctl( long cmd, u_long* argp ) const;
  Sockets::Address PeerName( ) const;
  Sockets::Address Name( ) const;
  static int Select( int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const timeval* timeout = nullptr );
  long long ReceiveFrom( void* buffer, size_t bufferSize, MessageFlags flags = MessageFlags::None, sockaddr* from = nullptr, int* fromlen = nullptr ) const;
  long long ReceiveFrom( void* buffer, size_t bufferSize, MessageFlags flags, Sockets::Address& from ) const;
  long long ReceiveFrom( void* buffer, size_t bufferSize, Sockets::Address& from ) const;
  bool ReceiveFrom( WSABUF* buffers, DWORD bufferCount, DWORD* numberOfBytesRecvd, MessageFlags* flags, sockaddr* from, int* fromlen, OVERLAPPED* overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine ) const;
  long long SendTo( const void* buffer, size_t numberOfBytesToSend, MessageFlags flags = MessageFlags::None, const sockaddr* destinationAddress = nullptr, int destinationAddressSize = 0 ) const;
  long long SendTo( const void* buffer, size_t numberOfBytesToSend, MessageFlags flags, const Sockets::Address& destinationAddress ) const;
  long long SendTo( const void* buffer, size_t numberOfBytesToSend, const Sockets::Address& destinationAddress ) const;
  bool SendTo( WSABUF* buffers, DWORD bufferCount, DWORD* numberOfBytesSent, MessageFlags flags, const sockaddr* destinationAddress, int destinationAddressLength, OVERLAPPED* overlapped = nullptr, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine  = nullptr ) const;
  ```
  
## 2022.02.16
- Fix object lifetime issues for `IO::Context` and related classes: 
  - Added support for `std::shared_ptr` to: 
    - `IO::FileHandler`
    - `IO::FileDispatcher` 
    - `IO::CommDeviceHandler`
    - `IO::CommDeviceDispatcher`
    - `IO::CommDeviceDispatcher`
    - `IO::PipeHandler`
    - `IO::PipeDispatcher`
    - `IO::Sockets::SocketHandler`
    - `IO::Sockets::Tcp::Server::ConnectionHandler`
    - `IO::Sockets::Tcp::Server::ConnectionHandlerFactory`
    - `IO::Sockets::Tcp::Server::ConnectionHandlerPool`
    - `IO::Sockets::Tcp::Server::ListenerHandler`
## 2022.02.15
- Fix object lifetime issues for `IO::Context` and related classes:
  - The lifetime of a `IO::ContextHandler` currently ends too soon, since all 
    `IO::Request` objects should be passed to the implementation of 
    `void ProcessDone( Message& message )` provided by any specialization of `IO::ContextHandler`.
    To enforce this, the implementation of `IO::Context::ProcessRequests( )` must be able to ensure that
    the lifetime of the `IO::ContextHandler` currently processing a message is guaranteed until the call
    to `void ProcessDone( Message& message )` has completed. This can be achieved by introducing reference 
    counting for the `IO::ContextHandler` types, which can easily be implemented using `std::shared_ptr`,
    `std::weak_ptr_` and `std::enable_shared_from_this`. 
  - Changed `IO::Context`, it is now derived from `std::enable_shared_from_this<IO::Context>` 
  - Changed `IO::ContextHandler`, it is now derived from `std::enable_shared_from_this<IO::ContextHandler>`
## 2022.02.14
- Fixed a memory leak in `Address::Address( const wchar_t* nodeName, const wchar_t* serviceName )`
- Fixed a memory leak in `Address::Address( const wchar_t* nodeName, UInt16 portNumber )`
- Added a new template `RequestPool` to HCCSockets.h
- Added a new template `RequestsPoolTypeParams` to HCCSockets.h
- Added a new template `RequestsPool` to HCCSockets.h
- Added a new template `ConnectionHandlerRequestsPool` to HCCSockets.h
## 2022.02.13
- Added a new a template `ConnectionHandlerPool` to HCCTcpServer.h
- Added a new a template `ConnectionHandlerFactory` to HCCTcpServer.h
- Added a new a template `ConnectionHandlerFactoryBase` to HCCTcpServer.h
## 2022.02.12
- Added a new a template `ConnectionHandler` to HCCTcpServer.h
- Added a new a template `ListenerHandler` to HCCTcpServer.h
## 2022.02.10
- Fixed a bug in the implementation of `template<typename DerivedT> IO::Sockets::SocketHandler::Process`, 
  where the implementation did not retrieve and update the value for the `flags_` member of the
  `IO::Sockets::ReceiveRequest` object before calling `HandleReceiveCompleted`. 
- Fixed a bug in the implementation of `template<typename DerivedT> IO::Sockets::SocketHandler::Process`, 
  where the implementation did not retrieve and update the value for the `flags_` member of the
  `IO::Sockets::ReceiveFromRequest` object before calling `HandleReceiveFromCompleted`.
- Improved the documentation for `IO::Sockets::ReceiveFromRequest`.
## 2022.02.09
- Improved the documentation for `IO::Sockets::ConnectRequest`.
- Improved the documentation for `IO::Sockets::AcceptRequest`.
- Improved the documentation for `IO::Sockets::DisconnectRequest`.
- Improved the documentation for `IO::Sockets::IoctlRequest`.
- Improved the documentation for `IO::Sockets::ReceiveRequest`.
- Improved the documentation for `template<typename DerivedT> IO::Sockets::SocketHandler`.
- Improved the documentation for `IO::Context`.
- Improved the documentation for `IO::ContextHandler`.
- Improved the documentation for `IO::Request`.
- Removed the `IO::Context* context` argument from the constructors for all classes derived from
  `IO::Request`. The context for an asynchronous request is now set by the BeginXXX functions
  implemented by the template classes derived from `ContextHandler`. 
- Fix build for examples that include HExTypes.h. Sensor has become ambiguous since SensorAPI.h 
  also declares `class Sensor`.
- Dropping Examples\Core\ThreadPools\HExTpEx01
- Dropping HCCThreadpools.h, for now turning all of it into a huge comment, because `IO::Request` no longer
  supports this API.  
- Changed the `context_` member of `IO::Request`, in HCCIORequest.h, from `void*` to `IO::Context*`. 
## 2022.02.04
- Added new file HCCUdpServer.h to Harlinn.Common.Core
- Added new file HCCUdpClient.h to Harlinn.Common.Core
- Added new file HCCTcpServer.h to Harlinn.Common.Core
- Added new file HCCTcpClient.h to Harlinn.Common.Core
## 2022.01.26
- Improved the tests for ``BitVector`` (BitVectorTests.cpp) in Harlinn.Common.Core.Tests
## 2022.01.25
- Added functionality to ``template<typename VectorT> BitVector``
  - Implemented ``template<typename T> void append( const T* bits, size_t bitCount )``
  - Implemented ``template<typename VectorU> void append( const BitVector<VectorU>& other )``
- Added unit more tests for ``BitVector`` to BitVectorTests.cpp in Harlinn.Common.Core.Tests
## 2022.01.24
- Added functionality to ``template<typename VectorT> BitVector``
  - Implemented ``BitVector operator~( ) const``
  - Implemented ``template<typename VectorU> void And( const BitVector<VectorU>& other )``
  - Implemented ``template<typename VectorU> void Or( const BitVector<VectorU>& other )``
  - Implemented ``template<typename VectorU> void Xor( const BitVector<VectorU>& other )``
  - Implemented ``template<typename VectorU> BitVector& operator &= ( const BitVector<VectorU>& other )``
  - Implemented ``template<typename VectorU> BitVector& operator |= ( const BitVector<VectorU>& other )``
  - Implemented ``template<typename VectorU> BitVector& operator ^= ( const BitVector<VectorU>& other )``
  - Implemented ``bool all( ) const noexcept``
  - Implemented ``bool none( ) const noexcept``
  - Implemented ``bool any( ) const``
- Added unit more tests for ``BitVector`` to BitVectorTests.cpp in Harlinn.Common.Core.Tests
## 2022.01.23
- Added functionality to ``template<typename VectorT> BitVector``
  - Implemented ``explicit operator bool( ) const noexcept``
  - Implemented ``constexpr bool empty( ) const noexcept``
  - Implemented ``BitVector`` constructors
  - Implemented ``operator & ( const BitVector<VectorT>& lhs, const BitVector<VectorU>& rhs )``
  - Implemented ``operator | ( const BitVector<VectorT>& lhs, const BitVector<VectorU>& rhs )``
  - Implemented ``operator ^ ( const BitVector<VectorT>& lhs, const BitVector<VectorU>& rhs )``
- Added unit more tests for `BitVector` to BitVectorTests.cpp in Harlinn.Common.Core.Tests
## 2022.01.22
- Added functionality to `template<typename VectorT> BitVector`
  - Implemented ``void resize( size_t newSize, bool value = false )``
  - Implemented ``void emplace_back( bool value )``
  - Implemented ``void push_back( bool value )``
  - Implemented ``template<size_t N> void append( const Bits<N> values )``
  - Implemented ``template<typename T> void append( const T value, size_t bitCount = sizeof(T) * BitsPerByte )``
  - Implemented ``void flip( ) noexcept``
  - Implemented ``constexpr size_t capacity( ) const noexcept``
  - Implemented ``void reserve( size_t numberOfBits )``
  - Implemented ``void clear( )``
  - Implemented ``void swap( BitVector& other ) noexcept``
  - Implemented ``BitVector::reference``
  - Implemented ``reference operator[]( size_t index ) noexcept``
  - Implemented ``bool operator[]( size_t index ) const noexcept``
  - Implemented ``bool test( size_t index ) const noexcept``
  - Implemented ``template<typename VectorU> bool EqualTo( const BitVector<VectorU>& other ) const noexcept``
  - Implemented ``template<typename VectorU> bool operator == ( const BitVector<VectorU>& other ) const noexcept``
  - Implemented ``template<typename VectorU> bool operator != ( const BitVector<VectorU>& other ) const noexcept``
  - Implemented ``word_type* data( ) noexcept``
  - Implemented ``const word_type* data( ) const noexcept``
  - Implemented ``constexpr size_t size( ) const noexcept``
  - Implemented ``constexpr size_t DataSize( ) const noexcept``
  - Implemented ``const VectorType& Vector( ) const noexcept``
## 2022.01.21
- Improved the implementation of ``template<size_t bitCount> Bits``
  - Performance improvements for ``template<size_t bitCount> Bits::reference``
## 2022.01.20
- Added more unit tests for ``template<size_t bitCount> Bits`` to BitsTests.cpp in Harlinn.Common.Core.Tests
- Added more performance tests for ``template<size_t bitCount> Bits`` to BitsOperations.cpp in HCCMathPerfTest01
## 2022.01.19
- Added more unit tests for ``template<size_t bitCount> Bits`` to BitsTests.cpp in Harlinn.Common.Core.Tests
## 2022.01.18
- Fixed a bug in ``template<size_t N> struct BitMask``, which caused an overflow in the 
  calculation of the bit-mask for N=8, N=16, N=32 and N=64 (HCCLib.h)
- Implemented ``template<size_t bitCount> Bits``
- Added unit tests for ``template<size_t bitCount> Bits`` (BitsTests.cpp) to Harlinn.Common.Core.Tests
- Added performance tests for ``template<size_t bitCount> Bits`` (BitsOperations.cpp) to HCCMathPerfTest01
## 2022.01.17
- Added new header ``HCCBits.h``
  - Added ``template<size_t bitCount> Bits``
    
    Like ``template< std::size_t N > class bitset`` this template implements 
    a fixed size container for bits.

    This template uses the smallest unsigned integer capable of holding ``bitCount`` number of bits to 
    hold its value. It implements an API similar to ``std::bitset``. Since it uses an unsigned integer to
    store the bits, ``bitCount`` has to be less or equal to 64. This also makes most operations significantly
    faster than the same operation on a ``std::bitset``. My primary use for this template is to parse a binary,
    fixed size, bit-mask received over the network.

  - Added ``template<typename VectorT> BitVector`` 
  
    Like ``template<class Allocator> class vector<bool, Allocator>`` this template implements a variable 
    sized container for bits, but with an API that is similar to ``template<size_t bitCount> Bits``. Unlike
    ``std::vector<bool>``, ``BitVector`` lets me specify the container used to store the bits, which must
    be a ``std::vector`` like container of some integer type. My primary use for this template is to parse a binary,
    variable sized, bit-mask received over the network. The idea is to be able to use ``boost::container::small_vector``
    to store the bit-mask, and avoid dynamic memory allocation for, perhaps, 99% of the received bit-masks.  
 
- Fixed a bug in `FileSystemEntriesBase::Read( )`
## 2022.01.16
- Fixed bug in the declaration of the WideStringType concept in HCCTraits.h
- Finished initial/minimal implementation of the classes in HCCwbem.h
- Added initial implementation of missing wrappers for common COM interfaces:
  - Added `ServiceProvider` to HCCObj.h
## 2022.01.15
- Added initial implementation of missing wrappers for common COM interfaces:
  - Added `OleLink` to HCCObj.h
  - Added `OleItemContainer` to HCCObj.h
  - Added `OleInPlaceUIWindow` to HCCObj.h
  - Added `OleInPlaceActiveObject` to HCCObj.h
  - Added `OleInPlaceFrame` to HCCObj.h
  - Added `Continue` to HCCObj.h
  - Added `DropSource` to HCCObj.h
  - Added `DropTarget` to HCCObj.h
  - Added `DropSourceNotify` to HCCObj.h
  - Added `EnterpriseDropTarget` to HCCObj.h
  - Added `CreateTypeInfo` to HCCObj.h
  - Added `CreateTypeInfo2` to HCCObj.h
  - Added `CreateTypeLib` to HCCObj.h
  - Added `CreateTypeLib2` to HCCObj.h
  - Added `TypeInfo2` to HCCObj.h
  - Added `TypeChangeEvents` to HCCObj.h
  - Added `TypeFactory` to HCCObj.h
  - Added `TypeMarshal` to HCCObj.h
  - Added `RecordInfo` to HCCObj.h
  - Added `ErrorLog` to HCCObj.h
  - Added `TypeLibRegistrationReader` to HCCObj.h
  - Added `TypeLibRegistration` to HCCObj.h
  - Added `ClassFactory2` to HCCObj.h
  - Added `ProvideClassInfo2` to HCCObj.h
  - Added `ProvideMultipleClassInfo` to HCCObj.h
  - Added `OleControl` to HCCObj.h
  - Added `OleControlSite` to HCCObj.h
  - Added `PropertyPage` to HCCObj.h
  - Added `PropertyPage2` to HCCObj.h
  - Added `PropertyPageSite` to HCCObj.h
  - Added `PropertyNotifySink` to HCCObj.h
  - Added `SpecifyPropertyPages` to HCCObj.h
  - Added `PersistMemory` to HCCObj.h
  - Added `PersistStreamInit` to HCCObj.h
  - Added `PersistPropertyBag` to HCCObj.h
  - Added `SimpleFrameSite` to HCCObj.h
  - Added `Font` to HCCObj.h
  - Added `Picture` to HCCObj.h
  - Added `Picture2` to HCCObj.h
  - Added `FontEventsDisp` to HCCObj.h
  - Added `FontDisp` to HCCObj.h
  - Added `PictureDisp` to HCCObj.h
  - Added `OleInPlaceObject` to HCCObj.h
  - Added `OleInPlaceObjectWindowless` to HCCObj.h
  - Added `OleInPlaceSite` to HCCObj.h
  - Added `OleInPlaceSiteEx` to HCCObj.h
  - Added `OleInPlaceSiteWindowless` to HCCObj.h
  - Added `ViewObject` to HCCObj.h
  - Added `ViewObject2` to HCCObj.h
  - Added `ViewObjectEx` to HCCObj.h
  - Added `OleUndoUnit` to HCCObj.h
  - Added `OleParentUndoUnit` to HCCObj.h
  - Added `EnumOleUndoUnits` to HCCObj.h
  - Added `OleUndoManager` to HCCObj.h
  - Added `PointerInactive` to HCCObj.h
  - Added `ObjectWithSite` to HCCObj.h
  - Added `PerPropertyBrowsing` to HCCObj.h
  - Added `PropertyBag` to HCCObj.h
  - Added `PropertyBag2` to HCCObj.h
  - Added `PersistPropertyBag2` to HCCObj.h
  - Added `AdviseSinkEx` to HCCObj.h
  - Added `QuickActivate` to HCCObj.h

## 2022.01.14
- Added `template<...> class ObjectBase` to HCCComImpl.h
- Added `template<...> class Interfaces` to HCCComImpl.h
- Added  ComInterfacesTests.cpp to Harlinn.Common.Core.Tests verifying that `QueryInterface` 
  works for, currently, more than 1000 different COM interfaces.
- Added  ComImplTests.cpp to Harlinn.Common.Core.Tests verifying that 
  ```C++
  class ObjectImpl : public Com::ObjectBase<ObjectImpl, IEnumString, IEnumVARIANT>
  {
      int value_ = 0;
  public:
      virtual HRESULT __stdcall Next( ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched ) override;
      virtual HRESULT __stdcall Next( ULONG celt, VARIANT* rgVar, ULONG* pCeltFetched ) override;
      virtual HRESULT __stdcall Skip( ULONG celt ) override;
      virtual HRESULT __stdcall Reset( ) override;
      virtual HRESULT __stdcall Clone( IEnumString** ppenum ) override;
      virtual HRESULT STDMETHODCALLTYPE Clone( IEnumVARIANT** ppEnum ) override;
  };
  ```
  is a valid implementation of a COM object that implements both `IEnumString` and `IEnumVARIANT`.

  Demonstrating an implementation that is significantly simpler than alternative COM implementation
  frameworks.   
## 2022.01.13
- Added HCCComImpl.h to Harlinn.Common.Core:
  Classes used to implement COM objects.
- Added HCCComInterfaces.h to Harlinn.Common.Core: 
  
  ```C++
    template<typename ...InterfaceTypes>
    struct Interface : std::false_type
    {

    };

  ```
  With specializations for many common COM interfaces derived from:
  ```C++
    template<>
    struct Interface<IUnknown> : std::true_type
    {
        using InterfaceType = IUnknown;
        template<typename DerivedInterfaceType>
        static void* QueryInterface( const Guid& interfaceId, const DerivedInterfaceType* impl )
        {
            if ( interfaceId == __uuidof( InterfaceType ) )
            {
                auto* result = static_cast<InterfaceType*>( const_cast<DerivedInterfaceType*>( impl ) );
                return result;
            }
            else
            {
                return nullptr;
            }
        }
    };
  ```
  Specializations for interfaces derived from IUnknown are the implemented using this macro:
  ```C++
    #define HCC_COM_DEFINE_INTERFACE( Itf, BaseItf ) \
    template<>  \
    struct Interface<Itf> : Interface<BaseItf>  \
    {  \
        using Base = Interface<BaseItf>; \
        using InterfaceType = Itf;  \
        template<typename DerivedInterfaceType>  \
        static void* QueryInterface( const Guid& interfaceId, const DerivedInterfaceType* impl )  \
        {  \
            if ( interfaceId == __uuidof( InterfaceType ) )  \
            {  \
                auto* result = static_cast<InterfaceType*>( const_cast<DerivedInterfaceType*>( impl ) ); \
                return result; \
            }  \
            else  \
            { \
                return Base::QueryInterface<DerivedInterfaceType>( interfaceId, impl ); \
            }  \
        }  \
    }
  ```
  Which is then used to implement specializations of Interface<...> for COM interfaces like this:

  ```C++
    HCC_COM_DEFINE_INTERFACE( IEnumString, IUnknown );
    HCC_COM_DEFINE_INTERFACE( IClassFactory, IUnknown );
    HCC_COM_DEFINE_INTERFACE( ISequentialStream, IUnknown );
    HCC_COM_DEFINE_INTERFACE( IStream, ISequentialStream );
    HCC_COM_DEFINE_INTERFACE( IPersist, IUnknown );
    HCC_COM_DEFINE_INTERFACE( IPersistStream, IPersist );
    HCC_COM_DEFINE_INTERFACE( IEnumMoniker, IUnknown );
    HCC_COM_DEFINE_INTERFACE( IMoniker, IPersistStream );
        .
        .
        .

  ```
  


 
## 2022.01.12
- Verify that the solution builds
- Update Examples\\Windows\\DirectX2D\\EWDX2D01Demo
- Update Examples\\Windows\\DirectX2D\\EWDX2D02Primitives
## 2022.01.11
- Reimplemented IUnknownImplementation; fixing, among other things, a nasty bug in QueryInterface, 
- Continued reimplementing the support for Direct2D in HWGraphics.h, rewriting the follwing classes/templates in the Harlinn\:\:Windows\:\:Graphics namespace:
  - CommandSink2
  - GdiMetafile1
  - GdiMetafileSink1
  - SpriteBatch
  - DeviceContext3
  - Device3
  - Factory4
  - CommandSink3
  - SvgGlyphStyle
  - DeviceContext4
  - Device4
  - Factory5
  - CommandSink4
  - ColorContext1
  - SvgAttribute
  - SvgPaint
  - SvgStrokeDashArray
  - SvgPointCollection
  - SvgPathData
  - SvgElement
  - SvgDocument
  - DeviceContext5
  - Device5
  - Factory6
  - CommandSink5
  - DeviceContext6
  - Device6
  - Factory7
## 2022.01.10
- Continued reimplementing the support for Direct2D in HWGraphics.h, rewriting the follwing classes/templates in the Harlinn\:\:Windows\:\:Graphics namespace:
  - Device
  - Factory1
  - Multithread
  - GeometryRealization
  - DeviceContext1
  - Device1
  - Factory2
  - CommandSink1
  - InkStyle
  - Ink
  - GradientMesh
  - ImageSource
  - ImageSourceFromWic
  - TransformedImageSource
  - LookupTable3D
  - DeviceContext2
  - Device2
  - Factory3
## 2022.01.09
- Continued reimplementing the support for Direct2D in HWGraphics.h, rewriting the follwing classes/templates in the Harlinn\:\:Windows\:\:Graphics namespace:
  - DeviceContextRenderTarget
  - Factory
  - GdiMetafileSink
  - ID2D1GdiMetafileSinkImplementationBase
  - GdiMetafile
  - CommandSink
  - ID2D1CommandSinkImplementationBase
  - CommandList
  - PrintControl
  - ImageBrush
  - BitmapBrush1
  - StrokeStyle1
  - PathGeometry1
  - Properties
  - Effect
  - Bitmap1
  - GradientStopCollection1
  - DrawingStateBlock1
  - DeviceContext
## 2022.01.08
- Moved support for DirectWrite out of HWGraphics.h and out of the Harlinn\:\:Windows\:\:Graphics namespace and into
  HWDWrite.h and into the Harlinn\:\:Windows\:\:DirectWrite namespace. 
- Reimplemented the support for Direct2D in HWGraphics.h, rewriting the follwing classes/templates in the Harlinn\:\:Windows\:\:Graphics namespace:
  - Resource
  - Image
  - ColorContext
  - Bitmap
  - GradientStopCollection
  - Brush
  - BitmapBrush
  - SolidColorBrush
  - LinearGradientBrush
  - RadialGradientBrush
  - StrokeStyle
  - Geometry
  - RectangleGeometry
  - RoundedRectangleGeometry
  - EllipseGeometry
  - GeometryGroup
  - TransformedGeometry
  - SimplifiedGeometrySink
  - ID2D1SimplifiedGeometrySinkImplementationBase
  - GeometrySink
  - ID2D1GeometrySinkImplementationBase
  - TessellationSink
  - ID2D1TessellationSinkImplementationBase
  - PathGeometry
  - Mesh
  - Layer
  - DrawingStateBlock
  - RenderTarget
  - BitmapRenderTarget
  - ControlRenderTarget
  - GdiInteropRenderTarget
  
  This rewrite provides better documentation, improved error handling, improved support 
  for working with raw COM interfaces, and an improved API compared to the API I created 
  back in 2012.  
## 2022.01.06/07
- Added new classes to Tools\\WMI\\CIMTool
  - Renderable
  - TreeNode
  - Command
  - CommandManager
  - Window
  - MenuItem
  - SubMenuItem
  - Menu
  - ClassObjectNode
  - NamespaceNode
  - Connection
  - ConnectionManager
  - ExplorerWindow
  - PropertiesWindow
  - FileMenu
  - EditMenu
  - ViewMenu
  - MainMenuBar
  - Main
## 2022.01.05
- Added new project Tools\\WMI\\CIMTool - A tool for exploring Windows Management Instrumentation (WMI) API implemented using ImGui.
## 2022.01.04
- Added new project Examples\\Core\\WMI\\HCCExampleSimpleWMIClient
- Added new project Examples\\Core\\WMI\\HCCExampleSimpleAsyncWMIClient
## 2022.01.03
- Added more classes for interfacing with the Windows Management Instrumentation (WMI) API
  - WbemMethodSignature
  - WbemMethod
## 2022.01.02
- Added classes for interfacing with the Windows Management Instrumentation (WMI) API
  - WbemProperty
  - WbemClassObject
  - WbemObjectAccess
  - WbemQualifierSet
  - WbemServices
  - WbemLocator
  - WbemObjectSink
  - EnumWbemClassObject
  - WbemCallResult
  - WbemContext
  - UnsecuredApartment
  - WbemUnsecuredApartment
  - WbemStatusCodeText
  - WbemBackupRestore
  - WbemBackupRestoreEx
  - WbemRefresher
  - WbemHiPerfEnum
  - WbemConfigureRefresher
  - WbemObjectSinkEx
  - WbemShutdown
  - WbemObjectTextSrc
  - MofCompiler
  - WbemPropertyProvider
  - WbemUnboundObjectSink
  - WbemEventProvider
  - WbemEventProviderQuerySink
  - WbemEventProviderSecurity
  - WbemEventConsumerProvider
  - WbemProviderInitSink
  - WbemProviderInit
  - WbemHiPerfProvider
  - WbemDecoupledRegistrar
  - WbemProviderIdentity
  - WbemDecoupledBasicEventProvider
  - WbemEventSink
  - WbemTransport
  - WbemLevel1Login
  - WbemConnectorLogin
  - WbemAddressResolution
  - WbemClientTransport
  - WbemClientConnectionTransport
  - WbemConstructClassObject
## 2022.01.01
- Added classes for interfacing with the Windows Location API
  - LocationReport
  - LatLongReport
  - CivicAddressReport
  - Location
  - LocationPower
  - DefaultLocation
  - DispLatLongReport
  - DispCivicAddressReport
  - LocationReportFactory
  - LatLongReportFactory
  - CivicAddressReportFactory
- Added classes for interfacing with the Windows sensor API
  - WpdSerializer
  - PortableDeviceValues
  - PortableDeviceKeyCollection
  - PortableDevicePropVariantCollection
  - PortableDeviceValuesCollection
  - SensorManager
  - LocationPermissions
  - SensorCollection
  - Sensor
  - SensorDataReport
  - SensorManagerEvents
  - SensorEvents
  - SensorManagerEventSinkBase
  - SensorManagerEventSink
  - SensorEventSinkBase
  - SensorEventSink
## 2021.12.29
- Added classes for serial port device I/O to Harlinn.Common.Core
  - DeviceControlBlock
  - CommConfig
  - SerialPort
  - SerialPorts
  - CommDeviceStream
  - CommDeviceRequest
  - ReadCommDeviceRequest
  - WriteCommDeviceRequest
  - CommDeviceHandler
  - CommDeviceDispatcher
- Added several backends to Harlinn.ImGui: DirectX 9 through 11: OpenGL 2 and 3; and Vulkan.
## 2021.12.28
- Updated Harlinn.ImGui to Docking branch after merge of master at version 1.86 and ImPlot to version 0.12
- Build fixes, rebuilding the entire solution for both Debug and release.
- Fixed missing exports from Harlinn.tiff while building Harlinn.gdal
## 2021.12.27
- Added new project Examples\\3rdParty\\bullet\\BulletBasicDemo
- Added bullet\\examples\\Importers to 3rdParty\\Harlinn.bullet
- Added bullet\\examples\\OpenGLWindow to 3rdParty\\Harlinn.bullet
- Added bullet\\examples\\Importers to 3rdParty\\Harlinn.bullet
- Added bullet\\Extras\\Serialize to 3rdParty\\Harlinn.bullet
- Added bullet\\Extras\\InverseDynamics to 3rdParty\\Harlinn.bullet
- Added bullet\\Extras\\HACD to 3rdParty\\Harlinn.bullet
- Added bullet\\Extras\\GIMPACTUtils to 3rdParty\\Harlinn.bullet
- Added bullet\\Extras\\ConvexDecomposition to 3rdParty\\Harlinn.bullet
- Added new project 3rdParty\\Harlinn.rtmidi
- Added new project 3rdParty\\Harlinn.gwen
- Added new project 3rdParty\\Harlinn.enet
- Added new project 3rdParty\\Harlinn.crossguid
- Added new project 3rdParty\\Harlinn.base64
- Added new project Tools\\3rdParty\\lua\\luac
- Added new project Tools\\3rdParty\\lua\\lua
- Added new project 3rdParty\\Harlinn.lua
- Added new project 3rdParty\\Harlinn.clsocket
## 2021.12.26
- Added new project 3rdParty\\Harlinn.BussIK
- Added new project 3rdParty\\Harlinn.glad
## 2021.12.23
- Added 31 tests to Tests\\3rdParty\\bullet\\Harlinn.bullet.tests
- Added new project Tests\\3rdParty\\bullet\\Harlinn.bullet.tests
## 2021.12.22
- Added new project 3rdParty\\Harlinn.Eigen
## 2021.12.21
- Added new project 3rdParty\\Harlinn.bullet
- Added new project 3rdParty\\Harlinn.tinyobjloader
- Added new project Examples\\3rdParty\\flatbuffers\\FlatbuffersGreeterClient
- Added new project Examples\\3rdParty\\flatbuffers\\FlatbuffersGreeterServer
- Added new project Tools\\3rdParty\\flatbuffers\\flatc
- Added new project 3rdParty\\Harlinn.flatbuffers
## 2021.12.20
- Updated Harlinn.Julia, required Julia version is now 1.7
- Added new project Tools\\3rdParty\\proj\\projinfo
- Added new project Tools\\3rdParty\\proj\\gie
- Added new project Tools\\3rdParty\\proj\\proj
- Added new project Tools\\3rdParty\\proj\\geod
- Added new project Tools\\3rdParty\\proj\\cs2cs
- Added new project Tools\\3rdParty\\proj\\projsync
- Added new project Tools\\3rdParty\\proj\\cct
## 2021.12.19
- Added new project Examples\\3rdParty\\rocksdb\\RocksDBOptimisticTransactionExample
- Added new project Examples\\3rdParty\\rocksdb\\RocksDBCompactionFilterExample
- Added new project Examples\\3rdParty\\rocksdb\\RocksDBCompactFilesExample
- Added new project Examples\\3rdParty\\rocksdb\\RocksDBColumnFamiliesExample
- Added new project Tools\\3rdParty\\rocksdb\\rocksdb_dump
- Added new project Tools\\3rdParty\\rocksdb\\rocksdb_undump
- Added new project Tools\\3rdParty\\rocksdb\\write_stress
- Added new project Tools\\3rdParty\\rocksdb\\trace_analyzer
- Added new project Tools\\3rdParty\\rocksdb\\sst_dump
- Added new project Tools\\3rdParty\\rocksdb\\io_tracer_parser
## 2021.12.18
- Added new project Tools\\3rdParty\\rocksdb\\db_sanity_test
- Added new project Tools\\3rdParty\\rocksdb\\db_repl_stress
- Added new project Tools\\3rdParty\\rocksdb\\db_bench
- Added new project Tools\\3rdParty\\rocksdb\\ldb
- Added new project Examples\\3rdParty\\rocksdb\\RocksDBSimpleExample2
- Modified 3rdParty\\Harlinn.rocksdb so that the Harlinn.rocksdb.dll now exports the C++ API.
## 2021.12.17
- Added new project Examples\\3rdParty\\rocksdb\\RocksDBSimpleExample
- Added new project Tools\\3rdParty\\rocksdb\\blob_dump
- Added new project Tools\\3rdParty\\rocksdb\\cache_bench
- Upgraded 3rdParty\\Harlinn.rocksdb to rocksdb 6.26.1
- Added 5 tests to Tools\\3rdParty\\gdal\\gdal_tests, for a total of 84 tests 
## 2021.12.16
- Added 79 tests to Tools\\3rdParty\\gdal\\gdal_tests
- Added gdal runtime datafiles to *Share\\gdal*
- Added proj runtime datafiles to *Share\\proj*
## 2021.12.15
- Added new project Harlinn.Java - A thin wrapper around the Java Native Interface. Locates jvm.dll dynamically. 
- Added new project Tools\\3rdParty\\gdal\\gdal_tests
## 2021.12.14
- Upgraded 3rdParty\\Harlinn.jxl to libjxl 0.6.1
- Upgraded 3rdParty\\Harlinn.gdal to gdal 3.4
- Upgraded 3rdParty\\Harlinn.tiff with modifications from gdal 3.4
- Added new project Tools\\3rdParty\\gdal\\dumpoverviews 
- Added new project Tools\\3rdParty\\gdal\\gdal_contour
- Added new project Tools\\3rdParty\\gdal\\gdal_create
- Added new project Tools\\3rdParty\\gdal\\gdal_grid
- Added new project Tools\\3rdParty\\gdal\\gdal_rasterize
- Added new project Tools\\3rdParty\\gdal\\gdal_translate
- Added new project Tools\\3rdParty\\gdal\\gdal_viewshed
- Added new project Tools\\3rdParty\\gdal\\gdal2ogr
- Added new project Tools\\3rdParty\\gdal\\gdaladdo
- Added new project Tools\\3rdParty\\gdal\\gdalasyncread
- Added new project Tools\\3rdParty\\gdal\\gdalbuildvrt
- Added new project Tools\\3rdParty\\gdal\\gdaldem
- Added new project Tools\\3rdParty\\gdal\\gdalenhance
- Added new project Tools\\3rdParty\\gdal\\gdalflattenmask
- Added new project Tools\\3rdParty\\gdal\\gdalinfo
- Added new project Tools\\3rdParty\\gdal\\gdallocationinfo
- Added new project Tools\\3rdParty\\gdal\\gdalmanage
- Added new project Tools\\3rdParty\\gdal\\gdalmdiminfo
- Added new project Tools\\3rdParty\\gdal\\gdalmultidimtranslate
- Added new project Tools\\3rdParty\\gdal\\gdalsrsinfo
- Added new project Tools\\3rdParty\\gdal\\gdaltindex
- Added new project Tools\\3rdParty\\gdal\\gdaltorture
- Added new project Tools\\3rdParty\\gdal\\gdaltransform
- Added new project Tools\\3rdParty\\gdal\\gdalwarp
- Added new project Tools\\3rdParty\\gdal\\gnmanalyse
- Added new project Tools\\3rdParty\\gdal\\gnmmanage
- Added new project Tools\\3rdParty\\gdal\\nearblack
- Added new project Tools\\3rdParty\\gdal\\ogr2ogr
- Added new project Tools\\3rdParty\\gdal\\ogrinfo
- Added new project Tools\\3rdParty\\gdal\\ogrlineref
- Added new project Tools\\3rdParty\\gdal\\ogrtindex
## 2021.12.12
- Added new project Tests\\3rdParty\\skia\\skia_test. A fair number of the tests 
  works, about 1500 of them, but then the test program terminates. As far as I
  have been able to determine, this seems to be related to the test code.
- Changed the build of 3rdParty\\Harlinn.skia to support Vulkan, 
  Open GL and DirectX 3D. Temporarily removed support for 3rdParty\\Harlinn.Angle
  in 3rdParty\\Harlinn.skia.