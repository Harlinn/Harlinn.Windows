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
#include "CSharpHelper.h"

namespace Harlinn::ODBC::Tool
{
    void CSharpStoredProceduresGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Data( ).DataTypes( );
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
        WriteLine( L"using Harlinn.Common.Core.Net.IO;" );
        WriteLine( );
        WriteLine( L"using {};", dataTypesNamespace );
        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( L"    public partial class StoredProcedures" );
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
                CreateUpdate( classInfo );
                CreateDelete( classInfo );
            }
            
        }
        WriteLine( L"    }" );
        WriteLine( L"}" );

        Flush( );
    }

    void CSharpStoredProceduresGenerator::CreateInsert( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetInsertFunctionName( classInfo );
        auto functionParameters = CSharpHelper::GetInsertFunctionParameters( classInfo );
        auto storedProcedureName = SqlServerHelper::GetInsertProcedureName( classInfo );

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
    void CSharpStoredProceduresGenerator::CreateUpdate( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetUpdateFunctionName( classInfo );
        auto functionParameters = CSharpHelper::GetUpdateFunctionParameters( classInfo );
        auto storedProcedureName = SqlServerHelper::GetUpdateProcedureName( classInfo );

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
        AddInsertParameter( *primaryKey );
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                AddInsertParameter( member );
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
    void CSharpStoredProceduresGenerator::CreateDelete( const ClassInfo& classInfo )
    {
        auto functionName = CSharpHelper::GetDeleteFunctionName( classInfo );
        auto functionParameters = CSharpHelper::GetDeleteFunctionParameters( classInfo );
        WriteLine( L"        public bool {}( {} )", functionName, functionParameters );
        WriteLine( L"        {" );
        WriteLine( L"            return false;" );
        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpStoredProceduresGenerator::AddInsertParameter( const MemberInfo& memberInfo )
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
    void CSharpStoredProceduresGenerator::AddUpdateParameter( const MemberInfo& memberInfo )
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


}