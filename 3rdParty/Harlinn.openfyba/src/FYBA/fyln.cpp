/* == AR 910819 ========================================== */
/*  STATENS KARTVERK  -  FYSAK-PC                          */
/*  Fil: fyln.c                                            */
/*  Innhold: Navnesystem for fysak-pc                      */
/* ======================================================= */

#include "fyba.h"
#include "fybax.h"

#include <fcntl.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>


/*
AR-890616
CH LN_InitTab                                           Klargjør navnetabell
CD ==========================================================================
CD Formål:
CD Initierer navnetabellen med kjente navn.
CD
CD Parametre:
CD Type             Navn I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_NAVNETABELL *  pLn   i   Peker til navnetabell
CD
CD Bruk:
CD LN_InitTab(pLn);
   ==========================================================================
*/
void LN_InitTab(LC_NAVNETABELL * pLn)
{
   UT_StrCopy(pLn->sosi[L_SLUTT].szNavn, ".SLUTT", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_SLUTT].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_SLUTT].cNivo = 1;
   pLn->sosi[L_SLUTT].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_PUNKT].szNavn, ".PUNKT", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_PUNKT].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_PUNKT].cNivo = 1;
   pLn->sosi[L_PUNKT].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_LINJE].szNavn, ".LINJE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_LINJE].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_LINJE].cNivo = 1;
   pLn->sosi[L_LINJE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_KURVE].szNavn, ".KURVE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_KURVE].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_KURVE].cNivo = 1;
   pLn->sosi[L_KURVE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_BUE].szNavn, ".BUE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_BUE].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_BUE].cNivo = 1;
   pLn->sosi[L_BUE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_BUEP].szNavn, ".BUEP", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_BUEP].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_BUEP].cNivo = 1;
   pLn->sosi[L_BUEP].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_SIRKEL].szNavn, ".SIRKEL", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_SIRKEL].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_SIRKEL].cNivo = 1;
   pLn->sosi[L_SIRKEL].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_SIRKELP].szNavn, ".SIRKELP", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_SIRKELP].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_SIRKELP].cNivo = 1;
   pLn->sosi[L_SIRKELP].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_KLOTOIDE].szNavn, ".KLOTOIDE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_KLOTOIDE].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_KLOTOIDE].cNivo = 1;
   pLn->sosi[L_KLOTOIDE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_BEZIER].szNavn, ".BEZIER", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_BEZIER].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_BEZIER].cNivo = 1;
   pLn->sosi[L_BEZIER].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_RASTER].szNavn, ".RASTER", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_RASTER].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_RASTER].cNivo = 1;
   pLn->sosi[L_RASTER].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_TEKST].szNavn, ".TEKST", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_TEKST].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_TEKST].cNivo = 1;
   pLn->sosi[L_TEKST].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_TRASE].szNavn, ".TRASE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_TRASE].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_TRASE].cNivo = 1;
   pLn->sosi[L_TRASE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_FLATE].szNavn, ".FLATE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_FLATE].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_FLATE].cNivo = 1;
   pLn->sosi[L_FLATE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_SVERM].szNavn, ".SVERM", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_SVERM].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_SVERM].cNivo = 1;
   pLn->sosi[L_SVERM].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_DEF].szNavn, ".DEF", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_DEF].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_DEF].cNivo = 1;
   pLn->sosi[L_DEF].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_OBJDEF].szNavn, ".OBJDEF", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_OBJDEF].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_OBJDEF].cNivo = 1;
   pLn->sosi[L_OBJDEF].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_MLINJE].szNavn, ".MLINJE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_MLINJE].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_MLINJE].cNivo = 1;
   pLn->sosi[L_MLINJE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_STRUKTUR].szNavn, ".STRUKTUR", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_STRUKTUR].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_STRUKTUR].cNivo = 1;
   pLn->sosi[L_STRUKTUR].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_OBJEKT].szNavn, ".OBJEKT", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_OBJEKT].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_OBJEKT].cNivo = 1;
   pLn->sosi[L_OBJEKT].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_SYMBOL].szNavn, ".SYMBOL", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_SYMBOL].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_SYMBOL].cNivo = 1;
   pLn->sosi[L_SYMBOL].bBrukt = false;
   
   UT_StrCopy(pLn->sosi[L_HODE].szNavn, ".HODE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_HODE].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_HODE].cNivo = 1;
   pLn->sosi[L_HODE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_NA].szNavn, "..NØ", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_NA].ucAntPar = 2;
   pLn->sosi[L_NA].cNivo = 2;
   pLn->sosi[L_NA].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_NAH].szNavn, "..NØH", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_NAH].ucAntPar = 3;
   pLn->sosi[L_NAH].cNivo = 2;
   pLn->sosi[L_NAH].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_NAD].szNavn, "..NØD", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_NAD].ucAntPar = 3;
   pLn->sosi[L_NAD].cNivo = 2;
   pLn->sosi[L_NAD].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_REF1].szNavn, "..", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_REF1].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_REF1].cNivo = 2;
   pLn->sosi[L_REF1].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_REF2].szNavn, "..REF", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_REF2].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_REF2].cNivo = 2;
   pLn->sosi[L_REF2].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_RADIUS].szNavn, "..RADIUS", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_RADIUS].ucAntPar = 1;
   pLn->sosi[L_RADIUS].cNivo = 2;
   pLn->sosi[L_RADIUS].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_ENHET2].szNavn, "..ENHET", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_ENHET2].ucAntPar = 1;
   pLn->sosi[L_ENHET2].cNivo = 2;
   pLn->sosi[L_ENHET2].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_ENHET2H].szNavn, "..ENHET-H", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_ENHET2H].ucAntPar = 1;
   pLn->sosi[L_ENHET2H].cNivo = 2;
   pLn->sosi[L_ENHET2H].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_ENHET2D].szNavn, "..ENHET-D", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_ENHET2D].ucAntPar = 1;
   pLn->sosi[L_ENHET2D].cNivo = 2;
   pLn->sosi[L_ENHET2D].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_ENHET3].szNavn, "...ENHET", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_ENHET3].ucAntPar = 1;
   pLn->sosi[L_ENHET3].cNivo = 3;
   pLn->sosi[L_ENHET3].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_ENHET3H].szNavn, "...ENHET-H", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_ENHET3H].ucAntPar = 1;
   pLn->sosi[L_ENHET3H].cNivo = 3;
   pLn->sosi[L_ENHET3H].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_ENHET3D].szNavn, "...ENHET-D", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_ENHET3D].ucAntPar = 1;
   pLn->sosi[L_ENHET3D].cNivo = 3;
   pLn->sosi[L_ENHET3D].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_ORIGONO].szNavn, "...ORIGO-NØ", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_ORIGONO].ucAntPar = 2;
   pLn->sosi[L_ORIGONO].cNivo = 3;
   pLn->sosi[L_ORIGONO].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_HOYDE].szNavn, "..HØYDE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_HOYDE].ucAntPar = 1;
   pLn->sosi[L_HOYDE].cNivo = 2;
   pLn->sosi[L_HOYDE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_DYBDE].szNavn, "..DYBDE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_DYBDE].ucAntPar = 1;                                   
   pLn->sosi[L_DYBDE].cNivo = 2;
   pLn->sosi[L_DYBDE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_NGISFLAGG].szNavn, "..NGIS-FLAGG", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_NGISFLAGG].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_NGISFLAGG].cNivo = 2;
   pLn->sosi[L_NGISFLAGG].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_NGISLAG].szNavn, "..NGIS-LAG", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_NGISLAG].ucAntPar = LC_ANT_PAR_UKJENT;
   pLn->sosi[L_NGISLAG].cNivo = 2;
   pLn->sosi[L_NGISLAG].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_OBJTYPE].szNavn, "..OBJTYPE", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_OBJTYPE].ucAntPar = 1;
   pLn->sosi[L_OBJTYPE].cNivo = 2;
   pLn->sosi[L_OBJTYPE].bBrukt = false;

   UT_StrCopy(pLn->sosi[L_KP].szNavn, "...KP", LC_MAX_SOSINAVN_LEN);
   pLn->sosi[L_KP].ucAntPar = 1;
   pLn->sosi[L_KP].cNivo = 3;
   pLn->sosi[L_KP].bBrukt = false;

   pLn->sAntNavn = L_KP + 1;           /* Antall navn i navnetabellen */
}


