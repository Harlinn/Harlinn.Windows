/*
CH FYLH        AR-900503                                  BIBLIOTEK
CD =================================================================
CD
CD Eier.......: STATENS KARTVERK / FYSAK-prosjektet
CD Ansvarlig..: Georg Langerak / Andreas Røstad
CD
CD Rutiner for å handtere hodet på SOSI-filer når dette ligger
CD som ginfo i RB.
CD  ==============================================================
*/

#include "fyba.h"
#include "fybax.h"

#include <math.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>

#include <Windows.h>

/* Globale variabler */
extern LC_SYSTEMADM Sys;



/*
AR:2000-10-07
CH LC_PutTransEx                                 Legger inn ..TRANSPAR i hodet
CD ==========================================================================
CD Formål:
CD Legger inn innholdet under ..TRANSPAR i ginfo i aktuell gruppe.
CD OBS! Forutsetter at aktuell gruppe er et SOSI-filhode versjon 3.x.
CD
CD Må velge mellom KOORDSYS, TRANSSYS eller GEOSYS.
CD Kun en av disse kan benyttes i filhodet. 
CD KOORDSYS er den mest vanlige måte å definere referansesystem. 
CD 
CD GEOKOORD skal benyttes for GEOSYS og for TRANSSYS 
CD
CD Må velge mellom VERT-DATUM eller VERT-INT.
CD VERT-DATUM er den mest vanlige beskrivelsesmåten. 
CD
CD Følgende kompaktifisering brukes:
CD     ..TRANSPAR 
CD     ...KOORDSYS <SYSKODE> <DATUM> <PROJEK> 
CD     ...TRANSSYS <TILSYS> <KONSTA1> <KONSTB1> <KONSTA2> <KONSTB2> <KONSTC1> <KONSTC2> 
CD     ...GEOSYS <GEO-DATUM> <GEO-PROJ> <GEO-SONE> 
CD     ...GEOKOORD <GEOKOORD> 
CD     ...ORIGO-NØ <ORIGO-N> <ORIGO-Ø> 
CD     ...ENHET <ENHET> 
CD     ...ENHET-H <ENHET-H> 
CD     ...ENHET-D <ENHET-D> 
CD     ...VERT-DATUM <HØYDE-REF> <DYBDE-REF> <FRISEIL-REF> <HØYDE-TYPE> 
CD     ...VERT-INT <H-REF-INT> <D-REF-INT> <F-REF-INT> 
CD     ...VERT-DELTA <V-DELTA-MIN> <V-DELTA-MAX>
CD
CD
CD Parametre:
CD Type           Navn    I/U  Forklaring
CD --------------------------------------------------------------------------
CD unsigned short usMaske  i   Maske som styrer hvilke deler av TRANSPAR som brukt
CD                             Følgende konstanter er definert:       
CD                              LC_TR_KOORDSYS - Koordsys             
CD                              LC_TR_TRANSSYS - Transsys             
CD                              LC_TR_GEOSYS - Geosys                 
CD                              LC_TR_GEOKOORD - Geokoord             
CD                              LC_TR_ORIGO - Origo-nø                
CD                              LC_TR_ENHET - Enhet                   
CD                              LC_TR_ENHETH - Enhet-h                
CD                              LC_TR_ENHETD - Enhet-d                
CD                              LC_TR_VERTDATUM - Vert-datum          
CD                              LC_TR_VERTINT - Vert-int              
CD                              LC_TR_VERTDELTA - Vert-delta          
CD
CD LC_TRANSPAR *   pTrans   i   Peker til struktur med ..TRANSPAR informasjonen.
CD short          ngi      r   Antall GINFO-linjer etter oppdateringen.
CD
CD Bruk:
CD LC_TRANSPAR Trans;
CD unsigned short usMaske = LC_TR_KOORDSYS | LC_TR_ORIGO | LC_TR_ENHET;
CD Trans.sKoordsys = 32;
CD Trans.dOrigoAust = 0.0;
CD Trans.dOrigoNord = 0.0;
CD Trans.dEnhet = 1.0;
CD ngi = LC_PutTransEx(usMaske,&Trans);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_PutTransEx(unsigned short usMaske, LC_TRANSPAR * pTrans)
{
   short i,lin,ngi;
   long nko;
   unsigned short info;
   char *cp = NULL;
   char szGiLin[LC_MAX_SOSI_LINJE_LEN];


   /* Ingen aktuell gruppe */
   if (Sys.GrId.lNr == INGEN_GRUPPE) {
      LC_Error(49,"(LC_PutTrans)","");
      return Sys.pGrInfo->ngi;
   }

   /* Aktuell gruppe er ikke .HODE */
   if (Sys.pGrInfo->gnavn != L_HODE) { 
      LC_Error(94,"(LC_PutTrans)","");
      return Sys.pGrInfo->ngi;
   }


   /* ----- Fjerner gammel transpar ----- */
   LC_GetGrPara(&ngi,&nko,&info);
   lin=2;
   if (LC_GetGP("..TRANSPAR",&lin,ngi) != NULL) {      
      i = lin;
      do {
         i++;
         if (i <= ngi)  cp = LC_GetGi(i);
      } while ( i <= ngi  &&  cp[2] == '.' );
      /* i peker nå til første linje etter hele ..TRANSPAR med undernivåer */

      LC_DelGiL(lin,(short)(i-lin));
   }

   /* ----- Legger inn ny transpar ----- */
   LC_PutGi(LC_AppGiL(),"..TRANSPAR");

   /* Koordsys */
   if ((usMaske & LC_TR_KOORDSYS) != 0) {
      UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...KOORDSYS %hd %s %s",pTrans->sKoordsys,pTrans->szKoordsysDatum,pTrans->szKoordsysProjek);
      LC_PutGi(LC_AppGiL(),szGiLin);
   }

   /* Transsys */
   if ((usMaske & LC_TR_TRANSSYS) != 0) {
      UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...TRANSSYS %hd %f %f %f %f %f %f", pTrans->sTranssysTilsys,
              pTrans->dTranssysKonstA1, pTrans->dTranssysKonstB1,
              pTrans->dTranssysKonstA2, pTrans->dTranssysKonstB2,
              pTrans->dTranssysKonstC1, pTrans->dTranssysKonstC2);
      LC_PutGi(LC_AppGiL(),szGiLin);
   }

   /* Geosys */
   if ((usMaske & LC_TR_GEOSYS) != 0) {
      if (pTrans->sGeosysProj  != LC_TR_GEOSYS_INGEN_VERDI)
      {
         UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...GEOSYS %hd %hd %hd", pTrans->sGeosysDatum,
                 pTrans->sGeosysProj, pTrans->sGeosysSone);
      }
      else
      {
         UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...GEOSYS %hd", pTrans->sGeosysDatum);
      }
     
      LC_PutGi(LC_AppGiL(),szGiLin);
   }

   /* Geokoord */ 
   if ((usMaske & LC_TR_GEOKOORD) != 0) {
      UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...GEOKOORD %hd", pTrans->sGeoKoord);
      LC_PutGi(LC_AppGiL(),szGiLin);
   }

   /* Origo */
   if ((usMaske & LC_TR_ORIGO) != 0) {
      UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...ORIGO-NØ %.0f  %.0f", pTrans->Origo.dNord, pTrans->Origo.dAust);
      LC_PutGi(LC_AppGiL(),szGiLin);
   }

   /* Enhet */
   if ((usMaske & LC_TR_ENHET) != 0) {
      LC_PutGi(LC_AppGiL(),LB_FormaterEnhet(szGiLin,LC_MAX_SOSI_LINJE_LEN, "...ENHET", pTrans->dEnhet));
   }

   /* Enhet-h */
   if ((usMaske & LC_TR_ENHETH) != 0) {
      /*
      * Hvis enhet og enhet_h er like
      * skal det ikke legges inn ENHET-H
      */
      if (fabs(pTrans->dEnhet-pTrans->dEnhet_h) > 0.0000001) {
         LC_PutGi(LC_AppGiL(),LB_FormaterEnhet(szGiLin,LC_MAX_SOSI_LINJE_LEN,"...ENHET-H",pTrans->dEnhet_h));
      }
   }

   /* Enhet-d */
   if ((usMaske & LC_TR_ENHETD) != 0) {
      /*
      * Hvis enhet og enhet_d er like
      * skal det ikke legges inn ENHET-D
      */
      if (fabs(pTrans->dEnhet-pTrans->dEnhet_d) > 0.0000001) {
         LC_PutGi(LC_AppGiL(),LB_FormaterEnhet(szGiLin,LC_MAX_SOSI_LINJE_LEN,"...ENHET-D",pTrans->dEnhet_d));
      }
   }

   /* Vert-datum */
   if ((usMaske & LC_TR_VERTDATUM) != 0) {
      UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...VERT-DATUM %s %s %s %s", pTrans->szVertdatHref,
              pTrans->szVertdatDref, pTrans->szVertdatFref, pTrans->szVertdatHtyp);
      LC_PutGi(LC_AppGiL(),szGiLin);
   }
      
   /* Vert-int */
   if ((usMaske & LC_TR_VERTINT) != 0) {
      UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...VERT-INT %hd %hd %hd", pTrans->sVertintHref,
              pTrans->sVertintDref, pTrans->sVertintFref);
      LC_PutGi(LC_AppGiL(),szGiLin);
   }

   /* Vert-delta */
   if ((usMaske & LC_TR_VERTDELTA) != 0) {
      UT_SNPRINTF(szGiLin, LC_MAX_SOSI_LINJE_LEN, "...VERT-DELTA %hd %hd", pTrans->sVdeltaMin, pTrans->sVdeltaMax);
      LC_PutGi(LC_AppGiL(),szGiLin);
   }

   return Sys.pGrInfo->ngi;
}


