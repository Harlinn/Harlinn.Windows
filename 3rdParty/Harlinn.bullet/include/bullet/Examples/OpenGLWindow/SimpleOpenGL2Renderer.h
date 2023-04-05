
#ifndef SIMPLE_OPENGL2_RENDERER_H
#define SIMPLE_OPENGL2_RENDERER_H

#include "../CommonInterfaces/CommonRenderInterface.h"
#include "SimpleCamera.h"

class SimpleOpenGL2Renderer : public CommonRenderInterface
{
	struct SimpleOpenGL2RendererInternalData* m_data;

	BT_EXPORT void drawSceneInternal(int pass, int cameraUpAxis);
	BT_EXPORT void drawOpenGL(int instanceIndex);

public:
	BT_EXPORT SimpleOpenGL2Renderer(int width, int height);
	BT_EXPORT virtual ~SimpleOpenGL2Renderer();

	BT_EXPORT virtual void init();

	BT_EXPORT virtual void updateCamera(int upAxis);

	BT_EXPORT virtual const CommonCameraInterface* getActiveCamera() const;
	BT_EXPORT virtual CommonCameraInterface* getActiveCamera();
	BT_EXPORT virtual void setActiveCamera(CommonCameraInterface* cam);

	BT_EXPORT virtual void setLightPosition(const float lightPos[3]);
	BT_EXPORT virtual void setLightPosition(const double lightPos[3]);
	BT_EXPORT virtual void setShadowMapResolution(int shadowMapResolution) {}
	BT_EXPORT virtual void setShadowMapIntensity(double shadowMapIntensity) {}
	BT_EXPORT virtual void setShadowMapWorldSize(float worldSize) {}
	BT_EXPORT virtual void resize(int width, int height);
	BT_EXPORT virtual void setBackgroundColor(const double rgbBackground[3]) {}

	BT_EXPORT virtual void removeAllInstances();
	BT_EXPORT virtual void removeGraphicsInstance(int instanceUid);

	BT_EXPORT virtual bool readSingleInstanceTransformToCPU(float* position, float* orientation, int srcIndex);
	BT_EXPORT virtual void writeSingleInstanceColorToCPU(const float* color, int srcIndex);
	BT_EXPORT virtual void writeSingleInstanceColorToCPU(const double* color, int srcIndex);
	BT_EXPORT virtual void writeSingleInstanceScaleToCPU(const float* scale, int srcIndex);
	BT_EXPORT virtual void writeSingleInstanceScaleToCPU(const double* scale, int srcIndex);
	BT_EXPORT virtual void writeSingleInstanceSpecularColorToCPU(const double* specular, int srcIndex) {}
	BT_EXPORT virtual void writeSingleInstanceSpecularColorToCPU(const float* specular, int srcIndex) {}
	BT_EXPORT virtual void writeSingleInstanceFlagsToCPU(int flags, int srcIndex) {}
	BT_EXPORT virtual void getCameraViewMatrix(float viewMat[16]) const;
	BT_EXPORT virtual void getCameraProjectionMatrix(float projMat[16]) const;
	virtual void drawTexturedTriangleMesh(float worldPosition[3], float worldOrientation[4], const float* vertices, int numvertices, const unsigned int* indices, int numIndices, float color[4], int textureIndex = -1, int vertexLayout = 0)
	{
	}

	BT_EXPORT virtual void renderScene();

	BT_EXPORT virtual int getScreenWidth();
	BT_EXPORT virtual int getScreenHeight();
	BT_EXPORT virtual int registerTexture(const unsigned char* texels, int width, int height, bool flipTexelsY);
	BT_EXPORT virtual void updateTexture(int textureIndex, const unsigned char* texels, bool flipTexelsY);
	BT_EXPORT virtual void activateTexture(int textureIndex);
	BT_EXPORT virtual void removeTexture(int textureIndex);

	BT_EXPORT virtual int registerGraphicsInstance(int shapeIndex, const double* position, const double* quaternion, const double* color, const double* scaling);

	BT_EXPORT virtual int registerGraphicsInstance(int shapeIndex, const float* position, const float* quaternion, const float* color, const float* scaling);

	BT_EXPORT virtual void drawLines(const float* positions, const float color[4], int numPoints, int pointStrideInBytes, const unsigned int* indices, int numIndices, float pointDrawSize);

	BT_EXPORT virtual void drawLine(const float from[4], const float to[4], const float color[4], float lineWidth);

	BT_EXPORT virtual int registerShape(const float* vertices, int numvertices, const int* indices, int numIndices, int primitiveType = B3_GL_TRIANGLES, int textureIndex = -1);

	BT_EXPORT virtual void writeSingleInstanceTransformToCPU(const float* position, const float* orientation, int srcIndex);

	BT_EXPORT virtual void writeSingleInstanceTransformToCPU(const double* position, const double* orientation, int srcIndex);

	BT_EXPORT virtual int getTotalNumInstances() const;

	BT_EXPORT virtual void writeTransforms();

	BT_EXPORT virtual void drawLine(const double from[4], const double to[4], const double color[4], double lineWidth);

	BT_EXPORT virtual void drawPoint(const float* position, const float color[4], float pointDrawSize);

	BT_EXPORT virtual void drawPoint(const double* position, const double color[4], double pointDrawSize);

	BT_EXPORT virtual void updateShape(int shapeIndex, const float* vertices, int numVertices);

	BT_EXPORT virtual void clearZBuffer();

	virtual struct GLInstanceRendererInternalData* getInternalData()
	{
		return 0;
	}
};
#endif  //SIMPLE_OPENGL2_RENDERER_H
