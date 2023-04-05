/*
AR-920214
CH FYHO                                       "Direkte" hoderutiner
CD =================================================================
CD
CD Eier.......: STATENS KARTVERK / FYSAK-prosjektet
CD Ansvarlig..: Georg Langerak / Andreas Røstad
CD
CD Rutiner for å handtere hodet på SOSI-filer direkte på filen.
CD  ==============================================================
*/

#include "fyba.h"
#include "fybax.h"

#include <math.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
              
#include <Windows.h>


/* --- Globale strukturer ---------------------- */
extern LC_SYSTEMADM Sys;

extern char retur_str[LC_MAX_SOSI_LINJE_LEN];     /* Returstreng */

// ----- Lokale rutiner -----
static short ho_TestFyllKommentar(const char *pszTx);

/*
AR:2000-10-07
CH HO_GetTransEx                                       Finner .TRANSPAR i hodet
CD =============================================================================
CD Formål:
CD Henter ut innholdet under ..TRANSPAR fra fra filhodet.
CD
CD Parametre:
CD Type            Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD char           *pszFil     i   Fullstendig filnavn
CD unsigned short *pusMaske  iu   [Inn] Styrer hvilke deler av TRANSPAR som skal hentes
CD                                [Ut] Viser hvilke deler av TRANSPAR som er funnet/hentet.
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
CD ist = HO_GetTransEx("Test.sos",&usMaske,&Trans);
CD ==========================================================================
*/
SK_EntPnt_FYBA short HO_GetTransEx(const char *pszFil,unsigned short *pusMaske, LC_TRANSPAR * pTrans)
{
   short sStatus;
   FILE * pFil;


   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"SOS",UT_READ,UT_OLD,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Hent verdier */
      sStatus = ho_GetTransEx(pFil,pusMaske,pTrans);
      fclose (pFil);

	/* Åpningsfeil på kladdefilen */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_GetTransEx)",err().tx);
      memset(pTrans,0,sizeof(LC_TRANSPAR));
      *pusMaske = 0;
      sStatus = UT_FALSE;
   }

   return sStatus;
}


/*
AR:2000-10-07
CH ho_GetTransEx                                         Finner .TRANSPAR i hodet
CD =============================================================================
CD Henter ut innholdet under ..TRANSPAR fra fra filhodet.
CD
CD Parametre:
CD Type            Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD FILE           *pFil       i   Filpeker til sosi-fil.
CD unsigned short *pusMaske  iu   [Inn] Styrer hvilke deler av TRANSPAR som skal hentes
CD                                [Ut] Viser hvilke deler av TRANSPAR som er funnet/hentet.
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
CD ist = ho_GetTransEx(pFil,&usMaske,&Trans);
   =============================================================================
*/
short ho_GetTransEx(FILE *pFil,unsigned short *pusMaske, LC_TRANSPAR * pTrans)
{
   short lin,itxi;
   char *cp;
   short ist = UT_TRUE;
   unsigned short usMaskeInn = *pusMaske;


   /* Nullstiller pTrans */
   memset(pTrans,0,sizeof(LC_TRANSPAR));

   /* Nullstiller masken */
   *pusMaske = 0;

   /* Sjekk hvilket tegnsett som skal brukes */
	ho_GetTegnsett(pFil,&Sys.BufAdm.sTegnsett);

   /* ----- Div. kontroller ----- */
   /* Transpar */
   lin=2;
   if ( ! ho_GetVal(pFil,"..TRANSPAR",&lin)) {
       LC_Error(14," (HO_GetTrans) "," ");
       return UT_FALSE;
   }

   /* ----- Henter verdier ----- */

   /* Koordsys */
   if ((usMaskeInn & LC_TR_KOORDSYS) != 0) {
      lin = 2;
      cp = ho_GetVal(pFil,"...KOORDSYS",&lin);
      if (cp == NULL) {
         lin=2;
         ho_GetVal(pFil,"..KOORDSYS",&lin);
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
      if ((cp = ho_GetVal(pFil,"...TRANSSYS",&lin)) != NULL) {
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
      if ((cp = ho_GetVal(pFil,"...GEOSYS",&lin)) != NULL) {
         *pusMaske |= LC_TR_GEOSYS;
         UT_StrShort(cp,0,&itxi,&pTrans->sGeosysDatum);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sGeosysProj);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sGeosysSone);
      }
   }

   /* Geokoord */ 
   if ((usMaskeInn & LC_TR_GEOKOORD) != 0) {
      lin = 2;
      if ((cp = ho_GetVal(pFil,"...GEOKOORD",&lin)) != NULL) {
         *pusMaske |= LC_TR_GEOKOORD;
         UT_StrShort(cp,0,&itxi,&pTrans->sGeoKoord);
      }
   }

   /* Origo */
   if ((usMaskeInn & LC_TR_ORIGO) != 0) {
      lin = 2;
      if ((cp = ho_GetVal(pFil,"...ORIGO-NØ",&lin)) != NULL) {
         *pusMaske |= LC_TR_ORIGO;
         UT_StrDbl(cp,0,&itxi,'.',&pTrans->Origo.dNord);
         UT_StrDbl(cp,itxi,&itxi,'.',&pTrans->Origo.dAust);
      }
   }

   /* Enhet */
   if ((usMaskeInn & LC_TR_ENHET) != 0) {
      lin = 2;
      if ((cp = ho_GetVal(pFil,"...ENHET",&lin)) != NULL) {
         *pusMaske |= LC_TR_ENHET;
         pTrans->dEnhet = strtod(cp,&cp);
      }
   }

   /* Enhet-h */
   if ((usMaskeInn & LC_TR_ENHETH) != 0) {
      lin=2;
      if ((cp = ho_GetVal(pFil,"...ENHET-H",&lin)) == NULL) {
        pTrans->dEnhet_h = pTrans->dEnhet;
      } else {
        *pusMaske |= LC_TR_ENHETH;
        pTrans->dEnhet_h = strtod(cp,&cp);
      }
   }

   /* Enhet-d */
   if ((usMaskeInn & LC_TR_ENHETD) != 0) {
      /* Enhet-d */
      lin=2;
      if ((cp = ho_GetVal(pFil,"...ENHET-D",&lin)) == NULL) {
        pTrans->dEnhet_d = pTrans->dEnhet;
      } else {
        *pusMaske |= LC_TR_ENHETD;
        pTrans->dEnhet_d = strtod(cp,&cp);
      }
   }

   /* Vert-datum */
   if ((usMaskeInn & LC_TR_VERTDATUM) != 0) {
      lin = 2;
      if ((cp = ho_GetVal(pFil,"...VERT-DATUM",&lin)) != NULL) {
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
      if ((cp = ho_GetVal(pFil,"...VERT-INT",&lin)) != NULL) {
         *pusMaske |= LC_TR_VERTINT;
         UT_StrShort(cp,0,&itxi,&pTrans->sVertintHref);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sVertintDref);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sVertintFref);
      }
   }

   /* Vert-delta */
   if ((usMaskeInn & LC_TR_VERTDELTA) != 0) {
      lin = 2;
      if ((cp = ho_GetVal(pFil,"...VERT-DELTA",&lin)) != NULL) {
         *pusMaske |= LC_TR_VERTDELTA;
         UT_StrShort(cp,0,&itxi,&pTrans->sVdeltaMin);
         UT_StrShort(cp,itxi,&itxi,&pTrans->sVdeltaMax);
      }
   }


   /* ----- Div. sluttkontroll ----- */

   /* Kontroller at det er funnet Koordsys, Transsys eller Geosys */
   if ((usMaskeInn & LC_TR_KOORDSYS) != 0  ||
       (usMaskeInn & LC_TR_TRANSSYS) != 0  ||
       (usMaskeInn & LC_TR_GEOSYS) != 0     ) {
      if ((*pusMaske & LC_TR_KOORDSYS) == 0  &&
          (*pusMaske & LC_TR_TRANSSYS) == 0  &&
          (*pusMaske & LC_TR_GEOSYS) == 0 ) {
         /* Ikke noe koordinatsystem funnet */
         LC_Error(15,"(ho_GetTransEx)","");
         ist = UT_FALSE;
      }
   }

   /* Kontroller at det er funnet Origo */
   if ((usMaskeInn & LC_TR_ORIGO) != 0 &&  
       (*pusMaske & LC_TR_ORIGO) == 0 ) {
      /* Origo mangler */
      LC_Error(16,"(ho_GetTransEx)","");
      ist = UT_FALSE;
   }

   /* Kontroller at det er funnet Enhet */
   if ((usMaskeInn & LC_TR_ENHET) != 0  &&  
       (*pusMaske & LC_TR_ENHET) == 0 ) {
      /* Enhet mangler */
      LC_Error(17,"(ho_GetTransEx)","");
      ist = UT_FALSE;
   }

   return ist;
}



