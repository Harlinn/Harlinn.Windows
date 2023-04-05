#pragma once

/*
 * Copyright 2008 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */





#ifndef SkUnPreMultiply_DEFINED
#define SkUnPreMultiply_DEFINED

#include <skia/core/SkColor.h>

class SkUnPreMultiply {
public:
    typedef uint32_t Scale;

    // index this table with alpha [0..255]
    static const Scale* GetScaleTable() {
        return gTable;
    }

    static Scale GetScale(U8CPU alpha) {
        SkASSERT(alpha <= 255);
        return gTable[alpha];
    }

    /** Usage:

        const Scale* table = SkUnPreMultiply::GetScaleTable();

        for (...) {
            unsigned a = ...
            SkUnPreMultiply::Scale scale = table[a];

            red = SkUnPreMultiply::ApplyScale(scale, red);
            ...
            // now red is unpremultiplied
        }
    */
    static U8CPU ApplyScale(Scale scale, U8CPU component) {
        SkASSERT(component <= 255);
        return (scale * component + (1 << 23)) >> 24;
    }

    SK_API static SkColor PMColorToColor(SkPMColor c);

private:
    SK_API static const uint32_t gTable[256];
};

#endif
