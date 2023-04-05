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

#ifndef BT_SEQUENTIAL_IMPULSE_CONSTRAINT_SOLVER_H
#define BT_SEQUENTIAL_IMPULSE_CONSTRAINT_SOLVER_H

class btIDebugDraw;
class btPersistentManifold;
class btDispatcher;
class btCollisionObject;
#include "bullet/BulletDynamics/ConstraintSolver/btTypedConstraint.h"
#include "bullet/BulletDynamics/ConstraintSolver/btContactSolverInfo.h"
#include "bullet/BulletDynamics/ConstraintSolver/btSolverBody.h"
#include "bullet/BulletDynamics/ConstraintSolver/btSolverConstraint.h"
#include "bullet/BulletCollision/NarrowPhaseCollision/btManifoldPoint.h"
#include "bullet/BulletDynamics/ConstraintSolver/btConstraintSolver.h"

typedef btScalar (*btSingleConstraintRowSolver)(btSolverBody&, btSolverBody&, const btSolverConstraint&);

struct btSolverAnalyticsData
{
	btSolverAnalyticsData()
	{
		m_numSolverCalls = 0;
		m_numIterationsUsed = -1;
		m_remainingLeastSquaresResidual = -1;
		m_islandId = -2;
	}
	int m_islandId;
	int m_numBodies;
	int m_numContactManifolds;
	int m_numSolverCalls;
	int m_numIterationsUsed;
	double m_remainingLeastSquaresResidual;
};

