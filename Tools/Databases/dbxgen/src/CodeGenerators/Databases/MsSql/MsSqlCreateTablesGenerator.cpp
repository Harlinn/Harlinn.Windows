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

#include "CodeGenerators/Generator.h"
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"


namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql
{
    MsSqlCreateTablesGenerator::MsSqlCreateTablesGenerator( const MsSqlGenerator& owner )
        : Base( owner, owner.Options( ).CreateTables( ) )
    {
    }

    void MsSqlCreateTablesGenerator::Run( )
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

    WideString MsSqlCreateTablesGenerator::GetColumnName( const Metadata::MemberInfo& member )
    {
        return MsSqlHelper::GetColumnName( member );
    }
    WideString MsSqlCreateTablesGenerator::GetColumnType( const Metadata::MemberInfo& member )
    {
        return MsSqlHelper::GetColumnType( member );
    }
    WideString MsSqlCreateTablesGenerator::GetColumnNullable( const Metadata::MemberInfo& member )
    {
        return WideString::From( member.Nullable( ) ? L"NULL" : L"NOT NULL" );
    }
    WideString MsSqlCreateTablesGenerator::GetTableName( const Metadata::ClassInfo& classInfo )
    {
        return MsSqlHelper::GetTableName( classInfo );
    }

    WideString MsSqlCreateTablesGenerator::GetIndexName( const Metadata::IndexInfo& indexInfo )
    {
        return MsSqlHelper::GetIndexName( indexInfo );
    }

    WideString MsSqlCreateTablesGenerator::GetColumnNames( const Metadata::IndexInfo& indexInfo )
    {
        return MsSqlHelper::GetColumnNames( indexInfo );
    }


    void MsSqlCreateTablesGenerator::WriteTableColumn( const Metadata::ClassInfo& classInfo, const Metadata::MemberInfo& member )
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
    void MsSqlCreateTablesGenerator::WriteTableIndex( const Metadata::ClassInfo& classInfo, const Metadata::IndexInfo& index )
    {
        auto tableName = GetTableName(classInfo);
        auto dbName = GetIndexName(index);
        auto dbColumnNames = GetColumnNames(index);

        if ( index.Unique() )
        {
            if ( index.HasNullableElements( ) )
            {
                auto nullableMembers = index.NullableElements( );
                WriteLine( L"CREATE UNIQUE NONCLUSTERED INDEX [{}] ON [dbo].[{}]({})", dbName, tableName, dbColumnNames );      
                WriteLine( L"   WHERE [{}] IS NOT NULL", nullableMembers[0]->Name() );
                WriteLine( "go" );
            }
            else
            {
                WriteLine( L"ALTER TABLE [dbo].[{}]", tableName );
                WriteLine( L"  ADD CONSTRAINT [{}] UNIQUE({})", dbName, dbColumnNames );
                WriteLine( "go" );
            }
        }
        else
        {
            WriteLine( L"CREATE INDEX [{}] ON [dbo].[{}]({})", dbName, tableName, dbColumnNames );
            WriteLine( "go" );
        }
        

        WriteLine( );
    }
    void MsSqlCreateTablesGenerator::WriteTable( const Metadata::ClassInfo& classInfo )
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

        if ( primaryKey->Type( ) == Metadata::MemberInfoType::Guid )
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
            
            WriteLine( L"  CONSTRAINT [FK_{}_{}] FOREIGN KEY([{}]) REFERENCES [dbo].[{}]([{}]) ON DELETE CASCADE,", tableName, primaryKeyFieldName, primaryKeyFieldName, baseClassTableName, primaryKeyFieldName );
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
    void MsSqlCreateTablesGenerator::WriteForeignKeys( const Metadata::ClassInfo& classInfo )
    {
        const auto& persistentMembers = classInfo.OwnPersistentMembers( );
        for ( const auto& member : persistentMembers )
        {
            auto memberInfoType = member->Type( );
            if ( memberInfoType == Metadata::MemberInfoType::Reference || memberInfoType == Metadata::MemberInfoType::TimeSeries )
            {
                const auto& reference = static_cast< const Metadata::ReferenceMemberInfo& >( *member );
                WriteForeignKey( classInfo, reference );
            }
        }
    }
    void MsSqlCreateTablesGenerator::WriteForeignKey( const Metadata::ClassInfo& classInfo, const Metadata::ReferenceMemberInfo& reference )
    {
        auto tableName = GetTableName( classInfo );
        
        auto referencedClassInfo = reference.ReferencedType( );
        auto referencedPrimaryKey = referencedClassInfo->PrimaryKey( );
        auto referencedPrimaryKeyName = referencedPrimaryKey->Name( );
        auto referencedTableName = GetTableName( *referencedClassInfo );

        WriteLine( L"ALTER TABLE [dbo].[{}]", tableName );
        WriteLine( L"  ADD CONSTRAINT [FK_{}_{}] FOREIGN KEY([{}]) REFERENCES [dbo].[{}]([{}])", tableName, reference.Name( ), reference.Name( ), referencedTableName, referencedPrimaryKeyName );
        WriteLine( L"go" );
        WriteLine( );
    }
    void MsSqlCreateTablesGenerator::WriteEntityTypesTable( )
    {
        WriteLine( "/*" );
        WriteLine( " * Entity type identifiers" );
        WriteLine( " *" );
        WriteLine( " */" );
        WriteLine( "CREATE TABLE [dbo].[EntityTypes]" );
        WriteLine( "(" );
        WriteLine( "  [Id][int] NOT NULL," );
        WriteLine( "  [EntityName][nvarchar](254) NOT NULL," );
        WriteLine( "  CONSTRAINT [PK_EntityTypes] PRIMARY KEY( [Id] )," );
        WriteLine( "  CONSTRAINT[ Unq_EntityName ] UNIQUE( [EntityName] )" );
        WriteLine( ")" );
        WriteLine( "go" );
        WriteLine( );
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        for ( const auto& classInfo : classes )
        {
            WriteLine( L"INSERT INTO [dbo].[EntityTypes] VALUES( {},'{}' )", classInfo->Id(), classInfo->Name() );
            WriteLine( L"go" );
        }

    }


}