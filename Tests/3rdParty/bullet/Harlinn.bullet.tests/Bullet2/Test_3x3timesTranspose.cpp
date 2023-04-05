#include <bullet/LinearMath/btScalar.h>

#if defined(BT_USE_SSE_IN_API) || defined(BT_USE_NEON)

#include "vector.h"
#include "Utils.h"
#include <math.h>
#include <string.h>

#include <bullet/LinearMath/btMatrix3x3.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

namespace
{
	class LocalFixture
	{
	public:
		LocalFixture( ) = default;
	};

#define LOOPCOUNT 1000
#define ARRAY_SIZE 128

static inline btSimdFloat4 rand_f4(void)
{
	return btAssign128(RANDF, RANDF, RANDF, BT_NAN);  // w channel NaN
}

static btMatrix3x3 timesTranspose(const btMatrix3x3 &in, const btMatrix3x3 &m)
{
	btVector3 m_el[3] = {in[0], in[1], in[2]};
	return btMatrix3x3(
		m_el[0].dot(m[0]), m_el[0].dot(m[1]), m_el[0].dot(m[2]),
		m_el[1].dot(m[0]), m_el[1].dot(m[1]), m_el[1].dot(m[2]),
		m_el[2].dot(m[0]), m_el[2].dot(m[1]), m_el[2].dot(m[2]));
}

static int operator!=(const btMatrix3x3 &a, const btMatrix3x3 &b)
{
	if (a.getRow(0) != b.getRow(0))
		return 1;
	if (a.getRow(1) != b.getRow(1))
		return 1;
	if (a.getRow(2) != b.getRow(2))
		return 1;
	return 0;
}

int Test_3x3timesTranspose(void)
{
	// Init an array flanked by guard pages
	btMatrix3x3 in1[ARRAY_SIZE];
	btMatrix3x3 in2[ARRAY_SIZE];
	btMatrix3x3 out[ARRAY_SIZE];
	btMatrix3x3 out2[ARRAY_SIZE];

	// Init the data
	size_t i, j;
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		in1[i] = btMatrix3x3(rand_f4(), rand_f4(), rand_f4());
		in2[i] = btMatrix3x3(rand_f4(), rand_f4(), rand_f4());

		out[i] = timesTranspose(in1[i], in2[i]);
		out2[i] = in1[i].timesTranspose(in2[i]);

		if (out[i] != out2[i])
		{
			printf("failure @ %zu\n", i);
			return -1;
		}
	}

	uint64_t scalarTime, vectorTime;
	uint64_t startTime, bestTime, currentTime;
	bestTime = -1LL;
	scalarTime = 0;
	for (j = 0; j < LOOPCOUNT; j++)
	{
		startTime = ReadTicks();
		for (i = 0; i < ARRAY_SIZE; i++)
			out[i] = timesTranspose(in1[i], in2[i]);
		currentTime = ReadTicks() - startTime;
		scalarTime += currentTime;
		if (currentTime < bestTime)
			bestTime = currentTime;
	}
	if (0 == gReportAverageTimes)
		scalarTime = bestTime;
	else
		scalarTime /= LOOPCOUNT;

	bestTime = -1LL;
	vectorTime = 0;
	for (j = 0; j < LOOPCOUNT; j++)
	{
		startTime = ReadTicks();
		for (i = 0; i < ARRAY_SIZE; i++)
			out[i] = in1[i].timesTranspose(in2[i]);
		currentTime = ReadTicks() - startTime;
		vectorTime += currentTime;
		if (currentTime < bestTime)
			bestTime = currentTime;
	}
	if (0 == gReportAverageTimes)
		vectorTime = bestTime;
	else
		vectorTime /= LOOPCOUNT;

	vlog("Timing:\n");
	vlog("\t    scalar\t    vector\n");
	vlog("\t%10.2f\t%10.2f\n", TicksToCycles(scalarTime) / ARRAY_SIZE, TicksToCycles(vectorTime) / ARRAY_SIZE);

	return 0;
}

}

BOOST_FIXTURE_TEST_SUITE( TestSuite_3x3timesTranspose, LocalFixture )

// --run_test=TestSuite_3x3timesTranspose/RunTest
BOOST_AUTO_TEST_CASE( RunTest )
{
	auto result = Test_3x3timesTranspose( );
	BOOST_CHECK( result == 0 );
}


BOOST_AUTO_TEST_SUITE_END( )
#endif

