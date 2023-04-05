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

/***************************************************************************
 *
 * This file contains the code to read old SDS objects out of HDF files
 *  an pretend that they are netCDF / mutli-file SDS data objects
 *
 **************************************************************************/

/***************************************************************************
  General Thoughts


  Will need to add a 'type' field to the variable stucture so that we can
  how it was stored (basically will want to just store the tag of the object
  as well as the ref (which is already stored)).
  

  We can use the LUF record to get names of dimensions.  If no info stored
  int the LUF then we will need to fake it.

  Will prolly be easiest to define a coordinate variable for every dimension 
  even if it doesn't need any attributes or data values

  Scales are a problem.  In HDF scales, are used to define the values for
  the coordinate variables.  The problem is that all of the values for the
  scales in HDF are jammed into the same tag's storage.  So, we will need
  to add an 'offset' field to the variable record so that we know where to 
  start reading to get the data.  If the offset == 0 then we should start
  reading from the beginning.  If the offset == -1 then there is *NO* data
  (since a scale may not have data specified for it).

 LOCAL ROUTINES
 ==============
 hdf_query_seen_sdg
 hdf_register_seen_sdg
 hdf_read_ndgs
 hdf_check_nt

 These functions were added in 2.13, Jun, 2017 as a result of refactoring
 hdf_read_ndgs.
 hdf_read_rank
 hdf_read_dimsizes
 hdf_read_NT
 hdf_get_sdc
 hdf_get_pred_str_attr
 hdf_get_desc_annot
 hdf_get_label_annot
 hdf_luf_to_attrs
 hdf_get_rangeinfo
 hdf_get_cal


 PUBLIC ROUTINES
 ===============
 hdf_read_sds_ndgs


 NOTE: This file could use the current comments updated and more
       comments in parts of the code. I tried my best. -GV 9/10/97

 **************************************************************************/

#ifdef HDF
#include        "local_nc.h"

#define SDG_MAX_INITIAL 100

/* local variables */
PRIVATE intn       sdgCurrent;
PRIVATE intn       sdgMax;
PRIVATE uint16     *sdgTable=NULL;
PRIVATE uint8      *ptbuf = NULL;

/* Local routines */
PRIVATE intn hdf_query_seen_sdg
    (uint16 ndgRef);

PRIVATE intn hdf_register_seen_sdg
    (uint16 ndgRef);

PRIVATE intn hdf_read_ndgs
    (NC *handle);

/******************************************************************************
 NAME
   hdf_query_seen_sdg

 DESCRIPTION
   The SDG with the given ref number might be part of an SDG-NDG combo
   if so, we return TRUE else FALSE.
 
   Attempt to discover if we've seen it in the most inefficient manner
   possible

 RETURNS
   TRUE / FALSE

******************************************************************************/
PRIVATE intn 
hdf_query_seen_sdg(uint16 ndgRef)
{
    intn i;

    if(!sdgTable) 
        return FALSE;

    for(i = 0; i < sdgCurrent; i++)
      {
        if(sdgTable[i] == ndgRef) 
            return TRUE;
      }

    return FALSE;
} /* hdf_query_seen_sdg */


/******************************************************************************
 NAME
   hdf_register_seen_sdg

 DESCRIPTION
   The SDG with the given ref is in an SDG-NDG combo.  Add it to the seen table
   so we don't read it twice

 RETURNS
   SUCCEED / FAIL

******************************************************************************/
PRIVATE intn 
hdf_register_seen_sdg(uint16 sdgRef)
{
    CONSTR(FUNC, "hdf_register_seen_sdg");        /* for HERROR */
    intn ret_value = SUCCEED;

    /* check if table is allocated */
    if(!sdgTable) 
      {
          sdgMax = SDG_MAX_INITIAL;
          sdgTable = (uint16 *) HDmalloc(sdgMax * sizeof(uint16));
          if (sdgTable == NULL)
            {
                HGOTO_ERROR(DFE_NOSPACE, FAIL);
            }
          sdgCurrent = 0;
      }
    
    /* add ref to table */
    sdgTable[sdgCurrent++] = sdgRef;
    
    /* check if we need to increase size of table */
    if(sdgCurrent == sdgMax) 
      {
          sdgMax *= 2;
          sdgTable = (uint16 *) HDrealloc((VOIDP) sdgTable, sdgMax * sizeof(uint16));
          if (sdgTable == NULL)
            {
                HGOTO_ERROR(DFE_NOSPACE, FAIL);
            }
      }

done:
    if (ret_value == FAIL)
      { /* Failure cleanup */
      }
    /* Normal cleanup */

    return ret_value;
} /* hdf_register_seen_sdg */

/******************************************************************************
 NAME
   hdf_check_nt - Checks format of number type

 DESCRIPTION
   Test if data was stored in native format of different machine or in the
   LITEND format, and make sure the numbertype version numbers are the same
   so we don't read it twice
   (Refactored from hdf_read_ndgs)

 RETURNS
   SUCCEED / FAIL

******************************************************************************/
PRIVATE intn
hdf_check_nt(uint8 *ntstring, int32 *type)
{
    intn ret_value = SUCCEED;
    if ((ntstring[0] != DFNT_VERSION)
         || ((ntstring[3] != DFNTF_NONE) && (ntstring[3] != DFNTF_IEEE)))
    {
        if (ntstring[3] == DFNTF_PC)  /* Little Endian */
            *type |= DFNT_LITEND;
        else
        {   /* same machine type?  */
            if (ntstring[3] == DFKgetPNSC(*type, DF_MT))
                *type |= DFNT_NATIVE;
            else  /* different machine */
            {
                ret_value = FAIL;
            }
        }  /* machine type */
    }   /* Little Endian */

    return(ret_value);
} /* hdf_check_nt */

/******************************************************************************
 NAME
   hdf_read_rank - Reads the rank from file

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   rank / FAIL
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_read_rank(int32 acc_id, int16 *rank)
{
    CONSTR(FUNC, "hdf_read_rank");        /* for HERROR */
    uint8 *p, *local_buf = NULL;
    hdf_err_code_t  ret_value = DFE_NONE;

    local_buf = (uint8 *)HDmalloc(2 * sizeof(uint8));
    if (local_buf == NULL)
    {
        HGOTO_ERROR(DFE_NOSPACE, DFE_NOSPACE);
    }

    /* read and extract the rank */
    if (Hread(acc_id, (int32) 2, local_buf) == FAIL) 
    {
        HGOTO_ERROR(DFE_READERROR, DFE_READERROR);
    }
    else
    {
        int16 temp_rank = 0;
        p = local_buf;
        INT16DECODE(p, temp_rank);
        if (temp_rank > 0)  /* what about the case of rank=0? -BMR */
        {
            *rank = temp_rank;
            HDfree(local_buf);
        }
        else
            HGOTO_ERROR(DFE_RANGE, DFE_RANGE);
    }

done:
    if (ret_value != DFE_NONE)
      { /* Failure cleanup */
        if (local_buf != NULL)
            HDfree(local_buf);
      }

    /* return DFE_NONE or error code */
    return(ret_value);
} /* hdf_read_rank */

