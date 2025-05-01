#pragma once
#ifndef DOUBLECONVERSIONEXPORT_H_
#define DOUBLECONVERSIONEXPORT_H_

#ifdef BUILDING_HARLINN_DOUBLE_CONVERSION
#define DBLCNV_EXPORT __declspec(dllexport)
#define DBLCNV_TEMPLATE_EXPORT __declspec(dllexport)
#define DBLCNV_TEMPLATE_EXPORT_DECL
#else
#define DBLCNV_EXPORT __declspec(dllimport)
#define DBLCNV_TEMPLATE_EXPORT __declspec(dllimport)
#define DBLCNV_TEMPLATE_EXPORT_DECL __declspec(dllimport)

#pragma comment(lib,"Harlinn.double-conversion.lib")
#endif

#endif
