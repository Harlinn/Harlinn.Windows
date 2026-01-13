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
#include "CodeGenerators/Java/JavaHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void JavaDataTypesGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateDataType( classInfo );
        }
        CreateFactory( );
        CreateTestDataObjectFactory( );
    }

    void JavaDataTypesGenerator::CreateDataType( const Metadata::ClassInfo& classInfo )
    {
        JavaDataTypeGenerator dataTypeGenerator( *this, classInfo );
        dataTypeGenerator.Run( );
    }
    void JavaDataTypesGenerator::CreateFactory( )
    {
        JavaDataTypeFactoryGenerator dataTypeFactoryGenerator( *this );
        dataTypeFactoryGenerator.Run( );
    }

    void JavaDataTypesGenerator::CreateTestDataObjectFactory( )
    {
        JavaTestDataObjectFactoryGenerator testDataObjectFactoryGenerator( *this );
        testDataObjectFactoryGenerator.Run( );
    }

}