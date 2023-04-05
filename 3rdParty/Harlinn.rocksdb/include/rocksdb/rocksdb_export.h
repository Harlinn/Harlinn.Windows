#pragma once
#ifndef HARLINN_ROCKSDB_ROCKSDB_EXPORT_H_
#define HARLINN_ROCKSDB_ROCKSDB_EXPORT_H_

#ifndef ROCKSDB_DLL
#define ROCKSDB_DLL
#endif

#ifdef _WIN32
#ifdef ROCKSDB_DLL
#ifdef ROCKSDB_LIBRARY_EXPORTS
#define ROCKSDB_LIBRARY_API __declspec(dllexport)
#else
#define ROCKSDB_LIBRARY_API __declspec(dllimport)
#pragma comment(lib,"Harlinn.rocksdb.lib")
#endif
#else
#define ROCKSDB_LIBRARY_API
#endif
#else
#define ROCKSDB_LIBRARY_API
#endif

#ifndef OS_WIN
#define OS_WIN
#endif


#endif
