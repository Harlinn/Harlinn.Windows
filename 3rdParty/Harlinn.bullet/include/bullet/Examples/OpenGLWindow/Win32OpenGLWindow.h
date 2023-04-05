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

#ifndef _WIN32_OPENGL_RENDER_MANAGER_H
#define _WIN32_OPENGL_RENDER_MANAGER_H

#include "Win32Window.h"

#define b3gDefaultOpenGLWindow Win32OpenGLWindow

class Win32OpenGLWindow : public Win32Window
{
	bool m_OpenGLInitialized;

protected:
	BT_EXPORT void enableOpenGL();

	BT_EXPORT void disableOpenGL();

public:
	BT_EXPORT Win32OpenGLWindow();

	BT_EXPORT virtual ~Win32OpenGLWindow();

	BT_EXPORT virtual void createWindow(const b3gWindowConstructionInfo& ci);

	BT_EXPORT virtual void closeWindow();

	BT_EXPORT virtual void startRendering();

	BT_EXPORT virtual void renderAllObjects();

	BT_EXPORT virtual void endRendering();

	virtual float getRetinaScale() const { return 1.f; }
	BT_EXPORT virtual void setAllowRetina(bool /*allowRetina*/){};

	BT_EXPORT virtual int getWidth() const;
	BT_EXPORT virtual int getHeight() const;

	BT_EXPORT virtual int fileOpenDialog(char* fileName, int maxFileNameLength);
};

#endif  //_WIN32_OPENGL_RENDER_MANAGER_H
