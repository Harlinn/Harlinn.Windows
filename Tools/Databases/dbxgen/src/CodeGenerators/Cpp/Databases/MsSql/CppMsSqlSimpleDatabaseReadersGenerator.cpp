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
#include "CodeGenerators/Databases/MsSql/MsSqlHelper.h"

namespace Harlinn::Tools::DbXGen::CodeGenerators::Cpp::Databases::MsSql
{
    using namespace Harlinn::Tools::DbXGen::Metadata;
    using namespace Harlinn::Tools::DbXGen::CodeGenerators::Databases::MsSql;

    void CppMsSqlSimpleDatabaseReadersGenerator::Run( )
    {
        const auto& model = Model( );
        const auto& classes = model.Classes( );
        auto classCount = classes.size( );
        const auto& dataTypesOptions = Options( ).Owner( ).Owner( ).Owner( ).Data( ).DataTypes( );

        auto headerGuard = CppHelper::GetHeaderGuard( Filename( ) );
        auto nspace = Options( ).Namespace( L"::" );
        WriteLine( L"#pragma once" );
        WriteLine( L"#ifndef {}", headerGuard );
        WriteLine( L"#define {}", headerGuard );
        WriteLine( );
        WriteLine( "#include <HODBC.h>" );
        WriteLine( "#include <HCCData.h>" );
        WriteLine( "#include \"Types/DataTypes.h\"" );
        WriteLine( );

        WriteLine( );
        WriteLine( L"namespace {}", nspace );
        WriteLine( L"{" );
        WriteLine( L"    using namespace Harlinn;" );
        WriteLine( L"    using namespace Harlinn::ODBC;" );
        WriteLine( L"    using namespace Harlinn::Common::Core;" );
        WriteLine( );

        CreateBaseClass( );

        for ( size_t i = 0; i < classCount; i++ )
        {
            const auto& classInfo = *classes[ i ];
            CreateColumnDataType( classInfo );
        }
        WriteLine( L"}" );
        WriteLine( L"#endif" );

        Flush( );
    }

