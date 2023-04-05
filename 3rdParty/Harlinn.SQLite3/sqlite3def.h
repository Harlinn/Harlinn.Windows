#pragma once
#ifndef __SQLITE3DEF_H__
#define __SQLITE3DEF_H__

#ifdef BUILDING_HARLINN_SQLITE3
#define SQLITE_API __declspec(dllexport)
#else
#define SQLITE_API __declspec(dllimport)
#pragma comment(lib,"Harlinn.SQLite3.lib")
#endif

#endif