/*
AR-910919
CH LN_Enhet                                          Sjekk om det er ..ENHET
CD ==========================================================================
CD Formål:
CD Sjekk om denne ginfo-linjen er ..ENHET.
CD
CD Parametre:
CD Type             Navn        I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_NAVNETABELL *  pLn          i   Peker til navnetabell
CD char            *ginfo_linje  i   Første pos i linjen
CD short            ok           r   1=linjen er ..ENHET, 0=ikke ..ENHET
CD
CD Bruk:
CD ok = LN_Enhet(pLn,ginfo_linje);
  ===========================================================================
*/
short LN_Enhet(LC_NAVNETABELL * pLn,char *ginfo_linje)
{
   char ord[LC_MAX_SOSINAVN_LEN];

   //JAØ-20000313
   //Leter etter "..ENHET " istedet for "..ENHET" for ikke å få tilslag på ..ENHET-H eller ..ENHET-D
   UT_StrCopy(ord,pLn->sosi[L_ENHET2].szNavn,LC_MAX_SOSINAVN_LEN);
   UT_StrCat(ord, " ", LC_MAX_SOSINAVN_LEN);

   return(strstr(ginfo_linje,ord) != NULL);
   //return(strstr(ginfo_linje,pLn->sosi[L_ENHET2].szNavn) != NULL);
}


