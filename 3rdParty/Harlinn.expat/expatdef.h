#pragma once
#ifndef __EXPATDEF_H__
#define __EXPATDEF_H__

#ifdef BUILDING_HARLINN_EXPAT
#define XMLIMPORT __declspec(dllexport)
#else
#define XMLIMPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.expat.lib")
#endif

#endif
