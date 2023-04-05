/* === AR-920210 ========================================================= */
/*  STATENS KARTVERK  -  FYSAK-PC                                          */
/*  Fil: fylo.c                                                            */
/*  Innhold: Åpningsrutiner for FYSAK-PC                                   */
/* ======================================================================= */

#include "fyba.h"
#include "fybax.h"

#include <math.h>
#include <fcntl.h>

#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* --- Lokale rutiner -------------------------- */
static LC_BASEADM * LO_AppBaseAdm(void);
static short       LO_DelBaseAdm(LC_BASEADM * pBase);
static LC_FILADM * LO_AppFilAdm(LC_BASEADM * pBase);
static void        LO_DelFilAdm(LC_FILADM *pFil);
static short       LO_OpenKladd(LC_BASEADM * pBase);
static short       LO_InklSos(LC_FILADM *pFil,short vising);

/* --- Globale strukturer ---------------------- */
LC_SYSTEMADM Sys;

LC_FEILMELDING& err() { /* Feilmeldingsstruktur - construct on first use to prevent */
					    /* it from being uninitialized */
  static LC_FEILMELDING* err = new LC_FEILMELDING;
  return *err;
}                       
char retur_str[LC_MAX_SOSI_LINJE_LEN];          /* Returstreng */

volatile short fyba_initiert = 0;    /* Bryter for å vise at LC_Init er utført */


void  (*LC_ErrorAdr)(short ifeilnr, const char* logtx, const char* vartx) = NULL;
void  (*LC_StartMessageAdr)(const char *cfil) = NULL;
void  (*LC_ShowMessageAdr)(double prosent) = NULL;
void  (*LC_EndMessageAdr)(void) = NULL;
short (*LC_CancelAdr)(void) = NULL;



/*
AR-910920
CH LC_Init                                                       Initierer FYBA
CD =============================================================================
CD Formål:
CD Initierer FYBA.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD
CD Bruk:
CD LC_Init();
   =============================================================================
*/
SK_EntPnt_FYBA void LC_Init(void)
{
   fyba_initiert = 1;                  /* FYBA er initiert */

   /* Husker aktuelle versjonsnummer */
   UT_StrCopy(Sys.szBaseVer,FYBA_IDENT,LC_BASEVER_LEN);
   UT_StrCopy(Sys.szIdxVer,FYBA_INDEKS_VERSJON,5);

	/* Ingen aktuell gruppe */
   Sys.GrId.lNr = INGEN_GRUPPE;
   Sys.sGrEndra = END_UENDRA;

   Sys.sResPlass = 0;
   Sys.lMaxSkriv = 0L;
   Sys.lAntSkriv = 0L;
   Sys.sNGISmodus = NGIS_NORMAL;
   Sys.sUtvidModus = LC_UTVID_SIKKER;

	/* Allokerer buffer */
	Sys.Hode.pszTx  = (char*)UT_MALLOC(LC_MAX_GINFO_BUFFER * sizeof(char));
	Sys.Ginfo.pszTx = (char*)UT_MALLOC(LC_MAX_GINFO_BUFFER * sizeof(char));
	Sys.pszPinfo    = (char*)UT_MALLOC(LC_MAX_PINFO_BUFFER * sizeof(char));
	Sys.pdAust      = (double *)UT_MALLOC(LC_MAX_KOORD * sizeof(double));
	Sys.pdNord      = (double *)UT_MALLOC(LC_MAX_KOORD * sizeof(double));
	Sys.pInfo       = (LB_INFO *)UT_MALLOC(LC_MAX_KOORD * sizeof(LB_INFO));

	/* Initierer lesebuffer for HO-rutinene */
	Sys.BufAdm.sStatus = LESEBUFFER_TOM;

	/* Initierer navnetabell for HO-rutinene */
	LN_InitTab(&(Sys.SosiNavn));

   Sys.usMerkRefGr = 0;

   /* Ingen base er åpnet */
   Sys.pForsteBase = NULL;
   Sys.pAktBase = NULL;
}


/*
AR-910920
CH LC_Close                                                    Stenger ned FYBA
CD =============================================================================
CD Formål:
CD Stenger ned FYBA.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD
CD Bruk:
CD LC_Close();
	=============================================================================
*/
SK_EntPnt_FYBA void LC_Close(void)
{
   LC_BASEADM *pBase, *pNesteBase;

   /* Ingen aktuell gruppe */
   Sys.GrId.lNr = INGEN_GRUPPE;

   if (fyba_initiert != 0) {
      fyba_initiert = 0;       /* FYBA er ikke initiert */

		/* Frigir buffer */
		UT_FREE(Sys.Hode.pszTx);
		UT_FREE(Sys.Ginfo.pszTx);
		UT_FREE(Sys.pszPinfo);
		UT_FREE(Sys.pdAust);
		UT_FREE(Sys.pdNord);
		UT_FREE(Sys.pInfo);

      /* Initierer navnetabell for HO-rutinene */
		LN_InitTab(&(Sys.SosiNavn));

      /* Stenger eventuelle åpne baser. */
      for (pBase=Sys.pForsteBase; pBase!=NULL; pBase=pNesteBase) {
         pNesteBase = pBase->pNesteBase;
         LC_CloseBase(pBase,RESET_IDX);
      }
    
      /* Ingen base er åpnet */
      Sys.pForsteBase = NULL;
      Sys.pAktBase = NULL;

   }
}





/*
AR-910920
CH LC_SetDefLpfi                                  Ledig plass mellom grupper
CD ==========================================================================
CD Formål:
CD Legger inn standardverdi for antall tegn ledig plass bak gruppe
CD på .SOS-fil.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD short    ant_tegn   i    Antall tegn ledig plass.
CD
CD Bruk:
CD LC_SetDefLpfi(ant_tegn);
   =============================================================================
*/
SK_EntPnt_FYBA void LC_SetDefLpfi(short ant_tegn)
{
   Sys.sResPlass = ant_tegn;
}


/*
AR-911003
CH LC_InqDefLpfi                             Hent ledig plass mellom grupper
CD ==========================================================================
CD Formål:
CD Henter ut standardverdi for antall tegn ledig plass bak gruppe
CD på .SOS-fil.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD short    ant_tegn   r    Antall tegn ledig plass.
CD
CD Bruk:
CD ant_tegn = LC_InqDefLpfi();
   =============================================================================
*/
SK_EntPnt_FYBA short LC_InqDefLpfi(void)
{
   return  Sys.sResPlass;
}


/*
AR-911021
CH LC_InqLag                          Finn hvilet lag aktuell gruppe tilhører
CD ==========================================================================
CD Formål:
CD Finn hvilket lag aktuell gruppe tilhører.
CD
CD Parametre:
CD Type            Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD unsigned short *usLag    u    "Lag":  LC_FRAMGR eller LC_BAKGR
CD short           status   r    UT_TRUE = OK, UT_FALSE = Ingen aktuell gruppe
CD
CD Bruk:
CD     status = LC_InqLag(&usLag);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_InqLag(unsigned short *usLag)
{
   /* Er det noen aktuell gruppe? */
   if (Sys.GrId.lNr != INGEN_GRUPPE) {
		*usLag = Sys.GrId.pFil->usLag;
		return UT_TRUE;
   }

   /* Ingen aktuell gruppe */
   return UT_FALSE;
}


/*
AR-920221
CH LC_InqFilLag                              Finn hvilet lag en fil tilhører
CD ==========================================================================
CD Formål:
CD Finn hvilket lag en fil tilhører.
CD
CD Parametre:
CD Type            Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM      *pFil     i    Filpeker
CD unsigned short  usLag    r    "Lag":  LC_FRAMGR eller LC_BAKGR
CD
CD Bruk:
CD     usLag = LC_InqFilLag(pFil);
   ==========================================================================
*/
SK_EntPnt_FYBA unsigned short LC_InqFilLag(LC_FILADM *pFil)
{
   /* LO_TestFilpeker(pFil,"LC_InqFilLag"); */
   LO_TestFilpeker(pFil,"InqFilLag");
   return pFil->usLag;
}


/*
AR-920221
CH LC_SetFilLag                             Velg hvilet lag en fil tilhører
CD ==========================================================================
CD Formål:
CD Velg hvilket lag en fil tilhører.
CD
CD Parametre:
CD Type            Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM      *pFil     i    Filpeker
CD unsigned short  usLag    i    "Lag":  LC_FRAMGR eller LC_BAKGR
CD
CD Bruk:
CD     LC_SetFilLag(pFil,LC_FRAMGR);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_SetFilLag(LC_FILADM *pFil,unsigned short usLag)
{
   short ostat;
   
   LO_TestFilpeker(pFil,"SetFilLag");

   /* Må lagre aktuell gruppe hvis den er på denne filen og er endret */
   //if (pFil == Sys.GrId.pFil  &&  Sys.sGrEndra != END_UENDRA) {
   if (pFil == Sys.GrId.pFil  &&  Sys.GrId.lNr != INGEN_GRUPPE  &&  Sys.sGrEndra != END_UENDRA) {
		LC_WxGr(SKRIV_OPTIMALT);
      Sys.sGrEndra = END_UENDRA;
   }

   /* Tømmer skrivekøa for denne filen */
   LB_Save(pFil);

   /* Steng eventuell åpen fil */
   LO_CloseSos(pFil->pBase);

   if ( usLag == LC_FRAMGR) {
      /* Sjekk at filen kan åpnes med den ønskede aksessen */   
		pFil->pBase->pfSos = UT_OpenFile(pFil->pszNavn,"",UT_UPDATE,UT_OLD,&ostat);

      /* Åpningsfeil */
      if (ostat != UT_OK) {
         char szError[256];
         UT_strerror(szError,256,ostat);
         UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pFil->pszNavn,szError);
         LC_Error(101,"(LC_SetFilLag)",err().tx);

      } else {
         // Husk current filnummer mm
         pFil->pBase->pCurSos = pFil;
         pFil->sAccess = UT_UPDATE;
         pFil->usLag = LC_FRAMGR;

         // Husk antall filer i framgrunn/bakgrunn
         pFil->pBase->sAntFramgrFil++;
         pFil->pBase->sAntBakgrFil--;
      }
   
   } else {
      pFil->sAccess = UT_READ;
      pFil->usLag = LC_BAKGR;
     
      // Husk antall filer i framgrunn/bakgrunn
      pFil->pBase->sAntBakgrFil++;
      pFil->pBase->sAntFramgrFil--;
   }
}


