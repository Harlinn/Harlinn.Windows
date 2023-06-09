/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrProcessorUnitTest_DEFINED
#define GrProcessorUnitTest_DEFINED

#include <skia/core/SkTypes.h>

#if GR_TEST_UTILS

#include <skia/private/SkTArray.h>
#include "src/core/SkArenaAlloc.h"
#include "src/gpu/GrTestUtils.h"
#include "src/gpu/GrTextureProxy.h"

#include <tuple>

class SkMatrix;
class GrCaps;
class GrProxyProvider;
class GrProcessorTestData;
class GrTexture;
class GrXPFactory;
class GrGeometryProcessor;

namespace GrProcessorUnitTest {

/** This allows parent FPs to implement a test create with known leaf children in order to avoid
 *  creating an unbounded FP tree which may overflow various shader limits.
 *  MakeOptionalChildFP is the same as MakeChildFP, but can return null.
 */
SK_API std::unique_ptr<GrFragmentProcessor> MakeChildFP(GrProcessorTestData*);
SK_API std::unique_ptr<GrFragmentProcessor> MakeOptionalChildFP(GrProcessorTestData*);

}  // namespace GrProcessorUnitTest

/** GrProcessorTestData is an argument struct to TestCreate functions
 *  fTextures are valid textures that can optionally be used to construct
 *  TextureSampler. The first texture has a RGBA8 format and the second has Alpha8 format for the
 *  specific backend API. TestCreate functions are also free to create additional textures using
 *  the GrContext.
 */
class GrProcessorTestData {
public:
    using ViewInfo = std::tuple<GrSurfaceProxyView, GrColorType, SkAlphaType>;

    SK_API GrProcessorTestData(SkRandom* random, GrRecordingContext* context, int maxTreeDepth,
                        int numViews, const ViewInfo views[]);
    SK_API GrProcessorTestData(SkRandom* random, GrRecordingContext* context, int maxTreeDepth,
                        int numViews, const ViewInfo views[],
                        std::unique_ptr<GrFragmentProcessor> inputFP);
    SK_API GrProcessorTestData(const GrProcessorTestData&) = delete;
    SK_API ~GrProcessorTestData();

    GrRecordingContext* context() { return fContext; }
    SK_API GrProxyProvider* proxyProvider();
    SK_API const GrCaps* caps();
    SkArenaAlloc* allocator() { return fArena.get(); }
    SK_API std::unique_ptr<GrFragmentProcessor> inputFP();

    SK_API ViewInfo randomView();
    SK_API ViewInfo randomAlphaOnlyView();

    SkRandom* fRandom;
    int fCurrentTreeDepth = 0;
    int fMaxTreeDepth = 1;

private:
    GrRecordingContext* fContext;
    SkTArray<ViewInfo> fViews;
    std::unique_ptr<SkArenaAlloc> fArena;
    std::unique_ptr<GrFragmentProcessor> fInputFP;
};

class GrProcessor;
class GrTexture;

template <class ProcessorSmartPtr>
class SK_API GrProcessorTestFactory : private SkNoncopyable {
public:
    using MakeProc = ProcessorSmartPtr (*)(GrProcessorTestData*);

    GrProcessorTestFactory(MakeProc makeProc, const char* name);

    /** Pick a random factory function and create a processor.  */
    static ProcessorSmartPtr Make(GrProcessorTestData* data);

    /** Use factory function at Index idx to create a processor. */
    static ProcessorSmartPtr MakeIdx(int idx, GrProcessorTestData* data);

    /** Number of registered factory functions */
    static int Count();

private:
    /** A test function which verifies the count of factories. */
    static void VerifyFactoryCount();
    static SkTArray<GrProcessorTestFactory<ProcessorSmartPtr>*, true>* GetFactories();

    MakeProc fMakeProc;
    SkString fName;
};

extern template SK_TEMPLATE_API_DECL class GrProcessorTestFactory<std::unique_ptr<GrFragmentProcessor>>;
extern template SK_TEMPLATE_API_DECL class GrProcessorTestFactory<GrGeometryProcessor*>;

using GrFragmentProcessorTestFactory = GrProcessorTestFactory<std::unique_ptr<GrFragmentProcessor>>;
using GrGeometryProcessorTestFactory = GrProcessorTestFactory<GrGeometryProcessor*>;

class GrXPFactoryTestFactory : private SkNoncopyable {
public:
    using GetFn = const GrXPFactory*(GrProcessorTestData*);

