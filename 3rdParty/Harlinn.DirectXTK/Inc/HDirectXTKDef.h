#pragma once
#ifndef HARLINN_WINDOWS_HDIRECTXTKDEF_H_
#define HARLINN_WINDOWS_HDIRECTXTKDEF_H_

#ifdef BUILDING_HARLINN_DIRECTXTK
#define HDXTK_EXPORT __declspec(dllexport)
#define HDXTK_TEMPLATE_EXPORT __declspec(dllexport)
#define HDXTK_TEMPLATE_EXPORT_DECL
#else
#define HDXTK_EXPORT __declspec(dllimport)
#define HDXTK_TEMPLATE_EXPORT __declspec(dllimport)
#define HDXTK_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.DirectXTK.lib")
#endif

#endif
