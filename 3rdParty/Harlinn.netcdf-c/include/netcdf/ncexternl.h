/*********************************************************************
 *   Copyright 2018, UCAR/Unidata
 *   See netcdf/COPYRIGHT file for copying and redistribution conditions.
 *   $Header$
 *********************************************************************/

#ifndef NCEXTERNL_H
#define NCEXTERNL_H

#define DLL_NETCDF 1

#if defined(DLL_NETCDF) /* define when library is a DLL */
#  if defined(BUILDING_HARLINN_NETCDF_C) /* define when building the library */
#   define MSC_EXTRA __declspec(dllexport)
#  else
#   define MSC_EXTRA __declspec(dllimport)
#pragma comment(lib,"Harlinn.netcdf-c.lib")
#  endif
#else
#  define MSC_EXTRA
#endif	/* defined(DLL_NETCDF) */
#ifndef EXTERNL
# define EXTERNL MSC_EXTRA extern
#endif

#endif /*NCEXTERNL_H*/
