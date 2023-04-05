#ifndef SIMPLE_OPENGL3_APP_H
#define SIMPLE_OPENGL3_APP_H

#include "../OpenGLWindow/GLInstancingRenderer.h"
#include "../OpenGLWindow/GLPrimitiveRenderer.h"
#include "../CommonInterfaces/CommonWindowInterface.h"

#include "../CommonInterfaces/CommonGraphicsAppInterface.h"

struct SimpleOpenGL3App : public CommonGraphicsApp
{
	struct SimpleInternalData* m_data;

	class GLPrimitiveRenderer* m_primRenderer;
	class GLInstancingRenderer* m_instancingRenderer;
	BT_EXPORT virtual void setBackgroundColor(float red, float green, float blue);
	BT_EXPORT virtual void setMp4Fps(int fps);

	BT_EXPORT SimpleOpenGL3App(const char* title, int width, int height, bool allowRetina = true, int windowType = 0, int renderDevice = -1, int maxNumObjectCapacity = 128 * 1024, int maxShapeCapacityInBytes = 128 * 1024 * 1024);

	BT_EXPORT virtual ~SimpleOpenGL3App();

	BT_EXPORT virtual int registerCubeShape(float halfExtentsX = 1.f, float halfExtentsY = 1.f, float halfExtentsZ = 1.f, int textureIndex = -1, float textureScaling = 1);
	BT_EXPORT virtual int registerGraphicsUnitSphereShape(EnumSphereLevelOfDetail lod, int textureId = -1);
	BT_EXPORT virtual void registerGrid(int xres, int yres, float color0[4], float color1[4]);
	BT_EXPORT void dumpNextFrameToPng(const char* pngFilename);
	BT_EXPORT void dumpFramesToVideo(const char* mp4Filename);
	BT_EXPORT virtual void getScreenPixels(unsigned char* rgbaBuffer, int bufferSizeInBytes, float* depthBuffer, int depthBufferSizeInBytes);
	BT_EXPORT virtual void setViewport(int width, int height);

	BT_EXPORT void drawGrid(DrawGridData data = DrawGridData());
	BT_EXPORT virtual void setUpAxis(int axis);
	BT_EXPORT virtual int getUpAxis() const;

	BT_EXPORT virtual void swapBuffer();
	BT_EXPORT virtual void drawText(const char* txt, int posX, int posY, float size, float colorRGBA[4]);
	BT_EXPORT virtual void drawText3D(const char* txt, float posX, float posZY, float posZ, float size);
	BT_EXPORT virtual void drawText3D(const char* txt, float position[3], float orientation[4], float color[4], float size, int optionFlag);

	BT_EXPORT virtual void drawTexturedRect(float x0, float y0, float x1, float y1, float color[4], float u0, float v0, float u1, float v1, int useRGBA);
	BT_EXPORT struct sth_stash* getFontStash();
};

#endif  //SIMPLE_OPENGL3_APP_H