/******************************************************************************
 NAME
   hdf_read_dimsizes - Reads the dimensions' size from file

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_read_dimsizes(int32 acc_id, int16 rank, int32* dimsizes)
{
    CONSTR(FUNC, "hdf_read_dimsizes");        /* for HERROR */
    uint8 *p, *local_buf = NULL;
    intn i;
    hdf_err_code_t ret_value = DFE_NONE;

    local_buf = (uint8 *)HDmalloc(4 * (size_t)rank * sizeof(uint8));
    if (local_buf == NULL)
    {
        HGOTO_ERROR(DFE_NOSPACE, DFE_NOSPACE);
    }

    /* read dimension record */
    if (Hread(acc_id, (int32) 4 * rank, local_buf) == FAIL) 
    {
        HGOTO_ERROR(DFE_READERROR, DFE_READERROR);
    }

    p = local_buf;
    for (i = 0; i < rank; i++)
    {
        int32 dim_size = 0;
        INT32DECODE(p, dim_size);
        if (dim_size < 0)
        {
            HGOTO_ERROR(DFE_RANGE, DFE_RANGE);
        }
        else
            dimsizes[i] = dim_size;
    }
    HDfree(local_buf);

done:
    if (ret_value != DFE_NONE)
      { /* Failure cleanup */
        if (local_buf != NULL)
            HDfree(local_buf);
      }

    /* return DFE_NONE or error code */
    return(ret_value);
} /* hdf_read_dimsizes */

/******************************************************************************
 NAME
   hdf_read_NT - Reads NT from file and stores in provided buffer

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_read_NT(int32 acc_id, NC *handle, uint8 *ntstring_buf)
{
    CONSTR(FUNC, "hdf_read_NT");        /* for HERROR */
    uint16 ntTag;
    uint16 ntRef;
    uint8 *p, *local_buf = NULL;
    hdf_err_code_t ret_value = DFE_NONE;

    local_buf = (uint8 *)HDmalloc(4 * sizeof(uint8));
    if (local_buf == NULL)
    {
        HGOTO_ERROR(DFE_NOSPACE, DFE_NOSPACE);
    }

    if (Hread(acc_id,(int32) 4, local_buf) == FAIL) 
    {
        HGOTO_ERROR(DFE_READERROR, DFE_READERROR);
    }

    p = local_buf;
    UINT16DECODE(p, ntTag);
    UINT16DECODE(p, ntRef);

    /* read NT of this scale (dimension) */
    if (Hgetelement(handle->hdf_file, ntTag, ntRef, ntstring_buf) == FAIL)
    {
        HGOTO_ERROR(DFE_GETELEM, DFE_GETELEM);
    }
    HDfree(local_buf);

done:
    if (ret_value != DFE_NONE)
      { /* Failure cleanup */
        if (local_buf != NULL)
            HDfree(local_buf);
      }

    /* return DFE_NONE or error code */
    return(ret_value);
} /* hdf_read_NT */

/******************************************************************************
 NAME
   hdf_get_sdc - Reads coordsys and stores in an attribute.

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_get_sdc(NC *handle, uint16 tmpRef, NC_attr **tmp_attr, intn *curr_attr)
{
    CONSTR(FUNC, "hdf_get_sdc");        /* for HERROR */
    uint8 *coordbuf = NULL; /* buffer to store coord system info */
    int len;
    hdf_err_code_t ret_value = DFE_NONE;

    len = Hlength(handle->hdf_file, DFTAG_SDC, tmpRef);
    if (len == FAIL)
    {
        HGOTO_ERROR(DFE_INTERNAL, DFE_INTERNAL);
    }

    coordbuf = (uint8 *) HDmalloc((uint32) len + 1);
    if (NULL == coordbuf)
    {
        HGOTO_ERROR(DFE_NOSPACE, DFE_NOSPACE);
    }

    if (Hgetelement(handle->hdf_file, DFTAG_SDC, tmpRef, coordbuf) == FAIL)
    {
        HDfreespace((VOIDP)coordbuf);
        HGOTO_ERROR(DFE_GETELEM, DFE_GETELEM);
    }

    coordbuf[len] = '\0';
    if (coordbuf[0] != '\0')
    {
        *tmp_attr = (NC_attr *) NC_new_attr(_HDF_CoordSys, NC_CHAR, HDstrlen(coordbuf), coordbuf);
        if (*tmp_attr == NULL)
        {
            HGOTO_ERROR(DFE_INTERNAL, DFE_INTERNAL);
        }
        else
        {
            (*tmp_attr)->HDFtype = DFNT_CHAR;
            tmp_attr++;
            (*curr_attr)++;
        }
    }
    HDfreespace((VOIDP)coordbuf);
done:
    if (ret_value != DFE_NONE)
      { /* Failure cleanup */
        if (coordbuf != NULL)
            HDfreespace((VOIDP)coordbuf);
      }
    /* Normal cleanup */

    return ret_value;
} /* hdf_get_sdc */

/******************************************************************************
 NAME
   hdf_get_pred_str_attr - Reads predefined string.

 DESCRIPTION
   Reads predefined strings and returns the buffer containing the values.
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   Buffer of predefined string or NULL

******************************************************************************/
uint8 *hdf_get_pred_str_attr(NC *handle, uint16 stratt_tag, uint16 satt_ref, int null_count)
{
    CONSTR(FUNC, "hdf_get_pred_str_attr");        /* for HERROR */
    uint8 *tmpbuf = NULL; /* buffer to store predefined string attribute info */
    intn i;
    uint8 *ret_value = NULL;

    if(satt_ref) 
    {
        int len;

        /*
         *  Add three NULLS to the end to account for a bug in HDF 3.2r1-3
         */

        len = Hlength(handle->hdf_file, stratt_tag, satt_ref);
        if(len == FAIL) 
        {
            HGOTO_ERROR(DFE_INTERNAL, NULL);
        }
                
        tmpbuf = (uint8 *) HDmalloc((uint32) len + 3);
        if(NULL == tmpbuf) 
        {
            HGOTO_ERROR(DFE_NOSPACE, NULL);
        }

        if(Hgetelement(handle->hdf_file, stratt_tag, satt_ref, tmpbuf) == FAIL)
        {
            HGOTO_ERROR(DFE_GETELEM, NULL);
        }
                
        for (i = null_count-1; i >= 0; i--)
            tmpbuf[len + i] = '\0';
    }
    ret_value = tmpbuf;

done:
    if (ret_value == NULL)
      { /* Failure cleanup */
        if (tmpbuf != NULL)
            HDfree(tmpbuf);
      }

    /* return the string attribute */
    return(ret_value);

} /* hdf_get_pred_str_attr */
            