/*
AR-940704
CH LN_EnhetHoyde                                   Sjekk om det er ..ENHET-H
CD ==========================================================================
CD Formål:
CD Sjekk om denne ginfo-linjen er ..ENHET-H.
CD
CD Parametre:
CD Type             Navn        I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_NAVNETABELL *  pLn          i   Peker til navnetabell
CD char            *ginfo_linje  i   Første pos i linjen
CD short            ok           r   1=linjen er ..ENHET-H, 0=ikke ..ENHET-H
CD
CD Bruk:
CD ok = LN_EnhetHoyde(pLn,ginfo_linje);
  ===========================================================================
*/
short LN_EnhetHoyde(LC_NAVNETABELL * pLn,char *ginfo_linje)
{
   char ord[LC_MAX_SOSINAVN_LEN];

   // Leter etter "..ENHET-H " istedet for "..ENHET-H" for ikke å få tilslag på andre navn
   UT_StrCopy(ord,pLn->sosi[L_ENHET2H].szNavn,LC_MAX_SOSINAVN_LEN);
   UT_StrCat(ord, " ", LC_MAX_SOSINAVN_LEN);
                                         
   //return(strstr(ginfo_linje,pLn->sosi[L_ENHET2H].szNavn) != NULL);
   return(strstr(ginfo_linje,ord) != NULL);
}


/*
AR-940704
CH LN_EnhetDybde                                    Sjekk om det er ..ENHET-D
CD ==========================================================================
CD Formål:
CD Sjekk om denne ginfo-linjen er ..ENHET-D.
CD
CD Parametre:
CD Type             Navn        I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_NAVNETABELL *  pLn          i   Peker til navnetabell
CD char            *ginfo_linje  i   Første pos i linjen
CD short            ok           r   1=linjen er ..ENHET-D, 0=ikke ..ENHET-D
CD
CD Bruk:
CD ok = LN_EnhetDybde(pLn,ginfo_linje);
  ===========================================================================
*/
short LN_EnhetDybde(LC_NAVNETABELL * pLn,char *ginfo_linje)
{
   char ord[LC_MAX_SOSINAVN_LEN];

   // Leter etter "..ENHET-D " istedet for "..ENHET-D" for ikke å få tilslag på andre navn
   UT_StrCopy(ord,pLn->sosi[L_ENHET2D].szNavn,LC_MAX_SOSINAVN_LEN);
   UT_StrCat(ord, " ",LC_MAX_SOSINAVN_LEN);

   //return(strstr(ginfo_linje,pLn->sosi[L_ENHET2D].szNavn) != NULL);
   return(strstr(ginfo_linje,ord) != NULL);
}


