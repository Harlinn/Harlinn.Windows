#include <iostream>

#include "project.h"
int main( int argc, char* argv[] )
{
    using namespace GenerateProject;
    Project project( argc, argv );
    if ( project.IsValid( ) )
    {
        try
        {
            project.Process( );
        }
        catch ( std::exception& exc )
        {
            auto what = exc.what( );
            printf( "Exception caught in main:%s\n", what );
        }
        return 0;
    }
    else
    {
        return -1;
    }
}

