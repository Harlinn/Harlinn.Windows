/*
 * Copyright 2019 Google LLC.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef TessellationPathRenderer_DEFINED
#define TessellationPathRenderer_DEFINED

#include <skia/gpu/GrTypes.h>
#include "src/gpu/v1/PathRenderer.h"

class GrCaps;

namespace skgpu::v1 {

// This is the tie-in point for path rendering via PathTessellateOp. This path renderer draws
// paths using a hybrid Red Book "stencil, then cover" method. Curves get linearized by GPU
// tessellation shaders. This path renderer doesn't apply analytic AA, so it requires MSAA if AA is
// desired.
class TessellationPathRenderer final : public PathRenderer {
public:
    SK_API static bool IsSupported(const GrCaps&);

    const char* name() const override { return "Tessellation"; }

private:
    SK_API StencilSupport onGetStencilSupport(const GrStyledShape&) const override;
    SK_API CanDrawPath onCanDrawPath(const CanDrawPathArgs&) const override;
    SK_API bool onDrawPath(const DrawPathArgs&) override;
    SK_API void onStencilPath(const StencilPathArgs&) override;
};

} // namespace skgpu::v1

#endif // TessellationPathRenderer_DEFINED
