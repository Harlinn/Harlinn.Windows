/* === 920909 ============================================================ */
/*  STATENS KARTVERK  -  FYSAK-PC                                          */
/*  Fil: fylb.c                                                            */
/*  Ansvarlig: Andreas Røstad                                              */
/*  Innhold: Bufferhandteringsrutiner for fysak-pc                         */
/* ======================================================================= */

#include "fyba.h"
#include "fybax.h"

#include <time.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <Windows.h>



/* Globale strukturer */
extern LC_SYSTEMADM Sys;
extern volatile short fyba_initiert;    /* Bryter for å vise at LC_Init er utført */


/*  Funksjonsdefinisjoner for interne funksjoner */
static void  LB_WriteBlank(FILE *fil,short sTegnsett,UT_INT64 ltilpos);
static char *LB_GetParameter(LB_LESEBUFFER *plb);
static short LB_TestFyll(const char *pszTx);
static void  LB_WriteRb(void);
static short LB_FlyttGrTilSlutt(LC_FILADM *pFil, UT_INT64 start, UT_INT64 *neste);
static short LB_RensOmkrets(LC_POL_OMKR * pPO,long lAktSnr,long lFraSnr);
static void LR_TestEndreBuepTilKurve(double dDeltaFi);


/*
AR-911011
CH LC_GetGrFi                                              Hent gruppe-filnr
CD =============================================================================
CD Formål:
CD Henter peker til FilAdm for aktuell gruppe.
CD
CD Parametre:
CD Type         Navn    I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_FILADM * *ppFil    u   Peker til FilAdm-peker
CD short        status   r   UT_TRUE = OK, UT_FALSE = Ingen aktuell gruppe
CD
CD Bruk:
CD     status = LC_GetGrFi(&pFil);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_GetGrFi(LC_FILADM **ppFil)
{

   /* Er det noen aktuell gruppe? */
   if (Sys.GrId.lNr != INGEN_GRUPPE) {
      *ppFil = Sys.GrId.pFil;
      return UT_TRUE;
   }

   /* Ingen aktuell gruppe */
   return UT_FALSE;
}


/*
AR-911008
CH LC_InitNextFil                                     Initier finn neste fil
CD ==========================================================================
CD Formål:
CD Initierer pFil for bruk i finn neste fil.
CD
CD Parametre:
CD Type           Navn   I/U  Forklaring
CD ------------------------------------------------------------------------
CD LC_FILADM    **ppFil    u   Peker til FilAdm-peker
CD
CD Bruk:
CD     LC_InitNextFil(&pFil)
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_InitNextFil(LC_FILADM **ppFil)
{
   *ppFil = (LC_FILADM *)-1L;
}


/*
AR-911008
CH LC_NextFil                                                 Finn neste fil
CD ==========================================================================
CD Formål:
CD Finn neste fil i aktuell base.
CD
CD Parametre:
CD Type           Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM    **ppFil   iu   Peker til FilAdm-peker
CD unsigned short usLag    i   Velg hvilke "lag" det skal søkes i.
CD                               LC_FRAMGR, LC_BAKGR og /eller LC_SEKV
CD                               (Bruk "|" for å kombinere.)
CD short          sStatus  r   Status  UT_TRUE=OK, UT_FALSE=ingen flere funnet
CD
CD Bruk:
CD     LC_FILADM *pFil;
CD               Denne løkka går gjennom alle framgrunns-filene i basen
CD     LC_InitNextFil(&pFil)
CD     while (LC_NextFil(&pFil,LC_FRAMGR)) {
CD       pszFilNavn = LC_GetFiNa(pFil);
CD       .
CD       Behandle filnavnet
CD       .
CD     }
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_NextFil(LC_FILADM **ppFil,unsigned short usLag)
{
   LC_FILADM *pF;

   /* Første gang */
   if (*ppFil == (void *)-1L) {
      pF = Sys.pAktBase->pForsteFil;

   } else {
      /* LO_TestFilpeker(*ppFil,"LC_NextFil"); */
      LO_TestFilpeker(*ppFil,"NextFil");
      pF = (*ppFil)->pNesteFil;
   }

   /* Er det flere filer i basen? */
   while (pF != NULL) {
      /* Er filen i rett lag? */ 
      if (pF->usLag & usLag) {
         *ppFil = pF;
         return UT_TRUE;

      /* Ikke rett lag, fortsett til neste fil */
      } else {
         pF = pF->pNesteFil;
      }
   }

   return UT_FALSE;
}


/*
AR-911001
CH LC_InitNextBgr                                  Initier finn neste gruppe
CD ==========================================================================
CD Formål:
CD Initierer Bgr for bruk i finn neste gruppe.
CD
CD Parametre:
CD Type           Navn   I/U  Forklaring
CD ------------------------------------------------------------------------
CD LC_BGR *        pBgr    iu  Peker til gruppestruktur
CD
CD Bruk:
CD     LC_InitNextBgr(&Bgr)
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_InitNextBgr(LC_BGR * pBgr)
{
   pBgr->pFil = Sys.pAktBase->pForsteFil;
   pBgr->lNr = -1L;
}


/*
AR-911003
CH LC_NextBgr                                              Finn neste gruppe
CD ==========================================================================
CD Formål:
CD Finn neste gruppe i aktuell base.
CD Sekvensielle filer blir ikke håndtert.
CD
CD Parametre:
CD Type           Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *        pBgr    iu   Peker til gruppestruktur der gruppenummer lagres
CD unsigned short usLag    i   Velg hvilke "lag" det skal søkes i.
CD                               LC_FRAMGR og /eller LC_BAKGR
CD                               (Bruk "|" for å kombinere.)
CD short          sStatus  r   Status  UT_TRUE=OK, UT_FALSE=ingen flere grupper
CD
CD Bruk:
CD     LC_BGR Bgr;
CD               Denne løkka går gjennom alle framgrunns-gruppene i basen
CD     LC_InitNextBgr(&Bgr);
CD     while (LC_NextBgr(&Bgr,LC_FRAMGR)) {
CD       gnavn = LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
CD       .
CD       Behandle gruppen
CD       .
CD     }
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_NextBgr(LC_BGR * pBgr,unsigned short usLag)
{
   LC_GRTAB_LINJE * grtp;


   /* Er det noen fil i basen? */
   while (pBgr->pFil != NULL) {
      LO_TestFilpeker(pBgr->pFil,"NextBgr");
      /* Er filen i rett lag? */ 
      if (pBgr->pFil->usLag & usLag) {
         /* Flere grupper i aktuell fil? */
         while (pBgr->lNr < pBgr->pFil->lAntGr -1) {
            pBgr->lNr++;

            /*
             * Sjekk gruppetabellen om gruppen er sletta
             *
             * (Permanent sletta, eller vanlig NGIS-modus, og
             *  "NGIS-gruppe" merka som sletta.)
             */

            grtp = LI_GetGrt(pBgr->pFil,pBgr->lNr);
            if (! (grtp->ngi == 0  ||
                   (Sys.sNGISmodus == NGIS_NORMAL  &&
                   grtp->info & GI_NGIS  &&
                   grtp->info & GI_SLETTA))) {

               return UT_TRUE;
            }
         }
      }

      /* Neste fil i basen */
      pBgr->pFil = pBgr->pFil->pNesteFil;
      pBgr->lNr = -1L;
   }

   return UT_FALSE;
}


/*
AR-911003
CH LC_InqAntFiler                                  Finn antall filer i basen
CD ==========================================================================
CD Formål:
CD Finn antall filer i aktuell base.
CD
CD Parametre:
CD Type           Navn    I/U  Forklaring
CD -------------------------------------------------------------------
CD unsigned short usLag    i   Velg hvilke "lag" det skal søkes i.
CD                               LC_FRAMGR og /eller LC_BAKGR
CD                               (Bruk "|" for å kombinere.)
CD short          sAntall  r   Antall filer i aktuell base.
CD
CD Bruk:
CD    Finner antall framgrunnsfiler i basen
CD    sAntall = LC_InqAntFiler(LC_FRAMGR);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_InqAntFiler(unsigned short usLag)
{
   short sAntall = 0;

   if (fyba_initiert == 1)
   {
      if (Sys.pAktBase != NULL)
      {
         if (usLag & LC_FRAMGR)  sAntall += Sys.pAktBase->sAntFramgrFil;
         if (usLag & LC_BAKGR)   sAntall += Sys.pAktBase->sAntBakgrFil;
      }
   }

   return sAntall;
}


/*
AR-911001
CH LC_GetGrNr                                             Hent gruppe-nummer
CD ==========================================================================
CD Formål:
CD Henter gruppenummer for aktuell gruppe.
CD
CD Parametre:
CD Type    Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR * pBgr      iu   Peker til gruppestruktur der gruppenummer lagres
CD short   status    r    Status  UT_TRUE=OK, UT_FALSE=ingen aktuell gruppe
CD
CD Bruk:
CD     status = LC_GetGrNr(&Bgr)
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetGrNr(LC_BGR * pBgr)
{
   pBgr->pFil = Sys.GrId.pFil;
   pBgr->lNr = Sys.GrId.lNr;

   /* Er det noen aktuell gruppe? */
   if (Sys.GrId.lNr != INGEN_GRUPPE)  return UT_TRUE;

   /* Ingen aktuell gruppe */
   return UT_FALSE;
}


/*
AR-911001
CH LC_GetGrPara                                        Hent gruppe-parametre
CD ==========================================================================
CD Formål:
CD Henter diverse opplysninger om aktuell gruppe.
CD
CD Parametre:
CD Type    Navn   I/U   Forklaring
CD-------------------------------------------------------------------------
CD short   *ngi    u    Antall linjer GINFO
CD long    *nko    u    Antall koordinater
CD short   *info   u    Diverse informasjon. En sum av følgende:
CD                        GI_PINFO = gruppen har PINFO
CD                        GI_NAH   = gruppen har høyde informasjon (..NØH)
CD                        GI_NAD   = gruppen har dybde informasjon (..NØD)
CD                        GI_KP    = gruppen har knutepunkt (...KP n)
CD                        GI_REF   = gruppen har referanser (.. :n)
CD                        GI_OY_REF= gruppen har referanser med øy
CD                        GI_NGIS      = gruppen er tatt ut fra NGIS for oppdat.
CD                        GI_SLETTA    = gruppen er sletta (merka som sletta)
CD                        GI_READ_ONLY = gruppen kan ikke endres.
CD
CD short   gnavn   r    Gruppenavn. (Se under $LENKE<LC_RxGr>)
CD
CD Bruk:
CD     gnavn = LC_GetGrPara(&ngi,&nko,&info);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetGrPara(short *ngi,long *nko,unsigned short *info)
{
   /* Feil ==> Ingen aktuell gruppe */
   if (Sys.GrId.lNr == INGEN_GRUPPE) {
      *ngi = 0;
      *nko = 0;
      return  INGEN_GRUPPE;

   /* Lovlig gruppe */
   } else {
      *ngi = Sys.pGrInfo->ngi;
      *nko = Sys.pGrInfo->nko;
      *info = Sys.pGrInfo->info;
      return  Sys.pGrInfo->gnavn;
   }

}


/*
AR-900107
CH LC_GetGrParaBgr                           Hent gruppe-parametre for gruppe
CD =============================================================================
CD Formål:
CD Henter diverse opplysninger om gitt gruppenummer.
CD
CD Parametre:
CD Type            Navn I/U  Forklaring
CD------------------------------------------------------------------------------
CD LC_BGR *         pBgr  i   Gruppenummer det ønskes opplysninger om.
CD short          *ngi   u   Antall linjer GINFO  (0=sletta eller ulovlig nummer)
CD long           *nko   u   Antall koordinater
CD unsigned short *info  u   Diverse informasjon. En sum av følgende:
CD                           GI_PINFO = gruppen har PINFO
CD                           GI_NAH   = gruppen har høyde informasjon (..NØH)
CD                           GI_NAD   = gruppen har døbde informasjon (..NØD)
CD                           GI_KP    = gruppen har knutepunkt (...KP n)
CD                           GI_REF   = gruppen har referanser (.. :n)
CD                           GI_OY_REF= gruppen har referanser med øy
CD                           GI_NGIS      = gruppen er tatt ut fra NGIS for oppdat.
CD                           GI_SLETTA    = gruppen er sletta (merka som sletta)
CD                           GI_READ_ONLY = gruppen kan ikke endres.
CD short           gnavn r   Gruppenavn. (Se under $LENKE<LC_RxGr>)
CD
CD Bruk:
CD     gnavn = LC_GetGrParaBgr(pBgr,&ngi,&nko,&info,&snr);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_GetGrParaBgr(LC_BGR * pBgr,short *ngi,long *nko,unsigned short *info)
{
   LC_GRTAB_LINJE * grtp;

   /* Aktuell gruppe */
   if (pBgr->pFil == Sys.GrId.pFil  &&  pBgr->lNr == Sys.GrId.lNr) {
      *ngi = Sys.pGrInfo->ngi;
      *nko = Sys.pGrInfo->nko;
      *info = Sys.pGrInfo->info;
      return  Sys.pGrInfo->gnavn;        /* ==> retur */
   }

   /* Hent fra gruppetabellen */
   LO_TestFilpeker(pBgr->pFil,"GetGrParaBgr");
   grtp = LI_GetGrt(pBgr->pFil,pBgr->lNr);

   /* Sjekk om NGIS-gruppe og merka som sletta */
   if (Sys.sNGISmodus == NGIS_NORMAL  &&    /* Vanlig modus, og         */
       grtp->info & GI_NGIS  &&      /* oppdater NGIS, og        */
       grtp->info & GI_SLETTA) {    /* merka som sletta         */

      *ngi = 0;
      *nko = 0;

   } else {
      *ngi = grtp->ngi;
      *nko = grtp->nko;
   }

   *info = grtp->info;

   return  grtp->gnavn;        /* ==> retur */
}


/*
AR-900107
CH LC_GetObjtypeBgr                                             Hent objekttype
CD =============================================================================
CD Formål:
CD Henter objekttype for gitt gruppenummer.
CD
CD Parametre:
CD Type    Navn       I/U  Forklaring
CD------------------------------------------------------------------------------
CD LC_BGR *pBgr        i   Gruppenummer det ønskes opplysninger om.
CD char   *pszObjtype  r   OBJTYPE
CD                         NULL hvis gruppen ikke finnes
CD
CD Bruk:
CD pszObjtype = LC_GetObjtypeBgr(pBgr);
=============================================================================
*/
SK_EntPnt_FYBA const char *LC_GetObjtypeBgr(LC_BGR * pBgr)
{
   LC_GRTAB_LINJE * grtp;

   /* Aktuell gruppe */
   if (pBgr->pFil == Sys.GrId.pFil  &&  pBgr->lNr == Sys.GrId.lNr) {
      return  Sys.pGrInfo->szObjtype;        /* ==> retur */
   }

   /* Hent fra gruppetabellen */
   LO_TestFilpeker(pBgr->pFil,"GetObjtypeBgr");
   grtp = LI_GetGrt(pBgr->pFil,pBgr->lNr);

   /* Sjekk om NGIS-gruppe og merka som sletta */
   if (Sys.sNGISmodus == NGIS_NORMAL  &&    /* Vanlig modus, og         */
      grtp->info & GI_NGIS  &&      /* oppdater NGIS, og        */
      grtp->info & GI_SLETTA)     /* merka som sletta         */
   {
      return "";           /* ==> retur */
   }

   return  grtp->szObjtype;        /* ==> retur */
}


/*
AR-911001
CH LC_RsGr                                           Les gruppe sekvensielt
CD ==========================================================================
CD Formål:
CD Leser en datagruppe fra ekstern SOSI-fil inn i aktuell gruppe i ringbuffer.
CD Rutinen tilsvarer put fra brukerprogram inn i ringbufferet, men rutinen
CD tildeler selv nødvendig plass..
CD Gruppen beholder serienummer tildelt i LC_NyGr.
CD Brukerindeks og geografisk-indeks blir ikke oppdatert.
CD (Dette skjer først når gruppen skrives til basen.)
CD
CD Parametre:
CD Type             Navn   I/U  Forklaring
CD --------------------------------------------------------------------------
CD short           *rstat  iu   Lesestatus
CD                                Inn: 1=Les fra starten, 0=Les neste
CD                                Ut:  0=OK, -1=slutten av filen er nådd
CD LC_FILADM       *pFil    i   Peker til FilAdm
CD short           *ngi     u   Antall linjer GINFO
CD long            *nko     u   Antall koordinater
CD unsigned short  *info    u   Diverse informasjon. En "sum" av følgende:
CD                          GI_PINFO     = gruppen har PINFO
CD                          GI_NAH       = gruppen har høyde informasjon (..NØH)
CD                          GI_NAD       = gruppen har dybde informasjon (..NØD)
CD                          GI_KP        = gruppen har knutepunkt (...KP n)
CD                          GI_REF       = gruppen har referanser (.. eller ..REF)
CD                          GI_OY_REF    = gruppen har referanser med øy
CD                          GI_NGIS      = gruppen er tatt ut fra NGIS for oppdat.
CD                          GI_SLETTA    = gruppen er sletta (merka som sletta)
CD                          GI_READ_ONLY = gruppen kan ikke endres.
CD long             gml_snr u    Serienummer gruppen hadde på ekstern fil
CD short            gnavn   r    Gruppenavn. (Se under $LENKE<LC_RxGr>)
CD
CD Bruk:
CD     gnavn = LC_RsGr(&rstat,pFil,&ngi,&nko,&info,&gml_snr);
CD     if (info & GI_PINFO)        (gruppen har PINFO)
CD         ;
CD     if (info & GI_KP)           (gruppen har KP)
CD         ;
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_RsGr(short *rstat,LC_FILADM *pFil,short *ngi,long *nko,
				  unsigned short *info,long *gml_snr)
{
   short siste;
   long  snr;
   UT_INT64 slutt;

   /* LO_TestFilpeker(pFil,"LC_RsGr"); */
   LO_TestFilpeker(pFil,"RsGr");

   if (Sys.GrId.lNr == INGEN_GRUPPE) {      /* Feil ==> Ingen aktuell gruppe */
      LC_Error(31,"(LC_RsGr)","");

                                           /* Feil ==> Ulovlig ekstern fil */
   } else if (pFil->usLag != LC_SEKV) {
      LC_Error(32,"(LC_RsGr)","");
      *ngi = Sys.pGrInfo->ngi;
      *nko = Sys.pGrInfo->nko;
      *info = Sys.pGrInfo->info;

   } else {                                 /* Lovlig gruppe */
      Sys.sPibufStatus = LC_PIBUF_TOM;
      Sys.sGrEndra = END_KOPI;
      if (*rstat == 1) {
          pFil->n64AktPos = 0L;      /* Sett ny startposisjon */
      }

      /* Husk snr */
      snr = LC_GetSn();  

      /* Les fra ekstern fil */
      siste = LB_RGru(pFil,pFil->n64AktPos,&slutt);

      /* Snr fra ekstern fil */
      *gml_snr = LC_GetSn();

      /* Legg tilbake SNR */
      LC_PutSn(snr);

      if (siste) {
          *rstat = -1;

      } else {
          *rstat = 0;
          pFil->n64AktPos = slutt;
          *ngi = Sys.pGrInfo->ngi;
          *nko = Sys.pGrInfo->nko;
          *info = Sys.pGrInfo->info;
      }
   }
   return  Sys.pGrInfo->gnavn;
}


/*
AR-911001
CH LC_RsHode                                        Les filhode sekvensiellt
CD ==========================================================================
CD Formål:
CD Leser et filhode fra ekstern SOSI-fil inn i aktuell gruppe i ringbuffer.
CD Rutinen tilsvarer put fra brukerprogram inn i ringbufret, men rutinen
CD tildeler selv nødvendig plass i RB.
CD Denne rutinen er stort sett lik LC_RsGr, men LC_RsHode forandrer
CD ikke aktuell filposisjon på den sekvensielle filen.
CD Gruppen beholder serienummer hodet hadde på SOSI-filen.
CD
CD Parametre:
CD Type             Navn   I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM       *pFil    i   Peker til FilAdm
CD short           *ngi     u   Antall linjer GINFO
CD long            *nko     u   Antall koordinater
CD unsigned short  *info    u   Diverse informasjon. En "sum" av følgende:
CD                          GI_PINFO = gruppen har PINFO
CD                          GI_NAH   = gruppen har høyde informasjon (..NØH)
CD                          GI_NAD   = gruppen har dybde informasjon (..NØD)
CD                          GI_KP    = gruppen har knutepunkt (...KP n)
CD                          GI_REF   = gruppen har referanser (.. :n)
CD                          GI_OY_REF= gruppen har referanser med øy
CD short            gnavn   r    Gruppenavn. (Se under $LENKE<LC_RxGr>)
CD
CD Bruk:
CD     gnavn = LC_RsHode(pFil,&ngi,&nko,&info);
   =============================================================================
*/
short LC_RsHode(LC_FILADM *pFil,short *ngi,long *nko,unsigned short *info)
{
   UT_INT64  slutt;

   /* LO_TestFilpeker(pFil,"LC_RsHode"); */
   LO_TestFilpeker(pFil,"RsHode");

   if (Sys.GrId.lNr == INGEN_GRUPPE){          /* Feil ==> Ingen aktuell gruppe */
      LC_Error(31,"(LC_RsHode)","");

                                           /* Feil ==> Ulovlig ekstern fil */
   } else if (pFil->usLag != LC_SEKV) {
      LC_Error(32,"(LC_RsHode)","");
      *ngi = Sys.pGrInfo->ngi;
      *nko = Sys.pGrInfo->nko;
      *info = Sys.pGrInfo->info;

   } else {                                /* Lovlig gruppe */

                                           /* Les fra ekstern fil */
      LB_RGru(pFil,0,&slutt);

      *ngi = Sys.pGrInfo->ngi;
      *nko = Sys.pGrInfo->nko;
      *info = Sys.pGrInfo->info;
      Sys.sGrEndra = END_KOPI;
   }

   return  Sys.pGrInfo->gnavn;
}


