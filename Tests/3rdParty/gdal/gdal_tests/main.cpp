#include <gtest/gtest.h>

#include "gcore/gdal.h"
#include "ogr/ogr_api.h"
#include "ogr/ogrsf_frmts/ogrsf_frmts.h"


int main( int argc, char** argv )
{
    ::GDALAllRegister( );
    ::OGRRegisterAll( );

    argc = GDALGeneralCmdLineProcessor( argc, &argv, 0 );

    testing::InitGoogleTest( &argc, argv );
    auto result = RUN_ALL_TESTS( );

    CSLDestroy( argv );
    GDALDestroyDriverManager( );
    OGRCleanupAll( );

    CPLDumpSharedList( nullptr );
    CPLCleanupTLS( );

    return result;
}

