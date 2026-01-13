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

#include "CodeGenerators/Generator.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    
    void JavaMsSqlSimpleReadersGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        for ( const auto& classInfoPtr : classes )
        {
            CreateReader( *classInfoPtr );
        }
    }

    void JavaMsSqlSimpleReadersGenerator::CreateReader( const Metadata::ClassInfo& classInfo )
    {
        JavaMsSqlSimpleDatabaseReaderGenerator readerGenerator( *this, classInfo );
        readerGenerator.Run( );
    }


}