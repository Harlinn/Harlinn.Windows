/******************************************************************************
*
* STATENS KARTVERK  -  FYSAK
*
* Filename: fyut.h
*
* Content: Prototyper for generelle hjelperutiner og operativsystemavhengige rutiner.
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

#ifdef _WIN32
#define WIN32
#endif

#include "fybadef.h"

#include <stdio.h>

#ifndef SK_EntPnt_UT
#  define SK_EntPnt_UT
#endif


/* ----------------------------------------- Konstanter */
/* Div. manifeste konstantar */

#ifdef WIN32


/* For DOS/OS2/Windows */
#   define UT_SLASH  '\\'
#   define UT_STR_SLASH  "\\"
#   define UT_INT64  __int64
#   define UT_SNPRINTF _snprintf_s
#   define UT_FPRINTF fprintf_s
#   define UT_GETPID   _getpid

#else
          /* For UNIX */
#  ifdef LINUX /* specifically the LINUX */
#    include <stdint.h>
#    include <inttypes.h>
#    define UT_INT64 int64_t 
#  endif

#   define UT_SNPRINTF snprintf
#   define UT_FPRINTF fprintf
#   define UT_GETPID   getpid

#   define UT_SLASH  '/'
#   define UT_STR_SLASH  "/"
#   define cdecl
#   define EZERO 0

#  ifdef  _FILE_OFFSET_BITS
#    undef _FILE_OFFSET_BITS
#  endif
#  define _FILE_OFFSET_BITS 64
#  include <limits.h>
#  include <sys/types.h>

#  ifdef WIN32
#    include <io.h>
#  else
#    include <unistd.h>
#  endif

#  define _TRUNCATE 0
#  define _fseeki64 fseek
#  define _ftelli64 ftell
#  define _strcmpi  strcasecmp

#endif

#define UT_FALSE 0
#define UT_TRUE  1
#define UT_OVRFLW 2

#define UT_NULL 0L

#define UT_OK  0
#define UT_EOF 1
#define UT_ERROR -1
#define UT_READ   0
#define UT_WRITE  1
#define UT_UPDATE  2
#define UT_UNKNOWN 0
#define UT_OLD     1
#define UT_NEW     2

/* Konstanter for UT_KonverterTegnsett */
#define TS_UKJENT   0  /* Ukjent tegnsett */
#define TS_DOSN8    1  /* DOS norsk 8-bits (standardverdi) */
#define TS_ND7      2  /* Norsk Data 7-bits */
#define TS_DECM8    4  /* DEC multinasjonal 8-bits */
#define TS_DECN7    8  /* DEC norsk 7-bits */
#define TS_ISO8859  16 /* ISO8859-10 (Samisk og norsk mm. ) */

/* Div lengder for filnavn; jfr. stdlib.h */
#define _MAX_PATH   260  /* max. length of full pathname */
#define _MAX_DRIVE    3  /* max. length of drive component */
#define _MAX_DIR    256  /* max. length of path component */
#define _MAX_FNAME  256  /* max. length of file name component */
#define _MAX_EXT    256  /* max. length of extension component */


/* ----------------------------------------- Makroer */
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))



/*
 *!--------------------------------------------------------------!
 *! Oppdateringstid for fil                                      !
 *!--------------------------------------------------------------!
 */
typedef struct dFTID {
   unsigned short usAar;
   unsigned short usMnd;
   unsigned short usDag;
   unsigned short usTime;
   unsigned short usMin;
   unsigned short usSek;
} FTID;

typedef FTID *PFTID;


/* ----------------------------------------- Prototyper */

