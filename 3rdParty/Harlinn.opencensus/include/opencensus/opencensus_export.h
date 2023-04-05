#pragma once
#ifndef HARLINN_OPENCENSUS_OPENCENSUS_EXPORT_H_
#define HARLINN_OPENCENSUS_OPENCENSUS_EXPORT_H_

#ifdef BUILDING_HARLINN_OPENCENSUS
#define OPENCENSUS_EXPORT __declspec(dllexport)
#define OPENCENSUS_TEMPLATE_EXPORT __declspec(dllexport)
#define OPENCENSUS_TEMPLATE_EXPORT_DECL
#else
#define OPENCENSUS_EXPORT __declspec(dllimport)
#define OPENCENSUS_TEMPLATE_EXPORT __declspec(dllimport)
#define OPENCENSUS_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.opencensus.lib")
#endif

#endif
