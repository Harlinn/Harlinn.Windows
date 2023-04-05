/* === AR-970929 ========================================================= */
/*  STATENS KARTVERK  -  FYSAK-PC                                          */
/*  Fil: fylp.c                                                            */
/*  Innhold: Polygonhandtering for FYSAK-PC                                */
/* ======================================================================= */

#include "fyba.h"
#include "fybax.h"

#include <ctype.h>
#include <memory.h>
#include <limits.h>
#include <string.h>


/* Globale variabler for FYBA */
extern LC_SYSTEMADM Sys;             /* Systemadministrasjon */


/*
AR-970929
CH LC_POL_LeggTilGruppeOmkrets                       Legg til eit element
CD =======================================================================
CD Bruk:
CD LC_POL_OMKR  YtrePolygon;
CD pElement = LC_POL_LeggTilGruppeOmkrets(YtrePolygon,pBgr,sRetning,lSnr);
CD
CD parametere:
CD Type            Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POL_OMKR *    pPO      I/U    Peikar til polygonadministrasjonsblokka
CD LC_BGR *         pBgr      I     Gruppenummer
CD short           sRetning  I     Nøsteretning (LC_MED_DIG eller LC_MOT_DIG)
CD long            lSnr      I     Serienummer
CD LC_POL_ELEMENT * pElement  R     Peker til innlagt element
CD
CD Legg til eit element i kjeden av polygonelement.
CD =======================================================================
*/
SK_EntPnt_FYBA LC_POL_ELEMENT * LC_POL_LeggTilGruppeOmkrets(LC_POL_OMKR *pPO,LC_BGR *pBgr,
                                                short sRetning, long lSnr)
{
  LC_POL_ELEMENT * pPE;
  pPE = (LC_POL_ELEMENT *) UT_MALLOC(sizeof(LC_POL_ELEMENT));
  pPE->pForrigePE = pPO->pSistePE;
  pPE->pNestePE = NULL;

  if(pPO->pForstePE == NULL) {
    pPO->pForstePE = pPE;

  } else {
    pPO->pSistePE->pNestePE = pPE;

  }

  pPO->pSistePE = pPE;

  pPE->Bgr = *pBgr;
  pPE->sRetning = sRetning;
  pPE->lSnr = lSnr;

  return pPE;
}


/*
SJM-930921
CH LC_POL_FjernSisteGruppeOmkrets                   Fjernar siste element
CD =======================================================================
CD Bruk:
CD LC_POL_OMKR  YtrePolygon;
CD LC_POL_FjernSisteGruppeOmkrets(&YtrePolygon);
CD
CD parametere:
CD Type         Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POL_OMKR *  pPO      I/U    Peikar til polygonadministrasjonsblokka
CD
CD Fjernar siste element i kjeden av polygonelement.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_FjernSisteGruppeOmkrets(LC_POL_OMKR *pPO)
{
   LC_POL_ELEMENT *pPE = pPO->pSistePE;

   if (pPE != NULL) {
      pPO->pSistePE = pPE->pForrigePE;
      if(pPE->pForrigePE == NULL) {
         pPO->pForstePE = NULL;

      } else {
         pPE->pForrigePE->pNestePE = NULL;
      }
		UT_FREE(pPE);
   }
}


/*
AR-971112
CH LC_POL_FjernGruppeOmkrets                              Fjernar element
CD =======================================================================
CD Bruk:
CD LC_POL_OMKR  YtrePolygon;
CD LC_POL_FjernGruppeOmkrets(&YtrePolygon,);
CD
CD parametere:
CD Type            Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POL_OMKR    *pPO      I/U    Peikar til polygonadministrasjonsblokka
CD LC_POL_ELEMENT *pPE       I      Peker til element som skal fjernes
CD
CD Fjernar et element i kjeden av polygonelement.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_FjernGruppeOmkrets(LC_POL_OMKR *pPO, LC_POL_ELEMENT *pPE)
{
   /* Oppdaterer pekeren til neste element */
   if (pPE->pForrigePE != NULL) {
      /* Inne i kjeden */
      pPE->pForrigePE->pNestePE = pPE->pNestePE;
   } else {
      /* Starten av kjeden */
      pPO->pForstePE = pPE->pNestePE;
   }

   /* Oppdaterer pekeren til forrige element */
   if (pPE->pNestePE != NULL) {
      /* Inne i kjeden */
      pPE->pNestePE->pForrigePE = pPE->pForrigePE;
   } else {
      /* Slutten av kjeden */
      pPO->pSistePE = pPE->pForrigePE;
   }
	UT_FREE(pPE);
}