/*
AR-930610
CH LC_WsGr                                            Skriv gruppe sekvensiellt
CD =============================================================================
CD Formål:
CD Skriver aktuell gruppe til ekstern, sekvensiell SOSI-fil.
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD LC_WsGr(pFil);
   =============================================================================
*/
SK_EntPnt_FYBA void LC_WsGr(LC_FILADM *pFil)
{
   UT_INT64 neste = LLONG_MAX;

   LO_TestFilpeker(pFil,"WsGr");

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
                                           /* Feil ==> Ulovlig ekstern fil */
       if (pFil->usLag != LC_SEKV) {
          LC_Error(33,"(LC_WsGr)","");

                                           /* Feil ==> Ikke skriveaksess */
		//} else if (pFil->sAccess != UT_UPDATE  ||  pFil->lNgisLag == LC_NGIS_LES) {
      } else if (pFil->sAccess != UT_UPDATE  || strcmp(pFil->szNgisLag,"0") == 0 ) {         
          LC_Error(34,"(LC_WsGr)","");

                                           /* OK ==> Skriv */
       } else {
                              /* Sjekk at SOSI-filen har hode */
         if ((pFil->TransMaske & LC_TR_ENHET) == 0  &&  Sys.pGrInfo->gnavn != L_HODE) {
              LC_Error(141,"(LC_WsGr)",pFil->pszNavn);
           }

           if (Sys.pGrInfo->gnavn == L_HODE) {       /* Oppdater filtabellen */
               LO_BeFt(pFil);
           }

           LB_WGru(SKRIV_SISTE,1,Sys.pGrInfo->nko,pFil,pFil->n64AktPos,&neste);
           pFil->n64AktPos = neste;

       }

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_WsGr)","");
   }
}


/*
AR-930610
CH LC_WsGrPart                              Skriv del av gruppe sekvensiellt
CD ==========================================================================
CD Formål:
CD Skriver en del av aktuell gruppe til ekstern, sekvensiell SOSI-fil.
CD
CD Parametre:
CD Type       Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil      i    Peker til FilAdm
CD long       fra_punkt i    Punktnummer for første koordinat som skal skrives.
CD                           (Lovlig:  1  <=  fra_punkt  <=  nko)
CD long       antall    i    Antall koordinatlinjer som skal skrives.
CD                           (Lovlig:  0  <=  antall  <=  nko)
CD
CD Bruk:
CD LC_WsGrPart(pFil,fra_punkt,antall);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_WsGrPart(LC_FILADM *pFil,long fra_punkt,long antall)
{
   UT_INT64 neste = LLONG_MAX;

   LO_TestFilpeker(pFil,"WsGrPart");

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
                                           /* Feil ==> Ulovlig ekstern fil */
       if (pFil->usLag != LC_SEKV) {
          LC_Error(33,"(LC_WsGr)","");

                                           /* Feil ==> Ikke skriveaksess */
		//} else if (pFil->sAccess != UT_UPDATE  ||  pFil->lNgisLag == LC_NGIS_LES) {
      } else if (pFil->sAccess != UT_UPDATE  ||  strcmp(pFil->szNgisLag,"0") == 0 ) {  

          LC_Error(34,"(LC_WsGr)","");

                                           /* OK ==> Skriv */
       } else{
                                         /* Sjekker at punktnummer er lovlig */
           fra_punkt = min( max(1,fra_punkt), max(1,Sys.pGrInfo->nko) );
           antall = min( max(antall,0), (Sys.pGrInfo->nko-fra_punkt+1) );

                                                        /* Skriver */
           LB_WGru(SKRIV_SISTE,fra_punkt,antall,pFil,pFil->n64AktPos,&neste);
           pFil->n64AktPos = neste;

           if (Sys.pGrInfo->gnavn == L_HODE){           /* Oppdater filtabellen */
               LO_BeFt(pFil);
           }
       }

   } else{                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_WsGr)","");
   }
}


/*
AR:2000-10-17
CH LC_EndreHode                            Endre hodet på eksisterende SOSI-fil
CD =============================================================================
CD Formål:
CD Skriver aktuell gruppe til starten av sekvensiell SOSI-fil.
CD Det er en forutsetning at aktuell gruppe er et filhode.
CD Denne rutinen er stort sett lik LC_WsGr, men LC_EndreHode forandrer ikke
CD aktuell filposisjon på den sekvensielle filen.
CD OBS!
CD Det må være nok ledig plass før neste gruppe for tilbakeskrivingen.
CD Det er ikke mulig å forandre koordinatsystem, enhet eller origo på fil
CD som inneholder data.
CD
CD Parametre:
CD Type       Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_FILADM *pFil       i    Peker til FilAdm
CD short      oppdatert  r    Skrivestatus (1=OK, 0=Det er ikke plass
CD                                          til å skrive hodet)
CD
CD Bruk:
CD ist = LC_EndreHode(pFil);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_EndreHode(LC_FILADM *pFil)
{
   short tegnsett,siste,oppdatert=0;
   UT_INT64 neste;
   char* pszNgisLag;
   unsigned short Maske = LC_TR_ALLT;
   LC_TRANSPAR Trans;


   if (Sys.GrId.lNr != INGEN_GRUPPE) {                /* Aktuell gruppe OK */
      /* LO_TestFilpeker(pFil,"LC_EndreHode"); */
      LO_TestFilpeker(pFil,"EndreHode");

                                           /* Feil ==> Ulovlig ekstern fil */
      if (pFil->usLag != LC_SEKV) {
         LC_Error(33,"(LC_EndreHode)","");

                                           /* Feil ==> Ikke skriveaksess */
		} else if (pFil->sAccess != UT_UPDATE  ||  strcmp(pFil->szNgisLag,"0") == 0 ) {
         LC_Error(34,"(LC_EndreHode)","");

                                           /* OK */
      } else {
                                  /* Sjekk at aktuell gruppe er filhode */
         if (Sys.pGrInfo->gnavn != L_HODE) {
                                           /* Feil ==> Ikke filhode */
            LC_Error(98,"(LC_EndreHode)","");

         } else {                         /* OK ==> Skriv */
                                          /* Finn ledig plass for å skrive */
            siste = LB_Plass(pFil,0,&neste);
                                             /* Sjekk mot ledig plass */
            if (LB_WGru(KONTROLLER_PLASS,1,Sys.pGrInfo->nko,pFil,0,&neste)) {
               /* Det er plass nok */

               /* Hent hode-opplysninger det ikke er lov til å endre når det er data i filen */
               LC_GetTransEx(&Maske,&Trans);
               LC_GetTegnsett(&tegnsett);
               pszNgisLag = LH_GetNgisLag();

               /* Skriv hvis siste gruppe, eller  transpar, tegnsett og NGIS-lag er uendret */
               if (siste  ||  (memcmp(&pFil->TransPar,&Trans,sizeof(LC_TRANSPAR)) == 0  &&
                   pFil->sTegnsett == tegnsett)) {
                               
                  if ( strcmp(pFil->szNgisLag,pszNgisLag) == 0) {
                     LO_BeFt(pFil);
                     LB_WGru(SKRIV_VANLIG,1,Sys.pGrInfo->nko,pFil,0,&neste);
                     oppdatert = 1;
                  
                  } else {
                     /* Koord.sys, enhet, origo eller tegnsett er endret */
                     LC_Error(96,"(LC_EndreHode)","");
                  }
                  
               } else {
                  /* Koord.sys, enhet, origo eller tegnsett er endret */
                  LC_Error(96,"(LC_EndreHode)","");
               }

            } else {        /* Det er ikke plass til å skrive hodet */
               LC_Error(97,"(LC_EndreHode)","");
            }
         }
      }

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_EndreHode)","");
   }

   return oppdatert;
}


/*
AR-920810
CH LC_RxGr                                               Les gruppe fra base
CD ==========================================================================
CD Formål:
CD Velger en gruppe som aktiv gruppe, og leser den fra SOSI-filen hvis den
CD ikke er i RB fra før. (Styres også av les_sosi.)
CD Hvis gruppen ikke finnes (sletta eller ulovlig gruppenummer) returneres
CD ngi=0 og nko=0.
CD
CD Parametre:
CD Type    Navn    I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR * pBgr     i   Peker til fil- og gruppenummer.
CD short   les_sosi i   Lesemetode: Følgende konstanter er definert:
CD                         LES_OPTIMALT   (0 = Les mest effektivt base/SOSI)
CD                         LES_SOSI       (1 = Les alltid fra SOSI-filen)
CD short  *ngi      u   Antall linjer GINFO
CD long   *nko      u   Antall koordinater
CD unsigned short *info      u   Diverse informasjon. En sum av følgende:
CD                       GI_PINFO     = gruppen har PINFO
CD                       GI_NAH       = gruppen har høyde informasjon (..NØH)
CD                       GI_NAD       = gruppen har dybde informasjon (..NØD)
CD                       GI_KP        = gruppen har knutepunkt (...KP n)
CD                       GI_REF       = gruppen har referanser (.. eller ..REF)
CD                       GI_OY_REF    = gruppen har referanser med øy
CD                       GI_NGIS      = gruppen er tatt ut fra NGIS for oppdat.
CD                       GI_SLETTA    = gruppen er sletta (merka som sletta)
CD                       GI_READ_ONLY = gruppen kan ikke endres.
CD short gnavn     r   Gruppenavn - Følgende konstanter er definert:
CD                                      INGEN_GRUPPE = Gruppen finnes ikke, ikke lest. 
CD                                      L_SLUTT    =   (.SLUTT) 
CD                                      L_PUNKT    =   (.PUNKT) 
CD                                      L_LINJE    =   (.LINJE) 
CD                                      L_KURVE    =   (.KURVE) 
CD                                      L_BUE      =   (.BUE) 
CD                                      L_BUEP     =   (.BUEP) 
CD                                      L_SIRKEL   =   (.SIRKEL) 
CD                                      L_SIRKELP  =   (.SIRKELP) 
CD                                      L_KLOTOIDE =   (.KLOTOIDE)
CD                                      L_SVERM    =   (.SVERM) 
CD                                      L_TEKST    =   (.TEKST) 
CD                                      L_TRASE    =   (.TRASE) 
CD                                      L_FLATE    =   (.FLATE) 
CD                                      L_BEZIER   =   (.BEZIER)
CD                                      L_RASTER   =   (.RASTER) 
CD                                      L_DEF      =   (.DEF) 
CD                                      L_OBJDEF   =   (.OBJDEF) 
CD                                      L_MLINJE   =   (.MLINJE)
CD                                      L_STRUKTUR =   (.STRUKTUR)  
CD                                      L_OBJEKT   =   (.OBJEKT) 
CD                                      L_SYMBOL   =   (.SYMBOL) 
CD                                      L_HODE     =   (.HODE)       
CD                                      
CD
CD Bruk:
CD     gnavn = LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
CD     if (info & GI_PINFO)        (gruppen har PINFO)
CD         ;
CD     if (info & GI_KP)           (gruppen har KP)
CD         ;
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_RxGr(LC_BGR * pBgr,short les_sosi,short *ngi,long *nko,unsigned short *info)
{
   UT_INT64  slutt;
   short sNyGruppe = UT_TRUE;

   LO_TestFilpeker(pBgr->pFil,"RxGr");

   // Har aktuell gruppe
   if (Sys.GrId.lNr != INGEN_GRUPPE) {
      sNyGruppe = Sys.GrId.pFil != pBgr->pFil  ||  Sys.GrId.lNr != pBgr->lNr;

      // Hvis aktuell gruppe er endret, skriv den
      if (Sys.sGrEndra != END_UENDRA) {
         if (!(!sNyGruppe  &&  les_sosi == LES_SOSI)) {
            if (LC_WxGr(SKRIV_OPTIMALT) == UT_FALSE) {
               // "Kan ikke lese ny gruppe. Du har ikke skriveaksess for å lagre aktuell gruppe som er endret. Fil :"
               LC_Error(163, "(LC_RxGr)", Sys.GrId.pFil->pszNavn);
            }
         }
      }
   }

   Sys.sGrEndra = END_UENDRA;
   Sys.sPibufStatus = LC_PIBUF_TOM;

                  /* Lovlig gruppe */
   if (pBgr->lNr >= 0L && pBgr->lNr < pBgr->pFil->lAntGr) {
      Sys.GrId = *pBgr;
                                /* Hent fra gruppe-tabellen */
      Sys.pGrInfo = LI_GetGrt(pBgr->pFil,pBgr->lNr);
                                /* Sjekk om gruppen er sletta */
      if (Sys.pGrInfo->ngi == 0  ||         /* Permanent sletta, eller  */
          (Sys.sNGISmodus == NGIS_NORMAL  &&    /* Vanlig modus, og         */
           Sys.pGrInfo->info & GI_NGIS  &&      /* oppdater NGIS, og        */
           Sys.pGrInfo->info & GI_SLETTA)) {    /* merka som sletta         */

         /* Gruppen er sletta */
         ;
         Sys.GrId.lNr = INGEN_GRUPPE;
         Sys.pGrInfo = NULL;
         *ngi = 0;
         *nko = 0;
         return  -1;  /* retur ===> */

      } else {                             /* Gruppen er OK */
         /* Tvungen les fra SOSI-filen av samme gruppe */
         if (les_sosi == LES_SOSI) {
            /* Les fra SOSI-filen */
            LB_RGru(pBgr->pFil,Sys.pGrInfo->sosi_st,&slutt);
            if (!sNyGruppe) {
               Sys.sGrEndra = END_ENDRA;
            }
            LC_OppdaterEndret(O_GINFO);

         /* Hent fra buffer-fil */
         } else if (sNyGruppe) {
            Sys.GrId = *pBgr;

            LI_ReadRb(pBgr->pFil,Sys.pGrInfo->rb_st,Sys.Ginfo.pszTx,Sys.pGrInfo->ulGiLen, Sys.pdAust,
                      Sys.pdNord, Sys.pInfo, Sys.pGrInfo->nko, Sys.pszPinfo,
                      Sys.pGrInfo->ulPiLen);
            LX_CreGiPeker(&Sys.Ginfo,Sys.pGrInfo->ngi);
         }

         *ngi = Sys.pGrInfo->ngi;
         *nko = Sys.pGrInfo->nko;
         *info = Sys.pGrInfo->info;
         return Sys.pGrInfo->gnavn;      /* retur ===> */
      }
   }

   /* Ulovlig gruppe */
   Sys.GrId.lNr = INGEN_GRUPPE;
   Sys.pGrInfo = NULL;
   *ngi = 0;
   *nko = 0;
   return  -1;  /* retur ===> */
}


/*
AR-911001
CH LC_WxGr                                             Skriv gruppe til base
CD ==========================================================================
CD Formål:
CD Skriver aktuell gruppe til tilhørende SOSI-fil.
CD Brukerindeks og geografisk indeks oppdateres straks, uavhengig av kø.
CD Ledig plass fram til neste gruppe blir blanket.
CD Filhode blir ALLTID skrevet direkte til SOSI-filen.
CD
CD Parametre:
CD Type  Navn    I/U  Forklaring
CD ------------------------------------------------------------------------
CD short k_stat   i   Skrivemetode:  Følgende konstanter er definert:
CD                      SKRIV_OPTIMALT = Skriv mest effektivt kø/SOSI
CD                      SKRIV_SOSI     = Skriv direkte til SOSI-filen
CD short status   r   Status: UT_TRUE = OK
CD                            UT_FALSE = Ikke utført, pga. feil.
CD
CD Bruk:
CD LC_WxGr(k_stat)
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_WxGr(short k_stat)
{
   short pnr,nivaa;

   if (Sys.GrId.lNr != INGEN_GRUPPE)      /* Aktuell gruppe OK */
   {
      if (Sys.sGrEndra != END_UENDRA)     /* Gruppen er endra, må skrive */
      {   
         /* Har skriveaksess? */
         //if (Sys.GrId.pFil->sAccess == UT_UPDATE  &&
         //    (Sys.GrId.pFil->szNgisLag[0] == '\0'  ||  strcmp(Sys.GrId.pFil->szNgisLag,"0") != 0 ) ) {

         //if (Sys.GrId.pFil->sAccess == UT_UPDATE  &&
         //    (Sys.GrId.pFil->szNgisLag[0] == '\0'  ||  Sys.sNGISmodus == NGIS_SPESIAL) ) {  

		   if (Sys.GrId.pFil->sAccess != UT_UPDATE  ||
                    ((Sys.sNGISmodus == NGIS_NORMAL) && (strcmp(Sys.GrId.pFil->szNgisLag,"0")) == 0) )
         {  
            /* Ikke skriveaksess */
            LC_Error(34,"(LC_WxGr)",Sys.GrId.pFil->pszNavn);

            return UT_FALSE;         // ===>  Retur ved feil

         } else {

            /* Sjekk at SOSI-filen har hode */
            if ((Sys.GrId.pFil->TransMaske & LC_TR_ENHET) == 0  &&  Sys.pGrInfo->gnavn != L_HODE) {
               LC_Error(141,"(LC_WxGr)",Sys.GrId.pFil->pszNavn);
            }

            if (Sys.sGrEndra == (short)END_ENDRA) {
               // Kontroller prikknivå i egenskaper ?

               // Oppdater ..NGIS-FLAGG
               LC_OppdaterEndret(O_ENDRET);     
            }

            Sys.sGrEndra = END_UENDRA;

            // Filhode som ligger som første gruppe på filen
            // Oppdater filtabellen 
            if (Sys.pGrInfo->gnavn == L_HODE  &&  Sys.GrId.lNr == 0) {
               LO_BeFt(Sys.GrId.pFil);

            // Ajourfører gruppetabellen med kvalitet og enhet
            } else {
               nivaa = 2;
               pnr = 1;
               LC_GetCurKvalitet(Sys.GrId.pFil,&nivaa,pnr,
                              &Sys.pGrInfo->Kvalitet.sMetode,
                              &Sys.pGrInfo->Kvalitet.lNoyaktighet,
                              &Sys.pGrInfo->Kvalitet.sSynbarhet,
                              &Sys.pGrInfo->Kvalitet.sHoydeMetode,
                              &Sys.pGrInfo->Kvalitet.lHoydeNoyaktighet);

               nivaa = 2;
               LC_GetCurEnhet(Sys.GrId.pFil, &nivaa, &Sys.pGrInfo->dEnhet,
                              &Sys.pGrInfo->dEnhetHoyde, &Sys.pGrInfo->dEnhetDybde);

               /* Avrund buffer til riktig enhet */
               LC_RoundKoord();
            }
 
            /* Skriv til buffer-fil */
            LB_WriteRb();

            /* Skriv direkte, eller filhode */
            if (k_stat == SKRIV_SOSI  ||  Sys.pGrInfo->gnavn == L_HODE) {
               LB_Swap();

            /* Legg inn i skrivekøa */
            } else {
               Sys.lAntSkriv++;
               LI_SetBt (Sys.GrId.pFil, Sys.GrId.lNr, BT_SKRKO);

                                           /* Tøm køa hvis den er full */
               if (Sys.lAntSkriv > Sys.lMaxSkriv) {
                  LC_Save();
               }
            }

            /* ----------------------------- Oppdater indekser */
            LS_Indx(); /* Serienummer */
            
            LR_Indx();      /* Primær geografisk */
            
            if (Sys.pGrInfo->gnavn == L_FLATE) {
               LR_IndxFlate(); /* Flate geografisk */
            }         

            Sys.pGrInfo->ulPrior[0] = 0UL;  /* Prioritetstabell */
            Sys.pGrInfo->ulPrior[1] = 0UL;
            Sys.pGrInfo->ulPrior[2] = 0UL;
            Sys.pGrInfo->ulPrior[3] = 0UL;

         //} else {                                 /* Ikke skriveaksess */
         //   LC_Error(34,"(LC_WxGr)","");
         }
      }
   }

   return UT_TRUE;
}


/*
AR-930907
CH LB_WriteRb                           Skriv aktuell gruppe til buffer-filen
CD ===========================================================================
CD Formål:
CD Skriv aktuell gruppe til buffer-filen.
CD
CD Parametre: ingen
CD
CD Bruk:
CD LB_WriteRb();
==============================================================================
*/
static void LB_WriteRb(void)
{
   LC_GRTAB_LINJE *pForrigeGrInfo, *pNesteGrInfo;
   long lLen;


   lLen = LI_BerBufferLen(Sys.pGrInfo->ulGiLen,Sys.pGrInfo->nko,Sys.pGrInfo->ulPiLen);

   /* Er ikke på filen fra før, tildel ny plass */
   if (Sys.pGrInfo->rb_st == NY_RB_ST) {
      Sys.pGrInfo->rb_st = Sys.GrId.pFil->n64NesteLedigRbPos;
      Sys.GrId.pFil->n64NesteLedigRbPos += (UT_INT64)lLen;
      /* Oppdater kjeden */
      pForrigeGrInfo = LI_GetGrt (Sys.GrId.pFil, Sys.GrId.pFil->lSisteGrRb);
      pForrigeGrInfo->rb_neste_gr = Sys.GrId.lNr;
      Sys.pGrInfo->rb_forrige_gr = Sys.GrId.pFil->lSisteGrRb;
      Sys.pGrInfo->rb_neste_gr = INGEN_GRUPPE;
      Sys.GrId.pFil->lSisteGrRb = Sys.GrId.lNr;


   /* Er på filen, sjekk om det er nok ledig plass */
   } else {
      /* Siste gruppe i buffer-filen */
      if (Sys.pGrInfo->rb_neste_gr == INGEN_GRUPPE) {
         Sys.GrId.pFil->n64NesteLedigRbPos = Sys.pGrInfo->rb_st + (UT_INT64)lLen;

      /* Inne i buffer-filen */
      } else {
         pNesteGrInfo = LI_GetGrt(Sys.GrId.pFil,Sys.pGrInfo->rb_neste_gr);

         /* Det er ikke plass, må flytte gruppen til slutten av filen */
         if (Sys.pGrInfo->rb_st + lLen  > pNesteGrInfo->rb_st) {
            /* Tett "hullet" i kjeden */
            pNesteGrInfo->rb_forrige_gr = Sys.pGrInfo->rb_forrige_gr;
            if (Sys.pGrInfo->rb_forrige_gr != INGEN_GRUPPE) {
               pForrigeGrInfo = LI_GetGrt(Sys.GrId.pFil,Sys.pGrInfo->rb_forrige_gr);
               pForrigeGrInfo->rb_neste_gr = Sys.pGrInfo->rb_neste_gr;
            }

            /* Legg til på slutten */
            Sys.pGrInfo->rb_st = Sys.GrId.pFil->n64NesteLedigRbPos;
            Sys.GrId.pFil->n64NesteLedigRbPos += (UT_INT64)lLen;

            pForrigeGrInfo = LI_GetGrt (Sys.GrId.pFil, Sys.GrId.pFil->lSisteGrRb);
            pForrigeGrInfo->rb_neste_gr = Sys.GrId.lNr;
            Sys.pGrInfo->rb_forrige_gr = Sys.GrId.pFil->lSisteGrRb;
            Sys.pGrInfo->rb_neste_gr = INGEN_GRUPPE;
            Sys.GrId.pFil->lSisteGrRb = Sys.GrId.lNr;
         }

      }
   }

   LI_WriteRb(Sys.GrId.pFil,Sys.pGrInfo->rb_st,Sys.Ginfo.pszTx,Sys.pGrInfo->ulGiLen,
              Sys.pdAust, Sys.pdNord, Sys.pInfo, Sys.pGrInfo->nko,
              Sys.pszPinfo, Sys.pGrInfo->ulPiLen);
}


