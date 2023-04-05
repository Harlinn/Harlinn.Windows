#pragma once
/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_STRING
#define SKSL_STRING

#include <skia/core/SkStringView.h>
#include <skia/private/SkSLDefines.h>
#include <cstring>
#include <stdarg.h>
#include <string>

#ifndef SKSL_STANDALONE
#include <skia/core/SkString.h>
#endif

namespace SkSL {

class String;

class String : public std::string {
public:
    using std::string::string;

    explicit String(std::string s) : INHERITED(std::move(s)) {}
    explicit String(skstd::string_view s) : INHERITED(s.data(), s.length()) {}
    // TODO(johnstiles): add operator skstd::string_view

    SK_API static String printf(const char* fmt, ...) SK_PRINTF_LIKE(1, 2);
    SK_API void appendf(const char* fmt, ...) SK_PRINTF_LIKE(2, 3);
    SK_API void vappendf(const char* fmt, va_list va);

    bool starts_with(const char prefix[]) const {
        return skstd::string_view(data(), size()).starts_with(prefix);
    }
    bool ends_with(const char suffix[]) const {
        return skstd::string_view(data(), size()).ends_with(suffix);
    }

    SK_API bool consumeSuffix(const char suffix[]);

    SK_API String operator+(const char* s) const;
    SK_API String operator+(const String& s) const;
    SK_API String operator+(skstd::string_view s) const;
    SK_API String& operator+=(char c);
    SK_API String& operator+=(const char* s);
    SK_API String& operator+=(const String& s);
    SK_API String& operator+=(skstd::string_view s);
    SK_API friend String operator+(const char* s1, const String& s2);

private:
    using INHERITED = std::string;
};

SK_API String operator+(skstd::string_view left, skstd::string_view right);

SK_API String to_string(double value);
SK_API String to_string(int32_t value);
SK_API String to_string(uint32_t value);
SK_API String to_string(int64_t value);
SK_API String to_string(uint64_t value);

SK_API bool stod(const skstd::string_view& s, SKSL_FLOAT* value);
SK_API bool stoi(const skstd::string_view& s, SKSL_INT* value);

} // namespace SkSL

namespace std {
    template<> struct hash<SkSL::String> {
        size_t operator()(const SkSL::String& s) const {
            return hash<std::string>{}(s);
        }
    };
} // namespace std

#endif
