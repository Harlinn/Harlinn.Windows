#pragma once
#ifndef __HODEF_H__
#define __HODEF_H__
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

#include <HCCDateTime.h>
#include <HCCString.h>
#include <HCCBlocks.h>
#include <HCCBinaryWriter.h>
#include <HCCConverters.h>
#include <HCCBitConverter.h>
#include <HCCSync.h>


#ifdef BUILDING_HARLINN_OCI
#define HO_EXPORT __declspec(dllexport)
#define HO_TEMPLATE_EXPORT __declspec(dllexport)
#define HO_TEMPLATE_EXPORT_DECL
#else
#define HO_EXPORT __declspec(dllimport)
#define HO_TEMPLATE_EXPORT __declspec(dllimport)
#define HO_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.OCI.lib")
#endif

#ifdef _DEBUG
#define HO_INLINE_DECL HO_EXPORT
#define HO_INLINE 
#else
#define HO_INLINE_DECL 
#define HO_INLINE inline
#endif

namespace Harlinn::Common::Core
{
}
namespace Harlinn::OCI
{
    using namespace Harlinn::Common::Core;
}


#endif
