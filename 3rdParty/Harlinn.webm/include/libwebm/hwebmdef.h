#pragma once
#ifndef __HWEBMDEF_H__
#define __HWEBMDEF_H__

#ifdef BUILDING_HARLINN_WEBM
#define WEBM_EXPORT __declspec(dllexport)
#else
#define WEBM_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.webm.lib")
#endif

#endif
