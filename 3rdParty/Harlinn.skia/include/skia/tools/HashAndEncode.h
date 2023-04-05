// Copyright 2019 Google LLC.
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "skia/core/SkBitmap.h"
#include "skia/core/SkStream.h"
#include "skia/tools/flags/CommandLineFlags.h"

// HashAndEncode transforms any SkBitmap into a standard format, currently
// 16-bit unpremul RGBA in the Rec. 2020 color space.  This lets us compare
// images from different backends or configurations, using feedHash() for
// direct content-based hashing, or encodePNG() for visual comparison.
class HashAndEncode {
public:
    SK_API explicit HashAndEncode(const SkBitmap&);

    // Feed uncompressed pixel data into a hash function like MD5.
    SK_API void feedHash(SkWStream*) const;

    // Encode pixels as a PNG in our standard format, with md5 and key/properties as metadata.
    SK_API bool encodePNG(SkWStream*,
                   const char* md5,
                   CommandLineFlags::StringArray key,
                   CommandLineFlags::StringArray properties) const;

private:
    const SkISize               fSize;
    std::unique_ptr<uint64_t[]> fPixels;  // In our standard format mentioned above.
};

