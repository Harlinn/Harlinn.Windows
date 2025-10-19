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


namespace Harlinn::Tools::DbXGen::CodeGenerators::Java::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    void JavaMsSqlStoredProceduresGenerator::Run( )
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
        WriteLine( );

        WriteLine( L"import com.harlinn.barrelman.types.*;" );
        WriteLine( L"import com.harlinn.common.data.*;" );
        WriteLine( L"import com.harlinn.common.io.*;" );
        WriteLine( L"import com.harlinn.common.types.*;" );
        WriteLine( L"import com.harlinn.common.util.*;" );
        WriteLine( );

        WriteLine( L"public class MsSqlStoredProcedures" );
        WriteLine( L"{" );
        WriteLine( L"    private final ConnectionWrapper connection;" );
        WriteLine( L"    private final InsertGuidKeyResult insertResult = new InsertGuidKeyResult(false, new Guid( ));" );
        WriteLine( L"    private final UpdateRowVersionResult updateResult = new UpdateRowVersionResult(false, 0);" );
        WriteLine( );
        WriteLine( L"    public MsSqlStoredProcedures( ConnectionWrapper connection ) {" );
        WriteLine( L"        assert connection != null : \"connection cannot be null.\";" );
        WriteLine( L"        this.connection = connection;" );
        WriteLine( L"    }" );
        WriteLine( );
        WriteLine( L"    public final ConnectionWrapper getConnection( ) {" );
        WriteLine( L"        return connection;" );
        WriteLine( L"    }" );
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
        
        WriteLine( L"}" );

        Flush( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateInsert( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetInsertFunctionName( classInfo );
        auto functionParameters = JavaHelper::GetInsertFunctionParameters( classInfo );
        auto storedProcedureName = MsSqlHelper::GetInsertProcedureName( classInfo );
        auto functionParameterPlaceHolders = JavaHelper::GetInsertFunctionParameterPlaceholders( classInfo );

        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyArgumentName = JavaHelper::GetInputArgumentName( *primaryKey );

        WriteLine( L"    public final InsertGuidKeyResult {}( {} ) throws SQLException {{", functionName, functionParameters );
        WriteLine( L"        insertResult.reset( );" );
        WriteLine( L"        var sqlStatement = \"{{call {}({})}}\";", storedProcedureName, functionParameterPlaceHolders );
        
        WriteLine( L"        try (var callableStatement = getConnection().prepareCallEx(sqlStatement)) {" );
        
        WriteLine( L"            if ( {} == null || {}.isEmpty( ) ) {{", primaryKeyArgumentName, primaryKeyArgumentName );
        WriteLine( L"                callableStatement.registerOutParameter( 1, Types.CHAR );" );
        WriteLine( L"            }" );
        WriteLine( L"            else {" );
        WriteLine( L"                callableStatement.setGuid(1, {});", primaryKeyArgumentName );
        WriteLine( L"            }" );
        int parameterIndex = 1;
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    parameterIndex++;
                    AddInsertParameter( parameterIndex, member );
                }
            }
        }

        WriteLine( L"            callableStatement.execute( );" );
        WriteLine( L"            int rowsAffected = callableStatement.getUpdateCount( );" );
        WriteLine( L"            if ( rowsAffected == 1 ) {" );
        WriteLine( L"                if ( {} == null || {}.isEmpty( ) ) {{", primaryKeyArgumentName, primaryKeyArgumentName );
        WriteLine( L"                    var returnedId = callableStatement.getGuid(1);" );
        WriteLine( L"                    insertResult.assign(returnedId);" );
        WriteLine( L"                }" );
        WriteLine( L"                else {" );
        WriteLine( L"                    insertResult.assign({});", primaryKeyArgumentName );
        WriteLine( L"                }" );
        WriteLine( L"            }");
        WriteLine( L"        }" );
        WriteLine( L"        return insertResult;" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateInsert1( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetInsertFunctionName1( classInfo );
        auto functionParameters = JavaHelper::GetInsertFunctionParameters1( classInfo );
        auto functionParameterPlaceHolders = JavaHelper::GetInsertFunctionParameterPlaceholders1( classInfo );
        auto storedProcedureName = MsSqlHelper::GetInsertProcedureName1( classInfo );

        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyArgumentName = JavaHelper::GetInputArgumentName( *primaryKey );

        WriteLine( L"    public final InsertGuidKeyResult {}( {} ) throws SQLException {{", functionName, functionParameters );
        WriteLine( L"        insertResult.reset( );" );
        WriteLine( L"        var sqlStatement = \"{{call {}({})}}\";", storedProcedureName, functionParameterPlaceHolders );

        WriteLine( L"        try (var callableStatement = getConnection().prepareCallEx(sqlStatement)) {" );

        WriteLine( L"            if ( {} == null || {}.isEmpty( ) ) {{", primaryKeyArgumentName, primaryKeyArgumentName );
        WriteLine( L"                callableStatement.registerOutParameter( 1, Types.CHAR );" );
        WriteLine( L"            }" );
        WriteLine( L"            else {" );
        WriteLine( L"                callableStatement.setGuid(1, {});", primaryKeyArgumentName );
        WriteLine( L"            }" );
        int parameterIndex = 1;
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    parameterIndex++;
                    AddInsertParameter( parameterIndex, member );
                }
            }
        }

        WriteLine( L"            callableStatement.execute( );" );
        WriteLine( L"            int rowsAffected = callableStatement.getUpdateCount( );" );
        WriteLine( L"            if ( rowsAffected == 1 ) {" );
        WriteLine( L"                if ( {} == null || {}.isEmpty( ) ) {{", primaryKeyArgumentName, primaryKeyArgumentName );
        WriteLine( L"                    var returnedId = callableStatement.getGuid(1);" );
        WriteLine( L"                    insertResult.assign(returnedId);" );
        WriteLine( L"                }" );
        WriteLine( L"                else {" );
        WriteLine( L"                    insertResult.assign({});", primaryKeyArgumentName );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"        return insertResult;" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateInsertObject( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetInsertFunctionName( classInfo );
        auto functionParameters = JavaHelper::GetInsertFunctionCallParameters( classInfo );

        auto dataTypeName = JavaHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );
        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );

        WriteLine( L"    public final boolean {}( {} {} ) throws SQLException {{", functionName, dataTypeName, argumentName );
        
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto memberType = member.Type( );
            if ( memberType != MemberInfoType::RowVersion )
            {
                auto variableType = JavaHelper::GetMemberFieldType( member );
                auto variableName = JavaHelper::GetInputArgumentName( member );
                auto propertyName = member.Name( ).FirstToUpper( );
                WriteLine( L"        {} {} = {}.get{}( );", variableType, variableName, argumentName, propertyName );
            }
        }

        WriteLine( L"        var result = {}( {} );", functionName, functionParameters );
        WriteLine( L"        if( result.isSuccess() ) {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyVariableName = JavaHelper::GetInputArgumentName( *primaryKey );
        WriteLine( L"            {}.setId(result.getId());", argumentName, primaryKeyVariableName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"            {}.set{}(0);", argumentName, propertyName );
        }
        WriteLine( L"            {}.setObjectState(ObjectState.Stored);", argumentName );
        WriteLine( L"        }" );
        
        WriteLine( L"        return result.isSuccess();" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateInsertObject1( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetInsertFunctionName1( classInfo );
        auto functionParameters = JavaHelper::GetInsertFunctionCallParameters1( classInfo );

        auto dataTypeName = JavaHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        auto memberCount = members.size( );

        WriteLine( L"    public final boolean {}( {} {} ) throws SQLException {{", functionName, dataTypeName, argumentName );
        
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto memberType = member.Type( );
            if ( memberType != MemberInfoType::RowVersion )
            {
                auto variableType = JavaHelper::GetMemberFieldType( member );
                auto variableName = JavaHelper::GetInputArgumentName( member );
                auto propertyName = member.Name( ).FirstToUpper( );
                WriteLine( L"        {} {} = {}.get{}( );", variableType, variableName, argumentName, propertyName );
            }
        }

        WriteLine( L"        var result = {}( {} );", functionName, functionParameters );
        WriteLine( L"        if( result.isSuccess( ) ) {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyVariableName = JavaHelper::GetInputArgumentName( *primaryKey );
        WriteLine( L"            {}.setId( result.getId( ) );", argumentName, primaryKeyVariableName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"            {}.set{}(0);", argumentName, propertyName );
        }
        WriteLine( L"            {}.setObjectState(ObjectState.Stored);", argumentName );
        WriteLine( L"        }" );
        
        WriteLine( L"        return result.isSuccess( );" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateUpdate( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetUpdateFunctionName( classInfo );
        auto functionParameters = JavaHelper::GetUpdateFunctionParameters( classInfo );
        auto functionParameterPlaceHolders = JavaHelper::GetUpdateFunctionParameterPlaceholders( classInfo );
        auto storedProcedureName = MsSqlHelper::GetUpdateProcedureName( classInfo );

        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );

        auto rowVersion = classInfo.RowVersion( );

        if ( rowVersion )
        {
            WriteLine( L"    public final UpdateRowVersionResult {}( {} ) throws SQLException {{", functionName, functionParameters );
            WriteLine( L"        updateResult.reset();" );
        }
        else
        {
            WriteLine( L"    public final boolean {}( {} ) throws SQLException {{", functionName, functionParameters );
            WriteLine( L"        boolean result = false;" );
        }
        WriteLine( L"        var sqlStatement = \"{{call {}({})}}\";", storedProcedureName, functionParameterPlaceHolders );
        WriteLine( L"        try (var callableStatement = getConnection().prepareCallEx(sqlStatement)) {" );
        AddUpdateParameter( 1, *primaryKey );
        int parameterIndex = 1;
        int rowVersionParameterIndex = 0;
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                parameterIndex++;
                AddUpdateParameter( parameterIndex, member );
                auto memberType = member.Type( );
                if ( memberType == MemberInfoType::RowVersion )
                {
                    rowVersionParameterIndex = parameterIndex;
                }
            }
        }
        WriteLine( L"            callableStatement.execute( );" );
        WriteLine( L"            int rowsAffected = callableStatement.getUpdateCount( );" );
        WriteLine( L"            if ( rowsAffected == 1 ) {" );
        if ( rowVersion )
        {
            WriteLine( L"                var returned{} = callableStatement.getInt64({});", rowVersion->Name(), rowVersionParameterIndex );
            WriteLine( L"                updateResult.assign(returned{});", rowVersion->Name( ) );
        }
        else
        {
            WriteLine( L"                result = true;" );
        }
        WriteLine( L"            }" );
        WriteLine( L"        }" );

        if ( rowVersion )
        {
            WriteLine( L"        return updateResult;" );
        }
        else
        {
            WriteLine( L"        return result;" );
        }

        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateUpdate1( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetUpdateFunctionName1( classInfo );
        auto functionParameters = JavaHelper::GetUpdateFunctionParameters1( classInfo );
        auto functionParameterPlaceHolders = JavaHelper::GetUpdateFunctionParameterPlaceholders1( classInfo );
        auto storedProcedureName = MsSqlHelper::GetUpdateProcedureName1( classInfo );

        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );


        auto rowVersion = classInfo.RowVersion( );

        if ( rowVersion )
        {
            WriteLine( L"    public final UpdateRowVersionResult {}( {} ) throws SQLException {{", functionName, functionParameters );
            WriteLine( L"        updateResult.reset();" );
        }
        else
        {
            WriteLine( L"    public final boolean {}( {} ) throws SQLException {{", functionName, functionParameters );
            WriteLine( L"        boolean result = false;" );
        }
        WriteLine( L"        var sqlStatement = \"{{call {}({})}}\";", storedProcedureName, functionParameterPlaceHolders );
        WriteLine( L"        try (var callableStatement = getConnection().prepareCallEx(sqlStatement)) {" );
        AddUpdateParameter( 1, *primaryKey );
        int parameterIndex = 1;
        int rowVersionParameterIndex = 0;
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                parameterIndex++;
                AddUpdateParameter( parameterIndex, member );
                auto memberType = member.Type( );
                if ( memberType == MemberInfoType::RowVersion )
                {
                    rowVersionParameterIndex = parameterIndex;
                }
            }
        }
        WriteLine( L"            callableStatement.execute( );" );
        WriteLine( L"            int rowsAffected = callableStatement.getUpdateCount( );" );
        WriteLine( L"            if ( rowsAffected == 1 ) {" );
        if ( rowVersion )
        {
            WriteLine( L"                var returned{} = callableStatement.getInt64({});", rowVersion->Name( ), rowVersionParameterIndex );
            WriteLine( L"                updateResult.assign(returned{});", rowVersion->Name( ) );
        }
        else
        {
            WriteLine( L"                result = true;" );
        }
        WriteLine( L"            }" );
        WriteLine( L"        }" );

        if ( rowVersion )
        {
            WriteLine( L"        return updateResult;" );
        }
        else
        {
            WriteLine( L"        return result;" );
        }

        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateUpdate2( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetUpdateFunctionName2( classInfo );
        auto functionParameters = JavaHelper::GetUpdateFunctionParameters2( classInfo );
        auto functionParameterPlaceHolders = JavaHelper::GetUpdateFunctionParameterPlaceholders2( classInfo );
        auto storedProcedureName = MsSqlHelper::GetUpdateProcedureName2( classInfo );

        const auto& members = classInfo.Update2Members( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );

        auto rowVersion = classInfo.RowVersion( );

        if ( rowVersion )
        {
            WriteLine( L"    public final UpdateRowVersionResult {}( {} ) throws SQLException {{", functionName, functionParameters );
            WriteLine( L"        updateResult.reset();" );
        }
        else
        {
            WriteLine( L"    public final boolean {}( {} ) throws SQLException {{", functionName, functionParameters );
            WriteLine( L"        boolean result = false;" );
        }
        
        WriteLine( L"        var sqlStatement = \"{{call {}({})}}\";", storedProcedureName, functionParameterPlaceHolders );
        WriteLine( L"        try (var callableStatement = getConnection().prepareCallEx(sqlStatement)) {" );
        AddUpdateParameter( 1, *primaryKey );
        int parameterIndex = 1;
        int rowVersionParameterIndex = 0;
        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                parameterIndex++;
                AddUpdateParameter( parameterIndex, member );
                auto memberType = member.Type( );
                if ( memberType == MemberInfoType::RowVersion )
                {
                    rowVersionParameterIndex = parameterIndex;
                }
            }
        }
        WriteLine( L"            callableStatement.execute( );" );
        WriteLine( L"            int rowsAffected = callableStatement.getUpdateCount( );" );
        WriteLine( L"            if ( rowsAffected == 1 ) {" );
        if ( rowVersion )
        {
            WriteLine( L"                var returned{} = callableStatement.getInt64({});", rowVersion->Name( ), rowVersionParameterIndex );
            WriteLine( L"                updateResult.assign(returned{});", rowVersion->Name( ) );
        }
        else
        {
            WriteLine( L"                result = true;" );
        }
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        if ( rowVersion )
        {
            WriteLine( L"        return updateResult;" );
        }
        else
        {
            WriteLine( L"        return result;" );
        }
        WriteLine( L"    }" );
        WriteLine( );
    }


    void JavaMsSqlStoredProceduresGenerator::CreateUpdateObject( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetUpdateFunctionName( classInfo );
        auto functionParameters = JavaHelper::GetUpdateFunctionCallParameters( classInfo );

        auto dataTypeName = JavaHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );

        auto rowVersion = classInfo.RowVersion( );

        WriteLine( L"    public final boolean {}( {} {} ) throws SQLException {{", functionName, dataTypeName, argumentName );

        
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = JavaHelper::GetMemberFieldType( member );
            auto variableName = JavaHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"        {} {} = {}.get{}();", variableType, variableName, argumentName, propertyName );
        }

        
        WriteLine( L"        var result = {}( {} );", functionName, functionParameters );

        if ( rowVersion )
        {
            auto rowVersionVariableName = JavaHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );

            
            WriteLine( L"        if( result.isSuccess( ) ) {" );
            WriteLine( L"            {}.set{}(result.getRowVersion());", argumentName, propertyName );
            WriteLine( L"            {}.setObjectState(ObjectState.Stored);", argumentName );
            WriteLine( L"        }" );
            WriteLine( L"        return result.isSuccess( );" );
        }
        else
        {
            WriteLine( L"        return result;" );
        }

        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateUpdateObject1( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetUpdateFunctionName1( classInfo );
        auto functionParameters = JavaHelper::GetUpdateFunctionCallParameters1( classInfo );

        auto dataTypeName = JavaHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        auto memberCount = members.size( );

        auto rowVersion = classInfo.RowVersion( );

        WriteLine( L"    public final boolean {}( {} {} ) throws SQLException {{", functionName, dataTypeName, argumentName );
        
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = JavaHelper::GetMemberFieldType( member );
            auto variableName = JavaHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"        {} {} = {}.get{}();", variableType, variableName, argumentName, propertyName );
        }


        WriteLine( L"        var result = {}( {} );", functionName, functionParameters );

        if ( rowVersion )
        {
            auto rowVersionVariableName = JavaHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );


            WriteLine( L"        if( result.isSuccess( ) ) {" );
            WriteLine( L"            {}.set{}(result.getRowVersion());", argumentName, propertyName );
            WriteLine( L"            {}.setObjectState(ObjectState.Stored);", argumentName );
            WriteLine( L"        }" );
            WriteLine( L"        return result.isSuccess( );" );
        }
        else
        {
            WriteLine( L"        return result;" );
        }

        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateUpdateObject2( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetUpdateFunctionName2( classInfo );
        auto functionParameters = JavaHelper::GetUpdateFunctionCallParameters2( classInfo );

        auto dataTypeName = JavaHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.Update2Members( );
        auto memberCount = members.size( );

        auto rowVersion = classInfo.RowVersion( );

        WriteLine( L"    public final boolean {}( {} {} ) throws SQLException {{", functionName, dataTypeName, argumentName );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = JavaHelper::GetMemberFieldType( member );
            auto variableName = JavaHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"        {} {} = {}.get{}();", variableType, variableName, argumentName, propertyName );
        }


        WriteLine( L"        var result = {}( {} );", functionName, functionParameters );

        if ( rowVersion )
        {
            auto rowVersionVariableName = JavaHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );


            WriteLine( L"        if( result.isSuccess( ) ) {" );
            WriteLine( L"            {}.set{}(result.getRowVersion());", argumentName, propertyName );
            WriteLine( L"            {}.setObjectState(ObjectState.Stored);", argumentName );
            WriteLine( L"        }" );
            WriteLine( L"        return result.isSuccess( );" );
        }
        else
        {
            WriteLine( L"        return result;" );
        }

        WriteLine( L"    }" );
        WriteLine( );
    }


    void JavaMsSqlStoredProceduresGenerator::CreateDelete( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetDeleteFunctionName( classInfo );
        auto functionParameters = JavaHelper::GetDeleteFunctionParameters( classInfo );
        auto functionParameterPlaceHolders = JavaHelper::GetDeleteFunctionParameterPlaceholders( classInfo ) + L", ?";
        auto storedProcedureName = MsSqlHelper::GetDeleteProcedureName( classInfo );

        auto primaryKey = classInfo.PrimaryKey( );
        auto rowVersion = classInfo.RowVersion( );

        WriteLine( L"    public final boolean {}( {} ) throws SQLException {{", functionName, functionParameters );
        WriteLine( L"        boolean result = false;" );
        WriteLine( L"        var sqlStatement = \"{{call {}({})}}\";", storedProcedureName, functionParameterPlaceHolders );
        WriteLine( L"        try (var callableStatement = getConnection().prepareCallEx(sqlStatement)) {" );
        AddDeleteParameter( 1, *primaryKey );
        if ( rowVersion )
        {
            AddDeleteParameter( 2, *rowVersion );
            WriteLine( L"            callableStatement.registerOutParameter( 3, Types.INTEGER );" );
        }
        else
        {
            WriteLine( L"            callableStatement.registerOutParameter( 2, Types.INTEGER );" );
        }
        WriteLine( L"            callableStatement.execute( );" );
        WriteLine( L"            int rowsAffected = callableStatement.getUpdateCount( );" );
        WriteLine( L"            if ( rowsAffected >= 1 ) {" );
        WriteLine( L"                result = true;" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateDeleteObject( const ClassInfo& classInfo )
    {
        auto functionName = JavaHelper::GetDeleteFunctionName( classInfo );
        auto dataTypeName = JavaHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        auto rowVersion = classInfo.RowVersion( );

        WriteLine( L"    public final boolean {}( {} {} ) throws SQLException {{", functionName, dataTypeName, argumentName );
        WriteLine( L"        var id = {}.getId( );", argumentName );

        if ( rowVersion )
        {
            auto rowVersionVariableName = JavaHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"        var {} = {}.get{}();", rowVersionVariableName, argumentName, propertyName );
            WriteLine( L"        var result = {}( id, {} );", functionName, rowVersionVariableName );
        }
        else
        {
            WriteLine( L"        var result = {}( id );", functionName );
        }

        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
    }

    void JavaMsSqlStoredProceduresGenerator::AddInsertParameter( int parameterIndex, const MemberInfo& memberInfo )
    {
        auto functionName = JavaHelper::GetSqlCommandParametersAddFunctionName( memberInfo );
        auto argumentName = JavaHelper::GetInputArgumentName( memberInfo );

        WriteLine( L"            callableStatement.{}({}, {});", functionName, parameterIndex, argumentName );

    }
    void JavaMsSqlStoredProceduresGenerator::AddUpdateParameter( int parameterIndex, const MemberInfo& memberInfo )
    {
        auto memberType = memberInfo.Type( );
        auto functionName = JavaHelper::GetSqlCommandParametersAddFunctionName( memberInfo );
        auto argumentName = JavaHelper::GetInputArgumentName( memberInfo );

        WriteLine( L"            callableStatement.{}({}, {});", functionName, parameterIndex, argumentName );


        if ( memberType == MemberInfoType::RowVersion )
        {
            WriteLine( L"            callableStatement.registerOutParameter( {}, Types.BIGINT );", parameterIndex );
        }
        
    }

    void JavaMsSqlStoredProceduresGenerator::AddDeleteParameter( int parameterIndex, const MemberInfo& memberInfo )
    {
        auto functionName = JavaHelper::GetSqlCommandParametersAddFunctionName( memberInfo );
        auto argumentName = JavaHelper::GetInputArgumentName( memberInfo );

        WriteLine( L"            callableStatement.{}({}, {});", functionName, parameterIndex, argumentName );
    }

    void JavaMsSqlStoredProceduresGenerator::CreateInsertDataObject( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"    public final boolean insertObject( AbstractDataObjectWithGuidKey dataObject ) throws SQLException {" );
        WriteLine( L"        boolean result = false;" );
        WriteLine( L"        var kind = dataObject.getObjectType( );" );
        WriteLine( L"        switch ( kind ) {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto functionName = JavaHelper::GetInsertFunctionName( classInfo );
                auto dataClassName = JavaHelper::GetDataType( classInfo );
                WriteLine( L"            case Kind.{}:", classInfo.Name( ).FirstToUpper( ) );
                WriteLine( L"                result = {}( ({})dataObject );", functionName, dataClassName );
                WriteLine( L"            break;" );
            }
        }
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( );
    }
    void JavaMsSqlStoredProceduresGenerator::CreateUpdateDataObject( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"    public final boolean updateObject( AbstractDataObjectWithGuidKey dataObject ) throws SQLException {" );
        WriteLine( L"        boolean result = false;" );
        WriteLine( L"        var kind = dataObject.getObjectType( );" );
        WriteLine( L"        switch ( kind ) {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto functionName = JavaHelper::GetUpdateFunctionName( classInfo );
                auto dataClassName = JavaHelper::GetDataType( classInfo );
                WriteLine( L"            case Kind.{}:", classInfo.Name( ).FirstToUpper( ) );
                WriteLine( L"                result = {}( ({})dataObject );", functionName, dataClassName );
                WriteLine( L"            break;" );
            }
        }
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( );
    }
    void JavaMsSqlStoredProceduresGenerator::CreateDeleteDataObject( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        WriteLine( L"    public final boolean deleteObject( AbstractDataObjectWithGuidKey dataObject ) throws SQLException {" );
        WriteLine( L"        boolean result = false;" );
        WriteLine( L"        var kind = dataObject.getObjectType( );" );
        WriteLine( L"        switch ( kind ) {" );
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto classInfo = *classes[ i ];
            if ( classInfo.Abstract( ) == false )
            {
                auto functionName = JavaHelper::GetDeleteFunctionName( classInfo );
                auto dataClassName = JavaHelper::GetDataType( classInfo );
                WriteLine( L"            case Kind.{}:", classInfo.Name( ).FirstToUpper( ) );
                WriteLine( L"                result = {}( ({})dataObject );", functionName, dataClassName );
                WriteLine( L"            break;" );
            }
        }
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( );
    }
    void JavaMsSqlStoredProceduresGenerator::CreateMergeDataObject( )
    {
        WriteLine( L"    public final boolean mergeObject( AbstractDataObjectWithGuidKey dataObject ) throws SQLException {" );
        WriteLine( L"        boolean result = false;" );
        WriteLine( L"        var objectState = dataObject.getObjectState( );" );
        WriteLine( L"        switch ( objectState ) {" );
        WriteLine( L"            case ObjectState.New:" );
        WriteLine( L"                result = insertObject( dataObject );" );
        WriteLine( L"            break;" );
        WriteLine( L"            case ObjectState.Changed:" );
        WriteLine( L"                result = updateObject( dataObject );" );
        WriteLine( L"            break;" );
        WriteLine( L"            case ObjectState.Deleted:" );
        WriteLine( L"                result = deleteObject( dataObject );" );
        WriteLine( L"            break;" );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( );
    }


}