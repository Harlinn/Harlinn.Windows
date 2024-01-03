#pragma once
#ifndef __HTDEF_H__
#define __HTDEF_H__
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
#include <HCCException.h>
#include <HCCBinaryReader.h>
#include <HCCBinaryWriter.h>
#include <HCCPersistent.h>


#ifdef BUILDING_HARLINN_TIMESERIES
#define HT_EXPORT __declspec(dllexport)
#define HT_TEMPLATE_EXPORT __declspec(dllexport)
#define HT_TEMPLATE_EXPORT_DECL
#else
#define HT_EXPORT __declspec(dllimport)
#define HT_TEMPLATE_EXPORT __declspec(dllimport)
#define HT_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Timeseries.lib")
#endif

#ifdef _DEBUG
#define HT_INLINE_DECL HT_EXPORT
#define HT_INLINE 
#else
#define HT_INLINE_DECL 
#define HT_INLINE inline
#endif

namespace Harlinn::Common::Core
{
}
namespace Harlinn::Timeseries
{
    using namespace Harlinn::Common::Core;
}


#endif
