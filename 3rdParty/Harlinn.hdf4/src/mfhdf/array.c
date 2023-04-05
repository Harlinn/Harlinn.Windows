/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 1993, University Corporation for Atmospheric Research             *
 * See netcdf/COPYRIGHT file for copying and redistribution conditions.      *
 *                                                                           *
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

/*    $Id$ */

#include    <string.h>
#include    "local_nc.h"
#include    "alloc.h"

#ifdef NO_MEM_FUNCTS
/*
 * internal replacement for memset
 */
char *
NCmemset (s, c, n)
     char *s;
     int c, n;
{

  char *cp ;

  for (cp = s ; cp < &s[n] ; *cp++ = c )
    /* nada */ ;

  return s ;

}
#endif

/*
 * for a netcdf type
 *  return the size of the on-disk representation
 */
int
NC_xtypelen(type)
nc_type    type ;
{
    char *nada = NULL ;

    switch(type){
    case NC_BYTE :
    case NC_CHAR :
        return(NC_CHAR_SIZE);
    case NC_SHORT :
        return(NC_SHORT_SIZE);
    case NC_LONG :
    case NC_FLOAT :
        return(NC_LONG_SIZE);
    case NC_DOUBLE :
        return(NC_DOUBLE_SIZE);
/* private types */
    case NC_UNSPECIFIED :
        return(NC_UNSPECIFIED_SIZE);
    case NC_STRING :
        return(NC_xlen_string((NC_string *)NULL)) ;
    case NC_DIMENSION :
        return(NC_xlen_dim((NC_dim **)&nada)) ;
    case NC_VARIABLE :
        return(NC_xlen_var((NC_var **)&nada)) ;
    case NC_ATTRIBUTE :
        return(NC_xlen_attr((NC_attr **)&nada)) ;
    default :
        NCadvise(NC_EBADTYPE, "NC_xtypelen: Unknown type %d", type) ;
        return(-1) ;
    }
}


/*
 *  private version of nctypelen
 */
size_t
NC_typelen(type)
nc_type    type ;
{
    switch(type){
    case NC_BYTE :
    case NC_CHAR :
        return(sizeof(char)) ;
    case NC_SHORT :
        return(sizeof(short)) ;
    case NC_LONG :
        return(sizeof(nclong)) ;
    case NC_FLOAT :
        return(sizeof(float)) ;
    case NC_DOUBLE :
        return(sizeof(double)) ;
/* private types */
    case NC_STRING :
        return(sizeof(NC_string *)) ;
    case NC_DIMENSION :
        return(sizeof(NC_dim *)) ;
    case NC_VARIABLE :
        return(sizeof(NC_var *)) ;
    case NC_ATTRIBUTE :
        return(sizeof(NC_attr *)) ;
    default :
        return(0) ;
    }
}

/*
 * external interface function
 *  this is how much space is required by the user, as in
 *
 *   vals = malloc(nel * nctypelen(var.type));
 *   ncvarget (cdfid, varid, cor, edg, vals);
 *
 */
int
nctypelen(type)
nc_type    type ;
{
    switch(type){
    case NC_BYTE :
    case NC_CHAR :
        return(sizeof(char)) ;
    case NC_SHORT :
        return(sizeof(short)) ;
    case NC_LONG :
        return(sizeof(nclong)) ;
    case NC_FLOAT :
        return(sizeof(float)) ;
    case NC_DOUBLE :
        return(sizeof(double)) ;
    default :
        NCadvise(NC_EBADTYPE, "Unknown type %d", type) ;
        return(-1) ;
    }
}

/* See netcdf.h for explanation of these initialzations */
/* assert( !(USE_F_UNION && USE_F_LONG_PUN) ) ; */
/* assert( !(USE_D_UNION && USE_D_LONG_PUN) ) ; */

#ifdef USE_F_UNION
#ifdef H4_WORDS_BIGENDIAN
union xdr_f_union xdr_f_infs = {0x7f, 0x80, 0x00, 0x00} ;
#else
union xdr_f_union xdr_f_infs = {0x00, 0x00, 0x80, 0x7f} ;
#endif /* H4_WORDS_BIGENDIAN */
#endif /* USE_F_UNION */

#ifdef USE_D_UNION
#ifdef H4_WORDS_BIGENDIAN
union xdr_d_union xdr_d_infs = {0x7f, 0xf0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00} ;
#else
union xdr_d_union xdr_d_infs = {0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0x7f} ;
#endif /* H4_WORDS_BIGENDIAN */
#endif /* USE_D_UNION */