/*
SJM-930921
CH LC_POL_FrigiAlleOyer    Frigjer minne som er allokert til kjede av øyelement
CD =======================================================================
CD Bruk:                           
CD LC_OY_ADM  OyKjede;
CD LC_POL_FrigiAlleOyer(OyKjede);
CD
CD parametere:
CD Type       Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_OY_ADM *pOA      I/U    Peikar til øyadministrasjonsblokka
CD
CD Frigjer minne som er allokert til kjede av øy (i polygon) - element.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_FrigiAlleOyer(LC_OY_ADM *pOA)
{
  LC_OY_ELEMENT *pOE,*pNesteOE;

  pOE = pOA->pForsteOE;

  /* Frigir omkretsen av hver øy */
  while(pOE != NULL) {
    LC_POL_FrigiOmkrets(&(pOE->PO));
	 pNesteOE = pOE->pNesteOE;
	 UT_FREE(pOE);
	 pOE = pNesteOE;
  }
  pOA->pForsteOE = NULL;
  pOA->pSisteOE = NULL;
}


/*
SJM-931003
CH LC_POL_FjernOy                    Fjernar ei oy frå kjede av øyelement
CD =======================================================================
CD Bruk:
CD LC_OY_ADM  OyKjede;
CD LC_POL_FjernOy(OyKjede,OyElement);
CD
CD parametere:
CD Type           Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_OY_ADM     *pOA      I/U    Peikar til øyadministrasjonsblokka
CD LC_OY_ELEMENT *pOE      I/U    Peikar til kjede av oyar
CD
CD Frigjer minne som er allokert til kjede av øy (i polygon) - element.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_FjernOy(LC_OY_ADM *pOA,LC_OY_ELEMENT *pOE)
{
   /* UT_FPRINTF(stderr,"LC_POL_FjernOy: Kallar LC_POL_Frigi()\n"); */
   LC_POL_FrigiOmkrets(&(pOE->PO));

   /* Frigir øykjeda */
   if (pOE->pForrigeOE != NULL) {
      pOE->pForrigeOE->pNesteOE = pOE->pNesteOE;
   } else {
      pOA->pForsteOE = pOE->pNesteOE;
   }

   if (pOE->pNesteOE != NULL) {
      pOE->pNesteOE->pForrigeOE = pOE->pForrigeOE;
   } else {
      pOA->pSisteOE = pOE->pForrigeOE;
   }
	UT_FREE(pOE);
}


/*
SJM-930921
CH LC_POL_LeggTilOy                                  Legg til eit element
CD =======================================================================
CD Bruk:
CD LC_OY_ADM  OyKjede;
CD LC_POL_LeggTilOy(&OyKjede,pPO);
CD
CD Parametere:
CD Type         Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_OY_ADM   *pOyKjede I/U    Peikar til kjede av øyelement
CD LC_POL_OMKR *pPO       I     Peikar til polygonadministrasjonsblokka
CD
CD Legg til eit element i kjeden av øyar (i polygon) - element.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_LeggTilOy(LC_OY_ADM *pOA,LC_POL_OMKR *pPO)
{
  LC_OY_ELEMENT *pOE;
  pOE = (LC_OY_ELEMENT *) UT_MALLOC(sizeof(LC_OY_ELEMENT));
  pOE->pForrigeOE = pOA->pSisteOE;
  pOE->pNesteOE = NULL;
  pOE->PO = *pPO;

  if(pOA->pForsteOE == NULL) {
    pOA->pForsteOE = pOE;

  } else {
    pOA->pSisteOE->pNesteOE = pOE;

  }

  pOA->pSisteOE = pOE;
  /* *********************************************
  UT_FPRINTF(stderr,"LC_POL_LeggTilOy: Aktuell OE %p\n",pOE);
  UT_FPRINTF(stderr,"LC_POL_LeggTilOy: OA->førsteOE %p\n" ,pOA->pForsteOE);
  UT_FPRINTF(stderr,"LC_POL_LeggTilOy: SisteOE->nesteOE %p\n",pOA->pSisteOE->pNesteOE);
  UT_FPRINTF(stderr,"LC_POL_LeggTilOy: SisteOE %p\n",pOA->pSisteOE);
   ********************************************* */
}


/*
SJM-930921
CH LC_POL_FrigiOmkrets     Frigjer minne som er allokert til kjede av polygonelement
CD =======================================================================
CD Bruk:
CD
CD parametere:
CD Type         Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POL_OMKR *pPO      I/U    Peikar til polygonadministrasjonsblokka
CD
CD Frigir minne som er allokert til kjede av polygonelement.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_FrigiOmkrets(LC_POL_OMKR *pPO)
{
  LC_POL_ELEMENT *pPE,*pNestePE;

  pPE = pPO->pForstePE;

  while(pPE != NULL) {
    /* UT_FPRINTF(stderr,"LC_POL_FrigiOmkrets: pPE = %p\n",pPE); */
	 pNestePE = pPE->pNestePE;
	 UT_FREE(pPE);
	 pPE = pNestePE;
  }
  pPO->pForstePE = NULL;
  pPO->pSistePE = NULL;
}


