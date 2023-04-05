/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 1993, University Corporation for Atmospheric Research           *
 * See netcdf/COPYRIGHT file for copying and redistribution conditions.      *
 *                                                                           *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF.  The full HDF copyright notice, including       *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://support.hdfgroup.org/ftp/HDF/releases/.  *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* $Id: error.c,v 1.14 90/02/23 16:08:55 davis Exp */


/* 
 *   Utility Functions to implement consistant error logging
 * mechanisms for netcdf
 */

/*LINTLIBRARY*/

#ifdef NO_STDARG  /* The 4.0 release should be ANSI compliant */
#undef NO_STDARG
#endif

#include	"local_nc.h"
#include	<stdio.h>
#ifndef NO_STDARG
#include	<stdarg.h>
#else
/* try varargs instead */
#include	<varargs.h>
#endif /* !NO_STDARG */

#include <errno.h>
#if defined ERRNO_MISSING
extern int errno;
#endif

#ifndef NO_STRERROR
#include <string.h> /* contains prototype for ansi libc function strerror() */
#else
/* provide a strerror function for older unix systems */
char *
strerror(errnum)
int errnum ;
{
	extern int sys_nerr;
	extern const char * const sys_errlist[];

	if (errnum < 0 || errnum >= sys_nerr)
		return NULL ;

	return (char *)sys_errlist[errnum] ;
}
#endif /* NO_STRERROR */


#ifdef USE_doprnt_FOR_vfprintf
/* 
 * kludge for ze ancienne regieme
 */
vfprintf(stream, fmt, va_alist)
     FILE *stream;
     char *fmt;
     va_dcl
{

  return _doprnt(fmt, va_alist, stream);

}
#endif


/*
 * Log SYSTEM errors
 * Use where you would want to call perror(3).
 * Calling sequence is
 *	nc_serror(format, arg1, arg2,...)
 * with zero or more args of types compatible with the associated format
 * specifiers.  For example:
 *         nc_serror("shutting down");
 *	   nc_serror("can't open %s", file_name);
 *         nc_serror("process %d in state %s",pid,state);
 */
void
#ifndef NO_STDARG
nc_serror(const char *fmt, ...)
#else
/*VARARGS1*/
nc_serror(fmt, va_alist)
     const char *fmt ;
     va_dcl
#endif /* !NO_STDARG */
{
    
    if( ncopts & NC_VERBOSE ) {
    	va_list args ;
        static const char unknown[] = "Unknown Error";
    	int errnum = errno;	/* save real errno in case we wipe it out */
    	const char * cp;

#ifndef NO_STDARG
        va_start(args, fmt) ;
#else
        va_start(args) ;
#endif /* !NO_STDARG */

        (void) fprintf(stderr,"%s: ", cdf_routine_name);
        (void) vfprintf(stderr,fmt,args) ;
        va_end(args) ;
        
        switch(errnum) {
	case 0 :
            ncerr = NC_NOERR ;
            (void) fputc('\n',stderr) ;
            break ;
            default :
		ncerr = NC_SYSERR ;
            (void) fprintf(stderr,": %s\n",
                           (cp = strerror(errnum)) == NULL ? unknown : cp ) ;
            break ;
        }

        (void) fflush(stderr);	/* to ensure log files are current */
        errno = 0 ; /* ??? */
    } /* NC_VERBOSE */
    
    if( ncopts & NC_FATAL ) {
	exit(ncopts) ;
    }
}

/*
 * Like nc_serror above, but doesn't check for system error.
 * Use for logging error conditions which are not system errors.
 * Calling sequence is
 *	NCadvise(ncerr, format, arg1, arg2,...)
 * with zero or more args of types compatible with the associated format
 * specifiers.  For example:
 *         NCadvise(NC_NOERR, "just advice");
 *         NCadvise(NC_EBADID, "%d is not a valid cdf id", cdfid);
 */
#ifndef NO_STDARG
void
NCadvise(int err, const char *fmt,...)
#else
/*VARARGS1*/
void
NCadvise(err, fmt, va_alist)
     int err ;
     const char *fmt ;
     va_dcl
#endif /* !NO_STDARG */
{
	va_list args ;

	ncerr = err ;

	if( ncopts & NC_VERBOSE )
	{
		(void) fprintf(stderr,"%s: ", cdf_routine_name);
#ifndef NO_STDARG
		va_start(args ,fmt) ;
#else
		va_start(args) ;
#endif /* !NO_STDARG */
		(void) vfprintf(stderr,fmt,args) ;
		va_end(args) ;
		(void) fputc('\n',stderr) ;
		(void) fflush(stderr);	/* to ensure log files are current */
	}

	if( (ncopts & NC_FATAL) && ncerr != NC_NOERR )
	{
		exit(ncopts) ;
	}
}
