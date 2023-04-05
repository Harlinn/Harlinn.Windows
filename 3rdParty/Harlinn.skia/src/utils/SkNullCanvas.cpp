/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/utils/SkNullCanvas.h>

#include <skia/core/SkCanvas.h>
#include <skia/utils/SkNWayCanvas.h>

std::unique_ptr<SkCanvas> SkMakeNullCanvas() {
    // An N-Way canvas forwards calls to N canvas's. When N == 0 it's
    // effectively a null canvas.
    return std::unique_ptr<SkCanvas>(new SkNWayCanvas(0, 0));
}
