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

/******************************************************************************
FILE
  mfdatainfo.c

  This file contains the multi-file SD interface functions that provide
  information about location and size of raw data.  This type of information
  will allow applications to extract raw data from an HDF file without the
  use of HDF4 library.  These features were developed to support the HDF4
  Mapping project (2010-2011.)

  As with the rest of the SD API, these functions have names beginning with SD.

EXPORTED ROUTINES
-----------------

  SDgetdatainfo       -- retrieves location and size of an SDS' data
  SDgetattdatainfo    -- retrieves location and size of an attribute's data
  SDgetoldattdatainfo -- retrieves location and size of an old-style attribute's data
  SDgetanndatainfo    -- retrieves location and size of an annotation's data

LOCAL ROUTINES
--------------
  get_attr_tag        -- Convert the name of an attribute to its associated hdf tag

 ******************************************************************************/

#include "local_nc.h"

#ifdef HDF

#ifndef DATAINFO_MASTER
#define DATAINFO_MASTER
#endif
#include "mfhdf.h"

#ifdef H4_HAVE_LIBSZ          /* we have the szip library */
#include "szlib.h"
#endif

#ifndef MFSD_INTERNAL
#define MFSD_INTERNAL
#endif

#ifdef MFSD_INTERNAL
/* Local function prototypes */
#include "mfprivate.h"
#endif

PRIVATE intn get_attr_tag(char *attr_name, uint16* attr_tag);

/******************************************************************************
 NAME
    SDgetdatainfo -- Retrieves location and size of data blocks.
 USAGE
    intn SDgetdatainfo(sdsid, chk_coord, start_block, info_count, offsetarray, lengtharray)
  int32 sdsid    IN: dataset ID
  int32 *chk_coord  IN: chunk coord array or NULL for non-chunk SDS
  int32 start_block  IN: indicating where to start reading offsets
  uintn info_count  IN: number of data blocks the arrays can hold
  int32 *offsetarray  OUT: array for offsets
  int32 *lengtharray  OUT: array for lengths
 RETURNS
    The number of data blocks retrieved if successful and FAIL, otherwise.

 DESCRIPTION
    SDgetdatainfo retrieves two lists, one containing offsets to sdsid's data
    blocks and the other containing the lengths of those blocks.

    If start_block is 0, SDgetdatainfo will start getting data info from the
    beginning of the data set's data.  If start_block is greater than the
    number of blocks in the data set's data, SDgetdatainfo will return FAIL.

    When both offsetarray and lengtharray lists are NULL, SDgetdatainfo will
    call HDgetdatainfo passing in NULLs to return the actual number of blocks
    in the data set's data.  Otherwise, it will pass in non-NULL arrays to
    retrieve the offset and length of data blocks in the specified data set.
    The non-NULL lists are assumed to be allocated sufficiently for holding
    info_count values.

    If info_count is larger than the actual number of offsets/lengths starting
    at start_block to the end of the data, then only the actual number
    offsets/lengths will be retrieved.

 MODIFICATION
    BMR - 2010/07/14: Revised to combine SDgetdatainfo and SDgetdatainfo_count

 ******************************************************************************/
