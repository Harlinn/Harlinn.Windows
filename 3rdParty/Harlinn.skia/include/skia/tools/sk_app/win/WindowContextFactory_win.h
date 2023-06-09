
/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef WindowContextFactory_win_DEFINED
#define WindowContextFactory_win_DEFINED

#include <Windows.h>

#include <memory>

#include <skia/core/SkTypes.h>

namespace sk_app {

class WindowContext;
struct DisplayParams;

namespace window_context_factory {

SK_API std::unique_ptr<WindowContext> MakeVulkanForWin(HWND, const DisplayParams&);

SK_API std::unique_ptr<WindowContext> MakeGLForWin(HWND, const DisplayParams&);

SK_API std::unique_ptr<WindowContext> MakeANGLEForWin(HWND, const DisplayParams&);

#ifdef SK_DIRECT3D
SK_API std::unique_ptr<WindowContext> MakeD3D12ForWin(HWND, const DisplayParams&);
#endif

#ifdef SK_DAWN
std::unique_ptr<WindowContext> MakeDawnD3D12ForWin(HWND, const DisplayParams&);
#endif

SK_API std::unique_ptr<WindowContext> MakeRasterForWin(HWND, const DisplayParams&);

}  // namespace window_context_factory

}  // namespace sk_app

#endif
