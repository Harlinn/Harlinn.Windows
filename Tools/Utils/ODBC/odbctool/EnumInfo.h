#pragma once
#ifndef ENUMINFO_H_
#define ENUMINFO_H_

#include "MemberInfo.h"

namespace Harlinn::ODBC::Tool
{
    class EnumValue : public std::enable_shared_from_this<EnumValue>
    {
        std::weak_ptr<EnumInfo> owner_;
        WideString name_;
        Int64 value_ = 0;
    public:
        EnumValue( const std::shared_ptr<EnumInfo>& owner, const WideString& name )
            : owner_( owner ), name_( name )
        { }

        std::shared_ptr<EnumInfo> Owner( ) const
        {
            return owner_.lock( );
        }

        const WideString& Name( ) const
        {
            return name_;
        }

        Int64 Value( ) const
        {
            return value_;
        }
        void SetValue( Int64 value )
        {
            value_ = value;
        }

    };

    

    class EnumInfo : public std::enable_shared_from_this<EnumInfo>
    {
        std::weak_ptr<StorageInfo> owner_;
        WideString name_;
        MemberInfoType valueType_ = MemberInfoType::Int32;
        bool flags_ = false;
        std::vector<std::shared_ptr<EnumValue>> values_;
    public:
        EnumInfo(const std::shared_ptr<StorageInfo>& owner, const WideString& name )
            : owner_( owner ), name_( name )
        { }

        std::shared_ptr<StorageInfo> Owner( ) const
        {
            return owner_.lock( );
        }

        const WideString& Name( ) const
        {
            return name_;
        }

        MemberInfoType ValueType( ) const
        {
            return valueType_;
        }

        void SetValueType( MemberInfoType valueType )
        {
            valueType_ = valueType;
        }

        bool Flags( ) const
        {
            return flags_;
        }
        void SetFlags( bool flags )
        {
            flags_ = flags;
        }

    };



}

#endif
