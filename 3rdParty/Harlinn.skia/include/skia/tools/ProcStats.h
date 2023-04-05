/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef ProcStats_DEFINED
#define ProcStats_DEFINED

#include <cstdint>

#include <skia/core/SkTypes.h>

/**
 * ProcStats - Process Statistics Functions
 */

namespace sk_tools {

/**
 *  If implemented, returns the current resident set size in bytes.
 *  If not, returns -1.
 */
SK_API int64_t getCurrResidentSetSizeBytes();

/**
 *  If implemented, returns the maximum resident set size in MB.
 *  If not, returns -1.
 */
SK_API int64_t getMaxResidentSetSizeBytes();

/**
 *  If implemented, returns the maximum resident set size in MB.
 *  If not, returns -1.
 */
SK_API int getMaxResidentSetSizeMB();

/**
 *  If implemented, returns the current resident set size in MB.
 *  If not, returns -1.
 */
SK_API int getCurrResidentSetSizeMB();

}  // namespace sk_tools

#endif  // ProcStats_DEFINED
