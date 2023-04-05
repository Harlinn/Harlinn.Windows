/* === 911001 ============================================================ */
/*  STATENS KARTVERK  -  FYSAK-PC                                          */
/*  Fil: fylr.c                                                            */
/*  Ansvarlig: Andreas Røstad                                              */
/*  Innhold: Rutiner for geografisk søking mm. i fysak-pc                  */
/* ======================================================================= */

#include "fyba.h"
#include "fybax.h"

#include <float.h>
#include <math.h>
#include <limits.h>
#include <memory.h>


/* Globale variabler */
extern LC_SYSTEMADM Sys;

/* --- Lokale rutiner */
static LC_R_LEAF * LR_R_Insert(long lGrNr,LC_BOKS * pB,LC_R_NODE * pFar,LC_R_NODE * pRN,LC_R_NODE * *ppNyRN);
static LC_R_NODE * LR_R_CreateRNode( LC_R_NODE * pFar,short sSonType);
static LC_R_LEAF * LR_R_CreateRLeaf(long lGrNr, LC_BOKS * pB,LC_R_NODE * pFar);
static void LR_R_BoksSum(LC_BOKS * pB1,LC_BOKS * pB2);
static double LR_BoksDeltaArealSum(LC_BOKS * pB1,LC_BOKS * pB2);
static void LR_LeggTilKB(LC_GEO_STATUS * pGeoStat,LC_FILADM *pFil,long lNr);
static short LR_R_BoksTestIntersect(LC_BOKS * pB1,LC_BOKS * pB2);
static void LR_R_SjekkNode(LC_GEO_STATUS * pGeoStat,LC_BOKS * pB,LC_FILADM *pFil,LC_R_NODE * pRN);
static void LR_R_SjekkNodeFlate(LC_GEO_STATUS * pGeoStat,LC_BOKS * pB,LC_FILADM *pFil,LC_R_NODE * pRN);
static void LR_VelgMetode(LC_GEO_STATUS * pGeoStat);

//#ifdef TEST
//#include <string.h>
//static void LR_R_DumpNode(LC_R_NODE * pRN, int iNivo);
static void LR_R_DumpLov(LC_R_LEAF * pRL, LC_FILADM *pDumpFil, int iNivo, double dA, double dN,long *plAntBarn);
static void LR_R_DumpNode(LC_R_NODE * pRN, LC_FILADM *pDumpFil, int iNivo, double dA, double dN, double dLengde,long *plAntBarn);
//#endif




#define MAX_REF 25


/*
AR:2000-07-25
CH LC_GetGrWin                           Hent omskrevet rektangel for gruppe
CD ==========================================================================
CD Formål:
CD Henter omskrevet rektangel for gitt gruppe.
CD For flater er refererte grupper medregnet.
CD
CD Parametre:
CD Type     Navn     I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR *  pBgr      i    Gruppenummer
CD double  *nva       u    Omskrevet rektangel for gruppen. Avrundet utover
CD double  *nvn       u    en enhet.
CD double  *oha       u    
CD double  *ohn       u    
CD short    ist       r    Status. UT_TRUE=OK, UT_FALSE=ulovlig gruppenummer.
CD
CD Bruk:
CD    ist = LC_GetGrWin(&Bgr,&nva,&nvn,&oha,&ohn);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetGrWin(LC_BGR * pBgr,double *nva,double *nvn,double *oha,double *ohn)
{
   LC_R_LEAF * pRL;

   /* LO_TestFilpeker(pBgr->pFil,"LC_GetGrWin"); */
   LO_TestFilpeker(pBgr->pFil,"GetGrWin");

                                           /* Lovlig gruppe */
   if (pBgr->lNr >= 0L  &&  pBgr->lNr < pBgr->pFil->lAntGr) {
      pRL = LI_GetGeo(pBgr->pFil,pBgr->lNr);

      if (pRL != NULL) {
         *nva = pRL->Boks.dMinAust;
         *nvn = pRL->Boks.dMinNord;
         *oha = pRL->Boks.dMaxAust;
         *ohn = pRL->Boks.dMaxNord;

      } else {
         *nva = *nvn = (double)LONG_MAX;
         *oha = *ohn = (double)LONG_MIN;
      }

      return  UT_TRUE;         /* ======> */
   }

   /* Ulovlig gruppe */
   LC_Error(36,"(LC_GetGrWin)","");
   return  UT_FALSE;
}


