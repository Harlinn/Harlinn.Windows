/******************************************************************************
*
* STATENS KARTVERK  -  FYSAK
*
* Filename: fyba.h
*
* Content: Prototyper for rutiner for les/skriv av SOSI-fil.
*
* Copyright (c) 1990-2011 Statens kartverk
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
******************************************************************************/

#pragma once

//
// Når FYBA brukes som DLL, defineres FYBA_DLL_IMPORTS
// Når FYBA brukes som lib er det ikke nødvendig med noen spesiell definisjon.
// (Når FYBA skal kompileres/lages som DLL defineres FYBA_DLL_EXPORTS)
//

#include <stdio.h>
#include <stdlib.h>

#include <fygm.h>
#include <fyut.h>


/* ======================================================= */
/*  Definerer konstanter                                   */
/* ======================================================= */
   /* Max-verdier for basen */
#define LC_MAX_GRU        10000000  /* Max grupper i en base */
#define LC_MAX_GINFO          6000  /* Max linjer GINFO i en gruppe */
#define LC_MAX_GINFO_BUFFER 250000  /* GINFO-buffer */
#define LC_MAX_KOORD         90000  /* Max antall koordinater i en gruppe */
#define LC_MAX_PINFO_BUFFER 250000  /* PINFO-buffer */
#define LC_MAX_ANT_PRIOR       128  /* Max antall prioriteter */
#define LC_DATO_LEN              9  /* Max lengde dato (inkl. '\0') */
#define LC_BASEVER_LEN          50  /* Max lengde av szBaseVer (inkl. '\0') */
#define LC_MAX_SOSINAVN_LEN     50  /* Max lengde for SOSI-navn (inkl. '\0') */
#define LC_MAX_NAVN            500  /* Max linjer i navnetabellen (pr. fil) */
#define LC_NGISLAG_LEN          50  /* Max lengde av NGIS-LAG fra filhodet */
#define LC_MAX_SOSI_LINJE_LEN 1024  /* Max linjelengde for lesing fra SOSI-filen */
#define LC_MAX_OBJTYPE_LEN      33  // Max lengde av objettypenavn (inkl. '\0')

#define  LC_INTERNT_TEGNSETT TS_ISO8859
        

   /* Konstanter for basetype */
#define  LC_KLADD  3   /* Kladdebase */
#define  LC_BASE   1   /* Vanlig base */

   /* Konstanter for åpning av eksisterende base */
#define  UKJENT_BASE     -1
#define  FEIL_VERSJON    -2
#define  IKKE_STENGT     -3
#define  IDX_MANGLER     -4
#define  IDX_FEIL_DATO   -5
#define  SOS_MANGLER     -6
#define  SOS_FEIL_DATO   -7
#define  SOS_FEIL_AKSESS -8

	/* Konstanter for LC_CloseBase */
#define RESET_IDX   0   /* Fjern indeksfilene */
#define SAVE_IDX    1   /* Lagrer indeksfilene */

   /* Konstanter for LC_OpenSos */
#define LC_BASE_FRAMGR 1  /* Framgrunnsfil i basen */
#define LC_BASE_BAKGR  2  /* Bakgrunnsfil i basen (Bare les) */
#define LC_SEKV_LES    3  /* Sekvensiell, les */
#define LC_SEKV_SKRIV  4  /* Sekvensiell, skriv */
#define LC_SEKV_UTVID  5  /* Sekvensiell, utvid gammel fil */

#define LC_NY_IDX      1  /* Tvungen nygenerering */
#define LC_GML_IDX     0 /* Bruk gammel .idx hvis den er OK */

#define LC_VIS_STATUS   1  /* Vis status under indeksoppbygging */
#define LC_INGEN_STATUS 0  /* Ikke vis status */

   /* Lag i basen */
#define LC_SEKV     0x0001   /* Sekvensiell fil */
#define LC_BAKGR    0x0002   /* Bakgrunnsfil i base */
#define LC_FRAMGR   0x0004   /* Framgrunnsfil i base */

   /* Status fra LC_OpenSos */
#define LC_CANCEL   -3  // Avbrutt med [Esc], eller lesefeil
#define LC_DUBLIKAT -4  // Filen er i basen fra før
#define LC_OPPTATT  -5  // Filen er åpen i annet program 

	/* Konstanter for LC_SetNgisModus */
#define NGIS_NORMAL   0   /* Vanlig modus */
#define NGIS_SPESIAL  1   /* Spesialmodus der det er mulig å finne og
                                lese grupper som er merka som sletta */

	/* Konstanter for LC_SetUtvidModus */
#define LC_UTVID_SIKKER 0 /* SOSI-filen stenges og filstørrelsen oppdateres */
                          /* etter hver gruppe som er skrevet på slutten av filen */
#define LC_UTVID_RASK   1 /* SOSI-filen stenges IKKE etter hver oppdatering*/

   /* Konstanter til QueryGP mfl. */
#define LC_HODE   1
#define LC_GINFO  2
#define LC_PINFO  4

/* Konstanter til bruk ved kombinert flatesøk. JAØ-20000516 */
#define LC_INGEN 0
#define LC_NOEN  1
#define LC_ALLE  2

   /* Gruppenummer når det ikke er noen aktuell gruppe */
#define INGEN_GRUPPE  -1L    /* bgr når det ikke er noen akt. gruppe */

   /* Lesemetode for LC_RxGr */
#define LES_OPTIMALT   0     /* Les mest effektivt base/SOSI */
#define LES_SOSI       1     /* Les alltid fra SOSI-filen */

   /* Skrivemetode for LC_WxGr */
#define SKRIV_OPTIMALT 0     /* Skriv mest effektivt kø/SOSI */
#define SKRIV_SOSI     1     /* Skriv direkte til SOSI-filen */

   /* Handteringmetode for NGIS-nøkkel for LC_CopyGr */
#define OPPDATER_NGIS 0  /* NGIS-nøkkel oppdateres i henhold til hodet i filen det kopieres til */
#define BEVAR_NGIS    1  /* NGIS-nøkkel bevares uforandret i kopien */

   /* Manglende kvalitetsopplysninger */
#define KVAL_MET_UNDEF  -1   /* Udefinert metode */
#define KVAL_MET_STD    -2   /* Standard metode fra nivå over */

#define KVAL_NOY_UNDEF  -1L  // Udefinert nøyaktighet. -  OBS! Denne skal utgå
#define KVAL_NOY_STD    -2L  /* Standard nøyaktighet fra nivå over */
#define KVAL_NOY_UKJENT  999999L  // Ukjent nøyaktighet 


#define KVAL_SYN_GOD     0   /* Godt synlig */
#define KVAL_SYN_UNDEF  -1   /* Udefinert synbarhet */
#define KVAL_SYN_STD    -2   /* Standard synbarhet fra nivå over */

   /* For LC_GetTH og LC_PutTH */
   /* Konstant for å si at punktet ikke har høyde */
   /* OBS! Denne må stemme med definisjonen i filen port.h */
#ifndef HOYDE_MANGLER
#   define HOYDE_MANGLER        -9999.999   /* Høyde mangler i punktet */
#endif

#define KOORD_MANGLER           -9999.999   /* Koordinat mangler i punktet */

   /* Gruppeinformasjon */
#define GI_PINFO     ((unsigned short)0x0001) /* Har PINFO */
#define GI_NAH       ((unsigned short)0x0002) /* Gruppen har høyde informasjon (..NØH) */
#define GI_KP        ((unsigned short)0x0004) /* Har knutepunkt (...KP n) */
#define GI_REF       ((unsigned short)0x0008) /* Har referanser (.. :n) */
#define GI_OY_REF    ((unsigned short)0x0010) /* Har referanser med øy */
#define GI_SLETTA    ((unsigned short)0x0020) /* Er sletta (merka som sletta) */
#define GI_NGIS      ((unsigned short)0x0040) /* Er tatt ut fra NGIS */
#define GI_NAD       ((unsigned short)0x0080) /* Har dybde informasjon (..NØD) */
#define GI_READ_ONLY ((unsigned short)0x0100) /* Bare leseaksess (kan ikke endres) */

   /* Avgrensing av brukttabellen */
#define  BT_MIN_BT    0       /* Første kolonne i brukttabellen */
#define  BT_MAX_BT   31       /* Siste kolonne i brukttabellen */
#define  BT_MIN_USER  1       /* Første tilgjengelig for brukerprogram */
#define  BT_MAX_USER 26       /* Siste tilgjengelig for brukerprogram */
   /* Spesielle posisjoner i brukttabellen */
#define  BT_SKRKO     0       /* I skrivekø */
#define  BT_REFBOX   27       /* Referanser er brukt i omskrevet boks */
#define  BT_X        28       /* Reserve systemposisjon */
#define  BT_SNRSOK   29       /* Funnet ved SNR-søk */
#define  BT_GISOK    30       /* Funnet ved GINFO-søk */
#define  BT_GEOSOK   31       /* Funnet ved geografisk søk */

   /* Logiske operasjoner mellom kolonner i brukttabellen */
#define BC_AND      0
#define BC_OR       1
#define BC_COPY     2
#define BC_INVERT   3
#define BC_EXCHANGE 4


   /* Konstanter for get og put referansenummer */
#define START_OY   9999999L      /* Start øy */
#define SLUTT_OY  -9999999L      /* Slutt øy */

   /* Konstanter for GetArrayTK() */
#define HENT_FORRFRA  1          /* Vanlig */
#define HENT_BAKFRA  -1          /* Snu buferet */

/* UTVALG */

// Utvalgskommandoer 
#define LC_U_OG          1     // ..OG 
#define LC_U_ELLER       2     // ..VELG og ..ELLER


 // Utvalgsmetoder
#define LC_U_IKKE         0     //  !     Ikke (Tilslag når SOSI-navnet     
                             //             ikke finnes. Bare GINFO.)    
