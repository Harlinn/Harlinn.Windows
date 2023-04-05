#pragma once
#ifndef HARLINN_COMMON_CONFIG_HCCFG_EXPORT_H_
#define HARLINN_COMMON_CONFIG_HCCFG_EXPORT_H_

#ifdef BUILDING_HARLINN_COMMON_CONFIG
#define HCCFG_EXPORT __declspec(dllexport)
#define HCCFG_TEMPLATE_EXPORT __declspec(dllexport)
#define HCCFG_TEMPLATE_EXPORT_DECL
#else
#define HCCFG_EXPORT __declspec(dllimport)
#define HCCFG_TEMPLATE_EXPORT __declspec(dllimport)
#define HCCFG_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Common.Config.lib")
#endif


#endif