///The btSequentialImpulseConstraintSolver is a fast SIMD implementation of the Projected Gauss Seidel (iterative LCP) method.
ATTRIBUTE_ALIGNED16(class)
btSequentialImpulseConstraintSolver : public btConstraintSolver
{
	

protected:
	btAlignedObjectArray<btSolverBody> m_tmpSolverBodyPool;
	btConstraintArray m_tmpSolverContactConstraintPool;
	btConstraintArray m_tmpSolverNonContactConstraintPool;
	btConstraintArray m_tmpSolverContactFrictionConstraintPool;
	btConstraintArray m_tmpSolverContactRollingFrictionConstraintPool;

	btAlignedObjectArray<int> m_orderTmpConstraintPool;
	btAlignedObjectArray<int> m_orderNonContactConstraintPool;
	btAlignedObjectArray<int> m_orderFrictionConstraintPool;
	btAlignedObjectArray<btTypedConstraint::btConstraintInfo1> m_tmpConstraintSizesPool;
	int m_maxOverrideNumSolverIterations;
	int m_fixedBodyId;
	// When running solvers on multiple threads, a race condition exists for Kinematic objects that
	// participate in more than one solver.
	// The getOrInitSolverBody() function writes the companionId of each body (storing the index of the solver body
	// for the current solver). For normal dynamic bodies it isn't an issue because they can only be in one island
	// (and therefore one thread) at a time. But kinematic bodies can be in multiple islands at once.
	// To avoid this race condition, this solver does not write the companionId, instead it stores the solver body
	// index in this solver-local table, indexed by the uniqueId of the body.
	btAlignedObjectArray<int> m_kinematicBodyUniqueIdToSolverBodyTable;  // only used for multithreading

	btSingleConstraintRowSolver m_resolveSingleConstraintRowGeneric;
	btSingleConstraintRowSolver m_resolveSingleConstraintRowLowerLimit;
	btSingleConstraintRowSolver m_resolveSplitPenetrationImpulse;
	int m_cachedSolverMode;  // used to check if SOLVER_SIMD flag has been changed
	void setupSolverFunctions(bool useSimd);

	btScalar m_leastSquaresResidual;

	BT_EXPORT void setupFrictionConstraint(btSolverConstraint & solverConstraint, const btVector3& normalAxis, int solverBodyIdA, int solverBodyIdB,
		btManifoldPoint& cp, const btVector3& rel_pos1, const btVector3& rel_pos2,
		btCollisionObject* colObj0, btCollisionObject* colObj1, btScalar relaxation,
		const btContactSolverInfo& infoGlobal,
		btScalar desiredVelocity = 0., btScalar cfmSlip = 0.);

	BT_EXPORT void setupTorsionalFrictionConstraint(btSolverConstraint & solverConstraint, const btVector3& normalAxis, int solverBodyIdA, int solverBodyIdB,
		btManifoldPoint& cp, btScalar combinedTorsionalFriction, const btVector3& rel_pos1, const btVector3& rel_pos2,
		btCollisionObject* colObj0, btCollisionObject* colObj1, btScalar relaxation,
		btScalar desiredVelocity = 0., btScalar cfmSlip = 0.);

	BT_EXPORT btSolverConstraint& addFrictionConstraint(const btVector3& normalAxis, int solverBodyIdA, int solverBodyIdB, int frictionIndex, btManifoldPoint& cp, const btVector3& rel_pos1, const btVector3& rel_pos2, btCollisionObject* colObj0, btCollisionObject* colObj1, btScalar relaxation, const btContactSolverInfo& infoGlobal, btScalar desiredVelocity = 0., btScalar cfmSlip = 0.);
	BT_EXPORT btSolverConstraint& addTorsionalFrictionConstraint(const btVector3& normalAxis, int solverBodyIdA, int solverBodyIdB, int frictionIndex, btManifoldPoint& cp, btScalar torsionalFriction, const btVector3& rel_pos1, const btVector3& rel_pos2, btCollisionObject* colObj0, btCollisionObject* colObj1, btScalar relaxation, btScalar desiredVelocity = 0, btScalar cfmSlip = 0.f);

	BT_EXPORT void setupContactConstraint(btSolverConstraint & solverConstraint, int solverBodyIdA, int solverBodyIdB, btManifoldPoint& cp,
		const btContactSolverInfo& infoGlobal, btScalar& relaxation, const btVector3& rel_pos1, const btVector3& rel_pos2);

	BT_EXPORT static void applyAnisotropicFriction(btCollisionObject * colObj, btVector3 & frictionDirection, int frictionMode);

	BT_EXPORT void setFrictionConstraintImpulse(btSolverConstraint & solverConstraint, int solverBodyIdA, int solverBodyIdB,
		btManifoldPoint& cp, const btContactSolverInfo& infoGlobal);

	///m_btSeed2 is used for re-arranging the constraint rows. improves convergence/quality of friction
	unsigned long m_btSeed2;

	BT_EXPORT btScalar restitutionCurve(btScalar rel_vel, btScalar restitution, btScalar velocityThreshold);

	BT_EXPORT virtual void convertContacts(btPersistentManifold * *manifoldPtr, int numManifolds, const btContactSolverInfo& infoGlobal);

	BT_EXPORT void convertContact(btPersistentManifold * manifold, const btContactSolverInfo& infoGlobal);

	BT_EXPORT virtual void convertJoints(btTypedConstraint * *constraints, int numConstraints, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void convertJoint(btSolverConstraint * currentConstraintRow, btTypedConstraint * constraint, const btTypedConstraint::btConstraintInfo1& info1, int solverBodyIdA, int solverBodyIdB, const btContactSolverInfo& infoGlobal);

	BT_EXPORT virtual void convertBodies(btCollisionObject * *bodies, int numBodies, const btContactSolverInfo& infoGlobal);

	btScalar resolveSplitPenetrationSIMD(btSolverBody & bodyA, btSolverBody & bodyB, const btSolverConstraint& contactConstraint)
	{
		return m_resolveSplitPenetrationImpulse(bodyA, bodyB, contactConstraint);
	}

	btScalar resolveSplitPenetrationImpulseCacheFriendly(btSolverBody & bodyA, btSolverBody & bodyB, const btSolverConstraint& contactConstraint)
	{
		return m_resolveSplitPenetrationImpulse(bodyA, bodyB, contactConstraint);
	}

	//internal method
	BT_EXPORT int getOrInitSolverBody(btCollisionObject & body, btScalar timeStep);
	BT_EXPORT void initSolverBody(btSolverBody * solverBody, btCollisionObject * collisionObject, btScalar timeStep);

	BT_EXPORT btScalar resolveSingleConstraintRowGeneric(btSolverBody & bodyA, btSolverBody & bodyB, const btSolverConstraint& contactConstraint);
	BT_EXPORT btScalar resolveSingleConstraintRowGenericSIMD(btSolverBody & bodyA, btSolverBody & bodyB, const btSolverConstraint& contactConstraint);
	BT_EXPORT btScalar resolveSingleConstraintRowLowerLimit(btSolverBody & bodyA, btSolverBody & bodyB, const btSolverConstraint& contactConstraint);
	BT_EXPORT btScalar resolveSingleConstraintRowLowerLimitSIMD(btSolverBody & bodyA, btSolverBody & bodyB, const btSolverConstraint& contactConstraint);
	btScalar resolveSplitPenetrationImpulse(btSolverBody & bodyA, btSolverBody & bodyB, const btSolverConstraint& contactConstraint)
	{
		return m_resolveSplitPenetrationImpulse(bodyA, bodyB, contactConstraint);
	}

protected:
	BT_EXPORT void writeBackContacts(int iBegin, int iEnd, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void writeBackJoints(int iBegin, int iEnd, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void writeBackBodies(int iBegin, int iEnd, const btContactSolverInfo& infoGlobal);
	BT_EXPORT virtual void solveGroupCacheFriendlySplitImpulseIterations(btCollisionObject * *bodies, int numBodies, btPersistentManifold** manifoldPtr, int numManifolds, btTypedConstraint** constraints, int numConstraints, const btContactSolverInfo& infoGlobal, btIDebugDraw* debugDrawer);
	BT_EXPORT virtual btScalar solveGroupCacheFriendlyFinish(btCollisionObject * *bodies, int numBodies, const btContactSolverInfo& infoGlobal);
	BT_EXPORT virtual btScalar solveSingleIteration(int iteration, btCollisionObject** bodies, int numBodies, btPersistentManifold** manifoldPtr, int numManifolds, btTypedConstraint** constraints, int numConstraints, const btContactSolverInfo& infoGlobal, btIDebugDraw* debugDrawer);

	BT_EXPORT virtual btScalar solveGroupCacheFriendlySetup(btCollisionObject * *bodies, int numBodies, btPersistentManifold** manifoldPtr, int numManifolds, btTypedConstraint** constraints, int numConstraints, const btContactSolverInfo& infoGlobal, btIDebugDraw* debugDrawer);
	BT_EXPORT virtual btScalar solveGroupCacheFriendlyIterations(btCollisionObject * *bodies, int numBodies, btPersistentManifold** manifoldPtr, int numManifolds, btTypedConstraint** constraints, int numConstraints, const btContactSolverInfo& infoGlobal, btIDebugDraw* debugDrawer);

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	BT_EXPORT btSequentialImpulseConstraintSolver();
	BT_EXPORT virtual ~btSequentialImpulseConstraintSolver();

	BT_EXPORT virtual btScalar solveGroup(btCollisionObject * *bodies, int numBodies, btPersistentManifold** manifold, int numManifolds, btTypedConstraint** constraints, int numConstraints, const btContactSolverInfo& info, btIDebugDraw* debugDrawer, btDispatcher* dispatcher);

	///clear internal cached data and reset random seed
	BT_EXPORT virtual void reset();

	BT_EXPORT unsigned long btRand2();

	BT_EXPORT int btRandInt2(int n);

	void setRandSeed(unsigned long seed)
	{
		m_btSeed2 = seed;
	}
	unsigned long getRandSeed() const
	{
		return m_btSeed2;
	}

	virtual btConstraintSolverType getSolverType() const
	{
		return BT_SEQUENTIAL_IMPULSE_SOLVER;
	}

	btSingleConstraintRowSolver getActiveConstraintRowSolverGeneric()
	{
		return m_resolveSingleConstraintRowGeneric;
	}
	void setConstraintRowSolverGeneric(btSingleConstraintRowSolver rowSolver)
	{
		m_resolveSingleConstraintRowGeneric = rowSolver;
	}
	btSingleConstraintRowSolver getActiveConstraintRowSolverLowerLimit()
	{
		return m_resolveSingleConstraintRowLowerLimit;
	}
	void setConstraintRowSolverLowerLimit(btSingleConstraintRowSolver rowSolver)
	{
		m_resolveSingleConstraintRowLowerLimit = rowSolver;
	}



	///Various implementations of solving a single constraint row using a generic equality constraint, using scalar reference, SSE2 or SSE4
	BT_EXPORT btSingleConstraintRowSolver getScalarConstraintRowSolverGeneric();
	BT_EXPORT btSingleConstraintRowSolver getSSE2ConstraintRowSolverGeneric();
	BT_EXPORT btSingleConstraintRowSolver getSSE4_1ConstraintRowSolverGeneric();

	///Various implementations of solving a single constraint row using an inequality (lower limit) constraint, using scalar reference, SSE2 or SSE4
	BT_EXPORT btSingleConstraintRowSolver getScalarConstraintRowSolverLowerLimit();
	BT_EXPORT btSingleConstraintRowSolver getSSE2ConstraintRowSolverLowerLimit();
	BT_EXPORT btSingleConstraintRowSolver getSSE4_1ConstraintRowSolverLowerLimit();
	btSolverAnalyticsData m_analyticsData;
};

#endif  //BT_SEQUENTIAL_IMPULSE_CONSTRAINT_SOLVER_H
