#include "test_utils.h"
#include "HCCIO.h"

namespace hcc = Harlinn::Common::Core;

std::string GetHomeDirecory( )
{
    auto ptr = getenv( "HCC_HOME" );
    if ( ptr )
    {
        return ptr;
    }
    return std::string( );
}

std::string GetTempDirecory( )
{
    auto tmpDir = hcc::IO::Directory::GetTemporaryA( ) + "\\GDALTest";
    return std::string( tmpDir.c_str( ), tmpDir.size( ) );
}


std::string GetDataDirecory( )
{
    return GetHomeDirecory( ) + "\\Tests\\3rdParty\\gdal\\data";
}


std::string GetCppDataDirecory( )
{
    return GetDataDirecory( ) + "\\cpp";
}

std::string GetCppDataFile( const std::string& filename )
{
    return GetCppDataDirecory( ) + "\\" + filename;
}


std::string GetDriversDataDirecory( )
{
    return GetDataDirecory( ) + "\\gdrivers";
}

std::string GetDriversDataFile( const std::string& filename )
{
    return GetDriversDataDirecory( ) + "\\" + filename;
}

std::string GetGCoreDataDirecory( )
{
    return GetDataDirecory( ) + "\\gcore";
}

std::string GetGCoreDataFile( const std::string& filename )
{
    return GetGCoreDataDirecory( ) + "\\" + filename;
}

std::string GetOGRDataDirecory( )
{
    return GetDataDirecory( ) + "\\ogr";
}

std::string GetOGRDataFile( const std::string& filename )
{
    return GetOGRDataDirecory( ) + "\\" + filename;
}

