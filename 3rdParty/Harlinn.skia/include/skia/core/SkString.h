#pragma once
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkString_DEFINED
#define SkString_DEFINED

#include <skia/core/SkRefCnt.h>
#include <skia/core/SkScalar.h>
#include <skia/core/SkTypes.h>
#include <skia/private/SkMalloc.h>
#include <skia/private/SkTArray.h>
#include <skia/private/SkTo.h>

#include <stdarg.h>
#include <string.h>
#include <atomic>
#include <string>

namespace skstd {
    class string_view;
}

/*  Some helper functions for C strings */
static inline bool SkStrStartsWith(const char string[], const char prefixStr[]) {
    SkASSERT(string);
    SkASSERT(prefixStr);
    return !strncmp(string, prefixStr, strlen(prefixStr));
}
static inline bool SkStrStartsWith(const char string[], const char prefixChar) {
    SkASSERT(string);
    return (prefixChar == *string);
}

SK_API bool SkStrEndsWith(const char string[], const char suffixStr[]);
SK_API bool SkStrEndsWith(const char string[], const char suffixChar);

int SkStrStartsWithOneOf(const char string[], const char prefixes[]);

static inline int SkStrFind(const char string[], const char substring[]) {
    const char *first = strstr(string, substring);
    if (nullptr == first) return -1;
    return SkToInt(first - &string[0]);
}

static inline int SkStrFindLastOf(const char string[], const char subchar) {
    const char* last = strrchr(string, subchar);
    if (nullptr == last) return -1;
    return SkToInt(last - &string[0]);
}

static inline bool SkStrContains(const char string[], const char substring[]) {
    SkASSERT(string);
    SkASSERT(substring);
    return (-1 != SkStrFind(string, substring));
}
static inline bool SkStrContains(const char string[], const char subchar) {
    SkASSERT(string);
    char tmp[2];
    tmp[0] = subchar;
    tmp[1] = '\0';
    return (-1 != SkStrFind(string, tmp));
}

/*
 *  The SkStrAppend... methods will write into the provided buffer, assuming it is large enough.
 *  Each method has an associated const (e.g. kSkStrAppendU32_MaxSize) which will be the largest
 *  value needed for that method's buffer.
 *
 *  char storage[kSkStrAppendU32_MaxSize];
 *  SkStrAppendU32(storage, value);
 *
 *  Note : none of the SkStrAppend... methods write a terminating 0 to their buffers. Instead,
 *  the methods return the ptr to the end of the written part of the buffer. This can be used
 *  to compute the length, and/or know where to write a 0 if that is desired.
 *
 *  char storage[kSkStrAppendU32_MaxSize + 1];
 *  char* stop = SkStrAppendU32(storage, value);
 *  size_t len = stop - storage;
 *  *stop = 0;   // valid, since storage was 1 byte larger than the max.
 */

static constexpr int kSkStrAppendU32_MaxSize = 10;
SK_API char*   SkStrAppendU32(char buffer[], uint32_t);
static constexpr int kSkStrAppendU64_MaxSize = 20;
SK_API char*   SkStrAppendU64(char buffer[], uint64_t, int minDigits);

static constexpr int kSkStrAppendS32_MaxSize = kSkStrAppendU32_MaxSize + 1;
SK_API char*   SkStrAppendS32(char buffer[], int32_t);
static constexpr int kSkStrAppendS64_MaxSize = kSkStrAppendU64_MaxSize + 1;
SK_API char*   SkStrAppendS64(char buffer[], int64_t, int minDigits);

/**
 *  Floats have at most 8 significant digits, so we limit our %g to that.
 *  However, the total string could be 15 characters: -1.2345678e-005
 *
 *  In theory we should only expect up to 2 digits for the exponent, but on
 *  some platforms we have seen 3 (as in the example above).
 */
static constexpr int kSkStrAppendScalar_MaxSize = 15;

/**
 *  Write the scalar in decimal format into buffer, and return a pointer to
 *  the next char after the last one written. Note: a terminating 0 is not
 *  written into buffer, which must be at least kSkStrAppendScalar_MaxSize.
 *  Thus if the caller wants to add a 0 at the end, buffer must be at least
 *  kSkStrAppendScalar_MaxSize + 1 bytes large.
 */
