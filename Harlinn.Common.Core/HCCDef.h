#pragma once
#ifndef __HCCDEF_H__
#define __HCCDEF_H__

#define HCC_WITH_BASIC_STRING 1


#ifdef BUILDING_HARLINN_COMMON_CORE
#define HCC_EXPORT __declspec(dllexport)
#define HCC_TEMPLATE_EXPORT __declspec(dllexport)
#define HCC_TEMPLATE_EXPORT_DECL
#else
#define HCC_EXPORT __declspec(dllimport)
#define HCC_TEMPLATE_EXPORT __declspec(dllimport)
#define HCC_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#define FMT_SHARED 1
#pragma comment(lib,"Harlinn.Common.Core.lib")
#endif

#ifdef _DEBUG
#define HCC_INLINE_DECL HCC_EXPORT
#define HCC_INLINE 
#else
#define HCC_INLINE_DECL 
#define HCC_INLINE inline
#endif

#pragma warning(disable:4996)
#pragma warning(disable:4091)
#pragma warning(disable:4503)

#define OEMRESOURCE

#define _USE_MATH_DEFINES 

#ifdef _M_AMD64
#define WIN64 1
#endif
#define SECURITY_WIN32

// Prevent inclusion of winsock.h in windows.h 
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_   
#endif


#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef _NOMINMAX
#define _NOMINMAX
#endif

#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK 1
#endif


#include <windows.h>
#include <winsock2.h>
#include <Mswsock.h>
#include <WinIoCtl.h>
#include <ws2ipdef.h>

#include <mstcpip.h>

#include <Windowsx.h>
#include <CommCtrl.h>
#include <Security.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <d2d1svg.h>
#include <d2d1effects_2.h>
#include <d2d1effectauthor_1.h>
#include <dwrite_3.h>
#include <dwmapi.h>
#include <XInput.h>
#include <d3dcommon.h>
#include <dxcore.h>
#include <d3d12.h>
#include <d3d12shader.h>
#include <d3d12video.h>
#include <d3d12sdklayers.h>
#include <d3d11on12.h>
#include <d3d11_4.h>
#include <d3d11shader.h>
#include <d3dcompiler.h>
#include <d3dcsx.h>
#include <D3D9Types.h>
#include <d3d9.h>
#include <dxva2api.h>
#include <DirectXMath.h>
#include <directxcollision.h>
#include <directxpackedvector.h>
#include <Dmo.h>
#include <mediaobj.h>
#include <mfobjects.h>
#include <mfidl.h>
#include <mfapi.h>
#include <mferror.h>
#include <mfreadwrite.h>
#include <evr.h>
#include <mmdeviceapi.h>
#include <camerauicontrol.h>
#include <wmcodecdsp.h>
#include <codecapi.h>
#include <wmsdkidl.h>
#include <dvdmedia.h>
#include <dcomp.h>
#include <ks.h>
#include <ksmedia.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <rtworkq.h>
#include <Shlobj.h>
#include <mshtml.h>
#include <http.h>
#include <OCIdl.h>
#include <OleDlg.h>
#include <DbgHelp.h>
#include <winnt.h>
#include <CorError.h>
#include <Aclapi.h>
#include <Sddl.h>
#include <lmcons.h>
#include <Odbcinst.h>
#include <Sql.h>
#include <Sqlext.h>
#include <Sqltypes.h>
#include <Sqlucode.h>
#include <Msdasql.h>
#include <Msdadc.h>
#include <tlhelp32.h>
#include <Lm.h>
#include <ntdsapi.h>
#include <Credssp.h>
#include <Schnlsp.h>
#include <Dbt.h>
#include <propvarutil.h>

#include <msxml2.h>
#include <msxml6.h>

#include <oledbdep.h>
#include <oledb.h>

#include <wbemidl.h>
#include <sensorsapi.h>