/*
AR-930608
CH LR_Indx                               Beregn geografiske ruter for gruppe
CD ==========================================================================
CD Formål:
CD Beregner og lagrer omskrevet boks for koordinatene på aktuell gruppe.
CD
CD Parametre: ingen
CD
CD Bruk:
CD LR_Indx();
   ==========================================================================
*/
void LR_Indx(void)
{
   short sfeil;
   long pt;
   double min_n,min_a,max_n,max_a;
   double radius,aust,nord,fi,dfi;
   LC_BOKS Boks;

   // UT_FPRINTF(stderr,"Indeks for: %s\n",LX_GetGi(1));

   /* Bygg ny indeks */
   if (Sys.pGrInfo->nko > 0) {

      /* Nullstill omskreven boks */
      min_a = min_n = (double)LONG_MAX;
      max_a = max_n = (double)LONG_MIN;

                                    /* Handterer "bue" */
      if (Sys.pGrInfo->gnavn == L_BUE  ||  Sys.pGrInfo->gnavn == L_BUEP ||
          Sys.pGrInfo->gnavn == L_SIRKEL  ||  Sys.pGrInfo->gnavn == L_SIRKELP) {

         if (LC_GetBuePar(HENT_FORRFRA,&aust,&nord,&radius,&fi,&dfi,&sfeil)) {
            /* Beregner omskrevet rektangel for "buen" */
            GM_buebox(aust,nord,radius,fi,dfi,&min_a,&min_n,&max_a,&max_n);

         } else {
            if (Sys.pGrInfo->gnavn == L_BUE) {
               /* Ulovlig bue-angivelse */
               //LC_Error(130,"(LR_Indx)",LX_GetGi(1));
               UT_FPRINTF(stderr,"Ulovlig forhold mellom koordinater og radius i: %s : %s\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
            }

            // Spesialhandtering av ulogiske sirkler og buer. Håndteres som KURVE
            for (pt=0; pt<Sys.pGrInfo->nko; pt++) {
               min_a = min(min_a,*(Sys.pdAust + pt));
               min_n = min(min_n,*(Sys.pdNord + pt));
               max_a = max(max_a,*(Sys.pdAust + pt));
               max_n = max(max_n,*(Sys.pdNord + pt));
            }
         }

                                    /* Andre grupper enn "bue" */
      } else {
         /* Omskreven firkant */
         for (pt=0; pt<Sys.pGrInfo->nko; pt++) {
            min_a = min(min_a,*(Sys.pdAust + pt));
            min_n = min(min_n,*(Sys.pdNord + pt));
            max_a = max(max_a,*(Sys.pdAust + pt));
            max_n = max(max_n,*(Sys.pdNord + pt));
         }
      }

      /* Beregn omskreven boks */
      /* Nedre venstre justeres ut en enhet */
      Boks.dMinAust = min_a - Sys.pGrInfo->dEnhet;
      Boks.dMinNord = min_n - Sys.pGrInfo->dEnhet;
         /* Øvre høyre justeres ut en enhet */
      Boks.dMaxAust = max_a + Sys.pGrInfo->dEnhet;
      Boks.dMaxNord = max_n + Sys.pGrInfo->dEnhet;

      // Finnes ikke i treet fra før
      if (Sys.pGrInfo->pRL == NULL ) { 
         /* Lagre omskrevet boks i søketreet */
         Sys.pGrInfo->pRL = LR_InsertGeo(Sys.GrId.pFil,Sys.GrId.lNr,&Boks);

      // Sjekk om boksen avviker fra gammel boks
      } else if (memcmp(&(Sys.pGrInfo->pRL->Boks),&Boks,sizeof(LC_BOKS)) != 0) { 
      
         /* Fjern eventuell gammel forekomst i R-treet */
         LR_R_Delete(Sys.pGrInfo->pRL);

         /* Lagre omskreven firkant i søketreet */
         Sys.pGrInfo->pRL = LR_InsertGeo(Sys.GrId.pFil,Sys.GrId.lNr,&Boks);
      }

   } else if (Sys.pGrInfo->pRL != NULL) {
      /* Fjern eventuell gammel forekomst i R-treet */
      LR_R_Delete(Sys.pGrInfo->pRL);
      Sys.pGrInfo->pRL = NULL;
   }
}


// ==========================================================================
SK_EntPnt_FYBA void LC_DumpGeoRtre(LC_FILADM *pFil)
{
   short ostat;
   LC_FILADM *pDumpFil;
   long lAntBarn = 0;

   // Åpner ny SOSI-fil for dump
   HO_New("Indeksdump.sos", 99, 0.0, 0.0, 0.001, 0.001, 0.001,
          -151000, -151000, 151000, 1000);
   if (LC_OpenSos("Indeksdump.sos",LC_BASE_FRAMGR,LC_NY_IDX,LC_INGEN_STATUS,&pDumpFil,&ostat))
   {
      short sUtvidModus = LC_GetUtvidModus();
      long lMaxSkriv = LC_InqMaxSkriv();
      LC_SetUtvidModus(LC_UTVID_RASK); 
      LC_MaxSkriv(100000000L);

      if (pFil->pGeoRN != NULL)
      {
         LR_R_DumpNode(pFil->pGeoRN,pDumpFil,0, 0.0, 0.0, 100000.0,&lAntBarn);
      }   

      LC_MaxSkriv(lMaxSkriv);
      LC_Save();
      LC_SetUtvidModus(sUtvidModus);  

      LC_CloseSos(pDumpFil,SAVE_IDX);
   }
}


// ==========================================================================
static void LR_R_DumpNode(LC_R_NODE * pRN, LC_FILADM *pDumpFil, int iNivo, double dA, double dN, double dLengde,long *plAntBarn)
{
   LC_BGR Bgr;
   char szTx[100];
   int i;
   long lSnr;
   double dDeltaN;
   long lBarn = 0;

   iNivo++;
   /* Rekursiv sjekk av de underliggende løv eller nodene */
   for (i=0; i<pRN->sSonAnt; i++) { 
      LC_NyGr(pDumpFil,".LINJE",&Bgr,&lSnr);
      LC_PutGi(LC_AppGiL(), "..LTEMA 1000");
      LC_PutTK(LC_AppKoL(), dA, dN);
      dDeltaN = dLengde;

      if (i == 0) {
         LC_PutTK(LC_AppKoL(), dA-dLengde, dN-dDeltaN);
         LC_WxGr(SKRIV_OPTIMALT);

         if (pRN->sSonType == LC_LEAF) {
            LR_R_DumpLov(pRN->Son.pLeaf[i], pDumpFil, iNivo, dA-dLengde, dN-dDeltaN, &lBarn);
         } else {
            LR_R_DumpNode(pRN->Son.pNode[i], pDumpFil, iNivo, dA-dLengde, dN-dDeltaN, dLengde / 3.1, &lBarn);
         }

      } else if (i == 1) {
         LC_PutTK(LC_AppKoL(), dA, dN-dDeltaN);
         LC_WxGr(SKRIV_OPTIMALT);

         if (pRN->sSonType == LC_LEAF) {
            LR_R_DumpLov(pRN->Son.pLeaf[i], pDumpFil, iNivo, dA, dN-dDeltaN, &lBarn);
         } else {
            LR_R_DumpNode(pRN->Son.pNode[i], pDumpFil, iNivo, dA, dN-dDeltaN, dLengde / 3.1, &lBarn);
         }

      } else {
         LC_PutTK(LC_AppKoL(), dA+dLengde, dN-dDeltaN);
         LC_WxGr(SKRIV_OPTIMALT);

         if (pRN->sSonType == LC_LEAF) {
            LR_R_DumpLov(pRN->Son.pLeaf[i], pDumpFil, iNivo, dA+dLengde, dN-dDeltaN, &lBarn);
         } else {
            LR_R_DumpNode(pRN->Son.pNode[i], pDumpFil, iNivo, dA+dLengde, dN-dDeltaN, dLengde / 3.1, &lBarn);
         }
      }
   }

   // Skriv ut noden 
   LC_NyGr(pDumpFil,".PUNKT",&Bgr,&lSnr);
   LC_PutGi(LC_AppGiL(), "..PTEMA 3000");
   LC_PutGi(LC_AppGiL(), "..NODE 1");
   
   UT_SNPRINTF(szTx,100,"..NIVÅ %d", iNivo-1);
   LC_PutGi(LC_AppGiL(), szTx);
   
   UT_SNPRINTF(szTx,100,"..MIN-NØ %f %f", pRN->Boks.dMinNord, pRN->Boks.dMinAust);
   LC_PutGi(LC_AppGiL(), szTx);

   UT_SNPRINTF(szTx,100,"..MAX-NØ %f %lf", pRN->Boks.dMaxNord, pRN->Boks.dMaxAust);
   LC_PutGi(LC_AppGiL(), szTx);

   UT_SNPRINTF(szTx,100,"..DELTA-NØ %f %f",
            pRN->Boks.dMaxNord - pRN->Boks.dMinNord,
            pRN->Boks.dMaxAust - pRN->Boks.dMinAust);
   LC_PutGi(LC_AppGiL(), szTx);

   UT_SNPRINTF(szTx,100,"..BARN %ld",lBarn);
   LC_PutGi(LC_AppGiL(), szTx);

   LC_PutTK(LC_AppKoL(), dA, dN);
   LC_WxGr(SKRIV_OPTIMALT);

   (*plAntBarn) += lBarn;

}


// ==========================================================================
static void LR_R_DumpLov(LC_R_LEAF * pRL, LC_FILADM *pDumpFil, int iNivo, double dA, double dN, long *plAntBarn)
{
   LC_BGR Bgr;
   char szTx[100];
   long lSnr;


   (*plAntBarn)++;
   // Skriv ut løvet
   LC_NyGr(pDumpFil,".PUNKT",&Bgr,&lSnr);
   LC_PutGi(LC_AppGiL(), "..PTEMA 5000");
   LC_PutGi(LC_AppGiL(), "..LØV 1");

   UT_SNPRINTF(szTx,100,"..NR %ld", pRL->lNr);
   LC_PutGi(LC_AppGiL(), szTx);
   
   UT_SNPRINTF(szTx,100,"..NIVÅ %d", iNivo);
   LC_PutGi(LC_AppGiL(), szTx);
   
   UT_SNPRINTF(szTx,100,"..MIN-NØ %f %f", pRL->Boks.dMinNord, pRL->Boks.dMinAust);
   LC_PutGi(LC_AppGiL(), szTx);

   UT_SNPRINTF(szTx,100,"..MAX-NØ %f %f", pRL->Boks.dMaxNord, pRL->Boks.dMaxAust);
   LC_PutGi(LC_AppGiL(), szTx);

   UT_SNPRINTF(szTx,100,"..DELTA-NØ %f %f",
            pRL->Boks.dMaxNord - pRL->Boks.dMinNord,
            pRL->Boks.dMaxAust - pRL->Boks.dMinAust);
   LC_PutGi(LC_AppGiL(), szTx);

   LC_PutTK(LC_AppKoL(), dA, dN);
   LC_WxGr(SKRIV_OPTIMALT);
}


/*
AR-900214
CH LR_IndxFlate                            Beregn geografisk indeks for flate
CD =============================================================================
CD Formål:
CD Utvider omskrevet boks for aktuell gruppe, slik at den tar hensyn til
CD referanser.
CD
CD Parametre: ingen
CD
CD Bruk:
CD LR_IndxFlate();
   =============================================================================
*/
void LR_IndxFlate(void)
{
   long ref_arr[MAX_REF];
   unsigned char ref_status[MAX_REF];
   long ant_ref;
   short s,ngi;
   long nko;
   unsigned short info;
   double min_n,min_a,max_n,max_a;
   LC_R_LEAF * pRL;
   LC_FILADM *pFi = Sys.GrId.pFil;
   LC_GRF_STATUS GrfStat;
   LC_BOKS Boks;
   short sRefBrukt = UT_FALSE;


   LC_GetGrPara(&ngi,&nko,&info);

   /* Sjekk om gruppen har referanser */
   if ((info & GI_REF) != 0  ||  nko >0) {

      /* Nullstill omskreven boks */
      min_a = min_n = (double)LONG_MAX;
      max_a = max_n = (double)LONG_MIN;

      /* Koordinater direkte på denne gruppen */
      if (nko > 0) {
         pRL = LI_GetGeo(pFi,Sys.GrId.lNr);
         if (pRL != NULL) {
            min_a = pRL->Boks.dMinAust;
            min_n = pRL->Boks.dMinNord;
            max_a = pRL->Boks.dMaxAust;
            max_n = pRL->Boks.dMaxNord;

         } else {
            /* Initier med inverse område fra filhodet */
            min_a = Sys.GrId.pFil->Omraade.dMaxAust;
            min_n = Sys.GrId.pFil->Omraade.dMaxNord;
            max_a = Sys.GrId.pFil->Omraade.dMinAust;
            max_n = Sys.GrId.pFil->Omraade.dMinNord;
         }

      } else {
         /* Initier med inverse område fra filhodet */
         min_a = Sys.GrId.pFil->Omraade.dMaxAust;
         min_n = Sys.GrId.pFil->Omraade.dMaxNord;
         max_a = Sys.GrId.pFil->Omraade.dMinAust;
         max_n = Sys.GrId.pFil->Omraade.dMinNord;
      }

      LC_InitGetRefFlate(&GrfStat);
      /*
       * Bygger opp omskreven firkant for gruppen ut fra omskreven
       * firkant for gruppene som inngår.
       * (Behandle bare ytre avgrensing.)
       */
      ant_ref = LC_GetRefFlate(&GrfStat,GRF_YTRE,ref_arr,ref_status,MAX_REF);
      do {
         for (s=0; s<ant_ref; s++) {
            pRL = LI_GetGeo(pFi,ref_arr[s]);
            if (pRL != NULL) {
               min_a = min(min_a, pRL->Boks.dMinAust);
               min_n = min(min_n, pRL->Boks.dMinNord);
               max_a = max(max_a, pRL->Boks.dMaxAust);
               max_n = max(max_n, pRL->Boks.dMaxNord);
            }
         }

         if (ant_ref > 0)  sRefBrukt = UT_TRUE;

         if (ant_ref < MAX_REF)  break;

         ant_ref = LC_GetRefFlate(&GrfStat,GRF_YTRE,ref_arr,ref_status,MAX_REF);
      } while (ant_ref > 0);

      /* Lagre omskreven firkant i søketreet */
      Boks.dMinAust = min_a;
      Boks.dMinNord = min_n;
      Boks.dMaxAust = max_a;
      Boks.dMaxNord = max_n;

      /* Fjern eventuell representasjonspunktet fra R-treet */
      if (Sys.pGrInfo->pRL != NULL) LR_R_Delete(Sys.pGrInfo->pRL);

      /* Legger inn hele flaten */
      Sys.pGrInfo->pRL = LR_InsertGeo(Sys.GrId.pFil,Sys.GrId.lNr,&Boks);
   }

   /* Husk om referanser er brukt */
   if (sRefBrukt == UT_TRUE) {
      LI_SetBt(pFi,Sys.GrId.lNr,BT_REFBOX);
   } else {
      LI_ClrBt(pFi,Sys.GrId.lNr,BT_REFBOX);
   }
}
   
/*
AR-911003
CH LC_SBGeo                             Sett søkegrense for grov geografisk søk
CD =============================================================================
CD Formål:
CD Definerer geografisk område for geografisk søk.
CD
CD Parametre:
CD Type           Navn      I/U  Forklaring
CD -----------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus.
CD unsigned short usLag      i   Velg hvilke "lag" det skal søkes i.
CD                               LC_FRAMGR og /eller LC_BAKGR
CD double         nv_a       i   Koordinat nedre venstre hjørne.
CD double         nv_n       i
CD double         oh_a       i   Koordinat øvre høyre hjørne.
CD double         oh_n       i
CD
CD Bruk:
CD LC_GEO_STATUS GeoStat;
CD .
CD LC_SBGeo(&GeoStat,LC_FRAMGR | LC_BAKGR,nv_a,nv_n,oh_a,oh_n);
CD if (LC_FFGeo(&GeoStat,&Bgr)) {
CD     do{
CD         . Behandle funnet gruppe
CD         .
CD     } while (LC_FNGeo(&GeoStat,&bgr));
CD }
CD LC_AvsluttSok(&GeoStat);
CD .
   =============================================================================
*/
SK_EntPnt_FYBA void LC_SBGeo(LC_GEO_STATUS * pGeoStat,unsigned short usLag,
              double nv_a,double nv_n,double oh_a,double oh_n)
{
   /* Normaliserer vinduet */
   GM_NormVindu(&nv_a,&nv_n,&oh_a,&oh_n);

   /* Avrunder ut til nærmeste meter utover */
   /* Nedre venstre ut til nærneste heltall under */
   //pGeoStat->nvn = (long)floor(nv_n);
   //pGeoStat->nva = (long)floor(nv_a);
   /* Øvre høyre ut til nærneste heltall over */
   //pGeoStat->ohn = (long)ceil(oh_n);
   //pGeoStat->oha = (long)ceil(oh_a);

   pGeoStat->nvn = nv_n;
   pGeoStat->nva = nv_a;
   pGeoStat->ohn = oh_n;
   pGeoStat->oha = oh_a;

   /* Husk lag */
   pGeoStat->usLag = usLag;

   /* Nullstiller resultatpekerne */
   pGeoStat->pForsteKB = NULL;
   pGeoStat->pSisteKB = NULL;
   pGeoStat->pAktuellKB = NULL;

   /* Velg søkemetode */
   LR_VelgMetode(pGeoStat);
}


/*
AR-911003
CH LC_FFGeo                                   Finn første ved geografisk søk
CD ==========================================================================
CD Formål:
CD Finner første gruppe i det definerte området for kombinert geografisk søk.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus
CD LC_BGR *        pBgr       u   Funnet gruppe
CD short          sstat      r   Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD Se under LC_SBGeo.
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_FFGeo(LC_GEO_STATUS * pGeoStat,LC_BGR * pBgr)
{
   /* Bruker R-tre */
   if (pGeoStat->usMetode == LC_GEO_RTRE) {
      LC_BOKS Boks;
      LC_FILADM *pFil;

      /* Beregn søkeboksen */
      Boks.dMinAust = pGeoStat->nva;
      Boks.dMinNord = pGeoStat->nvn;
      Boks.dMaxAust = pGeoStat->oha;
      Boks.dMaxNord = pGeoStat->ohn;

      /* Frigir eventuell gammel resultatkjede */
      LC_AvsluttSok(pGeoStat);

      /* Sjekker alle filer */
      LC_InitNextFil(&pFil);
	   while (LC_NextFil(&pFil,pGeoStat->usLag)) {
         /* Filen inneholder data, må sjekke alle berørte noder */
         if (pFil->pGeoRN != NULL) {
            LR_R_SjekkNode(pGeoStat,&Boks,pFil,pFil->pGeoRN);
         }   
      }

      pGeoStat->pAktuellKB = pGeoStat->pForsteKB;
      if (pGeoStat->pAktuellKB != NULL) {
         /* Tilslag */
         *pBgr = pGeoStat->pAktuellKB->Bgr;
         return UT_TRUE;
      }

   /* Sekvensiell gjennomgang av alle grupper */
   } else {
      LC_BGR Bgr;
      LC_R_LEAF * pRL;

      LC_InitNextBgr(&Bgr);
      while (LC_NextBgr(&Bgr,pGeoStat->usLag)) {
         pRL = LI_GetGeo(Bgr.pFil,Bgr.lNr);
         if (pRL != NULL) {
            /* Sjekk område-tabellen */
            if (pGeoStat->ohn >= pRL->Boks.dMinNord && pGeoStat->oha >= pRL->Boks.dMinAust &&
                pGeoStat->nvn <= pRL->Boks.dMaxNord && pGeoStat->nva <= pRL->Boks.dMaxAust) {
               *pBgr = pGeoStat->Bgr = Bgr;            /* Tilslag */
               return UT_TRUE;
            }
         }
      }

      /* Ikke tilslag */
      pGeoStat->Bgr = Bgr;
   }
   
   /* Ikke tilslag */
   return UT_FALSE;
}


