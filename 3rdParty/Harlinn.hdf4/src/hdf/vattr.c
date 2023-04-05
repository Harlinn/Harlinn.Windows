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

/**************************************************************
*
* vattr.c
*
* Handles vgroup and vdata attributes 
*
* Up to HDF4.0r2 vdata and vgroup version number is VSET_VERSION, 
* defined as 3 in vg.h. With attributes or large fields
*   or other new features, version number will be 4, VSET_NEW_VERSION. 
* Attributes will be stored in vdatas. All attributes of a vgroup
*    or a vdata will be included in the vgroup or the vdata header. 
*
* Changes in the vdata header in HDF files :
*    if attr or other new features are assigned:
*      o version number will be VSET_NEW_VERSION (4, 
*          defined in vg.h)
*      o the new DFTAG_VH looks like:
*            
*        interlace  number_records hdf_rec_size n_fields
*          2 bytes        4              2           2
*        datatype_field_n offset_field_n order_field_n fldnmlen_n
*          2*n_fields        2*n_fields     2*n_fields  2*n_fields
*        fldnm_n namelen name classlen class extag exref version
*                  2            2             2     2      2
*        more  flags  < nattrs  attr0_tag/ref attr1_tag/ref ...> 
*         2      4         4         2/2            2/2          
*        <other new featrues >  version  more extra_byte
*                                 2       2      1 
*
*      o To make version number accessible without parsing the 
*           variable length of new feature list, a dublicated
*           version number and 3 bytes (the 'more' and the extra
*           byte) will be added at the end of the VH. See below.
*           The new code (version 4 or later) will get the 
*           version number from the bottom
*           while the old libraries get the version number from the
*           middle of VH, after the field list and before the new 
*           features list. The new features will be ignored by the 
*           old library. Also, since the old libraries ignore
*           the extra byte, there is no need to have the extra
*           byte after the middle 'more' field.  
*      o Add a field "flags" of  uint32, 
*            bit 0 -- has attr
*            bit 1 -- "large field"  <not implemented >
*            bit 2 -- "interlaced data is appendable" <not impl'ed>
*            bit 3-15  -- unused.
*      o Fields follow the flags are:
*            number_of_attrs this vdata has  (4 bytes)
*            attr_index_list  (#_attrs * 8 bytes (4+2+2))
*                 (field_n, avdtag, avdref) 
*        the flags and attribute fields are added between the 
*            middle version field and the bottom version field.
*    if no new features:
*        version number is still VSET_VERSION  and the old VH
*             will be written out.
*
* Changes in the vgroup data in HDF files :
*    If has attribute(s):
*       o add a flag field, uint16,
*           bit 0 -- has attr
*           bit 1-15  -- unused.
*       o version number will be changed to 4 
*       o fields following the flag are:
*           number_of_attrs 
*           vg_attr_list
*         the above fields are added preceding the version field
*       o don't remove the current undocumented "Slush/Mistake byte"
*         This byte is hard coded in vpackvg and vunpackvg. 
*            in order to get version number which can be 
*            either 3 or 4, the extra byte must be there )
*    If no attribute:
*       version number is still 3
*       No changes in vgroup data
*
* Create 2 new types in vg.h:
*     typedef struct dyn_vsattr_struct 
*        {
*            int32 field_n -- which field of the vdata. 0 for the 
*                              entire vdata.
*            uint16 atag, aref  -- tag/ref of the attr vdata
*         } vs_attr_t;
*          (If there are too many attrs and performance becomes a 
*           problem, the vs_attr_t listed above can be replaced by an
*           array of attr lists, each list contains attrs for 1 field.)
*     typedef struct dyn_vgattr_struct
*        {
*            uint16 atag, aref  -- tag/ref of the attr vdata
*         } vg_attr_t;
*
* Changes in the internal structure VDATA:
*     add fields:
*         uint32  flags;
*         int32   nattrs;
*         vd_attr_t *alist;
*         intn new_h_sz;  --  set to 1 when VH size changed 
*
* Changes in the internal structure VGROUP:
*     add fields:
*         uint32 flags;
*         int32  nattrs;
*         vg_attr_t *alist;
*
* New routines:
*   intn VSfindex(int32 vsid, char *fieldname, int32 *findex)
*        find out the index of a field given the field name.
*   intn VSsetattr(int32 vsid, int32 findex, char *attrname, 
*                  int32 datatype, int32 count, void * values)
*        set attr for a field of a vdata or for the vdata.
*        if the attr already exists the new values will replace
*           the current ones as far as the datatype and order
*           are not changed.
*   intn VSnattrs(int32 vsid)
*        total number of attr for a vdata and its fields
*   int32 VSfnattrs(int32 vsid, int32 findex) 
*        number of attrs for a vdata or a field of it
*   intn VSfindattr(int32 vsid, int32 findex, char *attrname)
*        get index of an attribute with a given name
*   intn VSattrinfo(int32 vsid, int32 findex, intn attrindex,
*                   char *name, int32 *datatype, int32 *count,
                    int32 *size);
*        get info about an attribute
*   intn VSgetattr(int32 vsid, int32 findex, intn attrindex, 
*                  void * values)
*        get values of an attribute
*   intn VSisattr(int32 vsid)
*        test if a vdata is an attribute of other object
*   < int32 VSgetversion(int32 vsid) already defined in vio.c >
*   <    get vset version of a vdata  >
*   intn Vsetattr(int32 vgid,  char *attrname, int32 datatype,
*                 int32 count, void * values) 
*        set attr for a vgroup
*   intn Vnattrs(int32 vgid)
*        number of attrs for a vgroup
*   intn Vnattrs2(int32 vgid)
*        number of attrs for a vgroup, also including attrs created prior
*        to the availability of Vdata and Vgroup attribute API routines
*   intn Vfindattr(int32 vgid, char *attrname)
*        get index of an attribute with a given name
*   intn Vattrinfo(int32 vgid, intn attrindex, char *name, 
*                  int32 *datatype, int32 *count, int32 *size)
*        get info about an attribute
*   intn Vattrinfo2(int32 vgid, intn attrindex, char *name, 
*                  int32 *datatype, int32 *count, int32 *size)
*        get info about an attribute - this function processes attributes
*	 that are counted by Vnattrs2.
*   intn Vgetattr(int32 vgid, intn attrindex, void * values)
*        get values of an attribute
*   intn Vgetattr2(int32 vgid, intn attrindex, void * values)
*        get values of an attribute - this function processes attributes
*	 that are counted by Vnattrs2.
*   int32 Vgetversion(int32 vgid)
*        get vset version of a vgroup
* Private routines:
*
* Affected existing functions:
*    vgp.c:vunpackvg--VPgetinfo
*    vgp.c:VPgetinfo--Load_vfile--vinitialize
*    vgp.c:vpackvg--Vdetach
*    vgp.c:Vattach
*    vgp.c:Vdestroynode--Remove_file--Vfinish
*    vio.c:VSPgetinfo--Load_vfile--vinitialize 
*    vio.c:vpackvs
*    vio.c:vunpackvs
*    vio.c:VSdetach
*    vio.c:VSattach
*    vio.c:VSdestroynode
*    vconv.c:Vimakecompat--vmakecompat (no change. compat to ver. 3)
*    
* First draft on 7/31/96, modified on 8/6/96, 8/15/96
*************************************************************/

