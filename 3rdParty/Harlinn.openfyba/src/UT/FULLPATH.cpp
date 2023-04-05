/* ------------------------------
 * Fil: FullPath.c
 * ------------------------------ */

#include "fyba.h"
#include <stdlib.h>
#include <string.h>

#ifdef LINUX
#  include <unistd.h>
#  include <new>
#endif

#ifdef UNIX
#  include <ctype.h>
#endif

#ifdef OS2
#  define INCL_DOSFILEMGR
#  define INCL_DOSERRORS
#  include <os2.h>
#endif

#ifdef BORLAND
#  include <windows.h>
#endif

#ifdef WIN32
#  include <windows.h>
#endif

#include "fyut.h"


#ifdef UNIX

#define wchar_t char
#define wcschr  strchr

/*
CH _fullpath                    
CD ==============================================================
CD Makes a complete path from a non-complete path. Handles "..",
CD "." and will prepend the path with current working directory
CD if it is relative (does not start with slash)
CD
CD The function returns buffer, pointer to memory area containing 
CD full path if buffer was NULL, or NULL if a error occured
CD (e.g. full path was longer than maxlen and a buffer 
CD was supplied.) The pointer should be free'd by calling code.
CD
CD Parameters:
CD Type        Name             I/O  Explanation
CD -------------------------------------------------------------
CD char       *buffer           i/o  Buffer to put full path into or NULL.
CD const char *pathname          i   Pathname to expand
CD size_t     maxlen             i   Size of buffer.
CD char *                        r   buffer, pointer to char[] or NULL
CD  ==============================================================
*/
char * _fullpath(char *buffer, const char *pathname, size_t maxlen) {
	if(maxlen < _MAX_PATH) {
		return NULL;
	}
	char * wpath;
	wpath = new (std::nothrow) char[_MAX_PATH];
	if (wpath == NULL) { // could not allocate memory
		return NULL;
	}
	
	char * wpath2;
	wpath2 = new (std::nothrow) char[_MAX_PATH];
	if (wpath2 == NULL) {
		delete [] wpath;
		return NULL;
	}

	strncpy(wpath, pathname, _MAX_PATH);	
	strncpy(wpath2, pathname, _MAX_PATH);

	/* Make relativer paths of ./foo-paths */
	if(pathname[0] == '.' && pathname[1] == UT_SLASH) {
		strncpy(wpath, pathname+2, _MAX_PATH);
		strncpy(wpath, pathname+2, _MAX_PATH);
	}

	char * prevPos = NULL;
	
	char same[4] = { UT_SLASH, '.', UT_SLASH, '\0' }; // e.g. "/./"
    /* replace /./ with nothing */
    while ((prevPos = strstr(wpath, same)) != NULL) {
        prevPos[1] = '\0';
        UT_StrCopy(wpath2, wpath, _MAX_PATH);
        strncat(wpath2, (prevPos+strlen(same)), _MAX_PATH);
        UT_StrCopy(wpath, wpath2, _MAX_PATH);
    }
	char prev[5] = { UT_SLASH, '.', '.', UT_SLASH, '\0' }; // e.g "/../"

	int i = -1;
	/* Remove /../ and parent folder */
	while ((prevPos = strstr(wpath, prev)) != NULL) {
		/* Walk forward in the string until first slash or start of string */
		while((prevPos + i) >= wpath && prevPos[i] != UT_SLASH) {
			prevPos[i--] = '\0';
		}
		UT_StrCopy(wpath2, wpath, _MAX_PATH);
		strncat(wpath2, (prevPos+strlen(prev)), _MAX_PATH);
		UT_StrCopy(wpath, wpath2, _MAX_PATH);
		i = -1;
	}
	
	/* prepend cwd on relative paths */
	if(wpath[0] != UT_SLASH) {
		if(getcwd(wpath2, _MAX_PATH) == NULL) {
			delete [] wpath;
		    delete [] wpath2;
			return NULL;
		}
		/* getcwd gives ut the path w/o ending slash */
		strncat(wpath2, UT_STR_SLASH, _MAX_PATH-(strlen(wpath2)+1));
		strncat(wpath2, wpath, _MAX_PATH)-(strlen(wpath2)+1);
		UT_StrCopy(wpath, wpath2, _MAX_PATH);
	}

	int endLen = strlen(wpath);
	int startAt = 0;
	if(wpath[0] == UT_SLASH) { 
		endLen--;
		startAt = 1;
	}
	if(wpath[endLen] == UT_SLASH) {
		wpath[endLen] = '\0';
		endLen--;
	}
	delete [] wpath2;
	if (endLen < maxlen && buffer != NULL) { /* we have a buffer, and we have room in buffer */
       	UT_StrCopy(buffer, (wpath+startAt), maxlen);
		delete [] wpath;
		return buffer;
	} else if (buffer == NULL) { /* we have no buffer */
		char * tempbuf;
		if ((tempbuf = (char*)UT_MALLOC(endLen+1)) != NULL) {
			UT_StrCopy(tempbuf, (wpath+startAt), (endLen+1));
			delete [] wpath;
			return tempbuf;
		} else { /* failed to alloc memory*/
			delete [] wpath;
            return NULL;
		}
	} else { /* not room in buffer and we were supposed to use the buffer */
		delete [] wpath;
		return NULL;
	}
}

