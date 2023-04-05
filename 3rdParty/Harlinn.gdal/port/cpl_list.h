#pragma once
/**********************************************************************
 * $Id$
 *
 * Name:     cpl_list.h
 * Project:  CPL - Common Portability Library
 * Purpose:  List functions.
 * Author:   Andrey Kiselev, dron@remotesensing.org
 *
 **********************************************************************
 * Copyright (c) 2003, Andrey Kiselev <dron@remotesensing.org>
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef CPL_LIST_H_INCLUDED
#define CPL_LIST_H_INCLUDED

#include <port/cpl_port.h>

/**
 * \file cpl_list.h
 *
 * Simplest list implementation.  List contains only pointers to stored
 * objects, not objects itself. All operations regarding allocation and
 * freeing memory for objects should be performed by the caller.
 *
 */

CPL_C_START

/** List element structure. */
typedef struct _CPLList CPLList;

/** List element structure. */
struct _CPLList
{
    /*! Pointer to the data object. Should be allocated and freed by the
     * caller.
     * */
    void        *pData;
    /*! Pointer to the next element in list. NULL, if current element is the
     * last one.
     */
    struct _CPLList    *psNext;
};

HGDAL_EXPORT CPLList *CPLListAppend( CPLList *psList, void * pData );
HGDAL_EXPORT CPLList *CPLListInsert( CPLList *psList, void * pData, int nPosition );
HGDAL_EXPORT CPLList *CPLListGetLast( CPLList *psList );
HGDAL_EXPORT CPLList *CPLListGet( CPLList * const psList, int nPosition );
HGDAL_EXPORT int CPLListCount( const CPLList *psList );
HGDAL_EXPORT CPLList *CPLListRemove( CPLList *psList, int nPosition );
HGDAL_EXPORT void CPLListDestroy( CPLList *psList );
HGDAL_EXPORT CPLList *CPLListGetNext( const CPLList *psElement );
HGDAL_EXPORT void *CPLListGetData( const CPLList *psElement );

CPL_C_END

#endif /* CPL_LIST_H_INCLUDED */
