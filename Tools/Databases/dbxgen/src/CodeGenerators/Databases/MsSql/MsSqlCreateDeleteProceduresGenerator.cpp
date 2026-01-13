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

namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql
{
    MsSqlCreateDeleteProceduresGenerator::MsSqlCreateDeleteProceduresGenerator( const MsSqlGenerator& owner )
        : Base( owner, owner.Options( ).CreateDeleteProcedures( ) )
    {
    }

    void MsSqlCreateDeleteProceduresGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        auto classCount = classes.size( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                CreateDeleteProcedure( classInfo );
            }
        }
        Flush( );
    }

    WideString MsSqlCreateDeleteProceduresGenerator::GetDeleteStatement( const Metadata::ClassInfo& classInfo )
    {
        const auto& ownMembers = classInfo.OwnPersistentMembers( );
        auto tableName = MsSqlHelper::GetTableName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto rowVersion = classInfo.RowVersion( );


        WideString deleteString;
        if ( classInfo.IsTopLevel() && rowVersion != nullptr )
        {
            auto rowVersionName = rowVersion->Name( );
            deleteString = Format(L"      DELETE FROM [dbo].[{}] WHERE [{}] = @{} AND [{}] = @{};", tableName, primaryKeyName, primaryKeyName, rowVersionName, rowVersionName );
        }
        else
        {
            deleteString = Format( L"      DELETE FROM [dbo].[{}] WHERE [{}] = @{};", tableName, primaryKeyName, primaryKeyName);
        }
        return deleteString;
    }
    void MsSqlCreateDeleteProceduresGenerator::CreateDeleteProcedure( const Metadata::ClassInfo& classInfo )
    {
        auto procedureName = MsSqlHelper::GetDeleteProcedureName( classInfo );

        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = primaryKey->Name( );
        auto primaryKeyType = MsSqlHelper::GetColumnType( *primaryKey );
        
        auto rowVersion = classInfo.RowVersion( );


        WriteLine( L"CREATE OR ALTER PROCEDURE [{}]", procedureName );

        if ( rowVersion )
        {
            auto rowVersionName = rowVersion->Name( );
            auto rowVersionType = MsSqlHelper::GetColumnType( *rowVersion );
            auto parameters = Format(L"  @{} {},\r\n  @{} {},\r\n  @RowCount int OUTPUT", primaryKeyName, primaryKeyType, rowVersionName, rowVersionType );
            WriteLine( parameters );
        }
        else
        {
            auto parameters = Format(L"  @{} {},\r\n  @RowCount int OUTPUT", primaryKeyName, primaryKeyType);
            WriteLine( parameters );
        }

        auto savePointName = Format( L"SavePoint{}", classInfo.Id( ) );


        WriteLine( L"AS" );
        WriteLine( L"  BEGIN" );
        WriteLine( L"    DECLARE @TranCounter INT;" );
        WriteLine( L"    SET @TranCounter = @@TRANCOUNT;" );
        WriteLine( L"    IF @TranCounter > 0" );
        WriteLine( L"      SAVE TRANSACTION {};", savePointName );
        WriteLine( L"    ELSE" );
        WriteLine( L"      BEGIN TRANSACTION;" );
        WriteLine( L"    BEGIN TRY" );

        auto baseClassesAndSelf = classInfo.BaseClassesAndSelf( );
        std::reverse( baseClassesAndSelf.begin( ), baseClassesAndSelf.end( ) );
        auto baseClassesAndSelfCount = baseClassesAndSelf.size( );
        

        for ( int i = 0; i < baseClassesAndSelfCount; i++ )
        {
            auto currentClassInfo = baseClassesAndSelf[ i ];
            auto deleteStatement = GetDeleteStatement( *currentClassInfo );
            WriteLine( deleteStatement );
            if ( i == 0 )
            {
                WriteLine( L"      SET @RowCount = @@ROWCOUNT;" );
                WriteLine( L"      IF @RowCount = 0" );
                WriteLine( L"      BEGIN" );
                WriteLine( L"        IF @TranCounter = 0" );
                WriteLine( L"          ROLLBACK TRANSACTION;" );
                WriteLine( L"        ELSE" );
                WriteLine( L"          IF XACT_STATE() <> -1" );
                WriteLine( L"            ROLLBACK TRANSACTION {};", savePointName );
                WriteLine( L"        RETURN" );
                WriteLine( L"      END" );
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


        WriteLine( "GO" );
        WriteLine( );
    }

}