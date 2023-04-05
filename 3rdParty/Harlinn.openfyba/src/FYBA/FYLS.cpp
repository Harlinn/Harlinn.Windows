/* == AR 891104 ========================================== */
/*  STATENS KARTVERK  -  FYSAK-PC                          */
/*  Fil: fyls.c                                            */
/*  Innhold: Serienummer system for fysak-pc               */
/* ======================================================= */

#include "fyba.h"
#include "fybax.h"

#include <ctype.h>


/* Globale variabler */
extern LC_SYSTEMADM    Sys;


/*
AR-910930
CH LS_Indx                                              Oppdater indekstabellen
CD =============================================================================
CD Formål:
CD Oppdater søketabellen for serienummer.
CD
CD Parametre: ingen
CD
CD Bruk:
CD LS_Indx();
================================================================================
*/
void LS_Indx(void)
{
   long lSnr = LC_GetSn();

   /* Legg inn snr i tabellen  og oppdaterer max snr for filen */
   LS_PutSn(Sys.GrId.pFil,Sys.GrId.lNr,lSnr);
}


/*
AR-910930
CH LC_SBSn                                   Sett søkegrense for serienummer
CD ==========================================================================
CD Formål:
CD Setter søkegrenser for serienummersøk.
CD
CD Parametre:
CD Type        Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm  iu    Peker til statusblokk for serienummersøk
CD LC_FILADM * pFil     i     Peker til FilAdm
CD long        lMinSnr  i     Fra og med serienummer
CD long        lMaxSnr  i     Til og med serienummer
CD
CD Bruk:
CD LC_SNR_ADM SnrAdm;
CD LC_SBSn(&SnrAdm,pFil,lMinSnr,lMaxSnr);
=============================================================================
*/
SK_EntPnt_FYBA void LC_SBSn(LC_SNR_ADM * pSnrAdm,LC_FILADM *pFil,long lMinSnr,long lMaxSnr)
{
   /* LO_TestFilpeker(pFil,"LC_SBSn"); */
   LO_TestFilpeker(pFil,"SBSn");

   pSnrAdm->pFil = pFil;
   pSnrAdm->lMinSnr = lMinSnr;
   pSnrAdm->lMaxSnr = lMaxSnr;
}


/*
AR-911118
CH LC_FiSn                              Finn gruppenummer for et serienummer
CD ==========================================================================
CD Formål:
CD Finn gruppenummer for et gitt serienummer i søkeområdet for serienummer.
CD Endrer IKKE "current gruppe".
CD
CD Parametre:
CD Type        Navn    I/U    Forklaring
CD -----------------------------------------------------------------------------
CD LC_FILADM * pFil     i     Peker til FilAdm
CD long        lSnr     i     Serienummer som skal finnes
CD LC_BGR *     pBgr     u     Gruppenummer i basen
CD short       sstat    r     Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FiSn(pFil,lSnr,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_FiSn(LC_FILADM *pFil,long lSnr,LC_BGR * pBgr)
{
   /* LO_TestFilpeker(pFil,"LC_FiSn"); */
   LO_TestFilpeker(pFil,"FiSn");

   pBgr->pFil = pFil;
   pBgr->lNr = LI_GetSnr(pFil,lSnr);

   /* Ukjent serienummer  ==> */
   if (pBgr->lNr == INGEN_GRUPPE)  return UT_FALSE;

   return UT_TRUE;
}


/*
AR-91118
CH LC_MoveSn                       Flytt til gruppenummer for et serienummer
CD ==========================================================================
CD Formål:
CD Finn gruppenummer for et gitt serienummer i søkeområdet for serienummer.
CD Intern "aktuellt serienummer" blir endret, slik at videre søk med
CD neste/forrige nå tar utgangspunkt i dette serienummer.
CD (Bare hvis snr er funnet).
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm  iu    Peker til statusblokk for serienummersøk
CD long        lSnr     i     Serienummer som skal finnes
CD LC_BGR *     pBgr     u     Gruppenummer i basen
CD short       sstat    r     Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_MoveSn(pSnrAdm,snr,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_MoveSn(LC_SNR_ADM * pSnrAdm,long lSnr,LC_BGR * pBgr)
{
   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_MoveSn"); */
   LO_TestFilpeker(pSnrAdm->pFil,"MoveSn");

   pBgr->pFil = pSnrAdm->pFil;
   pBgr->lNr = LI_GetSnr(pSnrAdm->pFil,lSnr);

   /* Ukjent serienummer  ==> */
   if (pBgr->lNr == INGEN_GRUPPE)  return UT_FALSE;

   pSnrAdm->lAktSnr = lSnr;

   return UT_TRUE;
}