/******************************************************************************
 NAME
   hdf_get_desc_annot - Reads description annotation and stores in an attribute

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_get_desc_annot(NC* handle, uint16 ndgTag, uint16 ndgRef, NC_attr **tmp_attr, intn *curr_attr)
{
    CONSTR(FUNC, "hdf_get_desc_annot");        /* for HERROR */
    intn i;
    hdf_err_code_t ret_value = DFE_NONE;

    /* Re-vamped desc annotation handling to use new ANxxx interface 
     *  -georgev 6/11/97 */
    int32  an_handle   = FAIL;
    int32  *ddescs    = NULL;
    char   *ann_desc  = NULL;
    int32  ann_len;
    intn   num_ddescs;
    char   hremark[30] = ""; /* should be big enough for new attribute */

    /* start Annotation inteface */
    if ((an_handle = ANstart(handle->hdf_file)) == FAIL)
    {
        HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
    }

    /* Get number of data descs with this tag/ref */
    num_ddescs = ANnumann(an_handle, AN_DATA_DESC, ndgTag, ndgRef);
    if (num_ddescs != 0)
    {
        /* allocate space for list of desc annotation id's with this tag/ref */
        if ((ddescs = (int32 *)HDmalloc(num_ddescs * sizeof(int32))) == NULL)
        {
            HGOTO_ERROR(DFE_NOSPACE, DFE_ANAPIERROR);
        }

        /* get list of desc annotations id's with this tag/ref */
        if (ANannlist(an_handle, AN_DATA_DESC, ndgTag, ndgRef, ddescs) != num_ddescs)
        {
            HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
        }

        /* loop through desc list. */
        for (i = 0; i < num_ddescs; i++)
        {
            if ((ann_len = ANannlen(ddescs[i])) == FAIL)
            {
                HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
            }
        
            /* allocate space for desc */
            if (ann_desc == NULL)
            {
                if ((ann_desc = (char *)HDmalloc((ann_len+1)*sizeof(char))) == NULL)
                {
                    HGOTO_ERROR(DFE_NOSPACE, DFE_NOSPACE);
                }
                HDmemset(ann_desc,'\0', ann_len+1);
            }
      
            /* read desc */
            if (ANreadann(ddescs[i], ann_desc, ann_len+1) == FAIL)
            {
                HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
            }

            /* make unique attribute */
            sprintf(hremark,"%s-%d",_HDF_Remarks,i+1);
                            
            /* add it as an attribute */
            *tmp_attr = (NC_attr *) NC_new_attr(hremark, NC_CHAR, 
                                               HDstrlen(ann_desc), ann_desc);

            if (NULL == *tmp_attr)
            {
                HGOTO_ERROR(DFE_INTERNAL, DFE_INTERNAL);
            }
            else
            {
                (*tmp_attr)->HDFtype = DFNT_CHAR;
                tmp_attr++;
                (*curr_attr)++;
            }

            /* end access */
            ANendaccess(ddescs[i]);

            /* free buffer */
            if(ann_desc != NULL)
            {
                HDfree(ann_desc);
                ann_desc = NULL;
            }
        }

    } /* end if descs */

done:
    if (ret_value == DFE_NONE)
      { /* Failure cleanup */
        if(ddescs != NULL)
            HDfree(ddescs);
        if(an_handle != FAIL)
            ANend(an_handle);
      }
    /* cleanup */

    /* return the status */
    return(ret_value);
/* end annotation description conversion */
} /* hdf_get_desc_annot */

/******************************************************************************
 NAME
   hdf_get_pred_str_attr - Reads label annotation and stores in an attribute

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_get_label_annot(NC *handle, uint16 ndgTag, uint16 ndgRef, NC_attr **tmp_attr, intn *curr_attr)
{
    CONSTR(FUNC, "hdf_get_label_annot");        /* for HERROR */
    intn i;
    hdf_err_code_t ret_value = DFE_NONE;

    /* Re-vamped label annotation handling to use new ANxxx interface 
     *  -georgev 6/11/97 */
    int32  an_handle   = FAIL;
    int32  *dlabels    = NULL;
    char   *ann_label  = NULL;
    int32  ann_len;
    intn   num_dlabels;
    char   hlabel[30] = ""; /* should be big enough for new attribute */

    /* start Annotation inteface */
    if ((an_handle = ANstart(handle->hdf_file)) == FAIL)
    {
        HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
    }

    /* Get number of data labels with this tag/ref */
    num_dlabels = ANnumann(an_handle, AN_DATA_LABEL, ndgTag, ndgRef);

    if (num_dlabels != 0)
    {
        /* allocate space for list of label annotation id's with this tag/ref */
        if ((dlabels = (int32 *)HDmalloc(num_dlabels * sizeof(int32))) == NULL)
        {
            HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
        }

        /* get list of label annotations id's with this tag/ref */
        if (ANannlist(an_handle, AN_DATA_LABEL, ndgTag, ndgRef, dlabels) != num_dlabels)
        {
            HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
        }

        /* loop through label list */
        for (i = 0; i < num_dlabels; i++)
        {
            if ((ann_len = ANannlen(dlabels[i])) == FAIL)
            {
                HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
            }
        
            /* allocate space for label */
            if (ann_label == NULL)
            {
                if ((ann_label = (char *)HDmalloc((ann_len+1)*sizeof(char))) == NULL)
                {
                    HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
                }
                HDmemset(ann_label,'\0', ann_len+1);
            }
      
            /* read label */
            if (ANreadann(dlabels[i], ann_label, ann_len+1) == FAIL)
            {
                HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
            }

            /* make unique attribute */
            sprintf(hlabel,"%s-%d",_HDF_AnnoLabel,i+1);

            /* add as attribute */
            *tmp_attr = (NC_attr *) NC_new_attr(hlabel, NC_CHAR,
                                               HDstrlen(ann_label), ann_label);

            if (NULL == tmp_attr)
            {
                HGOTO_ERROR(DFE_ANAPIERROR, DFE_ANAPIERROR);
            }
            else
            {
                (*tmp_attr)->HDFtype = DFNT_CHAR;
                tmp_attr++;
                (*curr_attr)++;
            }

            /* end access */
            ANendaccess(dlabels[i]);

            /* free buffer */
            if(ann_label != NULL)
            {
                HDfree(ann_label);
                ann_label = NULL;
            }
        }
    } /* end if labels */

done:
    if (ret_value == DFE_NONE)
      { /* Failure cleanup */
        if(dlabels != NULL)
            HDfree(dlabels);
        if(an_handle != FAIL)
            ANend(an_handle);
      }
    /* cleanup */
    /* return the status */
    return(ret_value);

/* end annotation label processing */
} /* hdf_get_label_annot */

/******************************************************************************
 NAME
   hdf_luf_to_attrs - Reads label, unit, and format strings and converts them
                      into attributes.

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_luf_to_attrs(char *labelstr, char *unitstr, char *formatstr, NC_attr **tmp_attr, intn *curr_attr)
{
    CONSTR(FUNC, "hdf_luf_to_attrs");        /* for HERROR */
    hdf_err_code_t ret_value = DFE_NONE;

    /* label => "long_name"  */
    if (labelstr && (labelstr[0] != '\0') > 0) 
    {
        *tmp_attr = (NC_attr *) NC_new_attr(_HDF_LongName, NC_CHAR,
                           HDstrlen((char *)labelstr), (Void *) labelstr);

        if (NULL == *tmp_attr)
        {
            HGOTO_ERROR(DFE_INTERNAL, DFE_INTERNAL);
        }
        else
        {
            (*tmp_attr)->HDFtype = DFNT_CHAR;
            tmp_attr++;
            (*curr_attr)++;
        }
    }

    /* Units => 'units' */
    if(unitstr && (unitstr[0] != '\0') > 0) 
    {
        *tmp_attr = (NC_attr *) NC_new_attr(_HDF_Units, NC_CHAR,
                           HDstrlen((char *)unitstr), (Void *) unitstr);

        if (NULL == *tmp_attr)
        {
            HGOTO_ERROR(DFE_INTERNAL, DFE_INTERNAL);
        }
        else
        {
            (*tmp_attr)->HDFtype = DFNT_CHAR;
            tmp_attr++;
            (*curr_attr)++;
        }
    }

    /* Fomrat => 'format' */
    if (formatstr && (formatstr[0] != '\0') > 0) 
    {
        *tmp_attr = (NC_attr *) NC_new_attr(_HDF_Format, NC_CHAR,
                           HDstrlen((char *)formatstr), (Void *) formatstr);

        if (NULL == *tmp_attr)
        {
            HGOTO_ERROR(DFE_INTERNAL, DFE_INTERNAL);
        }
        else
        {
            (*tmp_attr)->HDFtype = DFNT_CHAR;
            tmp_attr++;
            (*curr_attr)++;
        }
    }

