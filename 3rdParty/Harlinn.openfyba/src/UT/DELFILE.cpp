/* ------------------------------ 
 * Fil: DelFile.c
 * ------------------------------ */

#include "fyba.h"

#ifdef LINUX
#  include <unistd.h>
#  define UT_access access
#else
#  include <io.h>
#  define UT_access _access
#endif

#include "fyut.h"

/*
AR-921013
CH  UT_DeleteFile                                      Sletter en fil
CD  ==================================================================
CD  Formål:
CD  Sletter en fil.
CD
CD  PARAMETERLISTE:
CD  Type      Navn     I/U  Merknad
CD  ------------------------------------------------------------------
CD  char     *pszPath   i   Filnavn
CD  short     sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD  Bruk:  sStatus = UT_DeleteFile(szPath);
    ==================================================================
*/

SK_EntPnt_UT short UT_DeleteFile(const char *pszPath)
{
   // Sjekk at filen finnes
   if( (UT_access( pszPath, 0 )) == 0 ) {
      /* Sletter eventuell gammel hjelpefil */
      return remove(pszPath); 
   }
   
   return  0;
}
