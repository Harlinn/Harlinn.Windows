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
    void CppDatabaseReadersSourceGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto nspace = Options( ).Namespace( L"::" );
        WriteLine( L"#include \"pch.h\"" );
        WriteLine( );
        WriteLine( "#include \"DatabaseReaders.h\"" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( );

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            
            
            CreateColumnDataType( classInfo );
            
        }

        WriteLine( L"}" );

        Flush( );
    }

    void CppDatabaseReadersSourceGenerator::CreateColumnDataType( const ClassInfo& classInfo )
    {
        CreateQuery( classInfo );
    }
    void CppDatabaseReadersSourceGenerator::CreateQuery( const ClassInfo& classInfo )
    {
        auto topLevelClass = classInfo.TopLevelClass( );
        classInfo.BaseClasses( );
        auto className = CppHelper::GetColumnDataType( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = SqlServerHelper::GetColumnName( *primaryKey );
        auto viewName = SqlServerHelper::GetViewName( classInfo );
        auto members = SqlServerHelper::GetColumnsForSelect( classInfo );
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
                WriteLine( L"        L\"  {}.[{}], \\r\\n\"", shortName, memberName );
                
                if ( member.PrimaryKey( ) && topLevelClass->HasDescendants() )
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
                WriteLine( L"        L\"  {}.[{}] \\r\\n\"", shortName, memberName );

            }
        }
        WriteLine( L"        L\"FROM [{}] {} \\r\\n\";", viewName, shortName );


        WriteLine( L"    WideString {}::BaseViewName = L\"{}\";", className, viewName );
        WriteLine( L"    WideString {}::ViewAliasName = L\"{}\";", className, shortName );
        WriteLine( );
    }



}