#define VSET_INTERFACE
#include "hdf.h"

/* -----------------  VSfindex ---------------------
NAME
      VSfindex -- find index of a named field in a vdata
USAGE
      intn VSfindex(int32 vsid, char *fieldname, int32 *findex)
      int32 vsid;    IN: vdata id which contains this field
      const char *fieldname; IN: field name
      int32 *findex; OUT: field index
RETURNS
      Returns SUCCEED if successful;
              FAIL otherwise.
DESCRIPTION
      This routine searchs field names only. It doesn't
      search the vdata name.  Use VSinquire() or VSgetname()
      to find vdata name. 
---------------------------------------------------- */
intn VSfindex(int32 vsid, const char *fieldname, int32 *findex)
{
     CONSTR(FUNC, "VSfindex");
     vsinstance_t *vs_inst;
     VDATA *vs;
     DYN_VWRITELIST *w;
     int32 nflds;
     int32 ret_value = SUCCEED;
     intn i, found = 0;

     HEclear();
     if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

     /* locate vs' index in vstab */
     if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
     vs = vs_inst->vs;
     w = &vs->wlist;
     nflds = w->n;
     for (i=0; i<nflds; i++)   {
#ifdef VDATA_FIELDS_ALL_UPPER
         if (matchnocase(fieldname, w->name[i]))
             { 
               found = 1;
               *findex = i;
               break;
             }
#else
         if (HDstrcmp(fieldname, w->name[i]) == 0)
             { 
               found = 1;
               *findex = i;
               break;
             }
#endif /* VDATA_FIELDS_ALL_UPPER */
     }         
     if (!found)  
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */
      
    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}       /* VSfindex */

