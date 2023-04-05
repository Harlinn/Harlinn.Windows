#pragma once
#ifndef __AECDEF_H__
#define __AECDEF_H__

#ifdef BUILDING_HARLINN_AEC
#define LIBAEC_DLL_EXPORTED __declspec(dllexport)
#else
#define LIBAEC_DLL_EXPORTED __declspec(dllimport)
#pragma comment(lib,"Harlinn.aec.lib")
#endif


#endif
