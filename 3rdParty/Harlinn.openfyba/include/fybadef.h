#pragma once
#ifndef __FYBADEF_H__
#define __FYBADEF_H__

#ifdef BUILDING_HARLINN_OPENFYBA
#define SK_EntPnt_FYBA __declspec(dllexport)
#else
#define SK_EntPnt_FYBA __declspec(dllimport)
#pragma comment(lib,"Harlinn.openfyba.lib")
#endif

#endif
