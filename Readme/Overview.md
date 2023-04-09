# Overview
This article describes Harlinn.Windows, a Visual Studio 2022 solution.

Before you can build the solution, please read [the build instructions](./Build.md) and configure 
your environment accordingly.  

## Introduction
Harlinn.Windows is a collection of libraries that I have put together that serves as a big part 
of the runtime we use at work. A few are my own; but most are; more or less, well-known open 
source libraries.

![Developed using Dear ImGui and ImPlot](./Images/ImGuiDemo2.png)

There are currently 522 projects in the solution, and this article provides a high-level overview of what's inside.

### Why did I not use cmake and vcpkg? 
This is a good question, and initially I tried to do just that, but there were some snags:
1. The size of the release build, using vcpkg, for grpc.lib was 325 MB; while the size of the release build of 
   Harlinn.grpc.dll is just 3.7 MB. Currently the combined size of all the native dlls created for a release 
   build of the solution is 118 MB.
2. Some packages relied on different versions of the same package, including their own private copy of a package.
3. Some packages were compiled with /sdl on, while others were not. I prefer to turn /sdl and /GS off for release builds, and on for debug builds.
   This may not be as significant as it used to, but you still get better performance when turning /sdl and /GS off. 
4. Many packages will not compile with: 
  - The **/std:c++latest** option, which *enables all currently implemented compiler and standard library features proposed for the next draft standard, as well as some in-progress and experimental features.*
6. Many packages creates static libraries, not dlls. 

Don't get me wrong; I think CMake and vcpkg are great tools, but putting everything into a 
single solution makes it easier, at least for me, to understand how everything is tied together. 

### Why put Harlinn in front of every dll name?
To avoid naming conflicts. I own the harlinn.com domain, so it is unlikely that anybody would, by accident, 
put Harlinn in front of the name of their dll.

### What about the unit tests? 
A few of those are included, but still just a fraction of those available for the original packages.

In particular, I've included many of the unit tests, that can be expected to compile on Windows, for: 
- Abseil - 4430 tests pass, 26 fails, and 12 tests are disabled
- boringssl
  - crypto_test - 910 tests pass, 0 fails, and 0 tests are disabled
  - ssl_test - 330 tests pass, 0 fails, and 0 tests are disabled
- gRPC - the tests are implemented as 94 separate executables, using multiple approaches to testing. 
  I think that the tests pass; but I am not certain, since much of the validation was performed manually.
- bullet - 31 tests pass, 0 fails, and 0 tests are disabled
- gdal - 84 tests pass, 0 fails, and 0 tests are disabled
- skia - A fair number of the tests works, about 1500 of them, but then the test program terminates. 
  As far as I have been able to determine, this seems to be related to the test code.
  


I've also created a fair number of tests for my own projects:

- **Harlinn.Common.Core.Tests:** 1175
- **Harlinn.Windows.Tests:** 271
- **Harlinn.OCI.Tests:** 49
- **Harlinn.ODBC.Tests:** 9
- **Harlinn.Timeseries.Tests:** 10
- **Harlinn.Julia.Tests:** 11
- **Harlinn.Common.Config.Tests:** 34
 
All tests can be found under the Tests folder.

### What about the examples?

So far I've included 202 example projects.

All Examples can be found under the Examples and DotNet\Examples folders.

### How stable is this?

This is a snapshot of the solution, and while most things seems to work, there are bound to be some snags. 
The most common problem will be a function or variable that is not exported from a dll, and there 
are probably other bugs too. Some, probably, created by yours truly. 

Still, with this solution you can now: 
- Create nice 2D effects:
 
  ![](./Images/HWSkiaShadowColorView.png)

- Create animated 3D visualizations:
 
  ![](./Images/HWSkiaSkottie3D.png)

- Learn a lot about some of the most widely used open source packages available, using Visual Studio 2022 and C++.

