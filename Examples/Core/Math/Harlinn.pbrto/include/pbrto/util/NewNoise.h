#pragma once
#ifndef PBRTO_UTIL_NEWNOISE_H_
#define PBRTO_UTIL_NEWNOISE_H_

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

namespace pbrto
{

    PBRTO_EXPORT Float Noise( Float x, Float y = .5f, Float z = .5f );
    PBRTO_EXPORT Float Noise( const Point3f& p );
    PBRTO_EXPORT Vector3f DNoise( const Point3f& p );
    PBRTO_EXPORT Float FBm( const Point3f& p, const Vector3f& dpdx, const Vector3f& dpdy, Float omega, int octaves );
    PBRTO_EXPORT Float Turbulence( const Point3f& p, const Vector3f& dpdx, const Vector3f& dpdy, Float omega, int octaves );

}


#endif