/*
AR-911003
CH LR_R_SjekkNode                          Sjekker node om overlappende boks
CD ==========================================================================
CD Formål:
CD Sjekker en node og underliggende noder om de har lagret bokser
CD som overlapper søkerektanglet. De gruppene som blir funnet blir hengt på
CD kjeden med søkeresultat i pGeoStat.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat   i   Peker til struktur for søkestatus
CD LC_BOKS *       pB         i   Søkeboks
CD LC_FILADM *    pFil       i   Filpeker
CD LC_R_NODE *     pRN        i   Peker til node som skal sjekkes
CD
CD Bruk:
CD LR_R_SjekkNode(pGeoStat,pB,pFil,pRN->pSon[i]);
   ==========================================================================
*/
static void LR_R_SjekkNode(LC_GEO_STATUS * pGeoStat,LC_BOKS * pB,LC_FILADM *pFil,LC_R_NODE * pRN)
{
   int i;


   /* Sjekk om denne noden berører søkeboksen */
   if (LR_R_BoksTestIntersect(&(pRN->Boks),pB)) {

      /* Har kommet til ytterste nivå */
      if (pRN->sSonType == LC_LEAF) {

         /* Sjekk de gruppene som er lagret under denne noden */
         for (i=0; i<pRN->sSonAnt; i++) { 
            if (LR_R_BoksTestIntersect(&(pRN->Son.pLeaf[i]->Boks),pB)) {
               LR_LeggTilKB(pGeoStat,pFil,pRN->Son.pLeaf[i]->lNr);
            }
         }

      /* Node */
      } else {

         /* Rekursiv sjekk av de underliggende nodene */
         for (i=0; i<pRN->sSonAnt; i++) { 
            LR_R_SjekkNode(pGeoStat,pB,pFil,pRN->Son.pNode[i]);
         }
      }
   }
}


/*
AR-911003
CH LR_R_BoksTestIntersect             Sjekker om to bokser "berører" hverandre
CD ==========================================================================
CD Formål:
CD Sjekker om to bokser "berører" hverandre.
CD
CD Parametre:
CD Type     Navn     I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_BOKS *  pB1      i   Rektangel 1
CD LC_BOKS *  pB2      i   Rektangel 2
CD short     sStatus  r   UT_TRUE=Berører,  UT_FALSE=Ikke berøring 
CD
CD Bruk:
CD LR_R_BoksTestIntersect(...);
   ==========================================================================
*/
static short LR_R_BoksTestIntersect(LC_BOKS * pB1,LC_BOKS * pB2)
{
   if (pB1->dMaxNord  >=  pB2->dMinNord  &&
       pB1->dMaxAust  >=  pB2->dMinAust  &&
       pB1->dMinNord  <=  pB2->dMaxNord  &&
       pB1->dMinAust  <=  pB2->dMaxAust ) {

      /* Tilslag */
      return UT_TRUE;
   }

   return UT_FALSE;
}


/*
AR-911003
CH LC_FNGeo                                    Finn neste ved geografisk søk
CD ==========================================================================
CD Formål:
CD Finner neste gruppe i det definerte området for geografisk søk.
CD
CD Parametre:
CD Type           Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus
CD LC_BGR *        pBgr       u   Funnet gruppe
CD short          sstat      r   Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD Se under LC_SBGeo.
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_FNGeo(LC_GEO_STATUS * pGeoStat,LC_BGR * pBgr)
{
   /* Bruker R-tre */
   if (pGeoStat->usMetode == LC_GEO_RTRE) {
      /* Søket er utført og ligger som en kjede */
      if (pGeoStat->pAktuellKB != NULL) {
         pGeoStat->pAktuellKB = pGeoStat->pAktuellKB->pNesteKB;
         if (pGeoStat->pAktuellKB != NULL) {
            /* Tilslag */
            *pBgr = pGeoStat->pAktuellKB->Bgr;
            return UT_TRUE;
         }
      }

   /* Sekvensiell gjennomgang av alle grupper */
   } else {
      LC_R_LEAF * pRL;
      LC_BGR Bgr = pGeoStat->Bgr;
   
      while (LC_NextBgr(&Bgr,pGeoStat->usLag)) {
         pRL = LI_GetGeo(Bgr.pFil,Bgr.lNr);
         if (pRL != NULL) {
            /* Sjekk område-tabellen */
            if (pGeoStat->ohn >= pRL->Boks.dMinNord && pGeoStat->oha >= pRL->Boks.dMinAust &&
                pGeoStat->nvn <= pRL->Boks.dMaxNord && pGeoStat->nva <= pRL->Boks.dMaxAust) {
               *pBgr = pGeoStat->Bgr = Bgr;            /* Tilslag */
               return UT_TRUE;
            }
         }
      }

      /* Ikke tilslag */
      pGeoStat->Bgr = Bgr;
   }
   
   /* Ikke tilslag */
   return UT_FALSE;
}


/*
AR-911003
CH LC_FFGeoFil                       Finn første ved geografisk søk i en fil
CD ==========================================================================
CD Formål:
CD Finner første gruppe i det definerte området for kombinert geografisk søk.
CD Søker bare i en gitt fil.
CD
CD Parametre:
CD Type           Navn       I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat   iu   Peker til struktur for søkestatus
CD LC_FILADM *    pOnsketFil  i   Filpeker til den filen det skal søkes i.
CD LC_BGR *        pBgr        u   Funnet gruppe
CD short          sstat       r   Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD Se under LC_SBGeo.
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_FFGeoFil(LC_GEO_STATUS * pGeoStat,LC_FILADM *pOnsketFil,LC_BGR * pBgr)
{
   /* Bruker R-tre */
   if (pGeoStat->usMetode == LC_GEO_RTRE) {
      LC_BOKS Boks;

      /* Beregn søkeboksen */
      Boks.dMinAust = pGeoStat->nva;
      Boks.dMinNord = pGeoStat->nvn;
      Boks.dMaxAust = pGeoStat->oha;
      Boks.dMaxNord = pGeoStat->ohn;
   
      /* Frigir eventuell gammel resultatkjede */
      LC_AvsluttSok(pGeoStat);

      /* Sjekker den aktuelle filen */
	   if (pOnsketFil->usLag & pGeoStat->usLag) {
         /* File inneholder data, må sjekke alle berørte noder */
         if (pOnsketFil->pGeoRN != NULL) {
            LR_R_SjekkNode(pGeoStat,&Boks,pOnsketFil,pOnsketFil->pGeoRN);
         }   
      }

      pGeoStat->pAktuellKB = pGeoStat->pForsteKB;
      if (pGeoStat->pAktuellKB != NULL) {
         /* Tilslag */
         *pBgr = pGeoStat->pAktuellKB->Bgr;
         return UT_TRUE;
      }

   /* Sekvensiell gjennomgang av alle grupper */
   } else {
      LC_BGR Bgr;
      LC_R_LEAF * pRL;
   
      LC_InitNextBgr(&Bgr);
      while (LC_NextBgr(&Bgr,pGeoStat->usLag)) {
         /* Rett fil? */ 
         if (Bgr.pFil == pOnsketFil) {
            pRL = LI_GetGeo(Bgr.pFil,Bgr.lNr);
            if (pRL != NULL) {
               /* Sjekk område-tabellen */
               if (pGeoStat->ohn >= pRL->Boks.dMinNord && pGeoStat->oha >= pRL->Boks.dMinAust &&
                   pGeoStat->nvn <= pRL->Boks.dMaxNord && pGeoStat->nva <= pRL->Boks.dMaxAust) {
                  *pBgr = pGeoStat->Bgr = Bgr;            /* Tilslag */
                  return UT_TRUE;
               }
            }
         }
      }

      /* Ikke tilslag */
      pGeoStat->Bgr = Bgr;
   }

   /* Ikke tilslag */
   return UT_FALSE;
}


