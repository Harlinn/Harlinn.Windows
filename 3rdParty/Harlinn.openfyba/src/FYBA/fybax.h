/* == AR-991012 =========================================================== */
/*   STATENS KARTVERK  -  FYSAK-PC                                          */
/*   Fil: fybax.h                                                           */
/*   Innhold: Interne prototyper for fysak-pc                               */
/*            Def. av typer og bufferstørrelser                             */
/*            Definisjon av filtabellen, ringbuffer mm.                     */
/* ======================================================================== */

#pragma once

#include "fyba.h"


/* ======================================================= */
/*  Definerer konstanter                                   */
/* ======================================================= */
#ifndef _FYBAX_DEFINED

#   define  FYBA_IDENT  "FYBA - G2.0  2011-03-10"
#   define  FYBA_INDEKS_VERSJON  "G009"
#   define  FYBA_SOSI_VERSJON  400

 /* Definerer PI */
//#   ifndef PI
////#      define PI  (3.14159265358979324)
//#      define PI  (3.14159265358979323846)
//#   endif

/* --- Konstant for testing av likhet på desimaltall -- */
#define LC_ACCY  1.0E-9


 /* Basetype */
 /* #define LC_START_KLADD       2  */  /* Åpning av kladdebase */
 /* (LC_BASE og LC_KLADD er definert i FYBA.H) */

 /* Filtabell */
 /* #define NO_OPEN_SOS   -1 */  /* Ingen åpen SOSI-fil */

 /* Kommando til LB_Wgru */
#   define KONTROLLER_PLASS    1   /* Bare kontroller plass, (ikke skriv SOSI) */
#   define SKRIV_VANLIG        2   /* Skriv til SOSI, vanlig */
#   define SKRIV_SISTE         3   /* Skriv til SOSI, med .SLUTT og bytepointer */

  /* Diverse */
#   define NYTT_SNR              -1L  /* Startverdi for akt.snr i filtabellen */

#   define NY_SOSI_ST            -1L  /* Start.sosi når gruppe ikke er skrevet */
#   define NY_RB_ST              -1L  /* Start.rb når gruppe ikke er skrevet */
#   define NY_UI_ST              -1L  /* Start.UI når gruppe ikke er skrevet */

/*
 * Diverse for intern mellomlagring av hele PINFO
 */
 /* Statusverdier */
#   define LC_PIBUF_TOM   0
#   define LC_PIBUF_OK    1
#   define LC_PIBUF_FULL  2
 /* Ant. tegn i buffer */
#   define LC_MAX_PIBUF_TEGN  LC_MAX_SOSI_LINJE_LEN
 /* Ant linjer i tabell med pekere til startposisjoner i strengen */
#   define LC_MAX_PIBUF_LIN 50

#   define LI_LESEFEIL           -1  // Filen er åpen i annet program 
#   define LI_OPPTATT            -2  // Filen er åpen i annet program 
#   define LI_FEIL_INDEKSVERSJON -3  // Feil indeksversjon 
#   define LI_FEIL_STORRELSE     -4  // Feil størrelse på SOSI-filen 
#   define LI_FEIL_OPPDATTID     -5  // Feil oppdateringstid på SOSI-filen 


#   define _FYBAX_DEFINED
#endif


/* ================================================ */
/*  Definerer data-strukturer                       */
/* ================================================ */

/* Lesebuffer */
/* Konstanter for set_brukt */
#define SET_UBRUKT 0
#define SET_BRUKT  1

/* Konstanter for sStatus */
#define LESEBUFFER_TOM   0          /* (Tom eller ikke ajour) */
#define LESEBUFFER_OK    1

 /* Verdier for cur_type */
                          /*  >= 0 : Gruppenavn,linjenummer i navnetab. */
#define  LEST_KOORD  -1   /* Koordinatlinje */
#define  LEST_BLANK  -2   /* "blank linje" (!!!, mm) */
#define  LEST_GINFO  -3   /* GINFO */
#define  LEST_KOM    -4   /* Kommentar-linje */


/* Felles streng for feilmeldinger */
#define LC_ERR_LEN 300
typedef struct dLC_FEILMELDING {
   short nr;
   short strategi;
   char tx[LC_ERR_LEN];
} LC_FEILMELDING;


