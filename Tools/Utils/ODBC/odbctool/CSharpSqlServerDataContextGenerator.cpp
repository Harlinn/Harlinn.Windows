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
#include <HCCStringBuilder.h>

namespace Harlinn::ODBC::Tool
{
    void CSharpSqlServerDataContextGenerator::Run( )
    {
        functions_.clear( );

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
        WriteLine( L"using System.Text;" );
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

        WriteLine( L"    public class SqlServerDataContext : IDataContext" );
        WriteLine( L"    {" );

        WriteLine( L"        ILoggerFactory _loggerFactory;" );
        WriteLine( L"        ILogger _logger;");
        WriteLine( L"        SqlConnection? _sqlConnection;");
        WriteLine( L"        bool _ownsConnection;");
        WriteLine( L"        bool _isDisposed = false;");
        WriteLine( L"        StoredProcedures _storedProcedures;" );
        WriteLine( );
        WriteLine( L"        public SqlServerDataContext( [DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlConnection sqlConnection, bool ownsConnection = true )");
        WriteLine( L"        {");
        WriteLine( L"            _loggerFactory = loggerFactory;");
        WriteLine( L"            _logger = loggerFactory.CreateLogger<DataReaderWrapper>( );");
        WriteLine( L"            _sqlConnection = sqlConnection;");
        WriteLine( L"            _ownsConnection = ownsConnection;");
        WriteLine( L"            _storedProcedures = new StoredProcedures( loggerFactory, sqlConnection );" );
        WriteLine( L"        }");
        WriteLine( );
        WriteLine( L"        #region IDisposable Members");
        WriteLine( L"        public void Dispose( )");
        WriteLine( L"        {");
        WriteLine( L"            try");
        WriteLine( L"            {");
        WriteLine( L"                if ( !_isDisposed )");
        WriteLine( L"                {");
        WriteLine( L"                    _isDisposed = true;");
        WriteLine( );
        WriteLine( L"                    OnDispose( );");
        WriteLine( L"                }");
        WriteLine( L"            }");
        WriteLine( L"            catch ( Exception exc )");
        WriteLine( L"            {");
        WriteLine( L"                LogException( exc );");
        WriteLine( L"                throw;");
        WriteLine( L"            }");
        WriteLine( L"        }");
        WriteLine( L"        protected virtual void OnDispose( )");
        WriteLine( L"        {");
        WriteLine( L"            try");
        WriteLine( L"            {");
        WriteLine( L"                DisposeConnection( );");
        WriteLine( L"            }");
        WriteLine( L"            catch ( Exception exc )");
        WriteLine( L"            {");
        WriteLine( L"                LogException( exc );");
        WriteLine( L"                throw;");
        WriteLine( L"            }");
        WriteLine( L"        }");
        WriteLine( L"        protected virtual void DisposeConnection( )");
        WriteLine( L"        {");
        WriteLine( L"            try");
        WriteLine( L"            {");
        WriteLine( L"                if ( ( _sqlConnection != null ) && ( _ownsConnection ) )");
        WriteLine( L"                {");
        WriteLine( L"                    SqlConnection sqlConnection = _sqlConnection;");
        WriteLine( L"                    _sqlConnection = null;");
        WriteLine( L"                    sqlConnection.Dispose( );");
        WriteLine( L"                }");
        WriteLine( L"            }");
        WriteLine( L"            catch ( Exception exc )");
        WriteLine( L"            {");
        WriteLine( L"                LogException( exc );");
        WriteLine( L"                throw;");
        WriteLine( L"            }");
        WriteLine( L"        }");
        WriteLine( L"        #endregion" );
        WriteLine( );
        WriteLine( L"        protected void LogException([DisallowNull] Exception exc, [CallerMemberName] string methodName = \"\" )" );
        WriteLine( L"        {" );
        WriteLine( L"            string exceptionMessageText = exc.Message;" );
        WriteLine( L"            string messageText = string.Format( \"Exception in{ 0 } - {1}\", methodName, exceptionMessageText );" );
        WriteLine( );
        WriteLine( L"            _logger.LogError( exc, messageText );" );
        WriteLine( L"#if DEBUG" );
        WriteLine( L"            if ( System.Diagnostics.Debugger.IsAttached )" );
        WriteLine( L"            {" );
        WriteLine( L"                System.Diagnostics.Debugger.Log( 1, \"Exception\", messageText );" );
        WriteLine( L"                System.Diagnostics.Debugger.Break( );" );
        WriteLine( L"            }" );
        WriteLine( L"#endif" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        SqlConnection GetSqlConnection( )");
        WriteLine( L"        {");
        WriteLine( L"            return _sqlConnection;");
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public bool Merge( BaseDataGuid<Kind> dataObject )");
        WriteLine( L"        {");
        WriteLine( L"            return _storedProcedures.Merge( dataObject );");
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public bool Insert( BaseDataGuid<Kind> dataObject )");
        WriteLine( L"        {");
        WriteLine( L"            return _storedProcedures.Insert( dataObject );");
        WriteLine( L"        }");
        WriteLine( );
        WriteLine( L"        public bool Update( BaseDataGuid<Kind> dataObject )");
        WriteLine( L"        {");
        WriteLine( L"            return _storedProcedures.Update( dataObject );");
        WriteLine( L"        }");
        WriteLine( );
        WriteLine( L"        public bool Delete( BaseDataGuid<Kind> dataObject )");
        WriteLine( L"        {");
        WriteLine( L"            return _storedProcedures.Delete( dataObject );");
        WriteLine( L"        }" );
        WriteLine( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateMembers( classInfo );
        }
        WriteLine( L"    }" );

        WriteLine( L"}" );

        Flush( );
    }

    void CSharpSqlServerDataContextGenerator::CreateMembers( const ClassInfo& classInfo )
    {
        WriteLine( L"        // ---------------------------------------------------------------------" );
        WriteLine( L"        // {} queries", classInfo.Name( ) );
        WriteLine( L"        // ---------------------------------------------------------------------" );
        CreateGetById( classInfo );
        CreateGetAll( classInfo );
        CreateGetByIndex( classInfo );
    }
    void CSharpSqlServerDataContextGenerator::CreateGetById( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIdFunctionName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyType = CSharpHelper::GetInputArgumentType( *primaryKey );
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        functions_.insert( functionName );

        WriteLine( L"        public {} {}DataReader( {} id )", dataReaderName, functionName, primaryKeyType );
        WriteLine( L"        {" );
        WriteLine( L"            const string sql = {}.BaseQuery + \"WHERE \" + {}.ViewAliasName + \".[{}] = @id\"; ", dataReaderName, dataReaderName, primaryKey->Name( ).FirstToUpper( ) );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlConnection = GetSqlConnection( );" );
        WriteLine( L"                var sqlCommand = sqlConnection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = sql;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        WriteLine( L"                sqlCommandParameters.AddGuid( \"@id\", id );" );
        WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleRow );" );
        WriteLine( L"                var {} = new {}( _loggerFactory, sqlDataReader );", dataReaderVariableName, dataReaderName );
        WriteLine( L"                return {};", dataReaderVariableName );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );

        WriteLine( L"        public {}? {}( {} id )", className, functionName, primaryKeyType );
        WriteLine( L"        {" );
        WriteLine( L"            var {} = {}DataReader( id );", dataReaderVariableName, functionName );
        WriteLine( L"            using ( {} )", dataReaderVariableName );
        WriteLine( L"            {");
        WriteLine( L"                if ( {}.Read( ) )", dataReaderVariableName );
        WriteLine( L"                {");
        WriteLine( L"                    var result = {}.GetDataObject( );", dataReaderVariableName );
        WriteLine( L"                    return result;");
        WriteLine( L"                }");
        WriteLine( L"            }");
        WriteLine( L"            return null;" );
        WriteLine( L"        }" );
        WriteLine( );

        WriteLine( L"        public void {}( {} id, Stream destinationStream )", functionName, primaryKeyType );
        WriteLine( L"        {" );
        WriteLine( L"            var destinationWriter = new BinaryWriter( destinationStream, Encoding.Unicode );" );
        WriteLine( L"            using( destinationWriter )" );
        WriteLine( L"            {" );
        WriteLine( L"                var {} = {}DataReader( id );", dataReaderVariableName, functionName );
        WriteLine( L"                using ( {} )", dataReaderVariableName );
        WriteLine( L"                {" );
        WriteLine( L"                    if ( {}.Read( ) )", dataReaderVariableName );
        WriteLine( L"                    {" );
        WriteLine( L"                        destinationWriter.Write( true );" );
        WriteLine( L"                        {}.WriteTo( destinationWriter );", dataReaderVariableName );
        WriteLine( L"                    }" );
        WriteLine( L"                    else" );
        WriteLine( L"                    {" );
        WriteLine( L"                        destinationWriter.Write( false );" );
        WriteLine( L"                    }" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );

    }
    void CSharpSqlServerDataContextGenerator::CreateGetAll( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetAllFunctionName( classInfo );
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );

