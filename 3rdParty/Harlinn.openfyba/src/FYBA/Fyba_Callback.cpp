//////////////////////////////////////////////////////////////////////////
//
// Fil: Fyba_Callback.cpp
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
// En tilsvarende enkel feilmeldingshandtering ligger i FYBA_DLL.DLL.
// Denne (DLL'ens) meldingshandtering blir brukt hvis meldingsingsrutinene
// ikke blir registrert av hovedprogrammet.
//
// Meldingsrutinene registreres med følgende rutiner:
//  - LC_SetErrorHandler
//  - LC_SetStartMessageHandler
//  - LC_SetShowMessageHandler
//  - LC_SetEndMessageHandler
//  - LC_SetCancelHandler
//
//////////////////////////////////////////////////////////////////////////


//#include "stdafx.h"

#include "fyba.h"

#ifdef WIN32
#  include <windows.h>
#endif

#ifdef LINUX

#include <termios.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/ioctl.h>

  int _kbhit() {
    static const int STDIN = 0;
    static bool bInit = false;

    if (! bInit) {
      termios term;
      tcgetattr(STDIN, &term);
      term.c_lflag &= ~ICANON;
      tcsetattr(STDIN, TCSANOW, &term);
      setbuf(stdin, NULL);
      bInit = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
  }
#else
#  include <conio.h>
#endif

/*
AR-930907
CH LC_ErrorHandler                                             Feilmelding
CD ==========================================================================
CD Formål:
CD Feilmelding.
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD --------------------------------------------------------------------------
CD short    feil_nr      i   Feilmeldingsnummer
CD char    *logtx        u   Peker til feilmeldingstekst avslutta med '\0'.
CD char    *vartx        u   Peker til feilmeldingstekst avslutta med '\0'.
CD
CD Bruk:
CD LC_SetErrorHandler(LC_ErrorHandler);
   ==========================================================================
*/
void LC_ErrorHandler (short feil_nr, const char logtx[], const char vartx[])
{
	short strategi;
	char *feilmelding;

                    /* Hent feilmeldingstekst og strategi */
    strategi = LC_StrError(feil_nr,&feilmelding);

                             /* Meldingen skrives */
    if (strategi > 0) {
       printf("\n%s %s\n",feilmelding,vartx);
       switch(strategi) {                           /* Velg strategi */
           case 1:
           case 2:
               break;
           case 3:
               printf("\aTrykk [Enter] for å fortsette:");
					if (getchar() == 0)  getchar();
               break;
			  case 4:
					printf("\aTrykk [Enter] for å avbryte programmet:");
					if (getchar() == 0)  getchar();
					exit(2);
					break;
		 }
	}
}


/*
AR-900609
CH LC_StartMessageHandler                                    Starte meldingsvisning
CD =============================================================================
CD Formål:
CD Starter vising av melding om baseoppbygging.
CD
CD Her skal brukerprogrammet legge inn sin egen initiering av visning av framdrift
CD under indeksoppbygging.
CD
CD Denne rutinen blir kallt fra FYBA under indeksoppbygging, og den skal
CD ikke kalles fra brukerprogramvaren.
CD
CD
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------------
CD char    *cfil         i   Ekstra meldingstekst  (filnavn)
CD
CD Bruk:
CD LC_SetStartMessageHandler(LC_StartMessageHandler);
   =============================================================================
*/
void LC_StartMessageHandler(const char *fnam)
{
#ifndef LINUX
      printf("\nLeser: %s ",fnam);
      printf("\n0%%");
      fflush(stdout);
#endif
}


/*
AR-900609
CH LC_ShowMessageHandler                                          Vise melding
CD =============================================================================
CD Formål:
CD Vising av melding om baseoppbygging.
CD
CD Her skal brukerprogrammet legge inn sin egen av visnig av framdrift
CD under indeksoppbygging.
CD
CD Denne rutinen blir kalt fra FYBA under indeksoppbygging, og den skal
CD ikke kalles fra brukerprogramvaren.
CD
CD Parametre:
CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------------
CD double   prosent      i   Prosent ferdig (0.0 - 100.0)
CD
CD Bruk:
CD LC_SetShowMessageHandler(LC_ShowMessageHandler);
   =============================================================================
*/
void LC_ShowMessageHandler(double prosent)
{
#ifndef LINUX
      printf("\r%d%%",(short)prosent);
      fflush(stdout);
#endif
}


/*
AR-900609
CH LC_EndMessageHandler                                          Avslutt melding
CD =============================================================================
CD Formål:
CD Avslutt melding om baseoppbygging.
CD
CD Her skal brukerprogrammet legge inn sin egen avslutning av visning av framdrift
CD under indeksoppbygging.
CD
CD Denne rutinen blir kalt fra FYBA under indeksoppbygging, og den skal
CD ikke kalles fra brukerprogramvaren.
CD
CD Parametre:
Dette CD Type     Navn        I/U  Forklaring
CD -----------------------------------------------------------------------------
CD
CD Bruk:
CD LC_SetEndMessageHandler(LC_EndMessageHandler);
   =============================================================================
*/
void LC_EndMessageHandler(void)
{
#ifndef LINUX
      printf("\r100%% ferdig.");
      fflush(stdout);
#endif
}


/*
AR-910402
CH LC_CancelHandler                                  Sjekk om Esc er trykket
CD ==========================================================================
CD Formål:
CD Sjekk om det er trykt på Esc (Avbryte indeksoppbygging).
CD
CD Parametre:
CD Type   Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD short  sAvbrutt   r    UT_TRUE  = Cancel
CD                        UT_FALSE = ikke avbrudd
CD
CD Bruk:
CD LC_SetCancelHandler(LC_CancelHandler);
   ==========================================================================
*/
short LC_CancelHandler(void)
{
   int tast = 0;

   if (_kbhit()) {
      tast = getchar();
   }
   return ((tast == 27)?  UT_TRUE : UT_FALSE );
}
