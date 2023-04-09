#pragma once
#ifndef HARLINN_SPIRV_CROSS_EXPORT_H_
#define HARLINN_SPIRV_CROSS_EXPORT_H_

#ifdef BUILDING_HARLINN_SPIRV_CROSS
#define SPVC_EXPORT_SYMBOLS 1
#define SPVC_EXPORT __declspec(dllexport)
#else
#define SPVC_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.spirv-cross.lib")
#endif



#endif