## Harlinn.Common.Core
Harlinn.Common.Core is a library packaged as a dll that provide 
functionality that is useful for most Windows C++ projects.
### Dependencies
1. The [boost](https://www.boost.org/) C++ libraries

### Other 3rd party code included in Harlinn.Common.Core
The Harlinn.Common.Core library contains code from a number of libraries:
1. The [\{fmt\}](https://github.com/fmtlib/fmt) library, version 8.0.1, by Victor Zverovich
2. The [xxHash](https://github.com/Cyan4973/xxHash) library, version 0.8.1 
3. The [CRC-32C (Castagnoli) for C++](https://github.com/robertvazan/crc32c-hw) library
4. The [xxhash_cx](https://github.com/masyos/xxhash_cx) library

### About ``char``, ``wchar_t``, ``signed char`` and ``unsigned char`` 
The library tries to treat ``char`` and ``wchar_t`` as types used for the sole purpose of representing
character data, while ``signed char`` and ``unsigned char`` are expected to represent signed and unsigned 8-bit integers, respectively. 

Normally this is not much of a problem, but consider:
```C++
constexpr char buffer1[] = { 1,2,3 };
constexpr unsigned char buffer2[] = { 1,2,3 };
constexpr char buffer3[] = "hello";
constexpr int buffer4[] = { 1,2,3 };
constexpr wchar_t_ buffer5[] = { 1,2,3 };
constexpr wchar_t_ buffer6[] = L"hello";
constexpr auto length1 = LengthOf( buffer1 );
constexpr auto length2 = LengthOf( buffer2 );
constexpr auto length3 = LengthOf( buffer3 );
constexpr auto length4 = LengthOf( buffer4 );
constexpr auto length5 = LengthOf( buffer5 );
constexpr auto length6 = LengthOf( buffer6 );
```
``LengthOf`` expects ``buffer1`` and ``buffer5`` to be zero-terminated; but since they are not, the compiler will not be able to evaluate ``LengthOf( buffer1 )`` and ``LengthOf( buffer5 )``.
``LengthOf( buffer3 )`` and ``LengthOf( buffer6 )`` evaluate to 5, while ``LengthOf( buffer2 )`` and ``LengthOf( buffer4 )`` evaluate to 3.

The code in *HCCPersistent.h*, which is used by the code in *HCCLogger.h*, relies on this, eliminating a significant number of calls to ``strlen`` and ``wcslen`` at runtime. 

### Main header files:
- **HCC7BitEncoding.h:** provides constexpr support for 7-bit encoded values.
- **HCCActiveObject.h:** provides:
  - ``template<typename DerivedT> class ActiveObject``: 
   
    An [active object](https://en.wikipedia.org/wiki/Active_object) implementation based on ``ConcurrentQueue<>``. 
- **HCCApplication.h:** provides:
  - ``class Application``:
  
    Every program needs to create one, and only one, instance of this class, or a class derived from this class.
    ```C++
    int main( int argc, char* argv[], char* envp[] )
    {
        Harlinn::Common::Core::ApplicationOptions options;
        options.Load( );
        Harlinn::Common::Core::Application application( options );
        application.Start( );
    
        // your code goes here, perhaps:
        int result = foo( );

        application.Stop( );
        return result;
    }
    ```
    Currently this configures, starts and stops the logging back-end on behalf of the program.
    
- **HCCArray.h:** provides:
  - ``template<typename T, size_t N> ArrayEx``: 
   
    A template derived from std::array that supports constexpr concatenation using operator +.
  - ``template<typename T, size_t N> class Array``: 
   
    An alternative to std::array that supports constexpr concatenation using operator +.
  - ``template<size_t N> class ByteArray``: 
   
    A template that supports constexpr serialization of binary data. 
  - ``template<size_t N, bool networkByteOrder = false, bool use7BitEncodedSize = true> class ArrayReader``: 
    
    A template that implements constexpr deserialization of data.
  - ``template<size_t N, bool networkByteOrder = false, bool use7BitEncodedSize = true> class ArrayWriter``: 
    
    A template that implements constexpr serialization of data.
- **HCCBinaryReader.h:** provides:
  - ``BinaryReaderBase``:
    ```C++
    template<typename Derived, 
            bool networkByteOrder, 
            bool use7BitEncodedSize>
    class BinaryReaderBase
    ```
    A template that can be used to deserialize binary data.
  - ``BufferedBinaryReader``:
    ```C++
    template<typename StreamT, 
            size_t BufferSizeValue, 
            bool networkByteOrder = false, 
            bool use7BitEncodedSize = true> 
    class BufferedBinaryReader
    ```
    A template that can be used to deserialize binary data from a stream using an internal buffer.
  - ``BinaryReader``: 
    ```C++ 
    template< IO::StreamReader StreamT, 
            bool networkByteOrder = false, 
            bool use7BitEncodedSize = true >
    class BinaryReader
    ```
    A template that can be used to deserialize binary data from a stream.
- **HCCBinaryWriter.h:** provides:
  - ``BinaryWriterBase``:
    ```C++
    template<typename Derived, 
            bool networkByteOrder, 
            bool use7BitEncodedSize>
    class BinaryWriterBase
    ```
    A template that can be used to serialize binary data.
  - ``BufferedBinaryWriter``:
    ```C++
    template<IO::StreamWriter StreamWriterT, 
            size_t BufferSizeValue, 
            bool networkByteOrder = false, 
            bool use7BitEncodedSize = true >
    class BufferedBinaryWriter
    ```
    A template that can be used to serialize binary data to a stream using an internal buffer.
  - ``BinaryWriter``: 
    ```C++ 
    template<IO::StreamWriter StreamT, 
            bool networkByteOrder = false, 
            bool use7BitEncodedSize = true>
    class BinaryWriter
    ```
    A template that can be used to serialize binary data to a stream.
- **HCCBuffer.h:** provides ``Blocks::Stream`` a block oriented memory stream.
- **HCCCom.h:** provides:
  - ``class Unknown``: A wrapper for the [``IUnknown``](https://docs.microsoft.com/en-us/windows/win32/api/unknwn/nn-unknwn-iunknown) interface.
  - ``template<typename T> class UnknownPtr``: A generic smart pointer for [COM](https://docs.microsoft.com/en-us/windows/win32/com/component-object-model--com--portal) interfaces.
  - ``template< class InterfaceType > class IUnknownImplementation``: An implementation of the [``IUnknown``](https://docs.microsoft.com/en-us/windows/win32/api/unknwn/nn-unknwn-iunknown) interface.
- **HCCConverters.h:** provides various overloads of: 
  ```C++
    template <typename ResultType, typename ArgumentType>
    inline ResultType ConvertTo( ArgumentType arg )
  ```
  implementing efficient and 'safe' conversion between basic data types.
- **HCCCRC.h:** provides a few ways of calculating the CRC value for data.
- **HCCCrypto.h:** provides functionality for working with certificates.
- **HCCCurrency.h:** declares the ``Currency`` class.
- **HCCDateTime.h:** provides functionality for handling date and time, declares:
  - ``class TimeSpan``
  - ``class DateTime``
  - ``class Stopwatch``
- **HCCEnvironment.h:** provides easy access to system information
- **HCCEse.h:** provides C++ classes for working with the [Extensible Storage Engine](https://docs.microsoft.com/en-us/windows/win32/extensible-storage-engine/extensible-storage-engine)
- **HCCException.h:** provides a wide range of exception classes.
- **HCCGuid.h:** functionality for working with UUIDs/GUIDs, declares ``class Guid``.
- **HCCHandle.h:** declares ``template<typename DerivedT, typename HandleT> class Handle``
- **HCCHTTP.h:** provides C++ classes for working with the [HTTP Server API](https://docs.microsoft.com/en-us/windows/win32/http/http-api-start-page).
- **HCCIO.h:** provides file, directory, and stream I/O related C++ classes. 
- **HCCIOContext.h:** declares:
  - ``class Context``: uses a thread-pool to process asynchronous I/O for an [I/O completion port](https://docs.microsoft.com/en-us/windows/win32/fileio/i-o-completion-ports) 
  - ``class ContextHandler``: An instance of the ``Context`` class delegates the work for a particular OS 
    handle to the ``Process`` override implemented for a class derived from ``ContextHandler``. 
  - ``template<typename DerivedT> FileHandler``: A template derived from ``ContextHandler`` used to perform file related asynchronous I/O.
  - ``class FileRequest``: Base class for file related asynchronous I/O requests.
  - ``class ReadFileRequest``: Represents an asynchronous file read request.
  - ``class WriteFileRequest``: Represents an asynchronous file write request.
  - ``class FileDispatcher``: Derived from ``FileHandler``, broadcasts I/O completion events to callbacks attached to ``boost::signals2::signal<>`` handlers.
- **HCCLib.h:** provides a number of useful funtions:
  - ``ByteSwap``: 
    ```C++
    template<typename T>
        requires IsInteger<std::remove_cvref_t<T>>
    inline constexpr T ByteSwap( T value )
    ```
    Swaps the bytes of the argument, which must be some type of integer. Performs this operation, if possible, at compile-time. 
    If the operation must be performed at runtime, the implementation will call _byteswap_ushort, _byteswap_ulong, _byteswap_uint64, 
    or just return the argument; based on the byte size of the argument type. ``ByteSwap`` for ``float``, ``double`` and enums are 
    implemented as:
    ```C++
    template<typename T>
        requires (IsFloatingPoint<std::remove_cvref_t<T>> || std::is_enum_v<std::remove_cvref_t<T>> )
    inline constexpr T ByteSwap( const T value ) noexcept
    {
        using Type = std::remove_cvref_t<T>;
        using UIntType = MakeUnsigned<Type>;
        std::bit_cast<Type>( ByteSwap( std::bit_cast<UIntType>( value ) ) );
    }
    ```
  - ``BitMask``:
    ```C++
    template<size_t N>
    struct BitMask
    {
        using type = ...
        static constexpr type value = ...;
    };
    ```
    ``BitMask::type``: is the type of the smallest unsigned integer capable of holding a bit-mask of N bits, where N <= 64.

    ``BitMask::value``: is the value of the bit-mask with the N lowest bits set to 1.
  - ``LengthOf``: returns the number of elements in an array, length of a char or wchar_t zero-terminated string, or the number 
    of elements in a container.
  - ``template<typename T> inline int Compare( T v1, T v2 ) noexcept``: compares two arguments of the same basic type, returning ``< 0`` if the first 
    value is considered to be less than the second; ``0`` if they are considered equal, and otherwise ``> 0``. For ``char`` or ``wchar_t`` 
    zero-terminated strings, ``nullptr`` is considered equal to a string with ``0`` length. 
  - ``AreNearlyEqual``: 
    ```C++
    template<typename T>
        requires std::is_floating_point_v<T>
    constexpr bool AreNearlyEqual( T a, T b, T smallNumber = static_cast<T>( 0.0001 ) ) noexcept
    ``` 
    returns ``true`` if the absolute value of the difference between ``a`` and ``b`` is less than ``smallNumber``. 
  - ``class XXH64Hasher``: use this class to incrementally generate a hash value from multiple inputs.
  - ``IsPowerOfTwo``: returns ``true`` if an integer is a power of ``2``.
  - ``NextPowerOfTwo``: returns the next higher value, that is a power of 2, greater than the argument. 
- **HCCLMDB.h:** declares a set of C++ classes for working with [LMDB](https://www.symas.com/lmdb) based on *3rdParty\\Harlinn.LMDB*.
- **HCCLogger.h:** logger implementation.
- **HCCLogging.h:** preprocessor macros used for logging.
- **HCCMath.h:** constexpr math, namespace: ``Harlinn::Common::Core::Math`` 
  - ``IsSameValue``:
    ```C++
    constexpr bool IsSameValue( double x, double y ) noexcept;
    constexpr bool IsSameValue( float x, float y ) noexcept;
    ```
    Returns ``true`` if ``x`` and ``y`` holds the same value, even if they hold ``NaN`` values. 
  - ``IsZero``:
    ```C++
    constexpr bool IsZero( double x ) noexcept;
    constexpr bool IsZero( float x ) noexcept;
    ```
    Returns true if ``x`` is ``0.0`` or ``-0.0``.
  - ``signum``:
    ```C++
    template< typename T>
        requires IsUnsignedInteger<std::remove_cvref_t<T>> || IsBoolean<std::remove_cvref_t<T>>
    inline constexpr T signum( T val ) noexcept;

    template< typename T>
        requires IsSignedInteger<std::remove_cvref_t<T>>
    inline constexpr T signum( T val ) noexcept;

    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    inline constexpr T signum( T val ) noexcept;
    ```
    Indicates the sign of ``val``, returning ``-1``, ``0``, or ``+1``.
  - ``Deg2Rad``:
    ```C++
    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    inline constexpr std::remove_cvref_t<T> Deg2Rad( T angleInDegrees ) noexcept;
    ```
    Convert ``angleInDegrees`` from degrees to radians.
  - ``Rad2Deg``:
    ```C++
    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    inline constexpr std::remove_cvref_t<T> Rad2Deg( T angleInRadians ) noexcept;
    ```
    Convert ``angleInRadians`` from radians to degrees.
  - ``NextAfter``:
    ```C++
    inline constexpr double NextAfter( double x, double y ) noexcept;
    inline constexpr double NextAfter( float x, float y ) noexcept;
    ```
    Returns the next representable value of x in the direction of y.
  - ``NextDown``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextDown( T x ) noexcept;
    ```
    Returns the next representable value of x in the direction of negative infinity.
  - ``NextUp``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextUp( T x ) noexcept;
    ```
    Returns the next representable value of x in the direction of positive infinity.
  - ``IsNaN``:
    ```C++
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsNaN( T val ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsNaN( T val ) noexcept;
    ```
    Returns ``true`` if ``val`` is ``NaN``.
  - ``IsInf``:
    ```C++
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsInf( T val ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsInf( T val ) noexcept;
    ```
    Returns ``true`` if ``val`` is infinite.
  - ``Abs``:
    ```C++
    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;

    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T> 
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;
    ```
    Returns the absolute value of ``val``.
  - ``SignBit``:
    ```C++
    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept;

    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool SignBit( T val ) noexcept;
    ```
    Returns ``true`` if the value of the sign of ``val`` is negative, otherwise ``false``.
  - ``FRExp``:
    ```C++
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::pair<double,int> FRExp( T val ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::pair<double,int> FRExp( T val ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline double FRExp( T val, int* exp ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int* exp ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline double FRExp( T val, int& exp ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int& exp ) noexcept;
    ```
    Return ``(result,exp)`` such that ``result`` has a magnitude in the interval ``[1/2, 1)`` or ``0``, and val is equal to ``result`` * ``2``<sup>``exp``</sup>.
  - ``ModF``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::pair<std::remove_cvref_t<T>, std::remove_cvref_t<T>> ModF( T val ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ModF( T val, T* integerPart ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ModF( T val, T& integerPart ) noexcept;
    ```
    Return a ``std::pair<T,T>`` of the fractional and integral parts of a number. Both parts have the same sign as the argument.
  - ``Min``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept;
    ```
    Returns the smaller of the argument values.
  - ``Max``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept;
    ```
    Returns the greater of the argument values.
  - ``Trunc``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T val ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T val ) noexcept;
    ```
    Returns the nearest integral value of the same type as ``val`` whose absolute value is less than or equal to the absolute value of ``val``.
  - ``Floor``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Floor( T val ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Floor( T val ) noexcept;
    ```
    Returns the nearest integral value of the same type as ``val`` that is less than or equal to ``val``.
  - ``Ceil``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T val ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T val ) noexcept;
    ```
    Returns the nearest integral value of the same type as ``val`` that is greater than or equal to ``val``.
  - ``Round``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Round( T val ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Round( T val ) noexcept;
    ```
    Returns ``val`` rounded to the nearest integral value.
  - ``Clamp``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Clamp( T val, T minimumValue, T maximumValue ) noexcept;

    template<typename T>
        requires ( IsInteger<T> )
    constexpr inline std::remove_cvref_t<T> Clamp( T val, T minimumValue, T maximumValue ) noexcept;
    ```
    If ``val`` compares less than ``minimumValue``, returns ``minimumValue``; otherwise if ``maximumValue`` compares 
    less than ``val``, returns ``maximumValue``; otherwise returns ``val``.
  - ``Lerp``:
    ```C++
    template<typename T, typename U>
        requires ( ( IsInteger<T> || IsFloatingPoint<T> ) && ( IsInteger<U> || IsFloatingPoint<U> ) )
    constexpr inline std::conditional_t<IsFloatingPoint<T>, T, std::conditional_t<IsFloatingPoint<U>, U, T>> Lerp( T a, T b, U t ) noexcept;
    ```
    Computes the linear interpolation between ``a`` and ``b`` for the parameter ``t`` (or extrapolation, when ``t`` is 
    outside the range [0,1]).
  - ``CopySign``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> CopySign( T magnitude, T signValue ) noexcept;
    ```
    Returns a value with the magnitude of ``magnitude`` and the sign of ``signValue``.
  - ``ScaleByN``:
    ```C++
    inline constexpr double ScaleByN( double x, int n ) noexcept;
    inline constexpr double ScaleByN( float x, int n ) noexcept;
    ```
    Multiplies a floating point value ``x`` by ``FLT_RADIX`` raised to power ``n``.
  - ``FMod``:
    ```C++
    inline constexpr double FMod( double x, double y ) noexcept;
    inline constexpr float FMod( float x, float y ) noexcept;
    ```
    Computes the floating-point remainder of the division operation ``x``/``y``.
  - ``Exp``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Exp( T x ) noexcept;
    ```
    Computes [e (Euler's number, 2.7182818)](https://en.wikipedia.org/wiki/E_(mathematical_constant)) raised to the given power of ``x``.
  - ``Hypot``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Hypot( T x, T y ) noexcept;
    ```
    Computes the [hypotenuse](https://en.wikipedia.org/wiki/Hypotenuse).
  - ``Log``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log( T x ) noexcept;
    ```
    Computes the natural (base [e](https://en.wikipedia.org/wiki/E_(mathematical_constant))) logarithm of ``x``.
  - ``Log2``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log2( T x ) noexcept;
    ```
    Computes the base 2 logarithm of ``x``.
  - ``Log10``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log10( T x ) noexcept;
    ```
    Computes the base 10 logarithm of ``x``.
  - ``Sin``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Sin( T x ) noexcept;
    ```
    Computes the sine of ``x``, where ``x`` is in radians.
  - ``ASin``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ASin( T x ) noexcept;
    ```
    Computes the inverse sine of ``x``, in radians.
  - ``Cos``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Cos( T x ) noexcept;
    ```
    Computes cosine of ``x``, where ``x`` is in radians.
  - ``ACos``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ACos( T x ) noexcept;
    ```
    Computes the inverse cosine of ``x``, with the result in radians.
  - ``Tan``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Tan( T x ) noexcept;
    ```
    Computes tangent of ``x``, where ``x`` is in radians.
  - ``ATan``, ``ATan2``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x ) noexcept;
    
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x, T y ) noexcept

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan2( T x, T y ) noexcept
    ```
    Compute the inverse tangent of ``y`` or ``y``/``x``, respectively.
  - ``SinCos``:
    ```C++
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr void SinCos( T x, T& sinResult, T& cosResult ) noexcept;
    ```
    Simultaneously compute the sine and cosine of ``x``, where ``x`` is in radians.
- **HCCObj.h:** provides wrapper C++ classes for a wide range of Windows COM interfaces.
- **HCCObjBase.h:** provides wrapper C++ classes for central Windows COM interfaces.
- **HCCObservable.h:** declares ``template<typename DerivedT> class Observable`` and a couple macros that can be used to implement observable properties.
- **HCCPersistent.h:** provides a flexible and efficient serialization and deserialization mechanism. 
- **HCCPersistentDecoder.h:** provides a generic decoder for data serialized using the mechanism provided in *HCCPersistent.h*. 
- **HCCPipe.h:** Synchronous and synchronous I/O using named pipes.
- **HCCProcess.h:** classes for working with Windows processes. 
- **HCCPropSys.h:** classes for working with the (Windows Property System)[https://docs.microsoft.com/en-us/windows/win32/api/_properties/]
- **HCCReference.h:** support for intrusive reference counted objects.
- **HCCSecurity.h:** classes for working with [Windows Security and identity](https://docs.microsoft.com/en-us/windows/apps/develop/security-and-identity) 
- **HCCShell.h:** classes for working with the [Windows Shell API](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb773177(v=vs.85)).
- **HCCSocket.h:** Synchronous and synchronous I/O using sockets.
- **HCCSync.h:** classes for working with synchronization.
- **HCCThread.h:** classes for working with threads.
- **HCCTraits.h:** useful meta programming features.
- **HCCTuple.h:** yet another tuple implementation. 
- **HCCVariant.h:** provides functionality for working with the [VARIANT](https://docs.microsoft.com/en-us/windows/win32/winauto/variant-structure) structure.
- **HCCVector.h:** yet another vector implementation.
- **HCCXml.h:** classes for working with the [MSXML SDK](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ms760399(v=vs.85)).

## Harlinn.Windows
Harlinn.Windows provides functionality for developing user interfaces in C++. 

It is used to implement 73 of the examples.

### Main header files:
- **HWDXGI.h:** provides support for the [DirectX Graphics Infrastructure API](https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/dx-graphics-dxgi).
- **HWGraphicsD3D12.h:** provides support for the [Direct3D 12 API](https://docs.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-graphics).
- **HWGraphics.h:** provides support for the [Direct2D API](https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-portal).
- **HWImaging.h:** provides support for the [Windows Imaging Component API](https://docs.microsoft.com/en-us/windows/win32/wic/-wic-lh)
- **HWHandles.h:** provides support for the [Windows GDI API](https://docs.microsoft.com/en-us/windows/win32/gdi/windows-gdi).
- **HWControl.h:** provides support for working with [Windows Controls](https://docs.microsoft.com/en-us/windows/win32/controls/window-controls)
- **HWMessage.h:** provides the Message class, a simple abstraction for the [MSG structure](https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-msg)
- **HWMenu.h:** provides support for working with [Windows Menus](https://docs.microsoft.com/en-us/windows/win32/menurc/menus).
- **HWForm.h:** provides support for working with top level Windows Controls using the Form class.
- **HWApplication.h:** provides an Application class and a MessageLoop class.
- **HWDXApplication.h:** declares some Direct3D 12 utility classes:
  - ``class DXMessageLoop``: The render/message loop.
  - ``class DXContext``: Initializes and manages interaction with the ``D3D12Device``, the ``DXGI::SwapChain3``, the ``D3D12GraphicsCommandList``, and the few other objects required for interaction with the Direct3D 12 API.
  - ``class DXApplication``: Derived from ``Windows::Application``, tailored for developing Direct3D 12 using ``Windows::Form``.
- **HWStdCtrls.h:** provides a number of classes for working with standard Windows controls. The provided functionality is, unfortunately, quite limited.
- **HWFileDialog.h:** provides support for the *Open* and *Save As* functionality from the [Common Dialog Box Library](https://docs.microsoft.com/en-us/windows/win32/dlgbox/common-dialog-box-library).
- **HWEnvironment.h:** provides easy access to system information.
- **HWSkia.h:** provides support for creating [Skia](https://skia.org/) based applications.
- **HWImGui.h:** provides support for creating [Dear ImGui](https://github.com/ocornut/imgui) based applications.

*HWControl.h*, *HWMessage.h*, *HWMenu.h*, *HWForm.h*, *HWApplication.h*, *HWStdCtrls.h*, *HWFileDialog.h*, *HWSkia.h* are meant to 
be used together, while *HWDXGI.h*, *HWGraphicsD3D12.h*, *HWGraphics.h*, *HWImaging.h* and *HWHandles.h* can be used on their own.

These days I often use the slightly modified version of [Dear ImGui](https://github.com/ocornut/imgui) and [ImPlot](https://github.com/epezent/implot) located under
3rdParty\\Harlinn.ImGui to create user interfaces for my *Harlinn\:\:Windows\:\:Form* based applications. 

![](./Images/ImGuiDemo.png)


```C++
#include "HWDXApplication.h"
#include "HWImGui.h"
#include "HWmenu.h"
#include "HWstdctrls.h"
#include <iostream>

using namespace Harlinn;

int main()
{
    try
    {
        Windows::ApplicationOptions applicationOptions;
        applicationOptions.Load( );
        Windows::ImGui::Application application( applicationOptions );
        application.Start( );

        Windows::ImGui::Form form;
        form.SetText( L"ImGui & ImPlot Demo" );

        bool showImGuiDemoWindow = true;
        bool showImPlotDemoWindow = true;
        bool showAnotherWindow = false;

        form.OnRender.connect( [&showImGuiDemoWindow,&showImPlotDemoWindow, &showAnotherWindow]( Windows::ImGui::Form* sender )
        {
            if ( showImGuiDemoWindow )
            {
                ImGui::ShowDemoWindow( &showImGuiDemoWindow );
            }
            if ( showImPlotDemoWindow )
            {
                ImPlot::ShowDemoWindow( &showImPlotDemoWindow );
            }

        } );

        auto result = application.Run( form );

        application.Stop( );

        return result;
    }
    catch ( std::exception& exc )
    {
        std::cout << exc.what( ) << std::endl;
    }
    catch ( ... )
    {
        std::cout << "Unknown exception" << std::endl;
    }
    return 0;
}
```


## Harlinn.OCI
Harlinn.OCI provides high performance access to the Oracle RDBMS using the [Oracle OCI API](https://docs.oracle.com/en/database/oracle/oracle-database/19/lnoci/introduction.html)

## Harlinn.ODBC
Harlinn.ODBC provides high performance access to database servers and engines through the ODBC API.

## Harlinn.Common.Config
This library implements an in-memory hierarchical storage suitable for handling configuration information. 

## Harlinn.Julia
This library provides easy access to [Julia](https://julialang.org/).

## 3rd party libraries
This solution contains a few useful C and C++ libraries located under the 3rdParty folder.

Header only libraries are contained within ''Static library (.lib)'' projects, everything else creates a dll.

All C++ code compiles using [/std:c++latest](https://docs.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version?view=msvc-170) and [/Zc:__cplusplus](https://docs.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-170)

### [abseil](https://abseil.io/)
**Version:** 20210324.2

**Description:**
> Abseil is an open source collection of C++ libraries drawn from the most fundamental pieces of Google’s 
> internal code-base. These libraries are the nuts-and-bolts that underpin almost everything Google runs. 
> Bits and pieces of these APIs are embedded in most of our open source projects, and Abseil aims to bring 
> them together into one comprehensive project. Abseil encompasses the most basic building blocks of Google’s 
> code-base: code that is production-tested and will be fully maintained for years to come.

**Projects:** 
- Harlinn.abseil
- Tests\\3rdParty\\abseil\\abseil_test

The abseil_test contains the unit tests for the Harlinn.abseil project

### [libaec - Adaptive Entropy Coding library](https://github.com/erget/libaec)
**Version:** master as of 2021.08.26

**Description:**
> Libaec provides fast lossless compression of 1 up to 32 bit wide signed or unsigned integers (samples). 

**Project:** Harlinn.aec



### [Alliance for Open Media - AV1 Codec Library](https://aomedia.googlesource.com/aom)
**Version:** 3.1.2 

**Description:**
> AV1 Codec Library

**Project:** Harlinn.aom


### [Armadillo: C++ Library for Linear Algebra & Scientific Computing](http://arma.sourceforge.net)
**Version:** 10.6.x

**Description:**
> Armadillo is a high quality linear algebra library (matrix maths) for the C++ language, aiming towards a good balance between speed and ease of use
>  
> Provides high-level syntax and functionality deliberately similar to Matlab
>  
> Useful for algorithm development directly in C++, or quick conversion of research code into production environments
>  
> Provides efficient classes for vectors, matrices and cubes; dense and sparse matrices are supported
>  
> Integer, floating point and complex numbers are supported
>  
> A sophisticated expression evaluator (based on template meta-programming) automatically combines several operations to increase speed and efficiency
>  
> Various matrix decompositions (eigen, SVD, QR, etc) are provided through integration with LAPACK, or one of its high performance drop-in replacements (eg. MKL or OpenBLAS)
>  
> Can automatically use OpenMP multi-threading (parallelisation) to speed up computationally expensive operations
>  
> Distributed under the permissive Apache 2.0 license, useful for both open-source and proprietary (closed-source) software
>  
> Can be used for machine learning, pattern recognition, computer vision, signal processing, bioinformatics, statistics, finance, etc

**Project:** Harlinn.armadillo

### [cpp-base64](https://github.com/ReneNyffenegger/cpp-base64)
**Version:** 2.0.rc8

**Description:**
> Base64 encoding and decoding with c++.

**Project:** Harlinn.base64

### [BoringSSL](https://boringssl.googlesource.com/boringssl/)
**Version:** master as of 2021.09.20

**Description:**
> BoringSSL is a fork of OpenSSL that is designed to meet Google's needs.

**Projects:** 
- Harlinn.boringssl
- Tests\\3rdParty\\boringssl\\crypto_test
- Tests\\3rdParty\\boringssl\\ssl_test

### [Brotli](https://github.com/google/brotli)
**Version:** master as of 2021.08.04

**Description:**
> Brotli is a generic-purpose lossless compression algorithm that compresses data using a combination of a modern variant 
> of the LZ77 algorithm, Huffman coding and 2nd order context modeling, with a compression ratio comparable to the best 
> currently available general-purpose compression methods. It is similar in speed with deflate but offers more dense compression.

**Project:** Harlinn.brotli

### [Bullet Physics SDK](https://github.com/bulletphysics/bullet3)
**Version:** 3.21

**Description:**
> Real-time collision detection and multi-physics simulation for VR, games, visual effects, robotics, machine learning etc.

**Project:** Harlinn.bullet

### [Inverse Kinematics](http://www.math.ucsd.edu/~sbuss/ResearchWeb/ikmethods/index.html)
**Version:** from bullet 3.21

**Description:**
> Selectively Damped Least Squares for Inverse Kinematics.

**Project:** Harlinn.BussIK

### [bzip2](https://gitlab.com/bzip2/bzip2/)
**Version:** 1.0.8

**Description:**
> bzip2 is a freely available, patent free (see below), high-quality data compressor. It typically 
> compresses files to within 10% to 15% of the best available techniques (the PPM family of statistical 
> compressors), whilst being around twice as fast at compression and six times faster at decompression.

**Project:** Harlinn.bzip2

### [c-ares is a C library for asynchronous DNS requests (including name resolves)](https://c-ares.org/)
**Version:** 1.17.0

**Description:**
> c-ares is a C library for asynchronous DNS requests (including name resolves)

**Project:** Harlinn.c-ares

### [CFITSIO - A FITS File Subroutine Library](https://heasarc.gsfc.nasa.gov/fitsio/)
**Version:** 4.0.0

**Description:**
> CFITSIO is a library of C and Fortran subroutines for reading and writing data files in FITS 
> (Flexible Image Transport System) data format. CFITSIO provides simple high-level routines for 
> reading and writing FITS files that insulate the programmer from the internal complexities of 
> the FITS format. CFITSIO also provides many advanced features for manipulating and filtering 
> the information in FITS files.

**Project:** Harlinn.cfitsio

### [Advanced DXTn texture compression library](https://github.com/BinomialLLC/crunch)
**Version:** 1.04

**Description:**
> crnlib is a lossy texture compression library for developers that ship content using the DXT1/5/N 
> or 3DC compressed color/normal map/cubemap mipmapped texture formats.
>
> It can compress mipmapped 2D textures, normal maps, and cubemaps to approx. 1-1.25 bits/texel, and 
> normal maps to 1.75-2 bits/texel. The actual bitrate depends on the complexity of the texture itself, 
> the specified quality factor/target bitrate, and ultimately on the desired quality needed for a 
> particular texture.

**Project:** Harlinn.crnlib

### [clsocket](https://github.com/DFHack/clsocket)
**Version:** 1.41.1

**Description:**
> Provides a mechanism for writing cross platform socket code. This library was originally written 
> to only support blocking TCP sockets. Over the years it has been extended to support UDP and RAW 
> sockets as well.

**Project:** Harlinn.clsocket

### [crossguid](https://github.com/graeme-hill/crossguid)
**Version:** 0.2.2

**Description:**
> CrossGuid is a minimal, cross platform, C++ GUID library. It uses the best native GUID/UUID generator 
> on the given platform and has a generic class for parsing, stringifying, and comparing IDs. The guid 
> generation technique is determined by your platform.

**Project:** Harlinn.crossguid

### [libcurl - the multiprotocol file transfer library](https://curl.se/libcurl/)
**Version:** 7.78.0

**Description:**
> libcurl is a free and easy-to-use client-side URL transfer library, supporting DICT, FILE, FTP, FTPS, 
> GOPHER, GOPHERS, HTTP, HTTPS, IMAP, IMAPS, LDAP, LDAPS, MQTT, POP3, POP3S, RTMP, RTMPS, RTSP, SCP, 
> SFTP, SMB, SMBS, SMTP, SMTPS, TELNET and TFTP. libcurl supports SSL certificates, HTTP POST, HTTP PUT, 
> FTP uploading, HTTP form based upload, proxies, HTTP/2, HTTP/3, cookies, user+password authentication 
> (Basic, Digest, NTLM, Negotiate, Kerberos), file transfer resume, http proxy tunneling and more!

**Project:** Harlinn.curl

### [D3D12 Memory Allocator](https://github.com/GPUOpen-LibrariesAndSDKs/D3D12MemoryAllocator)
**Version:** 2.0.0-development (2021-07-26)

**Description:**
> Easy to integrate memory allocation library for Direct3D 12

**Project:** Harlinn.d3d12allocator

### [libdeflate](https://github.com/ebiggers/libdeflate)
**Version:** 1.8

**Description:**
> libdeflate is a library for fast, whole-buffer DEFLATE-based compression and decompression

**Project:** Harlinn.deflate

### [Adobe Digital Negative (DNG) SDK](https://helpx.adobe.com/camera-raw/digital-negative.html)
**Version:** 1.5.1

**Description:**
> The DNG SDK provides support for reading and writing DNG files as well as for converting DNG 
> data to a format that is easily displayed or processed by imaging applications.

**Project:** Harlinn.dngsdk

### [Effcee](https://github.com/google/effcee)
**Version:** main as of 2021.09.27

**Description:**
> Effcee is a C++ library for stateful pattern matching of strings, inspired by LLVM's FileCheck command.

**Project:** Harlinn.effcee

### [Eigen](https://eigen.tuxfamily.org/)
**Version:** 3.4.0

**Description:**
> Eigen is a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.

**Project:** Harlinn.Eigen

### [ENet](https://github.com/lsalzman/enet)
**Version:** 1.3.17

**Description:**
> ENet's purpose is to provide a relatively thin, simple and robust network communication layer on top of UDP 
> (User Datagram Protocol).The primary feature it provides is optional reliable, in-order delivery of packets.

**Project:** Harlinn.enet


### [Expat](https://github.com/libexpat/libexpat)
**Version:** 2.4.1

**Description:**
> This is Expat, a C library for parsing XML, started by James Clark in 1997. Expat is a stream-oriented 
> XML parser. This means that you register handlers with the parser before starting the parse. These 
> handlers are called when the parser discovers the associated structures in the document being parsed. 
> A start tag is an example of the kind of structures for which you may register handlers.

**Project:** Harlinn.expat

### [FlatBuffers](https://google.github.io/flatbuffers/)
**Version:** 2.0.0

**Description:**
> FlatBuffers is an efficient cross platform serialization library for C++, 
> C#, C, Go, Java, Kotlin, JavaScript, Lobster, Lua, TypeScript, PHP, Python, 
> Rust and Swift. It was originally created at Google for game development 
> and other performance-critical applications.

**Project:** Harlinn.flatbuffers


### [Freetype](https://freetype.org/)
**Version:** 2.11.0

**Description:**
> FreeType is a freely available software library to render fonts.
> 
> It is written in C, designed to be small, efficient, highly customizable, and portable while capable of 
> producing high-quality output (glyph images) of most vector and bitmap font formats.

**Project:** Harlinn.freetype

### [GDAL - Geospatial Data Abstraction Library](https://gdal.org/)
**Version:** 3.4.0

**Description:**
> GDAL is a translator library for raster and vector geospatial data formats that is released under an 
> X/MIT style Open Source License by the Open Source Geospatial Foundation. As a library, it presents a 
> single raster abstract data model and single vector abstract data model to the calling application for 
> all supported formats.

**Project:** Harlinn.gdal

### [GEOS - coordinate transformation software library](https://libgeos.org/)
**Version:** 3.10.0dev

**Description:**
> GEOS is a C/C++ library for spatial computational geometry of the sort generally used by “geographic information systems” software.

**Project:** Harlinn.geos

### [Google gflags](https://github.com/gflags/gflags)
**Version:** 2.2.2

**Description:**
> Gflags, the commandline flags library used within Google, differs from other libraries, 
> such as getopt(), in that flag definitions can be scattered around the source code, and 
> not just listed in one place such as main(). In practice, this means that a single source-code 
> file will define and use flags that are meaningful to that file. Any application that links 
> in that file will get the flags, and the gflags library will automatically handle that 
> flag appropriately.
> 
> There's significant gain in flexibility, and ease of code reuse, due to this technique.

**Project:** Harlinn.gflags

### [Giflib](https://sourceforge.net/projects/giflib/)
**Version:** 5.2.1

**Description:**
> giflib is a library for reading and writing gif images.

**Project:** Harlinn.gif

### [Glad](https://glad.dav1d.de/)
**Version:** generated by glad 0.1.35 on Sun Dec 26 15:01:04 2021

**Description:**
> GLSC2, OpenGL, OpenGL ES loader generated by glad 0.1.35 on Sun Dec 26 15:01:04 2021
> using the [Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs](https://glad.dav1d.de/).

**Project:** Harlinn.glad


### [GLFW - multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop](https://www.glfw.org/)
**Version:** 3.3.4 

**Description:**
> GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on 
> the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving 
> input and events.

**Project:** Harlinn.glfw

### [gRPC](https://grpc.io/)
**Version:** 1.41.1 

**Description:**
> gRPC is a modern open source high performance Remote Procedure Call (RPC) framework that can run 
> in any environment. It can efficiently connect services in and across data centers with pluggable 
> support for load balancing, tracing, health checking and authentication. It is also applicable in 
> last mile of distributed computing to connect devices, mobile applications and browsers to backend 
> services.

**Projects:**
- Harlinn.grpc
- Harlinn.grpc-compiler
- Tools\\3rdParty\\grpc\\gen_hpack_tables
- Tools\\3rdParty\\grpc\\grpc_cpp_plugin
- Tools\\3rdParty\\grpc\\grpc_csharp_plugin
- Tools\\3rdParty\\grpc\\grpc_node_plugin
- Tools\\3rdParty\\grpc\\grpc_objective_c_plugin
- Tools\\3rdParty\\grpc\\grpc_php_plugin
- Tools\\3rdParty\\grpc\\grpc_python_plugin
- Tools\\3rdParty\\grpc\\grpc_ruby_plugin
- Tests\\3rdParty\\gRPC\\core\address_utils\\grpc_test_core_address_utils_parse_address_test
- Tests\\3rdParty\\gRPC\\core\address_utils\\grpc_test_core_address_utils_parse_address_with_named_scope_id_test
- Tests\\3rdParty\\gRPC\\core\address_utils\\grpc_test_core_address_utils_sockaddr_utils_test
- Tests\\3rdParty\\gRPC\\core\avl\\grpc_test_avl_avl_test
- Tests\\3rdParty\\gRPC\\core\backoff\\grpc_test_backoff_backoff_test
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_badreq
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_bad_streaming_id
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_connection_prefix
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_duplicate_header
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_headers
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_head_of_line_blocking
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_initial_settings_frame
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_large_metadata
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_out_of_bounds
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_server_registered_method
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_simple_request
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_unknown_frame
- Tests\\3rdParty\\gRPC\\core\bad_client\\grpc_test_bad_client_window_overflow
- Tests\\3rdParty\\gRPC\\core\bad_connection\\grpc_test_bad_connection_close_fd_test
- Tests\\3rdParty\\gRPC\\core\bad_ssl\\grpc_test_bad_ssl_alpn_server_test
- Tests\\3rdParty\\gRPC\\core\bad_ssl\\grpc_test_bad_ssl_bad_ssl_test
- Tests\\3rdParty\\gRPC\\core\bad_ssl\\grpc_test_bad_ssl_cert_server_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_channel_channel_args_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_channel_channel_stack_builder_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_channel_channel_stack_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_channel_channel_trace_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_core_channelz_registry_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_core_channelz_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_core_channel_status_util_test
- Tests\\3rdParty\\gRPC\\core\channel\\grpc_test_core_minimal_stack_is_minimal_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\grpc_test_core_client_channel_certificate_provider_registry_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\grpc_test_core_client_channel_retry_throttle_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\grpc_test_core_client_channel_service_config_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\dns_resolver_connectivity_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\dns_resolver_cooldown_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\grpc_test_dns_resolver_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\grpc_test_fake_resolver_test
- Tests\\3rdParty\\gRPC\\core\client_channel\\resolvers\grpc_test_sockaddr_resolver_test
- Tests\\3rdParty\\gRPC\\core\compression\\grpc_test_core_compression_algorithm_test
- Tests\\3rdParty\\gRPC\\core\compression\\grpc_test_core_compression_compression_test
- Tests\\3rdParty\\gRPC\\core\compression\\grpc_test_core_compression_message_compress_test
- Tests\\3rdParty\\gRPC\\core\compression\\grpc_test_core_compression_stream_compression_test
- Tests\\3rdParty\\gRPC\\core\config\\grpc_test_core_config_core_configuration_test
- Tests\\3rdParty\\gRPC\\core\debug\\grpc_test_core_debug_stats_test
- Tests\\3rdParty\\gRPC\\core\event_engine\\grpc_test_core_event_engine_endpoint_config_test
- Tests\\3rdParty\\gRPC\\core\fling\\fling_client
- Tests\\3rdParty\\gRPC\\core\fling\\fling_server
- Tests\\3rdParty\\gRPC\\core\fling\\grpc_test_core_fling_fling_stream_test
- Tests\\3rdParty\\gRPC\\core\fling\\grpc_test_core_fling_fling_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_alloc_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_arena_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_cpu_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_env_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_log_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_murmur_hash_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_spinlock_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_string_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_sync_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_time_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_tls_test
- Tests\\3rdParty\\gRPC\\core\gpr\\grpc_test_core_gpr_useful_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_bitset_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_capture_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_dual_ref_counted_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_examine_stack_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_fork_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_global_config_env_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_global_config_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_host_port_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_manual_constructor_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_match_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_mpscq_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_orphanable_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_overload_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_ref_counted_ptr_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_ref_counted_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_status_helper_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_stat_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_table_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_thd_test
- Tests\\3rdParty\\gRPC\\core\gprpp\\grpc_test_core_gprpp_time_util_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_combiner_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_endpoint_pair_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_error_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_grpc_ipv6_loopback_available_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_load_file_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_mpmcqueue_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_pollset_windows_starvation_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_resolve_address_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_resource_quota_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_threadpool_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_timer_heap_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_timer_list_test
- Tests\\3rdParty\\gRPC\\core\iomgr\\grpc_test_core_iomgr_time_averaged_stats_test
- Tests\\3rdParty\\gRPC\\grpc_test_core_util


### [libgta - Generic Tagged Arrays](https://marlam.de/gta/)
**Version:** 1.2.1

**Description:**
> Libgta, a library that reads and writes GTA files.

**Project:** Harlinn.gta

### [GoogleTest](https://github.com/google/googletest)
**Version:** 1.11.0

**Description:**
> GoogleTest is Google’s C++ testing and mocking framework.

**Project:** Harlinn.gtest

### [gwen](https://github.com/garrynewman/GWEN)
**Version:** from bullet 3.21

**Description:**
> a C++ GUI library

**Project:** Harlinn.gwen

### [HarfBuzz, a text shaping library](https://github.com/harfbuzz/harfbuzz)
**Version:** 3.0.0

**Description:**
> HarfBuzz is a text shaping library. Using the HarfBuzz library allows programs to convert a sequence 
> of Unicode input into properly formatted and positioned glyph output—for any writing system and language.

**Project:** Harlinn.harfbuzz

### [HDF](https://github.com/HDFGroup/hdf4)
**Version:** 4.2.15 

**Description:**
> The Hierarchical Data Format, or HDF, is a multiobject file format for sharing scientific 
> data in a distributed environment. HDF was created at the National Center for Supercomputing 
> Applications, and is now developed and maintained by The HDF Group, to serve the needs of 
> diverse groups of scientists working on projects in various fields

**Project:** Harlinn.hdf4

### [HDF5](https://github.com/HDFGroup/hdf5)
**Version:** 1.12.1

**Description:**
> The HDF Group is the developer of HDF5®, a high-performance software library and data format 
> that has been adopted across multiple industries and has become a de facto standard in scientific 
> and research communities.

**Project:** Harlinn.hdf5

### [Highway](https://github.com/google/highway)
**Version:** 0.14.2

**Description:**
> Highway is a C++ library for SIMD (Single Instruction, Multiple Data), i.e. applying the same 
> operation to multiple 'lanes' using a single CPU instruction.

**Project:** Harlinn.highway

### [Imath](https://github.com/AcademySoftwareFoundation/Imath)
**Version:** master as of 2021.08.18

**Description:**
> Imath is a basic, light-weight, and efficient C++ representation of 2D and 3D vectors and 
> matrices and other simple but useful mathematical objects, functions, and data types common 
> in computer graphics applications, including the “half” 16-bit floating-point type.

**Project:** Harlinn.imath

### [Dear ImGui](https://github.com/ocornut/imgui) and [ImPlot](https://github.com/epezent/implot)
**Dear ImGui Version:** Docking branch after merge of master at version 1.86
**ImPlot Version:** 0.12

**Description:**
Packages Dear ImGui and ImPlot as a single dll. 

**Description 'Dear ImGui':**
> Dear ImGui is a bloat-free graphical user interface library for C++. It outputs optimized 
> vertex buffers that you can render anytime in your 3D-pipeline enabled application.

**Description 'ImPlot':**
> ImPlot is an immediate mode, GPU accelerated plotting library for Dear ImGui. It aims to 
> provide a first-class API that ImGui fans will love. ImPlot is well suited for visualizing 
> program data in real-time or creating interactive plots, and requires minimal code to integrate.

**Project:** Harlinn.ImGui

### [JasPer Image Processing/Coding Tool Kit](https://github.com/jasper-software/jasper)
**Version:** 2.0.33

**Description:**
> JasPer Image Processing/Coding Tool Kit

**Project:** Harlinn.jasper

### [The Independent JPEG Group's JPEG software](https://www.ijg.org)
**Version:** 9d

**Description:**
> IJG is an informal group that writes and distributes a widely used free library for JPEG image compression.

**Project:** Harlinn.jpeg

### [libjpeg-turbo](http://libjpeg-turbo.org)
**Version:** 2.1.1

**Description:**
> libjpeg-turbo is a JPEG image codec that uses SIMD instructions (MMX, SSE2, AVX2, Neon, AltiVec) to accelerate 
> baseline JPEG compression and decompression on x86, x86-64, Arm, and PowerPC systems, as well as progressive 
> JPEG compression on x86 and x86-64 systems. On such systems, libjpeg-turbo is generally 2-6x as fast as libjpeg, 
> all else being equal. On other types of systems, libjpeg-turbo can still outperform libjpeg by a significant 
> amount, by virtue of its highly-optimized Huffman coding routines. In many cases, the performance of 
> libjpeg-turbo rivals that of proprietary high-speed JPEG codecs.
>
> libjpeg-turbo implements both the traditional libjpeg API as well as the less powerful but more straightforward 
> TurboJPEG API. libjpeg-turbo also features colorspace extensions that allow it to compress from/decompress to 
> 32-bit and big-endian pixel buffers (RGBX, XBGR, etc.), as well as a full-featured Java interface.

**Project:** Harlinn.jpeg-turbo

### [JSON-C - A JSON implementation in C](https://github.com/json-c/json-c)
**Version:** master as of 2021.08.01 

**Description:**
> A JSON implementation in C.

**Project:** Harlinn.json-c

### [JsonCpp](https://github.com/open-source-parsers/jsoncpp)
**Version:** 1.9.4

**Description:**
> JsonCpp is a C++ library that allows manipulating JSON values, including serialization and deserialization 
> to and from strings. It can also preserve existing comment in unserialization/serialization steps, making 
> it a convenient format to store user input files.

**Project:** Harlinn.jsoncpp

### [JPEG XL reference implementation](https://github.com/libjxl/libjxl)
**Version:** 0.5

**Description:**
> A reference implementation of JPEG XL (encoder and decoder), called libjxl.

**Project:** Harlinn.jxl

### [kml](https://github.com/libkml/libkml)
**Version:** 1.3.0

**Description:**
> This is Google's reference implementation of OGC KML 2.2. 

**Projects:**
- Harlinn.kmlbase
- Harlinn.kmlconvenience
- Harlinn.kmldom
- Harlinn.kmlengine
- Harlinn.kmlregionator
- Harlinn.kmlxsd

### [Little CMS](https://github.com/mm2/Little-CMS)
**Version:** 2.12

**Description:**
> Little CMS intends to be an OPEN SOURCE small-footprint color management engine, 
> with special focus on accuracy and performance. It uses the International Color 
> Consortium standard (ICC), which is the modern standard when regarding to color 
> management. The ICC specification is widely used and is referred to in many 
> International and other de-facto standards. It was approved as an International 
> Standard, ISO 15076-1, in 2005.

**Project:** Harlinn.lcms2

### [LERC - Limited Error Raster Compression](https://github.com/Esri/lerc)
**Version:** 3.0

**Description:**
> LERC is an open-source image or raster format which supports rapid encoding and 
> decoding for any pixel type (not just RGB or Byte).

**Project:** Harlinn.Lerc

### [libde265 - open h.265 codec implementation](https://github.com/strukturag/libde265)
**Version:** 1.0.8

**Description:**
> libde265 is an open source implementation of the h.265 video codec. It is written from 
> scratch and has a plain C API to enable a simple integration into other software.
> 
> libde265 supports WPP and tile-based multithreading and includes SSE optimizations. 
> The decoder includes all features of the Main profile and correctly decodes almost 
> all conformance streams

**Project:** Harlinn.libde265

### [FLAC - Free Lossless Audio Codec](https://github.com/xiph/flac)
**Version:** 1.3.2 

**Description:**
> FLAC is an Open Source lossless audio codec

**Project:** Harlinn.libflac

### [libheif](https://github.com/strukturag/libheif)
**Version:** 1.12.0 

**Description:**
> libheif is an ISO/IEC 23008-12:2017 HEIF and AVIF (AV1 Image File Format) file format 
> decoder and encoder.
> 
> HEIF and AVIF are new image file formats employing HEVC (h.265) or AV1 image coding, 
> respectively, for the best compression ratios currently possible.

**Project:** Harlinn.libheif

### [liblzma](https://tukaani.org/)
**Version:** 5.2.5

**Description:**
> LZMA Utils is an attempt to provide LZMA compression to POSIX-like systems. The idea 
> is to have a gzip-like command line tool and a zlib-like library, which would make 
> it easy to adapt the new compression technology to existing applications.

**Project:** Harlinn.liblzma

### [libmysofa](https://github.com/hoene/libmysofa)
**Version:** 1.2.1

**Description:**
> This is a simple set of C functions to read AES SOFA files, if they contain HRTFs 
> stored according to the AES69-2015 standard.

**Project:** Harlinn.libmysofa

### [libogg](https://www.xiph.org/ogg)
**Version:** 1.3.5 

**Description:**
> Ogg is a multimedia container format, and the native file and stream format for the 
> Xiph.org multimedia codecs.

**Project:** Harlinn.libogg

### [LIBSVM -- A Library for Support Vector Machines](http://www.csie.ntu.edu.tw/~cjlin/libsvm)
**Version:** 3.16

**Description:**
> LIBSVM is an integrated software for support vector classification, (C-SVC, nu-SVC), regression 
> (epsilon-SVR, nu-SVR) and distribution estimation (one-class SVM). It supports multi-class classification.

**Project:** Harlinn.libsvm

### [VMAF - Video Multi-Method Assessment Fusion](https://github.com/Netflix/vmaf)
**Version:** 2.2.0

**Description:**
> VMAF is a perceptual video quality assessment algorithm developed by Netflix. 

**Project:** Harlinn.libvmaf

### [Libxml2](http://xmlsoft.org/)
**Version:** 2.9.12

**Description:**
> Libxml2 is the XML C parser and toolkit developed for the Gnome project.

**Project:** Harlinn.libxml2

### [Lightning Memory-Mapped Database](https://symas.com/lmdb/)
**Version:** 0.9.70

**Description:**
> An ultra-fast, ultra-compact, crash-proof, key-value, embedded data store

**Project:** Harlinn.LMDB


### [LodePNG - PNG encoder and decoder in C and C++, without dependencies](http://lodev.org/lodepng)
**Version:** 20200215

**Description:**
> LodePNG is a PNG image decoder and encoder, all in one, no dependency or 
> linkage to zlib or libpng required.

**Project:** Harlinn.lodepng

### [Lua](https://www.lua.org/home.html)
**Version:** 5.4.3

**Description:**
> Lua is a powerful, efficient, lightweight, embeddable scripting language. It supports procedural 
> programming, object-oriented programming, functional programming, data-driven programming, and 
> data description.

**Project:** Harlinn.lua


### [LZ4 - Extremely fast compression](https://github.com/lz4/lz4)
**Version:** 1.9.3

**Description:**
> LZ4 is lossless compression algorithm, providing compression speed > 500 MB/s 
> per core, scalable with multi-cores CPU. It features an extremely fast decoder, 
> with speed in multiple GB/s per core, typically reaching RAM speed limits on 
> multi-core systems.

**Project:** Harlinn.lz4

### [LZMA SDK](https://www.7-zip.org/sdk.html)
**Version:** 21.03

**Description:**
> LZMA / LZMA2 are default and general compression methods of 7z format in the 
> 7-Zip program. LZMA provides a high compression ratio and fast decompression, 
> so it is very suitable for embedded applications. 

**Project:** Harlinn.lzma

### [Mesh Data Abstraction Library (MDAL)](https://github.com/lutraconsulting/MDAL)
**Version:** 0.8.1

**Description:**
> Mesh Data Abstraction Library.

**Project:** Harlinn.mdal

### [minizip](http://www.winimage.com/zLibDll/minizip.html)
**Version:** 1.1

**Description:**
> This package enables to extract files from a .zip archive file.

**Project:** Harlinn.minizip

### [Unidata NetCDF](https://github.com/Unidata/netcdf-c)
**Version:** TBD - this project is currently just a placeholder

**Project:** Harlinn.netcdf-c

### [JSON for Modern C++](https://github.com/nlohmann/json)
**Version:** develop as of 2021.08.16

**Description:**
> JSON for Modern C++

**Project:** Harlinn.nlohmann-json

### [OpenAL Soft is an LGPL-licensed, cross-platform, software implementation of the OpenAL 3D audio API.](http://openal-soft.org)
**Version:** 1.21.1

**Description:**
> OpenAL Soft is an LGPL-licensed, cross-platform, software implementation of the OpenAL 3D audio API.
> 
> OpenAL provides capabilities for playing audio in a virtual 3D environment. Distance attenuation, 
> doppler shift, and directional sound emitters are among the features handled by the API.

**Project:** Harlinn.openal-soft

### [OpenCensus - A stats collection and distributed tracing framework](https://github.com/census-instrumentation/opencensus-cpp)
**Version:** 0.4.0

**Description:**
> OpenCensus is a toolkit for collecting application performance and behavior data. It currently includes an API for tracing and stats.

**Project:** Harlinn.opencensus

### [OpenEXR](https://github.com/AcademySoftwareFoundation/openexr)
**Version:** master as of 2021.08.18

**Description:**
> OpenEXR provides the specification and reference implementation of the EXR file format, the 
> professional-grade image storage format of the motion picture industry.
> 
> The purpose of EXR format is to accurately and efficiently represent high-dynamic-range 
> scene-linear image data and associated metadata, with strong support for multi-part, 
> multi-channel use cases.

**Projects:**
- Harlinn.iex
- Harlinn.ilmthread
- Harlinn.openexr
- Harlinn.openexrcore
- Harlinn.openexrutil

### [OpenFYBA](https://github.com/kartverket/fyba)
**Version:** 4.1.1 

**Description:**
> OpenFYBA is the source code release of the FYBA library, distributed by the 
> National Mapping Authority of Norway (Statens kartverk) to read and write 
> files in the National geodata standard format SOSI.

**Project:** Harlinn.openfyba

### [The Preview Image Extractor (PIEX)](https://github.com/google/piex)
**Version:** master as of 2021.09.24

**Description:**
> The Preview Image Extractor (PIEX) is designed to find and extract the largest JPEG 
> compressed preview image contained in a RAW file.

**Project:** Harlinn.piex

### [libpng](http://www.libpng.org/pub/png/libpng.html)
**Version:** 1.6.37

**Description:**
> libpng is the official PNG reference library. It supports almost all PNG features, 
> is extensible, and has been extensively tested for over 23 years.

**Project:** Harlinn.png

### [PROJ is a generic coordinate transformation software](https://proj.org/)
**Version:** 8.1.0

**Description:**
> PROJ is a generic coordinate transformation software that transforms geospatial 
> coordinates from one coordinate reference system (CRS) to another. This includes 
> cartographic projections as well as geodetic transformations. 

**Project:** Harlinn.proj

### [Protocol Buffers](https://developers.google.com/protocol-buffers)
**Version:** 3.17.3

**Description:**
> Protocol buffers are Google's language-neutral, platform-neutral, extensible 
> mechanism for serializing structured data – think XML, but smaller, faster, and 
> simpler. You define how you want your data to be structured once, then you can 
> use special generated source code to easily write and read your structured data 
> to and from a variety of data streams and using a variety of languages.

**Projects:** 
- Harlinn.protobuf
- Tools\\3rdParty\\protobuf\\protoc

### [pthreads4w](https://sourceforge.net/projects/pthreads4w/)
**Version:** 3.0.0

**Description:**
> Also known as "pthreads-win32", POSIX Threads for Windows implements a large subset 
> of the threads related API from the Single Unix Specification Version 3.
>
> Conformance and quality are high priorities of this mature library. Development began 
> in 1998 and has continued with numerous significant professional contributions.

**Project:** Harlinn.pthreads4w

### [Qpid Proton - The AMQP messaging toolkit](https://qpid.apache.org/proton/)
**Version:** 0.35.0

**Description:**
> Qpid Proton is a high-performance, lightweight messaging library. It can be used 
> in the widest range of messaging applications, including brokers, client libraries, 
> routers, bridges, proxies, and more. Proton makes it trivial to integrate with the 
> AMQP 1.0 ecosystem from any platform, environment, or language.

**Projects:**
- Harlinn.qpid-proton
- Harlinn.qpid-proton-cpp

### [RapidJSON](https://github.com/Tencent/rapidjson)
**Version:** master as of 2021.09.26

**Description:**
> A fast JSON parser/generator for C++ with both SAX/DOM style API.

**Project:** Harlinn.RapidJSON

### [RE2 - a regular expression library](https://github.com/google/re2)
**Version:** 2021-09-01

**Description:**
> RE2 was designed and implemented with an explicit goal of being able to 
> handle regular expressions from untrusted users without risk. One of its 
> primary guarantees is that the match time is linear in the length of the 
> input string. It was also written with production concerns in mind: the 
> parser, the compiler and the execution engines limit their memory usage by 
> working within a configurable budget – failing gracefully when exhausted – 
> and they avoid stack overflow by eschewing recursion.

**Project:** Harlinn.re2

### [RocksDB: A Persistent Key-Value Store for Flash and RAM Storage](https://github.com/facebook/rocksdb)
**Version:** 6.22.1

**Description:**
> RocksDB is a storage engine with key/value interface, where keys and values are arbitrary 
> byte streams. It is a C++ library. It was developed at Facebook based on LevelDB and provides 
> backwards-compatible support for LevelDB APIs.
> 
> RocksDB supports various storage hardware, with fast flash as the initial focus. It uses a 
> Log Structured Database Engine for storage, is written entirely in C++

**Project:** Harlinn.rocksdb

### [rtmidi](https://www.music.mcgill.ca/~gary/rtmidi/index.html)
**Version:** 5.0.0

**Description:**
> RtMidi is a set of C++ classes (RtMidiIn, RtMidiOut and API-specific classes) that provides a common 
> API (Application Programming Interface) for realtime MIDI input/output across Linux (ALSA & JACK), 
> Macintosh OS X (CoreMIDI & JACK), and Windows (Multimedia Library) operating systems. RtMidi significantly 
> simplifies the process of interacting with computer MIDI hardware and software.

**Project:** Harlinn.rtmidi


### [Scintilla - a free source code editing component](https://www.scintilla.org/)
**Version:** 5.1.3

**Description:**
> Scintilla is a free source code editing component. It comes with complete source code and 
> a license that permits use in any free project or commercial product.
>
> As well as features found in standard text editing components, Scintilla includes features 
> especially useful when editing and debugging source code. These include support for syntax 
> styling, error indicators, code completion and call tips. The selection margin can contain 
> markers like those used in debuggers to indicate breakpoints and the current line. Styling 
> choices are more open than with many editors, allowing the use of proportional fonts, bold 
> and italics, multiple foreground and background colours and multiple fonts.

**Project:** Harlinn.scintilla

### [Simple DirectMedia Layer (SDL) Version 2.0](https://github.com/libsdl-org/SDL)
**Version:** 2.0.16 

**Description:**
> Simple DirectMedia Layer is a cross-platform development library designed to provide low 
> level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and 
> Direct3D.

**Project:** Harlinn.SDL2

### [Simple and Fast Multimedia Library](https://www.sfml-dev.org/)
**Version:** 2.5.1

**Description:**
> SFML provides a simple interface to the various components of your PC, to ease the 
> development of games and multimedia applications. It is composed of five modules: 
> system, window, graphics, audio and network.

**Projects:**
- Harlinn.sfml-audio
- Harlinn.sfml-graphics
- Harlinn.sfml-network
- Harlinn.sfml-system
- Harlinn.sfml-window

### [The sjpeg library](https://github.com/webmproject/sjpeg)
**Version:** master as of 2021.09.11

**Description:**
> sjpeg is a simple encoding library for encoding baseline JPEG files.

**Project:** Harlinn.sjpeg

### [skcms](https://skia.googlesource.com/skcms/)
**Version:** main as of 2021.09.12

**Description:**
Skia Color Management

**Project:** Harlinn.skcms

### [Skia - The 2D Graphics Library](https://skia.org/)
**Version:** 0.31

**Description:**
> Skia is an open source 2D graphics library which provides common APIs that work 
> across a variety of hardware and software platforms. It serves as the graphics 
> engine for Google Chrome and Chrome OS, Android, Flutter, Mozilla Firefox and 
> Firefox OS, and many other products.

**Projects:** 
- Harlinn.skia
- Tools\\3rdParty\\Skia\\skslc

### [Snappy - a compression/decompression library](https://github.com/google/snappy)
**Version:** master as of 2021.08.02

**Description:**
> Snappy is a compression/decompression library. It does not aim for maximum compression, 
> or compatibility with any other compression library; instead, it aims for very high 
> speeds and reasonable compression. For instance, compared to the fastest mode of zlib, 
> Snappy is an order of magnitude faster for most inputs, but the resulting compressed 
> files are anywhere from 20% to 100% bigger.

**Project:** Harlinn.snappy

### [sqlite3](https://www.sqlite.org/index.html)
**Version:** 3.36.0

**Description:**
> SQLite is a C-language library that implements a small, fast, self-contained, high-reliability, 
> full-featured, SQL database engine.

**Projects:** 
- Harlinn.SQLite3
- Tools\\3rdParty\\SQLite3\\sqlite3

### [Single-file public-domain/open source libraries with minimal dependencies (STB) ](https://github.com/nothings/single_file_libs)
**Version:** master as of 2021.09.10

**Description:**
> Small, easy-to-integrate, portable libraries which are usable from C and/or C++

**Project:** Harlinn.stb

### [SuperLU](https://portal.nersc.gov/project/sparse/superlu/)
**Version:** 5.2.2

**Description:**
> SuperLU is a general purpose library for the direct solution of large, sparse, nonsymmetric systems of linear equations.

**Project:** Harlinn.superlu

### [LibTIFF](https://libtiff.gitlab.io/libtiff/)
**Version:** 4.3.0 

**Description:**
> This software provides support for the Tag Image File Format (TIFF), a widely used format for storing image data.

**Project:** Harlinn.tiff

### [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
**Version:** master as of 2021.12.27

**Description:**
> Tiny but powerful single file wavefront obj loader written in C++03. No dependency 
> except for C++ STL. It can parse over 10M polygons with moderate memory and time.

**Project:** Harlinn.tinyobjloader

### [TinyXML-2](https://github.com/leethomason/tinyxml2)
**Version:** master as of 2021.06.07

**Description:**
> TinyXML-2 is a simple, small, efficient, C++ XML parser that can be easily integrated into other programs.

**Project:** Harlinn.tinyxml2

### [μpb: small, fast C protos](https://github.com/protocolbuffers/upb)
**Version:** master as of 2021.10.21

**Description:**
> μpb (often written 'upb') is a small protobuf implementation written in C.

**Projects:** 
- Harlinn.upb
- Tools\\3rdParty\\upb\\protoc-gen-upb
- Tools\\3rdParty\\upb\\protoc-gen-upbdefs

### [uriparser](https://github.com/uriparser/uriparser)
**Version:** 0.9.5

**Description:**
> uriparser is a strictly RFC 3986 compliant URI parsing and handling library written in C89 ("ANSI C").

**Project:** Harlinn.uriparser

### [libvorbis, libvorbisfile and libvorbisenc](https://github.com/xiph/vorbis)
**Version:** 1.3.7

**Description:**
> Vorbis is a general purpose audio and music encoding format contemporary to MPEG-4's AAC 
> and TwinVQ, the next generation beyond MPEG audio layer 3.

**Project:** Harlinn.vorbis

### [Vulkan header files](https://github.com/KhronosGroup/Vulkan-Headers)
**Version:** main as of 2021.09.21

**Description:**
> Vulkan header files

**Project:** Harlinn.vulkan

### [Vulkan Memory Allocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
**Version:** 2.3.0 

**Description:**
> The Vulkan® Memory Allocator (VMA) library provides a simple and easy to integrate API 
> to help you allocate memory for Vulkan® buffer and image storage.

**Project:** Harlinn.vulkanmemoryallocator

### [libwebm](https://chromium.googlesource.com/webm/libwebm/)
**Version:** main as of 2021.09.08

**Description:**
> The WebM Project is dedicated to developing a high-quality, open video format for the 
> web that's freely available to everyone.

**Project:** Harlinn.webm

### [WebP - An image format for the Web](https://developers.google.com/speed/webp)
**Version:** main as of 2021.09.08

**Description:**
> WebP is a modern image format that provides superior lossless and lossy compression for 
> images on the web. Using WebP, webmasters and web developers can create smaller, richer 
> images that make the web faster.

**Project:** Harlinn.webp

### [Xerces-C++ - a validating XML parser](http://xerces.apache.org/xerces-c/)
**Version:** 3.2.3 

**Description:**
> Xerces-C++ is a validating XML parser written in a portable subset of C++. 
> Xerces-C++ makes it easy to give your application the ability to read and 
> write XML data.

**Project:** Harlinn.xerces-c

### [XMP-Toolkit-SDK](https://github.com/adobe/XMP-Toolkit-SDK)
**Version:** 6.0.0

**Description:**
> The XMP Toolkit allows you to integrate XMP functionality into your product or solution. 

**Project:** Harlinn.xmptoolkitsdk

### [libyuv](https://chromium.googlesource.com/libyuv/libyuv/)
**Version:** main as of 2021-09-07

**Description:**
> libyuv is an open source project that includes YUV scaling and conversion functionality.

**Project:** Harlinn.yuv

### [zlib](http://zlib.net/)
**Version:** 1.2.11

**Description:**
> zlib is designed to be a free, general-purpose, legally unencumbered -- that is, not 
> covered by any patents -- lossless data-compression library for use on virtually any 
> computer hardware and operating system. 

**Project:** Harlinn.zlib

### [zlib-ng](https://github.com/zlib-ng/zlib-ng)
**Version:** develop as of 2021.05.08

**Description:**
> zlib data compression library for the next generation systems

**Project:** Harlinn.zlibng

### [Zstandard (zstd)](https://github.com/facebook/zstd)
**Version:** dev as of 2021.08.04

**Description:**
> Zstandard, or zstd as short version, is a fast lossless compression algorithm, targeting 
> real-time compression scenarios at zlib-level and better compression ratios.

**Project:** Harlinn.zstd

