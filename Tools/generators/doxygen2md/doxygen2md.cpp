/*
   Copyright 2024-2025 Espen Harlinn

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

#include "D2MStructure.h"

using namespace Doxygen2Md;





int main(int argc, char* argv[] )
{
    using namespace Harlinn::Common::Core;
    using namespace Doxygen2Md;

    Doxygen2MdOptions options;
    

    if ( options.Parse( argc, argv ) )
    {
        Doxygen::DocumentCollection documentCollection;
        auto directory = options.InputDirectory();
        documentCollection.AddDirectory( directory );
        auto typeSystem = documentCollection.TypeSystem( );
        const auto& allCompoundDefs = typeSystem->AllCompoundDefs( );
        auto allCompoundDefsSize = allCompoundDefs.size( );

        const auto& namespaceMap = typeSystem->NamespaceMap( );
        auto namespaceMapSize = namespaceMap.size( );

        auto namespaces = typeSystem->Namespaces( );
        auto namespacesSize = namespaces.size( );

        std::ranges::sort( namespaces, []( auto a, auto b ) { return a->CompoundName( ) < b->CompoundName( ); } );

        for ( auto entry : namespaces )
        {
            auto it = namespaceMap.find( entry->CompoundName( ) );
            if ( it == namespaceMap.end( ) )
            {
                PrintLn( "Missing {}", entry->CompoundName( ) );
            }
            else
            {
                int foundIndex = -1;
                int index = 0;
                for ( auto& mapEntry : namespaceMap )
                {
                    if ( mapEntry.second == entry )
                    {
                        foundIndex = index;
                        break;
                    }
                    index++;
                }
                if ( foundIndex == -1 )
                {
                    PrintLn( "Duplicate {}", entry->CompoundName( ) );
                }
            }
            
        }

        const auto& rootCompoundDefs = typeSystem->RootCompoundDefs( );
        auto rootCompoundDefsSize = rootCompoundDefs.size( );
        

        



    }


}
