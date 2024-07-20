#pragma once
#ifndef HARLINN_WINDOWS_FLATBUFFERS_EXPORT_H_
#define HARLINN_WINDOWS_FLATBUFFERS_EXPORT_H_

#ifdef BUILDING_HARLINN_FLATBUFFERS
#define FLATBUFFERS_EXPORT __declspec(dllexport)
#else
#define FLATBUFFERS_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.flatbuffers.lib")
#endif


#endif
