/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkBitmapCache_DEFINED
#define SkBitmapCache_DEFINED

#include <skia/core/SkRect.h>
#include <memory>

class SkBitmap;
class SkImage;
class SkImage_Base;
struct SkImageInfo;
class SkMipmap;
class SkPixmap;
class SkResourceCache;

uint64_t SkMakeResourceCacheSharedIDForBitmap(uint32_t bitmapGenID);

void SkNotifyBitmapGenIDIsStale(uint32_t bitmapGenID);

struct SkBitmapCacheDesc {
    uint32_t    fImageID;       // != 0
    SkIRect     fSubset;        // always set to a valid rect (entire or subset)

    void validate() const {
        SkASSERT(fImageID);
        SkASSERT(fSubset.fLeft >= 0 && fSubset.fTop >= 0);
        SkASSERT(fSubset.width() > 0 && fSubset.height() > 0);
    }

    SK_API static SkBitmapCacheDesc Make(const SkImage*);
    SK_API static SkBitmapCacheDesc Make(uint32_t genID, const SkIRect& subset);
};

class SkBitmapCache {
public:
    /**
     *  Search based on the desc. If found, returns true and
     *  result will be set to the matching bitmap with its pixels already locked.
     */
    SK_API static bool Find(const SkBitmapCacheDesc&, SkBitmap* result);

    class Rec;
    struct RecDeleter { void operator()(Rec* r) { PrivateDeleteRec(r); } };
    typedef std::unique_ptr<Rec, RecDeleter> RecPtr;

    SK_API static RecPtr Alloc(const SkBitmapCacheDesc&, const SkImageInfo&, SkPixmap*);
    SK_API static void Add(RecPtr, SkBitmap*);

private:
    static void PrivateDeleteRec(Rec*);
};

class SkMipmapCache {
public:
    SK_API static const SkMipmap* FindAndRef(const SkBitmapCacheDesc&,
                                      SkResourceCache* localCache = nullptr);
    SK_API static const SkMipmap* AddAndRef(const SkImage_Base*,
                                     SkResourceCache* localCache = nullptr);
};

#endif
