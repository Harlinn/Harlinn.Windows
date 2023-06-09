/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGAttributeParser_DEFINED
#define SkSVGAttributeParser_DEFINED

#include <vector>

#include "skia/private/SkNoncopyable.h"
#include "skia/svg/SkSVGTypes.h"
#include "src/core/SkTLazy.h"

class SkSVGAttributeParser : public SkNoncopyable {
public:
    SK_API SkSVGAttributeParser(const char[]);

    SK_API bool parseInteger(SkSVGIntegerType*);
    SK_API bool parseViewBox(SkSVGViewBoxType*);
    SK_API bool parsePreserveAspectRatio(SkSVGPreserveAspectRatio*);

    // TODO: Migrate all parse*() functions to this style (and delete the old version)
    //      so they can be used by parse<T>():
    bool parse(SkSVGIntegerType* v) { return parseInteger(v); }

    template <typename T> using ParseResult = SkTLazy<T>;

    template <typename T> static ParseResult<T> parse(const char* value) {
        ParseResult<T> result;
        T parsedValue;
        if (SkSVGAttributeParser(value).parse(&parsedValue)) {
            result.set(std::move(parsedValue));
        }
        return result;
    }

    template <typename T>
    static ParseResult<T> parse(const char* expectedName,
                                const char* name,
                                const char* value) {
        if (!strcmp(name, expectedName)) {
            return parse<T>(value);
        }

        return ParseResult<T>();
    }

    template <typename PropertyT>
    static ParseResult<PropertyT> parseProperty(const char* expectedName,
                                                const char* name,
                                                const char* value) {
        if (strcmp(name, expectedName) != 0) {
            return ParseResult<PropertyT>();
        }

        if (!strcmp(value, "inherit")) {
            PropertyT result(SkSVGPropertyState::kInherit);
            return ParseResult<PropertyT>(&result);
        }

        auto pr = parse<typename PropertyT::ValueT>(value);
        if (pr.isValid()) {
            PropertyT result(*pr);
            return ParseResult<PropertyT>(&result);
        }

        return ParseResult<PropertyT>();
    }

private:
    // Stack-only
    void* operator new(size_t) = delete;
    void* operator new(size_t, void*) = delete;

    template <typename T>
    bool parse(T*);

    template <typename F>
    bool advanceWhile(F func);

    bool matchStringToken(const char* token, const char** newPos = nullptr) const;

    bool parseWSToken();
    bool parseEOSToken();
    bool parseSepToken();
    bool parseCommaWspToken();
    bool parseExpectedStringToken(const char*);
    bool parseScalarToken(SkScalar*);
    bool parseInt32Token(int32_t*);
    bool parseHexToken(uint32_t*);
    bool parseLengthUnitToken(SkSVGLength::Unit*);
    bool parseNamedColorToken(SkColor*);
    bool parseHexColorToken(SkColor*);
    bool parseColorComponentToken(int32_t*);
    bool parseRGBColorToken(SkColor*);
    bool parseFuncIRI(SkSVGFuncIRI*);

    // Transform helpers
    bool parseMatrixToken(SkMatrix*);
    bool parseTranslateToken(SkMatrix*);
    bool parseScaleToken(SkMatrix*);
    bool parseRotateToken(SkMatrix*);
    bool parseSkewXToken(SkMatrix*);
    bool parseSkewYToken(SkMatrix*);

    // Parses a sequence of 'WS* <prefix> WS* (<nested>)', where the nested sequence
    // is handled by the passed functor.
    template <typename Func, typename T>
    bool parseParenthesized(const char* prefix, Func, T* result);

    template <typename T>
    bool parseList(std::vector<T>*);

    template <typename T, typename TArray>
    bool parseEnumMap(const TArray& arr, T* result) {
        for (size_t i = 0; i < SK_ARRAY_COUNT(arr); ++i) {
            if (this->parseExpectedStringToken(std::get<0>(arr[i]))) {
                *result = std::get<1>(arr[i]);
                return true;
            }
        }
        return false;
    }

    // The current position in the input string.
    const char* fCurPos;

    using INHERITED = SkNoncopyable;
};

#endif // SkSVGAttributeParser_DEFINED
