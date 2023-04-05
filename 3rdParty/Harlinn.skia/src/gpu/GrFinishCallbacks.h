/*
 * Copyright 2020 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrFinishCallbacks_DEFINED
#define GrFinishCallbacks_DEFINED

#include <skia/gpu/GrTypes.h>
#include <skia/private/GrTypesPriv.h>

#include <list>

class GrGpu;

/**
 * Maintains a list of callbacks to be called when work on the GPU is complete.
 */

class GrFinishCallbacks {
public:
    SK_API GrFinishCallbacks(GrGpu* gpu);
    SK_API ~GrFinishCallbacks();

    /**
     * Call all the callbacks in the list. This will block until all work is done.
     *
     * @param doDelete        delete the contained fence object.
     */
    SK_API void callAll(bool doDelete);

    /**
     * Add a new callback to the list.
     *
     * @param finishedProc    The function to call when GPU work is complete.
     * @param finishedContext The context object to pass back to the callback.
     */
    SK_API void add(GrGpuFinishedProc finishedProc, GrGpuFinishedContext finishedContext);

    /**
     * Check if any GPU work is complete, and call the associated callbacks.
     * This call is non-blocking.
     */
    SK_API void check();

    /**
     * Returns true if the callback list is empty.
     */
    bool empty() const { return fCallbacks.empty(); }

private:
    struct FinishCallback {
        GrGpuFinishedProc     fCallback;
        GrGpuFinishedContext  fContext;
        GrFence               fFence;
    };

    GrGpu*                    fGpu;
    std::list<FinishCallback> fCallbacks;
};

#endif
