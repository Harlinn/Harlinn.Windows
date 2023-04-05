/* ------------------------------
 * Fil: StrtPros.c
 * ------------------------------ */


#ifdef UNIX
#  ifndef _INCLUDE_POSIX_SOURCE
#    define _INCLUDE_POSIX_SOURCE
#  endif
#  ifndef _HPUX_SOURCE
#    define _HPUX_SOURCE
#  endif
#endif

#ifdef OS2
#endif


#ifdef BORLAND
#endif

#include "fyut.h"

#ifdef WIN32
#  include<windows.h>
#endif


/*
AR-961118
CH  UT_StartProsess      
CD  ==============================================================
CD  Formål:
CD  Starter en ny prosess.
CD
CD  PARAMETERLISTE:
CD  Type   Navn           I/U Merknad
CD  ------------------------------------------------------------- 
CD  char  *pszCommandLine  i  Kommandolinje
CD  short  sVent           i  UT_VENT = Vent til prosessen avsluttes
CD                            UT_FORTSETT = Ikke vent
CD short  sStatus          r  Status:
CD                              UT_TRUE = OK
CD                              UT_FALSE = Feil.
CD
CD
CD  Bruk:
CD  sStatus = UT_StartProsess(szKommandolinje,UT_VENT);
CD
CD  ==============================================================
*/
SK_EntPnt_UT short UT_StartProsess(char *pszCommandLine,short sVent)
{

#ifdef WIN32
   PROCESS_INFORMATION ProcessInfo;
   STARTUPINFO StartupInfo;
   DWORD ExitCode = 0;
   //char szCurrentDir[_MAX_PATH];
   //char szShortPath[100];


   // Setter opp oppstartinformasjon
   StartupInfo.cb = sizeof(STARTUPINFO); 
   StartupInfo.lpDesktop = NULL; 
   StartupInfo.lpTitle = NULL; 
   StartupInfo.cbReserved2 = 0;
   StartupInfo.lpReserved = NULL; 
   StartupInfo.lpReserved2 = NULL;
   StartupInfo.dwFlags = 0;
   //   STARTF_USESTDHANDLES	If this value is specified, sets the standard input of the process, standard output,
   //                        and standard error handles to the handles specified in the hStdInput, hStdOutput, 
   //                        and hStdError members of the STARTUPINFO structure. The CreateProcess function's fInheritHandles
   //                        parameter must be set to TRUE for this to work properly.
	//                        If this value is not specified, the hStdInput, hStdOutput, and hStdError members of the STARTUPINFO
   //                        structure are ignored.

   //StartupInfo.dwX; 
   //StartupInfo.dwY; 
   //StartupInfo.dwXSize; 
   //StartupInfo.dwYSize; 
   //StartupInfo.dwXCountChars; 
   //StartupInfo.dwYCountChars; 
   //StartupInfo.dwFillAttribute; 
   //StartupInfo.wShowWindow; 
   //StartupInfo.hStdInput; 
   //StartupInfo.hStdOutput; 
   //StartupInfo.hStdError; 


   //GetCurrentDirectory(_MAX_PATH,szCurrentDir);
   //GetShortPathName(szCurrentDir,szShortPath,100);

   // Utfører system-kommando
   if ( ! CreateProcess(NULL, pszCommandLine, NULL, NULL, FALSE,
                        NORMAL_PRIORITY_CLASS , 
                                  //CREATE_NEW_CONSOLE	
                                  //CREATE_NEW_PROCESS_GROUP	
                                  //CREATE_SEPARATE_WOW_VDM	
                                  //CREATE_SHARED_WOW_VDM	
                        NULL, NULL, &StartupInfo, &ProcessInfo)) {
      return UT_FALSE;
   }   

   // Vent til prosessen er ferdig
   if (sVent == UT_VENT) {
      WaitForSingleObject( ProcessInfo.hProcess, INFINITE);

      //Retrieves the termination status of the specified process.
      GetExitCodeProcess(ProcessInfo.hProcess, &ExitCode);
   }

   CloseHandle(ProcessInfo.hProcess);
   CloseHandle(ProcessInfo.hThread);
   
   return (ExitCode == 0)? UT_TRUE:UT_FALSE;

#else

   return UT_FALSE;
#endif
}
