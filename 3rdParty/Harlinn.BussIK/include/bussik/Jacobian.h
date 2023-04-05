
/*
*
* Inverse Kinematics software, with several solvers including
* Selectively Damped Least Squares Method
* Damped Least Squares Method
* Pure Pseudoinverse Method
* Jacobian Transpose Method
*
*
* Author: Samuel R. Buss, sbuss@ucsd.edu.
* Web page: http://www.math.ucsd.edu/~sbuss/ResearchWeb/ikmethods/index.html
*
*
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*
*
*/

#include "Node.h"
#include "Tree.h"
#include "MathMisc.h"
#include "LinearR3.h"
#include "VectorRn.h"
#include "MatrixRmn.h"

#ifndef _CLASS_JACOBIAN
#define _CLASS_JACOBIAN

#ifdef _DYNAMIC
constexpr double BASEMAXDIST = 0.02;
#else
constexpr double MAXDIST = 0.08;  // optimal value for double Y shape : 0.08
#endif
constexpr double DELTA = 0.4;
constexpr long double LAMBDA = 2.0;  // only for DLS. optimal : 0.24
constexpr double NEARZERO = 0.0000000001;

enum UpdateMode
{
	JACOB_Undefined = 0,
	JACOB_JacobianTranspose = 1,
	JACOB_PseudoInverse = 2,
	JACOB_DLS = 3,
	JACOB_SDLS = 4
};

class Jacobian
{
public:
	BUSSIK_EXPORT Jacobian(Tree*);
	BUSSIK_EXPORT Jacobian(bool useAngularJacobian, int nDof, int numEndEffectors);

	BUSSIK_EXPORT void ComputeJacobian(VectorR3* targets);
	const MatrixRmn& ActiveJacobian() const { return *Jactive; }
	void SetJendActive() { Jactive = &Jend; }  // The default setting is Jend.
	void SetJtargetActive() { Jactive = &Jtarget; }
	BUSSIK_EXPORT void SetJendTrans(MatrixRmn& J);
	BUSSIK_EXPORT void SetDeltaS(VectorRn& S);

	BUSSIK_EXPORT void CalcDeltaThetas(MatrixRmn& AugMat);  // Use this only if the Current Mode has been set.
	BUSSIK_EXPORT void ZeroDeltaThetas();
	BUSSIK_EXPORT void CalcDeltaThetasTranspose();
	BUSSIK_EXPORT void CalcDeltaThetasPseudoinverse();
	BUSSIK_EXPORT void CalcDeltaThetasDLS(MatrixRmn& AugMat);
	BUSSIK_EXPORT void CalcDeltaThetasDLS2(const VectorRn& dVec, MatrixRmn& AugMat);
	BUSSIK_EXPORT void CalcDeltaThetasDLSwithSVD();
	BUSSIK_EXPORT void CalcDeltaThetasSDLS();
	BUSSIK_EXPORT void CalcDeltaThetasDLSwithNullspace(const VectorRn& desiredV, MatrixRmn& AugMat);

	BUSSIK_EXPORT void UpdateThetas();
	BUSSIK_EXPORT void UpdateThetaDot();
	BUSSIK_EXPORT double UpdateErrorArray(VectorR3* targets);  // Returns sum of errors
	const VectorRn& GetErrorArray() const { return errorArray; }
	BUSSIK_EXPORT void UpdatedSClampValue(VectorR3* targets);

	BUSSIK_EXPORT void SetCurrentMode(UpdateMode mode) { CurrentUpdateMode = mode; }
	BUSSIK_EXPORT UpdateMode GetCurrentMode() const { return CurrentUpdateMode; }
	void SetDampingDLS(double lambda)
	{
		DampingLambda = lambda;
		DampingLambdaSq = Square(lambda);
	}

	BUSSIK_EXPORT void Reset();

	BUSSIK_EXPORT static void CompareErrors(const Jacobian& j1, const Jacobian& j2, double* weightedDist1, double* weightedDist2);
	BUSSIK_EXPORT static void CountErrors(const Jacobian& j1, const Jacobian& j2, int* numBetter1, int* numBetter2, int* numTies);

	int GetNumRows() { return nRow; }
	int GetNumCols() { return nCol; }

public:
	Tree* m_tree;     // tree associated with this Jacobian matrix
	int m_nEffector;  // Number of end effectors
	int nJoint;       // Number of joints
	int nRow;         // Total number of rows the real J (= 3*number of end effectors for now)
	int nCol;         // Total number of columns in the real J (= number of joints for now)

	MatrixRmn Jend;     // Jacobian matrix based on end effector positions
	MatrixRmn Jtarget;  // Jacobian matrix based on target positions
	MatrixRmn Jnorms;   // Norms of 3-vectors in active Jacobian (SDLS only)

	MatrixRmn U;  // J = U * Diag(w) * V^T	(Singular Value Decomposition)
	VectorRn w;
	MatrixRmn V;

	UpdateMode CurrentUpdateMode;

	VectorRn dS;         // delta s
	VectorRn dT1;        // delta t		--  these are delta S values clamped to smaller magnitude
	VectorRn dSclamp;    // Value to clamp magnitude of dT at.
	VectorRn dTheta;     // delta theta
	VectorRn dPreTheta;  // delta theta for single eigenvalue  (SDLS only)

	VectorRn errorArray;  // Distance of end effectors from target after updating

	// Parameters for pseudoinverses
	static constexpr double PseudoInverseThresholdFactor = 0.01;  // Threshold for treating eigenvalue as zero (fraction of largest eigenvalue)

	// Parameters for damped least squares
	static constexpr double DefaultDampingLambda = 0.6;  // Optimal for the "Y" shape (any lower gives jitter)
	// static constexpr DefaultDampingLambda = 1.1;			// Optimal for the DLS "double Y" shape (any lower gives jitter)
	// static constexpr DefaultDampingLambda = 0.7;			// Optimal for the DLS "double Y" shape with distance clamping (lower gives jitter)
	double DampingLambda;
	double DampingLambdaSq;
	//double DampingLambdaSDLS;

	// Cap on max. value of changes in angles in single update step
	static constexpr double MaxAngleJtranspose = 30.0 * DegreesToRadians;
	static constexpr double MaxAnglePseudoinverse = 5.0 * DegreesToRadians;
	static constexpr double MaxAngleDLS = 45.0 * DegreesToRadians;
	static constexpr double MaxAngleSDLS = 45.0 * DegreesToRadians;
	MatrixRmn* Jactive;

	void CalcdTClampedFromdS();
	static constexpr double BaseMaxTargetDist = 0.4;
};

#endif