/*
AR-910920
CH LC_PutTrans                                 Legger inn ..TRANSPAR i hodet
CD ==========================================================================
CD Formål:
CD Legger inn transformasjonsparametrene i ginfo i aktuell gruppe.
CD Forutsetter at aktuell gruppe er et SOSI-filhode versjon 3.x.
CD
CD OBS! Denne rutinen opprettholdes bare for bakoverkompatibilitet.
CD      For nye programmer bør LC_PutTransEx benyttes. LC_PutTransEx er
CD      kompatibel med nye versjoner av SOSI.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD short    koosys     i    Koordinatsystem
CD double   origo_a    i    Origo øst
CD double   origo_n    i    Origo nord
CD double   enhet      i    Enhet
CD double   enhet_h    i    Enhet-H
CD double   enhet_d    i    Enhet-D
CD short    ngi        r    Antall GINFO-linjer etter oppdateringen.
CD
CD Bruk:
CD     ngi = LC_PutTrans(koosys,origo_a,origo_n,enhet,enhet_h,enhet_d);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_PutTrans(short koosys,double origo_a,double origo_n,
                  double enhet,double enhet_h,double enhet_d)
{
   short i,ngi,linje_enhet;
   char c[80];

   if (Sys.GrId.lNr != INGEN_GRUPPE) {           /* Aktuell gruppe OK */
       if (Sys.pGrInfo->gnavn == L_HODE) {        /* Aktuell gruppe .HODE */
           UT_SNPRINTF(c,80,"%d",koosys);
           ngi = LC_PutGP("...KOORDSYS",c,&i);
           UT_SNPRINTF(c,80," %.0f  %.0f",origo_n,origo_a);
           ngi = LC_PutGP("...ORIGO-NØ",c,&i);
           linje_enhet = 2;              
           LC_GetGP("...ENHET",&linje_enhet,ngi);
           LC_PutGi(linje_enhet,LB_FormaterEnhet(c,80,"...ENHET",enhet));
        
           /*
            * Hvis enhet og enhet_h er like
            * skal det ikke legges inn ENHET-H,
            * eventuell gammel linje fjernes.
            */

           if (fabs(enhet-enhet_h) < 0.0000001) {
              i = 2;
              if (LC_GetGP("...ENHET-H",&i,ngi) != NULL) {
                 LC_DelGiL(i,1);
              }

           } else {
            
              i = 2;              
              if (LC_GetGP("...ENHET-H",&i,ngi) == NULL) {
                i = linje_enhet + 1;
                ngi = LC_InsGiL(i,1);         /* Ikke funnet, tildel ny linje */
              }
              LC_PutGi(i,LB_FormaterEnhet(c,80,"...ENHET-H",enhet_h));
           }

           /*
            * Hvis enhet og enhet_d er like
            * skal det ikke legges inn ENHET-D,
            * eventuell gammel linje fjernes.
            */
           if (fabs(enhet-enhet_d) < 0.000001) {
              i = 2;
              if (LC_GetGP("...ENHET-D",&i,ngi) != NULL) {
                 LC_DelGiL(i,1);
              }

           } else {
              i = 2;              
              if (LC_GetGP("...ENHET-D",&i,ngi) == NULL) {
                i = linje_enhet + 1;
                ngi = LC_InsGiL(i,1);         /* Ikke funnet, tildel ny linje */
             }
             LC_PutGi(i,LB_FormaterEnhet(c,80,"...ENHET-D",enhet_d));

           }

       } else{                              /* Gruppen er ikke filhode */
           LC_Error(94,"(LC_PutTrans)","");
       }

   } else{                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_PutTrans)","");
   }

   return Sys.pGrInfo->ngi;
}


