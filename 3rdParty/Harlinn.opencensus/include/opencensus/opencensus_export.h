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

#ifndef LOCKS_EXCLUDED
#define LOCKS_EXCLUDED(m)
#endif

#ifndef GUARDED_BY
#define GUARDED_BY(x)
#endif

#ifndef EXCLUSIVE_LOCKS_REQUIRED
#define EXCLUSIVE_LOCKS_REQUIRED(x,y)
#endif

#ifndef ACQUIRED_AFTER
#define ACQUIRED_AFTER(x)
#endif





#endif