/*
AR:1999-07-12
CH HO_GetTrans                                         Finner .TRANSPAR i hodet
CD =============================================================================
CD Formål:
CD Henter transformasjonsparametrene fra filhodet.
CD
CD OBS! Denne rutinen opprettholdes bare for bakoverkompatibilitet.
CD      For nye programmer bør HO_GetTransEx benyttes. HO_GetTransEx er
CD      kompatibel med nye versjoner av SOSI.
CD
CD Parametre:
CD Type     Navn       I/U   Forklaring
CD -----------------------------------------------------------------------------
CD char    *pszFil      i   Fullstendig filnavn
CD short   *koosys      u   Koordinatsystem
CD double  *origo_a     u   ..ORIGO-AUST
CD double  *origo_n     u   ..ORIGO-NORD
CD double  *enhet       u   ...ENHET
CD double  *enhet_h     u   ...ENHET-H
CD double  *enhet_d     u   ...ENHET-D
CD short    sStatus     r   UT_TRUE, eller UT_FALSE.
CD
CD Bruk:
CD sStatus = HO_GetTrans(fil,&koosys,&origo_a,&origo_n,&enhet,&enhet_h,&enhet_d);
   =============================================================================
*/
SK_EntPnt_FYBA short HO_GetTrans(const char *pszFil,short *koosys,double *origo_a,
					  double *origo_n,double *enhet,double *enhet_h,double *enhet_d)
{
   short sStatus;
   FILE * pFil;

   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"",UT_READ,UT_OLD,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Hent verdier */
      sStatus = ho_GetTrans(pFil,koosys,origo_a,origo_n,enhet,enhet_h,enhet_d);
      fclose (pFil);

	/* Åpningsfeil på kladdefilen */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_GetTrans)",err().tx);
      sStatus = UT_FALSE;
   }

   return sStatus;
}


