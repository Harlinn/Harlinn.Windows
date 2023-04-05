/* === AR-911003 ============================================================ */
/*  STATENS KARTVERK  -  FYSAK-PC                                             */
/*  Fil: fylx.c                                                               */
/*  Innhold: Put og get rutiner til RB                                        */
/* ========================================================================== */

#include "fyba.h"
#include "fybax.h"
 
#include <math.h>

#include <ctype.h>
#include <limits.h>


#include <Windows.h>


/* Globale variabler for FYBA */
extern LC_SYSTEMADM Sys;             /* Systemadministrasjon */
extern char retur_str[LC_MAX_SOSI_LINJE_LEN];  /* Returstreng */

/* Statiske variabler */

/* Lokale rutiner */
static long LX_GetRefOmkrets(LC_GR_STATUS *pGRS,long *ref_array,
                              unsigned char *ref_status,long max_ref);
static long LX_GetRefOy(LC_GRF_STATUS * pGS,long *ref_array,
                         unsigned char *ref_status,long max_ref);
static void LX_CreatePibuf(long lPnr);
static double LX_ArealGruppe(LC_BGR * pBgr,short retning);
static void LX_PutGi(short lin_nr, const char *szGinfo);


/*
AR-920921
CH LC_InitGetRefFlate                       Initierer status for GetRefFlate
CD ==========================================================================
CD Formål:
CD Initierer status for GetRefFlate.
CD
CD Parametre:
CD Type           Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_GRF_STATUS * pRefStat  iu   Struktur med statusopplysninger.
CD
CD Bruk:
CD     LC_InitGetRefFlate(pGrfStat,pBgr);
CD ==========================================================================
*/
SK_EntPnt_FYBA void LC_InitGetRefFlate(LC_GRF_STATUS * pGS)
{
   pGS->Omkr.sGiLinNr = 2;
   pGS->Omkr.sRefPos = 0;
   pGS->Omkr.sRefLin = UT_FALSE;

   pGS->usOmkretsFerdig = UT_FALSE;

   pGS->Bgr.pFil = NULL;
   pGS->Bgr.lNr  = INGEN_GRUPPE;
}


/*
AR-920930
CH LC_GetRefFlate                        Hent referanser for flate fra GINFO
CD ==========================================================================
CD Formål:
CD Henter ut et array med referanser for flate fra GINFO i aktuell gruppe.
CD
CD Parametre:
CD Type            Navn      I/U  Forklaring
CD -------------------------------------------------------------------------
CD LC_GRF_STATUS *  GrfStat    iu  Struktur med statusopplysninger.
CD unsigned short  usHent     i   Hva skal hentes:
CD                                 GRF_YTRE  = Ytre avgrensing
CD                                 GRF_INDRE = Indre avgrensing, øyer
CD                                     (kan kombineres med | (or).)
CD long           *ref_array  u   GRUPPENUMMER for refererte grupper.
CD unsigned char  *ref_status u   Status for gruppene i ref_array.
CD                                 LC_MED_DIG = Brukes MED dig retning.
CD                                 LC_MOT_DIG  = Brukes MOT dig retning.
CD                                 GRF_START_OY     = Første gruppe i øy
CD                                 GRF_SLUTT_OY     = Siste gruppe i øy
CD long            max_ref    i   Max antall linjer i ref_array og ref_status.
CD long           ant_ref    r   Antall linjer brukt i ref_array.
CD                                0 viser at hele flata er behandla.
CD
CD Bruk:
CD    #define  MAX_REF  20
CD    long ref_arr[MAX_REF];
CD    char ref_status[MAX_REF];
CD    long ant_ref;
CD    LC_GRF_STATUS GrfStat;
CD
CD    LC_InitGetRefFlate(&GrfStat);
CD
CD    ant_ref = LC_GetRefFlate(&GrfStat,GRF_YTRE,ref_arr,ref_status,MAX_REF);
CD    do {
CD       if (ant_ref > 0) {
CD          .
CD          Behandle ytre avgrensing            
CD          .
CD       }
CD
CD       [if (ant_ref < MAX_REF)  break;]
CD
CD       ant_ref = LC_GetRefFlate(&GrfStat,GRF_YTRE,ref_arr,ref_status,MAX_REF);
CD    } while (ant_ref > 0);
CD
CD    LC_InitGetRefFlate(&GrfStat);
CD    ant_ref = LC_GetRefFlate(&GrfStat,GRF_INDRE,ref_arr,ref_status,MAX_REF);
CD    do {
CD       if (ant_ref > 0) {
CD          .
CD          Behandle indre avgrensing (øy)
CD          .
CD       }
CD
CD       [if (ant_ref < MAX_REF)  break;]
CD
CD       ant_ref = LC_GetRefFlate(&GrfStat,GRF_INDRE,ref_arr,ref_status,MAX_REF);
CD    } while (ant_ref > 0);
CD
CD ==========================================================================
*/
SK_EntPnt_FYBA long LC_GetRefFlate(LC_GRF_STATUS * GrfStat,unsigned short usHent,long *ref_array,
                     unsigned char *ref_status,long max_ref)
{
   long antall;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */

      if ((usHent & GRF_YTRE)  &&  GrfStat->usOmkretsFerdig == UT_FALSE) {
         /* Ytre avgrensning */
         antall = LX_GetRefOmkrets(&GrfStat->Omkr,ref_array,ref_status,max_ref);
         if (antall > 0) {
            return antall;
         }

         /* Ferdig med behandling av omkretsen */
         GrfStat->usOmkretsFerdig = UT_TRUE;
      }

      if (usHent & GRF_INDRE) {
         /* Indre avgrensning (øy) */
         return LX_GetRefOy(GrfStat,ref_array,ref_status,max_ref);
      }
   }

   return 0;
}


