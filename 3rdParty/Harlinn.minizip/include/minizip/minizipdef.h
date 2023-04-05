#pragma once
#ifndef __MINIZIPDEF_H__
#define __MINIZIPDEF_H__

#ifdef BUILDING_HARLINN_MINIZIP
#define MINIZIP_EXPORT __declspec(dllexport)

#ifndef MAXU32
#define MAXU32 UINT32_MAX
#endif

#else
#define MINIZIP_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.minizip.lib")
#endif

#define HAVE_BZIP2 1
#define HAS_STDINT_H 1

//Non-standard, used by kmlbase and iomem_simple.c
#define ZIP_MAX_UNCOMPRESSED_SIZE 2147483647


#endif
