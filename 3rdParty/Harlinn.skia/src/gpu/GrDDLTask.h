/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrDDLTask_DEFINED
#define GrDDLTask_DEFINED

#include <skia/core/SkPoint.h>
#include "src/gpu/GrRenderTask.h"

class GrRenderTargetProxy;

/**
 * This render task isolates the DDL's tasks from the rest of the DAG. This means that
 * the DDL's tasks cannot be reordered by the topological sort and are always executed
 * as a single block.
 * It almost entirely just forwards calls down to the DDL's render tasks.
 */
class GrDDLTask final : public GrRenderTask {
public:
    SK_API GrDDLTask(GrDrawingManager*,
              sk_sp<GrRenderTargetProxy> ddlTarget,
              sk_sp<const SkDeferredDisplayList>,
              SkIPoint offset);

    SK_API ~GrDDLTask() override;

    // The render tasks w/in the DDL don't appear in the DAG so need explicit notification
    // when they can free their contents.
    bool requiresExplicitCleanup() const override { return true; }

    SK_API void endFlush(GrDrawingManager*) override;

    SK_API void disown(GrDrawingManager*) override;

private:
    SK_API bool onIsUsed(GrSurfaceProxy*) const override;

    SK_API void gatherProxyIntervals(GrResourceAllocator*) const override;

    SK_API ExpectedOutcome onMakeClosed(GrRecordingContext*, SkIRect* targetUpdateBounds) override;

    SK_API void gatherIDs(SkSTArray<8, uint32_t, true>* idArray) const override;

    void onPrePrepare(GrRecordingContext*) override {
        // This entry point is only called when a DDL is snapped off of a recorder.
        // Since DDL tasks should never recursively appear within a DDL this should never
        // be called.
        SkASSERT(0);
    }

    SK_API void onPrepare(GrOpFlushState*) override;

    SK_API bool onExecute(GrOpFlushState*) override;

#if GR_TEST_UTILS
    SK_API void dump(const SkString& label,
              SkString indent,
              bool printDependencies,
              bool close) const final;
    const char* name() const final { return "DDL"; }
#endif
#ifdef SK_DEBUG
    void visitProxies_debugOnly(const GrVisitProxyFunc&) const override {}
#endif

    sk_sp<const SkDeferredDisplayList> fDDL;
    sk_sp<GrRenderTargetProxy>         fDDLTarget;
    SkIPoint                           fOffset;

    typedef GrRenderTask INHERITED;
};

#endif
