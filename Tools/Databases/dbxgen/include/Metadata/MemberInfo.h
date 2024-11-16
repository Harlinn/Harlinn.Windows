#pragma once
#ifndef DBXGEN_METADATA_MEMBERINFO_H_
#define DBXGEN_METADATA_MEMBERINFO_H_
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
#include <HCCEnvironment.h>

namespace Harlinn::Tools::DbXGen
{
    using namespace Harlinn::Common::Core;
    using namespace Harlinn::ODBC;
}

namespace Harlinn::Tools::DbXGen::Metadata
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
        std::weak_ptr<Metadata::ClassInfo> owner_;
        Metadata::MemberInfoType type_;
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
        MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, Metadata::MemberInfoType type, const WideString& name, const WideString& typeName, ODBC::NativeType nativeType, const WideString& nativeTypeName, ODBC::SqlType sqlType, const WideString& sqlTypeName )
            : owner_( owner ), type_( type ), name_( name ), typeName_( typeName ), nativeType_( nativeType ), nativeTypeName_( nativeTypeName ), sqlType_( sqlType ), sqlTypeName_( sqlTypeName )
        { }
        MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, Metadata::MemberInfoType type, const wchar_t* name, const wchar_t* typeName, ODBC::NativeType nativeType, const wchar_t* nativeTypeName, ODBC::SqlType sqlType, const wchar_t* sqlTypeName )
            : owner_( owner ), type_( type ), name_( name ), typeName_( typeName ), nativeType_( nativeType ), nativeTypeName_( nativeTypeName ), sqlType_( sqlType ), sqlTypeName_( sqlTypeName )
        {
        }
        MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, Metadata::MemberInfoType type, const WideString& name, const wchar_t* typeName, ODBC::NativeType nativeType, const wchar_t* nativeTypeName, ODBC::SqlType sqlType, const wchar_t* sqlTypeName )
            : owner_( owner ), type_( type ), name_( name ), typeName_( typeName ), nativeType_( nativeType ), nativeTypeName_( nativeTypeName ), sqlType_( sqlType ), sqlTypeName_( sqlTypeName )
        {
        }
    public:
        virtual ~MemberInfo( ) = default;

        std::shared_ptr<Metadata::ClassInfo> Owner( ) const
        {
            return owner_.lock();
        }

        std::shared_ptr<Metadata::ModelInfo> Model( ) const;

        Metadata::MemberInfoType Type( ) const
        {
            return type_;
        }

        bool IsReferenceType( ) const
        {
            return type_ == Metadata::MemberInfoType::Reference || type_ == Metadata::MemberInfoType::TimeSeries;
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

        virtual void Validate( ) const;

    };



    class BooleanMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        BooleanMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Boolean, name, L"Boolean", ODBC::NativeType::Boolean, L"bool", ODBC::SqlType::Bit, L"bit" )
        { }
    };

    class SByteMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        SByteMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::SByte, name, L"SByte", ODBC::NativeType::SByte, L"SByte", ODBC::SqlType::TinyInt, L"tinyint" )
        {
        }
    };

    class ByteMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        ByteMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Byte, name, L"Byte", ODBC::NativeType::Byte, L"Byte", ODBC::SqlType::TinyInt, L"tinyint" )
        {
        }
    };

    class Int16MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        Int16MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Int16, name, L"Int16", ODBC::NativeType::Int16, L"Int16", ODBC::SqlType::SmallInt, L"smallint" )
        {
        }
    };

    class UInt16MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        UInt16MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::UInt16, name, L"UInt16", ODBC::NativeType::UInt16, L"UInt16", ODBC::SqlType::SmallInt, L"smallint" )
        {
        }
    };

    class Int32MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        Int32MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Int32, name, L"Int32", ODBC::NativeType::Int32, L"Int32", ODBC::SqlType::Integer, L"int" )
        {
        }
    };

    class UInt32MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        UInt32MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::UInt32, name, L"UInt32", ODBC::NativeType::UInt32, L"UInt32", ODBC::SqlType::Integer, L"int" )
        {
        }
    };

    class Int64MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        Int64MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Int64, name, L"Int64", ODBC::NativeType::Int64, L"Int64", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    protected:
        Int64MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, Metadata::MemberInfoType type, const WideString& name )
            : Base( owner, type, name, L"Int64", ODBC::NativeType::Int64, L"Int64", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class UInt64MemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        UInt64MemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::UInt64, name, L"UInt64", ODBC::NativeType::UInt64, L"UInt64", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class EnumMemberInfo : public MemberInfo
    {
        std::weak_ptr<EnumInfo> type_;
    public:
        using Base = MemberInfo;
        EnumMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Enum, name, L"Int32", ODBC::NativeType::Int32, L"Int32", ODBC::SqlType::Integer, L"int" )
        {
        }

        std::shared_ptr<EnumInfo> EnumType( ) const
        {
            return type_.lock( );
        }

        virtual void Load( const XmlElement& memberElement ) override;

        virtual void Validate( ) const override;

    };


    class SingleMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        SingleMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Single, name, L"Single", ODBC::NativeType::Single, L"float", ODBC::SqlType::Real, L"real" )
        {
        }
    };

    class DoubleMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        DoubleMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Double, name, L"Double", ODBC::NativeType::Double, L"double", ODBC::SqlType::Float, L"float" )
        {
        }
    };

    class CurrencyMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        CurrencyMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Currency, name, L"Currency", ODBC::NativeType::Int64, L"Currency", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class DateTimeMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        DateTimeMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::DateTime, name, L"DateTime", ODBC::NativeType::Int64, L"DateTime", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class TimeSpanMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        TimeSpanMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::TimeSpan, name, L"TimeSpan", ODBC::NativeType::Int64, L"TimeSpan", ODBC::SqlType::BigInt, L"bigint" )
        {
        }
    };

    class GuidMemberInfo : public MemberInfo
    {
    public:
        using Base = MemberInfo;
        GuidMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Guid, name, L"Guid", ODBC::NativeType::Guid, L"Guid", ODBC::SqlType::Guid, L"uniqueidentifier" )
        {
        }
    protected:
        GuidMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, Metadata::MemberInfoType type, const WideString& name )
            : Base( owner, type, name, L"Guid", ODBC::NativeType::Guid, L"Guid", ODBC::SqlType::Guid, L"uniqueidentifier" )
        {
        }
    };

    class StringMemberInfo : public MemberInfo
    {
        size_t size_ = 127;
    public:
        using Base = MemberInfo;
        StringMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::String, name, L"String", ODBC::NativeType::WideChar, L"WideString", ODBC::SqlType::Guid, L"nvarchar" )
        {
        }

        size_t Size( ) const
        {
            return size_;
        }

        virtual void Load( const XmlElement& memberElement ) override;
    };

    class BinaryMemberInfo : public MemberInfo
    {
        size_t size_ = 0;
    public:
        using Base = MemberInfo;
        BinaryMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Binary, name, L"Binary", ODBC::NativeType::Binary, L"std::vector<Byte>", ODBC::SqlType::VarBinary, L"varbinary" )
        {
        }

        size_t Size( ) const
        {
            return size_;
        }

        virtual void Load( const XmlElement& memberElement ) override;
    };


    class RowVersionMemberInfo : public Int64MemberInfo
    {
    public:
        using Base = Int64MemberInfo;
        RowVersionMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::RowVersion, name )
        {
        }
    };


    class CollectionMemberInfo;
    class ReferenceMemberInfo : public GuidMemberInfo
    {
        std::weak_ptr<ClassInfo> type_;
        WideString member_;
        mutable std::weak_ptr<CollectionMemberInfo> collectionMember_;
        mutable std::weak_ptr<ReferenceMemberInfo> referencingMember_;
        mutable std::optional<bool> isOneToMany_;
        mutable std::optional<bool> isOneToOne_;
    public:
        using Base = GuidMemberInfo;
        ReferenceMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Reference, name )
        {
        }

        std::shared_ptr<ClassInfo> ReferencedType( ) const
        {
            return type_.lock( );
        }

        std::shared_ptr<CollectionMemberInfo> ReferencingCollectionMember( ) const;
        std::shared_ptr<ReferenceMemberInfo> ReferencingReferenceMember( ) const;

        bool IsOneToMany( ) const;
        bool IsOneToOne( ) const;


        virtual void Load( const XmlElement& memberElement ) override;

        virtual void Validate( ) const override;
    protected:
        ReferenceMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, Metadata::MemberInfoType type, const WideString& name )
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
        TimeSeriesMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::TimeSeries, name )
        {
        }

        virtual void Load( const XmlElement& memberElement ) override;
    };


    class CollectionMemberInfo : public MemberInfo
    {
        std::weak_ptr<ClassInfo> type_;
        WideString member_;
        mutable std::weak_ptr<ReferenceMemberInfo> referencingReferenceMember_;
        mutable std::weak_ptr<CollectionMemberInfo> referencingCollectionMember_;
        mutable std::optional<bool> isManyToMany_;
        mutable std::optional<bool> isOneToMany_;
        bool aggregated_ = false;
    public:
        using Base = MemberInfo;
        CollectionMemberInfo( const std::shared_ptr<Metadata::ClassInfo>& owner, const WideString& name )
            : Base( owner, Metadata::MemberInfoType::Collection, name, L"Guid", ODBC::NativeType::Guid, L"Guid", ODBC::SqlType::Guid, L"uniqueidentifier" )
        {
        }

        std::shared_ptr<ClassInfo> ReferencedType( ) const
        {
            return type_.lock( );
        }

        virtual bool Persistent( ) const override
        {
            return false;
        }

        bool Aggregated( ) const
        {
            return aggregated_;
        }

        std::shared_ptr<ReferenceMemberInfo> ReferencingReferenceMember( ) const;
        std::shared_ptr<CollectionMemberInfo> ReferencingCollectionMember( ) const;

        bool IsManyToMany( ) const;
        bool IsOneToMany( ) const;

        virtual void Load( const XmlElement& memberElement ) override;

        virtual void Validate( ) const override;

    };


}


#endif


