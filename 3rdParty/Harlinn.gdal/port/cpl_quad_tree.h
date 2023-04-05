#pragma once
/**********************************************************************
 * $Id$
 *
 * Project:  CPL - Common Portability Library
 * Purpose:  Implementation of quadtree building and searching functions.
 *           Derived from shapelib and mapserver implementations
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *           Even Rouault, <even dot rouault at spatialys.com>
 *
 ******************************************************************************
 * Copyright (c) 1999-2008, Frank Warmerdam
 * Copyright (c) 2008-2014, Even Rouault <even dot rouault at spatialys.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef CPL_QUAD_TREE_H_INCLUDED
#define CPL_QUAD_TREE_H_INCLUDED

#include <port/cpl_port.h>

/**
 * \file cpl_quad_tree.h
 *
 * Quad tree implementation.
 *
 * A quadtree is a tree data structure in which each internal node
 * has up to four children. Quadtrees are most often used to partition
 * a two dimensional space by recursively subdividing it into four
 * quadrants or regions
 */

CPL_C_START

/* Types */

/** Describe a rectangle */
typedef struct {
  double minx; /**< Minimum x */
  double miny; /**< Minimum y */
  double maxx; /**< Maximum x */
  double maxy; /**< Maximum y */
} CPLRectObj;

/** Opaque type for a quad tree */
typedef struct _CPLQuadTree CPLQuadTree;

/** CPLQuadTreeGetBoundsFunc */
typedef void         (*CPLQuadTreeGetBoundsFunc)(const void* hFeature, CPLRectObj* pBounds);
/** CPLQuadTreeForeachFunc */
typedef int          (*CPLQuadTreeForeachFunc)(void* pElt, void* pUserData);
/** CPLQuadTreeDumpFeatureFunc */
typedef void         (*CPLQuadTreeDumpFeatureFunc)(const void* hFeature, int nIndentLevel, void* pUserData);

/* Functions */

HGDAL_EXPORT CPLQuadTree *CPLQuadTreeCreate(const CPLRectObj* pGlobalBounds,
                                        CPLQuadTreeGetBoundsFunc pfnGetBounds);
HGDAL_EXPORT void CPLQuadTreeDestroy(CPLQuadTree *hQuadtree);

HGDAL_EXPORT void CPLQuadTreeSetBucketCapacity(CPLQuadTree *hQuadtree,
                                                   int nBucketCapacity);
HGDAL_EXPORT int CPLQuadTreeGetAdvisedMaxDepth(int nExpectedFeatures);
HGDAL_EXPORT void CPLQuadTreeSetMaxDepth(CPLQuadTree *hQuadtree,
                                             int nMaxDepth);

HGDAL_EXPORT void CPLQuadTreeInsert(CPLQuadTree *hQuadtree,
                                        void* hFeature);
HGDAL_EXPORT void CPLQuadTreeInsertWithBounds(CPLQuadTree *hQuadtree,
                                                  void* hFeature,
                                                  const CPLRectObj* psBounds);

HGDAL_EXPORT void CPLQuadTreeRemove(CPLQuadTree *hQuadtree,
                                        void* hFeature,
                                        const CPLRectObj* psBounds);

HGDAL_EXPORT void **CPLQuadTreeSearch(const CPLQuadTree *hQuadtree,
                                        const CPLRectObj* pAoi,
                                        int* pnFeatureCount);

HGDAL_EXPORT void CPLQuadTreeForeach(const CPLQuadTree *hQuadtree,
                                         CPLQuadTreeForeachFunc pfnForeach,
                                         void* pUserData);

HGDAL_EXPORT void CPLQuadTreeDump(const CPLQuadTree *hQuadtree,
                                      CPLQuadTreeDumpFeatureFunc pfnDumpFeatureFunc,
                                      void* pUserData);
HGDAL_EXPORT void CPLQuadTreeGetStats(const CPLQuadTree *hQuadtree,
                                          int* pnFeatureCount,
                                          int* pnNodeCount,
                                          int* pnMaxDepth,
                                          int* pnMaxBucketCapacity);

CPL_C_END

#endif