/*
AR-911003
CH LC_FNGeoFil                        Finn neste ved geografisk søk i en fil
CD ==========================================================================
CD Formål:
CD Finner neste gruppe i det definerte området for geografisk søk.
CD Søker bare i en gitt fil.
CD
CD Parametre:
CD Type           Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus
CD LC_FILADM *    pFil      i    Filpeker til den filen det skal søkes i.
CD LC_BGR *        pBgr       u   Funnet gruppe
CD short          sstat      r   Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD Se under LC_SBGeo.
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_FNGeoFil(LC_GEO_STATUS * pGeoStat,LC_FILADM *pFil,LC_BGR * pBgr)
{
   /* Bruker R-tre */
   if (pGeoStat->usMetode == LC_GEO_RTRE) {
      if (pGeoStat->pAktuellKB != NULL) {
         pGeoStat->pAktuellKB = pGeoStat->pAktuellKB->pNesteKB;
         if (pGeoStat->pAktuellKB != NULL) {
            /* Tilslag */
            *pBgr = pGeoStat->pAktuellKB->Bgr;
            return UT_TRUE;
         }
      }

   /* Sekvensiell gjennomgang av alle grupper */
   } else {
      LC_R_LEAF * pRL;
      LC_BGR Bgr = pGeoStat->Bgr;
   
      while (LC_NextBgr(&Bgr,pGeoStat->usLag)) {

         if (Bgr.pFil == pFil) {
            pRL = LI_GetGeo(Bgr.pFil,Bgr.lNr);
            if (pRL != NULL) {
               /* Sjekk område-tabellen */
               if (pGeoStat->ohn >= pRL->Boks.dMinNord && pGeoStat->oha >= pRL->Boks.dMinAust &&
                   pGeoStat->nvn <= pRL->Boks.dMaxNord && pGeoStat->nva <= pRL->Boks.dMaxAust) {
                  *pBgr = pGeoStat->Bgr = Bgr;            /* Tilslag */
                  return UT_TRUE;
               }
            }
         }
      }

      /* Ikke tilslag */
      pGeoStat->Bgr = Bgr;
   }
   
   /* Ikke tilslag */
   return UT_FALSE;
}


/*
AR-911002
CH LC_FAGeo                                     Finn alle ved geografisk søk
CD ==========================================================================
CD Formål:
CD Finn alle i geografisk søkeområde.
CD Tilslag merkes i brukttabellen kolonne BT_GEOSOK (15).
CD
CD Parametre:
CD Type           Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus
CD long           lAntall    r   Antall funnet.
CD
CD Bruk:
CD .
CD LC_SBGeo(&GeoStat,LC_FRAMGR | LC_BAKGR,nv_a,nv_n,oh_a,oh_n);
CD antall = LC_FAGeo(&Bgr);
CD .
   =============================================================================
*/
SK_EntPnt_FYBA long LC_FAGeo(LC_GEO_STATUS * pGeoStat)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_BGR AktBgr,Bgr;
   long lAntall = 0;


   /* Husk aktuell gruppe */
   AktBgr = Sys.GrId;

   /* Blanker brukttabellen */
   LI_EraseBt(BT_GEOSOK,BT_GEOSOK);
   
   /* Utfører søket */
   if (LC_FFGeo(pGeoStat,&Bgr)) {
      do {
         LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
         lAntall += LC_MerkGr(BT_GEOSOK,1);     /* Tilslag */
      } while (LC_FNGeo(pGeoStat,&Bgr));
   }
   LC_AvsluttSok(pGeoStat);

   /* Les tilbake aktuell gruppe */
   if (AktBgr.lNr != INGEN_GRUPPE) {
      LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);
   }

   return lAntall;
}


/*
AR-911003
CH LC_SBFlate                     Sett søkegrense for geografisk søk på flate
CD =============================================================================
CD Formål:
CD Definerer punkt for geografisk søk på flate.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD -----------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus
CD unsigned short usLag      i   Velg hvilke "lag" det skal søkes i.
CD                               LC_FRAMGR og /eller LC_BAKGR
CD double         nv_a       i   Koordinat nedre venstre hjørne
CD double         nv_n       i
CD double         oh_a       i   Koordinat øvre høyre hjørne
CD double         oh_n       i
CD
CD Bruk:
CD LC_GEO_STATUS GeoStat;
CD .
CD LC_SBFlate(&GeoStat,LC_FRAMGR | LC_BAKGR,nv_a,nv_n,oh_a,oh_n);
CD if (LC_FFFlate(&GeoStat,&Bgr)) {
CD     do{
CD         . Behandle funnet gruppe
CD         .
CD     } while (LC_FNFlate(&GeoStat,&Bgr));
CD }
CD LC_AvsluttSok(&GeoStat);
CD .
   =============================================================================
*/
SK_EntPnt_FYBA void LC_SBFlate(LC_GEO_STATUS * pGeoStat,unsigned short usLag,
              double nv_a,double nv_n,double oh_a,double oh_n)
{
                     /* Normaliserer vinduet */
   GM_NormVindu(&nv_a,&nv_n,&oh_a,&oh_n);

                          /* Avrunder ut til nærmeste meter utover */
                          /* Nedre venstre ut til nærneste heltall under */
   pGeoStat->nvn = (long)floor(nv_n);
   pGeoStat->nva = (long)floor(nv_a);
                           /* Øvre høyre ut til nærneste heltall over */
   pGeoStat->ohn = (long)ceil(oh_n);
   pGeoStat->oha = (long)ceil(oh_a);

                           /* Husk lag */
   pGeoStat->usLag = usLag;

   /* Nullstiller resultatpekerne */
   pGeoStat->pForsteKB = NULL;
   pGeoStat->pSisteKB = NULL;
   pGeoStat->pAktuellKB = NULL;

   /* Velg søkemetode */
   LR_VelgMetode(pGeoStat);
}


/*
AR-911003
CH LC_FFFlate                                        Finn første ved flatesøk
CD =============================================================================
CD Formål:
CD Finner første gruppe i det definerte området for flatesøk.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD -----------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus
CD LC_BGR *        pBgr       u   Funnet gruppe
CD short          sstat      r   Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD Se under LC_SBFlate.
   =============================================================================
*/
SK_EntPnt_FYBA short LC_FFFlate(LC_GEO_STATUS * pGeoStat,LC_BGR * pBgr)
{
   /* Bruker R-tre */
   if (pGeoStat->usMetode == LC_GEO_RTRE) {
      LC_BOKS Boks;
      LC_FILADM *pFil;

      /* Beregn søkeboksen */
      Boks.dMinAust = pGeoStat->nva;
      Boks.dMinNord = pGeoStat->nvn;
      Boks.dMaxAust = pGeoStat->oha;
      Boks.dMaxNord = pGeoStat->ohn;
  
      /* Frigir eventuell gammel resultatkjede */
      LC_AvsluttSok(pGeoStat);

      /* Sjekker alle filer */
      LC_InitNextFil(&pFil);
	   while (LC_NextFil(&pFil,pGeoStat->usLag)) {

         /* File inneholder data, må sjekke alle berørte kvadranter */
         if (pFil->pGeoRN != NULL) {
            LR_R_SjekkNodeFlate(pGeoStat,&Boks,pFil,pFil->pGeoRN);
         }   
      }

      pGeoStat->pAktuellKB = pGeoStat->pForsteKB;

      if (pGeoStat->pAktuellKB != NULL) {
         /* Tilslag */
         *pBgr = pGeoStat->pAktuellKB->Bgr;
         return UT_TRUE;
      }

   /* Sekvensiell gjennomgang av alle grupper */
   } else {
      LC_BGR Bgr;
      LC_R_LEAF * pRL;

      LC_InitNextBgr(&Bgr);

      while (LC_NextBgr(&Bgr,pGeoStat->usLag)) {
         if (LI_InqBt(Bgr.pFil,Bgr.lNr,BT_REFBOX)) {
            pRL = LI_GetGeo(Bgr.pFil,Bgr.lNr);
            if (pRL != NULL) {
               /* Sjekk område-tabellen */
               if (pGeoStat->ohn >= pRL->Boks.dMinNord && pGeoStat->oha >= pRL->Boks.dMinAust &&
                   pGeoStat->nvn <= pRL->Boks.dMaxNord && pGeoStat->nva <= pRL->Boks.dMaxAust) {
                  *pBgr = pGeoStat->Bgr = Bgr;            /* Tilslag */
                  return UT_TRUE;
               }
            }
         }
      }

      /* Ikke tilslag */
      pGeoStat->Bgr = Bgr;
   }
   
   /* Ikke tilslag */
   return UT_FALSE;
}