/*
AR-910930
CH LC_FiArraySn                      Finn gruppenummer for flere serienummer
CD ==========================================================================
CD Formål:
CD Finner gruppenummer for tabell med serienummer.
CD Endrer IKKE "current gruppe".
CD Serienummertabellen kan være "rå" slik den kommer fra GetRef. Linjer med
CD start øy og slutt øy overses.
CD
CD Parametre:
CD Type       Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_FILADM *pFil     i     Peker til FilAdm
CD short      antall   i     Antall linjer brukt i serienummertabellen
CD long      *snr      i     Tabell med serienummer som skal finnes
CD long      *bgr      u     Tabell med gruppenummer funnet
CD                             (INGEN_GRUPPE = ikke funnet)
CD
CD Bruk:
CD LC_FiArraySn(pFil,antall,snr,bgr);
================================================================================
*/
SK_EntPnt_FYBA void LC_FiArraySn(LC_FILADM *pFil,short antall,long *snr,long *bgr)
{
   short s;

   LO_TestFilpeker(pFil,"LC_FiArraySn");

   /* Søk gjennom hele serienummertabellen */
   for (s=0; s<antall; s++) {
      if (snr[s] == START_OY  ||  snr[s] == SLUTT_OY) {
         bgr[s] = INGEN_GRUPPE;

      } else {
         bgr[s] = LI_GetSnr(pFil,labs(snr[s]));
      } /* endif */
   }
}


/*
AR-911022
CH LC_FASn                                             Finn alle serienummer
CD ==========================================================================
CD Formål:
CD Finner alle grupper i fil/serienummer søkeområdet og merker i kolonne
CD BT_SNRSOK i brukttabellen.
CD
CD Parametre:
CD Type        Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm  i    Peker til statusblokk for serienummersøk
CD long        antall   r    Antall grupper funnet.
CD
CD Bruk:
CD antall_funnet = LC_FASn(&SnrAdm);
=============================================================================
*/
SK_EntPnt_FYBA long LC_FASn(LC_SNR_ADM * pSnrAdm)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_BGR AktBgr,Bgr;
   long lSnr,lGrNr;
   long lAntall = 0;
   long lMaxSnr = min(pSnrAdm->pFil->lMaxSnr, pSnrAdm->lMaxSnr);


   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FASn"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FASn");

   /* Husk aktuell gruppe */
   AktBgr = Sys.GrId;

   /* Blanker brukttabellen */
   LI_EraseBt(BT_SNRSOK,BT_SNRSOK);

   /* Sjekker alle serienummer i søkeområdet */
   Bgr.pFil = pSnrAdm->pFil;
   for (lSnr=pSnrAdm->lMinSnr; lSnr<=lMaxSnr; lSnr++) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         Bgr.lNr = lGrNr;
         LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
         lAntall += LC_MerkGr(BT_SNRSOK,1);     /* Tilslag */
      }
   }

   /* Les tilbake aktuell gruppe */
   if (AktBgr.lNr != INGEN_GRUPPE) {
      LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);
   }

   return lAntall;
}


/*
AR-911022
CH LC_FFSn                                              Finn første serienummer
CD =============================================================================
CD Formål:
CD Finner første gruppe i fil/serienummer søkeområdet.
CD
CD Parametre:
CD Type        Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm  iu    Peker til statusblokk for serienummersøk
CD LC_BGR *     pBgr     u     Gruppenummer
CD short       sstat    r     Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FFSn(&SnrAdm,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_FFSn(LC_SNR_ADM * pSnrAdm,LC_BGR * pBgr)
{
   long lSnr,lGrNr;
   long lMaxSnr;

   if (pSnrAdm->pFil == NULL) {
		LC_Error(5,"(LC_FFSn)","Ingen aktuelt fil.");
		return UT_FALSE;
   }

   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FFSn"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FFSn");

   lMaxSnr = min(pSnrAdm->pFil->lMaxSnr, pSnrAdm->lMaxSnr);

   /* Sjekker fra starten av søkeområdet */
   for (lSnr=pSnrAdm->lMinSnr; lSnr<=lMaxSnr; lSnr++) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         /* Tilslag ==> */
         pBgr->pFil = pSnrAdm->pFil;
         pBgr->lNr = lGrNr;
         pSnrAdm->lAktSnr = lSnr;
         return UT_TRUE;
      }
   }

   return UT_FALSE;
}