/* UTVALG */
/*
 // Utvalgskommandoer 
#define U_OG          1     // ..OG 
#define U_ELLER       2     // ..VELG og ..ELLER


 // Utvalgsmetoder
#define U_IKKE         0     //  !     Ikke (Tilslag når SOSI-navnet     
                             //             ikke finnes. Bare GINFO.)    
#define U_ALLE         1     //  AL    Alle                              
#define U_FRATIL       2     //  <>    Fra-til                           
#define U_UTENFOR      3     //  ><    Utenfor                           
#define U_MINDRE       4     //  <     Mindre-enn                        
#define U_STORRE       5     //  >     Større-enn                        
#define U_DELELIG      6     //  /     Delelig-med, eventuellt med       
                             //        sjekk på om restverdi er 2. verdi 
#define U_UDELELIG     7     //  !/    Ikke-delelig-med                  
#define U_CONTEIN      8     //  ()    Inneholder                        
#define U_IKKECONTEIN  9     //  !()   Inneholder ikke (Tilslag når      
                             //        denne navn og verdi kombinasjonen 
                             //        ikke finnes)                      
#define U_LIK         10     //  =     Lik                               
#define U_IKKEVALGT   11     //  IV    Ikke valgt (Tilslag når gruppen   
                             //        ikke er tegnet ennå. Kombineres   
                             //        med SOSI-navnet "..*")            
#define U_IKKELIK     12     //  !=    Ikke lik (Tilslag når denne       
                             //        navn og verdi kombinasjonen ikke  
                             //        finnes)                           
#define U_FLERE       13     //  FL    Flere (Tilslag når SOSI-navnet    
                             //        forekommer flere ganger.)         
#define U_IKKEFLERE   14     //  !FL   Ikke flere enn (Tilslag når       
                             //        SOSI-navnet IKKE forekommer       
                             //        flere ganger enn gitt antall.)    



 // Parametertyper 
#define U_TALL          1     // Heltall     
#define U_FLYT          2     // Flyttall    
#define U_ALFA          9     // Tekststreng 
*/

   /* GINFO i minne */
typedef struct dLC_GINFO_BUFFER {
   char *pszTx;         /* GINFO buffer */
   unsigned long ulOfset[LC_MAX_GINFO]; /* Peker til starten av hver GINFO-linje */
} LC_GINFO_BUFFER;


/*
 *!--------------------------------------------------------------!
 *! Systemadministrasjon                                         !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_SYSTEMADM {
   char   szBaseVer[LC_BASEVER_LEN];  // Versjon og dato for aktuell versjon av FYBA
   char   szIdxVer[5];                // Indeksfil-versjon

   short  sResPlass;  // Ant. tegn reserve plass bak ny gruppe
   long   lMaxSkriv;  // Max antall skriv uten lagring til SOSI-filen
   long   lAntSkriv;  // Antall skriv siden siste lagring til SOSI
   short  sNGISmodus; // Behandlingsmåte for grupper med NGIS-oppdateringsflagg
   short  sUtvidModus; // Handteringsmåte for utvidelse av SOSI-filer.
   char   szIdxPath[_MAX_PATH]; //Katalognavn for ny indeks.
   LB_LESEBUFFER BufAdm;         // Lesebuffer mot SOSI-fil-hode

   LC_NAVNETABELL  SosiNavn;     // Navnetabell (brukes av HO-rutinene)

   /* Div opplysninger om aktuell gruppe */
   short sGrEndra;         // Er aktuell gruppe endra?
   LC_BGR GrId;            // Gruppens identifikasjon
   LC_GRTAB_LINJE *pGrInfo;  // Peker til gruppetabell-linje
   
   /* Aktuell gruppe i minne */
   /* GINFO i minne */
   LC_GINFO_BUFFER Hode;     // Hodebuffer
   unsigned short usHoLen;   // Ant tegn i hodebuffer
   LC_GINFO_BUFFER Ginfo;    // GINFO-buffer
   double *pdAust;    // Øst koordinat
   double *pdNord;    // Nord koordinat
   LB_INFO * pInfo;    // Høyde,KP og PINFO-peker
   char *pszPinfo;    // PINFO buffer

   /* Søkebuffer for PINFO */
   long lPibufPnr;                 // Punktnummer for data i buffer
   short sPibufAntPi;               // Antall elementer brukt i PIbuf
   char cPibuf[LC_MAX_PIBUF_TEGN];  // Kopi av PINFO, (for raskere søking)
   short sPibufStatus;              // Status for bruken av cPibuf
   /* Peker til startposisjoner i cPibuf for hver PINFO */
   char *pcPibufNavn[LC_MAX_PIBUF_LIN];   // Peker til SOSI-navn
   char *pcPibufVerdi[LC_MAX_PIBUF_LIN];  // Peker til verdi

   unsigned short usMerkRefGr;  // Flagg for å vise om refererte grupper skal merkes ved utvalg

   LC_BASEADM * pForsteBase;   // Peker til første base-adm.
   LC_BASEADM * pAktBase;      // Peker til aktuell base-adm.
} LC_SYSTEMADM;


