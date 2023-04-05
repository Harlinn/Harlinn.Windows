#include <bullet/Bullet3Common/b3Vector3.h>
#include <bullet/Bullet3Collision/BroadPhaseCollision/b3DynamicBvhBroadphase.h>
#include <bullet/Bullet3Common/b3CommandLineArgs.h>
#include <bullet/Bullet3Common/b3MinMax.h>
#include <bullet/Bullet3Collision/BroadPhaseCollision/b3OverlappingPairCache.h>

#include <memory>


#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) = default;
    };
}

BOOST_FIXTURE_TEST_SUITE( b3DynamicBvhBroadphaseTests, LocalFixture )

// --run_test=b3DynamicBvhBroadphaseTests/broadphaseTest
BOOST_AUTO_TEST_CASE( broadphaseTest )
{
	auto bp = std::make_unique<b3DynamicBvhBroadphase>( 2 );

	int group = 1;
	int mask = 1;
	b3Vector3 aabbMin( 0, 0, 0 );
	b3Vector3 aabbMax( 1, 1, 1 );
	int userId = 0;
	bp->createProxy( aabbMin, aabbMax, userId++, 0, group, mask );

	aabbMin.setValue( 1, 1, 1 );
	aabbMax.setValue( 2, 2, 2 );

	bp->createProxy( aabbMin, aabbMax, userId++, 0, group, mask );

	bp->calculateOverlappingPairs( );

	int numOverlap = bp->getOverlappingPairCache( )->getNumOverlappingPairs( );

	BOOST_CHECK( numOverlap == 1 );
}


BOOST_AUTO_TEST_SUITE_END( )