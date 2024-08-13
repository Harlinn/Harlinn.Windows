#pragma once
#ifndef MEMBERINFO_H_
#define MEMBERINFO_H_
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

#include <HODBC.h>
#include <HCCXml.h>

namespace Harlinn::ODBC::Tool
{
    using XmlElement = Harlinn::Common::Core::Xml::Dom::Element;
    
    enum class MemberInfoType
    {
        Unknown,
        Boolean,
        SByte,
        Byte,
        Int16,
        UInt16,
        Int32,
        UInt32,
        Int64,
        UInt64,
        Enum,
        Single,
        Double,
        Currency,
        DateTime,
        TimeSpan,
        Guid,
        String,
        Binary,
        Type,
        RowVersion,
        Reference,
        TimeSeries,
        Collection
    };

    class ModelInfo;
    class EnumInfo;
    
    class ClassInfo;
    using TypeInfo = ClassInfo;

    class MemberInfo : public std::enable_shared_from_this<MemberInfo>
    {
        std::weak_ptr<Tool::ClassInfo> owner_;
        Tool::MemberInfoType type_;
        WideString name_;
        WideString typeName_;
        ODBC::NativeType nativeType_;
        WideString nativeTypeName_;
        ODBC::SqlType sqlType_;
        WideString sqlTypeName_;
        bool nullable_ = false;
        bool primaryKey_ = false;
        WideString displayName_;
        WideString description_;
    protected:
        MemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, Tool::MemberInfoType type, const WideString& name, const WideString& typeName, ODBC::NativeType nativeType, const WideString& nativeTypeName, ODBC::SqlType sqlType, const WideString& sqlTypeName )
            : owner_( owner ), type_( type ), name_( name ), typeName_( typeName ), nativeType_( nativeType ), nativeTypeName_( nativeTypeName ), sqlType_( sqlType ), sqlTypeName_( sqlTypeName )
        { }
    public:
        virtual ~MemberInfo( ) = default;

        std::shared_ptr<Tool::ClassInfo> Owner( ) const
        {
            return owner_.lock();
        }

        std::shared_ptr<Tool::ModelInfo> Model( ) const;

        Tool::MemberInfoType Type( ) const
        {
            return type_;
        }
        const WideString& Name( ) const
        {
            return name_;
        }
        const WideString& TypeName( ) const
        {
            return typeName_;
        }
        ODBC::NativeType NativeType( ) const
        {
            return nativeType_;
        }
        const WideString& NativeTypeName( ) const
        {
            return nativeTypeName_;
        }
        ODBC::SqlType SqlType( ) const
        {
            return sqlType_;
        }

        virtual const WideString& SqlTypeName( ) const
        {
            return sqlTypeName_;
        }

        bool Nullable( ) const
        {
            return nullable_;
        }
        bool PrimaryKey( ) const
        {
            return primaryKey_;
        }

        virtual bool Persistent( ) const
        {
            return true;
        }


