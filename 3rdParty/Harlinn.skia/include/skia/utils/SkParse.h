#pragma once

/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkParse_DEFINED
#define SkParse_DEFINED

#include <skia/core/SkColor.h>

class SkParse {
public:
    SK_API static int Count(const char str[]); // number of scalars or int values
    SK_API static int Count(const char str[], char separator);
    SK_API static const char* FindColor(const char str[], SkColor* value);
    SK_API static const char* FindHex(const char str[], uint32_t* value);
    SK_API static const char* FindMSec(const char str[], SkMSec* value);
    SK_API static const char* FindNamedColor(const char str[], size_t len, SkColor* color);
    SK_API static const char* FindS32(const char str[], int32_t* value);
    SK_API static const char* FindScalar(const char str[], SkScalar* value);
    SK_API static const char* FindScalars(const char str[], SkScalar value[], int count);

    SK_API static bool FindBool(const char str[], bool* value);
    // return the index of str in list[], or -1 if not found
    SK_API static int  FindList(const char str[], const char list[]);
};

#endif
