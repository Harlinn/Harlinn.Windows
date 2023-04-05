/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  https://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BT_SIMPLE_DYNAMICS_WORLD_H
#define BT_SIMPLE_DYNAMICS_WORLD_H

#include "btDynamicsWorld.h"

class btDispatcher;
class btOverlappingPairCache;
class btConstraintSolver;

///The btSimpleDynamicsWorld serves as unit-test and to verify more complicated and optimized dynamics worlds.
///Please use btDiscreteDynamicsWorld instead
class btSimpleDynamicsWorld : public btDynamicsWorld
{
protected:
	btConstraintSolver* m_constraintSolver;

	bool m_ownsConstraintSolver;

	void predictUnconstraintMotion(btScalar timeStep);

	void integrateTransforms(btScalar timeStep);

	btVector3 m_gravity;

public:
	///this btSimpleDynamicsWorld constructor creates dispatcher, broadphase pairCache and constraintSolver
	BT_EXPORT btSimpleDynamicsWorld(btDispatcher* dispatcher, btBroadphaseInterface* pairCache, btConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration);

	BT_EXPORT virtual ~btSimpleDynamicsWorld();

	///maxSubSteps/fixedTimeStep for interpolation is currently ignored for btSimpleDynamicsWorld, use btDiscreteDynamicsWorld instead
	BT_EXPORT virtual int stepSimulation(btScalar timeStep, int maxSubSteps = 1, btScalar fixedTimeStep = btScalar(1.) / btScalar(60.));

	BT_EXPORT virtual void setGravity(const btVector3& gravity);

	BT_EXPORT virtual btVector3 getGravity() const;

	BT_EXPORT virtual void addRigidBody(btRigidBody* body);

	BT_EXPORT virtual void addRigidBody(btRigidBody* body, int group, int mask);

	BT_EXPORT virtual void removeRigidBody(btRigidBody* body);

	BT_EXPORT virtual void debugDrawWorld();

	BT_EXPORT virtual void addAction(btActionInterface* action);

	BT_EXPORT virtual void removeAction(btActionInterface* action);

	///removeCollisionObject will first check if it is a rigid body, if so call removeRigidBody otherwise call btCollisionWorld::removeCollisionObject
	BT_EXPORT virtual void removeCollisionObject(btCollisionObject* collisionObject);

	BT_EXPORT virtual void updateAabbs();

	BT_EXPORT virtual void synchronizeMotionStates();

	BT_EXPORT virtual void setConstraintSolver(btConstraintSolver* solver);

	BT_EXPORT virtual btConstraintSolver* getConstraintSolver();

	virtual btDynamicsWorldType getWorldType() const
	{
		return BT_SIMPLE_DYNAMICS_WORLD;
	}

	BT_EXPORT virtual void clearForces();
};

#endif  //BT_SIMPLE_DYNAMICS_WORLD_H
