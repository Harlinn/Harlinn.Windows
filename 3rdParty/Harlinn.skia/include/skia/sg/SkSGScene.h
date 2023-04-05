/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGScene_DEFINED
#define SkSGScene_DEFINED

#include "skia/core/SkRefCnt.h"
#include "skia/core/SkTypes.h"

#include <memory>
#include <vector>

class SkCanvas;
struct SkPoint;

namespace sksg {

class InvalidationController;
class RenderNode;

/**
 * Holds a scene root.  Provides high-level methods for rendering.
 *
 */
class Scene final {
public:
    SK_API static std::unique_ptr<Scene> Make(sk_sp<RenderNode> root);
    SK_API ~Scene();
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    SK_API void render(SkCanvas*) const;
    SK_API void revalidate(InvalidationController* = nullptr);
    SK_API const RenderNode* nodeAt(const SkPoint&) const;

private:
    SK_API explicit Scene(sk_sp<RenderNode> root);

    const sk_sp<RenderNode> fRoot;
};

} // namespace sksg

#endif // SkSGScene_DEFINED