/*
AR-971114
CH LC_Backup                                     Lag backup av gitt SOSI-fil
CD ==========================================================================
CD Formål:
CD Lag backup av gitt SOSI-fil.
CD Kopien legges på en underkatlog med navn "Backup" under den katalogen
CD SOSI-filen ligger på. Kopien navnes "Filnavn.nnn" der nnn er et
CD fortløpende nummer fra 000 og oppover. Det første ledige numret blir brukt.
CD
CD Parametre:
CD Type         Navn          I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM   *pFil           i   Filpeker
CD char        *pszBackupPath  i   Katalognavn for lagring av backup.
CD short        sStatus        r   UT_TRUE = OK
CD                                 UT_FALSE = Feil.
CD
CD Bruk:
CD     sStatus = LC_Backup(pFil, szBackupPath);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_Backup(LC_FILADM *pFil, const char *pszBackupPath)
{
   char drive[_MAX_DRIVE],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
	char szBakFil[_MAX_PATH];
	char szBakKatalog[_MAX_PATH];
   short sIdx;
   UT_INT64 Size;
   
   LO_TestFilpeker(pFil,"Backup");

   /* Må lagre aktuell gruppe hvis den er på denne filen og er endret */
   //if (pFil == Sys.GrId.pFil  &&  Sys.sGrEndra != END_UENDRA) {
   if (pFil == Sys.GrId.pFil  &&  Sys.GrId.lNr != INGEN_GRUPPE  &&  Sys.sGrEndra != END_UENDRA) {
		LC_WxGr(SKRIV_OPTIMALT);
      Sys.sGrEndra = END_UENDRA;
   }

   /* Tømmer skrivekøa for denne filen */
   LB_Save(pFil);

   /* Steng eventuell åpen fil */
   LO_CloseSos(pFil->pBase);
   

   UT_splitpath(pFil->pszNavn,drive,dir,fname,ext);

   /* Opprett katalogen */
   if (pszBackupPath != NULL  &&  *pszBackupPath != '\0') {
      UT_StrCopy(szBakKatalog,pszBackupPath,_MAX_PATH);
   } else {
      UT_makepath(szBakKatalog,drive,dir,"Backup","");
   }
   UT_CreateDir(szBakKatalog);

   /* Lag standard navn */
   for (sIdx=0; sIdx<100; sIdx++) {

      UT_SNPRINTF(ext,_MAX_EXT,".b%02hd",sIdx);
      UT_makepath(szBakFil,"",szBakKatalog,fname,ext);

      /* Kontroller om filen finnes fra før */
      /* (Gjøres ved å prøve å spørre om filens størrelse) */
      if (UT_InqPathSize_i64(szBakFil,&Size) != 0) {
         break;  /* Har funnet et ubrukt navn */
      }
   }

   /* Kopier */
   return UT_CopyFile(pFil->pszNavn,szBakFil, UT_FALSE);
}


/*
AR-910920
CH LC_MaxSkriv                                         Max skriv før lagring
CD ==========================================================================
CD Formål:
CD Setter max antall skriv uten lagring til SOSI-filen.
CD (0 = allt skrives direkte til SOSI-filen.)
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD long     antall     i    Max antall skriv uten lagring til SOSI-filen
CD
CD Bruk:
CD LC_MaxSkriv(antall);
   =============================================================================
*/
SK_EntPnt_FYBA void LC_MaxSkriv(long antall)
{
   Sys.lMaxSkriv = labs(antall);
}


/*
AR-910920
CH LC_InqMaxSkriv                                       Max skriv før lagring
CD ==========================================================================
CD Formål:
CD Spørr etter max antall skriv uten lagring til SOSI-filen.
CD (0 = allt skrives direkte til SOSI-filen.)
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD long     antall     i    Max antall skriv uten lagring til SOSI-filen
CD
CD Bruk:
CD antall = LC_InqMaxSkriv();
   =============================================================================
*/
SK_EntPnt_FYBA long LC_InqMaxSkriv(void)
{
   return Sys.lMaxSkriv;
}


/*	
AR-900924
CH LC_SetNgisModus                                            Velg NGIS modus
CD ==========================================================================
CD Formål:
CD Velger handteringsmåte for grupper som er merket for oppdatering av NGIS.
CD	Standardverdi fra LC_Init er NGIS_NORMAL.
CD
CD Parametre:
CD Type   Navn  I/U  Forklaring
CD --------------------------------------------------------------------------
CD short  modus  i   Behandlingsmåte:
CD						    NGIS_NORMAL  (0) = Vanlig handtering
CD							 NGIS_SPESIAL (1) = Spesialmodus der det er mulig å lese
CD                                       grupper som er merka som sletta.
CD
CD Bruk:
CD LC_SetNgisModus(NGIS_NORMAL);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_SetNgisModus(short modus)
{
   if (modus == NGIS_SPESIAL){
		 Sys.sNGISmodus = NGIS_SPESIAL;
	} else{
       Sys.sNGISmodus = NGIS_NORMAL;
	}
}


/*	
AR-2003-03-31
CH LC_GetNgisModus                                            Hent NGIS modus
CD ==========================================================================
CD Formål:
CD Henter handteringsmåte for grupper som er merket for oppdatering av NGIS.
CD	Standardverdi fra LC_Init er NGIS_NORMAL.
CD
CD Parametre:
CD Type   Navn  I/U  Forklaring
CD --------------------------------------------------------------------------
CD short  modus  r   Behandlingsmåte:
CD						    NGIS_NORMAL  (0) = Vanlig handtering
CD							 NGIS_SPESIAL (1) = Spesialmodus der det er mulig å lese
CD                                       grupper som er merka som sletta.
CD
CD Bruk:
CD modus = LC_GetNgisModus();
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetNgisModus(void)
{
   return Sys.sNGISmodus;
}


/*	
AR-900924
CH LC_GetNgisLag                                               Hent NGIS-LAG 
CD ==========================================================================
CD Formål:
CD Henter NGIS-LAG for gitt fil.
CD Strengen ligger i et felles "returbuffer" for alle get-rutiner i fyba.
CD Dette blir ødelagt ved neste kall til en "get-rutine". For å ta vare på
CD strengen må den kopieres over til egen streng. (Bruk strcpy).
CD
CD Parametre:
CD Type       Navn    I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil     i   Fil det ønskes opplsninger om.
CD char*  pszNgisLag   r   NGIS-lag. 
CD                           Tom streng = ..NGIS-LAG er ikke funnet
CD                           "0"  = Bare leseaksess (..NGIS-LAG 0)
CD
CD
CD Bruk:
CD pszNgisLag = LC_GetNgisLag(pFil);
   ==========================================================================
*/
SK_EntPnt_FYBA char* LC_GetNgisLag(LC_FILADM *pFil)
{
	LO_TestFilpeker(pFil,"LC_GetNgisLag");
   
   UT_StrCopy(retur_str,pFil->szNgisLag,LC_MAX_SOSI_LINJE_LEN);

   return retur_str;
}


/*	
AR-970109
CH LC_SetUtvidModus                                         Velg utvis modus
CD ==========================================================================
CD Formål:
CD Velger handteringsmåte for utvidelse av SOSI-filer.
CD	Standardverdi fra LC_Init er LC_UTVID_SIKKER.
CD
CD Parametre:
CD Type   Navn  I/U  Forklaring
CD --------------------------------------------------------------------------
CD short  modus  i   Behandlingsmåte:
CD						    LC_UTVID_SIKKER (0) = SOSI-filen stenges og filstørrelsen
CD                                          oppdateres etter hver gruppe som er
CD                                          skrevet på slutten av filen.
CD							 LC_UTVID_RASK   (1) = SOSI-filen stenges IKKE etter hver
CD                                          gruppe som er skrevet på slutten
CD                                          av filen.
CD                                          (Må bare brukes i spesielle tilfeller.)
CD
CD Bruk:
CD LC_SetUtvidModus(LC_UTVID_SIKKER);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_SetUtvidModus(short modus)
{
   if (modus == LC_UTVID_SIKKER) {
      Sys.sUtvidModus = LC_UTVID_SIKKER;
   } else{
      Sys.sUtvidModus = LC_UTVID_RASK;
   }
}


/*	
AR-970109
CH LC_GetUtvidModus                                         Hent utvis modus
CD ==========================================================================
CD Formål:
CD Henter valgt handteringsmåte for utvidelse av SOSI-filer.
CD
CD Parametre:
CD Type   Navn  I/U  Forklaring
CD --------------------------------------------------------------------------
CD short  modus  r   Behandlingsmåte:
CD						    LC_UTVID_SIKKER (0) = SOSI-filen stenges og filstørrelsen
CD                                          oppdateres etter hver gruppe som er
CD                                          skrevet på slutten av filen.
CD							 LC_UTVID_RASK   (1) = SOSI-filen stenges IKKE etter hver
CD                                          gruppe som er skrevet på slutten
CD                                          av filen.
CD                                          (Må bare brukes i spesielle tilfeller.)
CD
CD Bruk:
CD short sModus = LC_GetUtvidModus();
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetUtvidModus(void)
{
   return Sys.sUtvidModus;
}


/*
AR-910922
CH LO_AppBaseAdm                                         Legg til ny BaseAdm
CD ==========================================================================
CD Formål:
CD Allokerer en ny BasAdm-tabell.
CD Legger tabellen inn i kjeden av base-adm-tabeller.
CD Velg basen som aktuell base.
CD
CD Parametre:
CD Type        Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_BASEADM * pBase      r   Basepeker.
CD
CD Bruk:
CD pBase = LO_AppBaseAdm();
   =============================================================================
*/
static LC_BASEADM * LO_AppBaseAdm(void)
{
   LC_BASEADM * pBase;

   /*
    * Allokerer og nullstiller minne til blokken
	 */
	pBase = (LC_BASEADM *) UT_MALLOC(sizeof(LC_BASEADM));
	memset(pBase,'\0',sizeof(LC_BASEADM));

	/*
	 * Legger blokken inn i kjeden av baser
	 */
	pBase->pNesteBase = Sys.pForsteBase;
   Sys.pForsteBase = pBase;

   /* Velg basen som aktuell base */
	Sys.pAktBase = pBase;

   return pBase;
}


/*
AR-931110
CH LC_InqCurBase                                              Aktuell base
CD ==========================================================================
CD Formål:
CD Spørr etter aktuell base.
CD
CD Parametre:
CD Type        Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_BASEADM * pBase      r   Basepeker.
CD
CD Bruk:
CD pBase = LC_InqCurBase();
   =============================================================================
*/
SK_EntPnt_FYBA LC_BASEADM * LC_InqCurBase(void)
{
   return  Sys.pAktBase;
}


/*
AR-910924
CH LO_DelBaseAdm                                            Fjern en BaseAdm
CD ==========================================================================
CD Formål:
CD Fjerner tabellen fra kjeden av base-adm-tabeller og frigir minnet.
CD OBS! All aktivitet mot basen må være avsluttet før dette kallet.
CD (Alle sosi-filer må være stengt!)
CD
CD Parametre:
CD Type        Navn     I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_BASEADM * pBase     i   Peker til baseadministrasjonsblokk.
CD short       sStatus   r   UT_TRUE=OK, UT_FALSE=Basen har åpne filer.
CD
CD Bruk:
CD sStatus = LO_DelBaseAdm(pBase);
   =============================================================================
*/
static short LO_DelBaseAdm(LC_BASEADM * pBase)
{
   LC_BASEADM * pB;

   /*
    * Sjekk at basen er tom
    */
   if (pBase->pForsteFil != NULL)  return UT_FALSE;

   /*
	 * Sjekk at alle filer er stengt
    */
   if (pBase->pCurSos != NULL)  fclose(pBase->pfSos);
   if (pBase->pCurRb != NULL)  fclose(pBase->pfRb);

	/*
    * Fjern blokken fra kjeden av Baser
    */

   /* Første base i systemet */   
   if (Sys.pForsteBase != NULL) {
     if (Sys.pForsteBase == pBase) {
        Sys.pForsteBase = pBase->pNesteBase;

     } else {
        /* Skanner til basen forran den aktuelle */
		  pB = Sys.pForsteBase;
        while ((pB->pNesteBase != pBase) && (pB->pNesteBase != NULL)) {
           pB = pB->pNesteBase;
        }

        /* Heng sammen kjeden */
        pB->pNesteBase = pBase->pNesteBase;
     }
   }
   
   /*
    * Frigi minne som var brukt av blokken
	 */
	UT_FREE(pBase);

	return UT_TRUE;
}


