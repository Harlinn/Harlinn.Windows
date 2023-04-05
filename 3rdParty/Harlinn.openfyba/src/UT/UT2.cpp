/******************************************************************^$date;
*                                                                           *
*       Hjelpebiblioteket   U T  (Utilities)                                *
*       Lars Staurset, Statens Kartverk / FYSAK-prosjektet, januar 1990     *
*       Fil: UT2.C versjon C22: Streng- og teikn-operasjonar                *
*                                                                           *
****************************************************************************/

//#include "stdafx.h"

#include	<math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "fyut.h"

#ifdef WIN32
#  include <windows.h>
#  include <memory.h>
#  include <stdlib.h>
#endif

/* Interne prototyper */
static short VT_JustStr (char ztr[], short mstr, char str[]);
static char  VT_StrWord (char str[], short ii, short *iu, char *sep, short mw,
								 char word[]);

/*******************************************************************************
*                                                                              *
*       FRAMHENTING AV TOKEN M.M.                                              *
*                                                                              *
*******************************************************************************/

/*LS-890927*********************************************************************
*       Get Token                                                              *
*******************************************************************************/


SK_EntPnt_UT char *UT_GetToken (char *str, short *tl)
{
	 char *ptr;
                                // Hopp fram til første ikkje-blanke 
	 while (UT_IsSpace(*str)) ++str;
                /* Hopp evt. forbi eitt komma el. punktum og blanke etter det */
    if (*str == ',' || *str == '.') {
        ++str;
        while (UT_IsSpace(*str)) ++str;
    }
                                /* Sjekk om strengen er ferdigbehandla */
    if (*str == '\0') {
      *tl=0;
      return NULL;
    }
                                /* Token avgrensa av hermeteikn */
    if (*str == '"') {
		  ptr = str + 1;
        while (*ptr != '"' && *ptr != '\0' && *ptr != '\n') ptr++;
        *tl = (short)(ptr - str + 1);
        return str;
    }
                                /* Tekststreng fram til skilleteikn */
	 else {
		  ptr = str;
        while (!UT_IsSpace(*ptr)  &&  *ptr != ',' &&  *ptr != '\0')  ptr++;
		  *tl = (short)(ptr - str);
        return str;
    }
}

/*LS-890927****AR-920317********************************************************
*       Get Token From String                                                  *
*******************************************************************************/

SK_EntPnt_UT char UT_StrToken (char str[], short ii, short *iu, short mt, char token[])
{
    char ch;
    register short it;

    
    /* Korrigerer max strenglengde (AR) */
    mt--;

    
    /* Hopp fram til første ikkje-blanke */
    while (UT_IsSpace(str[ii])) ii++;
	
    /* Hopp evt. forbi eitt komma eller semikolon og blanke etter det */
	 if (str[ii] == ','  ||  str[ii] == ';') {
        ii++;
		  while (UT_IsSpace(str[ii])) ii++;
    }
    
    /* Sjekk om strengen er ferdigbehandla */
    if (str[ii] == '\0') {
        token[0] = '\0';
        ch = '\0';

    /* Token avgrensa av doble hermeteikn */
    } else if (str[ii] == '"') {
        for (ii++, it = 0; !strchr ("\"",str[ii]); ii++) {
            if (it < mt) token[it++] = str[ii];
        }
        token[it] = '\0';
		  ch = '"';
        if (str[ii]) ii++;
    
    /* Token avgrensa av enkle hermeteikn */
    } else if (str[ii] == '\'') {
        for (ii++, it = 0; !strchr ("'",str[ii]); ii++) {
            if (it < mt) token[it++] = str[ii];
        }
        token[it] = '\0';
		  ch = '\'';
        if (str[ii]) ii++;
    

    /* Token går fram til ',' , ';' , 'Space' el '\0' */
    } else {
        for (it = 0; (!UT_IsSpace(str[ii]) && str[ii] != ',' && str[ii] != ';' && str[ii] != '\0'); ii++) {
				if (it < mt) token[it++] = str[ii];
		  }
        token[it] = '\0';
										  /* Returkode avh. av slutt-teikn */
        if (str[ii] == '\0' || UT_IsSpace(str[ii]))
            ch = ' ';
        else
            ch = str[ii++];
    }
    *iu = ii;

    return ch;
}

/*LS-880929*****AR-890713*******************************************************
*       Get Word From String                                                   *
*******************************************************************************/

SK_EntPnt_UT char UT_StrWord (char *str, short ii, short *iu, short mw, char *word)
{
    static char separators[] = { '\x20',',','\x9','\xA','\xB','\xC','\xD' };

    return VT_StrWord (str,ii,iu, separators,mw,word);
}

/*LS-881005******AR-890713******************************************************
*       Get Integer From String                                                *
*******************************************************************************/

SK_EntPnt_UT short UT_StrInt (char str[], short ii, short *iu, int *_int)
{
    short ok;
    long l;

    ok = UT_StrLong (str,ii,iu,&l);
    *_int = (int)l;
    return ok;
}

/*LS-881005****AR-890713********************************************************
*       Get Short Integer From String                                          *
*******************************************************************************/

SK_EntPnt_UT short UT_StrShort (char *str, short ii, short *iu, short *s)
{
    static char separators[] = { '\x20',',','\x9','\xA','\xB','\xC','\xD' };
   char tal[7];

	if (VT_StrWord (str,ii,iu, separators,7,tal)) {
		*s = (short)atol(tal);
      return UT_TRUE;
	}

   *s = (short)0;
   return UT_FALSE;
}


/*LS-880929*****AR-890713*******************************************************
*       Get Long Integer From String                                           *
*******************************************************************************/

SK_EntPnt_UT short UT_StrLong (char str[], short ii, short *iu, long *_long)
{
    static char separators[] = { '\x20',',','\x9','\xA','\xB','\xC','\xD' };
   char tal[12];

   if (VT_StrWord (str,ii,iu, separators,12,tal)) {
      *_long = atol(tal);
      return UT_TRUE;
   }
      
	*_long = 0;
	return UT_FALSE;
}


