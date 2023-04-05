#pragma once
#ifndef __HIGHWAYDEF_H__
#define __HIGHWAYDEF_H__

#ifdef BUILDING_HARLINN_HIGHWAY
#define HIGHWAY_EXPORT __declspec(dllexport)
#else
#define HIGHWAY_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.highway.lib")
#endif


#endif
