#pragma once
/******************************************************************************
 * $Id$
 *
 * Project:  Common Portability Library
 * Purpose:  Functions for reading and scanning CSV (comma separated,
 *           variable length text files holding tables) files.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 1999, Frank Warmerdam
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef CPL_CSV_H_INCLUDED
#define CPL_CSV_H_INCLUDED

#include <stdio.h>

#include <port/cpl_conv.h>
#include <port/cpl_string.h>
#include <port/cpl_vsi.h>

CPL_C_START

typedef enum {
    CC_ExactString,
    CC_ApproxString,
    CC_Integer
} CSVCompareCriteria;

HGDAL_EXPORT const char *CSVFilename( const char * );

HGDAL_EXPORT char CSVDetectSeperator( const char *pszLine );

HGDAL_EXPORT char **CSVReadParseLine( FILE *fp);
HGDAL_EXPORT char **CSVReadParseLine2( FILE *fp, char chDelimiter );

HGDAL_EXPORT char **CSVReadParseLineL( VSILFILE *fp);
HGDAL_EXPORT char **CSVReadParseLine2L( VSILFILE *fp, char chDelimiter );

HGDAL_EXPORT char **CSVScanLines( FILE *, int, const char *, CSVCompareCriteria );
HGDAL_EXPORT char **CSVScanLinesL( VSILFILE *, int, const char *, CSVCompareCriteria );
HGDAL_EXPORT char **CSVScanFile( const char *, int, const char *,
                            CSVCompareCriteria );
HGDAL_EXPORT char **CSVScanFileByName( const char *, const char *, const char *,
                                  CSVCompareCriteria );
HGDAL_EXPORT char **CSVGetNextLine( const char * );
HGDAL_EXPORT int CSVGetFieldId( FILE *, const char * );
HGDAL_EXPORT int CSVGetFieldIdL( VSILFILE *, const char * );
HGDAL_EXPORT int CSVGetFileFieldId( const char *, const char * );

HGDAL_EXPORT void CSVDeaccess( const char * );

HGDAL_EXPORT const char *CSVGetField( const char *, const char *, const char *,
                                 CSVCompareCriteria, const char * );

#ifndef DOXYGEN_XML
HGDAL_EXPORT void SetCSVFilenameHook( const char *(*)(const char *) );
#endif

CPL_C_END

#endif /* ndef CPL_CSV_H_INCLUDED */