    SK_API GrXPFactoryTestFactory(GetFn* getProc);

    SK_API static const GrXPFactory* Get(GrProcessorTestData* data);

private:
    /** A test function which verifies the count of factories. */
    SK_API static void VerifyFactoryCount();
    SK_API static SkTArray<GrXPFactoryTestFactory*, true>* GetFactories();

    GetFn* fGetProc;
};

#if SK_ALLOW_STATIC_GLOBAL_INITIALIZERS

/** GrProcessor subclasses should insert this macro in their declaration to be included in the
 *  program generation unit test.
 */
#define GR_DECLARE_GEOMETRY_PROCESSOR_TEST                        \
    static GrGeometryProcessorTestFactory gTestFactory SK_UNUSED; \
    static GrGeometryProcessor* TestCreate(GrProcessorTestData*);

#define GR_DECLARE_FRAGMENT_PROCESSOR_TEST                        \
    static GrFragmentProcessorTestFactory gTestFactory SK_UNUSED; \
    static std::unique_ptr<GrFragmentProcessor> TestCreate(GrProcessorTestData*);

#define GR_DECLARE_XP_FACTORY_TEST                                                                 \
    static GrXPFactoryTestFactory gTestFactory SK_UNUSED;                                          \
    static const GrXPFactory* TestGet(GrProcessorTestData*);

/** GrProcessor subclasses should insert this macro in their implementation file. They must then
 *  also implement this static function:
 *      GrProcessor* TestCreate(GrProcessorTestData*);
 */
#define GR_DEFINE_FRAGMENT_PROCESSOR_TEST(Effect) \
    GrFragmentProcessorTestFactory Effect::gTestFactory(Effect::TestCreate, #Effect)

#define GR_DEFINE_GEOMETRY_PROCESSOR_TEST(Effect) \
    GrGeometryProcessorTestFactory Effect::gTestFactory(Effect::TestCreate, #Effect)

#define GR_DEFINE_XP_FACTORY_TEST(Factory)                                                         \
    GrXPFactoryTestFactory Factory::gTestFactory(Factory::TestGet)

#else // !SK_ALLOW_STATIC_GLOBAL_INITIALIZERS

// The unit test relies on static initializers. Just declare the TestCreate function so that
// its definitions will compile.
#define GR_DECLARE_FRAGMENT_PROCESSOR_TEST                                                         \
    SK_API static std::unique_ptr<GrFragmentProcessor> TestCreate(GrProcessorTestData*);
#define GR_DEFINE_FRAGMENT_PROCESSOR_TEST(X)

// The unit test relies on static initializers. Just declare the TestCreate function so that
// its definitions will compile.
#define GR_DECLARE_GEOMETRY_PROCESSOR_TEST                                                         \
    SK_API static GrGeometryProcessor* TestCreate(GrProcessorTestData*);
#define GR_DEFINE_GEOMETRY_PROCESSOR_TEST(X)

// The unit test relies on static initializers. Just declare the TestGet function so that
// its definitions will compile.
#define GR_DECLARE_XP_FACTORY_TEST                                                                 \
    SK_API const GrXPFactory* TestGet(GrProcessorTestData*);
#define GR_DEFINE_XP_FACTORY_TEST(X)

#endif  // !SK_ALLOW_STATIC_GLOBAL_INITIALIZERS
#else   // GR_TEST_UTILS
    #define GR_DECLARE_GEOMETRY_PROCESSOR_TEST
    #define GR_DECLARE_FRAGMENT_PROCESSOR_TEST
    #define GR_DECLARE_XP_FACTORY_TEST
    #define GR_DEFINE_FRAGMENT_PROCESSOR_TEST(...)
    #define GR_DEFINE_GEOMETRY_PROCESSOR_TEST(...)
    #define GR_DEFINE_XP_FACTORY_TEST(...)
    #define GR_DECLARE_FRAGMENT_PROCESSOR_TEST
    #define GR_DEFINE_FRAGMENT_PROCESSOR_TEST(...)
    #define GR_DECLARE_GEOMETRY_PROCESSOR_TEST
    #define GR_DEFINE_GEOMETRY_PROCESSOR_TEST(...)
    #define GR_DECLARE_XP_FACTORY_TEST
    #define GR_DEFINE_XP_FACTORY_TEST(...)
#endif  // GR_TEST_UTILS
#endif  // GrProcessorUnitTest_DEFINED
