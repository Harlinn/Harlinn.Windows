/*
   Copyright 2024-2026 Espen Harlinn

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

