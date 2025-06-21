#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletDynamics/Character/btKinematicCharacterController.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>
#include <HCCLib.h>
#include <memory>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

namespace hc = Harlinn::Common;
namespace hcc = Harlinn::Common::Core;

namespace
{
	class LocalFixture
	{
	public:
		LocalFixture( ) = default;
	};
}

BOOST_FIXTURE_TEST_SUITE( btKinematicCharacterControllerTests, LocalFixture )

// --run_test=btKinematicCharacterControllerTests/broadphaseTest
BOOST_AUTO_TEST_CASE( broadphaseTest )
{
	std::unique_ptr<btPairCachingGhostObject> ghostObject( new btPairCachingGhostObject( ) );
	std::unique_ptr<btBoxShape> convexShape( new btBoxShape( btVector3( 1, 1, 1 ) ) );

	//For now only a simple test that it initializes correctly.
	std::unique_ptr<btKinematicCharacterController> tested( new btKinematicCharacterController( ghostObject.get( ), convexShape.get( ), 1 ) );
	BOOST_CHECK( tested != nullptr );

	

	BOOST_CHECK( hc::AreNearlyEqual( -9.8f * 3.0f, tested->getGravity( ).x( ) ) );
	BOOST_CHECK_EQUAL( 0, tested->getGravity( ).y( ) );
	BOOST_CHECK_EQUAL( 0, tested->getGravity( ).z( ) );
}


BOOST_AUTO_TEST_SUITE_END( )