#ifdef USE_F_LONG_PUN
nclong xdr_f_infinity = 0x7f800000;
#endif

#ifdef USE_D_LONG_PUN
#ifdef H4_WORDS_BIGENDIAN
nclong xdr_d_infinity[2] = {0x7ff00000,0x00000000};
#else
nclong xdr_d_infinity[2] = {0x00000000,0x7ff00000};
#endif /* H4_WORDS_BIGENDIAN */
#endif /* USE_D_LONG_PUN */

/*
 *    Fill an array region with an appropriate special value
 */
void
NC_arrayfill(low, len, type)
void *low ;    /* lower bound of area to be filled */
size_t len ;    /* how many bytes */
nc_type type ;
{
    char *hi, *lo;    /* local low and hi ptr */

    lo = low;
        hi = lo + len;
    switch(type) {
    case NC_BYTE :
                HDmemset(lo, FILL_BYTE, len);
        break ;
    case NC_CHAR :
                HDmemset(lo, FILL_CHAR, len);
        break ;
    case NC_SHORT :
        while(lo < hi ){
            *((short *)lo) = FILL_SHORT ;
            lo += sizeof(short);
        }
        break ;
    case NC_LONG :
        while(lo < hi ){
            *((nclong *)lo) = FILL_LONG ;
            lo += sizeof(nclong) ;
        }
        break ;
    case NC_FLOAT :
        while(lo < hi ){
            *((float *)lo) = FILL_FLOAT ;
            lo += sizeof(float) ;
        }
        break ;
    case NC_DOUBLE :
        while(lo < hi ){
            /*SUPPRESS 450*/
            *((double *)lo) = FILL_DOUBLE ;
            lo += sizeof(double) ;
        }
        break ;
    default :
        HDmemset(lo,0xff,len) ;
        break ;
    }
}


/*
 * Allocate a new array, returning a handle to it, NULL on error.
 * If count is no-zero, allocate private space for the values, and,
 * if values is non-NULL, copy them in.
 * Else, just hook up the values passed in.
 */
NC_array *
NC_new_array(type, count, values)
nc_type type ;
unsigned count ;
const void *values ;
{
    NC_array *ret ;
    size_t memlen ;

    ret = (NC_array *)HDmalloc(sizeof(NC_array)) ;
    if( ret == NULL )
        goto alloc_err ;

    ret->type = type ;
    ret->szof = NC_typelen(type) ;
#ifdef SDDEBUG
  fprintf(stderr, "NC_new_array(): type=%u, NC_typelen(type)=%u\n",(unsigned)type,(unsigned)ret->szof);
#endif
    ret->count = count ;
    memlen = count * ret->szof ;
    ret->len = count * NC_xtypelen(type) ;
#ifdef SDDEBUG
  fprintf(stderr, "NC_new_array(): count=%u, memlen=%u\n",count,memlen);
#endif
    if( count != 0 )
    {
        ret->values = (Void*)HDmalloc(memlen) ;
#ifdef SDDEBUG
  fprintf(stderr, "NC_new_array(): ret->values=%p, values=%p\n",ret->values,values);
#endif
        if(ret->values == NULL)
            goto alloc_err ;
        if( values == NULL )
        {
            NC_arrayfill(ret->values, memlen, type) ;
        } else {
            /* can be dangerous */
            (void)memcpy(ret->values, values, memlen) ;
        }
    } else {
        ret->values = NULL ;
    }

#ifdef SDDEBUG
  fprintf(stderr, "NC_new_array(): ret=%p\n",ret);
#endif
    return(ret) ;
alloc_err :
    nc_serror("NC_new_array") ;
    return(NULL) ;
}


/*
 * Recyle a NC_array, if possible.
 * EG, if there is enough space, use it, else return NULL
 * If values is non-NULL, copy them in.
 */
NC_array *
NC_re_array(old, type, count, values)
NC_array *old ;
nc_type type ;
unsigned count ;
const void *values ;
{
    size_t memlen ;
    size_t szof ;

    szof = NC_typelen(type) ;
    memlen = count * szof ;
    if(memlen > old->count * old->szof )
        return(NULL) ; /* punt */
    old->count = count ;
    old->type = type ;
    old->szof = szof ;
    if(count != 0)
    {
        if( values == NULL )
        {
            NC_arrayfill(old->values, memlen, type) ;
        } else {
            /* can be dangerous */
            (void)memcpy(old->values, values, memlen) ;
        }
    }

    return(old) ;
}


/*
 * Free array, and, if needed, its values.
 *
 * NOTE: Changed return value to return 'int'
 *       If successful returns SUCCEED else FAIL -GV 9/19/97
 */