    void CppMsSqlSimpleDatabaseReadersGenerator::CreateBaseClass( )
    {

        WriteLine( L"    class BaseColumnData" );
        WriteLine( L"    {" );
        WriteLine( L"    public:" );
        WriteLine( L"        using Kind = Types::Kind;" );
        WriteLine( L"        virtual ~BaseColumnData( ) = default;" );
        WriteLine( L"        virtual Kind GetKind() const = 0;" );
        WriteLine( L"        void ReadUnboundData( const ODBC::Statement& statement )" );
        WriteLine( L"        {" );
        WriteLine( L"        }" );
        WriteLine( L"    protected:" );
        WriteLine( L"        static void ThrowBoundsExceededException( )" );
        WriteLine( L"        {" );
        WriteLine( L"            throw Exception( L\"Bounds exceeded.\" );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Assign( const WideString& str, WideString& destination, SQLLEN& lengthOrNullIndicator )" );
        WriteLine( L"        {" );
        WriteLine( L"            auto strLength = str.Length( );" );
        WriteLine( L"            destination = str;" );
        WriteLine( L"            lengthOrNullIndicator = static_cast< SQLLEN >( strLength );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Assign( const std::vector<Byte>& data, std::vector<Byte>& destination, SQLLEN& lengthOrNullIndicator )" );
        WriteLine( L"        {" );
        WriteLine( L"            auto dataLength = data.size( );" );
        WriteLine( L"            destination = data;" );
        WriteLine( L"            lengthOrNullIndicator = static_cast< SQLLEN >( dataLength );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, bool& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindBooleanColumn( fieldId, reinterpret_cast< bool* >( &value ), nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBBoolean& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindBooleanColumn( fieldId, reinterpret_cast< bool* >( value.data() ), value.Indicator() );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, SByte& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindSByteColumn( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBSByte& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindSByteColumn( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, Byte& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindByteColumn( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBByte& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindByteColumn( fieldId, value.data(), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, Int16& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt16Column( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBInt16& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt16Column( fieldId, value.data(), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, UInt16& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindUInt16Column( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBUInt16& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindUInt16Column( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, Int32& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt32Column( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBInt32& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt32Column( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, UInt32& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindUInt32Column( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBUInt32& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindUInt32Column( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, Int64& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt64Column( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBInt64& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt64Column( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, UInt64& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindUInt64Column( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBUInt64& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindUInt64Column( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, float& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindSingleColumn( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBSingle& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindSingleColumn( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, double& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindDoubleColumn( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBDouble& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindDoubleColumn( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, Currency& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( &value ), nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBCurrency& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value.data() ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DateTime& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( &value ), nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBDateTime& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value.data() ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, TimeSpan& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( &value ), nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBTimeSpan& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindInt64Column( fieldId, reinterpret_cast< Int64* >( value.data() ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, Guid& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindGuidColumn( fieldId, &value, nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, DBGuid& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindGuidColumn( fieldId, value.data( ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        template<typename T>" );
        WriteLine( L"            requires std::is_enum_v<T>" );
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, T& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            using IntegerType = std::underlying_type_t<T>;" );
        WriteLine( L"            statement.BindColumn( fieldId, NativeType::Int32, &value, sizeof( IntegerType ), nullptr );" );
        WriteLine( L"        }" );
        WriteLine( L"        template<typename T>" );
        WriteLine( L"            requires std::is_enum_v<T>" );
        WriteLine( L"        static void Bind( const ODBC::Statement & statement, SQLUSMALLINT fieldId, DBEnum<T>& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            using IntegerType = std::underlying_type_t<T>;" );
        WriteLine( L"            statement.BindColumn( fieldId, NativeType::Int32, value.data( ), sizeof( IntegerType ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        template<size_t N>" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, FixedDBWideString<N>& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindColumn( fieldId, NativeType::WideChar, value.data( ), static_cast< SQLLEN >( N * sizeof( wchar_t ) ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        template<size_t N>" );
        WriteLine( L"        static void Bind( const ODBC::Statement& statement, SQLUSMALLINT fieldId, FixedDBBinary<N>& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            statement.BindColumn( fieldId, NativeType::Binary, value.data( ), static_cast< SQLLEN >( N ), value.Indicator( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"        template<IO::StreamWriter StreamT, typename T>" );
        WriteLine( L"            requires std::is_same_v<Currency, T> || std::is_same_v<DateTime, T> || std::is_same_v<TimeSpan, T> || std::is_same_v<Guid, T> || std::is_floating_point_v<T> || std::is_integral_v<T> || std::is_enum_v<T>" );
        WriteLine( L"        void WriteColumnValue( IO::BinaryWriter<StreamT>& destination, T value )" );
        WriteLine( L"        {" );
        WriteLine( L"            destination.Write( value );" );
        WriteLine( L"        }" );
        WriteLine( L"        template<IO::StreamWriter StreamT, typename T>" );
        WriteLine( L"            requires std::is_same_v<Currency, T> || std::is_same_v<DateTime, T> || std::is_same_v<TimeSpan, T> || std::is_same_v<Guid, T> || std::is_floating_point_v<T> || std::is_integral_v<T> || std::is_enum_v<T>" );
        WriteLine( L"        void WriteColumnValue( IO::BinaryWriter<StreamT>& destination, T value, SQLLEN nullIndicator )" );
        WriteLine( L"        {" );
        WriteLine( L"            if ( nullIndicator != SQL_NULL_DATA )" );
        WriteLine( L"            {" );
        WriteLine( L"                destination.Write( true );" );
        WriteLine( L"                destination.Write( value );" );
        WriteLine( L"            }" );
        WriteLine( L"            else" );
        WriteLine( L"            {" );
        WriteLine( L"                destination.Write( false );" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"        template<IO::StreamWriter StreamT, typename T, size_t N>" );
        WriteLine( L"        void WriteNullableColumnValue( IO::BinaryWriter<StreamT>& destination, const std::array<T, N>& value, SQLLEN lengthOrNullIndicator )" );
        WriteLine( L"        {" );
        WriteLine( L"            if ( lengthOrNullIndicator != SQL_NULL_DATA )" );
        WriteLine( L"            {" );
        WriteLine( L"                destination.Write( true );" );
        WriteLine( );
        WriteLine( L"                if constexpr ( std::is_same_v<T, Byte> )" );
        WriteLine( L"                {" );
        WriteLine( L"                    auto size = static_cast< size_t >( lengthOrNullIndicator ) * sizeof( wchar_t );" );
        WriteLine( L"                    destination.Write7BitEncoded( size );" );
        WriteLine( L"                    destination.Write( value.data( ), size );" );
        WriteLine( L"                }" );
        WriteLine( L"                else" );
        WriteLine( L"                {" );
        WriteLine( L"                    auto size = static_cast< size_t >( lengthOrNullIndicator );" );
        WriteLine( L"                    destination.WriteSize( size );" );
        WriteLine( L"                    destination.Write( value.data( ), size );" );
        WriteLine( L"                }" );
        WriteLine( );
        WriteLine( L"            }" );
        WriteLine( L"            else" );
        WriteLine( L"            {" );
        WriteLine( L"                destination.Write( false );" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"        template<IO::StreamWriter StreamT, typename T, size_t N>" );
        WriteLine( L"        void WriteColumnValue( IO::BinaryWriter<StreamT>& destination, const std::array<T, N>& value, SQLLEN length )" );
        WriteLine( L"        {" );
        WriteLine( L"            if constexpr ( std::is_same_v<T, wchar_t> )" );
        WriteLine( L"            {" );
        WriteLine( L"                auto size = static_cast< size_t >( length ) * sizeof( wchar_t );" );
        WriteLine( L"                destination.Write7BitEncoded( size );" );
        WriteLine( L"                destination.Write( value.data( ), size );" );
        WriteLine( L"            }" );
        WriteLine( L"            else" );
        WriteLine( L"            {" );
        WriteLine( L"                auto size = static_cast< size_t >( length );" );
        WriteLine( L"                destination.WriteSize( size );" );
        WriteLine( L"                destination.Write( value.data( ), size );" );
        WriteLine( L"            }" );
        WriteLine( L"        }" );
        WriteLine( L"        template<IO::StreamWriter StreamT, typename T>" );
        WriteLine( L"            requires std::is_same_v<WideString, T> || std::is_same_v<std::vector<Byte>, T> || std::is_same_v<std::optional<WideString>, T> || std::is_same_v<std::optional<std::vector<Byte>>, T>" );
        WriteLine( L"        void WriteColumnValue( IO::BinaryWriter<StreamT>& destination, const T& value )" );
        WriteLine( L"        {" );
        WriteLine( L"            destination.Write( value );" );
        WriteLine( L"        }" );
        WriteLine( L"    };" );
        WriteLine( );
        WriteLine( L"    template<typename T>" );
        WriteLine( L"        requires std::is_base_of_v<BaseColumnData, T>" );
        WriteLine( L"    class SimpleColumnDataReader : public ODBC::DataReader, public T" );
        WriteLine( L"    {" );
        WriteLine( L"    public:" );
        WriteLine( L"        using Base = ODBC::DataReader;" );
        WriteLine( L"        SimpleColumnDataReader( const ODBC::Statement* statement )" );
        WriteLine( L"            : Base( statement )" );
        WriteLine( L"        {" );
        WriteLine( L"            T::BindColumns( *statement );" );
        WriteLine( L"        }" );
        WriteLine( L"    protected:" );
        WriteLine( L"        virtual void AfterFetch( ) override" );
        WriteLine( L"        {" );
        WriteLine( L"            T::ReadUnboundData( Base::Statement( ) );" );
        WriteLine( L"        }" );
        WriteLine( L"    };" );
        WriteLine( );
    }

    void CppMsSqlSimpleDatabaseReadersGenerator::CreateColumnDataType( const ClassInfo& classInfo )
    {
        auto className = CppHelper::GetColumnDataType( classInfo );
        auto primaryKey = classInfo.PrimaryKey( );
        auto primaryKeyTypeName = CppHelper::GetMemberFieldType( *primaryKey );

        WideString baseClassName( L"BaseColumnData" );
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
            if ( classInfo.HasDescendants( ) )
            {
                WriteLine( L"        Types::Kind entityType_ = Types::Kind::Unknown;" );
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
        CreateQuery( classInfo );
        CreateFieldIds( classInfo );
        WriteLine( L"        {}( ) = default;", className );
        WriteLine( );

        WriteLine( L"        virtual Kind GetKind() const override" );
        WriteLine( L"        {" );
        WriteLine( L"            return Kind::{};", classInfo.Name( ) );
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
        CreateReadUnboundData( classInfo );
        CreateWriteColumns( classInfo );
        CreateAssignTo( classInfo );
        WriteLine( L"    };" );
        WriteLine( );
        WriteLine( L"    using Simple{}DataReader = SimpleColumnDataReader<{}ColumnData>;", classInfo.Name( ), classInfo.Name( ) );
        WriteLine( );
    }

    void CppMsSqlSimpleDatabaseReadersGenerator::CreateQuery( const ClassInfo& classInfo )
    {
        auto dllExport = Options( ).DllExport( );
        WriteLine( L"        static {} WideString BaseQuery;", dllExport );
        WriteLine( L"        static {} WideString BaseViewName;", dllExport );
        WriteLine( L"        static {} WideString ViewAliasName;", dllExport );
        WriteLine( );
    }
    void CppMsSqlSimpleDatabaseReadersGenerator::CreateFieldIds( const ClassInfo& classInfo )
    {
        auto members = MsSqlHelper::GetOwnColumnsForSelect( classInfo );
        if ( members.empty( ) == false )
        {
            if ( classInfo.IsTopLevel( ) )
            {
                size_t id = 1;
                for ( const auto& member : members )
                {
                    WriteLine( L"        static constexpr SQLUSMALLINT {}_FIELD_ID = {};", member->Name( ).ToUpper( ), id );
                    id++;
                    if( member->PrimaryKey() && classInfo.HasDescendants() )
                    { 
                        WriteLine( L"        static constexpr SQLUSMALLINT ENTITYTYPE_FIELD_ID = {};", id );
                        id++;
                    }
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

    void CppMsSqlSimpleDatabaseReadersGenerator::CreateBindColumns( const ClassInfo& classInfo )
    {
        auto members = MsSqlHelper::GetOwnColumnsForSelect( classInfo );
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

                    WriteLine( L"            Bind(statement, {}, {});", fieldId, fieldName );
                    if ( member->PrimaryKey( ) && classInfo.HasDescendants( ) )
                    {
                        WriteLine( L"            Bind(statement, ENTITYTYPE_FIELD_ID, entityType_ );" );
                    }

                }
            }
            WriteLine( L"        }" );
            WriteLine( );
        }
    }

    void CppMsSqlSimpleDatabaseReadersGenerator::CreateReadUnboundData( const ClassInfo& classInfo )
    {
        auto members = MsSqlHelper::GetOwnUnboundColumnsForSelect( classInfo );
        if ( members.empty( ) == false )
        {
            WriteLine( L"        void ReadUnboundData( const ODBC::Statement& statement )" );
            WriteLine( L"        {" );
            WriteLine( L"            Base::ReadUnboundData( statement );" );
            WriteLine( );
            for ( const auto& member : members )
            {
                auto memberType = member->Type( );
                if ( memberType == MemberInfoType::String || memberType == MemberInfoType::Binary )
                {
                    auto fieldName = CppHelper::GetMemberFieldName( *member );
                    auto fieldId = Format( L"{}_FIELD_ID", member->Name( ).ToUpper( ) );
                    if ( memberType == MemberInfoType::String )
                    {
                        if ( member->Nullable( ) )
                        {
                            WriteLine( L"            {} = statement.GetDBWideString({});", fieldName, fieldId );
                        }
                        else
                        {
                            WriteLine( L"            {} = statement.GetWideString({});", fieldName, fieldId );
                        }
                    }
                    else if ( memberType == MemberInfoType::Binary )
                    {
                        if ( member->Nullable( ) )
                        {
                            WriteLine( L"            {} = statement.GetDBBinary({});", fieldName, fieldId );
                        }
                        else
                        {
                            WriteLine( L"            {} = statement.GetBinary({});", fieldName, fieldId );
                        }
                    }
                }
            }
            WriteLine( L"        }" );
        }
    }



    void CppMsSqlSimpleDatabaseReadersGenerator::CreateAccessor( const ClassInfo& classInfo, const MemberInfo& member )
    {
        auto memberInfoType = member.Type( );
        auto fieldName = CppHelper::GetMemberFieldName( member );
        auto accessorName = CppHelper::GetMemberAccessorName( member );
        auto returnType = CppHelper::GetMemberAccessorReturnType( member );
        WriteLine( L"        {} {}( ) const", returnType, accessorName );
        WriteLine( L"        {" );
        WriteLine( L"            return {};", fieldName );
        WriteLine( L"        }" );
        if ( member.PrimaryKey( ) && classInfo.HasDescendants() )
        {
            WriteLine( L"        Types::Kind EntityType( ) const" );
            WriteLine( L"        {" );
            WriteLine( L"            return entityType_;" );
            WriteLine( L"        }" );
        }
    }
    void CppMsSqlSimpleDatabaseReadersGenerator::CreateSetter( const ClassInfo& classInfo, const MemberInfo& member )
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

    void CppMsSqlSimpleDatabaseReadersGenerator::CreateWriteColumns( const ClassInfo& classInfo )
    {
        auto members = classInfo.OwnPersistentMembers( );
        auto memberCount = members.size( );
        WriteLine( L"        template<IO::StreamWriter StreamT>" );
        WriteLine( L"        void WriteColumns( IO::BinaryWriter<StreamT>& destination ) const" );
        WriteLine( L"        {" );
        if ( classInfo.IsTopLevel( ) == false )
        {
            WriteLine( L"            Base::WriteColumns( destination );" );
        }
        else
        {
            WriteLine( L"            WriteColumnValue( destination, Types::Kind::{} );", classInfo.Name() );
        }
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto fieldName = CppHelper::GetMemberFieldName( member );
            auto memberType = member.Type( );
            WriteLine( L"            WriteColumnValue( destination, {});", fieldName );
        }
        WriteLine( L"        }" );
    }

    void CppMsSqlSimpleDatabaseReadersGenerator::CreateAssignTo( const ClassInfo& classInfo )
    {
        auto dataClassName = CppHelper::GetDataType( classInfo );
        auto members = classInfo.OwnPersistentMembers( );
        auto memberCount = members.size( );

        WriteLine( L"        void AssignTo( Types::{}& destination ) const", dataClassName );
        WriteLine( L"        {" );
        if ( classInfo.IsTopLevel( ) == false )
        {
            auto baseClass = classInfo.BaseClass( );
            auto baseDataClassName = CppHelper::GetDataType( *baseClass );
            WriteLine( L"            Base::AssignTo( static_cast<Types::{}&>( destination ) );", baseDataClassName );
        }
        for ( size_t i = 0; i < memberCount; i++ )
        {
            const auto& member = *members[ i ];
            auto fieldName = CppHelper::GetMemberFieldName( member );
            auto setterName = CppHelper::GetMemberSetterName( member );
            
            WriteLine( L"            destination.{}( {} );", setterName, fieldName );

        }
        WriteLine( L"        }" );

    }

    


}