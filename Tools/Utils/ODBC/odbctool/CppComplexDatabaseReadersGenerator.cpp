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
#include "CppHelper.h"

namespace Harlinn::ODBC::Tool
{
    void CppComplexDatabaseReadersGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto headerGuard = CppHelper::GetHeaderGuard( Filename( ) );
        auto nspace = Options( ).Namespace( L"::" );
        WriteLine( L"#pragma once" );
        WriteLine( L"#ifndef {}", headerGuard );
        WriteLine( L"#define {}", headerGuard );
        WriteLine( );
        WriteLine( "#include \"DatabaseReaders.h\"" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( L"    using namespace Harlinn;" );
        WriteLine( L"    using namespace Harlinn::ODBC;" );
        WriteLine( L"    using namespace Harlinn::Common::Core;" );
        WriteLine( );

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            if ( classInfo.DerivedClasses( ).size( ) )
            {
                CreateColumnDataType( classInfo );
            }
        }

        WriteLine( L"}" );
        WriteLine( L"#endif" );

        Flush( );
    }


    void CppComplexDatabaseReadersGenerator::CreateColumnDataType( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetComplexColumnDataType( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyTypeName = CppHelper::GetMemberFieldType( *primaryKey );

        WideString baseClassName = L"BaseColumnData";

        WriteLine( L"    class {} : public {}", className, baseClassName );
        WriteLine( L"    {" );
        
        auto shortName = classInfo.ShortName( );
        auto shortname = shortName.ToLower( );

        const auto& viewMembers = classInfo.ViewMembers( );
        for ( const auto& member : viewMembers )
        {
            auto typeName = CppHelper::GetMemberFieldType( *member );
            auto fieldName = CppHelper::GetMemberFieldName( *member );
            if ( CppHelper::MemberFieldRequiresDefaultValue( *member ) )
            {
                auto defaultValue = CppHelper::GetDefaultValue( *member );
                WriteLine( L"        {} {} = {};", typeName, fieldName, defaultValue );
            }
            else
            {
                WriteLine( L"        {} {};", typeName, fieldName );
            }
            if ( CppHelper::RequiresIndicator( *member ) )
            {
                auto indicatorName = CppHelper::GetMemberIndicatorName( *member );
                WriteLine( L"        SQLLEN {} = SQL_NULL_DATA;", indicatorName );
            }
            if ( member->PrimaryKey( ) )
            {
                WriteLine( L"        Data::Kind kind_ = Data::Kind::Unknown;"  );
            }
        }

        auto derivedClasses = classInfo.AllDerivedClasses( );
        for ( const auto& derivedClass : derivedClasses )
        {
            auto ownPersistentMembers = derivedClass->OwnPersistentMembers( );
            for ( const auto& member : ownPersistentMembers )
            {
                auto typeName = CppHelper::GetMemberNullableFieldType( *member );
                auto fieldName = CppHelper::GetLongMemberFieldName( *member );
                WriteLine( L"        {} {};", typeName, fieldName );
            }
        }

        WriteLine( L"    public:" );
        WriteLine( L"        using Base = {};", baseClassName );
        WriteLine( );
        CreateQuery( classInfo );
        CreateFieldIds( classInfo );
        WriteLine( );
        WriteLine( L"        {}( ) = default;", className );
        WriteLine( );

        WriteLine( L"        virtual Kind GetKind() const override" );
        WriteLine( L"        {" );
        WriteLine( L"            return kind_;" );
        WriteLine( L"        }" );
        WriteLine( );

        CreateBindColumns( classInfo );
        CreateReadUnboundData( classInfo );
        CreateAccessors( classInfo );

        /*
        

        if ( classInfo.IsTopLevel( ) )
        {
            CreateAccessor( classInfo, *primaryKey );
            CreateSetter( classInfo, *primaryKey );
        }

        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                CreateAccessor( classInfo, *member );
                CreateSetter( classInfo, *member );
            }
        }
        
        
        */

        CreateWriteColumns( classInfo );

        WriteLine( L"    };" );
        WriteLine( );
        WriteLine( L"    using Complex{}DataReader = SimpleColumnDataReader<{}>;", classInfo.Name( ), className );
        WriteLine( );
    }

    void CppComplexDatabaseReadersGenerator::CreateQuery( const ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        WriteLine( L"        static {} WideString BaseQuery;", dllExport );
        WriteLine( L"        static {} WideString BaseViewName;", dllExport );
        WriteLine( L"        static {} WideString ViewAliasName;", dllExport );
        WriteLine( );
    }

    void CppComplexDatabaseReadersGenerator::CreateFieldIds( const ClassInfo& classInfo )
    {
        auto members = SqlServerHelper::GetColumnsForComplexSelect( classInfo );

        auto viewName = SqlServerHelper::GetViewName( classInfo );
        
        auto memberCount = members.size( );
        auto shortName = classInfo.ShortName( ).ToUpper( );

        if ( members.empty( ) == false )
        {
            size_t id = 1;
            for ( size_t i = 0; i < memberCount; i++ )
            {
                const auto& member = *members[ i ];
                if ( classInfo.IsViewMember(  member ) )
                {
                    WriteLine( L"        static constexpr SQLUSMALLINT {}_{}_FIELD_ID = {};", shortName, member.Name( ).ToUpper( ), id );
                    if ( member.PrimaryKey( ) )
                    {
                        WriteLine( L"        static constexpr SQLUSMALLINT {}_KIND_FIELD_ID = {};", shortName, id );
                        id++;
                    }
                }
                else
                {
                    auto owner = member.Owner( );
                    auto derivedShortName = owner->ShortName( ).ToUpper( );
                    WriteLine( L"        static constexpr SQLUSMALLINT {}_{}_FIELD_ID = {};", derivedShortName, member.Name( ).ToUpper( ), id );
                }
                id++;
            }

        }
    }

    void CppComplexDatabaseReadersGenerator::CreateBindColumns( const ClassInfo& classInfo )
    {
        auto members = SqlServerHelper::GetBindableColumnsForComplexSelect( classInfo );
        if ( members.empty( ) == false )
        {
            auto dllExport = Options( ).DllExport( );
            WriteLine( L"        {} void BindColumns( const ODBC::Statement& statement );", dllExport );
            WriteLine( );
        }
    }

    void CppComplexDatabaseReadersGenerator::CreateReadUnboundData( const ClassInfo& classInfo )
    {
        auto members = SqlServerHelper::GetUnboundColumnsForComplexSelect( classInfo );
        if ( members.empty( ) == false )
        {
            auto dllExport = Options( ).DllExport( );
            WriteLine( L"        {} void ReadUnboundData( const ODBC::Statement& statement );", dllExport );
        }
    }



    void CppComplexDatabaseReadersGenerator::CreateAccessors( const ClassInfo& classInfo )
    {
        const auto& viewMembers = classInfo.ViewMembers( );
        for ( const auto& member : viewMembers )
        {
            auto memberType = member->Type( );
            auto typeName = CppHelper::GetMemberFieldType( *member );
            auto fieldName = CppHelper::GetMemberFieldName( *member );
            auto returnType = typeName;
            if ( memberType > MemberInfoType::Double && memberType != MemberInfoType::RowVersion )
            {
                returnType = Format( L"const {}&", typeName );
            }
            auto accessorName = CppHelper::GetMemberAccessorName( *member );
            WriteLine( L"        {} {}( ) const", returnType, accessorName );
            WriteLine( L"        {" );
            WriteLine( L"            return {};", fieldName );
            WriteLine( L"        }" );
        }

        auto derivedClasses = classInfo.AllDerivedClasses( );
        for ( const auto& derivedClass : derivedClasses )
        {
            auto ownPersistentMembers = derivedClass->OwnPersistentMembers( );
            for ( const auto& member : ownPersistentMembers )
            {
                auto memberType = member->Type( );
                auto typeName = CppHelper::GetMemberNullableFieldType( *member );
                auto fieldName = CppHelper::GetLongMemberFieldName( *member );
                auto returnType = typeName;
                if ( memberType > MemberInfoType::Double && memberType != MemberInfoType::RowVersion )
                {
                    returnType = Format( L"const {}&", typeName );
                }
                auto accessorName = derivedClass->Name() + CppHelper::GetMemberAccessorName( *member );
                WriteLine( L"        {} {}( ) const", returnType, accessorName );
                WriteLine( L"        {" );
                WriteLine( L"            return {};", fieldName );
                WriteLine( L"        }" );
            }
        }
    }
    

    void CppComplexDatabaseReadersGenerator::CreateWriteColumns( const ClassInfo& classInfo )
    {
        auto members = classInfo.ViewMembers( );
        auto memberCount = members.size( );
        WriteLine( L"        template<IO::StreamWriter StreamT>" );
        WriteLine( L"        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const" );
        WriteLine( L"        {" );
        WriteLine( L"            WriteColumnValue( destination, kind_);" );
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto fieldName = CppHelper::GetMemberFieldName( member );
            auto memberType = member.Type( );
            WriteLine( L"            WriteColumnValue( destination, {});", fieldName );
        }

        if ( classInfo.HasDerivedPersistentMembers( ) )
        {
            WriteLine( L"            switch( kind_ )" );
            WriteLine( L"            {" );
            auto derivedClasses = classInfo.AllDerivedClasses( );
            for ( const auto& derivedClass : derivedClasses )
            {
                if ( derivedClass->Abstract( ) == false )
                {
                    auto derivedPersistentMembers = derivedClass->DerivedPersistentMembersUntil( classInfo );
                    if ( derivedPersistentMembers.size( ) )
                    {
                        WriteLine( L"                case Data::Kind::{}:", derivedClass->Name( ) );
                        WriteLine( L"                {" );

                        for ( const auto& member : derivedPersistentMembers )
                        {
                            auto fieldName = CppHelper::GetLongMemberFieldName( *member );
                            WriteLine( L"                    WriteColumnValue( destination, {});", fieldName );
                        }
                        WriteLine( L"                }" );
                        WriteLine( L"                break;" );
                    }
                }

            }
            WriteLine( L"            }" );
        }
        WriteLine( L"        }" );
    }
}