
/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef MockTestContext_DEFINED
#define MockTestContext_DEFINED

#include "skia/tools/gpu/TestContext.h"

namespace sk_gpu_test {

/**
 * Creates mock context object for use with GrContexts created with GrBackendApi::kMock. It will
 * trivially succeed at everything.
 */
SK_API TestContext* CreateMockTestContext(TestContext* shareContext = nullptr);

}  // namespace sk_gpu_test
#endif