#include <netioapi.h>
#include <netiodef.h>
#ifndef __WINCRYPT_H__
#include <wincrypt.h>
#endif

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
#pragma push_macro("NTDDI_VERSION")
#undef NTDDI_VERSION
#define NTDDI_VERSION NTDDI_WINBLUE
#include <locationapi.h>
#pragma pop_macro("NTDDI_VERSION")
#else
#include <locationapi.h>
#endif


//#include <ntstatus.h>

#ifndef STATUS_CANCELLED
#define STATUS_CANCELLED                 ((NTSTATUS)0xC0000120L)
#endif

#ifndef STATUS_LOCAL_DISCONNECT
#define STATUS_LOCAL_DISCONNECT          ((NTSTATUS)0xC000013BL)
#endif

#ifndef STATUS_REMOTE_DISCONNECT
#define STATUS_REMOTE_DISCONNECT         ((NTSTATUS)0xC000013CL)
#endif



#include <immintrin.h>

#include <concepts>
#include <compare>

#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <cinttypes>

#include <iostream>
#include <fstream>
#include <valarray>

#include <algorithm>
#include <array>

#include <atomic>
#include <format>
#include <bit>
#include <cfloat>
#include <cstddef>
#include <chrono>
#include <complex>
#include <deque>
#include <functional>
#include <forward_list>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <span>
#include <utility>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <set>
#include <vector>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <optional>
#include <thread>
#ifndef _MANAGED
#include <future>
#endif
#include <mutex>
#include <shared_mutex>
#include <tuple>
#include <variant>
#include <any>
#include <source_location>
#include <cctype>
#include <cwctype>

#include <ppl.h>

#include <malloc.h>
#include <wchar.h>
#include <process.h>
#include <sys/stat.h>
#include <string.h>
#include <limits>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#include <concurrent_priority_queue.h>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <concurrent_unordered_set.h>
#include <concurrent_vector.h>


#define XXH_INLINE_ALL
#include <xxhash.h>

#include <boost/signals2.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/mp11.hpp>

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include <boost/program_options.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include <boost/icl/right_open_interval.hpp>
#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/separate_interval_set.hpp>
#include <boost/icl/split_interval_set.hpp>
#include <boost/icl/split_interval_map.hpp>

#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/stack.hpp>
#include <boost/lockfree/spsc_queue.hpp>

#include <HCCWinError.h>

namespace Harlinn::Common::Core
{
    namespace asio = boost::asio;

    template<typename EnumT, typename ... Args >
        requires std::is_enum_v<EnumT> && std::conjunction_v<std::is_same<std::remove_cvref_t<EnumT>, std::remove_cvref_t<Args>>...> && ( sizeof...( Args ) > 0 )
    constexpr bool ContainsAllOf( EnumT flags, Args&& ... args )
    {
        using IntType = std::underlying_type_t<EnumT>;
        IntType mask = std::bit_cast<IntType>( (args | ...) ) ;
        return ( std::bit_cast<IntType>( flags ) & mask ) == mask;
    }

    template<typename EnumT, typename ... Args >
        requires std::is_enum_v<EnumT>&& std::conjunction_v<std::is_same<std::remove_cvref_t<EnumT>, std::remove_cvref_t<Args>>...> && ( sizeof...( Args ) > 0 )
    constexpr bool ContainsNoneOf( EnumT flags, Args ... args )
    {
        using IntType = std::underlying_type_t<EnumT>;
        IntType mask = std::bit_cast<IntType>( ( args | ... ) );
        return ( std::bit_cast<IntType>( flags ) & mask ) == static_cast<IntType>( 0 );
    }
    template<typename EnumT, typename ... Args >
        requires std::is_enum_v<EnumT>&& std::conjunction_v<std::is_same<std::remove_cvref_t<EnumT>, std::remove_cvref_t<Args>>...> && ( sizeof...( Args ) > 0 )
    constexpr bool ContainsAnyOf( EnumT flags, Args ... args )
    {
        using IntType = std::underlying_type_t<EnumT>;
        IntType mask = std::bit_cast<IntType>( ( args | ... ) );
        return ( std::bit_cast<IntType>( flags ) & mask ) != static_cast<IntType>( 0 );
    }
    template<typename EnumT, typename ... Args >
        requires std::is_enum_v<EnumT> && std::conjunction_v<std::is_same<std::remove_cvref_t<EnumT>, std::remove_cvref_t<Args>>...> && ( sizeof...( Args ) > 0 )
    constexpr bool IsSet( EnumT flags, Args&& ... args )
    {
        using IntType = std::underlying_type_t<EnumT>;
        IntType mask = std::bit_cast<IntType>( (args | ...) ) ;
        return ( std::bit_cast<IntType>( flags ) & mask ) == mask;
    }
    template<typename EnumT, typename ... Args >
        requires std::is_enum_v<EnumT>&& std::conjunction_v<std::is_same<std::remove_cvref_t<EnumT>, std::remove_cvref_t<Args>>...> && ( sizeof...( Args ) > 0 )
    constexpr bool IsNotSet( EnumT flags, Args ... args )
    {
        using IntType = std::underlying_type_t<EnumT>;
        IntType mask = std::bit_cast<IntType>( ( args | ... ) );
        return ( std::bit_cast<IntType>( flags ) & mask ) == static_cast<IntType>( 0 );
    }


}