/* -------------- VSsetattr ---------------------------------
NAME
   VSsetattr -- Set attribute for a vdata or a field of a
                     vdata
USAGE
   intn VSsetattr(int32 vsid, int32 findex, char *attrname,
                 int32 datatype, int32 count, void * values)
   int32 vsid;     IN: vdata access id
   int32 findex; IN: number determined by assinging each field 
                       in a record a number starting with 0; 
                       _HDF_VDATA (-1) represents the entire vdata. 
   const char *attrname;   IN: name of the attribute
   int32 datatype;   IN: data type of the attribute
   int32 count;      IN: number of values the attribute has
   const void * values;     IN: a buffer which contains the values of 
                           the attribute
RETURNS
   Returns SUCCEED if successful, FAIL otherwise.
DESCRIPTION
   Create a vdata to store this attribute.
   If the field already has an attribute with the same name,
   replace the current values with the new values if the 
   new data type and order are the same as the current ones;
   changes in data type or order will be considered as errors.
   No limit on max number of attributes. (int32 is the final
   limit.)
-----------------------------------------------------------  */
intn VSsetattr(int32 vsid, int32 findex, const char *attrname,
                 int32 datatype, int32 count, const void * values)
{
     CONSTR(FUNC, "VSsetattr");
     vsinstance_t *vs_inst, *attr_inst;
     VDATA    *vs, *attr_vs;
     DYN_VWRITELIST *w, *attr_w;
     intn i;
     int32 nattrs, ret_value = SUCCEED;
     int32 attr_vs_ref, fid, attr_vsid;

     HEclear();

     /* check if id is valid vdata */
     if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

     /* check for null attribute name */
     if (attrname == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

     /* locate vs' index in vstab */
     if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
     if (NULL == (vs = vs_inst->vs))
        HGOTO_ERROR(DFE_NOVS, FAIL);

     /* check for read access */
     if (vs->access == 'r')
        HGOTO_ERROR(DFE_BADATTACH, FAIL);

     w = &(vs->wlist);
     /* check field index */
     if ((findex >= w->n || findex < 0) && (findex != _HDF_VDATA))
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
     /* if the attr already exist for this field, check data type
        and order */
     nattrs = vs->nattrs;
     fid = vs->f; /* assume attrs are in the same file */
     if (nattrs && vs->alist != NULL)    {
        for (i=0; i<nattrs; i++)  {
            if (vs->alist[i].findex == findex) {
               attr_vs_ref = (int32)vs->alist[i].aref;
               attr_vsid = VSattach(fid, attr_vs_ref, "w");
               if (attr_vsid == FAIL)
                  HGOTO_ERROR(DFE_CANTATTACH, FAIL);
               if (NULL == (attr_inst=(vsinstance_t *)HAatom_object(attr_vsid)))
                  HGOTO_ERROR(DFE_NOVS, FAIL);
               if (NULL == (attr_vs = attr_inst->vs))
                  HGOTO_ERROR(DFE_BADPTR, FAIL);
               if (HDstrcmp(attr_vs->vsname, attrname) == 0)  {
                   attr_w = &attr_vs->wlist;
                   if (attr_w->n != 1 || datatype != attr_w->type[0] ||
                      count != attr_w->order[0])   {
                         VSdetach(attr_vsid);
                         HGOTO_ERROR(DFE_BADATTR, FAIL);
                    }  /* type or order changed */
                   /* replace the values  */
                   if (1 != VSwrite(attr_vsid, values, 1, FULL_INTERLACE)) {
                       VSdetach(attr_vsid);
                       HGOTO_ERROR(DFE_VSWRITE, FAIL);
                   }
                   if (FAIL == VSdetach(attr_vsid))
                       HGOTO_ERROR(DFE_CANTDETACH, FAIL);
                   HGOTO_DONE(SUCCEED); 
               }  /* attr exist */
               if (FAIL == VSdetach(attr_vsid))
                  HGOTO_ERROR(DFE_CANTDETACH, FAIL);
            } /* if findex */
        }   /* for loop, not exists */ 
     }
     /* create a vdata to store the attribute */
     if (FAIL == (attr_vs_ref = VHstoredatam(fid, ATTR_FIELD_NAME, 
           values, 1, datatype, attrname,  _HDF_ATTRIBUTE, count)))
        HGOTO_ERROR(DFE_VSCANTCREATE, FAIL);
     /* add this attr to vs->alist */
     if (vs->alist == NULL)    {
        if (vs->nattrs > 0)
           HGOTO_ERROR(DFE_BADATTR, FAIL); 
        vs->alist=(vs_attr_t *)HDmalloc(sizeof(vs_attr_t));
     }
     else  
        vs->alist = HDrealloc(vs->alist,(vs->nattrs+1) * sizeof(vs_attr_t));
     if (vs->alist == NULL)  
           HGOTO_ERROR(DFE_NOSPACE, FAIL);
     vs->alist[vs->nattrs].findex = findex;
     vs->alist[vs->nattrs].atag = DFTAG_VH;
     vs->alist[vs->nattrs].aref = (uint16)attr_vs_ref; 
     vs->nattrs++;
     /* set attr flag and  version number */
     vs->flags = vs->flags | VS_ATTR_SET;
     vs->version = VSET_NEW_VERSION;
     vs->marked = 1;
     vs->new_h_sz = 1;
done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* VSsetattr */


/* ------------------ VSnattrs ------------------------ 
NAME
   VSnattrs -- get total number of attributes assigned for
                  this vdata and its fields
USAGE
   intn VSnattrs(int32 vsid);
   int32 vsid;   IN: access id of the vdata
RETURNS
   Returns total number of attributes assigned to this vdata
   and its fields when successful, FAIL otherwise. 
DESCRIPTION
   Use VSfnattrs to get number of attributes for a field
   or for the vdata ifself.
--------------------------------------------------------  */
intn VSnattrs(int32 vsid)
{
    CONSTR(FUNC, "VSnattrs");
    vsinstance_t *vs_inst;
    VDATA *vs;
    int32 ret_value = SUCCEED;
    
     HEclear();
     if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

     /* locate vs' index in vstab */
     if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
     if (NULL == (vs = vs_inst->vs))
        HGOTO_ERROR(DFE_NOVS, FAIL);
     ret_value = vs->nattrs;
done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* VSnattrs */

/* ---------------- VSfnattrs -------------------------
NAME
   VSfnattrs -- get the number of attributes assigned to
                  a vdata or a field of a vdata.
USAGE
   intn VSfnattrs(int32 vsid, int32 findex);
   int32 vsid;   IN: access id of the vdata
   int32 findex; IN: index of the field, 0 based. 
                     Use _HDF_VDATA (-1) for the vdata itself. 
RETURNS
   Returns the number of attributes assigned to 
   the specified field when successful, FAIL otherwise.
DESCRIPTION
   Use VSnattrs to get total number of attributes for all
   fields and the vdata ifself.
--------------------------------------------------------  */
intn VSfnattrs(int32 vsid, int32 findex)
{
    CONSTR(FUNC, "VSfnattrs");
    vsinstance_t *vs_inst;
    VDATA *vs;
    int32 ret_value = SUCCEED;
    vs_attr_t *vs_alist;
    intn i, nattrs, t_attrs;
 
     HEclear();
     if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

     /* locate vs' index in vstab */
     if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
     if (NULL == (vs = vs_inst->vs))
        HGOTO_ERROR(DFE_NOVS, FAIL);
     if ((findex > vs->wlist.n || findex < 0) && (findex != _HDF_VDATA))
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
     t_attrs = vs->nattrs;
     vs_alist = vs->alist;

     nattrs = 0;
     for (i=0; i<t_attrs; i++)  {
         if (vs_alist->findex == findex)  
            nattrs++;
         vs_alist++;
     }
     ret_value = nattrs;
done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* VSfattrs */
              
/* --------------  VSfindattr ---------------------
NAME
   VSfindattr -- get index of an attribute with given name
                      for a field of a vdata or for the vdata itself
USAGE
   intn VSfindattr(int32 vsid, int32 findex, char *attrname)
   int32 vsid;        IN: access id of the vdata
   int32 findex;      IN: index of the field starting from 0;
                          _HDF_VDATA (-1) for the vdata 
   char *attrname;    IN: name of the attr
RETURNS
   Returns the index of the attr when successful, FAIL otherwise.
DESCRIPTION

------------------------------------------------------------  */
intn VSfindattr(int32 vsid, int32 findex, const char *attrname)
{
     CONSTR(FUNC, "VSfindattr");
     VDATA *vs, *attr_vs;
     vsinstance_t *vs_inst, *attr_inst;
     vs_attr_t *vs_alist;
     int32 fid, attr_vsid;
     int32 ret_value = FAIL;
     intn i, nattrs, a_index, found;

     HEclear();
     /* check if id is valid vdata */
     if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

     /* check for null attribute name */
     if (attrname == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

     /* locate vs' index in vstab */
     if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
     if (NULL == (vs = vs_inst->vs))
        HGOTO_ERROR(DFE_NOVS, FAIL);
     if ((findex >= vs->wlist.n || findex < 0) && (findex != _HDF_VDATA))
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
     nattrs = vs->nattrs;
     vs_alist = vs->alist;
     if (nattrs == 0 || vs_alist == NULL)
          /* no attrs or bad attr list */
            HGOTO_ERROR(DFE_ARGS, FAIL);
    fid = vs->f;
    found = 0;
    a_index = -1;  
    for (i=0; i<nattrs; i++)  {
        if (vs_alist->findex == findex)  {
           a_index++; /* index of fld attr */
           if ((attr_vsid = VSattach(fid, (int32)vs_alist->aref, "r")) 
               == FAIL)
               HGOTO_ERROR(DFE_CANTATTACH, FAIL);
           if (HAatom_group(attr_vsid) != VSIDGROUP)  {
               VSdetach(attr_vsid);
               HGOTO_ERROR(DFE_ARGS, FAIL);
           }
           if (NULL == 
              (attr_inst = (vsinstance_t *)HAatom_object(attr_vsid))) {
               VSdetach(attr_vsid);
               HGOTO_ERROR(DFE_NOVS, FAIL);
           }
           if (NULL == (attr_vs = attr_inst->vs) ||
               HDstrncmp(attr_vs->vsclass, _HDF_ATTRIBUTE, 
                             HDstrlen(_HDF_ATTRIBUTE)))  {
               VSdetach(attr_vsid);
               HGOTO_ERROR(DFE_BADATTR, FAIL);
           }
           if (!HDstrcmp(attr_vs->vsname, attrname)) {
               ret_value = a_index;
               found = 1;
           }
           if (VSdetach(attr_vsid) == FAIL)
               HGOTO_ERROR(DFE_CANTDETACH, FAIL);
        }
        if (found)
               break;
        vs_alist++;
    }

done:
    if (ret_value == FAIL)
       { /*  Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */

  return ret_value;
}   /* VSfindattr */

/* ------------- VSattrinfo --------------------------
NAME
   VSattrinfo -- get info of an attribute of a vdata/field
USAGE
   intn VSattrinfo(int32 vsid, int32 findex, intn attrindex,
        char *name, int32 *datatype, int32 *count, int32 *size);
   int32 vsid;      IN: vdata id
   int32 findex;    IN: field index. _HDF_VDATA (-1) for the vdata
   intn attrindex;  IN: which attr of the field/vdata 
                        attrindex is 0-based
   char *name;      OUT: attribute name
   int32 *datatype; OUT: datatype of the attribute
   int32 *count;    OUT: number of values
   int32 *size;     OUT: size of the attr values on local machine
RETURNS
   Returns SUCCEED when successful, FAIL otherwise.
DESCRIPTION
   name, datatype or count can be NULL if which is not interested.
--------------------------------------------------- */
intn VSattrinfo(int32 vsid, int32 findex, intn attrindex, 
     char *name, int32 *datatype, int32 *count, int32 *size)
{

     CONSTR(FUNC, "VSattrinfo");
     VDATA *vs, *attr_vs;
     vs_attr_t *vs_alist;
     vsinstance_t *vs_inst, *attr_inst;
     int32 attr_vsid;
     int32 ret_value = SUCCEED;
     intn i, nattrs, a_index, found;
     DYN_VWRITELIST *w;
     char *fldname;

     HEclear();
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
     if (attrindex <0 || attrindex >= nattrs)
        HGOTO_ERROR(DFE_ARGS, FAIL);
     vs_alist = vs->alist;
     if (nattrs == 0 || vs_alist == NULL)
          /* no attrs or bad attr list */
            HGOTO_ERROR(DFE_ARGS, FAIL);
    found = 0;
    a_index = -1; 
    for (i=0; i<nattrs; i++)  {
        if (vs_alist->findex == findex)  {
           a_index++; 
           if (a_index == attrindex) {
              found = 1;
              break;
           }
        }
        vs_alist++;
    }
    if (!found)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    /* found. get attr info */
    if (FAIL == (attr_vsid = VSattach(vs->f, (int32)vs_alist->aref, "r")))
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);
    if (NULL == (attr_inst = (vsinstance_t *)HAatom_object(attr_vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
    if (NULL == (attr_vs = attr_inst->vs) ||
          HDstrcmp(attr_vs->vsclass,  _HDF_ATTRIBUTE) != 0)
        HGOTO_ERROR(DFE_BADATTR, FAIL);
    if (name) {
       HDstrncpy(name, attr_vs->vsname, HDstrlen(attr_vs->vsname));
       name[HDstrlen(attr_vs->vsname)] = '\0';
    }
    w = &(attr_vs->wlist);
    fldname = w->name[0];
    /* this vdata has 1 field */
    if (w->n != 1 || HDstrcmp(fldname, ATTR_FIELD_NAME))
        HGOTO_ERROR(DFE_BADATTR, FAIL);
    if (datatype) 
        *datatype =  (int32)w->type[0];
    if (count)
        *count = (int32)w->order[0];
    if (size)
        *size = w->order[0] * (DFKNTsize(w->type[0] | DFNT_NATIVE));
    if (FAIL == VSdetach(attr_vsid))
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);
done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* VSattrinfo */

/* ----------------------  VSgetattr --------------------
NAME
   VSgetattr -- get values of a specified attribute
USAGE
   intn VSgetattr(int32 vsid, int32 findex, intn attrindex,
                  void * values)
   int32 vsid;     IN: vdata access id
   int32 findex;   IN: field index; _HDF_VDATA (-1) for vdata
   intn attrindex; IN: attribute index
   void * values;  OUT: buffer holding attribute values.
RETURNS
   Returns SUCCEED if successful, FAIL otherwise
DESCRIPTION

--------------------------------------------------------- */
intn VSgetattr(int32 vsid, int32 findex, intn attrindex,
               void * values)
{
     CONSTR(FUNC, "VSgetattr");
     VDATA *vs, *attr_vs;
     vs_attr_t *vs_alist;
     vsinstance_t *vs_inst, *attr_inst;
     int32 fid, attr_vsid;
     int32 ret_value = SUCCEED;
     intn i, nattrs, a_index, found;
     int32 n_recs, il;
     char fields[FIELDNAMELENMAX+1];

     HEclear();
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
     if (attrindex <0 || attrindex >= nattrs)
        HGOTO_ERROR(DFE_ARGS, FAIL);
     vs_alist = vs->alist;
     if (nattrs == 0 || vs_alist == NULL)
          /* no attrs or bad attr list */
            HGOTO_ERROR(DFE_ARGS, FAIL);
     fid = vs->f;  /* assume attrs are in the same file */
    found = 0;
    a_index = -1; 
    for (i=0; i<nattrs; i++)  {
        if (vs_alist->findex == findex)  {
           a_index++;
           if (a_index == attrindex) {
              found = 1;
              break;
           }
        }
        vs_alist++;
    }
    if (!found)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    /* found. get attr info */
        if ((attr_vsid = VSattach(fid, (int32)vs_alist->aref, "r")) == FAIL)
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);
    if (HAatom_group(attr_vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    /* check correctness of attr vdata */
    if (NULL == (attr_inst = (vsinstance_t *)HAatom_object(attr_vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
    if (NULL == (attr_vs = attr_inst->vs) ||
          HDstrcmp(attr_vs->vsclass,  _HDF_ATTRIBUTE) != 0)
        HGOTO_ERROR(DFE_BADATTR, FAIL);
    if (FAIL == VSinquire(attr_vsid, &n_recs, &il, fields, NULL, NULL))
        HGOTO_ERROR(DFE_BADATTR, FAIL);
    if (HDstrcmp(fields, ATTR_FIELD_NAME) != 0)
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
    /* ready to read */
    if (FAIL == VSsetfields(attr_vsid, fields))
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
    if (FAIL == VSread(attr_vsid, (unsigned char *)values, n_recs, il))
        HGOTO_ERROR(DFE_VSREAD, FAIL);
    if (FAIL == VSdetach(attr_vsid))
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);

done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* VSgetattr */

/* -------------------- VSisattr ----------------------
NAME
   VSisattr -- test if a vdata is an attribute of 
                    other object
USAGE
   intn VSisattr(int32 vsid)
   int32 vsid;    IN: vdata access id
RETURNS
   Returns TRUE if the vdata is an attribute,
   FALSE otherwise
DESCRIPTION

-------------------------------------------------------- */
intn VSisattr(int32 vsid)
{
     CONSTR(FUNC, "VSsetattr");
     vsinstance_t *vs_inst;
     VDATA    *vs;
     int32  ret_value = FALSE;

     HEclear();
     if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FALSE);
     /* locate vs' index in vstab */
     if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FALSE);
     if (NULL == (vs = vs_inst->vs))
        HGOTO_ERROR(DFE_NOVS, FALSE);
     if (HDstrcmp(vs->vsclass,  _HDF_ATTRIBUTE) == 0)
        ret_value = TRUE;
done:
    if (ret_value == FALSE)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* VSisattr */

/* -----------------  Vsetattr  -------------------------
NAME 
   Vsetattr -- set an attribute for a vgroup
USAGE 
   intn Vsetattr(int32 vgid,  char *attrname, int32 datatype,
             int32 count, void * values) 
   int32 vgid;        IN: access id of the vgroup
   char *attrname;    IN: name of the attr
   int32 datatype;    IN: datatype of the attr
   int32 count;       IN: number of values the attr has
   void * values;      IN: values of the attr
RETURNS
   Returns SUCCEED when successful, FAIL otherwise.
DESCRIPTION
   Create a vdata to store this attribute.
   If the vgroup already has an attribute with the same name
      and if the type and order are the same, use the new 
      values to replace the current values. Any changes in 
      datatype or order will be considered as an error.
   No limit on max number of attributes. (int32 is the final
      limit. 
------------------------------------------------------------  */
intn Vsetattr(int32 vgid, const char *attrname, int32 datatype,
              int32 count, const void * values)
{
    CONSTR(FUNC, "Vsetattr");
    VGROUP *vg; 
    VDATA *vs;
    vginstance_t *v;
    vsinstance_t *vs_inst;
    DYN_VWRITELIST *w;
    int32 ret_value = SUCCEED;
    int32 attr_vs_ref,fid, vsid;
    intn i;

    HEclear();

    /* check if id is valid vgroup */
    if (HAatom_group(vgid)!=VGIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* check for null attribute name */
    if (attrname == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* locate vg's index in vgtab */
    if (NULL == (v = (vginstance_t *) HAatom_object(vgid)))
        HGOTO_ERROR(DFE_VTAB, FAIL);

    vg = v->vg;
    if (vg == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    if ((vg->otag != DFTAG_VG) || (vg->access != 'w'))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    if (vg->otag != DFTAG_VG)
      HGOTO_ERROR(DFE_ARGS,FAIL);
    
    fid = vg->f;

    if ((vg->alist != NULL && vg->nattrs == 0) ||
        (vg->alist == NULL && vg->nattrs != 0))
      HGOTO_ERROR(DFE_BADATTR, FAIL);
 
    /* if the attr already exist, check data type and order. */ 
   if (vg->alist != NULL) {
       for (i=0; i<vg->nattrs; i++)  { 
           if ((vsid = VSattach(fid, (int32)vg->alist[i].aref, "w")) == FAIL)
               HGOTO_ERROR(DFE_CANTATTACH, FAIL);
           if (NULL == (vs_inst=(vsinstance_t *)HAatom_object(vsid)))  
               HGOTO_ERROR(DFE_NOVS, FAIL);
           if (NULL == (vs = vs_inst->vs))
               HGOTO_ERROR(DFE_BADPTR, FAIL);
           if (HDstrcmp(vs->vsname, attrname) == 0)  {
               w = &vs->wlist;
               if (w->n != 1 || w->type[0] != datatype ||
                   w->order[0] != count)  {
                        VSdetach(vsid);
                        HGOTO_ERROR(DFE_BADATTR, FAIL);
               }  /* type or order changed */
               /* replace the values  */
               if (1 != VSwrite(vsid, values, 1, FULL_INTERLACE)) {
                   VSdetach(vsid);
                   HGOTO_ERROR(DFE_VSWRITE, FAIL);
               }
               if (FAIL == VSdetach(vsid))
                  HGOTO_ERROR(DFE_CANTDETACH, FAIL);
                  HGOTO_DONE(SUCCEED);
           }  /* attr exist */
           if (FAIL == VSdetach(vsid))
               HGOTO_ERROR(DFE_CANTDETACH, FAIL);
       }   /* for loop, not exists */
    }
    /* create the attr_vdata and insert it into vg->alist */ 
    if ((attr_vs_ref = VHstoredatam(fid, ATTR_FIELD_NAME, 
          values, 1, datatype, attrname, _HDF_ATTRIBUTE, count)) 
         == FAIL)  
        HGOTO_ERROR(DFE_VSCANTCREATE, FAIL); 
    /* add the attr to attr list */
    if (vg->alist == NULL) 
       vg->alist = (vg_attr_t *)HDmalloc(sizeof(vg_attr_t));
    else 
       /* not exist */
       vg->alist = HDrealloc(vg->alist, (vg->nattrs + 1) * sizeof(vg_attr_t));
    if (vg->alist == NULL)
       HGOTO_ERROR(DFE_NOSPACE, FAIL);
    vg->nattrs++;
    vg->flags = vg->flags | VG_ATTR_SET;
    vg->version = VSET_NEW_VERSION;
    vg->alist[vg->nattrs-1].atag = DFTAG_VH;
    vg->alist[vg->nattrs-1].aref = (uint16)attr_vs_ref; 
    vg->marked = 1;
    /* list of refs of all attributes, it is only used when Vattrinfo2 is
       invoked; see Vattrinfo2 function header for info. 2/4/2011 -BMR */
    vg->old_alist = NULL;
    vg->noldattrs = 0;
done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* Vsetattr */

/* -----------------  Vgetversion  -----------------------
NAME 
   Vgetversion -- gets vset version of a vgroup
USAGE 
   int32 Vgetversion(int32 vgid)
   int32 vgid;     IN: vgroup access id
RETURNS
   Returns vset version number if successful, FAIL otherwise.
DESCRIPTION
   Version 4 (VSET_NEW_VERSION) allows attrs.
   Version 2 (VSET_OLD_VERSION) is the old vset (before
             it was merged into HDF3.2?)
   Version 3 (VSET_VERSION) is the version between
             HDF3.2 through HDF4.0r2.

------------------------------------------------------------  */
int32 Vgetversion(int32 vgid)
{
    CONSTR(FUNC, "Vgetversion");
    VGROUP *vg;
    vginstance_t *v;
    int16 vg_version;
    int32 ret_value = FAIL;

    HEclear();
    if (HAatom_group(vgid)!=VGIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* locate vg's index in vgtab */
    if (NULL == (v = (vginstance_t *) HAatom_object(vgid)))
        HGOTO_ERROR(DFE_VTAB, FAIL);

    vg = v->vg;
    if (vg == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);
    vg_version = vg->version;
    ret_value = (int32) vg_version;

done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* Vgetversion */

/* ---------------- Vnattrs ------------------------ 
NAME
   Vnattrs  -- get number of attributes for a vgroup
USAGE
   intn Vnattrs(int32 vgid)
   int32 vgid;    IN: access id of the vgroup
RETURNS
   Returns number of attributes when successful, Fail otherwise.
DESCRIPTION

--------------------------------------------------  */
intn Vnattrs(int32 vgid)
{
    CONSTR(FUNC, "Vnattrs");
    VGROUP *vg;
    vginstance_t *v;
    int32 ret_value = SUCCEED;

    HEclear();
    if (HAatom_group(vgid) != VGIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Locate vg's index in vgtab */
    if (NULL == (v = (vginstance_t *)HAatom_object(vgid)))
        HGOTO_ERROR(DFE_VTAB, FAIL);
    vg = v->vg;
    if (vg == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);
    if (vg->otag != DFTAG_VG)
      HGOTO_ERROR(DFE_ARGS,FAIL);
    ret_value = vg->nattrs;

done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* Vnattrs */


/* ---------------- Vnoldattrs ------------------------ 
NAME
   Vnoldattrs  -- get number of old-style attributes in a vgroup
USAGE
   intn Vnoldattrs(int32 vgid)
   int32 vgid;    IN: access id of the vgroup
RETURNS
   Returns number of old-style attributes when successful, FAIL, otherwise.
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

   Note that a vgroup (and vdata) that has attribute created by Vsetattr
   (and VSsetattr) will have a version number of VSET_NEW_VERSION (4)
   while the other type will have version number of VSET_VERSION (3.)

   While both types of attributes are stored as vdatas, the vdatas of
   the new-style attributes are saved in a list of attribute tags/refs
   of the vgroup, and the vdatas of the old-style attributes are saved
   as elements of the vgroup.  Because of the different storages, the
   new attribute functions would miss the old-style attributes.  Note
   that the attribute in the SD API are created/stored using the old
   approach.  Thus, V API would miss the SD attributes.

   Two new fields are added to the internal structure vgroup_desc,
   noldattrs and old_alist, for holding the number of old-style attributes
   and their ref#s, respectively.  Vnoldattrs calls VSofclass to get
   the number of old-style attributes and their ref numbers, then sets
   these two fields when old-style attributes exist in the file before
   returning the number of old-style attributes to the caller.
   -BMR 2011/2/16

--------------------------------------------------  */
intn Vnoldattrs(int32 vgid)
{
    CONSTR(FUNC, "Vnoldattrs");
    VGROUP *vg;
    vginstance_t *v;
    intn n_old_attrs=0;
    intn ii;
    uint16 *areflist=NULL;
    int32 ret_value = 0;

    HEclear();
    if (HAatom_group(vgid) != VGIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Get number of old-style attributes */
    n_old_attrs = VSofclass(vgid, _HDF_ATTRIBUTE, 0, 0, NULL);

    /* Note: a new attribute is stored in vdata of class _HDF_ATTRIBUTE too, but
       it is only saved in the file as attribute (by tag/ref,) not as an element
       of the vgroup.  Hence, vg->nattrs = 1, but vg->nvelt = 0 -BMR Feb, 2011*/

    /* Store the ref numbers of old-style attributes into the list
       vg->old_alist, for easy access later by Vattrinfo2 and Vgetattr2 */ 
    if (n_old_attrs > 0)
    {
        /* Locate vg's index in vgtab */
        if (NULL == (v = (vginstance_t *)HAatom_object(vgid)))
            HGOTO_ERROR(DFE_VTAB, FAIL);
        vg = v->vg;
        if (vg == NULL)
            HGOTO_ERROR(DFE_BADPTR, FAIL);
        if (vg->otag != DFTAG_VG)
            HGOTO_ERROR(DFE_ARGS,FAIL);

	/* Establish the list of attribute refs if it is not done so already 
	   or if it is outdated. */

	/* temporary list of attr refs to pass into VSofclass */
        areflist = (uint16 *) HDmalloc(sizeof(uint16) * n_old_attrs);
	if (areflist == NULL)
	    HGOTO_ERROR(DFE_NOSPACE, FAIL);

	/* Get ref numbers of old-style attributes belonging to this vg */
	n_old_attrs = VSofclass(vgid, _HDF_ATTRIBUTE, 0, (uintn)n_old_attrs, areflist);
	if (n_old_attrs == FAIL)
            HGOTO_ERROR(DFE_INTERNAL, FAIL);

	/* Do nothing when the list exists and is current */
	if (vg->old_alist != NULL && vg->noldattrs == n_old_attrs)
	{
	    ret_value = vg->noldattrs;
	    HGOTO_DONE(vg->noldattrs);
	}

	/* Either list doesn't exist or exists but is not current */
	else if (vg->noldattrs != n_old_attrs)
	{
	    /* List is outdated, i.e., more old style attributes had been added
	       since the list was established, release it */
	    if (vg->old_alist != NULL)
		HDfree(vg->old_alist);

	    /* Allocate new list */
            vg->old_alist = (vg_attr_t *)HDmalloc(sizeof(vg_attr_t) * (n_old_attrs));
	    if (vg->old_alist == NULL)
		HGOTO_ERROR(DFE_NOSPACE, FAIL);

	} /* not current */

	/* Transfer ref nums to the vg_attr_t list for future accesses */
        for (ii = 0; ii < n_old_attrs; ii++)
	{
	    vg->old_alist[ii].aref = areflist[ii];
	    /* atag is not needed */
	}
	vg->noldattrs = n_old_attrs; /* record number of old-style attrs */

	ret_value = vg->noldattrs;
    } /* there are some old attributes */

done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

    if (areflist != NULL)
	HDfree(areflist);

  /* Normal function cleanup */
  return ret_value;
}  /* Vnoldattrs */


/* ---------------- Vnattrs2 ------------------------ 
NAME
   Vnattrs2  -- get number of old and new attributes for a vgroup
USAGE
   intn Vnattrs2(int32 vgid)
   int32 vgid;    IN: access id of the vgroup
RETURNS
   Returns number of attributes when successful, FAIL, otherwise.
DESCRIPTION
   The returned number of attributes will include:
	1. the attributes created by the Vgroup attribute API
	   routines, that were added starting from Vgroups version
	   VSET_NEW_VERSION, and
	2. the attributes created using the combination of
	   VHstoredatam and Vaddtagref/Vinsert, most likely prior to
	   the availability of the attribute API routines.
   More detailed description is available in the header of Vnoldattrs.

   This function was added specifically to assist the HDF Mapping
   project.  -BMR 2011/2/8

--------------------------------------------------  */
intn Vnattrs2(int32 vgid)
{
    CONSTR(FUNC, "Vnattrs2");
    intn n_new_attrs=0, n_old_attrs=0;
    int32 ret_value = SUCCEED;

    HEclear();

    /* Get number of new-style attributes */
    n_new_attrs = Vnattrs(vgid);
    if (n_new_attrs == FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);

    /* Get number of old-style attributes */
    n_old_attrs = Vnoldattrs(vgid);
    if (n_old_attrs == FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);

    /* Total number of attributes */
    ret_value = n_old_attrs + n_new_attrs;

done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */
  /* Normal function cleanup */
  return ret_value;
}  /* Vnattrs2 */


/* -----------------  Vfindattr  -----------------------
 NAME
   Vfindattr -- get index of an attribute with given name
 USAGE
   intn Vfindattr(int32 vgid, char *attrname)
   int32 vgid;        IN: access id of the vgroup
   const char *attrname;    IN: name of the attr
 RETURNS
   Returns the index of the attr when successful, FAIL otherwise. 
 DESCRIPTION
------------------------------------------------------------  */
intn Vfindattr(int32 vgid, const char *attrname)
{
    CONSTR(FUNC, "Vfindattr");
    VGROUP *vg;
    VDATA *vs;
    vginstance_t *v;
    vsinstance_t *vs_inst;
    int32 fid, vsid;
    int32 ret_value = FAIL;
    intn i, found;

    HEclear();

    /* check if id is valid vgroup */
    if (HAatom_group(vgid) != VGIDGROUP)
       HGOTO_ERROR(DFE_ARGS, FAIL);

    /* check for null attribute name */
    if (attrname == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* locate vg's index in vgtab */
    if (NULL == (v = (vginstance_t *)HAatom_object(vgid)))
       HGOTO_ERROR(DFE_VTAB, FAIL);
    vg = v->vg;
    fid = vg->f; 
    if (vg == NULL)
       HGOTO_ERROR(DFE_BADPTR, FAIL);
    if (vg->otag != DFTAG_VG)
       HGOTO_ERROR(DFE_ARGS, FAIL);
    if (vg->nattrs == 0 || vg->alist == NULL)
          /* no attrs or bad attr list */
            HGOTO_ERROR(DFE_ARGS, FAIL);
    found = 0;
    for (i=0; found == 0 && i<vg->nattrs; i++)  {
        if ((vsid = VSattach(fid, (int32)vg->alist[i].aref, "r")) == FAIL)
            HGOTO_ERROR(DFE_CANTATTACH, FAIL);
        if (HAatom_group(vsid) != VSIDGROUP)
            HGOTO_ERROR(DFE_ARGS, FAIL);
        if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
            HGOTO_ERROR(DFE_NOVS, FAIL);    
        if (NULL == (vs = vs_inst->vs) ||
            HDstrcmp(vs->vsclass,  _HDF_ATTRIBUTE) != 0)
            HGOTO_ERROR(DFE_BADATTR, FAIL);
        if (0 == HDstrcmp(vs->vsname, attrname)) {
            ret_value = i;
            found = 1;
        }
        if (VSdetach(vsid) == FAIL) 
            HGOTO_ERROR(DFE_CANTDETACH, FAIL);
    }

done:
    if (ret_value == FAIL)
    { /*  Error condition cleanup */
    } /* end if */
  /* Normal function cleanup */

  return ret_value;
}   /* Vfindattr */
        
/* ----------   Vattrinfo ----------------------
NAME
   Vattrinfo -- get info of a vgroup attribute
USAGE
   intn Vattrinfo(int32 vgid, intn attrindex, char *name,
                  int32 *datatype, int32 *count, int32 *size)
   int32 vgid;      IN: vgroup id
   intn attrindex;  IN: which attr's info we want
                             attrindex is 0-based
   char *name;      OUT: attribute name 
   int32 *datatype; OUT: datatype of the attribute
   int32 *count;    OUT: number of values
   int32 *size;     OUT: size of the attr values on local machine.

RETURNS
   Returns SUCCEED when successful, FAIL otherwise.
DESCRIPTION
   name, datatype or count can be NULL if which is
   not interested.
--------------------------------------------------- */
intn Vattrinfo(int32 vgid, intn attrindex, char *name,
             int32 *datatype, int32 *count, int32 *size)
{
    CONSTR(FUNC, "Vattrinfo");
    VGROUP *vg;
    VDATA *vs;
    DYN_VWRITELIST  *w;
/*    char fldname[FIELDNAMELENMAX + 1]; */
    char *fldname;
    vginstance_t *v;
    vsinstance_t *vs_inst;
    int32 fid, vsid;
    int32 ret_value = SUCCEED;

    HEclear();
    if (HAatom_group(vgid) != VGIDGROUP)
       HGOTO_ERROR(DFE_ARGS, FAIL);
    /* locate vg's index in vgtab */
    if (NULL == (v = (vginstance_t *)HAatom_object(vgid)))
       HGOTO_ERROR(DFE_VTAB, FAIL);
    vg = v->vg;
    fid = vg->f;
    if (vg == NULL)
       HGOTO_ERROR(DFE_BADPTR, FAIL);
    if (vg->otag != DFTAG_VG)
       HGOTO_ERROR(DFE_ARGS, FAIL);
    if (vg->nattrs <= attrindex || vg->alist == NULL) 
         /* not that many attrs or bad attr list */
            HGOTO_ERROR(DFE_ARGS, FAIL);
    
    if ((vsid = VSattach(fid, (int32)vg->alist[attrindex].aref, "r")) == FAIL)
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);
    if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
    if (NULL == (vs = vs_inst->vs) ||
          HDstrcmp(vs->vsclass,  _HDF_ATTRIBUTE) != 0)
        HGOTO_ERROR(DFE_BADATTR, FAIL);
    if (name)  {
        HDstrncpy(name, vs->vsname, HDstrlen(vs->vsname));
        name[HDstrlen(vs->vsname)] = '\0';
    }
    w = &(vs->wlist);
    fldname = w->name[0];
    /* this vdata has 1 field */
    if (w->n != 1 || HDstrcmp(fldname, ATTR_FIELD_NAME))  
/*    if (w->n != 1 )   */
        HGOTO_ERROR(DFE_BADATTR, FAIL);
    if (datatype)
       *datatype =  (int32)w->type[0];
    if (count)
       *count = (int32)w->order[0];
    if (size)
       *size = w->order[0] * (DFKNTsize(w->type[0] | DFNT_NATIVE));
    if (FAIL == VSdetach(vsid))
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);
done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* Vattrinfo */


/* ------------ Vattrinfo2 ----------------------
NAME
   Vattrinfo2 -- get info of a vgroup attribute
USAGE
   intn Vattrinfo2(int32 vgid, intn attrindex, char *name,
                  int32 *datatype, int32 *count, int32 *size)
   int32 vgid;      IN: vgroup id
   intn attrindex;  IN: which attr's info we want, attrindex is 0-based
   char *name;      OUT: attribute name 
   int32 *datatype; OUT: datatype of the attribute
   int32 *count;    OUT: number of values
   int32 *size;     OUT: size of the attr values on local machine.

RETURNS
   Returns SUCCEED when successful, FAIL otherwise.
DESCRIPTION
   Vattrinfo2 is an updated version of Vattrinfo.  Both functions return
   the information of an attribute belongging to the given vgroup.
   However, unlike Vattrinfo, which only processes new-style attributes,
   i.e., attributes created by Vsetattr, Vattrinfo2 also handles old-style
   attributes.  In addition, Vattrinfo2 was written to assist the HDF
   Mapping writer.  Thus, it is assumed that Vattrinfo2 is to be used in
   a loop going through all the attributes of the vgroup, including
   old-style and, perhaps, new-style attributes, if they exist.  Refer to
   the function header of Vnattrs2 and Vnoldattrs for more detail.

   If the vgroup has both types of attributes, the old-style attributes 
   will be listed first, hence, the need for Vattrinfo2 to be used in a
   loop.

   Note that Vattrinfo2 must be used in conjunction with Vnattrs2, which
   is an updated version of Vnattrs, or Vnoldattrs, which is invoked by
   Vnattrs2.  Vnoldattrs finds old-style attributes and establishes the
   list of their ref numbers for Vattrinfo2 to access.

   Note that the arguments name, datatype or count can be NULL if which
   is not interested.
   -BMR 2011/2/16
-------------------------------------------------------------- */
intn Vattrinfo2(int32 vgid, intn attrindex, char *name, int32 *datatype,
	int32 *count, int32 *size, int32 *nfields, uint16 *refnum)
{
    CONSTR(FUNC, "Vattrinfo2");
    VGROUP *vg;
    VDATA *vs;
    DYN_VWRITELIST  *w;
    vginstance_t *vg_inst;
    vsinstance_t *vs_inst;
    vg_attr_t *vg_alist=NULL;
    int32 vsid;
    intn adjusted_index;
    int32 ret_value = SUCCEED;

    /* Clear error stack */
    HEclear();

    /* Make sure given object is a vgroup */
    if (HAatom_group(vgid) != VGIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Locate vg's index in vgtab */
    if (NULL == (vg_inst = (vginstance_t *)HAatom_object(vgid)))
       HGOTO_ERROR(DFE_VTAB, FAIL);
    vg = vg_inst->vg;
    if (vg == NULL)
       HGOTO_ERROR(DFE_BADPTR, FAIL);

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

    /* Getting attribute information */

    /* Get access to the vdata storing the attr, and obtain requested info */
    if ((vsid = VSattach(vg->f, (int32)vg_alist[adjusted_index].aref, "r")) == FAIL)
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);
    if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
    if (NULL == (vs = vs_inst->vs) ||
          HDstrcmp(vs->vsclass,  _HDF_ATTRIBUTE) != 0)
        HGOTO_ERROR(DFE_BADATTR, FAIL);
    if (name)  {
        HDstrncpy(name, vs->vsname, HDstrlen(vs->vsname));
        name[HDstrlen(vs->vsname)] = '\0';
    }
    w = &(vs->wlist);
    if (datatype)
       *datatype =  (int32)w->type[0];
    if (count)
       *count = (int32)w->order[0];
    if (size)
       *size = w->order[0] * (DFKNTsize(w->type[0] | DFNT_NATIVE));
    if (nfields)
       *nfields = (int32)w->n; /* Note: int32 to be consistent with VFnfields */
    if (refnum)
       *refnum = vs->oref;
    if (FAIL == VSdetach(vsid))
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);
done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* Vattrinfo2 */

/* ----------  Vgetattr  -----------------------
NAME
   Vgetattr -- read values of a vgroup attribute
USAGE
   intn Vgetattr(int32 vgid, intn attrindex, void * values)
   int32 vgid;      IN: vgroup id
   intn attrindex;  IN: index of the attribute
   void * values;    OUT: where the values go
RETURNS
   Returns SUCCEED when successful, FAIL otherwise
DESCRIPTION

------------------------------------------------- */

intn Vgetattr(int32 vgid, intn attrindex, void * values)
{
    CONSTR(FUNC, "Vgetattr");
    VGROUP *vg;
    VDATA *vs;
    char fields[FIELDNAMELENMAX];
    vginstance_t *v;
    vsinstance_t *vs_inst;
    int32 fid, vsid;
    int32 n_recs, il;
    int32 ret_value = SUCCEED;
    
    HEclear();
    if (HAatom_group(vgid) != VGIDGROUP)
       HGOTO_ERROR(DFE_ARGS, FAIL);
    /* locate vg's index in vgtab */
    if (NULL == (v = (vginstance_t *)HAatom_object(vgid)))
       HGOTO_ERROR(DFE_VTAB, FAIL);
    vg = v->vg;
    fid = vg->f;
    if (vg == NULL)
       HGOTO_ERROR(DFE_BADPTR, FAIL);
    if (vg->otag != DFTAG_VG)
       HGOTO_ERROR(DFE_ARGS, FAIL);
    if (vg->nattrs <= attrindex || vg->alist == NULL) 
          /* not that many attrs or bad attr_Vg tag/ref */
        HGOTO_ERROR(DFE_ARGS, FAIL);
    
    if ((vsid = VSattach(fid, (int32)vg->alist[attrindex].aref, "r")) == FAIL)
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);
    if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);
    /* check correctness of attr vdata */
    if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
    if (NULL == (vs = vs_inst->vs) ||
          HDstrcmp(vs->vsclass,  _HDF_ATTRIBUTE) != 0)
        HGOTO_ERROR(DFE_BADATTR, FAIL);
    if (FAIL == VSinquire(vsid, &n_recs, &il, fields, NULL, NULL))
        HGOTO_ERROR(DFE_BADATTR, FAIL);  
/*    if (HDstrcmp(fields, ATTR_FIELD_NAME) != 0)
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
*/
    /* ready to read */
    if (FAIL == VSsetfields(vsid, ATTR_FIELD_NAME))
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
    if (FAIL == VSread(vsid, (unsigned char *)values, n_recs, il))
        HGOTO_ERROR(DFE_VSREAD, FAIL);
    if (FAIL == VSdetach(vsid))
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);

done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}  /* Vgetattr */

/* ----------  Vgetattr2  -----------------------
NAME
   Vgetattr2 -- read values of a vgroup attribute
		   (updated of Vgetattr)
USAGE
   intn Vgetattr2(int32 vgid, intn attrindex, void * values)
   int32 vgid;      IN: vgroup id
   intn attrindex;  IN: index of the attribute
   void * values;  OUT: buffer for attribute values
RETURNS
   Returns SUCCEED when successful, FAIL otherwise
DESCRIPTION
   This function is an updated version of Vgetattr because,
   beside processing an attribute that was created by the
   Vsetattr, it also reads values of an attribute that was
   created prior to Vsetattr by other method such as the
   combination of VHstoredatam and Vaddtagref/Vinsert.
   More detailed description is available in the function
   header of Vnattrs2 and Vnoldattrs.
   -BMR 2011/2/16
------------------------------------------------- */
intn Vgetattr2(int32 vgid, intn attrindex, void * values)
{
    CONSTR(FUNC, "Vgetattr2");
    VGROUP *vg;
    VDATA *vs;
    char fields[FIELDNAMELENMAX];
    vginstance_t *v;
    vsinstance_t *vs_inst;
    vg_attr_t *vg_alist=NULL;
    intn adjusted_index;
    int32 vsid=-1;
    int32 n_recs, il;
    int32 ret_value = SUCCEED;
    
    /* Clear error stack */
    HEclear();

    /* Make sure given object is a vgroup */
    if (HAatom_group(vgid) != VGIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Locate vg's index in vgtab */
    if (NULL == (v = (vginstance_t *)HAatom_object(vgid)))
       HGOTO_ERROR(DFE_VTAB, FAIL);
    vg = v->vg;
    if (vg == NULL)
       HGOTO_ERROR(DFE_BADPTR, FAIL);

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

    /* Getting attribute information */

    /* Get access to the vdata storing the attr, and obtain requested info */
    if ((vsid = VSattach(vg->f, (int32)vg_alist[adjusted_index].aref, "r")) == FAIL)
        HGOTO_ERROR(DFE_CANTATTACH, FAIL);
    if (HAatom_group(vsid) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Check correctness of attr vdata */
    if (NULL == (vs_inst = (vsinstance_t *)HAatom_object(vsid)))
        HGOTO_ERROR(DFE_NOVS, FAIL);
    if (NULL == (vs = vs_inst->vs) ||
          HDstrcmp(vs->vsclass, _HDF_ATTRIBUTE) != 0)
        HGOTO_ERROR(DFE_BADATTR, FAIL);

    /* Get vdata information */
    if (FAIL == VSinquire(vsid, &n_recs, &il, fields, NULL, NULL))
        HGOTO_ERROR(DFE_BADATTR, FAIL);  

    /* Ready to read */

    /* Some older attribute vdatas have field name as "AttrValues" instead
       of the common "VALUES" (ATTR_FIELD_NAME) so we need to use what was
       read by VSinquire instead of ATTR_FIELD_NAME -BMR 2011/2/11 (I'll look
       for "AttrValues" in previous versions of the library, just in case) */
     /* if (FAIL == VSsetfields(vsid, ATTR_FIELD_NAME))
 */ 
    if (FAIL == VSsetfields(vsid, fields))
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);
    if (FAIL == VSread(vsid, (unsigned char *)values, n_recs, il))
        HGOTO_ERROR(DFE_VSREAD, FAIL);
    if (FAIL == VSdetach(vsid))
        HGOTO_ERROR(DFE_CANTDETACH, FAIL);

done:
    if (ret_value == FAIL)
    { /* Error condition cleanup */
    if (vsid != -1)
        VSdetach(vsid);
    } /* end if */
  /* Normal function cleanup */
  return ret_value;
}  /* Vgetattr2 */