/*
AR-920930
CH LX_GetRefOmkrets                            Hent referanser for omkretsen
CD ==========================================================================
CD Formål:
CD Henter ut et array med referanser for omkretsen av flate.
CD ant_ref == 0 eller ant_ref < max_ref viser at hele omkretsen er behandla.
CD
CD Parametre:
CD Type            Navn       I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_GR_STATUS   *pGRS       iu   Struktur med statusopplysninger.
CD long           *ref_array   u    GRUPPENUMMER for refererte grupper.
CD unsigned char  *ref_status  u    Status for gruppene i ref_array.
CD                                  LC_MED_DIG = Brukes MED dig retning
CD                                  LC_MOT_DIG  = Brukes MOT dig retning
CD long            max_ref     i    Max antall linjer i ref_array.
CD short           ant_ref     r    Antall linjer brukt i ref_array.
CD
CD Bruk:
CD     ant_ref = LX_GetRefOmkrets(&OmkrStat,ref_array,ref_status,max_ref);
CD ==========================================================================
*/
static long LX_GetRefOmkrets(LC_GR_STATUS *pGRS,long *ref_array,
                              unsigned char *ref_status,long max_ref)
{
   char *gp,ginfo[LC_MAX_SOSI_LINJE_LEN];
   long snr,grnr;
   long ant_ref = 0;


   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */
                                        /* Finn referanser */
      while (pGRS->sGiLinNr <= Sys.pGrInfo->ngi) {
         gp = LX_GetGi(pGRS->sGiLinNr);
         
         /* Handter referanselinjer */
         if ((pGRS->sRefLin = LC_ErLinjeRefLin(gp,pGRS->sRefLin)) == UT_TRUE) {
            UT_StrCopy(ginfo,gp,LC_MAX_SOSI_LINJE_LEN);
            gp = ginfo + pGRS->sRefPos;
            pGRS->sRefPos = 0;
            while (*gp){                  /* Tolk en linje */
               if (ant_ref < max_ref) {
                  if (*gp == ':') {                              /* Tall */
                     ++gp;
                     /* Husk retning */
                     if (*gp == '-') {
                        *ref_status++ = LC_MOT_DIG;
                        ++gp;
                     } else {
                        *ref_status++ = LC_MED_DIG;
                     }
                     /* Hent serienummer og konverter til gruppenummer */
                     if (isdigit(*gp)) {
                        snr = strtol(gp,&gp,10);
                        /* Konverter til gruppenummer */
                        if ((grnr = LI_GetSnr(Sys.GrId.pFil,snr)) != INGEN_GRUPPE) {
                           *ref_array++ = grnr;
                           ++ant_ref;

                        } else {
                           UT_FPRINTF(stderr,"Snr. %ld er referert i \"%s : %s\", finnes ikke!\n",snr,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                           Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                           ref_status--;
                        }

                     } else {
                        UT_FPRINTF(stderr,"Ulovlig referanse \"%s\" i \"%s : %s\"\n",ginfo,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                        Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                        ref_status--;
                     }

                  } else if (*gp == '(') {  /* Start øy, ferdig med omkretsen */
                     pGRS->sRefPos = (short)(gp - ginfo);
                     return  ant_ref;

                  } else {                                    /* Ukjent tegn */
                     ++gp;
                  }

               } else {                                /* Tabellen er full */
                  pGRS->sRefPos = (short)(gp - ginfo);
                  return  ant_ref;
               }
            }
         }
         pGRS->sGiLinNr++;
      }
   }
   return (ant_ref);
}


/*
AR-920930
CH LX_GetRefOy                                      Hent referanser for øyer
CD ==========================================================================
CD Formål:
CD Henter ut et array med referanser for omkretsen av øy.
CD ant_ref == 0 eller ant_ref < max_ref viser at hele omkretsen er behandla.
CD
CD Parametre:
CD Type            Navn       I/U  Forklaring
CD -------------------------------------------------------------------------
CD LC_GRF_STATUS *  pGS        iu  Struktur med statusopplysninger.
CD long           *ref_array   u   GRUPPENUMMER for refererte grupper.
CD unsigned char  *ref_status  u   Status for gruppene i ref_array.
CD                                  LC_MED_DIG = Brukes MED dig retning
CD                                  LC_MOT_DIG  = Brukes MOT dig retning
CD                                  GRF_START_OY     = Første gruppe i øy
CD                                  GRF_SLUTT_OY     = Siste gruppe i øy
CD long            max_ref     i   Max antall linjer i ref_array.
CD short           ant_ref     r   Antall linjer brukt i ref_array.
CD
CD Bruk:
CD     ant_ref = LX_GetRefOy(&GS,ref_array,ref_status,max_ref);
CD ==========================================================================
*/
static long LX_GetRefOy(LC_GRF_STATUS * pGS,long *ref_array,
                         unsigned char *ref_status,long max_ref)
{
   short ngi;
   long nko;
   unsigned short info;
   char *gp,ginfo[LC_MAX_SOSI_LINJE_LEN];
   long snr,grnr,antall;
   unsigned char ucRetning;
   LC_BGR Bgr,GmlBgr;
   long ant_ref = 0;


   Bgr.pFil = Sys.GrId.pFil;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */
      /* Husk aktuell gruppe */
      GmlBgr = Sys.GrId;
      
      /* Les inn resten av påbegynnt refferert flate */
      if (pGS->Bgr.lNr != INGEN_GRUPPE) {
         LC_RxGr(&(pGS->Bgr),LES_OPTIMALT,&ngi,&nko,&info);

         ant_ref = LX_GetRefOmkrets(&(pGS->Oy),ref_array,ref_status,max_ref);
         ref_array  += ant_ref;
         ref_status += ant_ref;

         /* Les inn igjen aktuell gruppe */
         LC_RxGr(&GmlBgr,LES_OPTIMALT,&ngi,&nko,&info);

         if (ant_ref < max_ref) {
            pGS->Bgr.pFil = NULL;
            pGS->Bgr.lNr  = INGEN_GRUPPE;
         }
      }

      /* Finn referanser */
      while (pGS->Omkr.sGiLinNr <= Sys.pGrInfo->ngi) {
         gp = LX_GetGi(pGS->Omkr.sGiLinNr);
         
         /* Handter referanselinjer */
         if ((pGS->Omkr.sRefLin = LC_ErLinjeRefLin(gp,pGS->Omkr.sRefLin)) == UT_TRUE) {
            UT_StrCopy(ginfo,gp,LC_MAX_SOSI_LINJE_LEN);
            gp = ginfo + pGS->Omkr.sRefPos;
            pGS->Omkr.sRefPos = 0;
            while (*gp) {                  /* Tolk en linje */
               if (ant_ref < max_ref) {
                  if (*gp == ':') {                              /* Tall */
                     ++gp;
                     /* Husk retning */
                     if (*gp == '-') {
                        ucRetning = LC_MOT_DIG;
                        ++gp;
                     } else {
                        ucRetning = LC_MED_DIG;
                     }
                     /* Hent serienummer og konverter til gruppenummer */
                     if (isdigit(*gp)) {
                        snr = strtol(gp,&gp,10);
                        /* Konverter til gruppenummer */
                        if ((grnr = LI_GetSnr(Sys.GrId.pFil,snr)) != INGEN_GRUPPE) {
                           Bgr.lNr = grnr;
                           /* Referanse til flate, pakk ut denne */
                           if (LC_GetGrParaBgr(&Bgr,&ngi,&nko,&info)
                                                               == L_FLATE) {
                              LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);

                              pGS->Oy.sGiLinNr = 2;
                              pGS->Oy.sRefPos = 0;
                              pGS->Oy.sRefLin = UT_FALSE;

                              antall = LX_GetRefOmkrets(&(pGS->Oy),ref_array,
                                             ref_status,max_ref-ant_ref);
                              ref_array  += antall;
                              ref_status += antall;
                              ant_ref += antall;

                              /* Les inn igjen aktuell gruppe */
                              LC_RxGr(&GmlBgr,LES_OPTIMALT,&ngi,&nko,&info);

                              if (ant_ref >= max_ref) {
                                 pGS->Bgr = Bgr;
                              } else {
                                 pGS->Bgr.pFil = NULL;
                                 pGS->Bgr.lNr  = INGEN_GRUPPE;
                              }

                           } else {
                              *ref_status++ = ucRetning;
                              *ref_array++ = grnr;
                              ++ant_ref;
                           }

                        } else {
                           UT_FPRINTF(stderr,"Snr. %ld er referert i \"%s : %s\", finnes ikke!\n",snr,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                           Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                        }

                     } else {
                        UT_FPRINTF(stderr,"Ulovlig referanse \"%s\" i \"%s : %s\"\n",ginfo,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                        Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                     }

                  } else if (*gp == '(') {                     /* Start øy */
                     *ref_array++ = INGEN_GRUPPE;
                     *ref_status++ = GRF_START_OY;
                     ++ant_ref;
                     ++gp;

                  } else if (*gp == ')') {                     /* Slutt øy */
                     *ref_array++ = INGEN_GRUPPE;
                     *ref_status++ = GRF_SLUTT_OY;
                     ++ant_ref;
                     ++gp;

                  } else {                                  /* Ukjent tegn */
                     ++gp;
                  }

               } else {                                /* Tabellen er full */
                  pGS->Omkr.sRefPos = (short)(gp - ginfo);
                  return  ant_ref;                /* ==> Retur */
               }
            }
         }
         pGS->Omkr.sGiLinNr++;
      }
   }

   return  ant_ref;
}


/*
AR-921012
CH LC_InqAntRef                                   Spørr om antall referanser
CD ==========================================================================
CD Formål:
CD Spørr om antall referanser i GINFO i aktuell gruppe.
CD Dette kallet kan brukes til å finne hvor stor array som må allokeres før
CD kall til LC_GetRef.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    ant_ref     r    Antall referanser i GINFO.
CD                            OBS! Start- og sluttparantes for øy blir regnet
CD                            som egne referanser.
CD
CD Bruk:
CD     long lAntRef;
CD     short sGiLin,sRefPos;
CD     long *plRefArray;
CD
CD     lAntRef = LC_InqAntRef();
CD     plRefArray = (long *) UT_MALLOC(lAntRef * sizeof(long));
CD     sGiLin = 2;
CD     sRefPos = 0;
CD     LC_GetRef(plRefArray,lAntRef,&sGiLin,&sRefPos);
CD ==========================================================================
*/
SK_EntPnt_FYBA long LC_InqAntRef(void)
{
   char *gp,ginfo[LC_MAX_SOSI_LINJE_LEN];
   long lAntRef = 0;
   short gilin = 2;
   short sRefLin = UT_FALSE;   /* Viser om aktuel linje inneholder referanser */


   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
                                        /* Finn referanser */
      while (gilin <= Sys.pGrInfo->ngi){
         gp = LX_GetGi(gilin);
         
         /* Handter referanselinjer */
         if ((sRefLin = LC_ErLinjeRefLin(gp,sRefLin)) == UT_TRUE) {
            UT_StrCopy(ginfo,gp,LC_MAX_SOSI_LINJE_LEN);
            gp = ginfo;
            while (*gp) {                  /* Tolk en linje */
               if (*gp == ':') {                        /* Tall */
                  ++gp;
                  if (isdigit(*gp) || *gp == '-') {
                     while (*gp  &&  (!UT_IsSpace(*gp)) &&  *gp != ')') {
                        ++gp;
                     }
                     ++lAntRef;
                  } else {
                     UT_FPRINTF(stderr,"Ulovlig referanse \"%s\" i gruppe \"%s : %s\"\n",ginfo,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                     Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                  }

               } else if (*gp == '('  ||  *gp == ')') { /* Start og slutt øy */
                  ++lAntRef;
                  ++gp;

               } else {                                    /* Ukjent tegn */
                  ++gp;
               }
            }
         }
         ++gilin;
      }
   }
   return  lAntRef;
}


/*
AR-900213
OJ-900213
CH LC_GetRef                                        Hent referanser fra GINFO
CD ==========================================================================
CD Formål:
CD Henter ut et array med referanser fra GINFO i aktuell gruppe.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    *ref_array  u    Serienr. for refererte grupper.
CD                          Start øy, og slutt øy angis ved fiktive gruppenr.
CD                          Følgende konstanter er definert:
CD                             START_OY =  9999999L = Start øy.
CD                             SLUTT_OY = -9999999L = Slutt øy.
CD long     max_ref    i    Max antall linjer i ref_array.
CD short   *gilin      i/u  linje for start referanselesing
CD short   *refpos     i/u  posisjon i linja for neste innlegging i array.
CD long     ant_ref    r    Antall linjer brukt i ref_array.
CD
CD Bruk:
CD     ant_ref = LC_GetRef(ref_array,max_ref,&gilin,&refpos);
CD ==========================================================================
*/
SK_EntPnt_FYBA long LC_GetRef(long *ref_array,long max_ref,short *gilin,short *refpos)
{
   char *gp,ginfo[LC_MAX_SOSI_LINJE_LEN];
   long ant_ref = 0;
   short sRefLin = UT_FALSE;   /* Viser om aktuel linje inneholder referanser */


   if (Sys.GrId.lNr != INGEN_GRUPPE){                  /* Aktuell gruppe OK */
                                        /* Finn referanser */
      while (*gilin <= Sys.pGrInfo->ngi){
         gp = LX_GetGi(*gilin);
         
         /* Handter referanselinjer */
         if ((sRefLin = LC_ErLinjeRefLin(gp,sRefLin)) == UT_TRUE) {
            UT_StrCopy(ginfo,gp,LC_MAX_SOSI_LINJE_LEN);
            gp = ginfo + *refpos;
            *refpos = 0;
            while (*gp){                  /* Tolk en linje */
               if (ant_ref < max_ref){
                  if (*gp == ':'){                              /* Tall */
                     ++gp;
                     if (isdigit(*gp) || *gp == '-') {
                        *ref_array++ = strtol(gp,&gp,10);
                        ++ant_ref;
                     } else {
                        UT_FPRINTF(stderr,"Ulovlig referanse \"%s\" i gruppe \"%s : %s\"\n",ginfo,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                        Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                     }

                  } else if (*gp == '('){                       /* Start øy */
                     *ref_array++ = START_OY;
                     ++ant_ref;
                     ++gp;
                  } else if (*gp == ')'){                       /* Slutt øy */
                     *ref_array++ = SLUTT_OY;
                     ++ant_ref;
                     ++gp;
                  } else{                                    /* Ukjent tegn */
                     ++gp;
                  }
               } else{                                 /* Tabellen er full */
                  *refpos = (short)(gp - ginfo);
                  return (ant_ref);
               }
            }
         }
         (*gilin)++;
      }
   }
   return (ant_ref);
}


/*
OJ-901016
AR-930930
CH LC_PutRef                                    Legger inn referanser i GINFO
CD ==========================================================================
CD Formål:
CD Legger inn et array med referanser til GINFO i aktuell gruppe.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long     ref_array  i    Gruppenummer for refererte grupper.
CD                          Start øy, og slutt øy angis ved fiktive gruppenr.
CD                          Følgende konstanter er definert:
CD                             START_OY =  9999999L = Start øy.
CD                             SLUTT_OY = -9999999L = Slutt øy.
CD long     ant_ref    i    Antall linjer i ref_array.
CD short    *ngi       r    Antall linjer GINFO
CD
CD Bruk:
CD     ngi = LC_PutRef(ref_array,ant_ref);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_PutRef(long *ref_array,long ant_ref)
{
   #define MAX_LEN  66   /* Ginfolinjen skrives ut når den er lengre en 66 tegn */
   short gilin;
   long j;
   char temp[LC_MAX_SOSI_LINJE_LEN],*ginfo,*cp;
   short ledig_linje = -1;


   if (Sys.GrId.lNr != INGEN_GRUPPE){                  /* Aktuell gruppe OK */
      /* Pakker gammel GINFO */
      for (gilin=2; gilin <= Sys.pGrInfo->ngi; ++gilin) {
         ginfo = LX_GetGi(gilin);

         /* Gammel type referanse er funnet */
         if (strncmp(ginfo,".. ",3) == 0) {
            if (ledig_linje == -1) {        /* Første linje med referanse */
               ledig_linje = gilin;
            }

         /* Ny type referanse er funnet */
         } else if (strncmp(ginfo,"..REF ",6) == 0) {
            if (ledig_linje == -1) {        /* Første linje med referanse */
               ledig_linje = gilin;
            }
            /* Søk over resten av referansene */
            for (++gilin; gilin <= Sys.pGrInfo->ngi; ++gilin) {
               ginfo = LX_GetGi(gilin);
               if (strncmp(ginfo,"..",2) == 0) { /* Annen GINFO er funnet */
                  gilin--;
                  break;      /* Avbryt, alle referanser er funnet*/
               }
            }

         /* Annen GINFO */
         } else {
            if (ledig_linje != -1) {
                                    /* Funnet linje som skal flyttes opp */
               LC_PutGi(ledig_linje,ginfo);
               ++ledig_linje;
            }
         }
      }

      if (ledig_linje == -1)  ledig_linje = Sys.pGrInfo->ngi + 1;

                              /* Legger inn referanser */
      if (ant_ref > 0) {

         /* Husk at det finnes flate i filen */
         if ( Sys.GrId.pFil->SosiNiv[1] < 4) {
            Sys.GrId.pFil->SosiNiv[1] = 4;
         }

         if (Sys.GrId.pFil->sSosiVer >= 220) {
            UT_StrCopy(temp,"..REF ",LC_MAX_SOSI_LINJE_LEN);
            cp = temp + 6;
         } else {   
            UT_StrCopy(temp,".. ",LC_MAX_SOSI_LINJE_LEN);
            cp = temp + 3;
         }


         j=0;
         while (j < ant_ref) {
            /* Strengen er full, skriver ut */
            if (*ref_array != SLUTT_OY  &&  strlen(temp) > MAX_LEN) {
               if (ledig_linje > Sys.pGrInfo->ngi) {
                  ledig_linje = LC_AppGiL();
               }
               LC_PutGi(ledig_linje,temp);
               ++ledig_linje;

               if (Sys.GrId.pFil->sSosiVer >= 220) {
                  *temp = '\0';
                  cp = temp;
               } else {   
                  UT_StrCopy(temp,".. ",LC_MAX_SOSI_LINJE_LEN);
                  cp = temp + 3;
               }
            }
                                             /* Bygg opp streng */
            if (*ref_array == START_OY) { 
               if (! UT_IsSpace(*(cp-1))) {
                  *cp++ = ' ';
               }
               *cp++ = '(';
               *cp = '\0';

            } else if (*ref_array == SLUTT_OY) {
               if (*(cp-1) == '.') {
                  *cp++ = ' ';
               }
               *cp++ = ')';
               *cp = '\0';

            } else {                                /* Referanse */
               if (! UT_IsSpace(*(cp-1))  &&  *(cp-1) != '(') {
                  *cp++ = ' ';
                  *cp = '\0';
               }
               char szOrd[50];
               UT_SNPRINTF(szOrd,50,":%ld",*ref_array);
               UT_StrCat(temp,szOrd,LC_MAX_SOSI_LINJE_LEN);
               cp = strchr(temp,'\0');
            }

            ++j;
            ++ref_array;
         }

         if (ledig_linje > Sys.pGrInfo->ngi) {          /* Skriver ut strengen */
            ledig_linje = LC_AppGiL();
         }
         LC_PutGi(ledig_linje,temp);
         ++ledig_linje;

      } else {
         Sys.pGrInfo->info &= ~((unsigned short)GI_REF);
         Sys.pGrInfo->info &= ~((unsigned short)GI_OY_REF);
      }

      /* Sletter 1. ledige og resten */
      LC_DelGiL(ledig_linje, (short)(Sys.pGrInfo->ngi - ledig_linje + 1));
   }

   return Sys.pGrInfo->ngi;
}


/*
JEK-920918
CH LC_SirkelTilBuep                        Konverterer en "sirkel" til to BUEP
CD ============================================================================
CD Formål:                                                   fi
CD Konverterer en SIRKEL/SIRKELP til to BUEP.
CD Forutsetter at aktuell gruppe er SIRKEL eller SIRKELP.
CD
CD Parametre:                                               
CD Type     Navn        I/U   Forklaring
CD ----------------------------------------------------------------------------
CD short    buff_retning i    Buffer-retning (kun for BUE og BUEP)
CD                                  HENT_FORRFRA  (1) =  Vanlig
CD                                  HENT_BAKFRA  (-1) =  Buffer skal snues
CD short    *sfeil       u    Feilstatus, definert dersom ist = 0
CD                                    1 = Ulovlig geometritype(ikke bue)
CD                                    2 = Feil ved beregning av bueparametre
CD short    ist          r    Returstatus
CD                                    UT_TRUE  = Alt OK
CD                                    UT_FALSE = Feil, se returvariabel sfeil
CD
CD Bruk:
CD ist = LC_SirkelTilBuep(buff_retning, &as, &ns, &radius, &fi, &dfi, &sfeil )
   ============================================================================
*/
/*
SK_EntPnt_FYBA short LC_SirkelTilBuep(short antDelingspunkt,double a1,double n1,double h1,double a2,double n2,double h2,
                                      short *ngi, long *nko, LC_BGR *pNyBgr)
{
   double as,ns,da,dn,aNy,nNy,r,fi,dfi,dfi2,fiNy;
   short gnavn,ngi;
   long nko;
   unsigned short info;
   double fi1,a_ny=0.0,n_ny=0.0;
   long lGmlSnr,lNyttSnr;
   short sGiLinje;
   short sfeil;


   if (Sys.pGrInfo->gnavn != L_SIRKEL  &&  Sys.pGrInfo->gnavn != L_SIRKELP)
      return UT_FALSE;  // ==>  Ikke sirkel
   
   lGmlSnr = LC_GetSn();
   LC_GetBuePar(LC_MED_DIG,&as,&ns,&r,&fi,&dfi,&sfeil);

   LC_PutGi(1,".BUEP");

   sGiLinje = 2;
   if (LC_GetGP("..RADIUS", &sGiLinje, ngi))  ngi = LC_DelGiL(sGiLinje,1);

   // Sikrer at det er tre koordinater i gruppen
   if (nko > 3)       nko = LC_DelKoL(4,nko-3);
   else if (nko < 3)  nko = LC_InsKoL(nko+1,3-nko);

   // Hvis det er bare ett nytt punkt deles sirkelen i to halvsirkler
   if (antDelingspunkt == 1)
   {
      // Beregner et nytt "fiktivt" punkt på motsatt side av sirkelen   
      da = a1 - as;
      dn = n1 - ns;
      a2 = as - da;
      n2 = ns - dn;
      h2 = HOYDE_MANGLER;

   }
   else if (antDelingspunkt != 2)
   {
      // Ikke gitt noe delingspunkt
      if (Sys.pGrInfo->gnavn == L_SIRKEL)
      {
         a1 = as - r;
         n1 = n2 = ns;
         a2 = as + r;
         h1 = h2 = LC_GetTH(1);
      }
      else  // L_SIRKELP
      {
         LC_GetTK(1,&a1,&n1);
         h1 = LC_GetTH(1);


      }

      a1 = as - r;
      n1 = n2 = ns;
      a2 = as + r;
      h1 = h2 = HOYDE_MANGLER;
   }

   LC_PutTK(1,a1,n1);
   LC_PutKp(1,kpdiv.kpnr);
   if (AntPkt > 1)  LC_PutTH(1,h1);
   GH_DrawMarks(pGA,1,&a1,&n1,FALSE);

   LC_PutTK(3,a2,n2);
   LC_PutKp(3,kpdiv.kpnr);
   if (AntPkt > 1) {
      LC_PutTH(3,h2);
      GH_DrawMarks(pGA,1,&a2,&n2,FALSE);
   }

   // Åpningsvinkel for buen fra P1 til P2
   fi1 = GM_retning(as,ns,a1,n1);
   GM_PktBue(as,ns,fi1,dfi,a2,n2,&dfi2);

   // Beregner et nytt punkt midt på buen fra P1 til P2
   fiNy = fi1 + (dfi2 / 2.0);
   aNy = as + fabs(r)*cos(fiNy);
   nNy = ns + fabs(r)*sin(fiNy);

   // OBS! Bør legge inn sjekk mot at punktet faller sammen med noen av de andre punktene

   LC_PutTK(2,aNy,nNy);
   if (AntPkt > 1) {
      if (h1 != HOYDE_MANGLER  &&  h2 != HOYDE_MANGLER)  LC_PutTH(2,(h1+h2)/2.0);
   }

   LC_WxGr(SKRIV_OPTIMALT);

   // ----- Oppretter og tilpasser den andre delen
   LC_NyGr(pBgr->pFil,".BUEP",&cur.bgr,&lNyttSnr);
   gnavn = LC_CopyGr(pBgr,OPPDATER_NGIS,&ngi,&nko,&info);

   LC_PutTK(1,a2,n2);
   LC_PutKp(1,kpdiv.kpnr);
   if (AntPkt > 1) LC_PutTH(1,h1);

   LC_PutTK(3,a1,n1);
   LC_PutKp(3,kpdiv.kpnr);
   if (AntPkt > 1) LC_PutTH(3,h2);

   // Beregner et nytt punkt på motsatt side av sirkelen av midtpunktet i den andre halvparten av sirkelen  
   da = aNy - as;
   dn = nNy - ns;
   aNy = as - da;
   nNy = ns - dn;

   LC_PutTK(2,aNy,nNy);
   if (AntPkt > 1) {
      if (h1 != HOYDE_MANGLER  &&  h2 != HOYDE_MANGLER)  LC_PutTH(2,(h1+h2)/2.0);
   }

   LC_WxGr(SKRIV_OPTIMALT);

   cur.gnavn = LC_RxGr(&cur.bgr,LES_OPTIMALT,&cur.ngi,&cur.nko,&cur.info);
   TegnGruppe(pGA,T_KOMFIL,VIS_FARGE,1,cur.nko);

   if (Utvalg.bPaa) LC_SetBt(&cur.bgr,UTVALG_1);
   LC_SetBt(&cur.bgr,TMP_TOT_SK);
   LC_SetBt(&cur.bgr,TOT_SK);
   LC_SetBt(&cur.bgr,KLADD1);

   OppdaterReferanser(pBgr->pFil,a1,n1,lGmlSnr,lNyttSnr);

   return UT_TRUE;
}
*/



/*
JEK-920918
CH LC_GetBuePar                    Beregner parametre som definerer sirkelbue
CD ============================================================================
CD Formål:                                                   fi
CD Sirkelbue defineres i SOSI ved en av                     /
CD geometrielementene .SIRKEL, .SIRKELP,                  /
CD .BUE, .BUEP.                                         /       \
CD Denne rutina regner om til en intern        as, ns * -radius- )  dfi
CD bueangivelse med sirkelsentrum, radius               \       /
CD og retning til buens startpunkt samt                   \
CD delta for sluttpunktet uansett hvordan                   \
CD buen er definert i SOSI.
CD
CD NB! Alle retninger i radianer, 0-retning i øst-aksen og positiv
CD omløpsretning mot urviseren.
CD
CD Parametre:                                               
CD Type     Navn        I/U   Forklaring
CD ----------------------------------------------------------------------------
CD short    buff_retning i    Buffer-retning (kun for BUE og BUEP)
CD                                  HENT_FORRFRA  (1) =  Vanlig
CD                                  HENT_BAKFRA  (-1) =  Buffer skal snues
CD double   *as          u    Øst-koordinat sentrum sirkelbue
CD double   *an          u    Nord-koordinat sentrum sirkelbue
CD double   *radius      u    Radius i sirkelbue.
CD double   *fi          u    Retningsvinkel sentrum -> startpunkt bue
CD double   *dfi         u    Vinkel mellom fi og sentrum -> sluttpunkt bue
CD                            dfi > 0  = Positiv omløpsretning(mot klokka)
CD                            dfi < 0  = Negativ omløpsretning(med klokka)
CD short    *sfeil       u    Feilstatus, definert dersom ist = 0
CD                                    1 = Ulovlig geometritype(ikke bue)
CD                                    2 = Feil ved beregning av bueparametre
CD short    ist          r    Returstatus
CD                                    UT_TRUE  = Alt OK
CD                                    UT_FALSE = Feil, se returvariabel sfeil
CD
CD Bruk:
CD ist = LC_GetBuePar(buff_retning, &as, &ns, &radius, &fi, &dfi, &sfeil )
   ============================================================================
*/
SK_EntPnt_FYBA short LC_GetBuePar(short buff_retning, double *as, double *ns, double *radius,
                   double *fi, double *dfi, short *sfeil)
{
   short ist;
   short storbue;
   double a,n,a2,n2,a3,n3;


   *sfeil = 0;
   ist = UT_FALSE;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {              /* Aktuell gruppe OK */
      /* ----- Sjekker geometritype og henter parametre for buen */

      if (Sys.pGrInfo->gnavn == L_BUE) {                 /* .BUE */
         if (LC_GetBue(buff_retning,&a,&n,&a2,&n2,&(*radius),&storbue)){
            if (GM_KonvBue(a,n,a2,n2,*radius,storbue,&(*as),&(*ns),&(*fi),&(*dfi))){
               ist = UT_TRUE;
            } else {
               *sfeil=2;
               UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\" - mer enn 2*radius mellom endepunktene\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
               Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
            }
         }

      } else if (Sys.pGrInfo->gnavn == L_BUEP) {         /* .BUEP */
         if (LC_GetBuep(buff_retning,&a,&n,&a2,&n2,&a3,&n3)) {
            if (GM_KonvBuep(a,n,a2,n2,a3,n3,&(*as),&(*ns),&(*radius),&(*fi),&(*dfi))){
               ist = UT_TRUE;
            } else {
               *sfeil = 2;
               UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\" - punktene ligger på rett linje\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
               Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
            }
         }

      } else if (Sys.pGrInfo->gnavn == L_SIRKEL) {       /* .SIRKEL */
         if (LC_GetSirkel(&(*as),&(*ns),&(*radius))) {
            if(GM_KonvSirkel(&(*fi),&(*dfi))) {
               ist = UT_TRUE;
            } else {
               *sfeil = 2;
               UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\"\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
               Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
            }
         }

      } else if (Sys.pGrInfo->gnavn == L_SIRKELP) {      /* .SIRKELP */
         if (LC_GetSirkelp(&a,&n,&a2,&n2,&a3,&n3)) {
            if (GM_KonvSirkelp(a,n,a2,n2,a3,n3,&(*as),&(*ns),&(*radius),&(*fi),&(*dfi))){
               ist = UT_TRUE;
            } else {
               *sfeil = 2;
               UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\"\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
               Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
            }
         }

      } else {             /* Feil geometritype */
         *sfeil = 1;
      }

      if (ist == UT_TRUE) {
         *radius = fabs(*radius);
      }

   } else {             /* Feil geometritype (ingen aktuell gruppe) */
      *sfeil = 1;
   }

   return ist;
}


/*
AR-890824
CH LC_GetBue                                                        Hent bue
CD ==========================================================================
CD Formål:
CD Henter ut nødvendige opplysninger om en bue.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD short   retning     i    Buffer-retning:
CD                                HENT_FORRFRA ( 1) = vanlig,
CD                                HENT_BAKFRA  (-1) = buffer skal snues.
CD double  *a1         u    Koordinat i første punkt
CD double  *n1         u
CD double  *a2         u    Koordinat i siste punkt
CD double  *n2         u
CD double  *radius     u    Radius
CD short   *storbue    u    0=vanlig bue, 1=storbue
CD short    ist        r    status: UT_TRUE = OK,
CD                                  UT_FALSE = feil (Gruppen er ikke OK bue)
CD
CD Bruk:
CD     ist = LC_GetBue(retning,&a1,&n1,&a2,&n2,&radius,&storbue);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetBue(short retning,double *a1,double *n1,double *a2,double *n2,
                double *radius,short *storbue)
{
   short gilin;
   char *gp;
   short ist = UT_FALSE;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */
      if (Sys.pGrInfo->gnavn == L_BUE  &&  Sys.pGrInfo->nko > 1) {
                                         /* Hent koordinater */
         if (retning == HENT_FORRFRA) {
            LC_GetTK(1,a1,n1);
            LC_GetTK(Sys.pGrInfo->nko,a2,n2);
         } else {
            LC_GetTK(Sys.pGrInfo->nko,a1,n1);
            LC_GetTK(1,a2,n2);
         }

                                           /* Finn radius og storbue */
         gilin = 2;
         if ((gp = LC_GetGP("..RADIUS",&gilin,Sys.pGrInfo->ngi)) != NULL) {
            *radius = strtod(gp,&gp);
            if (retning == HENT_BAKFRA)  *radius = - *radius;
            gilin = 2;
            if ((gp = LC_GetGP("..STORBUE",&gilin,Sys.pGrInfo->ngi)) != NULL) {
               *storbue = (short)strtol(gp,&gp,10);
            } else {
               *storbue = 0;
            }
            ist = UT_TRUE;          /* Buen er OK */

         } else {
            UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\" - mangler ..RADIUS\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
            Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
         }

      } else {
         UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\" - for få koordinater\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
         Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
      }                              
   }

   return ist;
}


/*
AR-911029
CH LC_GetBuep                                                      Hent buep
CD ==========================================================================
CD Formål:
CD Henter ut nødvendige opplysninger om en buep.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD short   retning     i    Buffer-retning:
CD                                HENT_FORRFRA ( 1) = vanlig,
CD                                HENT_BAKFRA  (-1) = buffer skal snues.
CD double  *a1         u    Koordinat i første punkt
CD double  *n1         u
CD double  *a2         u    Koordinat i midtre punkt
CD double  *n2         u
CD double  *a3         u    Koordinat i siste punkt
CD double  *n3         u
CD short    ist        r    status: UT_TRUE = OK,
CD                                  UT_FALSE = feil (Gruppen er ikke OK buep)
CD
CD Bruk:
CD     ist = LC_GetBuep(retning,&a1,&n1,&a2,&n2,&a3,&n3);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetBuep(short retning,double *a1,double *n1,double *a2,double *n2,
                 double *a3,double *n3)
{
   short ist = UT_FALSE;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */
      if (Sys.pGrInfo->gnavn == L_BUEP  &&  Sys.pGrInfo->nko > 2) {
                                         /* Hent koordinater */
         LC_GetTK((1+Sys.pGrInfo->nko)/2, a2, n2);
         if (retning == HENT_FORRFRA) {
            LC_GetTK(1,a1,n1);
            LC_GetTK(Sys.pGrInfo->nko,a3,n3);
         } else {
            LC_GetTK(1,a3,n3);
            LC_GetTK(Sys.pGrInfo->nko,a1,n1);
         }

         ist = UT_TRUE;          /* Buen er OK */

      } else {
         UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\" - for få koordinater\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
         Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
      }                              
   }

   return ist;
}


/*
AR-911029
CH LC_GetSirkel                                                  Hent silkel
CD ==========================================================================
CD Formål:
CD Henter ut nødvendige opplysninger om en sirkel.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  *as         u    Koordinat i sentrum
CD double  *ns         u
CD double  *radius     u    Radius
CD short    ist        r    status: UT_TRUE = OK,
CD                                  UT_FALSE = Feil (Gruppen er ikke OK sirkel)
CD
CD Bruk:
CD     ist = LC_GetSirkel(&as,&ns,&radius);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetSirkel(double *as,double *ns,double *radius)
{
   short gilin;
   char *gp;
   short ist = UT_FALSE;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */
      if (Sys.pGrInfo->gnavn == L_SIRKEL  &&  Sys.pGrInfo->nko > 0) {
                                         /* Hent koordinater */
         LC_GetTK(1,as,ns);

         /* Finn radius */
         gilin = 2;
         if ((gp = LC_GetGP("..RADIUS",&gilin,Sys.pGrInfo->ngi)) != NULL) {
            *radius = strtod(gp,&gp);
            ist = UT_TRUE;          /* Sirkelen er OK */

         } else {
            UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\" - mangler ..RADIUS\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
            Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
         }

      } else {
         UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\" - mangler koordinat\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
         Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
      }
   }

   return ist;
}


/*
AR-911029
CH LC_GetSirkelp                                               Hent silkelp
CD ==========================================================================
CD Formål:
CD Henter ut nødvendige opplysninger om en sirkelp.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  *a1         u    Koordinat i P1
CD double  *n1         u
CD double  *a2         u    Koordinat i P2
CD double  *n2         u
CD double  *a3         u    Koordinat i P3
CD double  *n3         u
CD short    ist        r    status: UT_TRUE = OK,
CD                                  UT_FALSE = Feil (Gruppen er ikke OK sirkelp)
CD
CD Bruk:
CD     ist = LC_GetSirkelp(&a1,&n1,&a2,&n2,&a3,&n3);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetSirkelp(double *a1,double *n1,double *a2,double *n2,
                double *a3,double *n3)
{
   short ist = UT_FALSE;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */
      if (Sys.pGrInfo->gnavn == L_SIRKELP  &&  Sys.pGrInfo->nko > 2) {
                                         /* Hent koordinater */
         LC_GetTK(1,a1,n1);
         LC_GetTK((1+Sys.pGrInfo->nko)/2, a2, n2);
         LC_GetTK(Sys.pGrInfo->nko,a3,n3);

         ist = UT_TRUE;          /* Buen er OK */

      } else {
         UT_FPRINTF(stderr,"Ulovlig bue: \"%s : %s\" - for få koordinater\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
         Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_BUE;
      }                              
   }

   return ist;
}


