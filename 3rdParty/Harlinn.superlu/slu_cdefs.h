/*! \file
Copyright (c) 2003, The Regents of the University of California, through
Lawrence Berkeley National Laboratory (subject to receipt of any required 
approvals from U.S. Dept. of Energy) 

All rights reserved. 

The source code is distributed under BSD license, see the file License.txt
at the top-level directory.
*/

/*! @file slu_cdefs.h
 * \brief Header file for real operations
 * 
 * <pre> 
 * -- SuperLU routine (version 4.1) --
 * Univ. of California Berkeley, Xerox Palo Alto Research Center,
 * and Lawrence Berkeley National Lab.
 * November, 2010
 * 
 * Global data structures used in LU factorization -
 * 
 *   nsuper: #supernodes = nsuper + 1, numbered [0, nsuper].
 *   (xsup,supno): supno[i] is the supernode no to which i belongs;
 *	xsup(s) points to the beginning of the s-th supernode.
 *	e.g.   supno 0 1 2 2 3 3 3 4 4 4 4 4   (n=12)
 *	        xsup 0 1 2 4 7 12
 *	Note: dfs will be performed on supernode rep. relative to the new 
 *	      row pivoting ordering
 *
 *   (xlsub,lsub): lsub[*] contains the compressed subscript of
 *	rectangular supernodes; xlsub[j] points to the starting
 *	location of the j-th column in lsub[*]. Note that xlsub 
 *	is indexed by column.
 *	Storage: original row subscripts
 *
 *      During the course of sparse LU factorization, we also use
 *	(xlsub,lsub) for the purpose of symmetric pruning. For each
 *	supernode {s,s+1,...,t=s+r} with first column s and last
 *	column t, the subscript set
 *		lsub[j], j=xlsub[s], .., xlsub[s+1]-1
 *	is the structure of column s (i.e. structure of this supernode).
 *	It is used for the storage of numerical values.
 *	Furthermore,
 *		lsub[j], j=xlsub[t], .., xlsub[t+1]-1
 *	is the structure of the last column t of this supernode.
 *	It is for the purpose of symmetric pruning. Therefore, the
 *	structural subscripts can be rearranged without making physical
 *	interchanges among the numerical values.
 *
 *	However, if the supernode has only one column, then we
 *	only keep one set of subscripts. For any subscript interchange
 *	performed, similar interchange must be done on the numerical
 *	values.
 *
 *	The last column structures (for pruning) will be removed
 *	after the numercial LU factorization phase.
 *
 *   (xlusup,lusup): lusup[*] contains the numerical values of the
 *	rectangular supernodes; xlusup[j] points to the starting
 *	location of the j-th column in storage vector lusup[*]
 *	Note: xlusup is indexed by column.
 *	Each rectangular supernode is stored by column-major
 *	scheme, consistent with Fortran 2-dim array storage.
 *
 *   (xusub,ucol,usub): ucol[*] stores the numerical values of
 *	U-columns outside the rectangular supernodes. The row
 *	subscript of nonzero ucol[k] is stored in usub[k].
 *	xusub[i] points to the starting location of column i in ucol.
 *	Storage: new row subscripts; that is subscripts of PA.
 * </pre>
 */
#ifndef __SUPERLU_cSP_DEFS /* allow multiple inclusions */
#define __SUPERLU_cSP_DEFS

/*
 * File name:		csp_defs.h
 * Purpose:             Sparse matrix types and function prototypes
 * History:
 */

#ifdef _CRAY
#include <fortran.h>
#endif

/* Define my integer type int_t */
typedef int int_t; /* default */

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "slu_Cnames.h"
#include "supermatrix.h"
#include "slu_util.h"
#include "slu_scomplex.h"


/* -------- Prototypes -------- */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Driver routines */
SUPERLU_EXPORT
extern void
cgssv(superlu_options_t *, SuperMatrix *, int *, int *, SuperMatrix *,
      SuperMatrix *, SuperMatrix *, SuperLUStat_t *, int *);

SUPERLU_EXPORT
extern void
cgssvx(superlu_options_t *, SuperMatrix *, int *, int *, int *,
       char *, float *, float *, SuperMatrix *, SuperMatrix *,
       void *, int, SuperMatrix *, SuperMatrix *,
       float *, float *, float *, float *,
       GlobalLU_t *, mem_usage_t *, SuperLUStat_t *, int *);

    /* ILU */
SUPERLU_EXPORT
extern void
cgsisv(superlu_options_t *, SuperMatrix *, int *, int *, SuperMatrix *,
      SuperMatrix *, SuperMatrix *, SuperLUStat_t *, int *);

SUPERLU_EXPORT
extern void
cgsisx(superlu_options_t *, SuperMatrix *, int *, int *, int *,
       char *, float *, float *, SuperMatrix *, SuperMatrix *,
       void *, int, SuperMatrix *, SuperMatrix *, float *, float *,
       GlobalLU_t *, mem_usage_t *, SuperLUStat_t *, int *);


