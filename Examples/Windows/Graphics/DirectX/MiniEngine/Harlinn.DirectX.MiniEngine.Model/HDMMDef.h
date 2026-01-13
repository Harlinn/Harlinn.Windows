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
#ifndef HDMMDEF_H_
#define HDMMDEF_H_

#include <HDMCDef.h>

#ifdef BUILDING_HARLINN_DIRECTX_MINIENGINE_MODEL
#define HDMM_EXPORT __declspec(dllexport)
#define HDMM_TEMPLATE_EXPORT __declspec(dllexport)
#define HDMM_TEMPLATE_EXPORT_DECL
#else
#define HDMM_EXPORT __declspec(dllimport)
#define HDMM_TEMPLATE_EXPORT __declspec(dllimport)
#define HDMM_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.DirectX.MiniEngine.Model.lib")
#endif

#ifdef _DEBUG
#define HDMM_INLINE_DECL HDMM_EXPORT
#define HDMM_INLINE 
#else
#define HDMM_INLINE_DECL 
#define HDMM_INLINE inline
#endif



#endif
