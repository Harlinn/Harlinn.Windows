/* ------------------------------
 * Fil: DiskInfo.c
 * ------------------------------ */
#include "fyba.h"
#include <ctype.h>

#ifdef UNIX
#  ifndef _INCLUDE_POSIX_SOURCE
#     define _INCLUDE_POSIX_SOURCE
#  endif

#  ifndef _HPUX_SOURCE
#     define _HPUX_SOURCE
#  endif

#  ifdef SUNOS                  /* NB! DIKAS */
#     include <sys/statvfs.h>
#  else
#     include <sys/stat.h>
#     ifdef __APPLE__
#        include<sys/mount.h>
#     else
#        include<sys/vfs.h>
#     endif
#  endif

#  include <sys/types.h>
#  include <unistd.h>
#  include <limits.h>
#endif

#ifdef OS2
#  define INCL_DOSFILEMGR
#  define INCL_DOSERRORS
#  include <os2.h>
#endif

#ifdef WIN32
#  include <windows.h>
#  include <LIMITS.H>
#endif

#ifdef BORLAND
#  include <windows.h>
#endif

#include "fyut.h"

/*
AR-930623
CH UT_InqAvailSize                       Finn ledig plass på disken
CD ==================================================================
CD Formål:
CD Finner hvor mye plass som er ledig for utvidelse av gitt fil.
CD
CD PARAMETERLISTE:
CD Type          Navn     I/U  Merknad
CD ------------------------------------------------------------------
CD char           *pszPath        i   Filnavn inkl. full sti.
CD unsigned long  *pulLedigPlass  u   Ledig plass på disken
CD short           sStatus        r   Status; 0=OK, annen verdi er feil.
CD
CD Bruk:  sStatus = UT_InqAvailSize(pszPath,&ulLedigPLass);
   ==================================================================
*/
SK_EntPnt_UT short UT_InqAvailSize(const char *pszPath,unsigned long *pulLedigPlass)
{
#ifdef UNIX
   int rc;
#  ifdef SUNOS
      struct statvfs buf;
#  else
      struct statfs buf;
#  endif
   
   /* Hent filopplysninger */
   rc = statfs(pszPath,&buf);
   if (rc == 0) {
      *pulLedigPlass = buf.f_bavail * buf.f_bsize;
   }

   /* Hent filopplysninger */
#  ifdef SUNOS
      /* NB! statfs er på vei ut av systemet ! , bruker statvfs i stedet*/
      rc = statvfs(pszPath,&buf);
      if (rc == 0) {
         *pulLedigPlass = buf.f_bavail * buf.f_bsize;
      }

#  else
      rc = statfs(pszPath,&buf);
      if (rc == 0) {
         *pulLedigPlass = buf.f_bavail * buf.f_bsize;
      }
#  endif

   return (short)rc;
#endif


#ifdef OS232
   unsigned long ulDisk;
   char disk[_MAX_DRIVE],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
   APIRET rc;
   FSALLOCATE drive;

   /* Finn disknummer */
   UT_splitpath(pszPath,disk,dir,fname,ext);
   if (*disk != '\0') {
      ulDisk = toupper(*disk) - '@';
   } else {
      ulDisk = 0L;
   }

   /* Hent filopplysninger */
   rc = DosQueryFSInfo(ulDisk,FSIL_ALLOC,(PBYTE)&drive,sizeof drive);

   if (rc == NO_ERROR) {
      *pulLedigPlass = drive.cUnitAvail * drive.cSectorUnit * drive.cbSector;
   }

   return (short)rc;
#endif


#ifdef OS216
   unsigned short usDisk;
   char disk[_MAX_DRIVE],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
   int rc;
   FSALLOCATE drive;

   /* Finn disknummer */
   UT_splitpath(pszPath,disk,dir,fname,ext);
   if (*disk != '\0') {
      usDisk = toupper(*disk) - '@';
   } else {
      usDisk = 0;
   }

   /* Hent filopplysninger */
   rc = DosQFSInfo(usDisk,FSIL_ALLOC,(PBYTE)&drive,sizeof drive);

   if (rc == NO_ERROR) {
      *pulLedigPlass = drive.cUnitAvail * drive.cSectorUnit * drive.cbSector;
   }

   return (short)rc;
#endif


#ifdef WIN32
         char disk[_MAX_DRIVE+1],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
         DWORD  SectorsPerCluster;       // address of sectors per cluster
         DWORD  BytesPerSector;     // address of bytes per sector
         DWORD  FreeClusters;       // address of number of free clusters
         DWORD  Clusters;                 // address of total number of clusters
         
         UINT64 ui64; 

        // Finn disk
        UT_splitpath(pszPath,disk,dir,fname,ext);
        strcat_s(disk,"\\");
        //Hent filopplysninger
        if (GetDiskFreeSpace((LPCTSTR)disk,
                              (LPDWORD)&SectorsPerCluster,
                              (LPDWORD)&BytesPerSector,
                              (LPDWORD)&FreeClusters,
                              (LPDWORD)&Clusters  ) )
        {
           ui64 = (UINT64)FreeClusters * (UINT64)SectorsPerCluster * (UINT64)BytesPerSector;
           if (ui64 < ULONG_MAX)   *pulLedigPlass = (unsigned long)ui64;
           else                     *pulLedigPlass = ULONG_MAX;

           return 0;
        }
   return 1;
#endif

#ifdef BORLAND
         char disk[_MAX_DRIVE+1],dir[_MAX_DIR],fname[_MAX_FNAME],ext[_MAX_EXT];
         DWORD  SectorsPerCluster;      /* address of sectors per cluster */
         DWORD  BytesPerSector;     /* address of bytes per sector */
         DWORD  FreeClusters;       /* address of number of free clusters */
         DWORD  Clusters;               /* address of total number of clusters */

        /* Finn disk */
        UT_splitpath(pszPath,disk,dir,fname,ext);
        UT_StrCat(disk,"\\",_MAX_DRIVE+1);

        /* Hent filopplysninger */
        if (GetDiskFreeSpace((LPCTSTR)disk,
                                                (LPDWORD)&SectorsPerCluster,
                                                (LPDWORD)&BytesPerSector,
                                                (LPDWORD)&FreeClusters,
                                                (LPDWORD)&Clusters  ) ) {

                 *pulLedigPlass = FreeClusters * SectorsPerCluster * BytesPerSector;
                 return 0;
        }

        return 1;
#endif
}
