/* === 900607 ============================================================= */
/*  STATENS KARTVERK  -  FYSAK-PC                                           */
/*  Fil: fyta.c                                                             */
/*  Innhold: Lagring og henting av "fil"-tabeller                           */
/* ======================================================================== */

#include "fyba.h"
#include "fybax.h"
#include <stdio.h>

#include <fcntl.h>


/* Div. styrevariabler */
#define NY    0
#define LES   1
#define SKRIV 2

/* Tabellsystem */
static short fytab_open = 0;
static struct {
   FILE   *fpek;
   size_t recl;
   short  modus;
   long   cur_lin;
} fytab;


/*
AR-900105
CH LC_InitTabel                                           �pner tabellsystemet
CD =============================================================================
CD Form�l:
CD Initierer tabellsystemet og �pner filen.
CD
CD Parametre:
CD Type     Navn      I/U   Forklaring
CD -----------------------------------------------------------------------------
CD long     n_rec      i    Antall reckords som skal nullstilles. Disse kan
CD                          etterp� brukes til tilfeldig aksess. Utvidelse
CD                          av filen kan senere bare skje i fortl�pende
CD                          rekkef�lge.
CD short    rec_len    i    Reckordlengde. (Bruk sizeof for � finne lengden.)
CD void    *buffer     i    Peker til buffer som skal brukes for nullstilling.
CD short    ist        r    Status. (0=OK, -1=feil)
CD
CD Bruk:
CD  .
CD  struct{
CD     long snr;
CD     short ngi;
CD     short nko;
CD  } buffer;
CD  .   
CD  .
CD  ist = LC_InitTabel(10000L,sizeof buffer,(void *)(&buffer));
CD  .   
CD  ist = LC_PutTabel(linje,(void *)&buffer);
CD  .   
CD  ist = LC_GetTabel(linje,(void *)&buffer);
CD  .   
CD  LC_CloseTabel();
   =============================================================================
*/
SK_EntPnt_FYBA short LC_InitTabel(long n_rec,short rec_len,void *buffer)
{
   short ierr;

   if (fytab_open){                    /* Systemet er allerede i bruk */
      return -1;
   }
                                       /* �pner tabellfilen */
   fytab.fpek = UT_OpenFile("fytabell.tmp","",UT_UPDATE,UT_UNKNOWN,&ierr);
   if (ierr != UT_OK){                 /* �pningsfeil */
      return -1;
   }

   fytab.recl = rec_len;

                                  /* Nullstill tabellen */
   if (fseek(fytab.fpek,0L,SEEK_SET) != 0){
      return -1;
   }
   for (; n_rec>0; n_rec--){
      if (fwrite(buffer,fytab.recl,1,fytab.fpek) != 1){
         return  -1;
      }
   }

   fytab.modus = NY;
   fytab_open = 1;                /* Merke for at systemet aktivisert */

   return 0;
}


/*
AR-900106
CH LC_GetTabel                                               Get tabell-linje
CD =============================================================================
CD Form�l:
CD Henter en linje fra tabellfilen.
CD
CD Parametre:
CD Type      Navn   I/U   Forklaring
CD -----------------------------------------------------------------------------
CD long      linje   i    Linjenummer som skal hentes.  (0 er f�rste linje)
CD void     *buffer  i    Peker til struktur som skal ta mot lest reckord.
CD short     ist     r    Status (0=OK, -1=feil)
CD
CD Bruk:
CD ist = LC_GetTabel(linje,(void *)&buffer);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_GetTabel(long linje,void *buffer)
{
   if ( ! fytab_open){        /* Systemet er ikke aktivisert */
      return -1;
   }

   if (fytab.modus != LES || fytab.cur_lin != linje){       /* Posisjoner */
      if (fseek(fytab.fpek,(long)(linje * fytab.recl),SEEK_SET) != 0){
         return  -1;
      }
   }

   if (fread(buffer,fytab.recl,1,fytab.fpek) != 1){               /* Les */
       return  -1;
   }

   fytab.modus = LES;
   fytab.cur_lin = linje + 1L;

   return 0;
}


/*
AR-900106
CH LC_PutTabel                                               Put tabell-linje
CD =============================================================================
CD Form�l:
CD Legg inn en linje fra tabellfilen.
CD
CD Parametre:
CD Type      Navn   I/U   Forklaring
CD -----------------------------------------------------------------------------
CD long      linje   i    Linjenummer som skal legges inn. (0 er f�rste linje)
CD                        (St�rste lovlige er 1 st�rre enn det st�rste hittil.)
CD void     *buffer  i    Peker til struktur som skal legges inn.
CD short     ist     r    Status (0=OK, -1=feil)
CD
CD Bruk:
CD ist = LC_PutTabel(linje,(void *)&buffer);
   =============================================================================
*/
SK_EntPnt_FYBA short LC_PutTabel(long linje,void *buffer)
{
   if ( ! fytab_open){        /* Systemet er ikke aktivisert */
      return -1;
   }

   if (fytab.modus != SKRIV || linje != fytab.cur_lin){    /* Posisjoner */
      if (fseek(fytab.fpek,(long)(linje * fytab.recl),SEEK_SET) != 0){
         return -1;
      }
   }

   if (fwrite(buffer,fytab.recl,1,fytab.fpek) != 1){  /* Skriv */
      return  -1;
   }

   fytab.modus = SKRIV;
   fytab.cur_lin = linje + 1L;

   return 0;
}


/*
AR-900106
CH LC_CloseTabel                                        Stenge tabellsystemet
CD =============================================================================
CD Form�l:
CD Avslutter tabellsystemet og stenger og sletter filen.
CD Tabellen kan n� �pnes p� nytt for annen bruk.
CD
CD Parametre: ingen
CD    
CD Bruk:
CD LC_CloseTabel();
   =============================================================================
*/
SK_EntPnt_FYBA void LC_CloseTabel(void)
{
   if (fytab_open){
      fclose(fytab.fpek);            /* Stenger tabellfilen */
      UT_DeleteFile("fytabell.tmp");        /* Sletter tabellfilen */
      fytab_open = 0;                /* Merke for at systemet er stengt */
   }
}
