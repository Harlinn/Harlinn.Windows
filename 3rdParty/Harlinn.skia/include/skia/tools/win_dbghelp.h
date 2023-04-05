/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef win_dbghelp_DEFINED
#define win_dbghelp_DEFINED

#include <skia/core/SkTypes.h>

#ifdef SK_BUILD_FOR_WIN

#include <dbghelp.h>
#include <shellapi.h>
#include <shlobj.h>

SK_API void setAppName(const char* app_name);
SK_API const char* getAppName();

SK_API void setBinariesPath(const char* binaries_path);
SK_API const char* getBinariesPath();

SK_API void setAppVersion(const char* version);
SK_API const char* getAppVersion();

SK_API void setCdbPath(const char* path);
SK_API const char* getCdbPath();

SK_API void setUpDebuggingFromArgs(const char* vargs0);

SK_API int GenerateDumpAndPrintCallstack(EXCEPTION_POINTERS* pExceptionPointers);

#endif  // SK_BUILD_FOR_WIN

#endif  // win_dbghelp_DEFINED
