#ifndef BT_SDF_COLLISION_SHAPE_H
#define BT_SDF_COLLISION_SHAPE_H

#include "btConcaveShape.h"

class btSdfCollisionShape : public btConcaveShape
{
	struct btSdfCollisionShapeInternalData* m_data;

public:
	BT_EXPORT btSdfCollisionShape();
	BT_EXPORT virtual ~btSdfCollisionShape();

	BT_EXPORT bool initializeSDF(const char* sdfData, int sizeInBytes);

	BT_EXPORT virtual void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;
	BT_EXPORT virtual void setLocalScaling(const btVector3& scaling);
	BT_EXPORT virtual const btVector3& getLocalScaling() const;
	BT_EXPORT virtual void calculateLocalInertia(btScalar mass, btVector3& inertia) const;
	BT_EXPORT virtual const char* getName() const;
	BT_EXPORT virtual void setMargin(btScalar margin);
	BT_EXPORT virtual btScalar getMargin() const;

	BT_EXPORT virtual void processAllTriangles(btTriangleCallback* callback, const btVector3& aabbMin, const btVector3& aabbMax) const;

	BT_EXPORT bool queryPoint(const btVector3& ptInSDF, btScalar& distOut, btVector3& normal);
};

#endif  //BT_SDF_COLLISION_SHAPE_H
