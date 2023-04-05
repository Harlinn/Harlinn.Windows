/* === 910828 ============================================================= */
/*  STATENS KARTVERK  -  FYSAK-PC                                           */
/*  Fil: fyli.c                                                             */
/*  Innhold: Lagring og henting av indekstabeller                           */
/* ======================================================================== */

#include "fyba.h"
#include "fybax.h"

#include <limits.h>

#ifdef WIN32
#   include <process.h>
#include <Windows.h>
#endif

/* Div. styrevariabler */

/* Konstanter for ModusXxx */
#define NY    0
#define LES   1
#define SKRIV 2


/* Globale strukturer for fyba */
extern LC_SYSTEMADM    Sys;


/* Lokale rutiner */
static FILE *LI_OpenIdxFil(LC_FILADM *pFil, const char *pszNavn, const char *pszType);
static FILE *LI_OpenAdm(LC_FILADM *pFil);
static FILE *LI_OpenGrt(LC_FILADM *pFil);
static FILE *LI_OpenGeo(LC_FILADM *pFil);
static FILE *LI_OpenSnr(LC_FILADM *pFil);
static FILE *LI_OpenBt(LC_FILADM *pFil);
static void  LI_OpenRb(LC_FILADM *pFil,UT_INT64 n64FilPos,short sModus);
static short LI_ReadAdm(LC_FILADM *pFil);
static void  LI_CreateIdx(LC_FILADM *pFil);
static void  LI_FrigiIdx(LC_FILADM *pFil);


/*
AR-910928
CH LI_TestIdx                               Sjekk at indeksfilene eksisterer
CD ==========================================================================
CD Formål:
CD Sjekk at indeksfilene eksisterer.
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD char   *szSosFil   i    SOSI-fil
CD short   status     r    Status
CD                          UT_TRUE = OK
CD                          UT_FALSE = Fil mangler
CD
CD Bruk:
CD status = LI_TestIdx(szSosFil);
   ==========================================================================
*/
short LI_TestIdx(char *szSosFil)
{
   UT_INT64 Size;
   char fil[_MAX_PATH];
   char drive[_MAX_DRIVE],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];


   // Hvis det er valgt spesiell indekskatalog skal indeksen alltid bygges opp på nytt
   if (*Sys.szIdxPath != '\0')  return UT_FALSE;

   /*
    *  Lag sti til indeksfilene
    */
   UT_splitpath(szSosFil,drive,dir,fname,ext);
   /* Lag navn på sub-directory */
   UT_StrCat(dir,fname,_MAX_DIR);
   UT_StrCat(dir,UT_STR_SLASH,_MAX_DIR);

   /* Sjekk at indeksfilene finnes */
   /* -------------- Adm ------------- */
   UT_makepath(fil,drive,dir,"Adm",".Idx");
   if (UT_InqPathSize_i64(fil,&Size) != 0)  return UT_FALSE;

   /* -------------- Gruppetabell ------------- */
   UT_makepath(fil,drive,dir,"Grt",".Idx");
   if (UT_InqPathSize_i64(fil,&Size) != 0)  return UT_FALSE;

   /* -------------- RB ------------- */
   UT_makepath(fil,drive,dir,"Rb",".Idx");
   if (UT_InqPathSize_i64(fil,&Size) != 0)  return UT_FALSE;

   /* -------------- SNR ------------- */
   UT_makepath(fil,drive,dir,"Snr",".Idx");
   if (UT_InqPathSize_i64(fil,&Size) != 0)  return UT_FALSE;
   
   /* -------------- BT -------------- */
   UT_makepath(fil,drive,dir,"Bt",".Idx");
   if (UT_InqPathSize_i64(fil,&Size) != 0)  return UT_FALSE;
   
   /* -------------- GEO ------------- */
   UT_makepath(fil,drive,dir,"Geo",".Idx");
   if (UT_InqPathSize_i64(fil,&Size) != 0)  return UT_FALSE;

   /* printf("\nIndeksfilene finnes."); */
   return UT_TRUE;
}


/*
AR-910929
CH LI_OpenInit                              Åpner og nullstiller indeksfilene
CD ==========================================================================
CD Formål:
CD Åpner indeksfilene og nullstiller tabellene.
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD short      status r    Status
CD                          UT_TRUE = OK
CD                          UT_FALSE = Ikke åpnet OK
CD
CD Bruk:
CD status = LI_OpenInit(pFil);
   ==========================================================================
*/
short LI_OpenInit(LC_FILADM *pFil)
{
   char fil[_MAX_PATH];
   char drive1[_MAX_DRIVE],dir1[_MAX_DIR],fname1[_MAX_FNAME],ext1[_MAX_EXT];
   char drive2[_MAX_DRIVE],dir2[_MAX_DIR],fname2[_MAX_FNAME],ext2[_MAX_EXT];
   FILE *pF;


   // ----- Alloker overordnet struktur for indekstabeller
   LI_CreateIdx(pFil);

   // ----- Splitt filnavnet
   UT_splitpath(pFil->pszNavn,drive1,dir1,fname1,ext1);

   // Gitt sti for indeksfilene
   if ( *Sys.szIdxPath != 0) {
      UT_splitpath(Sys.szIdxPath,drive2,dir2,fname2,ext2);
      UT_makepath(fil,drive2,dir2,fname1,"");

   } else {
      UT_makepath(fil,drive1,dir1,fname1,"");
   }

   // ----- Lag subdirectory hvis det ikke finnes fra før
   // Sjekk at navnet er lovlig (ikke blanke siste i navnet)
   if (fil[strlen(fil)-1] == ' ')
   {
      LC_Error(120,"(LI_OpenInit)",pFil->pszNavn);
      exit(99);
   }

   // Opprett katalogen
   UT_CreateDir(fil);


   // ----- Åpner indeksfilene

   /* -------------- Adm ------------- */
   pF = LI_OpenAdm(pFil);

   /* Marker at basen er åpnet */       
   UT_StrCopy(pFil->szBaseVer, FYBA_IDENT, LC_BASEVER_LEN);
   UT_StrCopy(pFil->szIdxVer, FYBA_INDEKS_VERSJON, 5);
   pFil->ulPid = 0;
   pFil->sIdxOpen = UT_TRUE;
   pFil->ulPid = UT_GETPID();
   //pFil->ulPid = GetCurrentProcessId();   // Bruke _getpid() i stede?

   if (fwrite(pFil,sizeof(*pFil),1,pF) != 1) {
      LC_Error(112,"(LI_OpenInit)","");
      exit(99);
   }

   fclose(pF);

   /* -------------- Gruppetabell ------------- */
   pF = LI_OpenGrt(pFil);
   fclose(pF);

   /* -------------- RB ------------- */
   LI_OpenRb(pFil,0L,SKRIV);
   pFil->pBase->n64FilPosRb = 0L;

   /* -------------- SNR ------------- */
   pF = LI_OpenSnr(pFil);
   fclose(pF);

   /* -------------- BT -------------- */
   pF = LI_OpenBt(pFil);
   fclose(pF);

   /* -------------- GEO ------------- */
   /* (Geografisk søk er uaktuellt ved kladdebase)  ?????? */
   pF = LI_OpenGeo(pFil);
   fclose(pF);

   return UT_TRUE;
}


/*
AR-910930
CH LI_OpenRead                                   Åpner og leser indeksfilene
CD ==========================================================================
CD Formål:
CD Åpner indeksfilene og leser inn tabellene.
CD
CD Parametre:
CD Type       Navn  I/U Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i  Peker til FilAdm
CD short      status r  Status
CD                         UT_OK (0): Lest OK
CD                         LI_LESEFEIL: Feil ved les fra Adm.idx
CD                         LI_OPPTATT: Filen er åpen i et annet program
CD                         LI_FEIL_INDEKSVERSJON: Feil indeksversjon
CD                         LI_FEIL_STORRELSE: Feil størrelse på SOSI-filen
CD                         LI_FEIL_OPPDATTID: Feil oppdateringstid på SOSI-filen
CD
CD Bruk:
CD status = LI_OpenRead(pFil);
   ==========================================================================
*/
short LI_OpenRead(LC_FILADM *pFil)
{
   FILE *pF;
   long linje;
   long lSnr;
   long lGrNr;
   unsigned long bt;
   LC_GRTAB_LINJE * pGrt;
   LC_BOKS Boks;
   short sStatus;


   /* -------------- Admin ------------- */
   // Her sjekkes det også mot feil versjon, lesefeil
   // og om filen er åpen i annet program.
   if ((sStatus = LI_ReadAdm(pFil)) != UT_OK)
   {
      return sStatus;
   }

   // Alloker overordnet struktur for indekstabeller
   LI_CreateIdx(pFil);

   /* -------------- RB ------------- */
   LI_OpenRb(pFil,0L,SKRIV);
   pFil->pBase->n64FilPosRb = 0L;

   /* -------------- Gruppetabell ------------- */
   pF = LI_OpenGrt(pFil);
   for (linje = 0; linje<pFil->lAntGr; linje++) {
      pGrt = LI_AppGrt(pFil,linje);
      if (fread(pGrt,sizeof(*pGrt),1,pF) != 1) { /* Les */
         UT_SNPRINTF(err().tx,LC_ERR_LEN," %s : %ld",pFil->pszNavn,linje);
         LC_Error(111,"(LI_OpenRead): ",err().tx);
         exit(99);
      }
   }
   fclose(pF);
   
   /* -------------- SNR ------------- */
   pF = LI_OpenSnr(pFil);
   lSnr = 0;
   while (fread(&lGrNr,sizeof(lGrNr),1,pF) == 1) {
      if (lGrNr != INGEN_GRUPPE)  LI_PutSnr(pFil,lSnr,lGrNr);
      lSnr++;
   }
   if (! feof(pF)) {
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %ld",lSnr);
      LC_Error(111,"(LI_OpenRead): ",err().tx);
      exit(99);
   }
   fclose(pF);


   /* -------------- BT -------------- */
   pF = LI_OpenBt(pFil);
   for (linje = 0; linje<pFil->lAntGr; linje++) {
      if (fread(&bt,sizeof(bt),1,pF) != 1) {   /* Les */
         UT_SNPRINTF(err().tx,LC_ERR_LEN," %s : %ld",pFil->pszNavn,linje);
         LC_Error(111,"(LI_OpenRead): ",err().tx);
         exit(99);
      }
      LI_PutBt(pFil,linje,bt);
   }
   fclose(pF);

   /* -------------- GEO ------------- */
   pF = LI_OpenGeo(pFil);
   for (linje = 0; linje<pFil->lAntGr; linje++) {
      if (fread(&Boks,sizeof(Boks),1,pF) != 1) { /* Les */
         UT_SNPRINTF(err().tx,LC_ERR_LEN," %s : %ld",pFil->pszNavn,linje);
         LC_Error(111,"(LI_OpenRead): ",err().tx);
         exit(99);
      }

      if (Boks.dMaxAust != (double)LONG_MAX) {
         /* Lagre omskrevet boks i søketreet */
         pGrt = LI_GetGrt(pFil,linje);
         pGrt->pRL = LR_InsertGeo(pFil,linje,&Boks);
      }
   }
   fclose(pF);

   return UT_OK;
}