intn
SDgetdatainfo(int32 sdsid, int32 *chk_coord, uintn start_block,
        uintn info_count, int32 *offsetarray, int32 *lengtharray)
{
    CONSTR(FUNC, "SDgetdatainfo");    /* for HGOTO_ERROR */
    NC     *handle;
    NC_var *var;
    intn    count = FAIL; /* number of data blocks */
    intn    ret_value = 0;

    /* Clear error stack */
    HEclear();

    /* Validate arguments */

    /* Getting only offsets or lengths is not allowed */
    if ((offsetarray != NULL && lengtharray == NULL) ||
            (offsetarray == NULL && lengtharray != NULL))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Just in case user forgot to allocate buffers */
    if ((offsetarray == NULL && lengtharray == NULL) && (info_count > 0))
        HGOTO_ERROR(DFE_NOTENOUGH, FAIL);

    /* Get NC_var record */
    handle = SDIhandle_from_id(sdsid, SDSTYPE);
    if(handle == NULL || handle->file_type != HDF_FILE)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    if(handle->vars == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    var = SDIget_var(handle, sdsid);
    if(var == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* If the data ref# of the SDS is 0, there is no storage is created yet */
    if (var->data_ref == 0)
    {
        count = 0; /* no blocks */
    }
    else
    {
        /* If both arrays are NULL, get the number of data blocks and return */
        if (offsetarray == NULL && lengtharray == NULL)
        {
            count = HDgetdatainfo(handle->hdf_file, var->data_tag,
                    var->data_ref, chk_coord, start_block, info_count, NULL, NULL);
            if (count == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);
        }

        /* Application requests actual offsets/lengths */
        else
        {
            count = HDgetdatainfo(handle->hdf_file, var->data_tag,
                    var->data_ref, chk_coord, start_block, info_count,
                    offsetarray, lengtharray);
            if (count == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);
        }
    }
    /* Returning number of data blocks */
    ret_value = count;
    done:
    if (ret_value == FAIL)
    { /* Failure cleanup */
    }
    /* Normal cleanup */
    return ret_value;
} /* SDgetdatainfo */


/******************************************************************************
 NAME
    SDgetattdatainfo -- Retrieves location and size of attribute's data.
 USAGE
    intn SDgetattdatainfo(id, attrindex, offset, length)
  int32 id    IN: file ID, SDS ID, or dimension ID
  int32 attrindex    IN: index of the attribute being inquired
  int32 *offset    OUT: offset of attribute's data
  int32 *length    OUT: length of attribute's data
 RETURNS
    The number of data blocks retrieved, which should be 1, if successful
    and FAIL, otherwise.

 DESCRIPTION
    There are attributes created by SD API functions and those created by
    the DFSD API functions.  When the searched attribute was created by the
    SD API, the attribute would be stored in a vdata.  Thus, SDgetattdatainfo
    will use VSgetdatainfo to get the location and length of the attribute's.

    When the searched attribute was created by the DFSD API, it would
    be stored with the SDS via an attribute tag/ref pair.  Refer to
    the function header of SDgetoldattdatainfo for more details.
    The application will need to call SDgetoldattdatainfo to get data
    info for this type of attributes.  Thus, SDgetattdatainfo will
    return to caller with error code DFE_NOVGREP so caller can call
    SDgetoldattdatainfo to get to its attributes directly from the file.

 MODIFICATION
    2010/10/14: Revised to remove the parameter attrname because, for hmap
  project, it makes sense to just provide the attribute index. -BMR

 ******************************************************************************/
intn
SDgetattdatainfo(int32 id, int32 attrindex, int32 *offset, int32 *length)
{
    CONSTR(FUNC, "SDgetattdatainfo");
    NC     *handle;
    NC_var *var;
    NC_dim *dim;
    int32   vg_ref=0,  /* ref# of the VG representing a file, SDS, or dim */
            n_elements,  /* number of elements in the file/SDS/dim vgroup */
            vs_id=-1,  /* VS id, needed while looking for _HDF_ATTRIBUTE */
            vg_id=-1,  /* id of the file/SDS/dimension vgroup */
            var_idx;  /* index of the variable representing the given dim */
    char    vsclass[H4_MAX_NC_CLASS] = "", /* vs class, is it _HDF_ATTRIBUTE? */
            attrname[H4_MAX_NC_CLASS] = "",/* name of the given attribute */
            vsname[H4_MAX_NC_CLASS] = "";  /* vs name to see if it's the inquired attr's name*/
    int32   ntype=0,  /* need these because SDattrinfo doesn't... */
            count=0;  /* ...take NULL pointers for not needed arguments */
    int     ii;
    intn    status,  /* returned value */
    found,  /* TRUE when attribute is found */
    ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Validate arguments */

    /* Both buffers must be allocated */
    if (offset == NULL || length == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Index must be positive */
    if (attrindex < 0)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Get the attribute's name */
    status = SDattrinfo(id, attrindex, attrname, &ntype, &count);

    /* Check if the id given is a file id, or SDS id, or dimension id, and get
       appropriate info structure */
    handle = SDIhandle_from_id(id, CDFTYPE);

    /* not a file id */
    if(handle == NULL)
    {
        /* then check if it's SDS id */
        handle = SDIhandle_from_id(id, SDSTYPE);
        /* not an SDS id */
        if(handle == NULL)
        {
            /* then check if it's a dimension id */
            handle = SDIhandle_from_id(id, DIMTYPE);

            /* not a dimension id either, return with an error */
            if(handle == NULL)
                HGOTO_ERROR(DFE_ARGS, FAIL);

            /* dimension id is given, get the dimension info */
            dim = SDIget_dim(handle, id);
            if(dim == NULL)
                HGOTO_ERROR(DFE_ARGS, FAIL);

            /* look for the variable representing this dimension,
       ie. coordinate variable */
            var_idx = SDIgetcoordvar(handle, dim, id, (int32)0);
            if(var_idx == FAIL)
                HGOTO_ERROR(DFE_ARGS, FAIL);

            /* get the variable object */
            var = NC_hlookupvar(handle, var_idx);
            if(var == NULL)
                HGOTO_ERROR(DFE_ARGS, FAIL);

            /* get the ref number of the vgroup representing this dim */
            vg_ref = var->vgid;

            /* If this dimension is not represented by a vgroup (old dimension,
               HDF 3.2, released in 1993) return to caller with error code
               DFE_NOVGREP so caller can call SDgetoldattdatainfo to get
               to its attributes directly from the file */
            if (vg_ref == 0)
                HGOTO_DONE(DFE_NOVGREP);
        }
        /* SDS id is given */
        else
        {
            /* get the variable record */
            if(handle->vars == NULL)
                HGOTO_ERROR(DFE_ARGS, FAIL);
            var = SDIget_var(handle, id);
            if(var == NULL)
                HGOTO_ERROR(DFE_ARGS, FAIL);

            /* get the reference number of the vgroup representing this SDS */
            vg_ref = var->vgid;

            /* If this data set is not represented by a vgroup (old data set,
               HDF 3.2, released in 1993) return to caller with error code
               DFE_NOVGREP so caller can call SDgetoldattdatainfo to get
               to its attributes directly from the file */
            if (vg_ref == 0)
                HGOTO_DONE(DFE_NOVGREP);
        }
    }
    /* File id is given */
    else
    {
        /* make sure it is an HDF file */
        if(handle->file_type != HDF_FILE)
            HGOTO_ERROR(DFE_ARGS, FAIL);

        /* get the reference number of the vgroup representing the file */
        vg_ref = handle->vgid;

        /* I believe file did not have the case of old pre-defined attributes,
     so no special handling for DFE_NOVGREP here. -BMR 2011/1/11 */

        /* Validate the vgroup ref# */
        if (vg_ref == 0) HGOTO_ERROR(DFE_ARGS, FAIL);
    }

    /* Get access to the vgroup and get the number of elements belong to it */
    vg_id = Vattach(handle->hdf_file, vg_ref, "r");
    if(vg_id == FAIL) 
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);
    n_elements = Vntagrefs(vg_id);
    if (n_elements == FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);

    /* Look through the vgroup for vdatas of class _HDF_ATTRIBUTE.  If one is
       found, check to see if its name matches the searched attribute.  If it
       matches, use VSgetdatainfo to get offset and length of the attribute's
       data, then set flag to terminate the search */
    found = FALSE;
    for (ii = 0; ii < n_elements && !found; ii++) 
    {
        int32 elem_tag, elem_ref;

        /* get current tag/ref */
        if (Vgettagref(vg_id, ii, &elem_tag, &elem_ref) == FAIL)
            HGOTO_ERROR(DFE_INTERNAL, FAIL);

        /* current element is a vdata */
        if(elem_tag == DFTAG_VH) 
        {
            vs_id = VSattach(handle->hdf_file, elem_ref, "r");
            if(vs_id == FAIL) 
                HGOTO_ERROR(DFE_CANTATTACH, FAIL);

            /* get the vdata's class */
            if (VSgetclass(vs_id, vsclass) == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);

            /* current vdata represents an attribute */
            if(!HDstrcmp(vsclass, _HDF_ATTRIBUTE)) 
            {
                /* get the vdata's name */
                if (VSgetname(vs_id, vsname) == FAIL)
                    HGOTO_ERROR(DFE_INTERNAL, FAIL);

                /* the searched attribute if found */
                if (!HDstrcmp(attrname, vsname))
                {
                    intn info_count=0;

                    /* get offset/length of attribute's data */
                    info_count = VSgetdatainfo(vs_id, 0, 1, offset, length);

                    /* attribute data should only be in 1 block */
                    if (info_count != 1) /* attribute data should only be in 1 block */
                        HGOTO_ERROR(DFE_INTERNAL, FAIL);

                    /* set flag to terminate the search, and return info count*/
                    found = TRUE;
                    ret_value = info_count;
                }
            }
            /* Close access to vdata */
            if (VSdetach(vs_id) == FAIL)
                HGOTO_ERROR(DFE_CANTDETACH, FAIL);
            vs_id = -1;
        }
    }
    /* Close access to the vgroup */
    if (Vdetach(vg_id) == FAIL)
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);

    done:
    if (ret_value == FAIL)
    { /* Failure cleanup */
        if (vs_id != -1)
            if (VSdetach(vs_id) == FAIL)
                HGOTO_ERROR(DFE_CANTDETACH, FAIL);
        if (vg_id != -1)
            if (Vdetach(vg_id) == FAIL)
                HGOTO_ERROR(DFE_CANTDETACH, FAIL);
    }
    /* Normal cleanup */

    return ret_value;
} /* SDgetattdatainfo */


/******************************************************************************
 NAME
    get_attr_tag -- Convert the name of a pre-defined attribute to its
         associated hdf tag (Private)
 USAGE
    intn get_attr_tag(attr_name, *attr_tag)
  char *attr_name    IN: name of the luf attributes
  uint16 *attr_tag  OUT: associated tag of luf
 RETURNS
    SUCCEED/FAIL

 DESCRIPTION
    In older files, when there were only pre-defined attributes, an attribute
    was not stored in vdata, but was located by an attribute tag/ref pair,
    which is an element of the group that represents the SDS.  The values of
    the SDS's attribute are followed by the values of its dimensions'
    attributes, each separated by a null character.

    This function gives the associated tag of an attributes so that
    application can use tag/ref to read the attribute string.

 ******************************************************************************/
PRIVATE intn 
get_attr_tag(char *attr_name, uint16* attr_tag)
{
    intn ret_value = SUCCEED;

    if (HDstrcmp(_HDF_LongName, attr_name) == 0)
        *attr_tag = DFTAG_SDL;
    else if (HDstrcmp(_HDF_Units, attr_name) == 0)
        *attr_tag = DFTAG_SDU;
    else if (HDstrcmp(_HDF_Format, attr_name) == 0)
        *attr_tag = DFTAG_SDF;
    else if (HDstrcmp(_HDF_CoordSys, attr_name) == 0)
        *attr_tag = DFTAG_SDC;
    else if ((HDstrcmp(_HDF_ValidMin, attr_name) == 0) ||
            (HDstrcmp(_HDF_ValidMax, attr_name) == 0) ||
            (HDstrcmp(_HDF_ValidRange, attr_name) == 0))
        *attr_tag = DFTAG_SDM;
    else if (HDstrcmp(_FillValue, attr_name) == 0)
        *attr_tag = DFTAG_FV;
    else if ((HDstrcmp(_HDF_CalibratedNt, attr_name) == 0)
            || (HDstrcmp(_HDF_ScaleFactor, attr_name) == 0)
            || (HDstrcmp(_HDF_ScaleFactorErr, attr_name) == 0)
            || (HDstrcmp(_HDF_AddOffset, attr_name) == 0)
            || (HDstrcmp(_HDF_AddOffsetErr, attr_name) == 0))
        *attr_tag = DFTAG_CAL;
    /* We need to decide how to handle this attribute when we see it...
    else 
            case DFTAG_SDLNK:
     */
    else
    {
        ret_value = FAIL;
        fprintf(stderr, "get_attr_tag: attr_name = <%s> is not recognized currently\n", attr_name);
    }
    return ret_value;
} /* get_attr_tag */

/******************************************************************************
 NAME
    SDgetoldattdatainfo -- Retrieves location and size of old predefined
         attribute's data.
 USAGE
    intn SDgetoldattdatainfo(id, sdsid, attr_name, offset, length)
  int32 dim_id    IN: dimension ID
  int32 sdsid    IN: ID of dataset the dim belongs to
  char *attr_name    IN: name of the attribute being inquired
  int32 *offset    OUT: buffer for offset
  int32 *length    OUT: buffer for length
 RETURNS
    The number of data blocks retrieved, which should be 1, if successful
    and FAIL, otherwise.

 DESCRIPTION
    In some older files, when data sets and dimensions were not stored as
    vgroup yet, the pre-defined attributes that belong to the data sets
    and dimensions were written as followed:
  attr_tag/attr_ref specify offset and length of the attribute string
  such as:
    "<SDS attribute values>null<dim0 attribute values>null<dim1 attribute values>null..."

  Some examples of attr_tag are: (refer to htags.h for more)
  DFTAG_SDL for Labels attribute
  DFTAG_SDU for Units attribute
  ...

    SDgetoldattdatainfo retrieves the offset and length of the attribute that
    belongs to a data set or a dimension.  Note that only Label, Units, and
    Format (LUF) are applicable to dimensions.  The other attributes are only
    available to the data set.

 DESIGN NOTE:
    This function could be modified to return lists of offsets and lengths
    for attributes of data set and dimension in one call, in the case of LUF.
    That approach would reduce the need to go over the attribute strings
    multiple times for each dimension.  However, it is pending on how the map
    writer uses the function. -BMR (2011/1/13)  It seemed to suit the writer
    so we stay with this design at this time. -BMR (2011/3/1)

 MODIFICATION
    2011/1/11: Revised to handle offset/length of SDS' attribute too. -BMR

 ******************************************************************************/
intn
SDgetoldattdatainfo(int32 dim_id, int32 sdsid, char  *attr_name,
        int32 *offset, int32 *length)
{
    CONSTR(FUNC, "SDgetoldattdatainfo");
    NC     *handle;
    NC_var *var;
    int32   off, len,
    dim_att_len=0,
    sdsluf_len=0,
    offp = 0;
    char   *lufbuf=NULL, *lufp=NULL;
    uint16  att_tag, att_ref;
    intn    dimidx_infile=0, dimidx_invar=0;
    intn    isdim = 0;
    int     ii;
    intn    status,  /* returned value */
    ret_value = 0;

    /* Clear error stack */
    HEclear();

    /* Both buffers must be allocated */
    if (offset == NULL || length == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Attribute name must be provided */
    if (attr_name == NULL || attr_name[0] == '\0')
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Check if a dimension ID is given then set flag */
    handle = SDIhandle_from_id(dim_id, DIMTYPE);
    if(handle != NULL)
        isdim = 1;

    /* Check if the given dataset ID really is a dataset ID; dataset ID
       must always be available */
    handle = SDIhandle_from_id(sdsid, SDSTYPE);
    if(handle == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Get the variable object of the dataset */
    var = SDIget_var(handle, sdsid);
    if(var == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* If this variable doesn't have a valid NDG ref, we cannot proceed */
    if (var->ndg_ref == 0)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    att_tag = 0;
    att_ref = var->ndg_ref; /* all elements of this var have the same ref# */

    /* Convert a predefined attribute name into its corresponding HDF tag */
    status = get_attr_tag(attr_name, &att_tag);
    if (status == FAIL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    if (att_tag != 0 && att_ref != 0)
    {
        /* Get offset/length of the attribute values. */
        off = Hoffset(handle->hdf_file, att_tag, att_ref);
        if (off == FAIL)
            HGOTO_ERROR(DFE_BADOFFSET, FAIL);

        len = Hlength(handle->hdf_file, att_tag, att_ref);
        if (len == FAIL)
            HGOTO_ERROR(DFE_BADLEN, FAIL);

        /* If the attribute pointed to by "off" and "len" is a LUF string, which
         includes LUFs of the data set and its dimensions all together, then
         parse the string to obtain offsets/lengths of the data set's LUF and
         of the dimensions' LUFs.
         Otherwise, return "off" and "len" for the inquired attribute. */

        if (att_tag != DFTAG_SDL && att_tag != DFTAG_SDU && att_tag != DFTAG_SDF)
        {
            *offset = off;
            *length = len;
            HGOTO_DONE(1);
        }

        if (len == 0)
        {
            HGOTO_DONE(0);
        }

        /* Read the luf string */
        lufbuf = (char *)HDmalloc(len+1);
        if (lufbuf == NULL)
            HGOTO_ERROR(DFE_NOSPACE, FAIL);
        Hgetelement(handle->hdf_file, att_tag, att_ref, lufbuf);

        /*
         * Parse the luf string to obtain the offset/length of the requested luf
         */
        /* Start at the beginning of the data set's luf */
        lufp = lufbuf;

        /* Get the length of the data set's luf */
        sdsluf_len = HDstrlen(lufbuf);

        /* If data set's attribute is being inquired, then return with offset
         and length of the SDS' attribute's data only */
        if (!isdim)
        {
            *offset = off;
            *length = sdsluf_len;
        }

        /* If a dimension's attribute is being inquired, then continue parsing
         the attribute string to get the appropriate dimension's attribute */
        else
        {
            char *dim_att=NULL; /* to hold a dimension's attribute */

            /* Move cursor forward to the first dimension's attribute */
            lufp += sdsluf_len + 1;

            /* Convert dimension id back to index */
            dimidx_infile = dim_id & 0xffff;

            /* The dimidx_infile is the index of the dimension relative to the
           file.  We need to find the index of dim within the variable */
            dimidx_invar = -1;
            for (ii = 0; ii < var->assoc->count && dimidx_invar != ii; ii++)
                if (var->assoc->values[ii] == dimidx_infile)
                    dimidx_invar = ii;

            /* Walk through each dimension to find requested luf */
            offp = 0; /* offset pointer */
            for (ii = 0; ii <= dimidx_invar; ii++)
            {
                /* NOTE: Should make tests for all cases to make sure all
                     empty attributes are covered -BMR */

                /* If dimension doesn't have attribute, its attr len is 0 */
                if (HDstrlen(lufp) == 0)
                    dim_att_len = 0;
                /* If dimension has attribute, calculate its attr length */
                else
                {
                    dim_att = (char *)HDmalloc(HDstrlen(lufp) + 1);
                    if (dim_att == NULL)
                        HGOTO_ERROR(DFE_NOSPACE, FAIL);

                    /* Extract current dimension's attribute */
                    HDstrcpy(dim_att, (char *) lufp);
                    dim_att[HDstrlen(lufp)] = 0;
                    dim_att_len = HDstrlen(dim_att);
                }

                /* Move forward if this is not the dim we're looking for */
                if (ii != dimidx_invar)
                {
                    /* move cursor forward to the next dimension's attribute */
                    lufp += dim_att_len + 1;  /* <- 1 is for the NULL */

                    /* add the length to the offset so far */
                    offp += dim_att_len + 1;
                }
                if (dim_att != NULL)
                {
                    HDfree(dim_att);
                    dim_att = NULL;
                }
            }

            /* Calculate offset and length of the requested dimension's luf   */
            /* - off: offset where luf string starts, returned by Hoffset     */
            /* - sdsluf_len: length of the dataset luf + 1 for the null space */
            /* - offp: offset accummulated of all dimension lufs before the   */
            /*   requested one */
            *offset = off + sdsluf_len + 1 + offp;
            *length = dim_att_len;
        }
        ret_value = 1;
    }
    if (lufbuf) HDfree(lufbuf);

    done:
    if (ret_value == FAIL)
    { /* Failure cleanup */
        if (lufbuf) HDfree(lufbuf);
    }
    /* Normal cleanup */

    return ret_value;
} /* SDgetoldattdatainfo */


/******************************************************************************
 NAME
    SDgetanndatainfo -- Retrieves location and size of annotations' data.
 USAGE
    intn SDgetanndatainfo(sdsid, annot_type, size, offsetarray, lengtharray)
  int32 sdsid    IN: SDS ID
  ann_type annot_type  IN: type of annotations to retrieve data info
  uintn size    IN: size of offsetarray and lengtharray
  int32 *offsetarray  OUT: offsets of annotations' data
  int32 *lengtharray  OUT: lengths of annotations' data
 RETURNS
    The number of annotation data info retrieved, if successful
    and FAIL, otherwise.

 DESCRIPTION
    SDgetanndatainfo retrieves the location and size specifying data of the
    annotations of the specified type from the dataset.  There may be more
    than one annotations, but each annotation has only one block of data.

 IMPORTANT NOTE
    If caller provides buffers that are smaller than the number of annotations
    then SDgetanndatainfo only fills the buffers up to its size, and returns
    the number of annotations retrieved.  That means, the rest of the
    annotations are not retrievable.  However, this function is designed for
    hmap writer at this point, and such insufficient buffers situation is not
    anticipated, beside the fact that we're running out of time.  In the future,
    or when such need arises, the function should be modified to include
    another parameter to allow retrieving partial annotations.
    -BMR 2011/1/9

 ******************************************************************************/
intn SDgetanndatainfo(int32 sdsid, ann_type annot_type, uintn size, int32* offsetarray, int32* lengtharray)
{
    CONSTR(FUNC, "SDgetanndatainfo");
    int32   file_id=FAIL,  /* file, AN API, annotation IDs */
            an_id=FAIL,
            ann_id=FAIL;
    NC     *handle = NULL;  /* file structure */
    NC_var *var = NULL;    /* variable structure of sds, to get NDG ref */
    int32  *dannots = NULL,  /* list of data annotation IDs */
            n_flabels = 0,  /* number of file labels */
            n_fdescs = 0,  /* number of file descriptions */
            n_dlabels = 0,  /* number of object labels */
            n_ddescs = 0;  /* number of file descriptions */
    uint16  elem_tag, elem_ref; /* tag/ref of dataset's NDG */
    intn    num_annots,    /* number of annotation of requested type */
    ii,
    ret_value = 0;

    /* Clear error stack */
    HEclear();

    /* Validate array size */
    if (size == 0 && (offsetarray != NULL && lengtharray != NULL))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Getting only offsets or lengths is not allowed */
    if ((offsetarray != NULL && lengtharray == NULL) ||
            (offsetarray == NULL && lengtharray != NULL))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Check if the given id is a file id */
    handle = SDIhandle_from_id(sdsid, CDFTYPE);

    /* It is a file id, process its annotations appropriately */
    if (handle != NULL)
    {
        /* Open file to start Annotation inteface */
        if ((file_id = Hopen(handle->path, DFACC_READ, 0)) == FAIL)
            HGOTO_ERROR(DFE_BADOPEN, FAIL);
        if ((an_id = ANstart(file_id)) == FAIL)
            HGOTO_ERROR(DFE_CANTINIT, FAIL);

        /* Validate annotation type */
        if (annot_type != AN_FILE_LABEL && annot_type != AN_FILE_DESC)
            HGOTO_ERROR(DFE_ARGS, FAIL);

        /* Get numbers of file annotations */
        ret_value = ANfileinfo(an_id, &n_flabels, &n_fdescs, &n_dlabels, &n_ddescs);
        if (ret_value == FAIL)
            HGOTO_ERROR(DFE_INTERNAL, FAIL);

        if (annot_type == AN_FILE_LABEL)
            num_annots = n_flabels;
        else
            num_annots = n_fdescs;

        if (num_annots < 0)
            HGOTO_ERROR(DFE_INTERNAL, FAIL);

        /* If offsets and lengths are not desired, return the number of annots */
        if (offsetarray == NULL || lengtharray == NULL)
            HGOTO_DONE(num_annots);

        /* If more annotations than space in user's buffers, only fill up buffers */
        if ((uintn)num_annots > size)
            num_annots = size;

        /* Get offset/length of each annotation of the specified type */
        for (ii = 0; ii < num_annots; ii++)
        {
            intn status;

            /* Get access to an annotation of the specified type */
            ann_id = ANselect(an_id, ii, annot_type);
            if (ann_id == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);

            /* Get annotation's offset and length */
            ret_value = ANgetdatainfo(ann_id, &offsetarray[ii], &lengtharray[ii]);
            /* Close the annotation (now, just in case ANgetdatainfo failed) */
            status = ANendaccess(ann_id);

            if (ret_value == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);

            if (status == FAIL)
                HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);
        }
    }
    /* Not a file ID */
    else
    {
        /* Check if the given dataset ID really is a dataset ID */
        handle = SDIhandle_from_id(sdsid, SDSTYPE);
        if(handle != NULL)
        {
            /* Validate annotation type */
            if (annot_type != AN_DATA_LABEL && annot_type != AN_DATA_DESC)
                HGOTO_ERROR(DFE_ARGS, FAIL);

            /* Get the NDG ref of this dataset */
            elem_ref = SDidtoref(sdsid);
            elem_tag = DFTAG_NDG;

            /* If this var doesn't have a valid NDG ref, we cannot proceed */
            if (elem_ref <= 0)
                HGOTO_ERROR(DFE_ARGS, FAIL);

            /* Open file to start Annotation inteface */
            if ((file_id = Hopen(handle->path, DFACC_READ, 0)) == FAIL)
                HGOTO_ERROR(DFE_BADOPEN, FAIL);
            if ((an_id = ANstart(file_id)) == FAIL)
                HGOTO_ERROR(DFE_CANTINIT, FAIL);

            /* Get number of data descs or labels with this tag/ref */
            num_annots = ANnumann(an_id, annot_type, elem_tag, elem_ref);
            if (num_annots == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL)
                else if (num_annots == 0) /* then try SDG */
                {
                    elem_tag = DFTAG_SDG;
                    num_annots = ANnumann(an_id, annot_type, elem_tag, elem_ref);

                    /* If there are no SDG annotations either then return 0 */
                    if (num_annots == 0)
                        HGOTO_DONE(0);
                }

            /* If offsets/lengths are not desired, return the number of annots */
            if (offsetarray == NULL || lengtharray == NULL)
                HGOTO_DONE(num_annots);

            /* If more annotations than space in user's buffers, only fill up buffers */
            if (num_annots > size)
                num_annots = size;

            /* Allocate space for list of annotation IDs on this tag/ref */
            if ((dannots = (int32 *)HDmalloc(num_annots * sizeof(int32))) == NULL)
                HGOTO_ERROR(DFE_NOSPACE, FAIL);

            /* Get list of annotations IDs on this tag/ref */
            if (ANannlist(an_id, annot_type, elem_tag, elem_ref, dannots) == FAIL)
                HGOTO_ERROR(DFE_INTERNAL, FAIL);
            /* Note: these ann IDs seem to be closed by HAdestroy_group() but
    I'm not sure.  MFAN needs to take care of them if not. -BMR */

            /* Loop through the annotation list and get their offsets/lengths */
            for (ii = 0; ii < num_annots; ii++)
            {
                /* Get annotation's offset and length */
                ret_value = ANgetdatainfo(dannots[ii], &offsetarray[ii], &lengtharray[ii]);
                if (ret_value == FAIL)
                    HGOTO_ERROR(DFE_INTERNAL, FAIL);
            }
        } /* ID is an SDS */
    } /* Not a file ID */

    /* Return the number of annotations retrieved */
    ret_value = num_annots;

    done:
    if (ret_value == FAIL)
    { /* Failure cleanup */
    }
    /* Normal cleanup */

    /* Release allocated memory */
    if (dannots) HDfree(dannots);

    /* Terminate access to the AN API and close the file if they are opened */
    if(an_id != FAIL)
        ANend(an_id);
    if(file_id != FAIL)
        Hclose(file_id);

    return ret_value;
} /* SDgetanndatainfo */

#endif /* HDF */