/*
AR-930608
CH LC_RoundKoord                 Endre koordinatene i buffer til riktig enhet
CD ===========================================================================
CD Formål:
CD Endrer koordinatene i aktuell gruppe i buffer til valgt enhet.
CD (Rutinen blir utført fra LC_WxGr.)
CD
CD Parametre: ingen
CD
CD Bruk:
CD LC_RoundKoord();
==============================================================================
*/
SK_EntPnt_FYBA void LC_RoundKoord(void)
{
	short iniv;
   long pt;
   double enhet,enhet_h,enhet_d,tall;

   /* Lovlig gruppe */
   if (Sys.GrId.lNr != INGEN_GRUPPE){

      /* Kan gruppen endres (ikke READ_ONLY) */
      //if ((Sys.pGrInfo->info & GI_READ_ONLY) == 0 ) {
      if ((Sys.pGrInfo->info & GI_READ_ONLY) == 0  ||  Sys.sNGISmodus == NGIS_SPESIAL ) {
         
         /* Finn aktuell enhet */
         iniv = 2;
         LC_GetCurEnhet(Sys.GrId.pFil,&iniv,&enhet,&enhet_h,&enhet_d);

         /* Avrund koordinatene */
         for (pt=0; pt<Sys.pGrInfo->nko; pt++) {
            /* Nord */
            tall = UT_RoundDD(*(Sys.pdNord+pt) / enhet);
            *(Sys.pdNord+pt) = tall * enhet;
            /* Øst */
            tall = UT_RoundDD(*(Sys.pdAust+pt) / enhet);
            *(Sys.pdAust+pt) = tall * enhet;

            /* Høyde */
            if (Sys.pGrInfo->info & GI_NAH) {
				   if ((Sys.pInfo+pt)->dHoyde != HOYDE_MANGLER) {
					   tall = UT_RoundDD((Sys.pInfo+pt)->dHoyde / enhet_h);
                  (Sys.pInfo+pt)->dHoyde = tall * enhet_h;
               }

            /* Dybde */
            } else if (Sys.pGrInfo->info & GI_NAD) {
               if ((Sys.pInfo+pt)->dHoyde != HOYDE_MANGLER) {
                  tall = UT_RoundDD((Sys.pInfo+pt)->dHoyde / enhet_d);
                  (Sys.pInfo+pt)->dHoyde = tall * enhet_d;
               }
            }
         }
      }
   }
}


/*
AR-911001
CH LC_OppdaterEndret                                    Oppdater ..NGIS-FLAGG
CD ==========================================================================
CD Formål:
CD Oppdaterer ..NGIS-FLAGG i GINFO og ajourfører interne tabeller.
CD Hvis endring = O_GINFO oppateres tabellene i forhold til
CD eksisterende GINFO.
CD
CD Parametre:
CD Navn     Type   I/U  Forklaring
CD --------------------------------------------------------------------------
CD endring  short   i   Kode for endring:
CD                       O_GINFO   (0) = Oppdater interne tabeller i fht. GINFO
CD                       O_ENDRET  (1) = Merk for endret og oppdat. tab.
CD                       O_SLETTET (2) = Merk for slettet og oppdat. tab.
CD
CD Bruk:
CD LC_OppdaterEndret(O_ENDRET);
=============================================================================
*/
SK_EntPnt_FYBA void LC_OppdaterEndret(short endring)
{
   short gilin;
   const char *gp;
   char szFlagg[80];

   /* Finn aktuell parameter */
   gilin=2;
   gp = LC_GetGP("..NGIS-FLAGG",&gilin,Sys.pGrInfo->ngi);
   if (gp == NULL){   
      Sys.pGrInfo->info &= (unsigned short)(~GI_NGIS);      /* Ikke NGIS-oppdatering */
      Sys.pGrInfo->info &= (unsigned short)(~GI_READ_ONLY); /* Ikke READ_ONLY */

   } else {
      /* Tolk gammel parameter */
      UT_StrCopy(szFlagg,gp,80);
      
      /*
       * Oppdater ..NGIS-FLAGG i GINFO hvis
       * det er NGIS-standardmodus, og ikke 
       * intern tabelloppdatering.
       */

      if (Sys.sNGISmodus == NGIS_NORMAL  &&  endring != O_GINFO) {
         /* Kode */
			if (endring == O_SLETTET) {
            szFlagg[0] = 'S';

         } else if (endring == O_ENDRET) {
            if (szFlagg[0] == 'V') {
               szFlagg[0] = 'E';
            }
         }

         /* Bygg opp ny ginfo */
         LC_UpdateGP(gilin,"..NGIS-FLAGG",szFlagg);
      }


      /* ---------- Oppdater interne tabeller --------- */

      /* NGIS-oppdatering */
      Sys.pGrInfo->info |= GI_NGIS;   
      
      /* Flagg for sletting */
      if (szFlagg[0] == 'S') {
         Sys.pGrInfo->info |= GI_SLETTA;                     /* Sletta */
      } else {
         Sys.pGrInfo->info &= (unsigned short)(~GI_SLETTA);  /* Ikke sletta */
      }

      /* Flagg for lese/skrive aksess */
      if (szFlagg[0] == 'R'  ||  szFlagg[0] == 'H') {
         Sys.pGrInfo->info |= GI_READ_ONLY;                    /* Bare leseaksess */
      } else {
         Sys.pGrInfo->info &= (unsigned short)(~GI_READ_ONLY); /* Både lese- og skriveaksess */
      }
   }
}


/*
AR-911001
CH LC_FiLastGr                                     Finn siste gruppe i filen
CD ==========================================================================
CD Formål:
CD Finner gruppenummer for siste gruppe i filen.
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD bgr        long   r    Gruppenummer
CD
CD Bruk:
CD bgr = LC_FiLastGr(pFil);
   ==========================================================================
*/
SK_EntPnt_FYBA long LC_FiLastGr(LC_FILADM *pFil)
{
   /* LO_TestFilpeker(pFil,"LC_FiLastGr"); */
   LO_TestFilpeker(pFil,"FiLastGr");

   return  pFil->lAntGr - 1;
}


/*
AR-930608
CH LC_CopyGr                                                   Kopier gruppe
CD ==========================================================================
CD Formål:
CD Kopierer fra en annen gruppe inn i aktuell gruppe i buffer.
CD Rutinen tilsvarer put fra brukerprogram inn i bufret, men rutinen
CD tildeler selv nødvendig plass.
CD Gruppen beholder serienummer tildelt i LC_NyGr.
CD Geografisk-indeks blir ikke oppdatert før gruppen skrives til basen.
CD Enhet blir oppdatert slik at opprinnelig enhet blir bevart. Om nødvendig
CD legges det inn ..ENHET i GINFO.
CD Kvalitet og dato blir oppdatert hvis SOSI-VERSJON < 4.00.
CD Hvis det er filhode som kopieres skjer det ingen endring av egenskaper.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR  *pBgr     i    Gruppenummer det skal kopieres fra.
CD short    ngis     i    Behandling for ..NGIS-FLAGG:
CD                          OPPDATER_NGIS (0) = ..NGIS-FLAGG oppdateres i henhold
CD                                              til hodet i filen det kopieres til.
CD                          BEVAR_NGIS (1) = ..NGIS-FLAGG bevares uforandret i kopien
CD short    ngi      u    Antall linjer GINFO
CD long     nko      u    Antall koordinater
CD unsigned short    info     u    Diverse informasjon. (Se under $LENKE<LC_RxGr>)
CD short    gnavn    r    Gruppenavn. (Se under $LENKE<LC_RxGr>)
CD
CD Bruk:
CD     gnavn = LC_CopyGr(&Bgr,ngis,&ngi,&nko,&info)
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_CopyGr (LC_BGR * pBgr,short ngis,short *ngi,long *nko,unsigned short *info)
{
   short gilin;
   long snr,rb_forrige_gr,rb_neste_gr;
   UT_INT64 rb_st,sosi_st;
   LC_GRTAB_LINJE * grtp;
   const char* cp;
   char szTx[256];
   LC_R_LEAF * pRL;   /* Peker inn i geografisk søketre */


   LO_TestFilpeker(pBgr->pFil,"CopyGr");

   grtp = LI_GetGrt(pBgr->pFil,pBgr->lNr);

   if (Sys.GrId.lNr == INGEN_GRUPPE) {       /* Feil ==> Ingen aktuell gruppe */
      LC_Error(31,"(LC_CopyGr)","");

												  /* Gruppen er sletta */
   } else if (grtp->ngi == 0  ||                 /* Permanent sletta, eller */
              (Sys.sNGISmodus == NGIS_NORMAL  &&   /* Vanlig modus, og        */
               grtp->info & GI_NGIS  &&          /* oppdater NGIS, og       */
               grtp->info & GI_SLETTA)){         /* merka som sletta        */
      LC_Error(35,"(LC_CopyGr)","");

   /* Kopierer seg selv */
   } else if (pBgr->pFil == Sys.GrId.pFil  &&  pBgr->lNr == Sys.GrId.lNr) {
      *ngi = Sys.pGrInfo->ngi;
      *nko = Sys.pGrInfo->nko;
      *info = Sys.pGrInfo->info;

   } else {                                         /* Lovlig gruppe */

      Sys.sGrEndra = END_KOPI;
      Sys.sPibufStatus = LC_PIBUF_TOM;
      snr = LC_GetSn();           /* Husk serienummer */

      /* Husk viktige data fra akt.gr. */
      sosi_st = Sys.pGrInfo->sosi_st;
      rb_st   = Sys.pGrInfo->rb_st;
		rb_forrige_gr = Sys.pGrInfo->rb_forrige_gr;
      rb_neste_gr   = Sys.pGrInfo->rb_neste_gr;
      pRL           = Sys.pGrInfo->pRL; /* Peker inn i geografisk søketre */

      /* Kopier data om gruppen det kopieres fra */
      *Sys.pGrInfo = *grtp;

      /* Legg tilbake data om akt.gr. */
      Sys.pGrInfo->sosi_st = sosi_st;
      Sys.pGrInfo->rb_st   = rb_st;
      Sys.pGrInfo->rb_forrige_gr = rb_forrige_gr;
      Sys.pGrInfo->rb_neste_gr   = rb_neste_gr;
      Sys.pGrInfo->pRL = pRL;

      /* Les fra buffer-filen */
      LI_ReadRb(pBgr->pFil,grtp->rb_st,Sys.Ginfo.pszTx,grtp->ulGiLen,
                Sys.pdAust, Sys.pdNord, Sys.pInfo, grtp->nko,
                Sys.pszPinfo, grtp->ulPiLen);
      LX_CreGiPeker(&Sys.Ginfo,grtp->ngi);

      /* Legg tilbake rett SNR */
      LX_PutSn(snr);

      // Hvis det er filhode som kopieres skjer det ingen endring av egenskaper.
      if (pBgr->lNr != 0)
      {
         // ----- Handter NGIS oppdateringsflagg
         // Søk etter ..NGIS-FLAGG, og fjern den
         gilin=2;
         if (LC_GetGP("..NGIS-FLAGG",&gilin,Sys.pGrInfo->ngi) != NULL)
         {
            if ( ngis == OPPDATER_NGIS)
            {
               // NGIS-flagg
               if (*Sys.GrId.pFil->szNgisLag != '\0'  &&  strcmp(Sys.GrId.pFil->szNgisLag,"0") != 0 )
               {         
                  // Skriv navnet med hermetegn hvis det er blanke i navnet
                  if (strchr(Sys.GrId.pFil->szNgisLag,' ') != NULL) {
                     UT_SNPRINTF(szTx,256,"..NGIS-FLAGG N \"%s\"",Sys.GrId.pFil->szNgisLag);
                  } else {
                     UT_SNPRINTF(szTx,256,"..NGIS-FLAGG N %s",Sys.GrId.pFil->szNgisLag);
                  }

                  LC_PutGi(gilin,szTx);
                  Sys.pGrInfo->info |= GI_NGIS;   

               } else {
                  LC_DelGiL(gilin,1);
                  Sys.pGrInfo->info &= (unsigned short)(~GI_NGIS);     /* Ikke NGIS-oppdatering */
               }

			   } else {
               // Flagget skal bevares
            }

         } else {
            /* NGIS-flagg */
            //if (Sys.GrId.pFil->lNgisLag > 0) {
            if (*Sys.GrId.pFil->szNgisLag != '\0'  &&  strcmp(Sys.GrId.pFil->szNgisLag,"0") != 0 ) {         

               // Skriv navnet med hermetegn hvis det er blanke i navnet
               if (strchr(Sys.GrId.pFil->szNgisLag,' ') != NULL) {
                  UT_SNPRINTF(szTx,256,"..NGIS-FLAGG N \"%s\"",Sys.GrId.pFil->szNgisLag);
               } else {
                  UT_SNPRINTF(szTx,256,"..NGIS-FLAGG N %s",Sys.GrId.pFil->szNgisLag);
               }

               LC_PutGi(LC_AppGiL(),szTx);
               Sys.pGrInfo->info |= GI_NGIS;   
            }
         }

         /* ------------ Legg inn div. standardopplysninger */
         /* ENHET */
         LC_UpdateGiEnhet(Sys.GrId.pFil,grtp->dEnhet, grtp->dEnhetHoyde, grtp->dEnhetDybde);

         // Bare hvis filen er eldre enn SOSI v 4.0
         if (Sys.GrId.pFil->sSosiVer < 400)
         {
            // Det skal aldri legges ut kvalitet på .FLATE eller .OBJEKT
            if (Sys.pGrInfo->gnavn != L_FLATE  &&  Sys.pGrInfo->gnavn != L_OBJEKT) {
               // ..KVALITET
               LC_UpdateGiKvalitet(Sys.GrId.pFil,grtp->Kvalitet.sMetode,
                                   grtp->Kvalitet.lNoyaktighet,
                                   grtp->Kvalitet.sSynbarhet,
                                   grtp->Kvalitet.sHoydeMetode,
                                   grtp->Kvalitet.lHoydeNoyaktighet);
            }

            // NGIS-fil, oppdater DATO
            if (*Sys.GrId.pFil->szNgisLag != '\0'  &&  strcmp(Sys.GrId.pFil->szNgisLag,"0") != 0 )
            {    
               if (*Sys.GrId.pFil->szDato != '\0'  &&  
                   *Sys.GrId.pFil->szDato != '*'  &&  
                   *Sys.GrId.pFil->szDato < '4')
               { 
                     // ..DATO fra fil-hodet
                  gilin=2;
                  if ((cp = LC_GetGP("..DATO",&gilin,Sys.pGrInfo->ngi)) == NULL) {
                     UT_SNPRINTF(szTx,256,"..DATO %s",pBgr->pFil->szDato);
                     LC_PutGi(LC_AppGiL(),szTx);
                  }
               }
            }

            // SOSI-VERSJON
            //gilin=2;
            //if ((cp = LC_GetGP("..SOSI-VERSJON",&gilin,Sys.pGrInfo->ngi)) == NULL) {
            //   UT_SNPRINTF(szTx,256,"..SOSI-VERSJON %.2f",((double)(pBgr->pFil->sSosiVer))/100.0);
            //   LC_PutGi(LC_AppGiL(),szTx);
            //}
         }
      }

      *ngi = Sys.pGrInfo->ngi;
      *nko = Sys.pGrInfo->nko;
      *info = Sys.pGrInfo->info;
   }


   return Sys.pGrInfo->gnavn;
}


/*
AR-930707
CH LC_CopyCoord                           Kopier koordinater fra annen gruppe
CD ===========================================================================
CD Formål:
CD Kopierer koordinater fra en annen gruppe inn i aktuell gruppe i ringbuffer.
CD De kopierte koordinatene kommer som en utvidelse av gruppen.
CD Rutinen tilsvarer put fra brukerprogram inn i ringbufret, men rutinen
CD tildeler selv nødvendig plass i RB.
CD Geografisk-indeks blir ikke oppdatert før gruppen skrives til basen.
CD Kvalitet og enhet blir automatisk oppdatert slik at gruppene ikke 
CD mister informasjon.
CD
CD Parametre:
CD Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_BGR *pBgr      i    Gruppenummer det skal kopieres fra.
CD short   retning   i    Buffer-retning:
CD                                HENT_FORRFRA ( 1) = vanlig,
CD                                HENT_BAKFRA  (-1) = buffer skal snues.
CD long   til_linje i    Linjenummer linjen skal skytes inn forran.
CD                        (Lovlig: 1  til  nko+1)
CD short   ngi       u    Antall GINFO-linjer
CD long    nko       u    Antall koordinater
CD short   info      u    Diverse informasjon. (Se under $LENKE<LC_RxGr>)
CD short   sStatus   r    Status: UT_TRUE=OK, UT_FALSE=ikke utført.
CD
CD Bruk:
CD sStatus = LC_CopyCoord(bgr,retning,til_linje,&ngi,&nko,&info);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_CopyCoord(LC_BGR * pBgr,short retning,long til_linje,short *ngi,
                  long *nko,unsigned short *info)
{
   long l,ko,pnr,fra_pt,til_pt;
   unsigned short in;
   unsigned long  ulPiLen,ulGiLen;
   short metode,hoydemetode,synbarhet,met,hmet,syn,nivaa,gi_met,gi_hmet,gi_syn;
   long noyaktighet,hoydenoyaktighet,noy,hnoy,gi_noy,gi_hnoy;
   UT_INT64 rb_st;
   double *pdAust, *pdNord;
   LB_INFO * pInfo;
   char *pszPinfo;
   LC_GRTAB_LINJE * grtp;
   short sStatus = UT_TRUE;


	LO_TestFilpeker(pBgr->pFil,"CopyCoord");

   grtp = LI_GetGrt(pBgr->pFil,pBgr->lNr);

   if (Sys.GrId.lNr == INGEN_GRUPPE){        /* Feil ==> Ingen aktuell gruppe */
      LC_Error(31,"(LC_CopyCoord)","");
      sStatus = UT_FALSE;

                                      /* Gruppen er sletta */
   } else if (grtp->ngi == 0  ||                   /* Permanent sletta, eller */
              (Sys.sNGISmodus == NGIS_NORMAL  &&   /* Vanlig modus, og        */
               grtp->info & GI_NGIS  &&            /* oppdater NGIS, og       */
               grtp->info & GI_SLETTA)){           /* merka som sletta        */
      LC_Error(35,"(LC_CopyCoord)","");
      sStatus = UT_FALSE;

   } else if (pBgr->pFil == Sys.GrId.pFil  &&  pBgr->lNr == Sys.GrId.lNr) {
      /* Kopierer seg selv */
      LC_Error(99,"(LC_CopyCoord)","");
      sStatus = UT_FALSE;

   } else {                                              /* Lovlig gruppe */

      /* Husk diverse opplysninger */
      ko = grtp->nko;
		in = grtp->info;
      metode = grtp->Kvalitet.sMetode;
      noyaktighet = grtp->Kvalitet.lNoyaktighet;
      synbarhet = grtp->Kvalitet.sSynbarhet;
      hoydemetode = grtp->Kvalitet.sHoydeMetode;
      hoydenoyaktighet = grtp->Kvalitet.lHoydeNoyaktighet;

      rb_st = grtp->rb_st;
      ulGiLen = grtp->ulGiLen;
      ulPiLen = grtp->ulPiLen;

      /* Tildel plass for koordinatene */
      l = Sys.pGrInfo->nko;
      LC_InsKoL(til_linje,ko);
      if (Sys.pGrInfo->nko > l) {   /* Har det blitt lagt inn flere linjer */
         Sys.sGrEndra = (short)END_ENDRA;
         Sys.sPibufStatus = LC_PIBUF_TOM;

		   /* Alloker midlertidig buffer */
		   pdAust   = (double*)UT_MALLOC(ko * sizeof(double));
		   pdNord   = (double*)UT_MALLOC(ko * sizeof(double));
		   pInfo    = (LB_INFO *)UT_MALLOC(ko * sizeof(LB_INFO));
		   pszPinfo = (char*)UT_MALLOC(ulPiLen * sizeof(char));

         /* Les fra buffer-filen */
         LI_ReadCoordRb(pBgr->pFil, rb_st, ulGiLen,pdAust, pdNord, pInfo, ko,
                   pszPinfo, ulPiLen);

         /* Regn posisjoner */
         til_pt = til_linje - 1;
         if (retning == HENT_FORRFRA) {
            fra_pt = 0;
            retning = 1;
         } else{
            fra_pt = ko - 1;
            retning = -1;
         }

         for (l = 0;  l < ko;  l++) {             /* Koordinater og PINFO */
			   *(Sys.pdAust+til_pt) = *(pdAust+fra_pt);
            *(Sys.pdNord+til_pt) = *(pdNord+fra_pt);
            (Sys.pInfo+til_pt)->dHoyde = (pInfo+fra_pt)->dHoyde;
            (Sys.pInfo+til_pt)->sKp = (pInfo+fra_pt)->sKp;
            if ((pInfo+fra_pt)->ulPiOfset != LC_INGEN_PINFO) {
               LC_PutPi(til_pt+1, pszPinfo+((pInfo+fra_pt)->ulPiOfset));
            }

            til_pt++;
            fra_pt += retning;
         }

         Sys.pGrInfo->info |= in;

		   /* Frigi midlertidig buffer */
		   UT_FREE(pdAust);
		   UT_FREE(pdNord);
		   UT_FREE(pInfo);
		   UT_FREE(pszPinfo);

         // ----- Oppdater Kvalitet i de kopierte punktene
         if (Sys.GrId.pFil->sSosiVer < 400)
         {
            // Husk kvalitet i GINFO på aktuell gruppe
            nivaa = 2;
            pnr = 1;
            LC_GetCurKvalitet(Sys.GrId.pFil,&nivaa,pnr,&gi_met,&gi_noy,&gi_syn,&gi_hmet,&gi_hnoy);

            // Oppdater punktene
            for (pnr=til_linje; ko>0; pnr++,ko--) {
               nivaa = 3;
               LC_GetCurKvalitet(Sys.GrId.pFil,&nivaa,pnr,&met,&noy,&syn,&hmet,&hnoy);
               // Funnet punkt uten kvalitet i PINFO
               if (nivaa < 3) {
                  LC_UpdatePiKvalitet(Sys.GrId.pFil,pnr,
                                      metode,noyaktighet,synbarhet,hoydemetode,hoydenoyaktighet);

               // Funnet punkt med samme kvalitet som aktuell GINFO
			      } else if (met == gi_met  &&  noy == gi_noy  &&  syn == gi_syn  &&
                          hmet == gi_hmet  &&  hnoy == gi_hnoy) {
                  LC_UpdatePiKvalitet(Sys.GrId.pFil,pnr,met,noy,syn,hmet,hnoy);
               }
            }
         }

         *ngi = Sys.pGrInfo->ngi;
         *nko = Sys.pGrInfo->nko;
         *info = Sys.pGrInfo->info;

      } else {                  /* For mange koordinater */
         sStatus = UT_FALSE;
      }
   }

   return sStatus;
}


