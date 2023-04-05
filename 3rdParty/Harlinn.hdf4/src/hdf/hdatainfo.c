/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF.  The full HDF copyright notice, including       *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://support.hdfgroup.org/ftp/HDF/releases/.  *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* NOTE: this file and other "datainfo" related files will be configured so
         that this feature will not be built by default. -BMR
   Update: THG and NASA had decided to include all features developed for the
           HDF Mapping Project in the library -BMR (~Jan 2011) */

/**********************************************************************
FILE
  hdatainfo.c
  HDF data information routines - added to support the HDF4 Mapping project

  This file contains the multi-file HDF interface functions that provide
  information about location and size of raw data.  This type of information
  will allow applications to extract raw data from an HDF file without the
  use of HDF4 library.  These features were developed to support the HDF4
  Mapping project (2010-2011.)

  As with the rest of the functions in the APIs, these functions have names
  beginning with VG, VS, GR, and AN, appropriately.

EXPORTED ROUTINES
-----------------
  VSgetdatainfo    -- retrieves offset(s) and length(s) of a vdata's data
  GRgetdatainfo    -- retrieves offset(s) and length(s) of an image's data
  VSgetattdatainfo -- retrieves offset and length of a vdata attribute's data
  Vgetattdatainfo  -- retrieves offset and length of a vgroup attribute's data 
  GRgetattdatainfo -- retrieves offset and length of an image attribute's data 
  ANgetdatainfo    -- retrieves offset and length of an annotation's data

LOW-LEVEL ROUTINES
------------------
  HDgetdatainfo -- retrieves offset(s) and length(s) of the data in a data element

**********************************************************************/

#ifndef MFGR_MASTER
#define MFGR_MASTER	/* for GRgetdatainfo and GRgetattdatainfo */
#endif			/* mfgr.h had been included in hdf.h */

#ifndef MFAN_MASTER
#define MFAN_MASTER	/* for ANgetdatainfo */
#endif			/* mfan.h is included here */

#include "hdf.h"
#include "hlimits.h"
#include "vgint.h"
#include "mfan.h"

#ifdef H4_HAVE_LIBSZ	/* we have the szip library */
#include "szlib.h"
#endif