/*
GL-880427
AR-900314
CH ho_GetTrans                                         Finner .TRANSPAR i hodet
CD =============================================================================
CD Formål:
CD Henter transformasjonsparametrene fra filhodet.
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD -----------------------------------------------------------------------------
CD FILE    *pFil         i   Filpeker til sosi-fil.
CD short   *koosys       u   Koordinatsystem
CD double  *origo_a      u   ..ORIGO-AUST
CD double  *origo_n      u   ..ORIGO-NORD
CD double  *enhet        u   ...ENHET
CD double  *enhet_h      u   ...ENHET-H
CD double  *enhet_d      u   ...ENHET-D
CD short    sStatus      r   UT_TRUE, eller UT_FALSE.
CD
CD Bruk:
CD ho_GetTrans(pFil,&koosys,&origo_a,&origo_n,&enhet,&enhet_h,&enhet_d);
   =============================================================================
*/
short ho_GetTrans(FILE *pFil,short *koosys,double *origo_a,
					  double *origo_n,double *enhet,double *enhet_h,double *enhet_d)
{
   short lin;
   char *cp;


   /* Sjekk hvilket tegnsett som skal brukes */
	ho_GetTegnsett(pFil,&Sys.BufAdm.sTegnsett);

   lin=2;
   if ( ! ho_GetVal(pFil,"..TRANSPAR",&lin)) {
       LC_Error(14," (HO_GetTrans) "," ");
       return UT_FALSE;
   }

   
   *koosys=0;
   lin=2;
   cp = ho_GetVal(pFil,"...KOORDSYS",&lin);
   if (cp == NULL) {
   lin=2;
   ho_GetVal(pFil,"..KOORDSYS",&lin);
   }
   if (cp == NULL) {
    LC_Error(15," (HO_GetTrans) "," ");
    return UT_FALSE;

   } else {
     *koosys = (short)atoi(cp);
   }

   lin=2;
   if ((cp = ho_GetVal(pFil,"...ORIGO-NØ",&lin)) == NULL) {
    LC_Error(16," (HO_GetTrans) "," ");
    return UT_FALSE;

   } else {
     *origo_n = strtod(cp,&cp);
     *origo_a = strtod(cp,&cp);
     lin=2;
     if ((cp = ho_GetVal(pFil,"...ENHET",&lin)) == NULL) {
        LC_Error(17," (HO_GetTrans) "," ");
        return UT_FALSE;
     } else {
        *enhet = strtod(cp,&cp);
     }
     lin=2;
     if ((cp = ho_GetVal(pFil,"...ENHET-H",&lin)) == NULL) {
         *enhet_h = *enhet;
     } else {
         *enhet_h = strtod(cp,&cp);
     }
     lin=2;
     if ((cp = ho_GetVal(pFil,"...ENHET-D",&lin)) == NULL) {
         *enhet_d = *enhet;
     } else {
         *enhet_d = strtod(cp,&cp);
     }
   }

   return UT_TRUE;
}


/*
AR-890823
CH HO_GetOmr                                            Finner ..OMRÅDE i hodet
CD =============================================================================
CD Formål:
CD Henter områdeangivelsen fra filhodet.
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD -----------------------------------------------------------------------------
CD char    *pszFil      i   Fullstendig filnavn
CD double  *nv_a        u
CD double  *nv_n        u
CD double  *oh_a        u
CD double  *oh_n        u
CD short    sStatus     r   UT_TRUE, eller UT_FALSE.
CD
CD Bruk:
CD sStatus = HO_GetOmr(pszFil,&nv_a,&nv_n,&oh_a,&oh_n);
	=============================================================================
*/
SK_EntPnt_FYBA short HO_GetOmr(const char * pszFil,double *nv_a,double *nv_n,double *oh_a,double *oh_n)
{
   short sStatus;
   FILE * pFil;

   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"",UT_READ,UT_OLD,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Hent verdier */
      ho_GetOmr(pFil,nv_a,nv_n,oh_a,oh_n);
      fclose (pFil);
      sStatus = UT_TRUE;

	/* Åpningsfeil */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_GetOmr)",err().tx);
      sStatus = UT_FALSE;
   }

   return sStatus;
}


/*
AR-890823
CH ho_GetOmr                                            Finner ..OMRÅDE i hodet
CD =============================================================================
CD Formål:
CD Henter områdeangivelsen fra filhodet.
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD -----------------------------------------------------------------------------
CD FILE    *fil          i    Filpeker til sosi-fil.
CD double  *nv_a         u
CD double  *nv_n         u
CD double  *oh_a         u
CD double  *oh_n         u
CD short    sStatus      r    UT_TRUE, eller UT_FALSE.
CD
CD Bruk:
CD sStatus = ho_GetOmr(fil,&nv_a,&nv_n,&oh_a,&oh_n);
	=============================================================================
*/
short ho_GetOmr(FILE *fil,double *nv_a,double *nv_n,double *oh_a,double *oh_n)
{
   short lin,i;
   char *cp;
   short sStatus = UT_TRUE;


   /* Sjekk hvilket tegnsett som skal brukes */
   ho_GetTegnsett(fil,&Sys.BufAdm.sTegnsett);


   lin=2;
   if (ho_GetVal(fil,"..OMRÅDE",&lin) == NULL) {
      LC_Error(7,"(HO_GetOmr)","");
      *nv_n = -9999999.0;
      *nv_a = -9999999.0;
      *oh_n =  9999999.0;
      *oh_a =  9999999.0;
      sStatus = UT_FALSE;


   } else {
      /* Min-NØ */
      i = lin;
	   if ((cp = ho_GetVal(fil,"...MIN-NØ",&i)) == NULL ) {
         LC_Error(8,"(HO_GetOmr)","");
         *nv_n = -9999999.0;
         *nv_a = -9999999.0;
         sStatus = UT_FALSE;
      
      } else {
         *nv_n = strtod(cp,&cp);
         *nv_a = strtod(cp,&cp);
      }
      
		/* Max-NØ */
      i = lin;
      if ((cp = ho_GetVal(fil,"...MAX-NØ",&i)) == NULL) {
         LC_Error(9,"(HO_GetOmr)","");
         *oh_n = 999999.0;
         *oh_a = 9999999.0;
         sStatus = UT_FALSE;
      
      } else{
         *oh_n = strtod(cp,&cp);
         *oh_a = strtod(cp,&cp);
      }
   }

   /* Sjekker at området har utstrekning */
   //if (*oh_a-*nv_a < 0.001  ||  *oh_n-*nv_n < 0.001) {
   //   LC_Error(104,"(HO_GetOmr)","");
   //   *nv_n = -9999999.0;
   //   *nv_a = -9999999.0;
   //   *oh_n =  9999999.0;
   //   *oh_a =  9999999.0;
	//}

   return sStatus;
}




