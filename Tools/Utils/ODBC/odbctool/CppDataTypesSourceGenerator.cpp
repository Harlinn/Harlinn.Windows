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

#include "Generator.h"
#include "SqlServerHelper.h"
#include "CppHelper.h"

namespace Harlinn::ODBC::Tool
{
    void CppDataTypesSourceGenerator::Run( )
    {
        auto nspace = Options( ).Namespace( L"::" );
        WriteLine( L"#include \"pch.h\"" );
        WriteLine( );
        WriteLine( "#include \"DataTypes.h\"" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( );

        CreateDataTypeFactory( );

        WriteLine( L"}" );

        Flush( );
    }

    void CppDataTypesSourceGenerator::CreateDataTypeFactory( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        auto dllExport = Options( ).DllExport( );
        WriteLine( L"    {} std::shared_ptr<BaseData<Kind, Guid>> DataFactory( Kind kind )", dllExport );
        WriteLine( L"    {" );
        WriteLine( L"        std::shared_ptr<BaseData<Kind, Guid>> result;" );
        WriteLine( L"        switch(kind)" );
        WriteLine( L"        {" );
        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                WriteLine( L"            case Kind::{}:", classInfo->Name() );
                auto className = CppHelper::GetDataType( *classInfo );
                WriteLine( L"                result = std::make_shared<{}>( );", className );
                WriteLine( L"                break;" );
            }
        }
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );

    }

}