done:
    if (ret_value == DFE_NONE)
      { /* Failure cleanup */
      }
    /* cleanup */
    /* return the status */
    return(ret_value);

} /* hdf_luf_to_attrs */

/******************************************************************************
 NAME
   hdf_get_rangeinfo - Reads range information and converts them into attributes

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_get_rangeinfo(nc_type nctype, int32 hdftype, NC_attr **tmp_attr, intn *curr_attr)
{
    CONSTR(FUNC, "hdf_get_rangeinfo");        /* for HERROR */
    uint8     tBuf[128] = "";
    intn idx = 0; /* index for tBuf */
    hdf_err_code_t ret_value = DFE_NONE;

    if (FAIL == DFKconvert((VOIDP)ptbuf, (VOIDP) tBuf, hdftype, 2, DFACC_READ, 0, 0))
    {
        HGOTO_ERROR(DFE_BADCONV, FAIL);
    }

    /* _HDF_ValidMax */
    *tmp_attr = (NC_attr *) NC_new_attr(_HDF_ValidMax, nctype, 1, (Void *) tBuf);

    if (NULL == *tmp_attr)
    {
        HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }
    else
    {
        (*tmp_attr)->HDFtype = hdftype;
        tmp_attr++;
        (*curr_attr)++;
    }

    /* _HDF_ValidMin */
    idx = DFKNTsize(hdftype|DFNT_NATIVE);
    *tmp_attr = (NC_attr *) NC_new_attr(_HDF_ValidMin, nctype, 1, (Void *) &(tBuf[idx]));

    if (NULL == *tmp_attr)
    {
        HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }
    else
    {
        (*tmp_attr)->HDFtype = hdftype;
        tmp_attr++;
        (*curr_attr)++;
    }

done:
    if (ret_value == DFE_NONE)
      { /* Failure cleanup */
      }
    /* cleanup */
    /* return the status */
    return(ret_value);

} /* hdf_get_rangeinfo */

/******************************************************************************
 NAME
   hdf_get_cal - Reads calibration and stores them attributes

 DESCRIPTION
   (Refactored from hdf_read_ndgs - Jun, 2017)

 RETURNS
   DFE_NONE / <error code>

******************************************************************************/
PRIVATE hdf_err_code_t
hdf_get_cal(nc_type nctype, int32 hdftype, NC_attr **tmp_attr, intn *curr_attr)
{
    CONSTR(FUNC, "hdf_get_cal");        /* for HERROR */
    uint8 tBuf[128] = "";
    intn idx = 0; /* index for tBuf */
    hdf_err_code_t ret_value = DFE_NONE;

    /* for DFNT_FLOAT32 based calibration */
    intn incr = 4;  /* increment 4 bytes */
    int32 nt_hdftype = DFNT_INT16;
    nc_type nt_nctype = NC_SHORT;

    /* for DFNT_FLOAT64 based calibration */
    if (hdftype == DFNT_FLOAT64)
    {
        incr = 8;   /* increment 8 bytes */
        nt_hdftype = DFNT_INT32;
        nt_nctype = NC_LONG;
    }

    if (FAIL == DFKconvert((VOIDP)ptbuf, (VOIDP) tBuf, hdftype, 4, DFACC_READ, 0, 0))
    {
        HGOTO_ERROR(DFE_BADCONV, FAIL);
    }

    /* _HDF_ScaleFactor */
    *tmp_attr = (NC_attr *) NC_new_attr(_HDF_ScaleFactor, nctype, 1, (Void *) &(tBuf[idx]));

    if (NULL == *tmp_attr)
    {
        HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }
    else
    {
        (*tmp_attr)->HDFtype = hdftype;
        tmp_attr++;
        (*curr_attr)++;
    }

    /* _HDF_ScaleFactorErr */
    idx = idx + incr;
    *tmp_attr = (NC_attr *) NC_new_attr(_HDF_ScaleFactorErr, nctype, 1, (Void *) &(tBuf[idx]));

    if (NULL == *tmp_attr)
    {
        HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }
    else
    {
        (*tmp_attr)->HDFtype = hdftype;
        tmp_attr++;
        (*curr_attr)++;
    }

    /* _HDF_AddOffset */
    idx = idx + incr;
    *tmp_attr = (NC_attr *) NC_new_attr(_HDF_AddOffset, nctype, 1, (Void *) &(tBuf[idx]));

    if (NULL == *tmp_attr)
    {
        HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }
    else
    {
        (*tmp_attr)->HDFtype = hdftype;
        tmp_attr++;
        (*curr_attr)++;
    }

    /* _HDF_AddOffsetErr */
    idx = idx + incr;
    *tmp_attr = (NC_attr *) NC_new_attr(_HDF_AddOffsetErr, nctype, 1, (Void *) &(tBuf[idx]));

    if (NULL == *tmp_attr)
    {
        HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }
    else
    {
        (*tmp_attr)->HDFtype = hdftype;
        tmp_attr++;
        (*curr_attr)++;
    }

    /* don't forget number_type  */
    if (FAIL == DFKconvert((VOIDP)(ptbuf + idx + incr), (VOIDP) tBuf, nt_hdftype, 1, DFACC_READ, 0,0))
    {
        HGOTO_ERROR(DFE_BADCONV, FAIL);
    }

    *tmp_attr = (NC_attr *) NC_new_attr(_HDF_CalibratedNt, nt_nctype, 1, (Void *) &(tBuf[0]));

    if (NULL == *tmp_attr)
    {
        HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }
    else
    {
        (*tmp_attr)->HDFtype = nt_hdftype;
        tmp_attr++;
        (*curr_attr)++;
    }
done:
    if (ret_value == DFE_NONE)
      { /* Failure cleanup */
      }
    /* cleanup */
    /* return the status */
    return(ret_value);

} /* hdf_get_cal */