/*
AR:1999-07-12
CH HO_GetKvalitet                                 Finner kvalitetsopplysninger
CD =============================================================================
CD Formål:
CD Finne kvalitetsopplysninger i filhode.
CD (Ikke aktuellt etter SOSI v. 4.00.)
CD
CD Parametre:
CD Type    Navn              I/U  Forklaring
CD -----------------------------------------------------------------------------
CD char   *pszFil             i  Fullstendig filnavn
CD short  *psMetode           u  Hvordan data er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD long   *pLNnoyaktighet     u  Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT  nøyaktighet er ukjent.
CD short  *psSynbarhet        u  Synbarhet i bilde
CD                                 KVAL_SYN_UNDEF  synbarhet er udefinert.
CD short  *psHoydeMetode      u  Hvordan høyden er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD long   *plHoydeNoyaktighet u  Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT  nøyaktighet er ukjent.
CD short   ist                r  Statusvariabel: UT_TRUE  - OK, ..KVALITET er funnet
CD                                               UT_FALSE - ikke funnet
CD
CD Bruk:
CD      ist = HO_GetKvalitet(fil,&sMetode,&lNoyaktighet,&sSynbarhet,
CD                           &sHoydeMetode,&lHoydeNoyaktighet);
CD =============================================================================
*/
SK_EntPnt_FYBA short HO_GetKvalitet(const char *pszFil,short *psMetode,long *plNoyaktighet,
                     short *psSynbarhet,short *psHoydeMetode,long *plHoydeNoyaktighet)
{
   short sStatus;
   FILE * pFil;

   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"",UT_READ,UT_OLD,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Hent verdier */
      sStatus = ho_GetKvalitet(pFil,psMetode,plNoyaktighet,psSynbarhet,psHoydeMetode,plHoydeNoyaktighet);
      fclose (pFil);

	/* Åpningsfeil */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_GetKvalitet)",err().tx);
      sStatus = UT_FALSE;
   }

   return sStatus;
}



/*
OJ-891123
CH ho_GetKvalitet                                 Finner kvalitetsopplysninger
CD =============================================================================
CD Formål:
CD Finne kvalitetsopplysninger i filhode.
CD (Ikke aktuellt etter SOSI v. 4.00.)
CD
CD Parametre:
CD Type    Navn              I/U  Forklaring
CD -----------------------------------------------------------------------------
CD FILE   *pFil               i  Filpeker til sosi-fil.
CD short  *psMetode           u  Hvordan data er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD long   *pLNnoyaktighet     u  Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT  nøyaktighet er ukjent.
CD short  *psSynbarhet        u  Synbarhet i bilde
CD                                 KVAL_SYN_UNDEF  synbarhet er udefinert.
CD short  *psHoydeMetode      u  Hvordan høyden er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD long   *plHoydeNoyaktighet u  Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT  nøyaktighet er ukjent.
CD short   ist                r  Statusvariabel: UT_TRUE  - OK, ..KVALITET er funnet
CD                                               UT_FALSE - ikke funnet
CD
CD Bruk:
CD      ist = ho_GetKvalitet(fil,&sMetode,&lNoyaktighet,&sSynbarhet,
CD                           &sHoydeMetode,&lHoydeNoyaktighet);
CD =============================================================================
*/
short ho_GetKvalitet(FILE *pFil,short *psMetode,long *plNoyaktighet,
                     short *psSynbarhet,short *psHoydeMetode,long *plHoydeNoyaktighet)
{
	short lin;
   char *cp;
   short ist = UT_FALSE;


   /* Sjekk hvilket tegnsett som skal brukes */
   ho_GetTegnsett(pFil,&Sys.BufAdm.sTegnsett);

   lin=2;
   if ((cp = ho_GetVal(pFil,"..KVALITET",&lin)) != NULL) {     /* Kvalitet */
      ist = UT_TRUE;
   }

   /* Tolk strengen til tallverdier */
   LN_TolkKvalitet(cp,psMetode,plNoyaktighet,psSynbarhet,
                   psHoydeMetode,plHoydeNoyaktighet);


   /* Handter manglende høyde-kvalitet spesiellt */
	if (*psHoydeMetode == KVAL_MET_UNDEF)      *psHoydeMetode      = *psMetode;
   if (*plHoydeNoyaktighet == KVAL_NOY_UKJENT) *plHoydeNoyaktighet = *plNoyaktighet;

   return ist;
}



/*
AR-920331
CH HO_GetTegnsett                                            Finner tegnsett
CD ==========================================================================
CD Formål:
CD Finne tegnsett i filhodet.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD char   *pszFil      i   Fullstendig filnavn
CD short  *psTegnsett  u   Tegnsett, konstanter definert:
CD                            TS_DOSN8   = DOS norsk 8-bits(standardverdi)
CD                            TS_ND7     = Norsk Data 7-bits
CD                            TS_DECM8   = DEC multinasjonal 8-bits
CD                            TS_ISO8859 = ISO8859-10 Norsk/samisk tegnsett
CD                            TS_DECN7   = DEC norsk 7-bits
CD short   sStatus     r   Status: UT_TRUE  = Funnet
CD                                 UT_FALSE = Ikke funnet
CD
CD Bruk:
CD      sStatus = HO_GetTegnsett(pszFil,&sTegnsett);
CD ==========================================================================
*/
SK_EntPnt_FYBA short HO_GetTegnsett(const char *pszFil,short *psTegnsett)
{
   short sStatus;
   FILE * pFil;

   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"",UT_READ,UT_OLD,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Hent verdier */
      sStatus = ho_GetTegnsett(pFil,psTegnsett);
      fclose (pFil);

	/* Åpningsfeil */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_GetTegnsett)",err().tx);
      sStatus = UT_FALSE;
   }

   return sStatus;
}


