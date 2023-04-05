#pragma once
#ifndef HARLINN_WINDOWS_RTSPSERVERDEF_H_
#define HARLINN_WINDOWS_RTSPSERVERDEF_H_

#ifdef BUILDING_HARLINN_WINDOWS_RTSPSERVER
#define HW_RTSPSERVER_EXPORT __declspec(dllexport)
#define HW_RTSPSERVER_TEMPLATE_EXPORT __declspec(dllexport)
#define HW_RTSPSERVER_TEMPLATE_EXPORT_DECL
#else
#define HW_RTSPSERVER_EXPORT __declspec(dllimport)
#define HW_RTSPSERVER_TEMPLATE_EXPORT __declspec(dllimport)
#define HW_RTSPSERVER_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.RtspServer.lib")
#endif

#endif
