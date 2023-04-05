/*! \file
Copyright (c) 2003, The Regents of the University of California, through
Lawrence Berkeley National Laboratory (subject to receipt of any required 
approvals from U.S. Dept. of Energy) 

All rights reserved. 

The source code is distributed under BSD license, see the file License.txt
at the top-level directory.
*/

/*! @file slu_dcomplex.h
 * \brief Header file for complex operations
 * <pre> 
 *  -- SuperLU routine (version 2.0) --
 * Univ. of California Berkeley, Xerox Palo Alto Research Center,
 * and Lawrence Berkeley National Lab.
 * November 15, 1997
 *
 * Contains definitions for various complex operations.
 * This header file is to be included in source files z*.c
 * </pre>
 */
#ifndef __SUPERLU_DCOMPLEX /* allow multiple inclusions */
#define __SUPERLU_DCOMPLEX

#include "slu_def.h"

#ifndef DCOMPLEX_INCLUDE
#define DCOMPLEX_INCLUDE

typedef struct { double r, i; } doublecomplex;


/* Macro definitions */

/*! \brief Complex Addition c = a + b */
#define z_add(c, a, b) { (c)->r = (a)->r + (b)->r; \
			 (c)->i = (a)->i + (b)->i; }

/*! \brief Complex Subtraction c = a - b */
#define z_sub(c, a, b) { (c)->r = (a)->r - (b)->r; \
			 (c)->i = (a)->i - (b)->i; }

/*! \brief Complex-Double Multiplication */
#define zd_mult(c, a, b) { (c)->r = (a)->r * (b); \
                           (c)->i = (a)->i * (b); }

/*! \brief Complex-Complex Multiplication */
#define zz_mult(c, a, b) { \
	double cr, ci; \
    	cr = (a)->r * (b)->r - (a)->i * (b)->i; \
    	ci = (a)->i * (b)->r + (a)->r * (b)->i; \
    	(c)->r = cr; \
    	(c)->i = ci; \
    }

#define zz_conj(a, b) { \
        (a)->r = (b)->r; \
        (a)->i = -((b)->i); \
    }

/*! \brief Complex equality testing */
#define z_eq(a, b)  ( (a)->r == (b)->r && (a)->i == (b)->i )


#ifdef __cplusplus
extern "C" {
#endif

/* Prototypes for functions in dcomplex.c */

SUPERLU_EXPORT
void z_div(doublecomplex *, doublecomplex *, doublecomplex *);

SUPERLU_EXPORT
double z_abs(doublecomplex *);     /* exact */

SUPERLU_EXPORT
double z_abs1(doublecomplex *);    /* approximate */

SUPERLU_EXPORT
void z_exp(doublecomplex *, doublecomplex *);

SUPERLU_EXPORT
void d_cnjg(doublecomplex *r, doublecomplex *z);

SUPERLU_EXPORT
double d_imag(doublecomplex *);

SUPERLU_EXPORT
doublecomplex z_sgn(doublecomplex *);

SUPERLU_EXPORT
doublecomplex z_sqrt(doublecomplex *);



#ifdef __cplusplus
  }
#endif

#endif

#endif  /* __SUPERLU_DCOMPLEX */
