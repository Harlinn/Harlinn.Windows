#pragma once
#ifndef HARLINN_PIEX_PIEXDEF_H_
#define HARLINN_PIEX_PIEXDEF_H_

#ifdef BUILDING_HARLINN_PIEX
#define HPIEX_EXPORT __declspec(dllexport)
#else
#define HPIEX_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.piex.lib" )
#endif

#endif