/*
AR-910315
CH LN_TestOy                               Sjekk om referansen inneholder øy
CD ==========================================================================
CD Formål:
CD Sjekk om denne ginfo-linjen inneholder referanse med ØY.
CD Forutsetter at aktuell linje inneholder referanser. 
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------
CD char    *ginfo_linje  i   Første pos i linjen
CD short    ok           r   1=linjen har øy-flate, 0=ikke øy
CD
CD Bruk:
CD ok = LN_TestOy(char *ginfo_linje);
  ===========================================================================
*/
short LN_TestOy(char *ginfo_linje)
{
   if (strchr(ginfo_linje,'(') != NULL)  return 1;

   return 0;
}


/*
AR-910918
CH LN_FinnNavn                          Søk etter et SOSI-navn i navnetabelen
CD =============================================================================
CD Formål:
CD Søker etter navnet i navnetabellen.
CD (Ukjent navn blir ikke lagt inn i navnetabellen.)
CD
CD Parametre:
CD Type             Navn    I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_NAVNETABELL *  pLn      i    Peker til navnetabell
CD char            *streng   i    Peker til SOSI-navn. Avslutta av '\0'.
CD short           *navn_nr  u    Navnets linjenummer i navnetabellen
CD short            nivo     r    Antall prikker (0=ukjent navn, 1=gruppenavn, osv.)
CD
CD Bruk:
CD nivo = LN_FinnNavn(pLn,streng,&neste,&navn_nr);
   =============================================================================
*/
short LN_FinnNavn(LC_NAVNETABELL * pLn,char *navn,short *navn_nr)
{
   short nr = 0;

                                    /* Utfør søket */
   for (; nr < pLn->sAntNavn; nr++)
   {
      if (strncmp(navn,pLn->sosi[nr].szNavn,LC_MAX_SOSINAVN_LEN-1) == 0)
      {
         // Legger inn merke om at navnet er brukt
         pLn->sosi[nr].bBrukt = true;

         // Navnet er funnet, ==> returner
         *navn_nr = nr;
         return  (pLn->sosi[nr].cNivo);     /* Nivå */
      }
   }
   
   return 0;                         /* Ukjent navn */
}


/*
AR-910710
CH LN_PakkNavn                          Søk etter navn, legg inn ukjent navn
CD ==========================================================================
CD Formål:
CD Finner et SOSI-navn i navnetabellen.  (Max LC_MAX_SOSINAVN_LEN tegn.)
CD Hvis navnet er ukjent, blir det lagt inn i tabellen.
CD
CD Parametre:
CD Type            Navn    I/U Forklaring
CD --------------------------------------------------------------------------
CD LC_NAVNETABELL *  pLn     i   Peker til navnetabell
CD char            *navn    i  SOSI-navn.
CD short           *ant_par u  Antall parametre til dette navnet.
CD                             LC_ANT_PAR_UKJENT (-1) = Ant. param. er ukjent.
CD short           *navn_nr u  Navnenummer.
CD short            nivo    r  Antall prikker i navnet (1=gruppenavn, osv.)
CD
CD Bruk:
CD type = LN_PakkNavn(pLn,navn,&navn_nr,&ant_par);
   =============================================================================
*/
short LN_PakkNavn (LC_NAVNETABELL * pLn,const char *navn,short *navn_nr,short *ant_par)
{
   char nivo,*cp;
   short nr;
                                    /* Utfør søket */
   for (nr=0; nr < pLn->sAntNavn; nr++) 
   {
      if (strncmp(navn,pLn->sosi[nr].szNavn,LC_MAX_SOSINAVN_LEN-1) == 0)
      {
         // Legger inn merke om at navnet er brukt
         pLn->sosi[nr].bBrukt = true;

         // Navnet er funnet, ==> returner
         *ant_par = pLn->sosi[nr].ucAntPar;
         *navn_nr = nr;
         return  (pLn->sosi[nr].cNivo);     /* Nivå */
      }
   }

   /* Er det plass i tabellen for et nytt navn? */
   if (pLn->sAntNavn >= LC_MAX_NAVN) {
      UT_FPRINTF(stderr,"Utskrift av navnetabellen:\n");
      for (nr=0; nr < pLn->sAntNavn; nr++) {
         UT_FPRINTF(stderr,"%s\n",LN_VisNavn(pLn,nr));
      }
      LC_Error(21,"(LN_PakkNavn)","");
      exit (2);
   }   

   /* ----- Nytt navn */
   UT_StrCopy(pLn->sosi[pLn->sAntNavn].szNavn,navn,LC_MAX_SOSINAVN_LEN);
   pLn->sosi[pLn->sAntNavn].ucAntPar = (unsigned char) LC_ANT_PAR_UKJENT;
   *ant_par = LC_ANT_PAR_UKJENT;
   
   /* Finn antall prikker */
   nivo = 0;
   cp = const_cast<char*>(navn);
   while (*cp == '.') {
      nivo++;
      cp++;
   }
   pLn->sosi[pLn->sAntNavn].cNivo = nivo;

   // Legger inn merke om at navnet er brukt
   pLn->sosi[pLn->sAntNavn].bBrukt = true;

   *navn_nr = pLn->sAntNavn;

   pLn->sAntNavn++;

   /* Melding om ulovlig gruppestart */
   if (nivo <= 1) {
      LC_Error(22,"(LN_PakkNavn)",navn);
   }

   return (nivo);     /* Antall prikker */
}