#define HCC_DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE,INTTYPE) \
  inline constexpr ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) noexcept { return ENUMTYPE(((INTTYPE) a) | ((INTTYPE) b)); } \
  inline constexpr ENUMTYPE &operator |= (ENUMTYPE &a, ENUMTYPE b) noexcept { (INTTYPE &) a |= ((INTTYPE) b); return a; } \
  inline constexpr ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) noexcept { return ENUMTYPE(((INTTYPE) a) & ((INTTYPE) b)); } \
  inline constexpr ENUMTYPE &operator &= (ENUMTYPE &a, ENUMTYPE b) noexcept { (INTTYPE &) a &= ((INTTYPE) b); return a; } \
  inline constexpr ENUMTYPE operator ~ (ENUMTYPE a) noexcept { return ENUMTYPE(~((INTTYPE) a)); } \
  inline constexpr ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) noexcept { return ENUMTYPE(((INTTYPE) a) ^ ((INTTYPE) b)); } \
  inline constexpr ENUMTYPE &operator ^= (ENUMTYPE &a, ENUMTYPE b) noexcept { (INTTYPE &) a ^= ((INTTYPE) b); return a; } \
  inline constexpr bool operator == (ENUMTYPE a, ENUMTYPE b) noexcept { return static_cast<INTTYPE>(a) == static_cast<INTTYPE>(b); } \
  inline constexpr bool operator == (INTTYPE a, ENUMTYPE b) noexcept { return static_cast<INTTYPE>(a) == static_cast<INTTYPE>(b); } \
  inline constexpr bool operator == (ENUMTYPE a, INTTYPE b) noexcept { return static_cast<INTTYPE>(a) == static_cast<INTTYPE>(b); } \
  inline constexpr bool operator != (ENUMTYPE a, ENUMTYPE b) noexcept { return static_cast<INTTYPE>(a) != static_cast<INTTYPE>(b); } \
  inline constexpr bool operator != (INTTYPE a, ENUMTYPE b) noexcept { return static_cast<INTTYPE>(a) != static_cast<INTTYPE>(b); } \
  inline constexpr bool operator != (ENUMTYPE a, INTTYPE b) noexcept { return static_cast<INTTYPE>(a) != static_cast<INTTYPE>(b); } \
  static_assert(std::is_same_v<std::underlying_type_t<ENUMTYPE>, INTTYPE> )

namespace Harlinn::Common::Core
{

    constexpr unsigned long long operator"" _gb( unsigned long long value )
    {
        return value * 1024ULL * 1024ULL * 1024ULL;
    }
    constexpr unsigned long long operator"" _mb( unsigned long long value )
    {
        return value * 1024ULL * 1024ULL;
    }
    constexpr unsigned long long operator"" _kb( unsigned long long value )
    {
        return value * 1024ULL;
    }
//#define HCC_WITH_BASIC_STRING 1
#ifdef HCC_WITH_BASIC_STRING
    template<typename T>
    class BasicString;