/*
AR-920331
CH ho_GetTegnsett                                            Finner tegnsett
CD ==========================================================================
CD Formål:
CD Finne tegnsett i filhodet.
CD
CD Parametre:
CD Type     Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD FILE    *fil        i   Filpeker til sosi-fil.
CD short  *psTegnsett  u   Tegnsett, konstanter definert:
CD                            TS_DOSN8   = DOS norsk 8-bits(standardverdi)
CD                            TS_ND7     = Norsk Data 7-bits
CD                            TS_DECM8   = DEC multinasjonal 8-bits
CD                            TS_ISO8859 = ISO8859-10 Norsk/samisk tegnsett
CD                            TS_DECN7   = DEC norsk 7-bits
CD short   sStatus     r   Status: UT_TRUE  = Funnet
CD                                 UT_FALSE = Ikke funnet
CD
CD Bruk:
CD      sStatus = ho_GetTegnsett(fil,&sTegnsett);
CD ==========================================================================
*/
short ho_GetTegnsett(FILE *pFil,short *psTegnsett)
{
   short lin;
   char *cp;
   short ist = UT_FALSE;

   *psTegnsett = TS_DOSN8;       
   lin=2;                        

   if ((cp = ho_GetVal(pFil,"..TEGNSETT",&lin)) != NULL) {     /* Tegnsett */
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

   return ist;
}


/*
AR:1999-07-14
CH HO_GetVal                                      Finn verdien til et SOSI-navn
CD =============================================================================
CD Formål:
CD Henter parametrene til et SOSI-navn.
CD Strengen ligger i et felles "returbuffer" for alle get-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "get-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk strcpy).
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------------
CD char    *pszFil       i   Fullstendig filnavn
CD char    *sosi_navn    i   SOSI-navn det skal finnes verdi til
CD short   *sett_nr     i/u  i: "Sett nummer"(linjenummer) for start søking (min 1)
CD                           u: Ved tilslag returneres "Sett nummer" for
CD                              tilslaget.
CD char    *para_peker   r   Peker til parameter-streng avslutta med '\0'.
CD                           Hvis SOSI-navnet ikke er funnet returneres NULL.
CD
CD Bruk:
CD para_peker = HO_GetVal(fil,sosi_navn,&sett_nr);
	=============================================================================
*/
SK_EntPnt_FYBA char *HO_GetVal(const char *pszFil,char *sosi_navn,short *sett_nr)
{
   short sStatus;
   FILE * pFil;
   char *rp = NULL;               /* Retur peker */


   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"",UT_READ,UT_OLD,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Hent verdier */
      rp = ho_GetVal(pFil,sosi_navn,sett_nr);
      fclose (pFil);

	/* Åpningsfeil */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_GetVal)",err().tx);
      sStatus = UT_FALSE;
   }

   return rp;
}


/*
GL:1988-04-27
AR:1989-08-23
CH ho_GetVal                                      Finn verdien til et SOSI-navn
CD =============================================================================
CD Formål:
CD Henter parametrene til et SOSI-navn.
CD Strengen ligger i et felles "returbuffer" for alle get-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "get-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk strcpy).
CD
CD Parametre:
CD Type     Navn        I/U   Forklaring
CD -----------------------------------------------------------------------------
CD FILE    *pFil         i   Filpeker til sosi-fil.
CD char    *sosi_navn    i   SOSI-navn det skal finnes verdi til
CD short   *sett_nr     i/u  i: "Sett nummer"(linjenummer) for start søking (min 1)
CD                           u: Ved tilslag returneres "Sett nummer" for
CD                              tilslaget.
CD char    *para_peker   r   Peker til parameter-streng avslutta med '\0'.
CD                           Hvis SOSI-navnet ikke er funnet returneres NULL.
CD
CD Bruk:
CD para_peker = ho_GetVal(pFil,sosi_navn,&sett_nr);
	=============================================================================
*/
char *ho_GetVal(FILE *pFil, const char *sosi_navn,short *sett_nr)
{
   UT_INT64 startpos;
   short ant_par,navn_nr,type;
   short funnet = 0;
   short ferdig = 0;
   short sett = 0;
   LB_LESEBUFFER * pLb = &(Sys.BufAdm);
   char *rp = NULL;               /* Retur peker */


   // Søk fram til .HODE
   if (ho_FinnHode(pFil, &startpos) == UT_TRUE) {
      // Finn riktig info
      // SOSI-navnet
      LN_PakkNavn(&(Sys.SosiNavn),sosi_navn,&navn_nr,&ant_par);

      /* Sikkrer at ny lesing startes */
      pLb->sStatus = LESEBUFFER_TOM;
      //_fseeki64(pFil,startpos,SEEK_SET);
      UT_SetPos_i64(pFil,startpos);

      do {
         sett++;
         /* Hent "sett" */
         type = LB_GetSet(pFil,pLb,&(Sys.SosiNavn));
         if (type >= 0  ||  type == LEST_GINFO) {
            if (sett > 1  &&  pLb->cur_niv == 1) {
               ferdig = 1;

            } else {
               if (sett >= *sett_nr) {
                  if (pLb->cur_navn[pLb->cur_niv-1] == navn_nr) {
                     funnet = 1;
                     rp = pLb->pp;
                     *sett_nr = sett;
                  }
               }
            }
         }
         pLb->set_brukt = SET_BRUKT;
      } while ( ! ferdig  &&  ! funnet);       /* Søk etter navnet */
   }

   pLb->sStatus = LESEBUFFER_TOM;
   return rp;
}