/*
AR-910922
CH LC_OpenBase                                                 Åpner ny base
CD ==========================================================================
CD Formål:
CD Åpner en base, nullstiller tabellene.
CD
CD Hvis basen er kladdebase opprettes en SOSI-fil med en gruppe i basen,
CD denne brukes som buffer for les / skriv.
CD Kladdefilen legges på current directory.
CD Kladdebase brukes bare når alle SOSI-filer åpnes med sekvensiell les/skriv.
CD  
CD Den nye basen velges som aktuell base.
CD
CD Parametre:
CD Type        Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD short       sBaseType  i   Basetype. Konstanter definert:
CD                             LC_BASE  = Vanlig base.
CD                             LC_KLADD = Kladdebase. Brukes bare i spesielle
CD                                        tilfeller hvis ingen fil åpnes
CD                                        som LC_BASE_xx.
CD LC_BASEADM * pBase      r   Basepeker.
CD
CD Bruk:
CD pBase = LC_OpenBase(sBaseType);
	==========================================================================
*/
SK_EntPnt_FYBA LC_BASEADM * LC_OpenBase(short sBaseType)
{
	LC_BASEADM * pBase;

	/*
	 * Sjekk at FYBA er initiert og at det er gitt lovlig sBaseType
	 */
	if (fyba_initiert != 1){
		LC_Error(4,"(LC_OpenBase)","");
		exit(2);
	}
	if (sBaseType != LC_BASE  &&  sBaseType != LC_KLADD) {
		LC_Error(1,"(LC_OpenBase)","");
		exit(2);
	}

	/*
	 * Legg til ny baseadm og sett denne som aktuell base
	 */
	pBase = LO_AppBaseAdm();

	/*
	 * Initierer
	 */
	pBase->sType = sBaseType;
	pBase->lAntGr = 0L;
   pBase->sAntFramgrFil = 0;
   pBase->sAntBakgrFil = 0;
	pBase->pForsteFil = NULL;
	pBase->pCurSos = NULL;
   pBase->pfSos = NULL;

	/* Initierer lesebuffer for les mot SOSI-fil */
	pBase->BufAdm.sStatus = LESEBUFFER_TOM;

	/*
	 * Kladdebase ==> Opprett kladde-SOSI-fil og opprett en gruppe i denne
	 */
	if (sBaseType == LC_KLADD) {
		if (! LO_OpenKladd(pBase)) {

         /*
          * Frigir BaseAdm og returnerer hvis det ikke kan Åpnes kladdebase.
          */
         LO_DelBaseAdm(pBase);
         return NULL;
      }
	}

   return pBase;
}


/*
AR-911003
CH LC_SelectBase                                           Velg aktuell base
CD ==========================================================================
CD Formål:
CD Velger ny aktuell base.
CD
CD Parametre:
CD Type        Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_BASEADM * pBase      i   Peker til BasAdm.
CD
CD Bruk:
CD LC_SelectBase(pBase);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_SelectBase(LC_BASEADM * pBase)
{
   Sys.pAktBase = pBase;
}


/*
AR-910922
CH LO_OpenKladd                                              Åpne kladdebase
CD ==========================================================================
CD Formål:
CD Initierer en base for bruk som kladdebase for bare sekvensielle filer,
CD Nullstiller tabellene.
CD Oppretter en gruppe i basen, denne brukes som buffer for les / skriv.
CD Kladdefilen legges på samme directory som indeksfilene.
CD
CD Parametre:
CD Type        Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BASEADM * pBase      i    Basepeker.
CD short       status     r    Status. UT_TRUE=OK, UT_FALSE=Feil ved åpning
CD
CD Bruk:
CD status = LO_OpenKladd(pBase);
   ==========================================================================
*/
static short LO_OpenKladd(LC_BASEADM * pBase)
{
   short status = UT_TRUE;
   short o_stat;
   long snr;
   FILE *kladdefil;
   LC_BGR Bgr;
   char fil[] = "FyKladd.Sos";

	/*
    * Åpner kladde-sosi-filen
    */
   kladdefil = UT_OpenFile(fil,"",UT_UPDATE,UT_UNKNOWN,&o_stat);

                                           /* Åpnet OK */
   if (o_stat == UT_OK){
      ho_New(kladdefil,0,0.0,0.0,0.001,0.001,0.001,-199999.0,-199999.0,1999999.0,1999999.0);
      fclose(kladdefil);
                        /* Nuller styrevariablene */
      pBase->sType = LC_BASE;    /* Åpner midlertidig som base */

      /* Åpner kladde filen */
      if (LC_OpenSos(fil,LC_BASE_FRAMGR,LC_NY_IDX,LC_INGEN_STATUS,
           &(Bgr.pFil),&o_stat)) {

         LC_NyGr(Bgr.pFil,".LINJE",&Bgr,&snr);

         /* Merke for at dette er åpen kladdebase */
			pBase->sType = LC_KLADD;
      
      /* Åpningsfeil */
      } else {   
         UT_DeleteFile(fil);
         char szError[256];
         UT_strerror(szError,256,o_stat);
         UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",fil,szError);
         LC_Error(101,"(LC_OpenKladd)",err().tx);
         status = UT_FALSE;
      }

	/* Åpningsfeil på kladdefilen */
   } else {
      char szError[256];
      UT_strerror(szError,256,o_stat);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",fil,szError);
      LC_Error(101,"(LO_OpenKladd)",err().tx);
      status = UT_FALSE;
   }

	return  status;
}


/*
AR-891204
CH LC_CloseBase                                                   Steng base
CD ==========================================================================
CD Formål:
CD Stenger alle filer i basen, og frigir baseadministrasjonsblokken.
CD Hvis aktuell base blir stengt blir første base i systemet valgt som ny
CD aktuell base.
CD
CD Parametre:
CD Type       Navn   I/U Forklaring
CD --------------------------------------------------------------------------
CD PLCBASEADM pBase   i  Peker tilBaseAdm
CD short      s_stat  i  Slutt-status
CD                       RESET_IDX = Fjern indeksfilene
CD                       SAVE_IDX  = Lagrer indeksfilene.
CD                       ABORT     = Fjerner indeksfilene (ved avbrutt
CD                                   indeks oppbygging).  
CD
CD Bruk:
CD LC_CloseBase(pBase,s_stat);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_CloseBase(LC_BASEADM * pBase,short s_stat)
{
	short sAktBaseSletta = (pBase == Sys.pAktBase);
	
    if (pBase == NULL) {
      LC_Error(101,"(LC_CloseBase)","LC_CloseBase fikk NULL-peker");
      return;
	}

	/*
    * Steng SOSI-filene
    */
   while (pBase->pForsteFil != NULL) {
      LC_CloseSos(pBase->pForsteFil,s_stat);
   }

	/*
	 * Kladdebase ==>  Slett kladdefilen
    */
   if (pBase->sType == LC_KLADD) {
      UT_DeleteFile("FyKladd.Sos");
   }

   /*
    * Frigi base-administrasjonsblokken
    */
   LO_DelBaseAdm(pBase);

	/* Aktuell base er sletta, velg første base som ny aktuell base */
   if (sAktBaseSletta) {
      Sys.pAktBase = Sys.pForsteBase;
   }
}


/*
AR-910922
CH LO_AppFilAdm                                           Legg til ny FilAdm
CD ==========================================================================
CD Formål:
CD Allokerer en ny FilAdm-tabell.
CD Legger tabellen inn i kjeden av fil-adm-tabeller.
CD
CD Parametre:
CD Type        Navn     I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_BASEADM * pBase     i   Base der filen skal ligge.
CD LC_FILADM  *pFil      r   Peker til filadministrasjonsblokk.
CD
CD Bruk:
CD pFil = LO_AppFilAdm();
   =============================================================================
*/
static LC_FILADM *LO_AppFilAdm(LC_BASEADM * pBase)
{
	LC_FILADM *pFil;

   /*
    * Allokerer minne til blokken
	 */
	pFil = (LC_FILADM *) UT_MALLOC(sizeof(LC_FILADM));
	memset(pFil,'\0',sizeof(LC_FILADM));

	/*
    * Legger blokken inn i kjeden av filer
    */
   if (pBase->pForsteFil == NULL) {
      pBase->pForsteFil = pFil;
   } else {
		pBase->pSisteFil->pNesteFil = pFil;
   }

	pBase->pSisteFil = pFil;
   pFil->pNesteFil = NULL;

   /*
    * Husker hvilken base filen tilhører
    */
   pFil->pBase = pBase;

   return pFil;
}


/*
AR-910924
CH LO_DelFilAdm                                              Fjern en FilAdm
CD ==========================================================================
CD Formål:
CD Fjerner en fil fra kjeden av fil-adm-tabeller og frigir minnet.
CD OBS! All aktivitet mot filen og indeksfilene må være avsluttet før dette
CD kallet.
CD szBaseVer settes til '\0', slik at dette kan brukes for å sjekke om en
CD filpeker er lovlig.
CD
CD Parametre:
CD Type        Navn     I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM  *pFil      i   Peker til filadministrasjonsblokk.
CD
CD Bruk:
CD LO_DelFilAdm(pFil);
   =============================================================================
*/
static void LO_DelFilAdm(LC_FILADM *pFil)
{
   LC_FILADM *pF;
	LC_BASEADM * pBase = pFil->pBase;


   /*
    * Fjern blokken fra kjeden av filer
    */

   /* Første fil i basen */   
   if (pBase->pForsteFil == pFil) {
		pBase->pForsteFil = pFil->pNesteFil;
      if (pBase->pSisteFil == pFil) {
         pBase->pSisteFil = NULL;
      }

   } else {
      /* Skanner til filen forran den aktuelle */
      pF = pBase->pForsteFil;
      while (pF->pNesteFil != pFil) {
         pF = pF->pNesteFil;
		}

      /* Heng sammen kjeden */
      pF->pNesteFil = pFil->pNesteFil;
      if (pBase->pSisteFil == pFil) {
         pBase->pSisteFil = pF;
      }
   }

   /*
    * Marker at blokken er frigitt.
    */
	pFil->szBaseVer[0] = '\0';

   
   //UT_FPRINTF(stderr,"Frigir minne til FilAdm for: %s\n",pFil->pszNavn);

   /*
    * Frigi minne som var brukt av blokken
	 */
	if (pFil->pszNavn != NULL)
   {
      UT_FREE(pFil->pszNavn);
      pFil->pszNavn = NULL;
   }

   // OBS! midlertidig?  AR:2004-05-19 
   //memset(pFil,'\0',sizeof(LC_FILADM));

	UT_FREE(pFil);
}


