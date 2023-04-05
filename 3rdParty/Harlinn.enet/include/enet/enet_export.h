#pragma once
#ifndef HARLINN_ENET_ENET_EXPORT_H_
#define HARLINN_ENET_ENET_EXPORT_H_

#ifndef ENET_DLL
#define ENET_DLL 1
#endif

#ifdef BUILDING_HARLINN_ENET
#define ENET_EXPORT __declspec(dllexport)
#ifndef ENET_BUILDING_LIB
#define ENET_BUILDING_LIB 1
#endif
#else
#define ENET_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.enet.lib")
#endif

#endif