/*----------------------------------------------------------------------------- 
 NAME
    HDgetdatainfo -- Retrieves offset(s) and length(s) of the data in a
		     data element.
 USAGE
    intn HDgetdatainfo(file_id, tag, ref, start_block, info_count,
			 *offsetarray, *lengtharray)	
	int32  file_id		IN: file id
	uint16 tag		IN: tag of the element
	uint16 ref		IN: ref of element
	int32 *chk_coord	IN: chunk's coordinates or NULL if not chunked
	uintn  start_block	IN: data block to start at, 0 base
	uintn  info_count	IN: number of info records
	int32 *offsetarray	OUT: array to hold offsets
	int32 *lengtharray	OUT: array to hold lengths
 RETURNS
    Number of data blocks if successful, or FAIL, otherwise.

 DESCRIPTION
    HDgetdatainfo will use low-level functions to get data information
    of element that is in chunk or linked-block storage.

    If the given tag/ref point to:
    - no data then the function will return 0 for number of data blocks,
    - actual data written then the function will return 1 for number of
      data blocks and its offset/length if they are requested, or
    - description record, which means this element is special, then the
      function will act appropriately depend upon the specialness
      + compression
	* if the compressed data is stored in one block, the function will
          return 1 and the offset/length if they are requested
	* if the compressed data is stored in linked-blocks,
	  > read the linked-block special header info
	  > call HLgetdatainfo to get data info of the blocks
      + chunking
	* call HMCgetdatainfo to get data info of the requested chunk
      + linked-block
	* read the linked-block special header info
	* call HLgetdatainfo to get data info of the blocks

 NOTES
    Aug 17, 2010: Tested with SDgetdatainfo and VSgetdatainfo -BMR
    Sep 7, 2010: Tested with GRgetdatainfo, but not linked-block yet -BMR
    Oct 5, 2010: Modified to handle compressed/linked-block element -BMR
--------------------------------------------------------------------------*/
intn
HDgetdatainfo(int32 file_id, uint16 tag, uint16 ref, int32 *chk_coord,
	uintn start_block, uintn info_count, int32 *offsetarray,
	int32 *lengtharray)
{
    CONSTR(FUNC, "HDgetdatainfo");	/* for HGOTO_ERROR */
    filerec_t  *file_rec;	/* file record */
    uint16	sp_tag;		/* special tag */
    uint16	comp_ref = 0;	/* ref for compressed data or comp header */
    uint16	dtag, dref;	/* description record tag/ref */
    int32	dlen=0, doff=0;	/* offset/length of the description record */
    uint8	lbuf[COMP_HEADER_LENGTH],
		*p=NULL;	/* desc record buffer and a pointer to it */
    atom_t	data_id = FAIL;	/* dd ID of existing element */
    int32	length; /* uncomp data len to check if data had been written */
    intn	count=0;/* num of data blocks returned by getdatainfo funcs */
    uint16	spec_code=0;/* special code: SPECIAL_LINKED, SPECIAL_COMP,... */
    int32	comp_aid=-1;/* compressed element access id */
    intn	ret_value=SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Validate array size */
    if (info_count == 0 && offsetarray != NULL && lengtharray != NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Getting only offsets or lengths is not allowed */
    if ((offsetarray != NULL && lengtharray == NULL) ||
        (offsetarray == NULL && lengtharray != NULL))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Convert file id to file rec and check for validity */
    file_rec = HAatom_object(file_id);
    if (BADFREC(file_rec))
	HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Get access element from dataset's tag/ref */
    if ((data_id=HTPselect(file_rec, tag, ref))!=FAIL)
    {
	/* Get the info pointed to by this dd, which could point to data or
	   description record */
	if (HTPinquire(data_id, &dtag, &dref, &doff, &dlen) == FAIL)
            HGOTO_ERROR(DFE_INTERNAL, FAIL);

        /* Return 0 if no data had been written */
        if (doff == INVALID_OFFSET && dlen == INVALID_LENGTH)
	{
	    /* End access to the element */
	    if (HTPendaccess(data_id) == FAIL)
	        HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);

	    HGOTO_DONE(0);
	}

	/* If the element is not special, that means dataset's tag/ref 
	   specifies the actual data that was written to the dataset, get
	   the offset and length of the data if they were requested */
	if (HTPis_special(data_id)==FALSE)
        {
	    /* Only one data block here, starting offset cannot be > 1 */
	    if (start_block > 1)
		HGOTO_ERROR(DFE_ARGS, FAIL);

	    /* Offset and length are requested by caller */
	    if (offsetarray != NULL && lengtharray != NULL)
	    {
		offsetarray[0] = doff;
		lengtharray[0] = dlen;
	    }
	    count = 1;
        }

	/* If the element is special, get the special info header and decode
	   for special tag to detect compression/chunking/linked blocks */
	else
	{
	    if (HPseek(file_rec, doff) == FAIL)
		HGOTO_ERROR(DFE_SEEKERROR, FAIL);
	    if (HP_read(file_rec, lbuf, (int)2) == FAIL)
		HGOTO_ERROR(DFE_READERROR, FAIL);

	    /* Decode the special tag */
	    p = &lbuf[0];
	    INT16DECODE(p, sp_tag);

	    /* This is a compressed element */
	    if (sp_tag == SPECIAL_COMP)
	    {
		/* Read compression info header */
		if (HP_read(file_rec, lbuf, (int)COMP_HEADER_LENGTH) == FAIL)
		HGOTO_ERROR(DFE_READERROR, FAIL);

		/* Decode header to get data length */
		p = &lbuf[0];
		p = p + 2; /* skip 2byte header_version */
		INT32DECODE(p, length);	/* get _uncompressed_ data length */

		/* No data written */
		if (length == 0)
		{
		    count = 0;
		}
		/* Data had been written, either in contiguous block or more
		   special storage, in which case special code needs to be read */
		else
		{
		    /* Decode for the compression ref# */
		    UINT16DECODE(p, comp_ref);

		    /* Get access to the compression element */
		    if ((comp_aid = HTPselect(file_rec, DFTAG_COMPRESSED, comp_ref)) == FAIL)
		        HGOTO_ERROR(DFE_INTERNAL, FAIL);

		    /* If data had been written in one contiguous block */
		    if (HTPis_special(comp_aid) != TRUE)
		    {
		        /* Only one data block here, starting offset cannot be > 1*/
		        if (start_block > 1)
			    HGOTO_ERROR(DFE_ARGS, FAIL);

		        /* This element is not further special, only compressed,
		           get its offset and length if they are requested */
		        if (offsetarray != NULL && lengtharray != NULL)
		        {
			    int32 off=0, len=0;
			    off = Hoffset(file_id, DFTAG_COMPRESSED, comp_ref);
			    if (off == FAIL)
			        HGOTO_ERROR(DFE_BADOFFSET, FAIL);
			    len = Hlength(file_id, DFTAG_COMPRESSED, comp_ref);
			    if (len == FAIL)
			        HGOTO_ERROR(DFE_BADLEN, FAIL);

			    offsetarray[0] = off;
			    lengtharray[0] = len;
		        }
		        count = 1;
		    }   /* end if */

		    /* This element is further special, read in the special code
		       to see what specialness is and process appropriately */
		    else
		    {
			/* Get offset of the special header */
		        if(HTPinquire(comp_aid, NULL, NULL, &doff, NULL)==FAIL)
		        {
			    HTPendaccess(comp_aid);
			    HGOTO_ERROR(DFE_INTERNAL, FAIL);
		        }
			/* Get to and read the special code from the header */
		        if (HPseek(file_rec, doff) == FAIL)
			    HGOTO_ERROR(DFE_SEEKERROR, FAIL);
		        if (HP_read(file_rec, lbuf, (int)2) == FAIL)
			    HGOTO_ERROR(DFE_READERROR, FAIL);

		        /* Decode special code */
		        p = &lbuf[0];
		        INT16DECODE(p, spec_code);

			/* The element has linked-blocks */
		        if (spec_code == SPECIAL_LINKED)
		        {
			    /* Read the rest of the linked-block info header */
			    if (HP_read(file_rec, lbuf, (int)14) == FAIL)
			        HGOTO_ERROR(DFE_READERROR, FAIL);

			    /* Pass the header info to the linked-block API
			       to get the data info if they are requested or the
			       info count only, otherwise */ 
			    p = &lbuf[0];
			    if (offsetarray != NULL && lengtharray != NULL)
			        count = HLgetdatainfo(file_id, p, start_block,
					info_count, offsetarray, lengtharray);
			    else  /* get number of data blocks only */
			        count = HLgetdatainfo(file_id, p, start_block,
					0, NULL, NULL);
		        } /* this element is also stored in linked blocks */
		    } /* this element is further special */

		    /* Release the compression element */
		    if(HTPendaccess(comp_aid)==FAIL)
		        HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);

		} /* compressed data written */
	    } /* element is compressed */

	    /* This is a chunked element, hand the task over to the chunking
		layer. */
	    else if (sp_tag == SPECIAL_CHUNKED)
	    {
		if (chk_coord != NULL)
		    count = HMCgetdatainfo(file_id, tag, ref, chk_coord,
			    start_block, info_count, offsetarray, lengtharray);
		else /* BMR: check to see what should be done here */
		{
		    fprintf(stderr, "\nERROR>>> Element with tag/ref %d/%d is a chunked element, the chunk's coordinates must be specified\n", tag, ref);
	 	    HGOTO_ERROR(DFE_ARGS, FAIL);
		}
	    }

	    /* Unlimited dimension; extract the number of blocks and the ref #
		of the link table then hand over to linked block layer */
	    else if (sp_tag == SPECIAL_LINKED)
	    {
		/* Read the linked-block info header */
		if (HP_read(file_rec, lbuf, (int)14) == FAIL)
		    HGOTO_ERROR(DFE_READERROR, FAIL);

		/* Pass the header info to the linked-block API to get the data
		   info if they are requested or the info count only */ 
		p = &lbuf[0];
		if (offsetarray != NULL && lengtharray != NULL)
		    count = HLgetdatainfo(file_id, p, start_block, info_count,
			    offsetarray, lengtharray);
		else  /* get data information from the linked blocks */
		    count = HLgetdatainfo(file_id, p, start_block, 0, NULL, NULL);
	    } /* element is SPECIAL_LINKED */
	} /* else, data element is special */

	/* End access to the element */
	if (HTPendaccess(data_id) == FAIL)
	    HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);
    }  /* end if data_id != FAIL */

    else /* HTPselect failed */
        HGOTO_ERROR(DFE_CANTACCESS, FAIL);

    /* Return the number of data blocks */
    ret_value = count;
