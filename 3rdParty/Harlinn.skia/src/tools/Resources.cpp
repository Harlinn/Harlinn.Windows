/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "skia/core/SkBitmap.h"
#include "skia/core/SkData.h"
#include "skia/core/SkImage.h"
#include "skia/core/SkImageGenerator.h"
#include "skia/core/SkStream.h"
#include "skia/core/SkTypeface.h"
#include "src/core/SkOSFile.h"
#include "src/utils/SkOSPath.h"
#include "skia/tools/ResourceFactory.h"
#include "skia/tools/Resources.h"
#include "skia/tools/flags/CommandLineFlags.h"

static DEFINE_string2(resourcePath, i, "resources",
                      "Directory with test resources: images, fonts, etc.");

sk_sp<SkData> (*gResourceFactory)(const char*) = nullptr;

SkString GetResourcePath(const char* resource) {
    return SkOSPath::Join(FLAGS_resourcePath[0], resource);
}

void SetResourcePath(const char* resource) {
    FLAGS_resourcePath.set(0, resource);
}

bool DecodeDataToBitmap(sk_sp<SkData> data, SkBitmap* dst) {
    std::unique_ptr<SkImageGenerator> gen(SkImageGenerator::MakeFromEncoded(std::move(data)));
    return gen && dst->tryAllocPixels(gen->getInfo()) &&
        gen->getPixels(gen->getInfo().makeColorSpace(nullptr), dst->getPixels(), dst->rowBytes());
}

std::unique_ptr<SkStreamAsset> GetResourceAsStream(const char* resource) {
    auto data = GetResourceAsData(resource);
    return data ? std::unique_ptr<SkStreamAsset>(new SkMemoryStream(std::move(data)))
                : nullptr;
}

sk_sp<SkData> GetResourceAsData(const char* resource) {
    if (sk_sp<SkData> data = gResourceFactory
                           ? gResourceFactory(resource)
                           : SkData::MakeFromFileName(GetResourcePath(resource).c_str())) {
        return data;
    }
    SkDebugf("Resource \"%s\" not found.\n", GetResourcePath(resource).c_str());
    #ifdef SK_TOOLS_REQUIRE_RESOURCES
    SK_ABORT("missing resource");
    #endif
    return nullptr;
}

sk_sp<SkTypeface> MakeResourceAsTypeface(const char* resource, int ttcIndex) {
    return SkTypeface::MakeFromStream(GetResourceAsStream(resource), ttcIndex);
}
