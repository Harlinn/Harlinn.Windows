#pragma once
#ifndef pdstemplates_H
#define pdstemplates_H
#include "grib2.h"

//   PRGMMR: Gilbert         ORG: W/NP11    DATE: 2002-10-26
//
// ABSTRACT: This include file contains info on all the available
//   GRIB2 Product Definition Templates used in Section 4 (PDS).
//   The information describing each template is stored in the
//   pdstemplate structure defined below.
//
//   Each Template has three parts: The number of entries in the template
//   (mappdslen);  A map of the template (mappds), which contains the
//   number of octets in which to pack each of the template values; and
//   a logical value (needext) that indicates whether the Template needs
//   to be extended.  In some cases the number of entries in a template
//   can vary depending upon values specified in the "static" part of
//   the template.  ( See Template 4.3 as an example )
//
//   NOTE:  Array mappds contains the number of octets in which the
//   corresponding template values will be stored.  A negative value in
//   mappds is used to indicate that the corresponding template entry can
//   contain negative values.  This information is used later when packing
//   (or unpacking) the template data values.  Negative data values in GRIB
//   are stored with the left most bit set to one, and a negative number
//   of octets value in mappds[] indicates that this possibility should
//   be considered.  The number of octets used to store the data value
//   in this case would be the absolute value of the negative value in
//   mappds[].
//  
// 2005-12-08  Gilbert   Allow negative scale factors and limits for
//                       Templates 4.5 and 4.9
// 2009-12-15  Vuong     Added Product Definition Template 4.31
//                       Added Product Definition Template 4.15
// 2010-08-03  Vuong     Added Product Definition Template 4.40,4.41,4.42,4.43
// 2010-12-08  Vuong     Corrected Definition Template 4.42,4.43
// 2010-12-08  Vuong     Corrected Definition Template 4.42,4.43
// 2012-03-29  Vuong     Added Templates 4.44,4.45,4.46,4.47,4.48,4.50,
//                       4.51,4.91,4.32 and 4.52
// 2013-08-05  Vuong     Corrected 4.91 and added Templates 4.33,4.34,4.53,4.54
// 2015-10-07  Vuong     Added Templates 4.57, 4.60, 4.61 and
//                       allow a forecast time to be negative
//
//$$$

      #define MAXPDSTEMP 47           // maximum number of templates
      #define MAXPDSMAPLEN 200        // maximum template map length

      struct pdstemplate
      {
          g2int template_num;
          g2int mappdslen;
          g2int needext;
          g2int mappds[MAXPDSMAPLEN];
      };

const struct pdstemplate *get_templatespds(void);
g2int getpdsindex(g2int number);

#endif  /*  pdstemplates_H  */
