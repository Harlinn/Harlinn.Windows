#pragma once
#ifndef HARLINN_CROSSGUID_CROSSGUID_EXPORT_H_
#define HARLINN_CROSSGUID_CROSSGUID_EXPORT_H_

#ifdef BUILDING_HARLINN_CROSSGUID
#define CROSSGUID_EXPORT __declspec(dllexport)
#else
#define CROSSGUID_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.base64.lib")
#endif

#endif

