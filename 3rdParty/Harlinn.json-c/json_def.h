#pragma once

#ifndef __JSON_DEF_H__
#define __JSON_DEF_H__

#ifdef BUILDING_HARLINN_JSON_C
#define JSON_EXPORT __declspec(dllexport)
#else
#define JSON_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.json-c.lib")
#endif


#endif