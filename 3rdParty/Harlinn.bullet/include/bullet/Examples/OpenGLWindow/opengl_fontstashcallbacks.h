#ifndef _OPENGL_FONTSTASH_CALLBACKS_H
#define _OPENGL_FONTSTASH_CALLBACKS_H

#include "fontstash.h"
struct PrimInternalData;
class GLPrimitiveRenderer;

struct InternalOpenGL2RenderCallbacks : public RenderCallbacks
{
	virtual PrimInternalData* getData() = 0;

	BT_EXPORT virtual ~InternalOpenGL2RenderCallbacks();

	BT_EXPORT virtual void updateTexture(sth_texture* texture, sth_glyph* glyph, int textureWidth, int textureHeight);
	BT_EXPORT virtual void render(sth_texture* texture);

	BT_EXPORT void display2();
};

BT_EXPORT void dumpTextureToPng(int screenWidth, int screenHeight, const char* fileName);

struct SimpleOpenGL2RenderCallbacks : public InternalOpenGL2RenderCallbacks
{
	PrimInternalData* m_data;
	virtual PrimInternalData* getData()
	{
		return m_data;
	}
	SimpleOpenGL2RenderCallbacks(PrimInternalData* data)
		: m_data(data)
	{
	}
	virtual ~SimpleOpenGL2RenderCallbacks()
	{
	}
};

struct OpenGL2RenderCallbacks : public InternalOpenGL2RenderCallbacks
{
	GLPrimitiveRenderer* m_primRender2;
	BT_EXPORT virtual PrimInternalData* getData();

	virtual void setWorldPosition(float pos[3]) {}
	virtual void setWorldOrientation(float orn[4]) {}
	virtual void setColorRGBA(float color[4]) {}

	BT_EXPORT OpenGL2RenderCallbacks(GLPrimitiveRenderer* primRender);
	BT_EXPORT virtual ~OpenGL2RenderCallbacks();
};

#endif  //_OPENGL_FONTSTASH_CALLBACKS_H
