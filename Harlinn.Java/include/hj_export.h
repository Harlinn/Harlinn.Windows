#pragma once
#ifndef HARLINN_JAVA_HJ_EXPORT_H_
#define HARLINN_JAVA_HJ_EXPORT_H_

#ifdef BUILDING_HARLINN_JAVA
#define HJ_EXPORT __declspec(dllexport)
#else
#define HJ_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.Java.lib")
#endif

#endif