/*
AR:2000-10-07
CH LC_GetTransEx                                 Henter ..TRANSPAR fra hodet
CD ==========================================================================
CD Formål:
CD Henter ut innholdet under ..TRANSPAR fra ginfo i aktuell gruppe.
CD OBS! Forutsetter at aktuell gruppe er et SOSI-filhode.
CD
CD Må velge mellom KOORDSYS, TRANSSYS eller GEOSYS. Kun en av disse kan benyttes i filhodet. 
CD KOORDSYS er den mest vanlige måte å definere referansesystem. 
CD 
CD GEOKOORD skal benyttes for GEOSYS og for TRANSSYS 
CD
CD Må velge mellom VERT-DATUM eller VERT-INT.
CD VERT-DATUM er den mest vanlige beskrivelsesmåten. 
CD

CD Parametre:
CD Type            Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD unsigned short *pusMaske  iu   [Inn] Styrer hvilke deler av TRANSPAR som skal hentes
CD                                [Ut]  Viser hvilke deler av TRANSPAR som er funnet/hentet.
CD                                Følgende konstanter er definert:
CD                                  LC_TR_ALLT - Alle deler av ..TRANSPAR hentes
CD                                  LC_TR_KOORDSYS - Koordsys
CD                                  LC_TR_TRANSSYS - Transsys
CD                                  LC_TR_GEOSYS - Geosys
CD                                  LC_TR_GEOKOORD - Geokoord
CD                                  LC_TR_ORIGO - Origo-nø
CD                                  LC_TR_ENHET - Enhet
CD                                  LC_TR_ENHETH - Enhet-h
CD                                  LC_TR_ENHETD - Enhet-d
CD                                  LC_TR_VERTDATUM - Vert-datum
CD                                  LC_TR_VERTINT - Vert-int
CD                                  LC_TR_VERTDELTA - Vert-delta
CD
CD LC_TRANSPAR *    pTrans    iu   Peker til struktur som skal motta ..TRANSPAR informasjonen.
CD short           sStatus   r    Status: UT_TRUE=OK, UT_FALSE=feil (ikke funnet).
CD
CD Bruk:
CD unsigned short usMaske = LC_TR_ALLT;
CD LC_TRANSPAR Trans;
CD ist = LC_GetTransEx(&usMaske,&Trans);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetTransEx(unsigned short *pusMaske, LC_TRANSPAR * pTrans)
{
   short lin,ngi,itxi;
   long nko;
   unsigned short us;
   char *cp;
   short ist = UT_TRUE;
   unsigned short usMaskeInn = *pusMaske;


   /* Nullstiller pTrans */
   memset(pTrans,0,sizeof(LC_TRANSPAR));

   /* Nullstiller masken */
   *pusMaske = 0;

   LC_GetGrPara(&ngi,&nko,&us);


   /* ----- Div. kontroller ----- */

   /* Ingen aktuell gruppe */
   if (Sys.GrId.lNr == INGEN_GRUPPE) {
      LC_Error(49,"(LC_GetTransEx)","");
      return  UT_FALSE;
   }
   /* Gruppen er ikke filhode */
   if (Sys.pGrInfo->gnavn != L_HODE) {        
      LC_Error(94,"(LC_GetTransEx)","");
      return  UT_FALSE;
   }
   /* Transpar */
   lin=2;
   if (LC_GetGP("..TRANSPAR",&lin,ngi) == NULL) {      
      LC_Error(14,"(LC_GetTransEx)","");
      return  UT_FALSE;
   }


   /* ----- Henter verdier ----- */

   /* Koordsys */
   if ((usMaskeInn & LC_TR_KOORDSYS) != 0) {
      lin = 2;
      cp = LC_GetGP("...KOORDSYS",&lin,ngi);
      if (cp == NULL) {
          lin=2;
          cp = LC_GetGP("..KOORDSYS",&lin,ngi);
      }
      if (cp != NULL) {
         *pusMaske |= LC_TR_KOORDSYS;
         UT_StrShort(cp,0,&itxi,&pTrans->sKoordsys);
         UT_StrToken(cp,itxi,&itxi,36,pTrans->szKoordsysDatum);
         UT_StrToken(cp,itxi,&itxi,36,pTrans->szKoordsysProjek);
      }
   }

   /* Transsys */
   if ((usMaskeInn & LC_TR_TRANSSYS) != 0) {
      lin = 2;
      if ((cp = LC_GetGP("...TRANSSYS",&lin,ngi)) != NULL) {
         *pusMaske |= LC_TR_TRANSSYS;
         UT_StrShort(cp,0,&itxi,&pTrans->sTranssysTilsys);
         UT_StrDbl(cp,itxi,&itxi,'.',&pTrans->dTranssysKonstA1);
         UT_StrDbl(cp,itxi,&itxi,'.',&pTrans->dTranssysKonstB1);
         UT_StrDbl(cp,itxi,&itxi,'.',&pTrans->dTranssysKonstA2);
         UT_StrDbl(cp,itxi,&itxi,'.',&pTrans->dTranssysKonstB2);
         UT_StrDbl(cp,itxi,&itxi,'.',&pTrans->dTranssysKonstC1);
         UT_StrDbl(cp,itxi,&itxi,'.',&pTrans->dTranssysKonstC2);
      }
   }

   /* Geosys */
   if ((usMaskeInn & LC_TR_GEOSYS) != 0) {
      lin = 2;
      if ((cp = LC_GetGP("...GEOSYS",&lin,ngi)) != NULL) {
         *pusMaske |= LC_TR_GEOSYS;
         UT_StrShort(cp,0,&itxi,&pTrans->sGeosysDatum);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sGeosysProj);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sGeosysSone);
      }
   }

   /* Geokoord */ 
   if ((usMaskeInn & LC_TR_GEOKOORD) != 0) {
      lin = 2;
      if ((cp = LC_GetGP("...GEOKOORD",&lin,ngi)) != NULL) {
         *pusMaske |= LC_TR_GEOKOORD;
         UT_StrShort(cp,0,&itxi,&pTrans->sGeoKoord);
      }
   }

   /* Origo */
   if ((usMaskeInn & LC_TR_ORIGO) != 0) {
      //pTrans->dOrigoAust = 0.0;                           
      //pTrans->dOrigoNord = 0.0;                           
      lin = 2;
      if ((cp = LC_GetGP("...ORIGO-NØ",&lin,ngi)) != NULL) {
         *pusMaske |= LC_TR_ORIGO;
         UT_StrDbl(cp,0,&itxi,'.',&pTrans->Origo.dNord);
         UT_StrDbl(cp,itxi,&itxi,'.',&pTrans->Origo.dAust);
      }
   }

   /* Enhet */
   if ((usMaskeInn & LC_TR_ENHET) != 0) {
      lin = 2;
      if ((cp = LC_GetGP("...ENHET",&lin,ngi)) != NULL) {
         *pusMaske |= LC_TR_ENHET;
         pTrans->dEnhet = strtod(cp,&cp);
      }
   }

   /* Enhet-h */
   if ((usMaskeInn & LC_TR_ENHETH) != 0) {
      lin=2;
      if ((cp = LC_GetGP("...ENHET-H",&lin,ngi)) == NULL) {
        pTrans->dEnhet_h = pTrans->dEnhet;
      } else {
        *pusMaske |= LC_TR_ENHETH;
        pTrans->dEnhet_h = strtod(cp,&cp);
      }
   }

   /* Enhet-d */
   if ((usMaskeInn & LC_TR_ENHETD) != 0) {
      lin=2;
      if ((cp = LC_GetGP("...ENHET-D",&lin,ngi)) == NULL) {
        pTrans->dEnhet_d = pTrans->dEnhet;
      } else {
        *pusMaske |= LC_TR_ENHETD;
        pTrans->dEnhet_d = strtod(cp,&cp);
      }
   }

   /* Vert-datum */
   if ((usMaskeInn & LC_TR_VERTDATUM) != 0) {
      lin = 2;
      if ((cp = LC_GetGP("...VERT-DATUM",&lin,ngi)) != NULL) {
         *pusMaske |= LC_TR_VERTDATUM;
         UT_StrToken(cp,0,&itxi,7,pTrans->szVertdatHref);
         UT_StrToken(cp,itxi,&itxi,6,pTrans->szVertdatDref);
         UT_StrToken(cp,itxi,&itxi,6,pTrans->szVertdatFref);
         UT_StrToken(cp,itxi,&itxi,2,pTrans->szVertdatHtyp);
      }
   }
   
   /* Vert-int */
   if ((usMaskeInn & LC_TR_VERTINT) != 0) {
      lin = 2;
      if ((cp = LC_GetGP("...VERT-INT",&lin,ngi)) != NULL) {
         *pusMaske |= LC_TR_VERTINT;
         UT_StrShort(cp,0,&itxi,&pTrans->sVertintHref);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sVertintDref);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sVertintFref);
      }
   }

   /* Vert-delta */
   if ((usMaskeInn & LC_TR_VERTDELTA) != 0) {
      lin = 2;
      if ((cp = LC_GetGP("...VERT-DELTA",&lin,ngi)) != NULL) {
         *pusMaske |= LC_TR_VERTDELTA;
         UT_StrShort(cp,0,&itxi,&pTrans->sVdeltaMin);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sVdeltaMax);
      }
   }


   /* ----- Div. sluttkontroll ----- */

   /* Kontroller at det er funnet Koordsys, Transsys eller Geosys */
   if ((usMaskeInn & LC_TR_KOORDSYS) != 0  ||
       (usMaskeInn & LC_TR_TRANSSYS) != 0  ||
       (usMaskeInn & LC_TR_GEOSYS) != 0      ) {
      if ((*pusMaske & LC_TR_KOORDSYS) == 0  &&
          (*pusMaske & LC_TR_TRANSSYS) == 0  &&
          (*pusMaske & LC_TR_GEOSYS) == 0  ) {
         /* Ikke noe koordinatsystem funnet */
         LC_Error(15,"(LC_GetTransEx)","");
         ist = UT_FALSE;
      }
   }

   /* Kontroller at det er funnet Origo */
   if ((usMaskeInn & LC_TR_ORIGO) != 0  &&  
       (*pusMaske & LC_TR_ORIGO) == 0  ) {
      /* Origo mangler */
      LC_Error(16,"(LC_GetTransEx)","");
      ist = UT_FALSE;
   }

   /* Kontroller at det er funnet Enhet */
   if ((usMaskeInn & LC_TR_ENHET) != 0  &&  
       (*pusMaske & LC_TR_ENHET) == 0 ) {
      /* Enhet mangler */
      LC_Error(17,"(LC_GetTransEx)","");
      ist = UT_FALSE;
   }

   return ist;
}


