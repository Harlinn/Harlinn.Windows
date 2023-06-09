#pragma once
#ifndef gridtemplates_H
#define gridtemplates_H
#include "grib2.h"

//   PRGMMR: Gilbert         ORG: W/NP11    DATE: 2001-10-26
//
// ABSTRACT: This Fortran Module contains info on all the available
//   GRIB2 Grid Definition Templates used in Section 3 (GDS).
//   The information describing each template is stored in the
//   gridtemplate structure defined below.
//
//   Each Template has three parts: The number of entries in the template
//   (mapgridlen);  A map of the template (mapgrid), which contains the
//   number of octets in which to pack each of the template values; and
//   a logical value (needext) that indicates whether the Template needs
//   to be extended.  In some cases the number of entries in a template
//   can vary depending upon values specified in the "static" part of
//   the template.  ( See Template 3.120 as an example )
//
//   NOTE:  Array mapgrid contains the number of octets in which the
//   corresponding template values will be stored.  A negative value in
//   mapgrid is used to indicate that the corresponding template entry can
//   contain negative values.  This information is used later when packing
//   (or unpacking) the template data values.  Negative data values in GRIB
//   are stored with the left most bit set to one, and a negative number
//   of octets value in mapgrid[] indicates that this possibility should
//   be considered.  The number of octets used to store the data value
//   in this case would be the absolute value of the negative value in
//   mapgrid[].
//  
// PROGRAM HISTORY LOG:
//
// 2001-10-26  Gilbert
// 2007-08-16  Vuong     -  Added GDT 3.204  Curvilinear Orthogonal Grid
// 2008-07-08  Vuong     -  Added GDT 3.32768 Rot Lat/Lon E-grid (Arakawa)
// 2010-05-11  Vuong     -  Added GDT 3.32769 Rotate Lat/Lon Non-E Staggered grid (Arakawa)
// 2013-08-06  Vuong     -  Added GDT 3.4,3.5,3.12,3.101,3.140
//
////////////////////////////////////////////////////////////////////

      #define MAXGRIDTEMP 31              // maximum number of templates
      #define MAXGRIDMAPLEN 200           // maximum template map length

      struct gridtemplate
      {
          g2int template_num;
          g2int mapgridlen;
          g2int needext;
          g2int mapgrid[MAXGRIDMAPLEN];
      };

const struct gridtemplate *get_templatesgrid(void);
g2int getgridindex(g2int number);

#endif  /*  gridtemplates_H  */
