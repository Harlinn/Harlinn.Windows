#pragma once
#ifndef HARLINN_AI_HAIMETADATA_H_
#define HARLINN_AI_HAIMETADATA_H_
/*
   Copyright 2024-2026 Espen Harlinn

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

#include "HAIDef.h"

namespace Harlinn::AI::Meta
{
    enum class TypeInfoType
    {
        Unknown,
        Tensor,
        Sequence,
        Map,
        Opaque,
        Sparsetensor,
        Optional
    };

    enum class TensorElementType
    {
        Undefined,
        Float,
        // maps to c type uint8_t
        UInt8,
        // maps to c type int8_t
        Int8,
        // maps to c type uint16_t
        UInt16,
        // maps to c type int16_t
        Int16,
        // maps to c type int32_t
        Int32,
        // maps to c type int64_t
        Int64,
        // maps to c++ type std::string
        String,
        Bool,
        Float16,
        // maps to c type double
        Double,
        // maps to c type uint32_t
        UInt32,
        // maps to c type uint64_t
        UInt64,
        // complex with float32 real and imaginary components
        Complex64,
        // complex with float64 real and imaginary components
        Complex128,
        // Non-IEEE floating-point format based on IEEE754 single-precision
        BFloat16,
        // Non-IEEE floating-point format based on IEEE754 single-precision
        Float8E4M3FN,
        // Non-IEEE floating-point format based on IEEE754 single-precision
        Float8E4M3FNUZ,
        // Non-IEEE floating-point format based on IEEE754 single-precision
        Float8E5M2,
        // Non-IEEE floating-point format based on IEEE754 single-precision
        Float8E5M2FNUZ,
        // maps to a pair of packed uint4 values (size == 1 byte)
        UInt4,
        // maps to a pair of packed int4 values (size == 1 byte)
        Int4,
    };


    class TypeInfoBase : public std::enable_shared_from_this<TypeInfoBase>
    {
    public:
        using Base = std::enable_shared_from_this<TypeInfoBase>;
    private:
        TypeInfoType type_;
        AnsiString name_;
    public:
        TypeInfoBase( TypeInfoType type, const AnsiString& name )
            : type_( type ), name_( name )
        {
        }
        virtual ~TypeInfoBase( ) = default;

        TypeInfoType Type( ) const noexcept
        {
            return type_;
        }
        const AnsiString& Name( ) const noexcept
        {
            return name_;
        }

        virtual bool Matches(const TypeInfoBase& other ) const
        {
            return type_ == other.type_;
        }
        bool Matches( const std::shared_ptr<TypeInfoBase>& other ) const
        {
            if ( other )
            {
                return this->Matches( *other );
            }
            return false;
        }

        template<typename T>
            requires std::is_base_of_v<TypeInfoBase,std::remove_cvref_t<T>>
        std::shared_ptr<std::remove_cvref_t<T>> As( )
        {
            return std::static_pointer_cast< std::remove_cvref_t<T> >( shared_from_this( ) );
        }
        template<typename T>
            requires std::is_base_of_v<TypeInfoBase, std::remove_cvref_t<T>>
        std::shared_ptr<const std::remove_cvref_t<T>> As( ) const
        {
            return std::static_pointer_cast< const std::remove_cvref_t<T> >( shared_from_this( ) );
        }


    };

    class TensorTypeAndShapeInfo : public TypeInfoBase
    {
    public:
        using Base = TypeInfoBase;
    private:
        TensorElementType elementType_;
        size_t elementCount_ = 0;
        std::vector<Int64> dimensions_;
        std::vector<AnsiString> symbolicDimensions_;
    public:
        TensorTypeAndShapeInfo( TypeInfoType type, const AnsiString& name, TensorElementType elementType, std::vector<Int64>&& dimensions, std::vector<AnsiString>&& symbolicDimensions )
            : Base( type, name ), elementType_( elementType ), dimensions_( std::move( dimensions ) ), symbolicDimensions_( std::move( symbolicDimensions ) )
        {
            elementCount_ = Harlinn::Math::Multiply( dimensions_ );
        }

        virtual bool Matches( const TypeInfoBase& other ) const override
        {
            auto result = Base::Matches( other );
            if ( result )
            {
                const auto& ti = static_cast< const TensorTypeAndShapeInfo& >( other );
                result = elementType_ == ti.elementType_;
                if ( result )
                {
                    result = dimensions_ == ti.dimensions_;
                }
            }
            return result;
        }

        TensorElementType ElementType( ) const noexcept
        {
            return elementType_;
        }
        size_t ElementCount( ) const noexcept
        {
            return elementCount_;
        }
        const std::vector<Int64>& Dimensions( ) const noexcept
        {
            return dimensions_;
        }
        const std::vector<AnsiString>& SymbolicDimensions( ) const noexcept
        {
            return symbolicDimensions_;
        }

        size_t DenseBufferSize( ) const
        {
            switch ( elementType_ )
            {
                case TensorElementType::Complex128:
                    return elementCount_ * sizeof( std::complex<double> );
                case TensorElementType::Int64:
                case TensorElementType::UInt64:
                case TensorElementType::Complex64:
                case TensorElementType::Double:
                    return elementCount_ * sizeof( std::complex<Int64> );
                case TensorElementType::Float:
                case TensorElementType::Int32:
                case TensorElementType::UInt32:
                    return elementCount_ * sizeof( std::complex<Int32> );
                case TensorElementType::UInt16:
                case TensorElementType::Int16:
                case TensorElementType::Float16:
                case TensorElementType::BFloat16:
                    return elementCount_ * sizeof( std::complex<Int16> );
                case TensorElementType::Bool:
                case TensorElementType::UInt8:
                case TensorElementType::Int8:
                case TensorElementType::Float8E4M3FN:
                case TensorElementType::Float8E4M3FNUZ:
                case TensorElementType::Float8E5M2:
                case TensorElementType::Float8E5M2FNUZ:
                    return elementCount_;
                case TensorElementType::UInt4:
                case TensorElementType::Int4:
                    return elementCount_ & 1 ? ( elementCount_ + 1 ) / 2 : elementCount_ / 2;
                case TensorElementType::String:
                    throw NotImplementedException( "Strings don't have a fixed size" );
                default:
                    throw NotImplementedException( "Undefined" );
            }
        }

        template<SimpleSpanLike T>
        bool IsValid( const T& tensorData ) const
        {
            auto numberOfBytes = tensorData.size( ) * sizeof( typename T::value_type );
            return numberOfBytes >= DenseBufferSize( );
        }


    };

    class MapTypeInfo : public TypeInfoBase
    {
    public:
        using Base = TypeInfoBase;
    private:
        TensorElementType keyType_;
        std::shared_ptr<TypeInfoBase> valueType_;
    public:
        MapTypeInfo( const AnsiString& name, TensorElementType keyType, const std::shared_ptr<TypeInfoBase>& valueType )
            : Base( TypeInfoType::Map, name ), keyType_( keyType ), valueType_( valueType )
        {
        }

        virtual bool Matches( const TypeInfoBase& other ) const override
        {
            auto result = Base::Matches( other );
            if ( result )
            {
                const auto& ti = static_cast< const MapTypeInfo& >( other );
                result = keyType_ == ti.keyType_;
                if ( result )
                {
                    result = valueType_->Matches( *ti.valueType_ );
                }
            }
            return result;
        }

        TensorElementType KeyType( ) const
        {
            return keyType_;
        }
        const std::shared_ptr<TypeInfoBase>& ValueType( ) const
        {
            return valueType_;
        }

    };

    class SequenceTypeInfo : public TypeInfoBase
    {
    public:
        using Base = TypeInfoBase;
    private:
        std::shared_ptr<TypeInfoBase> elementType_;
    public:
        SequenceTypeInfo( const AnsiString& name, const std::shared_ptr<TypeInfoBase>& elementType )
            : Base( TypeInfoType::Sequence, name ), elementType_( elementType )
        {
        }

        virtual bool Matches( const TypeInfoBase& other ) const override
        {
            auto result = Base::Matches( other );
            if ( result )
            {
                const auto& ti = static_cast< const SequenceTypeInfo& >( other );
                result = elementType_->Matches( *ti.elementType_ );
            }
            return result;
        }

        const std::shared_ptr<TypeInfoBase>& ElementType( ) const noexcept
        {
            return elementType_;
        }
    };

    class OptionalTypeInfo : public TypeInfoBase
    {
    public:
        using Base = TypeInfoBase;
    private:
        std::shared_ptr<TypeInfoBase> elementType_;
    public:
        OptionalTypeInfo( const AnsiString& name, const std::shared_ptr<TypeInfoBase>& elementType )
            : Base( TypeInfoType::Optional, name ), elementType_( elementType )
        {
        }

        virtual bool Matches( const TypeInfoBase& other ) const override
        {
            auto result = Base::Matches( other );
            if ( result )
            {
                const auto& ti = static_cast< const OptionalTypeInfo& >( other );
                result = elementType_->Matches( *ti.elementType_ );
            }
            return result;
        }

        const std::shared_ptr<TypeInfoBase>& ElementType( ) const noexcept
        {
            return elementType_;
        }
    };

    class OpaqueTypeInfo : public TypeInfoBase
    {
    public:
        using Base = TypeInfoBase;

        OpaqueTypeInfo( const AnsiString& name )
            : Base( TypeInfoType::Opaque, name )
        {
        }
    };

    class UnknownTypeInfo : public TypeInfoBase
    {
    public:
        using Base = TypeInfoBase;
    private:
        std::shared_ptr<TypeInfoBase> elementType_;
    public:
        UnknownTypeInfo( const AnsiString& name )
            : Base( TypeInfoType::Unknown, name )
        {
        }
    };

    /// <summary>
    /// Provides access to metadata for a Session,
    /// including the type information about the
    /// inputs and outputs for the model loaded into 
    /// the Session object.
    /// </summary>
    class Metadata : public std::enable_shared_from_this<Metadata>
    {
    public:
        using Base = std::enable_shared_from_this<Metadata>;
    private:
        AnsiString producerName_;
        AnsiString graphName_;
        AnsiString domain_;
        AnsiString description_;
        std::map<AnsiString, AnsiString> customMetadataMap_;
        Int64 version_ = 0;
        AnsiString graphDescription_;
        std::vector<std::shared_ptr<TypeInfoBase>> inputs_;
        std::vector<std::shared_ptr<TypeInfoBase>> outputs_;
        std::vector<std::shared_ptr<TypeInfoBase>> overridableInitializers_;
    public:
        Metadata( ) = default;

        const AnsiString& ProducerName( ) const noexcept
        {
            return producerName_;
        }
        void SetProducerName( const AnsiString& producerName )
        {
            producerName_ = producerName;
        }
        const AnsiString& GraphName( ) const noexcept
        {
            return graphName_;
        }
        void SetGraphName( const AnsiString& graphName )
        {
            graphName_ = graphName;
        }

        const AnsiString& Domain( ) const noexcept
        {
            return domain_;
        }
        void SetDomain( const AnsiString& domain )
        {
            domain_ = domain;
        }

        const AnsiString& Description( ) const noexcept
        {
            return description_;
        }
        void SetDescription( const AnsiString& description )
        {
            description_ = description;
        }

        const std::map<AnsiString, AnsiString>& CustomMetadataMap( ) const noexcept
        {
            return customMetadataMap_;
        }
        void SetCustomMetadataMap( const std::map<AnsiString, AnsiString>& customMetadataMap )
        {
            customMetadataMap_ = customMetadataMap;
        }
        void SetCustomMetadataMap( std::map<AnsiString, AnsiString>&& customMetadataMap )
        {
            customMetadataMap_ = std::move(customMetadataMap);
        }

        Int64 Version( ) const noexcept
        {
            return version_;
        }
        void SetVersion( Int64 version )
        {
            version_ = version;
        }

        const AnsiString& GraphDescription( ) const noexcept
        {
            return graphDescription_;
        }
        void SetGraphDescription( const AnsiString& graphDescription )
        {
            graphDescription_ = graphDescription;
        }
        const std::vector<std::shared_ptr<TypeInfoBase>>& Inputs( ) const noexcept
        {
            return inputs_;
        }
        void SetInputs( const std::vector<std::shared_ptr<TypeInfoBase>>& inputs )
        {
            inputs_ = inputs;
        }
        void SetInputs( std::vector<std::shared_ptr<TypeInfoBase>>&& inputs )
        {
            inputs_ = std::move( inputs );
        }
        const std::vector<std::shared_ptr<TypeInfoBase>>& Outputs( ) const noexcept
        {
            return outputs_;
        }
        void SetOutputs( const std::vector<std::shared_ptr<TypeInfoBase>>& outputs )
        {
            outputs_ = outputs;
        }
        void SetOutputs( std::vector<std::shared_ptr<TypeInfoBase>>&& outputs )
        {
            outputs_ = std::move( outputs );
        }

        const std::vector<std::shared_ptr<TypeInfoBase>>& OverridableInitializers( ) const noexcept
        {
            return overridableInitializers_;
        }

        void SetOverridableInitializers( const std::vector<std::shared_ptr<TypeInfoBase>>& overridableInitializers )
        {
            overridableInitializers_ = overridableInitializers;
        }
        void SetOverridableInitializers( std::vector<std::shared_ptr<TypeInfoBase>>&& overridableInitializers )
        {
            overridableInitializers_ = std::move( overridableInitializers );
        }

    };

}

#endif
