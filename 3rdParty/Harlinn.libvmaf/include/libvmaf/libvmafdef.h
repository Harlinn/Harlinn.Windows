#pragma once
#ifndef HARLINN_WINDOWS_LIBVMAF_LIBVMAFDEF_H_
#define HARLINN_WINDOWS_LIBVMAF_LIBVMAFDEF_H_

#ifdef BUILDING_HARLINN_LIBVMAF
#define HLIBVMAF_EXPORT __declspec(dllexport)
#else
#define HLIBVMAF_EXPORT __declspec(dllexport)
#pragma comment(lib,"Harlinn.libvmaf.lib")
#endif


#endif
