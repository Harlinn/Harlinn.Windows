/* ------------------------------
 * Fil: SetSize.c
 * ------------------------------ */

#include "fyut.h"

#ifdef LINUX
#  include <unistd.h>
#endif

#ifdef OS232
#  define INCL_DOSFILEMGR
#  define INCL_DOSERRORS
#  include <os2.h>
#endif

#ifdef OS216
#  define INCL_DOSFILEMGR
#  define INCL_DOSERRORS
#  include <os2.h>
#  include <io.h>
#endif

#ifdef WIN32
#	include <windows.h>
#  include <io.h>
#  include <Share.h>
#  include <fcntl.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <stdlib.h>
#endif

#ifdef BORLAND
#  include <fcntl.h>
#  include <sys/stat.h>
#endif



/*
AR-921013
CH UT_SetPathSize                                  Sett filstørrelse
CD ==================================================================
CD Formål:
CD Setter filstørrelsen for gitt fil.
CD
CD PARAMETERLISTE:
CD Type      Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char     *pszPath   i   Filnavn
CD long      lSize     i   Ønsket filstørrelse
CD short     sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_SetPathSize(szPath,lSize);
   ==================================================================
*/

SK_EntPnt_UT short UT_SetPathSize(const char *pszPath,long lSize)
{
#ifdef UNIX
   size_t filesize;

   filesize  = (size_t)lSize;
   return  (short) truncate(pszPath,filesize);
#endif

#ifdef OS232
   APIRET rc;
   HFILE   FileHandle;
   ULONG   Action;

   /* UT_FPRINTF(stderr,"SetPathSize: %s: %ld\n",pszPath,lSize); */

   rc = DosOpen(pszPath,                    /* File path name */
                &FileHandle,                /* File handle */
                &Action,                    /* Action taken */
                0,                          /* File primary allocation */
                FILE_NORMAL,                /* File attribute */
                OPEN_ACTION_FAIL_IF_NEW |    /* Open function type */
                OPEN_ACTION_OPEN_IF_EXISTS,
                OPEN_SHARE_DENYREADWRITE | OPEN_ACCESS_READWRITE, /* Open mode of the file */
                NULL);                      /* No extended attributes */

   if (rc == NO_ERROR) {
      rc = DosSetFileSize(FileHandle,(ULONG)lSize);
      DosClose(FileHandle);
	}

	return (short)rc;
#endif

#ifdef OS216
   int rc;
   HFILE   FileHandle;
   USHORT   Action;

   rc = DosOpen(pszPath,                    /* File path name */
                &FileHandle,                /* File handle */
                &Action,                    /* Action taken */
                0,                          /* File primary allocation */
                FILE_NORMAL,                /* File attribute */
                OPEN_ACTION_FAIL_IF_NEW |   /* Open function type */
                OPEN_ACTION_OPEN_IF_EXISTS,
                OPEN_SHARE_DENYREADWRITE | OPEN_ACCESS_READWRITE, /* Open mode of the file */
                0L);                      /* No extended attributes */

   if (rc == NO_ERROR) {
      rc = chsize(FileHandle,lSize);
		DosClose(FileHandle);
   }

	return (short)rc;
#endif


#ifdef WIN32
   int fh,rc;

	//fh = _open( pszPath, _O_RDWR | _O_BINARY | _O_RANDOM );
   _sopen_s(&fh, pszPath, _O_RDWR | _O_BINARY | _O_RANDOM, _SH_DENYRW, _S_IREAD | _S_IWRITE);

	 if (fh != -1) {
		  rc = _chsize(fh,lSize);
		  _close(fh);

	 }  else {
		rc = fh;
	}

	 return (short)rc;
#endif

#ifdef BORLAND
	 int fh,rc;


	 fh = open( pszPath, O_RDWR | O_BINARY);

	 if (fh != -1) {
		  rc = chsize(fh,lSize);
		  close(fh);

	 }  else {
		rc = fh;
	}

	 return (short)rc;
#endif
}


#ifdef WIN32
/*
AR-921013
CH UT_SetPathSize_i64                              Sett filstørrelse
CD ==================================================================
CD Formål:
CD Setter filstørrelsen for gitt fil.
CD
CD PARAMETERLISTE:
CD Type      Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char     *pszPath   i   Filnavn
CD UT_INT64  n64Size   i   Ønsket filstørrelse
CD short     sStatus   r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_SetPathSize_i64(szPath,lSize);
   ==================================================================
*/
SK_EntPnt_UT short UT_SetPathSize_i64(const char *pszPath, UT_INT64 n64Size)
{
   int fh,rc;

   //fh = _open( pszPath, _O_RDWR | _O_BINARY | _O_RANDOM );
   _sopen_s(&fh, pszPath, _O_RDWR | _O_BINARY | _O_RANDOM, _SH_DENYRW, _S_IREAD | _S_IWRITE);
  
   // Åpnet OK
   if (fh != -1)
   {
      rc = _chsize_s(fh,n64Size);

      // _chsize_s returns the value 0 if the file size is successfully changed.
      if (rc != 0)
      {
         char szError[256];
         UT_strerror(szError,256,errno);
         UT_FPRINTF(stderr,"(UT_SetPathSize_i64)Feil ved endring av filstørrelse (_chsize_s). (%s, Posisjon:%ld, Feil:%s)\n",pszPath,n64Size,szError);
      }

      _close(fh);
   } 

   // Feil ved filåpning
   else
   {
      char szError[256];
      UT_strerror(szError,256,errno);
      UT_FPRINTF(stderr,"(UT_SetPathSize_i64)Feil ved filåpning. (%s, Feil:%s)\n",pszPath,szError);
      rc = fh;
   }

   return (short)rc;
}
#else
SK_EntPnt_UT short UT_SetPathSize_i64(char *pszPath, UT_INT64 n64Size)
{
	return UT_SetPathSize(pszPath, n64Size);
}
#endif
