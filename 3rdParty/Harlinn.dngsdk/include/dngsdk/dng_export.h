#pragma once
#ifndef HARLINN_DNG_EXPORT_H_
#define HARLINN_DNG_EXPORT_H_

#ifdef BUILDING_HARLINN_DNGSDK
#define DNG_EXPORT __declspec(dllexport)
#else
#define DNG_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.dngsdk.lib")
#endif

#endif