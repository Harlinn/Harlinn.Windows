#pragma once
#ifndef HARLINN_UPB_UPB_EXPORT_H_
#define HARLINN_UPB_UPB_EXPORT_H_

#ifdef BUILDING_HARLINN_UPB
#define UPB_EXPORT __declspec(dllexport)    
#else
#define UPB_EXPORT __declspec(dllimport)    
#pragma comment(lib,"Harlinn.upb.lib")
#endif


#endif
