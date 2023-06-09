/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "tests/Test.h"

#include "skia/core/SkMallocPixelRef.h"
#include "skia/core/SkPixelRef.h"
#include "skia/private/SkIDChangeListener.h"

static void decrement_counter_proc(void* pixels, void* ctx) {
    int* counter = (int*)ctx;
    *counter -= 1;
}

static void test_dont_leak_install(skiatest::Reporter* reporter) {
    bool success;
    int release_counter;
    SkImageInfo info;
    SkBitmap bm;

    info = SkImageInfo::MakeN32Premul(0, 0);
    release_counter = 1;
    success = bm.installPixels(info, nullptr, 0, decrement_counter_proc, &release_counter);
    REPORTER_ASSERT(reporter, true == success);
    bm.reset();
    REPORTER_ASSERT(reporter, 0 == release_counter);

    info = SkImageInfo::MakeN32Premul(10, 10);
    release_counter = 1;
    success = bm.installPixels(info, nullptr, 0, decrement_counter_proc, &release_counter);
    REPORTER_ASSERT(reporter, true == success);
    bm.reset();
    REPORTER_ASSERT(reporter, 0 == release_counter);

    info = SkImageInfo::MakeN32Premul(-10, -10);
    release_counter = 1;
    success = bm.installPixels(info, nullptr, 0, decrement_counter_proc, &release_counter);
    REPORTER_ASSERT(reporter, false == success);
    bm.reset();
    REPORTER_ASSERT(reporter, 0 == release_counter);
}

static void test_install(skiatest::Reporter* reporter) {
    bool success;
    SkImageInfo info = SkImageInfo::MakeN32Premul(0, 0);
    SkBitmap bm;
    // make sure we don't assert on an empty install
    success = bm.installPixels(info, nullptr, 0);
    REPORTER_ASSERT(reporter, success);

    // no pixels should be the same as setInfo()
    info = SkImageInfo::MakeN32Premul(10, 10);
    success = bm.installPixels(info, nullptr, 0);
    REPORTER_ASSERT(reporter, success);

}

class TestListener : public SkIDChangeListener {
public:
    explicit TestListener(int* ptr) : fPtr(ptr) {}
    void changed() override { (*fPtr)++; }
private:
    int* fPtr;
};

DEF_TEST(PixelRef_GenIDChange, r) {
    SkImageInfo info = SkImageInfo::MakeN32Premul(10, 10);

    sk_sp<SkPixelRef> pixelRef = SkMallocPixelRef::MakeAllocate(info, 0);

    // Register a listener.
    int count = 0;
    pixelRef->addGenIDChangeListener(sk_make_sp<TestListener>(&count));
    REPORTER_ASSERT(r, 0 == count);

    // No one has looked at our pixelRef's generation ID, so invalidating it doesn't make sense.
    // (An SkPixelRef tree falls in the forest but there's nobody around to hear it.  Do we care?)
    pixelRef->notifyPixelsChanged();
    REPORTER_ASSERT(r, 0 == count);

    // Force the generation ID to be calculated.
    REPORTER_ASSERT(r, 0 != pixelRef->getGenerationID());

    // Our listener was dropped in the first call to notifyPixelsChanged().  This is a no-op.
    pixelRef->notifyPixelsChanged();
    REPORTER_ASSERT(r, 0 == count);

    // Force the generation ID to be recalculated, then add a listener.
    REPORTER_ASSERT(r, 0 != pixelRef->getGenerationID());
    pixelRef->addGenIDChangeListener(sk_make_sp<TestListener>(&count));
    pixelRef->notifyPixelsChanged();
    REPORTER_ASSERT(r, 1 == count);

    // Check that asking for deregistration causes the listener to not be called.
    REPORTER_ASSERT(r, 0 != pixelRef->getGenerationID());
    auto listener = sk_make_sp<TestListener>(&count);
    pixelRef->addGenIDChangeListener(listener);
    REPORTER_ASSERT(r, 1 == count);
    listener->markShouldDeregister();
    pixelRef->notifyPixelsChanged();
    REPORTER_ASSERT(r, 1 == count);

    // Check that we use deregistration to prevent unbounded growth.
    REPORTER_ASSERT(r, 0 != pixelRef->getGenerationID());
    listener = sk_make_sp<TestListener>(&count);
    pixelRef->addGenIDChangeListener(listener);
    REPORTER_ASSERT(r, 1 == count);
    listener->markShouldDeregister();
    // Add second listener. Should deregister first listener.
    pixelRef->addGenIDChangeListener(sk_make_sp<TestListener>(&count));
    REPORTER_ASSERT(r, listener->unique());

    // Quick check that nullptr is safe.
    REPORTER_ASSERT(r, 0 != pixelRef->getGenerationID());
    pixelRef->addGenIDChangeListener(nullptr);
    pixelRef->notifyPixelsChanged();

    test_install(r);
    test_dont_leak_install(r);
}
