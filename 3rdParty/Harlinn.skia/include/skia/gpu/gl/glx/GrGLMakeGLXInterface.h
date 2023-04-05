#pragma once
/*
 * Copyright 2021 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/gpu/GrTypes.h>

#include <skia/core/SkRefCnt.h>

struct GrGLInterface;

SK_API sk_sp<const GrGLInterface> GrGLMakeGLXInterface();