/*
AR-940208
CH LC_SnuGr                                                        Snu gruppe
CD ===========================================================================
CD Formål:
CD Snur en gruppe.
CD Rutinen tilsvarer put fra brukerprogram inn i ringbufret.
CD Både koordinater, høyde, KP og PINFO blir behandlet.
CD For .BUE blir fortegnet på radius endret.
CD Fortegnet på referanser til gruppen blir oppdatert.
CD
CD Parametre:
CD Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD
CD Bruk:
CD    LC_SnuGr();
   =============================================================================
*/
SK_EntPnt_FYBA void LC_SnuGr(void)
{
   short ngi,sGiLin,Endret;
   long fra_pt,til_pt;
   long nko;
   unsigned short info;
   double *pdAust,*pdNord;
   LB_INFO * pInfo;
   char* pszPinfo; 
   char szRadius[30];
   double nva,nvn,oha,ohn;
   LC_GEO_STATUS GeoStat;
   LC_BGR Bgr,FlateBgr;
   LC_POLYGON Polygon;
	LC_POL_ELEMENT * pPE;
   LC_OY_ELEMENT * pOE;


   /* Feil ==> Ingen aktuell gruppe */
   if (Sys.GrId.lNr == INGEN_GRUPPE){
      LC_Error(31,"(LC_CopyCoord)","");

   /* Lovlig gruppe */
   } else if (Sys.pGrInfo->nko > 1) {

      /* Husk diverse opplysninger */
      nko = Sys.pGrInfo->nko;

      /* Tildel plass for koordinatene */
      Sys.sGrEndra = (short)END_ENDRA;
		Sys.sPibufStatus = LC_PIBUF_TOM;

		/* Lag en midlertidig kopi av original-bufferet */
		pdAust   = (double*)UT_MALLOC(nko * sizeof(double));
		UT_memcpy(pdAust,nko * sizeof(double),Sys.pdAust,nko * sizeof(double));

		pdNord   = (double*)UT_MALLOC(nko * sizeof(double));
      UT_memcpy(pdNord,nko * sizeof(double),Sys.pdNord,nko * sizeof(double));

		pInfo    = (LB_INFO *)UT_MALLOC(nko * sizeof(LB_INFO));
      UT_memcpy(pInfo,nko * sizeof(LB_INFO),Sys.pInfo,nko * sizeof(LB_INFO));

		pszPinfo = (char*)UT_MALLOC(Sys.pGrInfo->ulPiLen * sizeof(char));
      UT_memcpy(pszPinfo,Sys.pGrInfo->ulPiLen * sizeof(char),Sys.pszPinfo,Sys.pGrInfo->ulPiLen * sizeof(char));

      /* Tømmer gruppen for gammelt innhold */
      LC_DelKoL(1,nko);
      LC_InsKoL(1,nko);

      /* Legger inn koordinater og PINFO */
		for (til_pt=0,fra_pt=nko-1;  til_pt<nko; til_pt++,fra_pt--) {
         *(Sys.pdAust+til_pt) = *(pdAust+fra_pt);
			*(Sys.pdNord+til_pt) = *(pdNord+fra_pt);
         (Sys.pInfo+til_pt)->dHoyde = (pInfo+fra_pt)->dHoyde;
         (Sys.pInfo+til_pt)->sKp = (pInfo+fra_pt)->sKp;
         if ((pInfo+fra_pt)->ulPiOfset != LC_INGEN_PINFO) {
            LC_PutPi(til_pt+1, pszPinfo+((pInfo+fra_pt)->ulPiOfset));
         }
      }

		/* Frigi midlertidig buffer */
		UT_FREE(pdAust);
		UT_FREE(pdNord);
		UT_FREE(pInfo);
		UT_FREE(pszPinfo);

		/* ====== Hvis gruppen er .BUE ==> skift fortegn på radius ==== */
      if (Sys.pGrInfo->gnavn == L_BUE) {
         sGiLin = 2;
         auto* p = LC_GetGP("..RADIUS",&sGiLin,Sys.pGrInfo->ngi);

         if (*p == '-') {
            UT_StrCopy(szRadius, p +1,30);
         } else {
            p[0] = '-';
            UT_StrCopy(szRadius+1, p,29);
         }

         LC_UpdateGP(sGiLin,"..RADIUS",szRadius);
      }


      /* ========= Oppdater referanser til gruppen */
      /* Husk gruppen */
      Bgr = Sys.GrId;

      LC_POL_InitPolygon(&Polygon);

		LC_GetGrWin(&Sys.GrId,&nva,&nvn,&oha,&ohn);
      LC_SBFlate(&GeoStat,LC_FRAMGR,nva,nvn,oha,ohn);
      if (LC_FFFlate(&GeoStat,&FlateBgr)) {
         do {
            if (FlateBgr.pFil == Bgr.pFil) {
               /* Funnet flate i rett fil, sjekk referansene */
               LC_RxGr(&FlateBgr,LES_OPTIMALT,&ngi,&nko,&info);
               LC_POL_GetRef(&Polygon);
               Endret = UT_FALSE;

               /* Omkretsen */
              for(pPE = Polygon.HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
                 if ((memcmp(&pPE->Bgr,&Bgr,sizeof(LC_BGR))) == 0) {
                    pPE->sRetning = (pPE->sRetning == LC_MED_DIG)?
                                                     LC_MOT_DIG  :  LC_MED_DIG;
                    Endret = UT_TRUE;
                 }
              }

              /* Øyer */
              for (pOE = Polygon.OyOA.pForsteOE; pOE != NULL; pOE = pOE->pNesteOE) {
					  for (pPE = pOE->PO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
                    if ((memcmp(&pPE->Bgr,&Bgr,sizeof(LC_BGR))) == 0) {
                       pPE->sRetning = (pPE->sRetning == LC_MED_DIG)?
                                                     LC_MOT_DIG  :  LC_MED_DIG;
                       Endret = UT_TRUE;
                    }
                 }
              }

              /* Lagre de oppdaterte referansene */
              if (Endret) {
                 LC_POL_PutRef(&Polygon);
                 LC_WxGr(SKRIV_OPTIMALT);
              }

              /* Frigi allokerte kjeder */
              LC_POL_FrigiPolygon(&Polygon);

            }
         } while (LC_FNFlate(&GeoStat,&FlateBgr));
      }
      LC_AvsluttSok(&GeoStat);


		/* ========= Les inn igjen opprinnelig gruppe */
      LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
   }
}


/*
AR-911001
CH LC_DelGr                                                     Slett gruppe
CD ==========================================================================
CD Formål:
CD Fjerner aktuell gruppe fra basen.
CD Grupper som er tatt ut fra NGIS for oppdatering blir ikke sletta fra
CD SOSI-filen, men de blir merka som sletta. (LC_SetNgisModus avgjør da om
CD disse kan leses.)
CD Det er ikke mulig å slette grupper fra sekvensielle filer, eller grupper
CD som er brukt i flater.
CD
CD Parametre:
CD Type   Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD short  sStatus  r    Status:  UT_TRUE  = OK
CD                               UT_FALSE = feil, ikke sletta
CD
CD Bruk:
CD sStatus = LC_DelGr();
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_DelGr(void)
{
   UT_INT64 neste;
   char *gp;
   short gilin = 2;
   short sStatus = UT_TRUE;
   long lSnr = LC_GetSn();
   char *pszNgisFlagg;


   if (Sys.GrId.lNr != INGEN_GRUPPE) {
                                         /* Ikke filhode, eller kladdebase */
      //if (Sys.pGrInfo->gnavn != L_HODE  &&  Sys.GrId.pFil->pBase->sType == LC_BASE) {
      if (Sys.GrId.lNr != 0  &&  Sys.GrId.pFil->pBase->sType == LC_BASE) {
         if ( ! (Sys.pGrInfo->info & GI_SLETTA)) {  /* Ikke sletta fra før */
            if (Sys.GrId.pFil->usLag & LC_FRAMGR) { /* Har skriveaksess */

               // Finn og ta vare på NGIS-flagg
               gp = LC_GetGP("..NGIS-FLAGG",&gilin,Sys.pGrInfo->ngi);
               if (gp) {
                  pszNgisFlagg = (char*)malloc(strlen(gp)+1);
                  UT_StrCopy(pszNgisFlagg, gp, strlen(gp)+1);
               } else {
                  pszNgisFlagg = NULL;
               }
               
               // Ny gruppe - ikke lagret til SOSI, eller
               // ikke NGIS-oppdatering, eller
               // ny NGIS-gruppe, eller
               // vanlig NGIS-grupppe
               if (Sys.pGrInfo->sosi_st == NY_SOSI_ST  || 
                   pszNgisFlagg == NULL  ||
                   *pszNgisFlagg == 'N'  ||
                   *pszNgisFlagg == 'V'  ||
                   *pszNgisFlagg == 'E'  ||
                   *pszNgisFlagg == 'S' ) {

                  if (Sys.pGrInfo->gnavn == L_LINJE    ||
                      Sys.pGrInfo->gnavn == L_KURVE    ||
                      Sys.pGrInfo->gnavn == L_BUE      ||
                      Sys.pGrInfo->gnavn == L_BUEP     ||
                      Sys.pGrInfo->gnavn == L_SIRKEL   ||
                      Sys.pGrInfo->gnavn == L_SIRKELP  ||
                      Sys.pGrInfo->gnavn == L_KLOTOIDE ||
                      Sys.pGrInfo->gnavn == L_TRASE      ) {

                     if (Sys.pGrInfo->nko > 0) {
                        // Sjekk om det finnes referanser til gruppen
                        if (LC_ErReferert())  sStatus = UT_FALSE;
                     }
                  }

                  // Det finnes ikke referanser til gruppen
                  if (sStatus == UT_TRUE) {

                     /* Ikke NGIS-oppdatering, eller ny NGIS-gruppe, fjerner fysisk fra SOSI-filen */
                     if (Sys.pGrInfo->sosi_st == NY_SOSI_ST  ||
                         pszNgisFlagg == NULL  ||
                         *pszNgisFlagg == 'N'  ) {  

                        if (Sys.pGrInfo->sosi_st != NY_SOSI_ST) { /* Ikke ny gruppe */
                           LB_Plass(Sys.GrId.pFil,Sys.pGrInfo->sosi_st,&neste);
                           /* Posisjoner og blank ut området */
                           _fseeki64(Sys.GrId.pFil->pBase->pfSos,Sys.pGrInfo->sosi_st,SEEK_SET);
							      LB_WriteBlank(Sys.GrId.pFil->pBase->pfSos,Sys.GrId.pFil->sTegnsett,neste);
									fflush(Sys.GrId.pFil->pBase->pfSos);
                        }
                        Sys.pGrInfo->ngi = 0;
                        Sys.pGrInfo->nko = 0;

                      /* Vanlig NGIS-grupppe, merker som slettet */
                     } else if (*pszNgisFlagg == 'V'  ||
                                *pszNgisFlagg == 'E'  ||
                                *pszNgisFlagg == 'S' ) {
                        LC_OppdaterEndret(O_SLETTET);
                        LC_WxGr(SKRIV_SOSI);
                     }

                     /* Fjerner fra snr.tab */
                     LS_PutSn(Sys.GrId.pFil,INGEN_GRUPPE,lSnr);

                     /* Fjerner fra geogr. søketabell */
                     LR_R_Delete(Sys.pGrInfo->pRL);
                     Sys.pGrInfo->pRL = NULL;


                     Sys.pGrInfo->info |= GI_SLETTA;      /* Gruppen sletta */
                     LI_PutBt(Sys.GrId.pFil,Sys.GrId.lNr,0L);  /* Fjerner all merking */

					      Sys.GrId.lNr = INGEN_GRUPPE;       /* Ingen aktuell gruppe */
                     Sys.sGrEndra = END_UENDRA;

                  /* Brukt i flate */
                  /*} else {
                     LC_Error(44,"(LC_DelGr)","");*/
                  }

               /* Bare leseaksess */
               } else if (*pszNgisFlagg == 'R'  ||  *pszNgisFlagg == 'H' ) {
                  LC_Error(91,"(LC_DelGr)","");
                  sStatus = UT_FALSE;

               /* Ukjent NGIS endringsflagg */
               } else {
                  LC_Error(91,"(LC_DelGr)","");
                  sStatus = UT_FALSE;
               }

               // Frigir alloker minne
               if (pszNgisFlagg)  free(pszNgisFlagg);

            } else {                          /* Ikke skriveaksess */
               LC_Error(91,"(LC_DelGr)","");
               sStatus = UT_FALSE;
            }
         }

      } else {                         /* Filhode, eller kladdebase */
         sStatus = UT_FALSE;

         if (Sys.GrId.pFil->pBase->sType != LC_BASE) {
            /* Slett gruppe ulovlig ved kladdebase */
            LC_Error(95,"(LC_DelGr)","");
         } else {
            /* Kan ikke slette filhodet */
            LC_Error(48,"(LC_DelGr)","");
         }
      }
   }

   return sStatus;
}


/*
AR-920129
CH LC_SplittGr                                                 Splitt gruppe
CD ==========================================================================
CD Formål:
CD Splitter aktuell gruppe i to deler.
CD Første del av gruppen beholdes som aktuell gruppe. Denne blir ikke
CD skrevet til SOSI-filen, men buffer er oppdatert.
CD Siste del av gruppen legges som en ny gruppe på samme fil som
CD opprinnelig gruppe. Denne blir skrevet til basen.
CD Den delen av gruppen som ligger mellom P1 og P2 blir fjernet.
CD
CD Hvis gruppen er BUEP og en av delene får bare to koordinater
CD blir det lagt inn et nytt punkt midt på buen.
CD
CD Parametre:
CD Type     Navn   I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    sP1     i    Punktnummer 1.   (Må være større enn 1)
CD long    sP2     i    Punktnummer 2.   (Må være mindre enn nko)
CD LC_BGR *  pBgr2   u    Nytt gruppenummer for siste del av gruppen.
CD short    sStatus r    Status: UT_TRUE  = OK
CD                               UT_FALSE = feil, ikke splittet
CD
CD Bruk:
CD sStatus = LC_SplittGr(sP1,sP2,&Bgr2);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_SplittGr (long sP1,long sP2,LC_BGR * pBgr2)
{
   short ngi,Endret,s;
   long nko;
   long l;
   unsigned short info;
   LC_FILADM *pFil;
   LC_BGR Bgr,FlateBgr;
   long lGmlSnr,lNyttSnr;
   double nva,nvn,oha,ohn;
   double a1,n1,a2,n2,as1,ns1,as2,ns2,r,fi,dfi,fi2,dfi2;
   LC_GEO_STATUS GeoStat;
   long lAntRef;
   long lNyAntRef;
   short sGiLin,sRefPos;
   long *plRefArray,*plNyRefArray,*plRef,*plNyRef;
   double fiNy,dfiNy,dA_ny,dN_ny;
   double ax,nx;
   bool bStorbue = false;   /* Viser om opprinnelig gruppe var OK storbue */
   short sStatus = UT_FALSE;

   /* Har aktuell gruppe med koordinater, og lovlige punktnummer */
   if (Sys.GrId.lNr != INGEN_GRUPPE  &&
       Sys.pGrInfo->nko > 0  &&
		 sP1 > 1  &&
       sP2 < Sys.pGrInfo->nko) {

      /* Husk at beregning er utført */
      sStatus = UT_TRUE;

      /* Husk gruppen */
      pFil = Sys.GrId.pFil;
      Bgr = Sys.GrId;
      lGmlSnr = LC_GetSn();
      LC_GetGrWin(&Bgr,&nva,&nvn,&oha,&ohn);


      if (Sys.pGrInfo->gnavn == L_BUE  || 
          Sys.pGrInfo->gnavn == L_BUEP ||
          Sys.pGrInfo->gnavn == L_SIRKELP )
      {
         // Tar vare på bueparametrene for opprinnelig "bue"
         LC_GetBuePar(HENT_FORRFRA,&as1,&ns1,&r,&fi,&dfi,&s);
         bStorbue = (fabs(dfi) > PI);
      }

      // ========= Lag ny gruppe, og kopier hele den opprinnelige gruppen
      LC_NyGr(pFil,".LINJE",pBgr2,&lNyttSnr);
      LC_CopyGr(&Bgr,OPPDATER_NGIS,&ngi,&nko,&info);

      /* Samme brukttabell som opprinnelig gruppe */
      for (s=BT_MIN_USER; s<=BT_MAX_USER; s++) {
         if (LC_GetBt(&Bgr,s) != 0) {
            LC_SetBt(pBgr2,s);
         }
      }

      // SIRKELP konverteres til BUEP
      if (Sys.pGrInfo->gnavn == L_SIRKELP )
      {
         LC_PutGi(1,".BUEP");
         double a,n;
         LC_GetTK(1,&a,&n);
         nko = LC_AppKoL();
         LC_PutTK(nko,a,n);
         LC_PutKp(nko,LC_GetKp(1));
      }

      /* Fjern første del av gruppen */
      if (sP2 > sP1){
         nko = LC_DelKoL(1, sP2-1);
      } else if (nko > 1) {
         nko = LC_DelKoL(1, sP1-1);
      }

      /* Sjekk om storbue er blitt liten bue */
      if (Sys.pGrInfo->gnavn == L_BUE  &&  bStorbue)
      {
         LC_GetBue(HENT_FORRFRA,&a1,&n1,&a2,&n2,&r,&s);
			GM_KonvBue(a1,n1,a2,n2,r,s,&as2,&ns2,&fi2,&dfi2);

         /* Buen skal ikke være storbue lenger hvis sentrum er flyttet.
          * Dette er tilfelle når linjen fra gammelt til nytt senter
          * skjærer linjen fra nytt start til sluttpunkt.
          */
         if (GM_sLinLin(a1,n1,a2,n2,as1,ns1,as2,ns2,&ax,&nx)) {
            LC_PutGP("..STORBUE","0",&s);
         }
      }

      // Sjekk at .BUEP har tre koordinater
      if (Sys.pGrInfo->gnavn == L_BUEP)
      {
         if (nko == 2)
         {
            // --- Legger inn nytt punkt på buen mellom de to endepunktene.
            // Åpningsvinkel til starten av den nye buen
            LC_GetTK(1,&a1,&n1);
            GM_PktBue(as1,ns1,fi,dfi,a1,n1,&dfiNy);

            // Midtpunktet
            fiNy = fi + (dfiNy+((dfi-dfiNy)/2.0));
            dA_ny = as1 + fabs(r)*cos(fiNy);
            dN_ny = ns1 + fabs(r)*sin(fiNy);

            nko = LC_InsKoL(2,1);
            LC_PutTK(2,dA_ny,dN_ny);
         }

         // Endre til .KURVE hvis buen blir ulovlig
         LR_TestEndreBuepTilKurve(dfi);
      }

      // Lagre
      LC_WxGr(SKRIV_OPTIMALT);

      // ========= Oppdater referanser til gruppen
      LC_SBFlate(&GeoStat,LC_FRAMGR,(double)nva,(double)nvn,
                                    (double)oha,(double)ohn);
      if (LC_FFFlate(&GeoStat,&FlateBgr)) {
         do {
            if (FlateBgr.pFil == pFil) {
               /* Funnet flate i rett fil, sjekk referansene */
               LC_RxGr(&FlateBgr,LES_OPTIMALT,&ngi,&nko,&info);
					lAntRef = LC_InqAntRef();
					plRefArray = (long *) UT_MALLOC(lAntRef * sizeof(long));
					plNyRefArray = (long *) UT_MALLOC((lAntRef+2) * sizeof(long));
					sGiLin = 2;
					sRefPos = 0;
					LC_GetRef(plRefArray,lAntRef,&sGiLin,&sRefPos);

               lNyAntRef = lAntRef;
               Endret = UT_FALSE;
               plRef = plRefArray;
               plNyRef = plNyRefArray;
               for (l=0; l<lAntRef; l++) {
                  if (labs(*plRef) == lGmlSnr) {
                     if (*plRef > 0) {
                        *plNyRef++ = *plRef++;
                        *plNyRef++ = lNyttSnr;

                     } else {
                        *plNyRef++ = -lNyttSnr;
                        *plNyRef++ = *plRef++;
                     }
                     Endret = UT_TRUE;
                     lNyAntRef++;
                     
                  } else {
                     *plNyRef++ = *plRef++;
                  }
               }

               if (Endret) {
                  LC_PutRef(plNyRefArray,lNyAntRef);
                  LC_WxGr(SKRIV_OPTIMALT);
               }
					UT_FREE(plRefArray);
					UT_FREE(plNyRefArray);
				}
			} while (LC_FNFlate(&GeoStat,&FlateBgr));
      }
      LC_AvsluttSok(&GeoStat);

      // ========= Oppdater opprinnelig gruppe
      LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);

      /* Fjern siste del av gruppen */
      if (nko > 1) {
         nko = LC_DelKoL(sP1+1, nko-sP1);
      }

      // SIRKELP må konverteres til BUEP
      if (Sys.pGrInfo->gnavn == L_SIRKELP )
      {
         LC_PutGi(1,".BUEP");
      }

      /* Sjekk om storbue er blitt liten bue */
      if (Sys.pGrInfo->gnavn == L_BUE  &&  bStorbue)
      {
         LC_GetBue(HENT_FORRFRA,&a1,&n1,&a2,&n2,&r,&s);
         GM_KonvBue(a1,n1,a2,n2,r,s,&as2,&ns2,&fi2,&dfi2);

         /* Buen skal ikke være storbue lenger hvis sentrum er flyttet.
          * Dette er tilfelle når linjen fra gammelt til nytt senter
			 * skjærer linjen fra nytt start til sluttpunkt.
          */
         if (GM_sLinLin(a1,n1,a2,n2,as1,ns1,as2,ns2,&dA_ny,&dN_ny)) {
            LC_PutGP("..STORBUE","0",&s);
         }
      }

      // Sjekk at .BUEP har tre koordinater
      if (Sys.pGrInfo->gnavn == L_BUEP)
      {
         if (nko == 2)
         {
            // --- Legger inn nytt punkt på buen mellom de to endepunktene.
            // Åpningsvinkel til slutten av den nye buen
            LC_GetTK(2,&a2,&n2);
            GM_PktBue(as1,ns1,fi,dfi,a2,n2,&dfiNy);
            // Midtpunktet
            fiNy = fi + (dfiNy/2.0);
            dA_ny = as1 + fabs(r)*cos(fiNy);
            dN_ny = ns1 + fabs(r)*sin(fiNy);

            LC_InsKoL(2,1);
            LC_PutTK(2,dA_ny,dN_ny);
         }

         // Endre til .KURVE hvis buen blir ulovlig
         LR_TestEndreBuepTilKurve(dfi);
      }
   }

   return sStatus;
}