SK_EntPnt_UT void  UT_makepath(char *pathP,const char *driveP,const char *dirP,const char *nameP,const char *extP);
SK_EntPnt_UT void  UT_splitpath(const char *pathP,char *driveP,char *dirP,char *nameP,char *extP);
SK_EntPnt_UT short UT_InqPathSize(const char *pszPath,long *plSize);
SK_EntPnt_UT short UT_InqPathSize_i64(const char *pszPath,UT_INT64 *n64Size);
SK_EntPnt_UT short UT_SetPathSize(const char *pszPath,long lSize);
SK_EntPnt_UT short UT_SetPathSize_i64(const char *pszPath, UT_INT64 n64Size);
SK_EntPnt_UT short UT_InqPathTid(const char *pszPath,PFTID pFilTid);
SK_EntPnt_UT short UT_InqAvailSize(const char *pszPath,unsigned long *pulLedigPlass);
SK_EntPnt_UT short UT_FullPath(char *pszBuffer, const char *pszPath, size_t maxlen);
SK_EntPnt_UT short UT_DeleteFile(const char *pszPath);
SK_EntPnt_UT short UT_DeleteDir( const char *pszPath);
SK_EntPnt_UT short UT_CreateDir( const char *pszPath);
SK_EntPnt_UT short UT_FilnavnCmp( const char *pszFil1, const char *pszFil2);
SK_EntPnt_UT short UT_CopyFile( const char *pszFraFilnavn, const char *pszTilFilnavn,short sFeilHvisEksisterer);


/* Framhenting frå streng */
SK_EntPnt_UT char *UT_GetToken (char *str, short *l_tok);
SK_EntPnt_UT char  UT_StrToken (char *str, short ii, short *iu, short mt, char *token);
SK_EntPnt_UT char  UT_StrWord (char *str, short ii, short *iu, short mw, char *word);
SK_EntPnt_UT short UT_StrInt (char *str, short ii, short *iu, int *_int);
SK_EntPnt_UT short UT_StrInt64 (char str[], short ii, short *iu, UT_INT64 *i64);
SK_EntPnt_UT short UT_StrShort (char *str, short ii, short *iu, short *s);
SK_EntPnt_UT short UT_StrLong (char *str, short ii, short *iu, long *_long);
SK_EntPnt_UT short UT_StrUlong (char str[], short ii, short *iu, unsigned long *_ulong);
SK_EntPnt_UT short UT_StrDbl (char *str, short ii, short *iu, char decpt,double *dbl);
SK_EntPnt_UT void  UT_StrCopy (char *tx_to, const char *tx_from, int tx_len);
SK_EntPnt_UT short UT_StrCat (char *dst,const char *src, const int maxlen);
SK_EntPnt_UT int UT_memcpy(void *dest,size_t numberOfElements,const void *src,size_t count);
SK_EntPnt_UT int UT_strerror(char *buffer,size_t numberOfElements,int errnum);
SK_EntPnt_UT char *UT_strtok(char *strToken,const char *strDelimit,char **context);


/* Konvertering */
#ifdef OS216
SK_EntPnt_UT    short UT_AtoI (char *str, int *_int);
SK_EntPnt_UT    short UT_AtoS (char str[], short *s);
SK_EntPnt_UT    short UT_AtoL (char str[], long *_long);
#endif
SK_EntPnt_UT short UT_AtoD (char *str, char decpt, double *d);
SK_EntPnt_UT short UT_ItoA (int i, short sl, char *str);
SK_EntPnt_UT short UT_StoA (short s, short mstr, char *str);
SK_EntPnt_UT short UT_LtoA (long l, short sl, char *str);
SK_EntPnt_UT short UT_DtoA (double d, short dec, char decpt, short sl, char *str);

/* Strengmanipulering ellers */
SK_EntPnt_UT char *UT_ClrCrlf (char *str);
SK_EntPnt_UT char *UT_ClrTrailsp(char *str);
SK_EntPnt_UT char *UT_ClrExtrasp(char *str);
SK_EntPnt_UT void  UT_JustStr (char justmode, char fill, short lstr, char *str);
SK_EntPnt_UT short UT_Index (char *str, char *substr);
SK_EntPnt_UT void  UT_GetSubstr (char ctx[],short fra,short til,char sub[],short maxlen);
SK_EntPnt_UT char *UT_StrLower (char *tx);
SK_EntPnt_UT char *UT_StrUpper (char *tx);
SK_EntPnt_UT int   UT_StrCmpi(const char *pszTx1, const char *pszTx2);
SK_EntPnt_UT int   UT_StrColli(const char *pszTx1, const char *pszTx2);
SK_EntPnt_UT unsigned char *UT_Ascii7to8 (unsigned char *tx);
SK_EntPnt_UT unsigned char *UT_Ascii8to7 (unsigned char *tx);
SK_EntPnt_UT unsigned char *UT_ISO8859toAscii8(unsigned char *tx);
SK_EntPnt_UT unsigned char *UT_Ascii8toISO8859(unsigned char *tx);
SK_EntPnt_UT unsigned char *UT_ISO8859toAscii7(unsigned char *tx);
SK_EntPnt_UT unsigned char *UT_Ascii7toISO8859(unsigned char *tx);
SK_EntPnt_UT unsigned char *UT_KonverterTegnsett(short sFraTegnsett,short sTilTegnsett,
                                    unsigned char *pszTx);