/* ======================================================= */
/*  Funksjonsdefinisjoner for fyho.c                       */
/* ======================================================= */

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylb.c                       */
/* ======================================================= */
void    LB_Save(LC_FILADM *pFil);
void    LB_NyRp(void);
short   LB_RGru(LC_FILADM *pFil,UT_INT64 start,UT_INT64 *slutt);
void    LB_Swap(void);
char   *LB_FormaterEnhet(char *streng,short sStrengMaxLen,const char *SosiNavn,double enhet);
void    LB_ClGr (void);
short   LB_WGru (short strategi,long fra_punkt,long antall,
                 LC_FILADM *pFil,UT_INT64 ffipos,UT_INT64 *lfipos);
short   LB_Plass(LC_FILADM *pFil, UT_INT64 start, UT_INT64 *neste);
short   LB_WriteLine (FILE *fil,short sTegnsett,const char *tx);
short   LB_GetSet(FILE *fil,LB_LESEBUFFER *plb,LC_NAVNETABELL * pNavn);


/* ======================================================= */
/*  Funksjonsdefinisjoner for fyli.c                       */
/* ======================================================= */
short   LI_TestIdx(char *szSosFil);
short   LI_OpenInit(LC_FILADM *pFil);
short   LI_OpenRead(LC_FILADM *pFil);
void    LI_Close(LC_FILADM *pFil,short s_stat);
void    LI_SaveAdm(LC_FILADM *pFil);

LC_R_LEAF * LI_GetGeo(LC_FILADM *pFil,long linje);
/*  void   LI_PutGeo(LC_FILADM *pFil,long linje,LC_GEOSOK_BOKS *geop); */

long   LI_GetSnr(LC_FILADM *pFil,long lSnr);
void   LI_PutSnr(LC_FILADM *pFil,long lSnr,long lGrNr);

LC_GRTAB_LINJE * LI_GetGrt(LC_FILADM *pFil,long linje);
LC_GRTAB_LINJE * LI_AppGrt(LC_FILADM *pFil,long linje);

unsigned long   LI_GetBt(LC_FILADM *pFil,long linje);
void   LI_PutBt(LC_FILADM *pFil,long linje,unsigned long bt_val);

void    LI_SetBt(LC_FILADM *pFil,long lGrNr,short kolonne);
void    LI_ClrBt(LC_FILADM *pFil,long lGrNr,short kolonne);
short   LI_InqBt(LC_FILADM *pFil,long lGrNr,short kolonne);
void    LI_EraseBt(short fra_kol,short til_kol);

void LI_WriteRb(LC_FILADM *pFil, UT_INT64 n64FilPos,
                char *pszGi, unsigned long ulGiLen,
                double *pdAust, double *pdNord,
                LB_INFO * pInfo, long lNko,
                char *pszPi, unsigned long ulPiLen);
void LI_ReadRb(LC_FILADM *pFil, UT_INT64 n64FilPos,
               char *pszGi, unsigned long ulGiLen,
               double *pdAust, double *pdNord,
               LB_INFO * pInfo, long lNko,
               char *pszPi, unsigned long ulPiLen);
