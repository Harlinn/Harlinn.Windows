/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkAutoCo_DEFINED
#define SkAutoCo_DEFINED

#include <skia/core/SkTypes.h>

#ifdef SK_BUILD_FOR_WIN

#include <skia/private/SkNoncopyable.h>
#include "src/core/SkLeanWindows.h"

/**
 * An instance of this class initializes COM on creation
 * and closes the COM library on destruction.
 */
class SkAutoCoInitialize : SkNoncopyable {
private:
    HRESULT fHR;
public:
    SK_API SkAutoCoInitialize();
    SK_API ~SkAutoCoInitialize();
    SK_API bool succeeded();
};

#endif  // SK_BUILD_FOR_WIN
#endif  // SkAutoCo_DEFINED
