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
    HAI_EXPORT void Node::Compute( const std::shared_ptr<NodeInput>& input, const std::shared_ptr<ResultSink>& resultSink )
    {
        auto session = Session( );
        auto metadata = Metadata( );
        Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
        Ort::Allocator allocator( session->Impl( ), memoryInfo );

        const auto& inputValues = input->Inputs( );
        std::vector<Ort::Value> ortInputValues;
        ortInputValues.reserve( inputValues.size() );
        auto bindings = Ort::IoBinding::IoBinding( session->Impl( ) );

        for ( const auto& inputValue : inputValues )
        {
            const auto& typeInfo = inputValue->TypeInfo( );
            auto type = typeInfo->Type( );
            switch ( type )
            {
                case Meta::TypeInfoType::Tensor:
                {
                    auto ti = typeInfo->As<Meta::TensorTypeAndShapeInfo>( );
                    const auto name = ti->Name( );
                    auto inputTensor = inputValue->As<Tensors::Tensor>( );
                    auto tensorData = inputTensor->Data( ).ToSpan( );
                    auto elementType = ti->ElementType( );
                    const auto& dimensions = ti->Dimensions( );

                    auto ortInputTensor = Ort::Value::CreateTensor( memoryInfo, tensorData.data( ), tensorData.size( ), dimensions.data( ), dimensions.size( ), static_cast< ONNXTensorElementDataType >( elementType ) );

                    bindings.BindInput( name.c_str( ), ortInputTensor );

                    ortInputValues.emplace_back( std::move( ortInputTensor ) );

                }
                break;
            }
        }
        auto nodeOutput = std::make_shared<NodeOutput>( metadata );
        const auto& outputValues = nodeOutput->Outputs( );
        std::vector<Ort::Value> ortOutputValues;
        ortOutputValues.reserve( outputValues.size( ) );

        for ( const auto& outputValue : outputValues )
        {
            const auto& typeInfo = outputValue->TypeInfo( );
            auto type = typeInfo->Type( );
            switch ( type )
            {
                case Meta::TypeInfoType::Tensor:
                {
                    auto ti = typeInfo->As<Meta::TensorTypeAndShapeInfo>( );
                    const auto name = ti->Name( );
                    auto outputTensor = outputValue->As<Tensors::Tensor>( );
                    auto tensorData = outputTensor->Data( ).ToSpan( );
                    auto elementType = ti->ElementType( );
                    const auto& dimensions = ti->Dimensions( );

                    auto ortOutputTensor = Ort::Value::CreateTensor( memoryInfo, tensorData.data( ), tensorData.size( ), dimensions.data( ), dimensions.size( ), static_cast< ONNXTensorElementDataType >( elementType ) );

                    bindings.BindOutput( name.c_str( ), ortOutputTensor );

                    ortOutputValues.emplace_back( std::move( ortOutputTensor ) );

                }
                break;
            }
        }

        Ort::RunOptions runOpts;
        auto stopwatch = Stopwatch::StartNew( );
        session->Run( runOpts, bindings );
        stopwatch.Stop( );
        auto computeTime = stopwatch.Elapsed( );
        bindings.SynchronizeOutputs( );

        resultSink->Process( computeTime, nodeOutput );
    }
}