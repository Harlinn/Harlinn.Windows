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

#ifndef BT_SEQUENTIAL_IMPULSE_CONSTRAINT_SOLVER_MT_H
#define BT_SEQUENTIAL_IMPULSE_CONSTRAINT_SOLVER_MT_H

#include "btSequentialImpulseConstraintSolver.h"
#include "btBatchedConstraints.h"
#include "bullet/LinearMath/btThreads.h"

///
/// btSequentialImpulseConstraintSolverMt
///
///  A multithreaded variant of the sequential impulse constraint solver. The constraints to be solved are grouped into
///  batches and phases where each batch of constraints within a given phase can be solved in parallel with the rest.
///  Ideally we want as few phases as possible, and each phase should have many batches, and all of the batches should
///  have about the same number of constraints.
///  This method works best on a large island of many constraints.
///
///  Supports all of the features of the normal sequential impulse solver such as:
///    - split penetration impulse
///    - rolling friction
///    - interleaving constraints
///    - warmstarting
///    - 2 friction directions
///    - randomized constraint ordering
///    - early termination when leastSquaresResidualThreshold is satisfied
///
///  When the SOLVER_INTERLEAVE_CONTACT_AND_FRICTION_CONSTRAINTS flag is enabled, unlike the normal SequentialImpulse solver,
///  the rolling friction is interleaved as well.
///  Interleaving the contact penetration constraints with friction reduces the number of parallel loops that need to be done,
///  which reduces threading overhead so it can be a performance win, however, it does seem to produce a less stable simulation,
///  at least on stacks of blocks.
///
///  When the SOLVER_RANDMIZE_ORDER flag is enabled, the ordering of phases, and the ordering of constraints within each batch
///  is randomized, however it does not swap constraints between batches.
///  This is to avoid regenerating the batches for each solver iteration which would be quite costly in performance.
///
///  Note that a non-zero leastSquaresResidualThreshold could possibly affect the determinism of the simulation
///  if the task scheduler's parallelSum operation is non-deterministic. The parallelSum operation can be non-deterministic
///  because floating point addition is not associative due to rounding errors.
///  The task scheduler can and should ensure that the result of any parallelSum operation is deterministic.
///
ATTRIBUTE_ALIGNED16(class)
btSequentialImpulseConstraintSolverMt : public btSequentialImpulseConstraintSolver
{
public:
	BT_EXPORT virtual void solveGroupCacheFriendlySplitImpulseIterations(btCollisionObject * *bodies, int numBodies, btPersistentManifold** manifoldPtr, int numManifolds, btTypedConstraint** constraints, int numConstraints, const btContactSolverInfo& infoGlobal, btIDebugDraw* debugDrawer) BT_OVERRIDE;
	BT_EXPORT virtual btScalar solveSingleIteration(int iteration, btCollisionObject** bodies, int numBodies, btPersistentManifold** manifoldPtr, int numManifolds, btTypedConstraint** constraints, int numConstraints, const btContactSolverInfo& infoGlobal, btIDebugDraw* debugDrawer) BT_OVERRIDE;
	BT_EXPORT virtual btScalar solveGroupCacheFriendlySetup(btCollisionObject * *bodies, int numBodies, btPersistentManifold** manifoldPtr, int numManifolds, btTypedConstraint** constraints, int numConstraints, const btContactSolverInfo& infoGlobal, btIDebugDraw* debugDrawer) BT_OVERRIDE;
	BT_EXPORT virtual btScalar solveGroupCacheFriendlyFinish(btCollisionObject * *bodies, int numBodies, const btContactSolverInfo& infoGlobal) BT_OVERRIDE;

	// temp struct used to collect info from persistent manifolds into a cache-friendly struct using multiple threads
	struct btContactManifoldCachedInfo
	{
		static const int MAX_NUM_CONTACT_POINTS = 4;

		int numTouchingContacts;
		int solverBodyIds[2];
		int contactIndex;
		int rollingFrictionIndex;
		bool contactHasRollingFriction[MAX_NUM_CONTACT_POINTS];
		btManifoldPoint* contactPoints[MAX_NUM_CONTACT_POINTS];
	};
	// temp struct used for setting up joint constraints in parallel
	struct JointParams
	{
		int m_solverConstraint;
		int m_solverBodyA;
		int m_solverBodyB;
	};
	BT_EXPORT void internalInitMultipleJoints(btTypedConstraint * *constraints, int iBegin, int iEnd);
	BT_EXPORT void internalConvertMultipleJoints(const btAlignedObjectArray<JointParams>& jointParamsArray, btTypedConstraint** constraints, int iBegin, int iEnd, const btContactSolverInfo& infoGlobal);

	// parameters to control batching
	BT_EXPORT static bool s_allowNestedParallelForLoops;        // whether to allow nested parallel operations
	BT_EXPORT static int s_minimumContactManifoldsForBatching;  // don't even try to batch if fewer manifolds than this
	BT_EXPORT static btBatchedConstraints::BatchingMethod s_contactBatchingMethod;
	BT_EXPORT static btBatchedConstraints::BatchingMethod s_jointBatchingMethod;
	BT_EXPORT static int s_minBatchSize;  // desired number of constraints per batch
	BT_EXPORT static int s_maxBatchSize;

protected:
	static const int CACHE_LINE_SIZE = 64;

	btBatchedConstraints m_batchedContactConstraints;
	btBatchedConstraints m_batchedJointConstraints;
	int m_numFrictionDirections;
	bool m_useBatching;
	bool m_useObsoleteJointConstraints;
	btAlignedObjectArray<btContactManifoldCachedInfo> m_manifoldCachedInfoArray;
	btAlignedObjectArray<int> m_rollingFrictionIndexTable;  // lookup table mapping contact index to rolling friction index
	btSpinMutex m_bodySolverArrayMutex;
	char m_antiFalseSharingPadding[CACHE_LINE_SIZE];  // padding to keep mutexes in separate cachelines
	btSpinMutex m_kinematicBodyUniqueIdToSolverBodyTableMutex;
	btAlignedObjectArray<char> m_scratchMemory;

	BT_EXPORT virtual void randomizeConstraintOrdering(int iteration, int numIterations);
	BT_EXPORT virtual btScalar resolveAllJointConstraints(int iteration);
	BT_EXPORT virtual btScalar resolveAllContactConstraints();
	BT_EXPORT virtual btScalar resolveAllContactFrictionConstraints();
	BT_EXPORT virtual btScalar resolveAllContactConstraintsInterleaved();
	BT_EXPORT virtual btScalar resolveAllRollingFrictionConstraints();

	BT_EXPORT virtual void setupBatchedContactConstraints();
	BT_EXPORT virtual void setupBatchedJointConstraints();
	BT_EXPORT virtual void convertJoints(btTypedConstraint * *constraints, int numConstraints, const btContactSolverInfo& infoGlobal) BT_OVERRIDE;
	BT_EXPORT virtual void convertContacts(btPersistentManifold * *manifoldPtr, int numManifolds, const btContactSolverInfo& infoGlobal) BT_OVERRIDE;
	BT_EXPORT virtual void convertBodies(btCollisionObject * *bodies, int numBodies, const btContactSolverInfo& infoGlobal) BT_OVERRIDE;

	BT_EXPORT int getOrInitSolverBodyThreadsafe(btCollisionObject & body, btScalar timeStep);
	BT_EXPORT void allocAllContactConstraints(btPersistentManifold * *manifoldPtr, int numManifolds, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void setupAllContactConstraints(const btContactSolverInfo& infoGlobal);
	BT_EXPORT void randomizeBatchedConstraintOrdering(btBatchedConstraints * batchedConstraints);

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	BT_EXPORT btSequentialImpulseConstraintSolverMt();
	BT_EXPORT virtual ~btSequentialImpulseConstraintSolverMt();

	BT_EXPORT btScalar resolveMultipleJointConstraints(const btAlignedObjectArray<int>& consIndices, int batchBegin, int batchEnd, int iteration);
	BT_EXPORT btScalar resolveMultipleContactConstraints(const btAlignedObjectArray<int>& consIndices, int batchBegin, int batchEnd);
	BT_EXPORT btScalar resolveMultipleContactSplitPenetrationImpulseConstraints(const btAlignedObjectArray<int>& consIndices, int batchBegin, int batchEnd);
	BT_EXPORT btScalar resolveMultipleContactFrictionConstraints(const btAlignedObjectArray<int>& consIndices, int batchBegin, int batchEnd);
	BT_EXPORT btScalar resolveMultipleContactRollingFrictionConstraints(const btAlignedObjectArray<int>& consIndices, int batchBegin, int batchEnd);
	BT_EXPORT btScalar resolveMultipleContactConstraintsInterleaved(const btAlignedObjectArray<int>& contactIndices, int batchBegin, int batchEnd);

	BT_EXPORT void internalCollectContactManifoldCachedInfo(btContactManifoldCachedInfo * cachedInfoArray, btPersistentManifold * *manifoldPtr, int numManifolds, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void internalAllocContactConstraints(const btContactManifoldCachedInfo* cachedInfoArray, int numManifolds);
	BT_EXPORT void internalSetupContactConstraints(int iContactConstraint, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void internalConvertBodies(btCollisionObject * *bodies, int iBegin, int iEnd, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void internalWriteBackContacts(int iBegin, int iEnd, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void internalWriteBackJoints(int iBegin, int iEnd, const btContactSolverInfo& infoGlobal);
	BT_EXPORT void internalWriteBackBodies(int iBegin, int iEnd, const btContactSolverInfo& infoGlobal);
};

#endif  //BT_SEQUENTIAL_IMPULSE_CONSTRAINT_SOLVER_MT_H
