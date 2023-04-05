/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
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

/* $Id$ */

/*-----------------------------------------------------------------------------
 * File:    dfutilf.c
 * Purpose: C stubs for Fortran utility routines
 * Invokes: dfutil.c
 * Contents:
 *  dfindnr_:       For a given tag, find the next ref after the given ref
 *---------------------------------------------------------------------------*/

#include "hdf.h"
#include "hproto_fortran.h"
/*-----------------------------------------------------------------------------
 * Name:    dfindnr
 * Purpose: For this tag, find the ref after lref
 * Inputs:  dfile: ptr to open DF file
 *          tag:   tag to look for
 *          lref:  ref after which to search
 *
 * Returns: the desired ref if successful, on failure with  DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFfindnextref
 *---------------------------------------------------------------------------*/

FRETVAL(intf)
ndfindnr(intf * dfile, intf * tag, intf * lref)
{
    return ((intf)DFfindnextref(*dfile, (uint16) *tag, (uint16) *lref));
}

/*
   CEND7MAX
 */

/*-----------------------------------------------------------------------------
 * Name:    dffindnextref
 * Purpose: For this tag, find the ref after lref
 * Inputs:  dfile: ptr to open DF file
 *          tag:   tag to look for
 *          lref:  ref after which to search
 *
 * Returns: the desired ref if successful, on failure with  DFerror set
 * Users:   HDF Fortran programmers
 * Invokes: DFfindnextref
 *---------------------------------------------------------------------------*/

FRETVAL(intf)
ndffindnextref(intf * dfile, intf * tag, intf * lref)
{
    return ((intf)DFfindnextref(*dfile, (uint16) *tag, (uint16) *lref));
}
