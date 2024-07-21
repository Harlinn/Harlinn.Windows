#pragma once
#ifndef HARLINN_LIVE555DEF_H_
#define HARLINN_LIVE555DEF_H_

#ifdef BUILDING_HARLINN_LIVE555
#define LIVE555_EXPORT __declspec(dllexport)
#define LIVE555_TEMPLATE_EXPORT __declspec(dllexport)
#define LIVE555_TEMPLATE_EXPORT_DECL
#else
#define LIVE555_EXPORT __declspec(dllimport)
#define LIVE555_TEMPLATE_EXPORT __declspec(dllimport)
#define LIVE555_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.live555.lib")
#pragma comment(lib,"Ws2_32.lib")
#endif

#ifdef _DEBUG
#define LIVE555_INLINE_DECL LIVE555_EXPORT
#define LIVE555_INLINE 
#else
#define LIVE555_INLINE_DECL 
#define LIVE555_INLINE inline
#endif


#endif