/*LS-880929*****AR:2007-08-09***************************************************
*       Get Integer64 From String                                              *
*******************************************************************************/

SK_EntPnt_UT short UT_StrInt64 (char str[], short ii, short *iu, UT_INT64 *i64)
{
    static char separators[] = { '\x20',',','\x9','\xA','\xB','\xC','\xD' };
   char tal[20];

   if (VT_StrWord (str,ii,iu, separators,20,tal)) {
#ifdef LINUX
      *i64 = atoll(tal);
#else
      *i64 = _atoi64(tal);
#endif
      return UT_TRUE;
   }
      
	*i64 = 0;
	return UT_FALSE;
}


/*LS-880929*****AR-890713*******************************************************
*       Get Unsigned Long Integer From String                                  *
*******************************************************************************/

SK_EntPnt_UT short UT_StrUlong (char str[], short ii, short *iu, unsigned long *_ulong)
{
    static char separators[] = { '\x20',',','\x9','\xA','\xB','\xC','\xD' };
   char tal[12],*endptr;

   if (VT_StrWord (str,ii,iu, separators,12,tal)) {

      *_ulong = strtoul( tal, &endptr, 10 );

		return UT_TRUE;
   }
      
   *_ulong = 0;
   return UT_FALSE;
}

/*LS-890909*********************************************************************
*       Get Double From String                                                 *
*******************************************************************************/

SK_EntPnt_UT short UT_StrDbl (char str[], short ii, short *iu, char decpt,
    double *dbl)
{
    char tal[31], *sep;
    static char sep1[] = " ,\x9\xA\xB\xC\xD", sep2[] = " \x9\xA\xB\xC\xD";

    sep = (decpt == ',') ? sep2 : sep1;
    if (VT_StrWord (str,ii,iu,sep,31,tal)) {
        UT_AtoD (tal,decpt,dbl);
        return UT_TRUE;
    }

    *dbl = 0.0;
    return UT_FALSE;
}

/*LS-890927****AR-890713********************************************************
*       Get Word From String                                                   *
*******************************************************************************/

static char VT_StrWord (char *str, short ii, short *iu, char *sep, short mw,
    char word[])
{
    char ch;
    int iw;


                            /* Korrigerer max strenglengde (AR) */
    mw--;
                            /* Hopp fram til første ikkje-blanke */
    while (UT_IsSpace(str[ii]))  ii++;
                            /* Hopp evt. forbi eitt komma og blanke etter det */
    if (strchr (sep,',')) {
		  if (str[ii] == ',')  ii++;
        while (UT_IsSpace(str[ii]))  ii++;
    }

                            /* Sjekk om strengen er ferdigbehandla */
    if (str[ii] == '\0') {
		  word[0] = '\0';
		  ch = '\0';

									 /* Ordet går fram til separator-teikn */
    } else {
        for (iw = 0; !strchr (sep,str[ii]); ii++) {
            if (iw < mw) word[iw++] = str[ii];
        }
        word[iw] = '\0';
                            /* Returkode avh. av slutt-teikn */
        if (str[ii] == '\0' || UT_IsSpace(str[ii]))
            ch = ' ';
        else
            ch = str[ii++];
    }
    *iu = ii;
	 return ch;
}


/*
AR:2011-08-04
CH UT_memcpy                                      Kopiere buffer
CD ==============================================================
CD For beskrivelse, se dokumentasjonen av memcpy_s.
CD
CD PARAMETERLISTE:
CD Type    Navn             I/U  Merknad
CD -------------------------------------------------------------
CD void   *dest              iu  Buffer det skal kopieres til.
CD size_t  numberOfElements  i   Size of the destination buffer.
CD void   *src               i   Buffer det kopieres fra.
CD size_t  count             i   Number of characters to copy.
CD int     status            r   Zero if successful; an error code on failure.
CD  ==============================================================
*/
SK_EntPnt_UT int UT_memcpy(void *dest,size_t numberOfElements,const void *src,size_t count)
{
#ifdef WIN32
   return memcpy_s(dest,numberOfElements,src,count);
#else
   if (memcpy(dest,src,count)==NULL) return 1;
   return 0;
#endif
}


/*
AR:2011-08-08
CH UT_strerror                          Henter systemfeilmelding
CD ==============================================================
CD For beskrivelse, se dokumentasjonen av strerror_s.
CD
CD PARAMETERLISTE:
CD Type    Navn             I/U  Merknad
CD -------------------------------------------------------------
CD char   *buffer            iu  Buffer to hold error string.
CD size_t  numberOfElements  i   Size of buffer.
CD int     errnum            i   Error number.
CD int     status            r   Zero if successful; an error code on failure.
CD  ==============================================================
*/
SK_EntPnt_UT int UT_strerror(char *buffer,size_t numberOfElements,int errnum)
{
#ifdef WIN32
   return strerror_s(buffer,numberOfElements,errnum);
#else
   UT_StrCopy(buffer,strerror(errnum),numberOfElements);
   return 0;
#endif
}


/*
AR:2011-08-08
CH UT_strtok                                        Henter token
CD ==============================================================
CD Overbygning over strtok i standardbiblioteket.
CD For beskrivelse, se dokumentasjonen av strtok_s.
CD
CD PARAMETERLISTE:
CD Type    Navn             I/U  Merknad
CD -------------------------------------------------------------
CD char       *strToken      iu  String containing token or tokens.
CD const char *strDelimit    i   Set of delimiter characters.
CD char      **context       iu  Used to store position information between calls to UT_strtok
CD char       *token         r   Returns a pointer to the next token found in strToken. 
CD                               They return NULL when no more tokens are found. 
CD
CD  ==============================================================
*/
SK_EntPnt_UT char *UT_strtok(char *strToken,const char *strDelimit,char **context)
{
#ifdef WIN32
   return strtok_s(strToken,strDelimit,context);
#else
   return strtok(strToken,strDelimit);
#endif
}


