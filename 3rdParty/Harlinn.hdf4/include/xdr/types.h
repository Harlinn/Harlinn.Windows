/*    $NetBSD: types.h,v 1.13 2000/06/13 01:02:44 thorpej Exp $    */

/*
 * Copyright (c) 2009, Sun Microsystems, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of Sun Microsystems, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *    from: @(#)types.h 1.18 87/07/24 SMI
 *    from: @(#)types.h    2.3 88/08/15 4.0 RPCSRC
 * $FreeBSD: src/include/rpc/types.h,v 1.10.6.1 2003/12/18 00:59:50 peter Exp $
 */
/*
 * Rpc additions to <sys/types.h>
 */
#ifndef __TYPES_RPC_HEADER__
#define __TYPES_RPC_HEADER__

#include "h4config.h"

#ifdef H4_HAVE_STDINT_H
#include <stdint.h>
#endif

#ifndef u_char
typedef unsigned char u_char;
#endif
#ifndef u_short
typedef uint16_t      u_short;
#endif
#ifndef u_int
typedef uint32_t      u_int;
#endif
#ifndef u_long
typedef unsigned long u_long;
#endif
#ifndef u_quad_t
typedef uint64_t      u_quad_t;
#endif
#ifndef quad_t
typedef int64_t       quad_t;
#endif
#ifndef caddr_t
typedef char *        caddr_t;
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
typedef int32_t bool_t;

/* Define the enumerated type in the wire protocol. */
typedef int32_t enum_t;

#ifndef NULL
#    define NULL 0
#endif

#ifdef H4_HAVE_STDDEF_H
#include <stddef.h>
#endif
#ifdef H4_HAVE_STDLIB_H
#include <stdlib.h>
#else
extern char *malloc();
#endif

#define mem_alloc(bsize)        calloc(1, bsize)
#define mem_free(ptr, bsize)    free(ptr)

#ifdef H4_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef __CYGWIN32__
#include <time.h>
#endif
#ifdef H4_HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifndef INADDR_LOOPBACK
#define       INADDR_LOOPBACK         (u_long)0x7F000001
#endif
#ifndef MAXHOSTNAMELEN
#define        MAXHOSTNAMELEN  64
#endif

#endif /* ndef __TYPES_RPC_HEADER__ */
