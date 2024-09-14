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
    void CSharpComplexDatabaseReadersGenerator::Run( )
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
            if ( classInfo.DerivedClasses( ).size( ) )
            {
                CreateReader( classInfo );
            }
        }

        WriteLine( L"}" );

        Flush( );
    }

    void CSharpComplexDatabaseReadersGenerator::CreateReader( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetComplexDataReaderName( classInfo );
        WideString baseClassName = L"DataReaderWrapper";

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
        CreateWriteTo( classInfo );
        CreateGetDataObject( classInfo );
        WriteLine( L"    }" );
        WriteLine( );
    }
    void CSharpComplexDatabaseReadersGenerator::CreateQuery( const ClassInfo& classInfo )
    {
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyName = SqlServerHelper::GetColumnName( *primaryKey );
        auto viewName = SqlServerHelper::GetViewName( classInfo );
        auto members = SqlServerHelper::GetColumnsForComplexSelect( classInfo );
        auto memberCount = members.size( );
        auto shortName = classInfo.ShortName( ).ToLower( );

        WriteLine( L"        public const string BaseQuery = \"SELECT \\r\\n\" +" );
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
            auto tableName = SqlServerHelper::GetTableName( derivedClass );
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
        WriteLine( L"        public const string BaseViewName = \"{}\";", viewName );
        WriteLine( L"        public const string ViewAliasName = \"{}\";", shortName );
        WriteLine( );
    }
    void CSharpComplexDatabaseReadersGenerator::CreateFieldIds( const ClassInfo& classInfo )
    {
        auto members = SqlServerHelper::GetColumnsForComplexSelect( classInfo );

        auto viewName = SqlServerHelper::GetViewName( classInfo );

        auto memberCount = members.size( );
        auto shortName = classInfo.ShortName( ).ToUpper( );

        if ( members.empty( ) == false )
        {
            size_t id = 0;
            for ( size_t i = 0; i < memberCount; i++ )
            {
                const auto& member = *members[ i ];
                if ( classInfo.IsViewMember( member ) )
                {
                    WriteLine( L"        public const int {}_{}_FIELD_ID = {};", shortName, member.Name( ).ToUpper( ), id );
                    if ( member.PrimaryKey( ) )
                    {
                        WriteLine( L"        public const int {}_KIND_FIELD_ID = {};", shortName, id );
                        id++;
                    }
                }
                else
                {
                    auto owner = member.Owner( );
                    auto derivedShortName = owner->ShortName( ).ToUpper( );
                    WriteLine( L"        public const int {}_{}_FIELD_ID = {};", derivedShortName, member.Name( ).ToUpper( ), id );
                }
                id++;
            }

        }
    }
    void CSharpComplexDatabaseReadersGenerator::CreateAccessors( const ClassInfo& classInfo )
    {
        auto shortName = classInfo.ShortName( ).ToUpper( );
        const auto& viewMembers = classInfo.ViewMembers( );
        for ( const auto& member : viewMembers )
        {
            auto getFunctionName = CSharpHelper::GetDataReaderGetFunctionName( *member );
            auto propertyName = member->Name( ).FirstToUpper( );

            auto fieldId = Format( L"{}_{}_FIELD_ID", shortName, member->Name( ).ToUpper( ) );

            CreateAccessor( *member, propertyName, fieldId );

            if ( member->PrimaryKey( ) )
            {
                WriteLine( L"        public Types.Kind Kind" );
                WriteLine( L"        {" );
                WriteLine( L"            get" );
                WriteLine( L"            {" );
                fieldId = Format( L"{}_KIND_FIELD_ID", shortName );
                WriteLine( L"                return (Types.Kind)GetInt32( {} );", fieldId );
                WriteLine( L"            }" );
                WriteLine( L"        }" );
            }

        }

        auto derivedClasses = classInfo.AllDerivedClasses( );
        for ( const auto& derivedClass : derivedClasses )
        {
            auto ownPersistentMembers = derivedClass->OwnPersistentMembers( );
            for ( const auto& member : ownPersistentMembers )
            {
                auto owner = member->Owner( );
                auto propertyName = owner->Name( ).FirstToUpper() + member->Name( ).FirstToUpper( );

                auto derivedShortName = owner->ShortName( ).ToUpper( );
                auto fieldId = Format( L"{}_{}_FIELD_ID", derivedShortName, member->Name( ).ToUpper( ) );

                CreateAccessor( *member, propertyName, fieldId );
            }
        }
    }

    void CSharpComplexDatabaseReadersGenerator::CreateAccessor( const MemberInfo& member, const WideString& propertyName, const WideString& fieldId )
    {
        auto getFunctionName = CSharpHelper::GetDataReaderGetFunctionName( member );
        auto propertyType = CSharpHelper::GetMemberFieldType( member );
        auto memberType = member.Type( );

        WriteLine( L"        public {} {}", propertyType, propertyName );
        WriteLine( L"        {" );
        WriteLine( L"            get" );
        WriteLine( L"            {" );
        if ( memberType == MemberInfoType::DateTime )
        {
            if ( member.Nullable( ) )
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
            if ( member.Nullable( ) )
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
            if ( member.Nullable( ) )
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
    }


    void CSharpComplexDatabaseReadersGenerator::CreateWriteTo( const ClassInfo& classInfo )
    {
        auto descendantClassesAndSelf = classInfo.AllDerivedClassesAndSelf( );
        WriteLine( L"        public void WriteTo([DisallowNull] BinaryWriter destination )" );
        WriteLine( L"        {" );
        WriteLine( L"            var kind = Kind;" );
        WriteLine( L"            switch(kind)" );
        WriteLine( L"            {" );
        for ( const auto clazz : descendantClassesAndSelf )
        {
            if ( clazz->Abstract( ) == false )
            {
                WriteLine( L"                case Types.Kind.{}:", clazz->Name( ) );
                WriteLine( L"                {" );
                const auto& members = clazz->PersistentMembers( );
                auto memberCount = members.size( );

                WriteLine( L"                    destination.Write( kind );" );
                WriteLine( L"                    destination.Write( ObjectState.Stored );" );
                WriteLine( L"                    destination.Write( Id );" );

                for ( size_t i = 0; i < memberCount; i++ )
                {
                    const auto& member = *members[ i ];
                    if ( member.PrimaryKey( ) == false )
                    {
                        auto memberType = member.Type( );
                        if ( classInfo.IsViewMember( member ) )
                        {
                            auto accessorName = member.Name( ).FirstToUpper( );
                            if ( memberType != MemberInfoType::Binary )
                            {
                                WriteLine( L"                    destination.Write( {} );", accessorName );
                            }
                            else
                            {
                                WriteLine( L"                    destination.WriteArray( {} );", accessorName );
                            }
                        }
                        else
                        {
                            auto owner = member.Owner( );
                            auto accessorName = owner->Name( ).FirstToUpper( ) + member.Name( ).FirstToUpper( );
                            if ( memberType != MemberInfoType::Binary )
                            {
                                WriteLine( L"                    destination.Write( {} );", accessorName );
                            }
                            else
                            {
                                WriteLine( L"                    destination.WriteArray( {} );", accessorName );
                            }
                        }
                    }
                }
                WriteLine( L"                }" );
                WriteLine( L"                break;" );
            }
        }
        WriteLine( L"                default:" );
        WriteLine( L"                {" );
        WriteLine( L"                    var exc = new Exception( $\"Cannot perform serialization for kind={kind}.\" );" );
        WriteLine( L"                    LogException( exc );" );
        WriteLine( L"                    throw exc;" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );
        WriteLine( L"        public void WriteResultSetTo( [ DisallowNull ] BinaryWriter destination )" );
        WriteLine( L"        {" );
        WriteLine( L"            while ( Read( ) )" );
        WriteLine( L"            {" );
        WriteLine( L"                destination.Write( true );" );
        WriteLine( L"                WriteTo( destination );" );
        WriteLine( L"            }" );
        WriteLine( L"            destination.Write( false );" );
        WriteLine( L"        }" );
        WriteLine( );
    }

    void CSharpComplexDatabaseReadersGenerator::CreateGetDataObject( const ClassInfo& classInfo )
    {
        auto className = CSharpHelper::GetDataType( classInfo );
        auto descendantClassesAndSelf = classInfo.AllDerivedClassesAndSelf( );
        WriteLine( L"        public {} GetDataObject( )", className );
        WriteLine( L"        {" );
        WriteLine( L"            var kind = Kind;" );
        WriteLine( L"            switch(kind)" );
        WriteLine( L"            {" );
        for ( const auto clazz : descendantClassesAndSelf )
        {
            if ( clazz->Abstract( ) == false )
            {
                WriteLine( L"                case Types.Kind.{}:", clazz->Name() );
                WriteLine( L"                {" );
                auto clazzName = CSharpHelper::GetDataType( *clazz );
                auto arguments = CSharpHelper::GetDataTypeConstructorCallComplexReaderPropertiesArguments( classInfo, *clazz );
                WriteLine( L"                    return new {}( {} );", clazzName, arguments );
                WriteLine( L"                }" );
            }
        }
        WriteLine( L"                default:" );
        WriteLine( L"                {" );
        WriteLine( L"                    var exc = new Exception( $\"Cannot create an object for kind={kind}.\" );" );
        WriteLine( L"                    LogException( exc );" );
        WriteLine( L"                    throw exc;" );
        WriteLine( L"                }" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( );
    }
}