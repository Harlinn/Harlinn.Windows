/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkAutoPixmapStorage_DEFINED
#define SkAutoPixmapStorage_DEFINED

#include <skia/core/SkPixmap.h>
#include <skia/private/SkMalloc.h>

class SkAutoPixmapStorage : public SkPixmap {
public:
    SK_API SkAutoPixmapStorage();
    SK_API ~SkAutoPixmapStorage();

    SK_API SkAutoPixmapStorage(SkAutoPixmapStorage&& other);

    /**
    * Leave the moved-from object in a free-but-valid state.
    */
    SK_API SkAutoPixmapStorage& operator=(SkAutoPixmapStorage&& other);

    /**
    *  Try to allocate memory for the pixels needed to match the specified Info. On success
    *  return true and fill out the pixmap to point to that memory. The storage will be freed
    *  when this object is destroyed, or if another call to tryAlloc() or alloc() is made.
    *
    *  On failure, return false and reset() the pixmap to empty.
    */
    SK_API bool tryAlloc(const SkImageInfo&);

    /**
    *  Allocate memory for the pixels needed to match the specified Info and fill out the pixmap
    *  to point to that memory. The storage will be freed when this object is destroyed,
    *  or if another call to tryAlloc() or alloc() is made.
    *
    *  If the memory cannot be allocated, calls SK_ABORT().
    */
    SK_API void alloc(const SkImageInfo&);

    /**
    * Gets the size and optionally the rowBytes that would be allocated by SkAutoPixmapStorage if
    * alloc/tryAlloc was called.
    */
    SK_API static size_t AllocSize(const SkImageInfo& info, size_t* rowBytes);

    /**
    * Returns a void* of the allocated pixel memory and resets the pixmap. If the storage hasn't
    * been allocated, the result is NULL. The caller is responsible for calling sk_free to free
    * the returned memory.
    */
    SK_API void* SK_WARN_UNUSED_RESULT detachPixels();

    /**
    *  Returns an SkData object wrapping the allocated pixels memory, and resets the pixmap.
    *  If the storage hasn't been allocated, the result is NULL.
    */
    SK_API sk_sp<SkData> SK_WARN_UNUSED_RESULT detachPixelsAsData();

    // We wrap these so we can clear our internal storage

    void reset() {
        this->freeStorage();
        this->INHERITED::reset();
    }
    void reset(const SkImageInfo& info, const void* addr, size_t rb) {
        this->freeStorage();
        this->INHERITED::reset(info, addr, rb);
    }

    bool SK_WARN_UNUSED_RESULT reset(const SkMask& mask) {
        this->freeStorage();
        return this->INHERITED::reset(mask);
    }

private:
    void*   fStorage;

    void freeStorage() {
        sk_free(fStorage);
        fStorage = nullptr;
    }

    using INHERITED = SkPixmap;
};

#endif
