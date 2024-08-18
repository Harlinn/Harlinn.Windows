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
#include "SqlServerUtils.h"

namespace Harlinn::ODBC::Tool
{
    SqlServerCreateTablesGenerator::SqlServerCreateTablesGenerator( const SqlServerGenerator& owner )
        : Base( owner, owner.Options( ).CreateTables( ) )
    {
    }

    void SqlServerCreateTablesGenerator::Run( )
    {
        WriteEntityTypesTable( );
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            WriteTable( classInfo );
        }
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            WriteForeignKeys( classInfo );
        }

        Flush( );
    }

    WideString SqlServerCreateTablesGenerator::GetColumnName( const MemberInfo& member )
    {
        return SqlServerHelper::GetColumnName( member );
    }
    WideString SqlServerCreateTablesGenerator::GetColumnType( const MemberInfo& member )
    {
        return SqlServerHelper::GetColumnType( member );
    }
    WideString SqlServerCreateTablesGenerator::GetColumnNullable( const MemberInfo& member )
    {
        return member.Nullable( ) ? L"NULL" : L"NOT NULL";
    }
    WideString SqlServerCreateTablesGenerator::GetTableName( const ClassInfo& classInfo )
    {
        return SqlServerHelper::GetTableName( classInfo );
    }

    WideString SqlServerCreateTablesGenerator::GetIndexName( const IndexInfo& indexInfo )
    {
        return SqlServerHelper::GetIndexName( indexInfo );
    }

    WideString SqlServerCreateTablesGenerator::GetColumnNames( const IndexInfo& indexInfo )
    {
        return SqlServerHelper::GetColumnNames( indexInfo );
    }


    void SqlServerCreateTablesGenerator::WriteTableColumn( const ClassInfo& classInfo, const MemberInfo& member )
    {
        auto& description = classInfo.Description();
        if ( description )
        {
            WriteLine( L"  /*" );
            WriteLine( L"   * {}", description );
            WriteLine( L"   */" );
        }
        auto columnName = GetColumnName( member );
        auto columnType = GetColumnType( member );
        auto columnNullable = GetColumnNullable( member );
        WriteLine( L"  {} {} {},", columnName, columnType, columnNullable );
    }
    void SqlServerCreateTablesGenerator::WriteTableIndex( const ClassInfo& classInfo, const IndexInfo& index )
    {
        auto tableName = GetTableName(classInfo);
        auto dbName = GetIndexName(index);
        auto dbColumnNames = GetColumnNames(index);

        if ( index.Unique() )
        {
            WriteLine( L"ALTER TABLE [dbo].[{}]", tableName );
            WriteLine( L"  ADD CONSTRAINT [{}] UNIQUE({})", dbName, dbColumnNames );
        }
        else
        {
            WriteLine( L"CREATE INDEX [{}] ON [dbo].[{}]({})", dbName, tableName, dbColumnNames );
        }
        WriteLine( "go" );

        WriteLine( );
    }
    void SqlServerCreateTablesGenerator::WriteTable( const ClassInfo& classInfo )
    {
        auto tableName = GetTableName( classInfo );
        const auto& name = classInfo.Name();
        auto primaryKey = classInfo.PrimaryKey( );
        const auto& primaryKeyFieldName = primaryKey->Name( );
        auto primaryKeyColumnType = GetColumnType( *primaryKey );

        WriteLine( L"/*" );
        WriteLine( L" * {}", name );
        if ( classInfo.IsTopLevel() == false )
        {
            
            auto baseClass = classInfo.BaseClass( );
            const auto& baseClassName = baseClass->Name();
            auto baseClassTableName = GetTableName( *baseClass );
            WriteLine( L" *" );
            WriteLine( L" * The {} entity a descendant of the {} entity.", name, baseClassName );
            WriteLine( L" *" );
            WriteLine( L" * Hence the one-to-one relationship between the " );
            WriteLine( L" * [dbo].[{}].[{}] field and the", tableName, primaryKeyFieldName );
            WriteLine( L" * [dbo].[{}].[{}] field.", baseClassTableName, primaryKeyFieldName );
        }
        WriteLine( L" *" );
        WriteLine( L" */" );

        WriteLine( L"CREATE TABLE [dbo].[{}]", tableName );
        WriteLine( L"(" );

        if ( primaryKey->Type( ) == MemberInfoType::Guid )
        {
            WriteLine( L"  [{}] {} ROWGUIDCOL NOT NULL,", primaryKeyFieldName, primaryKeyColumnType );
        }
        else
        {
            WriteLine( L"  [{}] {} IDENTITY(1, 1) NOT NULL,", primaryKeyFieldName, primaryKeyColumnType );
        }
        if ( classInfo.IsTopLevel() )
        {
            if ( classInfo.HasDescendants() )
            {
                WriteLine( L"  /*" );
                WriteLine( L"   * [EntityType] discriminates between {}", name );
                WriteLine( L"   * derived entity types." );
                WriteLine( L"   */" );
                WriteLine( L"  [EntityType] [int] NOT NULL," );
            }
        }
        const auto& persistentMembers = classInfo.OwnPersistentMembers();
        for( const auto & member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                WriteTableColumn( classInfo, *member );
            }
        }


        if ( classInfo.IsTopLevel() && classInfo.HasDescendants( ) )
        {
            WriteLine( L"  CONSTRAINT [FK_{}_EntityType] FOREIGN KEY([EntityType]) REFERENCES [dbo].[EntityTypes]([Id]),", tableName );
        }
        else if ( classInfo.IsTopLevel() == false )
        {
            auto baseClass = classInfo.BaseClass( );
            const auto& baseClassName = baseClass->Name( );
            auto baseClassTableName = GetTableName( *baseClass );
            
            WriteLine( L"  CONSTRAINT [FK_{}_{}] FOREIGN KEY([{}]) REFERENCES [dbo].[{}]([{}]),", tableName, primaryKeyFieldName, primaryKeyFieldName, baseClassTableName, primaryKeyFieldName );
        }



        WriteLine( L"  CONSTRAINT [PK_{}] PRIMARY KEY([{}])", tableName, primaryKeyFieldName );
        WriteLine( L")" );
        WriteLine( L"go" );
        WriteLine( );

        
        const auto& indexes = classInfo.Indexes();
        for( const auto& index : indexes )
        {
            WriteTableIndex( classInfo, *index );
        }
        
    }
    void SqlServerCreateTablesGenerator::WriteForeignKeys( const ClassInfo& classInfo )
    {
        const auto& persistentMembers = classInfo.OwnPersistentMembers( );
        for ( const auto& member : persistentMembers )
        {
            auto memberInfoType = member->Type( );
            if ( memberInfoType == MemberInfoType::Reference || memberInfoType == MemberInfoType::TimeSeries )
            {
                const ReferenceMemberInfo& reference = static_cast< const ReferenceMemberInfo& >( *member );
                WriteForeignKey( classInfo, reference );
            }
        }
    }
    void SqlServerCreateTablesGenerator::WriteForeignKey( const ClassInfo& classInfo, const ReferenceMemberInfo& reference )
    {
        auto tableName = GetTableName( classInfo );
        
        auto referencedClassInfo = reference.ReferencedType( );
        auto referencedPrimaryKey = referencedClassInfo->PrimaryKey( );
        auto referencedPrimaryKeyName = referencedPrimaryKey->Name( );
        auto referencedTableName = GetTableName( *referencedClassInfo );

        WriteLine( L"ALTER TABLE [dbo].[{}]", tableName );
        WriteLine( L"  ADD CONSTRAINT [FK_{}_{}] FOREIGN KEY([{}]) REFERENCES [dbo].[{}]([{}])", tableName, reference.Name(), reference.Name( ), referencedTableName, referencedPrimaryKeyName );
        WriteLine( L"go" );
        WriteLine( );
    }
    void SqlServerCreateTablesGenerator::WriteEntityTypesTable( )
    {
        WriteLine( "/*" );
        WriteLine( " * Entity type identifiers" );
        WriteLine( " *" );
        WriteLine( " */" );
        WriteLine( "CREATE TABLE [dbo].[EntityTypes]" );
        WriteLine( "(" );
        WriteLine( "  [Id][int] IDENTITY(1, 1) NOT NULL," );
        WriteLine( "  [EntityName][nvarchar](254) NOT NULL," );
        WriteLine( "  CONSTRAINT [PK_EntityTypes] PRIMARY KEY( [Id] )," );
        WriteLine( "  CONSTRAINT[ Unq_EntityName ] UNIQUE( [EntityName] )" );
        WriteLine( ")" );
        WriteLine( "go" );
        WriteLine( );
    }


}