    using WideString = BasicString<wchar_t>;
    using AnsiString = BasicString<char>;

    template<typename T>
    class BasicStringView;

    using WideStringView = BasicStringView<wchar_t>;
    using AnsiStringView = BasicStringView<char>;
#else
    using WideString = std::wstring;
    using AnsiString = std::string;
    using WideStringView = std::wstring_view;
    using AnsiStringView = std::string_view;
#endif

    class Guid;
    class DateTime;
    class TimeSpan;
    class Currency;
    
    class Variant;
    class PropertyVariant;
    

    using Boolean = bool;
    using Int8 = signed char;
    using SByte = signed char;
    using UInt8 = unsigned char;
    using Byte = unsigned char;
    using Int16 = short;
    using UInt16 = unsigned short;
    using ushort = unsigned short;

    using Int32 = int;
    using Int = int;
    using UInt32 = unsigned int;
    using UInt = unsigned int;
    using ULong32 = unsigned long;
    using Long32 = long;
    using uint = unsigned int;
    using DWord32 = unsigned long;
    using DWord = unsigned long;

    using Int64 = long long;
    using Long64 = long long;
    using LongLong = long long;
    using UInt64 = unsigned long long;
    using ULong64 = unsigned long long;
    using ULongLong = unsigned long long;
    using DWord64 = unsigned long;

    using SSizeT = ptrdiff_t;
    using SizeT = size_t;

    using Char = char;
    using WideChar = wchar_t;
    using Char8 = char;
    using Char16 = wchar_t;
    using Char32 = UInt32;

    using Single = float;
    using Double = double;


    constexpr UInt8 MaxUInt8 = ( (UInt8)~( (UInt8)0 ) );
    constexpr Int8 MaxInt8 = ( (Int8)( MaxUInt8 >> 1 ) );
    constexpr Int8 MinInt8 = ( (Int8)~MaxInt8 );

    constexpr UInt16 MaxUInt16 = ( (UInt16)~( (UInt16)0 ) );
    constexpr Int16  MaxInt16 = ( (Int16)( MaxUInt16 >> 1 ) );
    constexpr Int16  MinInt16 = ( (Int16)~MaxInt16 );

    constexpr UInt32 MaxUInt32 = ( (UInt32)~( (UInt32)0 ) );
    constexpr Int32  MaxInt32 = ( (Int32)( MaxUInt32 >> 1 ) );
    constexpr Int32  MinInt32 = ( (Int32)~MaxInt32 );

    constexpr UInt64 MaxUInt64 = ( (UInt64)~( (UInt64)0 ) );
    constexpr Int64  MaxInt64 = ( (Int64)( MaxUInt64 >> 1 ) );
    constexpr Int64  MinInt64 = ( (Int64)~MaxInt64 );

    constexpr ULong32 MaxULong32 = ( (ULong32)~( (ULong32)0 ) );
    constexpr Long32  MaxLong32 = ( (Long32)( MaxULong32 >> 1 ) );
    constexpr Long32  MinLong32 = ( (Long32)~MaxLong32 );

    constexpr ULong64 MaxULong64 = ( (ULong64)~( (ULong64)0 ) );
    constexpr Long64 MaxLong64 = ( (Long64)( MaxULong64 >> 1 ) );
    constexpr Long64 MinLong64 = ( (Long64)~MaxLong64 );

    constexpr ULongLong MaxULongLong = ( (ULongLong)~( (ULongLong)0 ) );
    constexpr LongLong MaxLongLong = ( (LongLong)( MaxULongLong >> 1 ) );
    constexpr LongLong MinLongLong = ( (LongLong)~MaxLongLong );

    constexpr SizeT MaxSizeT = ( (SizeT)~( (SizeT)0 ) );
    constexpr SSizeT MaxSSizeT = ( (SSizeT)( MaxSizeT >> 1 ) );
    constexpr SSizeT MinSSizeT = ( (SSizeT)~MaxSSizeT );