SK_API char* SkStrAppendScalar(char buffer[], SkScalar);

/** \class SkString

    Light weight class for managing strings. Uses reference
    counting to make string assignments and copies very fast
    with no extra RAM cost. Assumes UTF8 encoding.
*/
class SkString {
public:
    SK_API             SkString();
    SK_API explicit    SkString(size_t len);
    SK_API explicit    SkString(const char text[]);
    SK_API             SkString(const char text[], size_t len);
    SK_API             SkString(const SkString&);
    SK_API             SkString(SkString&&);
    SK_API explicit    SkString(const std::string&);
    SK_API explicit    SkString(skstd::string_view);
    SK_API             ~SkString();

    bool        isEmpty() const { return 0 == fRec->fLength; }
    size_t      size() const { return (size_t) fRec->fLength; }
    const char* c_str() const { return fRec->data(); }
    char operator[](size_t n) const { return this->c_str()[n]; }

    SK_API bool equals(const SkString&) const;
    SK_API bool equals(const char text[]) const;
    SK_API bool equals(const char text[], size_t len) const;

    bool startsWith(const char prefixStr[]) const {
        return SkStrStartsWith(fRec->data(), prefixStr);
    }
    bool startsWith(const char prefixChar) const {
        return SkStrStartsWith(fRec->data(), prefixChar);
    }
    bool endsWith(const char suffixStr[]) const {
        return SkStrEndsWith(fRec->data(), suffixStr);
    }
    bool endsWith(const char suffixChar) const {
        return SkStrEndsWith(fRec->data(), suffixChar);
    }
    bool contains(const char substring[]) const {
        return SkStrContains(fRec->data(), substring);
    }
    bool contains(const char subchar) const {
        return SkStrContains(fRec->data(), subchar);
    }
    int find(const char substring[]) const {
        return SkStrFind(fRec->data(), substring);
    }
    int findLastOf(const char subchar) const {
        return SkStrFindLastOf(fRec->data(), subchar);
    }

    friend bool operator==(const SkString& a, const SkString& b) {
        return a.equals(b);
    }
    friend bool operator!=(const SkString& a, const SkString& b) {
        return !a.equals(b);
    }

    // these methods edit the string

    SK_API SkString& operator=(const SkString&);
    SK_API SkString& operator=(SkString&&);
    SK_API SkString& operator=(const char text[]);

    SK_API char* writable_str();
    char& operator[](size_t n) { return this->writable_str()[n]; }

    SK_API void reset();
    /** String contents are preserved on resize. (For destructive resize, `set(nullptr, length)`.)
     * `resize` automatically reserves an extra byte at the end of the buffer for a null terminator.
     */
    SK_API void resize(size_t len);
    void set(const SkString& src) { *this = src; }
    SK_API void set(const char text[]);
    SK_API void set(const char text[], size_t len);

    void insert(size_t offset, const SkString& src) { this->insert(offset, src.c_str(), src.size()); }
    SK_API void insert(size_t offset, const char text[]);
    SK_API void insert(size_t offset, const char text[], size_t len);
    SK_API void insertUnichar(size_t offset, SkUnichar);
    SK_API void insertS32(size_t offset, int32_t value);
    SK_API void insertS64(size_t offset, int64_t value, int minDigits = 0);
    SK_API void insertU32(size_t offset, uint32_t value);
    SK_API void insertU64(size_t offset, uint64_t value, int minDigits = 0);
    SK_API void insertHex(size_t offset, uint32_t value, int minDigits = 0);
    SK_API void insertScalar(size_t offset, SkScalar);

    void append(const SkString& str) { this->insert((size_t)-1, str); }
    void append(const char text[]) { this->insert((size_t)-1, text); }
    void append(const char text[], size_t len) { this->insert((size_t)-1, text, len); }
    void appendUnichar(SkUnichar uni) { this->insertUnichar((size_t)-1, uni); }
    void appendS32(int32_t value) { this->insertS32((size_t)-1, value); }
    void appendS64(int64_t value, int minDigits = 0) { this->insertS64((size_t)-1, value, minDigits); }
    void appendU32(uint32_t value) { this->insertU32((size_t)-1, value); }
    void appendU64(uint64_t value, int minDigits = 0) { this->insertU64((size_t)-1, value, minDigits); }
    void appendHex(uint32_t value, int minDigits = 0) { this->insertHex((size_t)-1, value, minDigits); }
    void appendScalar(SkScalar value) { this->insertScalar((size_t)-1, value); }