/*
AR-920508
CH LC_OpenSos                                      Åpner og sjekker SOSI-fil
CD ==========================================================================
CD Formål:
CD Åpner en ny fil i aktuell base.
CD Allokerer minne til ny filadministrasjonsblokk og initierer denne.
CD Åpner SOSI-filen og legger navn mm. inn i fil-adm.
CD Leser hodet og tolker det inn i filtabellen.
CD Hode blir ikke generert for nye filer. Dette kan lages med LC_PutGi, eller
CD LC_NyttHode eller kopieres fra annen fil, og skrives med LC_WsGr
CD eller LC_WxGr.
CD
CD Parametre:
CD Type    Navn   I/U  Forklaring
CD --------------------------------------------------------------------
CD char   *fil        i   Filnavn inkl. sti og fil-type
CD                        (Hvis fil-type mangler forutsettes  .SOS)
CD short   sModus     i   Filmodus
CD                        LC_BASE_FRAMGR = Framgrunnsfil
CD                        LC_BASE_BAKGR  = Bakgrunnsfil (Bare les)
CD                        LC_SEKV_LES    = Sekvensiell, les
CD                        LC_SEKV_SKRIV  = Sekvensiell, skriv
CD                        LC_SEKV_UTVID  = Sekvensiell, utvid gammel fil
CD short   sNyIdx     i   Indeksgenerering:
CD                        LC_NY_IDX  = Tvungen nygenerering 
CD                        LC_GML_IDX = Bruk gammel .idx hvis den er OK
CD short   sVisStatus i  Vis indeksoppbygging
CD                        LC_VIS_STATUS   = Vis status
CD                        LC_INGEN_STATUS = Ikke vis status
CD LC_FILADM **pFil   u  Peker til FilAdm blokk. 
CD short  *o_stat     u  Detaljert åpningsstatus:
CD                          0: Åpning og hode OK
CD                         >0: Åpningsfeil feilmelding
CD                         -1: Åpning OK, tom fil / ikke SOSI-fil
CD                         -2: Ikke åpnet, kan ikke bruke append på
CD                             tom fil / ikke sosi-fil
CD                         -3: (LC_CANCEL): Ikke åpnet,
CD                             indeksoppbygging avbrutt med [Esc],
CD                             eller feil på filen.
CD                         -4: (LC_DUBLIKAT): Filen er i basen fra før (pFil)
CD                         -5: (LC_OPPTATT): Filen er åpen i annet program 
CD short   status     r  Åpningsstatus: UT_TRUE = OK
CD                                      UT_FALSE = Feil, (o_stat gir detalj)
CD
CD Bruk:
CD ist=LC_OpenSos(fil,LC_BASE_FRAMGR,LC_NY_IDX,LC_VIS_STATUS,&pFil,&o_stat);
CD ist=LC_OpenSos(fil,LC_SEKV_LES,LC_NY_IDX,LC_INGEN_STATUS,&pFil,&o_stat);
   ==========================================================================
*/

/// <summary><c>LC_OpenSos</c> Åpner og sjekker SOSI-fil <c>FYBA</c> biblioteket.
/// </summary>
/// <param name="fil">Filnavn inkl. sti og fil-type (Hvis fil-type mangler forutsettes  .SOS)</param>
SK_EntPnt_FYBA short LC_OpenSos(const char *fil,short sModus,short sNyIdx,short sVisStatus,
                                LC_FILADM **pFil, short *o_stat)
{
   short sAccess;
   UT_INT64 sluttpos;
   double nv_a,nv_n,oh_a,oh_n;
   char drive[_MAX_DRIVE],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
	char szSosFil[_MAX_PATH];
   LC_FILADM *pFi;
   UT_INT64 Size;
   short sStatus;

   /*
    * Sjekk at FYBA er initiert
    */
   if (fyba_initiert != 1) {
      LC_Error(4,"(LC_OpenSos)","");
      exit(2);
   }
   if (Sys.pForsteBase == NULL) {
		LC_Error(5,"(LC_OpenSos)","");
      exit(2);
   }

   if (Sys.pAktBase->sType == LC_KLADD) {
      if (sModus == LC_BASE_FRAMGR  || sModus == LC_BASE_BAKGR) {
   		LC_Error(106,"(LC_OpenSos)",fil);
         exit(2);
      }
   }

   *o_stat = 0;
   LO_CloseSos(Sys.pAktBase);            /* Steng eventuell åpen fil */

   /*
    * Bygg opp fullstendig filnavn
    */
	UT_FullPath(szSosFil,fil,_MAX_PATH);
   UT_splitpath(szSosFil,drive,dir,fname,ext);
   if (*ext == '\0')  UT_StrCopy(ext, ".sos",_MAX_EXT);
   UT_makepath(szSosFil,drive,dir,fname,ext);
   /* UT_StrUpper(szSosFil); */

   /* UT_FPRINTF(stderr,"Åpner: %s\n",szSosFil); */

   /* Sjekk om filen er i basen fra før */
	if ((*pFil = LC_GetFiNr(szSosFil)) != NULL) {
      *o_stat = LC_DUBLIKAT;
      return UT_FALSE;
   }

   /*
    * Tolk aksess for UT_OpenFile
    */
   if (sModus == LC_BASE_BAKGR  ||  sModus == LC_SEKV_LES) {
      sAccess = UT_READ;
   } else {
      sAccess = UT_UPDATE;
   }

   /*
    * Fil som bare skal leses må finnes fra før.
    */
   if (sModus == LC_SEKV_LES  ||  sModus == LC_BASE_BAKGR) {
      if (UT_InqPathSize_i64(szSosFil,&Size) != UT_OK) {
			*o_stat=-2;
         return UT_FALSE;
      }
   }
   
   /*
    * Sekvensiell utvid krever at filen finnes og at det er lov å skrive.
    */
   if (sModus == LC_SEKV_UTVID) {
      if (UT_InqPathSize_i64(szSosFil,&Size) != UT_OK) {
         *o_stat=-2;
         return UT_FALSE;
      }
   }

   /*
	 * Basefil og gammel indeks, krever at filene finnes.
    */
   if ((sModus == LC_BASE_FRAMGR  &&  sNyIdx == LC_GML_IDX) ||
		 (sModus == LC_BASE_BAKGR   &&  sNyIdx == LC_GML_IDX)) {
      /* Må også sjekke lovlig aksess ? */
      if (UT_InqPathSize_i64(szSosFil,&Size) != UT_OK) {
         sNyIdx = LC_NY_IDX;
      } else {
         if (! LI_TestIdx(szSosFil)) {
            sNyIdx = LC_NY_IDX;
         }
      }
   }

   /*
    * Legg til ny Filadm
    */
   pFi = *pFil = LO_AppFilAdm(Sys.pAktBase);

   /*
    * Initierer
    */
   UT_StrCopy(pFi->szBaseVer,FYBA_IDENT,LC_BASEVER_LEN);
   UT_StrCopy(pFi->szIdxVer,FYBA_INDEKS_VERSJON,5);
	pFi->sSosiVer = FYBA_SOSI_VERSJON;
   UT_StrCopy(pFi->szDato,"*",LC_DATO_LEN);
	pFi->SosiNiv[0] = 0;
	pFi->SosiNiv[1] = 0;
	pFi->pszNavn = (char*)UT_MALLOC(strlen(szSosFil)+1);
	UT_StrCopy(pFi->pszNavn,szSosFil,strlen(szSosFil)+1);
	pFi->sAccess = sAccess;
	pFi->lMaxSnr = NYTT_SNR;   /* Ikke noe akt. snr */
	pFi->lAntGr = 0L;
	pFi->sTegnsett = TS_DOSN8; /* Standard når ikke annet er gitt */
	pFi->n64NesteLedigRbPos = 0;
   *pFi->szNgisLag = '\0';

   pFi->pIdx = NULL;
   pFi->pGeoRN=NULL;

   if (sModus == LC_BASE_FRAMGR) {
      pFi->usLag = LC_FRAMGR;
	} else if (sModus == LC_BASE_BAKGR) {
      pFi->usLag = LC_BAKGR;
   } else {
      pFi->usLag = LC_SEKV;
   }

                                           /* Åpner .SOS-filen */
	pFi->pBase->pfSos = UT_OpenFile(pFi->pszNavn,"",sAccess,UT_OLD,o_stat);

                 /* Ukjent fil med skriveaksess ==> opprett filen */
   if (*o_stat == ENOENT  &&  sAccess == UT_UPDATE){
      pFi->pBase->pfSos = UT_OpenFile(pFi->pszNavn,"",sAccess,UT_UNKNOWN,o_stat);
   }
   pFi->pBase->pCurSos = pFi;

   
   if (*o_stat == UT_OK) {      /* Gammel file er åpnet OK */
                           /* Sjekk at SOSI-filen er OK */
		if (ho_TestSOSI(pFi->pBase->pfSos,&sluttpos) == UT_FALSE){
            *o_stat = -1;                  /* Tom fil */
      }
   
   } else {
      /* Åpningsfeil på SOSI-filen  ==>  avbryter */
      char szError[256];
      UT_strerror(szError,256,*o_stat);
      UT_SNPRINTF(err().tx,LC_ERR_LEN," %s - %s",pFi->pszNavn,szError);
      LC_Error(101,"(LC_OpenSos)",err().tx);
      pFi->pBase->pCurSos = NULL;
      LO_DelFilAdm(pFi);
      *pFil = NULL;
      return UT_FALSE;
   }


   /* Eksisterende fil er åpnet OK, hent tegnsett */
   if (*o_stat == UT_OK) {
      ho_GetTegnsett(pFi->pBase->pfSos,&(pFi->sTegnsett));

   /* Tom fil, pr. def. DOSN8 når ikke gitt annet tegnsett */ 
   } else if (*o_stat == -1) {
		pFi->sTegnsett = TS_DOSN8;
   }

   /* Område */
   if (*o_stat == UT_OK) {
      /* Eksisterende fil er åpnet OK, hent område */
      ho_GetOmr(pFi->pBase->pfSos,&nv_a,&nv_n,&oh_a,&oh_n);
      pFi->Omraade.dMinAust = nv_a;
      pFi->Omraade.dMinNord = nv_n;
      pFi->Omraade.dMaxAust = oh_a;
      pFi->Omraade.dMaxNord = oh_n;

   } else {
      /* Tom fil, pr. def. ingen utstrekning */ 
      pFi->Omraade.dMinAust = pFi->Omraade.dMinNord = (double)LONG_MAX;
      pFi->Omraade.dMaxAust = pFi->Omraade.dMaxNord = (double)LONG_MIN;
   }
   
   /* Filen er åpnet OK */
   if (*o_stat == UT_OK || *o_stat == -1) {

               /* Sett aktuell filposisjon mm. */
      if (sModus == LC_SEKV_UTVID) {
			if (*o_stat == -1) {         /* Kan ikke utvide tom fil */
            *o_stat=-2;
            return UT_FALSE;
         }

         /* Aktuell posisjon settes til slutten av filen */
         pFi->n64AktPos = sluttpos;

         /* ----- Oppdater filtabellen ----- */

         /* ..TRANSPAR */
         pFi->TransMaske = LC_TR_ALLT;
         ho_GetTransEx(pFi->pBase->pfSos,&(pFi->TransMaske),&(pFi->TransPar));
 
         /* Ikke noe akt. snr */
         pFi->lMaxSnr = NYTT_SNR;
         
         /* Kvalitet */
         ho_GetKvalitet(pFi->pBase->pfSos,&(pFi->Kvalitet.sMetode),
                                         &(pFi->Kvalitet.lNoyaktighet),
                                         &(pFi->Kvalitet.sSynbarhet),
                                         &(pFi->Kvalitet.sHoydeMetode),
                                         &(pFi->Kvalitet.lHoydeNoyaktighet));


		} else {                    /* Annen aksess */
                  /* Aktuell posisjon settes til starten av filen */
			pFi->n64AktPos = 0L;
                     /* I dette tilfellet oppdateres filtabellen   */
                     /* når hodet leses/skrives fra/til SOSI-filen */
         /* Denne brukes senere for å sjekke at hode er skrevet til filen */
         pFi->TransPar.dEnhet = 0.0;  
      }
   }

   /*
    * Basefil, handter indeks.
    */
   if (sModus == LC_BASE_FRAMGR  ||  sModus == LC_BASE_BAKGR) {
      
      if (sNyIdx == LC_GML_IDX) {
         // Lagret indeks, les inn indeksfilene
         sStatus = LI_OpenRead(pFi);

         if (sStatus == UT_OK) {
            // Åpnet OK, nullstill prioritetstabellen
            LC_EraseAllPrioritet(pFi);

         } else if (sStatus == LI_OPPTATT) {
            // Filen er åpen i et annet program
            LO_CloseSos(Sys.pAktBase);  // Steng eventuell åpen fil
            LO_DelFilAdm(*pFil);         // Frigir filadministrasjonsblokken
            *pFil = NULL;
            *o_stat = LC_OPPTATT;
            return UT_FALSE;

			} else {
            // Feil indeksversjon, størrelse eller oppdateringstid på SOSI-filen
				// - Må bygge ny indeks
            LI_Close(pFi,RESET_IDX);
            sNyIdx = LC_NY_IDX;

            /*
            * Må initiere deler av fil-adm på nytt.
            */
            pFi->lAntGr = 0L;
            pFi->n64NesteLedigRbPos = 0;
            pFi->lMaxSnr = NYTT_SNR;   /* Ikke noe akt. snr */
           	pFi->SosiNiv[0] = 0;
           	pFi->SosiNiv[1] = 0;
         }
      }


      if (sNyIdx == LC_NY_IDX) {
         LI_OpenInit(pFi);                  /* Initierer LI-systemet */
         LN_InitTab(&(pFi->SosiNavn));      /* Initierer navne-systemet */

			if (*o_stat != -1) {       /* Filen har innhold */
            /* Bygg indekser for filen, m. vising av status */
            pFi->usDataFeil = 0;
            if (! LO_InklSos(pFi,sVisStatus)) {
					/* Indeksoppbygging er avbrutt */
               /* Steng filen */
               LC_CloseSos(pFi,RESET_IDX);
               *pFil = NULL;
               *o_stat = LC_CANCEL;
               return UT_FALSE;
            }

            /* Gi melding om ulovlig referanse */
            if ((pFi->usDataFeil & LC_DATAFEIL_REF) != 0) {
               LC_Error(56,"(LC_OpenSos)",pFi->pszNavn);
            }

            /* Gi melding om ulovlig bue */
            if ((pFi->usDataFeil & LC_DATAFEIL_BUE) != 0) {
               LC_Error(59,"(LC_OpenSos)",pFi->pszNavn);
            }
         }
      }

   /*
    * Sekvensiell fil, initier navnesystemet.
    */
   } else {
      LN_InitTab(&(pFi->SosiNavn));
   }


   // Husk antall filer i framgrunn/bakgrunn
   if (pFi->usLag & LC_FRAMGR)     pFi->pBase->sAntFramgrFil++;
   else if (pFi->usLag & LC_BAKGR) pFi->pBase->sAntBakgrFil++;


   // Initierer filtype
   LC_SetFilType(pFi,LC_FILTYPE_UKJENT);
   return  UT_TRUE;
}


