#pragma once

/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkParsePath_DEFINED
#define SkParsePath_DEFINED

#include <skia/core/SkPath.h>

class SkString;

class SkParsePath {
public:
    SK_API static bool FromSVGString(const char str[], SkPath*);

    enum class PathEncoding { Absolute, Relative };
    SK_API static void ToSVGString(const SkPath&, SkString*, PathEncoding = PathEncoding::Absolute);
};

#endif
