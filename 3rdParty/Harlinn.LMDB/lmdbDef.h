#pragma once
#ifndef __LMDBDEF_H__
#define __LMDBDEF_H__

#ifdef BUILDING_HARLINN_LIBLMDB
#define LIBLMDB_EXPORT __declspec(dllexport)
#else
#define LIBLMDB_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.LMDB.lib")
#endif


#endif
