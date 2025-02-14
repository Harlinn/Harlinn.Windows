#pragma once
#ifndef DBXGEN_METADATA_ENUMINFO_H_
#define DBXGEN_METADATA_ENUMINFO_H_
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

#include "MemberInfo.h"

namespace Harlinn::Tools::DbXGen::Metadata
{
    class EnumValue : public std::enable_shared_from_this<EnumValue>
    {
        std::weak_ptr<EnumInfo> owner_;
        WideString name_;
        Int64 value_ = 0;
        bool default_ = false;
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

        bool Default( ) const
        {
            return default_;
        }

        inline void Load( const XmlElement& enumValueElement );
    };

    

    class EnumInfo : public std::enable_shared_from_this<EnumInfo>
    {
        std::weak_ptr<ModelInfo> owner_;
        WideString name_;
        MemberInfoType valueType_ = MemberInfoType::Int32;
        bool flags_ = false;
        std::vector<std::shared_ptr<EnumValue>> values_;
    public:
        EnumInfo(const std::shared_ptr<ModelInfo>& owner, const WideString& name )
            : owner_( owner ), name_( name )
        { }

        std::shared_ptr<ModelInfo> Owner( ) const
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

        const std::vector<std::shared_ptr<EnumValue>>& Values( ) const
        {
            return values_;
        }
        std::vector<std::shared_ptr<EnumValue>>& Values( ) 
        {
            return values_;
        }

        std::shared_ptr<EnumValue> Default( ) const
        {
            const auto valueCount = values_.size( );
            if ( valueCount )
            {
                std::shared_ptr<EnumValue> result = values_[ 0 ];
                for ( size_t i = 0; i < valueCount; i++ )
                {
                    const auto& value = values_[ i ];
                    if ( value->Default( ) )
                    {
                        result = value;
                        break;
                    }
                }
                return result;
            }
            else
            {
                return {};
            }
        }



        void Load( const XmlElement& enumElement )
        {
            if ( enumElement.HasAttribute( L"flags" ) )
            {
                flags_ = enumElement.Read<bool>( L"flags" );
            }
            if ( enumElement.HasAttribute( L"type" ) )
            {
                auto typeName = enumElement.Read<WideString>( L"type" );
                if ( typeName == L"SByte" )
                {
                    valueType_ = MemberInfoType::SByte;
                }
                else if ( typeName == L"Byte" )
                {
                    valueType_ = MemberInfoType::Byte;
                }
                else if ( typeName == L"Int16" )
                {
                    valueType_ = MemberInfoType::Int16;
                }
                else if ( typeName == L"UInt16" )
                {
                    valueType_ = MemberInfoType::UInt16;
                }
                else if ( typeName == L"Int32" )
                {
                    valueType_ = MemberInfoType::Int32;
                }
                else if ( typeName == L"UInt32" )
                {
                    valueType_ = MemberInfoType::UInt32;
                }
                else if ( typeName == L"Int64" )
                {
                    valueType_ = MemberInfoType::Int64;
                }
                else if ( typeName == L"UInt64" )
                {
                    valueType_ = MemberInfoType::UInt64;
                }
            }

            auto self = shared_from_this( );
            auto valueList = enumElement.ElementsByTagName( L"value" );
            for ( auto enumValueElement : valueList )
            {
                auto name = enumValueElement.Read<WideString>( L"name" );
                auto enumValue = std::make_shared<EnumValue>( self, name );
                enumValue->Load( enumValueElement );
                values_.emplace_back( enumValue );
                
            }


        }


    };

    inline void EnumValue::Load( const XmlElement& enumValueElement )
    {
        if ( enumValueElement.HasAttribute( L"default" ) )
        {
            default_ = enumValueElement.Read<bool>( L"default" );
        }

        if ( enumValueElement.HasAttribute( L"value" ) )
        {
            auto value = enumValueElement.Read<WideString>( L"value" );
            if ( value.StartsWith( L"0x" ) )
            {
                auto intValue = Parse<Int64>( value.data( ) + 2, 16 );
                value_ = intValue;
            }
            else if ( value.StartsWith( L"0" ) && value.Length() > 1 )
            {
                auto intValue = Parse<Int64>( value.data( ) + 1, 8 );
                value_ = intValue;
            }
            else 
            {
                auto intValue = Parse<Int64>( value );
                value_ = intValue;
            }
        }
        else
        {
            auto owner = Owner( );
            const auto& values = owner->Values( );
            if ( values.empty( ) )
            {
                value_ = 0;
            }
            else
            {
                value_ = values.back( )->Value( ) + 1;
            }
        }
    }



}

#endif
