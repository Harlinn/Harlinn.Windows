#pragma once
#ifndef HARLINN_AI_HAITENSOR_H_
#define HARLINN_AI_HAITENSOR_H_

#include "HAIMetadata.h"

namespace Harlinn::AI::Tensors
{

    class Value : public std::enable_shared_from_this<Value>
    { 
    public:
        using Base = std::enable_shared_from_this<Value>;
        using TypeInfoBase = Meta::TypeInfoBase;
    private:
        std::shared_ptr<TypeInfoBase> typeInfo_;
    public:
        Value( const std::shared_ptr<TypeInfoBase>& typeInfo )
            : typeInfo_( typeInfo )
        { 
            assert( typeInfo_ != nullptr );
        }
        Value( std::shared_ptr<TypeInfoBase>&& typeInfo )
            : typeInfo_( std::move( typeInfo ) )
        {
            assert( typeInfo_ != nullptr );
        }

        const std::shared_ptr<TypeInfoBase>& TypeInfo( ) const noexcept
        {
            return typeInfo_;
        }
    };

    /// <summary>
    /// Holds tensor data and the metadata defining 
    /// the shape of the tensor.
    /// </summary>
    class Tensor : public Value
    {
    public:
        using Base = Value;
        using TensorTypeAndShapeInfo = Meta::TensorTypeAndShapeInfo;
    private:
        Binary data_;
    public:
        Tensor( const std::shared_ptr<TensorTypeAndShapeInfo>& typeInfo )
            : Base( typeInfo )
        { 
            auto denseBufferSize = TypeInfo( )->DenseBufferSize( );
            data_.resize( denseBufferSize );
        }

        Tensor( const std::shared_ptr<TensorTypeAndShapeInfo>& typeInfo, const Binary& tensorData )
            : Base( typeInfo ), data_( tensorData )
        {
            if ( TypeInfo( )->IsValid( tensorData ) == false )
            {
                throw ArgumentException( "tensorData" );
            }
        }

        Tensor( std::shared_ptr<TensorTypeAndShapeInfo>&& typeInfo )
            : Base( std::move( typeInfo ) )
        { 
            auto denseBufferSize = TypeInfo( )->DenseBufferSize( );
            data_.resize( denseBufferSize );
        }

        Tensor( std::shared_ptr<TensorTypeAndShapeInfo>&& typeInfo, const Binary& tensorData )
            : Base( std::move( typeInfo ) ), data_( tensorData )
        {
            if ( TypeInfo( )->IsValid( data_ ) == false )
            {
                throw ArgumentException( "tensorData" );
            }
        }

        Tensor( std::shared_ptr<TensorTypeAndShapeInfo>&& typeInfo, Binary&& tensorData )
            : Base( std::move( typeInfo ) ), data_( std::move( tensorData ) )
        {
            if ( TypeInfo( )->IsValid( data_ ) == false )
            {
                throw ArgumentException( "tensorData" );
            }
        }

        Tensor( const std::shared_ptr<TensorTypeAndShapeInfo>& typeInfo, Binary&& tensorData )
            : Base( typeInfo ), data_( std::move( tensorData ) )
        {
            if ( TypeInfo( )->IsValid( data_ ) == false )
            {
                throw ArgumentException( "tensorData" );
            }
        }

        const std::shared_ptr<TensorTypeAndShapeInfo> TypeInfo( ) const noexcept
        {
            return std::static_pointer_cast< TensorTypeAndShapeInfo >( Base::TypeInfo( ) );
        }

        const Binary& Data( ) const
        {
            return data_;
        }
        Binary& Data( )
        {
            return data_;
        }

        void Assign( const Binary& tensorData )
        {
            if ( TypeInfo( )->IsValid( tensorData ) == false )
            {
                throw ArgumentException( "tensorData" );
            }
            data_ = tensorData;
        }
    };

}

#endif
