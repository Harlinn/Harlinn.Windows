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
    void CSharpDatabaseReadersGenerator::Run( )
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

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateReader( classInfo );
        }

        WriteLine( L"}" );

        Flush();
    }

    void CSharpDatabaseReadersGenerator::CreateReader( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetSimpleDataReaderName( classInfo );
        WideString baseClassName = L"DataReaderWrapper";
        if ( classInfo.IsTopLevel( ) == false )
        {
            auto baseClass = classInfo.BaseClass( );
            baseClassName = CSharpHelper::GetSimpleDataReaderName( *baseClass );
        }
        WriteLine( L"    public class {} : {}", className, baseClassName );
        WriteLine( L"    {" );
        CreateQuery( classInfo );
        CreateFieldIds( classInfo );
        WriteLine( L"        public {}( [ DisallowNull ] ILoggerFactory loggerFactory, [ DisallowNull ] SqlDataReader sqlDataReader, bool ownsReader = true )", className );
        WriteLine( L"            : base(loggerFactory, sqlDataReader, ownsReader )" );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( );
        CreateAccessors( classInfo );
        WriteLine( L"    }" );
        WriteLine( );
    }
    void CSharpDatabaseReadersGenerator::CreateQuery( const ClassInfo& classInfo )
    {
        auto topLevelClass = classInfo.TopLevelClass( );

        auto className = CSharpHelper::GetSimpleDataReaderName( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = SqlServerHelper::GetColumnName( *primaryKey );
        auto viewName = SqlServerHelper::GetViewName( classInfo );
        const auto& members = classInfo.PersistentMembers();
        auto memberCount = members.size( );
        auto shortName = classInfo.ShortName( ).ToLower( );

        if ( classInfo.IsTopLevel( ) )
        {
            WriteLine( L"        public const string BaseQuery = \"SELECT \\r\\n\" +" );
        }
        else
        {
            WriteLine( L"        public new const string BaseQuery = \"SELECT \\r\\n\" +" );
        }

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
        if ( classInfo.IsTopLevel( ) )
        {
            WriteLine( L"        public const string BaseViewName = \"{}\";", viewName );
            WriteLine( L"        public const string ViewAliasName = \"{}\";", shortName );
        }
        else
        {
            WriteLine( L"        public new const string BaseViewName = \"{}\";", viewName );
            WriteLine( L"        public new const string ViewAliasName = \"{}\";", shortName );
        }
        WriteLine( );
    }
    void CSharpDatabaseReadersGenerator::CreateFieldIds( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.OwnPersistentMembers();
        if ( members.empty( ) == false )
        {
            size_t id = 0;
            if ( classInfo.IsTopLevel( ) )
            {
                for ( const auto& member : members )
                {
                    WriteLine( L"        public const int {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                    if ( member->PrimaryKey( ) && classInfo.HasDescendants( ) )
                    {
                        WriteLine( L"        public const int ENTITYTYPE_FIELD_ID = {};", id );
                        id++;
                    }
                }
            }
            else
            {
                auto baseClass = classInfo.BaseClass( );
                while ( baseClass )
                {
                    id += baseClass->OwnPersistentMembers( ).size( );
                    baseClass = baseClass->BaseClass( );
                }

                for ( const auto& member : members )
                {
                    WriteLine( L"        public const int {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                }
            }
            WriteLine( );
        }
    }
    void CSharpDatabaseReadersGenerator::CreateAccessors( const ClassInfo& classInfo )
    {
        const auto& members = classInfo.OwnPersistentMembers( );
        for ( const auto& member : members )
        {
            auto fieldId = Format( L"{}_FIELD_ID", member->Name( ).ToUpper( ) );
            auto getFunctionName = CSharpHelper::GetDataReaderGetFunctionName( *member );
            auto propertyType = CSharpHelper::GetMemberFieldType( *member );
            auto propertyName = member->Name( ).FirstToUpper( );
            auto memberType = member->Type( );

            WriteLine( L"        public {} {}", propertyType, propertyName );
            WriteLine( L"        {" );
            WriteLine( L"            get" );
            WriteLine( L"            {" );
            if ( memberType == MemberInfoType::DateTime )
            {
                if ( member->Nullable( ) )
                {
                    WriteLine( L"                var v = {}( {} );", getFunctionName, fieldId );
                    WriteLine( L"                if( v is long value )" );
                    WriteLine( L"                {" );
                    WriteLine( L"                    return new DateTime( value , DateTimeKind.Utc );" );
                    WriteLine( L"                }" );
                    WriteLine( L"                return null;" );
                }
                else
                {
                    WriteLine( L"                return new DateTime( {}( {} ), DateTimeKind.Utc );", getFunctionName, fieldId );
                }
            }
            else if ( memberType == MemberInfoType::TimeSpan )
            {
                if ( member->Nullable( ) )
                {
                    WriteLine( L"                var v = {}( {} );", getFunctionName, fieldId );
                    WriteLine( L"                if( v is long value )" );
                    WriteLine( L"                {" );
                    WriteLine( L"                    return new TimeSpan( value );" );
                    WriteLine( L"                }" );
                    WriteLine( L"                return null;" );
                }
                else
                {
                    WriteLine( L"                return new TimeSpan( {}( {} ) );", getFunctionName, fieldId );
                }
            }
            else if ( memberType == MemberInfoType::Currency )
            {
                if ( member->Nullable( ) )
                {
                    WriteLine( L"                var v = {}( {} );", getFunctionName, fieldId );
                    WriteLine( L"                if( v is long value )" );
                    WriteLine( L"                {" );
                    WriteLine( L"                    return Currency.FromScaled( value );" );
                    WriteLine( L"                }" );
                    WriteLine( L"                return null;" );
                }
                else
                {
                    WriteLine( L"                return Currency.FromScaled( {}( {} ) );", getFunctionName, fieldId );
                }
            }
            else
            {
                WriteLine( L"                return {}( {} );", getFunctionName, fieldId );
            }
            WriteLine( L"            }" );
            WriteLine( L"        }" );

            if ( member->PrimaryKey( ) && classInfo.HasDescendants( ) )
            {
                WriteLine( L"        public Types.Kind EntityType" );
                WriteLine( L"        {" );
                WriteLine( L"            get" );
                WriteLine( L"            {" );
                WriteLine( L"                return GetEnum<Types.Kind>( ENTITYTYPE_FIELD_ID );" );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
            }
            
        }

    }
    void CSharpDatabaseReadersGenerator::CreateWriteColumns( const ClassInfo& classInfo )
    {

    }
    void CSharpDatabaseReadersGenerator::CreateAssignTo( const ClassInfo& classInfo )
    {

    }

}