int
NC_free_array(array)
NC_array *array ;
{
    int ret_value = SUCCEED;

    if( array != NULL)
      {
          if(array->values != NULL)
            {
                switch(array->type)
                  {
                  case NC_UNSPECIFIED :
                  case NC_BYTE :
                  case NC_CHAR :
                  case NC_SHORT :
                  case NC_LONG :
                  case NC_FLOAT :
                  case NC_DOUBLE :
                      break ;
                  case NC_STRING  :
                  {
                      NC_string **sp ;
                      sp = (NC_string **)array->values ;
                      for(sp += array->count - 1 ;
                          array->count > 0;
                          array->count--)
                        {
                            if (FAIL == NC_free_string(*sp-- ))
                              {
                                  ret_value = FAIL;
                                  goto done;
                              }

                        }
                  }
                  break ;
                  case NC_DIMENSION :
                  {
                      NC_dim **dp ;
                      dp = (NC_dim**)array->values ;
                      for(dp += array->count - 1 ;
                          array->count > 0;
                          array->count--)
                        {
                            if (FAIL == NC_free_dim(*dp-- ))
                              {
                                  ret_value = FAIL;
                                  goto done;
                              }

                        }
                  }
                  break ;
                  case NC_VARIABLE :
                  {
                      NC_var **dp ;
                      dp = (NC_var**)array->values ;
                      for(dp += array->count - 1 ;
                          array->count > 0;
                          array->count--)
                        {
                            if (FAIL == NC_free_var(*dp-- ))
                              {
                                  ret_value = FAIL;
                                  goto done;
                              }
                        }
                  }
                  break ;
                  case NC_ATTRIBUTE :
                  {
                      NC_attr **dp ;
                      dp = (NC_attr**)array->values ;
                      for(dp += array->count - 1 ;
                          array->count > 0;
                          array->count--)
                        {
                            if (FAIL == NC_free_attr(*dp-- ))
                              {
                                  ret_value = FAIL;
                                  goto done;
                              }
                        }
                  }
                  break ;
                  default:
                      NCadvise(NC_EBADTYPE, "Unknown type %d",array->type) ;
                      break ;
                  }

                Free(array->values) ;
            }

          Free(array) ;
      }


done:
    if (ret_value == FAIL)
      { /* Failure cleanup */

      }
     /* Normal cleanup */

    return ret_value;
}


/*
 * How much space will the xdr'd array take.
 */
int NC_xlen_array(array)
NC_array *array ;
{
    int len = 8 ;
    int rem ;
    int (*xlen_funct)() =NULL;
    Void *vp ;
    unsigned ii ;

    if(array!=NULL)
    {
        switch(array->type){
        case NC_BYTE :
        case NC_CHAR :
            len += array->count * NC_CHAR_SIZE;
            if( (rem = len%4) != 0)
                len += 4 - rem ;
            return(len) ;
        case NC_SHORT :
            len += array->count * NC_SHORT_SIZE;
            if( (rem = len%4) != 0)
                len += 4 - rem ;
            return(len) ;
        case NC_LONG :
        case NC_FLOAT :
            len += array->count * NC_LONG_SIZE;
            return(len) ;
        case NC_DOUBLE :
            len += array->count * NC_DOUBLE_SIZE;
            return(len) ;
        case NC_STRING  :
            xlen_funct = NC_xlen_string ;
            break ;
        case NC_DIMENSION :
            xlen_funct = NC_xlen_dim ;
            break ;
        case NC_VARIABLE :
            xlen_funct = NC_xlen_var ;
            break ;
        case NC_ATTRIBUTE :
            xlen_funct = NC_xlen_attr ;
            break ;
        default:
            break;
        }
        vp = array->values ;
        for(ii=0 ; ii < array->count ; ii++)
        {
            len += (*xlen_funct)(vp) ;
            vp += array->szof ;
        }
    }
    return(len) ;
}


/*
 * Add a new handle on the end of and array of handles
 */
Void *
NC_incr_array(array, tail)
NC_array *array ;
Void *tail ;
{
    char *ap ;

    if(array == NULL)
    {
        NCadvise(NC_EINVAL, "increment: NULL array") ;
        return(NULL) ;
    }

    array->values = (Void*)HDrealloc(array->values,
        (array->count +1) * array->szof) ;
    if(array->values == NULL)
    {
        nc_serror("extend_array") ;
        return(NULL) ;
    }
    ap = array->values + array->szof * array->count ;
    (void)memcpy(ap, tail, array->szof) ;
    array->count ++ ;
    return(array->values) ;
}


