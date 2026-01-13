#pragma once
#ifndef HARLINN_COMMON_CORE_HCCEXPORT_H_
#define HARLINN_COMMON_CORE_HCCEXPORT_H_

/*
   Copyright 2024-2026 Espen Harlinn

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

#include "HCCDef.h"

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


namespace Harlinn::Math
{
    class Half;
}

namespace Harlinn::Common::Core
{
    HCC_EXPORT WideString ToWideString( const Harlinn::Math::Half& value );
    HCC_EXPORT AnsiString ToAnsiString( const Harlinn::Math::Half& value );
    
}


#endif