/*
AR-930809
CH LI_CreateIdx                               Allokerer Idx struktur i minne
CD ==========================================================================
CD Formål:
CD Allokerer Idx struktur i minne
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD LI_CreateIdx(pFil);
   ==========================================================================
*/
static void LI_CreateIdx(LC_FILADM *pFil)
{
	pFil->pIdx = (LC_IDX_TABELL *) UT_MALLOC(sizeof(LC_IDX_TABELL));
	memset(pFil->pIdx,'\0',sizeof(LC_IDX_TABELL));
}


/*
AR-930809
CH LI_FrigiIdx                                   Frigi Idx struktur i minne
CD ==========================================================================
CD Formål:
CD Frigi Idx struktur i minne
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD LI_FrigiIdx(pFil);
   ==========================================================================
*/
static void LI_FrigiIdx(LC_FILADM *pFil)
{
   int i;
   LC_GRTAB_LINJE * *ppGt = pFil->pIdx->GtAdm;
   long **pplSnr;
   unsigned long **ppulBt;


   if (pFil->pIdx != NULL) {
      ppGt = pFil->pIdx->GtAdm;
      pplSnr = pFil->pIdx->SnrAdm;
      ppulBt = pFil->pIdx->BtAdm;

      for (i=0; i<LC_ANT_IDX_BLOKK; i++) {
         /* Gruppetabellen */
			if (*ppGt != NULL) {
				UT_FREE(*ppGt);
			}
         ppGt++;

         /* SNR-tabellen */
			if (*pplSnr != NULL) {
				UT_FREE(*pplSnr);
         }
         pplSnr++;

         /* Brukt-tabellen */
			if (*ppulBt != NULL) {
				UT_FREE(*ppulBt);
         }
         ppulBt++;

      }

      /* Frigi GEO-tabellen */
      if (pFil->pGeoRN != NULL) {
         LR_R_FrigiGren(pFil->pGeoRN);
      }
		
      /* Frigir topp-blokken */
		UT_FREE(pFil->pIdx);

		pFil->pIdx = NULL;
	}
}


/*
AR-910830
CH LI_Close                                             Stenger indeksfilene
CD ==========================================================================
CD Formål:
CD Skriver adm. opplysning og stenger indeksfilene.
CD
CD Parametre:
CD Type       Navn  I/U Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i  Peker til FilAdm
CD short      s_stat i  Slutt-status (brukes foreløpig ikke)
CD                         (RESET_IDX) = Fjern indeksfilene
CD                         (SAVE_IDX ) = Lagrer indeksfilene
CD
CD Bruk:
CD LI_Close(pFil,SAVE_IDX);
   ==========================================================================
*/
void LI_Close(LC_FILADM *pFil,short s_stat)
{
   long lGrNr,lSnr;
   unsigned long flag;
   FILE *pF;
   LC_R_LEAF * pRL;
   LC_BOKS Boks;


   /* RB */
   if (pFil->pBase->pCurRb != NULL) {
      fclose(pFil->pBase->pfRb);
      pFil->pBase->pCurRb = NULL;
   }

   if (s_stat == SAVE_IDX  &&  pFil->pIdx != NULL  &&  *Sys.szIdxPath == '\0') {

      /* Gruppetabellen */
      pF = LI_OpenGrt(pFil);     /* Åpne og posisjoner */
      for (lGrNr=0; lGrNr<pFil->lAntGr; lGrNr++) {
			if (fwrite(LI_GetGrt(pFil,lGrNr),sizeof (LC_GRTAB_LINJE),1,pF) != 1) {
            LC_Error(112,"(LI_Close)","");
            exit(99);
         }
      }
      fclose(pF);

      /* Brukttabellen */
      pF = LI_OpenBt(pFil);     /* Åpne og posisjoner */
      for (lGrNr=0; lGrNr<pFil->lAntGr; lGrNr++) {
         flag = LI_GetBt(pFil,lGrNr);
         if (fwrite(&flag,sizeof flag,1,pF) != 1) {
				LC_Error(112,"(LI_Close)","");
            exit(99);
         }
      }
      fclose(pF);

      /*Serienummertabellen */
      pF = LI_OpenSnr(pFil);     /* Åpne og posisjoner */
      for (lSnr=0; lSnr<=pFil->lMaxSnr; lSnr++) {
         lGrNr = LI_GetSnr(pFil,lSnr);
         if (fwrite(&lGrNr,sizeof lGrNr,1,pF) != 1) {
            LC_Error(112,"(LI_Close)","");
				exit(99);
         }
      }
      fclose(pF);

      /* Geografisk søketabell */
      pF = LI_OpenGeo(pFil);     /* Åpne og posisjoner */
      for (lGrNr=0; lGrNr<pFil->lAntGr; lGrNr++) {
         pRL = LI_GetGeo(pFil,lGrNr);

         if (pRL == NULL) {
            Boks.dMaxAust = (double)LONG_MAX;
            if (fwrite(&Boks,sizeof (LC_BOKS),1,pF) != 1) {
               LC_Error(112,"(LI_Close)","");
               exit(99);
            }

         } else {
            if (fwrite(&(pRL->Boks),sizeof (LC_BOKS),1,pF) != 1) {
               LC_Error(112,"(LI_Close)","");
               exit(99);
            }
         }
		}
      fclose(pF);

      /* Lagre adm. blokken */
      LI_SaveAdm(pFil);

   } else {
      /* Fjern indeks filene */
      LC_DelIdx(pFil->pszNavn);
   }

   /*
	 *  Frigi overordnet struktur for indekstabeller
    */
   LI_FrigiIdx(pFil);

}


/*
AR-910929
CH LI_OpenIdxFil                                              Åpne indeksfil
CD ==========================================================================
CD Formål:
CD Åpner indeksfil på rett katalog
CD
CD Parametre:
CD Type        Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM  *pFil     i    Peker til FilAdm
CD const char *pszNavn  i    Filnavn
CD const char *pszType  i    Filtype
CD
CD Bruk:
CD pF = LI_OpenIdxFil(pFil,"Adm",".Idx");
   ==========================================================================
*/
static FILE *LI_OpenIdxFil(LC_FILADM *pFil, const char *pszNavn, const char *pszType)
{
   short ierr;
   char fil[_MAX_PATH];
   char drive1[_MAX_DRIVE],dir1[_MAX_DIR],fname1[_MAX_FNAME],ext1[_MAX_EXT];
   char drive2[_MAX_DRIVE],dir2[_MAX_DIR],fname2[_MAX_FNAME],ext2[_MAX_EXT];

   FILE *pF;

   // ----- Bygg opp fullt filnavn til filen
   //  Splitt SOSI-filnavnet
   UT_splitpath(pFil->pszNavn,drive1,dir1,fname1,ext1);

   // Gitt sti for indeksfilene
   if ( *Sys.szIdxPath != 0) {
      UT_splitpath(Sys.szIdxPath,drive2,dir2,fname2,ext2);
      UT_StrCat(dir2,fname1,_MAX_DIR);
      UT_StrCat(dir2,UT_STR_SLASH,_MAX_DIR);
      // Bygg opp filnavn
      UT_makepath(fil,drive2,dir2,pszNavn,pszType);

   } else {
      UT_StrCat(dir1,fname1,_MAX_DIR);
      UT_StrCat(dir1,UT_STR_SLASH,_MAX_DIR);
      // Bygg opp filnavn
      UT_makepath(fil,drive1,dir1,pszNavn,pszType);
   }

	// Åner filen
   pF = UT_OpenFile(fil,"",UT_UPDATE,UT_UNKNOWN,&ierr);
   if (ierr != UT_OK){
      char szError[256];
      UT_strerror(szError,256,ierr);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",fil,szError);
      LC_Error(6,"(LI_OpenIdxFil)",err().tx);
      exit(2);
   }

   /* Posisjoner hvis nødvendig */
   //fseek(pF,0L,SEEK_SET);   // OBS!  Er denne nødvendig? AR:2004-05-14  Fjernet

   return pF;
}


