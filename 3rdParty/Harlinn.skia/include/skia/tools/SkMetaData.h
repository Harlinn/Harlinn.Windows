/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkMetaData_DEFINED
#define SkMetaData_DEFINED

#include "skia/core/SkScalar.h"

/** A map from c-string keys to arrays of POD (int32_t, kScalar, void*, or bool)
    values.
*/
class SkMetaData {
public:
    SkMetaData() {}
    ~SkMetaData() { if (fRec) { this->reset(); } }
    SK_API void reset();

    SK_API bool findS32(const char name[], int32_t* value = nullptr) const;
    SK_API bool findScalar(const char name[], SkScalar* value = nullptr) const;
    SK_API const SkScalar* findScalars(const char name[], int* count,
                                SkScalar values[] = nullptr) const;
    SK_API bool findPtr(const char name[], void** value = nullptr) const;
    SK_API bool findBool(const char name[], bool* value = nullptr) const;

    bool hasS32(const char name[], int32_t value) const {
        int32_t v;
        return this->findS32(name, &v) && v == value;
    }
    bool hasScalar(const char name[], SkScalar value) const {
        SkScalar v;
        return this->findScalar(name, &v) && v == value;
    }
    bool hasPtr(const char name[], void* value) const {
        void* v;
        return this->findPtr(name, &v) && v == value;
    }
    bool hasBool(const char name[], bool value) const {
        bool    v;
        return this->findBool(name, &v) && v == value;
    }

    SK_API void setS32(const char name[], int32_t value);
    SK_API void setScalar(const char name[], SkScalar value);
    SK_API SkScalar* setScalars(const char name[], int count, const SkScalar values[] = nullptr);
    SK_API void setPtr(const char name[], void* value);
    SK_API void setBool(const char name[], bool value);

    SK_API bool removeS32(const char name[]);
    SK_API bool removeScalar(const char name[]);
    SK_API bool removePtr(const char name[]);
    SK_API bool removeBool(const char name[]);

    enum Type {
        kS32_Type,
        kScalar_Type,
        kPtr_Type,
        kBool_Type,

        kTypeCount
    };

    struct Rec;
    class Iter;
    friend class Iter;

    class Iter {
    public:
        Iter() : fRec(nullptr) {}
        SK_API Iter(const SkMetaData&);

        /** Reset the iterator, so that calling next() will return the first
            data element. This is done implicitly in the constructor.
        */
        SK_API void reset(const SkMetaData&);

        /** Each time next is called, it returns the name of the next data element,
            or null when there are no more elements. If non-null is returned, then the
            element's type is returned (if not null), and the number of data values
            is returned in count (if not null).
        */
        SK_API const char* next(Type*, int* count);

    private:
        Rec* fRec;
    };

public:
    struct Rec {
        Rec*        fNext;
        uint16_t    fDataCount; // number of elements
        uint8_t     fDataLen;   // sizeof a single element
        uint8_t     fType;

        const void* data() const { return (this + 1); }
        void*       data() { return (this + 1); }
        const char* name() const { return (const char*)this->data() + fDataLen * fDataCount; }
        char*       name() { return (char*)this->data() + fDataLen * fDataCount; }

        SK_API static Rec* Alloc(size_t);
        SK_API static void Free(Rec*);
    };
    Rec*    fRec = nullptr;

    SK_API const Rec* find(const char name[], Type) const;
    SK_API void* set(const char name[], const void* data, size_t len, Type, int count);
    SK_API bool remove(const char name[], Type);

    SK_API SkMetaData(const SkMetaData&) = delete;
    SK_API SkMetaData& operator=(const SkMetaData&) = delete;

private:
    struct FindResult {
        SkMetaData::Rec* rec;
        SkMetaData::Rec* prev;
    };
    SK_API FindResult findWithPrev(const char name[], Type type) const;
    SK_API void remove(FindResult);
};

#endif