/*
AR-910819
CH LN_GetNavn                               Hent en linje fra  navnetabellen
CD ==========================================================================
CD Formål:
CD Henter et navn fra navnetabellen.
CD
CD Parametre:
CD Type             Navn  I/U   Forklaring
CD --------------------------------------------------------------------------
CD LC_NAVNETABELL *  pLn    i    Peker til navnetabell
CD long             navn   i    Linjenummer i navnetabellen
CD char            *tx     r    Peker til SOSI-navn, NULL=ukjent linje
CD
CD Bruk:
CD cp = LN_GetNavn(pLn,navn_nr);
   =============================================================================
*/
char *LN_GetNavn(LC_NAVNETABELL * pLn,short navn)
{
   SOSINAVN *ip;

   if (navn >= 0  &&  navn < pLn->sAntNavn){
       ip = pLn->sosi + navn;
       return ip->szNavn;
   }

   return NULL;
}


/*
AR:2009-05-05
CH LC_GetElementNavn                                        Hent elementnavn
CD ==========================================================================
CD Formål:
CD Hent et elementnavn fra den interne navnetabellen i FYBA.
CD Denne tabellen inneholder både gruppenavn (.LINJE, .KURVE, ...) og
CD egenskapsnavn (..OBJTYPE, ..LTEMA, ...)
CD
CD Tabellen har tre logiske deler:
CD  - (Linje 0 - L_HODE): Forhåndsdefinerte gruppenavn.
CD  - (Linje L_HODE+1 - L_KP): Forhåndsdefinerte egenskapsnavn.
CD  - (Linje L_KP+1 - n): Andre elementnavn brukt i SOSI-filen etter
CD                        indeksoppbygging.
CD
CD Selv om egenskapen blir fjernet fra SOSI-filen blir navnet fortsatt
CD liggende i navnetabellen
CD
CD Parametre:
CD Type        Navn    I/U  Forklaring
CD --------------------------------------------------------------------------
CD LC_FILADM  *pFil     i   Peker til FilAdm
CD short       sNavnNr  i   Linjenummer i navnetabellen (0 - n)
CD bool       *bBrukt       Viser om navnet har/er brukt i filen
CD                          Hvis det har vært en gruppe som har brukt navnet blir
CD                          denne stående "true" selv om gruppen er slettet.
CD const char *pszNavn  r   Peker til elementnavn, 
CD                          NULL = ukjent fil eller ulovlig linjenummer
CD
CD
CD Bruk:
CD // Går gjennom alle navnene ut over de forhåndsdefinerte navnene.
CD short sNavnNr = L_KP+1; 
CD while ((pszNavn = LC_GetElementNavn(pFil,sNavnNr)) != NULL)
CD {
CD    // Gjør noe med navnet
CD    ...
CD    ++sNavnNr;
CD }
=============================================================================
*/
SK_EntPnt_FYBA const char *LC_GetElementNavn(LC_FILADM *pFil,short sNavnNr,bool *bBrukt)
{
   LO_TestFilpeker(pFil,"GetNavn");

   LC_NAVNETABELL *pLn = &(pFil->SosiNavn);    //Peker til filens navnetabell

   if (sNavnNr >= 0  &&  sNavnNr < pLn->sAntNavn)
   {
      SOSINAVN *ip = pLn->sosi + sNavnNr;

      *bBrukt = ip->bBrukt;

      return ip->szNavn;
   }

   return NULL;
}


