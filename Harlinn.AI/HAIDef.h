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
#pragma once
#ifndef HARLINN_WINDOWS_HAIDEF_H_
#define HARLINN_WINDOWS_HAIDEF_H_

#include "HWDef.h"
#include "HWDXGI.h"
#include "HWGraphics.h"
#include "HWGraphicsD3D12.h"
#include "HWGraphicsD3D11.h"
#include "HWGraphicsD3D11On12.h"
#include "HWDXCore.h"
#include "HWMediaEngine.h"
#include "HCCActiveObject.h"
#include "Harlinn/Math/VectorMath.h"

#ifdef BUILDING_HARLINN_AI
#define HAI_EXPORT __declspec(dllexport)
#define HAI_TEMPLATE_EXPORT __declspec(dllexport)
#define HAI_TEMPLATE_EXPORT_DECL
#else
#define HAI_EXPORT __declspec(dllimport)
#define HAI_TEMPLATE_EXPORT __declspec(dllimport)
#define HAI_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.ai.lib")
#endif

#ifdef _DEBUG
#define HAI_INLINE_DECL HW_EXPORT
#define HAI_INLINE 
#else
#define HAI_INLINE_DECL 
#define HAI_INLINE inline
#endif

namespace Harlinn::AI
{
    using namespace Harlinn;
    using namespace Harlinn::Common;
    using namespace Harlinn::Common::Core;
    using namespace Harlinn::Windows;
    HAI_EXPORT UInt32 GetHAIVersion( );
}


#endif
