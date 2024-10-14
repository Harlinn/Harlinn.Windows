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
#include "CodeGenerators/Cpp/CppHelper.h"
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    void CppMsSqlStoredProceduresSourceGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        auto nspace = Options( ).Namespace( L"::" );
        WriteLine( L"#include \"pch.h\"" );
        WriteLine( );
        WriteLine( "#include \"MsSqlStoredProcedures.h\"" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( );

        auto classCount = classes.size( );
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
                WriteLine( );
            }
        }

        WriteLine( L"}" );

        Flush( );
    }
    void CppMsSqlStoredProceduresSourceGenerator::CreateInsert( const ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetInsertFunctionName( classInfo );
        auto functionParameters = CppHelper::GetInsertFunctionParameters( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} )", dllExport, functionName, functionParameters );
        WriteLine( L"    {" );

        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = CppHelper::GetInputArgumentName( *primaryKey );

        auto procedureName = MsSqlHelper::GetInsertProcedureName( classInfo );
        auto parameterMarkers = CppHelper::GetInsertFunctionParameterMarkers( classInfo );


        WriteLine( L"        auto statement = connection.CreateStatement( );" );
        WriteLine( L"        statement.Prepare( L\"{{ CALL [{}]( {} ) }}\" );", procedureName, parameterMarkers );
        auto bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( *primaryKey );
        int markerId = 1;
        WriteLine( L"        statement.{}( {}, &{}, ODBC::ParameterDirection::InputOutput );", bindParameterFunctionName, markerId, primaryKeyName );
        markerId++;


        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {
                    
                    auto variableName = CppHelper::GetInputArgumentName( member );
                    bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( member );
                    if ( member.Nullable( ) == false && ( memberType <= MemberInfoType::Double || memberType == MemberInfoType::Guid || memberType == MemberInfoType::Reference || memberType == MemberInfoType::TimeSeries ) )
                    {
                        WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, variableName );
                    }
                    else
                    {
                        WriteLine( L"        statement.{}( {}, {} );", bindParameterFunctionName, markerId, variableName );
                    }
                    markerId++;
                }
            }
        }
        WriteLine( L"        statement.Execute( );" );
        WriteLine( L"        SQLLEN numberOfRowsInserted = statement.RowCount( );" );
        WriteLine( L"        if ( numberOfRowsInserted )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.ConsumeResults( );" );
        WriteLine( L"        }" );
        WriteLine( L"        return numberOfRowsInserted > 0;" );
        WriteLine( L"    }" );
    }

    void CppMsSqlStoredProceduresSourceGenerator::CreateInsert1( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetInsertFunctionName1( classInfo );
        auto functionParameters = CppHelper::GetInsertFunctionParameters1( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} )", dllExport, functionName, functionParameters );
        WriteLine( L"    {" );

        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = CppHelper::GetInputArgumentName( *primaryKey );

        auto procedureName = MsSqlHelper::GetInsertProcedureName1( classInfo );
        auto parameterMarkers = CppHelper::GetInsertFunctionParameterMarkers1( classInfo );


        WriteLine( L"        auto statement = connection.CreateStatement( );" );
        WriteLine( L"        statement.Prepare( L\"{{ CALL [{}]( {} ) }}\" );", procedureName, parameterMarkers );
        auto bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( *primaryKey );
        int markerId = 1;
        WriteLine( L"        statement.{}( {}, &{}, ODBC::ParameterDirection::InputOutput );", bindParameterFunctionName, markerId, primaryKeyName );
        markerId++;


        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                if ( memberType != MemberInfoType::RowVersion )
                {

                    auto variableName = CppHelper::GetInputArgumentName( member );
                    bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( member );
                    if ( member.Nullable( ) == false && ( memberType <= MemberInfoType::Double || memberType == MemberInfoType::Guid || memberType == MemberInfoType::Reference || memberType == MemberInfoType::TimeSeries ) )
                    {
                        WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, variableName );
                    }
                    else
                    {
                        WriteLine( L"        statement.{}( {}, {} );", bindParameterFunctionName, markerId, variableName );
                    }
                    markerId++;
                }
            }
        }
        WriteLine( L"        statement.Execute( );" );
        WriteLine( L"        SQLLEN numberOfRowsInserted = statement.RowCount( );" );
        WriteLine( L"        if ( numberOfRowsInserted )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.ConsumeResults( );" );
        WriteLine( L"        }" );
        WriteLine( L"        return numberOfRowsInserted > 0;" );
        WriteLine( L"    }" );
    }
    void CppMsSqlStoredProceduresSourceGenerator::CreateInsertObject( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetInsertFunctionName( classInfo );
        auto functionParameters = CppHelper::GetInsertFunctionCallParameters( classInfo );

        auto dataTypeName = CppHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );
        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );

        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& {} )", dllExport, functionName, dataTypeName, argumentName );
        WriteLine( L"    {" );
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto memberType = member.Type( );
            if ( memberType != MemberInfoType::RowVersion )
            {
                auto variableType = CppHelper::GetMemberFieldType( member );
                auto variableName = CppHelper::GetInputArgumentName( member );
                auto propertyName = member.Name( ).FirstToUpper( );
                WriteLine( L"        {} {} = {}.{}( );", variableType, variableName, argumentName, propertyName );
            }
        }

        WriteLine( L"        auto result = {}( connection, {} );", functionName, functionParameters );
        WriteLine( L"        if( result )" );
        WriteLine( L"        {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyVariableName = CppHelper::GetInputArgumentName( *primaryKey );
        WriteLine( L"            {}.SetId( {} );", argumentName, primaryKeyVariableName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"            {}.Set{}( 0 );", argumentName, propertyName );
        }
        WriteLine( L"            {}.SetObjectState( ObjectState::Stored );", argumentName );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
        WriteLine( );
    }
    void CppMsSqlStoredProceduresSourceGenerator::CreateInsertObject1( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetInsertFunctionName1( classInfo );
        auto functionParameters = CppHelper::GetInsertFunctionCallParameters1( classInfo );

        auto dataTypeName = CppHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );
        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        auto memberCount = members.size( );

        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& {} )", dllExport, functionName, dataTypeName, argumentName );
        WriteLine( L"    {" );
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto memberType = member.Type( );
            if ( memberType != MemberInfoType::RowVersion )
            {
                auto variableType = CppHelper::GetMemberFieldType( member );
                auto variableName = CppHelper::GetInputArgumentName( member );
                auto propertyName = member.Name( ).FirstToUpper( );
                WriteLine( L"        {} {} = {}.{}( );", variableType, variableName, argumentName, propertyName );
            }
        }

        WriteLine( L"        auto result = {}( connection, {} );", functionName, functionParameters );
        WriteLine( L"        if( result )" );
        WriteLine( L"        {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyVariableName = CppHelper::GetInputArgumentName( *primaryKey );
        WriteLine( L"            {}.SetId( {} );", argumentName, primaryKeyVariableName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"            {}.Set{}( 0 );", argumentName, propertyName );
        }
        WriteLine( L"                {}.SetObjectState( ObjectState::Stored );", argumentName );
        WriteLine( L"            }" );
        WriteLine( L"            return result;" );
        WriteLine( L"        }" );
        WriteLine( );
    }

    void CppMsSqlStoredProceduresSourceGenerator::CreateUpdate( const ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionParameters( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} )", dllExport, functionName, functionParameters );
        WriteLine( L"    {" );
        const auto& members = classInfo.PersistentMembers( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = CppHelper::GetInputArgumentName( *primaryKey );

        auto procedureName = MsSqlHelper::GetUpdateProcedureName( classInfo );
        auto parameterMarkers = CppHelper::GetUpdateFunctionParameterMarkers( classInfo );


        WriteLine( L"        auto statement = connection.CreateStatement( );" );
        WriteLine( L"        statement.Prepare( L\"{{ CALL [{}]( {} ) }}\" );", procedureName, parameterMarkers );
        auto bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( *primaryKey );
        int markerId = 1;
        WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, primaryKeyName );
        markerId++;



        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = CppHelper::GetInputArgumentName( member );
                bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( member );
                if ( member.Nullable() == false && ( memberType <= MemberInfoType::Double || memberType == MemberInfoType::Guid || memberType == MemberInfoType::Reference || memberType == MemberInfoType::TimeSeries ) )
                {
                    WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, variableName );
                }
                else if ( memberType == MemberInfoType::RowVersion )
                {
                    WriteLine( L"        statement.{}( {}, &{}, ODBC::ParameterDirection::InputOutput );", bindParameterFunctionName, markerId, variableName );
                }
                else
                {
                    WriteLine( L"        statement.{}( {}, {} );", bindParameterFunctionName, markerId, variableName );
                }
                markerId++;
            }
        }
        WriteLine( L"        statement.Execute( );" );
        
        WriteLine( L"        SQLLEN numberOfRowsUpdated = statement.RowCount( );" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            WriteLine( L"        if( numberOfRowsUpdated )" );
            WriteLine( L"        {" );
            WriteLine( L"            statement.ConsumeResults( );" );
            WriteLine( L"        }" );
        }
        WriteLine( L"        return numberOfRowsUpdated > 0;" );
        WriteLine( L"    }" );
    }

    void CppMsSqlStoredProceduresSourceGenerator::CreateUpdate1( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName1( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionParameters1( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} )", dllExport, functionName, functionParameters );
        WriteLine( L"    {" );
        auto members = classInfo.PersistentMembersExceptNullableReferences( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = CppHelper::GetInputArgumentName( *primaryKey );

        auto procedureName = MsSqlHelper::GetUpdateProcedureName1( classInfo );
        auto parameterMarkers = CppHelper::GetUpdateFunctionParameterMarkers1( classInfo );


        WriteLine( L"        auto statement = connection.CreateStatement( );" );
        WriteLine( L"        statement.Prepare( L\"{{ CALL [{}]( {} ) }}\" );", procedureName, parameterMarkers );
        auto bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( *primaryKey );
        int markerId = 1;
        WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, primaryKeyName );
        markerId++;



        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = CppHelper::GetInputArgumentName( member );
                bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( member );
                if ( member.Nullable( ) == false && ( memberType <= MemberInfoType::Double || memberType == MemberInfoType::Guid || memberType == MemberInfoType::Reference || memberType == MemberInfoType::TimeSeries ) )
                {
                    WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, variableName );
                }
                else if ( memberType == MemberInfoType::RowVersion )
                {
                    WriteLine( L"        statement.{}( {}, &{}, ODBC::ParameterDirection::InputOutput );", bindParameterFunctionName, markerId, variableName );
                }
                else
                {
                    WriteLine( L"        statement.{}( {}, {} );", bindParameterFunctionName, markerId, variableName );
                }
                markerId++;
            }
        }
        WriteLine( L"        statement.Execute( );" );

        WriteLine( L"        SQLLEN numberOfRowsUpdated = statement.RowCount( );" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            WriteLine( L"        if( numberOfRowsUpdated )" );
            WriteLine( L"        {" );
            WriteLine( L"            statement.ConsumeResults( );" );
            WriteLine( L"        }" );
        }
        WriteLine( L"        return numberOfRowsUpdated > 0;" );
        WriteLine( L"    }" );
    }
    void CppMsSqlStoredProceduresSourceGenerator::CreateUpdate2( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName2( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionParameters2( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} )", dllExport, functionName, functionParameters );
        WriteLine( L"    {" );
        auto members = classInfo.Update2Members( );
        size_t membersCount = members.size( );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = CppHelper::GetInputArgumentName( *primaryKey );

        auto procedureName = MsSqlHelper::GetUpdateProcedureName2( classInfo );
        auto parameterMarkers = CppHelper::GetUpdateFunctionParameterMarkers2( classInfo );


        WriteLine( L"        auto statement = connection.CreateStatement( );" );
        WriteLine( L"        statement.Prepare( L\"{{ CALL [{}]( {} ) }}\" );", procedureName, parameterMarkers );
        auto bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( *primaryKey );
        int markerId = 1;
        WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, primaryKeyName );
        markerId++;



        for ( size_t i = 0; i < membersCount; i++ )
        {
            const auto& member = *members[ i ];
            if ( member.PrimaryKey( ) == false )
            {
                auto memberType = member.Type( );
                auto variableName = CppHelper::GetInputArgumentName( member );
                bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( member );
                if ( member.Nullable( ) == false && ( memberType <= MemberInfoType::Double || memberType == MemberInfoType::Guid || memberType == MemberInfoType::Reference || memberType == MemberInfoType::TimeSeries ) )
                {
                    WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, variableName );
                }
                else if ( memberType == MemberInfoType::RowVersion )
                {
                    WriteLine( L"        statement.{}( {}, &{}, ODBC::ParameterDirection::InputOutput );", bindParameterFunctionName, markerId, variableName );
                }
                else
                {
                    WriteLine( L"        statement.{}( {}, {} );", bindParameterFunctionName, markerId, variableName );
                }
                markerId++;
            }
        }
        WriteLine( L"        statement.Execute( );" );

        WriteLine( L"        SQLLEN numberOfRowsUpdated = statement.RowCount( );" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            WriteLine( L"        if( numberOfRowsUpdated )" );
            WriteLine( L"        {" );
            WriteLine( L"            statement.ConsumeResults( );" );
            WriteLine( L"        }" );
        }
        WriteLine( L"        return numberOfRowsUpdated > 0;" );
        WriteLine( L"    }" );
    }
    void CppMsSqlStoredProceduresSourceGenerator::CreateUpdateObject( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionCallParameters( classInfo );

        auto dataTypeName = CppHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.PersistentMembers( );
        auto memberCount = members.size( );

        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& {} )", dllExport, functionName, dataTypeName, argumentName );
        WriteLine( L"    {" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = CppHelper::GetMemberFieldType( member );
            auto variableName = CppHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"        {} {} = {}.{}( );", variableType, variableName, argumentName, propertyName );
        }

        WriteLine( L"        auto result = {}( connection, {} );", functionName, functionParameters );
        WriteLine( L"        if( result )" );
        WriteLine( L"        {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionVariableName = CppHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"            {}.Set{}( {} );", argumentName, propertyName, rowVersionVariableName );
        }
        WriteLine( L"            {}.SetObjectState( ObjectState::Stored );", argumentName );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );

        WriteLine( L"    }" );
    }
    void CppMsSqlStoredProceduresSourceGenerator::CreateUpdateObject1( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName1( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionCallParameters1( classInfo );

        auto dataTypeName = CppHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.PersistentMembersExceptNullableReferences( );
        auto memberCount = members.size( );

        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& {} )", dllExport, functionName, dataTypeName, argumentName );
        WriteLine( L"    {" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = CppHelper::GetMemberFieldType( member );
            auto variableName = CppHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"        {} {} = {}.{}( );", variableType, variableName, argumentName, propertyName );
        }

        WriteLine( L"        auto result = {}( connection, {} );", functionName, functionParameters );
        WriteLine( L"        if( result )" );
        WriteLine( L"        {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionVariableName = CppHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"            {}.Set{}( {} );", argumentName, propertyName, rowVersionVariableName );
        }
        WriteLine( L"            {}.SetObjectState( ObjectState::Stored );", argumentName );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );

        WriteLine( L"    }" );
    }
    void CppMsSqlStoredProceduresSourceGenerator::CreateUpdateObject2( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetUpdateFunctionName2( classInfo );
        auto functionParameters = CppHelper::GetUpdateFunctionCallParameters2( classInfo );

        auto dataTypeName = CppHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        const auto& members = classInfo.Update2Members( );
        auto memberCount = members.size( );

        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& {} )", dllExport, functionName, dataTypeName, argumentName );
        WriteLine( L"    {" );

        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto variableType = CppHelper::GetMemberFieldType( member );
            auto variableName = CppHelper::GetInputArgumentName( member );
            auto propertyName = member.Name( ).FirstToUpper( );
            WriteLine( L"        {} {} = {}.{}( );", variableType, variableName, argumentName, propertyName );
        }

        WriteLine( L"        auto result = {}( connection, {} );", functionName, functionParameters );
        WriteLine( L"        if( result )" );
        WriteLine( L"        {" );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionVariableName = CppHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"            {}.Set{}( {} );", argumentName, propertyName, rowVersionVariableName );
        }
        WriteLine( L"            {}.SetObjectState( ObjectState::Stored );", argumentName );
        WriteLine( L"        }" );
        WriteLine( L"        return result;" );

        WriteLine( L"    }" );
    }

    void CppMsSqlStoredProceduresSourceGenerator::CreateDelete( const ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetDeleteFunctionName( classInfo );
        auto functionParameters = CppHelper::GetDeleteFunctionParameters( classInfo );
        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {} )", dllExport, functionName, functionParameters );
        WriteLine( L"    {" );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = CppHelper::GetInputArgumentName( *primaryKey );

        auto procedureName = MsSqlHelper::GetDeleteProcedureName( classInfo );
        auto parameterMarkers = CppHelper::GetDeleteFunctionParameterMarkers( classInfo );

        WriteLine( L"        auto statement = connection.CreateStatement( );" );
        WriteLine( L"        statement.Prepare( L\"{{ CALL [{}]( {} ) }}\" );", procedureName, parameterMarkers );
        auto bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( *primaryKey );
        int markerId = 1;
        WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, primaryKeyName );
        markerId++;

        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto variableName = CppHelper::GetInputArgumentName( *rowVersion );
            bindParameterFunctionName = CppHelper::GetBindParameterFunctionName( *rowVersion );
            WriteLine( L"        statement.{}( {}, &{} );", bindParameterFunctionName, markerId, variableName );
            markerId++;
        }
        WriteLine( L"        Int32 numberOfObjectsDeleted = 0;" );
        WriteLine( L"        statement.BindInt32Parameter( {}, &numberOfObjectsDeleted, ODBC::ParameterDirection::Output );", markerId );
        WriteLine( L"        statement.Execute( );" );
        WriteLine( L"        SQLLEN numberOfRowsDeleted = statement.RowCount( );" );
        WriteLine( L"        if( numberOfRowsDeleted )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.ConsumeResults( );" );
        WriteLine( L"        }" );
        WriteLine( L"        return numberOfRowsDeleted > 0;" );
        WriteLine( L"    }" );
    }

    void CppMsSqlStoredProceduresSourceGenerator::CreateDeleteObject( const Metadata::ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        auto functionName = CppHelper::GetDeleteFunctionName( classInfo );
        auto dataTypeName = CppHelper::GetDataType( classInfo );
        auto argumentName = dataTypeName.FirstToLower( );

        WriteLine( L"    {} bool {}( const ODBC::Connection& connection, {}& {} )", dllExport, functionName, dataTypeName, argumentName );
        WriteLine( L"    {" );
        WriteLine( L"        const auto& id = {}.Id( );", argumentName );
        auto rowVersion = classInfo.RowVersion( );
        if ( rowVersion )
        {
            auto rowVersionVariableName = CppHelper::GetInputArgumentName( *rowVersion );
            auto propertyName = rowVersion->Name( ).FirstToUpper( );
            WriteLine( L"        auto {} = {}.{}( );", rowVersionVariableName, argumentName, propertyName );
            WriteLine( L"        auto result = {}( connection, id, {} );", functionName, rowVersionVariableName );
        }
        else
        {
            WriteLine( L"        auto result = {}( connection, id );", functionName );
        }
        WriteLine( L"        return result;" );
        WriteLine( L"    }" );
    }

}