/*
OJ-891126
CH LC_GetCurEnhet                                  Hent enhet på angitt nivå
CD ==========================================================================
CD Formål:
CD Henter ut enhet fra filhode eller GINFO
CD
CD Parametre:
CD Type        Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM * pFil     i    Peker til FilAdm
CD short      *nivaa    iu   angir nivå for henting, returnerer aktuelt nivå
CD                             1 = filhode
CD                             2 = GINFO
CD double     *enhet    u    Aktuell enhet
CD double     *enhet_h  u    Aktuell enhet-H
CD double     *enhet_d  u    Aktuell enhet-D
CD
CD Bruk:
CD     LC_GetCurEnhet(pFil,&nivaa,&enhet,&enhet_h,&enhet_d);
CD ==========================================================================
*/
SK_EntPnt_FYBA void LC_GetCurEnhet(LC_FILADM * pFil,short *nivaa, double *enhet,
                    double *enhet_h, double *enhet_d)
{
   LO_TestFilpeker(pFil,"GetCurEnhet");

   *enhet = pFil->TransPar.dEnhet;
   *enhet_h = pFil->TransPar.dEnhet_h;
   *enhet_d = pFil->TransPar.dEnhet_d;

   /* Enhet fra GINFO */
   if (*nivaa == 2)
   {
      short lin = 2;
      char *para;
      double enhet_temp;

      para = LC_GetGP("..ENHET",&lin,Sys.pGrInfo->ngi);
      if (para == NULL) {
         *nivaa = 1;
      } else {
         UT_AtoD(para,'.',&enhet_temp);
         if (enhet_temp > LC_ACCY)  *enhet = enhet_temp;
      }
 
      lin=2;
      para = LC_GetGP("...ENHET-H",&lin,Sys.pGrInfo->ngi);
      if (para != NULL) {
         UT_AtoD(para,'.',&enhet_temp);
         if (enhet_temp > LC_ACCY)  *enhet_h = enhet_temp;
      }

      lin=2;
      para = LC_GetGP("...ENHET-D",&lin,Sys.pGrInfo->ngi);
      if (para != NULL) {
         UT_AtoD(para,'.',&enhet_temp);
         if (enhet_temp > LC_ACCY)  *enhet_d = enhet_temp;
      }
   }
}


/*
AR-890515
CH LC_UpdateGiEnhet                                  Oppdater ..ENHET i GINFO
CD ==========================================================================
CD Formål:
CD Setter koordinat-enhet for gruppen.
CD Oppdaterer ..ENHET / ..ENHET-H / ..ENHET-D i GINFO.
CD Rutinen handterer selv tildeling eller sletting av GINFO-linje.
CD Hvis verdien er lik filhodets verdi blir det ikke lagt inn verdi i GINFO.
CD Enhet = 0.0 = bruk filhodets enhet, og fører til at det ikke legges inn
CD i GINFO. Eventuell eksisterende linje jgernes.
CD
CD Parametre:
CD Type        Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM * pFil     i    Peker til FilAdm
CD double      enhet    i    Grunnriss-enhet
CD double      enhet_h  i    Høyde-enhet
CD double      enhet_d  i    Dybde-enhet
CD ngi         short    r    Antall GINFO-linjer etter oppdatering
CD
CD Bruk:
CD ngi = LC_UpdateGiEnhet(pFil,enhet,enhet_h,enhet_d);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_UpdateGiEnhet(LC_FILADM *pFil,double enhet,double enhet_h,double enhet_d)
{
   short linje;
   char tx[80];

   LO_TestFilpeker(pFil,"UpdateGiEnhet");

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */

      // ----- ..ENHET
      linje = 2;

       // Ikke spesiell ..ENHET
       if (fabs(enhet - pFil->TransPar.dEnhet) < LC_ACCY  ||  fabs(enhet) < LC_ACCY)
       {
          if (LC_GetGP("..ENHET",&linje,Sys.pGrInfo->ngi) != NULL)
          {
             LC_DelGiL(linje,1);                 /* Funnet, fjern linjen */
          }
       }

       // Spesiell ..ENHET
       else
       {
          if (LC_GetGP("..ENHET",&linje,Sys.pGrInfo->ngi) == NULL)
          {
             linje = LC_AppGiL();         /* Ikke funnet, tildel ny linje */
          }
          LC_PutGi(linje,LB_FormaterEnhet(tx,80,"..ENHET",enhet));
       }

       // ----- ..ENHET-H
       linje = 2;

       // Ikke spesiell ..ENHET-H
       if (fabs(enhet_h - pFil->TransPar.dEnhet_h) < LC_ACCY  ||  fabs(enhet_h) < LC_ACCY)
       {
          if (LC_GetGP("..ENHET-H",&linje,Sys.pGrInfo->ngi) != NULL)
          {
             LC_DelGiL(linje,1);                 /* Funnet, fjern linjen */
          }
       }

       // Spesiell ..ENHET-H
       else
       {
          if (LC_GetGP("..ENHET-H",&linje,Sys.pGrInfo->ngi) == NULL)
          {
             linje = LC_AppGiL();         /* Ikke funnet, tildel ny linje */
          }
          LC_PutGi(linje,LB_FormaterEnhet(tx,80,"..ENHET-H",enhet_h));
       }

       // ----- ..ENHET-D
       linje = 2;

       // Ikke spesiell ..ENHET-D
       if (fabs(enhet_d - pFil->TransPar.dEnhet_d) < LC_ACCY  ||  fabs(enhet_d) < LC_ACCY)
       {
          if (LC_GetGP("..ENHET-D",&linje,Sys.pGrInfo->ngi) != NULL)
          {
             LC_DelGiL(linje,1);                 /* Funnet, fjern linjen */
          }
       }

       // Spesiell ..ENHET-D
       else
       {
          if (LC_GetGP("..ENHET-D",&linje,Sys.pGrInfo->ngi) == NULL)
          {
             linje = LC_AppGiL();         /* Ikke funnet, tildel ny linje */
          }
          LC_PutGi(linje,LB_FormaterEnhet(tx,80,"..ENHET-D",enhet_d));
       }
   }

   return Sys.pGrInfo->ngi;
}


/*
OJ-891123
CH LC_GetKvalitet                               Finner kvalitetsopplysninger
CD ==========================================================================
CD Formål:
CD Finne kvalitetsopplysninger i filhode eller vanlig gruppe.
CD (Tolker aktuell gruppe.)
CD
CD Parametre:
CD Type     Navn       I/U   Forklaring
CD --------------------------------------------------------------------------
CD short  *psMetode           u  Hvordan data er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD                                 KVAL_MET_STD    standard metode fra nivå over.
CD long   *pLNnoyaktighet     u  Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT nøyaktighet er ukjent.
CD                                 KVAL_NOY_STD    standard nøyaktighet fra nivå over
CD short  *psSynbarhet        u  Synbarhet i bilde
CD                                 KVAL_SYN_UNDEF  synbarhet er udefinert.
CD                                 KVAL_SYN_STD    standard metode fra nivå over.
CD short  *psHoydeMetode      u  Hvordan høyden er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD                                 KVAL_MET_STD    standard metode fra nivå over.
CD long   *plHoydeNoyaktighet u  Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT nøyaktighet er ukjent.
CD                                 KVAL_NOY_STD    standard nøyaktighet fra nivå over
CD short    ist               r  Status: UT_TRUE  = OK, ..KVALITET er funnet
CD                                       UT_FALSE = ikke funnet
CD
CD Bruk:
CD      ist = LC_GetKvalitet(&sMetode,&lNoyaktighet,&sSynbarhet,
CD                           &sHoydeMetode,&lHoydeNoyaktighet);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetKvalitet(short *psMetode,long *plNoyaktighet,short *psSynbarhet,
                     short *psHoydeMetode,long *plHoydeNoyaktighet)
{
   short lin;
   char *cp;
   short ist = UT_FALSE;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {            /* Aktuell gruppe OK */
       lin=2;
       /* Søk i GINFO */
       if ((cp = LC_GetGP("..KVALITET",&lin,Sys.pGrInfo->ngi)) != NULL) {
           ist = UT_TRUE;
       }

       LN_TolkKvalitet(cp,psMetode,plNoyaktighet,psSynbarhet,
                       psHoydeMetode,plHoydeNoyaktighet);
   }

   return ist;
}


/*
OJ-900103
CH LC_GetCurKvalitet             Finner kvalitetsopplysninger på angitt nivå
CD ==========================================================================
CD Formål:
CD Finne kvalitetsopplysninger på angitt nivå, hode ginfo eller pinfo.
CD
CD Parametre:
CD Type        Navn          I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM * pFil           i   Peker til FilAdm
CD short      *nivaa         iu   Hvor skal det letes.
CD                                 0 = ikke funnet
CD                                 1 = hode
CD                                 2 = ginfo
CD                                 3 = pinfo
CD                                 Returnerer aktuelt nivå.
CD long        pnr            i    punktnr. ved spørring på pinfo
CD short  *psMetode           u   Hvordan data er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD long   *pLNnoyaktighet     u   Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT nøyaktighet er ukjent.
CD short  *psSynbarhet        u   Synbarhet i bilde
CD                                 KVAL_SYN_UNDEF  synbarhet er udefinert.
CD short  *psHoydeMetode      u   Hvordan høyden er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD long   *plHoydeNoyaktighet u   Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT nøyaktighet er ukjent.
CD short   ist                r   Statusvariabel:
CD                                 UT_TRUE = OK, KVALITET er funnet
CD                                 UT_FALSE = KVALITET er ikke funnet
CD
CD Bruk:
CD  ist = LC_GetCurKvalitet(pFil,&nivaa,pnr,&sMetode,&lNoyaktighet,
CD                          &sSynbarhet,&sHoydeMetode,&lHoydeNoyaktighet);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetCurKvalitet(LC_FILADM *pFil,short *nivaa,long pnr,
                        short *psMetode,long *plNoyaktighet,short *psSynbarhet,
                        short *psHoydeMetode,long *plHoydeNoyaktighet)
{
   short lin;
   char *cp;
   short sMetode, sHoydeMetode, sSynbarhet;
   long lNoyaktighet, lHoydeNoyaktighet;
   LC_GETPP_STATUS  pp_stat;
   short sFunnetNivaa = 0;

   short sStatus = UT_FALSE;

   LO_TestFilpeker(pFil,"GetCurKvalitet");

   if (Sys.GrId.lNr != INGEN_GRUPPE) {         /* Aktuell gruppe OK */

      *psMetode           = KVAL_MET_STD;
      *plNoyaktighet      = KVAL_NOY_STD;
      *psSynbarhet        = KVAL_SYN_STD;
      *psHoydeMetode      = KVAL_MET_STD;
      *plHoydeNoyaktighet = KVAL_NOY_STD;


      /* Søk i PINFO */
      if (*nivaa == 3) {
         LC_InitPP("...KVALITET",pnr,pnr,&pp_stat);
         if ((cp = LC_GetPP(&pnr,&pp_stat)) != NULL) {
            LN_TolkKvalitet(cp,psMetode,plNoyaktighet,psSynbarhet,
                            psHoydeMetode,plHoydeNoyaktighet);
            sStatus = UT_TRUE;
            sFunnetNivaa = 3;
         }
      }

      /* Søk i GINFO */
      if (*nivaa >= 2) {
         lin=2;
         if ((cp = LC_GetGP("..KVALITET",&lin,Sys.pGrInfo->ngi)) != NULL){       /* Kvalitet */
            LN_TolkKvalitet(cp,&sMetode,&lNoyaktighet,&sSynbarhet,
                            &sHoydeMetode,&lHoydeNoyaktighet);

            /* Oppdater med kvalitet fra GINFO */
            if (*psMetode == KVAL_MET_STD)  *psMetode = sMetode;
            if (*plNoyaktighet == KVAL_NOY_STD)  *plNoyaktighet = lNoyaktighet;
            if (*psSynbarhet == KVAL_SYN_STD)  *psSynbarhet = sSynbarhet;
            if (*psHoydeMetode == KVAL_MET_STD)  *psHoydeMetode = sHoydeMetode;
            if (*plHoydeNoyaktighet == KVAL_NOY_STD)  *plHoydeNoyaktighet = lHoydeNoyaktighet;

            sStatus = UT_TRUE;
            if (sFunnetNivaa == 0)  sFunnetNivaa = 2;
         }
      }

      /* Hent fra hodet */
      /* Oppdater med kvalitet fra HODE */
      if (*psMetode == KVAL_MET_STD)  *psMetode = pFil->Kvalitet.sMetode;
      if (*plNoyaktighet == KVAL_NOY_STD)  *plNoyaktighet = pFil->Kvalitet.lNoyaktighet;
      if (*psSynbarhet == KVAL_SYN_STD)  *psSynbarhet = pFil->Kvalitet.sSynbarhet;
      if (*psHoydeMetode == KVAL_MET_STD)  *psHoydeMetode = pFil->Kvalitet.sHoydeMetode;
      if (*plHoydeNoyaktighet == KVAL_NOY_STD)  *plHoydeNoyaktighet = pFil->Kvalitet.lHoydeNoyaktighet;

      /* Handter eventuell standardverdi */
      if (*psMetode == KVAL_MET_STD)  *psMetode = KVAL_MET_UNDEF;
      if (*plNoyaktighet == KVAL_NOY_STD)  *plNoyaktighet = KVAL_NOY_UKJENT;
      if (*psSynbarhet == KVAL_SYN_STD)  *psSynbarhet = KVAL_SYN_GOD;
      if (*psHoydeMetode == KVAL_MET_STD)  *psHoydeMetode = KVAL_MET_UNDEF;
      if (*plHoydeNoyaktighet == KVAL_NOY_STD)  *plHoydeNoyaktighet = KVAL_NOY_UKJENT;

      if (*psMetode           != KVAL_MET_UNDEF  ||
          *plNoyaktighet      != KVAL_NOY_UKJENT ||
          *psSynbarhet        != KVAL_SYN_GOD    ||
          *psHoydeMetode      != KVAL_MET_UNDEF  ||
          *plHoydeNoyaktighet != KVAL_NOY_UKJENT ) {

          sStatus = UT_TRUE;
         if (sFunnetNivaa == 0)  sFunnetNivaa = 1;
      }
   }  

   *nivaa = sFunnetNivaa;

   return sStatus;
}


/*
CH OJ-891205
CH LC_UpdateGiKvalitet                         Oppdaterer ..KVALITET i Ginfo
CD ==========================================================================
CD Formål:
CD Oppdaterer GINFO med ..KVALITET
CD
CD Parametre:
CD Type       Navn            I/U  Forklaring
CD --------------------------------------------------------------------------
CD Parametre:
CD LC_FILADM *pFil              i  Peker til FilAdm for sosifil kvalitet skal
CD                                 testes mot.
CD short      sMetode           i  Metode i ..KVALITET
CD long       lNoyaktighet      i  Nøyaktighet i ..KVALITET
CD short      sSynbarhet        i  Synbarhet i ..KVALITET
CD short      sHoydeMetode      i  HøydeMetode i ..KVALITET
CD long       lHoydeNoyaktighet i  HøydeNøyaktighet i ..KVALITET
CD short      ngi               r  Antall linjer i ginfo.
CD
CD Bruk:
CD      ngi = LC_UpdateGiKvalitet(pFil,sMetode,lNoyaktighet,sSynbarhet,
CD                                sHoydeMetode,lHoydeNoyaktighet);
CD
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_UpdateGiKvalitet(LC_FILADM *pFil,short sMetode,long lNoyaktighet,
                          short sSynbarhet,short sHoydeMetode,long lHoydeNoyaktighet)
{
   // Endret slik at ..KVALITET blir skrevet ut til gruppen bare hvis den er
   // forskjellig fra kvalitet i filhodet.
   // Fjerner aldri eksisterende kvalitet fra GINFO.

   short ho_metode,ho_hmetode,ho_synbarhet;
   long  ho_noyaktighet,ho_hnoyaktighet;
   short linje_nr,nivaa;
   short pnr = 1;
   short ngi = Sys.pGrInfo->ngi;


   LO_TestFilpeker(pFil,"UpdateGiKvalitet");

   // Hent kvalitet fra hode
   nivaa = 1;
   LC_GetCurKvalitet(pFil,&nivaa,pnr,&ho_metode,&ho_noyaktighet,
                     &ho_synbarhet,&ho_hmetode,&ho_hnoyaktighet);

   // Hvis ulik kvalitet i gruppen og filhodet
   if ((sMetode != ho_metode) ||
       (lNoyaktighet != ho_noyaktighet) ||
       (sSynbarhet != ho_synbarhet) ||
       (sHoydeMetode != ho_hmetode) ||
       (lHoydeNoyaktighet != ho_hnoyaktighet))
   {
      // Formatterer strengen og oppdater GINFO
      ngi = LC_PutGP("..KVALITET",
                     LC_FormatterKvalitet(sMetode,lNoyaktighet,sSynbarhet,
                                          sHoydeMetode,lHoydeNoyaktighet),&linje_nr);
   }

   //else
   //{
   //   // Samme kvalitet som i filhodet, fjern eventuell GI-linje
   //   linje_nr = 2;
   //   if (LC_GetGP("..KVALITET",&linje_nr,ngi) != NULL) {
   //      ngi = LC_DelGiL(linje_nr,1);
   //   }
   //}

   return Sys.pGrInfo->ngi;
}


/*
OJ-891208
AR-920312
CH LC_UpdatePiKvalitet                        Oppdaterer ...KVALITET i Pinfo
CD ==========================================================================
CD Formål:
CD Oppdaterer PINFO med ...KVALITET
CD
CD Parametre:
CD Type        Navn             I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM * pFil              i  Peker til FilAdm for sosifil kvalitet
CD                                  skal testes mot.
CD long        pnr               i  Punktnummer som skal oppdateres.
CD short       sMetode           i  Metode i ..KVALITET
CD long        lNoyaktighet      i  Nøyaktighet i ..KVALITET
CD short       sSynbarhet        i  Synbarhet i ..KVALITET
CD short       sHoydeMetode      i  HøydeMetode i ..KVALITET
CD long        lHoydeNoyaktighet i  HøydeNøyaktighet i ..KVALITET
CD short       sStatus           r  UT_TRUE = OK,
CD                                  UT_FALSE = ikke utført (for lite plass tilgjengelig)
CD
CD Bruk:
CD sStatus = LC_UpdatePiKvalitet(pFil,pnr,sMetode,lNoyaktighet,sSynbarhet,
CD                               sHoydeMetode,lHoydeNoyaktighet)
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_UpdatePiKvalitet(LC_FILADM *pFil,long pnr,short sMetode,long lNoyaktighet,
                          short sSynbarhet,short sHoydeMetode,long lHoydeNoyaktighet)
{
   char  temp[LC_MAX_SOSI_LINJE_LEN],*pp,*neste,*cp;
   short nivaa;
   short gi_metode,gi_hmetode,gi_synbarhet;
   long  gi_noyaktighet,gi_hnoyaktighet;

   LO_TestFilpeker(pFil,"UpdatePiKvalitet");

   if (Sys.GrId.lNr != INGEN_GRUPPE) {            /* Aktuell gruppe OK */

      /* Fjern eksisterende KVALITET fra PINFO */
      pp = LC_GetPi(pnr);
      if ((neste = strstr(pp,"...KVALITET")) != NULL) {    /* Finn SOSI-navnet */
         cp = neste - 1;                    /* Avslutt første del av pinfo */
         while (UT_IsSpace(*cp) && cp >= pp) {
            cp--;
         }
         *(cp+1) = '\0';
         UT_StrCopy(temp,pp,LC_MAX_SOSI_LINJE_LEN);

         /* Hopp over KVALITETen */
         if ((cp = strstr(neste+3,"...")) != NULL) {   /* Neste SOSI-navn */
            /* Heng på resten av den gamle PINFOen */
            if (*temp)  UT_StrCat(temp," ",LC_MAX_SOSI_LINJE_LEN);
            UT_StrCat(temp,cp,LC_MAX_SOSI_LINJE_LEN);
         }

      /* KVALITET er ikke funnet, ta vare på hele strengen */
      } else {
         UT_StrCopy(temp,pp,LC_MAX_SOSI_LINJE_LEN);
      }

      /* Hent kvalitet fra ginfo/hode */
      nivaa = 2;
      LC_GetCurKvalitet(pFil,&nivaa,pnr,&gi_metode,&gi_noyaktighet,
                        &gi_synbarhet,&gi_hmetode,&gi_hnoyaktighet);

      /* Hvis Kvaliteten avviker fra ginfo/hode, heng den på PINFO */                                          /* Legg inn endringen */
      if (sMetode != gi_metode  ||
          lNoyaktighet != gi_noyaktighet  ||
          sSynbarhet != gi_synbarhet  ||
          sHoydeMetode != gi_hmetode  ||
          lHoydeNoyaktighet != gi_hnoyaktighet ) {

         if (*temp)  UT_StrCat(temp," ",LC_MAX_SOSI_LINJE_LEN);
         UT_StrCat(temp,"...KVALITET ",LC_MAX_SOSI_LINJE_LEN);
         UT_StrCat(temp,LC_FormatterKvalitet(sMetode,lNoyaktighet,sSynbarhet,sHoydeMetode,lHoydeNoyaktighet),
                   LC_MAX_SOSI_LINJE_LEN);
      }

      if(strlen(temp) > LC_MAX_SOSI_LINJE_LEN) {
         LC_Error(131,"(LC_UpdatePiKvalitet)",temp);
      }

      /* Lagre strengen */
      return LC_PutPi(pnr,temp);
   }

   return UT_FALSE;
}


