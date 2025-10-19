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
#include "CodeGenerators/Java/JavaHelper.h"
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"

#include <HCCStringBuilder.h>

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    void JavaMsSqlDataContextGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Owner( ).Data( ).DataTypes( );
        auto dataTypesNamespace = dataTypesOptions.Namespace( L"." );

        auto nspace = Options( ).Namespace( L"." );
        WriteLine( L"package {};", nspace );
        WriteLine( );
        WriteLine( L"import java.sql.*;" );
        WriteLine( L"import java.util.List;" );
        WriteLine( L"import java.util.ArrayList;" );
        WriteLine( );

        WriteLine( L"import com.harlinn.barrelman.databases.mssql.readers.complex.*;" );
        WriteLine( L"import com.harlinn.barrelman.databases.mssql.readers.simple.*;" );
        WriteLine( L"import com.harlinn.barrelman.types.*;" );
        WriteLine( L"import com.harlinn.common.data.*;" );
        WriteLine( L"import com.harlinn.common.io.*;" );
        WriteLine( L"import com.harlinn.common.types.*;" );
        WriteLine( L"import com.harlinn.common.util.*;" );
        WriteLine( );

        WriteLine( L"public class MsSqlDataContext implements DataContext" );
        WriteLine( L"{" );
        WriteLine( L"    private final ConnectionWrapper connection;" );
        WriteLine( L"    private final MsSqlStoredProcedures storedProcedures;" );
        WriteLine( L"    private final Guid sessionId;" );
        WriteLine( );
        WriteLine( L"    public MsSqlDataContext( ConnectionWrapper connection, Guid sessionId ) {" );
        WriteLine( L"        assert connection != null : \"connection cannot be null.\";" );
        WriteLine( L"        assert sessionId != null : \"sessionId cannot be null.\";" );
        WriteLine( L"        this.connection = connection;" );
        WriteLine( L"        this.sessionId = sessionId;" );
        WriteLine( L"        storedProcedures = new MsSqlStoredProcedures(connection);" );
        WriteLine( L"    }" );
        WriteLine( );
        WriteLine( L"    public final ConnectionWrapper getConnection( ) {" );
        WriteLine( L"        return connection;" );
        WriteLine( L"    }" );
        WriteLine( );
        WriteLine( L"    public final MsSqlStoredProcedures getStoredProcedures() {" );
        WriteLine( L"    	return storedProcedures;" );
        WriteLine( L"    }" );
        WriteLine( );
        WriteLine( L"    public final Guid getSessionId() {" );
        WriteLine( L"    	return sessionId;" );
        WriteLine( L"    }" );
        WriteLine( );
        WriteLine( L"    public final boolean insertObject(AbstractDataObjectWithGuidKey dataObject ) throws SQLException {" );
        WriteLine( L"    	return getStoredProcedures().insertObject(dataObject);" );
        WriteLine( L"    }" );
        WriteLine( );
        WriteLine( L"    public final boolean updateObject(AbstractDataObjectWithGuidKey dataObject ) throws SQLException {" );
        WriteLine( L"    	return getStoredProcedures().updateObject(dataObject);" );
        WriteLine( L"    }" );
        WriteLine( );
        WriteLine( L"    public final boolean deleteObject(AbstractDataObjectWithGuidKey dataObject ) throws SQLException {" );
        WriteLine( L"    	return getStoredProcedures().deleteObject(dataObject);" );
        WriteLine( L"    }" );
        WriteLine( );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateMembers( classInfo );
        }
        WriteLine( );
        WriteLine( L"}" );

        Flush( );
    }

    void JavaMsSqlDataContextGenerator::CreateMembers( const ClassInfo& classInfo )
    {
        WriteLine( L"    // ---------------------------------------------------------------------" );
        WriteLine( L"    // {} queries", classInfo.Name( ) );
        WriteLine( L"    // ---------------------------------------------------------------------" );
        CreateGetById( classInfo );
        CreateGetAll( classInfo );
        CreateGetByIndex( classInfo );
    }

    void JavaMsSqlDataContextGenerator::CreateGetById( const ClassInfo& classInfo )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIdFunctionName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyType = JavaHelper::GetInputArgumentType( *primaryKey );
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        functions_.insert( functionName );

        WriteLine( L"    public final {} {}DataReader( {} id ) throws SQLException {{", dataReaderName, functionName, primaryKeyType );
        WriteLine( L"        String sql = {}.BaseQuery + \"WHERE \" + {}.ViewAliasName + \".[{}] = ?\";", dataReaderName, dataReaderName, primaryKey->Name( ).FirstToUpper( ) );
        WriteLine( L"        var sqlConnection = getConnection( );" );
        WriteLine( L"        var preparedStatement = sqlConnection.prepareStatementEx( sql, ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY );" );
        WriteLine( L"        preparedStatement.setGuid( 1, id );" );
        WriteLine( L"        var resultSet = preparedStatement.executeQuery( );" );
        WriteLine( L"        return new {}( resultSet );", dataReaderName );
        WriteLine( L"    }" );
        WriteLine( );
        
        WriteLine( L"    public final {} {}( {} id ) throws SQLException {{", className, functionName, primaryKeyType );
        WriteLine( L"        var {} = {}DataReader( id );", dataReaderVariableName, functionName );
        WriteLine( L"        try ( {} ) {{", dataReaderVariableName );
        WriteLine( L"            if ( {}.next( ) ) {{", dataReaderVariableName );
        WriteLine( L"                var result = {}.getDataObject( );", dataReaderVariableName );
        WriteLine( L"                return result;" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"        return null;" );
        WriteLine( L"    }" );
        WriteLine( );

        WriteLine( L"    public final void {}( {} id, BinaryWriter destination ) throws SQLException {{", functionName, primaryKeyType );
        WriteLine( L"        var {} = {}DataReader( id );", dataReaderVariableName, functionName );
        WriteLine( L"        try ( {} ) {{", dataReaderVariableName );
        WriteLine( L"            if ( {}.next( ) ) {{", dataReaderVariableName );
        WriteLine( L"                destination.writeBoolean( true );" );
        WriteLine( L"                {}.writeTo( destination );", dataReaderVariableName );
        WriteLine( L"            }" );
        WriteLine( L"            else {" );
        WriteLine( L"                destination.writeBoolean( false );" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"    }" );
        WriteLine( );
        WriteLine( );

    }

    void JavaMsSqlDataContextGenerator::CreateGetAll( const ClassInfo& classInfo )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetAllFunctionName( classInfo );
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );

        functions_.insert( functionName );

        WriteLine( L"    public final {} {}DataReader( ) throws SQLException {{", dataReaderName, functionName );
        WriteLine( L"        String sql = {}.BaseQuery; ", dataReaderName );
        WriteLine( L"        var sqlConnection = getConnection( );" );
        WriteLine( L"        var preparedStatement = sqlConnection.prepareStatementEx( sql, ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY );" );
        WriteLine( L"        var resultSet = preparedStatement.executeQuery( );" );
        WriteLine( L"        return new {}( resultSet );", dataReaderName );
        WriteLine( L"    }" );
        WriteLine( );

        
        WriteLine( L"    public final List<{}> {}( ) throws SQLException {{", className, functionName );
        WriteLine( L"        var result = new ArrayList<{}>( );", className );
        WriteLine( L"        var {} = {}DataReader( );", dataReaderVariableName, functionName );
        WriteLine( L"        try ( {} ) {{", dataReaderVariableName );
        WriteLine( L"            while ( {}.next( ) ) {{", dataReaderVariableName );
        WriteLine( L"                var data = {}.getDataObject( );", dataReaderVariableName );
        WriteLine( L"                result.add( data );" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( );
        
        WriteLine( L"    public final void {}( BinaryWriter destination ) throws SQLException {{", functionName );
        WriteLine( L"        var {} = {}DataReader( );", dataReaderVariableName, functionName );
        WriteLine( L"        try ( {} ) {{", dataReaderVariableName );
        WriteLine( L"            {}.writeResultSetTo( destination );", dataReaderVariableName );
        WriteLine( L"        }" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo )
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

    void JavaMsSqlDataContextGenerator::CreateGetByIndexDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = JavaHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        
        auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"    public final {} {}( {} ) throws SQLException {{", dataReaderName, functionName, arguments );
        CreateGetByIndexSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        var sqlConnection = getConnection( );" );
        WriteLine( L"        var preparedStatement = sqlConnection.prepareStatementEx( sql, ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY ); " );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter(i+1, field );
        }
        WriteLine( L"        var resultSet = preparedStatement.executeQuery( );" );
        WriteLine( L"        return new {}( resultSet );", dataReaderName );
        WriteLine( L"    }" );
    }


    void JavaMsSqlDataContextGenerator::CreateGetByIndexSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        WriteLine( L"        String sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                {}.ViewAliasName + \".[{}] = ? AND \" +", dataReaderName, columnName );
            }
            else
            {
                WriteLine( L"                {}.ViewAliasName + \".[{}] = ? \" +", dataReaderName, columnName );
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
        WriteLine( L"                \" ORDER BY \" + {};", sb.ToString( ) );

    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = className;
            if ( JavaHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                returnType = Format( L"List<{}>", className );
            }
            auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = JavaHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    public final {} {}( {} ) throws SQLException {{", returnType, functionName, arguments );
            if ( JavaHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"        try( {} ) {{", dataReaderVariableName );
                WriteLine( L"            if( {}.next( ) ) {{", dataReaderVariableName );
                WriteLine( L"                return {}.getDataObject( );", dataReaderVariableName );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
                WriteLine( L"        return null;" );
            }
            else
            {
                WriteLine( L"        var result = new ArrayList<{}>( );", className );
                WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"        try( {} ) {{", dataReaderVariableName );
                WriteLine( L"            while( {}.next( ) ) {{", dataReaderVariableName );
                WriteLine( L"                var dataObject = {}.getDataObject( );", dataReaderVariableName );
                WriteLine( L"                result.add( dataObject );" );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
                WriteLine( L"        return result;" );
            }
            WriteLine( L"    }" );
            WriteLine( );
            WriteLine( L"    public final void {}( {}, BinaryWriter destination ) throws SQLException {{", functionName, arguments );
            if ( JavaHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"        try( {} ) {{", dataReaderVariableName );
                WriteLine( L"            if( {}.next( ) ) {{", dataReaderVariableName );
                WriteLine( L"                destination.writeBoolean( true );" );
                WriteLine( L"                {}.writeTo( destination );", dataReaderVariableName );
                WriteLine( L"            }" );
                WriteLine( L"            else {" );
                WriteLine( L"                destination.writeBoolean( false );" );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
            }
            else
            {
                WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"        try( {} ) {{", dataReaderVariableName );
                WriteLine( L"            {}.writeResultSetTo( destination );", dataReaderVariableName );
                WriteLine( L"        }" );
            }
            WriteLine( L"    }" );
            WriteLine( );

        }
    }

    void JavaMsSqlDataContextGenerator::CreateGetByNullableIndex( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByNullableIndexFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            auto returnType = Format( L"List<{}>", className );
            auto arguments = JavaHelper::GetByNullableIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    public final {} {}( {} ) throws SQLException {{", returnType, functionName, arguments );
            WriteLine( L"        throw new UnsupportedOperationException(\"This method is not yet implemented.\");" );
            WriteLine( L"    }" );
        }
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndexAtDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = JavaHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"    public final {} {}( {} ) throws SQLException {{", dataReaderName, functionName, arguments );
        CreateGetByIndexAtSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        var sqlConnection = getConnection( );" );
        WriteLine( L"        var preparedStatement = sqlConnection.prepareStatementEx( sql, ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY ); " );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter(i + 1, field );
        }
        AddParameter( fields.size() + 1, *fields.back() );
        WriteLine( L"        var resultSet = preparedStatement.executeQuery( );" );
        WriteLine( L"        return new {}( resultSet );", dataReaderName );
        WriteLine( L"    }" );
    }
    void JavaMsSqlDataContextGenerator::CreateGetByIndexAtSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        WriteLine( L"        String sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                {}.ViewAliasName + \".[{}] = ? AND \" +", dataReaderName, columnName );
            }
            else
            {
                StringBuilder<wchar_t> sb;
                auto viewAlias2 = classInfo.ShortName( ).ToLower( ) + L"2";
                auto viewName = MsSqlHelper::GetViewName( classInfo );
                sb.Append( L"SELECT MAX({}.[{}]) FROM [{}] {} WHERE ", viewAlias2, columnName, viewName, viewAlias2 );
                for ( size_t j = 0; j < indexMemberCount; j++ )
                {
                    const auto& field2 = *fields[ j ];
                    auto columnName2 = field2.Name( ).FirstToUpper( );
                    if ( j < ( indexMemberCount - 1 ) )
                    {
                        sb.Append( L"{}.[{}] = ? AND ", viewAlias2, columnName2 );
                    }
                    else
                    {
                        sb.Append( L"{}.[{}] <= ?", viewAlias2, columnName2 );
                    }
                }

                WriteLine( L"                {}.ViewAliasName + \".[{}] = ({}) \" +", dataReaderName, columnName, sb.ToString( ) );
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
        WriteLine( L"                \" ORDER BY \" + {};", sb.ToString( ) );
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndexAt( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexAtFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexAtDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = className;
            if ( JavaHelper::IsUnique( indexInfo, indexMemberCount ) == false )
            {
                returnType = Format( L"List<{}>", className );
            }
            auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = JavaHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    public final {} {}( {} ) throws SQLException {{", returnType, functionName, arguments );
            if ( JavaHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"        try( {} ) {{", dataReaderVariableName );
                WriteLine( L"            if( {}.next( ) ) {{", dataReaderVariableName );
                WriteLine( L"                return {}.getDataObject( );", dataReaderVariableName );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
                WriteLine( L"        return null;" );
            }
            else
            {
                WriteLine( L"        var result = new ArrayList<{}>( );", className );
                WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"        try( {} ) {{", dataReaderVariableName );
                WriteLine( L"            while( {}.next( ) ) {{", dataReaderVariableName );
                WriteLine( L"                var dataObject = {}.getDataObject( );", dataReaderVariableName );
                WriteLine( L"                result.add( dataObject );" );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
                WriteLine( L"        return result;" );
            }
            WriteLine( L"    }" );
            WriteLine( );
            WriteLine( L"    public final void {}( {}, BinaryWriter destination ) throws SQLException {{", functionName, arguments );
            if ( JavaHelper::IsUnique( indexInfo, indexMemberCount ) )
            {
                WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"        try( {} ) {{", dataReaderVariableName );
                WriteLine( L"            if( {}.next( ) ) {{", dataReaderVariableName );
                WriteLine( L"                destination.writeBoolean( true );" );
                WriteLine( L"                {}.writeTo( destination );", dataReaderVariableName );
                WriteLine( L"            }" );
                WriteLine( L"            else {" );
                WriteLine( L"                destination.writeBoolean( false );" );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
            }
            else
            {
                WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
                WriteLine( L"        try( {} ) {{", dataReaderVariableName );
                WriteLine( L"            {}.writeResultSetTo( destination );", dataReaderVariableName );
                WriteLine( L"        }" );
            }
            WriteLine( L"    }" );
            WriteLine( );
        }
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndexFromDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = JavaHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"    public final {} {}( {} ) throws SQLException {{", dataReaderName, functionName, arguments );
        CreateGetByIndexFromSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        var sqlConnection = getConnection( );" );
        WriteLine( L"        var preparedStatement = sqlConnection.prepareStatementEx( sql, ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY ); " );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter(i + 1, field );
        }
        WriteLine( L"        var resultSet = preparedStatement.executeQuery( );" );
        WriteLine( L"        return new {}( resultSet );", dataReaderName );
        WriteLine( L"    }" );
    }
    void JavaMsSqlDataContextGenerator::CreateGetByIndexFromSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        WriteLine( L"        String sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                {}.ViewAliasName + \".[{}] = ? AND \" +", dataReaderName, columnName );
            }
            else
            {
                WriteLine( L"                {}.ViewAliasName + \".[{}] >= ? \" +", dataReaderName, columnName );
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
        WriteLine( L"                \" ORDER BY \" + {};", sb.ToString( ) );
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndexFrom( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexFromFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexFromDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = Format( L"List<{}>", className );
            auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = JavaHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    public final {} {}( {} ) throws SQLException {{", returnType, functionName, arguments );
            WriteLine( L"        var result = new ArrayList<{}>( );", className );
            WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"        try( {} ) {{", dataReaderVariableName );
            WriteLine( L"            while( {}.next( ) ) {{", dataReaderVariableName );
            WriteLine( L"                var dataObject = {}.getDataObject( );", dataReaderVariableName );
            WriteLine( L"                result.add( dataObject );" );
            WriteLine( L"            }" );
            WriteLine( L"        }" );
            WriteLine( L"        return result;" );
            WriteLine( L"    }" );
            WriteLine( );
            WriteLine( L"    public final void {}( {}, BinaryWriter destination ) throws SQLException {{", functionName, arguments );
            WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"        try( {} ) {{", dataReaderVariableName );
            WriteLine( L"            {}.writeResultSetTo( destination );", dataReaderVariableName );
            WriteLine( L"        }" );
            WriteLine( L"    }" );
            WriteLine( );
        }
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndexUntilDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = JavaHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"    public final {} {}( {} ) throws SQLException {{", dataReaderName, functionName, arguments );
        CreateGetByIndexUntilSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        var sqlConnection = getConnection( );" );
        WriteLine( L"        var preparedStatement = sqlConnection.prepareStatementEx( sql, ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY ); " );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter( i + 1, field );
        }
        
        WriteLine( L"        var resultSet = preparedStatement.executeQuery( );" );
        WriteLine( L"        return new {}( resultSet );", dataReaderName );
        WriteLine( L"    }" );
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndexUntilSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        WriteLine( L"        String sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                {}.ViewAliasName + \".[{}] = ? AND \" +", dataReaderName, columnName );
            }
            else
            {
                WriteLine( L"                {}.ViewAliasName + \".[{}] < ? \" +", dataReaderName, columnName );
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
        WriteLine( L"                \" ORDER BY \" + {};", sb.ToString( ) );
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndexUntil( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexUntilFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexUntilDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = Format( L"List<{}>", className );
            auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = JavaHelper::GetByIndexFunctionParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = JavaHelper::GetByIndexFunctionCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    public final {} {}( {} ) throws SQLException {{", returnType, functionName, arguments );
            WriteLine( L"        var result = new ArrayList<{}>( );", className );
            WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"        try( {} ) {{", dataReaderVariableName );
            WriteLine( L"            while( {}.next( ) ) {{", dataReaderVariableName );
            WriteLine( L"                var dataObject = {}.getDataObject( );", dataReaderVariableName );
            WriteLine( L"                result.add( dataObject );" );
            WriteLine( L"            }" );
            WriteLine( L"        }" );
            WriteLine( L"        return result;" );
            WriteLine( L"    }" );
            WriteLine( );
            WriteLine( L"    public final void {}( {}, BinaryWriter destination ) throws SQLException {{", functionName, arguments );
            WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"        try( {} ) {{", dataReaderVariableName );
            WriteLine( L"            {}.writeResultSetTo( destination );", dataReaderVariableName );
            WriteLine( L"        }" );
            WriteLine( L"    }" );
            WriteLine( );
        }
    }


    void JavaMsSqlDataContextGenerator::CreateGetByIndexOverDataReader( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto functionName = JavaHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount ) + L"DataReader";
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        auto dataReaderVariableName = dataReaderName.FirstToLower( );
        auto arguments = JavaHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"    public final {} {}( {} ) throws SQLException {{", dataReaderName, functionName, arguments );
        CreateGetByIndexOverSql( classInfo, indexInfo, indexMemberCount );
        WriteLine( L"        var sqlConnection = getConnection( );" );
        WriteLine( L"        var preparedStatement = sqlConnection.prepareStatementEx( sql, ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY ); " );
        size_t i = 0;
        for ( ; i < ( indexMemberCount - 1 ); i++ )
        {
            const auto& field = *fields[ i ];
            AddParameter(i + 1, field );
        }
        const auto& lastField = *fields[ indexMemberCount - 1 ];
        auto lastParameterName = JavaHelper::GetInputArgumentName( lastField ).FirstToUpper( );
        AddParameter( i + 1, lastField, Format( L"from{}", lastParameterName ) );
        AddParameter( i + 2, lastField, Format( L"until{}", lastParameterName ) );


        WriteLine( L"        var resultSet = preparedStatement.executeQuery( );" );
        WriteLine( L"        return new {}( resultSet );", dataReaderName );
        WriteLine( L"    }" );
    }

    void JavaMsSqlDataContextGenerator::CreateGetByIndexOverSql( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        const auto& fields = indexInfo.Fields( );
        auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
        WriteLine( L"        String sql = {}.BaseQuery + \" WHERE \" +", dataReaderName );
        for ( size_t i = 0; i < indexMemberCount; i++ )
        {
            const auto& field = *fields[ i ];
            auto columnName = field.Name( ).FirstToUpper( );
            if ( i < ( indexMemberCount - 1 ) )
            {
                WriteLine( L"                {}.ViewAliasName + \".[{}] = ? AND \" +", dataReaderName, columnName );
            }
            else
            {
                WriteLine( L"                    {}.ViewAliasName + \".[{}] >= ? AND \" +", dataReaderName, columnName);
                WriteLine( L"                    {}.ViewAliasName + \".[{}] < ? \" +", dataReaderName, columnName );
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
        WriteLine( L"                \" ORDER BY \" + {};", sb.ToString( ) );
    }


    void JavaMsSqlDataContextGenerator::CreateGetByIndexOver( const ClassInfo& classInfo, const IndexInfo& indexInfo, size_t indexMemberCount )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        auto functionName = JavaHelper::GetByIndexOverFunctionName( classInfo, indexInfo, indexMemberCount );
        if ( functions_.contains( functionName ) == false )
        {
            functions_.insert( functionName );
            CreateGetByIndexOverDataReader( classInfo, indexInfo, indexMemberCount );
            auto returnType = Format( L"List<{}>", className );
            auto dataReaderName = JavaHelper::GetDataReaderName( classInfo );
            auto dataReaderVariableName = dataReaderName.FirstToLower( );
            auto arguments = JavaHelper::GetByIndexFunctionOverParameters( classInfo, indexInfo, indexMemberCount );
            auto callArguments = JavaHelper::GetByIndexFunctionOverCallParameters( classInfo, indexInfo, indexMemberCount );
            WriteLine( L"    public final {} {}( {} ) throws SQLException {{", returnType, functionName, arguments );
            WriteLine( L"        var result = new ArrayList<{}>( );", className );
            WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"        try( {} ) {{", dataReaderVariableName );
            WriteLine( L"            while( {}.next( ) ) {{", dataReaderVariableName );
            WriteLine( L"                var dataObject = {}.getDataObject( );", dataReaderVariableName );
            WriteLine( L"                result.add( dataObject );" );
            WriteLine( L"            }" );
            WriteLine( L"        }" );
            WriteLine( L"        return result;" );
            WriteLine( L"    }" );
            WriteLine( );
            WriteLine( L"    public final void {}( {}, BinaryWriter destination ) throws SQLException {{", functionName, arguments );
            WriteLine( L"        var {} = {}DataReader( {} );", dataReaderVariableName, functionName, callArguments );
            WriteLine( L"        try( {} ) {{", dataReaderVariableName );
            WriteLine( L"            {}.writeResultSetTo( destination );", dataReaderVariableName );
            WriteLine( L"        }" );
            WriteLine( L"    }" );
            WriteLine( );
        }
    }

    void JavaMsSqlDataContextGenerator::AddParameter( size_t parameterIndex, const Metadata::MemberInfo& memberInfo )
    {
        auto argumentName = JavaHelper::GetInputArgumentName( memberInfo );
        AddParameter( parameterIndex, memberInfo, argumentName );
    }

    void JavaMsSqlDataContextGenerator::AddParameter( size_t parameterIndex, const MemberInfo& memberInfo, const WideString& argumentName )
    {
        auto sqlCommandParametersAddFunctionName = JavaHelper::GetSqlCommandParametersAddFunctionName( memberInfo );
        WriteLine( L"        preparedStatement.{}( {}, {} );", sqlCommandParametersAddFunctionName, parameterIndex, argumentName );
    }

}