#define LC_U_ALLE         1     //  AL    Alle                              
#define LC_U_FRATIL       2     //  <>    Fra-til                           
#define LC_U_UTENFOR      3     //  ><    Utenfor                           
#define LC_U_MINDRE       4     //  <     Mindre-enn                        
#define LC_U_STORRE       5     //  >     Større-enn                        
#define LC_U_DELELIG      6     //  /     Delelig-med, eventuellt med       
                                //        sjekk på om restverdi er 2. verdi 
#define LC_U_UDELELIG     7     //  !/    Ikke-delelig-med                  
#define LC_U_CONTEIN      8     //  ()    Inneholder                        
#define LC_U_IKKECONTEIN  9     //  !()   Inneholder ikke (Tilslag når      
                                //        denne navn og verdi kombinasjonen 
                                //        ikke finnes)                      
#define LC_U_LIK         10     //  =     Lik                               
#define LC_U_IKKEVALGT   11     //  IV    Ikke valgt (Tilslag når gruppen   
                                //        ikke er tegnet ennå. Kombineres   
                                //        med SOSI-navnet "..*")            
#define LC_U_IKKELIK     12     //  !=    Ikke lik (Tilslag når denne       
                                //        navn og verdi kombinasjonen ikke  
                                //        finnes)                           
#define LC_U_FLERE       13     //  FL    Flere (Tilslag når SOSI-navnet    
                                //        forekommer flere ganger.)         
#define LC_U_IKKEFLERE   14     //  !FL   Ikke flere enn (Tilslag når       
                                //        SOSI-navnet IKKE forekommer       
                                //        flere ganger enn gitt antall.)    



 // Parametertyper 
#define LC_U_TALL          1     // Heltall     
#define LC_U_FLYT          2     // Flyttall    
#define LC_U_ALFA          4     // Tekststreng 
#define LC_U_DEFINERT      8     // Type definert i utvalgsregel


/*
 *!--------------------------------------------------------------!
 *! Kvalitet                                                     !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_KVALITET {  /* Standard Kvalitet */
   short sMetode;
   long  lNoyaktighet;
   short sSynbarhet;
   short sHoydeMetode;
   long  lHoydeNoyaktighet;
} LC_KVALITET;

/*
 *!--------------------------------------------------------------!
 *! Buffer for lesing av SOSI-fil                                !
 *!--------------------------------------------------------------!
 */

typedef struct dLB_LESEBUFFER {
   char tx[LC_MAX_SOSI_LINJE_LEN];  /* Lesebuffer */
   UT_INT64 filpos;                 /* Filposisjon for starten av bufret */
   UT_INT64 startpos;               /* Startposisjon i filen for aktuellt SOSI-navn */
   char *cp;                        /* Peker til aktuell posisjon i bufret */
   char *pp;                        /* Peker til start parameter */
   char *ep;                        /* Peker til posisjon etter aktuellt ord */
	char *np;                        /* Peker til posisjon etter parameter (neste cp) */
   short cur_navn[6];               /* Aktuellt SOSI-navn på dette nivå */
   short cur_niv;                   /* Aktuellt nivå (der cp peker) (Ant. prikker) */
   short cur_ant_par;               /* Antall parametre på aktuellt nivå */
   short cur_type;                  /* Viser hva aktuellt set inneholder */
   short set_brukt;                 /* Status som viser om aktuellt "sett" er brukt */
   short sTegnsett;                 /* SOSI-filens tegnsett */
   short sStatus;                   /* Status, viser om buffer har brukbart innhold */
} LB_LESEBUFFER;


/*
 *!----------------------------------------------------------!
 *! BUFFER for koordinater og GINFO i minne                  !
 *!----------------------------------------------------------!
*/

/*
CH SOSI-buffer                 Binær kopi av SOSI-filen
CD For å øke hastigheten holder FYBA en binær kopi av SOSI-filen.
CD Denne kopien ligger delevis i minne og delevis på disk.
CD
CD Denne kopien består av gruppeinformasjon, koordinater og punktinformasjon.
CD
CD Gruppeinformasjonen for en gruppe handteres som en lang streng med pekere
CD til startposisjon for hver GINFO-linje.
CD
CD !-----------:-----------:----------:----------------------------------!
CD !  GINFO 1  !  GINFO 2  ! GINFO 3  ! .....                            !
CD !-----------:-----------:----------:----------------------------------!
CD  !            !           !
CD  !---------!  !           !
CD            !  !           !
CD !--------! !  !           !
CD ! GINFO  ! !  !           !
CD !--------! !  !           !
CD ! ofset  !-!  !           !
CD !        !-----           !
CD !        !-----------------
CD
CD Koordinatene lagres i egne array. Punktinformasjonen lagres som
CD en lang streng for hele gruppen med peker for hvert punkt til startposisjon
CD for PINFO for hvert punkt på samme måte som GINFO.
CD
CD !--------! !--------! !--------:-------:--------!
CD ! Øst    ! ! Nord   ! ! Høyde  !  KP   ! PINFO  !
CD !--------! !--------! !--------!-------!--------!
CD ! double ! ! double ! ! double ! short ! ushort !
CD !   m    ! !   m    ! !   m    !       !  ofset !
*/
typedef struct d_LB_INFO {
   double dHoyde;            // Høyde
   short sKp;                // Knutepunkt (0=ikke knutepunkt)
   unsigned long ulPiOfset;  // PINFO ofset i eget buffer
} LB_INFO;


#   define LC_INGEN_PINFO ULONG_MAX     /* Offset ved tom PINFO */


/*
 *!--------------------------------------------------------------!
 *! Navnetabell                                                  !
 *!--------------------------------------------------------------!
 */
typedef struct dSOSINAVN {            /* Navnetabellen */
   char szNavn[LC_MAX_SOSINAVN_LEN];   /* Sosi-navn */
   unsigned char ucAntPar;      /* Antall parametre til dette navnet */
   char cNivo;                  /* "Prikk-nivå"  (1 = Gruppenavn) */
   bool bBrukt;                 // Viser om navnet er vært brukt
} SOSINAVN;

typedef struct dLC_NAVNETABELL {
   short sAntNavn;              /* Antall navn totalt i navnetabellen */
   SOSINAVN sosi[LC_MAX_NAVN];  /* Navnetabellen */
} LC_NAVNETABELL;


#  define LC_ANT_PAR_UKJENT  255  /* Antall parametre til dette navnet er
                                     ukjent, ta med fram til neste " ."  */

  /* Definerte navn */
#define L_SLUTT       0
#define L_PUNKT       1
#define L_LINJE       2
#define L_KURVE       3
#define L_BUE         4
#define L_BUEP        5
#define L_SIRKEL      6
#define L_SIRKELP     7
#define L_KLOTOIDE    8
#define L_SVERM       9
#define L_TEKST      10
#define L_TRASE      11
#define L_FLATE      12
#define L_BEZIER     13
#define L_RASTER     14
#define L_DEF        15 
#define L_OBJDEF     16
#define L_MLINJE     17
#define L_STRUKTUR   18
#define L_OBJEKT     19
#define L_SYMBOL     20
#define L_HODE       21  /* L_HODE må alltid ligge sist av gruppenavnene */

#define L_NA         22  /* Andre definerte navn */
#define L_NAH        23
#define L_REF1       24
#define L_REF2       25
#define L_RADIUS     26
#define L_ENHET2     27
#define L_ENHET2H    28
#define L_ENHET2D    29
#define L_ENHET3     30
#define L_ENHET3H    31
#define L_ENHET3D    32
#define L_ORIGONO    33
#define L_HOYDE      34
#define L_DYBDE      35
#define L_NAD        36
#define L_NGISFLAGG  37
#define L_NGISLAG    38
#define L_OBJTYPE    39
#define L_KP         40   /* L_KP må alltid ligge sist av de forhåndsdefierte navnene */



/* ======= INDEKS-TABELLER =================== */

/*
CH Serienummer-tabell
CD !-------------*
CD ! Gruppenummer!
CD !-------------!       Linjenummer i tabellen er serienummer.
CD !  lGrNr      !
CD !  (long)     !
CD *-------------*
*/



/*
CH Geografisk-søketabell                               Geografisk søketabell
CD
CD Geografisk søk er basert på omskrevet boks.
CD Boksene organiseres i et R-tre. 
CD
CD !-----------------------------------*
CD !      Omskreven boks               !
CD !                                   !
CD ! min-N  ! min-Ø  ! max-N  ! max-Ø  !
CD !        !        !        !        !
CD !--------!--------!--------!--------!
CD !dMinNord!dMinAust!dMaxNord!dMaxAust!
CD !  d     !   d    !   d    !   d    !
CD !        !        !        !        !
CD *-----------------------------------*
*/

/*
 *!--------------------------------------------------------------!
 *! Boks for geografisk søk                                      !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_BOKS{
   double dMinAust;
	double dMinNord;
   double dMaxAust;      
   double dMaxNord;      
} LC_BOKS;

#define LC_R_MAX_SON  3      /* Max antall sønner for hver node i R-treet */

typedef struct dLC_R_NODE{
   struct dLC_R_NODE *pFar;  /* Far i treet (node) */
   LC_BOKS Boks;             /* Sum av omskreven boks for sønnene */
   short sSonType;  /* Hvilken type sønner har denne noden LC_NODE / LC_LEAF */
   short sSonAnt;   /* Antall sønner */
   union {
      struct dLC_R_NODE *pNode[LC_R_MAX_SON];  /* Sønner i treet (node) */
      struct dLC_R_LEAF *pLeaf[LC_R_MAX_SON];  /* Sønner i treet (løv) */
   } Son;
} LC_R_NODE;

#define LC_NODE 0
#define LC_LEAF 1


typedef struct dLC_R_LEAF{
   LC_R_NODE *pFar;  /* Far i treet (node) */
   LC_BOKS Boks;     /* Omskreven boks for gruppen */
   long lNr;         /* Gruppenummer i filen  */
} LC_R_LEAF;


/*
 *!--------------------------------------------------------------!
 *! Gruppetabel                                                  !
 *!--------------------------------------------------------------!
 */