/******************************************************************************
 NAME
   hdf_read_ndgs
 
 DESCRIPTION
   Loop through all of the NDGs in the file and create data structures for 
   them

 RETURNS
   SUCCEED / FAIL
 
******************************************************************************/
PRIVATE intn 
hdf_read_ndgs(NC *handle)
{
    CONSTR(FUNC, "hdf_read_ndgs");        /* for HERROR */
    char     tmpname[80] = "";
    uint8    ntstring[4] = "";
    intn     dimcount;
    intn     dimattrcnt;
    /* info about NDG structure */
    int32    GroupID;
    int32    aid;
    int32    aid1;
    uint16   ndgTag;
    uint16   ndgRef;
    uint16   sddRef;
    uint16   lRef;
    uint16   uRef;
    uint16   fRef;
    uint16   sRef;
    uint16   sdRef;
    uint16   tmpTag;
    uint16   tmpRef;
    int16    rank=0;
    nc_type  type;
    int32   *dimsizes = NULL;
    int32   *scaletypes = NULL;
    int32    HDFtype;
    int32    temptype;
    hdf_err_code_t err_code;
    intn     dim;
    intn     max_thangs;
    intn     current_dim;
    intn     current_var;
    intn     current_attr;
    intn    *vardims = NULL;
    /* info about netCDF structures */
    NC_dim  **dims = NULL;   /* hold list of dimensions as we create it */
    NC_var  **vars = NULL;   /* hold variable list as we create it      */
    NC_attr **attrs = NULL;  /* hold attribute list as we create it     */
    NC_attr  *dimattrs[10];  /* for LUF and anno_label, anno_desc, 10 is enough */
    uint8    *labelbuf = NULL; /* label should not be used as var name due to non-uniqueness  */
    uint8    *scalebuf = NULL; /* buffer to store scale info */
    uint8    *unitbuf = NULL;  /* buffer to store unit info */
    uint8    *formatbuf = NULL; /* buffer to store format info */
    uint8    *coordbuf = NULL; /* buffer to store coord system info */
    intn      new_dim;   /* == new dim so create coord variable     */
    /* random book-keeping */
    intn      i;
    intn      status;
    intn      tag_index;
    uint8    *p = NULL;
    uint8     tBuf[128] = "";
    intn      scale_offset;   /* current offset into the scales record for the
                            current dimension's values */
    intn      ret_value = SUCCEED;

    /*
     *  Allocate the array to store the dimensions
     */
    max_thangs  = 1; /* what is this limit ? */

    dims = (NC_dim **) HDmalloc(sizeof(NC_dim *) * max_thangs);
    if(NULL == dims) 
      {
          HGOTO_ERROR(DFE_NOSPACE, FAIL);
      }
    
    vars = (NC_var **) HDmalloc(sizeof(NC_var *) * max_thangs);
    if(NULL == vars) 
      {
          HGOTO_ERROR(DFE_NOSPACE, FAIL);
      }

    attrs = (NC_attr **) HDmalloc(sizeof(NC_attr *) * 100);
    if(NULL == attrs) 
      {
          HGOTO_ERROR(DFE_NOSPACE, FAIL);
      }

    /* no dimensions or variables yet */
    current_dim = 0;
    current_var = 0;
    dimcount = 0;

    for(tag_index = 0; tag_index < 2; tag_index++) 
      {

          if(tag_index == 0)
              ndgTag = DFTAG_NDG;
          else
              ndgTag = DFTAG_SDG;

          /*
           * Start from the beginning and look though
           */
          aid = Hstartread(handle->hdf_file, ndgTag, DFREF_WILDCARD);
          if(aid == FAIL) 
              continue; /* hmm if we fail we continue the loop? */
        
          /*
           * Loop through all of the NDGs in the file
           */
          status = SUCCEED;
          while (status == SUCCEED) 
            {
                uint16 ntTag;
                uint16 ntRef;

                if(HQuerytagref(aid, &ndgTag, &ndgRef) == FAIL) 
                  {
                      HGOTO_ERROR(DFE_INTERNAL, FAIL);
                  }

                /* Test if its an SDG-NDG which we've processed already */
                if((ndgTag == DFTAG_SDG) && (hdf_query_seen_sdg(ndgRef))) 
                  {
                      status = Hnextread(aid, ndgTag, DFREF_WILDCARD, DF_CURRENT);  
                      continue; /* go to next element */
                  }
                
                /* OK, now we need to get the relevant dimension structure */
#ifdef DEBUG
                printf("Found NDG at %d %d\n", ndgTag, ndgRef);
#endif
            
                /* read the group into memory */
                if ((GroupID = DFdiread(handle->hdf_file, ndgTag, ndgRef)) < 0) 
                  {
                      HGOTO_ERROR(DFE_INTERNAL, FAIL);
                  }
            
                sddRef = lRef = uRef = fRef = sRef = sdRef = 0;
            
                /* default number type is Float32 */
                type    = NC_FLOAT; 
                HDFtype = DFNT_FLOAT32;
            
                /* no attributes found yet */
                current_attr = 0;
            
                /* no meta-data seen yet */
                labelbuf = unitbuf = scalebuf = formatbuf = NULL;
            
                /*
                 * Loop through the members of the group looking for stuff
                 *
                 * NOTE:  Only generate attributes for meta-data which does
                 *        not depend on the rank of the data since we can not
                 *        be sure that we get the rank first.  
                 *        If the meta-data depends on the rank, just remember
                 *        the ref number and read the element once this while
                 *        loop is finished.
                 */

                /* Check if temporary buffer has been allocated */
                if (ptbuf == NULL)
                {
                    ptbuf = (uint8 *)HDmalloc(TBUF_SZ * sizeof(uint8));
                    if (ptbuf == NULL)
                    {
                        HGOTO_ERROR(DFE_NOSPACE, FAIL);
                    }
                }

                while (!DFdiget(GroupID, &tmpTag, &tmpRef)) 
                  {
                      switch(tmpTag) 
                        {
                        case DFTAG_SDD:
 /* hdf_get_sdd(handle, tmpTag, tmpRef);
 */ 
                            aid1 = Hstartread(handle->hdf_file, tmpTag, tmpRef);
                            if (aid1 == FAIL)
                              {
                                  HGOTO_ERROR(DFE_CANTACCESS, FAIL);
                              }

                            /* read rank */
                            err_code = hdf_read_rank(aid1, &rank);
                            if (err_code != DFE_NONE)
                                HGOTO_ERROR(err_code, FAIL);

                            /* get space for dimensions */
                            dimsizes = (int32 *) HDmalloc((uint32) rank * sizeof(int32));
                            if (dimsizes == NULL) 
                              {
                                  HGOTO_ERROR(DFE_NOSPACE, FAIL);
                              }

                            vardims = (intn *) HDmalloc((uint32) rank * sizeof(intn));
                            if (vardims == NULL) 
                              {
                                  HGOTO_ERROR(DFE_NOSPACE, FAIL);
                              }

                            scaletypes = (int32 *) HDmalloc((uint32) rank * sizeof(int32));
                            if (scaletypes == NULL) 
                              {
                                  HGOTO_ERROR(DFE_NOSPACE, FAIL);
                              }

                            /* read dimension record */
                            err_code = hdf_read_dimsizes(aid1, rank, dimsizes);
                            if (err_code != DFE_NONE)
                                HGOTO_ERROR(err_code, FAIL);

                            /* read in number type string */
                            err_code = hdf_read_NT(aid1, handle, ntstring);
                            if (err_code == FAIL)
                                  HGOTO_ERROR(err_code, FAIL);

                            HDFtype = ntstring[1];
                            if ((type = hdf_unmap_type(HDFtype)) == FAIL)
                              {
                                  HGOTO_ERROR(DFE_INTERNAL, FAIL);
                              }

                            /* Validate number type regarding platform/format */
                            if (hdf_check_nt(ntstring, &HDFtype) == FAIL)
                                 HGOTO_ERROR(DFE_INTERNAL, FAIL);

                            /* read in scale NTs */
                            for(i = 0; i < rank; i++) 
                              {
                                err_code = hdf_read_NT(aid1, handle, ntstring);
                                if (err_code != DFE_NONE)
                                    HGOTO_ERROR(err_code, FAIL);

                                scaletypes[i] = ntstring[1];

                                /* temp preserve scaletype in case of error */
                                temptype = scaletypes[i];

                                  /* check native format and LITEND */
                                  if (hdf_check_nt(ntstring, &temptype) == FAIL)
                                       HGOTO_ERROR(DFE_INTERNAL, FAIL);

                                  /* restore scaletype */
                                  scaletypes[i] = temptype;
                              }
                    
                            sddRef = tmpRef;    /* prepare for a new dim var */
                            if (Hendaccess(aid1) == FAIL)
                              {
                                  HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);
                              }
                    
                            break;
                    
                        case DFTAG_SDL:       /* label */
                            lRef = tmpRef;
                            break;
                    
                        case DFTAG_SDU:       /* unit */
                            uRef = tmpRef;
                            break;
                    
                        case DFTAG_SDF:       /* format */
                            fRef = tmpRef;
                            break;

                        case DFTAG_SDC:       /* coord  */
                            /*
                             * DFTAG_SDC => 'cordsys'
                             */
                        { 
                            err_code = hdf_get_sdc(handle, tmpRef, &attrs[current_attr], &current_attr);
                            if (err_code != DFE_NONE)
                            {
                                HGOTO_ERROR(err_code, FAIL);
                            }
                        }
                        break;

                        case DFTAG_SDS:       /* scales */
                            sRef = tmpRef;
                            break;
                    
                        case DFTAG_SD:        /* actual data */
                            sdRef = tmpRef;
                            break;
                    
                        case DFTAG_CAL:        /* calibration info */
                            /* 
                           * DFTAG_CAL => 'scale_factor', 'add_offset', 'scale_factor_err', 
                           *              'add_offset_err'
                           */
                        {
                            if (Hgetelement(handle->hdf_file, tmpTag, tmpRef, ptbuf) == FAIL)
                              {
                                  HGOTO_ERROR(DFE_GETELEM, FAIL);
                              }

                            if (Hlength(handle->hdf_file, tmpTag, tmpRef) == 36)
                            {
                                  /* DFNT_FLOAT64 based calibration */
                                err_code = hdf_get_cal(NC_DOUBLE, DFNT_FLOAT64,
                                        &attrs[current_attr], &current_attr);
                                if (err_code != DFE_NONE)
                                {
                                    HGOTO_ERROR(err_code, FAIL);
                                }
                            } 
                            else 
                            {
                                  /* DFNT_FLOAT32 based calibration */
                                err_code = hdf_get_cal(NC_FLOAT, DFNT_FLOAT32,
                                        &attrs[current_attr], &current_attr);

                                if (err_code != DFE_NONE)
                                {
                                    HGOTO_ERROR(err_code, FAIL);
                                }
                            } 
                            break;
                        }

                        case DFTAG_SDM:        /* valid range info */
                    
                            if (Hgetelement(handle->hdf_file, tmpTag, tmpRef, ptbuf) == FAIL)
                              {
                                  HGOTO_ERROR(DFE_GETELEM, FAIL);
                              }
                    
                            err_code = hdf_get_rangeinfo(type, HDFtype, &attrs[current_attr], &current_attr);
                                if (err_code != DFE_NONE)
                                {
                                    HGOTO_ERROR(err_code, FAIL);
                                }

                            break;

                        case DFTAG_SDLNK:
                            if(ndgTag == DFTAG_SDG) 
                                continue; /* continue processing? */

                            if (Hgetelement(handle->hdf_file, tmpTag, tmpRef, ptbuf) == FAIL) 
                              {
                                  HGOTO_ERROR(DFE_GETELEM, FAIL);
                              }
                            else 
                              {
                                  uint16 sdgTag, sdgRef;

                                  p = ptbuf;
                        
                                  /* the first two are for the NDG tag/ref */
                                  UINT16DECODE(p, sdgTag);
                                  UINT16DECODE(p, sdgRef);
                        
                                  /* now the ones we're interested in */
                                  UINT16DECODE(p, sdgTag);
                                  UINT16DECODE(p, sdgRef);

                                  if (hdf_register_seen_sdg(sdgRef) == FAIL)
                                    {
                                        HGOTO_ERROR(DFE_INTERNAL, FAIL);
                                    }
                              }

                            break;
                    
                        default:
                            break;
                        } /* end switch 'tmpTag */
                  }     /* end while 'DFdiget()'*/

                /* Free local buffer */
                if (ptbuf != NULL)
                {
                    HDfree(ptbuf);
                    ptbuf = NULL;
                }
            
                /*
                 * Get the predefined string attributes of the dataset.  Note
                 * that, in the first three attributes, we need to add three
                 * NULLs to the end of the buffer to account for a bug in
                 * HDF 3.2r1-3, hence, the last argument is 3.  The last
                 * attribute doesn't need the NULL characters.
                 */
                labelbuf = hdf_get_pred_str_attr(handle, DFTAG_SDL, lRef, 3);
                unitbuf = hdf_get_pred_str_attr(handle, DFTAG_SDU, uRef, 3);
                formatbuf = hdf_get_pred_str_attr(handle, DFTAG_SDF, fRef, 3);
                scalebuf = hdf_get_pred_str_attr(handle, DFTAG_SDS, sRef, 0);
           
                /* skip over the garbage at the beginning */
                scale_offset = rank * sizeof(uint8);
            
                for (dim = 0; dim < rank; dim++) 
                  {
                      intn this_dim     = FAIL;
                      char *labelvalue  = NULL;
                      char *unitvalue = NULL;
                      char *formatvalue = NULL;

                      /* now loop though each dimension
                         - get the size from dimsize[i]
                         - lref will give the ref of the label descriptor to see if 
                         has a real name else fake one based on the label of the NDG
                         - look at uref for units information and fref for formating 
                         info store both of these as attributes of the coordinate 
                         variable
                         - Promote the dimension to a variable if any of the LUF or
                         scales is assigned to this dimentsion. 
                         - The dimension variable name is the same as the dimension 
                         record name, fakeDim<dim count>.
                         */
               
                      new_dim = FAIL; 
                      tmpname[0] = '\0';
                
                      if(lRef) 
                        {
                            labelvalue = (char *) labelbuf;
                            for(i = 0; i < dim + 1; i++) 
                                labelvalue += HDstrlen(labelvalue) + 1;
                            if (labelvalue[0] != '\0') 
                                new_dim = SUCCEED;
                        }
                
                      if(uRef) 
                        {
                            unitvalue = (char *) unitbuf;
                            for(i = 0; i < dim + 1; i++) 
                                unitvalue += HDstrlen(unitvalue) + 1;
                            if (unitvalue[0] != '\0') 
                                new_dim = SUCCEED;
                        }

                      if(fRef) 
                        {
                            formatvalue = (char *) formatbuf;
                            for(i = 0; i < dim + 1; i++) 
                                formatvalue += HDstrlen(formatvalue) + 1;
                            if (formatvalue[0] != '\0') 
                                new_dim = SUCCEED;
                        }

                      sprintf(tmpname, "fakeDim%d", dimcount++);
                
                      this_dim = current_dim++;
                      if(current_dim == max_thangs)
                        {
                            /* need to allocate more space */
                            max_thangs *= 2;
                            dims = (NC_dim **) HDrealloc((VOIDP) dims, sizeof(NC_dim *) * max_thangs);
                            if(NULL == dims)
                              {
                                  HGOTO_ERROR(DFE_NOSPACE, FAIL);
                              }

                            vars = (NC_var **) HDrealloc((VOIDP) vars, sizeof(NC_var *) * max_thangs);
                            if(NULL == vars)
                              {
                                  HGOTO_ERROR(DFE_NOSPACE, FAIL);
                              }
                        }

                      /*
                       * Create a new dimension record for each dimension. 
                       * Each NC_dim takes 8 bytes in memory. 
                       */
                      dims[this_dim] = NC_new_dim(tmpname, dimsizes[dim]);
                      if (NULL == dims[this_dim])
                        {
                            HGOTO_ERROR(DFE_INTERNAL, FAIL);
                        }
                
                      /* 
                       * It looks like were gonna have to do the variable define
                       * here too cuz we need to remember the indices of where
                       * we put the dimensions
                       */
                      vardims[dim] = (intn) this_dim;
                
                
                      /*
                       * Look at the scale NTs since the scales may have
                       * different number types.
                       * Promote the dimension to a variable, but only if it
                       * has meta-data stored with it.  
                       */
                      if(new_dim || (scalebuf && scalebuf[dim])) 
                        {
                            nc_type stype;

                            if ((stype = hdf_unmap_type(scaletypes[dim])) == FAIL)
                              {
                                  HGOTO_ERROR(DFE_INTERNAL, FAIL);
                              }

                            vars[current_var] = NC_new_var(tmpname, stype, 1, 
                                                           &this_dim);
                            if (NULL == vars[current_var])
                              {
                                  HGOTO_ERROR(DFE_INTERNAL, FAIL);
                              }

                            vars[current_var]->data_tag = DFTAG_SDS;  /* not normal data */
                            vars[current_var]->data_ref = sRef;
                            vars[current_var]->HDFtype  = scaletypes[dim];
#ifdef NOT_YET
                            vars[current_var]->ndg_ref  = Htagnewref(handle->hdf_file,DFTAG_NDG);
#else /* NOT_YET */
                            vars[current_var]->ndg_ref  = Hnewref(handle->hdf_file);
#endif /* NOT_YET */
			                /* Indicate that it is unknown whether the current
			                   variable is an SDS or a coordinate variable.
			                   bugzilla 624 - BMR - 05/16/2007 */
			                /* vars[current_var]->var_type  = UNKNOWN; */ 
			                /* It looks like this is a dimension variable for
                               sure! -BMR 10/26/2010 */
			                vars[current_var]->var_type  = IS_CRDVAR;

                            /*
                             * See if a scales record has been stored and if there have
                             *   been scale values provided
                             */
                            if((scalebuf) && (scalebuf[dim])) 
                              {
                                  vars[current_var]->numrecs = dimsizes[dim];
                                  vars[current_var]->data_offset = scale_offset;
                                  scale_offset += dimsizes[dim] * DFKNTsize(scaletypes[dim]);
                              } 
                            else 
                              {
                                  vars[current_var]->data_offset = -1;  /* no values */
                              }
                            /*
                             * Convert dimstrs into attributes  
                             * label -- "long_name" (cuz SDsetdimstrs() assigns
                             * "long_name" to label)
                             * unit  -- "units"
                             * format -- "format"
                             */
                            dimattrcnt = 0;
                            err_code = hdf_luf_to_attrs(
                                            labelvalue, unitvalue, formatvalue,
                                            &dimattrs[dimattrcnt], &dimattrcnt);

                            /*
                             * Add the attributes to the variable
                             */
                            if(dimattrcnt)
                              {
                                vars[current_var]->attrs = NC_new_array(
                                                    NC_ATTRIBUTE, dimattrcnt,
                                                    (Void *) dimattrs);
                                  if (NULL == vars[current_var]->attrs)
                                    {
                                        HGOTO_ERROR(DFE_INTERNAL, FAIL);
                                    }
                              }
                            else
                                vars[current_var]->attrs = NULL;

                            current_var++;  

                            if(current_var == max_thangs)
                              {
                                  /* need to allocate more space */
                                  max_thangs *= 2;

                                  dims = (NC_dim **) HDrealloc((VOIDP)dims, sizeof(NC_dim *) * max_thangs);
                                  if(NULL == dims)
                                        HGOTO_ERROR(DFE_NOSPACE, FAIL);

                                  vars = (NC_var **) HDrealloc((VOIDP)vars, sizeof(NC_var *) * max_thangs);
                                  if(NULL == vars)
                                        HGOTO_ERROR(DFE_NOSPACE, FAIL);
                              }
                        } /* end if 'new_dim' */
                  } /* end for 'dim' */
            
                /*
                 * Should the LUF-label be mapped as attr of "longname", to be
                 * consistent with the dim vars? 8/18/94
                 * Should the annotation-label mapped to attr "anno-label",
                 * if "longname" has been taken by LUF-label?  8/18/94.
                 *   
                 * (If there is a data label, use that as the variable name
                 *  else) 
                 * Use the reference number of the NDG as part of
                 * a made up name (Label is mapped as attr "longname" 9/2/94).
                 *
                 * Convert spaces in the name to underscores (yuck) otherwise
                 *    ncgen will barf on ncdumped files)
                 */
#if 0
                /* if(labelbuf && (labelbuf[0] != '\0')) 
                   {
                   char *c;
                   for(c = (char *)labelbuf; *c; c++)
                   if((*c) == ' ') (*c) = '_';

                   vars[current_var] = NC_new_var((char *) labelbuf, type, (int) rank, vardims);
                   } 
                   else 
                   { */
#endif

                sprintf(tmpname, "Data-Set-%d", ndgRef); 
                vars[current_var] = NC_new_var(tmpname, type, (int) rank, vardims);
                if (NULL == vars[current_var])
                  {
                      HGOTO_ERROR(DFE_INTERNAL, FAIL);
                  }

#if 0
                /*   } */
#endif 
                /*
                 * Fill in extra information so it will be easier to backtrack
                 *    when the user wants to lift data out
                 */
                vars[current_var]->data_tag = DATA_TAG;
                vars[current_var]->data_ref = sdRef;
                vars[current_var]->HDFtype  = HDFtype;

		        /* Indicate that it is unknown whether the current variable 
		           is an SDS or a coordinate variable.  bugzilla 624 - BMR - 
		           05/16/2007.  This looks like a IS_CRDVAR because it's from
		           vardim! -BMR - 6/1/16 */
                vars[current_var]->var_type  = UNKNOWN;

                /*
                 * NOTE:  If the user changes the file and saves setting this
                 *   to ndgRef will blow away the old ndgs (but they will get
                 *   rewritten).  Otherwise calls to SDidtoref() will return
                 *   bogus values
                 */
                vars[current_var]->ndg_ref  = ndgRef; 

                /*
                 * --------------------------------------------
                 * Convert HDF meta-data into netCDF attributes
                 * --------------------------------------------
                 */
            
                /*
                 * If there is an annotation put in 'remarks'
                 */
                {
                    NC_attr *tmp_attr = NULL;
                    err_code = DFE_NONE;

                    err_code = hdf_get_desc_annot(handle, ndgTag, ndgRef,
                                    &attrs[current_attr], &current_attr);
                    if (err_code != DFE_NONE)
                    {
                        HGOTO_ERROR(err_code, FAIL);
                    }

                } /* end annotation description conversion */
            
                /*
                 * If there is a label, put it in attr 'anno_label' (note:
                 * NOT 'long_name' 9/2/94)
                 */
                {
                    NC_attr *tmp_attr = NULL;
                    err_code = DFE_NONE;

                    err_code = hdf_get_label_annot(handle, ndgTag, ndgRef,
                                    &attrs[current_attr], &current_attr);
                    if (err_code != DFE_NONE)
                    {
                        HGOTO_ERROR(err_code, FAIL);
                    }

                } /* end annotation label processing */

                /* Convert label, units, format strings to attributes */
                err_code = hdf_luf_to_attrs(
                             (char*)labelbuf, (char*)unitbuf, (char *)formatbuf,
                             &attrs[current_attr], &current_attr);
                if (err_code != DFE_NONE)
                {
                    HGOTO_ERROR(err_code, FAIL);
                }

                /*
                 * Add the attributes to the variable
                 */ 
                if(current_attr)
                  {
                    vars[current_var]->attrs = NC_new_array(NC_ATTRIBUTE, 
                                                            current_attr,
                                                            (Void *) attrs);

                      if (NULL == vars[current_var]->attrs)
                        {
                            HGOTO_ERROR(DFE_INTERNAL, FAIL);
                        }
                  }
                else
                    vars[current_var]->attrs = NULL;
            
                current_var++;

                if(current_var == max_thangs)
                  {
                      /* need to allocate more space */
                      max_thangs *= 2;

                      dims = (NC_dim **) HDrealloc((VOIDP) dims, sizeof(NC_dim *) * max_thangs);
                      if(NULL == dims)
                        {
                            HGOTO_ERROR(DFE_NOSPACE, FAIL);
                        }

                      vars = (NC_var **) HDrealloc((VOIDP) vars, sizeof(NC_var *) * max_thangs);
                      if(NULL == vars)
                        {
                            HGOTO_ERROR(DFE_NOSPACE, FAIL);
                        }

                  }

                /*
                 * De-allocate temporary storage
                 */
                if(labelbuf != NULL)  
                    HDfree((VOIDP)labelbuf);
                if(scalebuf != NULL)
                    HDfree((VOIDP)scalebuf);
                if(unitbuf != NULL)  
                    HDfree((VOIDP)unitbuf);
                if(formatbuf != NULL)  
                    HDfree((VOIDP)formatbuf);
                if (dimsizes != NULL)
                    HDfree((VOIDP)dimsizes);
                if (vardims != NULL)
                    HDfree((VOIDP)vardims);
                if (scaletypes != NULL)
                    HDfree((VOIDP)scaletypes);
            
                /*
                 * Look for the next DataSet
                 */
                status = Hnextread(aid, ndgTag, DFREF_WILDCARD, DF_CURRENT);
            
            } /* while (more NDGs) */
        
          if (Hendaccess(aid) == FAIL)
            {
                HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);
            }
        
      } /* outermost for loop to loop between NDGs and SDGs */

      /*
       * Set up the structures in the proper form
       */
      if(current_dim)
      {
          handle->dims = NC_new_array(NC_DIMENSION, current_dim, (Void *) dims);
          if (NULL == handle->dims)
          {
              HGOTO_ERROR(DFE_INTERNAL, FAIL);
          }
      }
      else
          handle->dims = NULL;
        
      if(current_var)
      {
          handle->vars = NC_new_array(NC_VARIABLE, current_var, (Void *) vars);
          if (NULL == handle->vars)
          {
              HGOTO_ERROR(DFE_INTERNAL, FAIL);
          }
      }
      else
          handle->vars = NULL;
        
