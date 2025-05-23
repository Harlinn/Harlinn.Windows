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
#include "CodeGenerators/Cpp/CppHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp
{
    using namespace Harlinn::Tools::DbXGen::Metadata;

    void CppDataTypesGenerator::Run( )
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
        WriteLine( "#include \"Enums.h\"" );
        WriteLine( "#include <HODBC.h>" );
        WriteLine( "#include <HCCData.h>" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( L"    using namespace Harlinn;");
        WriteLine( L"    using namespace Harlinn::ODBC;" );
        WriteLine( L"    using namespace Harlinn::Common::Core;" );
        WriteLine( );

        WriteLine( L"    template<typename ObjectT, typename KeyT>" );
        WriteLine( L"        requires std::is_enum_v<ObjectT>" );
        WriteLine( L"    using BaseData = Harlinn::Common::Core::Data::BaseData<ObjectT, KeyT>;" );
        WriteLine( );
        auto dllExport = Options( ).DllExport( );
        WriteLine( L"    {} std::shared_ptr<BaseData<Kind, Guid>> DataFactory( Kind kind );", dllExport );
        WriteLine( );
        
        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateDataType( classInfo );
        }

        CreateReadDataFrom( );
        CreateWriteDataTo( );
        WriteLine( );
        WriteLine( L"}" );
        WriteLine( L"#endif" );

        Flush( );
    }

    void CppDataTypesGenerator::CreateDataType( const ClassInfo& classInfo )
    {
        auto baseClass = classInfo.BaseClass( );

        auto className = CppHelper::GetDataType( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyTypeName = CppHelper::GetMemberFieldType( *primaryKey );
        const auto& persistentMembers = classInfo.OwnPersistentMembers( );

        auto baseClassName = Format(L"BaseData<Kind, {}>", primaryKeyTypeName );
        if ( baseClass )
        {
            baseClassName = CppHelper::GetDataType( *baseClass );
        }

        WriteLine( L"    class {} : public {}", className, baseClassName );
        WriteLine( L"    {");
        WriteLine( L"    public:");
        WriteLine( L"        using Base = {};", baseClassName );
        WriteLine( L"        static constexpr Kind KIND = Kind::{};",classInfo.Name());
        WriteLine( L"    private:");
        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
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
            }
        }
        WriteLine( L"    public:");
        WriteLine( L"        {}( ) = default;", className );
        WriteLine( L"        template<IO::StreamWriter StreamT>");
        WriteLine( L"        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const");
        WriteLine( L"        {");
        WriteLine( L"            Base::WriteTo( destination );");
        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                auto memberType = member->Type( );
                auto fieldName = CppHelper::GetMemberFieldName( *member );
                if ( CppHelper::IsBindable( *member ) )
                {
                    if ( member->Nullable( ) || memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
                    {
                        WriteLine( L"            {}.WriteTo( destination );", fieldName );
                    }
                    else
                    {
                        WriteLine( L"            destination.Write({});", fieldName );
                    }
                }
                else
                {
                    WriteLine( L"            destination.Write({});", fieldName );
                }
            }
        }
        WriteLine( L"        }");
        WriteLine( L"        template<IO::StreamReader StreamT>");
        WriteLine( L"        void ReadFrom( IO::BinaryReader<StreamT>& source )");
        WriteLine( L"        {");
        WriteLine( L"            Base::ReadFrom( source );");
        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                auto memberType = member->Type( );
                auto fieldName = CppHelper::GetMemberFieldName( *member );
                if ( CppHelper::IsBindable( *member ) )
                {
                    if ( member->Nullable( ) || memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
                    {
                        WriteLine( L"            {}.ReadFrom( source );", fieldName );
                    }
                    else
                    {
                        WriteLine( L"            source.Read({});", fieldName );
                    }
                }
                else
                {
                    WriteLine( L"            source.Read({});", fieldName );
                }
            }
        }
        WriteLine( L"        }");
        WriteLine( L"        virtual [[nodiscard]] ObjectType GetObjectType( ) const noexcept override");
        WriteLine( L"        {");
        WriteLine( L"            return KIND;");
        WriteLine( L"        }");
        WriteLine( L"        virtual [[nodiscard]] bool IsOfType( ObjectType objectType ) const noexcept");
        WriteLine( L"        {");
        WriteLine( L"            if ( objectType == KIND )");
        WriteLine( L"            {");
        WriteLine( L"                return true;");
        WriteLine( L"            }");
        WriteLine( L"            return Base::IsOfType( objectType );");
        WriteLine( L"        }");
        WriteLine( L"        virtual [[nodiscard]] std::shared_ptr<BaseData> Create( ) const override");
        WriteLine( L"        {");
        WriteLine( L"            return std::make_shared<{}>( );", className );
        WriteLine( L"        }");
        WriteLine( L"        virtual void AssignTo( BaseData& target ) const override");
        WriteLine( L"        {");
        WriteLine( L"            Base::AssignTo( target );");
        WriteLine( L"            auto& dest = static_cast<{}&>( target );", className );
        WriteLine( L"        }");
        WriteLine( L"        virtual [[nodiscard]] bool IsEqualTo( const BaseData& other ) const");
        WriteLine( L"        {");
        WriteLine( L"            if ( Base::IsEqualTo( other ) )");
        WriteLine( L"            {");
        WriteLine( L"                const auto& dataObject = static_cast< const {}& >( other );", className );
        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                auto fieldName = CppHelper::GetMemberFieldName( *member );
                WriteLine( L"                if ( dataObject.{} != {} )", fieldName, fieldName );
                WriteLine( L"                {" );
                WriteLine( L"                    return false;" );
                WriteLine( L"                }" );
            }
        }
        WriteLine( L"                return true;");
        WriteLine( L"            }");
        WriteLine( L"            return false;");
        WriteLine( L"        }");
        for ( const auto& member : persistentMembers )
        {
            if ( member->PrimaryKey( ) == false )
            {
                CreateAccessor( classInfo, *member );
                CreateSetter( classInfo, *member );
            }
        }
        WriteLine( L"    };" );

    }

    void CppDataTypesGenerator::CreateAccessor( const ClassInfo& classInfo, const MemberInfo& member )
    {
        auto memberInfoType = member.Type( );
        auto fieldName = CppHelper::GetMemberFieldName( member );
        auto accessorName = CppHelper::GetMemberAccessorName( member );
        auto returnType = CppHelper::GetMemberAccessorReturnType( member );
        WriteLine( L"        {} {}( ) const", returnType, accessorName );
        WriteLine( L"        {" );
        WriteLine( L"            return {};", fieldName );
        WriteLine( L"        }" );
    }
    void CppDataTypesGenerator::CreateSetter( const ClassInfo& classInfo, const MemberInfo& member )
    {
        auto memberInfoType = member.Type( );
        auto fieldName = CppHelper::GetMemberFieldName( member );
        auto setterName = CppHelper::GetMemberSetterName( member );
        auto argumentName = CppHelper::GetInputArgumentName( member );
        auto argumentType = CppHelper::GetInputArgumentType( member );

        if ( memberInfoType == MemberInfoType::RowVersion )
        {
            argumentType = L"const Int64&";
        }

        WriteLine( L"        void {}( {} {} )", setterName, argumentType, argumentName );
        WriteLine( L"        {" );
        
        WriteLine( L"            {} = {};", fieldName, argumentName );
        
        WriteLine( L"        }" );
    }

    void CppDataTypesGenerator::CreateReadDataFrom( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        WriteLine( L"    template<IO::StreamReader StreamT>" );
        WriteLine( L"    std::shared_ptr<BaseData<Kind, Guid>> ReadDataFrom( IO::BinaryReader<StreamT>& source )" );
        WriteLine( L"    {" );
        WriteLine( L"        auto kind = source.Read<Kind>( );" );
        WriteLine( L"        auto newObject = DataFactory( kind );" );
        WriteLine( L"        switch ( kind )" );
        WriteLine( L"        {" );
        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                WriteLine( L"            case Kind::{}:", classInfo->Name( ) );
                auto className = CppHelper::GetDataType( *classInfo );
                WriteLine( L"                static_cast<{}&>(*newObject).ReadFrom( source );", className );
                WriteLine( L"                break;" );
            }
        }
        WriteLine( L"        }" );
        WriteLine( L"        return newObject;" );
        WriteLine( L"    }" );
        WriteLine( );
    }

    void CppDataTypesGenerator::CreateWriteDataTo( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );

        WriteLine( L"    template<IO::StreamWriter StreamT>");
        WriteLine( L"    void WriteDataTo( const BaseData<Kind, Guid>& data, IO::BinaryWriter<StreamT>& destination )");
        WriteLine( L"    {");
        WriteLine( L"        auto kind = data.GetObjectType( );");
        WriteLine( L"        switch ( kind )");
        WriteLine( L"        {");
        for ( const auto& classInfo : classes )
        {
            if ( classInfo->Abstract( ) == false )
            {
                WriteLine( L"            case Kind::{}:", classInfo->Name( ) );
                auto className = CppHelper::GetDataType( *classInfo );
                WriteLine( L"                static_cast<const {}&>(data).WriteTo( destination );", className );
                WriteLine( L"                break;" );
            }
        }
        WriteLine( L"        }");
        WriteLine( L"    }" );
        WriteLine( );

    }
}