/*
AR-911022
CH LC_FFSnBt                        Finn første serienummer med tilleggskrav
CD ==========================================================================
CD Formål:
CD Finner første gruppe som er merka i gitt kolonne i brukttabellen.
CD
CD Parametre:
CD Type        Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm   i    Peker til statusblokk for serienummersøk
CD short       kolonne   i    Kolonne i brukt-tabellen som skal sjekkes
CD LC_BGR *     pBgr      u    Gruppenummer
CD short       sstat     r    Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FFSnBt(&SnrAdm,BT_GEOSOK,&Bgr);
=============================================================================
*/
SK_EntPnt_FYBA short LC_FFSnBt(LC_SNR_ADM * pSnrAdm,short kolonne,LC_BGR * pBgr)
{
   long lSnr,lGrNr;
   LC_BGR Bgr;
   long lMaxSnr;

   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FFSnBt"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FFSnBt");

   lMaxSnr = min(pSnrAdm->pFil->lMaxSnr, pSnrAdm->lMaxSnr);

   /* Sjekker fra starten av søkeområdet */
   for (lSnr=pSnrAdm->lMinSnr; lSnr<=lMaxSnr; lSnr++) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         Bgr.pFil = pSnrAdm->pFil;
         Bgr.lNr = lGrNr;
         if (LC_GetBt(&Bgr,kolonne)) {          /* Merka? */
            /* Tilslag ==> */
            pBgr->pFil = pSnrAdm->pFil;
            pBgr->lNr = lGrNr;
            pSnrAdm->lAktSnr = lSnr;
            return UT_TRUE;
         }
      }
   }

   return UT_FALSE;
}


/*
AR-911022
CH LC_FNSn                                            Finn neste serienummer
CD ==========================================================================
CD Formål:
CD Finner neste gruppe i fil/serienummer søkeområdet.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm  iu    Peker til statusblokk for serienummersøk
CD LC_BGR *     pBgr     u     Gruppenummer
CD short       sstat    r     Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FNSn(&SnrAdm,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_FNSn(LC_SNR_ADM * pSnrAdm,LC_BGR * pBgr)
{
   long lSnr,lGrNr;
   long lMaxSnr;

   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FNSn"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FNSn");

   lMaxSnr = min(pSnrAdm->pFil->lMaxSnr, pSnrAdm->lMaxSnr);

   /* Sjekker fra aktuellt serienummer */
   for (lSnr=pSnrAdm->lAktSnr+1L; lSnr<=lMaxSnr; lSnr++) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         /* Tilslag ==> */
         pBgr->pFil = pSnrAdm->pFil;
         pBgr->lNr = lGrNr;
         pSnrAdm->lAktSnr = lSnr;
         return UT_TRUE;
      }
   }

   return UT_FALSE;
}


/*
AR-911022
CH LC_FNSnBt                         Finn neste serienummer med tilleggskrav
CD ==========================================================================
CD Formål:
CD Finner neste gruppe også er merka i gitt kolonne i brukttabellen.
CD
CD Parametre:
CD Type        Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm   i    Peker til statusblokk for serienummersøk
CD short       kolonne   i    Kolonne i brukt-tabellen som skal sjekkes
CD LC_BGR *     pBgr      u    Gruppenummer
CD short       sstat     r    Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FNSnBt(&SnrAdm,BT_GEOSOK,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_FNSnBt(LC_SNR_ADM * pSnrAdm,short kolonne,LC_BGR * pBgr)
{
   long lSnr,lGrNr;
   LC_BGR Bgr;
   long lMaxSnr;

   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FNSnBt"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FNSnBt");

   lMaxSnr = min(pSnrAdm->pFil->lMaxSnr, pSnrAdm->lMaxSnr);

   /* Sjekker fra aktuellt serienummer */
   for (lSnr=pSnrAdm->lAktSnr+1L; lSnr<=lMaxSnr; lSnr++) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         Bgr.pFil = pSnrAdm->pFil;
         Bgr.lNr = lGrNr;
         if (LC_GetBt(&Bgr,kolonne)) {          /* Merka? */
            /* Tilslag ==> */
            pBgr->pFil = pSnrAdm->pFil;
            pBgr->lNr = lGrNr;
            pSnrAdm->lAktSnr = lSnr;
            return UT_TRUE;
         }
      }
   }

   return UT_FALSE;
}


