/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrPorterDuffXferProcessor_DEFINED
#define GrPorterDuffXferProcessor_DEFINED

#include <skia/core/SkBlendMode.h>
#include <skia/gpu/GrTypes.h>
#include <skia/private/SkMacros.h>
#include "src/gpu/GrXferProcessor.h"

// See the comment above GrXPFactory's definition about this warning suppression.
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif
class GrPorterDuffXPFactory : public GrXPFactory {
public:
    SK_API static const GrXPFactory* Get(SkBlendMode blendMode);

    /** Because src-over is so common we special case it for performance reasons. If this returns
        null then the SimpleSrcOverXP() below should be used. */
    SK_API static sk_sp<const GrXferProcessor> MakeSrcOverXferProcessor(const GrProcessorAnalysisColor&,
                                                                 GrProcessorAnalysisCoverage,
                                                                 const GrCaps&);

    /** Returns a simple non-LCD porter duff blend XP with no optimizations or coverage. */
    SK_API static sk_sp<const GrXferProcessor> MakeNoCoverageXP(SkBlendMode);

    /** This XP implements non-LCD src-over using hw blend with no optimizations. It is returned
        by reference because it is global and its ref-cnting methods are not thread safe. */
    SK_API static const GrXferProcessor& SimpleSrcOverXP();

    SK_API static AnalysisProperties SrcOverAnalysisProperties(const GrProcessorAnalysisColor&,
                                                        const GrProcessorAnalysisCoverage&,
                                                        const GrCaps&,
                                                        GrClampType);

private:
    SK_API constexpr GrPorterDuffXPFactory(SkBlendMode);

    SK_API sk_sp<const GrXferProcessor> makeXferProcessor(const GrProcessorAnalysisColor&,
                                                   GrProcessorAnalysisCoverage,
                                                   const GrCaps&,
                                                   GrClampType) const override;

    SK_API AnalysisProperties analysisProperties(const GrProcessorAnalysisColor&,
                                          const GrProcessorAnalysisCoverage&,
                                          const GrCaps&,
                                          GrClampType) const override;

    GR_DECLARE_XP_FACTORY_TEST
    SK_API static void TestGetXPOutputTypes(const GrXferProcessor*, int* outPrimary, int* outSecondary);

    SkBlendMode fBlendMode;

    friend class GrPorterDuffTest; // for TestGetXPOutputTypes()
    using INHERITED = GrXPFactory;
};
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif
