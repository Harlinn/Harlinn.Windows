#ifndef B3_GPU_NARROWPHASE_H
#define B3_GPU_NARROWPHASE_H

#include "bullet/Bullet3Collision/NarrowPhaseCollision/shared/b3Collidable.h"
#include "bullet/Bullet3OpenCL/Initialize/b3OpenCLInclude.h"
#include "bullet/Bullet3Common/b3AlignedObjectArray.h"
#include "bullet/Bullet3Common/b3Vector3.h"

class b3GpuNarrowPhase
{
protected:
	struct b3GpuNarrowPhaseInternalData* m_data;
	int m_acceleratedCompanionShapeIndex;
	int m_planeBodyIndex;
	int m_static0Index;

	cl_context m_context;
	cl_device_id m_device;
	cl_command_queue m_queue;

	BT_EXPORT int registerConvexHullShapeInternal(class b3ConvexUtility* convexPtr, b3Collidable& col);
	BT_EXPORT int registerConcaveMeshShape(b3AlignedObjectArray<b3Vector3>* vertices, b3AlignedObjectArray<int>* indices, b3Collidable& col, const float* scaling);

public:
	BT_EXPORT b3GpuNarrowPhase(cl_context vtx, cl_device_id dev, cl_command_queue q, const struct b3Config& config);

	BT_EXPORT virtual ~b3GpuNarrowPhase(void);

	BT_EXPORT int registerSphereShape(float radius);
	BT_EXPORT int registerPlaneShape(const b3Vector3& planeNormal, float planeConstant);

	BT_EXPORT int registerCompoundShape(b3AlignedObjectArray<b3GpuChildShape>* childShapes);
	BT_EXPORT int registerFace(const b3Vector3& faceNormal, float faceConstant);

	BT_EXPORT int registerConcaveMesh(b3AlignedObjectArray<b3Vector3>* vertices, b3AlignedObjectArray<int>* indices, const float* scaling);

	//do they need to be merged?

	BT_EXPORT int registerConvexHullShape(b3ConvexUtility* utilPtr);
	BT_EXPORT int registerConvexHullShape(const float* vertices, int strideInBytes, int numVertices, const float* scaling);

	BT_EXPORT int registerRigidBody(int collidableIndex, float mass, const float* position, const float* orientation, const float* aabbMin, const float* aabbMax, bool writeToGpu);
	BT_EXPORT void setObjectTransform(const float* position, const float* orientation, int bodyIndex);

	BT_EXPORT void writeAllBodiesToGpu();
	BT_EXPORT void reset();
	BT_EXPORT void readbackAllBodiesToCpu();
	BT_EXPORT bool getObjectTransformFromCpu(float* position, float* orientation, int bodyIndex) const;

	BT_EXPORT void setObjectTransformCpu(float* position, float* orientation, int bodyIndex);
	BT_EXPORT void setObjectVelocityCpu(float* linVel, float* angVel, int bodyIndex);

	BT_EXPORT virtual void computeContacts(cl_mem broadphasePairs, int numBroadphasePairs, cl_mem aabbsWorldSpace, int numObjects);

	BT_EXPORT cl_mem getBodiesGpu();
	BT_EXPORT const struct b3RigidBodyData* getBodiesCpu() const;
	//struct b3RigidBodyData* getBodiesCpu();

	BT_EXPORT int getNumBodiesGpu() const;

	BT_EXPORT cl_mem getBodyInertiasGpu();
	BT_EXPORT int getNumBodyInertiasGpu() const;

	BT_EXPORT cl_mem getCollidablesGpu();
	BT_EXPORT const struct b3Collidable* getCollidablesCpu() const;
	BT_EXPORT int getNumCollidablesGpu() const;

	BT_EXPORT const struct b3SapAabb* getLocalSpaceAabbsCpu() const;

	BT_EXPORT const struct b3Contact4* getContactsCPU() const;

	BT_EXPORT cl_mem getContactsGpu();
	BT_EXPORT int getNumContactsGpu() const;

	BT_EXPORT cl_mem getAabbLocalSpaceBufferGpu();

	BT_EXPORT int getNumRigidBodies() const;

	BT_EXPORT int allocateCollidable();

	int getStatic0Index() const
	{
		return m_static0Index;
	}
	BT_EXPORT b3Collidable& getCollidableCpu(int collidableIndex);
	BT_EXPORT const b3Collidable& getCollidableCpu(int collidableIndex) const;

	const b3GpuNarrowPhaseInternalData* getInternalData() const
	{
		return m_data;
	}

	b3GpuNarrowPhaseInternalData* getInternalData()
	{
		return m_data;
	}

	BT_EXPORT const struct b3SapAabb& getLocalSpaceAabb(int collidableIndex) const;
};

#endif  //B3_GPU_NARROWPHASE_H