/*
AR-911022
CH LC_FPSn                                              Finn forige serienummer
CD =============================================================================
CD Formål:
CD Finner forrige gruppe i fil/serienummer søkeområdet.
CD
CD Parametre:
CD Type        Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm  iu    Peker til statusblokk for serienummersøk
CD LC_BGR *     pBgr     u     Gruppenummer
CD short       sstat    r     Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FPSn(&SnrAdm,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_FPSn(LC_SNR_ADM * pSnrAdm,LC_BGR * pBgr)
{
   long lSnr,lGrNr;

   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FPSn"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FPSn");

   /* Sjekker fra aktuellt serienummer */
   for (lSnr=pSnrAdm->lAktSnr-1L; lSnr>=pSnrAdm->lMinSnr; lSnr--) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         /* Tilslag ==> */
         pBgr->pFil = pSnrAdm->pFil;
         pBgr->lNr = lGrNr;
         pSnrAdm->lAktSnr = lSnr;
         return UT_TRUE;
      }
   }

   return UT_FALSE;
}


/*
AR-910930
CH LC_FPSnBt                         Finn forige serienummer med tilleggskrav
CD ==========================================================================
CD Formål:
CD Finner forrige gruppe i fil/serienummer søkeområdet, som også er merka i
CD gitt kolonne i brukttabellen.
CD
CD Parametre:
CD Type        Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm   i    Peker til statusblokk for serienummersøk
CD short       kolonne   i    Kolonne i brukt-tabellen som skal sjekkes
CD LC_BGR *     pBgr      u    Gruppenummer
CD short       sstat     r    Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FPSnBt(&SnrAdm,BT_GEOSOK,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_FPSnBt(LC_SNR_ADM * pSnrAdm,short kolonne,LC_BGR * pBgr)
{
   long lSnr,lGrNr;
   LC_BGR Bgr;

   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FPSnBt"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FPSnBt");

   /* Sjekker fra aktuellt serienummer */
   for (lSnr=pSnrAdm->lAktSnr-1L; lSnr>=pSnrAdm->lMinSnr; lSnr--) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         Bgr.pFil = pSnrAdm->pFil;
         Bgr.lNr = lGrNr;
         if (LC_GetBt(&Bgr,kolonne)) {          /* Merka? */
            /* Tilslag ==> */
            pBgr->pFil = pSnrAdm->pFil;
            pBgr->lNr = lGrNr;
            pSnrAdm->lAktSnr = lSnr;
            return UT_TRUE;
         }
      }
   }

   return UT_FALSE;
}


/*
AR-910930
CH LC_FLSn                                              Finn siste serienummer
CD =============================================================================
CD Formål:
CD Finner siste gruppe i fil/serienummer søkeområdet.
CD
CD Parametre:
CD Type        Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm  iu    Peker til statusblokk for serienummersøk
CD LC_BGR *     pBgr     u     Gruppenummer
CD short       sstat    r     Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FLSn(&SnrAdm,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_FLSn(LC_SNR_ADM * pSnrAdm,LC_BGR * pBgr)
{
   long lGrNr;
   long lSnr;

   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FLSn"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FLSn");

   lSnr = min(pSnrAdm->pFil->lMaxSnr, pSnrAdm->lMaxSnr);

   /* Sjekker fra slutten av tabellen */
   for (; lSnr>=pSnrAdm->lMinSnr; lSnr--) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         /* Tilslag ==> */
         pBgr->pFil = pSnrAdm->pFil;
         pBgr->lNr = lGrNr;
         pSnrAdm->lAktSnr = lSnr;
         return UT_TRUE;
      }
   }

   return UT_FALSE;
}


