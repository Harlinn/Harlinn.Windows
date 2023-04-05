#pragma once
#ifndef __CRNLIBDEF_H__
#define __CRNLIBDEF_H__

#ifdef BUILDING_HARLINN_CRNLIB
#define HCRNLIB_EXPORT __declspec(dllexport)
#else
#define HCRNLIB_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.crnlib.lib")
#endif

#endif