/*
AR-910925
CH LO_ReopenSos                                              Reåpne SOSI-fil
CD ==========================================================================
CD Formål:
CD Åpner på nytt en av filene i filtabellen.
CD
CD Parametre:
CD Type         Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM   *pFil     i    Peker til FilAdm-blokk
CD
CD Bruk:
CD LO_ReopenSos(pFil);
   ==========================================================================
*/
void LO_ReopenSos(LC_FILADM *pFil)
{
   short ostat;

   if (pFil->pBase->pCurSos != pFil) {
      if (pFil->pBase->pCurSos != NULL){     /* Stenger forrige fil */
         fclose(pFil->pBase->pfSos);
      }

      /* Åner filen */
		pFil->pBase->pfSos = UT_OpenFile(pFil->pszNavn,"",pFil->sAccess,UT_OLD,&ostat);

      /* Åpningsfeil */
      if (ostat != UT_OK) {
         LC_Error(6,"(LO_ReopenSos)",pFil->pszNavn);
         exit(2);
      }

      /* Husk current filnummer */
      pFil->pBase->pCurSos = pFil;
   }
}


/*
AR-881027
CH LC_CloseSos                                                Steng SOSI-fil
CD ==========================================================================
CD Formål:
CD Stenger en SOSI-fil, og fjerner den fra basen.
CD
CD Parametre:
CD Type        Navn   I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM  *pFil     i   Peker til FilAdm-blokk
CD short       s_stat  i   Slutt-status
CD                         RESET_IDX = Fjern indeksfilene
CD                         SAVE_IDX  = Lagrer indeksfilene.
CD
CD Bruk:
CD LC_CloseSos(pFil,SAVE_IDX);
   ==========================================================================
*/
SK_EntPnt_FYBA void LC_CloseSos(LC_FILADM *pFil,short s_stat)
{
   LC_BGR Bgr,AktBgr;
   short ngi,linje_nr;
   long nko;
   unsigned short info;
   char szSosiNiv[10];
   LC_BOKS * pB;


   /* LO_TestFilpeker(pFil,"LC_CloseSos"); */
	LO_TestFilpeker(pFil,"CloseSos");

	/*
    * Hvis aktuell gruppe er på denne filen
    */
   if (Sys.GrId.lNr != INGEN_GRUPPE  &&  Sys.GrId.pFil == pFil) {

      if (pFil->pBase->sType == LC_BASE) {
         /* Hvis gruppen er endra, skriv den til filen */
         if (Sys.sGrEndra != END_UENDRA) {
            if (LC_WxGr(SKRIV_SOSI) == UT_FALSE) {
               // Indeksfilene ikke er brukbare
               s_stat = RESET_IDX;
            }
         }
      }
      /* Vis at det ikke er noen aktuell gruppe lenger */
      Sys.GrId.lNr = INGEN_GRUPPE;
   }

   // Husk antall filer i framgrunn/bakgrunn
   if (pFil->usLag & LC_FRAMGR)     pFil->pBase->sAntFramgrFil--;
   else if (pFil->usLag & LC_BAKGR) pFil->pBase->sAntBakgrFil--;

   /*
	 * Sikrer oppdatering av sosi-filen
    */
   if (pFil->pBase->sType == LC_BASE) {
      LB_Save(pFil);
   }
   
   /* Oppdater ..SOSI-NIVÅ i fil-hodet */
	if (pFil->SosiNiv[1] > pFil->SosiNiv[0]) {
      AktBgr = Sys.GrId;
      Bgr.pFil = pFil;
      Bgr.lNr = 0;
      LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info);

      UT_SNPRINTF (szSosiNiv, 10, "%d", (int)pFil->SosiNiv[1]);
      ngi = LC_PutGP("..SOSI-NIVÅ", szSosiNiv, &linje_nr);
      LC_WxGr(SKRIV_SOSI);

      if (AktBgr.lNr != INGEN_GRUPPE) { 
         LC_RxGr(&AktBgr,LES_OPTIMALT,&ngi,&nko,&info);
      } else {
         Sys.GrId = AktBgr;
      }
   }
   
   /* UT_FPRINTF(stderr,"Stenger: %s\n",pFil->pszNavn); */
   LO_CloseSos(pFil->pBase);

   /*
   * Indeks skal alltid fjernes for kladdefilen i kladdebase
   */
   if (pFil->pBase->sType == LC_KLADD  &&  (pFil->usLag & LC_FRAMGR)) {
      s_stat = RESET_IDX;
   }

   /*
    * Fjern indeksfilene / lagre indeks og steng filer
    */
   if (pFil->usLag != LC_SEKV) {
		LI_Close(pFil,s_stat);
   }

   /*
    * Frigi fil-administrasjonsblokken
    */
   LO_DelFilAdm(pFil);

   /* Oppdaterer omskrevet boks for basen */
   if (Sys.pAktBase != NULL) { /* er basen fortsatt aapent? */
     pFil = Sys.pAktBase->pForsteFil;
     pB = &(Sys.pAktBase->Omraade);
     pB->dMinAust = pB->dMinNord = (double)LONG_MAX;
     pB->dMaxAust = pB->dMaxNord = (double)LONG_MIN;
     while (pFil != NULL) {
        /* Er filen i rett lag? (Hoper over sekvensielle filer) */
        if (pFil->usLag & (LC_FRAMGR | LC_BAKGR)) {
           /* Filen inneholder data */
           if (pFil->pGeoRN != NULL) {
              pB->dMinAust = min(pB->dMinAust,pFil->Omraade.dMinAust);
              pB->dMinNord = min(pB->dMinNord,pFil->Omraade.dMinNord);
              pB->dMaxAust = max(pB->dMaxAust,pFil->Omraade.dMaxAust);
              pB->dMaxNord = max(pB->dMaxNord,pFil->Omraade.dMaxNord);
           }
        }
        pFil = pFil->pNesteFil;
     }
   }
}