/*! \brief Supernodal LU factor related */
SUPERLU_EXPORT
extern void
cCreate_CompCol_Matrix(SuperMatrix *, int, int, int, complex *,
		       int *, int *, Stype_t, Dtype_t, Mtype_t);
SUPERLU_EXPORT
extern void
cCreate_CompRow_Matrix(SuperMatrix *, int, int, int, complex *,
		       int *, int *, Stype_t, Dtype_t, Mtype_t);
SUPERLU_EXPORT
extern void
cCopy_CompCol_Matrix(SuperMatrix *, SuperMatrix *);

SUPERLU_EXPORT
extern void
cCreate_Dense_Matrix(SuperMatrix *, int, int, complex *, int,
		     Stype_t, Dtype_t, Mtype_t);

SUPERLU_EXPORT
extern void
cCreate_SuperNode_Matrix(SuperMatrix *, int, int, int, complex *, 
		         int *, int *, int *, int *, int *,
			 Stype_t, Dtype_t, Mtype_t);

SUPERLU_EXPORT
extern void
cCopy_Dense_Matrix(int, int, complex *, int, complex *, int);

SUPERLU_EXPORT
extern void    countnz (const int, int *, int *, int *, GlobalLU_t *);
SUPERLU_EXPORT
extern void    ilu_countnz (const int, int *, int *, GlobalLU_t *);
SUPERLU_EXPORT
extern void    fixupL (const int, const int *, GlobalLU_t *);

