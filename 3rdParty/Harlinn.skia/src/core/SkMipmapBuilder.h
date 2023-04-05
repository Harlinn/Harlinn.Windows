/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkMipmapBuilder_DEFINED
#define SkMipmapBuilder_DEFINED

#include <skia/core/SkImage.h>

class SkMipmapBuilder {
public:
    SK_API SkMipmapBuilder(const SkImageInfo&);
    SK_API ~SkMipmapBuilder();

    SK_API int countLevels() const;
    SK_API SkPixmap level(int index) const;

    /**
     *  If these levels are compatible with src, return a new Image that combines src's base level
     *  with these levels as mip levels. If not compatible, this returns nullptr.
     */
    SK_API sk_sp<SkImage> attachTo(const SkImage* src);

    sk_sp<SkImage> attachTo(sk_sp<SkImage> src) {
        return this->attachTo(src.get());
    }

private:
    sk_sp<SkMipmap> fMM;

    friend class SkImage;
};

#endif