/*
AR:2009-03-20
CH LC_FcloseSos                             Steng åpen SOSI-fil i filsystemet
CD ==========================================================================
CD Formål:
CD Denne rutinen brukes til å sikre at en fil er oppdatert og stengt i filsystemet,
CD slik at SOSI-filen kan leses fra andre program.
CD 
CD OBS!
CD Stenger bare filen i filsystemet.
CD Filen er fortsatt åpen i basen.
CD FYBA åpner automatisk filen på nytt når det er behov for dette.
CD
CD Parametre:
CD Type        Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM  *pFil     i   Peker til FilAdm-blokk
CD
CD Bruk:
CD LC_FcloseSos(pFil);
==========================================================================
*/
SK_EntPnt_FYBA void LC_FcloseSos(LC_FILADM *pFil)
{
   LO_TestFilpeker(pFil,"LC_FcloseSos");

   // Må lagre aktuell gruppe hvis den er på denne filen og er endret
   if (pFil == Sys.GrId.pFil  &&  Sys.GrId.lNr != INGEN_GRUPPE  &&  Sys.sGrEndra != END_UENDRA) {
      LC_WxGr(SKRIV_OPTIMALT);
      Sys.sGrEndra = END_UENDRA;
   }

   // Tømmer skrivekøa for denne filen
   LB_Save(pFil);

   // Steng eventuell åpen fil
   LO_CloseSos(pFil->pBase);
}


/*
AR-911001
CH LO_CloseSos                                        Steng current SOSI-fil
CD ==========================================================================
CD Formål:
CD Stenger current SOSI-fil i basen.
CD
CD Parametre:
CD Type         Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_BASEADM *  pBase    i    Peker til BaseAdm-blokk
CD
CD Bruk:
CD LO_CloseSos(pBase);
	==========================================================================
*/
void LO_CloseSos(LC_BASEADM * pBase)
{
   if (pBase->pCurSos != NULL) {
      fclose(pBase->pfSos);     
      pBase->pCurSos = NULL;
   }
}


/*
AR-890510
CH LO_BeFt                                       Beregn omregnings-parametre
CD ==========================================================================
CD Formål:
CD Oppdaterer filtabellen med hodeinformasjoner fra aktuell gruppe,
CD som må være SOSI-filens hode.
CD
CD Parametre:
CD Type         Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM   *pFil     i    Peker til FilAdm-blokk
CD
CD Bruk:
CD LO_BeFt(pFil);
   ==========================================================================
*/
void LO_BeFt(LC_FILADM *pFil)
{
   double nva,nvn,oha,ohn;
   short lin;
   char *cp;


   /* Transformasjonsparametre */
   pFil->TransMaske = LC_TR_ALLT;
   LC_GetTransEx(&(pFil->TransMaske),&(pFil->TransPar));

   /* Område */
   LC_GetOmr(&nva,&nvn,&oha,&ohn);
   pFil->Omr.dMinAust = nva;
   pFil->Omr.dMinNord = nvn;
   pFil->Omr.dMaxAust = oha;
   pFil->Omr.dMaxNord = ohn;

	/* Kvalitet */
   LC_GetKvalitet(&(pFil->Kvalitet.sMetode),
                  &(pFil->Kvalitet.lNoyaktighet),
                  &(pFil->Kvalitet.sSynbarhet),
                  &(pFil->Kvalitet.sHoydeMetode),
						&(pFil->Kvalitet.lHoydeNoyaktighet));

   /* Tegnsett */
   LC_GetTegnsett(&(pFil->sTegnsett));

   /* SOSI-VERSJON */
   lin=2;
   if ((cp = LC_GetGP("..SOSI-VERSJON",&lin,Sys.pGrInfo->ngi)) != NULL) {
      pFil->sSosiVer = (short)(strtod(cp,&cp)*100.0);
   } else {
      pFil->sSosiVer = FYBA_SOSI_VERSJON;
   }

   // DATO
   lin=2;
   if ((cp = LC_GetGP("..DATO",&lin,Sys.pGrInfo->ngi)) != NULL) {
      UT_StrCopy(pFil->szDato,cp,LC_DATO_LEN);
   } else {
      UT_StrCopy(pFil->szDato,"*",LC_DATO_LEN);
   }

   /* SOSI-NIVÅ */
   lin=2;
   if ((cp = LC_GetGP("..SOSI-NIVÅ",&lin,Sys.pGrInfo->ngi)) != NULL) {
      pFil->SosiNiv[0] = (char)(strtol(cp,&cp,10));
   } else {
      pFil->SosiNiv[0] = 0;
   }

   /* ..NGIS-LAG */
   UT_StrCopy(pFil->szNgisLag,LH_GetNgisLag(),LC_NGISLAG_LEN);
}


/*
AR-911003
CH LC_GetBaOm                                                Hent baseområde
CD ==========================================================================
CD Formål:
CD Henter baseområdet for aktuell base (Sum av filhodene).
CD Sekvensielle filer regnes ikke med.
CD
CD Parametre:
CD Type           Navn    I/U   Forklaring
CD --------------------------------------------------------------------------
CD unsigned short usLag    i   Velg hvilke "lag" det skal søkes i.
CD                               LC_FRAMGR og /eller LC_BAKGR
CD                               (Bruk "|" for å kombinere.)
CD double        *nva      u    Nedre venstre øst
CD double        *nvn      u    Nedre venstre nord
CD double        *oha      u    Øvre høyre øst
CD double        *ohn      u    Øvre høyre nord
CD short          sStatus  r    UT_TRUE=OK, UT_FALSE=ingen fil
CD
CD Bruk:
CD sStatus = LC_GetBaOm(LC_FRAMGR,&nva,&nvn,&oha,&ohn);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetBaOm(unsigned short usLag,double *nva,double *nvn,double *oha,
                 double *ohn)
{
   double na,nn,oa,on;
   LC_FILADM *pFil;
	short sAntall = 0;

   *nvn = LONG_MAX; 
   *nva = LONG_MAX;
   *ohn = LONG_MIN;
   *oha = LONG_MIN;

   LC_InitNextFil(&pFil);
	while (LC_NextFil(&pFil,usLag)) {
      sAntall++;
      if (LC_GetFiOm(pFil,&na,&nn,&oa,&on)) {
         *nva = min (*nva, na);
         *nvn = min (*nvn, nn);
         *oha = max (*oha, oa);
         *ohn = max (*ohn, on);
      }
   }
   
   return (sAntall > 0);
}


/*
AR-910928
CH LC_GetFiOm                                       Hent område fra fil-hode
CD ==========================================================================
CD Formål:
CD Hent område for en SOSI-fil i basen.
CD Fungerer ikke mot sekvensielle filer.
CD
CD Parametre:
CD Type       Navn  I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil   i   Peker til FilAdm
CD double     nva    u   Nedre venstre øst
CD double     nvn    u   Nedre venstre nord
CD double     oha    u   Øvre høyre øst
CD double     ohn    u   Øvre høyre nord
CD short      ist    r   Status (UT_TRUE=OK, UT_FALSE=sekvensiell fil)
CD
CD Bruk:
CD ist = LC_GetFiOm(pFil,&nva,&nvn,&oha,&ohn);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_GetFiOm(LC_FILADM *pFil,double *nva,double *nvn,double *oha,double *ohn)
{
	/* LO_TestFilpeker(pFil,"LC_GetFiOm"); */
   LO_TestFilpeker(pFil,"LC_GetFiOm");

   if (pFil->usLag != LC_SEKV) {
      *nva = pFil->Omr.dMinAust;
      *nvn = pFil->Omr.dMinNord;
      *oha = pFil->Omr.dMaxAust;
      *ohn = pFil->Omr.dMaxNord;
      return UT_TRUE;
   }

   return UT_FALSE;
}