/*
AR-930803
CH LR_TestEndreBuepTilKurve                               Sammenføy grupper
CD ==========================================================================
CD Formål:
CD Sjekk om BUEP blir ugyldeig etter splitting. 
CD Konverterer eventuellt til .KURVE
CD
CD Parametre:
CD Type    Navn      I/U  Forklaring
CD -----------------------------------------------------------------------------
CD double  dDeltaFi   i   Åpningsvinkel for opprinnelig BUEP
CD
CD Bruk:
CD LR_TestEndreBuepTilKurve(dDeltaFi);
   =============================================================================
*/
static void LR_TestEndreBuepTilKurve(double dDeltaFi)
{
   double as,ns,r,fi,dfi;
   double dAMidt,dNMidt,dAFotP,dNFotP;
   double a1,n1,a2,n2;
   short s;
 
   // Avrund buffer til riktig enhet
   LC_RoundKoord();

   // Bueparametrene for oppdatert "bue"
   if (LC_GetBuePar(HENT_FORRFRA,&as,&ns,&r,&fi,&dfi,&s) )
   {
      // Buen er snudd krumming (åpningsvinkelen har skiftet fortegn)
      if (dDeltaFi * dfi  <  0.0)
      {
         LC_PutGi(1,".KURVE");
      }
      else
      {
         // Sjekk at buen ikke har blitt en rett linje etter avrunding til aktuell enhet.
         LC_GetTK(1,&a1,&n1);
         LC_GetTK((Sys.pGrInfo->nko+1)/2,&dAMidt,&dNMidt);
         LC_GetTK(Sys.pGrInfo->nko,&a2,&n2);
         GM_fotp(a1,n1,a2,n2,dAMidt,dNMidt,&dAFotP,&dNFotP);
         // Avstand fra fotpunktet til punktet på buen må være minst en enhet
         if(GM_Avstand(dAMidt,dNMidt,dAFotP,dNFotP) < Sys.pGrInfo->dEnhet) {
            LC_PutGi(1,".KURVE");
         }
      }
   }
   else
   {
      LC_PutGi(1,".KURVE");
   }
}


/*
AR-930803
CH LC_SammenfoyGr                                          Sammenføy grupper
CD ==========================================================================
CD Formål:
CD Sammenføye to grupper.
CD Kopierer koordinater fra gitt gruppe inn i aktuell gruppe.
CD De kopierte koordinatene kommer som en utvidelse av gruppen.
CD Rutinen tildeler selv nødvendig plass i buffer.
CD Kvalitet og enhet blir automatisk oppdatert slik at gruppene ikke 
CD mister informasjon.
CD Gruppen det kopieres fra blir slettet.
CD Eventuelle referanser til gruppene blir oppdatert.
CD
CD
CD Parametre:
CD Type    Navn       I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_BGR * pFraBgr     i    Gruppenummer det skal kopieres fra.
CD short   retning     i    Buffer-retning:
CD                                HENT_FORRFRA ( 1) = vanlig,
CD                                HENT_BAKFRA  (-1) = buffer skal snues.
CD short   plassering  i    Forteller hvor pFraBgr skal plasseres i
CD                          aktuell gruppe.
CD                             LC_SG_FORRAN = Heng den andre gruppen inn
CD                                            forran første koordinat.
CD                             LC_SG_BAK    = Heng den andre gruppen inn
CD                                            etter siste koordinat.
CD short   metode      i    Forteller hva som skal skje med sammenføingspunktene.
CD                             LC_SG_BEHOLD = Begge punktene beholdes.
CD                             LC_SG_FJERN  = Bare det ene av punktene beholdes.
CD short   ngi         u    Antall GINFO-linjer
CD long    nko         u    Antall koordinater
CD unsigned short info u    Diverse informasjon. (Se under $LENKE<LC_RxGr>)
CD short   sStatus     r    Status: UT_TRUE=OK, UT_FALSE=ikke utført.
CD
CD Bruk:
CD sStatus = LC_SammenfoyGr(bgr,retning,plassering,metode,&ngi,&nko,&info);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_SammenfoyGr(LC_BGR * pFraBgr,short retning,short plassering,short metode,
                    short *ngi,long *nko,unsigned short *info)
{
   short Endret,gnavn;
   long FraNko,sTilPkt;
   LC_BGR AktBgr,FlateBgr;
   long lAktSnr,lFraSnr;
   double nva,nvn,oha,ohn;
   LC_GEO_STATUS GeoStat;
   LC_POLYGON Pol;
   LC_OY_ELEMENT * pOE;
   short sStatus = UT_TRUE;


   if (Sys.GrId.lNr == INGEN_GRUPPE){        /* Feil ==> Ingen aktuell gruppe */
      LC_Error(31,"(LC_SammenfoyGr)","");
      sStatus = UT_FALSE;

   } else {
      /* Husk aktuell gruppe */
      AktBgr = Sys.GrId;
      lAktSnr = LC_GetSn();
      sTilPkt = (plassering == LC_SG_FORRAN)?  1 : (Sys.pGrInfo->nko+1); 

		/* ========= Kopier */
      if (LC_CopyCoord(pFraBgr,retning,sTilPkt,ngi,nko,info)) {
         LC_WxGr(SKRIV_OPTIMALT);

         /* ========= Oppdater referanser */
         LC_RxGr(pFraBgr,LES_OPTIMALT,ngi,&FraNko,info);
         lFraSnr = LC_GetSn();
      
         LC_GetGrWin(&AktBgr,&nva,&nvn,&oha,&ohn);

         LC_SBFlate(&GeoStat,LC_FRAMGR,(double)nva,(double)nvn,
                                       (double)oha,(double)ohn);
         if (LC_FFFlate(&GeoStat,&FlateBgr)) {
            do {
               if (FlateBgr.pFil == AktBgr.pFil) {  /* På samme fil ? */
   
                  /* Funnet flate i rett fil, sjekk referansene */
                  gnavn = LC_RxGr(&FlateBgr,LES_OPTIMALT,ngi,nko,info);

                  if ( gnavn == L_FLATE) {
                     /* Hent referansene */
                     LC_POL_InitPolygon(&Pol);
                     LC_POL_GetRef(&Pol);

                     /* Ytre avgrensning */
					      Endret = LB_RensOmkrets(&Pol.HovedPO,lAktSnr,lFraSnr);

                     /* Øyer */
                     for (pOE = Pol.OyOA.pForsteOE; pOE != NULL; pOE = pOE->pNesteOE) {
                        /* Sjkker en og en øy */
					         Endret |= LB_RensOmkrets(&pOE->PO,lAktSnr,lFraSnr);
                     }

                     /* Lagre oppdatert referanse */
                     if (Endret == UT_TRUE) {
                        *ngi = LC_POL_PutRef(&Pol);
                        LC_WxGr(SKRIV_OPTIMALT);
                     }

                     /* Frigi allokerte kjeder */
                     LC_POL_FrigiPolygon(&Pol);
                  }
				   }
			   } while (LC_FNFlate(&GeoStat,&FlateBgr));
         }
         LC_AvsluttSok(&GeoStat);

         /* ========= Fjern den kopierte gruppen fra basen */
         LC_RxGr(pFraBgr,LES_OPTIMALT,ngi,&FraNko,info);
         lFraSnr = LC_GetSn();
         LC_DelGr();
      
         /* ========= Les inn opprinnelig gruppe igjen */
         LC_RxGr(&AktBgr,LES_OPTIMALT,ngi,nko,info);

         /* ========= Fjerner punkt og fjerner KP fra koblingspunktet */
         if (metode == LC_SG_FJERN) {
            if (plassering == LC_SG_BAK) {
               LC_PutKp(sTilPkt,0);
               *nko = LC_DelKoL(sTilPkt-1,1);
            } else {
               LC_PutKp(FraNko,0);
               *nko = LC_DelKoL(FraNko+1,1);
            }

         } else {
            if (plassering == LC_SG_BAK) {
               LC_PutKp(sTilPkt,0);
               LC_PutKp(sTilPkt-1,0);
            } else {
               LC_PutKp(FraNko,0);
               LC_PutKp(FraNko+1,0);
            }
         }

      } else {                  /* For mange koordinater */
         sStatus = UT_FALSE;
      }
   }

   return sStatus;
}


/*
AR-930803
CH LB_RensOmkrets                             Fjerner overflødige referanser
CD ==========================================================================
CD Formål:
CD  Fjerner overflødige referanser ved sammenføining av to grupper.
CD
CD Parametre:
CD Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD
CD
CD
CD Bruk:
CD Endret = LB_RensOmkrets(&Pol.HovedPO,lAktSnr,lFraSnr);
   =============================================================================
*/
static short LB_RensOmkrets(LC_POL_OMKR * pPO,long lAktSnr,long lFraSnr)
{
   LC_POL_ELEMENT * pPE;


   if (pPO != NULL) {
      /* Tilslag på første og siste gruppe */
      if (pPO->pForstePE->lSnr  == lAktSnr  &&
          pPO->pSistePE->lSnr  == lFraSnr) {
         /* Overser siste referansen (kopiert gruppe) */
         LC_POL_FjernGruppeOmkrets(pPO, pPO->pSistePE);
		   return UT_TRUE;

      } else if (pPO->pForstePE->lSnr  == lFraSnr  &&
                 pPO->pSistePE->lSnr  == lAktSnr) {

         /* Overser første referansen (kopiert gruppe) */
         LC_POL_FjernGruppeOmkrets(pPO, pPO->pForstePE);
         return UT_TRUE;
      }

      /* Resten av referansene */
      for(pPE = pPO->pForstePE; pPE->pNestePE != NULL; pPE = pPE->pNestePE) {

         if (pPE->lSnr  == lAktSnr  &&
             pPE->pNestePE->lSnr  == lFraSnr) {
            /* Overser siste referansen (kopiert gruppe) */
            LC_POL_FjernGruppeOmkrets(pPO, pPE->pNestePE);
		      return UT_TRUE;

         } else if (pPE->lSnr  == lFraSnr  &&
                    pPE->pNestePE->lSnr  == lAktSnr) {

            /* Overser første referansen (kopiert gruppe) */
            LC_POL_FjernGruppeOmkrets(pPO, pPE);
            return UT_TRUE;
         }
      }
   }

   return UT_FALSE;
}


/*
AR:2000-07-28
CH LC_NyGr                                                 Ny gruppe i basen
CD ==========================================================================
CD Formål:
CD Lager en ny gruppe i basen, og tildeler serienummer.
CD Sjekker at gruppenavnet er lovlig i denne versjon av FYBA.
CD Ved feil navn vil ".LINJE" bli valgt.
CD Legger inn gruppenavn i buffer.
CD Gruppen blir "aktuell" gruppe.
CD Sjekker ledig plass både for indeks-fil og sosi-fil.
CD
CD Parametre:
CD Type       Navn    I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_FILADM  *pFil    i    Peker til FilAdm
CD char       *sosi    i    Gruppenavn (Eks. ".KURVE")
CD LC_BGR *     pBgr    iu   Tildelt gruppenummer i basen
CD                          (Bgr.lNr=INGEN_GRUPPE = Feil, ikke oppretta)
CD long        snr     u    Tildelt serienummer
CD gnavn       short   r    Gruppenavn. (Se under $LENKE<LC_RxGr>)
CD                          INGEN_GRUPPE hvis det ikke er opprettet noen ny gruppe.
CD
CD Bruk:
CD gnavn = LC_NyGr (pFil,sosi,&Bgr,&snr);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_NyGr (LC_FILADM *pFil,const char *sosi,LC_BGR * pBgr,long *snr)
{
   short navn_nr,gilin;
   unsigned long ulLedigPlass;
   char szTx[256];
   char szSosiNavn[LC_MAX_SOSINAVN_LEN];
   short sMetode, sSynbarhet, sHoydeMetode,sNivaa;
   long lNoyaktighet, lHoydeNoyaktighet;


   /* Test lovlig filpeker */
   LO_TestFilpeker(pFil,"NyGr");

   /* Preparer SOSI-navnet */
   UT_StrCopy(szSosiNavn,sosi,LC_MAX_SOSINAVN_LEN);
   UT_StrUpper(szSosiNavn);

   /* Vanlig base */
   if (pFil->pBase->sType == LC_BASE) {

      // Har aktuell gruppe
      if (Sys.GrId.lNr != INGEN_GRUPPE) {
         // Er forrige gruppe endra?
         if (Sys.sGrEndra != END_UENDRA) {
            LC_WxGr(SKRIV_OPTIMALT);
         }
      }

      /* Setter: 'ingen aktuell gruppe' */
      pBgr->lNr = Sys.GrId.lNr = INGEN_GRUPPE;

      /* Sjekk om lovlig filnummer */
      if (pFil->usLag == LC_SEKV) {
			LC_Error(37,"(LC_NyGr)","");
         Sys.pGrInfo->gnavn = INGEN_GRUPPE;

		/* Ikke skriveaksess */
		//} else if (pFil->sAccess != UT_UPDATE  ||  pFil->lNgisLag == LC_NGIS_LES) {
		//} else if (pFil->sAccess != UT_UPDATE  ||  strcmp(pFil->szNgisLag,"0") == 0 ) {  
		} else if (pFil->sAccess != UT_UPDATE  ||
                 ((Sys.sNGISmodus == NGIS_NORMAL) && (strcmp(pFil->szNgisLag,"0")) == 0) ) {  

         LC_Error(38,"(LC_NyGr)","");
         Sys.pGrInfo->gnavn = INGEN_GRUPPE;

		} else {
			if (pFil->lAntGr < LC_MAX_GRU) {
				/* Sjekk ledig diskplass  for SOSI-filer */
				UT_InqAvailSize(pFil->pszNavn,&ulLedigPlass);
				if (ulLedigPlass < ((unsigned long)LC_MAX_KOORD * (unsigned long)120)) {
               /* Disken er snart full */
               LC_Error(93,"(LB_NyGr)",pFil->pszNavn);
            }
										 /* Sjekk om navnet finnes */
				if (LN_FinnNavn(&pFil->SosiNavn,szSosiNavn,&navn_nr) != 1) {
					navn_nr = L_LINJE;    /* Ukjent gruppenavn ==> Velg ".LINJE" */
				}

				pBgr->pFil = Sys.GrId.pFil = pFil;         /* Fil */
				pBgr->lNr = Sys.GrId.lNr = pFil->lAntGr++; /* Ant. grupper i basen */

				Sys.pGrInfo = LI_AppGrt(pBgr->pFil,pBgr->lNr);

				LB_ClGr();
				Sys.pGrInfo->gnavn = navn_nr;                /* Gruppenavn */
				Sys.pGrInfo->sosi_st = NY_SOSI_ST;           /* Setter start SOSI til ny */
				Sys.pGrInfo->rb_st = NY_RB_ST;
				Sys.pGrInfo->dEnhet = pFil->TransPar.dEnhet;             /* Enhet */
            Sys.pGrInfo->dEnhetHoyde = pFil->TransPar.dEnhet_h;   /* Enhet-H */
            Sys.pGrInfo->dEnhetDybde = pFil->TransPar.dEnhet_d;   /* Enhet-D */
            Sys.pGrInfo->ulPrior[0] = 0UL;              /* Prioritetstabell */
            Sys.pGrInfo->ulPrior[1] = 0UL;
            Sys.pGrInfo->ulPrior[2] = 0UL;
            Sys.pGrInfo->ulPrior[3] = 0UL;

            /* Nuller brukttabellen */
            LI_PutBt(pFil,pBgr->lNr,0L);

            /* Fjerner fra geogr. søketabell */
            Sys.pGrInfo->pRL = NULL;

            /* Nytt serienummer */
            *snr = pFil->lMaxSnr + 1L;

            /* Legg inn gruppenavn */
            LC_AppGiL();
            LC_PutGi(1,LN_GetNavn(&pFil->SosiNavn,navn_nr));
            LC_PutSn(*snr);

            /* NGIS-flagg */
            //if (pFil->lNgisLag > 0) {
            if (*pFil->szNgisLag != '\0'  &&  strcmp(pFil->szNgisLag,"0") != 0 ) {         

               // Skriv navnet med hermetegn hvis det er blanke i navnet
               if (strchr(Sys.GrId.pFil->szNgisLag,' ') != NULL) {
                  UT_SNPRINTF(szTx,256,"..NGIS-FLAGG N \"%s\"",pFil->szNgisLag);
               } else {
                  UT_SNPRINTF(szTx,256,"..NGIS-FLAGG N %s",pFil->szNgisLag);
               }

               gilin = LC_AppGiL();
               LC_PutGi(gilin,szTx);
            }

            /* ------------ Legg inn div. standardopplysninger */
            if (*Sys.GrId.pFil->szNgisLag != '\0'  &&  strcmp(Sys.GrId.pFil->szNgisLag,"0") != 0 ) {         

               /* ..KVALITET */
               sNivaa = 1;
               LC_GetCurKvalitet(pFil,&sNivaa,1,&sMetode,&lNoyaktighet,
                                 &sSynbarhet,&sHoydeMetode,&lHoydeNoyaktighet);
               UT_SNPRINTF(szTx,256,"..KVALITET %s",
                       LC_FormatterKvalitet(sMetode,lNoyaktighet,sSynbarhet,
                                            sHoydeMetode,lHoydeNoyaktighet) );
               LC_PutGi(LC_AppGiL(),szTx);
            
               // ..DATO
               if (*Sys.GrId.pFil->szDato != '\0'  &&  
                   *Sys.GrId.pFil->szDato != '*'  &&  
                   *Sys.GrId.pFil->szDato < '4')
               { 
                  UT_SNPRINTF(szTx,256,"..DATO %s",pFil->szDato);
                  LC_PutGi(LC_AppGiL(),szTx);
               }

               // ..SOSI-VERSJON
               //UT_SNPRINTF(szTx,256,"..SOSI-VERSJON %.2f",((double)(pFil->sSosiVer))/100.0);
               //LC_PutGi(LC_AppGiL(),szTx);
            }

            /* PINFO-buffer */
            Sys.sPibufStatus = LC_PIBUF_TOM;

         } else{                     /* For mange grupper, tab. sprengt */
            UT_SNPRINTF(err().tx,LC_ERR_LEN," %ld",pFil->lAntGr);
            LC_Error(39,"(LC_NyGr)",err().tx);
            Sys.pGrInfo->gnavn = INGEN_GRUPPE;
         }
      }

   } else{                         /* Kladdebase */
                               /* Rens bort gammelt innhold i buffergruppen */
      LC_DelKoL(1,Sys.pGrInfo->nko);
      LC_DelGiL(2,(short)(Sys.pGrInfo->ngi-1));
   
      /* Sjekk om navnet finnes */
      if (LN_FinnNavn(&Sys.GrId.pFil->SosiNavn,const_cast<char*>(sosi),&navn_nr) != 1) {
         LC_PutGi(1,".LINJE");    /* Ukjent gruppenavn ==> Velg ".LINJE" */

      } else {
         LC_PutGi(1,szSosiNavn);
      }

      /* Nytt serienummer */
      *snr = NYTT_SNR;

      /* Nullstill info */
      Sys.pGrInfo->info = 0;
   }

   return (Sys.pGrInfo->gnavn);
}


/*
AR-911001
CH LB_FormaterEnhet                                         Lag GINFO for enhet
CD =============================================================================
CD Formål:
CD Legger inn enhet med høvelig antall siffer.
CD
CD Parametre:
CD Type     Navn   I/U   Forklaring
CD -----------------------------------------------------------------------------
CD char   *streng    i    Peker til streng hvor ginfo skal legges
CD char   *sosi     i    SOSI-navn som skal legges først i strengen
CD double  enhet    i    Aktuell enhet
CD char   *ginfo    r    Peker til oppbygd streng
CD
CD Bruk:
CD LB_FormaterEnhet(streng,sStrengMaxLen,"..ENHET",enhet);
   =============================================================================
*/
char *LB_FormaterEnhet(char *streng,short sStrengMaxLen,const char *SosiNavn,double enhet)
{
   char enhet_buffer[20],*cp;
   short sAntDes = max(1,UT_RoundDS(fabs(min(1.0,log10(enhet)))));

   UT_StrCopy(streng,SosiNavn,sStrengMaxLen);
   UT_StrCat(streng," ",sStrengMaxLen);

   UT_DtoA(enhet,sAntDes,'.',20,enhet_buffer);

   cp = enhet_buffer;
   while (*cp == ' ')
       cp++;

   UT_StrCat(streng,cp,sStrengMaxLen);

   return(streng);
}


/*
AR-930611
CH LC_InsGiL                                              Skyt inn GINFO-linjer
CD =============================================================================
CD Formål:
CD Skyter inn linjer GINFO-delen i en gruppe.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD -----------------------------------------------------------------------------
CD short    linje    i    Linjenummer linjen skal skytes inn forran.
CD                        (Lovlig: 1  til  ngi+1)
CD short    antall   i    Antall linjer som skal skytest inn.
CD short    ngi      r    Antall GINFO-linjer i gruppen etter innskuddet.
CD
CD Bruk:
CD ngi = LC_InsGiL(linje, antall);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_InsGiL(short linje, short antall)
{
   short s,len;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {            /* Aktuell gruppe OK */
      if (linje > 0  &&  linje <= (Sys.pGrInfo->ngi + 1)) {

         /* På slutten av GINFO */
         if (linje == (Sys.pGrInfo->ngi + 1)) {
            for ( ; antall > 0; antall--) {
               LC_AppGiL();
            }

         /* Inni GINFO */
         } else {
            Sys.sGrEndra = (short)END_ENDRA;
            /* Må flytte resten av buffer for å gi plass til de nye linjene */
            memmove(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[linje-1] + antall,
                  Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[linje-1],
                  Sys.pGrInfo->ulGiLen - Sys.Ginfo.ulOfset[linje-1]);

            /* Ny total GINFO-lengde; */
            Sys.pGrInfo->ulGiLen += antall;
 
            /* Antall GINFO-linjer etter utvidelsen */
            Sys.pGrInfo->ngi += antall;

            /* Oppdater offset for resten av GINFO */
            for (s=Sys.pGrInfo->ngi; s>=linje+antall; s--) {
               Sys.Ginfo.ulOfset[s-1] = Sys.Ginfo.ulOfset[s-1-antall] + antall;
            }

            /* Blank ut de nye linjene */
            for (s=0; s<antall; s++) {
               /* Beregn ofset og blank ut linjen */
               if (linje == 1) {
                  Sys.Ginfo.ulOfset[0] = 0;
                  *Sys.Ginfo.pszTx = '\0';
               } else {
                  /* Førte posisjon etter forrige linje */
                  len = (short)strlen(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[linje-2]);
                  Sys.Ginfo.ulOfset[linje-1] = Sys.Ginfo.ulOfset[linje-2] + len + 1;
                  *(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[linje-1]) = '\0';
               }

               linje++;
            }
         }

      } else {
         UT_SNPRINTF(err().tx,LC_ERR_LEN," %d",linje);
         LC_Error(40,"(LC_InsGiL)",err().tx);
      }

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_InsGiL)","");
   }

   return(Sys.pGrInfo->ngi);
}


