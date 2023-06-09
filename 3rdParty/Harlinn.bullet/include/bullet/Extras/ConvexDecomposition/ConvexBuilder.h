#ifndef CONVEX_BUILDER_H
#define CONVEX_BUILDER_H

#include <bullet/bullet_export.h>

/*----------------------------------------------------------------------
Copyright (c) 2004 Open Dynamics Framework Group
www.physicstools.org
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided
that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

Neither the name of the Open Dynamics Framework Group nor the names of its contributors may
be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE INTEL OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------*/

// http://codesuppository.blogspot.com
//
// mailto: jratcliff@infiniplex.net
//
// http://www.amillionpixels.us
//

#include "ConvexDecomposition.h"
#include "vlookup.h"
#include "bullet/LinearMath/btAlignedObjectArray.h"

class CHull
{
public:
	BT_EXPORT CHull(const ConvexDecomposition::ConvexResult &result);

	BT_EXPORT ~CHull(void);

	BT_EXPORT bool overlap(const CHull &h) const;

	float mMin[3];
	float mMax[3];
	float mVolume;
	float mDiagonal;  // long edge..
	ConvexDecomposition::ConvexResult *mResult;
};

// Usage: std::sort( list.begin(), list.end(), StringSortRef() );
class CHullSort
{
public:
	inline bool operator()(const CHull *a, const CHull *b) const
	{
		return a->mVolume < b->mVolume;
	}
};

typedef btAlignedObjectArray<CHull *> CHullVector;

class ConvexBuilder : public ConvexDecomposition::ConvexDecompInterface
{
public:
	BT_EXPORT ConvexBuilder(ConvexDecomposition::ConvexDecompInterface *callback);

	BT_EXPORT virtual ~ConvexBuilder(void);

	BT_EXPORT bool isDuplicate(unsigned int i1, unsigned int i2, unsigned int i3,
					 unsigned int ci1, unsigned int ci2, unsigned int ci3);

	BT_EXPORT void getMesh(const ConvexDecomposition::ConvexResult &cr, VertexLookup vc, UintVector &indices);

	BT_EXPORT CHull *canMerge(CHull *a, CHull *b);

	BT_EXPORT bool combineHulls(void);

	BT_EXPORT unsigned int process(const ConvexDecomposition::DecompDesc &desc);

	BT_EXPORT virtual void ConvexDebugTri(const float *p1, const float *p2, const float *p3, unsigned int color);

	BT_EXPORT virtual void ConvexDebugOBB(const float *sides, const float *matrix, unsigned int color);
	BT_EXPORT virtual void ConvexDebugPoint(const float *p, float dist, unsigned int color);

	BT_EXPORT virtual void ConvexDebugBound(const float *bmin, const float *bmax, unsigned int color);

	BT_EXPORT virtual void ConvexDecompResult(ConvexDecomposition::ConvexResult &result);

	BT_EXPORT void sortChulls(CHullVector &hulls);

	CHullVector mChulls;
	ConvexDecompInterface *mCallback;
};

#endif  //CONVEX_BUILDER_H
