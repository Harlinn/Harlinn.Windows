/*
 * Copyright (c) 1999-2000 Image Power, Inc. and the University of
 *   British Columbia.
 * Copyright (c) 2001-2003 Michael David Adams.
 * All rights reserved.
 */

/* __START_OF_JASPER_LICENSE__
 * 
 * JasPer License Version 2.0
 * 
 * Copyright (c) 2001-2006 Michael David Adams
 * Copyright (c) 1999-2000 Image Power, Inc.
 * Copyright (c) 1999-2000 The University of British Columbia
 * 
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person (the
 * "User") obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 * 
 * 1.  The above copyright notices and this permission notice (which
 * includes the disclaimer below) shall be included in all copies or
 * substantial portions of the Software.
 * 
 * 2.  The name of a copyright holder shall not be used to endorse or
 * promote products derived from the Software without specific prior
 * written permission.
 * 
 * THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS
 * LICENSE.  NO USE OF THE SOFTWARE IS AUTHORIZED HEREUNDER EXCEPT UNDER
 * THIS DISCLAIMER.  THE SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS
 * "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
 * INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  NO ASSURANCES ARE
 * PROVIDED BY THE COPYRIGHT HOLDERS THAT THE SOFTWARE DOES NOT INFRINGE
 * THE PATENT OR OTHER INTELLECTUAL PROPERTY RIGHTS OF ANY OTHER ENTITY.
 * EACH COPYRIGHT HOLDER DISCLAIMS ANY LIABILITY TO THE USER FOR CLAIMS
 * BROUGHT BY ANY OTHER ENTITY BASED ON INFRINGEMENT OF INTELLECTUAL
 * PROPERTY RIGHTS OR OTHERWISE.  AS A CONDITION TO EXERCISING THE RIGHTS
 * GRANTED HEREUNDER, EACH USER HEREBY ASSUMES SOLE RESPONSIBILITY TO SECURE
 * ANY OTHER INTELLECTUAL PROPERTY RIGHTS NEEDED, IF ANY.  THE SOFTWARE
 * IS NOT FAULT-TOLERANT AND IS NOT INTENDED FOR USE IN MISSION-CRITICAL
 * SYSTEMS, SUCH AS THOSE USED IN THE OPERATION OF NUCLEAR FACILITIES,
 * AIRCRAFT NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL
 * SYSTEMS, DIRECT LIFE SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH
 * THE FAILURE OF THE SOFTWARE OR SYSTEM COULD LEAD DIRECTLY TO DEATH,
 * PERSONAL INJURY, OR SEVERE PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH
 * RISK ACTIVITIES").  THE COPYRIGHT HOLDERS SPECIFICALLY DISCLAIM ANY
 * EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR HIGH RISK ACTIVITIES.
 * 
 * __END_OF_JASPER_LICENSE__
 */

/*
 * JP2 Library
 *
 * $Id$
 */

/******************************************************************************\
* Includes.
\******************************************************************************/

#include "jasper/jas_image.h"
#include "jasper/jas_malloc.h"
#include "jasper/jas_stream.h"
#include "jasper/jas_cm.h"
#include "jasper/jas_icc.h"
#include "jasper/jas_debug.h"

#include "jp2_cod.h"

#include <stdio.h>
#include <stdlib.h>

/******************************************************************************\
* Function prototypes.
\******************************************************************************/

static uint_fast32_t jp2_gettypeasoc(int colorspace, int ctype);
static int clrspctojp2(jas_clrspc_t clrspc);

/******************************************************************************\
* Functions.
\******************************************************************************/

