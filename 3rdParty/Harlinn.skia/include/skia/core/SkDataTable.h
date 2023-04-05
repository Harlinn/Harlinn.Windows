#pragma once
/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkDataTable_DEFINED
#define SkDataTable_DEFINED

#include <skia/core/SkData.h>
#include <skia/private/SkTDArray.h>

/**
 *  Like SkData, SkDataTable holds an immutable data buffer. The data buffer is
 *  organized into a table of entries, each with a length, so the entries are
 *  not required to all be the same size.
 */
class SkDataTable : public SkRefCnt {
public:
    /**
     *  Returns true if the table is empty (i.e. has no entries).
     */
    bool isEmpty() const { return 0 == fCount; }

    /**
     *  Return the number of entries in the table. 0 for an empty table
     */
    int count() const { return fCount; }

    /**
     *  Return the size of the index'th entry in the table. The caller must
     *  ensure that index is valid for this table.
     */
    SK_API size_t atSize(int index) const;

    /**
     *  Return a pointer to the data of the index'th entry in the table.
     *  The caller must ensure that index is valid for this table.
     *
     *  @param size If non-null, this returns the byte size of this entry. This
     *              will be the same value that atSize(index) would return.
     */
    SK_API const void* at(int index, size_t* size = nullptr) const;

    template <typename T>
    const T* atT(int index, size_t* size = nullptr) const {
        return reinterpret_cast<const T*>(this->at(index, size));
    }

    /**
     *  Returns the index'th entry as a c-string, and assumes that the trailing
     *  null byte had been copied into the table as well.
     */
    const char* atStr(int index) const {
        size_t size;
        const char* str = this->atT<const char>(index, &size);
        SkASSERT(strlen(str) + 1 == size);
        return str;
    }

    typedef void (*FreeProc)(void* context);

    SK_API static sk_sp<SkDataTable> MakeEmpty();

    /**
     *  Return a new DataTable that contains a copy of the data stored in each
     *  "array".
     *
     *  @param ptrs array of points to each element to be copied into the table.
     *  @param sizes array of byte-lengths for each entry in the corresponding
     *               ptrs[] array.
     *  @param count the number of array elements in ptrs[] and sizes[] to copy.
     */
    SK_API static sk_sp<SkDataTable> MakeCopyArrays(const void * const * ptrs,
                                             const size_t sizes[], int count);

    /**
     *  Return a new table that contains a copy of the data in array.
     *
     *  @param array contiguous array of data for all elements to be copied.
     *  @param elemSize byte-length for a given element.
     *  @param count the number of entries to be copied out of array. The number
     *               of bytes that will be copied is count * elemSize.
     */
    SK_API static sk_sp<SkDataTable> MakeCopyArray(const void* array, size_t elemSize, int count);

    SK_API static sk_sp<SkDataTable> MakeArrayProc(const void* array, size_t elemSize, int count,
                                            FreeProc proc, void* context);

private:
    struct Dir {
        const void* fPtr;
        uintptr_t   fSize;
    };

    int         fCount;
    size_t      fElemSize;
    union {
        const Dir*  fDir;
        const char* fElems;
    } fU;

    FreeProc    fFreeProc;
    void*       fFreeProcContext;

    SK_API SkDataTable();
    SK_API SkDataTable(const void* array, size_t elemSize, int count,
                FreeProc, void* context);
    SK_API SkDataTable(const Dir*, int count, FreeProc, void* context);
    SK_API ~SkDataTable() override;

    friend class SkDataTableBuilder;    // access to Dir

    using INHERITED = SkRefCnt;
};

#endif