#endif


/*
AR-930423
CH UT_FullPath                              Finn fullstendig filnavn
CD ==================================================================
CD Formål:
CD Lag absolutt path navn fra relativt path navn.
CD I tilleg tolker denne environment-variabler inn i filnavnet.
CD Environment-varialen skrives i parantes.
CD
CD Eks:
CD    SET FKB=D:\DATA\SOSI\FKB
CD
CD   Filnavnet   (FKB)\CV03851V.SOS
CD   pakkes ut til  D:\DATA\SOSI\FKB\CV03851V.SOS
CD
CD PARAMETERLISTE:
CD Type             Navn       I/U  Merknad
CD ------------------------------------------------------------------
CD wchar_t            *pszBuffer u   Komplett filnavn
CD const wchar_t      *pszPath   i   Forkortet filnavn
CD size_t           maxlen    i   Max lengde av pszBuffer
CD short            sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_FullPath(szBuffer,szPath,maxlen);
	==================================================================
*/
SK_EntPnt_UT short  UT_FullPath(char *pszBuffer, const char *pszPath, size_t maxlen)
{
	char szFilnavn[_MAX_PATH];
	char *pszStart,*pszSlutt;
	char *env;
#ifdef BORLAND
	wchar_t  *pszOrgPath;
#endif

	/* Søk start- og sluttparantes */
	UT_StrCopy(szFilnavn,pszPath,_MAX_PATH);
	pszStart = strchr(szFilnavn,'(');
	pszSlutt = strchr(szFilnavn,')');

	/* Både start- og sluttparantes er funnet,
      og starten er først i strengen */
   if (pszStart != NULL  &&  pszSlutt != NULL  &&  pszStart < pszSlutt) {
      *pszStart++ = '\0';
		*pszSlutt++ = '\0';
#ifdef LINUX
      env = getenv( UT_StrUpper(pszStart));
#else      
      size_t len;
      _dupenv_s(&env, &len, UT_StrUpper(pszStart));
#endif

      /* Navnet er ikke funnet */
      if (env == NULL) {
         UT_StrCopy(szFilnavn,pszPath,_MAX_PATH);

		} else {
 		  UT_StrCat(szFilnavn,env,_MAX_PATH);
        UT_ClrTrailsp(szFilnavn);
        UT_StrCat(szFilnavn,pszPath+(pszSlutt-szFilnavn),_MAX_PATH);
		}
	}

	/* Hent filopplysninger */
#ifdef UNIX
   return  (short)(_fullpath(pszBuffer,szFilnavn,maxlen) != NULL)?  0 : 1;
#endif

#ifdef OS232
	return  (short) DosQueryPathInfo(szFilnavn,FIL_QUERYFULLNAME,pszBuffer,maxlen);
#endif

#ifdef OS216
	return  (short) DosQPathInfo(szFilnavn,FIL_QUERYFULLNAME,(PBYTE)pszBuffer,(USHORT)maxlen,0);
#endif

#ifdef WIN32
   return  (short)(_fullpath(pszBuffer,szFilnavn,maxlen) != NULL)?  0 : 1;
#endif

#ifdef BORLAND
	pszOrgPath = FullPath(pszBuffer,szFilnavn,maxlen);

	if (pszOrgPath != NULL)
		return((short)0);
	else
		return ((short)1);
#endif

}

