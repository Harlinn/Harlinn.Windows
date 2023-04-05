/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2014 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BT_COLLISION_WORLD_IMPORTER_H
#define BT_COLLISION_WORLD_IMPORTER_H

#include "bullet/LinearMath/btTransform.h"
#include "bullet/LinearMath/btVector3.h"
#include "bullet/LinearMath/btAlignedObjectArray.h"
#include "bullet/LinearMath/btHashMap.h"

class btCollisionShape;
class btCollisionObject;
struct btBulletSerializedArrays;

struct ConstraintInput;
class btCollisionWorld;
struct btCollisionShapeData;
class btTriangleIndexVertexArray;
class btStridingMeshInterface;
struct btStridingMeshInterfaceData;
class btGImpactMeshShape;
class btOptimizedBvh;
struct btTriangleInfoMap;
class btBvhTriangleMeshShape;
class btPoint2PointConstraint;
class btHingeConstraint;
class btConeTwistConstraint;
class btGeneric6DofConstraint;
class btGeneric6DofSpringConstraint;
class btSliderConstraint;
class btGearConstraint;
struct btContactSolverInfo;

class btCollisionWorldImporter
{
protected:
	btCollisionWorld* m_collisionWorld;

	int m_verboseMode;

	btAlignedObjectArray<btCollisionShape*> m_allocatedCollisionShapes;
	btAlignedObjectArray<btCollisionObject*> m_allocatedRigidBodies;

	btAlignedObjectArray<btOptimizedBvh*> m_allocatedBvhs;
	btAlignedObjectArray<btTriangleInfoMap*> m_allocatedTriangleInfoMaps;
	btAlignedObjectArray<btTriangleIndexVertexArray*> m_allocatedTriangleIndexArrays;
	btAlignedObjectArray<btStridingMeshInterfaceData*> m_allocatedbtStridingMeshInterfaceDatas;
	btAlignedObjectArray<btCollisionObject*> m_allocatedCollisionObjects;

	btAlignedObjectArray<char*> m_allocatedNames;

	btAlignedObjectArray<int*> m_indexArrays;
	btAlignedObjectArray<short int*> m_shortIndexArrays;
	btAlignedObjectArray<unsigned char*> m_charIndexArrays;

	btAlignedObjectArray<btVector3FloatData*> m_floatVertexArrays;
	btAlignedObjectArray<btVector3DoubleData*> m_doubleVertexArrays;

	btHashMap<btHashPtr, btOptimizedBvh*> m_bvhMap;
	btHashMap<btHashPtr, btTriangleInfoMap*> m_timMap;

	btHashMap<btHashString, btCollisionShape*> m_nameShapeMap;
	btHashMap<btHashString, btCollisionObject*> m_nameColObjMap;

	btHashMap<btHashPtr, const char*> m_objectNameMap;

	btHashMap<btHashPtr, btCollisionShape*> m_shapeMap;
	btHashMap<btHashPtr, btCollisionObject*> m_bodyMap;

	//methods

	BT_EXPORT char* duplicateName(const char* name);

	BT_EXPORT btCollisionShape* convertCollisionShape(btCollisionShapeData* shapeData);

public:
	BT_EXPORT btCollisionWorldImporter(btCollisionWorld* world);

	BT_EXPORT virtual ~btCollisionWorldImporter();

	BT_EXPORT bool convertAllObjects(btBulletSerializedArrays* arrays);

	///delete all memory collision shapes, rigid bodies, constraints etc. allocated during the load.
	///make sure you don't use the dynamics world containing objects after you call this method
	BT_EXPORT virtual void deleteAllData();

	void setVerboseMode(int verboseMode)
	{
		m_verboseMode = verboseMode;
	}

	int getVerboseMode() const
	{
		return m_verboseMode;
	}

	// query for data
	BT_EXPORT int getNumCollisionShapes() const;
	BT_EXPORT btCollisionShape* getCollisionShapeByIndex(int index);
	BT_EXPORT int getNumRigidBodies() const;
	BT_EXPORT btCollisionObject* getRigidBodyByIndex(int index) const;