/*
CH Gruppetabell                                     Gruppetabell
CD Dette er hovedtabellen med informasjon om hver enkelt gruppe på SOSI-filen. 
CD
CD !------------------------------:-----------------------------------------------*
CD !Start  !Start !Ant.   !Ant.   !            Gruppeinnhold                      !
CD ! på    ! i    !tegn   !tegn   !-----------------------------------------------!
CD !SOSI-  ! RB   !GINFO- !PINFO- !Gruppe!ant. !ant. !Kvali-  !Enhet ! Div. info  !
CD !fil    !      !buffer !buffer !navn  !GINFO! NØ  ! tet    !      ! (bit def.) !
CD !-------!------!-------!-------!------!-----!-----!--------!------!------------!
CD !sosi_st!rb_st !ulGiLen!ulPiLen!gnavn !ngi  !nko  !Kvalitet!dEnhet! info       !
CD !  n64  ! n64  !  ul   !  ul   ! s    !  s  ! l   ! struct !  d   ! us         !
CD !       !      !       !       !      !     !     !        !      !0=i         !
CD !       !      !       !       !      !     !     !        !      !1=H         !
CD !       !      !       !       !      !     !     !        !      !2=KP        !
CD !       !      !       !       !      !     !     !        !      !3=REF       !
CD !       !      !       !       !      !     !     !        !      !4=REF med ØY!
CD !       !      !       !       !      !     !     !        !      !5=sletta    !
CD !       !      !       !       !      !     !     !        !      !6=NGIS oppd !
CD *------------------------------------------------------------------------------*
*/
typedef struct dLC_GRTAB_LINJE{
   unsigned long ulPrior[4]; /* Bitfelt for prioriteter. */
									  /* Siste bit viser om feltet er bygd opp. */
   UT_INT64 sosi_st;     /* Startposisjon i SOSI-filen */
   UT_INT64 rb_st;       /* Peker til start av gruppen i buffer-fil */
   long  rb_forrige_gr;  /* Forrige gruppe i buffer-filen */
   long  rb_neste_gr;    /* Neste gruppe i buffer-filen */
   short gnavn;          /* Gruppenavn. Eks. .HODE, .PUNKT, mm */
   short ngi;            /* Antall GINFO-linjer */
   long nko;             /* Antall koordinater */
   unsigned short info;  /* Info, se under gruppetabellen */
	LC_KVALITET Kvalitet; /* Aktuell kvalitet fra GINFO */
   char szObjtype[LC_MAX_OBJTYPE_LEN]; /* ..OBJTYPE fra GINFO */
   double dEnhet;        /* Aktuell enhet for gruppen i bufferet */
   double dEnhetHoyde;   /* Aktuell enhet-H for gruppen i bufferet */
   double dEnhetDybde;   /* Aktuell enhet-D for gruppen i bufferet */
   unsigned long ulGiLen; /* Antall tegn i GINFO-buffer (inkl. \0) */
   unsigned long ulPiLen; /* Antall tegn i PINFO-buffer (inkl. \0) */
   LC_R_LEAF *pRL;        /* Peker inn i geografisk søketre */

} LC_GRTAB_LINJE;


/*
CH Brukttabell                                            Merking av grupper
CD Denne tabellen brukes delevis internt av FYBA, og delevis av brukerprogrammet.
CD
CD Følgende bit er definert:
CD -------------------------------------------------------------------------
CD  31  Gruppen er funnet ved geografisk søk   -----! Brukere kan lese/bruke
CD  30  Gruppen er funnet ved GINFO-utvalg          ! disse, men det er ikke
CD  29  Gruppen er funnet ved serienummer-søk       ! lov til å endre dem.
CD  28  Gruppen er i ringbufferet                   !
CD  27  Referanser er brukt i omskrevet blokk ------!
CD  26                              -----!
CD   .                                   ! Brukere har
CD   .                                   ! full tilgang
CD   2                                   ! til disse.
CD   1                              -----!
CD   0  Gruppen ligger i kø for skriving til SOSI-filen
*/


   /*
    *!--------------------------------------------------------------!
    *! Overordnet blokk med pekere til de ulike indekstabellene     !
    *!--------------------------------------------------------------!
    */
#define LC_IDX_LIN_BLOKK 5000
#define LC_ANT_IDX_BLOKK  (LC_MAX_GRU / LC_IDX_LIN_BLOKK)
typedef struct dLC_IDX_TABELL{
	/* Array med pekere til starten av blokk med Gruppetabell-linjer */
   LC_GRTAB_LINJE * GtAdm[LC_MAX_GRU / LC_IDX_LIN_BLOKK];

   /* Array med pekere til starten av blokk med Gruppenummer for gitt SNR */
   long             *SnrAdm[LC_MAX_GRU / LC_IDX_LIN_BLOKK];

   /* Array med pekere til starten av blokk med Brukttabell-linjer */
   unsigned long    *BtAdm[LC_MAX_GRU / LC_IDX_LIN_BLOKK];

	/* Array med pekere til starten av blokk med Geo-tabell-linjer */
   /* LC_GEOSOK_BOKS *GeoAdm[LC_MAX_GRU / LC_IDX_LIN_BLOKK]; */
} LC_IDX_TABELL;


/*
 *!--------------------------------------------------------------!
 *! Koordinat 2D                                                 !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_KOORD_2D {  /* (ø,n) Koordinatpar */
   double dAust;     /* øst-koordinat */
   double dNord;     /* nord-koordinat */
} LC_KOORD_2D;

/*
 *!--------------------------------------------------------------!
 *! Koordinat 3D                                                 !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_KOORD_3D {  /* (ø,n,h) Koordinatpar */
   double dAust;     /* øst-koordinat */
   double dNord;     /* nord-koordinat */
   double dHoyde;    /* Høyde */
} LC_KOORD_3D;

/*
 *!--------------------------------------------------------------!
 *! Rektangel                                                    !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_REKT {
   double dMinAust;
	double dMinNord;
   double dMaxAust;      
   double dMaxNord;      
} LC_REKT;


/*
 *!--------------------------------------------------------------!
 *! Kontanter og struktur for handtering av TRANSPAR i filhodet  !
 *!--------------------------------------------------------------!
 */
// Maske som styrer hvilke elementer i LC_TRANSPAR som benyttes
#define LC_TR_KOORDSYS  ((unsigned short)0x0001)  /* Koordsys */  
#define LC_TR_TRANSSYS  ((unsigned short)0x0002)  /* Transsys */
#define LC_TR_GEOSYS    ((unsigned short)0x0004)  /* Geosys   */  
#define LC_TR_GEOKOORD  ((unsigned short)0x0008)  /* Geokoord */  
#define LC_TR_ORIGO     ((unsigned short)0x0010)  /* Origo-nø */  
#define LC_TR_ENHET     ((unsigned short)0x0020)  /* Enhet    */  
#define LC_TR_ENHETH    ((unsigned short)0x0040)  /* Enhet-h  */  
#define LC_TR_ENHETD    ((unsigned short)0x0080)  /* Enhet-d  */  
#define LC_TR_VERTDATUM ((unsigned short)0x0100)  /* Vert-datum */
#define LC_TR_VERTINT   ((unsigned short)0x0200)  /* Vert-int   */
#define LC_TR_VERTDELTA ((unsigned short)0x0400)  /* Vert-delta */

#define LC_TR_ALLT      ((unsigned short)0xFFFF)  /* Alle deler av ..TRANSPAR */  


// Definerer struktur for ..TRANSPAR
typedef struct dLC_TRANSPAR {
   /* ...KOORDSYS */
   short   sKoordsys;
   char    szKoordsysDatum[36];
   char    szKoordsysProjek[36];
   /* ...TRANSSYS */
   short sTranssysTilsys;
   double dTranssysKonstA1;
   double dTranssysKonstB1;
   double dTranssysKonstA2;
   double dTranssysKonstB2;
   double dTranssysKonstC1;
   double dTranssysKonstC2;
   /* ...GEOSYS */
   short sGeosysDatum;
   short sGeosysProj;
   short sGeosysSone;
   /*...GEOKOORD */
   short sGeoKoord;
   /* ...ORIGO-NØ */
   LC_KOORD_2D Origo;
   //double dOrigoAust;
   //double dOrigoNord;
   /* ...ENHET */
   double  dEnhet;
   /* ...ENHET-H */
   double  dEnhet_h;
   /* ...ENHET-D */
   double  dEnhet_d;      
   /* ...VERT-DATUM */ 
   char szVertdatHref[7];
   char szVertdatDref[6];
   char szVertdatFref[6];
   char szVertdatHtyp[2];
   /* ...VERT-INT */ 
   short sVertintHref;
   short sVertintDref;
   short sVertintFref;
   /* ...VERT-DELTA */ 
   short sVdeltaMin;
   short sVdeltaMax;
} LC_TRANSPAR;


#define LC_TR_GEOSYS_INGEN_VERDI  -9999  // Brukes  for å angi at projeksjon og sone under geosys ikke er gitt

// Konstanter for definering av filtype (primært for bruk i GabEdit) JAØ-20010306
#define LC_FILTYPE_UKJENT        0
#define LC_FILTYPE_INAKTIV       1
#define LC_FILTYPE_GAB_EIENDOM   2
#define LC_FILTYPE_GAB_ADRESSE   3
#define LC_FILTYPE_GAB_BYGNING   4
#define LC_FILTYPE_BYGG          5
#define LC_FILTYPE_DEK           6
#define LC_FILTYPE_DEK_ENDRING   7
#define LC_FILTYPE_GRUNNKRETS    8
#define LC_FILTYPE_POSTKRETS     9
#define LC_FILTYPE_SKOLEKRETS   10
#define LC_FILTYPE_KIRKESOGN    11
#define LC_FILTYPE_TETTSTED     12
#define LC_FILTYPE_VALGKRETS    13