/*
GL-880303
AR-891124
CH  HO_New                                                   Lager nytt hode
CD  =========================================================================
CD Formål:
CD Genererer et nytt SOSI-filhode.
CD Hvis område ikke har noen utstrekning justeres
CD dette med 1 meter i hver retning. 
CD
CD Parametre:
CD Type     Navn         I/U    Forklaring
CD --------------------------------------------------------------------------
CD char    *pszFil        i    Fullstendig filnavn
CD short    koosys        i    Koordinatsystem
CD double   origo_a       i    Origo øst
CD double   origo_n       i    Origo nord
CD double   enhet         i    Enhet
CD double   enhet_h       i    Enhet-H
CD double   enhet_d       i    Enhet-D
CD double   nv_a          i    Område:  Nedre venstre hjørne
CD double   nv_n          i
CD double   oh_a          i             Øvre høyre hjørne
CD double   oh_n          i
CD short    sStatus       r    Status: UT_TRUE  = Funnet
CD                                     UT_FALSE = Ikke funnet
CD
CD Bruk:
CD sStatus = HO_New(fil,koosys,origo_a,origo_n,enhet,enhet_h-enhet_d,
CD                  nv_a,nv_n,oh_a,oh_n);
CD =============================================================================
*/
SK_EntPnt_FYBA short HO_New(const char *pszFil,short koosys,double origo_a,double origo_n,
            double enhet,double enhet_h,double enhet_d,
            double nv_a,double nv_n,double oh_a,double oh_n)
{

   short sStatus = UT_TRUE;
   FILE * pFil;


   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"",UT_UPDATE,UT_UNKNOWN,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Skriv nytt hode */
      ho_New(pFil, koosys, origo_a, origo_n, enhet, enhet_h, enhet_d,
             nv_a, nv_n, oh_a, oh_n);

      fclose (pFil);
      sStatus = UT_TRUE;

	/* Åpningsfeil */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_New)",err().tx);
      sStatus = UT_FALSE;
   }

   return sStatus;
}


/*
GL-880303
AR-891124
CH  ho_New                                                   Lager nytt hode
CD  =========================================================================
CD Formål:
CD Genererer et nytt SOSI-filhode.
CD Hvis område ikke har noen utstrekning justeres
CD dette med 1 meter i hver retning. 
CD
CD Parametre:
CD Type     Navn         I/U    Forklaring
CD --------------------------------------------------------------------------
CD FILE    *fil           i   Filpeker til sosi-fil.
CD short    koosys        i    Koordinatsystem
CD double   origo_a       i    Origo øst
CD double   origo_n       i    Origo nord
CD double   enhet         i    Enhet
CD double   enhet_h       i    Enhet-H
CD double   enhet_d       i    Enhet-D
CD double   nv_a          i    Område:  Nedre venstre hjørne
CD double   nv_n          i
CD double   oh_a          i             Øvre høyre hjørne
CD double   oh_n          i
CD
CD Bruk:
CD     ho_New(fil,koosys,origo_a,origo_n,enhet,enhet_h-enhet_d,
CD            nv_a,nv_n,oh_a,oh_n);
CD =============================================================================
*/
void ho_New(FILE *fil,short koosys,double origo_a,double origo_n,
            double enhet,double enhet_h,double enhet_d,
            double nv_a,double nv_n,double oh_a,double oh_n)
{
   char tx[LC_MAX_SOSI_LINJE_LEN];


   //_fseeki64(fil,0,SEEK_SET);
   UT_SetPos_i64(fil,0);

   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,".HODE\r\n");
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,"..TEGNSETT ISO8859-10\r\n");
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,"..TRANSPAR\r\n");
   UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"...KOORDSYS  %d\r\n",koosys);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"...ORIGO-NØ  %.0f  %.0f\r\n",origo_n,origo_a);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   
   //UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"...ENHET  %-.3f\r\n",enhet);
   LB_FormaterEnhet(tx,LC_MAX_SOSI_LINJE_LEN,"...ENHET",enhet);
   UT_StrCat(tx,"\r\n",LC_MAX_SOSI_LINJE_LEN);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   
   if (fabs(enhet-enhet_h)>0.000001) {
      LB_FormaterEnhet(tx,LC_MAX_SOSI_LINJE_LEN,"...ENHET-H",enhet_h);
      UT_StrCat(tx,"\r\n",LC_MAX_SOSI_LINJE_LEN);
      LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   }
   
   if (fabs(enhet-enhet_d)>0.000001) {
      LB_FormaterEnhet(tx,LC_MAX_SOSI_LINJE_LEN,"...ENHET-D",enhet_d);
      UT_StrCat(tx,"\r\n",LC_MAX_SOSI_LINJE_LEN);
      LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   }
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,"..OMRÅDE\r\n");
   
   // Hvis nødvendig justeres område
   if (fabs(oh_n-nv_n) < 0.000001) {
      nv_n -= 1.0;
      oh_n += 1.0;
   }
   if (fabs(oh_a-nv_a) < 0.000001) {
      nv_a -= 1.0;
      oh_a += 1.0;
   }

   UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"...MIN-NØ   %.0f     %.0f\r\n",nv_n,nv_a);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"...MAX-NØ   %.0f     %.0f\r\n",oh_n,oh_a);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);

   UT_SNPRINTF(tx,LC_MAX_SOSI_LINJE_LEN,"..SOSI-VERSJON %.2f\r\n",((double)FYBA_SOSI_VERSJON)/100.0);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);

   UT_StrCopy(tx,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n",LC_MAX_SOSI_LINJE_LEN);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,tx);
   LB_WriteLine(fil,LC_INTERNT_TEGNSETT,".SLUTT\r\n");

   /* chsize(fileno(fil),ftell(fil)-1); */    /* Sett filstørrelse */
}


/*
AR:1999-07-14
CH HO_TestSOSI                                              Tester SOSI-filen
CD =============================================================================
CD Formål:
CD Sjekker at filen er en SOSI-fil, og finner posisjonen for .SLUTT.
CD
CD Parametre:
CD Type      Navn       I/U   Forklaring
CD -----------------------------------------------------------------------------
CD char     *pszFil      i    Fullstendig filnavn
CD UT_INT64 *sluttpos    u    Posisjon for .SLUTT
CD short     ist         r    Status: UT_TRUE  = OK
CD                                  UT_FALSE = feil
CD
CD Bruk:
CD     ist = HO_TestSOSI(pszFil,&sluttpos);
CD =============================================================================
*/
SK_EntPnt_FYBA short HO_TestSOSI(const char *pszFil,UT_INT64 *sluttpos)
{
   short sStatus;
   FILE * pFil;


   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"",UT_READ,UT_OLD,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Sjekk filen */
      sStatus = ho_TestSOSI(pFil,sluttpos);
      fclose (pFil);

	/* Åpningsfeil */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_TestSOSI)",err().tx);
      sStatus = UT_FALSE;
   }

   return sStatus;
}


