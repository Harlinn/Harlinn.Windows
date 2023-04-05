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


/*
FILE  
     vg.c
     HDF vdata routines and some vgroup routines

LOCAL ROUTINES
==============
 VSIgetvdatas      -- get vdatas of a specified class or created by user
                      applications, i.e., not created by the library internally
                      for storage.  Currently used by VSgetvdatas and VSofclass.
EXPORTED ROUTINES
=================
     VSelts         -- number of elements in a vdata
     VSgetinterlace -- returns the interlace type of the vdata
     VSsetinterlace -- sets the vdata's interlace to full or none
     VSgetfields    -- returns the fieldnames in a vdata
     VSfexist       -- tests for existence of one or more fields in a vdata
     VSsizeof       -- computes the byte size of the field(s) if a vdata
     VSdump         -- prints contents of a vdata (for debugging)
     VSsetname      -- associate a name with a vdata
     VSsetclass     -- assigns a class name to a vdata
     VSgetname      -- gets the vdata's name
     VSgetclass     -- gets the vdata's class name
     VSinquire      -- gets information about a vdata
     VSisinternal   -- determines if a class name is for internal use only
     VSlone         -- returns an array of refs of all lone vdatas in the file
     Vlone          -- returns an array of refs of all lone vgroups in the file
     Vfind          -- looks in the file for a vgroup with a given name 
     VSfind         -- looks in the file for a vdata with a given name
     Vfindclass     -- looks in the file and returns the ref of 
                       the vgroup with the specified class
     VSfindclass    -- looks in the file and returns the ref of the vdata 
                       with specified class
     VSsetblocksize -- sets the block size of the linked-block element.
     VSsetnumblocks -- sets the number of blocks for a linked-block element.
     VSgetblockinfo -- retrieves the block size and the number of blocks 
		       of a linked-block element.
     Vsetzap        -- maintaind for back compatibility

PRIVATE FUNCTIONS
=================
     matchnocase    -- compares to strings, ignoring case
     vscheckclass   -- checks if a given vdata has the specified class or if
                       it is user-created, which means its class name is not
                       one of the predefined HDF classes.

PRIVATE functions manipulate vsdir and are used only within this file.
PRIVATE data structures in here pertain to vdata in vsdir only.
 */

#define VSET_INTERFACE
#include "hdf.h"

/* These are used to determine whether a vdata had been created by the
   library internally, that is, not created by user's application */
#define HDF_NUM_INTERNAL_VDS	8
const char *HDF_INTERNAL_VDS[] = {DIM_VALS, DIM_VALS01, _HDF_ATTRIBUTE,
	_HDF_SDSVAR, _HDF_CRDVAR, "_HDF_CHK_TBL_", RIGATTRNAME, RIGATTRCLASS};

/* Private functions */
#ifdef VDATA_FIELDS_ALL_UPPER
PRIVATE int32 matchnocase
            (char *strx, char *stry);
#endif /* VDATA_FIELDS_ALL_UPPER */

#ifdef VDATA_FIELDS_ALL_UPPER
/*-----------------------------------------------------------------
NAME
   matchnocase -  (PRIVATE) compares 2 strings, ignoring case 

DESCRIPTION
   Private routine. 

RETURNS
   if strings match return TRUE, 
   else FALSE
--------------------------------------------------------------------*/
PRIVATE int32 
matchnocase(char *strx, /* IN: first string to be compared */
            char *stry  /* IN: second string to be compared */)
{
    int32  i;
    int32  nx, ny; /* length of strings */

    nx = HDstrlen(strx);
    ny = HDstrlen(stry);

    if (nx != ny)
        return (FALSE);     /* different lengths */

    for (i = 0; i < nx; i++, strx++, stry++)
      {
        if (toupper(*strx) != toupper(*stry))
            return (FALSE); /* not identical */
      }

    return (TRUE);
}   /* matchnocase */
#endif /* VDATA_FIELDS_ALL_UPPER */

/* ------------------------------------------------------------------
NAME
   VSelts -- get number of elements in a vdata

DESCRIPTION
   Gets the number of elements in the specified vdata

RETURNS
   On success returns the number of elements in the VDATA vkey; 
   returns FAIL  on error.
--------------------------------------------------------------------- */
int32 
VSelts(int32 vkey /* IN: vdata key */)
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    int32        ret_value = SUCCEED;
    CONSTR(FUNC, "VSelts");

    /* make sure vdata key is part of vdata group */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if ((vs == NULL) || (vs->otag != DFTAG_VH))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* return number of elements in vdata */
    ret_value = (vs->nvertices);

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSelts */

/* ------------------------------------------------------------------
NAME
   VSgetinterlace -- gets interlace of the vdata vkey.

DESCRIPTION
   Gets the interlace scheme for the specified vdata.

RETURNS
   On success returns the interlace scheme used in the fil) of the 
   specified vdata vkey.   returns FAIL on error.
----------------------------------------------------------------------- */
int32 
VSgetinterlace(int32 vkey /* IN: vdata key */)
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    int32        ret_value = SUCCEED;
    CONSTR(FUNC, "VSgetinterlace");

    /* check key is valid vdata */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* return interlace of vdata */
    ret_value = ((int32) (vs->interlace));

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSgetinterlace */

