#include "pch.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Security;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( SecurityTokenTests, LocalFixture )

// --run_test=SecurityTokenTests/CurrentProcessOpenTokenTest1
BOOST_AUTO_TEST_CASE( CurrentProcessOpenTokenTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto tokenHandle = token.Handle( );
    BOOST_CHECK( tokenHandle != 0 );

}


// --run_test=SecurityTokenTests/CurrentProcessOpenTokenTest2
BOOST_AUTO_TEST_CASE( CurrentProcessOpenTokenTest2 )
{
    TokenAccessMask desiredAccess;
    desiredAccess.SetMaximumAllowed( );
    auto token = CurrentProcess::OpenToken( desiredAccess );
    auto tokenHandle = token.Handle( );
    BOOST_CHECK( tokenHandle != 0 );
}

// --run_test=SecurityTokenTests/UserTest1
BOOST_AUTO_TEST_CASE( UserTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto securityId = token.User( );
    auto isValid = securityId.IsValid( );
    BOOST_CHECK( isValid );
}

// --run_test=SecurityTokenTests/GroupsTest1
BOOST_AUTO_TEST_CASE( GroupsTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto groups = token.Groups( );
    auto size = groups.size( );
    BOOST_CHECK( size > 0 );

    wprintf( L"Groups:\n" );
    for ( auto& group : groups )
    {
        auto securityId = group.SecurityId( );
        auto name = securityId.Name( );
        wprintf(L"\t%s\n", name.c_str( ) );
    }

}

// --run_test=SecurityTokenTests/PrivilegesTest1
BOOST_AUTO_TEST_CASE( PrivilegesTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto privileges = token.Privileges( );
    auto size = privileges.size( );
    BOOST_CHECK( size > 0 );

    wprintf( L"Privileges:\n");
    for ( auto& tokenPrivilege : privileges )
    {
        auto privilege = tokenPrivilege.Privilege;
        auto name = privilege.QueryPrivilegeName();
        wprintf( L"\t%s\n", name.c_str( ) );
    }
}

// --run_test=SecurityTokenTests/OwnerTest1
BOOST_AUTO_TEST_CASE( OwnerTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto securityId = token.Owner( );
    auto isValid = securityId.IsValid( );
    BOOST_CHECK( isValid );
}
// --run_test=SecurityTokenTests/PrimaryGroupTest1
BOOST_AUTO_TEST_CASE( PrimaryGroupTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto securityId = token.PrimaryGroup( );
    auto isValid = securityId.IsValid( );
    BOOST_CHECK( isValid );
}


// --run_test=SecurityTokenTests/DefaultAccessControlListTest1
BOOST_AUTO_TEST_CASE( DefaultAccessControlListTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto defaultAccessControlList = token.DefaultAccessControlList( );
    auto defaultAccessControlListSize = defaultAccessControlList.size();
    BOOST_CHECK( defaultAccessControlListSize );
}

// --run_test=SecurityTokenTests/SourceTest1
BOOST_AUTO_TEST_CASE( SourcetTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto tokenSource = token.Source( );
    auto& tokenSourceName = tokenSource.SourceName;
    auto tokenSourceNameLength = LengthOf( tokenSourceName.data() );

    BOOST_CHECK( tokenSourceNameLength > 0 );
}

// --run_test=SecurityTokenTests/StatisticsTest1
BOOST_AUTO_TEST_CASE( StatisticsTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto tokenStatistics = token.Statistics( );
    auto groupCount = tokenStatistics.GroupCount;

    BOOST_CHECK( groupCount > 0 );
}

// --run_test=SecurityTokenTests/GroupsAndPrivilegesTest1
BOOST_AUTO_TEST_CASE( GroupsAndPrivilegesTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto groupsAndPrivileges = token.GroupsAndPrivileges( );
    auto sidCount = groupsAndPrivileges.SidCount( );

    BOOST_CHECK( sidCount > 0 );
}


// --run_test=SecurityTokenTests/SandBoxInertTest1
BOOST_AUTO_TEST_CASE( SandBoxInertTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto sandBoxInert = token.SandBoxInert( );

    BOOST_CHECK( sandBoxInert == false );
}


// --run_test=SecurityTokenTests/OriginatingLogonSessionTest1
BOOST_AUTO_TEST_CASE( OriginatingLogonSessionTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto originatingLogonSession = token.OriginatingLogonSession( );
    bool assigned = originatingLogonSession != 0;
    BOOST_CHECK( assigned == true );
}

// --run_test=SecurityTokenTests/ElevationTypeTest1
BOOST_AUTO_TEST_CASE( ElevationTypeTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto elevationType = token.ElevationType( );

    BOOST_CHECK( elevationType != TokenElevationType::Unknown );
}

// --run_test=SecurityTokenTests/LinkedTokenTest1
BOOST_AUTO_TEST_CASE( LinkedTokenTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto linkedToken = token.LinkedToken( );

    auto handle = linkedToken.Handle( );

    BOOST_CHECK( handle != 0 );
}

// --run_test=SecurityTokenTests/IsElevatedTest1
BOOST_AUTO_TEST_CASE( IsElevatedTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto isElevated = token.IsElevated( );
    // Surely; neither tests, nor Visual Studio, are executed using an elevated user ...
    BOOST_CHECK( isElevated == false );
}

// --run_test=SecurityTokenTests/HasRestrictionsTest1
BOOST_AUTO_TEST_CASE( HasRestrictionsTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto hasRestrictions = token.HasRestrictions( );
    BOOST_CHECK( hasRestrictions == true );
}

// --run_test=SecurityTokenTests/IsFilteredTest1
BOOST_AUTO_TEST_CASE( IsFilteredTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto isFiltered = token.IsFiltered( );
    BOOST_CHECK( isFiltered == true );
}

// --run_test=SecurityTokenTests/AccessInformationTest1
BOOST_AUTO_TEST_CASE( AccessInformationTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto accessInformation = token.AccessInformation( );
    BOOST_CHECK( accessInformation.TokenType() == TokenType::Primary );
}

// --run_test=SecurityTokenTests/IsVirtualizationAllowedTest1
BOOST_AUTO_TEST_CASE( IsVirtualizationAllowedTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto value = token.IsVirtualizationAllowed( );
    BOOST_CHECK( value == true );
}

// --run_test=SecurityTokenTests/IsVirtualizationEnabledTest1
BOOST_AUTO_TEST_CASE( IsVirtualizationEnabledTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto value = token.IsVirtualizationEnabled( );
    BOOST_CHECK( value == false );
}

// --run_test=SecurityTokenTests/IntegrityLevelTest1
BOOST_AUTO_TEST_CASE( IntegrityLevelTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto value = token.IntegrityLevel( );
    auto securityId = value.SecurityId( );
    auto flags = value.Flags( );
    BOOST_CHECK( securityId.IsValid() );
    BOOST_CHECK( flags != GroupFlags::None );
}



// --run_test=SecurityTokenTests/UserClaimAttributesTest1
BOOST_AUTO_TEST_CASE( UserClaimAttributesTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto userClaimAttributes = token.UserClaimAttributes( );

    BOOST_CHECK( userClaimAttributes.size() == 0 );
}

// --run_test=SecurityTokenTests/DeviceClaimAttributesTest1
BOOST_AUTO_TEST_CASE( DeviceClaimAttributesTest1 )
{
    auto token = CurrentProcess::OpenToken( TokenAccessRights::MaximumAllowed );
    auto deviceClaimAttributes = token.DeviceClaimAttributes( );

    BOOST_CHECK( deviceClaimAttributes.size( ) == 0 );
}




BOOST_AUTO_TEST_SUITE_END( )