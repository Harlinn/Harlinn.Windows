#pragma once
#ifndef PBRTO_BASE_NEWFILTER_H_
#define PBRTO_BASE_NEWFILTER_H_

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
#include <pbrto/util/NewTaggedPtr.h>

#include <string>

namespace pbrto
{

    // Filter Declarations
    struct FilterSample;
    class BoxFilter;
    class GaussianFilter;
    class MitchellFilter;
    class LanczosSincFilter;
    class TriangleFilter;

    // Filter Definition
    class Filter : public TaggedPointer<BoxFilter, GaussianFilter, MitchellFilter,
        LanczosSincFilter, TriangleFilter>
    {
    public:
        // Filter Interface
        using TaggedPointer::TaggedPointer;

        static Filter Create( const std::string& name, const ParameterDictionary& parameters,
            const FileLoc* loc, Allocator alloc );

        PBRT_CPU_GPU inline Vector2f Radius( ) const;

        PBRT_CPU_GPU inline Float Evaluate( Point2f p ) const;

        PBRT_CPU_GPU inline Float Integral( ) const;

        PBRT_CPU_GPU inline FilterSample Sample( Point2f u ) const;

        std::string ToString( ) const;
    };

}


#endif
