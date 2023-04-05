/*! \file
Copyright (c) 2003, The Regents of the University of California, through
Lawrence Berkeley National Laboratory (subject to receipt of any required 
approvals from U.S. Dept. of Energy) 

All rights reserved. 

The source code is distributed under BSD license, see the file License.txt
at the top-level directory.
*/

/*! @file slu_zdefs.h
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
#ifndef __SUPERLU_zSP_DEFS /* allow multiple inclusions */
#define __SUPERLU_zSP_DEFS

/*
 * File name:		zsp_defs.h
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
#include "slu_dcomplex.h"


/* -------- Prototypes -------- */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Driver routines */

SUPERLU_EXPORT
extern void
zgssv(superlu_options_t *, SuperMatrix *, int *, int *, SuperMatrix *,
      SuperMatrix *, SuperMatrix *, SuperLUStat_t *, int *);

SUPERLU_EXPORT
extern void
zgssvx(superlu_options_t *, SuperMatrix *, int *, int *, int *,
       char *, double *, double *, SuperMatrix *, SuperMatrix *,
       void *, int, SuperMatrix *, SuperMatrix *,
       double *, double *, double *, double *,
       GlobalLU_t *, mem_usage_t *, SuperLUStat_t *, int *);
    /* ILU */

SUPERLU_EXPORT
extern void
zgsisv(superlu_options_t *, SuperMatrix *, int *, int *, SuperMatrix *,
      SuperMatrix *, SuperMatrix *, SuperLUStat_t *, int *);

SUPERLU_EXPORT
extern void
zgsisx(superlu_options_t *, SuperMatrix *, int *, int *, int *,
       char *, double *, double *, SuperMatrix *, SuperMatrix *,
       void *, int, SuperMatrix *, SuperMatrix *, double *, double *,
       GlobalLU_t *, mem_usage_t *, SuperLUStat_t *, int *);


/*! \brief Supernodal LU factor related */
SUPERLU_EXPORT
extern void
zCreate_CompCol_Matrix(SuperMatrix *, int, int, int, doublecomplex *,
		       int *, int *, Stype_t, Dtype_t, Mtype_t);

SUPERLU_EXPORT
extern void
zCreate_CompRow_Matrix(SuperMatrix *, int, int, int, doublecomplex *,
		       int *, int *, Stype_t, Dtype_t, Mtype_t);
SUPERLU_EXPORT
extern void
zCopy_CompCol_Matrix(SuperMatrix *, SuperMatrix *);

SUPERLU_EXPORT
extern void
zCreate_Dense_Matrix(SuperMatrix *, int, int, doublecomplex *, int,
		     Stype_t, Dtype_t, Mtype_t);

SUPERLU_EXPORT
extern void
zCreate_SuperNode_Matrix(SuperMatrix *, int, int, int, doublecomplex *, 
		         int *, int *, int *, int *, int *,
			 Stype_t, Dtype_t, Mtype_t);

SUPERLU_EXPORT
extern void
zCopy_Dense_Matrix(int, int, doublecomplex *, int, doublecomplex *, int);

SUPERLU_EXPORT
extern void    countnz (const int, int *, int *, int *, GlobalLU_t *);
SUPERLU_EXPORT
extern void    ilu_countnz (const int, int *, int *, GlobalLU_t *);
SUPERLU_EXPORT
extern void    fixupL (const int, const int *, GlobalLU_t *);

