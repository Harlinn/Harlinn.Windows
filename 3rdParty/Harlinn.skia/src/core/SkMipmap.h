/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkMipmap_DEFINED
#define SkMipmap_DEFINED

#include <skia/core/SkPixmap.h>
#include <skia/core/SkScalar.h>
#include <skia/core/SkSize.h>
#include <skia/private/SkImageInfoPriv.h>
#include "src/core/SkCachedData.h"
#include "src/shaders/SkShaderBase.h"

class SkBitmap;
class SkData;
class SkDiscardableMemory;
class SkMipmapBuilder;

typedef SkDiscardableMemory* (*SkDiscardableFactoryProc)(size_t bytes);

/*
 * SkMipmap will generate mipmap levels when given a base mipmap level image.
 *
 * Any function which deals with mipmap levels indices will start with index 0
 * being the first mipmap level which was generated. Said another way, it does
 * not include the base level in its range.
 */
class SkMipmap : public SkCachedData {
public:
    // Allocate and fill-in a mipmap. If computeContents is false, we just allocated
    // and compute the sizes/rowbytes, but leave the pixel-data uninitialized.
    SK_API static SkMipmap* Build(const SkPixmap& src, SkDiscardableFactoryProc,
                           bool computeContents = true);

    SK_API static SkMipmap* Build(const SkBitmap& src, SkDiscardableFactoryProc);

    // Determines how many levels a SkMipmap will have without creating that mipmap.
    // This does not include the base mipmap level that the user provided when
    // creating the SkMipmap.
    SK_API static int ComputeLevelCount(int baseWidth, int baseHeight);
    SK_API static int ComputeLevelCount(SkISize s) { return ComputeLevelCount(s.width(), s.height()); }

    // Determines the size of a given mipmap level.
    // |level| is an index into the generated mipmap levels. It does not include
    // the base level. So index 0 represents mipmap level 1.
    SK_API static SkISize ComputeLevelSize(int baseWidth, int baseHeight, int level);

    // Computes the fractional level based on the scaling in X and Y.
    SK_API static float ComputeLevel(SkSize scaleSize);

    // We use a block of (possibly discardable) memory to hold an array of Level structs, followed
    // by the pixel data for each level. On 32-bit platforms, Level would naturally be 4 byte
    // aligned, so the pixel data could end up with 4 byte alignment. If the pixel data is F16,
    // it must be 8 byte aligned. To ensure this, keep the Level struct 8 byte aligned as well.
    struct alignas(8) Level {
        SkPixmap    fPixmap;
        SkSize      fScale; // < 1.0
    };

    SK_API bool extractLevel(SkSize scale, Level*) const;

    // countLevels returns the number of mipmap levels generated (which does not
    // include the base mipmap level).
    SK_API int countLevels() const;

    // |index| is an index into the generated mipmap levels. It does not include
    // the base level. So index 0 represents mipmap level 1.
    SK_API bool getLevel(int index, Level*) const;

    SK_API bool validForRootLevel(const SkImageInfo&) const;

    SK_API sk_sp<SkData> serialize() const;
    SK_API static bool Deserialize(SkMipmapBuilder*, const void* data, size_t size);

protected:
    void onDataChange(void* oldData, void* newData) override {
        fLevels = (Level*)newData; // could be nullptr
    }

private:
    sk_sp<SkColorSpace> fCS;
    Level*              fLevels;    // managed by the baseclass, may be null due to onDataChanged.
    int                 fCount;

    SkMipmap(void* malloc, size_t size) : INHERITED(malloc, size) {}
    SkMipmap(size_t size, SkDiscardableMemory* dm) : INHERITED(size, dm) {}

    SK_API static size_t AllocLevelsSize(int levelCount, size_t pixelSize);

    using INHERITED = SkCachedData;
};

#endif
