#include <bullet/LinearMath/btScalar.h>

#if defined(BT_USE_SSE_IN_API) || defined(BT_USE_NEON)

#include "vector.h"
#include "Utils.h"
#include <math.h>
#include <string.h>

#include <bullet/LinearMath/btQuaternion.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

namespace
{
	class LocalFixture
	{
	public:
		LocalFixture( ) = default;
	};


#define BT_OP(a, b) (a.dot(b))
// reference code for testing purposes
static inline btScalar qtdot_ref(btQuaternion& q1, btQuaternion& q2);

static inline btScalar qtdot_ref(btQuaternion& q1, btQuaternion& q2)
{
	return q1.x() * q2.x() +
		   q1.y() * q2.y() +
		   q1.z() * q2.z() +
		   q1.w() * q2.w();
}

#define LOOPCOUNT 1024
#define NUM_CYCLES 1000

int Test_qtdot(void)
{
	btQuaternion q1, q2;
	float x, y, z, w, vNaN;
	vNaN = BT_NAN;  // w channel NaN

	// Init the data
	x = RANDF_01;
	y = RANDF_01;
	z = RANDF_01;
	w = RANDF_01;
	q1.setValue(x, y, z, w);

	x = RANDF_01;
	y = RANDF_01;
	z = RANDF_01;
	w = RANDF_01;
	q2.setValue(x, y, z, w);

	btScalar correct_res, test_res;

	{
		correct_res = vNaN;
		test_res = vNaN;
		correct_res = qtdot_ref(q1, q2);
		test_res = BT_OP(q1, q2);

		if (fabsf(correct_res - test_res) > FLT_EPSILON * 4)
		{
			vlog(
				"Error - qtdot result error! "
				"\ncorrect = %10.4f "
				"\ntested  = %10.4f \n",
				correct_res, test_res);

			return 1;
		}
	}

#define DATA_SIZE LOOPCOUNT

	btQuaternion qt_arr1[DATA_SIZE];
	btQuaternion qt_arr2[DATA_SIZE];
	btScalar res_arr[DATA_SIZE];

	uint64_t scalarTime;
	uint64_t vectorTime;
	size_t j, k;

	for (k = 0; k < DATA_SIZE; k++)
	{
		x = RANDF_01;
		y = RANDF_01;
		z = RANDF_01;
		w = RANDF_01;
		qt_arr1[k].setValue(x, y, z, w);

		x = RANDF_01;
		y = RANDF_01;
		z = RANDF_01;
		w = RANDF_01;
		qt_arr2[k].setValue(x, y, z, w);
	}

	{
		uint64_t startTime, bestTime, currentTime;

		bestTime = -1LL;
		scalarTime = 0;
		for (j = 0; j < NUM_CYCLES; j++)
		{
			startTime = ReadTicks();
			for (k = 0; k + 4 <= LOOPCOUNT; k += 4)
			{
				size_t km = (k & (DATA_SIZE - 1));
				res_arr[km] = qtdot_ref(qt_arr1[km], qt_arr2[km]);
				km++;
				res_arr[km] = qtdot_ref(qt_arr1[km], qt_arr2[km]);
				km++;
				res_arr[km] = qtdot_ref(qt_arr1[km], qt_arr2[km]);
				km++;
				res_arr[km] = qtdot_ref(qt_arr1[km], qt_arr2[km]);
			}
			currentTime = ReadTicks() - startTime;
			scalarTime += currentTime;
			if (currentTime < bestTime)
				bestTime = currentTime;
		}
		if (0 == gReportAverageTimes)
			scalarTime = bestTime;
		else
			scalarTime /= NUM_CYCLES;
	}

	{
		uint64_t startTime, bestTime, currentTime;

		bestTime = -1LL;
		vectorTime = 0;
		for (j = 0; j < NUM_CYCLES; j++)
		{
			startTime = ReadTicks();
			for (k = 0; k + 4 <= LOOPCOUNT; k += 4)
			{
				size_t km = (k & (DATA_SIZE - 1));
				res_arr[km] = BT_OP(qt_arr1[km], qt_arr2[km]);
				km++;
				res_arr[km] = BT_OP(qt_arr1[km], qt_arr2[km]);
				km++;
				res_arr[km] = BT_OP(qt_arr1[km], qt_arr2[km]);
				km++;
				res_arr[km] = BT_OP(qt_arr1[km], qt_arr2[km]);
				km++;
			}
			currentTime = ReadTicks() - startTime;
			vectorTime += currentTime;
			if (currentTime < bestTime)
				bestTime = currentTime;
		}
		if (0 == gReportAverageTimes)
			vectorTime = bestTime;
		else
			vectorTime /= NUM_CYCLES;
	}

	vlog("Timing:\n");
	vlog("     \t    scalar\t    vector\n");
	vlog("    \t%10.4f\t%10.4f\n", TicksToCycles(scalarTime) / LOOPCOUNT,
		 TicksToCycles(vectorTime) / LOOPCOUNT);

	return 0;
}
}

BOOST_FIXTURE_TEST_SUITE( TestSuite_qtdot, LocalFixture )

// --run_test=TestSuite_qtdot/RunTest
BOOST_AUTO_TEST_CASE( RunTest )
{
	auto result = Test_qtdot( );
	BOOST_CHECK( result == 0 );
}


BOOST_AUTO_TEST_SUITE_END( )
#endif