JAS_EXPORT int jp2_encode(jas_image_t *image, jas_stream_t *out, const char *optstr)
{
	jp2_box_t *box;
	jp2_ftyp_t *ftyp;
	jp2_ihdr_t *ihdr;
	jas_stream_t *tmpstream;
	int allcmptssame;
	jp2_bpcc_t *bpcc;
	long len;
	uint_fast16_t cmptno;
	jp2_colr_t *colr;
	char buf[4096];
	uint_fast32_t overhead;
	jp2_cdefchan_t *cdefchanent;
	jp2_cdef_t *cdef;
	uint_fast32_t typeasoc;
	jas_iccprof_t *iccprof;
	jas_stream_t *iccstream;
	int pos;
	int needcdef;

	box = 0;
	tmpstream = 0;
	iccstream = 0;
	iccprof = 0;

	if (jas_image_numcmpts(image) < 1) {
		jas_logerrorf("image must have at least one component\n");
		goto error;
	}

	allcmptssame = 1;
	const bool sgnd = jas_image_cmptsgnd(image, 0);
	const unsigned prec = jas_image_cmptprec(image, 0);
	for (unsigned i = 1; i < jas_image_numcmpts(image); ++i) {
		if (jas_image_cmptsgnd(image, i) != sgnd ||
		  jas_image_cmptprec(image, i) != prec) {
			allcmptssame = 0;
			break;
		}
	}

	/* Output the signature box. */

	if (!(box = jp2_box_create(JP2_BOX_JP))) {
		jas_logerrorf("cannot create JP box\n");
		goto error;
	}
	box->data.jp.magic = JP2_JP_MAGIC;
	if (jp2_box_put(box, out)) {
		jas_logerrorf("cannot write JP box\n");
		goto error;
	}
	jp2_box_destroy(box);
	box = 0;

	/* Output the file type box. */

	if (!(box = jp2_box_create(JP2_BOX_FTYP))) {
		jas_logerrorf("cannot create FTYP box\n");
		goto error;
	}
	ftyp = &box->data.ftyp;
	ftyp->majver = JP2_FTYP_MAJVER;
	ftyp->minver = JP2_FTYP_MINVER;
	ftyp->numcompatcodes = 1;
	ftyp->compatcodes[0] = JP2_FTYP_COMPATCODE;
	if (jp2_box_put(box, out)) {
		jas_logerrorf("cannot write FTYP box\n");
		goto error;
	}
	jp2_box_destroy(box);
	box = 0;

	/*
	 * Generate the data portion of the JP2 header box.
	 * We cannot simply output the header for this box
	 * since we do not yet know the correct value for the length
	 * field.
	 */

	if (!(tmpstream = jas_stream_memopen(0, 0))) {
		jas_logerrorf("cannot create temporary stream\n");
		goto error;
	}

	/* Generate image header box. */

	if (!(box = jp2_box_create(JP2_BOX_IHDR))) {
		jas_logerrorf("cannot create IHDR box\n");
		goto error;
	}
	ihdr = &box->data.ihdr;
	ihdr->width = jas_image_width(image);
	ihdr->height = jas_image_height(image);
	ihdr->numcmpts = jas_image_numcmpts(image);
	ihdr->bpc = allcmptssame ? JP2_SPTOBPC(jas_image_cmptsgnd(image, 0),
	  jas_image_cmptprec(image, 0)) : JP2_IHDR_BPCNULL;
	ihdr->comptype = JP2_IHDR_COMPTYPE;
	ihdr->csunk = 0;
	ihdr->ipr = 0;
	if (jp2_box_put(box, tmpstream)) {
		jas_logerrorf("cannot write IHDR box\n");
		goto error;
	}
	jp2_box_destroy(box);
	box = 0;

	/* Generate bits per component box. */

	if (!allcmptssame) {
		if (!(box = jp2_box_create(JP2_BOX_BPCC))) {
			jas_logerrorf("cannot create BPCC box\n");
			goto error;
		}
		bpcc = &box->data.bpcc;
		bpcc->numcmpts = jas_image_numcmpts(image);
		if (!(bpcc->bpcs = jas_alloc2(bpcc->numcmpts,
		  sizeof(uint_fast8_t)))) {
			jas_logerrorf("memory allocation failed\n");
			goto error;
		}
		for (cmptno = 0; cmptno < bpcc->numcmpts; ++cmptno) {
			bpcc->bpcs[cmptno] = JP2_SPTOBPC(jas_image_cmptsgnd(image,
			  cmptno), jas_image_cmptprec(image, cmptno));
		}
		if (jp2_box_put(box, tmpstream)) {
			jas_logerrorf("cannot write BPCC box\n");
			goto error;
		}
		jp2_box_destroy(box);
		box = 0;
	}

	/* Generate color specification box. */

	if (!(box = jp2_box_create(JP2_BOX_COLR))) {
		jas_logerrorf("cannot create COLR box\n");
		goto error;
	}
	colr = &box->data.colr;
	switch (jas_image_clrspc(image)) {
	case JAS_CLRSPC_SRGB:
	case JAS_CLRSPC_SYCBCR:
	case JAS_CLRSPC_SGRAY:
		colr->method = JP2_COLR_ENUM;
		colr->csid = clrspctojp2(jas_image_clrspc(image));
		colr->pri = JP2_COLR_PRI;
		colr->approx = 0;
		break;
	default:
		colr->method = JP2_COLR_ICC;
		colr->pri = JP2_COLR_PRI;
		colr->approx = 0;
		/* Ensure that cmprof_ is not null. */
		if (!jas_image_cmprof(image)) {
			jas_logerrorf("CM profile is null\n");
			goto error;
		}
		if (!(iccprof = jas_iccprof_createfromcmprof(
		  jas_image_cmprof(image)))) {
			jas_logerrorf("cannot create ICC profile\n");
			goto error;
		}
		if (!(iccstream = jas_stream_memopen(0, 0))) {
			jas_logerrorf("cannot create temporary stream\n");
			goto error;
		}
		if (jas_iccprof_save(iccprof, iccstream)) {
			jas_logerrorf("cannot write ICC profile\n");
			goto error;
		}
		if ((pos = jas_stream_tell(iccstream)) < 0) {
			jas_logerrorf("cannot get stream position\n");
			goto error;
		}
		colr->iccplen = pos;
		if (!(colr->iccp = jas_malloc(pos))) {
			jas_logerrorf("memory allocation failed\n");
			goto error;
		}
		jas_stream_rewind(iccstream);
		if (jas_stream_read(iccstream, colr->iccp, colr->iccplen) !=
		  colr->iccplen) {
			jas_logerrorf("cannot read temporary stream\n");
			goto error;
		}
		jas_stream_close(iccstream);
		iccstream = 0;
		jas_iccprof_destroy(iccprof);
		iccprof = 0;
		break;
	}
	if (jp2_box_put(box, tmpstream)) {
		jas_logerrorf("cannot write box\n");
		goto error;
	}
	jp2_box_destroy(box);
	box = 0;

	needcdef = 1;
	switch (jas_clrspc_fam(jas_image_clrspc(image))) {
	case JAS_CLRSPC_FAM_RGB:
		if (jas_image_numcmpts(image) >= 3 &&
		  jas_image_cmpttype(image, 0) ==
		  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_R) &&
		  jas_image_cmpttype(image, 1) ==
		  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_G) &&
		  jas_image_cmpttype(image, 2) ==
		  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_B))
			needcdef = 0;
		break;
	case JAS_CLRSPC_FAM_YCBCR:
		if (jas_image_numcmpts(image) >= 3 &&
		  jas_image_cmpttype(image, 0) ==
		  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_YCBCR_Y) &&
		  jas_image_cmpttype(image, 1) ==
		  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_YCBCR_CB) &&
		  jas_image_cmpttype(image, 2) ==
		  JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_YCBCR_CR))
			needcdef = 0;
		break;
	case JAS_CLRSPC_FAM_GRAY:
		if (jas_image_numcmpts(image) >= 1 &&
		  jas_image_cmpttype(image, 0) ==
		  JAS_IMAGE_CT_COLOR(JAS_IMAGE_CT_GRAY_Y))
			needcdef = 0;
		break;
	default:
		assert(false);
		JAS_UNREACHABLE();
	}

	if (needcdef) {
		if (!(box = jp2_box_create(JP2_BOX_CDEF))) {
			jas_logerrorf("cannot create CDEF box\n");
			goto error;
		}
		cdef = &box->data.cdef;
		cdef->numchans = jas_image_numcmpts(image);
		cdef->ents = jas_alloc2(cdef->numchans, sizeof(jp2_cdefchan_t));
		if (!cdef->ents) {
			goto error;
		}
		for (unsigned i = 0; i < jas_image_numcmpts(image); ++i) {
			cdefchanent = &cdef->ents[i];
			cdefchanent->channo = i;
			typeasoc = jp2_gettypeasoc(jas_image_clrspc(image), jas_image_cmpttype(image, i));
			cdefchanent->type = typeasoc >> 16;
			cdefchanent->assoc = typeasoc & 0x7fff;
		}
		if (jp2_box_put(box, tmpstream)) {
			jas_logerrorf("cannot write CDEF box\n");
			goto error;
		}
		jp2_box_destroy(box);
		box = 0;
	}

	/* Determine the total length of the JP2 header box. */

	len = jas_stream_tell(tmpstream);
	jas_stream_rewind(tmpstream);

	/*
	 * Output the JP2 header box and all of the boxes which it contains.
	 */

	if (!(box = jp2_box_create(JP2_BOX_JP2H))) {
		jas_logerrorf("cannot create JP2H box\n");
		goto error;
	}
	box->len = len + JP2_BOX_HDRLEN(false);
	if (jp2_box_put(box, out)) {
		jas_logerrorf("cannot write JP2H box\n");
		goto error;
	}
	jp2_box_destroy(box);
	box = 0;

	if (jas_stream_copy(out, tmpstream, len)) {
		jas_logerrorf("cannot copy stream\n");
		goto error;
	}

	jas_stream_close(tmpstream);
	tmpstream = 0;

	/*
	 * Output the contiguous code stream box.
	 */

	if (!(box = jp2_box_create(JP2_BOX_JP2C))) {
		jas_logerrorf("cannot create JP2C box\n");
		goto error;
	}
	box->len = 0;
	if (jp2_box_put(box, out)) {
		jas_logerrorf("cannot write JP2C box\n");
		goto error;
	}
	jp2_box_destroy(box);
	box = 0;

	/* Output the JPEG-2000 code stream. */

	overhead = jas_stream_getrwcount(out);
	sprintf(buf, "%s\n_jp2overhead=%lu\n", (optstr ? optstr : ""),
	  (unsigned long) overhead);

	if (jpc_encode(image, out, buf)) {
		jas_logerrorf("jpc_encode failed\n");
		goto error;
	}

	return 0;

