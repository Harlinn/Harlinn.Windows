#pragma once
#ifndef PBRTO_BASE_NEWBSSRDF_H_
#define PBRTO_BASE_NEWBSSRDF_H_

/*
   Copyright 2024-2025 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>
#include <pbrto/util/NewPStd.h>
#include <pbrto/util/NewTaggedPtr.h>

#include <string>

namespace pbrto
{

    struct BSSRDFSample;
    struct BSSRDFProbeSegment;
    struct SubsurfaceInteraction;
    struct BSSRDFTable;

    // BSSRDF Definition
    class TabulatedBSSRDF;

    class BSSRDF : public TaggedPointer<TabulatedBSSRDF>
    {
    public:
        // BSSRDF Interface
        using TaggedPointer::TaggedPointer;

        inline pstdo::optional<BSSRDFProbeSegment> SampleSp( Float u1, const Point2f& u2 ) const;

        inline BSSRDFSample ProbeIntersectionToSample( const SubsurfaceInteraction& si, ScratchBuffer& scratchBuffer ) const;
    };

}


#endif