    constexpr UInt MaxUInt = ( (UInt)~( (UInt)0 ) );
    constexpr Int MaxInt = ( (Int)( MaxUInt >> 1 ) );
    constexpr Int  MinInt = ( (Int)~MaxInt );

    constexpr DWord32 MaxDWord32 = ( (DWord32)~( (DWord32)0 ) );
    constexpr DWord64 MaxDWord64 = ( (DWord64)~( (DWord64)0 ) );

    template<typename T>
    using Nullable = std::optional<T>;


    
#define HCC_TEXT(quote) L##quote
#define CURRENT_FUNCTION __FUNCTIONW__
#define CURRENT_FILE __FILEW__

    HCC_EXPORT void CheckHRESULT( HRESULT hresult );
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, IUnknown* itf );
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, const wchar_t* function, const wchar_t* filename, int lineNumber );
    HCC_EXPORT void CheckHRESULT( HRESULT hresult, IUnknown* itf, const wchar_t* function, const wchar_t* filename, int lineNumber );
    HCC_EXPORT WideString FormatError( DWORD errorId );
    HCC_EXPORT AnsiString FormatErrorA( DWORD errorId );
    HCC_EXPORT void ThrowLastOSError( );
    HCC_EXPORT void ThrowOSError( DWORD errorId );
    [[noreturn]] HCC_EXPORT void ThrowNoInterface( );
    [[noreturn]] HCC_EXPORT void ThrowPointerIsNULL( );
    [[noreturn]] HCC_EXPORT void ThrowInvalidHandle( );
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( );
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( const char* message );
    [[noreturn]] HCC_EXPORT void ThrowNullReferenceException( const wchar_t* message );
    HCC_EXPORT HRESULT HRESULTFromException( const std::exception& exception );

    template <typename T>
    inline void CheckPointerNotNull( T* ptr )
    {
        if ( !ptr )
        {
            ThrowPointerIsNULL( );
        }
    }
    namespace Environment
    {
        HCC_EXPORT bool IsComputerDomainJoined( );
    }

    template<typename T>
    inline constexpr bool False_v = false;

    template<typename T>
    inline constexpr bool True_v = true;

    class Exception;
    HCC_EXPORT void ReportException( const Exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber );
    HCC_EXPORT void ReportException( const std::exception& exception, const wchar_t* function, const wchar_t* filename, int lineNumber );
    HCC_EXPORT void ReportUnknownException( const wchar_t* function, const wchar_t* filename, int lineNumber );

    /// <summary>
    /// Thrown by Thread::Exit 
    /// </summary>
    class ThreadAbortException
    {
        DWORD exitCode_;
    public:
        ThreadAbortException( DWORD exitCode )
            : exitCode_( exitCode )
        {
        }
        DWORD ExitCode( ) const
        {
            return exitCode_;
        }
    };

#define HCC_CATCH_ALL_AND_REPORT_EXCEPTION \
    catch ( const Harlinn::Common::Core::ThreadAbortException& /*exception*/ ) \
    { \
        throw; \
    } \
    catch ( const Harlinn::Common::Core::Exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    catch ( const std::exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    catch ( ... ) \
    { \
        Harlinn::Common::Core::ReportUnknownException( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    }

#define HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT( ) \
    catch ( const Harlinn::Common::Core::Exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
        return exception.GetHRESULT( ); \
    } \
    catch ( const std::exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
        return E_FAIL; \
    } \
    catch ( ... ) \
    { \
        Harlinn::Common::Core::ReportUnknownException( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
        return E_FAIL; \
    } \
    return S_OK

#define HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN( ) \
    catch ( const Harlinn::Common::Core::Exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    catch ( const std::exception& exception ) \
    { \
        Harlinn::Common::Core::ReportException( exception, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    catch ( ... ) \
    { \
        Harlinn::Common::Core::ReportUnknownException( CURRENT_FUNCTION, CURRENT_FILE, __LINE__ ); \
    } \
    return




}


#endif
