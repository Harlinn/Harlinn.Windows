#pragma once
#ifndef __HODBCDEF_H__
#define __HODBCDEF_H__
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

#include <HCCDef.h>
#include <HCCGuid.h>
#include <HCCDateTime.h>
#include <HCCString.h>
#include <HCCBinary.h>
#include <HCCCurrency.h>
#include <HCCConcepts.h>
#include <HCCSync.h>
#include <HCCBinaryReader.h>
#include <HCCBinaryWriter.h>


#ifdef BUILDING_HARLINN_ODBC
#define HODBC_EXPORT __declspec(dllexport)
#define HODBC_TEMPLATE_EXPORT __declspec(dllexport)
#define HODBC_TEMPLATE_EXPORT_DECL
#else
#define HODBC_EXPORT __declspec(dllimport)
#define HODBC_TEMPLATE_EXPORT __declspec(dllimport)
#define HODBC_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.ODBC.lib")
#endif

#ifdef _DEBUG
#define HODBC_INLINE_DECL HODBC_EXPORT
#define HODBC_INLINE 
#else
#define HODBC_INLINE_DECL 
#define HODBC_INLINE inline
#endif

namespace Harlinn::Common::Core
{

}
namespace Harlinn::ODBC
{
    using namespace Harlinn::Common::Core;
}


#endif