/*
AR-930610
CH LC_AppGiL                                             Heng på en GINFO-linje
CD =============================================================================
CD Formål:
CD Henger på en linje i GINFO-delen i en gruppe.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD -----------------------------------------------------------------------------
CD short    ngi      r    Antall GINFO-linjer i gruppen etter utvidelsen.
CD                        (Linjenumret på den tilføyde linjen.)
CD
CD Bruk:
CD ngi = LC_AppGiL();
   =============================================================================
*/
SK_EntPnt_FYBA short LC_AppGiL()
{
   if (Sys.GrId.lNr != INGEN_GRUPPE) {            /* Aktuell gruppe OK */
      Sys.sGrEndra = (short)END_ENDRA;
      Sys.pGrInfo->ngi++;  /* Antall GINFO-linjer etter utvidelsen */

      /* Blank ut den nye linjen */
      Sys.pGrInfo->ulGiLen++;
      Sys.Ginfo.ulOfset[Sys.pGrInfo->ngi - 1] = Sys.pGrInfo->ulGiLen - 1;
      *(Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[Sys.pGrInfo->ngi - 1]) = '\0';

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_InsGiL)","");
   }

   return(Sys.pGrInfo->ngi);
}


/*
AR-930611
CH LC_InsKoL                                        Skyt inn koordinatlinjer
CD ==========================================================================
CD Formål:
CD Skyter inn linjer koordinatdelen i en gruppe.
CD
CD Parametre:
CD Type    Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    linje    i    Linjenummer linjen skal skytes inn forran.
CD                        (Lovlig: 1  til  nko+1)
CD long    antall   i    Antall linjer som skal skytest inn.
CD long    nko      r    Antall koordinater i gruppen etter innskuddet.
CD
CD Bruk:
CD nko = LC_InsKoL(linje, antall);
   ==========================================================================
*/
SK_EntPnt_FYBA long LC_InsKoL(long linje, long antall)
{
   double *pdAust = Sys.pdAust + linje - 1;
   double *pdNord = Sys.pdNord + linje - 1;
   LB_INFO * pInfo = Sys.pInfo + linje - 1;
 

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* AKtuell gruppe OK */
      if (Sys.pGrInfo->nko + antall < LC_MAX_KOORD) {
         if (linje > 0  &&  linje <= (Sys.pGrInfo->nko + 1)) {
            Sys.sGrEndra = (short)END_ENDRA;
            if (linje <= Sys.lPibufPnr)  Sys.sPibufStatus = LC_PIBUF_TOM;

            /* Utfør flyttingen */
            memmove(pdAust+antall, pdAust, (Sys.pGrInfo->nko-linje+1) * (sizeof(double)));
            memmove(pdNord+antall, pdNord, (Sys.pGrInfo->nko-linje+1) * (sizeof(double)));
            memmove(pInfo+antall,  pInfo,  (Sys.pGrInfo->nko-linje+1) * (sizeof(LB_INFO)));

            /* Antall koordinater etter utvidelsen */
            Sys.pGrInfo->nko += antall;

            /* Blank ut det nye området */
            while (antall > 0) {
               *pdAust = 0.0;
               *pdNord = 0.0;
               pInfo->dHoyde = HOYDE_MANGLER;
               pInfo->sKp = 0;
               pInfo->ulPiOfset = LC_INGEN_PINFO;
               pdAust++;
               pdNord++;
               pInfo++;
               antall--;
            }

         } else {
            UT_SNPRINTF(err().tx,LC_ERR_LEN," %ld",linje);
            LC_Error(41,"(LC_InsKoL)",err().tx);
         }

      } else {                           /* For mange koordinater */
         LC_Error(162,"(LC_InsKoL)",LX_GetGi(1));
      }
         
   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_InsKoL)","");
   }

   return(Sys.pGrInfo->nko);
}


/*
AR-911001
CH LC_AppKoL                                       Heng på en koordinatlinje
CD ==========================================================================
CD Formål:
CD Henger på en linje i koordinatdelen i en gruppe.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD long    nko      r    Antall koordinater i gruppen etter utvidelsen.
CD
CD Bruk:
CD nko = LC_AppKoL();
   ==========================================================================
*/
SK_EntPnt_FYBA long LC_AppKoL()
{
   if (Sys.GrId.lNr != INGEN_GRUPPE) {                  /* AKtuell gruppe OK */
      if (Sys.pGrInfo->nko + 1 < LC_MAX_KOORD) {
         Sys.sGrEndra = (short)END_ENDRA;
         Sys.pGrInfo->nko++;             /* Antall koordinater etter utvidelsen */

         /* Blank ut den nye linjen */
         *(Sys.pdAust+Sys.pGrInfo->nko - 1) = 0.0;
         *(Sys.pdNord+Sys.pGrInfo->nko - 1) = 0.0;
         (Sys.pInfo+Sys.pGrInfo->nko - 1)->dHoyde = HOYDE_MANGLER;
         (Sys.pInfo+Sys.pGrInfo->nko - 1)->sKp = 0;
         (Sys.pInfo+Sys.pGrInfo->nko - 1)->ulPiOfset = LC_INGEN_PINFO;

      } else {                           /* For mange koordinater */
         LC_Error(162,"(LC_AppKoL)",LX_GetGi(1));
      }

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_AppKoL)","");
   }

   return(Sys.pGrInfo->nko);
}




/*
AR-930611
CH LC_DelGiL                                                 Fjern GINFO-linjer
CD =============================================================================
CD Formål:
CD Fjerner linjer i GINFO-delen i en gruppe.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD -----------------------------------------------------------------------------
CD short    linje    i    Første linjenummer som skal fjernes.
CD                        (Lovlig: 2  til  ngi)
CD short    antall   i    Antall linjer som skal fjernes.
CD short    ngi      r    Antall GINFO-linjer i gruppen etter setting.
CD
CD Bruk:
CD ngi = LC_DelGiL(linje, antall);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_DelGiL(short linje, short antall)
{
   short start;
   char *pszTil, *pszFra;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {                 /* AKtuell gruppe OK */
      if (antall > 0) {
         Sys.sGrEndra = (short)END_ENDRA;

         start = max(linje,2);           /* 2 er første lovlige linje */
         antall -= (start-linje);        /* Juster antall tilsvarende */

         /* Max antall er resten av GINFO */
         antall = min(start+antall-1,Sys.pGrInfo->ngi) - start + 1;

         if (start+antall <= Sys.pGrInfo->ngi) {
            /* Beregn forflytting */
            pszTil = Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[start-1];
            pszFra = Sys.Ginfo.pszTx + Sys.Ginfo.ulOfset[start+antall-1];

            /* Utfør flyttingen */
            memmove(pszTil, pszFra, Sys.pGrInfo->ulGiLen - Sys.Ginfo.ulOfset[start+antall-1] + 1);

            /* Antall GINFO-linjer etter slettingen */
            Sys.pGrInfo->ngi -= antall;

            /* Ny total GINFO-lengde; */
            Sys.pGrInfo->ulGiLen -= (unsigned long)(pszFra - pszTil);

            /* Oppdater offset for resten av GINFO */
            LX_CreGiPeker(&Sys.Ginfo,Sys.pGrInfo->ngi);

         /* Fjerner fram til slutten av GINFO */
         } else {
            /* Antall GINFO-linjer etter slettingen */
            Sys.pGrInfo->ngi -= antall;
            /* Ny total GINFO-lengde; */
            Sys.pGrInfo->ulGiLen = Sys.Ginfo.ulOfset[start-1];
         }
      }

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_DelGiL)","");
   }

   return (Sys.pGrInfo->ngi);
}


/*
AR:2008-04-09
CH LC_DelGiNavn                                   Fjerner egenskap fra GINFO
CD ==========================================================================
CD Formål:
CD Fjerner alle forekomster av gitt egenskap (SOSI-navn) fra GINFO.
CD
CD Parametre:
CD Type     Navn             I/U   Forklaring
CD --------------------------------------------------------------------------
CD char    *pszEgenskapNavn   i    SOSI-navn som skal slettes
CD short    ngi               r    Antall GINFO-linjer i gruppen etter setting
CD
CD Bruk:
CD ngi = LC_DelGiNavn("..RADIUS");
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_DelGiNavn(char *pszEgenskapNavn)
{
   short sGiLinje = 2;
   while (LC_GetGP(pszEgenskapNavn,&sGiLinje,Sys.pGrInfo->ngi) != NULL)
   {
      LC_DelGiL(sGiLinje,1);  
   }

   return Sys.pGrInfo->ngi;
}


/*
AR-930611
CH LC_DelKoL                                              Fjern koordinatlinjer
CD =============================================================================
CD Formål:
CD Fjerner linjer koordinatdelen i en gruppe.
CD
CD Parametre:
CD Type     Navn    I/U   Forklaring
CD -----------------------------------------------------------------------------
CD long    linje    i    Første linje som skal fjernes.
CD                        (Lovlig: 1  til  nko)
CD long    antall   i    Antall linjer som skal fjernes.(Max resten av gruppen)
CD long    nko      r    Antall koordinater i gruppen etter blanking.
CD
CD Bruk:
CD nko = LC_DelKoL(linje, antall);
   =============================================================================
*/
SK_EntPnt_FYBA long LC_DelKoL(long linje, long antall)
{
   long start,s;
   double *pdAust, *pdNord;
   LB_INFO * pInfo,*pI;
   unsigned long ulP1,ulP2,ulDelta;
 

   /* UT_FPRINTF(stderr,"DelKoL: %hd - %hd (%hd) \n",linje,antall,Sys.GrInfo.nko); */

   if (Sys.GrId.lNr != INGEN_GRUPPE) {              /* AKtuell gruppe OK */
      Sys.sGrEndra = (short)END_ENDRA;
      if (linje <= Sys.lPibufPnr)  Sys.sPibufStatus = LC_PIBUF_TOM;
            
      start = max(linje,1);             /* 1 er første lovlige linje */
      antall -= (start-linje);          /* Juster antall tilsvarende */

                                        /* Max antall er resten av punktene */
      antall = min(start+antall-1,Sys.pGrInfo->nko) - start + 1;

      /* UT_FPRINTF(stderr," %hd - %hd\n",start,antall); */

      if (antall > 0) {
         pdAust = Sys.pdAust + start - 1;
         pdNord = Sys.pdNord + start - 1;
         pInfo = Sys.pInfo + start - 1;


         /* Pakk PINFO-bufferet */

         /* Har gruppen PINFO */
         if (Sys.pGrInfo->ulPiLen > 0) {
            /* Er det PINFO på de punktene som er slettet? */
            pI = pInfo;
            ulP1 = LC_INGEN_PINFO;
            for (s=0; s<antall && ulP1==LC_INGEN_PINFO; s++,pI++) {
               if (pI->ulPiOfset != LC_INGEN_PINFO) {
                  ulP1 = pI->ulPiOfset;
               }
            }

            /* Er det funnet PINFO ? */
            if (ulP1 != LC_INGEN_PINFO) {
                /* Sjekk om det er PINFO i resten av gruppen */
               pI = pInfo+antall;
               ulP2 = LC_INGEN_PINFO;
               for (s=start+antall; s<=Sys.pGrInfo->nko && ulP2==LC_INGEN_PINFO; s++,pI++) {
                  if (pI->ulPiOfset != LC_INGEN_PINFO) {
                     ulP2 = pI->ulPiOfset;
                  }
               }


               /* Er det funnet PINFO ? */
               if (ulP2 != LC_INGEN_PINFO) {
                  /* Oppdater ofset */
                  ulDelta = ulP2 - ulP1;
                  pI = pInfo+antall;
                  for (s=start+antall; s <= Sys.pGrInfo->nko; s++,pI++) {
                     if (pI->ulPiOfset != LC_INGEN_PINFO) {
                        pI->ulPiOfset -= ulDelta;
                     }
                  }
 
                  /* Pakk buffer */
                  memmove(Sys.pszPinfo+ulP1, Sys.pszPinfo+ulP2, (Sys.pGrInfo->ulPiLen-ulP2) * (sizeof(char)));
                  Sys.pGrInfo->ulPiLen -= ulDelta;

               /* Det er ikke PINFO i resten av gruppen */
               } else {
                  /* Oppdater total PINFO-lengde */
                  Sys.pGrInfo->ulPiLen = ulP1;
               }
            }
         }

         /* Utfør flyttingen */
         memmove(pdAust, pdAust+antall, (Sys.pGrInfo->nko-start-antall+1) * (sizeof(double)));
         memmove(pdNord, pdNord+antall, (Sys.pGrInfo->nko-start-antall+1) * (sizeof(double)));
         memmove(pInfo,  pInfo+antall,  (Sys.pGrInfo->nko-start-antall+1) * (sizeof(LB_INFO)));
 
         /* Antall koordinater etter sletting */
         Sys.pGrInfo->nko -= antall;
      }

   } else {                              /* Ingen aktuell gruppe */
      LC_Error(49,"(LC_DelKoL)","");
   }

   return(Sys.pGrInfo->nko);
}
       


/*
AR-930803
CH LB_ClGr                                          Nullstill aktuell gruppe
CD ==========================================================================
CD Formål:
CD Nullstill aktuell gruppe.
CD
CD Parametre:
CD Type             Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD
CD Bruk:
CD LB_ClGr ();
   =============================================================================
*/
void LB_ClGr (void)
{
   Sys.pGrInfo->ngi = 0;
   Sys.pGrInfo->nko = 0;
   Sys.pGrInfo->info = 0;
   Sys.pGrInfo->ulGiLen = 0;
   Sys.pGrInfo->ulPiLen = 0;
   Sys.pGrInfo->szObjtype[0] = '\0';
}


/*
AR-930610
CH LB_RGru                                                        Les gruppe
CD ==========================================================================
CD Formål:
CD Leser en datagruppe fra SOSI-fil inn i aktuell gruppe.
CD Eventuelle gamle pekere må være frgitt utenfor denne rutinen.
CD
CD Parametre:
CD Type       Navn    I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil     i   Peker til FilAdm
CD UT_INT64   start    i   Startposisjon på SOSI-filen
CD UT_INT64   slutt    u   Sluttposisjon på SOSI-filen
CD short      siste_gr r   Siste gruppe (0=ikke siste, 1=siste på filen)
CD
CD Bruk:
CD siste_gr = LB_RGru(pFil,start,&slutt);
   ==========================================================================
*/
short LB_RGru(LC_FILADM *pFil,UT_INT64 start,UT_INT64 *slutt)
{
   short type,siste,npinf;
   long snr;
   char *cp,tx[LC_MAX_SOSI_LINJE_LEN];
   LB_LESEBUFFER *pLb = &pFil->pBase->BufAdm;
   LC_FILADM *pAktFil = Sys.GrId.pFil;
   LB_INFO *pInfo = NULL;
   double d;
   short sLagreNavn;      /* Flagg som viser om sosi-navnet skal skrives til buffer */
   short sRefFunnet = UT_FALSE; /* Flagg som viser om referanse av ny type (..REF) er funnet i gruppen */

   double dEnhet = 0.0;
   double dEnhet_h = 0.0;
   double dEnhet_d = 0.0;
   double dOrigoAust = pFil->TransPar.Origo.dAust;      /* Origo til lokale variabler */
   double dOrigoNord = pFil->TransPar.Origo.dNord;


   /* PINFO-buffer er ødelagt */
   Sys.sPibufStatus = LC_PIBUF_TOM;

   /* Angi hvilket tegnsett som skal brukes */
   pLb->sTegnsett = pFil->sTegnsett;

      /* Sett filposisjon */
   LO_ReopenSos(pFil);
   _fseeki64(pFil->pBase->pfSos,start,SEEK_SET);
   pLb->sStatus = LESEBUFFER_TOM;

   type = LB_GetSet(pFil->pBase->pfSos,pLb,&(pAktFil->SosiNavn));

   if (pLb->cur_navn[pLb->cur_niv-1] != L_SLUTT) {    /* Ikke lest ".SLUTT" */
      /* Sjekk at gruppen har lovlig gruppenavn */
      if (type < 0) {
         UT_SNPRINTF(err().tx,LC_ERR_LEN," \"%s %s\"",LN_GetNavn(&(pAktFil->SosiNavn),
                                 pLb->cur_navn[pLb->cur_niv-1]),pLb->pp);
         LC_Error(47,"(LB_RGru)",err().tx);
         exit (2);
      }  
      
      siste = 0;

      /* Nullstiller gruppen */
      LB_ClGr();

      /* Legg inn gruppenavnet med serienummer */
      Sys.pGrInfo->gnavn = pLb->cur_navn[0];
      Sys.pGrInfo->ngi = 1;                           
      snr = strtol(pLb->pp,&cp,10); 
      if (Sys.pGrInfo->gnavn != L_HODE) {
         UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"%s %ld:",LN_GetNavn(&pAktFil->SosiNavn,pLb->cur_navn[0]),snr);
      } else {
         UT_StrCopy(tx,LN_GetNavn(&pAktFil->SosiNavn,pLb->cur_navn[0]),LC_MAX_SOSI_LINJE_LEN);
      }
      UT_StrCopy(Sys.Ginfo.pszTx,tx,LC_MAX_SOSI_LINJE_LEN);
      *Sys.Ginfo.ulOfset = 0;
      Sys.pGrInfo->ulGiLen = (unsigned long)strlen(tx) + 1;

      pLb->set_brukt = SET_BRUKT;

      /* Leser resten av GINFO */
      type = LB_GetSet(pFil->pBase->pfSos,pLb,&(pAktFil->SosiNavn));

      while (type < LEST_KOORD  &&  pLb->cur_niv > 1) {
         if (type != LEST_BLANK) {
            sLagreNavn = UT_TRUE;

            /* GINFO */
            if (type == LEST_GINFO) {
                  /* Referanse */
               if (pLb->cur_navn[pLb->cur_niv-1] == L_REF1  ||
                   pLb->cur_navn[pLb->cur_niv-1] == L_REF2) {
                  Sys.pGrInfo->info |= GI_REF;               
                  if (LN_TestOy(pLb->pp))  Sys.pGrInfo->info |= GI_OY_REF;

                  /* ..REF skal skrives bare på første linje med referanser */ 
                  if (pLb->cur_navn[pLb->cur_niv-1] == L_REF2  &&  sRefFunnet == UT_TRUE) {
                     sLagreNavn = UT_FALSE;
                  }

#ifdef UTGAAR
                  /* Gruppen har høyde informasjon */
               } else if (pLb->cur_navn[pLb->cur_niv-1] == L_HOYDE) {
                  Sys.pGrInfo->info |= GI_NAH;   /* Husk at gruppen har høyde */
#endif

                  /* Spesiell "..ENHET" */
               } else if (pLb->cur_navn[pLb->cur_niv-1] == L_ENHET2) {
                  dEnhet = strtod(pLb->pp,&cp);

                  /* Spesiell "..ENHET-H" */
               } else if (pLb->cur_navn[pLb->cur_niv-1] == L_ENHET2H) {
                  dEnhet_h = strtod(pLb->pp,&cp);

                  /* Spesiell "..ENHET-D" */
               } else if (pLb->cur_navn[pLb->cur_niv-1] == L_ENHET2D) {
                  dEnhet_d = strtod(pLb->pp,&cp);

                  /* Spesiell "...ENHET" */
               } else if (pLb->cur_navn[pLb->cur_niv-1] == L_ENHET3) {
                  dEnhet = strtod(pLb->pp,&cp);

                  /* Spesiell "...ENHET-H" */
               } else if (pLb->cur_navn[pLb->cur_niv-1] == L_ENHET3H) {
                  dEnhet_h = strtod(pLb->pp,&cp);

                  /* Spesiell "...ENHET-D" */
               } else if (pLb->cur_navn[pLb->cur_niv-1] == L_ENHET3D) {
                  dEnhet_d = strtod(pLb->pp,&cp);
               }

               /* Bygg opp GINFO-strengen for denne linjen */
               if (sLagreNavn == UT_TRUE) {
                  UT_StrCopy(tx,LN_GetNavn(&pAktFil->SosiNavn,pLb->cur_navn[pLb->cur_niv-1]),LC_MAX_SOSI_LINJE_LEN);
               } else {
                  *tx = '\0';
               }
               if (sLagreNavn == UT_TRUE  &&  *(pLb->pp) != '\0') {
                  UT_StrCat(tx," ",LC_MAX_SOSI_LINJE_LEN);
               }
               if (*(pLb->pp) != '\0') {
                  UT_StrCat(tx,pLb->pp,LC_MAX_SOSI_LINJE_LEN);
               }
            
               /* Husk at det er funnet ny type referanse */
               if (pLb->cur_navn[pLb->cur_niv-1] == L_REF2) {
                  sRefFunnet = UT_TRUE;     /* Viser at referanse av ny type (..REF) er funnet */
               }

               // Husk OBJTYPE
               if (pLb->cur_navn[pLb->cur_niv-1] == L_OBJTYPE) {
                  UT_StrCopy(Sys.pGrInfo->szObjtype,pLb->pp,LC_MAX_OBJTYPE_LEN);
               }

            /* Kommentar */
            } else {
               UT_StrCopy(tx,pLb->pp,LC_MAX_SOSI_LINJE_LEN);
            }

            /* GINFO og kommentar-linje lagres */
            if (Sys.pGrInfo->ngi >= LC_MAX_GINFO) {
               LC_Error(149,"(LB_RGru)",Sys.Ginfo.pszTx);

            } else if ((Sys.pGrInfo->ulGiLen + strlen(tx) + 1) >= LC_MAX_GINFO_BUFFER) {
               LC_Error(150,"(LB_RGru)",Sys.Ginfo.pszTx);

            } else {
               Sys.pGrInfo->ngi++;    
               UT_StrCopy(Sys.Ginfo.pszTx + Sys.pGrInfo->ulGiLen, tx,LC_MAX_SOSI_LINJE_LEN);
               Sys.Ginfo.ulOfset[Sys.pGrInfo->ngi - 1] = Sys.pGrInfo->ulGiLen;
               Sys.pGrInfo->ulGiLen += (unsigned long)strlen(tx) + 1;
            }
         }

         // Hent neste linje
         pLb->set_brukt = SET_BRUKT;
         type = LB_GetSet(pFil->pBase->pfSos,pLb,&(pAktFil->SosiNavn));
      }

      // Enhet er ikke gitt i GINFO, bruk filhodets enhet
      if (dEnhet == 0.0)  dEnhet = pFil->TransPar.dEnhet;

      // Enhet-H er ikke gitt i GINFO brukes enhet-H fra filhodet
      if (dEnhet_h == 0.0)  dEnhet_h = pFil->TransPar.dEnhet_h;

      // Enhet-D er ikke gitt i GINFO brukes enhet-D fra filhodet
      if (dEnhet_d == 0.0)  dEnhet_d = pFil->TransPar.dEnhet_d;

      /* Husk aktuell ENHET */
      Sys.pGrInfo->dEnhet = dEnhet;
      Sys.pGrInfo->dEnhetHoyde = dEnhet_h;
      Sys.pGrInfo->dEnhetDybde = dEnhet_d;

      /* Koordinatdelen */
      while (pLb->cur_niv >= 2) {
         if (type != LEST_BLANK  &&  type != LEST_KOM) {
            /* Sjekk at det ikke kommer GINFO innimellom koordinatene */
               /* Ikke NØ eller NØH */
            if (pLb->cur_niv == 2  &&
                pLb->cur_navn[pLb->cur_niv-1] != L_NAH  &&
                pLb->cur_navn[pLb->cur_niv-1] != L_NAD  &&
                pLb->cur_navn[pLb->cur_niv-1] != L_NA)
            {
               char szMelding[256];
               UT_SNPRINTF(szMelding,256,"Egenskap \"%s\" i \"%s\"",pLb->tx,Sys.Ginfo.pszTx);
               LC_Error(144,"(LB_RGru)",szMelding);
            }

            /* Sjekk at det ikke blir for mange koordinater */
            if (Sys.pGrInfo->nko >= LC_MAX_KOORD)
            {
               UT_SNPRINTF(err().tx,LC_ERR_LEN," \"%s %ld:\"",LN_GetNavn(&pAktFil->SosiNavn,pLb->cur_navn[0]),snr);
               LC_Error(148,"(LB_RGru)",err().tx);
            }

            if (*pLb->pp != '\0')
            {
               Sys.pGrInfo->nko++;
               pInfo = Sys.pInfo + Sys.pGrInfo->nko - 1;

               /* Regn om til basekoordinater og legg inn i buffer */

              /* Nord-koordinaten */
               d = strtod(pLb->pp,&cp);
               *(Sys.pdNord + Sys.pGrInfo->nko - 1) = dOrigoNord + (d * dEnhet);

               /* Øst-koordinaten */
               d = strtod(cp,&cp);  
               *(Sys.pdAust + Sys.pGrInfo->nko - 1) = dOrigoAust + (d * dEnhet);

               /* ..NØH */
               if (pLb->cur_navn[pLb->cur_niv-1] == L_NAH)
               { 
                  Sys.pGrInfo->info |= GI_NAH;   /* Husk at gruppen har høyde */

                  /* Regn om høyden */
                  d = strtod(cp,&cp);
                  pInfo->dHoyde = d * dEnhet_h;
               }

               /* ..NØD */
               else if (pLb->cur_navn[pLb->cur_niv-1] == L_NAD)
               {
                  Sys.pGrInfo->info |= GI_NAD;   /* Husk at gruppen har dybde */

                  /* Regn om dybden (Lagres som terrengverdi i mm) */
                  d = strtod(cp,&cp);
                  pInfo->dHoyde = d * dEnhet_d;
               }

               else 
               {
                  pInfo->dHoyde = HOYDE_MANGLER;
               }
            }

            pLb->set_brukt = SET_BRUKT;

            /* Neste sett */
            type = LB_GetSet(pFil->pBase->pfSos,pLb,&(pAktFil->SosiNavn));
            

                                 /* PINFO */
            if (Sys.pGrInfo->nko > 0)
            {
               pInfo->sKp = 0;
               pInfo->ulPiOfset = LC_INGEN_PINFO;
               npinf = 0;
               *tx = '\0';
               while (pLb->cur_niv > 2)
               {
                  if (type != LEST_BLANK  &&  type != LEST_KOM)
                  {
                     if (pLb->cur_navn[pLb->cur_niv-1] == L_KP) 
                     {    /* Knutepunkt */
                        /* Sjekk om det er flere kp i samme punkt */
                        if (pInfo->sKp != 0)
                        {
                           //UT_SNPRINTF(err().tx,LC_ERR_LEN," \"%s\"",pLb->pp);
                           UT_SNPRINTF(err().tx,LC_ERR_LEN," \"%s\" pnr.: %ld ",LX_GetGi(1), Sys.pGrInfo->nko);
                           LC_Error(145,"(LB_RGru)",err().tx);
                        }
                        else
                        {
                           pInfo->sKp = (short)strtol(pLb->pp,&cp,10);
                           Sys.pGrInfo->info |= GI_KP;
                        }

                     } else {                                  /* Annen PINFO */
                        npinf++;
                        if (npinf > 1)  UT_StrCat(tx," ",LC_MAX_SOSI_LINJE_LEN);
                        UT_StrCat(tx, LN_GetNavn(&(pAktFil->SosiNavn),pLb->cur_navn[pLb->cur_niv-1]),
                                  LC_MAX_SOSI_LINJE_LEN);
                        if (*(pLb->pp) != '\0'){
                           UT_StrCat(tx," ",LC_MAX_SOSI_LINJE_LEN);
                           UT_StrCat(tx,pLb->pp,LC_MAX_SOSI_LINJE_LEN);
                        }
                     
                        if (strlen(tx) > LC_MAX_SOSI_LINJE_LEN) {
                           tx[30] = '\0';
                           LC_Error(143,"(LB_RGru)",tx);
                           tx[0] = '\0';
                           npinf = 0;
                        }
                     }
                  }

                  pLb->set_brukt = SET_BRUKT;

                  /* Neste sett */
                  type = LB_GetSet(pFil->pBase->pfSos,pLb,&(pAktFil->SosiNavn));
               }

               /* Lagre PINFO */
               if (*tx != '\0') {
                  if (Sys.pGrInfo->ulPiLen == 0) {
                     pInfo->ulPiOfset = 0;
                  } else {
                     pInfo->ulPiOfset = Sys.pGrInfo->ulPiLen;
                  }

                  if ((Sys.pGrInfo->ulPiLen + strlen(tx) + 1) >= LC_MAX_PINFO_BUFFER) {
                     LC_Error(161,"(LB_RGru)",Sys.Ginfo.pszTx);

                  } else {
                     UT_StrCopy(Sys.pszPinfo + pInfo->ulPiOfset, tx, LC_MAX_PINFO_BUFFER-pInfo->ulPiOfset);
                     Sys.pGrInfo->ulPiLen += (unsigned long)strlen(tx) + 1;
                  }

                  Sys.pGrInfo->info |= GI_PINFO;
               }
            }         

         } else {       /* Fyll-linje er lest */
            pLb->set_brukt = SET_BRUKT;
            /* Neste sett */
            type = LB_GetSet(pFil->pBase->pfSos,pLb,&(pAktFil->SosiNavn));

         }
      }

   } else {                                         /* ".SLUTT" */
       siste = 1;
   }

   if (Sys.pGrInfo->gnavn == L_HODE  &&  !siste ) {  /* Oppdater filtabellen */
       LO_BeFt(pFil);
   }

   *slutt = pLb->startpos;                         /* Slutt - filposisjon */
   return(siste);
}