SUPERLU_EXPORT
extern void    callocateA (int, int, complex **, int **, int **);
SUPERLU_EXPORT
extern void    cgstrf (superlu_options_t*, SuperMatrix*,
                       int, int, int*, void *, int, int *, int *, 
                       SuperMatrix *, SuperMatrix *, GlobalLU_t *,
		       SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern int     csnode_dfs (const int, const int, const int *, const int *,
			     const int *, int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     csnode_bmod (const int, const int, const int, complex *,
                              complex *, GlobalLU_t *, SuperLUStat_t*);
SUPERLU_EXPORT
extern void    cpanel_dfs (const int, const int, const int, SuperMatrix *,
			   int *, int *, complex *, int *, int *, int *,
			   int *, int *, int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern void    cpanel_bmod (const int, const int, const int, const int,
                           complex *, complex *, int *, int *,
			   GlobalLU_t *, SuperLUStat_t*);
SUPERLU_EXPORT
extern int     ccolumn_dfs (const int, const int, int *, int *, int *, int *,
			   int *, int *, int *, int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     ccolumn_bmod (const int, const int, complex *,
			   complex *, int *, int *, int,
                           GlobalLU_t *, SuperLUStat_t*);

SUPERLU_EXPORT
extern int     ccopy_to_ucol (int, int, int *, int *, int *,
                              complex *, GlobalLU_t *);         

SUPERLU_EXPORT
extern int     cpivotL (const int, const double, int *, int *, 
                         int *, int *, int *, GlobalLU_t *, SuperLUStat_t*);

SUPERLU_EXPORT
extern void    cpruneL (const int, const int *, const int, const int,
			  const int *, const int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern void    creadmt (int *, int *, int *, complex **, int **, int **);

SUPERLU_EXPORT
extern void    cGenXtrue (int, int, complex *, int);

SUPERLU_EXPORT
extern void    cFillRHS (trans_t, int, complex *, int, SuperMatrix *,
			  SuperMatrix *);

SUPERLU_EXPORT
extern void    cgstrs (trans_t, SuperMatrix *, SuperMatrix *, int *, int *,
                        SuperMatrix *, SuperLUStat_t*, int *);
/* ILU */
SUPERLU_EXPORT
extern void    cgsitrf (superlu_options_t*, SuperMatrix*, int, int, int*,
		        void *, int, int *, int *, SuperMatrix *, SuperMatrix *,
                        GlobalLU_t *, SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern int     cldperm(int, int, int, int [], int [], complex [],
                        int [],	float [], float []);

SUPERLU_EXPORT
extern int     ilu_csnode_dfs (const int, const int, const int *, const int *,
			       const int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern void    ilu_cpanel_dfs (const int, const int, const int, SuperMatrix *,
			       int *, int *, complex *, float *, int *, int *,
			       int *, int *, int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     ilu_ccolumn_dfs (const int, const int, int *, int *, int *,
				int *, int *, int *, int *, int *,
				GlobalLU_t *);

SUPERLU_EXPORT
extern int     ilu_ccopy_to_ucol (int, int, int *, int *, int *,
                                  complex *, int, milu_t, double, int,
                                  complex *, int *, GlobalLU_t *, float *);

SUPERLU_EXPORT
extern int     ilu_cpivotL (const int, const double, int *, int *, int, int *,
			    int *, int *, int *, double, milu_t,
                            complex, GlobalLU_t *, SuperLUStat_t*);

SUPERLU_EXPORT
extern int     ilu_cdrop_row (superlu_options_t *, int, int, double,
                              int, int *, double *, GlobalLU_t *, 
                              float *, float *, int);


/*! \brief Driver related */

extern void    cgsequ (SuperMatrix *, float *, float *, float *,
			float *, float *, int *);

SUPERLU_EXPORT
extern void    claqgs (SuperMatrix *, float *, float *, float,
                        float, float, char *);

SUPERLU_EXPORT
extern void    cgscon (char *, SuperMatrix *, SuperMatrix *, 
		         float, float *, SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern float   cPivotGrowth(int, SuperMatrix *, int *, 
                            SuperMatrix *, SuperMatrix *);

SUPERLU_EXPORT
extern void    cgsrfs (trans_t, SuperMatrix *, SuperMatrix *,
                       SuperMatrix *, int *, int *, char *, float *, 
                       float *, SuperMatrix *, SuperMatrix *,
                       float *, float *, SuperLUStat_t*, int *);


SUPERLU_EXPORT
extern int     sp_ctrsv (char *, char *, char *, SuperMatrix *,
			SuperMatrix *, complex *, SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern int     sp_cgemv (char *, complex, SuperMatrix *, complex *,
			int, complex, complex *, int);

SUPERLU_EXPORT
extern int     sp_cgemm (char *, char *, int, int, int, complex,
			SuperMatrix *, complex *, int, complex, 
			complex *, int);

SUPERLU_EXPORT
extern         float smach(char *);   /* from C99 standard, in float.h */

/*! \brief Memory-related */

SUPERLU_EXPORT
extern int     cLUMemInit (fact_t, void *, int, int, int, int, int,
                            float, SuperMatrix *, SuperMatrix *,
                            GlobalLU_t *, int **, complex **);

SUPERLU_EXPORT
extern void    cSetRWork (int, int, complex *, complex **, complex **);

SUPERLU_EXPORT
extern void    cLUWorkFree (int *, complex *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     cLUMemXpand (int, int, MemType, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern complex  *complexMalloc(int);

SUPERLU_EXPORT
extern complex  *complexCalloc(int);

SUPERLU_EXPORT
extern float  *floatMalloc(int);

SUPERLU_EXPORT
extern float  *floatCalloc(int);

SUPERLU_EXPORT
extern int     cmemory_usage(const int, const int, const int, const int);

SUPERLU_EXPORT
extern int     cQuerySpace (SuperMatrix *, SuperMatrix *, mem_usage_t *);

SUPERLU_EXPORT
extern int     ilu_cQuerySpace (SuperMatrix *, SuperMatrix *, mem_usage_t *);

/*! \brief Auxiliary routines */

SUPERLU_EXPORT
extern void    creadhb(FILE *, int *, int *, int *, complex **, int **, int **);

SUPERLU_EXPORT
extern void    creadrb(int *, int *, int *, complex **, int **, int **);

SUPERLU_EXPORT
extern void    creadtriple(int *, int *, int *, complex **, int **, int **);

SUPERLU_EXPORT
extern void    creadMM(FILE *, int *, int *, int *, complex **, int **, int **);

SUPERLU_EXPORT
extern void    cCompRow_to_CompCol(int, int, int, complex*, int*, int*,
		                   complex **, int **, int **);

SUPERLU_EXPORT
extern void    cfill (complex *, int, complex);

SUPERLU_EXPORT
extern void    cinf_norm_error (int, SuperMatrix *, complex *);

SUPERLU_EXPORT
extern float  sqselect(int, float *, int);


/*! \brief Routines for debugging */

SUPERLU_EXPORT
extern void    cPrint_CompCol_Matrix(char *, SuperMatrix *);

SUPERLU_EXPORT
extern void    cPrint_SuperNode_Matrix(char *, SuperMatrix *);

SUPERLU_EXPORT
extern void    cPrint_Dense_Matrix(char *, SuperMatrix *);

SUPERLU_EXPORT
extern void    cprint_lu_col(char *, int, int, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     print_double_vec(char *, int, double *);

SUPERLU_EXPORT
extern void    ccheck_tempv(int, complex *);

/*! \brief BLAS */


SUPERLU_EXPORT
extern int cgemm_(const char*, const char*, const int*, const int*, const int*,
                  const complex*, const complex*, const int*, const complex*,
		  const int*, const complex*, complex*, const int*);

SUPERLU_EXPORT
extern int ctrsv_(char*, char*, char*, int*, complex*, int*,
                  complex*, int*);

SUPERLU_EXPORT
extern int ctrsm_(char*, char*, char*, char*, int*, int*,
                  complex*, complex*, int*, complex*, int*);

SUPERLU_EXPORT
extern int cgemv_(char *, int *, int *, complex *, complex *a, int *,
                  complex *, int *, complex *, complex *, int *);

#ifdef __cplusplus
  }
#endif

#endif /* __SUPERLU_cSP_DEFS */

