// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#ifndef PBRT_BASE_BSSRDF_H
#define PBRT_BASE_BSSRDF_H

#include <pbrto/pbrt.h>

#include <pbrto/util/pstd.h>
#include <pbrto/util/taggedptr.h>

#include <string>

namespace pbrt
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

        PBRT_CPU_GPU 
        inline pstd::optional<BSSRDFProbeSegment> SampleSp( Float u1, Point2f u2 ) const;

        inline BSSRDFSample ProbeIntersectionToSample( const SubsurfaceInteraction& si, ScratchBuffer& scratchBuffer ) const;
    };

}  // namespace pbrt

#endif  // PBRT_BASE_BSSRDF_H