/*
AR-910930
CH LC_FLSnBt                         Finn siste serienummer med tilleggskrav
CD ==========================================================================
CD Formål:
CD Finner siste gruppe i fil/serienummer søkeområdet som også er merka i
CD gitt kolonne i brukttabellen.
CD
CD Parametre:
CD Type        Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_SNR_ADM * pSnrAdm   i    Peker til statusblokk for serienummersøk
CD short       kolonne   i    Kolonne i brukt-tabellen som skal sjekkes
CD LC_BGR *     pBgr      u    Gruppenummer
CD short       sstat     r    Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD sstat = LC_FLSnBt(&SnrAdm,BT_GEOSOK,&Bgr);
================================================================================
*/
SK_EntPnt_FYBA short LC_FLSnBt(LC_SNR_ADM * pSnrAdm,short kolonne,LC_BGR * pBgr)
{
   long lGrNr;
   LC_BGR Bgr;
   long lSnr;

   /* LO_TestFilpeker(pSnrAdm->pFil,"LC_FLSnBt"); */
   LO_TestFilpeker(pSnrAdm->pFil,"FLSnBt");

   lSnr = min(pSnrAdm->pFil->lMaxSnr, pSnrAdm->lMaxSnr);

   /* Sjekker fra slutten av tabellen */
   for (; lSnr>=pSnrAdm->lMinSnr; lSnr--) {
      if ((lGrNr = LI_GetSnr(pSnrAdm->pFil,lSnr)) != INGEN_GRUPPE) {
         Bgr.pFil = pSnrAdm->pFil;
         Bgr.lNr = lGrNr;
         if (LC_GetBt(&Bgr,kolonne)) {          /* Merka? */
            /* Tilslag ==> */
            pBgr->pFil = pSnrAdm->pFil;
            pBgr->lNr = lGrNr;
            pSnrAdm->lAktSnr = lSnr;
            return UT_TRUE;
         }
      }
   }

   return UT_FALSE;
}


/*
AR-910930
CH LS_PutSn                                             Legg inn serienummer
CD ==========================================================================
CD Formål:
CD Legg inn snr i tabellen  og oppdaterer max snr for filen
CD
CD Parametre:
CD Type     Navn   I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil  i   Peker til FilAdm
CD long       lGrNr i   Gruppenummer
CD long       lSnr  i   Serienummer
CD
CD Bruk:
CD LS_PutSn(pFil,lGrNr,lSnr);
=============================================================================
*/
void LS_PutSn(LC_FILADM *pFil,long lGrNr,long lSnr)
{
   if (lSnr >= 0L) {
      /* LO_TestFilpeker(pFil,"LC_PutSn"); */
      LO_TestFilpeker(pFil,"PutSn");

      /* Max snr på filen */
      if (lSnr > pFil->lMaxSnr) {
         pFil->lMaxSnr = lSnr;
      }

      /* Legg inn verdi */
      LI_PutSnr(pFil,lSnr,lGrNr);

   } else {
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %ld ",lSnr);
      LC_Error(61,"(LS_PutSn)",err().tx);
   }
}


/*
AR-891104
CH LS_VisSn                                            Vis serienummer-tabellen
CD =============================================================================
CD Formål:
CD Henter en linje fra serienummer-tabellen som formatert streng.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD long       lin    i    Linjenummer i SN-tab som skal hentes
CD char      *tx     r    Peker til streng med formatert SN-linje
CD
CD Bruk:
CD UT_FPRINTF(stderr,"\nSerienummertabell:\n");
CD for (lin=0L; lin<100L; lin++) {
CD     UT_FPRINTF(stderr,"%s\n",LS_VisSn(BlaFile,lin));
CD }
   =============================================================================
*/
char *LS_VisSn(LC_FILADM *pFil,long lin)
{
   if (lin >= 0L  &&  lin < pFil->lMaxSnr){
       UT_SNPRINTF(err().tx,LC_ERR_LEN,"%8ld: %8ld",lin,LI_GetSnr(pFil,lin));
   } else{
       *err().tx = '\0';
   }
   return err().tx;
}
