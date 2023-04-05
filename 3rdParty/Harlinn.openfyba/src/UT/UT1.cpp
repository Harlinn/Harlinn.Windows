/***************************************************************************
*                                                                           *
*       Hjelpebiblioteket   U T  (Utilities)                                *
*       Georg Langerak, Statens Kartverk / FYSAK-prosjektet, januar 1989    *
*       Fil: UT1.C : Filhandtering                                          *
*                                                                           *
****************************************************************************/

/*
CH  UT1                                                 Leser-på-Disk
CD  ==================================================================
CD  Rutiner for å åpne, posisjonere og lese/skrive på filer åpnet
CD  for binær les/skriv som stream.
CD  ==================================================================
CD
CH  INSTALLERINGS- OG BRUKS-OPPLYSNINGER:
CD
CD  Bibliotek..: UTLE.LIB
CD  Kildefiler.: UT1.C + fyut.h
CD  Versjon....: E00
CD  Eier.......: STATENS KARTVERK / FYSAK-prosjektet
CD  Ansvarlig..: Georg Langerak / Andreas Røstad
CD
CD  #include...: fyut.h
CD  ==================================================================
*/

//#include "stdafx.h"

#ifdef OS2
#   define INCL_DOSFILEMGR
#   define INCL_DOSERRORS
#   include <os2.h>
#endif

#ifdef UNIX
#  ifndef _INCLUDE_POSIX_SOURCE
#     define _INCLUDE_POSIX_SOURCE
#  endif
#  ifndef _HPUX_SOURCE
#     define _HPUX_SOURCE
#  endif
#  include<sys/stat.h>
#endif

#ifdef LINUX /*This is just a quick fix. The two parameter versions of these are just not portable.*/
#   define strcpy_s strcpy
#   define strcat_s strcat
#endif


#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#ifndef LINUX
  #include <share.h>
#endif

#include "fyut.h"

#ifdef WIN32
#  include <sys/stat.h>
#endif

#ifdef BORLAND
#  include <sys/stat.h>
#endif


/*******************************************************************************
*                                                                              *
*       RUTINER FOR VERSJONSKONTROLL                                         *
*                                                                              *
*******************************************************************************/

