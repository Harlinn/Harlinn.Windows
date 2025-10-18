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

#include "HCCStringBuilder.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Java::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    namespace
    {
        std::unordered_map<WideString, WideString> GetReservedNames( )
        {
            std::unordered_map<WideString, WideString> reservedNames;
            reservedNames.emplace( L"ObjectType", L"ObjectTypeField" );
            reservedNames.emplace( L"Type", L"TypeField" );
            
            return reservedNames;
        }

        WideString GetPropertyName( const WideString& propertyName )
        {
            static std::unordered_map<WideString, WideString> reservedNames = GetReservedNames( );
            auto it = reservedNames.find( propertyName );
            if ( it != reservedNames.end( ) )
            {
                return it->second;
            }
            return propertyName;
        }

        WideString GetDataTypeConstructorCallPropertiesArguments( const ClassInfo& classInfo )
        {
            const auto& members = classInfo.PersistentMembers( );
            auto memberCount = members.size( );
            StringBuilder<wchar_t> sb;

            sb.Append( L"ObjectState.Stored, getId( )" );

            for ( size_t i = 0; i < memberCount; i++ )
            {
                const auto& member = *members[ i ];
                if ( member.PrimaryKey( ) == false )
                {
                    auto argumentName = GetPropertyName( member.Name( ).FirstToUpper( ) );
                    sb.Append( L", get{}( )", argumentName );
                }
            }
            return sb.ToString( );
        }
    }

    void JavaMsSqlComplexDatabaseReaderGenerator::Run( )
    {
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

        CreateReader( classInfo_ );

        Flush( );
    }

    void JavaMsSqlComplexDatabaseReaderGenerator::CreateReader( const Metadata::ClassInfo& classInfo )
    {
        auto complexReaderClassName = JavaHelper::GetComplexDataReaderName( classInfo );
        WideString baseClassName{ L"ResultSetWrapper" };

        WriteLine( L"public class {} extends {} {{", complexReaderClassName, baseClassName );
        WriteLine( );
        CreateQuery( classInfo );
        CreateFieldIds( classInfo );
        WriteLine( );
        WriteLine( L"    public {}( ResultSet resultSet ) {{", complexReaderClassName );
        WriteLine( L"        super( resultSet );" );
        WriteLine( L"    }" );
        WriteLine( );
        CreateAccessors( classInfo );
        WriteLine( L"}" );
        WriteLine( );
    }

    void JavaMsSqlComplexDatabaseReaderGenerator::CreateQuery( const Metadata::ClassInfo& classInfo )
    {
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = MsSqlHelper::GetColumnName( *primaryKey );
        auto viewName = MsSqlHelper::GetViewName( classInfo );
        auto members = MsSqlHelper::GetColumnsForComplexSelect( classInfo );
        auto memberCount = members.size( );
        auto shortName = classInfo.ShortName( ).ToLower( );

        WriteLine( L"    public final static String BaseQuery = \"SELECT \\r\\n\" +" );
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto owner = member.Owner( );
            auto memberName = member.Name( );
            if ( i < memberCount - 1 || member.PrimaryKey( ) )
            {
                if ( classInfo.IsViewMember( member ) )
                {
                    WriteLine( L"            \"  {}.[{}], \\r\\n\" +", shortName, memberName );
                }
                else
                {
                    auto derivedShortName = owner->ShortName( ).ToLower( );
                    WriteLine( L"            \"  {}.[{}], \\r\\n\" +", derivedShortName, memberName );
                }
                if ( member.PrimaryKey( ) )
                {
                    if ( i < memberCount - 1 )
                    {
                        WriteLine( L"            \"  {}.[EntityType], \\r\\n\" +", shortName );
                    }
                    else
                    {
                        WriteLine( L"            \"  {}.[EntityType] \\r\\n\" +", shortName );
                    }
                }
            }
            else
            {
                if ( classInfo.IsViewMember( member ) )
                {
                    WriteLine( L"            \"  {}.[{}] \\r\\n\" +", shortName, memberName );
                }
                else
                {
                    auto derivedShortName = owner->ShortName( ).ToLower( );
                    WriteLine( L"            \"  {}.[{}] \\r\\n\" +", derivedShortName, memberName );
                }

            }
        }
        WriteLine( L"            \"FROM [{}] {} \\r\\n\" +", viewName, shortName );
        auto derivedClasses = classInfo.AllDerivedClasses( );
        auto derivedClassCount = derivedClasses.size( );
        for ( size_t i = 0; i < derivedClassCount; i++ )
        {
            const auto& derivedClass = *derivedClasses[ i ];
            auto tableName = MsSqlHelper::GetTableName( derivedClass );
            auto derivedShortName = derivedClass.ShortName( ).ToLower( );
            if ( i < derivedClassCount - 1 )
            {
                WriteLine( L"            \"  LEFT JOIN [{}] {} ON({}.{} = {}.{} ) \\r\\n\" +", tableName, derivedShortName, shortName, primaryKeyName, derivedShortName, primaryKeyName );
            }
            else
            {
                WriteLine( L"            \"  LEFT JOIN [{}] {} ON({}.{} = {}.{} ) \\r\\n\";", tableName, derivedShortName, shortName, primaryKeyName, derivedShortName, primaryKeyName );
            }

        }


        WriteLine( );
        WriteLine( L"    public final static String BaseViewName = \"{}\";", viewName );
        WriteLine( L"    public final static String ViewAliasName = \"{}\";", shortName );
        WriteLine( );
    }

    void JavaMsSqlComplexDatabaseReaderGenerator::CreateFieldIds( const ClassInfo& classInfo )
    {
        auto members = MsSqlHelper::GetColumnsForComplexSelect( classInfo );

        auto viewName = MsSqlHelper::GetViewName( classInfo );

        auto memberCount = members.size( );
        auto shortName = classInfo.ShortName( ).ToUpper( );

        if ( members.empty( ) == false )
        {
            size_t id = 1;
            for ( size_t i = 0; i < memberCount; i++ )
            {
                const auto& member = *members[ i ];
                if ( classInfo.IsViewMember( member ) )
                {
                    WriteLine( L"    public final static int {}_{}_FIELD_ID = {};", shortName, member.Name( ).ToUpper( ), id );
                    if ( member.PrimaryKey( ) )
                    {
                        id++;
                        WriteLine( L"    public final static int {}_KIND_FIELD_ID = {};", shortName, id );
                    }
                }
                else
                {
                    auto owner = member.Owner( );
                    auto derivedShortName = owner->ShortName( ).ToUpper( );
                    WriteLine( L"    public final static int {}_{}_FIELD_ID = {};", derivedShortName, member.Name( ).ToUpper( ), id );
                }
                id++;
            }

        }
    }

    void JavaMsSqlComplexDatabaseReaderGenerator::CreateAccessors( const ClassInfo& classInfo )
    {
        auto shortName = classInfo.ShortName( ).ToUpper( );
        const auto& viewMembers = classInfo.ViewMembers( );
        for ( const auto& member : viewMembers )
        {
            auto getFunctionName = JavaHelper::GetDataReaderGetFunctionName( *member );
            auto propertyName = member->Name( ).FirstToUpper( );

            auto fieldId = Format( L"{}_{}_FIELD_ID", shortName, member->Name( ).ToUpper( ) );

            CreateAccessor( *member, propertyName, fieldId );

            if ( member->PrimaryKey( ) )
            {
                WriteLine( L"    public int getObjectType() throws SQLException {" );
                fieldId = Format( L"{}_KIND_FIELD_ID", shortName );
                WriteLine( L"        return getInt32( {} );", fieldId );
                WriteLine( L"    }" );
                WriteLine( );
            }
        }

        auto derivedClasses = classInfo.AllDerivedClasses( );
        for ( const auto& derivedClass : derivedClasses )
        {
            auto ownPersistentMembers = derivedClass->OwnPersistentMembers( );
            for ( const auto& member : ownPersistentMembers )
            {
                auto owner = member->Owner( );
                auto propertyName = owner->Name( ).FirstToUpper( ) + member->Name( ).FirstToUpper( );

                auto derivedShortName = owner->ShortName( ).ToUpper( );
                auto fieldId = Format( L"{}_{}_FIELD_ID", derivedShortName, member->Name( ).ToUpper( ) );

                CreateAccessor( *member, propertyName, fieldId );
            }
        }
    }

    void JavaMsSqlComplexDatabaseReaderGenerator::CreateAccessor( const MemberInfo& member, const WideString& propertyName, const WideString& fieldId )
    {
        auto getFunctionName = JavaHelper::GetDataReaderGetFunctionName( member );
        auto propertyType = JavaHelper::GetMemberFieldType( member );

        WriteLine( L"    public {} get{}( ) throws SQLException {{", propertyType, GetPropertyName( propertyName ) );
        WriteLine( L"        return {}( {} );", getFunctionName, fieldId );
        WriteLine( L"    }" );
        WriteLine( );
    }

}