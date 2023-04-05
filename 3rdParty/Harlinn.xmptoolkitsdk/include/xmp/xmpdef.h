#pragma once
#ifndef HARLINN_XMPTOOLKITSDK_XMPDEF_H_
#define HARLINN_XMPTOOLKITSDK_XMPDEF_H_

#ifdef BUILDING_HARLINN_XMPTOOLKITSDK
#define HXMP_EXPORT __declspec(dllexport)
#define HXMP_EXTERN_TEMPLATE
#else
#define HXMP_EXPORT __declspec(dllimport)
#define HXMP_EXTERN_TEMPLATE extern
#pragma comment(lib,"Harlinn.xmptoolkitsdk.lib")
#endif

#define WIN_ENV 1
#define ENABLE_CPP_DOM_MODEL 1

#define XMP_PUBLIC HXMP_EXPORT

#ifndef _DEBUG
//#define HXMP_USE_INLINE 1
#endif

#ifdef HXMP_USE_INLINE
#define HXMP_INLINE_DECL
#define HXMP_INLINE inline
#else
#define HXMP_INLINE_DECL HXMP_EXPORT
#define HXMP_INLINE 
#endif

#ifndef XMP_COMPONENT_INT_NAMESPACE
#define XMP_COMPONENT_INT_NAMESPACE AdobeXMPCore_Int
#endif

#ifndef XMP_DynamicBuild
#define XMP_DynamicBuild 1
#endif


#endif
