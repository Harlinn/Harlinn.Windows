#pragma once
#ifndef HARLINN_TINYOBJLOADER_TINY_OBJ_LOADER_EXPORTS_H_
#define HARLINN_TINYOBJLOADER_TINY_OBJ_LOADER_EXPORTS_H_

#ifdef BUILDING_HARLINN_TINYOBJLOADER
#define TOL_EXPORT __declspec(dllexport)
#else
#define TOL_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.tinyobjloader.lib")
#endif


#endif
