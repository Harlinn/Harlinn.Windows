#pragma once
#ifndef HARLINN_FLATBUFFERS_FLATBUFFERS_EXPORT_H_
#define HARLINN_FLATBUFFERS_FLATBUFFERS_EXPORT_H_

#ifdef BUILDING_HARLINN_FLATBUFFERS
#define FB_EXPORT __declspec(dllexport)
#else
#define FB_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.flatbuffers.lib")
#endif

#endif
