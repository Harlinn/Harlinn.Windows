#pragma once
#ifndef __SNAPPYDEF_H__
#define __SNAPPYDEF_H__

#ifdef BUILDING_HARLINN_SNAPPY
#define SNAPPY_EXPORT __declspec(dllexport)
#else
#define SNAPPY_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.snappy.lib")
#endif

#define SNAPPY_HAVE_VECTOR_BYTE_SHUFFLE 1
#define SNAPPY_HAVE_SSSE3 1


#endif
