#pragma once
#ifndef DIRECTXMESHDEF_H_
#define DIRECTXMESHDEF_H_

#ifndef __d3d12_h__
#include <d3d12.h>
#endif

#ifdef BUILDING_HARLINN_DIRECTXMESH
#define HDXM_EXPORT __declspec(dllexport)
#define HDXM_TEMPLATE_EXPORT __declspec(dllexport)
#define HDXM_TEMPLATE_EXPORT_DECL
#else
#define HDXM_EXPORT __declspec(dllimport)
#define HDXM_TEMPLATE_EXPORT __declspec(dllimport)
#define HDXM_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.DirectXMesh.lib")
#endif

#ifdef _DEBUG
#define HDXM_INLINE_DECL HDXM_EXPORT
#define HDXM_INLINE 
#else
#define HDXM_INLINE_DECL 
#define HDXM_INLINE inline
#endif



#endif

