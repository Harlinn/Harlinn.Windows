#pragma once
#ifndef HARLINN_BASE64_BASE64_EXPORT_H_
#define HARLINN_BASE64_BASE64_EXPORT_H_

#ifdef BUILDING_HARLINN_BASE64
#define BASE64_EXPORT __declspec(dllexport)
#else
#define BASE64_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.base64.lib")
#endif

#endif