/*
AR-911001
CH LB_Save                                           Tøm skrivekøa for 1 fil
CD ==========================================================================
CD Formål:
CD Skriver gruppene som ligger i skrivekø ut til SOSI-fil.
CD
CD Parametre:
CD Type       Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i    Peker til FilAdm
CD
CD Bruk:
CD LB_Save(pFil);
   ==========================================================================
*/
void LB_Save(LC_FILADM *pFil)
{
   LC_BGR Bgr,AktBgr;
   long lNr;
   short ngi;
   long  nko;
   unsigned short info;

   Bgr.pFil = pFil;

   if (Sys.lAntSkriv > 0L) {                     /* Er det noen i kø ? */
      AktBgr = Sys.GrId;
      for (lNr=0L; lNr<pFil->lAntGr; lNr++) {
         if (LI_InqBt(pFil,lNr,BT_SKRKO)) {           /* I kø ? */
            Bgr.lNr = lNr;
            LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
            LB_Swap();
         }
      }
      if (AktBgr.lNr != INGEN_GRUPPE) { 
         LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);
      } else {
         Sys.GrId = AktBgr;
      }
   }  
}


/*
AR-911001
CH LC_Save                                                     Tøm skrivekøa
CD ==========================================================================
CD Formål:
CD Skriver gruppene som ligger i skrivekø ut til SOSI-fil.
CD
CD Parametre: ingen
CD
CD Bruk:
CD LC_Save();
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_Save(void)
{
   LC_BASEADM * pBase;
   LC_FILADM *pFil;

   if (Sys.lAntSkriv > 0L) {                     /* Er det noen i kø ? */
      /* Skanner alle baser og alle filer */
      for (pBase=Sys.pForsteBase; pBase!=NULL; pBase=pBase->pNesteBase) {
         for (pFil=pBase->pForsteFil; pFil!=NULL; pFil=pFil->pNesteFil) {
            LB_Save(pFil);
         }
         LO_CloseSos(pBase);
      }

      Sys.lAntSkriv = 0L;
   }
}


/*
AR-930610
CH LB_Swap                                  Dump gruppe fra buffer til SOSI
CD ==========================================================================
CD Formål:
CD Skriver en gruppe fra buffer tilbake til SOSI-fil. Ledig plass fram til
CD neste gruppe blir blanket. Hvis det ikke er plass blir gruppen flyttet
CD til slutten av filen. Fjerner gruppen fra skrivekøa.
CD
CD Parametre: ingen
CD
CD Bruk:
CD LB_Swap()
   ==========================================================================
*/
void LB_Swap(void)
{
   short siste;
   long nko;
   UT_INT64 start,neste;

   /* Filnummer og posisjon */
   start = Sys.pGrInfo->sosi_st;
   nko = Sys.pGrInfo->nko;

   if (start == NY_SOSI_ST){                       /* Ny gruppe? */
      siste = 1;                                   /* På slutten */
      start = Sys.GrId.pFil->n64AktPos;
   } else{
      siste = LB_Plass(Sys.GrId.pFil,start,&neste);    /* Finn ledig plass */
   }  

   /* Ikke siste gruppe */
   if ( ! siste ) {
      /* Skriver */
      if ( ! LB_WGru(SKRIV_VANLIG,1,nko,Sys.GrId.pFil,start,&neste)) {
         /* For lite plass, blank ut "gammelt" området på SOSI-filen */
         _fseeki64(Sys.GrId.pFil->pBase->pfSos,start,SEEK_SET);
         Sys.GrId.pFil->pBase->BufAdm.sStatus = LESEBUFFER_TOM;
         LB_WriteBlank(Sys.GrId.pFil->pBase->pfSos,Sys.GrId.pFil->sTegnsett,neste); /* Blank ut området */

         /* Gruppen skrives på slutten av SOSI-filen */
         siste = 1;
         start = Sys.GrId.pFil->n64AktPos;
      }
   }

   /* Siste gruppe på SOSI-filen */
   if ( siste ) {
      Sys.pGrInfo->sosi_st = start;       /* Ny filposisjon */
      neste = LLONG_MAX;
      /* Skriver */
      LB_WGru (SKRIV_SISTE,1,nko,Sys.GrId.pFil,start,&neste);

      Sys.GrId.pFil->n64AktPos = neste;                    /* Ny slutt-posisjon */
   }

   LI_ClrBt(Sys.GrId.pFil,Sys.GrId.lNr,BT_SKRKO);       /* Fjern fra skrivekø */
}


/*
AR-930610
CH LB_WGru                                         Skriv gruppe til SOSI-fil
CD ==========================================================================
CD Formål:
CD Skriver aktuell gruppe fra buffer til en SOSI-fil.
CD Sjekker ikke om buffer er endret i fht. SOSI. (Skriver alltid.)
CD
CD Parametre:
CD Type       Navn     I/U  Forklaring
CD --------------------------------------------------------------------------
CD short      strategi  i   Skrivestrategi: Følgende konstanter er definert:
CD                          KONTROLLER_PLASS = Bare kontroller plass,
CD                                             (ikke skriv til SOSI).
CD                          SKRIV_VANLIG     = Skriv til SOSI, vanlig.
CD                          SKRIV_SISTE      = Skriv til SOSI, med .SLUTT
CD                                             og sett filstørrelse.
CD long       fra_punkt i   Punktnummer for første koordinat som skal skrives.
CD                          (Lovlig:  1  <=  fra_punkt  <=  nko)
CD long       antall    i   Antall koordinatlinjer som skal skrives.
CD                          (Lovlig:  0  <=  antall  <=  nko)
CD                          (Ved skriv av annet enn aktuell gruppe skrives
CD                          alltid hele gruppen.)
CD LC_FILADM *pFil      i   Peker til FilAdm for fil det skal skrives til
CD UT_INT64   ffipos    i   Startposisjon på SOSI-filen
CD UT_INT64  *lfipos   iu   inn: Første pos i neste gruppe (må ikke overskrives)
CD                          ut : Første pos etter gruppen (etter event. utrop.)
CD short      ist       r   Status: 1 = Skrevet OK
CD                               0 = Ikke plass, må flyttes til slutten
CD
CD Bruk:
CD ok = LB_WGru (strategi,fra_punkt,antall,pFil,ffipos,&lfipos);
=============================================================================
*/
short LB_WGru (short strategi,long fra_punkt,long antall,
               LC_FILADM *pFil,UT_INT64 ffipos,UT_INT64 *lfipos)
{
   short i,gnavn,ngi,skriv_nah,nah,forrige_nah;
   long pt,l;
   unsigned long ulOfset;
   char tx[LC_MAX_SOSI_LINJE_LEN],*cp,szOrd[60];
   char szError[256];
   double dN,dA;
   short sFilMindre;
   UT_INT64 Size;
   char szKp[50];
   FILE *pfSos = NULL;
   double dEnhet = 0.0;
   double dEnhetHoyde = 0.0;
   double dEnhetDybde = 0.0;
   double dOrigoNord = pFil->TransPar.Origo.dNord;
   double dOrigoAust = pFil->TransPar.Origo.dAust;
   UT_INT64 fpos;
   UT_INT64 nfipos;                   /* Neste filposisjon (første etter linjen) */
   UT_INT64 afipos = ffipos;                 /* Aktuell filposisjon */


#ifdef test
   SH_OutTx(1,1,"WGru:");
   SH_OutShort(0,1,1,strategi);
   SH_OutShort(0,1,3,fra_punkt);
   SH_OutShort(0,1,4,antall);
   SH_OutLong(0,1,5,pBgr->lNr);
   SH_OutTx(0,1,pBgr->pFil->pszNavn);
   SH_OutTx(0,1,pFil->pszNavn);
   SH_OutTx(2,1,"ffipos:");SH_OutLong(0,0,10,ffipos);
   SH_OutTx(0,1,"lfipos:");SH_OutLong(0,0,10,*lfipos);
   SH_WaitKb();
   SH_ErLine(SH_SCR,1);
   SH_ErLine(SH_SCR,2);
#endif

/* printf("\nWGru:fra: %s : %ld nko:%ld til %s",
       strrchr(pBgr->pFil->pszNavn,'\\')+1,
       pBgr->lNr,                                     
       antall,                                     
       strrchr(pFil->pszNavn,'\\')+1);           */

   /* Hent diverse opplysninger om gruppen */
   gnavn  = Sys.pGrInfo->gnavn;
   ngi  = Sys.pGrInfo->ngi;
   /* antall  = Sys.pGrInfo->nko;      (Ant.koord kommer inn i kallet)   */
   /* info = Sys.pGrInfo->info; */

   if (strategi != KONTROLLER_PLASS) {
       LO_ReopenSos(pFil);                  /* Aktiviser SOSI-filen */
       pfSos = pFil->pBase->pfSos;
       _fseeki64 (pfSos, afipos, SEEK_SET);
       pFil->pBase->BufAdm.sStatus = LESEBUFFER_TOM;
   }

                                     /* Skriv GINFO */
   for (i = 1; i <= ngi; i++) {
      UT_StrCopy(tx,LX_GetGi(i),LC_MAX_SOSI_LINJE_LEN);
      UT_StrCat(tx,"\r\n",LC_MAX_SOSI_LINJE_LEN);

      /* Spesiell ..ENHET */
      if (LN_Enhet(&(Sys.GrId.pFil->SosiNavn),tx)) {
         cp = tx;
         while(!UT_IsSpace(*cp)){
             cp++;
         }
         dEnhet = strtod(cp,&cp);
      }

      /* Spesiell ..ENHET-H */
      if (LN_EnhetHoyde(&(Sys.GrId.pFil->SosiNavn),tx)) {
         cp = tx;
         while(!UT_IsSpace(*cp)){
             cp++;
         }
         dEnhetHoyde = strtod(cp,&cp);
      }

      /* Spesiell ..ENHET-D */
      if (LN_EnhetDybde(&(Sys.GrId.pFil->SosiNavn),tx)) {
         cp = tx;
         while(!UT_IsSpace(*cp)){
             cp++;
         }
         dEnhetDybde = strtod(cp,&cp);
      }

      /* GINFO, og kommentar-linje lagres */
      /*
      * Sjekk om plassen er oppbrukt.
      * (Overskriver neste guppe.)
      */
      nfipos = afipos + (long)strlen(tx);
      while (nfipos > *lfipos) {
         if (gnavn == L_HODE) {
            /* Prøver å flytte gruppen til slutten */
            if (!LB_FlyttGrTilSlutt(pFil,*lfipos,lfipos)) {
               LC_Error(146,"(LB_WGru)",pFil->pszNavn);
               return 1;
            }

         } else {
            return 0;
         }
      }

      /* Skriv til SOSI */
      if (strategi != KONTROLLER_PLASS) {
         LB_WriteLine(pfSos,pFil->sTegnsett,tx);
      }
      afipos = nfipos;
   }

   /* Enhet er ikke gitt i GINFO, bruk filhodets enhet */
   if (dEnhet == 0.0)  dEnhet = pFil->TransPar.dEnhet;

   // Enhet-H er ikke gitt i GINFO, bruk enhet-H fra filhodet
   if (dEnhetHoyde == 0.0)  dEnhetHoyde = pFil->TransPar.dEnhet_h;

   // Enhet-D er ikke gitt i GINFO, bruk enhet-D fra filhodet
   if (dEnhetDybde == 0.0)  dEnhetDybde = pFil->TransPar.dEnhet_d;


   /* Hopp fram til første koordinat som skal skrives */
   pt = fra_punkt - 1;

   forrige_nah = -1;
   skriv_nah = 1;         /* Skriv ..NØ(H) før første koordinat linje */

   /* =====> Skriv koordinater og PINFO */
   for (l=0; l<antall; l++,pt++) {
      nah = ((Sys.pInfo + pt)->dHoyde != HOYDE_MANGLER);

       /* Må skrive ..NØ eller ..NØH ved skifte mellom disse */
      if (forrige_nah != nah) {
         skriv_nah = 1;
      }

      if (skriv_nah) {               /* Skriv ..NØ / ..NØH / ..NØD */
         if (nah) {

            if ((Sys.pGrInfo->info & GI_NAH) != 0) {
               UT_StrCopy(tx,"..NØH\r\n",LC_MAX_SOSI_LINJE_LEN);
            } else {
               UT_StrCopy(tx,"..NØD\r\n",LC_MAX_SOSI_LINJE_LEN);
            }
            nfipos = afipos + 7;
         } else {
            UT_StrCopy(tx,"..NØ\r\n",LC_MAX_SOSI_LINJE_LEN);
            nfipos = afipos + 6;
         }
         forrige_nah = nah;

         if (nfipos > *lfipos) {            /* Sjekk om plassen er oppbrukt */
            return(0);                      /* Overskriver neste guppe */
         }

         if (strategi != KONTROLLER_PLASS) {
            LB_WriteLine(pfSos,pFil->sTegnsett,tx);    /* Skriv til SOSI */
         }
         afipos = nfipos;
         skriv_nah = 0;
      }

      /* -----> Koordinater */
      dN = UT_RoundDD((*(Sys.pdNord+pt) - dOrigoNord) / dEnhet);
      dA = UT_RoundDD((*(Sys.pdAust+pt) - dOrigoAust) / dEnhet);
      UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"%.0f %.0f",dN,dA);

      // ----- Høyde eller dybde
      if (nah)
      {
         // NØH
         if ((Sys.pGrInfo->info & GI_NAH) != 0)
         {
            dA = UT_RoundDD((Sys.pInfo+pt)->dHoyde / dEnhetHoyde);
         }

         // NØD
         else
         {
            dA = UT_RoundDD((Sys.pInfo+pt)->dHoyde / dEnhetDybde);
         }

         UT_SNPRINTF(szOrd,60," %.0f",dA);
         UT_StrCat(tx,szOrd,LC_MAX_SOSI_LINJE_LEN);
      }

      // ----- PINFO
      ulOfset = (Sys.pInfo+pt)->ulPiOfset;

      if (ulOfset != LC_INGEN_PINFO)
      {
         skriv_nah = 1;
         UT_StrCat(tx," ",LC_MAX_SOSI_LINJE_LEN);
         UT_StrCat(tx,Sys.pszPinfo+ulOfset,LC_MAX_SOSI_LINJE_LEN);
      }

      // ----- ...KP n
      if ((Sys.pInfo+pt)->sKp != 0)
      {
         skriv_nah = 1;
         UT_SNPRINTF(szKp,50," ...KP %hd",(Sys.pInfo+pt)->sKp);
         UT_StrCat(tx,szKp,LC_MAX_SOSI_LINJE_LEN);
      }

      // Sjekk at linjen ikke er for lang
      if (strlen(tx) > (LC_MAX_SOSI_LINJE_LEN - 10))
      {
         tx[LC_MAX_SOSI_LINJE_LEN -10] = '\0';
         UT_StrCat(tx, " ?????", LC_MAX_SOSI_LINJE_LEN);
         LC_Error(134,"(LB_WGru)",LX_GetGi(1));
      }

      // Legg på linjeslutt
      UT_StrCat(tx,"\r\n",LC_MAX_SOSI_LINJE_LEN);
                                           
      /* Sjekk om plassen er oppbrukt */
      nfipos = afipos + (long)strlen(tx);
      if (nfipos > *lfipos) {                /* Overskriver neste guppe */
         /* printf(" (Overskriv)"); */
         return(0);                        /* ===> RETUR */
      }

      if (strategi != KONTROLLER_PLASS){
         LB_WriteLine(pfSos,pFil->sTegnsett,tx);               /* Skriver */
      }

      afipos = nfipos;
   }

   if (strategi == SKRIV_SISTE)                 /* På slutten av filen */
   {
      /* Akt.pos + reserveplass */
      *lfipos = _ftelli64(pfSos) + (UT_INT64)Sys.sResPlass;
      /* Legg på 200 ekstra etter filhodet */
      if (ffipos == 0)  *lfipos += 200;
      LB_WriteBlank(pfSos,pFil->sTegnsett,*lfipos);

      /* Skriver .SLUTT */
      UT_StrCopy(tx,".SLUTT\r\n",LC_MAX_SOSI_LINJE_LEN);                 
      LB_WriteLine(pfSos,pFil->sTegnsett,tx);

      /* Husk akt. filposisjon */
      fpos = _ftelli64(pfSos);
      if (fpos == -1) {
         UT_strerror(szError,256,errno);
         UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"%s - %s",pFil->pszNavn,szError);
         LC_Error(142,"(LB_WGru)",tx);
      }

      // Sjekk om filstørrelsen er redusert
      sFilMindre = UT_FALSE;
      if (Sys.sUtvidModus != LC_UTVID_SIKKER) {
         if (UT_InqPathSize_i64(pFil->pszNavn,&Size) == 0) {
            if (fpos <= Size)  sFilMindre = UT_TRUE;
         }
      }

      // Filstørrelsen er redusert, eller sikker utvidingsmodus
      if (sFilMindre == UT_TRUE  ||  Sys.sUtvidModus == LC_UTVID_SIKKER) {

         /* Steng filen for å bevare byte-pekeren */
         LO_CloseSos(pFil->pBase);

         /* Sett filstørrelse */
         if (fpos != -1) {
            if ((i = UT_SetPathSize_i64(pFil->pszNavn,fpos-1)) != 0) {
               UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"(%s, Posisjon:%lld, Se log-fil for detaljert beskrivelse)",pFil->pszNavn,fpos-1);
               LC_Error(92,"(LB_WGru)",tx);
            }
         }
      }
   }

   else
   {
      if (strategi != KONTROLLER_PLASS) {
                            /* Blank fram til neste gruppe, og tøm buffer */
         LB_WriteBlank(pfSos,pFil->sTegnsett,*lfipos);
      }
   }