/*
AR-910819
CH LN_VisNavn                                Hent en linje fra  navnetabellen
CD =============================================================================
CD Formål:
CD Henter en linje fra navnetabellen som formatert streng.
CD
CD Parametre:
CD Type             Navn  I/U   Forklaring
CD -----------------------------------------------------------------------------
CD LC_NAVNETABELL *  pLn    i    Peker til navnetabell
CD long             navn   i    Linjenummer i navnetabellen som skall vises
CD char            *tx     r    Peker til streng med formatert linje
CD
CD Bruk:
CD for (navn=0,linje=10; navn<10; navn++,linje++){
CD     SH_OutTx(linje,1,LN_VisNavn(pLn,navn));
CD }
   =============================================================================
*/
char *LN_VisNavn(LC_NAVNETABELL * pLn,short navn)
{
   SOSINAVN *ip;

   if (navn < pLn->sAntNavn){
       ip = pLn->sosi + navn;
       UT_SNPRINTF(err().tx,LC_ERR_LEN,"%2d %16s", navn,ip->szNavn);
   } else{
       *err().tx = '\0';
   }

   return err().tx;
}


/*
AR-940413
CH LN_TolkKvalitet                                             Tolk KVALITET
CD ==========================================================================
CD Formål:
CD Tolk parameterstrengen for KVALITET.
CD
CD Parametre:
CD Type    Navn         I/U   Forklaring
CD -------------------------------------------------------------------------
CD char   *pszParameter       i  Peker til '\0'-avslutta streng, eller
CD                                 NULL hvis KVALITET mangler.
CD short  *psMetode           u  Hvordan data er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD                                 KVAL_MET_STD    standard metode fra nivå over.
CD long   *plNoyaktighet      u  Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT nøyaktighet er ukjent.
CD                                 KVAL_NOY_STD    standard nøyaktighet fra nivå over.
CD short  *psSynbarhet        u  Synbarhet i bilde
CD                                 KVAL_SYN_GOD    godt synlig.
CD                                 KVAL_SYN_UNDEF  synbarhet er udefinert.
CD                                 KVAL_SYN_STD    standard metode fra nivå over.
CD short  *psHoydeMetode      u  Hvordan høyden er registrert.
CD                                 KVAL_MET_UNDEF  metode er udefinert.
CD                                 KVAL_MET_STD    standard metode fra nivå over.
CD long   *plHoydeNoyaktighet u  Registreringsnøyaktighet
CD                                 KVAL_NOY_UKJENT nøyaktighet er ukjent.
CD                                 KVAL_NOY_STD    standard nøyaktighet fra nivå over.
CD
CD Bruk:
CD   ist = LN_TolkKvalitet(pszParameter,&sMetode,&lNoyaktighet,&sSynbarhet,
CD                         &sHoydeMetode,&lHoydeNoyaktighet);
CD =============================================================================
*/
void LN_TolkKvalitet(char *pszParameter,short *psMetode,long *plNoyaktighet,
                     short *psSynbarhet,short *psHoydeMetode,long *plHoydeNoyaktighet)
{
   char ord[32];
   short i;
   char szMetode[6] = {"*"};
   char szNoyaktighet[11] = {"*"};
   char szSynbarhet[6] = {"0"};
   char szHoydeMetode[6] = {" "};
   char szHoydeNoyaktighet[11] = {" "};

   /* Er det noen parameterstreng? */
   if (pszParameter) {
                              /* Hent strengene */
      if (UT_StrToken(pszParameter,0,&i,32,ord)) {
         UT_StrCopy(szMetode,ord,6);

         if (UT_StrToken(pszParameter,i,&i,32,ord)) {
            UT_StrCopy(szNoyaktighet,ord,10);

            if (UT_StrToken(pszParameter,i,&i,32,ord)) {
               UT_StrCopy(szSynbarhet,ord,6);

               if (UT_StrToken(pszParameter,i,&i,32,ord)) {
                  UT_StrCopy(szHoydeMetode,ord,6);

                  if (UT_StrToken(pszParameter,i,&i,32,ord)) {
                     UT_StrCopy(szHoydeNoyaktighet,ord,10);
                  }
               }
            }
         }
      }
   }

   /* Tolk strengene til tallverdier */
   if (*szMetode == '*') {
      *psMetode = KVAL_MET_UNDEF;
   } else if (*szMetode == '@') {
      *psMetode = KVAL_MET_STD;
   } else {
      UT_StrShort(szMetode,0,&i,psMetode);
   }

   if (*szNoyaktighet == '*') {
      *plNoyaktighet = KVAL_NOY_UKJENT;
   } else if (*szNoyaktighet == '@') {
      *plNoyaktighet = KVAL_NOY_STD;
   } else {
      UT_StrLong(szNoyaktighet,0,&i,plNoyaktighet);
   }

   if (*szSynbarhet == '*') {
      *psSynbarhet = KVAL_SYN_UNDEF;
   } else if (*szSynbarhet == '@') {
      *psSynbarhet = KVAL_SYN_STD;
   } else {
      UT_StrShort(szSynbarhet,0,&i,psSynbarhet);
   }

   if (*szHoydeMetode == '*') {
      *psHoydeMetode = KVAL_MET_UNDEF;
   } else if (*szHoydeMetode == '@') {
      *psHoydeMetode = KVAL_MET_STD;
   } else if (*szHoydeMetode == ' ') {
      *psHoydeMetode = *psMetode;
   } else {
      UT_StrShort(szHoydeMetode,0,&i,psHoydeMetode);
   }

   if (*szHoydeNoyaktighet == '*') {
      *plHoydeNoyaktighet = KVAL_NOY_UKJENT;
   } else if (*szHoydeNoyaktighet == '@') {
      *plHoydeNoyaktighet = KVAL_NOY_STD;
   } else if (*szHoydeNoyaktighet == ' ') {
      *plHoydeNoyaktighet = *plNoyaktighet;
   } else {
      UT_StrLong(szHoydeNoyaktighet,0,&i,plHoydeNoyaktighet);
   }

   return;
}


