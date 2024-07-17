/*********************************************************************
 *   Copyright 2010, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *********************************************************************/

/* $Id: stubdap4.c,v 1.4 2010/05/24 19:48:15 dmh Exp $ */
/* $Header: /upc/share/CVS/netcdf-3/libncdap4/stubdap4.c,v 1.4 2010/05/24 19:48:15 dmh Exp $ */

#include "config.h"
#include "netcdf.h"

extern int NC3_initialize(void);
extern int NCD3_initialize(void);
extern int NC4_initialize(void);
extern int NCD4_initialize(void);

int
NC_initialize(void)
{
    NC3_initialize();
    NCD3_initialize();
    NC4_initialize();
    NCD4_initialize();
    return NC_NOERR;
}