/*
 *!--------------------------------------------------------------!
 *! Filadministrasjon                                            !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_FILADM{
   char     szBaseVer[LC_BASEVER_LEN]; // Versjon og dato for aktuell versjon av FYBA
   char     szIdxVer[5];    // Indeksfil-versjon
   short    sIdxOpen;       // UT_FALSE/UT_TRUE - Flagg som viser at indeks er åpnet
   unsigned long ulPid;     // Prosess ID for programmet som har åpnet filen
   short    sFilType;       // Primært tenkt brukt i GabEdit, definerer hvilken type arbeidsfil dette er.
   unsigned short  usLag;   // Lag: (LC_SEKV,LC_FRAMGR,LC_BAKGR)
   char     szNgisLag[LC_NGISLAG_LEN]; // Ngislag i filhodet
   short    sAccess;        // Aksess: (READ / UPDATE)
	/* short    sDisk; */          // Disk for SOSI-filen (1=A, 2=B, osv.)
   char    *pszNavn;        // Filnavn (SOSI-filens navn, inkl. sti
   UT_INT64 SosiBytes;      // Antall byte i SOSI-filen
   FTID     SosiTid;        // Oppdateringstidspunkt for SOSI-filen
   LC_TRANSPAR TransPar;       // Transformasjonsparametre fra filhodet
   unsigned short TransMaske;  // Maske som viser hvilke deler av TransPar som inneholder data
   LC_REKT Omr;                // ..OMRÅDE fra filhodet
   short   sTegnsett;          // Tegnsett fra filhodet eller standardverdi
   char    szDato[LC_DATO_LEN]; // ..DATO fra fil-hodet
   short   sSosiVer;            // ..SOSI-VERSJON fra fil-hodet * 100
   char    SosiNiv[2];          // ..SOSI-NIVÅ fra fil-hodet
                                 // SosiNiv[0] = nivå fra filåpningen
                                 // SosiNiv[1] = nivå fra senere handtering
                                 // Filhodet oppdateres når filen stenges
   // short usUlovligRef;  // Bryter som viser om det er ulovlige
   //                      // referanser i filen (Indeksoppbygging)
   unsigned short usDataFeil;  // Flagg som viser om det er datafeil
                               // i filen (Indeksoppbygging)
   LC_KVALITET Kvalitet;   // Kvalitet fra filhodet

   UT_INT64 n64AktPos;        // Aktuell posisjon for sekv. skriv / les
	UT_INT64 n64NesteLedigRbPos; // Neste ledige posisjon i buffer-filen
   long lSisteGrRb;       // Siste gruppe i buffer-filen

   long lMaxSnr;        // Største serienummer brukt i filen
   long    lAntGr;      // Antall grupper i filen

   struct dLC_NAVNETABELL  SosiNavn;   // Navnetabell

	LC_IDX_TABELL *pIdx; // Starten av indekstabellen
   LC_R_NODE *pGeoRN;   // Peker til starten av trestruktur for geografisk søk
   LC_BOKS Omraade;     // Område angitt i filhodet ved åpning

   struct dLC_FILADM *pNesteFil;  // Peker til neste fil-adm.
   struct dLC_BASEADM *pBase;     // Peker til base-adm. for denne filen
} LC_FILADM;


/* Konstanter for flagg som viser om det er datafeil i filen (Indeksoppbygging) */
#define LC_DATAFEIL_REF  1   /* Ulovlig referanse (referanse til gruppe som ikke finnes)*/
#define LC_DATAFEIL_BUE  2   /* Ulovlige buer i filen */


/*
 *!--------------------------------------------------------------!
 *! Baseadministrasjon                                           !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_BASEADM{
   short  sType;        // Basetype: LC_BASE / LC_START_KLADD / LC_KLADD

   long   lAntGr;       // Antall grupper i basen
   LC_BOKS Omraade;     // Summert område fra filhodene
   short sAntFramgrFil; // Antall filer i framgrunn
   short sAntBakgrFil;  // Antall filer i bakgrunn

   LB_LESEBUFFER BufAdm;  // Vanlig lesebuffer mot SOSI-fil

   LC_FILADM *pCurSos;    // Fil-adm for åpen SOSI-fil
   FILE      *pfSos;      // Filhandel for åpen SOSI-fil

   LC_FILADM *pCurRb;    // Fil-adm for åpen Rb-fil
	FILE      *pfRb;      // Filhandel for åpen Rb-fil
   short      sModusRb;  // LES eller SKRIV til buffer-filen
   UT_INT64    n64FilPosRb; // Aktuell posisjon i buffer-filen 

   LC_FILADM *pForsteFil;    // Peker til første fil-adm.
   LC_FILADM *pSisteFil;     // Peker til siste fil-adm.

   struct dLC_BASEADM *pNesteBase;      // Peker til neste base-adm
} LC_BASEADM;


/*
 *!--------------------------------------------------------------!
 *! Gruppenummer                                                 !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_BGR {
   LC_FILADM *pFil;   /* Peker til FilAdm for SOSI-fil */
   long lNr;          /* Gruppenummer innen filen */
} LC_BGR;

/*
 *!--------------------------------------------------------------!
 *! Hent flate-referanser, status                                !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_GR_STAT {  
   short sGiLinNr;  /* Aktuell GINFO-linjenummer referanselesing */
   short sRefPos;   /* Aktuell posisjon i GINFO-linja */
   short sRefLin;   /* Viser om aktuel linje inneholder referanser */
} LC_GR_STATUS;

typedef struct dLC_GRF_STAT {
   LC_GR_STATUS Omkr;
   unsigned short usOmkretsFerdig;
   LC_GR_STATUS Oy;
   LC_BGR Bgr;      /* Aktuell øy-gruppe */
} LC_GRF_STATUS;


/*
 *!--------------------------------------------------------------!
 *! Geografisk søk, status mm.                                   !
 *!--------------------------------------------------------------!
 */

/* Kjede med resultatet av søket */
typedef struct dLC_KJEDE_BGR {
   LC_BGR Bgr;
   struct dLC_KJEDE_BGR *pNesteKB;
} LC_KJEDE_BGR;

/* Søkemetode i basen */
#define LC_GEO_SEKV  0x0000   /* Søker sekvensiellt gjennom gruppene */
#define LC_GEO_RTRE  0x0001   /* Bruker R-tre-srukturene i søket */

/* Status */
typedef struct dLC_GEO_STAT {
   unsigned short usMetode; /* Søkemetode (LC_GEO_SEKV eller LC_GEO_RTRE) */ 
   double nvn,nva,ohn,oha; /* Rektangel for søkeområde. */
   unsigned short usLag; /* Lag det skal søkes i. (LC_FRAMGR | LC_BAKGR) */
   LC_BGR Bgr;           /* Aktuell gruppe */
   /* Kjede med resultatet av søket */
   LC_KJEDE_BGR *pForsteKB;
   LC_KJEDE_BGR *pSisteKB;
   LC_KJEDE_BGR *pAktuellKB;
} LC_GEO_STATUS;

   
/*
CH Utvalgstabell
CD .===============================================================================.
CD !Ginfo/!Utvalgs-!Prio-!SOSI-!Utvalgs-!Para-!Ledd-!Start !Slutt !Min !Max !Regel-!
CD !Pinfo !kommando!ritet!navn !metode  !type !nr   !i str !i str !    !    !navn  !
CD !------!--------!-----!-----!--------!-----!-----!------!------!----!----!------!
CD !gi_pi !kommando!sPri-!sosi !metode  !type !ledd !start !slutt !min !max !regel !
CD !      !        !orit-!     !        !     !     !      !      !    !    !      !
CD !  c   !  c     !et   !c[]  ! c      !  c  !  c  !  c   !  c   !c[] !c[] ! c[]  !
CD !      !        !     !     !        !     !     !      !      !    !    !      !
CD !      !        ! s   !     !        !     !     !      !      !    !    !      !
CD !Def. se under  !     !     !Def. se !se   !     !      !      !Def. se nedenfor!
CD !      !        !     !     !nedenfor!nedf.!     !      !      !    !    !      !
CD *-------------------------------------------------------------------------------*
*/

   /* Gruppe, punkt eller pinfo-uvalg */
#define U_GRUPPE   1   /* GRUPPE-UTVALG */
#define U_PUNKT    2   /* PUNKT-UTVALG */
#define U_PINFO    3   /* PINFO-UTVALG */

/* Struktur for statusopplysninger for LC_InitPP / LC_GetPP */
typedef struct {
   short type;         /* LC_GETPP_KP, LC_GETPP_HOYDE, LC_GETPP_KVALITET, LC_GETPP_VANLIG */
   char pinfo_navn[LC_MAX_SOSINAVN_LEN]; /* Sosi-navn det skal finnes verdi til */
   long curr_punkt;        /* Aktuellt punkt */
   long slutt_punkt;       /* Første punkt etter søkeområdet */
	short neste_tegn;       /* Neste tegn (Ved flere PINFO i punktet) */
} LC_GETPP_STATUS;
/* Bruk:  LC_GETPP_STATUS  pp_stat; */

#define LC_GETPP_VANLIG   0
#define LC_GETPP_KP       1
#define LC_GETPP_HOYDE    2
#define LC_GETPP_KVALITET 3

   /* Konstant for sAktuellPrioritet */
#define LC_OVERSE_PRIORITET  -1

/* Utvalgslinje */
typedef struct sLC_UTVALG_ELEMENT {
   char kommando;
   char sosi[LC_MAX_SOSINAVN_LEN];
   char metode;
   //char type;
   short type;
   char ledd;         /* Ledd-nr for flerleddet parameter */
	char start;        /* Startposisjon i tegnstreng (0=hele) */
   char slutt;        /* Sluttposisjon i tegnstreng (0=resten) */
   char *min;
   char *max;
   struct sLC_UTVALG_ELEMENT *pNesteUE;       /* Neste på dette nivå */
   struct sLC_UTVALG_ELEMENT *pForsteUE; /* Første på nivået under */
   struct sLC_UTVALG_ELEMENT *pSisteUE;  /* Siste på nivået under */
} LC_UTVALG_ELEMENT;

