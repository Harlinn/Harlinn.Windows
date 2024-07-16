#ifndef GEO_CONFIG_H
#define GEO_CONFIG_H

/* Define if you have the ANSI C header files.  */
#ifndef STDC_HEADERS
#define STDC_HEADERS 1
#endif

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
/* #undef WORDS_BIGENDIAN */

/* Define if you have the <stdlib.h> header file.  */
#ifndef HAVE_STDLIB_H
#define HAVE_STDLIB_H 1
#endif

/* Define if you have the <string.h> header file.  */
#ifndef HAVE_STRING_H
#define HAVE_STRING_H 1
#endif

/* Build as DLL */
#define BUILD_AS_DLL      1

#ifdef BUILDING_HARLINN_GEOTIFF
 #define GTIF_DLL __declspec(dllexport)
#else
 #define GTIF_DLL __declspec(dllimport)
 #pragma comment(lib,"Harlinn.geotiff.lib")
#endif


/* Turn off TOWGS84 if necessary */
/* #define GEO_NORMALIZE_DISABLE_TOWGS84 1 */

#endif /* ndef GEO_CONFIG_H */
