/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkDescriptor_DEFINED
#define SkDescriptor_DEFINED

#include <memory>
#include <new>

#include <skia/private/SkMacros.h>
#include <skia/private/SkNoncopyable.h>
#include "src/core/SkScalerContext.h"

class SkDescriptor : SkNoncopyable {
public:
    static size_t ComputeOverhead(int entryCount) {
        SkASSERT(entryCount >= 0);
        return sizeof(SkDescriptor) + entryCount * sizeof(Entry);
    }

    SK_API static std::unique_ptr<SkDescriptor> Alloc(size_t length);

    //
    // Ensure the unsized delete is called.
    SK_API void operator delete(void* p);
    SK_API void* operator new(size_t);
    SK_API void* operator new(size_t, void* p) { return p; }

    uint32_t getLength() const { return fLength; }
    SK_API void* addEntry(uint32_t tag, size_t length, const void* data = nullptr);
    SK_API void computeChecksum();

    // Assumes that getLength <= capacity of this SkDescriptor.
    SK_API bool isValid() const;

#ifdef SK_DEBUG
    void assertChecksum() const {
        SkASSERT(SkDescriptor::ComputeChecksum(this) == fChecksum);
    }
#endif

    SK_API const void* findEntry(uint32_t tag, uint32_t* length) const;

    SK_API std::unique_ptr<SkDescriptor> copy() const;

    // This assumes that all memory added has a length that is a multiple of 4. This is checked
    // by the assert in addEntry.
    SK_API bool operator==(const SkDescriptor& other) const;
    bool operator!=(const SkDescriptor& other) const { return !(*this == other); }

    uint32_t getChecksum() const { return fChecksum; }

    struct Entry {
        uint32_t fTag;
        uint32_t fLen;
    };

#ifdef SK_DEBUG
    SK_API uint32_t getCount() const { return fCount; }
#endif

    SK_API SkString dumpRec() const;

private:
    SkDescriptor() = default;
    friend class SkDescriptorTestHelper;
    friend class SkAutoDescriptor;

    SK_API static uint32_t ComputeChecksum(const SkDescriptor* desc);

    uint32_t fChecksum{0};  // must be first
    uint32_t fLength{sizeof(SkDescriptor)};    // must be second
    uint32_t fCount{0};
};

class SkAutoDescriptor {
public:
    SK_API SkAutoDescriptor();
    SK_API explicit SkAutoDescriptor(size_t size);
    SK_API explicit SkAutoDescriptor(const SkDescriptor&);
    SK_API SkAutoDescriptor(const SkAutoDescriptor&);
    SK_API SkAutoDescriptor& operator=(const SkAutoDescriptor&);
    SK_API SkAutoDescriptor(SkAutoDescriptor&&);
    SK_API SkAutoDescriptor& operator=(SkAutoDescriptor&&);

    SK_API ~SkAutoDescriptor();

    SK_API void reset(size_t size);
    SK_API void reset(const SkDescriptor& desc);
    SkDescriptor* getDesc() const { SkASSERT(fDesc); return fDesc; }

private:
    SK_API void free();
    static constexpr size_t kStorageSize
            = sizeof(SkDescriptor)
              + sizeof(SkDescriptor::Entry) + sizeof(SkScalerContextRec) // for rec
              + sizeof(SkDescriptor::Entry) + sizeof(void*)              // for typeface
              + 32;   // slop for occasional small extras

    SkDescriptor*   fDesc{nullptr};
    alignas(uint32_t) char fStorage[kStorageSize];
};

#endif  //SkDescriptor_DEFINED
