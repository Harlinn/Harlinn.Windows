#pragma once
#ifndef __GFLAGSDEF_H__
#define __GFLAGSDEF_H__

#ifdef BUILDING_HARLINN_GFLAGS
#define GFLAGS_DLL_DECL __declspec(dllexport)
#else
#define GFLAGS_DLL_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.gflags.lib")
#endif 
#ifndef GFLAGS_DLL_DECLARE_FLAG
#define GFLAGS_DLL_DECLARE_FLAG GFLAGS_DLL_DECL
#endif


#endif
