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
#include "CodeGenerators/CSharp/CSharpHelper.h"
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"


namespace Harlinn::Tools::DbXGen::CodeGenerators::CSharp::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    void CSharpMsSqlStoredProceduresGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Owner( ).Data( ).DataTypes( );
        auto dataTypesNamespace = dataTypesOptions.Namespace( L"." );

        auto nspace = Options( ).Namespace( L"." );
        WriteLine( L"using System;" );
        WriteLine( L"using System.Diagnostics.CodeAnalysis;" );
        WriteLine( L"using System.IO;" );
        WriteLine( L"using System.Runtime.CompilerServices;" );
        WriteLine( );
        WriteLine( L"using Microsoft.Data.SqlClient;" );
        WriteLine( L"using Microsoft.Extensions.Logging;" );
        WriteLine( );
        WriteLine( L"using Harlinn.Common.Core.Net;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data.SqlClient;" );
        WriteLine( L"using Harlinn.Common.Core.Net.Data.Updates;" );
        WriteLine( L"using Harlinn.Common.Core.Net.IO;" );
        WriteLine( );
        WriteLine( L"using {};", dataTypesNamespace );
        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( L"    public partial class StoredProcedures : IStoredProcedures" );
        WriteLine( L"    {" );
        WriteLine( L"        private ILogger _logger;" );
        WriteLine( L"        SqlConnection _connection;" );
        WriteLine( );
        WriteLine( L"        public StoredProcedures( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlConnection connection )" );
        WriteLine( L"        {" );
        WriteLine( L"            _logger = loggerFactory.CreateLogger<StoredProcedures>( );" );
        WriteLine( L"            _connection = connection;" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        protected void LogException( [ DisallowNull ] Exception exc, [ CallerMemberName ] string methodName = \"\" )");
        WriteLine( L"        {");
        WriteLine( L"            string exceptionMessageText = exc.Message;");
        WriteLine( L"            string messageText = string.Format( \"Exception in {0} - {1}\", methodName, exceptionMessageText );");
        WriteLine( );
        WriteLine( L"            _logger.LogError( exc, messageText );");
        WriteLine( L"#if DEBUG");
        WriteLine( L"            if ( System.Diagnostics.Debugger.IsAttached )");
        WriteLine( L"            {");
        WriteLine( L"                System.Diagnostics.Debugger.Log( 1, \"Exception\", messageText );");
        WriteLine( L"                System.Diagnostics.Debugger.Break( );");
        WriteLine( L"            }");
        WriteLine( L"#endif");
        WriteLine( L"        }" );
        WriteLine( );
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
            }
            
        }
        CreateInsertDataObject( );
        CreateUpdateDataObject( );
        CreateDeleteDataObject( );
        CreateMergeDataObject( );
        WriteLine( L"    }" );
        WriteLine( L"}" );

        Flush( );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateInsert( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetInsertFunctionName( classInfo );
        auto functionParameters = CSharpHelper::GetInsertFunctionParameters( classInfo );
        auto storedProcedureName = MsSqlHelper::GetInsertProcedureName( classInfo );

        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyArgumentName = CSharpHelper::GetInputArgumentName( *primaryKey );
        auto primaryKeySqlCommandParameterName = primaryKey->Name().FirstToLower() + L"Parameter";

        WriteLine( L"        public bool {}( {} )", functionName, functionParameters );
        WriteLine( L"        {" );
        WriteLine( L"            bool result = false;" );
        WriteLine( L"            try");
        WriteLine( L"            {");
        WriteLine( L"                var sqlCommand = _connection.CreateCommand( );");
        WriteLine( L"                sqlCommand.CommandText = \"{}\";", storedProcedureName );
        WriteLine( L"                sqlCommand.CommandType = System.Data.CommandType.StoredProcedure;");
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;");
        AddInsertParameter( *primaryKey );
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    AddInsertParameter( member );
                }
            }
        }
        WriteLine( L"                int rowsAffected = sqlCommand.ExecuteNonQuery( );");
        WriteLine( L"                if(rowsAffected > 0)" );
        WriteLine( L"                {" );
        if ( primaryKey->Type( ) == MemberInfoType::Guid )
        {
            WriteLine( L"                    {} = (Guid){}.Value;", primaryKeyArgumentName, primaryKeySqlCommandParameterName );
        }
        else
        {
            WriteLine( L"                    {} = (long){}.Value;", primaryKeyArgumentName, primaryKeySqlCommandParameterName );
        }
        WriteLine( L"                    result = true;" );
        WriteLine( L"                }" );
        WriteLine( L"            }");
        WriteLine( L"            catch ( Exception exc )");
        WriteLine( L"            {");
        WriteLine( L"                LogException( exc );");
        WriteLine( L"                throw;");
        WriteLine( L"            }");
        WriteLine( L"            return result;" );
        
        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateInsert1( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetInsertFunctionName1( classInfo );
        auto functionParameters = CSharpHelper::GetInsertFunctionParameters1( classInfo );
        auto storedProcedureName = MsSqlHelper::GetInsertProcedureName1( classInfo );

        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyArgumentName = CSharpHelper::GetInputArgumentName( *primaryKey );
        auto primaryKeySqlCommandParameterName = primaryKey->Name( ).FirstToLower( ) + L"Parameter";

        WriteLine( L"        public bool {}( {} )", functionName, functionParameters );
        WriteLine( L"        {" );
        WriteLine( L"            bool result = false;" );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlCommand = _connection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = \"{}\";", storedProcedureName );
        WriteLine( L"                sqlCommand.CommandType = System.Data.CommandType.StoredProcedure;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        AddInsertParameter( *primaryKey );
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    AddInsertParameter( member );
                }
            }
        }
        WriteLine( L"                int rowsAffected = sqlCommand.ExecuteNonQuery( );" );
        WriteLine( L"                if(rowsAffected > 0)" );
        WriteLine( L"                {" );
        if ( primaryKey->Type( ) == MemberInfoType::Guid )
        {
            WriteLine( L"                    {} = (Guid){}.Value;", primaryKeyArgumentName, primaryKeySqlCommandParameterName );
        }
        else
        {
            WriteLine( L"                    {} = (long){}.Value;", primaryKeyArgumentName, primaryKeySqlCommandParameterName );
        }
        WriteLine( L"                    result = true;" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );

        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateInsertObject( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetInsertFunctionName( classInfo );
        auto functionParameters = CSharpHelper::GetInsertFunctionCallParameters( classInfo );

        auto dataTypeName = CSharpHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );
        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );

        WriteLine( L"        public bool {}( {} {} )", functionName, dataTypeName, argumentName );
        WriteLine( L"        {" );
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto memberType = member.Type( );
            if ( memberType != MemberInfoType::RowVersion )
            {
                auto variableType = CSharpHelper::GetMemberFieldType( member );
                auto variableName = CSharpHelper::GetInputArgumentName( member );
                auto propertyName = member.Name( ).FirstToUpper( );
                WriteLine( L"            {} {} = {}.{};", variableType, variableName, argumentName, propertyName );
            }
        }
        
        WriteLine( L"            var result = {}( {} );", functionName, functionParameters );
        WriteLine( L"            if( result )" );
        WriteLine( L"            {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyVariableName = CSharpHelper::GetInputArgumentName( *primaryKey );
        WriteLine( L"                {}.Id = {};", argumentName, primaryKeyVariableName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"                {}.{} = 0;", argumentName, propertyName );
        }
        WriteLine( L"                {}.ObjectState = ObjectState.Stored;", argumentName );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateInsertObject1( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetInsertFunctionName1( classInfo );
        auto functionParameters = CSharpHelper::GetInsertFunctionCallParameters1( classInfo );

        auto dataTypeName = CSharpHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        auto memberCount = members.size( );

        WriteLine( L"        public bool {}( {} {} )", functionName, dataTypeName, argumentName );
        WriteLine( L"        {" );
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto memberType = member.Type( );
            if ( memberType != MemberInfoType::RowVersion )
            {
                auto variableType = CSharpHelper::GetMemberFieldType( member );
                auto variableName = CSharpHelper::GetInputArgumentName( member );
                auto propertyName = member.Name( ).FirstToUpper( );
                WriteLine( L"            {} {} = {}.{};", variableType, variableName, argumentName, propertyName );
            }
        }

        WriteLine( L"            var result = {}( {} );", functionName, functionParameters );
        WriteLine( L"            if( result )" );
        WriteLine( L"            {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyVariableName = CSharpHelper::GetInputArgumentName( *primaryKey );
        WriteLine( L"                {}.Id = {};", argumentName, primaryKeyVariableName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"                {}.{} = 0;", argumentName, propertyName );
        }
        WriteLine( L"                {}.ObjectState = ObjectState.Stored;", argumentName );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateUpdate( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName( classInfo );
        auto functionParameters = CSharpHelper::GetUpdateFunctionParameters( classInfo );
        auto storedProcedureName = MsSqlHelper::GetUpdateProcedureName( classInfo );

        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        

        WriteLine( L"        public bool {}( {} )", functionName, functionParameters );
        WriteLine( L"        {" );
        WriteLine( L"            bool result = false;" );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlCommand = _connection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = \"{}\";", storedProcedureName );
        WriteLine( L"                sqlCommand.CommandType = System.Data.CommandType.StoredProcedure;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        AddUpdateParameter( *primaryKey );
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                AddUpdateParameter( member );
            }
        }
        WriteLine( L"                int rowsAffected = sqlCommand.ExecuteNonQuery( );" );
        WriteLine( L"                if(rowsAffected > 0)" );
        WriteLine( L"                {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionArgumentName = CSharpHelper::GetInputArgumentName( *rowVersion );
            auto rowVersionSqlCommandParameterName = rowVersion->Name( ).FirstToLower( ) + L"Parameter";
            WriteLine( L"                    {} = (long){}.Value;", rowVersionArgumentName, rowVersionSqlCommandParameterName );
        }
        WriteLine( L"                    result = true;" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );

        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateUpdate1( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName1( classInfo );
        auto functionParameters = CSharpHelper::GetUpdateFunctionParameters1( classInfo );
        auto storedProcedureName = MsSqlHelper::GetUpdateProcedureName1( classInfo );

        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );


        WriteLine( L"        public bool {}( {} )", functionName, functionParameters );
        WriteLine( L"        {" );
        WriteLine( L"            bool result = false;" );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlCommand = _connection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = \"{}\";", storedProcedureName );
        WriteLine( L"                sqlCommand.CommandType = System.Data.CommandType.StoredProcedure;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        AddUpdateParameter( *primaryKey );
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                AddUpdateParameter( member );
            }
        }
        WriteLine( L"                int rowsAffected = sqlCommand.ExecuteNonQuery( );" );
        WriteLine( L"                if(rowsAffected > 0)" );
        WriteLine( L"                {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionArgumentName = CSharpHelper::GetInputArgumentName( *rowVersion );
            auto rowVersionSqlCommandParameterName = rowVersion->Name( ).FirstToLower( ) + L"Parameter";
            WriteLine( L"                    {} = (long){}.Value;", rowVersionArgumentName, rowVersionSqlCommandParameterName );
        }
        WriteLine( L"                    result = true;" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );

        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateUpdate2( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName2( classInfo );
        auto functionParameters = CSharpHelper::GetUpdateFunctionParameters2( classInfo );
        auto storedProcedureName = MsSqlHelper::GetUpdateProcedureName2( classInfo );

        const auto& members = classInfo.Update2Members( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );


        WriteLine( L"        public bool {}( {} )", functionName, functionParameters );
        WriteLine( L"        {" );
        WriteLine( L"            bool result = false;" );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlCommand = _connection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = \"{}\";", storedProcedureName );
        WriteLine( L"                sqlCommand.CommandType = System.Data.CommandType.StoredProcedure;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        AddUpdateParameter( *primaryKey );
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                AddUpdateParameter( member );
            }
        }
        WriteLine( L"                int rowsAffected = sqlCommand.ExecuteNonQuery( );" );
        WriteLine( L"                if(rowsAffected > 0)" );
        WriteLine( L"                {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionArgumentName = CSharpHelper::GetInputArgumentName( *rowVersion );
            auto rowVersionSqlCommandParameterName = rowVersion->Name( ).FirstToLower( ) + L"Parameter";
            WriteLine( L"                    {} = (long){}.Value;", rowVersionArgumentName, rowVersionSqlCommandParameterName );
        }
        WriteLine( L"                    result = true;" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );

        WriteLine( L"        }" );
        WriteLine( );
    }


    void CSharpMsSqlStoredProceduresGenerator::CreateUpdateObject( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName( classInfo );
        auto functionParameters = CSharpHelper::GetUpdateFunctionCallParameters( classInfo );
        
        auto dataTypeName = CSharpHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );

        WriteLine( L"        public bool {}( {} {} )", functionName, dataTypeName, argumentName );
        WriteLine( L"        {" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = CSharpHelper::GetMemberFieldType( member );
            auto variableName = CSharpHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"            {} {} = {}.{};", variableType, variableName, argumentName, propertyName );
        }

        WriteLine( L"            var result = {}( {} );", functionName, functionParameters );
        WriteLine( L"            if( result )" );
        WriteLine( L"            {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionVariableName = CSharpHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"                {}.{} = {};", argumentName, propertyName, rowVersionVariableName );
        }
        WriteLine( L"                {}.ObjectState = ObjectState.Stored;", argumentName );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );

        WriteLine( L"        }" );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateUpdateObject1( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName1( classInfo );
        auto functionParameters = CSharpHelper::GetUpdateFunctionCallParameters1( classInfo );

        auto dataTypeName = CSharpHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        auto memberCount = members.size( );

        WriteLine( L"        public bool {}( {} {} )", functionName, dataTypeName, argumentName );
        WriteLine( L"        {" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = CSharpHelper::GetMemberFieldType( member );
            auto variableName = CSharpHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"            {} {} = {}.{};", variableType, variableName, argumentName, propertyName );
        }

        WriteLine( L"            var result = {}( {} );", functionName, functionParameters );
        WriteLine( L"            if( result )" );
        WriteLine( L"            {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionVariableName = CSharpHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"                {}.{} = {};", argumentName, propertyName, rowVersionVariableName );
        }
        WriteLine( L"                {}.ObjectState = ObjectState.Stored;", argumentName );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );

        WriteLine( L"        }" );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateUpdateObject2( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName2( classInfo );
        auto functionParameters = CSharpHelper::GetUpdateFunctionCallParameters2( classInfo );

        auto dataTypeName = CSharpHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.Update2Members( );
        auto memberCount = members.size( );

        WriteLine( L"        public bool {}( {} {} )", functionName, dataTypeName, argumentName );
        WriteLine( L"        {" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = CSharpHelper::GetMemberFieldType( member );
            auto variableName = CSharpHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"            {} {} = {}.{};", variableType, variableName, argumentName, propertyName );
        }

        WriteLine( L"            var result = {}( {} );", functionName, functionParameters );
        WriteLine( L"            if( result )" );
        WriteLine( L"            {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionVariableName = CSharpHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"                {}.{} = {};", argumentName, propertyName, rowVersionVariableName );
        }
        WriteLine( L"                {}.ObjectState = ObjectState.Stored;", argumentName );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );

        WriteLine( L"        }" );
    }


    void CSharpMsSqlStoredProceduresGenerator::CreateDelete( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetDeleteFunctionName( classInfo );
        auto functionParameters = CSharpHelper::GetDeleteFunctionParameters( classInfo );
        auto storedProcedureName = MsSqlHelper::GetDeleteProcedureName( classInfo );

        auto primaryKey = classInfo.PrimaryKey( );


        WriteLine( L"        public bool {}( {} )", functionName, functionParameters );
        WriteLine( L"        {" );
        WriteLine( L"            bool result = false;" );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                int rowCountValue = 0;" );
        WriteLine( L"                var sqlCommand = _connection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = \"{}\";", storedProcedureName );
        WriteLine( L"                sqlCommand.CommandType = System.Data.CommandType.StoredProcedure;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        AddDeleteParameter( *primaryKey );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            AddDeleteParameter( *rowVersion );
        }
        WriteLine( L"                var rowCountParameter = sqlCommandParameters.AddInt32( \"@RowCount\", rowCountValue, System.Data.ParameterDirection.Output );");
        
        WriteLine( L"                int rowsAffected = sqlCommand.ExecuteNonQuery( );" );
        WriteLine( L"                if(rowsAffected > 0)" );
        WriteLine( L"                {" );
        WriteLine( L"                    result = true;" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );

        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateDeleteObject( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetDeleteFunctionName( classInfo );
        auto dataTypeName = CSharpHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        WriteLine( L"        public bool {}( {} {} )", functionName, dataTypeName, argumentName );
        WriteLine( L"        {" );
        WriteLine( L"            var id = {}.Id;", argumentName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionVariableName = CSharpHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"            var {} = {}.{};", rowVersionVariableName, argumentName, propertyName );
            WriteLine( L"            var result = {}( id, {} );", functionName, rowVersionVariableName );
        }
        else
        {
            WriteLine( L"            var result = {}( id );", functionName );
        }
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
    }

    void CSharpMsSqlStoredProceduresGenerator::AddInsertParameter( const MemberInfo& memberInfo )
    {
        auto sqlCommandParametersAddFunctionName = CSharpHelper::GetSqlCommandParametersAddFunctionName( memberInfo );
        auto storedProcedureArgumentName = Format(L"@{}", memberInfo.Name().FirstToUpper() );
        auto parameterVariableName = memberInfo.Name( ).FirstToLower( ) + L"Parameter";
        auto argumentName = CSharpHelper::GetInputArgumentName( memberInfo );
        if ( memberInfo.PrimaryKey( ) )
        {
            WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, System.Data.ParameterDirection.InputOutput );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
        }
        else
        {
            auto memberType = memberInfo.Type( );
            if ( memberType == MemberInfoType::String )
            {
                const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( memberInfo );
                if ( stringMemberInfo.Size( ) <= 4000 )
                {
                    WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName, stringMemberInfo.Size( ) );
                }
                else
                {
                    WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
                }
            }
            else if ( memberType == MemberInfoType::Binary )
            {
                const auto& binaryMemberInfo = static_cast< const BinaryMemberInfo& >( memberInfo );
                if ( binaryMemberInfo.Size( ) <= 8000 )
                {
                    WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName, binaryMemberInfo.Size( ) );
                }
                else
                {
                    WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
                }
            }
            else
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
            }
        }
    }
    void CSharpMsSqlStoredProceduresGenerator::AddUpdateParameter( const MemberInfo& memberInfo )
    {
        auto sqlCommandParametersAddFunctionName = CSharpHelper::GetSqlCommandParametersAddFunctionName( memberInfo );
        auto storedProcedureArgumentName = Format( L"@{}", memberInfo.Name( ).FirstToUpper( ) );
        auto parameterVariableName = memberInfo.Name( ).FirstToLower( ) + L"Parameter";
        auto argumentName = CSharpHelper::GetInputArgumentName( memberInfo );
        auto memberType = memberInfo.Type( );
        if ( memberType == MemberInfoType::String )
        {
            const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( memberInfo );
            if ( stringMemberInfo.Size( ) <= 4000 )
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName, stringMemberInfo.Size( ) );
            }
            else
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
            }
        }
        else if ( memberType == MemberInfoType::Binary )
        {
            const auto& binaryMemberInfo = static_cast< const BinaryMemberInfo& >( memberInfo );
            if ( binaryMemberInfo.Size( ) <= 8000 )
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName, binaryMemberInfo.Size( ) );
            }
            else
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
            }
        }
        else if ( memberType == MemberInfoType::RowVersion )
        {
            WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, System.Data.ParameterDirection.InputOutput );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
        }
        else
        {
            WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
        }
    }

    void CSharpMsSqlStoredProceduresGenerator::AddDeleteParameter( const MemberInfo& memberInfo )
    {
        auto sqlCommandParametersAddFunctionName = CSharpHelper::GetSqlCommandParametersAddFunctionName( memberInfo );
        auto storedProcedureArgumentName = Format( L"@{}", memberInfo.Name( ).FirstToUpper( ) );
        auto parameterVariableName = memberInfo.Name( ).FirstToLower( ) + L"Parameter";
        auto argumentName = CSharpHelper::GetInputArgumentName( memberInfo );
        auto memberType = memberInfo.Type( );
        if ( memberType == MemberInfoType::String )
        {
            const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( memberInfo );
            if ( stringMemberInfo.Size( ) <= 4000 )
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName, stringMemberInfo.Size( ) );
            }
            else
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
            }
        }
        else if ( memberType == MemberInfoType::Binary )
        {
            const auto& binaryMemberInfo = static_cast< const BinaryMemberInfo& >( memberInfo );
            if ( binaryMemberInfo.Size( ) <= 8000 )
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName, binaryMemberInfo.Size( ) );
            }
            else
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
            }
        }
        else
        {
            WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, storedProcedureArgumentName, argumentName );
        }
    }

    void CSharpMsSqlStoredProceduresGenerator::CreateInsertDataObject( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"        public bool Insert( BaseDataGuid<Kind> dataObject )");
        WriteLine( L"        {");
        WriteLine( L"            bool result = false;");
        WriteLine( L"            var kind = dataObject.GetObjectType( );");
        WriteLine( L"            switch ( kind )");
        WriteLine( L"            {");
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto functionName = CSharpHelper::GetInsertFunctionName( classInfo );
                auto dataClassName = CSharpHelper::GetDataType( classInfo );
                WriteLine( L"                case Types.Kind.{}:", classInfo.Name().FirstToUpper() );
                WriteLine( L"                {" );
                WriteLine( L"                    result = {}( ({})dataObject );", functionName, dataClassName );
                WriteLine( L"                }" );
                WriteLine( L"                break;" );
            }
        }
        WriteLine( L"            }" );
        WriteLine( L"            return result;");
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpMsSqlStoredProceduresGenerator::CreateUpdateDataObject( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"        public bool Update( BaseDataGuid<Kind> dataObject )");
        WriteLine( L"        {");
        WriteLine( L"            bool result = false;");
        WriteLine( L"            var kind = dataObject.GetObjectType( );" );
        WriteLine( L"            switch ( kind )" );
        WriteLine( L"            {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto functionName = CSharpHelper::GetUpdateFunctionName( classInfo );
                auto dataClassName = CSharpHelper::GetDataType( classInfo );
                WriteLine( L"                case Types.Kind.{}:", classInfo.Name( ).FirstToUpper( ) );
                WriteLine( L"                {" );
                WriteLine( L"                    result = {}( ({})dataObject );", functionName, dataClassName );
                WriteLine( L"                }" );
                WriteLine( L"                break;" );
            }
        }
        WriteLine( L"            }" );
        WriteLine( L"            return result;");
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpMsSqlStoredProceduresGenerator::CreateDeleteDataObject( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"        public bool Delete( BaseDataGuid<Kind> dataObject )");
        WriteLine( L"        {");
        WriteLine( L"            bool result = false;");
        WriteLine( L"            var kind = dataObject.GetObjectType( );" );
        WriteLine( L"            switch ( kind )" );
        WriteLine( L"            {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto functionName = CSharpHelper::GetDeleteFunctionName( classInfo );
                auto dataClassName = CSharpHelper::GetDataType( classInfo );
                WriteLine( L"                case Types.Kind.{}:", classInfo.Name( ).FirstToUpper( ) );
                WriteLine( L"                {" );
                WriteLine( L"                    result = {}( ({})dataObject );", functionName, dataClassName );
                WriteLine( L"                }" );
                WriteLine( L"                break;" );
            }
        }
        WriteLine( L"            }" );
        WriteLine( L"            return result;");
        WriteLine( L"        }" );
        WriteLine( );
    }
    void CSharpMsSqlStoredProceduresGenerator::CreateMergeDataObject( )
    {
        WriteLine( L"        public bool Merge( BaseDataGuid<Kind> dataObject )");
        WriteLine( L"        {");
        WriteLine( L"            bool result = false;");
        WriteLine( L"            var objectState = dataObject.ObjectState;");
        WriteLine( L"            switch ( objectState )");
        WriteLine( L"            {");
        WriteLine( L"                case ObjectState.New:");
        WriteLine( L"                {");
        WriteLine( L"                    result = Insert( dataObject );");
        WriteLine( L"                }");
        WriteLine( L"                break;");
        WriteLine( L"                case ObjectState.Changed:");
        WriteLine( L"                {");
        WriteLine( L"                    result = Update( dataObject );");
        WriteLine( L"                }");
        WriteLine( L"                break;");
        WriteLine( L"                case ObjectState.Deleted:");
        WriteLine( L"                {");
        WriteLine( L"                    result = Delete( dataObject );");
        WriteLine( L"                }");
        WriteLine( L"                break;");
        WriteLine( L"            }");
        WriteLine( L"            return result;");
        WriteLine( L"        }" );
        WriteLine( );
    }


}