/*
 * Definitely NOT Bomb proof.
 */
void
NC_copy_arrayvals( target, array )
char *target ;
NC_array *array ;
{
    size_t memlen ;

    memlen = array->szof * array->count ;
    (void)memcpy(target, array->values, memlen) ;
}


bool_t
xdr_NC_array(xdrs, app)
    XDR *xdrs;
    NC_array **app;
{
    bool_t (*xdr_NC_fnct)() ;
    u_long count = 0, *countp=NULL ;
    nc_type type = NC_UNSPECIFIED, *typep=NULL ;
    bool_t stat ;
    Void *vp = NULL;

    switch (xdrs->x_op) {
    case XDR_FREE:
        NC_free_array((*app)) ;
        return(TRUE) ;
    case XDR_ENCODE:
        if(*app == NULL)
        {
            (*app) = NC_new_array(NC_UNSPECIFIED, (unsigned)0,
                (Void*)NULL) ;
            if(*app == NULL)
            {
                NCadvise(NC_EXDR, "xdr_NC_array:NC_new_array") ;
                return(FALSE) ;
            }
        }
        count = (*app)->count ;
        type = (*app)->type ;
        /* fall into */
    case XDR_DECODE:
        countp = &count ;
        typep = &type ;
        break ;
    }

    /* This USE_ENUM may not be necessary after xdr and code cleanup.
    See HDFFR-1318, HDFFR-1327, and other Mac/XDR issues for details.
       -BMR, 6/14/2016 */
#ifdef USE_ENUM
    if (! xdr_enum(xdrs, (enum_t *)typep)) {
        NCadvise(NC_EXDR, "xdr_NC_array:xdr_enum") ;
        return (FALSE);
    }
#else
    if (! xdr_int(xdrs, typep)) {
            NCadvise(NC_EXDR, "xdr_NC_array:xdr_int (enum)") ;
            return (FALSE);
        }

#endif
    {
        u_long temp_count = 0;
        if (! xdr_u_long(xdrs, &temp_count)) {
            NCadvise(NC_EXDR, "xdr_NC_array:xdr_u_long") ;
            return (FALSE);
        }
        *countp = temp_count;
    }

    if( xdrs->x_op == XDR_DECODE )
    {
        if( *typep == NC_UNSPECIFIED && *countp == 0 )
        {
            *app = NULL ;
            return(TRUE) ;
        } /* else */
        (*app) = NC_new_array(*typep, (unsigned)*countp, (Void*)NULL) ;
        if((*app) == NULL)
        {
            NCadvise(NC_EXDR, "xdr_NC_array:NC_new_array  (second call)") ;
            return(FALSE) ;
        }
    }

    vp = (*app)->values ;

    switch(*typep){
    case NC_UNSPECIFIED :
    case NC_BYTE :
    case NC_CHAR :
        xdr_NC_fnct = xdr_opaque ;
        goto func ;
    case NC_SHORT :
        xdr_NC_fnct = xdr_shorts ;
        goto func ;
    case NC_LONG :
        xdr_NC_fnct = xdr_int ;
        goto loop ;
    case NC_FLOAT :
        xdr_NC_fnct = xdr_float ;
        goto loop ;
    case NC_DOUBLE :
        xdr_NC_fnct = xdr_double ;
        goto loop ;
/* private types */
    case NC_STRING :
        xdr_NC_fnct = xdr_NC_string ;
        goto loop ;
    case NC_DIMENSION :
        xdr_NC_fnct = xdr_NC_dim ;
        goto loop ;
    case NC_VARIABLE :
        xdr_NC_fnct = xdr_NC_var ;
        goto loop ;
    case NC_ATTRIBUTE :
        xdr_NC_fnct = xdr_NC_attr ;
        goto loop ;
    default :
        {
        NCadvise(NC_EBADTYPE, "xdr_NC_array: unknown type 0x%x", (unsigned)*typep) ;
        return(FALSE) ;
        }
    }
loop:
    for(stat = TRUE ; stat && (count > 0) ; count--)
    {
        stat = (*xdr_NC_fnct)(xdrs,vp) ;
        vp += (*app)->szof ;
    }
    if ( !stat ) NCadvise(NC_EXDR, "xdr_NC_array: loop") ;

    return(stat) ;
func:

    stat = (*xdr_NC_fnct)(xdrs, vp, *countp);
    if ( !stat ) NCadvise(NC_EXDR, "xdr_NC_array: func") ;
    return( stat );
}
