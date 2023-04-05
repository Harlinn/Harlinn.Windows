#pragma once
#ifndef __KMLREGIONATORDEF_H__
#define __KMLREGIONATORDEF_H__

#ifdef BUILDING_HARLINN_KMLREGIONATOR
#define KMLREGIONATOR_EXPORT __declspec(dllexport)
#else
#define KMLREGIONATOR_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.kmlregionator.lib")
#endif


#endif
