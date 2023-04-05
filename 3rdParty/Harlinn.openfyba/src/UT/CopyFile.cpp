/* ------------------------------
 * Fil: CopyFile.c
 * ------------------------------ */

#include "fyba.h"

#ifdef UNIX
#  ifndef _INCLUDE_POSIX_SOURCE
#    define _INCLUDE_POSIX_SOURCE
#  endif
#  ifndef _HPUX_SOURCE
#    define _HPUX_SOURCE
#  endif
#endif

#ifdef OS2
#endif

#ifdef WIN32
#  include<windows.h>
#endif

#ifdef BORLAND
#endif

//#include "StdAfx.h"
#include "fyut.h"

/*
AR-971118
CH UT_CopyFile                                            Kopier fil
CD ==================================================================
CD Formål:
CD Kopierer en eksisterende fil til en ny fil.
CD
CD PARAMETERLISTE:
CD Type   Navn               I/U Merknad
CD ------------------------------------------------------------------
CD char  *pszFraFilnavn       i  Kopier fra denne filen
CD char  *pszTilFilnavn       i  Kopier til denne filen
CD short  sFeilHvisEksisterer i  Hva skal skje hvis resultatfilen finnes fra før:
CD                                  UT_TRUE = Avbryter
CD                                  UT_FALSE = Overskriver  
CD short  sStatus             r  Status:
CD                                  UT_TRUE = OK
CD                                  UT_FALSE = Feil.
CD
CD Bruk:  sStatus = UT_CopyFile(pszFraFilnavn,pszTilFilnavn,UT_TRUE);
   ==================================================================
*/
SK_EntPnt_UT short UT_CopyFile(const char *pszFraFilnavn,const char *pszTilFilnavn,short sFeilHvisEksisterer)
{
#ifdef WIN32
   if (CopyFile( pszFraFilnavn, pszTilFilnavn, sFeilHvisEksisterer)) {
      return UT_TRUE;
   } else {
      return UT_FALSE;
   }
#endif


#ifdef UNIX
      return UT_FALSE;
#endif

#ifdef OS232
      return UT_FALSE;
#endif

#ifdef OS216
      return UT_FALSE;
#endif

#ifdef BORLAND
      return UT_FALSE;
#endif

}
