#pragma once
#ifndef __HCCDEF_H__
#define __HCCDEF_H__
/*
   Copyright 2024-2025 Espen Harlinn

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

#pragma warning(disable:4996)
#pragma warning(disable:4091)
#pragma warning(disable:4503)

#define OEMRESOURCE

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif

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
#include <DXCore.h>
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
#define DML_TARGET_VERSION_USE_LATEST 1
#include <DirectML.h>
#include <Dmo.h>
#include <mediaobj.h>
#include <mfobjects.h>
#include <mfidl.h>
#include <mfapi.h>
#include <mferror.h>
#include <mfreadwrite.h>
#include <mfmediaengine.h>
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
#include <ranges>
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
#include <random>

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
#include <fenv.h>


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

#include <Harlinn/Common/BasicTypes.h>

#define HCC_USE_COMMON 1

namespace Harlinn::Common::Core
{
    template<typename T>
    class BasicString;

    using WideString = BasicString<wchar_t>;
    using AnsiString = BasicString<char>;

    template<typename T>
    class BasicStringView;

    using WideStringView = BasicStringView<wchar_t>;
    using AnsiStringView = BasicStringView<char>;

    class Guid;
    class DateTime;
    class TimeSpan;
    class Currency;
    
    class Variant;
    class PropertyVariant;
    
    
#define HCC_TEXT(quote) L##quote
#define CURRENT_FUNCTION __FUNCTIONW__
#define CURRENT_FILE __FILEW__

    




}


#endif
