#pragma once
#ifndef __KMLXSDDEF_H__
#define __KMLXSDDEF_H__

#ifdef BUILDING_HARLINN_KMLXSD
#define KMLXSD_EXPORT __declspec(dllexport)
#else
#define KMLXSD_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.kmlxsd.lib")
#endif


#endif