        virtual void Load( const XmlElement& memberElement );

    };



    class BooleanMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        BooleanMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Boolean, name, L"Boolean", ODBC::NativeType::Boolean, L"bool", ODBC::SqlType::Bit, L"bit" )
        { }
    };

    class SByteMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        SByteMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::SByte, name, L"SByte", ODBC::NativeType::SByte, L"SByte", ODBC::SqlType::TinyInt, L"tinyint" )
        {
        }
    };

    class ByteMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        ByteMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Byte, name, L"Byte", ODBC::NativeType::Byte, L"Byte", ODBC::SqlType::TinyInt, L"tinyint" )
        {
        }
    };

    class Int16MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        Int16MemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Int16, name, L"Int16", ODBC::NativeType::Int16, L"Int16", ODBC::SqlType::SmallInt, L"smallint" )
        {
        }
    };

    class UInt16MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        UInt16MemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::UInt16, name, L"UInt16", ODBC::NativeType::UInt16, L"UInt16", ODBC::SqlType::SmallInt, L"smallint" )
        {
        }
    };

    class Int32MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        Int32MemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Int32, name, L"Int32", ODBC::NativeType::Int32, L"Int32", ODBC::SqlType::Integer, L"int" )
        {
        }
    };

    class UInt32MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        UInt32MemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::UInt32, name, L"UInt32", ODBC::NativeType::UInt32, L"UInt32", ODBC::SqlType::Integer, L"int" )
        {
        }
    };

    class Int64MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        Int64MemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Int64, name, L"Int64", ODBC::NativeType::Int64, L"Int64", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    protected:
        Int64MemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, Tool::MemberInfoType type, const WideString& name )
            : Base( owner, type, name, L"Int64", ODBC::NativeType::Int64, L"Int64", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class UInt64MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        UInt64MemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::UInt64, name, L"UInt64", ODBC::NativeType::UInt64, L"UInt64", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class EnumMemberInfo : public MemberInfo
    {
        std::weak_ptr<EnumInfo> type_;
    public:
        using Base = MemberInfo;
        EnumMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::UInt64, name, L"UInt64", ODBC::NativeType::UInt64, L"UInt64", ODBC::SqlType::BigInt, L"bigint" )
        {
        }

        virtual void Load( const XmlElement& memberElement ) override;

    };


    class SingleMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        SingleMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Single, name, L"Single", ODBC::NativeType::Single, L"float", ODBC::SqlType::Real, L"real" )
        {
        }
    };

    class DoubleMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        DoubleMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Double, name, L"Double", ODBC::NativeType::Double, L"double", ODBC::SqlType::Float, L"float" )
        {
        }
    };

    class CurrencyMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        CurrencyMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Currency, name, L"Currency", ODBC::NativeType::Int64, L"Currency", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class DateTimeMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        DateTimeMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::DateTime, name, L"DateTime", ODBC::NativeType::Int64, L"DateTime", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class TimeSpanMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        TimeSpanMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::TimeSpan, name, L"TimeSpan", ODBC::NativeType::Int64, L"TimeSpan", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class GuidMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        GuidMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Guid, name, L"Guid", ODBC::NativeType::Guid, L"Guid", ODBC::SqlType::Guid, L"uniqueidentifier" )
        {
        }
    protected:
        GuidMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, Tool::MemberInfoType type, const WideString& name )
            : Base( owner, type, name, L"Guid", ODBC::NativeType::Guid, L"Guid", ODBC::SqlType::Guid, L"uniqueidentifier" )
        {
        }
    };

    class StringMemberInfo : public MemberInfo
    {
        size_t size_ = 127;
    public:
        using Base = MemberInfo;
        StringMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::String, name, L"String", ODBC::NativeType::WideChar, L"WideString", ODBC::SqlType::Guid, L"nvarchar" )
        {
        }

        virtual void Load( const XmlElement& memberElement ) override;
    };

    class BinaryMemberInfo : public MemberInfo
    {
        size_t size_ = 0;
    public:
        using Base = MemberInfo;
        BinaryMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Binary, name, L"Binary", ODBC::NativeType::Binary, L"std::vector<Byte>", ODBC::SqlType::VarBinary, L"varbinary" )
        {
        }

        virtual void Load( const XmlElement& memberElement ) override;
    };


    class RowVersionMemberInfo : public Int64MemberInfo
    {
    public:
        using Base = Int64MemberInfo;
        RowVersionMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::RowVersion, name )
        {
        }
    };

    class ReferenceMemberInfo : public GuidMemberInfo
    {
        std::weak_ptr<ClassInfo> type_;
    public:
        using Base = GuidMemberInfo;
        ReferenceMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Reference, name )
        {
        }

        virtual void Load( const XmlElement& memberElement ) override;
    protected:
        ReferenceMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, Tool::MemberInfoType type, const WideString& name )
            : Base( owner, type, name )
        {
        }
    };

    class TimeSeriesMemberInfo : public ReferenceMemberInfo
    {
        WideString propertyName_;
        WideString propertyTypeName_;
        bool propertyNullable_;
    public:
        using Base = ReferenceMemberInfo;
        TimeSeriesMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::TimeSeries, name )
        {
        }

        virtual void Load( const XmlElement& memberElement ) override;
    };


    class CollectionMemberInfo : public MemberInfo
    {
        std::weak_ptr<ClassInfo> type_;
        WideString referenceName_;
    public:
        using Base = MemberInfo;
        CollectionMemberInfo( const std::shared_ptr<Tool::ClassInfo>& owner, const WideString& name )
            : Base( owner, Tool::MemberInfoType::Collection, name, L"Guid", ODBC::NativeType::Guid, L"Guid", ODBC::SqlType::Guid, L"uniqueidentifier" )
        {
        }
        virtual bool Persistent( ) const override
        {
            return false;
        }

        virtual void Load( const XmlElement& memberElement ) override;
    };


}


#endif


