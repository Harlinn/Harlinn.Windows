#include "pch.h"

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

#include <pbrto/NewBsdf.h>

#include <pbrto/util/NewSpectrum.h>

namespace pbrto
{

    std::string BSDFSample::ToString( ) const
    {
        return StringPrintf( "[ BSDFSample f: %s wi: %s pdf: %s flags: %s ]", f, wi, pdf,
            flags );
    }

    // BSDF Method Definitions
    std::string BSDF::ToString( ) const
    {
        return StringPrintf( "[ BSDF bxdf: %s shadingFrame: %s ]", bxdf, shadingFrame );
    }

}