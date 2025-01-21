#pragma once
#ifndef __HWDEF_H__
#define __HWDEF_H__
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

#include <HCCDef.h>
#include <HCCGuid.h>
#include <HCCCom.h>
#include <HCCDateTime.h>
#include <HCCString.h>
#include <HCCTraits.h>
#include <HCCMath.h>
#include <HCCSync.h>

#ifdef BUILDING_HARLINN_WINDOWS
#define HW_EXPORT __declspec(dllexport)
#define HW_TEMPLATE_EXPORT __declspec(dllexport)
#define HW_TEMPLATE_EXPORT_DECL
#else
#define HW_EXPORT __declspec(dllimport)
#define HW_TEMPLATE_EXPORT __declspec(dllimport)
#define HW_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Windows.lib")
#endif

#ifdef _DEBUG
#define HW_INLINE_DECL HW_EXPORT
#define HW_INLINE 
#else
#define HW_INLINE_DECL 
#define HW_INLINE inline
#endif

namespace Harlinn::Windows
{
    using namespace Harlinn::Common::Core;
}



#endif
