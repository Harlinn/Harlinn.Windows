/* ------------------------------ 
 * Fil: InqTid.c
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
#    include<sys/mount.h>
#  else
#    include<sys/vfs.h>
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
#  include<windows.h>
#  include<sys/types.h>
#  include<sys/stat.h>
#  include<time.h>
#endif

#ifdef BORLAND
#  include<sys/stat.h>
#  include<time.h>
#endif

#ifdef LINUX
#   include <time.h>
#endif



/*
AR-921013
CH UT_InqPathTid                                Finn oppdateringstid
CD ==================================================================
CD Formål:
CD Henter oppdateringstidspunktet for gitt fil.
CD
CD PARAMETERLISTE:
CD Type      Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char     *pszPath   i   Filnavn
CD PFTID     pFilTid   u   Oppdateringstid
CD short     sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_InqPathTid(szPath,&FilTid);
   ==================================================================
*/
SK_EntPnt_UT short UT_InqPathTid(const char *pszPath,PFTID pFilTid)
{
#ifdef LINUX
    struct stat buf; 
    struct tm *ntime;
    int sStatus;
    time_t temp;

    /* Hent filopplysninger */
    sStatus = stat(pszPath,&buf);
  
    temp = buf.st_mtime;
     
    ntime = localtime(&temp);
   
    if (sStatus == 0) {
        pFilTid->usAar  = (unsigned short)ntime->tm_year;
        pFilTid->usMnd  = (unsigned short)ntime->tm_mon; 
        pFilTid->usDag  = (unsigned short)ntime->tm_mday;
        pFilTid->usTime = (unsigned short)ntime->tm_hour;
        pFilTid->usMin  = (unsigned short)ntime->tm_min;
        pFilTid->usSek  = (unsigned short)ntime->tm_sec;
    }

    return (short)sStatus;
#else
#ifdef UNIX
    struct stat buf; 
    struct tm ntime;
    int sStatus;
    time_t temp;

    /* Hent filopplysninger */
    sStatus = stat(pszPath,&buf);
  
    temp = buf.st_mtime;
     
    localtime(&ntime,&temp);
   
    if (sStatus == 0) {
        pFilTid->usAar  = (unsigned short)ntime.tm_year;
        pFilTid->usMnd  = (unsigned short)ntime.tm_mon; 
        pFilTid->usDag  = (unsigned short)ntime.tm_mday;
        pFilTid->usTime = (unsigned short)ntime.tm_hour;
        pFilTid->usMin  = (unsigned short)ntime.tm_min;
        pFilTid->usSek  = (unsigned short)ntime.tm_sec;
    }

    return (short)sStatus;
#endif
#endif /*not LINUX*/

#ifdef OS232
   APIRET rc;
   FILESTATUS3 PathInfoBuf;

   /* Hent filopplysninger */
   rc = DosQueryPathInfo(pszPath,FIL_STANDARD,&PathInfoBuf,sizeof(FILESTATUS3));

   if (rc == NO_ERROR) {
      pFilTid->usAar  = PathInfoBuf.fdateLastWrite.year;
      pFilTid->usMnd  = PathInfoBuf.fdateLastWrite.month;
      pFilTid->usDag  = PathInfoBuf.fdateLastWrite.day;
      pFilTid->usTime = PathInfoBuf.ftimeLastWrite.hours;
      pFilTid->usMin  = PathInfoBuf.ftimeLastWrite.minutes;
      pFilTid->usSek  = PathInfoBuf.ftimeLastWrite.twosecs;
   }

   return (short)rc;
#endif

#ifdef OS216
   int rc;
   FILESTATUS2 PathInfoBuf;

   /* Hent filopplysninger */
   rc = DosQPathInfo(pszPath,FIL_STANDARD,(PBYTE)&PathInfoBuf,sizeof(FILESTATUS2),0);

   if (rc == NO_ERROR) {
      pFilTid->usAar  = PathInfoBuf.fdateLastWrite.year;
      pFilTid->usMnd  = PathInfoBuf.fdateLastWrite.month;
      pFilTid->usDag  = PathInfoBuf.fdateLastWrite.day;
      pFilTid->usTime = PathInfoBuf.ftimeLastWrite.hours;
      pFilTid->usMin  = PathInfoBuf.ftimeLastWrite.minutes;
      pFilTid->usSek  = PathInfoBuf.ftimeLastWrite.twosecs;
   }

   return (short)rc;
#endif
 

#ifdef WIN32
    struct _stat32i64 buf;
	 struct tm ntime;
	 int sStatus;
	 time_t temp;

	 /* Hent filopplysninger */
	 sStatus = _stat32i64(pszPath,&buf);

    /* Endringstidspunktet */
	 temp = buf.st_mtime;                 
    /* Hvis filen ikke er endret brukes opprettelsestidspunktet */
    if (temp == -1)  temp = buf.st_ctime;

	 localtime_s(&ntime,&temp);

	 if (sStatus == 0) {
        pFilTid->usAar  = (unsigned short)ntime.tm_year;
		  pFilTid->usMnd  = (unsigned short)ntime.tm_mon;
		  pFilTid->usDag  = (unsigned short)ntime.tm_mday;
		  pFilTid->usTime = (unsigned short)ntime.tm_hour;
		  pFilTid->usMin  = (unsigned short)ntime.tm_min;
		  pFilTid->usSek  = (unsigned short)ntime.tm_sec;
	 }

	 return (short)sStatus;
#endif

#ifdef BORLAND
	 struct stat buf;
	 struct tm ntime;
	 int sStatus;
	 time_t temp;

	 /* Hent filopplysninger */
	 sStatus = stat(pszPath,&buf);

	 temp = buf.st_mtime;

	 localtime(&ntime,&temp);

	 if (sStatus == 0) {
        pFilTid->usAar  = (unsigned short)ntime.tm_year;
		  pFilTid->usMnd  = (unsigned short)ntime.tm_mon;
		  pFilTid->usDag  = (unsigned short)ntime.tm_mday;
		  pFilTid->usTime = (unsigned short)ntime.tm_hour;
		  pFilTid->usMin  = (unsigned short)ntime.tm_min;
		  pFilTid->usSek  = (unsigned short)ntime.tm_sec;
	 }

	 return (short)sStatus;
#endif

}
