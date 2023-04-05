#pragma once
#ifndef ABSL_EXPORT_H_
#define ABSL_EXPORT_H_

#ifdef BUILDING_HARLINN_ABSEIL
#define ABSEIL_EXPORT __declspec(dllexport)
#define ABSEIL_TEMPLATE_EXPORT __declspec(dllexport)
#define ABSEIL_TEMPLATE_EXPORT_DECL
#define ABSL_BUILD_DLL 1
#else
#define ABSEIL_EXPORT __declspec(dllimport)
#define ABSEIL_TEMPLATE_EXPORT __declspec(dllimport)
#define ABSEIL_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#define ABSL_CONSUME_DLL
#pragma comment(lib,"Harlinn.abseil.lib")
#endif


#endif
