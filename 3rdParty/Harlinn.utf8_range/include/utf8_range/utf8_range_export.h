#pragma once
#ifndef HARLINN_UTF8_RANGE_UTF8_RANGE_EXPORT_H_
#define HARLINN_UTF8_RANGE_UTF8_RANGE_EXPORT_H_

#ifdef BUILDING_HARLINN_UTF8_RANGE
#define UTF8_RANGE_EXPORT __declspec(dllexport)
#define UTF8_RANGE_TEMPLATE_EXPORT __declspec(dllexport)
#define UTF8_RANGE_TEMPLATE_EXPORT_DECL
#else
#define UTF8_RANGE_EXPORT __declspec(dllimport)
#define UTF8_RANGE_TEMPLATE_EXPORT __declspec(dllimport)
#define UTF8_RANGE_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.utf8_range.lib")
#endif

#endif
