#pragma once
#ifndef __KMLENGINEDEF_H__

#ifdef BUILDING_HARLINN_KMLENGINE
#define KMLENGINE_EXPORT __declspec(dllexport)
#else
#define KMLENGINE_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.kmlengine.lib")
#endif

#endif 

