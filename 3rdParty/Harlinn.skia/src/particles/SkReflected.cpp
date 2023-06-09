/*
* Copyright 2019 Google LLC
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#include "skia/particles/SkReflected.h"

SkSTArray<16, const SkReflected::Type*, true> SkReflected::gTypes;

void SkReflected::VisitTypes(std::function<void(const Type*)> visitor) {
    for (const Type* type : gTypes) {
        visitor(type);
    }
}