/*
AR-980205
CH LR_R_SjekkNodeFlate            Sjekker node om overlappende boks (flate)
CD ==========================================================================
CD Formål:
CD Sjekker en node og underliggende noder om de har lagret bokser
CD som overlapper søkerektanglet. De gruppene som blir funnet blir hengt på
CD kjeden med søkeresultat i pGeoStat. Finner bare grupper der det er brukt
CD referanser for oppbygging av geografisk boks.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat   i   Peker til struktur for søkestatus
CD LC_BOKS *       pB         i   Søkeboks
CD LC_FILADM *    pFil       i   Filpeker
CD LC_R_NODE *     pRN        i   Peker til node som skal sjekkes
CD
CD Bruk:
CD LR_R_SjekkNodeFlate(pGeoStat,pB,pFil,pRN->pSon[i]);
   ==========================================================================
*/
static void LR_R_SjekkNodeFlate(LC_GEO_STATUS * pGeoStat,LC_BOKS * pB,LC_FILADM *pFil,LC_R_NODE * pRN)
{
   int i;


   /* Sjekk om denne noden berører søkeboksen */
   if (LR_R_BoksTestIntersect(&(pRN->Boks),pB)) {

      /* Har kommet til ytterste nivå */
      if (pRN->sSonType == LC_LEAF) {

         /* Sjekk de gruppene som er lagret under denne noden */
         for (i=0; i<pRN->sSonAnt; i++) { 
            if (LR_R_BoksTestIntersect(&(pRN->Son.pLeaf[i]->Boks),pB)) {
               /* Huskes bare hvis det er brukt referanser */
               if (LI_InqBt(pFil,pRN->Son.pLeaf[i]->lNr,BT_REFBOX)) {
                  LR_LeggTilKB(pGeoStat,pFil,pRN->Son.pLeaf[i]->lNr);
               }
            }
         }

      /* Node */
      } else {

         /* Rekursiv sjekk av de underliggende nodene */
         for (i=0; i<pRN->sSonAnt; i++) { 
            LR_R_SjekkNodeFlate(pGeoStat,pB,pFil,pRN->Son.pNode[i]);
         }
      }
   }
}


/*
AR-911002
CH LC_FNFlate                                        Finn neste ved flatesøk
CD ==========================================================================
CD Formål:
CD Finner neste gruppe i det definerte området for flatesøk.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus
CD LC_BGR *        pBgr       u   Funnet gruppe
CD short          sstat      r   Søkestatus (UT_TRUE=Funnet, UT_FALSE=Ingen funnet)
CD
CD Bruk:
CD Se under LC_SBFlate.
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_FNFlate(LC_GEO_STATUS * pGeoStat,LC_BGR * pBgr)
{
   /* Bruker R-tre */
   if (pGeoStat->usMetode == LC_GEO_RTRE) {
      if (pGeoStat->pAktuellKB != NULL) {
         pGeoStat->pAktuellKB = pGeoStat->pAktuellKB->pNesteKB;
         if (pGeoStat->pAktuellKB != NULL) {
            /* Tilslag */
            *pBgr = pGeoStat->pAktuellKB->Bgr;
            return UT_TRUE;
         }
      }

   /* Sekvensiell gjennomgang av alle grupper */
   } else {
      LC_R_LEAF * pRL;
      LC_BGR Bgr = pGeoStat->Bgr;

      while (LC_NextBgr(&Bgr,pGeoStat->usLag)) {
         if (LI_InqBt(Bgr.pFil,Bgr.lNr,BT_REFBOX)) {
            pRL = LI_GetGeo(Bgr.pFil,Bgr.lNr);
            if (pRL != NULL) {
               /* Sjekk område-tabellen */
               if (pGeoStat->ohn >= pRL->Boks.dMinNord && pGeoStat->oha >= pRL->Boks.dMinAust &&
                   pGeoStat->nvn <= pRL->Boks.dMaxNord && pGeoStat->nva <= pRL->Boks.dMaxAust) {
                  *pBgr = pGeoStat->Bgr = Bgr;            /* Tilslag */
                  return UT_TRUE;
               }
            }
         }
      }

      /* Ikke tilslag */
      pGeoStat->Bgr = Bgr;
   }
   
   /* Ikke tilslag */
   return UT_FALSE;
}


/*
AR-890824
CH LC_WTst                                                        Vindustest
CD ==========================================================================
CD Formål:
CD Sjekk om aktuell gruppe berører gitt vindu.
CD Tar hensyn til gruppenavnet. Handterer (PUNKT, LINJE, KURVE, BUE,
CD BUEP, SIRKEL, SIRKELP, SVERM, TRASE ).
CD
CD Parametre:
CD Type    Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  nva        i    Avgrensing av vinduet
CD double  nvn        i
CD double  oha        i
CD double  ohn        i
CD short   ist        r    status: 0 = ikke berøring
CD                                 1 = skjæring
CD
CD Bruk:
CD .
CD LC_SBGeo(&GeoStat,nv_a,nv_n,oh_a,oh_n);
CD if (LC_FFGeo(&GeoStat,&Bgr)){
CD     do{
CD         LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
CD         if (LC_WTst(nv_a,nv_n,oh_a,oh_n)) {       (Nøyaktig vindustest)
CD             . Behandle funnet gruppe
CD             .
CD         }
CD     } while (LC_FNGeo(&GeoStat,&Bgr));
CD }
CD LC_AvsluttSok(&GeoStat);
CD .
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_WTst(double nva,double nvn,double oha,double ohn)
{
   short ngi,gruppenavn,sfeil;
   long nko,pt;
   unsigned short info;
   double radius,aust,nord,fi,dfi;
   double *pdAust = Sys.pdAust;
   double *pdNord = Sys.pdNord;


   if (Sys.GrId.lNr != INGEN_GRUPPE) {            /* Har aktuell gruppe */
      gruppenavn = LC_GetGrPara(&ngi,&nko,&info);
      if (nko > 0){                           /* Har koordinater */

            /* .BUE, .BUEP, .SIRKEL eller .SIRKELP */
         if (gruppenavn == L_BUE  ||  gruppenavn == L_BUEP ||
             gruppenavn == L_SIRKEL  ||  gruppenavn == L_SIRKELP) {

            if (LC_GetBuePar(HENT_FORRFRA,&aust,&nord,&radius,&fi,&dfi,&sfeil)) {
               /* Vindustest på buen */
               if (GM_wtstBue(aust,nord,radius,fi,dfi,nva,nvn,oha,ohn)) {
                  return(1);
               }

            } else {
               // Spesialhandtering av ulogiske sirkler og buer
               // Handteres som punkt/linje
                                           // Sjekk første koordinat
               if (GM_wtst(*pdAust,*pdNord,*pdAust,*pdNord,nva,nvn,oha,ohn)) {
                  return(1);
               }

               // Sjekk resten av gruppen
               ++pdAust;
               ++pdNord;
               for (pt=1; pt<Sys.pGrInfo->nko; ++pt,++pdAust,++pdNord) {
                  if (GM_wtst(*(pdAust-1),*(pdNord-1),*pdAust,*pdNord,
                              nva,nvn,oha,ohn)) {
                     return(1);
                  }
               }
            }

         /* .PUNKT eller .SVERM */
         } else if (gruppenavn == L_PUNKT  ||  gruppenavn == L_SVERM) {
            /* Sjekk om noe punkt er innenfor */
            for (pt=1; pt<=Sys.pGrInfo->nko; ++pt) {
               LC_GetTK(pt,&aust,&nord);
               if (aust >= nva  &&  aust <= oha  &&
                   nord >= nvn  &&  nord <= ohn    ) {
                  return(1);
               }
            }

         /* .TRASE */
         } else if (gruppenavn == L_TRASE) {

            short ngi;
            long nko;
            unsigned short info;
            LC_POLYGON Polygon;
            LC_POL_ELEMENT * pPE;
            LC_BGR BgrTrase = Sys.GrId;      /* Husk gruppenummer for traseen */


            /* Initier referansehandtering, og les beskrivelsen */
            LC_POL_InitPolygon(&Polygon);
            LC_POL_GetRef(&Polygon);

            /* Behandle referansene */
            for (pPE = Polygon.HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
               LC_RxGr(&pPE->Bgr,LES_OPTIMALT,&ngi,&nko,&info);
               if (LC_WTst(nva,nvn,oha,ohn)) {      /* (Nøyaktig vindustest) */
                  /* Frigi allokerte kjeder */
                  LC_POL_FrigiPolygon(&Polygon);

                  /* Les inn traseen igjen */
                  LC_RxGr(&BgrTrase,LES_OPTIMALT,&ngi,&nko,&info);
                  
                  return (1);
               }
            }

            /* Frigi allokerte kjeder */
            LC_POL_FrigiPolygon(&Polygon);

            /* Les inn traseen igjen */
            LC_RxGr(&BgrTrase,LES_OPTIMALT,&ngi,&nko,&info);


         /* Andre gruppenavn */
         } else {
                                           /* Sjekk første koordinat */
            if (GM_wtst(*pdAust,*pdNord,*pdAust,*pdNord,nva,nvn,oha,ohn)) {
               return(1);
            }

            /* Sjekk resten av gruppen */
            ++pdAust;
            ++pdNord;
            for (pt=1; pt<Sys.pGrInfo->nko; ++pt,++pdAust,++pdNord) {
               if (GM_wtst(*(pdAust-1),*(pdNord-1),*pdAust,*pdNord,
                           nva,nvn,oha,ohn)) {
                  return(1);
               }
            }
         }
      }
   }
   return (0);
}


/*
AR-890824
CH LC_PTst                                                        Polygontest
CD ==========================================================================
CD Formål:
CD Sjekker om gitt punkt ligger innenfor polygon angitt av aktuell gruppe.
CD Forutsetter at tabellen danner et lukket polygon
CD
CD Parametre:
CD Type    Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  a        i    Punkt som skal sjekkes
CD double  n        i
CD short   ist      r    status: 0 = punktet er utenfor flaten
CD                               1 = punktet ligger inne på flaten
CD
CD Bruk:
CD .
CD LC_SBFlate(&GeoStat,a-d,n-d,a+d,n+d);
CD if (LC_FFFlate(&GeoStat,&Bgr)) {
CD     do{
CD         LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
CD         if (LC_PTst(a,n)){          (Nøyaktig polygontest)
CD             . Behandle funnet gruppe
CD             .
CD         }
CD     } while (LC_FNFlate(&GeoStat,&Bgr));
CD }
CD LC_AvsluttSok(&GeoStat);
CD .
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_PTst(double a,double n)
{
   LC_POLYGON Polygon;
   short inni = 0;   /* Returverdi: 1 = inne på flaten, 0 = utenfor  */
      
   // Sjekk om gruppen er flate
   if (Sys.pGrInfo->gnavn == L_FLATE)
   {
      // Initier flatehandtering, og les flatebeskrivelsen
      LC_POL_InitPolygon(&Polygon);
      LC_POL_GetRef(&Polygon);

      // Utfør selve polygontesten
      inni = LC_POL_PTst(&Polygon,a,n);

      // Frigi allokerte kjeder
      LC_POL_FrigiPolygon(&Polygon);
   }
   
   return  inni;
}