/*
AR-911001
CH LO_InklSos                                       Inkluder SOSI-fil i base
CD ==========================================================================
CD Formål:
CD Hjelperutine for LC_OpenSos.
CD Bygger indeks og klargjør filen for basen.
CD Prosessen kan avbrytes med <ESC>, og rutinen returnerer da UT_FALSE.
CD Aktuell gruppe blir brukt under prosessen, og etterpå er det ingen
CD aktuell gruppe tilgjengelig.
CD
CD Parametre:
CD Type       Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *pFil        i   Peker til FilAdm
CD short      sVisStatus  i   Vis indeksoppbygging
CD                               LC_VIS_STATUS   = Vis status
CD                               LC_INGEN_STATUS = Ikke vis status
CD short      sStatus     r   Status: UT_TRUE=OK, UT_FALSE=avbrutt eller feil 
CD
CD Bruk:
CD ant_bgr = LO_InklSos(pFil,LC_VIS_STATUS);
   ==========================================================================
*/
static short LO_InklSos(LC_FILADM *pFil,short sVisStatus)
{
   unsigned long ulLedigPlass;
   short siste,ngi,nivaa;
   long nko;
	unsigned short info;
   UT_INT64 pos,fpos;
   long lGrNr;
   LC_BGR Bgr;
   LC_GRTAB_LINJE *pForrigeGrInfo,*pGrInfo;
   LC_BOKS * pB;
   short avbrutt = 0;
   double lengde_faktor = 0.0;
   short sStatus = UT_TRUE;
   short pnr = 1;

   // Hvis aktuell gruppe er endret, skriv den
   if (Sys.GrId.lNr != INGEN_GRUPPE  &&  Sys.sGrEndra != END_UENDRA) {
      LC_WxGr(SKRIV_OPTIMALT);
   }

   LO_ReopenSos(pFil);    // Sikkrer at filen er åpen - Kan ha blitt stengt i LC_WxGr

   Sys.GrId.pFil = pFil;
  
   // ----- Søk fram til .HODE
   if (ho_FinnHode(pFil->pBase->pfSos, &pos) == UT_TRUE) {

      // ----- Bygg indeks
      /* Sikkrer at ny lesing startes */
      _fseeki64(pFil->pBase->pfSos,pos,SEEK_SET);

      /* Ledetekst */
      if (sVisStatus == LC_VIS_STATUS) {
         LC_StartMessage(pFil->pszNavn);
		   fpos = _ftelli64(pFil->pBase->pfSos);
         _fseeki64(pFil->pBase->pfSos,-1,SEEK_END);
         lengde_faktor = 100.0 / (double)_ftelli64(pFil->pBase->pfSos);
         _fseeki64(pFil->pBase->pfSos,fpos,SEEK_SET);
      }

      pForrigeGrInfo = NULL;

      do {
         if (pFil->lAntGr < LC_MAX_GRU) {        /* Klargjør for lesing */

			   /* Sjekk ledig diskplass  for SOSI-filer */

            if (pFil->sAccess == UT_UPDATE) {
			      UT_InqAvailSize(pFil->pszNavn,&ulLedigPlass);
			      if (ulLedigPlass < ((unsigned long)LC_MAX_KOORD * (unsigned long)120)) {
                  /* Disken er snart full */
                  LC_Error(93,"(LO_InklSos)",pFil->pszNavn);
               }
            }

            Sys.GrId.lNr = pFil->lAntGr++;   /* (Nr er 1 mindre enn antall) */

			   Sys.pGrInfo = LI_AppGrt(pFil,Sys.GrId.lNr);


            Sys.pGrInfo->sosi_st = pos;



            /* Les gruppen */
            siste = LB_RGru(pFil,pos,&pos);

            /* Buffer for GetPP er ødelagt */
            Sys.sPibufStatus = LC_PIBUF_TOM;
      
			   /* Grafisk vising av mengde lest */
            if (sVisStatus == LC_VIS_STATUS) {
               LC_ShowMessage((double)pos * lengde_faktor);
            }

            /* Gruppe lest OK */
            if ( ! siste) {
               LC_OppdaterEndret(O_GINFO);
               nivaa = 2;
				   LC_GetCurKvalitet(Sys.GrId.pFil,&nivaa,pnr,
                              &Sys.pGrInfo->Kvalitet.sMetode,
                              &Sys.pGrInfo->Kvalitet.lNoyaktighet,
                              &Sys.pGrInfo->Kvalitet.sSynbarhet,
                              &Sys.pGrInfo->Kvalitet.sHoydeMetode,
                              &Sys.pGrInfo->Kvalitet.lHoydeNoyaktighet);

               /* Oppdater buffer-fil */
               Sys.GrId.pFil->lSisteGrRb = Sys.GrId.lNr;
               Sys.pGrInfo->rb_st = Sys.GrId.pFil->n64NesteLedigRbPos;
               Sys.pGrInfo->rb_forrige_gr = Sys.GrId.lNr - 1L;
               Sys.pGrInfo->rb_neste_gr = INGEN_GRUPPE;
               Sys.pGrInfo->ulPrior[0] = 0UL;
				   Sys.pGrInfo->ulPrior[1] = 0UL;
				   Sys.pGrInfo->ulPrior[2] = 0UL;
				   Sys.pGrInfo->ulPrior[3] = 0UL;

               if (pForrigeGrInfo != NULL) {
                  pForrigeGrInfo->rb_neste_gr = Sys.GrId.lNr;
               }

				   LI_WriteRb(Sys.GrId.pFil,Sys.pGrInfo->rb_st,Sys.Ginfo.pszTx,Sys.pGrInfo->ulGiLen,
                          Sys.pdAust, Sys.pdNord, Sys.pInfo, Sys.pGrInfo->nko,
                          Sys.pszPinfo, Sys.pGrInfo->ulPiLen);
 
               Sys.GrId.pFil->n64NesteLedigRbPos +=
                     (UT_INT64)LI_BerBufferLen(Sys.pGrInfo->ulGiLen,Sys.pGrInfo->nko,Sys.pGrInfo->ulPiLen);

               pForrigeGrInfo = Sys.pGrInfo;

              /* Nuller merking */
               LI_PutBt(pFil,Sys.GrId.lNr,0L);

               LS_Indx();          /* Serienummer tabeller */
               LR_Indx();          /* Geografisk indeks */

            /* ".SLUTT" er lest */
			   } else {
               pFil->n64AktPos = pos;
               pFil->lAntGr--;
			   }

         } else {                     /* For mange grupper, tab. sprengt */
            UT_SNPRINTF(err().tx,LC_ERR_LEN," %ld",pFil->lAntGr+1L);
            LC_Error(2,"(LO_InklSos)",err().tx);
            exit(99);
         }

         avbrutt = LC_Cancel();     /* <ESC> avbryter lesing */
      } while ( !siste  &&  !avbrutt);


                     /* Bygg indeks for grupper med referanser */
      if (! avbrutt) {          /* Lesing er avbrutt */
         lengde_faktor = 100.0 / (double)pFil->lAntGr;

         Bgr.pFil = pFil;
         for (lGrNr=0; lGrNr<pFil->lAntGr && !avbrutt; lGrNr++) {
            if (sVisStatus == LC_VIS_STATUS) {
				   LC_ShowMessage((double)lGrNr * lengde_faktor);
            }

            /* Sjekk om gruppen har referanser */
            pGrInfo = LI_GetGrt(pFil,lGrNr);
            if ((pGrInfo->info & GI_REF) != 0) {
               /* Les inn og beregn omskreven boks medregnet refererte grupper */
               Bgr.lNr = lGrNr;
               if (LC_RxGr(&Bgr,LES_OPTIMALT,&ngi,&nko,&info) != INGEN_GRUPPE) { 
                  LR_IndxFlate();
               }
            }

            avbrutt = LC_Cancel();     /* <ESC> avbryter lesing */
         }
      }

      Sys.GrId.lNr = INGEN_GRUPPE;               /* Ingen aktuell gruppe */
      Sys.sGrEndra = END_UENDRA;

      /* Oppdaterer omskrevet boks for basen */
      if ( ! avbrutt) {          /* Lesing er avbrutt */
         pFil = Sys.pAktBase->pForsteFil;
         pB = &(Sys.pAktBase->Omraade);
         pB->dMinAust = pB->dMinNord = (double)LONG_MAX;
         pB->dMaxAust = pB->dMaxNord = (double)LONG_MIN;
         while (pFil != NULL) {
            /* Er filen i rett lag? (Hoper over sekvensielle filer) */
            if (pFil->usLag & (LC_FRAMGR | LC_BAKGR)) {
               /* Filen inneholder data */
               if (pFil->pGeoRN != NULL) {
                  pB->dMinAust = min(pB->dMinAust,pFil->Omraade.dMinAust);
                  pB->dMinNord = min(pB->dMinNord,pFil->Omraade.dMinNord);
                  pB->dMaxAust = max(pB->dMaxAust,pFil->Omraade.dMaxAust);
                  pB->dMaxNord = max(pB->dMaxNord,pFil->Omraade.dMaxNord);
               }
            }
            pFil = pFil->pNesteFil;
         }
      }

      if (avbrutt) {          /* Lesing er avbrutt */
         LC_Error(10,"(LO_InklSos)","");
		   pFil->lAntGr = 0L;
         sStatus = UT_FALSE;
      }

      if (sVisStatus == LC_VIS_STATUS) {
         LC_EndMessage();
      }
   }

   return sStatus;
}


/*
AR-911001
CH LC_GetFiNr                                                 Get fil nummer
CD ==========================================================================
CD Formål:
CD Sjekker alle filer i aktuell base om noen av den har det gitte filnavnet.
CD
CD Parametre:
CD Type        Navn     I/U  Forklaring
CD --------------------------------------------------------------------------
CD char        fil_navn  i   Filnavn
CD LC_FILADM  *pFil      r   Peker til FilAdm for filen. (NULL = ukjent fil)
CD
CD Bruk:
CD pFil = LC_GetFiNr(fil_navn);
   ==========================================================================
*/
SK_EntPnt_FYBA LC_FILADM *LC_GetFiNr(const char *fil_navn)
{
   LC_FILADM *pFil;
   char drive[_MAX_DRIVE],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
   char szSosFil[_MAX_PATH];


   /*
    * Bygg opp fullstendig filnavn
    */
   UT_FullPath(szSosFil,fil_navn,_MAX_PATH);
   UT_splitpath(szSosFil,drive,dir,fname,ext);
   if (*ext == '\0')  UT_StrCopy(ext,".sos",_MAX_EXT);
	UT_makepath(szSosFil,drive,dir,fname,ext);

   for (pFil=Sys.pAktBase->pForsteFil; pFil!=NULL; pFil=pFil->pNesteFil) {
      /* Rett filnavn? ==> */
      if (UT_FilnavnCmp(pFil->pszNavn,szSosFil) == 0)   return pFil;
   }

   return  NULL;
}


/*
AR-911001
CH LC_GetFiNa                                                   Hent filnavn
CD ==========================================================================
CD Formål:
CD Henter filnavnet for en fil i basen. Fungerer både for basefiler
CD og for sekvensielle filer.
CD OBS! Hvis du skal endre på filnavnet må du først kopiere det 
CD      til en lokale varialel.
CD
CD Parametre:
CD Type        Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM  *pFil       i    Peker til FilAdm
CD char       *fil_navn   r    Peker til filnavn 
CD
CD Bruk:
CD fil_navn = LC_GetFiNa(pFil);
   ==========================================================================
*/
SK_EntPnt_FYBA char *LC_GetFiNa(LC_FILADM *pFil)
{
   /* LO_TestFilpeker(pFil,"LC_GetFiNa"); */
   LO_TestFilpeker(pFil,"GetFiNa");

   return pFil->pszNavn;
}


/*
AR-920729
CH LO_TestFilpeker                            Sjekk at en filpeker er gyldig
CD ==========================================================================
CD Formål:
CD Sjekk at en filpeker er gyldig.
CD
CD Parametre:
CD Type        Navn         I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM * pFil          i    Peker til FilAdm
CD char       *pszRutineNavn i    Melding (rutinenavnet for kallende rutine)
CD
CD Bruk:
CD LO_TestFilpeker(pFil,"LC_OpenBase");
   ==========================================================================
*/
void LO_TestFilpeker(LC_FILADM *pFil,const char *pszRutineNavn)
{
   char szTx[100];


   if (pFil == NULL  ||  *(pFil->szBaseVer) != 'F') { 

      UT_SNPRINTF(szTx,100," %s,  (Filpeker: %p)",pszRutineNavn,pFil); 
      LC_Error(105,"(TestFilpeker)",szTx);
   }
}


/*
AR-921008
CH LC_ErFilBase                                 Sjekker om en fil er i basen
CD ==========================================================================
CD Formål:
CD Sjekker om en fil er i basen.
CD
CD Parametre:
CD Type    Navn   I/U  Forklaring
CD --------------------------------------------------------------------
CD char   *fil     i   Filnavn inkl. sti og fil-type
CD                     (Hvis fil-type mangler forutsettes  .SOS)
CD short   status  r   Status: UT_TRUE = Filen er med i basen.
CD                             UT_FALSE = Filen er IKKE med i basen.
CD
CD Bruk:
CD ist = LC_ErFilBase(fil);
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_ErFilBase(const char *fil)
{
   char drive[_MAX_DRIVE],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
   char szSosFil[_MAX_PATH];

   /*
    * Bygg opp fullstendig filnavn
    */
   UT_FullPath(szSosFil,fil,_MAX_PATH);
   UT_splitpath(szSosFil,drive,dir,fname,ext);
   if (*ext == '\0')  UT_StrCopy(ext,".sos",_MAX_EXT);
   UT_makepath(szSosFil,drive,dir,fname,ext);

   /* Sjekk om filen er i basen fra før */
   if (LC_GetFiNr(szSosFil) != NULL)  return UT_TRUE;  /* Er i basen */

   return UT_FALSE;  /* Er ikke i basen */
}
 


/*
AR-940923
CH LC_ErKoordsysLik                                      Sjekker KOORDSYS
CD =======================================================================
CD Formål:
CD Sjekk at alle filene i basen har samme koordinatsystem.
CD
CD Parametre:
CD Type    Navn   I/U  Forklaring
CD -----------------------------------------------------------------------
CD short   status  r   Status: UT_TRUE = KOORDSYS er lik.
CD                             UT_FALSE = KOORDSYS er IKKE lik.
CD
CD Bruk:
CD ist = LC_ErKoordsysLik();
	=======================================================================
*/
SK_EntPnt_FYBA short LC_ErKoordsysLik(void)
{
   short sKoSys = 0;
   short sFilNr = 0;
   LC_FILADM *pFil;

   /* Sjekk at alle filene i basen har samme koordinatsystem */
   LC_InitNextFil(&pFil);

   while (LC_NextFil(&pFil,LC_FRAMGR | LC_BAKGR))
   {
      sFilNr++;
      if (sFilNr == 1)
      {
         sKoSys = pFil->TransPar.sKoordsys;
      } 

      else if (pFil->TransPar.sKoordsys != sKoSys)
      {
         LC_FILADM *pF;

         // Skriv filnavn og koordinatsystem til loggfilen

         UT_FPRINTF(stderr,"Det er funnet filer med ulikt koordinatsystem:\n");

         LC_InitNextFil(&pF);
         while (LC_NextFil(&pF,LC_FRAMGR | LC_BAKGR))
         {
            UT_FPRINTF(stderr,"   \"%s\" : %hd\n",pF->pszNavn,pF->TransPar.sKoordsys);
         }
         return  UT_FALSE;
      }
   }

   return  UT_TRUE;
}



