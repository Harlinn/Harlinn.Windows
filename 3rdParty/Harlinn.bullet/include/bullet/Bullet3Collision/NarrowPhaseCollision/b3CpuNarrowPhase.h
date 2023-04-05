#ifndef B3_CPU_NARROWPHASE_H
#define B3_CPU_NARROWPHASE_H

#include "bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3Collidable.h"
#include "bullet/Bullet3Common/b3AlignedObjectArray.h"
#include "bullet/Bullet3Common/b3Vector3.h"
#include "bullet/Bullet3Collision/BroadPhaseCollision/shared/b3Aabb.h"
#include "bullet/Bullet3Common/shared/b3Int4.h"
#include "bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3RigidBodyData.h"
#include "bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3Contact4Data.h"

class b3CpuNarrowPhase
{
protected:
	struct b3CpuNarrowPhaseInternalData* m_data;
	int m_acceleratedCompanionShapeIndex;
	int m_planeBodyIndex;
	int m_static0Index;

	int registerConvexHullShapeInternal(class b3ConvexUtility* convexPtr, b3Collidable& col);
	int registerConcaveMeshShape(b3AlignedObjectArray<b3Vector3>* vertices, b3AlignedObjectArray<int>* indices, b3Collidable& col, const float* scaling);

public:
	BT_EXPORT b3CpuNarrowPhase(const struct b3Config& config);

	BT_EXPORT virtual ~b3CpuNarrowPhase(void);

	BT_EXPORT int registerSphereShape(float radius);
	BT_EXPORT int registerPlaneShape(const b3Vector3& planeNormal, float planeConstant);

	BT_EXPORT int registerCompoundShape(b3AlignedObjectArray<b3GpuChildShape>* childShapes);
	BT_EXPORT int registerFace(const b3Vector3& faceNormal, float faceConstant);

	BT_EXPORT int registerConcaveMesh(b3AlignedObjectArray<b3Vector3>* vertices, b3AlignedObjectArray<int>* indices, const float* scaling);

	//do they need to be merged?

	BT_EXPORT int registerConvexHullShape(b3ConvexUtility* utilPtr);
	BT_EXPORT int registerConvexHullShape(const float* vertices, int strideInBytes, int numVertices, const float* scaling);

	//int registerRigidBody(int collidableIndex, float mass, const float* position, const float* orientation, const float* aabbMin, const float* aabbMax,bool writeToGpu);
	BT_EXPORT void setObjectTransform(const float* position, const float* orientation, int bodyIndex);

	BT_EXPORT void writeAllBodiesToGpu();
	BT_EXPORT void reset();
	BT_EXPORT void readbackAllBodiesToCpu();
	BT_EXPORT bool getObjectTransformFromCpu(float* position, float* orientation, int bodyIndex) const;

	BT_EXPORT void setObjectTransformCpu(float* position, float* orientation, int bodyIndex);
	BT_EXPORT void setObjectVelocityCpu(float* linVel, float* angVel, int bodyIndex);

	//virtual void computeContacts(cl_mem broadphasePairs, int numBroadphasePairs, cl_mem aabbsWorldSpace, int numObjects);
	BT_EXPORT virtual void computeContacts(b3AlignedObjectArray<b3Int4>& pairs, b3AlignedObjectArray<b3Aabb>& aabbsWorldSpace, b3AlignedObjectArray<b3RigidBodyData>& bodies);

	BT_EXPORT const struct b3RigidBodyData* getBodiesCpu() const;
	//struct b3RigidBodyData* getBodiesCpu();

	BT_EXPORT int getNumBodiesGpu() const;

	BT_EXPORT int getNumBodyInertiasGpu() const;

	BT_EXPORT const struct b3Collidable* getCollidablesCpu() const;
	BT_EXPORT int getNumCollidablesGpu() const;

	/*const struct b3Contact4* getContactsCPU() const;

	
	int	getNumContactsGpu() const;
	*/

	BT_EXPORT const b3AlignedObjectArray<b3Contact4Data>& getContacts() const;

	BT_EXPORT int getNumRigidBodies() const;

	BT_EXPORT int allocateCollidable();

	int getStatic0Index() const
	{
		return m_static0Index;
	}
	BT_EXPORT b3Collidable& getCollidableCpu(int collidableIndex);
	BT_EXPORT const b3Collidable& getCollidableCpu(int collidableIndex) const;

	const b3CpuNarrowPhaseInternalData* getInternalData() const
	{
		return m_data;
	}

	BT_EXPORT const struct b3Aabb& getLocalSpaceAabb(int collidableIndex) const;
};

#endif  //B3_CPU_NARROWPHASE_H
