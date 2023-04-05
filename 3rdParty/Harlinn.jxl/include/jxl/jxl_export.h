#pragma once
#ifndef HARLINN_WINDOWS_JXL_EXPORT_H_
#define HARLINN_WINDOWS_JXL_EXPORT_H_

#ifdef BUILDING_HARLINN_JXL
#define JXL_EXPORT __declspec(dllexport)
#define JXL_DEPRECATED
#else
#define JXL_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.jxl.lib")
#define JXL_DEPRECATED
#endif

#define JPEGXL_MAJOR_VERSION 0
#define JPEGXL_MINOR_VERSION 5
#define JPEGXL_PATCH_VERSION 0

#define JPEGXL_ENABLE_SKCMS 1
#define JPEGXL_ENABLE_JPEG 1
#define JPEGXL_ENABLE_GIF 1



#endif
