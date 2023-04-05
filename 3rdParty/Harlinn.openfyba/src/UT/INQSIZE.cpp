/* ------------------------------
 * Fil: InqSize.c
 * ------------------------------ */

#include "fyut.h"

#ifdef UNIX
#  ifndef _INCLUDE_POSIX_SOURCE
#    define _INCLUDE_POSIX_SOURCE
#  endif

#  ifndef _HPUX_SOURCE
#    define _HPUX_SOURCE
#  endif

#  include<stdio.h>
#  include<sys/time.h>
#  include<sys/types.h>
#  ifdef __APPLE__
#     include<sys/mount.h>
#  else
#     include<sys/vfs.h>
#  endif
#  include<fcntl.h>
#  include<sys/stat.h>
#  include<errno.h>
#endif

#ifdef OS2
#  define INCL_DOSFILEMGR
#  define INCL_DOSERRORS
#  include <os2.h>
#endif

#ifdef WIN32
#  include<sys/stat.h>
#endif

#ifdef BORLAND
#  include<sys/stat.h>
#endif



/*
AR-921013
CH UT_InqPathSize                                  Finn filstørrelse
CD ==================================================================
CD Formål:
CD Henter filstørrelsen for gitt fil.
CD
CD PARAMETERLISTE:
CD Type      Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char     *pszPath   i   Filnavn
CD long     *plSize    u   Filstørrelse
CD short     sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_InqPathSize(szPath,&lSize);
   ==================================================================
*/
SK_EntPnt_UT short UT_InqPathSize(const char *pszPath,long *plSize)
{
#ifdef UNIX
   struct stat buf; 
   int result;


   /* Hent filopplysninger */
   result = stat(pszPath,&buf);
   if (result == 0) {
      *plSize = (long)buf.st_size;
   }

   return (short)result;
#endif

#ifdef OS232
      APIRET rc;
		FILESTATUS3 PathInfoBuf;

      /* Hent filopplysninger */
      rc = DosQueryPathInfo(pszPath,FIL_STANDARD,&PathInfoBuf,sizeof(FILESTATUS3));

      if (rc == NO_ERROR) {
         *plSize = (long)PathInfoBuf.cbFile;
      }

      return (short)rc;
#endif

#ifdef OS216
	int rc;
	FILESTATUS PathInfoBuf;

   /* Hent filopplysninger */
   rc = DosQPathInfo(pszPath,FIL_STANDARD,(PBYTE)&PathInfoBuf,sizeof(FILESTATUS),0);

   if (rc == NO_ERROR) {
      *plSize = (long)PathInfoBuf.cbFile;
   }

	return (short)rc;
#endif

#ifdef WIN32
    struct _stat buf;
	 int result;


	 /* Hent filopplysninger */
    result = _stat(pszPath,&buf);
	 if (result == 0) {
		  *plSize = (long)buf.st_size;
	 }

	 return (short)result;
#endif

#ifdef BORLAND
	 struct stat buf;
	 int result;


	 /* Hent filopplysninger */
	 result = stat(pszPath,&buf);
	 if (result == 0) {
		  *plSize = (long)buf.st_size;
	 }

	 return (short)result;
#endif

}



/*
AR-921013
CH UT_InqPathSize_i64                              Finn filstørrelse
CD ==================================================================
CD Formål:
CD Henter filstørrelsen for gitt fil.
CD
CD PARAMETERLISTE:
CD Type      Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char     *pszPath   i   Filnavn
CD UT_INT64 *n64Size   u   Filstørrelse
CD short     sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_InqPathSize_i64(szPath,&n64Size);
   ==================================================================
*/
SK_EntPnt_UT short UT_InqPathSize_i64(const char *pszPath,UT_INT64 *n64Size)
{
#ifdef LINUX
	struct stat buf;
#else
    struct _stat32i64 buf;
#endif
	 int result;


	 // Hent filopplysninger
    //result = _stat(pszPath,&buf);
#ifdef LINUX
    result = stat(pszPath,&buf);
#else
    result = _stat32i64(pszPath,&buf);
#endif
	 if (result == 0) {
		  *n64Size = buf.st_size;
	 }

	 return (short)result;
}
