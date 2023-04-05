/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef ResourceFactory_DEFINED
#define ResourceFactory_DEFINED

#include "skia/core/SkData.h"

extern SK_API sk_sp<SkData> (*gResourceFactory)(const char*);

#endif  // ResourceFactory_DEFINED
