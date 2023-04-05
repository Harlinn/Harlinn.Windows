/* === 920413 ============================================================= */
/*  STATENS KARTVERK  -  FYSAK-PC                                           */
/*  Fil: fyld.c                                                             */
/*  Innhold: Lagring og henting av indekstabeller                           */
/* ======================================================================== */

#include "fyba.h"
#include "fybax.h"

#include <stdlib.h>

#include <Windows.h>



/* Globale strukturer for fyba */
extern LC_SYSTEMADM    Sys;



/*
AR:2004-05-04
CH LC_DelIdx                                            Sletter indeksfilene
CD ==========================================================================
CD Formål:
CD Sletter indeksfilene for gitt SOSI-fil.
CD
CD Parametre:
CD Type  Navn     I/U Forklaring
CD --------------------------------------------------------------------------
CD char *szSosFil  i  SOSI-filnavn
CD
CD Bruk:
CD LC_DelIdx(szSosFil);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_DelIdx(char *szSosFil)
{
   char fil[_MAX_PATH],sdir[_MAX_PATH];
   char drive1[_MAX_DRIVE],dir1[_MAX_DIR],fname1[_MAX_FNAME],ext1[_MAX_EXT];
   char drive2[_MAX_DRIVE],dir2[_MAX_DIR],fname2[_MAX_FNAME],ext2[_MAX_EXT];


   // Bygg opp fullstendig filnavn
   UT_FullPath(fil,szSosFil,_MAX_PATH);

   // Splitt filnavnet
   UT_splitpath(fil,drive1,dir1,fname1,ext1);

   // Lag subdirectory navn
   if ( *Sys.szIdxPath != 0) {
      // Gitt sti for indeksfilene
      UT_splitpath(Sys.szIdxPath,drive2,dir2,fname2,ext2);
      UT_makepath(sdir,drive2,dir2,fname1,"");
   } else {
      // Ikke gitt sti.
      UT_makepath(sdir,drive1,dir1,fname1,"");
   }

   /* Lag sti til filer på sub-directory */
   UT_splitpath(sdir,drive2,dir2,fname2,ext2);
   UT_StrCat(dir2,fname1,_MAX_DIR);
   UT_StrCat(dir2,UT_STR_SLASH,_MAX_DIR);

   //
   // Fjern indeks filene
   //

   // Administrasjonstabeller
   UT_makepath(fil,drive2,dir2,"Adm",".Idx");
   UT_DeleteFile(fil);
   UT_makepath(fil,drive2,dir2,"admin",".idx");       /* FYBA - C */
   UT_DeleteFile(fil);

   // Ringbuffer
   UT_makepath(fil,drive2,dir2,"Rb",".Idx"); 
   UT_DeleteFile(fil);
   
   // Inf
   UT_makepath(fil,drive2,dir2,"Inf",".Idx");         /* FYBA - D */
   UT_DeleteFile(fil);
   UT_makepath(fil,drive2,dir2,"info",".idx");        /* FYBA - C */
   UT_DeleteFile(fil);
   
   // Gruppetabell
   UT_makepath(fil,drive2,dir2,"Grt",".Idx");
   UT_DeleteFile(fil);
   UT_makepath(fil,drive2,dir2,"grtab",".idx");       /* FYBA - C */
   UT_DeleteFile(fil);
   
   // Serienummer-tabell */
   UT_makepath(fil,drive2,dir2,"Snr",".Idx");
   UT_DeleteFile(fil);
   
   // Brukt-tabell
   UT_makepath(fil,drive2,dir2,"Bt",".Idx");
   UT_DeleteFile(fil);
   UT_makepath(fil,drive2,dir2,"btab",".idx");        /* FYBA - C */
   UT_DeleteFile(fil);

   // Geografisk søketabell
   UT_makepath(fil,drive2,dir2,"Geo",".Idx");
   UT_DeleteFile(fil);

   // Flate geografisk søketabell
   UT_makepath(fil,drive2,dir2,"flate",".idx");       /* FYBA - C */
   UT_DeleteFile(fil);

   //
   // Fjern subdirectory
   //
   UT_DeleteDir(sdir);
}
