#pragma once
#ifndef HARLINN_WINDOWS_HDIRECTXTK12DEF_H_
#define HARLINN_WINDOWS_HDIRECTXTK12DEF_H_

#ifdef BUILDING_HARLINN_DIRECTXTK12
#define HDXTK12_EXPORT __declspec(dllexport)
#define HDXTK12_TEMPLATE_EXPORT __declspec(dllexport)
#define HDXTK12_TEMPLATE_EXPORT_DECL
#else
#define HDXTK12_EXPORT __declspec(dllimport)
#define HDXTK12_TEMPLATE_EXPORT __declspec(dllimport)
#define HDXTK12_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.DirectXTK12.lib")
#endif

#endif