done:
    if(ret_value == FAIL)   
    { /* Error condition cleanup */
    } /* end if */

    /* Normal function cleanup */
    return ret_value;
} /* HDgetdatainfo */


/*------------------------------------------------------ 
 NAME
    VSgetdatainfo - Gets the offset/length of a vdata's data
 USAGE
    intn VSgetdatainfo(vsid, start_block, info_count, offsetarray, lengtharray)	
	int32  vsid		IN: vdata id
	uintn  start_block	IN: data block to start at, 0 base
	uintn  info_count	IN: number of blocks to be retrieved
	int32 *offsetarray	OUT: array to hold offsets
	int32 *lengtharray	OUT: array to hold lengths
 RETURNS
    The number of data blocks retrieved, if successful and FAIL, otherwise.

 DESCRIPTION
    This function uses the low-level function HDgetdatainfo to 
    get the data info when the vdata is stored in linked-blocks.

 TODO
    - not tested with start_block and info_count
 NOTES
    Aug 17, 2010: Tested some in hdf/test/tdatainfo.c -BMR
----------------------------------------------------------*/
intn 
VSgetdatainfo(int32 vsid, uintn start_block, uintn info_count,
	int32 *offsetarray, int32 *lengtharray)
{
    CONSTR(FUNC, "VSgetdatainfo");
    vsinstance_t *vs_inst = NULL;
    VDATA        *vs = NULL;
    accrec_t     *access_rec;
    intn	  count;
    intn          ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Validate array size */
    if (info_count == 0 && offsetarray != NULL && lengtharray != NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Getting only offsets or lengths is not allowed */
    if ((offsetarray != NULL && lengtharray == NULL) ||
        (offsetarray == NULL && lengtharray != NULL))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Check key is valid vdata */
    if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Get vdata instance */
    if (NULL == (vs_inst = (vsinstance_t *) HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* Get vdata info structure and check it */
    vs = vs_inst->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    /* Get access record of the vdata */
    access_rec = HAatom_object(vs->aid);
    if (access_rec == (accrec_t *) NULL)
	HGOTO_ERROR(DFE_ARGS, FAIL);

    /* If the vdata is empty, return 0 block */
    if (vs->nvertices <= 0)
	HGOTO_DONE(0);

    /* If the vdata is stored in linked-blocks, let the low-level function
       handle it */
    if (access_rec->special == SPECIAL_LINKED)
    {
	/* Application only wants the number of data blocks */
	if (offsetarray == NULL && lengtharray == NULL)
	{
	    count = HDgetdatainfo(vs->f, VSDATATAG, vs->oref, NULL, start_block, info_count, NULL, NULL);
	}
	/* Application only wants the offset and length of the blocks too */
	else
	{
	    count = HDgetdatainfo(vs->f, VSDATATAG, vs->oref, NULL, start_block, info_count, offsetarray, lengtharray);
	}
	if (count == FAIL)
	    HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }

    /* The vdata is stored in contiguous block */
    else
    {
	if (offsetarray != NULL && lengtharray != NULL)
	{
	    int32 off=0, len=0;
	    if ((off = Hoffset(vs->f, VSDATATAG, vs->oref)) == FAIL)
		HGOTO_ERROR(DFE_BADOFFSET, FAIL);
	    if ((len = Hlength(vs->f, VSDATATAG, vs->oref)) == FAIL)
		HGOTO_ERROR(DFE_BADLEN, FAIL);
	    *offsetarray = off;
	    *lengtharray = len;
	}
	count = 1;
    }
    /* Return the number of data blocks */
    ret_value = count;

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */
    } /* end if */
  /* Normal function cleanup */
  return ret_value;
}   /* VSgetdatainfo */


/*----------------------------------------------------------------------------- 
 NAME
    Vgetattdatainfo - Gets the offset/length of the data of a vgroup's attribute
 USAGE
    intn Vgetattdatainfo(vgid, attrindex, *offset, *length)	
	int32  vgid		IN: vgroup id
	intn   attrindex	IN: attribute index
	int32 *offset		OUT: buffer for offset
	int32 *length		OUT: buffer for length
 RETURNS
    The number of data blocks retrieved, which should be 1, if successful
    and FAIL, otherwise.

 DESCRIPTION
    There are two types of attributes for vgroups.  One is the old-style
    that was created using methods other than the standard attribute API
    function Vsetattr, which was introduced after HDF Version 4.0 Release
    2, July 19, 1996.  Without the use of Vsetattr, an application could
    simulate an attribute for a vgroup by creating and writing a vdata
    of class _HDF_ATTRIBUTE and adding that vdata to the vgroup via
    these calls:

    vdata_ref = VHstoredatam(file_id, ATTR_FIELD_NAME, values, size, type,
		 attr_name, _HDF_ATTRIBUTE, order);
    ret_value = Vaddtagref (vgroup_id, DFTAG_VH, vdata2_ref);

    While both types of attributes are stored as vdatas, the vdatas of
    the new-style attributes are saved in a list of attribute tags/refs
    of the vgroup, and the vdatas of the old-style attributes are saved
    as elements of the vgroup.  Because of the different storages, the
    new attribute functions would miss the old-style attributes.

    Two fields are added to the internal structure VGROUP for holding the
    number of old-style attributes and their ref#s.  These fields are set
    by Vnoldattrs when old-style attributes exist in the file.

    When a vgroup has both type of attributes, the two list will be
    combined with the old-style attributes preceeding the new ones.
    The attribute indices will be adjusted accordingly.

    This function uses the API function VSgetdatainfo to get the data
    info of the attribute's data.
    -BMR 2011/3/19
----------------------------------------------------------*/
intn 
Vgetattdatainfo(int32 vgid, intn attrindex, int32 *offset, int32 *length)
{
    CONSTR(FUNC, "Vgetattdatainfo");
    VGROUP *vg;
    vg_attr_t *vg_alist;
    vginstance_t *vg_inst;
    int32 attr_vsid;
    intn adjusted_index;
    intn status;
    intn ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Both buffers must be allocated */
    if (offset == NULL || length == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Validate Vgroup ID */
    if (HAatom_group(vgid) != VGIDGROUP)
       HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Locate vg's index in vgtab */
    if (NULL == (vg_inst = (vginstance_t *)HAatom_object(vgid)))
       HGOTO_ERROR(DFE_VTAB, FAIL);
    if (NULL == (vg = vg_inst->vg))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* Validate arguments */

    if (attrindex < 0)
        HGOTO_ERROR(DFE_BADATTR, FAIL); /* invalid attribute index given */

    adjusted_index = attrindex;
    if (adjusted_index < vg->noldattrs) /* index of old-style attribute */
        vg_alist = vg->old_alist;  /* use old-attr list */
    else if (adjusted_index >= vg->noldattrs &&
             adjusted_index < (vg->nattrs+vg->noldattrs))
                 /* index of new-style attributes */
    {
        /* Adjust the index to accommodate for the old-style attributes
           preceding the new-style attribute list */
        adjusted_index = adjusted_index - vg->noldattrs;
        vg_alist = vg->alist;        /* use new-attr list */
    }
    else /* not that many attrs */
        HGOTO_ERROR(DFE_BADATTR, FAIL);

    if (vg_alist == NULL)
        /* Bad attr list */
        HGOTO_ERROR(DFE_BADATTR, FAIL);

    /* Get vdata holding the attribute */
    if (FAIL == (attr_vsid = VSattach(vg->f, (int32)vg_alist[adjusted_index].aref, "r")))
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);

    /* Get offset and length of attribute's data.  Note that start_block is 0
       and info_count is 1 because attribute's data is only stored in 1 block */
    status = VSgetdatainfo(attr_vsid, 0, 1, offset, length);
    if (status == FAIL)
        HGOTO_ERROR(DFE_GENAPP, FAIL);

    /* Close vdata */
    if (FAIL == VSdetach(attr_vsid))
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);

    /* Return the number of data blocks, which should be 1 */
    ret_value = status;
done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* Vgetattdatainfo */


/*------------------------------------------------------ 
 NAME
    VSgetattdatainfo - Gets the offset/length of the data
		      of a vdata's or vdata field's attribute
 USAGE
    intn VSgetattdatainfo(vsid, findex, attrindex, *offset, *length)	
	int32  vsid		IN: vdata id
	int32  findex		IN: vdata's field index or _HDF_VDATA
	intn   attrindex	IN: attribute index
	int32 *offset		OUT: buffer for offset
	int32 *length		OUT: buffer for length
 RETURNS
    The number of data blocks retrieved, which should be 1, if successful
    and FAIL, otherwise.

 DESCRIPTION
    VSgetattdatainfo retrieves the offset and length of the data that belongs
    to an attribute.  If findex is _HDF_VDATA (or -1), then the attribute is
    associated with the vdata vsid.  If findex is an index of the vdata field,
    then the attribute is one that is associated with the vdata field.  The
    parameter attrindex specifies the attribute's index within the vdata's
    or the field's attribute list.  Thus, its valid value must be within
    [0-nattrs of the associated list].

    VSgetattdatainfo uses VSgetdatainfo once it locates the vdata that stores
    the attribute.
    -BMR 2011/3/19
----------------------------------------------------------*/
intn 
VSgetattdatainfo(int32 vsid, int32 findex, intn attrindex, int32 *offset, int32 *length)
{
    CONSTR(FUNC, "VSgetattdatainfo");
    VDATA *vs;
    vs_attr_t *vs_alist;
    vsinstance_t *vs_inst;
    int32 attr_vsid;
    intn nattrs, idx, a_index, found;
    intn status;
    intn ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Both buffers must be allocated */
    if (offset == NULL || length == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    /* locate vs' index in vstab */
    if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
    if (NULL == (vs = vs_inst->vs))
        HGOTO_ERROR(DFE_NOVS, FAIL);
    if ((findex >= vs->wlist.n || findex < 0) && (findex != _HDF_VDATA))
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
    nattrs = vs->nattrs;

    /* No attrs */
    if (nattrs == 0) HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Index must be positive and less than the number of attributes */
    if (attrindex <0 || attrindex >= nattrs)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    vs_alist = vs->alist;

    /* Bad attr list */
    if (vs_alist == NULL) HGOTO_ERROR(DFE_ARGS, FAIL);

    found = 0;
    a_index = -1;
    for (idx=0; idx<nattrs && found==0; idx++)
    {
	if (vs_alist->findex == findex)
	{
	    a_index++;
	    if (a_index == attrindex)
		found = 1;
        }
	if (!found) vs_alist++;
    }
    /* If this happened, it would have been detected by the check for range
       of attrindex above already, but check it anyway */
    if (!found)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Attribute is found.  Get access to the vdata that stores the attribute's
       data, retrieve the offset and length of the data, then close access. */

    /* Get vdata */
    if (FAIL == (attr_vsid = VSattach(vs->f, (int32)vs_alist->aref, "r")))
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);

    /* Get offset and length of attribute's data.  Note that start_block is 0
       and info_count is 1 because attribute's data is only stored in 1 block */
    status = VSgetdatainfo(attr_vsid, 0, 1, offset, length);
    if (status == FAIL)
        HGOTO_ERROR(DFE_GENAPP, FAIL);

    /* Close vdata */
    if (FAIL == VSdetach(attr_vsid))
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);

    /* Return the number of data blocks, which should be 1 */
    ret_value = status;

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSgetattdatainfo */


/*------------------------------------------------------------ 
 NAME
    GRgetattdatainfo - Gets the offset/length of the data of a
			GR file's or an image's attribute
 USAGE
    intn GRgetattdatainfo(id, attrindex, offset, length)
        int32 id		IN: either GR ID or RI ID
        int32 attrindex		IN: index of the attribute being inquired
        int32 *offset		OUT: buffer for offset
        int32 *length		OUT: buffer for length
 RETURNS
    The number of data blocks retrieved, which should be 1, if successful
    and FAIL, otherwise.

 DESCRIPTION
    GRgetattdatainfo retrieves the location and size of the attribute's data
    and its length.

 MODIFICATION
    Apr 03, 2011: Revised to remove the parameter attrname because, for hmap
        project, it makes sense to just provide the attribute index. -BMR

--------------------------------------------------------------*/
intn 
GRgetattdatainfo(int32 id, int32 attrindex, int32 *offset, int32 *length)
{
    CONSTR(FUNC, "GRgetattdatainfo");
    int32      hdf_file_id;	/* file id */
    int32      attr_vsid;	/* id of vdata that stores the attribute */
    group_t id_group=BADGROUP;	/* temporary group of id */
    gr_info_t *gr_ptr;          /* ptr to the GR information for gr id */
    ri_info_t *ri_ptr;          /* ptr to the image information for ri id */
    at_info_t *at_ptr=NULL;	/* ptr to the attribute information */
    void     **aentry;		/* temp. ptr to the image found */
    TBBT_TREE *search_tree;	/* attribute tree to search through */
    int        found = FALSE;	/* TRUE when the searched attribute is found */
    intn       status = 0; 
    intn       ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Validate index */
    if (attrindex < 0)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Both buffers must be allocated */
    if (offset == NULL || length == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Validate ID */
    id_group = HAatom_group(id);
    if (id_group != RIIDGROUP && id_group != GRIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    
    /* Get attribute info and validate index */

    /* When file ID is given, check index against file's attribute count */
    if (id_group == GRIDGROUP)
      {
          /* locate GR's object in hash table */
          if (NULL == (gr_ptr = (gr_info_t *) HAatom_object(id)))
              HGOTO_ERROR(DFE_GRNOTFOUND, FAIL);

	  /* Check index against file's attribute count */
          if(attrindex >= gr_ptr->gattr_count)
              HGOTO_ERROR(DFE_ARGS, FAIL);

          search_tree = gr_ptr->gattree;
	  hdf_file_id = gr_ptr->hdf_file_id;
      } /* end if */

    /* When raster image ID is given, check index against image's attr count */
    else if (id_group == RIIDGROUP)
      {
          /* locate RI's object in hash table */
          if (NULL == (ri_ptr = (ri_info_t *) HAatom_object(id)))
              HGOTO_ERROR(DFE_RINOTFOUND, FAIL);

	  /* Check index against image's attribute count */
          if(attrindex >= ri_ptr->lattr_count)
              HGOTO_ERROR(DFE_ARGS, FAIL); 
          search_tree = ri_ptr->lattree;
	  hdf_file_id = ri_ptr->gr_ptr->hdf_file_id;
      } /* end if */
    else
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Search for an attribute with the same index */
    aentry = (void **)tbbtfirst((TBBT_NODE *)*search_tree);
    found = FALSE;
    while (!found && (aentry != NULL))
    {
	at_ptr = (at_info_t *)*aentry;
	if (at_ptr == NULL)
	{
	    HGOTO_ERROR(DFE_ARGS, FAIL); 
	}

	/* If index is found, set flag */
	if (at_ptr->index == attrindex)
	    found = TRUE;

	/* Not found, go to the next entry */
	if (!found)
	    aentry = (void **)tbbtnext((TBBT_NODE *)aentry);
    } /* end while */

    /* If the attribute is found, get offset/length of its data */
    if (found)
    {
	/* Get access to the vdata that stores the attribute */
	attr_vsid = VSattach(hdf_file_id, (int32)at_ptr->ref, "r");
	if (attr_vsid == FAIL)
	    HGOTO_ERROR(DFE_CANTATTACH, FAIL);

	/* Get offset and length of attribute's data.  Note that start_block
	   is 0 and info_count is 1 because attribute's data is only stored
	   in 1 block */
	status = VSgetdatainfo(attr_vsid, 0, 1, offset, length);
	if (status == FAIL)
	    HGOTO_ERROR(DFE_GENAPP, FAIL);

	if (FAIL == VSdetach(attr_vsid))
	    HGOTO_ERROR(DFE_CANTDETACH, FAIL);
    }
    ret_value = status; /* should be 1 */

done:
  if(ret_value == 0)   
    { /* Error condition cleanup */
    } /* end if */
  /* Normal function cleanup */
  return ret_value;
}   /* GRgetattdatainfo */


/*--------------------------------------------------------------- 
NAME
    GRgetdatainfo - Gets the offsets/lengths of the data of an image
USAGE
    intn GRgetdatainfo(riid, start_block, info_count, offsetarray, lengtharray)
        int32 riid		IN: raster image ID
	uintn start_block	IN: start retrieving data at
	uintn info_count	IN: number of data blocks to retrieve
	int32 *offsetarray	OUT: buffer for offset(s)
	int32 *lengtharray	OUT: buffer for length(s)
RETURNS
    The number of data blocks retrieved, if successful and FAIL, otherwise.

DESCRIPTION
    This function uses the low-level function HDgetdatainfo to 
    get the data info of an image.

TODO
    - not tested with linked-block element yet
    - need more documentation
----------------------------------------------------------------*/
intn 
GRgetdatainfo(int32 riid, uintn start_block, uintn info_count,
	int32 *offsetarray, int32 *lengtharray)
{
    CONSTR(FUNC, "GRgetdatainfo");
    ri_info_t *ri_ptr;          /* ptr to the image to work with */
    int32 hdf_file_id;		/* short cut for file id */
    int32 length = 0;
    uintn count;
    intn   ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Validate array size */
    if (info_count == 0 && (offsetarray != NULL && lengtharray != NULL))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Getting only offsets or lengths is not allowed */
    if ((offsetarray != NULL && lengtharray == NULL) ||
        (offsetarray == NULL && lengtharray != NULL))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Check the validity of the ID */
    if (HAatom_group(riid) != RIIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Locate RI's object in hash table */
    ri_ptr = (ri_info_t *) HAatom_object(riid);
    if (NULL == ri_ptr)
	HGOTO_ERROR(DFE_RINOTFOUND, FAIL);

    hdf_file_id = ri_ptr->gr_ptr->hdf_file_id;	/* alias for file id */

    /* Check for no data in the image */

    /* If the image has no tag/ref pair assigned to it yet, return 0 for
       info count */
    if(ri_ptr->img_tag==DFTAG_NULL || ri_ptr->img_tag==DFREF_WILDCARD
	|| ri_ptr->img_ref==DFREF_WILDCARD)
    {
        if ((offsetarray != NULL && lengtharray != NULL))
	    *offsetarray = *lengtharray = 0;
	HGOTO_DONE(0);
    }
    /* If the image already had a tag/ref pair, make sure it has actual data,
       if not, return 0 for info count */
    else
    {
	length = Hlength(hdf_file_id, ri_ptr->img_tag, ri_ptr->img_ref);
	if (length == FAIL)
	{
            if ((offsetarray != NULL && lengtharray != NULL))
		*offsetarray = *lengtharray = 0;
	    HGOTO_DONE(0);
	}

        /* If both arrays are NULL, get the number of data blocks and return */
        if ((offsetarray == NULL && lengtharray == NULL))
        {
            count = HDgetdatainfo(hdf_file_id, ri_ptr->img_tag, ri_ptr->img_ref, NULL, start_block, 0, NULL, NULL);
            if (count == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);
        }

        /* Application requests offsets/lengths */
        else
        {
            count = HDgetdatainfo(hdf_file_id, ri_ptr->img_tag, ri_ptr->img_ref, NULL, start_block, info_count, offsetarray, lengtharray);
            if (count == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);
        }
    } /* end else */

    ret_value = count;

done:
  if(ret_value == 0)   
    { /* Error condition cleanup */
    } /* end if */
  /* Normal function cleanup */
  return ret_value;
}   /* GRgetdatainfo */


/*--------------------------------------------------------------- 
NAME
    GRgetpalinfo - Gets the palette data descriptors (DDs) in the
		   file (i.e., palette tags, refs, offsets, and lengths)
USAGE
    intn GRgetpalinfo(gr_id, pal_count, palinfo_array)
        int32 gr_id		IN: GR interface ID
	uintn pal_count		IN: number of palette DDs to get
	hdf_ddinfo_t *palinfo_array	OUT: array of palette DDs
RETURNS
    The number of palette DDs in the file or the actual number of palette
    DDs retrieved, if successful, and FAIL, otherwise.

DESCRIPTION
    If the caller only requests the number of palette tags in the file,
    i.e., when palinfo_array is NULL and pal_count is 0, we will simply
    return the number of palette tags, including both DFTAG_IP8 and
    DFTAG_LUT, without further processing.

    Otherwise, the function will search the file for all tags DFTAG_IP8
    and DFTAG_LUT, then retrieve the palette data information into the
    provided array of structures.

    -BMR 2012/6/19
----------------------------------------------------------------*/
intn 
GRgetpalinfo(int32 gr_id, uintn pal_count, hdf_ddinfo_t *palinfo_array)
{
    CONSTR(FUNC, "GRgetpalinfo");
    gr_info_t *gr_ptr;
    int32 file_id;
    int32 nbytes = 0;
    int32 aid = FAIL;
    intn  idx;
    uintn count;
    intn  ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* check the validity of the GR ID */
    if (HAatom_group(gr_id)!=GRIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* locate GR's object in hash table */
    if (NULL == (gr_ptr = (gr_info_t *) HAatom_object(gr_id)))
        HGOTO_ERROR(DFE_GRNOTFOUND, FAIL);

    file_id = gr_ptr->hdf_file_id; /* alias of the file id */

    /* Validate array size.  Fail when count is a pos number but the array is
       NULL, or when count is a neg number */
    if ((pal_count > 0 && palinfo_array == NULL) || pal_count < 0)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* If only the number of palette tags is interested, return that */
    if (pal_count == 0 && palinfo_array == NULL)
    {
	int32 n_IP8s = 0, n_LUTs = 0;

	n_IP8s = Hnumber(file_id, DFTAG_IP8);
	n_LUTs = Hnumber(file_id, DFTAG_LUT);
	if (n_IP8s == FAIL || n_LUTs == FAIL)
	{   HGOTO_ERROR(DFE_INTERNAL, FAIL); }
	else 
	    return(n_IP8s + n_LUTs);
    }

    /* Application requests data info of palettes.  Start checking tags in
       the file and when a palette tag is encountered, retrieve its DD.  The
       process continues until no more tags/refs in the file or the maxinum
       size of the provided array is reached */
    idx = 0;
    ret_value = aid = Hstartread(file_id, DFTAG_WILDCARD, DFREF_WILDCARD);
    while (ret_value != FAIL && idx < pal_count)
    {
	uint16 tag;

	/* Get tag of this element */
	ret_value = Hinquire(aid, NULL, &tag, NULL,NULL,NULL,NULL,NULL,NULL);
	if (ret_value == FAIL)
	    HGOTO_ERROR(DFE_INTERNAL, FAIL);

	if (tag == DFTAG_IP8 || tag == DFTAG_LUT)
	{ /* a palette tag is found */

	    /* Get the palette's data info */
	    ret_value = Hinquire(aid, NULL, &palinfo_array[idx].tag,
		&palinfo_array[idx].ref, &palinfo_array[idx].length,
		&palinfo_array[idx].offset, NULL, NULL, NULL);
	    if (ret_value == FAIL)
		HGOTO_ERROR(DFE_INTERNAL, FAIL);

	    /* Move to next element in the array */
	    idx++;
	} /* a palette tag is found */

	/* Get next element */
	ret_value = Hnextread(aid, DFTAG_WILDCARD, DFREF_WILDCARD, DF_CURRENT);
    } /* get data info of palettes */

    /* Close access id */
    if (aid != FAIL)
	if (Hendaccess(aid) == FAIL)
	    HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);

    ret_value = idx;

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */
      if (aid != FAIL)
          Hendaccess(aid);
    } /* end if */
  /* Normal function cleanup */
  return ret_value;
}   /* GRgetpalinfo */


/*--------------------------------------------------------------------------
NAME
    ANgetdatainfo -- Gets the offset(s) and length(s) locating the data of
		      the annotation.
USAGE
    int32 ANgetdatainfo(ann_id, *offset, *length)	
	int32  ann_id	IN: annotation ID
	int32 *offset	OUT: buffer for offset
	int32 *length	OUT: buffer for length
RETURNS
    SUCCEED/FAIL

DESCRIPTION
    Annotations have contiguous data, so ANgetdatainfo only needs to use
    Hoffset/Hlength to get the data info of an annotation.
    
NOTES
    Aug 25, 2010: Tested in tdatainfo.c/test_annotation -BMR
--------------------------------------------------------------------------*/
intn
ANgetdatainfo(int32 ann_id,    /* IN: annotation id */
	int32 *offset,	/* OUT: buffer for offset */
	int32 *length)	/* OUT: buffer for length */
{
    CONSTR(FUNC, "ANgetdatainfo");
    filerec_t  *file_rec = NULL;		/* file record pointer */
    ANnode     *ann_node   = NULL;
    int32       file_id = FAIL;
    int32       type;
    int32       ann_key;
    int         newflag = 0;
    uint16      ann_tag;
    uint16      ann_ref;
    intn        ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Both buffers must be allocated */
    if (offset == NULL || length == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Get annotation record */
    ann_node = HAatom_object(ann_id);
    if (NULL == ann_node)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Convert file_id to file rec and check for validity */
    file_id = ann_node->file_id;
    file_rec = HAatom_object(file_id);
    if (BADFREC(file_rec))
        HGOTO_ERROR(DFE_INTERNAL, FAIL);

    /* Get annotation key, type, and ref# */
    ann_key = ann_node->ann_key;
    type    = AN_KEY2TYPE(ann_key);
    ann_ref = AN_KEY2REF(ann_key);

    /* Set type tag */
    switch((int32)type)
      {
      case AN_DATA_LABEL:
          ann_tag = DFTAG_DIL;
          break;
      case AN_DATA_DESC:
          ann_tag = DFTAG_DIA;
          break;
      case AN_FILE_LABEL:
          ann_tag = DFTAG_FID;
          break;
      case AN_FILE_DESC:
          ann_tag = DFTAG_FD;
          break;
      default:
          HE_REPORT_GOTO("Bad annotation type for this call",FAIL);
      }

#ifdef NEED_ELEMENT_TAG_REF
/* Keep these here just in case we end up need the object's tag/ref -BMR */
    /* Get annotation entry so that we can get object's tag/ref later */
    if ((entry = tbbtdfind(file_rec->an_tree[type], &ann_key, NULL)) == NULL)
	HE_REPORT_GOTO("failed to retrieve annotation of 'type' tree", FAIL);

    ann_entry = (ANentry *) entry->data;

    elem_tag = ann_entry->elmtag;
    elem_ref = ann_entry->elmref;
#endif

    /* If annotation exists, try to get offset/length */
    newflag  = ann_node->new_ann;
    if (newflag == 0)
    {
	int32 off=0, len=0;
	if (offset != NULL && length != NULL)
	{
	    off = Hoffset(file_id, ann_tag, ann_ref);
	    if (off == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);
	    len = Hlength(file_id, ann_tag, ann_ref);
	    if (len == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);
	    *offset = off;
	    *length = len;
	}

	/* Because for Data label/description, the object's tag/ref were
	written to the file before the annotation data, 4 bytes must be
	taken into account for them */
	if (ann_tag == DFTAG_DIL || ann_tag == DFTAG_DIA)
	{
	    *offset = *offset + 4;
	    *length = *length - 4;
	}
    }

  done:
    if(ret_value == FAIL)   
      { /* Error condition cleanup */
      } /* end if */
    /* Normal function cleanup */
    return ret_value;
} /* ANgetdatainfo */