/*
AR-930609
CH LC_GetGP                                               Get GINFO-parameter
CD ==========================================================================
CD Formål:
CD Henter parametrene til et SOSI-navn.
CD Strengen ligger i et felles "returbuffer" for alle get-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "get-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk UT_StrCopy).
CD
CD Leddnummer, delstreng,skilletegn og formateringskode kan inngå som
CD forlengelse av SOSI-navnet.
CD
CD Leddnummer for flerleddet parameter angis ved #n.
CD Eks: ..GID#2 er bruksnummer.
CD
CD Delstreng angis ved: [start:slutt].
CD NB! 1 er første tegn.
CD Sluttposisjon 0 betyr at resten av strengen skal brukes.      
CD Eks: ..STRENG[2:0]  Posisjon 2 og resten av strengen.
CD
CD Skilletegn for flerleddet GINFO. Dette angis ved ^x hvor x er det tegnet
CD som skal skrives ut mellom leddene.
CD
CD Formateringskode. Dette brukes for å angi plassering av komma og antall
CD desimaler i desimaltall.
CD Eks: ..AREAL%-3.2    Betyr at ..AREAL fra GINFO skal formateres slik:
CD Komma flyttes 3 posisjoner til venstre (divisjon med tusen) og resultatet
CD presenteres avrundet til 2 desimaler.
CD
CD Eks: ..DYBDE£-1.2    Betyr at ..DYBDE fra GINFO skal formateres slik:
CD Komma flyttes 1 posisjon til venstre (divisjon med ti) og resultatet
CD presenteres med 2 desimaler uten avrunding. Spesielt for dybdeverdier.
CD
CD Disse tilleggene kan kombineres, slik at  ..GID#2[1:2] betyr at det er
CD tegn nummer 1 og 2 i det andre leddet (bruksnumret) som skal brukes.
CD
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD char     sosi_navn    i    SOSI-navn det skal finnes verdi til.
CD                            Leddnummer, posisjon, skilletegn
CD                            og formateringskode kan inngå
CD                            som forlengelse av navnet.
CD                            OBS! Store og små bokstaver er signifikante.
CD
CD short   *forste_linje iu   GINFO-linjenummer for start søking
CD                            (1 er første linje i GINFO.)
CD                            Ved tilslag returneres linjenummer for tilslaget.
CD short    siste_linje  i    Siste GINFO-linje det skal søkes i.
CD char    *para_peker   r    Peker til parameter-streng avslutta med '\0'.
CD                            Hvis SOSI-navnet ikke er funnet returneres NULL.
CD
CD Bruk:
CD para_peker = LC_GetGP(sosi_navn,&forste_linje,siste_linje);
   ==========================================================================
*/
SK_EntPnt_FYBA char *LC_GetGP(const char *sosi_navn,short *forste_linje,short siste_linje)
{
   short gi_lin,sAntallBlank,sSosiLen,sFortegn,s;
   char *ginfo,*cp,*nt,*cs,szSosiNavn[LC_MAX_SOSINAVN_LEN];
   double d;
   char cSkilleTegn = '\0';
   short sLedd = 0;
   short sStart = 0;
   short sSlutt = 0;
   short funnet = 0;
   short sFormater = UT_FALSE;
   short sFlyttKomma = 0; /* Flytting av komma ( <0 flytt til venstre) */
   short sAntDes = 2;     /* Antall desimaler */

   char *rp = NULL;          /* Retur peker */

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
      /* Sjekk at det er lovlige linjenummer */
      if (*forste_linje < 1)        *forste_linje = 1;
      if (siste_linje > Sys.pGrInfo->ngi)  siste_linje   = Sys.pGrInfo->ngi;

      /* Plukk ut info om ledd, delstreng og formatering */
      UT_StrCopy(szSosiNavn,sosi_navn,LC_MAX_SOSINAVN_LEN);
      UT_StrUpper(szSosiNavn);

      if ((cs = strpbrk(szSosiNavn,"#[^%£")) != NULL) {
         cp = cs;
         while (*cp != '\0') {
            if (*cp == '#') {
               ++cp;
               sLedd = (short) strtol(cp,&cp,10);       /* Ledd-nummer */
            } else if (*cp == '^') {
               ++cp;
               cSkilleTegn = *cp;                       /* Skilletegn */
               ++cp;
            } else if (*cp == '[') {
               ++cp;
               sStart = (short) strtol(cp,&cp,10);      /* Startposisjon */
               ++cp;
               sSlutt = (short) strtol(cp,&cp,10);      /* Sluttposisjon */
            } else if ((*cp == '%') || (*cp == '£')) {
               if(*cp == '£')
                  sFormater = 2;
               else
                  sFormater = UT_TRUE;
               ++cp;
               if (*cp == '-') {
                  sFortegn = -1;
                  ++cp;
               } else {
                  sFortegn = 1;
               }
               if (isdigit(*cp)) sFlyttKomma = (short) strtol(cp,&cp,10); /* Flytting av komma */
               sFlyttKomma *= sFortegn;                
               if (*cp == '.')  ++cp;
               if (isdigit(*cp)) sAntDes = (short) strtol(cp,&cp,10); /* Ant. des */
            } else {
               ++cp;
            }
         }
         /* Fjern tilleggsinfo fra SOSI-navnet */
         *cs = '\0';
      }

      /* Søk etter SOSI-navnet */
      sSosiLen = (short)strlen(szSosiNavn);
      gi_lin = *forste_linje;
      while (gi_lin <= siste_linje) {
         /* Les ny linje */
         ginfo = LX_GetGi(gi_lin);

         /* Er dette rett navn? */
         if ((strncmp(ginfo,szSosiNavn,sSosiLen) == 0) &&
             ( (UT_IsSpace(*(ginfo+sSosiLen))  ||  *(ginfo+sSosiLen) == '\0'))) {

            /* Hopp over blanke mellom navn og verdi */
            cp = ginfo + sSosiLen;
            while (UT_IsSpace(*cp)) {
               ++cp;
            }
            // Kopier parameter
            UT_StrCopy(retur_str,cp,LC_MAX_SOSI_LINJE_LEN);
            rp = retur_str;

            // Har ikke ledd , funnet OK
            if (sLedd == 0) {

               
               //Fjerner hermetegn " eller ' foran
               while (*rp == '"' || *rp == '\'')
                  ++rp;

               //Finner enden av strengen
               cp = strchr(rp+1,'\0');

               //Går framover fra enden og fjerner anførselstegn
               while (cp-- && (*cp == '"' || *cp == '\'') && cp != NULL)
                  *cp = '\0';

               funnet = 1;
               // Husk linjenummeret
               *forste_linje = gi_lin;
               break;           // Funnet, ==> hopp ut av løkken

            // Handter leddnummer
            } else {
               s = sLedd;
               cs = rp+strlen(rp); // Markerer slutten av parameterstrengen
               while(s > 0) {
                  if(s-- == sLedd) {  // Første ledd leses
                     cp = UT_strtok(rp," ",&nt);
                  }
                  else {            // Neste ledd leses
                     cp = UT_strtok(NULL," ",&nt);
                  }
                  if (cp != NULL) {
                     // Test på hermetegn
                     if (*cp == '"') {
                        if((cp+strlen(cp)) != cs)  { // Dersom ikke slutten av parameterstrengen
                           *(cp+strlen(cp)) = ' ';  // Setter tilbake space for NULL
                        }
                        rp = cp+1;              // Unngår start-hermetegnet
                        cp = UT_strtok(rp,"\"",&nt);   // Leser til slutt-hermetegnet eller \0
                     }  
                     else if (*cp == '\'') {
                        if((cp+strlen(cp)) != cs)  { // Dersom ikke slutten av parameterstrengen
                           *(cp+strlen(cp)) = ' ';  // Setter tilbake space for NULL
                        }
                        rp = cp+1;              // Unngår start-hermetegnet
                        cp = UT_strtok(rp,"'",&nt);    // Leser til slutt-hermetegnet eller \0
                     }
                  }
                  else { // cp == NULL
                     break;
                  }
               }

               /* Leddet er funnet */
               if (cp != NULL) {
                  /* Aktuelt ledd huskes */
                  rp = cp;
                  funnet = 1;
                  /* Husk linjenummeret */
                  *forste_linje = gi_lin;
                  break;           /* Funnet, ==> hopp ut av løkken */
               
               } else {
                                    /* AR-950901 */
                  /* rp = NULL; */  /* Det aktuelle leddet finnes ikke */
                  /* Aktuellt ledd huskes */
                  rp = strchr(rp,'\0');
                  funnet = 1;
                  /* Husk linjenummeret */
                  *forste_linje = gi_lin;
                  break;           /* Funnet, ==> hopp ut av l›kken */
               }
            }
         }

         ++gi_lin;
      }

      /* Spesialnavn */
      if ( ! funnet  &&  (*szSosiNavn != '.'  &&  ((*forste_linje <= siste_linje) || (siste_linje == 1)))) {
         /* Handter AREAL spesielt*/
         if (strcmp(szSosiNavn,"AREAL") == 0) {
            d = LC_BerAreal();
            d *= pow((double)10.0,(int)sFlyttKomma);
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%.*f",sAntDes,d);
            *forste_linje = siste_linje + 1;
            rp = retur_str;
            sFormater = UT_FALSE;     /* Formatering er utført */

         /* Handter LENGDE spesielt */
         } else if (strcmp(szSosiNavn,"LENGDE") == 0) {
            if ( ! LC_BerLengde3D(&d)){
               d = LC_BerLengde();
            }
            d *= pow((double)10.0,(int)sFlyttKomma);
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%.*f",sAntDes,d);
            *forste_linje = siste_linje + 1;
            rp = retur_str;
            sFormater = UT_FALSE;     /* Formatering er utført */
            
         /* Handter LENGDE_HORISONTAL spesielt */
         } else if (strcmp(szSosiNavn,"LENGDE_HORISONTAL") == 0) {
            d = LC_BerLengde();
            d *= pow((double)10.0,(int)sFlyttKomma);
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%.*f",sAntDes,d);
            *forste_linje = siste_linje + 1;
            rp = retur_str;
            sFormater = UT_FALSE;     /* Formatering er utført */

         /* Handter LENGDE_AVGRENS spesielt */
         } else if (strcmp(szSosiNavn,"LENGDE_AVGRENS") == 0) {
            d = LC_BerAvgrensLengde();
            d *= pow((double)10.0,(int)sFlyttKomma);
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%.*f",sAntDes,d);
            *forste_linje = siste_linje + 1;
            rp = retur_str;
            sFormater = UT_FALSE;     /* Formatering er utført */

         /* Handter LENGDE_YTRE_AVGRENS spesielt */
         } else if (strcmp(szSosiNavn,"LENGDE_YTRE_AVGRENS") == 0) {
            d = LC_BerYtreAvgrensLengde();
            d *= pow((double)10.0,(int)sFlyttKomma);
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%.*f",sAntDes,d);
            *forste_linje = siste_linje + 1;
            rp = retur_str;
            sFormater = UT_FALSE;     /* Formatering er utført */

         /* Handter LENGDE_INDRE_AVGRENS spesielt */
         } else if (strcmp(szSosiNavn,"LENGDE_INDRE_AVGRENS") == 0) {
            d = LC_BerIndreAvgrensLengde();
            d *= pow((double)10.0,(int)sFlyttKomma);
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%.*f",sAntDes,d);
            *forste_linje = siste_linje + 1;
            rp = retur_str;
            sFormater = UT_FALSE;     /* Formatering er utført */

         /* Handter SNR spesielt */
         } else if (strcmp(szSosiNavn,"SNR") == 0) {
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%ld",LC_GetSn());
            *forste_linje = siste_linje + 1;
            rp = retur_str;

         /* Handter NPT spesielt */
         } else if (strcmp(szSosiNavn,"NPT") == 0) {
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%ld", Sys.pGrInfo->nko);
            *forste_linje = siste_linje + 1;
            rp = retur_str;

         // Handter REF_FRA spesielt (referert fra antall grupper)
         } else if (strcmp(szSosiNavn,"REF_FRA") == 0) {
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%ld", LC_ErReferertFraAntall());
            rp = retur_str;

         // Handter NPT_REF spesielt antall punkt referert
         } else if (strcmp(szSosiNavn,"NPT_REF") == 0) {

            if(Sys.pGrInfo->info & GI_REF)
            {                
               // Gruppen har referanser
               short ngi;
               long nko;
               unsigned short info;
               LC_POLYGON Polygon;
               LC_POL_ELEMENT * pPE;
               LC_OY_ELEMENT * pOE;
               long lSumNko = 0;

               LC_POL_InitPolygon(&Polygon);
               LC_POL_GetRef(&Polygon);

               // Ytre avgrensning
               for(pPE = Polygon.HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
                  LC_GetGrParaBgr(&pPE->Bgr,&ngi,&nko,&info);
                  lSumNko += nko;
               }

               // Indre avgrensning
               for (pOE = Polygon.OyOA.pForsteOE; pOE != NULL; pOE = pOE->pNesteOE) {
                for (pPE = pOE->PO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
                   LC_GetGrParaBgr(&pPE->Bgr,&ngi,&nko,&info);
                   lSumNko += nko;
                }
               }

               // Frigi allokerte kjeder
               LC_POL_FrigiPolygon(&Polygon);

               //Lag returstrengen
               UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%ld", lSumNko);
            }

            else
            {
               // Har ikke referanser
               UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%hd", 0);
            }

            *forste_linje = siste_linje + 1;
            rp = retur_str;


         /* Handter KVALITET spesielt */
         } else if (strcmp(szSosiNavn,"KVALITET") == 0) {
            short sMetode, sSynbarhet, sHoydeMetode;
            long lNoyaktighet, lHoydeNoyaktighet;
            short nivaa = 2;
            /* Funnet kvalitet? */
            if (LC_GetCurKvalitet(Sys.GrId.pFil,&nivaa,1,
                                  &sMetode,&lNoyaktighet,&sSynbarhet,
                                  &sHoydeMetode,&lHoydeNoyaktighet) == UT_TRUE) {
               /* Formater kvaliteten */
               UT_StrCopy(retur_str,
                          LC_FormatterKvalitet(sMetode,lNoyaktighet,sSynbarhet,sHoydeMetode,lHoydeNoyaktighet),
                          LC_MAX_SOSI_LINJE_LEN);
               rp = retur_str;
            }
            *forste_linje = siste_linje + 1;
         }
      }

      /* Har funnet navnet */
      //if (rp != NULL) {
      if ((rp != NULL) && (*rp != '\0')) { //22.11.2007 AR/ÅE Stopper tom variabel som har adresse
         /* Handter delstreng */
         if (sStart != 0) {
            if (sSlutt != 0  &&  sSlutt < (short)strlen(rp)) {
               *(rp+sSlutt) = '\0';
            }
            sStart = min(sStart,((short)strlen(rp)));
            rp += (sStart-1);
         }

         /* Handter skilletegn */
         if (cSkilleTegn != '\0') {
            /* Skann hele strengen */
            sAntallBlank = 0;
            cp = cs = rp;
            while (*cp) {
               if (*cp == ' ') {    /* Funnet blank */
                  if (sAntallBlank == 0) {    /* Første i dette mellomrommet */
                     *(cs++) = cSkilleTegn;
                  }
                  ++cp;
                  ++sAntallBlank;

               }  else {          /* Kopier og pakk strengen */
                  *(cs++) = *(cp++);
                  sAntallBlank = 0;
               }
            }
            *cs = '\0';
         }

         /* Handter formateringskode */
         if (sFormater == 2) { // Desimaltallet skal ikke avrundes
            // Fjerner unødvendige desimaler fra tall for å unngå avrunding
            cp = rp;
            short sTeller=-99;
            while (*cp) {               
               if (*cp == '.')    // Funnet skilletegn
                  sTeller = -1;                          
               if(sTeller>-99)
                  if(sTeller++==sAntDes) {
                     *cp = '\0';
                     break;
                  }
               ++cp;
            }
         }
         if (sFormater) {
            UT_AtoD (rp,'.',&d);
            d *= pow((double)10.0,(int)sFlyttKomma);
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%.*f",sAntDes,d);
            rp = retur_str;
         }

      }
   }

   return  rp;
}


/*
AR-920615
CH LC_GetPiVerdi                                             Get PINFO-verdi
CD ==========================================================================
CD Formål:
CD Henter parametrene til et SOSI-navn.
CD Strengen ligger i et felles "returbuffer" for alle get-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "get-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk UT_StrCopy).
CD
CD Leddnummer, delstreng og formateringskode kan inngå som
CD forlengelse av SOSI-navnet.
CD
CD Leddnummer for flerleddet parameter angis ved #n.
CD Eks: ...KVALITET#2 er nøyaktighet.
CD
CD Delstreng angis ved: [start:slutt].
CD NB! 1 er første tegn.
CD Sluttposisjon 0 betyr at resten av strengen skal brukes.
CD Eks: ..STRENG[2:0]  Posisjon 2 og resten av strengen.
CD
CD Formateringskode kan angi skilletegn for flerleddet PINFO. Dette
CD angis ved ^x hvor x er det tegnet som skal skrives ut mellom leddene.
CD
CD Disse tilleggene kan kombineres, slik at  ...KVALITET#2[1:2] betyr at
CD det er tegn nummer 1 og 2 i det andre leddet (nøyaktigheten) som skal
CD brukes.
CD
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD char     pszSosiNavn  i    SOSI-navn det skal finnes verdi til.
CD                            Leddnummer posisjon og formateringskode kan
CD                            inngå som forlengelse av navnet.
CD                            OBS! Store og små bokstaver er signifikante.
CD                            HØYDE er spesialverdi som henter formatert
CD                            høyde fra punktet eller GINFO.
CD                            KVALITET er spesialverdi som henter formatert
CD                            kvalitet fra punktet, GINFO eller hode.
CD long     lPnr         i    Punktnummer
CD short   *sSettNr      iu   PINFO-nummer   (1 er første sett i PINFO.)
CD                            Ved tilslag returneres settnummer for tilslaget.
CD char    *pszVerdi     r    Peker til verdien avslutta med '\0'.
CD                            Hvis SOSI-navnet ikke er funnet returneres NULL.
CD
CD Bruk:
CD pszVerdi = LC_GetPiVerdi(pszSosiNavn,lPnr,&sSettNr);
   ==========================================================================
*/
SK_EntPnt_FYBA char *LC_GetPiVerdi(const char *pszSosiNavn,long lPnr,short *sSettNr)
{
   short lin,i,sAntallBlank;
   char *cp,*cs,*nt,szSosiNavn[LC_MAX_SOSINAVN_LEN];
   short sAntDes,niv;
   char format[20];
   double enhet,enhet_h,enhet_d,h;
   char cSkilleTegn = '\0';
   short sLedd = 0;
   short sStart = 0;
   short sSlutt = 0;
   short funnet = UT_FALSE;
   char *rp = NULL;          /* Retur peker */

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
      if (lPnr > 0  &&  lPnr <= Sys.pGrInfo->nko) {    /* Lovlig punkt ? */
         /* Er søkebuffer oppbygd ? */
         if (Sys.sPibufStatus != LC_PIBUF_OK  ||  Sys.lPibufPnr != lPnr) {
            LX_CreatePibuf(lPnr);
         }
      
         if (Sys.sPibufStatus != LC_PIBUF_OK) {
            UT_SNPRINTF(err().tx,LC_ERR_LEN," \"%s\"  pnr: %ld",LX_GetGi(1),lPnr);
            LC_Error(55,"(LC_GetPiVerdi)",err().tx);
            return NULL;

         }  else {

            /* Sjekk at det er lovlige linjenummer */
            if (*sSettNr < 1) {
               *sSettNr = 1;
            }
            lin = *sSettNr - 1;

            /* Plukk ut info om ledd, delstreng og formatering */
            UT_StrCopy(szSosiNavn,pszSosiNavn,LC_MAX_SOSINAVN_LEN);
            if ((cs = strpbrk(szSosiNavn,"#[^")) != NULL) {
               cp = cs;
               for (i=0;i<3;++i) {
                  if (*cp == '#') {
                     ++cp;
                     sLedd = (short) strtol(cp,&cp,10);       /* Ledd-nummer */
                  } else if (*cp == '^') {
                     ++cp;
                     cSkilleTegn = *cp;                       /* Skilletegn */
                     ++cp;
                  } else if (*cp == '[') {
                     ++cp;
                     sStart = (short) strtol(cp,&cp,10);      /* Startposisjon */
                     ++cp;
                     sSlutt = (short) strtol(cp,&cp,10);      /* Sluttposisjon */
                  }	
               }
               /* Fjern tilleggsinfo fra SOSI-navnet */
               *cs = '\0';
            }


                                           /* -------- Vanlig PINFO */
            /* Søk etter SOSI-navnet */
            while (lin < Sys.sPibufAntPi) {
               if (strcmp(Sys.pcPibufNavn[lin],szSosiNavn) == 0) {
                  funnet = UT_TRUE;
                  /* Kopier parameter */
                  UT_StrCopy(retur_str,Sys.pcPibufVerdi[lin],LC_MAX_SOSI_LINJE_LEN);
                  break;           /* Funnet, ==> hopp ut av løkken */
               }
               ++lin;
            }

                                             /* -------- Knutepunkt */
            if (!funnet) {
               if (lin < (Sys.sPibufAntPi+1)  &&
                           strcmp(szSosiNavn,"...KP") == 0) {
                  if ((i = LC_GetKp(lPnr)) != 0) {        /* Funnet KP */
                     UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%hd",i);
                     funnet = UT_TRUE;
                  }
                  lin = Sys.sPibufAntPi + 1;

                                             /* -------- Høyde */
               } else if (lin < (Sys.sPibufAntPi+2)  &&
                          strcmp(szSosiNavn,"HØYDE") == 0) {
                  if ((h = LC_GetHoyde(lPnr)) != HOYDE_MANGLER) { /* Funnet høyde */

                     /* Hent enhet og formater høyden */
                     niv = 2;
                     LC_GetCurEnhet(Sys.GrId.pFil,&niv,&enhet,&enhet_h,&enhet_d);
                     sAntDes = UT_RoundDS(fabs(min(0.0,log10(enhet_h))));
                     UT_SNPRINTF(format,20,"%%.%dlf",sAntDes);
                     UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,format,h);
                     funnet = UT_TRUE;
                  }
                  lin = Sys.sPibufAntPi + 2;

                                             /* -------- Kvalitet */
               } else if (lin < (Sys.sPibufAntPi+3)  &&
                          strcmp(szSosiNavn,"KVALITET") == 0) {
                  short sMetode, sSynbarhet, sHoydeMetode;
                  long lNoyaktighet, lHoydeNoyaktighet;
                  short nivaa = 3;
                  /* Funnet kvalitet? */
                  if (LC_GetCurKvalitet(Sys.GrId.pFil,&nivaa,lPnr,
                                        &sMetode,&lNoyaktighet,&sSynbarhet,
                                        &sHoydeMetode,&lHoydeNoyaktighet) == UT_TRUE) {
                     /* Formater kvaliteten */
                     UT_StrCopy(retur_str,
                               LC_FormatterKvalitet(sMetode,lNoyaktighet,sSynbarhet,sHoydeMetode,lHoydeNoyaktighet),
                               LC_MAX_SOSI_LINJE_LEN);
                     funnet = UT_TRUE;
                  }
                  lin = Sys.sPibufAntPi + 3;
               }
            }

            /* Klargjør for retur */
            *sSettNr = lin+1;
            if (funnet) {
               rp = retur_str;

               /* Handter leddnummer */
               if (sLedd != 0) {
                  cp = UT_strtok(rp," ",&nt);
                  while(cp != NULL  &&  --sLedd > 0){
                     cp = UT_strtok(NULL," ",&nt);
                  }
                  if (cp == NULL) {
                     *rp = '\0';
                  } else {
                     rp = cp;
                  }
               }

               /* Handter delstreng */
               if (sStart != 0) {
                  if (sSlutt != 0  &&  sSlutt < (short)strlen(rp)) {
                     *(rp+sSlutt) = '\0';
                  }
                  sStart = min(sStart,((short)strlen(rp)));
                  rp += (sStart-1);
               }

               /* Handter skilletegn */
               if (cSkilleTegn != '\0') {
                  /* Skann hele strengen */
                  sAntallBlank = 0;
                  cp = cs = rp;
                  while (*cp) {
                     if (*cp == ' ') {    /* Funnet blank */
                        if (sAntallBlank == 0) {    /* Første i dette mellomrommet */
                           *(cs++) = cSkilleTegn;
                        }
                        ++cp;
                        ++sAntallBlank;

                     }  else {          /* Kopier og pakk strengen */
                        *(cs++) = *(cp++);
                        sAntallBlank = 0;
                     }
                  }
                  *cs = '\0';
               }
            }
         }

      } else {                           /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),lPnr);
         LC_Error(51,"(LC_GetPiVerdi)",err().tx);
      }
   }

   return  rp;
}