/*
AR-910929
CH LI_OpenAdm                                     Åpne og posisjoner, Adm
CD ==========================================================================
CD Formål:
CD Sjekker at rett Adm-fil er åpen, og posisjoner
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD pF = LI_OpenAdm(pFil);
   ==========================================================================
*/
static FILE *LI_OpenAdm(LC_FILADM *pFil)
{
   FILE *fi = LI_OpenIdxFil(pFil,"Adm",".Idx");
   fseek(fi,0L,SEEK_SET);

   return fi;
}


/*
AR-910929
CH LI_OpenGrt                                     Åpne og posisjoner, Grt
CD ==========================================================================
CD Formål:
CD Sjekker at rett Grt-fil er åpen, og posisjoner
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD pF = LI_OpenGrt(pFil);
   ==========================================================================
*/
static FILE *LI_OpenGrt(LC_FILADM *pFil)
{
   FILE *fi = LI_OpenIdxFil(pFil,"Grt",".Idx");
   fseek(fi,0L,SEEK_SET);

   return fi;
}


/*
AR-910929
CH LI_OpenGeo                                     Åpne og posisjoner, Geo
CD ==========================================================================
CD Formål:
CD Sjekker at rett Geo-fil er åpen, og posisjoner
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD pF = LI_OpenGeo(pFil);
   ==========================================================================
*/
static FILE *LI_OpenGeo(LC_FILADM *pFil)
{
   FILE *fi = LI_OpenIdxFil(pFil,"Geo",".Idx");
   fseek(fi,0L,SEEK_SET);

   return fi;
}


/*
AR-910929
CH LI_OpenSnr                                     Åpne og posisjoner, Snr
CD ==========================================================================
CD Formål:
CD Sjekker at rett Snr-fil er åpen, og posisjoner
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD pF = LI_OpenSnr(pFil);
   ==========================================================================
*/
static FILE *LI_OpenSnr(LC_FILADM *pFil)
{
   FILE *fi = LI_OpenIdxFil(pFil,"Snr",".Idx");
   fseek(fi,0L,SEEK_SET);

   return fi;
}


/*
AR-910929
CH LI_OpenBt                                     Åpne og posisjoner, Bt
CD ==========================================================================
CD Formål:
CD Åpne Bt-fil, og posisjoner
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD pF = LI_OpenBt(pFil);
   ==========================================================================
*/
static FILE *LI_OpenBt(LC_FILADM *pFil)
{
   FILE *fi = LI_OpenIdxFil(pFil,"Bt",".Idx");
   fseek(fi,0L,SEEK_SET);

   return fi;
}


/*
AR-930810
CH LI_GetGeo                                                   Get geo-linje
CD ==========================================================================
CD Formål:
CD Henter en linje fra geografisk søketabell.
CD
CD Parametre:
CD Type          Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM    *pFil   i    Peker til FilAdm
CD long          linje  i    Linjenummer i geo-tabellen (gruppenummer)
CD LC_GEOTABELL *geop   r    Peker til geo-tabell-struktur
CD
CD Bruk:
CD geop = LI_GetGeo(pFil,linje);
   ==========================================================================
*/
LC_R_LEAF * LI_GetGeo(LC_FILADM *pFil,long linje)
{
   LC_GRTAB_LINJE * pGT;

   pGT = LI_GetGrt(pFil,linje);

   return pGT->pRL; /* Peker til element søketreet */
}


/*
AR-930810
CH LI_GetSnr                                                   Get snr-linje
CD ==========================================================================
CD Formål:
CD Henter en linje fra serienummer-tabellen.
CD
CD Parametre:
CD Type             Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM       *pFil   i    Peker til FilAdm
CD long             lSnr   i    Serienummer
CD long             lGrNr  r    Gruppenummer
CD
CD Bruk:
CD lGrNr = LI_GetSnr(pFil,lSnr);
   ==========================================================================
*/
long LI_GetSnr(LC_FILADM *pFil,long lSnr)
{
   long **pplGrNr;

   if (pFil->pIdx != NULL) {
      /* Lovlig serienummer? */
      if (lSnr <= pFil->lMaxSnr) {
         /* Finner starten av aktuell blokk */
			pplGrNr = pFil->pIdx->SnrAdm + (lSnr / LC_IDX_LIN_BLOKK);
         /* Er denne blokken brukt? */
         if (*pplGrNr != NULL) {
            /* Hent aktuell linje i denne blokken */
            return  *(*pplGrNr + (lSnr % LC_IDX_LIN_BLOKK));
         }
      }
   }

   return  INGEN_GRUPPE;
}


/*
AR-930810
CH LI_PutSnr                                                   Put snr-linje
CD ==========================================================================
CD Formål:
CD Legger inn en linje i serienummer-tabellen.
CD
CD Parametre:
CD Type          Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM    *pFil   i    Peker til FilAdm
CD long          lSnr   i    Serienummer
CD long          lGrNr  i    Gruppenummer
CD
CD Bruk:
CD LI_PutSnr(pFil,lSnr,lGrNr);
   ==========================================================================
*/
void LI_PutSnr(LC_FILADM *pFil,long lSnr,long lGrNr)
{
   long **pplGrNr,*pL;
   int antall;

	if (pFil->pBase->sType == LC_BASE) {
      if (pFil->pIdx != NULL) {
         if (lSnr < LC_MAX_GRU) {
            /* Finner starten av aktuell blokk */
            pplGrNr = pFil->pIdx->SnrAdm + (lSnr / LC_IDX_LIN_BLOKK);

            /* Blokken finnes ikke, lag ny blokk */ 
				if (*pplGrNr == NULL)
				{
					*pplGrNr = (long *) UT_MALLOC(sizeof(long)*LC_IDX_LIN_BLOKK);

               for (pL=*pplGrNr,antall=0; antall<LC_IDX_LIN_BLOKK; pL++,antall++) {
						*pL = INGEN_GRUPPE;
					}
				}

            /* Legg inn aktuell linje i blokken */
            *(*pplGrNr + (lSnr % LC_IDX_LIN_BLOKK)) = lGrNr;

         } else {
				UT_SNPRINTF(err().tx,LC_ERR_LEN,"%ld",lSnr);
            LC_Error(61,"(LI_PutSnr): ",err().tx);
            exit(99);
         }

      } else {
         LC_Error(75,"(LI_PutSnr): ","");
         exit(99);
      }
   }
}


/*
AR-930810
CH LI_GetGrt                                                   Get grt-linje
CD ==========================================================================
CD Formål:
CD Henter en linje fra gruppetabellen. 
CD
CD Parametre:
CD Type            Navn  I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM      *pFil   i   Peker til FilAdm
CD long            linje  i   Linjenummer i grt-tabellen (gruppenummer)
CD LC_GRTAB_LINJE *grtp   r   Peker til grt-tabell-linje
CD
CD Bruk:
CD grtp = LI_GetGrt(pFil,linje);
   ==========================================================================
*/
LC_GRTAB_LINJE * LI_GetGrt(LC_FILADM *pFil,long linje)
{
   LC_GRTAB_LINJE * *ppGt;

   if (pFil->pIdx != NULL) {
		/* Finner starten av aktuell blokk */
      ppGt = pFil->pIdx->GtAdm + (linje / LC_IDX_LIN_BLOKK);
      /* Er denne blokken brukt? */
      if (*ppGt != NULL) {
         /* Hent aktuell linje i denne blokken */
         return  (*ppGt + (linje % LC_IDX_LIN_BLOKK));
      }
   }

   UT_SNPRINTF(err().tx,LC_ERR_LEN," %s : %ld",pFil->pszNavn,linje);
   LC_Error(111,"(LI_GetGrt): ",err().tx);
   exit(99);

   return  NULL;
}


/*
AR-930810
CH LI_AppGrt                                                    Ny grt-linje
CD ==========================================================================
CD Formål:
CD Legger inn en NY linje i gruppetabell.
CD
CD Parametre:
CD Type          Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM    *pFil   i    Peker til FilAdm
CD long          linje  i    Linjenummer i grt-tabellen (gruppenummer)
CD LC_GEOTABELL *grtp   r    Peker til grt-tabell-struktur
CD
CD Bruk:
CD pgrt = LI_AppGrt(pFil,linje,geop);
   ==========================================================================
*/
LC_GRTAB_LINJE * LI_AppGrt(LC_FILADM *pFil,long linje)
{
   LC_GRTAB_LINJE * *ppGt;

   if (pFil->pIdx != NULL) {
      /* Finner starten av aktuell blokk */
      ppGt = pFil->pIdx->GtAdm + (linje / LC_IDX_LIN_BLOKK);
      if (*ppGt == NULL) {
			/* Blokken finnes ikke, lag ny blokk */
			*ppGt = (LC_GRTAB_LINJE *)UT_MALLOC(sizeof(LC_GRTAB_LINJE)*LC_IDX_LIN_BLOKK);
			memset(*ppGt,'\0',sizeof(LC_GRTAB_LINJE)*LC_IDX_LIN_BLOKK);
		}

		/* Finn aktuell linje i blokken */
      return  (*ppGt + (linje % LC_IDX_LIN_BLOKK));    /* Funnet ===> */

   } else {
      LC_Error(75,"(LI_PutGrt): ",err().tx);
      exit(99);
   }

   return  NULL;
}


