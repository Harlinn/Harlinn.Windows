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