typedef struct sLC_LAG {
   char  *pszLagNavn;           /* Lagnavn */
   short  sLagAktiv;            /* Lag aktiv for tegning */
   struct sLC_LAG *pNesteLag;   /* Neste lag */
} LC_LAG;

#define LC_UFORANDRET 0
#define LC_ENDRET     1
#define LC_NY         2
#define LC_SLETTET    3

typedef struct sLC_UTVALG {
   char  *pszNavn;
   short  sPrioritet;
   short  sOriginalPrioritet;
   short sStatus;
   short sTegnes;                 // Flagg for å styre om utvalgsregelen skal brukes ved tegning
   LC_UTVALG_ELEMENT *pForsteUE; /* Første utvalgslinje på øverste nivå */
   LC_UTVALG_ELEMENT *pSisteUE;  /* Siste utvalgslinje på øverste nivå */

   struct sLC_UTVALG *pForrigeU;  /* Forrige utvalg */
   struct sLC_UTVALG *pNesteU;    /* Neste utvalg */
   struct sLC_LAG *pLag;          /* Lag */
   char *pszRegel;                /* Regel */
} LC_UTVALG;

/* Toppblokk for GRUPPE-, PUNKT- og PINFO-utvalg */
typedef struct dLC_UTVALG_BLOKK {
   short sHoydeBrukt;
   short sTestAllePi;    /* "!" er brukt, må sjekke alle punkt */
   LC_UTVALG *pForsteU;
   LC_UTVALG *pSisteU;
   LC_UTVALG *pAktU;
} LC_UTVALG_BLOKK;

/* Administrasjonsblokk for utvalg */
typedef struct dLC_UT_ADM {
   short            sMaxPrior;       /* Største prioritet */
   LC_UTVALG_BLOKK  Gruppe;
   LC_UTVALG_BLOKK  Punkt;
   LC_UTVALG_BLOKK  Pinfo;
   LC_UTVALG_BLOKK *pAktUB;
	short            sGruppeValgt;
   LC_LAG *pForsteLag;
   LC_LAG *pSisteLag;
} LC_UT_ADM;

/* Administrasjonsblokk for serienummersøk */
typedef struct dLC_SNR_ADM {
   LC_FILADM *pFil;
	long lMinSnr;
   long lMaxSnr;
   long lAktSnr;
} LC_SNR_ADM;

/*
CH Polygonbeskrivelse                        Strukturer for polygonbeskrivelse.
CD 
CD Dette er et sett med strukturer som er kjedet sammen til en komplett
CD beskrielse av en flate. Eksempel på bruk er gitt under $LENKE<LC_POL_GetRef>.
CD
CD
CD   !-----------------!
CD   ! LC_POLYGON      !
CD   !                 !       !-------------------------!
CD   ! !- Omkrets --!  !       !   !-----------------!   !---------------!
CD   ! !LC_POL_OMKR !  !       ! !-!LC_POL_ELEMENT   ! !-!LC_POL_ELEMENT !
CD   ! !            !  !       ! ! ! - Bgr           ! ! ! - Bgr         !
CD   ! !- Siste     !--!-------! ! ! - Snr           ! ! ! - Snr         !
CD   ! !- Første    !--!---------! ! - Retning       ! ! ! - Retning     !
CD   ! !------------!  !           ! - Forrige (NULL)! ! ! - Forrige     !
CD   ! !- Hull ------! !           ! - Neste         !-! ! - Neste (NULL)!
CD   ! !LC_OY_ADM    ! !           !-----------------!   !---------------!
CD   ! !             ! !
CD   ! !- Første øy  !-!-!
CD !-!-!- Siste øy   ! ! !
CD ! ! !-------------! ! !
CD ! !-----------------! !
CD !   !-----------------!
CD !   !                                 !------------------------!
CD !   !                  !------------! !   !-----------------! !---------------!
CD !  !--------------!  !-!LC_POL_OMKR ! ! !-!LC_POL_ELEMENT   !!!LC_POL_ELEMENT !
CD !  !LC_OY_ELEMENT !  ! !            ! ! ! ! - Bgr           !!! - Bgr         !
CD !  !- Omkrets     !--! !- Siste     !-! ! ! - Snr           !!! - Snr         !
CD !  !- Neste       !-!  !- Første    !---! ! - Retning       !!! - Retning     !
CD !  !--------------! !  !------------!     ! - Forrige (NULL)!!! - Forrige     !
CD !                   !                     ! - Neste         !!! - Neste (NULL)!
CD !                   !                     !-----------------! !---------------!
CD !                   !
CD !   !---------------!                 !--------------------------!
CD !   !                  !------------! !   !-----------------!   !---------------!
CD !  !--------------!  !-!LC_POL_OMKR ! ! !-!LC_POL_ELEMENT   ! !-!LC_POL_ELEMENT !
CD !--!LC_OY_ELEMENT !  ! !            ! ! ! ! - Bgr           ! ! ! - Bgr         !
CD    !- Omkrets     !--! !- Siste     !-! ! ! - Snr           ! ! ! - Snr         !
CD    !- Neste (NULL)!    !- Første    !---! ! - Retning       ! ! ! - Retning     !
CD    !--------------!    !------------!     ! - Forrige (NULL)! ! ! - Forrige     !
CD                                           ! - Neste         !-! ! - Neste (NULL)!
CD                                           !-----------------!   !---------------!
*/


/*
 *!--------------------------------------------------------------!
 *! Polygon element (ett for hver gruppe i polygonbeskrivelsen)  !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_POL_ELEMENT {
   LC_BGR Bgr;       /* Gruppenummer */
   short  sRetning;  /* LC_MED_DIG eller LC_MOT_DIG */
   long   lSnr;      /* Serienummer */
   LC_KOORD_2D Pkt;     /* (ø,n) Representasjonspunkt (Brukes ikke av FYBA. Til disp.) */
   struct dLC_POL_ELEMENT *pNestePE;  /* Peker til neste element i polygonet */
   struct dLC_POL_ELEMENT *pForrigePE;  /* Peker til forrige element i polygonet */
} LC_POL_ELEMENT;

/*
 *!----------------------------------------------------------------------!
 *! Adm. blokk for polygon (en for hver lukket "del", omkrets eller øy)  !
 *!----------------------------------------------------------------------!
 */
typedef struct dLC_POL_OMKR {
   LC_POL_ELEMENT *pForstePE;
   LC_POL_ELEMENT *pSistePE;
} LC_POL_OMKR;

/*
 *!--------------------------------------------------------------!
 *! Øy (i polygon) element  (en for hver øy)                    !
 *!--------------------------------------------------------------!
 */
typedef struct dLC_OY_ELEMENT{
	LC_POL_OMKR PO;  /* Administrasjonsblokk til kjede som beskriv øyavgrensinga */
   struct dLC_OY_ELEMENT *pNesteOE;  /* Peker til neste øyelement i polygonet */
   struct dLC_OY_ELEMENT *pForrigeOE;  /* Peker til forrige øyelement i polygonet */
} LC_OY_ELEMENT;

/*
 *!------------------------------------------------------------------------!
 *! Adm. blokk for øy (i polygon) element (en for alle øyene i en flate)  !
 *!------------------------------------------------------------------------!
 */
typedef struct dLC_OY_ADM{
   LC_OY_ELEMENT *pForsteOE;   /* Første øy (hull) */
   LC_OY_ELEMENT *pSisteOE;    /* Siste øy  (hull) */
} LC_OY_ADM;

/*
 *!--------------------------------------------------------------!
 *! Adm blokk for Polygon  (En for hver flate, inkl øyer)        !
 *!--------------------------------------------------------------!
 */

typedef struct dLC_POLYGON {
   LC_POL_OMKR HovedPO;      /* Adm blokk for kjede som beskriver ytre avgrensing */
   LC_OY_ADM  OyOA;        /* Kjede som beskriver hull i flata */
} LC_POLYGON;


/* ======================================================= */
/*  Funksjonsdefinisjoner for fyho.c                       */
/* ======================================================= */
SK_EntPnt_FYBA short HO_New(const char *pszFil,short koosys,double origo_a,double origo_n,
                            double enhet,double enhet_h,double enhet_d,
                            double nv_a,double nv_n,double oh_a,double oh_n);
SK_EntPnt_FYBA short HO_TestSOSI(const char *pszFil,UT_INT64 *sluttpos);
SK_EntPnt_FYBA char *HO_GetVal(const char *pszFil,char *sosi_navn,short *sett_nr);
SK_EntPnt_FYBA short HO_GetKvalitet(const char *pszFil,short *psMetode,long *plNoyaktighet,
                                    short *psSynbarhet,short *psHoydeMetode,long *plHoydeNoyaktighet);
SK_EntPnt_FYBA short HO_GetTrans(const char *pszFil,short *koosys,double *origo_a,
                                 double *origo_n,double *enhet,double *enhet_h,double *enhet_d);
SK_EntPnt_FYBA short HO_GetTransEx(const char *pszFil,unsigned short *pusMaske, LC_TRANSPAR *pTrans);
SK_EntPnt_FYBA short HO_GetOmr(const char *pszFil,double *nv_a,double *nv_n,double *oh_a,double *oh_n);
SK_EntPnt_FYBA short HO_GetTegnsett(const char *pszFil,short *psTegnsett);
SK_EntPnt_FYBA short HO_SjekkTegnsett(const char *pszFil,short *psTegnsett);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylh.c                       */
/* ======================================================= */
SK_EntPnt_FYBA short LC_GetTrans(short *koosys,double *origo_a,double *origo_n,double *enhet,
						               double *enhet_h,double *enhet_d);
SK_EntPnt_FYBA short LC_GetTransEx(unsigned short *pusMaske, LC_TRANSPAR *pTrans);
SK_EntPnt_FYBA short LC_PutTrans(short koosys,double origo_a,double origo_n,
                                 double enhet,double enhet_h,double enhet_d);
