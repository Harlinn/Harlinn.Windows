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
#include <HCCStringBuilder.h>

namespace Harlinn::ODBC::Tool
{
    SqlServerCreateUpdateProceduresGenerator::SqlServerCreateUpdateProceduresGenerator( const SqlServerGenerator& owner )
        : Base( owner, owner.Options( ).CreateUpdateProcedures( ) )
    {
    }

    void SqlServerCreateUpdateProceduresGenerator::Run( )
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
            }
        }
        Flush( );
    }

    WideString SqlServerCreateUpdateProceduresGenerator::GetProcedureParameters( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto primaryKeyType = SqlServerHelper::GetColumnType( *primaryKey );

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
                auto variableType = SqlServerHelper::GetColumnType( member );

                parameters.Append( L"  {} {}", variableName, variableType );

                if ( memberType == MemberInfoType::RowVersion )
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
    WideString SqlServerCreateUpdateProceduresGenerator::GetTopLevelUpdateStatement( const ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> statement;

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        
        auto tableName = SqlServerHelper::GetTableName( classInfo );
        const auto& ownMembers = classInfo.OwnPersistentMembers( );
        auto ownMemberCount = ownMembers.size( );

        WideString updateString;
        std::shared_ptr<MemberInfo> rowVersion;
        for ( size_t i = 0; i < ownMemberCount; i++ )
        {
            const auto& ownMember = ownMembers[ i ];
            if ( ownMember->PrimaryKey( ) == false )
            {
                auto memberType = ownMember->Type( );
                auto variableName = ownMember->Name( ).FirstToUpper( );
                if ( memberType == MemberInfoType::RowVersion )
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
    WideString SqlServerCreateUpdateProceduresGenerator::GetUpdateStatement( const ClassInfo& classInfo )
    {
        StringBuilder<wchar_t> statement;

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );

        auto tableName = SqlServerHelper::GetTableName( classInfo );
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
    void SqlServerCreateUpdateProceduresGenerator::CreateUpdateStatement( const ClassInfo& classInfo )
    {
        auto procedureName = SqlServerHelper::GetUpdateProcedureName( classInfo );
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

}