/*
AR-920614
CH LX_CreatePibuf                                       Generer PINFO-buffer
CD ==========================================================================
CD Formål:
CD Henter PINFO for gitt punkt og legger den inn i et buffer.
CD Det bygges opp en tabell med pekere til starten av hvert SOSI-navn og
CD hver verdi.
CD
CD Parametre:
CD Type    Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD long   lPnr   i    Punktnummer.
CD
CD Bruk:
CD LX_CreatePibuf(lPnr);
   ==========================================================================
*/
static void LX_CreatePibuf(long lPnr)
{
   short sAntPi;
   char *pp,*cp;
   char *bp = Sys.cPibuf ;

   *Sys.cPibuf = '\0';

   sAntPi = 0;
   pp = LC_GetPi(lPnr);

   /* For lang pinfo */
   if (strlen(pp) > LC_MAX_PIBUF_TEGN) {
      Sys.sPibufStatus = LC_PIBUF_FULL;
      return;
   }

   /* Finn første/neste SOSI-navn */
   while ((cp = strstr(pp,"...")) != NULL) {  /* SOSI-navn */
      ++sAntPi;

      /* Sjekk om det er nok plass i tabell for peker til PINFO-linje */
      if (sAntPi > LC_MAX_PIBUF_LIN){
         Sys.sPibufStatus = LC_PIBUF_FULL;
         return;
      }

      pp = cp;
      Sys.pcPibufNavn[sAntPi-1] = bp;
      while (!UT_IsSpace(*pp)  &&  *pp != '\0') {
         *bp++ = *pp++;
      }
      *bp++ = '\0';

      /* Hopp over blanke mellom navn og verdi */
      while (UT_IsSpace(*pp)) {
         ++pp;
      }

      /* Ta vare på verdien */

      if (*pp == '"') {                 /* Hermetegn */
         if ((cp = strchr(pp+1,'"')) != NULL) {      /* Slutt-hermetegn */
            ++pp;
            *cp++ = '\0';
            cp = strstr(cp," ..."); /* Neste SOSI-navn */

         } else {
            UT_ClrTrailsp(pp);         /* Fjern blanke på slutten */
         }

      } else if ((cp = strstr(pp," ...")) != NULL) {  /* SOSI-navn */
         *cp++ = '\0';
         UT_ClrTrailsp(pp);         /* Fjern blanke på slutten */

      } else if ((cp = strchr(pp,'!')) != NULL) {    /* Kommentar */
         *cp = '\0';
         UT_ClrTrailsp(pp);         /* Fjern blanke på slutten */
         cp = NULL;

      } else {
         /* Linjeslutt  cp = NULL*/
         UT_ClrTrailsp(pp);         /* Fjern blanke på slutten */
      }

      /* Kopier strengen */
      Sys.pcPibufVerdi[sAntPi-1] = bp;
      while (*pp) {
         *bp++ = *pp++;
      }
      *bp++ = '\0';

      /* Neste sett */
      if (cp != NULL) {
         pp = cp;
      }
   }

   Sys.lPibufPnr = lPnr;
   Sys.sPibufAntPi = sAntPi;            /* Antall elementer brukt i Pibuf */
   Sys.sPibufStatus = LC_PIBUF_OK;
}


/*
AR-891001
CH LC_PutGP                                               Put GINFO-parameter
CD ==========================================================================
CD Formål:
CD Legger inn et SOSI-navn med verdi.
CD Denne rutinen kan brukes til å legge inn ginfo med nytt SOSI-navn.
CD Rutinen kan endre antall ginfo-linjer.
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD char     sosi_navn    i    Sosi-navn det skal legges inn verdi til
CD char     verdi        i    Streng som skal legges inn.
CD short   *linje_nr     u    Linjenummer for endringen.
CD short    ngi          r    Ant. ginfo-linjer etter  endringen.
CD
CD Bruk:
CD ngi = LC_PutGP(sosi_navn,verdi,&linje_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_PutGP(const char *sosi_navn,const char *verdi,short *linje_nr)
{
   char temp[LC_MAX_SOSI_LINJE_LEN];



#ifdef TEST

************************************************************
   short sLedd = 0;
   short funnet = 0;

   char *rp = NULL;          /* Retur peker */

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */

      /* Plukk ut info om ledd */
      UT_StrCopy(szSosiNavn,sosi_navn,LC_MAX_SOSINAVN_LEN);
      UT_StrUpper(szSosiNavn);

      if ((cs = strchr(szSosiNavn,'#')) != NULL) {
         cp = cs;
         ++cp;
         sLedd = (short) strtol(cp,&cp,10);       /* Ledd-nummer */
         /* Fjern tilleggsinfo fra SOSI-navnet */
         *cs = '\0';
      }

      /* Søk etter SOSI-navnet */
      sSosiLen = strlen(szSosiNavn);
      gi_lin = *forste_linje;
      while (gi_lin <= siste_linje) {
         /* Les ny linje */
         ginfo = LX_GetGi(gi_lin);

         /* Er dette rett navn? */
         if ((strncmp(ginfo,szSosiNavn,sSosiLen) == 0) &&
             ( (UT_IsSpace(*(ginfo+sSosiLen))  ||  *(ginfo+sSosiLen) == '\0'))) {

            /* Hopp over blanke mellom navn og verdi */
            cp = ginfo + sSosiLen;
            while (UT_IsSpace(*cp)) {
               ++cp;
            }
            /* Kopier parameter */
            rp = strcpy(retur_str,cp);

            /* Fjern hermetegn (") */
            if (*rp == '"') {
               if ((cp = strchr(rp+1,'"')) != NULL) {   /* Slutt-hermetegn */
                  ++rp;
                  *cp = '\0';
               }
            }

            /* Fjern hermetegn (') */
            if (*rp == '\'') {
               if ((cp = strchr(rp+1,'\'')) != NULL) {   /* Slutt-hermetegn */
                  ++rp;
                  *cp = '\0';
               }
            }

            /* Har ikke ledd , funnet OK */
            if (sLedd == 0) {
               funnet = 1;
               /* Husk linjenummeret */
               *forste_linje = gi_lin;
               break;           /* Funnet, ==> hopp ut av løkken */

            /* Handter leddnummer */
            } else {
               cp = strtok(rp," ");
               s = sLedd;
               while(cp != NULL  &&  --s > 0){
                  cp = strtok(NULL," ");
               }

               /* Leddet er funnet */
               if (cp != NULL) {
                  /* Aktuellt ledd huskes */
                  rp = cp;
                  funnet = 1;
                  /* Husk linjenummeret */
                  *forste_linje = gi_lin;
                  break;           /* Funnet, ==> hopp ut av løkken */
               
               } else {
                                    /* AR-950901 */
                  /* rp = NULL; */  /* Det aktuelle leddet finnes ikke */
                  /* Aktuellt ledd huskes */
                  rp = strchr(rp,'\0');
                  funnet = 1;
                  /* Husk linjenummeret */
                  *forste_linje = gi_lin;
                  break;           /* Funnet, ==> hopp ut av l›kken */
               }
            }
         }

         ++gi_lin;
      }

      /* Har funnet navnet */
      if (rp != NULL) {

         /* Handter delstreng */
         if (sStart != 0) {
            if (sSlutt != 0  &&  sSlutt < (short)strlen(rp)) {
               *(rp+sSlutt) = '\0';
            }
            sStart = min(sStart,((short)strlen(rp)));
            rp += (sStart-1);
         }

*****************************************************************
#endif



   if (Sys.GrId.lNr != INGEN_GRUPPE){                    /* Aktuell gruppe OK */
       *linje_nr = 2;
       if (LC_GetGP(sosi_navn,linje_nr,Sys.pGrInfo->ngi) != NULL){     /* Finn linjen */
                                                      /* Legg inn endringen */
           LC_UpdateGP(*linje_nr,sosi_navn,verdi);

       } else{                             /* Ikke funnet, ny linje */
           *linje_nr = LC_AppGiL();
           UT_StrCopy(temp,sosi_navn,LC_MAX_SOSI_LINJE_LEN);
           UT_StrCopy(temp," ",LC_MAX_SOSI_LINJE_LEN);
           UT_StrCopy(temp,verdi,LC_MAX_SOSI_LINJE_LEN);
           LC_PutGi(*linje_nr,temp);
       }

   } else{                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_PutGP)","");
   }

   return Sys.pGrInfo->ngi;
}


/*
AR:2010-02-09
CH LC_AppGP                                         Legg til GINFO-parameter
CD ==========================================================================
CD Formål:
CD Legger til et SOSI-navn med verdi i GINFO.
CD Lik LC_PutGP, men legger alltid til ny linje i ginfo.
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD char     sosi_navn    i    Sosi-navn det skal legges inn verdi til
CD char     verdi        i    Streng som skal legges inn.
CD short   *linje_nr     u    Linjenummer for endringen.
CD short    ngi          r    Ant. ginfo-linjer etter  endringen.
CD
CD Bruk:
CD ngi = LC_AppGP(sosi_navn,verdi,&linje_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_AppGP(const char *sosi_navn,const char *verdi,short *linje_nr)
{
   char temp[LC_MAX_SOSI_LINJE_LEN];


   if (Sys.GrId.lNr != INGEN_GRUPPE){                    /* Aktuell gruppe OK */
        *linje_nr = LC_AppGiL();
        UT_StrCopy(temp,sosi_navn,LC_MAX_SOSI_LINJE_LEN);
        UT_StrCopy(temp," ",LC_MAX_SOSI_LINJE_LEN);
        UT_StrCopy(temp,verdi,LC_MAX_SOSI_LINJE_LEN);
        LC_PutGi(*linje_nr,temp);

   } else{                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_AppGP)","");
   }

   return Sys.pGrInfo->ngi;
}


/*
AR-891001
CH LC_UpdateGP                                          Endre GINFO-parameter
CD ==========================================================================
CD Formål:
CD Legger inn parametren til et SOSI-navn.
CD Rutinen handterer at det er flere SOSI-navn på samme linje.
CD OBS! Denne rutinen kan ikke brukes til å legge inn nytt SOSI-navn.
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD short    linje_nr     i    Linjenummer som skal endres.
CD char     sosi_navn    i    Sosi-navn det skal legges inn verdi til
CD char     verdi        i    Streng som skall legges inn
CD short    ist          r    1=ok, 0=navnet er ikke funnet
CD
CD Bruk:
CD ist = LC_UpdateGP(linje_nr,sosi_navn,verdi);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_UpdateGP(short linje_nr,const char *sosi_navn,const char *verdi)
{
   char temp[LC_MAX_SOSI_LINJE_LEN],*gp,*neste,*cp;
   short ist=0;

   if (Sys.GrId.lNr != INGEN_GRUPPE){                    /* Aktuell gruppe OK */
       gp = LC_GetGi(linje_nr);
       if ((neste = strstr(gp,sosi_navn)) != NULL){    /* Finn SOSI-navnet */

           cp = neste - 1;                    /* Avslutt første del av ginfo */
           while (cp >= gp && UT_IsSpace(*cp)){
               cp--;
           }
           *(cp+1) = '\0';

           neste += strlen(sosi_navn);      /* Hopp over SOSI-navnet */

           while (UT_IsSpace(*neste))                 /* Ledende blanke */
               ++neste;

           if (*neste == '"' &&  (cp = strchr(neste+1,'"')) != NULL){   /* Hermetegn */
               neste = cp + 1;
               while (UT_IsSpace(*neste)){          /* Blanke */
                   ++neste;
               }

           } else if ((cp = strstr(neste-1," ..")) != NULL) { /* SOSI-navn */
               neste = cp + 1;

           } else if ((cp = strchr(neste,'!')) != NULL) { /* Kommentar */
               neste = cp;

           } else{                                 /* Slutten av strengen */
               neste = strchr(neste,'\0');
           }

                                                 /* Legg inn endringen */
           *temp = '\0';
           if (*gp){                      /* Første del */
               UT_StrCat(temp,gp,LC_MAX_SOSI_LINJE_LEN);
               UT_StrCat(temp," ",LC_MAX_SOSI_LINJE_LEN);
           }
           UT_StrCat(temp,sosi_navn,LC_MAX_SOSI_LINJE_LEN);        /* Aktuellt navn */
           UT_StrCat(temp," ",LC_MAX_SOSI_LINJE_LEN);
           UT_StrCat(temp,verdi,LC_MAX_SOSI_LINJE_LEN);
           if (*neste){                   /* Siste del */
               UT_StrCat(temp," ",LC_MAX_SOSI_LINJE_LEN);
               UT_StrCat(temp,neste,LC_MAX_SOSI_LINJE_LEN);
           }

           LC_PutGi(linje_nr,temp);
           ist = 1;
       }

   } else{                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_UpdateGP)","");
   }

   return ist;
}


/*
AR-881113
CH LC_InitPP                                                Initier PINFO-søk
CD ==========================================================================
CD Formål:
CD Initierer søk etter PINFO.
CD
CD Parametre:
CD Type            Navn        I/U  Forklaring
CD --------------------------------------------------------------------------
CD char            sosi_navn    i   Sosi-navn det skal finnes verdi til
CD long            forste_punkt i   Første punkt. (1 er første pkt i gr)
CD long            siste_punkt  i   Siste punkt det skal søkes i
CD LC_GETPP_STATUS pp_stat      iu  Struktur med statusvariabler. Denne er
CD                                  bare for intern bruk i InitPP / GetPP.
CD
CD Bruk:
CD   Se under LC_GetPP.
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_InitPP(const char *sosi_navn,long forste_punkt,long siste_punkt,
               LC_GETPP_STATUS *pp_stat)
{
   short itxu;

   if (Sys.GrId.lNr != INGEN_GRUPPE){                 /* Aktuell gruppe OK */

       UT_StrToken(const_cast<char*>(sosi_navn),0,&itxu,LC_MAX_SOSINAVN_LEN,pp_stat->pinfo_navn);  /* SOSI-navnet */
       UT_StrUpper(pp_stat->pinfo_navn);
       pp_stat->slutt_punkt = min(siste_punkt,Sys.pGrInfo->nko) + 1;

       /* -------- Knutepunkt */
       if (strcmp(pp_stat->pinfo_navn,"...KP") == 0){
           pp_stat->type = LC_GETPP_KP;
           pp_stat->curr_punkt = max(forste_punkt,1) -1;  /* Sjekk punktnummer */

       /* -------- Høyde */
       } else if (strcmp(pp_stat->pinfo_navn,"HØYDE") == 0) {
           pp_stat->type = LC_GETPP_HOYDE;
           pp_stat->curr_punkt = max(forste_punkt,1) -1;  /* Sjekk punktnummer */

       /* -------- Kvalitet */
       } else if (strcmp(pp_stat->pinfo_navn,"KVALITET") == 0) {
           pp_stat->type = LC_GETPP_KVALITET;
           pp_stat->curr_punkt = max(forste_punkt,1) -1;  /* Sjekk punktnummer */

       /* -------- Annen PINFO */
       } else {
           pp_stat->type = LC_GETPP_VANLIG;
           pp_stat->neste_tegn = 0;
           pp_stat->curr_punkt = max(forste_punkt,1);  /* Sjekk punktnummer */
       }
   }
}


/*
AR-890511
CH LC_GetPP                                                   Utfør PINFO-søk
CD ==========================================================================
CD Formål:
CD Henter parametrene til et SOSI-navn definert i LC_InitPP.
CD Strengen ligger i et felles "returbuffer" for alle get-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "get-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk strcpy).
CD
CD Parametre:
CD Type     Navn               I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    *punkt             u  Ved tilslag returneres punktnummer for
CD                               tilslaget.
CD LC_GETPP_STATUS pp_stat iu  Struktur med statusvariabler. Denne er
CD                               bare for intern bruk i InitPP / GetPP.
CD char    *para_peker        r  Peker til para.-streng avslutta med '\0'.
CD                               Hvis ingenting er funnet returneres NULL.
CD
CD Bruk:
CD .
CD   LC_GETPP_STATUS pp_stat;
CD .
CD LC_InitPP(sosi_navn,forste_punkt,siste_punkt,pp_stat);
CD para_peker = LC_GetPP(&punkt,pp_stat);
CD   .
   =============================================================================
*/
SK_EntPnt_FYBA char *LC_GetPP(long *punkt,LC_GETPP_STATUS *pp_stat)
{
   short nt,kp_type,sAntDes,niv;
   char format[20];
   char *pinfo,*cp,*parameter;
   char funnet_sosi[LC_MAX_SOSINAVN_LEN];
   double enhet,enhet_h,enhet_d,h;


   /* -------- Knutepunkt */
   if (pp_stat->type == LC_GETPP_KP) {
      pp_stat->curr_punkt++;
      if (LC_FinnKp(&(pp_stat->curr_punkt), pp_stat->slutt_punkt-1, &kp_type))  {      /* Søk */
         *punkt = pp_stat->curr_punkt;
                                     /* Lag parameter */
         UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,"%hd",kp_type);
         return  retur_str;               /* OBS! RETURNERER HER! */

      } else {                                         /* Ikke funnet */
         return  NULL;                           /* OBS! RETURNERER HER! */
      }

   /* -------- Høyde */
   } else if (pp_stat->type == LC_GETPP_HOYDE) {
      pp_stat->curr_punkt++;

      while (pp_stat->curr_punkt < pp_stat->slutt_punkt) {  /* Søk etter navnet */
         h = LC_GetHoyde(pp_stat->curr_punkt);
         if (h != HOYDE_MANGLER) {    /* Funnet høyde */
            *punkt = pp_stat->curr_punkt;

            /* Hent enhet og formater høyden */
            niv = 2;
            LC_GetCurEnhet(Sys.GrId.pFil,&niv,&enhet,&enhet_h,&enhet_d);
            
            sAntDes = UT_RoundDS(fabs(min(0.0,log10(enhet_h))));
            UT_SNPRINTF(format,20,"%%.%dlf",sAntDes);
            UT_SNPRINTF(retur_str,LC_MAX_SOSI_LINJE_LEN,format,h);

            return retur_str;              /* OBS! RETURNERER HER! */

         } else {                 /* Neste punkt */
            pp_stat->curr_punkt++;
         }
      }

      return NULL;                             /* Ikke funnet */

   /* -------- Kvalitet */
   } else if (pp_stat->type == LC_GETPP_KVALITET) {
      short sMetode, sSynbarhet, sHoydeMetode;
      long lNoyaktighet, lHoydeNoyaktighet;
      short nivaa = 3;

      pp_stat->curr_punkt++;

      while (pp_stat->curr_punkt < pp_stat->slutt_punkt) {  /* Søk etter navnet */

         /* Funnet kvalitet? */
         if (LC_GetCurKvalitet(Sys.GrId.pFil,&nivaa,pp_stat->curr_punkt,
                               &sMetode,&lNoyaktighet,&sSynbarhet,
                               &sHoydeMetode,&lHoydeNoyaktighet) == UT_TRUE) {
            *punkt = pp_stat->curr_punkt;
           
            /* Formater kvaliteten */
            UT_StrCopy(retur_str,
                       LC_FormatterKvalitet(sMetode,lNoyaktighet,sSynbarhet,sHoydeMetode,lHoydeNoyaktighet),
                       LC_MAX_SOSI_LINJE_LEN);
            return retur_str;              /* OBS! RETURNERER HER! */

         } else {                 /* Neste punkt */
            pp_stat->curr_punkt++;
         }
      }

      return NULL;                             /* Ikke funnet */

   /* -------- Annen PINFO */
   } else {
       nt = pp_stat->neste_tegn;
       while (pp_stat->curr_punkt < pp_stat->slutt_punkt){  /* Søk etter navnet */
           pinfo = LC_GetPi(pp_stat->curr_punkt);
           if (*pinfo){                        /* Punktet har PINFO */
               *punkt = pp_stat->curr_punkt;
               while (*punkt == pp_stat->curr_punkt){
                   UT_StrToken(pinfo,nt,&nt,LC_MAX_SOSINAVN_LEN,funnet_sosi); /* SOSI-navn */
                   parameter = pinfo + nt;

                   if (strcmp(pp_stat->pinfo_navn,funnet_sosi) == 0){  /* Tilslag */
                                                        /* Finn parameter */
                       while (*parameter == ' ')        /* Ledende blanke */
                           ++parameter;

                       if (*parameter == '"'){                 /* Hermetegn */
                           if ((cp = strchr(parameter+1,'"')) != NULL){ /* Slutt-hermetegn */
                               ++parameter;
                               *cp = '\0';
                           }
                       } else if ((cp = strstr(parameter," ..")) != NULL){ /* SOSI-navn */
                           *cp = '\0';
                           nt = (short)(cp - pinfo + 1);

                       } else if ((cp = strchr(parameter,'!')) != NULL){ /* Kommentar */
                           *cp = '\0';
                           pp_stat->curr_punkt++;
                           nt = 0;
                       } else{                             /* Linjeslutt */
                           pp_stat->curr_punkt++;
                           nt = 0;
                       }

                       pp_stat->neste_tegn = nt;               /* Klargjør for retur */
                       return parameter;              /* OBS! RETURNERER HER! */

                   } else{                /* Ikke tilslag, neste PINFO */
                       if ((cp = strstr(parameter," ..")) != NULL){  /* SOSI-navn */
                           nt = (short)(cp - pinfo + 1);
                       } else{                             /* Linjeslutt */
                           pp_stat->curr_punkt++;
                           nt = 0;
                       }
                   }
               }

           } else {
               pp_stat->curr_punkt++;
           }
       }
   }

   return NULL;                             /* Ikke funnet */
}