	BT_EXPORT int getNumBvhs() const;
	BT_EXPORT btOptimizedBvh* getBvhByIndex(int index) const;
	BT_EXPORT int getNumTriangleInfoMaps() const;
	BT_EXPORT btTriangleInfoMap* getTriangleInfoMapByIndex(int index) const;

	// queris involving named objects
	BT_EXPORT btCollisionShape* getCollisionShapeByName(const char* name);
	BT_EXPORT btCollisionObject* getCollisionObjectByName(const char* name);

	BT_EXPORT const char* getNameForPointer(const void* ptr) const;

	///those virtuals are called by load and can be overridden by the user

	//bodies

	BT_EXPORT virtual btCollisionObject* createCollisionObject(const btTransform& startTransform, btCollisionShape* shape, const char* bodyName);

	///shapes

	BT_EXPORT virtual btCollisionShape* createPlaneShape(const btVector3& planeNormal, btScalar planeConstant);
	BT_EXPORT virtual btCollisionShape* createBoxShape(const btVector3& halfExtents);
	BT_EXPORT virtual btCollisionShape* createSphereShape(btScalar radius);
	BT_EXPORT virtual btCollisionShape* createCapsuleShapeX(btScalar radius, btScalar height);
	BT_EXPORT virtual btCollisionShape* createCapsuleShapeY(btScalar radius, btScalar height);
	BT_EXPORT virtual btCollisionShape* createCapsuleShapeZ(btScalar radius, btScalar height);

	BT_EXPORT virtual btCollisionShape* createCylinderShapeX(btScalar radius, btScalar height);
	BT_EXPORT virtual btCollisionShape* createCylinderShapeY(btScalar radius, btScalar height);
	BT_EXPORT virtual btCollisionShape* createCylinderShapeZ(btScalar radius, btScalar height);
	BT_EXPORT virtual btCollisionShape* createConeShapeX(btScalar radius, btScalar height);
	BT_EXPORT virtual btCollisionShape* createConeShapeY(btScalar radius, btScalar height);
	BT_EXPORT virtual btCollisionShape* createConeShapeZ(btScalar radius, btScalar height);
	BT_EXPORT virtual class btTriangleIndexVertexArray* createTriangleMeshContainer();
	BT_EXPORT virtual btBvhTriangleMeshShape* createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh);
	BT_EXPORT virtual btCollisionShape* createConvexTriangleMeshShape(btStridingMeshInterface* trimesh);
#ifdef SUPPORT_GIMPACT_SHAPE_IMPORT
	BT_EXPORT virtual btGImpactMeshShape* createGimpactShape(btStridingMeshInterface* trimesh);
#endif  //SUPPORT_GIMPACT_SHAPE_IMPORT
	BT_EXPORT virtual btStridingMeshInterfaceData* createStridingMeshInterfaceData(btStridingMeshInterfaceData* interfaceData);

	BT_EXPORT virtual class btConvexHullShape* createConvexHullShape();
	BT_EXPORT virtual class btCompoundShape* createCompoundShape();
	BT_EXPORT virtual class btScaledBvhTriangleMeshShape* createScaledTrangleMeshShape(btBvhTriangleMeshShape* meshShape, const btVector3& localScalingbtBvhTriangleMeshShape);

	BT_EXPORT virtual class btMultiSphereShape* createMultiSphereShape(const btVector3* positions, const btScalar* radi, int numSpheres);

	BT_EXPORT virtual btTriangleIndexVertexArray* createMeshInterface(btStridingMeshInterfaceData& meshData);

	///acceleration and connectivity structures
	BT_EXPORT virtual btOptimizedBvh* createOptimizedBvh();
	BT_EXPORT virtual btTriangleInfoMap* createTriangleInfoMap();
};

#endif  //BT_WORLD_IMPORTER_H
