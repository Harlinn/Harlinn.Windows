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

#include "doxygen2mdOptions.h"
#include <HCCDoxygen.h>
#include <HCCStringBuilder.h>



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
        const auto& allTypes = typeSystem->AllTypes( );
        auto allTypesSize = allTypes.size( );

        auto globalNamespace = typeSystem->GlobalNamespace( );

        const auto& globalNamespaceMembers = globalNamespace->Members( );

        for ( auto& member : globalNamespaceMembers )
        {
            auto line = Format( L"{} -> {}", member->Name( ), member->QualifiedName( ) );
            std::wcout << line << std::endl;
        }

        auto documentCount = documentCollection.size( );
    }


}