/*
AR-931208
CH LC_POL_FrigiPolygon            Frigi minne som er allokert til polygon
CD =======================================================================
CD Formål:
CD Frigir minne som er allokert til polygon. (Både omkrets og hull.)
CD
CD Parametere:
CD Type        Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POLYGON *pPolygon  I     Peikar til polygonbeskrivelse
CD
CD Bruk:
CD LC_POLYGON  Polygon;
CD LC_POL_FrigiPolygon(&Polygon);
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_FrigiPolygon(LC_POLYGON *pPolygon)
{
   /* Frigir øy-kjeden */
   LC_POL_FrigiAlleOyer(&(pPolygon->OyOA));

   /* Frigir omkretsen */
   LC_POL_FrigiOmkrets(&(pPolygon->HovedPO));
}


/*
SJM-930921  
CH LC_POL_InitOmkrets                           Initierer polygon-omkrets
CD =======================================================================
CD Bruk:
CD POL_OMKR  YtrePolygon;
CD LC_POL_InitOmkrets(YtrePolygon);
CD
CD parametere:
CD Type         Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POL_OMKR *pPO      I/U    Peikar til polygonadministrasjonsblokka
CD
CD Initierer administrasjonsblokka for polygonelement
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_InitOmkrets(LC_POL_OMKR *pPO)
{
  pPO->pForstePE = NULL;
  pPO->pSistePE = NULL;
}


/*
SJM-930921 
CH LC_POL_InitOy                                      Initierer øy-kjeden
CD =======================================================================
CD Bruk:
CD LC_OY_ADM  OyKjede;
CD LC_POL_InitOy(OyKjede);
CD
CD parametere:
CD Type       Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_OY_ADM *pOA      I/U    Peikar til øyadministrasjonsblokka
CD
CD Initierer øy-kjeden.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_InitOy(LC_OY_ADM *pOA)
{
  pOA->pForsteOE = NULL;
  pOA->pSisteOE = NULL;
}


/*
AR-931208
CH LC_POL_InitPolygon                          Initierer polygon-struktur
CD =======================================================================
CD Formål:
CD Initierer polygon-struktur.
CD
CD Parametere:
CD Type        Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POLYGON *pPolygon  I     Peikar til polygonbeskrivelse
CD
CD Bruk:
CD LC_POLYGON  Polygon;
CD LC_POL_InitPolygon(&Polygon);
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_InitPolygon(LC_POLYGON *pPolygon)
{
   LC_POL_InitOmkrets(&(pPolygon->HovedPO));
   LC_POL_InitOy(&(pPolygon->OyOA));
}


/*
AR-931208
CH LC_POL_PutRef                            Legger inn referanser i GINFO
CD =======================================================================
CD Formål:
CD Legger inn referanser i GINFO, ut fra beskrivelse i struktur.
CD
CD Parametere:
CD Type        Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POLYGON *pPolygon  I     Polygonbeskrivelse
CD short       ngi       r     Antall linjer GINFO
CD
CD Bruk:
CD ngi = LC_POL_PutRef(pPolygon);
CD =======================================================================
*/
SK_EntPnt_FYBA short LC_POL_PutRef(LC_POLYGON *pPolygon)
{
   #define MAX_LEN  66   /* Ginfolinjen skrives ut når den er lengre en 70 tegn */
   LC_POL_ELEMENT *pPE;
   LC_OY_ELEMENT *pOE;
   short gilin;
   char temp[LC_MAX_SOSI_LINJE_LEN],*ginfo,*cp;
   char szOrd[50];
   short ledig_linje = -1;


   if (Sys.GrId.lNr != INGEN_GRUPPE){                  /* Aktuell gruppe OK */
      /* Pakker gammel GINFO */
      for (gilin=2; gilin <= Sys.pGrInfo->ngi; gilin++) {
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
            for (gilin++; gilin <= Sys.pGrInfo->ngi; gilin++) {
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
               ledig_linje++;
            }
         }

      
      }

      if (ledig_linje == -1)  ledig_linje = Sys.pGrInfo->ngi + 1;


      /* Legger inn referanser */
      if (pPolygon->HovedPO.pForstePE != NULL) {
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

         /* Legger ut hovedpolygonet */
         for (pPE = pPolygon->HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {

            /* Strengen er full, skriver ut */
            if(strlen(temp) > MAX_LEN) {
               if (ledig_linje > Sys.pGrInfo->ngi) {
                  ledig_linje = LC_AppGiL();
               }
               LC_PutGi(ledig_linje,temp);
               ledig_linje ++;

               if (Sys.GrId.pFil->sSosiVer >= 220) {
                  *temp = '\0';
                  cp = temp;
               } else {   
                  UT_StrCopy(temp,".. ",LC_MAX_SOSI_LINJE_LEN);
                  cp = temp + 3;
               }
            }

            /* Skriv ut referansen */
            if (cp > temp) {
               if (! UT_IsSpace(*(cp-1))  &&  *(cp-1) != '(') {
                  *cp++ = ' ';
                  *cp = '\0';
               }
            }    
            UT_SNPRINTF(szOrd, 50, ":%ld", ((pPE->sRetning == LC_MED_DIG)?  pPE->lSnr : -pPE->lSnr));
            UT_StrCat(temp, szOrd, LC_MAX_SOSI_LINJE_LEN);
            cp = strchr(temp,'\0');
         }


         /* Legger ut øyer */
         for (pOE = pPolygon->OyOA.pForsteOE; pOE != NULL; pOE = pOE->pNesteOE) {
            /* Strengen er full, skriver ut */
            if(strlen(temp) >= (MAX_LEN-2)) {
               if (ledig_linje > Sys.pGrInfo->ngi) {
                  ledig_linje = LC_AppGiL();
               }
               LC_PutGi(ledig_linje,temp);
               ledig_linje ++;

               if (Sys.GrId.pFil->sSosiVer >= 220) {
                  *temp = '\0';
                  cp = temp;
               } else {   
                  UT_StrCopy(temp,".. ",LC_MAX_SOSI_LINJE_LEN);
                  cp = temp + 3;
               }
            }

            /* Startparantesen */
            if (cp > temp) {
               if (! UT_IsSpace(*(cp-1))) {
                  *cp++ = ' ';
               }
            }
            *cp++ = '(';
            *cp = '\0';

            /* Legger ut elementa i øyane */
            for (pPE = pOE->PO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {

               /* Strengen er full, skriver ut */
               if(strlen(temp) >= MAX_LEN) {
                  if (ledig_linje > Sys.pGrInfo->ngi) {
                     ledig_linje = LC_AppGiL();
                  }
                  LC_PutGi(ledig_linje,temp);
                  ledig_linje ++;

                  if (Sys.GrId.pFil->sSosiVer >= 220) {
                     *temp = '\0';
                     cp = temp;
                  } else {   
                     UT_StrCopy(temp,".. ",LC_MAX_SOSI_LINJE_LEN);
                     cp = temp + 3;
                  }
               }

               /* Skriv ut referansen */
               if (cp > temp) {
                  if (! UT_IsSpace(*(cp-1))  &&  *(cp-1) != '(') {
                     *cp++ = ' ';
                     *cp = '\0';
                  }
               }
               UT_SNPRINTF(szOrd, 50, ":%ld", ((pPE->sRetning == LC_MED_DIG)?  pPE->lSnr : -pPE->lSnr));
               UT_StrCat(temp, szOrd, LC_MAX_SOSI_LINJE_LEN);
               cp = strchr(temp,'\0');
            }


            /* Sluttparantesen */
            if (cp > temp) {
               if (*(cp-1) == '.') {
                  *cp++ = ' ';
               }
            }
            *cp++ = ')';
            *cp = '\0';
         }


         /* Skriver ut resten av strengen */
         if ((Sys.GrId.pFil->sSosiVer >= 220  &&  strlen(temp) > 0)  ||
             strlen(temp) > 3) {
            if (ledig_linje > Sys.pGrInfo->ngi) {
               ledig_linje = LC_AppGiL();
            }
            LC_PutGi(ledig_linje,temp);
            ledig_linje ++;
         }

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
AR-931212
CH LC_POL_GetRef                        Hent referanser for flate fra GINFO
CD ==========================================================================
CD Formål:
CD Henter referanser fra GINFO til struktur.
CD
CD Parametre:
CD Type         Navn      I/U  Forklaring
CD -----------------------------------------------------------------------
CD LC_POLYGON  *pPolygon   I   Peker til adm. for polygonbeskrivelse
CD
CD
CD Bruk:
CD    short ngi;
CD    long nko;
CD    unsigned short info;
CD    LC_POLYGON Polygon;
CD    LC_POL_ELEMENT * pPE;
CD    LC_OY_ELEMENT * pOE;
CD
CD    LC_POL_InitPolygon(&Polygon);
CD
CD    LC_POL_GetRef(&Polygon);
CD
CD    . Omkretsen .
CD    for(pPE = Polygon.HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
CD       gnavn = LC_RxGr(&pPE->Bgr,LES_OPTIMALT,&ngi,&nko,&info);
CD       .
CD       Behandle ytre avgrensing            
CD       .
CD    }
CD
CD    . Øyer .
CD    for (pOE = Polygon.OyOA.pForsteOE; pOE != NULL; pOE = pOE->pNesteOE) {
CD       for (pPE = pOE->PO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
CD          gnavn = LC_RxGr(&pPE->Bgr,LES_OPTIMALT,&ngi,&nko,&info);
CD          .
CD          Behandle indre avgrensing (øy)           
CD          .
CD       }
CD    }
CD
CD    . Frigi allokerte kjeder .
CD    LC_POL_FrigiPolygon(&Polygon);
CD
CD ==========================================================================
*/
SK_EntPnt_FYBA void LC_POL_GetRef(LC_POLYGON *pPolygon)
{
   char *gp,ginfo[LC_MAX_SOSI_LINJE_LEN];
   long lSnr;
   LC_BGR Bgr;
   short ngi;
   long nko;
   unsigned short info;
   short sRetning;
   LC_POL_OMKR OyPO;
   short sGiLinNr = 2;
   short sOy = UT_FALSE;
   LC_BGR AktBgr = Sys.GrId;
   short sRefLin = UT_FALSE;   /* Viser om aktuel linje inneholder referanser */


   LC_POL_InitOmkrets(&OyPO);


   if (Sys.GrId.lNr != INGEN_GRUPPE) {            /* Aktuell gruppe OK */

      Bgr.pFil = Sys.GrId.pFil;

      /* Finn referanser */
      while (sGiLinNr <= Sys.pGrInfo->ngi) {
         gp = LX_GetGi(sGiLinNr);
         
         /* Handter referanselinjer */
         if ((sRefLin = LC_ErLinjeRefLin(gp,sRefLin)) == UT_TRUE) {
            UT_StrCopy(ginfo,gp,LC_MAX_SOSI_LINJE_LEN);
            gp = ginfo;
            while (*gp) {                  /* Tolk en linje */
               if (*gp == ':') {                              /* Tall */
                  gp++;
                  /* Husk retning */
                  if (*gp == '-') {
                     sRetning = LC_MOT_DIG;
                     gp++;
                  } else {
                     sRetning = LC_MED_DIG;
                  }
                  /* Hent serienummer og konverter til gruppenummer */
                  if (isdigit(*gp)) {
                     lSnr = strtol(gp,&gp,10);
                     /* Konverter til gruppenummer */
                     if ((Bgr.lNr = LI_GetSnr(Sys.GrId.pFil,lSnr)) != INGEN_GRUPPE) {
                        /* Legg gruppen inn i kjeden */
                        if (sOy == UT_TRUE) {
                           /* Referanse til flate, pakk ut denne */
                           if (LC_GetGrParaBgr(&Bgr,&ngi,&nko,&info) == L_FLATE) {
                              LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);
                              LC_POL_GetRefOmkrets(&OyPO);
                              LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);

                           } else {
                              LC_POL_LeggTilGruppeOmkrets(&OyPO,&Bgr,sRetning,lSnr);
                           }

                        } else {
                           LC_POL_LeggTilGruppeOmkrets(&(pPolygon->HovedPO),
                                                       &Bgr,sRetning,lSnr);
                        }

                     } else {
                        UT_FPRINTF(stderr,"Snr. %ld er referert i \"%s : %s\", finnes ikke!\n",lSnr,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                        Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                     }

                  } else {
                     //UT_FPRINTF(stderr,"Ulovlig referanse \"%s\" i \"%s : %s\"\n",ginfo,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                     //Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                     gp++;
                  }


               } else if (*gp == '(') {                     /* Start øy */

                  if (sOy == UT_FALSE) {
                     LC_POL_InitOmkrets(&OyPO);
                     sOy = UT_TRUE;

                  } else {
                     /* Øy i øy er ikke lovlig */
                     LC_Error(56,"(LC_POL_GetRef)",Sys.GrId.pFil->pszNavn);
                     UT_FPRINTF(stderr,"Øy i øy i gruppe \"%s : %s\"\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                     Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                  }
                  gp++;

               } else if (*gp == ')') {                     /* Slutt øy */

                  if (sOy == UT_TRUE) {
                     LC_POL_LeggTilOy(&(pPolygon->OyOA),&OyPO);
                     sOy = UT_FALSE;

                  } else {
                     /* Øy i øy er ikke lovlig */
                     LC_Error(56,"(LC_POL_GetRef)",Sys.GrId.pFil->pszNavn);
                     UT_FPRINTF(stderr,"Øy i øy i gruppe \"%s : %s\"\n",Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                     Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                  }
                  gp++;

               } else {                                    /* Ukjent tegn */
                  gp++;
               }
            }
         }

         sGiLinNr++;
      }
   }

   return;
}


/*
AR-931212
CH LC_POL_GetRefOmkrets               Hent referanser for omkretsen av flate
CD ==========================================================================
CD Formål:
CD Henter referanser fra GINFO til struktur.
CD Rutinen initierer strukturen pPO, men frigir ikke eventuellt gammelt innhold.
CD
CD
CD Parametre:
CD Type          Navn    I/U  Forklaring
CD -------------------------------------------------------------------------
CD LC_POL_OMKR  *pPO;     IU  Peker til kjede som beskriver omkretsen.
CD
CD Bruk:
CD    LC_POL_GetRefOmkrets(&OyPO);
CD ==========================================================================
*/
SK_EntPnt_FYBA void LC_POL_GetRefOmkrets(LC_POL_OMKR *pPO)
{
   char *gp,ginfo[LC_MAX_SOSI_LINJE_LEN];
   long lSnr;
   short sRetning;
   short sGiLinNr = 2;
   short sFerdig = UT_FALSE;
   LC_BGR Bgr = Sys.GrId;
   short sRefLin = UT_FALSE;   /* Viser om aktuel linje inneholder referanser */


   LC_POL_InitOmkrets(pPO);

   if (Sys.GrId.lNr != INGEN_GRUPPE  &&  Sys.pGrInfo->ngi > 0) {
      /* Finn referanser */
      while (sFerdig == UT_FALSE  &&  sGiLinNr <= Sys.pGrInfo->ngi) {
         gp = LX_GetGi(sGiLinNr);
         
         /* Handter referanselinjer */
         if ((sRefLin = LC_ErLinjeRefLin(gp,sRefLin)) == UT_TRUE) {
            UT_StrCopy(ginfo,gp,LC_MAX_SOSI_LINJE_LEN);
            gp = ginfo;
            while (sFerdig == UT_FALSE  &&  *gp) {  /* Tolk en linje */
               if (*gp == ':') {                              /* Tall */
                  gp++;
                  /* Husk retning */
                  if (*gp == '-') {
                     sRetning = LC_MOT_DIG;
                     gp++;
                  } else {
                     sRetning = LC_MED_DIG;
                  }
                  /* Hent serienummer og konverter til gruppenummer */
                  if (isdigit(*gp)) {
                     lSnr = strtol(gp,&gp,10);
                     /* Konverter til gruppenummer */
                     if ((Bgr.lNr = LI_GetSnr(Sys.GrId.pFil,lSnr)) != INGEN_GRUPPE) {
                        /* Legg gruppen inn i kjeden */
                        LC_POL_LeggTilGruppeOmkrets(pPO,&Bgr,sRetning,lSnr);

                     } else {
                        UT_FPRINTF(stderr,"Snr. %ld er referert i \"%s : %s\", finnes ikke!\n",lSnr,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                        Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                     }

                  } else {
                     UT_FPRINTF(stderr,"Ulovlig referanse \"%s\" i \"%s : %s\"\n",ginfo,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
                     Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
                  }

               /* Start øy */
               } else if (*gp == '(') {
                  sFerdig = UT_TRUE;
                  gp++;

               } else {                                    /* Ukjent tegn */
                  gp++;
               }
            }
         }

         sGiLinNr++;
      }
   }
}


/*
SJM-930928
CH LC_POL_TestBrukt              Testar om ei gruppe er brukt i polygonet
CD =======================================================================
CD Bruk:
CD LC_POL_TestBrukt(pPolygon,&Bgr);
CD
CD parametere:
CD Type        Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POLYGON *pPolygon  I     Peker til polygonbeskrivelse.
CD LC_BGR     *pBgr      I     Peikar til gruppe
CD short       status    R     Status UT_TRUE = gruppe er brukt i polygonet
CD                              Status UT_FALSE = gruppe er IKKJE brukt i polygonet
CD
CD Testar om ei gruppe er brukt i gitt polygon.
CD =======================================================================
*/
SK_EntPnt_FYBA short LC_POL_TestBrukt(LC_POLYGON *pPolygon,LC_BGR *pBgr)
{
   LC_POL_ELEMENT *pPE;
   LC_OY_ELEMENT *pOE;

   /* Sjekk omkretsen */
   for(pPE = pPolygon->HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
      if (memcmp(pBgr,&pPE->Bgr, sizeof(LC_BGR)) == 0) {
         return UT_TRUE;
      }
   }

   /* Sjekk øyene */
   for (pOE = pPolygon->OyOA.pForsteOE; pOE != NULL; pOE = pOE->pNesteOE) {
      for (pPE = pOE->PO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
         if (memcmp(pBgr,&pPE->Bgr, sizeof(LC_BGR)) == 0) {
            return UT_TRUE;
         }
      }
   }

   return UT_FALSE;
}


/*
AR:2009-03-04
CH LC_POL_PTst                                                   Polygontest
CD ==========================================================================
CD Formål:
CD Sjekker om gitt punkt ligger innenfor polygon angitt av pPolygon.
CD Forutsetter at pPolygon danner et lukket polygon.
CD Skifter ikke aktuell gruppe.
CD
CD Parametre:
CD Type    Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  a        i    Punkt som skal sjekkes
CD double  n        i
CD short   ist      r    status: UT_FALSE = punktet er utenfor flaten
CD                               UT_TRUE = punktet ligger inne på flaten
CD
CD Bruk:
CD .
==========================================================================
*/
SK_EntPnt_FYBA short LC_POL_PTst(LC_POLYGON *pPolygon,double a,double n)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_POL_ELEMENT * pPE;
   LC_OY_ELEMENT * pOE;
   short sAntSkjaer;
   LC_BGR Flate = Sys.GrId;      /* Husk gruppenummer for flaten */
   short inni = UT_FALSE;   /* Returverdi: 1 = inne på flaten, 0 = utenfor  */
   

   // Har ytre avgrensning? 
   if (pPolygon == NULL  ||  pPolygon->HovedPO.pForstePE == NULL)  return inni;  // ==> Avbryter, har ikke noen ytre avgrensning


   double dEnhet = pPolygon->HovedPO.pForstePE->Bgr.pFil->TransPar.dEnhet;

   // Pluss på et lite tillegg for å unngå treff på node
   a += dEnhet / 1000.0;
   n += dEnhet / 1000.0;

   // Inndata
   if (pPolygon) {
      // ----- Behandle ytre avgrensing  (Omkretsen)
      sAntSkjaer = 0;
      for(pPE = pPolygon->HovedPO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
         sAntSkjaer += LR_PTstGruppe(&pPE->Bgr,a,n);
      }
      // Sjekk om punktet er innenfor
      inni = ((sAntSkjaer % 2) == 1)?  1 : 0;
      
      // ----- Behandler indre avgrensing (øy)
      for (pOE = pPolygon->OyOA.pForsteOE;  inni && (pOE != NULL);  pOE = pOE->pNesteOE) {
         // Behandler en øy
         sAntSkjaer = 0;
         for (pPE = pOE->PO.pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
            sAntSkjaer += LR_PTstGruppe(&pPE->Bgr,a,n);
         }
         // Sjekk om punktet er inni øya
         inni = ((sAntSkjaer % 2) == 1)?  UT_FALSE : UT_TRUE;
      }
     
      // Les inn flaten igjen
      LC_RxGr(&Flate,LES_OPTIMALT,&ngi,&nko,&info);
   }

   return  inni;
}


/*
AR-931213
CH LC_POL_PTstOmkrets              Sjekk om punkt ligger inni polygonomkrets
CD ==========================================================================
CD Formål:
CD Sjekker om gitt punkt ligger innenfor yttergrensen for polygon angitt
CD av struktur.
CD Forutsetter at tabellen danner et lukket polygon
CD Skifter ikke aktuell gruppe.
CD
CD Parametre:
CD Type          Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_POL_OMKR  *pPO    I/U  Peker til beskrivelse av omkretsen
CD double        a      i    Punkt som skal sjekkes
CD double        n      i
CD short         ist    r    status: UT_FALSE = punktet er utenfor flaten
CD                                   UT_TRUE  = punktet ligger inne på flaten
CD
CD Bruk:
CD ist = LC_POL_PTstOmkrets(pPO,a,n);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_POL_PTstOmkrets(LC_POL_OMKR *pPO,double a,double n)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_POL_ELEMENT *pPE;
   short sAntSkjaer = 0;
   LC_BGR AktBgr = Sys.GrId;      /* Husk gruppenummer for aktuell gruppe */


   // Har ytre avgrensning? 
   if (pPO == NULL  ||  pPO->pForstePE == NULL)  return UT_FALSE;  // ==> Avbryter, har ikke noen ytre avgrensning


   double dEnhet = pPO->pForstePE->Bgr.pFil->TransPar.dEnhet;

   // Pluss på et lite tillegg for å unngå treff på node
   a += dEnhet / 1000.0;
   n += dEnhet / 1000.0;

   /*
    * Sjekk omkretsen ved å beregne antall skjæringer mellom omkretsen
    * og en linje fra "test-punktet" til "uendelig øst".
    */

   for (pPE = pPO->pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
      /* Beregn skjæringer med denne gruppen */
      sAntSkjaer += LR_PTstGruppe(&pPE->Bgr,a,n);
   }

   /* Les inn opprinnelig gruppe igjen */
   LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);

   /*
    * Sjekk om punktet er innenfor omkretsen.
    * (Inni hvis antall skjæringspunkt er oddetall.)
    */
   return  ((sAntSkjaer % 2) == 1)?  UT_TRUE : UT_FALSE;
}
 

/*
JAØ-20061130
CH LC_POL_OmkretsSkjaering        Finner antall skjæringer med polygonomkrets
CD ==========================================================================
CD Formål:
CD Sjekker om gitt punkt ligger innenfor yttergrensen for polygon angitt
CD av struktur. Egentlig kopi av LC_POL_PTstOmkrets, men returnerer antall 
CD skjæringer istedet for inni/utenfor. 
CD Forutsetter at tabellen danner et lukket polygon
CD Skifter ikke aktuell gruppe.
CD
CD Parametre:
CD Type          Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_POL_OMKR  *pPO    I/U  Peker til beskrivelse av omkretsen
CD double        a      i    Punkt som skal sjekkes
CD double        n      i
CD short         ist    r    Antall skjæringer med omkrets fra pkt til "uendelig" øst
CD
CD Bruk:
CD ist = LC_POL_PTstOmkrets(pPO,a,n);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_POL_OmkretsSkjaering(LC_POL_OMKR *pPO,double a,double n)
{
   short ngi;
   long nko;
   unsigned short info;
   LC_POL_ELEMENT *pPE;
   short sAntSkjaer = 0;
   LC_BGR AktBgr = Sys.GrId;      /* Husk gruppenummer for aktuell gruppe */


   // Har ytre avgrensning? 
   if (pPO == NULL  ||  pPO->pForstePE == NULL)  return 0;  // ==> Avbryter, har ikke noen ytre avgrensning
   

   double dEnhet = pPO->pForstePE->Bgr.pFil->TransPar.dEnhet;

   // Pluss på et lite tillegg for å unngå treff på node
   a += dEnhet / 1000.0;
   n += dEnhet / 1000.0;

   /*
    * Sjekk omkretsen ved å beregne antall skjæringer mellom omkretsen
    * og en linje fra "test-punktet" til "uendelig øst".
    */

   for (pPE = pPO->pForstePE; pPE != NULL; pPE = pPE->pNestePE) {
      /* Beregn skjæringer med denne gruppen */
      sAntSkjaer += LR_PTstGruppe(&pPE->Bgr,a,n);
   }
  
   /* Les inn opprinnelig gruppe igjen */
   LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);

   return  sAntSkjaer;
}


/*
AR-950421
CH LC_POL_Box                                  Henter omskreven boks
CD =======================================================================
CD Bruk:
CD LC_POL_Box(pPA,&nva,&nvn,&oha,&ohn);
CD
CD parametere:
CD Type          Navn     I/U    Forklaring
CD -----------------------------------------------------------------------
CD LC_POL_OMKR  *pPO       I     Peikar til polygonadministrasjonsblokka
CD double       *nva       U
CD double       *nvn       U
CD double       *oha       U
CD double       *ohn       U
CD
CD Henter omskriven boks for polygon.
CD =======================================================================
*/
SK_EntPnt_FYBA void LC_POL_Box(LC_POL_OMKR *pPO,double *nva,double *nvn, double *oha,double*ohn)
{
   LC_POL_ELEMENT *pPE;
   double na,nn,oa,on;
   /* Omskreven boks */
   double mina = (double)LONG_MAX;
   double minn = (double)LONG_MAX;
   double maxa = (double)LONG_MIN;
   double maxn = (double)LONG_MIN;

   for (pPE = pPO->pForstePE; pPE != NULL; pPE = pPE->pNestePE) {

      if (LC_GetGrWin(&pPE->Bgr,&na,&nn,&oa,&on) ) {
         if (na < mina)  mina = na;
         if (nn < minn)  minn = nn;
         if (oa > maxa)  maxa = oa;
         if (on > maxn)  maxn = on;
      }
   }

   *nva = mina;
   *nvn = minn;
   *oha = maxa;
   *ohn = maxn;
}


/*
AR-950421
CH LC_ErLinjeRefLin                  Sjekk om linje inneholder referanser
CD =======================================================================
CD Bruk:
CD sRefLin = LC_ErLinjeRefLin(gp,sRefLin);
CD
CD parametere:
CD Type    Navn        I/U  Forklaring
CD -----------------------------------------------------------------------
CD char   *pszGinfoLin  i   Peikar til GINFO-linje
CD short   sRefLin      i   Flagg som viser om forrige linje inneholdt referanser
CD short   sRefLin      r   Flagg som viser om aktuell linje inneholdt referanser
CD
CD Sjekk om linje er linje med referanser.
CD =======================================================================
*/
short LC_ErLinjeRefLin(char *pszSosiLin, short sRefLin)
{
   /* Sjekk om dette er referanselinje */
   if (strncmp(pszSosiLin,".. ",3) == 0) {
      return UT_TRUE;

   } else if (strncmp(pszSosiLin,"..REF ",6) == 0) {
      //if (sRefLin == UT_TRUE) {
      //   UT_FPRINTF(stderr,"Ulovlig SOSI-syntaks \"%s\" i gruppe \"%s : %s\"\n",pszSosiLin,Sys.GrId.pFil->pszNavn,LX_GetGi(1));
      //   Sys.GrId.pFil->usDataFeil |= LC_DATAFEIL_REF;
      //}
      return UT_TRUE;

   } else if (sRefLin == UT_TRUE) {
      /* Annet SOSI-navn */
      if (*pszSosiLin == '.') {
         return UT_FALSE;
      
      } else {
         return UT_TRUE;
      }

   } else {
      return UT_FALSE;
   }
}
