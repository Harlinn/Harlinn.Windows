// Copyright 2022 The RE2 Authors.  All Rights Reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef RE2_STRINGPIECE_H_
#define RE2_STRINGPIECE_H_

#include "absl/strings/string_view.h"

#ifdef BUILDING_HARLINN_RE2
#define HRE2_EXPORT __declspec(dllexport)
#define HRE2_TEMPLATE_EXPORT __declspec(dllexport)
#define HRE2_TEMPLATE_EXPORT_DECL
#else
#define HRE2_EXPORT __declspec(dllimport)
#define HRE2_TEMPLATE_EXPORT __declspec(dllimport)
#define HRE2_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.re2.lib")
#endif

namespace re2 {

// Until RE2 requires C++17 and uses std::string_view, allow users to
// continue to #include "re2/stringpiece.h" and use re2::StringPiece.
using StringPiece = absl::string_view;

}  // namespace re2

#endif  // RE2_STRINGPIECE_H_
