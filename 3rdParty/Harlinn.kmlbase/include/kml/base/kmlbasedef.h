#pragma once
#ifndef __KMLBASEDEF_H__
#define __KMLBASEDEF_H__

#ifdef BUILDING_HARLINN_KMLBASE
#define KMLBASE_EXPORT __declspec(dllexport)
#else
#define KMLBASE_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.kmlbase.lib")
#endif

#endif
