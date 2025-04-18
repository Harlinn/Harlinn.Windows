
#ifndef JXL_EXPORT_H
#define JXL_EXPORT_H

#ifdef JXL_STATIC_DEFINE
#  define JXL_EXPORT
#  define JXL_NO_EXPORT
#else
#  ifndef JXL_EXPORT
#    ifdef JXL_INTERNAL_LIBRARY_BUILD
        /* We are building this library */
#      define JXL_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define JXL_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.jxl.lib")
#    endif
#  endif

#  ifndef JXL_NO_EXPORT
#    define JXL_NO_EXPORT 
#  endif
#endif

#ifndef JXL_DEPRECATED
#  define JXL_DEPRECATED __declspec(deprecated)
#endif

#ifndef JXL_DEPRECATED_EXPORT
#  define JXL_DEPRECATED_EXPORT JXL_EXPORT JXL_DEPRECATED
#endif

#ifndef JXL_DEPRECATED_NO_EXPORT
#  define JXL_DEPRECATED_NO_EXPORT JXL_NO_EXPORT JXL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef JXL_NO_DEPRECATED
#    define JXL_NO_DEPRECATED
#  endif
#endif

#endif /* JXL_EXPORT_H */
