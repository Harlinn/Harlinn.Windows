#include "flatbuffers/flatc.h"
#include "flatbuffers/util.h"

namespace flatbuffers {

FB_EXPORT const char *g_program_name = nullptr;

void Warn(const FlatCompiler *flatc,
                 const std::string &warn, bool show_exe_name) {
  (void)flatc;
  if (show_exe_name) { printf("%s: ", g_program_name); }
  printf("warning: %s\n", warn.c_str());
}

void Error(const FlatCompiler *flatc,
                  const std::string &err, bool usage, bool show_exe_name) {
  if (show_exe_name) { printf("%s: ", g_program_name); }
  printf("error: %s\n", err.c_str());
  if (usage && flatc) {
    printf("%s", flatc->GetUsageString(g_program_name).c_str());
  }
  exit(1);
}

void LogCompilerWarn(const std::string &warn) {
  Warn(static_cast<const flatbuffers::FlatCompiler *>(nullptr), warn, true);
}
void LogCompilerError(const std::string &err) {
  Error(static_cast<const flatbuffers::FlatCompiler *>(nullptr), err, false,
        true);
}
}  // namespace flatbuffers
