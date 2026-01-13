/*
    Copyright 2024-2026 Espen Harlinn
 
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

#ifndef PBRT_UTIL_NOISE_H
#define PBRT_UTIL_NOISE_H

#include <pbrto/pbrt.h>

namespace pbrt {

PBRT_CPU_GPU
Float Noise(Float x, Float y = .5f, Float z = .5f);
PBRT_CPU_GPU
Float Noise(Point3f p);
PBRT_CPU_GPU
Vector3f DNoise(Point3f p);
PBRT_CPU_GPU
Float FBm(Point3f p, Vector3f dpdx, Vector3f dpdy, Float omega, int octaves);
PBRT_CPU_GPU
Float Turbulence(Point3f p, Vector3f dpdx, Vector3f dpdy, Float omega, int octaves);

}  // namespace pbrt

#endif  // PBRT_UTIL_NOISE_H