/*
AR-891205
CH ho_TestSOSI                                              Tester SOSI-filen
CD =============================================================================
CD Formål:
CD Sjekker at filen er en SOSI-fil, og finner posisjonen for .SLUTT.
CD
CD Parametre:
CD Type      Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD FILE     *pFil       i    Filpeker til sosi-fil.
CD UT_INT64 *sluttpos   u    Posisjon for .SLUTT
CD short     ist        r    Status: UT_TRUE  = OK
CD                                 UT_FALSE = feil
CD
CD Bruk:
CD     ist = ho_TestSOSI(pFil,&sluttpos);
CD =============================================================================
*/
short ho_TestSOSI(FILE *pFil,UT_INT64 *sluttpos)
{
   short ferdig;
   char tx[LC_MAX_SOSI_LINJE_LEN];
   UT_INT64 startpos,filpos;
   double nv_a,nv_n,oh_a,oh_n;
   short ist = UT_FALSE;

   *sluttpos = 0;
   
   // ----- Sjekk at filen starter med .HODE og søk fram til .HODE
   if (ho_FinnHode(pFil, &startpos) == UT_TRUE) {
      ist = UT_FALSE;

      // Skann siste del av filen for å finne .SLUTT
      ferdig = 0;
      _fseeki64(pFil,-200,SEEK_END);
      UT_GetPos_i64(pFil,&filpos);

      while (!ferdig  &&  UT_ReadLine(pFil,LC_MAX_SOSI_LINJE_LEN,tx) == UT_OK) {
         if (*tx == '.' &&  *(tx+1) == 'S') {
            if (strncmp(tx,".SLUTT",6) == 0) {  /* .SLUTT er funnet */
               *sluttpos = filpos;
               ferdig = 1;
               ist = UT_TRUE;
            }
         }
         //UT_GetPos(pFil,&filpos);
         filpos = _ftelli64(pFil);
      }
                 
      if (ist == UT_FALSE) {
         // .SLUTT ikke er funnet, skann hele filen fra hodet 
         ferdig = 0;
         filpos = startpos;
         UT_SetPos_i64(pFil,filpos);
  
         while (!ferdig  &&  UT_ReadLine(pFil,LC_MAX_SOSI_LINJE_LEN,tx) == UT_OK) {
            if (*tx == '.' &&  *(tx+1) == 'S') {
               if (strncmp(tx,".SLUTT",6) == 0) {  /* .SLUTT er funnet */
                  *sluttpos = filpos;
                  ferdig = 1;
                  ist = UT_TRUE;
               }
            }
            UT_GetPos_i64(pFil,&filpos);
         }
      }
   }


   /* Sjekk at hodet har transpar og fornuftig område */   
   if (ist == UT_TRUE) {
      unsigned short usMaske = LC_TR_ALLT;
      LC_TRANSPAR Trans;
      ist = ho_GetTransEx(pFil,&usMaske,&Trans);

      if (ist == UT_TRUE) {
         ist = ho_GetOmr(pFil,&nv_a,&nv_n,&oh_a,&oh_n);
      }
   }

   return ist;
}


/*
HT:1998-05-19
CH HO_SjekkTegnsett                              Sjekker tegnsett på SOSI-filen
CD =============================================================================
CD Formål:
CD Sjekker faktisk tegnsett i .HODE.
CD
CD Parametre:
CD Type    Navn       I/U   Forklaring
CD -----------------------------------------------------------------------------
CD char   *pszFil      i   Fullstendig filnavn
CD short  *psTegnsett  u   Tegnsett, konstanter definert:
CD                            TS_UKJENT  = Fikk ikke sjekket tegnsett
CD                            TS_DOSN8   = DOS norsk 8-bits(standardverdi)
CD                            TS_ND7     = Norsk Data 7-bits
CD                            TS_DECM8   = DEC multinasjonal 8-bits
CD                            TS_ISO8859 = ISO8859-10 Norsk/samisk tegnsett
CD                            TS_DECN7   = DEC norsk 7-bits
CD short   sStatus     r   Status:  0  = Ikke funnet
CD                                  1  = Ett tegnsett funnet
CD                                  2  = Flere tegnsett funnet
CD Bruk:
CD     sStatus = HO_SjekkTegnsett(fpek,tegnsett);
CD =============================================================================
*/
SK_EntPnt_FYBA short HO_SjekkTegnsett(const char *pszFil,short *psTegnsett)
{
   short sStatus;
   FILE * pFil;


   /* Åpner filen */
   pFil = UT_OpenFile(pszFil,"",UT_READ,UT_OLD,&sStatus);

   /* Åpnet OK ? */
   if (sStatus == UT_OK) {
      /* Sjekk filen */
      sStatus = ho_SjekkTegnsett(pFil,psTegnsett);
      fclose (pFil);

	/* Åpningsfeil */
   } else {
      char szError[256];
      UT_strerror(szError,256,sStatus);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pszFil,szError);
      LC_Error(101,"(HO_SjekkTegnsett)",err().tx);
      sStatus = 0;
   }

   return sStatus;
}


