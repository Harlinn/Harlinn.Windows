 /******************************************************************^$date;
*                                                                           *
*       Hjelpebiblioteket   U T  (Utilities)                                *
*       Lars Staurset, Statens Kartverk / FYSAK-prosjektet, januar 1990     *
*       Fil: UT3.C versjon C22: Diverse rutiner                             *
*                                                                           *
****************************************************************************/

//#include "stdafx.h"

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef OS2
  #define INCL_DOSMEMMGR
  #include <os2.h>
#endif


#include "fyut.h"

#ifdef WIN32
#	include <windows.h>
#endif


/*******************************************************************************
*                                                                              *
*       RUTINER FOR Å STYRE MASKINUTSTYR                                       *
*                                                                              *
*******************************************************************************/

/*LS-880928*********************************************************************
*       Sound Bell                                                             *
*******************************************************************************/
SK_EntPnt_UT void UT_Bell (void)
{
   UT_Sound(900,40);
}


/*AR-900110*********************************************************************
*       Sound Speaker for OS/2                                                 *
*******************************************************************************/
SK_EntPnt_UT void UT_Sound (short freq, short dur)
{
#ifdef OS232
   DosBeep((ULONG)freq,((ULONG)dur)*10);
#endif

#ifdef OS216
   DosBeep((USHORT)freq,((USHORT)dur)*10);
#endif

#ifdef WIN32
	Beep((DWORD)freq,((DWORD)dur)*10);
#endif
}

/*LS-890706*********************************************************************
*       Pause                                                                  *
*******************************************************************************/
SK_EntPnt_UT void UT_Pause (short dur)
{
#ifdef OS216
   short t1,t2,t,tid[4];

   UT_InqTime (tid);
   t1 = 100*tid[2] + tid[3];
   t2 = t1 + min (dur,6000);
   do {
      UT_InqTime (tid);
      t = 100*tid[2] + tid[3];
      if (t < t1) t += 6000;
   } while (t < t2);
#else
#ifdef OS2
   DosSleep(((ULONG)dur)*10);
#endif
#endif

#ifdef WIN32
	Sleep(((DWORD)dur)*10);
#endif
}

/*******************************************************************************
*                                                                              *
*       MATEMATISKE FUNKSJONAR                                                 *
*                                                                              *
*******************************************************************************/

/*AR*LS-890611******************************************************************
*       Round Double to Double                                                 *
*******************************************************************************/

SK_EntPnt_UT double UT_RoundDD (double d)
{
   double dint;

   modf((d + ((d < 0.0) ? -0.5 : 0.5)  ), &dint) ;

   return dint;
}

/*AR*TOU*IR:2010-01-25**********************************************************
*       Round Double to Double                                                 *
*       Spesiell avrunding som runder av halve verdier oppover                 *
*       Eks:  -1.1  ->  -1.0                                                   *
*             -1.5  ->  -1.0                                                   *
*              1.1  ->   1.0                                                   *
*              1.5  ->   2.0                                                   *
*******************************************************************************/

SK_EntPnt_UT double UT_RoundHalfUpDD (double d)
{
   return floor(d + 0.5);
}


/*LS-890915*********************************************************************
*       Round Double to Integer                                                *
*******************************************************************************/

SK_EntPnt_UT int UT_RoundDI (double d)
{
   if (d > INT_MAX  ||  d < INT_MIN)
   {
      UT_FPRINTF(stderr,"Kan ikke avrunde %.3f til int!(Fil:%s, Linje:%d)\n", d, __FILE__, __LINE__);
#ifndef LINUX
      RaiseException( EXCEPTION_INT_OVERFLOW, EXCEPTION_NONCONTINUABLE, 0, NULL);
#endif
      return  (d > INT_MAX)?  INT_MAX : INT_MIN;
   }

   //(d > 0.0)?  (d+=0.5) : (d-=0.5);
   //return (int)d;
   return (int)( d + ( (d < 0.0)? -0.5 : 0.5) );
}


/*LS-890915*********************************************************************
*       Round Double to Unsigned Integer                                                *
*******************************************************************************/