    void prepend(const SkString& str) { this->insert(0, str); }
    void prepend(const char text[]) { this->insert(0, text); }
    void prepend(const char text[], size_t len) { this->insert(0, text, len); }
    void prependUnichar(SkUnichar uni) { this->insertUnichar(0, uni); }
    void prependS32(int32_t value) { this->insertS32(0, value); }
    void prependS64(int32_t value, int minDigits = 0) { this->insertS64(0, value, minDigits); }
    void prependHex(uint32_t value, int minDigits = 0) { this->insertHex(0, value, minDigits); }
    void prependScalar(SkScalar value) { this->insertScalar((size_t)-1, value); }

    SK_API void printf(const char format[], ...) SK_PRINTF_LIKE(2, 3);
    SK_API void printVAList(const char format[], va_list);
    SK_API void appendf(const char format[], ...) SK_PRINTF_LIKE(2, 3);
    SK_API void appendVAList(const char format[], va_list);
    SK_API void prependf(const char format[], ...) SK_PRINTF_LIKE(2, 3);
    SK_API void prependVAList(const char format[], va_list);

    SK_API void remove(size_t offset, size_t length);

    SkString& operator+=(const SkString& s) { this->append(s); return *this; }
    SkString& operator+=(const char text[]) { this->append(text); return *this; }
    SkString& operator+=(const char c) { this->append(&c, 1); return *this; }

    /**
     *  Swap contents between this and other. This function is guaranteed
     *  to never fail or throw.
     */
    SK_API void swap(SkString& other);

private:
    struct Rec {
    public:
        constexpr Rec(uint32_t len, int32_t refCnt) : fLength(len), fRefCnt(refCnt) {}
        static sk_sp<Rec> Make(const char text[], size_t len);
        char* data() { return fBeginningOfData; }
        const char* data() const { return fBeginningOfData; }
        SK_API void ref() const;
        SK_API void unref() const;
        SK_API bool unique() const;
#ifdef SK_DEBUG
        SK_API int32_t getRefCnt() const;
#endif
        uint32_t fLength; // logically size_t, but we want it to stay 32 bits

    private:
        mutable std::atomic<int32_t> fRefCnt;
        char fBeginningOfData[1] = {'\0'};

        // Ensure the unsized delete is called.
        void operator delete(void* p) { ::operator delete(p); }
    };
    sk_sp<Rec> fRec;

#ifdef SK_DEBUG
    SK_API const SkString& validate() const;
#else
    const SkString& validate() const { return *this; }
#endif

    SK_API static const Rec gEmptyRec;
};

/// Creates a new string and writes into it using a printf()-style format.
SK_API SkString SkStringPrintf(const char* format, ...) SK_PRINTF_LIKE(1, 2);
/// This makes it easier to write a caller as a VAR_ARGS function where the format string is
/// optional.
static inline SkString SkStringPrintf() { return SkString(); }

static inline void swap(SkString& a, SkString& b) {
    a.swap(b);
}

enum SkStrSplitMode {
    // Strictly return all results. If the input is ",," and the separator is ',' this will return
    // an array of three empty strings.
    kStrict_SkStrSplitMode,

    // Only nonempty results will be added to the results. Multiple separators will be
    // coalesced. Separators at the beginning and end of the input will be ignored.  If the input is
    // ",," and the separator is ',', this will return an empty vector.
    kCoalesce_SkStrSplitMode
};

// Split str on any characters in delimiters into out.  (Think, strtok with a sane API.)
SK_API void SkStrSplit(const char* str, const char* delimiters, SkStrSplitMode splitMode,
                SkTArray<SkString>* out);
inline void SkStrSplit(const char* str, const char* delimiters, SkTArray<SkString>* out) {
    SkStrSplit(str, delimiters, kCoalesce_SkStrSplitMode, out);
}

#endif