/*
AR-930810
CH LI_GetBt                                                     Get bt-linje
CD ==========================================================================
CD Formål:
CD Henter en linje fra brukt-tabellen.
CD
CD Parametre:
CD Type          Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM    *pFil     i    Peker til FilAdm
CD long          linje    i    Linjenummer i bt-tabellen (gruppenummer)
CD unsigned long bt_val   r    Hentet bit-mønster
CD
CD Bruk:
CD bt_val = LI_GetBt(pFil,linje);
   ==========================================================================
*/
unsigned long LI_GetBt(LC_FILADM *pFil,long linje)
{
   unsigned long **ppulFlag;

   if (pFil->pIdx != NULL) {
      /* Finner starten av aktuell blokk */
      ppulFlag = pFil->pIdx->BtAdm + (linje / LC_IDX_LIN_BLOKK);
      /* Er denne blokken brukt? */
      if (*ppulFlag != NULL) {
         /* Hent aktuell linje i denne blokken */
         return  *(*ppulFlag + (linje % LC_IDX_LIN_BLOKK));
      }
   }

   UT_SNPRINTF(err().tx,LC_ERR_LEN," %s : %ld",pFil->pszNavn,linje);
   LC_Error(111,"(LI_GetBt): ",err().tx);
   exit(99);

   return  0L;
}


/*
AR-930810
CH LI_PutBt                                                     Put bt-linje
CD ==========================================================================
CD Formål:
CD Legger inn en linje i brukt-tabell.
CD
CD Parametre:
CD Type              Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD long              linje     i    Linjenummer i bt-tabellen (gruppenummer)
CD unsigned long     bt_val    i    Bit mønster som skal lagres
CD
CD Bruk:
CD LI_PutBt(pFil,linje,bt_val);
   ==========================================================================
*/
void LI_PutBt(LC_FILADM *pFil,long linje,unsigned long bt_val)
{
   unsigned long **ppulFlag;

   if (pFil->pIdx != NULL) {
      /* Finner starten av aktuell blokk */
      ppulFlag = pFil->pIdx->BtAdm + (linje / LC_IDX_LIN_BLOKK);

      /* Blokken finnes ikke, lag ny blokk */ 
		if (*ppulFlag == NULL)
		{
			*ppulFlag =	(unsigned long *) UT_MALLOC(sizeof(unsigned long)*LC_IDX_LIN_BLOKK);
			memset(*ppulFlag,'\0',sizeof(unsigned long)*LC_IDX_LIN_BLOKK);
		}

      /* Legg inn aktuell linje i blokken */
      *(*ppulFlag + (linje % LC_IDX_LIN_BLOKK)) = bt_val;

   } else {
      LC_Error(75,"(LI_PutBt): ",err().tx);
      exit(99);
   }
}


/*
AR-881123
CH LC_SetBt                                       Sett merke i brukttabellen
CD ==========================================================================
CD Formål:
CD Legg inn merke i brukttabellen.
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR * pGr       i    Gruppenummer
CD short   kolonne   i    Kolonne som skal merkes.
CD                        (Lovlig BT_MIN_USER - BT_MAX_USER)
CD
CD Bruk:
CD LC_SetBt(pGr,kolonne);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_SetBt(LC_BGR * pGr,short kolonne)
{
   /* LO_TestFilpeker(pGr->pFil,"LC_SetBt"); */
   LO_TestFilpeker(pGr->pFil,"SetBt");

                                           /* Lovlig gruppe */
   if (pGr->lNr >= 0L && pGr->lNr < pGr->pFil->lAntGr) {
                                           /* Lovlig kolonne */
       if (kolonne >= BT_MIN_USER  &&  kolonne <= BT_MAX_USER) {
                                           /* Merk */
           LI_SetBt(pGr->pFil,pGr->lNr,kolonne);
       }

   } else{                                 /* Ulovlig gruppe */
      char errtx[50];
      UT_SNPRINTF(errtx,50," %ld",pGr->lNr);
      LC_Error(72,"(LC_SetBt)",errtx);
   }
}


/*
AR-881123
CH LC_ClrBt                                      Slett merke i brukttabellen
CD ==========================================================================
CD Formål:
CD Fjern merke i brukttabellen.
CD
CD Parametre:
CD Navn     Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *  pGr      i    Gruppenummer
CD kolonne  short    i    Kolonne som skal merkes.
CD                        (Lovlig BT_MIN_USER - BT_MAX_USER)
CD
CD Bruk:
CD LC_ClrBt(pGr,kolonne);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_ClrBt(LC_BGR * pGr,short kolonne)
{
   /* LO_TestFilpeker(pGr->pFil,"LC_ClrBt"); */
   LO_TestFilpeker(pGr->pFil,"ClrBt");

                                           /* Lovlig gruppe */
   if (pGr->lNr >= 0L && pGr->lNr < pGr->pFil->lAntGr) {
                                           /* Lovlig kolonne */
       if (kolonne >= BT_MIN_USER  &&  kolonne <= BT_MAX_USER) {
                                           /* Fjern merkingen */
           LI_ClrBt(pGr->pFil,pGr->lNr,kolonne);
       }

   } else{                                 /* Ulovlig gruppe */
      char errtx[50];
      UT_SNPRINTF(errtx,50," %ld",pGr->lNr);
      LC_Error(72,"(LC_ClrBt)",errtx);
   }
}


/*
AR-881123
CH LC_GetBt                                       Hent merke i brukttabellen
CD ==========================================================================
CD Formål:
CD Hent merke i brukttabellen.
CD
CD Parametre:
CD Navn     Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *  pGr      i    Gruppenummer
CD kolonne  short    i    Kolonne som skal brukes.
CD                        (Lovlig BT_MIN_BT - BT_MAX_BT)
CD merke    short    r    UT_FALSE = ikke marka,  UT_TRUE = merka
CD
CD Bruk:
CD merke = LC_GetBt(pGr,kolonne);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetBt(LC_BGR * pGr,short kolonne)
{
   /* LO_TestFilpeker(pGr->pFil,"LC_GetBt"); */
   LO_TestFilpeker(pGr->pFil,"GetBt");

                                           /* Lovlig gruppe */
   if (pGr->lNr >= 0L && pGr->lNr < pGr->pFil->lAntGr) {
                                           /* Lovlig kolonne */
       if (kolonne >= BT_MIN_BT  &&  kolonne <= BT_MAX_BT) {
                                           /* Returner verdi */
           return (LI_InqBt(pGr->pFil,pGr->lNr,kolonne));
       }

   } else{                                 /* Ulovlig gruppe */
      char errtx[50];
      UT_SNPRINTF(errtx,50," %ld",pGr->lNr);
      LC_Error(72,"(LC_GetBt)",errtx);
   }

   return UT_FALSE;                            /* Retur ved feil */
}


/*
AR-881123
CH LC_EraseBt                                   Slett område i brukttabellen
CD ==========================================================================
CD Formål:
CD Blanker en eller flere kolonner i brukttabellen i aktuell base.
CD
CD Parametre:
CD Navn     Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD fra_kol  short    i    Første kolonne som skal blankes.
CD                        (Lovlig BT_MIN_USER - BT_MAX_USER)
CD til_kol  short    i    Siste kolonne som skall blankes.
CD                        (Lovlig BT_MIN_USER - BT_MAX_USER)
CD
CD Bruk:
CD LC_EraseBt(fra_kol,til_kol);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_EraseBt(short fra_kol,short til_kol)
{
                       /* Beregner lovlige kolonner */
   fra_kol = max(fra_kol,BT_MIN_USER);
   til_kol = min(til_kol,BT_MAX_USER);

   LI_EraseBt(fra_kol,til_kol);
}


/*
AR-891120
CH LI_SetBt                                       Sett merke i brukttabellen
CD ==========================================================================
CD Formål:
CD Legg inn merke i brukttabellen.
CD
CD Parametre:
CD Navn     Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD long       lGrNr  i    Gruppenummer
CD kolonne    short  i    Kolonne som skal merkes.
CD                        (Lovlig BT_MIN_BT - BT_MAX_BT)
CD
CD Bruk:
CD LI_SetBt(pFil,lGrNr,kolonne);
   ==========================================================================
*/
void LI_SetBt(LC_FILADM *pFil,long lGrNr,short kolonne)
{
   LI_PutBt (pFil,lGrNr,LI_GetBt(pFil,lGrNr) | (0x1UL << kolonne));
}


/*
AR-891120
CH LI_ClrBt                                      Slett merke i brukttabellen
CD ==========================================================================
CD Formål:
CD Fjern merke i brukttabellen.
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD long       lGrNr  i    Gruppenummer
CD kolonne    short  i    Kolonne som skal merkes.
CD                        (Lovlig BT_MIN_BT - BT_MAX_BT)
CD
CD Bruk:
CD LI_ClrBt(pFil,lGrNr,kolonne);
   ==========================================================================
*/
void LI_ClrBt(LC_FILADM *pFil,long lGrNr,short kolonne)
{
   LI_PutBt(pFil,lGrNr,LI_GetBt(pFil,lGrNr) & (~ (0x1UL << kolonne) ));
}


