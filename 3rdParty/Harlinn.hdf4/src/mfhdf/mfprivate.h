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
/******************************************************************************
file - mfprivate.h

  This file contains prototypes of private functions that are implemented
  in mfsd.c.  Some of them are used by new functions in mfdatainfo.c.
  The new file mfdatainfo.c keeps raw-data-information related functions
  separately from the rest of the API.  These functions were introduced by
  the hmap project.

  Aug 8, 2010 -BMR
******************************************************************************/

/* Get the dimension record */
NC_dim * SDIget_dim (NC *handle, int32 id);

/* Get the handle from this object */
NC * SDIhandle_from_id (int32 id, intn typ);

/* Get the variable record */
NC_var *SDIget_var (NC *handle, int32 sdsid);

/* Put an attribute in an attribute list */
intn SDIputattr (NC_array **ap, const char *name, int32 nt, intn count, const void * data);

/* Get index of coordinate variable */
int32 SDIgetcoordvar (NC *handle, NC_dim *dim, int32 id, int32 nt);

/* Free a variables AID */
int32 SDIfreevarAID (NC * handle, int32 index);

/* Get the attribute list */
intn SDIapfromid (int32 id, NC ** handlep, NC_array *** app);

/* Check permission on the file */
int SDI_can_clobber (const char *name);

