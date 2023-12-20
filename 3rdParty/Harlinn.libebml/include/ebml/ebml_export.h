
#ifndef EBML_DLL_API_H
#define EBML_DLL_API_H

#define EBML_DLL_API
#define EBML_NO_EXPORT


#ifdef BUILDING_HARLINN_LIBEBML
#define EBML_EXPORT __declspec(dllexport)
#else
#define EBML_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.libebml.lib")
#endif



#ifndef EBML_DEPRECATED
#  define EBML_DEPRECATED __declspec(deprecated)
#endif

#ifndef EBML_DEPRECATED_EXPORT
#  define EBML_DEPRECATED_EXPORT EBML_DLL_API EBML_DEPRECATED
#endif

#ifndef EBML_DEPRECATED_NO_EXPORT
#  define EBML_DEPRECATED_NO_EXPORT EBML_NO_EXPORT EBML_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef EBML_NO_DEPRECATED
#    define EBML_NO_DEPRECATED
#  endif
#endif

#endif /* EBML_DLL_API_H */