/*
AR-910828
CH LI_InqBt                                       Hent merke i brukttabellen
CD ==========================================================================
CD Formål:
CD Hent merke i brukttabellen.
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD long       lGrNr  i    Gruppenummer
CD kolonne    short  i    Kolonne som skal brukes.
CD                        (Lovlig BT_MIN_BT - BT_MAX_BT)
CD merke      short  r    UT_TRUE = marka,  UT_FALSE = ikke merka.
CD
CD Bruk:
CD merke = LI_InqBt(pFil,lGrNr,kolonne);
   ==========================================================================
*/
short LI_InqBt(LC_FILADM *pFil,long lGrNr,short kolonne)
{
   return ((LI_GetBt(pFil,lGrNr) & (0x1UL << kolonne)) == 0)?  UT_FALSE : UT_TRUE;
}


/*
AR-910827
CH LI_EraseBt                                   Slett område i brukttabellen
CD ==========================================================================
CD Formål:
CD Blanker en eller flere kolonner i brukttabellen i aktuell base.
CD
CD Parametre:
CD Type   Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD short  fra_kol    i    Første kolonne som skal blankes. (Lovlig 0 - BT_MAX_BT)
CD short  til_kol    i    Siste kolonne som skal blankes. (Lovlig 0 - BT_MAX_BT)
CD
CD Bruk:
CD LI_EraseBt(fra_kol,til_kol);
   ==========================================================================
*/
void LI_EraseBt(short fra_kol,short til_kol)
{
   long lNr;
   unsigned long maske;
   LC_FILADM *pFil;

                                               /* Beregner lovlige områder */
   fra_kol = max(fra_kol,BT_MIN_BT);
   til_kol = min(til_kol,BT_MAX_BT);

   maske = 0x0000;                             /* Lager slettemaske */
   for ( ; fra_kol <= til_kol; fra_kol++){
       maske |= (0x1UL << fra_kol);   /* Merker bit som skal blankes */
   }
   maske = ~ maske;                            /* Inverterer masken */

   /*
    * Fjerner merkingen
    */
   for (pFil=Sys.pAktBase->pForsteFil; pFil != NULL; pFil=pFil->pNesteFil) {
      for (lNr=0L; lNr<pFil->lAntGr; lNr++) {
         LI_PutBt(pFil,lNr,(maske & LI_GetBt(pFil,lNr)));
      }
   }
}


/*
AR-910827
CH LC_CopyBt                                  Kopier kolonne i brukttabellen
CD ==========================================================================
CD Formål:
CD Kopier kolonne i brukttabellen.
CD Samtidig er det mulig å utføre logiske operasjoner mellom de to kolonnene.
CD
CD Parametre:
CD Type   Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD short  fra_kol      i    Kolonne det skal kopieres fra. (Lovlig 0 - BT_MAX_BT)
CD short  til_kol      i    Kolonne det skal kopieres til. (Lovlig 1 - BT_MAX_USER)
CD short  operasjon    i    Logisk operasjon mellom kolonnene.
CD                           BC_COPY     = Overskriv gammelt innhold.
CD                           BC_AND      = Logisk AND mellom de to kolonnene.               
CD                           BC_OR       = Logisk OR mellom de to kolonnene.               
CD                           BC_INVERT   = Overskriv gammelt innhold med
CD                                         invertert verdi.
CD                           BC_EXCHANGE = Bytter innholdet i de to kolonnene.
CD                                           
CD Bruk:
CD LC_CopyBt(fra_kol,til_kol,operasjon);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_CopyBt(short fra_kol,short til_kol,short operasjon)
{
   long lNr;
   unsigned long maske_fra,maske_til;
   LC_FILADM *pFil = Sys.pAktBase->pForsteFil;
   unsigned long merke;
   unsigned long ul;

                                           /* Beregner lovlige områder */
   fra_kol = min(max(fra_kol,0),BT_MAX_BT);
   til_kol = min(max(til_kol,0),BT_MAX_USER);

                                           /* Returner verdi */
   maske_fra = 0x00000001UL << fra_kol;
   maske_til = 0x00000001UL << til_kol;


                                           /* Går gjennom alle grupper */
   for (; pFil != NULL; pFil=pFil->pNesteFil) {
      for (lNr=1L; lNr<pFil->lAntGr; lNr++) {
         merke = LI_GetBt(pFil,lNr);
         switch (operasjon){
            case BC_AND:                                        /* AND */
               if ((merke & maske_fra)  &&  (merke & maske_til)){
                  merke |= maske_til;             /* Sett */
               } else{
                  merke &= ( ~ maske_til);        /* Blank */
               }
               break;

            case BC_OR:                                         /* OR */
               if ((merke & maske_fra)  ||  (merke & maske_til)){
                  merke |= maske_til;             /* Sett */
               } else{
                  merke &= ( ~ maske_til);        /* Blank */
               }
               break;

            case BC_INVERT:                    /* INVERT  (Invertert kopi)*/
               if (merke & maske_fra) {
                  merke &= ( ~ maske_til);        /* Blank */
               } else{
                  merke |= maske_til;             /* Sett */
               }
               break;

            case BC_EXCHANGE:                                       /* BYTT */
               /* Husk innholdet i "til-kolonnen" */
               ul = merke & maske_til;
               /* Oppdater "til-kolonnen" */
               if (merke & maske_fra) {
                   merke |= maske_til;             /* Sett */
               } else{
                   merke &= ( ~ maske_til);        /* Blank */
               }
               /* Oppdater "fra-kolonnen" */
               if (ul) {
                   merke |= maske_fra;             /* Sett */
               } else{
                   merke &= ( ~ maske_fra);        /* Blank */
               }
               break;

            default:
            case BC_COPY:                                       /* COPY */
               if (merke & maske_fra) {
                   merke |= maske_til;             /* Sett */
               } else{
                   merke &= ( ~ maske_til);        /* Blank */
               }
               break;
         }

            /* Skriv tilbake */
      LI_PutBt(pFil,lNr,merke);
      }
   }
}


/*
AR-891120
CH LI_SaveAdm                          Skriv globale variabler til indeksfil
CD ==========================================================================
CD Formål:
CD Skriver globale variabler til indeksfilen.
CD
CD Parametre:
CD Type   Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD LI_SaveAdm(pFil);
   ==========================================================================
*/
void LI_SaveAdm(LC_FILADM *pFil)
{
   UT_INT64 Size;
   FTID FilTid;
   FILE *pF;

   /* Åpner Adm-fil, og posisjonerer */
   pF = LI_OpenAdm(pFil);

   /* Filstørrelse for SOSI-filen */
   UT_InqPathSize_i64(pFil->pszNavn,&Size);
   pFil->SosiBytes = Size;

   /* Oppdateringstid for SOSI-filen */
   UT_InqPathTid(pFil->pszNavn,&FilTid);
   pFil->SosiTid.usAar  = FilTid.usAar;
   pFil->SosiTid.usMnd  = FilTid.usMnd;
   pFil->SosiTid.usDag  = FilTid.usDag;
   pFil->SosiTid.usTime = FilTid.usTime;
   pFil->SosiTid.usMin  = FilTid.usMin;
   pFil->SosiTid.usSek  = FilTid.usSek;


   pFil->sIdxOpen = UT_FALSE;
   pFil->ulPid = 0;
   if (fwrite(pFil,sizeof(*pFil),1,pF) != 1) {
      LC_Error(112,"(LI_SaveAdm)","");
      exit(99);
   }

   fclose(pF);
}


