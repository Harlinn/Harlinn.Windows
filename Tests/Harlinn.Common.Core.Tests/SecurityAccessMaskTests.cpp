/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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

BOOST_FIXTURE_TEST_SUITE( SecurityAccessMaskTests, LocalFixture )

// --run_test=SecurityAccessMaskTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
}

// --run_test=SecurityAccessMaskTests/CanDeleteTest1
BOOST_AUTO_TEST_CASE( CanDeleteTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetDelete( );
    auto enabled = accessMask.CanDelete( );
    BOOST_CHECK( enabled );
    accessMask.SetDelete( false );
    enabled = accessMask.CanDelete( );
    BOOST_CHECK( enabled == false );
}

// --run_test=SecurityAccessMaskTests/CanReadControlTest1
BOOST_AUTO_TEST_CASE( CanReadControlTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetReadControl( );
    auto enabled = accessMask.CanReadControl( );
    BOOST_CHECK( enabled );
    accessMask.SetReadControl( false );
    enabled = accessMask.CanReadControl( );
    BOOST_CHECK( enabled == false );
}


// --run_test=SecurityAccessMaskTests/CanReadPermissionsTest1
BOOST_AUTO_TEST_CASE( CanReadPermissionsTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetReadPermissions( );
    auto enabled = accessMask.CanReadPermissions( );
    BOOST_CHECK( enabled );
    accessMask.SetReadPermissions( false );
    enabled = accessMask.CanReadPermissions( );
    BOOST_CHECK( enabled == false );
}

// --run_test=SecurityAccessMaskTests/CanWriteDacTest1
BOOST_AUTO_TEST_CASE( CanWriteDacTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetWriteDac( );
    auto enabled = accessMask.CanWriteDac( );
    BOOST_CHECK( enabled );
    accessMask.SetWriteDac( false );
    enabled = accessMask.CanWriteDac( );
    BOOST_CHECK( enabled == false );
}

// --run_test=SecurityAccessMaskTests/CanChangePermissionsTest1
BOOST_AUTO_TEST_CASE( CanChangePermissionsTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetChangePermissions( );
    auto enabled = accessMask.CanChangePermissions( );
    BOOST_CHECK( enabled );
    accessMask.SetChangePermissions( false );
    enabled = accessMask.CanChangePermissions( );
    BOOST_CHECK( enabled == false );
}

// --run_test=SecurityAccessMaskTests/CanWriteOwnerTest1
BOOST_AUTO_TEST_CASE( CanWriteOwnerTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetWriteOwner( );
    auto enabled = accessMask.CanWriteOwner( );
    BOOST_CHECK( enabled );
    accessMask.SetWriteOwner( false );
    enabled = accessMask.CanWriteOwner( );
    BOOST_CHECK( enabled == false );
}

// --run_test=SecurityAccessMaskTests/CanTakeOwnershipTest1
BOOST_AUTO_TEST_CASE( CanTakeOwnershipTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetTakeOwnership( );
    auto enabled = accessMask.CanTakeOwnership( );
    BOOST_CHECK( enabled );
    accessMask.SetTakeOwnership( false );
    enabled = accessMask.CanTakeOwnership( );
    BOOST_CHECK( enabled == false );
}

// --run_test=SecurityAccessMaskTests/CanSynchronizeTest1
BOOST_AUTO_TEST_CASE( CanSynchronizeTest1 )
{
    AccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetSynchronize( );
    auto enabled = accessMask.CanSynchronize( );
    BOOST_CHECK( enabled );
    accessMask.SetSynchronize( false );
    enabled = accessMask.CanSynchronize( );
    BOOST_CHECK( enabled == false );
}

// --run_test=SecurityAccessMaskTests/EventWaitHandleAccessMaskCanModifyTest1
BOOST_AUTO_TEST_CASE( EventWaitHandleAccessMaskCanModifyTest1 )
{
    EventWaitHandleAccessMask accessMask;
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == 0 );
    accessMask.SetModify( );
    auto enabled = accessMask.CanModify( );
    BOOST_CHECK( enabled );
    accessMask.SetModify( false );
    enabled = accessMask.CanModify( );
    BOOST_CHECK( enabled == false );
}

// --run_test=SecurityAccessMaskTests/EventWaitHandleAccessMaskCanModifyTest2
BOOST_AUTO_TEST_CASE( EventWaitHandleAccessMaskCanModifyTest2 )
{
    EventWaitHandleAccessMask accessMask( EventWaitHandleRights::Synchronize );
    auto accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == SYNCHRONIZE );
    accessMask += EventWaitHandleRights::Modify;
    auto enabled = accessMask.CanModify( );
    BOOST_CHECK( enabled );
    accessMask -= EventWaitHandleRights::Modify;
    enabled = accessMask.CanModify( );
    BOOST_CHECK( enabled == false );
    accessMaskValue = accessMask.Value( );
    BOOST_CHECK( accessMaskValue == SYNCHRONIZE );

    bool isEqualToSYNCHRONIZE = accessMask == EventWaitHandleRights::Synchronize;
    BOOST_CHECK( isEqualToSYNCHRONIZE );
}






BOOST_AUTO_TEST_SUITE_END( )