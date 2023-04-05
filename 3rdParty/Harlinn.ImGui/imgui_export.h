#pragma once
#ifndef __HIMGUIDEF_H__
#define __HIMGUIDEF_H__

#include <HWDef.h>

#ifdef BUILDING_HARLINN_IMGUI
#define HIG_EXPORT __declspec(dllexport)
#define HIG_TEMPLATE_EXPORT __declspec(dllexport)
#define HIG_TEMPLATE_EXPORT_DECL
#else
#define HIG_EXPORT __declspec(dllimport)
#define HIG_TEMPLATE_EXPORT __declspec(dllimport)
#define HIG_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.ImGui.lib")
#endif

#ifdef _DEBUG
#define HIG_INLINE_DECL HIG_EXPORT
#define HIG_INLINE 
#else
#define HIG_INLINE_DECL 
#define HIG_INLINE inline
#endif


#define IMGUI_API HIG_EXPORT
#define IMPLOT_API HIG_EXPORT



#endif