/*------------------------------------------------------------------
NAME
   VSsetinterlace --  sets the vdata's interlace to full or none.

DESCRIPTION
   Sets the interlace scheme for the vdata to one of
   FULL_INTERLACE or NO_INTERLACE.

RETURNS
   SUCCEED/FAIL
--------------------------------------------------------------------*/
intn 
VSsetinterlace(int32 vkey,     /* IN: vdata key */
               int32 interlace /* IN: interlace for storing records */ )
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    intn         ret_value = SUCCEED;
    CONSTR(FUNC, "VSsetinterlace");

    /* check key is valid vdata */
    if (HAatom_group(vkey)!=VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    /* check if only read access, this is a failure */
    if (vs->access == 'r')
        HGOTO_ERROR(DFE_RDONLY, FAIL);

    /* check if records have already been written out,
       cannot reset interlace in this case */
    if (vs->nvertices > 0)
        HGOTO_ERROR(DFE_NORESET, FAIL);

    /* currently only 2 kinds of interlaced schemes allowed. */
    if (interlace == FULL_INTERLACE || interlace == NO_INTERLACE)
      {
          vs->interlace = (int16) interlace;
          ret_value = SUCCEED;    /* ok */
      }
    else
        ret_value = FAIL;

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSsetinterlace */

/*------------------------------------------------------------------
NAME
   VSgetfields -- returns the name (if any) of all the fields in the vdata

DESCRIPTION
   Returns the names of all the fields in comma seperated string in
   the argument 'fields'. (e.g., "PX,PY").

RETURNS
   Returns FAIL on error, 
   else the number of fields in the vdata.
----------------------------------------------------------------------*/
int32 
VSgetfields(int32 vkey,   /* IN: vdata key */
            char *fields  /* OUT: comman seperated field name list */)
{
    int32        i;
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    int32        ret_value = SUCCEED;
    CONSTR(FUNC, "VSgetfields");

    /* check if a NULL field list is passed in, then return with
       error (found while fixing bug #554) - BMR 4/30/01 */
    if (fields == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* check key is valid vdata */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    /* Got through Vdata and build the comman seperated string of field names */
    fields[0] = '\0';
    /* No special handling for 0-field vdatas, this algorithm should work fine. */
    for (i = 0; i < vs->wlist.n; i++)
      {   /* build the comma-separated string */
          HDstrcat(fields, vs->wlist.name[i]);
          if (i < vs->wlist.n - 1)
              HDstrcat(fields, ",");
      }

    /* return number of fields */
    ret_value = ((int32) vs->wlist.n);

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSgetfields */

/*------------------------------------------------------------------
NAME
   VSfexist -- tests for existence of 1 or more fields in a vdata.

DESCRIPTION
   The argument 'fields' is a string of comma-separated fieldnames 
   (e.g. "PX,PY,PZ") to check for in vdata.

RETURNS 
   Returns SUCCEED if all fields exist 
   else otherwise FAIL is returned.
--------------------------------------------------------------------*/
intn 
VSfexist(int32 vkey,  /* IN: vdata key */
         char *fields /* IN: names of fields to check for */)
{
    char          **av = NULL;
    char           *s = NULL;
    DYN_VWRITELIST *w = NULL;
    vsinstance_t   *wi = NULL;
    VDATA          *vs = NULL;
    int32         ac;
    int32         i, j;
    int32         found;
    intn          ret_value = SUCCEED;
    CONSTR(FUNC, "VSfexist");

    /* check key is valid vdata */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (wi = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* call scanattrs to parse the string */
    if (scanattrs(fields, &ac, &av) < 0)
        HGOTO_ERROR(DFE_BADFIELDS, FAIL);

    /* get vdata itself and check it 
       check also that more than one field in 'fields' */    
    vs = wi->vs;
    if ((vs == NULL) || (ac < 1))
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* now check in vdata's field table for these field names */
    w = &vs->wlist;
    for (i = 0; i < ac; i++)
      {
          found = 0;
          s = av[i];
          /* No changes for 0-field Vdatas, this algorithm should work fine. */
          for (j = 0; j < w->n; j++)
            {
#ifdef VDATA_FIELDS_ALL_UPPER
                if (matchnocase(s, w->name[j]))
                  {
                      found = 1;
                      break;
                  }
#else
                if (HDstrcmp(s, w->name[j]) == 0)
                  {
                      found = 1;
                      break;
                  }
#endif /* VDATA_FIELDS_ALL_UPPER */
            }
          if (!found)
            HGOTO_DONE(FAIL);
      }

    ret_value = TRUE;

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}	/* VSfexist */

/* -----------------------------------------------------------------
NAME
   VSsizeof - computes the byte size of the field(s) of a vdata.

DESCRIPTION
   The size is the actual size for the local architecture

RETURNS
   The byte size of the field(s), positive integer, on success; 
   otherwise, returns FAIL.
----------------------------------------------------------------- */
int32 
VSsizeof(int32 vkey,   /* IN vdata key */
         char *fields  /* IN: Name(s) of the fields to check size of */ )
{
    int32       totalsize;
    int32       i, j;
    int32       found;
    int32       ac;
    char        **av = NULL;
    vsinstance_t *w  = NULL;
    VDATA        *vs = NULL;
    int32        ret_value = SUCCEED;
    CONSTR(FUNC, "VSsizeof");

    /* check key is valid vdata */
    if (HAatom_group(vkey)!=VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    totalsize = 0;
    if (fields == NULL) /* default case? */
      {   /* count all field sizes in vdata */
        for (j = 0; j < vs->wlist.n; j++)	
            totalsize += vs->wlist.esize[j];
      }		
    else
      {  /* parse field string */
        if ((scanattrs(fields, &ac, &av) < 0) || (ac < 1))
            HGOTO_ERROR(DFE_ARGS, FAIL);

        for (i = 0; i < ac; i++)
          {   /* check fields in vs */
            for (found = 0, j = 0; j < vs->wlist.n; j++)	
                if (!HDstrcmp(av[i], vs->wlist.name[j]))
                  {
                    totalsize += vs->wlist.esize[j];
                    found = 1;
                    break;
                  }

            if (!found)
                HGOTO_ERROR(DFE_ARGS, FAIL);
          }	/* end for */
      }		/* end else */

    /* return total size of vdata fields specified */
    ret_value = totalsize;

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSsizeof */

/*----------------------------------------------------------------- 
NAME
   VSdump - prints contents of a vdata (for debugging) 

DESCRIPTION
    Prints contents of a vdata (for debugging) 

RETURNS
   No return codes.
-------------------------------------------------------------------*/
VOID 
VSdump(int32 vkey /* IN: vdata key */)
{
    vkey = vkey;    /* suppress warning */
}   /* VSdump */

/*-------------------------------------------------------
NAME
   VSsetname - give a name to a vdata.

DESCRIPTION
   Truncates name to max length of VSNAMELENMAX
   If new name is longer than the current name set new_h_sz,
      so that VSdetach will delete the original vdata header
      and write a new header. 

RETURNS
   SUCCEED/FAIL
----------------------------------------------------------*/
int32 
VSsetname(int32 vkey,        /* IN: Vdata key */
          const char *vsname /* IN: name to set for vdata*/)
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    int32       curr_len;
    int32       slen;
    int32       ret_value = SUCCEED;
    CONSTR(FUNC, "VSsetname");

    /* check key is valid vdata */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* check for null vdata name */
    if (vsname == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    /* get current length of vdata name */
    if (vs->vsname != NULL)
        curr_len = HDstrlen(vs->vsname);

    /* check length of new name against MAX length */
    if ((slen = HDstrlen(vsname)) > VSNAMELENMAX)
      { /* truncate name */
          HDstrncpy(vs->vsname, vsname, VSNAMELENMAX);
          vs->vsname[VSNAMELENMAX] = '\0';
      }
    else /* copy whole name */
        HDstrcpy(vs->vsname, vsname);

    vs->marked = TRUE; /* mark vdata as being modified */

    if (curr_len < slen) 
        vs->new_h_sz = TRUE; /* mark vdata header size being changed */

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSsetname */

/* ------------------------------------------------------
NAME
   VSsetclass - give a class name to a vdata.

DESCRIPTION
   Truncates class name to max length of VSNAMELENMAX
   If new class is longer than the current class set new_h_sz,
   so that VSdetach will delete the original vdata header
   and write a new header.

RETURNS
   SUCCEED/FAIL
----------------------------------------------------------*/
int32 
VSsetclass(int32 vkey,         /* IN: vdata key */
           const char *vsclass /* IN: class name to set for vdata */)
{
    vsinstance_t *w = NULL;
    VDATA       *vs = NULL;
    int32       curr_len;
    int32       slen;
    int32       ret_value = SUCCEED;
    CONSTR(FUNC, "VSsetclass");

    /* check key is valid vdata */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* check for null vdata class */
    if (vsclass == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    /* get current length of vdata class name */
    curr_len = (intn)HDstrlen(vs->vsclass);

    /* check length of new class name against MAX length */
    if ((slen = (intn)HDstrlen(vsclass)) > VSNAMELENMAX)
      {
          HDstrncpy(vs->vsclass, vsclass, VSNAMELENMAX);
          vs->vsclass[VSNAMELENMAX] = '\0';
      }
    else
        HDstrcpy(vs->vsclass, vsclass);

    vs->marked = TRUE; /* mark vdata as being modified */

    if (curr_len < slen)
        vs->new_h_sz = TRUE; /* mark vdata header size being changed */

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSsetclass */

/*------------------------------------------------------ 
NAME
   VSgetname - gets the vdata's name. 

DESCRIPTION
   Get vdata's name and comy it to 'vsname'. Space for
   'vsname' must be allocated by user.

RETURNS
   SUCCEED/FAIL
----------------------------------------------------------*/
int32 
VSgetname(int32 vkey,   /* IN: vdata key */
          char *vsname  /* OUT: vdata name (allocated by user)*/)
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    int32        ret_value = SUCCEED;
    CONSTR(FUNC, "VSgetname");

    /* check key is valid vdata */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* check user allocated space */
    if (vsname == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    /* copy vdata name over */
    HDstrcpy(vsname, vs->vsname);

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSgetname */

/*------------------------------------------------------ 
NAME
   VSgetclass - gets the vdata's class name.

DESCRIPTION
   Get vdata class name and copy over to 'vsclass'. Space
   for 'vsclass' must be allocated by user.

RETURNS
   SUCCEED/FAIL
---------------------------------------------------------- */
int32 
VSgetclass(int32 vkey,    /* IN: vdata key */
           char *vsclass  /* OUT: class name for vdata (allocated by user) */ )
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    int32     ret_value = SUCCEED;
    CONSTR(FUNC, "VSgetclass");

    /* check key is valid vdata */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* check user allocated space */
    if (vsclass == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    /* copy class name over */
    HDstrcpy(vsclass, vs->vsclass);

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSgetclass */

/* ------------------------------------------------------------------ 
NAME
   VSinquire - gets info about a vdata vkey:

DESCRIPTION
   Get information about Vdata. Space for 'fields' and 'vsname'
   must be allocated by user.

RETURNS
   SUCCEED/FAIL

------------------------------------------------------------------------*/
intn 
VSinquire(int32 vkey,       /* IN: vdata key */
          int32 *nelt,      /* OUT: number of elements in vdata */
          int32 *interlace, /* OUT: interlace scheme of vdata */
          char *fields,     /* OUT: comma seperated string of field names */
          int32 *eltsize,   /* OUT: total size of all fields in bytes */
          char *vsname      /* OUT: name of vdata */)
{
  intn ret_value = SUCCEED;
  intn status;
  CONSTR(FUNC, "VSinquire");

    /* check key is valid vdata */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* obtain the value for each parameter although the previous one
       fails; ret_value should be FAIL if any of the parameters fails */
    if (fields)
      { /* we assume 'fields' space has been pre-allocated by user? */
        status = VSgetfields(vkey, fields);
        ret_value = (status == FAIL)? FAIL: ret_value;
      }
    if (nelt)
      {
        *nelt = VSelts(vkey);
        ret_value = (*nelt == FAIL)? FAIL: ret_value;
      }
    if (interlace)
      {
        *interlace = VSgetinterlace(vkey);
        ret_value = (*interlace == FAIL)? FAIL: ret_value;
      }
    if (eltsize)
      {
        *eltsize = VSsizeof(vkey, fields);
        ret_value = (*eltsize == FAIL)? FAIL: ret_value;
      }
    if (vsname)
      { /* we assume 'vsname' space as been pre-allocated by user? */
        status = VSgetname(vkey, vsname);
        ret_value = (status == FAIL)? FAIL: ret_value;
      }

done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
    return ret_value;   /* ok */

}   /* VSinquire */

/*-----------------------------------------------------------------
NAME
   VSlone - returns an array of refs of all lone vdatas in the file.

DESCRIPTION
   If 'idarray' is too small, routine will only fill 'idarray' with up
   to 'asize' worth of refs.

RETURNS
   Returns FAIL if error else returns the total number of lone 
   vdatas in the file.
---------------------------------------------------------------------*/
int32 
VSlone(HFILEID f,     /* IN: file id */
       int32 *idarray,/* OUT: array to return refs of lone vdatas? */
       int32 asize    /* IN: size of 'idarray' */)
{
    int32   i;
    int32   vgid;
    int32   vsid;
    int32   vstag;
    int32   vkey;
    uint8  *lonevdata = NULL;  /* lcl wrk area: stores flags of vdatas */
    int32   nlone;             /* total number of lone vdatas */
    int32   ret_value = SUCCEED;
    CONSTR(FUNC, "VSlone");

    /* -- allocate local space for vdata refs, init to zeros -- */
    if (NULL == (lonevdata = (uint8 *) HDcalloc(MAX_REF , sizeof(uint8))))
        HGOTO_ERROR(DFE_NOSPACE, FAIL);

    /* -- look for all vdatas in the file, and flag (1) each -- */
    vsid = -1;
    while (FAIL != (vsid = VSgetid(f, vsid)))    /* until no more vdatas */
        lonevdata[vsid] = 1;

    /* -- Look through all vgroups, searching for vdatas -- */
    /* -- increment its index in lonevdata if found -- */
    vgid = -1;
    while (FAIL != (vgid = Vgetid(f, vgid)))
      {     /* until no more vgroups */
        vkey = Vattach(f, vgid, "r"); /* attach to vgroup */
        for (i = 0; i < Vntagrefs(vkey); i++)
          {
            Vgettagref(vkey, i, &vstag, &vsid); /* get tag/ref of element in vg */
            if (vstag == (int32) DFTAG_VH)
                lonevdata[vsid] = 0; /* set vdata as not lone vdata */
          }
        Vdetach(vkey); /* detach from vgroup */
      }

    /* -- check in lonevdata: it's a lone vdata if its flag is still 1 -- */
    nlone = 0;
    for (i = 0; i < (int32)MAX_REF; i++)
      {
        if (lonevdata[i])
          { /* insert into idarray up till asize */
            if (nlone < asize)  
                idarray[nlone] = i; /* insert ref of vdata into idarray */
            nlone++;
          }
      }

    /* free up locally allocated space */
    HDfree((VOIDP) lonevdata);

    ret_value = nlone; /* return the TOTAL # of lone vdatas */

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSlone */

/*----------------------------------------------------------------- 
NAME
   Vlone  - returns an array of refs of all lone vgroups in the file.

DESCRIPTION
   If 'idarray' is too small, routine will only fill 'idarray' with up
   to 'asize' worth of refs.

RETURNS
   Returns FAIL if error else returns the total number of lone
   vgroups in the file
---------------------------------------------------------------------*/
int32 
Vlone(HFILEID f,      /* IN: file id */
      int32 *idarray, /* OUT: array to return refs of lone vgroups? */
      int32 asize     /* IN: size of 'idarray' */)
{
    int32       i;
    int32       vgid;
    int32       vstag;
    int32       id;
    int32       vkey;
    uint8      *lonevg = NULL;  /* local wrk area: stores flags of vgroups */
    int32       nlone;          /* total number of lone vgroups */
    int32       ret_value = SUCCEED;
    CONSTR(FUNC, "Vlone");

    /* -- allocate space for vgroup refs, init to zeroes -- */
    if (NULL == (lonevg = (uint8 *) HDcalloc(MAX_REF , sizeof(uint8))))
        HGOTO_ERROR(DFE_NOSPACE, FAIL);

    /* -- look for all vgroups in the file, and flag (1) each -- */
    id = -1;
    while (FAIL != (id = Vgetid(f, id)))     /* until no more vgroups */
        lonevg[id] = 1;

    /* -- Look through all vgs, searching for vgroups -- */
    /* -- increment its index in lonevg if found -- */
    vgid = -1;
    while (FAIL != (vgid = Vgetid(f, vgid)))
      {     /* until no more vgroups */
        vkey = Vattach(f, vgid, "r"); /* attach to vgroup */
        id = -1;
        for (i = 0; i < Vntagrefs(vkey); i++)
          {
            Vgettagref(vkey, i, &vstag, &id); /* get tag/ref of element in vg */
            if (vstag == DFTAG_VG)
                lonevg[id] = 0; /* set vgroup as not lone vgroup */
          }
        Vdetach(vkey); /* detach from vgroup */
      }

    /* -- check in lonevg: it's a lone vgroup if its flag is still 1 -- */
    nlone = 0;
    for (i = 0; i < (int32)MAX_REF; i++)
      {
        if (lonevg[i])
          { /* insert into idarray up till asize */
            if (nlone < asize)  
                idarray[nlone] = i; /* insert ref of vgroup into idarray */
            nlone++;
          }
      }

    /* free up locally allocated space */
    HDfree((VOIDP) lonevg);

    ret_value = nlone; /* return the TOTAL # of lone vgroups */

done:
  if(ret_value == FAIL)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* Vlone */

/* ----------------------------------------------------------------- 
NAME
   Vfind -- looks in the file and returns the ref of 
            the vgroup with name vgname 

DESCRIPTION
   Finds the vgroup with the specified name and returns the ref of
   the vgroup if successful.

RETURNS
   Returns 0 if not found or on error. Otherwise, returns the 
   vgroup's ref (a positive integer).
-----------------------------------------------------------------------*/
int32 
Vfind(HFILEID f,          /* IN: file id */
      const char *vgname  /* IN: name of vgroup to find */)
{
    int32        vgid = -1;
    vginstance_t *v = NULL;
    VGROUP       *vg = NULL;
    int32       ret_value = 0;
    CONSTR(FUNC, "Vfind");

    /* check for null vgroup name */
    if (vgname == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* process through Vgroups in file */
    while (FAIL != (vgid = Vgetid(f, vgid)))
      { /* get instance of vgroup */
        if((v = vginst(f,(uint16)vgid)) == NULL)
            HGOTO_DONE(0);

        /* get vgroup itself and check it */
        vg = v->vg;
        if (vg == NULL)
            HGOTO_DONE(0);

        /* compare vgroup name to 'vgname' if it had been set */
	if (vg->vgname != NULL)
            if (!HDstrcmp(vgname, vg->vgname)) 
                HGOTO_DONE((int32)(vg->oref));  /* found the vgroup */
      }

done:
  if(ret_value == 0)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}	/* Vfind */

/*------------------------------------------------------------------
NAME
   VSfind -- looks in the file and returns the ref of the vdata 
             with name vsname 

DESCRIPTION
   Finds the vdata with the specified name and returns the ref of
   the vdata if successfull.

RETURNS
   Returns 0 if not found, or on error. Otherwise, returns the vdata's 
   ref (a positive integer).
---------------------------------------------------------------------*/
int32 
VSfind(HFILEID f,          /* IN: file id */
       const char *vsname  /* IN: name of vdata to find */)
{
    int32        vsid = -1;
    vsinstance_t *v = NULL;
    VDATA        *vs = NULL;
    int32 ret_value = 0;
    CONSTR(FUNC, "VSfind");

    /* check for null vdata name */
    if (vsname == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* process through Vdatas in file */
    while (FAIL != (vsid = VSgetid(f, vsid)))
      { /* get instance of vdata */
        if((v = vsinst(f,(uint16)vsid)) == NULL)
            HGOTO_DONE(0);

        /* get vdata itself and check it */
        vs = v->vs;
        if (vs == NULL)
            HGOTO_DONE(0);

        /* compare vdata name to 'vsname' if it had been set */
        if (!HDstrcmp(vsname, vs->vsname)) 
            HGOTO_DONE((int32)(vs->oref));  /* found the vdata */
      }

done:
  if(ret_value == 0)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSfind */

/* ----------------------------------------------------------------- 
NAME
   Vfindclass -- looks in the file and returns the ref of 
                 the vgroup with class vgclass 

DESCRIPTION
   Finds the vgroup with the specified class and returns the ref
   of the vgroup if successful.

RETURNS
   Returns 0 if not found, or error. Otherwise, returns the 
   vgroup's ref (a positive integer).
-----------------------------------------------------------------------*/
int32 
Vfindclass(HFILEID f,           /* IN: file id */
           const char *vgclass  /* IN: class of vgroup to find */)
{
    int32        vgid = -1;
    vginstance_t *v = NULL;
    VGROUP       *vg = NULL;
    int32       ret_value = 0;
    CONSTR(FUNC, "Vfindclass");

    /* check for null vgroup class */
    if (vgclass == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* process through Vgroups in file */
    while (FAIL != (vgid = Vgetid(f, vgid)))
      { /* get instance of vgroup */
        if((v = vginst(f,(uint16)vgid)) == NULL)
            HGOTO_DONE(0);

        /* get vgroup itself and check it */
        vg = v->vg;
        if (vg == NULL)
            HGOTO_DONE(0);
	/* Shouldn't we move on to the next vgroup instead of getting out?
	   Same question for the above HGOTO_DONE. -BMR 9/12/2011 */

        /* compare vgroup class to 'vgclass' if it had been set */
	if (vg->vgclass != NULL)
	    if (!HDstrcmp(vgclass, vg->vgclass)) 
		HGOTO_DONE((int32)(vg->oref));  /* found the vgroup */
      }

done:
  if(ret_value == 0)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;    
}	/* Vfindclass */

/*------------------------------------------------------------------
NAME
   VSfindclass -- looks in the file and returns the ref of the vdata 
                  with class vsclass 

DESCRIPTION
   Finds the vdata with the specified class and returns the ref of 
   the vdata if successful.

RETURNS
   Returns 0 if not found, or error. Otherwise, returns the vdata's 
   ref (a positive integer).
---------------------------------------------------------------------*/
int32 
VSfindclass(HFILEID f,           /* IN: file id */
            const char *vsclass  /* IN: class of vdata to find */)
{
    int32        vsid = -1;
    vsinstance_t *v = NULL;
    VDATA        *vs = NULL;
    int32        ret_value = 0;
    CONSTR(FUNC, "VSfindclass");

    /* check for null vdata class */
    if (vsclass == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* process through Vdatas in file */
    while (FAIL != (vsid = VSgetid(f, vsid)))
      { /* get instance of vdata */
        if((v = vsinst(f,(uint16)vsid)) == NULL)
            HGOTO_DONE(0);          /* error */

        /* get vdata itself and check it */
        vs = v->vs;
        if (vs == NULL)
            HGOTO_DONE(0);

        /* compare vdata class to 'vsclass' if it had been set */
        if (!HDstrcmp(vsclass, vs->vsclass)) 
            HGOTO_DONE((int32)(vs->oref));  /* found the vdata */
      }

done:
  if(ret_value == 0)   
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSfindclass */

/* ----------------------------------------------------------------- 
NAME
   VSsetblocksize -- sets the block size of the linked-block element.

DESCRIPTION
   Sets the size of the blocks, that are after the first block, of a 
   linked-block element used for storing a vdata.  This routine is 
   to be called before the first write to the vdata to change the block 
   size from the default value HDF_APPENDABLE_BLOCK_LEN (4096).  Once the
   linked-block element is created, the block size cannot be changed.

RETURNS
   Returns SUCCEED/FAIL

MODIFICATION
   BMR - added in June 2001 to fix bug# 267

---------------------------------------------------------------------*/
intn
VSsetblocksize(	int32 vkey, /* IN: vdata key */
		int32 block_size) /* length to be used for each linked-block */
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    intn        ret_value = SUCCEED;
    CONSTR(FUNC, "VSsetblocksize");

    /* clear error stack */
    HEclear();

    /* check if the given vdata id is part of vdata group */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if ((vs == NULL) || (vs->otag != VSDESCTAG))
      HGOTO_ERROR(DFE_ARGS,FAIL);

    /* internal routine handles the actual setting */
    if (HLsetblockinfo(vs->aid, block_size, -1) == FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);

done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}       /* VSsetblocksize */

/* ----------------------------------------------------------------- 
NAME
   VSsetnumblocks -- sets the number of blocks for a linked-block element.

DESCRIPTION
   Sets the number of blocks of a linked-block element used for storing
   a vdata.  This routine is to be called before the first write to the
   vdata to change the number of blocks from the default value
   HDF_APPENDABLE_BLOCK_NUM (16).  Once the linked-block element is
   created, the number of blocks cannot be changed.

RETURNS
   Returns SUCCEED/FAIL

MODIFICATION
   BMR - added in June 2001 to fix bug# 267

---------------------------------------------------------------------*/
intn
VSsetnumblocks( int32 vkey, /* IN: vdata key */
		int32 num_blocks) /* number of blocks the element can have */
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    intn        ret_value = SUCCEED;
    CONSTR(FUNC, "VSsetnumblocks");

    /* clear error stack */
    HEclear();

    /* check if the given vdata id is part of vdata group */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if ((vs == NULL) || (vs->otag != VSDESCTAG))
      HGOTO_ERROR(DFE_ARGS,FAIL);

    /* internal routine handles the actual setting */
    if (HLsetblockinfo(vs->aid, -1, num_blocks) == FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);

done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}       /* VSsetnumblocks */

/* ----------------------------------------------------------------- 
NAME
   VSgetblockinfo -- retrieves the block size and the number of blocks 
		     of a linked-block element.

DESCRIPTION
   Retrieves the block size and the number of blocks of a linked-block
   element used for storing a vdata.  A NULL can be passed in for
   unwanted value.

RETURNS
   Returns SUCCEED/FAIL

MODIFICATION
   BMR - added in June 2001 to fix bug# 267

---------------------------------------------------------------------*/
intn
VSgetblockinfo(int32 vkey, /* IN: vdata id */
               int32* block_size, /* OUT: length used for each linked-block */
               int32* num_blocks) /* OUT: number of blocks the element has */
{
    vsinstance_t *w = NULL;
    VDATA        *vs = NULL;
    intn        ret_value = SUCCEED;
    CONSTR(FUNC, "VSgetblockinfo");

    /* clear error stack */
    HEclear();

    /* check if vdata is part of vdata group */
    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* get vdata instance */
    if (NULL == (w = (vsinstance_t *) HAatom_object(vkey)))
        HGOTO_ERROR(DFE_NOVS, FAIL);

    /* get vdata itself and check it */
    vs = w->vs;
    if ((vs == NULL) || (vs->otag != VSDESCTAG))
      HGOTO_ERROR(DFE_ARGS,FAIL);

    /* internal routine handles the actual retrieval */
    if (HLgetblockinfo(vs->aid, block_size, num_blocks) == FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);

done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}       /* VSgetblockinfo */

/*******************************************************************************
 NAME
    VSisinternal  --  Determine if a vdata's class name is for internal only

 RETURNS
    Returns TRUE (1) if "classname" is one of the class names used for
    vdata created by the the library and FALSE (0) otherwise.

*******************************************************************************/
intn
VSisinternal(const char *classname)
{
    int  i;
    intn ret_value = FALSE;

    /* Check if this class name is one of the internal class name and return
        TRUE, otherwise, return FALSE */
    for (i=0; i < HDF_NUM_INTERNAL_VDS; i++) {
        if (HDstrncmp(HDF_INTERNAL_VDS[i], classname, HDstrlen(HDF_INTERNAL_VDS[i])) == 0 ) {
            ret_value = TRUE;
            break;
        }
    }
    return ret_value;
}

/*------------------------------------------------------------------
NAME
    VSofclass -- Get vdatas of a given class in a file or in a vgroup.

DESCRIPTION
    VSofclass retrieves n_vds vdatas by their reference numbers via the
    caller-supplied array refarray.  It simply calls VSIgetvdatas to perform
    the task.

    The parameter n_vds provides the number of values that the refarray list
    can hold and can be any positive number smaller than MAX_REF (65535).  If
    n_vds is larger than the actual number of user-created vdatas, then only
    the actual number of reference numbers will be retrieved.

    The parameter start_vd indicates the vdata number to start at.
    - When start_vd is 0, the retrieval starts at the beginning.
    - When start_vd is between 0 and the number of vdatas that meet the
      search criteria, VSofclass will start retrieving vdatas from
      the vdata number start_vd.
    - When start_vd is greater than the number of vdatas that meet the
      search criteria, VSofclass will return FAIL.

    When refarray argument is NULL, VSofclass will return the actual number
    of vdatas that meet the search criteria without further processing.  This
    allows application to find out the size of the array for proper allocation.
   
RETURNS
    Returns
	- 0 if none is found, or
	- FAIL(-1) if error occurs, or
	- the number of refs returned in refarray

NOTE
    This function was added originally to assist the hdf4 map writer because
    Vnattrs does not handle attributes created via VHstoredatam and Vaddtagref.
    -BMR - 2010/11/21
---------------------------------------------------------------------*/
intn
VSofclass(int32 id,              /* IN: file id or vgroup id */
	    const char *vsclass, /* IN: class to be queried */
	    uintn start_vd,/* IN: vdata number to start retrieving */
            uintn n_vds,	 /* IN: number of user-created vds to return */
            uint16 *refarray	 /* IN/OUT: ref array to fill */)
{
    CONSTR(FUNC, "VSofclass");
    intn      ret_value = 0;

    /* clear error stack */
    HEclear();

    /* Make sure that proper size is passed in for the non-null array */
    if (refarray != NULL && n_vds == 0)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    ret_value = VSIgetvdatas(id, vsclass, start_vd, n_vds, refarray);

done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */

    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSofclass */

/*******************************************************************************
NAME
   vscheckclass - (PRIVATE) checks if the given vdata has the specified class
		 or if it is a user-created vdata.

DESCRIPTION
   This is common code to be used in VSIgetvdatas.

RETURNS
   if the vdata has the same class as 'vsclass' or is a user-created vdata,
   return TRUE, else FALSE.
   BMR - 2010/11/30
*******************************************************************************/
PRIVATE intn
vscheckclass(int32 id, /* IN: vgroup id or file id */
	    uint16 vs_ref, /* IN: reference number of vdata being checked */
	    const char *vsclass  /* IN: class name to be queried or NULL for
					 non-internal vdata */)
{
    CONSTR(FUNC, "vscheckclass");
    vsinstance_t *vs_inst = NULL;
    VDATA        *vs = NULL;
    intn ret_value = FALSE;

    /* get instance of vdata; if it's not found, continue to look for
       other vdatas */
    if((vs_inst = vsinst(id, (uint16)vs_ref)) == NULL)
        HGOTO_DONE(FALSE);

    /* get vdata itself and check */
    vs = vs_inst->vs;
    if (vs == NULL)
        HGOTO_ERROR(DFE_BADPTR, FAIL);

    /* Make sure this vdata has a class name before checking */
    if (vs->vsclass != NULL && HDstrlen(vs->vsclass) != 0)
    {
        /* If user-created vdatas are being checked for, then set flag
           if this vdata is not internally created by the library */
        if (vsclass == NULL)
        {
            if (VSisinternal(vs->vsclass) == FALSE)
                ret_value = TRUE;
        }
        /* If a specific class is searched, set flag if this
           vdata has that same class */
        else
        {
            size_t len = HDstrlen(_HDF_CHK_TBL_CLASS);

            /* Explanation of the comparison below:
               Because a class name that starts with _HDF_CHK_TBL_CLASS
               may have variable information appended to the end after
               _HDF_CHK_TBL_CLASS, we need to compare up to the length
               of _HDF_CHK_TBL_CLASS so that we can get all occurences
               of the classes starting with _HDF_CHK_TBL_CLASS.  For
               the non-_HDF_CHK_TBL_CLASS classes, we want to compare
               the entire array of characters.  However, if specific
               version of _HDF_CHK_TBL_CLASS is requested, this code
               will need to be modified properly */

            /* vsclass != _HDF_CHK_TBL_CLASS..., compare entire string*/
            if (HDstrncmp(vsclass, _HDF_CHK_TBL_CLASS, len))
                ret_value = HDstrcmp(vsclass, vs->vsclass) ? FALSE : TRUE;
            else
                ret_value = HDstrncmp(vsclass, vs->vsclass, len) ? FALSE : TRUE;
        }
    }
    /* This vd doesn't have a class name, so it must be a user-created vd */
    else
    {
        /* If user-created vdatas are being checked for, then set flag to
           indicate that this vdata is user-created */
        if (vsclass == NULL)
            ret_value = TRUE;
	/* If a specific class name is requested, then set flag to indicate
	   that this vd is not what is being searched for */
	else
	    ret_value = FALSE;
    }
done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */
    } /* end if */

  /* Normal function cleanup */
  return ret_value;
} /* vscheckclass */

/*******************************************************************************
NAME
   VSIgetvdatas -- (PRIVATE) Get user-created vdata in a file or in a vgroup.

DESCRIPTION
    VSIgetvdatas retrieves n_vds vdatas by their reference numbers via the
    caller-supplied array refarray.  When a vgroup id is specified, VSIgetvdatas
    will only retrieve the vdatas immediately belong to the specified vgroup,
    and not any sub-vgroups.

    The parameter n_vds provides the number of values that the refarray list
    can hold and can be any positive number smaller than MAX_REF (65535).  If
    n_vds is larger than the actual number of user-created vdatas, then only
    the actual number of reference numbers will be retrieved.

    The parameter start_vd indicates the vdata number to start at.
    - When start_vd is 0, the retrieval starts at the beginning.
    - When start_vd is between 0 and the number of user-created vdatas in
      the file or the vgroup, VSIgetvdatas will start retrieving vdatas from
      the vdata number start_vd.
    - When start_vd is greater than the number of user-created vdatas in the
      file or the vgroup, VSIgetvdatas will return FAIL.

    When refarray argument is NULL, VSIgetvdatas will return the actual number
    of user-created vdatas without further processing.  This allows application
    to find out the size of the array for proper allocation.
   
RETURNS
    The number of user-created vdatas if successful and FAIL, otherwise.
    BMR - 2010/07/10
*******************************************************************************/
intn
VSIgetvdatas(int32 id,		 /* IN: file id or vgroup id */
	    const char *vsclass, /* IN: a specific class or NULL for user-created vdatas */
	    const uintn start_vd,/* IN: vdata number to start retrieving */
            const uintn n_vds,	 /* IN: number of user-created vds to return */
            uint16 *refarray	 /* IN/OUT: ref array to fill */)
{
    CONSTR(FUNC, "VSIgetvdatas");
    vginstance_t *vg_inst = NULL;
    group_t id_type = HAatom_group(id);    /* id is FIDGROUP or VGIDGROUP */
    intn        nactual_vds=0, nfound_vds=0, ii;
    VGROUP     *vg = NULL;
    vfile_t    *vf = NULL;
    int32	vs_ref;
    int32       ret_value = SUCCEED;

    /* clear error stack */
    HEclear();

    /* Make sure that proper size is passed in for the non-null array */
    if (refarray != NULL && n_vds == 0)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* The given id must be a file ID or a vgroup ID */
    if (id_type != FIDGROUP && id_type != VGIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* If given id is a file id */
    if (id_type == FIDGROUP)
    {
        /* get vdata file record */
        if (NULL == (vf = Get_vfile(id)))
            HGOTO_ERROR(DFE_FNF, FAIL);

	/* Look through all vdatas, searching for user-created vdatas until
	   no more vdatas in the file or the number of vdatas to be
	   retrieved is reached */
	nactual_vds = 0;/* number of user-created vdatas to be retrieved */
	nfound_vds = 0;	/* number of user-created vdatas */
	vs_ref = VSgetid(id, -1);  /* get ref number of first vd in the file */
	while ((vs_ref != FAIL)	   /* there are more vdatas */
		&& ((nactual_vds < n_vds) || (n_vds == 0))
		&& (nactual_vds <= nfound_vds))
	{
	    intn found = FALSE;

	    /* Check if the vdata either has the specified class (when vsclass
	       is !NULL) or is a user-created vdata (when vsclass is NULL) */
	    found = vscheckclass(id, (uint16)vs_ref, vsclass);

            /* If this vs met the search criteria, record its ref# according to
               caller's specifying of where to start and how many to retrieve */
            if (found)
            {
                /* make sure to count only from vdata number start_vd */
                if (nfound_vds >= start_vd)
                    /* if caller requests for reference numbers */
                    if (refarray != NULL)
                    {
                        refarray[nactual_vds] = (uint16)vs_ref;

                        /* increment the actual number of user-created vds
                           to be retrieved */
                        nactual_vds++;
                    }
                    /* increment the number of user-created vds */
                    nfound_vds++;
                }
	    /* Move forward to the next vdata in the file */
	    vs_ref = VSgetid(id, vs_ref);
	} /* while more vdatas in file */
    } /* file id is given */

    /* check if given id is a vgroup id */
    else if (id_type == VGIDGROUP)
    { /* vgroup id is given */

	/* get the number of sub-vdatas belong to this vgroup */
	int32 n_elements = Vntagrefs(id);
	if (n_elements == FAIL)
	    HGOTO_ERROR(DFE_GENAPP, FAIL);

	/* get instance of vgroup */
	if (NULL == (vg_inst = (vginstance_t *) HAatom_object(id)))
	    HGOTO_ERROR(DFE_NOVS, FAIL);

	/* get vgroup itself and check */
	vg = vg_inst->vg;
	if (vg == NULL)
	    HGOTO_ERROR(DFE_BADPTR, FAIL);

        /* get vdata file record */
        if (NULL == (vf = Get_vfile(vg->f)))
            HGOTO_ERROR(DFE_FNF, FAIL);

	/* Go through the tag list vg->tag and find user-created vdatas, until
	   no more sub-vdatas or the number of vdatas to be retrieved is
	   reached */
	nactual_vds = 0;/* number of user-created vdatas to be retrieved */
	nfound_vds = 0;	/* number of user-created vdatas */
        for (ii = 0; ii < n_elements && ((nactual_vds < n_vds) || (n_vds == 0))
			&& nactual_vds <= nfound_vds; ii++)
        {
	    /* If an element is a vdata, then get access to it */
            if (vg->tag[ii] == DFTAG_VH)
	    {
	        intn found = FALSE;

	        found = vscheckclass((int32)vg->f, vg->ref[ii], vsclass);

                /* If this vdata met the search criteria, record its ref#
                   according to caller's specification of where to start and
                   how many to retrieve */
                if (found)
		{
		    /* Make sure to count only from vdata number start_vd */
		    if (nfound_vds >= start_vd)
			/* If caller requests for reference numbers */
			if (refarray != NULL)
			{
			    refarray[nactual_vds] = (uint16)vg->ref[ii];

			    /* Increment the actual number of vdatas to be
			       retrieved */
			    nactual_vds++;
			}

		    /* Increment number of vds that meet the search criteria */
		    nfound_vds++;
		}
	    } /* this sub element is a vdata */
        } /* for */
    } /* vgroup id is given */

    /* Flag if start_vd is beyond the number of user-created vdatas */
    if (nfound_vds < start_vd)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* If caller is asking for the number of vdatas only, return the
	number of user-created vdatas, otherwise, return the number of
	vdatas that are actually stored in refarray */
    if (refarray == NULL)
	ret_value = nfound_vds - start_vd;
    else
	ret_value = nactual_vds;

done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */
    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSIgetvdatas */

/*******************************************************************************
NAME
   VSgetvdatas -- Get user-created vdata in a file or in a vgroup.

DESCRIPTION
    VSgetvdatas retrieves n_vds vdatas by their reference numbers via the
    caller-supplied array refarray.  When a vgroup id is specified, VSgetvdatas
    will only retrieve the vdatas immediately belong to the specified vgroup,
    and not any sub-vgroups.

    The parameter n_vds provides the number of values that the refarray list
    can hold and can be any positive number smaller than MAX_REF (65535).  If
    n_vds is larger than the actual number of user-created vdatas, then only
    the actual number of reference numbers will be retrieved.

    The parameter start_vd indicates the vdata number to start at.
    - When start_vd is 0, the retrieval starts at the beginning.
    - When start_vd is between 0 and the number of user-created vdatas in
      the file or the vgroup, VSgetvdatas will start retrieving vdatas from
      the vdata number start_vd.
    - When start_vd is greater than the number of user-created vdatas in the
      file or the vgroup, VSgetvdatas will return FAIL.

    When refarray argument is NULL, VSgetvdatas will return the actual number
    of user-created vdatas without further processing.  This allows application
    to find out the size of the array for proper allocation.
   
RETURNS
    The number of user-created vdatas if successful and FAIL, otherwise.
    -BMR - 2010/07/10

MODIFICATION
    - Made the original VSgetvdatas into a private function VSIgetvdatas so
      that the code can be reused by VSofclass.  VSgetvdatas now simply calls
      VSIgetvdatas. -BMR - 2010/11/17
*******************************************************************************/
intn
VSgetvdatas(int32 id,		/* IN: file id or vgroup id */
	    const uintn start_vd,/* IN: vdata number to start retrieving */
            const uintn n_vds,	/* IN: number of user-created vds to return */
            uint16 *refarray	/* IN/OUT: ref array to fill */)
{
    CONSTR(FUNC, "VSgetvdatas");
    int32       ret_value = SUCCEED;

    /* clear error stack */
    HEclear();

    /* Make sure that proper size is passed in for the non-null array */
    if (refarray != NULL && n_vds == 0)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    /* Passing NULL in to VSIgetvdatas to get user-created vdatas */
    ret_value = VSIgetvdatas(id, NULL, start_vd, n_vds, refarray);
done:
  if(ret_value == FAIL)
    { /* Error condition cleanup */
    } /* end if */

  /* Normal function cleanup */
  return ret_value;
}   /* VSgetvdatas */


/* ------------------------------- Vsetzap -------------------------------- */
/*
 * Vsetzap: Useless now. Maintained for back compatibility.
 */
VOID 
Vsetzap(void)
{
}
