#include "pch.h"
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

#include "HAIDirectMLX.h"

namespace Harlinn::AI::DML
{
    namespace
    {
        std::vector<UInt32> Range( UInt32 first, UInt32 last )
        {
            auto count = last - first;
            std::vector<UInt32> result;
            result.reserve( count );
            for ( UInt32 i = 0; i < count; i++ )
            {
                result.emplace_back( i + first );
            }
            return result;
        }


        std::unique_ptr<OperatorTypeInfo> MakeUnary( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes );
            return result;
        }
        std::unique_ptr<OperatorTypeInfo> MakeUnary( const char* name, TensorDataTypeMask inputTypes, std::vector<UInt32>& inputDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes, inputDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes, outputDimensions );
            return result;
        }


        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnary( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnary( const char* name, TensorDataTypeMask inputTypes, std::vector<UInt32>& inputDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes, inputDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes, outputDimensions );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes );
            result->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, std::vector<UInt32>& inputDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input, inputTypes, inputDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes, outputDimensions );
            result->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
            result->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeInplaceUnaryWithScaleBias( const char* name, TensorDataTypeMask inputTypes, std::vector<UInt32>& inputDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputTypes, inputDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes, outputDimensions );
            result->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeBinary( const char* name, TensorDataTypeMask inputATypes, TensorDataTypeMask inputBTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input, inputATypes );
            result->AddInputTensor( "BTensor", FieldFlags::Input, inputBTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes );
            return result;
        }
        std::unique_ptr<OperatorTypeInfo> MakeBinary( const char* name, TensorDataTypeMask inputATypes, std::vector<UInt32>& inputADimensions, TensorDataTypeMask inputBTypes, std::vector<UInt32>& inputBDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input, inputATypes, inputADimensions );
            result->AddInputTensor( "BTensor", FieldFlags::Input, inputBTypes, inputBDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputTypes, outputDimensions );
            return result;
        }


        std::unique_ptr<OperatorTypeInfo> MakeInplaceBinary( const char* name, TensorDataTypeMask inputATypes, TensorDataTypeMask inputBTypes, TensorDataTypeMask outputTypes )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputATypes );
            result->AddInputTensor( "BTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputBTypes );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes );
            return result;
        }

        std::unique_ptr<OperatorTypeInfo> MakeInplaceBinary( const char* name, TensorDataTypeMask inputATypes, std::vector<UInt32>& inputADimensions, TensorDataTypeMask inputBTypes, std::vector<UInt32>& inputBDimensions, TensorDataTypeMask outputTypes, std::vector<UInt32>& outputDimensions )
        {
            auto result = std::make_unique<OperatorTypeInfo>( name );
            result->AddInputTensor( "ATensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputATypes, inputADimensions );
            result->AddInputTensor( "BTensor", FieldFlags::Input | FieldFlags::InplaceExecution, inputBTypes, inputBDimensions );
            result->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, outputTypes, outputDimensions );
            return result;
        }

        using Map = std::unordered_map<DML::OperatorType, std::unique_ptr<DML::OperatorTypeInfo>>;


        void AddElementWiseIdentity( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseIdentity", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseIdentity, std::move( typeInfo ) );
        }

        void AddElementWiseAbs( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                (TensorDataTypeMask::Float32 | 
                    TensorDataTypeMask::Float16 | 
                    TensorDataTypeMask::Int64 | 
                    TensorDataTypeMask::Int32 | 
                    TensorDataTypeMask::Int16 | 
                    TensorDataTypeMask::Int8);
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseAbs", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseAbs, std::move( typeInfo ) );
        }
        void AddElementWiseACos( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & (TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseACos", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseACos, std::move( typeInfo ) );
        }
        void AddElementWiseAdd( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                (TensorDataTypeMask::Float32 | 
                    TensorDataTypeMask::Float16 | 
                    TensorDataTypeMask::Int64 | 
                    TensorDataTypeMask::Int32 | 
                    TensorDataTypeMask::Int16 | 
                    TensorDataTypeMask::Int8 | 
                    TensorDataTypeMask::UInt64 | 
                    TensorDataTypeMask::UInt32 | 
                    TensorDataTypeMask::UInt16 | 
                    TensorDataTypeMask::UInt8);
            auto typeInfo = MakeInplaceBinary( "ElementWiseAdd", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseAdd, std::move( typeInfo ) );
        }

        void AddElementWiseAdd1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseAdd1", dataTypes, dataTypes, dataTypes );
            typeInfo->AddFusedActivation("FusedActivation", FieldFlags::Optional );
            map.emplace( OperatorType::ElementWiseAdd1, std::move( typeInfo ) );
        }

        void AddElementWiseASin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseASin", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseASin, std::move( typeInfo ) );
        }

        void AddElementWiseATan( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseATan", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseATan, std::move( typeInfo ) );
        }

        void AddElementWiseCeil( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseCeil", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseCeil, std::move( typeInfo ) );
        }

        void AddElementWiseClip( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseClip", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Min" );
            typeInfo->AddFloat32( "Max" );
            map.emplace( OperatorType::ElementWiseClip, std::move( typeInfo ) );
        }

        void AddElementWiseCos( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseCos", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseCos, std::move( typeInfo ) );
        }

        void AddElementWiseDivide( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseDivide", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseDivide, std::move( typeInfo ) );
        }

        void AddElementWiseExp( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseExp", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseExp, std::move( typeInfo ) );
        }

        void AddElementWiseFloor( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseFloor", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseFloor, std::move( typeInfo ) );
        }

        void AddElementWiseLog( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseLog", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLog, std::move( typeInfo ) );
        }


        void AddElementWiseLogicalAnd( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalAnd", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLogicalAnd, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalEquals( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & 
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalEquals", inputDataTypes, inputDataTypes, outputDataTypes );
            map.emplace( OperatorType::ElementWiseLogicalEquals, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalGreaterThan( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalGreaterThan", inputDataTypes, inputDataTypes, outputDataTypes );
            map.emplace( OperatorType::ElementWiseLogicalGreaterThan, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalLessThan( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalLessThan", inputDataTypes, inputDataTypes, outputDataTypes );
            map.emplace( OperatorType::ElementWiseLogicalLessThan, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalNot( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalNot", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLogicalNot, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalOr( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalOr", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLogicalOr, std::move( typeInfo ) );
        }

        void AddElementWiseLogicalXor( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseLogicalXor", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseLogicalXor, std::move( typeInfo ) );
        }

        void AddElementWiseMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseMax", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseMax, std::move( typeInfo ) );
        }

        void AddElementWiseMean( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt32 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseMean", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseMean, std::move( typeInfo ) );
        }

        void AddElementWiseMin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseMin", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseMin, std::move( typeInfo ) );
        }

        void AddElementWiseMultiply( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseMultiply", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseMultiply, std::move( typeInfo ) );
        }

        void AddElementWisePow( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWisePow" );
            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddInputTensor( "ExponentTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddScaleBias( "ScaleBias", FieldFlags::Optional );
            map.emplace( OperatorType::ElementWisePow, std::move( typeInfo ) );
        }

        void AddElementWiseConstantPow( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseConstantPow", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Exponent" );
            map.emplace( OperatorType::ElementWiseConstantPow, std::move( typeInfo ) );
        }

        void AddElementWiseReciprocal( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseReciprocal", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseReciprocal, std::move( typeInfo ) );
        }

        void AddElementWiseSin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseSin", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSin, std::move( typeInfo ) );
        }

        void AddElementWiseSqrt( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseSqrt", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSqrt, std::move( typeInfo ) );
        }

        void AddElementWiseSubtract( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes &
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int64 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt64 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceBinary( "ElementWiseSubtract", dataTypes, dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSubtract, std::move( typeInfo ) );
        }

        void AddElementWiseTan( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseTan", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseTan, std::move( typeInfo ) );
        }

        void AddElementWiseThreshold( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & 
                ( TensorDataTypeMask::Float32 |
                    TensorDataTypeMask::Float16 |
                    TensorDataTypeMask::Int32 |
                    TensorDataTypeMask::Int16 |
                    TensorDataTypeMask::Int8 |
                    TensorDataTypeMask::UInt32 |
                    TensorDataTypeMask::UInt16 |
                    TensorDataTypeMask::UInt8 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseThreshold", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Min", FieldFlags::Input );
            map.emplace( OperatorType::ElementWiseThreshold, std::move( typeInfo ) );
        }
        

        void AddElementWiseQuantizeLinear( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int32  );
            auto scaleDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto zeroPointDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseQuantizeLinear" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input , inputDataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, scaleDataTypes );
            typeInfo->AddInputTensor( "ZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, zeroPointDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output , outputDataTypes );
            
            map.emplace( OperatorType::ElementWiseQuantizeLinear, std::move( typeInfo ) );
        }

        void AddElementWiseDequantizeLinear( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );
            auto scaleDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto zeroPointDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseDequantizeLinear" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, scaleDataTypes );
            typeInfo->AddInputTensor( "ZeroPointTensor", FieldFlags::Input | FieldFlags::Optional, zeroPointDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes );

            map.emplace( OperatorType::ElementWiseDequantizeLinear, std::move( typeInfo ) );
        }


        void AddActivationELU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ActivationELU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            map.emplace( OperatorType::ActivationELU, std::move( typeInfo ) );
        }

        void AddActivationHardMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnaryWithScaleBias( "ActivationHardMax", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationHardMax, std::move( typeInfo ) );
        }

        void AddActivationHardSigmoid( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ActivationHardSigmoid", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            map.emplace( OperatorType::ActivationHardSigmoid, std::move( typeInfo ) );
        }

        void AddActivationIdentity( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationIdentity", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationIdentity, std::move( typeInfo ) );
        }

        void AddActivationLeakyReLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationLeakyReLU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            map.emplace( OperatorType::ActivationLeakyReLU, std::move( typeInfo ) );
        }

        void AddActivationLinear( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationLinear", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            map.emplace( OperatorType::ActivationLinear, std::move( typeInfo ) );
        }

        void AddActivationLogSoftMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnary( "ActivationLogSoftMax", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationLogSoftMax, std::move( typeInfo ) );
        }


        void AddActivationParameterizedReLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8  );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ActivationParameterizedReLU" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input | FieldFlags::InplaceExecution, dataTypes );
            typeInfo->AddInputTensor( "SlopeTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output | FieldFlags::InplaceExecution, dataTypes );

            map.emplace( OperatorType::ActivationParameterizedReLU, std::move( typeInfo ) );
        }

        void AddActivationParametricSoftPlus( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationParametricSoftPlus", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            map.emplace( OperatorType::ActivationParametricSoftPlus, std::move( typeInfo ) );
        }

        void AddActivationReLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationReLU", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationReLU, std::move( typeInfo ) );
        }

        void AddActivationScaledELU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationScaledELU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Gamma", FieldFlags::Input );
            map.emplace( OperatorType::ActivationScaledELU, std::move( typeInfo ) );
        }

        void AddActivationScaledTanH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationScaledTanH", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            map.emplace( OperatorType::ActivationScaledTanH, std::move( typeInfo ) );
        }


        void AddActivationSigmoid( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationSigmoid", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationSigmoid, std::move( typeInfo ) );
        }

        void AddActivationSoftMax( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeUnary( "ActivationSoftMax", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationSoftMax, std::move( typeInfo ) );
        }

        void AddActivationSoftPlus( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationSoftPlus", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Steepness", FieldFlags::Input );
            map.emplace( OperatorType::ActivationSoftPlus, std::move( typeInfo ) );
        }

        void AddActivationSoftSign( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationSoftSign", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationSoftSign, std::move( typeInfo ) );
        }

        void AddActivationTanH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationTanH", dataTypes, dataTypes );
            map.emplace( OperatorType::ActivationTanH, std::move( typeInfo ) );
        }


        void AddActivationThresholdedReLU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto typeInfo = MakeInplaceUnary( "ActivationThresholdedReLU", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            map.emplace( OperatorType::ActivationThresholdedReLU, std::move( typeInfo ) );
        }


        void AddConvolution( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Convolution" );

            auto dimensions = Range( 3, 5 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "FilterTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddEnum( "Mode", EnumType::ConvolutionMode, FieldFlags::Input );
            typeInfo->AddEnum( "Direction", EnumType::ConvolutionDirection, FieldFlags::Input );
            typeInfo->AddSize( "DimensionCount", 5, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Strides", FieldFlags::Input );
            typeInfo->AddFloat32Array( "Dilations", FieldFlags::Input );
            typeInfo->AddFloat32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddFloat32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddFloat32Array( "OutputPadding", FieldFlags::Input );
            typeInfo->AddUInt32( "GroupCount", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::Convolution, std::move( typeInfo ) );
        }

        void AddGEMM( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "GEMM" );

            auto dimensions = Range( 2, 4 );

            typeInfo->AddInputTensor( "ATensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "CTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddEnum( "TransA", EnumType::MatrixTransform, FieldFlags::Input );
            typeInfo->AddEnum( "TransB", EnumType::MatrixTransform, FieldFlags::Input );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::GEMM, std::move( typeInfo ) );
        }

        void AddReduce( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int64 | 
                TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Reduce" );

            typeInfo->AddEnum( "Function", EnumType::ReduceFunction, FieldFlags::Input );
            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, inputDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, outputDataTypes );
            typeInfo->AddSize( "AxisCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Axes", FieldFlags::Input );

            map.emplace( OperatorType::Reduce, std::move( typeInfo ) );
        }

        void AddAveragePooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "AveragePooling", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddBoolean( "IncludePadding", FieldFlags::Input );

            map.emplace( OperatorType::AveragePooling, std::move( typeInfo ) );
        }

        void AddLPPooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "LPPooling", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );
            typeInfo->AddUInt32( "P", FieldFlags::Input );

            map.emplace( OperatorType::LPPooling, std::move( typeInfo ) );
        }

        void AddMaxPooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "MaxPooling", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::MaxPooling, std::move( typeInfo ) );
        }

        void AddROIPooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ROIPooling" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "ROITensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddFloat32( "SpatialScale", FieldFlags::Input );
            typeInfo->AddSize2D( "PooledSize", FieldFlags::Input );

            map.emplace( OperatorType::ROIPooling, std::move( typeInfo ) );
        }

        void AddSlice( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | 
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | 
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "Slice", dataTypes, dataTypes );
            typeInfo->AddSize( "DimensionCount", 3, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Offsets", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Sizes", FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );

            map.emplace( OperatorType::Slice, std::move( typeInfo ) );
        }

        void AddCast( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "Cast", dataTypes, dataTypes );

            map.emplace( OperatorType::Cast, std::move( typeInfo ) );
        }

        void AddSplit( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Split" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddSize( "OutputCount", 1, FieldFlags::Input );
            typeInfo->AddOutputTensorArray( "OutputTensors", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );

            map.emplace( OperatorType::Split, std::move( typeInfo ) );
        }

        void AddJoin( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Join" );

            typeInfo->AddSize( "InputCount", 1, FieldFlags::Input );
            typeInfo->AddInputTensorArray( "InputTensors", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );

            map.emplace( OperatorType::Join, std::move( typeInfo ) );
        }


        void AddPadding( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "Padding", dataTypes, dataTypes );
            typeInfo->AddEnum( "PaddingMode", EnumType::PaddingMode, FieldFlags::Input );
            typeInfo->AddFloat32( "PaddingValue", FieldFlags::Input );
            typeInfo->AddSize( "DimensionCount", 2, FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::Padding, std::move( typeInfo ) );
        }

        void AddValueScale2D( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16  );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "ValueScale2D", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddFloat32( "Scale", FieldFlags::Input );
            typeInfo->AddSize( "ChannelCount", 1, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Bias", FieldFlags::Input );

            map.emplace( OperatorType::ValueScale2D, std::move( typeInfo ) );
        }

        void AddUpSample2D( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "UpSample2D", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddSize2D( "ScaleSize", FieldFlags::Input );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode ,FieldFlags::Input );

            map.emplace( OperatorType::UpSample2D, std::move( typeInfo ) );
        }

        void AddGather( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "Gather" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesDataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );
            typeInfo->AddUInt32( "IndexDimensions", FieldFlags::Input );

            map.emplace( OperatorType::Join, std::move( typeInfo ) );
        }

        void AddSpaceToDepth( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "SpaceToDepth", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddUInt32( "BlockSize", FieldFlags::Input );

            map.emplace( OperatorType::SpaceToDepth, std::move( typeInfo ) );
        }

        void AddDepthToSpace( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "DepthToSpace", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddUInt32( "BlockSize", FieldFlags::Input );

            map.emplace( OperatorType::DepthToSpace, std::move( typeInfo ) );
        }

        void AddTile( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::AllButNibble );

            auto typeInfo = MakeUnary( "Tile", dataTypes, dataTypes );

            typeInfo->AddSize( "RepeatsCount", 1, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Repeats", FieldFlags::Input );

            map.emplace( OperatorType::Tile, std::move( typeInfo ) );
        }


        void AddTopK( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "TopK" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputValueTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddInputTensor( "OutputIndexTensor", FieldFlags::Output, indicesDataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );
            typeInfo->AddUInt32( "K", FieldFlags::Input );

            map.emplace( OperatorType::TopK, std::move( typeInfo ) );
        }


        void AddBatchNormalization( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "BatchNormalization" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "MeanTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "VarianceTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input, dataTypes );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddBoolean( "Spatial", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::BatchNormalization, std::move( typeInfo ) );
        }

        void AddMeanVarianceNormalization( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MeanVarianceNormalization" );

            auto dimensions = Range( 4, 4 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "ScaleTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );

            typeInfo->AddBoolean( "CrossChannel", FieldFlags::Input );
            typeInfo->AddBoolean( "NormalizeVariance", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddFusedActivation( "FusedActivation", FieldFlags::Input | FieldFlags::Optional );

            map.emplace( OperatorType::MeanVarianceNormalization, std::move( typeInfo ) );
        }

        void AddLocalResponseNormalization( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = MakeUnary( "LocalResponseNormalization", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddBoolean( "CrossChannel", FieldFlags::Input );
            typeInfo->AddUInt32( "LocalSize", FieldFlags::Input );
            typeInfo->AddFloat32( "Alpha", FieldFlags::Input );
            typeInfo->AddFloat32( "Beta", FieldFlags::Input );
            typeInfo->AddFloat32( "Bias", FieldFlags::Input );

            map.emplace( OperatorType::LocalResponseNormalization, std::move( typeInfo ) );
        }

        void AddLPNormalization( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeUnary( "LPNormalization", dataTypes, dataTypes );

            typeInfo->AddUInt32( "Axis", FieldFlags::Input );
            typeInfo->AddFloat32( "Epsilon", FieldFlags::Input );
            typeInfo->AddUInt32( "P", FieldFlags::Input );

            map.emplace( OperatorType::LPNormalization, std::move( typeInfo ) );
        }


        void AddRNN( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "RNN" );

            auto dimensions = Range( 4, 4 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "WeightTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "RecurrenceTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "HiddenInitTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "SequenceLengthsTensor", FieldFlags::Input | FieldFlags::Optional, TensorDataTypeMask::UInt32, dimensions );
            
            typeInfo->AddOutputTensor( "OutputSequenceTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputSingleTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddSize( "ActivationDescCount", 1, FieldFlags::Input );
            typeInfo->AddOperatorArray( "ActivationDescs", FieldFlags::Input );
            typeInfo->AddEnum( "Direction", EnumType::RecurrentNetworkDirection,FieldFlags::Input );
            

            map.emplace( OperatorType::RNN, std::move( typeInfo ) );
        }

        void AddLSTM( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "LSTM" );

            auto dimensions = Range( 4, 4 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "WeightTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "RecurrenceTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "HiddenInitTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "CellMemInitTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "SequenceLengthsTensor", FieldFlags::Input | FieldFlags::Optional, TensorDataTypeMask::UInt32, dimensions );
            typeInfo->AddInputTensor( "PeepholeTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputSequenceTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputSingleTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputCellSingleTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddSize( "ActivationDescCount", 1, FieldFlags::Input );
            typeInfo->AddOperatorArray( "ActivationDescs", FieldFlags::Input );
            typeInfo->AddEnum( "Direction", EnumType::RecurrentNetworkDirection, FieldFlags::Input );

            typeInfo->AddFloat32( "ClipThreshold", FieldFlags::Input );
            typeInfo->AddBoolean( "UseClipThreshold", FieldFlags::Input );
            typeInfo->AddBoolean( "CoupleInputForget", FieldFlags::Input );


            map.emplace( OperatorType::LSTM, std::move( typeInfo ) );
        }

        void AddGRU( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "GRU" );

            auto dimensions = Range( 4, 4 );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "WeightTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "RecurrenceTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "BiasTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "HiddenInitTensor", FieldFlags::Input | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddInputTensor( "SequenceLengthsTensor", FieldFlags::Input | FieldFlags::Optional, TensorDataTypeMask::UInt32, dimensions );

            typeInfo->AddOutputTensor( "OutputSequenceTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );
            typeInfo->AddOutputTensor( "OutputSingleTensor", FieldFlags::Output | FieldFlags::Optional, dataTypes, dimensions );

            typeInfo->AddSize( "ActivationDescCount", 1, FieldFlags::Input );
            typeInfo->AddOperatorArray( "ActivationDescs", FieldFlags::Input );
            typeInfo->AddEnum( "Direction", EnumType::RecurrentNetworkDirection, FieldFlags::Input );
            typeInfo->AddBoolean( "LinearBeforeReset", FieldFlags::Input );

            map.emplace( OperatorType::GRU, std::move( typeInfo ) );
        }

        void AddElementWiseSign( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceUnary( "ElementWiseSign", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSign, std::move( typeInfo ) );
        }

        void AddElementWiseIsNaN( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto outputDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeUnary( "ElementWiseIsNaN", inputDataTypes, outputDataTypes );
            map.emplace( OperatorType::ElementWiseIsNaN, std::move( typeInfo ) );
        }

        void AddElementWiseErf( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseErf", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseErf, std::move( typeInfo ) );
        }

        void AddElementWiseSinH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseSinH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseSinH, std::move( typeInfo ) );
        }

        void AddElementWiseCosH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseCosH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseCosH, std::move( typeInfo ) );
        }

        void AddElementWiseTanH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseTanH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseTanH, std::move( typeInfo ) );
        }

        void AddElementWiseASinH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseASinH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseASinH, std::move( typeInfo ) );
        }

        void AddElementWiseACosH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseACosH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseACosH, std::move( typeInfo ) );
        }

        void AddElementWiseATanH( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnaryWithScaleBias( "ElementWiseATanH", dataTypes, dataTypes );
            map.emplace( OperatorType::ElementWiseATanH, std::move( typeInfo ) );
        }

        void AddElementWiseIf( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ElementWiseIf" );

            typeInfo->AddInputTensor( "ConditionTensor", FieldFlags::Input, TensorDataTypeMask::UInt8 );
            typeInfo->AddInputTensor( "ATensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "BTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );

            map.emplace( OperatorType::ElementWiseIf, std::move( typeInfo ) );
        }

        void AddActivationShrink( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | 
                        TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | 
                        TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceUnary( "ActivationShrink", dataTypes, dataTypes );
            typeInfo->AddFloat32( "Bias", FieldFlags::Input );
            typeInfo->AddFloat32( "Threshold", FieldFlags::Input );

            map.emplace( OperatorType::ActivationShrink, std::move( typeInfo ) );
        }

        void AddMaxPooling1( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 | 
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto outputIndicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto dimensions = Range( 4, 5 );

            auto typeInfo = MakeUnary( "MaxPooling1", dataTypes, dimensions, dataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputIndicesTensor", FieldFlags::Output | FieldFlags::Optional, outputIndicesDataTypes, dimensions );

            typeInfo->AddSize( "DimensionCount", 4, FieldFlags::Input );
            typeInfo->AddUInt32Array( "Strides", FieldFlags::Input );
            typeInfo->AddUInt32Array( "WindowSize", FieldFlags::Input );
            typeInfo->AddUInt32Array( "StartPadding", FieldFlags::Input );
            typeInfo->AddUInt32Array( "EndPadding", FieldFlags::Input );

            map.emplace( OperatorType::MaxPooling1, std::move( typeInfo ) );
        }

        void AddMaxUnpooling( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto dimensions = Range( 4, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "MaxUnpooling" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes, dimensions );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesDataTypes, dimensions );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );

            map.emplace( OperatorType::MaxUnpooling, std::move( typeInfo ) );
        }

        void AddDiagonalMatrix( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float64 | TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 2, 4 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "DiagonalMatrix" );
            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes, dimensions );
            typeInfo->AddInt32( "Offset", FieldFlags::Input );
            typeInfo->AddFloat32( "Value", FieldFlags::Input );

            map.emplace( OperatorType::DiagonalMatrix, std::move( typeInfo ) );
        }


        void AddScatterElements( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "ScatterElements" );

            typeInfo->AddInputTensor( "InputTensor", FieldFlags::Input, dataTypes );
            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesDataTypes );
            typeInfo->AddInputTensor( "UpdatesTensor", FieldFlags::Input, dataTypes );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );

            map.emplace( OperatorType::ScatterElements, std::move( typeInfo ) );
        }


        void AddOneHot( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & TensorDataTypeMask::AllButNibble;

            auto indicesDataTypes = supportedDataTypes & ( TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 );

            auto typeInfo = std::make_unique<OperatorTypeInfo>( "OneHot" );

            typeInfo->AddInputTensor( "IndicesTensor", FieldFlags::Input, indicesDataTypes );
            typeInfo->AddInputTensor( "ValuesTensor", FieldFlags::Input, dataTypes );

            typeInfo->AddOutputTensor( "OutputTensor", FieldFlags::Output, dataTypes );
            typeInfo->AddUInt32( "Axis", FieldFlags::Input );

            map.emplace( OperatorType::OneHot, std::move( typeInfo ) );
        }

        void AddResample( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 | TensorDataTypeMask::Int8 | TensorDataTypeMask::UInt8 );

            auto dimensions = Range( 1, 4 );

            auto typeInfo = MakeUnary( "Resample", dataTypes, dimensions, dataTypes, dimensions );
            typeInfo->AddEnum( "InterpolationMode", EnumType::InterpolationMode, FieldFlags::Input );

            typeInfo->AddSize( "ScaleCount", 1, FieldFlags::Input );
            typeInfo->AddFloat32Array( "Scales", FieldFlags::Input );

            map.emplace( OperatorType::Resample, std::move( typeInfo ) );
        }

        void AddElementWiseBitShiftLeft( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseBitShiftLeft", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseBitShiftLeft, std::move( typeInfo ) );
        }

        void AddElementWiseBitShiftRight( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseBitShiftRight", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseBitShiftRight, std::move( typeInfo ) );
        }

        void AddElementWiseRound( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );

            auto typeInfo = MakeInplaceUnary( "ElementWiseRound", dataTypes, dataTypes );
            typeInfo->AddEnum( "RoundingMode", EnumType::RoundingMode, FieldFlags::Input );

            map.emplace( OperatorType::ElementWiseRound, std::move( typeInfo ) );
        }

        void AddElementWiseIsInfinity( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto inputDataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 );
            auto outputDataTypes = supportedDataTypes & TensorDataTypeMask::UInt8;

            auto typeInfo = MakeUnary( "ElementWiseIsInfinity", inputDataTypes, outputDataTypes );
            typeInfo->AddEnum( "InfinityMode", EnumType::IsInfinityMode, FieldFlags::Input );

            map.emplace( OperatorType::ElementWiseIsInfinity, std::move( typeInfo ) );
        }

        void AddElementWiseModulusTruncate( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseModulusTruncate", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseModulusTruncate, std::move( typeInfo ) );
        }

        void AddElementWiseModulusFloor( FeatureLevel featureLevel, TensorDataTypeMask supportedDataTypes, Map& map )
        {
            auto dataTypes = supportedDataTypes & ( TensorDataTypeMask::Float32 | TensorDataTypeMask::Float16 |
                TensorDataTypeMask::Int64 | TensorDataTypeMask::Int32 | TensorDataTypeMask::Int16 | TensorDataTypeMask::Int8 |
                TensorDataTypeMask::UInt64 | TensorDataTypeMask::UInt32 | TensorDataTypeMask::UInt16 | TensorDataTypeMask::UInt8 );

            auto typeInfo = MakeInplaceBinary( "ElementWiseModulusFloor", dataTypes, dataTypes, dataTypes );

            map.emplace( OperatorType::ElementWiseModulusFloor, std::move( typeInfo ) );
        }



        std::unordered_map<DML::OperatorType, std::unique_ptr<DML::OperatorTypeInfo>> InitializeOperatorTypeInfoMap( const Device& device )
        {
            std::unordered_map<DML::OperatorType, std::unique_ptr<DML::OperatorTypeInfo>> result;

            FeatureLevel featureLevel = device.SupportedFeatureLevel( );
            TensorDataTypeMask supportedDataTypes = device.SupportedTensorDataTypes( );

            AddElementWiseIdentity( featureLevel, supportedDataTypes, result );
            AddElementWiseAbs( featureLevel, supportedDataTypes, result );
            AddElementWiseACos( featureLevel, supportedDataTypes, result );
            AddElementWiseAdd( featureLevel, supportedDataTypes, result );
            AddElementWiseAdd1( featureLevel, supportedDataTypes, result );
            AddElementWiseASin( featureLevel, supportedDataTypes, result );
            AddElementWiseATan( featureLevel, supportedDataTypes, result );
            AddElementWiseCeil( featureLevel, supportedDataTypes, result );
            AddElementWiseClip( featureLevel, supportedDataTypes, result );
            AddElementWiseCos( featureLevel, supportedDataTypes, result );
            AddElementWiseDivide( featureLevel, supportedDataTypes, result );
            AddElementWiseExp( featureLevel, supportedDataTypes, result );
            AddElementWiseLog( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalAnd( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalEquals( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalGreaterThan( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalLessThan( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalNot( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalOr( featureLevel, supportedDataTypes, result );
            AddElementWiseLogicalXor( featureLevel, supportedDataTypes, result );
            AddElementWiseMax( featureLevel, supportedDataTypes, result );
            AddElementWiseMean( featureLevel, supportedDataTypes, result );
            AddElementWiseMin( featureLevel, supportedDataTypes, result );
            AddElementWiseMultiply( featureLevel, supportedDataTypes, result );
            AddElementWisePow( featureLevel, supportedDataTypes, result );
            AddElementWiseConstantPow( featureLevel, supportedDataTypes, result );
            AddElementWiseReciprocal( featureLevel, supportedDataTypes, result );
            AddElementWiseSin( featureLevel, supportedDataTypes, result );
            AddElementWiseSqrt( featureLevel, supportedDataTypes, result );
            AddElementWiseSubtract( featureLevel, supportedDataTypes, result );
            AddElementWiseTan( featureLevel, supportedDataTypes, result );
            AddElementWiseThreshold( featureLevel, supportedDataTypes, result );
            AddElementWiseQuantizeLinear( featureLevel, supportedDataTypes, result );
            AddElementWiseDequantizeLinear( featureLevel, supportedDataTypes, result );
            AddActivationELU( featureLevel, supportedDataTypes, result );
            AddActivationHardMax( featureLevel, supportedDataTypes, result );
            AddActivationHardSigmoid( featureLevel, supportedDataTypes, result );
            AddActivationIdentity( featureLevel, supportedDataTypes, result );
            AddActivationLeakyReLU( featureLevel, supportedDataTypes, result );
            AddActivationLinear( featureLevel, supportedDataTypes, result );
            AddActivationLogSoftMax( featureLevel, supportedDataTypes, result );
            AddActivationParameterizedReLU( featureLevel, supportedDataTypes, result );
            AddActivationParametricSoftPlus( featureLevel, supportedDataTypes, result );
            AddActivationReLU( featureLevel, supportedDataTypes, result );
            AddActivationScaledELU( featureLevel, supportedDataTypes, result );
            AddActivationScaledTanH( featureLevel, supportedDataTypes, result );
            AddActivationSigmoid( featureLevel, supportedDataTypes, result );
            AddActivationSoftMax( featureLevel, supportedDataTypes, result );
            AddActivationSoftPlus( featureLevel, supportedDataTypes, result );
            AddActivationSoftSign( featureLevel, supportedDataTypes, result );
            AddActivationTanH( featureLevel, supportedDataTypes, result );
            AddActivationThresholdedReLU( featureLevel, supportedDataTypes, result );
            AddConvolution( featureLevel, supportedDataTypes, result );
            AddGEMM( featureLevel, supportedDataTypes, result );
            AddReduce( featureLevel, supportedDataTypes, result );
            AddAveragePooling( featureLevel, supportedDataTypes, result );
            AddLPPooling( featureLevel, supportedDataTypes, result );
            AddROIPooling( featureLevel, supportedDataTypes, result );
            AddSlice( featureLevel, supportedDataTypes, result );
            AddCast( featureLevel, supportedDataTypes, result );
            AddSplit( featureLevel, supportedDataTypes, result );
            AddJoin( featureLevel, supportedDataTypes, result );
            AddPadding( featureLevel, supportedDataTypes, result );
            AddValueScale2D( featureLevel, supportedDataTypes, result );
            AddUpSample2D( featureLevel, supportedDataTypes, result );
            AddGather( featureLevel, supportedDataTypes, result );
            AddSpaceToDepth( featureLevel, supportedDataTypes, result );
            AddDepthToSpace( featureLevel, supportedDataTypes, result );
            AddTile( featureLevel, supportedDataTypes, result );
            AddTopK( featureLevel, supportedDataTypes, result );
            AddBatchNormalization( featureLevel, supportedDataTypes, result );
            AddMeanVarianceNormalization( featureLevel, supportedDataTypes, result );
            AddLocalResponseNormalization( featureLevel, supportedDataTypes, result );
            AddLPNormalization( featureLevel, supportedDataTypes, result );
            AddRNN( featureLevel, supportedDataTypes, result );
            AddLSTM( featureLevel, supportedDataTypes, result );
            AddGRU( featureLevel, supportedDataTypes, result );
            AddElementWiseSign( featureLevel, supportedDataTypes, result );
            AddElementWiseIsNaN( featureLevel, supportedDataTypes, result );
            AddElementWiseErf( featureLevel, supportedDataTypes, result );
            AddElementWiseSinH( featureLevel, supportedDataTypes, result );
            AddElementWiseCosH( featureLevel, supportedDataTypes, result );
            AddElementWiseTanH( featureLevel, supportedDataTypes, result );
            AddElementWiseASinH( featureLevel, supportedDataTypes, result );
            AddElementWiseACosH( featureLevel, supportedDataTypes, result );
            AddElementWiseATanH( featureLevel, supportedDataTypes, result );
            AddElementWiseIf( featureLevel, supportedDataTypes, result );
            AddActivationShrink( featureLevel, supportedDataTypes, result );
            AddMaxPooling1( featureLevel, supportedDataTypes, result );
            AddMaxUnpooling( featureLevel, supportedDataTypes, result );
            AddDiagonalMatrix( featureLevel, supportedDataTypes, result );
            AddScatterElements( featureLevel, supportedDataTypes, result );
            AddOneHot( featureLevel, supportedDataTypes, result );
            AddResample( featureLevel, supportedDataTypes, result );
            AddElementWiseBitShiftLeft( featureLevel, supportedDataTypes, result );
            AddElementWiseBitShiftRight( featureLevel, supportedDataTypes, result );
            AddElementWiseRound( featureLevel, supportedDataTypes, result );
            AddElementWiseIsInfinity( featureLevel, supportedDataTypes, result );
            AddElementWiseModulusTruncate( featureLevel, supportedDataTypes, result );
            AddElementWiseModulusFloor( featureLevel, supportedDataTypes, result );

            return result;
        }

        
    }

    HAI_EXPORT OperatorTypeInfoMap Device::GetOperatorTypeInfo( ) const
    {
        return InitializeOperatorTypeInfoMap( *this );
    }


}