/*
AR-940413
CH LC_FormatterKvalitet                                   Formatter KVALITET
CD ==========================================================================
CD Formål:
CD Formater parameterstrengen for KVALITET.
CD Resultatet legges i en intern streng, og må kopieres over til andre
CD variabler før endring.
CD
CD Parametre:
CD Type    Navn         I/U   Forklaring
CD -------------------------------------------------------------------------
CD short   sMetode           i Hvordan data er registrert.
CD                               KVAL_MET_UNDEF  metode er udefinert.
CD                               KVAL_MET_STD    standard metode fra nivå over.
CD long    lNoyaktighet      i Registreringsnøyaktighet
CD                               KVAL_NOY_UKJENT nøyaktighet er ukjent.
CD                               KVAL_NOY_STD    standard nøyaktighet fra nivå over 
CD short   sSynbarhet        i Synbarhet i bilde
CD                               KVAL_SYN_GOD    godt synlig.
CD                               KVAL_SYN_UNDEF  synbarhet er udefinert.
CD                               KVAL_SYN_STD    standard metode fra nivå over.
CD short   sHoydeMetode      i Hvordan data er registrert.
CD                               KVAL_MET_UNDEF  metode er udefinert.
CD                               KVAL_MET_STD    standard metode fra nivå over.
CD long    lHoydeNoyaktighet i Registreringsnøyaktighet
CD                               KVAL_NOY_UKJENT nøyaktighet er ukjent.
CD                               KVAL_NOY_STD    standard nøyaktighet fra nivå over 
CD char   *pszParameter      r Peker til '\0'-avslutta streng.
CD
CD Bruk:
CD  pszParameter = LC_FormatterKvalitet(sMetode,lNoyaktighet,sSynbarhet,
CD                                      sHoydeMetode,lHoydeNoyaktighet);
CD =============================================================================
*/
SK_EntPnt_FYBA char *LC_FormatterKvalitet(short sMetode,long lNoyaktighet,short sSynbarhet,
                           short sHoydeMetode,long lHoydeNoyaktighet)
{
   static char szParameter[60];
   char szMetode[8] = {"*"};
   char szNoyaktighet[13] = {" *"};
   char szSynbarhet[8] = {" *"};
   char szHoydeMetode[8] = {" *"};
   char szHoydeNoyaktighet[13] = {" *"};


   /* Metode */
   if (sMetode == KVAL_MET_STD) {
      *szMetode = '@';
   } else if (sMetode != KVAL_MET_UNDEF) {
      UT_SNPRINTF(szMetode,8,"%hd",sMetode);
   }

   /* Nøyaktighet */
   if (lNoyaktighet == KVAL_NOY_STD) {
      szNoyaktighet[1] = '@';
   } else if (lNoyaktighet != KVAL_NOY_UKJENT  && lNoyaktighet != KVAL_NOY_UNDEF) {
      UT_SNPRINTF(szNoyaktighet,13," %ld",lNoyaktighet);
   }

   /* Synbarhet */
   if (sSynbarhet == KVAL_SYN_STD) {
      szSynbarhet[1] = '@';
   } else if (sSynbarhet != KVAL_SYN_UNDEF) {
      UT_SNPRINTF(szSynbarhet,8," %hd",sSynbarhet);
   }

   /* Høyde-metode */
   if (sHoydeMetode == KVAL_MET_STD) {
      szHoydeMetode[1] = '@';
   } else if (sHoydeMetode != KVAL_MET_UNDEF) {
      UT_SNPRINTF(szHoydeMetode,8," %hd",sHoydeMetode);
   }

   /* Høyde-nøyaktighet */
   if (lHoydeNoyaktighet == KVAL_NOY_STD) {
      szHoydeNoyaktighet[1] = '@';
   } else if (lHoydeNoyaktighet != KVAL_NOY_UKJENT  &&  lHoydeNoyaktighet != KVAL_NOY_UNDEF) {
      UT_SNPRINTF(szHoydeNoyaktighet,13," %ld",lHoydeNoyaktighet);
   }

   
   /* Bygg opp parameterstrengen */

   UT_StrCopy(szParameter,szMetode,60);

   if (szNoyaktighet[1] != '*'         ||
       sSynbarhet != KVAL_SYN_GOD      ||
       sHoydeMetode != sMetode         ||
       lHoydeNoyaktighet != lNoyaktighet) {

      UT_StrCat(szParameter,szNoyaktighet,60);

      if (sSynbarhet != KVAL_SYN_GOD      ||
          sHoydeMetode != sMetode         ||
          lHoydeNoyaktighet != lNoyaktighet) {

         UT_StrCat(szParameter,szSynbarhet,60);

         if (sHoydeMetode != sMetode         ||
             lHoydeNoyaktighet != lNoyaktighet) {

            UT_StrCat(szParameter,szHoydeMetode,60);

            if (lHoydeNoyaktighet != lNoyaktighet) {
               UT_StrCat(szParameter,szHoydeNoyaktighet,60);
            }
         }
      }
   }

   return szParameter;
}


/*
AR: 2000-01-19
CH LC_FinnNivo                                     Beregn nivå
CD ==============================================================
CD Formål:
CD Teller antall prikker i starten på egenskapsnavn.
CD
CD PARAMETERLISTE:
CD Type     Navn      I/U   Merknad
CD -------------------------------------------------------------
CD char    *pszGinfo   i    Streng med egenskapsnavn i starten
CD short    sNivo      r    Antall prikker 
CD
CD Bruk:
CD sNivo = LC_FinnNivo(pszGinfo);
  ================================================================
*/
SK_EntPnt_FYBA short LC_FinnNivo(const char * pszNavn)
{
   short sNivo = 0;

   while (*pszNavn != '\0'  &&  *pszNavn == '.') {
      ++pszNavn;
      ++sNivo;
   }

   return sNivo;
}
