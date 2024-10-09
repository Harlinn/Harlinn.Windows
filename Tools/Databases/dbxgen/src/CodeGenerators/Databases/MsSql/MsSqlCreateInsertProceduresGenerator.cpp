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
    MsSqlCreateInsertProceduresGenerator::MsSqlCreateInsertProceduresGenerator( const MsSqlGenerator& owner )
        : Base( owner, owner.Options( ).CreateInsertProcedures( ) )
    {
    }

    void MsSqlCreateInsertProceduresGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                CreateInsertProcedure( classInfo );
                if ( classInfo.HasNullableReferences( ) )
                {
                    CreateInsertProcedure1( classInfo );
                }
                CreateInsertTrigger( classInfo );
            }
        }

        Flush( );
    }

    WideString MsSqlCreateInsertProceduresGenerator::GetProcedureParameters( const Metadata::ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        return GetProcedureParameters( classInfo, members );
    }

    WideString MsSqlCreateInsertProceduresGenerator::GetProcedureParameters( const Metadata::ClassInfo& classInfo, const std::vector<std::shared_ptr<Metadata::MemberInfo>>& persistentMembers )
    {
        size_t membersCount = persistentMembers.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto primaryKeyType = MsSqlHelper::GetColumnType( *primaryKey );

        auto rowVersion = classInfo.RowVersion( );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"  @{} {} OUTPUT", primaryKeyName, primaryKeyType );

        if ( (rowVersion == nullptr && membersCount > 1) || ( rowVersion != nullptr && membersCount > 2 ) )
        {
            parameters.AppendLine( L"," );
        }
        else
        {
            parameters.AppendLine( );
        }


        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *persistentMembers[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != Metadata::MemberInfoType::RowVersion )
                {
                    auto variableName = Format( L"@{}", member.Name( ).FirstToUpper( ) );
                    auto variableType = MsSqlHelper::GetColumnType( member );

                    if ( i < ( membersCount - 1 ) )
                    {
                        parameters.AppendLine( L"  {} {},", variableName, variableType );
                    }
                    else
                    {
                        parameters.AppendLine( L"  {} {}", variableName, variableType );
                    }
                }
            }
        }
        
        return parameters.ToString( );
    }

    WideString MsSqlCreateInsertProceduresGenerator::GetInsertStatement( const Metadata::ClassInfo& classInfo )
    {
        const auto& members = classInfo.OwnPersistentMembers( );
        return GetInsertStatement( classInfo, members );
    }

    WideString MsSqlCreateInsertProceduresGenerator::GetInsertStatement( const Metadata::ClassInfo& classInfo, const std::vector<std::shared_ptr<Metadata::MemberInfo>>& ownPersistentMembers )
    {
        StringBuilder<wchar_t> statement;

        size_t membersCount = ownPersistentMembers.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );


        auto tableName = MsSqlHelper::GetTableName( classInfo );

        auto insertString = Format( L"INSERT INTO [{}]([{}]", tableName, primaryKeyName );
        auto valueString = Format( L"VALUES(@{}", primaryKeyName );

        if ( classInfo.IsTopLevel( ) && classInfo.HasDescendants( ) )
        {
            insertString += L", [EntityType]";
            valueString += L", @EntityType";
        }

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *ownPersistentMembers[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );

                auto variableName = member.Name( ).FirstToUpper( );

                insertString += Format( L", [{}]", variableName );

                if ( memberType == Metadata::MemberInfoType::RowVersion )
                {
                    valueString += L", 0";
                }
                else
                {
                    valueString += Format( L", @{}", variableName );
                }
            }
        }
        insertString += L")";
        valueString += L");";
        statement.AppendLine( L"      {}", insertString );
        statement.AppendLine( L"          {}", valueString );

        return statement.ToString( );
    }

    WideString MsSqlCreateInsertProceduresGenerator::GetInsertProcedure( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> procedure;

        auto procedureName = MsSqlHelper::GetInsertProcedureName( classInfo );
        
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto primaryKeyType = MsSqlHelper::GetColumnType( *primaryKey );
        
        procedure.AppendLine( L"CREATE OR ALTER PROCEDURE [{}]", procedureName );

        auto parameters = GetProcedureParameters( classInfo );
        procedure.Append( parameters );


        auto savePointName = Format( L"SavePoint{}", classInfo.Id() );


        procedure.AppendLine( L"AS" );
        procedure.AppendLine( L"  BEGIN" );
        procedure.AppendLine( L"    IF @{} IS NULL", primaryKeyName );
        procedure.AppendLine( L"    BEGIN" );
        procedure.AppendLine( L"      SET @{} = NEWID()", primaryKeyName );
        procedure.AppendLine( L"    END" );
        if ( classInfo.IsTopLevel( ) == false || classInfo.HasDescendants( ) )
        {
            procedure.AppendLine( L"    DECLARE @EntityType INT;" );
            procedure.AppendLine( L"    SET @EntityType = {};", classInfo.Id() );
        }
        procedure.AppendLine( L"    DECLARE @TranCounter INT;" );
        procedure.AppendLine( L"    SET @TranCounter = @@TRANCOUNT;" );
        procedure.AppendLine( L"    IF @TranCounter > 0" );
        procedure.AppendLine( L"      SAVE TRANSACTION {};", savePointName );
        procedure.AppendLine( L"    ELSE" );
        procedure.AppendLine( L"      BEGIN TRANSACTION;" );
        procedure.AppendLine( L"    BEGIN TRY" );

        auto classInfos = classInfo.BaseClassesAndSelf();
        auto classInfoCount = classInfos.size( );

        for ( size_t i = 0; i < classInfoCount; i++ )
        {
            const auto& currentClassInfo = *classInfos[ i ];
            auto insertStatement = GetInsertStatement( currentClassInfo );
            procedure.Append( insertStatement );
        }


        procedure.AppendLine( L"      IF @TranCounter = 0" );
        procedure.AppendLine( L"          COMMIT TRANSACTION;" );
        procedure.AppendLine( L"    END TRY" );
        procedure.AppendLine( L"    BEGIN CATCH" );
        procedure.AppendLine( L"        DECLARE @ErrorMessage NVARCHAR(4000);" );
        procedure.AppendLine( L"        DECLARE @ErrorSeverity INT;" );
        procedure.AppendLine( L"        DECLARE @ErrorState INT;" );
        procedure.AppendLine( L"        SELECT @ErrorMessage = ERROR_MESSAGE()," );
        procedure.AppendLine( L"            @ErrorSeverity = ERROR_SEVERITY()," );
        procedure.AppendLine( L"            @ErrorState = ERROR_STATE();" );
        procedure.AppendLine( L"        IF @TranCounter = 0" );
        procedure.AppendLine( L"          ROLLBACK TRANSACTION;" );
        procedure.AppendLine( L"        ELSE" );
        procedure.AppendLine( L"          IF XACT_STATE() <> -1" );
        procedure.AppendLine( L"            ROLLBACK TRANSACTION {};", savePointName );
        procedure.AppendLine( L"        RAISERROR(" );
        procedure.AppendLine( L"            @ErrorMessage," );
        procedure.AppendLine( L"            @ErrorSeverity," );
        procedure.AppendLine( L"            @ErrorState);" );
        procedure.AppendLine( L"    END CATCH" );
        procedure.AppendLine( L"  END" );

        return procedure.ToString( );
    }

    WideString MsSqlCreateInsertProceduresGenerator::GetInsertTrigger( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> trigger;

        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );

        if ( membersCount == 0 )
        {
            return {};
        }

        auto procedureName = MsSqlHelper::GetInsertProcedureName( classInfo );
        auto viewName = MsSqlHelper::GetViewName( classInfo );
        auto triggerName = MsSqlHelper::GetInsertTriggerName( classInfo );

        trigger.AppendLine( L"CREATE OR ALTER TRIGGER [{}]", triggerName );
        trigger.AppendLine( L"ON [{}]", viewName );
        trigger.AppendLine( L"INSTEAD OF INSERT AS" );
        trigger.AppendLine( L"  BEGIN" );
        trigger.AppendLine( L"    DECLARE @cur CURSOR" );
        trigger.AppendLine( L"    SET @cur = CURSOR FOR" );
        trigger.AppendLine( L"      SELECT" );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableName = member.Name( ).FirstToUpper();

            if ( i < ( membersCount - 1 ) )
            {
                trigger.AppendLine( L"        [{}],", variableName );
            }
            else
            {
                trigger.AppendLine( L"        [{}]", variableName );
            }
        }
        trigger.AppendLine( L"      FROM inserted" );
        trigger.AppendLine( L"    OPEN @cur" );

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];

            auto variableName = Format(L"@{}", member.Name( ).FirstToUpper() );
            auto variableType = MsSqlHelper::GetColumnType( member );

            trigger.AppendLine( L"    DECLARE {} {}", variableName, variableType );
        }
        trigger.AppendLine( L"    FETCH NEXT FROM @cur INTO" );
        WideString args;

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableName = Format(L"@{}", member.Name( ).FirstToUpper());

            if ( i < ( membersCount - 1 ) )
            {
                trigger.AppendLine( L"        {},", variableName );
                args += variableName + L",";
            }
            else
            {
                trigger.AppendLine( L"        {}", variableName );
                args += variableName;
            }
        }
        trigger.AppendLine( L"    WHILE(@@fetch_status <> -1)" );
        trigger.AppendLine( L"      BEGIN" );
        trigger.AppendLine( L"        EXEC [{}] {}", procedureName, args );
        trigger.AppendLine( L"        FETCH NEXT FROM @cur INTO" );


        for ( int i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableName = Format( L"@{}", member.Name( ).FirstToUpper( ) );

            if ( i < ( membersCount - 1 ) )
            {
                trigger.AppendLine( L"            {},", variableName );
            }
            else
            {
                trigger.AppendLine( L"            {}", variableName );
            }
        }

        trigger.AppendLine( L"      END" );




        trigger.AppendLine( L"    CLOSE @cur" );
        trigger.AppendLine( L"    DEALLOCATE @cur" );
        trigger.AppendLine( L"  END" );

        return trigger.ToString( );
    }

    void MsSqlCreateInsertProceduresGenerator::CreateInsertProcedure( const Metadata::ClassInfo& classInfo )
    {
        auto insertProcedure = GetInsertProcedure( classInfo );
        WriteLine( insertProcedure );
        WriteLine( "GO" );
        WriteLine( );
    }

    void MsSqlCreateInsertProceduresGenerator::CreateInsertTrigger( const Metadata::ClassInfo& classInfo )
    {
        auto insertTrigger = GetInsertTrigger( classInfo );
        WriteLine( insertTrigger );
        WriteLine( "GO" );
        WriteLine( );
    }

    
    WideString MsSqlCreateInsertProceduresGenerator::GetInsertProcedure1( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> procedure;

        auto procedureName = MsSqlHelper::GetInsertProcedureName1( classInfo );

        auto members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto primaryKeyType = MsSqlHelper::GetColumnType( *primaryKey );

        procedure.AppendLine( L"CREATE OR ALTER PROCEDURE [{}]", procedureName );

        auto parameters = GetProcedureParameters( classInfo, members );
        procedure.Append( parameters );


        auto savePointName = Format( L"SavePoint{}", classInfo.Id( ) );


        procedure.AppendLine( L"AS" );
        procedure.AppendLine( L"  BEGIN" );
        procedure.AppendLine( L"    IF @{} IS NULL", primaryKeyName );
        procedure.AppendLine( L"    BEGIN" );
        procedure.AppendLine( L"      SET @{} = NEWID()", primaryKeyName );
        procedure.AppendLine( L"    END" );
        if ( classInfo.IsTopLevel( ) == false || classInfo.HasDescendants( ) )
        {
            procedure.AppendLine( L"    DECLARE @EntityType INT;" );
            procedure.AppendLine( L"    SET @EntityType = {};", classInfo.Id( ) );
        }
        procedure.AppendLine( L"    DECLARE @TranCounter INT;" );
        procedure.AppendLine( L"    SET @TranCounter = @@TRANCOUNT;" );
        procedure.AppendLine( L"    IF @TranCounter > 0" );
        procedure.AppendLine( L"      SAVE TRANSACTION {};", savePointName );
        procedure.AppendLine( L"    ELSE" );
        procedure.AppendLine( L"      BEGIN TRANSACTION;" );
        procedure.AppendLine( L"    BEGIN TRY" );

        auto classInfos = classInfo.BaseClassesAndSelf( );
        auto classInfoCount = classInfos.size( );

        for ( size_t i = 0; i < classInfoCount; i++ )
        {
            const auto& currentClassInfo = *classInfos[ i ];
            auto ownPersistentMembersExceptNullableReferences = currentClassInfo.OwnPersistentMembersExceptNullableReferences( );
            auto insertStatement = GetInsertStatement( currentClassInfo, ownPersistentMembersExceptNullableReferences );
            procedure.Append( insertStatement );
        }


        procedure.AppendLine( L"      IF @TranCounter = 0" );
        procedure.AppendLine( L"          COMMIT TRANSACTION;" );
        procedure.AppendLine( L"    END TRY" );
        procedure.AppendLine( L"    BEGIN CATCH" );
        procedure.AppendLine( L"        DECLARE @ErrorMessage NVARCHAR(4000);" );
        procedure.AppendLine( L"        DECLARE @ErrorSeverity INT;" );
        procedure.AppendLine( L"        DECLARE @ErrorState INT;" );
        procedure.AppendLine( L"        SELECT @ErrorMessage = ERROR_MESSAGE()," );
        procedure.AppendLine( L"            @ErrorSeverity = ERROR_SEVERITY()," );
        procedure.AppendLine( L"            @ErrorState = ERROR_STATE();" );
        procedure.AppendLine( L"        IF @TranCounter = 0" );
        procedure.AppendLine( L"          ROLLBACK TRANSACTION;" );
        procedure.AppendLine( L"        ELSE" );
        procedure.AppendLine( L"          IF XACT_STATE() <> -1" );
        procedure.AppendLine( L"            ROLLBACK TRANSACTION {};", savePointName );
        procedure.AppendLine( L"        RAISERROR(" );
        procedure.AppendLine( L"            @ErrorMessage," );
        procedure.AppendLine( L"            @ErrorSeverity," );
        procedure.AppendLine( L"            @ErrorState);" );
        procedure.AppendLine( L"    END CATCH" );
        procedure.AppendLine( L"  END" );

        return procedure.ToString( );
    }

    void MsSqlCreateInsertProceduresGenerator::CreateInsertProcedure1( const Metadata::ClassInfo& classInfo )
    {
        auto insertProcedure = GetInsertProcedure1( classInfo );
        WriteLine( insertProcedure );
        WriteLine( "GO" );
        WriteLine( );
    }
}