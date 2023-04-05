#pragma once
#ifndef __HGIFDEF_H__
#define __HGIFDEF_H__

#ifdef BUILDING_HARLINN_GIF
#define HGIF_EXPORT __declspec(dllexport)
#else
#define HGIF_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.gif.lib" )
#endif

#endif