SK_EntPnt_FYBA short LC_PutTransEx(unsigned short usMaske, LC_TRANSPAR *pTrans);
SK_EntPnt_FYBA short LC_GetTegnsett(short *psTegnsett);
SK_EntPnt_FYBA short LC_GetOmr(double *nv_a,double *nv_n,double *oh_a,double *oh_n);
SK_EntPnt_FYBA short LC_PutOmr(double nv_a,double nv_n,double oh_a,double oh_n);
SK_EntPnt_FYBA void  LC_NyttHode(void);
SK_EntPnt_FYBA short LC_TestHode(void);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylo.c                       */
/* ======================================================= */
SK_EntPnt_FYBA void			LC_Init(void);
SK_EntPnt_FYBA void			LC_Close(void);
SK_EntPnt_FYBA LC_BASEADM* LC_OpenBase(short sBaseType);
SK_EntPnt_FYBA void			LC_CloseBase(LC_BASEADM *pBase,short s_stat);
SK_EntPnt_FYBA short			LC_OpenSos(const char *fil,short sModus,short sNyIdx,short sVisStatus,
                                      LC_FILADM **ppFil, short *o_stat);
SK_EntPnt_FYBA void			LC_CloseSos(LC_FILADM *pFil,short s_stat);
SK_EntPnt_FYBA void        LC_FcloseSos(LC_FILADM *pFil);
SK_EntPnt_FYBA void    LC_SetDefLpfi(short ant_tegn);
SK_EntPnt_FYBA short   LC_InqDefLpfi(void);
SK_EntPnt_FYBA short   LC_InqLag(unsigned short *usLag);
SK_EntPnt_FYBA unsigned short LC_InqFilLag(LC_FILADM *pFil);
SK_EntPnt_FYBA void    LC_SetFilLag(LC_FILADM *pFil,unsigned short usLag);
SK_EntPnt_FYBA short   LC_Backup(LC_FILADM *pFil,const char *pszBackupPath);
SK_EntPnt_FYBA void    LC_MaxSkriv(long);
SK_EntPnt_FYBA long    LC_InqMaxSkriv(void);
SK_EntPnt_FYBA void    LC_SetNgisModus(short modus);
SK_EntPnt_FYBA short   LC_GetNgisModus(void);
SK_EntPnt_FYBA void    LC_SetUtvidModus(short modus);
SK_EntPnt_FYBA short   LC_GetUtvidModus(void);
SK_EntPnt_FYBA LC_BASEADM* LC_InqCurBase(void);
SK_EntPnt_FYBA void    LC_SelectBase(LC_BASEADM *pBase);
SK_EntPnt_FYBA short   LC_GetBaOm(unsigned short usLag,double *nva,double *nvn,double *oha,double *ohn);
SK_EntPnt_FYBA short   LC_GetFiOm(LC_FILADM *pFil,double *nva,double *nvn,double *oha,double *ohn);
SK_EntPnt_FYBA LC_FILADM * LC_GetFiNr(const char *fil_navn);
SK_EntPnt_FYBA char   *LC_GetFiNa(LC_FILADM *pFil);
SK_EntPnt_FYBA short   LC_ErFilBase(const char *fil);
SK_EntPnt_FYBA short   LC_ErKoordsysLik(void);
SK_EntPnt_FYBA short   LC_ErVertdatumLik(void);
SK_EntPnt_FYBA char*   LC_GetNgisLag(LC_FILADM *pFil);
SK_EntPnt_FYBA void    LC_SetEndringsstatus(short sStatus);
SK_EntPnt_FYBA void    LC_SetFilType(LC_FILADM *pFil, short sType);
SK_EntPnt_FYBA short   LC_GetFilType(LC_FILADM *pFil);
SK_EntPnt_FYBA short   LC_SetIdxPath(const char *pszIdxPath);
SK_EntPnt_FYBA const char* LC_GetIdxPath(void);
/* Konstanter for intgt.sEndra (aktuell gruppe er endra) */
#define END_UENDRA  0   /* Ikke endra */
#define END_KOPI    1   /* Endra ved totalkopi fra annen gruppe */
#define END_ENDRA   2   /* Endra ved normal Put fra program */

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylx.c                       */
/* ======================================================= */
#define GRF_YTRE   0x01  /* Ytre avgrensing */
#define GRF_INDRE   0x02  /* Indre avgrensing, øyer */
#define LC_MED_DIG 0x01  /* Brukes MED dig retning */
#define LC_MOT_DIG 0x02  /* Brukes MOT dig retning */
#define GRF_START_OY    0x04  /* Første gruppe i øy */
#define GRF_SLUTT_OY    0x08  /* Siste gruppe i øy */

SK_EntPnt_FYBA long   LC_InqAntRef(void);
SK_EntPnt_FYBA void   LC_InitGetRefFlate(LC_GRF_STATUS *pGrfStat);
SK_EntPnt_FYBA long   LC_GetRefFlate(LC_GRF_STATUS *RefStat,unsigned short sHent,long *ref_array,
                                     unsigned char *ref_status,long max_ref);
SK_EntPnt_FYBA short  LC_PutRef(long *ref_array,long ant_ref);
SK_EntPnt_FYBA long   LC_GetRef(long *ref_array,long max_ref,short *gilin,short *refpos);

SK_EntPnt_FYBA short  LC_GetBuePar(short buff_retning, double *as, double *ns, double *radius,
                                   double *fi, double *dfi, short *sfeil);
SK_EntPnt_FYBA short  LC_GetBue(short retning,double *a1,double *n1,double *a2,double *n2,
                                double *radius,short *storbue);
SK_EntPnt_FYBA short  LC_GetBuep(short retning,double *a1,double *n1,double *a2,double *n2,
                                 double *a3,double *n3);
SK_EntPnt_FYBA short  LC_GetSirkel(double *as,double *ns,double *radius);
SK_EntPnt_FYBA short  LC_GetSirkelp(double *a1,double *n1,double *a2,double *n2,
                                    double *a3,double *n3);

SK_EntPnt_FYBA void   LC_GetCurEnhet(LC_FILADM * pFil,short *nivaa, double *enhet,
                                     double *enhet_h, double *enhet_d);
SK_EntPnt_FYBA short  LC_UpdateGiEnhet(LC_FILADM *pFil,double enhet,double enhet_h,double enhet_d);

SK_EntPnt_FYBA short  LC_GetKvalitet(short *psMetode,long *plNoyaktighet,short *psSynbarhet,
                                     short *psHoydeMetode,long *plHoydeNoyaktighet);
SK_EntPnt_FYBA short  LC_GetCurKvalitet(LC_FILADM *pFil,short *nivaa,long pnr,
                                        short *psMetode,long *plNoyaktighet,short *psSynbarhet,
                                        short *psHoydeMetode,long *plHoydeNoyaktighet);
SK_EntPnt_FYBA short  LC_UpdateGiKvalitet(LC_FILADM *pFil,short sMetode,long lNoyaktighet,
                                          short sSynbarhet,short sHoydeMetode,long lHoydeNoyaktighet);
SK_EntPnt_FYBA short  LC_UpdatePiKvalitet(LC_FILADM *pFil,long pnr,short sMetode,long lNoyaktighet,
                                          short sSynbarhet,short sHoydeMetode,long lHoydeNoyaktighet);

SK_EntPnt_FYBA char * LC_GetGP(const char *,short *,short);
SK_EntPnt_FYBA short LC_PutGP(const char *sosi_navn,const char *verdi,short *linje_nr);
SK_EntPnt_FYBA short LC_AppGP(const char *sosi_navn,const char *verdi,short *linje_nr);
SK_EntPnt_FYBA short  LC_UpdateGP(short linje_nr,const char *sosi_navn,const char *verdi);
SK_EntPnt_FYBA void   LC_InitPP(const char *sosi_navn,long forste_punkt,long siste_punkt,
                                LC_GETPP_STATUS *pp_status);
SK_EntPnt_FYBA char * LC_GetPP(long *punkt,LC_GETPP_STATUS *pp_stat);
SK_EntPnt_FYBA char * LC_GetPiVerdi(const char *pszSosiNavn,long sPnr,short *sSettNr);
SK_EntPnt_FYBA short  LC_TestPi(long punkt_nr,short sTestHoyde);
SK_EntPnt_FYBA short  LC_FinnKp(long *forste_punkt,long siste_punkt,short *kp);
SK_EntPnt_FYBA long   LC_GetSn(void);
SK_EntPnt_FYBA void   LC_PutSn(long snr);
SK_EntPnt_FYBA char * LC_GetGi(short gilin);
SK_EntPnt_FYBA void   LC_PutGi(short gilin,const char *ginfo);
SK_EntPnt_FYBA void   LC_GetTK(long pkt,double *aust,double *nord);
SK_EntPnt_FYBA void   LC_GetArrayTK(short retning,long max_antall,long fra_punkt,
                                    double *aust,double *nord,long *antall);
SK_EntPnt_FYBA void   LC_GetArrayTH(short retning,long max_antall,long fra_punkt,
                                    double *hoyde,long *antall);