/*
GL-880427
AR-910920
CH LC_GetTrans                                     Finner ..TRANSPAR i hodet
CD ==========================================================================
CD Formål:
CD Henter ut transformasjonsparametrene fra ginfo i aktuell gruppe.
CD Forutsetter at aktuell gruppe er et SOSI-filhode.
CD
CD OBS! Denne rutinen opprettholdes bare for bakoverkompatibilitet.
CD      For nye programmer bør LC_GetTransEx benyttes. LC_GetTransEx er
CD      kompatibel med nye versjoner av SOSI.
CD
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD short   *koosys     u    Koordinatsystem
CD double  *origo_a    u    Origo øst
CD double  *origo_n    u    Origo nord
CD double  *enhet      u    Enhet
CD double  *enhet_h    u    ...ENHET-H
CD double  *enhet_d    u    ...ENHET-D
CD short    ist        r    status: UT_TRUE=OK, UT_FALSE=feil (navn er ikke funnet)
CD
CD Bruk:
CD     ist = LC_GetTrans(&koosys,&origo_a,&origo_n,&enhet,&enhet_h,&enhet_d);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetTrans(short *koosys,double *origo_a,double *origo_n,double *enhet,
					 double *enhet_h,double *enhet_d)
{

   short lin,ngi;
   long nko;
   unsigned short us;
   char *cp;
   short ist = UT_TRUE;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {           /* Aktuell gruppe OK */
       if (Sys.pGrInfo->gnavn == L_HODE) {        /* Aktuell gruppe .HODE */
           LC_GetGrPara(&ngi,&nko,&us);

           lin=2;
           if (LC_GetGP("..TRANSPAR",&lin,ngi) == NULL) {      /* Transpar */
               LC_Error(14,"(LC_GetTrans)","");
               ist = UT_FALSE;
           } else{
               *koosys=0;                                      /* Koordsys */
               lin=2;
               cp = LC_GetGP("...KOORDSYS",&lin,ngi);
               if (cp == NULL){
                   lin=2;
                   cp = LC_GetGP("..KOORDSYS",&lin,ngi);
               }
               if (cp == NULL){
                   LC_Error(15,"(LC_GetTrans)","");
                   ist = UT_FALSE;
               } else{
                   *koosys = atoi(cp);
                   *origo_a = 0.0;                            /* Origo */
                   *origo_n = 0.0;
                   lin = 2;
                   cp = LC_GetGP("...ORIGO-NØ",&lin,ngi);
                   if (cp == NULL) {
                       LC_Error(16,"(LC_GetTrans)","");
                       ist = UT_FALSE;
                   } else{
                       *origo_n=strtod(cp,&cp);
                       *origo_a=strtod(cp,&cp);

                       *enhet  = 1.0;                         /* Enhet */
                       lin = 2;
                       cp = LC_GetGP("...ENHET",&lin,ngi);
                       if (cp == NULL){
                           LC_Error(17,"(LC_GetTrans)","");
                           ist = UT_FALSE;
                       } else{
                           *enhet  = strtod(cp,&cp);
                       }
                       lin=2;
                       cp = LC_GetGP("...ENHET-H",&lin,ngi);
                       if (cp == NULL){
                          *enhet_h = *enhet;
                       } else {
                          *enhet_h = strtod(cp,&cp);
                       }
                       lin=2;
                       cp = LC_GetGP("...ENHET-D",&lin,ngi);
                       if (cp == NULL){
                          *enhet_d = *enhet;
                       } else{
                          *enhet_d = strtod(cp,&cp);
                       }
                   }
               }
           }

       } else{                              /* Gruppen er ikke filhode */
           LC_Error(94,"(LC_GetTrans)","");
           ist = UT_FALSE;
       }

   } else{                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_GetTrans)","");
       ist = UT_FALSE;
   }

   return ist;
}

