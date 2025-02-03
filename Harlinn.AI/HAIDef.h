#pragma once
#ifndef HARLINN_WINDOWS_HAIDEF_H_
#define HARLINN_WINDOWS_HAIDEF_H_

#include "HWDef.h"
#include "HWDXGI.h"
#include "HWGraphicsD3D12.h"
#include "HWMediaEngine.h"

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
    using namespace Harlinn::Windows;
    HAI_EXPORT UInt32 GetHAIVersion( );
}


#endif