/*
AR-930609
CH LC_FinnKp                                                  Finn knutepunkt
CD ==========================================================================
CD Formål:
CD Skanner gruppe, og finner punkt som er knutepunkt.
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    *forste_punkt iu   Punktnummer for start søking.
CD                            (1 er første punkt i gruppen.)
CD                            Ved tilslag returneres punktnummer for tilslaget.
CD long     siste_punkt  i    Siste punkt det skal søkes i.
CD short   *kp           u    Knutepunkt.
CD short    status       r    Søkestatus (1=funnet, 0=ikke funnet)
CD
CD Bruk:
CD status = LC_FinnKp(&forste_punkt,siste_punkt,kp);
   ==========================================================================
*/
short LC_FinnKp(long *forste_punkt,long siste_punkt,short *kp)
{
   long punkt;


   if (Sys.GrId.lNr != INGEN_GRUPPE){                 /* Aktuell gruppe OK */
      if(Sys.pGrInfo->info & GI_KP){                 /* Gruppen har knutepunkt */
         punkt = max(*forste_punkt,1);               /* Sjekk punktnummer */
         siste_punkt = min(siste_punkt,Sys.pGrInfo->nko);

         /* Skann gruppen */
         for (punkt--; punkt<siste_punkt; ++punkt) {
            if ((Sys.pInfo+punkt)->sKp != 0) {         /* KP ? */
               *kp = (Sys.pInfo+punkt)->sKp;
               *forste_punkt = punkt+1;
               return(1);
            }
         }
      }
   }
   return(0);
}


/*
AR-890520
CH LC_PutSn                                                   Put Serienummer
CD ==========================================================================
CD Formål:
CD Legger inn nytt serienummer på aktuell gruppe.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD long     snr      i    Serienummer
CD
CD Bruk:
CD LC_PutSn(snr);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_PutSn(long snr)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE){               /* Aktuell gruppe OK */
                    /* Legger inn SNR og marker for endring */
       LX_PutSn(snr);
       Sys.sGrEndra = END_ENDRA;

   } else{                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_PutSn)","");
   }
}


/*
AR-930609
CH LX_PutSn                                           Lavnivå Put Serienummer
CD ==========================================================================
CD Formål:
CD Legger inn nytt serienummer på aktuell gruppe, uten å sette flagg for at
CD aktuell gruppe er oppdatert. Sjekker ikke om det er noen aktuell gruppe.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD long     snr      i    Serienummer
CD
CD Bruk:
CD LX_PutSn(snr);
   ==========================================================================
*/
void LX_PutSn(long snr)
{
   char szGinfo[LC_MAX_SOSI_LINJE_LEN],*cp;

   /* Legger ikke inn serienr i hodet */
   if (Sys.GrId.lNr > 0L) {
      /* Kobler gml SOSI-navn med nytt SNR */
      UT_StrCopy(szGinfo,Sys.Ginfo.pszTx,LC_MAX_SOSI_LINJE_LEN);

      cp = szGinfo;
      while (! UT_IsSpace(*cp) && *cp) {
         ++cp;
      }
      *cp = '\0';
     
      /* Heng på serienummer */
      if (snr != 0L) {
         char szOrd[50];
         UT_SNPRINTF(szOrd, 50, " %ld:", snr);
         UT_StrCat(szGinfo,szOrd,LC_MAX_SOSI_LINJE_LEN);
      }
     
      /* Linjen lagres */
      LX_PutGi(1,szGinfo);
   }
}


/*
AR-930609
CH LC_GetSn                                                  Get serienummer
CD ==========================================================================
CD Formål:
CD Henter serienummer for aktuell gruppe.
CD
CD Parametre:
CD Type  Navn  I/U  Forklaring
CD --------------------------------------------------------------------
CD long  snr    r   Serienr.  (INGEN_GRUPPE = ingen aktuell gruppe)
CD
CD Bruk:
CD snr = LC_GetSn();
   ==========================================================================
*/
SK_EntPnt_FYBA long LC_GetSn(void)
{
   char *cp;

   /* Aktuell gruppe OK */
   if (Sys.GrId.lNr != INGEN_GRUPPE) {
       cp = strchr(LX_GetGi(1),' ');
       if (cp != NULL) {
         return  atol(cp);                              /* ==> */
      } else {
         return  0L;                                    /* ==> */
      }
   }

   /* Ingen aktuell gruppe */
   return  INGEN_GRUPPE;                                /* ==> */
}


/*
AR-930609
CH LC_PutGi                                                   Put GINFO-linje
CD ==========================================================================
CD Formål:
CD Legger inn GINFO-linje rent generellt.
CD Dette omfatter også nytt gruppenavn (GINFO-linje 1)
CD Ønsker du å endre serienummer må LC_PutSn benyttes.
CD Referansenummer legges inn med LC_PutRef.
CD Blanke på starten og slutten blir skrella vekk, og SOSI-navnet blir
CD konvertert til "store" bokstaver, .ellers lagres det slik det er.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD short    lin_nr   i    Linjenummer i GINFO   (1 er første linje)
CD char     *ginfo   i    GINFO-streng avslutta med '\0'
CD
CD Bruk:
CD LC_PutGi(lin_nr,ginfo);
	==========================================================================
*/
SK_EntPnt_FYBA void LC_PutGi(short lin_nr, const char *pszGinfo)
{
   // Aktuell gruppe OK
	if (Sys.GrId.lNr != INGEN_GRUPPE)
   {   
      // Lovlig linje ?
		if (lin_nr > 0 && lin_nr <= Sys.pGrInfo->ngi)
      {                          
         // Gruppestart håndteres spesielt
			if (lin_nr == 1)
         {                   
            char ginfo[LC_MAX_SOSI_LINJE_LEN];
            char *ct;

				/* Husk gammelt SNR */
            long  lGmlSnr = LC_GetSn();

				// Fjern ledende blanke og kopier til lokal variabel
            while (UT_IsSpace(*pszGinfo)) {
					++pszGinfo;
				}
				UT_StrCopy(ginfo,pszGinfo,LC_MAX_SOSI_LINJE_LEN);

				/* Finn SOSI-navnet */
				ct = ginfo;
				while (*ct  &&  ! UT_IsSpace(*ct)) {
					++ct;
				}
				*ct = '\0';

				/* Heng på serienummer */
				if (lGmlSnr != 0L) {
               char szOrd[50];
               UT_SNPRINTF(szOrd, 50, " %ld:", lGmlSnr);
               UT_StrCat(ginfo,szOrd,LC_MAX_SOSI_LINJE_LEN);
				}
            LX_PutGi(lin_nr,ginfo);
         }

         else
         {
            LX_PutGi(lin_nr,pszGinfo);
         }

			/* Linjen lagres */

      } else {                                 /* Ulovlig linjenummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN," %d",lin_nr);
         LC_Error(52,"(LC_PutGi)",err().tx);
      }
   }
}



/*
AR-930609
CH LX_PutGi                                          Lavnivå put GINFO-linje
CD ==========================================================================
CD Formål:
CD Lavnivå innlegging GINFO-linje rent generellt.
CD Blanke på starten og slutten blir skrella vekk, og SOSI-navnet blir
CD konvertert til "store" bokstaver, ellers lagres det slik det er.
CD Sjekker også at det aktuelle SOSI-navnet er lovlig å oppdatere.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD short    lin_nr   i    Linjenummer i GINFO   (1 er første linje)
CD char     *ginfo   i    GINFO-streng avslutta med '\0'
CD
CD Bruk:
CD LX_PutGi(lin_nr,ginfo);
   ==========================================================================
*/
static void LX_PutGi(short lin_nr, const char *szGinfo)
{
   short navn_nr,gr_start,dummy,sGmlLen,sNyLen;
   char *cs,tmp,*ct;
   double enhet,dNord,dAust;
   char* pszNgisLag;
   char ginfo[LC_MAX_SOSI_LINJE_LEN];
   short sLagre = UT_TRUE;


   Sys.sGrEndra = END_ENDRA;

   /* Fjern blanke i starten og på slutten */
   UT_StrCopy(ginfo,szGinfo,LC_MAX_SOSI_LINJE_LEN);
   UT_ClrTrailsp(ginfo);

   cs = ginfo;
   while (UT_IsSpace(*cs))
   {
      ++cs;
   }

   // Sjekk at linjen ikke er for lang
   if (strlen(cs) > (LC_MAX_SOSI_LINJE_LEN - 10))
   {
      *(cs + LC_MAX_SOSI_LINJE_LEN -10) = '\0';
      UT_StrCat(ginfo, " ?????", LC_MAX_SOSI_LINJE_LEN);
      LC_Error(134,"(LX_PutGi)",LX_GetGi(1));
   }

   /* Finn SOSI-navnet */
   ct = cs;
   while (*ct  &&  ! UT_IsSpace(*ct))
   {
      ++ct;
   }

   /* Konv. SOSI-navnet til stor-bokstaver og finn navnenummer */
   tmp = *ct;
   *ct = '\0';
   UT_StrUpper(cs);
   gr_start = LN_FinnNavn(&(Sys.GrId.pFil->SosiNavn),cs,&navn_nr);
   *ct = tmp;

   /* Gruppestart */
   if (lin_nr == 1) {
      if (gr_start == 1) {
         Sys.pGrInfo->gnavn = navn_nr;          /* Husk gruppenavnet */

      } else {
         /* Melding om ukjent gruppestart */
         LC_Error(54,"(LC_PutGi)",ginfo);
         sLagre = UT_FALSE;
      }

   /* Annen GINFO */
   } else { 
      if (gr_start > 0) {
         /* ...ENHET i filhode på fil med data */
         if (Sys.GrId.lNr == 0L  &&  Sys.GrId.pFil->lAntGr > 1  &&  navn_nr == L_ENHET3) {

            /* Sjekk at enhet ikke er endret */
            UT_StrDbl(ct,1,&dummy,'.',&enhet);
            if (fabs(enhet - Sys.GrId.pFil->TransPar.dEnhet) > LC_ACCY) {
               LB_FormaterEnhet(err().tx,LC_ERR_LEN,
                                LN_GetNavn(&(Sys.GrId.pFil->SosiNavn),navn_nr),
                                Sys.GrId.pFil->TransPar.dEnhet);
               LC_Error(57,"(LX_PutGi)",err().tx);
               sLagre = UT_FALSE;
            }
         }

         /* ...ENHET-H i filhode på fil med data */
         if (Sys.GrId.lNr == 0L  &&  Sys.GrId.pFil->lAntGr > 1  &&  navn_nr == L_ENHET3H) {
            /* Sjekk at enhet ikke er endret */
            UT_StrDbl(ct,1,&dummy,'.',&enhet);
            if (fabs(enhet - Sys.GrId.pFil->TransPar.dEnhet_h) > LC_ACCY) {
               LB_FormaterEnhet(err().tx,LC_ERR_LEN,
                                LN_GetNavn(&(Sys.GrId.pFil->SosiNavn),navn_nr),
                                Sys.GrId.pFil->TransPar.dEnhet_h);
               LC_Error(57,"(LX_PutGi)",err().tx);
               sLagre = UT_FALSE;
            }
         }

         /* ...ENHET-D i filhode på fil med data */
         if (Sys.GrId.lNr == 0L  &&  Sys.GrId.pFil->lAntGr > 1  &&  navn_nr == L_ENHET3D) {
            /* Sjekk at enhet ikke er endret */
            UT_StrDbl(ct,1,&dummy,'.',&enhet);
            if (fabs(enhet - Sys.GrId.pFil->TransPar.dEnhet_d) > LC_ACCY) {
               LB_FormaterEnhet(err().tx,LC_ERR_LEN,
                                LN_GetNavn(&(Sys.GrId.pFil->SosiNavn),navn_nr),
                                Sys.GrId.pFil->TransPar.dEnhet_d);
               LC_Error(57,"(LX_PutGi)",err().tx);
               sLagre = UT_FALSE;
            }
         }

         /* ..NGIS-LAG i filhode på fil med data */
         if (Sys.GrId.lNr == 0L  &&  Sys.GrId.pFil->lAntGr > 1  &&  navn_nr == L_NGISLAG) {

            /* Sjekk at ..NGIS-LAG ikke er endret */
            pszNgisLag = ct; 
         
            // Filen har ikke NGIS-LAG eller NGIS-LAG er endret
            //if (lNgisLag != Sys.GrId.pFil->lNgisLag) {
            if (*(Sys.GrId.pFil->szNgisLag) == '\0'  ||
                strcmp(pszNgisLag,Sys.GrId.pFil->szNgisLag) != 0) {
            
               UT_SNPRINTF(err().tx,LC_ERR_LEN," %s %s",
                       LN_GetNavn(&(Sys.GrId.pFil->SosiNavn),navn_nr),
                       Sys.GrId.pFil->szNgisLag);
               LC_Error(58,"(LX_PutGi)",err().tx);
               sLagre = UT_FALSE;
            }
         }

         /* ..ORIGO-NØ i filhode på fil med data */
         if (Sys.GrId.lNr == 0L  &&  Sys.GrId.pFil->lAntGr > 1  &&  navn_nr == L_ORIGONO) {

            /* Sjekk at ..ORIGO-NØ ikke er endret */
            UT_StrDbl(ct,1,&dummy,'.',&dNord);
            UT_StrDbl(ct,dummy,&dummy,'.',&dAust);
        
            if (fabs(dNord - Sys.GrId.pFil->TransPar.Origo.dNord) > 0.1 ||
                fabs(dAust - Sys.GrId.pFil->TransPar.Origo.dAust) > 0.1  ) {
         
               UT_SNPRINTF(err().tx,LC_ERR_LEN," %s %.0f %.0f",
                       LN_GetNavn(&(Sys.GrId.pFil->SosiNavn),navn_nr),
                       Sys.GrId.pFil->TransPar.Origo.dNord, Sys.GrId.pFil->TransPar.Origo.dAust);
               LC_Error(60,"(LX_PutGi)",err().tx);
               sLagre = UT_FALSE;
            }
         }

         // ..OBJTYPE
         if (navn_nr == L_OBJTYPE) {
            UT_StrCopy(Sys.pGrInfo->szObjtype,ct,LC_MAX_OBJTYPE_LEN);
         }

         /* Referanser */
         if (navn_nr == L_REF1  ||  navn_nr == L_REF2) {
            Sys.pGrInfo->info |= GI_REF;
            if (LN_TestOy(ginfo))  Sys.pGrInfo->info |= GI_OY_REF;

#ifdef UTGAAR
         /* Gruppen har høyde informasjon */
         } else if (navn_nr == L_HOYDE) {
            Sys.pGrInfo->info |= GI_NAH;   /* Husk at gruppen har høyde */
#endif
         }
      }
   }


   if (sLagre == UT_TRUE) {
      /* Linjen lagres */
      sGmlLen = (short)strlen(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr - 1]);
      sNyLen = (short)strlen(cs);

      /* Samme lengde, trenger ikke å flytte noe i buffer */
      if (sNyLen == sGmlLen) {
         //strcpy(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr - 1], cs);
         UT_memcpy(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr - 1], sNyLen+1, cs, sNyLen+1);

      /* Siste linje i GINFO, trenger ikke å flytte noe i buffer */
      } else if (lin_nr == Sys.pGrInfo->ngi) {
         //strcpy(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr - 1],cs);
         UT_memcpy(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr - 1], sNyLen+1, cs, sNyLen+1);

         /* Oppdater antall tegn brukt i GINFO-buffer */
         Sys.pGrInfo->ulGiLen = Sys.pGrInfo->ulGiLen - sGmlLen + sNyLen;

      /* Må flytte resten av buffer for å tilpasse plassen */
      } else {
         memmove(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr] - sGmlLen + sNyLen,
                 Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr],
                 Sys.pGrInfo->ulGiLen - Sys.Ginfo.ulOfset[lin_nr]);
         //strcpy(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr - 1],cs);
         UT_memcpy(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr - 1], sNyLen+1, cs, sNyLen+1);

         /* Oppdater antall tegn brukt i GINFO-buffer */
         Sys.pGrInfo->ulGiLen += (sNyLen - sGmlLen);
         /* Oppdater pekere til GINFO linjene */
         LX_CreGiPeker(&Sys.Ginfo,Sys.pGrInfo->ngi);
      }
   }
}

/*
AR-930609
CH LX_CreGiPeker                              Bygg opp pekertabell til GINFO
CD ==========================================================================
CD Formål:
CH Bygg opp pekertabell til GINFO buffer.
CD
CD Parametre:
CD Type            Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_GINFO       *pGinfo     i    Peker til GINFO struktur
CD short           ngi        i    Ant. GINFO linjer
CD
CD Bruk:
CD LX_CreGiPeker(&Sys.Ginfo,Sys.pGrInfo->ngi);
   ==========================================================================
*/
void LX_CreGiPeker(LC_GINFO_BUFFER * pGinfo,short ngi)
{
   short i;
   unsigned long *pulOfset = pGinfo->ulOfset;
   char *cp = pGinfo->pszTx;

   /* Første GINFO starter alltid i posisjon 0 */
   *pulOfset++ = 0;

   /* Skanner strengen og finner startposisjonen for resten av GINFO */
   for (i=1; i<ngi; ++i) {
      cp = strchr(cp,'\0') + 1;
      *pulOfset++ = (unsigned long) (cp - pGinfo->pszTx);
   }
}


/*
AR-930609
CH LX_GetGi                                           Intern get GINFO-linje
CD ==========================================================================
CD Formål:
CD Henter en GINFO-linje som en streng rent generellt.
CD Dette omfatter også serienummer og referansenummer.
CD Returnerer peker til den aktuelle strengen i GINFO-buffer.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD short    lin_nr   i    Linjenummer i GINFO   (1 er første linje)
CD char    *ginfo    r    Peker til GINFO-streng avslutta med '\0'
CD
CD Bruk:
CD ginfo = LX_GetGi(lin_nr);
   ==========================================================================
*/
char *LX_GetGi(short lin_nr)
{
   return  Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[lin_nr - 1];
}


/*
AR-930609
CH LC_GetGi                                                  Get GINFO-linje
CD ==========================================================================
CD Formål:
CD Henter en GINFO-linje som en streng rent generellt.
CD Dette omfatter også serienummer og referansenummer.
CD Strengen ligger i et felles "returbuffer" for alle get-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "get-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk strcpy).
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD short    lin_nr   i    Linjenummer i GINFO   (1 er første linje)
CD char    *ginfo    r    Peker til GINFO-streng avslutta med '\0'
CD
CD Bruk:
CD ginfo = LC_GetGi(lin_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA char *LC_GetGi(short lin_nr)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */

      if (lin_nr > 0 && lin_nr <= Sys.pGrInfo->ngi) {       /* Lovlig linje ?  */

         UT_StrCopy(retur_str,LX_GetGi(lin_nr),LC_MAX_SOSI_LINJE_LEN);

      } else {                              /* Ulovlig linjenummer */
         *retur_str = '\0';
      }

   } else {                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_GetGi)","");
       *retur_str = '\0';
   }

   return retur_str;
}


/*
AR-910219
CH LC_PutTK                                                     Put koordinat
CD ==========================================================================
CD Formål:
CD Legger inn et punkts koordinater (n,ø) i meter i terreng
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long   punkt_nr   i    Punktnummer (1 er første punkt)
CD double  aust       i    Øst-koordinat i meter i terreng
CD double  nord       i    Nord-koordinat i meter i terreng
CD
CD Bruk:
CD LC_PutTK(punkt_nr,aust,nord);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_PutTK(long punkt_nr,double aust,double nord)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE){                  /* Aktuell gruppe OK */

      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {    /* Lovlig punkt ? */

         *(Sys.pdAust + punkt_nr - 1) = aust;    /* Øst */
         *(Sys.pdNord + punkt_nr - 1) = nord;    /* Nord */

         Sys.sGrEndra = END_ENDRA;

      } else {                                     /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_PutTK)",err().tx);
      }

   } else {                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_PutTK)","");
   }
}