SK_EntPnt_FYBA void   LC_PutTK(long punkt_nr,double aust,double nord);
SK_EntPnt_FYBA double LC_GetTH(long pkt);
SK_EntPnt_FYBA void   LC_PutTH(long pkt,double hoyde);
SK_EntPnt_FYBA double LC_GetHoyde(long punkt_nr);
SK_EntPnt_FYBA void   LC_PutTD(long punkt_nr, double dybde);
SK_EntPnt_FYBA double LC_GetTD(long punkt_nr);
SK_EntPnt_FYBA double LC_GetDybde(long punkt_nr);
SK_EntPnt_FYBA char * LC_GetPi(long pkt);
SK_EntPnt_FYBA short  LC_PutPi(long pkt,const char *pi);
SK_EntPnt_FYBA short  LC_GetKp(long pkt);
SK_EntPnt_FYBA void   LC_PutKp(long pkt,short kp);
SK_EntPnt_FYBA double LC_BerAreal(void);
SK_EntPnt_FYBA double LC_BerLengde(void);
SK_EntPnt_FYBA bool   LC_BerLengde3D(double *skraa_lengde);
SK_EntPnt_FYBA double LC_BerAvgrensLengde(void);
SK_EntPnt_FYBA double LC_BerIndreAvgrensLengde(void);
SK_EntPnt_FYBA double LC_BerYtreAvgrensLengde(void);
SK_EntPnt_FYBA void   LC_DumpTab(void);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylb.c                       */
/* ======================================================= */
SK_EntPnt_FYBA short  LC_GetGrFi(LC_FILADM **ppFil);
SK_EntPnt_FYBA void   LC_InitNextFil(LC_FILADM **ppFil);
SK_EntPnt_FYBA short  LC_NextFil(LC_FILADM **ppFil,unsigned short usLag);
SK_EntPnt_FYBA void   LC_InitNextBgr(LC_BGR * pBgr);
SK_EntPnt_FYBA short  LC_NextBgr(LC_BGR * pBgr,unsigned short usLag);
SK_EntPnt_FYBA short  LC_InqAntFiler(unsigned short usLag);
SK_EntPnt_FYBA short  LC_GetGrNr(LC_BGR * pBgr);
SK_EntPnt_FYBA const char *LC_GetObjtypeBgr(LC_BGR * pBgr);
SK_EntPnt_FYBA short  LC_GetGrPara(short *ngi,long *nko,unsigned short *info);
SK_EntPnt_FYBA short  LC_GetGrParaBgr(LC_BGR * pBgr,short *ngi,long *nko,unsigned short *info);
SK_EntPnt_FYBA short  LC_RsGr(short *rstat,LC_FILADM *pFil,short *ngi,long *nko,
                              unsigned short *info,long *gml_snr);
SK_EntPnt_FYBA short  LC_RsHode(LC_FILADM *pFil,short *ngi,long *nko,unsigned short *info);
SK_EntPnt_FYBA void   LC_WsGr(LC_FILADM *pFil);
SK_EntPnt_FYBA void   LC_WsGrPart(LC_FILADM *pFil,long fra_punkt,long antall);
SK_EntPnt_FYBA short  LC_EndreHode(LC_FILADM *pFil);
SK_EntPnt_FYBA short  LC_RxGr(LC_BGR * pBgr,short les_sosi,short *ngi,long *nko,unsigned short *info);
SK_EntPnt_FYBA short  LC_WxGr(short k_stat);
SK_EntPnt_FYBA void   LC_RoundKoord(void);
SK_EntPnt_FYBA long   LC_FiLastGr(LC_FILADM *pFil);
SK_EntPnt_FYBA short  LC_NyGr (LC_FILADM *pFil,const char *sosi,LC_BGR * pBgr,long *snr);
SK_EntPnt_FYBA short  LC_CopyGr (LC_BGR * pBgr,short ngis,short *ngi,long *nko,unsigned short *info);
SK_EntPnt_FYBA short  LC_CopyCoord(LC_BGR * pBgr,short retning,long til_linje,short *ngi,
                                   long *nko,unsigned short *info);
SK_EntPnt_FYBA short  LC_DelGr(void);
SK_EntPnt_FYBA void   LC_SnuGr(void);
SK_EntPnt_FYBA short  LC_SplittGr (long p1,long p2,LC_BGR * pBgr2);
SK_EntPnt_FYBA short  LC_SammenfoyGr(LC_BGR * pFraBgr,short retning,short plassering,short metode,
                      short *ngi,long *nko,unsigned short *info);
SK_EntPnt_FYBA void   LC_ErstattReferanse (LC_FILADM *pFil,long lGmlSnr,long lNyttSnr, bool bSammeRetning);


   /* Konstanter for SammenfoyGr() */
#define LC_SG_FORRAN 1   /* Heng den andre gruppen inn forran første koordinat */
#define LC_SG_BAK    2   /* Heng den andre gruppen inn etter siste koordinat */
#define LC_SG_BEHOLD 3   /* Begge sammenføyings-punktene beholdes */
#define LC_SG_FJERN  4   /* Bare det ene av sammenføyings-punktene beholdes */


SK_EntPnt_FYBA short  LC_InsGiL (short linje, short antall);
SK_EntPnt_FYBA short  LC_AppGiL (void);
SK_EntPnt_FYBA short  LC_DelGiL (short linje, short antall);
SK_EntPnt_FYBA short  LC_DelGiNavn(char *pszEgenskapNavn);
SK_EntPnt_FYBA long  LC_InsKoL (long linje, long antall);
SK_EntPnt_FYBA long  LC_AppKoL (void);
SK_EntPnt_FYBA long  LC_DelKoL (long linje, long antall);
SK_EntPnt_FYBA void   LC_Save (void);
SK_EntPnt_FYBA void   LC_OppdaterEndret(short endring);
  #define O_GINFO   0  /* Oppdater tabeller i forhold til GINFO */
  #define O_ENDRET  1  /* Merk for endret og oppdat. tab. */
  #define O_SLETTET 2  /* Merk for slettet og oppdat. tab. */

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyli.c                       */
/* ======================================================= */
/* Brukttabellen */
SK_EntPnt_FYBA void  LC_SetBt(LC_BGR * pGr,short kolonne);
SK_EntPnt_FYBA void  LC_ClrBt(LC_BGR * pGr,short kolonne);
SK_EntPnt_FYBA short LC_GetBt(LC_BGR * pGr,short kolonne);
SK_EntPnt_FYBA void  LC_EraseBt(short fra_kol,short til_kol);
SK_EntPnt_FYBA void  LC_CopyBt(short fra_kol,short til_kol,short operasjon);
SK_EntPnt_FYBA void  LC_SetModusMerk(unsigned short usModus);
SK_EntPnt_FYBA long  LC_MerkGr(short sKolonne,short sBryter);
SK_EntPnt_FYBA void  LC_ClrPrioritet(LC_BGR * pGr,short kolonne);
SK_EntPnt_FYBA void  LC_SetPrioritet(LC_BGR * pGr,short kolonne);
SK_EntPnt_FYBA short LC_InqPrioritet(LC_BGR * pGr,short kolonne);
SK_EntPnt_FYBA void  LC_ErasePrioritet(LC_BGR * pGr);
SK_EntPnt_FYBA void  LC_EraseAllPrioritet(LC_FILADM *pFil);
SK_EntPnt_FYBA void  LC_DumpBt(const char *pszMelding);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyld.c                       */
/* ======================================================= */
SK_EntPnt_FYBA void   LC_DelIdx(char *szSosFil);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyta.c                       */
/* ======================================================= */
/* Tabellsystemet */
SK_EntPnt_FYBA short  LC_InitTabel(long n_rec,short rec_len,void *buffer);
SK_EntPnt_FYBA short  LC_PutTabel(long linje,void *buffer);
SK_EntPnt_FYBA short  LC_GetTabel(long linje,void *buffer);
SK_EntPnt_FYBA void   LC_CloseTabel(void);
/* ======================================================= */
/*  Funksjonsdefinisjoner for fyln.c                       */
/* ======================================================= */
SK_EntPnt_FYBA char *LC_FormatterKvalitet(short sMetode,long lNoyaktighet,short sSynbarhet,
                           short sHoydeMetode,long lHoydeNoyaktighet);
SK_EntPnt_FYBA short LC_FinnNivo(const char *pszNavn);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyls.c                       */
/* ======================================================= */
SK_EntPnt_FYBA void   LC_SBSn(LC_SNR_ADM *pSnrAdm,LC_FILADM *pFil,long lMinSnr,long lMaxSnr);
SK_EntPnt_FYBA short  LC_MoveSn(LC_SNR_ADM *pSnrAdm,long lSnr,LC_BGR * pBgr);
SK_EntPnt_FYBA short  LC_FiSn(LC_FILADM *pFil,long lSnr,LC_BGR * pBgr);
SK_EntPnt_FYBA void   LC_FiArraySn(LC_FILADM *pFil,short antall,long *snr,long *bgr);
SK_EntPnt_FYBA long   LC_FASn(LC_SNR_ADM *pSnrAdm);
SK_EntPnt_FYBA short  LC_FFSn(LC_SNR_ADM *pSnrAdm,LC_BGR *pBgr);
SK_EntPnt_FYBA short  LC_FNSn(LC_SNR_ADM *pSnrAdm,LC_BGR *pBgr);
SK_EntPnt_FYBA short  LC_FPSn(LC_SNR_ADM *pSnrAdm,LC_BGR *pBgr);
SK_EntPnt_FYBA short  LC_FLSn(LC_SNR_ADM *pSnrAdm,LC_BGR *pBgr);
SK_EntPnt_FYBA short  LC_FFSnBt(LC_SNR_ADM *pSnrAdm,short kolonne,LC_BGR *pBgr);
SK_EntPnt_FYBA short  LC_FNSnBt(LC_SNR_ADM *pSnrAdm,short kolonne,LC_BGR *pBgr);
SK_EntPnt_FYBA short  LC_FPSnBt(LC_SNR_ADM *pSnrAdm,short kolonne,LC_BGR *pBgr);
SK_EntPnt_FYBA short  LC_FLSnBt(LC_SNR_ADM *pSnrAdm,short kolonne,LC_BGR *pBgr);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fylr.c                       */
/* ======================================================= */
SK_EntPnt_FYBA short  LC_GetGrWin(LC_BGR *pBgr,double *nva,double *nvn,double *oha,double *ohn);
/* Flate-søk */
SK_EntPnt_FYBA void   LC_SBFlate(LC_GEO_STATUS *pGeoStat,unsigned short usLag,
                                 double nv_a,double nv_n,double oh_a,double oh_n);
SK_EntPnt_FYBA short  LC_FFFlate(LC_GEO_STATUS *pGeoStat,LC_BGR * pBgr);
SK_EntPnt_FYBA short  LC_FNFlate(LC_GEO_STATUS *pGeoStat,LC_BGR * pBgr);
/* Geografisk søk primær gruppe */
SK_EntPnt_FYBA void   LC_SBGeo(LC_GEO_STATUS *pGeoStat,unsigned short usLag,
                               double nv_a,double nv_n,double oh_a,double oh_n);