/*
AR-911002
CH LC_PTstOmkrets                         Sjekk om punkt ligger inni polygon
CD ==========================================================================
CD Formål:
CD Sjekker om gitt punkt ligger innenfor yttergrensen for polygon angitt
CD av aktuell gruppe.
CD Forutsetter at tabellen danner et lukket polygon
CD
CD Parametre:
CD Type    Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  a        i    Punkt som skal sjekkes
CD double  n        i
CD short   ist      r    status: 0 = punktet er utenfor flaten
CD                               1 = punktet ligger inne på flaten
CD
CD Bruk:
CD ist = LC_PTstOmkrets(a,n);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_PTstOmkrets(double a,double n)
{
   long ref_arr[MAX_REF];
   unsigned char ref_status[MAX_REF];
   long ant_ref;
   short ngi,s;
   long nko;
   unsigned short info;
   LC_GRF_STATUS GrfStat;
   LC_BGR Bgr;
   short sAntSkjaer = 0;
   LC_BGR Flate = Sys.GrId;      /* Husk gruppenummer for flaten */

   Bgr.pFil = Flate.pFil;

   double dEnhet = Sys.pGrInfo->dEnhet;

   // Pluss på et lite tillegg for å unngå treff på node
   a += dEnhet / 1000.0;
   n += dEnhet / 1000.0;

   /* Sjekk om gruppen er flate */
   if (LC_GetGrPara(&ngi,&nko,&info) == L_FLATE){

      LC_InitGetRefFlate(&GrfStat);

      /* Behandle ytre avgrensing */
      ant_ref = LC_GetRefFlate(&GrfStat,GRF_YTRE,ref_arr,ref_status,MAX_REF);
      do {
         for (s=0; s<ant_ref; s++) {
            Bgr.lNr = ref_arr[s];
            sAntSkjaer += LR_PTstGruppe(&Bgr,a,n);
         }
         /* Les inn flaten igjen */    
         LC_RxGr(&Flate,LES_OPTIMALT,&ngi,&nko,&info);

         if (ant_ref < MAX_REF)  break;

         ant_ref = LC_GetRefFlate(&GrfStat,GRF_YTRE,ref_arr,ref_status,MAX_REF);
      } while (ant_ref > 0);
   }

   /* Sjekk om punktet er innenfor */
   return  ((sAntSkjaer % 2) == 1)?  1 : 0;
}


/*
AR-921028
CH LR_PTstGruppe                  Sjekk om punkt ligger inni polygon
CD ==========================================================================
CD Formål:
CD Sjekker antall skjæringer mellom gitt gruppe og linje fra gitt punkt
CD til "uendelig" øst.
CD
CD Parametre:
CD Type    Navn       I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BGR * pBgr        i    Peker til datagruppe
CD double  a           i    Punkt som skal sjekkes
CD double  n           i
CD short   sAntSkjaer  r    Antall skjæringer
CD
CD Bruk:
CD ist = LR_PTstOmkrets(&Bgr,a,n);
   ==========================================================================
*/
short LR_PTstGruppe(LC_BGR * pBgr,double a,double n)
{
   double maxa = 99999999999.0;           /* "Uendelig" øst */
   short ngi,gruppenavn,sfeil;
   long pt,nko;
   unsigned short info;
   #define ARR_LEN 50
   long punkt, antall;
   double a1,n1,a2,n2,radius,as,ns,fi,dfi;
   double n_arr[ARR_LEN],a_arr[ARR_LEN];
   LC_POLYGON Polygon;
   LC_POL_ELEMENT * pPE;
   LC_BGR BgrTrase;
   short sAntSkjaer = 0;

       
   /* Sjekk gruppen */
   gruppenavn = LC_RxGr(pBgr,LES_OPTIMALT,&ngi,&nko,&info);
   if (nko > 0) {
       
      /* .TRASE */
      if (gruppenavn == L_TRASE) {
         BgrTrase = Sys.GrId;      /* Husk gruppenummer for traseen */

         /* Initier referansehandtering, og les beskrivelsen */
         LC_POL_InitPolygon(&Polygon);
         LC_POL_GetRef(&Polygon);

         /* Behandle referansene */
         for (pPE = Polygon.HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
            sAntSkjaer += LR_PTstGruppe(&pPE->Bgr,a,n);
         }

         /* Frigi allokerte kjeder, og les inn traseen igjen */
         LC_POL_FrigiPolygon(&Polygon);
         LC_RxGr(&BgrTrase,LES_OPTIMALT,&ngi,&nko,&info);

      /* "bue" */
      } else if (gruppenavn == L_BUE     ||  gruppenavn == L_BUEP ||
                 gruppenavn == L_SIRKEL  ||  gruppenavn == L_SIRKELP) {

         if (LC_GetBuePar(HENT_FORRFRA,&as,&ns,&radius,&fi,&dfi,&sfeil)) {
            sAntSkjaer += GM_sLinBue(as,ns,radius,fi,dfi,
                               a,n,maxa,n,&a1,&n1,&a2,&n2);
         }

      /* Annen gruppe */
      } else {                    
         punkt = 1;
         do {                       /* Finn skjæringspunkter */
            LC_GetArrayTK(HENT_FORRFRA,ARR_LEN,punkt,a_arr,n_arr,&antall);/* Henter */
            if (antall > 0) {
               for (pt=1; pt<antall; pt++) {
                  sAntSkjaer += GM_shor(a_arr[pt-1],n_arr[pt-1],
                                    a_arr[pt],n_arr[pt],a,n,maxa,n,&a1,&n1);
               }
               punkt += (antall-1);
            }
         } while (punkt < nko);
      }
   }

   return  sAntSkjaer;
}


/*
AR-980108
CH LR_InsertGeo                     Legg gruppen inn i geografisk indeks
CD =======================================================================
CD Bruk:
CD
CD Parametere:
CD Type          Navn  I/U  Forklaring
CD -----------------------------------------------------------------------
CD LC_FILADM *   pFil   i   Filpeker
CD long          lNr    i   Gruppenummer i filen
CD LC_BOKS *      pB     i   Boks som skal legges inn i treet
CD LC_R_LEAF *    pRL    r   Peker inn i geografisk søketre
CD
CD Formål:
CD Legg gruppen inn i geografisk indeks.
CD Forutsetter at grupen ikke ligger i søketreet fra før.
CD =======================================================================
*/
LC_R_LEAF * LR_InsertGeo(LC_FILADM *pFil,long lNr,LC_BOKS * pB)
{
   LC_R_NODE * pNyRN,*pRotRN;
   LC_R_LEAF * pRL;


   /* Lagre omskrevet boks i søketreet */
   pRL = LR_R_Insert(lNr,pB,NULL,pFil->pGeoRN,&pNyRN);

   /* Hvis rot-noden er splittet må det lages ny rot-node */
   if (pNyRN != NULL) {
      if (pFil->pGeoRN != NULL) {
         /* Lag ny rot-node */
         pRotRN = LR_R_CreateRNode(NULL,LC_NODE);
         pRotRN->Son.pNode[0] = pFil->pGeoRN;
         pRotRN->Son.pNode[1] = pNyRN;
         pRotRN->sSonAnt = 2;

         /* Oppdater boks */
         pRotRN->Boks = pFil->pGeoRN->Boks;
         LR_R_BoksSum(&(pRotRN->Boks),&(pNyRN->Boks));

         /* Oppdater far i sønnene */
         pFil->pGeoRN->pFar = pRotRN;
         pNyRN->pFar = pRotRN;

         pFil->pGeoRN = pRotRN;

      } else {
         pFil->pGeoRN = pNyRN;
      }
   }

   return pRL;
}


