#ifndef _GL_PRIMITIVE_RENDERER_H
#define _GL_PRIMITIVE_RENDERER_H

//#include "OpenGLInclude.h"

#include <bullet/bullet_export.h>

struct PrimVec2
{
	PrimVec2()
	{
	}
	PrimVec2(float x, float y)
	{
		p[0] = x;
		p[1] = y;
	}
	float p[2];
};

struct PrimVec4
{
	PrimVec4() {}
	PrimVec4(float x, float y, float z, float w)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
		p[3] = w;
	}

	float p[4];
};

struct PrimVertex
{
	PrimVertex(const PrimVec4& p, const PrimVec4& c, const PrimVec2& u)
		: position(p),
		  colour(c),
		  uv(u)
	{
	}

	PrimVertex()
	{
	}
	PrimVec4 position;
	PrimVec4 colour;
	PrimVec2 uv;
};

class GLPrimitiveRenderer
{
	int m_screenWidth;
	int m_screenHeight;

	struct PrimInternalData* m_data;
	struct PrimInternalData2* m_data2;
	BT_EXPORT void loadBufferData();

public:
	BT_EXPORT GLPrimitiveRenderer(int screenWidth, int screenHeight);
	BT_EXPORT virtual ~GLPrimitiveRenderer();

	BT_EXPORT void drawRect(float x0, float y0, float x1, float y1, float color[4]);
	BT_EXPORT void drawTexturedRect(float x0, float y0, float x1, float y1, float color[4], float u0, float v0, float u1, float v1, int useRGBA = 0);
	BT_EXPORT void drawTexturedRect3D(const PrimVertex& v0, const PrimVertex& v1, const PrimVertex& v2, const PrimVertex& v3, float viewMat[16], float projMat[16], bool useRGBA = true);
	BT_EXPORT void drawLine();  //float from[4], float to[4], float color[4]);
	BT_EXPORT void setScreenSize(int width, int height);

	BT_EXPORT void drawTexturedRect2(float x0, float y0, float x1, float y1, float color[4], float u0, float v0, float u1, float v1, int useRGBA = 0);
	BT_EXPORT void drawTexturedRect2a(float x0, float y0, float x1, float y1, float color[4], float u0, float v0, float u1, float v1, int useRGBA = 0);
	BT_EXPORT void flushBatchedRects();

	BT_EXPORT void drawTexturedRect3D2Text(bool useRGBA = true);
	BT_EXPORT void drawTexturedRect3D2(PrimVertex* vertices, int numVertices, bool useRGBA = true);

	PrimInternalData* getData()
	{
		return m_data;
	}
};

#endif  //_GL_PRIMITIVE_RENDERER_H