/*
AR-920401
CH LC_GetTegnsett                                            Finner tegnsett
CD ==========================================================================
CD Formål:
CD Finne tegnsett i ginfo i aktuell gruppe.
CD OBS! Forutsetter at aktuell gruppe er et SOSI-filhode.
CD
CD Parametre:
CD Type    Navn       I/U  Forklaring
CD --------------------------------------------------------------------------
CD short  *psTegnsett  u   Tegnsett, konstanter definert:
CD                            TS_DOSN8   = DOS norsk 8-bits(standardverdi)
CD                            TS_ND7     = Norsk Data 7-bits
CD                            TS_ISO8859 = ISO8859-10 norsk/samisk
CD                            TS_DECM8   = DEC multinasjonal 8-bits
CD                            TS_DECN7   = DEC norsk 7-bits
CD short   sStatus     r   Status: UT_TRUE  = Funnet
CD                                  UT_FALSE = Ikke funnet
CD
CD Bruk:
CD      sStatus = LC_GetTegnsett(&sTegnsett);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetTegnsett(short *psTegnsett)
{
   short lin,ngi;
   long nko;
   unsigned short us;
   char *cp;
   short ist = UT_FALSE;

   *psTegnsett = TS_DOSN8;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {           /* Aktuell gruppe OK */
      if (Sys.pGrInfo->gnavn == L_HODE) {        /* Aktuell gruppe .HODE */
         LC_GetGrPara(&ngi,&nko,&us);
         lin=2;
         if ((cp = LC_GetGP("..TEGNSETT",&lin,ngi)) != NULL) {  /* Tegnsett */
            ist = UT_TRUE;
            UT_StrUpper(cp);
            if (strcmp(cp,"ISO8859-10") == 0) {
               *psTegnsett = TS_ISO8859;

            } else if (strcmp(cp,"ISO8859-1") == 0) {
               *psTegnsett = TS_ISO8859;

            } else if (strcmp(cp,"ANSI") == 0) {
               *psTegnsett = TS_ISO8859;

            } else if (strcmp(cp,"ND7") == 0) {
               *psTegnsett = TS_ND7;

            } else if (strcmp(cp,"DECN7") == 0) {
               *psTegnsett = TS_DECN7;

            } else if (strcmp(cp,"DECM8") == 0) {
               *psTegnsett = TS_DECM8;
            }
         }

      } else {                              /* Gruppen er ikke filhode */
         LC_Error(94,"(LC_GetTegnsett)","");
         ist = UT_FALSE;
      }

   } else {                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_GetTegnsett)","");
       ist = UT_FALSE;
   }

   return ist;
}


