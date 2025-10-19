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
    

    void JavaMsSqlSimpleDatabaseReaderGenerator::Run( )
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

        WideString baseClassName{ L"ResultSetWrapper" };
        if ( classInfo_.IsTopLevel( ) == false )
        {
            auto baseClass = classInfo_.BaseClass( );
            baseClassName = JavaHelper::GetSimpleDataReaderName( *baseClass );
        }

        auto simpleReaderClassName = JavaHelper::GetSimpleDataReaderName( classInfo_ );

        if ( classInfo_.Abstract( ) )
        {
            WriteLine( L"public abstract class {} extends {} {{", simpleReaderClassName, baseClassName );
        }
        else
        {
            WriteLine( L"public class {} extends {} {{", simpleReaderClassName, baseClassName );
        }
        CreateQuery( classInfo_ );
        CreateFieldIds( classInfo_ );
        WriteLine( L"    public {}( ResultSet resultSet ) {{", simpleReaderClassName );
        WriteLine( L"        super( resultSet );" );
        WriteLine( L"    }" );
        WriteLine( );
        CreateAccessors( classInfo_ );
        CreateWriteColumns( classInfo_ );
        CreateGetDataObject( classInfo_ );
        WriteLine( L"}" );
        Flush( );
    }

    void JavaMsSqlSimpleDatabaseReaderGenerator::CreateQuery( const Metadata::ClassInfo& classInfo )
    {

        auto topLevelClass = classInfo.TopLevelClass( );

        auto className = JavaHelper::GetSimpleDataReaderName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = MsSqlHelper::GetColumnName( *primaryKey );
        auto viewName = MsSqlHelper::GetViewName( classInfo );
        const auto& members = classInfo.PersistentMembers( );
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
                WriteLine( L"            \"  {}.[{}], \\r\\n\" +", shortName, memberName );

                if ( member.PrimaryKey( ) && topLevelClass->HasDescendants( ) )
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
                WriteLine( L"            \"  {}.[{}] \\r\\n\" +", shortName, memberName );

            }
        }
        WriteLine( L"            \"FROM [{}] {} \\r\\n\";", viewName, shortName );
        WriteLine( );
        
        WriteLine( L"    public final static String BaseViewName = \"{}\";", viewName );
        WriteLine( L"    public final static String ViewAliasName = \"{}\";", shortName );
        
        WriteLine( );
    }

    void JavaMsSqlSimpleDatabaseReaderGenerator::CreateFieldIds( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.OwnPersistentMembers( );
        if ( members.empty( ) == false )
        {
            
            if ( classInfo.IsTopLevel( ) )
            {
                size_t id = 1;
                for ( const auto& member : members )
                {
                    WriteLine( L"    public final static int {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                    if ( member->PrimaryKey( ) && classInfo.HasDescendants( ) )
                    {
                        WriteLine( L"    public final static int ENTITYTYPE_FIELD_ID = {};", id );
                        id++;
                    }
                }
            }
            else
            {
                size_t id = 2;
                auto baseClass = classInfo.BaseClass( );
                while ( baseClass )
                {
                    id += baseClass->OwnPersistentMembers( ).size( );
                    baseClass = baseClass->BaseClass( );
                }

                for ( const auto& member : members )
                {
                    WriteLine( L"    public final static int {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                }
            }
            WriteLine( );
        }
    }

    

    void JavaMsSqlSimpleDatabaseReaderGenerator::CreateAccessors( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.OwnPersistentMembers( );
        for ( const auto& member : members )
        {
            auto fieldId = Format( L"{}_FIELD_ID", member->Name( ).ToUpper( ) );
            auto getFunctionName = JavaHelper::GetDataReaderGetFunctionName( *member );
            auto propertyType = JavaHelper::GetMemberFieldType( *member );
            auto propertyName = GetPropertyName( member->Name( ).FirstToUpper( ) );

            WriteLine( L"    public final {} get{}() throws SQLException {{", propertyType, propertyName );
            WriteLine( L"        return {}( {} );", getFunctionName, fieldId );
            WriteLine( L"    }" );
            WriteLine( );
            if ( member->PrimaryKey( ) && classInfo.HasDescendants( ) )
            {
                WriteLine( L"    public final int getObjectType() throws SQLException {" );
                WriteLine( L"        return getInt32( ENTITYTYPE_FIELD_ID );" );
                WriteLine( L"    }" );
                WriteLine( );
            }

        }
    }

    void JavaMsSqlSimpleDatabaseReaderGenerator::CreateWriteColumns( const ClassInfo& classInfo )
    {
        auto members = classInfo.OwnPersistentMembers( );
        auto memberCount = members.size( );

        if ( classInfo.IsTopLevel( ) == false )
        {
            WriteLine( L"    @Override" );
            WriteLine( L"    public void writeTo(BinaryWriter destination) throws SQLException {" );
            WriteLine( L"        super.writeTo( destination );" );
        }
        else
        {
            WriteLine( L"    public void writeTo(BinaryWriter destination) throws SQLException {" );
            WriteLine( L"        destination.writeInt32( Kind.{} );", classInfo.Name( ) );
            WriteLine( L"        destination.writeUInt8( ObjectState.Stored );" );
        }
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto fieldName = GetPropertyName( member.Name( ).FirstToUpper( ) );
            auto memberType = member.Type( );
            auto writeFunction = JavaHelper::GetSerializationWriteFunction( member );
            WriteLine( L"        destination.{}( get{}( ) );", writeFunction, fieldName );

        }
        WriteLine( L"    }" );
        WriteLine( );

        if ( classInfo.IsTopLevel( ) )
        {
            WriteLine( L"    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {" );
            WriteLine( L"        while ( next( ) ) {" );
            WriteLine( L"            destination.writeBoolean( true );" );
            WriteLine( L"            writeTo( destination );" );
            WriteLine( L"        }" );
            WriteLine( L"        destination.writeBoolean( false );" );
            WriteLine( L"    }" );
            WriteLine( );
        }

    }

    void JavaMsSqlSimpleDatabaseReaderGenerator::CreateGetDataObject( const ClassInfo& classInfo )
    {
        auto className = JavaHelper::GetDataType( classInfo );
        if ( classInfo.IsTopLevel( ) )
        {

            if ( classInfo.HasDescendants( ) )
            {
                if ( classInfo.Abstract( ) )
                {
                    WriteLine( L"    public abstract {} getDataObject( ) throws SQLException;", className );
                    WriteLine( );
                    return;
                }
                WriteLine( L"    public {} getDataObject( ) throws SQLException {{", className );
            }
            else
            {
                WriteLine( L"    public {} getDataObject( ) throws SQLException {{", className );
            }
            auto arguments = GetDataTypeConstructorCallPropertiesArguments( classInfo );
            WriteLine( L"            return new {}( {} );", className, arguments );
            WriteLine( L"    }" );
            WriteLine( );
        }
        else
        {
            if ( classInfo.Abstract( ) == false )
            {
                auto topLevelClassInfo = classInfo.TopLevelClass( );
                auto topLevelClassName = JavaHelper::GetDataType( classInfo );
                WriteLine( L"    @Override" );
                WriteLine( L"    public {} getDataObject( ) throws SQLException {{", topLevelClassName );
                auto arguments = GetDataTypeConstructorCallPropertiesArguments( classInfo );
                WriteLine( L"        return new {}( {} );", className, arguments );
                WriteLine( L"    }" );
                WriteLine( );
            }
        }
    }


}