/* Andre teiknhandterings rutiner */
SK_EntPnt_UT int UT_IsSpace (char c);
SK_EntPnt_UT int UT_IsPrint (int ch);
SK_EntPnt_UT int UT_IsLower (int ch);
SK_EntPnt_UT int UT_IsUpper (int ch);
SK_EntPnt_UT int UT_ToUpper (int ch);
SK_EntPnt_UT int UT_ToLower (int ch);

/* Matematiske funksjonar */
SK_EntPnt_UT double UT_RoundDD (double d);
SK_EntPnt_UT double UT_RoundHalfUpDD (double d);
SK_EntPnt_UT int    UT_RoundDI (double d);
SK_EntPnt_UT unsigned int UT_RoundDUI (double d);
SK_EntPnt_UT long   UT_RoundDL (double d);
SK_EntPnt_UT long long UT_RoundDLL (double d);
SK_EntPnt_UT short  UT_RoundDS (double d);

/* Kalender/klokke-rutiner */
SK_EntPnt_UT void UT_InqDate (short *date);
SK_EntPnt_UT char *UT_InqDateString(void);
SK_EntPnt_UT char *UT_InqDatetimeString(void);
SK_EntPnt_UT void UT_InqTime (short *time);

/* Høgnivå */
SK_EntPnt_UT FILE *UT_OpenFile     (const char *filnavn,const char *ftyp,
                                    short facc,short exist,short *ierr);
SK_EntPnt_UT short UT_ReadLine     (FILE *pfil,short llin, char clin[]);
SK_EntPnt_UT short UT_ReadLineCrlf (FILE *pfil,short llin, char clin[]);
SK_EntPnt_UT short UT_ReadLineNoComm(FILE *pfil,short llin, char *clin);
SK_EntPnt_UT short UT_WriteLine    (FILE *pfil,char clin[]);
SK_EntPnt_UT short UT_WriteLineCrlf(FILE *pfil,char clin[]);
SK_EntPnt_UT short UT_SetPos       (FILE *fi,long lpos);
SK_EntPnt_UT short UT_SetPos_i64   (FILE *fi,UT_INT64 n64FilPos);
SK_EntPnt_UT short UT_GetPos       (FILE *fi,long *lpos);
SK_EntPnt_UT short UT_GetPos_i64(FILE *fi,UT_INT64 *n64FilPos);
SK_EntPnt_UT short UT_Save         (FILE *pfil);

/* Div. rutiner */
SK_EntPnt_UT void UT_Bell (void);
SK_EntPnt_UT void UT_Sound (short freq, short dur);
SK_EntPnt_UT void UT_Pause (short dur);
SK_EntPnt_UT unsigned long UT_InqFreemem (void);
SK_EntPnt_UT char *UT_GetEnv (char *var, short mstr, char *str);
SK_EntPnt_UT char *UT_MakeFysak ( char *str, short mstr, char *filename );
SK_EntPnt_UT char *UT_MakeFysakPath ( char *str, short mstr, char *path, char *filename );
SK_EntPnt_UT void UT_SortD(double *db_arr, short size);

SK_EntPnt_UT unsigned long *UT_InitFlag(short sNlin);
SK_EntPnt_UT void UT_CloseFlag(unsigned long *plFlag);
SK_EntPnt_UT bool UT_SetFlag(unsigned long *plFlag,short sLine);
SK_EntPnt_UT short UT_GetFlag(unsigned long *plFlag,short sLine);

SK_EntPnt_UT short UT_StartProsess(char *pszCommandLine,short sVent);

SK_EntPnt_UT short UT_PutAnfTegn(char *pszTx, char cTegn, short sMaksLen);


/* --- Makroer -- */
#define UT_MALLOC  malloc
#define UT_FREE  free

#define UT_VENT 1
#define UT_FORTSETT 2



