/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef random_parse_path_DEFINED
#define random_parse_path_DEFINED

#include <skia/core/SkString.h>

class SkRandom;

SK_API SkString MakeRandomParsePathPiece(SkRandom* rand);

#endif