SK_EntPnt_UT unsigned int UT_RoundDUI (double d)
{
   if (d > UINT_MAX  ||  d < 0)
   {
      UT_FPRINTF(stderr,"Kan ikke avrunde %.3f til unsigned int!(Fil:%s, Linje:%d)\n", d, __FILE__, __LINE__);
#ifndef LINUX
      RaiseException( EXCEPTION_INT_OVERFLOW, EXCEPTION_NONCONTINUABLE, 0, NULL);
#endif
      return  (d > UINT_MAX)?  UINT_MAX : 0;
   }

   return (unsigned int)( d + 0.5 );
}


/*LS-890915*********************************************************************
*       Round Double to Long Integer                                           *
*******************************************************************************/

SK_EntPnt_UT long UT_RoundDL (double d)
{
   if (d > LONG_MAX  ||  d < LONG_MIN)
   {
      UT_FPRINTF(stderr,"Kan ikke avrunde %.3f til long!(Fil:%s, Linje:%d)\n", d, __FILE__, __LINE__);
#ifndef LINUX
      RaiseException( EXCEPTION_INT_OVERFLOW, EXCEPTION_NONCONTINUABLE, 0, NULL);
#endif
      return  (d > LONG_MAX)?  LONG_MAX : LONG_MIN;
   }

   //(d > 0.0)?  (d+=0.5) : (d-=0.5);
   //return (long)d;
   return (long)( d + ( (d < 0.0)? -0.5 : 0.5) );
}

/*PG-071219*********************************************************************
*       Round Double to Long Long Integer                                      *
*******************************************************************************/

SK_EntPnt_UT long long UT_RoundDLL (double d)
{
   if (d > LLONG_MAX  ||  d < LLONG_MIN)
   {
      UT_FPRINTF(stderr,"Kan ikke avrunde %.3f til long long!(Fil:%s, Linje:%d)\n", d, __FILE__, __LINE__);
#ifndef LINUX
      RaiseException( EXCEPTION_INT_OVERFLOW, EXCEPTION_NONCONTINUABLE, 0, NULL);
#endif
      return  (d > LLONG_MAX)?  LLONG_MAX : LLONG_MIN;
   }

   //(d > 0.0)?  (d+=0.5) : (d-=0.5);
   //return (long)d;
   return (long long)( d + ( (d < 0.0)? -0.5 : 0.5) );
}

/*LS-890915*********************************************************************
*       Round Double to Short Integer                                          *
*******************************************************************************/

SK_EntPnt_UT short UT_RoundDS (double d)
{
   if (d > SHRT_MAX  ||  d < SHRT_MIN)
   {
      UT_FPRINTF(stderr,"Kan ikke avrunde %.3f til short!(Fil:%s, Linje:%d)\n", d, __FILE__, __LINE__);
#ifndef LINUX
      RaiseException( EXCEPTION_INT_OVERFLOW, EXCEPTION_NONCONTINUABLE, 0, NULL);
#endif
      return  (d > SHRT_MAX)?  SHRT_MAX : SHRT_MIN;
   }

   //(d > 0.0)?  (d+=0.5) : (d-=0.5);
   //return (short)d;
   return (short)( d + ( (d < 0.0)? -0.5 : 0.5) );
}

/*******************************************************************************
*                                                                              *
*       DIVERSE - DIVERSE                                                      *
*                                                                              *
*******************************************************************************/

/*LS-890926*********************************************************************
*       Get Environment Variable                                               *
*******************************************************************************/

SK_EntPnt_UT char *UT_GetEnv (char *var, short mstr, char *str)
{
    char *env;
#ifdef LINUX
    env = getenv (UT_StrUpper(var));
    if (env == NULL) {
        UT_StrCopy(str,"C:\\",mstr);
        UT_StrCat(str,var,(mstr-3));
    }
    else {
        UT_StrCopy(str,env,mstr);
        *(str+mstr-1) = '\0';
        UT_ClrTrailsp(str);
    }
    return str;
#else
    size_t len;
    _dupenv_s(&env, &len, UT_StrUpper(var));
    //env = getenv (UT_StrUpper(var));
    if (env == NULL) {
        UT_StrCopy(str,"C:\\",mstr);
        UT_StrCat(str,var,(mstr-3));
    }
    else {
        UT_StrCopy(str,env,mstr);
        *(str+mstr-1) = '\0';
        UT_ClrTrailsp(str);
    }
    return str;
#endif   
}