done:
    if (ret_value == FAIL)
      { /* FAIL cleanup? */
          if(labelbuf != NULL)  
              HDfree((VOIDP)labelbuf);
          if(scalebuf != NULL)
              HDfree((VOIDP)scalebuf);
          if(unitbuf != NULL)  
              HDfree((VOIDP)unitbuf);
          if(formatbuf != NULL)  
              HDfree((VOIDP)formatbuf);
          if (dimsizes != NULL)
              HDfree((VOIDP)dimsizes);
          if (vardims != NULL)
              HDfree((VOIDP)vardims);
          if (scaletypes != NULL)
              HDfree((VOIDP)scaletypes);
	  if (ptbuf != NULL)
	      HDfree(ptbuf);

      }
    /* Normal cleanup */
    if (dims != NULL)
        HDfree((VOIDP)dims);
    if (vars != NULL)
        HDfree((VOIDP)vars);
    if (attrs != NULL)
        HDfree((VOIDP)attrs);

    return ret_value;
} /* hdf_read_ndgs */

/******************************************************************************
 NAME
   hdf_read_sds_cdf
 
 DESCRIPTION
   Read SDSs out of an HDF file an pretend like they are netCDF objects
   We can already assume that the file is open and that it is in fact
   an HDF file

 RETURNS
   SUCCEED / FAIL
 
******************************************************************************/
intn
hdf_read_sds_cdf(XDR *xdrs, NC **handlep)
{
    CONSTR(FUNC, "hdf_read_sds_cdf");        /* for HERROR */
    intn  status;
    NC    *handle = NULL;
    intn  ret_value = SUCCEED;
    
    /* 
     * go through and treat each SDS as a separate variable 
     */

    /* 
     * should we try to create an unlimited dimension somehow ???
     */
    
    /* we haven't seen any SDG-NDG combos yet */
    HDfreenclear(sdgTable);

    handle = (*handlep);
    if(NULL == handle) 
      {
        HGOTO_ERROR(DFE_ARGS, FAIL);
      }

    status = hdf_read_ndgs(handle);
    if(status == FAIL) 
      {
        HGOTO_ERROR(DFE_INTERNAL, FAIL);
      }

    /* deallocate SDG-NDG space */
    if(sdgTable != NULL) 
        HDfree((VOIDP)sdgTable);

    sdgTable = NULL;

done:
    if (ret_value == FAIL)
      { /* Failure cleanup */

      }
    /* Normal cleanup */

    return ret_value;
} /* hdf_read_sds_cdf */

#endif /* HDF */
