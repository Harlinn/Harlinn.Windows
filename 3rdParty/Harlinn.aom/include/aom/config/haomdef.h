#pragma once
#ifndef HARLINN_WINDOWS_HAOMDEF_H_
#define HARLINN_WINDOWS_HAOMDEF_H_

#ifdef BUILDING_HARLINN_AOM
#define HAOM_EXPORT __declspec(dllexport)
#else
#define HAOM_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.aom.lib")
#endif

#endif