SUPERLU_EXPORT
extern void    zallocateA (int, int, doublecomplex **, int **, int **);
SUPERLU_EXPORT
extern void    zgstrf (superlu_options_t*, SuperMatrix*,
                       int, int, int*, void *, int, int *, int *, 
                       SuperMatrix *, SuperMatrix *, GlobalLU_t *,
		       SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern int     zsnode_dfs (const int, const int, const int *, const int *,
			     const int *, int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     zsnode_bmod (const int, const int, const int, doublecomplex *,
                              doublecomplex *, GlobalLU_t *, SuperLUStat_t*);

SUPERLU_EXPORT
extern void    zpanel_dfs (const int, const int, const int, SuperMatrix *,
			   int *, int *, doublecomplex *, int *, int *, int *,
			   int *, int *, int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern void    zpanel_bmod (const int, const int, const int, const int,
                           doublecomplex *, doublecomplex *, int *, int *,
			   GlobalLU_t *, SuperLUStat_t*);

SUPERLU_EXPORT
extern int     zcolumn_dfs (const int, const int, int *, int *, int *, int *,
			   int *, int *, int *, int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     zcolumn_bmod (const int, const int, doublecomplex *,
			   doublecomplex *, int *, int *, int,
                           GlobalLU_t *, SuperLUStat_t*);

SUPERLU_EXPORT
extern int     zcopy_to_ucol (int, int, int *, int *, int *,
                              doublecomplex *, GlobalLU_t *);         

SUPERLU_EXPORT
extern int     zpivotL (const int, const double, int *, int *, 
                         int *, int *, int *, GlobalLU_t *, SuperLUStat_t*);

SUPERLU_EXPORT
extern void    zpruneL (const int, const int *, const int, const int,
			  const int *, const int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern void    zreadmt (int *, int *, int *, doublecomplex **, int **, int **);

SUPERLU_EXPORT
extern void    zGenXtrue (int, int, doublecomplex *, int);

SUPERLU_EXPORT
extern void    zFillRHS (trans_t, int, doublecomplex *, int, SuperMatrix *,
			  SuperMatrix *);

SUPERLU_EXPORT
extern void    zgstrs (trans_t, SuperMatrix *, SuperMatrix *, int *, int *,
                        SuperMatrix *, SuperLUStat_t*, int *);
/* ILU */

SUPERLU_EXPORT
extern void    zgsitrf (superlu_options_t*, SuperMatrix*, int, int, int*,
		        void *, int, int *, int *, SuperMatrix *, SuperMatrix *,
                        GlobalLU_t *, SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern int     zldperm(int, int, int, int [], int [], doublecomplex [],
                        int [],	double [], double []);

SUPERLU_EXPORT
extern int     ilu_zsnode_dfs (const int, const int, const int *, const int *,
			       const int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern void    ilu_zpanel_dfs (const int, const int, const int, SuperMatrix *,
			       int *, int *, doublecomplex *, double *, int *, int *,
			       int *, int *, int *, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     ilu_zcolumn_dfs (const int, const int, int *, int *, int *,
				int *, int *, int *, int *, int *,
				GlobalLU_t *);

SUPERLU_EXPORT
extern int     ilu_zcopy_to_ucol (int, int, int *, int *, int *,
                                  doublecomplex *, int, milu_t, double, int,
                                  doublecomplex *, int *, GlobalLU_t *, double *);

SUPERLU_EXPORT
extern int     ilu_zpivotL (const int, const double, int *, int *, int, int *,
			    int *, int *, int *, double, milu_t,
                            doublecomplex, GlobalLU_t *, SuperLUStat_t*);

SUPERLU_EXPORT
extern int     ilu_zdrop_row (superlu_options_t *, int, int, double,
                              int, int *, double *, GlobalLU_t *, 
                              double *, double *, int);


/*! \brief Driver related */

SUPERLU_EXPORT
extern void    zgsequ (SuperMatrix *, double *, double *, double *,
			double *, double *, int *);

SUPERLU_EXPORT
extern void    zlaqgs (SuperMatrix *, double *, double *, double,
                        double, double, char *);

SUPERLU_EXPORT
extern void    zgscon (char *, SuperMatrix *, SuperMatrix *, 
		         double, double *, SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern double   zPivotGrowth(int, SuperMatrix *, int *, 
                            SuperMatrix *, SuperMatrix *);

SUPERLU_EXPORT
extern void    zgsrfs (trans_t, SuperMatrix *, SuperMatrix *,
                       SuperMatrix *, int *, int *, char *, double *, 
                       double *, SuperMatrix *, SuperMatrix *,
                       double *, double *, SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern int     sp_ztrsv (char *, char *, char *, SuperMatrix *,
			SuperMatrix *, doublecomplex *, SuperLUStat_t*, int *);

SUPERLU_EXPORT
extern int     sp_zgemv (char *, doublecomplex, SuperMatrix *, doublecomplex *,
			int, doublecomplex, doublecomplex *, int);

SUPERLU_EXPORT
extern int     sp_zgemm (char *, char *, int, int, int, doublecomplex,
			SuperMatrix *, doublecomplex *, int, doublecomplex, 
			doublecomplex *, int);

SUPERLU_EXPORT
extern         double dmach(char *);   /* from C99 standard, in float.h */

/*! \brief Memory-related */

SUPERLU_EXPORT
extern int     zLUMemInit (fact_t, void *, int, int, int, int, int,
                            double, SuperMatrix *, SuperMatrix *,
                            GlobalLU_t *, int **, doublecomplex **);

SUPERLU_EXPORT
extern void    zSetRWork (int, int, doublecomplex *, doublecomplex **, doublecomplex **);

SUPERLU_EXPORT
extern void    zLUWorkFree (int *, doublecomplex *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     zLUMemXpand (int, int, MemType, int *, GlobalLU_t *);


SUPERLU_EXPORT
extern doublecomplex  *doublecomplexMalloc(int);

SUPERLU_EXPORT
extern doublecomplex  *doublecomplexCalloc(int);

SUPERLU_EXPORT
extern double  *doubleMalloc(int);

SUPERLU_EXPORT
extern double  *doubleCalloc(int);

SUPERLU_EXPORT
extern int     zmemory_usage(const int, const int, const int, const int);

SUPERLU_EXPORT
extern int     zQuerySpace (SuperMatrix *, SuperMatrix *, mem_usage_t *);

SUPERLU_EXPORT
extern int     ilu_zQuerySpace (SuperMatrix *, SuperMatrix *, mem_usage_t *);

/*! \brief Auxiliary routines */

SUPERLU_EXPORT
extern void    zreadhb(FILE *, int *, int *, int *, doublecomplex **, int **, int **);

SUPERLU_EXPORT
extern void    zreadrb(int *, int *, int *, doublecomplex **, int **, int **);

SUPERLU_EXPORT
extern void    zreadtriple(int *, int *, int *, doublecomplex **, int **, int **);

SUPERLU_EXPORT
extern void    zreadMM(FILE *, int *, int *, int *, doublecomplex **, int **, int **);

SUPERLU_EXPORT
extern void    zCompRow_to_CompCol(int, int, int, doublecomplex*, int*, int*,
		                   doublecomplex **, int **, int **);

SUPERLU_EXPORT
extern void    zfill (doublecomplex *, int, doublecomplex);

SUPERLU_EXPORT
extern void    zinf_norm_error (int, SuperMatrix *, doublecomplex *);

SUPERLU_EXPORT
extern double  dqselect(int, double *, int);


/*! \brief Routines for debugging */

SUPERLU_EXPORT
extern void    zPrint_CompCol_Matrix(char *, SuperMatrix *);

SUPERLU_EXPORT
extern void    zPrint_SuperNode_Matrix(char *, SuperMatrix *);

SUPERLU_EXPORT
extern void    zPrint_Dense_Matrix(char *, SuperMatrix *);

SUPERLU_EXPORT
extern void    zprint_lu_col(char *, int, int, int *, GlobalLU_t *);

SUPERLU_EXPORT
extern int     print_double_vec(char *, int, double *);

SUPERLU_EXPORT
extern void    zcheck_tempv(int, doublecomplex *);

/*! \brief BLAS */

SUPERLU_EXPORT
extern int zgemm_(const char*, const char*, const int*, const int*, const int*,
                  const doublecomplex*, const doublecomplex*, const int*, const doublecomplex*,
		  const int*, const doublecomplex*, doublecomplex*, const int*);

SUPERLU_EXPORT
extern int ztrsv_(char*, char*, char*, int*, doublecomplex*, int*,
                  doublecomplex*, int*);

SUPERLU_EXPORT
extern int ztrsm_(char*, char*, char*, char*, int*, int*,
                  doublecomplex*, doublecomplex*, int*, doublecomplex*, int*);

SUPERLU_EXPORT
extern int zgemv_(char *, int *, int *, doublecomplex *, doublecomplex *a, int *,
                  doublecomplex *, int *, doublecomplex *, doublecomplex *, int *);

#ifdef __cplusplus
  }
#endif

#endif /* __SUPERLU_zSP_DEFS */