/*
AR-930609
CH LC_GetTK                                                     Get koordinat
CD ==========================================================================
CD Formål:
CD Henter et punkts koordinater (ø,n) i meter i terreng
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long   punkt_nr   i    Punktnummer (1 er første punkt)
CD double  *aust      u    Øst-koordinat i meter i terreng
CD double  *nord      u    Nord-koordinat i meter i terreng
CD
CD Bruk:
CD LC_GetTK(punkt_nr,&aust,&nord);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_GetTK(long punkt_nr,double *aust,double *nord)
{
   /* Aktuell gruppe OK? */
   if (Sys.GrId.lNr != INGEN_GRUPPE) {
      /* Lovlig punkt ? */
      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {
         *aust = *(Sys.pdAust + punkt_nr - 1);    /* Øst */
         *nord = *(Sys.pdNord + punkt_nr - 1);    /* Nord */

      /* Ulovlig punktnummer */
      } else {
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_GetTK)",err().tx);
      }
   }
}


/*
AR-930617
CH LC_GetArrayTK                                  Hent tabell med koordinater
CD ==========================================================================
CD Formål:
CD Henter tabell med koordinater (ø,n) i meter i terreng
CD
CD Parametre:
CD Type    Navn       I/U   Forklaring
CD --------------------------------------------------------------------------
CD short   retning     i    Buffer-retning:
CD                                HENT_FORRFRA ( 1) = vanlig,
CD                                HENT_BAKFRA  (-1) = buffer skal snues.
CD long    max_antall  i    Max antall punkt som kan hentes
CD long    fra_punkt   i    Fra punktnummer (1 eller nko  er første punkt)
CD double  *aust       u    Peker til tab. for øst-koordinater
CD double  *nord       u    Peker til tab. for nord-koordinater
CD long    *antall     u    Antall punkt hentet
CD
CD Bruk:
CD LC_GetArrayTK(retning,max_antall,fra_punkt,aust,nord,&lest);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_GetArrayTK(short retning,long max_antall,long fra_punkt,
                   double *aust,double *nord,long *antall)
{
   long ant = 0;
   long pt;
   double *pdA,*pdN;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */

      /* Hent bakfra */
      if (retning == HENT_BAKFRA) {
         if (fra_punkt > Sys.pGrInfo->nko)  fra_punkt = Sys.pGrInfo->nko;
         pt = fra_punkt - 1;
         pdA = Sys.pdAust + pt;
         pdN = Sys.pdNord + pt;
         while (ant < max_antall  &&  pt >= 0) {
            ++ant;
            *aust++ = *pdA--;    /* Øst */
            *nord++ = *pdN--;    /* Nord */
            --pt;
         }

      /* Hent forrfra */
      } else {
         if (fra_punkt < 1)  fra_punkt = 1;
         pt = fra_punkt - 1;
         pdA = Sys.pdAust + pt;
         pdN = Sys.pdNord + pt;
         while (ant < max_antall  &&  pt < Sys.pGrInfo->nko) {
            ++ant;
            *aust++ = *pdA++;    /* Øst */
            *nord++ = *pdN++;    /* Nord */
            ++pt;
         }
      }
   }

   *antall = ant;
}


/*
AR-940630
CH LC_GetArrayTH                                  Hent tabell med høyder
CD ==========================================================================
CD Formål:
CD Henter tabell med høyder
CD
CD Parametre:
CD Type    Navn       I/U   Forklaring
CD --------------------------------------------------------------------------
CD short   retning     i    Buffer-retning:
CD                                HENT_FORRFRA ( 1) = vanlig,
CD                                HENT_BAKFRA  (-1) = buffer skal snues.
CD long    max_antall  i    Max antall punkt som kan hentes
CD long    fra_punkt   i    Fra punktnummer (1 eller nko  er første punkt)
CD double  *aust       u    Peker til tab. for høyder
CD long   *antall     u    Antall punkt hentet
CD
CD Bruk:
CD LC_GetArrayTH(retning,max_antall,fra_punkt,hoyde,&lest);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_GetArrayTH(short retning,long max_antall,long fra_punkt,
                   double *hoyde,long *antall)
{
   short gilin;
   char *gp;
   long pt;
   double dGiHoyde;
   long ant = 0;


   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */
      /* Hent høyde fra GINFO */
      gilin = 2;
      gp = LC_GetGP(LN_GetNavn(&Sys.GrId.pFil->SosiNavn,L_HOYDE),
                    &gilin,Sys.pGrInfo->ngi);
      if (gp != NULL) {
         dGiHoyde = strtod(gp,&gp);

      } else {
         dGiHoyde = HOYDE_MANGLER;
      }

      /* Hent aktuelle høyder i punktene */

      /* Hent bakfra */
      if (retning == HENT_BAKFRA) {
         if (fra_punkt > Sys.pGrInfo->nko)  fra_punkt = Sys.pGrInfo->nko;
         pt = fra_punkt - 1;
         while (ant < max_antall  &&  pt >= 0) {
            ++ant;

            if ((Sys.pGrInfo->info & GI_NAH) != 0  &&
                (Sys.pInfo + pt)->dHoyde != HOYDE_MANGLER) {
               *hoyde++ = (Sys.pInfo + pt)->dHoyde;

            } else {
               *hoyde++ = dGiHoyde;
            }

            pt--;
         }

      /* Hent forrfra */
      } else {
         if (fra_punkt < 1)  fra_punkt = 1;
         pt = fra_punkt - 1;
         while (ant < max_antall  &&  pt < Sys.pGrInfo->nko) {
            ++ant;

            if ((Sys.pGrInfo->info & GI_NAH) != 0  &&
                (Sys.pInfo + pt)->dHoyde != HOYDE_MANGLER) {
               *hoyde++ = (Sys.pInfo + pt)->dHoyde;

            } else {
               *hoyde++ = dGiHoyde;
            }

            ++pt;
         }
      }
   }

   *antall = ant;
}


/*
AR-940630
CH LC_PutTH                                                        Put høyde
CD ==========================================================================
CD Formål:
CD Legger inn et punkts høyde i meter i terreng
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    punkt_nr   i    Punktnummer (1 er første punkt)
CD double  hoyde      i    Høyde i meter i terreng. Konstanten
CD                         HOYDE_MANGLER (-999.999) angir at punktet ikke
CD                         har høydeverdi.
CD
CD Bruk:
CD LC_PutTH(punkt_nr,hoyde);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_PutTH(long punkt_nr, double hoyde)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */

      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {   /* Lovlig punkt ? */

         if ((Sys.pGrInfo->info & GI_NAD) == 0) {

             if (hoyde != HOYDE_MANGLER)  Sys.pGrInfo->info |= GI_NAH; // Husker at gruppen har høyde
                
             (Sys.pInfo + punkt_nr - 1)->dHoyde = hoyde;
         
             Sys.sGrEndra = END_ENDRA;
             if (punkt_nr == Sys.lPibufPnr)  Sys.sPibufStatus = LC_PIBUF_TOM;

         /* Gruppen har ..NAD fra før og det prøves å legge inne en høyde */
         } else if (hoyde != HOYDE_MANGLER) {
            LC_Error(132,"(LC_PutTH)",LC_GetGi(1));
         }

      } else {
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_PutTH)",err().tx);
      }
   }
}


/*
AR-9930609
CH LC_GetTH                                                        Get høyde
CD ==========================================================================
CD Formål:
CD Henter et punkts høyde i meter i terreng. (Henter BARE FRA PUNKTET.)
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    punkt_nr   i    Punktnummer (1 er første punkt)
CD double *hoyde      r    Høyde i meter i terreng. Konstanten
CD                         HOYDE_MANGLER (-999.999) angir at punktet ikke
CD                         har høydeverdi.
CD
CD Bruk:
CD hoyde = LC_GetTH(punkt_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA double LC_GetTH(long punkt_nr)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {  /* Lovlig punkt ? */
         /* Gruppen har ..NAH */
         if ((Sys.pGrInfo->info & GI_NAH) != 0) {
            return (Sys.pInfo + punkt_nr - 1)->dHoyde;
         }

      } else {                           /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_GetTH)",err().tx);
      }
   }

   return  HOYDE_MANGLER;
}


/*
AR-940630
CH LC_GetHoyde                                                     Get høyde
CD ==========================================================================
CD Formål:
CD Henter et punkts høyde i meter i terreng. (Henter fra punktet eller fra
CD GINFO.)
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    punkt_nr   i    Punktnummer (1 er første punkt)
CD double *hoyde      r    Høyde i meter i terreng. Konstanten
CD                         HOYDE_MANGLER (-999.999) angir at punktet ikke
CD                         har høydeverdi.
CD
CD Bruk:
CD hoyde = LC_GetHoyde(punkt_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA double LC_GetHoyde(long punkt_nr)
{
   short gilin;
   char *gp;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {  /* Lovlig punkt ? */
         /* Gruppen har ..NAH */
         if ((Sys.pGrInfo->info & GI_NAH) != 0) {
            /* Punktet har høyde */
            if ((Sys.pInfo + punkt_nr - 1)->dHoyde != HOYDE_MANGLER) {
               return (Sys.pInfo + punkt_nr - 1)->dHoyde;
            }
         }

         /* Punktet har ikke høyde, sjekk GINFO */
         gilin = 2;
         gp = LC_GetGP(LN_GetNavn(&Sys.GrId.pFil->SosiNavn,L_HOYDE),
                       &gilin,Sys.pGrInfo->ngi);
         if (gp != NULL) {
            return  strtod(gp,&gp);
         }

      } else {                           /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_GetHoyde)",err().tx);
      }
   }

   return  HOYDE_MANGLER;
}


/*
AR-940630
CH LC_PutTD                                                        Put dybde
CD ==========================================================================
CD Formål:
CD Legger inn et punkts dybde i meter i terreng
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    punkt_nr   i    Punktnummer (1 er første punkt)
CD double  hoyde      i    Dybde i meter i terreng. Konstanten
CD                         HOYDE_MANGLER (-999.999) angir at punktet ikke
CD                         har dybdeverdi.
CD
CD Bruk:
CD LC_PutTD(punkt_nr,dybde);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_PutTD(long punkt_nr, double dybde)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE){                  /* Aktuell gruppe OK */

      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko){    /* Lovlig punkt ? */

         if ((Sys.pGrInfo->info & GI_NAH) == 0) {

             if (dybde != HOYDE_MANGLER)  Sys.pGrInfo->info |= GI_NAD;

             (Sys.pInfo + punkt_nr - 1)->dHoyde = dybde;
         
             Sys.sGrEndra = END_ENDRA;
             if (punkt_nr == Sys.lPibufPnr)  Sys.sPibufStatus = LC_PIBUF_TOM;

         /* Gruppen har ..NAH fra før og det prøves å legge inn en dybde */
         } else if (dybde != HOYDE_MANGLER) {
            LC_Error(133,"(LC_PutTD)",LC_GetGi(1));
         }

      } else {
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_PutTD)",err().tx);
      }
   }
}


/*
AR-940630
CH LC_GetTD                                                        Get dybde
CD ==========================================================================
CD Formål:
CD Henter et punkts dybde i meter i terreng. (Henter BARE FRA PUNKTET.)
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    punkt_nr   i    Punktnummer (1 er første punkt)
CD double *dybde      r    Dybde i meter i terreng. Konstanten
CD                         HOYDE_MANGLER (-999.999) angir at punktet ikke
CD                         har dybdeverdi.
CD
CD Bruk:
CD dybde = LC_GetTD(punkt_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA double LC_GetTD(long punkt_nr)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {  /* Lovlig punkt ? */
         /* Gruppen har ..NAD */
         if ((Sys.pGrInfo->info & GI_NAD) != 0) {
            return (Sys.pInfo + punkt_nr - 1)->dHoyde;
         }

      } else {                           /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_GetTD)",err().tx);
      }
   }

   return  HOYDE_MANGLER;
}


/*
AR-940630
CH LC_GetDybde                                                     Get dybde
CD ==========================================================================
CD Formål:
CD Henter et punkts dybde i meter i terreng. (Henter fra punktet eller fra
CD GINFO.)
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    punkt_nr   i    Punktnummer (1 er første punkt)
CD double *hoyde      r    Dybde i meter i terreng. Konstanten
CD                         HOYDE_MANGLER (-999.999) angir at punktet ikke
CD                         har høydeverdi.
CD
CD Bruk:
CD dybde = LC_GetHoyde(punkt_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA double LC_GetDybde(long punkt_nr)
{
   short gilin;
   char *gp;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {  /* Lovlig punkt ? */
         /* Gruppen har ..NAD */
         if ((Sys.pGrInfo->info & GI_NAD) != 0) {
            /* Punktet har dybde */
            if ((Sys.pInfo + punkt_nr - 1)->dHoyde != HOYDE_MANGLER) {
               return (Sys.pInfo + punkt_nr - 1)->dHoyde;
            }
         }

         /* Punktet har ikke dybde, sjekk GINFO */
         gilin = 2;
         gp = LC_GetGP(LN_GetNavn(&Sys.GrId.pFil->SosiNavn,L_DYBDE),
                       &gilin,Sys.pGrInfo->ngi);
         if (gp != NULL) {
            return  strtod(gp,&gp);
         }

      } else {                           /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_GetHoyde)",err().tx);
      }
   }

   return  HOYDE_MANGLER;
}


/*
AR-930609
CH LC_GetPi                                                        Get PINFO
CD ==========================================================================
CD Formål:
CD Henter punktinformasjon i angitte punkt som en streng.
CD Strengen ligger i et felles "returbuffer" for alle get-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "get-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk strcpy).
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long   punkt_nr   i    Punktnummer (1 er første punkt)
CD char   *pinfo      r    Peker til punktinformasjon eksklusiv knutepunkt
CD
CD Bruk:
CD pinfo = LC_GetPi(punkt_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA char *LC_GetPi(long punkt_nr)
{
   unsigned long ulOfset;

   *retur_str = '\0';

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                   /* Aktuell gruppe OK */
      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {    /* Lovlig punkt ? */

         ulOfset = (Sys.pInfo+punkt_nr-1)->ulPiOfset;

         if (ulOfset != LC_INGEN_PINFO) {
            UT_StrCopy(retur_str,Sys.pszPinfo+ulOfset,LC_MAX_SOSI_LINJE_LEN);

         }

      } else {                           /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_GetPi)",err().tx);
      }
   }

   return retur_str;
}


/*
AR-930609
CH LC_PutPi                                                         Put PINFO
CD ==========================================================================
CD Formål:
CD Legger inn hele punktinformasjonen på angitte punkt
CD Ny verdi skriver over eksisterende verdi.
CD Verdi "" fjerner eksisterende PINFO.
CD Knutepunkt legges inn med LC_PutKp.
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    punkt_nr   i    Punktnummer (1 er første punkt)
CD char   *pinfo      i    PINFO-streng som skal legges inn
CD                         (Knutepunkt regnes ikke som pinfo)
CD short   sStatus    r    UT_TRUE = OK,
CD                         UT_FALSE = ikke utført (for lite plass tilgjengelig)
CD
CD Bruk:
CD sStatus = LC_PutPi(punkt_nr,pinfo);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_PutPi(long punkt_nr, const char *pinfo)
{
   short sNyLen, sGmlLen;
   long pt;
   unsigned long ulOfset;
   char *pszBuffer = NULL;
   short sStatus = UT_FALSE;


   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* Aktuell gruppe OK */

      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {    /* Lovlig punkt ? */

         /* Fjern blanke i starten */
         while (UT_IsSpace(*pinfo)) {
            ++pinfo;
         }
         sNyLen = (short)strlen(pinfo);
         
         if (sNyLen > 0) {
            /* Ta kopi av strengen */
         	pszBuffer = (char*)UT_MALLOC(sNyLen+1);
         	UT_StrCopy(pszBuffer,pinfo,sNyLen+1);
            pinfo = pszBuffer;

            /* Fjern blanke på slutten */
            UT_ClrTrailsp(pszBuffer);
            sNyLen = (short)strlen(pszBuffer);
         }

         /* Gammel lengde av PINFO */
         ulOfset = (Sys.pInfo+punkt_nr-1)->ulPiOfset;
         if (ulOfset == LC_INGEN_PINFO) {
            sGmlLen = 0;
         } else {
            sGmlLen = (short)strlen(Sys.pszPinfo+ulOfset);
         }

         /* --------------------- Blank ut PINFO */
         if (sNyLen == 0) {
            /* Punktet har PINFO fra før */
            if (sGmlLen > 0) {
               /* Merk at punktet ikke har PINFO */
               (Sys.pInfo+punkt_nr-1)->ulPiOfset = LC_INGEN_PINFO;
                  
               /* Pakk innholdet i bufferet */
               memmove(Sys.pszPinfo + ulOfset,
                       Sys.pszPinfo + ulOfset + sGmlLen + 1,
                       Sys.pGrInfo->ulPiLen - ulOfset - sGmlLen - 1);
 
               /* Oppdater ofset for resten av gruppen */
               /* if (Sys.pGrInfo->ulPiLen > ulOfset + sGmlLen + 1) { */
                  for (pt=punkt_nr; pt < Sys.pGrInfo->nko; ++pt) {
                     if ((Sys.pInfo+pt)->ulPiOfset != LC_INGEN_PINFO) {
                        (Sys.pInfo+pt)->ulPiOfset -= (sGmlLen + 1);
                     }
                  }
               /* } */

               /* Ny totallengde av PINFO i denne gruppen */
               Sys.pGrInfo->ulPiLen -= sGmlLen;
            }


         /* --------------------- Legg inn PINFO */
         } else {
         
            /* Sjekk om det blir plass til den nye PINFO'en */
            if (((long)Sys.pGrInfo->ulPiLen - (long)sGmlLen + (long)sNyLen) < LC_MAX_PINFO_BUFFER) {
               sStatus = UT_TRUE;
            
               /* Punktet har ikke PINFO fra før */
               if (sGmlLen == 0) {
                  /* Søk mot starten av gruppen for å finne slutten av forrige PINFO */
                  ulOfset = 0;
                  for (pt=punkt_nr-2; pt>=0; pt--) {
                     if ((Sys.pInfo+pt)->ulPiOfset != LC_INGEN_PINFO) {
                        /* ulOfset = (strlen(Sys.pszPinfo+(Sys.pInfo+pt)->ulPiOfset) + 1); */
                        ulOfset = (Sys.pInfo+pt)->ulPiOfset +
                                  strlen(Sys.pszPinfo+(Sys.pInfo+pt)->ulPiOfset) + 1;
                        break;  /* ---> avbryter for-løkka */
                     } /* endif */
                  } /* endfor */

                  /* Husk ofset */
                  (Sys.pInfo+punkt_nr-1)->ulPiOfset = ulOfset;

                  /* Flytt innholdet i bufferet */
                  memmove(Sys.pszPinfo + ulOfset + sNyLen + 1,
                          Sys.pszPinfo + ulOfset,
                          Sys.pGrInfo->ulPiLen - ulOfset);

                  /* Oppdater ofset for resten av gruppen */
                  /* if (Sys.pGrInfo->ulPiLen > ulOfset + sGmlLen + 1) { */
                     for (pt=punkt_nr; pt < Sys.pGrInfo->nko; ++pt) {
                        if ((Sys.pInfo+pt)->ulPiOfset != LC_INGEN_PINFO) {
                           (Sys.pInfo+pt)->ulPiOfset += (sNyLen + 1);
                        }
                     }
                  /* } */

                  /* Kopier inn strengen */
                  //strcpy(Sys.pszPinfo+ulOfset, pinfo);
                  UT_memcpy(Sys.pszPinfo+ulOfset, sNyLen+1, pinfo, sNyLen+1);

                  /* Ny totallengde */
                  Sys.pGrInfo->ulPiLen += (sNyLen + 1);

               /* Samme lengde, trenger ikke å flytte noe i buffer */
               } else if (sNyLen == sGmlLen) {
                  //strcpy(Sys.pszPinfo+ulOfset, pinfo);
                  UT_memcpy(Sys.pszPinfo+ulOfset, sNyLen+1, pinfo, sNyLen+1);

               /* Punktet har PINFO, men med annen lengde */
               } else {
                  /* Flytt innholdet i bufferet */
                  memmove(Sys.pszPinfo + ulOfset + sNyLen + 1,
                          Sys.pszPinfo + ulOfset + sGmlLen + 1,
                          Sys.pGrInfo->ulPiLen - ulOfset - sGmlLen - 1);

                  /* Kopier inn strengen */
                  //strcpy(Sys.pszPinfo+ulOfset, pinfo);
                  UT_memcpy(Sys.pszPinfo+ulOfset, sNyLen+1, pinfo, sNyLen+1);

                  /* Oppdater ofset for resten av gruppen */
                  /* if (Sys.pGrInfo->ulPiLen > ulOfset + sGmlLen + 1) { */
                     for (pt=punkt_nr; pt < Sys.pGrInfo->nko; ++pt) {
                        if ((Sys.pInfo+pt)->ulPiOfset != LC_INGEN_PINFO) {
                           (Sys.pInfo+pt)->ulPiOfset += (sNyLen - sGmlLen);
                        }
                     }
                  /* } */

                  /* Ny totallengde */
                  Sys.pGrInfo->ulPiLen += (sNyLen - sGmlLen);
               }
            }
 
            /* Husk at gruppen har PINFO */
            Sys.pGrInfo->info |= GI_PINFO;
         }

         /* Husk at gruppen er endret */
         Sys.sGrEndra = END_ENDRA;
         if (punkt_nr == Sys.lPibufPnr)  Sys.sPibufStatus = LC_PIBUF_TOM;

         /* Frigir midlertidig buffer */
         if (pszBuffer != NULL)  UT_FREE(pszBuffer);

      } else {                            /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_PutPi)",err().tx);
      }

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_PutPi)","");
   }

   return sStatus;
}