/*
HT-980519
CH ho_SjekkTegnsett                              Sjekker tegnsett på SOSI-filen
CD =============================================================================
CD Formål:
CD Sjekker faktisk tegnsett i .HODE.
CD
CD Parametre:
CD Type    Navn       I/U   Forklaring
CD -----------------------------------------------------------------------------
CD FILE   *fil         i   Filpeker til sosi-fil.
CD short  *psTegnsett  u   Tegnsett, konstanter definert:
CD                            TS_UKJENT  = Fikk ikke sjekket tegnsett
CD                            TS_DOSN8   = DOS norsk 8-bits(standardverdi)
CD                            TS_ND7     = Norsk Data 7-bits
CD                            TS_DECM8   = DEC multinasjonal 8-bits
CD                            TS_ISO8859 = ISO8859-10 Norsk/samisk tegnsett
CD                            TS_DECN7   = DEC norsk 7-bits
CD short   sStatus     r   Status:  0  = Ikke funnet
CD                                  1  = Ett tegnsett funnet
CD                                  2  = Flere tegnsett funnet
CD Bruk:
CD     sStatus = ho_SjekkTegnsett(fpek,tegnsett);
CD =============================================================================
*/
short ho_SjekkTegnsett(FILE *fil,short *psTegnsett)
{
   char *ch, tx[LC_MAX_SOSI_LINJE_LEN];
   short tegnsett, lesefeil;
   short ferdig = 0;
   short ant = 0; 

/*          Æ   Ø   Å   æ   ø   å 
TS_DOSN8   146 157 143 145 155 134 
TS_ND7      91  92  93 123 124 125 
TS_ISO8859 198 216 197 230 248 229 */
   static unsigned char atab[256] =
   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 19 */
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 39 */
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 59 */
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 79 */
     0,0,0,0,0,0,0,0,0,0,0,TS_ND7,TS_ND7,TS_ND7,0,0,0,0,0,0, /* 99 */
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 119 */
     0,0,0,TS_ND7,TS_ND7,TS_ND7,0,0,0,0,0,0,0,0,TS_DOSN8,0,0,0,0,0, /* 139 */
     0,0,0,TS_DOSN8,0,TS_DOSN8,TS_DOSN8,0,0,0,0,0,0,0,0,TS_DOSN8,0,TS_DOSN8,0,0, /* 159 */
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 179 */
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,TS_ISO8859,TS_ISO8859,0, /* 199 */
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,TS_ISO8859,0,0,0, /* 219 */
     0,0,0,0,0,0,0,0,0,TS_ISO8859,TS_ISO8859,0,0,0,0,0,0,0,0,0, /* 239 */
     0,0,0,0,0,0,0,0,TS_ISO8859,0,0,0,0,0,0,0 };


   tegnsett = TS_UKJENT;

   /* Sjekker hva som faktisk er tegnsettet i .HODE,
      starter først på filen og leser  */
   UT_SetPos_i64(fil,0);
   
   /* Leser første linje i .HODE */
   lesefeil = UT_ReadLineNoComm(fil,LC_MAX_SOSI_LINJE_LEN,tx);
   while (!ferdig  &&  ! lesefeil ){

      /* Sjekker tegnsett*/
      for (ch=tx; *ch; ch++) {
                  
         /* Hvis vi har fått sjekket tegnsettet, og det
         ikke er funnet tidligere tas det vare på nå */
         if (atab[(unsigned char)*ch] && !(atab[(unsigned char)*ch] & tegnsett)) {
            tegnsett |= atab[(unsigned char)*ch];
            ant++;
         }
      }

      /* Leser eventuellt neste linje i .HODE */
      if (!ferdig) lesefeil = UT_ReadLineNoComm(fil,LC_MAX_SOSI_LINJE_LEN,tx);
      
      /* Slutt på .HODE? */
      ferdig = *(tx+1) != '.';  
   }

   *psTegnsett = tegnsett;
 
   return ant;
}


/*
AR:2004-05-05
!---------------------------------------------------------------!
! ho_TestFyllKommentar - Tester om en streng er fyll/kommentar. !
!                                                               !
! Retur:  UT_TRUE  = linjen er fyll/kommentar                   !
!         UT_FALSE = linjen inneholder annen informasjon        !
!                                                               !
!---------------------------------------------------------------!
*/
static short ho_TestFyllKommentar(const char *pszTx)
{
   for (; *pszTx; ++pszTx) {
      if (!UT_IsSpace(*pszTx)  &&  *pszTx != '!')  return (UT_FALSE);
      if (*pszTx == '!')  return (UT_TRUE);
   }

   return (UT_TRUE);
}


/*
AR:2004-05-05
!---------------------------------------------------------------------!
! ho_FinnHode - Finner filposisjonen til .HODE                        !
!                                                                     !
! Retur:  UT_TRUE  = Lovlig hode er funnet                            !
!         UT_FALSE = .HODE er ikke funnet,                            !
!                    eller .HODE er ikke første logiske info i filen. !
!                                                                     !
!---------------------------------------------------------------------!
*/
short ho_FinnHode(FILE *pFil, UT_INT64 *lHodepos)
{
   char tx[LC_MAX_SOSI_LINJE_LEN], *cp;
   short ierr;

   *lHodepos = 0L;
   
   // ----- Sjekk at filen starter med .HODE
   UT_SetPos_i64(pFil,0);

   do
   {
      // Husk filposisjonen
      *lHodepos =  _ftelli64(pFil);
      // Les
      if ((ierr = UT_ReadLine(pFil,LC_MAX_SOSI_LINJE_LEN,tx)) != UT_OK) {

         return UT_FALSE;     // ===>  Retur pga. lesefeil
      }
   } while (ho_TestFyllKommentar(tx) == UT_TRUE);


   // ----- Har nå funnet en linje som inneholder logisk informasjon

   // Hopp over blanke på starten av linjen
   cp = &tx[0];
   while (UT_IsSpace(*cp)) {
      ++cp;
      ++(*lHodepos);
   }

   if (strncmp(cp,".HODE",5) == 0) {
         return UT_TRUE;      // ===>  Retur, .HODE er funnet
   }
         
   return UT_FALSE;   // ===>  Retur, .HODE er ikke funnet
}
