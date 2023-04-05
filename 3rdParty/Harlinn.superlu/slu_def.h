#pragma once
#ifndef __SLU_DEF_H__
#define __SLU_DEF_H__

#ifdef BUILDING_HARLINN_SUPERLU 
#define SUPERLU_EXPORT __declspec(dllexport)
#else
#define SUPERLU_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.superlu.lib")
#endif 


#endif
