/* ------------------------------ 
 * Fil: FilnaCmp.c
 * ------------------------------ */

#include "fyba.h"
#include <string.h>
#include "fyut.h"

#ifdef BORLAND
#  include <windows.h>
#endif

#ifdef WIN32
#  include <windows.h>
#endif

/*
AR-921013
CH UT_FilnavnCmp                                   Sammenlignfilnavn
CD ==================================================================
CD Formål:
CD Sammenligner om 2 filnavn er like.
CD Tar hensyn til om filsystemet handterer store og små bokstaver likt.
CD
CD PARAMETERLISTE:
CD Type      Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char     *pszFil1   i   Filnavn 1
CD char     *pszFil2   i   Filnavn 2
CD short     sStatus   r   Status; 0=Navnene er like, annen verdi = ulik
CD
CD Bruk:  sStatus = UT_FilnavnCmp(pszFil1,pszFil2);
   ==================================================================
*/
SK_EntPnt_UT short UT_FilnavnCmp(const char *pszFil1, const char *pszFil2)
{
   char fil1[_MAX_PATH];
   char fil2[_MAX_PATH];

#ifdef LINUX
   strncpy(fil1,pszFil1,strlen(pszFil1));
   strncpy(fil2,pszFil2,strlen(pszFil2));
#else
   strcpy_s(fil1,pszFil1);
   strcpy_s(fil2,pszFil2);
#endif

#ifndef UNIX
   UT_StrUpper(fil1);
   UT_StrUpper(fil2);
#endif

   return  (short)strcmp(fil1,fil2);
}