/*
AR-920401
CH LH_GetNgisLag                                           Finner NGIS-LAG
CD ==========================================================================
CD Formål:
CD Finne NGIS-LAG i ginfo i aktuell gruppe.
CD OBS! Forutsetter at aktuell gruppe er et SOSI-filhode.
CD
CD Parametre:
CD Type   Navn        I/U  Forklaring
CD --------------------------------------------------------------------------
CD char*  pszNgisLag   r   NGIS-lag. 
CD                           Tom streng = ..NGIS-LAG er ikke funnet eller parameter mangler
CD                           ..NGIS-LAG 0 = Bare leseaksess
CD
CD Bruk:
CD      pszNgisLag = LH_GetNgisLag();
CD ==========================================================================
*/
char* LH_GetNgisLag(void)
{
    static char emptyStr[] = {'\x0'};
   char *cp;
   short lin = 2;


   if (Sys.GrId.lNr != INGEN_GRUPPE) {           /* Aktuell gruppe OK */
      if (Sys.pGrInfo->gnavn == L_HODE) {        /* Aktuell gruppe .HODE */
         if ((cp = LC_GetGP("..NGIS-LAG",&lin,Sys.pGrInfo->ngi)) != NULL) {
            return cp; 
         } else {
            return  emptyStr;
         }

      } else {                              /* Gruppen er ikke filhode */
         LC_Error(94,"(LH_GetNgisLag)","");
      }

   } else {                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LH_GetNgisLag)","");
   }

   return  emptyStr;
}


