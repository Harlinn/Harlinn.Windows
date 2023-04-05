#pragma once
#ifndef HARLINN_BUSSIK_BUSSIK_EXPORT_H_
#define HARLINN_BUSSIK_BUSSIK_EXPORT_H_

#ifdef BUILDING_HARLINN_BUSSIK
#define BUSSIK_EXPORT __declspec(dllexport) 
#else
#define BUSSIK_EXPORT __declspec(dllimport) 
#pragma comment(lib,"Harlinn.BussIK.lib")
#endif

#endif
