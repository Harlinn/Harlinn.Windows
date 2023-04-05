
#ifndef MYSOFA_EXPORT_H
#define MYSOFA_EXPORT_H

#ifdef MYSOFA_STATIC_DEFINE
#  define MYSOFA_EXPORT
#  define MYSOFA_NO_EXPORT
#else
#  ifndef MYSOFA_EXPORT
#    ifdef BUILDING_HARLINN_LIBMYSOFA
        /* We are building this library */
#      define MYSOFA_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define MYSOFA_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.libmysofa.lib")
#    endif
#  endif

#  ifndef MYSOFA_NO_EXPORT
#    define MYSOFA_NO_EXPORT 
#  endif
#endif

#ifndef MYSOFA_DEPRECATED
#  define MYSOFA_DEPRECATED __declspec(deprecated)
#endif

#ifndef MYSOFA_DEPRECATED_EXPORT
#  define MYSOFA_DEPRECATED_EXPORT MYSOFA_EXPORT MYSOFA_DEPRECATED
#endif

#ifndef MYSOFA_DEPRECATED_NO_EXPORT
#  define MYSOFA_DEPRECATED_NO_EXPORT MYSOFA_NO_EXPORT MYSOFA_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MYSOFA_NO_DEPRECATED
#    define MYSOFA_NO_DEPRECATED
#  endif
#endif

#endif /* MYSOFA_EXPORT_H */
