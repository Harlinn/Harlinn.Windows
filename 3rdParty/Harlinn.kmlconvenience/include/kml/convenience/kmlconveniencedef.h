#pragma once
#ifndef __KMLCONVENIENCEDEF_H__
#define __KMLCONVENIENCEDEF_H__

#ifdef BUILDING_HARLINN_KMLCONVENIENCE
#define KMLCONVENIENCE_EXPORT __declspec(dllexport)
#else
#define KMLCONVENIENCE_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.kmlconvenience.lib")
#endif


#endif
