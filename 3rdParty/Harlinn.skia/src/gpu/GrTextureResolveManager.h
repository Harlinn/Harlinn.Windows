/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrTextureResolveManager_DEFINED
#define GrTextureResolveManager_DEFINED

#include <skia/core/SkRefCnt.h>
#include "src/gpu/GrDrawingManager.h"

class GrCaps;
class GrDrawingManager;
class GrRenderTask;

/*
 * This class is a shallow view of the drawing manager. It is passed to render tasks when setting up
 * the dependency DAG, and gives them limited access to functionality for making new tasks that
 * regenerate mipmaps and/or resolve MSAA.
 */
class GrTextureResolveManager {
public:
    explicit GrTextureResolveManager(GrDrawingManager* drawingManager)
            : fDrawingManager(drawingManager) {}

    GrTextureResolveRenderTask* newTextureResolveRenderTask(const GrCaps& caps) const {
        SkASSERT(fDrawingManager);
        return fDrawingManager->newTextureResolveRenderTask(caps);
    }

private:
    GrDrawingManager* fDrawingManager;
};

#endif
