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

#include "pch.h"
#include "HAIONNX.h"

namespace Harlinn::AI::ONNX
{
    std::shared_ptr<TypeInfo> CreateTypeInfo( const AnsiString& name, const Ort::TypeInfo& ortTypeInfo )
    {
        std::shared_ptr<TypeInfo> result;
        auto onnxType = ortTypeInfo.GetONNXType( );
        switch ( onnxType )
        {
            case ONNX_TYPE_UNKNOWN:
            {
                result = std::make_shared<UnknownTypeInfo>( name );
            }
            break;
            case ONNX_TYPE_TENSOR:
            case ONNX_TYPE_SPARSETENSOR:
            {
                auto tensorTypeAndShapeInfo = ortTypeInfo.GetTensorTypeAndShapeInfo( );
                auto elementType = tensorTypeAndShapeInfo.GetElementType( );
                auto elementCount = tensorTypeAndShapeInfo.GetElementCount( );
                auto dimensions = tensorTypeAndShapeInfo.GetShape( );
                auto dimensionCount = tensorTypeAndShapeInfo.GetDimensionsCount( );
                std::vector<const char*> symbolicDimensions;
                symbolicDimensions.resize( dimensionCount );
                tensorTypeAndShapeInfo.GetSymbolicDimensions( symbolicDimensions.data( ), dimensionCount );

                std::vector<AnsiString> symbolicDimensionStrings;
                symbolicDimensionStrings.resize( dimensionCount );
                for ( size_t i = 0; i < dimensionCount; i++ )
                {
                    auto ptr = symbolicDimensions[ i ];
                    if ( ptr )
                    {
                        symbolicDimensionStrings[ i ] = ptr;
                    }
                }
                result = std::make_shared<TensorTypeAndShapeInfo>( onnxType, name, elementType, elementCount, std::move( dimensions ), std::move( symbolicDimensionStrings ) );
            }
            break;
            case ONNX_TYPE_SEQUENCE:
            {
                auto ortSequenceTypeInfo = ortTypeInfo.GetSequenceTypeInfo( );
                auto ortElementType = ortSequenceTypeInfo.GetSequenceElementType( );
                auto elementType = CreateTypeInfo( AnsiString( ), ortElementType );
                result = std::make_shared<SequenceTypeInfo>( name, elementType );
            }
            break;
            case ONNX_TYPE_MAP:
            {
                auto ortMapTypeInfo = ortTypeInfo.GetMapTypeInfo( );
                auto keyType = ortMapTypeInfo.GetMapKeyType( );
                auto ortValueTypeInfo = ortMapTypeInfo.GetMapValueType( );
                auto valueTypeInfo = CreateTypeInfo( AnsiString( ), ortValueTypeInfo );
                result = std::make_shared<MapTypeInfo>( name, keyType, valueTypeInfo );
            }
            break;
            case ONNX_TYPE_OPAQUE:
            {
                result = std::make_shared<OpaqueTypeInfo>( name );
            }
            break;
            case ONNX_TYPE_OPTIONAL:
            {
                auto ortOptionalTypeInfo = ortTypeInfo.GetOptionalTypeInfo( );
                auto ortElementType = ortOptionalTypeInfo.GetOptionalElementType( );
                auto elementType = CreateTypeInfo( AnsiString( ), ortElementType );
                result = std::make_shared<OptionalTypeInfo>( name, elementType );
            }
            break;
        }
        return result;
    }

    HAI_EXPORT Metadata::Metadata( const Session& session )
    {
        Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
        Ort::Allocator allocator( session.Impl( ), memoryInfo );

        auto modelMetadata = session.GetModelMetadata( );
        auto producerName = modelMetadata.GetProducerNameAllocated( allocator );
        if ( producerName )
        {
            producerName_ = producerName.get( );
        }
        auto graphName = modelMetadata.GetGraphNameAllocated( allocator );
        if ( graphName )
        {
            graphName_ = graphName.get( );
        }
        auto domain = modelMetadata.GetDomainAllocated( allocator );
        if ( domain )
        {
            domain_ = domain.get( );
        }
        auto description = modelMetadata.GetDescriptionAllocated( allocator );
        if ( description )
        {
            description_ = description.get( );
        }
        auto graphDescription = modelMetadata.GetGraphDescriptionAllocated( allocator );
        if ( graphDescription )
        {
            graphDescription_ = graphDescription.get( );
        }
        version_ = modelMetadata.GetVersion( );

        auto count = session.GetInputCount( );
        inputs_.reserve( count );
        for ( size_t i = 0; i < count; i++ )
        {
            auto typeInfoNameAllocated = session.GetInputNameAllocated( i, allocator );
            AnsiString typeInfoName = typeInfoNameAllocated.get( );
            auto ortTypeInfo = session.GetInputTypeInfo( i );
            auto typeInfo = CreateTypeInfo( typeInfoName, ortTypeInfo );
            inputs_.emplace_back( std::move( typeInfo ) );
        }
        count = session.GetOutputCount( );
        outputs_.reserve( count );
        for ( size_t i = 0; i < count; i++ )
        {
            auto typeInfoNameAllocated = session.GetOutputNameAllocated( i, allocator );
            AnsiString typeInfoName = typeInfoNameAllocated.get( );
            auto ortTypeInfo = session.GetOutputTypeInfo( i );
            auto typeInfo = CreateTypeInfo( typeInfoName, ortTypeInfo );
            outputs_.emplace_back( std::move( typeInfo ) );
        }
        count = session.GetOverridableInitializerCount( );
        overridableInitializers_.reserve( count );
        for ( size_t i = 0; i < count; i++ )
        {
            auto typeInfoNameAllocated = session.GetOverridableInitializerNameAllocated( i, allocator );
            AnsiString typeInfoName = typeInfoNameAllocated.get( );
            auto ortTypeInfo = session.GetOverridableInitializerTypeInfo( i );
            auto typeInfo = CreateTypeInfo( typeInfoName, ortTypeInfo );
            overridableInitializers_.emplace_back( std::move( typeInfo ) );
        }

        auto customMetadataMapKeys = modelMetadata.GetCustomMetadataMapKeysAllocated( allocator );
        for ( const auto& key : customMetadataMapKeys )
        {
            auto value = modelMetadata.LookupCustomMetadataMapAllocated( key.get( ), allocator );
            customMetadataMap_.emplace( key.get(), value.get() );
        }


    }
}