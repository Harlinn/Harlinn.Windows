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
    using namespace Meta;
    using namespace Tensors;
    std::shared_ptr<TypeInfoBase> CreateTypeInfo( const AnsiString& name, const Ort::TypeInfo& ortTypeInfo )
    {
        std::shared_ptr<TypeInfoBase> result;
        auto onnxType = static_cast< TypeInfoType >( ortTypeInfo.GetONNXType( ) );
        switch ( onnxType )
        {
            case TypeInfoType::Unknown:
            {
                result = std::make_shared<UnknownTypeInfo>( name );
            }
            break;
            case TypeInfoType::Tensor:
            case TypeInfoType::Sparsetensor:
            {
                auto tensorTypeAndShapeInfo = ortTypeInfo.GetTensorTypeAndShapeInfo( );
                auto elementType = static_cast< TensorElementType >(tensorTypeAndShapeInfo.GetElementType( ));
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
                result = std::make_shared<TensorTypeAndShapeInfo>( onnxType, name, elementType, std::move( dimensions ), std::move( symbolicDimensionStrings ) );
            }
            break;
            case TypeInfoType::Sequence:
            {
                auto ortSequenceTypeInfo = ortTypeInfo.GetSequenceTypeInfo( );
                auto ortElementType = ortSequenceTypeInfo.GetSequenceElementType( );
                auto elementType = CreateTypeInfo( AnsiString( ), ortElementType );
                result = std::make_shared<SequenceTypeInfo>( name, elementType );
            }
            break;
            case TypeInfoType::Map:
            {
                auto ortMapTypeInfo = ortTypeInfo.GetMapTypeInfo( );
                auto keyType = static_cast< TensorElementType >( ortMapTypeInfo.GetMapKeyType( ) );
                auto ortValueTypeInfo = ortMapTypeInfo.GetMapValueType( );
                auto valueTypeInfo = CreateTypeInfo( AnsiString( ), ortValueTypeInfo );
                result = std::make_shared<MapTypeInfo>( name, keyType, valueTypeInfo );
            }
            break;
            case TypeInfoType::Opaque:
            {
                result = std::make_shared<OpaqueTypeInfo>( name );
            }
            break;
            case TypeInfoType::Optional:
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

    std::shared_ptr<Meta::Metadata> Session::CreateMetadata( )
    {
        auto result = std::make_shared<Meta::Metadata>( );
        Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
        Ort::Allocator allocator( Impl( ), memoryInfo );

        auto modelMetadata = GetModelMetadata( );
        auto producerName = modelMetadata.GetProducerNameAllocated( allocator );
        if ( producerName )
        {
            result->SetProducerName( producerName.get( ) );
        }
        auto graphName = modelMetadata.GetGraphNameAllocated( allocator );
        if ( graphName )
        {
            result->SetGraphName( graphName.get( ) );
        }
        auto domain = modelMetadata.GetDomainAllocated( allocator );
        if ( domain )
        {
            result->SetDomain( domain.get( ) );
        }
        auto description = modelMetadata.GetDescriptionAllocated( allocator );
        if ( description )
        {
            result->SetDescription( description.get( ) );
        }
        auto graphDescription = modelMetadata.GetGraphDescriptionAllocated( allocator );
        if ( graphDescription )
        {
            result->SetGraphDescription( graphDescription.get( ) );
        }
        result->SetVersion( modelMetadata.GetVersion( ) );

        auto count = GetInputCount( );

        std::vector<std::shared_ptr<TypeInfoBase>> inputs;
        inputs.reserve( count );
        for ( size_t i = 0; i < count; i++ )
        {
            auto typeInfoNameAllocated = GetInputNameAllocated( i, allocator );
            AnsiString typeInfoName = typeInfoNameAllocated.get( );
            auto ortTypeInfo = GetInputTypeInfo( i );
            auto typeInfo = CreateTypeInfo( typeInfoName, ortTypeInfo );
            inputs.emplace_back( std::move( typeInfo ) );
        }
        result->SetInputs( std::move( inputs ) );
        count = GetOutputCount( );
        std::vector<std::shared_ptr<TypeInfoBase>> outputs;
        outputs.reserve( count );
        for ( size_t i = 0; i < count; i++ )
        {
            auto typeInfoNameAllocated = GetOutputNameAllocated( i, allocator );
            AnsiString typeInfoName = typeInfoNameAllocated.get( );
            auto ortTypeInfo = GetOutputTypeInfo( i );
            auto typeInfo = CreateTypeInfo( typeInfoName, ortTypeInfo );
            outputs.emplace_back( std::move( typeInfo ) );
        }
        result->SetOutputs( std::move( outputs ) );
        count = GetOverridableInitializerCount( );
        std::vector<std::shared_ptr<TypeInfoBase>> overridableInitializers;
        overridableInitializers.reserve( count );
        for ( size_t i = 0; i < count; i++ )
        {
            auto typeInfoNameAllocated = GetOverridableInitializerNameAllocated( i, allocator );
            AnsiString typeInfoName = typeInfoNameAllocated.get( );
            auto ortTypeInfo = GetOverridableInitializerTypeInfo( i );
            auto typeInfo = CreateTypeInfo( typeInfoName, ortTypeInfo );
            overridableInitializers.emplace_back( std::move( typeInfo ) );
        }
        result->SetOverridableInitializers( std::move( overridableInitializers ) );

        std::map<AnsiString, AnsiString> customMetadataMap;
        auto customMetadataMapKeys = modelMetadata.GetCustomMetadataMapKeysAllocated( allocator );
        for ( const auto& key : customMetadataMapKeys )
        {
            auto value = modelMetadata.LookupCustomMetadataMapAllocated( key.get( ), allocator );
            customMetadataMap.emplace( key.get(), value.get() );
        }
        result->SetCustomMetadataMap( std::move( customMetadataMap ) );
        return result;

    }
}