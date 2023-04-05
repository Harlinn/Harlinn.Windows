#pragma once
#ifndef __KMLDOMDEF_H__
#define __KMLDOMDEF_H__

#ifdef BUILDING_HARLINN_KMLDOM
#define KMLDOM_EXPORT __declspec(dllexport)
#else
#define KMLDOM_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.kmldom.lib")
#endif

#endif