#ifdef WIN32

/*LS-890926*********************************************************************
*       Lag filnavn med path til FYSAK                                               *
*******************************************************************************/
SK_EntPnt_UT char *UT_MakeFysakPath ( char *str, short mstr, char *path, char *filename )
{
	size_t len;

	/* Standardverdi */
	if (path == NULL  ||  *path == '\0') {
		GetCurrentDirectory(mstr,str);
	} else {
		UT_StrCopy(str,path,mstr);
	}

	UT_ClrTrailsp(str);
	UT_FullPath(str,str,mstr);

	/* Heng på '\' */
	len = strlen(str);
	if (*(str+len-1) != '\\'  &&  *(str+len-1) != ':'){
		UT_StrCat(str, "\\", mstr);
	}

	/* Heng på filnavn */
	len = strlen(str);
	UT_StrCat(str, filename, mstr);

   return str;
}

#endif


#ifdef OS216

/*LS-890926*********************************************************************
*       Lag filnavn med path til FYSAK                                               *
*******************************************************************************/
SK_EntPnt_UT char *UT_MakeFysak ( char *str, short mstr, char *filename )
{
   char *cp,finn_env[_MAX_EXT+10];
   size_t len;
   char *env = NULL;

   /* S›k etter filtype, og hent environment-variabel */
   if ((cp = strchr(filename,'.')) != NULL) {
      cp++;
      strcpy(finn_env,"FYSAK_");
      strcat(finn_env,cp);
      size_t len;
      errno_t err = _dupenv_s(&env, &len, UT_StrUpper(finn_env));
		//env = getenv( UT_StrUpper(finn_env));
   }

   /* Spesialtype er ikke funnet, bruk FYSAK-standard */
   if (env == NULL) {
      size_t len;
      errno_t err = _dupenv_s(&env, &len, "FYSAK");
      //env = getenv ("FYSAK");
   }
 
   /* Standardverdi */
   if (env == NULL) {
      strncpy(str,"C:\\FYSAK\\",(size_t)(mstr-1));
      *(str+mstr-1) = '\0';

   } else {
      strncpy (str,env,(size_t)(mstr-1));
		*(str+mstr-1) = '\0';
      UT_ClrTrailsp(str);
   }

   /* Heng p† '\' */
   len = strlen(str);
   if (*(str+len-1) != '\\'  &&  *(str+len-1) != ':'){
      strncat (str,"\\",mstr-len-1);
      *(str+mstr-1) = '\0';
   }

   /* Heng p† filnavn */
   len = strlen(str);
	strncat (str,filename,mstr-len-1);
   *(str+mstr-1) = '\0';

    return str;
}

#endif


/*LS-880929*********************************************************************
*       Function : Inquire System Date                                         *
*******************************************************************************/

SK_EntPnt_UT void UT_InqDate (short *date)
{
#ifdef LINUX
   struct tm *ntime;
   time_t ltime=NULL;

   time(&ltime);

   ntime = localtime(&ltime);

    *date++ = (short)ntime->tm_year;
    *date++ = (short)ntime->tm_mon;
    *date++ = (short)ntime->tm_mday;
    *date   = (short)((ntime->tm_wday) ? ntime->tm_wday - 1 : 6);
#else
   time_t ltime=NULL;
   struct tm ntime;

   time(&ltime);

   localtime_s(&ntime,&ltime);

    *date++ = (short)ntime.tm_year;
    *date++ = (short)ntime.tm_mon;
    *date++ = (short)ntime.tm_mday;
    *date   = (short)((ntime.tm_wday) ? ntime.tm_wday - 1 : 6);
#endif
}


//*****************************************************************
// Henter og formatterer dagens dato som en 8-sifret streng
//*****************************************************************
SK_EntPnt_UT char *UT_InqDateString(void)
{ 
#ifdef LINUX
   struct tm *ntime;
   time_t aclock;
   static char szDato[9];


   time(&aclock);
   ntime = localtime(&aclock);
   UT_SNPRINTF(szDato,9,"%4d%02d%02d",
           1900+ntime->tm_year,
           ntime->tm_mon+1,
           ntime->tm_mday);

   return szDato;
#else
   struct tm ntime;
   time_t aclock;
   static char szDato[9];


   time(&aclock);
   localtime_s(&ntime,&aclock);
   UT_SNPRINTF(szDato,9,"%4d%02d%02d",
           1900+ntime.tm_year,
           ntime.tm_mon+1,
           ntime.tm_mday);

   return szDato;
#endif
}