/*
AR-910920
CH LC_PutOmr                                     Legger inn ..OMRÅDE i hodet
CD ==========================================================================
CD Formål:
CD Legger inn område i ginfo i aktuell gruppe.
CD Hvis område ikke har noen utstrekning justeres
CD dette med 1 meter i hver retning. 
CD OBS! Forutsetter at aktuell gruppe er et SOSI-filhode av ny type.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD double   nv_a       i    Område
CD double   nv_n       i
CD double   oh_a       i
CD double   oh_n       i
CD short    ist        r    status: UT_TRUE=OK, UT_FALSE=feil
CD
CD Bruk:
CD     ist = LC_PutOmr(nv_a,nv_n,oh_a,oh_n);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_PutOmr(double nv_a,double nv_n,double oh_a,double oh_n)
{
   short i;
   char c[80];
   short ist = UT_FALSE;
   double dNV_N, dNV_A, dOH_A, dOH_N;


   if (Sys.GrId.lNr != INGEN_GRUPPE) {           /* Aktuell gruppe OK */
       if (Sys.pGrInfo->gnavn == L_HODE) {        /* Aktuell gruppe .HODE */

           //UT_SNPRINTF(c,80," %ld     %ld",UT_RoundDL(floor(nv_n)),UT_RoundDL(floor(nv_a)));
           dNV_N = UT_RoundDD(floor(nv_n));
           dNV_A = UT_RoundDD(floor(nv_a));
 
           dOH_N = UT_RoundDD(ceil(oh_n));
           dOH_A = UT_RoundDD(ceil(oh_a));

           // Hvis nødvendig justeres område
           if (fabs(dOH_N-dNV_N) < 0.00000001) {
               dNV_N -= 1.0;
               dOH_N += 1.0;
           }
           if (fabs(dOH_A-dOH_A) < 0.00000001) {
               dNV_A -= 1.0;
               dOH_A += 1.0;
           }

           UT_SNPRINTF( c,80, " %.0f  %.0f", dNV_N, dNV_A );
           if (LC_PutGP("...MIN-NØ",c,&i)) {

               UT_SNPRINTF( c, 80, " %.0f  %.0f", dOH_N, dOH_A );
               if (LC_PutGP("...MAX-NØ",c,&i)){
                   ist = UT_TRUE;
               }
           }

       } else{                              /* Gruppen er ikke filhode */
           LC_Error(94,"(LC_PutOmr)","");
       }

   } else{                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_PutOmr)","");
   }

   return ist;
}


