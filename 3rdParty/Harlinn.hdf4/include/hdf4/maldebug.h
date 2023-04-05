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

/*----------------------------------------------------------------------
 *
 *  maldebug.h -- Dynamic memory handler interface
 *  Description: memdebug.h provides the interface definitions for the dynamic
 *  memory handler.
 *  See memdebug.c for complete documentation.
 *
 */

#ifndef _MALDEBUG_H
#define _MALDEBUG_H

/* Compilation options */
#define MEM_LIST    /* Build internal list */
#define MEM_WHERE   /* Keep track of memory block source */
#define MEM_HEADER  /* Keep headers and footers around for each block */
#define MEM_COMP_FREE   /* Complement the space free'd */

/* Interface functions */
unsigned long Mem_Used(void);
void        Mem_Display(FILE * fp);

/* Interface functions to access only through macros */
#if defined(MEM_WHERE)
void       *mem_HDmalloc(size_t size, char *fil, int lin);
void       *mem_HDrealloc(void *old_ptr, size_t size, char *fil, int lin);
void       *mem_HDfree(void *ptr, char *fil, int lin);
#else
void       *mem_HDmalloc(size_t size);
void       *mem_HDrealloc(void *old_ptr, size_t size);
void       *mem_HDfree(void *ptr);
#endif

/* Interface macros */
#if !defined(__MALDEBUG__)
#if defined(MEM_WHERE)
#define HDmalloc(a)         mem_HDmalloc((a),__FILE__,__LINE__)
#define HDrealloc(a,b)      mem_HDrealloc((a),(b),__FILE__,__LINE__)
#define HDfree(a)           mem_HDfree((a),__FILE__,__LINE__)
#else
#define HDmalloc(a)         mem_HDmalloc(a)
#define HDrealloc(a,b)      mem_HDrealloc((a),(b))
#define HDfree(a)           mem_HDfree(a)
#endif
#endif

#endif /* _MALDEBUG_H */
