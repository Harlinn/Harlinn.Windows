/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#pragma once

#include <skia/core/SkString.h>
#include <skia/private/SkTArray.h>
#include <skia/tools/flags/CommandLineFlags.h>

namespace CommonFlags {
/**
 *  Helper to assist in collecting image paths from |dir| specified through a command line
 * flag.
 *
 *  Populates |output|, an array of strings with paths to images to test.
 *
 *  Returns true if each argument to the images flag is meaningful:
 *  - If the file/directory does not exist, return false.
 *  - If |dir| does not have any supported images (based on file type), return false.
 *  - If |dir| is a single file, assume the user is deliberately testing this image,
 *    regardless of file type.
 */
SK_API bool CollectImages(CommandLineFlags::StringArray dir, SkTArray<SkString>* output);

/**
 *  Helper to set GrContextOptions from common GPU flags, including
 *     --gpuThreads
 *     --cachePathMasks
 *     --allPathsVolatile
 *     --(no)gs
 *     --(no)ts
 *     --maxTessellationSegments
 *     --pr
 *     --internalSamples
 *     --disableDriverCorrectnessWorkarounds
 *     --reduceOpsTaskSplitting
 *     --dontReduceOpsTaskSplitting
 */
SK_API void SetCtxOptions(struct GrContextOptions*);

/**
 *  Enable, disable, or force analytic anti-aliasing using --analyticAA and --forceAnalyticAA.
 */
SK_API void SetAnalyticAA();

/**
 *  Turn on portable (--nonativeFonts) or GDI font rendering (--gdi).
 */
SK_API void SetDefaultFontMgr();

}  // namespace CommonFlags