/* printf(" (OK)"); */

   return(1);
}


/*
AR-920309
CH LB_FlyttGrTilSlutt                      Flytt gruppe til slutten av filen
CD ==========================================================================
CD Formål:
CD Flytt gruppe til slutten av filen
CD
CD Parametre:
CD Type       Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil     i    Peker til FilAdm
CD UT_INT64   start    i    Startposisjon på SOSI-filen (første pos. i gr.)
CD UT_INT64  *neste    u    Startposisjon i neste gruppe (første pos. etter gr.)
CD short      status   r    Status:  UT_FALSE = Feil
CD                                   UT_TRUE = OK
CD
CD Bruk:
CD status = LB_FlyttGrTilSlutt(forste,&neste)
   ==========================================================================
*/
static short LB_FlyttGrTilSlutt(LC_FILADM *pFil, UT_INT64 start, UT_INT64 *neste)
{
   UT_INT64 lCurFilpos;
   long lAntTegn,lNr;
   char *pszBuffer;
   LC_GRTAB_LINJE * pGrInfo;

   /* Husk aktuell filposisjon */
   lCurFilpos = _ftelli64(pFil->pBase->pfSos);

   /* Sjekk gruppetabellen for å finne hvilken gruppe */
   /* som starter i start posisjonen. */
   for (lNr=1L; lNr<pFil->lAntGr; lNr++) {
      pGrInfo = LI_GetGrt(pFil,lNr);
      if (pGrInfo->ngi != 0) {
         if (pGrInfo->sosi_st == start) {
            /* Oppdater startposisjon */
            pGrInfo->sosi_st = pFil->n64AktPos;
            break;
         }
      }
   }

   /* Finn starten av neste gruppe */
   LB_Plass (pFil,start,neste);

   /* Alloker buffer for flyttingen */
	lAntTegn = (long)(*neste - start);
	pszBuffer = (char*)UT_MALLOC((size_t)lAntTegn * sizeof(char));

	/* Les inn gruppen */
	_fseeki64(pFil->pBase->pfSos,start,SEEK_SET);
	fread(pszBuffer,sizeof(char),(size_t)lAntTegn,pFil->pBase->pfSos);

	/* Skriv gruppen */
	_fseeki64(pFil->pBase->pfSos,pFil->n64AktPos,SEEK_SET);
   fwrite(pszBuffer,sizeof(char),(size_t)lAntTegn,pFil->pBase->pfSos);

   /* Ny sluttposisjon */
   pFil->n64AktPos = _ftelli64(pFil->pBase->pfSos);

   /* Skriver .SLUTT */
   UT_StrCopy(pszBuffer,".SLUTT\r\n",lAntTegn);
   LB_WriteLine(pFil->pBase->pfSos,pFil->sTegnsett,pszBuffer);
	UT_FREE(pszBuffer);
	/* Posisjoner tilbake til opprinnelig posisjon */
   _fseeki64(pFil->pBase->pfSos,lCurFilpos,SEEK_SET);

   return UT_TRUE;
}


/*
AR-920309
CH LB_Plass                                          Finn tilgjengelig plass
CD ==========================================================================
CD Formål:
CD Scanner SOSI-filen og finner hvor mye plass som er tilgjengelig for
CD gruppen. (Uten flytting.)
CD
CD Parametre:
CD Type       Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil     i    Peker til FilAdm
CD UT_INT64      start    i    Startposisjon på SOSI-filen (første pos. i gr.)
CD UT_INT64     *neste    u    Startposisjon i neste gruppe (første pos. etter gr.)
CD short      siste    r    Siste gruppe:  UT_FALSE = Ikke siste gruppe
CD                                         UT_TRUE = Siste gruppe
CD
CD Bruk:
CD siste = LB_Plass (pFil,start,&neste)
   ==========================================================================
*/
short LB_Plass (LC_FILADM *pFil, UT_INT64 start, UT_INT64 *neste)
{
   LB_LESEBUFFER * pLb = &pFil->pBase->BufAdm;

   LO_ReopenSos(pFil);      /* Aktiviser SOSI-filen */
   _fseeki64(pFil->pBase->pfSos,start,SEEK_SET);
   pLb->sStatus = LESEBUFFER_TOM;
   
   /* Gruppenavn på egen gruppe */
   LB_GetSet(pFil->pBase->pfSos,pLb,&(pFil->SosiNavn));

   /* Scann gruppen sett for sett */
   do {
      pLb->set_brukt = SET_BRUKT;
      LB_GetSet(pFil->pBase->pfSos,pLb,&(pFil->SosiNavn));
   } while (pLb->cur_niv != 1);

   *neste = pLb->startpos;

   return ((pLb->cur_navn[0] == L_SLUTT)?  1 : 0 );  /* Siste gruppe? */
}


/*
GL-880119
AR-911001
CH LB_WriteBlank                                        Fyller inn "!!!!!!!"
CD ==========================================================================
CD Formål:
CD Fyller området FRA-OG-MED current-posisjon og fram TIL,
CD (men ikke inklusiv) , ltilpos med !!!!!.
CD Rutina takler fra 1 til mange posisjoner.
CD
CD        curr-pos                       ltilpos
CD          +------------------------------+
CD          !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD FILE    *fil       i    Filpeker
CD short    sTegnsett i    Tegnsett (Def fra fyut.h)
CD long     ltilpos   i    Posisjon det skal blankes fram til
CD
CD Bruk:
CD LB_WriteBlank(fil,sTegnsett,ltilpos);
   ===================================================================
*/
static void LB_WriteBlank (FILE *fil,short sTegnsett,UT_INT64 ltilpos)
{
   UT_INT64 fpos;
   long  iant;
   short  i;
   char buffer[LC_MAX_SOSI_LINJE_LEN] = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n";

   fpos = _ftelli64(fil);       /* Skriver fulle linjer */
   if (ltilpos > fpos){
      while (fpos < (ltilpos-40)){
         LB_WriteLine(fil,sTegnsett,buffer);
         fpos = _ftelli64(fil);  
      }
                                         /* Skriver resten */
      iant = (long)(ltilpos-fpos);
      if (iant > 2) {                /* ant fyll > 2  */
         for (i=0 ;( i < (iant - 2)) ; i++) {
            buffer[i] = '!';
         }
         buffer[iant-2] = '\r';
         buffer[iant-1] = '\n';
         buffer[iant]   = '\0';
         LB_WriteLine(fil,sTegnsett,buffer);

      }else {                          /* ant fyll = 1 eller 2 */
                                      /* blank sist på forrige linje */
         _fseeki64(fil,-2L,SEEK_CUR);
         if      (iant == 1)   UT_StrCopy(buffer, " \r\n", LC_MAX_SOSI_LINJE_LEN);
         else if (iant == 2)   UT_StrCopy(buffer, "  \r\n", LC_MAX_SOSI_LINJE_LEN);
         LB_WriteLine(fil,sTegnsett,buffer);
      }
   }
}


/*
AR-911001
CH LB_WriteLine                                    Lavnivå skriv tekst linje
CD ==========================================================================
CD Formål:
CD Lavnivå overbygning ove write i C-biblioteket for å skrive en linje.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD FILE    *fil       i    Filpeker
CD short    sTegnsett i    Tegnsett (Spesifisert i UT)
CD char    *tx        i    Tekststreng som skal skrives.
CD short    antall    r    Antall tegn skrevet, eller -1 ved feil.
CD
CD Bruk:
CD antall = LB_WriteLine(fil,sTegnsett,tx);
   ==========================================================================
*/
short LB_WriteLine (FILE *fil,short sTegnsett,const char *tx)
{
   UT_KonverterTegnsett(LC_INTERNT_TEGNSETT,sTegnsett,(unsigned char*)tx);
   return (short)fwrite(tx,strlen(tx),1,fil);
}


/*
AR-920909
CH LB_FyllBuffer                         Oppdater lesebuffer fra SOSI-filen
CD ==========================================================================
CD Formål:
CD Les neste linje fra SOSI-filen inn i lesebuffer.
CD Konverterer til rett internt tegnsett.
CD
CD Parametre:
CD Type            Navn   I/U   Forklaring
CD --------------------------------------------------------------------------
CD FILE           *fil     i    Filpeker
CD LB_LESEBUFFER  *plb     i    Peker til bufferstruktur
CD
CD Bruk:
CD LB_FyllBuffer(fil,&lb);
   ===================================================================
*/
void LB_FyllBuffer (FILE *fil,LB_LESEBUFFER *plb)
{
   short ierr;


   /* Husk filposisjonen */
   plb->filpos =  _ftelli64(fil);

   /* Les */
   if ((ierr = UT_ReadLine(fil,LC_MAX_SOSI_LINJE_LEN,plb->tx)) != UT_OK) {
      /* Lesefeil */
      if (ierr == UT_EOF) {
         LC_Error(42,"(LB_FyllBuffer)","");   /* EOF */
      } else {
         LC_Error(43,"(LB_FyllBuffer)","");   /* Annen lesefeil */
      }
      exit(1);
   }

   /* Konverter til rett tegnsett */
   UT_KonverterTegnsett(plb->sTegnsett,LC_INTERNT_TEGNSETT,(unsigned char*)plb->tx);

   if (strlen(plb->tx) >= LC_MAX_SOSI_LINJE_LEN-2)
   {
      char szMelding[LC_MAX_SOSI_LINJE_LEN + 10];
      UT_SNPRINTF(szMelding, LC_MAX_SOSI_LINJE_LEN + 10, "\"%s\"", plb->tx);
      LC_Error(164,"(LB_FyllBuffer)",szMelding);
      exit(1);
   }

   /* Nullstill pekere */
   plb->cp = plb->np = plb->pp = plb->ep = plb->tx;
   plb->set_brukt = SET_BRUKT;
   plb->sStatus = LESEBUFFER_OK;
}


/*
AR-920909
CH LB_GetSet                               Hent SOSI-navn og verdi fra buffer
CD =============================================================================
CD Formål:
CD Hen ett SOSI-navn og tilhørende verdi fra lesebuffer.
CD Inn: Hvis buffer har gyldig innhold peker "plb->np" til posisjon
CD      der tolking skal starte.
CD
CD Parametre:
CD Type            Navn   I/U   Forklaring
CD -----------------------------------------------------------------------------
CD FILE           *fil     i    Filpeker
CD LB_LESEBUFFER  *plb     i    Peker til bufferstruktur
CD LC_NAVNETABELL * pNavn   i    Peker til navnetabell
CD short           type    r    Hva er hentet: >= 0 : Gruppenavn,linjenr
CD                                                   i navnetab.
CD                                  LEST_KOORD (-1): Koordinatlinje
CD                                  LEST_BLANK (-2): Fyll-linje
CD                                  LEST_GINFO (-3): Annen GINFO
CD                                  LEST_KOM   (-4): Kommentarlinje
CD
CD Bruk:
CD type = LB_GetSet(fil,&lb,pNavn);
   =============================================================================
*/
short LB_GetSet(FILE *fil,LB_LESEBUFFER *plb,LC_NAVNETABELL * pNavn)
{
   short navn_nr,gml_niv;
   char cTmp;

   /* Sjekk at buffer har rett innhold */
   if (plb->sStatus != LESEBUFFER_OK) {
      LB_FyllBuffer(fil,plb);
   }

   /* Henter nytt sett */
   if (plb->set_brukt == SET_BRUKT) {
      plb->cp = plb->np;

      do {
         /* Hopp over ledende blanke */
         while (UT_IsSpace(*plb->cp)) {
            (plb->cp)++;
         }
         /* Linjen er oppbrukt, les inn ny */
         if (*plb->cp == '\0') {
            LB_FyllBuffer(fil,plb);
         }
      } while (UT_IsSpace(*plb->cp)  ||  *plb->cp == '\0');

      plb->np = plb->cp;
   
      if (*plb->cp == '.') {                  /* --------- SOSI-navn */
         plb->startpos = plb->filpos + (plb->cp - plb->tx); /* Husk filposisjon */
         /* Scann over navnet (Ikke \0, mellomrom eller filslutt) */
         while (*plb->cp  &&  !UT_IsSpace(*plb->cp)  &&  *plb->cp != 26) {
            (plb->cp)++;
         }
         cTmp = *plb->cp;
         *plb->cp = '\0';

         /* Søk i navnetabellen */
         gml_niv = plb->cur_niv;
         plb->cur_niv = LN_PakkNavn(pNavn,plb->np,&navn_nr,&(plb->cur_ant_par));
         plb->cur_navn[plb->cur_niv - 1] = navn_nr;

         *plb->cp = cTmp;

         /* Sjekk mot sprang i prikknivå */
         if ((plb->cur_niv - gml_niv) > 1) {
            LC_Error(147,"(LB_GetSet)",plb->np);
         }

         /* Handter parameter */
         if (navn_nr != L_SLUTT) {
            do {
               /* Hopp over ledende blanke */
               while (UT_IsSpace(*plb->cp)) {
                  (plb->cp)++;
               }
               /* Linjen er oppbrukt, les inn ny */
               if (*plb->cp == '\0') {
                  LB_FyllBuffer(fil,plb);
               }
            } while (UT_IsSpace(*plb->cp)  ||  *plb->cp == '\0');
            plb->np = plb->cp;

            LB_GetParameter(plb);
         }

         if (plb->cur_niv == 1) {                           /* Gruppenavn */
            plb->cur_type = navn_nr;

         } else if (navn_nr == L_NA  ||
                    navn_nr == L_NAH ||
                    navn_nr == L_NAD ) {                    /* Koordinat */
            plb->cur_type = LEST_KOORD;

         } else {                                   /* Annen GINFO / PINFO */
            plb->cur_type = LEST_GINFO;
         }

      } else {                       /* Parameter, kommentar eller fyll */
         if (LB_TestFyll(plb->cp)) {    /* ------------------ Fyll */
            /* Marker at linjen er oppbrukt */
            *plb->cp = '\0';

            plb->cur_type = LEST_BLANK;
            plb->np = plb->cp;

            /* Fyll er alltid nivå 2 eller 3 */
            if (plb->cur_niv == 1) {
               plb->cur_niv = 2; 
            }

         } else if (*plb->cp == '!') {     /* ------------------ Kommentar */
            plb->pp = plb->np;
            /* Resten av linjen er kommentar */
            plb->np = strchr(plb->cp,'\0');
            plb->cur_type = LEST_KOM;
            //plb->cur_niv = 2;   /* Kommentar er bare lovlig i ginfo */  // Fjernet 24/7-02.   
            if (plb->cur_niv < 2)  plb->cur_niv = 2;       // Endret 22/8-02. 

         } else {                          /* ------------------ Parameter */
            LB_GetParameter(plb);
            if (plb->cur_navn[plb->cur_niv - 1] == L_NA  ||
                plb->cur_navn[plb->cur_niv - 1] == L_NAH ||
                plb->cur_navn[plb->cur_niv - 1] == L_NAD ) {  /* Koordinat */
               plb->cur_type = LEST_KOORD;

            } else {                                   /* Annen GINFO / PINFO */
               plb->cur_type = LEST_GINFO;
            }
         }
      }
   }

   plb->set_brukt = SET_UBRUKT;

   return plb->cur_type;
}


/*
AR-920909
CH LB_GetParameter                                 Hent parameter fra buffer
CD ==========================================================================
CD Formål:
CD Hent parameter fra lesebuffer.
CD Forutsetter at det ikke er blanke forran parameteren.
CD Inn: "plb->np" peker til første posisjon i parameteren. (Der tolking
CD skal starte.
CD
CD Parametre:
CD Type            Navn   I/U   Forklaring
CD --------------------------------------------------------------------------
CD LB_LESEBUFFER  *plb     i    Peker til bufferstruktur
CD
CD Bruk:
CD param = LB_GetParameter(&lb)
   ==========================================================================
*/
static char *LB_GetParameter(LB_LESEBUFFER *plb)
{
   short npar = (plb->cur_ant_par == LC_ANT_PAR_UKJENT)?  9999 : plb->cur_ant_par;

   plb->pp = plb->cp = plb->ep = plb->np;

   for ( ; npar > 0; npar--) {
      /* Neste sett er funnet */
      if (*plb->cp == '\0'  ||  *plb->cp == '.'  ||  *plb->cp == '!') {
         break;

      /* Vanlig ord */
      } else if (*plb->cp != '"') {
         while (*plb->cp  &&  !UT_IsSpace(*plb->cp)) {
            (plb->cp)++;
         }
         plb->ep = plb->cp;

      /* "Ord" i hermetegn */ 
      } else {
         (plb->cp)++;     /* Start-hermetegn */
         while (*plb->cp  &&  *plb->cp != '"') {          /* "Ordet" */
            (plb->cp)++;
         }
         if (*plb->cp == '"') {
            (plb->cp)++;
         }
         plb->ep = plb->cp;
      }

      if (npar > 1) {      /* Skann fram til neste parameter */
         while (UT_IsSpace(*plb->cp)) {
            (plb->cp)++;
         }
      }
   }

   /* Avslutt strengen */
   if (plb->ep > plb->pp) {     /* Vanlig */
      plb->cp = plb->ep;
      (plb->cp)++;
      plb->np = plb->cp;
      *plb->ep = '\0';
   } else {                /* Tom parameter */
      plb->np = plb->ep;
      plb->pp = plb->ep - 1;
      *plb->pp = '\0';
   }

   return  plb->pp;
}


/*
AR-920626
!-------------------------------------------------------------!
! LB_TestFyll -  Tester om en streng er fyll-linje.           !
!                                                             !
! Retur:  UT_TRUE  = linjen er fyll                           !
!         UT_FALSE = linjen inneholder annen informasjon      !
!                                                             !
!-------------------------------------------------------------!
*/
static short LB_TestFyll(const char *pszTx)
{
   for (; *pszTx; ++pszTx) {
      if (!UT_IsSpace(*pszTx)  &&  *pszTx != '!')  return (UT_FALSE);
   }

   return (UT_TRUE);
}


/*
AR/TU:2008-09-11
CH LC_ErstattReferanse                                     Erstatt referanse 
CD ==========================================================================
CD Formål:
CD Erstatt referanse i alle grupper i gitt fil.
CD 
CD
CD Parametre:
CD Type       Navn          I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil           i   Fil som skal behandles
CD long       lGmlSnr        i   Gruppe som skal byttes ut
CD long       lNyttSnr       i   Ny gruppe
CD                               Verdien 0 fører til gammelt serienummer 
CD                               fjernes uten at det legges inn noe nytt.
CD bool       bSammeRetning  i   Gruppene er digitalisert i samme retning
CD
CD Bruk:
CD sStatus = LC_ErstattReferanse(pFil, lGmlSnr, lNyttSnr, bSammeRetning);
==========================================================================
*/
SK_EntPnt_FYBA void LC_ErstattReferanse (LC_FILADM *pFil,long lGmlSnr,long lNyttSnr, bool bSammeRetning)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_BGR BgrGml,Bgr;
   long lAntRef;
   short sGiLin,sRefPos;
   long *plRefArray,*plRef,l;
   bool bEndret;


   // Husk gruppen
   BgrGml = Sys.GrId;


   lGmlSnr = labs(lGmlSnr);
   lNyttSnr = labs(lNyttSnr);


   LC_InitNextBgr(&Bgr);
   Bgr.pFil = pFil;
   while (LC_NextBgr(&Bgr,LC_FRAMGR))
   {
      if (Bgr.pFil == pFil)
      {
         LC_GetGrParaBgr(&Bgr,&ngi,&nko,&info);
         if ((info&GI_REF) != 0)
         {
            // Gruppen er på rett fil og har referanser, Bytt serienummer 
            LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
            lAntRef = LC_InqAntRef();
            plRefArray = (long *) UT_MALLOC(lAntRef * sizeof(long));
            sGiLin = 2;
            sRefPos = 0;
            LC_GetRef(plRefArray,lAntRef,&sGiLin,&sRefPos);

            bEndret = false;
            plRef = plRefArray;
            for (l=0; l<lAntRef; ++l,++plRef) 
            {
               if (labs(*plRef) == lGmlSnr)
               {
                  // Skal bytte serienummer
                  if (lNyttSnr != 0)
                  {
                     if (*plRef > 0  && bSammeRetning)
                     {
                        *plRef = lNyttSnr;
                     }
                     else if (*plRef > 0  && !bSammeRetning)
                     {
                        *plRef = -lNyttSnr;
                     }
                     else if (*plRef < 0  && bSammeRetning)
                     {
                        *plRef = -lNyttSnr;
                     }
                     else if (*plRef < 0  && !bSammeRetning)
                     {
                        *plRef = lNyttSnr;
                     }
                  }

                  // Skal fjerne serienummer
                  else
                  {
                     memmove(plRef, plRef+1, (lAntRef-l-1) * sizeof(long));

                     --l;
                     --plRef;
                     --lAntRef;
                  }

                  bEndret = true;
               }
            }

            if (bEndret) {
               LC_PutRef(plRefArray,lAntRef);
               LC_WxGr(SKRIV_OPTIMALT);
            }
            UT_FREE(plRefArray);
         }
      }
   }

   // ========= Leser inn opprinnelig gruppe
   LC_RxGr(&BgrGml,LES_OPTIMALT,&ngi,&nko,&info);
}