/*
GL.06.03.89
CH  UT_StrCopy                    Kopiere streng med overflyttest
CD  ==============================================================
CD  Kopierer en streng med max ant tegn. Legger på \0 på slutten.
CD
CD  PARAMETERLISTE:
CD  Navn     Type       I/U  Merknad
CD  -------------------------------------------------------------
CD  dst     *char       u   streng det skal kopieres til.
CD  src     const *char i   streng det skal kopieres fra.
CD  maxlen  int         i   max antall tegn som skal kopieres
CD                          (Inkludert null-terminator.)
CD  ==============================================================
*/
SK_EntPnt_UT void UT_StrCopy (char *dst, const char *src, int maxlen)
{
#ifdef WIN32
   strncpy_s(dst,maxlen,src,_TRUNCATE);
#else
   strncpy(dst,src,maxlen);
#endif
}


/*
T.H.10.08.96
CH  UT_StrCat                               Konkatinerer streng
CD  ==============================================================
CD  Koncatinerer en streng med max ant tegn. Legger på \0 på slutten.
CD
CD  PARAMETERLISTE:
CD  Navn     Type    I/U  Merknad
CD  -------------------------------------------------------------
CD  dst     *char     u   streng det skal kopieres til.
CD  src     *char     i   streng det skal kopieres fra.
CD  maxlen   int      i   Max lengde av dst, inkl. null-terminator.
CD  retur    short    r   1 = OK, 0 = feil.
CD  ==============================================================
*/
SK_EntPnt_UT short UT_StrCat (char *dst,const char *src, const int maxlen)
{
   //return (strcat_s(dst,maxlen,src))?  0 : 1; 
#ifdef WIN32
   int err = strncat_s(dst,maxlen,src,_TRUNCATE);  //Returns 0 if successful, an error code on failure.
   return (err == 0)?  1 : 0; 
#else
   strncat(dst,src,maxlen); 
   return 1;
#endif


/*
#ifndef BORLAND
   short    sStatus = 1;
   short sLen = (short)strlen(dst);

   if (dst) {
      //UT_StrCopy (dst+sLen-1, src, (short)(maxlen-sLen));
      UT_StrCopy (dst+sLen, src, (short)(maxlen-sLen));  // AR:2000-10-26
   }

   return sStatus;

#else

   HANDLE   hStringDest;
   HANDLE   hStringSource;
   LPSTR    Dest;
   LPCSTR   Source;
   short    sStatus = 1;;

   hStringDest    = LocalAlloc(LHND, maxlen + 1);
   hStringSource  = LocalAlloc(LHND, maxlen + 1);

   if ((hStringDest != NULL) && (hStringSource != NULL)) {
	   Dest   = LocalLock(hStringDest);
	   Source = LocalLock(hStringSource);
	   Dest   = dst; // Setter Dest lik adressen til dst
	   Source = src; // Setter Src lik adressen til src

	   if (Dest) {
		   maxlen--;  // Tar hensyn til null-terminator
		   if ((short)lstrlen(Source) <= maxlen) {
			   src+= maxlen;
			   *src = '\0';
         }
         lstrcat(Dest, Source);
      }
	   LocalUnlock(hStringDest);
	   LocalUnlock(hStringSource);

	   if ((LocalFree(hStringDest))!= NULL)
		   sStatus = 0;

	   if ((LocalFree(hStringSource))!= NULL)
		   sStatus = 0;

   }
   
   return sStatus;
   
#endif
*/
}



/* (AR) */
/*GL-880907*LS-880829***********************************************************
*       Get Substring                                                          *
*******************************************************************************/
SK_EntPnt_UT void UT_GetSubstr (char ctx[],short fra,short til,char sub[],short maxlen)
{
	short i;
	short j = 0;
	short txlen = (short)strlen(ctx);


	sub[0] = '\0';

	if (fra >= txlen)  return;  /* Starter etter slutten av strengen ==> retur */

   if (til > txlen) til=txlen;

   if (fra == -1) {
		fra++;
      while (UT_IsSpace(ctx[fra])  &&  fra < txlen) {
         fra++;
      }
   }

   if (til == -1) {
      til=txlen;
      while (UT_IsSpace(ctx[til])  &&  til > 0) {
         til--;
      }
   }

   for (i=fra; i<= til && ctx[i] != '\0' && maxlen>1 ; i++, maxlen--) {
      sub[j++]=ctx[i];
   }

   sub[j]='\0';
}


/* (AR) */
/*LS-880929*********************************************************************
*       Search String for Substring (INDEX)                                    *
*******************************************************************************/

SK_EntPnt_UT short UT_Index (char str[], char substr[])
{                              /* Wortman & Sidebottom, p. 101 */
    short i;
    short j,k;

    for (i = 0; str[i] != '\0'; i++) {
        for (j=i, k=0;  substr[k] != '\0' && substr[k] == str[j];  j++, k++) {
           ;
        }
        if (substr[k] == '\0') return (i);
    }
    return (-1);
}

/*******************************************************************************
*                                                                              *
*       ANDRE STRENG- OG TEIKN-RUTINER                                         *
*                                                                              *
*******************************************************************************/

/*LS-880929**AR-890713**********************************************************
*       Clear After CR/LF                                                      *
*******************************************************************************/

SK_EntPnt_UT char *UT_ClrCrlf (char *str)
{
   char *cp;

   if ((cp = strpbrk(str,"\r\n")) != NULL)   *cp = '\0';
   
   return str;
}

/*AR-900111********************************************************************
*       Clear Trailing Space                                                     *
*******************************************************************************/
SK_EntPnt_UT char *UT_ClrTrailsp(char *str)
{
   char *cp;

   if (*str != '\0')
   {
      // Fjern blanke på slutten
      cp = strchr(str,'\0');
      --cp;
      while ( cp >= str && UT_IsSpace(*cp) )
      {
         --cp;
      }
      *(cp+1) = '\0';
   }

   return str;
}


