#pragma once
#define GDAL_COMPILATION 1
#include <gtest/gtest.h>
#include <port/cpl_string.h>

std::string GetHomeDirecory( );
std::string GetTempDirecory( );

std::string GetCppDataDirecory( );
std::string GetCppDataFile( const std::string& filename );

std::string GetDriversDataDirecory( );
std::string GetDriversDataFile( const std::string& filename );

std::string GetGCoreDataDirecory( );
std::string GetGCoreDataFile( const std::string& filename );

std::string GetOGRDataDirecory( );
std::string GetOGRDataFile( const std::string& filename );

inline bool IsEqual( const char* first, const char* second )
{
    if ( first != second )
    {
        if ( first && second )
        {
            return strcmp( first, second ) == 0;
        }
        return false;
    }
    else
    {
        return true;
    }
}




