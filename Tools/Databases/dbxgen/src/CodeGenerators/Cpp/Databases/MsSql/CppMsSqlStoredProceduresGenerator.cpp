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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/Cpp/CppHelper.h"
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    void CppMsSqlStoredProceduresGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        auto headerGuard = CppHelper::GetHeaderGuard( Filename( ) );
        auto nspace = Options( ).Namespace( L"::" );
        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Owner( ).Data( );
        auto dataTypesNamespace = dataTypesOptions.Namespace( L"::" );
        WriteLine( L"#pragma once" );
        WriteLine( L"#ifndef {}", headerGuard );
        WriteLine( L"#define {}", headerGuard );
        WriteLine( );
        WriteLine( "#include <HODBC.h>" );
        WriteLine( "#include <HCCData.h>" );
        WriteLine( "#include \"Types/DataTypes.h\"" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( L"    using namespace Harlinn;" );
        WriteLine( L"    using namespace Harlinn::ODBC;" );
        WriteLine( L"    using namespace Harlinn::Common::Core;" );
        WriteLine( L"    using namespace {};", dataTypesNamespace );
        WriteLine( );

        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                CreateInsert( classInfo );
                if ( classInfo.HasNullableReferences( ) )
                {
                    CreateInsert1( classInfo );
                }
                CreateInsertObject( classInfo );
                if ( classInfo.HasNullableReferences( ) )
                {
                    CreateInsertObject1( classInfo );
                }
                CreateUpdate( classInfo );
                if ( classInfo.HasNullableReferences( ) )
                {
                    CreateUpdate1( classInfo );
                    CreateUpdate2( classInfo );
                }
                CreateUpdateObject( classInfo );
                if ( classInfo.HasNullableReferences( ) )
                {
                    CreateUpdateObject1( classInfo );
                    CreateUpdateObject2( classInfo );
                }
                CreateDelete( classInfo );
                CreateDeleteObject( classInfo );
                WriteLine( );
            }
        }

        WriteLine( L"}" );
        WriteLine( L"#endif" );

        Flush( );
    }

    void CppMsSqlStoredProceduresGenerator::CreateInsert( const ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetInsertFunctionName( classInfo );
        auto functionParameters = CppHelper::GetInsertFunctionParameters( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} );", dllExport, functionName, functionParameters );
    }

    void CppMsSqlStoredProceduresGenerator::CreateInsert1( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetInsertFunctionName1( classInfo );
        auto functionParameters = CppHelper::GetInsertFunctionParameters1( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} );", dllExport, functionName, functionParameters );
    }
    void CppMsSqlStoredProceduresGenerator::CreateInsertObject( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetInsertFunctionName( classInfo );
        auto dataTypeName = CppHelper::GetDataType( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& data );", dllExport, functionName, dataTypeName );
    }
    void CppMsSqlStoredProceduresGenerator::CreateInsertObject1( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetInsertFunctionName1( classInfo );
        auto dataTypeName = CppHelper::GetDataType( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& data );", dllExport, functionName, dataTypeName );
    }

    void CppMsSqlStoredProceduresGenerator::CreateUpdate( const ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionParameters( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} );", dllExport, functionName, functionParameters );
    }

    void CppMsSqlStoredProceduresGenerator::CreateUpdate1( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName1( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionParameters1( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} );", dllExport, functionName, functionParameters );
    }
    void CppMsSqlStoredProceduresGenerator::CreateUpdate2( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName2( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionParameters2( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} );", dllExport, functionName, functionParameters );
    }
    void CppMsSqlStoredProceduresGenerator::CreateUpdateObject( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName( classInfo );
        auto dataTypeName = CppHelper::GetDataType( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& data );", dllExport, functionName, dataTypeName );
    }
    void CppMsSqlStoredProceduresGenerator::CreateUpdateObject1( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName1( classInfo );
        auto dataTypeName = CppHelper::GetDataType( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& data );", dllExport, functionName, dataTypeName );
    }
    void CppMsSqlStoredProceduresGenerator::CreateUpdateObject2( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName2( classInfo );
        auto dataTypeName = CppHelper::GetDataType( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& data );", dllExport, functionName, dataTypeName );
    }

    void CppMsSqlStoredProceduresGenerator::CreateDelete( const ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetDeleteFunctionName( classInfo );
        auto functionParameters = CppHelper::GetDeleteFunctionParameters( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} );", dllExport, functionName, functionParameters );
    }

    void CppMsSqlStoredProceduresGenerator::CreateDeleteObject( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetDeleteFunctionName( classInfo );
        auto dataTypeName = CppHelper::GetDataType( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& data );", dllExport, functionName, dataTypeName );
    }

}