/*
GL-890215
AR-911006
CH UT_OpenFile                                          Åpner og sjekker fil
CD ==========================================================================
CD Bruk:
CD  fp = UT_OpenFile("TULLFILA","DAT",READ,OLD,&ierr);
CD
CD Parametre:
CD Type        Navn      I/U   Forklaring
CD --------------------------------------------------------------------------
CD const char *fnam       i    Filnavn inkl. type (Max 46 tegn inkl. '\0')
CD const char *ftyp       i    Filtype (extention) (Max 4 tegn inkl. '\0')
CD short   facc        i    Aksess (0=UT_READ,1=UT_WRITE,2=UT_UPDATE)
CD short   exist       i    Åpningstatus (0=UT_UNKNOWN,1=UT_OLD,2=UT_NEW)
CD short   &ierr       u    (UT_OK,UT_ERROR eller skriv printf(strerror(ierr));
CD FILE    filpeker    r    filpeker.
CD
CD Formål:
CD     Åpner en fil med angitt aksess og åpningstatus.
CD     returnerer status som kan benyttes videre eller utskrives
	==========================================================================
*/
SK_EntPnt_UT FILE *UT_OpenFile(const char *filnavn,const char *ftyp,short facc,short exist,short *ierr)
{
	FILE *fp;
	char mode[4];
	char drive[_MAX_DRIVE],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
	char path[_MAX_PATH];
	int filslutt = 0;

#  ifdef OS232
		FILESTATUS3 PathInfoBuf;
		APIRET rc;
#  endif

#  ifdef OS216
		FILESTATUS PathInfoBuf;
		int rc;
#  endif

#  ifdef UNIX
		struct stat buf;
		int status;
#  endif

#ifdef WIN32
		//struct _stat buf;
        struct _stat32i64 buf32i64;
		int status;
#endif

#ifdef BORLAND
		struct stat buf;
		int status;
#endif

   /* Lag fullstendig filnavn */
	UT_FullPath(path,filnavn,_MAX_PATH);

	/* Splitt filnavnet */
	UT_splitpath(path,drive,dir,fname,ext);

	/* Ikke gitt filtype */
	if (*ext == '\0') {
		if (ftyp != NULL) {
			if (*ftyp != '\0') {
				strcpy_s(ext,".");
				strcat_s(ext,ftyp);
			}
		}
	}

	/* Bygg opp filnavnet igjen */
	UT_makepath(path,drive,dir,fname,ext);

	mode[0] = '\0';

	/* UT_FPRINTF(stderr,"\nFilnavn \"%s\"\n",path); */

	/* Hent filopplysninger */
#  ifdef OS232
		rc = DosQueryPathInfo(path,FIL_STANDARD,&PathInfoBuf,sizeof(FILESTATUS3));
		/* UT_FPRINTF(stderr,"Fra DosQeryPathInfo rc = %d\n",rc); */
#  endif
#  ifdef OS216
		rc = DosQPathInfo(path,FIL_STANDARD,(PBYTE)&PathInfoBuf,sizeof(FILESTATUS),0);
#  endif
#  ifdef UNIX
		status =  stat(path,&buf);
#  endif
#  ifdef WIN32
		//status = _stat(path,&buf);
      status = _stat32i64(path,&buf32i64);
      /*
      if (status == -1){
         char szError[256];
         UT_strerror(szError,256,errno);
         szError[255] = '\0';
      }
      */

#  endif

#  ifdef BORLAND
		status =  stat(path,&buf);
#  endif


	/* Setter sammen flagg for åpningsmodus */
	if (facc == UT_READ && exist == UT_UNKNOWN) {
		/* Hvis filen IKKE eksisterer */
#     ifdef OS2
		if (rc == ERROR_FILE_NOT_FOUND) {
#     endif
#     ifdef UNIX
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef WIN32
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef BORLAND
		if (status == -1  &&  errno == ENOENT) {
#     endif
			strcpy_s(mode,"wb+");
		} else {      /* Filen finnes fra før */
			strcpy_s(mode,"rb");
		}
	} else if (facc == UT_READ  && exist == UT_OLD) {
		/* Filen finnes ikke */

#     ifdef OS2
		if (rc == ERROR_FILE_NOT_FOUND) {
#     endif
#     ifdef UNIX
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef WIN32
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef BORLAND
		if (status == -1  &&  errno == ENOENT) {
#     endif
			*ierr = ENOENT;
			return (NULL);     /* ===> RETUR */
		}

		strcpy_s(mode,"rb");

	} else if (facc == UT_READ  && exist == UT_NEW) {
		/* Sjekk at filen IKKE eksisterer */
#     ifdef OS2
		if (rc == ERROR_FILE_NOT_FOUND) {
#     endif
#     ifdef UNIX
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef WIN32
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef BORLAND
		if (status == -1  &&  errno == ENOENT) {
#     endif
			strcpy_s(mode,"wb+");
		} else {
			*ierr = EEXIST;
			return (NULL);     /* ===> RETUR */
		}

	} else if (facc == UT_WRITE && exist == UT_UNKNOWN) {
		strcpy_s(mode,"wb+");

	} else if (facc == UT_WRITE && exist == UT_OLD) {
		/* Filen finnes ikke */
#     ifdef OS2
		if (rc == ERROR_FILE_NOT_FOUND) {
#     endif
#     ifdef UNIX
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef WIN32
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef BORLAND
		if (status == -1  &&  errno == ENOENT) {
#     endif
			*ierr = ENOENT;
			return (NULL);     /* ===> RETUR */
		}

		/* Hvis filen er OK */
#     ifdef OS2
		if (rc == NO_ERROR) {
#     endif
#     ifdef UNIX
		if (status == 0) {
#     endif
#     ifdef WIN32
		if (status == 0) {
#     endif
#     ifdef BORLAND
		if (status == 0) {
#     endif
			strcpy_s(mode,"wb+");
		}

	} else if (facc == UT_WRITE && exist == UT_NEW) {
		/* Sjekk at filen IKKE eksisterer */
#     ifdef OS2
		if (rc == ERROR_FILE_NOT_FOUND) {
#     endif
#     ifdef UNIX
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef WIN32
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef BORLAND
		if (status == -1  &&  errno == ENOENT) {
#     endif
			strcpy_s(mode,"wb+");
		}

	} else if (facc == UT_UPDATE && exist == UT_UNKNOWN) {
		/* Hvis filen IKKE eksisterer */
#     ifdef OS2
			if (rc == ERROR_FILE_NOT_FOUND) {
#     endif
#     ifdef UNIX
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef WIN32
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef BORLAND
		if (status == -1  &&  errno == ENOENT) {
#     endif
			strcpy_s(mode,"wb+");

		} else {      /* Filen finnes fra før */
			strcpy_s(mode,"rb+");
			filslutt=1;
		}

	} else if (facc == UT_UPDATE  &&  exist == UT_OLD) {
		/* Filen finnes ikke */
#     ifdef OS2
		if (rc == ERROR_FILE_NOT_FOUND) {
#     endif
#     ifdef UNIX
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef WIN32
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef BORLAND
		if (status == -1  &&  errno == ENOENT) {
#     endif
			*ierr = ENOENT;
			return (NULL);     /* ===> RETUR */
		}

		strcpy_s(mode,"rb+");
		filslutt=1;

	} else if (facc == UT_UPDATE  &&  exist == UT_NEW) {
		/* Sjekk at filen IKKE eksisterer */
#     ifdef OS2
		if (rc == ERROR_FILE_NOT_FOUND) {
#     endif
#     ifdef UNIX
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef WIN32
		if (status == -1  &&  errno == ENOENT) {
#     endif
#     ifdef BORLAND
		if (status == -1  &&  errno == ENOENT) {
#     endif
			strcpy_s(mode,"wb+");
		}

	} else {                                    /* Ugyldig kombinasjon */
		*ierr=UT_ERROR;
		return(NULL);
	}

/*
_SH_COMPAT : Sets compatibility mode
_SH_DENYRW : Denies read and write access to file
_SH_DENYWR : Denies write access to file
_SH_DENYRD : Denies read access to file
_SH_DENYNO : Permits read and write access
_SH_SECURE : Sets secure mode (shared read, exclusive write access).
*/


   // ----- Selve filåpningen
	if (mode[0] != '\0') {
         fp = fopen(path,mode);
#if 0
	// TODO: File locking on windows
	// FIXME: LI_OpenIdxFil always opens in UT_UPDATE mode
      if (mode[0] == 'w' || mode[2] == '+')
      {
         fp = _fsopen(path,mode,_SH_DENYWR);   // Sperrer mot at andre åpner filen for skriving, godtar lesing
      }
      else
      {
         fp = _fsopen(path,mode,_SH_DENYNO);
      }
#endif


      if (fp  == NULL)
      {
			*ierr = errno;
		}

      else
      {
			*ierr =UT_OK;
			if (filslutt)
         {
				// Posisjoner på slutten av filen
#           ifdef OS2
					UT_SetPos(fp,(long)PathInfoBuf.cbFile);
#           endif
#           ifdef UNIX
					UT_SetPos(fp,(long)buf.st_size);
#           endif
#           ifdef WIN32
					UT_SetPos_i64(fp,buf32i64.st_size);
#           endif
#           ifdef BORLAND
					UT_SetPos(fp,(long)buf.st_size);
#           endif
			}
		}

		/* UT_FPRINTF(stderr,"Ierr: %d\n",*ierr); */
		/* UT_FPRINTF(stderr,strerror(*ierr)); */
	}

   else
   {
		*ierr = UT_ERROR;
		return (NULL);
	}

	if (*ierr != UT_OK)  fp=NULL;

   return fp;
}


/*
GL-890105
CH UT_ReadLineCrlf                     Leser en linje inkl cl/lf
CD ==================================================================
CD Formål......:  Leser en linje inkl. Crlf fra current posisjon.
CD
CD Aktivisering:  ist = UT_ReadLineCrlf(fil,llin,clin);
CD
CD Retur-verdier: short  UT_OK  - Lesing er ok
CD                short  UT_EOF - Du har lest End Of File
CD                short  UT_ERROR - Du har fått feil ved lesingen
CD
CD PARAMETERLISTE:
CD Navn      Type    i/U Merknad
CD --------------------------------------------------------------
CD pfil      FILE     i   Peker til filstruktur (def i stdio.h)
CD llin      short    i   Max lengde på clin inkl (\r\n\0)
CD clin      *char    u   Streng les. Må være 3 større enn behov.
	==================================================================
*/
SK_EntPnt_UT short UT_ReadLineCrlf(FILE *pfil,short llin, char *clin)
{
#ifdef UTGAAR
   short ierr = UT_OK;

   if (fgets(clin,llin,pfil) == NULL) {
	   if      (feof(pfil))   ierr = UT_EOF;
	   else if (ferror(pfil)) ierr = UT_ERROR;
   }
   if ((int)*clin == 26) ierr = UT_EOF;      /* LS-890928 */
   return (ierr);
#endif


   char *cp = clin;
   char *siste = clin + llin - 1;
   short ierr = UT_OK;
   int c;

   while (cp < siste) {
      c = getc(pfil);
      if (c == EOF) {
	      if (feof(pfil)) {
            if (cp == clin)  ierr = UT_EOF;
         } else if (ferror(pfil)) {
            ierr = UT_ERROR;
         }
         break;

      } else if (c == '\n') {
         *cp = c;
         cp++;
         break;

      } else if (c == '\0') {
         *cp = ' ';

      } else {
         *cp = c;
      }

      cp++;
   }

   *cp = '\0';

   if ((int)*clin == 26) ierr = UT_EOF;      /* LS-890928 */


   return (ierr);
}


/*
GL-890105
CH UT_ReadLine                        Leser en linje og fjerner crlf
CD ==================================================================
CD Aktivisering:  ist = UT_ReadLine(fil,llin,clin);
CD
CD Retur-verdier: short  UT_OK  - Lesing er ok
CD                short  UT_EOF - Du har lest End Of File
CD                short  UT_ERROR - Du har fått feil ved lesingen
CD
CD PARAMETERLISTE:
CD Navn    Type   i/U Merknad
CD -----------------------------------------------------------
CD pfil    FILE    i   Peker til filstruktur (def i stdio.h)
CD llin    short   i   Max lengde på clin inkl '\0'
CD clin    *char   u   Streng lest. Må være 3 større enn faktisk.
	==================================================================
*/
SK_EntPnt_UT short UT_ReadLine(FILE *pfil,short llin, char *clin)
{
#ifdef UTGAAR
	short ierr = UT_OK;
	size_t len;
									  /* Leser en linje */
	if   (fgets(clin,llin,pfil) == NULL) {
	   if (feof(pfil))  ierr = UT_EOF;
	   else             ierr = UT_ERROR;
	}
	if ((int)*clin == 26) ierr = UT_EOF;      /* LS-890928 */
									  /* Fjerner Crlf */
	len = strlen(clin);
	if  (len > 1) {
	   if      (clin[len-2] == '\r') clin[len-2]=clin[len-1]='\0'; /* crlf */
	   else if (clin[len-1] == '\n') clin[len-1]='\0';             /* lf */
	}
	return (ierr);
#endif


   char *cp = clin;
   char *siste = clin + llin - 1;
   short ierr = UT_OK;
   int c;

   while (cp < siste) {
      c = getc(pfil);
      if (c == EOF) {
	      if (feof(pfil)) {
            if (cp == clin)  ierr = UT_EOF;
         } else if (ferror(pfil)) {
            ierr = UT_ERROR;
         }
         break;

      } else if (c == '\n') {
         *cp = c;
         cp++;
         break;

      } else if (c == '\0') {
         *cp = ' ';

      } else {
         *cp = c;
      }

      cp++;
   }

   *cp = '\0';

   if ((int)*clin == 26) ierr = UT_EOF;      /* LS-890928 */


   /* Fjerner Crlf */
   if (cp-clin > 1) {
	   if (*(cp-2) == '\r') {
         *(cp-2) = *(cp-1) = '\0'; /* crlf */
      } else if (*(cp-1) == '\n') {
         *(cp-1) = '\0';             /* lf */
      }
	}

   return (ierr);
}


/*
GL-890308
CH UT_ReadLineNoComm             Leser linjer og fjerner kommentarer
CD ==================================================================
CD Aktivisering :  ist = UT_ReadLineNoComm(fil,llin,clin);
CD
CD Retur-verdier: short  UT_OK  - Lesing er ok
CD                short  UT_EOF - Du har lest End Of File
CD                short  UT_ERROR - Du har fått feil ved lesingen
CD
CD PARAMETERLISTE:
CD Type     Navn    i/U Merknad
CD ------------------------------------------------------------------
CD FILE     fi       i   Peker til filstruktur (def i stdio.h)
CD short    llin     i   Max lengde på clin inkl \r\n\0.(cr+lf)
CD char    *clin     u   Streng lest. (Uten \r\n. (cr+lf))
CD
CD Formål:
CD Leser en linje fra filen, og fjerner CrLf. Hvis linjen er blank
CD eller første "ikke-blanke-tegn" er utropstegn leses påfølgende linje(r).
	==================================================================
*/
SK_EntPnt_UT short UT_ReadLineNoComm(FILE *pfil,short llin, char *clin)
{
	short ierr;
	register char *cp=NULL;

	do{
		 ierr = UT_ReadLine(pfil,llin,clin);
		 if (ierr == UT_OK){
			  for (cp=clin;  UT_IsSpace(*cp) && *cp;  cp++){
					;
			  }
		 }
	} while (ierr == UT_OK && (!*cp || *cp=='!'));

	/* Fjern blanke på slutten */
	if (ierr == UT_OK) {
		UT_ClrTrailsp(clin);
	}

	return (ierr);
}


/*
GL-890107
CH UT_WriteLineCrlf                      Skriver en linje incl crlf
CD ==================================================================
CD Formål......:  Skriver en linje som alt HAR Crlf på slutten .
CD
CD Aktivisering:  ist = UT_WriteLineCrlf(fil,clin);
CD
CD Retur-verdier: short  UT_OK  - Lesing er ok
CD                short  UT_ERROR - Du har fått feil ved lesingen
CD
CD PARAMETERLISTE:
CD Navn      Type    i/U Merknad
CD --------------------------------------------
CD pfil      FILE     i   Peker til filstruktur (def i stdio.h)
CD clin      char[]   i   Streng som skal skrives (må ha \r\n\0 )
   ==================================================================
*/
SK_EntPnt_UT short UT_WriteLineCrlf(FILE *pfil,char clin[])
{
      fputs(clin,pfil);
      if (ferror(pfil))  return UT_ERROR;
      return UT_OK;
}


/*
GL-890107
CH UT_WriteLine                           Skriver en linje uten crlf
CD ==================================================================
CD Formål......:  Skriver en linje og legger på Crlf etterpå .
CD
CD Aktivisering:  ist = UT_WriteLine(fil,clin);
CD
CD Retur-verdier: short  UT_OK  - Lesing er ok
CD                short  UT_ERROR - Du har fått feil ved lesingen
CD
CD PARAMETERLISTE:
CD Navn      Type    i/U Merknad
CD --------------------------------------------
CD pfil      FILE     i   Peker til filstruktur (def i stdio.h)
CD clin      char[]   i   Streng som skal skrives.
   ==================================================================
*/
SK_EntPnt_UT short UT_WriteLine(FILE *pfil,char clin[])
{
      fputs(clin,pfil);
		fputs("\r\n",pfil);
      if (ferror(pfil)) return(UT_ERROR);
      return(UT_OK);
}


/*
GL-880809
CH UT_Save                             Berger diskbuffer ut på disk.
CD ==================================================================
CD Formål......:  Sikre at at operativsystemets filbuffer
CD                blir disklagret. (Sikre mot strømstans etc.)
CD
CD Aktivisering:  UT_Save(fil);
CD
CD Retur-verdier: short  UT_OK  - Lesing er ok
CD                short  UT_ERROR - Du har fått feil ved flushingen
CD
CD PARAMETERLISTE:
CD Navn      Type  Array i/U Merknad
CD ------------------------------------------------------------------
CD pfil      FILE         i   Peker til filstruktur (def i stdio.h)
   ==================================================================
*/
SK_EntPnt_UT short UT_Save (FILE *pfil)
{
   if (fflush(pfil) == EOF)  return (UT_ERROR);

   return(UT_OK);
}


/*
GL-871127
CH UT_SetPos                               Sette current filposisjon
CD ==================================================================
CD Formål......:  Setter filposisjon hvor det skal begynnes å lese fra
CD
CD Aktivisering:  ist = UT_SetPos(fil,lpos);
CD
CD Retur-verdier: short  UT_OK  - Lesing er ok
CD                short  UT_ERROR - Du har fått feil.
CD
CD PARAMETERLISTE:
CD Navn      Type  Array i/U Merknad
CD ------------------------------------------------------------------
CD pfil      FILE         i   Peker til filstruktur (def i stdio.h)
CD lpos      long         i   Fil-posisjon
   ==================================================================
*/
SK_EntPnt_UT short UT_SetPos  (FILE *fi,long lpos)
{
      if (fseek(fi,lpos,SEEK_SET)) return (UT_ERROR);
      return(UT_OK);
}


/*
CH UT_SetPos_i64                             Sette current filposisjon
CD ==================================================================
CD Formål......:  Setter filposisjon hvor det skal begynnes å lese fra
CD
CD Aktivisering:  ist = UT_SetPos_i64(fil,pos);
CD
CD Retur-verdier: short  UT_OK  - Utført OK.
CD                short  UT_ERROR - Du har fått feil.
CD
CD PARAMETERLISTE:
CD Type      Navn      i/U  Merknad
CD ------------------------------------------------------------------
CD FILE      pfil       i   Peker til filstruktur (def i stdio.h)
CD UT_INT64  n64FilPos  i   Fil-posisjon
   ==================================================================
*/
SK_EntPnt_UT short UT_SetPos_i64 (FILE *fi,UT_INT64 n64FilPos)
{
      if (_fseeki64(fi,n64FilPos,SEEK_SET)) return (UT_ERROR);
      return(UT_OK);
}


/*
GL-871127
CH UT_GetPos                                Finner neste filposisjon
CD ==================================================================
CD Formål......:  Finner NESTE posisjon på filen.
CD                Dette vil bli neste linje etter UT_Readxxx og,
CD                UT_Writexxxx.
CD
CD Aktivisering:  ist = UT_GetPos(fil,&lpos);
CD
CD Retur-verdier: short  UT_OK  - Lesing er ok
CD                short  UT_ERROR - Du har fått feil.
CD
CD PARAMETERLISTE:
CD Navn      Type  Array i/U Merknad
CD ------------------------------------------------
CD pfil      FILE         i   Peker til filstruktur (def i stdio.h)
CD lpos      long         u   Peker til filposisjon
   ==================================================================
*/
SK_EntPnt_UT short UT_GetPos(FILE *fi,long *lpos)
{
      *lpos = ftell(fi);
      if (*lpos == -1L ) return (UT_ERROR);
      return(UT_OK);
}


/*
CH UT_GetPos_i64                            Finner neste filposisjon
CD ==================================================================
CD Formål......:  Finner NESTE posisjon på filen.
CD                Dette vil bli neste linje etter UT_Readxxx og,
CD                UT_Writexxxx.
CD
CD Aktivisering:  ist = UT_GetPos_i64(fil,&n64FilPos);
CD
CD Retur-verdier: short  UT_OK  - Utført OK
CD                short  UT_ERROR - Du har fått feil.
CD
CD PARAMETERLISTE:
CD Type  Navn        i/U Merknad
CD ------------------------------------------------
CD FILE  pfil              i   Peker til filstruktur (def i stdio.h)
CD long  n64FilPos         u   Peker til filposisjon
   ==================================================================
*/
SK_EntPnt_UT short UT_GetPos_i64(FILE *fi,UT_INT64 *n64FilPos)
{
      *n64FilPos = _ftelli64(fi);
      if (*n64FilPos == -1L ) return (UT_ERROR);
      return(UT_OK);
}


