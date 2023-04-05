#pragma once
#ifndef __BZIP2DEF_H__
#define __BZIP2DEF_H__

#ifdef BUILDING_HARLINN_BZIP2
#define BZIP2_EXPORT __declspec(dllexport)
#else
#define BZIP2_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.bzip2.lib")
#endif


#endif