/*
AR-891120
CH LI_ReadAdm                            Les globale variabler fra indeksfil
CD ==========================================================================
CD Formål:
CD Åpner Adm-filen, og henter "globale" variabler fra indeksfilen.
CD
CD Parametre: ingen
CD Type       Navn   I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil    i    Peker til FilAdm
CD short      status  r    Status:
CD                         UT_OK (0): Lest OK
CD                         LI_LESEFEIL: Feil ved lesing av 
CD                         LI_OPPTATT: Filen er åpen i et annet program
CD                         LI_FEIL_INDEKSVERSJON: Feil indeksversjon
CD                         LI_FEIL_STORRELSE: Feil størrelse på SOSI-filen
CD                         LI_FEIL_OPPDATTID: Feil oppdateringstid på SOSI-filen
CD
CD Bruk:
CD sStatus = LI_ReadAdm(pFil);
   ==========================================================================
*/
static short LI_ReadAdm(LC_FILADM *pFil)
{
   unsigned short  usLag;
   FTID SosiTid;
   UT_INT64 SosiSize;
   short  sAccess;         
   short sTegnsett;
   char  *pszNavn;
   LC_IDX_TABELL *pIdx;
   LC_FILADM *pNesteFil;
   LC_BASEADM *pBase;   
   FILE *pF;
   LC_R_NODE *pGeoRN;
   short  sStatus = UT_OK;         


   /* Åpner Adm-fil, og posisjonerer */
   pF = LI_OpenAdm(pFil);

   /* Tar vare på div. adm som ikke må bli overskrevet av adm fra filen */
   pszNavn   = pFil->pszNavn;
   sAccess   = pFil->sAccess;
   usLag     = pFil->usLag;
   pBase     = pFil->pBase;
   pIdx      = pFil->pIdx;
   pGeoRN    = pFil->pGeoRN;
   pNesteFil = pFil->pNesteFil;
   pBase     = pFil->pBase;
   sTegnsett = pFil->sTegnsett;

   /* Hent div. opplysninger om SOSI-filen */
   UT_InqPathSize_i64(pszNavn,&SosiSize);
   UT_InqPathTid(pszNavn,&SosiTid);

   /* Leser adm */
   if (fread(pFil,sizeof(*pFil),1,pF) != 1)
   {
      /* printf("\nFeil lengde lest."); */
      sStatus = LI_LESEFEIL;
   }
   
   // lest OK
   else
   { 
      /*
      // Sjekk om filen er åpen i et annet program
      if (pFil->sIdxOpen == UT_TRUE)
      {
         // Sjekk om dette programmet er aktivt nå, eller om det har krasjet
         // (ulPid er prosessID for programmet som åpnet filen)
         if (pFil->ulPid != 0)
         {
            HANDLE hProgram = OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, pFil->ulPid );
            if (hProgram != NULL)
            {
               // Programmet finnes / er aktivt nå
               CloseHandle(hProgram);
               // printf("\nFilen er åpen i et annet program.");
               sStatus = LI_OPPTATT;
            }
         }
      }
      */

      // Ikke åpen i annet program som er aktivt nå
      if (sStatus == UT_OK)
      {
         /* Sjekk versjonsnummer */
         if (strcmp(FYBA_INDEKS_VERSJON,pFil->szIdxVer) != 0) {
            /* printf("\nFeil indeksversjon"); */
            sStatus = LI_FEIL_INDEKSVERSJON;

         /* Sjekk størrelse for SOSI-filen */
         } else if (pFil->SosiBytes != SosiSize) {
            /* printf("\nFeil størrelse på SOSI-filen."); */
            sStatus = LI_FEIL_STORRELSE;

         /* Sjekk oppdateringstid for SOSI-filen */
         } else if (memcmp(&pFil->SosiTid,&SosiTid,sizeof(FTID)) != 0) {
            /* printf("\nFeil oppdateringstid"); */
            sStatus = LI_FEIL_OPPDATTID;
         }
      }
   }

   /* Legg inn igjen diverse  adm. */
   pFil->pszNavn   = pszNavn;
   pFil->sAccess   = sAccess;
   pFil->usLag     = usLag;
   pFil->pBase     = pBase;
   pFil->pIdx      = pIdx;
   pFil->pGeoRN    = pGeoRN;
   pFil->pNesteFil = pNesteFil;
   pFil->pBase     = pBase;
   pFil->sTegnsett = sTegnsett;
   UT_StrCopy(pFil->szBaseVer,FYBA_IDENT,LC_BASEVER_LEN);
   UT_StrCopy(pFil->szIdxVer,FYBA_INDEKS_VERSJON,5);
      

   // Retur hvis feil
   if (sStatus != UT_OK)
   {
      fclose(pF);
      return sStatus;
   }

   // Marker at basen er åpnet
   pFil->sIdxOpen = UT_TRUE;
#ifdef LINUX
   pFil->ulPid = getpid();
#else
   pFil->ulPid = _getpid();
#endif

   // Skriv
   fseek(pF,0L,SEEK_SET);
   if (fwrite(pFil,sizeof(*pFil),1,pF) != 1) 
   {
      LC_Error(112,"(LI_ReadAdm)","");
      exit(99);
   }

   // Stenger filen
   fclose(pF);

   return sStatus;
}


/*
AR-930824
CH LI_WriteRb                                     Skriv gruppe til bufferfil
CD ==========================================================================
CD Formål:
CD Skriv gruppe fra buffer i minne til buffer-fil.
CD
CD Parametre:
CD Type            Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM      *pFil      i    Peker til FilAdm
CD UT_INT64        n64FilPos i    Startposisjon i buffer-filen.
CD char           *pszGi     iu   Ginfo-buffer
CD unsigned long   ulGiLen   i    Ant tegn som skal skrives
CD double         *pdAust    iu   Koord
CD double         *pdNord    iu   Koord
CD LB_INFO *        pInfo     iu   Høyde, KP og PINFO-ofsett
CD long            lNko      i    Ant koord
CD char           *pszPi     iu   Pinfo-buffer
CD unsigned long   ulPiLen   i    Ant tegn som skal skrives
CD
CD Bruk:
CD LI_WriteRb(pFil,lFilPos,Sys.Ginfo.pszTx,Sys.pGrInfo->ulGiLen,
CD            Sys.pdAust, Sys.pdNord, Sys.pInfo, Sys.pGrInfo->nko,
CD            Sys.pszPinfo, Sys.pGrInfo->ulPiLen);
   ==========================================================================
*/
void LI_WriteRb(LC_FILADM *pFil, UT_INT64 n64FilPos,
                char *pszGi, unsigned long ulGiLen,
                double *pdAust, double *pdNord,
                LB_INFO * pInfo, long lNko,
                char *pszPi, unsigned long ulPiLen)
{
   short sSkrivefeil = UT_FALSE;
   FILE *pF;

   /* Åpner RB-fil, og posisjonerer */
   LI_OpenRb(pFil,n64FilPos,SKRIV);
   pF = pFil->pBase->pfRb;

   /* GINFO */
   if (ulGiLen > 0) {
      if (fwrite(pszGi,(sizeof(char))*ulGiLen,1,pF) != 1) {
         sSkrivefeil = UT_TRUE;
      }
   }

   if (lNko > 0) {
      /* Øst koordinat */
      if (fwrite(pdAust,(sizeof(double))*lNko,1,pF) != 1) {
         sSkrivefeil = UT_TRUE;
      }

      /* Nord koordinat */
      if (fwrite(pdNord,(sizeof(double))*lNko,1,pF) != 1) {
         sSkrivefeil = UT_TRUE;
      }

      /* Høyde, KP mm. */
      if (fwrite(pInfo,(sizeof(LB_INFO)) * lNko,1,pF) != 1) {
         sSkrivefeil = UT_TRUE;
      }

      /* PINFO */
      if (ulPiLen > 0) {
         if (fwrite(pszPi,(sizeof(char))*ulPiLen,1,pF) != 1) {
            sSkrivefeil = UT_TRUE;
         }
      }
   }

   if (sSkrivefeil == UT_TRUE) {
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s : %lld",pFil->pszNavn,n64FilPos);
      LC_Error(74,"(LI_WriteRb): ",err().tx);
      exit(99);
   }

   pFil->pBase->n64FilPosRb = _ftelli64(pF);
}


/*
AR-930823
CH LI_ReadRb                                       Les gruppe fra buffer-fil
CD ==========================================================================
CD Formål:
CD Les gruppe fra buffer-fil til buffer i minne.
CD
CD Parametre:
CD Type            Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM      *pFil      i    Peker til FilAdm for filen det skal leses fra.
CD UT_INT64        n64FilPos i    Startposisjon i buffer-filen.
CD char           *pszGi     iu   Ginfo-buffer
CD unsigned long   ulGiLen   i    Ant tegn som skal leses til buffer
CD double         *pdAust    iu   Koord
CD double         *pdNord    iu   Koord
CD LB_INFO *        pInfo     iu   Høyde, KP og PINFO-ofsett
CD long            lNko      i    Ant koord
CD char           *pszPi     iu   Pinfo-buffer
CD unsigned long   ulPiLen   i    Ant tegn som skal leses til buffer
CD
CD Bruk:
CD LI_ReadRb(pFil,lFilPos,Sys.Ginfo.pszTx,Sys.pGrInfo->ulGiLen,
CD           Sys.pdAust, Sys.pdNord, Sys.pInfo, Sys.pGrInfo->nko,
CD           Sys.pszPinfo, Sys.pGrInfo->ulPiLen);
   ==========================================================================
*/
void LI_ReadRb(LC_FILADM *pFil, UT_INT64 n64FilPos,
               char *pszGi, unsigned long ulGiLen,
               double *pdAust, double *pdNord,
               LB_INFO * pInfo, long lNko,
               char *pszPi, unsigned long ulPiLen)
{
   short sLesefeil = UT_FALSE;
   FILE *pF;

   /* Åpner RB-fil, og posisjonerer */
   LI_OpenRb(pFil,n64FilPos,LES);
   pF = pFil->pBase->pfRb;

   /* Leser GINFO */
   if (ulGiLen > 0) {
      if (fread(pszGi,(sizeof(char))*ulGiLen,1,pF) != 1) {
         sLesefeil = UT_TRUE;
      }
      // AR:2004-05-14 - Test
      /*
      int antall = fread(pszGi,(sizeof(char))*ulGiLen,1,pF);
      if (antall != 1) {
         sLesefeil = UT_TRUE;
         // Bygger streng for feilvisning
         char szError[256];
         strerror_s(szError,256,errno);
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"%s",szError);
         if (feof(pF)) {
            UT_SNPRINTF(err().tx,LC_ERR_LEN,"Filslutt");
         }
      }
      */
   }

   if (lNko > 0) {
      /* Leser øst koordinat */
      if (fread(pdAust,(sizeof(double))*lNko,1,pF) != 1) {
         sLesefeil = UT_TRUE;
      }

      /* Leser nord koordinat */
      if (fread(pdNord,(sizeof(double))*lNko,1,pF) != 1) {
         sLesefeil = UT_TRUE;
      }

      /* Leser høyde, KP mm. */
      if (fread(pInfo,(sizeof(LB_INFO)) * lNko,1,pF) != 1) {
         sLesefeil = UT_TRUE;
      }

      /* Leser PINFO */
      if (ulPiLen > 0) {
         if (fread(pszPi,(sizeof(char))*ulPiLen,1,pF) != 1) {
            sLesefeil = UT_TRUE;
         }
      }
   }

   if (sLesefeil == UT_TRUE) {
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s : %lld",pFil->pszNavn,n64FilPos);

      LC_Error(73,"(LI_ReadRb): ",err().tx);
      exit(99);
   }

   pFil->pBase->n64FilPosRb = _ftelli64(pF);
}