error:

	if (iccprof) {
		jas_iccprof_destroy(iccprof);
	}
	if (iccstream) {
		jas_stream_close(iccstream);
	}
	if (box) {
		jp2_box_destroy(box);
	}
	if (tmpstream) {
		jas_stream_close(tmpstream);
	}
	return -1;
}

static uint_fast32_t jp2_gettypeasoc(int colorspace, int ctype)
{
	int type;
	int asoc;

	if (ctype & JAS_IMAGE_CT_OPACITY) {
		type = JP2_CDEF_TYPE_OPACITY;
		asoc = JP2_CDEF_ASOC_ALL;
		goto done;
	}

	type = JP2_CDEF_TYPE_UNSPEC;
	asoc = JP2_CDEF_ASOC_NONE;
	switch (jas_clrspc_fam(colorspace)) {
	case JAS_CLRSPC_FAM_RGB:
		switch (JAS_IMAGE_CT_COLOR(ctype)) {
		case JAS_IMAGE_CT_RGB_R:
			type = JP2_CDEF_TYPE_COLOR;
			asoc = JP2_CDEF_RGB_R;
			break;
		case JAS_IMAGE_CT_RGB_G:
			type = JP2_CDEF_TYPE_COLOR;
			asoc = JP2_CDEF_RGB_G;
			break;
		case JAS_IMAGE_CT_RGB_B:
			type = JP2_CDEF_TYPE_COLOR;
			asoc = JP2_CDEF_RGB_B;
			break;
		}
		break;
	case JAS_CLRSPC_FAM_YCBCR:
		switch (JAS_IMAGE_CT_COLOR(ctype)) {
		case JAS_IMAGE_CT_YCBCR_Y:
			type = JP2_CDEF_TYPE_COLOR;
			asoc = JP2_CDEF_YCBCR_Y;
			break;
		case JAS_IMAGE_CT_YCBCR_CB:
			type = JP2_CDEF_TYPE_COLOR;
			asoc = JP2_CDEF_YCBCR_CB;
			break;
		case JAS_IMAGE_CT_YCBCR_CR:
			type = JP2_CDEF_TYPE_COLOR;
			asoc = JP2_CDEF_YCBCR_CR;
			break;
		}
		break;
	case JAS_CLRSPC_FAM_GRAY:
		type = JP2_CDEF_TYPE_COLOR;
		asoc = JP2_CDEF_GRAY_Y;
		break;
	}

done:
	return (type << 16) | asoc;
}

static int clrspctojp2(jas_clrspc_t clrspc)
{
	switch (clrspc) {
	case JAS_CLRSPC_SRGB:
		return JP2_COLR_SRGB;
	case JAS_CLRSPC_SYCBCR:
		return JP2_COLR_SYCC;
	case JAS_CLRSPC_SGRAY:
		return JP2_COLR_SGRAY;
	default:
		assert(false);
		JAS_UNREACHABLE();
	}
	JAS_UNREACHABLE();
}