void LI_ReadCoordRb(LC_FILADM *pFil, UT_INT64 n64FilPos, unsigned long ulGiLen,
               double *pdAust, double *pdNord,
               LB_INFO * pInfo, long lNko,
               char *pszPi, unsigned long ulPiLen);
long LI_BerBufferLen(unsigned long ulGiLen,long lNko,unsigned long ulPiLen);


/* ======================================================= */
/*  Funksjonsdefinisjoner for fyln.c                       */
/* ======================================================= */
void  LN_InitTab(LC_NAVNETABELL *pLn);
short LN_Enhet(LC_NAVNETABELL *pLn,char *ginfo_linje);
short LN_EnhetHoyde(LC_NAVNETABELL *pLn,char *ginfo_linje);
short LN_EnhetDybde(LC_NAVNETABELL *pLn,char *ginfo_linje);
short LN_TestOy(char *ginfo_linje);
short LN_PakkNavn(LC_NAVNETABELL *pLn,const char *navn,short *navn_nr,
                short *ant_par);
short LN_FinnNavn(LC_NAVNETABELL *pLn,char *navn,short *navn_nr);
char *LN_GetNavn(LC_NAVNETABELL *pLn,short navn);
char *LN_VisNavn(LC_NAVNETABELL *pLn,short navn);
void  LN_TolkKvalitet(char *pszParameter,short *psMetode,long *plNoyaktighet,
                      short *psSynbarhet,short *psHoydeMetode,long *plHoydeNoyaktighet);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyls.c                       */
/* ======================================================= */
void    LS_Indx(void);
void    LS_PutSn(LC_FILADM *pFil,long lGrNr,long lSnr);
char *  LS_VisSn(LC_FILADM *pFil,long lin);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylr.c                       */
/* ======================================================= */
/* Indeksoppbygging */
void  LR_Indx(void);
void  LR_IndxFlate(void);
short LR_PTstGruppe(LC_BGR * pBgr,double a,double n);
void LR_R_Delete(LC_R_LEAF * pCL);
LC_R_LEAF * LR_InsertGeo(LC_FILADM *pFil,long lNr,LC_BOKS * pB);
void LR_R_FrigiGren(LC_R_NODE *pRN);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylo.c                       */
/* ======================================================= */
LC_FEILMELDING& err();
void   LO_CloseSos(LC_BASEADM *pBase);
void   LO_ReopenSos(LC_FILADM *pFil);
void   LO_BeFt(LC_FILADM *pFil);
void   LO_TestFilpeker(LC_FILADM *pFil,const char *pszRutineNavn);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylx.c                       */
/* ======================================================= */
void   LX_PutSn(long snr);
void   LX_CreGiPeker(LC_GINFO_BUFFER *pGinfo,short ngi);
char  *LX_GetGi(short lin_nr);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylp.c                       */
/* ======================================================= */

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylh.c                       */
/* ======================================================= */
char* LH_GetNgisLag(void);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyho.c                       */
/* ======================================================= */
void  ho_New(FILE *fil,short koosys,double origo_a,double origo_n,
             double enhet,double enhet_h,double enhet_d,
             double nv_a,double nv_n,double oh_a,double oh_n);
short ho_TestSOSI(FILE *fil,UT_INT64 *sluttpos);
char *ho_GetVal(FILE *fil,const char *sosi_navn,short *sett_nr);
short ho_GetKvalitet(FILE *fil,short *psMetode,long *plNoyaktighet,
                     short *psSynbarhet,short *psHoydeMetode,long *plHoydeNoyaktighet);
short ho_GetTrans(FILE *fil,short *koosys,double *origo_a,
                  double *origo_n,double *enhet,double *enhet_h,double *enhet_d);
short ho_GetTransEx(FILE *pFil,unsigned short *pusMaske, LC_TRANSPAR * pTrans);
short ho_GetOmr(FILE *fil,double *nv_a,double *nv_n,double *oh_a,double *oh_n);
short ho_GetTegnsett(FILE *pfFil,short *psTegnsett);
short ho_SjekkTegnsett(FILE *fil,short *psTegnsett);
short ho_FinnHode(FILE *pFil, UT_INT64 *lHodepos);

