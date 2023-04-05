/******************************************************************^$date;
*                                                                           *
*       Hjelpebiblioteket   U T  (Utilities)                                *
*       Lars Staurset, Statens Kartverk / FYSAK-prosjektet, januar 1990     *
*       Fil: UT4.C: Handtering av flag-tabell                               *
*                                                                           *
****************************************************************************/

//#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "fyut.h"


/**************************************************************************
*                                                                         *
*       RUTINER FOR Å HANDTERE FLAG-TABELL                                *
*                                                                         *
***************************************************************************/

/*
OJ-920309
CH UT_InitFlag
CD ==========================================================================
CD Formål:
CD Opprette og nullstille flag-tabell.
CD
CD Parametre:
CD Type        Navn        I/U   Forklaring
CD --------------------------------------------------------------------------
CD short       sNlin        i    Antall linjer.
CD long[]      *plFlag      r    Peker til minneblokk for flagging.
CD
CD Bruk:
CD plFlag = UT_InitFlag(sNgi,&sAktLines);
   ==========================================================================
*/
SK_EntPnt_UT unsigned long *UT_InitFlag(short sNlin)
{
   unsigned long *plFlag;

   unsigned long ulAntUL = UT_RoundDL(ceil((double)(sNlin + 1) / (double)(sizeof(unsigned long) * 8)));
	plFlag = (unsigned long *)UT_MALLOC((size_t)((ulAntUL+1) * (sizeof(unsigned long))));
   memset(plFlag,0,(size_t)((ulAntUL+1) * (sizeof(unsigned long))));

   *plFlag = (unsigned long)sNlin;

   return plFlag;
}

/*
OJ-920309
CH UT_CloseFlag
CD ==========================================================================
CD Formål:
CD Frigjøre minne brukt til flagging av brukte linjer.
CD
CD Parametre:
CD Type        Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD long        *plFlag    I    Peker til minneblokk for flagging.
CD
CD Bruk:
CD UT_CloseFlag(plFlag);
   ==========================================================================
*/
SK_EntPnt_UT void UT_CloseFlag(unsigned long *plFlag)
{
	UT_FREE((void *)(plFlag));
	plFlag = NULL;
}

/*
OJ-920309
CH UT_SetFlag                                 Flagger brukt linje.
CD ==========================================================================
CD Formål:
CD Legg inn merke i linje tabell.
CD
CD Parametre:
CD Navn              Type        I/U   Forklaring
CD --------------------------------------------------------------------------
CD bStatus          bool        r     Returstatus, UT_TRUE=OK, UT_FALSE=flagging feilet
CD unsigned long   *plFlag      i     Peker til minneblokk for flagging.
CD short            sLine       i     Linje som skal flagges som brukt.
CD
CD Bruk:
CD bStatus = UT_SetFlag(plFlag,sLine)
   ==========================================================================
*/
// SK_EntPnt_UT void UT_SetFlag(unsigned long *plFlag,short sLine)
SK_EntPnt_UT bool UT_SetFlag(unsigned long *plFlag,short sLine)
{

   // char szErrMsg[80];

        /* Maksimalt: antall long * 32 - 1 for bit 0 i første */
   /*
   if (sLine >= (short)*plFlag){
      UT_SNPRINTF(szErrMsg,80,"For mange -linjer %hd, maksimalt: %hd",sLine,(short)*plFlag-1);
   }
   *(plFlag + (sLine / (sizeof(unsigned long) * 8)) + 1) |=
                     (0x00000001L << (sLine % (sizeof(unsigned long) * 8)));
   */

   // JEK 20090428 Gjort om til boolsk funksjon
   if (sLine < (short)*plFlag){
      *(plFlag + (sLine / (sizeof(unsigned long) * 8)) + 1) |=
         (0x00000001L << (sLine % (sizeof(unsigned long) * 8)));
      return UT_TRUE;
   }else{
      // UT_SNPRINTF(szErrMsg,80,"For mange -linjer %hd, maksimalt: %hd",sLine,(short)*plFlag-1);
      return UT_FALSE;
   }
}


/*
OJ-920309
CH UT_GetFlag                                 Flagger brukt -linje.
CD ==========================================================================
CD Formål:
CD Teste merke i linje tabell.
CD
CD Parametre:
CD Navn        Type      I/U   Forklaring
CD --------------------------------------------------------------------------
CD unsigned long       *plFlag    i    Peker til minneblokk for flagging.
CD short       sLine      i    Linje som skal hentes.
CD
CD Bruk:
CD UT_GetFlag(plFlag,sNlines,sLine)
   ==========================================================================
*/
SK_EntPnt_UT short UT_GetFlag(unsigned long *plFlag,short sLine)
{
   char szErrMsg[80];

        /* Maksimalt: antall long * 32 - 1 for bit 0 i første */
   if (sLine >= (short)*plFlag){
      UT_SNPRINTF(szErrMsg,80,"For mange -linjer %hd, maksimalt: %hd",sLine,(short)*plFlag-1);
   }
   return ((*(plFlag + (sLine / (sizeof(unsigned long) * 8)) + 1)  &
            (0x00000001L << (sLine % (sizeof(unsigned long) * 8)))) == 0)?
                                                           UT_FALSE : UT_TRUE;
}
