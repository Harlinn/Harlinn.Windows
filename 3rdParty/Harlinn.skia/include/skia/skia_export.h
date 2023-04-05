#pragma once
#ifndef HARLINN_SKIA_SKIA_EXPORT_H_
#define HARLINN_SKIA_SKIA_EXPORT_H_

#ifndef SKIA_STATIC
 #ifndef SKIA_DLL
  #define SKIA_DLL 1
 #endif
#endif

#ifndef SK_API
 #ifdef SKIA_DLL
  #ifdef BUILDING_HARLINN_SKIA
   #define SK_API __declspec(dllexport)
   #define SK_TEMPLATE_API __declspec(dllexport)
   #define SK_TEMPLATE_API_DECL
  #else
   #define SK_API __declspec(dllimport)
   #pragma comment(lib,"Harlinn.skia.lib")
   #define SK_TEMPLATE_API __declspec(dllimport)
   #define SK_TEMPLATE_API_DECL __declspec(dllimport) 
#endif
 #else
  #define SK_API
 #endif
#endif


#endif
