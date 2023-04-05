//////////////////////////////////////////////////////////////////////////
//
// Fil: Fyba_melding.cpp
// Eier: Statens kartverk, FYSAK-prosjektet
//
//////////////////////////////////////////////////////////////////////////
//
// Denne filen inneholder eksempel på callback-rutiner som kalles
// av FYBA for feilmeldings-handtering og visning av framdrift under
// indeksoppbygging.
//
// For å få et godt brukergrensesnitt bør disse rutinene endres til
// det meldings og feilhandteringssystemet som brukes av hovedprogrammet.
//
// Rutinene må kompileres og linkes sammen med hovedprogrammet når
// FYBA brukes som LIB.
//
//////////////////////////////////////////////////////////////////////////


//
// Innholdet i rutinene må byttes ut med meldingshandtering som er tilpasset
// det aktuelle hovedprogrammet.
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// Fyba_melding.cpp
//
// Denne filen inneholder eksempel på rutiner som må linkes inn i
// hovedprogrammet når FYBA brukes som LIB.
//
//////////////////////////////////////////////////////////////////////////


#include "fyba.h"

#ifdef WIN32
#include <windows.h>
#endif


//static short sProsent;


/*
AR-890911
CH LC_Error                                                  Feilmeldingsrutine
CD =============================================================================
CD Formål:
CD Standard feilmeldingsrutine.
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------------
CD short    feil_nr      i   Feil-nummer
CD char    *logtx        i   Tekst som bare skrives til logfil.
CD                           Eks:"(utført i LC_RxGr)"
CD char    *vartx        i   Denne tekststreng henges etter feilmeldingsteksten.
CD
CD Bruk:
CD LC_Error(35,"(Kallt i LC_Error)","");
   =============================================================================
*/
void LC_Error(short feil_nr,const char *logtx,const char *vartx)
{
   char szErrMsg[260];
   short strategi;
   char *pszFeilmelding;


   // Egen enkel implementasjon av feilhandtering
   /* Hent feilmeldingstekst og strategi */
   strategi = LC_StrError(feil_nr,&pszFeilmelding);
   switch(strategi) {
      case 2:  UT_SNPRINTF(szErrMsg,260,"%s","Observer følgende! \n\n");  break;
      case 3:  UT_SNPRINTF(szErrMsg,260,"%s","Det er oppstått en feil! \n\n");  break;
      case 4:  UT_SNPRINTF(szErrMsg,260,"%s","Alvorlig feil avslutt programmet! \n\n");  break;
      default: szErrMsg[0]='\0';
   }

   #ifdef WIN32

   if (UT_StrCat (szErrMsg,pszFeilmelding, sizeof(szErrMsg))) {
      if (UT_StrCat (szErrMsg,&vartx[0], sizeof(szErrMsg))) {
         MessageBox(NULL, szErrMsg, "Melding fra FYBA ", MB_ICONHAND | MB_OK);

      } else {
         MessageBox(NULL, "Klarer ikke å vise teksten", "Melding fra FYBA ", MB_ICONHAND | MB_OK);
      }

   } else {
      MessageBox(NULL, "Klarer ikke å vise teksten", "Melding fra FYBA ", MB_ICONHAND | MB_OK);
   }
   #else 
      printf("\nError: %s ",pszFeilmelding);
      fflush(stdout);
   #endif
}


/*
AR-900609
CH LC_StartMess                                          Vise melding
CD =============================================================================
CD Formål:
CD Starter vising av melding om baseoppbygging.
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------------
CD char    *pszFilnavn   i   Ekstra meldingstekst  (filnavn)
CD
CD Bruk:
CD LC_StartMess(pszFilnavn);
   =============================================================================
*/
void LC_StartMessage(char const *pszFilnavn)
{
#ifndef LINUX
      printf("\nLeser: %s ",pszFilnavn);
      printf("\n0%%");
      fflush(stdout);
#endif
}


/*
AR-900609
CH LC_ShowMess                                          Vise melding
CD =============================================================================
CD Formål:
CD Vising av melding om baseoppbygging.
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------------
CD double   prosent      i   Prosent ferdig (0.0 - 100.0)
CD
CD Bruk:
CD LC_ShowMess(prosent);
   =============================================================================
*/
void LC_ShowMessage(double prosent)
{
#ifndef LINUX
      printf("\r%d%%",(short)prosent);
      fflush(stdout);
#endif
}


/*
AR-900609
CH LC_EndMess                                          Avslutt melding
CD =============================================================================
CD Formål:
CD Avslutt melding om baseoppbygging.
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------------
CD
CD Bruk:
CD LC_EndMess();
   =============================================================================
*/
void LC_EndMessage(void)
{
#ifndef LINUX
      printf("\r100%% ferdig.");
      fflush(stdout);
#endif
}


/*
AR-910402
CH LC_Cancel                                         Sjekk om Esc er trykket
CD ==========================================================================
CD Formål:
CD Sjekk om det er trykkt på Esc (Avbryte indeksoppbygging).
CD
CD
CD Parametre:
CD Type   Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD short  sAvbrutt   r    UT_TRUE  = Cancel
CD                        UT_FALSE = ikke avbrudd
CD
CD Bruk:
CD sAvbrutt = LC_Cancel();
   ==========================================================================
*/
short LC_Cancel(void)
{
      /* Ikke mulig å avbryte */
      return UT_FALSE;
}

