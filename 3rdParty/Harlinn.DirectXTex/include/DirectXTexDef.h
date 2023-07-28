#pragma once
#ifndef DIRECTXTEX_H_
#define DIRECTXTEX_H_

#ifndef __d3d12_h__
#include <d3d12.h>
#endif

#ifdef BUILDING_HARLINN_DIRECTXTEX
#define HDXT_EXPORT __declspec(dllexport)
#define HDXT_TEMPLATE_EXPORT __declspec(dllexport)
#define HDXT_TEMPLATE_EXPORT_DECL
#else
#define HDXT_EXPORT __declspec(dllimport)
#define HDXT_TEMPLATE_EXPORT __declspec(dllimport)
#define HDXT_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.DirectXTex.lib")
#endif

#ifdef _DEBUG
#define HDXT_INLINE_DECL HDXT_EXPORT
#define HDXT_INLINE 
#else
#define HDXT_INLINE_DECL 
#define HDXT_INLINE inline
#endif


#endif