/*
AR-940923
CH LC_ErVertdatumLik                                   Sjekker VERT-DATUM
CD =======================================================================
CD Formål:
CD Sjekk at alle filene i basen har samme VERT-DATUM.
CD
CD Parametre:
CD Type    Navn   I/U  Forklaring
CD -----------------------------------------------------------------------
CD short   status  r   Status: UT_TRUE = VERT-DATUM er lik.
CD                             UT_FALSE = VERT-DATUM er IKKE lik.
CD
CD Bruk:
CD ist = LC_ErVertdatumLik();
	=======================================================================
*/
SK_EntPnt_FYBA short LC_ErVertdatumLik(void)
{
   char szVertdatHref[7];
   char szVertdatDref[6];
   char szVertdatFref[6];
   char szVertdatHtyp[2];

   bool bForsteFil = true;
   LC_FILADM *pFil;

   /* Sjekk at alle filene i basen har samme VERT-DATUM */
   LC_InitNextFil(&pFil);

   while (LC_NextFil(&pFil,LC_FRAMGR | LC_BAKGR))
   {
      // Sjekker bare filer med VERT-DATUM gitt i filhodet
      // (Overser standardverdien)
      if (strlen(pFil->TransPar.szVertdatHref) > 0)
      {
         if ( bForsteFil)
         {
            UT_StrCopy(szVertdatHref, pFil->TransPar.szVertdatHref, 7);
            UT_StrCopy(szVertdatDref, pFil->TransPar.szVertdatDref, 6);
            UT_StrCopy(szVertdatFref, pFil->TransPar.szVertdatFref, 6);
            UT_StrCopy(szVertdatHtyp, pFil->TransPar.szVertdatHtyp, 2);
            bForsteFil = false;
         } 

         else if (UT_StrCmpi(pFil->TransPar.szVertdatHref,szVertdatHref) != 0  ||
                  UT_StrCmpi(pFil->TransPar.szVertdatDref,szVertdatDref) != 0  ||
                  UT_StrCmpi(pFil->TransPar.szVertdatFref,szVertdatFref) != 0  ||
                  UT_StrCmpi(pFil->TransPar.szVertdatHtyp,szVertdatHtyp) != 0    )
         {
            LC_FILADM *pF;

            // Skriv filnavn og VERT-DATUM til loggfilen

            UT_FPRINTF(stderr,"Det er funnet filer med ulikt VERT-DATUM:\n");

            LC_InitNextFil(&pF);
            while (LC_NextFil(&pF,LC_FRAMGR | LC_BAKGR))
            {
               UT_FPRINTF(stderr,"   \"%s\" : \"%s %s %s %s\"\n",
                         pF->pszNavn,
                         pF->TransPar.szVertdatHref,
                         pF->TransPar.szVertdatDref,
                         pF->TransPar.szVertdatFref,
                         pF->TransPar.szVertdatHtyp);
            }
            return  UT_FALSE;
         }
      }
   }

   return  UT_TRUE;
}


/*
AR:2000-11-30
CH LC_SetEndringsstatus             Setter endringsstatus for aktuell gruppe
CD ==========================================================================
CD Formål:
CD Setter endringsstatus for aktuell gruppe.
CD
CD NB! Denne rutinen bør normalt ikke brukes av vanlige klient-program!
CD
CD
CD Parametre:
CD Type   Navn      I/U  Forklaring
CD --------------------------------------------------------------------------
CD short  sStatus    i   Kode for endring:
CD                         END_UENDRA  0   Ikke endra
CD                         END_KOPI    1   Endra ved totalkopi fra annen gruppe
CD                         END_ENDRA   2   Endra ved normal Put fra program
CD
CD Bruk:
CD LC_dg_SetEndringsstatus(END_KOPI);
=============================================================================
*/
SK_EntPnt_FYBA void LC_SetEndringsstatus(short sStatus)
{
   Sys.sGrEndra = sStatus;
}

/*
JAØ:2001-03-06
CH LC_SetFilType								Setter filtype for en sosifil
CD ==========================================================================
CD Formål:
CD Setter filtype for en fil.
CD
CD Denne rutinen er primært tenkt brukt i GabEdit hvor det er behov for å 
CD definere flere typer arbeidsfil.
CD
CD Parametre:
CD Type         Navn   I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *  pFil	   i   Peker til filen
CD short        type    i   Filtypen som skal settes
CD                             LC_FILTYPE_UKJENT
CD                             LC_FILTYPE_INAKTIV
CD                             LC_FILTYPE_GAB_EIENDOM
CD                             LC_FILTYPE_GAB_ADRESSE
CD                             LC_FILTYPE_GAB_BYGNING
CD                             LC_FILTYPE_BYGG
CD                             LC_FILTYPE_DEK
CD                             LC_FILTYPE_DEK_ENDRING
CD                             LC_FILTYPE_GRUNNKRETS
CD                             LC_FILTYPE_POSTKRETS
CD                             LC_FILTYPE_SKOLEKRETS
CD                             LC_FILTYPE_KIRKESOGN
CD                             LC_FILTYPE_TETTSTED
CD                             LC_FILTYPE_VALGKRETS
CD
CD Bruk:
CD LC_SetFilType(pFil,type);
=============================================================================
*/
SK_EntPnt_FYBA void LC_SetFilType(LC_FILADM *pFil, short sType)
{  
   LO_TestFilpeker(pFil,"SetFilType");
	pFil->sFilType = sType;
}

/*
JAØ:2001-03-06
CH LC_GetFilType                               Henter filtype for en sosifil
CD ==========================================================================
CD Formål:
CD Finner filtypen for en fil.
CD
CD Parametre:
CD Type         Navn   I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM *  pFil	   i   Peker til filen
CD short        type    r   Filtypen som skal settes
CD                             LC_FILTYPE_UKJENT
CD                             LC_FILTYPE_INAKTIV
CD                             LC_FILTYPE_GAB_EIENDOM
CD                             LC_FILTYPE_GAB_ADRESSE
CD                             LC_FILTYPE_GAB_BYGNING
CD                             LC_FILTYPE_BYGG
CD                             LC_FILTYPE_DEK
CD                             LC_FILTYPE_DEK_ENDRING
CD                             LC_FILTYPE_GRUNNKRETS
CD                             LC_FILTYPE_POSTKRETS
CD                             LC_FILTYPE_SKOLEKRETS
CD                             LC_FILTYPE_KIRKESOGN
CD                             LC_FILTYPE_TETTSTED
CD                             LC_FILTYPE_VALGKRETS
CD
CD Bruk:
CD type = LC_GetFilType(pFil);
=============================================================================
*/
SK_EntPnt_FYBA short LC_GetFilType(LC_FILADM *pFil)
{
   LO_TestFilpeker(pFil,"GetFilType");
	return pFil->sFilType;
}


/*
AR:2004-05-03
CH LC_GetIdxPath                               Hent katalog for ny indeksfil
CD ==========================================================================
CD Formål:
CD Hent katalognavn for ny indeks. For detaljer se under LC_SetIdxPath.
CD
CD Parametre:
CD Type         Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD const char  *pszIdxPath   r    Katalog for indeks
CD
CD Bruk:
CD const char *pszIdxPath = LC_GetIdxPath();
   ==========================================================================
*/
SK_EntPnt_FYBA const char *LC_GetIdxPath(void)
{
   return Sys.szIdxPath;
}


/*
AR:2011-05-31
CH LC_SetIdxPath                               Velg katalog for ny indeksfil
CD ==========================================================================
CD Formål:
CD Velg katalognavn for ny indeks. Indeksfilene for en SOSI-fil legges som
CD en underkatalog under den gitte katalogen. Underkatalogen har samme navn
CD som SOSI-filen. Hvis det er valgt spesiell plassering av indeksfilene blir
CD disse alltid slettet når SOSI-filen stenges.
CD OBS! Ingen SOSI-filer kan være åpne når indekskatalog velges.
CD
CD Parametre:
CD Type        Navn       I/U Forklaring
CD --------------------------------------------------------------------------
CD const char *pszIdxPath  i  Katalog for indeks
CD                            "" = Tom streng betyr at indeksfilene legges på en
CD                                 underkatalog under katalogen der SOSI-filen ligger
CD                                 (default).
CD                            "katalognavn" = Indeksfilene legges på en
CD                                            underkatalog under denne katalogen.
CD short       status      r  Status: UT_TRUE = OK
CD                                    UT_FALSE = Feil, feilmelding er gitt.
CD
CD Bruk:
CD status = LC_SetIdxPath("C:\\kart\\test");
   ==========================================================================
*/
SK_EntPnt_FYBA short LC_SetIdxPath(const char *pszIdxPath)
{
   if (LC_InqAntFiler(LC_FRAMGR|LC_BAKGR) == 0)
   {
      // Handter TEMP spesielt
      /*
      CD "TEMP" = Indeksfilene legges på brukerens temp-katalog.
      // 2011-05-31: Handtering av "TEMP" er fjernet.
      if (_strcmpi(pszIdxPath,"TEMP") == 0)
      {
         char szBuffer[_MAX_PATH];
         size_t returnValue;
        // Hent katalognavn fra environment
         getenv_s( &returnValue, szBuffer, _MAX_PATH, "TEMP");
         if(returnValue == 0)
         {
            getenv_s( &returnValue, szBuffer, _MAX_PATH, "TMP");
         }
         if(returnValue == 0)
         {
            Sys.szIdxPath[0] = '\0';
            return UT_FALSE;
         }
         else
         {
            UT_StrCopy(Sys.szIdxPath,szBuffer,_MAX_PATH);
            if (Sys.szIdxPath[strlen(Sys.szIdxPath)-1] != UT_SLASH)  UT_StrCat(Sys.szIdxPath,UT_STR_SLASH,_MAX_PATH);
         }
      }
      else 
      */
      if (*pszIdxPath == '\0')
      {
         Sys.szIdxPath[0] = '\0';
      }

      else
      {
         UT_StrCopy(Sys.szIdxPath,pszIdxPath,_MAX_PATH);
         if (Sys.szIdxPath[strlen(Sys.szIdxPath)-1] != UT_SLASH)  UT_StrCat(Sys.szIdxPath,UT_STR_SLASH,_MAX_PATH);

         // Opprett katalogen hvis den ikke finnes fra før
         UT_CreateDir(Sys.szIdxPath);
      }

      return UT_TRUE;
   }

   return UT_FALSE;
}