//*****************************************************************
// Henter og formatterer dagens dato og tid som en 14-sifret 
// streng på formen ååååmmddttmmss.
//*****************************************************************
SK_EntPnt_UT char *UT_InqDatetimeString(void)
{ 
#ifdef LINUX
   struct tm *ntime;
   time_t aclock;
   static char szDatotid[15];

   time(&aclock);
   ntime = localtime(&aclock);
   UT_SNPRINTF(szDatotid,15,"%4d%02d%02d%02d%02d%02d",
           1900+ntime->tm_year,
           ntime->tm_mon+1,
           ntime->tm_mday,
           ntime->tm_hour,
           ntime->tm_min,
           ntime->tm_sec);

   return szDatotid;
#else
   struct tm ntime;
   time_t aclock;
   static char szDatotid[15];

   time(&aclock);
   localtime_s(&ntime,&aclock);
   UT_SNPRINTF(szDatotid,15,"%4d%02d%02d%02d%02d%02d",
           1900+ntime.tm_year,
           ntime.tm_mon+1,
           ntime.tm_mday,
           ntime.tm_hour,
           ntime.tm_min,
           ntime.tm_sec);

   return szDatotid;
#endif
}


/*LS-880929*********************************************************************
*        Inquire System Time                                                   *
*******************************************************************************/

SK_EntPnt_UT void UT_InqTime (short *tid)
{
#ifdef LINUX
   struct tm *ntime;
   time_t ltime;

   time(&ltime);
   ntime = localtime(&ltime);
   *tid++ = (short)ntime->tm_hour;
   *tid++ = (short)ntime->tm_min;
   *tid++ = (short)ntime->tm_sec;
#else 
   time_t ltime;
   struct tm ntime;

   time(&ltime);
   localtime_s(&ntime,&ltime);
   *tid++ = (short)ntime.tm_hour;
	*tid++ = (short)ntime.tm_min;
   *tid++ = (short)ntime.tm_sec;
#endif
}


/*LS-890913********************************************************************/
/*      Inquire Free Memory  i OS2                                            */
/******************************************************************************/
SK_EntPnt_UT extern unsigned long UT_InqFreemem (void)
{
#ifdef OS216
   ULONG size;
   DosMemAvail(&size);
	return size;

#else
   return 0L;
#endif
}


/*
JEK-920604
CH UT_SortD                                         Sorteringsrutine
CD ==================================================================
CD Formål:
CD Sorterer verdier i en double-tabell i stigende rekkefølge.
CD Teorien bak sorteringsalgoritmen(CombSort11) er beskrevet i
CD Byte April-91 s315-320.
CD
CD NB! Rutina flytter de enkelte elementer i tabellen!!
CD
CD PARAMETERLISTE:
CD Navn      Type  Array I/U  Merknad
CD ------------------------------------------------------------------
CD *db_arr   double       i/u Tabell som skal sorteres
CD size      short        i   Ant elementer i tabell
CD
CD Bruk:  UT_SortD(db_arr, size)
	==================================================================
*/
SK_EntPnt_UT void UT_SortD ( double *db_arr, short size)
{
	#define SHRINKFACTOR 1.3          /* Empirisk verdi */

	int  switches;
	int  i, j;
   int  top, gap;
   double dtmp;

   gap = size;                       /* Initier gap til tabellstørrelse */

   /* ----- Start løkke */
   do {
      gap = (int)((float)gap/SHRINKFACTOR);

      switch (gap) {
         case 0:                     /* Minste gap --> boblesortering */
            gap = 1;
            break;
         case 9:                     /* Spesielt for CombSort11 */
         case 10:
            gap = 11;
            break;
         default:
            break;
      }

      switches = 0;
      top = size - gap;
   
      for (i=0;i<top;++i) {
         j = i + gap;
         if (db_arr[i] > db_arr[j]) {
            dtmp = db_arr[i];
            db_arr[i] = db_arr[j];
            db_arr[j] = dtmp;
            ++switches;
         }
      }

   } while (switches || (gap > 1));
}
