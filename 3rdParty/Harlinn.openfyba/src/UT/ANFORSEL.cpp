/*
CD AR-920127
CH Anforsel                  Legger til eller fjerner anførseltegn
CD ===============================================================
CD
CD Eier.......: STATENS KARTVERK / FYSAK-prosjektet
CD Ansvarlig..: Åge Eliassen
CD
CD ===============================================================
*/

#include "fyba.h"
#include <string.h>

#include "fyut.h"


/*
OJ-2003-12-03
ÅE-950401
CH UT_PutAnfTegn           Legg inn / fjern anførseltegn forran og bak streng
CD ===========================================================================
CD Formål:
CD Legger inn eller fjerner anførseltegn forran eller bak parameter-streng.
CD Ved rydding av anførseltegn ryddes også tegn inni strengen.
CD Ved rydding må parameterstrengen bestå av mer enn ett tegn.
CD
CD PARAMETERLISTE:
CD Type   Navn       I/U   Merknad
CD --------------------------------------------------------------------------
CD char  *pszTx       iu   Tekststreng som skal behandles
CD char   cTegn       i    Styreparameter:
CD                           "  = Omslutt pszTx med  ' " '
CD                           '  = Omslutt pszTx med  " ' "
CD                           F  = Fjern anførselstegn fra strengen
CD short  sMaksLen    i    Makslimal lengde på streng inklusiv null-termiantor
CD short  sOk         r    Feilstatus. UT_OK hvis ok, UT_ERROR hvis strengen er
CD                         for kort til å føye på anførselstegn.
CD
CD Bruk:
CD bOk = UT_PutAnfTegn(pszTx,cTegn, sMaksLen);
CD =============================================================================
*/
SK_EntPnt_UT short UT_PutAnfTegn(char *pszTx, char cTegn, short sMaksLen)
{
   short i,ii,sTxtLen;
   char t1,t2;
   short sOk = UT_OK;

   sTxtLen = (short)strlen(pszTx);
   /* Hvis det skal legges på " eller ' i para-strengens ender: */
   if (cTegn=='\"' || cTegn=='\'') {

      /* Hvis para-strengen allerede er innrammet av anførselstegn :*/
      if ((sTxtLen>1 && pszTx[0]=='\"' && pszTx[sTxtLen]=='\"')
         || (sTxtLen>1 && pszTx[0]=='\'' && pszTx[sTxtLen]=='\'')) {
         if (sTxtLen <= sMaksLen - 1)
         {
            pszTx[0] = pszTx[sTxtLen] = cTegn;
         }
         else
         {
            sOk = UT_ERROR;
         }
      // Hvis tegnet finnes bare i starten av strengen.
      } else if ((sTxtLen > 1 ) && (pszTx[0]=='\'' || pszTx[0]=='\"')){
         if(sTxtLen < sMaksLen - 2)
         {
            pszTx[0] = pszTx[sTxtLen] = cTegn;
            pszTx[sTxtLen + 1] = '\0';
         }
         else
         {
            sOk = UT_ERROR;
         }
      // Hvis tegnet finnes bare i slutten av strengen.
      } else if ((sTxtLen > 1 ) && (pszTx[sTxtLen - 1]=='\'' || pszTx[sTxtLen - 1]=='\"')){
          if(sTxtLen < sMaksLen - 2)
          {
            t1 = pszTx[0];
            t2 = pszTx[1];
            pszTx[0] = cTegn;
            pszTx[1] = t1;

            i = 2;
            while (pszTx[i] != '\0') {
               t1 = pszTx[i];
               pszTx[i] = t2;
               t2 = t1;
               i++;
            }
            pszTx[i] = cTegn;
            pszTx[i+1] = '\0';
         }else{
            sOk = UT_ERROR;
          }
      // Strengen består av bare et anførselstegn.
      } else if ((sTxtLen == 1 ) && (pszTx[sTxtLen - 1]=='\'' || pszTx[sTxtLen - 1]=='\"')){
          if (sTxtLen <= sMaksLen - 2)
          {
             pszTx[0] = pszTx[1] = cTegn;
             pszTx[2] = '\0';
          }
          else
          {
            sOk = UT_ERROR;
          }

      /* Hvis para-strengen ikke er innrammet av ' eller " :*/
      } else {
          if (sTxtLen <= sMaksLen - 3)
          {
             if (pszTx[0] == '\0') {         /* ingen tegn, legger inn "" */
                pszTx[0] = pszTx[1] = cTegn;
                pszTx[2] = '\0';
             } else if (pszTx[1] == '\0') {  /* ett tegn, legger inn "x" */
                pszTx[1] = pszTx[0];
                pszTx[0] = pszTx[2] = cTegn;
                pszTx[3] = '\0';
             } else {                      /* flere tegn, legger inn "xx yy" */
                t1 = pszTx[0];
                t2 = pszTx[1];
                pszTx[0] = cTegn;
                pszTx[1] = t1;

                i = 2;
                while (pszTx[i] != '\0') {
                   t1 = pszTx[i];
                   pszTx[i] = t2;
                   t2 = t1;
                   i++;
                }
                pszTx[i]   = t2;
                pszTx[i+1] = cTegn;
                pszTx[i+2] = '\0';
             }
          }
          else
          {
             sOk = UT_ERROR;
          }
      }

   /* Fjerner appostroffer: */
   } else if (cTegn=='F') {
       if (sTxtLen <= sMaksLen)
       {
          /* Para-strengen må innholde mer enn ett tegn: */
          if (sTxtLen > 1) {

             /* " */
             if ( pszTx[0]=='\"' || pszTx[sTxtLen-1]=='\"') {

                /* Fjerner alle " i hele strengen. */
                i = 0;
                ii = 0;
                do {
                   if (pszTx[i] != '\"') {
                      pszTx[ii] = pszTx[i];
                      ii++;
                   }
                   i++;
                } while (pszTx[i] != '\0');
                pszTx[ii] = '\0';

             /* ' */
             } else if ( pszTx[0]=='\'' || pszTx[sTxtLen-1]=='\'') {

                /* Fjerner alle ' i hele strengen. */
                i = 0;
                ii = 0;
                do {
                   if (pszTx[i] != '\'') {
                      pszTx[ii] = pszTx[i];
                      ii++;
                   }
                   i++;
                } while (pszTx[i] != '\0');
                pszTx[ii] = '\0';
             }
          }
       }
       else
       {
           sOk = UT_ERROR;
       }
   }
   return sOk;
}
