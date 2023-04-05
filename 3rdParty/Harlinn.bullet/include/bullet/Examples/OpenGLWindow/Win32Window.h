/*
Copyright (c) 2012 Advanced Micro Devices, Inc.  

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
//Originally written by Erwin Coumans

#ifndef _WIN32_WINDOW_H
#define _WIN32_WINDOW_H

struct InternalData2;

#include "../CommonInterfaces/CommonWindowInterface.h"

#include <bullet/bullet_export.h>

class Win32Window : public CommonWindowInterface
{
protected:
	struct InternalData2* m_data;

	BT_EXPORT void pumpMessage();

public:
	BT_EXPORT Win32Window();

	BT_EXPORT virtual ~Win32Window();

	BT_EXPORT virtual void createWindow(const b3gWindowConstructionInfo& ci);

	BT_EXPORT virtual void switchFullScreen(bool fullscreen, int width = 0, int height = 0, int colorBitsPerPixel = 0);

	BT_EXPORT virtual void closeWindow();

	BT_EXPORT virtual void runMainLoop();

	BT_EXPORT virtual void startRendering();

	BT_EXPORT virtual void renderAllObjects();

	BT_EXPORT virtual void endRendering();

	BT_EXPORT virtual float getTimeInSeconds();

	BT_EXPORT virtual void setDebugMessage(int x, int y, const char* message);

	BT_EXPORT virtual bool requestedExit() const;

	BT_EXPORT virtual void setRequestExit();

	BT_EXPORT virtual void getMouseCoordinates(int& x, int& y);

	BT_EXPORT virtual void setMouseMoveCallback(b3MouseMoveCallback mouseCallback);
	BT_EXPORT virtual void setMouseButtonCallback(b3MouseButtonCallback mouseCallback);
	BT_EXPORT virtual void setResizeCallback(b3ResizeCallback resizeCallback);
	BT_EXPORT virtual void setWheelCallback(b3WheelCallback wheelCallback);
	BT_EXPORT virtual void setKeyboardCallback(b3KeyboardCallback keyboardCallback);

	BT_EXPORT virtual b3MouseMoveCallback getMouseMoveCallback();
	BT_EXPORT virtual b3MouseButtonCallback getMouseButtonCallback();
	BT_EXPORT virtual b3ResizeCallback getResizeCallback();
	BT_EXPORT virtual b3WheelCallback getWheelCallback();
	BT_EXPORT virtual b3KeyboardCallback getKeyboardCallback();

	BT_EXPORT virtual void setRenderCallback(b3RenderCallback renderCallback);

	BT_EXPORT virtual void setWindowTitle(const char* title);

	BT_EXPORT virtual bool isModifierKeyPressed(int key);
};

#endif  //_WIN32_WINDOW_H