/*
AR-930825
CH LI_ReadCoordRb                            Les koordinater fra buffer-fil
CD ==========================================================================
CD Formål:
CD Les koordinatene for en gruppe fra buffer-fil til buffer i minne.
CD
CD Parametre:
CD Type            Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM      *pFil      i    Peker til FilAdm for filen det skal leses fra.
CD UT_INT64        n64FilPos i    Startposisjon for gruppen i buffer-filen.
CD unsigned long   ulGiLen   i    Ant tegn GINFO
CD double         *pdAust    iu   Koord
CD double         *pdNord    iu   Koord
CD LB_INFO *        pInfo     iu   Høyde, KP og PINFO-ofsett
CD long            lNko      i    Ant koord
CD char           *pszPi     iu   Pinfo-buffer
CD unsigned long   ulPiLen   i    Ant tegn som skal leses til buffer
CD
CD Bruk:
CD LI_ReadCoordRb(pFil,lFilPos,Sys.pGrInfo->ulGiLen,
CD           Sys.pdAust, Sys.pdNord, Sys.pInfo, Sys.pGrInfo->nko,
CD           Sys.pszPinfo, Sys.pGrInfo->ulPiLen);
   ==========================================================================
*/
void LI_ReadCoordRb(LC_FILADM *pFil, UT_INT64 n64FilPos, unsigned long ulGiLen,
               double *pdAust, double *pdNord,
               LB_INFO * pInfo, long lNko,
               char *pszPi, unsigned long ulPiLen)
{
   short sLesefeil = UT_FALSE;
   FILE *pF;

   /* Åpner RB-fil, og posisjonerer */
   LI_OpenRb(pFil,n64FilPos+(UT_INT64)ulGiLen,LES);
   pF = pFil->pBase->pfRb;

   if (lNko > 0) {
      /* Leser øst koordinat */
      if (fread(pdAust,(sizeof(double))*lNko,1,pF) != 1) {
         sLesefeil = UT_TRUE;
      }

      /* Leser nord koordinat */
      if (fread(pdNord,(sizeof(double))*lNko,1,pF) != 1) {
         sLesefeil = UT_TRUE;
      }

      /* Leser høyde, KP mm. */
      if (fread(pInfo,(sizeof(LB_INFO))*lNko,1,pF) != 1) {
         sLesefeil = UT_TRUE;
      }

      /* Leser PINFO */
      if (ulPiLen > 0) {
         if (fread(pszPi,(sizeof(char))*ulPiLen,1,pF) != 1) {
            sLesefeil = UT_TRUE;
         }
      }
   }

   if (sLesefeil == UT_TRUE) {
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s : %lld",pFil->pszNavn,n64FilPos);
      LC_Error(73,"(LI_ReadCoordRb): ",err().tx);
      exit(99);
   }

   pFil->pBase->n64FilPosRb = _ftelli64(pF);
}



/*
AR-930823
CH LI_BerBufferLen                                      Beregn bufferlengde
CD ==========================================================================
CD Formål:
CD Beregn nødvendig plass for å skrive gitt gruppe til RB.
CD
CD Parametre:
CD Type            Navn   I/U   Forklaring
CD --------------------------------------------------------------------------
CD unsigned long   ulGiLen i    Ant tegn som skal leses til buffer
CD long            lNko    i    Ant koord
CD unsigned long   ulPiLen i    Ant tegn som skal leses til buffer
CD long            lLen    r    Ant byte for å lagre gruppen
CD
CD Bruk:
CD lLen = LI_BerBufferLen(Sys.pGrInfo->ulGiLen,Sys.pGrInfo->nko,
CD                        Sys.pGrInfo->ulPiLen);
   ==========================================================================
*/
long LI_BerBufferLen(unsigned long ulGiLen,long lNko,unsigned long ulPiLen)
{
            /* GINFO */
            /* Koordinat Ø og N */
            /* Høyde, KP og PINFO-ofsett */
            /* PINFO */
   return  ((long)sizeof(char) * (long)ulGiLen) +
           (2L * (long)sizeof(double) * lNko) +
           ((long)sizeof(LB_INFO) * lNko) +
           ((long)sizeof(char) * (long)ulPiLen);


#ifdef TEST
   long lLen;

   /* GINFO */
   lLen = (sizeof(char)) * ulGiLen;

   /* Koordinat Ø og N */
   lLen += 2L * (sizeof(double)) * lNko;

   /* Høyde, KP og PINFO-ofsett */
   lLen += (sizeof(LB_INFO)) * lNko;

   /* PINFO */
   lLen += (sizeof(char)) * ulPiLen;

   return lLen;
#endif
}


/*
AR-910929
CH LI_OpenRb                                         Åpne og posisjoner, Rb
CD ==========================================================================
CD Formål:
CD Sjekker at rett Rb-fil er åpen, og posisjoner
CD
CD Parametre:
CD Type       Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil      i    Peker til FilAdm
CD UT_INT64   n64FilPos i    Filposisjon i byte fra filstart
CD short      sModus    i    Modus (LES / SKRIV)
CD
CD Bruk:
CD void LI_OpenRb(pFil,lFilPos);
   ==========================================================================
*/
static void LI_OpenRb(LC_FILADM *pFil,UT_INT64 n64FilPos,short sModus)
{
   if (pFil->pBase->pCurRb != pFil) {
      // ----- Feil fil er åpen, stenger denne og åpner rett fil

      // Stenger forrige fil
      if (pFil->pBase->pCurRb != NULL) {
         fclose(pFil->pBase->pfRb);
      }

      // Byggr opp fullt filnavn til Rb-filen og åpner filen
      pFil->pBase->pfRb = LI_OpenIdxFil(pFil, "Rb", ".Idx");

      // Husk current filnummer
      pFil->pBase->pCurRb = pFil;
      pFil->pBase->sModusRb = NY;
   }

   // Posisjoner hvis nødvendig
   if (pFil->pBase->sModusRb == NY  ||  sModus != pFil->pBase->sModusRb  ||  n64FilPos != pFil->pBase->n64FilPosRb) {
      //_fseeki64(pFil->pBase->pfRb,n64FilPos,SEEK_SET);
      UT_SetPos_i64(pFil->pBase->pfRb,n64FilPos);

      pFil->pBase->sModusRb = sModus;
   }
}



/*
AR-930927
CH LC_SetModusMerk                Setter flag for merking av referert gruppe.
CD ==========================================================================
CD Formål:
CD Setter flag for merking av referert gruppe.
CD Har innvirkning for virkemåten til:
CD LC_FAGeo, LC_FASn, og LC_FAGiQuery
CD
CD Parametre:
CD Type           Navn   I/U  Forklaring
CD -----------------------------------------------------------------------
CD unsigned short modus   i   0 = Ikke merk referert gruppe.
CD                            1 = Merk referert gruppe.
CD
CD Bruk:
CD LC_SetModusMerk(1);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_SetModusMerk(unsigned short usModus)
{
   Sys.usMerkRefGr = usModus;
}


/*
AR-881123
CH LC_MerkGr                                    Merk en gruppe brukttabellen
CD ==========================================================================
CD Formål:
CH Merk aktuell gruppe i brukttabellen. Hvis flag for merking av referert
CD gruppe er satt, blir også eventuelle refererte grupper merket.
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD short   sKolonne   i    Kolonne som skal merkes.
CD                         (Lovlig BT_MIN_USER - BT_MAX_USER)
CD short   sBryter    i    Bryter   1=på, 0=av
CD long    lAntall    r    Antall grupper merket.
CD
CD Bruk:
CD lAntall = LC_MerkGr(sKolonne,sBryter);
   ==========================================================================
*/
SK_EntPnt_FYBA long LC_MerkGr(short sKolonne,short sBryter)
{
   LC_BGR AktBgr,Bgr;
   long lAntRef;
   short sGiLin,sRefPos;
   long l;
   short ngi;
   long nko;
   unsigned short info;
   long *plRefArr;
   long lAntall = 0L;


   /* Lovlig gruppe */
   if (Sys.GrId.lNr != INGEN_GRUPPE) {
      /* Lovlig kolonne */
      if (sKolonne >= BT_MIN_BT  &&  sKolonne <= BT_MAX_BT) {
         /* Merk denne gruppen */
         if (sBryter) {
            LI_SetBt(Sys.GrId.pFil,Sys.GrId.lNr,sKolonne);

         } else {
            LI_ClrBt(Sys.GrId.pFil,Sys.GrId.lNr,sKolonne);
         }
         lAntall++;

         /* Er det referanser på gruppen og rekursiv merking er aktivisert? */
         if ((Sys.pGrInfo->info & GI_REF)  &&  Sys.usMerkRefGr) {
            /* Husk aktuell gruppe */
            AktBgr = Sys.GrId;

            /* Hent og merk refererte grupper */
				lAntRef = LC_InqAntRef();
				plRefArr = (long *) UT_MALLOC(lAntRef * sizeof(long));
				sGiLin = 2;
				sRefPos = 0;
				LC_GetRef(plRefArr,lAntRef,&sGiLin,&sRefPos);
				for (l=0; l<lAntRef; l++) {
               if (plRefArr[l] != START_OY  &&  plRefArr[l] != SLUTT_OY) {
                  if (LC_FiSn(AktBgr.pFil,labs(plRefArr[l]),&Bgr)) {
                     LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
                     lAntall += LC_MerkGr(sKolonne,sBryter);
                  }
               }
            }
				UT_FREE(plRefArr);

            /* Les tilbake aktuell gruppe */
            LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);
         }
      }
   }

   return lAntall;
}