/*AR-900111********************************************************************
*    Clear leading and trailing Space, and compress multiple space to one.    *
*******************************************************************************/
SK_EntPnt_UT char *UT_ClrExtrasp(char *str)
{
   char *cp,*tp;
   short sSp = UT_TRUE;

   /* Fjern blanke på slutten */
   UT_ClrTrailsp(str);

   /* Fjern ledende blanke og overflødige blanke inni strengen */
   cp = tp = str;

   while (*cp != '\0') {
      if (! UT_IsSpace(*cp)) {
         *tp++ = *cp;
         sSp = UT_FALSE;
      } else {
         if (sSp == UT_FALSE)  *tp++ = ' ';
         sSp = UT_TRUE;
      }
      cp++;
   }
   *tp = '\0';

   return str;
}


/*
AR-890312
CH UT_IsSpace                                           Test om mellomromstegn
CD =============================================================================
CD Formål:
CD Sjekker om et tegn er mellomromstegn (ascii 0x09-0x0d eller 0x20)
CD
CD Parametre:
CD Type   Navn   I/U   Forklaring
CD -----------------------------------------------------------------------------
CD char   c       i    Tegn som skall testes.
CD int    ist     r    1=mellomromstegn, 0=ikke mellomromstegn.
CD
CD Bruk:
CD ist = UT_IsSpace(*cp);
   =============================================================================
*/
SK_EntPnt_UT int UT_IsSpace(char c)
{
#ifdef WIN32
   static unsigned char atab[256] =
   { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

   return atab[(unsigned char)c];

#else
   switch (c){
      case 0x20:
      case 0x09:
      case 0x0A:
      case 0x0B:
      case 0x0C:
      case 0x0D:
         return 1;
			break;
      default:
         return 0;
			break;
   }
#endif
}

/*LS-890430*********************************************************************
*       Check for Printable Character                                          *
*******************************************************************************/

SK_EntPnt_UT int UT_IsPrint (int ch)
{
    if (isprint (ch))              return UT_TRUE;
    else if (ch == 0)              return UT_FALSE;
    else if (strchr ("ÆØÅæøå",ch)) return UT_TRUE;
    else                           return UT_FALSE;
}

/*LS-890517*********************************************************************
*       Check for Lower-Case Character                                         *
*******************************************************************************/

SK_EntPnt_UT int UT_IsLower (int ch)
{
    if (islower (ch))           return UT_TRUE;
    else if (ch == 0)           return UT_FALSE;
    else if (strchr ("æøåáäèïñö",ch)) return UT_TRUE;
    else                        return UT_FALSE;
}

/*LS-890913*********************************************************************
*       Convert Character to Lower-Case                                        *
*******************************************************************************/

SK_EntPnt_UT int UT_ToLower (int ch)
{
    if (ch >= 'A'  &&  ch <= 'Z') {
       ch += 0x20;

    } else {
        switch (ch) {
            case 'Æ' : ch = 'æ'; break;
            case 'Ø' : ch = 'ø'; break;
            case 'Å' : ch = 'å'; break;

            case 'Á' : ch = 'á'; break; // á - SK-fonter + standardfonter
            case 'Ä' : ch = 'ä'; break; // ä - SK-fonter + standardfonter
            case 'È' : ch = 'è'; break; // Samisk c - SK-fonter og è - standardfonter
            case 'Ï' : ch = 'ï'; break; // ï - SK-fonter + standardfonter
            case 'Ñ' : ch = 'ñ'; break; // Samisk n(aksent) - SK-fonter og ñ - standardfonter
            case 'Ö' : ch = 'ö'; break; // ö - SK-fonter + standardfonter

            case 0x010C : ch = 0x010D; break; // Samisk c - utvidede standardfonter
            case 0x0110 : ch = 0x0111; break; // Samisk d - utvidede standardfonter
            case 0x014A : ch = 0x014B; break; // Samisk n(lav) - utvidede standardfonter
            case 0x0143 : ch = 0x0144; break; // Samisk n(aksent) - utvidede standardfonter
            case 0x0160 : ch = 0x0161; break; // Samisk s - utvidede standardfonter
            case 0x0166 : ch = 0x0167; break; // Samisk t - utvidede standardfonter
            case 0x017D : ch = 0x017E; break; // Samisk z - utvidede standardfonter
        }
    } /* endif */

    return ch;
}

/*AR-881020*LS-890517***********************************************************
*       Convert String to Lower-Case                                           *
*******************************************************************************/

SK_EntPnt_UT char *UT_StrLower (char *ti)
{
   char *t = ti;

   while ((*t = (char)UT_ToLower(*t)) != '\0')
       t++;
   return (ti);
}

/*LS-890517*********************************************************************
*       Check for Upper-Case Character                                         *
*******************************************************************************/

SK_EntPnt_UT int UT_IsUpper (int ch)
{
    if (isupper (ch))           return UT_TRUE;
    else if (ch == 0)           return UT_FALSE;
    else if (strchr ("ÆØÅÁÄÈÏÑÖ",ch)) return UT_TRUE;
    else                        return UT_FALSE;
}

/*LS-890913*********************************************************************
*       Convert Character to Upper-Case                                        *
*******************************************************************************/

SK_EntPnt_UT int UT_ToUpper (int ch)
{
    if (ch >= 'a'  &&  ch <= 'z') {
       ch -= 0x20;

    } else {
        switch (ch) {
            case 'æ' : ch = 'Æ'; break;
            case 'ø' : ch = 'Ø'; break;
            case 'å' : ch = 'Å'; break;
         
            case 'á' : ch = 'Á'; break; // á - SK-fonter + standardfonter
            case 'ä' : ch = 'Ä'; break; // ä - SK-fonter + standardfonter
            case 'è' : ch = 'È'; break; // Samisk c - SK-fonter og è - standardfonter
            case 'ï' : ch = 'Ï'; break; // ï - SK-fonter + standardfonter
            case 'ñ' : ch = 'Ñ'; break; // Samisk n(aksent) - SK-fonter og ñ - standardfonter
            case 'ö' : ch = 'Ö'; break; // ö - SK-fonter + standardfonter

            case 0x010D : ch = 0x010C; break; // Samisk c - utvidede standardfonter
            case 0x0111 : ch = 0x0110; break; // Samisk d - utvidede standardfonter
            case 0x014B : ch = 0x014A; break; // Samisk n(lav) - utvidede standardfonter
            case 0x0144 : ch = 0x0143; break; // Samisk n(aksent) - utvidede standardfonter
            case 0x0161 : ch = 0x0160; break; // Samisk s - utvidede standardfonter
            case 0x0167 : ch = 0x0166; break; // Samisk t - utvidede standardfonter
            case 0x017E : ch = 0x017D; break; // Samisk z - utvidede standardfonter
        }
    }

    return ch;
}

/*LS-890517*********************************************************************
*       Convert String to Upper-Case                                           *
*******************************************************************************/

SK_EntPnt_UT char *UT_StrUpper (char *ti)
{
   char *t = ti;

   while ((*t = (char)UT_ToUpper(*t)) != '\0')
       t++;
   return (ti);
}

/*******************************************************************************
*                                                                              *
*       KONVERTERINGSRUTINER                                                   *
*                                                                              *
*******************************************************************************/

#ifdef OS216

/*LS-880928*********************************************************************
*       Convert String to Integer If Possible                                  *
*******************************************************************************/

SK_EntPnt_UT int UT_AtoI (char *str, int *_int)
{
    short s,ok;

    ok = UT_AtoS (str,&s);
    *_int = (int)s;
    return ok;
}

/*LS-880929*********************************************************************
*       Convert String to Short Integer If Possible                            *
*******************************************************************************/

SK_EntPnt_UT short UT_AtoS (char str[], short *s)
{
    short ok,slen;
    short len,sif;

    ok = UT_FALSE;
                                    /* Finn første siffer != 0 */
    /*; for (sif=0; str[sif]<'1' || str[sif]>'9'; sif++); */ 
    /* Rettet AR-940623 for å handtere streng uten siffer 1-9 */
    for (sif=0; (str[sif]<'1' || str[sif]>'9') && str[sif]!='\0' ; sif++);
                                    /* Lengde på sifferstrengen */
    slen = (short)strlen(str);
    len = slen - sif;
                                    /* Viss <5 siffer: ok */
    if (len < 5) ok = UT_TRUE;
                                    /* Viss 5 siffer: u.s. dei 4 første */
    else if (len == 5) {
        sif = (short)str[--slen];
        str[slen] = '\0';
        *s = (short)abs(atoi(str));
        if (*s < 3276) ok = UT_TRUE;
                                    /* På grensa for lovleg verdi, sjekk det 5. */
        else if (*s == 3276) {
            if (sif <= '7') ok = UT_TRUE;
            else if (sif == '8') {
                                    /* Neg. tal kan ha 1 større abs.verdi */
                if (atoi(str) < 0) ok = UT_TRUE;
            }
        }
                                    /* Sett tilbake det lånte sifferet */
        str[slen++] = (char)sif;
    }
    if (ok) *s = (short)atoi(str);
    else *s = 0;
    return ok;
}

/*LS-880929*********************************************************************
*       Convert String to Long Integer If Possible                             *
*******************************************************************************/

SK_EntPnt_UT short UT_AtoL (char str[], long *_long)
{
    short ok,slen;
    register short len,sif;

    ok = UT_FALSE;
                                    /* Finn første siffer != 0 */
    /*; for (sif=0; str[sif]<'1' || str[sif]>'9'; sif++); */ 
    /* Rettet AR-940623 for å handtere streng uten siffer 1-9 */
    for (sif=0; (str[sif]<'1' || str[sif]>'9') && str[sif]!='\0' ; sif++);

                                    /* Lengde på sifferstrengen */
    slen = (short)strlen(str);
    len = slen - sif;
                                    /* Viss <10 siffer: ok */
    if (len < 10) ok = UT_TRUE;
                                    /* Viss 10 siffer: u.s. dei 9 første */
    else if (len == 10) {
        sif = (short)str[--slen];
        str[slen] = '\0';
        *_long = labs (atol (str));
        if (*_long < 214748364) ok = UT_TRUE;
                                    /* På grensa for lovleg verdi, sjekk det 10. */
        else if (*_long == 214748364) {
            if (sif <= '7') ok = UT_TRUE;
            else if (sif == '8') {
                                    /* Neg. tal kan ha 1 større abs.verdi */
                if (atol(str) < 0) ok = UT_TRUE;
            }
        }
                                    /* Sett tilbake det lånte sifferet */
        str[slen++] = (char)sif;
    }
    if (ok) *_long = atol (str);
    else *_long = 0L;
    return ok;
}

#endif


/*LS-890519*********************************************************************
*       Convert String to Double                                               *
*******************************************************************************/

SK_EntPnt_UT short UT_AtoD (char *str, char decpt, double *dbl)
{
    char *kompos;
                                    /* Pass på desimalkomma */
    if (decpt == ',') {
        kompos = strchr (str,',');
        if (kompos) *kompos = '.';
    }
    else
        kompos = NULL;
    *dbl = atof (str);
    if (kompos) *kompos = ',';
    return UT_TRUE;
}

/*LS-889297*********************************************************************
*       Convert Integer to String                                              *
*******************************************************************************/

SK_EntPnt_UT short UT_ItoA (int _int, short mstr, char *str)
{
   char ztr[12];
   
   UT_SNPRINTF(ztr,12,"%d",_int);
   return VT_JustStr (ztr,mstr,str);
}

/*LS-880928*********************************************************************
*       Convert Short Integer to String                                        *
*******************************************************************************/

SK_EntPnt_UT short UT_StoA (short s, short mstr, char *str)
{
   char ztr[7];

   UT_SNPRINTF(ztr,7,"%hd",s);
   return VT_JustStr (ztr,mstr,str);
}

/*LS-880929*********************************************************************
*       Convert Long Integer to String                                         *
*******************************************************************************/

SK_EntPnt_UT short UT_LtoA (long _long, short mstr, char *str)
{
   char ztr[12];

   UT_SNPRINTF(ztr,12,"%ld",_long);
   return VT_JustStr (ztr,mstr,str);
}

/*LS-890912*********************************************************************
*       Convert Double To String                                               *
*******************************************************************************/

SK_EntPnt_UT short UT_DtoA (double dbl, short dec, char decpt, short mstr, char *str)
{  
   /* size_t len; */
   char *cp,ztr[41];
   
   /* Sjekk mot for lang streng  */ 
   if (dbl!=0.0   &&  (log10(fabs(dbl)) + dec  > 36.0)) {
      memset( ztr, '*', 40);
      ztr[40] = '\0';

   } else {

      /* Konverter til streng */
      UT_SNPRINTF(ztr,41,"%.*f",dec,dbl);

      /* Skift til rett desimaltegn */
      if ((cp = strchr(ztr,'.')) != NULL) {
         *cp = decpt;
      }

      /* Kontroller strenglengda */
      /*if ((len = strlen (ztr)) > 40) {                  */
      /*   UT_FPRINTF (stderr,"\nFeil i UT_DtoA: %d",len);   */
      /*   exit (1);                                      */
      /*}                                                 */
   }

   /* Juster etter behov */
   return VT_JustStr(ztr,mstr,str);
}

/*LS-890912*********************************************************************
*       Check and Justify String                                               *
*******************************************************************************/

static short VT_JustStr (char ztr[], short mstr, char str[])
{
    short ok,i,lstr;

    lstr = (short)strlen (ztr);
    mstr--;
                                        /* For kort streng? */
    if (mstr > 0 && mstr < lstr) {
        for (i=0; i<mstr; i++) str[i] = ztr[i+lstr-mstr];
        str[mstr] = '\0';
        ok = UT_FALSE;
    }
                                        /* Lang nok streng */
    else {
        //strcpy_s (str,mstr,ztr);
#ifdef LINUX
        strncpy (str,ztr,mstr+1);
#else
        strcpy_s (str,mstr+1,ztr); // Må bruke mstr+1 fordi det er trukket fra en i den verdien som kommer inn
#endif
        ok = UT_TRUE;
    }
                                        /* For lang streng? */
    if (mstr > lstr) UT_JustStr ('>',' ',(short)(mstr+1),str);
                                        /* Avslutt */
    return ok;
}

/*LS-891011*********************************************************************
*       Justify and Fill String                                                *
*******************************************************************************/

SK_EntPnt_UT void UT_JustStr (char justmode, char fill, short lstr, char *str)
{
   char *pc1, *pc2, *pc, *qc;

   if (lstr > 0) {
                                           /* Terminer strengen */
      lstr--;
      *(str+lstr) = '\0';
                                           /* Finn endane av strengen */
      pc1 = str;
      while (UT_IsSpace(*pc1) || *pc1 == fill) {
         pc1++;
      }

      pc2 = strchr(pc1,'\0')-1;
      while (UT_IsSpace(*pc2) || *pc2 == fill) {
         pc2--;
      }

      switch (justmode) {
         case '>' :                      /* Høgrepakking */
            for (pc = pc2, qc = str+lstr-1; pc >= pc1; pc--) {
               if (!UT_IsSpace(*pc) && *pc != fill) {
                  *qc-- = *pc;
               }
            }
            while (qc >= str) *qc-- = fill;
            break;
         case '/' :                      /* Høgrejustering */
            for (pc = pc2, qc = str+lstr-1; pc >= pc1; pc--)
               *qc-- = *pc;
            while (qc >= str) *qc-- = fill;
            break;
         case '<' :                      /* Venstrepakking */
            for (pc = pc1, qc = str; pc <= pc2; pc++) {
               if (!UT_IsSpace(*pc) && *pc != fill) *qc++ = *pc;
            }
            while (qc < str+lstr) *qc++ = fill;
            break;
         case '`' :                      /* Venstrejustering */
            for (pc = pc1, qc = str; pc <= pc2; pc++)
               *qc++ = *pc;
            while (qc < str+lstr) *qc++ = fill;
            break;
      }
   }
}


/*
AR-890113 LS-890915
CH UT_Ascii7to8                                          Konverter til PC-ASCII
CD =============================================================================
CD Formål:
CD Konverterer en streng fra ND-7-bits norsk ASCII til PC-8-bits norsk ASCII.
CD
CD Parametre:
CD  Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  char   *tx        i    Peker til streng som skal konverteres
CD                         (avsluttet med '\0').
CD  char   *tp        r    Peker til konvertert streng.
CD
CD Bruk:
CD tp = UT_Ascii7to8(tx);
   =============================================================================
*/
SK_EntPnt_UT unsigned char *UT_Ascii7to8(unsigned char *tx)
{
   static unsigned char atab[256] =
   {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
      40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
      80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,146,157,143, 94, 95, 96, 97, 98, 99,
     100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
     120,121,122,145,155,134,126,127,128,129,130,131,132,133,134,135,136,137,138,139,
     140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
     180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,
     200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,
     220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
     240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};

   unsigned char *tp = tx;

   for ( ; ((*tp = atab[*tp]) != '\0'); tp++){
       ;
   }

   return (tx);
}


/*
AR-890113 LS-890915
CH UT_Ascii8to7                                          Konverter til ND-ASCII
CD =============================================================================
CD Formål:
CD Konverterer en streng fra PC-8-bits norsk ASCII til ND-7-bits norsk ASCII.
CD
CD Parametre:
CD  Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  char   *tx        i    Peker til streng som skal konverteres
CD                         (avsluttet med '\0').
CD  char   *tp        r    Peker til konvertert streng.
CD
CD Bruk:
CD tp = UT_Ascii8to7(tx)
   =============================================================================
*/
SK_EntPnt_UT unsigned char *UT_Ascii8to7(unsigned char *tx)
{
   static unsigned char atab[256] =
   {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
      40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
      80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
     100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
     120,121,122,123,124,125,126,127,128,129,130,131,132,133,125,135,136,137,138,139,
     140,141,142, 93,144,123, 91,147,148,149,150,151,152,153,154,124,156, 92,158,159,
     160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
     180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,
     200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,
     220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
     240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};

   unsigned char *tp = tx;

   for ( ; (*tp = atab[*tp]) != '\0'; tp++){
       ;
   }

   return (tx);
}


/*
AR-920929
CH UT_Ascii8toISO8859                                 Konverter til ISO8859-10
CD =============================================================================
CD Formål:
CD Konverterer en streng fra PC-8-bits norsk ASCII til ISO8859-10.
CD
CD Parametre:
CD  Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  char   *tx        i    Peker til streng som skal konverteres
CD                         (avsluttet med '\0').
CD  char   *tp        r    Peker til konvertert streng.
CD
CD Bruk:
CD tp = UT_Ascii8toISO8859(tx)
   =============================================================================
*/
SK_EntPnt_UT unsigned char *UT_Ascii8toISO8859(unsigned char *tx)
{
   static unsigned char atab[256] =
   {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
      40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
      80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
     100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
     120,121,122,123,124,125,126,127,128,129,130,131,132,133,229,135,136,137,138,139,
     140,141,142,197,144,230,198,147,148,149,150,151,152,153,154,248,156,216,158,159,
     160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
     180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,
     200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,
     220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
     240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};



   unsigned char *tp = tx;

   for ( ; (*tp = atab[*tp]) != '\0'; tp++){
       ;
   }

   return (tx);
}


/*
AR-920929
CH UT_ISO8859toAscii8                                    Konverter til PC-ASCII
CD =============================================================================
CD Formål:
CD Konverterer en streng fra ISO8859-10 til PC-8-bits norsk ASCII.
CD
CD Parametre:
CD  Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  char   *tx        i    Peker til streng som skal konverteres
CD                         (avsluttet med '\0').
CD  char   *tp        r    Peker til konvertert streng.
CD
CD Bruk:
CD tp = UT_ISO8859toAscii8(tx);
   =============================================================================
*/
SK_EntPnt_UT unsigned char *UT_ISO8859toAscii8(unsigned char *tx)
{
   static unsigned char atab[256] =
   {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
      40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
      80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
     100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
     120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,
     140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
     180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,143,146,199,
     200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,157,217,218,219,
     220,221,222,223,224,225,226,227,228,134,145,231,232,233,234,235,236,237,238,239,
     240,241,242,243,244,245,246,247,155,249,250,251,252,253,254,255};



   unsigned char *tp = tx;

   for ( ; ((*tp = atab[*tp]) != '\0'); tp++){
       ;
   }

   return (tx);
}


/*
AR-920929
CH UT_Ascii7toISO8859                                 Konverter til ISO8859-10
CD =============================================================================
CD Formål:
CD Konverterer en streng fra norsk 7-bits ASCII til ISO8859-10.
CD
CD Parametre:
CD  Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  char   *tx        i    Peker til streng som skal konverteres
CD                         (avsluttet med '\0').
CD  char   *tp        r    Peker til konvertert streng.
CD
CD Bruk:
CD tp = UT_Ascii7toISO8859(tx)
   =============================================================================
*/
SK_EntPnt_UT unsigned char *UT_Ascii7toISO8859(unsigned char *tx)
{

   static unsigned char atab[256] =
   {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
      40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
      80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,198,216,197, 94, 95, 96, 97, 98, 99,
     100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
     120,121,122,230,248,229,126,127,128,129,130,131,132,133,134,135,136,137,138,139,
     140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
     180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,
     200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,
     220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
     240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};

   unsigned char *tp = tx;

   for ( ; (*tp = atab[*tp]) != '\0'; tp++){
       ;
   }

   return (tx);
}


/*
AR-920929
CH UT_ISO8859toAscii7                                    Konverter til ND-ASCII
CD =============================================================================
CD Formål:
CD Konverterer en streng fra ISO8859-10 til norsk 7-bits ASCII.
CD
CD Parametre:
CD  Type    Navn     I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  char   *tx        i    Peker til streng som skal konverteres
CD                         (avsluttet med '\0').
CD  char   *tp        r    Peker til konvertert streng.
CD
CD Bruk:
CD tp = UT_ISO8859toAscii7(tx);
   =============================================================================
*/
SK_EntPnt_UT unsigned char *UT_ISO8859toAscii7(unsigned char *tx)
{

   static unsigned char atab[256] =
   {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
      40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
      80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
     100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
     120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,
     140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
     160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
     180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196, 93, 91,199,
     200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215, 92,217,218,219,
     220,221,222,223,224,225,226,227,228,125,123,231,232,233,234,235,236,237,238,239,
     240,241,242,243,244,245,246,247,124,249,250,251,252,253,254,255};


   unsigned char *tp = tx;

   for ( ; ((*tp = atab[*tp]) != '\0'); tp++){
       ;
   }

   return (tx);
}


/*
AR-890113
CH UT_KonverterTegnsett                                   Konverter tegnsett
CD ==========================================================================
CD Formål:
CD Konverterer en streng fra et tegnsett til et annet.
CD
CD Parametre:
CD  Type    Navn         I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  short   sFraTegnsett  i    Fra tegnsett
CD                                TS_UKJENT  = Ukjent tegnsett
CD                                TS_DOSN8   = DOS norsk 8-bits
CD                                TS_ND7     = Norsk Data 7-bits
CD                                TS_DECM8   = DEC multinasjonal 8-bits
CD                                TS_DECN7   = DEC norsk 7-bits
CD                                TS_ISO8859 = ISO8859-10
CD  short   sTilTegnsett  i    Til tegnsett 
CD                                TS_UKJENT  = Ukjent tegnsett
CD                                TS_DOSN8   = DOS norsk 8-bits
CD                                TS_ND7     = Norsk Data 7-bits
CD                                TS_DECM8   = DEC multinasjonal 8-bits
CD                                TS_DECN7   = DEC norsk 7-bits
CD                                TS_ISO8859 = ISO8859-10
CD  char   *pszTx         iu   Peker til streng som skal konverteres
CD                             (avsluttet med '\0').
CD  char   *pszTx         r    Peker til konvertert streng.
CD
CD Bruk:
CD pszTx = UT_KonverterTegnsett(sFraTegnsett,sTilTegnsett,pszTx);
   =============================================================================
*/
SK_EntPnt_UT unsigned char *UT_KonverterTegnsett(short sFraTegnsett,short sTilTegnsett,
                                    unsigned char *pszTx)
{
   if (sFraTegnsett != sTilTegnsett) {
      switch (sFraTegnsett) {
         /* Fra DOS 8-bits */
         case TS_DOSN8:
            switch (sTilTegnsett) {
               /* Til norsk 7-bits */
               case TS_ND7:
               case TS_DECN7:
                  return  UT_Ascii8to7(pszTx);

               /* Til ISO8859 */
               case TS_ISO8859:
               case TS_DECM8:
                  return  UT_Ascii8toISO8859(pszTx);
            }
            break;

         /* Fra norsk 7-bits */
         case TS_ND7:
         case TS_DECN7:
            switch (sTilTegnsett) {
               /* Til DOS 8-bits */
               case TS_DOSN8:
                  return  UT_Ascii7to8(pszTx);

               /* Til ISO8859 */
               case TS_ISO8859:
               case TS_DECM8:
                  return  UT_Ascii7toISO8859(pszTx);
            }
            break;

         /* Fra Dec-multinasjonal 8-bits */
         case TS_ISO8859:
         case TS_DECM8:
            switch (sTilTegnsett) {
               /* Til DOS 8-bits */
               case TS_DOSN8:
                  return  UT_ISO8859toAscii8(pszTx);
               
               /* Til norsk 7-bits */
               case TS_ND7:
               case TS_DECN7:
                  return  UT_ISO8859toAscii7(pszTx);
            }
            break;
      }
   }

   return  pszTx;
}



/*
AR:2003-10-13
CH UT_StrCmpi                                            Sammenlign strenger
CD ==========================================================================
CD Formål:
CD Sammenligner to strenger uavhengig av store og små bokstaver.
CD For sammenligning der det bare sjekkes på likhet fungerer den for norske bokstaver.
CD (Sammenligner bare karakterverdier.)
CD For sortering må UT_StrColli brukes for å handtere norske bokstaver rett. 
CD UT_StrCmpi er mye raskere enn UT_StrColli.
CD
CD Parametre:
CD  Type    Navn         I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  char   *pszTx1        i    Peker til første streng (avsluttet med '\0').
CD  char   *pszTx2        i    Peker til andre streng (avsluttet med '\0').
CD  int     iStatus       r    Status, samme som strcmpi
CD
CD Bruk:
CD iStatus = UT_StrCmpi(szTx1,szTx2);
   =============================================================================
*/
SK_EntPnt_UT int UT_StrCmpi(const char *pszTx1, const char *pszTx2)
{
   char *ps1,*ps2;
   int iStatus;


   ps1 = (char*)malloc(strlen(pszTx1)+1);
#ifdef LINUX
   strncpy(ps1, pszTx1, strlen(pszTx1)+1);
#else
   strcpy_s(ps1, strlen(pszTx1)+1, pszTx1);
#endif
   UT_StrUpper(ps1);

   ps2 = (char*)malloc(strlen(pszTx2)+1);
#ifdef LINUX
   strncpy(ps2, pszTx2, strlen(pszTx2)+1);
#else
   strcpy_s(ps2, strlen(pszTx2)+1, pszTx2);
#endif
   UT_StrUpper(ps2);

   iStatus = strcmp(ps1,ps2);

   free(ps1);
   free(ps2);

   return iStatus;
}

/*
PG:2010-10-21
CH UT_StrColli                                            Sammenlign strenger
CD ==========================================================================
CD Formål:
CD Sammenligner to strenger uavhengig av store og små bokstaver.
CD Fungerer for norske bokstaver. Justerer for landskode (LC_COLLATE)
CD Hvis det er bare er likhet det sjekkes på, bør heller den raskere UT_StrCmpi brukes.
CD
CD Parametre:
CD  Type    Navn         I/U   Forklaring
CD -----------------------------------------------------------------------------
CD  char   *pszTx1        i    Peker til første streng (avsluttet med '\0').
CD  char   *pszTx2        i    Peker til andre streng (avsluttet med '\0').
CD  int     iStatus       r    Status, samme som strcmpi
CD
CD Bruk:
CD iStatus = UT_StrColli(szTx1,szTx2);
   =============================================================================
*/
SK_EntPnt_UT int UT_StrColli(const char *pszTx1, const char *pszTx2)
{
   char *ps1,*ps2;
   int iStatus;

   ps1 = (char*)malloc(strlen(pszTx1)+1);
#ifdef LINUX
   strncpy(ps1, pszTx1, strlen(pszTx1)+1);
#else
   strcpy_s(ps1, strlen(pszTx1)+1, pszTx1);
#endif
   UT_StrUpper(ps1);

   ps2 = (char*)malloc(strlen(pszTx2)+1);
#ifdef LINUX
   strncpy (ps2, pszTx2, strlen(pszTx2)+1);
#else
   strcpy_s(ps2, strlen(pszTx2)+1, pszTx2);
#endif
   UT_StrUpper(ps2);

   iStatus = strcoll(ps1,ps2);

   free(ps1);
   free(ps2);

   return iStatus;
}