SK_EntPnt_FYBA short  LC_FFGeo(LC_GEO_STATUS *pGeoStat,LC_BGR *pBgr);
SK_EntPnt_FYBA short  LC_FNGeo(LC_GEO_STATUS *pGeoStat,LC_BGR *pBgr);
SK_EntPnt_FYBA long   LC_FAGeo(LC_GEO_STATUS *pGeoStat);
SK_EntPnt_FYBA short LC_FFGeoFil(LC_GEO_STATUS *pGeoStat,LC_FILADM *pFil,LC_BGR *pBgr);
SK_EntPnt_FYBA short LC_FNGeoFil(LC_GEO_STATUS *pGeoStat,LC_FILADM *pFil,LC_BGR *pBgr);
SK_EntPnt_FYBA void LC_AvsluttSok(LC_GEO_STATUS *pGeoStat);

/* Vindustest mm */
SK_EntPnt_FYBA short  LC_WTst(double nva,double nvn,double oha,double ohn);
SK_EntPnt_FYBA short  LC_PTst(double a,double n);
SK_EntPnt_FYBA short  LC_PTstOmkrets(double a,double n);

/* Debugformål */
SK_EntPnt_FYBA void LC_DumpGeoRtre(LC_FILADM *pFil);


/* ======================================================= */
/*  Funksjonsdefinisjoner for fylu.c                       */
/* ======================================================= */
SK_EntPnt_FYBA LC_UT_ADM *  LC_OpenQuery(void);
SK_EntPnt_FYBA void    LC_CloseQuery(LC_UT_ADM *pUtAdm);
//SK_EntPnt_FYBA short   LC_PutQueryLine(LC_UT_ADM *pUtAdm,char *qulin);
SK_EntPnt_FYBA short   LC_PutQueryLine(LC_UT_ADM *pUtAdm,const char *qulin,short sType);
SK_EntPnt_FYBA void    LC_PutQueryRegel(LC_UTVALG *pU,const char *navn);
SK_EntPnt_FYBA short   LC_LesUtvalg(LC_UT_ADM *pUtAdm,const char *pszKomFil);
SK_EntPnt_FYBA char   *LC_GetUtRegelNavn(LC_UT_ADM *pUtAdm,short *ist);
SK_EntPnt_FYBA char   *LC_GruppeUtvalg(LC_UT_ADM *pUtAdm,short sPrior,short *sstat,char **regelnavn);
SK_EntPnt_FYBA short   LU_GiTestUtvalg(LC_UT_ADM *pUtAdm,LC_UTVALG * pU);
SK_EntPnt_FYBA void    LC_PunktUtvalg(LC_UT_ADM *pUtAdm,short sPrior,short *psStat,long lPnr,char **ppszRegel);
SK_EntPnt_FYBA LC_UTVALG *LC_FinnPinfoUtvalg(LC_UT_ADM *pUtAdm,const char *pszNavn);
SK_EntPnt_FYBA short   LC_PiTestUtvalg(LC_UT_ADM *pUtAdm,LC_UTVALG * pU,long lPnr);
SK_EntPnt_FYBA short   LC_GiQuery(LC_UT_ADM  *pUtAdm);
SK_EntPnt_FYBA long    LC_FAGiQuery(LC_UT_ADM *pUtAdm,unsigned short usLag);
SK_EntPnt_FYBA long    LC_FAPiQuery(LC_UT_ADM *pUtAdm,unsigned short usLag);
SK_EntPnt_FYBA long    LC_FAGiKombinertFlateQuery(LC_UT_ADM *pUtAdmFlate,LC_UT_ADM *pUtAdmOmkrets,
											                 unsigned short usLag,short sMetode);
SK_EntPnt_FYBA short   LC_QueryGP(char *qulin,unsigned short iniv,unsigned short *univ,short *ulin,char **para);
SK_EntPnt_FYBA short   LC_InqMaxPrioritet(LC_UT_ADM *pUA);
SK_EntPnt_FYBA short   LC_TestPrioritetBrukt(LC_UT_ADM *pUtAdm,short sPrioritet);
SK_EntPnt_FYBA void    LC_UtvalgPrioritet(LC_UT_ADM *pUtAdm);
SK_EntPnt_FYBA void    LC_LoggPrioritetUtvalg(LC_UT_ADM *pUtAdm);
SK_EntPnt_FYBA void    LU_FrigiUE(LC_UTVALG_ELEMENT *pUE);
SK_EntPnt_FYBA short   LU_AppUE (LC_UTVALG *pU,short sNiv,const char *pszTx);
SK_EntPnt_FYBA void    LC_PutLag(LC_UT_ADM *pUtAdm,LC_UTVALG *pU,const char *navn);
SK_EntPnt_FYBA bool    LC_ErLik_Avrundet(double dA1,double dN1,double dA2, double dN2, double dEnhet);
SK_EntPnt_FYBA bool    LC_ErLik_IkkeAvrundet(double dA1,double dN1,double dA2, double dN2, double dEnhet);
SK_EntPnt_FYBA bool    LC_ErReferert(void);
SK_EntPnt_FYBA long    LC_ErReferertFraAntall(void);


/* ======================================================= */
/*  Funksjonsdefinisjoner for fylp.c                       */
/* ======================================================= */
SK_EntPnt_FYBA void LC_POL_InitPolygon(LC_POLYGON *pPolygon);
SK_EntPnt_FYBA void LC_POL_FrigiPolygon(LC_POLYGON *pPolygon);

SK_EntPnt_FYBA void LC_POL_InitOmkrets(LC_POL_OMKR *pPO);
SK_EntPnt_FYBA LC_POL_ELEMENT * LC_POL_LeggTilGruppeOmkrets(LC_POL_OMKR *pPO,LC_BGR *pBgr,short sRetning,long lSnr);
SK_EntPnt_FYBA void LC_POL_FjernSisteGruppeOmkrets(LC_POL_OMKR *pPO);
SK_EntPnt_FYBA void LC_POL_FjernGruppeOmkrets(LC_POL_OMKR *pPO, LC_POL_ELEMENT *pPE);
SK_EntPnt_FYBA void LC_POL_FrigiOmkrets(LC_POL_OMKR *pPO);

SK_EntPnt_FYBA void LC_POL_InitOy(LC_OY_ADM *pOA);
SK_EntPnt_FYBA void LC_POL_FrigiAlleOyer(LC_OY_ADM *pOA);
SK_EntPnt_FYBA void LC_POL_FjernOy(LC_OY_ADM *pOA,LC_OY_ELEMENT *pOE);
SK_EntPnt_FYBA void LC_POL_LeggTilOy(LC_OY_ADM *pOA,LC_POL_OMKR *pPO);

SK_EntPnt_FYBA short LC_POL_TestBrukt(LC_POLYGON *pPolygon,LC_BGR *pBgr);
SK_EntPnt_FYBA short LC_POL_PutRef(LC_POLYGON *pPolygon);
SK_EntPnt_FYBA void  LC_POL_GetRef(LC_POLYGON *pPolygon);
SK_EntPnt_FYBA void  LC_POL_GetRefOmkrets(LC_POL_OMKR *pPO);
SK_EntPnt_FYBA short LC_POL_PTst(LC_POLYGON *pPolygon,double a,double n);
SK_EntPnt_FYBA short LC_POL_PTstOmkrets(LC_POL_OMKR *pPO,double a,double n);
SK_EntPnt_FYBA short LC_POL_OmkretsSkjaering(LC_POL_OMKR *pPO,double a,double n);
SK_EntPnt_FYBA void  LC_POL_Box(LC_POL_OMKR *pPO,double *nva,double *nvn, double *oha,double*ohn);
SK_EntPnt_FYBA short LC_ErLinjeRefLin(char *pszSosiLin, short sRefLin);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyln.c                       */
/* ======================================================= */
SK_EntPnt_FYBA const char *LC_GetElementNavn(LC_FILADM *pFil,short sNavnNr,bool *bBrukt);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyba.c                       */
/* ======================================================= */
SK_EntPnt_FYBA const char *LC_InqVer(void);

/* ======================================================= */
/*  Funksjonsdefinisjoner for fyle.c                       */
/* ======================================================= */
SK_EntPnt_FYBA short LC_StrError(short feil_nr,char **feilmelding);

SK_EntPnt_FYBA void LC_SetErrorHandler(void (*f) (short,const char*,const char*));
SK_EntPnt_FYBA void LC_SetStartMessageHandler(void (*f)(const char*));
SK_EntPnt_FYBA void LC_SetShowMessageHandler(void (*f)(double));
SK_EntPnt_FYBA void LC_SetEndMessageHandler(void (*f)(void));
SK_EntPnt_FYBA void LC_SetCancelHandler(short (*f)(void));

//////////////////////////////////////////////////////////////////////////
//
// Når FYBA brukes som LIB må følgende funksjoner finnes definert
//
//////////////////////////////////////////////////////////////////////////
void  LC_Error (short ifeilnr, const char logtx[], const char vartx[]);
void  LC_StartMessage(const char *cfil);
void  LC_ShowMessage(double prosent);
void  LC_EndMessage(void);
short LC_Cancel(void);

//////////////////////////////////////////////////////////////////////////
//
// Når FYBA brukes som DLL må følgende funksjoner finnes definert.
// Eksempel finnes i filen Fyba_Callback.cpp
// Funksjonene aktiveres med LC_SetXxxxxHandler rutinene.
// Hvis disse ikke blir aktivert brukes enkle rutiner som ligger i DLL-en.
//
//////////////////////////////////////////////////////////////////////////
void   LC_ErrorHandler (short ifeilnr, const char* logtx, const char* vartx);
void   LC_StartMessageHandler(const char *cfil);
void   LC_ShowMessageHandler(double prosent);
void   LC_EndMessageHandler(void);
short  LC_CancelHandler(void);


