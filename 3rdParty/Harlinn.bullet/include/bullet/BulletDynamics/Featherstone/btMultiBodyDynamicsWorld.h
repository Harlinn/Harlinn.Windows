/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2013 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BT_MULTIBODY_DYNAMICS_WORLD_H
#define BT_MULTIBODY_DYNAMICS_WORLD_H

#include "bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "bullet/BulletDynamics/Featherstone/btMultiBodyInplaceSolverIslandCallback.h"

#define BT_USE_VIRTUAL_CLEARFORCES_AND_GRAVITY

class btMultiBody;
class btMultiBodyConstraint;
class btMultiBodyConstraintSolver;
struct MultiBodyInplaceSolverIslandCallback;

///The btMultiBodyDynamicsWorld adds Featherstone multi body dynamics to Bullet
///This implementation is still preliminary/experimental.
class btMultiBodyDynamicsWorld : public btDiscreteDynamicsWorld
{
protected:
	btAlignedObjectArray<btMultiBody*> m_multiBodies;
	btAlignedObjectArray<btMultiBodyConstraint*> m_multiBodyConstraints;
	btAlignedObjectArray<btMultiBodyConstraint*> m_sortedMultiBodyConstraints;
	btMultiBodyConstraintSolver* m_multiBodyConstraintSolver;
	MultiBodyInplaceSolverIslandCallback* m_solverMultiBodyIslandCallback;

	//cached data to avoid memory allocations
	btAlignedObjectArray<btQuaternion> m_scratch_world_to_local;
	btAlignedObjectArray<btVector3> m_scratch_local_origin;
	btAlignedObjectArray<btQuaternion> m_scratch_world_to_local1;
	btAlignedObjectArray<btVector3> m_scratch_local_origin1;
	btAlignedObjectArray<btScalar> m_scratch_r;
	btAlignedObjectArray<btVector3> m_scratch_v;
	btAlignedObjectArray<btMatrix3x3> m_scratch_m;

	BT_EXPORT virtual void calculateSimulationIslands();
	BT_EXPORT virtual void updateActivationState(btScalar timeStep);
	

	BT_EXPORT virtual void serializeMultiBodies(btSerializer* serializer);

public:
	BT_EXPORT btMultiBodyDynamicsWorld(btDispatcher* dispatcher, btBroadphaseInterface* pairCache, btMultiBodyConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration);

	BT_EXPORT virtual ~btMultiBodyDynamicsWorld();
    
	BT_EXPORT virtual void solveConstraints(btContactSolverInfo& solverInfo);
    
	BT_EXPORT virtual void addMultiBody(btMultiBody* body, int group = btBroadphaseProxy::DefaultFilter, int mask = btBroadphaseProxy::AllFilter);

	BT_EXPORT virtual void removeMultiBody(btMultiBody* body);

	virtual int getNumMultibodies() const
	{
		return m_multiBodies.size();
	}

	btMultiBody* getMultiBody(int mbIndex)
	{
		return m_multiBodies[mbIndex];
	}

	const btMultiBody* getMultiBody(int mbIndex) const
	{
		return m_multiBodies[mbIndex];
	}

	BT_EXPORT virtual void addMultiBodyConstraint(btMultiBodyConstraint* constraint);

	virtual int getNumMultiBodyConstraints() const
	{
		return m_multiBodyConstraints.size();
	}

	virtual btMultiBodyConstraint* getMultiBodyConstraint(int constraintIndex)
	{
		return m_multiBodyConstraints[constraintIndex];
	}

	virtual const btMultiBodyConstraint* getMultiBodyConstraint(int constraintIndex) const
	{
		return m_multiBodyConstraints[constraintIndex];
	}

	BT_EXPORT virtual void removeMultiBodyConstraint(btMultiBodyConstraint* constraint);

	BT_EXPORT virtual void integrateTransforms(btScalar timeStep);
    BT_EXPORT void integrateMultiBodyTransforms(btScalar timeStep);
    BT_EXPORT void predictMultiBodyTransforms(btScalar timeStep);
    
	BT_EXPORT virtual void predictUnconstraintMotion(btScalar timeStep);
	BT_EXPORT virtual void debugDrawWorld();

	BT_EXPORT virtual void debugDrawMultiBodyConstraint(btMultiBodyConstraint* constraint);

	BT_EXPORT void forwardKinematics();
	BT_EXPORT virtual void clearForces();
	BT_EXPORT virtual void clearMultiBodyConstraintForces();
	BT_EXPORT virtual void clearMultiBodyForces();
	BT_EXPORT virtual void applyGravity();

	BT_EXPORT virtual void serialize(btSerializer* serializer);
	BT_EXPORT virtual void setMultiBodyConstraintSolver(btMultiBodyConstraintSolver* solver);
	BT_EXPORT virtual void setConstraintSolver(btConstraintSolver* solver);
	BT_EXPORT virtual void getAnalyticsData(btAlignedObjectArray<struct btSolverAnalyticsData>& m_islandAnalyticsData) const;
    
    BT_EXPORT virtual void solveExternalForces(btContactSolverInfo& solverInfo);
    BT_EXPORT virtual void solveInternalConstraints(btContactSolverInfo& solverInfo);
    BT_EXPORT void buildIslands();

	BT_EXPORT virtual void saveKinematicState(btScalar timeStep);
};
#endif  //BT_MULTIBODY_DYNAMICS_WORLD_H
