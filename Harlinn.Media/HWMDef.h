#pragma once
#ifndef HWMDEF_H_
#define HWMDEF_H_
/*
   Copyright 2024 Espen Harlinn

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

#include <HWDef.h>
#include <HCCRegistry.h>
#include <HCCIO.h>
#include <gst/gst.h>
#include <gst/rtsp/rtsp.h>
#include <gst/rtsp-server/rtsp-server.h>

#ifdef BUILDING_HARLINN_MEDIA
#define HWM_EXPORT __declspec(dllexport)
#define HWM_TEMPLATE_EXPORT __declspec(dllexport)
#define HWM_TEMPLATE_EXPORT_DECL
#else
#define HWM_EXPORT __declspec(dllimport)
#define HWM_TEMPLATE_EXPORT __declspec(dllimport)
#define HWM_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Media.lib")
#endif

#ifdef _DEBUG
#define HWM_INLINE_DECL HWM_EXPORT
#define HWM_INLINE 
#else
#define HWM_INLINE_DECL 
#define HWM_INLINE inline
#endif

namespace Harlinn::Common::Core
{
}
namespace Harlinn::Windows
{
    
}
namespace Harlinn::Media
{
    using namespace Harlinn::Common::Core;
    using namespace Harlinn::Windows;
}

using ssize_t = std::make_signed_t<size_t>;



#endif