/*
AR-930609
CH LC_TestPi                                        Sjekk om punkt har PINFO
CD ==========================================================================
CD Formål:
CD Sjekker om et punkt har PINFO i en eller annen form.
CD (PINFO, KP, høyde.)
CD Høyde handteres ikke foreløpig.
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    punkt_nr   i    Punktnummer (1 er første punkt)
CD short   sTestHoyde i    Bryter for å si om høyde skal regnes med i sjekken.
CD short   sStatus    r    UT_TRUE=har "pinfo", UT_FALSE=har ikke "pinfo"
CD
CD Bruk:
CD sStatus = LC_TestPi(punkt_nr,UT_TRUE);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_TestPi(long punkt_nr,short sTestHoyde)
{

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                 /* Aktuell gruppe OK */
      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {   /* Lovlig punkt ? */

         /* ==> Høyde skal behandles */
         if (sTestHoyde) {
            /* if (Sys.pGrInfo->info & GI_NAH)  return UT_TRUE; */
            return UT_TRUE;
         }

         /* ==> Har PINFO */
         if ((Sys.pInfo+punkt_nr-1)->ulPiOfset != LC_INGEN_PINFO) {
            return UT_TRUE;

         /* ==> Har KP */
         } else if ((Sys.pInfo+punkt_nr-1)->sKp != 0) {
            return UT_TRUE;
         }

      } else {                           /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_GetPi)",err().tx);
      }
   }

   return UT_FALSE;
}


/*
AR-930609
CH LC_GetKp                                                    Get knutepunkt
CD ==========================================================================
CD Formål:
CD Henter knutepunktverdi i punktet.
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long   punkt_nr   i    Punktnummer (1 er første punkt)
CD short   kp_type    r    Knutepunkttype (1-4095)
CD                         (0 = punktet har ikke knutepunkt)
CD
CD Bruk:
CD kp = LC_GetKp(punkt_nr);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetKp(long punkt_nr)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE){                  /* Aktuell gruppe OK */

      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko){    /* Lovlig punkt ? */
         return  (Sys.pInfo+punkt_nr-1)->sKp;

      } else{                            /* Ulovlig punktnummer */
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_GetKp)",err().tx);
      }
   }

   return (0);
}


/*
AR-930609
CH LC_PutKp                                                    Put knutepunkt
CD ==========================================================================
CD Formål:
CD Legger inn knutepunktverdi i punktet. Ny verdi skrives over eksisterende
CD verdi. (Multiple KP er ikke mulig.)
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long   punkt_nr   i    Punktnummer (1 er første punkt)
CD short   kp         i    Knutepunkt (lovlig verdi 0 - SHRT_MAX)
CD                         kp == 0 fjerner knutepunkt.
CD
CD Bruk:
CD LC_PutKp(punkt_nr,kp);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_PutKp(long punkt_nr, short kp)
{
   if (Sys.GrId.lNr != INGEN_GRUPPE) {                 /* Aktuell gruppe OK */
      if (punkt_nr > 0 && punkt_nr <= Sys.pGrInfo->nko) {   /* Lovlig punkt ? */
         if (kp >= 0  &&  kp < SHRT_MAX) {
            if (kp != 0)  Sys.pGrInfo->info |= GI_KP;   /* Merk at gruppen har KP */

            (Sys.pInfo+punkt_nr-1)->sKp = kp;

            Sys.sGrEndra = END_ENDRA;
            if (punkt_nr == Sys.lPibufPnr)  Sys.sPibufStatus = LC_PIBUF_TOM;

            /* Husk at det finnes KP i filen */
            if (kp > 0) {
               if ( Sys.GrId.pFil->SosiNiv[1] < 3) {
                  Sys.GrId.pFil->SosiNiv[1] = 3;
               }
            }

         } else {
            UT_SNPRINTF(err().tx,LC_ERR_LEN," %d",kp);
            LC_Error(53,"(LC_PutKp)",err().tx);
         }

      } else {
         UT_SNPRINTF(err().tx,LC_ERR_LEN,"(%s) %ld",LC_GetGi(1),punkt_nr);
         LC_Error(51,"(LC_PutKp)",err().tx);
      }

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_PutKp)","");
   }
}


/*
AR-911106
CH LC_BerAreal                                 Beregn areal av aktuell FLATE
CD ==========================================================================
CD Formål:
CD Beregner arealet av aktuell gruppe hvis denne er flate.
CD Referansene brukes for arealberegningen.
CD Tar hensyn til fradrag for øyer.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   areal     u    Beregnet areal
CD
CD Bruk:
CD areal = LC_BerAreal();
   =============================================================================
*/
SK_EntPnt_FYBA double LC_BerAreal(void)
{
   short ngi;
   long nko;
   unsigned short info;
   #define  MAX_REFERANSE  20
   long ref_arr[MAX_REFERANSE];
   unsigned char ref_status[MAX_REFERANSE];
   long ant_ref;
   short s,retning;
   LC_GRF_STATUS GrfStat;
   LC_BGR BgrFlate,Bgr;

   double dTotalAreal = 0.0;
   double dDelAreal = 0.0;

   /* Husk gruppenummer for flaten */
   LC_GetGrNr(&BgrFlate);
   Bgr.pFil = BgrFlate.pFil;


   /* Behandle ytre avgrensing */
   LC_InitGetRefFlate(&GrfStat);
   ant_ref = LC_GetRefFlate(&GrfStat,GRF_YTRE,ref_arr,ref_status,MAX_REFERANSE);
   do {
      for (s=0; s<ant_ref; ++s) {
         Bgr.lNr = ref_arr[s];
         retning = (ref_status[s] & LC_MED_DIG)?
                                            HENT_FORRFRA : HENT_BAKFRA;
         dTotalAreal += LX_ArealGruppe(&Bgr,retning);
      }
      /* Les inn flaten igjen */    
      LC_RxGr(&BgrFlate,LES_OPTIMALT,&ngi,&nko,&info);

      if (ant_ref < MAX_REFERANSE)  break;

      ant_ref = LC_GetRefFlate(&GrfStat,GRF_YTRE,ref_arr,ref_status,MAX_REFERANSE);
   } while (ant_ref > 0);

   /* Beregn endelig areal innenfor yttergrensen */
   dTotalAreal = fabs(dTotalAreal / 2.0);


   /* Behandler indre avgrensing (øy) */
   LC_InitGetRefFlate(&GrfStat);
   ant_ref = LC_GetRefFlate(&GrfStat,GRF_INDRE,ref_arr,ref_status,MAX_REFERANSE);
   do {
      for (s=0; s<ant_ref; ++s) {
         if (ref_status[s] & GRF_START_OY) {
            dDelAreal = 0.0;

         } else if (ref_status[s] & GRF_SLUTT_OY) {
            /* Beregn endelig areal innenfor yttergrensen */
            dTotalAreal -= fabs(dDelAreal / 2.0);

         } else {
            Bgr.lNr = ref_arr[s];
            retning = (ref_status[s] & LC_MED_DIG)?
                                             HENT_FORRFRA : HENT_BAKFRA;
            dDelAreal += LX_ArealGruppe(&Bgr,retning);
         }
      }
      /* Les inn flaten igjen */    
      LC_RxGr(&BgrFlate,LES_OPTIMALT,&ngi,&nko,&info);

      if (ant_ref < MAX_REFERANSE)  break;

      ant_ref = LC_GetRefFlate(&GrfStat,GRF_INDRE,ref_arr,ref_status,MAX_REFERANSE);
   } while (ant_ref > 0);

   return  dTotalAreal;
}


/*
AR-900731
CH LX_BerArealGruppe             Beregn areal "arealandel" av aktuell gruppe
CD ==========================================================================
CD Formål:
CD Beregner areal av polygon angitt av yttergrensen av aktuell gruppe.
CD Forutsetter .FLATE og det er referansene som brukes i arealberegningen.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *  pBgr      i    Gruppepeker
CD short    retning   i    HENT_FORRFRA eller HENT_BAKFRA 
CD double   areal     u    Beregnet areal
CD
CD Bruk:
CD areal = LX_ArealGruppe(&Bgr,retning);
   =============================================================================
*/
static double LX_ArealGruppe(LC_BGR * pBgr,short retning)
{
   #define  ARR_LEN  50
   short ngi, gruppenavn;
   long nko, pt, antall, punkt;
   unsigned short info;
   short storbue;
   double a1,n1,a2,n2,a3,n3,radius,as,ns,fi,dfi;
   double n_arr[ARR_LEN],a_arr[ARR_LEN];
   double a_forrige=0.0, n_forrige=0.0, a, n;
   short forste;
   double areal_seg = 0.0; 
   double areal_poly = 0.0;

   gruppenavn = LC_RxGr(pBgr,LES_OPTIMALT,&ngi,&nko,&info);
   if (nko > 0) {
      if (gruppenavn == L_BUE) {   /* .BUE */
         if (LC_GetBue(retning,&a1,&n1,&a2,&n2,&radius,&storbue)){
            areal_poly += (a1 - a2) * (n1 + n2);
            /* Sektoren */
            if (GM_KonvBue(a1,n1,a2,n2,radius,storbue,
                           &as,&ns,&fi,&dfi)){
               areal_seg += (radius*radius*(dfi-sin(dfi)));
            }
         }

      } else if (gruppenavn == L_BUEP){   /* .BUEP */
         if (LC_GetBuep(retning,&a1,&n1,&a2,&n2,&a3,&n3)) {
            areal_poly += (a1 - a3) * (n1 + n3);
            /* Sektoren */
            if (GM_KonvBuep(a1,n1,a2,n2,a3,n3,
                            &as,&ns,&radius,&fi,&dfi)) {
               areal_seg += (radius*radius*(dfi-sin(dfi)));
            }
         }

      } else if (gruppenavn == L_SIRKEL) {   /* .SIRKEL */
         if (LC_GetSirkel(&as,&ns,&radius)) {
            /* Dobbelt areal av sirkelen */
            areal_seg = 2.0 * PI * radius * radius;
         }

      } else if (gruppenavn == L_SIRKELP) {   /* .SIRKELP */
         if (LC_GetSirkelp(&a1,&n1,&a2,&n2,&a3,&n3)) {
            if (GM_KonvSirkelp(a1,n1,a2,n2,a3,n3,
                            &as,&ns,&radius,&fi,&dfi)) {
               /* Dobbelt areal av sirkelen */
               areal_seg = 2.0 * PI * radius * radius;
            }
         }

      } else {                    /* Annen gruppe */
         punkt = (retning == HENT_FORRFRA)?  1 : nko;
         forste = UT_TRUE;

         do {                       /* Beregn areal */
            LC_GetArrayTK(retning,ARR_LEN,punkt,a_arr,n_arr,&antall);/* Henter */
            if (antall > 0) {
               if (forste) {
                  a_forrige = a_arr[0];
                  n_forrige = n_arr[0];
                  forste = UT_FALSE;
               }
               for (pt=1; pt<antall; ++pt) {
                  a = a_arr[pt];
                  n = n_arr[pt];
                  areal_poly += (a_forrige - a) * (n_forrige + n);
                  a_forrige = a;
                  n_forrige = n;
               }

               if (retning == HENT_FORRFRA) {
                  punkt += (antall-1);
                  if (punkt >= nko)   antall = 0;
               } else{
                  punkt -= (antall-1);
                  if (punkt <= 1)   antall = 0;
               }
            }
         } while (antall == ARR_LEN);
      }
   }

   return  (areal_poly + areal_seg);
}


/*
AR-911106
CH LC_BerLengde                   Beregn horisontal lengde av aktuell gruppe
CD ==========================================================================
CD Formål:
CD Beregn horisontal lengde av aktuell gruppe.
CD Tar ikke hensyn til høyde/dybde.
CD Referansene brukes IKKE i beregningen.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   lengde    u    Beregnet lengde
CD
CD Bruk:
CD areal = LC_BerLengde();
=============================================================================
*/
SK_EntPnt_FYBA double LC_BerLengde(void)
{
   short sfeil;
   long l;
   double a1,n1,a2,n2,rx,as,ns,fi,dfi;
   double lengde = 0.0;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {
      if (Sys.pGrInfo->gnavn == L_LINJE  ||  Sys.pGrInfo->gnavn == L_KURVE) {
         for (l=2; l<=Sys.pGrInfo->nko; ++l) {
            LC_GetTK(l-1,&a1,&n1);
            LC_GetTK(l,&a2,&n2);
            lengde += sqrt((n2-n1)*(n2-n1)+(a2-a1)*(a2-a1));
         }

                  // Handterer "bue"
      } else if (Sys.pGrInfo->gnavn == L_BUE  ||  Sys.pGrInfo->gnavn == L_BUEP ||
            Sys.pGrInfo->gnavn == L_SIRKEL  ||  Sys.pGrInfo->gnavn == L_SIRKELP) {

         if (LC_GetBuePar(HENT_FORRFRA,&as,&ns,&rx,&fi,&dfi,&sfeil)) {
            lengde = fabs (rx * dfi);
         }
      }
   }

   return lengde;
}


/*
AR-911106
CH LC_BerLengde3D                       Beregn skrå lengde av aktuell gruppe
CD ==========================================================================
CD Formål:
CD Beregn skrå lengde av aktuell gruppe.
CD Krever at det finnes høyde/dybde i alle punkt.
CD Referansene brukes IKKE i beregningen.
CD Beregner bare for LINJE og KURVE.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   lengde    u    Beregnet lengde
CD bool     beregnet  r    Status som viser om lengde er beregnet
CD
CD Bruk:
CD beregnet = LC_BerLengde3D(&skraa_lengde);
=============================================================================
*/
SK_EntPnt_FYBA bool LC_BerLengde3D(double *skraa_lengde)
{
   long s;
   double a1,n1,a2,n2,h1,h2,da,dn,dh;
  
   bool beregnet = false;

   *skraa_lengde = 0.0;
   

   if (Sys.GrId.lNr != INGEN_GRUPPE)
   {

      // Beregn skrå lengde
      if (Sys.pGrInfo->gnavn == L_LINJE  ||  Sys.pGrInfo->gnavn == L_KURVE) 
      {
         // Husk om gruppen har høyde/dybde
         beregnet = ((Sys.pGrInfo->info & GI_NAH) || (Sys.pGrInfo->info & GI_NAD))?  true : false;

         for (s=2; beregnet && s<=Sys.pGrInfo->nko; s++)
         {
            LC_GetTK(s-1,&a1,&n1);
            if (Sys.pGrInfo->info & GI_NAD)
            {
               h1 = LC_GetDybde(s-1);
            }
            else
            {
               h1 = LC_GetHoyde(s-1);
            }

            LC_GetTK(s,&a2,&n2);
            if (Sys.pGrInfo->info & GI_NAD)
            {
               h2 = LC_GetDybde(s);
            }
            else
            {
               h2 = LC_GetHoyde(s);
            }


            if (h1 != HOYDE_MANGLER  && h2 != HOYDE_MANGLER)
            {
               da = a2 - a1;
               dn = n2 - n1;
               dh = h2 - h1;
               (*skraa_lengde) += sqrt(dn*dn + da*da + dh*dh);
            }
            else
            {
               beregnet = false;
            }
         }
      }
   }

   return beregnet;
}


/*
AR:2009-04-28
CH LC_BerAvgrensLengde                Beregn lengden av avgrensning av FLATE
CD ==========================================================================
CD Formål:
CD Beregn lengden av avgrensningen av aktuell gruppe hvis denne er flate.
CD Både indre og ytre avgrensning beregnes.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   lengde     u    Beregnet areal
CD
CD Bruk:
CD lengde = LC_BerAvgrensLengde();
=============================================================================
*/
SK_EntPnt_FYBA double LC_BerAvgrensLengde(void)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_BGR BgrFlate;
   double dSumLengde = 0.0;

   if (Sys.pGrInfo->info & GI_REF)
   {        
      // Husk gruppenummer for flaten
      LC_GetGrNr(&BgrFlate);

      LC_POLYGON Polygon;
      LC_POL_InitPolygon(&Polygon);
      LC_POL_GetRef(&Polygon);

      LC_POL_ELEMENT * pPE;
      // Ytre avgrensning
      for(pPE = Polygon.HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
         LC_RxGr(&pPE->Bgr,LES_OPTIMALT,&ngi,&nko,&info);
         dSumLengde += LC_BerLengde();
      }

      // Indre avgrensning
      LC_OY_ELEMENT * pOE;
      for (pOE = Polygon.OyOA.pForsteOE; pOE != NULL; pOE = pOE->pNesteOE) {
         for (pPE = pOE->PO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
            LC_RxGr(&pPE->Bgr,LES_OPTIMALT,&ngi,&nko,&info);
            dSumLengde += LC_BerLengde();
         }
      }

      // Frigi allokerte kjeder
      LC_POL_FrigiPolygon(&Polygon);

      // Les inn flaten igjen
      LC_RxGr(&BgrFlate,LES_OPTIMALT,&ngi,&nko,&info);
   }

   return  dSumLengde;
}


/*
AR:2009-04-28
CH LC_BerIndreAvgrensLengde      Beregn lengden av indre avgrensning av FLATE
CD ==========================================================================
CD Formål:
CD Beregn lengden av indre avgrensningen av aktuell gruppe hvis denne er flate.
CD Bare indre avgrensning beregnes.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   lengde     u    Beregnet lengde
CD
CD Bruk:
CD lengde = LC_BerIndreAvgrensLengde();
=============================================================================
*/
SK_EntPnt_FYBA double LC_BerIndreAvgrensLengde(void)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_BGR BgrFlate;
   double dSumLengde = 0.0;

   if (Sys.pGrInfo->info & GI_REF)
   {        
      // Husk gruppenummer for flaten
      LC_GetGrNr(&BgrFlate);

      LC_POLYGON Polygon;
      LC_POL_InitPolygon(&Polygon);
      LC_POL_GetRef(&Polygon);

      // Indre avgrensning
      LC_OY_ELEMENT * pOE;
      LC_POL_ELEMENT * pPE;
      for (pOE = Polygon.OyOA.pForsteOE; pOE != NULL; pOE = pOE->pNesteOE) {
         for (pPE = pOE->PO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
            LC_RxGr(&pPE->Bgr,LES_OPTIMALT,&ngi,&nko,&info);
            dSumLengde += LC_BerLengde();
         }
      }

      // Frigi allokerte kjeder
      LC_POL_FrigiPolygon(&Polygon);

      // Les inn flaten igjen
      LC_RxGr(&BgrFlate,LES_OPTIMALT,&ngi,&nko,&info);
   }

   return  dSumLengde;
}



/*
AR:2009-04-28
CH LC_BerYtreAvgrensLengde      Beregn lengden av ytre avgrensning av FLATE
CD ==========================================================================
CD Formål:
CD Beregn lengden av ytre avgrensningen av aktuell gruppe hvis denne er flate.
CD Bare ytre avgrensning beregnes.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   lengde     u    Beregnet lengde
CD
CD Bruk:
CD lengde = LC_BerYtreAvgrensLengde();
=============================================================================
*/
SK_EntPnt_FYBA double LC_BerYtreAvgrensLengde(void)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_BGR BgrFlate;
   double dSumLengde = 0.0;

   if (Sys.pGrInfo->info & GI_REF)
   {        
      // Husk gruppenummer for flaten
      LC_GetGrNr(&BgrFlate);

      LC_POLYGON Polygon;
      LC_POL_InitPolygon(&Polygon);
      LC_POL_GetRef(&Polygon);

      LC_POL_ELEMENT * pPE;
      // Ytre avgrensning
      for(pPE = Polygon.HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
         LC_RxGr(&pPE->Bgr,LES_OPTIMALT,&ngi,&nko,&info);
         dSumLengde += LC_BerLengde();
      }

      // Frigi allokerte kjeder
      LC_POL_FrigiPolygon(&Polygon);

      // Les inn flaten igjen
      LC_RxGr(&BgrFlate,LES_OPTIMALT,&ngi,&nko,&info);
   }

   return  dSumLengde;
}


/*
AR-911106
CH LC_DumpTab                               Dump interne tabeller til stderr
CD ==========================================================================
CD Formål:
CD Dump interne tabeller til stderr
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD
CD Bruk:
CD LC_DumpTab();
   =============================================================================
*/
SK_EntPnt_FYBA void LC_DumpTab(void)
{
   short ngi,s;
   long nko;
   unsigned short info;
   LC_BGR Bgr,AktBgr;

   LC_GetGrNr(&AktBgr);

   UT_FPRINTF(stderr,"\n=================================================\n");
   UT_FPRINTF(stderr,"Dump av interne tabeller i FYBA\n");
   UT_FPRINTF(stderr,"=================================================\n");

   UT_FPRINTF(stderr,"\nLC_INGEN_PINFO = %lu\n", LC_INGEN_PINFO);

   UT_FPRINTF(stderr,"\n    Snr    sosi_st     rb_st  rb_fgr  rb_ngr gna ngi  nko info    GiLen    PiLen\n");
   LC_InitNextBgr(&Bgr);

   /* Alle gruppene i framgrunn */
   while (LC_NextBgr(&Bgr,LC_FRAMGR)) {
      LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
      UT_FPRINTF(stderr,"%7ld: %9lld %9lld %7ld %7ld %3hd %3hd %5ld %4hx %8lu %8lu\n",
           Sys.GrId.lNr,
           Sys.pGrInfo->sosi_st,
           Sys.pGrInfo->rb_st,
           Sys.pGrInfo->rb_forrige_gr,
           Sys.pGrInfo->rb_neste_gr,
           Sys.pGrInfo->gnavn,
           Sys.pGrInfo->ngi,
           Sys.pGrInfo->nko,
           Sys.pGrInfo->info,
           Sys.pGrInfo->ulGiLen,
           Sys.pGrInfo->ulPiLen);
      /* List ut PINFO-pekerene */
      if (ngi > 0) {
         for (s=1; s<=Sys.pGrInfo->nko; ++s) {
            if ((Sys.pInfo+s-1)->ulPiOfset != LC_INGEN_PINFO) {
               UT_FPRINTF(stderr,"PI ofset %4hd: %8lu\n", s, (Sys.pInfo+s-1)->ulPiOfset);
            }
         }
      }
   }

   if (AktBgr.lNr != INGEN_GRUPPE) {
      LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);
   }
}
