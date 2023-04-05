
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
 */


/*
 * xdr_float.c, Generic XDR routines implementation.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 *
 * These are the "floating point" xdr routines used to (de)serialize
 * most common data items.  See xdr.h for more info on the interface to
 * xdr.
 */

#include "h4config.h"

#include <stdio.h>

#include "types.h"
#include "xdr.h"

bool_t
xdr_float(xdrs, fp)
    XDR *xdrs;
    float *fp;
{
    switch (xdrs->x_op) {

    case XDR_ENCODE:
        return (XDR_PUTINT32(xdrs, (int32_t *)fp));

    case XDR_DECODE:
        return (XDR_GETINT32(xdrs, (int32_t *)fp));

    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_double(xdrs, dp)
    XDR *xdrs;
    double *dp;
{
    int32_t *i32p;
    bool_t rv;

    if (!dp)
        return FALSE;

    switch (xdrs->x_op) {
    case XDR_ENCODE:
        i32p = (int32_t *)(void *)dp;
#ifdef H4_WORDS_BIGENDIAN
        rv = XDR_PUTINT32(xdrs, i32p);
        if (!rv)
            return (rv);
        rv = XDR_PUTINT32(xdrs, i32p+1);
#else
        rv = XDR_PUTINT32(xdrs, i32p+1);
        if (!rv)
            return (rv);
        rv = XDR_PUTINT32(xdrs, i32p);
#endif
        return rv;
        break;

    case XDR_DECODE:
        i32p = (int32_t *)(void *)dp;
#ifdef H4_WORDS_BIGENDIAN
        rv = XDR_GETINT32(xdrs, i32p);
        if (!rv)
            return (rv);
        rv = XDR_GETINT32(xdrs, i32p+1);
#else
        rv = XDR_GETINT32(xdrs, i32p+1);
        if (!rv)
            return (rv);
        rv = XDR_GETINT32(xdrs, i32p);
#endif
        return (rv);
        break;

    case XDR_FREE:
        return TRUE;
    } /* switch xdrs->x_op */

    return FALSE;
}
