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
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"
#include <HCCStringBuilder.h>

namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql
{
    MsSqlCreateUpdateProceduresGenerator::MsSqlCreateUpdateProceduresGenerator( const MsSqlGenerator& owner )
        : Base( owner, owner.Options( ).CreateUpdateProcedures( ) )
    {
    }

    void MsSqlCreateUpdateProceduresGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                CreateUpdateStatement( classInfo );
                if ( classInfo.HasNullableReferences( ) )
                {
                    CreateUpdateStatement1( classInfo );
                    CreateUpdateStatement2( classInfo );
                }
            }
        }
        Flush( );
    }

    WideString MsSqlCreateUpdateProceduresGenerator::GetProcedureParameters( const Metadata::ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto primaryKeyType = MsSqlHelper::GetColumnType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"  @{} {}", primaryKeyName, primaryKeyType );

        if ( membersCount > 1 )
        {
            parameters.AppendLine( L"," );
        }
        else
        {
            parameters.AppendLine();
        }

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = Format( L"@{}", member.Name( ).FirstToUpper( ));
                auto variableType = MsSqlHelper::GetColumnType( member );

                parameters.Append( L"  {} {}", variableName, variableType );

                if ( memberType == Metadata::MemberInfoType::RowVersion )
                {
                    parameters.Append( L" OUTPUT" );
                }

                if ( i < (membersCount - 1) )
                {
                    parameters.AppendLine( L"," );
                }
                else
                {
                    parameters.AppendLine( );
                }

            }
        }

        return parameters.ToString( );
    }
    WideString MsSqlCreateUpdateProceduresGenerator::GetTopLevelUpdateStatement( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> statement;

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        
        auto tableName = MsSqlHelper::GetTableName( classInfo );
        const auto& ownMembers = classInfo.OwnPersistentMembers( );
        auto ownMemberCount = ownMembers.size( );

        WideString updateString;
        std::shared_ptr<Metadata::MemberInfo> rowVersion;
        for ( size_t i = 0; i < ownMemberCount; i++ )
        {
            const auto& ownMember = ownMembers[ i ];
            if ( ownMember->PrimaryKey( ) == false )
            {
                auto memberType = ownMember->Type( );
                auto variableName = ownMember->Name( ).FirstToUpper( );
                if ( memberType == Metadata::MemberInfoType::RowVersion )
                {
                    updateString += Format( L"[{}] = [{}] + 1", variableName, variableName );
                    rowVersion = ownMember;
                }
                else
                {
                    updateString += Format( L"[{}] = @{}", variableName, variableName );
                }
                if ( i < ( ownMemberCount - 1 ) )
                {
                    updateString += L',';
                }
            }
        }

        if ( rowVersion )
        {
            auto rowVersionName = rowVersion->Name( );
            statement.AppendLine( L"      UPDATE [{}] SET {}", tableName, updateString );
            statement.AppendLine( L"          OUTPUT INSERTED.[{}] INTO @MyTableVar ", rowVersionName );
            statement.AppendLine( L"          WHERE [{}] = @{} AND [{}] = @{};", primaryKeyName, primaryKeyName, rowVersionName, rowVersionName );
            statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
            statement.AppendLine( L"      IF @RowCnt = 0" );
            statement.AppendLine( L"        BEGIN" );
            statement.AppendLine( L"          RAISERROR('Row not found or concurrency error',16,1);" );
            statement.AppendLine( L"        END" );
            statement.AppendLine( L"      SET @{}  = ( SELECT TOP 1 [{}] FROM @MyTableVar);", rowVersionName, rowVersionName );
        }
        else
        {
            statement.AppendLine( L"      UPDATE [{}] SET {}", tableName, updateString );
            statement.AppendLine( L"          WHERE [{}] = @{};", primaryKeyName, primaryKeyName );
            statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
            statement.AppendLine( L"      IF @RowCnt = 0" );
            statement.AppendLine( L"        BEGIN" );
            statement.AppendLine( L"          RAISERROR('Row not found',16,1);" );
            statement.AppendLine( L"        END" );
        }

        return statement.ToString( );
    }
    WideString MsSqlCreateUpdateProceduresGenerator::GetUpdateStatement( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> statement;

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );

        auto tableName = MsSqlHelper::GetTableName( classInfo );
        const auto& ownMembers = classInfo.OwnPersistentMembers( );
        auto ownMemberCount = ownMembers.size( );

        auto updateString = Format(L"UPDATE [{}] SET ", tableName);
        auto whereString = Format( L"WHERE [{}] = @{}", primaryKeyName, primaryKeyName);

        for ( size_t i = 0; i < ownMemberCount; i++ )
        {
            const auto& ownMember = ownMembers[ i ];
            if ( ownMember->PrimaryKey( ) == false )
            {
                auto variableName = ownMember->Name( ).FirstToUpper( );
                updateString += Format( L"[{}] = @{}", variableName, variableName );
                if ( i < ( ownMemberCount - 1 ) )
                {
                    updateString += L',';
                }
            }
        }

        statement.AppendLine( L"      " + updateString );
        statement.AppendLine( L"          " + whereString );

        statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
        statement.AppendLine( L"      IF @RowCnt = 0" );
        statement.AppendLine( L"        BEGIN" );
        statement.AppendLine( L"          RAISERROR('Row not found',16,1);" );
        statement.AppendLine( L"        END" );

        return statement.ToString( );
    }
    void MsSqlCreateUpdateProceduresGenerator::CreateUpdateStatement( const Metadata::ClassInfo& classInfo )
    {
        auto procedureName = MsSqlHelper::GetUpdateProcedureName( classInfo );
        auto baseClassesAndSelf = classInfo.BaseClassesAndSelf( );

        auto rowVersion = classInfo.RowVersion( );

        WriteLine( L"CREATE OR ALTER PROCEDURE [{}]", procedureName );

        auto parameters = GetProcedureParameters( classInfo );
        WriteLine( parameters );

        auto savePointName = Format( L"SavePointU{}", classInfo.Id() );


        WriteLine( L"AS" );
        WriteLine( L"  BEGIN" );
        WriteLine( L"    DECLARE @RowCnt INT;" );
        if ( rowVersion )
        {
            WriteLine( L"    DECLARE @MyTableVar table({} INT);", rowVersion->Name() );
        }
        WriteLine( L"    DECLARE @TranCounter INT;" );
        WriteLine( L"    SET @TranCounter = @@TRANCOUNT;" );
        WriteLine( L"    IF @TranCounter > 0" );
        WriteLine( L"      SAVE TRANSACTION {};", savePointName );
        WriteLine( L"    ELSE" );
        WriteLine( L"      BEGIN TRANSACTION;" );
        WriteLine( L"    BEGIN TRY" );
        auto topLevelUpdateStatement = GetTopLevelUpdateStatement( *baseClassesAndSelf[0] );
        WriteLine( topLevelUpdateStatement );

        auto baseClassesAndSelfCount = baseClassesAndSelf.size( );

        for ( size_t i = 1; i < baseClassesAndSelfCount; i++ )
        {
            const auto& currentClassInfo = *baseClassesAndSelf[ i ];
            const auto& ownMembers = currentClassInfo.OwnPersistentMembers();
            auto ownMembersCount = ownMembers.size( );
            if ( ownMembersCount > 0 )
            {
                auto updateStatement = GetUpdateStatement( currentClassInfo );
                WriteLine( updateStatement );
            }
        }

        WriteLine( L"      IF @TranCounter = 0" );
        WriteLine( L"          COMMIT TRANSACTION;" );
        WriteLine( L"    END TRY" );
        WriteLine( L"    BEGIN CATCH" );
        WriteLine( L"        DECLARE @ErrorMessage NVARCHAR(4000);" );
        WriteLine( L"        DECLARE @ErrorSeverity INT;" );
        WriteLine( L"        DECLARE @ErrorState INT;" );
        WriteLine( L"        SELECT @ErrorMessage = ERROR_MESSAGE()," );
        WriteLine( L"            @ErrorSeverity = ERROR_SEVERITY()," );
        WriteLine( L"            @ErrorState = ERROR_STATE();" );
        WriteLine( L"        IF @TranCounter = 0" );
        WriteLine( L"          ROLLBACK TRANSACTION;" );
        WriteLine( L"        ELSE" );
        WriteLine( L"          IF XACT_STATE() <> -1" );
        WriteLine( L"            ROLLBACK TRANSACTION {};", savePointName );
        WriteLine( L"        RAISERROR(" );
        WriteLine( L"            @ErrorMessage," );
        WriteLine( L"            @ErrorSeverity," );
        WriteLine( L"            @ErrorState);" );
        WriteLine( L"    END CATCH" );
        WriteLine( L"  END" );
        WriteLine( L"GO" );
        WriteLine( );
        
    }

    WideString MsSqlCreateUpdateProceduresGenerator::GetProcedureParameters1( const Metadata::ClassInfo& classInfo )
    {
        auto members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto primaryKeyType = MsSqlHelper::GetColumnType( *primaryKey );

        StringBuilder<wchar_t> parameters;

        parameters.Append( L"  @{} {}", primaryKeyName, primaryKeyType );

        if ( membersCount > 1 )
        {
            parameters.AppendLine( L"," );
        }
        else
        {
            parameters.AppendLine( );
        }

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = Format( L"@{}", member.Name( ).FirstToUpper( ) );
                auto variableType = MsSqlHelper::GetColumnType( member );

                parameters.Append( L"  {} {}", variableName, variableType );

                if ( memberType == Metadata::MemberInfoType::RowVersion )
                {
                    parameters.Append( L" OUTPUT" );
                }

                if ( i < ( membersCount - 1 ) )
                {
                    parameters.AppendLine( L"," );
                }
                else
                {
                    parameters.AppendLine( );
                }

            }
        }

        return parameters.ToString( );
    }
    WideString MsSqlCreateUpdateProceduresGenerator::GetTopLevelUpdateStatement1( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> statement;

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );

        auto tableName = MsSqlHelper::GetTableName( classInfo );
        const auto& ownMembers = classInfo.OwnPersistentMembersExceptNullableReferences( );
        auto ownMemberCount = ownMembers.size( );

        WideString updateString;
        std::shared_ptr<Metadata::MemberInfo> rowVersion;
        for ( size_t i = 0; i < ownMemberCount; i++ )
        {
            const auto& ownMember = ownMembers[ i ];
            if ( ownMember->PrimaryKey( ) == false )
            {
                auto memberType = ownMember->Type( );
                auto variableName = ownMember->Name( ).FirstToUpper( );
                if ( memberType == Metadata::MemberInfoType::RowVersion )
                {
                    updateString += Format( L"[{}] = [{}] + 1", variableName, variableName );
                    rowVersion = ownMember;
                }
                else
                {
                    updateString += Format( L"[{}] = @{}", variableName, variableName );
                }
                if ( i < ( ownMemberCount - 1 ) )
                {
                    updateString += L',';
                }
            }
        }

        if ( rowVersion )
        {
            auto rowVersionName = rowVersion->Name( );
            statement.AppendLine( L"      UPDATE [{}] SET {}", tableName, updateString );
            statement.AppendLine( L"          OUTPUT INSERTED.[{}] INTO @MyTableVar ", rowVersionName );
            statement.AppendLine( L"          WHERE [{}] = @{} AND [{}] = @{};", primaryKeyName, primaryKeyName, rowVersionName, rowVersionName );
            statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
            statement.AppendLine( L"      IF @RowCnt = 0" );
            statement.AppendLine( L"        BEGIN" );
            statement.AppendLine( L"          RAISERROR('Row not found or concurrency error',16,1);" );
            statement.AppendLine( L"        END" );
            statement.AppendLine( L"      SET @{}  = ( SELECT TOP 1 [{}] FROM @MyTableVar);", rowVersionName, rowVersionName );
        }
        else
        {
            statement.AppendLine( L"      UPDATE [{}] SET {}", tableName, updateString );
            statement.AppendLine( L"          WHERE [{}] = @{};", primaryKeyName, primaryKeyName );
            statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
            statement.AppendLine( L"      IF @RowCnt = 0" );
            statement.AppendLine( L"        BEGIN" );
            statement.AppendLine( L"          RAISERROR('Row not found',16,1);" );
            statement.AppendLine( L"        END" );
        }

        return statement.ToString( );
    }
    WideString MsSqlCreateUpdateProceduresGenerator::GetUpdateStatement1( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> statement;

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );

        auto tableName = MsSqlHelper::GetTableName( classInfo );
        const auto& ownMembers = classInfo.OwnPersistentMembersExceptNullableReferences( );
        auto ownMemberCount = ownMembers.size( );

        auto updateString = Format( L"UPDATE [{}] SET ", tableName );
        auto whereString = Format( L"WHERE [{}] = @{}", primaryKeyName, primaryKeyName );

        for ( size_t i = 0; i < ownMemberCount; i++ )
        {
            const auto& ownMember = ownMembers[ i ];
            if ( ownMember->PrimaryKey( ) == false )
            {
                auto variableName = ownMember->Name( ).FirstToUpper( );
                updateString += Format( L"[{}] = @{}", variableName, variableName );
                if ( i < ( ownMemberCount - 1 ) )
                {
                    updateString += L',';
                }
            }
        }

        statement.AppendLine( L"      " + updateString );
        statement.AppendLine( L"          " + whereString );

        statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
        statement.AppendLine( L"      IF @RowCnt = 0" );
        statement.AppendLine( L"        BEGIN" );
        statement.AppendLine( L"          RAISERROR('Row not found',16,1);" );
        statement.AppendLine( L"        END" );

        return statement.ToString( );
    }
    void MsSqlCreateUpdateProceduresGenerator::CreateUpdateStatement1( const Metadata::ClassInfo& classInfo )
    {
        auto procedureName = MsSqlHelper::GetUpdateProcedureName1( classInfo );
        auto baseClassesAndSelf = classInfo.BaseClassesAndSelf( );

        auto rowVersion = classInfo.RowVersion( );

        WriteLine( L"CREATE OR ALTER PROCEDURE [{}]", procedureName );

        auto parameters = GetProcedureParameters1( classInfo );
        WriteLine( parameters );

        auto savePointName = Format( L"SavePointU1{}", classInfo.Id( ) );


        WriteLine( L"AS" );
        WriteLine( L"  BEGIN" );
        WriteLine( L"    DECLARE @RowCnt INT;" );
        if ( rowVersion )
        {
            WriteLine( L"    DECLARE @MyTableVar table({} INT);", rowVersion->Name( ) );
        }
        WriteLine( L"    DECLARE @TranCounter INT;" );
        WriteLine( L"    SET @TranCounter = @@TRANCOUNT;" );
        WriteLine( L"    IF @TranCounter > 0" );
        WriteLine( L"      SAVE TRANSACTION {};", savePointName );
        WriteLine( L"    ELSE" );
        WriteLine( L"      BEGIN TRANSACTION;" );
        WriteLine( L"    BEGIN TRY" );
        auto topLevelUpdateStatement = GetTopLevelUpdateStatement1( *baseClassesAndSelf[ 0 ] );
        WriteLine( topLevelUpdateStatement );

        auto baseClassesAndSelfCount = baseClassesAndSelf.size( );

        for ( size_t i = 1; i < baseClassesAndSelfCount; i++ )
        {
            const auto& currentClassInfo = *baseClassesAndSelf[ i ];
            const auto& ownMembers = currentClassInfo.OwnPersistentMembersExceptNullableReferences( );
            auto ownMembersCount = ownMembers.size( );
            if ( ownMembersCount > 0 )
            {
                auto updateStatement = GetUpdateStatement1( currentClassInfo );
                WriteLine( updateStatement );
            }
        }

        WriteLine( L"      IF @TranCounter = 0" );
        WriteLine( L"          COMMIT TRANSACTION;" );
        WriteLine( L"    END TRY" );
        WriteLine( L"    BEGIN CATCH" );
        WriteLine( L"        DECLARE @ErrorMessage NVARCHAR(4000);" );
        WriteLine( L"        DECLARE @ErrorSeverity INT;" );
        WriteLine( L"        DECLARE @ErrorState INT;" );
        WriteLine( L"        SELECT @ErrorMessage = ERROR_MESSAGE()," );
        WriteLine( L"            @ErrorSeverity = ERROR_SEVERITY()," );
        WriteLine( L"            @ErrorState = ERROR_STATE();" );
        WriteLine( L"        IF @TranCounter = 0" );
        WriteLine( L"          ROLLBACK TRANSACTION;" );
        WriteLine( L"        ELSE" );
        WriteLine( L"          IF XACT_STATE() <> -1" );
        WriteLine( L"            ROLLBACK TRANSACTION {};", savePointName );
        WriteLine( L"        RAISERROR(" );
        WriteLine( L"            @ErrorMessage," );
        WriteLine( L"            @ErrorSeverity," );
        WriteLine( L"            @ErrorState);" );
        WriteLine( L"    END CATCH" );
        WriteLine( L"  END" );
        WriteLine( L"GO" );
        WriteLine( );
    }
    
    WideString MsSqlCreateUpdateProceduresGenerator::GetProcedureParameters2( const Metadata::ClassInfo& classInfo )
    {
        auto members = classInfo.Update2Members( );
        
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto primaryKeyType = MsSqlHelper::GetColumnType( *primaryKey );

        size_t membersCount = members.size( );
        StringBuilder<wchar_t> parameters;

        parameters.Append( L"  @{} {}", primaryKeyName, primaryKeyType );

        if ( membersCount > 1 )
        {
            parameters.AppendLine( L"," );
        }
        else
        {
            parameters.AppendLine( );
        }

        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = Format( L"@{}", member.Name( ).FirstToUpper( ) );
                auto variableType = MsSqlHelper::GetColumnType( member );

                parameters.Append( L"  {} {}", variableName, variableType );

                if ( memberType == Metadata::MemberInfoType::RowVersion )
                {
                    parameters.Append( L" OUTPUT" );
                }

                if ( i < ( membersCount - 1 ) )
                {
                    parameters.AppendLine( L"," );
                }
                else
                {
                    parameters.AppendLine( );
                }

            }
        }

        return parameters.ToString( );
    }
    WideString MsSqlCreateUpdateProceduresGenerator::GetTopLevelUpdateStatement2( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> statement;

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );

        auto ownMembers = classInfo.OwnUpdate2Members( );
        auto rowVersion = classInfo.RowVersion( );

        auto tableName = MsSqlHelper::GetTableName( classInfo );

        auto ownMemberCount = ownMembers.size( );

        WideString updateString;
        
        for ( size_t i = 0; i < ownMemberCount; i++ )
        {
            const auto& ownMember = ownMembers[ i ];
            if ( ownMember->PrimaryKey( ) == false )
            {
                auto memberType = ownMember->Type( );
                auto variableName = ownMember->Name( ).FirstToUpper( );
                if ( memberType == Metadata::MemberInfoType::RowVersion )
                {
                    updateString += Format( L"[{}] = [{}] + 1", variableName, variableName );
                }
                else
                {
                    updateString += Format( L"[{}] = @{}", variableName, variableName );
                }
                if ( i < ( ownMemberCount - 1 ) )
                {
                    updateString += L',';
                }
            }
        }

        if ( rowVersion )
        {
            auto rowVersionName = rowVersion->Name( );
            statement.AppendLine( L"      UPDATE [{}] SET {}", tableName, updateString );
            statement.AppendLine( L"          OUTPUT INSERTED.[{}] INTO @MyTableVar ", rowVersionName );
            statement.AppendLine( L"          WHERE [{}] = @{} AND [{}] = @{};", primaryKeyName, primaryKeyName, rowVersionName, rowVersionName );
            statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
            statement.AppendLine( L"      IF @RowCnt = 0" );
            statement.AppendLine( L"        BEGIN" );
            statement.AppendLine( L"          RAISERROR('Row not found or concurrency error',16,1);" );
            statement.AppendLine( L"        END" );
            statement.AppendLine( L"      SET @{}  = ( SELECT TOP 1 [{}] FROM @MyTableVar);", rowVersionName, rowVersionName );
        }
        else
        {
            if ( ownMemberCount > 1 )
            {
                statement.AppendLine( L"      UPDATE [{}] SET {}", tableName, updateString );
                statement.AppendLine( L"          WHERE [{}] = @{};", primaryKeyName, primaryKeyName );
                statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
                statement.AppendLine( L"      IF @RowCnt = 0" );
                statement.AppendLine( L"        BEGIN" );
                statement.AppendLine( L"          RAISERROR('Row not found',16,1);" );
                statement.AppendLine( L"        END" );
            }
        }

        return statement.ToString( );
    }
    WideString MsSqlCreateUpdateProceduresGenerator::GetUpdateStatement2( const Metadata::ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> statement;

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );

        auto tableName = MsSqlHelper::GetTableName( classInfo );
        const auto& ownMembers = classInfo.OwnUpdate2Members( );
        auto ownMemberCount = ownMembers.size( );

        auto updateString = Format( L"UPDATE [{}] SET ", tableName );
        auto whereString = Format( L"WHERE [{}] = @{}", primaryKeyName, primaryKeyName );

        for ( size_t i = 0; i < ownMemberCount; i++ )
        {
            const auto& ownMember = ownMembers[ i ];
            if ( ownMember->PrimaryKey( ) == false )
            {
                auto variableName = ownMember->Name( ).FirstToUpper( );
                updateString += Format( L"[{}] = @{}", variableName, variableName );
                if ( i < ( ownMemberCount - 1 ) )
                {
                    updateString += L',';
                }
            }
        }

        statement.AppendLine( L"      " + updateString );
        statement.AppendLine( L"          " + whereString );

        statement.AppendLine( L"      SET @RowCnt = @@RowCount;" );
        statement.AppendLine( L"      IF @RowCnt = 0" );
        statement.AppendLine( L"        BEGIN" );
        statement.AppendLine( L"          RAISERROR('Row not found',16,1);" );
        statement.AppendLine( L"        END" );

        return statement.ToString( );
    }
    
    void MsSqlCreateUpdateProceduresGenerator::CreateUpdateStatement2( const Metadata::ClassInfo& classInfo )
    {
        auto procedureName = MsSqlHelper::GetUpdateProcedureName2( classInfo );
        auto baseClassesAndSelf = classInfo.BaseClassesAndSelf( );

        auto rowVersion = classInfo.RowVersion( );

        WriteLine( L"CREATE OR ALTER PROCEDURE [{}]", procedureName );

        auto parameters = GetProcedureParameters2( classInfo );
        WriteLine( parameters );

        auto savePointName = Format( L"SavePointU2{}", classInfo.Id( ) );


        WriteLine( L"AS" );
        WriteLine( L"  BEGIN" );
        WriteLine( L"    DECLARE @RowCnt INT;" );
        if ( rowVersion )
        {
            WriteLine( L"    DECLARE @MyTableVar table({} INT);", rowVersion->Name( ) );
        }
        WriteLine( L"    DECLARE @TranCounter INT;" );
        WriteLine( L"    SET @TranCounter = @@TRANCOUNT;" );
        WriteLine( L"    IF @TranCounter > 0" );
        WriteLine( L"      SAVE TRANSACTION {};", savePointName );
        WriteLine( L"    ELSE" );
        WriteLine( L"      BEGIN TRANSACTION;" );
        WriteLine( L"    BEGIN TRY" );
        auto topLevelUpdateStatement = GetTopLevelUpdateStatement2( *baseClassesAndSelf[ 0 ] );
        WriteLine( topLevelUpdateStatement );

        auto baseClassesAndSelfCount = baseClassesAndSelf.size( );

        for ( size_t i = 1; i < baseClassesAndSelfCount; i++ )
        {
            const auto& currentClassInfo = *baseClassesAndSelf[ i ];
            const auto& ownMembers = currentClassInfo.OwnUpdate2Members( );
            auto ownMembersCount = ownMembers.size( );
            if ( ownMembersCount > 0 )
            {
                auto updateStatement = GetUpdateStatement2( currentClassInfo );
                WriteLine( updateStatement );
            }
        }

        WriteLine( L"      IF @TranCounter = 0" );
        WriteLine( L"          COMMIT TRANSACTION;" );
        WriteLine( L"    END TRY" );
        WriteLine( L"    BEGIN CATCH" );
        WriteLine( L"        DECLARE @ErrorMessage NVARCHAR(4000);" );
        WriteLine( L"        DECLARE @ErrorSeverity INT;" );
        WriteLine( L"        DECLARE @ErrorState INT;" );
        WriteLine( L"        SELECT @ErrorMessage = ERROR_MESSAGE()," );
        WriteLine( L"            @ErrorSeverity = ERROR_SEVERITY()," );
        WriteLine( L"            @ErrorState = ERROR_STATE();" );
        WriteLine( L"        IF @TranCounter = 0" );
        WriteLine( L"          ROLLBACK TRANSACTION;" );
        WriteLine( L"        ELSE" );
        WriteLine( L"          IF XACT_STATE() <> -1" );
        WriteLine( L"            ROLLBACK TRANSACTION {};", savePointName );
        WriteLine( L"        RAISERROR(" );
        WriteLine( L"            @ErrorMessage," );
        WriteLine( L"            @ErrorSeverity," );
        WriteLine( L"            @ErrorState);" );
        WriteLine( L"    END CATCH" );
        WriteLine( L"  END" );
        WriteLine( L"GO" );
        WriteLine( );
    }

}