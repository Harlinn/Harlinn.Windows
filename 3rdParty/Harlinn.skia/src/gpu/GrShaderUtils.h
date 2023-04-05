/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrShaderUtils_DEFINED
#define GrShaderUtils_DEFINED

#include <skia/core/SkTypes.h>
#include <skia/gpu/GrContextOptions.h>
#include <skia/private/SkSLProgramKind.h>
#include <skia/private/SkSLString.h>

namespace GrShaderUtils {

SK_API SkSL::String PrettyPrint(const SkSL::String& string);

SK_API void VisitLineByLine(const SkSL::String& text,
                     const std::function<void(int lineNumber, const char* lineText)>&);

// Prints shaders one line at the time. This ensures they don't get truncated by the adb log.
inline void PrintLineByLine(const SkSL::String& text) {
    VisitLineByLine(text, [](int lineNumber, const char* lineText) {
        SkDebugf("%4i\t%s\n", lineNumber, lineText);
    });
}

// Combines raw shader and error text into an easier-to-read error message with line numbers.
SK_API SkSL::String BuildShaderErrorMessage(const char* shader, const char* errors);

SK_API GrContextOptions::ShaderErrorHandler* DefaultShaderErrorHandler();

SK_API void PrintShaderBanner(SkSL::ProgramKind programKind);

}  // namespace GrShaderUtils

#endif