/*
AR-931101
CH LC_ClrPrioritet                                      Slett prioritets-bit
CD ==========================================================================
CD Formål:
CD Slett prioritets-bit.
CD
CD Parametre:
CD Navn     Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *  pGr      i    Gruppenummer
CD kolonne  short    i    Kolonne som skal merkes.
CD                        (Lovlig 0 til LC_MAX_ANT_PRIOR-1)
CD
CD Bruk:
CD LC_ClrPrioritet(pGr,kolonne);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_ClrPrioritet(LC_BGR * pGr,short kolonne)
{
   short s;
   LC_GRTAB_LINJE * pGrt;

   LO_TestFilpeker(pGr->pFil,"ClrPrioritet");

   /* Lovlig gruppe */
   if (pGr->lNr >= 0L && pGr->lNr < pGr->pFil->lAntGr) {
      /* Lovlig kolonne */
      if (kolonne >= 0  &&  kolonne < LC_MAX_ANT_PRIOR) {

         pGrt = LI_GetGrt(pGr->pFil,pGr->lNr);

         /* Fjern merkingen */
         s = kolonne / 32;
         pGrt->ulPrior[s]  &=  (~ (0x1UL << (kolonne % 32)) );

      }

   } else{                                 /* Ulovlig gruppe */
      char errtx[50];
      UT_SNPRINTF(errtx,50," %ld",pGr->lNr);
      LC_Error(72,"(LC_ClrPrioritet)",errtx);
   }
}


/*
AR-931101
CH LC_SetPrioritet                                      Sett prioritets-bit
CD ==========================================================================
CD Formål:
CD Sett prioritets-bit.
CD
CD Parametre:
CD Navn     Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *  pGr      i    Gruppenummer
CD kolonne  short    i    Kolonne som skal merkes.
CD                        (Lovlig 0 til LC_MAX_ANT_PRIOR-1)
CD
CD Bruk:
CD LC_SetPrioritet(pGr,kolonne);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_SetPrioritet(LC_BGR * pGr,short kolonne)
{
   short s;
   LC_GRTAB_LINJE * pGrt;

   LO_TestFilpeker(pGr->pFil,"SetPrioritet");

   /* Lovlig gruppe */
   if (pGr->lNr >= 0L && pGr->lNr < pGr->pFil->lAntGr) {
      /* Lovlig kolonne */
      if (kolonne >= 0  &&  kolonne < LC_MAX_ANT_PRIOR) {

         pGrt = LI_GetGrt(pGr->pFil,pGr->lNr);

         /* Fjern merkingen */
         s = kolonne / 32;
         pGrt->ulPrior[s]  |=  (0x1UL << (kolonne % 32));
      }

   } else {                                 /* Ulovlig gruppe */
      char errtx[50];
      UT_SNPRINTF(errtx,50," %ld",pGr->lNr);
      LC_Error(72,"(LC_SetPrioritet)",errtx);
   }
}


/*
AR-931101
CH LC_InqPrioritet                                       Hent prioritets-bit
CD ==========================================================================
CD Formål:
CD Hent prioritets-bit.
CD
CD Parametre:
CD Navn     Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *  pGr      i    Gruppenummer
CD kolonne  short    i    Kolonne som skal hentes.
CD                        (Lovlig 0 til LC_MAX_ANT_PRIOR-1)
CD short    sAvPaa   r    Av eller På  (UT_TRUE = På, UT_FALSE = Av)
CD
CD Bruk:
CD sAvPaa = LC_InqPrioritet(pGr,kolonne);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_InqPrioritet(LC_BGR * pGr,short kolonne)
{
   short s;
   LC_GRTAB_LINJE * pGrt;

   LO_TestFilpeker(pGr->pFil,"InqPrioritet");

   /* Lovlig gruppe */
   if (pGr->lNr >= 0L && pGr->lNr < pGr->pFil->lAntGr) {
      /* Lovlig kolonne */
      if (kolonne >= 0  &&  kolonne < LC_MAX_ANT_PRIOR) {

         pGrt = LI_GetGrt(pGr->pFil,pGr->lNr);

         /* Returner aktuellt bit */
         s = kolonne / 32;
         return ((pGrt->ulPrior[s] & (0x1UL << (kolonne % 32))) == 0UL)?  UT_FALSE : UT_TRUE;
      }

   } else {                                 /* Ulovlig gruppe */
      char errtx[50];
      UT_SNPRINTF(errtx,50," %ld",pGr->lNr);
      LC_Error(72,"(LC_SetPrioritet)",errtx);
   }

   return UT_FALSE;
}


/*
AR-931101
CH LC_ErasePrioritet                                 Blank ut prioritets-bit
CD ==========================================================================
CD Formål:
CD Blank ut prioritets-bit.
CD
CD Parametre:
CD Navn     Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *  pGr      i    Gruppenummer
CD
CD Bruk:
CD LC_ErasePrioritet(pGr);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_ErasePrioritet(LC_BGR * pGr)
{
   LC_GRTAB_LINJE * pGrt;

   LO_TestFilpeker(pGr->pFil,"ErasePrioritet");

   /* Lovlig gruppe */
   if (pGr->lNr >= 0L && pGr->lNr < pGr->pFil->lAntGr) {

      pGrt = LI_GetGrt(pGr->pFil,pGr->lNr);

      /* Blank ut alle bit */
      pGrt->ulPrior[0] = 0x0UL;
      pGrt->ulPrior[1] = 0x0UL;
      pGrt->ulPrior[2] = 0x0UL;
      pGrt->ulPrior[3] = 0x0UL;

   } else {                                 /* Ulovlig gruppe */
      char errtx[50];
      UT_SNPRINTF(errtx,50," %ld",pGr->lNr);
      LC_Error(72,"(LC_SetPrioritet)",errtx);
   }
}


/*
AR-931101
CH LC_EraseAllPrioritet                        Blank ut ALLE prioritets-bit
CD ==========================================================================
CD Formål:
CD Blank ut alle prioritets-bit på alle gruppene i denne filen.
CD
CD Parametre:
CD Navn        Type    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM  *pFil     i    Filpeker
CD
CD Bruk:
CD LC_EraseAllPrioritet(pFil);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_EraseAllPrioritet(LC_FILADM *pFil)
{
   LC_GRTAB_LINJE * pGrt;
   long lNr;

   LO_TestFilpeker(pFil,"EraseAllPrioritet");

   for (lNr=0L; lNr<pFil->lAntGr; lNr++) {

      pGrt = LI_GetGrt(pFil,lNr);

      /* Blank ut alle bit */
      pGrt->ulPrior[0] = 0x0UL;
      pGrt->ulPrior[1] = 0x0UL;
      pGrt->ulPrior[2] = 0x0UL;
      pGrt->ulPrior[3] = 0x0UL;

   } /* endfor */
}
                                       
/*
AR:2005-06-20
CH LC_DumpBt                                   Dump brukttabellen til stderr
CD ==========================================================================
CD Formål:
CD Dump brukttabellen til stderr
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD
CD Bruk:
CD LC_DumpBt();
   =============================================================================
*/
SK_EntPnt_FYBA void LC_DumpBt(const char *pszMelding)
{
   short ngi,s;
   long nko;
   unsigned short info;
   LC_BGR Bgr,AktBgr;
   char szTx[1024],szOrd[30];
   LC_FILADM *pAktuellFil = NULL;


   LC_GetGrNr(&AktBgr);

   UT_FPRINTF(stderr,"\n=================================================\n");
   UT_FPRINTF(stderr,"Dump av brukt-tabellen i FYBA: %s\n", pszMelding);
   UT_FPRINTF(stderr,"=================================================\n");

   UT_StrCopy(szTx,"\n    Snr  ",1024);

   for (s=BT_MIN_BT; s<=BT_MAX_BT; ++s)
   {
      UT_SNPRINTF(szOrd,30,"%3hd",s);
      UT_StrCat(szTx,szOrd,1024);
   }
   UT_FPRINTF(stderr,"%s\n",szTx);

   UT_FPRINTF(stderr,"---------------------------------------------------------------------------------------------------------\n");

   LC_InitNextBgr(&Bgr);

   /* Alle gruppene i framgrunn */
   while (LC_NextBgr(&Bgr,LC_FRAMGR)) {
      LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
      // Filnavn
      if (Bgr.pFil != pAktuellFil)
      {
         UT_FPRINTF(stderr,"%s\n",Bgr.pFil->pszNavn);
         pAktuellFil = Bgr.pFil;
      }
      // Snr
      UT_SNPRINTF(szTx,1024,"%7ld: ", LC_GetSn());

      for (s=BT_MIN_BT; s<=BT_MAX_BT; ++s)
      {
         UT_SNPRINTF(szOrd,30,"%3hd",LC_GetBt(&Bgr,s));
         UT_StrCat(szTx,szOrd,1024);
      }

      UT_FPRINTF(stderr,"%s\n",szTx);
   }

   UT_FPRINTF(stderr,"\n=================================================\n");

   if (AktBgr.lNr != INGEN_GRUPPE) {
      LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);
   }
}