        functions_.insert( functionName );

        WriteLine( L"        public {} {}DataReader( )", dataReaderName, functionName );
        WriteLine( L"        {" );
        WriteLine( L"            const string sql = {}.BaseQuery; ", dataReaderName );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlConnection = GetSqlConnection( );" );
        WriteLine( L"                var sqlCommand = sqlConnection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = sql;" );
        WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleResult );" );
        WriteLine( L"                var {} = new {}( _loggerFactory, sqlDataReader );", dataReaderVariableName, dataReaderName );
        WriteLine( L"                return {};", dataReaderVariableName );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );


        WriteLine( L"        public IList<{}> {}( )", className, functionName );
        WriteLine( L"        {" );
        WriteLine( L"            var result = new List<{}>( );", className );
        WriteLine( L"            var {} = {}DataReader( );", dataReaderVariableName, functionName );
        WriteLine( L"            using ( {} )", dataReaderVariableName );
        WriteLine( L"            {" );
        WriteLine( L"                while ( {}.Read( ) )", dataReaderVariableName );
        WriteLine( L"                {" );
        WriteLine( L"                    var data = {}.GetDataObject( );", dataReaderVariableName );
        WriteLine( L"                    result.Add( data );" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public void {}( Stream destinationStream )", functionName );
        WriteLine( L"        {" );
        WriteLine( L"            var destinationWriter = new BinaryWriter( destinationStream, Encoding.Unicode );" );
        WriteLine( L"            using( destinationWriter )" );
        WriteLine( L"            {" );
        WriteLine( L"                var {} = {}DataReader( );", dataReaderVariableName, functionName );
        WriteLine( L"                using ( {} )", dataReaderVariableName );
        WriteLine( L"                {" );
        WriteLine( L"                    {}.WriteResultSetTo( destinationWriter );", dataReaderVariableName );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );

    }
    void CSharpSqlServerDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo )
    {
        auto indexes = classInfo.AllIndexes( );
        auto indexCount = indexes.size( );
        for ( size_t i = 0; i < indexCount; i++ )
        {
            const auto& index = *indexes[ i ];
            const auto& indexMembers = index.Fields( );
            auto indexMemberCount = indexMembers.size( );
            for ( size_t j = 0; j < indexMemberCount; j++ )
            {
                CreateGetByIndex( classInfo, index, j + 1 );
                if ( index.HasNullableElements( j + 1 ) )
                {
                    CreateGetByNullableIndex( classInfo, index, j + 1 );
                }
                if ( index.IsTimeSeries( j + 1 ) )
                {
                    CreateGetByIndexAt( classInfo, index, j + 1 );
                }
                if ( index.IsRange( j + 1 ) )
                {
                    CreateGetByIndexFrom( classInfo, index, j + 1 );
                    CreateGetByIndexUntil( classInfo, index, j + 1 );
                    CreateGetByIndexOver( classInfo, index, j + 1 );
                }
            }
        }
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = CSharpHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", dataReaderName, functionName, arguments );
        WriteLine( L"        {" );
        CreateGetByIndexSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlConnection = GetSqlConnection( );" );
        WriteLine( L"                var sqlCommand = sqlConnection.CreateCommand( );");
        WriteLine( L"                sqlCommand.CommandText = sql;");
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter( field );
        }
        if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
        {
            WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleRow );" );
        }
        else
        {
            WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleResult );" );
        }
        WriteLine( L"                var {} = new {}( _loggerFactory, sqlDataReader );", dataReaderVariableName, dataReaderName );
        WriteLine( L"                return {};", dataReaderVariableName );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )");
        WriteLine( L"            {");
        WriteLine( L"                LogException( exc );");
        WriteLine( L"                throw;");
        WriteLine( L"            }" );
        WriteLine( L"        }" );
    }
    void CSharpSqlServerDataContextGenerator::CreateGetByIndexSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        WriteLine( L"            const string sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            auto sqlVariableName = Format( L"@{}", CSharpHelper::GetInputArgumentName( field ));
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] = {} AND \" +", dataReaderName, columnName, sqlVariableName );
            }
            else
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] = {} \" +", dataReaderName, columnName, sqlVariableName );
            }
        }
        StringBuilder<wchar_t> sb;
        auto fieldCount = fields.size( );
        for ( size_t i = 0; i < fieldCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( fieldCount - 1 ) )
            {
                sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
            }
            else
            {
                if ( indexInfo.Unique( ) )
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
                else
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
                    auto primaryKey = classInfo.PrimaryKey( );
                    columnName = primaryKey->Name( ).FirstToUpper( );
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
            }
        }
        WriteLine( L"                    \" ORDER BY \" + {};", sb.ToString( ) );

    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = className + L"?";
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                returnType = Format( L"IList<{}>", className );
            }
            auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                WriteLine( L"            var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"            using( {} )", dataReaderVariableName );
                WriteLine( L"            {" );
                WriteLine( L"                if( {}.Read( ) )", dataReaderVariableName );
                WriteLine( L"                {" );
                WriteLine( L"                    return {}.GetDataObject( );", dataReaderVariableName );
                WriteLine( L"                }" );
                WriteLine( L"                return null;" );
                WriteLine( L"            }" );
            }
            else
            {
                WriteLine( L"            var result = new List<{}>( );", className );
                WriteLine( L"            var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"            using( {} )", dataReaderVariableName );
                WriteLine( L"            {" );
                WriteLine( L"                while( {}.Read( ) )", dataReaderVariableName );
                WriteLine( L"                {" );
                WriteLine( L"                    var dataObject = {}.GetDataObject( );", dataReaderVariableName );
                WriteLine( L"                    result.Add( dataObject );" );
                WriteLine( L"                }" );
                WriteLine( L"            }" );
                WriteLine( L"            return result;" );
            }
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public void {}( {}, Stream destinationStream )", functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var destinationWriter = new BinaryWriter( destinationStream, Encoding.Unicode );" );
            WriteLine( L"            using( destinationWriter )" );
            WriteLine( L"            {" );
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                WriteLine( L"                var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"                using( {} )", dataReaderVariableName );
                WriteLine( L"                {" );
                WriteLine( L"                    if( {}.Read( ) )", dataReaderVariableName );
                WriteLine( L"                    {" );
                WriteLine( L"                        destinationWriter.Write( true );" );
                WriteLine( L"                        {}.WriteTo( destinationWriter );", dataReaderVariableName );
                WriteLine( L"                    }" );
                WriteLine( L"                    else" );
                WriteLine( L"                    {" );
                WriteLine( L"                        destinationWriter.Write( false );" );
                WriteLine( L"                    }" );
                WriteLine( L"                }" );
            }
            else
            {
                WriteLine( L"                var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"                using( {} )", dataReaderVariableName );
                WriteLine( L"                {" );
                WriteLine( L"                    {}.WriteResultSetTo( destinationWriter );", dataReaderVariableName );
                WriteLine( L"                }" );
            }
            WriteLine( L"            }" );
            WriteLine( L"        }" );
            WriteLine( );

        }
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByNullableIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"IList<{}>", className );
            auto arguments = CSharpHelper::GetByNullableIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            throw new NotImplementedException( );" );
            WriteLine( L"        }" );
        }
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexAtDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = CSharpHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", dataReaderName, functionName, arguments );
        WriteLine( L"        {" );
        CreateGetByIndexAtSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlConnection = GetSqlConnection( );" );
        WriteLine( L"                var sqlCommand = sqlConnection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = sql;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter( field );
        }
        if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
        {
            WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleRow );" );
        }
        else
        {
            WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleResult );" );
        }
        WriteLine( L"                var {} = new {}( _loggerFactory, sqlDataReader );", dataReaderVariableName, dataReaderName );
        WriteLine( L"                return {};", dataReaderVariableName );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
    }
    void CSharpSqlServerDataContextGenerator::CreateGetByIndexAtSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        WriteLine( L"            const string sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            auto sqlVariableName = Format( L"@{}", CSharpHelper::GetInputArgumentName( field ) );
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] = {} AND \" +", dataReaderName, columnName, sqlVariableName );
            }
            else
            {
                StringBuilder<wchar_t> sb;
                auto viewAlias2 = classInfo.ShortName( ).ToLower( ) + L"2";
                auto viewName = SqlServerHelper::GetViewName( classInfo );
                sb.Append( L"SELECT MAX({}.[{}]) FROM [{}] {} WHERE ", viewAlias2, columnName, viewName, viewAlias2 );
                for ( size_t j = 0; j < indexMemberCount; j++ )
                {
                    const auto& field2 = *fields[ j ];
                    auto columnName2 = field2.Name( ).FirstToUpper( );
                    auto sqlVariableName2 = Format( L"@{}", CSharpHelper::GetInputArgumentName( field2 ) );
                    if ( j < ( indexMemberCount - 1 ) )
                    {
                        sb.Append( L"{}.[{}] = {} AND ", viewAlias2, columnName2, sqlVariableName2 );
                    }
                    else
                    {
                        sb.Append( L"{}.[{}] <= {}", viewAlias2, columnName2, sqlVariableName2 );
                    }
                }

                WriteLine( L"                    {}.ViewAliasName + \".[{}] = ({}) \" +", dataReaderName, columnName, sb.ToString( ) );
            }
        }
        StringBuilder<wchar_t> sb;
        auto fieldCount = fields.size( );
        for ( size_t i = 0; i < fieldCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( fieldCount - 1 ) )
            {
                sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
            }
            else
            {
                if ( indexInfo.Unique( ) )
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
                else
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
                    auto primaryKey = classInfo.PrimaryKey( );
                    columnName = primaryKey->Name( ).FirstToUpper( );
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
            }
        }
        WriteLine( L"                    \" ORDER BY \" + {};", sb.ToString( ) );
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexAtDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = className + L"?";
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                returnType = Format( L"IList<{}>", className );
            }
            auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                WriteLine( L"            var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"            using( {} )", dataReaderVariableName );
                WriteLine( L"            {" );
                WriteLine( L"                if( {}.Read( ) )", dataReaderVariableName );
                WriteLine( L"                {" );
                WriteLine( L"                    return {}.GetDataObject( );", dataReaderVariableName );
                WriteLine( L"                }" );
                WriteLine( L"                return null;" );
                WriteLine( L"            }" );
            }
            else
            {
                WriteLine( L"            var result = new List<{}>( );", className );
                WriteLine( L"            var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"            using( {} )", dataReaderVariableName );
                WriteLine( L"            {" );
                WriteLine( L"                while( {}.Read( ) )", dataReaderVariableName );
                WriteLine( L"                {" );
                WriteLine( L"                    var dataObject = {}.GetDataObject( );", dataReaderVariableName );
                WriteLine( L"                    result.Add( dataObject );" );
                WriteLine( L"                }" );
                WriteLine( L"            }" );
                WriteLine( L"            return result;" );
            }
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public void {}( {}, Stream destinationStream )", functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var destinationWriter = new BinaryWriter( destinationStream, Encoding.Unicode );" );
            WriteLine( L"            using( destinationWriter )" );
            WriteLine( L"            {" );
            if ( CSharpHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                WriteLine( L"                var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"                using( {} )", dataReaderVariableName );
                WriteLine( L"                {" );
                WriteLine( L"                    if( {}.Read( ) )", dataReaderVariableName );
                WriteLine( L"                    {" );
                WriteLine( L"                        destinationWriter.Write( true );" );
                WriteLine( L"                        {}.WriteTo( destinationWriter );", dataReaderVariableName );
                WriteLine( L"                    }" );
                WriteLine( L"                    else" );
                WriteLine( L"                    {" );
                WriteLine( L"                        destinationWriter.Write( false );" );
                WriteLine( L"                    }" );
                WriteLine( L"                }" );
            }
            else
            {
                WriteLine( L"                var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"                using( {} )", dataReaderVariableName );
                WriteLine( L"                {" );
                WriteLine( L"                    {}.WriteResultSetTo( destinationWriter );", dataReaderVariableName );
                WriteLine( L"                }" );
            }
            WriteLine( L"            }" );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexFromDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = CSharpHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", dataReaderName, functionName, arguments );
        WriteLine( L"        {" );
        CreateGetByIndexFromSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlConnection = GetSqlConnection( );" );
        WriteLine( L"                var sqlCommand = sqlConnection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = sql;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter( field );
        }
        WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleResult );" );
        WriteLine( L"                var {} = new {}( _loggerFactory, sqlDataReader );", dataReaderVariableName, dataReaderName );
        WriteLine( L"                return {};", dataReaderVariableName );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
    }
    void CSharpSqlServerDataContextGenerator::CreateGetByIndexFromSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        WriteLine( L"            const string sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            auto sqlVariableName = Format( L"@{}", CSharpHelper::GetInputArgumentName( field ) );
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] = {} AND \" +", dataReaderName, columnName, sqlVariableName );
            }
            else
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] >= {} \" +", dataReaderName, columnName, sqlVariableName );
            }
        }
        StringBuilder<wchar_t> sb;
        auto fieldCount = fields.size( );
        for ( size_t i = 0; i < fieldCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( fieldCount - 1 ) )
            {
                sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
            }
            else
            {
                if ( indexInfo.Unique( ) )
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
                else
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
                    auto primaryKey = classInfo.PrimaryKey( );
                    columnName = primaryKey->Name( ).FirstToUpper( );
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
            }
        }
        WriteLine( L"                    \" ORDER BY \" + {};", sb.ToString( ) );
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexFromDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = Format( L"IList<{}>", className );
            auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var result = new List<{}>( );", className );
            WriteLine( L"            var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"            using( {} )", dataReaderVariableName );
            WriteLine( L"            {" );
            WriteLine( L"                while( {}.Read( ) )", dataReaderVariableName );
            WriteLine( L"                {" );
            WriteLine( L"                    var dataObject = {}.GetDataObject( );", dataReaderVariableName );
            WriteLine( L"                    result.Add( dataObject );" );
            WriteLine( L"                }" );
            WriteLine( L"            }" );
            WriteLine( L"            return result;" );
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public void {}( {}, Stream destinationStream )", functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var destinationWriter = new BinaryWriter( destinationStream, Encoding.Unicode );" );
            WriteLine( L"            using( destinationWriter )" );
            WriteLine( L"            {" );
            WriteLine( L"                var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"                using( {} )", dataReaderVariableName );
            WriteLine( L"                {" );
            WriteLine( L"                    {}.WriteResultSetTo( destinationWriter );", dataReaderVariableName );
            WriteLine( L"                }" );
            WriteLine( L"            }" );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexUntilDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = CSharpHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", dataReaderName, functionName, arguments );
        WriteLine( L"        {" );
        CreateGetByIndexUntilSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlConnection = GetSqlConnection( );" );
        WriteLine( L"                var sqlCommand = sqlConnection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = sql;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter( field );
        }
        WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleResult );" );
        WriteLine( L"                var {} = new {}( _loggerFactory, sqlDataReader );", dataReaderVariableName, dataReaderName );
        WriteLine( L"                return {};", dataReaderVariableName );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexUntilSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        WriteLine( L"            const string sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            auto sqlVariableName = Format( L"@{}", CSharpHelper::GetInputArgumentName( field ) );
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] = {} AND \" +", dataReaderName, columnName, sqlVariableName );
            }
            else
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] < {} \" +", dataReaderName, columnName, sqlVariableName );
            }
        }
        StringBuilder<wchar_t> sb;
        auto fieldCount = fields.size( );
        for ( size_t i = 0; i < fieldCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( fieldCount - 1 ) )
            {
                sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
            }
            else
            {
                if ( indexInfo.Unique( ) )
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
                else
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
                    auto primaryKey = classInfo.PrimaryKey( );
                    columnName = primaryKey->Name( ).FirstToUpper( );
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
            }
        }
        WriteLine( L"                    \" ORDER BY \" + {};", sb.ToString( ) );
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexUntilDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = Format( L"IList<{}>", className );
            auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = CSharpHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var result = new List<{}>( );", className );
            WriteLine( L"            var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"            using( {} )", dataReaderVariableName );
            WriteLine( L"            {" );
            WriteLine( L"                while( {}.Read( ) )", dataReaderVariableName );
            WriteLine( L"                {" );
            WriteLine( L"                    var dataObject = {}.GetDataObject( );", dataReaderVariableName );
            WriteLine( L"                    result.Add( dataObject );" );
            WriteLine( L"                }" );
            WriteLine( L"            }" );
            WriteLine( L"            return result;" );
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public void {}( {}, Stream destinationStream )", functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var destinationWriter = new BinaryWriter( destinationStream, Encoding.Unicode );" );
            WriteLine( L"            using( destinationWriter )" );
            WriteLine( L"            {" );
            WriteLine( L"                var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"                using( {} )", dataReaderVariableName );
            WriteLine( L"                {" );
            WriteLine( L"                    {}.WriteResultSetTo( destinationWriter );", dataReaderVariableName );
            WriteLine( L"                }" );
            WriteLine( L"            }" );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }


    void CSharpSqlServerDataContextGenerator::CreateGetByIndexOverDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = CSharpHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = CSharpHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        public {} {}( {} )", dataReaderName, functionName, arguments );
        WriteLine( L"        {" );
        CreateGetByIndexOverSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"            try" );
        WriteLine( L"            {" );
        WriteLine( L"                var sqlConnection = GetSqlConnection( );" );
        WriteLine( L"                var sqlCommand = sqlConnection.CreateCommand( );" );
        WriteLine( L"                sqlCommand.CommandText = sql;" );
        WriteLine( L"                var sqlCommandParameters = sqlCommand.Parameters;" );
        for ( size_t i = 0; i < (indexMemberCount - 1); i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter( field );
        }
        const auto& lastField = *fields[ indexMemberCount - 1 ];
        auto lastParameterName = CSharpHelper::GetInputArgumentName( lastField ).FirstToUpper();
        AddParameter( lastField, Format(L"from{}", lastParameterName ), Format(L"@from{}", lastParameterName ) );
        AddParameter( lastField, Format( L"until{}", lastParameterName ), Format( L"@until{}", lastParameterName ) );


        WriteLine( L"                var sqlDataReader = sqlCommand.ExecuteReader( System.Data.CommandBehavior.SingleResult );" );
        WriteLine( L"                var {} = new {}( _loggerFactory, sqlDataReader );", dataReaderVariableName, dataReaderName );
        WriteLine( L"                return {};", dataReaderVariableName );
        WriteLine( L"            }" );
        WriteLine( L"            catch ( Exception exc )" );
        WriteLine( L"            {" );
        WriteLine( L"                LogException( exc );" );
        WriteLine( L"                throw;" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
    }

    void CSharpSqlServerDataContextGenerator::CreateGetByIndexOverSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
        WriteLine( L"            const string sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            auto sqlVariableName = Format( L"@{}", CSharpHelper::GetInputArgumentName( field ) );
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] = {} AND \" +", dataReaderName, columnName, sqlVariableName );
            }
            else
            {
                auto lastParameterName = CSharpHelper::GetInputArgumentName( field ).FirstToUpper( );
                WriteLine( L"                    {}.ViewAliasName + \".[{}] >= @from{} AND \" +", dataReaderName, columnName, lastParameterName );
                WriteLine( L"                    {}.ViewAliasName + \".[{}] < @until{} \" +", dataReaderName, columnName, lastParameterName );
            }
        }
        StringBuilder<wchar_t> sb;
        auto fieldCount = fields.size( );
        for ( size_t i = 0; i < fieldCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( fieldCount - 1 ) )
            {
                sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
            }
            else
            {
                if ( indexInfo.Unique( ) )
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
                else
                {
                    sb.Append( L"{}.ViewAliasName + \".[{}],\" +", dataReaderName, columnName );
                    auto primaryKey = classInfo.PrimaryKey( );
                    columnName = primaryKey->Name( ).FirstToUpper( );
                    sb.Append( L"{}.ViewAliasName + \".[{}]\"", dataReaderName, columnName );
                }
            }
        }
        WriteLine( L"                    \" ORDER BY \" + {};", sb.ToString( ) );
    }


    void CSharpSqlServerDataContextGenerator::CreateGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto functionName = CSharpHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexOverDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = Format( L"IList<{}>", className );
            auto dataReaderName = CSharpHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = CSharpHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = CSharpHelper::GetByIndexFunctionOverCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"        public {} {}( {} )", returnType, functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var result = new List<{}>( );", className );
            WriteLine( L"            var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"            using( {} )", dataReaderVariableName );
            WriteLine( L"            {" );
            WriteLine( L"                while( {}.Read( ) )", dataReaderVariableName );
            WriteLine( L"                {" );
            WriteLine( L"                    var dataObject = {}.GetDataObject( );", dataReaderVariableName );
            WriteLine( L"                    result.Add( dataObject );" );
            WriteLine( L"                }" );
            WriteLine( L"            }" );
            WriteLine( L"            return result;" );
            WriteLine( L"        }" );
            WriteLine( );
            WriteLine( L"        public void {}( {}, Stream destinationStream )", functionName, arguments );
            WriteLine( L"        {" );
            WriteLine( L"            var destinationWriter = new BinaryWriter( destinationStream, Encoding.Unicode );" );
            WriteLine( L"            using( destinationWriter )" );
            WriteLine( L"            {" );
            WriteLine( L"                var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"                using( {} )", dataReaderVariableName );
            WriteLine( L"                {" );
            WriteLine( L"                    {}.WriteResultSetTo( destinationWriter );", dataReaderVariableName );
            WriteLine( L"                }" );
            WriteLine( L"            }" );
            WriteLine( L"        }" );
            WriteLine( );
        }
    }

    void CSharpSqlServerDataContextGenerator::AddParameter( const MemberInfo& memberInfo )
    {
        auto argumentName = CSharpHelper::GetInputArgumentName( memberInfo );
        auto sqlArgumentName = Format( L"@{}", memberInfo.Name( ).FirstToLower( ) );
        AddParameter( memberInfo, argumentName, sqlArgumentName );
    }

    void CSharpSqlServerDataContextGenerator::AddParameter( const MemberInfo& memberInfo, const WideString& argumentName, const WideString& sqlArgumentName )
    {
        auto sqlCommandParametersAddFunctionName = CSharpHelper::GetSqlCommandParametersAddFunctionName( memberInfo );
        
        auto parameterVariableName = argumentName + L"Parameter";
        
        auto memberType = memberInfo.Type( );
        if ( memberType == MemberInfoType::String )
        {
            const auto& stringMemberInfo = static_cast< const StringMemberInfo& >( memberInfo );
            if ( stringMemberInfo.Size( ) <= 4000 )
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, {} );", parameterVariableName, sqlCommandParametersAddFunctionName, sqlArgumentName, argumentName, stringMemberInfo.Size( ) );
            }
            else
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, sqlArgumentName, argumentName );
            }
        }
        else if ( memberType == MemberInfoType::Binary )
        {
            const auto& binaryMemberInfo = static_cast< const BinaryMemberInfo& >( memberInfo );
            if ( binaryMemberInfo.Size( ) <= 8000 )
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {}, {} );", parameterVariableName, sqlCommandParametersAddFunctionName, sqlArgumentName, argumentName, binaryMemberInfo.Size( ) );
            }
            else
            {
                WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, sqlArgumentName, argumentName );
            }
        }
        else
        {
            WriteLine( L"                var {} = sqlCommandParameters.{}( \"{}\", {} );", parameterVariableName, sqlCommandParametersAddFunctionName, sqlArgumentName, argumentName );
        }
    }

}