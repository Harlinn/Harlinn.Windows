/* ------------------------------
 * Fil: DelDir.c
 * ------------------------------ */

#include "fyba.h"

#ifdef LINUX
#  include <unistd.h>
#endif

#ifdef UNIX
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

#ifdef OS232
#  define INCL_DOSFILEMGR
#  define INCL_DOSERRORS
#  include <os2.h>
#endif

#ifdef OS216
#  include <direct.h>
#endif

#ifdef WIN32
#  include <direct.h>
#endif

#ifdef BORLAND
#  include <dir.h>
#endif

//#include "StdAfx.h"
#include "fyut.h"

/*
AR-921013
CH UT_DeleteDir                                 Sletter et directory
CD ==================================================================
CD Formål:
CD Sletter et directory.
CD
CD PARAMETERLISTE:
CD Type      Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char     *pszPath   i   Directory-navn
CD short     sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_DeleteDir(szPath);
   ==================================================================
*/
SK_EntPnt_UT short UT_DeleteDir(const char *pszPath)
{
#ifdef LINUX
	return  (short)rmdir(pszPath);
#endif

#ifdef UNIX
	return  (short)rmdir(pszPath);
#endif

#ifdef OS232
   return  (short)DosDeleteDir(pszPath);
#endif

#ifdef OS216
   return  (short)rmdir(pszPath);
#endif

#ifdef WIN32
   return  (short)_rmdir(pszPath);
#endif

#ifdef BORLAND
	return  (short)rmdir(pszPath);
#endif
}