/*
AR-980108
CH LR_R_Insert                                             Insert i R-tre
CD =======================================================================
CD Bruk:
CD
CD Parametere:
CD Type         Navn  I/U  Forklaring
CD -----------------------------------------------------------------------
CD long         lGrNr  i   Gruppenummer i filen
CD LC_BOKS     *pB     i   Boks som skal legges inn i treet
CD LC_R_NODE   *pFar   i   Peker til far i quad-treet
CD LC_R_NODE   *pRN    i   Peker til node i R-treet
CD LC_R_NODE  **ppNyRN u   Peker til peker til nyopprettet node i R-treet
CD LC_R_LEAF   *pRL    r   Peker til forekomst i R-treet
CD
CD Formål:
CD Leger inn et rektangl i R-treet med rot i node pRN.
CD Hvis pRN == NULL (Tomt tre) settes *ppNyRN til å peke til et nyt tre.
CD =======================================================================
*/
static LC_R_LEAF * LR_R_Insert(long lGrNr,LC_BOKS *pB,LC_R_NODE *pFar,LC_R_NODE *pRN,LC_R_NODE **ppNyRN)
{
   LC_R_NODE *pNyRN,*pKandidatRN[LC_R_MAX_SON+1];
   LC_R_LEAF *pRL,*pKandidatRL[LC_R_MAX_SON+1];
   int i,iIdxMin=0,iIdxMax=0;
   double dDeltaAreal,dMinDeltaAreal;
   double dMinAust,dMaxAust;

   // Test
   //static int iNivo;
   //iNivo++;
   //UT_FPRINTF(stderr,"LR_R_Insert nivå :%d\n",iNivo);

   
   *ppNyRN = NULL;


   /* Treet er tomt, må allokere ny node */
   if (pRN == NULL) {
      *ppNyRN = pRN = LR_R_CreateRNode(NULL,LC_LEAF);
   }

   /* Har kommet til ytterste nivå */
   if (pRN->sSonType == LC_LEAF) {

      pRL = LR_R_CreateRLeaf(lGrNr,pB,pRN);

      /* Hvis ledig plass */
      if (pRN->sSonAnt < LC_R_MAX_SON) {
         /* Legg inn rektanglet */
         pRN->Son.pLeaf[pRN->sSonAnt] = pRL;
         (pRN->sSonAnt)++;
         
         /* Oppdaterer omskrevet boks */
         LR_R_BoksSum(&(pRN->Boks),pB);

      /* Fullt, må opprett ny node */
      } else {
         *ppNyRN = pNyRN = LR_R_CreateRNode(pRN->pFar,LC_LEAF);

         /* Fordel boksene på de to nodene etter lineær kost algoritmen */

         /* Beregn "ekstrem-bokser" */
         dMinAust = LONG_MAX;
         dMaxAust = LONG_MIN;

         iIdxMax = 0;
         for (i=0; i<pRN->sSonAnt; i++) {
            pKandidatRL[i] = pRN->Son.pLeaf[i];
            if (pKandidatRL[i]->Boks.dMinAust > dMaxAust) {
               dMaxAust = pKandidatRL[i]->Boks.dMinAust;
               iIdxMax = i;
            }
         }
         pKandidatRL[LC_R_MAX_SON] = pRL;
         if (pB->dMinAust > dMaxAust) {
            dMaxAust = pB->dMinAust;
            iIdxMax = LC_R_MAX_SON;
         }

         for (i=0; i<pRN->sSonAnt; i++) {
            if (iIdxMax != i) {
               if (pKandidatRL[i]->Boks.dMaxAust < dMinAust) {
                  dMinAust = pKandidatRL[i]->Boks.dMaxAust;
                  iIdxMin = i;
               }
            }
         }
         if (iIdxMax != LC_R_MAX_SON  &&  pB->dMaxAust < dMinAust) {
            dMinAust = pB->dMaxAust;
            iIdxMin = LC_R_MAX_SON;
         }

         /* Plasser ut ekstremboksene */
         pRN->Son.pLeaf[0] = pKandidatRL[iIdxMax];
         pRN->sSonAnt = 1;
         pRN->Boks = pKandidatRL[iIdxMax]->Boks;
         pKandidatRL[iIdxMax]->pFar = pRN;
         pKandidatRL[iIdxMax] = NULL;

         pNyRN->Son.pLeaf[0] = pKandidatRL[iIdxMin];
         pNyRN->sSonAnt = 1;
         pNyRN->Boks = pKandidatRL[iIdxMin]->Boks;
         pKandidatRL[iIdxMin]->pFar = pNyRN;
         pKandidatRL[iIdxMin] = NULL;

         /* Resten av boksene plasseres der de fører til minst utvielse av boksen */
         for (i=0; i<=LC_R_MAX_SON; i++) {
            if (pKandidatRL[i] != NULL) {

               if (LR_BoksDeltaArealSum(&(pRN->Boks),&(pKandidatRL[i]->Boks)) <
                   LR_BoksDeltaArealSum(&(pNyRN->Boks),&(pKandidatRL[i]->Boks)) ) {

                  pRN->Son.pLeaf[pRN->sSonAnt] = pKandidatRL[i];
                  pRN->sSonAnt++;
                  LR_R_BoksSum(&(pRN->Boks),&(pKandidatRL[i]->Boks));
                  pKandidatRL[i]->pFar = pRN;

               } else {
                  pNyRN->Son.pLeaf[pNyRN->sSonAnt] = pKandidatRL[i];
                  pNyRN->sSonAnt++;
                  LR_R_BoksSum(&(pNyRN->Boks),&(pKandidatRL[i]->Boks));
                  pKandidatRL[i]->pFar = pNyRN;
               }
            }
         }
      }

   /* Node */
   } else {
      /* velg den noden som utvides minst ved tillegg av den nye boksen */
      dMinDeltaAreal = LONG_MAX;
      iIdxMin = 0;
      for (i=0; i<pRN->sSonAnt; i++) {
         /* Beregn hvor mye boksen ville ha blitt utvidet hvis denne ble valget */
         dDeltaAreal = LR_BoksDeltaArealSum(&(pRN->Son.pNode[i]->Boks),pB);
         if (dDeltaAreal < dMinDeltaAreal) {

            dMinDeltaAreal = dDeltaAreal;
            iIdxMin = i;
         }
      }

      /* Legger inn rektanglet i den noden med minst utvdelse */
      pRL = LR_R_Insert(lGrNr,pB,pRN,pRN->Son.pNode[iIdxMin],ppNyRN);

      /* Denne noden har blitt splittet, dette må tas vare på her */
      if (*ppNyRN != NULL) {

         /* Hvis ledig plass */
         if (pRN->sSonAnt < LC_R_MAX_SON) {
            /* Legg inn rektanglet */
            pRN->Son.pNode[pRN->sSonAnt] = *ppNyRN;
            (pRN->sSonAnt)++;
         
            /* Oppdaterer omskrevet boks */
            LR_R_BoksSum(&(pRN->Boks),pB);

            /* Ingen splitting på nivået over */
            *ppNyRN = NULL;

         /* Fullt, må opprett ny node */
         } else {
            pNyRN = LR_R_CreateRNode(pFar,LC_NODE);

            /* Fordel boksene på de to nodene etter lineær kost algoritmen */

            /* Beregn "ekstrem-bokser" */
            dMinAust = LONG_MAX;
            dMaxAust = LONG_MIN;

            for (i=0; i<pRN->sSonAnt; i++) {
               pKandidatRN[i] = pRN->Son.pNode[i];
               if (pKandidatRN[i]->Boks.dMinAust > dMaxAust) {
                  dMaxAust = pKandidatRN[i]->Boks.dMinAust;
                  iIdxMax = i;
               }
            }
            pKandidatRN[LC_R_MAX_SON] = *ppNyRN;
            if (pKandidatRN[i]->Boks.dMinAust > dMaxAust) {
               dMaxAust = pKandidatRN[i]->Boks.dMinAust;
               iIdxMax = LC_R_MAX_SON;
            }

            for (i=0; i<pRN->sSonAnt; i++) {
               if (iIdxMax != i) {
                  if (pKandidatRN[i]->Boks.dMaxAust < dMinAust) {
                     dMinAust = pKandidatRN[i]->Boks.dMaxAust;
                     iIdxMin = i;
                  }
               }
            }

            /* Plasser ut ekstremboksene */
            pRN->Son.pNode[0] = pKandidatRN[iIdxMax];
            pRN->sSonAnt = 1;
            pRN->Boks = pKandidatRN[iIdxMax]->Boks;
            pKandidatRN[iIdxMax]->pFar = pRN;
            pKandidatRN[iIdxMax] = NULL;

            pNyRN->Son.pNode[0] = pKandidatRN[iIdxMin];
            pNyRN->sSonAnt = 1;
            pNyRN->Boks = pKandidatRN[iIdxMin]->Boks;
            pKandidatRN[iIdxMin]->pFar = pNyRN;
            pKandidatRN[iIdxMin] = NULL;

            /* Resten av boksene plasseres der de fører til minst utvielse av boksen */
            for (i=0; i<=LC_R_MAX_SON; i++) {
               if (pKandidatRN[i] != NULL) {

                  if (LR_BoksDeltaArealSum(&(pRN->Boks),&(pKandidatRN[i]->Boks)) <
                      LR_BoksDeltaArealSum(&(pNyRN->Boks),&(pKandidatRN[i]->Boks)) ) {

                     pRN->Son.pNode[pRN->sSonAnt] = pKandidatRN[i];
                     pRN->sSonAnt++;
                     LR_R_BoksSum(&(pRN->Boks),&(pKandidatRN[i]->Boks));
                     pKandidatRN[i]->pFar = pRN;

                  } else {
                     pNyRN->Son.pNode[pNyRN->sSonAnt] = pKandidatRN[i];
                     pNyRN->sSonAnt++;
                     LR_R_BoksSum(&(pNyRN->Boks),&(pKandidatRN[i]->Boks));
                     pKandidatRN[i]->pFar = pNyRN;
                  }
               }
            }

            /* Husk den nye noden til nivået over */
            *ppNyRN = pNyRN;
         }

      } else {
         /* Oppdater omskrevet boks for noden */
         LR_R_BoksSum(&(pRN->Boks),pB);
      }
   }


   // Test
   //iNivo--;

   return pRL;
}
  

/*
AR-980108
CH LR_R_BoksSum                                        Summerer to bokser
CD =======================================================================
CD Formål:
CD Summerer to bokser ved at boks1 blir utvidet slik at den også dekker 
CD boks2.
CD
CD Parametere:
CD Type       Navn  I/U  Forklaring
CD -----------------------------------------------------------------------
CD LC_BOKS *   pB1   iu   Boks1 som skal utvides
CD LC_BOKS *   pB2   i    Boks2 som skal legges til boks1
CD =======================================================================
*/
static void LR_R_BoksSum(LC_BOKS * pB1,LC_BOKS * pB2)
{
   pB1->dMinAust = min(pB1->dMinAust,pB2->dMinAust);
	pB1->dMinNord = min(pB1->dMinNord,pB2->dMinNord);
   pB1->dMaxAust = max(pB1->dMaxAust,pB2->dMaxAust);      
   pB1->dMaxNord = max(pB1->dMaxNord,pB2->dMaxNord);  
}


/*
AR-980108
CH LR_BoksDeltaArealSum                   Bereg arealendring ved sumering
CD =======================================================================
CD Formål:
CD Beregner hvor mye arealet av boks1 blir utvidet hvis den blir
CD summert med boks2.
CD
CD Parametere:
CD Type       Navn       I/U  Forklaring
CD -----------------------------------------------------------------------
CD LC_BOKS *   pB1         i   Boks1
CD LC_BOKS *   pB2         i   Boks2
CD double     dDeltaAreal r   Arealendring
CD =======================================================================
*/
static double LR_BoksDeltaArealSum(LC_BOKS * pB1,LC_BOKS * pB2)
{
    //long lNy, lGml;
    //lGml = (pB1->dMaxAust - pB1->dMinAust) * (pB1->dMaxNord - pB1->dMinNord);
    //return (lNy - lGml); 

    double dDeltaAreal = (max(pB1->dMaxAust,pB2->dMaxAust) - min(pB1->dMinAust,pB2->dMinAust)) *
                         (max(pB1->dMaxNord,pB2->dMaxNord) - min(pB1->dMinNord,pB2->dMinNord));

    return dDeltaAreal; 
}


