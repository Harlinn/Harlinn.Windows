#pragma once
/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkThreadID_DEFINED
#define SkThreadID_DEFINED

#include <skia/core/SkTypes.h>

typedef int64_t SkThreadID;

// SkMutex.h uses SkGetThredID in debug only code.
SK_API SkThreadID SkGetThreadID();

const SkThreadID kIllegalThreadID = 0;

#endif  // SkThreadID_DEFINED
