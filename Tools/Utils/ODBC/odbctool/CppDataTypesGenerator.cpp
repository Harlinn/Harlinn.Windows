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
    void CppDataTypesGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );

        auto headerGuard = CppHelper::GetHeaderGuard( Filename( ) );
        auto nspace = CppHelper::GetNamespace( model, Filename( ) );
        WriteLine( L"#pragma once" );
        WriteLine( L"#ifndef {}", headerGuard );
        WriteLine( L"#define {}", headerGuard );
        WriteLine( );
        WriteLine( "#include \"Data/Enums.h\"" );
        WriteLine( "#include <HODBC.h>" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( L"    using namespace Harlinn;");
        WriteLine( L"    using namespace Harlinn::ODBC;" );
        WriteLine( L"    using namespace Harlinn::Common::Core;" );
        WriteLine( );

        CreateBaseClass( );

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateDataType( classInfo );
        }

        WriteLine( L"}" );
        WriteLine( L"#endif" );

        Flush( );
    }

    void CppDataTypesGenerator::CreateBaseClass( )
    {
        WriteLine( L"    class BaseColumnData" );
        WriteLine( L"    {" );
        WriteLine( L"    public:" );
        WriteLine( L"        virtual ~BaseColumnData( ) = default;" );
        WriteLine( L"        virtual Kind GetKind() const = 0;" );
        WriteLine( L"    protected:" );
        WriteLine( L"        static void ThrowBoundsExceededException( )");
        WriteLine( L"        {");
        WriteLine( L"            throw Exception( L\"Bounds exceeded.\" );");
        WriteLine( L"        }");
        WriteLine( L"        template<size_t N>");
        WriteLine( L"        static void Assign( const WideString& str, std::array<wchar_t, N>& destination, SQLLEN& lengthOrNullIndicator )");
        WriteLine( L"        {");
        WriteLine( L"            auto strLength = str.Length( );");
        WriteLine( L"            if ( strLength > N - 1 )");
        WriteLine( L"            {");
        WriteLine( L"                ThrowBoundsExceededException( );");
        WriteLine( L"            }");
        WriteLine( L"            wmemcpy_s( destination.data( ), N, str.data( ), strLength );");
        WriteLine( L"            lengthOrNullIndicator = static_cast< SQLLEN >( strLength );");
        WriteLine( L"        }");
        WriteLine( L"        static void Assign( const WideString& str, WideString& destination, SQLLEN& lengthOrNullIndicator )");
        WriteLine( L"        {");
        WriteLine( L"            auto strLength = str.Length( );");
        WriteLine( L"            destination = str;");
        WriteLine( L"            lengthOrNullIndicator = static_cast< SQLLEN >( strLength );");
        WriteLine( L"        }");
        WriteLine( L"        template<size_t N>");
        WriteLine( L"        static void Assign( const std::vector<Byte>& data, std::array<Byte, N>& destination, SQLLEN& lengthOrNullIndicator )");
        WriteLine( L"        {");
        WriteLine( L"            auto dataLength = data.size( );");
        WriteLine( L"            if ( dataLength > N )");
        WriteLine( L"            {");
        WriteLine( L"                ThrowBoundsExceededException( );");
        WriteLine( L"            }");
        WriteLine( L"            memcpy_s( destination.data( ), N, data.data( ), dataLength );");
        WriteLine( L"            lengthOrNullIndicator = static_cast< SQLLEN >( dataLength );");
        WriteLine( L"        }");
        WriteLine( L"        static void Assign( const std::vector<Byte>& data, std::vector<Byte>& destination, SQLLEN& lengthOrNullIndicator )");
        WriteLine( L"        {");
        WriteLine( L"            auto dataLength = data.size( );");
        WriteLine( L"            destination = data;");
        WriteLine( L"            lengthOrNullIndicator = static_cast< SQLLEN >( dataLength );");
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, bool* value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindBooleanColumn( fieldId, reinterpret_cast< Byte* >( value ), lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, SByte * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindSByteColumn( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Byte * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindByteColumn( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Int16 * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindInt16Column( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, UInt16 * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindUInt16Column( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Int32 * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindInt32Column( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, UInt32 * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindUInt32Column( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Int64 * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindInt64Column( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, UInt64 * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindUInt64Column( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, float* value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindSingleColumn( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, double* value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindDoubleColumn( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Currency * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value ), lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, DateTime * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value ), lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, TimeSpan * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value ), lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, Guid * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindGuidColumn( fieldId, value, lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        template<typename T>");
        WriteLine( L"            requires std::is_enum_v<T>");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, T * value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            using IntegerType = std::underlying_type_t<T>;");
        WriteLine( L"            Bind( statement, fieldId, reinterpret_cast< IntegerType* >( value ), lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        template<size_t N>");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, std::array<wchar_t, N>*value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindColumn( fieldId, NativeType::WideChar, value->data( ), static_cast< SQLLEN >( N * sizeof( wchar_t ) ), lengthOrNullIndicator );");
        WriteLine( L"        }");
        WriteLine( L"        template<size_t N>");
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, std::array<Byte, N>*value, SQLLEN * lengthOrNullIndicator = nullptr )");
        WriteLine( L"        {");
        WriteLine( L"            statement.BindColumn( fieldId, NativeType::Binary, value->data( ), static_cast< SQLLEN >( N ), lengthOrNullIndicator );");
        WriteLine( L"        }" );

        WriteLine( L"    };" );
        WriteLine( );
    }


    void CppDataTypesGenerator::CreateDataType( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetColumnDataType( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyTypeName = CppHelper::GetMemberFieldType( *primaryKey );

        WideString baseClassName = L"BaseColumnData";
        if ( classInfo.IsTopLevel( ) == false )
        {
            auto baseClass = classInfo.BaseClass( );
            baseClassName = CppHelper::GetColumnDataType( *baseClass );
        }

        WriteLine( L"    class {} : public {}", className, baseClassName );
        WriteLine( L"    {" );
        if ( classInfo.IsTopLevel( ) )
        {
            
            auto fieldName = CppHelper::GetMemberFieldName( *primaryKey );
            if ( CppHelper::MemberFieldRequiresDefaultValue( *primaryKey ) )
            {
                auto defaultValue = CppHelper::GetDefaultValue( *primaryKey );
                WriteLine( L"        {} {} = {};", primaryKeyTypeName, fieldName, defaultValue );
            }
            else
            {
                WriteLine( L"        {} {};", primaryKeyTypeName, fieldName );
            }
        }

        const auto& persistentMembers = classInfo.OwnPersistentMembers( );
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

        WriteLine( L"    public:" );
        WriteLine( L"        using Base = {};", baseClassName );
        WriteLine( );
        CreateFieldNames( classInfo );
        CreateFieldIds( classInfo );
        WriteLine( L"        {}( ) = default;", className );
        WriteLine( );

        WriteLine( L"        virtual Kind GetKind() const override" );
        WriteLine( L"        {" );
        WriteLine( L"            return Kind::{};", classInfo.Name() );
        WriteLine( L"        }" );
        WriteLine( );

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
        CreateBindColumns( classInfo );

        WriteLine( L"    };" );
        WriteLine( );

    }

    void CppDataTypesGenerator::CreateFieldNames( const ClassInfo& classInfo )
    {
        auto fieldNames = SqlServerHelper::GetColumnNamesForSelect( classInfo );
        WriteLine( L"        static constexpr std::wstring_view FieldNames = L\"{}\";", fieldNames );
        auto viewName = SqlServerHelper::GetViewName( classInfo );
        WriteLine( L"        static constexpr std::wstring_view ViewName = L\"{}\";", viewName );
        WriteLine( );
    }
    void CppDataTypesGenerator::CreateFieldIds( const ClassInfo& classInfo )
    {
        auto members = SqlServerHelper::GetOwnColumnsForSelect( classInfo );
        if ( members.empty( ) == false )
        {
            if ( classInfo.IsTopLevel( ) )
            {
                size_t id = 1;
                for ( const auto& member : members )
                {
                    WriteLine( L"        static constexpr SQLUSMALLINT {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                }
            }
            else
            {
                auto baseClass = classInfo.BaseClass( );
                size_t id = 1;
                while ( baseClass )
                {
                    id += baseClass->OwnPersistentMembers( ).size( );
                    baseClass = baseClass->BaseClass( );
                }

                for ( const auto& member : members )
                {
                    WriteLine( L"        static constexpr SQLUSMALLINT {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                }
            }
            WriteLine( );
        }
    }

    void CppDataTypesGenerator::CreateBindColumns( const ClassInfo& classInfo )
    {
        auto members = SqlServerHelper::GetOwnColumnsForSelect( classInfo );
        if ( members.empty( ) == false )
        {
            WriteLine( L"        void BindColumns( const ODBC::Statement& statement )" );
            WriteLine( L"        {" );
            if ( classInfo.IsTopLevel( ) == false )
            {
                WriteLine( L"            Base::BindColumns( statement );" );
                WriteLine( );
            }
            for ( const auto& member : members )
            {
                if ( CppHelper::IsBindable( *member ) )
                {
                    auto fieldName = CppHelper::GetMemberFieldName( *member );
                    auto fieldId = Format( L"{}_FIELD_ID", member->Name( ).ToUpper( ) );

                    if ( CppHelper::RequiresIndicator( *member ) )
                    {
                        auto indicatorName = CppHelper::GetMemberIndicatorName( *member );
                        WriteLine( L"            Bind(statement, {}, &{}, &{});", fieldId, fieldName, indicatorName );
                    }
                    else
                    {
                        WriteLine( L"            Bind(statement, {}, &{});", fieldId, fieldName );
                    }
                    
                }

                    
                    
            }
            WriteLine( L"        }" );
            WriteLine( );
        }
    }



    void CppDataTypesGenerator::CreateAccessor( const ClassInfo& classInfo, const MemberInfo& member )
    {
        auto memberInfoType = member.Type( );
        auto fieldName = CppHelper::GetMemberFieldName( member );
        auto accessorName = CppHelper::GetMemberAccessorName( member );
        auto returnType = CppHelper::GetMemberAccessorReturnType( member );
        WriteLine( L"        {} {}( ) const", returnType, accessorName );
        WriteLine( L"        {" );
        if ( memberInfoType == MemberInfoType::String )
        {
            if ( CppHelper::IsBindable( member ) )
            {
                auto indicatorName = CppHelper::GetMemberIndicatorName( member );
                WriteLine( L"            if({} != SQL_NULL_DATA)", indicatorName );
                WriteLine( L"            {" );
                WriteLine( L"                return std::wstring_view({}.data(),static_cast<size_t>( {} ));", fieldName, indicatorName );
                WriteLine( L"            }" );
                WriteLine( L"            return {};" );
            }
            else
            {
                WriteLine( L"            return {};", fieldName );
            }
        }
        else if ( memberInfoType == MemberInfoType::Binary )
        {
            if ( CppHelper::IsBindable( member ) )
            {
                auto indicatorName = CppHelper::GetMemberIndicatorName( member );
                WriteLine( L"            if({} != SQL_NULL_DATA)", indicatorName );
                WriteLine( L"            {" );
                WriteLine( L"                return std::span<Byte>({}.data(),static_cast<size_t>( {} ));", fieldName, indicatorName );
                WriteLine( L"            }" );
                WriteLine( L"            return {};" );
            }
            else
            {
                WriteLine( L"            return {};", fieldName );
            }
        }
        else
        {
            WriteLine( L"            return {};", fieldName );
        }
        WriteLine( L"        }" );
    }
    void CppDataTypesGenerator::CreateSetter( const ClassInfo& classInfo, const MemberInfo& member )
    {
        auto memberInfoType = member.Type( );
        auto fieldName = CppHelper::GetMemberFieldName( member );
        auto setterName = CppHelper::GetMemberSetterName( member );
        auto argumentName = CppHelper::GetInputArgumentName( member );
        auto argumentType = CppHelper::GetInputArgumentType( member );

        WriteLine( L"        void {}( {} {} )", setterName, argumentType, argumentName );
        WriteLine( L"        {" );
        if ( memberInfoType == MemberInfoType::String || memberInfoType == MemberInfoType::Binary )
        {
            auto indicatorName = CppHelper::GetMemberIndicatorName( member );
            WriteLine( L"            Assign({}, {}, {});", argumentName, fieldName, indicatorName );
        }
        else
        {
            WriteLine( L"            {} = {};", fieldName, argumentName );
        }
        WriteLine( L"        }" );
    }

}