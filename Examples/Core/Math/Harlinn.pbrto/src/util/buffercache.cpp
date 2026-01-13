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
#include "pch.h"
// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/util/buffercache.h>

#include <pbrto/util/stats.h>

namespace pbrt {

// BufferCache Global Definitions
BufferCache<int> *intBufferCache;
BufferCache<Point2f> *point2BufferCache;
BufferCache<Point3f> *point3BufferCache;
BufferCache<Vector3f> *vector3BufferCache;
BufferCache<Normal3f> *normal3BufferCache;

void InitBufferCaches() {
    CHECK(intBufferCache == nullptr);
    intBufferCache = new BufferCache<int>;
    point2BufferCache = new BufferCache<Point2f>;
    point3BufferCache = new BufferCache<Point3f>;
    vector3BufferCache = new BufferCache<Vector3f>;
    normal3BufferCache = new BufferCache<Normal3f>;
}

}  // namespace pbrt
