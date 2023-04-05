/*
* Copyright 2016 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#ifndef Window_win_DEFINED
#define Window_win_DEFINED

#include "skia/tools/sk_app/Window.h"

#include <windows.h>

namespace sk_app {

class Window_win : public Window {
public:
    Window_win() : Window() {}
    SK_API ~Window_win() override;

    SK_API bool init(HINSTANCE instance);

    SK_API void setTitle(const char*) override;
    SK_API void show() override;

    SK_API bool attach(BackendType) override;

    SK_API void onInval() override;

    SK_API void setRequestedDisplayParams(const DisplayParams&, bool allowReattach) override;

private:
    SK_API void closeWindow();

    HINSTANCE   fHInstance;
    HWND        fHWnd;
    BackendType fBackend;
    bool        fInitializedBackend = false;

    using INHERITED = Window;
};

}   // namespace sk_app

#endif