/*
AR-980108
CH LR_R_Delete                                       Fjern fra "søketreet"
CD =======================================================================
CD Bruk:
CD
CD Parametere:
CD Type        Navn  I/U  Forklaring
CD -----------------------------------------------------------------------
CD LC_R_LEAF *  pRL    i   Peker til forekomst i R-treet
CD
CD Formål:
CD Fjern et gitt element fra R-treet for geografisk søk.
CD =======================================================================
*/
void LR_R_Delete(LC_R_LEAF * pRL)
{
   LC_R_NODE *pFar,*pRN,*pSonRN;
   int i,iFunnet,iIdx=0,iFerdig;


   if (pRL != NULL) {
      // Husk "far"
      pFar = pRL->pFar;

      /* Fjerner pekeren fra gruppetabellen */
      Sys.pGrInfo->pRL = NULL;

      /* Fjern pekeren til løvet */
      pRN = pFar;
      iFunnet = UT_FALSE;

      for (i=0; i<pRN->sSonAnt; i++) {
      
         /* Sjekk om dette er den rette pekeren */
         if (iFunnet == UT_FALSE) {
            if (pRN->Son.pLeaf[i] == pRL) {
               iFunnet = UT_TRUE;
               iIdx = i;
            }

         /* Pakk de andre pekerne i denne noden */
         } else {
            pRN->Son.pLeaf[iIdx] = pRN->Son.pLeaf[i];
         }
      }

      if (iFunnet == UT_TRUE) {
         (pRN->sSonAnt)--;
      }

      // Frigir det aktuelle "løvet"
      UT_FREE((char *)pRL);

      /* Sjekk om det er mere som skal fjernes oppover i treet */
      iFerdig = UT_FALSE;
      while ( iFerdig == UT_FALSE) {

         /* Antall sønner er 0, denne noden skal fjernes på nivået over */
         if (pRN->sSonAnt == 0) {

            // Er ikke på øverste nivå
            if (pRN->pFar != NULL)  {

               /* Husk noden */
               pSonRN = pRN;
         
               /* Fjern pekeren til noden */
               pRN = pSonRN->pFar;
               iFunnet = UT_FALSE;
   
               for (i=0; i<pRN->sSonAnt; i++) {
      
                  /* Sjekk om dette er den rette pekeren */
                  if (iFunnet == UT_FALSE) {
                     if (pRN->Son.pNode[i] == pSonRN) {
                        iFunnet = UT_TRUE;
                        iIdx = i;
                     }

                  /* Pakk de andre pekerne i denne noden */
                  } else {
                     pRN->Son.pNode[iIdx] = pRN->Son.pNode[i];
                  }
               }

               if (iFunnet == UT_TRUE) {
                  (pRN->sSonAnt)--;
               }

               /* Frigir noden */
               UT_FREE((char *)pSonRN);
         

            /* Har kommet til toppen */
            } else {
               iFerdig = UT_TRUE;

               /* Treet er tomt initierer verdier på nytt */
               pRN->sSonType = LC_LEAF;
               /* Omskrevet boks initieres til stor invers verdi */
               pRN->Boks.dMinAust =	pRN->Boks.dMinNord = LONG_MAX;
               pRN->Boks.dMaxAust = pRN->Boks.dMaxNord = LONG_MIN;
            }


         /* Har flere sønner, må beregne omskrevet boks på nytt */
         } else {

            pRN->Boks.dMinAust =	pRN->Boks.dMinNord = LONG_MAX;
            pRN->Boks.dMaxAust = pRN->Boks.dMaxNord = LONG_MIN;

            if (pRN->sSonType == LC_LEAF) {
               for (i=0; i<pRN->sSonAnt; i++) {
                  LR_R_BoksSum(&(pRN->Boks),&(pRN->Son.pLeaf[i]->Boks));
               }

            } else {
               for (i=0; i<pRN->sSonAnt; i++) {
                  LR_R_BoksSum(&(pRN->Boks),&(pRN->Son.pNode[i]->Boks));
               }
            }

            iFerdig = UT_TRUE;
         }
      }
   }
}


/*
AR-980204
CH LR_R_CreateRNode                         Alloker og initier R-tre-node
CD =======================================================================
CD Bruk:
CD
CD Parametere:
CD Type          Navn  I/U  Forklaring
CD -----------------------------------------------------------------------
CD LC_R_NODE *  pFar     i  Peker til far i R-treet
CD short       sSonType i  Hvilken type sønner har denne noden LC_NODE / LC_LEAF
CD LC_R_NODE *  pRN      r  Peker til ny node i R-tre
CD
CD Formål:
CD Alloker og initier node i R-tre.
CD =======================================================================
*/
static LC_R_NODE * LR_R_CreateRNode( LC_R_NODE * pFar,short sSonType)
{
   LC_R_NODE * pRN;

   pRN = (LC_R_NODE *)UT_MALLOC(sizeof(LC_R_NODE));

   pRN->pFar = pFar;
   pRN->sSonType = sSonType;
   pRN->sSonAnt = 0;


   //for (i=0; i>LC_R_MAX_SON; i++) {
   //   if (sSonType == LC_NODE) {
   //      pRN->Son.pNode[i] = NULL;
   //   } else {
   //      pRN->Son.pLeaf[i] = NULL;
   //   }
   //}

   /* Omskrevet boks initieres til stor invers boks */
   pRN->Boks.dMinAust =	pRN->Boks.dMinNord = LONG_MAX;
   pRN->Boks.dMaxAust = pRN->Boks.dMaxNord = LONG_MIN;

   return pRN;
}


/*
AR-980204
CH LR_R_CreateRLeaf                         Alloker og initier R-tre-løv
CD =======================================================================
CD Bruk:
CD
CD Parametere:
CD Type        Navn   I/U  Forklaring
CD -----------------------------------------------------------------------
CD long        lGrNr   i  Gruppenummer i filen
CD LC_BOKS *    pB      i  Boks som skal legges inn i treet
CD LC_R_NODE *  pFar    i  Peker til far i R-treet
CD LC_R_LEAF *  pCL     r  Peker til ny forekomst
CD
CD Formål:
CD Alloker og initier løv R-tre.
CD =======================================================================
*/
static LC_R_LEAF * LR_R_CreateRLeaf(long lGrNr, LC_BOKS * pB,LC_R_NODE * pFar)
{
   LC_R_LEAF * pCL = (LC_R_LEAF *)UT_MALLOC(sizeof(LC_R_LEAF));

   pCL->pFar = pFar;
   pCL->Boks = *pB;
   pCL->lNr = lGrNr;

   return pCL;
}


/*
AR-980113
CH LR_LeggTilKB                         Legg til Bgr i søkeresultat-kjede
CD =======================================================================
CD Bruk:
CD
CD parametere:
CD Type            Navn     I/U   Forklaring
CD -----------------------------------------------------------------------
CD LC_GEO_STATUS *  pGeoStat  i    Peker til struktur for søkestatus
CD LC_FILADM *     pFil      i    Filpeker
CD long            lNr       i    Gruppenummer i filen
CD
CD Formål:
CD Legg til Bgr i kjede med søkeresultat.
CD =======================================================================
*/
static void LR_LeggTilKB(LC_GEO_STATUS * pGeoStat,LC_FILADM *pFil,long lNr)
{
   LC_KJEDE_BGR * pKB;

   pKB = (LC_KJEDE_BGR *) UT_MALLOC(sizeof(LC_KJEDE_BGR));

   /* Sosi-gruppe */
   pKB->Bgr.pFil = pFil;
   pKB->Bgr.lNr = lNr;   
  
  /* Oppdater pekerne i kjeden */
  pKB->pNesteKB = NULL;
  
  if (pGeoStat->pForsteKB == NULL) {
    pGeoStat->pForsteKB = pKB;

  } else {
    pGeoStat->pSisteKB->pNesteKB = pKB;
  }

  pGeoStat->pSisteKB = pKB;
}


/*
AR-980113
CH LC_AvsluttSok                                 Avslutter geografisk søk
CD =======================================================================
CD Bruk:
CD
CD parametere:
CD Type            Navn     I/U   Forklaring
CD -----------------------------------------------------------------------
CD LC_GEO_STATUS *  pGeoStat  i    Peker til struktur for søkestatus
CD
CD Formål:
CD Avslutter geografisk søk, og frigir kjede med søkeresultat.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_AvsluttSok(LC_GEO_STATUS * pGeoStat)
{
   LC_KJEDE_BGR *pKB, *pNesteKB; 
      
      
   pNesteKB = pGeoStat->pForsteKB;

   while (pNesteKB != NULL) {
      pKB = pNesteKB;
      pNesteKB = pKB->pNesteKB;
      UT_FREE(pKB);
   }

   pGeoStat->pForsteKB = NULL;
   pGeoStat->pSisteKB = NULL;
   pGeoStat->pAktuellKB = NULL;
}


/*
AR-980209
CH LR_VelgMetode                         Velg søkemetode for geografisk søk
CD ==========================================================================
CD Formål:
CD Velg søkemetode for geografisk søk. Bruker R-tre hvis utstrekningen av
CD søkeområdet er mindre enn 10% av baseområdet i nord eller øst retning.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_GEO_STATUS * pGeoStat  iu   Peker til struktur for søkestatus
CD
   ==========================================================================
*/
static void LR_VelgMetode(LC_GEO_STATUS * pGeoStat)
{
   LC_BOKS * pB = &Sys.pAktBase->Omraade;
 
   if ( pGeoStat->oha - pGeoStat->nva < (pB->dMaxAust - pB->dMinAust) / 10  ||
        pGeoStat->ohn - pGeoStat->nvn < (pB->dMaxNord - pB->dMinNord) / 10 ) {
     pGeoStat->usMetode = LC_GEO_RTRE;

   } else {
     pGeoStat->usMetode = LC_GEO_SEKV;
   }
}


/*
AR-980108
CH LR_R_FrigiGren                           Frigir en gren fra "søketreet"
CD =======================================================================
CD Bruk:
CD
CD Parametere:
CD Type        Navn  I/U  Forklaring
CD -----------------------------------------------------------------------
CD LC_R_NODE *  pRN    i   Peker til node i R-treet
CD
CD Formål:
CD Frigir en gren fra R-treet for geografisk søk.
CD =======================================================================
*/
void LR_R_FrigiGren(LC_R_NODE * pRN)
{
   int i;

   /* Har kommet til ytterste nivå */
   if (pRN->sSonType == LC_LEAF) {
      /* Sjekk løvene som er lagret under denne noden */
      for (i=0; i<pRN->sSonAnt; i++) { 
         UT_FREE((char *)pRN->Son.pLeaf[i]);
      }

   /* Node */
   } else {
      /* Rekursiv sjekk av de underliggende nodene */
      for (i=0; i<pRN->sSonAnt; i++) { 
         // Vis alle underliggende nivåer
         LR_R_FrigiGren(pRN->Son.pNode[i]);
      }
   }

   UT_FREE((char *)pRN);
}