/*
AR-910920
CH LC_GetOmr                                         Finner ..OMRÅDE i hodet
CD ==========================================================================
CD Formål:
CD Henter ut område fra ginfo i aktuell gruppe.
CD OBS! Forutsetter at aktuell gruppe er et SOSI-filhode.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD double  *nv_a       u    Område
CD double  *nv_n       u
CD double  *oh_a       u
CD double  *oh_n       u
CD short    ist        r    status: UT_TRUE=OK, UT_FALSE=feil (navn er ikke funnet)
CD
CD Bruk:
CD     ist = LC_GetOmr(&nv_a,&nv_n,&oh_a,&oh_n);
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetOmr(double *nv_a,double *nv_n,double *oh_a,double *oh_n)
{
   short lin,i,ngi;
   long nko;
   unsigned short info;
   char *cp;
   short ist = UT_TRUE;

   if (Sys.GrId.lNr != INGEN_GRUPPE) {           /* Aktuell gruppe OK */
       if (Sys.pGrInfo->gnavn == L_HODE) {        /* Aktuell gruppe .HODE */
           LC_GetGrPara(&ngi,&nko,&info);
           lin=2;
           if (LC_GetGP("..OMRÅDE",&lin,ngi) == NULL) { 
               LC_Error(7,"(LC_GetOmr)","");
               *nv_n = -9999999.0;
               *nv_a = -9999999.0;
               *oh_n =  9999999.0;
               *oh_a =  9999999.0;
               ist = UT_FALSE;
           } else {
               /* Min-NØ */
               i = lin;
               cp = LC_GetGP("...MIN-NØ",&i,ngi);
               if (cp == NULL){
                  LC_Error(8,"(LC_GetOmr)","");
                  ist = UT_FALSE;
                  *nv_n = -9999999.0;
                  *nv_a = -9999999.0;
               } else{
                   *nv_n = strtod(cp,&cp);
                   *nv_a = strtod(cp,&cp);
                   /* Max-NØ */
                   i = lin;
                   cp = LC_GetGP("...MAX-NØ",&i,ngi);
                   if (cp == NULL){
                      LC_Error(9,"(LC_GetOmr)","");
                      ist = UT_FALSE;
                      *oh_n = 9999999.0;
                      *oh_a = 9999999.0;

                   } else{
                      *oh_n = strtod(cp,&cp);
                      *oh_a = strtod(cp,&cp);
                   }
               }
           }

       } else{                              /* Gruppen er ikke filhode */
           LC_Error(94,"(LC_GetOmr)","");
           ist = UT_FALSE;
       }

   } else{                              /* Ingen aktuell gruppe */
       LC_Error(49,"(LC_GetOmr)","");
       ist = UT_FALSE;
   }

   return ist;
}


/*
AR-910920
CH LC_NyttHode                                               Lager nytt hode
CD ==========================================================================
CD Formål:
CD Legger inn et standard SOSI-filhode i ginfo i aktuell gruppe.
CD
CD Parametre:
CD     ingen
CD
CD Bruk:
CD     LC_NyttHode();
CD ==========================================================================
*/
SK_EntPnt_FYBA void LC_NyttHode(void)
{
   short ngi;
   long nko;
   unsigned short us;
   char szTx[100];

   if (Sys.GrId.lNr != INGEN_GRUPPE) {           /* Aktuell gruppe OK */
                                           /* Tildel plass */
       LC_GetGrPara(&ngi,&nko,&us);
       if (ngi < 10){
           LC_InsGiL((short)(ngi+1),(short)(10-ngi));
       } else if (ngi > 10){
           LC_DelGiL(11,(short)(ngi-10));
       }

       Sys.pGrInfo->gnavn = L_HODE;       /* Aktuell gruppe .HODE */

                                           /* Generer nytt hode */
       LC_PutGi(1,".HODE");
       LC_PutGi(2,"..TEGNSETT ISO8859-10");
       LC_PutGi(3,"..TRANSPAR");
       LC_PutGi(4,"...KOORDSYS 0");
       LC_PutGi(5,"...ORIGO-NØ  0  0");
       LC_PutGi(6,"...ENHET 0.01");
       LC_PutGi(7,"..OMRÅDE");
       LC_PutGi(8,"...MIN-NØ   -99999   -99999");
       LC_PutGi(9,"...MAX-NØ  1999999  1999999");

       //LC_PutGi(10,"..SOSI-VERSJON  3.0");
       UT_SNPRINTF(szTx,100,"..SOSI-VERSJON %.2f",((double)FYBA_SOSI_VERSJON)/100.0);
       LC_PutGi(10,szTx);

       LC_PutSn(0L);          /* Standard serienummer 0 for hodet*/
   }
}


/*
AR-910920
CH LC_TestHode                                             Tester SOSI-hodet
CD ==========================================================================
CD Formål:
CD Sjekker at ginfo i aktuell gruppe er et lovlig SOSI-filhode.
CD
CD Parametre:
CD  Type    Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD  short   ist      r    status: UT_TRUE=OK, UT_FALSE=feil
CD
CD Bruk:
CD     ist = LC_TestHode();
CD ==========================================================================
*/
SK_EntPnt_FYBA short LC_TestHode(void)
{
   double d;
   short ist;
   unsigned short usMaske = LC_TR_ALLT;
   LC_TRANSPAR Trans;


   ist = LC_GetTransEx(&usMaske,&Trans);

   if (ist == UT_TRUE) {
       ist =  LC_GetOmr(&d,&d,&d,&d);
   }

   return ist;
}

