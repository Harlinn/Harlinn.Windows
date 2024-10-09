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

    void CppMsSqlComplexDatabaseReadersSourceGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"::" );
        WriteLine( L"#include \"pch.h\"" );
        WriteLine( );
        WriteLine( "#include \"MsSqlComplexDatabaseReaders.h\"" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( );

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.DerivedClasses( ).size( ) )
            {
                CreateColumnDataType( classInfo );
            }
        }

        WriteLine( L"}" );

        Flush( );
    }


    void CppMsSqlComplexDatabaseReadersSourceGenerator::CreateColumnDataType( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetComplexColumnDataType( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyTypeName = CppHelper::GetMemberFieldType( *primaryKey );

        WideString baseClassName = L"BaseColumnData";

        auto shortName = classInfo.ShortName( );
        auto shortname = shortName.ToLower( );
        const auto& viewMembers = classInfo.ViewMembers( );

        CreateQuery( classInfo );

        CreateBindColumns( classInfo );
        CreateReadUnboundData( classInfo );

        WriteLine( );
    }


    void CppMsSqlComplexDatabaseReadersSourceGenerator::CreateQuery( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetComplexColumnDataType( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = MsSqlHelper::GetColumnName( *primaryKey );
        auto viewName = MsSqlHelper::GetViewName( classInfo );
        auto members = MsSqlHelper::GetColumnsForComplexSelect( classInfo );
        auto memberCount = members.size( );
        auto shortName = classInfo.ShortName( ).ToLower( );

        WriteLine( L"    WideString {}::BaseQuery = L\"SELECT \\r\\n\"", className );
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto owner = member.Owner( );
            auto memberName = member.Name( );
            if ( i < memberCount - 1 || member.PrimaryKey( ) )
            {
                if ( classInfo.IsViewMember( member ) )
                {
                    WriteLine( L"        L\"  {}.[{}], \\r\\n\"", shortName, memberName );
                }
                else
                {
                    auto derivedShortName = owner->ShortName( ).ToLower( );
                    WriteLine( L"        L\"  {}.[{}], \\r\\n\"", derivedShortName, memberName );
                }
                if ( member.PrimaryKey( ) )
                {
                    if ( i < memberCount - 1 )
                    {
                        WriteLine( L"        L\"  {}.[EntityType], \\r\\n\"", shortName );
                    }
                    else
                    {
                        WriteLine( L"        L\"  {}.[EntityType] \\r\\n\"", shortName );
                    }
                }
            }
            else
            {
                if ( classInfo.IsViewMember( member ) )
                {
                    WriteLine( L"        L\"  {}.[{}] \\r\\n\"", shortName, memberName );
                }
                else
                {
                    auto derivedShortName = owner->ShortName( ).ToLower( );
                    WriteLine( L"        L\"  {}.[{}] \\r\\n\"", derivedShortName, memberName );
                }
                
            }
        }
        WriteLine( L"        L\"FROM [{}] {} \\r\\n\"", viewName, shortName );
        auto derivedClasses = classInfo.AllDerivedClasses( );
        auto derivedClassCount = derivedClasses.size( );
        for ( size_t i = 0; i < derivedClassCount; i++ )
        {
            const auto& derivedClass = *derivedClasses[ i ];
            auto tableName = MsSqlHelper::GetTableName( derivedClass );
            auto derivedShortName = derivedClass.ShortName( ).ToLower( );
            if ( i < derivedClassCount - 1 )
            {
                WriteLine( L"        L\"  LEFT JOIN [{}] {} ON({}.{} = {}.{} ) \\r\\n\"", tableName, derivedShortName, shortName, primaryKeyName, derivedShortName, primaryKeyName );
            }
            else
            {
                WriteLine( L"        L\"  LEFT JOIN [{}] {} ON({}.{} = {}.{} )\";", tableName, derivedShortName, shortName, primaryKeyName, derivedShortName, primaryKeyName );
            }

        }

        
        
        WriteLine( L"    WideString {}::BaseViewName = L\"{}\";", className, viewName );
        WriteLine( L"    WideString {}::ViewAliasName = L\"{}\";", className, shortName );
        WriteLine( );
    }
    

    void CppMsSqlComplexDatabaseReadersSourceGenerator::CreateBindColumns( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetComplexColumnDataType( classInfo );
        auto shortName = classInfo.ShortName( ).ToUpper( );
        auto members = MsSqlHelper::GetBindableColumnsForComplexSelect( classInfo );
        auto memberCount = members.size( );
        if ( memberCount )
        {
            WriteLine( L"    void {}::BindColumns( const ODBC::Statement& statement )", className );
            WriteLine( L"    {" );
            for ( const auto& member : members )
            {
                if ( classInfo.IsViewMember( *member ) )
                {
                    auto fieldId = Format(L"{}_{}_FIELD_ID", shortName, member->Name( ).ToUpper( ) );
                    auto typeName = CppHelper::GetMemberFieldType( *member );
                    auto fieldName = CppHelper::GetMemberFieldName( *member );
                    WriteLine( L"        Bind( statement, {}, {} );", fieldId, fieldName );
                    if ( member->PrimaryKey( ) )
                    {
                        fieldId = Format( L"{}_KIND_FIELD_ID", shortName  );
                        WriteLine( L"        Bind( statement, {}, kind_ );", fieldId );
                    }
                }
                else
                {
                    auto owner = member->Owner( );
                    auto derivedShortName = owner->ShortName( ).ToUpper( );
                    auto fieldId = Format( L"{}_{}_FIELD_ID", derivedShortName, member->Name( ).ToUpper( ) );
                    auto typeName = CppHelper::GetMemberNullableFieldType( *member );
                    auto fieldName = CppHelper::GetLongMemberFieldName( *member );
                    WriteLine( L"        Bind( statement, {}, {} );", fieldId, fieldName );
                }
            }
            WriteLine( L"    }" );
            WriteLine( );
        }
    }

    void CppMsSqlComplexDatabaseReadersSourceGenerator::CreateReadUnboundData( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetComplexColumnDataType( classInfo );
        auto shortName = classInfo.ShortName( ).ToUpper( );
        auto members = MsSqlHelper::GetUnboundColumnsForComplexSelect( classInfo );
        auto memberCount = members.size( );
        if ( memberCount )
        {
            WriteLine( L"    void {}::ReadUnboundData( const ODBC::Statement& statement )", className );
            WriteLine( L"    {" );
            for ( const auto& member : members )
            {
                if ( classInfo.IsViewMember( *member ) )
                {
                    auto memberType = member->Type( );
                    if ( memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
                    {
                        auto fieldName = CppHelper::GetMemberFieldName( *member );
                        auto fieldId = Format( L"{}_{}_FIELD_ID", shortName, member->Name( ).ToUpper( ) );
                        if ( memberType == MemberInfoType::String )
                        {
                            if ( member->Nullable( ) )
                            {
                                WriteLine( L"            {} = statement.GetDBWideString({});", fieldName, fieldId );
                            }
                            else
                            {
                                WriteLine( L"            {} = statement.GetWideString({});", fieldName, fieldId );
                            }
                        }
                        else if ( memberType == MemberInfoType::Binary )
                        {
                            if ( member->Nullable( ) )
                            {
                                WriteLine( L"            {} = statement.GetDBBinary({});", fieldName, fieldId );
                            }
                            else
                            {
                                WriteLine( L"            {} = statement.GetBinary({});", fieldName, fieldId );
                            }
                        }
                    }
                }
                else
                {
                    auto memberType = member->Type( );
                    if ( memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
                    {
                        auto fieldName = CppHelper::GetLongMemberFieldName( *member );
                        auto owner = member->Owner( );
                        auto derivedShortName = owner->ShortName( ).ToUpper( );
                        auto fieldId = Format( L"{}_{}_FIELD_ID", derivedShortName, member->Name( ).ToUpper( ) );
                        if ( memberType == MemberInfoType::String )
                        {
                            WriteLine( L"            {} = statement.GetDBWideString({});", fieldName, fieldId );
                        }
                        else if ( memberType == MemberInfoType::Binary )
                        {
                            WriteLine( L"            {} = statement.GetDBBinary({});", fieldName, fieldId );
                        }
                    }
                }
            }
            WriteLine( L"    }" );
        }
    }

}