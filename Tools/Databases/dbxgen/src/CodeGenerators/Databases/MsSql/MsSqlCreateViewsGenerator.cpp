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
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"
#include <HCCStringBuilder.h>

namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql
{
    MsSqlCreateViewsGenerator::MsSqlCreateViewsGenerator( const MsSqlGenerator& owner )
        : Base( owner, owner.Options( ).CreateViews( ) )
    {
    }

    void MsSqlCreateViewsGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.IsTopLevel( ) )
            {
                CreateTopLevelView( classInfo );
            }
            else
            {
                CreateView( classInfo );
            }
        }
        Flush( );
    }

    WideString MsSqlCreateViewsGenerator::GetFieldNameForSelect( const Metadata::MemberInfo& memberInfo )
    {
        auto result = Format(L"[{}]", memberInfo.Name() );
        return result;
    }
    void MsSqlCreateViewsGenerator::CreateTopLevelView( const Metadata::ClassInfo& classInfo )
    {
        auto viewName = MsSqlHelper::GetViewName( classInfo );
        auto tableName = MsSqlHelper::GetTableName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyFieldName = primaryKey->Name( );

        const auto& members = classInfo.OwnPersistentMembers( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> statement;

        statement.AppendLine( L"CREATE OR ALTER VIEW {}", viewName );
        statement.AppendLine( L"AS" );
        statement.AppendLine( L" SELECT" );

        statement.Append( L"  [{}].[{}]", tableName, primaryKeyFieldName );
        

        if ( classInfo.HasDescendants() )
        {
            statement.AppendLine( L"," );
            statement.Append( L"  [{}].[EntityType]", tableName );
        }
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = members[ i ];
            if ( member->PrimaryKey( ) == false )
            {
                statement.AppendLine( L"," );
                auto fieldName = GetFieldNameForSelect( *member );
                statement.Append( L"  [{}].{}", tableName, fieldName );
            }
        }
        statement.AppendLine( );

        statement.AppendLine( L" FROM [{}]", tableName );


        auto sql = statement.ToString( );

        

        WriteLine( sql );
        WriteLine( L"go " );
        WriteLine( );
    }
    void MsSqlCreateViewsGenerator::CreateView( const Metadata::ClassInfo& classInfo )
    {
        auto baseClass = classInfo.BaseClass();
        auto parentViewName = MsSqlHelper::GetViewName( *baseClass );
        auto viewName = MsSqlHelper::GetViewName( classInfo );
        auto tableName = MsSqlHelper::GetTableName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyFieldName = primaryKey->Name( );



        const auto& members = classInfo.OwnPersistentMembers( );
        size_t membersCount = members.size( );

        StringBuilder<wchar_t> statement;

        statement.AppendLine( L"CREATE OR ALTER VIEW {}", viewName );
        statement.AppendLine( L"AS" );
        statement.AppendLine( L" SELECT" );
        statement.Append( L"  {}.*", parentViewName );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            auto member = members[ i ];
            if ( member->PrimaryKey( ) == false )
            {
                statement.AppendLine( L"," );

                auto fieldName = GetFieldNameForSelect( *member );
                statement.Append( L"  [{}].{}", tableName, fieldName );
            }
        }
        statement.AppendLine( );
        statement.AppendLine( L" FROM [{}]", tableName );
        statement.AppendLine( L" JOIN {} ON ([{}].{} = [{}].{})", parentViewName, parentViewName, primaryKeyFieldName, tableName, primaryKeyFieldName );


        auto sql = statement.ToString( );

        WriteLine( sql );
        WriteLine( L"go " );
        WriteLine( );
    }

}