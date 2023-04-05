#ifndef SIMPLE_OPENGL2_APP_H
#define SIMPLE_OPENGL2_APP_H

#include "../CommonInterfaces/CommonGraphicsAppInterface.h"

#include <bullet/bullet_export.h>

class SimpleOpenGL2App : public CommonGraphicsApp
{
protected:
	struct SimpleOpenGL2AppInternalData* m_data;

public:
	BT_EXPORT SimpleOpenGL2App(const char* title, int width, int height);
	BT_EXPORT virtual ~SimpleOpenGL2App();

	BT_EXPORT virtual void drawGrid(DrawGridData data = DrawGridData());
	BT_EXPORT virtual void setUpAxis(int axis);
	BT_EXPORT virtual int getUpAxis() const;

	BT_EXPORT virtual void swapBuffer();
	BT_EXPORT virtual void drawText(const char* txt, int posX, int posY, float size, float colorRGBA[4]);

	BT_EXPORT virtual void drawTexturedRect(float x0, float y0, float x1, float y1, float color[4], float u0, float v0, float u1, float v1, int useRGBA){};
	BT_EXPORT virtual void setBackgroundColor(float red, float green, float blue);
	BT_EXPORT virtual int registerCubeShape(float halfExtentsX, float halfExtentsY, float halfExtentsZ, int textureIndex = -1, float textureScaling = 1);

	BT_EXPORT virtual int registerGraphicsUnitSphereShape(EnumSphereLevelOfDetail lod, int textureId = -1);
	BT_EXPORT virtual void drawText3D(const char* txt, float posX, float posZY, float posZ, float size);
	BT_EXPORT virtual void drawText3D(const char* txt, float position[3], float orientation[4], float color[4], float size, int optionFlag);

	BT_EXPORT virtual void registerGrid(int xres, int yres, float color0[4], float color1[4]);
};
#endif  //SIMPLE_OPENGL2_APP_H