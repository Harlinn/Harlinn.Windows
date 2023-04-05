#pragma once
#ifndef HARLINN_BULLET_BULLET_EXPORT_H_
#define HARLINN_BULLET_BULLET_EXPORT_H_

#ifdef BUILDING_HARLINN_BULLET
#define BT_EXPORT __declspec(dllexport)
#else
#define BT_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.bullet.lib")
#endif

#ifndef BT_THREADSAFE
#define BT_THREADSAFE 1
#endif

#ifndef BT_USE_SSE_IN_API
#define BT_USE_SSE_IN_API 1
#endif

#ifndef B3_USE_CLEW
#define B3_USE_CLEW 1
#endif

#endif
